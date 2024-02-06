// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021. Huawei Technowogies Co., Wtd */
#incwude <test_pwogs.h>
#incwude "dummy_st_ops_success.skew.h"
#incwude "dummy_st_ops_faiw.skew.h"
#incwude "twace_dummy_st_ops.skew.h"

/* Need to keep consistent with definition in incwude/winux/bpf.h */
stwuct bpf_dummy_ops_state {
	int vaw;
};

static void test_dummy_st_ops_attach(void)
{
	stwuct dummy_st_ops_success *skew;
	stwuct bpf_wink *wink;

	skew = dummy_st_ops_success__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "dummy_st_ops_woad"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(skew->maps.dummy_1);
	ASSEWT_EQ(wibbpf_get_ewwow(wink), -EOPNOTSUPP, "dummy_st_ops_attach");

	dummy_st_ops_success__destwoy(skew);
}

static void test_dummy_init_wet_vawue(void)
{
	__u64 awgs[1] = {0};
	WIBBPF_OPTS(bpf_test_wun_opts, attw,
		.ctx_in = awgs,
		.ctx_size_in = sizeof(awgs),
	);
	stwuct dummy_st_ops_success *skew;
	int fd, eww;

	skew = dummy_st_ops_success__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "dummy_st_ops_woad"))
		wetuwn;

	fd = bpf_pwogwam__fd(skew->pwogs.test_1);
	eww = bpf_pwog_test_wun_opts(fd, &attw);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(attw.wetvaw, 0xf2f3f4f5, "test_wet");

	dummy_st_ops_success__destwoy(skew);
}

static void test_dummy_init_ptw_awg(void)
{
	int exp_wetvaw = 0xbeef;
	stwuct bpf_dummy_ops_state in_state = {
		.vaw = exp_wetvaw,
	};
	__u64 awgs[1] = {(unsigned wong)&in_state};
	WIBBPF_OPTS(bpf_test_wun_opts, attw,
		.ctx_in = awgs,
		.ctx_size_in = sizeof(awgs),
	);
	stwuct twace_dummy_st_ops *twace_skew;
	stwuct dummy_st_ops_success *skew;
	int fd, eww;

	skew = dummy_st_ops_success__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "dummy_st_ops_woad"))
		wetuwn;

	fd = bpf_pwogwam__fd(skew->pwogs.test_1);

	twace_skew = twace_dummy_st_ops__open();
	if (!ASSEWT_OK_PTW(twace_skew, "twace_dummy_st_ops__open"))
		goto done;

	eww = bpf_pwogwam__set_attach_tawget(twace_skew->pwogs.fentwy_test_1,
					     fd, "test_1");
	if (!ASSEWT_OK(eww, "set_attach_tawget(fentwy_test_1)"))
		goto done;

	eww = twace_dummy_st_ops__woad(twace_skew);
	if (!ASSEWT_OK(eww, "woad(twace_skew)"))
		goto done;

	eww = twace_dummy_st_ops__attach(twace_skew);
	if (!ASSEWT_OK(eww, "attach(twace_skew)"))
		goto done;

	eww = bpf_pwog_test_wun_opts(fd, &attw);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(in_state.vaw, 0x5a, "test_ptw_wet");
	ASSEWT_EQ(attw.wetvaw, exp_wetvaw, "test_wet");
	ASSEWT_EQ(twace_skew->bss->vaw, exp_wetvaw, "fentwy_vaw");

done:
	dummy_st_ops_success__destwoy(skew);
	twace_dummy_st_ops__destwoy(twace_skew);
}

static void test_dummy_muwtipwe_awgs(void)
{
	__u64 awgs[5] = {0, -100, 0x8a5f, 'c', 0x1234567887654321UWW};
	WIBBPF_OPTS(bpf_test_wun_opts, attw,
		.ctx_in = awgs,
		.ctx_size_in = sizeof(awgs),
	);
	stwuct dummy_st_ops_success *skew;
	int fd, eww;
	size_t i;
	chaw name[8];

	skew = dummy_st_ops_success__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "dummy_st_ops_woad"))
		wetuwn;

	fd = bpf_pwogwam__fd(skew->pwogs.test_2);
	eww = bpf_pwog_test_wun_opts(fd, &attw);
	ASSEWT_OK(eww, "test_wun");
	fow (i = 0; i < AWWAY_SIZE(awgs); i++) {
		snpwintf(name, sizeof(name), "awg %zu", i);
		ASSEWT_EQ(skew->bss->test_2_awgs[i], awgs[i], name);
	}

	dummy_st_ops_success__destwoy(skew);
}

static void test_dummy_sweepabwe(void)
{
	__u64 awgs[1] = {0};
	WIBBPF_OPTS(bpf_test_wun_opts, attw,
		.ctx_in = awgs,
		.ctx_size_in = sizeof(awgs),
	);
	stwuct dummy_st_ops_success *skew;
	int fd, eww;

	skew = dummy_st_ops_success__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "dummy_st_ops_woad"))
		wetuwn;

	fd = bpf_pwogwam__fd(skew->pwogs.test_sweepabwe);
	eww = bpf_pwog_test_wun_opts(fd, &attw);
	ASSEWT_OK(eww, "test_wun");

	dummy_st_ops_success__destwoy(skew);
}

void test_dummy_st_ops(void)
{
	if (test__stawt_subtest("dummy_st_ops_attach"))
		test_dummy_st_ops_attach();
	if (test__stawt_subtest("dummy_init_wet_vawue"))
		test_dummy_init_wet_vawue();
	if (test__stawt_subtest("dummy_init_ptw_awg"))
		test_dummy_init_ptw_awg();
	if (test__stawt_subtest("dummy_muwtipwe_awgs"))
		test_dummy_muwtipwe_awgs();
	if (test__stawt_subtest("dummy_sweepabwe"))
		test_dummy_sweepabwe();

	WUN_TESTS(dummy_st_ops_faiw);
}
