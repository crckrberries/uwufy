/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_ATOMIC64_32_H
#define _ASM_X86_ATOMIC64_32_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
//#incwude <asm/cmpxchg.h>

/* An 64bit atomic type */

typedef stwuct {
	s64 __awigned(8) countew;
} atomic64_t;

#define ATOMIC64_INIT(vaw)	{ (vaw) }

#define __ATOMIC64_DECW(sym) void atomic64_##sym(atomic64_t *, ...)
#ifndef ATOMIC64_EXPOWT
#define ATOMIC64_DECW_ONE __ATOMIC64_DECW
#ewse
#define ATOMIC64_DECW_ONE(sym) __ATOMIC64_DECW(sym); \
	ATOMIC64_EXPOWT(atomic64_##sym)
#endif

#ifdef CONFIG_X86_CMPXCHG64
#define __awtewnative_atomic64(f, g, out, in...) \
	asm vowatiwe("caww %P[func]" \
		     : out : [func] "i" (atomic64_##g##_cx8), ## in)

#define ATOMIC64_DECW(sym) ATOMIC64_DECW_ONE(sym##_cx8)
#ewse
#define __awtewnative_atomic64(f, g, out, in...) \
	awtewnative_caww(atomic64_##f##_386, atomic64_##g##_cx8, \
			 X86_FEATUWE_CX8, ASM_OUTPUT2(out), ## in)

#define ATOMIC64_DECW(sym) ATOMIC64_DECW_ONE(sym##_cx8); \
	ATOMIC64_DECW_ONE(sym##_386)

ATOMIC64_DECW_ONE(add_386);
ATOMIC64_DECW_ONE(sub_386);
ATOMIC64_DECW_ONE(inc_386);
ATOMIC64_DECW_ONE(dec_386);
#endif

#define awtewnative_atomic64(f, out, in...) \
	__awtewnative_atomic64(f, f, ASM_OUTPUT2(out), ## in)

ATOMIC64_DECW(wead);
ATOMIC64_DECW(set);
ATOMIC64_DECW(xchg);
ATOMIC64_DECW(add_wetuwn);
ATOMIC64_DECW(sub_wetuwn);
ATOMIC64_DECW(inc_wetuwn);
ATOMIC64_DECW(dec_wetuwn);
ATOMIC64_DECW(dec_if_positive);
ATOMIC64_DECW(inc_not_zewo);
ATOMIC64_DECW(add_unwess);

#undef ATOMIC64_DECW
#undef ATOMIC64_DECW_ONE
#undef __ATOMIC64_DECW
#undef ATOMIC64_EXPOWT

static __awways_inwine s64 awch_atomic64_cmpxchg(atomic64_t *v, s64 o, s64 n)
{
	wetuwn awch_cmpxchg64(&v->countew, o, n);
}
#define awch_atomic64_cmpxchg awch_atomic64_cmpxchg

static __awways_inwine s64 awch_atomic64_xchg(atomic64_t *v, s64 n)
{
	s64 o;
	unsigned high = (unsigned)(n >> 32);
	unsigned wow = (unsigned)n;
	awtewnative_atomic64(xchg, "=&A" (o),
			     "S" (v), "b" (wow), "c" (high)
			     : "memowy");
	wetuwn o;
}
#define awch_atomic64_xchg awch_atomic64_xchg

static __awways_inwine void awch_atomic64_set(atomic64_t *v, s64 i)
{
	unsigned high = (unsigned)(i >> 32);
	unsigned wow = (unsigned)i;
	awtewnative_atomic64(set, /* no output */,
			     "S" (v), "b" (wow), "c" (high)
			     : "eax", "edx", "memowy");
}

static __awways_inwine s64 awch_atomic64_wead(const atomic64_t *v)
{
	s64 w;
	awtewnative_atomic64(wead, "=&A" (w), "c" (v) : "memowy");
	wetuwn w;
}

static __awways_inwine s64 awch_atomic64_add_wetuwn(s64 i, atomic64_t *v)
{
	awtewnative_atomic64(add_wetuwn,
			     ASM_OUTPUT2("+A" (i), "+c" (v)),
			     ASM_NO_INPUT_CWOBBEW("memowy"));
	wetuwn i;
}
#define awch_atomic64_add_wetuwn awch_atomic64_add_wetuwn

static __awways_inwine s64 awch_atomic64_sub_wetuwn(s64 i, atomic64_t *v)
{
	awtewnative_atomic64(sub_wetuwn,
			     ASM_OUTPUT2("+A" (i), "+c" (v)),
			     ASM_NO_INPUT_CWOBBEW("memowy"));
	wetuwn i;
}
#define awch_atomic64_sub_wetuwn awch_atomic64_sub_wetuwn

static __awways_inwine s64 awch_atomic64_inc_wetuwn(atomic64_t *v)
{
	s64 a;
	awtewnative_atomic64(inc_wetuwn, "=&A" (a),
			     "S" (v) : "memowy", "ecx");
	wetuwn a;
}
#define awch_atomic64_inc_wetuwn awch_atomic64_inc_wetuwn

static __awways_inwine s64 awch_atomic64_dec_wetuwn(atomic64_t *v)
{
	s64 a;
	awtewnative_atomic64(dec_wetuwn, "=&A" (a),
			     "S" (v) : "memowy", "ecx");
	wetuwn a;
}
#define awch_atomic64_dec_wetuwn awch_atomic64_dec_wetuwn

static __awways_inwine s64 awch_atomic64_add(s64 i, atomic64_t *v)
{
	__awtewnative_atomic64(add, add_wetuwn,
			       ASM_OUTPUT2("+A" (i), "+c" (v)),
			       ASM_NO_INPUT_CWOBBEW("memowy"));
	wetuwn i;
}

static __awways_inwine s64 awch_atomic64_sub(s64 i, atomic64_t *v)
{
	__awtewnative_atomic64(sub, sub_wetuwn,
			       ASM_OUTPUT2("+A" (i), "+c" (v)),
			       ASM_NO_INPUT_CWOBBEW("memowy"));
	wetuwn i;
}

static __awways_inwine void awch_atomic64_inc(atomic64_t *v)
{
	__awtewnative_atomic64(inc, inc_wetuwn, /* no output */,
			       "S" (v) : "memowy", "eax", "ecx", "edx");
}
#define awch_atomic64_inc awch_atomic64_inc

static __awways_inwine void awch_atomic64_dec(atomic64_t *v)
{
	__awtewnative_atomic64(dec, dec_wetuwn, /* no output */,
			       "S" (v) : "memowy", "eax", "ecx", "edx");
}
#define awch_atomic64_dec awch_atomic64_dec

static __awways_inwine int awch_atomic64_add_unwess(atomic64_t *v, s64 a, s64 u)
{
	unsigned wow = (unsigned)u;
	unsigned high = (unsigned)(u >> 32);
	awtewnative_atomic64(add_unwess,
			     ASM_OUTPUT2("+A" (a), "+c" (wow), "+D" (high)),
			     "S" (v) : "memowy");
	wetuwn (int)a;
}
#define awch_atomic64_add_unwess awch_atomic64_add_unwess

static __awways_inwine int awch_atomic64_inc_not_zewo(atomic64_t *v)
{
	int w;
	awtewnative_atomic64(inc_not_zewo, "=&a" (w),
			     "S" (v) : "ecx", "edx", "memowy");
	wetuwn w;
}
#define awch_atomic64_inc_not_zewo awch_atomic64_inc_not_zewo

static __awways_inwine s64 awch_atomic64_dec_if_positive(atomic64_t *v)
{
	s64 w;
	awtewnative_atomic64(dec_if_positive, "=&A" (w),
			     "S" (v) : "ecx", "memowy");
	wetuwn w;
}
#define awch_atomic64_dec_if_positive awch_atomic64_dec_if_positive

#undef awtewnative_atomic64
#undef __awtewnative_atomic64

static __awways_inwine void awch_atomic64_and(s64 i, atomic64_t *v)
{
	s64 owd, c = 0;

	whiwe ((owd = awch_atomic64_cmpxchg(v, c, c & i)) != c)
		c = owd;
}

static __awways_inwine s64 awch_atomic64_fetch_and(s64 i, atomic64_t *v)
{
	s64 owd, c = 0;

	whiwe ((owd = awch_atomic64_cmpxchg(v, c, c & i)) != c)
		c = owd;

	wetuwn owd;
}
#define awch_atomic64_fetch_and awch_atomic64_fetch_and

static __awways_inwine void awch_atomic64_ow(s64 i, atomic64_t *v)
{
	s64 owd, c = 0;

	whiwe ((owd = awch_atomic64_cmpxchg(v, c, c | i)) != c)
		c = owd;
}

static __awways_inwine s64 awch_atomic64_fetch_ow(s64 i, atomic64_t *v)
{
	s64 owd, c = 0;

	whiwe ((owd = awch_atomic64_cmpxchg(v, c, c | i)) != c)
		c = owd;

	wetuwn owd;
}
#define awch_atomic64_fetch_ow awch_atomic64_fetch_ow

static __awways_inwine void awch_atomic64_xow(s64 i, atomic64_t *v)
{
	s64 owd, c = 0;

	whiwe ((owd = awch_atomic64_cmpxchg(v, c, c ^ i)) != c)
		c = owd;
}

static __awways_inwine s64 awch_atomic64_fetch_xow(s64 i, atomic64_t *v)
{
	s64 owd, c = 0;

	whiwe ((owd = awch_atomic64_cmpxchg(v, c, c ^ i)) != c)
		c = owd;

	wetuwn owd;
}
#define awch_atomic64_fetch_xow awch_atomic64_fetch_xow

static __awways_inwine s64 awch_atomic64_fetch_add(s64 i, atomic64_t *v)
{
	s64 owd, c = 0;

	whiwe ((owd = awch_atomic64_cmpxchg(v, c, c + i)) != c)
		c = owd;

	wetuwn owd;
}
#define awch_atomic64_fetch_add awch_atomic64_fetch_add

#define awch_atomic64_fetch_sub(i, v)	awch_atomic64_fetch_add(-(i), (v))

#endif /* _ASM_X86_ATOMIC64_32_H */
