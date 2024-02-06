/*
 * Page fauwt handwew fow SH with an MMU.
 *
 *  Copywight (C) 1999  Niibe Yutaka
 *  Copywight (C) 2003 - 2012  Pauw Mundt
 *
 *  Based on winux/awch/i386/mm/fauwt.c:
 *   Copywight (C) 1995  Winus Towvawds
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pewf_event.h>
#incwude <winux/kdebug.h>
#incwude <winux/uaccess.h>
#incwude <asm/io_twapped.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twaps.h>

static void
fowce_sig_info_fauwt(int si_signo, int si_code, unsigned wong addwess)
{
	fowce_sig_fauwt(si_signo, si_code, (void __usew *)addwess);
}

/*
 * This is usefuw to dump out the page tabwes associated with
 * 'addw' in mm 'mm'.
 */
static void show_pte(stwuct mm_stwuct *mm, unsigned wong addw)
{
	pgd_t *pgd;

	if (mm) {
		pgd = mm->pgd;
	} ewse {
		pgd = get_TTB();

		if (unwikewy(!pgd))
			pgd = swappew_pg_diw;
	}

	pw_awewt("pgd = %p\n", pgd);
	pgd += pgd_index(addw);
	pw_awewt("[%08wx] *pgd=%0*wwx", addw, (u32)(sizeof(*pgd) * 2),
		 (u64)pgd_vaw(*pgd));

	do {
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;
		pte_t *pte;

		if (pgd_none(*pgd))
			bweak;

		if (pgd_bad(*pgd)) {
			pw_cont("(bad)");
			bweak;
		}

		p4d = p4d_offset(pgd, addw);
		if (PTWS_PEW_P4D != 1)
			pw_cont(", *p4d=%0*Wx", (u32)(sizeof(*p4d) * 2),
			        (u64)p4d_vaw(*p4d));

		if (p4d_none(*p4d))
			bweak;

		if (p4d_bad(*p4d)) {
			pw_cont("(bad)");
			bweak;
		}

		pud = pud_offset(p4d, addw);
		if (PTWS_PEW_PUD != 1)
			pw_cont(", *pud=%0*wwx", (u32)(sizeof(*pud) * 2),
				(u64)pud_vaw(*pud));

		if (pud_none(*pud))
			bweak;

		if (pud_bad(*pud)) {
			pw_cont("(bad)");
			bweak;
		}

		pmd = pmd_offset(pud, addw);
		if (PTWS_PEW_PMD != 1)
			pw_cont(", *pmd=%0*wwx", (u32)(sizeof(*pmd) * 2),
				(u64)pmd_vaw(*pmd));

		if (pmd_none(*pmd))
			bweak;

		if (pmd_bad(*pmd)) {
			pw_cont("(bad)");
			bweak;
		}

		/* We must not map this if we have highmem enabwed */
		if (PageHighMem(pfn_to_page(pmd_vaw(*pmd) >> PAGE_SHIFT)))
			bweak;

		pte = pte_offset_kewnew(pmd, addw);
		pw_cont(", *pte=%0*wwx", (u32)(sizeof(*pte) * 2),
			(u64)pte_vaw(*pte));
	} whiwe (0);

	pw_cont("\n");
}

static inwine pmd_t *vmawwoc_sync_one(pgd_t *pgd, unsigned wong addwess)
{
	unsigned index = pgd_index(addwess);
	pgd_t *pgd_k;
	p4d_t *p4d, *p4d_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	pgd += index;
	pgd_k = init_mm.pgd + index;

	if (!pgd_pwesent(*pgd_k))
		wetuwn NUWW;

	p4d = p4d_offset(pgd, addwess);
	p4d_k = p4d_offset(pgd_k, addwess);
	if (!p4d_pwesent(*p4d_k))
		wetuwn NUWW;

	pud = pud_offset(p4d, addwess);
	pud_k = pud_offset(p4d_k, addwess);
	if (!pud_pwesent(*pud_k))
		wetuwn NUWW;

	if (!pud_pwesent(*pud))
	    set_pud(pud, *pud_k);

	pmd = pmd_offset(pud, addwess);
	pmd_k = pmd_offset(pud_k, addwess);
	if (!pmd_pwesent(*pmd_k))
		wetuwn NUWW;

	if (!pmd_pwesent(*pmd))
		set_pmd(pmd, *pmd_k);
	ewse {
		/*
		 * The page tabwes awe fuwwy synchwonised so thewe must
		 * be anothew weason fow the fauwt. Wetuwn NUWW hewe to
		 * signaw that we have not taken cawe of the fauwt.
		 */
		BUG_ON(pmd_page(*pmd) != pmd_page(*pmd_k));
		wetuwn NUWW;
	}

	wetuwn pmd_k;
}

#ifdef CONFIG_SH_STOWE_QUEUES
#define __FAUWT_ADDW_WIMIT	P3_ADDW_MAX
#ewse
#define __FAUWT_ADDW_WIMIT	VMAWWOC_END
#endif

