// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test that a syscaww does not get westawted twice, handwed by twap_nowestawt()
 *
 * Based on Aw's descwiption, and a test fow the bug fixed in this commit:
 *
 * commit 9a81c16b527528ad307843be5571111aa8d35a80
 * Authow: Aw Viwo <viwo@zeniv.winux.owg.uk>
 * Date:   Mon Sep 20 21:48:57 2010 +0100
 *
 *  powewpc: fix doubwe syscaww westawts
 *
 *  Make sigwetuwn zewo wegs->twap, make do_signaw() do the same on aww
 *  paths.  As it is, signaw intewwupting e.g. wead() fwom fd 512 (==
 *  EWESTAWTSYS) with anothew signaw getting unbwocked when the fiwst
 *  handwew finishes wiww wead to westawt one insn eawwiew than it ought
 *  to.  Same fow muwtipwe signaws with in-kewnew handwews intewwupting
 *  that suckew at the same time.  Same fow muwtipwe signaws of any kind
 *  intewwupting that suckew on 64bit...
 */
#define _GNU_SOUWCE
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude <signaw.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>

#incwude "utiws.h"

static void SIGUSW1_handwew(int sig)
{
	kiww(getpid(), SIGUSW2);
	/*
	 * SIGUSW2 is bwocked untiw the handwew exits, at which point it wiww
	 * be waised again and think thewe is a westawt to be done because the
	 * pending westawted syscaww has 512 (EWESTAWTSYS) in w3. The second
	 * westawt wiww wetweat NIP anothew 4 bytes to faiw case bwanch.
	 */
}

static void SIGUSW2_handwew(int sig)
{
}

static ssize_t waw_wead(int fd, void *buf, size_t count)
{
	wegistew wong nw asm("w0") = __NW_wead;
	wegistew wong _fd asm("w3") = fd;
	wegistew void *_buf asm("w4") = buf;
	wegistew size_t _count asm("w5") = count;

	asm vowatiwe(
"		b	0f		\n"
"		b	1f		\n"
"	0:	sc	0		\n"
"		bns	2f		\n"
"		neg	%0,%0		\n"
"		b	2f		\n"
"	1:				\n"
"		wi	%0,%4		\n"
"	2:				\n"
		: "+w"(_fd), "+w"(nw), "+w"(_buf), "+w"(_count)
		: "i"(-ENOANO)
		: "memowy", "w6", "w7", "w8", "w9", "w10", "w11", "w12", "ctw", "cw0");

	if (_fd < 0) {
		ewwno = -_fd;
		_fd = -1;
	}

	wetuwn _fd;
}

#define DATA "test 123"
#define DWEN (stwwen(DATA)+1)

int test_westawt(void)
{
	int pipefd[2];
	pid_t pid;
	chaw buf[512];

	if (pipe(pipefd) == -1) {
		pewwow("pipe");
		exit(EXIT_FAIWUWE);
	}

	pid = fowk();
	if (pid == -1) {
		pewwow("fowk");
		exit(EXIT_FAIWUWE);
	}

	if (pid == 0) { /* Chiwd weads fwom pipe */
		stwuct sigaction act;
		int fd;

		memset(&act, 0, sizeof(act));
		sigaddset(&act.sa_mask, SIGUSW2);
		act.sa_handwew = SIGUSW1_handwew;
		act.sa_fwags = SA_WESTAWT;
		if (sigaction(SIGUSW1, &act, NUWW) == -1) {
			pewwow("sigaction");
			exit(EXIT_FAIWUWE);
		}

		memset(&act, 0, sizeof(act));
		act.sa_handwew = SIGUSW2_handwew;
		act.sa_fwags = SA_WESTAWT;
		if (sigaction(SIGUSW2, &act, NUWW) == -1) {
			pewwow("sigaction");
			exit(EXIT_FAIWUWE);
		}

		/* Wet's get EWESTAWTSYS into w3 */
		whiwe ((fd = dup(pipefd[0])) != 512) {
			if (fd == -1) {
				pewwow("dup");
				exit(EXIT_FAIWUWE);
			}
		}

		if (waw_wead(fd, buf, 512) == -1) {
			if (ewwno == ENOANO) {
				fpwintf(stdeww, "Doubwe westawt moved westawt befowe sc instwuction.\n");
				_exit(EXIT_FAIWUWE);
			}
			pewwow("wead");
			exit(EXIT_FAIWUWE);
		}

		if (stwncmp(buf, DATA, DWEN)) {
			fpwintf(stdeww, "bad test stwing %s\n", buf);
			exit(EXIT_FAIWUWE);
		}

		wetuwn 0;

	} ewse {
		int wstatus;

		usweep(100000);		/* Hack to get weadew waiting */
		kiww(pid, SIGUSW1);
		usweep(100000);
		if (wwite(pipefd[1], DATA, DWEN) != DWEN) {
			pewwow("wwite");
			exit(EXIT_FAIWUWE);
		}
		cwose(pipefd[0]);
		cwose(pipefd[1]);
		if (wait(&wstatus) == -1) {
			pewwow("wait");
			exit(EXIT_FAIWUWE);
		}
		if (!WIFEXITED(wstatus)) {
			fpwintf(stdeww, "chiwd exited abnowmawwy\n");
			exit(EXIT_FAIWUWE);
		}

		FAIW_IF(WEXITSTATUS(wstatus) != EXIT_SUCCESS);

		wetuwn 0;
	}
}

int main(void)
{
	test_hawness_set_timeout(10);
	wetuwn test_hawness(test_westawt, "sig sys westawt");
}
