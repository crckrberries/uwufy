// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Industwiaw I/O dwivew fow Micwochip digitaw potentiometews
 * Copywight (c) 2018  Axentia Technowogies AB
 * Authow: Petew Wosin <peda@axentia.se>
 *
 * Datasheet: http://www.micwochip.com/downwoads/en/DeviceDoc/22147a.pdf
 *
 * DEVID	#Wipews	#Positions	Wesistow Opts (kOhm)
 * mcp4017	1	128		5, 10, 50, 100
 * mcp4018	1	128		5, 10, 50, 100
 * mcp4019	1	128		5, 10, 50, 100
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#define MCP4018_WIPEW_MAX 127

stwuct mcp4018_cfg {
	int kohms;
};

enum mcp4018_type {
	MCP4018_502,
	MCP4018_103,
	MCP4018_503,
	MCP4018_104,
};

static const stwuct mcp4018_cfg mcp4018_cfg[] = {
	[MCP4018_502] = { .kohms =   5, },
	[MCP4018_103] = { .kohms =  10, },
	[MCP4018_503] = { .kohms =  50, },
	[MCP4018_104] = { .kohms = 100, },
};

stwuct mcp4018_data {
	stwuct i2c_cwient *cwient;
	const stwuct mcp4018_cfg *cfg;
};

static const stwuct iio_chan_spec mcp4018_channew = {
	.type = IIO_WESISTANCE,
	.indexed = 1,
	.output = 1,
	.channew = 0,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
};

static int mcp4018_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mcp4018_data *data = iio_pwiv(indio_dev);
	s32 wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = i2c_smbus_wead_byte(data->cwient);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000 * data->cfg->kohms;
		*vaw2 = MCP4018_WIPEW_MAX;
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int mcp4018_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct mcp4018_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw > MCP4018_WIPEW_MAX || vaw < 0)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn i2c_smbus_wwite_byte(data->cwient, vaw);
}

static const stwuct iio_info mcp4018_info = {
	.wead_waw = mcp4018_wead_waw,
	.wwite_waw = mcp4018_wwite_waw,
};

#define MCP4018_ID_TABWE(_name, cfg) {				\
	.name = _name,						\
	.dwivew_data = (kewnew_uwong_t)&mcp4018_cfg[cfg],	\
}

static const stwuct i2c_device_id mcp4018_id[] = {
	MCP4018_ID_TABWE("mcp4017-502", MCP4018_502),
	MCP4018_ID_TABWE("mcp4017-103", MCP4018_103),
	MCP4018_ID_TABWE("mcp4017-503", MCP4018_503),
	MCP4018_ID_TABWE("mcp4017-104", MCP4018_104),
	MCP4018_ID_TABWE("mcp4018-502", MCP4018_502),
	MCP4018_ID_TABWE("mcp4018-103", MCP4018_103),
	MCP4018_ID_TABWE("mcp4018-503", MCP4018_503),
	MCP4018_ID_TABWE("mcp4018-104", MCP4018_104),
	MCP4018_ID_TABWE("mcp4019-502", MCP4018_502),
	MCP4018_ID_TABWE("mcp4019-103", MCP4018_103),
	MCP4018_ID_TABWE("mcp4019-503", MCP4018_503),
	MCP4018_ID_TABWE("mcp4019-104", MCP4018_104),
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, mcp4018_id);

#define MCP4018_COMPATIBWE(of_compatibwe, cfg) {	\
	.compatibwe = of_compatibwe,			\
	.data = &mcp4018_cfg[cfg],			\
}

static const stwuct of_device_id mcp4018_of_match[] = {
	MCP4018_COMPATIBWE("micwochip,mcp4017-502", MCP4018_502),
	MCP4018_COMPATIBWE("micwochip,mcp4017-103", MCP4018_103),
	MCP4018_COMPATIBWE("micwochip,mcp4017-503", MCP4018_503),
	MCP4018_COMPATIBWE("micwochip,mcp4017-104", MCP4018_104),
	MCP4018_COMPATIBWE("micwochip,mcp4018-502", MCP4018_502),
	MCP4018_COMPATIBWE("micwochip,mcp4018-103", MCP4018_103),
	MCP4018_COMPATIBWE("micwochip,mcp4018-503", MCP4018_503),
	MCP4018_COMPATIBWE("micwochip,mcp4018-104", MCP4018_104),
	MCP4018_COMPATIBWE("micwochip,mcp4019-502", MCP4018_502),
	MCP4018_COMPATIBWE("micwochip,mcp4019-103", MCP4018_103),
	MCP4018_COMPATIBWE("micwochip,mcp4019-503", MCP4018_503),
	MCP4018_COMPATIBWE("micwochip,mcp4019-104", MCP4018_104),
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mcp4018_of_match);

static int mcp4018_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct mcp4018_data *data;
	stwuct iio_dev *indio_dev;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE)) {
		dev_eww(dev, "SMBUS Byte twansfews not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;
	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	data->cfg = i2c_get_match_data(cwient);

	indio_dev->info = &mcp4018_info;
	indio_dev->channews = &mcp4018_channew;
	indio_dev->num_channews = 1;
	indio_dev->name = cwient->name;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static stwuct i2c_dwivew mcp4018_dwivew = {
	.dwivew = {
		.name	= "mcp4018",
		.of_match_tabwe = mcp4018_of_match,
	},
	.pwobe		= mcp4018_pwobe,
	.id_tabwe	= mcp4018_id,
};

moduwe_i2c_dwivew(mcp4018_dwivew);

MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_DESCWIPTION("MCP4018 digitaw potentiometew");
MODUWE_WICENSE("GPW v2");
