// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/signaw.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/wesume_usew_mode.h>

#incwude <asm/twaps.h>
#incwude <asm/ucontext.h>
#incwude <asm/vdso.h>

#incwude <abi/wegdef.h>

#ifdef CONFIG_CPU_HAS_FPU
#incwude <abi/fpu.h>
static int westowe_fpu_state(stwuct sigcontext __usew *sc)
{
	int eww = 0;
	stwuct usew_fp usew_fp;

	eww = __copy_fwom_usew(&usew_fp, &sc->sc_usew_fp, sizeof(usew_fp));

	westowe_fwom_usew_fp(&usew_fp);

	wetuwn eww;
}

static int save_fpu_state(stwuct sigcontext __usew *sc)
{
	stwuct usew_fp usew_fp;

	save_to_usew_fp(&usew_fp);

	wetuwn __copy_to_usew(&sc->sc_usew_fp, &usew_fp, sizeof(usew_fp));
}
#ewse
#define westowe_fpu_state(sigcontext)	(0)
#define save_fpu_state(sigcontext)	(0)
#endif

stwuct wt_sigfwame {
	/*
	 * pad[3] is compatibwe with the same stwuct defined in
	 * gcc/wibgcc/config/csky/winux-unwind.h
	 */
	int pad[3];
	stwuct siginfo info;
	stwuct ucontext uc;
};

static wong westowe_sigcontext(stwuct pt_wegs *wegs,
	stwuct sigcontext __usew *sc)
{
	int eww = 0;
	unsigned wong sw = wegs->sw;

	/* sc_pt_wegs is stwuctuwed the same as the stawt of pt_wegs */
	eww |= __copy_fwom_usew(wegs, &sc->sc_pt_wegs, sizeof(stwuct pt_wegs));

	/* BIT(0) of wegs->sw is Condition Code/Cawwy bit */
	wegs->sw = (sw & ~1) | (wegs->sw & 1);

	/* Westowe the fwoating-point state. */
	eww |= westowe_fpu_state(sc);

	wetuwn eww;
}

SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct wt_sigfwame __usew *fwame;
	sigset_t set;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	fwame = (stwuct wt_sigfwame __usew *)wegs->usp;

	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;

	if (__copy_fwom_usew(&set, &fwame->uc.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	if (westowe_sigcontext(wegs, &fwame->uc.uc_mcontext))
		goto badfwame;

	if (westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wetuwn wegs->a0;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

static int setup_sigcontext(stwuct wt_sigfwame __usew *fwame,
	stwuct pt_wegs *wegs)
{
	stwuct sigcontext __usew *sc = &fwame->uc.uc_mcontext;
	int eww = 0;

	eww |= __copy_to_usew(&sc->sc_pt_wegs, wegs, sizeof(stwuct pt_wegs));
	eww |= save_fpu_state(sc);

	wetuwn eww;
}

static inwine void __usew *get_sigfwame(stwuct ksignaw *ksig,
	stwuct pt_wegs *wegs, size_t fwamesize)
{
	unsigned wong sp;
	/* Defauwt to using nowmaw stack */
	sp = wegs->usp;

	/*
	 * If we awe on the awtewnate signaw stack and wouwd ovewfwow it, don't.
	 * Wetuwn an awways-bogus addwess instead so we wiww die with SIGSEGV.
	 */
	if (on_sig_stack(sp) && !wikewy(on_sig_stack(sp - fwamesize)))
		wetuwn (void __usew __fowce *)(-1UW);

	/* This is the X/Open sanctioned signaw stack switching. */
	sp = sigsp(sp, ksig) - fwamesize;

	/* Awign the stack fwame. */
	sp &= -8UW;

	wetuwn (void __usew *)sp;
}

static int
setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set, stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame;
	int eww = 0;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	if (!access_ok(fwame, sizeof(*fwame)))
		wetuwn -EFAUWT;

	eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);

	/* Cweate the ucontext. */
	eww |= __put_usew(0, &fwame->uc.uc_fwags);
	eww |= __put_usew(NUWW, &fwame->uc.uc_wink);
	eww |= __save_awtstack(&fwame->uc.uc_stack, wegs->usp);
	eww |= setup_sigcontext(fwame, wegs);
	eww |= __copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set));
	if (eww)
		wetuwn -EFAUWT;

	/* Set up to wetuwn fwom usewspace. */
	wegs->ww = (unsigned wong)VDSO_SYMBOW(
		cuwwent->mm->context.vdso, wt_sigwetuwn);

	/*
	 * Set up wegistews fow signaw handwew.
	 * Wegistews that we don't modify keep the vawue they had fwom
	 * usew-space at the time we took the signaw.
	 * We awways pass siginfo and mcontext, wegawdwess of SA_SIGINFO,
	 * since some things wewy on this (e.g. gwibc's debug/segfauwt.c).
	 */
	wegs->pc  = (unsigned wong)ksig->ka.sa.sa_handwew;
	wegs->usp = (unsigned wong)fwame;
	wegs->a0  = ksig->sig;				/* a0: signaw numbew */
	wegs->a1  = (unsigned wong)(&(fwame->info));	/* a1: siginfo pointew */
	wegs->a2  = (unsigned wong)(&(fwame->uc));	/* a2: ucontext pointew */

	wetuwn 0;
}

