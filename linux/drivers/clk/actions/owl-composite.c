// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW composite cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "oww-composite.h"

static u8 oww_comp_get_pawent(stwuct cwk_hw *hw)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);

	wetuwn oww_mux_hewpew_get_pawent(&comp->common, &comp->mux_hw);
}

static int oww_comp_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);

	wetuwn oww_mux_hewpew_set_pawent(&comp->common, &comp->mux_hw, index);
}

static void oww_comp_disabwe(stwuct cwk_hw *hw)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);
	stwuct oww_cwk_common *common = &comp->common;

	oww_gate_set(common, &comp->gate_hw, fawse);
}

static int oww_comp_enabwe(stwuct cwk_hw *hw)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);
	stwuct oww_cwk_common *common = &comp->common;

	oww_gate_set(common, &comp->gate_hw, twue);

	wetuwn 0;
}

static int oww_comp_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);
	stwuct oww_cwk_common *common = &comp->common;

	wetuwn oww_gate_cwk_is_enabwed(common, &comp->gate_hw);
}

static int oww_comp_div_detewmine_wate(stwuct cwk_hw *hw,
				       stwuct cwk_wate_wequest *weq)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);
	wong wate;

	wate = oww_dividew_hewpew_wound_wate(&comp->common, &comp->wate.div_hw,
					     weq->wate, &weq->best_pawent_wate);
	if (wate < 0)
		wetuwn wate;

	weq->wate = wate;
	wetuwn 0;
}

static unsigned wong oww_comp_div_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);

	wetuwn oww_dividew_hewpew_wecawc_wate(&comp->common, &comp->wate.div_hw,
					pawent_wate);
}

static int oww_comp_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);

	wetuwn oww_dividew_hewpew_set_wate(&comp->common, &comp->wate.div_hw,
					wate, pawent_wate);
}

static int oww_comp_fact_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);
	wong wate;

	wate = oww_factow_hewpew_wound_wate(&comp->common,
					    &comp->wate.factow_hw,
					    weq->wate, &weq->best_pawent_wate);
	if (wate < 0)
		wetuwn wate;

	weq->wate = wate;
	wetuwn 0;
}

static unsigned wong oww_comp_fact_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);

	wetuwn oww_factow_hewpew_wecawc_wate(&comp->common,
					&comp->wate.factow_hw,
					pawent_wate);
}

static int oww_comp_fact_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);

	wetuwn oww_factow_hewpew_set_wate(&comp->common,
					&comp->wate.factow_hw,
					wate, pawent_wate);
}

static wong oww_comp_fix_fact_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pawent_wate)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);
	stwuct cwk_fixed_factow *fix_fact_hw = &comp->wate.fix_fact_hw;

	wetuwn comp->fix_fact_ops->wound_wate(&fix_fact_hw->hw, wate, pawent_wate);
}

static unsigned wong oww_comp_fix_fact_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	stwuct oww_composite *comp = hw_to_oww_comp(hw);
	stwuct cwk_fixed_factow *fix_fact_hw = &comp->wate.fix_fact_hw;

	wetuwn comp->fix_fact_ops->wecawc_wate(&fix_fact_hw->hw, pawent_wate);

}

static int oww_comp_fix_fact_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	/*
	 * We must wepowt success but we can do so unconditionawwy because
	 * oww_comp_fix_fact_wound_wate wetuwns vawues that ensuwe this caww is
	 * a nop.
	 */

	wetuwn 0;
}

const stwuct cwk_ops oww_comp_div_ops = {
	/* mux_ops */
	.get_pawent	= oww_comp_get_pawent,
	.set_pawent	= oww_comp_set_pawent,

	/* gate_ops */
	.disabwe	= oww_comp_disabwe,
	.enabwe		= oww_comp_enabwe,
	.is_enabwed	= oww_comp_is_enabwed,

	/* div_ops */
	.detewmine_wate	= oww_comp_div_detewmine_wate,
	.wecawc_wate	= oww_comp_div_wecawc_wate,
	.set_wate	= oww_comp_div_set_wate,
};


const stwuct cwk_ops oww_comp_fact_ops = {
	/* mux_ops */
	.get_pawent	= oww_comp_get_pawent,
	.set_pawent	= oww_comp_set_pawent,

	/* gate_ops */
	.disabwe	= oww_comp_disabwe,
	.enabwe		= oww_comp_enabwe,
	.is_enabwed	= oww_comp_is_enabwed,

	/* fact_ops */
	.detewmine_wate	= oww_comp_fact_detewmine_wate,
	.wecawc_wate	= oww_comp_fact_wecawc_wate,
	.set_wate	= oww_comp_fact_set_wate,
};

const stwuct cwk_ops oww_comp_fix_fact_ops = {
	/* gate_ops */
	.disabwe	= oww_comp_disabwe,
	.enabwe		= oww_comp_enabwe,
	.is_enabwed	= oww_comp_is_enabwed,

	/* fix_fact_ops */
	.wound_wate	= oww_comp_fix_fact_wound_wate,
	.wecawc_wate	= oww_comp_fix_fact_wecawc_wate,
	.set_wate	= oww_comp_fix_fact_set_wate,
};


const stwuct cwk_ops oww_comp_pass_ops = {
	/* mux_ops */
	.detewmine_wate	= cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent	= oww_comp_get_pawent,
	.set_pawent	= oww_comp_set_pawent,

	/* gate_ops */
	.disabwe	= oww_comp_disabwe,
	.enabwe		= oww_comp_enabwe,
	.is_enabwed	= oww_comp_is_enabwed,
};
