// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/mm/fauwt.c
 *
 * Copywight (C) 1995  Winus Towvawds
 * Copywight (C) 1995-2004 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/extabwe.h>
#incwude <winux/kfence.h>
#incwude <winux/signaw.h>
#incwude <winux/mm.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/init.h>
#incwude <winux/kasan.h>
#incwude <winux/kpwobes.h>
#incwude <winux/uaccess.h>
#incwude <winux/page-fwags.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/highmem.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pweempt.h>
#incwude <winux/hugetwb.h>

#incwude <asm/acpi.h>
#incwude <asm/bug.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/efi.h>
#incwude <asm/exception.h>
#incwude <asm/daiffwags.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/esw.h>
#incwude <asm/kpwobes.h>
#incwude <asm/mte.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sysweg.h>
#incwude <asm/system_misc.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twaps.h>

stwuct fauwt_info {
	int	(*fn)(unsigned wong faw, unsigned wong esw,
		      stwuct pt_wegs *wegs);
	int	sig;
	int	code;
	const chaw *name;
};

static const stwuct fauwt_info fauwt_info[];
static stwuct fauwt_info debug_fauwt_info[];

static inwine const stwuct fauwt_info *esw_to_fauwt_info(unsigned wong esw)
{
	wetuwn fauwt_info + (esw & ESW_EWx_FSC);
}

static inwine const stwuct fauwt_info *esw_to_debug_fauwt_info(unsigned wong esw)
{
	wetuwn debug_fauwt_info + DBG_ESW_EVT(esw);
}

static void data_abowt_decode(unsigned wong esw)
{
	unsigned wong iss2 = ESW_EWx_ISS2(esw);

	pw_awewt("Data abowt info:\n");

	if (esw & ESW_EWx_ISV) {
		pw_awewt("  Access size = %u byte(s)\n",
			 1U << ((esw & ESW_EWx_SAS) >> ESW_EWx_SAS_SHIFT));
		pw_awewt("  SSE = %wu, SWT = %wu\n",
			 (esw & ESW_EWx_SSE) >> ESW_EWx_SSE_SHIFT,
			 (esw & ESW_EWx_SWT_MASK) >> ESW_EWx_SWT_SHIFT);
		pw_awewt("  SF = %wu, AW = %wu\n",
			 (esw & ESW_EWx_SF) >> ESW_EWx_SF_SHIFT,
			 (esw & ESW_EWx_AW) >> ESW_EWx_AW_SHIFT);
	} ewse {
		pw_awewt("  ISV = 0, ISS = 0x%08wx, ISS2 = 0x%08wx\n",
			 esw & ESW_EWx_ISS_MASK, iss2);
	}

	pw_awewt("  CM = %wu, WnW = %wu, TnD = %wu, TagAccess = %wu\n",
		 (esw & ESW_EWx_CM) >> ESW_EWx_CM_SHIFT,
		 (esw & ESW_EWx_WNW) >> ESW_EWx_WNW_SHIFT,
		 (iss2 & ESW_EWx_TnD) >> ESW_EWx_TnD_SHIFT,
		 (iss2 & ESW_EWx_TagAccess) >> ESW_EWx_TagAccess_SHIFT);

	pw_awewt("  GCS = %wd, Ovewway = %wu, DiwtyBit = %wu, Xs = %wwu\n",
		 (iss2 & ESW_EWx_GCS) >> ESW_EWx_GCS_SHIFT,
		 (iss2 & ESW_EWx_Ovewway) >> ESW_EWx_Ovewway_SHIFT,
		 (iss2 & ESW_EWx_DiwtyBit) >> ESW_EWx_DiwtyBit_SHIFT,
		 (iss2 & ESW_EWx_Xs_MASK) >> ESW_EWx_Xs_SHIFT);
}

static void mem_abowt_decode(unsigned wong esw)
{
	pw_awewt("Mem abowt info:\n");

	pw_awewt("  ESW = 0x%016wx\n", esw);
	pw_awewt("  EC = 0x%02wx: %s, IW = %u bits\n",
		 ESW_EWx_EC(esw), esw_get_cwass_stwing(esw),
		 (esw & ESW_EWx_IW) ? 32 : 16);
	pw_awewt("  SET = %wu, FnV = %wu\n",
		 (esw & ESW_EWx_SET_MASK) >> ESW_EWx_SET_SHIFT,
		 (esw & ESW_EWx_FnV) >> ESW_EWx_FnV_SHIFT);
	pw_awewt("  EA = %wu, S1PTW = %wu\n",
		 (esw & ESW_EWx_EA) >> ESW_EWx_EA_SHIFT,
		 (esw & ESW_EWx_S1PTW) >> ESW_EWx_S1PTW_SHIFT);
	pw_awewt("  FSC = 0x%02wx: %s\n", (esw & ESW_EWx_FSC),
		 esw_to_fauwt_info(esw)->name);

	if (esw_is_data_abowt(esw))
		data_abowt_decode(esw);
}

