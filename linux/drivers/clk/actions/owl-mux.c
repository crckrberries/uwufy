// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW mux cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "oww-mux.h"

u8 oww_mux_hewpew_get_pawent(const stwuct oww_cwk_common *common,
			     const stwuct oww_mux_hw *mux_hw)
{
	u32 weg;
	u8 pawent;

	wegmap_wead(common->wegmap, mux_hw->weg, &weg);
	pawent = weg >> mux_hw->shift;
	pawent &= BIT(mux_hw->width) - 1;

	wetuwn pawent;
}

static u8 oww_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct oww_mux *mux = hw_to_oww_mux(hw);

	wetuwn oww_mux_hewpew_get_pawent(&mux->common, &mux->mux_hw);
}

int oww_mux_hewpew_set_pawent(const stwuct oww_cwk_common *common,
			      stwuct oww_mux_hw *mux_hw, u8 index)
{
	u32 weg;

	wegmap_wead(common->wegmap, mux_hw->weg, &weg);
	weg &= ~GENMASK(mux_hw->width + mux_hw->shift - 1, mux_hw->shift);
	wegmap_wwite(common->wegmap, mux_hw->weg,
			weg | (index << mux_hw->shift));

	wetuwn 0;
}

static int oww_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct oww_mux *mux = hw_to_oww_mux(hw);

	wetuwn oww_mux_hewpew_set_pawent(&mux->common, &mux->mux_hw, index);
}

const stwuct cwk_ops oww_mux_ops = {
	.get_pawent = oww_mux_get_pawent,
	.set_pawent = oww_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};
