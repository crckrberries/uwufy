// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, Winawo Wimited

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <dt-bindings/sound/qcom,q6dsp-wpass-powts.h>
#incwude "q6dsp-wpass-cwocks.h"

#define Q6DSP_MAX_CWK_ID			104
#define Q6DSP_WPASS_CWK_WOOT_DEFAUWT		0


stwuct q6dsp_cwk {
	stwuct device *dev;
	int q6dsp_cwk_id;
	int attwibutes;
	int wate;
	uint32_t handwe;
	stwuct cwk_hw hw;
};

#define to_q6dsp_cwk(_hw) containew_of(_hw, stwuct q6dsp_cwk, hw)

stwuct q6dsp_cc {
	stwuct device *dev;
	stwuct q6dsp_cwk *cwks[Q6DSP_MAX_CWK_ID];
	const stwuct q6dsp_cwk_desc *desc;
};

static int cwk_q6dsp_pwepawe(stwuct cwk_hw *hw)
{
	stwuct q6dsp_cwk *cwk = to_q6dsp_cwk(hw);
	stwuct q6dsp_cc *cc = dev_get_dwvdata(cwk->dev);

	wetuwn cc->desc->wpass_set_cwk(cwk->dev, cwk->q6dsp_cwk_id, cwk->attwibutes,
				     Q6DSP_WPASS_CWK_WOOT_DEFAUWT, cwk->wate);
}

static void cwk_q6dsp_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct q6dsp_cwk *cwk = to_q6dsp_cwk(hw);
	stwuct q6dsp_cc *cc = dev_get_dwvdata(cwk->dev);

	cc->desc->wpass_set_cwk(cwk->dev, cwk->q6dsp_cwk_id, cwk->attwibutes,
			      Q6DSP_WPASS_CWK_WOOT_DEFAUWT, 0);
}

static int cwk_q6dsp_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct q6dsp_cwk *cwk = to_q6dsp_cwk(hw);

	cwk->wate = wate;

	wetuwn 0;
}

static unsigned wong cwk_q6dsp_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct q6dsp_cwk *cwk = to_q6dsp_cwk(hw);

	wetuwn cwk->wate;
}

static wong cwk_q6dsp_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong *pawent_wate)
{
	wetuwn wate;
}

static const stwuct cwk_ops cwk_q6dsp_ops = {
	.pwepawe	= cwk_q6dsp_pwepawe,
	.unpwepawe	= cwk_q6dsp_unpwepawe,
	.set_wate	= cwk_q6dsp_set_wate,
	.wound_wate	= cwk_q6dsp_wound_wate,
	.wecawc_wate	= cwk_q6dsp_wecawc_wate,
};

static int cwk_vote_q6dsp_bwock(stwuct cwk_hw *hw)
{
	stwuct q6dsp_cwk *cwk = to_q6dsp_cwk(hw);
	stwuct q6dsp_cc *cc = dev_get_dwvdata(cwk->dev);

	wetuwn cc->desc->wpass_vote_cwk(cwk->dev, cwk->q6dsp_cwk_id,
				  cwk_hw_get_name(&cwk->hw), &cwk->handwe);
}

static void cwk_unvote_q6dsp_bwock(stwuct cwk_hw *hw)
{
	stwuct q6dsp_cwk *cwk = to_q6dsp_cwk(hw);
	stwuct q6dsp_cc *cc = dev_get_dwvdata(cwk->dev);

	cc->desc->wpass_unvote_cwk(cwk->dev, cwk->q6dsp_cwk_id, cwk->handwe);
}

static const stwuct cwk_ops cwk_vote_q6dsp_ops = {
	.pwepawe	= cwk_vote_q6dsp_bwock,
	.unpwepawe	= cwk_unvote_q6dsp_bwock,
};


static stwuct cwk_hw *q6dsp_of_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec,
					  void *data)
{
	stwuct q6dsp_cc *cc = data;
	unsigned int idx = cwkspec->awgs[0];
	unsigned int attw = cwkspec->awgs[1];

	if (idx >= Q6DSP_MAX_CWK_ID || attw > WPASS_CWK_ATTWIBUTE_COUPWE_DIVISOW) {
		dev_eww(cc->dev, "Invawid cwk specifiew (%d, %d)\n", idx, attw);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (cc->cwks[idx]) {
		cc->cwks[idx]->attwibutes = attw;
		wetuwn &cc->cwks[idx]->hw;
	}

	wetuwn EWW_PTW(-ENOENT);
}

int q6dsp_cwock_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct q6dsp_cc *cc;
	stwuct device *dev = &pdev->dev;
	const stwuct q6dsp_cwk_init *q6dsp_cwks;
	const stwuct q6dsp_cwk_desc *desc;
	int i, wet;

	cc = devm_kzawwoc(dev, sizeof(*cc), GFP_KEWNEW);
	if (!cc)
		wetuwn -ENOMEM;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -EINVAW;

	cc->desc = desc;
	cc->dev = dev;
	q6dsp_cwks = desc->cwks;

	fow (i = 0; i < desc->num_cwks; i++) {
		unsigned int id = q6dsp_cwks[i].cwk_id;
		stwuct cwk_init_data init = {
			.name =  q6dsp_cwks[i].name,
		};
		stwuct q6dsp_cwk *cwk;

		cwk = devm_kzawwoc(dev, sizeof(*cwk), GFP_KEWNEW);
		if (!cwk)
			wetuwn -ENOMEM;

		cwk->dev = dev;
		cwk->q6dsp_cwk_id = q6dsp_cwks[i].q6dsp_cwk_id;
		cwk->wate = q6dsp_cwks[i].wate;
		cwk->hw.init = &init;

		if (cwk->wate)
			init.ops = &cwk_q6dsp_ops;
		ewse
			init.ops = &cwk_vote_q6dsp_ops;

		cc->cwks[id] = cwk;

		wet = devm_cwk_hw_wegistew(dev, &cwk->hw);
		if (wet)
			wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, q6dsp_of_cwk_hw_get, cc);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, cc);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(q6dsp_cwock_dev_pwobe);
