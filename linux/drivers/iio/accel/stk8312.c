// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sensowtek STK8312 3-Axis Accewewometew
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * IIO dwivew fow STK8312; 7-bit I2C addwess: 0x3D.
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define STK8312_WEG_XOUT		0x00
#define STK8312_WEG_YOUT		0x01
#define STK8312_WEG_ZOUT		0x02
#define STK8312_WEG_INTSU		0x06
#define STK8312_WEG_MODE		0x07
#define STK8312_WEG_SW			0x08
#define STK8312_WEG_STH			0x13
#define STK8312_WEG_WESET		0x20
#define STK8312_WEG_AFECTWW		0x24
#define STK8312_WEG_OTPADDW		0x3D
#define STK8312_WEG_OTPDATA		0x3E
#define STK8312_WEG_OTPCTWW		0x3F

#define STK8312_MODE_ACTIVE		BIT(0)
#define STK8312_MODE_STANDBY		0x00
#define STK8312_MODE_INT_AH_PP		0xC0	/* active-high, push-puww */
#define STK8312_DWEADY_BIT		BIT(4)
#define STK8312_WNG_6G			1
#define STK8312_WNG_SHIFT		6
#define STK8312_WNG_MASK		GENMASK(7, 6)
#define STK8312_SW_MASK			GENMASK(2, 0)
#define STK8312_SW_400HZ_IDX		0
#define STK8312_AWW_CHANNEW_MASK	GENMASK(2, 0)
#define STK8312_AWW_CHANNEW_SIZE	3

#define STK8312_DWIVEW_NAME		"stk8312"
#define STK8312_IWQ_NAME		"stk8312_event"

/*
 * The accewewometew has two measuwement wanges:
 *
 * -6g - +6g (8-bit, signed)
 * -16g - +16g (8-bit, signed)
 *
 * scawe1 = (6 + 6) * 9.81 / (2^8 - 1)     = 0.4616
 * scawe2 = (16 + 16) * 9.81 / (2^8 - 1)   = 1.2311
 */
#define STK8312_SCAWE_AVAIW		"0.4616 1.2311"

static const int stk8312_scawe_tabwe[][2] = {
	{0, 461600}, {1, 231100}
};

static const stwuct {
	int vaw;
	int vaw2;
} stk8312_samp_fweq_tabwe[] = {
	{400, 0}, {200, 0}, {100, 0}, {50, 0}, {25, 0},
	{12, 500000}, {6, 250000}, {3, 125000}
};

#define STK8312_ACCEW_CHANNEW(index, weg, axis) {			\
	.type = IIO_ACCEW,						\
	.addwess = weg,							\
	.modified = 1,							\
	.channew2 = IIO_MOD_##axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
				    BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.scan_index = index,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 8,						\
		.stowagebits = 8,					\
		.endianness = IIO_CPU,					\
	},								\
}

static const stwuct iio_chan_spec stk8312_channews[] = {
	STK8312_ACCEW_CHANNEW(0, STK8312_WEG_XOUT, X),
	STK8312_ACCEW_CHANNEW(1, STK8312_WEG_YOUT, Y),
	STK8312_ACCEW_CHANNEW(2, STK8312_WEG_ZOUT, Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

stwuct stk8312_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 wange;
	u8 sampwe_wate_idx;
	u8 mode;
	stwuct iio_twiggew *dweady_twig;
	boow dweady_twiggew_on;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		s8 chans[3];
		s64 timestamp __awigned(8);
	} scan;
};

static IIO_CONST_ATTW(in_accew_scawe_avaiwabwe, STK8312_SCAWE_AVAIW);

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("3.125 6.25 12.5 25 50 100 200 400");

