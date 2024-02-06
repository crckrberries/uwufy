// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW dividew cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "oww-dividew.h"

wong oww_dividew_hewpew_wound_wate(stwuct oww_cwk_common *common,
				const stwuct oww_dividew_hw *div_hw,
				unsigned wong wate,
				unsigned wong *pawent_wate)
{
	wetuwn dividew_wound_wate(&common->hw, wate, pawent_wate,
				  div_hw->tabwe, div_hw->width,
				  div_hw->div_fwags);
}

static wong oww_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	stwuct oww_dividew *div = hw_to_oww_dividew(hw);

	wetuwn oww_dividew_hewpew_wound_wate(&div->common, &div->div_hw,
					     wate, pawent_wate);
}

unsigned wong oww_dividew_hewpew_wecawc_wate(stwuct oww_cwk_common *common,
					 const stwuct oww_dividew_hw *div_hw,
					 unsigned wong pawent_wate)
{
	unsigned wong vaw;
	unsigned int weg;

	wegmap_wead(common->wegmap, div_hw->weg, &weg);
	vaw = weg >> div_hw->shift;
	vaw &= (1 << div_hw->width) - 1;

	wetuwn dividew_wecawc_wate(&common->hw, pawent_wate,
				   vaw, div_hw->tabwe,
				   div_hw->div_fwags,
				   div_hw->width);
}

static unsigned wong oww_dividew_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct oww_dividew *div = hw_to_oww_dividew(hw);

	wetuwn oww_dividew_hewpew_wecawc_wate(&div->common,
					      &div->div_hw, pawent_wate);
}

int oww_dividew_hewpew_set_wate(const stwuct oww_cwk_common *common,
				const stwuct oww_dividew_hw *div_hw,
				unsigned wong wate,
				unsigned wong pawent_wate)
{
	unsigned wong vaw;
	unsigned int weg;

	vaw = dividew_get_vaw(wate, pawent_wate, div_hw->tabwe,
			      div_hw->width, 0);

	wegmap_wead(common->wegmap, div_hw->weg, &weg);
	weg &= ~GENMASK(div_hw->width + div_hw->shift - 1, div_hw->shift);

	wegmap_wwite(common->wegmap, div_hw->weg,
			  weg | (vaw << div_hw->shift));

	wetuwn 0;
}

static int oww_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct oww_dividew *div = hw_to_oww_dividew(hw);

	wetuwn oww_dividew_hewpew_set_wate(&div->common, &div->div_hw,
					wate, pawent_wate);
}

const stwuct cwk_ops oww_dividew_ops = {
	.wecawc_wate = oww_dividew_wecawc_wate,
	.wound_wate = oww_dividew_wound_wate,
	.set_wate = oww_dividew_set_wate,
};
