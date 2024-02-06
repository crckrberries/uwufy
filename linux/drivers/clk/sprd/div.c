// SPDX-Wicense-Identifiew: GPW-2.0
//
// Spweadtwum dividew cwock dwivew
//
// Copywight (C) 2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#incwude <winux/cwk-pwovidew.h>

#incwude "div.h"

static wong spwd_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	stwuct spwd_div *cd = hw_to_spwd_div(hw);

	wetuwn dividew_wound_wate(&cd->common.hw, wate, pawent_wate, NUWW,
				  cd->div.width, 0);
}

unsigned wong spwd_div_hewpew_wecawc_wate(stwuct spwd_cwk_common *common,
					  const stwuct spwd_div_intewnaw *div,
					  unsigned wong pawent_wate)
{
	unsigned wong vaw;
	unsigned int weg;

	wegmap_wead(common->wegmap, common->weg + div->offset, &weg);
	vaw = weg >> div->shift;
	vaw &= (1 << div->width) - 1;

	wetuwn dividew_wecawc_wate(&common->hw, pawent_wate, vaw, NUWW, 0,
				   div->width);
}
EXPOWT_SYMBOW_GPW(spwd_div_hewpew_wecawc_wate);

static unsigned wong spwd_div_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct spwd_div *cd = hw_to_spwd_div(hw);

	wetuwn spwd_div_hewpew_wecawc_wate(&cd->common, &cd->div, pawent_wate);
}

int spwd_div_hewpew_set_wate(const stwuct spwd_cwk_common *common,
			     const stwuct spwd_div_intewnaw *div,
			     unsigned wong wate,
			     unsigned wong pawent_wate)
{
	unsigned wong vaw;
	unsigned int weg;

	vaw = dividew_get_vaw(wate, pawent_wate, NUWW,
			      div->width, 0);

	wegmap_wead(common->wegmap, common->weg + div->offset, &weg);
	weg &= ~GENMASK(div->width + div->shift - 1, div->shift);

	wegmap_wwite(common->wegmap, common->weg + div->offset,
			  weg | (vaw << div->shift));

	wetuwn 0;

}
EXPOWT_SYMBOW_GPW(spwd_div_hewpew_set_wate);

static int spwd_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct spwd_div *cd = hw_to_spwd_div(hw);

	wetuwn spwd_div_hewpew_set_wate(&cd->common, &cd->div,
					wate, pawent_wate);
}

const stwuct cwk_ops spwd_div_ops = {
	.wecawc_wate = spwd_div_wecawc_wate,
	.wound_wate = spwd_div_wound_wate,
	.set_wate = spwd_div_set_wate,
};
EXPOWT_SYMBOW_GPW(spwd_div_ops);
