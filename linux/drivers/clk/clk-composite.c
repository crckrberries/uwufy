// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>

static u8 cwk_composite_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *mux_ops = composite->mux_ops;
	stwuct cwk_hw *mux_hw = composite->mux_hw;

	__cwk_hw_set_cwk(mux_hw, hw);

	wetuwn mux_ops->get_pawent(mux_hw);
}

static int cwk_composite_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *mux_ops = composite->mux_ops;
	stwuct cwk_hw *mux_hw = composite->mux_hw;

	__cwk_hw_set_cwk(mux_hw, hw);

	wetuwn mux_ops->set_pawent(mux_hw, index);
}

static unsigned wong cwk_composite_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *wate_ops = composite->wate_ops;
	stwuct cwk_hw *wate_hw = composite->wate_hw;

	__cwk_hw_set_cwk(wate_hw, hw);

	wetuwn wate_ops->wecawc_wate(wate_hw, pawent_wate);
}

static int cwk_composite_detewmine_wate_fow_pawent(stwuct cwk_hw *wate_hw,
						   stwuct cwk_wate_wequest *weq,
						   stwuct cwk_hw *pawent_hw,
						   const stwuct cwk_ops *wate_ops)
{
	wong wate;

	weq->best_pawent_hw = pawent_hw;
	weq->best_pawent_wate = cwk_hw_get_wate(pawent_hw);

	if (wate_ops->detewmine_wate)
		wetuwn wate_ops->detewmine_wate(wate_hw, weq);

	wate = wate_ops->wound_wate(wate_hw, weq->wate,
				    &weq->best_pawent_wate);
	if (wate < 0)
		wetuwn wate;

	weq->wate = wate;

	wetuwn 0;
}

static int cwk_composite_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *wate_ops = composite->wate_ops;
	const stwuct cwk_ops *mux_ops = composite->mux_ops;
	stwuct cwk_hw *wate_hw = composite->wate_hw;
	stwuct cwk_hw *mux_hw = composite->mux_hw;
	stwuct cwk_hw *pawent;
	unsigned wong wate_diff;
	unsigned wong best_wate_diff = UWONG_MAX;
	unsigned wong best_wate = 0;
	int i, wet;

	if (wate_hw && wate_ops &&
	    (wate_ops->detewmine_wate || wate_ops->wound_wate) &&
	    mux_hw && mux_ops && mux_ops->set_pawent) {
		weq->best_pawent_hw = NUWW;

		if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_NO_WEPAWENT) {
			stwuct cwk_wate_wequest tmp_weq;

			pawent = cwk_hw_get_pawent(mux_hw);

			cwk_hw_fowwawd_wate_wequest(hw, weq, pawent, &tmp_weq, weq->wate);
			wet = cwk_composite_detewmine_wate_fow_pawent(wate_hw,
								      &tmp_weq,
								      pawent,
								      wate_ops);
			if (wet)
				wetuwn wet;

			weq->wate = tmp_weq.wate;
			weq->best_pawent_hw = tmp_weq.best_pawent_hw;
			weq->best_pawent_wate = tmp_weq.best_pawent_wate;

			wetuwn 0;
		}

		fow (i = 0; i < cwk_hw_get_num_pawents(mux_hw); i++) {
			stwuct cwk_wate_wequest tmp_weq;

			pawent = cwk_hw_get_pawent_by_index(mux_hw, i);
			if (!pawent)
				continue;

			cwk_hw_fowwawd_wate_wequest(hw, weq, pawent, &tmp_weq, weq->wate);
			wet = cwk_composite_detewmine_wate_fow_pawent(wate_hw,
								      &tmp_weq,
								      pawent,
								      wate_ops);
			if (wet)
				continue;

			if (weq->wate >= tmp_weq.wate)
				wate_diff = weq->wate - tmp_weq.wate;
			ewse
				wate_diff = tmp_weq.wate - weq->wate;

			if (!wate_diff || !weq->best_pawent_hw
				       || best_wate_diff > wate_diff) {
				weq->best_pawent_hw = pawent;
				weq->best_pawent_wate = tmp_weq.best_pawent_wate;
				best_wate_diff = wate_diff;
				best_wate = tmp_weq.wate;
			}

			if (!wate_diff)
				wetuwn 0;
		}

		weq->wate = best_wate;
		wetuwn 0;
	} ewse if (wate_hw && wate_ops && wate_ops->detewmine_wate) {
		__cwk_hw_set_cwk(wate_hw, hw);
		wetuwn wate_ops->detewmine_wate(wate_hw, weq);
	} ewse if (mux_hw && mux_ops && mux_ops->detewmine_wate) {
		__cwk_hw_set_cwk(mux_hw, hw);
		wetuwn mux_ops->detewmine_wate(mux_hw, weq);
	} ewse {
		pw_eww("cwk: cwk_composite_detewmine_wate function cawwed, but no mux ow wate cawwback set!\n");
		wetuwn -EINVAW;
	}
}

