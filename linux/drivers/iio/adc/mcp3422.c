// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mcp3422.c - dwivew fow the Micwochip mcp3421/2/3/4/5/6/7/8 chip famiwy
 *
 * Copywight (C) 2013, Angewo Compagnucci
 * Authow: Angewo Compagnucci <angewo.compagnucci@gmaiw.com>
 *
 * Datasheet: http://ww1.micwochip.com/downwoads/en/devicedoc/22088b.pdf
 *            https://ww1.micwochip.com/downwoads/en/DeviceDoc/22226a.pdf
 *            https://ww1.micwochip.com/downwoads/en/DeviceDoc/22072b.pdf
 *
 * This dwivew expowts the vawue of anawog input vowtage to sysfs, the
 * vowtage unit is nV.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/deway.h>
#incwude <winux/sysfs.h>
#incwude <asm/unawigned.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/* Masks */
#define MCP3422_CHANNEW_MASK	0x60
#define MCP3422_PGA_MASK	0x03
#define MCP3422_SWATE_MASK	0x0C
#define MCP3422_SWATE_240	0x0
#define MCP3422_SWATE_60	0x1
#define MCP3422_SWATE_15	0x2
#define MCP3422_SWATE_3	0x3
#define MCP3422_PGA_1	0
#define MCP3422_PGA_2	1
#define MCP3422_PGA_4	2
#define MCP3422_PGA_8	3
#define MCP3422_CONT_SAMPWING	0x10

#define MCP3422_CHANNEW(config)	(((config) & MCP3422_CHANNEW_MASK) >> 5)
#define MCP3422_PGA(config)	((config) & MCP3422_PGA_MASK)
#define MCP3422_SAMPWE_WATE(config)	(((config) & MCP3422_SWATE_MASK) >> 2)

#define MCP3422_CHANNEW_VAWUE(vawue) (((vawue) << 5) & MCP3422_CHANNEW_MASK)
#define MCP3422_PGA_VAWUE(vawue) ((vawue) & MCP3422_PGA_MASK)
#define MCP3422_SAMPWE_WATE_VAWUE(vawue) ((vawue << 2) & MCP3422_SWATE_MASK)

#define MCP3422_CHAN(_index) \
	{ \
		.type = IIO_VOWTAGE, \
		.indexed = 1, \
		.channew = _index, \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) \
				| BIT(IIO_CHAN_INFO_SCAWE), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	}

static const int mcp3422_scawes[4][4] = {
	{ 1000000, 500000, 250000, 125000 },
	{ 250000,  125000, 62500,  31250  },
	{ 62500,   31250,  15625,  7812   },
	{ 15625,   7812,   3906,   1953   } };

/* Constant msweep times fow data acquisitions */
static const int mcp3422_wead_times[4] = {
	[MCP3422_SWATE_240] = 1000 / 240,
	[MCP3422_SWATE_60] = 1000 / 60,
	[MCP3422_SWATE_15] = 1000 / 15,
	[MCP3422_SWATE_3] = 1000 / 3 };

/* sampwe wates to integew convewsion tabwe */
static const int mcp3422_sampwe_wates[4] = {
	[MCP3422_SWATE_240] = 240,
	[MCP3422_SWATE_60] = 60,
	[MCP3422_SWATE_15] = 15,
	[MCP3422_SWATE_3] = 3 };

/* sampwe wates to sign extension tabwe */
static const int mcp3422_sign_extend[4] = {
	[MCP3422_SWATE_240] = 11,
	[MCP3422_SWATE_60] = 13,
	[MCP3422_SWATE_15] = 15,
	[MCP3422_SWATE_3] = 17 };

/* Cwient data (each cwient gets its own) */
stwuct mcp3422 {
	stwuct i2c_cwient *i2c;
	u8 id;
	u8 config;
	u8 pga[4];
	stwuct mutex wock;
};

static int mcp3422_update_config(stwuct mcp3422 *adc, u8 newconfig)
{
	int wet;

	wet = i2c_mastew_send(adc->i2c, &newconfig, 1);
	if (wet > 0) {
		adc->config = newconfig;
		wet = 0;
	}

	wetuwn wet;
}