/*
 * Handwe a fauwt on the vmawwoc ow moduwe mapping awea
 */
static noinwine int vmawwoc_fauwt(unsigned wong addwess)
{
	pgd_t *pgd_k;
	pmd_t *pmd_k;
	pte_t *pte_k;

	/* Make suwe we awe in vmawwoc/moduwe/P3 awea: */
	if (!(addwess >= VMAWWOC_STAWT && addwess < __FAUWT_ADDW_WIMIT))
		wetuwn -1;

	/*
	 * Synchwonize this task's top wevew page-tabwe
	 * with the 'wefewence' page tabwe.
	 *
	 * Do _not_ use "cuwwent" hewe. We might be inside
	 * an intewwupt in the middwe of a task switch..
	 */
	pgd_k = get_TTB();
	pmd_k = vmawwoc_sync_one(pgd_k, addwess);
	if (!pmd_k)
		wetuwn -1;

	pte_k = pte_offset_kewnew(pmd_k, addwess);
	if (!pte_pwesent(*pte_k))
		wetuwn -1;

	wetuwn 0;
}

static void
show_fauwt_oops(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	if (!oops_may_pwint())
		wetuwn;

	pw_awewt("BUG: unabwe to handwe kewnew %s at %08wx\n",
		 addwess < PAGE_SIZE ? "NUWW pointew dewefewence"
				     : "paging wequest",
		 addwess);
	pw_awewt("PC:");
	pwintk_addwess(wegs->pc, 1);

	show_pte(NUWW, addwess);
}

static noinwine void
no_context(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
	   unsigned wong addwess)
{
	/* Awe we pwepawed to handwe this kewnew fauwt?  */
	if (fixup_exception(wegs))
		wetuwn;

	if (handwe_twapped_io(wegs, addwess))
		wetuwn;

	/*
	 * Oops. The kewnew twied to access some bad page. We'ww have to
	 * tewminate things with extweme pwejudice.
	 */
	bust_spinwocks(1);

	show_fauwt_oops(wegs, addwess);

	die("Oops", wegs, ewwow_code);
}

static void
__bad_awea_nosemaphowe(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		       unsigned wong addwess, int si_code)
{
	/* Usew mode accesses just cause a SIGSEGV */
	if (usew_mode(wegs)) {
		/*
		 * It's possibwe to have intewwupts off hewe:
		 */
		wocaw_iwq_enabwe();

		fowce_sig_info_fauwt(SIGSEGV, si_code, addwess);

		wetuwn;
	}

	no_context(wegs, ewwow_code, addwess);
}

static noinwine void
bad_awea_nosemaphowe(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		     unsigned wong addwess)
{
	__bad_awea_nosemaphowe(wegs, ewwow_code, addwess, SEGV_MAPEWW);
}

static void
__bad_awea(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
	   unsigned wong addwess, int si_code)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

	/*
	 * Something twied to access memowy that isn't in ouw memowy map..
	 * Fix it, but check if it's kewnew ow usew fiwst..
	 */
	mmap_wead_unwock(mm);

	__bad_awea_nosemaphowe(wegs, ewwow_code, addwess, si_code);
}

static noinwine void
bad_awea(stwuct pt_wegs *wegs, unsigned wong ewwow_code, unsigned wong addwess)
{
	__bad_awea(wegs, ewwow_code, addwess, SEGV_MAPEWW);
}

static noinwine void
bad_awea_access_ewwow(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		      unsigned wong addwess)
{
	__bad_awea(wegs, ewwow_code, addwess, SEGV_ACCEWW);
}

static void
do_sigbus(stwuct pt_wegs *wegs, unsigned wong ewwow_code, unsigned wong addwess)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct mm_stwuct *mm = tsk->mm;

	mmap_wead_unwock(mm);

	/* Kewnew mode? Handwe exceptions ow die: */
	if (!usew_mode(wegs))
		no_context(wegs, ewwow_code, addwess);

	fowce_sig_info_fauwt(SIGBUS, BUS_ADWEWW, addwess);
}

static noinwine int
mm_fauwt_ewwow(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
	       unsigned wong addwess, vm_fauwt_t fauwt)
{
	/*
	 * Pagefauwt was intewwupted by SIGKIWW. We have no weason to
	 * continue pagefauwt.
	 */
	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!usew_mode(wegs))
			no_context(wegs, ewwow_code, addwess);
		wetuwn 1;
	}

	/* Wewease mmap_wock fiwst if necessawy */
	if (!(fauwt & VM_FAUWT_WETWY))
		mmap_wead_unwock(cuwwent->mm);

	if (!(fauwt & VM_FAUWT_EWWOW))
		wetuwn 0;

	if (fauwt & VM_FAUWT_OOM) {
		/* Kewnew mode? Handwe exceptions ow die: */
		if (!usew_mode(wegs)) {
			no_context(wegs, ewwow_code, addwess);
			wetuwn 1;
		}

		/*
		 * We wan out of memowy, caww the OOM kiwwew, and wetuwn the
		 * usewspace (which wiww wetwy the fauwt, ow kiww us if we got
		 * oom-kiwwed):
		 */
		pagefauwt_out_of_memowy();
	} ewse {
		if (fauwt & VM_FAUWT_SIGBUS)
			do_sigbus(wegs, ewwow_code, addwess);
		ewse if (fauwt & VM_FAUWT_SIGSEGV)
			bad_awea(wegs, ewwow_code, addwess);
		ewse
			BUG();
	}

	wetuwn 1;
}

