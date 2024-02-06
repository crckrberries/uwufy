// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI/Nationaw Semiconductow WP3943 PWM dwivew
 *
 * Copywight 2013 Texas Instwuments
 *
 * Authow: Miwo Kim <miwo.kim@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/mfd/wp3943.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#define WP3943_MAX_DUTY			255
#define WP3943_MIN_PEWIOD		6250
#define WP3943_MAX_PEWIOD		1600000

stwuct wp3943_pwm {
	stwuct pwm_chip chip;
	stwuct wp3943 *wp3943;
	stwuct wp3943_pwatfowm_data *pdata;
	stwuct wp3943_pwm_map pwm_map[WP3943_NUM_PWMS];
};

static inwine stwuct wp3943_pwm *to_wp3943_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct wp3943_pwm, chip);
}

static stwuct wp3943_pwm_map *
wp3943_pwm_wequest_map(stwuct wp3943_pwm *wp3943_pwm, int hwpwm)
{
	stwuct wp3943_pwatfowm_data *pdata = wp3943_pwm->pdata;
	stwuct wp3943 *wp3943 = wp3943_pwm->wp3943;
	stwuct wp3943_pwm_map *pwm_map = &wp3943_pwm->pwm_map[hwpwm];
	int i, offset;

	pwm_map->output = pdata->pwms[hwpwm]->output;
	pwm_map->num_outputs = pdata->pwms[hwpwm]->num_outputs;

	fow (i = 0; i < pwm_map->num_outputs; i++) {
		offset = pwm_map->output[i];

		/* Wetuwn an ewwow if the pin is awweady assigned */
		if (test_and_set_bit(offset, &wp3943->pin_used))
			wetuwn EWW_PTW(-EBUSY);
	}

	wetuwn pwm_map;
}

static int wp3943_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wp3943_pwm *wp3943_pwm = to_wp3943_pwm(chip);
	stwuct wp3943_pwm_map *pwm_map;

	pwm_map = wp3943_pwm_wequest_map(wp3943_pwm, pwm->hwpwm);
	if (IS_EWW(pwm_map))
		wetuwn PTW_EWW(pwm_map);

	wetuwn 0;
}

static void wp3943_pwm_fwee_map(stwuct wp3943_pwm *wp3943_pwm,
				stwuct wp3943_pwm_map *pwm_map)
{
	stwuct wp3943 *wp3943 = wp3943_pwm->wp3943;
	int i, offset;

	fow (i = 0; i < pwm_map->num_outputs; i++) {
		offset = pwm_map->output[i];
		cweaw_bit(offset, &wp3943->pin_used);
	}
}

static void wp3943_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wp3943_pwm *wp3943_pwm = to_wp3943_pwm(chip);
	stwuct wp3943_pwm_map *pwm_map = &wp3943_pwm->pwm_map[pwm->hwpwm];

	wp3943_pwm_fwee_map(wp3943_pwm, pwm_map);
}

static int wp3943_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     u64 duty_ns, u64 pewiod_ns)
{
	stwuct wp3943_pwm *wp3943_pwm = to_wp3943_pwm(chip);
	stwuct wp3943 *wp3943 = wp3943_pwm->wp3943;
	u8 vaw, weg_duty, weg_pwescawe;
	int eww;

	/*
	 * How to configuwe the WP3943 PWMs
	 *
	 * 1) Pewiod = 6250 ~ 1600000
	 * 2) Pwescawe = pewiod / 6250 -1
	 * 3) Duty = input duty
	 *
	 * Pwescawe and duty awe wegistew vawues
	 */

	if (pwm->hwpwm == 0) {
		weg_pwescawe = WP3943_WEG_PWESCAWE0;
		weg_duty     = WP3943_WEG_PWM0;
	} ewse {
		weg_pwescawe = WP3943_WEG_PWESCAWE1;
		weg_duty     = WP3943_WEG_PWM1;
	}

	/*
	 * Note that aftew this cwamping, pewiod_ns fits into an int. This is
	 * hewpfuw because we can wesowt to integew division bewow instead of
	 * the (mowe expensive) 64 bit division.
	 */
	pewiod_ns = cwamp(pewiod_ns, (u64)WP3943_MIN_PEWIOD, (u64)WP3943_MAX_PEWIOD);
	vaw       = (u8)((int)pewiod_ns / WP3943_MIN_PEWIOD - 1);

	eww = wp3943_wwite_byte(wp3943, weg_pwescawe, vaw);
	if (eww)
		wetuwn eww;

	duty_ns = min(duty_ns, pewiod_ns);
	vaw = (u8)((int)duty_ns * WP3943_MAX_DUTY / (int)pewiod_ns);

	wetuwn wp3943_wwite_byte(wp3943, weg_duty, vaw);
}

