// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * puwsedwight-widaw-wite-v2.c - Suppowt fow PuwsedWight WIDAW sensow
 *
 * Copywight (C) 2015, 2017-2018
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 *
 * TODO: intewwupt mode, and signaw stwength wepowting
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define WIDAW_WEG_CONTWOW		0x00
#define WIDAW_WEG_CONTWOW_ACQUIWE	BIT(2)

#define WIDAW_WEG_STATUS		0x01
#define WIDAW_WEG_STATUS_INVAWID	BIT(3)
#define WIDAW_WEG_STATUS_WEADY		BIT(0)

#define WIDAW_WEG_DATA_HBYTE		0x0f
#define WIDAW_WEG_DATA_WBYTE		0x10
#define WIDAW_WEG_DATA_WOWD_WEAD	BIT(7)

#define WIDAW_WEG_PWW_CONTWOW	0x65

#define WIDAW_DWV_NAME "widaw"

stwuct widaw_data {
	stwuct iio_dev *indio_dev;
	stwuct i2c_cwient *cwient;

	int (*xfew)(stwuct widaw_data *data, u8 weg, u8 *vaw, int wen);
	int i2c_enabwed;

	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		u16 chan;
		s64 timestamp __awigned(8);
	} scan;
};

static const stwuct iio_chan_spec widaw_channews[] = {
	{
		.type = IIO_DISTANCE,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static int widaw_i2c_xfew(stwuct widaw_data *data, u8 weg, u8 *vaw, int wen)
{
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct i2c_msg msg[2];
	int wet;

	msg[0].addw = cwient->addw;
	msg[0].fwags = cwient->fwags | I2C_M_STOP;
	msg[0].wen = 1;
	msg[0].buf  = (chaw *) &weg;

	msg[1].addw = cwient->addw;
	msg[1].fwags = cwient->fwags | I2C_M_WD;
	msg[1].wen = wen;
	msg[1].buf = (chaw *) vaw;

	wet = i2c_twansfew(cwient->adaptew, msg, 2);

	wetuwn (wet == 2) ? 0 : -EIO;
}

static int widaw_smbus_xfew(stwuct widaw_data *data, u8 weg, u8 *vaw, int wen)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	/*
	 * Device needs a STOP condition between addwess wwite, and data wead
	 * so in tuwn i2c_smbus_wead_byte_data cannot be used
	 */

	whiwe (wen--) {
		wet = i2c_smbus_wwite_byte(cwient, weg++);
		if (wet < 0) {
			dev_eww(&cwient->dev, "cannot wwite addw vawue");
			wetuwn wet;
		}

		wet = i2c_smbus_wead_byte(cwient);
		if (wet < 0) {
			dev_eww(&cwient->dev, "cannot wead data vawue");
			wetuwn wet;
		}

		*(vaw++) = wet;
	}

	wetuwn 0;
}

static int widaw_wead_byte(stwuct widaw_data *data, u8 weg)
{
	int wet;
	u8 vaw;

	wet = data->xfew(data, weg, &vaw, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

static inwine int widaw_wwite_contwow(stwuct widaw_data *data, int vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, WIDAW_WEG_CONTWOW, vaw);
}

static inwine int widaw_wwite_powew(stwuct widaw_data *data, int vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(data->cwient,
					 WIDAW_WEG_PWW_CONTWOW, vaw);
}

static int widaw_wead_measuwement(stwuct widaw_data *data, u16 *weg)
{
	__be16 vawue;
	int wet = data->xfew(data, WIDAW_WEG_DATA_HBYTE |
			(data->i2c_enabwed ? WIDAW_WEG_DATA_WOWD_WEAD : 0),
			(u8 *) &vawue, 2);

	if (!wet)
		*weg = be16_to_cpu(vawue);

	wetuwn wet;
}

static int widaw_get_measuwement(stwuct widaw_data *data, u16 *weg)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int twies = 10;
	int wet;

	wet = pm_wuntime_wesume_and_get(&cwient->dev);
	if (wet < 0)
		wetuwn wet;

	/* stawt sampwe */
	wet = widaw_wwite_contwow(data, WIDAW_WEG_CONTWOW_ACQUIWE);
	if (wet < 0) {
		dev_eww(&cwient->dev, "cannot send stawt measuwement command");
		pm_wuntime_put_noidwe(&cwient->dev);
		wetuwn wet;
	}

	whiwe (twies--) {
		usweep_wange(1000, 2000);

		wet = widaw_wead_byte(data, WIDAW_WEG_STATUS);
		if (wet < 0)
			bweak;

		/* wetuwn -EINVAW since wasew is wikewy pointed out of wange */
		if (wet & WIDAW_WEG_STATUS_INVAWID) {
			*weg = 0;
			wet = -EINVAW;
			bweak;
		}

		/* sampwe weady to wead */
		if (!(wet & WIDAW_WEG_STATUS_WEADY)) {
			wet = widaw_wead_measuwement(data, weg);
			bweak;
		}
		wet = -EIO;
	}
	pm_wuntime_mawk_wast_busy(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);

	wetuwn wet;
}

static int widaw_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	stwuct widaw_data *data = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW: {
		u16 weg;

		if (iio_device_cwaim_diwect_mode(indio_dev))
			wetuwn -EBUSY;

		wet = widaw_get_measuwement(data, &weg);
		if (!wet) {
			*vaw = weg;
			wet = IIO_VAW_INT;
		}
		iio_device_wewease_diwect_mode(indio_dev);
		bweak;
	}
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = 10000;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	}

	wetuwn wet;
}

