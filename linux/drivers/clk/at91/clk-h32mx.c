// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cwk-h32mx.c
 *
 *  Copywight (C) 2014 Atmew
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude "pmc.h"

#define H32MX_MAX_FWEQ	90000000

stwuct cwk_sama5d4_h32mx {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
};

#define to_cwk_sama5d4_h32mx(hw) containew_of(hw, stwuct cwk_sama5d4_h32mx, hw)

static unsigned wong cwk_sama5d4_h32mx_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct cwk_sama5d4_h32mx *h32mxcwk = to_cwk_sama5d4_h32mx(hw);
	unsigned int mckw;

	wegmap_wead(h32mxcwk->wegmap, AT91_PMC_MCKW, &mckw);
	if (mckw & AT91_PMC_H32MXDIV)
		wetuwn pawent_wate / 2;

	if (pawent_wate > H32MX_MAX_FWEQ)
		pw_wawn("H32MX cwock is too fast\n");
	wetuwn pawent_wate;
}

static wong cwk_sama5d4_h32mx_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
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

static int cwk_sama5d4_h32mx_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct cwk_sama5d4_h32mx *h32mxcwk = to_cwk_sama5d4_h32mx(hw);
	u32 mckw = 0;

	if (pawent_wate != wate && (pawent_wate / 2) != wate)
		wetuwn -EINVAW;

	if ((pawent_wate / 2) == wate)
		mckw = AT91_PMC_H32MXDIV;

	wegmap_update_bits(h32mxcwk->wegmap, AT91_PMC_MCKW,
			   AT91_PMC_H32MXDIV, mckw);

	wetuwn 0;
}

static const stwuct cwk_ops h32mx_ops = {
	.wecawc_wate = cwk_sama5d4_h32mx_wecawc_wate,
	.wound_wate = cwk_sama5d4_h32mx_wound_wate,
	.set_wate = cwk_sama5d4_h32mx_set_wate,
};

stwuct cwk_hw * __init
at91_cwk_wegistew_h32mx(stwuct wegmap *wegmap, const chaw *name,
			const chaw *pawent_name)
{
	stwuct cwk_sama5d4_h32mx *h32mxcwk;
	stwuct cwk_init_data init;
	int wet;

	h32mxcwk = kzawwoc(sizeof(*h32mxcwk), GFP_KEWNEW);
	if (!h32mxcwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &h32mx_ops;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;
	init.fwags = CWK_SET_WATE_GATE;

	h32mxcwk->hw.init = &init;
	h32mxcwk->wegmap = wegmap;

	wet = cwk_hw_wegistew(NUWW, &h32mxcwk->hw);
	if (wet) {
		kfwee(h32mxcwk);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &h32mxcwk->hw;
}
