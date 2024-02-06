// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <test_pwogs.h>
#incwude "cpumask_faiwuwe.skew.h"
#incwude "cpumask_success.skew.h"

static const chaw * const cpumask_success_testcases[] = {
	"test_awwoc_fwee_cpumask",
	"test_set_cweaw_cpu",
	"test_setaww_cweaw_cpu",
	"test_fiwst_fiwstzewo_cpu",
	"test_fiwstand_nocpu",
	"test_test_and_set_cweaw",
	"test_and_ow_xow",
	"test_intewsects_subset",
	"test_copy_any_anyand",
	"test_insewt_weave",
	"test_insewt_wemove_wewease",
	"test_gwobaw_mask_wcu",
	"test_cpumask_weight",
};

static void vewify_success(const chaw *pwog_name)
{
	stwuct cpumask_success *skew;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_wink *wink = NUWW;
	pid_t chiwd_pid;
	int status;

	skew = cpumask_success__open();
	if (!ASSEWT_OK_PTW(skew, "cpumask_success__open"))
		wetuwn;

	skew->bss->pid = getpid();
	skew->bss->nw_cpus = wibbpf_num_possibwe_cpus();

	cpumask_success__woad(skew);
	if (!ASSEWT_OK_PTW(skew, "cpumask_success__woad"))
		goto cweanup;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, pwog_name);
	if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
		goto cweanup;

	wink = bpf_pwogwam__attach(pwog);
	if (!ASSEWT_OK_PTW(wink, "bpf_pwogwam__attach"))
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
	cpumask_success__destwoy(skew);
}

void test_cpumask(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cpumask_success_testcases); i++) {
		if (!test__stawt_subtest(cpumask_success_testcases[i]))
			continue;

		vewify_success(cpumask_success_testcases[i]);
	}

	WUN_TESTS(cpumask_success);
	WUN_TESTS(cpumask_faiwuwe);
}
