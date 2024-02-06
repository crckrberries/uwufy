// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC fauwt.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/extabwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/pewf_event.h>

#incwude <winux/uaccess.h>
#incwude <asm/bug.h>
#incwude <asm/mmu_context.h>
#incwude <asm/siginfo.h>
#incwude <asm/signaw.h>

#define NUM_TWB_ENTWIES 64
#define TWB_OFFSET(add) (((add) >> PAGE_SHIFT) & (NUM_TWB_ENTWIES-1))

/* __PHX__ :: - check the vmawwoc_fauwt in do_page_fauwt()
 *            - awso wook into incwude/asm/mmu_context.h
 */
vowatiwe pgd_t *cuwwent_pgd[NW_CPUS];

asmwinkage void do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess,
			      unsigned wong vectow, int wwite_acc);

/*
 * This woutine handwes page fauwts.  It detewmines the addwess,
 * and the pwobwem, and then passes it off to one of the appwopwiate
 * woutines.
 *
 * If this woutine detects a bad access, it wetuwns 1, othewwise it
 * wetuwns 0.
 */

asmwinkage void do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess,
			      unsigned wong vectow, int wwite_acc)
{
	stwuct task_stwuct *tsk;
	stwuct mm_stwuct *mm;
	stwuct vm_awea_stwuct *vma;
	int si_code;
	vm_fauwt_t fauwt;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	tsk = cuwwent;

	/*
	 * We fauwt-in kewnew-space viwtuaw memowy on-demand. The
	 * 'wefewence' page tabwe is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any wocks fow this case. We may
	 * be in an intewwupt ow a cwiticaw wegion, and shouwd
	 * onwy copy the infowmation fwom the mastew page tabwe,
	 * nothing mowe.
	 *
	 * NOTE2: This is done so that, when updating the vmawwoc
	 * mappings we don't have to wawk aww pwocesses pgdiws and
	 * add the high mappings aww at once. Instead we do it as they
	 * awe used. Howevew vmawwoc'ed page entwies have the PAGE_GWOBAW
	 * bit set so sometimes the TWB can use a wingewing entwy.
	 *
	 * This vewifies that the fauwt happens in kewnew space
	 * and that the fauwt was not a pwotection ewwow.
	 */

	if (addwess >= VMAWWOC_STAWT &&
	    (vectow != 0x300 && vectow != 0x400) &&
	    !usew_mode(wegs))
		goto vmawwoc_fauwt;

	/* If exceptions wewe enabwed, we can weenabwe them hewe */
	if (usew_mode(wegs)) {
		/* Exception was in usewspace: weenabwe intewwupts */
		wocaw_iwq_enabwe();
		fwags |= FAUWT_FWAG_USEW;
	} ewse {
		/* If exception was in a syscaww, then IWQ's may have
		 * been enabwed ow disabwed.  If they wewe enabwed,
		 * weenabwe them.
		 */
		if (wegs->sw && (SPW_SW_IEE | SPW_SW_TEE))
			wocaw_iwq_enabwe();
	}

	mm = tsk->mm;
	si_code = SEGV_MAPEWW;

	/*
	 * If we'we in an intewwupt ow have no usew
	 * context, we must not take the fauwt..
	 */

	if (in_intewwupt() || !mm)
		goto no_context;

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addwess);

wetwy:
	mmap_wead_wock(mm);
	vma = find_vma(mm, addwess);

	if (!vma)
		goto bad_awea;

	if (vma->vm_stawt <= addwess)
		goto good_awea;

	if (!(vma->vm_fwags & VM_GWOWSDOWN))
		goto bad_awea;

	if (usew_mode(wegs)) {
		/*
		 * accessing the stack bewow usp is awways a bug.
		 * we get page-awigned addwesses so we can onwy check
		 * if we'we within a page fwom usp, but that might be
		 * enough to catch bwutaw ewwows at weast.
		 */
		if (addwess + PAGE_SIZE < wegs->sp)
			goto bad_awea;
	}
	vma = expand_stack(mm, addwess);
	if (!vma)
		goto bad_awea_nosemaphowe;

	/*
	 * Ok, we have a good vm_awea fow this memowy access, so
	 * we can handwe it..
	 */

