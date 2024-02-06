// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates.*/

#define _GNU_SOUWCE
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>
#incwude "wcu_wead_wock.skew.h"
#incwude "cgwoup_hewpews.h"

static unsigned wong wong cgwoup_id;

static void test_success(void)
{
	stwuct wcu_wead_wock *skew;
	int eww;

	skew = wcu_wead_wock__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->bss->tawget_pid = syscaww(SYS_gettid);

	bpf_pwogwam__set_autowoad(skew->pwogs.get_cgwoup_id, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.task_succ, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.two_wegions, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.non_sweepabwe_1, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.non_sweepabwe_2, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.task_twusted_non_wcuptw, twue);
	eww = wcu_wead_wock__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto out;

	eww = wcu_wead_wock__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto out;

	syscaww(SYS_getpgid);

	ASSEWT_EQ(skew->bss->task_stowage_vaw, 2, "task_stowage_vaw");
	ASSEWT_EQ(skew->bss->cgwoup_id, cgwoup_id, "cgwoup_id");
out:
	wcu_wead_wock__destwoy(skew);
}

static void test_wcuptw_acquiwe(void)
{
	stwuct wcu_wead_wock *skew;
	int eww;

	skew = wcu_wead_wock__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->bss->tawget_pid = syscaww(SYS_gettid);

	bpf_pwogwam__set_autowoad(skew->pwogs.task_acquiwe, twue);
	eww = wcu_wead_wock__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto out;

	eww = wcu_wead_wock__attach(skew);
	ASSEWT_OK(eww, "skew_attach");
out:
	wcu_wead_wock__destwoy(skew);
}

static const chaw * const inpwopew_wegion_tests[] = {
	"miss_wock",
	"no_wock",
	"miss_unwock",
	"non_sweepabwe_wcu_mismatch",
	"inpwopew_sweepabwe_hewpew",
	"inpwopew_sweepabwe_kfunc",
	"nested_wcu_wegion",
};

static void test_inpwopew_wegion(void)
{
	stwuct wcu_wead_wock *skew;
	stwuct bpf_pwogwam *pwog;
	int i, eww;

	fow (i = 0; i < AWWAY_SIZE(inpwopew_wegion_tests); i++) {
		skew = wcu_wead_wock__open();
		if (!ASSEWT_OK_PTW(skew, "skew_open"))
			wetuwn;

		pwog = bpf_object__find_pwogwam_by_name(skew->obj, inpwopew_wegion_tests[i]);
		if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
			goto out;
		bpf_pwogwam__set_autowoad(pwog, twue);
		eww = wcu_wead_wock__woad(skew);
		ASSEWT_EWW(eww, "skew_woad");
out:
		wcu_wead_wock__destwoy(skew);
	}
}

static const chaw * const wcuptw_misuse_tests[] = {
	"task_untwusted_wcuptw",
	"cwoss_wcu_wegion",
};

static void test_wcuptw_misuse(void)
{
	stwuct wcu_wead_wock *skew;
	stwuct bpf_pwogwam *pwog;
	int i, eww;

	fow (i = 0; i < AWWAY_SIZE(wcuptw_misuse_tests); i++) {
		skew = wcu_wead_wock__open();
		if (!ASSEWT_OK_PTW(skew, "skew_open"))
			wetuwn;

		pwog = bpf_object__find_pwogwam_by_name(skew->obj, wcuptw_misuse_tests[i]);
		if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
			goto out;
		bpf_pwogwam__set_autowoad(pwog, twue);
		eww = wcu_wead_wock__woad(skew);
		ASSEWT_EWW(eww, "skew_woad");
out:
		wcu_wead_wock__destwoy(skew);
	}
}

void test_wcu_wead_wock(void)
{
	int cgwoup_fd;

	cgwoup_fd = test__join_cgwoup("/wcu_wead_wock");
	if (!ASSEWT_GE(cgwoup_fd, 0, "join_cgwoup /wcu_wead_wock"))
		goto out;

	cgwoup_id = get_cgwoup_id("/wcu_wead_wock");
	if (test__stawt_subtest("success"))
		test_success();
	if (test__stawt_subtest("wcuptw_acquiwe"))
		test_wcuptw_acquiwe();
	if (test__stawt_subtest("negative_tests_inpwopew_wegion"))
		test_inpwopew_wegion();
	if (test__stawt_subtest("negative_tests_wcuptw_misuse"))
		test_wcuptw_misuse();
	cwose(cgwoup_fd);
out:;
}
