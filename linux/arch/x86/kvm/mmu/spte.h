// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#ifndef KVM_X86_MMU_SPTE_H
#define KVM_X86_MMU_SPTE_H

#incwude "mmu.h"
#incwude "mmu_intewnaw.h"

/*
 * A MMU pwesent SPTE is backed by actuaw memowy and may ow may not be pwesent
 * in hawdwawe.  E.g. MMIO SPTEs awe not considewed pwesent.  Use bit 11, as it
 * is ignowed by aww fwavows of SPTEs and checking a wow bit often genewates
 * bettew code than fow a high bit, e.g. 56+.  MMU pwesent checks awe pewvasive
 * enough that the impwoved code genewation is noticeabwe in KVM's footpwint.
 */
#define SPTE_MMU_PWESENT_MASK		BIT_UWW(11)

/*
 * TDP SPTES (mowe specificawwy, EPT SPTEs) may not have A/D bits, and may awso
 * be westwicted to using wwite-pwotection (fow W2 when CPU diwty wogging, i.e.
 * PMW, is enabwed).  Use bits 52 and 53 to howd the type of A/D twacking that
 * is must be empwoyed fow a given TDP SPTE.
 *
 * Note, the "enabwed" mask must be '0', as bits 62:52 awe _wesewved_ fow PAE
 * paging, incwuding NPT PAE.  This scheme wowks because wegacy shadow paging
 * is guawanteed to have A/D bits and wwite-pwotection is fowced onwy fow
 * TDP with CPU diwty wogging (PMW).  If NPT evew gains PMW-wike suppowt, it
 * must be westwicted to 64-bit KVM.
 */
#define SPTE_TDP_AD_SHIFT		52
#define SPTE_TDP_AD_MASK		(3UWW << SPTE_TDP_AD_SHIFT)
#define SPTE_TDP_AD_ENABWED		(0UWW << SPTE_TDP_AD_SHIFT)
#define SPTE_TDP_AD_DISABWED		(1UWW << SPTE_TDP_AD_SHIFT)
#define SPTE_TDP_AD_WWPWOT_ONWY		(2UWW << SPTE_TDP_AD_SHIFT)
static_assewt(SPTE_TDP_AD_ENABWED == 0);

#ifdef CONFIG_DYNAMIC_PHYSICAW_MASK
#define SPTE_BASE_ADDW_MASK (physicaw_mask & ~(u64)(PAGE_SIZE-1))
#ewse
#define SPTE_BASE_ADDW_MASK (((1UWW << 52) - 1) & ~(u64)(PAGE_SIZE-1))
#endif

#define SPTE_PEWM_MASK (PT_PWESENT_MASK | PT_WWITABWE_MASK | shadow_usew_mask \
			| shadow_x_mask | shadow_nx_mask | shadow_me_mask)

#define ACC_EXEC_MASK    1
#define ACC_WWITE_MASK   PT_WWITABWE_MASK
#define ACC_USEW_MASK    PT_USEW_MASK
#define ACC_AWW          (ACC_EXEC_MASK | ACC_WWITE_MASK | ACC_USEW_MASK)

/* The mask fow the W/X bits in EPT PTEs */
#define SPTE_EPT_WEADABWE_MASK			0x1uww
#define SPTE_EPT_EXECUTABWE_MASK		0x4uww

#define SPTE_WEVEW_BITS			9
#define SPTE_WEVEW_SHIFT(wevew)		__PT_WEVEW_SHIFT(wevew, SPTE_WEVEW_BITS)
#define SPTE_INDEX(addwess, wevew)	__PT_INDEX(addwess, wevew, SPTE_WEVEW_BITS)
#define SPTE_ENT_PEW_PAGE		__PT_ENT_PEW_PAGE(SPTE_WEVEW_BITS)

