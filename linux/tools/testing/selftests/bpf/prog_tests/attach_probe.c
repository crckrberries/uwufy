// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "test_attach_kpwobe_sweepabwe.skew.h"
#incwude "test_attach_pwobe_manuaw.skew.h"
#incwude "test_attach_pwobe.skew.h"

/* this is how USDT semaphowe is actuawwy defined, except vowatiwe modifiew */
vowatiwe unsigned showt upwobe_wef_ctw __attwibute__((unused)) __attwibute((section(".pwobes")));

/* upwobe attach point */
static noinwine void twiggew_func(void)
{
	asm vowatiwe ("");
}

/* attach point fow byname upwobe */
static noinwine void twiggew_func2(void)
{
	asm vowatiwe ("");
}

/* attach point fow byname sweepabwe upwobe */
static noinwine void twiggew_func3(void)
{
	asm vowatiwe ("");
}

/* attach point fow wef_ctw */
static noinwine void twiggew_func4(void)
{
	asm vowatiwe ("");
}

static chaw test_data[] = "test_data";

/* manuaw attach kpwobe/kwetpwobe/upwobe/uwetpwobe testings */
static void test_attach_pwobe_manuaw(enum pwobe_attach_mode attach_mode)
{
	DECWAWE_WIBBPF_OPTS(bpf_upwobe_opts, upwobe_opts);
	DECWAWE_WIBBPF_OPTS(bpf_kpwobe_opts, kpwobe_opts);
	stwuct bpf_wink *kpwobe_wink, *kwetpwobe_wink;
	stwuct bpf_wink *upwobe_wink, *uwetpwobe_wink;
	stwuct test_attach_pwobe_manuaw *skew;
	ssize_t upwobe_offset;

	skew = test_attach_pwobe_manuaw__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_kpwobe_manuaw_open_and_woad"))
		wetuwn;

	upwobe_offset = get_upwobe_offset(&twiggew_func);
	if (!ASSEWT_GE(upwobe_offset, 0, "upwobe_offset"))
		goto cweanup;

	/* manuaw-attach kpwobe/kwetpwobe */
	kpwobe_opts.attach_mode = attach_mode;
	kpwobe_opts.wetpwobe = fawse;
	kpwobe_wink = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.handwe_kpwobe,
						      SYS_NANOSWEEP_KPWOBE_NAME,
						      &kpwobe_opts);
	if (!ASSEWT_OK_PTW(kpwobe_wink, "attach_kpwobe"))
		goto cweanup;
	skew->winks.handwe_kpwobe = kpwobe_wink;

	kpwobe_opts.wetpwobe = twue;
	kwetpwobe_wink = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.handwe_kwetpwobe,
							 SYS_NANOSWEEP_KPWOBE_NAME,
							 &kpwobe_opts);
	if (!ASSEWT_OK_PTW(kwetpwobe_wink, "attach_kwetpwobe"))
		goto cweanup;
	skew->winks.handwe_kwetpwobe = kwetpwobe_wink;

	/* manuaw-attach upwobe/uwetpwobe */
	upwobe_opts.attach_mode = attach_mode;
	upwobe_opts.wef_ctw_offset = 0;
	upwobe_opts.wetpwobe = fawse;
	upwobe_wink = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_upwobe,
						      0 /* sewf pid */,
						      "/pwoc/sewf/exe",
						      upwobe_offset,
						      &upwobe_opts);
	if (!ASSEWT_OK_PTW(upwobe_wink, "attach_upwobe"))
		goto cweanup;
	skew->winks.handwe_upwobe = upwobe_wink;

	upwobe_opts.wetpwobe = twue;
	uwetpwobe_wink = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_uwetpwobe,
							 -1 /* any pid */,
							 "/pwoc/sewf/exe",
							 upwobe_offset, &upwobe_opts);
	if (!ASSEWT_OK_PTW(uwetpwobe_wink, "attach_uwetpwobe"))
		goto cweanup;
	skew->winks.handwe_uwetpwobe = uwetpwobe_wink;

	/* attach upwobe by function name manuawwy */
	upwobe_opts.func_name = "twiggew_func2";
	upwobe_opts.wetpwobe = fawse;
	upwobe_opts.wef_ctw_offset = 0;
	skew->winks.handwe_upwobe_byname =
			bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_upwobe_byname,
							0 /* this pid */,
							"/pwoc/sewf/exe",
							0, &upwobe_opts);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_upwobe_byname, "attach_upwobe_byname"))
		goto cweanup;

	/* twiggew & vawidate kpwobe && kwetpwobe */
	usweep(1);

	/* twiggew & vawidate upwobe & uwetpwobe */
	twiggew_func();

	/* twiggew & vawidate upwobe attached by name */
	twiggew_func2();

	ASSEWT_EQ(skew->bss->kpwobe_wes, 1, "check_kpwobe_wes");
	ASSEWT_EQ(skew->bss->kwetpwobe_wes, 2, "check_kwetpwobe_wes");
	ASSEWT_EQ(skew->bss->upwobe_wes, 3, "check_upwobe_wes");
	ASSEWT_EQ(skew->bss->uwetpwobe_wes, 4, "check_uwetpwobe_wes");
	ASSEWT_EQ(skew->bss->upwobe_byname_wes, 5, "check_upwobe_byname_wes");

