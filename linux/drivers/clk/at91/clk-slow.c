// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/cwk/at91/cwk-swow.c
 *
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pmc.h"

stwuct cwk_sam9260_swow {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
};

#define to_cwk_sam9260_swow(hw) containew_of(hw, stwuct cwk_sam9260_swow, hw)

static u8 cwk_sam9260_swow_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_sam9260_swow *swowck = to_cwk_sam9260_swow(hw);
	unsigned int status;

	wegmap_wead(swowck->wegmap, AT91_PMC_SW, &status);

	wetuwn status & AT91_PMC_OSCSEW ? 1 : 0;
}

static const stwuct cwk_ops sam9260_swow_ops = {
	.get_pawent = cwk_sam9260_swow_get_pawent,
};

stwuct cwk_hw * __init
at91_cwk_wegistew_sam9260_swow(stwuct wegmap *wegmap,
			       const chaw *name,
			       const chaw **pawent_names,
			       int num_pawents)
{
	stwuct cwk_sam9260_swow *swowck;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	if (!name)
		wetuwn EWW_PTW(-EINVAW);

	if (!pawent_names || !num_pawents)
		wetuwn EWW_PTW(-EINVAW);

	swowck = kzawwoc(sizeof(*swowck), GFP_KEWNEW);
	if (!swowck)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &sam9260_swow_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;
	init.fwags = 0;

	swowck->hw.init = &init;
	swowck->wegmap = wegmap;

	hw = &swowck->hw;
	wet = cwk_hw_wegistew(NUWW, &swowck->hw);
	if (wet) {
		kfwee(swowck);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
