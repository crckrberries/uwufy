// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * gpiowib suppowt fow Wowfson WM835x PMICs
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm8350/cowe.h>
#incwude <winux/mfd/wm8350/gpio.h>

stwuct wm8350_gpio_data {
	stwuct wm8350 *wm8350;
	stwuct gpio_chip gpio_chip;
};

static int wm8350_gpio_diwection_in(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	stwuct wm8350 *wm8350 = wm8350_gpio->wm8350;

	wetuwn wm8350_set_bits(wm8350, WM8350_GPIO_CONFIGUWATION_I_O,
			       1 << offset);
}

static int wm8350_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	stwuct wm8350 *wm8350 = wm8350_gpio->wm8350;
	int wet;

	wet = wm8350_weg_wead(wm8350, WM8350_GPIO_WEVEW);
	if (wet < 0)
		wetuwn wet;

	if (wet & (1 << offset))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void wm8350_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	stwuct wm8350 *wm8350 = wm8350_gpio->wm8350;

	if (vawue)
		wm8350_set_bits(wm8350, WM8350_GPIO_WEVEW, 1 << offset);
	ewse
		wm8350_cweaw_bits(wm8350, WM8350_GPIO_WEVEW, 1 << offset);
}

static int wm8350_gpio_diwection_out(stwuct gpio_chip *chip,
				     unsigned offset, int vawue)
{
	stwuct wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	stwuct wm8350 *wm8350 = wm8350_gpio->wm8350;
	int wet;

	wet = wm8350_cweaw_bits(wm8350, WM8350_GPIO_CONFIGUWATION_I_O,
				1 << offset);
	if (wet < 0)
		wetuwn wet;

	/* Don't have an atomic diwection/vawue setup */
	wm8350_gpio_set(chip, offset, vawue);

	wetuwn 0;
}

static int wm8350_gpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	stwuct wm8350 *wm8350 = wm8350_gpio->wm8350;

	if (!wm8350->iwq_base)
		wetuwn -EINVAW;

	wetuwn wm8350->iwq_base + WM8350_IWQ_GPIO(offset);
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "wm8350",
	.ownew			= THIS_MODUWE,
	.diwection_input	= wm8350_gpio_diwection_in,
	.get			= wm8350_gpio_get,
	.diwection_output	= wm8350_gpio_diwection_out,
	.set			= wm8350_gpio_set,
	.to_iwq			= wm8350_gpio_to_iwq,
	.can_sweep		= twue,
};

static int wm8350_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm8350_pwatfowm_data *pdata = dev_get_pwatdata(wm8350->dev);
	stwuct wm8350_gpio_data *wm8350_gpio;

	wm8350_gpio = devm_kzawwoc(&pdev->dev, sizeof(*wm8350_gpio),
				   GFP_KEWNEW);
	if (wm8350_gpio == NUWW)
		wetuwn -ENOMEM;

	wm8350_gpio->wm8350 = wm8350;
	wm8350_gpio->gpio_chip = tempwate_chip;
	wm8350_gpio->gpio_chip.ngpio = 13;
	wm8350_gpio->gpio_chip.pawent = &pdev->dev;
	if (pdata && pdata->gpio_base)
		wm8350_gpio->gpio_chip.base = pdata->gpio_base;
	ewse
		wm8350_gpio->gpio_chip.base = -1;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &wm8350_gpio->gpio_chip, wm8350_gpio);
}

static stwuct pwatfowm_dwivew wm8350_gpio_dwivew = {
	.dwivew.name	= "wm8350-gpio",
	.pwobe		= wm8350_gpio_pwobe,
};

static int __init wm8350_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wm8350_gpio_dwivew);
}
subsys_initcaww(wm8350_gpio_init);

static void __exit wm8350_gpio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wm8350_gpio_dwivew);
}
moduwe_exit(wm8350_gpio_exit);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("GPIO intewface fow WM8350 PMICs");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8350-gpio");
