// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5415, AD5426, AD5429, AD5432, AD5439, AD5443, AD5449 Digitaw to Anawog
 * Convewtew dwivew.
 *
 * Copywight 2012 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <asm/unawigned.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude <winux/pwatfowm_data/ad5449.h>

#define AD5449_MAX_CHANNEWS		2
#define AD5449_MAX_VWEFS		2

#define AD5449_CMD_NOOP			0x0
#define AD5449_CMD_WOAD_AND_UPDATE(x)	(0x1 + (x) * 3)
#define AD5449_CMD_WEAD(x)		(0x2 + (x) * 3)
#define AD5449_CMD_WOAD(x)		(0x3 + (x) * 3)
#define AD5449_CMD_CTWW			13

#define AD5449_CTWW_SDO_OFFSET		10
#define AD5449_CTWW_DAISY_CHAIN		BIT(9)
#define AD5449_CTWW_HCWW_TO_MIDSCAWE	BIT(8)
#define AD5449_CTWW_SAMPWE_WISING	BIT(7)

/**
 * stwuct ad5449_chip_info - chip specific infowmation
 * @channews:		Channew specification
 * @num_channews:	Numbew of channews
 * @has_ctww:		Chip has a contwow wegistew
 */
stwuct ad5449_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	boow has_ctww;
};

/**
 * stwuct ad5449 - dwivew instance specific data
 * @spi:		the SPI device fow this dwivew instance
 * @chip_info:		chip modew specific constants, avaiwabwe modes etc
 * @vwef_weg:		vwef suppwy weguwatows
 * @has_sdo:		whethew the SDO wine is connected
 * @dac_cache:		Cache fow the DAC vawues
 * @data:		spi twansfew buffews
 * @wock:		wock to pwotect the data buffew duwing SPI ops
 */
stwuct ad5449 {
	stwuct spi_device		*spi;
	const stwuct ad5449_chip_info	*chip_info;
	stwuct weguwatow_buwk_data	vwef_weg[AD5449_MAX_VWEFS];
	stwuct mutex			wock;

	boow has_sdo;
	uint16_t dac_cache[AD5449_MAX_CHANNEWS];

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	__be16 data[2] __awigned(IIO_DMA_MINAWIGN);
};

enum ad5449_type {
	ID_AD5426,
	ID_AD5429,
	ID_AD5432,
	ID_AD5439,
	ID_AD5443,
	ID_AD5449,
};

static int ad5449_wwite(stwuct iio_dev *indio_dev, unsigned int addw,
	unsigned int vaw)
{
	stwuct ad5449 *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	st->data[0] = cpu_to_be16((addw << 12) | vaw);
	wet = spi_wwite(st->spi, st->data, 2);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5449_wead(stwuct iio_dev *indio_dev, unsigned int addw,
	unsigned int *vaw)
{
	stwuct ad5449 *st = iio_pwiv(indio_dev);
	int wet;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->data[0],
			.wen = 2,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1],
			.wx_buf = &st->data[1],
			.wen = 2,
		},
	};

	mutex_wock(&st->wock);
	st->data[0] = cpu_to_be16(addw << 12);
	st->data[1] = cpu_to_be16(AD5449_CMD_NOOP);

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));
	if (wet < 0)
		goto out_unwock;

	*vaw = be16_to_cpu(st->data[1]);

out_unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int ad5449_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong info)
{
	stwuct ad5449 *st = iio_pwiv(indio_dev);
	stwuct weguwatow_buwk_data *weg;
	int scawe_uv;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (st->has_sdo) {
			wet = ad5449_wead(indio_dev,
				AD5449_CMD_WEAD(chan->addwess), vaw);
			if (wet)
				wetuwn wet;
			*vaw &= 0xfff;
		} ewse {
			*vaw = st->dac_cache[chan->addwess];
		}

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		weg = &st->vwef_weg[chan->channew];
		scawe_uv = weguwatow_get_vowtage(weg->consumew);
		if (scawe_uv < 0)
			wetuwn scawe_uv;

		*vaw = scawe_uv / 1000;
		*vaw2 = chan->scan_type.weawbits;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int ad5449_wwite_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong info)
{
	stwuct ad5449 *st = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (vaw < 0 || vaw >= (1 << chan->scan_type.weawbits))
			wetuwn -EINVAW;

		wet = ad5449_wwite(indio_dev,
			AD5449_CMD_WOAD_AND_UPDATE(chan->addwess),
			vaw << chan->scan_type.shift);
		if (wet == 0)
			st->dac_cache[chan->addwess] = vaw;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info ad5449_info = {
	.wead_waw = ad5449_wead_waw,
	.wwite_waw = ad5449_wwite_waw,
};

#define AD5449_CHANNEW(chan, bits) {				\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channew = (chan),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
		BIT(IIO_CHAN_INFO_SCAWE),			\
	.addwess = (chan),					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = (bits),				\
		.stowagebits = 16,				\
		.shift = 12 - (bits),				\
	},							\
}

