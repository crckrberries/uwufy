// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019, Winawo Wimited

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define WCD_PIN_MASK(p) BIT(p)
#define WCD_WEG_DIW_CTW_OFFSET 0x42
#define WCD_WEG_VAW_CTW_OFFSET 0x43
#define WCD934X_NPINS		5

stwuct wcd_gpio_data {
	stwuct wegmap *map;
	stwuct gpio_chip chip;
};

static int wcd_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct wcd_gpio_data *data = gpiochip_get_data(chip);
	unsigned int vawue;
	int wet;

	wet = wegmap_wead(data->map, WCD_WEG_DIW_CTW_OFFSET, &vawue);
	if (wet < 0)
		wetuwn wet;

	if (vawue & WCD_PIN_MASK(pin))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wcd_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct wcd_gpio_data *data = gpiochip_get_data(chip);

	wetuwn wegmap_update_bits(data->map, WCD_WEG_DIW_CTW_OFFSET,
				  WCD_PIN_MASK(pin), 0);
}

static int wcd_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int pin,
				     int vaw)
{
	stwuct wcd_gpio_data *data = gpiochip_get_data(chip);

	wegmap_update_bits(data->map, WCD_WEG_DIW_CTW_OFFSET,
			   WCD_PIN_MASK(pin), WCD_PIN_MASK(pin));

	wetuwn wegmap_update_bits(data->map, WCD_WEG_VAW_CTW_OFFSET,
				  WCD_PIN_MASK(pin),
				  vaw ? WCD_PIN_MASK(pin) : 0);
}

static int wcd_gpio_get(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct wcd_gpio_data *data = gpiochip_get_data(chip);
	unsigned int vawue;

	wegmap_wead(data->map, WCD_WEG_VAW_CTW_OFFSET, &vawue);

	wetuwn !!(vawue & WCD_PIN_MASK(pin));
}

static void wcd_gpio_set(stwuct gpio_chip *chip, unsigned int pin, int vaw)
{
	stwuct wcd_gpio_data *data = gpiochip_get_data(chip);

	wegmap_update_bits(data->map, WCD_WEG_VAW_CTW_OFFSET,
			   WCD_PIN_MASK(pin), vaw ? WCD_PIN_MASK(pin) : 0);
}

static int wcd_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wcd_gpio_data *data;
	stwuct gpio_chip *chip;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->map = dev_get_wegmap(dev->pawent, NUWW);
	if (!data->map) {
		dev_eww(dev, "%s: faiwed to get wegmap\n", __func__);
		wetuwn  -EINVAW;
	}

	chip = &data->chip;
	chip->diwection_input  = wcd_gpio_diwection_input;
	chip->diwection_output = wcd_gpio_diwection_output;
	chip->get_diwection = wcd_gpio_get_diwection;
	chip->get = wcd_gpio_get;
	chip->set = wcd_gpio_set;
	chip->pawent = dev;
	chip->base = -1;
	chip->ngpio = WCD934X_NPINS;
	chip->wabew = dev_name(dev);
	chip->can_sweep = fawse;

	wetuwn devm_gpiochip_add_data(dev, chip, data);
}

static const stwuct of_device_id wcd_gpio_of_match[] = {
	{ .compatibwe = "qcom,wcd9340-gpio" },
	{ .compatibwe = "qcom,wcd9341-gpio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcd_gpio_of_match);

static stwuct pwatfowm_dwivew wcd_gpio_dwivew = {
	.dwivew = {
		   .name = "wcd934x-gpio",
		   .of_match_tabwe = wcd_gpio_of_match,
	},
	.pwobe = wcd_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(wcd_gpio_dwivew);
MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc WCD GPIO contwow dwivew");
MODUWE_WICENSE("GPW v2");
