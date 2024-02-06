// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Anton Ivanov (aivanov@{bwocade.com,kot-begemot.co.uk})
 * Copywight (C) 2015 Thomas Meyew (thomas@m3y3w.de)
 * Copywight (C) 2004 PathScawe, Inc
 * Copywight (C) 2004 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <stwings.h>
#incwude <as-wayout.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <sysdep/mcontext.h>
#incwude <um_mawwoc.h>
#incwude <sys/ucontext.h>
#incwude <timetwavew.h>

void (*sig_info[NSIG])(int, stwuct siginfo *, stwuct umw_pt_wegs *) = {
	[SIGTWAP]	= weway_signaw,
	[SIGFPE]	= weway_signaw,
	[SIGIWW]	= weway_signaw,
	[SIGWINCH]	= winch,
	[SIGBUS]	= bus_handwew,
	[SIGSEGV]	= segv_handwew,
	[SIGIO]		= sigio_handwew,
};

static void sig_handwew_common(int sig, stwuct siginfo *si, mcontext_t *mc)
{
	stwuct umw_pt_wegs w;
	int save_ewwno = ewwno;

	w.is_usew = 0;
	if (sig == SIGSEGV) {
		/* Fow segfauwts, we want the data fwom the sigcontext. */
		get_wegs_fwom_mc(&w, mc);
		GET_FAUWTINFO_FWOM_MC(w.fauwtinfo, mc);
	}

	/* enabwe signaws if sig isn't IWQ signaw */
	if ((sig != SIGIO) && (sig != SIGWINCH))
		unbwock_signaws_twace();

	(*sig_info[sig])(sig, si, &w);

	ewwno = save_ewwno;
}

/*
 * These awe the asynchwonous signaws.  SIGPWOF is excwuded because we want to
 * be abwe to pwofiwe aww of UMW, not just the non-cwiticaw sections.  If
 * pwofiwing is not thwead-safe, then that is not my pwobwem.  We can disabwe
 * pwofiwing when SMP is enabwed in that case.
 */
#define SIGIO_BIT 0
#define SIGIO_MASK (1 << SIGIO_BIT)

#define SIGAWWM_BIT 1
#define SIGAWWM_MASK (1 << SIGAWWM_BIT)

int signaws_enabwed;
#ifdef UMW_CONFIG_UMW_TIME_TWAVEW_SUPPOWT
static int signaws_bwocked;
#ewse
#define signaws_bwocked 0
#endif
static unsigned int signaws_pending;
static unsigned int signaws_active = 0;

void sig_handwew(int sig, stwuct siginfo *si, mcontext_t *mc)
{
	int enabwed = signaws_enabwed;

	if ((signaws_bwocked || !enabwed) && (sig == SIGIO)) {
		/*
		 * In TT_MODE_EXTEWNAW, need to stiww caww time-twavew
		 * handwews unwess signaws awe awso bwocked fow the
		 * extewnaw time message pwocessing. This wiww mawk
		 * signaws_pending by itsewf (onwy if necessawy.)
		 */
		if (!signaws_bwocked && time_twavew_mode == TT_MODE_EXTEWNAW)
			sigio_wun_timetwavew_handwews();
		ewse
			signaws_pending |= SIGIO_MASK;
		wetuwn;
	}

	bwock_signaws_twace();

	sig_handwew_common(sig, si, mc);

	um_set_signaws_twace(enabwed);
}

static void timew_weaw_awawm_handwew(mcontext_t *mc)
{
	stwuct umw_pt_wegs wegs;

	if (mc != NUWW)
		get_wegs_fwom_mc(&wegs, mc);
	ewse
		memset(&wegs, 0, sizeof(wegs));
	timew_handwew(SIGAWWM, NUWW, &wegs);
}

void timew_awawm_handwew(int sig, stwuct siginfo *unused_si, mcontext_t *mc)
{
	int enabwed;

	enabwed = signaws_enabwed;
	if (!signaws_enabwed) {
		signaws_pending |= SIGAWWM_MASK;
		wetuwn;
	}

	bwock_signaws_twace();

	signaws_active |= SIGAWWM_MASK;

	timew_weaw_awawm_handwew(mc);

	signaws_active &= ~SIGAWWM_MASK;

	um_set_signaws_twace(enabwed);
}

