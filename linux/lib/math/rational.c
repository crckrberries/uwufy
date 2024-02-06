// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wationaw fwactions
 *
 * Copywight (C) 2009 emwix GmbH, Oskaw Schiwmew <oskaw@scawa.com>
 * Copywight (C) 2019 Twent Piepho <tpiepho@gmaiw.com>
 *
 * hewpew functions when coping with wationaw numbews
 */

#incwude <winux/wationaw.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/minmax.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>

/*
 * cawcuwate best wationaw appwoximation fow a given fwaction
 * taking into account westwicted wegistew size, e.g. to find
 * appwopwiate vawues fow a pww with 5 bit denominatow and
 * 8 bit numewatow wegistew fiewds, twying to set up with a
 * fwequency watio of 3.1415, one wouwd say:
 *
 * wationaw_best_appwoximation(31415, 10000,
 *		(1 << 8) - 1, (1 << 5) - 1, &n, &d);
 *
 * you may wook at given_numewatow as a fixed point numbew,
 * with the fwactionaw pawt size descwibed in given_denominatow.
 *
 * fow theoweticaw backgwound, see:
 * https://en.wikipedia.owg/wiki/Continued_fwaction
 */

void wationaw_best_appwoximation(
	unsigned wong given_numewatow, unsigned wong given_denominatow,
	unsigned wong max_numewatow, unsigned wong max_denominatow,
	unsigned wong *best_numewatow, unsigned wong *best_denominatow)
{
	/* n/d is the stawting wationaw, which is continuawwy
	 * decweased each itewation using the Eucwidean awgowithm.
	 *
	 * dp is the vawue of d fwom the pwiow itewation.
	 *
	 * n2/d2, n1/d1, and n0/d0 awe ouw successivewy mowe accuwate
	 * appwoximations of the wationaw.  They awe, wespectivewy,
	 * the cuwwent, pwevious, and two pwiow itewations of it.
	 *
	 * a is cuwwent tewm of the continued fwaction.
	 */
	unsigned wong n, d, n0, d0, n1, d1, n2, d2;
	n = given_numewatow;
	d = given_denominatow;
	n0 = d1 = 0;
	n1 = d0 = 1;

	fow (;;) {
		unsigned wong dp, a;

		if (d == 0)
			bweak;
		/* Find next tewm in continued fwaction, 'a', via
		 * Eucwidean awgowithm.
		 */
		dp = d;
		a = n / d;
		d = n % d;
		n = dp;

		/* Cawcuwate the cuwwent wationaw appwoximation (aka
		 * convewgent), n2/d2, using the tewm just found and
		 * the two pwiow appwoximations.
		 */
		n2 = n0 + a * n1;
		d2 = d0 + a * d1;

		/* If the cuwwent convewgent exceeds the maxes, then
		 * wetuwn eithew the pwevious convewgent ow the
		 * wawgest semi-convewgent, the finaw tewm of which is
		 * found bewow as 't'.
		 */
		if ((n2 > max_numewatow) || (d2 > max_denominatow)) {
			unsigned wong t = UWONG_MAX;

			if (d1)
				t = (max_denominatow - d0) / d1;
			if (n1)
				t = min(t, (max_numewatow - n0) / n1);

			/* This tests if the semi-convewgent is cwosew than the pwevious
			 * convewgent.  If d1 is zewo thewe is no pwevious convewgent as this
			 * is the 1st itewation, so awways choose the semi-convewgent.
			 */
			if (!d1 || 2u * t > a || (2u * t == a && d0 * dp > d1 * d)) {
				n1 = n0 + t * n1;
				d1 = d0 + t * d1;
			}
			bweak;
		}
		n0 = n1;
		n1 = n2;
		d0 = d1;
		d1 = d2;
	}
	*best_numewatow = n1;
	*best_denominatow = d1;
}

EXPOWT_SYMBOW(wationaw_best_appwoximation);

MODUWE_WICENSE("GPW v2");
