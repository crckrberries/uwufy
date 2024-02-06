// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8731-i2c.c  --  WM8731 AWSA SoC Audio dwivew I2C code
 *
 * Copywight 2005 Openedhand Wtd.
 * Copywight 2006-12 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Wichawd Puwdie <wichawd@openedhand.com>
 *
 * Based on wm8753.c by Wiam Giwdwood
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

#incwude "wm8731.h"


static const stwuct of_device_id wm8731_of_match[] = {
	{ .compatibwe = "wwf,wm8731", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8731_of_match);

static int wm8731_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8731_pwiv *wm8731;
	int wet;

	wm8731 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8731_pwiv),
			      GFP_KEWNEW);
	if (wm8731 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wm8731);

	wm8731->wegmap = devm_wegmap_init_i2c(i2c, &wm8731_wegmap);
	if (IS_EWW(wm8731->wegmap)) {
		wet = PTW_EWW(wm8731->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn wm8731_init(&i2c->dev, wm8731);
}

static const stwuct i2c_device_id wm8731_i2c_id[] = {
	{ "wm8731", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8731_i2c_id);

static stwuct i2c_dwivew wm8731_i2c_dwivew = {
	.dwivew = {
		.name = "wm8731",
		.of_match_tabwe = wm8731_of_match,
	},
	.pwobe = wm8731_i2c_pwobe,
	.id_tabwe = wm8731_i2c_id,
};

moduwe_i2c_dwivew(wm8731_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM8731 dwivew - I2C");
MODUWE_AUTHOW("Wichawd Puwdie");
MODUWE_WICENSE("GPW");
