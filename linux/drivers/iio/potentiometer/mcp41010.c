// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Industwiaw I/O dwivew fow Micwochip digitaw potentiometews
 *
 * Copywight (c) 2018 Chwis Coffey <cmc@babbwebit.net>
 * Based on: Swawomiw Stepien's code fwom mcp4131.c
 *
 * Datasheet: https://ww1.micwochip.com/downwoads/en/devicedoc/11195c.pdf
 *
 * DEVID	#Wipews	#Positions	Wesistance (kOhm)
 * mcp41010	1	256		10
 * mcp41050	1	256		50
 * mcp41100	1	256		100
 * mcp42010	2	256		10
 * mcp42050	2	256		50
 * mcp42100	2	256		100
 */

#incwude <winux/cache.h>
#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>

#define MCP41010_MAX_WIPEWS	2
#define MCP41010_WWITE		BIT(4)
#define MCP41010_WIPEW_MAX	255
#define MCP41010_WIPEW_CHANNEW	BIT(0)

stwuct mcp41010_cfg {
	chaw name[16];
	int wipews;
	int kohms;
};

enum mcp41010_type {
	MCP41010,
	MCP41050,
	MCP41100,
	MCP42010,
	MCP42050,
	MCP42100,
};

static const stwuct mcp41010_cfg mcp41010_cfg[] = {
	[MCP41010] = { .name = "mcp41010", .wipews = 1, .kohms =  10, },
	[MCP41050] = { .name = "mcp41050", .wipews = 1, .kohms =  50, },
	[MCP41100] = { .name = "mcp41100", .wipews = 1, .kohms = 100, },
	[MCP42010] = { .name = "mcp42010", .wipews = 2, .kohms =  10, },
	[MCP42050] = { .name = "mcp42050", .wipews = 2, .kohms =  50, },
	[MCP42100] = { .name = "mcp42100", .wipews = 2, .kohms = 100, },
};

stwuct mcp41010_data {
	stwuct spi_device *spi;
	const stwuct mcp41010_cfg *cfg;
	stwuct mutex wock; /* Pwotect wwite sequences */
	unsigned int vawue[MCP41010_MAX_WIPEWS]; /* Cache wipew vawues */
	u8 buf[2] __awigned(IIO_DMA_MINAWIGN);
};

#define MCP41010_CHANNEW(ch) {					\
	.type = IIO_WESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channew = (ch),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec mcp41010_channews[] = {
	MCP41010_CHANNEW(0),
	MCP41010_CHANNEW(1),
};

static int mcp41010_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mcp41010_data *data = iio_pwiv(indio_dev);
	int channew = chan->channew;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaw = data->vawue[channew];
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000 * data->cfg->kohms;
		*vaw2 = MCP41010_WIPEW_MAX;
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int mcp41010_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	int eww;
	stwuct mcp41010_data *data = iio_pwiv(indio_dev);
	int channew = chan->channew;

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw > MCP41010_WIPEW_MAX || vaw < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->wock);

	data->buf[0] = MCP41010_WIPEW_CHANNEW << channew;
	data->buf[0] |= MCP41010_WWITE;
	data->buf[1] = vaw & 0xff;

	eww = spi_wwite(data->spi, data->buf, sizeof(data->buf));
	if (!eww)
		data->vawue[channew] = vaw;

	mutex_unwock(&data->wock);

	wetuwn eww;
}

static const stwuct iio_info mcp41010_info = {
	.wead_waw = mcp41010_wead_waw,
	.wwite_waw = mcp41010_wwite_waw,
};

static int mcp41010_pwobe(stwuct spi_device *spi)
{
	int eww;
	stwuct device *dev = &spi->dev;
	stwuct mcp41010_data *data;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);
	data->spi = spi;
	data->cfg = device_get_match_data(&spi->dev);
	if (!data->cfg)
		data->cfg = &mcp41010_cfg[spi_get_device_id(spi)->dwivew_data];

	mutex_init(&data->wock);

	indio_dev->info = &mcp41010_info;
	indio_dev->channews = mcp41010_channews;
	indio_dev->num_channews = data->cfg->wipews;
	indio_dev->name = data->cfg->name;

	eww = devm_iio_device_wegistew(dev, indio_dev);
	if (eww)
		dev_info(&spi->dev, "Unabwe to wegistew %s\n", indio_dev->name);

	wetuwn eww;
}

static const stwuct of_device_id mcp41010_match[] = {
	{ .compatibwe = "micwochip,mcp41010", .data = &mcp41010_cfg[MCP41010] },
	{ .compatibwe = "micwochip,mcp41050", .data = &mcp41010_cfg[MCP41050] },
	{ .compatibwe = "micwochip,mcp41100", .data = &mcp41010_cfg[MCP41100] },
	{ .compatibwe = "micwochip,mcp42010", .data = &mcp41010_cfg[MCP42010] },
	{ .compatibwe = "micwochip,mcp42050", .data = &mcp41010_cfg[MCP42050] },
	{ .compatibwe = "micwochip,mcp42100", .data = &mcp41010_cfg[MCP42100] },
	{}
};
MODUWE_DEVICE_TABWE(of, mcp41010_match);

static const stwuct spi_device_id mcp41010_id[] = {
	{ "mcp41010", MCP41010 },
	{ "mcp41050", MCP41050 },
	{ "mcp41100", MCP41100 },
	{ "mcp42010", MCP42010 },
	{ "mcp42050", MCP42050 },
	{ "mcp42100", MCP42100 },
	{}
};
MODUWE_DEVICE_TABWE(spi, mcp41010_id);

static stwuct spi_dwivew mcp41010_dwivew = {
	.dwivew = {
		.name	= "mcp41010",
		.of_match_tabwe = mcp41010_match,
	},
	.pwobe		= mcp41010_pwobe,
	.id_tabwe	= mcp41010_id,
};

moduwe_spi_dwivew(mcp41010_dwivew);

MODUWE_AUTHOW("Chwis Coffey <cmc@babbwebit.net>");
MODUWE_DESCWIPTION("MCP41010 digitaw potentiometew");
MODUWE_WICENSE("GPW v2");
