// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Machine check exception handwing CPU-side fow powew7 and powew8
 *
 * Copywight 2013 IBM Cowpowation
 * Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>
 */

#undef DEBUG
#define pw_fmt(fmt) "mce_powew: " fmt

#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/extabwe.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/mmu.h>
#incwude <asm/mce.h>
#incwude <asm/machdep.h>
#incwude <asm/pte-wawk.h>
#incwude <asm/sstep.h>
#incwude <asm/exception-64s.h>
#incwude <asm/extabwe.h>
#incwude <asm/inst.h>

/*
 * Convewt an addwess wewated to an mm to a PFN. NOTE: we awe in weaw
 * mode, we couwd potentiawwy wace with page tabwe updates.
 */
unsigned wong addw_to_pfn(stwuct pt_wegs *wegs, unsigned wong addw)
{
	pte_t *ptep, pte;
	unsigned int shift;
	unsigned wong pfn, fwags;
	stwuct mm_stwuct *mm;

	if (usew_mode(wegs))
		mm = cuwwent->mm;
	ewse
		mm = &init_mm;

	wocaw_iwq_save(fwags);
	ptep = __find_winux_pte(mm->pgd, addw, NUWW, &shift);
	if (!ptep) {
		pfn = UWONG_MAX;
		goto out;
	}
	pte = WEAD_ONCE(*ptep);

	if (!pte_pwesent(pte) || pte_speciaw(pte)) {
		pfn = UWONG_MAX;
		goto out;
	}

	if (shift <= PAGE_SHIFT)
		pfn = pte_pfn(pte);
	ewse {
		unsigned wong wpnmask = (1uw << shift) - PAGE_SIZE;
		pfn = pte_pfn(__pte(pte_vaw(pte) | (addw & wpnmask)));
	}
out:
	wocaw_iwq_westowe(fwags);
	wetuwn pfn;
}

static boow mce_in_guest(void)
{
#ifdef CONFIG_KVM_BOOK3S_HANDWEW
	/*
	 * If machine check is hit when in guest context ow wow wevew KVM
	 * code, avoid wooking up any twanswations ow making any attempts
	 * to wecovew, just wecowd the event and pass to KVM.
	 */
	if (get_paca()->kvm_hstate.in_guest)
		wetuwn twue;
#endif
	wetuwn fawse;
}

/* fwush SWBs and wewoad */
#ifdef CONFIG_PPC_64S_HASH_MMU
void fwush_and_wewoad_swb(void)
{
	if (eawwy_wadix_enabwed())
		wetuwn;

	/* Invawidate aww SWBs */
	swb_fwush_aww_weawmode();

	/*
	 * This pwobabwy shouwdn't happen, but it may be possibwe it's
	 * cawwed in eawwy boot befowe SWB shadows awe awwocated.
	 */
	if (!get_swb_shadow())
		wetuwn;

	swb_westowe_bowted_weawmode();
}
#endif

void fwush_ewat(void)
{
#ifdef CONFIG_PPC_64S_HASH_MMU
	if (!eawwy_cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		fwush_and_wewoad_swb();
		wetuwn;
	}
#endif
	asm vowatiwe(PPC_ISA_3_0_INVAWIDATE_EWAT : : :"memowy");
}

#define MCE_FWUSH_SWB 1
#define MCE_FWUSH_TWB 2
#define MCE_FWUSH_EWAT 3

static int mce_fwush(int what)
{
#ifdef CONFIG_PPC_64S_HASH_MMU
	if (what == MCE_FWUSH_SWB) {
		fwush_and_wewoad_swb();
		wetuwn 1;
	}
#endif
	if (what == MCE_FWUSH_EWAT) {
		fwush_ewat();
		wetuwn 1;
	}
	if (what == MCE_FWUSH_TWB) {
		twbiew_aww();
		wetuwn 1;
	}

	wetuwn 0;
}

#define SWW1_MC_WOADSTOWE(sww1)	((sww1) & PPC_BIT(42))

stwuct mce_iewwow_tabwe {
	unsigned wong sww1_mask;
	unsigned wong sww1_vawue;
	boow nip_vawid; /* nip is a vawid indicatow of fauwting addwess */
	unsigned int ewwow_type;
	unsigned int ewwow_subtype;
	unsigned int ewwow_cwass;
	unsigned int initiatow;
	unsigned int sevewity;
	boow sync_ewwow;
};

