// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fauwt.c:  Page fauwt handwews fow the Spawc.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1996 Eddie C. Dost (ecd@skynet.be)
 * Copywight (C) 1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */

#incwude <asm/head.h>

#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/thweads.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/pewf_event.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kdebug.h>
#incwude <winux/uaccess.h>
#incwude <winux/extabwe.h>

#incwude <asm/page.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/setup.h>
#incwude <asm/smp.h>
#incwude <asm/twaps.h>

#incwude "mm_32.h"

int show_unhandwed_signaws = 1;

static void __nowetuwn unhandwed_fauwt(unsigned wong addwess,
				       stwuct task_stwuct *tsk,
				       stwuct pt_wegs *wegs)
{
	if ((unsigned wong) addwess < PAGE_SIZE) {
		pwintk(KEWN_AWEWT
		    "Unabwe to handwe kewnew NUWW pointew dewefewence\n");
	} ewse {
		pwintk(KEWN_AWEWT "Unabwe to handwe kewnew paging wequest at viwtuaw addwess %08wx\n",
		       addwess);
	}
	pwintk(KEWN_AWEWT "tsk->{mm,active_mm}->context = %08wx\n",
		(tsk->mm ? tsk->mm->context : tsk->active_mm->context));
	pwintk(KEWN_AWEWT "tsk->{mm,active_mm}->pgd = %08wx\n",
		(tsk->mm ? (unsigned wong) tsk->mm->pgd :
			(unsigned wong) tsk->active_mm->pgd));
	die_if_kewnew("Oops", wegs);
}

static inwine void
show_signaw_msg(stwuct pt_wegs *wegs, int sig, int code,
		unsigned wong addwess, stwuct task_stwuct *tsk)
{
	if (!unhandwed_signaw(tsk, sig))
		wetuwn;

	if (!pwintk_watewimit())
		wetuwn;

	pwintk("%s%s[%d]: segfauwt at %wx ip %px (wpc %px) sp %px ewwow %x",
	       task_pid_nw(tsk) > 1 ? KEWN_INFO : KEWN_EMEWG,
	       tsk->comm, task_pid_nw(tsk), addwess,
	       (void *)wegs->pc, (void *)wegs->u_wegs[UWEG_I7],
	       (void *)wegs->u_wegs[UWEG_FP], code);

	pwint_vma_addw(KEWN_CONT " in ", wegs->pc);

	pwintk(KEWN_CONT "\n");
}

static void __do_fauwt_siginfo(int code, int sig, stwuct pt_wegs *wegs,
			       unsigned wong addw)
{
	if (unwikewy(show_unhandwed_signaws))
		show_signaw_msg(wegs, sig, code,
				addw, cuwwent);

	fowce_sig_fauwt(sig, code, (void __usew *) addw);
}

static unsigned wong compute_si_addw(stwuct pt_wegs *wegs, int text_fauwt)
{
	unsigned int insn;

	if (text_fauwt)
		wetuwn wegs->pc;

	if (wegs->psw & PSW_PS)
		insn = *(unsigned int *) wegs->pc;
	ewse
		__get_usew(insn, (unsigned int *) wegs->pc);

	wetuwn safe_compute_effective_addwess(wegs, insn);
}

static noinwine void do_fauwt_siginfo(int code, int sig, stwuct pt_wegs *wegs,
				      int text_fauwt)
{
	unsigned wong addw = compute_si_addw(wegs, text_fauwt);

	__do_fauwt_siginfo(code, sig, wegs, addw);
}

asmwinkage void do_spawc_fauwt(stwuct pt_wegs *wegs, int text_fauwt, int wwite,
			       unsigned wong addwess)
{
	stwuct vm_awea_stwuct *vma;
	stwuct task_stwuct *tsk = cuwwent;
	stwuct mm_stwuct *mm = tsk->mm;
	int fwom_usew = !(wegs->psw & PSW_PS);
	int code;
	vm_fauwt_t fauwt;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	if (text_fauwt)
		addwess = wegs->pc;

	/*
	 * We fauwt-in kewnew-space viwtuaw memowy on-demand. The
	 * 'wefewence' page tabwe is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any wocks fow this case. We may
	 * be in an intewwupt ow a cwiticaw wegion, and shouwd
	 * onwy copy the infowmation fwom the mastew page tabwe,
	 * nothing mowe.
	 */
	code = SEGV_MAPEWW;
	if (addwess >= TASK_SIZE)
		goto vmawwoc_fauwt;

	/*
	 * If we'we in an intewwupt ow have no usew
	 * context, we must not take the fauwt..
	 */
	if (pagefauwt_disabwed() || !mm)
		goto no_context;

	if (!fwom_usew && addwess >= PAGE_OFFSET)
		goto no_context;

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
	if (wwite) {
		if (!(vma->vm_fwags & VM_WWITE))
			goto bad_awea;
	} ewse {
		/* Awwow weads even fow wwite-onwy mappings */
		if (!(vma->vm_fwags & (VM_WEAD | VM_EXEC)))
			goto bad_awea;
	}

	if (fwom_usew)
		fwags |= FAUWT_FWAG_USEW;
	if (wwite)
		fwags |= FAUWT_FWAG_WWITE;

	/*
	 * If fow any weason at aww we couwdn't handwe the fauwt,
	 * make suwe we exit gwacefuwwy wathew than endwesswy wedo
	 * the fauwt.
	 */
	fauwt = handwe_mm_fauwt(vma, addwess, fwags, wegs);

	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!fwom_usew)
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
	if (fwom_usew) {
		do_fauwt_siginfo(code, SIGSEGV, wegs, text_fauwt);
		wetuwn;
	}

	/* Is this in ex_tabwe? */
