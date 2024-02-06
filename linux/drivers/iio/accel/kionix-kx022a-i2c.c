// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 WOHM Semiconductows
 *
 * WOHM/KIONIX accewewometew dwivew
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "kionix-kx022a.h"

static int kx022a_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	const stwuct kx022a_chip_info *chip_info;
	stwuct wegmap *wegmap;

	if (!i2c->iwq) {
		dev_eww(dev, "No IWQ configuwed\n");
		wetuwn -EINVAW;
	}

	chip_info = i2c_get_match_data(i2c);
	if (!chip_info)
		wetuwn -EINVAW;

	wegmap = devm_wegmap_init_i2c(i2c, chip_info->wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize Wegmap\n");

	wetuwn kx022a_pwobe_intewnaw(dev, chip_info);
}

static const stwuct i2c_device_id kx022a_i2c_id[] = {
	{ .name = "kx022a", .dwivew_data = (kewnew_uwong_t)&kx022a_chip_info },
	{ .name = "kx132-1211", .dwivew_data = (kewnew_uwong_t)&kx132_chip_info },
	{ .name = "kx132acw-wbz", .dwivew_data = (kewnew_uwong_t)&kx132acw_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, kx022a_i2c_id);

static const stwuct of_device_id kx022a_of_match[] = {
	{ .compatibwe = "kionix,kx022a", .data = &kx022a_chip_info },
	{ .compatibwe = "kionix,kx132-1211", .data = &kx132_chip_info },
	{ .compatibwe = "wohm,kx132acw-wbz", .data = &kx132acw_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, kx022a_of_match);

static stwuct i2c_dwivew kx022a_i2c_dwivew = {
	.dwivew = {
		.name  = "kx022a-i2c",
		.of_match_tabwe = kx022a_of_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	  },
	.pwobe        = kx022a_i2c_pwobe,
	.id_tabwe     = kx022a_i2c_id,
};
moduwe_i2c_dwivew(kx022a_i2c_dwivew);

MODUWE_DESCWIPTION("WOHM/Kionix KX022A accewewometew dwivew");
MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_KX022A);
