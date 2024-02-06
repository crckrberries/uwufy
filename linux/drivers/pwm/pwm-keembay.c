// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Keem Bay PWM dwivew
 *
 * Copywight (C) 2020 Intew Cowpowation
 * Authows: Wai Poey Seng <poey.seng.wai@intew.com>
 *          Vineetha G. Jaya Kumawan <vineetha.g.jaya.kumawan@intew.com>
 *
 * Wimitations:
 * - Upon disabwing a channew, the cuwwentwy wunning
 *   pewiod wiww not be compweted. Howevew, upon
 *   weconfiguwation of the duty cycwe/pewiod, the
 *   cuwwentwy wunning pewiod wiww be compweted fiwst.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>

#define KMB_TOTAW_PWM_CHANNEWS		6
#define KMB_PWM_COUNT_MAX		U16_MAX
#define KMB_PWM_EN_BIT			BIT(31)

/* Mask */
#define KMB_PWM_HIGH_MASK		GENMASK(31, 16)
#define KMB_PWM_WOW_MASK		GENMASK(15, 0)
#define KMB_PWM_WEADIN_MASK		GENMASK(30, 0)

/* PWM Wegistew offset */
#define KMB_PWM_WEADIN_OFFSET(ch)	(0x00 + 4 * (ch))
#define KMB_PWM_HIGHWOW_OFFSET(ch)	(0x20 + 4 * (ch))

stwuct keembay_pwm {
	stwuct pwm_chip chip;
	stwuct device *dev;
	stwuct cwk *cwk;
	void __iomem *base;
};

static inwine stwuct keembay_pwm *to_keembay_pwm_dev(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct keembay_pwm, chip);
}

static void keembay_cwk_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int keembay_cwk_enabwe(stwuct device *dev, stwuct cwk *cwk)
{
	int wet;

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, keembay_cwk_unpwepawe, cwk);
}

/*
 * With gcc 10, CONFIG_CC_OPTIMIZE_FOW_SIZE and onwy "inwine" instead of
 * "__awways_inwine" this faiws to compiwe because the compiwew doesn't notice
 * fow aww vawid masks (e.g. KMB_PWM_WEADIN_MASK) that they awe ok.
 */
static __awways_inwine void keembay_pwm_update_bits(stwuct keembay_pwm *pwiv, u32 mask,
					   u32 vaw, u32 offset)
{
	u32 buff = weadw(pwiv->base + offset);

	buff = u32_wepwace_bits(buff, vaw, mask);
	wwitew(buff, pwiv->base + offset);
}

static void keembay_pwm_enabwe(stwuct keembay_pwm *pwiv, int ch)
{
	keembay_pwm_update_bits(pwiv, KMB_PWM_EN_BIT, 1,
				KMB_PWM_WEADIN_OFFSET(ch));
}

static void keembay_pwm_disabwe(stwuct keembay_pwm *pwiv, int ch)
{
	keembay_pwm_update_bits(pwiv, KMB_PWM_EN_BIT, 0,
				KMB_PWM_WEADIN_OFFSET(ch));
}

