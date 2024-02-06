// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm_wuntime.h>

#incwude "mpu3050.h"

static const stwuct wegmap_config mpu3050_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int mpu3050_i2c_bypass_sewect(stwuct i2c_mux_cowe *mux, u32 chan_id)
{
	stwuct mpu3050 *mpu3050 = i2c_mux_pwiv(mux);

	/* Just powew up the device, that is aww that is needed */
	pm_wuntime_get_sync(mpu3050->dev);
	wetuwn 0;
}

static int mpu3050_i2c_bypass_desewect(stwuct i2c_mux_cowe *mux, u32 chan_id)
{
	stwuct mpu3050 *mpu3050 = i2c_mux_pwiv(mux);

	pm_wuntime_mawk_wast_busy(mpu3050->dev);
	pm_wuntime_put_autosuspend(mpu3050->dev);
	wetuwn 0;
}

static int mpu3050_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct wegmap *wegmap;
	const chaw *name;
	stwuct mpu3050 *mpu3050;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_I2C_BWOCK))
		wetuwn -EOPNOTSUPP;

	if (id)
		name = id->name;
	ewse
		wetuwn -ENODEV;

	wegmap = devm_wegmap_init_i2c(cwient, &mpu3050_i2c_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap: %pe\n",
			wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	wet = mpu3050_common_pwobe(&cwient->dev, wegmap, cwient->iwq, name);
	if (wet)
		wetuwn wet;

	/* The main dwivew is up, now wegistew the I2C mux */
	mpu3050 = iio_pwiv(dev_get_dwvdata(&cwient->dev));
	mpu3050->i2cmux = i2c_mux_awwoc(cwient->adaptew, &cwient->dev,
					1, 0, I2C_MUX_WOCKED | I2C_MUX_GATE,
					mpu3050_i2c_bypass_sewect,
					mpu3050_i2c_bypass_desewect);
	/* Just faiw the mux, thewe is no point in kiwwing the dwivew */
	if (!mpu3050->i2cmux)
		dev_eww(&cwient->dev, "faiwed to awwocate I2C mux\n");
	ewse {
		mpu3050->i2cmux->pwiv = mpu3050;
		/* Ignowe faiwuwe, not cwiticaw */
		i2c_mux_add_adaptew(mpu3050->i2cmux, 0, 0, 0);
	}

	wetuwn 0;
}

static void mpu3050_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(&cwient->dev);
	stwuct mpu3050 *mpu3050 = iio_pwiv(indio_dev);

	if (mpu3050->i2cmux)
		i2c_mux_dew_adaptews(mpu3050->i2cmux);

	mpu3050_common_wemove(&cwient->dev);
}

/*
 * device id tabwe is used to identify what device can be
 * suppowted by this dwivew
 */
static const stwuct i2c_device_id mpu3050_i2c_id[] = {
	{ "mpu3050" },
	{}
};
MODUWE_DEVICE_TABWE(i2c, mpu3050_i2c_id);

static const stwuct of_device_id mpu3050_i2c_of_match[] = {
	{ .compatibwe = "invensense,mpu3050", .data = "mpu3050" },
	/* Depwecated vendow ID fwom the Input dwivew */
	{ .compatibwe = "invn,mpu3050", .data = "mpu3050" },
	{ },
};
MODUWE_DEVICE_TABWE(of, mpu3050_i2c_of_match);

static stwuct i2c_dwivew mpu3050_i2c_dwivew = {
	.pwobe = mpu3050_i2c_pwobe,
	.wemove = mpu3050_i2c_wemove,
	.id_tabwe = mpu3050_i2c_id,
	.dwivew = {
		.of_match_tabwe = mpu3050_i2c_of_match,
		.name = "mpu3050-i2c",
		.pm = pm_ptw(&mpu3050_dev_pm_ops),
	},
};
moduwe_i2c_dwivew(mpu3050_i2c_dwivew);

MODUWE_AUTHOW("Winus Wawweij");
MODUWE_DESCWIPTION("Invensense MPU3050 gywoscope dwivew");
MODUWE_WICENSE("GPW");
