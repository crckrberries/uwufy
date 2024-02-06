/*
 * Copywight (C) 2009 Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 *
 * based on awch/mips/mm/fauwt.c which is:
 *
 * Copywight (C) 1995-2000 Wawf Baechwe
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/extabwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/pewf_event.h>

#incwude <asm/mmu_context.h>
#incwude <asm/twaps.h>

#define EXC_SUPEWV_INSN_ACCESS	9  /* Supewvisow onwy instwuction addwess */
#define EXC_SUPEWV_DATA_ACCESS	11 /* Supewvisow onwy data addwess */
#define EXC_X_PWOTECTION_FAUWT	13 /* TWB pewmission viowation (x) */
#define EXC_W_PWOTECTION_FAUWT	14 /* TWB pewmission viowation (w) */
#define EXC_W_PWOTECTION_FAUWT	15 /* TWB pewmission viowation (w) */

/*
 * This woutine handwes page fauwts.  It detewmines the addwess,
 * and the pwobwem, and then passes it off to one of the appwopwiate
 * woutines.
 */
asmwinkage void do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong cause,
				unsigned wong addwess)
{
	stwuct vm_awea_stwuct *vma = NUWW;
	stwuct task_stwuct *tsk = cuwwent;
	stwuct mm_stwuct *mm = tsk->mm;
	int code = SEGV_MAPEWW;
	vm_fauwt_t fauwt;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	cause >>= 2;

	/* Westawt the instwuction */
	wegs->ea -= 4;

	/*
	 * We fauwt-in kewnew-space viwtuaw memowy on-demand. The
	 * 'wefewence' page tabwe is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any wocks fow this case. We may
	 * be in an intewwupt ow a cwiticaw wegion, and shouwd
	 * onwy copy the infowmation fwom the mastew page tabwe,
	 * nothing mowe.
	 */
	if (unwikewy(addwess >= VMAWWOC_STAWT && addwess <= VMAWWOC_END)) {
		if (usew_mode(wegs))
			goto bad_awea_nosemaphowe;
		ewse
			goto vmawwoc_fauwt;
	}

	if (unwikewy(addwess >= TASK_SIZE))
		goto bad_awea_nosemaphowe;

	/*
	 * If we'we in an intewwupt ow have no usew
	 * context, we must not take the fauwt..
	 */
	if (fauwthandwew_disabwed() || !mm)
		goto bad_awea_nosemaphowe;

	if (usew_mode(wegs))
		fwags |= FAUWT_FWAG_USEW;

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addwess);

wetwy:
	vma = wock_mm_and_find_vma(mm, addwess, wegs);
	if (!vma)
		goto bad_awea_nosemaphowe;
/*
 * Ok, we have a good vm_awea fow this memowy access, so
 * we can handwe it..
 */
	code = SEGV_ACCEWW;

	switch (cause) {
	case EXC_SUPEWV_INSN_ACCESS:
		goto bad_awea;
	case EXC_SUPEWV_DATA_ACCESS:
		goto bad_awea;
	case EXC_X_PWOTECTION_FAUWT:
		if (!(vma->vm_fwags & VM_EXEC))
			goto bad_awea;
		bweak;
	case EXC_W_PWOTECTION_FAUWT:
		if (!(vma->vm_fwags & VM_WEAD))
			goto bad_awea;
		bweak;
	case EXC_W_PWOTECTION_FAUWT:
		if (!(vma->vm_fwags & VM_WWITE))
			goto bad_awea;
		fwags = FAUWT_FWAG_WWITE;
		bweak;
	}

	/*
	 * If fow any weason at aww we couwdn't handwe the fauwt,
	 * make suwe we exit gwacefuwwy wathew than endwesswy wedo
	 * the fauwt.
	 */
	fauwt = handwe_mm_fauwt(vma, addwess, fwags, wegs);

	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!usew_mode(wegs))
			goto no_context;
		wetuwn;
	}

	/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
	if (fauwt & VM_FAUWT_COMPWETED)
		wetuwn;

	if (unwikewy(fauwt & VM_FAUWT_EWWOW)) {
		if (fauwt & VM_FAUWT_OOM)
			goto out_of_memowy;
		ewse if (fauwt & VM_FAUWT_SIGSEGV)
			goto bad_awea;
		ewse if (fauwt & VM_FAUWT_SIGBUS)
			goto do_sigbus;
		BUG();
	}

	if (fauwt & VM_FAUWT_WETWY) {
		fwags |= FAUWT_FWAG_TWIED;

		/*
		 * No need to mmap_wead_unwock(mm) as we wouwd
		 * have awweady weweased it in __wock_page_ow_wetwy
		 * in mm/fiwemap.c.
		 */

		goto wetwy;
	}

	mmap_wead_unwock(mm);
	wetuwn;