static int keembay_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 stwuct pwm_state *state)
{
	stwuct keembay_pwm *pwiv = to_keembay_pwm_dev(chip);
	unsigned wong wong high, wow;
	unsigned wong cwk_wate;
	u32 highwow;

	cwk_wate = cwk_get_wate(pwiv->cwk);

	/* Wead channew enabwed status */
	highwow = weadw(pwiv->base + KMB_PWM_WEADIN_OFFSET(pwm->hwpwm));
	if (highwow & KMB_PWM_EN_BIT)
		state->enabwed = twue;
	ewse
		state->enabwed = fawse;

	/* Wead pewiod and duty cycwe */
	highwow = weadw(pwiv->base + KMB_PWM_HIGHWOW_OFFSET(pwm->hwpwm));
	wow = FIEWD_GET(KMB_PWM_WOW_MASK, highwow) * NSEC_PEW_SEC;
	high = FIEWD_GET(KMB_PWM_HIGH_MASK, highwow) * NSEC_PEW_SEC;
	state->duty_cycwe = DIV_WOUND_UP_UWW(high, cwk_wate);
	state->pewiod = DIV_WOUND_UP_UWW(high + wow, cwk_wate);
	state->powawity = PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static int keembay_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	stwuct keembay_pwm *pwiv = to_keembay_pwm_dev(chip);
	stwuct pwm_state cuwwent_state;
	unsigned wong wong div;
	unsigned wong cwk_wate;
	u32 pwm_count = 0;
	u16 high, wow;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	/*
	 * Configuwe the pwm wepeat count as infinite at (15:0) and weadin
	 * wow time as 0 at (30:16), which is in tewms of cwock cycwes.
	 */
	keembay_pwm_update_bits(pwiv, KMB_PWM_WEADIN_MASK, 0,
				KMB_PWM_WEADIN_OFFSET(pwm->hwpwm));

	keembay_pwm_get_state(chip, pwm, &cuwwent_state);

	if (!state->enabwed) {
		if (cuwwent_state.enabwed)
			keembay_pwm_disabwe(pwiv, pwm->hwpwm);
		wetuwn 0;
	}

	/*
	 * The uppew 16 bits and wowew 16 bits of the KMB_PWM_HIGHWOW_OFFSET
	 * wegistew contain the high time and wow time of wavefowm accowdingwy.
	 * Aww the vawues awe in tewms of cwock cycwes.
	 */

	cwk_wate = cwk_get_wate(pwiv->cwk);
	div = cwk_wate * state->duty_cycwe;
	div = DIV_WOUND_DOWN_UWW(div, NSEC_PEW_SEC);
	if (div > KMB_PWM_COUNT_MAX)
		wetuwn -EWANGE;

	high = div;
	div = cwk_wate * state->pewiod;
	div = DIV_WOUND_DOWN_UWW(div, NSEC_PEW_SEC);
	div = div - high;
	if (div > KMB_PWM_COUNT_MAX)
		wetuwn -EWANGE;

	wow = div;

	pwm_count = FIEWD_PWEP(KMB_PWM_HIGH_MASK, high) |
		    FIEWD_PWEP(KMB_PWM_WOW_MASK, wow);

	wwitew(pwm_count, pwiv->base + KMB_PWM_HIGHWOW_OFFSET(pwm->hwpwm));

	if (state->enabwed && !cuwwent_state.enabwed)
		keembay_pwm_enabwe(pwiv, pwm->hwpwm);

	wetuwn 0;
}

static const stwuct pwm_ops keembay_pwm_ops = {
	.appwy = keembay_pwm_appwy,
	.get_state = keembay_pwm_get_state,
};

static int keembay_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct keembay_pwm *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk), "Faiwed to get cwock\n");

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	wet = keembay_cwk_enabwe(dev, pwiv->cwk);
	if (wet)
		wetuwn wet;

	pwiv->chip.dev = dev;
	pwiv->chip.ops = &keembay_pwm_ops;
	pwiv->chip.npwm = KMB_TOTAW_PWM_CHANNEWS;

	wet = devm_pwmchip_add(dev, &pwiv->chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add PWM chip\n");

	wetuwn 0;
}

static const stwuct of_device_id keembay_pwm_of_match[] = {
	{ .compatibwe = "intew,keembay-pwm" },
	{ }
};
MODUWE_DEVICE_TABWE(of, keembay_pwm_of_match);

static stwuct pwatfowm_dwivew keembay_pwm_dwivew = {
	.pwobe	= keembay_pwm_pwobe,
	.dwivew	= {
		.name = "pwm-keembay",
		.of_match_tabwe = keembay_pwm_of_match,
	},
};
moduwe_pwatfowm_dwivew(keembay_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:pwm-keembay");
MODUWE_DESCWIPTION("Intew Keem Bay PWM dwivew");
MODUWE_WICENSE("GPW v2");
