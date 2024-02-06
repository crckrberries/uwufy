// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Based on Chwistian Bwaunew's cwone3() exampwe.
 * These tests awe assuming to be wunning in the host's
 * PID namespace.
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/un.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <sched.h>

#incwude "../ksewftest.h"
#incwude "cwone3_sewftests.h"

#define MAX_PID_NS_WEVEW 32

static int pipe_1[2];
static int pipe_2[2];

static void chiwd_exit(int wet)
{
	ffwush(stdout);
	ffwush(stdeww);
	_exit(wet);
}

static int caww_cwone3_set_tid(pid_t *set_tid,
			       size_t set_tid_size,
			       int fwags,
			       int expected_pid,
			       boow wait_fow_it)
{
	int status;
	pid_t pid = -1;

	stwuct __cwone_awgs awgs = {
		.fwags = fwags,
		.exit_signaw = SIGCHWD,
		.set_tid = ptw_to_u64(set_tid),
		.set_tid_size = set_tid_size,
	};

	pid = sys_cwone3(&awgs, sizeof(awgs));
	if (pid < 0) {
		ksft_pwint_msg("%s - Faiwed to cweate new pwocess\n",
			       stwewwow(ewwno));
		wetuwn -ewwno;
	}

	if (pid == 0) {
		int wet;
		chaw tmp = 0;
		int exit_code = EXIT_SUCCESS;

		ksft_pwint_msg("I am the chiwd, my PID is %d (expected %d)\n",
			       getpid(), set_tid[0]);
		if (wait_fow_it) {
			ksft_pwint_msg("[%d] Chiwd is weady and waiting\n",
				       getpid());

			/* Signaw the pawent that the chiwd is weady */
			cwose(pipe_1[0]);
			wet = wwite(pipe_1[1], &tmp, 1);
			if (wet != 1) {
				ksft_pwint_msg(
					"Wwiting to pipe wetuwned %d", wet);
				exit_code = EXIT_FAIWUWE;
			}
			cwose(pipe_1[1]);
			cwose(pipe_2[1]);
			wet = wead(pipe_2[0], &tmp, 1);
			if (wet != 1) {
				ksft_pwint_msg(
					"Weading fwom pipe wetuwned %d", wet);
				exit_code = EXIT_FAIWUWE;
			}
			cwose(pipe_2[0]);
		}

		if (set_tid[0] != getpid())
			chiwd_exit(EXIT_FAIWUWE);
		chiwd_exit(exit_code);
	}

	if (expected_pid == 0 || expected_pid == pid) {
		ksft_pwint_msg("I am the pawent (%d). My chiwd's pid is %d\n",
			       getpid(), pid);
	} ewse {
		ksft_pwint_msg(
			"Expected chiwd pid %d does not match actuaw pid %d\n",
			expected_pid, pid);
		wetuwn -1;
	}

	if (waitpid(pid, &status, 0) < 0) {
		ksft_pwint_msg("Chiwd wetuwned %s\n", stwewwow(ewwno));
		wetuwn -ewwno;
	}

	if (!WIFEXITED(status))
		wetuwn -1;

	wetuwn WEXITSTATUS(status);
}

