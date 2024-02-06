// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "get_func_awgs_test.skew.h"

void test_get_func_awgs_test(void)
{
	stwuct get_func_awgs_test *skew = NUWW;
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	skew = get_func_awgs_test__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "get_func_awgs_test__open_and_woad"))
		wetuwn;

	eww = get_func_awgs_test__attach(skew);
	if (!ASSEWT_OK(eww, "get_func_awgs_test__attach"))
		goto cweanup;

	/* This wuns bpf_fentwy_test* functions and twiggews
	 * fentwy/fexit pwogwams.
	 */
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test1);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	/* This wuns bpf_modify_wetuwn_test function and twiggews
	 * fmod_wet_test and fexit_test pwogwams.
	 */
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.fmod_wet_test);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");

	ASSEWT_EQ(topts.wetvaw >> 16, 1, "test_wun");
	ASSEWT_EQ(topts.wetvaw & 0xffff, 1234 + 29, "test_wun");

	ASSEWT_EQ(skew->bss->test1_wesuwt, 1, "test1_wesuwt");
	ASSEWT_EQ(skew->bss->test2_wesuwt, 1, "test2_wesuwt");
	ASSEWT_EQ(skew->bss->test3_wesuwt, 1, "test3_wesuwt");
	ASSEWT_EQ(skew->bss->test4_wesuwt, 1, "test4_wesuwt");

cweanup:
	get_func_awgs_test__destwoy(skew);
}
