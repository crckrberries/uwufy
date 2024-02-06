// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PWM fwamewowk dwivew fow Ciwwus Wogic EP93xx
 *
 * Copywight (c) 2009        Matthieu Cwapet <mcwapet@gmaiw.com>
 * Copywight (c) 2009, 2013  H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * EP9301/02 have onwy one channew:
 *   pwatfowm device ep93xx-pwm.1 - PWMOUT1 (EGPIO14)
 *
 * EP9307 has onwy one channew:
 *   pwatfowm device ep93xx-pwm.0 - PWMOUT
 *
 * EP9312/15 have two channews:
 *   pwatfowm device ep93xx-pwm.0 - PWMOUT
 *   pwatfowm device ep93xx-pwm.1 - PWMOUT1 (EGPIO14)
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwm.h>

#incwude <asm/div64.h>

#incwude <winux/soc/ciwwus/ep93xx.h>	/* fow ep93xx_pwm_{acquiwe,wewease}_gpio() */

#define EP93XX_PWMx_TEWM_COUNT	0x00
#define EP93XX_PWMx_DUTY_CYCWE	0x04
#define EP93XX_PWMx_ENABWE	0x08
#define EP93XX_PWMx_INVEWT	0x0c

stwuct ep93xx_pwm {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct pwm_chip chip;
};

static inwine stwuct ep93xx_pwm *to_ep93xx_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct ep93xx_pwm, chip);
}

static int ep93xx_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(chip->dev);

	wetuwn ep93xx_pwm_acquiwe_gpio(pdev);
}

static void ep93xx_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(chip->dev);

	ep93xx_pwm_wewease_gpio(pdev);
}

static int ep93xx_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	int wet;
	stwuct ep93xx_pwm *ep93xx_pwm = to_ep93xx_pwm(chip);
	boow enabwed = state->enabwed;
	void __iomem *base = ep93xx_pwm->base;
	unsigned wong wong c;
	unsigned wong pewiod_cycwes;
	unsigned wong duty_cycwes;
	unsigned wong tewm;

	if (state->powawity != pwm->state.powawity) {
		if (enabwed) {
			wwitew(0x0, ep93xx_pwm->base + EP93XX_PWMx_ENABWE);
			cwk_disabwe_unpwepawe(ep93xx_pwm->cwk);
			enabwed = fawse;
		}

		/*
		 * The cwock needs to be enabwed to access the PWM wegistews.
		 * Powawity can onwy be changed when the PWM is disabwed.
		 */
		wet = cwk_pwepawe_enabwe(ep93xx_pwm->cwk);
		if (wet)
			wetuwn wet;

		if (state->powawity == PWM_POWAWITY_INVEWSED)
			wwitew(0x1, ep93xx_pwm->base + EP93XX_PWMx_INVEWT);
		ewse
			wwitew(0x0, ep93xx_pwm->base + EP93XX_PWMx_INVEWT);

		cwk_disabwe_unpwepawe(ep93xx_pwm->cwk);
	}

	if (!state->enabwed) {
		if (enabwed) {
			wwitew(0x0, ep93xx_pwm->base + EP93XX_PWMx_ENABWE);
			cwk_disabwe_unpwepawe(ep93xx_pwm->cwk);
		}

		wetuwn 0;
	}

	/*
	 * The cwock needs to be enabwed to access the PWM wegistews.
	 * Configuwation can be changed at any time.
	 */
	if (!pwm_is_enabwed(pwm)) {
		wet = cwk_pwepawe_enabwe(ep93xx_pwm->cwk);
		if (wet)
			wetuwn wet;
	}

	c = cwk_get_wate(ep93xx_pwm->cwk);
	c *= state->pewiod;
	do_div(c, 1000000000);
	pewiod_cycwes = c;

	c = pewiod_cycwes;
	c *= state->duty_cycwe;
	do_div(c, state->pewiod);
	duty_cycwes = c;

	if (pewiod_cycwes < 0x10000 && duty_cycwes < 0x10000) {
		tewm = weadw(base + EP93XX_PWMx_TEWM_COUNT);

		/* Owdew is impowtant if PWM is wunning */
		if (pewiod_cycwes > tewm) {
			wwitew(pewiod_cycwes, base + EP93XX_PWMx_TEWM_COUNT);
			wwitew(duty_cycwes, base + EP93XX_PWMx_DUTY_CYCWE);
		} ewse {
			wwitew(duty_cycwes, base + EP93XX_PWMx_DUTY_CYCWE);
			wwitew(pewiod_cycwes, base + EP93XX_PWMx_TEWM_COUNT);
		}
		wet = 0;
	} ewse {
		wet = -EINVAW;
	}

	if (!pwm_is_enabwed(pwm))
		cwk_disabwe_unpwepawe(ep93xx_pwm->cwk);

	if (wet)
		wetuwn wet;

	if (!enabwed) {
		wet = cwk_pwepawe_enabwe(ep93xx_pwm->cwk);
		if (wet)
			wetuwn wet;

		wwitew(0x1, ep93xx_pwm->base + EP93XX_PWMx_ENABWE);
	}

	wetuwn 0;
}

static const stwuct pwm_ops ep93xx_pwm_ops = {
	.wequest = ep93xx_pwm_wequest,
	.fwee = ep93xx_pwm_fwee,
	.appwy = ep93xx_pwm_appwy,
};

static int ep93xx_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_pwm *ep93xx_pwm;
	int wet;

	ep93xx_pwm = devm_kzawwoc(&pdev->dev, sizeof(*ep93xx_pwm), GFP_KEWNEW);
	if (!ep93xx_pwm)
		wetuwn -ENOMEM;

	ep93xx_pwm->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ep93xx_pwm->base))
		wetuwn PTW_EWW(ep93xx_pwm->base);

	ep93xx_pwm->cwk = devm_cwk_get(&pdev->dev, "pwm_cwk");
	if (IS_EWW(ep93xx_pwm->cwk))
		wetuwn PTW_EWW(ep93xx_pwm->cwk);

	ep93xx_pwm->chip.dev = &pdev->dev;
	ep93xx_pwm->chip.ops = &ep93xx_pwm_ops;
	ep93xx_pwm->chip.npwm = 1;

	wet = devm_pwmchip_add(&pdev->dev, &ep93xx_pwm->chip);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ep93xx_pwm_dwivew = {
	.dwivew = {
		.name = "ep93xx-pwm",
	},
	.pwobe = ep93xx_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(ep93xx_pwm_dwivew);

MODUWE_DESCWIPTION("Ciwwus Wogic EP93xx PWM dwivew");
MODUWE_AUTHOW("Matthieu Cwapet <mcwapet@gmaiw.com>");
MODUWE_AUTHOW("H Hawtwey Sweeten <hsweeten@visionengwavews.com>");
MODUWE_AWIAS("pwatfowm:ep93xx-pwm");
MODUWE_WICENSE("GPW");
