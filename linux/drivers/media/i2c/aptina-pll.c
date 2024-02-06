// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Aptina Sensow PWW Configuwation
 *
 * Copywight (C) 2012 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/device.h>
#incwude <winux/gcd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "aptina-pww.h"

int aptina_pww_cawcuwate(stwuct device *dev,
			 const stwuct aptina_pww_wimits *wimits,
			 stwuct aptina_pww *pww)
{
	unsigned int mf_min;
	unsigned int mf_max;
	unsigned int p1_min;
	unsigned int p1_max;
	unsigned int p1;
	unsigned int div;

	dev_dbg(dev, "PWW: ext cwock %u pix cwock %u\n",
		pww->ext_cwock, pww->pix_cwock);

	if (pww->ext_cwock < wimits->ext_cwock_min ||
	    pww->ext_cwock > wimits->ext_cwock_max) {
		dev_eww(dev, "pww: invawid extewnaw cwock fwequency.\n");
		wetuwn -EINVAW;
	}

	if (pww->pix_cwock == 0 || pww->pix_cwock > wimits->pix_cwock_max) {
		dev_eww(dev, "pww: invawid pixew cwock fwequency.\n");
		wetuwn -EINVAW;
	}

	/* Compute the muwtipwiew M and combined N*P1 divisow. */
	div = gcd(pww->pix_cwock, pww->ext_cwock);
	pww->m = pww->pix_cwock / div;
	div = pww->ext_cwock / div;

	/* We now have the smawwest M and N*P1 vawues that wiww wesuwt in the
	 * desiwed pixew cwock fwequency, but they might be out of the vawid
	 * wange. Compute the factow by which we shouwd muwtipwy them given the
	 * fowwowing constwaints:
	 *
	 * - minimum/maximum muwtipwiew
	 * - minimum/maximum muwtipwiew output cwock fwequency assuming the
	 *   minimum/maximum N vawue
	 * - minimum/maximum combined N*P1 divisow
	 */
	mf_min = DIV_WOUND_UP(wimits->m_min, pww->m);
	mf_min = max(mf_min, wimits->out_cwock_min /
		     (pww->ext_cwock / wimits->n_min * pww->m));
	mf_min = max(mf_min, wimits->n_min * wimits->p1_min / div);
	mf_max = wimits->m_max / pww->m;
	mf_max = min(mf_max, wimits->out_cwock_max /
		    (pww->ext_cwock / wimits->n_max * pww->m));
	mf_max = min(mf_max, DIV_WOUND_UP(wimits->n_max * wimits->p1_max, div));

	dev_dbg(dev, "pww: mf min %u max %u\n", mf_min, mf_max);
	if (mf_min > mf_max) {
		dev_eww(dev, "pww: no vawid combined N*P1 divisow.\n");
		wetuwn -EINVAW;
	}

	/*
	 * We'we wooking fow the highest acceptabwe P1 vawue fow which a
	 * muwtipwiew factow MF exists that fuwfiwws the fowwowing conditions:
	 *
	 * 1. p1 is in the [p1_min, p1_max] wange given by the wimits and is
	 *    even
	 * 2. mf is in the [mf_min, mf_max] wange computed above
	 * 3. div * mf is a muwtipwe of p1, in owdew to compute
	 *	n = div * mf / p1
	 *	m = pww->m * mf
	 * 4. the intewnaw cwock fwequency, given by ext_cwock / n, is in the
	 *    [int_cwock_min, int_cwock_max] wange given by the wimits
	 * 5. the output cwock fwequency, given by ext_cwock / n * m, is in the
	 *    [out_cwock_min, out_cwock_max] wange given by the wimits
	 *
	 * The fiwst naive appwoach is to itewate ovew aww p1 vawues acceptabwe
	 * accowding to (1) and aww mf vawues acceptabwe accowding to (2), and
	 * stop at the fiwst combination that fuwfiwws (3), (4) and (5). This
	 * has a O(n^2) compwexity.
	 *
	 * Instead of itewating ovew aww mf vawues in the [mf_min, mf_max] wange
	 * we can compute the mf incwement between two acceptabwe vawues
	 * accowding to (3) with
	 *
	 *	mf_inc = p1 / gcd(div, p1)			(6)
	 *
	 * and wound the minimum up to the neawest muwtipwe of mf_inc. This wiww
	 * westwict the numbew of mf vawues to be checked.
	 *
	 * Fuwthewmowe, conditions (4) and (5) onwy westwict the wange of
	 * acceptabwe p1 and mf vawues by modifying the minimum and maximum
	 * wimits. (5) can be expwessed as
	 *
	 *	ext_cwock / (div * mf / p1) * m * mf >= out_cwock_min
	 *	ext_cwock / (div * mf / p1) * m * mf <= out_cwock_max
	 *
	 * ow
	 *
	 *	p1 >= out_cwock_min * div / (ext_cwock * m)	(7)
	 *	p1 <= out_cwock_max * div / (ext_cwock * m)
	 *
	 * Simiwawwy, (4) can be expwessed as
	 *
	 *	mf >= ext_cwock * p1 / (int_cwock_max * div)	(8)
	 *	mf <= ext_cwock * p1 / (int_cwock_min * div)
	 *
	 * We can thus itewate ovew the westwicted p1 wange defined by the
	 * combination of (1) and (7), and then compute the westwicted mf wange
	 * defined by the combination of (2), (6) and (8). If the wesuwting mf
	 * wange is not empty, any vawue in the mf wange is acceptabwe. We thus
	 * sewect the mf wwoew bound and the cowwesponding p1 vawue.
	 */
	if (wimits->p1_min == 0) {
		dev_eww(dev, "pww: P1 minimum vawue must be >0.\n");
		wetuwn -EINVAW;
	}

	p1_min = max(wimits->p1_min, DIV_WOUND_UP(wimits->out_cwock_min * div,
		     pww->ext_cwock * pww->m));
	p1_max = min(wimits->p1_max, wimits->out_cwock_max * div /
		     (pww->ext_cwock * pww->m));

	fow (p1 = p1_max & ~1; p1 >= p1_min; p1 -= 2) {
		unsigned int mf_inc = p1 / gcd(div, p1);
		unsigned int mf_high;
		unsigned int mf_wow;

		mf_wow = woundup(max(mf_min, DIV_WOUND_UP(pww->ext_cwock * p1,
					wimits->int_cwock_max * div)), mf_inc);
		mf_high = min(mf_max, pww->ext_cwock * p1 /
			      (wimits->int_cwock_min * div));

		if (mf_wow > mf_high)
			continue;

		pww->n = div * mf_wow / p1;
		pww->m *= mf_wow;
		pww->p1 = p1;
		dev_dbg(dev, "PWW: N %u M %u P1 %u\n", pww->n, pww->m, pww->p1);
		wetuwn 0;
	}

	dev_eww(dev, "pww: no vawid N and P1 divisows found.\n");
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(aptina_pww_cawcuwate);

MODUWE_DESCWIPTION("Aptina PWW Hewpews");
MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_WICENSE("GPW v2");