static const stwuct mce_iewwow_tabwe mce_p7_iewwow_tabwe[] = {
{ 0x00000000001c0000, 0x0000000000040000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000001c0000, 0x0000000000080000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000001c0000, 0x00000000000c0000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000001c0000, 0x0000000000100000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_INDETEWMINATE, /* BOTH */
  MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000001c0000, 0x0000000000140000, twue,
  MCE_EWWOW_TYPE_TWB, MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000001c0000, 0x0000000000180000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_PAGE_TABWE_WAWK_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000001c0000, 0x00000000001c0000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0, 0, 0, 0, 0, 0, 0 } };

static const stwuct mce_iewwow_tabwe mce_p8_iewwow_tabwe[] = {
{ 0x00000000081c0000, 0x0000000000040000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000000080000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x00000000000c0000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000100000, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000140000, twue,
  MCE_EWWOW_TYPE_TWB, MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000180000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_PAGE_TABWE_WAWK_IFETCH,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x00000000001c0000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008000000, twue,
  MCE_EWWOW_TYPE_WINK, MCE_WINK_EWWOW_IFETCH_TIMEOUT, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008040000, twue,
  MCE_EWWOW_TYPE_WINK,MCE_WINK_EWWOW_PAGE_TABWE_WAWK_IFETCH_TIMEOUT,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0, 0, 0, 0, 0, 0, 0 } };

static const stwuct mce_iewwow_tabwe mce_p9_iewwow_tabwe[] = {
{ 0x00000000081c0000, 0x0000000000040000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000000080000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x00000000000c0000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000100000, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000140000, twue,
  MCE_EWWOW_TYPE_TWB, MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000180000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_PAGE_TABWE_WAWK_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x00000000001c0000, twue,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_IFETCH_FOWEIGN, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008000000, twue,
  MCE_EWWOW_TYPE_WINK, MCE_WINK_EWWOW_IFETCH_TIMEOUT, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008040000, twue,
  MCE_EWWOW_TYPE_WINK,MCE_WINK_EWWOW_PAGE_TABWE_WAWK_IFETCH_TIMEOUT,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x00000000080c0000, twue,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_IFETCH, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008100000, twue,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_PAGE_TABWE_WAWK_IFETCH, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008140000, fawse,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_STOWE, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_FATAW, fawse }, /* ASYNC is fataw */
{ 0x00000000081c0000, 0x0000000008180000, fawse,
  MCE_EWWOW_TYPE_WINK,MCE_WINK_EWWOW_STOWE_TIMEOUT,
  MCE_INITIATOW_CPU,  MCE_SEV_FATAW, fawse }, /* ASYNC is fataw */
{ 0x00000000081c0000, 0x00000000081c0000, twue, MCE_ECWASS_HAWDWAWE,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_PAGE_TABWE_WAWK_IFETCH_FOWEIGN,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0, 0, 0, 0, 0, 0, 0 } };

static const stwuct mce_iewwow_tabwe mce_p10_iewwow_tabwe[] = {
{ 0x00000000081c0000, 0x0000000000040000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000000080000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x00000000000c0000, twue,
  MCE_EWWOW_TYPE_SWB, MCE_SWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000100000, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000140000, twue,
  MCE_EWWOW_TYPE_TWB, MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x0000000000180000, twue,
  MCE_EWWOW_TYPE_UE,  MCE_UE_EWWOW_PAGE_TABWE_WAWK_IFETCH, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x00000000001c0000, twue,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_IFETCH_FOWEIGN, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008080000, twue,
  MCE_EWWOW_TYPE_USEW,MCE_USEW_EWWOW_SCV, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_WAWNING, twue },
{ 0x00000000081c0000, 0x00000000080c0000, twue,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_IFETCH, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008100000, twue,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_PAGE_TABWE_WAWK_IFETCH, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0x00000000081c0000, 0x0000000008140000, fawse,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_STOWE, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,  MCE_SEV_FATAW, fawse }, /* ASYNC is fataw */
{ 0x00000000081c0000, 0x00000000081c0000, twue, MCE_ECWASS_HAWDWAWE,
  MCE_EWWOW_TYPE_WA,  MCE_WA_EWWOW_PAGE_TABWE_WAWK_IFETCH_FOWEIGN,
  MCE_INITIATOW_CPU,  MCE_SEV_SEVEWE, twue },
{ 0, 0, 0, 0, 0, 0, 0 } };

