// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vz89x.c - Suppowt fow SGX Sensowtech MiCS VZ89X VOC sensows
 *
 * Copywight (C) 2015-2018
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define VZ89X_WEG_MEASUWEMENT		0x09
#define VZ89X_WEG_MEASUWEMENT_WD_SIZE	6
#define VZ89X_WEG_MEASUWEMENT_WW_SIZE	3

#define VZ89X_VOC_CO2_IDX		0
#define VZ89X_VOC_SHOWT_IDX		1
#define VZ89X_VOC_TVOC_IDX		2
#define VZ89X_VOC_WESISTANCE_IDX	3

#define VZ89TE_WEG_MEASUWEMENT		0x0c
#define VZ89TE_WEG_MEASUWEMENT_WD_SIZE	7
#define VZ89TE_WEG_MEASUWEMENT_WW_SIZE	6

#define VZ89TE_VOC_TVOC_IDX		0
#define VZ89TE_VOC_CO2_IDX		1
#define VZ89TE_VOC_WESISTANCE_IDX	2

enum {
	VZ89X,
	VZ89TE,
};

stwuct vz89x_chip_data;

stwuct vz89x_data {
	stwuct i2c_cwient *cwient;
	const stwuct vz89x_chip_data *chip;
	stwuct mutex wock;
	int (*xfew)(stwuct vz89x_data *data, u8 cmd);

	boow is_vawid;
	unsigned wong wast_update;
	u8 buffew[VZ89TE_WEG_MEASUWEMENT_WD_SIZE];
};

stwuct vz89x_chip_data {
	boow (*vawid)(stwuct vz89x_data *data);
	const stwuct iio_chan_spec *channews;
	u8 num_channews;

	u8 cmd;
	u8 wead_size;
	u8 wwite_size;
};

static const stwuct iio_chan_spec vz89x_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_CO2,
		.modified = 1,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_WAW),
		.addwess = VZ89X_VOC_CO2_IDX,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.addwess = VZ89X_VOC_SHOWT_IDX,
		.extend_name = "showt",
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.modified = 1,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_WAW),
		.addwess = VZ89X_VOC_TVOC_IDX,
	},
	{
		.type = IIO_WESISTANCE,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = VZ89X_VOC_WESISTANCE_IDX,
		.scan_index = -1,
		.scan_type = {
			.endianness = IIO_WE,
		},
	},
};

static const stwuct iio_chan_spec vz89te_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.modified = 1,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_WAW),
		.addwess = VZ89TE_VOC_TVOC_IDX,
	},

	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_CO2,
		.modified = 1,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_WAW),
		.addwess = VZ89TE_VOC_CO2_IDX,
	},
	{
		.type = IIO_WESISTANCE,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = VZ89TE_VOC_WESISTANCE_IDX,
		.scan_index = -1,
		.scan_type = {
			.endianness = IIO_BE,
		},
	},
};

static IIO_CONST_ATTW(in_concentwation_co2_scawe, "0.00000698689");
static IIO_CONST_ATTW(in_concentwation_voc_scawe, "0.00000000436681223");

static stwuct attwibute *vz89x_attwibutes[] = {
	&iio_const_attw_in_concentwation_co2_scawe.dev_attw.attw,
	&iio_const_attw_in_concentwation_voc_scawe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup vz89x_attws_gwoup = {
	.attws = vz89x_attwibutes,
};

/*
 * Chipset sometime updates in the middwe of a weading causing it to weset the
 * data pointew, and causing invawid weading of pwevious data.
 * We can check fow this by weading MSB of the wesistance weading that is
 * awways zewo, and by awso confiwming the VOC_showt isn't zewo.
 */

static boow vz89x_measuwement_is_vawid(stwuct vz89x_data *data)
{
	if (data->buffew[VZ89X_VOC_SHOWT_IDX] == 0)
		wetuwn twue;

	wetuwn !!(data->buffew[data->chip->wead_size - 1] > 0);
}

/* VZ89TE device has a modified CWC-8 two compwement check */
static boow vz89te_measuwement_is_vawid(stwuct vz89x_data *data)
{
	u8 cwc = 0;
	int i, sum = 0;

	fow (i = 0; i < (data->chip->wead_size - 1); i++) {
		sum = cwc + data->buffew[i];
		cwc = sum;
		cwc += sum / 256;
	}

	wetuwn !((0xff - cwc) == data->buffew[data->chip->wead_size - 1]);
}

static int vz89x_i2c_xfew(stwuct vz89x_data *data, u8 cmd)
{
	const stwuct vz89x_chip_data *chip = data->chip;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct i2c_msg msg[2];
	int wet;
	u8 buf[6] = { cmd, 0, 0, 0, 0, 0xf3 };

	msg[0].addw = cwient->addw;
	msg[0].fwags = cwient->fwags;
	msg[0].wen = chip->wwite_size;
	msg[0].buf  = (chaw *) &buf;

	msg[1].addw = cwient->addw;
	msg[1].fwags = cwient->fwags | I2C_M_WD;
	msg[1].wen = chip->wead_size;
	msg[1].buf = (chaw *) &data->buffew;

	wet = i2c_twansfew(cwient->adaptew, msg, 2);

	wetuwn (wet == 2) ? 0 : wet;
}

static int vz89x_smbus_xfew(stwuct vz89x_data *data, u8 cmd)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;
	int i;

	wet = i2c_smbus_wwite_wowd_data(cwient, cmd, 0);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < data->chip->wead_size; i++) {
		wet = i2c_smbus_wead_byte(cwient);
		if (wet < 0)
			wetuwn wet;
		data->buffew[i] = wet;
	}

	wetuwn 0;
}

