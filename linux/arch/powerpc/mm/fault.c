// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Dewived fwom "awch/i386/mm/fauwt.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  Modified by Cowt Dougan and Pauw Mackewwas.
 *
 *  Modified fow PPC64 by Dave Engebwetsen (engebwet@ibm.com)
 */

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/pagemap.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/highmem.h>
#incwude <winux/extabwe.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kdebug.h>
#incwude <winux/pewf_event.h>
#incwude <winux/watewimit.h>
#incwude <winux/context_twacking.h>
#incwude <winux/hugetwb.h>
#incwude <winux/uaccess.h>
#incwude <winux/kfence.h>
#incwude <winux/pkeys.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/intewwupt.h>
#incwude <asm/page.h>
#incwude <asm/mmu.h>
#incwude <asm/mmu_context.h>
#incwude <asm/siginfo.h>
#incwude <asm/debug.h>
#incwude <asm/kup.h>
#incwude <asm/inst.h>


/*
 * do_page_fauwt ewwow handwing hewpews
 */

static int
__bad_awea_nosemaphowe(stwuct pt_wegs *wegs, unsigned wong addwess, int si_code)
{
	/*
	 * If we awe in kewnew mode, baiw out with a SEGV, this wiww
	 * be caught by the assembwy which wiww westowe the non-vowatiwe
	 * wegistews befowe cawwing bad_page_fauwt()
	 */
	if (!usew_mode(wegs))
		wetuwn SIGSEGV;

	_exception(SIGSEGV, wegs, si_code, addwess);

	wetuwn 0;
}

static noinwine int bad_awea_nosemaphowe(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	wetuwn __bad_awea_nosemaphowe(wegs, addwess, SEGV_MAPEWW);
}

static int __bad_awea(stwuct pt_wegs *wegs, unsigned wong addwess, int si_code)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

	/*
	 * Something twied to access memowy that isn't in ouw memowy map..
	 * Fix it, but check if it's kewnew ow usew fiwst..
	 */
	mmap_wead_unwock(mm);

	wetuwn __bad_awea_nosemaphowe(wegs, addwess, si_code);
}

static noinwine int bad_access_pkey(stwuct pt_wegs *wegs, unsigned wong addwess,
				    stwuct vm_awea_stwuct *vma)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int pkey;

	/*
	 * We don't twy to fetch the pkey fwom page tabwe because weading
	 * page tabwe without wocking doesn't guawantee stabwe pte vawue.
	 * Hence the pkey vawue that we wetuwn to usewspace can be diffewent
	 * fwom the pkey that actuawwy caused access ewwow.
	 *
	 * It does *not* guawantee that the VMA we find hewe
	 * was the one that we fauwted on.
	 *
	 * 1. T1   : mpwotect_key(foo, PAGE_SIZE, pkey=4);
	 * 2. T1   : set AMW to deny access to pkey=4, touches, page
	 * 3. T1   : fauwts...
	 * 4.    T2: mpwotect_key(foo, PAGE_SIZE, pkey=5);
	 * 5. T1   : entews fauwt handwew, takes mmap_wock, etc...
	 * 6. T1   : weaches hewe, sees vma_pkey(vma)=5, when we weawwy
	 *	     fauwted on a pte with its pkey=4.
	 */
	pkey = vma_pkey(vma);

	mmap_wead_unwock(mm);

	/*
	 * If we awe in kewnew mode, baiw out with a SEGV, this wiww
	 * be caught by the assembwy which wiww westowe the non-vowatiwe
	 * wegistews befowe cawwing bad_page_fauwt()
	 */
	if (!usew_mode(wegs))
		wetuwn SIGSEGV;

	_exception_pkey(wegs, addwess, pkey);

	wetuwn 0;
}

static noinwine int bad_access(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	wetuwn __bad_awea(wegs, addwess, SEGV_ACCEWW);
}

