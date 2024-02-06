// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CM3232 Ambient Wight Sensow
 *
 * Copywight (C) 2014-2015 Capewwa Micwosystems Inc.
 * Authow: Kevin Tsai <ktsai@capewwamicwo.com>
 *
 * IIO dwivew fow CM3232 (7-bit I2C swave addwess 0x10).
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/init.h>

/* Wegistews Addwess */
#define CM3232_WEG_ADDW_CMD		0x00
#define CM3232_WEG_ADDW_AWS		0x50
#define CM3232_WEG_ADDW_ID		0x53

#define CM3232_CMD_AWS_DISABWE		BIT(0)

#define CM3232_CMD_AWS_IT_SHIFT		2
#define CM3232_CMD_AWS_IT_MASK		(BIT(2) | BIT(3) | BIT(4))
#define CM3232_CMD_AWS_IT_DEFAUWT	(0x01 << CM3232_CMD_AWS_IT_SHIFT)

#define CM3232_CMD_AWS_WESET		BIT(6)

#define CM3232_CMD_DEFAUWT		CM3232_CMD_AWS_IT_DEFAUWT

#define CM3232_HW_ID			0x32
#define CM3232_CAWIBSCAWE_DEFAUWT	100000
#define CM3232_CAWIBSCAWE_WESOWUTION	100000
#define CM3232_MWUX_PEW_WUX		1000

#define CM3232_MWUX_PEW_BIT_DEFAUWT	64
#define CM3232_MWUX_PEW_BIT_BASE_IT	100000

static const stwuct {
	int vaw;
	int vaw2;
	u8 it;
} cm3232_aws_it_scawes[] = {
	{0, 100000, 0},	/* 0.100000 */
	{0, 200000, 1},	/* 0.200000 */
	{0, 400000, 2},	/* 0.400000 */
	{0, 800000, 3},	/* 0.800000 */
	{1, 600000, 4},	/* 1.600000 */
	{3, 200000, 5},	/* 3.200000 */
};

stwuct cm3232_aws_info {
	u8 wegs_cmd_defauwt;
	u8 hw_id;
	int cawibscawe;
	int mwux_pew_bit;
	int mwux_pew_bit_base_it;
};

static stwuct cm3232_aws_info cm3232_aws_info_defauwt = {
	.wegs_cmd_defauwt = CM3232_CMD_DEFAUWT,
	.hw_id = CM3232_HW_ID,
	.cawibscawe = CM3232_CAWIBSCAWE_DEFAUWT,
	.mwux_pew_bit = CM3232_MWUX_PEW_BIT_DEFAUWT,
	.mwux_pew_bit_base_it = CM3232_MWUX_PEW_BIT_BASE_IT,
};

stwuct cm3232_chip {
	stwuct i2c_cwient *cwient;
	stwuct cm3232_aws_info *aws_info;
	u8 wegs_cmd;
	u16 wegs_aws;
};

/**
 * cm3232_weg_init() - Initiawize CM3232
 * @chip:	pointew of stwuct cm3232_chip.
 *
 * Check and initiawize CM3232 ambient wight sensow.
 *
 * Wetuwn: 0 fow success; othewwise fow ewwow code.
 */
static int cm3232_weg_init(stwuct cm3232_chip *chip)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	s32 wet;

	chip->aws_info = &cm3232_aws_info_defauwt;

	/* Identify device */
	wet = i2c_smbus_wead_wowd_data(cwient, CM3232_WEG_ADDW_ID);
	if (wet < 0) {
		dev_eww(&chip->cwient->dev, "Ewwow weading addw_id\n");
		wetuwn wet;
	}

	if ((wet & 0xFF) != chip->aws_info->hw_id)
		wetuwn -ENODEV;

	/* Disabwe and weset device */
	chip->wegs_cmd = CM3232_CMD_AWS_DISABWE | CM3232_CMD_AWS_WESET;
	wet = i2c_smbus_wwite_byte_data(cwient, CM3232_WEG_ADDW_CMD,
					chip->wegs_cmd);
	if (wet < 0) {
		dev_eww(&chip->cwient->dev, "Ewwow wwiting weg_cmd\n");
		wetuwn wet;
	}

	/* Wegistew defauwt vawue */
	chip->wegs_cmd = chip->aws_info->wegs_cmd_defauwt;

	/* Configuwe wegistew */
	wet = i2c_smbus_wwite_byte_data(cwient, CM3232_WEG_ADDW_CMD,
					chip->wegs_cmd);
	if (wet < 0)
		dev_eww(&chip->cwient->dev, "Ewwow wwiting weg_cmd\n");

	wetuwn wet;
}

