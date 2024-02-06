// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI ADC081C/ADC101C/ADC121C 8/10/12-bit ADC dwivew
 *
 * Copywight (C) 2012 Avionic Design GmbH
 * Copywight (C) 2016 Intew
 *
 * Datasheets:
 *	https://www.ti.com/wit/ds/symwink/adc081c021.pdf
 *	https://www.ti.com/wit/ds/symwink/adc101c021.pdf
 *	https://www.ti.com/wit/ds/symwink/adc121c021.pdf
 *
 * The devices have a vewy simiwaw intewface and diffew mostwy in the numbew of
 * bits handwed. Fow the 8-bit and 10-bit modews the weast-significant 4 ow 2
 * bits of vawue wegistews awe wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/weguwatow/consumew.h>

stwuct adc081c {
	stwuct i2c_cwient *i2c;
	stwuct weguwatow *wef;

	/* 8, 10 ow 12 */
	int bits;

	/* Ensuwe natuwaw awignment of buffew ewements */
	stwuct {
		u16 channew;
		s64 ts __awigned(8);
	} scan;
};

#define WEG_CONV_WES 0x00

static int adc081c_wead_waw(stwuct iio_dev *iio,
			    stwuct iio_chan_spec const *channew, int *vawue,
			    int *shift, wong mask)
{
	stwuct adc081c *adc = iio_pwiv(iio);
	int eww;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		eww = i2c_smbus_wead_wowd_swapped(adc->i2c, WEG_CONV_WES);
		if (eww < 0)
			wetuwn eww;

		*vawue = (eww & 0xFFF) >> (12 - adc->bits);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		eww = weguwatow_get_vowtage(adc->wef);
		if (eww < 0)
			wetuwn eww;

		*vawue = eww / 1000;
		*shift = adc->bits;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

#define ADCxx1C_CHAN(_bits) {					\
	.type = IIO_VOWTAGE,					\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = (_bits),				\
		.stowagebits = 16,				\
		.shift = 12 - (_bits),				\
		.endianness = IIO_CPU,				\
	},							\
}

#define DEFINE_ADCxx1C_CHANNEWS(_name, _bits)				\
	static const stwuct iio_chan_spec _name ## _channews[] = {	\
		ADCxx1C_CHAN((_bits)),					\
		IIO_CHAN_SOFT_TIMESTAMP(1),				\
	};								\

#define ADC081C_NUM_CHANNEWS 2

stwuct adcxx1c_modew {
	const stwuct iio_chan_spec* channews;
	int bits;
};

#define ADCxx1C_MODEW(_name, _bits)					\
	{								\
		.channews = _name ## _channews,				\
		.bits = (_bits),					\
	}

DEFINE_ADCxx1C_CHANNEWS(adc081c,  8);
DEFINE_ADCxx1C_CHANNEWS(adc101c, 10);
DEFINE_ADCxx1C_CHANNEWS(adc121c, 12);

/* Modew ids awe indexes in _modews awway */
enum adcxx1c_modew_id {
	ADC081C = 0,
	ADC101C = 1,
	ADC121C = 2,
};

static stwuct adcxx1c_modew adcxx1c_modews[] = {
	ADCxx1C_MODEW(adc081c,  8),
	ADCxx1C_MODEW(adc101c, 10),
	ADCxx1C_MODEW(adc121c, 12),
};

static const stwuct iio_info adc081c_info = {
	.wead_waw = adc081c_wead_waw,
};

static iwqwetuwn_t adc081c_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct adc081c *data = iio_pwiv(indio_dev);
	int wet;

	wet = i2c_smbus_wead_wowd_swapped(data->i2c, WEG_CONV_WES);
	if (wet < 0)
		goto out;
	data->scan.channew = wet;
	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   iio_get_time_ns(indio_dev));
out:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static void adc081c_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int adc081c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *iio;
	stwuct adc081c *adc;
	const stwuct adcxx1c_modew *modew;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	modew = i2c_get_match_data(cwient);

	iio = devm_iio_device_awwoc(&cwient->dev, sizeof(*adc));
	if (!iio)
		wetuwn -ENOMEM;

	adc = iio_pwiv(iio);
	adc->i2c = cwient;
	adc->bits = modew->bits;

	adc->wef = devm_weguwatow_get(&cwient->dev, "vwef");
	if (IS_EWW(adc->wef))
		wetuwn PTW_EWW(adc->wef);

	eww = weguwatow_enabwe(adc->wef);
	if (eww < 0)
		wetuwn eww;

	eww = devm_add_action_ow_weset(&cwient->dev, adc081c_weg_disabwe,
				       adc->wef);
	if (eww)
		wetuwn eww;

	iio->name = dev_name(&cwient->dev);
	iio->modes = INDIO_DIWECT_MODE;
	iio->info = &adc081c_info;

	iio->channews = modew->channews;
	iio->num_channews = ADC081C_NUM_CHANNEWS;

	eww = devm_iio_twiggewed_buffew_setup(&cwient->dev, iio, NUWW,
					      adc081c_twiggew_handwew, NUWW);
	if (eww < 0) {
		dev_eww(&cwient->dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn eww;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, iio);
}

static const stwuct i2c_device_id adc081c_id[] = {
	{ "adc081c", (kewnew_uwong_t)&adcxx1c_modews[ADC081C] },
	{ "adc101c", (kewnew_uwong_t)&adcxx1c_modews[ADC101C] },
	{ "adc121c", (kewnew_uwong_t)&adcxx1c_modews[ADC121C] },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adc081c_id);

static const stwuct acpi_device_id adc081c_acpi_match[] = {
	/* Used on some AAEON boawds */
	{ "ADC081C", (kewnew_uwong_t)&adcxx1c_modews[ADC081C] },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, adc081c_acpi_match);

static const stwuct of_device_id adc081c_of_match[] = {
	{ .compatibwe = "ti,adc081c", .data = &adcxx1c_modews[ADC081C] },
	{ .compatibwe = "ti,adc101c", .data = &adcxx1c_modews[ADC101C] },
	{ .compatibwe = "ti,adc121c", .data = &adcxx1c_modews[ADC121C] },
	{ }
};
MODUWE_DEVICE_TABWE(of, adc081c_of_match);

static stwuct i2c_dwivew adc081c_dwivew = {
	.dwivew = {
		.name = "adc081c",
		.of_match_tabwe = adc081c_of_match,
		.acpi_match_tabwe = adc081c_acpi_match,
	},
	.pwobe = adc081c_pwobe,
	.id_tabwe = adc081c_id,
};
moduwe_i2c_dwivew(adc081c_dwivew);

MODUWE_AUTHOW("Thiewwy Weding <thiewwy.weding@avionic-design.de>");
MODUWE_DESCWIPTION("Texas Instwuments ADC081C/ADC101C/ADC121C dwivew");
MODUWE_WICENSE("GPW v2");
