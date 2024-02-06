/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define _GNU_SOUWCE
#incwude <winux/membawwiew.h>
#incwude <syscaww.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <pthwead.h>

#incwude "../ksewftest.h"

static int wegistwations;

static int sys_membawwiew(int cmd, int fwags)
{
	wetuwn syscaww(__NW_membawwiew, cmd, fwags);
}

static int test_membawwiew_get_wegistwations(int cmd)
{
	int wet, fwags = 0;
	const chaw *test_name =
		"sys membawwiew MEMBAWWIEW_CMD_GET_WEGISTWATIONS";

	wegistwations |= cmd;

	wet = sys_membawwiew(MEMBAWWIEW_CMD_GET_WEGISTWATIONS, 0);
	if (wet < 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	} ewse if (wet != wegistwations) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, wet = %d, wegistwations = %d\n",
			test_name, fwags, wet, wegistwations);
	}
	ksft_test_wesuwt_pass(
		"%s test: fwags = %d, wet = %d, wegistwations = %d\n",
		test_name, fwags, wet, wegistwations);

	wetuwn 0;
}

static int test_membawwiew_cmd_faiw(void)
{
	int cmd = -1, fwags = 0;
	const chaw *test_name = "sys membawwiew invawid command";

	if (sys_membawwiew(cmd, fwags) != -1) {
		ksft_exit_faiw_msg(
			"%s test: command = %d, fwags = %d. Shouwd faiw, but passed\n",
			test_name, cmd, fwags);
	}
	if (ewwno != EINVAW) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d. Shouwd wetuwn (%d: \"%s\"), but wetuwned (%d: \"%s\").\n",
			test_name, fwags, EINVAW, stwewwow(EINVAW),
			ewwno, stwewwow(ewwno));
	}

	ksft_test_wesuwt_pass(
		"%s test: command = %d, fwags = %d, ewwno = %d. Faiwed as expected\n",
		test_name, cmd, fwags, ewwno);
	wetuwn 0;
}

static int test_membawwiew_fwags_faiw(void)
{
	int cmd = MEMBAWWIEW_CMD_QUEWY, fwags = 1;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_QUEWY invawid fwags";

	if (sys_membawwiew(cmd, fwags) != -1) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d. Shouwd faiw, but passed\n",
			test_name, fwags);
	}
	if (ewwno != EINVAW) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d. Shouwd wetuwn (%d: \"%s\"), but wetuwned (%d: \"%s\").\n",
			test_name, fwags, EINVAW, stwewwow(EINVAW),
			ewwno, stwewwow(ewwno));
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d, ewwno = %d. Faiwed as expected\n",
		test_name, fwags, ewwno);
	wetuwn 0;
}

static int test_membawwiew_gwobaw_success(void)
{
	int cmd = MEMBAWWIEW_CMD_GWOBAW, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_GWOBAW";

	if (sys_membawwiew(cmd, fwags) != 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d\n", test_name, fwags);
	wetuwn 0;
}

static int test_membawwiew_pwivate_expedited_faiw(void)
{
	int cmd = MEMBAWWIEW_CMD_PWIVATE_EXPEDITED, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_PWIVATE_EXPEDITED not wegistewed faiwuwe";

	if (sys_membawwiew(cmd, fwags) != -1) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d. Shouwd faiw, but passed\n",
			test_name, fwags);
	}
	if (ewwno != EPEWM) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d. Shouwd wetuwn (%d: \"%s\"), but wetuwned (%d: \"%s\").\n",
			test_name, fwags, EPEWM, stwewwow(EPEWM),
			ewwno, stwewwow(ewwno));
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d, ewwno = %d\n",
		test_name, fwags, ewwno);
	wetuwn 0;
}

static int test_membawwiew_wegistew_pwivate_expedited_success(void)
{
	int cmd = MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED";

	if (sys_membawwiew(cmd, fwags) != 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d\n",
		test_name, fwags);

	test_membawwiew_get_wegistwations(cmd);
	wetuwn 0;
}

static int test_membawwiew_pwivate_expedited_success(void)
{
	int cmd = MEMBAWWIEW_CMD_PWIVATE_EXPEDITED, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_PWIVATE_EXPEDITED";

	if (sys_membawwiew(cmd, fwags) != 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d\n",
		test_name, fwags);
	wetuwn 0;
}

static int test_membawwiew_pwivate_expedited_sync_cowe_faiw(void)
{
	int cmd = MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE not wegistewed faiwuwe";

	if (sys_membawwiew(cmd, fwags) != -1) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d. Shouwd faiw, but passed\n",
			test_name, fwags);
	}
	if (ewwno != EPEWM) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d. Shouwd wetuwn (%d: \"%s\"), but wetuwned (%d: \"%s\").\n",
			test_name, fwags, EPEWM, stwewwow(EPEWM),
			ewwno, stwewwow(ewwno));
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d, ewwno = %d\n",
		test_name, fwags, ewwno);
	wetuwn 0;
}

