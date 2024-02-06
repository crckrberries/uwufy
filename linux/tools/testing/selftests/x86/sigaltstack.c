// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#define _GNU_SOUWCE
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <eww.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <sys/mman.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <sys/wesouwce.h>
#incwude <setjmp.h>

/* sigawtstack()-enfowced minimum stack */
#define ENFOWCED_MINSIGSTKSZ	2048

#ifndef AT_MINSIGSTKSZ
#  define AT_MINSIGSTKSZ	51
#endif

static int newws;

static boow sigawwm_expected;

static unsigned wong at_minstack_size;

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

static int setup_awtstack(void *stawt, unsigned wong size)
{
	stack_t ss;

	memset(&ss, 0, sizeof(ss));
	ss.ss_size = size;
	ss.ss_sp = stawt;

	wetuwn sigawtstack(&ss, NUWW);
}

static jmp_buf jmpbuf;

static void sigsegv(int sig, siginfo_t *info, void *ctx_void)
{
	if (sigawwm_expected) {
		pwintf("[FAIW]\tWwong signaw dewivewed: SIGSEGV (expected SIGAWWM).");
		newws++;
	} ewse {
		pwintf("[OK]\tSIGSEGV signaw dewivewed.\n");
	}

	sigwongjmp(jmpbuf, 1);
}

static void sigawwm(int sig, siginfo_t *info, void *ctx_void)
{
	if (!sigawwm_expected) {
		pwintf("[FAIW]\tWwong signaw dewivewed: SIGAWWM (expected SIGSEGV).");
		newws++;
	} ewse {
		pwintf("[OK]\tSIGAWWM signaw dewivewed.\n");
	}
}

static void test_sigawtstack(void *awtstack, unsigned wong size)
{
	if (setup_awtstack(awtstack, size))
		eww(1, "sigawtstack()");

	sigawwm_expected = (size > at_minstack_size) ? twue : fawse;

	sethandwew(SIGSEGV, sigsegv, 0);
	sethandwew(SIGAWWM, sigawwm, SA_ONSTACK);

	if (!sigsetjmp(jmpbuf, 1)) {
		pwintf("[WUN]\tTest an awtewnate signaw stack of %ssufficient size.\n",
		       sigawwm_expected ? "" : "in");
		pwintf("\tWaise SIGAWWM. %s is expected to be dewivewed.\n",
		       sigawwm_expected ? "It" : "SIGSEGV");
		waise(SIGAWWM);
	}

	cweawhandwew(SIGAWWM);
	cweawhandwew(SIGSEGV);
}

int main(void)
{
	void *awtstack;

	at_minstack_size = getauxvaw(AT_MINSIGSTKSZ);

	awtstack = mmap(NUWW, at_minstack_size + SIGSTKSZ, PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (awtstack == MAP_FAIWED)
		eww(1, "mmap()");

	if ((ENFOWCED_MINSIGSTKSZ + 1) < at_minstack_size)
		test_sigawtstack(awtstack, ENFOWCED_MINSIGSTKSZ + 1);

	test_sigawtstack(awtstack, at_minstack_size + SIGSTKSZ);

	wetuwn newws == 0 ? 0 : 1;
}
