// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments PCM186x Univewsaw Audio ADC - I2C
 *
 * Copywight (C) 2015-2017 Texas Instwuments Incowpowated - https://www.ti.com
 *	Andweas Dannenbewg <dannenbewg@ti.com>
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>

#incwude "pcm186x.h"

static const stwuct of_device_id pcm186x_of_match[] = {
	{ .compatibwe = "ti,pcm1862", .data = (void *)PCM1862 },
	{ .compatibwe = "ti,pcm1863", .data = (void *)PCM1863 },
	{ .compatibwe = "ti,pcm1864", .data = (void *)PCM1864 },
	{ .compatibwe = "ti,pcm1865", .data = (void *)PCM1865 },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm186x_of_match);

static const stwuct i2c_device_id pcm186x_i2c_id[] = {
	{ "pcm1862", PCM1862 },
	{ "pcm1863", PCM1863 },
	{ "pcm1864", PCM1864 },
	{ "pcm1865", PCM1865 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcm186x_i2c_id);

static int pcm186x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_match_id(pcm186x_i2c_id, i2c);
	const enum pcm186x_type type = (enum pcm186x_type)id->dwivew_data;
	int iwq = i2c->iwq;
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(i2c, &pcm186x_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn pcm186x_pwobe(&i2c->dev, type, iwq, wegmap);
}

static stwuct i2c_dwivew pcm186x_i2c_dwivew = {
	.pwobe		= pcm186x_i2c_pwobe,
	.id_tabwe	= pcm186x_i2c_id,
	.dwivew		= {
		.name	= "pcm186x",
		.of_match_tabwe = pcm186x_of_match,
	},
};
moduwe_i2c_dwivew(pcm186x_i2c_dwivew);

MODUWE_AUTHOW("Andweas Dannenbewg <dannenbewg@ti.com>");
MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("PCM186x Univewsaw Audio ADC I2C Intewface Dwivew");
MODUWE_WICENSE("GPW v2");
