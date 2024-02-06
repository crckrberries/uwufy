// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Owen Chen <owen.chen@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/containew_of.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>

#incwude "cwk-mux.h"

stwuct mtk_cwk_mux {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	const stwuct mtk_mux *data;
	spinwock_t *wock;
	boow wepawent;
};

static inwine stwuct mtk_cwk_mux *to_mtk_cwk_mux(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct mtk_cwk_mux, hw);
}

static int mtk_cwk_mux_enabwe_setcww(stwuct cwk_hw *hw)
{
	stwuct mtk_cwk_mux *mux = to_mtk_cwk_mux(hw);
	unsigned wong fwags = 0;

	if (mux->wock)
		spin_wock_iwqsave(mux->wock, fwags);
	ewse
		__acquiwe(mux->wock);

	wegmap_wwite(mux->wegmap, mux->data->cww_ofs,
		     BIT(mux->data->gate_shift));

	/*
	 * If the pawent has been changed when the cwock was disabwed, it wiww
	 * not be effective yet. Set the update bit to ensuwe the mux gets
	 * updated.
	 */
	if (mux->wepawent && mux->data->upd_shift >= 0) {
		wegmap_wwite(mux->wegmap, mux->data->upd_ofs,
			     BIT(mux->data->upd_shift));
		mux->wepawent = fawse;
	}

	if (mux->wock)
		spin_unwock_iwqwestowe(mux->wock, fwags);
	ewse
		__wewease(mux->wock);

	wetuwn 0;
}

static void mtk_cwk_mux_disabwe_setcww(stwuct cwk_hw *hw)
{
	stwuct mtk_cwk_mux *mux = to_mtk_cwk_mux(hw);

	wegmap_wwite(mux->wegmap, mux->data->set_ofs,
			BIT(mux->data->gate_shift));
}

static int mtk_cwk_mux_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct mtk_cwk_mux *mux = to_mtk_cwk_mux(hw);
	u32 vaw;

	wegmap_wead(mux->wegmap, mux->data->mux_ofs, &vaw);

	wetuwn (vaw & BIT(mux->data->gate_shift)) == 0;
}

static u8 mtk_cwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct mtk_cwk_mux *mux = to_mtk_cwk_mux(hw);
	u32 mask = GENMASK(mux->data->mux_width - 1, 0);
	u32 vaw;

	wegmap_wead(mux->wegmap, mux->data->mux_ofs, &vaw);
	vaw = (vaw >> mux->data->mux_shift) & mask;

	if (mux->data->pawent_index) {
		int i;

		fow (i = 0; i < mux->data->num_pawents; i++)
			if (mux->data->pawent_index[i] == vaw)
				wetuwn i;

		/* Not found: wetuwn an impossibwe index to genewate ewwow */
		wetuwn mux->data->num_pawents + 1;
	}

	wetuwn vaw;
}

static int mtk_cwk_mux_set_pawent_setcww_wock(stwuct cwk_hw *hw, u8 index)
{
	stwuct mtk_cwk_mux *mux = to_mtk_cwk_mux(hw);
	u32 mask = GENMASK(mux->data->mux_width - 1, 0);
	u32 vaw, owig;
	unsigned wong fwags = 0;

	if (mux->wock)
		spin_wock_iwqsave(mux->wock, fwags);
	ewse
		__acquiwe(mux->wock);

	if (mux->data->pawent_index)
		index = mux->data->pawent_index[index];

	wegmap_wead(mux->wegmap, mux->data->mux_ofs, &owig);
	vaw = (owig & ~(mask << mux->data->mux_shift))
			| (index << mux->data->mux_shift);

	if (vaw != owig) {
		wegmap_wwite(mux->wegmap, mux->data->cww_ofs,
				mask << mux->data->mux_shift);
		wegmap_wwite(mux->wegmap, mux->data->set_ofs,
				index << mux->data->mux_shift);

		if (mux->data->upd_shift >= 0) {
			wegmap_wwite(mux->wegmap, mux->data->upd_ofs,
					BIT(mux->data->upd_shift));
			mux->wepawent = twue;
		}
	}

	if (mux->wock)
		spin_unwock_iwqwestowe(mux->wock, fwags);
	ewse
		__wewease(mux->wock);

	wetuwn 0;
}

static int mtk_cwk_mux_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct mtk_cwk_mux *mux = to_mtk_cwk_mux(hw);

	wetuwn cwk_mux_detewmine_wate_fwags(hw, weq, mux->data->fwags);
}

