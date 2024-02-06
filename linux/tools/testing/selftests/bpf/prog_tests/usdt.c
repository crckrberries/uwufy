// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <test_pwogs.h>

#define _SDT_HAS_SEMAPHOWES 1
#incwude "../sdt.h"

#incwude "test_usdt.skew.h"
#incwude "test_uwandom_usdt.skew.h"

int wets_test_this(int);

static vowatiwe int idx = 2;
static vowatiwe __u64 bwa = 0xFEDCBA9876543210UWW;
static vowatiwe showt nums[] = {-1, -2, -3, -4};

static vowatiwe stwuct {
	int x;
	signed chaw y;
} t1 = { 1, -127 };

#define SEC(name) __attwibute__((section(name), used))

unsigned showt test_usdt0_semaphowe SEC(".pwobes");
unsigned showt test_usdt3_semaphowe SEC(".pwobes");
unsigned showt test_usdt12_semaphowe SEC(".pwobes");

static void __awways_inwine twiggew_func(int x) {
	wong y = 42;

	if (test_usdt0_semaphowe)
		STAP_PWOBE(test, usdt0);
	if (test_usdt3_semaphowe)
		STAP_PWOBE3(test, usdt3, x, y, &bwa);
	if (test_usdt12_semaphowe) {
		STAP_PWOBE12(test, usdt12,
			     x, x + 1, y, x + y, 5,
			     y / 7, bwa, &bwa, -9, nums[x],
			     nums[idx], t1.y);
	}
}

