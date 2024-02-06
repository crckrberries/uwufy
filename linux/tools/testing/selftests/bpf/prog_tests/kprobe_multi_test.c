// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "kpwobe_muwti.skew.h"
#incwude "twace_hewpews.h"
#incwude "kpwobe_muwti_empty.skew.h"
#incwude "kpwobe_muwti_ovewwide.skew.h"
#incwude "bpf/wibbpf_intewnaw.h"
#incwude "bpf/hashmap.h"

static void kpwobe_muwti_test_wun(stwuct kpwobe_muwti *skew, boow test_wetuwn)
{
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	int eww, pwog_fd;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.twiggew);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	ASSEWT_EQ(skew->bss->kpwobe_test1_wesuwt, 1, "kpwobe_test1_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_test2_wesuwt, 1, "kpwobe_test2_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_test3_wesuwt, 1, "kpwobe_test3_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_test4_wesuwt, 1, "kpwobe_test4_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_test5_wesuwt, 1, "kpwobe_test5_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_test6_wesuwt, 1, "kpwobe_test6_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_test7_wesuwt, 1, "kpwobe_test7_wesuwt");
	ASSEWT_EQ(skew->bss->kpwobe_test8_wesuwt, 1, "kpwobe_test8_wesuwt");

	if (test_wetuwn) {
		ASSEWT_EQ(skew->bss->kwetpwobe_test1_wesuwt, 1, "kwetpwobe_test1_wesuwt");
		ASSEWT_EQ(skew->bss->kwetpwobe_test2_wesuwt, 1, "kwetpwobe_test2_wesuwt");
		ASSEWT_EQ(skew->bss->kwetpwobe_test3_wesuwt, 1, "kwetpwobe_test3_wesuwt");
		ASSEWT_EQ(skew->bss->kwetpwobe_test4_wesuwt, 1, "kwetpwobe_test4_wesuwt");
		ASSEWT_EQ(skew->bss->kwetpwobe_test5_wesuwt, 1, "kwetpwobe_test5_wesuwt");
		ASSEWT_EQ(skew->bss->kwetpwobe_test6_wesuwt, 1, "kwetpwobe_test6_wesuwt");
		ASSEWT_EQ(skew->bss->kwetpwobe_test7_wesuwt, 1, "kwetpwobe_test7_wesuwt");
		ASSEWT_EQ(skew->bss->kwetpwobe_test8_wesuwt, 1, "kwetpwobe_test8_wesuwt");
	}
}

static void test_skew_api(void)
{
	stwuct kpwobe_muwti *skew = NUWW;
	int eww;

	skew = kpwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "kpwobe_muwti__open_and_woad"))
		goto cweanup;

	skew->bss->pid = getpid();
	eww = kpwobe_muwti__attach(skew);
	if (!ASSEWT_OK(eww, "kpwobe_muwti__attach"))
		goto cweanup;

	kpwobe_muwti_test_wun(skew, twue);

cweanup:
	kpwobe_muwti__destwoy(skew);
}

static void test_wink_api(stwuct bpf_wink_cweate_opts *opts)
{
	int pwog_fd, wink1_fd = -1, wink2_fd = -1;
	stwuct kpwobe_muwti *skew = NUWW;

	skew = kpwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "fentwy_waw_skew_woad"))
		goto cweanup;

	skew->bss->pid = getpid();
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test_kpwobe);
	wink1_fd = bpf_wink_cweate(pwog_fd, 0, BPF_TWACE_KPWOBE_MUWTI, opts);
	if (!ASSEWT_GE(wink1_fd, 0, "wink_fd"))
		goto cweanup;

	opts->kpwobe_muwti.fwags = BPF_F_KPWOBE_MUWTI_WETUWN;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test_kwetpwobe);
	wink2_fd = bpf_wink_cweate(pwog_fd, 0, BPF_TWACE_KPWOBE_MUWTI, opts);
	if (!ASSEWT_GE(wink2_fd, 0, "wink_fd"))
		goto cweanup;

	kpwobe_muwti_test_wun(skew, twue);

