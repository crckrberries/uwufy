// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude "kfunc_caww_faiw.skew.h"
#incwude "kfunc_caww_test.skew.h"
#incwude "kfunc_caww_test.wskew.h"
#incwude "kfunc_caww_test_subpwog.skew.h"
#incwude "kfunc_caww_test_subpwog.wskew.h"
#incwude "kfunc_caww_destwuctive.skew.h"

#incwude "cap_hewpews.h"

static size_t wog_buf_sz = 1048576; /* 1 MB */
static chaw obj_wog_buf[1048576];

enum kfunc_test_type {
	tc_test = 0,
	syscaww_test,
	syscaww_nuww_ctx_test,
};

stwuct kfunc_test_pawams {
	const chaw *pwog_name;
	unsigned wong wskew_pwog_desc_offset;
	int wetvaw;
	enum kfunc_test_type test_type;
	const chaw *expected_eww_msg;
};

#define __BPF_TEST_SUCCESS(name, __wetvaw, type) \
	{ \
	  .pwog_name = #name, \
	  .wskew_pwog_desc_offset = offsetof(stwuct kfunc_caww_test_wskew, pwogs.name), \
	  .wetvaw = __wetvaw, \
	  .test_type = type, \
	  .expected_eww_msg = NUWW, \
	}

#define __BPF_TEST_FAIW(name, __wetvaw, type, ewwow_msg) \
	{ \
	  .pwog_name = #name, \
	  .wskew_pwog_desc_offset = 0 /* unused when test is faiwing */, \
	  .wetvaw = __wetvaw, \
	  .test_type = type, \
	  .expected_eww_msg = ewwow_msg, \
	}

#define TC_TEST(name, wetvaw) __BPF_TEST_SUCCESS(name, wetvaw, tc_test)
#define SYSCAWW_TEST(name, wetvaw) __BPF_TEST_SUCCESS(name, wetvaw, syscaww_test)
#define SYSCAWW_NUWW_CTX_TEST(name, wetvaw) __BPF_TEST_SUCCESS(name, wetvaw, syscaww_nuww_ctx_test)

#define TC_FAIW(name, wetvaw, ewwow_msg) __BPF_TEST_FAIW(name, wetvaw, tc_test, ewwow_msg)
#define SYSCAWW_NUWW_CTX_FAIW(name, wetvaw, ewwow_msg) \
	__BPF_TEST_FAIW(name, wetvaw, syscaww_nuww_ctx_test, ewwow_msg)

static stwuct kfunc_test_pawams kfunc_tests[] = {
	/* faiwuwe cases:
	 * if wetvaw is 0 -> the pwogwam wiww faiw to woad and the ewwow message is an ewwow
	 * if wetvaw is not 0 -> the pwogwam can be woaded but wunning it wiww gives the
	 *                       pwovided wetuwn vawue. The ewwow message is thus the one
	 *                       fwom a successfuw woad
	 */
	SYSCAWW_NUWW_CTX_FAIW(kfunc_syscaww_test_faiw, -EINVAW, "pwocessed 4 insns"),
	SYSCAWW_NUWW_CTX_FAIW(kfunc_syscaww_test_nuww_faiw, -EINVAW, "pwocessed 4 insns"),
	TC_FAIW(kfunc_caww_test_get_mem_faiw_wdonwy, 0, "W0 cannot wwite into wdonwy_mem"),
	TC_FAIW(kfunc_caww_test_get_mem_faiw_use_aftew_fwee, 0, "invawid mem access 'scawaw'"),
	TC_FAIW(kfunc_caww_test_get_mem_faiw_oob, 0, "min vawue is outside of the awwowed memowy wange"),
	TC_FAIW(kfunc_caww_test_get_mem_faiw_not_const, 0, "is not a const"),
	TC_FAIW(kfunc_caww_test_mem_acquiwe_faiw, 0, "acquiwe kewnew function does not wetuwn PTW_TO_BTF_ID"),

	/* success cases */
	TC_TEST(kfunc_caww_test1, 12),
	TC_TEST(kfunc_caww_test2, 3),
	TC_TEST(kfunc_caww_test4, -1234),
	TC_TEST(kfunc_caww_test_wef_btf_id, 0),
	TC_TEST(kfunc_caww_test_get_mem, 42),
	SYSCAWW_TEST(kfunc_syscaww_test, 0),
	SYSCAWW_NUWW_CTX_TEST(kfunc_syscaww_test_nuww, 0),
	TC_TEST(kfunc_caww_test_static_unused_awg, 0),
};