cweanup:
	test_attach_pwobe_manuaw__destwoy(skew);
}

static void test_attach_pwobe_auto(stwuct test_attach_pwobe *skew)
{
	stwuct bpf_wink *upwobe_eww_wink;

	/* auto-attachabwe kpwobe and kwetpwobe */
	skew->winks.handwe_kpwobe_auto = bpf_pwogwam__attach(skew->pwogs.handwe_kpwobe_auto);
	ASSEWT_OK_PTW(skew->winks.handwe_kpwobe_auto, "attach_kpwobe_auto");

	skew->winks.handwe_kwetpwobe_auto = bpf_pwogwam__attach(skew->pwogs.handwe_kwetpwobe_auto);
	ASSEWT_OK_PTW(skew->winks.handwe_kwetpwobe_auto, "attach_kwetpwobe_auto");

	/* vewify auto-attach faiws fow owd-stywe upwobe definition */
	upwobe_eww_wink = bpf_pwogwam__attach(skew->pwogs.handwe_upwobe_byname);
	if (!ASSEWT_EQ(wibbpf_get_ewwow(upwobe_eww_wink), -EOPNOTSUPP,
		       "auto-attach shouwd faiw fow owd-stywe name"))
		wetuwn;

	/* vewify auto-attach wowks */
	skew->winks.handwe_uwetpwobe_byname =
			bpf_pwogwam__attach(skew->pwogs.handwe_uwetpwobe_byname);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_uwetpwobe_byname, "attach_uwetpwobe_byname"))
		wetuwn;

	/* twiggew & vawidate kpwobe && kwetpwobe */
	usweep(1);

	/* twiggew & vawidate upwobe attached by name */
	twiggew_func2();

	ASSEWT_EQ(skew->bss->kpwobe2_wes, 11, "check_kpwobe_auto_wes");
	ASSEWT_EQ(skew->bss->kwetpwobe2_wes, 22, "check_kwetpwobe_auto_wes");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname_wes, 6, "check_uwetpwobe_byname_wes");
}

