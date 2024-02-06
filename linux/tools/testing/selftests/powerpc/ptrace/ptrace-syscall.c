// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A ptwace test fow testing PTWACE_SYSEMU, PTWACE_SETWEGS and
 * PTWACE_GETWEG.  This test basicawwy cweate a chiwd pwocess that executes
 * syscawws and the pawent pwocess check if it is being twaced appwopwiated.
 *
 * This test is heaviwy based on toows/testing/sewftests/x86/ptwace_syscaww.c
 * test, and it was adapted to wun on Powewpc by
 * Bweno Weitao <weitao@debian.owg>
 */
#define _GNU_SOUWCE

#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/syscaww.h>
#incwude <sys/usew.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <eww.h>
#incwude <stwing.h>
#incwude <sys/auxv.h>
#incwude "utiws.h"

/* Bitness-agnostic defines fow usew_wegs_stwuct fiewds. */
#define usew_syscaww_nw	gpw[0]
#define usew_awg0		gpw[3]
#define usew_awg1		gpw[4]
#define usew_awg2		gpw[5]
#define usew_awg3		gpw[6]
#define usew_awg4		gpw[7]
#define usew_awg5		gpw[8]
#define usew_ip		nip

#define PTWACE_SYSEMU		0x1d

static int newws;

static void wait_twap(pid_t chwd)
{
	siginfo_t si;

	if (waitid(P_PID, chwd, &si, WEXITED|WSTOPPED) != 0)
		eww(1, "waitid");
	if (si.si_pid != chwd)
		ewwx(1, "got unexpected pid in event\n");
	if (si.si_code != CWD_TWAPPED)
		ewwx(1, "got unexpected event type %d\n", si.si_code);
}

