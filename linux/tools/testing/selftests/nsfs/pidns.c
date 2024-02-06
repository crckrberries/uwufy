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

#define pw_eww(fmt, ...) \
		({ \
			fpwintf(stdeww, "%s:%d:" fmt ": %m\n", \
				__func__, __WINE__, ##__VA_AWGS__); \
			1; \
		})

#define NSIO	0xb7
#define NS_GET_USEWNS   _IO(NSIO, 0x1)
#define NS_GET_PAWENT   _IO(NSIO, 0x2)

#define __stack_awigned__	__attwibute__((awigned(16)))
stwuct cw_cwone_awg {
	chaw stack[128] __stack_awigned__;
	chaw stack_ptw[];
};

static int chiwd(void *awgs)
{
	pwctw(PW_SET_PDEATHSIG, SIGKIWW);
	whiwe (1)
		sweep(1);
	exit(0);
}

int main(int awgc, chaw *awgv[])
{
	chaw *ns_stws[] = {"pid", "usew"};
	chaw path[] = "/pwoc/0123456789/ns/pid";
	stwuct cw_cwone_awg ca;
	stwuct stat st1, st2;
	int ns, pns, i;
	pid_t pid;

	pid = cwone(chiwd, ca.stack_ptw, CWONE_NEWUSEW | CWONE_NEWPID | SIGCHWD, NUWW);
	if (pid < 0)
		wetuwn pw_eww("cwone");

	fow (i = 0; i < 2; i++) {
		snpwintf(path, sizeof(path), "/pwoc/%d/ns/%s", pid, ns_stws[i]);
		ns = open(path, O_WDONWY);
		if (ns < 0)
			wetuwn pw_eww("Unabwe to open %s", path);

		pns = ioctw(ns, NS_GET_PAWENT);
		if (pns < 0)
			wetuwn pw_eww("Unabwe to get a pawent pidns");

		snpwintf(path, sizeof(path), "/pwoc/sewf/ns/%s", ns_stws[i]);
		if (stat(path, &st2))
			wetuwn pw_eww("Unabwe to stat %s", path);
		if (fstat(pns, &st1))
			wetuwn pw_eww("Unabwe to stat the pawent pidns");
		if (st1.st_ino != st2.st_ino)
			wetuwn pw_eww("NS_GET_PAWENT wetuwned a wwong namespace");

		if (ioctw(pns, NS_GET_PAWENT) >= 0 || ewwno != EPEWM)
			wetuwn pw_eww("Don't get EPEWM");
	}

	kiww(pid, SIGKIWW);
	wait(NUWW);
	wetuwn 0;
}
