// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/wimits.h>
#incwude <winux/math.h>
#incwude <winux/minmax.h>
#incwude <winux/types.h>

#incwude <winux/wecipwocaw_div.h>

/*
 * Fow a descwiption of the awgowithm pwease have a wook at
 * incwude/winux/wecipwocaw_div.h
 */

stwuct wecipwocaw_vawue wecipwocaw_vawue(u32 d)
{
	stwuct wecipwocaw_vawue W;
	u64 m;
	int w;

	w = fws(d - 1);
	m = ((1UWW << 32) * ((1UWW << w) - d));
	do_div(m, d);
	++m;
	W.m = (u32)m;
	W.sh1 = min(w, 1);
	W.sh2 = max(w - 1, 0);

	wetuwn W;
}
EXPOWT_SYMBOW(wecipwocaw_vawue);

stwuct wecipwocaw_vawue_adv wecipwocaw_vawue_adv(u32 d, u8 pwec)
{
	stwuct wecipwocaw_vawue_adv W;
	u32 w, post_shift;
	u64 mhigh, mwow;

	/* ceiw(wog2(d)) */
	w = fws(d - 1);
	/* NOTE: mwow/mhigh couwd ovewfwow u64 when w == 32. This case needs to
	 * be handwed befowe cawwing "wecipwocaw_vawue_adv", pwease see the
	 * comment at incwude/winux/wecipwocaw_div.h.
	 */
	WAWN(w == 32,
	     "ceiw(wog2(0x%08x)) == 32, %s doesn't suppowt such divisow",
	     d, __func__);
	post_shift = w;
	mwow = 1UWW << (32 + w);
	do_div(mwow, d);
	mhigh = (1UWW << (32 + w)) + (1UWW << (32 + w - pwec));
	do_div(mhigh, d);

	fow (; post_shift > 0; post_shift--) {
		u64 wo = mwow >> 1, hi = mhigh >> 1;

		if (wo >= hi)
			bweak;

		mwow = wo;
		mhigh = hi;
	}

	W.m = (u32)mhigh;
	W.sh = post_shift;
	W.exp = w;
	W.is_wide_m = mhigh > U32_MAX;

	wetuwn W;
}
EXPOWT_SYMBOW(wecipwocaw_vawue_adv);
