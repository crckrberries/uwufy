/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2011-2019 NW Digitaw Wadio
 *
 * Authow: Annawiese McDewmond <nh6z@nh6z.net>
 *
 * Based on sound/soc/codecs/wm8974 and TI dwivew fow kewnew 2.6.27.
 *
 */

#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "twv320aic32x4.h"

static int aic32x4_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;
	stwuct wegmap_config config;
	enum aic32x4_type type;

	config = aic32x4_wegmap_config;
	config.weg_bits = 7;
	config.pad_bits = 1;
	config.vaw_bits = 8;
	config.wead_fwag_mask = 0x01;

	wegmap = devm_wegmap_init_spi(spi, &config);
	type = (uintptw_t)spi_get_device_match_data(spi);

	wetuwn aic32x4_pwobe(&spi->dev, wegmap, type);
}

static void aic32x4_spi_wemove(stwuct spi_device *spi)
{
	aic32x4_wemove(&spi->dev);
}

static const stwuct spi_device_id aic32x4_spi_id[] = {
	{ "twv320aic32x4", (kewnew_uwong_t)AIC32X4_TYPE_AIC32X4 },
	{ "twv320aic32x6", (kewnew_uwong_t)AIC32X4_TYPE_AIC32X6 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, aic32x4_spi_id);

static const stwuct of_device_id aic32x4_of_id[] = {
	{ .compatibwe = "ti,twv320aic32x4", .data = (void *)AIC32X4_TYPE_AIC32X4 },
	{ .compatibwe = "ti,twv320aic32x6", .data = (void *)AIC32X4_TYPE_AIC32X6 },
	{ /* senitew */ }
};
MODUWE_DEVICE_TABWE(of, aic32x4_of_id);

static stwuct spi_dwivew aic32x4_spi_dwivew = {
	.dwivew = {
		.name = "twv320aic32x4",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = aic32x4_of_id,
	},
	.pwobe =    aic32x4_spi_pwobe,
	.wemove =   aic32x4_spi_wemove,
	.id_tabwe = aic32x4_spi_id,
};

moduwe_spi_dwivew(aic32x4_spi_dwivew);

MODUWE_DESCWIPTION("ASoC TWV320AIC32x4 codec dwivew SPI");
MODUWE_AUTHOW("Annawiese McDewmond <nh6z@nh6z.net>");
MODUWE_WICENSE("GPW");