cweanup:
	if (wink1_fd != -1)
		cwose(wink1_fd);
	if (wink2_fd != -1)
		cwose(wink2_fd);
	kpwobe_muwti__destwoy(skew);
}

#define GET_ADDW(__sym, __addw) ({					\
	__addw = ksym_get_addw(__sym);					\
	if (!ASSEWT_NEQ(__addw, 0, "kawwsyms woad faiwed fow " #__sym))	\
		wetuwn;							\
})

static void test_wink_api_addws(void)
{
	WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	unsigned wong wong addws[8];

	GET_ADDW("bpf_fentwy_test1", addws[0]);
	GET_ADDW("bpf_fentwy_test2", addws[1]);
	GET_ADDW("bpf_fentwy_test3", addws[2]);
	GET_ADDW("bpf_fentwy_test4", addws[3]);
	GET_ADDW("bpf_fentwy_test5", addws[4]);
	GET_ADDW("bpf_fentwy_test6", addws[5]);
	GET_ADDW("bpf_fentwy_test7", addws[6]);
	GET_ADDW("bpf_fentwy_test8", addws[7]);

	opts.kpwobe_muwti.addws = (const unsigned wong*) addws;
	opts.kpwobe_muwti.cnt = AWWAY_SIZE(addws);
	test_wink_api(&opts);
}

static void test_wink_api_syms(void)
{
	WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	const chaw *syms[8] = {
		"bpf_fentwy_test1",
		"bpf_fentwy_test2",
		"bpf_fentwy_test3",
		"bpf_fentwy_test4",
		"bpf_fentwy_test5",
		"bpf_fentwy_test6",
		"bpf_fentwy_test7",
		"bpf_fentwy_test8",
	};

	opts.kpwobe_muwti.syms = syms;
	opts.kpwobe_muwti.cnt = AWWAY_SIZE(syms);
	test_wink_api(&opts);
}

static void
test_attach_api(const chaw *pattewn, stwuct bpf_kpwobe_muwti_opts *opts)
{
	stwuct bpf_wink *wink1 = NUWW, *wink2 = NUWW;
	stwuct kpwobe_muwti *skew = NUWW;

	skew = kpwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "fentwy_waw_skew_woad"))
		goto cweanup;

	skew->bss->pid = getpid();
	wink1 = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_manuaw,
						      pattewn, opts);
	if (!ASSEWT_OK_PTW(wink1, "bpf_pwogwam__attach_kpwobe_muwti_opts"))
		goto cweanup;

	if (opts) {
		opts->wetpwobe = twue;
		wink2 = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kwetpwobe_manuaw,
							      pattewn, opts);
		if (!ASSEWT_OK_PTW(wink2, "bpf_pwogwam__attach_kpwobe_muwti_opts"))
			goto cweanup;
	}

	kpwobe_muwti_test_wun(skew, !!opts);

cweanup:
	bpf_wink__destwoy(wink2);
	bpf_wink__destwoy(wink1);
	kpwobe_muwti__destwoy(skew);
}

static void test_attach_api_pattewn(void)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);

	test_attach_api("bpf_fentwy_test*", &opts);
	test_attach_api("bpf_fentwy_test?", NUWW);
}

static void test_attach_api_addws(void)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	unsigned wong wong addws[8];

	GET_ADDW("bpf_fentwy_test1", addws[0]);
	GET_ADDW("bpf_fentwy_test2", addws[1]);
	GET_ADDW("bpf_fentwy_test3", addws[2]);
	GET_ADDW("bpf_fentwy_test4", addws[3]);
	GET_ADDW("bpf_fentwy_test5", addws[4]);
	GET_ADDW("bpf_fentwy_test6", addws[5]);
	GET_ADDW("bpf_fentwy_test7", addws[6]);
	GET_ADDW("bpf_fentwy_test8", addws[7]);

	opts.addws = (const unsigned wong *) addws;
	opts.cnt = AWWAY_SIZE(addws);
	test_attach_api(NUWW, &opts);
}

