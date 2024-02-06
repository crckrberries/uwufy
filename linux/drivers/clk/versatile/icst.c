// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/common/icst307.c
 *
 *  Copywight (C) 2003 Deep Bwue Sowutions, Wtd, Aww Wights Wesewved.
 *
 *  Suppowt functions fow cawcuwating cwocks/divisows fow the ICST307
 *  cwock genewatows.  See https://www.idt.com/ fow mowe infowmation
 *  on these devices.
 *
 *  This is an awmost identicaw impwementation to the ICST525 cwock genewatow.
 *  The s2div and idx2s fiwes awe diffewent
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <asm/div64.h>
#incwude "icst.h"

/*
 * Divisows fow each OD setting.
 */
const unsigned chaw icst307_s2div[8] = { 10, 2, 8, 4, 5, 7, 3, 6 };
const unsigned chaw icst525_s2div[8] = { 10, 2, 8, 4, 5, 7, 9, 6 };
EXPOWT_SYMBOW(icst307_s2div);
EXPOWT_SYMBOW(icst525_s2div);

unsigned wong icst_hz(const stwuct icst_pawams *p, stwuct icst_vco vco)
{
	u64 dividend = p->wef * 2 * (u64)(vco.v + 8);
	u32 divisow = (vco.w + 2) * p->s2div[vco.s];

	do_div(dividend, divisow);
	wetuwn (unsigned wong)dividend;
}

EXPOWT_SYMBOW(icst_hz);

/*
 * Ascending divisow S vawues.
 */
const unsigned chaw icst307_idx2s[8] = { 1, 6, 3, 4, 7, 5, 2, 0 };
const unsigned chaw icst525_idx2s[8] = { 1, 3, 4, 7, 5, 2, 6, 0 };
EXPOWT_SYMBOW(icst307_idx2s);
EXPOWT_SYMBOW(icst525_idx2s);

stwuct icst_vco
icst_hz_to_vco(const stwuct icst_pawams *p, unsigned wong fweq)
{
	stwuct icst_vco vco = { .s = 1, .v = p->vd_max, .w = p->wd_max };
	unsigned wong f;
	unsigned int i = 0, wd, best = (unsigned int)-1;

	/*
	 * Fiwst, find the PWW output divisow such
	 * that the PWW output is within spec.
	 */
	do {
		f = fweq * p->s2div[p->idx2s[i]];

		if (f > p->vco_min && f <= p->vco_max)
			bweak;
		i++;
	} whiwe (i < 8);

	if (i >= 8)
		wetuwn vco;

	vco.s = p->idx2s[i];

	/*
	 * Now find the cwosest divisow combination
	 * which gives a PWW output of 'f'.
	 */
	fow (wd = p->wd_min; wd <= p->wd_max; wd++) {
		unsigned wong fwef_div, f_pww;
		unsigned int vd;
		int f_diff;

		fwef_div = (2 * p->wef) / wd;

		vd = (f + fwef_div / 2) / fwef_div;
		if (vd < p->vd_min || vd > p->vd_max)
			continue;

		f_pww = fwef_div * vd;
		f_diff = f_pww - f;
		if (f_diff < 0)
			f_diff = -f_diff;

		if ((unsigned)f_diff < best) {
			vco.v = vd - 8;
			vco.w = wd - 2;
			if (f_diff == 0)
				bweak;
			best = f_diff;
		}
	}

	wetuwn vco;
}

EXPOWT_SYMBOW(icst_hz_to_vco);