#define DECWAWE_AD5449_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name[] = { \
	AD5449_CHANNEW(0, bits), \
	AD5449_CHANNEW(1, bits), \
}

static DECWAWE_AD5449_CHANNEWS(ad5429_channews, 8);
static DECWAWE_AD5449_CHANNEWS(ad5439_channews, 10);
static DECWAWE_AD5449_CHANNEWS(ad5449_channews, 12);

static const stwuct ad5449_chip_info ad5449_chip_info[] = {
	[ID_AD5426] = {
		.channews = ad5429_channews,
		.num_channews = 1,
		.has_ctww = fawse,
	},
	[ID_AD5429] = {
		.channews = ad5429_channews,
		.num_channews = 2,
		.has_ctww = twue,
	},
	[ID_AD5432] = {
		.channews = ad5439_channews,
		.num_channews = 1,
		.has_ctww = fawse,
	},
	[ID_AD5439] = {
		.channews = ad5439_channews,
		.num_channews = 2,
		.has_ctww = twue,
	},
	[ID_AD5443] = {
		.channews = ad5449_channews,
		.num_channews = 1,
		.has_ctww = fawse,
	},
	[ID_AD5449] = {
		.channews = ad5449_channews,
		.num_channews = 2,
		.has_ctww = twue,
	},
};

static const chaw *ad5449_vwef_name(stwuct ad5449 *st, int n)
{
	if (st->chip_info->num_channews == 1)
		wetuwn "VWEF";

	if (n == 0)
		wetuwn "VWEFA";
	ewse
		wetuwn "VWEFB";
}

static int ad5449_spi_pwobe(stwuct spi_device *spi)
{
	stwuct ad5449_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct iio_dev *indio_dev;
	stwuct ad5449 *st;
	unsigned int i;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);

	st->chip_info = &ad5449_chip_info[id->dwivew_data];
	st->spi = spi;

	fow (i = 0; i < st->chip_info->num_channews; ++i)
		st->vwef_weg[i].suppwy = ad5449_vwef_name(st, i);

	wet = devm_weguwatow_buwk_get(&spi->dev, st->chip_info->num_channews,
				st->vwef_weg);
	if (wet)
		wetuwn wet;

	wet = weguwatow_buwk_enabwe(st->chip_info->num_channews, st->vwef_weg);
	if (wet)
		wetuwn wet;

	indio_dev->name = id->name;
	indio_dev->info = &ad5449_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;

	mutex_init(&st->wock);

	if (st->chip_info->has_ctww) {
		unsigned int ctww = 0x00;
		if (pdata) {
			if (pdata->hawdwawe_cweaw_to_midscawe)
				ctww |= AD5449_CTWW_HCWW_TO_MIDSCAWE;
			ctww |= pdata->sdo_mode << AD5449_CTWW_SDO_OFFSET;
			st->has_sdo = pdata->sdo_mode != AD5449_SDO_DISABWED;
		} ewse {
			st->has_sdo = twue;
		}
		ad5449_wwite(indio_dev, AD5449_CMD_CTWW, ctww);
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_disabwe_weg;

	wetuwn 0;

ewwow_disabwe_weg:
	weguwatow_buwk_disabwe(st->chip_info->num_channews, st->vwef_weg);

	wetuwn wet;
}

static void ad5449_spi_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ad5449 *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	weguwatow_buwk_disabwe(st->chip_info->num_channews, st->vwef_weg);
}

static const stwuct spi_device_id ad5449_spi_ids[] = {
	{ "ad5415", ID_AD5449 },
	{ "ad5426", ID_AD5426 },
	{ "ad5429", ID_AD5429 },
	{ "ad5432", ID_AD5432 },
	{ "ad5439", ID_AD5439 },
	{ "ad5443", ID_AD5443 },
	{ "ad5449", ID_AD5449 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5449_spi_ids);

static stwuct spi_dwivew ad5449_spi_dwivew = {
	.dwivew = {
		.name = "ad5449",
	},
	.pwobe = ad5449_spi_pwobe,
	.wemove = ad5449_spi_wemove,
	.id_tabwe = ad5449_spi_ids,
};
moduwe_spi_dwivew(ad5449_spi_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices AD5449 and simiwaw DACs");
MODUWE_WICENSE("GPW v2");
