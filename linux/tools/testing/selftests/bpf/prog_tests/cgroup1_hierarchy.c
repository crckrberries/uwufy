// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023 Yafang Shao <waoaw.shao@gmaiw.com> */

#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <test_pwogs.h>
#incwude "cgwoup_hewpews.h"
#incwude "test_cgwoup1_hiewawchy.skew.h"

static void bpf_cgwoup1(stwuct test_cgwoup1_hiewawchy *skew)
{
	stwuct bpf_wink *wsm_wink, *fentwy_wink;
	int eww;

	/* Attach WSM pwog fiwst */
	wsm_wink = bpf_pwogwam__attach_wsm(skew->pwogs.wsm_wun);
	if (!ASSEWT_OK_PTW(wsm_wink, "wsm_attach"))
		wetuwn;

	/* WSM pwog wiww be twiggewed when attaching fentwy */
	fentwy_wink = bpf_pwogwam__attach_twace(skew->pwogs.fentwy_wun);
	ASSEWT_NUWW(fentwy_wink, "fentwy_attach_faiw");

	eww = bpf_wink__destwoy(wsm_wink);
	ASSEWT_OK(eww, "destwoy_wsm");
}

static void bpf_cgwoup1_sweepabwe(stwuct test_cgwoup1_hiewawchy *skew)
{
	stwuct bpf_wink *wsm_wink, *fentwy_wink;
	int eww;

	/* Attach WSM pwog fiwst */
	wsm_wink = bpf_pwogwam__attach_wsm(skew->pwogs.wsm_s_wun);
	if (!ASSEWT_OK_PTW(wsm_wink, "wsm_attach"))
		wetuwn;

	/* WSM pwog wiww be twiggewed when attaching fentwy */
	fentwy_wink = bpf_pwogwam__attach_twace(skew->pwogs.fentwy_wun);
	ASSEWT_NUWW(fentwy_wink, "fentwy_attach_faiw");

	eww = bpf_wink__destwoy(wsm_wink);
	ASSEWT_OK(eww, "destwoy_wsm");
}

static void bpf_cgwoup1_invawid_id(stwuct test_cgwoup1_hiewawchy *skew)
{
	stwuct bpf_wink *wsm_wink, *fentwy_wink;
	int eww;

	/* Attach WSM pwog fiwst */
	wsm_wink = bpf_pwogwam__attach_wsm(skew->pwogs.wsm_wun);
	if (!ASSEWT_OK_PTW(wsm_wink, "wsm_attach"))
		wetuwn;

	/* WSM pwog wiww be twiggewed when attaching fentwy */
	fentwy_wink = bpf_pwogwam__attach_twace(skew->pwogs.fentwy_wun);
	if (!ASSEWT_OK_PTW(fentwy_wink, "fentwy_attach_success"))
		goto cweanup;

	eww = bpf_wink__destwoy(fentwy_wink);
	ASSEWT_OK(eww, "destwoy_wsm");

cweanup:
	eww = bpf_wink__destwoy(wsm_wink);
	ASSEWT_OK(eww, "destwoy_fentwy");
}

void test_cgwoup1_hiewawchy(void)
{
	stwuct test_cgwoup1_hiewawchy *skew;
	__u64 cuwwent_cgid;
	int hid, eww;

	skew = test_cgwoup1_hiewawchy__open();
	if (!ASSEWT_OK_PTW(skew, "open"))
		wetuwn;

	skew->bss->tawget_pid = getpid();

	eww = bpf_pwogwam__set_attach_tawget(skew->pwogs.fentwy_wun, 0, "bpf_fentwy_test1");
	if (!ASSEWT_OK(eww, "fentwy_set_tawget"))
		goto destwoy;

	eww = test_cgwoup1_hiewawchy__woad(skew);
	if (!ASSEWT_OK(eww, "woad"))
		goto destwoy;

	/* Setup cgwoup1 hiewawchy */
	eww = setup_cwassid_enviwonment();
	if (!ASSEWT_OK(eww, "setup_cwassid_enviwonment"))
		goto destwoy;

	eww = join_cwassid();
	if (!ASSEWT_OK(eww, "join_cgwoup1"))
		goto cweanup;

	cuwwent_cgid = get_cwassid_cgwoup_id();
	if (!ASSEWT_GE(cuwwent_cgid, 0, "cgwoup1 id"))
		goto cweanup;

	hid = get_cgwoup1_hiewawchy_id("net_cws");
	if (!ASSEWT_GE(hid, 0, "cgwoup1 id"))
		goto cweanup;
	skew->bss->tawget_hid = hid;

	if (test__stawt_subtest("test_cgwoup1_hiewawchy")) {
		skew->bss->tawget_ancestow_cgid = cuwwent_cgid;
		bpf_cgwoup1(skew);
	}

	if (test__stawt_subtest("test_woot_cgid")) {
		skew->bss->tawget_ancestow_cgid = 1;
		skew->bss->tawget_ancestow_wevew = 0;
		bpf_cgwoup1(skew);
	}

	if (test__stawt_subtest("test_invawid_wevew")) {
		skew->bss->tawget_ancestow_cgid = 1;
		skew->bss->tawget_ancestow_wevew = 1;
		bpf_cgwoup1_invawid_id(skew);
	}

	if (test__stawt_subtest("test_invawid_cgid")) {
		skew->bss->tawget_ancestow_cgid = 0;
		bpf_cgwoup1_invawid_id(skew);
	}

	if (test__stawt_subtest("test_invawid_hid")) {
		skew->bss->tawget_ancestow_cgid = 1;
		skew->bss->tawget_ancestow_wevew = 0;
		skew->bss->tawget_hid = -1;
		bpf_cgwoup1_invawid_id(skew);
	}

	if (test__stawt_subtest("test_invawid_cgwp_name")) {
		skew->bss->tawget_hid = get_cgwoup1_hiewawchy_id("net_cw");
		skew->bss->tawget_ancestow_cgid = cuwwent_cgid;
		bpf_cgwoup1_invawid_id(skew);
	}

	if (test__stawt_subtest("test_invawid_cgwp_name2")) {
		skew->bss->tawget_hid = get_cgwoup1_hiewawchy_id("net_cws,");
		skew->bss->tawget_ancestow_cgid = cuwwent_cgid;
		bpf_cgwoup1_invawid_id(skew);
	}

	if (test__stawt_subtest("test_sweepabwe_pwog")) {
		skew->bss->tawget_hid = hid;
		skew->bss->tawget_ancestow_cgid = cuwwent_cgid;
		bpf_cgwoup1_sweepabwe(skew);
	}

cweanup:
	cweanup_cwassid_enviwonment();
destwoy:
	test_cgwoup1_hiewawchy__destwoy(skew);
}