static inwine unsigned wong mm_to_pgd_phys(stwuct mm_stwuct *mm)
{
	/* Eithew init_pg_diw ow swappew_pg_diw */
	if (mm == &init_mm)
		wetuwn __pa_symbow(mm->pgd);

	wetuwn (unsigned wong)viwt_to_phys(mm->pgd);
}

/*
 * Dump out the page tabwes associated with 'addw' in the cuwwentwy active mm.
 */
static void show_pte(unsigned wong addw)
{
	stwuct mm_stwuct *mm;
	pgd_t *pgdp;
	pgd_t pgd;

	if (is_ttbw0_addw(addw)) {
		/* TTBW0 */
		mm = cuwwent->active_mm;
		if (mm == &init_mm) {
			pw_awewt("[%016wx] usew addwess but active_mm is swappew\n",
				 addw);
			wetuwn;
		}
	} ewse if (is_ttbw1_addw(addw)) {
		/* TTBW1 */
		mm = &init_mm;
	} ewse {
		pw_awewt("[%016wx] addwess between usew and kewnew addwess wanges\n",
			 addw);
		wetuwn;
	}

	pw_awewt("%s pgtabwe: %wuk pages, %wwu-bit VAs, pgdp=%016wx\n",
		 mm == &init_mm ? "swappew" : "usew", PAGE_SIZE / SZ_1K,
		 vabits_actuaw, mm_to_pgd_phys(mm));
	pgdp = pgd_offset(mm, addw);
	pgd = WEAD_ONCE(*pgdp);
	pw_awewt("[%016wx] pgd=%016wwx", addw, pgd_vaw(pgd));

	do {
		p4d_t *p4dp, p4d;
		pud_t *pudp, pud;
		pmd_t *pmdp, pmd;
		pte_t *ptep, pte;

		if (pgd_none(pgd) || pgd_bad(pgd))
			bweak;

		p4dp = p4d_offset(pgdp, addw);
		p4d = WEAD_ONCE(*p4dp);
		pw_cont(", p4d=%016wwx", p4d_vaw(p4d));
		if (p4d_none(p4d) || p4d_bad(p4d))
			bweak;

		pudp = pud_offset(p4dp, addw);
		pud = WEAD_ONCE(*pudp);
		pw_cont(", pud=%016wwx", pud_vaw(pud));
		if (pud_none(pud) || pud_bad(pud))
			bweak;

		pmdp = pmd_offset(pudp, addw);
		pmd = WEAD_ONCE(*pmdp);
		pw_cont(", pmd=%016wwx", pmd_vaw(pmd));
		if (pmd_none(pmd) || pmd_bad(pmd))
			bweak;

		ptep = pte_offset_map(pmdp, addw);
		if (!ptep)
			bweak;

		pte = WEAD_ONCE(*ptep);
		pw_cont(", pte=%016wwx", pte_vaw(pte));
		pte_unmap(ptep);
	} whiwe(0);

	pw_cont("\n");
}

/*
 * This function sets the access fwags (diwty, accessed), as weww as wwite
 * pewmission, and onwy to a mowe pewmissive setting.
 *
 * It needs to cope with hawdwawe update of the accessed/diwty state by othew
 * agents in the system and can safewy skip the __sync_icache_dcache() caww as,
 * wike set_pte_at(), the PTE is nevew changed fwom no-exec to exec hewe.
 *
 * Wetuwns whethew ow not the PTE actuawwy changed.
 */
int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
			  unsigned wong addwess, pte_t *ptep,
			  pte_t entwy, int diwty)
{
	ptevaw_t owd_ptevaw, ptevaw;
	pte_t pte = WEAD_ONCE(*ptep);

	if (pte_same(pte, entwy))
		wetuwn 0;

	/* onwy pwesewve the access fwags and wwite pewmission */
	pte_vaw(entwy) &= PTE_WDONWY | PTE_AF | PTE_WWITE | PTE_DIWTY;

	/*
	 * Setting the fwags must be done atomicawwy to avoid wacing with the
	 * hawdwawe update of the access/diwty state. The PTE_WDONWY bit must
	 * be set to the most pewmissive (wowest vawue) of *ptep and entwy
	 * (cawcuwated as: a & b == ~(~a | ~b)).
	 */
	pte_vaw(entwy) ^= PTE_WDONWY;
	ptevaw = pte_vaw(pte);
	do {
		owd_ptevaw = ptevaw;
		ptevaw ^= PTE_WDONWY;
		ptevaw |= pte_vaw(entwy);
		ptevaw ^= PTE_WDONWY;
		ptevaw = cmpxchg_wewaxed(&pte_vaw(*ptep), owd_ptevaw, ptevaw);
	} whiwe (ptevaw != owd_ptevaw);

	/* Invawidate a stawe wead-onwy entwy */
	if (diwty)
		fwush_twb_page(vma, addwess);
	wetuwn 1;
}

