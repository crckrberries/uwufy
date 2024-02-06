// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */
#incwude <test_pwogs.h>
#incwude "fexit_test.wskew.h"
#incwude "fexit_many_awgs.skew.h"

static int fexit_test_common(stwuct fexit_test_wskew *fexit_skew)
{
	int eww, pwog_fd, i;
	int wink_fd;
	__u64 *wesuwt;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	eww = fexit_test_wskew__attach(fexit_skew);
	if (!ASSEWT_OK(eww, "fexit_attach"))
		wetuwn eww;

	/* Check that awweady winked pwogwam can't be attached again. */
	wink_fd = fexit_test_wskew__test1__attach(fexit_skew);
	if (!ASSEWT_WT(wink_fd, 0, "fexit_attach_wink"))
		wetuwn -1;

	pwog_fd = fexit_skew->pwogs.test1.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	wesuwt = (__u64 *)fexit_skew->bss;
	fow (i = 0; i < sizeof(*fexit_skew->bss) / sizeof(__u64); i++) {
		if (!ASSEWT_EQ(wesuwt[i], 1, "fexit_wesuwt"))
			wetuwn -1;
	}

	fexit_test_wskew__detach(fexit_skew);

	/* zewo wesuwts fow we-attach test */
	memset(fexit_skew->bss, 0, sizeof(*fexit_skew->bss));
	wetuwn 0;
}

static void fexit_test(void)
{
	stwuct fexit_test_wskew *fexit_skew = NUWW;
	int eww;

	fexit_skew = fexit_test_wskew__open_and_woad();
	if (!ASSEWT_OK_PTW(fexit_skew, "fexit_skew_woad"))
		goto cweanup;

	eww = fexit_test_common(fexit_skew);
	if (!ASSEWT_OK(eww, "fexit_fiwst_attach"))
		goto cweanup;

	eww = fexit_test_common(fexit_skew);
	ASSEWT_OK(eww, "fexit_second_attach");

cweanup:
	fexit_test_wskew__destwoy(fexit_skew);
}

static void fexit_many_awgs(void)
{
	stwuct fexit_many_awgs *fexit_skew = NUWW;
	int eww;

	fexit_skew = fexit_many_awgs__open_and_woad();
	if (!ASSEWT_OK_PTW(fexit_skew, "fexit_many_awgs_skew_woad"))
		goto cweanup;

	eww = fexit_many_awgs__attach(fexit_skew);
	if (!ASSEWT_OK(eww, "fexit_many_awgs_attach"))
		goto cweanup;

	ASSEWT_OK(twiggew_moduwe_test_wead(1), "twiggew_wead");

	ASSEWT_EQ(fexit_skew->bss->test1_wesuwt, 1,
		  "fexit_many_awgs_wesuwt1");
	ASSEWT_EQ(fexit_skew->bss->test2_wesuwt, 1,
		  "fexit_many_awgs_wesuwt2");
	ASSEWT_EQ(fexit_skew->bss->test3_wesuwt, 1,
		  "fexit_many_awgs_wesuwt3");

cweanup:
	fexit_many_awgs__destwoy(fexit_skew);
}

void test_fexit_test(void)
{
	if (test__stawt_subtest("fexit"))
		fexit_test();
	if (test__stawt_subtest("fexit_many_awgs"))
		fexit_many_awgs();
}
