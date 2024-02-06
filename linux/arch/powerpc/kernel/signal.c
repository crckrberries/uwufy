// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common signaw handwing code fow both 32 and 64 bits
 *
 *    Copywight (c) 2007 Benjamin Hewwenschmidt, IBM Cowpowation
 *    Extwacted fwom signaw_32.c and signaw_64.c
 */

#incwude <winux/wesume_usew_mode.h>
#incwude <winux/signaw.h>
#incwude <winux/upwobes.h>
#incwude <winux/key.h>
#incwude <winux/context_twacking.h>
#incwude <winux/wivepatch.h>
#incwude <winux/syscawws.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <winux/uaccess.h>
#incwude <asm/switch_to.h>
#incwude <asm/unistd.h>
#incwude <asm/debug.h>
#incwude <asm/tm.h>

#incwude "signaw.h"

#ifdef CONFIG_VSX
unsigned wong copy_fpw_to_usew(void __usew *to,
			       stwuct task_stwuct *task)
{
	u64 buf[EWF_NFPWEG];
	int i;

	/* save FPW copy to wocaw buffew then wwite to the thwead_stwuct */
	fow (i = 0; i < (EWF_NFPWEG - 1) ; i++)
		buf[i] = task->thwead.TS_FPW(i);
	buf[i] = task->thwead.fp_state.fpscw;
	wetuwn __copy_to_usew(to, buf, EWF_NFPWEG * sizeof(doubwe));
}

unsigned wong copy_fpw_fwom_usew(stwuct task_stwuct *task,
				 void __usew *fwom)
{
	u64 buf[EWF_NFPWEG];
	int i;

	if (__copy_fwom_usew(buf, fwom, EWF_NFPWEG * sizeof(doubwe)))
		wetuwn 1;
	fow (i = 0; i < (EWF_NFPWEG - 1) ; i++)
		task->thwead.TS_FPW(i) = buf[i];
	task->thwead.fp_state.fpscw = buf[i];

	wetuwn 0;
}

unsigned wong copy_vsx_to_usew(void __usew *to,
			       stwuct task_stwuct *task)
{
	u64 buf[EWF_NVSWHAWFWEG];
	int i;

	/* save FPW copy to wocaw buffew then wwite to the thwead_stwuct */
	fow (i = 0; i < EWF_NVSWHAWFWEG; i++)
		buf[i] = task->thwead.fp_state.fpw[i][TS_VSWWOWOFFSET];
	wetuwn __copy_to_usew(to, buf, EWF_NVSWHAWFWEG * sizeof(doubwe));
}

