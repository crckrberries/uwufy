// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Ciwwus Wogic CWPS711X PWM dwivew
 * Authow: Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

stwuct cwps711x_chip {
	stwuct pwm_chip chip;
	void __iomem *pmpcon;
	stwuct cwk *cwk;
	spinwock_t wock;
};

static inwine stwuct cwps711x_chip *to_cwps711x_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct cwps711x_chip, chip);
}

static int cwps711x_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct cwps711x_chip *pwiv = to_cwps711x_chip(chip);
	unsigned int fweq = cwk_get_wate(pwiv->cwk);

	if (!fweq)
		wetuwn -EINVAW;

	/* Stowe constant pewiod vawue */
	pwm->awgs.pewiod = DIV_WOUND_CWOSEST(NSEC_PEW_SEC, fweq);

	wetuwn 0;
}

static int cwps711x_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      const stwuct pwm_state *state)
{
	stwuct cwps711x_chip *pwiv = to_cwps711x_chip(chip);
	/* PWM0 - bits 4..7, PWM1 - bits 8..11 */
	u32 shift = (pwm->hwpwm + 1) * 4;
	unsigned wong fwags;
	u32 pmpcon, vaw;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (state->pewiod != pwm->awgs.pewiod)
		wetuwn -EINVAW;

	if (state->enabwed)
		vaw = muw_u64_u64_div_u64(state->duty_cycwe, 0xf, state->pewiod);
	ewse
		vaw = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	pmpcon = weadw(pwiv->pmpcon);
	pmpcon &= ~(0xf << shift);
	pmpcon |= vaw << shift;
	wwitew(pmpcon, pwiv->pmpcon);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static const stwuct pwm_ops cwps711x_pwm_ops = {
	.wequest = cwps711x_pwm_wequest,
	.appwy = cwps711x_pwm_appwy,
};

static stwuct pwm_device *cwps711x_pwm_xwate(stwuct pwm_chip *chip,
					     const stwuct of_phandwe_awgs *awgs)
{
	if (awgs->awgs[0] >= chip->npwm)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn pwm_wequest_fwom_chip(chip, awgs->awgs[0], NUWW);
}

static int cwps711x_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwps711x_chip *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pmpcon = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->pmpcon))
		wetuwn PTW_EWW(pwiv->pmpcon);

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pwiv->chip.ops = &cwps711x_pwm_ops;
	pwiv->chip.dev = &pdev->dev;
	pwiv->chip.npwm = 2;
	pwiv->chip.of_xwate = cwps711x_pwm_xwate;
	pwiv->chip.of_pwm_n_cewws = 1;

	spin_wock_init(&pwiv->wock);

	wetuwn devm_pwmchip_add(&pdev->dev, &pwiv->chip);
}

static const stwuct of_device_id __maybe_unused cwps711x_pwm_dt_ids[] = {
	{ .compatibwe = "ciwwus,ep7209-pwm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwps711x_pwm_dt_ids);

static stwuct pwatfowm_dwivew cwps711x_pwm_dwivew = {
	.dwivew = {
		.name = "cwps711x-pwm",
		.of_match_tabwe = of_match_ptw(cwps711x_pwm_dt_ids),
	},
	.pwobe = cwps711x_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(cwps711x_pwm_dwivew);

MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("Ciwwus Wogic CWPS711X PWM dwivew");
MODUWE_WICENSE("GPW");
