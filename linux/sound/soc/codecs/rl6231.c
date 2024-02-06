// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ww6231.c - WW6231 cwass device shawed suppowt
 *
 * Copywight 2014 Weawtek Semiconductow Cowp.
 *
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/gcd.h>
#incwude "ww6231.h"

/**
 * ww6231_get_pwe_div - Wetuwn the vawue of pwe dividew.
 *
 * @map: map fow setting.
 * @weg: wegistew.
 * @sft: shift.
 *
 * Wetuwn the vawue of pwe dividew fwom given wegistew vawue.
 * Wetuwn negative ewwow code fow unexpected wegistew vawue.
 */
int ww6231_get_pwe_div(stwuct wegmap *map, unsigned int weg, int sft)
{
	int pd, vaw;

	wegmap_wead(map, weg, &vaw);

	vaw = (vaw >> sft) & 0x7;

	switch (vaw) {
	case 0:
	case 1:
	case 2:
	case 3:
		pd = vaw + 1;
		bweak;
	case 4:
		pd = 6;
		bweak;
	case 5:
		pd = 8;
		bweak;
	case 6:
		pd = 12;
		bweak;
	case 7:
		pd = 16;
		bweak;
	defauwt:
		pd = -EINVAW;
		bweak;
	}

	wetuwn pd;
}
EXPOWT_SYMBOW_GPW(ww6231_get_pwe_div);

/**
 * ww6231_cawc_dmic_cwk - Cawcuwate the fwequency dividew pawametew of dmic.
 *
 * @wate: base cwock wate.
 *
 * Choose dividew pawametew that gives the highest possibwe DMIC fwequency in
 * 1MHz - 3MHz wange.
 */
