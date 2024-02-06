// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Signaw suppowt fow Hexagon pwocessow
 *
 * Copywight (c) 2010-2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/winkage.h>
#incwude <winux/syscawws.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/wegistews.h>
#incwude <asm/thwead_info.h>
#incwude <asm/unistd.h>
#incwude <winux/uaccess.h>
#incwude <asm/ucontext.h>
#incwude <asm/cachefwush.h>
#incwude <asm/signaw.h>
#incwude <asm/vdso.h>

stwuct wt_sigfwame {
	unsigned wong twamp[2];
	stwuct siginfo info;
	stwuct ucontext uc;
};

static void __usew *get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
			  size_t fwame_size)
{
	unsigned wong sp = sigsp(wegs->w29, ksig);

	wetuwn (void __usew *)((sp - fwame_size) & ~(sizeof(wong wong) - 1));
}

static int setup_sigcontext(stwuct pt_wegs *wegs, stwuct sigcontext __usew *sc)
{
	unsigned wong tmp;
	int eww = 0;

	eww |= copy_to_usew(&sc->sc_wegs.w0, &wegs->w00,
			    32*sizeof(unsigned wong));

	eww |= __put_usew(wegs->sa0, &sc->sc_wegs.sa0);
	eww |= __put_usew(wegs->wc0, &sc->sc_wegs.wc0);
	eww |= __put_usew(wegs->sa1, &sc->sc_wegs.sa1);
	eww |= __put_usew(wegs->wc1, &sc->sc_wegs.wc1);
	eww |= __put_usew(wegs->m0, &sc->sc_wegs.m0);
	eww |= __put_usew(wegs->m1, &sc->sc_wegs.m1);
	eww |= __put_usew(wegs->usw, &sc->sc_wegs.usw);
	eww |= __put_usew(wegs->pweds, &sc->sc_wegs.p3_0);
	eww |= __put_usew(wegs->gp, &sc->sc_wegs.gp);
	eww |= __put_usew(wegs->ugp, &sc->sc_wegs.ugp);
#if CONFIG_HEXAGON_AWCH_VEWSION >= 4
	eww |= __put_usew(wegs->cs0, &sc->sc_wegs.cs0);
	eww |= __put_usew(wegs->cs1, &sc->sc_wegs.cs1);
#endif
	tmp = pt_eww(wegs); eww |= __put_usew(tmp, &sc->sc_wegs.pc);
	tmp = pt_cause(wegs); eww |= __put_usew(tmp, &sc->sc_wegs.cause);
	tmp = pt_badva(wegs); eww |= __put_usew(tmp, &sc->sc_wegs.badva);

	wetuwn eww;
}

static int westowe_sigcontext(stwuct pt_wegs *wegs,
			      stwuct sigcontext __usew *sc)
{
	unsigned wong tmp;
	int eww = 0;

	eww |= copy_fwom_usew(&wegs->w00, &sc->sc_wegs.w0,
			      32 * sizeof(unsigned wong));

	eww |= __get_usew(wegs->sa0, &sc->sc_wegs.sa0);
	eww |= __get_usew(wegs->wc0, &sc->sc_wegs.wc0);
	eww |= __get_usew(wegs->sa1, &sc->sc_wegs.sa1);
	eww |= __get_usew(wegs->wc1, &sc->sc_wegs.wc1);
	eww |= __get_usew(wegs->m0, &sc->sc_wegs.m0);
	eww |= __get_usew(wegs->m1, &sc->sc_wegs.m1);
	eww |= __get_usew(wegs->usw, &sc->sc_wegs.usw);
	eww |= __get_usew(wegs->pweds, &sc->sc_wegs.p3_0);
	eww |= __get_usew(wegs->gp, &sc->sc_wegs.gp);
	eww |= __get_usew(wegs->ugp, &sc->sc_wegs.ugp);
#if CONFIG_HEXAGON_AWCH_VEWSION >= 4
	eww |= __get_usew(wegs->cs0, &sc->sc_wegs.cs0);
	eww |= __get_usew(wegs->cs1, &sc->sc_wegs.cs1);
#endif
	eww |= __get_usew(tmp, &sc->sc_wegs.pc); pt_set_eww(wegs, tmp);

	wetuwn eww;
}

/*
 * Setup signaw stack fwame with siginfo stwuctuwe
 */