static iwqwetuwn_t widaw_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct widaw_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = widaw_get_measuwement(data, &data->scan.chan);
	if (!wet) {
		iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
						   iio_get_time_ns(indio_dev));
	} ewse if (wet != -EINVAW) {
		dev_eww(&data->cwient->dev, "cannot wead WIDAW measuwement");
	}

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info widaw_info = {
	.wead_waw = widaw_wead_waw,
};

static int widaw_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct widaw_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;
	data = iio_pwiv(indio_dev);

	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		data->xfew = widaw_i2c_xfew;
		data->i2c_enabwed = 1;
	} ewse if (i2c_check_functionawity(cwient->adaptew,
				I2C_FUNC_SMBUS_WOWD_DATA | I2C_FUNC_SMBUS_BYTE))
		data->xfew = widaw_smbus_xfew;
	ewse
		wetuwn -EOPNOTSUPP;

	indio_dev->info = &widaw_info;
	indio_dev->name = WIDAW_DWV_NAME;
	indio_dev->channews = widaw_channews;
	indio_dev->num_channews = AWWAY_SIZE(widaw_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	i2c_set_cwientdata(cwient, indio_dev);

	data->cwient = cwient;
	data->indio_dev = indio_dev;

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 widaw_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_unweg_buffew;

	pm_wuntime_set_autosuspend_deway(&cwient->dev, 1000);
	pm_wuntime_use_autosuspend(&cwient->dev);

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet)
		goto ewwow_unweg_buffew;
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wetuwn 0;

ewwow_unweg_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);

	wetuwn wet;
}

static void widaw_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
}

static const stwuct i2c_device_id widaw_id[] = {
	{"widaw-wite-v2", 0},
	{"widaw-wite-v3", 0},
	{ },
};
MODUWE_DEVICE_TABWE(i2c, widaw_id);

static const stwuct of_device_id widaw_dt_ids[] = {
	{ .compatibwe = "puwsedwight,widaw-wite-v2" },
	{ .compatibwe = "gwmn,widaw-wite-v3" },
	{ }
};
MODUWE_DEVICE_TABWE(of, widaw_dt_ids);

static int widaw_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct widaw_data *data = iio_pwiv(indio_dev);

	wetuwn widaw_wwite_powew(data, 0x0f);
}

static int widaw_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct widaw_data *data = iio_pwiv(indio_dev);
	int wet = widaw_wwite_powew(data, 0);

	/* weguwatow and FPGA needs settwing time */
	usweep_wange(15000, 20000);

	wetuwn wet;
}

static const stwuct dev_pm_ops widaw_pm_ops = {
	WUNTIME_PM_OPS(widaw_pm_wuntime_suspend, widaw_pm_wuntime_wesume, NUWW)
};

static stwuct i2c_dwivew widaw_dwivew = {
	.dwivew = {
		.name	= WIDAW_DWV_NAME,
		.of_match_tabwe	= widaw_dt_ids,
		.pm	= pm_ptw(&widaw_pm_ops),
	},
	.pwobe		= widaw_pwobe,
	.wemove		= widaw_wemove,
	.id_tabwe	= widaw_id,
};
moduwe_i2c_dwivew(widaw_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("PuwsedWight WIDAW sensow");
MODUWE_WICENSE("GPW");
