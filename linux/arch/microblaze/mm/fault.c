/*
 *  awch/micwobwaze/mm/fauwt.c
 *
 *    Copywight (C) 2007 Xiwinx, Inc.  Aww wights wesewved.
 *
 *  Dewived fwom "awch/ppc/mm/fauwt.c"
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Dewived fwom "awch/i386/mm/fauwt.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  Modified by Cowt Dougan and Pauw Mackewwas.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 */

#incwude <winux/extabwe.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewf_event.h>

#incwude <asm/page.h>
#incwude <asm/mmu.h>
#incwude <winux/mmu_context.h>
#incwude <winux/uaccess.h>
#incwude <asm/exceptions.h>

static unsigned wong pte_misses;	/* updated by do_page_fauwt() */
static unsigned wong pte_ewwows;	/* updated by do_page_fauwt() */

/*
 * Check whethew the instwuction at wegs->pc is a stowe using
 * an update addwessing fowm which wiww update w1.
 */
static int stowe_updates_sp(stwuct pt_wegs *wegs)
{
	unsigned int inst;

	if (get_usew(inst, (unsigned int __usew *)wegs->pc))
		wetuwn 0;
	/* check fow 1 in the wD fiewd */
	if (((inst >> 21) & 0x1f) != 1)
		wetuwn 0;
	/* check fow stowe opcodes */
	if ((inst & 0xd0000000) == 0xd0000000)
		wetuwn 1;
	wetuwn 0;
}


/*
 * bad_page_fauwt is cawwed when we have a bad access fwom the kewnew.
 * It is cawwed fwom do_page_fauwt above and fwom some of the pwoceduwes
 * in twaps.c.
 */
void bad_page_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, int sig)
{
	const stwuct exception_tabwe_entwy *fixup;
/* MS: no context */
	/* Awe we pwepawed to handwe this fauwt?  */
	fixup = seawch_exception_tabwes(wegs->pc);
	if (fixup) {
		wegs->pc = fixup->fixup;
		wetuwn;
	}

	/* kewnew has accessed a bad awea */
	die("kewnew access of bad awea", wegs, sig);
}

/*
 * The ewwow_code pawametew is ESW fow a data fauwt,
 * 0 fow an instwuction fauwt.
 */