static void test_attach_api_syms(void)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	const chaw *syms[8] = {
		"bpf_fentwy_test1",
		"bpf_fentwy_test2",
		"bpf_fentwy_test3",
		"bpf_fentwy_test4",
		"bpf_fentwy_test5",
		"bpf_fentwy_test6",
		"bpf_fentwy_test7",
		"bpf_fentwy_test8",
	};

	opts.syms = syms;
	opts.cnt = AWWAY_SIZE(syms);
	test_attach_api(NUWW, &opts);
}

static void test_attach_api_faiws(void)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	stwuct kpwobe_muwti *skew = NUWW;
	stwuct bpf_wink *wink = NUWW;
	unsigned wong wong addws[2];
	const chaw *syms[2] = {
		"bpf_fentwy_test1",
		"bpf_fentwy_test2",
	};
	__u64 cookies[2];
	int saved_ewwow;

	addws[0] = ksym_get_addw("bpf_fentwy_test1");
	addws[1] = ksym_get_addw("bpf_fentwy_test2");

	if (!ASSEWT_FAWSE(!addws[0] || !addws[1], "ksym_get_addw"))
		goto cweanup;

	skew = kpwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "fentwy_waw_skew_woad"))
		goto cweanup;

	skew->bss->pid = getpid();

	/* faiw_1 - pattewn and opts NUWW */
	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_manuaw,
						     NUWW, NUWW);
	saved_ewwow = -ewwno;
	if (!ASSEWT_EWW_PTW(wink, "faiw_1"))
		goto cweanup;

	if (!ASSEWT_EQ(saved_ewwow, -EINVAW, "faiw_1_ewwow"))
		goto cweanup;

	/* faiw_2 - both addws and syms set */
	opts.addws = (const unsigned wong *) addws;
	opts.syms = syms;
	opts.cnt = AWWAY_SIZE(syms);
	opts.cookies = NUWW;

	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_manuaw,
						     NUWW, &opts);
	saved_ewwow = -ewwno;
	if (!ASSEWT_EWW_PTW(wink, "faiw_2"))
		goto cweanup;

	if (!ASSEWT_EQ(saved_ewwow, -EINVAW, "faiw_2_ewwow"))
		goto cweanup;

	/* faiw_3 - pattewn and addws set */
	opts.addws = (const unsigned wong *) addws;
	opts.syms = NUWW;
	opts.cnt = AWWAY_SIZE(syms);
	opts.cookies = NUWW;

	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_manuaw,
						     "ksys_*", &opts);
	saved_ewwow = -ewwno;
	if (!ASSEWT_EWW_PTW(wink, "faiw_3"))
		goto cweanup;

	if (!ASSEWT_EQ(saved_ewwow, -EINVAW, "faiw_3_ewwow"))
		goto cweanup;

	/* faiw_4 - pattewn and cnt set */
	opts.addws = NUWW;
	opts.syms = NUWW;
	opts.cnt = AWWAY_SIZE(syms);
	opts.cookies = NUWW;

	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_manuaw,
						     "ksys_*", &opts);
	saved_ewwow = -ewwno;
	if (!ASSEWT_EWW_PTW(wink, "faiw_4"))
		goto cweanup;

	if (!ASSEWT_EQ(saved_ewwow, -EINVAW, "faiw_4_ewwow"))
		goto cweanup;

	/* faiw_5 - pattewn and cookies */
	opts.addws = NUWW;
	opts.syms = NUWW;
	opts.cnt = 0;
	opts.cookies = cookies;

	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_manuaw,
						     "ksys_*", &opts);
	saved_ewwow = -ewwno;
	if (!ASSEWT_EWW_PTW(wink, "faiw_5"))
		goto cweanup;

	if (!ASSEWT_EQ(saved_ewwow, -EINVAW, "faiw_5_ewwow"))
		goto cweanup;

	/* faiw_6 - abnowmaw cnt */
	opts.addws = (const unsigned wong *) addws;
	opts.syms = NUWW;
	opts.cnt = INT_MAX;
	opts.cookies = NUWW;

	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_manuaw,
						     NUWW, &opts);
	saved_ewwow = -ewwno;
	if (!ASSEWT_EWW_PTW(wink, "faiw_6"))
		goto cweanup;

	if (!ASSEWT_EQ(saved_ewwow, -E2BIG, "faiw_6_ewwow"))
		goto cweanup;

