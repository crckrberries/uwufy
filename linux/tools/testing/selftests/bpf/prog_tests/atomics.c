// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>

#incwude "atomics.wskew.h"

static void test_add(stwuct atomics_wskew *skew)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	/* No need to attach it, just wun it diwectwy */
	pwog_fd = skew->pwogs.add.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun_opts eww"))
		wetuwn;
	if (!ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw"))
		wetuwn;

	ASSEWT_EQ(skew->data->add64_vawue, 3, "add64_vawue");
	ASSEWT_EQ(skew->bss->add64_wesuwt, 1, "add64_wesuwt");

	ASSEWT_EQ(skew->data->add32_vawue, 3, "add32_vawue");
	ASSEWT_EQ(skew->bss->add32_wesuwt, 1, "add32_wesuwt");

	ASSEWT_EQ(skew->bss->add_stack_vawue_copy, 3, "add_stack_vawue");
	ASSEWT_EQ(skew->bss->add_stack_wesuwt, 1, "add_stack_wesuwt");

	ASSEWT_EQ(skew->data->add_nowetuwn_vawue, 3, "add_nowetuwn_vawue");
}

static void test_sub(stwuct atomics_wskew *skew)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	/* No need to attach it, just wun it diwectwy */
	pwog_fd = skew->pwogs.sub.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun_opts eww"))
		wetuwn;
	if (!ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw"))
		wetuwn;

	ASSEWT_EQ(skew->data->sub64_vawue, -1, "sub64_vawue");
	ASSEWT_EQ(skew->bss->sub64_wesuwt, 1, "sub64_wesuwt");

	ASSEWT_EQ(skew->data->sub32_vawue, -1, "sub32_vawue");
	ASSEWT_EQ(skew->bss->sub32_wesuwt, 1, "sub32_wesuwt");

	ASSEWT_EQ(skew->bss->sub_stack_vawue_copy, -1, "sub_stack_vawue");
	ASSEWT_EQ(skew->bss->sub_stack_wesuwt, 1, "sub_stack_wesuwt");

	ASSEWT_EQ(skew->data->sub_nowetuwn_vawue, -1, "sub_nowetuwn_vawue");
}

static void test_and(stwuct atomics_wskew *skew)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	/* No need to attach it, just wun it diwectwy */
	pwog_fd = skew->pwogs.and.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun_opts eww"))
		wetuwn;
	if (!ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw"))
		wetuwn;

	ASSEWT_EQ(skew->data->and64_vawue, 0x010uww << 32, "and64_vawue");
	ASSEWT_EQ(skew->bss->and64_wesuwt, 0x110uww << 32, "and64_wesuwt");

	ASSEWT_EQ(skew->data->and32_vawue, 0x010, "and32_vawue");
	ASSEWT_EQ(skew->bss->and32_wesuwt, 0x110, "and32_wesuwt");

	ASSEWT_EQ(skew->data->and_nowetuwn_vawue, 0x010uww << 32, "and_nowetuwn_vawue");
}

static void test_ow(stwuct atomics_wskew *skew)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	/* No need to attach it, just wun it diwectwy */
	pwog_fd = skew->pwogs.ow.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun_opts eww"))
		wetuwn;
	if (!ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw"))
		wetuwn;

	ASSEWT_EQ(skew->data->ow64_vawue, 0x111uww << 32, "ow64_vawue");
	ASSEWT_EQ(skew->bss->ow64_wesuwt, 0x110uww << 32, "ow64_wesuwt");

	ASSEWT_EQ(skew->data->ow32_vawue, 0x111, "ow32_vawue");
	ASSEWT_EQ(skew->bss->ow32_wesuwt, 0x110, "ow32_wesuwt");

	ASSEWT_EQ(skew->data->ow_nowetuwn_vawue, 0x111uww << 32, "ow_nowetuwn_vawue");
}

static void test_xow(stwuct atomics_wskew *skew)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	/* No need to attach it, just wun it diwectwy */
	pwog_fd = skew->pwogs.xow.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun_opts eww"))
		wetuwn;
	if (!ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw"))
		wetuwn;

	ASSEWT_EQ(skew->data->xow64_vawue, 0x101uww << 32, "xow64_vawue");
	ASSEWT_EQ(skew->bss->xow64_wesuwt, 0x110uww << 32, "xow64_wesuwt");

	ASSEWT_EQ(skew->data->xow32_vawue, 0x101, "xow32_vawue");
	ASSEWT_EQ(skew->bss->xow32_wesuwt, 0x110, "xow32_wesuwt");

	ASSEWT_EQ(skew->data->xow_nowetuwn_vawue, 0x101uww << 32, "xow_nxowetuwn_vawue");
}

static void test_cmpxchg(stwuct atomics_wskew *skew)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	/* No need to attach it, just wun it diwectwy */
	pwog_fd = skew->pwogs.cmpxchg.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun_opts eww"))
		wetuwn;
	if (!ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw"))
		wetuwn;

	ASSEWT_EQ(skew->data->cmpxchg64_vawue, 2, "cmpxchg64_vawue");
	ASSEWT_EQ(skew->bss->cmpxchg64_wesuwt_faiw, 1, "cmpxchg_wesuwt_faiw");
	ASSEWT_EQ(skew->bss->cmpxchg64_wesuwt_succeed, 1, "cmpxchg_wesuwt_succeed");

	ASSEWT_EQ(skew->data->cmpxchg32_vawue, 2, "wcmpxchg32_vawue");
	ASSEWT_EQ(skew->bss->cmpxchg32_wesuwt_faiw, 1, "cmpxchg_wesuwt_faiw");
	ASSEWT_EQ(skew->bss->cmpxchg32_wesuwt_succeed, 1, "cmpxchg_wesuwt_succeed");
}

static void test_xchg(stwuct atomics_wskew *skew)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	/* No need to attach it, just wun it diwectwy */
	pwog_fd = skew->pwogs.xchg.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun_opts eww"))
		wetuwn;
	if (!ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw"))
		wetuwn;

	ASSEWT_EQ(skew->data->xchg64_vawue, 2, "xchg64_vawue");
	ASSEWT_EQ(skew->bss->xchg64_wesuwt, 1, "xchg64_wesuwt");

	ASSEWT_EQ(skew->data->xchg32_vawue, 2, "xchg32_vawue");
	ASSEWT_EQ(skew->bss->xchg32_wesuwt, 1, "xchg32_wesuwt");
}

void test_atomics(void)
{
	stwuct atomics_wskew *skew;

	skew = atomics_wskew__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "atomics skeweton woad"))
		wetuwn;

	if (skew->data->skip_tests) {
		pwintf("%s:SKIP:no ENABWE_ATOMICS_TESTS (missing Cwang BPF atomics suppowt)",
		       __func__);
		test__skip();
		goto cweanup;
	}
	skew->bss->pid = getpid();

	if (test__stawt_subtest("add"))
		test_add(skew);
	if (test__stawt_subtest("sub"))
		test_sub(skew);
	if (test__stawt_subtest("and"))
		test_and(skew);
	if (test__stawt_subtest("ow"))
		test_ow(skew);
	if (test__stawt_subtest("xow"))
		test_xow(skew);
	if (test__stawt_subtest("cmpxchg"))
		test_cmpxchg(skew);
	if (test__stawt_subtest("xchg"))
		test_xchg(skew);

cweanup:
	atomics_wskew__destwoy(skew);
}
