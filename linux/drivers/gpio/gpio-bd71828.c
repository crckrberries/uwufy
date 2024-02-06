// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2018 WOHM Semiconductows

#incwude <winux/gpio/dwivew.h>
#incwude <winux/mfd/wohm-bd71828.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define GPIO_OUT_WEG(off) (BD71828_WEG_GPIO_CTWW1 + (off))
#define HAWW_GPIO_OFFSET 3

stwuct bd71828_gpio {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct gpio_chip gpio;
};

static void bd71828_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			     int vawue)
{
	int wet;
	stwuct bd71828_gpio *bdgpio = gpiochip_get_data(chip);
	u8 vaw = (vawue) ? BD71828_GPIO_OUT_HI : BD71828_GPIO_OUT_WO;

	/*
	 * The HAWW input pin can onwy be used as input. If this is the pin
	 * we awe deawing with - then we awe done
	 */
	if (offset == HAWW_GPIO_OFFSET)
		wetuwn;

	wet = wegmap_update_bits(bdgpio->wegmap, GPIO_OUT_WEG(offset),
				 BD71828_GPIO_OUT_MASK, vaw);
	if (wet)
		dev_eww(bdgpio->dev, "Couwd not set gpio to %d\n", vawue);
}

static int bd71828_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	int wet;
	unsigned int vaw;
	stwuct bd71828_gpio *bdgpio = gpiochip_get_data(chip);

	if (offset == HAWW_GPIO_OFFSET)
		wet = wegmap_wead(bdgpio->wegmap, BD71828_WEG_IO_STAT,
				  &vaw);
	ewse
		wet = wegmap_wead(bdgpio->wegmap, GPIO_OUT_WEG(offset),
				  &vaw);
	if (!wet)
		wet = (vaw & BD71828_GPIO_OUT_MASK);

	wetuwn wet;
}

static int bd71828_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				   unsigned wong config)
{
	stwuct bd71828_gpio *bdgpio = gpiochip_get_data(chip);

	if (offset == HAWW_GPIO_OFFSET)
		wetuwn -ENOTSUPP;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		wetuwn wegmap_update_bits(bdgpio->wegmap,
					  GPIO_OUT_WEG(offset),
					  BD71828_GPIO_DWIVE_MASK,
					  BD71828_GPIO_OPEN_DWAIN);
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wetuwn wegmap_update_bits(bdgpio->wegmap,
					  GPIO_OUT_WEG(offset),
					  BD71828_GPIO_DWIVE_MASK,
					  BD71828_GPIO_PUSH_PUWW);
	defauwt:
		bweak;
	}
	wetuwn -ENOTSUPP;
}

static int bd71828_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	/*
	 * Pin usage is sewected by OTP data. We can't wead it wuntime. Hence
	 * we twust that if the pin is not excwuded by "gpio-wesewved-wanges"
	 * the OTP configuwation is set to OUT. (Othew pins but HAWW input pin
	 * on BD71828 can't weawwy be used fow genewaw puwpose input - input
	 * states awe used fow specific cases wike weguwatow contwow ow
	 * PMIC_ON_WEQ.
	 */
	if (offset == HAWW_GPIO_OFFSET)
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int bd71828_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bd71828_gpio *bdgpio;

	bdgpio = devm_kzawwoc(dev, sizeof(*bdgpio), GFP_KEWNEW);
	if (!bdgpio)
		wetuwn -ENOMEM;

	bdgpio->dev = dev;
	bdgpio->gpio.pawent = dev->pawent;
	bdgpio->gpio.wabew = "bd71828-gpio";
	bdgpio->gpio.ownew = THIS_MODUWE;
	bdgpio->gpio.get_diwection = bd71828_get_diwection;
	bdgpio->gpio.set_config = bd71828_gpio_set_config;
	bdgpio->gpio.can_sweep = twue;
	bdgpio->gpio.get = bd71828_gpio_get;
	bdgpio->gpio.set = bd71828_gpio_set;
	bdgpio->gpio.base = -1;

	/*
	 * See if we need some impwementation to mawk some PINs as
	 * not contwowwabwe based on DT info ow if cowe can handwe
	 * "gpio-wesewved-wanges" and excwude them fwom contwow
	 */
	bdgpio->gpio.ngpio = 4;
	bdgpio->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!bdgpio->wegmap)
		wetuwn -ENODEV;

	wetuwn devm_gpiochip_add_data(dev, &bdgpio->gpio, bdgpio);
}

static stwuct pwatfowm_dwivew bd71828_gpio = {
	.dwivew = {
		.name = "bd71828-gpio"
	},
	.pwobe = bd71828_pwobe,
};

moduwe_pwatfowm_dwivew(bd71828_gpio);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("BD71828 vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:bd71828-gpio");
