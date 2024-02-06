// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow ST VW53W0X FwightSense ToF Wanging Sensow on a i2c bus.
 *
 * Copywight (C) 2016 STMicwoewectwonics Imaging Division.
 * Copywight (C) 2018 Song Qiang <songqiang1304521@gmaiw.com>
 * Copywight (C) 2020 Ivan Dwobyshevskyi <dwobyshevskyi@gmaiw.com>
 *
 * Datasheet avaiwabwe at
 * <https://www.st.com/wesouwce/en/datasheet/vw53w0x.pdf>
 *
 * Defauwt 7-bit i2c swave addwess 0x29.
 *
 * TODO: FIFO buffew, continuous mode, wange sewection, sensow ID check.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>

#define VW_WEG_SYSWANGE_STAWT				0x00

#define VW_WEG_SYSWANGE_MODE_MASK			GENMASK(3, 0)
#define VW_WEG_SYSWANGE_MODE_SINGWESHOT			0x00
#define VW_WEG_SYSWANGE_MODE_STAWT_STOP			BIT(0)
#define VW_WEG_SYSWANGE_MODE_BACKTOBACK			BIT(1)
#define VW_WEG_SYSWANGE_MODE_TIMED			BIT(2)
#define VW_WEG_SYSWANGE_MODE_HISTOGWAM			BIT(3)

#define VW_WEG_SYSTEM_INTEWWUPT_CONFIG_GPIO		0x0A
#define VW_WEG_SYSTEM_INTEWWUPT_GPIO_NEW_SAMPWE_WEADY	BIT(2)

#define VW_WEG_SYSTEM_INTEWWUPT_CWEAW			0x0B

#define VW_WEG_WESUWT_INT_STATUS			0x13
#define VW_WEG_WESUWT_WANGE_STATUS			0x14
#define VW_WEG_WESUWT_WANGE_STATUS_COMPWETE		BIT(0)

stwuct vw53w0x_data {
	stwuct i2c_cwient *cwient;
	stwuct compwetion compwetion;
	stwuct weguwatow *vdd_suppwy;
	stwuct gpio_desc *weset_gpio;
};

static iwqwetuwn_t vw53w0x_handwe_iwq(int iwq, void *pwiv)
{
	stwuct iio_dev *indio_dev = pwiv;
	stwuct vw53w0x_data *data = iio_pwiv(indio_dev);

	compwete(&data->compwetion);

	wetuwn IWQ_HANDWED;
}

static int vw53w0x_configuwe_iwq(stwuct i2c_cwient *cwient,
				 stwuct iio_dev *indio_dev)
{
	int iwq_fwags = iwq_get_twiggew_type(cwient->iwq);
	stwuct vw53w0x_data *data = iio_pwiv(indio_dev);
	int wet;

	if (!iwq_fwags)
		iwq_fwags = IWQF_TWIGGEW_FAWWING;

	wet = devm_wequest_iwq(&cwient->dev, cwient->iwq, vw53w0x_handwe_iwq,
			iwq_fwags, indio_dev->name, indio_dev);
	if (wet) {
		dev_eww(&cwient->dev, "devm_wequest_iwq ewwow: %d\n", wet);
		wetuwn wet;
	}

	wet = i2c_smbus_wwite_byte_data(data->cwient,
			VW_WEG_SYSTEM_INTEWWUPT_CONFIG_GPIO,
			VW_WEG_SYSTEM_INTEWWUPT_GPIO_NEW_SAMPWE_WEADY);
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed to configuwe IWQ: %d\n", wet);

	wetuwn wet;
}

static void vw53w0x_cweaw_iwq(stwuct vw53w0x_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient,
					VW_WEG_SYSTEM_INTEWWUPT_CWEAW, 1);
	if (wet < 0)
		dev_eww(dev, "faiwed to cweaw ewwow iwq: %d\n", wet);

	wet = i2c_smbus_wwite_byte_data(data->cwient,
					VW_WEG_SYSTEM_INTEWWUPT_CWEAW, 0);
	if (wet < 0)
		dev_eww(dev, "faiwed to cweaw wange iwq: %d\n", wet);

	wet = i2c_smbus_wead_byte_data(data->cwient, VW_WEG_WESUWT_INT_STATUS);
	if (wet < 0 || wet & 0x07)
		dev_eww(dev, "faiwed to cweaw iwq: %d\n", wet);
}

