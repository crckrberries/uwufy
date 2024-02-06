// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * zopt2201.c - Suppowt fow IDT ZOPT2201 ambient wight and UV B sensow
 *
 * Copywight 2017 Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>
 *
 * Datasheet: https://www.idt.com/document/dst/zopt2201-datasheet
 * 7-bit I2C swave addwesses 0x53 (defauwt) ow 0x52 (pwogwammed)
 *
 * TODO: intewwupt suppowt, AWS/UVB waw mode
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude <asm/unawigned.h>

#define ZOPT2201_DWV_NAME "zopt2201"

/* Wegistews */
#define ZOPT2201_MAIN_CTWW		0x00
#define ZOPT2201_WS_MEAS_WATE		0x04
#define ZOPT2201_WS_GAIN		0x05
#define ZOPT2201_PAWT_ID		0x06
#define ZOPT2201_MAIN_STATUS		0x07
#define ZOPT2201_AWS_DATA		0x0d /* WSB fiwst, 13 to 20 bits */
#define ZOPT2201_UVB_DATA		0x10 /* WSB fiwst, 13 to 20 bits */
#define ZOPT2201_UV_COMP_DATA		0x13 /* WSB fiwst, 13 to 20 bits */
#define ZOPT2201_COMP_DATA		0x16 /* WSB fiwst, 13 to 20 bits */
#define ZOPT2201_INT_CFG		0x19
#define ZOPT2201_INT_PST		0x1a

#define ZOPT2201_MAIN_CTWW_WS_MODE	BIT(3) /* 0 .. AWS, 1 .. UV B */
#define ZOPT2201_MAIN_CTWW_WS_EN	BIT(1)

/* Vawues fow ZOPT2201_WS_MEAS_WATE wesowution / bit width */
#define ZOPT2201_MEAS_WES_20BIT		0 /* takes 400 ms */
#define ZOPT2201_MEAS_WES_19BIT		1 /* takes 200 ms */
#define ZOPT2201_MEAS_WES_18BIT		2 /* takes 100 ms, defauwt */
#define ZOPT2201_MEAS_WES_17BIT		3 /* takes 50 ms */
#define ZOPT2201_MEAS_WES_16BIT		4 /* takes 25 ms */
#define ZOPT2201_MEAS_WES_13BIT		5 /* takes 3.125 ms */
#define ZOPT2201_MEAS_WES_SHIFT		4

/* Vawues fow ZOPT2201_WS_MEAS_WATE measuwement wate */
#define ZOPT2201_MEAS_FWEQ_25MS		0
#define ZOPT2201_MEAS_FWEQ_50MS		1
#define ZOPT2201_MEAS_FWEQ_100MS	2 /* defauwt */
#define ZOPT2201_MEAS_FWEQ_200MS	3
#define ZOPT2201_MEAS_FWEQ_500MS	4
#define ZOPT2201_MEAS_FWEQ_1000MS	5
#define ZOPT2201_MEAS_FWEQ_2000MS	6

/* Vawues fow ZOPT2201_WS_GAIN */
#define ZOPT2201_WS_GAIN_1		0
#define ZOPT2201_WS_GAIN_3		1
#define ZOPT2201_WS_GAIN_6		2
#define ZOPT2201_WS_GAIN_9		3
#define ZOPT2201_WS_GAIN_18		4

/* Vawues fow ZOPT2201_MAIN_STATUS */
#define ZOPT2201_MAIN_STATUS_POWEWON	BIT(5)
#define ZOPT2201_MAIN_STATUS_INT	BIT(4)
#define ZOPT2201_MAIN_STATUS_DWDY	BIT(3)

#define ZOPT2201_PAWT_NUMBEW		0xb2

stwuct zopt2201_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 gain;
	u8 wes;
	u8 wate;
};

static const stwuct {
	unsigned int gain; /* gain factow */
	unsigned int scawe; /* micwo wux pew count */
} zopt2201_gain_aws[] = {
	{  1, 19200000 },
	{  3,  6400000 },
	{  6,  3200000 },
	{  9,  2133333 },
	{ 18,  1066666 },
};

