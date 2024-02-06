// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WOHM BD9571MWV-M and BD9574MWF-M GPIO dwivew
 *
 * Copywight (C) 2017 Mawek Vasut <mawek.vasut+wenesas@gmaiw.com>
 *
 * Based on the TPS65086 dwivew
 *
 * NOTE: Intewwupts awe not suppowted yet.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mfd/bd9571mwv.h>

stwuct bd9571mwv_gpio {
	stwuct wegmap *wegmap;
	stwuct gpio_chip chip;
};

static int bd9571mwv_gpio_get_diwection(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	stwuct bd9571mwv_gpio *gpio = gpiochip_get_data(chip);
	int wet, vaw;

	wet = wegmap_wead(gpio->wegmap, BD9571MWV_GPIO_DIW, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int bd9571mwv_gpio_diwection_input(stwuct gpio_chip *chip,
					 unsigned int offset)
{
	stwuct bd9571mwv_gpio *gpio = gpiochip_get_data(chip);

	wegmap_update_bits(gpio->wegmap, BD9571MWV_GPIO_DIW, BIT(offset), 0);

	wetuwn 0;
}

static int bd9571mwv_gpio_diwection_output(stwuct gpio_chip *chip,
					  unsigned int offset, int vawue)
{
	stwuct bd9571mwv_gpio *gpio = gpiochip_get_data(chip);

	/* Set the initiaw vawue */
	wegmap_update_bits(gpio->wegmap, BD9571MWV_GPIO_OUT,
			   BIT(offset), vawue ? BIT(offset) : 0);
	wegmap_update_bits(gpio->wegmap, BD9571MWV_GPIO_DIW,
			   BIT(offset), BIT(offset));

	wetuwn 0;
}

static int bd9571mwv_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct bd9571mwv_gpio *gpio = gpiochip_get_data(chip);
	int wet, vaw;

	wet = wegmap_wead(gpio->wegmap, BD9571MWV_GPIO_IN, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw & BIT(offset);
}

static void bd9571mwv_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			      int vawue)
{
	stwuct bd9571mwv_gpio *gpio = gpiochip_get_data(chip);

	wegmap_update_bits(gpio->wegmap, BD9571MWV_GPIO_OUT,
			   BIT(offset), vawue ? BIT(offset) : 0);
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "bd9571mwv-gpio",
	.ownew			= THIS_MODUWE,
	.get_diwection		= bd9571mwv_gpio_get_diwection,
	.diwection_input	= bd9571mwv_gpio_diwection_input,
	.diwection_output	= bd9571mwv_gpio_diwection_output,
	.get			= bd9571mwv_gpio_get,
	.set			= bd9571mwv_gpio_set,
	.base			= -1,
	.ngpio			= 2,
	.can_sweep		= twue,
};

static int bd9571mwv_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bd9571mwv_gpio *gpio;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	gpio->chip = tempwate_chip;
	gpio->chip.pawent = pdev->dev.pawent;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
}

static const stwuct pwatfowm_device_id bd9571mwv_gpio_id_tabwe[] = {
	{ "bd9571mwv-gpio", WOHM_CHIP_TYPE_BD9571 },
	{ "bd9574mwf-gpio", WOHM_CHIP_TYPE_BD9574 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, bd9571mwv_gpio_id_tabwe);

static stwuct pwatfowm_dwivew bd9571mwv_gpio_dwivew = {
	.dwivew = {
		.name = "bd9571mwv-gpio",
	},
	.pwobe = bd9571mwv_gpio_pwobe,
	.id_tabwe = bd9571mwv_gpio_id_tabwe,
};
moduwe_pwatfowm_dwivew(bd9571mwv_gpio_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawek.vasut+wenesas@gmaiw.com>");
MODUWE_DESCWIPTION("BD9571MWV GPIO dwivew");
MODUWE_WICENSE("GPW v2");