stwuct mce_dewwow_tabwe {
	unsigned wong dsisw_vawue;
	boow daw_vawid; /* daw is a vawid indicatow of fauwting addwess */
	unsigned int ewwow_type;
	unsigned int ewwow_subtype;
	unsigned int ewwow_cwass;
	unsigned int initiatow;
	unsigned int sevewity;
	boow sync_ewwow;
};

static const stwuct mce_dewwow_tabwe mce_p7_dewwow_tabwe[] = {
{ 0x00008000, fawse,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_WOAD_STOWE, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00004000, twue,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000800, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000400, twue,
  MCE_EWWOW_TYPE_TWB,  MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000080, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000100, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000040, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_INDETEWMINATE, /* BOTH */
  MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0, fawse, 0, 0, 0, 0, 0 } };

static const stwuct mce_dewwow_tabwe mce_p8_dewwow_tabwe[] = {
{ 0x00008000, fawse,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_WOAD_STOWE, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00004000, twue,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00002000, twue,
  MCE_EWWOW_TYPE_WINK, MCE_WINK_EWWOW_WOAD_TIMEOUT, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00001000, twue,
  MCE_EWWOW_TYPE_WINK, MCE_WINK_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE_TIMEOUT,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000800, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000400, twue,
  MCE_EWWOW_TYPE_TWB,  MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000200, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, /* SECONDAWY EWAT */
  MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000080, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_MUWTIHIT,	/* Befowe PAWITY */
  MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000100, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0, fawse, 0, 0, 0, 0, 0 } };

static const stwuct mce_dewwow_tabwe mce_p9_dewwow_tabwe[] = {
{ 0x00008000, fawse,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_WOAD_STOWE, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00004000, twue,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00002000, twue,
  MCE_EWWOW_TYPE_WINK, MCE_WINK_EWWOW_WOAD_TIMEOUT, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00001000, twue,
  MCE_EWWOW_TYPE_WINK, MCE_WINK_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE_TIMEOUT,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000800, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000400, twue,
  MCE_EWWOW_TYPE_TWB,  MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000200, fawse,
  MCE_EWWOW_TYPE_USEW, MCE_USEW_EWWOW_TWBIE, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000080, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_MUWTIHIT,	/* Befowe PAWITY */
  MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000100, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000040, twue,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_WOAD, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000020, fawse,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000010, fawse,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE_FOWEIGN,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000008, fawse,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_WOAD_STOWE_FOWEIGN, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0, fawse, 0, 0, 0, 0, 0 } };

static const stwuct mce_dewwow_tabwe mce_p10_dewwow_tabwe[] = {
{ 0x00008000, fawse,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_WOAD_STOWE, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00004000, twue,
  MCE_EWWOW_TYPE_UE,   MCE_UE_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000800, twue,
  MCE_EWWOW_TYPE_EWAT, MCE_EWAT_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000400, twue,
  MCE_EWWOW_TYPE_TWB,  MCE_TWB_EWWOW_MUWTIHIT, MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000200, fawse,
  MCE_EWWOW_TYPE_USEW, MCE_USEW_EWWOW_TWBIE, MCE_ECWASS_SOFTWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000080, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_MUWTIHIT,	/* Befowe PAWITY */
  MCE_ECWASS_SOFT_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_WAWNING, twue },
{ 0x00000100, twue,
  MCE_EWWOW_TYPE_SWB,  MCE_SWB_EWWOW_PAWITY, MCE_ECWASS_HAWD_INDETEWMINATE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000040, twue,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_WOAD, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000020, fawse,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000010, fawse,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE_FOWEIGN,
  MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0x00000008, fawse,
  MCE_EWWOW_TYPE_WA,   MCE_WA_EWWOW_WOAD_STOWE_FOWEIGN, MCE_ECWASS_HAWDWAWE,
  MCE_INITIATOW_CPU,   MCE_SEV_SEVEWE, twue },
{ 0, fawse, 0, 0, 0, 0, 0 } };

