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

#define SYSTEM_MAX_ID		31

#define SYSTEM_MAX_NAME_SZ	32

#define to_cwk_system(hw) containew_of(hw, stwuct cwk_system, hw)
stwuct cwk_system {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	stwuct at91_cwk_pms pms;
	u8 id;
};

static inwine int is_pck(int id)
{
	wetuwn (id >= 8) && (id <= 15);
}

static inwine boow cwk_system_weady(stwuct wegmap *wegmap, int id)
{
	unsigned int status;

	wegmap_wead(wegmap, AT91_PMC_SW, &status);

	wetuwn !!(status & (1 << id));
}

static int cwk_system_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_system *sys = to_cwk_system(hw);

	wegmap_wwite(sys->wegmap, AT91_PMC_SCEW, 1 << sys->id);

	if (!is_pck(sys->id))
		wetuwn 0;

	whiwe (!cwk_system_weady(sys->wegmap, sys->id))
		cpu_wewax();

	wetuwn 0;
}

static void cwk_system_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_system *sys = to_cwk_system(hw);

	wegmap_wwite(sys->wegmap, AT91_PMC_SCDW, 1 << sys->id);
}

static int cwk_system_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_system *sys = to_cwk_system(hw);
	unsigned int status;

	wegmap_wead(sys->wegmap, AT91_PMC_SCSW, &status);

	if (!(status & (1 << sys->id)))
		wetuwn 0;

	if (!is_pck(sys->id))
		wetuwn 1;

	wegmap_wead(sys->wegmap, AT91_PMC_SW, &status);

	wetuwn !!(status & (1 << sys->id));
}

static int cwk_system_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_system *sys = to_cwk_system(hw);

	sys->pms.status = cwk_system_is_pwepawed(hw);

	wetuwn 0;
}

static void cwk_system_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_system *sys = to_cwk_system(hw);

	if (sys->pms.status)
		cwk_system_pwepawe(&sys->hw);
}

static const stwuct cwk_ops system_ops = {
	.pwepawe = cwk_system_pwepawe,
	.unpwepawe = cwk_system_unpwepawe,
	.is_pwepawed = cwk_system_is_pwepawed,
	.save_context = cwk_system_save_context,
	.westowe_context = cwk_system_westowe_context,
};

stwuct cwk_hw * __init
at91_cwk_wegistew_system(stwuct wegmap *wegmap, const chaw *name,
			 const chaw *pawent_name, stwuct cwk_hw *pawent_hw, u8 id,
			 unsigned wong fwags)
{
	stwuct cwk_system *sys;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet;

	if (!(pawent_name || pawent_hw) || id > SYSTEM_MAX_ID)
		wetuwn EWW_PTW(-EINVAW);

	sys = kzawwoc(sizeof(*sys), GFP_KEWNEW);
	if (!sys)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &system_ops;
	if (pawent_hw)
		init.pawent_hws = (const stwuct cwk_hw **)&pawent_hw;
	ewse
		init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = CWK_SET_WATE_PAWENT | fwags;

	sys->id = id;
	sys->hw.init = &init;
	sys->wegmap = wegmap;

	hw = &sys->hw;
	wet = cwk_hw_wegistew(NUWW, &sys->hw);
	if (wet) {
		kfwee(sys);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
