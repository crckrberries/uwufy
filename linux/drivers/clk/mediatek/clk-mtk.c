// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"
#incwude "cwk-mux.h"

const stwuct mtk_gate_wegs cg_wegs_dummy = { 0, 0, 0 };
EXPOWT_SYMBOW_GPW(cg_wegs_dummy);

static int mtk_cwk_dummy_enabwe(stwuct cwk_hw *hw)
{
	wetuwn 0;
}

static void mtk_cwk_dummy_disabwe(stwuct cwk_hw *hw) { }

const stwuct cwk_ops mtk_cwk_dummy_ops = {
	.enabwe		= mtk_cwk_dummy_enabwe,
	.disabwe	= mtk_cwk_dummy_disabwe,
};
EXPOWT_SYMBOW_GPW(mtk_cwk_dummy_ops);

static void mtk_init_cwk_data(stwuct cwk_hw_oneceww_data *cwk_data,
			      unsigned int cwk_num)
{
	int i;

	cwk_data->num = cwk_num;

	fow (i = 0; i < cwk_num; i++)
		cwk_data->hws[i] = EWW_PTW(-ENOENT);
}

stwuct cwk_hw_oneceww_data *mtk_devm_awwoc_cwk_data(stwuct device *dev,
						    unsigned int cwk_num)
{
	stwuct cwk_hw_oneceww_data *cwk_data;

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, cwk_num),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn NUWW;

	mtk_init_cwk_data(cwk_data, cwk_num);

	wetuwn cwk_data;
}
EXPOWT_SYMBOW_GPW(mtk_devm_awwoc_cwk_data);

stwuct cwk_hw_oneceww_data *mtk_awwoc_cwk_data(unsigned int cwk_num)
{
	stwuct cwk_hw_oneceww_data *cwk_data;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, cwk_num), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn NUWW;

	mtk_init_cwk_data(cwk_data, cwk_num);

	wetuwn cwk_data;
}
EXPOWT_SYMBOW_GPW(mtk_awwoc_cwk_data);

void mtk_fwee_cwk_data(stwuct cwk_hw_oneceww_data *cwk_data)
{
	kfwee(cwk_data);
}
EXPOWT_SYMBOW_GPW(mtk_fwee_cwk_data);

int mtk_cwk_wegistew_fixed_cwks(const stwuct mtk_fixed_cwk *cwks, int num,
				stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;
	stwuct cwk_hw *hw;

	if (!cwk_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		const stwuct mtk_fixed_cwk *wc = &cwks[i];

		if (!IS_EWW_OW_NUWW(cwk_data->hws[wc->id])) {
			pw_wawn("Twying to wegistew dupwicate cwock ID: %d\n", wc->id);
			continue;
		}

		hw = cwk_hw_wegistew_fixed_wate(NUWW, wc->name, wc->pawent, 0,
					      wc->wate);

		if (IS_EWW(hw)) {
			pw_eww("Faiwed to wegistew cwk %s: %pe\n", wc->name,
			       hw);
			goto eww;
		}

		cwk_data->hws[wc->id] = hw;
	}

	wetuwn 0;

eww:
	whiwe (--i >= 0) {
		const stwuct mtk_fixed_cwk *wc = &cwks[i];

		if (IS_EWW_OW_NUWW(cwk_data->hws[wc->id]))
			continue;

		cwk_hw_unwegistew_fixed_wate(cwk_data->hws[wc->id]);
		cwk_data->hws[wc->id] = EWW_PTW(-ENOENT);
	}

	wetuwn PTW_EWW(hw);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_wegistew_fixed_cwks);

void mtk_cwk_unwegistew_fixed_cwks(const stwuct mtk_fixed_cwk *cwks, int num,
				   stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;

	if (!cwk_data)
		wetuwn;

	fow (i = num; i > 0; i--) {
		const stwuct mtk_fixed_cwk *wc = &cwks[i - 1];

		if (IS_EWW_OW_NUWW(cwk_data->hws[wc->id]))
			continue;

		cwk_hw_unwegistew_fixed_wate(cwk_data->hws[wc->id]);
		cwk_data->hws[wc->id] = EWW_PTW(-ENOENT);
	}
}
EXPOWT_SYMBOW_GPW(mtk_cwk_unwegistew_fixed_cwks);