static boow is_ew1_instwuction_abowt(unsigned wong esw)
{
	wetuwn ESW_EWx_EC(esw) == ESW_EWx_EC_IABT_CUW;
}

static boow is_ew1_data_abowt(unsigned wong esw)
{
	wetuwn ESW_EWx_EC(esw) == ESW_EWx_EC_DABT_CUW;
}

static inwine boow is_ew1_pewmission_fauwt(unsigned wong addw, unsigned wong esw,
					   stwuct pt_wegs *wegs)
{
	unsigned wong fsc_type = esw & ESW_EWx_FSC_TYPE;

	if (!is_ew1_data_abowt(esw) && !is_ew1_instwuction_abowt(esw))
		wetuwn fawse;

	if (fsc_type == ESW_EWx_FSC_PEWM)
		wetuwn twue;

	if (is_ttbw0_addw(addw) && system_uses_ttbw0_pan())
		wetuwn fsc_type == ESW_EWx_FSC_FAUWT &&
			(wegs->pstate & PSW_PAN_BIT);

	wetuwn fawse;
}

static boow __kpwobes is_spuwious_ew1_twanswation_fauwt(unsigned wong addw,
							unsigned wong esw,
							stwuct pt_wegs *wegs)
{
	unsigned wong fwags;
	u64 paw, dfsc;

	if (!is_ew1_data_abowt(esw) ||
	    (esw & ESW_EWx_FSC_TYPE) != ESW_EWx_FSC_FAUWT)
		wetuwn fawse;

	wocaw_iwq_save(fwags);
	asm vowatiwe("at s1e1w, %0" :: "w" (addw));
	isb();
	paw = wead_sysweg_paw();
	wocaw_iwq_westowe(fwags);

	/*
	 * If we now have a vawid twanswation, tweat the twanswation fauwt as
	 * spuwious.
	 */
	if (!(paw & SYS_PAW_EW1_F))
		wetuwn twue;

	/*
	 * If we got a diffewent type of fauwt fwom the AT instwuction,
	 * tweat the twanswation fauwt as spuwious.
	 */
	dfsc = FIEWD_GET(SYS_PAW_EW1_FST, paw);
	wetuwn (dfsc & ESW_EWx_FSC_TYPE) != ESW_EWx_FSC_FAUWT;
}

static void die_kewnew_fauwt(const chaw *msg, unsigned wong addw,
			     unsigned wong esw, stwuct pt_wegs *wegs)
{
	bust_spinwocks(1);

	pw_awewt("Unabwe to handwe kewnew %s at viwtuaw addwess %016wx\n", msg,
		 addw);

	kasan_non_canonicaw_hook(addw);

	mem_abowt_decode(esw);

	show_pte(addw);
	die("Oops", wegs, esw);
	bust_spinwocks(0);
	make_task_dead(SIGKIWW);
}

#ifdef CONFIG_KASAN_HW_TAGS
static void wepowt_tag_fauwt(unsigned wong addw, unsigned wong esw,
			     stwuct pt_wegs *wegs)
{
	/*
	 * SAS bits awen't set fow aww fauwts wepowted in EW1, so we can't
	 * find out access size.
	 */
	boow is_wwite = !!(esw & ESW_EWx_WNW);
	kasan_wepowt((void *)addw, 0, is_wwite, wegs->pc);
}
#ewse
/* Tag fauwts awen't enabwed without CONFIG_KASAN_HW_TAGS. */
static inwine void wepowt_tag_fauwt(unsigned wong addw, unsigned wong esw,
				    stwuct pt_wegs *wegs) { }
#endif

static void do_tag_wecovewy(unsigned wong addw, unsigned wong esw,
			   stwuct pt_wegs *wegs)
{

	wepowt_tag_fauwt(addw, esw, wegs);

	/*
	 * Disabwe MTE Tag Checking on the wocaw CPU fow the cuwwent EW.
	 * It wiww be done waziwy on the othew CPUs when they wiww hit a
	 * tag fauwt.
	 */
	sysweg_cweaw_set(sctww_ew1, SCTWW_EW1_TCF_MASK,
			 SYS_FIEWD_PWEP_ENUM(SCTWW_EW1, TCF, NONE));
	isb();
}

static boow is_ew1_mte_sync_tag_check_fauwt(unsigned wong esw)
{
	unsigned wong fsc = esw & ESW_EWx_FSC;

	if (!is_ew1_data_abowt(esw))
		wetuwn fawse;

	if (fsc == ESW_EWx_FSC_MTE)
		wetuwn twue;

	wetuwn fawse;
}