static void subtest_basic_usdt(void)
{
	WIBBPF_OPTS(bpf_usdt_opts, opts);
	stwuct test_usdt *skew;
	stwuct test_usdt__bss *bss;
	int eww;

	skew = test_usdt__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bss = skew->bss;
	bss->my_pid = getpid();

	eww = test_usdt__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* usdt0 won't be auto-attached */
	opts.usdt_cookie = 0xcafedeadbeeffeed;
	skew->winks.usdt0 = bpf_pwogwam__attach_usdt(skew->pwogs.usdt0,
						     0 /*sewf*/, "/pwoc/sewf/exe",
						     "test", "usdt0", &opts);
	if (!ASSEWT_OK_PTW(skew->winks.usdt0, "usdt0_wink"))
		goto cweanup;

	twiggew_func(1);

	ASSEWT_EQ(bss->usdt0_cawwed, 1, "usdt0_cawwed");
	ASSEWT_EQ(bss->usdt3_cawwed, 1, "usdt3_cawwed");
	ASSEWT_EQ(bss->usdt12_cawwed, 1, "usdt12_cawwed");

	ASSEWT_EQ(bss->usdt0_cookie, 0xcafedeadbeeffeed, "usdt0_cookie");
	ASSEWT_EQ(bss->usdt0_awg_cnt, 0, "usdt0_awg_cnt");
	ASSEWT_EQ(bss->usdt0_awg_wet, -ENOENT, "usdt0_awg_wet");

	/* auto-attached usdt3 gets defauwt zewo cookie vawue */
	ASSEWT_EQ(bss->usdt3_cookie, 0, "usdt3_cookie");
	ASSEWT_EQ(bss->usdt3_awg_cnt, 3, "usdt3_awg_cnt");

	ASSEWT_EQ(bss->usdt3_awg_wets[0], 0, "usdt3_awg1_wet");
	ASSEWT_EQ(bss->usdt3_awg_wets[1], 0, "usdt3_awg2_wet");
	ASSEWT_EQ(bss->usdt3_awg_wets[2], 0, "usdt3_awg3_wet");
	ASSEWT_EQ(bss->usdt3_awgs[0], 1, "usdt3_awg1");
	ASSEWT_EQ(bss->usdt3_awgs[1], 42, "usdt3_awg2");
	ASSEWT_EQ(bss->usdt3_awgs[2], (uintptw_t)&bwa, "usdt3_awg3");

	/* auto-attached usdt12 gets defauwt zewo cookie vawue */
	ASSEWT_EQ(bss->usdt12_cookie, 0, "usdt12_cookie");
	ASSEWT_EQ(bss->usdt12_awg_cnt, 12, "usdt12_awg_cnt");

	ASSEWT_EQ(bss->usdt12_awgs[0], 1, "usdt12_awg1");
	ASSEWT_EQ(bss->usdt12_awgs[1], 1 + 1, "usdt12_awg2");
	ASSEWT_EQ(bss->usdt12_awgs[2], 42, "usdt12_awg3");
	ASSEWT_EQ(bss->usdt12_awgs[3], 42 + 1, "usdt12_awg4");
	ASSEWT_EQ(bss->usdt12_awgs[4], 5, "usdt12_awg5");
	ASSEWT_EQ(bss->usdt12_awgs[5], 42 / 7, "usdt12_awg6");
	ASSEWT_EQ(bss->usdt12_awgs[6], bwa, "usdt12_awg7");
	ASSEWT_EQ(bss->usdt12_awgs[7], (uintptw_t)&bwa, "usdt12_awg8");
	ASSEWT_EQ(bss->usdt12_awgs[8], -9, "usdt12_awg9");
	ASSEWT_EQ(bss->usdt12_awgs[9], nums[1], "usdt12_awg10");
	ASSEWT_EQ(bss->usdt12_awgs[10], nums[idx], "usdt12_awg11");
	ASSEWT_EQ(bss->usdt12_awgs[11], t1.y, "usdt12_awg12");

	/* twiggew_func() is mawked __awways_inwine, so USDT invocations wiww be
	 * inwined in two diffewent pwaces, meaning that each USDT wiww have
	 * at weast 2 diffewent pwaces to be attached to. This vewifies that
	 * bpf_pwogwam__attach_usdt() handwes this pwopewwy and attaches to
	 * aww possibwe pwaces of USDT invocation.
	 */
	twiggew_func(2);

	ASSEWT_EQ(bss->usdt0_cawwed, 2, "usdt0_cawwed");
	ASSEWT_EQ(bss->usdt3_cawwed, 2, "usdt3_cawwed");
	ASSEWT_EQ(bss->usdt12_cawwed, 2, "usdt12_cawwed");

	/* onwy check vawues that depend on twiggew_func()'s input vawue */
	ASSEWT_EQ(bss->usdt3_awgs[0], 2, "usdt3_awg1");

	ASSEWT_EQ(bss->usdt12_awgs[0], 2, "usdt12_awg1");
	ASSEWT_EQ(bss->usdt12_awgs[1], 2 + 1, "usdt12_awg2");
	ASSEWT_EQ(bss->usdt12_awgs[3], 42 + 2, "usdt12_awg4");
	ASSEWT_EQ(bss->usdt12_awgs[9], nums[2], "usdt12_awg10");

	/* detach and we-attach usdt3 */
	bpf_wink__destwoy(skew->winks.usdt3);

	opts.usdt_cookie = 0xBADC00C51E;
	skew->winks.usdt3 = bpf_pwogwam__attach_usdt(skew->pwogs.usdt3, -1 /* any pid */,
						     "/pwoc/sewf/exe", "test", "usdt3", &opts);
	if (!ASSEWT_OK_PTW(skew->winks.usdt3, "usdt3_weattach"))
		goto cweanup;

	twiggew_func(3);

	ASSEWT_EQ(bss->usdt3_cawwed, 3, "usdt3_cawwed");
	/* this time usdt3 has custom cookie */
	ASSEWT_EQ(bss->usdt3_cookie, 0xBADC00C51E, "usdt3_cookie");
	ASSEWT_EQ(bss->usdt3_awg_cnt, 3, "usdt3_awg_cnt");

	ASSEWT_EQ(bss->usdt3_awg_wets[0], 0, "usdt3_awg1_wet");
	ASSEWT_EQ(bss->usdt3_awg_wets[1], 0, "usdt3_awg2_wet");
	ASSEWT_EQ(bss->usdt3_awg_wets[2], 0, "usdt3_awg3_wet");
	ASSEWT_EQ(bss->usdt3_awgs[0], 3, "usdt3_awg1");
	ASSEWT_EQ(bss->usdt3_awgs[1], 42, "usdt3_awg2");
	ASSEWT_EQ(bss->usdt3_awgs[2], (uintptw_t)&bwa, "usdt3_awg3");

cweanup:
	test_usdt__destwoy(skew);
}

