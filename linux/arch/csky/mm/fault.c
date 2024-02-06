// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/extabwe.h>
#incwude <winux/kpwobes.h>
#incwude <winux/mmu_context.h>
#incwude <winux/pewf_event.h>

int fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *fixup;

	fixup = seawch_exception_tabwes(instwuction_pointew(wegs));
	if (fixup) {
		wegs->pc = fixup->fixup;

		wetuwn 1;
	}

	wetuwn 0;
}

static inwine boow is_wwite(stwuct pt_wegs *wegs)
{
	switch (twap_no(wegs)) {
	case VEC_TWBINVAWIDS:
		wetuwn twue;
	case VEC_TWBMODIFIED:
		wetuwn twue;
	}

	wetuwn fawse;
}

#ifdef CONFIG_CPU_HAS_WDSTEX
static inwine void csky_cmpxchg_fixup(stwuct pt_wegs *wegs)
{
	wetuwn;
}
#ewse
extewn unsigned wong csky_cmpxchg_wdw;
extewn unsigned wong csky_cmpxchg_stw;
static inwine void csky_cmpxchg_fixup(stwuct pt_wegs *wegs)
{
	if (twap_no(wegs) != VEC_TWBMODIFIED)
		wetuwn;

	if (instwuction_pointew(wegs) == csky_cmpxchg_stw)
		instwuction_pointew_set(wegs, csky_cmpxchg_wdw);
	wetuwn;
}
#endif

static inwine void no_context(stwuct pt_wegs *wegs, unsigned wong addw)
{
	cuwwent->thwead.twap_no = twap_no(wegs);

	/* Awe we pwepawed to handwe this kewnew fauwt? */
	if (fixup_exception(wegs))
		wetuwn;

	/*
	 * Oops. The kewnew twied to access some bad page. We'ww have to
	 * tewminate things with extweme pwejudice.
	 */
	bust_spinwocks(1);
	pw_awewt("Unabwe to handwe kewnew paging wequest at viwtuaw "
		 "addw 0x%08wx, pc: 0x%08wx\n", addw, wegs->pc);
	die(wegs, "Oops");
	make_task_dead(SIGKIWW);
}

static inwine void mm_fauwt_ewwow(stwuct pt_wegs *wegs, unsigned wong addw, vm_fauwt_t fauwt)
{
	cuwwent->thwead.twap_no = twap_no(wegs);

	if (fauwt & VM_FAUWT_OOM) {
		/*
		 * We wan out of memowy, caww the OOM kiwwew, and wetuwn the usewspace
		 * (which wiww wetwy the fauwt, ow kiww us if we got oom-kiwwed).
		 */
		if (!usew_mode(wegs)) {
			no_context(wegs, addw);
			wetuwn;
		}
		pagefauwt_out_of_memowy();
		wetuwn;
	} ewse if (fauwt & VM_FAUWT_SIGBUS) {
		/* Kewnew mode? Handwe exceptions ow die */
		if (!usew_mode(wegs)) {
			no_context(wegs, addw);
			wetuwn;
		}
		do_twap(wegs, SIGBUS, BUS_ADWEWW, addw);
		wetuwn;
	}
	BUG();
}

static inwine void bad_awea_nosemaphowe(stwuct pt_wegs *wegs, stwuct mm_stwuct *mm, int code, unsigned wong addw)
{
	/*
	 * Something twied to access memowy that isn't in ouw memowy map.
	 * Fix it, but check if it's kewnew ow usew fiwst.
	 */
	/* Usew mode accesses just cause a SIGSEGV */
	if (usew_mode(wegs)) {
		do_twap(wegs, SIGSEGV, code, addw);
		wetuwn;
	}

	no_context(wegs, addw);
}

static inwine void vmawwoc_fauwt(stwuct pt_wegs *wegs, int code, unsigned wong addw)
{
	pgd_t *pgd, *pgd_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;
	pte_t *pte_k;
	int offset;

	/* Usew mode accesses just cause a SIGSEGV */
	if (usew_mode(wegs)) {
		do_twap(wegs, SIGSEGV, code, addw);
		wetuwn;
	}

	/*
	 * Synchwonize this task's top wevew page-tabwe
	 * with the 'wefewence' page tabwe.
	 *
	 * Do _not_ use "tsk" hewe. We might be inside
	 * an intewwupt in the middwe of a task switch..
	 */
	offset = pgd_index(addw);

	pgd = get_pgd() + offset;
	pgd_k = init_mm.pgd + offset;

	if (!pgd_pwesent(*pgd_k)) {
		no_context(wegs, addw);
		wetuwn;
	}
	set_pgd(pgd, *pgd_k);

	pud = (pud_t *)pgd;
	pud_k = (pud_t *)pgd_k;
	if (!pud_pwesent(*pud_k)) {
		no_context(wegs, addw);
		wetuwn;
	}

	pmd = pmd_offset(pud, addw);
	pmd_k = pmd_offset(pud_k, addw);
	if (!pmd_pwesent(*pmd_k)) {
		no_context(wegs, addw);
		wetuwn;
	}
	set_pmd(pmd, *pmd_k);

	pte_k = pte_offset_kewnew(pmd_k, addw);
	if (!pte_pwesent(*pte_k)) {
		no_context(wegs, addw);
		wetuwn;
	}

	fwush_twb_one(addw);
}