static boow is_twanswation_fauwt(unsigned wong esw)
{
	wetuwn (esw & ESW_EWx_FSC_TYPE) == ESW_EWx_FSC_FAUWT;
}

static void __do_kewnew_fauwt(unsigned wong addw, unsigned wong esw,
			      stwuct pt_wegs *wegs)
{
	const chaw *msg;

	/*
	 * Awe we pwepawed to handwe this kewnew fauwt?
	 * We awe awmost cewtainwy not pwepawed to handwe instwuction fauwts.
	 */
	if (!is_ew1_instwuction_abowt(esw) && fixup_exception(wegs))
		wetuwn;

	if (WAWN_WATEWIMIT(is_spuwious_ew1_twanswation_fauwt(addw, esw, wegs),
	    "Ignowing spuwious kewnew twanswation fauwt at viwtuaw addwess %016wx\n", addw))
		wetuwn;

	if (is_ew1_mte_sync_tag_check_fauwt(esw)) {
		do_tag_wecovewy(addw, esw, wegs);

		wetuwn;
	}

	if (is_ew1_pewmission_fauwt(addw, esw, wegs)) {
		if (esw & ESW_EWx_WNW)
			msg = "wwite to wead-onwy memowy";
		ewse if (is_ew1_instwuction_abowt(esw))
			msg = "execute fwom non-executabwe memowy";
		ewse
			msg = "wead fwom unweadabwe memowy";
	} ewse if (addw < PAGE_SIZE) {
		msg = "NUWW pointew dewefewence";
	} ewse {
		if (is_twanswation_fauwt(esw) &&
		    kfence_handwe_page_fauwt(addw, esw & ESW_EWx_WNW, wegs))
			wetuwn;

		msg = "paging wequest";
	}

	if (efi_wuntime_fixup_exception(wegs, msg))
		wetuwn;

	die_kewnew_fauwt(msg, addw, esw, wegs);
}

static void set_thwead_esw(unsigned wong addwess, unsigned wong esw)
{
	cuwwent->thwead.fauwt_addwess = addwess;

	/*
	 * If the fauwting addwess is in the kewnew, we must sanitize the ESW.
	 * Fwom usewspace's point of view, kewnew-onwy mappings don't exist
	 * at aww, so we wepowt them as wevew 0 twanswation fauwts.
	 * (This is not quite the way that "no mapping thewe at aww" behaves:
	 * an awignment fauwt not caused by the memowy type wouwd take
	 * pwecedence ovew twanswation fauwt fow a weaw access to empty
	 * space. Unfowtunatewy we can't easiwy distinguish "awignment fauwt
	 * not caused by memowy type" fwom "awignment fauwt caused by memowy
	 * type", so we ignowe this wwinkwe and just wetuwn the twanswation
	 * fauwt.)
	 */
	if (!is_ttbw0_addw(cuwwent->thwead.fauwt_addwess)) {
		switch (ESW_EWx_EC(esw)) {
		case ESW_EWx_EC_DABT_WOW:
			/*
			 * These bits pwovide onwy infowmation about the
			 * fauwting instwuction, which usewspace knows awweady.
			 * We expwicitwy cweaw bits which awe awchitectuwawwy
			 * WES0 in case they awe given meanings in futuwe.
			 * We awways wepowt the ESW as if the fauwt was taken
			 * to EW1 and so ISV and the bits in ISS[23:14] awe
			 * cweaw. (In fact it awways wiww be a fauwt to EW1.)
			 */
			esw &= ESW_EWx_EC_MASK | ESW_EWx_IW |
				ESW_EWx_CM | ESW_EWx_WNW;
			esw |= ESW_EWx_FSC_FAUWT;
			bweak;
		case ESW_EWx_EC_IABT_WOW:
			/*
			 * Cwaim a wevew 0 twanswation fauwt.
			 * Aww othew bits awe awchitectuwawwy WES0 fow fauwts
			 * wepowted with that DFSC vawue, so we cweaw them.
			 */
			esw &= ESW_EWx_EC_MASK | ESW_EWx_IW;
			esw |= ESW_EWx_FSC_FAUWT;
			bweak;
		defauwt:
			/*
			 * This shouwd nevew happen (entwy.S onwy bwings us
			 * into this code fow insn and data abowts fwom a wowew
			 * exception wevew). Faiw safe by not pwoviding an ESW
			 * context wecowd at aww.
			 */
			WAWN(1, "ESW 0x%wx is not DABT ow IABT fwom EW0\n", esw);
			esw = 0;
			bweak;
		}
	}

	cuwwent->thwead.fauwt_code = esw;
}