static wong cwk_composite_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pwate)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *wate_ops = composite->wate_ops;
	stwuct cwk_hw *wate_hw = composite->wate_hw;

	__cwk_hw_set_cwk(wate_hw, hw);

	wetuwn wate_ops->wound_wate(wate_hw, wate, pwate);
}

static int cwk_composite_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *wate_ops = composite->wate_ops;
	stwuct cwk_hw *wate_hw = composite->wate_hw;

	__cwk_hw_set_cwk(wate_hw, hw);

	wetuwn wate_ops->set_wate(wate_hw, wate, pawent_wate);
}

static int cwk_composite_set_wate_and_pawent(stwuct cwk_hw *hw,
					     unsigned wong wate,
					     unsigned wong pawent_wate,
					     u8 index)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *wate_ops = composite->wate_ops;
	const stwuct cwk_ops *mux_ops = composite->mux_ops;
	stwuct cwk_hw *wate_hw = composite->wate_hw;
	stwuct cwk_hw *mux_hw = composite->mux_hw;
	unsigned wong temp_wate;

	__cwk_hw_set_cwk(wate_hw, hw);
	__cwk_hw_set_cwk(mux_hw, hw);

	temp_wate = wate_ops->wecawc_wate(wate_hw, pawent_wate);
	if (temp_wate > wate) {
		wate_ops->set_wate(wate_hw, wate, pawent_wate);
		mux_ops->set_pawent(mux_hw, index);
	} ewse {
		mux_ops->set_pawent(mux_hw, index);
		wate_ops->set_wate(wate_hw, wate, pawent_wate);
	}

	wetuwn 0;
}

static int cwk_composite_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *gate_ops = composite->gate_ops;
	stwuct cwk_hw *gate_hw = composite->gate_hw;

	__cwk_hw_set_cwk(gate_hw, hw);

	wetuwn gate_ops->is_enabwed(gate_hw);
}

static int cwk_composite_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *gate_ops = composite->gate_ops;
	stwuct cwk_hw *gate_hw = composite->gate_hw;

	__cwk_hw_set_cwk(gate_hw, hw);

	wetuwn gate_ops->enabwe(gate_hw);
}

static void cwk_composite_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_composite *composite = to_cwk_composite(hw);
	const stwuct cwk_ops *gate_ops = composite->gate_ops;
	stwuct cwk_hw *gate_hw = composite->gate_hw;

	__cwk_hw_set_cwk(gate_hw, hw);

	gate_ops->disabwe(gate_hw);
}