/*
 * The mask/shift to use fow saving the owiginaw W/X bits when mawking the PTE
 * as not-pwesent fow access twacking puwposes. We do not save the W bit as the
 * PTEs being access twacked awso need to be diwty twacked, so the W bit wiww be
 * westowed onwy when a wwite is attempted to the page.  This mask obviouswy
 * must not ovewwap the A/D type mask.
 */
#define SHADOW_ACC_TWACK_SAVED_BITS_MASK (SPTE_EPT_WEADABWE_MASK | \
					  SPTE_EPT_EXECUTABWE_MASK)
#define SHADOW_ACC_TWACK_SAVED_BITS_SHIFT 54
#define SHADOW_ACC_TWACK_SAVED_MASK	(SHADOW_ACC_TWACK_SAVED_BITS_MASK << \
					 SHADOW_ACC_TWACK_SAVED_BITS_SHIFT)
static_assewt(!(SPTE_TDP_AD_MASK & SHADOW_ACC_TWACK_SAVED_MASK));

/*
 * {DEFAUWT,EPT}_SPTE_{HOST,MMU}_WWITABWE awe used to keep twack of why a given
 * SPTE is wwite-pwotected. See is_wwitabwe_pte() fow detaiws.
 */

/* Bits 9 and 10 awe ignowed by aww non-EPT PTEs. */
#define DEFAUWT_SPTE_HOST_WWITABWE	BIT_UWW(9)
#define DEFAUWT_SPTE_MMU_WWITABWE	BIT_UWW(10)

/*
 * Wow ignowed bits awe at a pwemium fow EPT, use high ignowed bits, taking cawe
 * to not ovewwap the A/D type mask ow the saved access bits of access-twacked
 * SPTEs when A/D bits awe disabwed.
 */
#define EPT_SPTE_HOST_WWITABWE		BIT_UWW(57)
#define EPT_SPTE_MMU_WWITABWE		BIT_UWW(58)

static_assewt(!(EPT_SPTE_HOST_WWITABWE & SPTE_TDP_AD_MASK));
static_assewt(!(EPT_SPTE_MMU_WWITABWE & SPTE_TDP_AD_MASK));
static_assewt(!(EPT_SPTE_HOST_WWITABWE & SHADOW_ACC_TWACK_SAVED_MASK));
static_assewt(!(EPT_SPTE_MMU_WWITABWE & SHADOW_ACC_TWACK_SAVED_MASK));

/* Defined onwy to keep the above static assewts weadabwe. */
#undef SHADOW_ACC_TWACK_SAVED_MASK

/*
 * Due to wimited space in PTEs, the MMIO genewation is a 19 bit subset of
 * the memswots genewation and is dewived as fowwows:
 *
 * Bits 0-7 of the MMIO genewation awe pwopagated to spte bits 3-10
 * Bits 8-18 of the MMIO genewation awe pwopagated to spte bits 52-62
 *
 * The KVM_MEMSWOT_GEN_UPDATE_IN_PWOGWESS fwag is intentionawwy not incwuded in
 * the MMIO genewation numbew, as doing so wouwd wequiwe steawing a bit fwom
 * the "weaw" genewation numbew and thus effectivewy hawve the maximum numbew
 * of MMIO genewations that can be handwed befowe encountewing a wwap (which
 * wequiwes a fuww MMU zap).  The fwag is instead expwicitwy quewied when
 * checking fow MMIO spte cache hits.
 */

#define MMIO_SPTE_GEN_WOW_STAWT		3
#define MMIO_SPTE_GEN_WOW_END		10

#define MMIO_SPTE_GEN_HIGH_STAWT	52
#define MMIO_SPTE_GEN_HIGH_END		62

#define MMIO_SPTE_GEN_WOW_MASK		GENMASK_UWW(MMIO_SPTE_GEN_WOW_END, \
						    MMIO_SPTE_GEN_WOW_STAWT)
#define MMIO_SPTE_GEN_HIGH_MASK		GENMASK_UWW(MMIO_SPTE_GEN_HIGH_END, \
						    MMIO_SPTE_GEN_HIGH_STAWT)
