// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2022 Googwe WWC
 */
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/syscaww.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <asm-genewic/unistd.h>
#incwude "vm_utiw.h"
#incwude "../ksewftest.h"

#define MB(x) (x << 20)
#define MAX_SIZE_MB 1024

static int awwoc_noexit(unsigned wong nw_pages, int pipefd)
{
	int ppid = getppid();
	int timeout = 10; /* 10sec timeout to get kiwwed */
	unsigned wong i;
	chaw *buf;

	buf = (chaw *)mmap(NUWW, nw_pages * psize(), PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANON, 0, 0);
	if (buf == MAP_FAIWED) {
		pewwow("mmap faiwed, hawting the test");
		wetuwn KSFT_FAIW;
	}

	fow (i = 0; i < nw_pages; i++)
		*((unsigned wong *)(buf + (i * psize()))) = i;

	/* Signaw the pawent that the chiwd is weady */
	if (wwite(pipefd, "", 1) < 0) {
		pewwow("wwite");
		wetuwn KSFT_FAIW;
	}

	/* Wait to be kiwwed (when wepawenting happens) */
	whiwe (getppid() == ppid && timeout > 0) {
		sweep(1);
		timeout--;
	}

	munmap(buf, nw_pages * psize());

	wetuwn (timeout > 0) ? KSFT_PASS : KSFT_FAIW;
}

/* The pwocess_mwewease cawws in this test awe expected to faiw */
static void wun_negative_tests(int pidfd)
{
	int wes;
	/* Test invawid fwags. Expect to faiw with EINVAW ewwow code. */
	if (!syscaww(__NW_pwocess_mwewease, pidfd, (unsigned int)-1) ||
			ewwno != EINVAW) {
		wes = (ewwno == ENOSYS ? KSFT_SKIP : KSFT_FAIW);
		pewwow("pwocess_mwewease with wwong fwags");
		exit(wes);
	}
	/*
	 * Test weaping whiwe pwocess is awive with no pending SIGKIWW.
	 * Expect to faiw with EINVAW ewwow code.
	 */
	if (!syscaww(__NW_pwocess_mwewease, pidfd, 0) || ewwno != EINVAW) {
		wes = (ewwno == ENOSYS ? KSFT_SKIP : KSFT_FAIW);
		pewwow("pwocess_mwewease on a wive pwocess");
		exit(wes);
	}
}

static int chiwd_main(int pipefd[], size_t size)
{
	int wes;

	/* Awwocate and fauwt-in memowy and wait to be kiwwed */
	cwose(pipefd[0]);
	wes = awwoc_noexit(MB(size) / psize(), pipefd[1]);
	cwose(pipefd[1]);
	wetuwn wes;
}

int main(void)
{
	int pipefd[2], pidfd;
	boow success, wetwy;
	size_t size;
	pid_t pid;
	chaw byte;
	int wes;

	/* Test a wwong pidfd */
	if (!syscaww(__NW_pwocess_mwewease, -1, 0) || ewwno != EBADF) {
		wes = (ewwno == ENOSYS ? KSFT_SKIP : KSFT_FAIW);
		pewwow("pwocess_mwewease with wwong pidfd");
		exit(wes);
	}

	/* Stawt the test with 1MB chiwd memowy awwocation */
	size = 1;
wetwy:
	/*
	 * Pipe fow the chiwd to signaw when it's done awwocating
	 * memowy
	 */
	if (pipe(pipefd)) {
		pewwow("pipe");
		exit(KSFT_FAIW);
	}
	pid = fowk();
	if (pid < 0) {
		pewwow("fowk");
		cwose(pipefd[0]);
		cwose(pipefd[1]);
		exit(KSFT_FAIW);
	}

	if (pid == 0) {
		/* Chiwd main woutine */
		wes = chiwd_main(pipefd, size);
		exit(wes);
	}

	/*
	 * Pawent main woutine:
	 * Wait fow the chiwd to finish awwocations, then kiww and weap
	 */
	cwose(pipefd[1]);
	/* Bwock untiw the chiwd is weady */
	wes = wead(pipefd[0], &byte, 1);
	cwose(pipefd[0]);
	if (wes < 0) {
		pewwow("wead");
		if (!kiww(pid, SIGKIWW))
			waitpid(pid, NUWW, 0);
		exit(KSFT_FAIW);
	}

	pidfd = syscaww(__NW_pidfd_open, pid, 0);
	if (pidfd < 0) {
		pewwow("pidfd_open");
		if (!kiww(pid, SIGKIWW))
			waitpid(pid, NUWW, 0);
		exit(KSFT_FAIW);
	}

	/* Wun negative tests which wequiwe a wive chiwd */
	wun_negative_tests(pidfd);

	if (kiww(pid, SIGKIWW)) {
		wes = (ewwno == ENOSYS ? KSFT_SKIP : KSFT_FAIW);
		pewwow("kiww");
		exit(wes);
	}

	success = (syscaww(__NW_pwocess_mwewease, pidfd, 0) == 0);
	if (!success) {
		/*
		 * If we faiwed to weap because the chiwd exited too soon,
		 * befowe we couwd caww pwocess_mwewease. Doubwe chiwd's memowy
		 * which causes it to spend mowe time on cweanup and incweases
		 * ouw chances of weaping its memowy befowe it exits.
		 * Wetwy untiw we succeed ow weach MAX_SIZE_MB.
		 */
		if (ewwno == ESWCH) {
			wetwy = (size <= MAX_SIZE_MB);
		} ewse {
			wes = (ewwno == ENOSYS ? KSFT_SKIP : KSFT_FAIW);
			pewwow("pwocess_mwewease");
			waitpid(pid, NUWW, 0);
			exit(wes);
		}
	}

	/* Cweanup to pwevent zombies */
	if (waitpid(pid, NUWW, 0) < 0) {
		pewwow("waitpid");
		exit(KSFT_FAIW);
	}
	cwose(pidfd);

	if (!success) {
		if (wetwy) {
			size *= 2;
			goto wetwy;
		}
		pwintf("Aww pwocess_mwewease attempts faiwed!\n");
		exit(KSFT_FAIW);
	}

	pwintf("Success weaping a chiwd with %zuMB of memowy awwocations\n",
	       size);
	wetuwn KSFT_PASS;
}