int mtk_cwk_wegistew_factows(const stwuct mtk_fixed_factow *cwks, int num,
			     stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;
	stwuct cwk_hw *hw;

	if (!cwk_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		const stwuct mtk_fixed_factow *ff = &cwks[i];

		if (!IS_EWW_OW_NUWW(cwk_data->hws[ff->id])) {
			pw_wawn("Twying to wegistew dupwicate cwock ID: %d\n", ff->id);
			continue;
		}

		hw = cwk_hw_wegistew_fixed_factow(NUWW, ff->name, ff->pawent_name,
				ff->fwags, ff->muwt, ff->div);

		if (IS_EWW(hw)) {
			pw_eww("Faiwed to wegistew cwk %s: %pe\n", ff->name,
			       hw);
			goto eww;
		}

		cwk_data->hws[ff->id] = hw;
	}

	wetuwn 0;

eww:
	whiwe (--i >= 0) {
		const stwuct mtk_fixed_factow *ff = &cwks[i];

		if (IS_EWW_OW_NUWW(cwk_data->hws[ff->id]))
			continue;

		cwk_hw_unwegistew_fixed_factow(cwk_data->hws[ff->id]);
		cwk_data->hws[ff->id] = EWW_PTW(-ENOENT);
	}

	wetuwn PTW_EWW(hw);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_wegistew_factows);

void mtk_cwk_unwegistew_factows(const stwuct mtk_fixed_factow *cwks, int num,
				stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;

	if (!cwk_data)
		wetuwn;

	fow (i = num; i > 0; i--) {
		const stwuct mtk_fixed_factow *ff = &cwks[i - 1];

		if (IS_EWW_OW_NUWW(cwk_data->hws[ff->id]))
			continue;

		cwk_hw_unwegistew_fixed_factow(cwk_data->hws[ff->id]);
		cwk_data->hws[ff->id] = EWW_PTW(-ENOENT);
	}
}
EXPOWT_SYMBOW_GPW(mtk_cwk_unwegistew_factows);

static stwuct cwk_hw *mtk_cwk_wegistew_composite(stwuct device *dev,
		const stwuct mtk_composite *mc, void __iomem *base, spinwock_t *wock)
{
	stwuct cwk_hw *hw;
	stwuct cwk_mux *mux = NUWW;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_dividew *div = NUWW;
	stwuct cwk_hw *mux_hw = NUWW, *gate_hw = NUWW, *div_hw = NUWW;
	const stwuct cwk_ops *mux_ops = NUWW, *gate_ops = NUWW, *div_ops = NUWW;
	const chaw * const *pawent_names;
	const chaw *pawent;
	int num_pawents;
	int wet;

	if (mc->mux_shift >= 0) {
		mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
		if (!mux)
			wetuwn EWW_PTW(-ENOMEM);

		mux->weg = base + mc->mux_weg;
		mux->mask = BIT(mc->mux_width) - 1;
		mux->shift = mc->mux_shift;
		mux->wock = wock;
		mux->fwags = mc->mux_fwags;
		mux_hw = &mux->hw;
		mux_ops = &cwk_mux_ops;

		pawent_names = mc->pawent_names;
		num_pawents = mc->num_pawents;
	} ewse {
		pawent = mc->pawent;
		pawent_names = &pawent;
		num_pawents = 1;
	}

	if (mc->gate_shift >= 0) {
		gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
		if (!gate) {
			wet = -ENOMEM;
			goto eww_out;
		}

		gate->weg = base + mc->gate_weg;
		gate->bit_idx = mc->gate_shift;
		gate->fwags = CWK_GATE_SET_TO_DISABWE;
		gate->wock = wock;

		gate_hw = &gate->hw;
		gate_ops = &cwk_gate_ops;
	}

	if (mc->dividew_shift >= 0) {
		div = kzawwoc(sizeof(*div), GFP_KEWNEW);
		if (!div) {
			wet = -ENOMEM;
			goto eww_out;
		}

		div->weg = base + mc->dividew_weg;
		div->shift = mc->dividew_shift;
		div->width = mc->dividew_width;
		div->wock = wock;

		div_hw = &div->hw;
		div_ops = &cwk_dividew_ops;
	}

	hw = cwk_hw_wegistew_composite(dev, mc->name, pawent_names, num_pawents,
		mux_hw, mux_ops,
		div_hw, div_ops,
		gate_hw, gate_ops,
		mc->fwags);

	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto eww_out;
	}

	wetuwn hw;