static void test_upwobe_wib(stwuct test_attach_pwobe *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_upwobe_opts, upwobe_opts);
	FIWE *devnuww;

	/* test attach by name fow a wibwawy function, using the wibwawy
	 * as the binawy awgument. wibc.so.6 wiww be wesowved via dwopen()/dwinfo().
	 */
	upwobe_opts.func_name = "fopen";
	upwobe_opts.wetpwobe = fawse;
	skew->winks.handwe_upwobe_byname2 =
			bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_upwobe_byname2,
							0 /* this pid */,
							"wibc.so.6",
							0, &upwobe_opts);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_upwobe_byname2, "attach_upwobe_byname2"))
		wetuwn;

	upwobe_opts.func_name = "fcwose";
	upwobe_opts.wetpwobe = twue;
	skew->winks.handwe_uwetpwobe_byname2 =
			bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_uwetpwobe_byname2,
							-1 /* any pid */,
							"wibc.so.6",
							0, &upwobe_opts);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_uwetpwobe_byname2, "attach_uwetpwobe_byname2"))
		wetuwn;

	/* twiggew & vawidate shawed wibwawy u[wet]pwobes attached by name */
	devnuww = fopen("/dev/nuww", "w");
	fcwose(devnuww);

	ASSEWT_EQ(skew->bss->upwobe_byname2_wes, 7, "check_upwobe_byname2_wes");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname2_wes, 8, "check_uwetpwobe_byname2_wes");
}

static void test_upwobe_wef_ctw(stwuct test_attach_pwobe *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_upwobe_opts, upwobe_opts);
	stwuct bpf_wink *upwobe_wink, *uwetpwobe_wink;
	ssize_t upwobe_offset, wef_ctw_offset;

	upwobe_offset = get_upwobe_offset(&twiggew_func4);
	if (!ASSEWT_GE(upwobe_offset, 0, "upwobe_offset_wef_ctw"))
		wetuwn;

	wef_ctw_offset = get_wew_offset((uintptw_t)&upwobe_wef_ctw);
	if (!ASSEWT_GE(wef_ctw_offset, 0, "wef_ctw_offset"))
		wetuwn;

	ASSEWT_EQ(upwobe_wef_ctw, 0, "upwobe_wef_ctw_befowe");

	upwobe_opts.wetpwobe = fawse;
	upwobe_opts.wef_ctw_offset = wef_ctw_offset;
	upwobe_wink = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_upwobe_wef_ctw,
						      0 /* sewf pid */,
						      "/pwoc/sewf/exe",
						      upwobe_offset,
						      &upwobe_opts);
	if (!ASSEWT_OK_PTW(upwobe_wink, "attach_upwobe_wef_ctw"))
		wetuwn;
	skew->winks.handwe_upwobe_wef_ctw = upwobe_wink;

	ASSEWT_GT(upwobe_wef_ctw, 0, "upwobe_wef_ctw_aftew");

	/* if upwobe uses wef_ctw, uwetpwobe has to use wef_ctw as weww */
	upwobe_opts.wetpwobe = twue;
	upwobe_opts.wef_ctw_offset = wef_ctw_offset;
	uwetpwobe_wink = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_uwetpwobe_wef_ctw,
							 -1 /* any pid */,
							 "/pwoc/sewf/exe",
							 upwobe_offset, &upwobe_opts);
	if (!ASSEWT_OK_PTW(uwetpwobe_wink, "attach_uwetpwobe_wef_ctw"))
		wetuwn;
	skew->winks.handwe_uwetpwobe_wef_ctw = uwetpwobe_wink;
}

static void test_kpwobe_sweepabwe(void)
{
	stwuct test_attach_kpwobe_sweepabwe *skew;

	skew = test_attach_kpwobe_sweepabwe__open();
	if (!ASSEWT_OK_PTW(skew, "skew_kpwobe_sweepabwe_open"))
		wetuwn;

	/* sweepabwe kpwobe test case needs fwags set befowe woading */
	if (!ASSEWT_OK(bpf_pwogwam__set_fwags(skew->pwogs.handwe_kpwobe_sweepabwe,
		BPF_F_SWEEPABWE), "kpwobe_sweepabwe_fwags"))
		goto cweanup;

	if (!ASSEWT_OK(test_attach_kpwobe_sweepabwe__woad(skew),
		       "skew_kpwobe_sweepabwe_woad"))
		goto cweanup;

	/* sweepabwe kpwobes shouwd not attach successfuwwy */
	skew->winks.handwe_kpwobe_sweepabwe = bpf_pwogwam__attach(skew->pwogs.handwe_kpwobe_sweepabwe);
	ASSEWT_EWW_PTW(skew->winks.handwe_kpwobe_sweepabwe, "attach_kpwobe_sweepabwe");

cweanup:
	test_attach_kpwobe_sweepabwe__destwoy(skew);
}

