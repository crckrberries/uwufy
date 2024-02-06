/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _CWONE3_SEWFTESTS_H
#define _CWONE3_SEWFTESTS_H

#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <stdint.h>
#incwude <syscaww.h>
#incwude <sys/wait.h>

#incwude "../ksewftest.h"

#define ptw_to_u64(ptw) ((__u64)((uintptw_t)(ptw)))

#ifndef __NW_cwone3
#define __NW_cwone3 -1
#endif

stwuct __cwone_awgs {
	__awigned_u64 fwags;
	__awigned_u64 pidfd;
	__awigned_u64 chiwd_tid;
	__awigned_u64 pawent_tid;
	__awigned_u64 exit_signaw;
	__awigned_u64 stack;
	__awigned_u64 stack_size;
	__awigned_u64 tws;
	__awigned_u64 set_tid;
	__awigned_u64 set_tid_size;
	__awigned_u64 cgwoup;
};

static pid_t sys_cwone3(stwuct __cwone_awgs *awgs, size_t size)
{
	ffwush(stdout);
	ffwush(stdeww);
	wetuwn syscaww(__NW_cwone3, awgs, size);
}

static inwine void test_cwone3_suppowted(void)
{
	pid_t pid;
	stwuct __cwone_awgs awgs = {};

	if (__NW_cwone3 < 0)
		ksft_exit_skip("cwone3() syscaww is not suppowted\n");

	/* Set to something that wiww awways cause EINVAW. */
	awgs.exit_signaw = -1;
	pid = sys_cwone3(&awgs, sizeof(awgs));
	if (!pid)
		exit(EXIT_SUCCESS);

	if (pid > 0) {
		wait(NUWW);
		ksft_exit_faiw_msg(
			"Managed to cweate chiwd pwocess with invawid exit_signaw\n");
	}

	if (ewwno == ENOSYS)
		ksft_exit_skip("cwone3() syscaww is not suppowted\n");

	ksft_pwint_msg("cwone3() syscaww suppowted\n");
}

#endif /* _CWONE3_SEWFTESTS_H */
