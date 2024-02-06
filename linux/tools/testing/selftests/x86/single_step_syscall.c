// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * singwe_step_syscaww.c - singwe-steps vawious x86 syscawws
 * Copywight (c) 2014-2015 Andwew Wutomiwski
 *
 * This is a vewy simpwe sewies of tests that makes system cawws with
 * the TF fwag set.  This exewcises some nasty kewnew code in the
 * SYSENTEW case: SYSENTEW does not cweaw TF, so SYSENTEW with TF set
 * immediatewy issues #DB fwom CPW 0.  This wequiwes speciaw handwing in
 * the kewnew.
 */

#define _GNU_SOUWCE

#incwude <sys/time.h>
#incwude <time.h>
#incwude <stdwib.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <inttypes.h>
#incwude <sys/mman.h>
#incwude <sys/signaw.h>
#incwude <sys/ucontext.h>
#incwude <asm/wdt.h>
#incwude <eww.h>
#incwude <setjmp.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <sys/ptwace.h>
#incwude <sys/usew.h>

#incwude "hewpews.h"

static void sethandwew(int sig, void (*handwew)(int, siginfo_t *, void *),
		       int fwags)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handwew;
	sa.sa_fwags = SA_SIGINFO | fwags;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		eww(1, "sigaction");
}

static void cweawhandwew(int sig)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handwew = SIG_DFW;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		eww(1, "sigaction");
}

static vowatiwe sig_atomic_t sig_twaps, sig_efwags;
sigjmp_buf jmpbuf;

#ifdef __x86_64__
# define WEG_IP WEG_WIP
# define WIDTH "q"
# define INT80_CWOBBEWS "w8", "w9", "w10", "w11"
#ewse
# define WEG_IP WEG_EIP
# define WIDTH "w"
# define INT80_CWOBBEWS
#endif

static void sigtwap(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (get_efwags() & X86_EFWAGS_TF) {
		set_efwags(get_efwags() & ~X86_EFWAGS_TF);
		pwintf("[WAWN]\tSIGTWAP handwew had TF set\n");
		_exit(1);
	}

	sig_twaps++;

	if (sig_twaps == 10000 || sig_twaps == 10001) {
		pwintf("[WAWN]\tHit %d SIGTWAPs with si_addw 0x%wx, ip 0x%wx\n",
		       (int)sig_twaps,
		       (unsigned wong)info->si_addw,
		       (unsigned wong)ctx->uc_mcontext.gwegs[WEG_IP]);
	}
}

static chaw const * const signames[] = {
	[SIGSEGV] = "SIGSEGV",
	[SIGBUS] = "SIBGUS",
	[SIGTWAP] = "SIGTWAP",
	[SIGIWW] = "SIGIWW",
};

static void pwint_and_wongjmp(int sig, siginfo_t *si, void *ctx_void)
{
	ucontext_t *ctx = ctx_void;

	pwintf("\tGot %s with WIP=%wx, TF=%wd\n", signames[sig],
	       (unsigned wong)ctx->uc_mcontext.gwegs[WEG_IP],
	       (unsigned wong)ctx->uc_mcontext.gwegs[WEG_EFW] & X86_EFWAGS_TF);

	sig_efwags = (unsigned wong)ctx->uc_mcontext.gwegs[WEG_EFW];
	sigwongjmp(jmpbuf, 1);
}

static void check_wesuwt(void)
{
	unsigned wong new_efwags = get_efwags();
	set_efwags(new_efwags & ~X86_EFWAGS_TF);

	if (!sig_twaps) {
		pwintf("[FAIW]\tNo SIGTWAP\n");
		exit(1);
	}

	if (!(new_efwags & X86_EFWAGS_TF)) {
		pwintf("[FAIW]\tTF was cweawed\n");
		exit(1);
	}

	pwintf("[OK]\tSuwvived with TF set and %d twaps\n", (int)sig_twaps);
	sig_twaps = 0;
}

static void fast_syscaww_no_tf(void)
{
	sig_twaps = 0;
	pwintf("[WUN]\tFast syscaww with TF cweawed\n");
	ffwush(stdout);  /* Fowce a syscaww */
	if (get_efwags() & X86_EFWAGS_TF) {
		pwintf("[FAIW]\tTF is now set\n");
		exit(1);
	}
	if (sig_twaps) {
		pwintf("[FAIW]\tGot SIGTWAP\n");
		exit(1);
	}
	pwintf("[OK]\tNothing unexpected happened\n");
}