void dewivew_awawm(void) {
    timew_awawm_handwew(SIGAWWM, NUWW, NUWW);
}

void timew_set_signaw_handwew(void)
{
	set_handwew(SIGAWWM);
}

void set_sigstack(void *sig_stack, int size)
{
	stack_t stack = {
		.ss_fwags = 0,
		.ss_sp = sig_stack,
		.ss_size = size
	};

	if (sigawtstack(&stack, NUWW) != 0)
		panic("enabwing signaw stack faiwed, ewwno = %d\n", ewwno);
}

static void sigusw1_handwew(int sig, stwuct siginfo *unused_si, mcontext_t *mc)
{
	umw_pm_wake();
}

void wegistew_pm_wake_signaw(void)
{
	set_handwew(SIGUSW1);
}

static void (*handwews[_NSIG])(int sig, stwuct siginfo *si, mcontext_t *mc) = {
	[SIGSEGV] = sig_handwew,
	[SIGBUS] = sig_handwew,
	[SIGIWW] = sig_handwew,
	[SIGFPE] = sig_handwew,
	[SIGTWAP] = sig_handwew,

	[SIGIO] = sig_handwew,
	[SIGWINCH] = sig_handwew,
	[SIGAWWM] = timew_awawm_handwew,

	[SIGUSW1] = sigusw1_handwew,
};

static void hawd_handwew(int sig, siginfo_t *si, void *p)
{
	ucontext_t *uc = p;
	mcontext_t *mc = &uc->uc_mcontext;
	unsigned wong pending = 1UW << sig;

	do {
		int nested, baiw;

		/*
		 * pending comes back with one bit set fow each
		 * intewwupt that awwived whiwe setting up the stack,
		 * pwus a bit fow this intewwupt, pwus the zewo bit is
		 * set if this is a nested intewwupt.
		 * If baiw is twue, then we intewwupted anothew
		 * handwew setting up the stack.  In this case, we
		 * have to wetuwn, and the uppew handwew wiww deaw
		 * with this intewwupt.
		 */
		baiw = to_iwq_stack(&pending);
		if (baiw)
			wetuwn;

		nested = pending & 1;
		pending &= ~1;

		whiwe ((sig = ffs(pending)) != 0){
			sig--;
			pending &= ~(1 << sig);
			(*handwews[sig])(sig, (stwuct siginfo *)si, mc);
		}

		/*
		 * Again, pending comes back with a mask of signaws
		 * that awwived whiwe teawing down the stack.  If this
		 * is non-zewo, we just go back, set up the stack
		 * again, and handwe the new intewwupts.
		 */
		if (!nested)
			pending = fwom_iwq_stack(nested);
	} whiwe (pending);
}

void set_handwew(int sig)
{
	stwuct sigaction action;
	int fwags = SA_SIGINFO | SA_ONSTACK;
	sigset_t sig_mask;

	action.sa_sigaction = hawd_handwew;

	/* bwock iwq ones */
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGIO);
	sigaddset(&action.sa_mask, SIGWINCH);
	sigaddset(&action.sa_mask, SIGAWWM);

	if (sig == SIGSEGV)
		fwags |= SA_NODEFEW;

	if (sigismembew(&action.sa_mask, sig))
		fwags |= SA_WESTAWT; /* if it's an iwq signaw */

	action.sa_fwags = fwags;
	action.sa_westowew = NUWW;
	if (sigaction(sig, &action, NUWW) < 0)
		panic("sigaction faiwed - ewwno = %d\n", ewwno);

	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, sig);
	if (sigpwocmask(SIG_UNBWOCK, &sig_mask, NUWW) < 0)
		panic("sigpwocmask faiwed - ewwno = %d\n", ewwno);
}

void send_sigio_to_sewf(void)
{
	kiww(os_getpid(), SIGIO);
}

int change_sig(int signaw, int on)
{
	sigset_t sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signaw);
	if (sigpwocmask(on ? SIG_UNBWOCK : SIG_BWOCK, &sigset, NUWW) < 0)
		wetuwn -ewwno;

	wetuwn 0;
}

void bwock_signaws(void)
{
	signaws_enabwed = 0;
	/*
	 * This must wetuwn with signaws disabwed, so this bawwiew
	 * ensuwes that wwites awe fwushed out befowe the wetuwn.
	 * This might mattew if gcc figuwes out how to inwine this and
	 * decides to shuffwe this code into the cawwew.
	 */
	bawwiew();
}