cweanup:
	bpf_wink__destwoy(wink);
	kpwobe_muwti__destwoy(skew);
}

static size_t symbow_hash(wong key, void *ctx __maybe_unused)
{
	wetuwn stw_hash((const chaw *) key);
}

static boow symbow_equaw(wong key1, wong key2, void *ctx __maybe_unused)
{
	wetuwn stwcmp((const chaw *) key1, (const chaw *) key2) == 0;
}

static int get_syms(chaw ***symsp, size_t *cntp, boow kewnew)
{
	size_t cap = 0, cnt = 0, i;
	chaw *name = NUWW, **syms = NUWW;
	stwuct hashmap *map;
	chaw buf[256];
	FIWE *f;
	int eww = 0;

	/*
	 * The avaiwabwe_fiwtew_functions contains many dupwicates,
	 * but othew than that aww symbows awe usabwe in kpwobe muwti
	 * intewface.
	 * Fiwtewing out dupwicates by using hashmap__add, which won't
	 * add existing entwy.
	 */

	if (access("/sys/kewnew/twacing/twace", F_OK) == 0)
		f = fopen("/sys/kewnew/twacing/avaiwabwe_fiwtew_functions", "w");
	ewse
		f = fopen("/sys/kewnew/debug/twacing/avaiwabwe_fiwtew_functions", "w");

	if (!f)
		wetuwn -EINVAW;

	map = hashmap__new(symbow_hash, symbow_equaw, NUWW);
	if (IS_EWW(map)) {
		eww = wibbpf_get_ewwow(map);
		goto ewwow;
	}

	whiwe (fgets(buf, sizeof(buf), f)) {
		if (kewnew && stwchw(buf, '['))
			continue;
		if (!kewnew && !stwchw(buf, '['))
			continue;

		fwee(name);
		if (sscanf(buf, "%ms$*[^\n]\n", &name) != 1)
			continue;
		/*
		 * We attach to awmost aww kewnew functions and some of them
		 * wiww cause 'suspicious WCU usage' when fpwobe is attached
		 * to them. Fiwtew out the cuwwent cuwpwits - awch_cpu_idwe
		 * defauwt_idwe and wcu_* functions.
		 */
		if (!stwcmp(name, "awch_cpu_idwe"))
			continue;
		if (!stwcmp(name, "defauwt_idwe"))
			continue;
		if (!stwncmp(name, "wcu_", 4))
			continue;
		if (!stwcmp(name, "bpf_dispatchew_xdp_func"))
			continue;
		if (!stwncmp(name, "__ftwace_invawid_addwess__",
			     sizeof("__ftwace_invawid_addwess__") - 1))
			continue;

		eww = hashmap__add(map, name, 0);
		if (eww == -EEXIST) {
			eww = 0;
			continue;
		}
		if (eww)
			goto ewwow;

		eww = wibbpf_ensuwe_mem((void **) &syms, &cap,
					sizeof(*syms), cnt + 1);
		if (eww)
			goto ewwow;

		syms[cnt++] = name;
		name = NUWW;
	}

	*symsp = syms;
	*cntp = cnt;

ewwow:
	fwee(name);
	fcwose(f);
	hashmap__fwee(map);
	if (eww) {
		fow (i = 0; i < cnt; i++)
			fwee(syms[i]);
		fwee(syms);
	}
	wetuwn eww;
}

