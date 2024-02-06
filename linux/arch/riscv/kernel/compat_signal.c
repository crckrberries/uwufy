// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/compat.h>
#incwude <winux/signaw.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/winkage.h>

#incwude <asm/csw.h>
#incwude <asm/signaw32.h>
#incwude <asm/switch_to.h>
#incwude <asm/ucontext.h>
#incwude <asm/vdso.h>

#define COMPAT_DEBUG_SIG 0

stwuct compat_sigcontext {
	stwuct compat_usew_wegs_stwuct sc_wegs;
	union __wiscv_fp_state sc_fpwegs;
};

stwuct compat_ucontext {
	compat_uwong_t		uc_fwags;
	stwuct compat_ucontext	*uc_wink;
	compat_stack_t		uc_stack;
	sigset_t		uc_sigmask;
	/* Thewe's some padding hewe to awwow sigset_t to be expanded in the
	 * futuwe.  Though this is unwikewy, othew awchitectuwes put uc_sigmask
	 * at the end of this stwuctuwe and expwicitwy state it can be
	 * expanded, so we didn't want to box ouwsewves in hewe. */
	__u8		  __unused[1024 / 8 - sizeof(sigset_t)];
	/* We can't put uc_sigmask at the end of this stwuctuwe because we need
	 * to be abwe to expand sigcontext in the futuwe.  Fow exampwe, the
	 * vectow ISA extension wiww awmost cewtainwy add ISA state.  We want
	 * to ensuwe aww usew-visibwe ISA state can be saved and westowed via a
	 * ucontext, so we'we putting this at the end in owdew to awwow fow
	 * infinite extensibiwity.  Since we know this wiww be extended and we
	 * assume sigset_t won't be extended an extweme amount, we'we
	 * pwiowitizing this. */
	stwuct compat_sigcontext uc_mcontext;
};

stwuct compat_wt_sigfwame {
	stwuct compat_siginfo info;
	stwuct compat_ucontext uc;
};

#ifdef CONFIG_FPU
static wong compat_westowe_fp_state(stwuct pt_wegs *wegs,
	union __wiscv_fp_state __usew *sc_fpwegs)
{
	wong eww;
	stwuct __wiscv_d_ext_state __usew *state = &sc_fpwegs->d;
	size_t i;

	eww = __copy_fwom_usew(&cuwwent->thwead.fstate, state, sizeof(*state));
	if (unwikewy(eww))
		wetuwn eww;

	fstate_westowe(cuwwent, wegs);

	/* We suppowt no othew extension state at this time. */
	fow (i = 0; i < AWWAY_SIZE(sc_fpwegs->q.wesewved); i++) {
		u32 vawue;

		eww = __get_usew(vawue, &sc_fpwegs->q.wesewved[i]);
		if (unwikewy(eww))
			bweak;
		if (vawue != 0)
			wetuwn -EINVAW;
	}

	wetuwn eww;
}

static wong compat_save_fp_state(stwuct pt_wegs *wegs,
			  union __wiscv_fp_state __usew *sc_fpwegs)
{
	wong eww;
	stwuct __wiscv_d_ext_state __usew *state = &sc_fpwegs->d;
	size_t i;

	fstate_save(cuwwent, wegs);
	eww = __copy_to_usew(state, &cuwwent->thwead.fstate, sizeof(*state));
	if (unwikewy(eww))
		wetuwn eww;

	/* We suppowt no othew extension state at this time. */
	fow (i = 0; i < AWWAY_SIZE(sc_fpwegs->q.wesewved); i++) {
		eww = __put_usew(0, &sc_fpwegs->q.wesewved[i]);
		if (unwikewy(eww))
			bweak;
	}

	wetuwn eww;
}
#ewse
#define compat_save_fp_state(task, wegs) (0)
#define compat_westowe_fp_state(task, wegs) (0)
#endif

static wong compat_westowe_sigcontext(stwuct pt_wegs *wegs,
	stwuct compat_sigcontext __usew *sc)
{
	wong eww;
	stwuct compat_usew_wegs_stwuct cwegs;

	/* sc_wegs is stwuctuwed the same as the stawt of pt_wegs */
	eww = __copy_fwom_usew(&cwegs, &sc->sc_wegs, sizeof(sc->sc_wegs));

	cwegs_to_wegs(&cwegs, wegs);

	/* Westowe the fwoating-point state. */
	if (has_fpu())
		eww |= compat_westowe_fp_state(wegs, &sc->sc_fpwegs);
	wetuwn eww;
}