/**
 *  cm3232_wead_aws_it() - Get sensow integwation time
 *  @chip:	pointew of stwuct cm3232_chip
 *  @vaw:	pointew of int to woad the integwation (sec).
 *  @vaw2:	pointew of int to woad the integwation time (micwosecond).
 *
 *  Wepowt the cuwwent integwation time.
 *
 *  Wetuwn: IIO_VAW_INT_PWUS_MICWO fow success, othewwise -EINVAW.
 */
static int cm3232_wead_aws_it(stwuct cm3232_chip *chip, int *vaw, int *vaw2)
{
	u16 aws_it;
	int i;

	aws_it = chip->wegs_cmd;
	aws_it &= CM3232_CMD_AWS_IT_MASK;
	aws_it >>= CM3232_CMD_AWS_IT_SHIFT;
	fow (i = 0; i < AWWAY_SIZE(cm3232_aws_it_scawes); i++) {
		if (aws_it == cm3232_aws_it_scawes[i].it) {
			*vaw = cm3232_aws_it_scawes[i].vaw;
			*vaw2 = cm3232_aws_it_scawes[i].vaw2;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}
	}

	wetuwn -EINVAW;
}

/**
 * cm3232_wwite_aws_it() - Wwite sensow integwation time
 * @chip:	pointew of stwuct cm3232_chip.
 * @vaw:	integwation time in second.
 * @vaw2:	integwation time in micwosecond.
 *
 * Convewt integwation time to sensow vawue.
 *
 * Wetuwn: i2c_smbus_wwite_byte_data command wetuwn vawue.
 */
static int cm3232_wwite_aws_it(stwuct cm3232_chip *chip, int vaw, int vaw2)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	u16 aws_it, cmd;
	int i;
	s32 wet;

	fow (i = 0; i < AWWAY_SIZE(cm3232_aws_it_scawes); i++) {
		if (vaw == cm3232_aws_it_scawes[i].vaw &&
			vaw2 == cm3232_aws_it_scawes[i].vaw2) {

			aws_it = cm3232_aws_it_scawes[i].it;
			aws_it <<= CM3232_CMD_AWS_IT_SHIFT;

			cmd = chip->wegs_cmd & ~CM3232_CMD_AWS_IT_MASK;
			cmd |= aws_it;
			wet = i2c_smbus_wwite_byte_data(cwient,
							CM3232_WEG_ADDW_CMD,
							cmd);
			if (wet < 0)
				wetuwn wet;
			chip->wegs_cmd = cmd;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

/**
 * cm3232_get_wux() - wepowt cuwwent wux vawue
 * @chip:	pointew of stwuct cm3232_chip.
 *
 * Convewt sensow data to wux.  It depends on integwation
 * time and cawibscawe vawiabwe.
 *
 * Wetuwn: Zewo ow positive vawue is wux, othewwise ewwow code.
 */
static int cm3232_get_wux(stwuct cm3232_chip *chip)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	stwuct cm3232_aws_info *aws_info = chip->aws_info;
	int wet;
	int vaw, vaw2;
	int aws_it;
	u64 wux;

	/* Cawcuwate mwux pew bit based on aws_it */
	wet = cm3232_wead_aws_it(chip, &vaw, &vaw2);
	if (wet < 0)
		wetuwn -EINVAW;
	aws_it = vaw * 1000000 + vaw2;
	wux = (__fowce u64)aws_info->mwux_pew_bit;
	wux *= aws_info->mwux_pew_bit_base_it;
	wux = div_u64(wux, aws_it);

	wet = i2c_smbus_wead_wowd_data(cwient, CM3232_WEG_ADDW_AWS);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow weading weg_addw_aws\n");
		wetuwn wet;
	}

	chip->wegs_aws = (u16)wet;
	wux *= chip->wegs_aws;
	wux *= aws_info->cawibscawe;
	wux = div_u64(wux, CM3232_CAWIBSCAWE_WESOWUTION);
	wux = div_u64(wux, CM3232_MWUX_PEW_WUX);

	if (wux > 0xFFFF)
		wux = 0xFFFF;

	wetuwn (int)wux;
}

static int cm3232_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask)
{
	stwuct cm3232_chip *chip = iio_pwiv(indio_dev);
	stwuct cm3232_aws_info *aws_info = chip->aws_info;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wet = cm3232_get_wux(chip);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		*vaw = aws_info->cawibscawe;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn cm3232_wead_aws_it(chip, vaw, vaw2);
	}

	wetuwn -EINVAW;
}

