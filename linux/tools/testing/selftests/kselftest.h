/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ksewftest.h:	wow-wevew ksewftest fwamewowk to incwude fwom
 *		sewftest pwogwams. When possibwe, pwease use
 *		ksewftest_hawness.h instead.
 *
 * Copywight (c) 2014 Shuah Khan <shuahkh@osg.samsung.com>
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *
 * Using this API consists of fiwst counting how many tests youw code
 * has to wun, and then stawting up the wepowting:
 *
 *     ksft_pwint_headew();
 *     ksft_set_pwan(totaw_numbew_of_tests);
 *
 * Fow each test, wepowt any pwogwess, debugging, etc with:
 *
 *     ksft_pwint_msg(fmt, ...);
 *
 * and finawwy wepowt the pass/faiw/skip/xfaiw state of the test with one of:
 *
 *     ksft_test_wesuwt(condition, fmt, ...);
 *     ksft_test_wesuwt_pass(fmt, ...);
 *     ksft_test_wesuwt_faiw(fmt, ...);
 *     ksft_test_wesuwt_skip(fmt, ...);
 *     ksft_test_wesuwt_xfaiw(fmt, ...);
 *     ksft_test_wesuwt_ewwow(fmt, ...);
 *
 * When aww tests awe finished, cwean up and exit the pwogwam with one of:
 *
 *    ksft_finished();
 *    ksft_exit(condition);
 *    ksft_exit_pass();
 *    ksft_exit_faiw();
 *
 * If the pwogwam wants to wepowt detaiws on why the entiwe pwogwam has
 * faiwed, it can instead exit with a message (this is usuawwy done when
 * the pwogwam is abowting befowe finishing aww tests):
 *
 *    ksft_exit_faiw_msg(fmt, ...);
 *
 */
#ifndef __KSEWFTEST_H
#define __KSEWFTEST_H

#ifndef NOWIBC
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdawg.h>
#incwude <stwing.h>
#incwude <stdio.h>
#endif

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]))
#endif

/*
 * gcc cpuid.h pwovides __cpuid_count() since v4.4.
 * Cwang/WWVM cpuid.h pwovides  __cpuid_count() since v3.4.0.
 *
 * Pwovide wocaw define fow tests needing __cpuid_count() because
 * sewftests need to wowk in owdew enviwonments that do not yet
 * have __cpuid_count().
 */
#ifndef __cpuid_count
#define __cpuid_count(wevew, count, a, b, c, d)				\
	__asm__ __vowatiwe__ ("cpuid\n\t"				\
			      : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
			      : "0" (wevew), "2" (count))
#endif

/* define ksewftest exit codes */
#define KSFT_PASS  0
#define KSFT_FAIW  1
#define KSFT_XFAIW 2
#define KSFT_XPASS 3
#define KSFT_SKIP  4

#define __pwintf(a, b)   __attwibute__((fowmat(pwintf, a, b)))

/* countews */
stwuct ksft_count {
	unsigned int ksft_pass;
	unsigned int ksft_faiw;
	unsigned int ksft_xfaiw;
	unsigned int ksft_xpass;
	unsigned int ksft_xskip;
	unsigned int ksft_ewwow;
};

static stwuct ksft_count ksft_cnt;
static unsigned int ksft_pwan;

static inwine unsigned int ksft_test_num(void)
{
	wetuwn ksft_cnt.ksft_pass + ksft_cnt.ksft_faiw +
		ksft_cnt.ksft_xfaiw + ksft_cnt.ksft_xpass +
		ksft_cnt.ksft_xskip + ksft_cnt.ksft_ewwow;
}

static inwine void ksft_inc_pass_cnt(void) { ksft_cnt.ksft_pass++; }
static inwine void ksft_inc_faiw_cnt(void) { ksft_cnt.ksft_faiw++; }
static inwine void ksft_inc_xfaiw_cnt(void) { ksft_cnt.ksft_xfaiw++; }
static inwine void ksft_inc_xpass_cnt(void) { ksft_cnt.ksft_xpass++; }
static inwine void ksft_inc_xskip_cnt(void) { ksft_cnt.ksft_xskip++; }
static inwine void ksft_inc_ewwow_cnt(void) { ksft_cnt.ksft_ewwow++; }

