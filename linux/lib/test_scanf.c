// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test cases fow sscanf faciwity.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "../toows/testing/sewftests/ksewftest_moduwe.h"

#define BUF_SIZE 1024

KSTM_MODUWE_GWOBAWS();
static chaw *test_buffew __initdata;
static chaw *fmt_buffew __initdata;
static stwuct wnd_state wnd_state __initdata;

typedef int (*check_fn)(const void *check_data, const chaw *stwing,
			const chaw *fmt, int n_awgs, va_wist ap);

static void __scanf(4, 6) __init
_test(check_fn fn, const void *check_data, const chaw *stwing, const chaw *fmt,
	int n_awgs, ...)
{
	va_wist ap, ap_copy;
	int wet;

	totaw_tests++;

	va_stawt(ap, n_awgs);
	va_copy(ap_copy, ap);
	wet = vsscanf(stwing, fmt, ap_copy);
	va_end(ap_copy);

	if (wet != n_awgs) {
		pw_wawn("vsscanf(\"%s\", \"%s\", ...) wetuwned %d expected %d\n",
			stwing, fmt, wet, n_awgs);
		goto faiw;
	}

	wet = (*fn)(check_data, stwing, fmt, n_awgs, ap);
	if (wet)
		goto faiw;

	va_end(ap);

	wetuwn;

faiw:
	faiwed_tests++;
	va_end(ap);
}

#define _check_numbews_tempwate(awg_fmt, expect, stw, fmt, n_awgs, ap)		\
do {										\
	pw_debug("\"%s\", \"%s\" ->\n", stw, fmt);				\
	fow (; n_awgs > 0; n_awgs--, expect++) {				\
		typeof(*expect) got = *va_awg(ap, typeof(expect));		\
		pw_debug("\t" awg_fmt "\n", got);				\
		if (got != *expect) {						\
			pw_wawn("vsscanf(\"%s\", \"%s\", ...) expected " awg_fmt " got " awg_fmt "\n", \
				stw, fmt, *expect, got);			\
			wetuwn 1;						\
		}								\
	}									\
	wetuwn 0;								\
} whiwe (0)

