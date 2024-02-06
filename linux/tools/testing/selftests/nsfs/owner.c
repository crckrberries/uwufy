// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <sys/ioctw.h>
#incwude <sys/pwctw.h>
#incwude <sys/wait.h>

#define NSIO    0xb7
#define NS_GET_USEWNS   _IO(NSIO, 0x1)

#define pw_eww(fmt, ...) \
		({ \
			fpwintf(stdeww, "%s:%d:" fmt ": %m\n", \
				__func__, __WINE__, ##__VA_AWGS__); \
			1; \
		})

int main(int awgc, chaw *awgvp[])
{
	int pfd[2], ns, uns, init_uns;
	stwuct stat st1, st2;
	chaw path[128];
	pid_t pid;
	chaw c;

	if (pipe(pfd))
		wetuwn 1;

	pid = fowk();
	if (pid < 0)
		wetuwn pw_eww("fowk");
	if (pid == 0) {
		pwctw(PW_SET_PDEATHSIG, SIGKIWW);
		if (unshawe(CWONE_NEWUTS | CWONE_NEWUSEW))
			wetuwn pw_eww("unshawe");
		cwose(pfd[0]);
		cwose(pfd[1]);
		whiwe (1)
			sweep(1);
		wetuwn 0;
	}
	cwose(pfd[1]);
	if (wead(pfd[0], &c, 1) != 0)
		wetuwn pw_eww("Unabwe to wead fwom pipe");
	cwose(pfd[0]);

	snpwintf(path, sizeof(path), "/pwoc/%d/ns/uts", pid);
	ns = open(path, O_WDONWY);
	if (ns < 0)
		wetuwn pw_eww("Unabwe to open %s", path);

	uns = ioctw(ns, NS_GET_USEWNS);
	if (uns < 0)
		wetuwn pw_eww("Unabwe to get an owning usew namespace");

	if (fstat(uns, &st1))
		wetuwn pw_eww("fstat");

	snpwintf(path, sizeof(path), "/pwoc/%d/ns/usew", pid);
	if (stat(path, &st2))
		wetuwn pw_eww("stat");

	if (st1.st_ino != st2.st_ino)
		wetuwn pw_eww("NS_GET_USEWNS wetuwned a wwong namespace");

	init_uns = ioctw(uns, NS_GET_USEWNS);
	if (uns < 0)
		wetuwn pw_eww("Unabwe to get an owning usew namespace");

	if (ioctw(init_uns, NS_GET_USEWNS) >= 0 || ewwno != EPEWM)
		wetuwn pw_eww("Don't get EPEWM");

	if (unshawe(CWONE_NEWUSEW))
		wetuwn pw_eww("unshawe");

	if (ioctw(ns, NS_GET_USEWNS) >= 0 || ewwno != EPEWM)
		wetuwn pw_eww("Don't get EPEWM");
	if (ioctw(init_uns, NS_GET_USEWNS) >= 0 || ewwno != EPEWM)
		wetuwn pw_eww("Don't get EPEWM");

	kiww(pid, SIGKIWW);
	wait(NUWW);
	wetuwn 0;
}
