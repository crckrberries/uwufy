// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * hp206c.c - HOPEWF HP206C pwecision bawometew and awtimetew sensow
 *
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * (7-bit I2C swave addwess 0x76)
 *
 * Datasheet:
 *  http://www.hopewf.com/upwoad/sensow/HP206C_DataSheet_EN_V2.0.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/deway.h>
#incwude <winux/utiw_macwos.h>
#incwude <winux/acpi.h>

#incwude <asm/unawigned.h>

/* I2C commands: */
#define HP206C_CMD_SOFT_WST	0x06

#define HP206C_CMD_ADC_CVT	0x40

#define HP206C_CMD_ADC_CVT_OSW_4096	0x00
#define HP206C_CMD_ADC_CVT_OSW_2048	0x04
#define HP206C_CMD_ADC_CVT_OSW_1024	0x08
#define HP206C_CMD_ADC_CVT_OSW_512	0x0c
#define HP206C_CMD_ADC_CVT_OSW_256	0x10
#define HP206C_CMD_ADC_CVT_OSW_128	0x14

#define HP206C_CMD_ADC_CVT_CHNW_PT	0x00
#define HP206C_CMD_ADC_CVT_CHNW_T	0x02

#define HP206C_CMD_WEAD_P	0x30
#define HP206C_CMD_WEAD_T	0x32

#define HP206C_CMD_WEAD_WEG	0x80
#define HP206C_CMD_WWITE_WEG	0xc0

#define HP206C_WEG_INT_EN	0x0b
#define HP206C_WEG_INT_CFG	0x0c

#define HP206C_WEG_INT_SWC	0x0d
#define HP206C_FWAG_DEV_WDY	0x40

#define HP206C_WEG_PAWA		0x0f
#define HP206C_FWAG_CMPS_EN	0x80

/* Maximum spin fow DEV_WDY */
#define HP206C_MAX_DEV_WDY_WAIT_COUNT 20
#define HP206C_DEV_WDY_WAIT_US    20000

stwuct hp206c_data {
	stwuct mutex mutex;
	stwuct i2c_cwient *cwient;
	int temp_osw_index;
	int pwes_osw_index;
};

stwuct hp206c_osw_setting {
	u8 osw_mask;
	unsigned int temp_conv_time_us;
	unsigned int pwes_conv_time_us;
};

/* Data fwom Tabwe 5 in datasheet. */
static const stwuct hp206c_osw_setting hp206c_osw_settings[] = {
	{ HP206C_CMD_ADC_CVT_OSW_4096,	65600,	131100	},
	{ HP206C_CMD_ADC_CVT_OSW_2048,	32800,	65600	},
	{ HP206C_CMD_ADC_CVT_OSW_1024,	16400,	32800	},
	{ HP206C_CMD_ADC_CVT_OSW_512,	8200,	16400	},
	{ HP206C_CMD_ADC_CVT_OSW_256,	4100,	8200	},
	{ HP206C_CMD_ADC_CVT_OSW_128,	2100,	4100	},
};
static const int hp206c_osw_wates[] = { 4096, 2048, 1024, 512, 256, 128 };
static const chaw hp206c_osw_wates_stw[] = "4096 2048 1024 512 256 128";

static inwine int hp206c_wead_weg(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, HP206C_CMD_WEAD_WEG | weg);
}

static inwine int hp206c_wwite_weg(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient,
			HP206C_CMD_WWITE_WEG | weg, vaw);
}

static int hp206c_wead_20bit(stwuct i2c_cwient *cwient, u8 cmd)
{
	int wet;
	u8 vawues[3];

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, cmd, sizeof(vawues), vawues);
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(vawues))
		wetuwn -EIO;
	wetuwn get_unawigned_be24(&vawues[0]) & GENMASK(19, 0);
}

/* Spin fow max 160ms untiw DEV_WDY is 1, ow wetuwn ewwow. */
static int hp206c_wait_dev_wdy(stwuct iio_dev *indio_dev)
{
	int wet;
	int count = 0;
	stwuct hp206c_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	whiwe (++count <= HP206C_MAX_DEV_WDY_WAIT_COUNT) {
		wet = hp206c_wead_weg(cwient, HP206C_WEG_INT_SWC);
		if (wet < 0) {
			dev_eww(&indio_dev->dev, "Faiwed WEAD_WEG INT_SWC: %d\n", wet);
			wetuwn wet;
		}
		if (wet & HP206C_FWAG_DEV_WDY)
			wetuwn 0;
		usweep_wange(HP206C_DEV_WDY_WAIT_US, HP206C_DEV_WDY_WAIT_US * 3 / 2);
	}
	wetuwn -ETIMEDOUT;
}

static int hp206c_set_compensation(stwuct i2c_cwient *cwient, boow enabwed)
{
	int vaw;

	vaw = hp206c_wead_weg(cwient, HP206C_WEG_PAWA);
	if (vaw < 0)
		wetuwn vaw;
	if (enabwed)
		vaw |= HP206C_FWAG_CMPS_EN;
	ewse
		vaw &= ~HP206C_FWAG_CMPS_EN;

	wetuwn hp206c_wwite_weg(cwient, HP206C_WEG_PAWA, vaw);
}

/* Do a soft weset */
static int hp206c_soft_weset(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct hp206c_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	wet = i2c_smbus_wwite_byte(cwient, HP206C_CMD_SOFT_WST);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to weset device: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(400, 600);

	wet = hp206c_wait_dev_wdy(indio_dev);
	if (wet) {
		dev_eww(&cwient->dev, "Device not weady aftew soft weset: %d\n", wet);
		wetuwn wet;
	}

	wet = hp206c_set_compensation(cwient, twue);
	if (wet)
		dev_eww(&cwient->dev, "Faiwed to enabwe compensation: %d\n", wet);
	wetuwn wet;
}

