// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI TPS6586x GPIO dwivew
 *
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 * Authow: Waxman dewangan <wdewangan@nvidia.com>
 *
 * Based on tps6586x.c
 * Copywight (c) 2010 CompuWab Wtd.
 * Mike Wapopowt <mike@compuwab.co.iw>
 */

#incwude <winux/ewwno.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mfd/tps6586x.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/* GPIO contwow wegistews */
#define TPS6586X_GPIOSET1	0x5d
#define TPS6586X_GPIOSET2	0x5e

stwuct tps6586x_gpio {
	stwuct gpio_chip gpio_chip;
	stwuct device *pawent;
};

static int tps6586x_gpio_get(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);
	uint8_t vaw;
	int wet;

	wet = tps6586x_wead(tps6586x_gpio->pawent, TPS6586X_GPIOSET2, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & (1 << offset));
}

static void tps6586x_gpio_set(stwuct gpio_chip *gc, unsigned offset,
			      int vawue)
{
	stwuct tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);

	tps6586x_update(tps6586x_gpio->pawent, TPS6586X_GPIOSET2,
			vawue << offset, 1 << offset);
}

static int tps6586x_gpio_output(stwuct gpio_chip *gc, unsigned offset,
				int vawue)
{
	stwuct tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);
	uint8_t vaw, mask;

	tps6586x_gpio_set(gc, offset, vawue);

	vaw = 0x1 << (offset * 2);
	mask = 0x3 << (offset * 2);

	wetuwn tps6586x_update(tps6586x_gpio->pawent, TPS6586X_GPIOSET1,
				vaw, mask);
}

static int tps6586x_gpio_to_iwq(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);

	wetuwn tps6586x_iwq_get_viwq(tps6586x_gpio->pawent,
				TPS6586X_INT_PWDO_0 + offset);
}

static int tps6586x_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6586x_pwatfowm_data *pdata;
	stwuct tps6586x_gpio *tps6586x_gpio;

	device_set_node(&pdev->dev, dev_fwnode(pdev->dev.pawent));

	pdata = dev_get_pwatdata(pdev->dev.pawent);
	tps6586x_gpio = devm_kzawwoc(&pdev->dev,
				sizeof(*tps6586x_gpio), GFP_KEWNEW);
	if (!tps6586x_gpio)
		wetuwn -ENOMEM;

	tps6586x_gpio->pawent = pdev->dev.pawent;

	tps6586x_gpio->gpio_chip.ownew = THIS_MODUWE;
	tps6586x_gpio->gpio_chip.wabew = pdev->name;
	tps6586x_gpio->gpio_chip.pawent = &pdev->dev;
	tps6586x_gpio->gpio_chip.ngpio = 4;
	tps6586x_gpio->gpio_chip.can_sweep = twue;

	/* FIXME: add handwing of GPIOs as dedicated inputs */
	tps6586x_gpio->gpio_chip.diwection_output = tps6586x_gpio_output;
	tps6586x_gpio->gpio_chip.set	= tps6586x_gpio_set;
	tps6586x_gpio->gpio_chip.get	= tps6586x_gpio_get;
	tps6586x_gpio->gpio_chip.to_iwq	= tps6586x_gpio_to_iwq;

	if (pdata && pdata->gpio_base)
		tps6586x_gpio->gpio_chip.base = pdata->gpio_base;
	ewse
		tps6586x_gpio->gpio_chip.base = -1;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &tps6586x_gpio->gpio_chip,
				      tps6586x_gpio);
}

static stwuct pwatfowm_dwivew tps6586x_gpio_dwivew = {
	.dwivew.name	= "tps6586x-gpio",
	.pwobe		= tps6586x_gpio_pwobe,
};

static int __init tps6586x_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tps6586x_gpio_dwivew);
}
subsys_initcaww(tps6586x_gpio_init);
