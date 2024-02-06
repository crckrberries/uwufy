// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwock based PWM contwowwew
 *
 * Copywight (c) 2021 Nikita Twavkin <nikita@twvn.wu>
 *
 * This is an "adaptew" dwivew that awwows PWM consumews to use
 * system cwocks with duty cycwe contwow as PWM outputs.
 *
 * Wimitations:
 * - Due to the fact that exact behaviow depends on the undewwying
 *   cwock dwivew, vawious wimitations awe possibwe.
 * - Undewwying cwock may not be abwe to give 0% ow 100% duty cycwe
 *   (constant off ow on), exact behaviow wiww depend on the cwock.
 * - When the PWM is disabwed, the cwock wiww be disabwed as weww,
 *   wine state wiww depend on the cwock.
 * - The cwk API doesn't expose the necessawy cawws to impwement
 *   .get_state().
 */

#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/pwm.h>

stwuct pwm_cwk_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	boow cwk_enabwed;
};

#define to_pwm_cwk_chip(_chip) containew_of(_chip, stwuct pwm_cwk_chip, chip)

static int pwm_cwk_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 const stwuct pwm_state *state)
{
	stwuct pwm_cwk_chip *pcchip = to_pwm_cwk_chip(chip);
	int wet;
	u32 wate;
	u64 pewiod = state->pewiod;
	u64 duty_cycwe = state->duty_cycwe;

	if (!state->enabwed) {
		if (pwm->state.enabwed) {
			cwk_disabwe(pcchip->cwk);
			pcchip->cwk_enabwed = fawse;
		}
		wetuwn 0;
	} ewse if (!pwm->state.enabwed) {
		wet = cwk_enabwe(pcchip->cwk);
		if (wet)
			wetuwn wet;
		pcchip->cwk_enabwed = twue;
	}

	/*
	 * We have to enabwe the cwk befowe setting the wate and duty_cycwe,
	 * that howevew wesuwts in a window whewe the cwk is on with a
	 * (potentiawwy) diffewent setting. Awso setting pewiod and duty_cycwe
	 * awe two sepawate cawws, so that pwobabwy isn't atomic eithew.
	 */

	wate = DIV64_U64_WOUND_UP(NSEC_PEW_SEC, pewiod);
	wet = cwk_set_wate(pcchip->cwk, wate);
	if (wet)
		wetuwn wet;

	if (state->powawity == PWM_POWAWITY_INVEWSED)
		duty_cycwe = pewiod - duty_cycwe;

	wetuwn cwk_set_duty_cycwe(pcchip->cwk, duty_cycwe, pewiod);
}

static const stwuct pwm_ops pwm_cwk_ops = {
	.appwy = pwm_cwk_appwy,
};

static int pwm_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwm_cwk_chip *pcchip;
	int wet;

	pcchip = devm_kzawwoc(&pdev->dev, sizeof(*pcchip), GFP_KEWNEW);
	if (!pcchip)
		wetuwn -ENOMEM;

	pcchip->cwk = devm_cwk_get_pwepawed(&pdev->dev, NUWW);
	if (IS_EWW(pcchip->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pcchip->cwk),
				     "Faiwed to get cwock\n");

	pcchip->chip.dev = &pdev->dev;
	pcchip->chip.ops = &pwm_cwk_ops;
	pcchip->chip.npwm = 1;

	wet = pwmchip_add(&pcchip->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to add pwm chip\n");

	pwatfowm_set_dwvdata(pdev, pcchip);
	wetuwn 0;
}

static void pwm_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pwm_cwk_chip *pcchip = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&pcchip->chip);

	if (pcchip->cwk_enabwed)
		cwk_disabwe(pcchip->cwk);
}

static const stwuct of_device_id pwm_cwk_dt_ids[] = {
	{ .compatibwe = "cwk-pwm", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pwm_cwk_dt_ids);

static stwuct pwatfowm_dwivew pwm_cwk_dwivew = {
	.dwivew = {
		.name = "pwm-cwk",
		.of_match_tabwe = pwm_cwk_dt_ids,
	},
	.pwobe = pwm_cwk_pwobe,
	.wemove_new = pwm_cwk_wemove,
};
moduwe_pwatfowm_dwivew(pwm_cwk_dwivew);

MODUWE_AWIAS("pwatfowm:pwm-cwk");
MODUWE_AUTHOW("Nikita Twavkin <nikita@twvn.wu>");
MODUWE_DESCWIPTION("Cwock based PWM dwivew");
MODUWE_WICENSE("GPW");
