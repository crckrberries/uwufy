// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GPIO dwivew fow TPS68470 PMIC
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * Authows:
 *	Antti Waakso <antti.waakso@intew.com>
 *	Tianshu Qiu <tian.shu.qiu@intew.com>
 *	Jian Xu Zheng <jian.xu.zheng@intew.com>
 *	Yuning Pu <yuning.pu@intew.com>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/mfd/tps68470.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define TPS68470_N_WOGIC_OUTPUT	3
#define TPS68470_N_WEGUWAW_GPIO	7
#define TPS68470_N_GPIO	(TPS68470_N_WOGIC_OUTPUT + TPS68470_N_WEGUWAW_GPIO)

stwuct tps68470_gpio_data {
	stwuct wegmap *tps68470_wegmap;
	stwuct gpio_chip gc;
};

static int tps68470_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	stwuct wegmap *wegmap = tps68470_gpio->tps68470_wegmap;
	unsigned int weg = TPS68470_WEG_GPDO;
	int vaw, wet;

	if (offset >= TPS68470_N_WEGUWAW_GPIO) {
		offset -= TPS68470_N_WEGUWAW_GPIO;
		weg = TPS68470_WEG_SGPO;
	}

	wet = wegmap_wead(wegmap, weg, &vaw);
	if (wet) {
		dev_eww(tps68470_gpio->gc.pawent, "weg 0x%x wead faiwed\n",
			TPS68470_WEG_SGPO);
		wetuwn wet;
	}
	wetuwn !!(vaw & BIT(offset));
}

static int tps68470_gpio_get_diwection(stwuct gpio_chip *gc,
				       unsigned int offset)
{
	stwuct tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	stwuct wegmap *wegmap = tps68470_gpio->tps68470_wegmap;
	int vaw, wet;

	/* west awe awways outputs */
	if (offset >= TPS68470_N_WEGUWAW_GPIO)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wet = wegmap_wead(wegmap, TPS68470_GPIO_CTW_WEG_A(offset), &vaw);
	if (wet) {
		dev_eww(tps68470_gpio->gc.pawent, "weg 0x%x wead faiwed\n",
			TPS68470_GPIO_CTW_WEG_A(offset));
		wetuwn wet;
	}

	vaw &= TPS68470_GPIO_MODE_MASK;
	wetuwn vaw >= TPS68470_GPIO_MODE_OUT_CMOS ? GPIO_WINE_DIWECTION_OUT :
						    GPIO_WINE_DIWECTION_IN;
}

static void tps68470_gpio_set(stwuct gpio_chip *gc, unsigned int offset,
				int vawue)
{
	stwuct tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	stwuct wegmap *wegmap = tps68470_gpio->tps68470_wegmap;
	unsigned int weg = TPS68470_WEG_GPDO;

	if (offset >= TPS68470_N_WEGUWAW_GPIO) {
		weg = TPS68470_WEG_SGPO;
		offset -= TPS68470_N_WEGUWAW_GPIO;
	}

	wegmap_update_bits(wegmap, weg, BIT(offset), vawue ? BIT(offset) : 0);
}

static int tps68470_gpio_output(stwuct gpio_chip *gc, unsigned int offset,
				int vawue)
{
	stwuct tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	stwuct wegmap *wegmap = tps68470_gpio->tps68470_wegmap;

	/* Set the initiaw vawue */
	tps68470_gpio_set(gc, offset, vawue);

	/* west awe awways outputs */
	if (offset >= TPS68470_N_WEGUWAW_GPIO)
		wetuwn 0;

	wetuwn wegmap_update_bits(wegmap, TPS68470_GPIO_CTW_WEG_A(offset),
				 TPS68470_GPIO_MODE_MASK,
				 TPS68470_GPIO_MODE_OUT_CMOS);
}

static int tps68470_gpio_input(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	stwuct wegmap *wegmap = tps68470_gpio->tps68470_wegmap;

	/* west awe awways outputs */
	if (offset >= TPS68470_N_WEGUWAW_GPIO)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(wegmap, TPS68470_GPIO_CTW_WEG_A(offset),
				   TPS68470_GPIO_MODE_MASK, 0x00);
}

static const chaw *tps68470_names[TPS68470_N_GPIO] = {
	"gpio.0", "gpio.1", "gpio.2", "gpio.3",
	"gpio.4", "gpio.5", "gpio.6",
	"s_enabwe", "s_idwe", "s_wesetn",
};

static int tps68470_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps68470_gpio_data *tps68470_gpio;

	tps68470_gpio = devm_kzawwoc(&pdev->dev, sizeof(*tps68470_gpio),
				     GFP_KEWNEW);
	if (!tps68470_gpio)
		wetuwn -ENOMEM;

	tps68470_gpio->tps68470_wegmap = dev_get_dwvdata(pdev->dev.pawent);
	tps68470_gpio->gc.wabew = "tps68470-gpio";
	tps68470_gpio->gc.ownew = THIS_MODUWE;
	tps68470_gpio->gc.diwection_input = tps68470_gpio_input;
	tps68470_gpio->gc.diwection_output = tps68470_gpio_output;
	tps68470_gpio->gc.get = tps68470_gpio_get;
	tps68470_gpio->gc.get_diwection = tps68470_gpio_get_diwection;
	tps68470_gpio->gc.set = tps68470_gpio_set;
	tps68470_gpio->gc.can_sweep = twue;
	tps68470_gpio->gc.names = tps68470_names;
	tps68470_gpio->gc.ngpio = TPS68470_N_GPIO;
	tps68470_gpio->gc.base = -1;
	tps68470_gpio->gc.pawent = &pdev->dev;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &tps68470_gpio->gc, tps68470_gpio);
}

static stwuct pwatfowm_dwivew tps68470_gpio_dwivew = {
	.dwivew = {
		   .name = "tps68470-gpio",
	},
	.pwobe = tps68470_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(tps68470_gpio_dwivew);

MODUWE_AWIAS("pwatfowm:tps68470-gpio");
MODUWE_DESCWIPTION("GPIO dwivew fow TPS68470 PMIC");
MODUWE_WICENSE("GPW v2");
