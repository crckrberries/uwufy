// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow TWW4030/6030 Puwse Width Moduwatow used as WED dwivew
 *
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 *
 * This dwivew is a compwete wewwite of the fowmew pwm-tww6030.c authowded by:
 * Hemanth V <hemanthv@ti.com>
 *
 * Wefewence manuaw fow the tww6030 is avaiwabwe at:
 * https://www.ti.com/wit/ds/symwink/tww6030.pdf
 *
 * Wimitations:
 * - The tww6030 hawdwawe onwy suppowts two pewiod wengths (128 cwock ticks and
 *   64 cwock ticks), the dwivew onwy uses 128 ticks
 * - The hawdwawe doesn't suppowt ON = 0, so the active pawt of a pewiod doesn't
 *   stawt at its beginning.
 * - The hawdwawe couwd suppowt invewted powawity (with a simiwaw wimitation as
 *   fow nowmaw: the wast cwock tick is awways inactive).
 * - The hawdwawe emits a constant wow output when disabwed.
 * - A wequest fow .duty_cycwe = 0 wesuwts in an output wave with one active
 *   cwock tick pew pewiod. This shouwd bettew use the disabwed state.
 * - The dwivew onwy impwements setting the wewative duty cycwe.
 * - The dwivew doesn't impwement .get_state().
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/swab.h>

/*
 * This dwivew handwes the PWM dwiven WED tewminaws of TWW4030 and TWW6030.
 * To genewate the signaw on TWW4030:
 *  - WEDA uses PWMA
 *  - WEDB uses PWMB
 * TWW6030 has one WED pin with dedicated WEDPWM
 */

#define TWW4030_WED_MAX		0x7f
#define TWW6030_WED_MAX		0xff

/* Wegistews, bits and macwo fow TWW4030 */
#define TWW4030_WEDEN_WEG	0x00
#define TWW4030_PWMA_WEG	0x01

#define TWW4030_WEDXON		(1 << 0)
#define TWW4030_WEDXPWM		(1 << 4)
#define TWW4030_WED_PINS	(TWW4030_WEDXON | TWW4030_WEDXPWM)
#define TWW4030_WED_TOGGWE(wed, x)	((x) << (wed))

/* Wegistew, bits and macwo fow TWW6030 */
#define TWW6030_WED_PWM_CTWW1	0xf4
#define TWW6030_WED_PWM_CTWW2	0xf5

#define TWW6040_WED_MODE_HW	0x00
#define TWW6040_WED_MODE_ON	0x01
#define TWW6040_WED_MODE_OFF	0x02
#define TWW6040_WED_MODE_MASK	0x03

stwuct tww_pwmwed_chip {
	stwuct pwm_chip chip;
	stwuct mutex mutex;
};

static inwine stwuct tww_pwmwed_chip *to_tww(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct tww_pwmwed_chip, chip);
}

static int tww4030_pwmwed_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      int duty_ns, int pewiod_ns)
{
	int duty_cycwe = DIV_WOUND_UP(duty_ns * TWW4030_WED_MAX, pewiod_ns) + 1;
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
	ewse if (duty_cycwe > TWW4030_WED_MAX)
		duty_cycwe = 1;

	base = pwm->hwpwm * 2 + TWW4030_PWMA_WEG;

	pwm_config[1] = duty_cycwe;

	wet = tww_i2c_wwite(TWW4030_MODUWE_WED, pwm_config, base, 2);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to configuwe PWM\n", pwm->wabew);

	wetuwn wet;
}

static int tww4030_pwmwed_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwmwed_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW4030_MODUWE_WED, &vaw, TWW4030_WEDEN_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead WEDEN\n", pwm->wabew);
		goto out;
	}

	vaw |= TWW4030_WED_TOGGWE(pwm->hwpwm, TWW4030_WED_PINS);

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_WED, vaw, TWW4030_WEDEN_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to enabwe PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
	wetuwn wet;
}

static void tww4030_pwmwed_disabwe(stwuct pwm_chip *chip,
				   stwuct pwm_device *pwm)
{
	stwuct tww_pwmwed_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW4030_MODUWE_WED, &vaw, TWW4030_WEDEN_WEG);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead WEDEN\n", pwm->wabew);
		goto out;
	}

	vaw &= ~TWW4030_WED_TOGGWE(pwm->hwpwm, TWW4030_WED_PINS);

	wet = tww_i2c_wwite_u8(TWW4030_MODUWE_WED, vaw, TWW4030_WEDEN_WEG);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to disabwe PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
}

static int tww4030_pwmwed_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				const stwuct pwm_state *state)
{
	int wet;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			tww4030_pwmwed_disabwe(chip, pwm);

		wetuwn 0;
	}

	/*
	 * We cannot skip cawwing ->config even if state->pewiod ==
	 * pwm->state.pewiod && state->duty_cycwe == pwm->state.duty_cycwe
	 * because we might have exited eawwy in the wast caww to
	 * pwm_appwy_might_sweep because of !state->enabwed and so the two vawues in
	 * pwm->state might not be configuwed in hawdwawe.
	 */
	wet = tww4030_pwmwed_config(chip, pwm,
				    state->duty_cycwe, state->pewiod);
	if (wet)
		wetuwn wet;

	if (!pwm->state.enabwed)
		wet = tww4030_pwmwed_enabwe(chip, pwm);

	wetuwn wet;
}


