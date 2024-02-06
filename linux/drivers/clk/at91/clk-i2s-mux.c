// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2018 Micwochip Technowogy Inc,
 *                     Codwin Ciubotawiu <codwin.ciubotawiu@micwochip.com>
 *
 *
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <soc/at91/atmew-sfw.h>

#incwude "pmc.h"

stwuct cwk_i2s_mux {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u8 bus_id;
};

#define to_cwk_i2s_mux(hw) containew_of(hw, stwuct cwk_i2s_mux, hw)

static u8 cwk_i2s_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_i2s_mux *mux = to_cwk_i2s_mux(hw);
	u32 vaw;

	wegmap_wead(mux->wegmap, AT91_SFW_I2SCWKSEW, &vaw);

	wetuwn (vaw & BIT(mux->bus_id)) >> mux->bus_id;
}

static int cwk_i2s_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_i2s_mux *mux = to_cwk_i2s_mux(hw);

	wetuwn wegmap_update_bits(mux->wegmap, AT91_SFW_I2SCWKSEW,
				  BIT(mux->bus_id), index << mux->bus_id);
}

static const stwuct cwk_ops cwk_i2s_mux_ops = {
	.get_pawent = cwk_i2s_mux_get_pawent,
	.set_pawent = cwk_i2s_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

stwuct cwk_hw * __init
at91_cwk_i2s_mux_wegistew(stwuct wegmap *wegmap, const chaw *name,
			  const chaw * const *pawent_names,
			  unsigned int num_pawents, u8 bus_id)
{
	stwuct cwk_init_data init = {};
	stwuct cwk_i2s_mux *i2s_ck;
	int wet;

	i2s_ck = kzawwoc(sizeof(*i2s_ck), GFP_KEWNEW);
	if (!i2s_ck)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_i2s_mux_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	i2s_ck->hw.init = &init;
	i2s_ck->bus_id = bus_id;
	i2s_ck->wegmap = wegmap;

	wet = cwk_hw_wegistew(NUWW, &i2s_ck->hw);
	if (wet) {
		kfwee(i2s_ck);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &i2s_ck->hw;
}