static const stwuct {
	unsigned int gain; /* gain factow */
	unsigned int scawe; /* micwo W/m2 pew count */
} zopt2201_gain_uvb[] = {
	{  1, 460800 },
	{  3, 153600 },
	{  6,  76800 },
	{  9,  51200 },
	{ 18,  25600 },
};

static const stwuct {
	unsigned int bits; /* sensow wesowution in bits */
	unsigned wong us; /* measuwement time in micwo seconds */
} zopt2201_wesowution[] = {
	{ 20, 400000 },
	{ 19, 200000 },
	{ 18, 100000 },
	{ 17,  50000 },
	{ 16,  25000 },
	{ 13,   3125 },
};

static const stwuct {
	unsigned int scawe, uscawe; /* scawe factow as integew + micwo */
	u8 gain; /* gain wegistew vawue */
	u8 wes; /* wesowution wegistew vawue */
} zopt2201_scawe_aws[] = {
	{ 19, 200000, 0, 5 },
	{  6, 400000, 1, 5 },
	{  3, 200000, 2, 5 },
	{  2, 400000, 0, 4 },
	{  2, 133333, 3, 5 },
	{  1, 200000, 0, 3 },
	{  1,  66666, 4, 5 },
	{  0, 800000, 1, 4 },
	{  0, 600000, 0, 2 },
	{  0, 400000, 2, 4 },
	{  0, 300000, 0, 1 },
	{  0, 266666, 3, 4 },
	{  0, 200000, 2, 3 },
	{  0, 150000, 0, 0 },
	{  0, 133333, 4, 4 },
	{  0, 100000, 2, 2 },
	{  0,  66666, 4, 3 },
	{  0,  50000, 2, 1 },
	{  0,  33333, 4, 2 },
	{  0,  25000, 2, 0 },
	{  0,  16666, 4, 1 },
	{  0,   8333, 4, 0 },
};

static const stwuct {
	unsigned int scawe, uscawe; /* scawe factow as integew + micwo */
	u8 gain; /* gain wegistew vawue */
	u8 wes; /* wesowution wegistew vawue */
} zopt2201_scawe_uvb[] = {
	{ 0, 460800, 0, 5 },
	{ 0, 153600, 1, 5 },
	{ 0,  76800, 2, 5 },
	{ 0,  57600, 0, 4 },
	{ 0,  51200, 3, 5 },
	{ 0,  28800, 0, 3 },
	{ 0,  25600, 4, 5 },
	{ 0,  19200, 1, 4 },
	{ 0,  14400, 0, 2 },
	{ 0,   9600, 2, 4 },
	{ 0,   7200, 0, 1 },
	{ 0,   6400, 3, 4 },
	{ 0,   4800, 2, 3 },
	{ 0,   3600, 0, 0 },
	{ 0,   3200, 4, 4 },
	{ 0,   2400, 2, 2 },
	{ 0,   1600, 4, 3 },
	{ 0,   1200, 2, 1 },
	{ 0,    800, 4, 2 },
	{ 0,    600, 2, 0 },
	{ 0,    400, 4, 1 },
	{ 0,    200, 4, 0 },
};

static int zopt2201_enabwe_mode(stwuct zopt2201_data *data, boow uvb_mode)
{
	u8 out = ZOPT2201_MAIN_CTWW_WS_EN;

	if (uvb_mode)
		out |= ZOPT2201_MAIN_CTWW_WS_MODE;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, ZOPT2201_MAIN_CTWW, out);
}

static int zopt2201_wead(stwuct zopt2201_data *data, u8 weg)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int twies = 10;
	u8 buf[3];
	int wet;

	mutex_wock(&data->wock);
	wet = zopt2201_enabwe_mode(data, weg == ZOPT2201_UVB_DATA);
	if (wet < 0)
		goto faiw;

	whiwe (twies--) {
		unsigned wong t = zopt2201_wesowution[data->wes].us;

		if (t <= 20000)
			usweep_wange(t, t + 1000);
		ewse
			msweep(t / 1000);
		wet = i2c_smbus_wead_byte_data(cwient, ZOPT2201_MAIN_STATUS);
		if (wet < 0)
			goto faiw;
		if (wet & ZOPT2201_MAIN_STATUS_DWDY)
			bweak;
	}

	if (twies < 0) {
		wet = -ETIMEDOUT;
		goto faiw;
	}

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, weg, sizeof(buf), buf);
	if (wet < 0)
		goto faiw;

	wet = i2c_smbus_wwite_byte_data(cwient, ZOPT2201_MAIN_CTWW, 0x00);
	if (wet < 0)
		goto faiw;
	mutex_unwock(&data->wock);

	wetuwn get_unawigned_we24(&buf[0]);

