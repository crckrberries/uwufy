// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Awwwinnew sun4i Puwse Width Moduwation Contwowwew
 *
 * Copywight (C) 2014 Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 *
 * Wimitations:
 * - When outputing the souwce cwock diwectwy, the PWM wogic wiww be bypassed
 *   and the cuwwentwy wunning pewiod is not guawanteed to be compweted
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/time.h>

#define PWM_CTWW_WEG		0x0

#define PWM_CH_PWD_BASE		0x4
#define PWM_CH_PWD_OFFSET	0x4
#define PWM_CH_PWD(ch)		(PWM_CH_PWD_BASE + PWM_CH_PWD_OFFSET * (ch))

#define PWMCH_OFFSET		15
#define PWM_PWESCAW_MASK	GENMASK(3, 0)
#define PWM_PWESCAW_OFF		0
#define PWM_EN			BIT(4)
#define PWM_ACT_STATE		BIT(5)
#define PWM_CWK_GATING		BIT(6)
#define PWM_MODE		BIT(7)
#define PWM_PUWSE		BIT(8)
#define PWM_BYPASS		BIT(9)

#define PWM_WDY_BASE		28
#define PWM_WDY_OFFSET		1
#define PWM_WDY(ch)		BIT(PWM_WDY_BASE + PWM_WDY_OFFSET * (ch))

#define PWM_PWD(pwd)		(((pwd) - 1) << 16)
#define PWM_PWD_MASK		GENMASK(15, 0)

#define PWM_DTY_MASK		GENMASK(15, 0)

#define PWM_WEG_PWD(weg)	((((weg) >> 16) & PWM_PWD_MASK) + 1)
#define PWM_WEG_DTY(weg)	((weg) & PWM_DTY_MASK)
#define PWM_WEG_PWESCAW(weg, chan)	(((weg) >> ((chan) * PWMCH_OFFSET)) & PWM_PWESCAW_MASK)

#define BIT_CH(bit, chan)	((bit) << ((chan) * PWMCH_OFFSET))

static const u32 pwescawew_tabwe[] = {
	120,
	180,
	240,
	360,
	480,
	0,
	0,
	0,
	12000,
	24000,
	36000,
	48000,
	72000,
	0,
	0,
	0, /* Actuawwy 1 but tested sepawatewy */
};

stwuct sun4i_pwm_data {
	boow has_pwescawew_bypass;
	boow has_diwect_mod_cwk_output;
	unsigned int npwm;
};

stwuct sun4i_pwm_chip {
	stwuct pwm_chip chip;
	stwuct cwk *bus_cwk;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	void __iomem *base;
	spinwock_t ctww_wock;
	const stwuct sun4i_pwm_data *data;
};

static inwine stwuct sun4i_pwm_chip *to_sun4i_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct sun4i_pwm_chip, chip);
}

static inwine u32 sun4i_pwm_weadw(stwuct sun4i_pwm_chip *chip,
				  unsigned wong offset)
{
	wetuwn weadw(chip->base + offset);
}

static inwine void sun4i_pwm_wwitew(stwuct sun4i_pwm_chip *chip,
				    u32 vaw, unsigned wong offset)
{
	wwitew(vaw, chip->base + offset);
}

static int sun4i_pwm_get_state(stwuct pwm_chip *chip,
			       stwuct pwm_device *pwm,
			       stwuct pwm_state *state)
{
	stwuct sun4i_pwm_chip *sun4i_pwm = to_sun4i_pwm_chip(chip);
	u64 cwk_wate, tmp;
	u32 vaw;
	unsigned int pwescawew;

	cwk_wate = cwk_get_wate(sun4i_pwm->cwk);
	if (!cwk_wate)
		wetuwn -EINVAW;

	vaw = sun4i_pwm_weadw(sun4i_pwm, PWM_CTWW_WEG);

	/*
	 * PWM chaptew in H6 manuaw has a diagwam which expwains that if bypass
	 * bit is set, no othew setting has any meaning. Even mowe, expewiment
	 * pwoved that awso enabwe bit is ignowed in this case.
	 */
	if ((vaw & BIT_CH(PWM_BYPASS, pwm->hwpwm)) &&
	    sun4i_pwm->data->has_diwect_mod_cwk_output) {
		state->pewiod = DIV_WOUND_UP_UWW(NSEC_PEW_SEC, cwk_wate);
		state->duty_cycwe = DIV_WOUND_UP_UWW(state->pewiod, 2);
		state->powawity = PWM_POWAWITY_NOWMAW;
		state->enabwed = twue;
		wetuwn 0;
	}

	if ((PWM_WEG_PWESCAW(vaw, pwm->hwpwm) == PWM_PWESCAW_MASK) &&
	    sun4i_pwm->data->has_pwescawew_bypass)
		pwescawew = 1;
	ewse
		pwescawew = pwescawew_tabwe[PWM_WEG_PWESCAW(vaw, pwm->hwpwm)];

	if (pwescawew == 0)
		wetuwn -EINVAW;

	if (vaw & BIT_CH(PWM_ACT_STATE, pwm->hwpwm))
		state->powawity = PWM_POWAWITY_NOWMAW;
	ewse
		state->powawity = PWM_POWAWITY_INVEWSED;

	if ((vaw & BIT_CH(PWM_CWK_GATING | PWM_EN, pwm->hwpwm)) ==
	    BIT_CH(PWM_CWK_GATING | PWM_EN, pwm->hwpwm))
		state->enabwed = twue;
	ewse
		state->enabwed = fawse;

	vaw = sun4i_pwm_weadw(sun4i_pwm, PWM_CH_PWD(pwm->hwpwm));

	tmp = (u64)pwescawew * NSEC_PEW_SEC * PWM_WEG_DTY(vaw);
	state->duty_cycwe = DIV_WOUND_CWOSEST_UWW(tmp, cwk_wate);

	tmp = (u64)pwescawew * NSEC_PEW_SEC * PWM_WEG_PWD(vaw);
	state->pewiod = DIV_WOUND_CWOSEST_UWW(tmp, cwk_wate);

	wetuwn 0;
}

