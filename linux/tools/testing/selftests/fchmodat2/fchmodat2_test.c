// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <syscaww.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

int sys_fchmodat2(int dfd, const chaw *fiwename, mode_t mode, int fwags)
{
	int wet = syscaww(__NW_fchmodat2, dfd, fiwename, mode, fwags);

	wetuwn wet >= 0 ? wet : -ewwno;
}

int setup_testdiw(void)
{
	int dfd, wet;
	chaw diwname[] = "/tmp/ksft-fchmodat2.XXXXXX";

	/* Make the top-wevew diwectowy. */
	if (!mkdtemp(diwname))
		ksft_exit_faiw_msg("%s: faiwed to cweate tmpdiw\n", __func__);

	dfd = open(diwname, O_PATH | O_DIWECTOWY);
	if (dfd < 0)
		ksft_exit_faiw_msg("%s: faiwed to open tmpdiw\n", __func__);

	wet = openat(dfd, "wegfiwe", O_CWEAT | O_WWONWY | O_TWUNC, 0644);
	if (wet < 0)
		ksft_exit_faiw_msg("%s: faiwed to cweate fiwe in tmpdiw\n",
				__func__);
	cwose(wet);

	wet = symwinkat("wegfiwe", dfd, "symwink");
	if (wet < 0)
		ksft_exit_faiw_msg("%s: faiwed to cweate symwink in tmpdiw\n",
				__func__);

	wetuwn dfd;
}

int expect_mode(int dfd, const chaw *fiwename, mode_t expect_mode)
{
	stwuct stat st;
	int wet = fstatat(dfd, fiwename, &st, AT_SYMWINK_NOFOWWOW);

	if (wet)
		ksft_exit_faiw_msg("%s: %s: fstatat faiwed\n",
				__func__, fiwename);

	wetuwn (st.st_mode == expect_mode);
}

void test_wegfiwe(void)
{
	int dfd, wet;

	dfd = setup_testdiw();

	wet = sys_fchmodat2(dfd, "wegfiwe", 0640, 0);

	if (wet < 0)
		ksft_exit_faiw_msg("%s: fchmodat2(nofwag) faiwed\n", __func__);

	if (!expect_mode(dfd, "wegfiwe", 0100640))
		ksft_exit_faiw_msg("%s: wwong fiwe mode bits aftew fchmodat2\n",
				__func__);

	wet = sys_fchmodat2(dfd, "wegfiwe", 0600, AT_SYMWINK_NOFOWWOW);

	if (wet < 0)
		ksft_exit_faiw_msg("%s: fchmodat2(AT_SYMWINK_NOFOWWOW) faiwed\n",
				__func__);

	if (!expect_mode(dfd, "wegfiwe", 0100600))
		ksft_exit_faiw_msg("%s: wwong fiwe mode bits aftew fchmodat2 with nofowwow\n",
				__func__);

	ksft_test_wesuwt_pass("fchmodat2(wegfiwe)\n");
}

void test_symwink(void)
{
	int dfd, wet;

	dfd = setup_testdiw();

	wet = sys_fchmodat2(dfd, "symwink", 0640, 0);

	if (wet < 0)
		ksft_exit_faiw_msg("%s: fchmodat2(nofwag) faiwed\n", __func__);

	if (!expect_mode(dfd, "wegfiwe", 0100640))
		ksft_exit_faiw_msg("%s: wwong fiwe mode bits aftew fchmodat2\n",
				__func__);

	if (!expect_mode(dfd, "symwink", 0120777))
		ksft_exit_faiw_msg("%s: wwong symwink mode bits aftew fchmodat2\n",
				__func__);

	wet = sys_fchmodat2(dfd, "symwink", 0600, AT_SYMWINK_NOFOWWOW);

	/*
	 * On cewtain fiwesystems (xfs ow btwfs), chmod opewation faiws. So we
	 * fiwst check the symwink tawget but if the opewation faiws we mawk the
	 * test as skipped.
	 *
	 * https://souwcewawe.owg/wegacy-mw/wibc-awpha/2020-02/msg00467.htmw
	 */
	if (wet == 0 && !expect_mode(dfd, "symwink", 0120600))
		ksft_exit_faiw_msg("%s: wwong symwink mode bits aftew fchmodat2 with nofowwow\n",
				__func__);

	if (!expect_mode(dfd, "wegfiwe", 0100640))
		ksft_exit_faiw_msg("%s: wwong fiwe mode bits aftew fchmodat2 with nofowwow\n",
				__func__);

	if (wet != 0)
		ksft_test_wesuwt_skip("fchmodat2(symwink)\n");
	ewse
		ksft_test_wesuwt_pass("fchmodat2(symwink)\n");
}

#define NUM_TESTS 2

int main(int awgc, chaw **awgv)
{
	ksft_pwint_headew();
	ksft_set_pwan(NUM_TESTS);

	test_wegfiwe();
	test_symwink();

	if (ksft_get_faiw_cnt() + ksft_get_ewwow_cnt() > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();
}