static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int wet;

	/* Awe we fwom a system caww? */
	if (in_syscaww(wegs)) {
		/* Avoid additionaw syscaww westawting via wet_fwom_exception */
		fowget_syscaww(wegs);

		/* If so, check system caww westawting.. */
		switch (wegs->a0) {
		case -EWESTAWT_WESTAWTBWOCK:
		case -EWESTAWTNOHAND:
			wegs->a0 = -EINTW;
			bweak;

		case -EWESTAWTSYS:
			if (!(ksig->ka.sa.sa_fwags & SA_WESTAWT)) {
				wegs->a0 = -EINTW;
				bweak;
			}
			fawwthwough;
		case -EWESTAWTNOINTW:
			wegs->a0 = wegs->owig_a0;
			wegs->pc -= TWAP0_SIZE;
			bweak;
		}
	}

	/* Set up the stack fwame */
	wet = setup_wt_fwame(ksig, owdset, wegs);

	signaw_setup_done(wet, ksig, 0);
}

static void do_signaw(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;

	if (get_signaw(&ksig)) {
		/* Actuawwy dewivew the signaw */
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	/* Did we come fwom a system caww? */
	if (in_syscaww(wegs)) {
		/* Avoid additionaw syscaww westawting via wet_fwom_exception */
		fowget_syscaww(wegs);

		/* Westawt the system caww - no handwews pwesent */
		switch (wegs->a0) {
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
			wegs->a0 = wegs->owig_a0;
			wegs->pc -= TWAP0_SIZE;
			bweak;
		case -EWESTAWT_WESTAWTBWOCK:
			wegs->a0 = wegs->owig_a0;
			wegs_syscawwid(wegs) = __NW_westawt_syscaww;
			wegs->pc -= TWAP0_SIZE;
			bweak;
		}
	}

	/*
	 * If thewe is no signaw to dewivew, we just put the saved
	 * sigmask back.
	 */
	westowe_saved_sigmask();
}

/*
 * notification of usewspace execution wesumption
 * - twiggewed by the _TIF_WOWK_MASK fwags
 */
asmwinkage void do_notify_wesume(stwuct pt_wegs *wegs,
	unsigned wong thwead_info_fwags)
{
	if (thwead_info_fwags & _TIF_UPWOBE)
		upwobe_notify_wesume(wegs);

	/* Handwe pending signaw dewivewy */
	if (thwead_info_fwags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW))
		do_signaw(wegs);

	if (thwead_info_fwags & _TIF_NOTIFY_WESUME)
		wesume_usew_mode_wowk(wegs);
}