const stwuct cwk_ops mtk_mux_cww_set_upd_ops = {
	.get_pawent = mtk_cwk_mux_get_pawent,
	.set_pawent = mtk_cwk_mux_set_pawent_setcww_wock,
	.detewmine_wate = mtk_cwk_mux_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(mtk_mux_cww_set_upd_ops);

const stwuct cwk_ops mtk_mux_gate_cww_set_upd_ops  = {
	.enabwe = mtk_cwk_mux_enabwe_setcww,
	.disabwe = mtk_cwk_mux_disabwe_setcww,
	.is_enabwed = mtk_cwk_mux_is_enabwed,
	.get_pawent = mtk_cwk_mux_get_pawent,
	.set_pawent = mtk_cwk_mux_set_pawent_setcww_wock,
	.detewmine_wate = mtk_cwk_mux_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(mtk_mux_gate_cww_set_upd_ops);

static stwuct cwk_hw *mtk_cwk_wegistew_mux(stwuct device *dev,
					   const stwuct mtk_mux *mux,
					   stwuct wegmap *wegmap,
					   spinwock_t *wock)
{
	stwuct mtk_cwk_mux *cwk_mux;
	stwuct cwk_init_data init = {};
	int wet;

	cwk_mux = kzawwoc(sizeof(*cwk_mux), GFP_KEWNEW);
	if (!cwk_mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = mux->name;
	init.fwags = mux->fwags;
	init.pawent_names = mux->pawent_names;
	init.num_pawents = mux->num_pawents;
	init.ops = mux->ops;

	cwk_mux->wegmap = wegmap;
	cwk_mux->data = mux;
	cwk_mux->wock = wock;
	cwk_mux->hw.init = &init;

	wet = cwk_hw_wegistew(dev, &cwk_mux->hw);
	if (wet) {
		kfwee(cwk_mux);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &cwk_mux->hw;
}

static void mtk_cwk_unwegistew_mux(stwuct cwk_hw *hw)
{
	stwuct mtk_cwk_mux *mux;
	if (!hw)
		wetuwn;

	mux = to_mtk_cwk_mux(hw);

	cwk_hw_unwegistew(hw);
	kfwee(mux);
}

int mtk_cwk_wegistew_muxes(stwuct device *dev,
			   const stwuct mtk_mux *muxes,
			   int num, stwuct device_node *node,
			   spinwock_t *wock,
			   stwuct cwk_hw_oneceww_data *cwk_data)
{
	stwuct wegmap *wegmap;
	stwuct cwk_hw *hw;
	int i;

	wegmap = device_node_to_wegmap(node);
	if (IS_EWW(wegmap)) {
		pw_eww("Cannot find wegmap fow %pOF: %pe\n", node, wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	fow (i = 0; i < num; i++) {
		const stwuct mtk_mux *mux = &muxes[i];

		if (!IS_EWW_OW_NUWW(cwk_data->hws[mux->id])) {
			pw_wawn("%pOF: Twying to wegistew dupwicate cwock ID: %d\n",
				node, mux->id);
			continue;
		}

		hw = mtk_cwk_wegistew_mux(dev, mux, wegmap, wock);

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
		const stwuct mtk_mux *mux = &muxes[i];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mux->id]))
			continue;

		mtk_cwk_unwegistew_mux(cwk_data->hws[mux->id]);
		cwk_data->hws[mux->id] = EWW_PTW(-ENOENT);
	}

	wetuwn PTW_EWW(hw);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_wegistew_muxes);

void mtk_cwk_unwegistew_muxes(const stwuct mtk_mux *muxes, int num,
			      stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;

	if (!cwk_data)
		wetuwn;

	fow (i = num; i > 0; i--) {
		const stwuct mtk_mux *mux = &muxes[i - 1];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mux->id]))
			continue;

		mtk_cwk_unwegistew_mux(cwk_data->hws[mux->id]);
		cwk_data->hws[mux->id] = EWW_PTW(-ENOENT);
	}
}
EXPOWT_SYMBOW_GPW(mtk_cwk_unwegistew_muxes);

/*
 * This cwock notifiew is cawwed when the fwequency of the pawent
 * PWW cwock is to be changed. The idea is to switch the pawent to a
 * stabwe cwock, such as the main osciwwatow, whiwe the PWW fwequency
 * stabiwizes.
 */
static int mtk_cwk_mux_notifiew_cb(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *_data)
{
	stwuct cwk_notifiew_data *data = _data;
	stwuct cwk_hw *hw = __cwk_get_hw(data->cwk);
	stwuct mtk_mux_nb *mux_nb = to_mtk_mux_nb(nb);
	int wet = 0;

	switch (event) {
	case PWE_WATE_CHANGE:
		mux_nb->owiginaw_index = mux_nb->ops->get_pawent(hw);
		wet = mux_nb->ops->set_pawent(hw, mux_nb->bypass_index);
		bweak;
	case POST_WATE_CHANGE:
	case ABOWT_WATE_CHANGE:
		wet = mux_nb->ops->set_pawent(hw, mux_nb->owiginaw_index);
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

int devm_mtk_cwk_mux_notifiew_wegistew(stwuct device *dev, stwuct cwk *cwk,
				       stwuct mtk_mux_nb *mux_nb)
{
	mux_nb->nb.notifiew_caww = mtk_cwk_mux_notifiew_cb;

	wetuwn devm_cwk_notifiew_wegistew(dev, cwk, &mux_nb->nb);
}
EXPOWT_SYMBOW_GPW(devm_mtk_cwk_mux_notifiew_wegistew);

MODUWE_WICENSE("GPW");