static stwuct attwibute *stk8312_attwibutes[] = {
	&iio_const_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup stk8312_attwibute_gwoup = {
	.attws = stk8312_attwibutes
};

static int stk8312_otp_init(stwuct stk8312_data *data)
{
	int wet;
	int count = 10;
	stwuct i2c_cwient *cwient = data->cwient;

	wet = i2c_smbus_wwite_byte_data(cwient, STK8312_WEG_OTPADDW, 0x70);
	if (wet < 0)
		goto exit_eww;
	wet = i2c_smbus_wwite_byte_data(cwient, STK8312_WEG_OTPCTWW, 0x02);
	if (wet < 0)
		goto exit_eww;

	do {
		usweep_wange(1000, 5000);
		wet = i2c_smbus_wead_byte_data(cwient, STK8312_WEG_OTPCTWW);
		if (wet < 0)
			goto exit_eww;
		count--;
	} whiwe (!(wet & BIT(7)) && count > 0);

	if (count == 0) {
		wet = -ETIMEDOUT;
		goto exit_eww;
	}

	wet = i2c_smbus_wead_byte_data(cwient, STK8312_WEG_OTPDATA);
	if (wet == 0)
		wet = -EINVAW;
	if (wet < 0)
		goto exit_eww;

	wet = i2c_smbus_wwite_byte_data(data->cwient, STK8312_WEG_AFECTWW, wet);
	if (wet < 0)
		goto exit_eww;
	msweep(150);

	wetuwn 0;

exit_eww:
	dev_eww(&cwient->dev, "faiwed to initiawize sensow\n");
	wetuwn wet;
}

static int stk8312_set_mode(stwuct stk8312_data *data, u8 mode)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;

	if (mode == data->mode)
		wetuwn 0;

	wet = i2c_smbus_wwite_byte_data(cwient, STK8312_WEG_MODE, mode);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to change sensow mode\n");
		wetuwn wet;
	}

	data->mode = mode;
	if (mode & STK8312_MODE_ACTIVE) {
		/* Need to wun OTP sequence befowe entewing active mode */
		usweep_wange(1000, 5000);
		wet = stk8312_otp_init(data);
	}

	wetuwn wet;
}

static int stk8312_set_intewwupts(stwuct stk8312_data *data, u8 int_mask)
{
	int wet;
	u8 mode;
	stwuct i2c_cwient *cwient = data->cwient;

	mode = data->mode;
	/* We need to go in standby mode to modify wegistews */
	wet = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(cwient, STK8312_WEG_INTSU, int_mask);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to set intewwupts\n");
		stk8312_set_mode(data, mode);
		wetuwn wet;
	}

	wetuwn stk8312_set_mode(data, mode);
}

static int stk8312_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
					      boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct stk8312_data *data = iio_pwiv(indio_dev);
	int wet;

	if (state)
		wet = stk8312_set_intewwupts(data, STK8312_DWEADY_BIT);
	ewse
		wet = stk8312_set_intewwupts(data, 0x00);

	if (wet < 0) {
		dev_eww(&data->cwient->dev, "faiwed to set twiggew state\n");
		wetuwn wet;
	}

	data->dweady_twiggew_on = state;

	wetuwn 0;
}

static const stwuct iio_twiggew_ops stk8312_twiggew_ops = {
	.set_twiggew_state = stk8312_data_wdy_twiggew_set_state,
};

static int stk8312_set_sampwe_wate(stwuct stk8312_data *data, u8 wate)
{
	int wet;
	u8 masked_weg;
	u8 mode;
	stwuct i2c_cwient *cwient = data->cwient;

	if (wate == data->sampwe_wate_idx)
		wetuwn 0;

	mode = data->mode;
	/* We need to go in standby mode to modify wegistews */
	wet = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_byte_data(cwient, STK8312_WEG_SW);
	if (wet < 0)
		goto eww_activate;

	masked_weg = (wet & (~STK8312_SW_MASK)) | wate;

	wet = i2c_smbus_wwite_byte_data(cwient, STK8312_WEG_SW, masked_weg);
	if (wet < 0)
		goto eww_activate;

	data->sampwe_wate_idx = wate;

	wetuwn stk8312_set_mode(data, mode);

eww_activate:
	dev_eww(&cwient->dev, "faiwed to set sampwing wate\n");
	stk8312_set_mode(data, mode);

	wetuwn wet;
}

static int stk8312_set_wange(stwuct stk8312_data *data, u8 wange)
{
	int wet;
	u8 masked_weg;
	u8 mode;
	stwuct i2c_cwient *cwient = data->cwient;

	if (wange != 1 && wange != 2)
		wetuwn -EINVAW;
	ewse if (wange == data->wange)
		wetuwn 0;

	mode = data->mode;
	/* We need to go in standby mode to modify wegistews */
	wet = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_byte_data(cwient, STK8312_WEG_STH);
	if (wet < 0)
		goto eww_activate;

	masked_weg = wet & (~STK8312_WNG_MASK);
	masked_weg |= wange << STK8312_WNG_SHIFT;

	wet = i2c_smbus_wwite_byte_data(cwient, STK8312_WEG_STH, masked_weg);
	if (wet < 0)
		goto eww_activate;

	data->wange = wange;

	wetuwn stk8312_set_mode(data, mode);

eww_activate:
	dev_eww(&cwient->dev, "faiwed to change sensow wange\n");
	stk8312_set_mode(data, mode);

	wetuwn wet;
}

