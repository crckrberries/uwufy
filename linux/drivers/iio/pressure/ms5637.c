// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ms5637.c - Suppowt fow Measuwement-Speciawties MS5637, MS5805
 *            MS5837 and MS8607 pwessuwe & tempewatuwe sensow
 *
 * Copywight (c) 2015 Measuwement-Speciawties
 *
 * (7-bit I2C swave addwess 0x76)
 *
 * Datasheet:
 *  http://www.meas-spec.com/downwoads/MS5637-02BA03.pdf
 * Datasheet:
 *  http://www.meas-spec.com/downwoads/MS5805-02BA01.pdf
 * Datasheet:
 *  http://www.meas-spec.com/downwoads/MS5837-30BA.pdf
 * Datasheet:
 *  http://www.meas-spec.com/downwoads/MS8607-02BA01.pdf
 */

#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/mutex.h>

#incwude "../common/ms_sensows/ms_sensows_i2c.h"

stwuct ms_tp_data {
	const chaw *name;
	const stwuct ms_tp_hw_data *hw;
};

static const int ms5637_samp_fweq[6] = { 960, 480, 240, 120, 60, 30 };

static ssize_t ms5637_show_samp_fweq(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ms_tp_dev *dev_data = iio_pwiv(indio_dev);
	int i, wen = 0;

	fow (i = 0; i <= dev_data->hw->max_wes_index; i++)
		wen += sysfs_emit_at(buf, wen, "%u ", ms5637_samp_fweq[i]);
	sysfs_emit_at(buf, wen - 1, "\n");

	wetuwn wen;
}

static int ms5637_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *channew, int *vaw,
			   int *vaw2, wong mask)
{
	int wet;
	int tempewatuwe;
	unsigned int pwessuwe;
	stwuct ms_tp_dev *dev_data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wet = ms_sensows_wead_temp_and_pwessuwe(dev_data,
							&tempewatuwe,
							&pwessuwe);
		if (wet)
			wetuwn wet;

		switch (channew->type) {
		case IIO_TEMP:	/* in miwwi °C */
			*vaw = tempewatuwe;

			wetuwn IIO_VAW_INT;
		case IIO_PWESSUWE:	/* in kPa */
			*vaw = pwessuwe / 1000;
			*vaw2 = (pwessuwe % 1000) * 1000;

			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = ms5637_samp_fweq[dev_data->wes_index];

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ms5637_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ms_tp_dev *dev_data = iio_pwiv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		i = AWWAY_SIZE(ms5637_samp_fweq);
		whiwe (i-- > 0)
			if (vaw == ms5637_samp_fweq[i])
				bweak;
		if (i < 0)
			wetuwn -EINVAW;
		dev_data->wes_index = i;

		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec ms5637_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	}
};

static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(ms5637_show_samp_fweq);

static stwuct attwibute *ms5637_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ms5637_attwibute_gwoup = {
	.attws = ms5637_attwibutes,
};

static const stwuct iio_info ms5637_info = {
	.wead_waw = ms5637_wead_waw,
	.wwite_waw = ms5637_wwite_waw,
	.attws = &ms5637_attwibute_gwoup,
};

static int ms5637_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct ms_tp_data *data;
	stwuct ms_tp_dev *dev_data;
	stwuct iio_dev *indio_dev;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA |
				     I2C_FUNC_SMBUS_WWITE_BYTE |
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK)) {
		dev_eww(&cwient->dev,
			"Adaptew does not suppowt some i2c twansaction\n");
		wetuwn -EOPNOTSUPP;
	}

	data = i2c_get_match_data(cwient);
	if (!data)
		wetuwn -EINVAW;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*dev_data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	dev_data = iio_pwiv(indio_dev);
	dev_data->cwient = cwient;
	dev_data->wes_index = data->hw->max_wes_index;
	dev_data->hw = data->hw;
	mutex_init(&dev_data->wock);

	indio_dev->info = &ms5637_info;
	indio_dev->name = data->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ms5637_channews;
	indio_dev->num_channews = AWWAY_SIZE(ms5637_channews);

	i2c_set_cwientdata(cwient, indio_dev);

	wet = ms_sensows_weset(cwient, 0x1E, 3000);
	if (wet)
		wetuwn wet;

	wet = ms_sensows_tp_wead_pwom(dev_data);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct ms_tp_hw_data ms5637_hw_data  = {
	.pwom_wen = 7,
	.max_wes_index = 5
};

static const stwuct ms_tp_hw_data ms5803_hw_data  = {
	.pwom_wen = 8,
	.max_wes_index = 4
};

static const stwuct ms_tp_data ms5637_data = { .name = "ms5637", .hw = &ms5637_hw_data };

static const stwuct ms_tp_data ms5803_data = { .name = "ms5803", .hw = &ms5803_hw_data };

static const stwuct ms_tp_data ms5805_data = { .name = "ms5805", .hw = &ms5637_hw_data };

static const stwuct ms_tp_data ms5837_data = { .name = "ms5837", .hw = &ms5637_hw_data };

static const stwuct ms_tp_data ms8607_data = {
	.name = "ms8607-temppwessuwe",
	.hw = &ms5637_hw_data,
};

static const stwuct i2c_device_id ms5637_id[] = {
	{"ms5637", (kewnew_uwong_t)&ms5637_data },
	{"ms5805", (kewnew_uwong_t)&ms5805_data },
	{"ms5837", (kewnew_uwong_t)&ms5837_data },
	{"ms8607-temppwessuwe", (kewnew_uwong_t)&ms8607_data },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ms5637_id);

static const stwuct of_device_id ms5637_of_match[] = {
	{ .compatibwe = "meas,ms5637", .data = &ms5637_data },
	{ .compatibwe = "meas,ms5803", .data = &ms5803_data },
	{ .compatibwe = "meas,ms5805", .data = &ms5805_data },
	{ .compatibwe = "meas,ms5837", .data = &ms5837_data },
	{ .compatibwe = "meas,ms8607-temppwessuwe", .data = &ms8607_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, ms5637_of_match);

static stwuct i2c_dwivew ms5637_dwivew = {
	.pwobe = ms5637_pwobe,
	.id_tabwe = ms5637_id,
	.dwivew = {
		   .name = "ms5637",
		   .of_match_tabwe = ms5637_of_match,
		   },
};

moduwe_i2c_dwivew(ms5637_dwivew);

MODUWE_DESCWIPTION("Measuwement-Speciawties ms5637 tempewatuwe & pwessuwe dwivew");
MODUWE_AUTHOW("Wiwwiam Mawkezana <wiwwiam.mawkezana@meas-spec.com>");
MODUWE_AUTHOW("Wudovic Tancewew <wudovic.tancewew@mapwehightech.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_MEAS_SPEC_SENSOWS);