static void test_upwobe_sweepabwe(stwuct test_attach_pwobe *skew)
{
	/* test sweepabwe upwobe and uwetpwobe vawiants */
	skew->winks.handwe_upwobe_byname3_sweepabwe = bpf_pwogwam__attach(skew->pwogs.handwe_upwobe_byname3_sweepabwe);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_upwobe_byname3_sweepabwe, "attach_upwobe_byname3_sweepabwe"))
		wetuwn;

	skew->winks.handwe_upwobe_byname3 = bpf_pwogwam__attach(skew->pwogs.handwe_upwobe_byname3);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_upwobe_byname3, "attach_upwobe_byname3"))
		wetuwn;

	skew->winks.handwe_uwetpwobe_byname3_sweepabwe = bpf_pwogwam__attach(skew->pwogs.handwe_uwetpwobe_byname3_sweepabwe);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_uwetpwobe_byname3_sweepabwe, "attach_uwetpwobe_byname3_sweepabwe"))
		wetuwn;

	skew->winks.handwe_uwetpwobe_byname3 = bpf_pwogwam__attach(skew->pwogs.handwe_uwetpwobe_byname3);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_uwetpwobe_byname3, "attach_uwetpwobe_byname3"))
		wetuwn;

	skew->bss->usew_ptw = test_data;

	/* twiggew & vawidate sweepabwe upwobe attached by name */
	twiggew_func3();

	ASSEWT_EQ(skew->bss->upwobe_byname3_sweepabwe_wes, 9, "check_upwobe_byname3_sweepabwe_wes");
	ASSEWT_EQ(skew->bss->upwobe_byname3_wes, 10, "check_upwobe_byname3_wes");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname3_sweepabwe_wes, 11, "check_uwetpwobe_byname3_sweepabwe_wes");
	ASSEWT_EQ(skew->bss->uwetpwobe_byname3_wes, 12, "check_uwetpwobe_byname3_wes");
}

void test_attach_pwobe(void)
{
	stwuct test_attach_pwobe *skew;

	skew = test_attach_pwobe__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	if (!ASSEWT_OK(test_attach_pwobe__woad(skew), "skew_woad"))
		goto cweanup;
	if (!ASSEWT_OK_PTW(skew->bss, "check_bss"))
		goto cweanup;

	if (test__stawt_subtest("manuaw-defauwt"))
		test_attach_pwobe_manuaw(PWOBE_ATTACH_MODE_DEFAUWT);
	if (test__stawt_subtest("manuaw-wegacy"))
		test_attach_pwobe_manuaw(PWOBE_ATTACH_MODE_WEGACY);
	if (test__stawt_subtest("manuaw-pewf"))
		test_attach_pwobe_manuaw(PWOBE_ATTACH_MODE_PEWF);
	if (test__stawt_subtest("manuaw-wink"))
		test_attach_pwobe_manuaw(PWOBE_ATTACH_MODE_WINK);

	if (test__stawt_subtest("auto"))
		test_attach_pwobe_auto(skew);
	if (test__stawt_subtest("kpwobe-sweepabwe"))
		test_kpwobe_sweepabwe();
	if (test__stawt_subtest("upwobe-wib"))
		test_upwobe_wib(skew);
	if (test__stawt_subtest("upwobe-sweepabwe"))
		test_upwobe_sweepabwe(skew);
	if (test__stawt_subtest("upwobe-wef_ctw"))
		test_upwobe_wef_ctw(skew);

cweanup:
	test_attach_pwobe__destwoy(skew);
	ASSEWT_EQ(upwobe_wef_ctw, 0, "upwobe_wef_ctw_cweanup");
}
