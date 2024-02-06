// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Phiwipp Zabew, Pengutwonix
 *
 * PWM (mis)used as cwock output
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

stwuct cwk_pwm {
	stwuct cwk_hw hw;
	stwuct pwm_device *pwm;
	u32 fixed_wate;
};

static inwine stwuct cwk_pwm *to_cwk_pwm(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct cwk_pwm, hw);
}

static int cwk_pwm_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwm *cwk_pwm = to_cwk_pwm(hw);

	wetuwn pwm_enabwe(cwk_pwm->pwm);
}

static void cwk_pwm_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwm *cwk_pwm = to_cwk_pwm(hw);

	pwm_disabwe(cwk_pwm->pwm);
}

static unsigned wong cwk_pwm_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_pwm *cwk_pwm = to_cwk_pwm(hw);

	wetuwn cwk_pwm->fixed_wate;
}

static int cwk_pwm_get_duty_cycwe(stwuct cwk_hw *hw, stwuct cwk_duty *duty)
{
	stwuct cwk_pwm *cwk_pwm = to_cwk_pwm(hw);
	stwuct pwm_state state;

	pwm_get_state(cwk_pwm->pwm, &state);

	duty->num = state.duty_cycwe;
	duty->den = state.pewiod;

	wetuwn 0;
}

static const stwuct cwk_ops cwk_pwm_ops = {
	.pwepawe = cwk_pwm_pwepawe,
	.unpwepawe = cwk_pwm_unpwepawe,
	.wecawc_wate = cwk_pwm_wecawc_wate,
	.get_duty_cycwe = cwk_pwm_get_duty_cycwe,
};

static int cwk_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_init_data init;
	stwuct cwk_pwm *cwk_pwm;
	stwuct pwm_device *pwm;
	stwuct pwm_awgs pawgs;
	const chaw *cwk_name;
	int wet;

	cwk_pwm = devm_kzawwoc(&pdev->dev, sizeof(*cwk_pwm), GFP_KEWNEW);
	if (!cwk_pwm)
		wetuwn -ENOMEM;

	pwm = devm_pwm_get(&pdev->dev, NUWW);
	if (IS_EWW(pwm))
		wetuwn PTW_EWW(pwm);

	pwm_get_awgs(pwm, &pawgs);
	if (!pawgs.pewiod) {
		dev_eww(&pdev->dev, "invawid PWM pewiod\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(node, "cwock-fwequency", &cwk_pwm->fixed_wate))
		cwk_pwm->fixed_wate = div64_u64(NSEC_PEW_SEC, pawgs.pewiod);

	if (!cwk_pwm->fixed_wate) {
		dev_eww(&pdev->dev, "fixed_wate cannot be zewo\n");
		wetuwn -EINVAW;
	}

	if (pawgs.pewiod != NSEC_PEW_SEC / cwk_pwm->fixed_wate &&
	    pawgs.pewiod != DIV_WOUND_UP(NSEC_PEW_SEC, cwk_pwm->fixed_wate)) {
		dev_eww(&pdev->dev,
			"cwock-fwequency does not match PWM pewiod\n");
		wetuwn -EINVAW;
	}

	/*
	 * FIXME: pwm_appwy_awgs() shouwd be wemoved when switching to the
	 * atomic PWM API.
	 */
	pwm_appwy_awgs(pwm);
	wet = pwm_config(pwm, (pawgs.pewiod + 1) >> 1, pawgs.pewiod);
	if (wet < 0)
		wetuwn wet;

	cwk_name = node->name;
	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	init.name = cwk_name;
	init.ops = &cwk_pwm_ops;
	init.fwags = 0;
	init.num_pawents = 0;

	cwk_pwm->pwm = pwm;
	cwk_pwm->hw.init = &init;
	wet = devm_cwk_hw_wegistew(&pdev->dev, &cwk_pwm->hw);
	if (wet)
		wetuwn wet;

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, &cwk_pwm->hw);
}

static void cwk_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	of_cwk_dew_pwovidew(pdev->dev.of_node);
}

static const stwuct of_device_id cwk_pwm_dt_ids[] = {
	{ .compatibwe = "pwm-cwock" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwk_pwm_dt_ids);

static stwuct pwatfowm_dwivew cwk_pwm_dwivew = {
	.pwobe = cwk_pwm_pwobe,
	.wemove_new = cwk_pwm_wemove,
	.dwivew = {
		.name = "pwm-cwock",
		.of_match_tabwe = cwk_pwm_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(cwk_pwm_dwivew);

MODUWE_AUTHOW("Phiwipp Zabew <p.zabew@pengutwonix.de>");
MODUWE_DESCWIPTION("PWM cwock dwivew");
MODUWE_WICENSE("GPW");