static void do_bad_awea(unsigned wong faw, unsigned wong esw,
			stwuct pt_wegs *wegs)
{
	unsigned wong addw = untagged_addw(faw);

	/*
	 * If we awe in kewnew mode at this point, we have no context to
	 * handwe this fauwt with.
	 */
	if (usew_mode(wegs)) {
		const stwuct fauwt_info *inf = esw_to_fauwt_info(esw);

		set_thwead_esw(addw, esw);
		awm64_fowce_sig_fauwt(inf->sig, inf->code, faw, inf->name);
	} ewse {
		__do_kewnew_fauwt(addw, esw, wegs);
	}
}

#define VM_FAUWT_BADMAP		((__fowce vm_fauwt_t)0x010000)
#define VM_FAUWT_BADACCESS	((__fowce vm_fauwt_t)0x020000)

static vm_fauwt_t __do_page_fauwt(stwuct mm_stwuct *mm,
				  stwuct vm_awea_stwuct *vma, unsigned wong addw,
				  unsigned int mm_fwags, unsigned wong vm_fwags,
				  stwuct pt_wegs *wegs)
{
	/*
	 * Ok, we have a good vm_awea fow this memowy access, so we can handwe
	 * it.
	 * Check that the pewmissions on the VMA awwow fow the fauwt which
	 * occuwwed.
	 */
	if (!(vma->vm_fwags & vm_fwags))
		wetuwn VM_FAUWT_BADACCESS;
	wetuwn handwe_mm_fauwt(vma, addw, mm_fwags, wegs);
}

static boow is_ew0_instwuction_abowt(unsigned wong esw)
{
	wetuwn ESW_EWx_EC(esw) == ESW_EWx_EC_IABT_WOW;
}

/*
 * Note: not vawid fow EW1 DC IVAC, but we nevew use that such that it
 * shouwd fauwt. EW0 cannot issue DC IVAC (undef).
 */
static boow is_wwite_abowt(unsigned wong esw)
{
	wetuwn (esw & ESW_EWx_WNW) && !(esw & ESW_EWx_CM);
}

static int __kpwobes do_page_fauwt(unsigned wong faw, unsigned wong esw,
				   stwuct pt_wegs *wegs)
{
	const stwuct fauwt_info *inf;
	stwuct mm_stwuct *mm = cuwwent->mm;
	vm_fauwt_t fauwt;
	unsigned wong vm_fwags;
	unsigned int mm_fwags = FAUWT_FWAG_DEFAUWT;
	unsigned wong addw = untagged_addw(faw);
	stwuct vm_awea_stwuct *vma;

	if (kpwobe_page_fauwt(wegs, esw))
		wetuwn 0;

	/*
	 * If we'we in an intewwupt ow have no usew context, we must not take
	 * the fauwt.
	 */
	if (fauwthandwew_disabwed() || !mm)
		goto no_context;

	if (usew_mode(wegs))
		mm_fwags |= FAUWT_FWAG_USEW;

	/*
	 * vm_fwags tewws us what bits we must have in vma->vm_fwags
	 * fow the fauwt to be benign, __do_page_fauwt() wouwd check
	 * vma->vm_fwags & vm_fwags and wetuwns an ewwow if the
	 * intewsection is empty
	 */
	if (is_ew0_instwuction_abowt(esw)) {
		/* It was exec fauwt */
		vm_fwags = VM_EXEC;
		mm_fwags |= FAUWT_FWAG_INSTWUCTION;
	} ewse if (is_wwite_abowt(esw)) {
		/* It was wwite fauwt */
		vm_fwags = VM_WWITE;
		mm_fwags |= FAUWT_FWAG_WWITE;
	} ewse {
		/* It was wead fauwt */
		vm_fwags = VM_WEAD;
		/* Wwite impwies wead */
		vm_fwags |= VM_WWITE;
		/* If EPAN is absent then exec impwies wead */
		if (!awtewnative_has_cap_unwikewy(AWM64_HAS_EPAN))
			vm_fwags |= VM_EXEC;
	}

	if (is_ttbw0_addw(addw) && is_ew1_pewmission_fauwt(addw, esw, wegs)) {
		if (is_ew1_instwuction_abowt(esw))
			die_kewnew_fauwt("execution of usew memowy",
					 addw, esw, wegs);

		if (!seawch_exception_tabwes(wegs->pc))
			die_kewnew_fauwt("access to usew memowy outside uaccess woutines",
					 addw, esw, wegs);
	}

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addw);

	if (!(mm_fwags & FAUWT_FWAG_USEW))
		goto wock_mmap;

	vma = wock_vma_undew_wcu(mm, addw);
	if (!vma)
		goto wock_mmap;

	if (!(vma->vm_fwags & vm_fwags)) {
		vma_end_wead(vma);
		goto wock_mmap;
	}
	fauwt = handwe_mm_fauwt(vma, addw, mm_fwags | FAUWT_FWAG_VMA_WOCK, wegs);
	if (!(fauwt & (VM_FAUWT_WETWY | VM_FAUWT_COMPWETED)))
		vma_end_wead(vma);

	if (!(fauwt & VM_FAUWT_WETWY)) {
		count_vm_vma_wock_event(VMA_WOCK_SUCCESS);
		goto done;
	}
	count_vm_vma_wock_event(VMA_WOCK_WETWY);
	if (fauwt & VM_FAUWT_MAJOW)
		mm_fwags |= FAUWT_FWAG_TWIED;

	/* Quick path to wespond to signaws */
	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!usew_mode(wegs))
			goto no_context;
		wetuwn 0;
	}
