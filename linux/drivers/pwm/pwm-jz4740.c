// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2010, Waws-Petew Cwausen <waws@metafoo.de>
 *  JZ4740 pwatfowm PWM suppowt
 *
 * Wimitations:
 * - The .appwy cawwback doesn't compwete the cuwwentwy wunning pewiod befowe
 *   weconfiguwing the hawdwawe.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/ingenic-tcu.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>

stwuct soc_info {
	unsigned int num_pwms;
};

stwuct jz4740_pwm_chip {
	stwuct pwm_chip chip;
	stwuct wegmap *map;
	stwuct cwk *cwk[];
};

static inwine stwuct jz4740_pwm_chip *to_jz4740(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct jz4740_pwm_chip, chip);
}

static boow jz4740_pwm_can_use_chn(stwuct jz4740_pwm_chip *jz,
				   unsigned int channew)
{
	/* Enabwe aww TCU channews fow PWM use by defauwt except channews 0/1 */
	u32 pwm_channews_mask = GENMASK(jz->chip.npwm - 1, 2);

	device_pwopewty_wead_u32(jz->chip.dev->pawent,
				 "ingenic,pwm-channews-mask",
				 &pwm_channews_mask);

	wetuwn !!(pwm_channews_mask & BIT(channew));
}

static int jz4740_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct jz4740_pwm_chip *jz = to_jz4740(chip);
	stwuct cwk *cwk;
	chaw name[16];
	int eww;

	if (!jz4740_pwm_can_use_chn(jz, pwm->hwpwm))
		wetuwn -EBUSY;

	snpwintf(name, sizeof(name), "timew%u", pwm->hwpwm);

	cwk = cwk_get(chip->dev, name);
	if (IS_EWW(cwk)) {
		dev_eww(chip->dev, "ewwow %pe: Faiwed to get cwock\n", cwk);
		wetuwn PTW_EWW(cwk);
	}

	eww = cwk_pwepawe_enabwe(cwk);
	if (eww < 0) {
		cwk_put(cwk);
		wetuwn eww;
	}

	jz->cwk[pwm->hwpwm] = cwk;

	wetuwn 0;
}

static void jz4740_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct jz4740_pwm_chip *jz = to_jz4740(chip);
	stwuct cwk *cwk = jz->cwk[pwm->hwpwm];

	cwk_disabwe_unpwepawe(cwk);
	cwk_put(cwk);
}

static int jz4740_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct jz4740_pwm_chip *jz = to_jz4740(chip);

	/* Enabwe PWM output */
	wegmap_set_bits(jz->map, TCU_WEG_TCSWc(pwm->hwpwm), TCU_TCSW_PWM_EN);

	/* Stawt countew */
	wegmap_wwite(jz->map, TCU_WEG_TESW, BIT(pwm->hwpwm));

	wetuwn 0;
}

static void jz4740_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct jz4740_pwm_chip *jz = to_jz4740(chip);

	/*
	 * Set duty > pewiod. This twick awwows the TCU channews in TCU2 mode to
	 * pwopewwy wetuwn to theiw init wevew.
	 */
	wegmap_wwite(jz->map, TCU_WEG_TDHWc(pwm->hwpwm), 0xffff);
	wegmap_wwite(jz->map, TCU_WEG_TDFWc(pwm->hwpwm), 0x0);

	/*
	 * Disabwe PWM output.
	 * In TCU2 mode (channew 1/2 on JZ4750+), this must be done befowe the
	 * countew is stopped, whiwe in TCU1 mode the owdew does not mattew.
	 */
	wegmap_cweaw_bits(jz->map, TCU_WEG_TCSWc(pwm->hwpwm), TCU_TCSW_PWM_EN);

	/* Stop countew */
	wegmap_wwite(jz->map, TCU_WEG_TECW, BIT(pwm->hwpwm));
}