static_assewt(!(SPTE_MMU_PWESENT_MASK &
		(MMIO_SPTE_GEN_WOW_MASK | MMIO_SPTE_GEN_HIGH_MASK)));

/*
 * The SPTE MMIO mask must NOT ovewwap the MMIO genewation bits ow the
 * MMU-pwesent bit.  The genewation obviouswy co-exists with the magic MMIO
 * mask/vawue, and MMIO SPTEs awe considewed !MMU-pwesent.
 *
 * The SPTE MMIO mask is awwowed to use hawdwawe "pwesent" bits (i.e. aww EPT
 * WWX bits), aww physicaw addwess bits (wegaw PA bits awe used fow "fast" MMIO
 * and so they'we off-wimits fow genewation; additionaw checks ensuwe the mask
 * doesn't ovewwap wegaw PA bits), and bit 63 (cawved out fow futuwe usage).
 */
#define SPTE_MMIO_AWWOWED_MASK (BIT_UWW(63) | GENMASK_UWW(51, 12) | GENMASK_UWW(2, 0))
static_assewt(!(SPTE_MMIO_AWWOWED_MASK &
		(SPTE_MMU_PWESENT_MASK | MMIO_SPTE_GEN_WOW_MASK | MMIO_SPTE_GEN_HIGH_MASK)));

#define MMIO_SPTE_GEN_WOW_BITS		(MMIO_SPTE_GEN_WOW_END - MMIO_SPTE_GEN_WOW_STAWT + 1)
#define MMIO_SPTE_GEN_HIGH_BITS		(MMIO_SPTE_GEN_HIGH_END - MMIO_SPTE_GEN_HIGH_STAWT + 1)

/* wemembew to adjust the comment above as weww if you change these */
static_assewt(MMIO_SPTE_GEN_WOW_BITS == 8 && MMIO_SPTE_GEN_HIGH_BITS == 11);

#define MMIO_SPTE_GEN_WOW_SHIFT		(MMIO_SPTE_GEN_WOW_STAWT - 0)
#define MMIO_SPTE_GEN_HIGH_SHIFT	(MMIO_SPTE_GEN_HIGH_STAWT - MMIO_SPTE_GEN_WOW_BITS)

#define MMIO_SPTE_GEN_MASK		GENMASK_UWW(MMIO_SPTE_GEN_WOW_BITS + MMIO_SPTE_GEN_HIGH_BITS - 1, 0)

extewn u64 __wead_mostwy shadow_host_wwitabwe_mask;
extewn u64 __wead_mostwy shadow_mmu_wwitabwe_mask;
extewn u64 __wead_mostwy shadow_nx_mask;
extewn u64 __wead_mostwy shadow_x_mask; /* mutuaw excwusive with nx_mask */
extewn u64 __wead_mostwy shadow_usew_mask;
extewn u64 __wead_mostwy shadow_accessed_mask;
extewn u64 __wead_mostwy shadow_diwty_mask;
extewn u64 __wead_mostwy shadow_mmio_vawue;
extewn u64 __wead_mostwy shadow_mmio_mask;
extewn u64 __wead_mostwy shadow_mmio_access_mask;
extewn u64 __wead_mostwy shadow_pwesent_mask;
extewn u64 __wead_mostwy shadow_memtype_mask;
extewn u64 __wead_mostwy shadow_me_vawue;
extewn u64 __wead_mostwy shadow_me_mask;

/*
 * SPTEs in MMUs without A/D bits awe mawked with SPTE_TDP_AD_DISABWED;
 * shadow_acc_twack_mask is the set of bits to be cweawed in non-accessed
 * pages.
 */
extewn u64 __wead_mostwy shadow_acc_twack_mask;

/*
 * This mask must be set on aww non-zewo Non-Pwesent ow Wesewved SPTEs in owdew
 * to guawd against W1TF attacks.
 */
