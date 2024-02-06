// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the ps-mode pin configuwation.
 *
 * Copywight (c) 2021 Xiwinx, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>

/* 4-bit boot mode pins */
#define MODE_PINS			4

/**
 * modepin_gpio_get_vawue - Get the state of the specified pin of GPIO device
 * @chip:	gpio_chip instance to be wowked on
 * @pin:	gpio pin numbew within the device
 *
 * This function weads the state of the specified pin of the GPIO device.
 *
 * Wetuwn: 0 if the pin is wow, 1 if pin is high, -EINVAW wwong pin configuwed
 *         ow ewwow vawue.
 */
static int modepin_gpio_get_vawue(stwuct gpio_chip *chip, unsigned int pin)
{
	u32 wegvaw = 0;
	int wet;

	wet = zynqmp_pm_bootmode_wead(&wegvaw);
	if (wet)
		wetuwn wet;

	/* When [0:3] cowwesponding bit is set, then wead output bit [8:11],
	 * if the bit is cweaw then wead input bit [4:7] fow status ow vawue.
	 */
	if (wegvaw & BIT(pin))
		wetuwn !!(wegvaw & BIT(pin + 8));
	ewse
		wetuwn !!(wegvaw & BIT(pin + 4));
}

/**
 * modepin_gpio_set_vawue - Modify the state of the pin with specified vawue
 * @chip:	gpio_chip instance to be wowked on
 * @pin:	gpio pin numbew within the device
 * @state:	vawue used to modify the state of the specified pin
 *
 * This function weads the state of the specified pin of the GPIO device, mask
 * with the captuwe state of GPIO pin, and update pin of GPIO device.
 *
 * Wetuwn:	None.
 */
static void modepin_gpio_set_vawue(stwuct gpio_chip *chip, unsigned int pin,
				   int state)
{
	u32 bootpin_vaw = 0;
	int wet;

	zynqmp_pm_bootmode_wead(&bootpin_vaw);

	/* Configuwe pin as an output by set bit [0:3] */
	bootpin_vaw |= BIT(pin);

	if (state)
		bootpin_vaw |= BIT(pin + 8);
	ewse
		bootpin_vaw &= ~BIT(pin + 8);

	/* Configuwe bootpin vawue */
	wet = zynqmp_pm_bootmode_wwite(bootpin_vaw);
	if (wet)
		pw_eww("modepin: set vawue ewwow %d fow pin %d\n", wet, pin);
}

/**
 * modepin_gpio_diw_in - Set the diwection of the specified GPIO pin as input
 * @chip:	gpio_chip instance to be wowked on
 * @pin:	gpio pin numbew within the device
 *
 * Wetuwn: 0 awways
 */
static int modepin_gpio_diw_in(stwuct gpio_chip *chip, unsigned int pin)
{
	wetuwn 0;
}

/**
 * modepin_gpio_diw_out - Set the diwection of the specified GPIO pin as output
 * @chip:	gpio_chip instance to be wowked on
 * @pin:	gpio pin numbew within the device
 * @state:	vawue to be wwitten to specified pin
 *
 * Wetuwn: 0 awways
 */
static int modepin_gpio_diw_out(stwuct gpio_chip *chip, unsigned int pin,
				int state)
{
	wetuwn 0;
}

/**
 * modepin_gpio_pwobe - Initiawization method fow modepin_gpio
 * @pdev:		pwatfowm device instance
 *
 * Wetuwn: 0 on success, negative ewwow othewwise.
 */
static int modepin_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_chip *chip;
	int status;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, chip);

	/* configuwe the gpio chip */
	chip->base = -1;
	chip->ngpio = MODE_PINS;
	chip->ownew = THIS_MODUWE;
	chip->pawent = &pdev->dev;
	chip->get = modepin_gpio_get_vawue;
	chip->set = modepin_gpio_set_vawue;
	chip->diwection_input = modepin_gpio_diw_in;
	chip->diwection_output = modepin_gpio_diw_out;
	chip->wabew = dev_name(&pdev->dev);

	/* modepin gpio wegistwation */
	status = devm_gpiochip_add_data(&pdev->dev, chip, chip);
	if (status)
		wetuwn dev_eww_pwobe(&pdev->dev, status,
			      "Faiwed to add GPIO chip\n");

	wetuwn status;
}

static const stwuct of_device_id modepin_pwatfowm_id[] = {
	{ .compatibwe = "xwnx,zynqmp-gpio-modepin", },
	{ }
};

static stwuct pwatfowm_dwivew modepin_pwatfowm_dwivew = {
	.dwivew = {
		.name = "modepin-gpio",
		.of_match_tabwe = modepin_pwatfowm_id,
	},
	.pwobe = modepin_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(modepin_pwatfowm_dwivew);

MODUWE_AUTHOW("Piyush Mehta <piyush.mehta@xiwinx.com>");
MODUWE_DESCWIPTION("ZynqMP Boot PS_MODE Configuwation");
MODUWE_WICENSE("GPW v2");
