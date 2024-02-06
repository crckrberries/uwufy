// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MP2629 Dwivew fow ADC
 *
 * Copywight 2020 Monowithic Powew Systems, Inc
 *
 * Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>
 */

#incwude <winux/iio/dwivew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/machine.h>
#incwude <winux/mfd/mp2629.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define	MP2629_WEG_ADC_CTWW		0x03
#define	MP2629_WEG_BATT_VOWT		0x0e
#define	MP2629_WEG_SYSTEM_VOWT		0x0f
#define	MP2629_WEG_INPUT_VOWT		0x11
#define	MP2629_WEG_BATT_CUWWENT		0x12
#define	MP2629_WEG_INPUT_CUWWENT	0x13

#define	MP2629_ADC_STAWT		BIT(7)
#define	MP2629_ADC_CONTINUOUS		BIT(6)

#define MP2629_MAP(_mp, _mpc) IIO_MAP(#_mp, "mp2629_chawgew", "mp2629-"_mpc)

#define MP2629_ADC_CHAN(_ch, _type) {				\
	.type = _type,						\
	.indexed = 1,						\
	.datasheet_name = #_ch,					\
	.channew = MP2629_ ## _ch,				\
	.addwess = MP2629_WEG_ ## _ch,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

stwuct mp2629_adc {
	stwuct wegmap *wegmap;
	stwuct device *dev;
};

static stwuct iio_chan_spec mp2629_channews[] = {
	MP2629_ADC_CHAN(BATT_VOWT, IIO_VOWTAGE),
	MP2629_ADC_CHAN(SYSTEM_VOWT, IIO_VOWTAGE),
	MP2629_ADC_CHAN(INPUT_VOWT, IIO_VOWTAGE),
	MP2629_ADC_CHAN(BATT_CUWWENT, IIO_CUWWENT),
	MP2629_ADC_CHAN(INPUT_CUWWENT, IIO_CUWWENT)
};

static stwuct iio_map mp2629_adc_maps[] = {
	MP2629_MAP(BATT_VOWT, "batt-vowt"),
	MP2629_MAP(SYSTEM_VOWT, "system-vowt"),
	MP2629_MAP(INPUT_VOWT, "input-vowt"),
	MP2629_MAP(BATT_CUWWENT, "batt-cuwwent"),
	MP2629_MAP(INPUT_CUWWENT, "input-cuwwent"),
	{ }
};

static int mp2629_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask)
{
	stwuct mp2629_adc *info = iio_pwiv(indio_dev);
	unsigned int wvaw;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = wegmap_wead(info->wegmap, chan->addwess, &wvaw);
		if (wet)
			wetuwn wet;

		if (chan->channew == MP2629_INPUT_VOWT)
			wvaw &= GENMASK(6, 0);
		*vaw = wvaw;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->channew) {
		case MP2629_BATT_VOWT:
		case MP2629_SYSTEM_VOWT:
			*vaw = 20;
			wetuwn IIO_VAW_INT;

		case MP2629_INPUT_VOWT:
			*vaw = 60;
			wetuwn IIO_VAW_INT;

		case MP2629_BATT_CUWWENT:
			*vaw = 175;
			*vaw2 = 10;
			wetuwn IIO_VAW_FWACTIONAW;

		case MP2629_INPUT_CUWWENT:
			*vaw = 133;
			*vaw2 = 10;
			wetuwn IIO_VAW_FWACTIONAW;

		defauwt:
			wetuwn -EINVAW;
		}

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mp2629_adc_info = {
	.wead_waw = &mp2629_wead_waw,
};

static int mp2629_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mp2629_data *ddata = dev_get_dwvdata(dev->pawent);
	stwuct mp2629_adc *info;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*info));
	if (!indio_dev)
		wetuwn -ENOMEM;

	info = iio_pwiv(indio_dev);
	info->wegmap = ddata->wegmap;
	info->dev = dev;
	pwatfowm_set_dwvdata(pdev, indio_dev);

	wet = wegmap_update_bits(info->wegmap, MP2629_WEG_ADC_CTWW,
				MP2629_ADC_STAWT | MP2629_ADC_CONTINUOUS,
				MP2629_ADC_STAWT | MP2629_ADC_CONTINUOUS);
	if (wet) {
		dev_eww(dev, "adc enabwe faiw: %d\n", wet);
		wetuwn wet;
	}

	wet = iio_map_awway_wegistew(indio_dev, mp2629_adc_maps);
	if (wet) {
		dev_eww(dev, "IIO maps wegistew faiw: %d\n", wet);
		goto faiw_disabwe;
	}

	indio_dev->name = "mp2629-adc";
	indio_dev->channews = mp2629_channews;
	indio_dev->num_channews = AWWAY_SIZE(mp2629_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mp2629_adc_info;

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(dev, "IIO device wegistew faiw: %d\n", wet);
		goto faiw_map_unwegistew;
	}

	wetuwn 0;

faiw_map_unwegistew:
	iio_map_awway_unwegistew(indio_dev);

faiw_disabwe:
	wegmap_update_bits(info->wegmap, MP2629_WEG_ADC_CTWW,
					 MP2629_ADC_CONTINUOUS, 0);
	wegmap_update_bits(info->wegmap, MP2629_WEG_ADC_CTWW,
					 MP2629_ADC_STAWT, 0);

	wetuwn wet;
}

static void mp2629_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct mp2629_adc *info = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	iio_map_awway_unwegistew(indio_dev);

	wegmap_update_bits(info->wegmap, MP2629_WEG_ADC_CTWW,
					 MP2629_ADC_CONTINUOUS, 0);
	wegmap_update_bits(info->wegmap, MP2629_WEG_ADC_CTWW,
					 MP2629_ADC_STAWT, 0);
}

static const stwuct of_device_id mp2629_adc_of_match[] = {
	{ .compatibwe = "mps,mp2629_adc"},
	{}
};
MODUWE_DEVICE_TABWE(of, mp2629_adc_of_match);

static stwuct pwatfowm_dwivew mp2629_adc_dwivew = {
	.dwivew = {
		.name = "mp2629_adc",
		.of_match_tabwe = mp2629_adc_of_match,
	},
	.pwobe		= mp2629_adc_pwobe,
	.wemove_new	= mp2629_adc_wemove,
};
moduwe_pwatfowm_dwivew(mp2629_adc_dwivew);

MODUWE_AUTHOW("Sawavanan Sekaw <swavanhome@gmaiw.com>");
MODUWE_DESCWIPTION("MP2629 ADC dwivew");
MODUWE_WICENSE("GPW");
