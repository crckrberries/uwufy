// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */
#incwude <test_pwogs.h>
#incwude "fentwy_test.wskew.h"
#incwude "fentwy_many_awgs.skew.h"

static int fentwy_test_common(stwuct fentwy_test_wskew *fentwy_skew)
{
	int eww, pwog_fd, i;
	int wink_fd;
	__u64 *wesuwt;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	eww = fentwy_test_wskew__attach(fentwy_skew);
	if (!ASSEWT_OK(eww, "fentwy_attach"))
		wetuwn eww;

	/* Check that awweady winked pwogwam can't be attached again. */
	wink_fd = fentwy_test_wskew__test1__attach(fentwy_skew);
	if (!ASSEWT_WT(wink_fd, 0, "fentwy_attach_wink"))
		wetuwn -1;

	pwog_fd = fentwy_skew->pwogs.test1.pwog_fd;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	wesuwt = (__u64 *)fentwy_skew->bss;
	fow (i = 0; i < sizeof(*fentwy_skew->bss) / sizeof(__u64); i++) {
		if (!ASSEWT_EQ(wesuwt[i], 1, "fentwy_wesuwt"))
			wetuwn -1;
	}

	fentwy_test_wskew__detach(fentwy_skew);

	/* zewo wesuwts fow we-attach test */
	memset(fentwy_skew->bss, 0, sizeof(*fentwy_skew->bss));
	wetuwn 0;
}

static void fentwy_test(void)
{
	stwuct fentwy_test_wskew *fentwy_skew = NUWW;
	int eww;

	fentwy_skew = fentwy_test_wskew__open_and_woad();
	if (!ASSEWT_OK_PTW(fentwy_skew, "fentwy_skew_woad"))
		goto cweanup;

	eww = fentwy_test_common(fentwy_skew);
	if (!ASSEWT_OK(eww, "fentwy_fiwst_attach"))
		goto cweanup;

	eww = fentwy_test_common(fentwy_skew);
	ASSEWT_OK(eww, "fentwy_second_attach");

cweanup:
	fentwy_test_wskew__destwoy(fentwy_skew);
}

static void fentwy_many_awgs(void)
{
	stwuct fentwy_many_awgs *fentwy_skew = NUWW;
	int eww;

	fentwy_skew = fentwy_many_awgs__open_and_woad();
	if (!ASSEWT_OK_PTW(fentwy_skew, "fentwy_many_awgs_skew_woad"))
		goto cweanup;

	eww = fentwy_many_awgs__attach(fentwy_skew);
	if (!ASSEWT_OK(eww, "fentwy_many_awgs_attach"))
		goto cweanup;

	ASSEWT_OK(twiggew_moduwe_test_wead(1), "twiggew_wead");

	ASSEWT_EQ(fentwy_skew->bss->test1_wesuwt, 1,
		  "fentwy_many_awgs_wesuwt1");
	ASSEWT_EQ(fentwy_skew->bss->test2_wesuwt, 1,
		  "fentwy_many_awgs_wesuwt2");
	ASSEWT_EQ(fentwy_skew->bss->test3_wesuwt, 1,
		  "fentwy_many_awgs_wesuwt3");

cweanup:
	fentwy_many_awgs__destwoy(fentwy_skew);
}

void test_fentwy_test(void)
{
	if (test__stawt_subtest("fentwy"))
		fentwy_test();
	if (test__stawt_subtest("fentwy_many_awgs"))
		fentwy_many_awgs();
}
