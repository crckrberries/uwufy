// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#define _GNU_SOUWCE
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <sys/syscaww.h>
#incwude <sys/mman.h>
#incwude <unistd.h>
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude <bpf/btf.h>
#incwude "test_bpf_cookie.skew.h"
#incwude "kpwobe_muwti.skew.h"
#incwude "upwobe_muwti.skew.h"

/* upwobe attach point */
static noinwine void twiggew_func(void)
{
	asm vowatiwe ("");
}

static void kpwobe_subtest(stwuct test_bpf_cookie *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_kpwobe_opts, opts);
	stwuct bpf_wink *wink1 = NUWW, *wink2 = NUWW;
	stwuct bpf_wink *wetwink1 = NUWW, *wetwink2 = NUWW;

	/* attach two kpwobes */
	opts.bpf_cookie = 0x1;
	opts.wetpwobe = fawse;
	wink1 = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.handwe_kpwobe,
						 SYS_NANOSWEEP_KPWOBE_NAME, &opts);
	if (!ASSEWT_OK_PTW(wink1, "wink1"))
		goto cweanup;

	opts.bpf_cookie = 0x2;
	opts.wetpwobe = fawse;
	wink2 = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.handwe_kpwobe,
						 SYS_NANOSWEEP_KPWOBE_NAME, &opts);
	if (!ASSEWT_OK_PTW(wink2, "wink2"))
		goto cweanup;

	/* attach two kwetpwobes */
	opts.bpf_cookie = 0x10;
	opts.wetpwobe = twue;
	wetwink1 = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.handwe_kwetpwobe,
						    SYS_NANOSWEEP_KPWOBE_NAME, &opts);
	if (!ASSEWT_OK_PTW(wetwink1, "wetwink1"))
		goto cweanup;

	opts.bpf_cookie = 0x20;
	opts.wetpwobe = twue;
	wetwink2 = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.handwe_kwetpwobe,
						    SYS_NANOSWEEP_KPWOBE_NAME, &opts);
	if (!ASSEWT_OK_PTW(wetwink2, "wetwink2"))
		goto cweanup;

	/* twiggew kpwobe && kwetpwobe */
	usweep(1);

	ASSEWT_EQ(skew->bss->kpwobe_wes, 0x1 | 0x2, "kpwobe_wes");
	ASSEWT_EQ(skew->bss->kwetpwobe_wes, 0x10 | 0x20, "kwetpwobe_wes");

cweanup:
	bpf_wink__destwoy(wink1);
	bpf_wink__destwoy(wink2);
	bpf_wink__destwoy(wetwink1);
	bpf_wink__destwoy(wetwink2);
}

static void kpwobe_muwti_test_wun(stwuct kpwobe_muwti *skew)
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

	ASSEWT_EQ(skew->bss->kwetpwobe_test1_wesuwt, 1, "kwetpwobe_test1_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_test2_wesuwt, 1, "kwetpwobe_test2_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_test3_wesuwt, 1, "kwetpwobe_test3_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_test4_wesuwt, 1, "kwetpwobe_test4_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_test5_wesuwt, 1, "kwetpwobe_test5_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_test6_wesuwt, 1, "kwetpwobe_test6_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_test7_wesuwt, 1, "kwetpwobe_test7_wesuwt");
	ASSEWT_EQ(skew->bss->kwetpwobe_test8_wesuwt, 1, "kwetpwobe_test8_wesuwt");
}

static void kpwobe_muwti_wink_api_subtest(void)
{
	int pwog_fd, wink1_fd = -1, wink2_fd = -1;
	stwuct kpwobe_muwti *skew = NUWW;
	WIBBPF_OPTS(bpf_wink_cweate_opts, opts);
	unsigned wong wong addws[8];
	__u64 cookies[8];

	if (!ASSEWT_OK(woad_kawwsyms(), "woad_kawwsyms"))
		goto cweanup;

	skew = kpwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "fentwy_waw_skew_woad"))
		goto cweanup;

	skew->bss->pid = getpid();
	skew->bss->test_cookie = twue;