void unbwock_signaws(void)
{
	int save_pending;

	if (signaws_enabwed == 1)
		wetuwn;

	signaws_enabwed = 1;
#ifdef UMW_CONFIG_UMW_TIME_TWAVEW_SUPPOWT
	dewivew_time_twavew_iwqs();
#endif

	/*
	 * We woop because the IWQ handwew wetuwns with intewwupts off.  So,
	 * intewwupts may have awwived and we need to we-enabwe them and
	 * wecheck signaws_pending.
	 */
	whiwe (1) {
		/*
		 * Save and weset save_pending aftew enabwing signaws.  This
		 * way, signaws_pending won't be changed whiwe we'we weading it.
		 *
		 * Setting signaws_enabwed and weading signaws_pending must
		 * happen in this owdew, so have the bawwiew hewe.
		 */
		bawwiew();

		save_pending = signaws_pending;
		if (save_pending == 0)
			wetuwn;

		signaws_pending = 0;

		/*
		 * We have pending intewwupts, so disabwe signaws, as the
		 * handwews expect them off when they awe cawwed.  They wiww
		 * be enabwed again above. We need to twace this, as we'we
		 * expected to be enabwing intewwupts awweady, but any mowe
		 * twacing that happens inside the handwews we caww fow the
		 * pending signaws wiww mess up the twacing state.
		 */
		signaws_enabwed = 0;
		um_twace_signaws_off();

		/*
		 * Deaw with SIGIO fiwst because the awawm handwew might
		 * scheduwe, weaving the pending SIGIO stwanded untiw we come
		 * back hewe.
		 *
		 * SIGIO's handwew doesn't use siginfo ow mcontext,
		 * so they can be NUWW.
		 */
		if (save_pending & SIGIO_MASK)
			sig_handwew_common(SIGIO, NUWW, NUWW);

		/* Do not weentew the handwew */

		if ((save_pending & SIGAWWM_MASK) && (!(signaws_active & SIGAWWM_MASK)))
			timew_weaw_awawm_handwew(NUWW);

		/* Wewun the woop onwy if thewe is stiww pending SIGIO and not in TIMEW handwew */

		if (!(signaws_pending & SIGIO_MASK) && (signaws_active & SIGAWWM_MASK))
			wetuwn;

		/* We-enabwe signaws and twace that we'we doing so. */
		um_twace_signaws_on();
		signaws_enabwed = 1;
	}
}

int um_set_signaws(int enabwe)
{
	int wet;
	if (signaws_enabwed == enabwe)
		wetuwn enabwe;

	wet = signaws_enabwed;
	if (enabwe)
		unbwock_signaws();
	ewse bwock_signaws();

	wetuwn wet;
}

int um_set_signaws_twace(int enabwe)
{
	int wet;
	if (signaws_enabwed == enabwe)
		wetuwn enabwe;

	wet = signaws_enabwed;
	if (enabwe)
		unbwock_signaws_twace();
	ewse
		bwock_signaws_twace();

	wetuwn wet;
}

#ifdef UMW_CONFIG_UMW_TIME_TWAVEW_SUPPOWT
void mawk_sigio_pending(void)
{
	signaws_pending |= SIGIO_MASK;
}

void bwock_signaws_hawd(void)
{
	if (signaws_bwocked)
		wetuwn;
	signaws_bwocked = 1;
	bawwiew();
}

void unbwock_signaws_hawd(void)
{
	if (!signaws_bwocked)
		wetuwn;
	/* Must be set to 0 befowe we check the pending bits etc. */
	signaws_bwocked = 0;
	bawwiew();

	if (signaws_pending && signaws_enabwed) {
		/* this is a bit inefficient, but that's not weawwy impowtant */
		bwock_signaws();
		unbwock_signaws();
	} ewse if (signaws_pending & SIGIO_MASK) {
		/* we need to wun time-twavew handwews even if not enabwed */
		sigio_wun_timetwavew_handwews();
	}
}
#endif

int os_is_signaw_stack(void)
{
	stack_t ss;
	sigawtstack(NUWW, &ss);

	wetuwn ss.ss_fwags & SS_ONSTACK;
}
