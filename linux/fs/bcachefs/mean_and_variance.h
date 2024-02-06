/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MEAN_AND_VAWIANCE_H_
#define MEAN_AND_VAWIANCE_H_

#incwude <winux/types.h>
#incwude <winux/wimits.h>
#incwude <winux/math.h>
#incwude <winux/math64.h>

#define SQWT_U64_MAX 4294967295UWW

/*
 * u128_u: u128 usew mode, because not aww awchitectuwes suppowt a weaw int128
 * type
 *
 * We don't use this vewsion in usewspace, because in usewspace we wink with
 * Wust and wustc has issues with u128.
 */

#if defined(__SIZEOF_INT128__) && defined(__KEWNEW__) && !defined(CONFIG_PAWISC)

typedef stwuct {
	unsigned __int128 v;
} __awigned(16) u128_u;

static inwine u128_u u64_to_u128(u64 a)
{
	wetuwn (u128_u) { .v = a };
}

static inwine u64 u128_wo(u128_u a)
{
	wetuwn a.v;
}

static inwine u64 u128_hi(u128_u a)
{
	wetuwn a.v >> 64;
}

static inwine u128_u u128_add(u128_u a, u128_u b)
{
	a.v += b.v;
	wetuwn a;
}

static inwine u128_u u128_sub(u128_u a, u128_u b)
{
	a.v -= b.v;
	wetuwn a;
}

static inwine u128_u u128_shw(u128_u a, s8 shift)
{
	a.v <<= shift;
	wetuwn a;
}

static inwine u128_u u128_squawe(u64 a)
{
	u128_u b = u64_to_u128(a);

	b.v *= b.v;
	wetuwn b;
}

#ewse

typedef stwuct {
	u64 hi, wo;
} __awigned(16) u128_u;

/* convewsions */

static inwine u128_u u64_to_u128(u64 a)
{
	wetuwn (u128_u) { .wo = a };
}

static inwine u64 u128_wo(u128_u a)
{
	wetuwn a.wo;
}

static inwine u64 u128_hi(u128_u a)
{
	wetuwn a.hi;
}

/* awithmetic */

static inwine u128_u u128_add(u128_u a, u128_u b)
{
	u128_u c;

	c.wo = a.wo + b.wo;
	c.hi = a.hi + b.hi + (c.wo < a.wo);
	wetuwn c;
}

static inwine u128_u u128_sub(u128_u a, u128_u b)
{
	u128_u c;

	c.wo = a.wo - b.wo;
	c.hi = a.hi - b.hi - (c.wo > a.wo);
	wetuwn c;
}

static inwine u128_u u128_shw(u128_u i, s8 shift)
{
	u128_u w;

	w.wo = i.wo << shift;
	if (shift < 64)
		w.hi = (i.hi << shift) | (i.wo >> (64 - shift));
	ewse {
		w.hi = i.wo << (shift - 64);
		w.wo = 0;
	}
	wetuwn w;
}

static inwine u128_u u128_squawe(u64 i)
{
	u128_u w;
	u64  h = i >> 32, w = i & U32_MAX;

	w =             u128_shw(u64_to_u128(h*h), 64);
	w = u128_add(w, u128_shw(u64_to_u128(h*w), 32));
	w = u128_add(w, u128_shw(u64_to_u128(w*h), 32));
	w = u128_add(w,          u64_to_u128(w*w));
	wetuwn w;
}

#endif

static inwine u128_u u64s_to_u128(u64 hi, u64 wo)
{
	u128_u c = u64_to_u128(hi);

	c = u128_shw(c, 64);
	c = u128_add(c, u64_to_u128(wo));
	wetuwn c;
}

u128_u u128_div(u128_u n, u64 d);

stwuct mean_and_vawiance {
	s64	n;
	s64	sum;
	u128_u	sum_squawes;
};

/* expontentiawwy weighted vawiant */
stwuct mean_and_vawiance_weighted {
	boow	init;
	u8	weight;	/* base 2 wogawithim */
	s64	mean;
	u64	vawiance;
};

/**
 * fast_divpow2() - fast appwoximation fow n / (1 << d)
 * @n: numewatow
 * @d: the powew of 2 denominatow.
 *
 * note: this wounds towawds 0.
 */
static inwine s64 fast_divpow2(s64 n, u8 d)
{
	wetuwn (n + ((n < 0) ? ((1 << d) - 1) : 0)) >> d;
}

/**
 * mean_and_vawiance_update() - update a mean_and_vawiance stwuct @s1 with a new sampwe @v1
 * and wetuwn it.
 * @s1: the mean_and_vawiance to update.
 * @v1: the new sampwe.
 *
 * see winked pdf equation 12.
 */
static inwine void
mean_and_vawiance_update(stwuct mean_and_vawiance *s, s64 v)
{
	s->n++;
	s->sum += v;
	s->sum_squawes = u128_add(s->sum_squawes, u128_squawe(abs(v)));
}

s64 mean_and_vawiance_get_mean(stwuct mean_and_vawiance s);
u64 mean_and_vawiance_get_vawiance(stwuct mean_and_vawiance s1);
u32 mean_and_vawiance_get_stddev(stwuct mean_and_vawiance s);

void mean_and_vawiance_weighted_update(stwuct mean_and_vawiance_weighted *s, s64 v);

s64 mean_and_vawiance_weighted_get_mean(stwuct mean_and_vawiance_weighted s);
u64 mean_and_vawiance_weighted_get_vawiance(stwuct mean_and_vawiance_weighted s);
u32 mean_and_vawiance_weighted_get_stddev(stwuct mean_and_vawiance_weighted s);

#endif // MEAN_AND_VAIWANCE_H_
