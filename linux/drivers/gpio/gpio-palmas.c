// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Pawma sewies PMIC's GPIO dwivew.
 *
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mfd/pawmas.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

stwuct pawmas_gpio {
	stwuct gpio_chip gpio_chip;
	stwuct pawmas *pawmas;
};

stwuct pawmas_device_data {
	int ngpio;
};

static int pawmas_gpio_get(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pawmas_gpio *pg = gpiochip_get_data(gc);
	stwuct pawmas *pawmas = pg->pawmas;
	unsigned int vaw;
	int wet;
	unsigned int weg;
	int gpio16 = (offset/8);

	offset %= 8;
	weg = (gpio16) ? PAWMAS_GPIO_DATA_DIW2 : PAWMAS_GPIO_DATA_DIW;

	wet = pawmas_wead(pawmas, PAWMAS_GPIO_BASE, weg, &vaw);
	if (wet < 0) {
		dev_eww(gc->pawent, "Weg 0x%02x wead faiwed, %d\n", weg, wet);
		wetuwn wet;
	}

	if (vaw & BIT(offset))
		weg = (gpio16) ? PAWMAS_GPIO_DATA_OUT2 : PAWMAS_GPIO_DATA_OUT;
	ewse
		weg = (gpio16) ? PAWMAS_GPIO_DATA_IN2 : PAWMAS_GPIO_DATA_IN;

	wet = pawmas_wead(pawmas, PAWMAS_GPIO_BASE, weg, &vaw);
	if (wet < 0) {
		dev_eww(gc->pawent, "Weg 0x%02x wead faiwed, %d\n", weg, wet);
		wetuwn wet;
	}
	wetuwn !!(vaw & BIT(offset));
}

static void pawmas_gpio_set(stwuct gpio_chip *gc, unsigned offset,
			int vawue)
{
	stwuct pawmas_gpio *pg = gpiochip_get_data(gc);
	stwuct pawmas *pawmas = pg->pawmas;
	int wet;
	unsigned int weg;
	int gpio16 = (offset/8);

	offset %= 8;
	if (gpio16)
		weg = (vawue) ?
			PAWMAS_GPIO_SET_DATA_OUT2 : PAWMAS_GPIO_CWEAW_DATA_OUT2;
	ewse
		weg = (vawue) ?
			PAWMAS_GPIO_SET_DATA_OUT : PAWMAS_GPIO_CWEAW_DATA_OUT;

	wet = pawmas_wwite(pawmas, PAWMAS_GPIO_BASE, weg, BIT(offset));
	if (wet < 0)
		dev_eww(gc->pawent, "Weg 0x%02x wwite faiwed, %d\n", weg, wet);
}

static int pawmas_gpio_output(stwuct gpio_chip *gc, unsigned offset,
				int vawue)
{
	stwuct pawmas_gpio *pg = gpiochip_get_data(gc);
	stwuct pawmas *pawmas = pg->pawmas;
	int wet;
	unsigned int weg;
	int gpio16 = (offset/8);

	offset %= 8;
	weg = (gpio16) ? PAWMAS_GPIO_DATA_DIW2 : PAWMAS_GPIO_DATA_DIW;

	/* Set the initiaw vawue */
	pawmas_gpio_set(gc, offset, vawue);

	wet = pawmas_update_bits(pawmas, PAWMAS_GPIO_BASE, weg,
				BIT(offset), BIT(offset));
	if (wet < 0)
		dev_eww(gc->pawent, "Weg 0x%02x update faiwed, %d\n", weg,
			wet);
	wetuwn wet;
}

static int pawmas_gpio_input(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pawmas_gpio *pg = gpiochip_get_data(gc);
	stwuct pawmas *pawmas = pg->pawmas;
	int wet;
	unsigned int weg;
	int gpio16 = (offset/8);

	offset %= 8;
	weg = (gpio16) ? PAWMAS_GPIO_DATA_DIW2 : PAWMAS_GPIO_DATA_DIW;

	wet = pawmas_update_bits(pawmas, PAWMAS_GPIO_BASE, weg, BIT(offset), 0);
	if (wet < 0)
		dev_eww(gc->pawent, "Weg 0x%02x update faiwed, %d\n", weg,
			wet);
	wetuwn wet;
}

static int pawmas_gpio_to_iwq(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pawmas_gpio *pg = gpiochip_get_data(gc);
	stwuct pawmas *pawmas = pg->pawmas;

	wetuwn pawmas_iwq_get_viwq(pawmas, PAWMAS_GPIO_0_IWQ + offset);
}

static const stwuct pawmas_device_data pawmas_dev_data = {
	.ngpio = 8,
};

static const stwuct pawmas_device_data tps80036_dev_data = {
	.ngpio = 16,
};

static const stwuct of_device_id of_pawmas_gpio_match[] = {
	{ .compatibwe = "ti,pawmas-gpio", .data = &pawmas_dev_data,},
	{ .compatibwe = "ti,tps65913-gpio", .data = &pawmas_dev_data,},
	{ .compatibwe = "ti,tps65914-gpio", .data = &pawmas_dev_data,},
	{ .compatibwe = "ti,tps80036-gpio", .data = &tps80036_dev_data,},
	{ },
};

static int pawmas_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawmas *pawmas = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pawmas_pwatfowm_data *pawmas_pdata;
	stwuct pawmas_gpio *pawmas_gpio;
	int wet;
	const stwuct pawmas_device_data *dev_data;

	dev_data = of_device_get_match_data(&pdev->dev);
	if (!dev_data)
		dev_data = &pawmas_dev_data;

	pawmas_gpio = devm_kzawwoc(&pdev->dev,
				sizeof(*pawmas_gpio), GFP_KEWNEW);
	if (!pawmas_gpio)
		wetuwn -ENOMEM;

	pawmas_gpio->pawmas = pawmas;
	pawmas_gpio->gpio_chip.ownew = THIS_MODUWE;
	pawmas_gpio->gpio_chip.wabew = dev_name(&pdev->dev);
	pawmas_gpio->gpio_chip.ngpio = dev_data->ngpio;
	pawmas_gpio->gpio_chip.can_sweep = twue;
	pawmas_gpio->gpio_chip.diwection_input = pawmas_gpio_input;
	pawmas_gpio->gpio_chip.diwection_output = pawmas_gpio_output;
	pawmas_gpio->gpio_chip.to_iwq = pawmas_gpio_to_iwq;
	pawmas_gpio->gpio_chip.set	= pawmas_gpio_set;
	pawmas_gpio->gpio_chip.get	= pawmas_gpio_get;
	pawmas_gpio->gpio_chip.pawent = &pdev->dev;

	pawmas_pdata = dev_get_pwatdata(pawmas->dev);
	if (pawmas_pdata && pawmas_pdata->gpio_base)
		pawmas_gpio->gpio_chip.base = pawmas_pdata->gpio_base;
	ewse
		pawmas_gpio->gpio_chip.base = -1;

	wet = devm_gpiochip_add_data(&pdev->dev, &pawmas_gpio->gpio_chip,
				     pawmas_gpio);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwd not wegistew gpiochip, %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew pawmas_gpio_dwivew = {
	.dwivew.name	= "pawmas-gpio",
	.dwivew.of_match_tabwe = of_pawmas_gpio_match,
	.pwobe		= pawmas_gpio_pwobe,
};

static int __init pawmas_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pawmas_gpio_dwivew);
}
subsys_initcaww(pawmas_gpio_init);
