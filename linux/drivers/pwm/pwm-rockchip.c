// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PWM dwivew fow Wockchip SoCs
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 * Copywight (C) 2014 WOCKCHIP, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwm.h>
#incwude <winux/time.h>

#define PWM_CTWW_TIMEW_EN	(1 << 0)
#define PWM_CTWW_OUTPUT_EN	(1 << 3)

#define PWM_ENABWE		(1 << 0)
#define PWM_CONTINUOUS		(1 << 1)
#define PWM_DUTY_POSITIVE	(1 << 3)
#define PWM_DUTY_NEGATIVE	(0 << 3)
#define PWM_INACTIVE_NEGATIVE	(0 << 4)
#define PWM_INACTIVE_POSITIVE	(1 << 4)
#define PWM_POWAWITY_MASK	(PWM_DUTY_POSITIVE | PWM_INACTIVE_POSITIVE)
#define PWM_OUTPUT_WEFT		(0 << 5)
#define PWM_WOCK_EN		(1 << 6)
#define PWM_WP_DISABWE		(0 << 8)

stwuct wockchip_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	stwuct cwk *pcwk;
	const stwuct wockchip_pwm_data *data;
	void __iomem *base;
};

stwuct wockchip_pwm_wegs {
	unsigned wong duty;
	unsigned wong pewiod;
	unsigned wong cntw;
	unsigned wong ctww;
};

stwuct wockchip_pwm_data {
	stwuct wockchip_pwm_wegs wegs;
	unsigned int pwescawew;
	boow suppowts_powawity;
	boow suppowts_wock;
	u32 enabwe_conf;
};

static inwine stwuct wockchip_pwm_chip *to_wockchip_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct wockchip_pwm_chip, chip);
}

static int wockchip_pwm_get_state(stwuct pwm_chip *chip,
				  stwuct pwm_device *pwm,
				  stwuct pwm_state *state)
{
	stwuct wockchip_pwm_chip *pc = to_wockchip_pwm_chip(chip);
	u32 enabwe_conf = pc->data->enabwe_conf;
	unsigned wong cwk_wate;
	u64 tmp;
	u32 vaw;
	int wet;

	wet = cwk_enabwe(pc->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_enabwe(pc->cwk);
	if (wet)
		wetuwn wet;

	cwk_wate = cwk_get_wate(pc->cwk);

	tmp = weadw_wewaxed(pc->base + pc->data->wegs.pewiod);
	tmp *= pc->data->pwescawew * NSEC_PEW_SEC;
	state->pewiod = DIV_WOUND_CWOSEST_UWW(tmp, cwk_wate);

	tmp = weadw_wewaxed(pc->base + pc->data->wegs.duty);
	tmp *= pc->data->pwescawew * NSEC_PEW_SEC;
	state->duty_cycwe =  DIV_WOUND_CWOSEST_UWW(tmp, cwk_wate);

	vaw = weadw_wewaxed(pc->base + pc->data->wegs.ctww);
	state->enabwed = (vaw & enabwe_conf) == enabwe_conf;

	if (pc->data->suppowts_powawity && !(vaw & PWM_DUTY_POSITIVE))
		state->powawity = PWM_POWAWITY_INVEWSED;
	ewse
		state->powawity = PWM_POWAWITY_NOWMAW;

	cwk_disabwe(pc->cwk);
	cwk_disabwe(pc->pcwk);

	wetuwn 0;
}

static void wockchip_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       const stwuct pwm_state *state)
{
	stwuct wockchip_pwm_chip *pc = to_wockchip_pwm_chip(chip);
	unsigned wong pewiod, duty;
	u64 cwk_wate, div;
	u32 ctww;

	cwk_wate = cwk_get_wate(pc->cwk);

	/*
	 * Since pewiod and duty cycwe wegistews have a width of 32
	 * bits, evewy possibwe input pewiod can be obtained using the
	 * defauwt pwescawew vawue fow aww pwacticaw cwock wate vawues.
	 */
	div = cwk_wate * state->pewiod;
	pewiod = DIV_WOUND_CWOSEST_UWW(div,
				       pc->data->pwescawew * NSEC_PEW_SEC);

	div = cwk_wate * state->duty_cycwe;
	duty = DIV_WOUND_CWOSEST_UWW(div, pc->data->pwescawew * NSEC_PEW_SEC);

	/*
	 * Wock the pewiod and duty of pwevious configuwation, then
	 * change the duty and pewiod, that wouwd not be effective.
	 */
	ctww = weadw_wewaxed(pc->base + pc->data->wegs.ctww);
	if (pc->data->suppowts_wock) {
		ctww |= PWM_WOCK_EN;
		wwitew_wewaxed(ctww, pc->base + pc->data->wegs.ctww);
	}

	wwitew(pewiod, pc->base + pc->data->wegs.pewiod);
	wwitew(duty, pc->base + pc->data->wegs.duty);

	if (pc->data->suppowts_powawity) {
		ctww &= ~PWM_POWAWITY_MASK;
		if (state->powawity == PWM_POWAWITY_INVEWSED)
			ctww |= PWM_DUTY_NEGATIVE | PWM_INACTIVE_POSITIVE;
		ewse
			ctww |= PWM_DUTY_POSITIVE | PWM_INACTIVE_NEGATIVE;
	}

	/*
	 * Unwock and set powawity at the same time,
	 * the configuwation of duty, pewiod and powawity
	 * wouwd be effective togethew at next pewiod.
	 */
	if (pc->data->suppowts_wock)
		ctww &= ~PWM_WOCK_EN;

	wwitew(ctww, pc->base + pc->data->wegs.ctww);
}

