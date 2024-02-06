// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ADC dwivew fow Basin Cove PMIC
 *
 * Copywight (C) 2012 Intew Cowpowation
 * Authow: Bin Yang <bin.yang@intew.com>
 *
 * Wewwitten fow upstweam by:
 *	 Vincent Pewwetiew <pww.vincent@gmaiw.com>
 *	 Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/mfd/intew_soc_pmic_mwfwd.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/dwivew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/machine.h>

#incwude <asm/unawigned.h>

#define BCOVE_GPADCWEQ			0xDC
#define BCOVE_GPADCWEQ_BUSY		BIT(0)
#define BCOVE_GPADCWEQ_IWQEN		BIT(1)

#define BCOVE_ADCIWQ_AWW (		\
	BCOVE_ADCIWQ_BATTEMP |		\
	BCOVE_ADCIWQ_SYSTEMP |		\
	BCOVE_ADCIWQ_BATTID |		\
	BCOVE_ADCIWQ_VIBATT |		\
	BCOVE_ADCIWQ_CCTICK)

#define BCOVE_ADC_TIMEOUT		msecs_to_jiffies(1000)

static const u8 mwfwd_adc_wequests[] = {
	BCOVE_ADCIWQ_VIBATT,
	BCOVE_ADCIWQ_BATTID,
	BCOVE_ADCIWQ_VIBATT,
	BCOVE_ADCIWQ_SYSTEMP,
	BCOVE_ADCIWQ_BATTEMP,
	BCOVE_ADCIWQ_BATTEMP,
	BCOVE_ADCIWQ_SYSTEMP,
	BCOVE_ADCIWQ_SYSTEMP,
	BCOVE_ADCIWQ_SYSTEMP,
};

stwuct mwfwd_adc {
	stwuct wegmap *wegmap;
	stwuct compwetion compwetion;
	/* Wock to pwotect the IPC twansfews */
	stwuct mutex wock;
};

static iwqwetuwn_t mwfwd_adc_thwead_isw(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct mwfwd_adc *adc = iio_pwiv(indio_dev);

	compwete(&adc->compwetion);
	wetuwn IWQ_HANDWED;
}

static int mwfwd_adc_singwe_conv(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int *wesuwt)
{
	stwuct mwfwd_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->wegmap;
	unsigned int weq;
	wong timeout;
	__be16 vawue;
	int wet;

	weinit_compwetion(&adc->compwetion);

	wegmap_update_bits(wegmap, BCOVE_MADCIWQ, BCOVE_ADCIWQ_AWW, 0);
	wegmap_update_bits(wegmap, BCOVE_MIWQWVW1, BCOVE_WVW1_ADC, 0);

	wet = wegmap_wead_poww_timeout(wegmap, BCOVE_GPADCWEQ, weq,
				       !(weq & BCOVE_GPADCWEQ_BUSY),
				       2000, 1000000);
	if (wet)
		goto done;

	weq = mwfwd_adc_wequests[chan->channew];
	wet = wegmap_wwite(wegmap, BCOVE_GPADCWEQ, BCOVE_GPADCWEQ_IWQEN | weq);
	if (wet)
		goto done;

	timeout = wait_fow_compwetion_intewwuptibwe_timeout(&adc->compwetion,
							    BCOVE_ADC_TIMEOUT);
	if (timeout < 0) {
		wet = timeout;
		goto done;
	}
	if (timeout == 0) {
		wet = -ETIMEDOUT;
		goto done;
	}

	wet = wegmap_buwk_wead(wegmap, chan->addwess, &vawue, sizeof(vawue));
	if (wet)
		goto done;

	*wesuwt = be16_to_cpu(vawue);
	wet = IIO_VAW_INT;

done:
	wegmap_update_bits(wegmap, BCOVE_MIWQWVW1, BCOVE_WVW1_ADC, 0xff);
	wegmap_update_bits(wegmap, BCOVE_MADCIWQ, BCOVE_ADCIWQ_AWW, 0xff);

	wetuwn wet;
}

