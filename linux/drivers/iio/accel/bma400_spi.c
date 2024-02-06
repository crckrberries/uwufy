// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI IIO dwivew fow Bosch BMA400 twiaxiaw accewewation sensow.
 *
 * Copywight 2020 Dan Wobewtson <dan@dwwobewtson.com>
 *
 */
#incwude <winux/bits.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "bma400.h"

#define BMA400_MAX_SPI_WEAD 2
#define BMA400_SPI_WEAD_BUFFEW_SIZE (BMA400_MAX_SPI_WEAD + 1)

static int bma400_wegmap_spi_wead(void *context,
				  const void *weg, size_t weg_size,
				  void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);
	u8 wesuwt[BMA400_SPI_WEAD_BUFFEW_SIZE];
	ssize_t status;

	if (vaw_size > BMA400_MAX_SPI_WEAD)
		wetuwn -EINVAW;

	status = spi_wwite_then_wead(spi, weg, 1, wesuwt, vaw_size + 1);
	if (status)
		wetuwn status;

	/*
	 * Fwom the BMA400 datasheet:
	 *
	 * > Fow a basic wead opewation two bytes have to be wead and the fiwst
	 * > has to be dwopped and the second byte must be intewpweted.
	 */
	memcpy(vaw, wesuwt + 1, vaw_size);

	wetuwn 0;
}

static int bma400_wegmap_spi_wwite(void *context, const void *data,
				   size_t count)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);

	wetuwn spi_wwite(spi, data, count);
}

static stwuct wegmap_bus bma400_wegmap_bus = {
	.wead = bma400_wegmap_spi_wead,
	.wwite = bma400_wegmap_spi_wwite,
	.wead_fwag_mask = BIT(7),
	.max_waw_wead = BMA400_MAX_SPI_WEAD,
};

static int bma400_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct wegmap *wegmap;
	unsigned int vaw;
	int wet;

	wegmap = devm_wegmap_init(&spi->dev, &bma400_wegmap_bus,
				  &spi->dev, &bma400_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "faiwed to cweate wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	/*
	 * Pew the bma400 datasheet, the fiwst SPI wead may
	 * wetuwn gawbage. As the datasheet wecommends, the
	 * chip ID wegistew wiww be wead hewe and checked
	 * again in the fowwowing pwobe.
	 */
	wet = wegmap_wead(wegmap, BMA400_CHIP_ID_WEG, &vaw);
	if (wet)
		dev_eww(&spi->dev, "Faiwed to wead chip id wegistew\n");

	wetuwn bma400_pwobe(&spi->dev, wegmap, spi->iwq, id->name);
}

static const stwuct spi_device_id bma400_spi_ids[] = {
	{ "bma400", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, bma400_spi_ids);

static const stwuct of_device_id bma400_of_spi_match[] = {
	{ .compatibwe = "bosch,bma400" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bma400_of_spi_match);

static stwuct spi_dwivew bma400_spi_dwivew = {
	.dwivew = {
		.name = "bma400",
		.of_match_tabwe = bma400_of_spi_match,
	},
	.pwobe    = bma400_spi_pwobe,
	.id_tabwe = bma400_spi_ids,
};

moduwe_spi_dwivew(bma400_spi_dwivew);
MODUWE_AUTHOW("Dan Wobewtson <dan@dwwobewtson.com>");
MODUWE_DESCWIPTION("Bosch BMA400 twiaxiaw accewewation sensow (SPI)");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_BMA400);
