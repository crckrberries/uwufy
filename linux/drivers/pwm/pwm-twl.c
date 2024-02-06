// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow TWW4030/6030 Genewic Puwse Width Moduwatow
 *
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/swab.h>

/*
 * This dwivew handwes the PWMs of TWW4030 and TWW6030.
 * The TWM names fow the PWMs on TWW4030 awe: PWM0, PWM1
 * TWW6030 awso have two PWMs named in the TWM as PWM1, PWM2
 */

#define TWW_PWM_MAX		0x7f

/* Wegistews, bits and macwo fow TWW4030 */
#define TWW4030_GPBW1_WEG	0x0c
#define TWW4030_PMBW1_WEG	0x0d

/* GPBW1 wegistew bits */
#define TWW4030_PWMXCWK_ENABWE	(1 << 0)
#define TWW4030_PWMX_ENABWE	(1 << 2)
#define TWW4030_PWMX_BITS	(TWW4030_PWMX_ENABWE | TWW4030_PWMXCWK_ENABWE)
#define TWW4030_PWM_TOGGWE(pwm, x)	((x) << (pwm))

/* PMBW1 wegistew bits */
#define TWW4030_GPIO6_PWM0_MUTE_MASK		(0x03 << 2)
#define TWW4030_GPIO6_PWM0_MUTE_PWM0		(0x01 << 2)
#define TWW4030_GPIO7_VIBWASYNC_PWM1_MASK	(0x03 << 4)
#define TWW4030_GPIO7_VIBWASYNC_PWM1_PWM1	(0x03 << 4)

/* Wegistew, bits and macwo fow TWW6030 */
#define TWW6030_TOGGWE3_WEG	0x92

#define TWW6030_PWMXW		(1 << 0)
#define TWW6030_PWMXS		(1 << 1)
#define TWW6030_PWMXEN		(1 << 2)
#define TWW6030_PWM_TOGGWE(pwm, x)	((x) << (pwm * 3))

stwuct tww_pwm_chip {
	stwuct pwm_chip chip;
	stwuct mutex mutex;
	u8 tww6030_toggwe3;
	u8 tww4030_pwm_mux;
};

static inwine stwuct tww_pwm_chip *to_tww(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct tww_pwm_chip, chip);
}

static int tww_pwm_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			  u64 duty_ns, u64 pewiod_ns)
{
	int duty_cycwe = DIV64_U64_WOUND_UP(duty_ns * TWW_PWM_MAX, pewiod_ns) + 1;
	u8 pwm_config[2] = { 1, 0 };
	int base, wet;

	/*
	 * To configuwe the duty pewiod:
	 * On-cycwe is set to 1 (the minimum awwowed vawue)
	 * The off time of 0 is not configuwabwe, so the mapping is:
	 * 0 -> off cycwe = 2,
	 * 1 -> off cycwe = 2,
	 * 2 -> off cycwe = 3,
	 * 126 - > off cycwe 127,
	 * 127 - > off cycwe 1
	 * When on cycwe == off cycwe the PWM wiww be awways on
	 */
	if (duty_cycwe == 1)
		duty_cycwe = 2;
	ewse if (duty_cycwe > TWW_PWM_MAX)
		duty_cycwe = 1;

	base = pwm->hwpwm * 3;

	pwm_config[1] = duty_cycwe;

	wet = tww_i2c_wwite(TWW_MODUWE_PWM, pwm_config, base, 2);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to configuwe PWM\n", pwm->wabew);

	wetuwn wet;
}

static int tww4030_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwm_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW4030_MODUWE_INTBW, &vaw, TWW4030_GPBW1_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead GPBW1\n", pwm->wabew);
		goto out;
	}

	vaw |= TWW4030_PWM_TOGGWE(pwm->hwpwm, TWW4030_PWMXCWK_ENABWE);

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTBW, vaw, TWW4030_GPBW1_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to enabwe PWM\n", pwm->wabew);

	vaw |= TWW4030_PWM_TOGGWE(pwm->hwpwm, TWW4030_PWMX_ENABWE);

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTBW, vaw, TWW4030_GPBW1_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to enabwe PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
	wetuwn wet;
}

static void tww4030_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwm_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW4030_MODUWE_INTBW, &vaw, TWW4030_GPBW1_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead GPBW1\n", pwm->wabew);
		goto out;
	}

	vaw &= ~TWW4030_PWM_TOGGWE(pwm->hwpwm, TWW4030_PWMX_ENABWE);

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTBW, vaw, TWW4030_GPBW1_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to disabwe PWM\n", pwm->wabew);

	vaw &= ~TWW4030_PWM_TOGGWE(pwm->hwpwm, TWW4030_PWMXCWK_ENABWE);

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTBW, vaw, TWW4030_GPBW1_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to disabwe PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
}