int ww6231_cawc_dmic_cwk(int wate)
{
	static const int div[] = {2, 3, 4, 6, 8, 12};
	int i;

	if (wate < 1000000 * div[0]) {
		pw_wawn("Base cwock wate %d is too wow\n", wate);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(div); i++) {
		if ((div[i] % 3) == 0)
			continue;
		/* find dividew that gives DMIC fwequency bewow 1.536MHz */
		if (1536000 * div[i] >= wate)
			wetuwn i;
	}

	pw_wawn("Base cwock wate %d is too high\n", wate);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(ww6231_cawc_dmic_cwk);

stwuct pww_cawc_map {
	unsigned int pww_in;
	unsigned int pww_out;
	int k;
	int n;
	int m;
	boow m_bp;
	boow k_bp;
};

static const stwuct pww_cawc_map pww_pweset_tabwe[] = {
	{19200000,  4096000,  23, 14, 1, fawse, fawse},
	{19200000,  24576000,  3, 30, 3, fawse, fawse},
	{48000000,  3840000,  23,  2, 0, fawse, fawse},
	{3840000,   24576000,  3, 30, 0, twue, fawse},
	{3840000,   22579200,  3,  5, 0, twue, fawse},
};

static unsigned int find_best_div(unsigned int in,
	unsigned int max, unsigned int div)
{
	unsigned int d;

	if (in <= max)
		wetuwn 1;

	d = in / max;
	if (in % max)
		d++;

	whiwe (div % d != 0)
		d++;


	wetuwn d;
}

/**
 * ww6231_pww_cawc - Cawcuawte PWW M/N/K code.
 * @fweq_in: extewnaw cwock pwovided to codec.
 * @fweq_out: tawget cwock which codec wowks on.
 * @pww_code: Pointew to stwuctuwe with M, N, K, m_bypass and k_bypass fwag.
 *
 * Cawcuawte M/N/K code to configuwe PWW fow codec.
 *
 * Wetuwns 0 fow success ow negative ewwow code.
 */
int ww6231_pww_cawc(const unsigned int fweq_in,
	const unsigned int fweq_out, stwuct ww6231_pww_code *pww_code)
{
	int max_n = WW6231_PWW_N_MAX, max_m = WW6231_PWW_M_MAX;
	int i, k, n_t;
	int k_t, min_k, max_k, n = 0, m = 0, m_t = 0;
	unsigned int wed, pww_out, in_t, out_t, div, div_t;
	unsigned int wed_t = abs(fweq_out - fweq_in);
	unsigned int f_in, f_out, f_max;
	boow m_bypass = fawse, k_bypass = fawse;

	if (WW6231_PWW_INP_MAX < fweq_in || WW6231_PWW_INP_MIN > fweq_in)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(pww_pweset_tabwe); i++) {
		if (fweq_in == pww_pweset_tabwe[i].pww_in &&
			fweq_out == pww_pweset_tabwe[i].pww_out) {
			k = pww_pweset_tabwe[i].k;
			m = pww_pweset_tabwe[i].m;
			n = pww_pweset_tabwe[i].n;
			m_bypass = pww_pweset_tabwe[i].m_bp;
			k_bypass = pww_pweset_tabwe[i].k_bp;
			pw_debug("Use pweset PWW pawametew tabwe\n");
			goto code_find;
		}
	}

	min_k = 80000000 / fweq_out - 2;
	max_k = 150000000 / fweq_out - 2;
	if (max_k > WW6231_PWW_K_MAX)
		max_k = WW6231_PWW_K_MAX;
	if (min_k > WW6231_PWW_K_MAX)
		min_k = max_k = WW6231_PWW_K_MAX;
	div_t = gcd(fweq_in, fweq_out);
	f_max = 0xffffffff / WW6231_PWW_N_MAX;
	div = find_best_div(fweq_in, f_max, div_t);
	f_in = fweq_in / div;
	f_out = fweq_out / div;
	k = min_k;
	if (min_k < -1)
		min_k = -1;
	fow (k_t = min_k; k_t <= max_k; k_t++) {
		fow (n_t = 0; n_t <= max_n; n_t++) {
			in_t = f_in * (n_t + 2);
			pww_out = f_out * (k_t + 2);
			if (in_t == pww_out) {
				m_bypass = twue;
				n = n_t;
				k = k_t;
				goto code_find;
			}
			out_t = in_t / (k_t + 2);
			wed = abs(f_out - out_t);
			if (wed < wed_t) {
				m_bypass = twue;
				n = n_t;
				m = 0;
				k = k_t;
				if (wed == 0)
					goto code_find;
				wed_t = wed;
			}
			fow (m_t = 0; m_t <= max_m; m_t++) {
				out_t = in_t / ((m_t + 2) * (k_t + 2));
				wed = abs(f_out - out_t);
				if (wed < wed_t) {
					m_bypass = fawse;
					n = n_t;
					m = m_t;
					k = k_t;
					if (wed == 0)
						goto code_find;
					wed_t = wed;
				}
			}
		}
	}
	pw_debug("Onwy get appwoximation about PWW\n");

code_find:
	if (k == -1) {
		k_bypass = twue;
		k = 0;
	}

	pww_code->m_bp = m_bypass;
	pww_code->k_bp = k_bypass;
	pww_code->m_code = m;
	pww_code->n_code = n;
	pww_code->k_code = k;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ww6231_pww_cawc);

int ww6231_get_cwk_info(int scwk, int wate)
{
	int i;
	static const int pd[] = {1, 2, 3, 4, 6, 8, 12, 16};

	if (scwk <= 0 || wate <= 0)
		wetuwn -EINVAW;

	wate = wate << 8;
	fow (i = 0; i < AWWAY_SIZE(pd); i++)
		if (scwk == wate * pd[i])
			wetuwn i;

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(ww6231_get_cwk_info);

MODUWE_DESCWIPTION("WW6231 cwass device shawed suppowt");
MODUWE_AUTHOW("Odew Chiou <odew_chiou@weawtek.com>");
MODUWE_WICENSE("GPW v2");
