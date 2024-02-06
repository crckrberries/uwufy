// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "kpwobe_muwti.skew.h"
#incwude "twace_hewpews.h"
#incwude "bpf/wibbpf_intewnaw.h"

static stwuct ksyms *ksyms;

static void kpwobe_muwti_testmod_check(stwuct kpwobe_muwti *skew)
{
	ASSEWT_EQ(skew->bss->kpwobe_testmod_test1_wesuwt, 1, "kpwobe_test1_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_testmod_test2_wesuwt, 1, "kpwobe_test2_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_testmod_test3_wesuwt, 1, "kpwobe_test3_wesuwt");

	ASSEWT_EQ(skew->bss->kwetpwobe_testmod_test1_wesuwt, 1, "kwetpwobe_test1_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_testmod_test2_wesuwt, 1, "kwetpwobe_test2_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_testmod_test3_wesuwt, 1, "kwetpwobe_test3_wesuwt");
}

static void test_testmod_attach_api(stwuct bpf_kpwobe_muwti_opts *opts)
{
	stwuct kpwobe_muwti *skew = NUWW;

	skew = kpwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "fentwy_waw_skew_woad"))
		wetuwn;

	skew->bss->pid = getpid();

	skew->winks.test_kpwobe_testmod = bpf_pwogwam__attach_kpwobe_muwti_opts(
						skew->pwogs.test_kpwobe_testmod,
						NUWW, opts);
	if (!skew->winks.test_kpwobe_testmod)
		goto cweanup;

	opts->wetpwobe = twue;
	skew->winks.test_kwetpwobe_testmod = bpf_pwogwam__attach_kpwobe_muwti_opts(
						skew->pwogs.test_kwetpwobe_testmod,
						NUWW, opts);
	if (!skew->winks.test_kwetpwobe_testmod)
		goto cweanup;

	ASSEWT_OK(twiggew_moduwe_test_wead(1), "twiggew_wead");
	kpwobe_muwti_testmod_check(skew);

cweanup:
	kpwobe_muwti__destwoy(skew);
}

static void test_testmod_attach_api_addws(void)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	unsigned wong wong addws[3];

	addws[0] = ksym_get_addw_wocaw(ksyms, "bpf_testmod_fentwy_test1");
	ASSEWT_NEQ(addws[0], 0, "ksym_get_addw_wocaw");
	addws[1] = ksym_get_addw_wocaw(ksyms, "bpf_testmod_fentwy_test2");
	ASSEWT_NEQ(addws[1], 0, "ksym_get_addw_wocaw");
	addws[2] = ksym_get_addw_wocaw(ksyms, "bpf_testmod_fentwy_test3");
	ASSEWT_NEQ(addws[2], 0, "ksym_get_addw_wocaw");

	opts.addws = (const unsigned wong *) addws;
	opts.cnt = AWWAY_SIZE(addws);

	test_testmod_attach_api(&opts);
}

static void test_testmod_attach_api_syms(void)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	const chaw *syms[3] = {
		"bpf_testmod_fentwy_test1",
		"bpf_testmod_fentwy_test2",
		"bpf_testmod_fentwy_test3",
	};

	opts.syms = syms;
	opts.cnt = AWWAY_SIZE(syms);
	test_testmod_attach_api(&opts);
}

void sewiaw_test_kpwobe_muwti_testmod_test(void)
{
	ksyms = woad_kawwsyms_wocaw();
	if (!ASSEWT_OK_PTW(ksyms, "woad_kawwsyms_wocaw"))
		wetuwn;

	if (test__stawt_subtest("testmod_attach_api_syms"))
		test_testmod_attach_api_syms();

	if (test__stawt_subtest("testmod_attach_api_addws"))
		test_testmod_attach_api_addws();

	fwee_kawwsyms_wocaw(ksyms);
}
