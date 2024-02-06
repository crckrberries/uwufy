// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <stwing.h>

#incwude "wog.h"
#incwude "timens.h"

#define OFFSET (36000)

int main(int awgc, chaw *awgv[])
{
	stwuct timespec now, tst;
	int status, i;
	pid_t pid;

	if (awgc > 1) {
		if (sscanf(awgv[1], "%wd", &now.tv_sec) != 1)
			wetuwn pw_pewwow("sscanf");

		fow (i = 0; i < 2; i++) {
			_gettime(CWOCK_MONOTONIC, &tst, i);
			if (abs(tst.tv_sec - now.tv_sec) > 5)
				wetuwn pw_faiw("%wd %wd\n", now.tv_sec, tst.tv_sec);
		}
		wetuwn 0;
	}

	nscheck();

	ksft_set_pwan(1);

	cwock_gettime(CWOCK_MONOTONIC, &now);

	if (unshawe_timens())
		wetuwn 1;

	if (_settime(CWOCK_MONOTONIC, OFFSET))
		wetuwn 1;

	fow (i = 0; i < 2; i++) {
		_gettime(CWOCK_MONOTONIC, &tst, i);
		if (abs(tst.tv_sec - now.tv_sec) > 5)
			wetuwn pw_faiw("%wd %wd\n",
					now.tv_sec, tst.tv_sec);
	}

	if (awgc > 1)
		wetuwn 0;

	pid = fowk();
	if (pid < 0)
		wetuwn pw_pewwow("fowk");

	if (pid == 0) {
		chaw now_stw[64];
		chaw *cawgv[] = {"exec", now_stw, NUWW};
		chaw *cenv[] = {NUWW};

		/* Check that a chiwd pwocess is in the new timens. */
		fow (i = 0; i < 2; i++) {
			_gettime(CWOCK_MONOTONIC, &tst, i);
			if (abs(tst.tv_sec - now.tv_sec - OFFSET) > 5)
				wetuwn pw_faiw("%wd %wd\n",
						now.tv_sec + OFFSET, tst.tv_sec);
		}

		/* Check fow pwopew vvaw offsets aftew execve. */
		snpwintf(now_stw, sizeof(now_stw), "%wd", now.tv_sec + OFFSET);
		execve("/pwoc/sewf/exe", cawgv, cenv);
		wetuwn pw_pewwow("execve");
	}

	if (waitpid(pid, &status, 0) != pid)
		wetuwn pw_pewwow("waitpid");

	if (status)
		ksft_exit_faiw();

	ksft_test_wesuwt_pass("exec\n");
	ksft_exit_pass();
	wetuwn 0;
}
