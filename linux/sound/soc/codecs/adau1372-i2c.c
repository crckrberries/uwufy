// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow ADAU1372 codec
 *
 * Copywight 2016 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "adau1372.h"

static int adau1372_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn adau1372_pwobe(&cwient->dev,
		devm_wegmap_init_i2c(cwient, &adau1372_wegmap_config), NUWW);
}

static const stwuct i2c_device_id adau1372_i2c_ids[] = {
	{ "adau1372", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adau1372_i2c_ids);

static stwuct i2c_dwivew adau1372_i2c_dwivew = {
	.dwivew = {
		.name = "adau1372",
	},
	.pwobe = adau1372_i2c_pwobe,
	.id_tabwe = adau1372_i2c_ids,
};
moduwe_i2c_dwivew(adau1372_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1372 CODEC I2C dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW v2");