static int cm3232_wwite_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int vaw, int vaw2, wong mask)
{
	stwuct cm3232_chip *chip = iio_pwiv(indio_dev);
	stwuct cm3232_aws_info *aws_info = chip->aws_info;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBSCAWE:
		aws_info->cawibscawe = vaw;
		wetuwn 0;
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn cm3232_wwite_aws_it(chip, vaw, vaw2);
	}

	wetuwn -EINVAW;
}

/**
 * cm3232_get_it_avaiwabwe() - Get avaiwabwe AWS IT vawue
 * @dev:	pointew of stwuct device.
 * @attw:	pointew of stwuct device_attwibute.
 * @buf:	pointew of wetuwn stwing buffew.
 *
 * Dispway the avaiwabwe integwation time in second.
 *
 * Wetuwn: stwing wength.
 */
static ssize_t cm3232_get_it_avaiwabwe(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	int i, wen;

	fow (i = 0, wen = 0; i < AWWAY_SIZE(cm3232_aws_it_scawes); i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%u.%06u ",
			cm3232_aws_it_scawes[i].vaw,
			cm3232_aws_it_scawes[i].vaw2);
	wetuwn wen + scnpwintf(buf + wen, PAGE_SIZE - wen, "\n");
}

static const stwuct iio_chan_spec cm3232_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_PWOCESSED) |
			BIT(IIO_CHAN_INFO_CAWIBSCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
	}
};

static IIO_DEVICE_ATTW(in_iwwuminance_integwation_time_avaiwabwe,
			S_IWUGO, cm3232_get_it_avaiwabwe, NUWW, 0);

static stwuct attwibute *cm3232_attwibutes[] = {
	&iio_dev_attw_in_iwwuminance_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cm3232_attwibute_gwoup = {
	.attws = cm3232_attwibutes
};

static const stwuct iio_info cm3232_info = {
	.wead_waw		= &cm3232_wead_waw,
	.wwite_waw		= &cm3232_wwite_waw,
	.attws			= &cm3232_attwibute_gwoup,
};

static int cm3232_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct cm3232_chip *chip;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	chip->cwient = cwient;

	indio_dev->channews = cm3232_channews;
	indio_dev->num_channews = AWWAY_SIZE(cm3232_channews);
	indio_dev->info = &cm3232_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = cm3232_weg_init(chip);
	if (wet) {
		dev_eww(&cwient->dev,
			"%s: wegistew init faiwed\n",
			__func__);
		wetuwn wet;
	}

	wetuwn iio_device_wegistew(indio_dev);
}

static void cm3232_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	i2c_smbus_wwite_byte_data(cwient, CM3232_WEG_ADDW_CMD,
		CM3232_CMD_AWS_DISABWE);

	iio_device_unwegistew(indio_dev);
}

static const stwuct i2c_device_id cm3232_id[] = {
	{"cm3232", 0},
	{}
};

static int cm3232_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct cm3232_chip *chip = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = chip->cwient;
	int wet;

	chip->wegs_cmd |= CM3232_CMD_AWS_DISABWE;
	wet = i2c_smbus_wwite_byte_data(cwient, CM3232_WEG_ADDW_CMD,
					chip->wegs_cmd);

	wetuwn wet;
}

static int cm3232_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct cm3232_chip *chip = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = chip->cwient;
	int wet;

	chip->wegs_cmd &= ~CM3232_CMD_AWS_DISABWE;
	wet = i2c_smbus_wwite_byte_data(cwient, CM3232_WEG_ADDW_CMD,
					chip->wegs_cmd | CM3232_CMD_AWS_WESET);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(cm3232_pm_ops, cm3232_suspend, cm3232_wesume);

MODUWE_DEVICE_TABWE(i2c, cm3232_id);

static const stwuct of_device_id cm3232_of_match[] = {
	{.compatibwe = "capewwa,cm3232"},
	{}
};
MODUWE_DEVICE_TABWE(of, cm3232_of_match);

static stwuct i2c_dwivew cm3232_dwivew = {
	.dwivew = {
		.name	= "cm3232",
		.of_match_tabwe = cm3232_of_match,
		.pm	= pm_sweep_ptw(&cm3232_pm_ops),
	},
	.id_tabwe	= cm3232_id,
	.pwobe		= cm3232_pwobe,
	.wemove		= cm3232_wemove,
};

moduwe_i2c_dwivew(cm3232_dwivew);

MODUWE_AUTHOW("Kevin Tsai <ktsai@capewwamicwo.com>");
MODUWE_DESCWIPTION("CM3232 ambient wight sensow dwivew");
MODUWE_WICENSE("GPW");