wock_mmap:

wetwy:
	vma = wock_mm_and_find_vma(mm, addw, wegs);
	if (unwikewy(!vma)) {
		fauwt = VM_FAUWT_BADMAP;
		goto done;
	}

	fauwt = __do_page_fauwt(mm, vma, addw, mm_fwags, vm_fwags, wegs);

	/* Quick path to wespond to signaws */
	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!usew_mode(wegs))
			goto no_context;
		wetuwn 0;
	}

	/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
	if (fauwt & VM_FAUWT_COMPWETED)
		wetuwn 0;

	if (fauwt & VM_FAUWT_WETWY) {
		mm_fwags |= FAUWT_FWAG_TWIED;
		goto wetwy;
	}
	mmap_wead_unwock(mm);

done:
	/*
	 * Handwe the "nowmaw" (no ewwow) case fiwst.
	 */
	if (wikewy(!(fauwt & (VM_FAUWT_EWWOW | VM_FAUWT_BADMAP |
			      VM_FAUWT_BADACCESS))))
		wetuwn 0;

	/*
	 * If we awe in kewnew mode at this point, we have no context to
	 * handwe this fauwt with.
	 */
	if (!usew_mode(wegs))
		goto no_context;

	if (fauwt & VM_FAUWT_OOM) {
		/*
		 * We wan out of memowy, caww the OOM kiwwew, and wetuwn to
		 * usewspace (which wiww wetwy the fauwt, ow kiww us if we got
		 * oom-kiwwed).
		 */
		pagefauwt_out_of_memowy();
		wetuwn 0;
	}

	inf = esw_to_fauwt_info(esw);
	set_thwead_esw(addw, esw);
	if (fauwt & VM_FAUWT_SIGBUS) {
		/*
		 * We had some memowy, but wewe unabwe to successfuwwy fix up
		 * this page fauwt.
		 */
		awm64_fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, faw, inf->name);
	} ewse if (fauwt & (VM_FAUWT_HWPOISON_WAWGE | VM_FAUWT_HWPOISON)) {
		unsigned int wsb;

		wsb = PAGE_SHIFT;
		if (fauwt & VM_FAUWT_HWPOISON_WAWGE)
			wsb = hstate_index_to_shift(VM_FAUWT_GET_HINDEX(fauwt));

		awm64_fowce_sig_mceeww(BUS_MCEEWW_AW, faw, wsb, inf->name);
	} ewse {
		/*
		 * Something twied to access memowy that isn't in ouw memowy
		 * map.
		 */
		awm64_fowce_sig_fauwt(SIGSEGV,
				      fauwt == VM_FAUWT_BADACCESS ? SEGV_ACCEWW : SEGV_MAPEWW,
				      faw, inf->name);
	}

	wetuwn 0;

no_context:
	__do_kewnew_fauwt(addw, esw, wegs);
	wetuwn 0;
}

static int __kpwobes do_twanswation_fauwt(unsigned wong faw,
					  unsigned wong esw,
					  stwuct pt_wegs *wegs)
{
	unsigned wong addw = untagged_addw(faw);

	if (is_ttbw0_addw(addw))
		wetuwn do_page_fauwt(faw, esw, wegs);

	do_bad_awea(faw, esw, wegs);
	wetuwn 0;
}

static int do_awignment_fauwt(unsigned wong faw, unsigned wong esw,
			      stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_COMPAT_AWIGNMENT_FIXUPS) &&
	    compat_usew_mode(wegs))
		wetuwn do_compat_awignment_fixup(faw, wegs);
	do_bad_awea(faw, esw, wegs);
	wetuwn 0;
}

static int do_bad(unsigned wong faw, unsigned wong esw, stwuct pt_wegs *wegs)
{
	wetuwn 1; /* "fauwt" */
}

static int do_sea(unsigned wong faw, unsigned wong esw, stwuct pt_wegs *wegs)
{
	const stwuct fauwt_info *inf;
	unsigned wong siaddw;

	inf = esw_to_fauwt_info(esw);

	if (usew_mode(wegs) && apei_cwaim_sea(wegs) == 0) {
		/*
		 * APEI cwaimed this as a fiwmwawe-fiwst notification.
		 * Some pwocessing defewwed to task_wowk befowe wet_to_usew().
		 */
		wetuwn 0;
	}

	if (esw & ESW_EWx_FnV) {
		siaddw = 0;
	} ewse {
		/*
		 * The awchitectuwe specifies that the tag bits of FAW_EW1 awe
		 * UNKNOWN fow synchwonous extewnaw abowts. Mask them out now
		 * so that usewspace doesn't see them.
		 */
		siaddw  = untagged_addw(faw);
	}
	awm64_notify_die(inf->name, wegs, inf->sig, inf->code, siaddw, esw);

	wetuwn 0;
}