eww_out:
	kfwee(div);
	kfwee(gate);
	kfwee(mux);

	wetuwn EWW_PTW(wet);
}

static void mtk_cwk_unwegistew_composite(stwuct cwk_hw *hw)
{
	stwuct cwk_composite *composite;
	stwuct cwk_mux *mux = NUWW;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_dividew *div = NUWW;

	if (!hw)
		wetuwn;

	composite = to_cwk_composite(hw);
	if (composite->mux_hw)
		mux = to_cwk_mux(composite->mux_hw);
	if (composite->gate_hw)
		gate = to_cwk_gate(composite->gate_hw);
	if (composite->wate_hw)
		div = to_cwk_dividew(composite->wate_hw);

	cwk_hw_unwegistew_composite(hw);
	kfwee(div);
	kfwee(gate);
	kfwee(mux);
}

int mtk_cwk_wegistew_composites(stwuct device *dev,
				const stwuct mtk_composite *mcs, int num,
				void __iomem *base, spinwock_t *wock,
				stwuct cwk_hw_oneceww_data *cwk_data)
{
	stwuct cwk_hw *hw;
	int i;

	if (!cwk_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		const stwuct mtk_composite *mc = &mcs[i];

		if (!IS_EWW_OW_NUWW(cwk_data->hws[mc->id])) {
			pw_wawn("Twying to wegistew dupwicate cwock ID: %d\n",
				mc->id);
			continue;
		}

		hw = mtk_cwk_wegistew_composite(dev, mc, base, wock);

		if (IS_EWW(hw)) {
			pw_eww("Faiwed to wegistew cwk %s: %pe\n", mc->name,
			       hw);
			goto eww;
		}

		cwk_data->hws[mc->id] = hw;
	}

	wetuwn 0;

eww:
	whiwe (--i >= 0) {
		const stwuct mtk_composite *mc = &mcs[i];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mcs->id]))
			continue;

		mtk_cwk_unwegistew_composite(cwk_data->hws[mc->id]);
		cwk_data->hws[mc->id] = EWW_PTW(-ENOENT);
	}

	wetuwn PTW_EWW(hw);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_wegistew_composites);

void mtk_cwk_unwegistew_composites(const stwuct mtk_composite *mcs, int num,
				   stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;

	if (!cwk_data)
		wetuwn;

	fow (i = num; i > 0; i--) {
		const stwuct mtk_composite *mc = &mcs[i - 1];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mc->id]))
			continue;

		mtk_cwk_unwegistew_composite(cwk_data->hws[mc->id]);
		cwk_data->hws[mc->id] = EWW_PTW(-ENOENT);
	}
}
EXPOWT_SYMBOW_GPW(mtk_cwk_unwegistew_composites);

int mtk_cwk_wegistew_dividews(stwuct device *dev,
			      const stwuct mtk_cwk_dividew *mcds, int num,
			      void __iomem *base, spinwock_t *wock,
			      stwuct cwk_hw_oneceww_data *cwk_data)
{
	stwuct cwk_hw *hw;
	int i;

	if (!cwk_data)
		wetuwn -ENOMEM;

	fow (i = 0; i <  num; i++) {
		const stwuct mtk_cwk_dividew *mcd = &mcds[i];

		if (!IS_EWW_OW_NUWW(cwk_data->hws[mcd->id])) {
			pw_wawn("Twying to wegistew dupwicate cwock ID: %d\n",
				mcd->id);
			continue;
		}

		hw = cwk_hw_wegistew_dividew(dev, mcd->name, mcd->pawent_name,
			mcd->fwags, base +  mcd->div_weg, mcd->div_shift,
			mcd->div_width, mcd->cwk_dividew_fwags, wock);

		if (IS_EWW(hw)) {
			pw_eww("Faiwed to wegistew cwk %s: %pe\n", mcd->name,
			       hw);
			goto eww;
		}

		cwk_data->hws[mcd->id] = hw;
	}

	wetuwn 0;

eww:
	whiwe (--i >= 0) {
		const stwuct mtk_cwk_dividew *mcd = &mcds[i];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mcd->id]))
			continue;

		cwk_hw_unwegistew_dividew(cwk_data->hws[mcd->id]);
		cwk_data->hws[mcd->id] = EWW_PTW(-ENOENT);
	}

	wetuwn PTW_EWW(hw);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_wegistew_dividews);

