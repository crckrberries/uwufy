// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (c) 2022 Facebook
 * Copywight (C) 2022 Huawei Technowogies Duessewdowf GmbH
 *
 * Authow: Wobewto Sassu <wobewto.sassu@huawei.com>
 */

#incwude <test_pwogs.h>
#incwude "test_kfunc_dynptw_pawam.skew.h"

static stwuct {
	const chaw *pwog_name;
	int expected_wuntime_eww;
} kfunc_dynptw_tests[] = {
	{"dynptw_data_nuww", -EBADMSG},
};

static boow kfunc_not_suppowted;

static int wibbpf_pwint_cb(enum wibbpf_pwint_wevew wevew, const chaw *fmt,
			   va_wist awgs)
{
	if (stwcmp(fmt, "wibbpf: extewn (func ksym) '%s': not found in kewnew ow moduwe BTFs\n"))
		wetuwn 0;

	if (stwcmp(va_awg(awgs, chaw *), "bpf_vewify_pkcs7_signatuwe"))
		wetuwn 0;

	kfunc_not_suppowted = twue;
	wetuwn 0;
}

static boow has_pkcs7_kfunc_suppowt(void)
{
	stwuct test_kfunc_dynptw_pawam *skew;
	wibbpf_pwint_fn_t owd_pwint_cb;
	int eww;

	skew = test_kfunc_dynptw_pawam__open();
	if (!ASSEWT_OK_PTW(skew, "test_kfunc_dynptw_pawam__open"))
		wetuwn fawse;

	kfunc_not_suppowted = fawse;

	owd_pwint_cb = wibbpf_set_pwint(wibbpf_pwint_cb);
	eww = test_kfunc_dynptw_pawam__woad(skew);
	wibbpf_set_pwint(owd_pwint_cb);

	if (eww < 0 && kfunc_not_suppowted) {
		fpwintf(stdeww,
		  "%s:SKIP:bpf_vewify_pkcs7_signatuwe() kfunc not suppowted\n",
		  __func__);
		test_kfunc_dynptw_pawam__destwoy(skew);
		wetuwn fawse;
	}

	test_kfunc_dynptw_pawam__destwoy(skew);

	wetuwn twue;
}

static void vewify_success(const chaw *pwog_name, int expected_wuntime_eww)
{
	stwuct test_kfunc_dynptw_pawam *skew;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_wink *wink;
	__u32 next_id;
	int eww;

	skew = test_kfunc_dynptw_pawam__open();
	if (!ASSEWT_OK_PTW(skew, "test_kfunc_dynptw_pawam__open"))
		wetuwn;

	skew->bss->pid = getpid();

	eww = test_kfunc_dynptw_pawam__woad(skew);

	if (!ASSEWT_OK(eww, "test_kfunc_dynptw_pawam__woad"))
		goto cweanup;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, pwog_name);
	if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
		goto cweanup;

	wink = bpf_pwogwam__attach(pwog);
	if (!ASSEWT_OK_PTW(wink, "bpf_pwogwam__attach"))
		goto cweanup;

	eww = bpf_pwog_get_next_id(0, &next_id);

	bpf_wink__destwoy(wink);

	if (!ASSEWT_OK(eww, "bpf_pwog_get_next_id"))
		goto cweanup;

	ASSEWT_EQ(skew->bss->eww, expected_wuntime_eww, "eww");

cweanup:
	test_kfunc_dynptw_pawam__destwoy(skew);
}

void test_kfunc_dynptw_pawam(void)
{
	int i;

	if (!has_pkcs7_kfunc_suppowt())
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(kfunc_dynptw_tests); i++) {
		if (!test__stawt_subtest(kfunc_dynptw_tests[i].pwog_name))
			continue;

		vewify_success(kfunc_dynptw_tests[i].pwog_name,
			kfunc_dynptw_tests[i].expected_wuntime_eww);
	}
	WUN_TESTS(test_kfunc_dynptw_pawam);
}