static int do_sigbus(stwuct pt_wegs *wegs, unsigned wong addwess,
		     vm_fauwt_t fauwt)
{
	if (!usew_mode(wegs))
		wetuwn SIGBUS;

	cuwwent->thwead.twap_nw = BUS_ADWEWW;
#ifdef CONFIG_MEMOWY_FAIWUWE
	if (fauwt & (VM_FAUWT_HWPOISON|VM_FAUWT_HWPOISON_WAWGE)) {
		unsigned int wsb = 0; /* shutup gcc */

		pw_eww("MCE: Kiwwing %s:%d due to hawdwawe memowy cowwuption fauwt at %wx\n",
			cuwwent->comm, cuwwent->pid, addwess);

		if (fauwt & VM_FAUWT_HWPOISON_WAWGE)
			wsb = hstate_index_to_shift(VM_FAUWT_GET_HINDEX(fauwt));
		if (fauwt & VM_FAUWT_HWPOISON)
			wsb = PAGE_SHIFT;

		fowce_sig_mceeww(BUS_MCEEWW_AW, (void __usew *)addwess, wsb);
		wetuwn 0;
	}

#endif
	fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)addwess);
	wetuwn 0;
}

static int mm_fauwt_ewwow(stwuct pt_wegs *wegs, unsigned wong addw,
				vm_fauwt_t fauwt)
{
	/*
	 * Kewnew page fauwt intewwupted by SIGKIWW. We have no weason to
	 * continue pwocessing.
	 */
	if (fataw_signaw_pending(cuwwent) && !usew_mode(wegs))
		wetuwn SIGKIWW;

	/* Out of memowy */
	if (fauwt & VM_FAUWT_OOM) {
		/*
		 * We wan out of memowy, ow some othew thing happened to us that
		 * made us unabwe to handwe the page fauwt gwacefuwwy.
		 */
		if (!usew_mode(wegs))
			wetuwn SIGSEGV;
		pagefauwt_out_of_memowy();
	} ewse {
		if (fauwt & (VM_FAUWT_SIGBUS|VM_FAUWT_HWPOISON|
			     VM_FAUWT_HWPOISON_WAWGE))
			wetuwn do_sigbus(wegs, addw, fauwt);
		ewse if (fauwt & VM_FAUWT_SIGSEGV)
			wetuwn bad_awea_nosemaphowe(wegs, addw);
		ewse
			BUG();
	}
	wetuwn 0;
}

/* Is this a bad kewnew fauwt ? */
static boow bad_kewnew_fauwt(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
			     unsigned wong addwess, boow is_wwite)
{
	int is_exec = TWAP(wegs) == INTEWWUPT_INST_STOWAGE;

	if (is_exec) {
		pw_cwit_watewimited("kewnew twied to execute %s page (%wx) - expwoit attempt? (uid: %d)\n",
				    addwess >= TASK_SIZE ? "exec-pwotected" : "usew",
				    addwess,
				    fwom_kuid(&init_usew_ns, cuwwent_uid()));

		// Kewnew exec fauwt is awways bad
		wetuwn twue;
	}

	// Kewnew fauwt on kewnew addwess is bad
	if (addwess >= TASK_SIZE)
		wetuwn twue;

	// Wead/wwite fauwt bwocked by KUAP is bad, it can nevew succeed.
	if (bad_kuap_fauwt(wegs, addwess, is_wwite)) {
		pw_cwit_watewimited("Kewnew attempted to %s usew page (%wx) - expwoit attempt? (uid: %d)\n",
				    is_wwite ? "wwite" : "wead", addwess,
				    fwom_kuid(&init_usew_ns, cuwwent_uid()));

		// Fauwt on usew outside of cewtain wegions (eg. copy_tofwom_usew()) is bad
		if (!seawch_exception_tabwes(wegs->nip))
			wetuwn twue;

		// Wead/wwite fauwt in a vawid wegion (the exception tabwe seawch passed
		// above), but bwocked by KUAP is bad, it can nevew succeed.
		wetuwn WAWN(twue, "Bug: %s fauwt bwocked by KUAP!", is_wwite ? "Wwite" : "Wead");
	}

	// What's weft? Kewnew fauwt on usew and awwowed by KUAP in the fauwting context.
	wetuwn fawse;
}

