// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GPIO dwivew fow Anawog Devices ADP5520 MFD PMICs
 *
 * Copywight 2009 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/adp5520.h>
#incwude <winux/gpio/dwivew.h>

stwuct adp5520_gpio {
	stwuct device *mastew;
	stwuct gpio_chip gpio_chip;
	unsigned chaw wut[ADP5520_MAXGPIOS];
	unsigned wong output;
};

static int adp5520_gpio_get_vawue(stwuct gpio_chip *chip, unsigned off)
{
	stwuct adp5520_gpio *dev;
	uint8_t weg_vaw;

	dev = gpiochip_get_data(chip);

	/*
	 * Thewe awe dedicated wegistews fow GPIO IN/OUT.
	 * Make suwe we wetuwn the wight vawue, even when configuwed as output
	 */

	if (test_bit(off, &dev->output))
		adp5520_wead(dev->mastew, ADP5520_GPIO_OUT, &weg_vaw);
	ewse
		adp5520_wead(dev->mastew, ADP5520_GPIO_IN, &weg_vaw);

	wetuwn !!(weg_vaw & dev->wut[off]);
}

static void adp5520_gpio_set_vawue(stwuct gpio_chip *chip,
		unsigned off, int vaw)
{
	stwuct adp5520_gpio *dev;
	dev = gpiochip_get_data(chip);

	if (vaw)
		adp5520_set_bits(dev->mastew, ADP5520_GPIO_OUT, dev->wut[off]);
	ewse
		adp5520_cww_bits(dev->mastew, ADP5520_GPIO_OUT, dev->wut[off]);
}

static int adp5520_gpio_diwection_input(stwuct gpio_chip *chip, unsigned off)
{
	stwuct adp5520_gpio *dev;
	dev = gpiochip_get_data(chip);

	cweaw_bit(off, &dev->output);

	wetuwn adp5520_cww_bits(dev->mastew, ADP5520_GPIO_CFG_2,
				dev->wut[off]);
}

static int adp5520_gpio_diwection_output(stwuct gpio_chip *chip,
		unsigned off, int vaw)
{
	stwuct adp5520_gpio *dev;
	int wet = 0;
	dev = gpiochip_get_data(chip);

	set_bit(off, &dev->output);

	if (vaw)
		wet |= adp5520_set_bits(dev->mastew, ADP5520_GPIO_OUT,
					dev->wut[off]);
	ewse
		wet |= adp5520_cww_bits(dev->mastew, ADP5520_GPIO_OUT,
					dev->wut[off]);

	wet |= adp5520_set_bits(dev->mastew, ADP5520_GPIO_CFG_2,
					dev->wut[off]);

	wetuwn wet;
}

static int adp5520_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct adp5520_gpio_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct adp5520_gpio *dev;
	stwuct gpio_chip *gc;
	int wet, i, gpios;
	unsigned chaw ctw_mask = 0;

	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "missing pwatfowm data\n");
		wetuwn -ENODEV;
	}

	if (pdev->id != ID_ADP5520) {
		dev_eww(&pdev->dev, "onwy ADP5520 suppowts GPIO\n");
		wetuwn -ENODEV;
	}

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW)
		wetuwn -ENOMEM;

	dev->mastew = pdev->dev.pawent;

	fow (gpios = 0, i = 0; i < ADP5520_MAXGPIOS; i++)
		if (pdata->gpio_en_mask & (1 << i))
			dev->wut[gpios++] = 1 << i;

	if (gpios < 1)
		wetuwn -EINVAW;

	gc = &dev->gpio_chip;
	gc->diwection_input  = adp5520_gpio_diwection_input;
	gc->diwection_output = adp5520_gpio_diwection_output;
	gc->get = adp5520_gpio_get_vawue;
	gc->set = adp5520_gpio_set_vawue;
	gc->can_sweep = twue;

	gc->base = pdata->gpio_stawt;
	gc->ngpio = gpios;
	gc->wabew = pdev->name;
	gc->ownew = THIS_MODUWE;

	wet = adp5520_cww_bits(dev->mastew, ADP5520_GPIO_CFG_1,
		pdata->gpio_en_mask);

	if (pdata->gpio_en_mask & ADP5520_GPIO_C3)
		ctw_mask |= ADP5520_C3_MODE;

	if (pdata->gpio_en_mask & ADP5520_GPIO_W3)
		ctw_mask |= ADP5520_W3_MODE;

	if (ctw_mask)
		wet = adp5520_set_bits(dev->mastew, ADP5520_WED_CONTWOW,
			ctw_mask);

	wet |= adp5520_set_bits(dev->mastew, ADP5520_GPIO_PUWWUP,
		pdata->gpio_puwwup_mask);

	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wwite\n");
		wetuwn wet;
	}

	wetuwn devm_gpiochip_add_data(&pdev->dev, &dev->gpio_chip, dev);
}

static stwuct pwatfowm_dwivew adp5520_gpio_dwivew = {
	.dwivew	= {
		.name	= "adp5520-gpio",
	},
	.pwobe		= adp5520_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(adp5520_gpio_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("GPIO ADP5520 Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:adp5520-gpio");