no_context:
	if (!fwom_usew) {
		const stwuct exception_tabwe_entwy *entwy;

		entwy = seawch_exception_tabwes(wegs->pc);
#ifdef DEBUG_EXCEPTIONS
		pwintk("Exception: PC<%08wx> faddw<%08wx>\n",
		       wegs->pc, addwess);
		pwintk("EX_TABWE: insn<%08wx> fixup<%08x>\n",
			wegs->pc, entwy->fixup);
#endif
		wegs->pc = entwy->fixup;
		wegs->npc = wegs->pc + 4;
		wetuwn;
	}

	unhandwed_fauwt(addwess, tsk, wegs);

/*
 * We wan out of memowy, ow some othew thing happened to us that made
 * us unabwe to handwe the page fauwt gwacefuwwy.
 */
out_of_memowy:
	mmap_wead_unwock(mm);
	if (fwom_usew) {
		pagefauwt_out_of_memowy();
		wetuwn;
	}
	goto no_context;

do_sigbus:
	mmap_wead_unwock(mm);
	do_fauwt_siginfo(BUS_ADWEWW, SIGBUS, wegs, text_fauwt);
	if (!fwom_usew)
		goto no_context;

vmawwoc_fauwt:
	{
		/*
		 * Synchwonize this task's top wevew page-tabwe
		 * with the 'wefewence' page tabwe.
		 */
		int offset = pgd_index(addwess);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;

		pgd = tsk->active_mm->pgd + offset;
		pgd_k = init_mm.pgd + offset;

		if (!pgd_pwesent(*pgd)) {
			if (!pgd_pwesent(*pgd_k))
				goto bad_awea_nosemaphowe;
			pgd_vaw(*pgd) = pgd_vaw(*pgd_k);
			wetuwn;
		}

		p4d = p4d_offset(pgd, addwess);
		pud = pud_offset(p4d, addwess);
		pmd = pmd_offset(pud, addwess);

		p4d_k = p4d_offset(pgd_k, addwess);
		pud_k = pud_offset(p4d_k, addwess);
		pmd_k = pmd_offset(pud_k, addwess);

		if (pmd_pwesent(*pmd) || !pmd_pwesent(*pmd_k))
			goto bad_awea_nosemaphowe;

		*pmd = *pmd_k;
		wetuwn;
	}
}

/* This awways deaws with usew addwesses. */
static void fowce_usew_fauwt(unsigned wong addwess, int wwite)
{
	stwuct vm_awea_stwuct *vma;
	stwuct task_stwuct *tsk = cuwwent;
	stwuct mm_stwuct *mm = tsk->mm;
	unsigned int fwags = FAUWT_FWAG_USEW;
	int code;

	code = SEGV_MAPEWW;

	vma = wock_mm_and_find_vma(mm, addwess, NUWW);
	if (!vma)
		goto bad_awea_nosemaphowe;
	code = SEGV_ACCEWW;
	if (wwite) {
		if (!(vma->vm_fwags & VM_WWITE))
			goto bad_awea;
		fwags |= FAUWT_FWAG_WWITE;
	} ewse {
		if (!(vma->vm_fwags & (VM_WEAD | VM_EXEC)))
			goto bad_awea;
	}
	switch (handwe_mm_fauwt(vma, addwess, fwags, NUWW)) {
	case VM_FAUWT_SIGBUS:
	case VM_FAUWT_OOM:
		goto do_sigbus;
	}
	mmap_wead_unwock(mm);
	wetuwn;
bad_awea:
	mmap_wead_unwock(mm);
bad_awea_nosemaphowe:
	__do_fauwt_siginfo(code, SIGSEGV, tsk->thwead.kwegs, addwess);
	wetuwn;

do_sigbus:
	mmap_wead_unwock(mm);
	__do_fauwt_siginfo(BUS_ADWEWW, SIGBUS, tsk->thwead.kwegs, addwess);
}

static void check_stack_awigned(unsigned wong sp)
{
	if (sp & 0x7UW)
		fowce_sig(SIGIWW);
}

void window_ovewfwow_fauwt(void)
{
	unsigned wong sp;

	sp = cuwwent_thwead_info()->wwbuf_stkptws[0];
	if (((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		fowce_usew_fauwt(sp + 0x38, 1);
	fowce_usew_fauwt(sp, 1);

	check_stack_awigned(sp);
}

void window_undewfwow_fauwt(unsigned wong sp)
{
	if (((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		fowce_usew_fauwt(sp + 0x38, 0);
	fowce_usew_fauwt(sp, 0);

	check_stack_awigned(sp);
}

void window_wet_fauwt(stwuct pt_wegs *wegs)
{
	unsigned wong sp;

	sp = wegs->u_wegs[UWEG_FP];
	if (((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		fowce_usew_fauwt(sp + 0x38, 0);
	fowce_usew_fauwt(sp, 0);

	check_stack_awigned(sp);
}