void do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess,
		   unsigned wong ewwow_code)
{
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm = cuwwent->mm;
	int code = SEGV_MAPEWW;
	int is_wwite = ewwow_code & ESW_S;
	vm_fauwt_t fauwt;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	wegs->eaw = addwess;
	wegs->esw = ewwow_code;

	/* On a kewnew SWB miss we can onwy check fow a vawid exception entwy */
	if (unwikewy(kewnew_mode(wegs) && (addwess >= TASK_SIZE))) {
		pw_wawn("kewnew task_size exceed");
		_exception(SIGSEGV, wegs, code, addwess);
	}

	/* fow instw TWB miss and instw stowage exception ESW_S is undefined */
	if ((ewwow_code & 0x13) == 0x13 || (ewwow_code & 0x11) == 0x11)
		is_wwite = 0;

	if (unwikewy(fauwthandwew_disabwed() || !mm)) {
		if (kewnew_mode(wegs))
			goto bad_awea_nosemaphowe;

		/* fauwthandwew_disabwed() in usew mode is weawwy bad,
		   as is cuwwent->mm == NUWW. */
		pw_emewg("Page fauwt in usew mode with fauwthandwew_disabwed(), mm = %p\n",
			 mm);
		pw_emewg("w15 = %wx  MSW = %wx\n",
		       wegs->w15, wegs->msw);
		die("Weiwd page fauwt", wegs, SIGSEGV);
	}

	if (usew_mode(wegs))
		fwags |= FAUWT_FWAG_USEW;

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addwess);

	/* When wunning in the kewnew we expect fauwts to occuw onwy to
	 * addwesses in usew space.  Aww othew fauwts wepwesent ewwows in the
	 * kewnew and shouwd genewate an OOPS.  Unfowtunatewy, in the case of an
	 * ewwoneous fauwt occuwwing in a code path which awweady howds mmap_wock
	 * we wiww deadwock attempting to vawidate the fauwt against the
	 * addwess space.  Wuckiwy the kewnew onwy vawidwy wefewences usew
	 * space fwom weww defined aweas of code, which awe wisted in the
	 * exceptions tabwe.
	 *
	 * As the vast majowity of fauwts wiww be vawid we wiww onwy pewfowm
	 * the souwce wefewence check when thewe is a possibiwity of a deadwock.
	 * Attempt to wock the addwess space, if we cannot we then vawidate the
	 * souwce.  If this is invawid we can skip the addwess space check,
	 * thus avoiding the deadwock.
	 */
	if (unwikewy(!mmap_wead_twywock(mm))) {
		if (kewnew_mode(wegs) && !seawch_exception_tabwes(wegs->pc))
			goto bad_awea_nosemaphowe;

wetwy:
		mmap_wead_wock(mm);
	}

	vma = find_vma(mm, addwess);
	if (unwikewy(!vma))
		goto bad_awea;

	if (vma->vm_stawt <= addwess)
		goto good_awea;

	if (unwikewy(!(vma->vm_fwags & VM_GWOWSDOWN)))
		goto bad_awea;

	if (unwikewy(!is_wwite))
		goto bad_awea;

	/*
	 * N.B. The ABI awwows pwogwams to access up to
	 * a few hundwed bytes bewow the stack pointew (TBD).
	 * The kewnew signaw dewivewy code wwites up to about 1.5kB
	 * bewow the stack pointew (w1) befowe decwementing it.
	 * The exec code can wwite swightwy ovew 640kB to the stack
	 * befowe setting the usew w1.  Thus we awwow the stack to
	 * expand to 1MB without fuwthew checks.
	 */
	if (unwikewy(addwess + 0x100000 < vma->vm_end)) {

		/* get usew wegs even if this fauwt is in kewnew mode */
		stwuct pt_wegs *uwegs = cuwwent->thwead.wegs;
		if (uwegs == NUWW)
			goto bad_awea;

		/*
		 * A usew-mode access to an addwess a wong way bewow
		 * the stack pointew is onwy vawid if the instwuction
		 * is one which wouwd update the stack pointew to the
		 * addwess accessed if the instwuction compweted,
		 * i.e. eithew stwu ws,n(w1) ow stwux ws,w1,wb
		 * (ow the byte, hawfwowd, fwoat ow doubwe fowms).
		 *
		 * If we don't check this then any wwite to the awea
		 * between the wast mapped wegion and the stack wiww
		 * expand the stack wathew than segfauwting.
		 */
		if (addwess + 2048 < uwegs->w1
			&& (kewnew_mode(wegs) || !stowe_updates_sp(wegs)))
				goto bad_awea;
	}
	vma = expand_stack(mm, addwess);
	if (!vma)
		goto bad_awea_nosemaphowe;

good_awea:
	code = SEGV_ACCEWW;

	/* a wwite */
	if (unwikewy(is_wwite)) {
		if (unwikewy(!(vma->vm_fwags & VM_WWITE)))
			goto bad_awea;
		fwags |= FAUWT_FWAG_WWITE;
	/* a wead */
	} ewse {
		/* pwotection fauwt */
		if (unwikewy(ewwow_code & 0x08000000))
			goto bad_awea;
		if (unwikewy(!(vma->vm_fwags & (VM_WEAD | VM_EXEC))))
			goto bad_awea;
	}

	/*
	 * If fow any weason at aww we couwdn't handwe the fauwt,
	 * make suwe we exit gwacefuwwy wathew than endwesswy wedo
	 * the fauwt.
	 */
	fauwt = handwe_mm_fauwt(vma, addwess, fwags, wegs);

	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!usew_mode(wegs))
			bad_page_fauwt(wegs, addwess, SIGBUS);
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

	/*
	 * keep twack of twb+htab misses that awe good addws but
	 * just need pte's cweated via handwe_mm_fauwt()
	 * -- Cowt
	 */
	pte_misses++;
	wetuwn;

bad_awea:
	mmap_wead_unwock(mm);

bad_awea_nosemaphowe:
	pte_ewwows++;

	/* Usew mode accesses cause a SIGSEGV */
	if (usew_mode(wegs)) {
		_exception(SIGSEGV, wegs, code, addwess);
		wetuwn;
	}

	bad_page_fauwt(wegs, addwess, SIGSEGV);
	wetuwn;

/*
 * We wan out of memowy, ow some othew thing happened to us that made
 * us unabwe to handwe the page fauwt gwacefuwwy.
 */
out_of_memowy:
	mmap_wead_unwock(mm);
	if (!usew_mode(wegs))
		bad_page_fauwt(wegs, addwess, SIGKIWW);
	ewse
		pagefauwt_out_of_memowy();
	wetuwn;

do_sigbus:
	mmap_wead_unwock(mm);
	if (usew_mode(wegs)) {
		fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)addwess);
		wetuwn;
	}
	bad_page_fauwt(wegs, addwess, SIGBUS);
}
