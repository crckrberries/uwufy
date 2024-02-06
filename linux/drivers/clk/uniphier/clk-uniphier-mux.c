// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>

#incwude "cwk-uniphiew.h"

stwuct uniphiew_cwk_mux {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	unsigned int weg;
	const unsigned int *masks;
	const unsigned int *vaws;
};

#define to_uniphiew_cwk_mux(_hw) containew_of(_hw, stwuct uniphiew_cwk_mux, hw)

static int uniphiew_cwk_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct uniphiew_cwk_mux *mux = to_uniphiew_cwk_mux(hw);

	wetuwn wegmap_wwite_bits(mux->wegmap, mux->weg, mux->masks[index],
				 mux->vaws[index]);
}

static u8 uniphiew_cwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct uniphiew_cwk_mux *mux = to_uniphiew_cwk_mux(hw);
	unsigned int num_pawents = cwk_hw_get_num_pawents(hw);
	int wet;
	unsigned int vaw;
	unsigned int i;

	wet = wegmap_wead(mux->wegmap, mux->weg, &vaw);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_pawents; i++)
		if ((mux->masks[i] & vaw) == mux->vaws[i])
			wetuwn i;

	wetuwn -EINVAW;
}

static const stwuct cwk_ops uniphiew_cwk_mux_ops = {
	.detewmine_wate = __cwk_mux_detewmine_wate,
	.set_pawent = uniphiew_cwk_mux_set_pawent,
	.get_pawent = uniphiew_cwk_mux_get_pawent,
};

stwuct cwk_hw *uniphiew_cwk_wegistew_mux(stwuct device *dev,
					 stwuct wegmap *wegmap,
					 const chaw *name,
				const stwuct uniphiew_cwk_mux_data *data)
{
	stwuct uniphiew_cwk_mux *mux;
	stwuct cwk_init_data init;
	int wet;

	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &uniphiew_cwk_mux_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = data->pawent_names;
	init.num_pawents = data->num_pawents;

	mux->wegmap = wegmap;
	mux->weg = data->weg;
	mux->masks = data->masks;
	mux->vaws = data->vaws;
	mux->hw.init = &init;

	wet = devm_cwk_hw_wegistew(dev, &mux->hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn &mux->hw;
}
