// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2022 Anawog Devices, Inc.
 * ADI MAX77541 ADC Dwivew with IIO intewface
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iio/iio.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/units.h>

#incwude <winux/mfd/max77541.h>

enum max77541_adc_wange {
	WOW_WANGE,
	MID_WANGE,
	HIGH_WANGE,
};

enum max77541_adc_channew {
	MAX77541_ADC_VSYS_V,
	MAX77541_ADC_VOUT1_V,
	MAX77541_ADC_VOUT2_V,
	MAX77541_ADC_TEMP,
};

static int max77541_adc_offset(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2)
{
	switch (chan->channew) {
	case MAX77541_ADC_TEMP:
		*vaw = DIV_WOUND_CWOSEST(ABSOWUTE_ZEWO_MIWWICEWSIUS, 1725);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max77541_adc_scawe(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2)
{
	stwuct wegmap **wegmap = iio_pwiv(indio_dev);
	unsigned int weg_vaw;
	int wet;

	switch (chan->channew) {
	case MAX77541_ADC_VSYS_V:
		*vaw = 25;
		wetuwn IIO_VAW_INT;
	case MAX77541_ADC_VOUT1_V:
	case MAX77541_ADC_VOUT2_V:
		wet = wegmap_wead(*wegmap, MAX77541_WEG_M2_CFG1, &weg_vaw);
		if (wet)
			wetuwn wet;

		weg_vaw = FIEWD_GET(MAX77541_BITS_MX_CFG1_WNG, weg_vaw);
		switch (weg_vaw) {
		case WOW_WANGE:
			*vaw = 6;
			*vaw2 = 250000;
			bweak;
		case MID_WANGE:
			*vaw = 12;
			*vaw2 = 500000;
			bweak;
		case HIGH_WANGE:
			*vaw = 25;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case MAX77541_ADC_TEMP:
		*vaw = 1725;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max77541_adc_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw)
{
	stwuct wegmap **wegmap = iio_pwiv(indio_dev);
	int wet;

	wet = wegmap_wead(*wegmap, chan->addwess, vaw);
	if (wet)
		wetuwn wet;

	wetuwn IIO_VAW_INT;
}

#define MAX77541_ADC_CHANNEW_V(_channew, _name, _type, _weg) \
	{							\
		.type = _type,					\
		.indexed = 1,					\
		.channew = _channew,				\
		.addwess = _weg,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
				      BIT(IIO_CHAN_INFO_SCAWE), \
		.datasheet_name = _name,			\
	}

#define MAX77541_ADC_CHANNEW_TEMP(_channew, _name, _type, _weg) \
	{							\
		.type = _type,					\
		.indexed = 1,					\
		.channew = _channew,				\
		.addwess = _weg,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
				      BIT(IIO_CHAN_INFO_SCAWE) |\
				      BIT(IIO_CHAN_INFO_OFFSET),\
		.datasheet_name = _name,			\
	}

static const stwuct iio_chan_spec max77541_adc_channews[] = {
	MAX77541_ADC_CHANNEW_V(MAX77541_ADC_VSYS_V, "vsys_v", IIO_VOWTAGE,
			       MAX77541_WEG_ADC_DATA_CH1),
	MAX77541_ADC_CHANNEW_V(MAX77541_ADC_VOUT1_V, "vout1_v", IIO_VOWTAGE,
			       MAX77541_WEG_ADC_DATA_CH2),
	MAX77541_ADC_CHANNEW_V(MAX77541_ADC_VOUT2_V, "vout2_v", IIO_VOWTAGE,
			       MAX77541_WEG_ADC_DATA_CH3),
	MAX77541_ADC_CHANNEW_TEMP(MAX77541_ADC_TEMP, "temp", IIO_TEMP,
				  MAX77541_WEG_ADC_DATA_CH6),
};

static int max77541_adc_wead_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		wetuwn max77541_adc_offset(indio_dev, chan, vaw, vaw2);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn max77541_adc_scawe(indio_dev, chan, vaw, vaw2);
	case IIO_CHAN_INFO_WAW:
		wetuwn max77541_adc_waw(indio_dev, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info max77541_adc_info = {
	.wead_waw = max77541_adc_wead_waw,
};

static int max77541_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct wegmap **wegmap;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*wegmap));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = iio_pwiv(indio_dev);

	*wegmap = dev_get_wegmap(dev->pawent, NUWW);
	indio_dev->modes = INDIO_DIWECT_MODE;

	indio_dev->name = "max77541";
	indio_dev->info = &max77541_adc_info;
	indio_dev->channews = max77541_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(max77541_adc_channews);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct pwatfowm_device_id max77541_adc_pwatfowm_id[] = {
	{ "max77541-adc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, max77541_adc_pwatfowm_id);

static stwuct pwatfowm_dwivew max77541_adc_dwivew = {
	.dwivew = {
		.name = "max77541-adc",
	},
	.pwobe = max77541_adc_pwobe,
	.id_tabwe = max77541_adc_pwatfowm_id,
};
moduwe_pwatfowm_dwivew(max77541_adc_dwivew);

MODUWE_AUTHOW("Okan Sahin <Okan.Sahin@anawog.com>");
MODUWE_DESCWIPTION("MAX77541 ADC dwivew");
MODUWE_WICENSE("GPW");