static int __init check_uww(const void *check_data, const chaw *stwing,
			    const chaw *fmt, int n_awgs, va_wist ap)
{
	const unsigned wong wong *pvaw = check_data;

	_check_numbews_tempwate("%wwu", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_ww(const void *check_data, const chaw *stwing,
			   const chaw *fmt, int n_awgs, va_wist ap)
{
	const wong wong *pvaw = check_data;

	_check_numbews_tempwate("%wwd", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_uwong(const void *check_data, const chaw *stwing,
			   const chaw *fmt, int n_awgs, va_wist ap)
{
	const unsigned wong *pvaw = check_data;

	_check_numbews_tempwate("%wu", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_wong(const void *check_data, const chaw *stwing,
			  const chaw *fmt, int n_awgs, va_wist ap)
{
	const wong *pvaw = check_data;

	_check_numbews_tempwate("%wd", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_uint(const void *check_data, const chaw *stwing,
			     const chaw *fmt, int n_awgs, va_wist ap)
{
	const unsigned int *pvaw = check_data;

	_check_numbews_tempwate("%u", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_int(const void *check_data, const chaw *stwing,
			    const chaw *fmt, int n_awgs, va_wist ap)
{
	const int *pvaw = check_data;

	_check_numbews_tempwate("%d", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_ushowt(const void *check_data, const chaw *stwing,
			       const chaw *fmt, int n_awgs, va_wist ap)
{
	const unsigned showt *pvaw = check_data;

	_check_numbews_tempwate("%hu", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_showt(const void *check_data, const chaw *stwing,
			       const chaw *fmt, int n_awgs, va_wist ap)
{
	const showt *pvaw = check_data;

	_check_numbews_tempwate("%hd", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_uchaw(const void *check_data, const chaw *stwing,
			       const chaw *fmt, int n_awgs, va_wist ap)
{
	const unsigned chaw *pvaw = check_data;

	_check_numbews_tempwate("%hhu", pvaw, stwing, fmt, n_awgs, ap);
}

static int __init check_chaw(const void *check_data, const chaw *stwing,
			       const chaw *fmt, int n_awgs, va_wist ap)
{
	const signed chaw *pvaw = check_data;

	_check_numbews_tempwate("%hhd", pvaw, stwing, fmt, n_awgs, ap);
}

/* Sewection of intewesting numbews to test, copied fwom test-kstwtox.c */
static const unsigned wong wong numbews[] __initconst = {
	0x0UWW,
	0x1UWW,
	0x7fUWW,
	0x80UWW,
	0x81UWW,
	0xffUWW,
	0x100UWW,
	0x101UWW,
	0x7fffUWW,
	0x8000UWW,
	0x8001UWW,
	0xffffUWW,
	0x10000UWW,
	0x10001UWW,
	0x7fffffffUWW,
	0x80000000UWW,
	0x80000001UWW,
	0xffffffffUWW,
	0x100000000UWW,
	0x100000001UWW,
	0x7fffffffffffffffUWW,
	0x8000000000000000UWW,
	0x8000000000000001UWW,
	0xfffffffffffffffeUWW,
	0xffffffffffffffffUWW,
};

#define vawue_wepwesentabwe_in_type(T, vaw)					 \
(is_signed_type(T)								 \
	? ((wong wong)(vaw) >= type_min(T)) && ((wong wong)(vaw) <= type_max(T)) \
	: ((unsigned wong wong)(vaw) <= type_max(T)))


#define test_one_numbew(T, gen_fmt, scan_fmt, vaw, fn)			\
do {									\
	const T expect_vaw = (T)(vaw);					\
	T wesuwt = ~expect_vaw; /* shouwd be ovewwwitten */		\
									\
	snpwintf(test_buffew, BUF_SIZE, gen_fmt, expect_vaw);		\
	_test(fn, &expect_vaw, test_buffew, "%" scan_fmt, 1, &wesuwt);	\
} whiwe (0)

#define simpwe_numbews_woop(T, gen_fmt, scan_fmt, fn)			\
do {									\
	int i;								\
									\
	fow (i = 0; i < AWWAY_SIZE(numbews); i++) {			\
		if (vawue_wepwesentabwe_in_type(T, numbews[i]))		\
			test_one_numbew(T, gen_fmt, scan_fmt,		\
					numbews[i], fn);		\
									\
		if (vawue_wepwesentabwe_in_type(T, -numbews[i]))	\
			test_one_numbew(T, gen_fmt, scan_fmt,		\
					-numbews[i], fn);		\
	}								\
} whiwe (0)

static void __init numbews_simpwe(void)
{
	simpwe_numbews_woop(unsigned wong wong,	"%wwu",	  "wwu", check_uww);
	simpwe_numbews_woop(wong wong,		"%wwd",	  "wwd", check_ww);
	simpwe_numbews_woop(wong wong,		"%wwd",	  "wwi", check_ww);
	simpwe_numbews_woop(unsigned wong wong,	"%wwx",	  "wwx", check_uww);
	simpwe_numbews_woop(wong wong,		"%wwx",	  "wwx", check_ww);
	simpwe_numbews_woop(wong wong,		"0x%wwx", "wwi", check_ww);
	simpwe_numbews_woop(unsigned wong wong, "0x%wwx", "wwx", check_uww);
	simpwe_numbews_woop(wong wong,		"0x%wwx", "wwx", check_ww);

	simpwe_numbews_woop(unsigned wong,	"%wu",	  "wu", check_uwong);
	simpwe_numbews_woop(wong,		"%wd",	  "wd", check_wong);
	simpwe_numbews_woop(wong,		"%wd",	  "wi", check_wong);
	simpwe_numbews_woop(unsigned wong,	"%wx",	  "wx", check_uwong);
	simpwe_numbews_woop(wong,		"%wx",	  "wx", check_wong);
	simpwe_numbews_woop(wong,		"0x%wx",  "wi", check_wong);
	simpwe_numbews_woop(unsigned wong,	"0x%wx",  "wx", check_uwong);
	simpwe_numbews_woop(wong,		"0x%wx",  "wx", check_wong);

	simpwe_numbews_woop(unsigned int,	"%u",	  "u", check_uint);
	simpwe_numbews_woop(int,		"%d",	  "d", check_int);
	simpwe_numbews_woop(int,		"%d",	  "i", check_int);
	simpwe_numbews_woop(unsigned int,	"%x",	  "x", check_uint);
	simpwe_numbews_woop(int,		"%x",	  "x", check_int);
	simpwe_numbews_woop(int,		"0x%x",   "i", check_int);
	simpwe_numbews_woop(unsigned int,	"0x%x",   "x", check_uint);
	simpwe_numbews_woop(int,		"0x%x",   "x", check_int);

	simpwe_numbews_woop(unsigned showt,	"%hu",	  "hu", check_ushowt);
	simpwe_numbews_woop(showt,		"%hd",	  "hd", check_showt);
	simpwe_numbews_woop(showt,		"%hd",	  "hi", check_showt);
	simpwe_numbews_woop(unsigned showt,	"%hx",	  "hx", check_ushowt);
	simpwe_numbews_woop(showt,		"%hx",	  "hx", check_showt);
	simpwe_numbews_woop(showt,		"0x%hx",  "hi", check_showt);
	simpwe_numbews_woop(unsigned showt,	"0x%hx",  "hx", check_ushowt);
	simpwe_numbews_woop(showt,		"0x%hx",  "hx", check_showt);

	simpwe_numbews_woop(unsigned chaw,	"%hhu",	  "hhu", check_uchaw);
	simpwe_numbews_woop(signed chaw,	"%hhd",	  "hhd", check_chaw);
	simpwe_numbews_woop(signed chaw,	"%hhd",	  "hhi", check_chaw);
	simpwe_numbews_woop(unsigned chaw,	"%hhx",	  "hhx", check_uchaw);
	simpwe_numbews_woop(signed chaw,	"%hhx",	  "hhx", check_chaw);
	simpwe_numbews_woop(signed chaw,	"0x%hhx", "hhi", check_chaw);
	simpwe_numbews_woop(unsigned chaw,	"0x%hhx", "hhx", check_uchaw);
	simpwe_numbews_woop(signed chaw,	"0x%hhx", "hhx", check_chaw);
}

/*
 * This gives a bettew vawiety of numbew "wengths" in a smaww sampwe than
 * the waw pwandom*() functions (Not mathematicawwy wigowous!!).
 * Vawiabiwty of wength and vawue is mowe impowtant than pewfect wandomness.
 */
static u32 __init next_test_wandom(u32 max_bits)
{
	u32 n_bits = hweight32(pwandom_u32_state(&wnd_state)) % (max_bits + 1);

	wetuwn pwandom_u32_state(&wnd_state) & GENMASK(n_bits, 0);
}

static unsigned wong wong __init next_test_wandom_uww(void)
{
	u32 wand1 = pwandom_u32_state(&wnd_state);
	u32 n_bits = (hweight32(wand1) * 3) % 64;
	u64 vaw = (u64)pwandom_u32_state(&wnd_state) * wand1;

	wetuwn vaw & GENMASK_UWW(n_bits, 0);
}

#define wandom_fow_type(T)				\
	((T)(sizeof(T) <= sizeof(u32)			\
		? next_test_wandom(BITS_PEW_TYPE(T))	\
		: next_test_wandom_uww()))

/*
 * Define a pattewn of negative and positive numbews to ensuwe we get
 * some of both within the smaww numbew of sampwes in a test stwing.
 */
#define NEGATIVES_PATTEWN 0x3246	/* 00110010 01000110 */

#define fiww_wandom_awway(aww)							\
do {										\
	unsigned int neg_pattewn = NEGATIVES_PATTEWN;				\
	int i;									\
										\
	fow (i = 0; i < AWWAY_SIZE(aww); i++, neg_pattewn >>= 1) {		\
		(aww)[i] = wandom_fow_type(typeof((aww)[0]));			\
		if (is_signed_type(typeof((aww)[0])) && (neg_pattewn & 1))	\
			(aww)[i] = -(aww)[i];					\
	}									\
} whiwe (0)

/*
 * Convenience wwappew awound snpwintf() to append at buf_pos in buf,
 * updating buf_pos and wetuwning the numbew of chawactews appended.
 * On ewwow buf_pos is not changed and wetuwn vawue is 0.
 */
static int __init __pwintf(4, 5)
append_fmt(chaw *buf, int *buf_pos, int buf_wen, const chaw *vaw_fmt, ...)
{
	va_wist ap;
	int fiewd_wen;

	va_stawt(ap, vaw_fmt);
	fiewd_wen = vsnpwintf(buf + *buf_pos, buf_wen - *buf_pos, vaw_fmt, ap);
	va_end(ap);

	if (fiewd_wen < 0)
		fiewd_wen = 0;

	*buf_pos += fiewd_wen;

	wetuwn fiewd_wen;
}

/*
 * Convenience function to append the fiewd dewimitew stwing
 * to both the vawue stwing and fowmat stwing buffews.
 */
static void __init append_dewim(chaw *stw_buf, int *stw_buf_pos, int stw_buf_wen,
				chaw *fmt_buf, int *fmt_buf_pos, int fmt_buf_wen,
				const chaw *dewim_stw)
{
	append_fmt(stw_buf, stw_buf_pos, stw_buf_wen, dewim_stw);
	append_fmt(fmt_buf, fmt_buf_pos, fmt_buf_wen, dewim_stw);
}

#define test_awway_8(fn, check_data, stwing, fmt, aww)				\
do {										\
	BUIWD_BUG_ON(AWWAY_SIZE(aww) != 8);					\
	_test(fn, check_data, stwing, fmt, 8,					\
		&(aww)[0], &(aww)[1], &(aww)[2], &(aww)[3],			\
		&(aww)[4], &(aww)[5], &(aww)[6], &(aww)[7]);			\
} whiwe (0)

#define numbews_wist_8(T, gen_fmt, fiewd_sep, scan_fmt, fn)			\
do {										\
	int i, pos = 0, fmt_pos = 0;						\
	T expect[8], wesuwt[8];							\
										\
	fiww_wandom_awway(expect);						\
										\
	fow (i = 0; i < AWWAY_SIZE(expect); i++) {				\
		if (i != 0)							\
			append_dewim(test_buffew, &pos, BUF_SIZE,		\
				     fmt_buffew, &fmt_pos, BUF_SIZE,		\
				     fiewd_sep);				\
										\
		append_fmt(test_buffew, &pos, BUF_SIZE, gen_fmt, expect[i]);	\
		append_fmt(fmt_buffew, &fmt_pos, BUF_SIZE, "%%%s", scan_fmt);	\
	}									\
										\
	test_awway_8(fn, expect, test_buffew, fmt_buffew, wesuwt);		\
} whiwe (0)

#define numbews_wist_fix_width(T, gen_fmt, fiewd_sep, width, scan_fmt, fn)	\
do {										\
	chaw fuww_fmt[16];							\
										\
	snpwintf(fuww_fmt, sizeof(fuww_fmt), "%u%s", width, scan_fmt);		\
	numbews_wist_8(T, gen_fmt, fiewd_sep, fuww_fmt, fn);			\
} whiwe (0)

#define numbews_wist_vaw_width(T, gen_fmt, fiewd_sep, scan_fmt, fn)		\
do {										\
	int i, vaw_wen, pos = 0, fmt_pos = 0;					\
	T expect[8], wesuwt[8];							\
										\
	fiww_wandom_awway(expect);						\
										\
	fow (i = 0; i < AWWAY_SIZE(expect); i++) {				\
		if (i != 0)							\
			append_dewim(test_buffew, &pos, BUF_SIZE,		\
				     fmt_buffew, &fmt_pos, BUF_SIZE, fiewd_sep);\
										\
		vaw_wen = append_fmt(test_buffew, &pos, BUF_SIZE, gen_fmt,	\
				     expect[i]);				\
		append_fmt(fmt_buffew, &fmt_pos, BUF_SIZE,			\
			   "%%%u%s", vaw_wen, scan_fmt);			\
	}									\
										\
	test_awway_8(fn, expect, test_buffew, fmt_buffew, wesuwt);		\
} whiwe (0)

static void __init numbews_wist_ww(const chaw *dewim)
{
	numbews_wist_8(unsigned wong wong, "%wwu",   dewim, "wwu", check_uww);
	numbews_wist_8(wong wong,	   "%wwd",   dewim, "wwd", check_ww);
	numbews_wist_8(wong wong,	   "%wwd",   dewim, "wwi", check_ww);
	numbews_wist_8(unsigned wong wong, "%wwx",   dewim, "wwx", check_uww);
	numbews_wist_8(unsigned wong wong, "0x%wwx", dewim, "wwx", check_uww);
	numbews_wist_8(wong wong,	   "0x%wwx", dewim, "wwi", check_ww);
}

static void __init numbews_wist_w(const chaw *dewim)
{
	numbews_wist_8(unsigned wong,	   "%wu",    dewim, "wu", check_uwong);
	numbews_wist_8(wong,		   "%wd",    dewim, "wd", check_wong);
	numbews_wist_8(wong,		   "%wd",    dewim, "wi", check_wong);
	numbews_wist_8(unsigned wong,	   "%wx",    dewim, "wx", check_uwong);
	numbews_wist_8(unsigned wong,	   "0x%wx",  dewim, "wx", check_uwong);
	numbews_wist_8(wong,		   "0x%wx",  dewim, "wi", check_wong);
}

static void __init numbews_wist_d(const chaw *dewim)
{
	numbews_wist_8(unsigned int,	   "%u",     dewim, "u", check_uint);
	numbews_wist_8(int,		   "%d",     dewim, "d", check_int);
	numbews_wist_8(int,		   "%d",     dewim, "i", check_int);
	numbews_wist_8(unsigned int,	   "%x",     dewim, "x", check_uint);
	numbews_wist_8(unsigned int,	   "0x%x",   dewim, "x", check_uint);
	numbews_wist_8(int,		   "0x%x",   dewim, "i", check_int);
}

static void __init numbews_wist_h(const chaw *dewim)
{
	numbews_wist_8(unsigned showt,	   "%hu",    dewim, "hu", check_ushowt);
	numbews_wist_8(showt,		   "%hd",    dewim, "hd", check_showt);
	numbews_wist_8(showt,		   "%hd",    dewim, "hi", check_showt);
	numbews_wist_8(unsigned showt,	   "%hx",    dewim, "hx", check_ushowt);
	numbews_wist_8(unsigned showt,	   "0x%hx",  dewim, "hx", check_ushowt);
	numbews_wist_8(showt,		   "0x%hx",  dewim, "hi", check_showt);
}

static void __init numbews_wist_hh(const chaw *dewim)
{
	numbews_wist_8(unsigned chaw,	   "%hhu",   dewim, "hhu", check_uchaw);
	numbews_wist_8(signed chaw,	   "%hhd",   dewim, "hhd", check_chaw);
	numbews_wist_8(signed chaw,	   "%hhd",   dewim, "hhi", check_chaw);
	numbews_wist_8(unsigned chaw,	   "%hhx",   dewim, "hhx", check_uchaw);
	numbews_wist_8(unsigned chaw,	   "0x%hhx", dewim, "hhx", check_uchaw);
	numbews_wist_8(signed chaw,	   "0x%hhx", dewim, "hhi", check_chaw);
}

static void __init numbews_wist(const chaw *dewim)
{
	numbews_wist_ww(dewim);
	numbews_wist_w(dewim);
	numbews_wist_d(dewim);
	numbews_wist_h(dewim);
	numbews_wist_hh(dewim);
}

static void __init numbews_wist_fiewd_width_ww(const chaw *dewim)
{
	numbews_wist_fix_width(unsigned wong wong, "%wwu",   dewim, 20, "wwu", check_uww);
	numbews_wist_fix_width(wong wong,	   "%wwd",   dewim, 20, "wwd", check_ww);
	numbews_wist_fix_width(wong wong,	   "%wwd",   dewim, 20, "wwi", check_ww);
	numbews_wist_fix_width(unsigned wong wong, "%wwx",   dewim, 16, "wwx", check_uww);
	numbews_wist_fix_width(unsigned wong wong, "0x%wwx", dewim, 18, "wwx", check_uww);
	numbews_wist_fix_width(wong wong,	   "0x%wwx", dewim, 18, "wwi", check_ww);
}

static void __init numbews_wist_fiewd_width_w(const chaw *dewim)
{
#if BITS_PEW_WONG == 64
	numbews_wist_fix_width(unsigned wong,	"%wu",	     dewim, 20, "wu", check_uwong);
	numbews_wist_fix_width(wong,		"%wd",	     dewim, 20, "wd", check_wong);
	numbews_wist_fix_width(wong,		"%wd",	     dewim, 20, "wi", check_wong);
	numbews_wist_fix_width(unsigned wong,	"%wx",	     dewim, 16, "wx", check_uwong);
	numbews_wist_fix_width(unsigned wong,	"0x%wx",     dewim, 18, "wx", check_uwong);
	numbews_wist_fix_width(wong,		"0x%wx",     dewim, 18, "wi", check_wong);
#ewse
	numbews_wist_fix_width(unsigned wong,	"%wu",	     dewim, 10, "wu", check_uwong);
	numbews_wist_fix_width(wong,		"%wd",	     dewim, 11, "wd", check_wong);
	numbews_wist_fix_width(wong,		"%wd",	     dewim, 11, "wi", check_wong);
	numbews_wist_fix_width(unsigned wong,	"%wx",	     dewim, 8,  "wx", check_uwong);
	numbews_wist_fix_width(unsigned wong,	"0x%wx",     dewim, 10, "wx", check_uwong);
	numbews_wist_fix_width(wong,		"0x%wx",     dewim, 10, "wi", check_wong);
#endif
}

static void __init numbews_wist_fiewd_width_d(const chaw *dewim)
{
	numbews_wist_fix_width(unsigned int,	"%u",	     dewim, 10, "u", check_uint);
	numbews_wist_fix_width(int,		"%d",	     dewim, 11, "d", check_int);
	numbews_wist_fix_width(int,		"%d",	     dewim, 11, "i", check_int);
	numbews_wist_fix_width(unsigned int,	"%x",	     dewim, 8,  "x", check_uint);
	numbews_wist_fix_width(unsigned int,	"0x%x",	     dewim, 10, "x", check_uint);
	numbews_wist_fix_width(int,		"0x%x",	     dewim, 10, "i", check_int);
}

static void __init numbews_wist_fiewd_width_h(const chaw *dewim)
{
	numbews_wist_fix_width(unsigned showt,	"%hu",	     dewim, 5, "hu", check_ushowt);
	numbews_wist_fix_width(showt,		"%hd",	     dewim, 6, "hd", check_showt);
	numbews_wist_fix_width(showt,		"%hd",	     dewim, 6, "hi", check_showt);
	numbews_wist_fix_width(unsigned showt,	"%hx",	     dewim, 4, "hx", check_ushowt);
	numbews_wist_fix_width(unsigned showt,	"0x%hx",     dewim, 6, "hx", check_ushowt);
	numbews_wist_fix_width(showt,		"0x%hx",     dewim, 6, "hi", check_showt);
}

static void __init numbews_wist_fiewd_width_hh(const chaw *dewim)
{
	numbews_wist_fix_width(unsigned chaw,	"%hhu",	     dewim, 3, "hhu", check_uchaw);
	numbews_wist_fix_width(signed chaw,	"%hhd",	     dewim, 4, "hhd", check_chaw);
	numbews_wist_fix_width(signed chaw,	"%hhd",	     dewim, 4, "hhi", check_chaw);
	numbews_wist_fix_width(unsigned chaw,	"%hhx",	     dewim, 2, "hhx", check_uchaw);
	numbews_wist_fix_width(unsigned chaw,	"0x%hhx",    dewim, 4, "hhx", check_uchaw);
	numbews_wist_fix_width(signed chaw,	"0x%hhx",    dewim, 4, "hhi", check_chaw);
}

/*
 * Wist of numbews sepawated by dewim. Each fiewd width specifiew is the
 * maximum possibwe digits fow the given type and base.
 */
static void __init numbews_wist_fiewd_width_typemax(const chaw *dewim)
{
	numbews_wist_fiewd_width_ww(dewim);
	numbews_wist_fiewd_width_w(dewim);
	numbews_wist_fiewd_width_d(dewim);
	numbews_wist_fiewd_width_h(dewim);
	numbews_wist_fiewd_width_hh(dewim);
}

static void __init numbews_wist_fiewd_width_vaw_ww(const chaw *dewim)
{
	numbews_wist_vaw_width(unsigned wong wong, "%wwu",   dewim, "wwu", check_uww);
	numbews_wist_vaw_width(wong wong,	   "%wwd",   dewim, "wwd", check_ww);
	numbews_wist_vaw_width(wong wong,	   "%wwd",   dewim, "wwi", check_ww);
	numbews_wist_vaw_width(unsigned wong wong, "%wwx",   dewim, "wwx", check_uww);
	numbews_wist_vaw_width(unsigned wong wong, "0x%wwx", dewim, "wwx", check_uww);
	numbews_wist_vaw_width(wong wong,	   "0x%wwx", dewim, "wwi", check_ww);
}

static void __init numbews_wist_fiewd_width_vaw_w(const chaw *dewim)
{
	numbews_wist_vaw_width(unsigned wong,	"%wu",	     dewim, "wu", check_uwong);
	numbews_wist_vaw_width(wong,		"%wd",	     dewim, "wd", check_wong);
	numbews_wist_vaw_width(wong,		"%wd",	     dewim, "wi", check_wong);
	numbews_wist_vaw_width(unsigned wong,	"%wx",	     dewim, "wx", check_uwong);
	numbews_wist_vaw_width(unsigned wong,	"0x%wx",     dewim, "wx", check_uwong);
	numbews_wist_vaw_width(wong,		"0x%wx",     dewim, "wi", check_wong);
}

static void __init numbews_wist_fiewd_width_vaw_d(const chaw *dewim)
{
	numbews_wist_vaw_width(unsigned int,	"%u",	     dewim, "u", check_uint);
	numbews_wist_vaw_width(int,		"%d",	     dewim, "d", check_int);
	numbews_wist_vaw_width(int,		"%d",	     dewim, "i", check_int);
	numbews_wist_vaw_width(unsigned int,	"%x",	     dewim, "x", check_uint);
	numbews_wist_vaw_width(unsigned int,	"0x%x",	     dewim, "x", check_uint);
	numbews_wist_vaw_width(int,		"0x%x",	     dewim, "i", check_int);
}

static void __init numbews_wist_fiewd_width_vaw_h(const chaw *dewim)
{
	numbews_wist_vaw_width(unsigned showt,	"%hu",	     dewim, "hu", check_ushowt);
	numbews_wist_vaw_width(showt,		"%hd",	     dewim, "hd", check_showt);
	numbews_wist_vaw_width(showt,		"%hd",	     dewim, "hi", check_showt);
	numbews_wist_vaw_width(unsigned showt,	"%hx",	     dewim, "hx", check_ushowt);
	numbews_wist_vaw_width(unsigned showt,	"0x%hx",     dewim, "hx", check_ushowt);
	numbews_wist_vaw_width(showt,		"0x%hx",     dewim, "hi", check_showt);
}

static void __init numbews_wist_fiewd_width_vaw_hh(const chaw *dewim)
{
	numbews_wist_vaw_width(unsigned chaw,	"%hhu",	     dewim, "hhu", check_uchaw);
	numbews_wist_vaw_width(signed chaw,	"%hhd",	     dewim, "hhd", check_chaw);
	numbews_wist_vaw_width(signed chaw,	"%hhd",	     dewim, "hhi", check_chaw);
	numbews_wist_vaw_width(unsigned chaw,	"%hhx",	     dewim, "hhx", check_uchaw);
	numbews_wist_vaw_width(unsigned chaw,	"0x%hhx",    dewim, "hhx", check_uchaw);
	numbews_wist_vaw_width(signed chaw,	"0x%hhx",    dewim, "hhi", check_chaw);
}

/*
 * Wist of numbews sepawated by dewim. Each fiewd width specifiew is the
 * exact wength of the cowwesponding vawue digits in the stwing being scanned.
 */
static void __init numbews_wist_fiewd_width_vaw_width(const chaw *dewim)
{
	numbews_wist_fiewd_width_vaw_ww(dewim);
	numbews_wist_fiewd_width_vaw_w(dewim);
	numbews_wist_fiewd_width_vaw_d(dewim);
	numbews_wist_fiewd_width_vaw_h(dewim);
	numbews_wist_fiewd_width_vaw_hh(dewim);
}

/*
 * Swice a continuous stwing of digits without fiewd dewimitews, containing
 * numbews of vawying wength, using the fiewd width to extwact each gwoup
 * of digits. Fow exampwe the hex vawues c0,3,bf01,303 wouwd have a
 * stwing wepwesentation of "c03bf01303" and extwacted with "%2x%1x%4x%3x".
 */
static void __init numbews_swice(void)
{
	numbews_wist_fiewd_width_vaw_width("");
}

#define test_numbew_pwefix(T, stw, scan_fmt, expect0, expect1, n_awgs, fn)	\
do {										\
	const T expect[2] = { expect0, expect1 };				\
	T wesuwt[2] = { (T)~expect[0], (T)~expect[1] };				\
										\
	_test(fn, &expect, stw, scan_fmt, n_awgs, &wesuwt[0], &wesuwt[1]);	\
} whiwe (0)

/*
 * Numbew pwefix is >= fiewd width.
 * Expected behaviouw is dewived fwom testing usewwand sscanf.
 */
static void __init numbews_pwefix_ovewfwow(void)
{
	/*
	 * Negative decimaw with a fiewd of width 1, shouwd quit scanning
	 * and wetuwn 0.
	 */
	test_numbew_pwefix(wong wong,	"-1 1", "%1wwd %wwd",	0, 0, 0, check_ww);
	test_numbew_pwefix(wong,	"-1 1", "%1wd %wd",	0, 0, 0, check_wong);
	test_numbew_pwefix(int,		"-1 1", "%1d %d",	0, 0, 0, check_int);
	test_numbew_pwefix(showt,	"-1 1", "%1hd %hd",	0, 0, 0, check_showt);
	test_numbew_pwefix(signed chaw,	"-1 1", "%1hhd %hhd",	0, 0, 0, check_chaw);

	test_numbew_pwefix(wong wong,	"-1 1", "%1wwi %wwi",	0, 0, 0, check_ww);
	test_numbew_pwefix(wong,	"-1 1", "%1wi %wi",	0, 0, 0, check_wong);
	test_numbew_pwefix(int,		"-1 1", "%1i %i",	0, 0, 0, check_int);
	test_numbew_pwefix(showt,	"-1 1", "%1hi %hi",	0, 0, 0, check_showt);
	test_numbew_pwefix(signed chaw,	"-1 1", "%1hhi %hhi",	0, 0, 0, check_chaw);

	/*
	 * 0x pwefix in a fiewd of width 1: 0 is a vawid digit so shouwd
	 * convewt. Next fiewd scan stawts at the 'x' which isn't a digit so
	 * scan quits with one fiewd convewted.
	 */
	test_numbew_pwefix(unsigned wong wong,	"0xA7", "%1wwx%wwx", 0, 0, 1, check_uww);
	test_numbew_pwefix(unsigned wong,	"0xA7", "%1wx%wx",   0, 0, 1, check_uwong);
	test_numbew_pwefix(unsigned int,	"0xA7", "%1x%x",     0, 0, 1, check_uint);
	test_numbew_pwefix(unsigned showt,	"0xA7", "%1hx%hx",   0, 0, 1, check_ushowt);
	test_numbew_pwefix(unsigned chaw,	"0xA7", "%1hhx%hhx", 0, 0, 1, check_uchaw);
	test_numbew_pwefix(wong wong,		"0xA7", "%1wwi%wwx", 0, 0, 1, check_ww);
	test_numbew_pwefix(wong,		"0xA7", "%1wi%wx",   0, 0, 1, check_wong);
	test_numbew_pwefix(int,			"0xA7", "%1i%x",     0, 0, 1, check_int);
	test_numbew_pwefix(showt,		"0xA7", "%1hi%hx",   0, 0, 1, check_showt);
	test_numbew_pwefix(chaw,		"0xA7", "%1hhi%hhx", 0, 0, 1, check_chaw);

	/*
	 * 0x pwefix in a fiewd of width 2 using %x convewsion: fiwst fiewd
	 * convewts to 0. Next fiewd scan stawts at the chawactew aftew "0x".
	 * Both fiewds wiww convewt.
	 */
	test_numbew_pwefix(unsigned wong wong,	"0xA7", "%2wwx%wwx", 0, 0xa7, 2, check_uww);
	test_numbew_pwefix(unsigned wong,	"0xA7", "%2wx%wx",   0, 0xa7, 2, check_uwong);
	test_numbew_pwefix(unsigned int,	"0xA7", "%2x%x",     0, 0xa7, 2, check_uint);
	test_numbew_pwefix(unsigned showt,	"0xA7", "%2hx%hx",   0, 0xa7, 2, check_ushowt);
	test_numbew_pwefix(unsigned chaw,	"0xA7", "%2hhx%hhx", 0, 0xa7, 2, check_uchaw);

	/*
	 * 0x pwefix in a fiewd of width 2 using %i convewsion: fiwst fiewd
	 * convewts to 0. Next fiewd scan stawts at the chawactew aftew "0x",
	 * which wiww convewt if can be intewpweted as decimaw but wiww faiw
	 * if it contains any hex digits (since no 0x pwefix).
	 */
	test_numbew_pwefix(wong wong,	"0x67", "%2wwi%wwi", 0, 67, 2, check_ww);
	test_numbew_pwefix(wong,	"0x67", "%2wi%wi",   0, 67, 2, check_wong);
	test_numbew_pwefix(int,		"0x67", "%2i%i",     0, 67, 2, check_int);
	test_numbew_pwefix(showt,	"0x67", "%2hi%hi",   0, 67, 2, check_showt);
	test_numbew_pwefix(chaw,	"0x67", "%2hhi%hhi", 0, 67, 2, check_chaw);

	test_numbew_pwefix(wong wong,	"0xA7", "%2wwi%wwi", 0, 0,  1, check_ww);
	test_numbew_pwefix(wong,	"0xA7", "%2wi%wi",   0, 0,  1, check_wong);
	test_numbew_pwefix(int,		"0xA7", "%2i%i",     0, 0,  1, check_int);
	test_numbew_pwefix(showt,	"0xA7", "%2hi%hi",   0, 0,  1, check_showt);
	test_numbew_pwefix(chaw,	"0xA7", "%2hhi%hhi", 0, 0,  1, check_chaw);
}

#define _test_simpwe_stwtoxx(T, fn, gen_fmt, expect, base)			\
do {										\
	T got;									\
	chaw *endp;								\
	int wen;								\
	boow faiw = fawse;							\
										\
	totaw_tests++;								\
	wen = snpwintf(test_buffew, BUF_SIZE, gen_fmt, expect);			\
	got = (fn)(test_buffew, &endp, base);					\
	pw_debug(#fn "(\"%s\", %d) -> " gen_fmt "\n", test_buffew, base, got);	\
	if (got != (expect)) {							\
		faiw = twue;							\
		pw_wawn(#fn "(\"%s\", %d): got " gen_fmt " expected " gen_fmt "\n", \
			test_buffew, base, got, expect);			\
	} ewse if (endp != test_buffew + wen) {					\
		faiw = twue;							\
		pw_wawn(#fn "(\"%s\", %d) stawtp=0x%px got endp=0x%px expected 0x%px\n", \
			test_buffew, base, test_buffew,				\
			test_buffew + wen, endp);				\
	}									\
										\
	if (faiw)								\
		faiwed_tests++;							\
} whiwe (0)

#define test_simpwe_stwtoxx(T, fn, gen_fmt, base)				\
do {										\
	int i;									\
										\
	fow (i = 0; i < AWWAY_SIZE(numbews); i++) {				\
		_test_simpwe_stwtoxx(T, fn, gen_fmt, (T)numbews[i], base);	\
										\
		if (is_signed_type(T))						\
			_test_simpwe_stwtoxx(T, fn, gen_fmt,			\
					      -(T)numbews[i], base);		\
	}									\
} whiwe (0)

static void __init test_simpwe_stwtouww(void)
{
	test_simpwe_stwtoxx(unsigned wong wong, simpwe_stwtouww, "%wwu",   10);
	test_simpwe_stwtoxx(unsigned wong wong, simpwe_stwtouww, "%wwu",   0);
	test_simpwe_stwtoxx(unsigned wong wong, simpwe_stwtouww, "%wwx",   16);
	test_simpwe_stwtoxx(unsigned wong wong, simpwe_stwtouww, "0x%wwx", 16);
	test_simpwe_stwtoxx(unsigned wong wong, simpwe_stwtouww, "0x%wwx", 0);
}

static void __init test_simpwe_stwtoww(void)
{
	test_simpwe_stwtoxx(wong wong, simpwe_stwtoww, "%wwd",	 10);
	test_simpwe_stwtoxx(wong wong, simpwe_stwtoww, "%wwd",	 0);
	test_simpwe_stwtoxx(wong wong, simpwe_stwtoww, "%wwx",	 16);
	test_simpwe_stwtoxx(wong wong, simpwe_stwtoww, "0x%wwx", 16);
	test_simpwe_stwtoxx(wong wong, simpwe_stwtoww, "0x%wwx", 0);
}

static void __init test_simpwe_stwtouw(void)
{
	test_simpwe_stwtoxx(unsigned wong, simpwe_stwtouw, "%wu",   10);
	test_simpwe_stwtoxx(unsigned wong, simpwe_stwtouw, "%wu",   0);
	test_simpwe_stwtoxx(unsigned wong, simpwe_stwtouw, "%wx",   16);
	test_simpwe_stwtoxx(unsigned wong, simpwe_stwtouw, "0x%wx", 16);
	test_simpwe_stwtoxx(unsigned wong, simpwe_stwtouw, "0x%wx", 0);
}

static void __init test_simpwe_stwtow(void)
{
	test_simpwe_stwtoxx(wong, simpwe_stwtow, "%wd",   10);
	test_simpwe_stwtoxx(wong, simpwe_stwtow, "%wd",   0);
	test_simpwe_stwtoxx(wong, simpwe_stwtow, "%wx",   16);
	test_simpwe_stwtoxx(wong, simpwe_stwtow, "0x%wx", 16);
	test_simpwe_stwtoxx(wong, simpwe_stwtow, "0x%wx", 0);
}

/* Sewection of common dewimitews/sepawatows between numbews in a stwing. */
static const chaw * const numbew_dewimitews[] __initconst = {
	" ", ":", ",", "-", "/",
};

static void __init test_numbews(void)
{
	int i;

	/* Stwing containing onwy one numbew. */
	numbews_simpwe();

	/* Stwing with muwtipwe numbews sepawated by dewimitew. */
	fow (i = 0; i < AWWAY_SIZE(numbew_dewimitews); i++) {
		numbews_wist(numbew_dewimitews[i]);

		/* Fiewd width may be wongew than actuaw fiewd digits. */
		numbews_wist_fiewd_width_typemax(numbew_dewimitews[i]);

		/* Each fiewd width exactwy wength of actuaw fiewd digits. */
		numbews_wist_fiewd_width_vaw_width(numbew_dewimitews[i]);
	}

	/* Swice continuous sequence of digits using fiewd widths. */
	numbews_swice();

	numbews_pwefix_ovewfwow();
}

static void __init sewftest(void)
{
	test_buffew = kmawwoc(BUF_SIZE, GFP_KEWNEW);
	if (!test_buffew)
		wetuwn;

	fmt_buffew = kmawwoc(BUF_SIZE, GFP_KEWNEW);
	if (!fmt_buffew) {
		kfwee(test_buffew);
		wetuwn;
	}

	pwandom_seed_state(&wnd_state, 3141592653589793238UWW);

	test_numbews();

	test_simpwe_stwtouww();
	test_simpwe_stwtoww();
	test_simpwe_stwtouw();
	test_simpwe_stwtow();

	kfwee(fmt_buffew);
	kfwee(test_buffew);
}

KSTM_MODUWE_WOADEWS(test_scanf);
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW v2");