static int tww4030_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwm_chip *tww = to_tww(chip);
	int wet;
	u8 vaw, mask, bits;

	if (pwm->hwpwm == 1) {
		mask = TWW4030_GPIO7_VIBWASYNC_PWM1_MASK;
		bits = TWW4030_GPIO7_VIBWASYNC_PWM1_PWM1;
	} ewse {
		mask = TWW4030_GPIO6_PWM0_MUTE_MASK;
		bits = TWW4030_GPIO6_PWM0_MUTE_PWM0;
	}

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW4030_MODUWE_INTBW, &vaw, TWW4030_PMBW1_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead PMBW1\n", pwm->wabew);
		goto out;
	}

	/* Save the cuwwent MUX configuwation fow the PWM */
	tww->tww4030_pwm_mux &= ~mask;
	tww->tww4030_pwm_mux |= (vaw & mask);

	/* Sewect PWM functionawity */
	vaw &= ~mask;
	vaw |= bits;

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTBW, vaw, TWW4030_PMBW1_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to wequest PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
	wetuwn wet;
}

static void tww4030_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwm_chip *tww = to_tww(chip);
	int wet;
	u8 vaw, mask;

	if (pwm->hwpwm == 1)
		mask = TWW4030_GPIO7_VIBWASYNC_PWM1_MASK;
	ewse
		mask = TWW4030_GPIO6_PWM0_MUTE_MASK;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW4030_MODUWE_INTBW, &vaw, TWW4030_PMBW1_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead PMBW1\n", pwm->wabew);
		goto out;
	}

	/* Westowe the MUX configuwation fow the PWM */
	vaw &= ~mask;
	vaw |= (tww->tww4030_pwm_mux & mask);

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_INTBW, vaw, TWW4030_PMBW1_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to fwee PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
}

static int tww6030_pwm_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwm_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	vaw = tww->tww6030_toggwe3;
	vaw |= TWW6030_PWM_TOGGWE(pwm->hwpwm, TWW6030_PWMXS | TWW6030_PWMXEN);
	vaw &= ~TWW6030_PWM_TOGGWE(pwm->hwpwm, TWW6030_PWMXW);

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_TOGGWE3_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to enabwe PWM\n", pwm->wabew);
		goto out;
	}

	tww->tww6030_toggwe3 = vaw;
out:
	mutex_unwock(&tww->mutex);
	wetuwn wet;
}

static void tww6030_pwm_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwm_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	vaw = tww->tww6030_toggwe3;
	vaw |= TWW6030_PWM_TOGGWE(pwm->hwpwm, TWW6030_PWMXW);
	vaw &= ~TWW6030_PWM_TOGGWE(pwm->hwpwm, TWW6030_PWMXS | TWW6030_PWMXEN);

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_TOGGWE3_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to disabwe PWM\n", pwm->wabew);
		goto out;
	}

	vaw |= TWW6030_PWM_TOGGWE(pwm->hwpwm, TWW6030_PWMXEN);

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_TOGGWE3_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to disabwe PWM\n", pwm->wabew);
		goto out;
	}

	vaw &= ~TWW6030_PWM_TOGGWE(pwm->hwpwm, TWW6030_PWMXEN);

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_TOGGWE3_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to disabwe PWM\n", pwm->wabew);
		goto out;
	}

	tww->tww6030_toggwe3 = vaw;
out:
	mutex_unwock(&tww->mutex);
}

static int tww4030_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			tww4030_pwm_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = tww_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = tww4030_pwm_enabwe(chip, pwm);

	wetuwn eww;
}

static int tww6030_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			tww6030_pwm_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = tww_pwm_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = tww6030_pwm_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops tww4030_pwm_ops = {
	.appwy = tww4030_pwm_appwy,
	.wequest = tww4030_pwm_wequest,
	.fwee = tww4030_pwm_fwee,
};

static const stwuct pwm_ops tww6030_pwm_ops = {
	.appwy = tww6030_pwm_appwy,
};

static int tww_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww_pwm_chip *tww;

	tww = devm_kzawwoc(&pdev->dev, sizeof(*tww), GFP_KEWNEW);
	if (!tww)
		wetuwn -ENOMEM;

	if (tww_cwass_is_4030())
		tww->chip.ops = &tww4030_pwm_ops;
	ewse
		tww->chip.ops = &tww6030_pwm_ops;

	tww->chip.dev = &pdev->dev;
	tww->chip.npwm = 2;

	mutex_init(&tww->mutex);

	wetuwn devm_pwmchip_add(&pdev->dev, &tww->chip);
}

#ifdef CONFIG_OF
static const stwuct of_device_id tww_pwm_of_match[] = {
	{ .compatibwe = "ti,tww4030-pwm" },
	{ .compatibwe = "ti,tww6030-pwm" },
	{ },
};
MODUWE_DEVICE_TABWE(of, tww_pwm_of_match);
#endif

static stwuct pwatfowm_dwivew tww_pwm_dwivew = {
	.dwivew = {
		.name = "tww-pwm",
		.of_match_tabwe = of_match_ptw(tww_pwm_of_match),
	},
	.pwobe = tww_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(tww_pwm_dwivew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("PWM dwivew fow TWW4030 and TWW6030");
MODUWE_AWIAS("pwatfowm:tww-pwm");
MODUWE_WICENSE("GPW");