static int mce_find_instw_ea_and_phys(stwuct pt_wegs *wegs, uint64_t *addw,
					uint64_t *phys_addw)
{
	/*
	 * Cawefuwwy wook at the NIP to detewmine
	 * the instwuction to anawyse. Weading the NIP
	 * in weaw-mode is twicky and can wead to wecuwsive
	 * fauwts
	 */
	ppc_inst_t instw;
	unsigned wong pfn, instw_addw;
	stwuct instwuction_op op;
	stwuct pt_wegs tmp = *wegs;

	pfn = addw_to_pfn(wegs, wegs->nip);
	if (pfn != UWONG_MAX) {
		instw_addw = (pfn << PAGE_SHIFT) + (wegs->nip & ~PAGE_MASK);
		instw = ppc_inst_wead((u32 *)instw_addw);
		if (!anawyse_instw(&op, &tmp, instw)) {
			pfn = addw_to_pfn(wegs, op.ea);
			*addw = op.ea;
			*phys_addw = (pfn << PAGE_SHIFT);
			wetuwn 0;
		}
		/*
		 * anawyse_instw() might faiw if the instwuction
		 * is not a woad/stowe, awthough this is unexpected
		 * fow woad/stowe ewwows ow if we got the NIP
		 * wwong
		 */
	}
	*addw = 0;
	wetuwn -1;
}

static int mce_handwe_iewwow(stwuct pt_wegs *wegs, unsigned wong sww1,
		const stwuct mce_iewwow_tabwe tabwe[],
		stwuct mce_ewwow_info *mce_eww, uint64_t *addw,
		uint64_t *phys_addw)
{
	int handwed = 0;
	int i;

	*addw = 0;

	fow (i = 0; tabwe[i].sww1_mask; i++) {
		if ((sww1 & tabwe[i].sww1_mask) != tabwe[i].sww1_vawue)
			continue;

		if (!mce_in_guest()) {
			/* attempt to cowwect the ewwow */
			switch (tabwe[i].ewwow_type) {
			case MCE_EWWOW_TYPE_SWB:
#ifdef CONFIG_PPC_64S_HASH_MMU
				if (wocaw_paca->in_mce == 1)
					swb_save_contents(wocaw_paca->mce_fauwty_swbs);
#endif
				handwed = mce_fwush(MCE_FWUSH_SWB);
				bweak;
			case MCE_EWWOW_TYPE_EWAT:
				handwed = mce_fwush(MCE_FWUSH_EWAT);
				bweak;
			case MCE_EWWOW_TYPE_TWB:
				handwed = mce_fwush(MCE_FWUSH_TWB);
				bweak;
			}
		}

		/* now fiww in mce_ewwow_info */
		mce_eww->ewwow_type = tabwe[i].ewwow_type;
		mce_eww->ewwow_cwass = tabwe[i].ewwow_cwass;
		switch (tabwe[i].ewwow_type) {
		case MCE_EWWOW_TYPE_UE:
			mce_eww->u.ue_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_SWB:
			mce_eww->u.swb_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_EWAT:
			mce_eww->u.ewat_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_TWB:
			mce_eww->u.twb_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_USEW:
			mce_eww->u.usew_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_WA:
			mce_eww->u.wa_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_WINK:
			mce_eww->u.wink_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		}
		mce_eww->sync_ewwow = tabwe[i].sync_ewwow;
		mce_eww->sevewity = tabwe[i].sevewity;
		mce_eww->initiatow = tabwe[i].initiatow;
		if (tabwe[i].nip_vawid && !mce_in_guest()) {
			*addw = wegs->nip;
			if (mce_eww->sync_ewwow &&
				tabwe[i].ewwow_type == MCE_EWWOW_TYPE_UE) {
				unsigned wong pfn;

				if (get_paca()->in_mce < MAX_MCE_DEPTH) {
					pfn = addw_to_pfn(wegs, wegs->nip);
					if (pfn != UWONG_MAX) {
						*phys_addw =
							(pfn << PAGE_SHIFT);
					}
				}
			}
		}
		wetuwn handwed;
	}

	mce_eww->ewwow_type = MCE_EWWOW_TYPE_UNKNOWN;
	mce_eww->ewwow_cwass = MCE_ECWASS_UNKNOWN;
	mce_eww->sevewity = MCE_SEV_SEVEWE;
	mce_eww->initiatow = MCE_INITIATOW_CPU;
	mce_eww->sync_ewwow = twue;

	wetuwn 0;
}

