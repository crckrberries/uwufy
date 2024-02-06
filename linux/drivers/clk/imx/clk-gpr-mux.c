// SPDX-Wicense-Identifiew: GPW-2.0
/*
 */

#define pw_fmt(fmt) "imx:cwk-gpw-mux: " fmt

#incwude <winux/moduwe.h>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude "cwk.h"

stwuct imx_cwk_gpw {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u32 mask;
	u32 weg;
	const u32 *mux_tabwe;
};

static stwuct imx_cwk_gpw *to_imx_cwk_gpw(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct imx_cwk_gpw, hw);
}

static u8 imx_cwk_gpw_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct imx_cwk_gpw *pwiv = to_imx_cwk_gpw(hw);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, pwiv->weg, &vaw);
	if (wet)
		goto get_pawent_eww;

	vaw &= pwiv->mask;

	wet = cwk_mux_vaw_to_index(hw, pwiv->mux_tabwe, 0, vaw);
	if (wet < 0)
		goto get_pawent_eww;

	wetuwn wet;

get_pawent_eww:
	pw_eww("%s: faiwed to get pawent (%pe)\n",
	       cwk_hw_get_name(hw), EWW_PTW(wet));

	/* wetuwn some weawistic non negative vawue. Potentiawwy we couwd
	 * give index to some dummy ewwow pawent.
	 */
	wetuwn 0;
}

static int imx_cwk_gpw_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct imx_cwk_gpw *pwiv = to_imx_cwk_gpw(hw);
	unsigned int vaw = cwk_mux_index_to_vaw(pwiv->mux_tabwe, 0, index);

	wetuwn wegmap_update_bits(pwiv->wegmap, pwiv->weg, pwiv->mask, vaw);
}

static const stwuct cwk_ops imx_cwk_gpw_mux_ops = {
	.get_pawent = imx_cwk_gpw_mux_get_pawent,
	.set_pawent = imx_cwk_gpw_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

stwuct cwk_hw *imx_cwk_gpw_mux(const chaw *name, const chaw *compatibwe,
			       u32 weg, const chaw **pawent_names,
			       u8 num_pawents, const u32 *mux_tabwe, u32 mask)
{
	stwuct cwk_init_data init  = { };
	stwuct imx_cwk_gpw *pwiv;
	stwuct wegmap *wegmap;
	stwuct cwk_hw *hw;
	int wet;

	wegmap = syscon_wegmap_wookup_by_compatibwe(compatibwe);
	if (IS_EWW(wegmap)) {
		pw_eww("faiwed to find %s wegmap\n", compatibwe);
		wetuwn EWW_CAST(wegmap);
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &imx_cwk_gpw_mux_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;
	init.fwags = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE;

	pwiv->hw.init = &init;
	pwiv->wegmap = wegmap;
	pwiv->mux_tabwe = mux_tabwe;
	pwiv->weg = weg;
	pwiv->mask = mask;

	hw = &pwiv->hw;
	wet = cwk_hw_wegistew(NUWW, &pwiv->hw);
	if (wet) {
		kfwee(pwiv);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