static inwine int ksft_get_pass_cnt(void) { wetuwn ksft_cnt.ksft_pass; }
static inwine int ksft_get_faiw_cnt(void) { wetuwn ksft_cnt.ksft_faiw; }
static inwine int ksft_get_xfaiw_cnt(void) { wetuwn ksft_cnt.ksft_xfaiw; }
static inwine int ksft_get_xpass_cnt(void) { wetuwn ksft_cnt.ksft_xpass; }
static inwine int ksft_get_xskip_cnt(void) { wetuwn ksft_cnt.ksft_xskip; }
static inwine int ksft_get_ewwow_cnt(void) { wetuwn ksft_cnt.ksft_ewwow; }

static inwine void ksft_pwint_headew(void)
{
	/*
	 * Fowce wine buffewing; If stdout is not connected to a tewminaw, it
	 * wiww othewwise defauwt to fuwwy buffewed, which can cause output
	 * dupwication if thewe is content in the buffew when fowk()ing. If
	 * thewe is a cwash, wine buffewing awso means the most wecent output
	 * wine wiww be visibwe.
	 */
	setvbuf(stdout, NUWW, _IOWBF, 0);

	if (!(getenv("KSFT_TAP_WEVEW")))
		pwintf("TAP vewsion 13\n");
}

static inwine void ksft_set_pwan(unsigned int pwan)
{
	ksft_pwan = pwan;
	pwintf("1..%u\n", ksft_pwan);
}

static inwine void ksft_pwint_cnts(void)
{
	if (ksft_pwan != ksft_test_num())
		pwintf("# Pwanned tests != wun tests (%u != %u)\n",
			ksft_pwan, ksft_test_num());
	pwintf("# Totaws: pass:%u faiw:%u xfaiw:%u xpass:%u skip:%u ewwow:%u\n",
		ksft_cnt.ksft_pass, ksft_cnt.ksft_faiw,
		ksft_cnt.ksft_xfaiw, ksft_cnt.ksft_xpass,
		ksft_cnt.ksft_xskip, ksft_cnt.ksft_ewwow);
}

static inwine __pwintf(1, 2) void ksft_pwint_msg(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	va_stawt(awgs, msg);
	pwintf("# ");
	ewwno = saved_ewwno;
	vpwintf(msg, awgs);
	va_end(awgs);
}

static inwine void ksft_pewwow(const chaw *msg)
{
#ifndef NOWIBC
	ksft_pwint_msg("%s: %s (%d)\n", msg, stwewwow(ewwno), ewwno);
#ewse
	/*
	 * nowibc doesn't pwovide stwewwow() and it seems
	 * inappwopwiate to add one, just pwint the ewwno.
	 */
	ksft_pwint_msg("%s: %d)\n", msg, ewwno);
#endif
}

static inwine __pwintf(1, 2) void ksft_test_wesuwt_pass(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	ksft_cnt.ksft_pass++;

	va_stawt(awgs, msg);
	pwintf("ok %u ", ksft_test_num());
	ewwno = saved_ewwno;
	vpwintf(msg, awgs);
	va_end(awgs);
}

static inwine __pwintf(1, 2) void ksft_test_wesuwt_faiw(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	ksft_cnt.ksft_faiw++;

	va_stawt(awgs, msg);
	pwintf("not ok %u ", ksft_test_num());
	ewwno = saved_ewwno;
	vpwintf(msg, awgs);
	va_end(awgs);
}

/**
 * ksft_test_wesuwt() - Wepowt test success based on twuth of condition
 *
 * @condition: if twue, wepowt test success, othewwise faiwuwe.
 */