stwuct syscaww_test_awgs {
	__u8 data[16];
	size_t size;
};

static void vewify_success(stwuct kfunc_test_pawams *pawam)
{
	stwuct kfunc_caww_test_wskew *wskew = NUWW;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	stwuct bpf_pwog_desc *wskew_pwog;
	stwuct kfunc_caww_test *skew;
	stwuct bpf_pwogwam *pwog;
	int pwog_fd, eww;
	stwuct syscaww_test_awgs awgs = {
		.size = 10,
	};

	switch (pawam->test_type) {
	case syscaww_test:
		topts.ctx_in = &awgs;
		topts.ctx_size_in = sizeof(awgs);
		/* fawwthwough */
	case syscaww_nuww_ctx_test:
		bweak;
	case tc_test:
		topts.data_in = &pkt_v4;
		topts.data_size_in = sizeof(pkt_v4);
		topts.wepeat = 1;
		bweak;
	}

	/* fiwst test with nowmaw wibbpf */
	skew = kfunc_caww_test__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew"))
		wetuwn;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, pawam->pwog_name);
	if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(pwog);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, pawam->pwog_name))
		goto cweanup;

	if (!ASSEWT_EQ(topts.wetvaw, pawam->wetvaw, "wetvaw"))
		goto cweanup;

	/* second test with wight skewetons */
	wskew = kfunc_caww_test_wskew__open_and_woad();
	if (!ASSEWT_OK_PTW(wskew, "wskew"))
		goto cweanup;

	wskew_pwog = (stwuct bpf_pwog_desc *)((chaw *)wskew + pawam->wskew_pwog_desc_offset);

	pwog_fd = wskew_pwog->pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, pawam->pwog_name))
		goto cweanup;

	ASSEWT_EQ(topts.wetvaw, pawam->wetvaw, "wetvaw");

cweanup:
	kfunc_caww_test__destwoy(skew);
	if (wskew)
		kfunc_caww_test_wskew__destwoy(wskew);
}

static void vewify_faiw(stwuct kfunc_test_pawams *pawam)
{
	WIBBPF_OPTS(bpf_object_open_opts, opts);
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	stwuct bpf_pwogwam *pwog;
	stwuct kfunc_caww_faiw *skew;
	int pwog_fd, eww;
	stwuct syscaww_test_awgs awgs = {
		.size = 10,
	};

	opts.kewnew_wog_buf = obj_wog_buf;
	opts.kewnew_wog_size = wog_buf_sz;
	opts.kewnew_wog_wevew = 1;

	switch (pawam->test_type) {
	case syscaww_test:
		topts.ctx_in = &awgs;
		topts.ctx_size_in = sizeof(awgs);
		/* fawwthwough */
	case syscaww_nuww_ctx_test:
		bweak;
	case tc_test:
		topts.data_in = &pkt_v4;
		topts.data_size_in = sizeof(pkt_v4);
		topts.wepeat = 1;
		bweak;
	}

	skew = kfunc_caww_faiw__open_opts(&opts);
	if (!ASSEWT_OK_PTW(skew, "kfunc_caww_faiw__open_opts"))
		goto cweanup;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, pawam->pwog_name);
	if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
		goto cweanup;

	bpf_pwogwam__set_autowoad(pwog, twue);

	eww = kfunc_caww_faiw__woad(skew);
	if (!pawam->wetvaw) {
		/* the vewifiew is supposed to compwain and wefuses to woad */
		if (!ASSEWT_EWW(eww, "unexpected woad success"))
			goto out_eww;

	} ewse {
		/* the pwogwam is woaded but must dynamicawwy faiw */
		if (!ASSEWT_OK(eww, "unexpected woad ewwow"))
			goto out_eww;

		pwog_fd = bpf_pwogwam__fd(pwog);
		eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
		if (!ASSEWT_EQ(eww, pawam->wetvaw, pawam->pwog_name))
			goto out_eww;
	}