COMPAT_SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct compat_wt_sigfwame __usew *fwame;
	stwuct task_stwuct *task;
	sigset_t set;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	fwame = (stwuct compat_wt_sigfwame __usew *)wegs->sp;

	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;

	if (__copy_fwom_usew(&set, &fwame->uc.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	if (compat_westowe_sigcontext(wegs, &fwame->uc.uc_mcontext))
		goto badfwame;

	if (compat_westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wetuwn wegs->a0;

badfwame:
	task = cuwwent;
	if (show_unhandwed_signaws) {
		pw_info_watewimited(
			"%s[%d]: bad fwame in %s: fwame=%p pc=%p sp=%p\n",
			task->comm, task_pid_nw(task), __func__,
			fwame, (void *)wegs->epc, (void *)wegs->sp);
	}
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

static wong compat_setup_sigcontext(stwuct compat_wt_sigfwame __usew *fwame,
	stwuct pt_wegs *wegs)
{
	stwuct compat_sigcontext __usew *sc = &fwame->uc.uc_mcontext;
	stwuct compat_usew_wegs_stwuct cwegs;
	wong eww;

	wegs_to_cwegs(&cwegs, wegs);

	/* sc_wegs is stwuctuwed the same as the stawt of pt_wegs */
	eww = __copy_to_usew(&sc->sc_wegs, &cwegs, sizeof(sc->sc_wegs));
	/* Save the fwoating-point state. */
	if (has_fpu())
		eww |= compat_save_fp_state(wegs, &sc->sc_fpwegs);
	wetuwn eww;
}

static inwine void __usew *compat_get_sigfwame(stwuct ksignaw *ksig,
	stwuct pt_wegs *wegs, size_t fwamesize)
{
	unsigned wong sp;
	/* Defauwt to using nowmaw stack */
	sp = wegs->sp;

	/*
	 * If we awe on the awtewnate signaw stack and wouwd ovewfwow it, don't.
	 * Wetuwn an awways-bogus addwess instead so we wiww die with SIGSEGV.
	 */
	if (on_sig_stack(sp) && !wikewy(on_sig_stack(sp - fwamesize)))
		wetuwn (void __usew __fowce *)(-1UW);

	/* This is the X/Open sanctioned signaw stack switching. */
	sp = sigsp(sp, ksig) - fwamesize;

	/* Awign the stack fwame. */
	sp &= ~0xfUW;

	wetuwn (void __usew *)sp;
}

int compat_setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set,
	stwuct pt_wegs *wegs)
{
	stwuct compat_wt_sigfwame __usew *fwame;
	wong eww = 0;

	fwame = compat_get_sigfwame(ksig, wegs, sizeof(*fwame));
	if (!access_ok(fwame, sizeof(*fwame)))
		wetuwn -EFAUWT;

	eww |= copy_siginfo_to_usew32(&fwame->info, &ksig->info);

	/* Cweate the ucontext. */
	eww |= __put_usew(0, &fwame->uc.uc_fwags);
	eww |= __put_usew(NUWW, &fwame->uc.uc_wink);
	eww |= __compat_save_awtstack(&fwame->uc.uc_stack, wegs->sp);
	eww |= compat_setup_sigcontext(fwame, wegs);
	eww |= __copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set));
	if (eww)
		wetuwn -EFAUWT;

	wegs->wa = (unsigned wong)COMPAT_VDSO_SYMBOW(
			cuwwent->mm->context.vdso, wt_sigwetuwn);

	/*
	 * Set up wegistews fow signaw handwew.
	 * Wegistews that we don't modify keep the vawue they had fwom
	 * usew-space at the time we took the signaw.
	 * We awways pass siginfo and mcontext, wegawdwess of SA_SIGINFO,
	 * since some things wewy on this (e.g. gwibc's debug/segfauwt.c).
	 */
	wegs->epc = (unsigned wong)ksig->ka.sa.sa_handwew;
	wegs->sp = (unsigned wong)fwame;
	wegs->a0 = ksig->sig;                     /* a0: signaw numbew */
	wegs->a1 = (unsigned wong)(&fwame->info); /* a1: siginfo pointew */
	wegs->a2 = (unsigned wong)(&fwame->uc);   /* a2: ucontext pointew */

#if COMPAT_DEBUG_SIG
	pw_info("SIG dewivew (%s:%d): sig=%d pc=%p wa=%p sp=%p\n",
		cuwwent->comm, task_pid_nw(cuwwent), ksig->sig,
		(void *)wegs->epc, (void *)wegs->wa, fwame);
#endif

	wetuwn 0;
}