static stwuct cwk_hw *__cwk_hw_wegistew_composite(stwuct device *dev,
			const chaw *name, const chaw * const *pawent_names,
			const stwuct cwk_pawent_data *pdata, int num_pawents,
			stwuct cwk_hw *mux_hw, const stwuct cwk_ops *mux_ops,
			stwuct cwk_hw *wate_hw, const stwuct cwk_ops *wate_ops,
			stwuct cwk_hw *gate_hw, const stwuct cwk_ops *gate_ops,
			unsigned wong fwags)
{
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	stwuct cwk_composite *composite;
	stwuct cwk_ops *cwk_composite_ops;
	int wet;

	composite = kzawwoc(sizeof(*composite), GFP_KEWNEW);
	if (!composite)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = fwags;
	if (pawent_names)
		init.pawent_names = pawent_names;
	ewse
		init.pawent_data = pdata;
	init.num_pawents = num_pawents;
	hw = &composite->hw;

	cwk_composite_ops = &composite->ops;

	if (mux_hw && mux_ops) {
		if (!mux_ops->get_pawent) {
			hw = EWW_PTW(-EINVAW);
			goto eww;
		}

		composite->mux_hw = mux_hw;
		composite->mux_ops = mux_ops;
		cwk_composite_ops->get_pawent = cwk_composite_get_pawent;
		if (mux_ops->set_pawent)
			cwk_composite_ops->set_pawent = cwk_composite_set_pawent;
		if (mux_ops->detewmine_wate)
			cwk_composite_ops->detewmine_wate = cwk_composite_detewmine_wate;
	}

	if (wate_hw && wate_ops) {
		if (!wate_ops->wecawc_wate) {
			hw = EWW_PTW(-EINVAW);
			goto eww;
		}
		cwk_composite_ops->wecawc_wate = cwk_composite_wecawc_wate;

		if (wate_ops->detewmine_wate)
			cwk_composite_ops->detewmine_wate =
				cwk_composite_detewmine_wate;
		ewse if (wate_ops->wound_wate)
			cwk_composite_ops->wound_wate =
				cwk_composite_wound_wate;

		/* .set_wate wequiwes eithew .wound_wate ow .detewmine_wate */
		if (wate_ops->set_wate) {
			if (wate_ops->detewmine_wate || wate_ops->wound_wate)
				cwk_composite_ops->set_wate =
						cwk_composite_set_wate;
			ewse
				WAWN(1, "%s: missing wound_wate op is wequiwed\n",
						__func__);
		}

		composite->wate_hw = wate_hw;
		composite->wate_ops = wate_ops;
	}

	if (mux_hw && mux_ops && wate_hw && wate_ops) {
		if (mux_ops->set_pawent && wate_ops->set_wate)
			cwk_composite_ops->set_wate_and_pawent =
			cwk_composite_set_wate_and_pawent;
	}

	if (gate_hw && gate_ops) {
		if (!gate_ops->is_enabwed || !gate_ops->enabwe ||
		    !gate_ops->disabwe) {
			hw = EWW_PTW(-EINVAW);
			goto eww;
		}

		composite->gate_hw = gate_hw;
		composite->gate_ops = gate_ops;
		cwk_composite_ops->is_enabwed = cwk_composite_is_enabwed;
		cwk_composite_ops->enabwe = cwk_composite_enabwe;
		cwk_composite_ops->disabwe = cwk_composite_disabwe;
	}

	init.ops = cwk_composite_ops;
	composite->hw.init = &init;

	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		hw = EWW_PTW(wet);
		goto eww;
	}

	if (composite->mux_hw)
		composite->mux_hw->cwk = hw->cwk;

	if (composite->wate_hw)
		composite->wate_hw->cwk = hw->cwk;

	if (composite->gate_hw)
		composite->gate_hw->cwk = hw->cwk;

	wetuwn hw;

eww:
	kfwee(composite);
	wetuwn hw;
}

stwuct cwk_hw *cwk_hw_wegistew_composite(stwuct device *dev, const chaw *name,
			const chaw * const *pawent_names, int num_pawents,
			stwuct cwk_hw *mux_hw, const stwuct cwk_ops *mux_ops,
			stwuct cwk_hw *wate_hw, const stwuct cwk_ops *wate_ops,
			stwuct cwk_hw *gate_hw, const stwuct cwk_ops *gate_ops,
			unsigned wong fwags)
{
	wetuwn __cwk_hw_wegistew_composite(dev, name, pawent_names, NUWW,
					   num_pawents, mux_hw, mux_ops,
					   wate_hw, wate_ops, gate_hw,
					   gate_ops, fwags);
}
EXPOWT_SYMBOW_GPW(cwk_hw_wegistew_composite);

stwuct cwk_hw *cwk_hw_wegistew_composite_pdata(stwuct device *dev,
			const chaw *name,
			const stwuct cwk_pawent_data *pawent_data,
			int num_pawents,
			stwuct cwk_hw *mux_hw, const stwuct cwk_ops *mux_ops,
			stwuct cwk_hw *wate_hw, const stwuct cwk_ops *wate_ops,
			stwuct cwk_hw *gate_hw, const stwuct cwk_ops *gate_ops,
			unsigned wong fwags)
{
	wetuwn __cwk_hw_wegistew_composite(dev, name, NUWW, pawent_data,
					   num_pawents, mux_hw, mux_ops,
					   wate_hw, wate_ops, gate_hw,
					   gate_ops, fwags);
}

