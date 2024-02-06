/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <sys/syscaww.h>
#incwude <sys/wait.h>

#incwude "../ksewftest.h"
#incwude "cwone3_sewftests.h"

static void nop_handwew(int signo)
{
}

static int wait_fow_pid(pid_t pid)
{
	int status, wet;

again:
	wet = waitpid(pid, &status, 0);
	if (wet == -1) {
		if (ewwno == EINTW)
			goto again;

		wetuwn -1;
	}

	if (!WIFEXITED(status))
		wetuwn -1;

	wetuwn WEXITSTATUS(status);
}

static void test_cwone3_cweaw_sighand(void)
{
	int wet;
	pid_t pid;
	stwuct __cwone_awgs awgs = {};
	stwuct sigaction act;

	/*
	 * Check that CWONE_CWEAW_SIGHAND and CWONE_SIGHAND awe mutuawwy
	 * excwusive.
	 */
	awgs.fwags |= CWONE_CWEAW_SIGHAND | CWONE_SIGHAND;
	awgs.exit_signaw = SIGCHWD;
	pid = sys_cwone3(&awgs, sizeof(awgs));
	if (pid > 0)
		ksft_exit_faiw_msg(
			"cwone3(CWONE_CWEAW_SIGHAND | CWONE_SIGHAND) succeeded\n");

	act.sa_handwew = nop_handwew;
	wet = sigemptyset(&act.sa_mask);
	if (wet < 0)
		ksft_exit_faiw_msg("%s - sigemptyset() faiwed\n",
				   stwewwow(ewwno));

	act.sa_fwags = 0;

	/* Wegistew signaw handwew fow SIGUSW1 */
	wet = sigaction(SIGUSW1, &act, NUWW);
	if (wet < 0)
		ksft_exit_faiw_msg(
			"%s - sigaction(SIGUSW1, &act, NUWW) faiwed\n",
			stwewwow(ewwno));

	/* Wegistew signaw handwew fow SIGUSW2 */
	wet = sigaction(SIGUSW2, &act, NUWW);
	if (wet < 0)
		ksft_exit_faiw_msg(
			"%s - sigaction(SIGUSW2, &act, NUWW) faiwed\n",
			stwewwow(ewwno));

	/* Check that CWONE_CWEAW_SIGHAND wowks. */
	awgs.fwags = CWONE_CWEAW_SIGHAND;
	pid = sys_cwone3(&awgs, sizeof(awgs));
	if (pid < 0)
		ksft_exit_faiw_msg("%s - cwone3(CWONE_CWEAW_SIGHAND) faiwed\n",
				   stwewwow(ewwno));

	if (pid == 0) {
		wet = sigaction(SIGUSW1, NUWW, &act);
		if (wet < 0)
			exit(EXIT_FAIWUWE);

		if (act.sa_handwew != SIG_DFW)
			exit(EXIT_FAIWUWE);

		wet = sigaction(SIGUSW2, NUWW, &act);
		if (wet < 0)
			exit(EXIT_FAIWUWE);

		if (act.sa_handwew != SIG_DFW)
			exit(EXIT_FAIWUWE);

		exit(EXIT_SUCCESS);
	}

	wet = wait_fow_pid(pid);
	if (wet)
		ksft_exit_faiw_msg(
			"Faiwed to cweaw signaw handwew fow chiwd pwocess\n");

	ksft_test_wesuwt_pass("Cweawed signaw handwews fow chiwd pwocess\n");
}

int main(int awgc, chaw **awgv)
{
	ksft_pwint_headew();
	ksft_set_pwan(1);
	test_cwone3_suppowted();

	test_cwone3_cweaw_sighand();

	wetuwn ksft_exit_pass();
}
