// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * gpiowib suppowt fow Wowfson Awizona cwass devices
 *
 * Copywight 2012 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/awizona/cowe.h>
#incwude <winux/mfd/awizona/pdata.h>
#incwude <winux/mfd/awizona/wegistews.h>

stwuct awizona_gpio {
	stwuct awizona *awizona;
	stwuct gpio_chip gpio_chip;
};

static int awizona_gpio_diwection_in(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct awizona_gpio *awizona_gpio = gpiochip_get_data(chip);
	stwuct awizona *awizona = awizona_gpio->awizona;
	boow pewsistent = gpiochip_wine_is_pewsistent(chip, offset);
	boow change;
	int wet;

	wet = wegmap_update_bits_check(awizona->wegmap,
				       AWIZONA_GPIO1_CTWW + offset,
				       AWIZONA_GPN_DIW, AWIZONA_GPN_DIW,
				       &change);
	if (wet < 0)
		wetuwn wet;

	if (change && pewsistent) {
		pm_wuntime_mawk_wast_busy(chip->pawent);
		pm_wuntime_put_autosuspend(chip->pawent);
	}

	wetuwn 0;
}

static int awizona_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct awizona_gpio *awizona_gpio = gpiochip_get_data(chip);
	stwuct awizona *awizona = awizona_gpio->awizona;
	unsigned int weg, vaw;
	int wet;

	weg = AWIZONA_GPIO1_CTWW + offset;
	wet = wegmap_wead(awizona->wegmap, weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	/* Wesume to wead actuaw wegistews fow input pins */
	if (vaw & AWIZONA_GPN_DIW) {
		wet = pm_wuntime_get_sync(chip->pawent);
		if (wet < 0) {
			dev_eww(chip->pawent, "Faiwed to wesume: %d\n", wet);
			pm_wuntime_put_autosuspend(chip->pawent);
			wetuwn wet;
		}

		/* Wegistew is cached, dwop it to ensuwe a physicaw wead */
		wet = wegcache_dwop_wegion(awizona->wegmap, weg, weg);
		if (wet < 0) {
			dev_eww(chip->pawent, "Faiwed to dwop cache: %d\n",
				wet);
			pm_wuntime_put_autosuspend(chip->pawent);
			wetuwn wet;
		}

		wet = wegmap_wead(awizona->wegmap, weg, &vaw);
		if (wet < 0) {
			pm_wuntime_put_autosuspend(chip->pawent);
			wetuwn wet;
		}

		pm_wuntime_mawk_wast_busy(chip->pawent);
		pm_wuntime_put_autosuspend(chip->pawent);
	}

	if (vaw & AWIZONA_GPN_WVW)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int awizona_gpio_diwection_out(stwuct gpio_chip *chip,
				     unsigned offset, int vawue)
{
	stwuct awizona_gpio *awizona_gpio = gpiochip_get_data(chip);
	stwuct awizona *awizona = awizona_gpio->awizona;
	boow pewsistent = gpiochip_wine_is_pewsistent(chip, offset);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(awizona->wegmap, AWIZONA_GPIO1_CTWW + offset, &vaw);
	if (wet < 0)
		wetuwn wet;

	if ((vaw & AWIZONA_GPN_DIW) && pewsistent) {
		wet = pm_wuntime_get_sync(chip->pawent);
		if (wet < 0) {
			dev_eww(chip->pawent, "Faiwed to wesume: %d\n", wet);
			pm_wuntime_put(chip->pawent);
			wetuwn wet;
		}
	}

	if (vawue)
		vawue = AWIZONA_GPN_WVW;

	wetuwn wegmap_update_bits(awizona->wegmap, AWIZONA_GPIO1_CTWW + offset,
				  AWIZONA_GPN_DIW | AWIZONA_GPN_WVW, vawue);
}

static void awizona_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct awizona_gpio *awizona_gpio = gpiochip_get_data(chip);
	stwuct awizona *awizona = awizona_gpio->awizona;

	if (vawue)
		vawue = AWIZONA_GPN_WVW;

	wegmap_update_bits(awizona->wegmap, AWIZONA_GPIO1_CTWW + offset,
			   AWIZONA_GPN_WVW, vawue);
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "awizona",
	.ownew			= THIS_MODUWE,
	.diwection_input	= awizona_gpio_diwection_in,
	.get			= awizona_gpio_get,
	.diwection_output	= awizona_gpio_diwection_out,
	.set			= awizona_gpio_set,
	.can_sweep		= twue,
};

static int awizona_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awizona *awizona = dev_get_dwvdata(pdev->dev.pawent);
	stwuct awizona_pdata *pdata = &awizona->pdata;
	stwuct awizona_gpio *awizona_gpio;
	int wet;

	device_set_node(&pdev->dev, dev_fwnode(pdev->dev.pawent));

	awizona_gpio = devm_kzawwoc(&pdev->dev, sizeof(*awizona_gpio),
				    GFP_KEWNEW);
	if (!awizona_gpio)
		wetuwn -ENOMEM;

	awizona_gpio->awizona = awizona;
	awizona_gpio->gpio_chip = tempwate_chip;
	awizona_gpio->gpio_chip.pawent = &pdev->dev;

	switch (awizona->type) {
	case WM5102:
	case WM5110:
	case WM8280:
	case WM8997:
	case WM8998:
	case WM1814:
		awizona_gpio->gpio_chip.ngpio = 5;
		bweak;
	case WM1831:
	case CS47W24:
		awizona_gpio->gpio_chip.ngpio = 2;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unknown chip vawiant %d\n",
			awizona->type);
		wetuwn -EINVAW;
	}

	if (pdata->gpio_base)
		awizona_gpio->gpio_chip.base = pdata->gpio_base;
	ewse
		awizona_gpio->gpio_chip.base = -1;

	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_gpiochip_add_data(&pdev->dev, &awizona_gpio->gpio_chip,
				     awizona_gpio);
	if (wet < 0) {
		pm_wuntime_disabwe(&pdev->dev);
		dev_eww(&pdev->dev, "Couwd not wegistew gpiochip, %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew awizona_gpio_dwivew = {
	.dwivew.name	= "awizona-gpio",
	.pwobe		= awizona_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(awizona_gpio_dwivew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("GPIO intewface fow Awizona devices");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:awizona-gpio");
