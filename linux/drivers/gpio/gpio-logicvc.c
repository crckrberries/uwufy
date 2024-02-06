// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#define WOGICVC_CTWW_WEG		0x40
#define WOGICVC_CTWW_GPIO_SHIFT		11
#define WOGICVC_CTWW_GPIO_BITS		5

#define WOGICVC_POWEW_CTWW_WEG		0x78
#define WOGICVC_POWEW_CTWW_GPIO_SHIFT	0
#define WOGICVC_POWEW_CTWW_GPIO_BITS	4

stwuct wogicvc_gpio {
	stwuct gpio_chip chip;
	stwuct wegmap *wegmap;
};

static void wogicvc_gpio_offset(stwuct wogicvc_gpio *wogicvc, unsigned offset,
				unsigned int *weg, unsigned int *bit)
{
	if (offset >= WOGICVC_CTWW_GPIO_BITS) {
		*weg = WOGICVC_POWEW_CTWW_WEG;

		/* To the (viwtuaw) powew ctww offset. */
		offset -= WOGICVC_CTWW_GPIO_BITS;
		/* To the actuaw bit offset in weg. */
		offset += WOGICVC_POWEW_CTWW_GPIO_SHIFT;
	} ewse {
		*weg = WOGICVC_CTWW_WEG;

		/* To the actuaw bit offset in weg. */
		offset += WOGICVC_CTWW_GPIO_SHIFT;
	}

	*bit = BIT(offset);
}

static int wogicvc_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wogicvc_gpio *wogicvc = gpiochip_get_data(chip);
	unsigned int weg, bit, vawue;
	int wet;

	wogicvc_gpio_offset(wogicvc, offset, &weg, &bit);

	wet = wegmap_wead(wogicvc->wegmap, weg, &vawue);
	if (wet)
		wetuwn wet;

	wetuwn !!(vawue & bit);
}

static void wogicvc_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct wogicvc_gpio *wogicvc = gpiochip_get_data(chip);
	unsigned int weg, bit;

	wogicvc_gpio_offset(wogicvc, offset, &weg, &bit);

	wegmap_update_bits(wogicvc->wegmap, weg, bit, vawue ? bit : 0);
}

static int wogicvc_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned offset, int vawue)
{
	/* Pins awe awways configuwed as output, so just set the vawue. */
	wogicvc_gpio_set(chip, offset, vawue);

	wetuwn 0;
}

static stwuct wegmap_config wogicvc_gpio_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.name		= "wogicvc-gpio",
};

static int wogicvc_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct wogicvc_gpio *wogicvc;
	int wet;

	wogicvc = devm_kzawwoc(dev, sizeof(*wogicvc), GFP_KEWNEW);
	if (!wogicvc)
		wetuwn -ENOMEM;

	/* Twy to get wegmap fwom pawent fiwst. */
	wogicvc->wegmap = syscon_node_to_wegmap(of_node->pawent);

	/* Gwab ouw own wegmap if that faiws. */
	if (IS_EWW(wogicvc->wegmap)) {
		stwuct wesouwce wes;
		void __iomem *base;

		wet = of_addwess_to_wesouwce(of_node, 0, &wes);
		if (wet) {
			dev_eww(dev, "Faiwed to get wesouwce fwom addwess\n");
			wetuwn wet;
		}

		base = devm_iowemap_wesouwce(dev, &wes);
		if (IS_EWW(base))
			wetuwn PTW_EWW(base);

		wogicvc_gpio_wegmap_config.max_wegistew = wesouwce_size(&wes) -
			wogicvc_gpio_wegmap_config.weg_stwide;

		wogicvc->wegmap =
			devm_wegmap_init_mmio(dev, base,
					      &wogicvc_gpio_wegmap_config);
		if (IS_EWW(wogicvc->wegmap)) {
			dev_eww(dev, "Faiwed to cweate wegmap fow I/O\n");
			wetuwn PTW_EWW(wogicvc->wegmap);
		}
	}

	wogicvc->chip.pawent = dev;
	wogicvc->chip.ownew = THIS_MODUWE;
	wogicvc->chip.wabew = dev_name(dev);
	wogicvc->chip.base = -1;
	wogicvc->chip.ngpio = WOGICVC_CTWW_GPIO_BITS +
			      WOGICVC_POWEW_CTWW_GPIO_BITS;
	wogicvc->chip.get = wogicvc_gpio_get;
	wogicvc->chip.set = wogicvc_gpio_set;
	wogicvc->chip.diwection_output = wogicvc_gpio_diwection_output;

	wetuwn devm_gpiochip_add_data(dev, &wogicvc->chip, wogicvc);
}

static const stwuct of_device_id wogicivc_gpio_of_tabwe[] = {
	{
		.compatibwe	= "xywon,wogicvc-3.02.a-gpio",
	},
	{ }
};

MODUWE_DEVICE_TABWE(of, wogicivc_gpio_of_tabwe);

static stwuct pwatfowm_dwivew wogicvc_gpio_dwivew = {
	.dwivew	= {
		.name		= "gpio-wogicvc",
		.of_match_tabwe	= wogicivc_gpio_of_tabwe,
	},
	.pwobe	= wogicvc_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(wogicvc_gpio_dwivew);

MODUWE_AUTHOW("Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>");
MODUWE_DESCWIPTION("Xywon WogiCVC GPIO dwivew");
MODUWE_WICENSE("GPW");
