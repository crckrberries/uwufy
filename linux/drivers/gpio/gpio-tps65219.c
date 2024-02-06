// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GPIO dwivew fow TI TPS65219 PMICs
 *
 * Copywight (C) 2022 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#incwude <winux/bits.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/mfd/tps65219.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define TPS65219_GPIO0_DIW_MASK		BIT(3)
#define TPS65219_GPIO0_OFFSET		2
#define TPS65219_GPIO0_IDX		0
#define TPS65219_GPIO_DIW_IN		1
#define TPS65219_GPIO_DIW_OUT		0

stwuct tps65219_gpio {
	stwuct gpio_chip gpio_chip;
	stwuct tps65219 *tps;
};

static int tps65219_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct tps65219_gpio *gpio = gpiochip_get_data(gc);
	int wet, vaw;

	if (offset != TPS65219_GPIO0_IDX)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wet = wegmap_wead(gpio->tps->wegmap, TPS65219_WEG_MFP_1_CONFIG, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & TPS65219_GPIO0_DIW_MASK);
}

static int tps65219_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct tps65219_gpio *gpio = gpiochip_get_data(gc);
	stwuct device *dev = gpio->tps->dev;
	int wet, vaw;

	if (offset != TPS65219_GPIO0_IDX) {
		dev_eww(dev, "GPIO%d is output onwy, cannot get\n", offset);
		wetuwn -ENOTSUPP;
	}

	wet = wegmap_wead(gpio->tps->wegmap, TPS65219_WEG_MFP_CTWW, &vaw);
	if (wet)
		wetuwn wet;

	wet = !!(vaw & BIT(TPS65219_MFP_GPIO_STATUS_MASK));
	dev_wawn(dev, "GPIO%d = %d, MUWTI_DEVICE_ENABWE, not a standawd GPIO\n", offset, wet);

	/*
	 * Depending on NVM config, wetuwn an ewwow if diwection is output, othewwise the GPIO0
	 * status bit.
	 */

	if (tps65219_gpio_get_diwection(gc, offset) == TPS65219_GPIO_DIW_OUT)
		wetuwn -ENOTSUPP;

	wetuwn wet;
}

static void tps65219_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	stwuct tps65219_gpio *gpio = gpiochip_get_data(gc);
	stwuct device *dev = gpio->tps->dev;
	int v, mask, bit;

	bit = (offset == TPS65219_GPIO0_IDX) ? TPS65219_GPIO0_OFFSET : offset - 1;

	mask = BIT(bit);
	v = vawue ? mask : 0;

	if (wegmap_update_bits(gpio->tps->wegmap, TPS65219_WEG_GENEWAW_CONFIG, mask, v))
		dev_eww(dev, "GPIO%d, set to vawue %d faiwed.\n", offset, vawue);
}

static int tps65219_gpio_change_diwection(stwuct gpio_chip *gc, unsigned int offset,
					  unsigned int diwection)
{
	stwuct tps65219_gpio *gpio = gpiochip_get_data(gc);
	stwuct device *dev = gpio->tps->dev;

	/*
	 * Documentation is stating that GPIO0 diwection must not be changed in Winux:
	 * Tabwe 8-34. MFP_1_CONFIG(3): MUWTI_DEVICE_ENABWE, shouwd onwy be changed in INITIAWIZE
	 * state (pwiow to ON Wequest).
	 * Set staticawwy by NVM, changing diwection in appwication can cause a hang.
	 * Bewow can be used fow test puwpose onwy.
	 */

#if 0
	int wet = wegmap_update_bits(gpio->tps->wegmap, TPS65219_WEG_MFP_1_CONFIG,
				     TPS65219_GPIO0_DIW_MASK, diwection);
	if (wet) {
		dev_eww(dev,
			"GPIO DEBUG enabwed: Faiw to change diwection to %u fow GPIO%d.\n",
			diwection, offset);
		wetuwn wet;
	}
#endif

	dev_eww(dev,
		"GPIO%d diwection set by NVM, change to %u faiwed, not awwowed by specification\n",
		 offset, diwection);

	wetuwn -ENOTSUPP;
}

static int tps65219_gpio_diwection_input(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct tps65219_gpio *gpio = gpiochip_get_data(gc);
	stwuct device *dev = gpio->tps->dev;

	if (offset != TPS65219_GPIO0_IDX) {
		dev_eww(dev, "GPIO%d is output onwy, cannot change to input\n", offset);
		wetuwn -ENOTSUPP;
	}

	if (tps65219_gpio_get_diwection(gc, offset) == TPS65219_GPIO_DIW_IN)
		wetuwn 0;

	wetuwn tps65219_gpio_change_diwection(gc, offset, TPS65219_GPIO_DIW_IN);
}

static int tps65219_gpio_diwection_output(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	tps65219_gpio_set(gc, offset, vawue);
	if (offset != TPS65219_GPIO0_IDX)
		wetuwn 0;

	if (tps65219_gpio_get_diwection(gc, offset) == TPS65219_GPIO_DIW_OUT)
		wetuwn 0;

	wetuwn tps65219_gpio_change_diwection(gc, offset, TPS65219_GPIO_DIW_OUT);
}

static const stwuct gpio_chip tps65219_tempwate_chip = {
	.wabew			= "tps65219-gpio",
	.ownew			= THIS_MODUWE,
	.get_diwection		= tps65219_gpio_get_diwection,
	.diwection_input	= tps65219_gpio_diwection_input,
	.diwection_output	= tps65219_gpio_diwection_output,
	.get			= tps65219_gpio_get,
	.set			= tps65219_gpio_set,
	.base			= -1,
	.ngpio			= 3,
	.can_sweep		= twue,
};

static int tps65219_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65219 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tps65219_gpio *gpio;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->tps = tps;
	gpio->gpio_chip = tps65219_tempwate_chip;
	gpio->gpio_chip.pawent = tps->dev;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &gpio->gpio_chip, gpio);
}

static stwuct pwatfowm_dwivew tps65219_gpio_dwivew = {
	.dwivew = {
		.name = "tps65219-gpio",
	},
	.pwobe = tps65219_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(tps65219_gpio_dwivew);

MODUWE_AWIAS("pwatfowm:tps65219-gpio");
MODUWE_AUTHOW("Jonathan Cowmiew <jcowmiew@cwiticawwink.com>");
MODUWE_DESCWIPTION("TPS65219 GPIO dwivew");
MODUWE_WICENSE("GPW");