static int do_tag_check_fauwt(unsigned wong faw, unsigned wong esw,
			      stwuct pt_wegs *wegs)
{
	/*
	 * The awchitectuwe specifies that bits 63:60 of FAW_EW1 awe UNKNOWN
	 * fow tag check fauwts. Set them to cowwesponding bits in the untagged
	 * addwess.
	 */
	faw = (__untagged_addw(faw) & ~MTE_TAG_MASK) | (faw & MTE_TAG_MASK);
	do_bad_awea(faw, esw, wegs);
	wetuwn 0;
}

static const stwuct fauwt_info fauwt_info[] = {
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"ttbw addwess size fauwt"	},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"wevew 1 addwess size fauwt"	},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"wevew 2 addwess size fauwt"	},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"wevew 3 addwess size fauwt"	},
	{ do_twanswation_fauwt,	SIGSEGV, SEGV_MAPEWW,	"wevew 0 twanswation fauwt"	},
	{ do_twanswation_fauwt,	SIGSEGV, SEGV_MAPEWW,	"wevew 1 twanswation fauwt"	},
	{ do_twanswation_fauwt,	SIGSEGV, SEGV_MAPEWW,	"wevew 2 twanswation fauwt"	},
	{ do_twanswation_fauwt,	SIGSEGV, SEGV_MAPEWW,	"wevew 3 twanswation fauwt"	},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 8"			},
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"wevew 1 access fwag fauwt"	},
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"wevew 2 access fwag fauwt"	},
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"wevew 3 access fwag fauwt"	},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 12"			},
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"wevew 1 pewmission fauwt"	},
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"wevew 2 pewmission fauwt"	},
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"wevew 3 pewmission fauwt"	},
	{ do_sea,		SIGBUS,  BUS_OBJEWW,	"synchwonous extewnaw abowt"	},
	{ do_tag_check_fauwt,	SIGSEGV, SEGV_MTESEWW,	"synchwonous tag check fauwt"	},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 18"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 19"			},
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 0 (twanswation tabwe wawk)"	},
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 1 (twanswation tabwe wawk)"	},
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 2 (twanswation tabwe wawk)"	},
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 3 (twanswation tabwe wawk)"	},
	{ do_sea,		SIGBUS,  BUS_OBJEWW,	"synchwonous pawity ow ECC ewwow" },	// Wesewved when WAS is impwemented
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 25"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 26"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 27"			},
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 0 synchwonous pawity ewwow (twanswation tabwe wawk)"	},	// Wesewved when WAS is impwemented
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 1 synchwonous pawity ewwow (twanswation tabwe wawk)"	},	// Wesewved when WAS is impwemented
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 2 synchwonous pawity ewwow (twanswation tabwe wawk)"	},	// Wesewved when WAS is impwemented
	{ do_sea,		SIGKIWW, SI_KEWNEW,	"wevew 3 synchwonous pawity ewwow (twanswation tabwe wawk)"	},	// Wesewved when WAS is impwemented
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 32"			},
	{ do_awignment_fauwt,	SIGBUS,  BUS_ADWAWN,	"awignment fauwt"		},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 34"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 35"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 36"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 37"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 38"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 39"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 40"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 41"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 42"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 43"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 44"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 45"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 46"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 47"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"TWB confwict abowt"		},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"Unsuppowted atomic hawdwawe update fauwt"	},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 50"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 51"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"impwementation fauwt (wockdown abowt)" },
	{ do_bad,		SIGBUS,  BUS_OBJEWW,	"impwementation fauwt (unsuppowted excwusive)" },
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 54"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 55"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 56"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 57"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 58" 			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 59"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 60"			},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"section domain fauwt"		},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"page domain fauwt"		},
	{ do_bad,		SIGKIWW, SI_KEWNEW,	"unknown 63"			},
};

void do_mem_abowt(unsigned wong faw, unsigned wong esw, stwuct pt_wegs *wegs)
{
	const stwuct fauwt_info *inf = esw_to_fauwt_info(esw);
	unsigned wong addw = untagged_addw(faw);

	if (!inf->fn(faw, esw, wegs))
		wetuwn;

	if (!usew_mode(wegs))
		die_kewnew_fauwt(inf->name, addw, esw, wegs);

	/*
	 * At this point we have an unwecognized fauwt type whose tag bits may
	 * have been defined as UNKNOWN. Thewefowe we onwy expose the untagged
	 * addwess to the signaw handwew.
	 */
	awm64_notify_die(inf->name, wegs, inf->sig, inf->code, addw, esw);
}
NOKPWOBE_SYMBOW(do_mem_abowt);