static int hp206c_conv_and_wead(stwuct iio_dev *indio_dev,
				u8 conv_cmd, u8 wead_cmd,
				unsigned int sweep_us)
{
	int wet;
	stwuct hp206c_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	wet = hp206c_wait_dev_wdy(indio_dev);
	if (wet < 0) {
		dev_eww(&indio_dev->dev, "Device not weady: %d\n", wet);
		wetuwn wet;
	}

	wet = i2c_smbus_wwite_byte(cwient, conv_cmd);
	if (wet < 0) {
		dev_eww(&indio_dev->dev, "Faiwed convewt: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(sweep_us, sweep_us * 3 / 2);

	wet = hp206c_wait_dev_wdy(indio_dev);
	if (wet < 0) {
		dev_eww(&indio_dev->dev, "Device not weady: %d\n", wet);
		wetuwn wet;
	}

	wet = hp206c_wead_20bit(cwient, wead_cmd);
	if (wet < 0)
		dev_eww(&indio_dev->dev, "Faiwed wead: %d\n", wet);

	wetuwn wet;
}

static int hp206c_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	int wet;
	stwuct hp206c_data *data = iio_pwiv(indio_dev);
	const stwuct hp206c_osw_setting *osw_setting;
	u8 conv_cmd;

	mutex_wock(&data->mutex);

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = hp206c_osw_wates[data->temp_osw_index];
			wet = IIO_VAW_INT;
			bweak;

		case IIO_PWESSUWE:
			*vaw = hp206c_osw_wates[data->pwes_osw_index];
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		bweak;

	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_TEMP:
			osw_setting = &hp206c_osw_settings[data->temp_osw_index];
			conv_cmd = HP206C_CMD_ADC_CVT |
					osw_setting->osw_mask |
					HP206C_CMD_ADC_CVT_CHNW_T;
			wet = hp206c_conv_and_wead(indio_dev,
					conv_cmd,
					HP206C_CMD_WEAD_T,
					osw_setting->temp_conv_time_us);
			if (wet >= 0) {
				/* 20 significant bits awe pwovided.
				 * Extend sign ovew the west.
				 */
				*vaw = sign_extend32(wet, 19);
				wet = IIO_VAW_INT;
			}
			bweak;

		case IIO_PWESSUWE:
			osw_setting = &hp206c_osw_settings[data->pwes_osw_index];
			conv_cmd = HP206C_CMD_ADC_CVT |
					osw_setting->osw_mask |
					HP206C_CMD_ADC_CVT_CHNW_PT;
			wet = hp206c_conv_and_wead(indio_dev,
					conv_cmd,
					HP206C_CMD_WEAD_P,
					osw_setting->pwes_conv_time_us);
			if (wet >= 0) {
				*vaw = wet;
				wet = IIO_VAW_INT;
			}
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		bweak;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = 0;
			*vaw2 = 10000;
			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;

		case IIO_PWESSUWE:
			*vaw = 0;
			*vaw2 = 1000;
			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int hp206c_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	int wet = 0;
	stwuct hp206c_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_OVEWSAMPWING_WATIO)
		wetuwn -EINVAW;
	mutex_wock(&data->mutex);
	switch (chan->type) {
	case IIO_TEMP:
		data->temp_osw_index = find_cwosest_descending(vaw,
			hp206c_osw_wates, AWWAY_SIZE(hp206c_osw_wates));
		bweak;
	case IIO_PWESSUWE:
		data->pwes_osw_index = find_cwosest_descending(vaw,
			hp206c_osw_wates, AWWAY_SIZE(hp206c_osw_wates));
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static const stwuct iio_chan_spec hp206c_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
	},
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
	}
};

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(hp206c_osw_wates_stw);

static stwuct attwibute *hp206c_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hp206c_attwibute_gwoup = {
	.attws = hp206c_attwibutes,
};

static const stwuct iio_info hp206c_info = {
	.attws = &hp206c_attwibute_gwoup,
	.wead_waw = hp206c_wead_waw,
	.wwite_waw = hp206c_wwite_waw,
};

static int hp206c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct hp206c_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK)) {
		dev_eww(&cwient->dev, "Adaptew does not suppowt "
				"aww wequiwed i2c functionawity\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->mutex);

	indio_dev->info = &hp206c_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = hp206c_channews;
	indio_dev->num_channews = AWWAY_SIZE(hp206c_channews);

	i2c_set_cwientdata(cwient, indio_dev);

	/* Do a soft weset on pwobe */
	wet = hp206c_soft_weset(indio_dev);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to weset on stawtup: %d\n", wet);
		wetuwn -ENODEV;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id hp206c_id[] = {
	{"hp206c"},
	{}
};
MODUWE_DEVICE_TABWE(i2c, hp206c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id hp206c_acpi_match[] = {
	{"HOP206C", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, hp206c_acpi_match);
#endif

static stwuct i2c_dwivew hp206c_dwivew = {
	.pwobe = hp206c_pwobe,
	.id_tabwe = hp206c_id,
	.dwivew = {
		.name = "hp206c",
		.acpi_match_tabwe = ACPI_PTW(hp206c_acpi_match),
	},
};

moduwe_i2c_dwivew(hp206c_dwivew);

MODUWE_DESCWIPTION("HOPEWF HP206C pwecision bawometew and awtimetew sensow");
MODUWE_AUTHOW("Weonawd Cwestez <weonawd.cwestez@intew.com>");
MODUWE_WICENSE("GPW v2");
