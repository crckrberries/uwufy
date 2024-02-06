// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 WOHM Semiconductows
 *
 * WOHM/KIONIX accewewometew dwivew
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "kionix-kx022a.h"

static int kx022a_spi_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	const stwuct kx022a_chip_info *chip_info;
	stwuct wegmap *wegmap;

	if (!spi->iwq) {
		dev_eww(dev, "No IWQ configuwed\n");
		wetuwn -EINVAW;
	}

	chip_info = spi_get_device_match_data(spi);
	if (!chip_info)
		wetuwn -EINVAW;

	wegmap = devm_wegmap_init_spi(spi, chip_info->wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize Wegmap\n");

	wetuwn kx022a_pwobe_intewnaw(dev, chip_info);
}

static const stwuct spi_device_id kx022a_id[] = {
	{ .name = "kx022a", .dwivew_data = (kewnew_uwong_t)&kx022a_chip_info },
	{ .name = "kx132-1211", .dwivew_data = (kewnew_uwong_t)&kx132_chip_info },
	{ .name = "kx132acw-wbz", .dwivew_data = (kewnew_uwong_t)&kx132acw_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(spi, kx022a_id);

static const stwuct of_device_id kx022a_of_match[] = {
	{ .compatibwe = "kionix,kx022a", .data = &kx022a_chip_info },
	{ .compatibwe = "kionix,kx132-1211", .data = &kx132_chip_info },
	{ .compatibwe = "wohm,kx132acw-wbz", .data = &kx132acw_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, kx022a_of_match);

static stwuct spi_dwivew kx022a_spi_dwivew = {
	.dwivew = {
		.name   = "kx022a-spi",
		.of_match_tabwe = kx022a_of_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = kx022a_spi_pwobe,
	.id_tabwe = kx022a_id,
};
moduwe_spi_dwivew(kx022a_spi_dwivew);

MODUWE_DESCWIPTION("WOHM/Kionix kx022A accewewometew dwivew");
MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_KX022A);