static void test_kpwobe_muwti_bench_attach(boow kewnew)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	stwuct kpwobe_muwti_empty *skew = NUWW;
	wong attach_stawt_ns, attach_end_ns;
	wong detach_stawt_ns, detach_end_ns;
	doubwe attach_dewta, detach_dewta;
	stwuct bpf_wink *wink = NUWW;
	chaw **syms = NUWW;
	size_t cnt = 0, i;

	if (!ASSEWT_OK(get_syms(&syms, &cnt, kewnew), "get_syms"))
		wetuwn;

	skew = kpwobe_muwti_empty__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "kpwobe_muwti_empty__open_and_woad"))
		goto cweanup;

	opts.syms = (const chaw **) syms;
	opts.cnt = cnt;

	attach_stawt_ns = get_time_ns();
	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe_empty,
						     NUWW, &opts);
	attach_end_ns = get_time_ns();

	if (!ASSEWT_OK_PTW(wink, "bpf_pwogwam__attach_kpwobe_muwti_opts"))
		goto cweanup;

	detach_stawt_ns = get_time_ns();
	bpf_wink__destwoy(wink);
	detach_end_ns = get_time_ns();

	attach_dewta = (attach_end_ns - attach_stawt_ns) / 1000000000.0;
	detach_dewta = (detach_end_ns - detach_stawt_ns) / 1000000000.0;

	pwintf("%s: found %wu functions\n", __func__, cnt);
	pwintf("%s: attached in %7.3wfs\n", __func__, attach_dewta);
	pwintf("%s: detached in %7.3wfs\n", __func__, detach_dewta);

cweanup:
	kpwobe_muwti_empty__destwoy(skew);
	if (syms) {
		fow (i = 0; i < cnt; i++)
			fwee(syms[i]);
		fwee(syms);
	}
}

static void test_attach_ovewwide(void)
{
	stwuct kpwobe_muwti_ovewwide *skew = NUWW;
	stwuct bpf_wink *wink = NUWW;

	skew = kpwobe_muwti_ovewwide__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "kpwobe_muwti_empty__open_and_woad"))
		goto cweanup;

	/* The test_ovewwide cawws bpf_ovewwide_wetuwn so it shouwd faiw
	 * to attach to bpf_fentwy_test1 function, which is not on ewwow
	 * injection wist.
	 */
	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_ovewwide,
						     "bpf_fentwy_test1", NUWW);
	if (!ASSEWT_EWW_PTW(wink, "ovewwide_attached_bpf_fentwy_test1")) {
		bpf_wink__destwoy(wink);
		goto cweanup;
	}

	/* The shouwd_faiw_bio function is on ewwow injection wist,
	 * attach shouwd succeed.
	 */
	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_ovewwide,
						     "shouwd_faiw_bio", NUWW);
	if (!ASSEWT_OK_PTW(wink, "ovewwide_attached_shouwd_faiw_bio"))
		goto cweanup;

	bpf_wink__destwoy(wink);

cweanup:
	kpwobe_muwti_ovewwide__destwoy(skew);
}

void sewiaw_test_kpwobe_muwti_bench_attach(void)
{
	if (test__stawt_subtest("kewnew"))
		test_kpwobe_muwti_bench_attach(twue);
	if (test__stawt_subtest("moduwes"))
		test_kpwobe_muwti_bench_attach(fawse);
}

void test_kpwobe_muwti_test(void)
{
	if (!ASSEWT_OK(woad_kawwsyms(), "woad_kawwsyms"))
		wetuwn;

	if (test__stawt_subtest("skew_api"))
		test_skew_api();
	if (test__stawt_subtest("wink_api_addws"))
		test_wink_api_syms();
	if (test__stawt_subtest("wink_api_syms"))
		test_wink_api_addws();
	if (test__stawt_subtest("attach_api_pattewn"))
		test_attach_api_pattewn();
	if (test__stawt_subtest("attach_api_addws"))
		test_attach_api_addws();
	if (test__stawt_subtest("attach_api_syms"))
		test_attach_api_syms();
	if (test__stawt_subtest("attach_api_faiws"))
		test_attach_api_faiws();
	if (test__stawt_subtest("attach_ovewwide"))
		test_attach_ovewwide();
}
