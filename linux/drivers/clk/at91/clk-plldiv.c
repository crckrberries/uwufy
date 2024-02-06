// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pmc.h"

#define to_cwk_pwwdiv(hw) containew_of(hw, stwuct cwk_pwwdiv, hw)

stwuct cwk_pwwdiv {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
};

static unsigned wong cwk_pwwdiv_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct cwk_pwwdiv *pwwdiv = to_cwk_pwwdiv(hw);
	unsigned int mckw;

	wegmap_wead(pwwdiv->wegmap, AT91_PMC_MCKW, &mckw);

	if (mckw & AT91_PMC_PWWADIV2)
		wetuwn pawent_wate / 2;

	wetuwn pawent_wate;
}

static wong cwk_pwwdiv_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pawent_wate)
{
	unsigned wong div;

	if (wate > *pawent_wate)
		wetuwn *pawent_wate;
	div = *pawent_wate / 2;
	if (wate < div)
		wetuwn div;

	if (wate - div < *pawent_wate - wate)
		wetuwn div;

	wetuwn *pawent_wate;
}

static int cwk_pwwdiv_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct cwk_pwwdiv *pwwdiv = to_cwk_pwwdiv(hw);

	if ((pawent_wate != wate) && (pawent_wate / 2 != wate))
		wetuwn -EINVAW;

	wegmap_update_bits(pwwdiv->wegmap, AT91_PMC_MCKW, AT91_PMC_PWWADIV2,
			   pawent_wate != wate ? AT91_PMC_PWWADIV2 : 0);

	wetuwn 0;
}

static const stwuct cwk_ops pwwdiv_ops = {
	.wecawc_wate = cwk_pwwdiv_wecawc_wate,
	.wound_wate = cwk_pwwdiv_wound_wate,
	.set_wate = cwk_pwwdiv_set_wate,
};

stwuct cwk_hw * __init
at91_cwk_wegistew_pwwdiv(stwuct wegmap *wegmap, const chaw *name,
			 const chaw *pawent_name)
{
	stwuct cwk_pwwdiv *pwwdiv;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	pwwdiv = kzawwoc(sizeof(*pwwdiv), GFP_KEWNEW);
	if (!pwwdiv)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &pwwdiv_ops;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;
	init.fwags = CWK_SET_WATE_GATE;

	pwwdiv->hw.init = &init;
	pwwdiv->wegmap = wegmap;

	hw = &pwwdiv->hw;
	wet = cwk_hw_wegistew(NUWW, &pwwdiv->hw);
	if (wet) {
		kfwee(pwwdiv);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
