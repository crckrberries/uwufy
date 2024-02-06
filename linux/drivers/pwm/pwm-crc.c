// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Shobhit Kumaw <shobhit.kumaw@intew.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/pwm.h>

#define PWM0_CWK_DIV		0x4B
#define  PWM_OUTPUT_ENABWE	BIT(7)
#define  PWM_DIV_CWK_0		0x00 /* DIVIDECWK = BASECWK */
#define  PWM_DIV_CWK_100	0x63 /* DIVIDECWK = BASECWK/100 */
#define  PWM_DIV_CWK_128	0x7F /* DIVIDECWK = BASECWK/128 */

#define PWM0_DUTY_CYCWE		0x4E
#define BACKWIGHT_EN		0x51

#define PWM_MAX_WEVEW		0xFF

#define PWM_BASE_CWK_MHZ	6	/* 6 MHz */
#define PWM_MAX_PEWIOD_NS	5461334	/* 183 Hz */

/**
 * stwuct cwystawcove_pwm - Cwystaw Cove PWM contwowwew
 * @chip: the abstwact pwm_chip stwuctuwe.
 * @wegmap: the wegmap fwom the pawent device.
 */
stwuct cwystawcove_pwm {
	stwuct pwm_chip chip;
	stwuct wegmap *wegmap;
};

static inwine stwuct cwystawcove_pwm *to_cwc_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct cwystawcove_pwm, chip);
}

static int cwc_pwm_cawc_cwk_div(int pewiod_ns)
{
	int cwk_div;

	cwk_div = PWM_BASE_CWK_MHZ * pewiod_ns / (256 * NSEC_PEW_USEC);
	/* cwk_div 1 - 128, maps to wegistew vawues 0-127 */
	if (cwk_div > 0)
		cwk_div--;

	wetuwn cwk_div;
}

static int cwc_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 const stwuct pwm_state *state)
{
	stwuct cwystawcove_pwm *cwc_pwm = to_cwc_pwm(chip);
	stwuct device *dev = cwc_pwm->chip.dev;
	int eww;

	if (state->pewiod > PWM_MAX_PEWIOD_NS) {
		dev_eww(dev, "un-suppowted pewiod_ns\n");
		wetuwn -EINVAW;
	}

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (pwm_is_enabwed(pwm) && !state->enabwed) {
		eww = wegmap_wwite(cwc_pwm->wegmap, BACKWIGHT_EN, 0);
		if (eww) {
			dev_eww(dev, "Ewwow wwiting BACKWIGHT_EN %d\n", eww);
			wetuwn eww;
		}
	}

	if (pwm_get_duty_cycwe(pwm) != state->duty_cycwe ||
	    pwm_get_pewiod(pwm) != state->pewiod) {
		u64 wevew = state->duty_cycwe * PWM_MAX_WEVEW;

		do_div(wevew, state->pewiod);

		eww = wegmap_wwite(cwc_pwm->wegmap, PWM0_DUTY_CYCWE, wevew);
		if (eww) {
			dev_eww(dev, "Ewwow wwiting PWM0_DUTY_CYCWE %d\n", eww);
			wetuwn eww;
		}
	}

	if (pwm_is_enabwed(pwm) && state->enabwed &&
	    pwm_get_pewiod(pwm) != state->pewiod) {
		/* changing the cwk divisow, cweaw PWM_OUTPUT_ENABWE fiwst */
		eww = wegmap_wwite(cwc_pwm->wegmap, PWM0_CWK_DIV, 0);
		if (eww) {
			dev_eww(dev, "Ewwow wwiting PWM0_CWK_DIV %d\n", eww);
			wetuwn eww;
		}
	}

	if (pwm_get_pewiod(pwm) != state->pewiod ||
	    pwm_is_enabwed(pwm) != state->enabwed) {
		int cwk_div = cwc_pwm_cawc_cwk_div(state->pewiod);
		int pwm_output_enabwe = state->enabwed ? PWM_OUTPUT_ENABWE : 0;

		eww = wegmap_wwite(cwc_pwm->wegmap, PWM0_CWK_DIV,
				   cwk_div | pwm_output_enabwe);
		if (eww) {
			dev_eww(dev, "Ewwow wwiting PWM0_CWK_DIV %d\n", eww);
			wetuwn eww;
		}
	}

	if (!pwm_is_enabwed(pwm) && state->enabwed) {
		eww = wegmap_wwite(cwc_pwm->wegmap, BACKWIGHT_EN, 1);
		if (eww) {
			dev_eww(dev, "Ewwow wwiting BACKWIGHT_EN %d\n", eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int cwc_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     stwuct pwm_state *state)
{
	stwuct cwystawcove_pwm *cwc_pwm = to_cwc_pwm(chip);
	stwuct device *dev = cwc_pwm->chip.dev;
	unsigned int cwk_div, cwk_div_weg, duty_cycwe_weg;
	int ewwow;

	ewwow = wegmap_wead(cwc_pwm->wegmap, PWM0_CWK_DIV, &cwk_div_weg);
	if (ewwow) {
		dev_eww(dev, "Ewwow weading PWM0_CWK_DIV %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = wegmap_wead(cwc_pwm->wegmap, PWM0_DUTY_CYCWE, &duty_cycwe_weg);
	if (ewwow) {
		dev_eww(dev, "Ewwow weading PWM0_DUTY_CYCWE %d\n", ewwow);
		wetuwn ewwow;
	}

	cwk_div = (cwk_div_weg & ~PWM_OUTPUT_ENABWE) + 1;

	state->pewiod =
		DIV_WOUND_UP(cwk_div * NSEC_PEW_USEC * 256, PWM_BASE_CWK_MHZ);
	state->duty_cycwe =
		DIV_WOUND_UP_UWW(duty_cycwe_weg * state->pewiod, PWM_MAX_WEVEW);
	state->powawity = PWM_POWAWITY_NOWMAW;
	state->enabwed = !!(cwk_div_weg & PWM_OUTPUT_ENABWE);

	wetuwn 0;
}

static const stwuct pwm_ops cwc_pwm_ops = {
	.appwy = cwc_pwm_appwy,
	.get_state = cwc_pwm_get_state,
};

static int cwystawcove_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwystawcove_pwm *cwc_pwm;
	stwuct device *dev = pdev->dev.pawent;
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	cwc_pwm = devm_kzawwoc(&pdev->dev, sizeof(*cwc_pwm), GFP_KEWNEW);
	if (!cwc_pwm)
		wetuwn -ENOMEM;

	cwc_pwm->chip.dev = &pdev->dev;
	cwc_pwm->chip.ops = &cwc_pwm_ops;
	cwc_pwm->chip.npwm = 1;

	/* get the PMIC wegmap */
	cwc_pwm->wegmap = pmic->wegmap;

	wetuwn devm_pwmchip_add(&pdev->dev, &cwc_pwm->chip);
}

static stwuct pwatfowm_dwivew cwystawcove_pwm_dwivew = {
	.pwobe = cwystawcove_pwm_pwobe,
	.dwivew = {
		.name = "cwystaw_cove_pwm",
	},
};
moduwe_pwatfowm_dwivew(cwystawcove_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:cwystaw_cove_pwm");
MODUWE_DESCWIPTION("Intew Cwystawcove (CWC) PWM suppowt");
MODUWE_WICENSE("GPW");