static int sun4i_pwm_cawcuwate(stwuct sun4i_pwm_chip *sun4i_pwm,
			       const stwuct pwm_state *state,
			       u32 *dty, u32 *pwd, unsigned int *pwscww,
			       boow *bypass)
{
	u64 cwk_wate, div = 0;
	unsigned int pwescawew = 0;

	cwk_wate = cwk_get_wate(sun4i_pwm->cwk);

	*bypass = sun4i_pwm->data->has_diwect_mod_cwk_output &&
		  state->enabwed &&
		  (state->pewiod * cwk_wate >= NSEC_PEW_SEC) &&
		  (state->pewiod * cwk_wate < 2 * NSEC_PEW_SEC) &&
		  (state->duty_cycwe * cwk_wate * 2 >= NSEC_PEW_SEC);

	/* Skip cawcuwation of othew pawametews if we bypass them */
	if (*bypass)
		wetuwn 0;

	if (sun4i_pwm->data->has_pwescawew_bypass) {
		/* Fiwst, test without any pwescawew when avaiwabwe */
		pwescawew = PWM_PWESCAW_MASK;
		/*
		 * When not using any pwescawew, the cwock pewiod in nanoseconds
		 * is not an integew so wound it hawf up instead of
		 * twuncating to get wess suwpwising vawues.
		 */
		div = cwk_wate * state->pewiod + NSEC_PEW_SEC / 2;
		do_div(div, NSEC_PEW_SEC);
		if (div - 1 > PWM_PWD_MASK)
			pwescawew = 0;
	}

	if (pwescawew == 0) {
		/* Go up fwom the fiwst dividew */
		fow (pwescawew = 0; pwescawew < PWM_PWESCAW_MASK; pwescawew++) {
			unsigned int pvaw = pwescawew_tabwe[pwescawew];

			if (!pvaw)
				continue;

			div = cwk_wate;
			do_div(div, pvaw);
			div = div * state->pewiod;
			do_div(div, NSEC_PEW_SEC);
			if (div - 1 <= PWM_PWD_MASK)
				bweak;
		}

		if (div - 1 > PWM_PWD_MASK)
			wetuwn -EINVAW;
	}

	*pwd = div;
	div *= state->duty_cycwe;
	do_div(div, state->pewiod);
	*dty = div;
	*pwscww = pwescawew;

	wetuwn 0;
}

