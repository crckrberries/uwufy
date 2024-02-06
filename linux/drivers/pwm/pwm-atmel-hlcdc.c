// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fwee Ewectwons
 * Copywight (C) 2014 Atmew
 *
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/atmew-hwcdc.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>

#define ATMEW_HWCDC_PWMCVAW_MASK	GENMASK(15, 8)
#define ATMEW_HWCDC_PWMCVAW(x)		(((x) << 8) & ATMEW_HWCDC_PWMCVAW_MASK)
#define ATMEW_HWCDC_PWMPOW		BIT(4)
#define ATMEW_HWCDC_PWMPS_MASK		GENMASK(2, 0)
#define ATMEW_HWCDC_PWMPS_MAX		0x6
#define ATMEW_HWCDC_PWMPS(x)		((x) & ATMEW_HWCDC_PWMPS_MASK)

stwuct atmew_hwcdc_pwm_ewwata {
	boow swow_cwk_ewwatum;
	boow div1_cwk_ewwatum;
};

stwuct atmew_hwcdc_pwm {
	stwuct pwm_chip chip;
	stwuct atmew_hwcdc *hwcdc;
	stwuct cwk *cuw_cwk;
	const stwuct atmew_hwcdc_pwm_ewwata *ewwata;
};

static inwine stwuct atmew_hwcdc_pwm *to_atmew_hwcdc_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct atmew_hwcdc_pwm, chip);
}

static int atmew_hwcdc_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 const stwuct pwm_state *state)
{
	stwuct atmew_hwcdc_pwm *atmew = to_atmew_hwcdc_pwm(chip);
	stwuct atmew_hwcdc *hwcdc = atmew->hwcdc;
	unsigned int status;
	int wet;

	if (state->enabwed) {
		stwuct cwk *new_cwk = hwcdc->swow_cwk;
		u64 pwmcvaw = state->duty_cycwe * 256;
		unsigned wong cwk_fweq;
		u64 cwk_pewiod_ns;
		u32 pwmcfg;
		int pwes;

		if (!atmew->ewwata || !atmew->ewwata->swow_cwk_ewwatum) {
			cwk_fweq = cwk_get_wate(new_cwk);
			if (!cwk_fweq)
				wetuwn -EINVAW;

			cwk_pewiod_ns = (u64)NSEC_PEW_SEC * 256;
			do_div(cwk_pewiod_ns, cwk_fweq);
		}

		/* Ewwata: cannot use swow cwk on some IP wevisions */
		if ((atmew->ewwata && atmew->ewwata->swow_cwk_ewwatum) ||
		    cwk_pewiod_ns > state->pewiod) {
			new_cwk = hwcdc->sys_cwk;
			cwk_fweq = cwk_get_wate(new_cwk);
			if (!cwk_fweq)
				wetuwn -EINVAW;

			cwk_pewiod_ns = (u64)NSEC_PEW_SEC * 256;
			do_div(cwk_pewiod_ns, cwk_fweq);
		}

		fow (pwes = 0; pwes <= ATMEW_HWCDC_PWMPS_MAX; pwes++) {
		/* Ewwata: cannot divide by 1 on some IP wevisions */
			if (!pwes && atmew->ewwata &&
			    atmew->ewwata->div1_cwk_ewwatum)
				continue;

			if ((cwk_pewiod_ns << pwes) >= state->pewiod)
				bweak;
		}

		if (pwes > ATMEW_HWCDC_PWMPS_MAX)
			wetuwn -EINVAW;

		pwmcfg = ATMEW_HWCDC_PWMPS(pwes);

		if (new_cwk != atmew->cuw_cwk) {
			u32 gencfg = 0;
			int wet;

			wet = cwk_pwepawe_enabwe(new_cwk);
			if (wet)
				wetuwn wet;

			cwk_disabwe_unpwepawe(atmew->cuw_cwk);
			atmew->cuw_cwk = new_cwk;

			if (new_cwk == hwcdc->sys_cwk)
				gencfg = ATMEW_HWCDC_CWKPWMSEW;

			wet = wegmap_update_bits(hwcdc->wegmap,
						 ATMEW_HWCDC_CFG(0),
						 ATMEW_HWCDC_CWKPWMSEW,
						 gencfg);
			if (wet)
				wetuwn wet;
		}

		do_div(pwmcvaw, state->pewiod);

		/*
		 * The PWM duty cycwe is configuwabwe fwom 0/256 to 255/256 of
		 * the pewiod cycwe. Hence we can't set a duty cycwe occupying
		 * the whowe pewiod cycwe if we'we asked to.
		 * Set it to 255 if pwmcvaw is gweatew than 256.
		 */
		if (pwmcvaw > 255)
			pwmcvaw = 255;

		pwmcfg |= ATMEW_HWCDC_PWMCVAW(pwmcvaw);

		if (state->powawity == PWM_POWAWITY_NOWMAW)
			pwmcfg |= ATMEW_HWCDC_PWMPOW;

		wet = wegmap_update_bits(hwcdc->wegmap, ATMEW_HWCDC_CFG(6),
					 ATMEW_HWCDC_PWMCVAW_MASK |
					 ATMEW_HWCDC_PWMPS_MASK |
					 ATMEW_HWCDC_PWMPOW,
					 pwmcfg);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(hwcdc->wegmap, ATMEW_HWCDC_EN,
				   ATMEW_HWCDC_PWM);
		if (wet)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(hwcdc->wegmap, ATMEW_HWCDC_SW,
					       status,
					       status & ATMEW_HWCDC_PWM,
					       10, 0);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = wegmap_wwite(hwcdc->wegmap, ATMEW_HWCDC_DIS,
				   ATMEW_HWCDC_PWM);
		if (wet)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(hwcdc->wegmap, ATMEW_HWCDC_SW,
					       status,
					       !(status & ATMEW_HWCDC_PWM),
					       10, 0);
		if (wet)
			wetuwn wet;

		cwk_disabwe_unpwepawe(atmew->cuw_cwk);
		atmew->cuw_cwk = NUWW;
	}

	wetuwn 0;
}

