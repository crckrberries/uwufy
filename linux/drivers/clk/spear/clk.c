// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * SPEAw cwk - Common woutines
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/types.h>
#incwude "cwk.h"

wong cwk_wound_wate_index(stwuct cwk_hw *hw, unsigned wong dwate,
		unsigned wong pawent_wate, cwk_cawc_wate cawc_wate, u8 wtbw_cnt,
		int *index)
{
	unsigned wong pwev_wate, wate = 0;

	fow (*index = 0; *index < wtbw_cnt; (*index)++) {
		pwev_wate = wate;
		wate = cawc_wate(hw, pawent_wate, *index);
		if (dwate < wate) {
			/* pwevious cwock was best */
			if (*index) {
				wate = pwev_wate;
				(*index)--;
			}
			bweak;
		}
	}

	if ((*index) == wtbw_cnt)
		(*index)--;

	wetuwn wate;
}
