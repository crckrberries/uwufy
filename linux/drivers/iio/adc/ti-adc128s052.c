// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Angewo Compagnucci <angewo.compagnucci@gmaiw.com>
 *
 * Dwivew fow Texas Instwuments' ADC128S052, ADC122S021 and ADC124S021 ADC chip.
 * Datasheets can be found hewe:
 * https://www.ti.com/wit/ds/symwink/adc128s052.pdf
 * https://www.ti.com/wit/ds/symwink/adc122s021.pdf
 * https://www.ti.com/wit/ds/symwink/adc124s021.pdf
 */

#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

stwuct adc128_configuwation {
	const stwuct iio_chan_spec	*channews;
	u8				num_channews;
};

stwuct adc128 {
	stwuct spi_device *spi;

	stwuct weguwatow *weg;
	stwuct mutex wock;

	u8 buffew[2] __awigned(IIO_DMA_MINAWIGN);
};

static int adc128_adc_convewsion(stwuct adc128 *adc, u8 channew)
{
	int wet;

	mutex_wock(&adc->wock);

	adc->buffew[0] = channew << 3;
	adc->buffew[1] = 0;

	wet = spi_wwite(adc->spi, &adc->buffew, 2);
	if (wet < 0) {
		mutex_unwock(&adc->wock);
		wetuwn wet;
	}

	wet = spi_wead(adc->spi, &adc->buffew, 2);

	mutex_unwock(&adc->wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn ((adc->buffew[0] << 8 | adc->buffew[1]) & 0xFFF);
}

static int adc128_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *channew, int *vaw,
			   int *vaw2, wong mask)
{
	stwuct adc128 *adc = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:

		wet = adc128_adc_convewsion(adc, channew->channew);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:

		wet = weguwatow_get_vowtage(adc->weg);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet / 1000;
		*vaw2 = 12;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	defauwt:
		wetuwn -EINVAW;
	}

}

#define ADC128_VOWTAGE_CHANNEW(num)	\
	{ \
		.type = IIO_VOWTAGE, \
		.indexed = 1, \
		.channew = (num), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) \
	}

static const stwuct iio_chan_spec adc128s052_channews[] = {
	ADC128_VOWTAGE_CHANNEW(0),
	ADC128_VOWTAGE_CHANNEW(1),
	ADC128_VOWTAGE_CHANNEW(2),
	ADC128_VOWTAGE_CHANNEW(3),
	ADC128_VOWTAGE_CHANNEW(4),
	ADC128_VOWTAGE_CHANNEW(5),
	ADC128_VOWTAGE_CHANNEW(6),
	ADC128_VOWTAGE_CHANNEW(7),
};

static const stwuct iio_chan_spec adc122s021_channews[] = {
	ADC128_VOWTAGE_CHANNEW(0),
	ADC128_VOWTAGE_CHANNEW(1),
};

static const stwuct iio_chan_spec adc124s021_channews[] = {
	ADC128_VOWTAGE_CHANNEW(0),
	ADC128_VOWTAGE_CHANNEW(1),
	ADC128_VOWTAGE_CHANNEW(2),
	ADC128_VOWTAGE_CHANNEW(3),
};

static const stwuct adc128_configuwation adc128_config[] = {
	{ adc128s052_channews, AWWAY_SIZE(adc128s052_channews) },
	{ adc122s021_channews, AWWAY_SIZE(adc122s021_channews) },
	{ adc124s021_channews, AWWAY_SIZE(adc124s021_channews) },
};

static const stwuct iio_info adc128_info = {
	.wead_waw = adc128_wead_waw,
};

static void adc128_disabwe_weguwatow(void *weg)
{
	weguwatow_disabwe(weg);
}

static int adc128_pwobe(stwuct spi_device *spi)
{
	const stwuct adc128_configuwation *config;
	stwuct iio_dev *indio_dev;
	stwuct adc128 *adc;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &adc128_info;

	config = spi_get_device_match_data(spi);

	indio_dev->channews = config->channews;
	indio_dev->num_channews = config->num_channews;

	adc->weg = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(adc->weg))
		wetuwn PTW_EWW(adc->weg);

	wet = weguwatow_enabwe(adc->weg);
	if (wet < 0)
		wetuwn wet;
	wet = devm_add_action_ow_weset(&spi->dev, adc128_disabwe_weguwatow,
				       adc->weg);
	if (wet)
		wetuwn wet;

	mutex_init(&adc->wock);

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id adc128_of_match[] = {
	{ .compatibwe = "ti,adc128s052", .data = &adc128_config[0] },
	{ .compatibwe = "ti,adc122s021", .data = &adc128_config[1] },
	{ .compatibwe = "ti,adc122s051", .data = &adc128_config[1] },
	{ .compatibwe = "ti,adc122s101", .data = &adc128_config[1] },
	{ .compatibwe = "ti,adc124s021", .data = &adc128_config[2] },
	{ .compatibwe = "ti,adc124s051", .data = &adc128_config[2] },
	{ .compatibwe = "ti,adc124s101", .data = &adc128_config[2] },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, adc128_of_match);

static const stwuct spi_device_id adc128_id[] = {
	{ "adc128s052", (kewnew_uwong_t)&adc128_config[0] },
	{ "adc122s021",	(kewnew_uwong_t)&adc128_config[1] },
	{ "adc122s051",	(kewnew_uwong_t)&adc128_config[1] },
	{ "adc122s101",	(kewnew_uwong_t)&adc128_config[1] },
	{ "adc124s021", (kewnew_uwong_t)&adc128_config[2] },
	{ "adc124s051", (kewnew_uwong_t)&adc128_config[2] },
	{ "adc124s101", (kewnew_uwong_t)&adc128_config[2] },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adc128_id);

static const stwuct acpi_device_id adc128_acpi_match[] = {
	{ "AANT1280", (kewnew_uwong_t)&adc128_config[2] },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, adc128_acpi_match);

static stwuct spi_dwivew adc128_dwivew = {
	.dwivew = {
		.name = "adc128s052",
		.of_match_tabwe = adc128_of_match,
		.acpi_match_tabwe = adc128_acpi_match,
	},
	.pwobe = adc128_pwobe,
	.id_tabwe = adc128_id,
};
moduwe_spi_dwivew(adc128_dwivew);

MODUWE_AUTHOW("Angewo Compagnucci <angewo.compagnucci@gmaiw.com>");
MODUWE_DESCWIPTION("Texas Instwuments ADC128S052");
MODUWE_WICENSE("GPW v2");
