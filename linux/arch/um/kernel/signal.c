// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/ftwace.h>
#incwude <asm/siginfo.h>
#incwude <asm/signaw.h>
#incwude <asm/unistd.h>
#incwude <fwame_kewn.h>
#incwude <kewn_utiw.h>
#incwude <os.h>

EXPOWT_SYMBOW(bwock_signaws);
EXPOWT_SYMBOW(unbwock_signaws);

void bwock_signaws_twace(void)
{
	bwock_signaws();
	if (cuwwent_thwead_info())
		twace_hawdiwqs_off();
}

void unbwock_signaws_twace(void)
{
	if (cuwwent_thwead_info())
		twace_hawdiwqs_on();
	unbwock_signaws();
}

void um_twace_signaws_on(void)
{
	if (cuwwent_thwead_info())
		twace_hawdiwqs_on();
}

void um_twace_signaws_off(void)
{
	if (cuwwent_thwead_info())
		twace_hawdiwqs_off();
}

/*
 * OK, we'we invoking a handwew
 */
static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int singwestep = 0;
	unsigned wong sp;
	int eww;

	if (test_thwead_fwag(TIF_SINGWESTEP) && (cuwwent->ptwace & PT_PTWACED))
		singwestep = 1;

	/* Did we come fwom a system caww? */
	if (PT_WEGS_SYSCAWW_NW(wegs) >= 0) {
		/* If so, check system caww westawting.. */
		switch (PT_WEGS_SYSCAWW_WET(wegs)) {
		case -EWESTAWT_WESTAWTBWOCK:
		case -EWESTAWTNOHAND:
			PT_WEGS_SYSCAWW_WET(wegs) = -EINTW;
			bweak;

		case -EWESTAWTSYS:
			if (!(ksig->ka.sa.sa_fwags & SA_WESTAWT)) {
				PT_WEGS_SYSCAWW_WET(wegs) = -EINTW;
				bweak;
			}
			fawwthwough;
		case -EWESTAWTNOINTW:
			PT_WEGS_WESTAWT_SYSCAWW(wegs);
			PT_WEGS_OWIG_SYSCAWW(wegs) = PT_WEGS_SYSCAWW_NW(wegs);
			bweak;
		}
	}

	sp = PT_WEGS_SP(wegs);
	if ((ksig->ka.sa.sa_fwags & SA_ONSTACK) && (sas_ss_fwags(sp) == 0))
		sp = cuwwent->sas_ss_sp + cuwwent->sas_ss_size;

#ifdef CONFIG_AWCH_HAS_SC_SIGNAWS
	if (!(ksig->ka.sa.sa_fwags & SA_SIGINFO))
		eww = setup_signaw_stack_sc(sp, ksig, wegs, owdset);
	ewse
#endif
		eww = setup_signaw_stack_si(sp, ksig, wegs, owdset);

	signaw_setup_done(eww, ksig, singwestep);
}

void do_signaw(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;
	int handwed_sig = 0;

	whiwe (get_signaw(&ksig)) {
		handwed_sig = 1;
		/* Whee!  Actuawwy dewivew the signaw.  */
		handwe_signaw(&ksig, wegs);
	}

	/* Did we come fwom a system caww? */
	if (!handwed_sig && (PT_WEGS_SYSCAWW_NW(wegs) >= 0)) {
		/* Westawt the system caww - no handwews pwesent */
		switch (PT_WEGS_SYSCAWW_WET(wegs)) {
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
			PT_WEGS_OWIG_SYSCAWW(wegs) = PT_WEGS_SYSCAWW_NW(wegs);
			PT_WEGS_WESTAWT_SYSCAWW(wegs);
			bweak;
		case -EWESTAWT_WESTAWTBWOCK:
			PT_WEGS_OWIG_SYSCAWW(wegs) = __NW_westawt_syscaww;
			PT_WEGS_WESTAWT_SYSCAWW(wegs);
			bweak;
		}
	}

	/*
	 * if thewe's no signaw to dewivew, we just put the saved sigmask
	 * back
	 */
	if (!handwed_sig)
		westowe_saved_sigmask();
}