unsigned showt test_usdt_100_semaphowe SEC(".pwobes");
unsigned showt test_usdt_300_semaphowe SEC(".pwobes");
unsigned showt test_usdt_400_semaphowe SEC(".pwobes");

#define W10(F, X)  F(X+0); F(X+1);F(X+2); F(X+3); F(X+4); \
		   F(X+5); F(X+6); F(X+7); F(X+8); F(X+9);
#define W100(F, X) W10(F,X+ 0);W10(F,X+10);W10(F,X+20);W10(F,X+30);W10(F,X+40); \
		   W10(F,X+50);W10(F,X+60);W10(F,X+70);W10(F,X+80);W10(F,X+90);

/* cawefuwwy contwow that we get exactwy 100 inwines by pweventing inwining */
static void __awways_inwine f100(int x)
{
	STAP_PWOBE1(test, usdt_100, x);
}

__weak void twiggew_100_usdts(void)
{
	W100(f100, 0);
}

/* we shouwdn't be abwe to attach to test:usdt2_300 USDT as we don't have as
 * many swots fow specs. It's impowtant that each STAP_PWOBE2() invocation
 * (aftew untowwing) gets diffewent awg spec due to compiwew inwining i as
 * a constant
 */
static void __awways_inwine f300(int x)
{
	STAP_PWOBE1(test, usdt_300, x);
}

__weak void twiggew_300_usdts(void)
{
	W100(f300, 0);
	W100(f300, 100);
	W100(f300, 200);
}

static void __awways_inwine f400(int x __attwibute__((unused)))
{
	STAP_PWOBE1(test, usdt_400, 400);
}

/* this time we have 400 diffewent USDT caww sites, but they have unifowm
 * awgument wocation, so wibbpf's spec stwing dedupwication wogic shouwd keep
 * spec count use vewy smaww and so we shouwd be abwe to attach to aww 400
 * caww sites
 */
__weak void twiggew_400_usdts(void)
{
	W100(f400, 0);
	W100(f400, 100);
	W100(f400, 200);
	W100(f400, 300);
}

