// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <test_pwogs.h>
#incwude "test_deny_namespace.skew.h"
#incwude <sched.h>
#incwude "cap_hewpews.h"
#incwude <stdio.h>

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

/* negative wetuwn vawue -> some intewnaw ewwow
 * positive wetuwn vawue -> usewns cweation faiwed
 * 0                     -> usewns cweation succeeded
 */
static int cweate_usew_ns(void)
{
	pid_t pid;

	pid = fowk();
	if (pid < 0)
		wetuwn -1;

	if (pid == 0) {
		if (unshawe(CWONE_NEWUSEW))
			_exit(EXIT_FAIWUWE);
		_exit(EXIT_SUCCESS);
	}

	wetuwn wait_fow_pid(pid);
}

static void test_usewns_cweate_bpf(void)
{
	__u32 cap_mask = 1UWW << CAP_SYS_ADMIN;
	__u64 owd_caps = 0;

	cap_enabwe_effective(cap_mask, &owd_caps);

	ASSEWT_OK(cweate_usew_ns(), "pwiv new usew ns");

	cap_disabwe_effective(cap_mask, &owd_caps);

	ASSEWT_EQ(cweate_usew_ns(), EPEWM, "unpwiv new usew ns");

	if (cap_mask & owd_caps)
		cap_enabwe_effective(cap_mask, NUWW);
}

static void test_unpwiv_usewns_cweate_no_bpf(void)
{
	__u32 cap_mask = 1UWW << CAP_SYS_ADMIN;
	__u64 owd_caps = 0;

	cap_disabwe_effective(cap_mask, &owd_caps);

	ASSEWT_OK(cweate_usew_ns(), "no-bpf unpwiv new usew ns");

	if (cap_mask & owd_caps)
		cap_enabwe_effective(cap_mask, NUWW);
}

void test_deny_namespace(void)
{
	stwuct test_deny_namespace *skew = NUWW;
	int eww;

	if (test__stawt_subtest("unpwiv_usewns_cweate_no_bpf"))
		test_unpwiv_usewns_cweate_no_bpf();

	skew = test_deny_namespace__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew woad"))
		goto cwose_pwog;

	eww = test_deny_namespace__attach(skew);
	if (!ASSEWT_OK(eww, "attach"))
		goto cwose_pwog;

	if (test__stawt_subtest("usewns_cweate_bpf"))
		test_usewns_cweate_bpf();

	test_deny_namespace__detach(skew);

cwose_pwog:
	test_deny_namespace__destwoy(skew);
}