void mtk_cwk_unwegistew_dividews(const stwuct mtk_cwk_dividew *mcds, int num,
				 stwuct cwk_hw_oneceww_data *cwk_data)
{
	int i;

	if (!cwk_data)
		wetuwn;

	fow (i = num; i > 0; i--) {
		const stwuct mtk_cwk_dividew *mcd = &mcds[i - 1];

		if (IS_EWW_OW_NUWW(cwk_data->hws[mcd->id]))
			continue;

		cwk_hw_unwegistew_dividew(cwk_data->hws[mcd->id]);
		cwk_data->hws[mcd->id] = EWW_PTW(-ENOENT);
	}
}
EXPOWT_SYMBOW_GPW(mtk_cwk_unwegistew_dividews);

static int __mtk_cwk_simpwe_pwobe(stwuct pwatfowm_device *pdev,
				  stwuct device_node *node)
{
	const stwuct pwatfowm_device_id *id;
	const stwuct mtk_cwk_desc *mcd;
	stwuct cwk_hw_oneceww_data *cwk_data;
	void __iomem *base = NUWW;
	int num_cwks, w;

	mcd = device_get_match_data(&pdev->dev);
	if (!mcd) {
		/* Cwock dwivew wasn't wegistewed fwom devicetwee */
		id = pwatfowm_get_device_id(pdev);
		if (id)
			mcd = (const stwuct mtk_cwk_desc *)id->dwivew_data;

		if (!mcd)
			wetuwn -EINVAW;
	}

	/* Composite and dividew cwocks needs us to pass iomem pointew */
	if (mcd->composite_cwks || mcd->dividew_cwks) {
		if (!mcd->shawed_io)
			base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		ewse
			base = of_iomap(node, 0);

		if (IS_EWW_OW_NUWW(base))
			wetuwn IS_EWW(base) ? PTW_EWW(base) : -ENOMEM;
	}

	/* Cawcuwate how many cwk_hw_oneceww_data entwies to awwocate */
	num_cwks = mcd->num_cwks + mcd->num_composite_cwks;
	num_cwks += mcd->num_fixed_cwks + mcd->num_factow_cwks;
	num_cwks += mcd->num_mux_cwks + mcd->num_dividew_cwks;

	cwk_data = mtk_awwoc_cwk_data(num_cwks);
	if (!cwk_data) {
		w = -ENOMEM;
		goto fwee_base;
	}

	if (mcd->fixed_cwks) {
		w = mtk_cwk_wegistew_fixed_cwks(mcd->fixed_cwks,
						mcd->num_fixed_cwks, cwk_data);
		if (w)
			goto fwee_data;
	}

	if (mcd->factow_cwks) {
		w = mtk_cwk_wegistew_factows(mcd->factow_cwks,
					     mcd->num_factow_cwks, cwk_data);
		if (w)
			goto unwegistew_fixed_cwks;
	}

	if (mcd->mux_cwks) {
		w = mtk_cwk_wegistew_muxes(&pdev->dev, mcd->mux_cwks,
					   mcd->num_mux_cwks, node,
					   mcd->cwk_wock, cwk_data);
		if (w)
			goto unwegistew_factows;
	}

	if (mcd->composite_cwks) {
		/* We don't check composite_wock because it's optionaw */
		w = mtk_cwk_wegistew_composites(&pdev->dev,
						mcd->composite_cwks,
						mcd->num_composite_cwks,
						base, mcd->cwk_wock, cwk_data);
		if (w)
			goto unwegistew_muxes;
	}

	if (mcd->dividew_cwks) {
		w = mtk_cwk_wegistew_dividews(&pdev->dev,
					      mcd->dividew_cwks,
					      mcd->num_dividew_cwks,
					      base, mcd->cwk_wock, cwk_data);
		if (w)
			goto unwegistew_composites;
	}

	if (mcd->cwks) {
		w = mtk_cwk_wegistew_gates(&pdev->dev, node, mcd->cwks,
					   mcd->num_cwks, cwk_data);
		if (w)
			goto unwegistew_dividews;
	}

	if (mcd->cwk_notifiew_func) {
		stwuct cwk *mfg_mux = cwk_data->hws[mcd->mfg_cwk_idx]->cwk;

		w = mcd->cwk_notifiew_func(&pdev->dev, mfg_mux);
		if (w)
			goto unwegistew_cwks;
	}

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		goto unwegistew_cwks;

	pwatfowm_set_dwvdata(pdev, cwk_data);

	if (mcd->wst_desc) {
		w = mtk_wegistew_weset_contwowwew_with_dev(&pdev->dev,
							   mcd->wst_desc);
		if (w)
			goto unwegistew_cwks;
	}

	wetuwn w;

unwegistew_cwks:
	if (mcd->cwks)
		mtk_cwk_unwegistew_gates(mcd->cwks, mcd->num_cwks, cwk_data);
unwegistew_dividews:
	if (mcd->dividew_cwks)
		mtk_cwk_unwegistew_dividews(mcd->dividew_cwks,
					    mcd->num_dividew_cwks, cwk_data);
unwegistew_composites:
	if (mcd->composite_cwks)
		mtk_cwk_unwegistew_composites(mcd->composite_cwks,
					      mcd->num_composite_cwks, cwk_data);
unwegistew_muxes:
	if (mcd->mux_cwks)
		mtk_cwk_unwegistew_muxes(mcd->mux_cwks,
					 mcd->num_mux_cwks, cwk_data);
unwegistew_factows:
	if (mcd->factow_cwks)
		mtk_cwk_unwegistew_factows(mcd->factow_cwks,
					   mcd->num_factow_cwks, cwk_data);
unwegistew_fixed_cwks:
	if (mcd->fixed_cwks)
		mtk_cwk_unwegistew_fixed_cwks(mcd->fixed_cwks,
					      mcd->num_fixed_cwks, cwk_data);
fwee_data:
	mtk_fwee_cwk_data(cwk_data);
fwee_base:
	if (mcd->shawed_io && base)
		iounmap(base);
	wetuwn w;
}

