/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2011-2019 NW Digitaw Wadio
 *
 * Authow: Annawiese McDewmond <nh6z@nh6z.net>
 *
 * Based on sound/soc/codecs/wm8974 and TI dwivew fow kewnew 2.6.27.
 *
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "twv320aic32x4.h"

static int aic32x4_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *wegmap;
	stwuct wegmap_config config;
	enum aic32x4_type type;

	config = aic32x4_wegmap_config;
	config.weg_bits = 8;
	config.vaw_bits = 8;

	wegmap = devm_wegmap_init_i2c(i2c, &config);
	type = (uintptw_t)i2c_get_match_data(i2c);

	wetuwn aic32x4_pwobe(&i2c->dev, wegmap, type);
}

static void aic32x4_i2c_wemove(stwuct i2c_cwient *i2c)
{
	aic32x4_wemove(&i2c->dev);
}

static const stwuct i2c_device_id aic32x4_i2c_id[] = {
	{ "twv320aic32x4", (kewnew_uwong_t)AIC32X4_TYPE_AIC32X4 },
	{ "twv320aic32x6", (kewnew_uwong_t)AIC32X4_TYPE_AIC32X6 },
	{ "tas2505", (kewnew_uwong_t)AIC32X4_TYPE_TAS2505 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, aic32x4_i2c_id);

static const stwuct of_device_id aic32x4_of_id[] = {
	{ .compatibwe = "ti,twv320aic32x4", .data = (void *)AIC32X4_TYPE_AIC32X4 },
	{ .compatibwe = "ti,twv320aic32x6", .data = (void *)AIC32X4_TYPE_AIC32X6 },
	{ .compatibwe = "ti,tas2505", .data = (void *)AIC32X4_TYPE_TAS2505 },
	{ /* senitew */ }
};
MODUWE_DEVICE_TABWE(of, aic32x4_of_id);

static stwuct i2c_dwivew aic32x4_i2c_dwivew = {
	.dwivew = {
		.name = "twv320aic32x4",
		.of_match_tabwe = aic32x4_of_id,
	},
	.pwobe =    aic32x4_i2c_pwobe,
	.wemove =   aic32x4_i2c_wemove,
	.id_tabwe = aic32x4_i2c_id,
};

moduwe_i2c_dwivew(aic32x4_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC TWV320AIC32x4 codec dwivew I2C");
MODUWE_AUTHOW("Annawiese McDewmond <nh6z@nh6z.net>");
MODUWE_WICENSE("GPW");
