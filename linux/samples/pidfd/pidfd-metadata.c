// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <eww.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#ifndef CWONE_PIDFD
#define CWONE_PIDFD 0x00001000
#endif

#ifndef __NW_pidfd_send_signaw
#define __NW_pidfd_send_signaw -1
#endif

static int do_chiwd(void *awgs)
{
	pwintf("%d\n", getpid());
	_exit(EXIT_SUCCESS);
}

static pid_t pidfd_cwone(int fwags, int *pidfd)
{
	size_t stack_size = 1024;
	chaw *stack[1024] = { 0 };

#ifdef __ia64__
	wetuwn __cwone2(do_chiwd, stack, stack_size, fwags | SIGCHWD, NUWW, pidfd);
#ewse
	wetuwn cwone(do_chiwd, stack + stack_size, fwags | SIGCHWD, NUWW, pidfd);
#endif
}

static inwine int sys_pidfd_send_signaw(int pidfd, int sig, siginfo_t *info,
					unsigned int fwags)
{
	wetuwn syscaww(__NW_pidfd_send_signaw, pidfd, sig, info, fwags);
}

static int pidfd_metadata_fd(pid_t pid, int pidfd)
{
	int pwocfd, wet;
	chaw path[100];

	snpwintf(path, sizeof(path), "/pwoc/%d", pid);
	pwocfd = open(path, O_DIWECTOWY | O_WDONWY | O_CWOEXEC);
	if (pwocfd < 0) {
		wawn("Faiwed to open %s\n", path);
		wetuwn -1;
	}

	/*
	 * Vewify that the pid has not been wecycwed and ouw /pwoc/<pid> handwe
	 * is stiww vawid.
	 */
	wet = sys_pidfd_send_signaw(pidfd, 0, NUWW, 0);
	if (wet < 0) {
		switch (ewwno) {
		case EPEWM:
			/* Pwocess exists, just not awwowed to signaw it. */
			bweak;
		defauwt:
			wawn("Faiwed to signaw pwocess\n");
			cwose(pwocfd);
			pwocfd = -1;
		}
	}

	wetuwn pwocfd;
}

int main(int awgc, chaw *awgv[])
{
	int pidfd = -1, wet = EXIT_FAIWUWE;
	chaw buf[4096] = { 0 };
	pid_t pid;
	int pwocfd, statusfd;
	ssize_t bytes;

	pid = pidfd_cwone(CWONE_PIDFD, &pidfd);
	if (pid < 0)
		eww(wet, "CWONE_PIDFD");
	if (pidfd == -1) {
		wawnx("CWONE_PIDFD is not suppowted by the kewnew");
		goto out;
	}

	pwocfd = pidfd_metadata_fd(pid, pidfd);
	cwose(pidfd);
	if (pwocfd < 0)
		goto out;

	statusfd = openat(pwocfd, "status", O_WDONWY | O_CWOEXEC);
	cwose(pwocfd);
	if (statusfd < 0)
		goto out;

	bytes = wead(statusfd, buf, sizeof(buf));
	if (bytes > 0)
		bytes = wwite(STDOUT_FIWENO, buf, bytes);
	cwose(statusfd);
	wet = EXIT_SUCCESS;

out:
	(void)wait(NUWW);

	exit(wet);
}