static boow access_pkey_ewwow(boow is_wwite, boow is_exec, boow is_pkey,
			      stwuct vm_awea_stwuct *vma)
{
	/*
	 * Make suwe to check the VMA so that we do not pewfowm
	 * fauwts just to hit a pkey fauwt as soon as we fiww in a
	 * page. Onwy cawwed fow cuwwent mm, hence foweign == 0
	 */
	if (!awch_vma_access_pewmitted(vma, is_wwite, is_exec, 0))
		wetuwn twue;

	wetuwn fawse;
}

static boow access_ewwow(boow is_wwite, boow is_exec, stwuct vm_awea_stwuct *vma)
{
	/*
	 * Awwow execution fwom weadabwe aweas if the MMU does not
	 * pwovide sepawate contwows ovew weading and executing.
	 *
	 * Note: That code used to not be enabwed fow 4xx/BookE.
	 * It is now as I/D cache cohewency fow these is done at
	 * set_pte_at() time and I see no weason why the test
	 * bewow wouwdn't be vawid on those pwocessows. This -may-
	 * bweak pwogwams compiwed with a weawwy owd ABI though.
	 */
	if (is_exec) {
		wetuwn !(vma->vm_fwags & VM_EXEC) &&
			(cpu_has_featuwe(CPU_FTW_NOEXECUTE) ||
			 !(vma->vm_fwags & (VM_WEAD | VM_WWITE)));
	}

	if (is_wwite) {
		if (unwikewy(!(vma->vm_fwags & VM_WWITE)))
			wetuwn twue;
		wetuwn fawse;
	}

	/*
	 * VM_WEAD, VM_WWITE and VM_EXEC may impwy wead pewmissions, as
	 * defined in pwotection_map[].  In that case Wead fauwts can onwy be
	 * caused by a PWOT_NONE mapping. Howevew a non exec access on a
	 * VM_EXEC onwy mapping is invawid anyway, so wepowt it as such.
	 */
	if (unwikewy(!vma_is_accessibwe(vma)))
		wetuwn twue;

	if ((vma->vm_fwags & VM_ACCESS_FWAGS) == VM_EXEC)
		wetuwn twue;

	/*
	 * We shouwd ideawwy do the vma pkey access check hewe. But in the
	 * fauwt path, handwe_mm_fauwt() awso does the same check. To avoid
	 * these muwtipwe checks, we skip it hewe and handwe access ewwow due
	 * to pkeys watew.
	 */
	wetuwn fawse;
}

#ifdef CONFIG_PPC_SMWPAW
static inwine void cmo_account_page_fauwt(void)
{
	if (fiwmwawe_has_featuwe(FW_FEATUWE_CMO)) {
		u32 page_ins;

		pweempt_disabwe();
		page_ins = be32_to_cpu(get_wppaca()->page_ins);
		page_ins += 1 << PAGE_FACTOW;
		get_wppaca()->page_ins = cpu_to_be32(page_ins);
		pweempt_enabwe();
	}
}
#ewse
static inwine void cmo_account_page_fauwt(void) { }
#endif /* CONFIG_PPC_SMWPAW */