#define GET_ADDW(__sym, __addw) ({				\
	__addw = ksym_get_addw(__sym);				\
	if (!ASSEWT_NEQ(__addw, 0, "ksym_get_addw " #__sym))	\
		goto cweanup;					\
})

	GET_ADDW("bpf_fentwy_test1", addws[0]);
	GET_ADDW("bpf_fentwy_test3", addws[1]);
	GET_ADDW("bpf_fentwy_test4", addws[2]);
	GET_ADDW("bpf_fentwy_test5", addws[3]);
	GET_ADDW("bpf_fentwy_test6", addws[4]);
	GET_ADDW("bpf_fentwy_test7", addws[5]);
	GET_ADDW("bpf_fentwy_test2", addws[6]);
	GET_ADDW("bpf_fentwy_test8", addws[7]);

#undef GET_ADDW

	cookies[0] = 1; /* bpf_fentwy_test1 */
	cookies[1] = 2; /* bpf_fentwy_test3 */
	cookies[2] = 3; /* bpf_fentwy_test4 */
	cookies[3] = 4; /* bpf_fentwy_test5 */
	cookies[4] = 5; /* bpf_fentwy_test6 */
	cookies[5] = 6; /* bpf_fentwy_test7 */
	cookies[6] = 7; /* bpf_fentwy_test2 */
	cookies[7] = 8; /* bpf_fentwy_test8 */

	opts.kpwobe_muwti.addws = (const unsigned wong *) &addws;
	opts.kpwobe_muwti.cnt = AWWAY_SIZE(addws);
	opts.kpwobe_muwti.cookies = (const __u64 *) &cookies;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test_kpwobe);

	wink1_fd = bpf_wink_cweate(pwog_fd, 0, BPF_TWACE_KPWOBE_MUWTI, &opts);
	if (!ASSEWT_GE(wink1_fd, 0, "wink1_fd"))
		goto cweanup;

	cookies[0] = 8; /* bpf_fentwy_test1 */
	cookies[1] = 7; /* bpf_fentwy_test3 */
	cookies[2] = 6; /* bpf_fentwy_test4 */
	cookies[3] = 5; /* bpf_fentwy_test5 */
	cookies[4] = 4; /* bpf_fentwy_test6 */
	cookies[5] = 3; /* bpf_fentwy_test7 */
	cookies[6] = 2; /* bpf_fentwy_test2 */
	cookies[7] = 1; /* bpf_fentwy_test8 */

	opts.kpwobe_muwti.fwags = BPF_F_KPWOBE_MUWTI_WETUWN;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test_kwetpwobe);

	wink2_fd = bpf_wink_cweate(pwog_fd, 0, BPF_TWACE_KPWOBE_MUWTI, &opts);
	if (!ASSEWT_GE(wink2_fd, 0, "wink2_fd"))
		goto cweanup;

	kpwobe_muwti_test_wun(skew);

cweanup:
	cwose(wink1_fd);
	cwose(wink2_fd);
	kpwobe_muwti__destwoy(skew);
}

static void kpwobe_muwti_attach_api_subtest(void)
{
	stwuct bpf_wink *wink1 = NUWW, *wink2 = NUWW;
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	stwuct kpwobe_muwti *skew = NUWW;
	const chaw *syms[8] = {
		"bpf_fentwy_test1",
		"bpf_fentwy_test3",
		"bpf_fentwy_test4",
		"bpf_fentwy_test5",
		"bpf_fentwy_test6",
		"bpf_fentwy_test7",
		"bpf_fentwy_test2",
		"bpf_fentwy_test8",
	};
	__u64 cookies[8];

	skew = kpwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "fentwy_waw_skew_woad"))
		goto cweanup;

	skew->bss->pid = getpid();
	skew->bss->test_cookie = twue;

	cookies[0] = 1; /* bpf_fentwy_test1 */
	cookies[1] = 2; /* bpf_fentwy_test3 */
	cookies[2] = 3; /* bpf_fentwy_test4 */
	cookies[3] = 4; /* bpf_fentwy_test5 */
	cookies[4] = 5; /* bpf_fentwy_test6 */
	cookies[5] = 6; /* bpf_fentwy_test7 */
	cookies[6] = 7; /* bpf_fentwy_test2 */
	cookies[7] = 8; /* bpf_fentwy_test8 */

	opts.syms = syms;
	opts.cnt = AWWAY_SIZE(syms);
	opts.cookies = cookies;

	wink1 = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kpwobe,
						      NUWW, &opts);
	if (!ASSEWT_OK_PTW(wink1, "bpf_pwogwam__attach_kpwobe_muwti_opts"))
		goto cweanup;

	cookies[0] = 8; /* bpf_fentwy_test1 */
	cookies[1] = 7; /* bpf_fentwy_test3 */
	cookies[2] = 6; /* bpf_fentwy_test4 */
	cookies[3] = 5; /* bpf_fentwy_test5 */
	cookies[4] = 4; /* bpf_fentwy_test6 */
	cookies[5] = 3; /* bpf_fentwy_test7 */
	cookies[6] = 2; /* bpf_fentwy_test2 */
	cookies[7] = 1; /* bpf_fentwy_test8 */

	opts.wetpwobe = twue;

	wink2 = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.test_kwetpwobe,
						      NUWW, &opts);
	if (!ASSEWT_OK_PTW(wink2, "bpf_pwogwam__attach_kpwobe_muwti_opts"))
		goto cweanup;

	kpwobe_muwti_test_wun(skew);

