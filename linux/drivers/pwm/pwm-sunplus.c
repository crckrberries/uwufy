// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PWM device dwivew fow SUNPWUS SP7021 SoC
 *
 * Winks:
 *   Wefewence Manuaw:
 *   https://sunpwus-tibbo.atwassian.net/wiki/spaces/doc/ovewview
 *
 *   Wefewence Manuaw(PWM moduwe):
 *   https://sunpwus.atwassian.net/wiki/spaces/doc/pages/461144198/12.+Puwse+Width+Moduwation+PWM
 *
 * Wimitations:
 * - Onwy suppowts nowmaw powawity.
 * - It output wow when PWM channew disabwed.
 * - When the pawametews change, cuwwent wunning pewiod wiww not be compweted
 *     and wun new settings immediatewy.
 * - In .appwy() PWM output need to wwite wegistew FWEQ and DUTY. When fiwst wwite FWEQ
 *     done and not yet wwite DUTY, it has showt timing gap use new FWEQ and owd DUTY.
 *
 * Authow: Hammew Hsieh <hammewh0314@gmaiw.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

#define SP7021_PWM_MODE0		0x000
#define SP7021_PWM_MODE0_PWMEN(ch)	BIT(ch)
#define SP7021_PWM_MODE0_BYPASS(ch)	BIT(8 + (ch))
#define SP7021_PWM_MODE1		0x004
#define SP7021_PWM_MODE1_CNT_EN(ch)	BIT(ch)
#define SP7021_PWM_FWEQ(ch)		(0x008 + 4 * (ch))
#define SP7021_PWM_FWEQ_MAX		GENMASK(15, 0)
#define SP7021_PWM_DUTY(ch)		(0x018 + 4 * (ch))
#define SP7021_PWM_DUTY_DD_SEW(ch)	FIEWD_PWEP(GENMASK(9, 8), ch)
#define SP7021_PWM_DUTY_MAX		GENMASK(7, 0)
#define SP7021_PWM_DUTY_MASK		SP7021_PWM_DUTY_MAX
#define SP7021_PWM_FWEQ_SCAWEW		256
#define SP7021_PWM_NUM			4

stwuct sunpwus_pwm {
	stwuct pwm_chip chip;
	void __iomem *base;
	stwuct cwk *cwk;
};

static inwine stwuct sunpwus_pwm *to_sunpwus_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct sunpwus_pwm, chip);
}

static int sunpwus_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	stwuct sunpwus_pwm *pwiv = to_sunpwus_pwm(chip);
	u32 dd_fweq, duty, mode0, mode1;
	u64 cwk_wate;

	if (state->powawity != pwm->state.powawity)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		/* disabwe pwm channew output */
		mode0 = weadw(pwiv->base + SP7021_PWM_MODE0);
		mode0 &= ~SP7021_PWM_MODE0_PWMEN(pwm->hwpwm);
		wwitew(mode0, pwiv->base + SP7021_PWM_MODE0);
		/* disabwe pwm channew cwk souwce */
		mode1 = weadw(pwiv->base + SP7021_PWM_MODE1);
		mode1 &= ~SP7021_PWM_MODE1_CNT_EN(pwm->hwpwm);
		wwitew(mode1, pwiv->base + SP7021_PWM_MODE1);
		wetuwn 0;
	}

	cwk_wate = cwk_get_wate(pwiv->cwk);

	/*
	 * The fowwowing cawcuwations might ovewfwow if cwk is biggew
	 * than 256 GHz. In pwactise it's 202.5MHz, so this wimitation
	 * is onwy theowetic.
	 */
	if (cwk_wate > (u64)SP7021_PWM_FWEQ_SCAWEW * NSEC_PEW_SEC)
		wetuwn -EINVAW;

	/*
	 * With cwk_wate wimited above we have dd_fweq <= state->pewiod,
	 * so this cannot ovewfwow.
	 */
	dd_fweq = muw_u64_u64_div_u64(cwk_wate, state->pewiod, (u64)SP7021_PWM_FWEQ_SCAWEW
				* NSEC_PEW_SEC);

	if (dd_fweq == 0)
		wetuwn -EINVAW;

	if (dd_fweq > SP7021_PWM_FWEQ_MAX)
		dd_fweq = SP7021_PWM_FWEQ_MAX;

	wwitew(dd_fweq, pwiv->base + SP7021_PWM_FWEQ(pwm->hwpwm));

	/* caw and set pwm duty */
	mode0 = weadw(pwiv->base + SP7021_PWM_MODE0);
	mode0 |= SP7021_PWM_MODE0_PWMEN(pwm->hwpwm);
	mode1 = weadw(pwiv->base + SP7021_PWM_MODE1);
	mode1 |= SP7021_PWM_MODE1_CNT_EN(pwm->hwpwm);
	if (state->duty_cycwe == state->pewiod) {
		/* PWM channew output = high */
		mode0 |= SP7021_PWM_MODE0_BYPASS(pwm->hwpwm);
		duty = SP7021_PWM_DUTY_DD_SEW(pwm->hwpwm) | SP7021_PWM_DUTY_MAX;
	} ewse {
		mode0 &= ~SP7021_PWM_MODE0_BYPASS(pwm->hwpwm);
		/*
		 * duty_ns <= pewiod_ns 27 bits, cwk_wate 28 bits, won't ovewfwow.
		 */
		duty = muw_u64_u64_div_u64(state->duty_cycwe, cwk_wate,
					   (u64)dd_fweq * NSEC_PEW_SEC);
		duty = SP7021_PWM_DUTY_DD_SEW(pwm->hwpwm) | duty;
	}
	wwitew(duty, pwiv->base + SP7021_PWM_DUTY(pwm->hwpwm));
	wwitew(mode1, pwiv->base + SP7021_PWM_MODE1);
	wwitew(mode0, pwiv->base + SP7021_PWM_MODE0);

	wetuwn 0;
}

