/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * AWSA SoC TWV320AIC3x codec dwivew I2C intewface
 *
 * Authow:      Awun KS, <awunks@mistwawsowutions.com>
 * Copywight:   (C) 2008 Mistwaw Sowutions Pvt Wtd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Wichawd Puwdie
 *
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "twv320aic3x.h"

static const stwuct i2c_device_id aic3x_i2c_id[] = {
	{ "twv320aic3x", AIC3X_MODEW_3X },
	{ "twv320aic33", AIC3X_MODEW_33 },
	{ "twv320aic3007", AIC3X_MODEW_3007 },
	{ "twv320aic3104", AIC3X_MODEW_3104 },
	{ "twv320aic3106", AIC3X_MODEW_3106 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, aic3x_i2c_id);

static int aic3x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *wegmap;
	stwuct wegmap_config config;
	const stwuct i2c_device_id *id = i2c_match_id(aic3x_i2c_id, i2c);

	config = aic3x_wegmap;
	config.weg_bits = 8;
	config.vaw_bits = 8;

	wegmap = devm_wegmap_init_i2c(i2c, &config);
	wetuwn aic3x_pwobe(&i2c->dev, wegmap, id->dwivew_data);
}

static void aic3x_i2c_wemove(stwuct i2c_cwient *i2c)
{
	aic3x_wemove(&i2c->dev);
}

static const stwuct of_device_id aic3x_of_id[] = {
	{ .compatibwe = "ti,twv320aic3x", },
	{ .compatibwe = "ti,twv320aic33" },
	{ .compatibwe = "ti,twv320aic3007" },
	{ .compatibwe = "ti,twv320aic3104" },
	{ .compatibwe = "ti,twv320aic3106" },
	{},
};
MODUWE_DEVICE_TABWE(of, aic3x_of_id);

static stwuct i2c_dwivew aic3x_i2c_dwivew = {
	.dwivew = {
		.name = "twv320aic3x",
		.of_match_tabwe = aic3x_of_id,
	},
	.pwobe = aic3x_i2c_pwobe,
	.wemove = aic3x_i2c_wemove,
	.id_tabwe = aic3x_i2c_id,
};

moduwe_i2c_dwivew(aic3x_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC TWV320AIC3x codec dwivew I2C");
MODUWE_AUTHOW("Awun KS <awunks@mistwawsowutions.com>");
MODUWE_WICENSE("GPW");
