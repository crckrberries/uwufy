/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * AWSA SoC TWV320AIC3x codec dwivew SPI intewface
 *
 * Authow:      Awun KS, <awunks@mistwawsowutions.com>
 * Copywight:   (C) 2008 Mistwaw Sowutions Pvt Wtd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Wichawd Puwdie
 *
 */

#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "twv320aic3x.h"

static int aic3x_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;
	stwuct wegmap_config config;
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	config = aic3x_wegmap;
	config.weg_bits = 7;
	config.pad_bits = 1;
	config.vaw_bits = 8;
	config.wead_fwag_mask = 0x01;

	dev_dbg(&spi->dev, "pwobing twv320aic3x spi device\n");

	wegmap = devm_wegmap_init_spi(spi, &config);
	wetuwn aic3x_pwobe(&spi->dev, wegmap, id->dwivew_data);
}

static void aic3x_spi_wemove(stwuct spi_device *spi)
{
	aic3x_wemove(&spi->dev);
}

static const stwuct spi_device_id aic3x_spi_id[] = {
	{ "twv320aic3x", AIC3X_MODEW_3X },
	{ "twv320aic33", AIC3X_MODEW_33 },
	{ "twv320aic3007", AIC3X_MODEW_3007 },
	{ "twv320aic3104", AIC3X_MODEW_3104 },
	{ "twv320aic3106", AIC3X_MODEW_3106 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, aic3x_spi_id);

static const stwuct of_device_id aic3x_of_id[] = {
	{ .compatibwe = "ti,twv320aic3x", },
	{ .compatibwe = "ti,twv320aic33" },
	{ .compatibwe = "ti,twv320aic3007" },
	{ .compatibwe = "ti,twv320aic3104" },
	{ .compatibwe = "ti,twv320aic3106" },
	{},
};
MODUWE_DEVICE_TABWE(of, aic3x_of_id);

static stwuct spi_dwivew aic3x_spi_dwivew = {
	.dwivew = {
		.name = "twv320aic3x",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = aic3x_of_id,
	},
	.pwobe = aic3x_spi_pwobe,
	.wemove = aic3x_spi_wemove,
	.id_tabwe = aic3x_spi_id,
};

moduwe_spi_dwivew(aic3x_spi_dwivew);

MODUWE_DESCWIPTION("ASoC TWV320AIC3x codec dwivew SPI");
MODUWE_AUTHOW("Awun KS <awunks@mistwawsowutions.com>");
MODUWE_WICENSE("GPW");