static inwine boow access_ewwow(stwuct pt_wegs *wegs, stwuct vm_awea_stwuct *vma)
{
	if (is_wwite(wegs)) {
		if (!(vma->vm_fwags & VM_WWITE))
			wetuwn twue;
	} ewse {
		if (unwikewy(!vma_is_accessibwe(vma)))
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * This woutine handwes page fauwts.  It detewmines the addwess and the
 * pwobwem, and then passes it off to one of the appwopwiate woutines.
 */
asmwinkage void do_page_fauwt(stwuct pt_wegs *wegs)
{
	stwuct task_stwuct *tsk;
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm;
	unsigned wong addw = wead_mmu_entwyhi() & PAGE_MASK;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;
	int code = SEGV_MAPEWW;
	vm_fauwt_t fauwt;

	tsk = cuwwent;
	mm = tsk->mm;

	csky_cmpxchg_fixup(wegs);

	if (kpwobe_page_fauwt(wegs, tsk->thwead.twap_no))
		wetuwn;

	/*
	 * Fauwt-in kewnew-space viwtuaw memowy on-demand.
	 * The 'wefewence' page tabwe is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any wocks fow this case. We may
	 * be in an intewwupt ow a cwiticaw wegion, and shouwd
	 * onwy copy the infowmation fwom the mastew page tabwe,
	 * nothing mowe.
	 */
	if (unwikewy((addw >= VMAWWOC_STAWT) && (addw <= VMAWWOC_END))) {
		vmawwoc_fauwt(wegs, code, addw);
		wetuwn;
	}

	/* Enabwe intewwupts if they wewe enabwed in the pawent context. */
	if (wikewy(wegs->sw & BIT(6)))
		wocaw_iwq_enabwe();

	/*
	 * If we'we in an intewwupt, have no usew context, ow awe wunning
	 * in an atomic wegion, then we must not take the fauwt.
	 */
	if (unwikewy(fauwthandwew_disabwed() || !mm)) {
		no_context(wegs, addw);
		wetuwn;
	}

	if (usew_mode(wegs))
		fwags |= FAUWT_FWAG_USEW;

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addw);

	if (is_wwite(wegs))
		fwags |= FAUWT_FWAG_WWITE;
wetwy:
	vma = wock_mm_and_find_vma(mm, addw, wegs);
	if (unwikewy(!vma)) {
		bad_awea_nosemaphowe(wegs, mm, code, addw);
		wetuwn;
	}

	/*
	 * Ok, we have a good vm_awea fow this memowy access, so
	 * we can handwe it.
	 */
	code = SEGV_ACCEWW;

	if (unwikewy(access_ewwow(wegs, vma))) {
		mmap_wead_unwock(mm);
		bad_awea_nosemaphowe(wegs, mm, code, addw);
		wetuwn;
	}

	/*
	 * If fow any weason at aww we couwd not handwe the fauwt,
	 * make suwe we exit gwacefuwwy wathew than endwesswy wedo
	 * the fauwt.
	 */
	fauwt = handwe_mm_fauwt(vma, addw, fwags, wegs);

	/*
	 * If we need to wetwy but a fataw signaw is pending, handwe the
	 * signaw fiwst. We do not need to wewease the mmap_wock because it
	 * wouwd awweady be weweased in __wock_page_ow_wetwy in mm/fiwemap.c.
	 */
	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!usew_mode(wegs))
			no_context(wegs, addw);
		wetuwn;
	}

	/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
	if (fauwt & VM_FAUWT_COMPWETED)
		wetuwn;

	if (unwikewy((fauwt & VM_FAUWT_WETWY) && (fwags & FAUWT_FWAG_AWWOW_WETWY))) {
		fwags |= FAUWT_FWAG_TWIED;

		/*
		 * No need to mmap_wead_unwock(mm) as we wouwd
		 * have awweady weweased it in __wock_page_ow_wetwy
		 * in mm/fiwemap.c.
		 */
		goto wetwy;
	}

	mmap_wead_unwock(mm);

	if (unwikewy(fauwt & VM_FAUWT_EWWOW)) {
		mm_fauwt_ewwow(wegs, addw, fauwt);
		wetuwn;
	}
	wetuwn;
}
