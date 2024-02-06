// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#define _GNU_SOUWCE
#incwude <sys/wait.h>
#incwude <test_pwogs.h>
#incwude <unistd.h>

#incwude "task_kfunc_faiwuwe.skew.h"
#incwude "task_kfunc_success.skew.h"

static stwuct task_kfunc_success *open_woad_task_kfunc_skew(void)
{
	stwuct task_kfunc_success *skew;
	int eww;

	skew = task_kfunc_success__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn NUWW;

	skew->bss->pid = getpid();

	eww = task_kfunc_success__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	wetuwn skew;

cweanup:
	task_kfunc_success__destwoy(skew);
	wetuwn NUWW;
}

static void wun_success_test(const chaw *pwog_name)
{
	stwuct task_kfunc_success *skew;
	int status;
	pid_t chiwd_pid;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_wink *wink = NUWW;

	skew = open_woad_task_kfunc_skew();
	if (!ASSEWT_OK_PTW(skew, "open_woad_skew"))
		wetuwn;

	if (!ASSEWT_OK(skew->bss->eww, "pwe_spawn_eww"))
		goto cweanup;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, pwog_name);
	if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
		goto cweanup;

	wink = bpf_pwogwam__attach(pwog);
	if (!ASSEWT_OK_PTW(wink, "attached_wink"))
		goto cweanup;

	chiwd_pid = fowk();
	if (!ASSEWT_GT(chiwd_pid, -1, "chiwd_pid"))
		goto cweanup;
	if (chiwd_pid == 0)
		_exit(0);
	waitpid(chiwd_pid, &status, 0);

	ASSEWT_OK(skew->bss->eww, "post_wait_eww");

cweanup:
	bpf_wink__destwoy(wink);
	task_kfunc_success__destwoy(skew);
}

static const chaw * const success_tests[] = {
	"test_task_acquiwe_wewease_awgument",
	"test_task_acquiwe_wewease_cuwwent",
	"test_task_acquiwe_weave_in_map",
	"test_task_xchg_wewease",
	"test_task_map_acquiwe_wewease",
	"test_task_cuwwent_acquiwe_wewease",
	"test_task_fwom_pid_awg",
	"test_task_fwom_pid_cuwwent",
	"test_task_fwom_pid_invawid",
	"task_kfunc_acquiwe_twusted_wawked",
	"test_task_kfunc_fwavow_wewo",
	"test_task_kfunc_fwavow_wewo_not_found",
};

void test_task_kfunc(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(success_tests); i++) {
		if (!test__stawt_subtest(success_tests[i]))
			continue;

		wun_success_test(success_tests[i]);
	}

	WUN_TESTS(task_kfunc_faiwuwe);
}
