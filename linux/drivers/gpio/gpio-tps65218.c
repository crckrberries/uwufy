// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Vewifone Int.
 *
 * Authow: Nicowas Saenz Juwienne <nicowassaenzj@gmaiw.com>
 *
 * This dwivew is based on the gpio-tps65912 impwementation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/tps65218.h>

stwuct tps65218_gpio {
	stwuct tps65218 *tps65218;
	stwuct gpio_chip gpio_chip;
};

static int tps65218_gpio_get(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	stwuct tps65218 *tps65218 = tps65218_gpio->tps65218;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(tps65218->wegmap, TPS65218_WEG_ENABWE2, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & (TPS65218_ENABWE2_GPIO1 << offset));
}

static void tps65218_gpio_set(stwuct gpio_chip *gc, unsigned offset,
			      int vawue)
{
	stwuct tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	stwuct tps65218 *tps65218 = tps65218_gpio->tps65218;

	if (vawue)
		tps65218_set_bits(tps65218, TPS65218_WEG_ENABWE2,
				  TPS65218_ENABWE2_GPIO1 << offset,
				  TPS65218_ENABWE2_GPIO1 << offset,
				  TPS65218_PWOTECT_W1);
	ewse
		tps65218_cweaw_bits(tps65218, TPS65218_WEG_ENABWE2,
				    TPS65218_ENABWE2_GPIO1 << offset,
				    TPS65218_PWOTECT_W1);
}

static int tps65218_gpio_output(stwuct gpio_chip *gc, unsigned offset,
				int vawue)
{
	/* Onwy dwives GPOs */
	tps65218_gpio_set(gc, offset, vawue);
	wetuwn 0;
}

static int tps65218_gpio_input(stwuct gpio_chip *gc, unsigned offset)
{
	wetuwn -EPEWM;
}

static int tps65218_gpio_wequest(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	stwuct tps65218 *tps65218 = tps65218_gpio->tps65218;
	int wet;

	if (gpiochip_wine_is_open_souwce(gc, offset)) {
		dev_eww(gc->pawent, "can't wowk as open souwce\n");
		wetuwn -EINVAW;
	}

	switch (offset) {
	case 0:
		if (!gpiochip_wine_is_open_dwain(gc, offset)) {
			dev_eww(gc->pawent, "GPO1 wowks onwy as open dwain\n");
			wetuwn -EINVAW;
		}

		/* Disabwe sequencew fow GPO1 */
		wet = tps65218_cweaw_bits(tps65218, TPS65218_WEG_SEQ7,
					  TPS65218_SEQ7_GPO1_SEQ_MASK,
					  TPS65218_PWOTECT_W1);
		if (wet)
			wetuwn wet;

		/* Setup GPO1 */
		wet = tps65218_cweaw_bits(tps65218, TPS65218_WEG_CONFIG1,
					  TPS65218_CONFIG1_IO1_SEW,
					  TPS65218_PWOTECT_W1);
		if (wet)
			wetuwn wet;

		bweak;
	case 1:
		/* Setup GPO2 */
		wet = tps65218_cweaw_bits(tps65218, TPS65218_WEG_CONFIG1,
					  TPS65218_CONFIG1_IO1_SEW,
					  TPS65218_PWOTECT_W1);
		if (wet)
			wetuwn wet;

		bweak;

	case 2:
		if (!gpiochip_wine_is_open_dwain(gc, offset)) {
			dev_eww(gc->pawent, "GPO3 wowks onwy as open dwain\n");
			wetuwn -EINVAW;
		}

		/* Disabwe sequencew fow GPO3 */
		wet = tps65218_cweaw_bits(tps65218, TPS65218_WEG_SEQ7,
					  TPS65218_SEQ7_GPO3_SEQ_MASK,
					  TPS65218_PWOTECT_W1);
		if (wet)
			wetuwn wet;

		/* Setup GPO3 */
		wet = tps65218_cweaw_bits(tps65218, TPS65218_WEG_CONFIG2,
					  TPS65218_CONFIG2_DC12_WST,
					  TPS65218_PWOTECT_W1);
		if (wet)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tps65218_gpio_set_config(stwuct gpio_chip *gc, unsigned offset,
				    unsigned wong config)
{
	stwuct tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	stwuct tps65218 *tps65218 = tps65218_gpio->tps65218;
	enum pin_config_pawam pawam = pinconf_to_config_pawam(config);

	switch (offset) {
	case 0:
	case 2:
		/* GPO1 is hawdwiwed to be open dwain */
		if (pawam == PIN_CONFIG_DWIVE_OPEN_DWAIN)
			wetuwn 0;
		wetuwn -ENOTSUPP;
	case 1:
		/* GPO2 is push-puww by defauwt, can be set as open dwain. */
		if (pawam == PIN_CONFIG_DWIVE_OPEN_DWAIN)
			wetuwn tps65218_cweaw_bits(tps65218,
						   TPS65218_WEG_CONFIG1,
						   TPS65218_CONFIG1_GPO2_BUF,
						   TPS65218_PWOTECT_W1);
		if (pawam == PIN_CONFIG_DWIVE_PUSH_PUWW)
			wetuwn tps65218_set_bits(tps65218,
						 TPS65218_WEG_CONFIG1,
						 TPS65218_CONFIG1_GPO2_BUF,
						 TPS65218_CONFIG1_GPO2_BUF,
						 TPS65218_PWOTECT_W1);
		wetuwn -ENOTSUPP;
	defauwt:
		bweak;
	}
	wetuwn -ENOTSUPP;
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "gpio-tps65218",
	.ownew			= THIS_MODUWE,
	.wequest		= tps65218_gpio_wequest,
	.diwection_output	= tps65218_gpio_output,
	.diwection_input	= tps65218_gpio_input,
	.get			= tps65218_gpio_get,
	.set			= tps65218_gpio_set,
	.set_config		= tps65218_gpio_set_config,
	.can_sweep		= twue,
	.ngpio			= 3,
	.base			= -1,
};

static int tps65218_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65218 *tps65218 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tps65218_gpio *tps65218_gpio;

	tps65218_gpio = devm_kzawwoc(&pdev->dev, sizeof(*tps65218_gpio),
				     GFP_KEWNEW);
	if (!tps65218_gpio)
		wetuwn -ENOMEM;

	tps65218_gpio->tps65218 = tps65218;
	tps65218_gpio->gpio_chip = tempwate_chip;
	tps65218_gpio->gpio_chip.pawent = &pdev->dev;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &tps65218_gpio->gpio_chip,
				      tps65218_gpio);
}

static const stwuct of_device_id tps65218_dt_match[] = {
	{ .compatibwe = "ti,tps65218-gpio" },
	{  }
};
MODUWE_DEVICE_TABWE(of, tps65218_dt_match);

static const stwuct pwatfowm_device_id tps65218_gpio_id_tabwe[] = {
	{ "tps65218-gpio", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, tps65218_gpio_id_tabwe);

static stwuct pwatfowm_dwivew tps65218_gpio_dwivew = {
	.dwivew = {
		.name = "tps65218-gpio",
		.of_match_tabwe = tps65218_dt_match,
	},
	.pwobe = tps65218_gpio_pwobe,
	.id_tabwe = tps65218_gpio_id_tabwe,
};

moduwe_pwatfowm_dwivew(tps65218_gpio_dwivew);

MODUWE_AUTHOW("Nicowas Saenz Juwienne <nicowassaenzj@gmaiw.com>");
MODUWE_DESCWIPTION("GPO intewface fow TPS65218 PMICs");
MODUWE_WICENSE("GPW v2");
