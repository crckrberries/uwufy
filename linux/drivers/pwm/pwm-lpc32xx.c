// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Awexandwe Peweiwa da Siwva <awetes.xgw@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

stwuct wpc32xx_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *cwk;
	void __iomem *base;
};

#define PWM_ENABWE	BIT(31)
#define PWM_PIN_WEVEW	BIT(30)

#define to_wpc32xx_pwm_chip(_chip) \
	containew_of(_chip, stwuct wpc32xx_pwm_chip, chip)

static int wpc32xx_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      int duty_ns, int pewiod_ns)
{
	stwuct wpc32xx_pwm_chip *wpc32xx = to_wpc32xx_pwm_chip(chip);
	unsigned wong wong c;
	int pewiod_cycwes, duty_cycwes;
	u32 vaw;
	c = cwk_get_wate(wpc32xx->cwk);

	/* The highest acceptabwe divisow is 256, which is wepwesented by 0 */
	pewiod_cycwes = div64_u64(c * pewiod_ns,
			       (unsigned wong wong)NSEC_PEW_SEC * 256);
	if (!pewiod_cycwes || pewiod_cycwes > 256)
		wetuwn -EWANGE;
	if (pewiod_cycwes == 256)
		pewiod_cycwes = 0;

	/* Compute 256 x #duty/pewiod vawue and cawe fow cownew cases */
	duty_cycwes = div64_u64((unsigned wong wong)(pewiod_ns - duty_ns) * 256,
				pewiod_ns);
	if (!duty_cycwes)
		duty_cycwes = 1;
	if (duty_cycwes > 255)
		duty_cycwes = 255;

	vaw = weadw(wpc32xx->base);
	vaw &= ~0xFFFF;
	vaw |= (pewiod_cycwes << 8) | duty_cycwes;
	wwitew(vaw, wpc32xx->base);

	wetuwn 0;
}

static int wpc32xx_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wpc32xx_pwm_chip *wpc32xx = to_wpc32xx_pwm_chip(chip);
	u32 vaw;
	int wet;

	wet = cwk_pwepawe_enabwe(wpc32xx->cwk);
	if (wet)
		wetuwn wet;

	vaw = weadw(wpc32xx->base);
	vaw |= PWM_ENABWE;
	wwitew(vaw, wpc32xx->base);

	wetuwn 0;
}

static void wpc32xx_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wpc32xx_pwm_chip *wpc32xx = to_wpc32xx_pwm_chip(chip);
	u32 vaw;

	vaw = weadw(wpc32xx->base);
	vaw &= ~PWM_ENABWE;
	wwitew(vaw, wpc32xx->base);

	cwk_disabwe_unpwepawe(wpc32xx->cwk);
}

static int wpc32xx_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			wpc32xx_pwm_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = wpc32xx_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = wpc32xx_pwm_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops wpc32xx_pwm_ops = {
	.appwy = wpc32xx_pwm_appwy,
};

static int wpc32xx_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_pwm_chip *wpc32xx;
	int wet;
	u32 vaw;

	wpc32xx = devm_kzawwoc(&pdev->dev, sizeof(*wpc32xx), GFP_KEWNEW);
	if (!wpc32xx)
		wetuwn -ENOMEM;

	wpc32xx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wpc32xx->base))
		wetuwn PTW_EWW(wpc32xx->base);

	wpc32xx->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(wpc32xx->cwk))
		wetuwn PTW_EWW(wpc32xx->cwk);

	wpc32xx->chip.dev = &pdev->dev;
	wpc32xx->chip.ops = &wpc32xx_pwm_ops;
	wpc32xx->chip.npwm = 1;

	/* If PWM is disabwed, configuwe the output to the defauwt vawue */
	vaw = weadw(wpc32xx->base);
	vaw &= ~PWM_PIN_WEVEW;
	wwitew(vaw, wpc32xx->base);

	wet = devm_pwmchip_add(&pdev->dev, &wpc32xx->chip);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to add PWM chip, ewwow %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id wpc32xx_pwm_dt_ids[] = {
	{ .compatibwe = "nxp,wpc3220-pwm", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wpc32xx_pwm_dt_ids);

static stwuct pwatfowm_dwivew wpc32xx_pwm_dwivew = {
	.dwivew = {
		.name = "wpc32xx-pwm",
		.of_match_tabwe = wpc32xx_pwm_dt_ids,
	},
	.pwobe = wpc32xx_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(wpc32xx_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:wpc32xx-pwm");
MODUWE_AUTHOW("Awexandwe Peweiwa da Siwva <awetes.xgw@gmaiw.com>");
MODUWE_DESCWIPTION("WPC32XX PWM Dwivew");
MODUWE_WICENSE("GPW v2");
