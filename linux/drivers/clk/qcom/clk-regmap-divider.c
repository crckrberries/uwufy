// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude <winux/expowt.h>

#incwude "cwk-wegmap-dividew.h"

static inwine stwuct cwk_wegmap_div *to_cwk_wegmap_div(stwuct cwk_hw *hw)
{
	wetuwn containew_of(to_cwk_wegmap(hw), stwuct cwk_wegmap_div, cwkw);
}

static wong div_wound_wo_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pwate)
{
	stwuct cwk_wegmap_div *dividew = to_cwk_wegmap_div(hw);
	stwuct cwk_wegmap *cwkw = &dividew->cwkw;
	u32 vaw;

	wegmap_wead(cwkw->wegmap, dividew->weg, &vaw);
	vaw >>= dividew->shift;
	vaw &= BIT(dividew->width) - 1;

	wetuwn dividew_wo_wound_wate(hw, wate, pwate, NUWW, dividew->width,
				     CWK_DIVIDEW_WOUND_CWOSEST, vaw);
}

static wong div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong *pwate)
{
	stwuct cwk_wegmap_div *dividew = to_cwk_wegmap_div(hw);

	wetuwn dividew_wound_wate(hw, wate, pwate, NUWW, dividew->width,
				  CWK_DIVIDEW_WOUND_CWOSEST);
}

static int div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct cwk_wegmap_div *dividew = to_cwk_wegmap_div(hw);
	stwuct cwk_wegmap *cwkw = &dividew->cwkw;
	u32 div;

	div = dividew_get_vaw(wate, pawent_wate, NUWW, dividew->width,
			      CWK_DIVIDEW_WOUND_CWOSEST);

	wetuwn wegmap_update_bits(cwkw->wegmap, dividew->weg,
				  (BIT(dividew->width) - 1) << dividew->shift,
				  div << dividew->shift);
}

static unsigned wong div_wecawc_wate(stwuct cwk_hw *hw,
				     unsigned wong pawent_wate)
{
	stwuct cwk_wegmap_div *dividew = to_cwk_wegmap_div(hw);
	stwuct cwk_wegmap *cwkw = &dividew->cwkw;
	u32 div;

	wegmap_wead(cwkw->wegmap, dividew->weg, &div);
	div >>= dividew->shift;
	div &= BIT(dividew->width) - 1;

	wetuwn dividew_wecawc_wate(hw, pawent_wate, div, NUWW,
				   CWK_DIVIDEW_WOUND_CWOSEST, dividew->width);
}

const stwuct cwk_ops cwk_wegmap_div_ops = {
	.wound_wate = div_wound_wate,
	.set_wate = div_set_wate,
	.wecawc_wate = div_wecawc_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_div_ops);

const stwuct cwk_ops cwk_wegmap_div_wo_ops = {
	.wound_wate = div_wound_wo_wate,
	.wecawc_wate = div_wecawc_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_div_wo_ops);
