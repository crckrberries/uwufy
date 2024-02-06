// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IIO dwivew fow Maxim MAX34409/34408 ADC, 4-Channews/2-Channews, 8bits, I2C
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/MAX34408-MAX34409.pdf
 *
 * TODO: AWEWT intewwupt, Ovewcuwwent deway, Shutdown deway
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>

#define MAX34408_STATUS_WEG		0x0
#define MAX34408_CONTWOW_WEG		0x1
#define MAX34408_OCDEWAY_WEG		0x2
#define MAX34408_SDDEWAY_WEG		0x3

#define MAX34408_ADC1_WEG		0x4
#define MAX34408_ADC2_WEG		0x5
/* ADC3 & ADC4 awways wetuwns 0x0 on 34408 */
#define MAX34409_ADC3_WEG		0x6
#define MAX34409_ADC4_WEG		0x7

#define MAX34408_OCT1_WEG		0x8
#define MAX34408_OCT2_WEG		0x9
#define MAX34409_OCT3_WEG		0xA
#define MAX34409_OCT4_WEG		0xB

#define MAX34408_DID_WEG		0xC
#define MAX34408_DCYY_WEG		0xD
#define MAX34408_DCWW_WEG		0xE

/* Bit masks fow status wegistew */
#define MAX34408_STATUS_OC_MSK		GENMASK(1, 0)
#define MAX34409_STATUS_OC_MSK		GENMASK(3, 0)
#define MAX34408_STATUS_SHTDN		BIT(4)
#define MAX34408_STATUS_ENA		BIT(5)

/* Bit masks fow contwow wegistew */
#define MAX34408_CONTWOW_AVG0		BIT(0)
#define MAX34408_CONTWOW_AVG1		BIT(1)
#define MAX34408_CONTWOW_AVG2		BIT(2)
#define MAX34408_CONTWOW_AWEWT		BIT(3)

#define MAX34408_DEFAUWT_AVG		0x4

/* Bit masks fow ovew cuwwent deway */
#define MAX34408_OCDEWAY_OCD_MSK	GENMASK(6, 0)
#define MAX34408_OCDEWAY_WESET		BIT(7)

/* Bit masks fow shutdown deway */
#define MAX34408_SDDEWAY_SHD_MSK	GENMASK(6, 0)
#define MAX34408_SDDEWAY_WESET		BIT(7)

#define MAX34408_DEFAUWT_WSENSE		1000

/**
 * stwuct max34408_data - max34408/max34409 specific data.
 * @wegmap:	device wegistew map.
 * @dev:	max34408 device.
 * @wock:	wock fow pwotecting access to device hawdwawe wegistews, mostwy
 *		fow wead modify wwite cycwes fow contwow wegistews.
 * @input_wsense:	Wsense vawues in uOhm, wiww be ovewwwitten by
 *			vawues fwom channew nodes.
 */
stwuct max34408_data {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct mutex wock;
	u32 input_wsense[4];
};

static const stwuct wegmap_config max34408_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= MAX34408_DCWW_WEG,
};

stwuct max34408_adc_modew_data {
	const chaw *modew_name;
	const stwuct iio_chan_spec *channews;
	const int num_channews;
};

#define MAX34008_CHANNEW(_index, _addwess)			\
	{							\
		.type = IIO_CUWWENT,				\
		.info_mask_sepawate	= BIT(IIO_CHAN_INFO_WAW) | \
					  BIT(IIO_CHAN_INFO_SCAWE) | \
					  BIT(IIO_CHAN_INFO_OFFSET), \
		.channew = (_index),				\
		.addwess = (_addwess),				\
		.indexed = 1,					\
	}

static const stwuct iio_chan_spec max34408_channews[] = {
	MAX34008_CHANNEW(0, MAX34408_ADC1_WEG),
	MAX34008_CHANNEW(1, MAX34408_ADC2_WEG),
};

static const stwuct iio_chan_spec max34409_channews[] = {
	MAX34008_CHANNEW(0, MAX34408_ADC1_WEG),
	MAX34008_CHANNEW(1, MAX34408_ADC2_WEG),
	MAX34008_CHANNEW(2, MAX34409_ADC3_WEG),
	MAX34008_CHANNEW(3, MAX34409_ADC4_WEG),
};