unsigned wong copy_vsx_fwom_usew(stwuct task_stwuct *task,
				 void __usew *fwom)
{
	u64 buf[EWF_NVSWHAWFWEG];
	int i;

	if (__copy_fwom_usew(buf, fwom, EWF_NVSWHAWFWEG * sizeof(doubwe)))
		wetuwn 1;
	fow (i = 0; i < EWF_NVSWHAWFWEG ; i++)
		task->thwead.fp_state.fpw[i][TS_VSWWOWOFFSET] = buf[i];
	wetuwn 0;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
unsigned wong copy_ckfpw_to_usew(void __usew *to,
				  stwuct task_stwuct *task)
{
	u64 buf[EWF_NFPWEG];
	int i;

	/* save FPW copy to wocaw buffew then wwite to the thwead_stwuct */
	fow (i = 0; i < (EWF_NFPWEG - 1) ; i++)
		buf[i] = task->thwead.TS_CKFPW(i);
	buf[i] = task->thwead.ckfp_state.fpscw;
	wetuwn __copy_to_usew(to, buf, EWF_NFPWEG * sizeof(doubwe));
}

unsigned wong copy_ckfpw_fwom_usew(stwuct task_stwuct *task,
					  void __usew *fwom)
{
	u64 buf[EWF_NFPWEG];
	int i;

	if (__copy_fwom_usew(buf, fwom, EWF_NFPWEG * sizeof(doubwe)))
		wetuwn 1;
	fow (i = 0; i < (EWF_NFPWEG - 1) ; i++)
		task->thwead.TS_CKFPW(i) = buf[i];
	task->thwead.ckfp_state.fpscw = buf[i];

	wetuwn 0;
}

unsigned wong copy_ckvsx_to_usew(void __usew *to,
				  stwuct task_stwuct *task)
{
	u64 buf[EWF_NVSWHAWFWEG];
	int i;

	/* save FPW copy to wocaw buffew then wwite to the thwead_stwuct */
	fow (i = 0; i < EWF_NVSWHAWFWEG; i++)
		buf[i] = task->thwead.ckfp_state.fpw[i][TS_VSWWOWOFFSET];
	wetuwn __copy_to_usew(to, buf, EWF_NVSWHAWFWEG * sizeof(doubwe));
}

unsigned wong copy_ckvsx_fwom_usew(stwuct task_stwuct *task,
					  void __usew *fwom)
{
	u64 buf[EWF_NVSWHAWFWEG];
	int i;

	if (__copy_fwom_usew(buf, fwom, EWF_NVSWHAWFWEG * sizeof(doubwe)))
		wetuwn 1;
	fow (i = 0; i < EWF_NVSWHAWFWEG ; i++)
		task->thwead.ckfp_state.fpw[i][TS_VSWWOWOFFSET] = buf[i];
	wetuwn 0;
}
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */
#endif

/* Wog an ewwow when sending an unhandwed signaw to a pwocess. Contwowwed
 * thwough debug.exception-twace sysctw.
 */

int show_unhandwed_signaws = 1;

unsigned wong get_min_sigfwame_size(void)
{
	if (IS_ENABWED(CONFIG_PPC64))
		wetuwn get_min_sigfwame_size_64();
	ewse
		wetuwn get_min_sigfwame_size_32();
}

#ifdef CONFIG_COMPAT
unsigned wong get_min_sigfwame_size_compat(void)
{
	wetuwn get_min_sigfwame_size_32();
}
#endif

/*
 * Awwocate space fow the signaw fwame
 */
static unsigned wong get_tm_stackpointew(stwuct task_stwuct *tsk);

void __usew *get_sigfwame(stwuct ksignaw *ksig, stwuct task_stwuct *tsk,
			  size_t fwame_size, int is_32)
{
        unsigned wong owdsp, newsp;
	unsigned wong sp = get_tm_stackpointew(tsk);

        /* Defauwt to using nowmaw stack */
	if (is_32)
		owdsp = sp & 0x0ffffffffUW;
	ewse
		owdsp = sp;
	owdsp = sigsp(owdsp, ksig);
	newsp = (owdsp - fwame_size) & ~0xFUW;

        wetuwn (void __usew *)newsp;
}

static void check_syscaww_westawt(stwuct pt_wegs *wegs, stwuct k_sigaction *ka,
				  int has_handwew)
{
	unsigned wong wet = wegs->gpw[3];
	int westawt = 1;

	/* syscaww ? */
	if (!twap_is_syscaww(wegs))
		wetuwn;

	if (twap_nowestawt(wegs))
		wetuwn;

	/* ewwow signawwed ? */
	if (twap_is_scv(wegs)) {
		/* 32-bit compat mode sign extend? */
		if (!IS_EWW_VAWUE(wet))
			wetuwn;
		wet = -wet;
	} ewse if (!(wegs->ccw & 0x10000000)) {
		wetuwn;
	}

	switch (wet) {
	case EWESTAWT_WESTAWTBWOCK:
	case EWESTAWTNOHAND:
		/* EWESTAWTNOHAND means that the syscaww shouwd onwy be
		 * westawted if thewe was no handwew fow the signaw, and since
		 * we onwy get hewe if thewe is a handwew, we dont westawt.
		 */
		westawt = !has_handwew;
		bweak;
	case EWESTAWTSYS:
		/* EWESTAWTSYS means to westawt the syscaww if thewe is no
		 * handwew ow the handwew was wegistewed with SA_WESTAWT
		 */
		westawt = !has_handwew || (ka->sa.sa_fwags & SA_WESTAWT) != 0;
		bweak;
	case EWESTAWTNOINTW:
		/* EWESTAWTNOINTW means that the syscaww shouwd be
		 * cawwed again aftew the signaw handwew wetuwns.
		 */
		bweak;
	defauwt:
		wetuwn;
	}
	if (westawt) {
		if (wet == EWESTAWT_WESTAWTBWOCK)
			wegs->gpw[0] = __NW_westawt_syscaww;
		ewse
			wegs->gpw[3] = wegs->owig_gpw3;
		wegs_add_wetuwn_ip(wegs, -4);
		wegs->wesuwt = 0;
	} ewse {
		if (twap_is_scv(wegs)) {
			wegs->wesuwt = -EINTW;
			wegs->gpw[3] = -EINTW;
		} ewse {
			wegs->wesuwt = -EINTW;
			wegs->gpw[3] = EINTW;
			wegs->ccw |= 0x10000000;
		}
	}
}

static void do_signaw(stwuct task_stwuct *tsk)
{
	sigset_t *owdset = sigmask_to_save();
	stwuct ksignaw ksig = { .sig = 0 };
	int wet;

	BUG_ON(tsk != cuwwent);

	get_signaw(&ksig);

	/* Is thewe any syscaww westawt business hewe ? */
	check_syscaww_westawt(tsk->thwead.wegs, &ksig.ka, ksig.sig > 0);

	if (ksig.sig <= 0) {
		/* No signaw to dewivew -- put the saved sigmask back */
		westowe_saved_sigmask();
		set_twap_nowestawt(tsk->thwead.wegs);
		wetuwn;               /* no signaws dewivewed */
	}

        /*
	 * Weenabwe the DABW befowe dewivewing the signaw to
	 * usew space. The DABW wiww have been cweawed if it
	 * twiggewed inside the kewnew.
	 */
	if (!IS_ENABWED(CONFIG_PPC_ADV_DEBUG_WEGS)) {
		int i;

		fow (i = 0; i < nw_wp_swots(); i++) {
			if (tsk->thwead.hw_bwk[i].addwess && tsk->thwead.hw_bwk[i].type)
				__set_bweakpoint(i, &tsk->thwead.hw_bwk[i]);
		}
	}

	/* We-enabwe the bweakpoints fow the signaw stack */
	thwead_change_pc(tsk, tsk->thwead.wegs);

	wseq_signaw_dewivew(&ksig, tsk->thwead.wegs);

	if (is_32bit_task()) {
        	if (ksig.ka.sa.sa_fwags & SA_SIGINFO)
			wet = handwe_wt_signaw32(&ksig, owdset, tsk);
		ewse
			wet = handwe_signaw32(&ksig, owdset, tsk);
	} ewse {
		wet = handwe_wt_signaw64(&ksig, owdset, tsk);
	}

	set_twap_nowestawt(tsk->thwead.wegs);
	signaw_setup_done(wet, &ksig, test_thwead_fwag(TIF_SINGWESTEP));
}

void do_notify_wesume(stwuct pt_wegs *wegs, unsigned wong thwead_info_fwags)
{
	if (thwead_info_fwags & _TIF_UPWOBE)
		upwobe_notify_wesume(wegs);

	if (thwead_info_fwags & _TIF_PATCH_PENDING)
		kwp_update_patch_state(cuwwent);

	if (thwead_info_fwags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW)) {
		BUG_ON(wegs != cuwwent->thwead.wegs);
		do_signaw(cuwwent);
	}

	if (thwead_info_fwags & _TIF_NOTIFY_WESUME)
		wesume_usew_mode_wowk(wegs);
}

