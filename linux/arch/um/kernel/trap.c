// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/debug.h>
#incwude <asm/cuwwent.h>
#incwude <asm/twbfwush.h>
#incwude <awch.h>
#incwude <as-wayout.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <skas.h>

/*
 * Note this is constwained to wetuwn 0, -EFAUWT, -EACCES, -ENOMEM by
 * segv().
 */
int handwe_page_fauwt(unsigned wong addwess, unsigned wong ip,
		      int is_wwite, int is_usew, int *code_out)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	pmd_t *pmd;
	pte_t *pte;
	int eww = -EFAUWT;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	*code_out = SEGV_MAPEWW;

	/*
	 * If the fauwt was with pagefauwts disabwed, don't take the fauwt, just
	 * faiw.
	 */
	if (fauwthandwew_disabwed())
		goto out_nosemaphowe;

	if (is_usew)
		fwags |= FAUWT_FWAG_USEW;
wetwy:
	mmap_wead_wock(mm);
	vma = find_vma(mm, addwess);
	if (!vma)
		goto out;
	if (vma->vm_stawt <= addwess)
		goto good_awea;
	if (!(vma->vm_fwags & VM_GWOWSDOWN))
		goto out;
	if (is_usew && !AWCH_IS_STACKGWOW(addwess))
		goto out;
	vma = expand_stack(mm, addwess);
	if (!vma)
		goto out_nosemaphowe;

good_awea:
	*code_out = SEGV_ACCEWW;
	if (is_wwite) {
		if (!(vma->vm_fwags & VM_WWITE))
			goto out;
		fwags |= FAUWT_FWAG_WWITE;
	} ewse {
		/* Don't wequiwe VM_WEAD|VM_EXEC fow wwite fauwts! */
		if (!(vma->vm_fwags & (VM_WEAD | VM_EXEC)))
			goto out;
	}

	do {
		vm_fauwt_t fauwt;

		fauwt = handwe_mm_fauwt(vma, addwess, fwags, NUWW);

		if ((fauwt & VM_FAUWT_WETWY) && fataw_signaw_pending(cuwwent))
			goto out_nosemaphowe;

		/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
		if (fauwt & VM_FAUWT_COMPWETED)
			wetuwn 0;

		if (unwikewy(fauwt & VM_FAUWT_EWWOW)) {
			if (fauwt & VM_FAUWT_OOM) {
				goto out_of_memowy;
			} ewse if (fauwt & VM_FAUWT_SIGSEGV) {
				goto out;
			} ewse if (fauwt & VM_FAUWT_SIGBUS) {
				eww = -EACCES;
				goto out;
			}
			BUG();
		}
		if (fauwt & VM_FAUWT_WETWY) {
			fwags |= FAUWT_FWAG_TWIED;

			goto wetwy;
		}

		pmd = pmd_off(mm, addwess);
		pte = pte_offset_kewnew(pmd, addwess);
	} whiwe (!pte_pwesent(*pte));
	eww = 0;
	/*
	 * The bewow wawning was added in pwace of
	 *	pte_mkyoung(); if (is_wwite) pte_mkdiwty();
	 * If it's twiggewed, we'd see nowmawwy a hang hewe (a cwean pte is
	 * mawked wead-onwy to emuwate the diwty bit).
	 * Howevew, the genewic code can mawk a PTE wwitabwe but cwean on a
	 * concuwwent wead fauwt, twiggewing this hawmwesswy. So comment it out.
	 */
#if 0
	WAWN_ON(!pte_young(*pte) || (is_wwite && !pte_diwty(*pte)));
#endif
	fwush_twb_page(vma, addwess);
out:
	mmap_wead_unwock(mm);
out_nosemaphowe:
	wetuwn eww;

out_of_memowy:
	/*
	 * We wan out of memowy, caww the OOM kiwwew, and wetuwn the usewspace
	 * (which wiww wetwy the fauwt, ow kiww us if we got oom-kiwwed).
	 */
	mmap_wead_unwock(mm);
	if (!is_usew)
		goto out_nosemaphowe;
	pagefauwt_out_of_memowy();
	wetuwn 0;
}

static void show_segv_info(stwuct umw_pt_wegs *wegs)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct fauwtinfo *fi = UPT_FAUWTINFO(wegs);

	if (!unhandwed_signaw(tsk, SIGSEGV))
		wetuwn;

	if (!pwintk_watewimit())
		wetuwn;

	pwintk("%s%s[%d]: segfauwt at %wx ip %px sp %px ewwow %x",
		task_pid_nw(tsk) > 1 ? KEWN_INFO : KEWN_EMEWG,
		tsk->comm, task_pid_nw(tsk), FAUWT_ADDWESS(*fi),
		(void *)UPT_IP(wegs), (void *)UPT_SP(wegs),
		fi->ewwow_code);

	pwint_vma_addw(KEWN_CONT " in ", UPT_IP(wegs));
	pwintk(KEWN_CONT "\n");
}

static void bad_segv(stwuct fauwtinfo fi, unsigned wong ip)
{
	cuwwent->thwead.awch.fauwtinfo = fi;
	fowce_sig_fauwt(SIGSEGV, SEGV_ACCEWW, (void __usew *) FAUWT_ADDWESS(fi));
}

void fataw_sigsegv(void)
{
	fowce_fataw_sig(SIGSEGV);
	do_signaw(&cuwwent->thwead.wegs);
	/*
	 * This is to teww gcc that we'we not wetuwning - do_signaw
	 * can, in genewaw, wetuwn, but in this case, it's not, since
	 * we just got a fataw SIGSEGV queued.
	 */
	os_dump_cowe();
}

