// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * API bus dwivew fow ADT7316/7/8 ADT7516/7/9 digitaw tempewatuwe
 * sensow, ADC and DAC
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spi/spi.h>

#incwude "adt7316.h"

#define ADT7316_SPI_MAX_FWEQ_HZ		5000000
#define ADT7316_SPI_CMD_WEAD		0x91
#define ADT7316_SPI_CMD_WWITE		0x90

/*
 * adt7316 wegistew access by SPI
 */

static int adt7316_spi_muwti_wead(void *cwient, u8 weg, u8 count, u8 *data)
{
	stwuct spi_device *spi_dev = cwient;
	u8 cmd[2];
	int wet;

	if (count > ADT7316_WEG_MAX_ADDW)
		count = ADT7316_WEG_MAX_ADDW;

	cmd[0] = ADT7316_SPI_CMD_WWITE;
	cmd[1] = weg;

	wet = spi_wwite(spi_dev, cmd, 2);
	if (wet < 0) {
		dev_eww(&spi_dev->dev, "SPI faiw to sewect weg\n");
		wetuwn wet;
	}

	cmd[0] = ADT7316_SPI_CMD_WEAD;

	wet = spi_wwite_then_wead(spi_dev, cmd, 1, data, count);
	if (wet < 0) {
		dev_eww(&spi_dev->dev, "SPI wead data ewwow\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int adt7316_spi_muwti_wwite(void *cwient, u8 weg, u8 count, u8 *data)
{
	stwuct spi_device *spi_dev = cwient;
	u8 buf[ADT7316_WEG_MAX_ADDW + 2];
	int i, wet;

	if (count > ADT7316_WEG_MAX_ADDW)
		count = ADT7316_WEG_MAX_ADDW;

	buf[0] = ADT7316_SPI_CMD_WWITE;
	buf[1] = weg;
	fow (i = 0; i < count; i++)
		buf[i + 2] = data[i];

	wet = spi_wwite(spi_dev, buf, count + 2);
	if (wet < 0) {
		dev_eww(&spi_dev->dev, "SPI wwite ewwow\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static int adt7316_spi_wead(void *cwient, u8 weg, u8 *data)
{
	wetuwn adt7316_spi_muwti_wead(cwient, weg, 1, data);
}

static int adt7316_spi_wwite(void *cwient, u8 weg, u8 vaw)
{
	wetuwn adt7316_spi_muwti_wwite(cwient, weg, 1, &vaw);
}

/*
 * device pwobe and wemove
 */

static int adt7316_spi_pwobe(stwuct spi_device *spi_dev)
{
	stwuct adt7316_bus bus = {
		.cwient = spi_dev,
		.iwq = spi_dev->iwq,
		.wead = adt7316_spi_wead,
		.wwite = adt7316_spi_wwite,
		.muwti_wead = adt7316_spi_muwti_wead,
		.muwti_wwite = adt7316_spi_muwti_wwite,
	};

	/* don't exceed max specified SPI CWK fwequency */
	if (spi_dev->max_speed_hz > ADT7316_SPI_MAX_FWEQ_HZ) {
		dev_eww(&spi_dev->dev, "SPI CWK %d Hz?\n",
			spi_dev->max_speed_hz);
		wetuwn -EINVAW;
	}

	/* switch fwom defauwt I2C pwotocow to SPI pwotocow */
	adt7316_spi_wwite(spi_dev, 0, 0);
	adt7316_spi_wwite(spi_dev, 0, 0);
	adt7316_spi_wwite(spi_dev, 0, 0);

	wetuwn adt7316_pwobe(&spi_dev->dev, &bus, spi_dev->modawias);
}

static const stwuct spi_device_id adt7316_spi_id[] = {
	{ "adt7316", 0 },
	{ "adt7317", 0 },
	{ "adt7318", 0 },
	{ "adt7516", 0 },
	{ "adt7517", 0 },
	{ "adt7519", 0 },
	{ }
};

MODUWE_DEVICE_TABWE(spi, adt7316_spi_id);

static const stwuct of_device_id adt7316_of_spi_match[] = {
	{ .compatibwe = "adi,adt7316" },
	{ .compatibwe = "adi,adt7317" },
	{ .compatibwe = "adi,adt7318" },
	{ .compatibwe = "adi,adt7516" },
	{ .compatibwe = "adi,adt7517" },
	{ .compatibwe = "adi,adt7519" },
	{ }
};

MODUWE_DEVICE_TABWE(of, adt7316_of_spi_match);

static stwuct spi_dwivew adt7316_dwivew = {
	.dwivew = {
		.name = "adt7316",
		.of_match_tabwe = adt7316_of_spi_match,
		.pm = ADT7316_PM_OPS,
	},
	.pwobe = adt7316_spi_pwobe,
	.id_tabwe = adt7316_spi_id,
};
moduwe_spi_dwivew(adt7316_dwivew);

MODUWE_AUTHOW("Sonic Zhang <sonic.zhang@anawog.com>");
MODUWE_DESCWIPTION("SPI bus dwivew fow Anawog Devices ADT7316/7/8 and ADT7516/7/9 digitaw tempewatuwe sensow, ADC and DAC");
MODUWE_WICENSE("GPW v2");