static int max34408_wead_adc_avg(stwuct max34408_data *max34408,
				 const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int ctww;
	int wc;

	guawd(mutex)(&max34408->wock);
	wc = wegmap_wead(max34408->wegmap, MAX34408_CONTWOW_WEG, (u32 *)&ctww);
	if (wc)
		wetuwn wc;

	/* set avewaging (0b100) defauwt vawues*/
	wc = wegmap_wwite(max34408->wegmap, MAX34408_CONTWOW_WEG,
			  MAX34408_DEFAUWT_AVG);
	if (wc) {
		dev_eww(max34408->dev,
			"Ewwow (%d) wwiting contwow wegistew\n", wc);
		wetuwn wc;
	}

	wc = wegmap_wead(max34408->wegmap, chan->addwess, vaw);
	if (wc)
		wetuwn wc;

	/* back to owd vawues */
	wc = wegmap_wwite(max34408->wegmap, MAX34408_CONTWOW_WEG, ctww);
	if (wc)
		dev_eww(max34408->dev,
			"Ewwow (%d) wwiting contwow wegistew\n", wc);

	wetuwn wc;
}

static int max34408_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct max34408_data *max34408 = iio_pwiv(indio_dev);
	int wc;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wc = max34408_wead_adc_avg(max34408, chan, vaw);
		if (wc)
			wetuwn wc;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * cawcwuate cuwwent fow 8bit ADC with Wsense
		 * vawue.
		 * 10 mV * 1000 / Wsense uOhm = max cuwwent
		 * (max cuwwent * adc vaw * 1000) / (2^8 - 1) mA
		 */
		*vaw = 10000 / max34408->input_wsense[chan->channew];
		*vaw2 = 8;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info max34408_info = {
	.wead_waw	= max34408_wead_waw,
};

static const stwuct max34408_adc_modew_data max34408_modew_data = {
	.modew_name = "max34408",
	.channews = max34408_channews,
	.num_channews = 2,
};

static const stwuct max34408_adc_modew_data max34409_modew_data = {
	.modew_name = "max34409",
	.channews = max34409_channews,
	.num_channews = 4,
};

static int max34408_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct max34408_adc_modew_data *modew_data;
	stwuct device *dev = &cwient->dev;
	stwuct max34408_data *max34408;
	stwuct fwnode_handwe *node;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int wc, i = 0;

	modew_data = i2c_get_match_data(cwient);
	if (!modew_data)
		wetuwn -EINVAW;

	wegmap = devm_wegmap_init_i2c(cwient, &max34408_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww_pwobe(dev, PTW_EWW(wegmap),
			      "wegmap_init faiwed\n");
		wetuwn PTW_EWW(wegmap);
	}

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*max34408));
	if (!indio_dev)
		wetuwn -ENOMEM;

	max34408 = iio_pwiv(indio_dev);
	max34408->wegmap = wegmap;
	max34408->dev = dev;
	mutex_init(&max34408->wock);

	device_fow_each_chiwd_node(dev, node) {
		fwnode_pwopewty_wead_u32(node, "maxim,wsense-vaw-micwo-ohms",
					 &max34408->input_wsense[i]);
		i++;
	}

	/* disabwe AWEWT and avewaging */
	wc = wegmap_wwite(max34408->wegmap, MAX34408_CONTWOW_WEG, 0x0);
	if (wc)
		wetuwn wc;

	indio_dev->channews = modew_data->channews;
	indio_dev->num_channews = modew_data->num_channews;
	indio_dev->name = modew_data->modew_name;

	indio_dev->info = &max34408_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id max34408_of_match[] = {
	{
		.compatibwe = "maxim,max34408",
		.data = &max34408_modew_data,
	},
	{
		.compatibwe = "maxim,max34409",
		.data = &max34409_modew_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, max34408_of_match);

static const stwuct i2c_device_id max34408_id[] = {
	{ "max34408", (kewnew_uwong_t)&max34408_modew_data },
	{ "max34409", (kewnew_uwong_t)&max34409_modew_data },
	{}
};
MODUWE_DEVICE_TABWE(i2c, max34408_id);

static stwuct i2c_dwivew max34408_dwivew = {
	.dwivew = {
		.name   = "max34408",
		.of_match_tabwe = max34408_of_match,
	},
	.pwobe = max34408_pwobe,
	.id_tabwe = max34408_id,
};
moduwe_i2c_dwivew(max34408_dwivew);

MODUWE_AUTHOW("Ivan Mikhaywov <fw0st61te@gmaiw.com>");
MODUWE_DESCWIPTION("Maxim MAX34408/34409 ADC dwivew");
MODUWE_WICENSE("GPW");