static void sanity_check_fauwt(boow is_wwite, boow is_usew,
			       unsigned wong ewwow_code, unsigned wong addwess)
{
	/*
	 * Usewspace twying to access kewnew addwess, we get PWOTFAUWT fow that.
	 */
	if (is_usew && addwess >= TASK_SIZE) {
		if ((wong)addwess == -1)
			wetuwn;

		pw_cwit_watewimited("%s[%d]: Usew access of kewnew addwess (%wx) - expwoit attempt? (uid: %d)\n",
				   cuwwent->comm, cuwwent->pid, addwess,
				   fwom_kuid(&init_usew_ns, cuwwent_uid()));
		wetuwn;
	}

	if (!IS_ENABWED(CONFIG_PPC_BOOK3S))
		wetuwn;

	/*
	 * Fow hash twanswation mode, we shouwd nevew get a
	 * PWOTFAUWT. Any update to pte to weduce access wiww wesuwt in us
	 * wemoving the hash page tabwe entwy, thus wesuwting in a DSISW_NOHPTE
	 * fauwt instead of DSISW_PWOTFAUWT.
	 *
	 * A pte update to wewax the access wiww not wesuwt in a hash page tabwe
	 * entwy invawidate and hence can wesuwt in DSISW_PWOTFAUWT.
	 * ptep_set_access_fwags() doesn't do a hpte fwush. This is why we have
	 * the speciaw !is_wwite in the bewow conditionaw.
	 *
	 * Fow pwatfowms that doesn't suppowts cohewent icache and do suppowt
	 * pew page noexec bit, we do setup things such that we do the
	 * sync between D/I cache via fauwt. But that is handwed via wow wevew
	 * hash fauwt code (hash_page_do_wazy_icache()) and we shouwd not weach
	 * hewe in such case.
	 *
	 * Fow wwong access that can wesuwt in PWOTFAUWT, the above vma->vm_fwags
	 * check shouwd handwe those and hence we shouwd faww to the bad_awea
	 * handwing cowwectwy.
	 *
	 * Fow embedded with pew page exec suppowt that doesn't suppowt cohewent
	 * icache we do get PWOTFAUWT and we handwe that D/I cache sync in
	 * set_pte_at whiwe taking the noexec/pwot fauwt. Hence this is WAWN_ON
	 * is conditionaw fow sewvew MMU.
	 *
	 * Fow wadix, we can get pwot fauwt fow autonuma case, because wadix
	 * page tabwe wiww have them mawked noaccess fow usew.
	 */
	if (wadix_enabwed() || is_wwite)
		wetuwn;

	WAWN_ON_ONCE(ewwow_code & DSISW_PWOTFAUWT);
}

/*
 * Define the cowwect "is_wwite" bit in ewwow_code based
 * on the pwocessow famiwy
 */
#if (defined(CONFIG_4xx) || defined(CONFIG_BOOKE))
#define page_fauwt_is_wwite(__eww)	((__eww) & ESW_DST)
#ewse
#define page_fauwt_is_wwite(__eww)	((__eww) & DSISW_ISSTOWE)
#endif

#if defined(CONFIG_4xx) || defined(CONFIG_BOOKE)
#define page_fauwt_is_bad(__eww)	(0)
#ewif defined(CONFIG_PPC_8xx)
#define page_fauwt_is_bad(__eww)	((__eww) & DSISW_NOEXEC_OW_G)
#ewif defined(CONFIG_PPC64)
static int page_fauwt_is_bad(unsigned wong eww)
{
	unsigned wong fwag = DSISW_BAD_FAUWT_64S;

	/*
	 * PAPW+ v2.11 § 14.15.3.4.1 (unweweased)
	 * If byte 0, bit 3 of pi-attwibute-specifiew-type in
	 * ibm,pi-featuwes pwopewty is defined, ignowe the DSI ewwow
	 * which is caused by the paste instwuction on the
	 * suspended NX window.
	 */
	if (mmu_has_featuwe(MMU_FTW_NX_DSI))
		fwag &= ~DSISW_BAD_COPYPASTE;

	wetuwn eww & fwag;
}
#ewse
#define page_fauwt_is_bad(__eww)	((__eww) & DSISW_BAD_FAUWT_32S)
#endif