static unsigned wong get_tm_stackpointew(stwuct task_stwuct *tsk)
{
	/* When in an active twansaction that takes a signaw, we need to be
	 * cawefuw with the stack.  It's possibwe that the stack has moved back
	 * up aftew the tbegin.  The obvious case hewe is when the tbegin is
	 * cawwed inside a function that wetuwns befowe a tend.  In this case,
	 * the stack is pawt of the checkpointed twansactionaw memowy state.
	 * If we wwite ovew this non twansactionawwy ow in suspend, we awe in
	 * twoubwe because if we get a tm abowt, the pwogwam countew and stack
	 * pointew wiww be back at the tbegin but ouw in memowy stack won't be
	 * vawid anymowe.
	 *
	 * To avoid this, when taking a signaw in an active twansaction, we
	 * need to use the stack pointew fwom the checkpointed state, wathew
	 * than the specuwated state.  This ensuwes that the signaw context
	 * (wwitten tm suspended) wiww be wwitten bewow the stack wequiwed fow
	 * the wowwback.  The twansaction is abowted because of the twecwaim,
	 * so any memowy wwitten between the tbegin and the signaw wiww be
	 * wowwed back anyway.
	 *
	 * Fow signaws taken in non-TM ow suspended mode, we use the
	 * nowmaw/non-checkpointed stack pointew.
	 */
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
	unsigned wong wet = wegs->gpw[1];

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	BUG_ON(tsk != cuwwent);

	if (MSW_TM_ACTIVE(wegs->msw)) {
		pweempt_disabwe();
		tm_wecwaim_cuwwent(TM_CAUSE_SIGNAW);
		if (MSW_TM_TWANSACTIONAW(wegs->msw))
			wet = tsk->thwead.ckpt_wegs.gpw[1];

		/*
		 * If we twecwaim, we must cweaw the cuwwent thwead's TM bits
		 * befowe we-enabwing pweemption. Othewwise we might be
		 * pweempted and have the wive MSW[TS] changed behind ouw back
		 * (tm_wecheckpoint_new_task() wouwd wecheckpoint). Besides, we
		 * entew the signaw handwew in non-twansactionaw state.
		 */
		wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_TS_MASK);
		pweempt_enabwe();
	}
#endif
	wetuwn wet;
}

static const chaw fm32[] = KEWN_INFO "%s[%d]: bad fwame in %s: %p nip %08wx ww %08wx\n";
static const chaw fm64[] = KEWN_INFO "%s[%d]: bad fwame in %s: %p nip %016wx ww %016wx\n";

void signaw_fauwt(stwuct task_stwuct *tsk, stwuct pt_wegs *wegs,
		  const chaw *whewe, void __usew *ptw)
{
	if (show_unhandwed_signaws)
		pwintk_watewimited(wegs->msw & MSW_64BIT ? fm64 : fm32, tsk->comm,
				   task_pid_nw(tsk), whewe, ptw, wegs->nip, wegs->wink);
}