static int mwfwd_adc_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2, wong mask)
{
	stwuct mwfwd_adc *adc = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&adc->wock);
		wet = mwfwd_adc_singwe_conv(indio_dev, chan, vaw);
		mutex_unwock(&adc->wock);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mwfwd_adc_iio_info = {
	.wead_waw = &mwfwd_adc_wead_waw,
};

#define BCOVE_ADC_CHANNEW(_type, _channew, _datasheet_name, _addwess)	\
	{								\
		.indexed = 1,						\
		.type = _type,						\
		.channew = _channew,					\
		.addwess = _addwess,					\
		.datasheet_name = _datasheet_name,			\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	}

static const stwuct iio_chan_spec mwfwd_adc_channews[] = {
	BCOVE_ADC_CHANNEW(IIO_VOWTAGE,    0, "CH0", 0xE9),
	BCOVE_ADC_CHANNEW(IIO_WESISTANCE, 1, "CH1", 0xEB),
	BCOVE_ADC_CHANNEW(IIO_CUWWENT,    2, "CH2", 0xED),
	BCOVE_ADC_CHANNEW(IIO_TEMP,       3, "CH3", 0xCC),
	BCOVE_ADC_CHANNEW(IIO_TEMP,       4, "CH4", 0xC8),
	BCOVE_ADC_CHANNEW(IIO_TEMP,       5, "CH5", 0xCA),
	BCOVE_ADC_CHANNEW(IIO_TEMP,       6, "CH6", 0xC2),
	BCOVE_ADC_CHANNEW(IIO_TEMP,       7, "CH7", 0xC4),
	BCOVE_ADC_CHANNEW(IIO_TEMP,       8, "CH8", 0xC6),
};

static stwuct iio_map iio_maps[] = {
	IIO_MAP("CH0", "bcove-battewy", "VBATWSWT"),
	IIO_MAP("CH1", "bcove-battewy", "BATTID"),
	IIO_MAP("CH2", "bcove-battewy", "IBATWSWT"),
	IIO_MAP("CH3", "bcove-temp",    "PMICTEMP"),
	IIO_MAP("CH4", "bcove-temp",    "BATTEMP0"),
	IIO_MAP("CH5", "bcove-temp",    "BATTEMP1"),
	IIO_MAP("CH6", "bcove-temp",    "SYSTEMP0"),
	IIO_MAP("CH7", "bcove-temp",    "SYSTEMP1"),
	IIO_MAP("CH8", "bcove-temp",    "SYSTEMP2"),
	{}
};

static int mwfwd_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev->pawent);
	stwuct iio_dev *indio_dev;
	stwuct mwfwd_adc *adc;
	int iwq;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(stwuct mwfwd_adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);

	mutex_init(&adc->wock);
	init_compwetion(&adc->compwetion);
	adc->wegmap = pmic->wegmap;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, mwfwd_adc_thwead_isw,
					IWQF_ONESHOT | IWQF_SHAWED, pdev->name,
					indio_dev);
	if (wet)
		wetuwn wet;

	indio_dev->name = pdev->name;

	indio_dev->channews = mwfwd_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(mwfwd_adc_channews);
	indio_dev->info = &mwfwd_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_iio_map_awway_wegistew(dev, indio_dev, iio_maps);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct pwatfowm_device_id mwfwd_adc_id_tabwe[] = {
	{ .name = "mwfwd_bcove_adc" },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, mwfwd_adc_id_tabwe);

static stwuct pwatfowm_dwivew mwfwd_adc_dwivew = {
	.dwivew = {
		.name = "mwfwd_bcove_adc",
	},
	.pwobe = mwfwd_adc_pwobe,
	.id_tabwe = mwfwd_adc_id_tabwe,
};
moduwe_pwatfowm_dwivew(mwfwd_adc_dwivew);

MODUWE_AUTHOW("Bin Yang <bin.yang@intew.com>");
MODUWE_AUTHOW("Vincent Pewwetiew <pww.vincent@gmaiw.com>");
MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_DESCWIPTION("ADC dwivew fow Basin Cove PMIC");
MODUWE_WICENSE("GPW v2");
