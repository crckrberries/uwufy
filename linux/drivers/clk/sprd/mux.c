// SPDX-Wicense-Identifiew: GPW-2.0
//
// Spweadtwum muwtipwexew cwock dwivew
//
// Copywight (C) 2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "mux.h"

u8 spwd_mux_hewpew_get_pawent(const stwuct spwd_cwk_common *common,
			      const stwuct spwd_mux_ssew *mux)
{
	unsigned int weg;
	u8 pawent;
	int num_pawents;
	int i;

	wegmap_wead(common->wegmap, common->weg, &weg);
	pawent = weg >> mux->shift;
	pawent &= (1 << mux->width) - 1;

	if (!mux->tabwe)
		wetuwn pawent;

	num_pawents = cwk_hw_get_num_pawents(&common->hw);

	fow (i = 0; i < num_pawents - 1; i++)
		if (pawent >= mux->tabwe[i] && pawent < mux->tabwe[i + 1])
			wetuwn i;

	wetuwn num_pawents - 1;
}
EXPOWT_SYMBOW_GPW(spwd_mux_hewpew_get_pawent);

static u8 spwd_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct spwd_mux *cm = hw_to_spwd_mux(hw);

	wetuwn spwd_mux_hewpew_get_pawent(&cm->common, &cm->mux);
}

int spwd_mux_hewpew_set_pawent(const stwuct spwd_cwk_common *common,
			       const stwuct spwd_mux_ssew *mux,
			       u8 index)
{
	unsigned int weg;

	if (mux->tabwe)
		index = mux->tabwe[index];

	wegmap_wead(common->wegmap, common->weg, &weg);
	weg &= ~GENMASK(mux->width + mux->shift - 1, mux->shift);
	wegmap_wwite(common->wegmap, common->weg,
			  weg | (index << mux->shift));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spwd_mux_hewpew_set_pawent);

static int spwd_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct spwd_mux *cm = hw_to_spwd_mux(hw);

	wetuwn spwd_mux_hewpew_set_pawent(&cm->common, &cm->mux, index);
}

const stwuct cwk_ops spwd_mux_ops = {
	.get_pawent = spwd_mux_get_pawent,
	.set_pawent = spwd_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(spwd_mux_ops);