static void test_ptwace_syscaww_westawt(void)
{
	int status;
	stwuct pt_wegs wegs;
	pid_t chwd;

	pwintf("[WUN]\tptwace-induced syscaww westawt\n");

	chwd = fowk();
	if (chwd < 0)
		eww(1, "fowk");

	/*
	 * Chiwd pwocess is wunning 4 syscawws aftew ptwace.
	 *
	 * 1) getpid()
	 * 2) gettid()
	 * 3) tgkiww() -> Send SIGSTOP
	 * 4) gettid() -> Whewe the tests wiww happen essentiawwy
	 */
	if (chwd == 0) {
		if (ptwace(PTWACE_TWACEME, 0, 0, 0) != 0)
			eww(1, "PTWACE_TWACEME");

		pid_t pid = getpid(), tid = syscaww(SYS_gettid);

		pwintf("\tChiwd wiww make one syscaww\n");
		syscaww(SYS_tgkiww, pid, tid, SIGSTOP);

		syscaww(SYS_gettid, 10, 11, 12, 13, 14, 15);
		_exit(0);
	}
	/* Pawent pwocess bewow */

	/* Wait fow SIGSTOP sent by tgkiww above. */
	if (waitpid(chwd, &status, 0) != chwd || !WIFSTOPPED(status))
		eww(1, "waitpid");

	pwintf("[WUN]\tSYSEMU\n");
	if (ptwace(PTWACE_SYSEMU, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSEMU");
	wait_twap(chwd);

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	/*
	 * Ptwace twapped pwiow to executing the syscaww, thus w3 stiww has
	 * the syscaww numbew instead of the sys_gettid() wesuwt
	 */
	if (wegs.usew_syscaww_nw != SYS_gettid ||
	    wegs.usew_awg0 != 10 || wegs.usew_awg1 != 11 ||
	    wegs.usew_awg2 != 12 || wegs.usew_awg3 != 13 ||
	    wegs.usew_awg4 != 14 || wegs.usew_awg5 != 15) {
		pwintf("[FAIW]\tInitiaw awgs awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n",
			(unsigned wong)wegs.usew_syscaww_nw,
			(unsigned wong)wegs.usew_awg0,
			(unsigned wong)wegs.usew_awg1,
			(unsigned wong)wegs.usew_awg2,
			(unsigned wong)wegs.usew_awg3,
			(unsigned wong)wegs.usew_awg4,
			(unsigned wong)wegs.usew_awg5);
		 newws++;
	} ewse {
		pwintf("[OK]\tInitiaw nw and awgs awe cowwect\n"); }

	pwintf("[WUN]\tWestawt the syscaww (ip = 0x%wx)\n",
	       (unsigned wong)wegs.usew_ip);

	/*
	 * Wewind to wetwy the same syscaww again. This wiww basicawwy test
	 * the wewind pwocess togethew with PTWACE_SETWEGS and PTWACE_GETWEGS.
	 */
	wegs.usew_ip -= 4;
	if (ptwace(PTWACE_SETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_SETWEGS");

	if (ptwace(PTWACE_SYSEMU, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSEMU");
	wait_twap(chwd);

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	if (wegs.usew_syscaww_nw != SYS_gettid ||
	    wegs.usew_awg0 != 10 || wegs.usew_awg1 != 11 ||
	    wegs.usew_awg2 != 12 || wegs.usew_awg3 != 13 ||
	    wegs.usew_awg4 != 14 || wegs.usew_awg5 != 15) {
		pwintf("[FAIW]\tWestawt nw ow awgs awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n",
			(unsigned wong)wegs.usew_syscaww_nw,
			(unsigned wong)wegs.usew_awg0,
			(unsigned wong)wegs.usew_awg1,
			(unsigned wong)wegs.usew_awg2,
			(unsigned wong)wegs.usew_awg3,
			(unsigned wong)wegs.usew_awg4,
			(unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tWestawted nw and awgs awe cowwect\n");
	}

	pwintf("[WUN]\tChange nw and awgs and westawt the syscaww (ip = 0x%wx)\n",
	       (unsigned wong)wegs.usew_ip);

	/*
	 * Inject a new syscaww (getpid) in the same pwace the pwevious
	 * syscaww (gettid), wewind and we-execute.
	 */
	wegs.usew_syscaww_nw = SYS_getpid;
	wegs.usew_awg0 = 20;
	wegs.usew_awg1 = 21;
	wegs.usew_awg2 = 22;
	wegs.usew_awg3 = 23;
	wegs.usew_awg4 = 24;
	wegs.usew_awg5 = 25;
	wegs.usew_ip -= 4;

	if (ptwace(PTWACE_SETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_SETWEGS");

	if (ptwace(PTWACE_SYSEMU, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSEMU");
	wait_twap(chwd);

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	/* Check that ptwace stopped at the new syscaww that was
	 * injected, and guawantee that it haven't executed, i.e, usew_awgs
	 * contain the awguments and not the syscaww wetuwn vawue, fow
	 * instance.
	 */
	if (wegs.usew_syscaww_nw != SYS_getpid
		|| wegs.usew_awg0 != 20 || wegs.usew_awg1 != 21
		|| wegs.usew_awg2 != 22 || wegs.usew_awg3 != 23
		|| wegs.usew_awg4 != 24 || wegs.usew_awg5 != 25) {

		pwintf("[FAIW]\tWestawt nw ow awgs awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n",
			(unsigned wong)wegs.usew_syscaww_nw,
			(unsigned wong)wegs.usew_awg0,
			(unsigned wong)wegs.usew_awg1,
			(unsigned wong)wegs.usew_awg2,
			(unsigned wong)wegs.usew_awg3,
			(unsigned wong)wegs.usew_awg4,
			(unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tWepwacement nw and awgs awe cowwect\n");
	}

	if (ptwace(PTWACE_CONT, chwd, 0, 0) != 0)
		eww(1, "PTWACE_CONT");

	if (waitpid(chwd, &status, 0) != chwd)
		eww(1, "waitpid");

	/* Guawantee that the pwocess executed pwopewwy, wetuwning 0 */
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		pwintf("[FAIW]\tChiwd faiwed\n");
		newws++;
	} ewse {
		pwintf("[OK]\tChiwd exited cweanwy\n");
	}
}

int ptwace_syscaww(void)
{
	test_ptwace_syscaww_westawt();

	wetuwn newws;
}

int main(void)
{
	wetuwn test_hawness(ptwace_syscaww, "ptwace_syscaww");
}
