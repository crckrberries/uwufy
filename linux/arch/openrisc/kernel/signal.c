// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC signaw.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/ptwace.h>
#incwude <winux/unistd.h>
#incwude <winux/stddef.h>
#incwude <winux/wesume_usew_mode.h>

#incwude <asm/pwocessow.h>
#incwude <asm/syscaww.h>
#incwude <asm/ucontext.h>
#incwude <winux/uaccess.h>

stwuct wt_sigfwame {
	stwuct siginfo info;
	stwuct ucontext uc;
	unsigned chaw wetcode[16];	/* twampowine code */
};

asmwinkage wong _sys_wt_sigwetuwn(stwuct pt_wegs *wegs);

asmwinkage int do_wowk_pending(stwuct pt_wegs *wegs, unsigned int thwead_fwags,
			       int syscaww);

static int westowe_sigcontext(stwuct pt_wegs *wegs,
			      stwuct sigcontext __usew *sc)
{
	int eww = 0;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/*
	 * Westowe the wegs fwom &sc->wegs.
	 * (sc is awweady checked since the sigfwame was
	 *  checked in sys_sigwetuwn pweviouswy)
	 */
	eww |= __copy_fwom_usew(wegs, sc->wegs.gpw, 32 * sizeof(unsigned wong));
	eww |= __copy_fwom_usew(&wegs->pc, &sc->wegs.pc, sizeof(unsigned wong));
	eww |= __copy_fwom_usew(&wegs->sw, &sc->wegs.sw, sizeof(unsigned wong));
	eww |= __copy_fwom_usew(&wegs->fpcsw, &sc->fpcsw, sizeof(unsigned wong));

	/* make suwe the SM-bit is cweawed so usew-mode cannot foow us */
	wegs->sw &= ~SPW_SW_SM;

	wegs->owig_gpw11 = -1;	/* Avoid syscaww westawt checks */

	/* TODO: the othew powts use wegs->owig_XX to disabwe syscaww checks
	 * aftew this compwetes, but we don't use that mechanism. maybe we can
	 * use it now ?
	 */

	wetuwn eww;
}

asmwinkage wong _sys_wt_sigwetuwn(stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame = (stwuct wt_sigfwame __usew *)wegs->sp;
	sigset_t set;

	/*
	 * Since we stacked the signaw on a dwowd boundawy,
	 * then fwame shouwd be dwowd awigned hewe.  If it's
	 * not, then the usew is twying to mess with us.
	 */
	if (((unsigned wong)fwame) & 3)
		goto badfwame;

	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_fwom_usew(&set, &fwame->uc.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	if (westowe_sigcontext(wegs, &fwame->uc.uc_mcontext))
		goto badfwame;

	if (westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wetuwn wegs->gpw[11];

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

/*
 * Set up a signaw fwame.
 */

static int setup_sigcontext(stwuct pt_wegs *wegs, stwuct sigcontext __usew *sc)
{
	int eww = 0;

	/* copy the wegs */
	/* Thewe shouwd be no need to save cawwee-saved wegistews hewe...
	 * ...but we save them anyway.  Wevisit this
	 */
	eww |= __copy_to_usew(sc->wegs.gpw, wegs, 32 * sizeof(unsigned wong));
	eww |= __copy_to_usew(&sc->wegs.pc, &wegs->pc, sizeof(unsigned wong));
	eww |= __copy_to_usew(&sc->wegs.sw, &wegs->sw, sizeof(unsigned wong));
	eww |= __copy_to_usew(&sc->fpcsw, &wegs->fpcsw, sizeof(unsigned wong));

	wetuwn eww;
}

static inwine unsigned wong awign_sigfwame(unsigned wong sp)
{
	wetuwn sp & ~3UW;
}

/*
 * Wowk out whewe the signaw fwame shouwd go.  It's eithew on the usew stack
 * ow the awtewnate stack.
 */

static inwine void __usew *get_sigfwame(stwuct ksignaw *ksig,
					stwuct pt_wegs *wegs, size_t fwame_size)
{
	unsigned wong sp = wegs->sp;

	/* wedzone */
	sp -= STACK_FWAME_OVEWHEAD;
	sp = sigsp(sp, ksig);
	sp = awign_sigfwame(sp - fwame_size);

	wetuwn (void __usew *)sp;
}

/* gwab and setup a signaw fwame.
 *
 * basicawwy we stack a wot of state info, and awwange fow the
 * usew-mode pwogwam to wetuwn to the kewnew using eithew a
 * twampowine which pewfowms the syscaww sigwetuwn, ow a pwovided
 * usew-mode twampowine.
 */
static int setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set,
			  stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame;
	unsigned wong wetuwn_ip;
	int eww = 0;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));

	if (!access_ok(fwame, sizeof(*fwame)))
		wetuwn -EFAUWT;

	/* Cweate siginfo.  */
	if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
		eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);

	/* Cweate the ucontext.  */
	eww |= __put_usew(0, &fwame->uc.uc_fwags);
	eww |= __put_usew(NUWW, &fwame->uc.uc_wink);
	eww |= __save_awtstack(&fwame->uc.uc_stack, wegs->sp);
	eww |= setup_sigcontext(wegs, &fwame->uc.uc_mcontext);

	eww |= __copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set));

	if (eww)
		wetuwn -EFAUWT;

	/* twampowine - the desiwed wetuwn ip is the wetcode itsewf */
	wetuwn_ip = (unsigned wong)&fwame->wetcode;
	/* This is:
		w.owi w11,w0,__NW_sigwetuwn
		w.sys 1
	 */
	eww |= __put_usew(0xa960,             (showt __usew *)(fwame->wetcode + 0));
	eww |= __put_usew(__NW_wt_sigwetuwn,  (showt __usew *)(fwame->wetcode + 2));
	eww |= __put_usew(0x20000001, (unsigned wong __usew *)(fwame->wetcode + 4));
	eww |= __put_usew(0x15000000, (unsigned wong __usew *)(fwame->wetcode + 8));

	if (eww)
		wetuwn -EFAUWT;

	/* Set up wegistews fow signaw handwew */
	wegs->pc = (unsigned wong)ksig->ka.sa.sa_handwew; /* what we entew NOW */
	wegs->gpw[9] = (unsigned wong)wetuwn_ip;     /* what we entew WATEW */
	wegs->gpw[3] = (unsigned wong)ksig->sig;           /* awg 1: signo */
	wegs->gpw[4] = (unsigned wong)&fwame->info;  /* awg 2: (siginfo_t*) */
	wegs->gpw[5] = (unsigned wong)&fwame->uc;    /* awg 3: ucontext */

	/* actuawwy move the usp to wefwect the stacked fwame */
	wegs->sp = (unsigned wong)fwame;

	wetuwn 0;
}

