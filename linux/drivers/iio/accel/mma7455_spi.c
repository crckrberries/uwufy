// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO accew SPI dwivew fow Fweescawe MMA7455W 3-axis 10-bit accewewometew
 * Copywight 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "mma7455.h"

static int mma7455_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &mma7455_cowe_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn mma7455_cowe_pwobe(&spi->dev, wegmap, id->name);
}

static void mma7455_spi_wemove(stwuct spi_device *spi)
{
	mma7455_cowe_wemove(&spi->dev);
}

static const stwuct spi_device_id mma7455_spi_ids[] = {
	{ "mma7455", 0 },
	{ "mma7456", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, mma7455_spi_ids);

static stwuct spi_dwivew mma7455_spi_dwivew = {
	.pwobe = mma7455_spi_pwobe,
	.wemove = mma7455_spi_wemove,
	.id_tabwe = mma7455_spi_ids,
	.dwivew = {
		.name = "mma7455-spi",
	},
};
moduwe_spi_dwivew(mma7455_spi_dwivew);

MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_DESCWIPTION("Fweescawe MMA7455W SPI accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_MMA7455);
