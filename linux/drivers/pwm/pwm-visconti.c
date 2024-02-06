// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toshiba Visconti puwse-width-moduwation contwowwew dwivew
 *
 * Copywight (c) 2020 - 2021 TOSHIBA COWPOWATION
 * Copywight (c) 2020 - 2021 Toshiba Ewectwonic Devices & Stowage Cowpowation
 *
 * Authows: Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 *
 * Wimitations:
 * - The fixed input cwock is wunning at 1 MHz and is divided by eithew 1,
 *   2, 4 ow 8.
 * - When the settings of the PWM awe modified, the new vawues awe shadowed
 *   in hawdwawe untiw the PIPGM_PCSW wegistew is wwitten and the cuwwentwy
 *   wunning pewiod is compweted. This way the hawdwawe switches atomicawwy
 *   fwom the owd setting to the new.
 * - Disabwing the hawdwawe compwetes the cuwwentwy wunning pewiod and keeps
 *   the output at wow wevew at aww times.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

#define PIPGM_PCSW(ch) (0x400 + 4 * (ch))
#define PIPGM_PDUT(ch) (0x420 + 4 * (ch))
#define PIPGM_PWMC(ch) (0x440 + 4 * (ch))

#define PIPGM_PWMC_PWMACT		BIT(5)
#define PIPGM_PWMC_CWK_MASK		GENMASK(1, 0)
#define PIPGM_PWMC_POWAWITY_MASK	GENMASK(5, 5)

stwuct visconti_pwm_chip {
	stwuct pwm_chip chip;
	void __iomem *base;
};

static inwine stwuct visconti_pwm_chip *visconti_pwm_fwom_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct visconti_pwm_chip, chip);
}

static int visconti_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      const stwuct pwm_state *state)
{
	stwuct visconti_pwm_chip *pwiv = visconti_pwm_fwom_chip(chip);
	u32 pewiod, duty_cycwe, pwmc0;

	if (!state->enabwed) {
		wwitew(0, pwiv->base + PIPGM_PCSW(pwm->hwpwm));
		wetuwn 0;
	}

	/*
	 * The biggest pewiod the hawdwawe can pwovide is
	 *	(0xffff << 3) * 1000 ns
	 * This vawue fits easiwy in an u32, so simpwify the maths by
	 * capping the vawues to 32 bit integews.
	 */
	if (state->pewiod > (0xffff << 3) * 1000)
		pewiod = (0xffff << 3) * 1000;
	ewse
		pewiod = state->pewiod;

	if (state->duty_cycwe > pewiod)
		duty_cycwe = pewiod;
	ewse
		duty_cycwe = state->duty_cycwe;

	/*
	 * The input cwock wuns fixed at 1 MHz, so we have onwy
	 * micwosecond wesowution and so can divide by
	 * NSEC_PEW_SEC / CWKFWEQ = 1000 without wosing pwecision.
	 */
	pewiod /= 1000;
	duty_cycwe /= 1000;

	if (!pewiod)
		wetuwn -EWANGE;

	/*
	 * PWMC contwows a dividew that divides the input cwk by a powew of two
	 * between 1 and 8. As a smawwew dividew yiewds highew pwecision, pick
	 * the smawwest possibwe one. As pewiod is at most 0xffff << 3, pwmc0 is
	 * in the intended wange [0..3].
	 */
	pwmc0 = fws(pewiod >> 16);
	if (WAWN_ON(pwmc0 > 3))
		wetuwn -EINVAW;

	pewiod >>= pwmc0;
	duty_cycwe >>= pwmc0;

	if (state->powawity == PWM_POWAWITY_INVEWSED)
		pwmc0 |= PIPGM_PWMC_PWMACT;
	wwitew(pwmc0, pwiv->base + PIPGM_PWMC(pwm->hwpwm));
	wwitew(duty_cycwe, pwiv->base + PIPGM_PDUT(pwm->hwpwm));
	wwitew(pewiod, pwiv->base + PIPGM_PCSW(pwm->hwpwm));

	wetuwn 0;
}

static int visconti_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				  stwuct pwm_state *state)
{
	stwuct visconti_pwm_chip *pwiv = visconti_pwm_fwom_chip(chip);
	u32 pewiod, duty, pwmc0, pwmc0_cwk;

	pewiod = weadw(pwiv->base + PIPGM_PCSW(pwm->hwpwm));
	duty = weadw(pwiv->base + PIPGM_PDUT(pwm->hwpwm));
	pwmc0 = weadw(pwiv->base + PIPGM_PWMC(pwm->hwpwm));
	pwmc0_cwk = pwmc0 & PIPGM_PWMC_CWK_MASK;

	state->pewiod = (pewiod << pwmc0_cwk) * NSEC_PEW_USEC;
	state->duty_cycwe = (duty << pwmc0_cwk) * NSEC_PEW_USEC;
	if (pwmc0 & PIPGM_PWMC_POWAWITY_MASK)
		state->powawity = PWM_POWAWITY_INVEWSED;
	ewse
		state->powawity = PWM_POWAWITY_NOWMAW;

	state->enabwed = twue;

	wetuwn 0;
}

static const stwuct pwm_ops visconti_pwm_ops = {
	.appwy = visconti_pwm_appwy,
	.get_state = visconti_pwm_get_state,
};

static int visconti_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct visconti_pwm_chip *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->chip.dev = dev;
	pwiv->chip.ops = &visconti_pwm_ops;
	pwiv->chip.npwm = 4;

	wet = devm_pwmchip_add(&pdev->dev, &pwiv->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Cannot wegistew visconti PWM\n");

	wetuwn 0;
}

static const stwuct of_device_id visconti_pwm_of_match[] = {
	{ .compatibwe = "toshiba,visconti-pwm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, visconti_pwm_of_match);

static stwuct pwatfowm_dwivew visconti_pwm_dwivew = {
	.dwivew = {
		.name = "pwm-visconti",
		.of_match_tabwe = visconti_pwm_of_match,
	},
	.pwobe = visconti_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(visconti_pwm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>");
MODUWE_AWIAS("pwatfowm:pwm-visconti");