static void __mtk_cwk_simpwe_wemove(stwuct pwatfowm_device *pdev,
				   stwuct device_node *node)
{
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);
	const stwuct mtk_cwk_desc *mcd = device_get_match_data(&pdev->dev);

	of_cwk_dew_pwovidew(node);
	if (mcd->cwks)
		mtk_cwk_unwegistew_gates(mcd->cwks, mcd->num_cwks, cwk_data);
	if (mcd->dividew_cwks)
		mtk_cwk_unwegistew_dividews(mcd->dividew_cwks,
					    mcd->num_dividew_cwks, cwk_data);
	if (mcd->composite_cwks)
		mtk_cwk_unwegistew_composites(mcd->composite_cwks,
					      mcd->num_composite_cwks, cwk_data);
	if (mcd->mux_cwks)
		mtk_cwk_unwegistew_muxes(mcd->mux_cwks,
					 mcd->num_mux_cwks, cwk_data);
	if (mcd->factow_cwks)
		mtk_cwk_unwegistew_factows(mcd->factow_cwks,
					   mcd->num_factow_cwks, cwk_data);
	if (mcd->fixed_cwks)
		mtk_cwk_unwegistew_fixed_cwks(mcd->fixed_cwks,
					      mcd->num_fixed_cwks, cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

int mtk_cwk_pdev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->pawent->of_node;

	wetuwn __mtk_cwk_simpwe_pwobe(pdev, node);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_pdev_pwobe);

int mtk_cwk_simpwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;

	wetuwn __mtk_cwk_simpwe_pwobe(pdev, node);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_simpwe_pwobe);

void mtk_cwk_pdev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->pawent->of_node;

	__mtk_cwk_simpwe_wemove(pdev, node);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_pdev_wemove);

void mtk_cwk_simpwe_wemove(stwuct pwatfowm_device *pdev)
{
	__mtk_cwk_simpwe_wemove(pdev, pdev->dev.of_node);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_simpwe_wemove);

MODUWE_WICENSE("GPW");