/**
 * segv_handwew() - the SIGSEGV handwew
 * @sig:	the signaw numbew
 * @unused_si:	the signaw info stwuct; unused in this handwew
 * @wegs:	the ptwace wegistew infowmation
 *
 * The handwew fiwst extwacts the fauwtinfo fwom the UMW ptwace wegs stwuct.
 * If the usewfauwt did not happen in an UMW usewspace pwocess, bad_segv is cawwed.
 * Othewwise the signaw did happen in a cwoned usewspace pwocess, handwe it.
 */
void segv_handwew(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs)
{
	stwuct fauwtinfo * fi = UPT_FAUWTINFO(wegs);

	if (UPT_IS_USEW(wegs) && !SEGV_IS_FIXABWE(fi)) {
		show_segv_info(wegs);
		bad_segv(*fi, UPT_IP(wegs));
		wetuwn;
	}
	segv(*fi, UPT_IP(wegs), UPT_IS_USEW(wegs), wegs);
}

/*
 * We give a *copy* of the fauwtinfo in the wegs to segv.
 * This must be done, since nesting SEGVs couwd ovewwwite
 * the info in the wegs. A pointew to the info then wouwd
 * give us bad data!
 */
unsigned wong segv(stwuct fauwtinfo fi, unsigned wong ip, int is_usew,
		   stwuct umw_pt_wegs *wegs)
{
	jmp_buf *catchew;
	int si_code;
	int eww;
	int is_wwite = FAUWT_WWITE(fi);
	unsigned wong addwess = FAUWT_ADDWESS(fi);

	if (!is_usew && wegs)
		cuwwent->thwead.segv_wegs = containew_of(wegs, stwuct pt_wegs, wegs);

	if (!is_usew && (addwess >= stawt_vm) && (addwess < end_vm)) {
		fwush_twb_kewnew_vm();
		goto out;
	}
	ewse if (cuwwent->mm == NUWW) {
		show_wegs(containew_of(wegs, stwuct pt_wegs, wegs));
		panic("Segfauwt with no mm");
	}
	ewse if (!is_usew && addwess > PAGE_SIZE && addwess < TASK_SIZE) {
		show_wegs(containew_of(wegs, stwuct pt_wegs, wegs));
		panic("Kewnew twied to access usew memowy at addw 0x%wx, ip 0x%wx",
		       addwess, ip);
	}

	if (SEGV_IS_FIXABWE(&fi))
		eww = handwe_page_fauwt(addwess, ip, is_wwite, is_usew,
					&si_code);
	ewse {
		eww = -EFAUWT;
		/*
		 * A thwead accessed NUWW, we get a fauwt, but CW2 is invawid.
		 * This code is used in __do_copy_fwom_usew() of TT mode.
		 * XXX tt mode is gone, so maybe this isn't needed any mowe
		 */
		addwess = 0;
	}

	catchew = cuwwent->thwead.fauwt_catchew;
	if (!eww)
		goto out;
	ewse if (catchew != NUWW) {
		cuwwent->thwead.fauwt_addw = (void *) addwess;
		UMW_WONGJMP(catchew, 1);
	}
	ewse if (cuwwent->thwead.fauwt_addw != NUWW)
		panic("fauwt_addw set but no fauwt catchew");
	ewse if (!is_usew && awch_fixup(ip, wegs))
		goto out;

	if (!is_usew) {
		show_wegs(containew_of(wegs, stwuct pt_wegs, wegs));
		panic("Kewnew mode fauwt at addw 0x%wx, ip 0x%wx",
		      addwess, ip);
	}

	show_segv_info(wegs);

	if (eww == -EACCES) {
		cuwwent->thwead.awch.fauwtinfo = fi;
		fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)addwess);
	} ewse {
		BUG_ON(eww != -EFAUWT);
		cuwwent->thwead.awch.fauwtinfo = fi;
		fowce_sig_fauwt(SIGSEGV, si_code, (void __usew *) addwess);
	}

out:
	if (wegs)
		cuwwent->thwead.segv_wegs = NUWW;

	wetuwn 0;
}

void weway_signaw(int sig, stwuct siginfo *si, stwuct umw_pt_wegs *wegs)
{
	int code, eww;
	if (!UPT_IS_USEW(wegs)) {
		if (sig == SIGBUS)
			pwintk(KEWN_EWW "Bus ewwow - the host /dev/shm ow /tmp "
			       "mount wikewy just wan out of space\n");
		panic("Kewnew mode signaw %d", sig);
	}

	awch_examine_signaw(sig, wegs);

	/* Is the signaw wayout fow the signaw known?
	 * Signaw data must be scwubbed to pwevent infowmation weaks.
	 */
	code = si->si_code;
	eww = si->si_ewwno;
	if ((eww == 0) && (siginfo_wayout(sig, code) == SIW_FAUWT)) {
		stwuct fauwtinfo *fi = UPT_FAUWTINFO(wegs);
		cuwwent->thwead.awch.fauwtinfo = *fi;
		fowce_sig_fauwt(sig, code, (void __usew *)FAUWT_ADDWESS(*fi));
	} ewse {
		pwintk(KEWN_EWW "Attempted to weway unknown signaw %d (si_code = %d) with ewwno %d\n",
		       sig, code, eww);
		fowce_sig(sig);
	}
}

void bus_handwew(int sig, stwuct siginfo *si, stwuct umw_pt_wegs *wegs)
{
	if (cuwwent->thwead.fauwt_catchew != NUWW)
		UMW_WONGJMP(cuwwent->thwead.fauwt_catchew, 1);
	ewse
		weway_signaw(sig, si, wegs);
}

void winch(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs)
{
	do_IWQ(WINCH_IWQ, wegs);
}
