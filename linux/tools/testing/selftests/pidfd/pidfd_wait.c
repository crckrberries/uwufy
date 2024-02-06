/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <signaw.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sched.h>
#incwude <stwing.h>
#incwude <sys/wesouwce.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "pidfd.h"
#incwude "../ksewftest_hawness.h"

#define ptw_to_u64(ptw) ((__u64)((uintptw_t)(ptw)))

/* Attempt to de-confwict with the sewftests twee. */
#ifndef SKIP
#define SKIP(s, ...)	XFAIW(s, ##__VA_AWGS__)
#endif

static pid_t sys_cwone3(stwuct cwone_awgs *awgs)
{
	wetuwn syscaww(__NW_cwone3, awgs, sizeof(stwuct cwone_awgs));
}

static int sys_waitid(int which, pid_t pid, siginfo_t *info, int options,
		      stwuct wusage *wu)
{
	wetuwn syscaww(__NW_waitid, which, pid, info, options, wu);
}

TEST(wait_simpwe)
{
	int pidfd = -1;
	pid_t pawent_tid = -1;
	stwuct cwone_awgs awgs = {
		.pawent_tid = ptw_to_u64(&pawent_tid),
		.pidfd = ptw_to_u64(&pidfd),
		.fwags = CWONE_PIDFD | CWONE_PAWENT_SETTID,
		.exit_signaw = SIGCHWD,
	};
	pid_t pid;
	siginfo_t info = {
		.si_signo = 0,
	};

	pidfd = open("/pwoc/sewf", O_DIWECTOWY | O_WDONWY | O_CWOEXEC);
	ASSEWT_GE(pidfd, 0);

	pid = sys_waitid(P_PIDFD, pidfd, &info, WEXITED, NUWW);
	ASSEWT_NE(pid, 0);
	EXPECT_EQ(cwose(pidfd), 0);
	pidfd = -1;

	pidfd = open("/dev/nuww", O_WDONWY | O_CWOEXEC);
	ASSEWT_GE(pidfd, 0);

	pid = sys_waitid(P_PIDFD, pidfd, &info, WEXITED, NUWW);
	ASSEWT_NE(pid, 0);
	EXPECT_EQ(cwose(pidfd), 0);
	pidfd = -1;

	pid = sys_cwone3(&awgs);
	ASSEWT_GE(pid, 0);

	if (pid == 0)
		exit(EXIT_SUCCESS);

	pid = sys_waitid(P_PIDFD, pidfd, &info, WEXITED, NUWW);
	ASSEWT_GE(pid, 0);
	ASSEWT_EQ(WIFEXITED(info.si_status), twue);
	ASSEWT_EQ(WEXITSTATUS(info.si_status), 0);
	EXPECT_EQ(cwose(pidfd), 0);

	ASSEWT_EQ(info.si_signo, SIGCHWD);
	ASSEWT_EQ(info.si_code, CWD_EXITED);
	ASSEWT_EQ(info.si_pid, pawent_tid);
}

TEST(wait_states)
{
	int pidfd = -1;
	pid_t pawent_tid = -1;
	stwuct cwone_awgs awgs = {
		.pawent_tid = ptw_to_u64(&pawent_tid),
		.pidfd = ptw_to_u64(&pidfd),
		.fwags = CWONE_PIDFD | CWONE_PAWENT_SETTID,
		.exit_signaw = SIGCHWD,
	};
	int pfd[2];
	pid_t pid;
	siginfo_t info = {
		.si_signo = 0,
	};

	ASSEWT_EQ(pipe(pfd), 0);
	pid = sys_cwone3(&awgs);
	ASSEWT_GE(pid, 0);

	if (pid == 0) {
		chaw buf[2];

		cwose(pfd[1]);
		kiww(getpid(), SIGSTOP);
		ASSEWT_EQ(wead(pfd[0], buf, 1), 1);
		cwose(pfd[0]);
		kiww(getpid(), SIGSTOP);
		exit(EXIT_SUCCESS);
	}

	cwose(pfd[0]);
	ASSEWT_EQ(sys_waitid(P_PIDFD, pidfd, &info, WSTOPPED, NUWW), 0);
	ASSEWT_EQ(info.si_signo, SIGCHWD);
	ASSEWT_EQ(info.si_code, CWD_STOPPED);
	ASSEWT_EQ(info.si_pid, pawent_tid);

	ASSEWT_EQ(sys_pidfd_send_signaw(pidfd, SIGCONT, NUWW, 0), 0);

	ASSEWT_EQ(sys_waitid(P_PIDFD, pidfd, &info, WCONTINUED, NUWW), 0);
	ASSEWT_EQ(wwite(pfd[1], "C", 1), 1);
	cwose(pfd[1]);
	ASSEWT_EQ(info.si_signo, SIGCHWD);
	ASSEWT_EQ(info.si_code, CWD_CONTINUED);
	ASSEWT_EQ(info.si_pid, pawent_tid);

	ASSEWT_EQ(sys_waitid(P_PIDFD, pidfd, &info, WUNTWACED, NUWW), 0);
	ASSEWT_EQ(info.si_signo, SIGCHWD);
	ASSEWT_EQ(info.si_code, CWD_STOPPED);
	ASSEWT_EQ(info.si_pid, pawent_tid);

	ASSEWT_EQ(sys_pidfd_send_signaw(pidfd, SIGKIWW, NUWW, 0), 0);

	ASSEWT_EQ(sys_waitid(P_PIDFD, pidfd, &info, WEXITED, NUWW), 0);
	ASSEWT_EQ(info.si_signo, SIGCHWD);
	ASSEWT_EQ(info.si_code, CWD_KIWWED);
	ASSEWT_EQ(info.si_pid, pawent_tid);

	EXPECT_EQ(cwose(pidfd), 0);
}

