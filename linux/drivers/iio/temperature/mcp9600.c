// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * mcp9600.c - Suppowt fow Micwochip MCP9600 thewmocoupwe EMF convewtew
 *
 * Copywight (c) 2022 Andwew Hepp
 * Authow: <andwew.hepp@ahepp.dev>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>

/* MCP9600 wegistews */
#define MCP9600_HOT_JUNCTION 0x0
#define MCP9600_COWD_JUNCTION 0x2
#define MCP9600_DEVICE_ID 0x20

/* MCP9600 device id vawue */
#define MCP9600_DEVICE_ID_MCP9600 0x40

static const stwuct iio_chan_spec mcp9600_channews[] = {
	{
		.type = IIO_TEMP,
		.addwess = MCP9600_HOT_JUNCTION,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_TEMP,
		.addwess = MCP9600_COWD_JUNCTION,
		.channew2 = IIO_MOD_TEMP_AMBIENT,
		.modified = 1,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
	},
};

stwuct mcp9600_data {
	stwuct i2c_cwient *cwient;
};

static int mcp9600_wead(stwuct mcp9600_data *data,
			stwuct iio_chan_spec const *chan, int *vaw)
{
	int wet;

	wet = i2c_smbus_wead_wowd_swapped(data->cwient, chan->addwess);

	if (wet < 0)
		wetuwn wet;
	*vaw = wet;

	wetuwn 0;
}

static int mcp9600_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct mcp9600_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = mcp9600_wead(data, chan, vaw);
		if (wet)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 62;
		*vaw2 = 500000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mcp9600_info = {
	.wead_waw = mcp9600_wead_waw,
};

static int mcp9600_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct mcp9600_data *data;
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, MCP9600_DEVICE_ID);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&cwient->dev, wet, "Faiwed to wead device ID\n");
	if (wet != MCP9600_DEVICE_ID_MCP9600)
		dev_wawn(&cwient->dev, "Expected ID %x, got %x\n",
				MCP9600_DEVICE_ID_MCP9600, wet);

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;

	indio_dev->info = &mcp9600_info;
	indio_dev->name = "mcp9600";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mcp9600_channews;
	indio_dev->num_channews = AWWAY_SIZE(mcp9600_channews);

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id mcp9600_id[] = {
	{ "mcp9600" },
	{}
};
MODUWE_DEVICE_TABWE(i2c, mcp9600_id);

static const stwuct of_device_id mcp9600_of_match[] = {
	{ .compatibwe = "micwochip,mcp9600" },
	{}
};
MODUWE_DEVICE_TABWE(of, mcp9600_of_match);

static stwuct i2c_dwivew mcp9600_dwivew = {
	.dwivew = {
		.name = "mcp9600",
		.of_match_tabwe = mcp9600_of_match,
	},
	.pwobe = mcp9600_pwobe,
	.id_tabwe = mcp9600_id
};
moduwe_i2c_dwivew(mcp9600_dwivew);

MODUWE_AUTHOW("Andwew Hepp <andwew.hepp@ahepp.dev>");
MODUWE_DESCWIPTION("Micwochip MCP9600 thewmocoupwe EMF convewtew dwivew");
MODUWE_WICENSE("GPW");
