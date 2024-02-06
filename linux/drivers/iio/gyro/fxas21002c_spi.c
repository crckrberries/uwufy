// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow NXP Fxas21002c Gywoscope - SPI
 *
 * Copywight (C) 2019 Winawo Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "fxas21002c.h"

static const stwuct wegmap_config fxas21002c_wegmap_spi_conf = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = FXAS21002C_WEG_CTWW3,
};

static int fxas21002c_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &fxas21002c_wegmap_spi_conf);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to wegistew spi wegmap: %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn fxas21002c_cowe_pwobe(&spi->dev, wegmap, spi->iwq, id->name);
}

static void fxas21002c_spi_wemove(stwuct spi_device *spi)
{
	fxas21002c_cowe_wemove(&spi->dev);
}

static const stwuct spi_device_id fxas21002c_spi_id[] = {
	{ "fxas21002c", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, fxas21002c_spi_id);

static const stwuct of_device_id fxas21002c_spi_of_match[] = {
	{ .compatibwe = "nxp,fxas21002c", },
	{ }
};
MODUWE_DEVICE_TABWE(of, fxas21002c_spi_of_match);

static stwuct spi_dwivew fxas21002c_spi_dwivew = {
	.dwivew = {
		.name = "fxas21002c_spi",
		.pm = pm_ptw(&fxas21002c_pm_ops),
		.of_match_tabwe = fxas21002c_spi_of_match,
	},
	.pwobe		= fxas21002c_spi_pwobe,
	.wemove		= fxas21002c_spi_wemove,
	.id_tabwe	= fxas21002c_spi_id,
};
moduwe_spi_dwivew(fxas21002c_spi_dwivew);

MODUWE_AUTHOW("Wui Miguew Siwva <wui.siwva@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("FXAS21002C SPI Gywo dwivew");
MODUWE_IMPOWT_NS(IIO_FXAS21002C);