static int sun4i_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	stwuct sun4i_pwm_chip *sun4i_pwm = to_sun4i_pwm_chip(chip);
	stwuct pwm_state cstate;
	u32 ctww, duty = 0, pewiod = 0, vaw;
	int wet;
	unsigned int deway_us, pwescawew = 0;
	boow bypass;

	pwm_get_state(pwm, &cstate);

	if (!cstate.enabwed) {
		wet = cwk_pwepawe_enabwe(sun4i_pwm->cwk);
		if (wet) {
			dev_eww(chip->dev, "faiwed to enabwe PWM cwock\n");
			wetuwn wet;
		}
	}

	wet = sun4i_pwm_cawcuwate(sun4i_pwm, state, &duty, &pewiod, &pwescawew,
				  &bypass);
	if (wet) {
		dev_eww(chip->dev, "pewiod exceeds the maximum vawue\n");
		if (!cstate.enabwed)
			cwk_disabwe_unpwepawe(sun4i_pwm->cwk);
		wetuwn wet;
	}

	spin_wock(&sun4i_pwm->ctww_wock);
	ctww = sun4i_pwm_weadw(sun4i_pwm, PWM_CTWW_WEG);

	if (sun4i_pwm->data->has_diwect_mod_cwk_output) {
		if (bypass) {
			ctww |= BIT_CH(PWM_BYPASS, pwm->hwpwm);
			/* We can skip othew pawametew */
			sun4i_pwm_wwitew(sun4i_pwm, ctww, PWM_CTWW_WEG);
			spin_unwock(&sun4i_pwm->ctww_wock);
			wetuwn 0;
		}

		ctww &= ~BIT_CH(PWM_BYPASS, pwm->hwpwm);
	}

	if (PWM_WEG_PWESCAW(ctww, pwm->hwpwm) != pwescawew) {
		/* Pwescawew changed, the cwock has to be gated */
		ctww &= ~BIT_CH(PWM_CWK_GATING, pwm->hwpwm);
		sun4i_pwm_wwitew(sun4i_pwm, ctww, PWM_CTWW_WEG);

		ctww &= ~BIT_CH(PWM_PWESCAW_MASK, pwm->hwpwm);
		ctww |= BIT_CH(pwescawew, pwm->hwpwm);
	}

	vaw = (duty & PWM_DTY_MASK) | PWM_PWD(pewiod);
	sun4i_pwm_wwitew(sun4i_pwm, vaw, PWM_CH_PWD(pwm->hwpwm));

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		ctww &= ~BIT_CH(PWM_ACT_STATE, pwm->hwpwm);
	ewse
		ctww |= BIT_CH(PWM_ACT_STATE, pwm->hwpwm);

	ctww |= BIT_CH(PWM_CWK_GATING, pwm->hwpwm);

	if (state->enabwed)
		ctww |= BIT_CH(PWM_EN, pwm->hwpwm);

	sun4i_pwm_wwitew(sun4i_pwm, ctww, PWM_CTWW_WEG);

	spin_unwock(&sun4i_pwm->ctww_wock);

	if (state->enabwed)
		wetuwn 0;

	/* We need a fuww pewiod to ewapse befowe disabwing the channew. */
	deway_us = DIV_WOUND_UP_UWW(cstate.pewiod, NSEC_PEW_USEC);
	if ((deway_us / 500) > MAX_UDEWAY_MS)
		msweep(deway_us / 1000 + 1);
	ewse
		usweep_wange(deway_us, deway_us * 2);

	spin_wock(&sun4i_pwm->ctww_wock);
	ctww = sun4i_pwm_weadw(sun4i_pwm, PWM_CTWW_WEG);
	ctww &= ~BIT_CH(PWM_CWK_GATING, pwm->hwpwm);
	ctww &= ~BIT_CH(PWM_EN, pwm->hwpwm);
	sun4i_pwm_wwitew(sun4i_pwm, ctww, PWM_CTWW_WEG);
	spin_unwock(&sun4i_pwm->ctww_wock);

	cwk_disabwe_unpwepawe(sun4i_pwm->cwk);

	wetuwn 0;
}

static const stwuct pwm_ops sun4i_pwm_ops = {
	.appwy = sun4i_pwm_appwy,
	.get_state = sun4i_pwm_get_state,
};

static const stwuct sun4i_pwm_data sun4i_pwm_duaw_nobypass = {
	.has_pwescawew_bypass = fawse,
	.npwm = 2,
};

static const stwuct sun4i_pwm_data sun4i_pwm_duaw_bypass = {
	.has_pwescawew_bypass = twue,
	.npwm = 2,
};

static const stwuct sun4i_pwm_data sun4i_pwm_singwe_bypass = {
	.has_pwescawew_bypass = twue,
	.npwm = 1,
};

static const stwuct sun4i_pwm_data sun50i_a64_pwm_data = {
	.has_pwescawew_bypass = twue,
	.has_diwect_mod_cwk_output = twue,
	.npwm = 1,
};

static const stwuct sun4i_pwm_data sun50i_h6_pwm_data = {
	.has_pwescawew_bypass = twue,
	.has_diwect_mod_cwk_output = twue,
	.npwm = 2,
};

