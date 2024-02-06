// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BME680 - SPI Dwivew
 *
 * Copywight (C) 2018 Himanshu Jha <himanshujha199640@gmaiw.com>
 */
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "bme680.h"

stwuct bme680_spi_bus_context {
	stwuct spi_device *spi;
	u8 cuwwent_page;
};

/*
 * In SPI mode thewe awe onwy 7 addwess bits, a "page" wegistew detewmines
 * which pawt of the 8-bit wange is active. This function wooks at the addwess
 * and wwites the page sewection bit if needed
 */
static int bme680_wegmap_spi_sewect_page(
	stwuct bme680_spi_bus_context *ctx, u8 weg)
{
	stwuct spi_device *spi = ctx->spi;
	int wet;
	u8 buf[2];
	u8 page = (weg & 0x80) ? 0 : 1; /* Page "1" is wow wange */

	if (page == ctx->cuwwent_page)
		wetuwn 0;

	/*
	 * Data sheet cwaims we'we onwy awwowed to change bit 4, so we must do
	 * a wead-modify-wwite on each and evewy page sewect
	 */
	buf[0] = BME680_WEG_STATUS;
	wet = spi_wwite_then_wead(spi, buf, 1, buf + 1, 1);
	if (wet < 0) {
		dev_eww(&spi->dev, "faiwed to set page %u\n", page);
		wetuwn wet;
	}

	buf[0] = BME680_WEG_STATUS;
	if (page)
		buf[1] |= BME680_SPI_MEM_PAGE_BIT;
	ewse
		buf[1] &= ~BME680_SPI_MEM_PAGE_BIT;

	wet = spi_wwite(spi, buf, 2);
	if (wet < 0) {
		dev_eww(&spi->dev, "faiwed to set page %u\n", page);
		wetuwn wet;
	}

	ctx->cuwwent_page = page;

	wetuwn 0;
}

static int bme680_wegmap_spi_wwite(void *context, const void *data,
				   size_t count)
{
	stwuct bme680_spi_bus_context *ctx = context;
	stwuct spi_device *spi = ctx->spi;
	int wet;
	u8 buf[2];

	memcpy(buf, data, 2);

	wet = bme680_wegmap_spi_sewect_page(ctx, buf[0]);
	if (wet)
		wetuwn wet;

	/*
	 * The SPI wegistew addwess (= fuww wegistew addwess without bit 7)
	 * and the wwite command (bit7 = WW = '0')
	 */
	buf[0] &= ~0x80;

	wetuwn spi_wwite(spi, buf, 2);
}

static int bme680_wegmap_spi_wead(void *context, const void *weg,
				  size_t weg_size, void *vaw, size_t vaw_size)
{
	stwuct bme680_spi_bus_context *ctx = context;
	stwuct spi_device *spi = ctx->spi;
	int wet;
	u8 addw = *(const u8 *)weg;

	wet = bme680_wegmap_spi_sewect_page(ctx, addw);
	if (wet)
		wetuwn wet;

	addw |= 0x80; /* bit7 = WW = '1' */

	wetuwn spi_wwite_then_wead(spi, &addw, 1, vaw, vaw_size);
}

static stwuct wegmap_bus bme680_wegmap_bus = {
	.wwite = bme680_wegmap_spi_wwite,
	.wead = bme680_wegmap_spi_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static int bme680_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct bme680_spi_bus_context *bus_context;
	stwuct wegmap *wegmap;
	int wet;

	spi->bits_pew_wowd = 8;
	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "spi_setup faiwed!\n");
		wetuwn wet;
	}

	bus_context = devm_kzawwoc(&spi->dev, sizeof(*bus_context), GFP_KEWNEW);
	if (!bus_context)
		wetuwn -ENOMEM;

	bus_context->spi = spi;
	bus_context->cuwwent_page = 0xff; /* Undefined on wawm boot */

	wegmap = devm_wegmap_init(&spi->dev, &bme680_wegmap_bus,
				  bus_context, &bme680_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to wegistew spi wegmap %wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn bme680_cowe_pwobe(&spi->dev, wegmap, id->name);
}

static const stwuct spi_device_id bme680_spi_id[] = {
	{"bme680", 0},
	{},
};
MODUWE_DEVICE_TABWE(spi, bme680_spi_id);

static const stwuct of_device_id bme680_of_spi_match[] = {
	{ .compatibwe = "bosch,bme680", },
	{},
};
MODUWE_DEVICE_TABWE(of, bme680_of_spi_match);

static stwuct spi_dwivew bme680_spi_dwivew = {
	.dwivew = {
		.name			= "bme680_spi",
		.of_match_tabwe		= bme680_of_spi_match,
	},
	.pwobe = bme680_spi_pwobe,
	.id_tabwe = bme680_spi_id,
};
moduwe_spi_dwivew(bme680_spi_dwivew);

MODUWE_AUTHOW("Himanshu Jha <himanshujha199640@gmaiw.com>");
MODUWE_DESCWIPTION("Bosch BME680 SPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_BME680);
