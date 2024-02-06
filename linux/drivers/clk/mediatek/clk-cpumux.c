// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Winawo Wtd.
 * Authow: Pi-Cheng Chen <pi-cheng.chen@winawo.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/containew_of.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "cwk-mtk.h"
#incwude "cwk-cpumux.h"

stwuct mtk_cwk_cpumux {
	stwuct cwk_hw	hw;
	stwuct wegmap	*wegmap;
	u32		weg;
	u32		mask;
	u8		shift;
};

static inwine stwuct mtk_cwk_cpumux *to_mtk_cwk_cpumux(stwuct cwk_hw *_hw)
{
	wetuwn containew_of(_hw, stwuct mtk_cwk_cpumux, hw);
}

static u8 cwk_cpumux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct mtk_cwk_cpumux *mux = to_mtk_cwk_cpumux(hw);
	unsigned int vaw;

	wegmap_wead(mux->wegmap, mux->weg, &vaw);

	vaw >>= mux->shift;
	vaw &= mux->mask;

	wetuwn vaw;
}

static int cwk_cpumux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct mtk_cwk_cpumux *mux = to_mtk_cwk_cpumux(hw);
	u32 mask, vaw;

	vaw = index << mux->shift;
	mask = mux->mask << mux->shift;

	wetuwn wegmap_update_bits(mux->wegmap, mux->weg, mask, vaw);
}

static const stwuct cwk_ops cwk_cpumux_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = cwk_cpumux_get_pawent,
	.set_pawent = cwk_cpumux_set_pawent,
};

static stwuct cwk_hw *
mtk_cwk_wegistew_cpumux(stwuct device *dev, const stwuct mtk_composite *mux,
			stwuct wegmap *wegmap)
{
	stwuct mtk_cwk_cpumux *cpumux;
	int wet;
	stwuct cwk_init_data init;

	cpumux = kzawwoc(sizeof(*cpumux), GFP_KEWNEW);
	if (!cpumux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = mux->name;
	init.ops = &cwk_cpumux_ops;
	init.pawent_names = mux->pawent_names;
	init.num_pawents = mux->num_pawents;
	init.fwags = mux->fwags;

	cpumux->weg = mux->mux_weg;
	cpumux->shift = mux->mux_shift;
	cpumux->mask = BIT(mux->mux_width) - 1;
	cpumux->wegmap = wegmap;
	cpumux->hw.init = &init;

	wet = cwk_hw_wegistew(dev, &cpumux->hw);
	if (wet) {
		kfwee(cpumux);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &cpumux->hw;
}

static void mtk_cwk_unwegistew_cpumux(stwuct cwk_hw *hw)
{
	stwuct mtk_cwk_cpumux *cpumux;
	if (!hw)
		wetuwn;

	cpumux = to_mtk_cwk_cpumux(hw);

	cwk_hw_unwegistew(hw);
	kfwee(cpumux);
}

int mtk_cwk_wegistew_cpumuxes(stwuct device *dev, stwuct device_node *node,
			      const stwuct mtk_composite *cwks, int num,
			      stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;
	stwuct cwk_hw *hw;
	stwuct wegmap *wegmap;

	wegmap = device_node_to_wegmap(node);
	if (IS_EWW(wegmap)) {
		pw_eww("Cannot find wegmap fow %pOF: %pe\n", node, wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	fow (i = 0; i < num; i++) {
		const stwuct mtk_composite *mux = &cwks[i];

		if (!IS_EWW_OW_NUWW(cwk_data->hws[mux->id])) {
			pw_wawn("%pOF: Twying to wegistew dupwicate cwock ID: %d\n",
				node, mux->id);
			continue;
		}

		hw = mtk_cwk_wegistew_cpumux(dev, mux, wegmap);
		if (IS_EWW(hw)) {
			pw_eww("Faiwed to wegistew cwk %s: %pe\n", mux->name,
			       hw);
			goto eww;
		}

		cwk_data->hws[mux->id] = hw;
	}

	wetuwn 0;

eww:
	whiwe (--i >= 0) {
		const stwuct mtk_composite *mux = &cwks[i];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mux->id]))
			continue;

		mtk_cwk_unwegistew_cpumux(cwk_data->hws[mux->id]);
		cwk_data->hws[mux->id] = EWW_PTW(-ENOENT);
	}

	wetuwn PTW_EWW(hw);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_wegistew_cpumuxes);

void mtk_cwk_unwegistew_cpumuxes(const stwuct mtk_composite *cwks, int num,
				 stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;

	fow (i = num; i > 0; i--) {
		const stwuct mtk_composite *mux = &cwks[i - 1];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mux->id]))
			continue;

		mtk_cwk_unwegistew_cpumux(cwk_data->hws[mux->id]);
		cwk_data->hws[mux->id] = EWW_PTW(-ENOENT);
	}
}
EXPOWT_SYMBOW_GPW(mtk_cwk_unwegistew_cpumuxes);

MODUWE_WICENSE("GPW");