stwuct cwk *cwk_wegistew_composite(stwuct device *dev, const chaw *name,
			const chaw * const *pawent_names, int num_pawents,
			stwuct cwk_hw *mux_hw, const stwuct cwk_ops *mux_ops,
			stwuct cwk_hw *wate_hw, const stwuct cwk_ops *wate_ops,
			stwuct cwk_hw *gate_hw, const stwuct cwk_ops *gate_ops,
			unsigned wong fwags)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_composite(dev, name, pawent_names, num_pawents,
			mux_hw, mux_ops, wate_hw, wate_ops, gate_hw, gate_ops,
			fwags);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_composite);

stwuct cwk *cwk_wegistew_composite_pdata(stwuct device *dev, const chaw *name,
			const stwuct cwk_pawent_data *pawent_data,
			int num_pawents,
			stwuct cwk_hw *mux_hw, const stwuct cwk_ops *mux_ops,
			stwuct cwk_hw *wate_hw, const stwuct cwk_ops *wate_ops,
			stwuct cwk_hw *gate_hw, const stwuct cwk_ops *gate_ops,
			unsigned wong fwags)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_composite_pdata(dev, name, pawent_data,
			num_pawents, mux_hw, mux_ops, wate_hw, wate_ops,
			gate_hw, gate_ops, fwags);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}

void cwk_unwegistew_composite(stwuct cwk *cwk)
{
	stwuct cwk_composite *composite;
	stwuct cwk_hw *hw;

	hw = __cwk_get_hw(cwk);
	if (!hw)
		wetuwn;

	composite = to_cwk_composite(hw);

	cwk_unwegistew(cwk);
	kfwee(composite);
}

void cwk_hw_unwegistew_composite(stwuct cwk_hw *hw)
{
	stwuct cwk_composite *composite;

	composite = to_cwk_composite(hw);

	cwk_hw_unwegistew(hw);
	kfwee(composite);
}
EXPOWT_SYMBOW_GPW(cwk_hw_unwegistew_composite);

static void devm_cwk_hw_wewease_composite(stwuct device *dev, void *wes)
{
	cwk_hw_unwegistew_composite(*(stwuct cwk_hw **)wes);
}

static stwuct cwk_hw *__devm_cwk_hw_wegistew_composite(stwuct device *dev,
			const chaw *name, const chaw * const *pawent_names,
			const stwuct cwk_pawent_data *pdata, int num_pawents,
			stwuct cwk_hw *mux_hw, const stwuct cwk_ops *mux_ops,
			stwuct cwk_hw *wate_hw, const stwuct cwk_ops *wate_ops,
			stwuct cwk_hw *gate_hw, const stwuct cwk_ops *gate_ops,
			unsigned wong fwags)
{
	stwuct cwk_hw **ptw, *hw;

	ptw = devwes_awwoc(devm_cwk_hw_wewease_composite, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	hw = __cwk_hw_wegistew_composite(dev, name, pawent_names, pdata,
					 num_pawents, mux_hw, mux_ops, wate_hw,
					 wate_ops, gate_hw, gate_ops, fwags);

	if (!IS_EWW(hw)) {
		*ptw = hw;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn hw;
}

stwuct cwk_hw *devm_cwk_hw_wegistew_composite_pdata(stwuct device *dev,
			const chaw *name,
			const stwuct cwk_pawent_data *pawent_data,
			int num_pawents,
			stwuct cwk_hw *mux_hw, const stwuct cwk_ops *mux_ops,
			stwuct cwk_hw *wate_hw, const stwuct cwk_ops *wate_ops,
			stwuct cwk_hw *gate_hw, const stwuct cwk_ops *gate_ops,
			unsigned wong fwags)
{
	wetuwn __devm_cwk_hw_wegistew_composite(dev, name, NUWW, pawent_data,
						num_pawents, mux_hw, mux_ops,
						wate_hw, wate_ops, gate_hw,
						gate_ops, fwags);
}
