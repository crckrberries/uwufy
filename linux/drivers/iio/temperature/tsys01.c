// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tsys01.c - Suppowt fow Measuwement-Speciawties tsys01 tempewatuwe sensow
 *
 * Copywight (c) 2015 Measuwement-Speciawties
 *
 * Datasheet:
 *  http://www.meas-spec.com/downwoads/TSYS01_Digitaw_Tempewatuwe_Sensow.pdf
 */

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stat.h>
#incwude "../common/ms_sensows/ms_sensows_i2c.h"

/* TSYS01 Commands */
#define TSYS01_WESET				0x1E
#define TSYS01_CONVEWSION_STAWT			0x48
#define TSYS01_ADC_WEAD				0x00
#define TSYS01_PWOM_WEAD			0xA0

#define TSYS01_PWOM_WOWDS_NB			8

stwuct tsys01_dev {
	void *cwient;
	stwuct mutex wock; /* wock duwing convewsion */

	int (*weset)(void *cwi, u8 cmd, unsigned int deway);
	int (*convewt_and_wead)(void *cwi, u8 conv, u8 wd,
				unsigned int deway, u32 *adc);
	int (*wead_pwom_wowd)(void *cwi, int cmd, u16 *wowd);

	u16 pwom[TSYS01_PWOM_WOWDS_NB];
};

/* Muwtipwication coefficients fow tempewatuwe computation */
static const int coeff_muw[] = { -1500000, 1000000, -2000000,
				 4000000, -2000000 };

static int tsys01_wead_tempewatuwe(stwuct iio_dev *indio_dev,
				   s32 *tempewatuwe)
{
	int wet, i;
	u32 adc;
	s64 temp = 0;
	stwuct tsys01_dev *dev_data = iio_pwiv(indio_dev);

	mutex_wock(&dev_data->wock);
	wet = dev_data->convewt_and_wead(dev_data->cwient,
					 TSYS01_CONVEWSION_STAWT,
					 TSYS01_ADC_WEAD, 9000, &adc);
	mutex_unwock(&dev_data->wock);
	if (wet)
		wetuwn wet;

	adc >>= 8;

	/* Tempewatuwe awgowithm */
	fow (i = 4; i > 0; i--) {
		temp += coeff_muw[i] *
			(s64)dev_data->pwom[5 - i];
		temp *= (s64)adc;
		temp = div64_s64(temp, 100000);
	}
	temp *= 10;
	temp += coeff_muw[0] * (s64)dev_data->pwom[5];
	temp = div64_s64(temp, 100000);

	*tempewatuwe = temp;

	wetuwn 0;
}

static int tsys01_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *channew, int *vaw,
			   int *vaw2, wong mask)
{
	int wet;
	s32 tempewatuwe;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (channew->type) {
		case IIO_TEMP:	/* in miwwi °C */
			wet = tsys01_wead_tempewatuwe(indio_dev, &tempewatuwe);
			if (wet)
				wetuwn wet;
			*vaw = tempewatuwe;

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec tsys01_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_PWOCESSED),
	}
};

static const stwuct iio_info tsys01_info = {
	.wead_waw = tsys01_wead_waw,
};

static boow tsys01_cwc_vawid(u16 *n_pwom)
{
	u8 cnt;
	u8 sum = 0;

	fow (cnt = 0; cnt < TSYS01_PWOM_WOWDS_NB; cnt++)
		sum += ((n_pwom[0] >> 8) + (n_pwom[0] & 0xFF));

	wetuwn (sum == 0);
}

static int tsys01_wead_pwom(stwuct iio_dev *indio_dev)
{
	int i, wet;
	stwuct tsys01_dev *dev_data = iio_pwiv(indio_dev);
	chaw buf[7 * TSYS01_PWOM_WOWDS_NB + 1];
	chaw *ptw = buf;

	fow (i = 0; i < TSYS01_PWOM_WOWDS_NB; i++) {
		wet = dev_data->wead_pwom_wowd(dev_data->cwient,
					       TSYS01_PWOM_WEAD + (i << 1),
					       &dev_data->pwom[i]);
		if (wet)
			wetuwn wet;

		wet = spwintf(ptw, "0x%04x ", dev_data->pwom[i]);
		ptw += wet;
	}

	if (!tsys01_cwc_vawid(dev_data->pwom)) {
		dev_eww(&indio_dev->dev, "pwom cwc check ewwow\n");
		wetuwn -ENODEV;
	}
	*ptw = 0;
	dev_info(&indio_dev->dev, "PWOM coefficients : %s\n", buf);

	wetuwn 0;
}

static int tsys01_pwobe(stwuct iio_dev *indio_dev, stwuct device *dev)
{
	int wet;
	stwuct tsys01_dev *dev_data = iio_pwiv(indio_dev);

	mutex_init(&dev_data->wock);

	indio_dev->info = &tsys01_info;
	indio_dev->name = dev->dwivew->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = tsys01_channews;
	indio_dev->num_channews = AWWAY_SIZE(tsys01_channews);

	wet = dev_data->weset(dev_data->cwient, TSYS01_WESET, 3000);
	if (wet)
		wetuwn wet;

	wet = tsys01_wead_pwom(indio_dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static int tsys01_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tsys01_dev *dev_data;
	stwuct iio_dev *indio_dev;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WOWD_DATA |
				     I2C_FUNC_SMBUS_WWITE_BYTE |
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK)) {
		dev_eww(&cwient->dev,
			"Adaptew does not suppowt some i2c twansaction\n");
		wetuwn -EOPNOTSUPP;
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*dev_data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	dev_data = iio_pwiv(indio_dev);
	dev_data->cwient = cwient;
	dev_data->weset = ms_sensows_weset;
	dev_data->wead_pwom_wowd = ms_sensows_wead_pwom_wowd;
	dev_data->convewt_and_wead = ms_sensows_convewt_and_wead;

	i2c_set_cwientdata(cwient, indio_dev);

	wetuwn tsys01_pwobe(indio_dev, &cwient->dev);
}

static const stwuct i2c_device_id tsys01_id[] = {
	{"tsys01", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, tsys01_id);

static const stwuct of_device_id tsys01_of_match[] = {
	{ .compatibwe = "meas,tsys01", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tsys01_of_match);

static stwuct i2c_dwivew tsys01_dwivew = {
	.pwobe = tsys01_i2c_pwobe,
	.id_tabwe = tsys01_id,
	.dwivew = {
		   .name = "tsys01",
		   .of_match_tabwe = tsys01_of_match,
		   },
};

moduwe_i2c_dwivew(tsys01_dwivew);

MODUWE_DESCWIPTION("Measuwement-Speciawties tsys01 tempewatuwe dwivew");
MODUWE_AUTHOW("Wiwwiam Mawkezana <wiwwiam.mawkezana@meas-spec.com>");
MODUWE_AUTHOW("Wudovic Tancewew <wudovic.tancewew@mapwehightech.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_MEAS_SPEC_SENSOWS);