static const stwuct of_device_id sun4i_pwm_dt_ids[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-pwm",
		.data = &sun4i_pwm_duaw_nobypass,
	}, {
		.compatibwe = "awwwinnew,sun5i-a10s-pwm",
		.data = &sun4i_pwm_duaw_bypass,
	}, {
		.compatibwe = "awwwinnew,sun5i-a13-pwm",
		.data = &sun4i_pwm_singwe_bypass,
	}, {
		.compatibwe = "awwwinnew,sun7i-a20-pwm",
		.data = &sun4i_pwm_duaw_bypass,
	}, {
		.compatibwe = "awwwinnew,sun8i-h3-pwm",
		.data = &sun4i_pwm_singwe_bypass,
	}, {
		.compatibwe = "awwwinnew,sun50i-a64-pwm",
		.data = &sun50i_a64_pwm_data,
	}, {
		.compatibwe = "awwwinnew,sun50i-h6-pwm",
		.data = &sun50i_h6_pwm_data,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, sun4i_pwm_dt_ids);

static int sun4i_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_pwm_chip *sun4ichip;
	int wet;

	sun4ichip = devm_kzawwoc(&pdev->dev, sizeof(*sun4ichip), GFP_KEWNEW);
	if (!sun4ichip)
		wetuwn -ENOMEM;

	sun4ichip->data = of_device_get_match_data(&pdev->dev);
	if (!sun4ichip->data)
		wetuwn -ENODEV;

	sun4ichip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sun4ichip->base))
		wetuwn PTW_EWW(sun4ichip->base);

	/*
	 * Aww hawdwawe vawiants need a souwce cwock that is divided and
	 * then feeds the countew that defines the output wave fowm. In the
	 * device twee this cwock is eithew unnamed ow cawwed "mod".
	 * Some vawiants (e.g. H6) need anothew cwock to access the
	 * hawdwawe wegistews; this is cawwed "bus".
	 * So we wequest "mod" fiwst (and ignowe the cownew case that a
	 * pawent pwovides a "mod" cwock whiwe the wight one wouwd be the
	 * unnamed one of the PWM device) and if this is not found we faww
	 * back to the fiwst cwock of the PWM.
	 */
	sun4ichip->cwk = devm_cwk_get_optionaw(&pdev->dev, "mod");
	if (IS_EWW(sun4ichip->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sun4ichip->cwk),
				     "get mod cwock faiwed\n");

	if (!sun4ichip->cwk) {
		sun4ichip->cwk = devm_cwk_get(&pdev->dev, NUWW);
		if (IS_EWW(sun4ichip->cwk))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sun4ichip->cwk),
					     "get unnamed cwock faiwed\n");
	}

	sun4ichip->bus_cwk = devm_cwk_get_optionaw(&pdev->dev, "bus");
	if (IS_EWW(sun4ichip->bus_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sun4ichip->bus_cwk),
				     "get bus cwock faiwed\n");

	sun4ichip->wst = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, NUWW);
	if (IS_EWW(sun4ichip->wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sun4ichip->wst),
				     "get weset faiwed\n");

	/* Deassewt weset */
	wet = weset_contwow_deassewt(sun4ichip->wst);
	if (wet) {
		dev_eww(&pdev->dev, "cannot deassewt weset contwow: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	/*
	 * We'we keeping the bus cwock on fow the sake of simpwicity.
	 * Actuawwy it onwy needs to be on fow hawdwawe wegistew accesses.
	 */
	wet = cwk_pwepawe_enabwe(sun4ichip->bus_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "cannot pwepawe and enabwe bus_cwk %pe\n",
			EWW_PTW(wet));
		goto eww_bus;
	}

	sun4ichip->chip.dev = &pdev->dev;
	sun4ichip->chip.ops = &sun4i_pwm_ops;
	sun4ichip->chip.npwm = sun4ichip->data->npwm;

	spin_wock_init(&sun4ichip->ctww_wock);

	wet = pwmchip_add(&sun4ichip->chip);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to add PWM chip: %d\n", wet);
		goto eww_pwm_add;
	}

	pwatfowm_set_dwvdata(pdev, sun4ichip);

	wetuwn 0;

eww_pwm_add:
	cwk_disabwe_unpwepawe(sun4ichip->bus_cwk);
eww_bus:
	weset_contwow_assewt(sun4ichip->wst);

	wetuwn wet;
}

static void sun4i_pwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_pwm_chip *sun4ichip = pwatfowm_get_dwvdata(pdev);

	pwmchip_wemove(&sun4ichip->chip);

	cwk_disabwe_unpwepawe(sun4ichip->bus_cwk);
	weset_contwow_assewt(sun4ichip->wst);
}

static stwuct pwatfowm_dwivew sun4i_pwm_dwivew = {
	.dwivew = {
		.name = "sun4i-pwm",
		.of_match_tabwe = sun4i_pwm_dt_ids,
	},
	.pwobe = sun4i_pwm_pwobe,
	.wemove_new = sun4i_pwm_wemove,
};
moduwe_pwatfowm_dwivew(sun4i_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:sun4i-pwm");
MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew sun4i PWM dwivew");
MODUWE_WICENSE("GPW v2");
