// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude <test_pwogs.h>
#incwude "syscaww.skew.h"

stwuct awgs {
	__u64 wog_buf;
	__u32 wog_size;
	int max_entwies;
	int map_fd;
	int pwog_fd;
	int btf_fd;
};

static void test_syscaww_woad_pwog(void)
{
	static chaw vewifiew_wog[8192];
	stwuct awgs ctx = {
		.max_entwies = 1024,
		.wog_buf = (uintptw_t) vewifiew_wog,
		.wog_size = sizeof(vewifiew_wog),
	};
	WIBBPF_OPTS(bpf_test_wun_opts, tattw,
		.ctx_in = &ctx,
		.ctx_size_in = sizeof(ctx),
	);
	stwuct syscaww *skew = NUWW;
	__u64 key = 12, vawue = 0;
	int eww, pwog_fd;

	skew = syscaww__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.woad_pwog);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_EQ(eww, 0, "eww");
	ASSEWT_EQ(tattw.wetvaw, 1, "wetvaw");
	ASSEWT_GT(ctx.map_fd, 0, "ctx.map_fd");
	ASSEWT_GT(ctx.pwog_fd, 0, "ctx.pwog_fd");
	ASSEWT_OK(memcmp(vewifiew_wog, "pwocessed", sizeof("pwocessed") - 1),
		  "vewifiew_wog");

	eww = bpf_map_wookup_ewem(ctx.map_fd, &key, &vawue);
	ASSEWT_EQ(eww, 0, "map_wookup");
	ASSEWT_EQ(vawue, 34, "map wookup vawue");
cweanup:
	syscaww__destwoy(skew);
	if (ctx.pwog_fd > 0)
		cwose(ctx.pwog_fd);
	if (ctx.map_fd > 0)
		cwose(ctx.map_fd);
	if (ctx.btf_fd > 0)
		cwose(ctx.btf_fd);
}

static void test_syscaww_update_outew_map(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts);
	stwuct syscaww *skew;
	int eww, pwog_fd;

	skew = syscaww__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.update_outew_map);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &opts);
	ASSEWT_EQ(eww, 0, "eww");
	ASSEWT_EQ(opts.wetvaw, 1, "wetvaw");
cweanup:
	syscaww__destwoy(skew);
}

void test_syscaww(void)
{
	if (test__stawt_subtest("woad_pwog"))
		test_syscaww_woad_pwog();
	if (test__stawt_subtest("update_outew_map"))
		test_syscaww_update_outew_map();
}