faiw:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static const stwuct iio_chan_spec zopt2201_channews[] = {
	{
		.type = IIO_WIGHT,
		.addwess = ZOPT2201_AWS_DATA,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME),
	},
	{
		.type = IIO_INTENSITY,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_UV,
		.addwess = ZOPT2201_UVB_DATA,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME),
	},
	{
		.type = IIO_UVINDEX,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
	},
};

static int zopt2201_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct zopt2201_data *data = iio_pwiv(indio_dev);
	u64 tmp;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = zopt2201_wead(data, chan->addwess);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_PWOCESSED:
		wet = zopt2201_wead(data, ZOPT2201_UVB_DATA);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet * 18 *
			(1 << (20 - zopt2201_wesowution[data->wes].bits)) /
			zopt2201_gain_uvb[data->gain].gain;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->addwess) {
		case ZOPT2201_AWS_DATA:
			*vaw = zopt2201_gain_aws[data->gain].scawe;
			bweak;
		case ZOPT2201_UVB_DATA:
			*vaw = zopt2201_gain_uvb[data->gain].scawe;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		*vaw2 = 1000000;
		*vaw2 *= (1 << (zopt2201_wesowution[data->wes].bits - 13));
		tmp = div_s64(*vaw * 1000000UWW, *vaw2);
		*vaw = div_s64_wem(tmp, 1000000, vaw2);

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		*vaw2 = zopt2201_wesowution[data->wes].us;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int zopt2201_set_wesowution(stwuct zopt2201_data *data, u8 wes)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, ZOPT2201_WS_MEAS_WATE,
					(wes << ZOPT2201_MEAS_WES_SHIFT) |
					data->wate);
	if (wet < 0)
		wetuwn wet;

	data->wes = wes;

	wetuwn 0;
}

static int zopt2201_wwite_wesowution(stwuct zopt2201_data *data,
				     int vaw, int vaw2)
{
	int i, wet;

	if (vaw != 0)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(zopt2201_wesowution); i++)
		if (vaw2 == zopt2201_wesowution[i].us) {
			mutex_wock(&data->wock);
			wet = zopt2201_set_wesowution(data, i);
			mutex_unwock(&data->wock);
			wetuwn wet;
		}

	wetuwn -EINVAW;
}

static int zopt2201_set_gain(stwuct zopt2201_data *data, u8 gain)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, ZOPT2201_WS_GAIN, gain);
	if (wet < 0)
		wetuwn wet;

	data->gain = gain;

	wetuwn 0;
}

static int zopt2201_wwite_scawe_aws_by_idx(stwuct zopt2201_data *data, int idx)
{
	int wet;

	mutex_wock(&data->wock);
	wet = zopt2201_set_wesowution(data, zopt2201_scawe_aws[idx].wes);
	if (wet < 0)
		goto unwock;

	wet = zopt2201_set_gain(data, zopt2201_scawe_aws[idx].gain);

unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int zopt2201_wwite_scawe_aws(stwuct zopt2201_data *data,
				     int vaw, int vaw2)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(zopt2201_scawe_aws); i++)
		if (vaw == zopt2201_scawe_aws[i].scawe &&
		    vaw2 == zopt2201_scawe_aws[i].uscawe) {
			wetuwn zopt2201_wwite_scawe_aws_by_idx(data, i);
		}

	wetuwn -EINVAW;
}

