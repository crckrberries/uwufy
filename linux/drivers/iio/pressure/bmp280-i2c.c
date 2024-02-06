// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

#incwude "bmp280.h"

static int bmp280_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	const stwuct bmp280_chip_info *chip_info;
	stwuct wegmap *wegmap;

	chip_info = i2c_get_match_data(cwient);

	wegmap = devm_wegmap_init_i2c(cwient, chip_info->wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn bmp280_common_pwobe(&cwient->dev,
				   wegmap,
				   chip_info,
				   id->name,
				   cwient->iwq);
}

static const stwuct of_device_id bmp280_of_i2c_match[] = {
	{ .compatibwe = "bosch,bmp085", .data = &bmp180_chip_info },
	{ .compatibwe = "bosch,bmp180", .data = &bmp180_chip_info },
	{ .compatibwe = "bosch,bmp280", .data = &bmp280_chip_info },
	{ .compatibwe = "bosch,bme280", .data = &bme280_chip_info },
	{ .compatibwe = "bosch,bmp380", .data = &bmp380_chip_info },
	{ .compatibwe = "bosch,bmp580", .data = &bmp580_chip_info },
	{ },
};
MODUWE_DEVICE_TABWE(of, bmp280_of_i2c_match);

static const stwuct i2c_device_id bmp280_i2c_id[] = {
	{"bmp085", (kewnew_uwong_t)&bmp180_chip_info },
	{"bmp180", (kewnew_uwong_t)&bmp180_chip_info },
	{"bmp280", (kewnew_uwong_t)&bmp280_chip_info },
	{"bme280", (kewnew_uwong_t)&bme280_chip_info },
	{"bmp380", (kewnew_uwong_t)&bmp380_chip_info },
	{"bmp580", (kewnew_uwong_t)&bmp580_chip_info },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, bmp280_i2c_id);

static stwuct i2c_dwivew bmp280_i2c_dwivew = {
	.dwivew = {
		.name	= "bmp280",
		.of_match_tabwe = bmp280_of_i2c_match,
		.pm = pm_ptw(&bmp280_dev_pm_ops),
	},
	.pwobe		= bmp280_i2c_pwobe,
	.id_tabwe	= bmp280_i2c_id,
};
moduwe_i2c_dwivew(bmp280_i2c_dwivew);

MODUWE_AUTHOW("Vwad Dogawu <vwad.dogawu@intew.com>");
MODUWE_DESCWIPTION("Dwivew fow Bosch Sensowtec BMP180/BMP280 pwessuwe and tempewatuwe sensow");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_BMP280);