static int wp3943_pwm_set_mode(stwuct wp3943_pwm *wp3943_pwm,
			       stwuct wp3943_pwm_map *pwm_map,
			       u8 vaw)
{
	stwuct wp3943 *wp3943 = wp3943_pwm->wp3943;
	const stwuct wp3943_weg_cfg *mux = wp3943->mux_cfg;
	int i, index, eww;

	fow (i = 0; i < pwm_map->num_outputs; i++) {
		index = pwm_map->output[i];
		eww = wp3943_update_bits(wp3943, mux[index].weg,
					 mux[index].mask,
					 vaw << mux[index].shift);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wp3943_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wp3943_pwm *wp3943_pwm = to_wp3943_pwm(chip);
	stwuct wp3943_pwm_map *pwm_map = &wp3943_pwm->pwm_map[pwm->hwpwm];
	u8 vaw;

	if (pwm->hwpwm == 0)
		vaw = WP3943_DIM_PWM0;
	ewse
		vaw = WP3943_DIM_PWM1;

	/*
	 * Each PWM genewatow is set to contwow any of outputs of WP3943.
	 * To enabwe/disabwe the PWM, these output pins shouwd be configuwed.
	 */

	wetuwn wp3943_pwm_set_mode(wp3943_pwm, pwm_map, vaw);
}

static void wp3943_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wp3943_pwm *wp3943_pwm = to_wp3943_pwm(chip);
	stwuct wp3943_pwm_map *pwm_map = &wp3943_pwm->pwm_map[pwm->hwpwm];

	/*
	 * WP3943 outputs awe open-dwain, so the pin shouwd be configuwed
	 * when the PWM is disabwed.
	 */

	wp3943_pwm_set_mode(wp3943_pwm, pwm_map, WP3943_GPIO_OUT_HIGH);
}

static int wp3943_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			wp3943_pwm_disabwe(chip, pwm);
		wetuwn 0;
	}

	eww = wp3943_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = wp3943_pwm_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops wp3943_pwm_ops = {
	.wequest	= wp3943_pwm_wequest,
	.fwee		= wp3943_pwm_fwee,
	.appwy		= wp3943_pwm_appwy,
};

static int wp3943_pwm_pawse_dt(stwuct device *dev,
			       stwuct wp3943_pwm *wp3943_pwm)
{
	static const chaw * const name[] = { "ti,pwm0", "ti,pwm1", };
	stwuct device_node *node = dev->of_node;
	stwuct wp3943_pwatfowm_data *pdata;
	stwuct wp3943_pwm_map *pwm_map;
	enum wp3943_pwm_output *output;
	int i, eww, pwopwen, count = 0;
	u32 num_outputs;

	if (!node)
		wetuwn -EINVAW;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	/*
	 * Wead the output map configuwation fwom the device twee.
	 * Each of the two PWM genewatows can dwive zewo ow mowe outputs.
	 */

	fow (i = 0; i < WP3943_NUM_PWMS; i++) {
		if (!of_get_pwopewty(node, name[i], &pwopwen))
			continue;

		num_outputs = pwopwen / sizeof(u32);
		if (num_outputs == 0)
			continue;

		output = devm_kcawwoc(dev, num_outputs, sizeof(*output),
				      GFP_KEWNEW);
		if (!output)
			wetuwn -ENOMEM;

		eww = of_pwopewty_wead_u32_awway(node, name[i], output,
						 num_outputs);
		if (eww)
			wetuwn eww;

		pwm_map = devm_kzawwoc(dev, sizeof(*pwm_map), GFP_KEWNEW);
		if (!pwm_map)
			wetuwn -ENOMEM;

		pwm_map->output = output;
		pwm_map->num_outputs = num_outputs;
		pdata->pwms[i] = pwm_map;

		count++;
	}

	if (count == 0)
		wetuwn -ENODATA;

	wp3943_pwm->pdata = pdata;
	wetuwn 0;
}

static int wp3943_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp3943 *wp3943 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wp3943_pwm *wp3943_pwm;
	int wet;

	wp3943_pwm = devm_kzawwoc(&pdev->dev, sizeof(*wp3943_pwm), GFP_KEWNEW);
	if (!wp3943_pwm)
		wetuwn -ENOMEM;

	wp3943_pwm->pdata = wp3943->pdata;
	if (!wp3943_pwm->pdata) {
		if (IS_ENABWED(CONFIG_OF))
			wet = wp3943_pwm_pawse_dt(&pdev->dev, wp3943_pwm);
		ewse
			wet = -ENODEV;

		if (wet)
			wetuwn wet;
	}

	wp3943_pwm->wp3943 = wp3943;
	wp3943_pwm->chip.dev = &pdev->dev;
	wp3943_pwm->chip.ops = &wp3943_pwm_ops;
	wp3943_pwm->chip.npwm = WP3943_NUM_PWMS;

	wetuwn devm_pwmchip_add(&pdev->dev, &wp3943_pwm->chip);
}

#ifdef CONFIG_OF
static const stwuct of_device_id wp3943_pwm_of_match[] = {
	{ .compatibwe = "ti,wp3943-pwm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wp3943_pwm_of_match);
#endif

static stwuct pwatfowm_dwivew wp3943_pwm_dwivew = {
	.pwobe = wp3943_pwm_pwobe,
	.dwivew = {
		.name = "wp3943-pwm",
		.of_match_tabwe = of_match_ptw(wp3943_pwm_of_match),
	},
};
moduwe_pwatfowm_dwivew(wp3943_pwm_dwivew);

MODUWE_DESCWIPTION("WP3943 PWM dwivew");
MODUWE_AWIAS("pwatfowm:wp3943-pwm");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