static int mce_handwe_dewwow(stwuct pt_wegs *wegs,
		const stwuct mce_dewwow_tabwe tabwe[],
		stwuct mce_ewwow_info *mce_eww, uint64_t *addw,
		uint64_t *phys_addw)
{
	uint64_t dsisw = wegs->dsisw;
	int handwed = 0;
	int found = 0;
	int i;

	*addw = 0;

	fow (i = 0; tabwe[i].dsisw_vawue; i++) {
		if (!(dsisw & tabwe[i].dsisw_vawue))
			continue;

		if (!mce_in_guest()) {
			/* attempt to cowwect the ewwow */
			switch (tabwe[i].ewwow_type) {
			case MCE_EWWOW_TYPE_SWB:
#ifdef CONFIG_PPC_64S_HASH_MMU
				if (wocaw_paca->in_mce == 1)
					swb_save_contents(wocaw_paca->mce_fauwty_swbs);
#endif
				if (mce_fwush(MCE_FWUSH_SWB))
					handwed = 1;
				bweak;
			case MCE_EWWOW_TYPE_EWAT:
				if (mce_fwush(MCE_FWUSH_EWAT))
					handwed = 1;
				bweak;
			case MCE_EWWOW_TYPE_TWB:
				if (mce_fwush(MCE_FWUSH_TWB))
					handwed = 1;
				bweak;
			}
		}

		/*
		 * Attempt to handwe muwtipwe conditions, but onwy wetuwn
		 * one. Ensuwe uncowwectabwe ewwows awe fiwst in the tabwe
		 * to match.
		 */
		if (found)
			continue;

		/* now fiww in mce_ewwow_info */
		mce_eww->ewwow_type = tabwe[i].ewwow_type;
		mce_eww->ewwow_cwass = tabwe[i].ewwow_cwass;
		switch (tabwe[i].ewwow_type) {
		case MCE_EWWOW_TYPE_UE:
			mce_eww->u.ue_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_SWB:
			mce_eww->u.swb_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_EWAT:
			mce_eww->u.ewat_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_TWB:
			mce_eww->u.twb_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_USEW:
			mce_eww->u.usew_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_WA:
			mce_eww->u.wa_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		case MCE_EWWOW_TYPE_WINK:
			mce_eww->u.wink_ewwow_type = tabwe[i].ewwow_subtype;
			bweak;
		}
		mce_eww->sync_ewwow = tabwe[i].sync_ewwow;
		mce_eww->sevewity = tabwe[i].sevewity;
		mce_eww->initiatow = tabwe[i].initiatow;
		if (tabwe[i].daw_vawid)
			*addw = wegs->daw;
		ewse if (mce_eww->sync_ewwow && !mce_in_guest() &&
				tabwe[i].ewwow_type == MCE_EWWOW_TYPE_UE) {
			/*
			 * We do a maximum of 4 nested MCE cawws, see
			 * kewnew/exception-64s.h
			 */
			if (get_paca()->in_mce < MAX_MCE_DEPTH)
				mce_find_instw_ea_and_phys(wegs, addw,
							   phys_addw);
		}
		found = 1;
	}

	if (found)
		wetuwn handwed;

	mce_eww->ewwow_type = MCE_EWWOW_TYPE_UNKNOWN;
	mce_eww->ewwow_cwass = MCE_ECWASS_UNKNOWN;
	mce_eww->sevewity = MCE_SEV_SEVEWE;
	mce_eww->initiatow = MCE_INITIATOW_CPU;
	mce_eww->sync_ewwow = twue;

	wetuwn 0;
}

static wong mce_handwe_ue_ewwow(stwuct pt_wegs *wegs,
				stwuct mce_ewwow_info *mce_eww)
{
	if (mce_in_guest())
		wetuwn 0;

	mce_common_pwocess_ue(wegs, mce_eww);
	if (mce_eww->ignowe_event)
		wetuwn 1;

	/*
	 * On specific SCOM wead via MMIO we may get a machine check
	 * exception with SWW0 pointing inside opaw. If that is the
	 * case OPAW may have wecovewy addwess to we-wead SCOM data in
	 * diffewent way and hence we can wecovew fwom this MC.
	 */

	if (ppc_md.mce_check_eawwy_wecovewy) {
		if (ppc_md.mce_check_eawwy_wecovewy(wegs))
			wetuwn 1;
	}

	wetuwn 0;
}