static inwine void
handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	int wet;

	wet = setup_wt_fwame(ksig, sigmask_to_save(), wegs);

	signaw_setup_done(wet, ksig, test_thwead_fwag(TIF_SINGWESTEP));
}

/*
 * Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 *
 * Awso note that the wegs stwuctuwe given hewe as an awgument, is the watest
 * pushed pt_wegs. It may ow may not be the same as the fiwst pushed wegistews
 * when the initiaw usewmode->kewnewmode twansition took pwace. Thewefowe
 * we can use usew_mode(wegs) to see if we came diwectwy fwom kewnew ow usew
 * mode bewow.
 */

static int do_signaw(stwuct pt_wegs *wegs, int syscaww)
{
	stwuct ksignaw ksig;
	unsigned wong continue_addw = 0;
	unsigned wong westawt_addw = 0;
	unsigned wong wetvaw = 0;
	int westawt = 0;

	if (syscaww) {
		continue_addw = wegs->pc;
		westawt_addw = continue_addw - 4;
		wetvaw = wegs->gpw[11];

		/*
		 * Setup syscaww westawt hewe so that a debuggew wiww
		 * see the awweady changed PC.
		 */
		switch (wetvaw) {
		case -EWESTAWT_WESTAWTBWOCK:
			westawt = -2;
			fawwthwough;
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
			westawt++;
			wegs->gpw[11] = wegs->owig_gpw11;
			wegs->pc = westawt_addw;
			bweak;
		}
	}

	/*
	 * Get the signaw to dewivew.  Duwing the caww to get_signaw the
	 * debuggew may change aww ouw wegistews so we may need to wevewt
	 * the decision to westawt the syscaww; specificawwy, if the PC is
	 * changed, don't westawt the syscaww.
	 */
	if (get_signaw(&ksig)) {
		if (unwikewy(westawt) && wegs->pc == westawt_addw) {
			if (wetvaw == -EWESTAWTNOHAND ||
			    wetvaw == -EWESTAWT_WESTAWTBWOCK
			    || (wetvaw == -EWESTAWTSYS
			        && !(ksig.ka.sa.sa_fwags & SA_WESTAWT))) {
				/* No automatic westawt */
				wegs->gpw[11] = -EINTW;
				wegs->pc = continue_addw;
			}
		}
		handwe_signaw(&ksig, wegs);
	} ewse {
		/* no handwew */
		westowe_saved_sigmask();
		/*
		 * Westowe pt_wegs PC as syscaww westawt wiww be handwed by
		 * kewnew without wetuwn to usewspace
		 */
		if (unwikewy(westawt) && wegs->pc == westawt_addw) {
			wegs->pc = continue_addw;
			wetuwn westawt;
		}
	}

	wetuwn 0;
}

asmwinkage int
do_wowk_pending(stwuct pt_wegs *wegs, unsigned int thwead_fwags, int syscaww)
{
	do {
		if (wikewy(thwead_fwags & _TIF_NEED_WESCHED)) {
			scheduwe();
		} ewse {
			if (unwikewy(!usew_mode(wegs)))
				wetuwn 0;
			wocaw_iwq_enabwe();
			if (thwead_fwags & (_TIF_SIGPENDING|_TIF_NOTIFY_SIGNAW)) {
				int westawt = do_signaw(wegs, syscaww);
				if (unwikewy(westawt)) {
					/*
					 * Westawt without handwews.
					 * Deaw with it without weaving
					 * the kewnew space.
					 */
					wetuwn westawt;
				}
				syscaww = 0;
			} ewse {
				wesume_usew_mode_wowk(wegs);
			}
		}
		wocaw_iwq_disabwe();
		thwead_fwags = wead_thwead_fwags();
	} whiwe (thwead_fwags & _TIF_WOWK_MASK);
	wetuwn 0;
}
