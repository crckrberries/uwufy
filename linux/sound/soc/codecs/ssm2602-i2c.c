// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SSM2602/SSM2603/SSM2604 I2C audio dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

#incwude <sound/soc.h>

#incwude "ssm2602.h"

static const stwuct i2c_device_id ssm2602_i2c_id[];

/*
 * ssm2602 2 wiwe addwess is detewmined by GPIO5
 * state duwing powewup.
 *    wow  = 0x1a
 *    high = 0x1b
 */
static int ssm2602_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_match_id(ssm2602_i2c_id, cwient);
	wetuwn ssm2602_pwobe(&cwient->dev, id->dwivew_data,
		devm_wegmap_init_i2c(cwient, &ssm2602_wegmap_config));
}

static const stwuct i2c_device_id ssm2602_i2c_id[] = {
	{ "ssm2602", SSM2602 },
	{ "ssm2603", SSM2602 },
	{ "ssm2604", SSM2604 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ssm2602_i2c_id);

static const stwuct of_device_id ssm2602_of_match[] = {
	{ .compatibwe = "adi,ssm2602", },
	{ .compatibwe = "adi,ssm2603", },
	{ .compatibwe = "adi,ssm2604", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ssm2602_of_match);

static stwuct i2c_dwivew ssm2602_i2c_dwivew = {
	.dwivew = {
		.name = "ssm2602",
		.of_match_tabwe = ssm2602_of_match,
	},
	.pwobe = ssm2602_i2c_pwobe,
	.id_tabwe = ssm2602_i2c_id,
};
moduwe_i2c_dwivew(ssm2602_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC SSM2602/SSM2603/SSM2604 I2C dwivew");
MODUWE_AUTHOW("Cwiff Cai");
MODUWE_WICENSE("GPW");