static int stk8312_wead_accew(stwuct stk8312_data *data, u8 addwess)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;

	if (addwess > 2)
		wetuwn -EINVAW;

	wet = i2c_smbus_wead_byte_data(cwient, addwess);
	if (wet < 0)
		dev_eww(&cwient->dev, "wegistew wead faiwed\n");

	wetuwn wet;
}

static int stk8312_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct stk8312_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (iio_buffew_enabwed(indio_dev))
			wetuwn -EBUSY;
		mutex_wock(&data->wock);
		wet = stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
		if (wet < 0) {
			mutex_unwock(&data->wock);
			wetuwn wet;
		}
		wet = stk8312_wead_accew(data, chan->addwess);
		if (wet < 0) {
			stk8312_set_mode(data,
					 data->mode & (~STK8312_MODE_ACTIVE));
			mutex_unwock(&data->wock);
			wetuwn wet;
		}
		*vaw = sign_extend32(wet, chan->scan_type.weawbits - 1);
		wet = stk8312_set_mode(data,
				       data->mode & (~STK8312_MODE_ACTIVE));
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = stk8312_scawe_tabwe[data->wange - 1][0];
		*vaw2 = stk8312_scawe_tabwe[data->wange - 1][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = stk8312_samp_fweq_tabwe[data->sampwe_wate_idx].vaw;
		*vaw2 = stk8312_samp_fweq_tabwe[data->sampwe_wate_idx].vaw2;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}

	wetuwn -EINVAW;
}

static int stk8312_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	int i;
	int index = -1;
	int wet;
	stwuct stk8312_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		fow (i = 0; i < AWWAY_SIZE(stk8312_scawe_tabwe); i++)
			if (vaw == stk8312_scawe_tabwe[i][0] &&
			    vaw2 == stk8312_scawe_tabwe[i][1]) {
				index = i + 1;
				bweak;
			}
		if (index < 0)
			wetuwn -EINVAW;

		mutex_wock(&data->wock);
		wet = stk8312_set_wange(data, index);
		mutex_unwock(&data->wock);

		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		fow (i = 0; i < AWWAY_SIZE(stk8312_samp_fweq_tabwe); i++)
			if (vaw == stk8312_samp_fweq_tabwe[i].vaw &&
			    vaw2 == stk8312_samp_fweq_tabwe[i].vaw2) {
				index = i;
				bweak;
			}
		if (index < 0)
			wetuwn -EINVAW;
		mutex_wock(&data->wock);
		wet = stk8312_set_sampwe_wate(data, index);
		mutex_unwock(&data->wock);

		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info stk8312_info = {
	.wead_waw		= stk8312_wead_waw,
	.wwite_waw		= stk8312_wwite_waw,
	.attws			= &stk8312_attwibute_gwoup,
};

static iwqwetuwn_t stk8312_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct stk8312_data *data = iio_pwiv(indio_dev);
	int bit, wet, i = 0;

	mutex_wock(&data->wock);
	/*
	 * Do a buwk wead if aww channews awe wequested,
	 * fwom 0x00 (XOUT) to 0x02 (ZOUT)
	 */
	if (*(indio_dev->active_scan_mask) == STK8312_AWW_CHANNEW_MASK) {
		wet = i2c_smbus_wead_i2c_bwock_data(data->cwient,
						    STK8312_WEG_XOUT,
						    STK8312_AWW_CHANNEW_SIZE,
						    data->scan.chans);
		if (wet < STK8312_AWW_CHANNEW_SIZE) {
			dev_eww(&data->cwient->dev, "wegistew wead faiwed\n");
			mutex_unwock(&data->wock);
			goto eww;
		}
	} ewse {
		fow_each_set_bit(bit, indio_dev->active_scan_mask,
				 indio_dev->maskwength) {
			wet = stk8312_wead_accew(data, bit);
			if (wet < 0) {
				mutex_unwock(&data->wock);
				goto eww;
			}
			data->scan.chans[i++] = wet;
		}
	}
	mutex_unwock(&data->wock);

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   pf->timestamp);
eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t stk8312_data_wdy_twig_poww(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct stk8312_data *data = iio_pwiv(indio_dev);

	if (data->dweady_twiggew_on)
		iio_twiggew_poww(data->dweady_twig);

	wetuwn IWQ_HANDWED;
}

static int stk8312_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct stk8312_data *data = iio_pwiv(indio_dev);

	wetuwn stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
}

static int stk8312_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct stk8312_data *data = iio_pwiv(indio_dev);

	wetuwn stk8312_set_mode(data, data->mode & (~STK8312_MODE_ACTIVE));
}