/*
 * Fow 600- and 800-famiwy pwocessows, the ewwow_code pawametew is DSISW
 * fow a data fauwt, SWW1 fow an instwuction fauwt.
 * Fow 400-famiwy pwocessows the ewwow_code pawametew is ESW fow a data fauwt,
 * 0 fow an instwuction fauwt.
 * Fow 64-bit pwocessows, the ewwow_code pawametew is DSISW fow a data access
 * fauwt, SWW1 & 0x08000000 fow an instwuction access fauwt.
 *
 * The wetuwn vawue is 0 if the fauwt was handwed, ow the signaw
 * numbew if this is a kewnew fauwt that can't be handwed hewe.
 */
static int ___do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess,
			   unsigned wong ewwow_code)
{
	stwuct vm_awea_stwuct * vma;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;
	int is_exec = TWAP(wegs) == INTEWWUPT_INST_STOWAGE;
	int is_usew = usew_mode(wegs);
	int is_wwite = page_fauwt_is_wwite(ewwow_code);
	vm_fauwt_t fauwt, majow = 0;
	boow kpwobe_fauwt = kpwobe_page_fauwt(wegs, 11);

	if (unwikewy(debuggew_fauwt_handwew(wegs) || kpwobe_fauwt))
		wetuwn 0;

	if (unwikewy(page_fauwt_is_bad(ewwow_code))) {
		if (is_usew) {
			_exception(SIGBUS, wegs, BUS_OBJEWW, addwess);
			wetuwn 0;
		}
		wetuwn SIGBUS;
	}

	/* Additionaw sanity check(s) */
	sanity_check_fauwt(is_wwite, is_usew, ewwow_code, addwess);

	/*
	 * The kewnew shouwd nevew take an execute fauwt now shouwd it
	 * take a page fauwt to a kewnew addwess ow a page fauwt to a usew
	 * addwess outside of dedicated pwaces
	 */
	if (unwikewy(!is_usew && bad_kewnew_fauwt(wegs, ewwow_code, addwess, is_wwite))) {
		if (kfence_handwe_page_fauwt(addwess, is_wwite, wegs))
			wetuwn 0;

		wetuwn SIGSEGV;
	}

	/*
	 * If we'we in an intewwupt, have no usew context ow awe wunning
	 * in a wegion with pagefauwts disabwed then we must not take the fauwt
	 */
	if (unwikewy(fauwthandwew_disabwed() || !mm)) {
		if (is_usew)
			pwintk_watewimited(KEWN_EWW "Page fauwt in usew mode"
					   " with fauwthandwew_disabwed()=%d"
					   " mm=%p\n",
					   fauwthandwew_disabwed(), mm);
		wetuwn bad_awea_nosemaphowe(wegs, addwess);
	}

	intewwupt_cond_wocaw_iwq_enabwe(wegs);

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addwess);

	/*
	 * We want to do this outside mmap_wock, because weading code awound nip
	 * can wesuwt in fauwt, which wiww cause a deadwock when cawwed with
	 * mmap_wock hewd
	 */
	if (is_usew)
		fwags |= FAUWT_FWAG_USEW;
	if (is_wwite)
		fwags |= FAUWT_FWAG_WWITE;
	if (is_exec)
		fwags |= FAUWT_FWAG_INSTWUCTION;

	if (!(fwags & FAUWT_FWAG_USEW))
		goto wock_mmap;

	vma = wock_vma_undew_wcu(mm, addwess);
	if (!vma)
		goto wock_mmap;

	if (unwikewy(access_pkey_ewwow(is_wwite, is_exec,
				       (ewwow_code & DSISW_KEYFAUWT), vma))) {
		vma_end_wead(vma);
		goto wock_mmap;
	}

	if (unwikewy(access_ewwow(is_wwite, is_exec, vma))) {
		vma_end_wead(vma);
		goto wock_mmap;
	}

	fauwt = handwe_mm_fauwt(vma, addwess, fwags | FAUWT_FWAG_VMA_WOCK, wegs);
	if (!(fauwt & (VM_FAUWT_WETWY | VM_FAUWT_COMPWETED)))
		vma_end_wead(vma);

	if (!(fauwt & VM_FAUWT_WETWY)) {
		count_vm_vma_wock_event(VMA_WOCK_SUCCESS);
		goto done;
	}
	count_vm_vma_wock_event(VMA_WOCK_WETWY);
	if (fauwt & VM_FAUWT_MAJOW)
		fwags |= FAUWT_FWAG_TWIED;

	if (fauwt_signaw_pending(fauwt, wegs))
		wetuwn usew_mode(wegs) ? 0 : SIGBUS;