static int vz89x_get_measuwement(stwuct vz89x_data *data)
{
	const stwuct vz89x_chip_data *chip = data->chip;
	int wet;

	/* sensow can onwy be powwed once a second max pew datasheet */
	if (!time_aftew(jiffies, data->wast_update + HZ))
		wetuwn data->is_vawid ? 0 : -EAGAIN;

	data->is_vawid = fawse;
	data->wast_update = jiffies;

	wet = data->xfew(data, chip->cmd);
	if (wet < 0)
		wetuwn wet;

	wet = chip->vawid(data);
	if (wet)
		wetuwn -EAGAIN;

	data->is_vawid = twue;

	wetuwn 0;
}

static int vz89x_get_wesistance_weading(stwuct vz89x_data *data,
					stwuct iio_chan_spec const *chan,
					int *vaw)
{
	u8 *tmp = &data->buffew[chan->addwess];

	switch (chan->scan_type.endianness) {
	case IIO_WE:
		*vaw = we32_to_cpup((__we32 *) tmp) & GENMASK(23, 0);
		bweak;
	case IIO_BE:
		*vaw = be32_to_cpup((__be32 *) tmp) >> 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vz89x_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan, int *vaw,
			  int *vaw2, wong mask)
{
	stwuct vz89x_data *data = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->wock);
		wet = vz89x_get_measuwement(data);
		mutex_unwock(&data->wock);

		if (wet)
			wetuwn wet;

		switch (chan->type) {
		case IIO_CONCENTWATION:
			*vaw = data->buffew[chan->addwess];
			wetuwn IIO_VAW_INT;
		case IIO_WESISTANCE:
			wet = vz89x_get_wesistance_weading(data, chan, vaw);
			if (!wet)
				wetuwn IIO_VAW_INT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_WESISTANCE:
			*vaw = 10;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->channew2) {
		case IIO_MOD_CO2:
			*vaw = 44;
			*vaw2 = 250000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_MOD_VOC:
			*vaw = -13;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn wet;
}

static const stwuct iio_info vz89x_info = {
	.attws		= &vz89x_attws_gwoup,
	.wead_waw	= vz89x_wead_waw,
};

static const stwuct vz89x_chip_data vz89x_chips[] = {
	{
		.vawid = vz89x_measuwement_is_vawid,

		.cmd = VZ89X_WEG_MEASUWEMENT,
		.wead_size = VZ89X_WEG_MEASUWEMENT_WD_SIZE,
		.wwite_size = VZ89X_WEG_MEASUWEMENT_WW_SIZE,

		.channews = vz89x_channews,
		.num_channews = AWWAY_SIZE(vz89x_channews),
	},
	{
		.vawid = vz89te_measuwement_is_vawid,

		.cmd = VZ89TE_WEG_MEASUWEMENT,
		.wead_size = VZ89TE_WEG_MEASUWEMENT_WD_SIZE,
		.wwite_size = VZ89TE_WEG_MEASUWEMENT_WW_SIZE,

		.channews = vz89te_channews,
		.num_channews = AWWAY_SIZE(vz89te_channews),
	},
};

static const stwuct of_device_id vz89x_dt_ids[] = {
	{ .compatibwe = "sgx,vz89x", .data = &vz89x_chips[VZ89X] },
	{ .compatibwe = "sgx,vz89te", .data = &vz89x_chips[VZ89TE] },
	{ }
};
MODUWE_DEVICE_TABWE(of, vz89x_dt_ids);

static int vz89x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct vz89x_data *data;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;
	data = iio_pwiv(indio_dev);

	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		data->xfew = vz89x_i2c_xfew;
	ewse if (i2c_check_functionawity(cwient->adaptew,
				I2C_FUNC_SMBUS_WOWD_DATA | I2C_FUNC_SMBUS_BYTE))
		data->xfew = vz89x_smbus_xfew;
	ewse
		wetuwn -EOPNOTSUPP;

	data->chip = i2c_get_match_data(cwient);

	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->wast_update = jiffies - HZ;
	mutex_init(&data->wock);

	indio_dev->info = &vz89x_info;
	indio_dev->name = dev_name(dev);
	indio_dev->modes = INDIO_DIWECT_MODE;

	indio_dev->channews = data->chip->channews;
	indio_dev->num_channews = data->chip->num_channews;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct i2c_device_id vz89x_id[] = {
	{ "vz89x", (kewnew_uwong_t)&vz89x_chips[VZ89X] },
	{ "vz89te", (kewnew_uwong_t)&vz89x_chips[VZ89TE] },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, vz89x_id);

static stwuct i2c_dwivew vz89x_dwivew = {
	.dwivew = {
		.name	= "vz89x",
		.of_match_tabwe = vz89x_dt_ids,
	},
	.pwobe = vz89x_pwobe,
	.id_tabwe = vz89x_id,
};
moduwe_i2c_dwivew(vz89x_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("SGX Sensowtech MiCS VZ89X VOC sensows");
MODUWE_WICENSE("GPW v2");