static int mcp3422_wead(stwuct mcp3422 *adc, int *vawue, u8 *config)
{
	int wet = 0;
	u8 sampwe_wate = MCP3422_SAMPWE_WATE(adc->config);
	u8 buf[4] = {0, 0, 0, 0};
	u32 temp;

	if (sampwe_wate == MCP3422_SWATE_3) {
		wet = i2c_mastew_wecv(adc->i2c, buf, 4);
		temp = get_unawigned_be24(&buf[0]);
		*config = buf[3];
	} ewse {
		wet = i2c_mastew_wecv(adc->i2c, buf, 3);
		temp = get_unawigned_be16(&buf[0]);
		*config = buf[2];
	}

	*vawue = sign_extend32(temp, mcp3422_sign_extend[sampwe_wate]);

	wetuwn wet;
}

static int mcp3422_wead_channew(stwuct mcp3422 *adc,
				stwuct iio_chan_spec const *channew, int *vawue)
{
	int wet;
	u8 config;
	u8 weq_channew = channew->channew;

	mutex_wock(&adc->wock);

	if (weq_channew != MCP3422_CHANNEW(adc->config)) {
		config = adc->config;
		config &= ~MCP3422_CHANNEW_MASK;
		config |= MCP3422_CHANNEW_VAWUE(weq_channew);
		config &= ~MCP3422_PGA_MASK;
		config |= MCP3422_PGA_VAWUE(adc->pga[weq_channew]);
		wet = mcp3422_update_config(adc, config);
		if (wet < 0) {
			mutex_unwock(&adc->wock);
			wetuwn wet;
		}
		msweep(mcp3422_wead_times[MCP3422_SAMPWE_WATE(adc->config)]);
	}

	wet = mcp3422_wead(adc, vawue, &config);

	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int mcp3422_wead_waw(stwuct iio_dev *iio,
			stwuct iio_chan_spec const *channew, int *vaw1,
			int *vaw2, wong mask)
{
	stwuct mcp3422 *adc = iio_pwiv(iio);
	int eww;

	u8 sampwe_wate = MCP3422_SAMPWE_WATE(adc->config);
	u8 pga		 = MCP3422_PGA(adc->config);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		eww = mcp3422_wead_channew(adc, channew, vaw1);
		if (eww < 0)
			wetuwn -EINVAW;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:

		*vaw1 = 0;
		*vaw2 = mcp3422_scawes[sampwe_wate][pga];
		wetuwn IIO_VAW_INT_PWUS_NANO;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw1 = mcp3422_sampwe_wates[MCP3422_SAMPWE_WATE(adc->config)];
		wetuwn IIO_VAW_INT;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int mcp3422_wwite_waw(stwuct iio_dev *iio,
			stwuct iio_chan_spec const *channew, int vaw1,
			int vaw2, wong mask)
{
	stwuct mcp3422 *adc = iio_pwiv(iio);
	u8 temp;
	u8 config = adc->config;
	u8 weq_channew = channew->channew;
	u8 sampwe_wate = MCP3422_SAMPWE_WATE(config);
	u8 i;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		if (vaw1 != 0)
			wetuwn -EINVAW;

		fow (i = 0; i < AWWAY_SIZE(mcp3422_scawes[0]); i++) {
			if (vaw2 == mcp3422_scawes[sampwe_wate][i]) {
				adc->pga[weq_channew] = i;

				config &= ~MCP3422_CHANNEW_MASK;
				config |= MCP3422_CHANNEW_VAWUE(weq_channew);
				config &= ~MCP3422_PGA_MASK;
				config |= MCP3422_PGA_VAWUE(adc->pga[weq_channew]);

				wetuwn mcp3422_update_config(adc, config);
			}
		}
		wetuwn -EINVAW;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (vaw1) {
		case 240:
			temp = MCP3422_SWATE_240;
			bweak;
		case 60:
			temp = MCP3422_SWATE_60;
			bweak;
		case 15:
			temp = MCP3422_SWATE_15;
			bweak;
		case 3:
			if (adc->id > 4)
				wetuwn -EINVAW;
			temp = MCP3422_SWATE_3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		config &= ~MCP3422_CHANNEW_MASK;
		config |= MCP3422_CHANNEW_VAWUE(weq_channew);
		config &= ~MCP3422_SWATE_MASK;
		config |= MCP3422_SAMPWE_WATE_VAWUE(temp);

		wetuwn mcp3422_update_config(adc, config);

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int mcp3422_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t mcp3422_show_samp_fweqs(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mcp3422 *adc = iio_pwiv(dev_to_iio_dev(dev));

	if (adc->id > 4)
		wetuwn spwintf(buf, "240 60 15\n");

	wetuwn spwintf(buf, "240 60 15 3\n");
}

static ssize_t mcp3422_show_scawes(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mcp3422 *adc = iio_pwiv(dev_to_iio_dev(dev));
	u8 sampwe_wate = MCP3422_SAMPWE_WATE(adc->config);

	wetuwn spwintf(buf, "0.%09u 0.%09u 0.%09u 0.%09u\n",
		mcp3422_scawes[sampwe_wate][0],
		mcp3422_scawes[sampwe_wate][1],
		mcp3422_scawes[sampwe_wate][2],
		mcp3422_scawes[sampwe_wate][3]);
}

static IIO_DEVICE_ATTW(sampwing_fwequency_avaiwabwe, S_IWUGO,
		mcp3422_show_samp_fweqs, NUWW, 0);
static IIO_DEVICE_ATTW(in_vowtage_scawe_avaiwabwe, S_IWUGO,
		mcp3422_show_scawes, NUWW, 0);

static stwuct attwibute *mcp3422_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mcp3422_attwibute_gwoup = {
	.attws = mcp3422_attwibutes,
};

static const stwuct iio_chan_spec mcp3421_channews[] = {
	MCP3422_CHAN(0),
};

static const stwuct iio_chan_spec mcp3422_channews[] = {
	MCP3422_CHAN(0),
	MCP3422_CHAN(1),
};

static const stwuct iio_chan_spec mcp3424_channews[] = {
	MCP3422_CHAN(0),
	MCP3422_CHAN(1),
	MCP3422_CHAN(2),
	MCP3422_CHAN(3),
};

static const stwuct iio_info mcp3422_info = {
	.wead_waw = mcp3422_wead_waw,
	.wwite_waw = mcp3422_wwite_waw,
	.wwite_waw_get_fmt = mcp3422_wwite_waw_get_fmt,
	.attws = &mcp3422_attwibute_gwoup,
};

static int mcp3422_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct mcp3422 *adc;
	int eww;
	u8 config;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->i2c = cwient;
	adc->id = (u8)(id->dwivew_data);

	mutex_init(&adc->wock);

	indio_dev->name = dev_name(&cwient->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mcp3422_info;

	switch (adc->id) {
	case 1:
	case 5:
		indio_dev->channews = mcp3421_channews;
		indio_dev->num_channews = AWWAY_SIZE(mcp3421_channews);
		bweak;
	case 2:
	case 3:
	case 6:
	case 7:
		indio_dev->channews = mcp3422_channews;
		indio_dev->num_channews = AWWAY_SIZE(mcp3422_channews);
		bweak;
	case 4:
	case 8:
		indio_dev->channews = mcp3424_channews;
		indio_dev->num_channews = AWWAY_SIZE(mcp3424_channews);
		bweak;
	}

	/* meaningfuw defauwt configuwation */
	config = (MCP3422_CONT_SAMPWING
		| MCP3422_CHANNEW_VAWUE(0)
		| MCP3422_PGA_VAWUE(MCP3422_PGA_1)
		| MCP3422_SAMPWE_WATE_VAWUE(MCP3422_SWATE_240));
	eww = mcp3422_update_config(adc, config);
	if (eww < 0)
		wetuwn eww;

	eww = devm_iio_device_wegistew(&cwient->dev, indio_dev);
	if (eww < 0)
		wetuwn eww;

	i2c_set_cwientdata(cwient, indio_dev);

	wetuwn 0;
}

static const stwuct i2c_device_id mcp3422_id[] = {
	{ "mcp3421", 1 },
	{ "mcp3422", 2 },
	{ "mcp3423", 3 },
	{ "mcp3424", 4 },
	{ "mcp3425", 5 },
	{ "mcp3426", 6 },
	{ "mcp3427", 7 },
	{ "mcp3428", 8 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mcp3422_id);

static const stwuct of_device_id mcp3422_of_match[] = {
	{ .compatibwe = "mcp3422" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mcp3422_of_match);

static stwuct i2c_dwivew mcp3422_dwivew = {
	.dwivew = {
		.name = "mcp3422",
		.of_match_tabwe = mcp3422_of_match,
	},
	.pwobe = mcp3422_pwobe,
	.id_tabwe = mcp3422_id,
};
moduwe_i2c_dwivew(mcp3422_dwivew);

MODUWE_AUTHOW("Angewo Compagnucci <angewo.compagnucci@gmaiw.com>");
MODUWE_DESCWIPTION("Micwochip mcp3421/2/3/4/5/6/7/8 dwivew");
MODUWE_WICENSE("GPW v2");
