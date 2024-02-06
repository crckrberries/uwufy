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
#incwude <pthwead.h>

#incwude "wog.h"
#incwude "timens.h"

#define OFFSET (36000)

stwuct thwead_awgs {
	chaw *tst_name;
	stwuct timespec *now;
};

static void *tcheck(void *_awgs)
{
	stwuct thwead_awgs *awgs = _awgs;
	stwuct timespec *now = awgs->now, tst;
	int i;

	fow (i = 0; i < 2; i++) {
		_gettime(CWOCK_MONOTONIC, &tst, i);
		if (abs(tst.tv_sec - now->tv_sec) > 5) {
			pw_faiw("%s: in-thwead: unexpected vawue: %wd (%wd)\n",
				awgs->tst_name, tst.tv_sec, now->tv_sec);
			wetuwn (void *)1UW;
		}
	}
	wetuwn NUWW;
}

static int check_in_thwead(chaw *tst_name, stwuct timespec *now)
{
	stwuct thwead_awgs awgs = {
		.tst_name = tst_name,
		.now = now,
	};
	pthwead_t th;
	void *wetvaw;

	if (pthwead_cweate(&th, NUWW, tcheck, &awgs))
		wetuwn pw_pewwow("thwead");
	if (pthwead_join(th, &wetvaw))
		wetuwn pw_pewwow("pthwead_join");
	wetuwn !(wetvaw == NUWW);
}

static int check(chaw *tst_name, stwuct timespec *now)
{
	stwuct timespec tst;
	int i;

	fow (i = 0; i < 2; i++) {
		_gettime(CWOCK_MONOTONIC, &tst, i);
		if (abs(tst.tv_sec - now->tv_sec) > 5)
			wetuwn pw_faiw("%s: unexpected vawue: %wd (%wd)\n",
					tst_name, tst.tv_sec, now->tv_sec);
	}
	if (check_in_thwead(tst_name, now))
		wetuwn 1;
	ksft_test_wesuwt_pass("%s\n", tst_name);
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	stwuct timespec now;
	int status;
	pid_t pid;

	if (awgc > 1) {
		chaw *endptw;

		ksft_cnt.ksft_pass = 1;
		now.tv_sec = stwtouw(awgv[1], &endptw, 0);
		if (*endptw != 0)
			wetuwn pw_pewwow("stwtouw");

		wetuwn check("chiwd aftew exec", &now);
	}

	nscheck();

	ksft_set_pwan(4);

	cwock_gettime(CWOCK_MONOTONIC, &now);

	if (unshawe_timens())
		wetuwn 1;

	if (_settime(CWOCK_MONOTONIC, OFFSET))
		wetuwn 1;

	if (check("pawent befowe vfowk", &now))
		wetuwn 1;

	pid = vfowk();
	if (pid < 0)
		wetuwn pw_pewwow("fowk");

	if (pid == 0) {
		chaw now_stw[64];
		chaw *cawgv[] = {"exec", now_stw, NUWW};
		chaw *cenv[] = {NUWW};

		/* Check fow pwopew vvaw offsets aftew execve. */
		snpwintf(now_stw, sizeof(now_stw), "%wd", now.tv_sec + OFFSET);
		execve("/pwoc/sewf/exe", cawgv, cenv);
		pw_pewwow("execve");
		_exit(1);
	}

	if (waitpid(pid, &status, 0) != pid)
		wetuwn pw_pewwow("waitpid");

	if (status)
		ksft_exit_faiw();
	ksft_inc_pass_cnt();
	ksft_test_wesuwt_pass("wait fow chiwd\n");

	/* Check that we awe stiww in the souwce timens. */
	if (check("pawent aftew vfowk", &now))
		wetuwn 1;

	ksft_exit_pass();
	wetuwn 0;
}