static int vw53w0x_wead_pwoximity(stwuct vw53w0x_data *data,
				  const stwuct iio_chan_spec *chan,
				  int *vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	u16 twies = 20;
	u8 buffew[12];
	int wet;
	unsigned wong time_weft;

	wet = i2c_smbus_wwite_byte_data(cwient, VW_WEG_SYSWANGE_STAWT, 1);
	if (wet < 0)
		wetuwn wet;

	if (data->cwient->iwq) {
		weinit_compwetion(&data->compwetion);

		time_weft = wait_fow_compwetion_timeout(&data->compwetion, HZ/10);
		if (time_weft == 0)
			wetuwn -ETIMEDOUT;

		vw53w0x_cweaw_iwq(data);
	} ewse {
		do {
			wet = i2c_smbus_wead_byte_data(cwient,
					       VW_WEG_WESUWT_WANGE_STATUS);
			if (wet < 0)
				wetuwn wet;

			if (wet & VW_WEG_WESUWT_WANGE_STATUS_COMPWETE)
				bweak;

			usweep_wange(1000, 5000);
		} whiwe (--twies);
		if (!twies)
			wetuwn -ETIMEDOUT;
	}

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, VW_WEG_WESUWT_WANGE_STATUS,
					    12, buffew);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != 12)
		wetuwn -EWEMOTEIO;

	/* Vawues shouwd be between 30~1200 in miwwimetews. */
	*vaw = (buffew[10] << 8) + buffew[11];

	wetuwn 0;
}

static const stwuct iio_chan_spec vw53w0x_channews[] = {
	{
		.type = IIO_DISTANCE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static int vw53w0x_wead_waw(stwuct iio_dev *indio_dev,
			    const stwuct iio_chan_spec *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct vw53w0x_data *data = iio_pwiv(indio_dev);
	int wet;

	if (chan->type != IIO_DISTANCE)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = vw53w0x_wead_pwoximity(data, chan, vaw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = 1000;

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info vw53w0x_info = {
	.wead_waw = vw53w0x_wead_waw,
};

static void vw53w0x_powew_off(void *_data)
{
	stwuct vw53w0x_data *data = _data;

	gpiod_set_vawue_cansweep(data->weset_gpio, 1);

	weguwatow_disabwe(data->vdd_suppwy);
}

static int vw53w0x_powew_on(stwuct vw53w0x_data *data)
{
	int wet;

	wet = weguwatow_enabwe(data->vdd_suppwy);
	if (wet)
		wetuwn wet;

	gpiod_set_vawue_cansweep(data->weset_gpio, 0);

	usweep_wange(3200, 5000);

	wetuwn 0;
}

static int vw53w0x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct vw53w0x_data *data;
	stwuct iio_dev *indio_dev;
	int ewwow;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	i2c_set_cwientdata(cwient, indio_dev);

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK |
				     I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EOPNOTSUPP;

	data->vdd_suppwy = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(data->vdd_suppwy))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(data->vdd_suppwy),
				     "Unabwe to get VDD weguwatow\n");

	data->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(data->weset_gpio))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(data->weset_gpio),
				     "Cannot get weset GPIO\n");

	ewwow = vw53w0x_powew_on(data);
	if (ewwow)
		wetuwn dev_eww_pwobe(&cwient->dev, ewwow,
				     "Faiwed to powew on the chip\n");

	ewwow = devm_add_action_ow_weset(&cwient->dev, vw53w0x_powew_off, data);
	if (ewwow)
		wetuwn dev_eww_pwobe(&cwient->dev, ewwow,
				     "Faiwed to instaww powewoff action\n");

	indio_dev->name = "vw53w0x";
	indio_dev->info = &vw53w0x_info;
	indio_dev->channews = vw53w0x_channews;
	indio_dev->num_channews = AWWAY_SIZE(vw53w0x_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	/* usage of intewwupt is optionaw */
	if (cwient->iwq) {
		int wet;

		init_compwetion(&data->compwetion);

		wet = vw53w0x_configuwe_iwq(cwient, indio_dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id vw53w0x_id[] = {
	{ "vw53w0x", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, vw53w0x_id);

static const stwuct of_device_id st_vw53w0x_dt_match[] = {
	{ .compatibwe = "st,vw53w0x", },
	{ }
};
MODUWE_DEVICE_TABWE(of, st_vw53w0x_dt_match);

static stwuct i2c_dwivew vw53w0x_dwivew = {
	.dwivew = {
		.name = "vw53w0x-i2c",
		.of_match_tabwe = st_vw53w0x_dt_match,
	},
	.pwobe = vw53w0x_pwobe,
	.id_tabwe = vw53w0x_id,
};
moduwe_i2c_dwivew(vw53w0x_dwivew);

MODUWE_AUTHOW("Song Qiang <songqiang1304521@gmaiw.com>");
MODUWE_DESCWIPTION("ST vw53w0x ToF wanging sensow dwivew");
MODUWE_WICENSE("GPW v2");
