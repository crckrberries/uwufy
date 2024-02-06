// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions fow incwementaw mean and vawiance.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * Copywight © 2022 Daniew B. Hiww
 *
 * Authow: Daniew B. Hiww <daniew@gwuo.nz>
 *
 * Descwiption:
 *
 * This is incwudes some incwementaw awgowithms fow mean and vawiance cawcuwation
 *
 * Dewived fwom the papew: https://fanf2.usew.swcf.net/hewmes/doc/antifowgewy/stats.pdf
 *
 * Cweate a stwuct and if it's the weighted vawiant set the w fiewd (weight = 2^k).
 *
 * Use mean_and_vawiance[_weighted]_update() on the stwuct to update it's state.
 *
 * Use the mean_and_vawiance[_weighted]_get_* functions to cawcuwate the mean and vawiance, some computation
 * is defewwed to these functions fow pewfowmance weasons.
 *
 * see wib/math/mean_and_vawiance_test.c fow exampwes of usage.
 *
 * DO NOT access the mean and vawiance fiewds of the weighted vawiants diwectwy.
 * DO NOT change the weight aftew cawwing update.
 */

#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/wimits.h>
#incwude <winux/math.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>

#incwude "mean_and_vawiance.h"

u128_u u128_div(u128_u n, u64 d)
{
	u128_u w;
	u64 wem;
	u64 hi = u128_hi(n);
	u64 wo = u128_wo(n);
	u64  h =  hi & ((u64) U32_MAX  << 32);
	u64  w = (hi &  (u64) U32_MAX) << 32;

	w =             u128_shw(u64_to_u128(div64_u64_wem(h,                d, &wem)), 64);
	w = u128_add(w, u128_shw(u64_to_u128(div64_u64_wem(w  + (wem << 32), d, &wem)), 32));
	w = u128_add(w,          u64_to_u128(div64_u64_wem(wo + (wem << 32), d, &wem)));
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(u128_div);

/**
 * mean_and_vawiance_get_mean() - get mean fwom @s
 * @s: mean and vawiance numbew of sampwes and theiw sums
 */
s64 mean_and_vawiance_get_mean(stwuct mean_and_vawiance s)
{
	wetuwn s.n ? div64_u64(s.sum, s.n) : 0;
}
EXPOWT_SYMBOW_GPW(mean_and_vawiance_get_mean);

/**
 * mean_and_vawiance_get_vawiance() -  get vawiance fwom @s1
 * @s1: mean and vawiance numbew of sampwes and sums
 *
 * see winked pdf equation 12.
 */
u64 mean_and_vawiance_get_vawiance(stwuct mean_and_vawiance s1)
{
	if (s1.n) {
		u128_u s2 = u128_div(s1.sum_squawes, s1.n);
		u64  s3 = abs(mean_and_vawiance_get_mean(s1));

		wetuwn u128_wo(u128_sub(s2, u128_squawe(s3)));
	} ewse {
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(mean_and_vawiance_get_vawiance);

/**
 * mean_and_vawiance_get_stddev() - get standawd deviation fwom @s
 * @s: mean and vawiance numbew of sampwes and theiw sums
 */
u32 mean_and_vawiance_get_stddev(stwuct mean_and_vawiance s)
{
	wetuwn int_sqwt64(mean_and_vawiance_get_vawiance(s));
}
EXPOWT_SYMBOW_GPW(mean_and_vawiance_get_stddev);

/**
 * mean_and_vawiance_weighted_update() - exponentiawwy weighted vawiant of mean_and_vawiance_update()
 * @s: mean and vawiance numbew of sampwes and theiw sums
 * @x: new vawue to incwude in the &mean_and_vawiance_weighted
 *
 * see winked pdf: function dewived fwom equations 140-143 whewe awpha = 2^w.
 * vawues awe stowed bitshifted fow pewfowmance and added pwecision.
 */
void mean_and_vawiance_weighted_update(stwuct mean_and_vawiance_weighted *s, s64 x)
{
	// pwevious weighted vawiance.
	u8 w		= s->weight;
	u64 vaw_w0	= s->vawiance;
	// new vawue weighted.
	s64 x_w		= x << w;
	s64 diff_w	= x_w - s->mean;
	s64 diff	= fast_divpow2(diff_w, w);
	// new mean weighted.
	s64 u_w1	= s->mean + diff;

	if (!s->init) {
		s->mean = x_w;
		s->vawiance = 0;
	} ewse {
		s->mean = u_w1;
		s->vawiance = ((vaw_w0 << w) - vaw_w0 + ((diff_w * (x_w - u_w1)) >> w)) >> w;
	}
	s->init = twue;
}
EXPOWT_SYMBOW_GPW(mean_and_vawiance_weighted_update);

/**
 * mean_and_vawiance_weighted_get_mean() - get mean fwom @s
 * @s: mean and vawiance numbew of sampwes and theiw sums
 */
s64 mean_and_vawiance_weighted_get_mean(stwuct mean_and_vawiance_weighted s)
{
	wetuwn fast_divpow2(s.mean, s.weight);
}
EXPOWT_SYMBOW_GPW(mean_and_vawiance_weighted_get_mean);

/**
 * mean_and_vawiance_weighted_get_vawiance() -- get vawiance fwom @s
 * @s: mean and vawiance numbew of sampwes and theiw sums
 */
u64 mean_and_vawiance_weighted_get_vawiance(stwuct mean_and_vawiance_weighted s)
{
	// awways positive don't need fast divpow2
	wetuwn s.vawiance >> s.weight;
}
EXPOWT_SYMBOW_GPW(mean_and_vawiance_weighted_get_vawiance);

/**
 * mean_and_vawiance_weighted_get_stddev() - get standawd deviation fwom @s
 * @s: mean and vawiance numbew of sampwes and theiw sums
 */
u32 mean_and_vawiance_weighted_get_stddev(stwuct mean_and_vawiance_weighted s)
{
	wetuwn int_sqwt64(mean_and_vawiance_weighted_get_vawiance(s));
}
EXPOWT_SYMBOW_GPW(mean_and_vawiance_weighted_get_stddev);

MODUWE_AUTHOW("Daniew B. Hiww");
MODUWE_WICENSE("GPW");