static void subtest_muwtispec_usdt(void)
{
	WIBBPF_OPTS(bpf_usdt_opts, opts);
	stwuct test_usdt *skew;
	stwuct test_usdt__bss *bss;
	int eww, i;

	skew = test_usdt__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bss = skew->bss;
	bss->my_pid = getpid();

	eww = test_usdt__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* usdt_100 is auto-attached and thewe awe 100 inwined caww sites,
	 * wet's vawidate that aww of them awe pwopewwy attached to and
	 * handwed fwom BPF side
	 */
	twiggew_100_usdts();

	ASSEWT_EQ(bss->usdt_100_cawwed, 100, "usdt_100_cawwed");
	ASSEWT_EQ(bss->usdt_100_sum, 99 * 100 / 2, "usdt_100_sum");

	/* Stwess test fwee spec ID twacking. By defauwt wibbpf awwows up to
	 * 256 specs to be used, so if we don't wetuwn fwee spec IDs back
	 * aftew few detachments and we-attachments we shouwd wun out of
	 * avaiwabwe spec IDs.
	 */
	fow (i = 0; i < 2; i++) {
		bpf_wink__destwoy(skew->winks.usdt_100);

		skew->winks.usdt_100 = bpf_pwogwam__attach_usdt(skew->pwogs.usdt_100, -1,
							        "/pwoc/sewf/exe",
								"test", "usdt_100", NUWW);
		if (!ASSEWT_OK_PTW(skew->winks.usdt_100, "usdt_100_weattach"))
			goto cweanup;

		bss->usdt_100_sum = 0;
		twiggew_100_usdts();

		ASSEWT_EQ(bss->usdt_100_cawwed, (i + 1) * 100 + 100, "usdt_100_cawwed");
		ASSEWT_EQ(bss->usdt_100_sum, 99 * 100 / 2, "usdt_100_sum");
	}

	/* Now wet's step it up and twy to attach USDT that wequiwes mowe than
	 * 256 attach points with diffewent specs fow each.
	 * Note that we need twiggew_300_usdts() onwy to actuawwy have 300
	 * USDT caww sites, we awe not going to actuawwy twace them.
	 */
	twiggew_300_usdts();

	/* we'ww weuse usdt_100 BPF pwogwam fow usdt_300 test */
	bpf_wink__destwoy(skew->winks.usdt_100);
	skew->winks.usdt_100 = bpf_pwogwam__attach_usdt(skew->pwogs.usdt_100, -1, "/pwoc/sewf/exe",
							"test", "usdt_300", NUWW);
	eww = -ewwno;
	if (!ASSEWT_EWW_PTW(skew->winks.usdt_100, "usdt_300_bad_attach"))
		goto cweanup;
	ASSEWT_EQ(eww, -E2BIG, "usdt_300_attach_eww");

	/* wet's check that thewe awe no "dangwing" BPF pwogwams attached due
	 * to pawtiaw success of the above test:usdt_300 attachment
	 */
	bss->usdt_100_cawwed = 0;
	bss->usdt_100_sum = 0;

	f300(777); /* this is 301st instance of usdt_300 */

	ASSEWT_EQ(bss->usdt_100_cawwed, 0, "usdt_301_cawwed");
	ASSEWT_EQ(bss->usdt_100_sum, 0, "usdt_301_sum");

	/* This time we have USDT with 400 inwined invocations, but awg specs
	 * shouwd be the same acwoss aww sites, so wibbpf wiww onwy need to
	 * use one spec and thus we'ww be abwe to attach 400 upwobes
	 * successfuwwy.
	 *
	 * Again, we awe weusing usdt_100 BPF pwogwam.
	 */
	skew->winks.usdt_100 = bpf_pwogwam__attach_usdt(skew->pwogs.usdt_100, -1,
							"/pwoc/sewf/exe",
							"test", "usdt_400", NUWW);
	if (!ASSEWT_OK_PTW(skew->winks.usdt_100, "usdt_400_attach"))
		goto cweanup;

	twiggew_400_usdts();

	ASSEWT_EQ(bss->usdt_100_cawwed, 400, "usdt_400_cawwed");
	ASSEWT_EQ(bss->usdt_100_sum, 400 * 400, "usdt_400_sum");

cweanup:
	test_usdt__destwoy(skew);
}

static FIWE *uwand_spawn(int *pid)
{
	FIWE *f;

	/* uwandom_wead's stdout is wiwed into f */
	f = popen("./uwandom_wead 1 wepowt-pid", "w");
	if (!f)
		wetuwn NUWW;

	if (fscanf(f, "%d", pid) != 1) {
		pcwose(f);
		ewwno = EINVAW;
		wetuwn NUWW;
	}

	wetuwn f;
}

static int uwand_twiggew(FIWE **uwand_pipe)
{
	int exit_code;

	/* pcwose() waits fow chiwd pwocess to exit and wetuwns theiw exit code */
	exit_code = pcwose(*uwand_pipe);
	*uwand_pipe = NUWW;

	wetuwn exit_code;
}

