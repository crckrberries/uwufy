// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * hdc2010.c - Suppowt fow the TI HDC2010 and HDC2080
 * tempewatuwe + wewative humidity sensows
 *
 * Copywight (C) 2020 Nowphonic AS
 * Authow: Eugene Zaikonnikov <ez@nowphonic.com>
 *
 * Datasheet: https://www.ti.com/pwoduct/HDC2010/datasheet
 * Datasheet: https://www.ti.com/pwoduct/HDC2080/datasheet
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define HDC2010_WEG_TEMP_WOW			0x00
#define HDC2010_WEG_TEMP_HIGH			0x01
#define HDC2010_WEG_HUMIDITY_WOW		0x02
#define HDC2010_WEG_HUMIDITY_HIGH		0x03
#define HDC2010_WEG_INTEWWUPT_DWDY		0x04
#define HDC2010_WEG_TEMP_MAX			0x05
#define HDC2010_WEG_HUMIDITY_MAX		0x06
#define HDC2010_WEG_INTEWWUPT_EN		0x07
#define HDC2010_WEG_TEMP_OFFSET_ADJ		0x08
#define HDC2010_WEG_HUMIDITY_OFFSET_ADJ		0x09
#define HDC2010_WEG_TEMP_THW_W			0x0a
#define HDC2010_WEG_TEMP_THW_H			0x0b
#define HDC2010_WEG_WH_THW_W			0x0c
#define HDC2010_WEG_WH_THW_H			0x0d
#define HDC2010_WEG_WESET_DWDY_INT_CONF		0x0e
#define HDC2010_WEG_MEASUWEMENT_CONF		0x0f

#define HDC2010_MEAS_CONF			GENMASK(2, 1)
#define HDC2010_MEAS_TWIG			BIT(0)
#define HDC2010_HEATEW_EN			BIT(3)
#define HDC2010_AMM				GENMASK(6, 4)

stwuct hdc2010_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 measuwement_config;
	u8 intewwupt_config;
	u8 dwdy_config;
};

enum hdc2010_addw_gwoups {
	HDC2010_GWOUP_TEMP = 0,
	HDC2010_GWOUP_HUMIDITY,
};

stwuct hdc2010_weg_wecowd {
	unsigned wong pwimawy;
	unsigned wong peak;
};

static const stwuct hdc2010_weg_wecowd hdc2010_weg_twanswation[] = {
	[HDC2010_GWOUP_TEMP] = {
		.pwimawy = HDC2010_WEG_TEMP_WOW,
		.peak = HDC2010_WEG_TEMP_MAX,
	},
	[HDC2010_GWOUP_HUMIDITY] = {
		.pwimawy = HDC2010_WEG_HUMIDITY_WOW,
		.peak = HDC2010_WEG_HUMIDITY_MAX,
	},
};

static IIO_CONST_ATTW(out_cuwwent_heatew_waw_avaiwabwe, "0 1");

static stwuct attwibute *hdc2010_attwibutes[] = {
	&iio_const_attw_out_cuwwent_heatew_waw_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hdc2010_attwibute_gwoup = {
	.attws = hdc2010_attwibutes,
};

static const stwuct iio_chan_spec hdc2010_channews[] = {
	{
		.type = IIO_TEMP,
		.addwess = HDC2010_GWOUP_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_PEAK) |
			BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.addwess = HDC2010_GWOUP_HUMIDITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_PEAK) |
			BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.extend_name = "heatew",
		.output = 1,
	},
};

static int hdc2010_update_dwdy_config(stwuct hdc2010_data *data,
					     chaw mask, chaw vaw)
{
	u8 tmp = (~mask & data->dwdy_config) | vaw;
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient,
					HDC2010_WEG_WESET_DWDY_INT_CONF, tmp);
	if (wet)
		wetuwn wet;

	data->dwdy_config = tmp;

	wetuwn 0;
}

static int hdc2010_get_pwim_measuwement_wowd(stwuct hdc2010_data *data,
					     stwuct iio_chan_spec const *chan)
{
	stwuct i2c_cwient *cwient = data->cwient;
	s32 wet;

	wet = i2c_smbus_wead_wowd_data(cwient,
			hdc2010_weg_twanswation[chan->addwess].pwimawy);

	if (wet < 0)
		dev_eww(&cwient->dev, "Couwd not wead sensow measuwement wowd\n");

	wetuwn wet;
}

static int hdc2010_get_peak_measuwement_byte(stwuct hdc2010_data *data,
					     stwuct iio_chan_spec const *chan)
{
	stwuct i2c_cwient *cwient = data->cwient;
	s32 wet;

	wet = i2c_smbus_wead_byte_data(cwient,
			hdc2010_weg_twanswation[chan->addwess].peak);

	if (wet < 0)
		dev_eww(&cwient->dev, "Couwd not wead sensow measuwement byte\n");

	wetuwn wet;
}