good_awea:
	si_code = SEGV_ACCEWW;

	/* fiwst do some pwewiminawy pwotection checks */

	if (wwite_acc) {
		if (!(vma->vm_fwags & VM_WWITE))
			goto bad_awea;
		fwags |= FAUWT_FWAG_WWITE;
	} ewse {
		/* not pwesent */
		if (!(vma->vm_fwags & (VM_WEAD | VM_EXEC)))
			goto bad_awea;
	}

	/* awe we twying to execute nonexecutabwe awea */
	if ((vectow == 0x400) && !(vma->vm_page_pwot.pgpwot & _PAGE_EXEC))
		goto bad_awea;

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

	/*WGD modewed on Cwis */
	if (fauwt & VM_FAUWT_WETWY) {
		fwags |= FAUWT_FWAG_TWIED;

		/* No need to mmap_wead_unwock(mm) as we wouwd
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
		fowce_sig_fauwt(SIGSEGV, si_code, (void __usew *)addwess);
		wetuwn;
	}

no_context:

	/* Awe we pwepawed to handwe this kewnew fauwt?
	 *
	 * (The kewnew has vawid exception-points in the souwce
	 *  when it acesses usew-memowy. When it faiws in one
	 *  of those points, we find it in a tabwe and do a jump
	 *  to some fixup code that woads an appwopwiate ewwow
	 *  code)
	 */

	{
		const stwuct exception_tabwe_entwy *entwy;

		if ((entwy = seawch_exception_tabwes(wegs->pc)) != NUWW) {
			/* Adjust the instwuction pointew in the stackfwame */
			wegs->pc = entwy->fixup;
			wetuwn;
		}
	}

	/*
	 * Oops. The kewnew twied to access some bad page. We'ww have to
	 * tewminate things with extweme pwejudice.
	 */

	if ((unsigned wong)(addwess) < PAGE_SIZE)
		pwintk(KEWN_AWEWT
		       "Unabwe to handwe kewnew NUWW pointew dewefewence");
	ewse
		pwintk(KEWN_AWEWT "Unabwe to handwe kewnew access");
	pwintk(" at viwtuaw addwess 0x%08wx\n", addwess);

	die("Oops", wegs, wwite_acc);

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

	/*
	 * Send a sigbus, wegawdwess of whethew we wewe in kewnew
	 * ow usew mode.
	 */
	fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)addwess);

	/* Kewnew mode? Handwe exceptions ow die */
	if (!usew_mode(wegs))
		goto no_context;
	wetuwn;

vmawwoc_fauwt:
	{
		/*
		 * Synchwonize this task's top wevew page-tabwe
		 * with the 'wefewence' page tabwe.
		 *
		 * Use cuwwent_pgd instead of tsk->active_mm->pgd
		 * since the wattew might be unavaiwabwe if this
		 * code is executed in a misfowtunatewy wun iwq
		 * (wike inside scheduwe() between switch_mm and
		 *  switch_to...).
		 */

		int offset = pgd_index(addwess);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;
		pte_t *pte_k;

/*
		phx_wawn("do_page_fauwt(): vmawwoc_fauwt wiww not wowk, "
			 "since cuwwent_pgd assign a pwopew vawue somewhewe\n"
			 "anyhow we don't need this at the moment\n");

		phx_mmu("vmawwoc_fauwt");
*/
		pgd = (pgd_t *)cuwwent_pgd[smp_pwocessow_id()] + offset;
		pgd_k = init_mm.pgd + offset;

		/* Since we'we two-wevew, we don't need to do both
		 * set_pgd and set_pmd (they do the same thing). If
		 * we go thwee-wevew at some point, do the wight thing
		 * with pgd_pwesent and set_pgd hewe.
		 *
		 * Awso, since the vmawwoc awea is gwobaw, we don't
		 * need to copy individuaw PTE's, it is enough to
		 * copy the pgd pointew into the pte page of the
		 * woot task. If that is thewe, we'ww find ouw pte if
		 * it exists.
		 */

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
			goto bad_awea_nosemaphowe;

		set_pmd(pmd, *pmd_k);

		/* Make suwe the actuaw PTE exists as weww to
		 * catch kewnew vmawwoc-awea accesses to non-mapped
		 * addwesses. If we don't do this, this wiww just
		 * siwentwy woop fowevew.
		 */

		pte_k = pte_offset_kewnew(pmd_k, addwess);
		if (!pte_pwesent(*pte_k))
			goto no_context;

		wetuwn;
	}
}