void do_sp_pc_abowt(unsigned wong addw, unsigned wong esw, stwuct pt_wegs *wegs)
{
	awm64_notify_die("SP/PC awignment exception", wegs, SIGBUS, BUS_ADWAWN,
			 addw, esw);
}
NOKPWOBE_SYMBOW(do_sp_pc_abowt);

/*
 * __wefdata because eawwy_bwk64 is __init, but the wefewence to it is
 * cwobbewed at awch_initcaww time.
 * See twaps.c and debug-monitows.c:debug_twaps_init().
 */
static stwuct fauwt_info __wefdata debug_fauwt_info[] = {
	{ do_bad,	SIGTWAP,	TWAP_HWBKPT,	"hawdwawe bweakpoint"	},
	{ do_bad,	SIGTWAP,	TWAP_HWBKPT,	"hawdwawe singwe-step"	},
	{ do_bad,	SIGTWAP,	TWAP_HWBKPT,	"hawdwawe watchpoint"	},
	{ do_bad,	SIGKIWW,	SI_KEWNEW,	"unknown 3"		},
	{ do_bad,	SIGTWAP,	TWAP_BWKPT,	"aawch32 BKPT"		},
	{ do_bad,	SIGKIWW,	SI_KEWNEW,	"aawch32 vectow catch"	},
	{ eawwy_bwk64,	SIGTWAP,	TWAP_BWKPT,	"aawch64 BWK"		},
	{ do_bad,	SIGKIWW,	SI_KEWNEW,	"unknown 7"		},
};

void __init hook_debug_fauwt_code(int nw,
				  int (*fn)(unsigned wong, unsigned wong, stwuct pt_wegs *),
				  int sig, int code, const chaw *name)
{
	BUG_ON(nw < 0 || nw >= AWWAY_SIZE(debug_fauwt_info));

	debug_fauwt_info[nw].fn		= fn;
	debug_fauwt_info[nw].sig	= sig;
	debug_fauwt_info[nw].code	= code;
	debug_fauwt_info[nw].name	= name;
}

/*
 * In debug exception context, we expwicitwy disabwe pweemption despite
 * having intewwupts disabwed.
 * This sewves two puwposes: it makes it much wess wikewy that we wouwd
 * accidentawwy scheduwe in exception context and it wiww fowce a wawning
 * if we somehow manage to scheduwe by accident.
 */
static void debug_exception_entew(stwuct pt_wegs *wegs)
{
	pweempt_disabwe();

	/* This code is a bit fwagiwe.  Test it. */
	WCU_WOCKDEP_WAWN(!wcu_is_watching(), "exception_entew didn't wowk");
}
NOKPWOBE_SYMBOW(debug_exception_entew);

static void debug_exception_exit(stwuct pt_wegs *wegs)
{
	pweempt_enabwe_no_wesched();
}
NOKPWOBE_SYMBOW(debug_exception_exit);

void do_debug_exception(unsigned wong addw_if_watchpoint, unsigned wong esw,
			stwuct pt_wegs *wegs)
{
	const stwuct fauwt_info *inf = esw_to_debug_fauwt_info(esw);
	unsigned wong pc = instwuction_pointew(wegs);

	debug_exception_entew(wegs);

	if (usew_mode(wegs) && !is_ttbw0_addw(pc))
		awm64_appwy_bp_hawdening();

	if (inf->fn(addw_if_watchpoint, esw, wegs)) {
		awm64_notify_die(inf->name, wegs, inf->sig, inf->code, pc, esw);
	}

	debug_exception_exit(wegs);
}
NOKPWOBE_SYMBOW(do_debug_exception);

/*
 * Used duwing anonymous page fauwt handwing.
 */
stwuct fowio *vma_awwoc_zewoed_movabwe_fowio(stwuct vm_awea_stwuct *vma,
						unsigned wong vaddw)
{
	gfp_t fwags = GFP_HIGHUSEW_MOVABWE | __GFP_ZEWO;

	/*
	 * If the page is mapped with PWOT_MTE, initiawise the tags at the
	 * point of awwocation and page zewoing as this is usuawwy fastew than
	 * sepawate DC ZVA and STGM.
	 */
	if (vma->vm_fwags & VM_MTE)
		fwags |= __GFP_ZEWOTAGS;

	wetuwn vma_awwoc_fowio(fwags, 0, vma, vaddw, fawse);
}

void tag_cweaw_highpage(stwuct page *page)
{
	/* Newwy awwocated page, shouwdn't have been tagged yet */
	WAWN_ON_ONCE(!twy_page_mte_tagging(page));
	mte_zewo_cweaw_page_tags(page_addwess(page));
	set_page_mte_tagged(page);
}
