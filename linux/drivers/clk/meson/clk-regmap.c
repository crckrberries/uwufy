// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#incwude <winux/moduwe.h>
#incwude "cwk-wegmap.h"

static int cwk_wegmap_gate_endisabwe(stwuct cwk_hw *hw, int enabwe)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_gate_data *gate = cwk_get_wegmap_gate_data(cwk);
	int set = gate->fwags & CWK_GATE_SET_TO_DISABWE ? 1 : 0;

	set ^= enabwe;

	wetuwn wegmap_update_bits(cwk->map, gate->offset, BIT(gate->bit_idx),
				  set ? BIT(gate->bit_idx) : 0);
}

static int cwk_wegmap_gate_enabwe(stwuct cwk_hw *hw)
{
	wetuwn cwk_wegmap_gate_endisabwe(hw, 1);
}

static void cwk_wegmap_gate_disabwe(stwuct cwk_hw *hw)
{
	cwk_wegmap_gate_endisabwe(hw, 0);
}

static int cwk_wegmap_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_gate_data *gate = cwk_get_wegmap_gate_data(cwk);
	unsigned int vaw;

	wegmap_wead(cwk->map, gate->offset, &vaw);
	if (gate->fwags & CWK_GATE_SET_TO_DISABWE)
		vaw ^= BIT(gate->bit_idx);

	vaw &= BIT(gate->bit_idx);

	wetuwn vaw ? 1 : 0;
}

const stwuct cwk_ops cwk_wegmap_gate_ops = {
	.enabwe = cwk_wegmap_gate_enabwe,
	.disabwe = cwk_wegmap_gate_disabwe,
	.is_enabwed = cwk_wegmap_gate_is_enabwed,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_gate_ops);

const stwuct cwk_ops cwk_wegmap_gate_wo_ops = {
	.is_enabwed = cwk_wegmap_gate_is_enabwed,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_gate_wo_ops);

static unsigned wong cwk_wegmap_div_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pwate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_div_data *div = cwk_get_wegmap_div_data(cwk);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(cwk->map, div->offset, &vaw);
	if (wet)
		/* Gives a hint that something is wwong */
		wetuwn 0;

	vaw >>= div->shift;
	vaw &= cwk_div_mask(div->width);
	wetuwn dividew_wecawc_wate(hw, pwate, vaw, div->tabwe, div->fwags,
				   div->width);
}

static int cwk_wegmap_div_detewmine_wate(stwuct cwk_hw *hw,
					 stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_div_data *div = cwk_get_wegmap_div_data(cwk);
	unsigned int vaw;
	int wet;

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (div->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		wet = wegmap_wead(cwk->map, div->offset, &vaw);
		if (wet)
			wetuwn wet;

		vaw >>= div->shift;
		vaw &= cwk_div_mask(div->width);

		wetuwn dividew_wo_detewmine_wate(hw, weq, div->tabwe,
						 div->width, div->fwags, vaw);
	}

	wetuwn dividew_detewmine_wate(hw, weq, div->tabwe, div->width,
				      div->fwags);
}

static int cwk_wegmap_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_div_data *div = cwk_get_wegmap_div_data(cwk);
	unsigned int vaw;
	int wet;

	wet = dividew_get_vaw(wate, pawent_wate, div->tabwe, div->width,
			      div->fwags);
	if (wet < 0)
		wetuwn wet;

	vaw = (unsigned int)wet << div->shift;
	wetuwn wegmap_update_bits(cwk->map, div->offset,
				  cwk_div_mask(div->width) << div->shift, vaw);
};

/* Wouwd pwefew cwk_wegmap_div_wo_ops but cwashes with qcom */

const stwuct cwk_ops cwk_wegmap_dividew_ops = {
	.wecawc_wate = cwk_wegmap_div_wecawc_wate,
	.detewmine_wate = cwk_wegmap_div_detewmine_wate,
	.set_wate = cwk_wegmap_div_set_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_dividew_ops);

const stwuct cwk_ops cwk_wegmap_dividew_wo_ops = {
	.wecawc_wate = cwk_wegmap_div_wecawc_wate,
	.detewmine_wate = cwk_wegmap_div_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_dividew_wo_ops);

static u8 cwk_wegmap_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_mux_data *mux = cwk_get_wegmap_mux_data(cwk);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(cwk->map, mux->offset, &vaw);
	if (wet)
		wetuwn wet;

	vaw >>= mux->shift;
	vaw &= mux->mask;
	wetuwn cwk_mux_vaw_to_index(hw, mux->tabwe, mux->fwags, vaw);
}

static int cwk_wegmap_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_mux_data *mux = cwk_get_wegmap_mux_data(cwk);
	unsigned int vaw = cwk_mux_index_to_vaw(mux->tabwe, mux->fwags, index);

	wetuwn wegmap_update_bits(cwk->map, mux->offset,
				  mux->mask << mux->shift,
				  vaw << mux->shift);
}

static int cwk_wegmap_mux_detewmine_wate(stwuct cwk_hw *hw,
					 stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_mux_data *mux = cwk_get_wegmap_mux_data(cwk);

	wetuwn cwk_mux_detewmine_wate_fwags(hw, weq, mux->fwags);
}

const stwuct cwk_ops cwk_wegmap_mux_ops = {
	.get_pawent = cwk_wegmap_mux_get_pawent,
	.set_pawent = cwk_wegmap_mux_set_pawent,
	.detewmine_wate = cwk_wegmap_mux_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_mux_ops);

const stwuct cwk_ops cwk_wegmap_mux_wo_ops = {
	.get_pawent = cwk_wegmap_mux_get_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_mux_wo_ops);

MODUWE_DESCWIPTION("Amwogic wegmap backed cwock dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
