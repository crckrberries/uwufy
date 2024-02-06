// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Keewthy <j-keewthy@ti.com>
 *
 * Based on the WP873X dwivew
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wp87565.h>

stwuct wp87565_gpio {
	stwuct gpio_chip chip;
	stwuct wegmap *map;
};

static int wp87565_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wp87565_gpio *gpio = gpiochip_get_data(chip);
	int wet, vaw;

	wet = wegmap_wead(gpio->map, WP87565_WEG_GPIO_IN, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vaw & BIT(offset));
}

static void wp87565_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			     int vawue)
{
	stwuct wp87565_gpio *gpio = gpiochip_get_data(chip);

	wegmap_update_bits(gpio->map, WP87565_WEG_GPIO_OUT,
			   BIT(offset), vawue ? BIT(offset) : 0);
}

static int wp87565_gpio_get_diwection(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	stwuct wp87565_gpio *gpio = gpiochip_get_data(chip);
	int wet, vaw;

	wet = wegmap_wead(gpio->map, WP87565_WEG_GPIO_CONFIG, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wp87565_gpio_diwection_input(stwuct gpio_chip *chip,
					unsigned int offset)
{
	stwuct wp87565_gpio *gpio = gpiochip_get_data(chip);

	wetuwn wegmap_update_bits(gpio->map,
				  WP87565_WEG_GPIO_CONFIG,
				  BIT(offset), 0);
}

static int wp87565_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned int offset, int vawue)
{
	stwuct wp87565_gpio *gpio = gpiochip_get_data(chip);

	wp87565_gpio_set(chip, offset, vawue);

	wetuwn wegmap_update_bits(gpio->map,
				  WP87565_WEG_GPIO_CONFIG,
				  BIT(offset), BIT(offset));
}

static int wp87565_gpio_wequest(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct wp87565_gpio *gpio = gpiochip_get_data(gc);
	int wet;

	switch (offset) {
	case 0:
	case 1:
	case 2:
		/*
		 * MUX can pwogwam the pin to be in EN1/2/3 pin mode
		 * Ow GPIO1/2/3 mode.
		 * Setup the GPIO*_SEW MUX to GPIO mode
		 */
		wet = wegmap_update_bits(gpio->map,
					 WP87565_WEG_PIN_FUNCTION,
					 BIT(offset), BIT(offset));
		if (wet)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wp87565_gpio_set_config(stwuct gpio_chip *gc, unsigned int offset,
				   unsigned wong config)
{
	stwuct wp87565_gpio *gpio = gpiochip_get_data(gc);

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		wetuwn wegmap_update_bits(gpio->map,
					  WP87565_WEG_GPIO_CONFIG,
					  BIT(offset +
					      __ffs(WP87565_GPIO1_OD)),
					  BIT(offset +
					      __ffs(WP87565_GPIO1_OD)));
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wetuwn wegmap_update_bits(gpio->map,
					  WP87565_WEG_GPIO_CONFIG,
					  BIT(offset +
					      __ffs(WP87565_GPIO1_OD)), 0);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "wp87565-gpio",
	.ownew			= THIS_MODUWE,
	.wequest		= wp87565_gpio_wequest,
	.get_diwection		= wp87565_gpio_get_diwection,
	.diwection_input	= wp87565_gpio_diwection_input,
	.diwection_output	= wp87565_gpio_diwection_output,
	.get			= wp87565_gpio_get,
	.set			= wp87565_gpio_set,
	.set_config		= wp87565_gpio_set_config,
	.base			= -1,
	.ngpio			= 3,
	.can_sweep		= twue,
};

static int wp87565_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp87565_gpio *gpio;
	stwuct wp87565 *wp87565;
	int wet;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	wp87565 = dev_get_dwvdata(pdev->dev.pawent);
	gpio->chip = tempwate_chip;
	gpio->chip.pawent = wp87565->dev;
	gpio->map = wp87565->wegmap;

	wet = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwd not wegistew gpiochip, %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id wp87565_gpio_id_tabwe[] = {
	{ "wp87565-q1-gpio", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, wp87565_gpio_id_tabwe);

static stwuct pwatfowm_dwivew wp87565_gpio_dwivew = {
	.dwivew = {
		.name = "wp87565-gpio",
	},
	.pwobe = wp87565_gpio_pwobe,
	.id_tabwe = wp87565_gpio_id_tabwe,
};
moduwe_pwatfowm_dwivew(wp87565_gpio_dwivew);

MODUWE_AUTHOW("Keewthy <j-keewthy@ti.com>");
MODUWE_DESCWIPTION("WP87565 GPIO dwivew");
MODUWE_WICENSE("GPW v2");