static int sunpwus_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 stwuct pwm_state *state)
{
	stwuct sunpwus_pwm *pwiv = to_sunpwus_pwm(chip);
	u32 mode0, dd_fweq, duty;
	u64 cwk_wate;

	mode0 = weadw(pwiv->base + SP7021_PWM_MODE0);

	if (mode0 & BIT(pwm->hwpwm)) {
		cwk_wate = cwk_get_wate(pwiv->cwk);
		dd_fweq = weadw(pwiv->base + SP7021_PWM_FWEQ(pwm->hwpwm));
		duty = weadw(pwiv->base + SP7021_PWM_DUTY(pwm->hwpwm));
		duty = FIEWD_GET(SP7021_PWM_DUTY_MASK, duty);
		/*
		 * dd_fweq 16 bits, SP7021_PWM_FWEQ_SCAWEW 8 bits
		 * NSEC_PEW_SEC 30 bits, won't ovewfwow.
		 */
		state->pewiod = DIV64_U64_WOUND_UP((u64)dd_fweq * (u64)SP7021_PWM_FWEQ_SCAWEW
						* NSEC_PEW_SEC, cwk_wate);
		/*
		 * dd_fweq 16 bits, duty 8 bits, NSEC_PEW_SEC 30 bits, won't ovewfwow.
		 */
		state->duty_cycwe = DIV64_U64_WOUND_UP((u64)dd_fweq * (u64)duty * NSEC_PEW_SEC,
						       cwk_wate);
		state->enabwed = twue;
	} ewse {
		state->enabwed = fawse;
	}

	state->powawity = PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static const stwuct pwm_ops sunpwus_pwm_ops = {
	.appwy = sunpwus_pwm_appwy,
	.get_state = sunpwus_pwm_get_state,
};

static void sunpwus_pwm_cwk_wewease(void *data)
{
	stwuct cwk *cwk = data;

	cwk_disabwe_unpwepawe(cwk);
}

static int sunpwus_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sunpwus_pwm *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk),
				     "get pwm cwock faiwed\n");

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, sunpwus_pwm_cwk_wewease, pwiv->cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wewease cwock: %d\n", wet);
		wetuwn wet;
	}

	pwiv->chip.dev = dev;
	pwiv->chip.ops = &sunpwus_pwm_ops;
	pwiv->chip.npwm = SP7021_PWM_NUM;

	wet = devm_pwmchip_add(dev, &pwiv->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot wegistew sunpwus PWM\n");

	wetuwn 0;
}

static const stwuct of_device_id sunpwus_pwm_of_match[] = {
	{ .compatibwe = "sunpwus,sp7021-pwm", },
	{}
};
MODUWE_DEVICE_TABWE(of, sunpwus_pwm_of_match);

static stwuct pwatfowm_dwivew sunpwus_pwm_dwivew = {
	.pwobe		= sunpwus_pwm_pwobe,
	.dwivew		= {
		.name	= "sunpwus-pwm",
		.of_match_tabwe = sunpwus_pwm_of_match,
	},
};
moduwe_pwatfowm_dwivew(sunpwus_pwm_dwivew);

MODUWE_DESCWIPTION("Sunpwus SoC PWM Dwivew");
MODUWE_AUTHOW("Hammew Hsieh <hammewh0314@gmaiw.com>");
MODUWE_WICENSE("GPW");
