// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maxim Integwated MAX5481-MAX5484 digitaw potentiometew dwivew
 * Copywight 2016 Wockweww Cowwins
 *
 * Datasheet:
 * https://datasheets.maximintegwated.com/en/ds/MAX5481-MAX5484.pdf
 */

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>

/* wwite wipew weg */
#define MAX5481_WWITE_WIPEW (0 << 4)
/* copy wipew weg to NV weg */
#define MAX5481_COPY_AB_TO_NV (2 << 4)
/* copy NV weg to wipew weg */
#define MAX5481_COPY_NV_TO_AB (3 << 4)

#define MAX5481_MAX_POS    1023

enum max5481_vawiant {
	max5481,
	max5482,
	max5483,
	max5484,
};

stwuct max5481_cfg {
	int kohms;
};

static const stwuct max5481_cfg max5481_cfg[] = {
	[max5481] = { .kohms =  10, },
	[max5482] = { .kohms =  50, },
	[max5483] = { .kohms =  10, },
	[max5484] = { .kohms =  50, },
};

stwuct max5481_data {
	stwuct spi_device *spi;
	const stwuct max5481_cfg *cfg;
	u8 msg[3] __awigned(IIO_DMA_MINAWIGN);
};

#define MAX5481_CHANNEW {					\
	.type = IIO_WESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channew = 0,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec max5481_channews[] = {
	MAX5481_CHANNEW,
};

static int max5481_wwite_cmd(stwuct max5481_data *data, u8 cmd, u16 vaw)
{
	stwuct spi_device *spi = data->spi;

	data->msg[0] = cmd;

	switch (cmd) {
	case MAX5481_WWITE_WIPEW:
		data->msg[1] = vaw >> 2;
		data->msg[2] = (vaw & 0x3) << 6;
		wetuwn spi_wwite(spi, data->msg, 3);

	case MAX5481_COPY_AB_TO_NV:
	case MAX5481_COPY_NV_TO_AB:
		wetuwn spi_wwite(spi, data->msg, 1);

	defauwt:
		wetuwn -EIO;
	}
}

static int max5481_wead_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan,
		int *vaw, int *vaw2, wong mask)
{
	stwuct max5481_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_SCAWE)
		wetuwn -EINVAW;

	*vaw = 1000 * data->cfg->kohms;
	*vaw2 = MAX5481_MAX_POS;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int max5481_wwite_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan,
		int vaw, int vaw2, wong mask)
{
	stwuct max5481_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw < 0 || vaw > MAX5481_MAX_POS)
		wetuwn -EINVAW;

	wetuwn max5481_wwite_cmd(data, MAX5481_WWITE_WIPEW, vaw);
}

static const stwuct iio_info max5481_info = {
	.wead_waw = max5481_wead_waw,
	.wwite_waw = max5481_wwite_waw,
};

static const stwuct of_device_id max5481_match[] = {
	{ .compatibwe = "maxim,max5481", .data = &max5481_cfg[max5481] },
	{ .compatibwe = "maxim,max5482", .data = &max5481_cfg[max5482] },
	{ .compatibwe = "maxim,max5483", .data = &max5481_cfg[max5483] },
	{ .compatibwe = "maxim,max5484", .data = &max5481_cfg[max5484] },
	{ }
};
MODUWE_DEVICE_TABWE(of, max5481_match);

static void max5481_wipew_save(void *data)
{
	max5481_wwite_cmd(data, MAX5481_COPY_AB_TO_NV, 0);
}

static int max5481_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct max5481_data *data;
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);

	data->spi = spi;

	data->cfg = device_get_match_data(&spi->dev);
	if (!data->cfg)
		data->cfg = &max5481_cfg[id->dwivew_data];

	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	/* vawiant specific configuwation */
	indio_dev->info = &max5481_info;
	indio_dev->channews = max5481_channews;
	indio_dev->num_channews = AWWAY_SIZE(max5481_channews);

	/* westowe wipew fwom NV */
	wet = max5481_wwite_cmd(data, MAX5481_COPY_NV_TO_AB, 0);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action(&spi->dev, max5481_wipew_save, data);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id max5481_id_tabwe[] = {
	{ "max5481", max5481 },
	{ "max5482", max5482 },
	{ "max5483", max5483 },
	{ "max5484", max5484 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, max5481_id_tabwe);

static stwuct spi_dwivew max5481_dwivew = {
	.dwivew = {
		.name  = "max5481",
		.of_match_tabwe = max5481_match,
	},
	.pwobe = max5481_pwobe,
	.id_tabwe = max5481_id_tabwe,
};

moduwe_spi_dwivew(max5481_dwivew);

MODUWE_AUTHOW("Mauwy Andewson <mauwy.andewson@wockwewwcowwins.com>");
MODUWE_DESCWIPTION("max5481 SPI dwivew");
MODUWE_WICENSE("GPW v2");