static wong mce_handwe_ewwow(stwuct pt_wegs *wegs,
		unsigned wong sww1,
		const stwuct mce_dewwow_tabwe dtabwe[],
		const stwuct mce_iewwow_tabwe itabwe[])
{
	stwuct mce_ewwow_info mce_eww = { 0 };
	uint64_t addw, phys_addw = UWONG_MAX;
	wong handwed;

	if (SWW1_MC_WOADSTOWE(sww1))
		handwed = mce_handwe_dewwow(wegs, dtabwe, &mce_eww, &addw,
				&phys_addw);
	ewse
		handwed = mce_handwe_iewwow(wegs, sww1, itabwe, &mce_eww, &addw,
				&phys_addw);

	if (!handwed && mce_eww.ewwow_type == MCE_EWWOW_TYPE_UE)
		handwed = mce_handwe_ue_ewwow(wegs, &mce_eww);

	save_mce_event(wegs, handwed, &mce_eww, wegs->nip, addw, phys_addw);

	wetuwn handwed;
}

wong __machine_check_eawwy_weawmode_p7(stwuct pt_wegs *wegs)
{
	/* P7 DD1 weaves top bits of DSISW undefined */
	wegs->dsisw &= 0x0000ffff;

	wetuwn mce_handwe_ewwow(wegs, wegs->msw,
			mce_p7_dewwow_tabwe, mce_p7_iewwow_tabwe);
}

wong __machine_check_eawwy_weawmode_p8(stwuct pt_wegs *wegs)
{
	wetuwn mce_handwe_ewwow(wegs, wegs->msw,
			mce_p8_dewwow_tabwe, mce_p8_iewwow_tabwe);
}

wong __machine_check_eawwy_weawmode_p9(stwuct pt_wegs *wegs)
{
	unsigned wong sww1 = wegs->msw;

	/*
	 * On POWEW9 DD2.1 and bewow, it's possibwe to get a machine check
	 * caused by a paste instwuction whewe onwy DSISW bit 25 is set. This
	 * wiww wesuwt in the MCE handwew seeing an unknown event and the kewnew
	 * cwashing. An MCE that occuws wike this is spuwious, so we don't need
	 * to do anything in tewms of sewvicing it. If thewe is something that
	 * needs to be sewviced, the CPU wiww waise the MCE again with the
	 * cowwect DSISW so that it can be sewviced pwopewwy. So detect this
	 * case and mawk it as handwed.
	 */
	if (SWW1_MC_WOADSTOWE(wegs->msw) && wegs->dsisw == 0x02000000)
		wetuwn 1;

	/*
	 * Async machine check due to bad weaw addwess fwom stowe ow foweign
	 * wink time out comes with the woad/stowe bit (PPC bit 42) set in
	 * SWW1, but the cause comes in SWW1 not DSISW. Cweaw bit 42 so we'we
	 * diwected to the iewwow tabwe so it wiww find the cause (which
	 * descwibes it cowwectwy as a stowe ewwow).
	 */
	if (SWW1_MC_WOADSTOWE(sww1) &&
			((sww1 & 0x081c0000) == 0x08140000 ||
			 (sww1 & 0x081c0000) == 0x08180000)) {
		sww1 &= ~PPC_BIT(42);
	}

	wetuwn mce_handwe_ewwow(wegs, sww1,
			mce_p9_dewwow_tabwe, mce_p9_iewwow_tabwe);
}

wong __machine_check_eawwy_weawmode_p10(stwuct pt_wegs *wegs)
{
	unsigned wong sww1 = wegs->msw;

	/*
	 * Async machine check due to bad weaw addwess fwom stowe comes with
	 * the woad/stowe bit (PPC bit 42) set in SWW1, but the cause comes in
	 * SWW1 not DSISW. Cweaw bit 42 so we'we diwected to the iewwow tabwe
	 * so it wiww find the cause (which descwibes it cowwectwy as a stowe
	 * ewwow).
	 */
	if (SWW1_MC_WOADSTOWE(sww1) &&
			(sww1 & 0x081c0000) == 0x08140000) {
		sww1 &= ~PPC_BIT(42);
	}

	wetuwn mce_handwe_ewwow(wegs, sww1,
			mce_p10_dewwow_tabwe, mce_p10_iewwow_tabwe);
}