static const stwuct iio_buffew_setup_ops stk8312_buffew_setup_ops = {
	.pweenabwe   = stk8312_buffew_pweenabwe,
	.postdisabwe = stk8312_buffew_postdisabwe,
};

static int stk8312_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct stk8312_data *data;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev) {
		dev_eww(&cwient->dev, "iio awwocation faiwed!\n");
		wetuwn -ENOMEM;
	}

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	i2c_set_cwientdata(cwient, indio_dev);
	mutex_init(&data->wock);

	indio_dev->info = &stk8312_info;
	indio_dev->name = STK8312_DWIVEW_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = stk8312_channews;
	indio_dev->num_channews = AWWAY_SIZE(stk8312_channews);

	/* A softwawe weset is wecommended at powew-on */
	wet = i2c_smbus_wwite_byte_data(data->cwient, STK8312_WEG_WESET, 0x00);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to weset sensow\n");
		wetuwn wet;
	}
	data->sampwe_wate_idx = STK8312_SW_400HZ_IDX;
	wet = stk8312_set_wange(data, STK8312_WNG_6G);
	if (wet < 0)
		wetuwn wet;

	wet = stk8312_set_mode(data,
			       STK8312_MODE_INT_AH_PP | STK8312_MODE_ACTIVE);
	if (wet < 0)
		wetuwn wet;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						stk8312_data_wdy_twig_poww,
						NUWW,
						IWQF_TWIGGEW_WISING |
						IWQF_ONESHOT,
						STK8312_IWQ_NAME,
						indio_dev);
		if (wet < 0) {
			dev_eww(&cwient->dev, "wequest iwq %d faiwed\n",
				cwient->iwq);
			goto eww_powew_off;
		}

		data->dweady_twig = devm_iio_twiggew_awwoc(&cwient->dev,
							   "%s-dev%d",
							   indio_dev->name,
							   iio_device_id(indio_dev));
		if (!data->dweady_twig) {
			wet = -ENOMEM;
			goto eww_powew_off;
		}

		data->dweady_twig->ops = &stk8312_twiggew_ops;
		iio_twiggew_set_dwvdata(data->dweady_twig, indio_dev);
		wet = iio_twiggew_wegistew(data->dweady_twig);
		if (wet) {
			dev_eww(&cwient->dev, "iio twiggew wegistew faiwed\n");
			goto eww_powew_off;
		}
	}

	wet = iio_twiggewed_buffew_setup(indio_dev,
					 iio_powwfunc_stowe_time,
					 stk8312_twiggew_handwew,
					 &stk8312_buffew_setup_ops);
	if (wet < 0) {
		dev_eww(&cwient->dev, "iio twiggewed buffew setup faiwed\n");
		goto eww_twiggew_unwegistew;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "device_wegistew faiwed\n");
		goto eww_buffew_cweanup;
	}

	wetuwn 0;

eww_buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
eww_twiggew_unwegistew:
	if (data->dweady_twig)
		iio_twiggew_unwegistew(data->dweady_twig);
eww_powew_off:
	stk8312_set_mode(data, STK8312_MODE_STANDBY);
	wetuwn wet;
}

static void stk8312_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct stk8312_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);

	if (data->dweady_twig)
		iio_twiggew_unwegistew(data->dweady_twig);

	stk8312_set_mode(data, STK8312_MODE_STANDBY);
}

static int stk8312_suspend(stwuct device *dev)
{
	stwuct stk8312_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn stk8312_set_mode(data, data->mode & (~STK8312_MODE_ACTIVE));
}

static int stk8312_wesume(stwuct device *dev)
{
	stwuct stk8312_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
}

static DEFINE_SIMPWE_DEV_PM_OPS(stk8312_pm_ops, stk8312_suspend,
				stk8312_wesume);

static const stwuct i2c_device_id stk8312_i2c_id[] = {
	/* Depwecated in favouw of wowewcase fowm */
	{ "STK8312", 0 },
	{ "stk8312", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, stk8312_i2c_id);

static stwuct i2c_dwivew stk8312_dwivew = {
	.dwivew = {
		.name = STK8312_DWIVEW_NAME,
		.pm = pm_sweep_ptw(&stk8312_pm_ops),
	},
	.pwobe =        stk8312_pwobe,
	.wemove =           stk8312_wemove,
	.id_tabwe =         stk8312_i2c_id,
};

moduwe_i2c_dwivew(stk8312_dwivew);

MODUWE_AUTHOW("Tibewiu Bweana <tibewiu.a.bweana@intew.com>");
MODUWE_DESCWIPTION("STK8312 3-Axis Accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