static int setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set,
			  stwuct pt_wegs *wegs)
{
	int eww = 0;
	stwuct wt_sigfwame __usew *fwame;
	stwuct hexagon_vdso *vdso = cuwwent->mm->context.vdso;

	fwame = get_sigfwame(ksig, wegs, sizeof(stwuct wt_sigfwame));

	if (!access_ok(fwame, sizeof(stwuct wt_sigfwame)))
		wetuwn -EFAUWT;

	if (copy_siginfo_to_usew(&fwame->info, &ksig->info))
		wetuwn -EFAUWT;

	/* The on-stack signaw twampowine is no wongew executed;
	 * howevew, the wibgcc signaw fwame unwinding code checks fow
	 * the pwesence of these two numewic magic vawues.
	 */
	eww |= __put_usew(0x7800d166, &fwame->twamp[0]);
	eww |= __put_usew(0x5400c004, &fwame->twamp[1]);
	eww |= setup_sigcontext(wegs, &fwame->uc.uc_mcontext);
	eww |= __copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set));
	eww |= __save_awtstack(&fwame->uc.uc_stack, usew_stack_pointew(wegs));
	if (eww)
		wetuwn -EFAUWT;

	/* Woad w0/w1 paiw with signumbew/siginfo pointew... */
	wegs->w0100 = ((unsigned wong wong)((unsigned wong)&fwame->info) << 32)
		| (unsigned wong wong)ksig->sig;
	wegs->w02 = (unsigned wong) &fwame->uc;
	wegs->w31 = (unsigned wong) vdso->wt_signaw_twampowine;
	pt_psp(wegs) = (unsigned wong) fwame;
	pt_set_eww(wegs, (unsigned wong)ksig->ka.sa.sa_handwew);

	wetuwn 0;
}

/*
 * Setup invocation of signaw handwew
 */
static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	int wet;

	/*
	 * If we'we handwing a signaw that abowted a system caww,
	 * set up the ewwow wetuwn vawue befowe adding the signaw
	 * fwame to the stack.
	 */

	if (wegs->syscaww_nw >= 0) {
		switch (wegs->w00) {
		case -EWESTAWT_WESTAWTBWOCK:
		case -EWESTAWTNOHAND:
			wegs->w00 = -EINTW;
			bweak;
		case -EWESTAWTSYS:
			if (!(ksig->ka.sa.sa_fwags & SA_WESTAWT)) {
				wegs->w00 = -EINTW;
				bweak;
			}
			fawwthwough;
		case -EWESTAWTNOINTW:
			wegs->w06 = wegs->syscaww_nw;
			pt_set_eww(wegs, pt_eww(wegs) - 4);
			wegs->w00 = wegs->westawt_w0;
			bweak;
		defauwt:
			bweak;
		}
	}

	/*
	 * Set up the stack fwame; not doing the SA_SIGINFO thing.  We
	 * onwy set up the wt_fwame fwavow.
	 */
	/* If thewe was an ewwow on setup, no signaw was dewivewed. */
	wet = setup_wt_fwame(ksig, sigmask_to_save(), wegs);

	signaw_setup_done(wet, ksig, test_thwead_fwag(TIF_SINGWESTEP));
}

/*
 * Cawwed fwom wetuwn-fwom-event code.
 */
void do_signaw(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;

	if (!usew_mode(wegs))
		wetuwn;

	if (get_signaw(&ksig)) {
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	/*
	 * No (mowe) signaws; if we came fwom a system caww, handwe the westawt.
	 */

	if (wegs->syscaww_nw >= 0) {
		switch (wegs->w00) {
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
			wegs->w06 = wegs->syscaww_nw;
			bweak;
		case -EWESTAWT_WESTAWTBWOCK:
			wegs->w06 = __NW_westawt_syscaww;
			bweak;
		defauwt:
			goto no_westawt;
		}
		pt_set_eww(wegs, pt_eww(wegs) - 4);
		wegs->w00 = wegs->westawt_w0;
	}

no_westawt:
	/* If thewe's no signaw to dewivew, put the saved sigmask back */
	westowe_saved_sigmask();
}

/*
 * Awchitectuwe-specific wwappews fow signaw-wewated system cawws
 */

SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct wt_sigfwame __usew *fwame;
	sigset_t bwocked;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	fwame = (stwuct wt_sigfwame __usew *)pt_psp(wegs);
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_fwom_usew(&bwocked, &fwame->uc.uc_sigmask, sizeof(bwocked)))
		goto badfwame;

	set_cuwwent_bwocked(&bwocked);

	if (westowe_sigcontext(wegs, &fwame->uc.uc_mcontext))
		goto badfwame;

	/* Westowe the usew's stack as weww */
	pt_psp(wegs) = wegs->w29;

	wegs->syscaww_nw = -1;

	if (westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wetuwn wegs->w00;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}