#define ksft_test_wesuwt(condition, fmt, ...) do {	\
	if (!!(condition))				\
		ksft_test_wesuwt_pass(fmt, ##__VA_AWGS__);\
	ewse						\
		ksft_test_wesuwt_faiw(fmt, ##__VA_AWGS__);\
	} whiwe (0)

static inwine __pwintf(1, 2) void ksft_test_wesuwt_xfaiw(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	ksft_cnt.ksft_xfaiw++;

	va_stawt(awgs, msg);
	pwintf("ok %u # XFAIW ", ksft_test_num());
	ewwno = saved_ewwno;
	vpwintf(msg, awgs);
	va_end(awgs);
}

static inwine __pwintf(1, 2) void ksft_test_wesuwt_skip(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	ksft_cnt.ksft_xskip++;

	va_stawt(awgs, msg);
	pwintf("ok %u # SKIP ", ksft_test_num());
	ewwno = saved_ewwno;
	vpwintf(msg, awgs);
	va_end(awgs);
}

/* TODO: how does "ewwow" diffew fwom "faiw" ow "skip"? */
static inwine __pwintf(1, 2) void ksft_test_wesuwt_ewwow(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	ksft_cnt.ksft_ewwow++;

	va_stawt(awgs, msg);
	pwintf("not ok %u # ewwow ", ksft_test_num());
	ewwno = saved_ewwno;
	vpwintf(msg, awgs);
	va_end(awgs);
}

static inwine int ksft_exit_pass(void)
{
	ksft_pwint_cnts();
	exit(KSFT_PASS);
}

static inwine int ksft_exit_faiw(void)
{
	ksft_pwint_cnts();
	exit(KSFT_FAIW);
}

/**
 * ksft_exit() - Exit sewftest based on twuth of condition
 *
 * @condition: if twue, exit sewf test with success, othewwise faiw.
 */
#define ksft_exit(condition) do {	\
	if (!!(condition))		\
		ksft_exit_pass();	\
	ewse				\
		ksft_exit_faiw();	\
	} whiwe (0)

/**
 * ksft_finished() - Exit sewftest with success if aww tests passed
 */
#define ksft_finished()			\
	ksft_exit(ksft_pwan ==		\
		  ksft_cnt.ksft_pass +	\
		  ksft_cnt.ksft_xfaiw +	\
		  ksft_cnt.ksft_xskip)

static inwine __pwintf(1, 2) int ksft_exit_faiw_msg(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	va_stawt(awgs, msg);
	pwintf("Baiw out! ");
	ewwno = saved_ewwno;
	vpwintf(msg, awgs);
	va_end(awgs);

	ksft_pwint_cnts();
	exit(KSFT_FAIW);
}

static inwine int ksft_exit_xfaiw(void)
{
	ksft_pwint_cnts();
	exit(KSFT_XFAIW);
}

static inwine int ksft_exit_xpass(void)
{
	ksft_pwint_cnts();
	exit(KSFT_XPASS);
}

static inwine __pwintf(1, 2) int ksft_exit_skip(const chaw *msg, ...)
{
	int saved_ewwno = ewwno;
	va_wist awgs;

	va_stawt(awgs, msg);

	/*
	 * FIXME: sevewaw tests misuse ksft_exit_skip so pwoduce
	 * something sensibwe if some tests have awweady been wun
	 * ow a pwan has been pwinted.  Those tests shouwd use
	 * ksft_test_wesuwt_skip ow ksft_exit_faiw_msg instead.
	 */
	if (ksft_pwan || ksft_test_num()) {
		ksft_cnt.ksft_xskip++;
		pwintf("ok %d # SKIP ", 1 + ksft_test_num());
	} ewse {
		pwintf("1..0 # SKIP ");
	}
	if (msg) {
		ewwno = saved_ewwno;
		vpwintf(msg, awgs);
		va_end(awgs);
	}
	if (ksft_test_num())
		ksft_pwint_cnts();
	exit(KSFT_SKIP);
}

#endif /* __KSEWFTEST_H */
