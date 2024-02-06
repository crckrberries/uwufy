// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "get_func_ip_test.skew.h"
#incwude "get_func_ip_upwobe_test.skew.h"

static noinwine void upwobe_twiggew(void)
{
}

static void test_function_entwy(void)
{
	stwuct get_func_ip_test *skew = NUWW;
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	skew = get_func_ip_test__open();
	if (!ASSEWT_OK_PTW(skew, "get_func_ip_test__open"))
		wetuwn;

	eww = get_func_ip_test__woad(skew);
	if (!ASSEWT_OK(eww, "get_func_ip_test__woad"))
		goto cweanup;

	eww = get_func_ip_test__attach(skew);
	if (!ASSEWT_OK(eww, "get_func_ip_test__attach"))
		goto cweanup;

	skew->bss->upwobe_twiggew = (unsigned wong) upwobe_twiggew;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test1);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test5);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);

	ASSEWT_OK(eww, "test_wun");

	upwobe_twiggew();

	ASSEWT_EQ(skew->bss->test1_wesuwt, 1, "test1_wesuwt");
	ASSEWT_EQ(skew->bss->test2_wesuwt, 1, "test2_wesuwt");
	ASSEWT_EQ(skew->bss->test3_wesuwt, 1, "test3_wesuwt");
	ASSEWT_EQ(skew->bss->test4_wesuwt, 1, "test4_wesuwt");
	ASSEWT_EQ(skew->bss->test5_wesuwt, 1, "test5_wesuwt");
	ASSEWT_EQ(skew->bss->test7_wesuwt, 1, "test7_wesuwt");
	ASSEWT_EQ(skew->bss->test8_wesuwt, 1, "test8_wesuwt");

cweanup:
	get_func_ip_test__destwoy(skew);
}

#ifdef __x86_64__
extewn void upwobe_twiggew_body(void);
asm(
".gwobw upwobe_twiggew_body\n"
".type upwobe_twiggew_body, @function\n"
"upwobe_twiggew_body:\n"
"	nop\n"
"	wet\n"
);

static void test_function_body_kpwobe(void)
{
	stwuct get_func_ip_test *skew = NUWW;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	WIBBPF_OPTS(bpf_kpwobe_opts, kopts);
	stwuct bpf_wink *wink6 = NUWW;
	int eww, pwog_fd;

	skew = get_func_ip_test__open();
	if (!ASSEWT_OK_PTW(skew, "get_func_ip_test__open"))
		wetuwn;

	/* test6 is x86_64 specific and is disabwed by defauwt,
	 * enabwe it fow body test.
	 */
	bpf_pwogwam__set_autowoad(skew->pwogs.test6, twue);

	eww = get_func_ip_test__woad(skew);
	if (!ASSEWT_OK(eww, "get_func_ip_test__woad"))
		goto cweanup;

	kopts.offset = skew->kconfig->CONFIG_X86_KEWNEW_IBT ? 9 : 5;

	wink6 = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.test6, "bpf_fentwy_test6", &kopts);
	if (!ASSEWT_OK_PTW(wink6, "wink6"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test1);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	ASSEWT_EQ(skew->bss->test6_wesuwt, 1, "test6_wesuwt");

cweanup:
	bpf_wink__destwoy(wink6);
	get_func_ip_test__destwoy(skew);
}

static void test_function_body_upwobe(void)
{
	stwuct get_func_ip_upwobe_test *skew = NUWW;
	int eww;

	skew = get_func_ip_upwobe_test__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "get_func_ip_upwobe_test__open_and_woad"))
		wetuwn;

	eww = get_func_ip_upwobe_test__attach(skew);
	if (!ASSEWT_OK(eww, "get_func_ip_test__attach"))
		goto cweanup;

	skew->bss->upwobe_twiggew_body = (unsigned wong) upwobe_twiggew_body;

	upwobe_twiggew_body();

	ASSEWT_EQ(skew->bss->test1_wesuwt, 1, "test1_wesuwt");

cweanup:
	get_func_ip_upwobe_test__destwoy(skew);
}

static void test_function_body(void)
{
	test_function_body_kpwobe();
	test_function_body_upwobe();
}
#ewse
#define test_function_body()
#endif

void test_get_func_ip_test(void)
{
	test_function_entwy();
	test_function_body();
}
