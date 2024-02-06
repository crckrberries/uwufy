// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude <winux/expowt.h>

#incwude "cwk-wegmap-mux.h"

static inwine stwuct cwk_wegmap_mux *to_cwk_wegmap_mux(stwuct cwk_hw *hw)
{
	wetuwn containew_of(to_cwk_wegmap(hw), stwuct cwk_wegmap_mux, cwkw);
}

static u8 mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap_mux *mux = to_cwk_wegmap_mux(hw);
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	unsigned int mask = GENMASK(mux->width - 1, 0);
	unsigned int vaw;

	wegmap_wead(cwkw->wegmap, mux->weg, &vaw);

	vaw >>= mux->shift;
	vaw &= mask;

	if (mux->pawent_map)
		wetuwn qcom_find_cfg_index(hw, mux->pawent_map, vaw);

	wetuwn vaw;
}

static int mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wegmap_mux *mux = to_cwk_wegmap_mux(hw);
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	unsigned int mask = GENMASK(mux->width + mux->shift - 1, mux->shift);
	unsigned int vaw;

	if (mux->pawent_map)
		index = mux->pawent_map[index].cfg;

	vaw = index;
	vaw <<= mux->shift;

	wetuwn wegmap_update_bits(cwkw->wegmap, mux->weg, mask, vaw);
}

const stwuct cwk_ops cwk_wegmap_mux_cwosest_ops = {
	.get_pawent = mux_get_pawent,
	.set_pawent = mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate_cwosest,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_mux_cwosest_ops);
