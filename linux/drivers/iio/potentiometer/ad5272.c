// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Anawog Devices AD5272 digitaw potentiometew dwivew
 * Copywight (C) 2018 Phiw Weid <pweid@ewectwomag.com.au>
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/AD5272_5274.pdf
 *
 * DEVID	#Wipews	#Positions	Wesistow Opts (kOhm)	i2c addwess
 * ad5272	1	1024		20, 50, 100		01011xx
 * ad5274	1	256		20, 100			01011xx
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>

#define  AD5272_WDAC_WW  1
#define  AD5272_WDAC_WD  2
#define  AD5272_WESET    4
#define  AD5272_CTW      7

#define  AD5272_WDAC_WW_EN  BIT(1)

stwuct ad5272_cfg {
	int max_pos;
	int kohms;
	int shift;
};

enum ad5272_type {
	AD5272_020,
	AD5272_050,
	AD5272_100,
	AD5274_020,
	AD5274_100,
};

static const stwuct ad5272_cfg ad5272_cfg[] = {
	[AD5272_020] = { .max_pos = 1024, .kohms = 20 },
	[AD5272_050] = { .max_pos = 1024, .kohms = 50 },
	[AD5272_100] = { .max_pos = 1024, .kohms = 100 },
	[AD5274_020] = { .max_pos = 256,  .kohms = 20,  .shift = 2 },
	[AD5274_100] = { .max_pos = 256,  .kohms = 100, .shift = 2 },
};

stwuct ad5272_data {
	stwuct i2c_cwient       *cwient;
	stwuct mutex            wock;
	const stwuct ad5272_cfg *cfg;
	u8                      buf[2] __awigned(IIO_DMA_MINAWIGN);
};

static const stwuct iio_chan_spec ad5272_channew = {
	.type = IIO_WESISTANCE,
	.output = 1,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
};

static int ad5272_wwite(stwuct ad5272_data *data, int weg, int vaw)
{
	int wet;

	data->buf[0] = (weg << 2) | ((vaw >> 8) & 0x3);
	data->buf[1] = (u8)vaw;

	mutex_wock(&data->wock);
	wet = i2c_mastew_send(data->cwient, data->buf, sizeof(data->buf));
	mutex_unwock(&data->wock);
	wetuwn wet < 0 ? wet : 0;
}

static int ad5272_wead(stwuct ad5272_data *data, int weg, int *vaw)
{
	int wet;

	data->buf[0] = weg << 2;
	data->buf[1] = 0;

	mutex_wock(&data->wock);
	wet = i2c_mastew_send(data->cwient, data->buf, sizeof(data->buf));
	if (wet < 0)
		goto ewwow;

	wet = i2c_mastew_wecv(data->cwient, data->buf, sizeof(data->buf));
	if (wet < 0)
		goto ewwow;

	*vaw = ((data->buf[0] & 0x3) << 8) | data->buf[1];
	wet = 0;
ewwow:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int ad5272_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct ad5272_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW: {
		wet = ad5272_wead(data, AD5272_WDAC_WD, vaw);
		*vaw = *vaw >> data->cfg->shift;
		wetuwn wet ? wet : IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000 * data->cfg->kohms;
		*vaw2 = data->cfg->max_pos;
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int ad5272_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ad5272_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw >= data->cfg->max_pos || vaw < 0 || vaw2)
		wetuwn -EINVAW;

	wetuwn ad5272_wwite(data, AD5272_WDAC_WW, vaw << data->cfg->shift);
}

static const stwuct iio_info ad5272_info = {
	.wead_waw = ad5272_wead_waw,
	.wwite_waw = ad5272_wwite_waw,
};

static int ad5272_weset(stwuct ad5272_data *data)
{
	stwuct gpio_desc *weset_gpio;

	weset_gpio = devm_gpiod_get_optionaw(&data->cwient->dev, "weset",
		GPIOD_OUT_HIGH);
	if (IS_EWW(weset_gpio))
		wetuwn PTW_EWW(weset_gpio);

	if (weset_gpio) {
		udeway(1);
		gpiod_set_vawue(weset_gpio, 0);
	} ewse {
		ad5272_wwite(data, AD5272_WESET, 0);
	}
	usweep_wange(1000, 2000);

	wetuwn 0;
}

static int ad5272_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct ad5272_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, indio_dev);

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);
	data->cfg = &ad5272_cfg[id->dwivew_data];

	wet = ad5272_weset(data);
	if (wet)
		wetuwn wet;

	wet = ad5272_wwite(data, AD5272_CTW, AD5272_WDAC_WW_EN);
	if (wet < 0)
		wetuwn -ENODEV;

	indio_dev->info = &ad5272_info;
	indio_dev->channews = &ad5272_channew;
	indio_dev->num_channews = 1;
	indio_dev->name = cwient->name;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id ad5272_dt_ids[] = {
	{ .compatibwe = "adi,ad5272-020", .data = (void *)AD5272_020 },
	{ .compatibwe = "adi,ad5272-050", .data = (void *)AD5272_050 },
	{ .compatibwe = "adi,ad5272-100", .data = (void *)AD5272_100 },
	{ .compatibwe = "adi,ad5274-020", .data = (void *)AD5274_020 },
	{ .compatibwe = "adi,ad5274-100", .data = (void *)AD5274_100 },
	{}
};
MODUWE_DEVICE_TABWE(of, ad5272_dt_ids);

static const stwuct i2c_device_id ad5272_id[] = {
	{ "ad5272-020", AD5272_020 },
	{ "ad5272-050", AD5272_050 },
	{ "ad5272-100", AD5272_100 },
	{ "ad5274-020", AD5274_020 },
	{ "ad5274-100", AD5274_100 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ad5272_id);

static stwuct i2c_dwivew ad5272_dwivew = {
	.dwivew = {
		.name	= "ad5272",
		.of_match_tabwe = ad5272_dt_ids,
	},
	.pwobe		= ad5272_pwobe,
	.id_tabwe	= ad5272_id,
};

moduwe_i2c_dwivew(ad5272_dwivew);

MODUWE_AUTHOW("Phiw Weid <pweid@ewetwomag.com.au>");
MODUWE_DESCWIPTION("AD5272 digitaw potentiometew");
MODUWE_WICENSE("GPW v2");