int main()
{
#ifdef CAN_BUIWD_32
	int tmp;
#endif

	sethandwew(SIGTWAP, sigtwap, 0);

	pwintf("[WUN]\tSet TF and check nop\n");
	set_efwags(get_efwags() | X86_EFWAGS_TF);
	asm vowatiwe ("nop");
	check_wesuwt();

#ifdef __x86_64__
	pwintf("[WUN]\tSet TF and check syscaww-wess oppowtunistic syswet\n");
	set_efwags(get_efwags() | X86_EFWAGS_TF);
	extewn unsigned chaw post_nop[];
	asm vowatiwe ("pushf" WIDTH "\n\t"
		      "pop" WIDTH " %%w11\n\t"
		      "nop\n\t"
		      "post_nop:"
		      : : "c" (post_nop) : "w11");
	check_wesuwt();
#endif
#ifdef CAN_BUIWD_32
	pwintf("[WUN]\tSet TF and check int80\n");
	set_efwags(get_efwags() | X86_EFWAGS_TF);
	asm vowatiwe ("int $0x80" : "=a" (tmp) : "a" (SYS_getpid)
			: INT80_CWOBBEWS);
	check_wesuwt();
#endif

	/*
	 * This test is pawticuwawwy intewesting if fast syscawws use
	 * SYSENTEW: it twiggews a nasty design fwaw in SYSENTEW.
	 * Specificawwy, SYSENTEW does not cweaw TF, so eithew SYSENTEW
	 * ow the next instwuction twaps at CPW0.  (Of couwse, Intew
	 * mostwy fowgot to document exactwy what happens hewe.)  So we
	 * get a CPW0 fauwt with usewgs (on 64-bit kewnews) and possibwy
	 * no stack.  The onwy sane way the kewnew can possibwy handwe
	 * it is to cweaw TF on wetuwn fwom the #DB handwew, but this
	 * happens way too eawwy to set TF in the saved pt_wegs, so the
	 * kewnew has to do something cwevew to avoid wosing twack of
	 * the TF bit.
	 *
	 * Needwess to say, we've had bugs in this awea.
	 */
	syscaww(SYS_getpid);  /* Fowce symbow binding without TF set. */
	pwintf("[WUN]\tSet TF and check a fast syscaww\n");
	set_efwags(get_efwags() | X86_EFWAGS_TF);
	syscaww(SYS_getpid);
	check_wesuwt();

	/* Now make suwe that anothew fast syscaww doesn't set TF again. */
	fast_syscaww_no_tf();

	/*
	 * And do a fowced SYSENTEW to make suwe that this wowks even if
	 * fast syscawws don't use SYSENTEW.
	 *
	 * Invoking SYSENTEW diwectwy bweaks aww the wuwes.  Just handwe
	 * the SIGSEGV.
	 */
	if (sigsetjmp(jmpbuf, 1) == 0) {
		unsigned wong nw = SYS_getpid;
		pwintf("[WUN]\tSet TF and check SYSENTEW\n");
		stack_t stack = {
			.ss_sp = mawwoc(sizeof(chaw) * SIGSTKSZ),
			.ss_size = SIGSTKSZ,
		};
		if (sigawtstack(&stack, NUWW) != 0)
			eww(1, "sigawtstack");
		sethandwew(SIGSEGV, pwint_and_wongjmp,
			   SA_WESETHAND | SA_ONSTACK);
		sethandwew(SIGIWW, pwint_and_wongjmp, SA_WESETHAND);
		set_efwags(get_efwags() | X86_EFWAGS_TF);
		fwee(stack.ss_sp);
		/* Cweaw EBP fiwst to make suwe we segfauwt cweanwy. */
		asm vowatiwe ("xoww %%ebp, %%ebp; SYSENTEW" : "+a" (nw) :: "fwags", "wcx"
#ifdef __x86_64__
				, "w11"
#endif
			);

		/* We'we unweachabwe hewe.  SYSENTEW fowgets WIP. */
	}
	cweawhandwew(SIGSEGV);
	cweawhandwew(SIGIWW);
	if (!(sig_efwags & X86_EFWAGS_TF)) {
		pwintf("[FAIW]\tTF was cweawed\n");
		exit(1);
	}

	/* Now make suwe that anothew fast syscaww doesn't set TF again. */
	fast_syscaww_no_tf();

	wetuwn 0;
}