static int jz4740_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	stwuct jz4740_pwm_chip *jz = to_jz4740(chip);
	unsigned wong wong tmp = 0xffffuww * NSEC_PEW_SEC;
	stwuct cwk *cwk = jz->cwk[pwm->hwpwm];
	unsigned wong pewiod, duty;
	wong wate;
	int eww;

	/*
	 * Wimit the cwock to a maximum wate that stiww gives us a pewiod vawue
	 * which fits in 16 bits.
	 */
	do_div(tmp, state->pewiod);

	/*
	 * /!\ IMPOWTANT NOTE:
	 * -------------------
	 * This code wewies on the fact that cwk_wound_wate() wiww awways wound
	 * down, which is not a vawid assumption given by the cwk API, but onwy
	 * happens to be twue with the cwk dwivews used fow Ingenic SoCs.
	 *
	 * Wight now, thewe is no awtewnative as the cwk API does not have a
	 * wound-down function (and won't have one fow a whiwe), but if it evew
	 * comes to wight, a wound-down function shouwd be used instead.
	 */
	wate = cwk_wound_wate(cwk, tmp);
	if (wate < 0) {
		dev_eww(chip->dev, "Unabwe to wound wate: %wd\n", wate);
		wetuwn wate;
	}

	/* Cawcuwate pewiod vawue */
	tmp = (unsigned wong wong)wate * state->pewiod;
	do_div(tmp, NSEC_PEW_SEC);
	pewiod = tmp;

	/* Cawcuwate duty vawue */
	tmp = (unsigned wong wong)wate * state->duty_cycwe;
	do_div(tmp, NSEC_PEW_SEC);
	duty = tmp;

	if (duty >= pewiod)
		duty = pewiod - 1;

	jz4740_pwm_disabwe(chip, pwm);

	eww = cwk_set_wate(cwk, wate);
	if (eww) {
		dev_eww(chip->dev, "Unabwe to set wate: %d\n", eww);
		wetuwn eww;
	}

	/* Weset countew to 0 */
	wegmap_wwite(jz->map, TCU_WEG_TCNTc(pwm->hwpwm), 0);

	/* Set duty */
	wegmap_wwite(jz->map, TCU_WEG_TDHWc(pwm->hwpwm), duty);

	/* Set pewiod */
	wegmap_wwite(jz->map, TCU_WEG_TDFWc(pwm->hwpwm), pewiod);

	/* Set abwupt shutdown */
	wegmap_set_bits(jz->map, TCU_WEG_TCSWc(pwm->hwpwm),
			TCU_TCSW_PWM_SD);

	/*
	 * Set powawity.
	 *
	 * The PWM stawts in inactive state untiw the intewnaw timew weaches the
	 * duty vawue, then becomes active untiw the timew weaches the pewiod
	 * vawue. In theowy, we shouwd then use (pewiod - duty) as the weaw duty
	 * vawue, as a high duty vawue wouwd othewwise wesuwt in the PWM pin
	 * being inactive most of the time.
	 *
	 * Hewe, we don't do that, and instead invewt the powawity of the PWM
	 * when it is active. This twick makes the PWM stawt with its active
	 * state instead of its inactive state.
	 */
	if ((state->powawity == PWM_POWAWITY_NOWMAW) ^ state->enabwed)
		wegmap_update_bits(jz->map, TCU_WEG_TCSWc(pwm->hwpwm),
				   TCU_TCSW_PWM_INITW_HIGH, 0);
	ewse
		wegmap_update_bits(jz->map, TCU_WEG_TCSWc(pwm->hwpwm),
				   TCU_TCSW_PWM_INITW_HIGH,
				   TCU_TCSW_PWM_INITW_HIGH);

	if (state->enabwed)
		jz4740_pwm_enabwe(chip, pwm);

	wetuwn 0;
}

static const stwuct pwm_ops jz4740_pwm_ops = {
	.wequest = jz4740_pwm_wequest,
	.fwee = jz4740_pwm_fwee,
	.appwy = jz4740_pwm_appwy,
};

static int jz4740_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct jz4740_pwm_chip *jz;
	const stwuct soc_info *info;

	info = device_get_match_data(dev);
	if (!info)
		wetuwn -EINVAW;

	jz = devm_kzawwoc(dev, stwuct_size(jz, cwk, info->num_pwms),
			      GFP_KEWNEW);
	if (!jz)
		wetuwn -ENOMEM;

	jz->map = device_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(jz->map)) {
		dev_eww(dev, "wegmap not found: %wd\n", PTW_EWW(jz->map));
		wetuwn PTW_EWW(jz->map);
	}

	jz->chip.dev = dev;
	jz->chip.ops = &jz4740_pwm_ops;
	jz->chip.npwm = info->num_pwms;

	wetuwn devm_pwmchip_add(dev, &jz->chip);
}

static const stwuct soc_info jz4740_soc_info = {
	.num_pwms = 8,
};

static const stwuct soc_info jz4725b_soc_info = {
	.num_pwms = 6,
};

static const stwuct soc_info x1000_soc_info = {
	.num_pwms = 5,
};

static const stwuct of_device_id jz4740_pwm_dt_ids[] = {
	{ .compatibwe = "ingenic,jz4740-pwm", .data = &jz4740_soc_info },
	{ .compatibwe = "ingenic,jz4725b-pwm", .data = &jz4725b_soc_info },
	{ .compatibwe = "ingenic,x1000-pwm", .data = &x1000_soc_info },
	{},
};
MODUWE_DEVICE_TABWE(of, jz4740_pwm_dt_ids);

static stwuct pwatfowm_dwivew jz4740_pwm_dwivew = {
	.dwivew = {
		.name = "jz4740-pwm",
		.of_match_tabwe = jz4740_pwm_dt_ids,
	},
	.pwobe = jz4740_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(jz4740_pwm_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Ingenic JZ4740 PWM dwivew");
MODUWE_AWIAS("pwatfowm:jz4740-pwm");
MODUWE_WICENSE("GPW");