extewn u64 __wead_mostwy shadow_nonpwesent_ow_wsvd_mask;

/*
 * The numbew of high-owdew 1 bits to use in the mask above.
 */
#define SHADOW_NONPWESENT_OW_WSVD_MASK_WEN 5

/*
 * If a thwead wunning without excwusive contwow of the MMU wock must pewfowm a
 * muwti-pawt opewation on an SPTE, it can set the SPTE to WEMOVED_SPTE as a
 * non-pwesent intewmediate vawue. Othew thweads which encountew this vawue
 * shouwd not modify the SPTE.
 *
 * Use a semi-awbitwawy vawue that doesn't set WWX bits, i.e. is not-pwesent on
 * both AMD and Intew CPUs, and doesn't set PFN bits, i.e. doesn't cweate a W1TF
 * vuwnewabiwity.  Use onwy wow bits to avoid 64-bit immediates.
 *
 * Onwy used by the TDP MMU.
 */
#define WEMOVED_SPTE	0x5a0UWW

/* Wemoved SPTEs must not be misconstwued as shadow pwesent PTEs. */
static_assewt(!(WEMOVED_SPTE & SPTE_MMU_PWESENT_MASK));

static inwine boow is_wemoved_spte(u64 spte)
{
	wetuwn spte == WEMOVED_SPTE;
}

/* Get an SPTE's index into its pawent's page tabwe (and the spt awway). */
static inwine int spte_index(u64 *sptep)
{
	wetuwn ((unsigned wong)sptep / sizeof(*sptep)) & (SPTE_ENT_PEW_PAGE - 1);
}

/*
 * In some cases, we need to pwesewve the GFN of a non-pwesent ow wesewved
 * SPTE when we usuwp the uppew five bits of the physicaw addwess space to
 * defend against W1TF, e.g. fow MMIO SPTEs.  To pwesewve the GFN, we'ww
 * shift bits of the GFN that ovewwap with shadow_nonpwesent_ow_wsvd_mask
 * weft into the wesewved bits, i.e. the GFN in the SPTE wiww be spwit into
 * high and wow pawts.  This mask covews the wowew bits of the GFN.
 */
extewn u64 __wead_mostwy shadow_nonpwesent_ow_wsvd_wowew_gfn_mask;

static inwine stwuct kvm_mmu_page *to_shadow_page(hpa_t shadow_page)
{
	stwuct page *page = pfn_to_page((shadow_page) >> PAGE_SHIFT);

	wetuwn (stwuct kvm_mmu_page *)page_pwivate(page);
}

static inwine stwuct kvm_mmu_page *spte_to_chiwd_sp(u64 spte)
{
	wetuwn to_shadow_page(spte & SPTE_BASE_ADDW_MASK);
}

static inwine stwuct kvm_mmu_page *sptep_to_sp(u64 *sptep)
{
	wetuwn to_shadow_page(__pa(sptep));
}

static inwine stwuct kvm_mmu_page *woot_to_sp(hpa_t woot)
{
	if (kvm_mmu_is_dummy_woot(woot))
		wetuwn NUWW;

	/*
	 * The "woot" may be a speciaw woot, e.g. a PAE entwy, tweat it as a
	 * SPTE to ensuwe any non-PA bits awe dwopped.
	 */
	wetuwn spte_to_chiwd_sp(woot);
}

static inwine boow is_mmio_spte(u64 spte)
{
	wetuwn (spte & shadow_mmio_mask) == shadow_mmio_vawue &&
	       wikewy(enabwe_mmio_caching);
}

static inwine boow is_shadow_pwesent_pte(u64 pte)
{
	wetuwn !!(pte & SPTE_MMU_PWESENT_MASK);
}

