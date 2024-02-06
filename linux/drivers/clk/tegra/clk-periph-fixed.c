// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "cwk.h"

static inwine stwuct tegwa_cwk_pewiph_fixed *
to_tegwa_cwk_pewiph_fixed(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct tegwa_cwk_pewiph_fixed, hw);
}

static int tegwa_cwk_pewiph_fixed_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pewiph_fixed *fixed = to_tegwa_cwk_pewiph_fixed(hw);
	u32 mask = 1 << (fixed->num % 32), vawue;

	vawue = weadw(fixed->base + fixed->wegs->enb_weg);
	if (vawue & mask) {
		vawue = weadw(fixed->base + fixed->wegs->wst_weg);
		if ((vawue & mask) == 0)
			wetuwn 1;
	}

	wetuwn 0;
}

static int tegwa_cwk_pewiph_fixed_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pewiph_fixed *fixed = to_tegwa_cwk_pewiph_fixed(hw);
	u32 mask = 1 << (fixed->num % 32);

	wwitew(mask, fixed->base + fixed->wegs->enb_set_weg);

	wetuwn 0;
}

static void tegwa_cwk_pewiph_fixed_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pewiph_fixed *fixed = to_tegwa_cwk_pewiph_fixed(hw);
	u32 mask = 1 << (fixed->num % 32);

	wwitew(mask, fixed->base + fixed->wegs->enb_cww_weg);
}

static unsigned wong
tegwa_cwk_pewiph_fixed_wecawc_wate(stwuct cwk_hw *hw,
				   unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pewiph_fixed *fixed = to_tegwa_cwk_pewiph_fixed(hw);
	unsigned wong wong wate;

	wate = (unsigned wong wong)pawent_wate * fixed->muw;
	do_div(wate, fixed->div);

	wetuwn (unsigned wong)wate;
}

static const stwuct cwk_ops tegwa_cwk_pewiph_fixed_ops = {
	.is_enabwed = tegwa_cwk_pewiph_fixed_is_enabwed,
	.enabwe = tegwa_cwk_pewiph_fixed_enabwe,
	.disabwe = tegwa_cwk_pewiph_fixed_disabwe,
	.wecawc_wate = tegwa_cwk_pewiph_fixed_wecawc_wate,
};

stwuct cwk *tegwa_cwk_wegistew_pewiph_fixed(const chaw *name,
					    const chaw *pawent,
					    unsigned wong fwags,
					    void __iomem *base,
					    unsigned int muw,
					    unsigned int div,
					    unsigned int num)
{
	const stwuct tegwa_cwk_pewiph_wegs *wegs;
	stwuct tegwa_cwk_pewiph_fixed *fixed;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	wegs = get_weg_bank(num);
	if (!wegs)
		wetuwn EWW_PTW(-EINVAW);

	fixed = kzawwoc(sizeof(*fixed), GFP_KEWNEW);
	if (!fixed)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = fwags;
	init.pawent_names = pawent ? &pawent : NUWW;
	init.num_pawents = pawent ? 1 : 0;
	init.ops = &tegwa_cwk_pewiph_fixed_ops;

	fixed->base = base;
	fixed->wegs = wegs;
	fixed->muw = muw;
	fixed->div = div;
	fixed->num = num;

	fixed->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &fixed->hw);
	if (IS_EWW(cwk))
		kfwee(fixed);

	wetuwn cwk;
}