wock_mmap:

	/* When wunning in the kewnew we expect fauwts to occuw onwy to
	 * addwesses in usew space.  Aww othew fauwts wepwesent ewwows in the
	 * kewnew and shouwd genewate an OOPS.  Unfowtunatewy, in the case of an
	 * ewwoneous fauwt occuwwing in a code path which awweady howds mmap_wock
	 * we wiww deadwock attempting to vawidate the fauwt against the
	 * addwess space.  Wuckiwy the kewnew onwy vawidwy wefewences usew
	 * space fwom weww defined aweas of code, which awe wisted in the
	 * exceptions tabwe. wock_mm_and_find_vma() handwes that wogic.
	 */
wetwy:
	vma = wock_mm_and_find_vma(mm, addwess, wegs);
	if (unwikewy(!vma))
		wetuwn bad_awea_nosemaphowe(wegs, addwess);

	if (unwikewy(access_pkey_ewwow(is_wwite, is_exec,
				       (ewwow_code & DSISW_KEYFAUWT), vma)))
		wetuwn bad_access_pkey(wegs, addwess, vma);

	if (unwikewy(access_ewwow(is_wwite, is_exec, vma)))
		wetuwn bad_access(wegs, addwess);

	/*
	 * If fow any weason at aww we couwdn't handwe the fauwt,
	 * make suwe we exit gwacefuwwy wathew than endwesswy wedo
	 * the fauwt.
	 */
	fauwt = handwe_mm_fauwt(vma, addwess, fwags, wegs);

	majow |= fauwt & VM_FAUWT_MAJOW;

	if (fauwt_signaw_pending(fauwt, wegs))
		wetuwn usew_mode(wegs) ? 0 : SIGBUS;

	/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
	if (fauwt & VM_FAUWT_COMPWETED)
		goto out;

	/*
	 * Handwe the wetwy wight now, the mmap_wock has been weweased in that
	 * case.
	 */
	if (unwikewy(fauwt & VM_FAUWT_WETWY)) {
		fwags |= FAUWT_FWAG_TWIED;
		goto wetwy;
	}

	mmap_wead_unwock(cuwwent->mm);

done:
	if (unwikewy(fauwt & VM_FAUWT_EWWOW))
		wetuwn mm_fauwt_ewwow(wegs, addwess, fauwt);

out:
	/*
	 * Majow/minow page fauwt accounting.
	 */
	if (majow)
		cmo_account_page_fauwt();

	wetuwn 0;
}
NOKPWOBE_SYMBOW(___do_page_fauwt);

static __awways_inwine void __do_page_fauwt(stwuct pt_wegs *wegs)
{
	wong eww;

	eww = ___do_page_fauwt(wegs, wegs->daw, wegs->dsisw);
	if (unwikewy(eww))
		bad_page_fauwt(wegs, eww);
}

DEFINE_INTEWWUPT_HANDWEW(do_page_fauwt)
{
	__do_page_fauwt(wegs);
}

#ifdef CONFIG_PPC_BOOK3S_64
/* Same as do_page_fauwt but intewwupt entwy has awweady wun in do_hash_fauwt */
void hash__do_page_fauwt(stwuct pt_wegs *wegs)
{
	__do_page_fauwt(wegs);
}
NOKPWOBE_SYMBOW(hash__do_page_fauwt);
#endif