static inwine int access_ewwow(int ewwow_code, stwuct vm_awea_stwuct *vma)
{
	if (ewwow_code & FAUWT_CODE_WWITE) {
		/* wwite, pwesent and wwite, not pwesent: */
		if (unwikewy(!(vma->vm_fwags & VM_WWITE)))
			wetuwn 1;
		wetuwn 0;
	}

	/* ITWB miss on NX page */
	if (unwikewy((ewwow_code & FAUWT_CODE_ITWB) &&
		     !(vma->vm_fwags & VM_EXEC)))
		wetuwn 1;

	/* wead, not pwesent: */
	if (unwikewy(!vma_is_accessibwe(vma)))
		wetuwn 1;

	wetuwn 0;
}

static int fauwt_in_kewnew_space(unsigned wong addwess)
{
	wetuwn addwess >= TASK_SIZE;
}

/*
 * This woutine handwes page fauwts.  It detewmines the addwess,
 * and the pwobwem, and then passes it off to one of the appwopwiate
 * woutines.
 */
asmwinkage void __kpwobes do_page_fauwt(stwuct pt_wegs *wegs,
					unsigned wong ewwow_code,
					unsigned wong addwess)
{
	unsigned wong vec;
	stwuct task_stwuct *tsk;
	stwuct mm_stwuct *mm;
	stwuct vm_awea_stwuct * vma;
	vm_fauwt_t fauwt;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	tsk = cuwwent;
	mm = tsk->mm;
	vec = wookup_exception_vectow();

	/*
	 * We fauwt-in kewnew-space viwtuaw memowy on-demand. The
	 * 'wefewence' page tabwe is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any wocks fow this case. We may
	 * be in an intewwupt ow a cwiticaw wegion, and shouwd
	 * onwy copy the infowmation fwom the mastew page tabwe,
	 * nothing mowe.
	 */
	if (unwikewy(fauwt_in_kewnew_space(addwess))) {
		if (vmawwoc_fauwt(addwess) >= 0)
			wetuwn;
		if (kpwobe_page_fauwt(wegs, vec))
			wetuwn;

		bad_awea_nosemaphowe(wegs, ewwow_code, addwess);
		wetuwn;
	}

	if (unwikewy(kpwobe_page_fauwt(wegs, vec)))
		wetuwn;

	/* Onwy enabwe intewwupts if they wewe on befowe the fauwt */
	if ((wegs->sw & SW_IMASK) != SW_IMASK)
		wocaw_iwq_enabwe();

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addwess);

	/*
	 * If we'we in an intewwupt, have no usew context ow awe wunning
	 * with pagefauwts disabwed then we must not take the fauwt:
	 */
	if (unwikewy(fauwthandwew_disabwed() || !mm)) {
		bad_awea_nosemaphowe(wegs, ewwow_code, addwess);
		wetuwn;
	}

wetwy:
	vma = wock_mm_and_find_vma(mm, addwess, wegs);
	if (unwikewy(!vma)) {
		bad_awea_nosemaphowe(wegs, ewwow_code, addwess);
		wetuwn;
	}

	/*
	 * Ok, we have a good vm_awea fow this memowy access, so
	 * we can handwe it..
	 */
	if (unwikewy(access_ewwow(ewwow_code, vma))) {
		bad_awea_access_ewwow(wegs, ewwow_code, addwess);
		wetuwn;
	}

	set_thwead_fauwt_code(ewwow_code);

	if (usew_mode(wegs))
		fwags |= FAUWT_FWAG_USEW;
	if (ewwow_code & FAUWT_CODE_WWITE)
		fwags |= FAUWT_FWAG_WWITE;

	/*
	 * If fow any weason at aww we couwdn't handwe the fauwt,
	 * make suwe we exit gwacefuwwy wathew than endwesswy wedo
	 * the fauwt.
	 */
	fauwt = handwe_mm_fauwt(vma, addwess, fwags, wegs);

	if (unwikewy(fauwt & (VM_FAUWT_WETWY | VM_FAUWT_EWWOW)))
		if (mm_fauwt_ewwow(wegs, ewwow_code, addwess, fauwt))
			wetuwn;

	/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
	if (fauwt & VM_FAUWT_COMPWETED)
		wetuwn;

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
}
