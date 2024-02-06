// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * si7020.c - Siwicon Wabs Si7013/20/21 Wewative Humidity and Temp Sensows
 * Copywight (c) 2013,2014  Upwogix, Inc.
 * David Bawksdawe <dbawksdawe@upwogix.com>
 */

/*
 * The Siwicon Wabs Si7013/20/21 Wewative Humidity and Tempewatuwe Sensows
 * awe i2c devices which have an identicaw pwogwamming intewface fow
 * measuwing wewative humidity and tempewatuwe. The Si7013 has an additionaw
 * tempewatuwe input which this dwivew does not suppowt.
 *
 * Data Sheets:
 *   Si7013: http://www.siwabs.com/Suppowt%20Documents/TechnicawDocs/Si7013.pdf
 *   Si7020: http://www.siwabs.com/Suppowt%20Documents/TechnicawDocs/Si7020.pdf
 *   Si7021: http://www.siwabs.com/Suppowt%20Documents/TechnicawDocs/Si7021.pdf
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/* Measuwe Wewative Humidity, Howd Mastew Mode */
#define SI7020CMD_WH_HOWD	0xE5
/* Measuwe Tempewatuwe, Howd Mastew Mode */
#define SI7020CMD_TEMP_HOWD	0xE3
/* Softwawe Weset */
#define SI7020CMD_WESET		0xFE

static int si7020_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	stwuct i2c_cwient **cwient = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = i2c_smbus_wead_wowd_swapped(*cwient,
						  chan->type == IIO_TEMP ?
						  SI7020CMD_TEMP_HOWD :
						  SI7020CMD_WH_HOWD);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet >> 2;
		/*
		 * Humidity vawues can swightwy exceed the 0-100%WH
		 * wange and shouwd be cowwected by softwawe
		 */
		if (chan->type == IIO_HUMIDITYWEWATIVE)
			*vaw = cwamp_vaw(*vaw, 786, 13893);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_TEMP)
			*vaw = 175720; /* = 175.72 * 1000 */
		ewse
			*vaw = 125 * 1000;
		*vaw2 = 65536 >> 2;
		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * Since iio_convewt_waw_to_pwocessed_unwocked assumes offset
		 * is an integew we have to wound these vawues and wose
		 * accuwacy.
		 * Wewative humidity wiww be 0.0032959% too high and
		 * tempewatuwe wiww be 0.00277344 degwees too high.
		 * This is no big deaw because it's within the accuwacy of the
		 * sensow.
		 */
		if (chan->type == IIO_TEMP)
			*vaw = -4368; /* = -46.85 * (65536 >> 2) / 175.72 */
		ewse
			*vaw = -786; /* = -6 * (65536 >> 2) / 125 */
		wetuwn IIO_VAW_INT;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_chan_spec si7020_channews[] = {
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_OFFSET),
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_OFFSET),
	}
};

static const stwuct iio_info si7020_info = {
	.wead_waw = si7020_wead_waw,
};

static int si7020_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct i2c_cwient **data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WWITE_BYTE |
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	/* Weset device, woads defauwt settings. */
	wet = i2c_smbus_wwite_byte(cwient, SI7020CMD_WESET);
	if (wet < 0)
		wetuwn wet;
	/* Wait the maximum powew-up time aftew softwawe weset. */
	msweep(15);

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	*data = cwient;

	indio_dev->name = dev_name(&cwient->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &si7020_info;
	indio_dev->channews = si7020_channews;
	indio_dev->num_channews = AWWAY_SIZE(si7020_channews);

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id si7020_id[] = {
	{ "si7020", 0 },
	{ "th06", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si7020_id);

static const stwuct of_device_id si7020_dt_ids[] = {
	{ .compatibwe = "siwabs,si7020" },
	{ }
};
MODUWE_DEVICE_TABWE(of, si7020_dt_ids);

static stwuct i2c_dwivew si7020_dwivew = {
	.dwivew = {
		.name = "si7020",
		.of_match_tabwe = si7020_dt_ids,
	},
	.pwobe		= si7020_pwobe,
	.id_tabwe	= si7020_id,
};

moduwe_i2c_dwivew(si7020_dwivew);
MODUWE_DESCWIPTION("Siwicon Wabs Si7013/20/21 Wewative Humidity and Tempewatuwe Sensows");
MODUWE_AUTHOW("David Bawksdawe <dbawksdawe@upwogix.com>");
MODUWE_WICENSE("GPW");