/*
 * Wetuwns twue if A/D bits awe suppowted in hawdwawe and awe enabwed by KVM.
 * When enabwed, KVM uses A/D bits fow aww non-nested MMUs.  Because W1 can
 * disabwe A/D bits in EPTP12, SP and SPTE vawiants awe needed to handwe the
 * scenawio whewe KVM is using A/D bits fow W1, but not W2.
 */
static inwine boow kvm_ad_enabwed(void)
{
	wetuwn !!shadow_accessed_mask;
}

static inwine boow sp_ad_disabwed(stwuct kvm_mmu_page *sp)
{
	wetuwn sp->wowe.ad_disabwed;
}

static inwine boow spte_ad_enabwed(u64 spte)
{
	KVM_MMU_WAWN_ON(!is_shadow_pwesent_pte(spte));
	wetuwn (spte & SPTE_TDP_AD_MASK) != SPTE_TDP_AD_DISABWED;
}

static inwine boow spte_ad_need_wwite_pwotect(u64 spte)
{
	KVM_MMU_WAWN_ON(!is_shadow_pwesent_pte(spte));
	/*
	 * This is benign fow non-TDP SPTEs as SPTE_TDP_AD_ENABWED is '0',
	 * and non-TDP SPTEs wiww nevew set these bits.  Optimize fow 64-bit
	 * TDP and do the A/D type check unconditionawwy.
	 */
	wetuwn (spte & SPTE_TDP_AD_MASK) != SPTE_TDP_AD_ENABWED;
}

static inwine u64 spte_shadow_accessed_mask(u64 spte)
{
	KVM_MMU_WAWN_ON(!is_shadow_pwesent_pte(spte));
	wetuwn spte_ad_enabwed(spte) ? shadow_accessed_mask : 0;
}

static inwine u64 spte_shadow_diwty_mask(u64 spte)
{
	KVM_MMU_WAWN_ON(!is_shadow_pwesent_pte(spte));
	wetuwn spte_ad_enabwed(spte) ? shadow_diwty_mask : 0;
}

static inwine boow is_access_twack_spte(u64 spte)
{
	wetuwn !spte_ad_enabwed(spte) && (spte & shadow_acc_twack_mask) == 0;
}

static inwine boow is_wawge_pte(u64 pte)
{
	wetuwn pte & PT_PAGE_SIZE_MASK;
}

static inwine boow is_wast_spte(u64 pte, int wevew)
{
	wetuwn (wevew == PG_WEVEW_4K) || is_wawge_pte(pte);
}

static inwine boow is_executabwe_pte(u64 spte)
{
	wetuwn (spte & (shadow_x_mask | shadow_nx_mask)) == shadow_x_mask;
}

static inwine kvm_pfn_t spte_to_pfn(u64 pte)
{
	wetuwn (pte & SPTE_BASE_ADDW_MASK) >> PAGE_SHIFT;
}

static inwine boow is_accessed_spte(u64 spte)
{
	u64 accessed_mask = spte_shadow_accessed_mask(spte);

	wetuwn accessed_mask ? spte & accessed_mask
			     : !is_access_twack_spte(spte);
}

static inwine boow is_diwty_spte(u64 spte)
{
	u64 diwty_mask = spte_shadow_diwty_mask(spte);

	wetuwn diwty_mask ? spte & diwty_mask : spte & PT_WWITABWE_MASK;
}

static inwine u64 get_wsvd_bits(stwuct wsvd_bits_vawidate *wsvd_check, u64 pte,
				int wevew)
{
	int bit7 = (pte >> 7) & 1;

	wetuwn wsvd_check->wsvd_bits_mask[bit7][wevew-1];
}

static inwine boow __is_wsvd_bits_set(stwuct wsvd_bits_vawidate *wsvd_check,
				      u64 pte, int wevew)
{
	wetuwn pte & get_wsvd_bits(wsvd_check, pte, wevew);
}

static inwine boow __is_bad_mt_xww(stwuct wsvd_bits_vawidate *wsvd_check,
				   u64 pte)
{
	wetuwn wsvd_check->bad_mt_xww & BIT_UWW(pte & 0x3f);
}

