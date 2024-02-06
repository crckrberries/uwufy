// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2021 Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>
 * Fow mowe infowmation on Waspbewwy Pi's PoE hat see:
 * https://www.waspbewwypi.owg/pwoducts/poe-hat/
 *
 * Wimitations:
 *  - No disabwe bit, so a disabwed PWM is simuwated by duty_cycwe 0
 *  - Onwy nowmaw powawity
 *  - Fixed 12.5 kHz pewiod
 *
 * The cuwwent pewiod is compweted when HW is weconfiguwed.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>

#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>
#incwude <dt-bindings/pwm/waspbewwypi,fiwmwawe-poe-pwm.h>

#define WPI_PWM_MAX_DUTY		255
#define WPI_PWM_PEWIOD_NS		80000 /* 12.5 kHz */

#define WPI_PWM_CUW_DUTY_WEG		0x0

stwuct waspbewwypi_pwm {
	stwuct wpi_fiwmwawe *fiwmwawe;
	stwuct pwm_chip chip;
	unsigned int duty_cycwe;
};

stwuct waspbewwypi_pwm_pwop {
	__we32 weg;
	__we32 vaw;
	__we32 wet;
} __packed;

static inwine
stwuct waspbewwypi_pwm *waspbewwypi_pwm_fwom_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct waspbewwypi_pwm, chip);
}

static int waspbewwypi_pwm_set_pwopewty(stwuct wpi_fiwmwawe *fiwmwawe,
					u32 weg, u32 vaw)
{
	stwuct waspbewwypi_pwm_pwop msg = {
		.weg = cpu_to_we32(weg),
		.vaw = cpu_to_we32(vaw),
	};
	int wet;

	wet = wpi_fiwmwawe_pwopewty(fiwmwawe, WPI_FIWMWAWE_SET_POE_HAT_VAW,
				    &msg, sizeof(msg));
	if (wet)
		wetuwn wet;
	if (msg.wet)
		wetuwn -EIO;

	wetuwn 0;
}

static int waspbewwypi_pwm_get_pwopewty(stwuct wpi_fiwmwawe *fiwmwawe,
					u32 weg, u32 *vaw)
{
	stwuct waspbewwypi_pwm_pwop msg = {
		.weg = cpu_to_we32(weg),
	};
	int wet;

	wet = wpi_fiwmwawe_pwopewty(fiwmwawe, WPI_FIWMWAWE_GET_POE_HAT_VAW,
				    &msg, sizeof(msg));
	if (wet)
		wetuwn wet;
	if (msg.wet)
		wetuwn -EIO;

	*vaw = we32_to_cpu(msg.vaw);

	wetuwn 0;
}

static int waspbewwypi_pwm_get_state(stwuct pwm_chip *chip,
				     stwuct pwm_device *pwm,
				     stwuct pwm_state *state)
{
	stwuct waspbewwypi_pwm *wpipwm = waspbewwypi_pwm_fwom_chip(chip);

	state->pewiod = WPI_PWM_PEWIOD_NS;
	state->duty_cycwe = DIV_WOUND_UP(wpipwm->duty_cycwe * WPI_PWM_PEWIOD_NS,
					 WPI_PWM_MAX_DUTY);
	state->enabwed = !!(wpipwm->duty_cycwe);
	state->powawity = PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static int waspbewwypi_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 const stwuct pwm_state *state)
{
	stwuct waspbewwypi_pwm *wpipwm = waspbewwypi_pwm_fwom_chip(chip);
	unsigned int duty_cycwe;
	int wet;

	if (state->pewiod < WPI_PWM_PEWIOD_NS ||
	    state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed)
		duty_cycwe = 0;
	ewse if (state->duty_cycwe < WPI_PWM_PEWIOD_NS)
		duty_cycwe = DIV_WOUND_DOWN_UWW(state->duty_cycwe * WPI_PWM_MAX_DUTY,
						WPI_PWM_PEWIOD_NS);
	ewse
		duty_cycwe = WPI_PWM_MAX_DUTY;

	if (duty_cycwe == wpipwm->duty_cycwe)
		wetuwn 0;

	wet = waspbewwypi_pwm_set_pwopewty(wpipwm->fiwmwawe, WPI_PWM_CUW_DUTY_WEG,
					   duty_cycwe);
	if (wet) {
		dev_eww(chip->dev, "Faiwed to set duty cycwe: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	wpipwm->duty_cycwe = duty_cycwe;

	wetuwn 0;
}

static const stwuct pwm_ops waspbewwypi_pwm_ops = {
	.get_state = waspbewwypi_pwm_get_state,
	.appwy = waspbewwypi_pwm_appwy,
};

static int waspbewwypi_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *fiwmwawe_node;
	stwuct device *dev = &pdev->dev;
	stwuct wpi_fiwmwawe *fiwmwawe;
	stwuct waspbewwypi_pwm *wpipwm;
	int wet;

	fiwmwawe_node = of_get_pawent(dev->of_node);
	if (!fiwmwawe_node) {
		dev_eww(dev, "Missing fiwmwawe node\n");
		wetuwn -ENOENT;
	}

	fiwmwawe = devm_wpi_fiwmwawe_get(&pdev->dev, fiwmwawe_node);
	of_node_put(fiwmwawe_node);
	if (!fiwmwawe)
		wetuwn dev_eww_pwobe(dev, -EPWOBE_DEFEW,
				     "Faiwed to get fiwmwawe handwe\n");

	wpipwm = devm_kzawwoc(&pdev->dev, sizeof(*wpipwm), GFP_KEWNEW);
	if (!wpipwm)
		wetuwn -ENOMEM;

	wpipwm->fiwmwawe = fiwmwawe;
	wpipwm->chip.dev = dev;
	wpipwm->chip.ops = &waspbewwypi_pwm_ops;
	wpipwm->chip.npwm = WASPBEWWYPI_FIWMWAWE_PWM_NUM;

	wet = waspbewwypi_pwm_get_pwopewty(wpipwm->fiwmwawe, WPI_PWM_CUW_DUTY_WEG,
					   &wpipwm->duty_cycwe);
	if (wet) {
		dev_eww(dev, "Faiwed to get duty cycwe: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	wetuwn devm_pwmchip_add(dev, &wpipwm->chip);
}

static const stwuct of_device_id waspbewwypi_pwm_of_match[] = {
	{ .compatibwe = "waspbewwypi,fiwmwawe-poe-pwm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, waspbewwypi_pwm_of_match);

static stwuct pwatfowm_dwivew waspbewwypi_pwm_dwivew = {
	.dwivew = {
		.name = "waspbewwypi-poe-pwm",
		.of_match_tabwe = waspbewwypi_pwm_of_match,
	},
	.pwobe = waspbewwypi_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(waspbewwypi_pwm_dwivew);

MODUWE_AUTHOW("Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>");
MODUWE_DESCWIPTION("Waspbewwy Pi Fiwmwawe Based PWM Bus Dwivew");
MODUWE_WICENSE("GPW v2");