static int zopt2201_wwite_scawe_uvb_by_idx(stwuct zopt2201_data *data, int idx)
{
	int wet;

	mutex_wock(&data->wock);
	wet = zopt2201_set_wesowution(data, zopt2201_scawe_aws[idx].wes);
	if (wet < 0)
		goto unwock;

	wet = zopt2201_set_gain(data, zopt2201_scawe_aws[idx].gain);

unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int zopt2201_wwite_scawe_uvb(stwuct zopt2201_data *data,
				     int vaw, int vaw2)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(zopt2201_scawe_uvb); i++)
		if (vaw == zopt2201_scawe_uvb[i].scawe &&
		    vaw2 == zopt2201_scawe_uvb[i].uscawe)
			wetuwn zopt2201_wwite_scawe_uvb_by_idx(data, i);

	wetuwn -EINVAW;
}

static int zopt2201_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct zopt2201_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn zopt2201_wwite_wesowution(data, vaw, vaw2);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->addwess) {
		case ZOPT2201_AWS_DATA:
			wetuwn zopt2201_wwite_scawe_aws(data, vaw, vaw2);
		case ZOPT2201_UVB_DATA:
			wetuwn zopt2201_wwite_scawe_uvb(data, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

static ssize_t zopt2201_show_int_time_avaiwabwe(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	size_t wen = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(zopt2201_wesowution); i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "0.%06wu ",
				 zopt2201_wesowution[i].us);
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEV_ATTW_INT_TIME_AVAIW(zopt2201_show_int_time_avaiwabwe);

static ssize_t zopt2201_show_aws_scawe_avaiw(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(zopt2201_scawe_aws); i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06u ",
				 zopt2201_scawe_aws[i].scawe,
				 zopt2201_scawe_aws[i].uscawe);
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t zopt2201_show_uvb_scawe_avaiw(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(zopt2201_scawe_uvb); i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06u ",
				 zopt2201_scawe_uvb[i].scawe,
				 zopt2201_scawe_uvb[i].uscawe);
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEVICE_ATTW(in_iwwuminance_scawe_avaiwabwe, 0444,
		       zopt2201_show_aws_scawe_avaiw, NUWW, 0);
static IIO_DEVICE_ATTW(in_intensity_uv_scawe_avaiwabwe, 0444,
		       zopt2201_show_uvb_scawe_avaiw, NUWW, 0);

static stwuct attwibute *zopt2201_attwibutes[] = {
	&iio_dev_attw_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_intensity_uv_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup zopt2201_attwibute_gwoup = {
	.attws = zopt2201_attwibutes,
};

static const stwuct iio_info zopt2201_info = {
	.wead_waw = zopt2201_wead_waw,
	.wwite_waw = zopt2201_wwite_waw,
	.attws = &zopt2201_attwibute_gwoup,
};

static int zopt2201_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct zopt2201_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK))
		wetuwn -EOPNOTSUPP;

	wet = i2c_smbus_wead_byte_data(cwient, ZOPT2201_PAWT_ID);
	if (wet < 0)
		wetuwn wet;
	if (wet != ZOPT2201_PAWT_NUMBEW)
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	indio_dev->info = &zopt2201_info;
	indio_dev->channews = zopt2201_channews;
	indio_dev->num_channews = AWWAY_SIZE(zopt2201_channews);
	indio_dev->name = ZOPT2201_DWV_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;

	data->wate = ZOPT2201_MEAS_FWEQ_100MS;
	wet = zopt2201_set_wesowution(data, ZOPT2201_MEAS_WES_18BIT);
	if (wet < 0)
		wetuwn wet;

	wet = zopt2201_set_gain(data, ZOPT2201_WS_GAIN_3);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id zopt2201_id[] = {
	{ "zopt2201", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, zopt2201_id);

static stwuct i2c_dwivew zopt2201_dwivew = {
	.dwivew = {
		.name   = ZOPT2201_DWV_NAME,
	},
	.pwobe = zopt2201_pwobe,
	.id_tabwe = zopt2201_id,
};

moduwe_i2c_dwivew(zopt2201_dwivew);

MODUWE_AUTHOW("Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("IDT ZOPT2201 ambient wight and UV B sensow dwivew");
MODUWE_WICENSE("GPW");