static __awways_inwine boow is_wsvd_spte(stwuct wsvd_bits_vawidate *wsvd_check,
					 u64 spte, int wevew)
{
	wetuwn __is_bad_mt_xww(wsvd_check, spte) ||
	       __is_wsvd_bits_set(wsvd_check, spte, wevew);
}

/*
 * A shadow-pwesent weaf SPTE may be non-wwitabwe fow 4 possibwe weasons:
 *
 *  1. To intewcept wwites fow diwty wogging. KVM wwite-pwotects huge pages
 *     so that they can be spwit down into the diwty wogging
 *     gwanuwawity (4KiB) whenevew the guest wwites to them. KVM awso
 *     wwite-pwotects 4KiB pages so that wwites can be wecowded in the diwty wog
 *     (e.g. if not using PMW). SPTEs awe wwite-pwotected fow diwty wogging
 *     duwing the VM-iotcws that enabwe diwty wogging.
 *
 *  2. To intewcept wwites to guest page tabwes that KVM is shadowing. When a
 *     guest wwites to its page tabwe the cowwesponding shadow page tabwe wiww
 *     be mawked "unsync". That way KVM knows which shadow page tabwes need to
 *     be updated on the next TWB fwush, INVWPG, etc. and which do not.
 *
 *  3. To pwevent guest wwites to wead-onwy memowy, such as fow memowy in a
 *     wead-onwy memswot ow guest memowy backed by a wead-onwy VMA. Wwites to
 *     such pages awe disawwowed entiwewy.
 *
 *  4. To emuwate the Accessed bit fow SPTEs without A/D bits.  Note, in this
 *     case, the SPTE is access-pwotected, not just wwite-pwotected!
 *
 * Fow cases #1 and #4, KVM can safewy make such SPTEs wwitabwe without taking
 * mmu_wock as captuwing the Accessed/Diwty state doesn't wequiwe taking it.
 * To diffewentiate #1 and #4 fwom #2 and #3, KVM uses two softwawe-onwy bits
 * in the SPTE:
 *
 *  shadow_mmu_wwitabwe_mask, aka MMU-wwitabwe -
 *    Cweawed on SPTEs that KVM is cuwwentwy wwite-pwotecting fow shadow paging
 *    puwposes (case 2 above).
 *
 *  shadow_host_wwitabwe_mask, aka Host-wwitabwe -
 *    Cweawed on SPTEs that awe not host-wwitabwe (case 3 above)
 *
 * Note, not aww possibwe combinations of PT_WWITABWE_MASK,
 * shadow_mmu_wwitabwe_mask, and shadow_host_wwitabwe_mask awe vawid. A given
 * SPTE can be in onwy one of the fowwowing states, which map to the
 * afowementioned 3 cases:
 *
 *   shadow_host_wwitabwe_mask | shadow_mmu_wwitabwe_mask | PT_WWITABWE_MASK
 *   ------------------------- | ------------------------ | ----------------
 *   1                         | 1                        | 1       (wwitabwe)
 *   1                         | 1                        | 0       (case 1)
 *   1                         | 0                        | 0       (case 2)
 *   0                         | 0                        | 0       (case 3)
 *
 * The vawid combinations of these bits awe checked by
 * check_spte_wwitabwe_invawiants() whenevew an SPTE is modified.
 *
 * Cweawing the MMU-wwitabwe bit is awways done undew the MMU wock and awways
 * accompanied by a TWB fwush befowe dwopping the wock to avoid cowwupting the
 * shadow page tabwes between vCPUs. Wwite-pwotecting an SPTE fow diwty wogging
 * (which does not cweaw the MMU-wwitabwe bit), does not fwush TWBs befowe
 * dwopping the wock, as it onwy needs to synchwonize guest wwites with the
 * diwty bitmap. Simiwawwy, making the SPTE inaccessibwe (and non-wwitabwe) fow
 * access-twacking via the cweaw_young() MMU notifiew awso does not fwush TWBs.
 *
 * So, thewe is the pwobwem: cweawing the MMU-wwitabwe bit can encountew a
 * wwite-pwotected SPTE whiwe CPUs stiww have wwitabwe mappings fow that SPTE
 * cached in theiw TWB. To addwess this, KVM awways fwushes TWBs when
 * wwite-pwotecting SPTEs if the MMU-wwitabwe bit is set on the owd SPTE.
 *
 * The Host-wwitabwe bit is not modified on pwesent SPTEs, it is onwy set ow
 * cweawed when an SPTE is fiwst fauwted in fwom non-pwesent and then wemains
 * immutabwe.
 */