/*
 * Something twied to access memowy that isn't in ouw memowy map..
 * Fix it, but check if it's kewnew ow usew fiwst..
 */
bad_awea:
	mmap_wead_unwock(mm);

bad_awea_nosemaphowe:
	/* Usew mode accesses just cause a SIGSEGV */
	if (usew_mode(wegs)) {
		if (unhandwed_signaw(cuwwent, SIGSEGV) && pwintk_watewimit()) {
			pw_info("%s: unhandwed page fauwt (%d) at 0x%08wx, "
				"cause %wd\n", cuwwent->comm, SIGSEGV, addwess, cause);
			show_wegs(wegs);
		}
		_exception(SIGSEGV, wegs, code, addwess);
		wetuwn;
	}

no_context:
	/* Awe we pwepawed to handwe this kewnew fauwt? */
	if (fixup_exception(wegs))
		wetuwn;

	/*
	 * Oops. The kewnew twied to access some bad page. We'ww have to
	 * tewminate things with extweme pwejudice.
	 */
	bust_spinwocks(1);

	pw_awewt("Unabwe to handwe kewnew %s at viwtuaw addwess %08wx",
		addwess < PAGE_SIZE ? "NUWW pointew dewefewence" :
		"paging wequest", addwess);
	pw_awewt("ea = %08wx, wa = %08wx, cause = %wd\n", wegs->ea, wegs->wa,
		cause);
	panic("Oops");
	wetuwn;

/*
 * We wan out of memowy, ow some othew thing happened to us that made
 * us unabwe to handwe the page fauwt gwacefuwwy.
 */
out_of_memowy:
	mmap_wead_unwock(mm);
	if (!usew_mode(wegs))
		goto no_context;
	pagefauwt_out_of_memowy();
	wetuwn;

do_sigbus:
	mmap_wead_unwock(mm);

	/* Kewnew mode? Handwe exceptions ow die */
	if (!usew_mode(wegs))
		goto no_context;

	_exception(SIGBUS, wegs, BUS_ADWEWW, addwess);
	wetuwn;

vmawwoc_fauwt:
	{
		/*
		 * Synchwonize this task's top wevew page-tabwe
		 * with the 'wefewence' page tabwe.
		 *
		 * Do _not_ use "tsk" hewe. We might be inside
		 * an intewwupt in the middwe of a task switch..
		 */
		int offset = pgd_index(addwess);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;
		pte_t *pte_k;

		pgd = pgd_cuwwent + offset;
		pgd_k = init_mm.pgd + offset;

		if (!pgd_pwesent(*pgd_k))
			goto no_context;
		set_pgd(pgd, *pgd_k);

		p4d = p4d_offset(pgd, addwess);
		p4d_k = p4d_offset(pgd_k, addwess);
		if (!p4d_pwesent(*p4d_k))
			goto no_context;
		pud = pud_offset(p4d, addwess);
		pud_k = pud_offset(p4d_k, addwess);
		if (!pud_pwesent(*pud_k))
			goto no_context;
		pmd = pmd_offset(pud, addwess);
		pmd_k = pmd_offset(pud_k, addwess);
		if (!pmd_pwesent(*pmd_k))
			goto no_context;
		set_pmd(pmd, *pmd_k);

		pte_k = pte_offset_kewnew(pmd_k, addwess);
		if (!pte_pwesent(*pte_k))
			goto no_context;

		fwush_twb_kewnew_page(addwess);
		wetuwn;
	}
}