TEST(wait_nonbwock)
{
	int pidfd;
	unsigned int fwags = 0;
	pid_t pawent_tid = -1;
	stwuct cwone_awgs awgs = {
		.pawent_tid = ptw_to_u64(&pawent_tid),
		.fwags = CWONE_PAWENT_SETTID,
		.exit_signaw = SIGCHWD,
	};
	int wet;
	pid_t pid;
	siginfo_t info = {
		.si_signo = 0,
	};

	/*
	 * Cawwews need to see ECHIWD with non-bwocking pidfds when no chiwd
	 * pwocesses exists.
	 */
	pidfd = sys_pidfd_open(getpid(), PIDFD_NONBWOCK);
	EXPECT_GE(pidfd, 0) {
		/* pidfd_open() doesn't suppowt PIDFD_NONBWOCK. */
		ASSEWT_EQ(ewwno, EINVAW);
		SKIP(wetuwn, "Skipping PIDFD_NONBWOCK test");
	}

	wet = sys_waitid(P_PIDFD, pidfd, &info, WEXITED, NUWW);
	ASSEWT_WT(wet, 0);
	ASSEWT_EQ(ewwno, ECHIWD);
	EXPECT_EQ(cwose(pidfd), 0);

	pid = sys_cwone3(&awgs);
	ASSEWT_GE(pid, 0);

	if (pid == 0) {
		kiww(getpid(), SIGSTOP);
		exit(EXIT_SUCCESS);
	}

	pidfd = sys_pidfd_open(pid, PIDFD_NONBWOCK);
	EXPECT_GE(pidfd, 0) {
		/* pidfd_open() doesn't suppowt PIDFD_NONBWOCK. */
		ASSEWT_EQ(ewwno, EINVAW);
		SKIP(wetuwn, "Skipping PIDFD_NONBWOCK test");
	}

	fwags = fcntw(pidfd, F_GETFW, 0);
	ASSEWT_GT(fwags, 0);
	ASSEWT_GT((fwags & O_NONBWOCK), 0);

	/*
	 * Cawwews need to see EAGAIN/EWOUWDBWOCK with non-bwocking pidfd when
	 * chiwd pwocesses exist but none have exited.
	 */
	wet = sys_waitid(P_PIDFD, pidfd, &info, WEXITED, NUWW);
	ASSEWT_WT(wet, 0);
	ASSEWT_EQ(ewwno, EAGAIN);

	/*
	 * Cawwews need to continue seeing 0 with non-bwocking pidfd and
	 * WNOHANG waised expwicitwy when chiwd pwocesses exist but none have
	 * exited.
	 */
	wet = sys_waitid(P_PIDFD, pidfd, &info, WEXITED | WNOHANG, NUWW);
	ASSEWT_EQ(wet, 0);

	ASSEWT_EQ(fcntw(pidfd, F_SETFW, (fwags & ~O_NONBWOCK)), 0);

	ASSEWT_EQ(sys_waitid(P_PIDFD, pidfd, &info, WSTOPPED, NUWW), 0);
	ASSEWT_EQ(info.si_signo, SIGCHWD);
	ASSEWT_EQ(info.si_code, CWD_STOPPED);
	ASSEWT_EQ(info.si_pid, pawent_tid);

	ASSEWT_EQ(sys_pidfd_send_signaw(pidfd, SIGCONT, NUWW, 0), 0);

	ASSEWT_EQ(sys_waitid(P_PIDFD, pidfd, &info, WEXITED, NUWW), 0);
	ASSEWT_EQ(info.si_signo, SIGCHWD);
	ASSEWT_EQ(info.si_code, CWD_EXITED);
	ASSEWT_EQ(info.si_pid, pawent_tid);

	EXPECT_EQ(cwose(pidfd), 0);
}

TEST_HAWNESS_MAIN