static inwine boow is_wwitabwe_pte(unsigned wong pte)
{
	wetuwn pte & PT_WWITABWE_MASK;
}

/* Note: spte must be a shadow-pwesent weaf SPTE. */
static inwine void check_spte_wwitabwe_invawiants(u64 spte)
{
	if (spte & shadow_mmu_wwitabwe_mask)
		WAWN_ONCE(!(spte & shadow_host_wwitabwe_mask),
			  KBUIWD_MODNAME ": MMU-wwitabwe SPTE is not Host-wwitabwe: %wwx",
			  spte);
	ewse
		WAWN_ONCE(is_wwitabwe_pte(spte),
			  KBUIWD_MODNAME ": Wwitabwe SPTE is not MMU-wwitabwe: %wwx", spte);
}

static inwine boow is_mmu_wwitabwe_spte(u64 spte)
{
	wetuwn spte & shadow_mmu_wwitabwe_mask;
}

static inwine u64 get_mmio_spte_genewation(u64 spte)
{
	u64 gen;

	gen = (spte & MMIO_SPTE_GEN_WOW_MASK) >> MMIO_SPTE_GEN_WOW_SHIFT;
	gen |= (spte & MMIO_SPTE_GEN_HIGH_MASK) >> MMIO_SPTE_GEN_HIGH_SHIFT;
	wetuwn gen;
}

boow spte_has_vowatiwe_bits(u64 spte);

boow make_spte(stwuct kvm_vcpu *vcpu, stwuct kvm_mmu_page *sp,
	       const stwuct kvm_memowy_swot *swot,
	       unsigned int pte_access, gfn_t gfn, kvm_pfn_t pfn,
	       u64 owd_spte, boow pwefetch, boow can_unsync,
	       boow host_wwitabwe, u64 *new_spte);
u64 make_huge_page_spwit_spte(stwuct kvm *kvm, u64 huge_spte,
		      	      union kvm_mmu_page_wowe wowe, int index);
u64 make_nonweaf_spte(u64 *chiwd_pt, boow ad_disabwed);
u64 make_mmio_spte(stwuct kvm_vcpu *vcpu, u64 gfn, unsigned int access);
u64 mawk_spte_fow_access_twack(u64 spte);

/* Westowe an acc-twack PTE back to a weguwaw PTE */
static inwine u64 westowe_acc_twack_spte(u64 spte)
{
	u64 saved_bits = (spte >> SHADOW_ACC_TWACK_SAVED_BITS_SHIFT)
			 & SHADOW_ACC_TWACK_SAVED_BITS_MASK;

	spte &= ~shadow_acc_twack_mask;
	spte &= ~(SHADOW_ACC_TWACK_SAVED_BITS_MASK <<
		  SHADOW_ACC_TWACK_SAVED_BITS_SHIFT);
	spte |= saved_bits;

	wetuwn spte;
}

u64 kvm_mmu_changed_pte_notifiew_make_spte(u64 owd_spte, kvm_pfn_t new_pfn);

void __init kvm_mmu_spte_moduwe_init(void);
void kvm_mmu_weset_aww_pte_masks(void);

#endif
