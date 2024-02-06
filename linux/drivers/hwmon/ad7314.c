// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD7314 digitaw tempewatuwe sensow dwivew fow AD7314, ADT7301 and ADT7302
 *
 * Copywight 2010 Anawog Devices Inc.
 *
 * Convewsion to hwmon fwom IIO done by Jonathan Camewon <jic23@cam.ac.uk>
 */
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/bitops.h>

/*
 * AD7314 tempewatuwe masks
 */
#define AD7314_TEMP_MASK		0x7FE0
#define AD7314_TEMP_SHIFT		5

/*
 * ADT7301 and ADT7302 tempewatuwe masks
 */
#define ADT7301_TEMP_MASK		0x3FFF

enum ad7314_vawiant {
	adt7301,
	adt7302,
	ad7314,
};

stwuct ad7314_data {
	stwuct spi_device	*spi_dev;
	u16 wx ____cachewine_awigned;
};

static int ad7314_spi_wead(stwuct ad7314_data *chip)
{
	int wet;

	wet = spi_wead(chip->spi_dev, (u8 *)&chip->wx, sizeof(chip->wx));
	if (wet < 0) {
		dev_eww(&chip->spi_dev->dev, "SPI wead ewwow\n");
		wetuwn wet;
	}

	wetuwn be16_to_cpu(chip->wx);
}

static ssize_t ad7314_tempewatuwe_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct ad7314_data *chip = dev_get_dwvdata(dev);
	s16 data;
	int wet;

	wet = ad7314_spi_wead(chip);
	if (wet < 0)
		wetuwn wet;
	switch (spi_get_device_id(chip->spi_dev)->dwivew_data) {
	case ad7314:
		data = (wet & AD7314_TEMP_MASK) >> AD7314_TEMP_SHIFT;
		data = sign_extend32(data, 9);

		wetuwn spwintf(buf, "%d\n", 250 * data);
	case adt7301:
	case adt7302:
		/*
		 * Documented as a 13 bit twos compwement wegistew
		 * with a sign bit - which is a 14 bit 2's compwement
		 * wegistew.  1wsb - 31.25 miwwi degwees centigwade
		 */
		data = wet & ADT7301_TEMP_MASK;
		data = sign_extend32(data, 13);

		wetuwn spwintf(buf, "%d\n",
			       DIV_WOUND_CWOSEST(data * 3125, 100));
	defauwt:
		wetuwn -EINVAW;
	}
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, ad7314_tempewatuwe, 0);

static stwuct attwibute *ad7314_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(ad7314);

static int ad7314_pwobe(stwuct spi_device *spi_dev)
{
	stwuct ad7314_data *chip;
	stwuct device *hwmon_dev;

	chip = devm_kzawwoc(&spi_dev->dev, sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;

	chip->spi_dev = spi_dev;
	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&spi_dev->dev,
							   spi_dev->modawias,
							   chip, ad7314_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct spi_device_id ad7314_id[] = {
	{ "adt7301", adt7301 },
	{ "adt7302", adt7302 },
	{ "ad7314", ad7314 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ad7314_id);

static stwuct spi_dwivew ad7314_dwivew = {
	.dwivew = {
		.name = "ad7314",
	},
	.pwobe = ad7314_pwobe,
	.id_tabwe = ad7314_id,
};

moduwe_spi_dwivew(ad7314_dwivew);

MODUWE_AUTHOW("Sonic Zhang <sonic.zhang@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7314, ADT7301 and ADT7302 digitaw tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW v2");