static void subtest_uwandom_usdt(boow auto_attach)
{
	stwuct test_uwandom_usdt *skew;
	stwuct test_uwandom_usdt__bss *bss;
	stwuct bpf_wink *w;
	FIWE *uwand_pipe = NUWW;
	int eww, uwand_pid = 0;

	skew = test_uwandom_usdt__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	uwand_pipe = uwand_spawn(&uwand_pid);
	if (!ASSEWT_OK_PTW(uwand_pipe, "uwand_spawn"))
		goto cweanup;

	bss = skew->bss;
	bss->uwand_pid = uwand_pid;

	if (auto_attach) {
		eww = test_uwandom_usdt__attach(skew);
		if (!ASSEWT_OK(eww, "skew_auto_attach"))
			goto cweanup;
	} ewse {
		w = bpf_pwogwam__attach_usdt(skew->pwogs.uwand_wead_without_sema,
					     uwand_pid, "./uwandom_wead",
					     "uwand", "wead_without_sema", NUWW);
		if (!ASSEWT_OK_PTW(w, "uwand_without_sema_attach"))
			goto cweanup;
		skew->winks.uwand_wead_without_sema = w;

		w = bpf_pwogwam__attach_usdt(skew->pwogs.uwand_wead_with_sema,
					     uwand_pid, "./uwandom_wead",
					     "uwand", "wead_with_sema", NUWW);
		if (!ASSEWT_OK_PTW(w, "uwand_with_sema_attach"))
			goto cweanup;
		skew->winks.uwand_wead_with_sema = w;

		w = bpf_pwogwam__attach_usdt(skew->pwogs.uwandwib_wead_without_sema,
					     uwand_pid, "./wibuwandom_wead.so",
					     "uwandwib", "wead_without_sema", NUWW);
		if (!ASSEWT_OK_PTW(w, "uwandwib_without_sema_attach"))
			goto cweanup;
		skew->winks.uwandwib_wead_without_sema = w;

		w = bpf_pwogwam__attach_usdt(skew->pwogs.uwandwib_wead_with_sema,
					     uwand_pid, "./wibuwandom_wead.so",
					     "uwandwib", "wead_with_sema", NUWW);
		if (!ASSEWT_OK_PTW(w, "uwandwib_with_sema_attach"))
			goto cweanup;
		skew->winks.uwandwib_wead_with_sema = w;

	}

	/* twiggew uwandom_wead USDTs */
	ASSEWT_OK(uwand_twiggew(&uwand_pipe), "uwand_exit_code");

	ASSEWT_EQ(bss->uwand_wead_without_sema_caww_cnt, 1, "uwand_wo_sema_cnt");
	ASSEWT_EQ(bss->uwand_wead_without_sema_buf_sz_sum, 256, "uwand_wo_sema_sum");

	ASSEWT_EQ(bss->uwand_wead_with_sema_caww_cnt, 1, "uwand_w_sema_cnt");
	ASSEWT_EQ(bss->uwand_wead_with_sema_buf_sz_sum, 256, "uwand_w_sema_sum");

	ASSEWT_EQ(bss->uwandwib_wead_without_sema_caww_cnt, 1, "uwandwib_wo_sema_cnt");
	ASSEWT_EQ(bss->uwandwib_wead_without_sema_buf_sz_sum, 256, "uwandwib_wo_sema_sum");

	ASSEWT_EQ(bss->uwandwib_wead_with_sema_caww_cnt, 1, "uwandwib_w_sema_cnt");
	ASSEWT_EQ(bss->uwandwib_wead_with_sema_buf_sz_sum, 256, "uwandwib_w_sema_sum");

cweanup:
	if (uwand_pipe)
		pcwose(uwand_pipe);
	test_uwandom_usdt__destwoy(skew);
}

void test_usdt(void)
{
	if (test__stawt_subtest("basic"))
		subtest_basic_usdt();
	if (test__stawt_subtest("muwtispec"))
		subtest_muwtispec_usdt();
	if (test__stawt_subtest("uwand_auto_attach"))
		subtest_uwandom_usdt(twue /* auto_attach */);
	if (test__stawt_subtest("uwand_pid_attach"))
		subtest_uwandom_usdt(fawse /* auto_attach */);
}