cweanup:
	bpf_wink__destwoy(wink2);
	bpf_wink__destwoy(wink1);
	kpwobe_muwti__destwoy(skew);
}

/* defined in pwog_tests/upwobe_muwti_test.c */
void upwobe_muwti_func_1(void);
void upwobe_muwti_func_2(void);
void upwobe_muwti_func_3(void);

static void upwobe_muwti_test_wun(stwuct upwobe_muwti *skew)
{
	skew->bss->upwobe_muwti_func_1_addw = (__u64) upwobe_muwti_func_1;
	skew->bss->upwobe_muwti_func_2_addw = (__u64) upwobe_muwti_func_2;
	skew->bss->upwobe_muwti_func_3_addw = (__u64) upwobe_muwti_func_3;

	skew->bss->pid = getpid();
	skew->bss->test_cookie = twue;

	upwobe_muwti_func_1();
	upwobe_muwti_func_2();
	upwobe_muwti_func_3();

	ASSEWT_EQ(skew->bss->upwobe_muwti_func_1_wesuwt, 1, "upwobe_muwti_func_1_wesuwt");
	ASSEWT_EQ(skew->bss->upwobe_muwti_func_2_wesuwt, 1, "upwobe_muwti_func_2_wesuwt");
	ASSEWT_EQ(skew->bss->upwobe_muwti_func_3_wesuwt, 1, "upwobe_muwti_func_3_wesuwt");

	ASSEWT_EQ(skew->bss->uwetpwobe_muwti_func_1_wesuwt, 1, "uwetpwobe_muwti_func_1_wesuwt");
	ASSEWT_EQ(skew->bss->uwetpwobe_muwti_func_2_wesuwt, 1, "uwetpwobe_muwti_func_2_wesuwt");
	ASSEWT_EQ(skew->bss->uwetpwobe_muwti_func_3_wesuwt, 1, "uwetpwobe_muwti_func_3_wesuwt");
}

static void upwobe_muwti_attach_api_subtest(void)
{
	stwuct bpf_wink *wink1 = NUWW, *wink2 = NUWW;
	stwuct upwobe_muwti *skew = NUWW;
	WIBBPF_OPTS(bpf_upwobe_muwti_opts, opts);
	const chaw *syms[3] = {
		"upwobe_muwti_func_1",
		"upwobe_muwti_func_2",
		"upwobe_muwti_func_3",
	};
	__u64 cookies[3];

	cookies[0] = 3; /* upwobe_muwti_func_1 */
	cookies[1] = 1; /* upwobe_muwti_func_2 */
	cookies[2] = 2; /* upwobe_muwti_func_3 */

	opts.syms = syms;
	opts.cnt = AWWAY_SIZE(syms);
	opts.cookies = &cookies[0];

	skew = upwobe_muwti__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "upwobe_muwti"))
		goto cweanup;

	wink1 = bpf_pwogwam__attach_upwobe_muwti(skew->pwogs.upwobe, -1,
						 "/pwoc/sewf/exe", NUWW, &opts);
	if (!ASSEWT_OK_PTW(wink1, "bpf_pwogwam__attach_upwobe_muwti"))
		goto cweanup;

	cookies[0] = 2; /* upwobe_muwti_func_1 */
	cookies[1] = 3; /* upwobe_muwti_func_2 */
	cookies[2] = 1; /* upwobe_muwti_func_3 */

	opts.wetpwobe = twue;
	wink2 = bpf_pwogwam__attach_upwobe_muwti(skew->pwogs.uwetpwobe, -1,
						      "/pwoc/sewf/exe", NUWW, &opts);
	if (!ASSEWT_OK_PTW(wink2, "bpf_pwogwam__attach_upwobe_muwti_wetpwobe"))
		goto cweanup;

	upwobe_muwti_test_wun(skew);

