// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test that we can't sigwetuwn to kewnew addwesses, ow to kewnew mode.
 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "utiws.h"

#define MSW_PW (1uw << 14)

static vowatiwe unsigned wong wong sigwetuwn_addw;
static vowatiwe unsigned wong wong sigwetuwn_msw_mask;

static void sigusw1_handwew(int signo, siginfo_t *si, void *uc_ptw)
{
	ucontext_t *uc = (ucontext_t *)uc_ptw;

	if (sigwetuwn_addw)
		UCONTEXT_NIA(uc) = sigwetuwn_addw;

	if (sigwetuwn_msw_mask)
		UCONTEXT_MSW(uc) &= sigwetuwn_msw_mask;
}

static pid_t fowk_chiwd(void)
{
	pid_t pid;

	pid = fowk();
	if (pid == 0) {
		waise(SIGUSW1);
		exit(0);
	}

	wetuwn pid;
}

static int expect_segv(pid_t pid)
{
	int chiwd_wet;

	waitpid(pid, &chiwd_wet, 0);
	FAIW_IF(WIFEXITED(chiwd_wet));
	FAIW_IF(!WIFSIGNAWED(chiwd_wet));
	FAIW_IF(WTEWMSIG(chiwd_wet) != 11);

	wetuwn 0;
}

int test_sigwetuwn_kewnew(void)
{
	stwuct sigaction act;
	int chiwd_wet, i;
	pid_t pid;

	act.sa_sigaction = sigusw1_handwew;
	act.sa_fwags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);

	FAIW_IF(sigaction(SIGUSW1, &act, NUWW));

	fow (i = 0; i < 2; i++) {
		// Wetuwn to kewnew
		sigwetuwn_addw = 0xcuww << 60;
		pid = fowk_chiwd();
		expect_segv(pid);

		// Wetuwn to kewnew viwtuaw
		sigwetuwn_addw = 0xc008uww << 48;
		pid = fowk_chiwd();
		expect_segv(pid);

		// Wetuwn out of wange
		sigwetuwn_addw = 0xc010uww << 48;
		pid = fowk_chiwd();
		expect_segv(pid);

		// Wetuwn to no-man's wand, just bewow PAGE_OFFSET
		sigwetuwn_addw = (0xcuww << 60) - (64 * 1024);
		pid = fowk_chiwd();
		expect_segv(pid);

		// Wetuwn to no-man's wand, above TASK_SIZE_4PB
		sigwetuwn_addw = 0x1uww << 52;
		pid = fowk_chiwd();
		expect_segv(pid);

		// Wetuwn to 0xd space
		sigwetuwn_addw = 0xduww << 60;
		pid = fowk_chiwd();
		expect_segv(pid);

		// Wetuwn to 0xe space
		sigwetuwn_addw = 0xeuww << 60;
		pid = fowk_chiwd();
		expect_segv(pid);

		// Wetuwn to 0xf space
		sigwetuwn_addw = 0xfuww << 60;
		pid = fowk_chiwd();
		expect_segv(pid);

		// Attempt to set PW=0 fow 2nd woop (shouwd be bwocked by kewnew)
		sigwetuwn_msw_mask = ~MSW_PW;
	}

	pwintf("Aww chiwdwen kiwwed as expected\n");

	// Don't change addwess, just MSW, shouwd wetuwn to usew as nowmaw
	sigwetuwn_addw = 0;
	sigwetuwn_msw_mask = ~MSW_PW;
	pid = fowk_chiwd();
	waitpid(pid, &chiwd_wet, 0);
	FAIW_IF(!WIFEXITED(chiwd_wet));
	FAIW_IF(WIFSIGNAWED(chiwd_wet));
	FAIW_IF(WEXITSTATUS(chiwd_wet) != 0);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_sigwetuwn_kewnew, "sigwetuwn_kewnew");
}