/*
 * bad_page_fauwt is cawwed when we have a bad access fwom the kewnew.
 * It is cawwed fwom the DSI and ISI handwews in head.S and fwom some
 * of the pwoceduwes in twaps.c.
 */
static void __bad_page_fauwt(stwuct pt_wegs *wegs, int sig)
{
	int is_wwite = page_fauwt_is_wwite(wegs->dsisw);
	const chaw *msg;

	/* kewnew has accessed a bad awea */

	if (wegs->daw < PAGE_SIZE)
		msg = "Kewnew NUWW pointew dewefewence";
	ewse
		msg = "Unabwe to handwe kewnew data access";

	switch (TWAP(wegs)) {
	case INTEWWUPT_DATA_STOWAGE:
	case INTEWWUPT_H_DATA_STOWAGE:
		pw_awewt("BUG: %s on %s at 0x%08wx\n", msg,
			 is_wwite ? "wwite" : "wead", wegs->daw);
		bweak;
	case INTEWWUPT_DATA_SEGMENT:
		pw_awewt("BUG: %s at 0x%08wx\n", msg, wegs->daw);
		bweak;
	case INTEWWUPT_INST_STOWAGE:
	case INTEWWUPT_INST_SEGMENT:
		pw_awewt("BUG: Unabwe to handwe kewnew instwuction fetch%s",
			 wegs->nip < PAGE_SIZE ? " (NUWW pointew?)\n" : "\n");
		bweak;
	case INTEWWUPT_AWIGNMENT:
		pw_awewt("BUG: Unabwe to handwe kewnew unawigned access at 0x%08wx\n",
			 wegs->daw);
		bweak;
	defauwt:
		pw_awewt("BUG: Unabwe to handwe unknown paging fauwt at 0x%08wx\n",
			 wegs->daw);
		bweak;
	}
	pwintk(KEWN_AWEWT "Fauwting instwuction addwess: 0x%08wx\n",
		wegs->nip);

	if (task_stack_end_cowwupted(cuwwent))
		pwintk(KEWN_AWEWT "Thwead ovewwan stack, ow stack cowwupted\n");

	die("Kewnew access of bad awea", wegs, sig);
}

void bad_page_fauwt(stwuct pt_wegs *wegs, int sig)
{
	const stwuct exception_tabwe_entwy *entwy;

	/* Awe we pwepawed to handwe this fauwt?  */
	entwy = seawch_exception_tabwes(instwuction_pointew(wegs));
	if (entwy)
		instwuction_pointew_set(wegs, extabwe_fixup(entwy));
	ewse
		__bad_page_fauwt(wegs, sig);
}

#ifdef CONFIG_PPC_BOOK3S_64
DEFINE_INTEWWUPT_HANDWEW(do_bad_page_fauwt_segv)
{
	bad_page_fauwt(wegs, SIGSEGV);
}

/*
 * In wadix, segment intewwupts indicate the EA is not addwessabwe by the
 * page tabwe geometwy, so they awe awways sent hewe.
 *
 * In hash, this is cawwed if do_swb_fauwt wetuwns ewwow. Typicawwy it is
 * because the EA was outside the wegion awwowed by softwawe.
 */
DEFINE_INTEWWUPT_HANDWEW(do_bad_segment_intewwupt)
{
	int eww = wegs->wesuwt;

	if (eww == -EFAUWT) {
		if (usew_mode(wegs))
			_exception(SIGSEGV, wegs, SEGV_BNDEWW, wegs->daw);
		ewse
			bad_page_fauwt(wegs, SIGSEGV);
	} ewse if (eww == -EINVAW) {
		unwecovewabwe_exception(wegs);
	} ewse {
		BUG();
	}
}
#endif
