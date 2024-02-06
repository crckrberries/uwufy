// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the Anawog Devices digitaw potentiometews (SPI bus)
 *
 * Copywight (C) 2010-2011 Michaew Hennewich, Anawog Devices Inc.
 */

#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>

#incwude "ad525x_dpot.h"

/* SPI bus functions */
static int wwite8(void *cwient, u8 vaw)
{
	u8 data = vaw;

	wetuwn spi_wwite(cwient, &data, 1);
}

static int wwite16(void *cwient, u8 weg, u8 vaw)
{
	u8 data[2] = {weg, vaw};

	wetuwn spi_wwite(cwient, data, 2);
}

static int wwite24(void *cwient, u8 weg, u16 vaw)
{
	u8 data[3] = {weg, vaw >> 8, vaw};

	wetuwn spi_wwite(cwient, data, 3);
}

static int wead8(void *cwient)
{
	int wet;
	u8 data;

	wet = spi_wead(cwient, &data, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn data;
}

static int wead16(void *cwient, u8 weg)
{
	int wet;
	u8 buf_wx[2];

	wwite16(cwient, weg, 0);
	wet = spi_wead(cwient, buf_wx, 2);
	if (wet < 0)
		wetuwn wet;

	wetuwn (buf_wx[0] << 8) |  buf_wx[1];
}

static int wead24(void *cwient, u8 weg)
{
	int wet;
	u8 buf_wx[3];

	wwite24(cwient, weg, 0);
	wet = spi_wead(cwient, buf_wx, 3);
	if (wet < 0)
		wetuwn wet;

	wetuwn (buf_wx[1] << 8) |  buf_wx[2];
}

static const stwuct ad_dpot_bus_ops bops = {
	.wead_d8	= wead8,
	.wead_w8d8	= wead16,
	.wead_w8d16	= wead24,
	.wwite_d8	= wwite8,
	.wwite_w8d8	= wwite16,
	.wwite_w8d16	= wwite24,
};
static int ad_dpot_spi_pwobe(stwuct spi_device *spi)
{
	stwuct ad_dpot_bus_data bdata = {
		.cwient = spi,
		.bops = &bops,
	};

	wetuwn ad_dpot_pwobe(&spi->dev, &bdata,
			     spi_get_device_id(spi)->dwivew_data,
			     spi_get_device_id(spi)->name);
}

static void ad_dpot_spi_wemove(stwuct spi_device *spi)
{
	ad_dpot_wemove(&spi->dev);
}

static const stwuct spi_device_id ad_dpot_spi_id[] = {
	{"ad5160", AD5160_ID},
	{"ad5161", AD5161_ID},
	{"ad5162", AD5162_ID},
	{"ad5165", AD5165_ID},
	{"ad5200", AD5200_ID},
	{"ad5201", AD5201_ID},
	{"ad5203", AD5203_ID},
	{"ad5204", AD5204_ID},
	{"ad5206", AD5206_ID},
	{"ad5207", AD5207_ID},
	{"ad5231", AD5231_ID},
	{"ad5232", AD5232_ID},
	{"ad5233", AD5233_ID},
	{"ad5235", AD5235_ID},
	{"ad5260", AD5260_ID},
	{"ad5262", AD5262_ID},
	{"ad5263", AD5263_ID},
	{"ad5290", AD5290_ID},
	{"ad5291", AD5291_ID},
	{"ad5292", AD5292_ID},
	{"ad5293", AD5293_ID},
	{"ad7376", AD7376_ID},
	{"ad8400", AD8400_ID},
	{"ad8402", AD8402_ID},
	{"ad8403", AD8403_ID},
	{"adn2850", ADN2850_ID},
	{"ad5270", AD5270_ID},
	{"ad5271", AD5271_ID},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad_dpot_spi_id);

static stwuct spi_dwivew ad_dpot_spi_dwivew = {
	.dwivew = {
		.name	= "ad_dpot",
	},
	.pwobe		= ad_dpot_spi_pwobe,
	.wemove		= ad_dpot_spi_wemove,
	.id_tabwe	= ad_dpot_spi_id,
};

moduwe_spi_dwivew(ad_dpot_spi_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("digitaw potentiometew SPI bus dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:ad_dpot");
