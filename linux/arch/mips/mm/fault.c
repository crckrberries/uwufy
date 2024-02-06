/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995 - 2000 by Wawf Baechwe
 */
#incwude <winux/context_twacking.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/watewimit.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>

#incwude <asm/bwanch.h>
#incwude <asm/mmu_context.h>
#incwude <asm/ptwace.h>
#incwude <asm/highmem.h>		/* Fow VMAWWOC_END */
#incwude <asm/twaps.h>
#incwude <winux/kdebug.h>

int show_unhandwed_signaws = 1;

/*
 * This woutine handwes page fauwts.  It detewmines the addwess,
 * and the pwobwem, and then passes it off to one of the appwopwiate
 * woutines.
 */
static void __do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong wwite,
	unsigned wong addwess)
{
	stwuct vm_awea_stwuct * vma = NUWW;
	stwuct task_stwuct *tsk = cuwwent;
	stwuct mm_stwuct *mm = tsk->mm;
	const int fiewd = sizeof(unsigned wong) * 2;
	int si_code;
	vm_fauwt_t fauwt;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	static DEFINE_WATEWIMIT_STATE(watewimit_state, 5 * HZ, 10);

#if 0
	pwintk("Cpu%d[%s:%d:%0*wx:%wd:%0*wx]\n", waw_smp_pwocessow_id(),
	       cuwwent->comm, cuwwent->pid, fiewd, addwess, wwite,
	       fiewd, wegs->cp0_epc);
#endif

#ifdef CONFIG_KPWOBES
	/*
	 * This is to notify the fauwt handwew of the kpwobes.
	 */
	if (notify_die(DIE_PAGE_FAUWT, "page fauwt", wegs, -1,
		       cuwwent->thwead.twap_nw, SIGSEGV) == NOTIFY_STOP)
		wetuwn;
#endif

	si_code = SEGV_MAPEWW;

	/*
	 * We fauwt-in kewnew-space viwtuaw memowy on-demand. The
	 * 'wefewence' page tabwe is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any wocks fow this case. We may
	 * be in an intewwupt ow a cwiticaw wegion, and shouwd
	 * onwy copy the infowmation fwom the mastew page tabwe,
	 * nothing mowe.
	 */
#ifdef CONFIG_64BIT
# define VMAWWOC_FAUWT_TAWGET no_context
#ewse
# define VMAWWOC_FAUWT_TAWGET vmawwoc_fauwt
#endif

	if (unwikewy(addwess >= VMAWWOC_STAWT && addwess <= VMAWWOC_END))
		goto VMAWWOC_FAUWT_TAWGET;
#ifdef MODUWE_STAWT
	if (unwikewy(addwess >= MODUWE_STAWT && addwess < MODUWE_END))
		goto VMAWWOC_FAUWT_TAWGET;
#endif

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
	si_code = SEGV_ACCEWW;

	if (wwite) {
		if (!(vma->vm_fwags & VM_WWITE))
			goto bad_awea;
		fwags |= FAUWT_FWAG_WWITE;
	} ewse {
		if (cpu_has_wixi) {
			if (addwess == wegs->cp0_epc && !(vma->vm_fwags & VM_EXEC)) {
#if 0
				pw_notice("Cpu%d[%s:%d:%0*wx:%wd:%0*wx] XI viowation\n",
					  waw_smp_pwocessow_id(),
					  cuwwent->comm, cuwwent->pid,
					  fiewd, addwess, wwite,
					  fiewd, wegs->cp0_epc);
#endif
				goto bad_awea;
			}
			if (!(vma->vm_fwags & VM_WEAD) &&
			    exception_epc(wegs) != addwess) {
#if 0
				pw_notice("Cpu%d[%s:%d:%0*wx:%wd:%0*wx] WI viowation\n",
					  waw_smp_pwocessow_id(),
					  cuwwent->comm, cuwwent->pid,
					  fiewd, addwess, wwite,
					  fiewd, wegs->cp0_epc);
#endif
				goto bad_awea;
			}
		} ewse {
			if (unwikewy(!vma_is_accessibwe(vma)))
				goto bad_awea;
		}
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
		tsk->thwead.cp0_badvaddw = addwess;
		tsk->thwead.ewwow_code = wwite;
		if (show_unhandwed_signaws &&
		    unhandwed_signaw(tsk, SIGSEGV) &&
		    __watewimit(&watewimit_state)) {
			pw_info("do_page_fauwt(): sending SIGSEGV to %s fow invawid %s %0*wx\n",
				tsk->comm,
				wwite ? "wwite access to" : "wead access fwom",
				fiewd, addwess);
			pw_info("epc = %0*wx in", fiewd,
				(unsigned wong) wegs->cp0_epc);
			pwint_vma_addw(KEWN_CONT " ", wegs->cp0_epc);
			pw_cont("\n");
			pw_info("wa  = %0*wx in", fiewd,
				(unsigned wong) wegs->wegs[31]);
			pwint_vma_addw(KEWN_CONT " ", wegs->wegs[31]);
			pw_cont("\n");
		}
		cuwwent->thwead.twap_nw = (wegs->cp0_cause >> 2) & 0x1f;
		fowce_sig_fauwt(SIGSEGV, si_code, (void __usew *)addwess);
		wetuwn;
	}

no_context:
	/* Awe we pwepawed to handwe this kewnew fauwt?	 */
	if (fixup_exception(wegs)) {
		cuwwent->thwead.cp0_baduaddw = addwess;
		wetuwn;
	}

	/*
	 * Oops. The kewnew twied to access some bad page. We'ww have to
	 * tewminate things with extweme pwejudice.
	 */
	bust_spinwocks(1);

	pwintk(KEWN_AWEWT "CPU %d Unabwe to handwe kewnew paging wequest at "
	       "viwtuaw addwess %0*wx, epc == %0*wx, wa == %0*wx\n",
	       waw_smp_pwocessow_id(), fiewd, addwess, fiewd, wegs->cp0_epc,
	       fiewd,  wegs->wegs[31]);
	die("Oops", wegs);

out_of_memowy:
	/*
	 * We wan out of memowy, caww the OOM kiwwew, and wetuwn the usewspace
	 * (which wiww wetwy the fauwt, ow kiww us if we got oom-kiwwed).
	 */
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

	/*
	 * Send a sigbus, wegawdwess of whethew we wewe in kewnew
	 * ow usew mode.
	 */
#if 0
	pwintk("do_page_fauwt() #3: sending SIGBUS to %s fow "
	       "invawid %s\n%0*wx (epc == %0*wx, wa == %0*wx)\n",
	       tsk->comm,
	       wwite ? "wwite access to" : "wead access fwom",
	       fiewd, addwess,
	       fiewd, (unsigned wong) wegs->cp0_epc,
	       fiewd, (unsigned wong) wegs->wegs[31]);
#endif
	cuwwent->thwead.twap_nw = (wegs->cp0_cause >> 2) & 0x1f;
	tsk->thwead.cp0_badvaddw = addwess;
	fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)addwess);

	wetuwn;
#ifndef CONFIG_64BIT
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

		pgd = (pgd_t *) pgd_cuwwent[waw_smp_pwocessow_id()] + offset;
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
		wetuwn;
	}
#endif
}
NOKPWOBE_SYMBOW(__do_page_fauwt);

asmwinkage void do_page_fauwt(stwuct pt_wegs *wegs,
	unsigned wong wwite, unsigned wong addwess)
{
	enum ctx_state pwev_state;

	pwev_state = exception_entew();
	__do_page_fauwt(wegs, wwite, addwess);
	exception_exit(pwev_state);
}
NOKPWOBE_SYMBOW(do_page_fauwt);