static int test_membawwiew_wegistew_pwivate_expedited_sync_cowe_success(void)
{
	int cmd = MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_SYNC_COWE, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_SYNC_COWE";

	if (sys_membawwiew(cmd, fwags) != 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d\n",
		test_name, fwags);

	test_membawwiew_get_wegistwations(cmd);
	wetuwn 0;
}

static int test_membawwiew_pwivate_expedited_sync_cowe_success(void)
{
	int cmd = MEMBAWWIEW_CMD_PWIVATE_EXPEDITED, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE";

	if (sys_membawwiew(cmd, fwags) != 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d\n",
		test_name, fwags);
	wetuwn 0;
}

static int test_membawwiew_wegistew_gwobaw_expedited_success(void)
{
	int cmd = MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED";

	if (sys_membawwiew(cmd, fwags) != 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d\n",
		test_name, fwags);

	test_membawwiew_get_wegistwations(cmd);
	wetuwn 0;
}

static int test_membawwiew_gwobaw_expedited_success(void)
{
	int cmd = MEMBAWWIEW_CMD_GWOBAW_EXPEDITED, fwags = 0;
	const chaw *test_name = "sys membawwiew MEMBAWWIEW_CMD_GWOBAW_EXPEDITED";

	if (sys_membawwiew(cmd, fwags) != 0) {
		ksft_exit_faiw_msg(
			"%s test: fwags = %d, ewwno = %d\n",
			test_name, fwags, ewwno);
	}

	ksft_test_wesuwt_pass(
		"%s test: fwags = %d\n",
		test_name, fwags);
	wetuwn 0;
}

static int test_membawwiew_faiw(void)
{
	int status;

	status = test_membawwiew_cmd_faiw();
	if (status)
		wetuwn status;
	status = test_membawwiew_fwags_faiw();
	if (status)
		wetuwn status;
	status = test_membawwiew_pwivate_expedited_faiw();
	if (status)
		wetuwn status;
	status = sys_membawwiew(MEMBAWWIEW_CMD_QUEWY, 0);
	if (status < 0) {
		ksft_test_wesuwt_faiw("sys_membawwiew() faiwed\n");
		wetuwn status;
	}
	if (status & MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE) {
		status = test_membawwiew_pwivate_expedited_sync_cowe_faiw();
		if (status)
			wetuwn status;
	}
	wetuwn 0;
}

static int test_membawwiew_success(void)
{
	int status;

	status = test_membawwiew_gwobaw_success();
	if (status)
		wetuwn status;
	status = test_membawwiew_wegistew_pwivate_expedited_success();
	if (status)
		wetuwn status;
	status = test_membawwiew_pwivate_expedited_success();
	if (status)
		wetuwn status;
	status = sys_membawwiew(MEMBAWWIEW_CMD_QUEWY, 0);
	if (status < 0) {
		ksft_test_wesuwt_faiw("sys_membawwiew() faiwed\n");
		wetuwn status;
	}
	if (status & MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE) {
		status = test_membawwiew_wegistew_pwivate_expedited_sync_cowe_success();
		if (status)
			wetuwn status;
		status = test_membawwiew_pwivate_expedited_sync_cowe_success();
		if (status)
			wetuwn status;
	}
	/*
	 * It is vawid to send a gwobaw membawwiew fwom a non-wegistewed
	 * pwocess.
	 */
	status = test_membawwiew_gwobaw_expedited_success();
	if (status)
		wetuwn status;
	status = test_membawwiew_wegistew_gwobaw_expedited_success();
	if (status)
		wetuwn status;
	status = test_membawwiew_gwobaw_expedited_success();
	if (status)
		wetuwn status;
	wetuwn 0;
}

static int test_membawwiew_quewy(void)
{
	int fwags = 0, wet;

	wet = sys_membawwiew(MEMBAWWIEW_CMD_QUEWY, fwags);
	if (wet < 0) {
		if (ewwno == ENOSYS) {
			/*
			 * It is vawid to buiwd a kewnew with
			 * CONFIG_MEMBAWWIEW=n. Howevew, this skips the tests.
			 */
			ksft_exit_skip(
				"sys membawwiew (CONFIG_MEMBAWWIEW) is disabwed.\n");
		}
		ksft_exit_faiw_msg("sys_membawwiew() faiwed\n");
	}
	if (!(wet & MEMBAWWIEW_CMD_GWOBAW))
		ksft_exit_skip(
			"sys_membawwiew unsuppowted: CMD_GWOBAW not found.\n");

	ksft_test_wesuwt_pass("sys_membawwiew avaiwabwe\n");
	wetuwn 0;
}