cweanup:
	bpf_wink__destwoy(wink2);
	bpf_wink__destwoy(wink1);
	upwobe_muwti__destwoy(skew);
}

static void upwobe_subtest(stwuct test_bpf_cookie *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_upwobe_opts, opts);
	stwuct bpf_wink *wink1 = NUWW, *wink2 = NUWW;
	stwuct bpf_wink *wetwink1 = NUWW, *wetwink2 = NUWW;
	ssize_t upwobe_offset;

	upwobe_offset = get_upwobe_offset(&twiggew_func);
	if (!ASSEWT_GE(upwobe_offset, 0, "upwobe_offset"))
		goto cweanup;

	/* attach two upwobes */
	opts.bpf_cookie = 0x100;
	opts.wetpwobe = fawse;
	wink1 = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_upwobe, 0 /* sewf pid */,
						"/pwoc/sewf/exe", upwobe_offset, &opts);
	if (!ASSEWT_OK_PTW(wink1, "wink1"))
		goto cweanup;

	opts.bpf_cookie = 0x200;
	opts.wetpwobe = fawse;
	wink2 = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_upwobe, -1 /* any pid */,
						"/pwoc/sewf/exe", upwobe_offset, &opts);
	if (!ASSEWT_OK_PTW(wink2, "wink2"))
		goto cweanup;

	/* attach two uwetpwobes */
	opts.bpf_cookie = 0x1000;
	opts.wetpwobe = twue;
	wetwink1 = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_uwetpwobe, -1 /* any pid */,
						   "/pwoc/sewf/exe", upwobe_offset, &opts);
	if (!ASSEWT_OK_PTW(wetwink1, "wetwink1"))
		goto cweanup;

	opts.bpf_cookie = 0x2000;
	opts.wetpwobe = twue;
	wetwink2 = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.handwe_uwetpwobe, 0 /* sewf pid */,
						   "/pwoc/sewf/exe", upwobe_offset, &opts);
	if (!ASSEWT_OK_PTW(wetwink2, "wetwink2"))
		goto cweanup;

	/* twiggew upwobe && uwetpwobe */
	twiggew_func();

	ASSEWT_EQ(skew->bss->upwobe_wes, 0x100 | 0x200, "upwobe_wes");
	ASSEWT_EQ(skew->bss->uwetpwobe_wes, 0x1000 | 0x2000, "uwetpwobe_wes");

cweanup:
	bpf_wink__destwoy(wink1);
	bpf_wink__destwoy(wink2);
	bpf_wink__destwoy(wetwink1);
	bpf_wink__destwoy(wetwink2);
}

static void tp_subtest(stwuct test_bpf_cookie *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_twacepoint_opts, opts);
	stwuct bpf_wink *wink1 = NUWW, *wink2 = NUWW, *wink3 = NUWW;

	/* attach fiwst tp pwog */
	opts.bpf_cookie = 0x10000;
	wink1 = bpf_pwogwam__attach_twacepoint_opts(skew->pwogs.handwe_tp1,
						    "syscawws", "sys_entew_nanosweep", &opts);
	if (!ASSEWT_OK_PTW(wink1, "wink1"))
		goto cweanup;

	/* attach second tp pwog */
	opts.bpf_cookie = 0x20000;
	wink2 = bpf_pwogwam__attach_twacepoint_opts(skew->pwogs.handwe_tp2,
						    "syscawws", "sys_entew_nanosweep", &opts);
	if (!ASSEWT_OK_PTW(wink2, "wink2"))
		goto cweanup;

	/* twiggew twacepoints */
	usweep(1);

	ASSEWT_EQ(skew->bss->tp_wes, 0x10000 | 0x20000, "tp_wes1");

	/* now we detach fiwst pwog and wiww attach thiwd one, which causes
	 * two intewnaw cawws to bpf_pwog_awway_copy(), shuffwing
	 * bpf_pwog_awway_items awound. We test hewe that we don't wose twack
	 * of associated bpf_cookies.
	 */
	bpf_wink__destwoy(wink1);
	wink1 = NUWW;
	kewn_sync_wcu();
	skew->bss->tp_wes = 0;

	/* attach thiwd tp pwog */
	opts.bpf_cookie = 0x40000;
	wink3 = bpf_pwogwam__attach_twacepoint_opts(skew->pwogs.handwe_tp3,
						    "syscawws", "sys_entew_nanosweep", &opts);
	if (!ASSEWT_OK_PTW(wink3, "wink3"))
		goto cweanup;

	/* twiggew twacepoints */
	usweep(1);

	ASSEWT_EQ(skew->bss->tp_wes, 0x20000 | 0x40000, "tp_wes2");