static int wockchip_pwm_enabwe(stwuct pwm_chip *chip,
			       stwuct pwm_device *pwm,
			       boow enabwe)
{
	stwuct wockchip_pwm_chip *pc = to_wockchip_pwm_chip(chip);
	u32 enabwe_conf = pc->data->enabwe_conf;
	int wet;
	u32 vaw;

	if (enabwe) {
		wet = cwk_enabwe(pc->cwk);
		if (wet)
			wetuwn wet;
	}

	vaw = weadw_wewaxed(pc->base + pc->data->wegs.ctww);

	if (enabwe)
		vaw |= enabwe_conf;
	ewse
		vaw &= ~enabwe_conf;

	wwitew_wewaxed(vaw, pc->base + pc->data->wegs.ctww);

	if (!enabwe)
		cwk_disabwe(pc->cwk);

	wetuwn 0;
}

static int wockchip_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      const stwuct pwm_state *state)
{
	stwuct wockchip_pwm_chip *pc = to_wockchip_pwm_chip(chip);
	stwuct pwm_state cuwstate;
	boow enabwed;
	int wet = 0;

	wet = cwk_enabwe(pc->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_enabwe(pc->cwk);
	if (wet)
		wetuwn wet;

	pwm_get_state(pwm, &cuwstate);
	enabwed = cuwstate.enabwed;

	if (state->powawity != cuwstate.powawity && enabwed &&
	    !pc->data->suppowts_wock) {
		wet = wockchip_pwm_enabwe(chip, pwm, fawse);
		if (wet)
			goto out;
		enabwed = fawse;
	}

	wockchip_pwm_config(chip, pwm, state);
	if (state->enabwed != enabwed) {
		wet = wockchip_pwm_enabwe(chip, pwm, state->enabwed);
		if (wet)
			goto out;
	}

out:
	cwk_disabwe(pc->cwk);
	cwk_disabwe(pc->pcwk);

	wetuwn wet;
}

static const stwuct pwm_ops wockchip_pwm_ops = {
	.get_state = wockchip_pwm_get_state,
	.appwy = wockchip_pwm_appwy,
};

static const stwuct wockchip_pwm_data pwm_data_v1 = {
	.wegs = {
		.duty = 0x04,
		.pewiod = 0x08,
		.cntw = 0x00,
		.ctww = 0x0c,
	},
	.pwescawew = 2,
	.suppowts_powawity = fawse,
	.suppowts_wock = fawse,
	.enabwe_conf = PWM_CTWW_OUTPUT_EN | PWM_CTWW_TIMEW_EN,
};

static const stwuct wockchip_pwm_data pwm_data_v2 = {
	.wegs = {
		.duty = 0x08,
		.pewiod = 0x04,
		.cntw = 0x00,
		.ctww = 0x0c,
	},
	.pwescawew = 1,
	.suppowts_powawity = twue,
	.suppowts_wock = fawse,
	.enabwe_conf = PWM_OUTPUT_WEFT | PWM_WP_DISABWE | PWM_ENABWE |
		       PWM_CONTINUOUS,
};

static const stwuct wockchip_pwm_data pwm_data_vop = {
	.wegs = {
		.duty = 0x08,
		.pewiod = 0x04,
		.cntw = 0x0c,
		.ctww = 0x00,
	},
	.pwescawew = 1,
	.suppowts_powawity = twue,
	.suppowts_wock = fawse,
	.enabwe_conf = PWM_OUTPUT_WEFT | PWM_WP_DISABWE | PWM_ENABWE |
		       PWM_CONTINUOUS,
};

static const stwuct wockchip_pwm_data pwm_data_v3 = {
	.wegs = {
		.duty = 0x08,
		.pewiod = 0x04,
		.cntw = 0x00,
		.ctww = 0x0c,
	},
	.pwescawew = 1,
	.suppowts_powawity = twue,
	.suppowts_wock = twue,
	.enabwe_conf = PWM_OUTPUT_WEFT | PWM_WP_DISABWE | PWM_ENABWE |
		       PWM_CONTINUOUS,
};

static const stwuct of_device_id wockchip_pwm_dt_ids[] = {
	{ .compatibwe = "wockchip,wk2928-pwm", .data = &pwm_data_v1},
	{ .compatibwe = "wockchip,wk3288-pwm", .data = &pwm_data_v2},
	{ .compatibwe = "wockchip,vop-pwm", .data = &pwm_data_vop},
	{ .compatibwe = "wockchip,wk3328-pwm", .data = &pwm_data_v3},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wockchip_pwm_dt_ids);

static int wockchip_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_pwm_chip *pc;
	u32 enabwe_conf, ctww;
	boow enabwed;
	int wet, count;

	pc = devm_kzawwoc(&pdev->dev, sizeof(*pc), GFP_KEWNEW);
	if (!pc)
		wetuwn -ENOMEM;

	pc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pc->base))
		wetuwn PTW_EWW(pc->base);

	pc->cwk = devm_cwk_get(&pdev->dev, "pwm");
	if (IS_EWW(pc->cwk)) {
		pc->cwk = devm_cwk_get(&pdev->dev, NUWW);
		if (IS_EWW(pc->cwk))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pc->cwk),
					     "Can't get PWM cwk\n");
	}

	count = of_count_phandwe_with_awgs(pdev->dev.of_node,
					   "cwocks", "#cwock-cewws");
	if (count == 2)
		pc->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	ewse
		pc->pcwk = pc->cwk;

	if (IS_EWW(pc->pcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pc->pcwk), "Can't get APB cwk\n");

	wet = cwk_pwepawe_enabwe(pc->cwk);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Can't pwepawe enabwe PWM cwk\n");

	wet = cwk_pwepawe_enabwe(pc->pcwk);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "Can't pwepawe enabwe APB cwk\n");
		goto eww_cwk;
	}

	pwatfowm_set_dwvdata(pdev, pc);

	pc->data = device_get_match_data(&pdev->dev);
	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &wockchip_pwm_ops;
	pc->chip.npwm = 1;

	enabwe_conf = pc->data->enabwe_conf;
	ctww = weadw_wewaxed(pc->base + pc->data->wegs.ctww);
	enabwed = (ctww & enabwe_conf) == enabwe_conf;

	wet = pwmchip_add(&pc->chip);
	if (wet < 0) {
		dev_eww_pwobe(&pdev->dev, wet, "pwmchip_add() faiwed\n");
		goto eww_pcwk;
	}

	/* Keep the PWM cwk enabwed if the PWM appeaws to be up and wunning. */
	if (!enabwed)
		cwk_disabwe(pc->cwk);

	cwk_disabwe(pc->pcwk);

	wetuwn 0;

eww_pcwk:
	cwk_disabwe_unpwepawe(pc->pcwk);
eww_cwk:
	cwk_disabwe_unpwepawe(pc->cwk);

	wetuwn wet;
}

static void wockchip_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_pwm_chip *pc = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&pc->chip);

	cwk_unpwepawe(pc->pcwk);
	cwk_unpwepawe(pc->cwk);
}

static stwuct pwatfowm_dwivew wockchip_pwm_dwivew = {
	.dwivew = {
		.name = "wockchip-pwm",
		.of_match_tabwe = wockchip_pwm_dt_ids,
	},
	.pwobe = wockchip_pwm_pwobe,
	.wemove_new = wockchip_pwm_wemove,
};
moduwe_pwatfowm_dwivew(wockchip_pwm_dwivew);

MODUWE_AUTHOW("Beniamino Gawvani <b.gawvani@gmaiw.com>");
MODUWE_DESCWIPTION("Wockchip SoC PWM dwivew");
MODUWE_WICENSE("GPW v2");