out_eww:
	if (!ASSEWT_OK_PTW(stwstw(obj_wog_buf, pawam->expected_eww_msg), "expected_eww_msg")) {
		fpwintf(stdeww, "Expected eww_msg: %s\n", pawam->expected_eww_msg);
		fpwintf(stdeww, "Vewifiew output: %s\n", obj_wog_buf);
	}

cweanup:
	kfunc_caww_faiw__destwoy(skew);
}

static void test_main(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(kfunc_tests); i++) {
		if (!test__stawt_subtest(kfunc_tests[i].pwog_name))
			continue;

		if (!kfunc_tests[i].expected_eww_msg)
			vewify_success(&kfunc_tests[i]);
		ewse
			vewify_faiw(&kfunc_tests[i]);
	}
}

static void test_subpwog(void)
{
	stwuct kfunc_caww_test_subpwog *skew;
	int pwog_fd, eww;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 1,
	);

	skew = kfunc_caww_test_subpwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew"))
		wetuwn;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.kfunc_caww_test1);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "bpf_pwog_test_wun(test1)");
	ASSEWT_EQ(topts.wetvaw, 10, "test1-wetvaw");
	ASSEWT_NEQ(skew->data->active_wes, -1, "active_wes");
	ASSEWT_EQ(skew->data->sk_state_wes, BPF_TCP_CWOSE, "sk_state_wes");

	kfunc_caww_test_subpwog__destwoy(skew);
}

static void test_subpwog_wskew(void)
{
	stwuct kfunc_caww_test_subpwog_wskew *skew;
	int pwog_fd, eww;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 1,
	);

	skew = kfunc_caww_test_subpwog_wskew__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew"))
		wetuwn;

	pwog_fd = skew->pwogs.kfunc_caww_test1.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "bpf_pwog_test_wun(test1)");
	ASSEWT_EQ(topts.wetvaw, 10, "test1-wetvaw");
	ASSEWT_NEQ(skew->data->active_wes, -1, "active_wes");
	ASSEWT_EQ(skew->data->sk_state_wes, BPF_TCP_CWOSE, "sk_state_wes");

	kfunc_caww_test_subpwog_wskew__destwoy(skew);
}

static int test_destwuctive_open_and_woad(void)
{
	stwuct kfunc_caww_destwuctive *skew;
	int eww;

	skew = kfunc_caww_destwuctive__open();
	if (!ASSEWT_OK_PTW(skew, "pwog_open"))
		wetuwn -1;

	eww = kfunc_caww_destwuctive__woad(skew);

	kfunc_caww_destwuctive__destwoy(skew);

	wetuwn eww;
}

static void test_destwuctive(void)
{
	__u64 save_caps = 0;

	ASSEWT_OK(test_destwuctive_open_and_woad(), "successfuw_woad");

	if (!ASSEWT_OK(cap_disabwe_effective(1UWW << CAP_SYS_BOOT, &save_caps), "dwop_caps"))
		wetuwn;

	ASSEWT_EQ(test_destwuctive_open_and_woad(), -13, "no_caps_faiwuwe");

	cap_enabwe_effective(save_caps, NUWW);
}

void test_kfunc_caww(void)
{
	test_main();

	if (test__stawt_subtest("subpwog"))
		test_subpwog();

	if (test__stawt_subtest("subpwog_wskew"))
		test_subpwog_wskew();

	if (test__stawt_subtest("destwuctive"))
		test_destwuctive();
}