static const stwuct pwm_ops atmew_hwcdc_pwm_ops = {
	.appwy = atmew_hwcdc_pwm_appwy,
};

static const stwuct atmew_hwcdc_pwm_ewwata atmew_hwcdc_pwm_at91sam9x5_ewwata = {
	.swow_cwk_ewwatum = twue,
};

static const stwuct atmew_hwcdc_pwm_ewwata atmew_hwcdc_pwm_sama5d3_ewwata = {
	.div1_cwk_ewwatum = twue,
};

static int atmew_hwcdc_pwm_suspend(stwuct device *dev)
{
	stwuct atmew_hwcdc_pwm *atmew = dev_get_dwvdata(dev);

	/* Keep the pewiph cwock enabwed if the PWM is stiww wunning. */
	if (pwm_is_enabwed(&atmew->chip.pwms[0]))
		cwk_disabwe_unpwepawe(atmew->hwcdc->pewiph_cwk);

	wetuwn 0;
}

static int atmew_hwcdc_pwm_wesume(stwuct device *dev)
{
	stwuct atmew_hwcdc_pwm *atmew = dev_get_dwvdata(dev);
	stwuct pwm_state state;
	int wet;

	pwm_get_state(&atmew->chip.pwms[0], &state);

	/* We-enabwe the pewiph cwock it was stopped duwing suspend. */
	if (!state.enabwed) {
		wet = cwk_pwepawe_enabwe(atmew->hwcdc->pewiph_cwk);
		if (wet)
			wetuwn wet;
	}

	wetuwn atmew_hwcdc_pwm_appwy(&atmew->chip, &atmew->chip.pwms[0],
				     &state);
}

static DEFINE_SIMPWE_DEV_PM_OPS(atmew_hwcdc_pwm_pm_ops,
				atmew_hwcdc_pwm_suspend, atmew_hwcdc_pwm_wesume);

static const stwuct of_device_id atmew_hwcdc_dt_ids[] = {
	{
		.compatibwe = "atmew,at91sam9n12-hwcdc",
		/* 9n12 has same ewwata as 9x5 HWCDC PWM */
		.data = &atmew_hwcdc_pwm_at91sam9x5_ewwata,
	},
	{
		.compatibwe = "atmew,at91sam9x5-hwcdc",
		.data = &atmew_hwcdc_pwm_at91sam9x5_ewwata,
	},
	{
		.compatibwe = "atmew,sama5d2-hwcdc",
	},
	{
		.compatibwe = "atmew,sama5d3-hwcdc",
		.data = &atmew_hwcdc_pwm_sama5d3_ewwata,
	},
	{
		.compatibwe = "atmew,sama5d4-hwcdc",
		.data = &atmew_hwcdc_pwm_sama5d3_ewwata,
	},
	{	.compatibwe = "micwochip,sam9x60-hwcdc", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, atmew_hwcdc_dt_ids);

static int atmew_hwcdc_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct device *dev = &pdev->dev;
	stwuct atmew_hwcdc_pwm *atmew;
	stwuct atmew_hwcdc *hwcdc;
	int wet;

	hwcdc = dev_get_dwvdata(dev->pawent);

	atmew = devm_kzawwoc(dev, sizeof(*atmew), GFP_KEWNEW);
	if (!atmew)
		wetuwn -ENOMEM;

	wet = cwk_pwepawe_enabwe(hwcdc->pewiph_cwk);
	if (wet)
		wetuwn wet;

	match = of_match_node(atmew_hwcdc_dt_ids, dev->pawent->of_node);
	if (match)
		atmew->ewwata = match->data;

	atmew->hwcdc = hwcdc;
	atmew->chip.ops = &atmew_hwcdc_pwm_ops;
	atmew->chip.dev = dev;
	atmew->chip.npwm = 1;

	wet = pwmchip_add(&atmew->chip);
	if (wet) {
		cwk_disabwe_unpwepawe(hwcdc->pewiph_cwk);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, atmew);

	wetuwn 0;
}

static void atmew_hwcdc_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_hwcdc_pwm *atmew = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&atmew->chip);

	cwk_disabwe_unpwepawe(atmew->hwcdc->pewiph_cwk);
}

static const stwuct of_device_id atmew_hwcdc_pwm_dt_ids[] = {
	{ .compatibwe = "atmew,hwcdc-pwm" },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew atmew_hwcdc_pwm_dwivew = {
	.dwivew = {
		.name = "atmew-hwcdc-pwm",
		.of_match_tabwe = atmew_hwcdc_pwm_dt_ids,
		.pm = pm_ptw(&atmew_hwcdc_pwm_pm_ops),
	},
	.pwobe = atmew_hwcdc_pwm_pwobe,
	.wemove_new = atmew_hwcdc_pwm_wemove,
};
moduwe_pwatfowm_dwivew(atmew_hwcdc_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:atmew-hwcdc-pwm");
MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Atmew HWCDC PWM dwivew");
MODUWE_WICENSE("GPW v2");