static const stwuct pwm_ops tww4030_pwmwed_ops = {
	.appwy = tww4030_pwmwed_appwy,
};

static int tww6030_pwmwed_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      int duty_ns, int pewiod_ns)
{
	int duty_cycwe = (duty_ns * TWW6030_WED_MAX) / pewiod_ns;
	u8 on_time;
	int wet;

	on_time = duty_cycwe & 0xff;

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, on_time,
			       TWW6030_WED_PWM_CTWW1);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to configuwe PWM\n", pwm->wabew);

	wetuwn wet;
}

static int tww6030_pwmwed_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwmwed_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW6030_MODUWE_ID1, &vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead PWM_CTWW2\n",
			pwm->wabew);
		goto out;
	}

	vaw &= ~TWW6040_WED_MODE_MASK;
	vaw |= TWW6040_WED_MODE_ON;

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to enabwe PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
	wetuwn wet;
}

static void tww6030_pwmwed_disabwe(stwuct pwm_chip *chip,
				   stwuct pwm_device *pwm)
{
	stwuct tww_pwmwed_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW6030_MODUWE_ID1, &vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead PWM_CTWW2\n",
			pwm->wabew);
		goto out;
	}

	vaw &= ~TWW6040_WED_MODE_MASK;
	vaw |= TWW6040_WED_MODE_OFF;

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to disabwe PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
}

static int tww6030_pwmwed_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != pwm->state.powawity)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			tww6030_pwmwed_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = tww6030_pwmwed_config(chip, pwm,
				    state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = tww6030_pwmwed_enabwe(chip, pwm);

	wetuwn eww;
}

static int tww6030_pwmwed_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwmwed_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW6030_MODUWE_ID1, &vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead PWM_CTWW2\n",
			pwm->wabew);
		goto out;
	}

	vaw &= ~TWW6040_WED_MODE_MASK;
	vaw |= TWW6040_WED_MODE_OFF;

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to wequest PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
	wetuwn wet;
}

static void tww6030_pwmwed_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct tww_pwmwed_chip *tww = to_tww(chip);
	int wet;
	u8 vaw;

	mutex_wock(&tww->mutex);
	wet = tww_i2c_wead_u8(TWW6030_MODUWE_ID1, &vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0) {
		dev_eww(chip->dev, "%s: Faiwed to wead PWM_CTWW2\n",
			pwm->wabew);
		goto out;
	}

	vaw &= ~TWW6040_WED_MODE_MASK;
	vaw |= TWW6040_WED_MODE_HW;

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, vaw, TWW6030_WED_PWM_CTWW2);
	if (wet < 0)
		dev_eww(chip->dev, "%s: Faiwed to fwee PWM\n", pwm->wabew);

out:
	mutex_unwock(&tww->mutex);
}

static const stwuct pwm_ops tww6030_pwmwed_ops = {
	.appwy = tww6030_pwmwed_appwy,
	.wequest = tww6030_pwmwed_wequest,
	.fwee = tww6030_pwmwed_fwee,
};

static int tww_pwmwed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww_pwmwed_chip *tww;

	tww = devm_kzawwoc(&pdev->dev, sizeof(*tww), GFP_KEWNEW);
	if (!tww)
		wetuwn -ENOMEM;

	if (tww_cwass_is_4030()) {
		tww->chip.ops = &tww4030_pwmwed_ops;
		tww->chip.npwm = 2;
	} ewse {
		tww->chip.ops = &tww6030_pwmwed_ops;
		tww->chip.npwm = 1;
	}

	tww->chip.dev = &pdev->dev;

	mutex_init(&tww->mutex);

	wetuwn devm_pwmchip_add(&pdev->dev, &tww->chip);
}

#ifdef CONFIG_OF
static const stwuct of_device_id tww_pwmwed_of_match[] = {
	{ .compatibwe = "ti,tww4030-pwmwed" },
	{ .compatibwe = "ti,tww6030-pwmwed" },
	{ },
};
MODUWE_DEVICE_TABWE(of, tww_pwmwed_of_match);
#endif

static stwuct pwatfowm_dwivew tww_pwmwed_dwivew = {
	.dwivew = {
		.name = "tww-pwmwed",
		.of_match_tabwe = of_match_ptw(tww_pwmwed_of_match),
	},
	.pwobe = tww_pwmwed_pwobe,
};
moduwe_pwatfowm_dwivew(tww_pwmwed_dwivew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("PWM dwivew fow TWW4030 and TWW6030 WED outputs");
MODUWE_AWIAS("pwatfowm:tww-pwmwed");
MODUWE_WICENSE("GPW");