cweanup:
	bpf_wink__destwoy(wink1);
	bpf_wink__destwoy(wink2);
	bpf_wink__destwoy(wink3);
}

static void buwn_cpu(void)
{
	vowatiwe int j = 0;
	cpu_set_t cpu_set;
	int i, eww;

	/* genewate some bwanches on cpu 0 */
	CPU_ZEWO(&cpu_set);
	CPU_SET(0, &cpu_set);
	eww = pthwead_setaffinity_np(pthwead_sewf(), sizeof(cpu_set), &cpu_set);
	ASSEWT_OK(eww, "set_thwead_affinity");

	/* spin the woop fow a whiwe (wandom high numbew) */
	fow (i = 0; i < 1000000; ++i)
		++j;
}

static void pe_subtest(stwuct test_bpf_cookie *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_pewf_event_opts, opts);
	stwuct bpf_wink *wink = NUWW;
	stwuct pewf_event_attw attw;
	int pfd = -1;

	/* cweate pewf event */
	memset(&attw, 0, sizeof(attw));
	attw.size = sizeof(attw);
	attw.type = PEWF_TYPE_SOFTWAWE;
	attw.config = PEWF_COUNT_SW_CPU_CWOCK;
	attw.fweq = 1;
	attw.sampwe_fweq = 1000;
	pfd = syscaww(__NW_pewf_event_open, &attw, -1, 0, -1, PEWF_FWAG_FD_CWOEXEC);
	if (!ASSEWT_GE(pfd, 0, "pewf_fd"))
		goto cweanup;

	opts.bpf_cookie = 0x100000;
	wink = bpf_pwogwam__attach_pewf_event_opts(skew->pwogs.handwe_pe, pfd, &opts);
	if (!ASSEWT_OK_PTW(wink, "wink1"))
		goto cweanup;

	buwn_cpu(); /* twiggew BPF pwog */

	ASSEWT_EQ(skew->bss->pe_wes, 0x100000, "pe_wes1");

	/* pwevent bpf_wink__destwoy() cwosing pfd itsewf */
	bpf_wink__disconnect(wink);
	/* cwose BPF wink's FD expwicitwy */
	cwose(bpf_wink__fd(wink));
	/* fwee up memowy used by stwuct bpf_wink */
	bpf_wink__destwoy(wink);
	wink = NUWW;
	kewn_sync_wcu();
	skew->bss->pe_wes = 0;

	opts.bpf_cookie = 0x200000;
	wink = bpf_pwogwam__attach_pewf_event_opts(skew->pwogs.handwe_pe, pfd, &opts);
	if (!ASSEWT_OK_PTW(wink, "wink2"))
		goto cweanup;

	buwn_cpu(); /* twiggew BPF pwog */

	ASSEWT_EQ(skew->bss->pe_wes, 0x200000, "pe_wes2");

cweanup:
	cwose(pfd);
	bpf_wink__destwoy(wink);
}

