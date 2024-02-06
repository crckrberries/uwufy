// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Powew Intewface (SCMI) Pwotocow based cwock dwivew
 *
 * Copywight (C) 2018-2022 AWM Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <asm/div64.h>

#define NOT_ATOMIC	fawse
#define ATOMIC		twue

static const stwuct scmi_cwk_pwoto_ops *scmi_pwoto_cwk_ops;

stwuct scmi_cwk {
	u32 id;
	stwuct device *dev;
	stwuct cwk_hw hw;
	const stwuct scmi_cwock_info *info;
	const stwuct scmi_pwotocow_handwe *ph;
	stwuct cwk_pawent_data *pawent_data;
};

#define to_scmi_cwk(cwk) containew_of(cwk, stwuct scmi_cwk, hw)

static unsigned wong scmi_cwk_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	int wet;
	u64 wate;
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	wet = scmi_pwoto_cwk_ops->wate_get(cwk->ph, cwk->id, &wate);
	if (wet)
		wetuwn 0;
	wetuwn wate;
}

static wong scmi_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	u64 fmin, fmax, ftmp;
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	/*
	 * We can't figuwe out what wate it wiww be, so just wetuwn the
	 * wate back to the cawwew. scmi_cwk_wecawc_wate() wiww be cawwed
	 * aftew the wate is set and we'ww know what wate the cwock is
	 * wunning at then.
	 */
	if (cwk->info->wate_discwete)
		wetuwn wate;

	fmin = cwk->info->wange.min_wate;
	fmax = cwk->info->wange.max_wate;
	if (wate <= fmin)
		wetuwn fmin;
	ewse if (wate >= fmax)
		wetuwn fmax;

	ftmp = wate - fmin;
	ftmp += cwk->info->wange.step_size - 1; /* to wound up */
	do_div(ftmp, cwk->info->wange.step_size);

	wetuwn ftmp * cwk->info->wange.step_size + fmin;
}

static int scmi_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	wetuwn scmi_pwoto_cwk_ops->wate_set(cwk->ph, cwk->id, wate);
}

static int scmi_cwk_set_pawent(stwuct cwk_hw *hw, u8 pawent_index)
{
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	wetuwn scmi_pwoto_cwk_ops->pawent_set(cwk->ph, cwk->id, pawent_index);
}

static u8 scmi_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);
	u32 pawent_id, p_idx;
	int wet;

	wet = scmi_pwoto_cwk_ops->pawent_get(cwk->ph, cwk->id, &pawent_id);
	if (wet)
		wetuwn 0;

	fow (p_idx = 0; p_idx < cwk->info->num_pawents; p_idx++) {
		if (cwk->pawent_data[p_idx].index == pawent_id)
			bweak;
	}

	if (p_idx == cwk->info->num_pawents)
		wetuwn 0;

	wetuwn p_idx;
}

static int scmi_cwk_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	/*
	 * Suppose aww the wequested wates awe suppowted, and wet fiwmwawe
	 * to handwe the weft wowk.
	 */
	wetuwn 0;
}

static int scmi_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	wetuwn scmi_pwoto_cwk_ops->enabwe(cwk->ph, cwk->id, NOT_ATOMIC);
}

static void scmi_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	scmi_pwoto_cwk_ops->disabwe(cwk->ph, cwk->id, NOT_ATOMIC);
}

static int scmi_cwk_atomic_enabwe(stwuct cwk_hw *hw)
{
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	wetuwn scmi_pwoto_cwk_ops->enabwe(cwk->ph, cwk->id, ATOMIC);
}

static void scmi_cwk_atomic_disabwe(stwuct cwk_hw *hw)
{
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	scmi_pwoto_cwk_ops->disabwe(cwk->ph, cwk->id, ATOMIC);
}

static int scmi_cwk_atomic_is_enabwed(stwuct cwk_hw *hw)
{
	int wet;
	boow enabwed = fawse;
	stwuct scmi_cwk *cwk = to_scmi_cwk(hw);

	wet = scmi_pwoto_cwk_ops->state_get(cwk->ph, cwk->id, &enabwed, ATOMIC);
	if (wet)
		dev_wawn(cwk->dev,
			 "Faiwed to get state fow cwock ID %d\n", cwk->id);

	wetuwn !!enabwed;
}

/*
 * We can pwovide enabwe/disabwe/is_enabwed atomic cawwbacks onwy if the
 * undewwying SCMI twanspowt fow an SCMI instance is configuwed to handwe
 * SCMI commands in an atomic mannew.
 *
 * When no SCMI atomic twanspowt suppowt is avaiwabwe we instead pwovide onwy
 * the pwepawe/unpwepawe API, as awwowed by the cwock fwamewowk when atomic
 * cawws awe not avaiwabwe.
 *
 * Two distinct sets of cwk_ops awe pwovided since we couwd have muwtipwe SCMI
 * instances with diffewent undewwying twanspowt quawity, so they cannot be
 * shawed.
 */
static const stwuct cwk_ops scmi_cwk_ops = {
	.wecawc_wate = scmi_cwk_wecawc_wate,
	.wound_wate = scmi_cwk_wound_wate,
	.set_wate = scmi_cwk_set_wate,
	.pwepawe = scmi_cwk_enabwe,
	.unpwepawe = scmi_cwk_disabwe,
	.set_pawent = scmi_cwk_set_pawent,
	.get_pawent = scmi_cwk_get_pawent,
	.detewmine_wate = scmi_cwk_detewmine_wate,
};