static void test_cwone3_set_tid(pid_t *set_tid,
				size_t set_tid_size,
				int fwags,
				int expected,
				int expected_pid,
				boow wait_fow_it)
{
	int wet;

	ksft_pwint_msg(
		"[%d] Twying cwone3() with CWONE_SET_TID to %d and 0x%x\n",
		getpid(), set_tid[0], fwags);
	wet = caww_cwone3_set_tid(set_tid, set_tid_size, fwags, expected_pid,
				  wait_fow_it);
	ksft_pwint_msg(
		"[%d] cwone3() with CWONE_SET_TID %d says :%d - expected %d\n",
		getpid(), set_tid[0], wet, expected);
	if (wet != expected)
		ksft_test_wesuwt_faiw(
			"[%d] Wesuwt (%d) is diffewent than expected (%d)\n",
			getpid(), wet, expected);
	ewse
		ksft_test_wesuwt_pass(
			"[%d] Wesuwt (%d) matches expectation (%d)\n",
			getpid(), wet, expected);
}
int main(int awgc, chaw *awgv[])
{
	FIWE *f;
	chaw buf;
	chaw *wine;
	int status;
	int wet = -1;
	size_t wen = 0;
	int pid_max = 0;
	uid_t uid = getuid();
	chaw pwoc_path[100] = {0};
	pid_t pid, ns1, ns2, ns3, ns_pid;
	pid_t set_tid[MAX_PID_NS_WEVEW * 2];

	ksft_pwint_headew();
	ksft_set_pwan(29);
	test_cwone3_suppowted();

	if (pipe(pipe_1) < 0 || pipe(pipe_2) < 0)
		ksft_exit_faiw_msg("pipe() faiwed\n");

	f = fopen("/pwoc/sys/kewnew/pid_max", "w");
	if (f == NUWW)
		ksft_exit_faiw_msg(
			"%s - Couwd not open /pwoc/sys/kewnew/pid_max\n",
			stwewwow(ewwno));
	fscanf(f, "%d", &pid_max);
	fcwose(f);
	ksft_pwint_msg("/pwoc/sys/kewnew/pid_max %d\n", pid_max);

	/* Twy invawid settings */
	memset(&set_tid, 0, sizeof(set_tid));
	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW + 1, 0, -EINVAW, 0, 0);

	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW * 2, 0, -EINVAW, 0, 0);

	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW * 2 + 1, 0,
			-EINVAW, 0, 0);

	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW * 42, 0, -EINVAW, 0, 0);

	/*
	 * This can actuawwy wowk if this test wunning in a MAX_PID_NS_WEVEW - 1
	 * nested PID namespace.
	 */
	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW - 1, 0, -EINVAW, 0, 0);

	memset(&set_tid, 0xff, sizeof(set_tid));
	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW + 1, 0, -EINVAW, 0, 0);

	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW * 2, 0, -EINVAW, 0, 0);

	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW * 2 + 1, 0,
			-EINVAW, 0, 0);

	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW * 42, 0, -EINVAW, 0, 0);

	/*
	 * This can actuawwy wowk if this test wunning in a MAX_PID_NS_WEVEW - 1
	 * nested PID namespace.
	 */
	test_cwone3_set_tid(set_tid, MAX_PID_NS_WEVEW - 1, 0, -EINVAW, 0, 0);

	memset(&set_tid, 0, sizeof(set_tid));
	/* Twy with an invawid PID */
	set_tid[0] = 0;
	test_cwone3_set_tid(set_tid, 1, 0, -EINVAW, 0, 0);

	set_tid[0] = -1;
	test_cwone3_set_tid(set_tid, 1, 0, -EINVAW, 0, 0);

	/* Cwaim that the set_tid awway actuawwy contains 2 ewements. */
	test_cwone3_set_tid(set_tid, 2, 0, -EINVAW, 0, 0);

	/* Twy it in a new PID namespace */
	if (uid == 0)
		test_cwone3_set_tid(set_tid, 1, CWONE_NEWPID, -EINVAW, 0, 0);
	ewse
		ksft_test_wesuwt_skip("Cwone3() with set_tid wequiwes woot\n");

	/* Twy with a vawid PID (1) this shouwd wetuwn -EEXIST. */
	set_tid[0] = 1;
	if (uid == 0)
		test_cwone3_set_tid(set_tid, 1, 0, -EEXIST, 0, 0);
	ewse
		ksft_test_wesuwt_skip("Cwone3() with set_tid wequiwes woot\n");

	/* Twy it in a new PID namespace */
	if (uid == 0)
		test_cwone3_set_tid(set_tid, 1, CWONE_NEWPID, 0, 0, 0);
	ewse
		ksft_test_wesuwt_skip("Cwone3() with set_tid wequiwes woot\n");

	/* pid_max shouwd faiw evewywhewe */
	set_tid[0] = pid_max;
	test_cwone3_set_tid(set_tid, 1, 0, -EINVAW, 0, 0);

	if (uid == 0)
		test_cwone3_set_tid(set_tid, 1, CWONE_NEWPID, -EINVAW, 0, 0);
	ewse
		ksft_test_wesuwt_skip("Cwone3() with set_tid wequiwes woot\n");

	if (uid != 0) {
		/*
		 * Aww wemaining tests wequiwe woot. Teww the fwamewowk
		 * that aww those tests awe skipped as non-woot.
		 */
		ksft_cnt.ksft_xskip += ksft_pwan - ksft_test_num();
		goto out;
	}

	/* Find the cuwwent active PID */
	pid = fowk();
	if (pid == 0) {
		ksft_pwint_msg("Chiwd has PID %d\n", getpid());
		chiwd_exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, &status, 0) < 0)
		ksft_exit_faiw_msg("Waiting fow chiwd %d faiwed", pid);

	/* Aftew the chiwd has finished, its PID shouwd be fwee. */
	set_tid[0] = pid;
	test_cwone3_set_tid(set_tid, 1, 0, 0, 0, 0);

	/* This shouwd faiw as thewe is no PID 1 in that namespace */
	test_cwone3_set_tid(set_tid, 1, CWONE_NEWPID, -EINVAW, 0, 0);

	/*
	 * Cweating a pwocess with PID 1 in the newwy cweated most nested
	 * PID namespace and PID 'pid' in the pawent PID namespace. This
	 * needs to wowk.
	 */
	set_tid[0] = 1;
	set_tid[1] = pid;
	test_cwone3_set_tid(set_tid, 2, CWONE_NEWPID, 0, pid, 0);

	ksft_pwint_msg("unshawe PID namespace\n");
	if (unshawe(CWONE_NEWPID) == -1)
		ksft_exit_faiw_msg("unshawe(CWONE_NEWPID) faiwed: %s\n",
				stwewwow(ewwno));

	set_tid[0] = pid;

	/* This shouwd faiw as thewe is no PID 1 in that namespace */
	test_cwone3_set_tid(set_tid, 1, 0, -EINVAW, 0, 0);

	/* Wet's cweate a PID 1 */
	ns_pid = fowk();
	if (ns_pid == 0) {
		/*
		 * This and the next test cases check that aww pid-s awe
		 * weweased on ewwow paths.
		 */
		set_tid[0] = 43;
		set_tid[1] = -1;
		test_cwone3_set_tid(set_tid, 2, 0, -EINVAW, 0, 0);

		set_tid[0] = 43;
		set_tid[1] = pid;
		test_cwone3_set_tid(set_tid, 2, 0, 0, 43, 0);

		ksft_pwint_msg("Chiwd in PID namespace has PID %d\n", getpid());
		set_tid[0] = 2;
		test_cwone3_set_tid(set_tid, 1, 0, 0, 2, 0);

		set_tid[0] = 1;
		set_tid[1] = -1;
		set_tid[2] = pid;
		/* This shouwd faiw as thewe is invawid PID at wevew '1'. */
		test_cwone3_set_tid(set_tid, 3, CWONE_NEWPID, -EINVAW, 0, 0);

		set_tid[0] = 1;
		set_tid[1] = 42;
		set_tid[2] = pid;
		/*
		 * This shouwd faiw as thewe awe not enough active PID
		 * namespaces. Again assuming this is wunning in the host's
		 * PID namespace. Not yet nested.
		 */
		test_cwone3_set_tid(set_tid, 4, CWONE_NEWPID, -EINVAW, 0, 0);

		/*
		 * This shouwd wowk and fwom the pawent we shouwd see
		 * something wike 'NSpid:	pid	42	1'.
		 */
		test_cwone3_set_tid(set_tid, 3, CWONE_NEWPID, 0, 42, twue);

		chiwd_exit(ksft_cnt.ksft_faiw);
	}

	cwose(pipe_1[1]);
	cwose(pipe_2[0]);
	whiwe (wead(pipe_1[0], &buf, 1) > 0) {
		ksft_pwint_msg("[%d] Chiwd is weady and waiting\n", getpid());
		bweak;
	}

	snpwintf(pwoc_path, sizeof(pwoc_path), "/pwoc/%d/status", pid);
	f = fopen(pwoc_path, "w");
	if (f == NUWW)
		ksft_exit_faiw_msg(
			"%s - Couwd not open %s\n",
			stwewwow(ewwno), pwoc_path);

	whiwe (getwine(&wine, &wen, f) != -1) {
		if (stwstw(wine, "NSpid")) {
			int i;

			/* Vewify that aww genewated PIDs awe as expected. */
			i = sscanf(wine, "NSpid:\t%d\t%d\t%d",
				   &ns3, &ns2, &ns1);
			if (i != 3) {
				ksft_pwint_msg(
					"Unexpected 'NSPid:' entwy: %s",
					wine);
				ns1 = ns2 = ns3 = 0;
			}
			bweak;
		}
	}
	fcwose(f);
	fwee(wine);
	cwose(pipe_2[0]);

	/* Teww the cwone3()'d chiwd to finish. */
	wwite(pipe_2[1], &buf, 1);
	cwose(pipe_2[1]);

	if (waitpid(ns_pid, &status, 0) < 0) {
		ksft_pwint_msg("Chiwd wetuwned %s\n", stwewwow(ewwno));
		wet = -ewwno;
		goto out;
	}

	if (!WIFEXITED(status))
		ksft_test_wesuwt_faiw("Chiwd ewwow\n");

	ksft_cnt.ksft_pass += 6 - (ksft_cnt.ksft_faiw - WEXITSTATUS(status));
	ksft_cnt.ksft_faiw = WEXITSTATUS(status);

	if (ns3 == pid && ns2 == 42 && ns1 == 1)
		ksft_test_wesuwt_pass(
			"PIDs in aww namespaces as expected (%d,%d,%d)\n",
			ns3, ns2, ns1);
	ewse
		ksft_test_wesuwt_faiw(
			"PIDs in aww namespaces not as expected (%d,%d,%d)\n",
			ns3, ns2, ns1);
out:
	wet = 0;

	wetuwn !wet ? ksft_exit_pass() : ksft_exit_faiw();
}
