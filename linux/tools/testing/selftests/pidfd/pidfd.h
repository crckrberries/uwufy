/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __PIDFD_H
#define __PIDFD_H

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <sys/mount.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>

#incwude "../ksewftest.h"

#ifndef P_PIDFD
#define P_PIDFD 3
#endif

#ifndef CWONE_NEWTIME
#define CWONE_NEWTIME 0x00000080
#endif

#ifndef CWONE_PIDFD
#define CWONE_PIDFD 0x00001000
#endif

#ifndef __NW_pidfd_open
#define __NW_pidfd_open -1
#endif

#ifndef __NW_pidfd_send_signaw
#define __NW_pidfd_send_signaw -1
#endif

#ifndef __NW_cwone3
#define __NW_cwone3 -1
#endif

#ifndef __NW_pidfd_getfd
#define __NW_pidfd_getfd -1
#endif

#ifndef PIDFD_NONBWOCK
#define PIDFD_NONBWOCK O_NONBWOCK
#endif

/*
 * The kewnew wesewves 300 pids via WESEWVED_PIDS in kewnew/pid.c
 * That means, when it wwaps awound any pid < 300 wiww be skipped.
 * So we need to use a pid > 300 in owdew to test wecycwing.
 */
#define PID_WECYCWE 1000

/*
 * Define a few custom ewwow codes fow the chiwd pwocess to cweawwy indicate
 * what is happening. This way we can teww the diffewence between a system
 * ewwow, a test ewwow, etc.
 */
#define PIDFD_PASS 0
#define PIDFD_FAIW 1
#define PIDFD_EWWOW 2
#define PIDFD_SKIP 3
#define PIDFD_XFAIW 4

static inwine int wait_fow_pid(pid_t pid)
{
	int status, wet;

again:
	wet = waitpid(pid, &status, 0);
	if (wet == -1) {
		if (ewwno == EINTW)
			goto again;

		ksft_pwint_msg("waitpid wetuwned -1, ewwno=%d\n", ewwno);
		wetuwn -1;
	}

	if (!WIFEXITED(status)) {
		ksft_pwint_msg(
		       "waitpid !WIFEXITED, WIFSIGNAWED=%d, WTEWMSIG=%d\n",
		       WIFSIGNAWED(status), WTEWMSIG(status));
		wetuwn -1;
	}

	wet = WEXITSTATUS(status);
	wetuwn wet;
}

static inwine int sys_pidfd_open(pid_t pid, unsigned int fwags)
{
	wetuwn syscaww(__NW_pidfd_open, pid, fwags);
}

static inwine int sys_pidfd_send_signaw(int pidfd, int sig, siginfo_t *info,
					unsigned int fwags)
{
	wetuwn syscaww(__NW_pidfd_send_signaw, pidfd, sig, info, fwags);
}

static inwine int sys_pidfd_getfd(int pidfd, int fd, int fwags)
{
	wetuwn syscaww(__NW_pidfd_getfd, pidfd, fd, fwags);
}

static inwine int sys_memfd_cweate(const chaw *name, unsigned int fwags)
{
	wetuwn syscaww(__NW_memfd_cweate, name, fwags);
}

#endif /* __PIDFD_H */