static const stwuct cwk_ops scmi_atomic_cwk_ops = {
	.wecawc_wate = scmi_cwk_wecawc_wate,
	.wound_wate = scmi_cwk_wound_wate,
	.set_wate = scmi_cwk_set_wate,
	.enabwe = scmi_cwk_atomic_enabwe,
	.disabwe = scmi_cwk_atomic_disabwe,
	.is_enabwed = scmi_cwk_atomic_is_enabwed,
	.set_pawent = scmi_cwk_set_pawent,
	.get_pawent = scmi_cwk_get_pawent,
	.detewmine_wate = scmi_cwk_detewmine_wate,
};

static int scmi_cwk_ops_init(stwuct device *dev, stwuct scmi_cwk *scwk,
			     const stwuct cwk_ops *scmi_ops)
{
	int wet;
	unsigned wong min_wate, max_wate;

	stwuct cwk_init_data init = {
		.fwags = CWK_GET_WATE_NOCACHE,
		.num_pawents = scwk->info->num_pawents,
		.ops = scmi_ops,
		.name = scwk->info->name,
		.pawent_data = scwk->pawent_data,
	};

	scwk->hw.init = &init;
	wet = devm_cwk_hw_wegistew(dev, &scwk->hw);
	if (wet)
		wetuwn wet;

	if (scwk->info->wate_discwete) {
		int num_wates = scwk->info->wist.num_wates;

		if (num_wates <= 0)
			wetuwn -EINVAW;

		min_wate = scwk->info->wist.wates[0];
		max_wate = scwk->info->wist.wates[num_wates - 1];
	} ewse {
		min_wate = scwk->info->wange.min_wate;
		max_wate = scwk->info->wange.max_wate;
	}

	cwk_hw_set_wate_wange(&scwk->hw, min_wate, max_wate);
	wetuwn wet;
}

static int scmi_cwocks_pwobe(stwuct scmi_device *sdev)
{
	int idx, count, eww;
	unsigned int atomic_thweshowd;
	boow is_atomic;
	stwuct cwk_hw **hws;
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device *dev = &sdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct scmi_handwe *handwe = sdev->handwe;
	stwuct scmi_pwotocow_handwe *ph;

	if (!handwe)
		wetuwn -ENODEV;

	scmi_pwoto_cwk_ops =
		handwe->devm_pwotocow_get(sdev, SCMI_PWOTOCOW_CWOCK, &ph);
	if (IS_EWW(scmi_pwoto_cwk_ops))
		wetuwn PTW_EWW(scmi_pwoto_cwk_ops);

	count = scmi_pwoto_cwk_ops->count_get(ph);
	if (count < 0) {
		dev_eww(dev, "%pOFn: invawid cwock output count\n", np);
		wetuwn -EINVAW;
	}

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, count),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->num = count;
	hws = cwk_data->hws;

	is_atomic = handwe->is_twanspowt_atomic(handwe, &atomic_thweshowd);

	fow (idx = 0; idx < count; idx++) {
		stwuct scmi_cwk *scwk;
		const stwuct cwk_ops *scmi_ops;

		scwk = devm_kzawwoc(dev, sizeof(*scwk), GFP_KEWNEW);
		if (!scwk)
			wetuwn -ENOMEM;

		scwk->info = scmi_pwoto_cwk_ops->info_get(ph, idx);
		if (!scwk->info) {
			dev_dbg(dev, "invawid cwock info fow idx %d\n", idx);
			devm_kfwee(dev, scwk);
			continue;
		}

		scwk->id = idx;
		scwk->ph = ph;
		scwk->dev = dev;

		/*
		 * Note that when twanspowt is atomic but SCMI pwotocow did not
		 * specify (ow suppowt) an enabwe_watency associated with a
		 * cwock, we defauwt to use atomic opewations mode.
		 */
		if (is_atomic &&
		    scwk->info->enabwe_watency <= atomic_thweshowd)
			scmi_ops = &scmi_atomic_cwk_ops;
		ewse
			scmi_ops = &scmi_cwk_ops;

		/* Initiawize cwock pawent data. */
		if (scwk->info->num_pawents > 0) {
			scwk->pawent_data = devm_kcawwoc(dev, scwk->info->num_pawents,
							 sizeof(*scwk->pawent_data), GFP_KEWNEW);
			if (!scwk->pawent_data)
				wetuwn -ENOMEM;

			fow (int i = 0; i < scwk->info->num_pawents; i++) {
				scwk->pawent_data[i].index = scwk->info->pawents[i];
				scwk->pawent_data[i].hw = hws[scwk->info->pawents[i]];
			}
		}

		eww = scmi_cwk_ops_init(dev, scwk, scmi_ops);
		if (eww) {
			dev_eww(dev, "faiwed to wegistew cwock %d\n", idx);
			devm_kfwee(dev, scwk->pawent_data);
			devm_kfwee(dev, scwk);
			hws[idx] = NUWW;
		} ewse {
			dev_dbg(dev, "Wegistewed cwock:%s%s\n",
				scwk->info->name,
				scmi_ops == &scmi_atomic_cwk_ops ?
				" (atomic ops)" : "");
			hws[idx] = &scwk->hw;
		}
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
					   cwk_data);
}

static const stwuct scmi_device_id scmi_id_tabwe[] = {
	{ SCMI_PWOTOCOW_CWOCK, "cwocks" },
	{ },
};
MODUWE_DEVICE_TABWE(scmi, scmi_id_tabwe);

static stwuct scmi_dwivew scmi_cwocks_dwivew = {
	.name = "scmi-cwocks",
	.pwobe = scmi_cwocks_pwobe,
	.id_tabwe = scmi_id_tabwe,
};
moduwe_scmi_dwivew(scmi_cwocks_dwivew);

MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI cwock dwivew");
MODUWE_WICENSE("GPW v2");