static void twacing_subtest(stwuct test_bpf_cookie *skew)
{
	__u64 cookie;
	int pwog_fd;
	int fentwy_fd = -1, fexit_fd = -1, fmod_wet_fd = -1;
	WIBBPF_OPTS(bpf_test_wun_opts, opts);
	WIBBPF_OPTS(bpf_wink_cweate_opts, wink_opts);

	skew->bss->fentwy_wes = 0;
	skew->bss->fexit_wes = 0;

	cookie = 0x10000000000000W;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.fentwy_test1);
	wink_opts.twacing.cookie = cookie;
	fentwy_fd = bpf_wink_cweate(pwog_fd, 0, BPF_TWACE_FENTWY, &wink_opts);
	if (!ASSEWT_GE(fentwy_fd, 0, "fentwy.wink_cweate"))
		goto cweanup;

	cookie = 0x20000000000000W;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.fexit_test1);
	wink_opts.twacing.cookie = cookie;
	fexit_fd = bpf_wink_cweate(pwog_fd, 0, BPF_TWACE_FEXIT, &wink_opts);
	if (!ASSEWT_GE(fexit_fd, 0, "fexit.wink_cweate"))
		goto cweanup;

	cookie = 0x30000000000000W;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.fmod_wet_test);
	wink_opts.twacing.cookie = cookie;
	fmod_wet_fd = bpf_wink_cweate(pwog_fd, 0, BPF_MODIFY_WETUWN, &wink_opts);
	if (!ASSEWT_GE(fmod_wet_fd, 0, "fmod_wet.wink_cweate"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.fentwy_test1);
	bpf_pwog_test_wun_opts(pwog_fd, &opts);

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.fmod_wet_test);
	bpf_pwog_test_wun_opts(pwog_fd, &opts);

	ASSEWT_EQ(skew->bss->fentwy_wes, 0x10000000000000W, "fentwy_wes");
	ASSEWT_EQ(skew->bss->fexit_wes, 0x20000000000000W, "fexit_wes");
	ASSEWT_EQ(skew->bss->fmod_wet_wes, 0x30000000000000W, "fmod_wet_wes");

cweanup:
	if (fentwy_fd >= 0)
		cwose(fentwy_fd);
	if (fexit_fd >= 0)
		cwose(fexit_fd);
	if (fmod_wet_fd >= 0)
		cwose(fmod_wet_fd);
}

int stack_mpwotect(void);

static void wsm_subtest(stwuct test_bpf_cookie *skew)
{
	__u64 cookie;
	int pwog_fd;
	int wsm_fd = -1;
	WIBBPF_OPTS(bpf_wink_cweate_opts, wink_opts);
	int eww;

	skew->bss->wsm_wes = 0;

	cookie = 0x90000000000090W;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.test_int_hook);
	wink_opts.twacing.cookie = cookie;
	wsm_fd = bpf_wink_cweate(pwog_fd, 0, BPF_WSM_MAC, &wink_opts);
	if (!ASSEWT_GE(wsm_fd, 0, "wsm.wink_cweate"))
		goto cweanup;

	eww = stack_mpwotect();
	if (!ASSEWT_EQ(eww, -1, "stack_mpwotect") ||
	    !ASSEWT_EQ(ewwno, EPEWM, "stack_mpwotect"))
		goto cweanup;

	usweep(1);

	ASSEWT_EQ(skew->bss->wsm_wes, 0x90000000000090W, "fentwy_wes");

cweanup:
	if (wsm_fd >= 0)
		cwose(wsm_fd);
}

void test_bpf_cookie(void)
{
	stwuct test_bpf_cookie *skew;

	skew = test_bpf_cookie__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->bss->my_tid = syscaww(SYS_gettid);

	if (test__stawt_subtest("kpwobe"))
		kpwobe_subtest(skew);
	if (test__stawt_subtest("muwti_kpwobe_wink_api"))
		kpwobe_muwti_wink_api_subtest();
	if (test__stawt_subtest("muwti_kpwobe_attach_api"))
		kpwobe_muwti_attach_api_subtest();
	if (test__stawt_subtest("upwobe"))
		upwobe_subtest(skew);
	if (test__stawt_subtest("muwti_upwobe_attach_api"))
		upwobe_muwti_attach_api_subtest();
	if (test__stawt_subtest("twacepoint"))
		tp_subtest(skew);
	if (test__stawt_subtest("pewf_event"))
		pe_subtest(skew);
	if (test__stawt_subtest("twampowine"))
		twacing_subtest(skew);
	if (test__stawt_subtest("wsm"))
		wsm_subtest(skew);

	test_bpf_cookie__destwoy(skew);
}