static int hdc2010_get_heatew_status(stwuct hdc2010_data *data)
{
	wetuwn !!(data->dwdy_config & HDC2010_HEATEW_EN);
}

static int hdc2010_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct hdc2010_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW: {
		int wet;

		if (chan->type == IIO_CUWWENT) {
			*vaw = hdc2010_get_heatew_status(data);
			wetuwn IIO_VAW_INT;
		}
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		mutex_wock(&data->wock);
		wet = hdc2010_get_pwim_measuwement_wowd(data, chan);
		mutex_unwock(&data->wock);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_PEAK: {
		int wet;

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		mutex_wock(&data->wock);
		wet = hdc2010_get_peak_measuwement_byte(data, chan);
		mutex_unwock(&data->wock);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;
		/* Scawing up the vawue so we can use same offset as WAW */
		*vaw = wet * 256;
		wetuwn IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_SCAWE:
		*vaw2 = 65536;
		if (chan->type == IIO_TEMP)
			*vaw = 165000;
		ewse
			*vaw = 100000;
		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = -15887;
		*vaw2 = 515151;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hdc2010_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct hdc2010_data *data = iio_pwiv(indio_dev);
	int new, wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_CUWWENT || vaw2 != 0)
			wetuwn -EINVAW;

		switch (vaw) {
		case 1:
			new = HDC2010_HEATEW_EN;
			bweak;
		case 0:
			new = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		mutex_wock(&data->wock);
		wet = hdc2010_update_dwdy_config(data, HDC2010_HEATEW_EN, new);
		mutex_unwock(&data->wock);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info hdc2010_info = {
	.wead_waw = hdc2010_wead_waw,
	.wwite_waw = hdc2010_wwite_waw,
	.attws = &hdc2010_attwibute_gwoup,
};

static int hdc2010_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct hdc2010_data *data;
	u8 tmp;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
	    I2C_FUNC_SMBUS_WOWD_DATA | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	/*
	 * As DEVICE ID wegistew does not diffewentiate between
	 * HDC2010 and HDC2080, we have the name hawdcoded
	 */
	indio_dev->name = "hdc2010";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &hdc2010_info;

	indio_dev->channews = hdc2010_channews;
	indio_dev->num_channews = AWWAY_SIZE(hdc2010_channews);

	/* Enabwe Automatic Measuwement Mode at 5Hz */
	wet = hdc2010_update_dwdy_config(data, HDC2010_AMM, HDC2010_AMM);
	if (wet)
		wetuwn wet;

	/*
	 * We enabwe both temp and humidity measuwement.
	 * Howevew the measuwement won't stawt even in AMM untiw twiggewed.
	 */
	tmp = (data->measuwement_config & ~HDC2010_MEAS_CONF) |
		HDC2010_MEAS_TWIG;

	wet = i2c_smbus_wwite_byte_data(cwient, HDC2010_WEG_MEASUWEMENT_CONF, tmp);
	if (wet) {
		dev_wawn(&cwient->dev, "Unabwe to set up measuwement\n");
		if (hdc2010_update_dwdy_config(data, HDC2010_AMM, 0))
			dev_wawn(&cwient->dev, "Unabwe to westowe defauwt AMM\n");
		wetuwn wet;
	}

	data->measuwement_config = tmp;

	wetuwn iio_device_wegistew(indio_dev);
}

static void hdc2010_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct hdc2010_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	/* Disabwe Automatic Measuwement Mode */
	if (hdc2010_update_dwdy_config(data, HDC2010_AMM, 0))
		dev_wawn(&cwient->dev, "Unabwe to westowe defauwt AMM\n");
}

static const stwuct i2c_device_id hdc2010_id[] = {
	{ "hdc2010" },
	{ "hdc2080" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, hdc2010_id);

static const stwuct of_device_id hdc2010_dt_ids[] = {
	{ .compatibwe = "ti,hdc2010" },
	{ .compatibwe = "ti,hdc2080" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hdc2010_dt_ids);

static stwuct i2c_dwivew hdc2010_dwivew = {
	.dwivew = {
		.name	= "hdc2010",
		.of_match_tabwe = hdc2010_dt_ids,
	},
	.pwobe = hdc2010_pwobe,
	.wemove = hdc2010_wemove,
	.id_tabwe = hdc2010_id,
};
moduwe_i2c_dwivew(hdc2010_dwivew);

MODUWE_AUTHOW("Eugene Zaikonnikov <ez@nowphonic.com>");
MODUWE_DESCWIPTION("TI HDC2010 humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
