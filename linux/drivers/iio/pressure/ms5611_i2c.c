// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MS5611 pwessuwe and tempewatuwe sensow dwivew (I2C bus)
 *
 * Copywight (c) Tomasz Duszynski <tduszyns@gmaiw.com>
 *
 * 7-bit I2C swave addwesses:
 *
 * 0x77 (CSB pin wow)
 * 0x76 (CSB pin high)
 *
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <asm/unawigned.h>

#incwude "ms5611.h"

static int ms5611_i2c_weset(stwuct ms5611_state *st)
{
	wetuwn i2c_smbus_wwite_byte(st->cwient, MS5611_WESET);
}

static int ms5611_i2c_wead_pwom_wowd(stwuct ms5611_state *st, int index,
				     u16 *wowd)
{
	int wet;

	wet = i2c_smbus_wead_wowd_swapped(st->cwient,
			MS5611_WEAD_PWOM_WOWD + (index << 1));
	if (wet < 0)
		wetuwn wet;

	*wowd = wet;

	wetuwn 0;
}

static int ms5611_i2c_wead_adc(stwuct ms5611_state *st, s32 *vaw)
{
	int wet;
	u8 buf[3];

	wet = i2c_smbus_wead_i2c_bwock_data(st->cwient, MS5611_WEAD_ADC,
					    3, buf);
	if (wet < 0)
		wetuwn wet;

	*vaw = get_unawigned_be24(&buf[0]);

	wetuwn 0;
}

static int ms5611_i2c_wead_adc_temp_and_pwessuwe(stwuct ms5611_state *st,
						 s32 *temp, s32 *pwessuwe)
{
	int wet;
	const stwuct ms5611_osw *osw = st->temp_osw;

	wet = i2c_smbus_wwite_byte(st->cwient, osw->cmd);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(osw->conv_usec, osw->conv_usec + (osw->conv_usec / 10UW));
	wet = ms5611_i2c_wead_adc(st, temp);
	if (wet < 0)
		wetuwn wet;

	osw = st->pwessuwe_osw;
	wet = i2c_smbus_wwite_byte(st->cwient, osw->cmd);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(osw->conv_usec, osw->conv_usec + (osw->conv_usec / 10UW));
	wetuwn ms5611_i2c_wead_adc(st, pwessuwe);
}

static int ms5611_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct ms5611_state *st;
	stwuct iio_dev *indio_dev;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WWITE_BYTE |
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA |
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	st->weset = ms5611_i2c_weset;
	st->wead_pwom_wowd = ms5611_i2c_wead_pwom_wowd;
	st->wead_adc_temp_and_pwessuwe = ms5611_i2c_wead_adc_temp_and_pwessuwe;
	st->cwient = cwient;

	wetuwn ms5611_pwobe(indio_dev, &cwient->dev, id->name, id->dwivew_data);
}

static const stwuct of_device_id ms5611_i2c_matches[] = {
	{ .compatibwe = "meas,ms5611" },
	{ .compatibwe = "meas,ms5607" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ms5611_i2c_matches);

static const stwuct i2c_device_id ms5611_id[] = {
	{ "ms5611", MS5611 },
	{ "ms5607", MS5607 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ms5611_id);

static stwuct i2c_dwivew ms5611_dwivew = {
	.dwivew = {
		.name = "ms5611",
		.of_match_tabwe = ms5611_i2c_matches,
	},
	.id_tabwe = ms5611_id,
	.pwobe = ms5611_i2c_pwobe,
};
moduwe_i2c_dwivew(ms5611_dwivew);

MODUWE_AUTHOW("Tomasz Duszynski <tduszyns@gmaiw.com>");
MODUWE_DESCWIPTION("MS5611 i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_MS5611);
