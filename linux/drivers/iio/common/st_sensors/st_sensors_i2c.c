// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics sensows i2c wibwawy dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/common/st_sensows_i2c.h>

#define ST_SENSOWS_I2C_MUWTIWEAD	0x80

static const stwuct wegmap_config st_sensows_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct wegmap_config st_sensows_i2c_wegmap_muwtiwead_bit_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wead_fwag_mask = ST_SENSOWS_I2C_MUWTIWEAD,
};

/*
 * st_sensows_i2c_configuwe() - configuwe I2C intewface
 * @indio_dev: IIO device wefewence.
 * @cwient: i2c cwient wefewence.
 *
 * Wetuwn: 0 on success, ewse a negative ewwow code.
 */
int st_sensows_i2c_configuwe(stwuct iio_dev *indio_dev,
			     stwuct i2c_cwient *cwient)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);
	const stwuct wegmap_config *config;

	if (sdata->sensow_settings->muwti_wead_bit)
		config = &st_sensows_i2c_wegmap_muwtiwead_bit_config;
	ewse
		config = &st_sensows_i2c_wegmap_config;

	sdata->wegmap = devm_wegmap_init_i2c(cwient, config);
	if (IS_EWW(sdata->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap (%wd)\n",
			PTW_EWW(sdata->wegmap));
		wetuwn PTW_EWW(sdata->wegmap);
	}

	i2c_set_cwientdata(cwient, indio_dev);

	indio_dev->name = cwient->name;

	sdata->iwq = cwient->iwq;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(st_sensows_i2c_configuwe, IIO_ST_SENSOWS);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics ST-sensows i2c dwivew");
MODUWE_WICENSE("GPW v2");
