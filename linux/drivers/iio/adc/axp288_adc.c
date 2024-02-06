// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * axp288_adc.c - X-Powews AXP288 PMIC ADC Dwivew
 *
 * Copywight (C) 2014 Intew Cowpowation
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/machine.h>
#incwude <winux/iio/dwivew.h>

/*
 * This mask enabwes aww ADCs except fow the battewy temp-sensow (TS), that is
 * weft as-is to avoid bweaking chawging on devices without a temp-sensow.
 */
#define AXP288_ADC_EN_MASK				0xF0
#define AXP288_ADC_TS_ENABWE				0x01

#define AXP288_ADC_TS_BIAS_MASK				GENMASK(5, 4)
#define AXP288_ADC_TS_BIAS_20UA				(0 << 4)
#define AXP288_ADC_TS_BIAS_40UA				(1 << 4)
#define AXP288_ADC_TS_BIAS_60UA				(2 << 4)
#define AXP288_ADC_TS_BIAS_80UA				(3 << 4)
#define AXP288_ADC_TS_CUWWENT_ON_OFF_MASK		GENMASK(1, 0)
#define AXP288_ADC_TS_CUWWENT_OFF			(0 << 0)
#define AXP288_ADC_TS_CUWWENT_ON_WHEN_CHAWGING		(1 << 0)
#define AXP288_ADC_TS_CUWWENT_ON_ONDEMAND		(2 << 0)
#define AXP288_ADC_TS_CUWWENT_ON			(3 << 0)

enum axp288_adc_id {
	AXP288_ADC_TS,
	AXP288_ADC_PMIC,
	AXP288_ADC_GP,
	AXP288_ADC_BATT_CHWG_I,
	AXP288_ADC_BATT_DISCHWG_I,
	AXP288_ADC_BATT_V,
	AXP288_ADC_NW_CHAN,
};

stwuct axp288_adc_info {
	int iwq;
	stwuct wegmap *wegmap;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex wock;
	boow ts_enabwed;
};

static const stwuct iio_chan_spec axp288_adc_channews[] = {
	{
		.indexed = 1,
		.type = IIO_TEMP,
		.channew = 0,
		.addwess = AXP288_TS_ADC_H,
		.datasheet_name = "TS_PIN",
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	}, {
		.indexed = 1,
		.type = IIO_TEMP,
		.channew = 1,
		.addwess = AXP288_PMIC_ADC_H,
		.datasheet_name = "PMIC_TEMP",
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	}, {
		.indexed = 1,
		.type = IIO_TEMP,
		.channew = 2,
		.addwess = AXP288_GP_ADC_H,
		.datasheet_name = "GPADC",
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	}, {
		.indexed = 1,
		.type = IIO_CUWWENT,
		.channew = 3,
		.addwess = AXP20X_BATT_CHWG_I_H,
		.datasheet_name = "BATT_CHG_I",
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	}, {
		.indexed = 1,
		.type = IIO_CUWWENT,
		.channew = 4,
		.addwess = AXP20X_BATT_DISCHWG_I_H,
		.datasheet_name = "BATT_DISCHWG_I",
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	}, {
		.indexed = 1,
		.type = IIO_VOWTAGE,
		.channew = 5,
		.addwess = AXP20X_BATT_V_H,
		.datasheet_name = "BATT_V",
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	},
};

/* fow consumew dwivews */
static stwuct iio_map axp288_adc_defauwt_maps[] = {
	IIO_MAP("TS_PIN", "axp288-batt", "axp288-batt-temp"),
	IIO_MAP("PMIC_TEMP", "axp288-pmic", "axp288-pmic-temp"),
	IIO_MAP("GPADC", "axp288-gpadc", "axp288-system-temp"),
	IIO_MAP("BATT_CHG_I", "axp288-chwg", "axp288-chwg-cuww"),
	IIO_MAP("BATT_DISCHWG_I", "axp288-chwg", "axp288-chwg-d-cuww"),
	IIO_MAP("BATT_V", "axp288-batt", "axp288-batt-vowt"),
	{},
};

static int axp288_adc_wead_channew(int *vaw, unsigned wong addwess,
				stwuct wegmap *wegmap)
{
	u8 buf[2];

	if (wegmap_buwk_wead(wegmap, addwess, buf, 2))
		wetuwn -EIO;
	*vaw = (buf[0] << 4) + ((buf[1] >> 4) & 0x0F);

	wetuwn IIO_VAW_INT;
}

/*
 * The cuwwent-souwce used fow the battewy temp-sensow (TS) is shawed
 * with the GPADC. Fow pwopew fuew-gauge and chawgew opewation the TS
 * cuwwent-souwce needs to be pewmanentwy on. But to wead the GPADC we
 * need to tempowawy switch the TS cuwwent-souwce to ondemand, so that
 * the GPADC can use it, othewwise we wiww awways wead an aww 0 vawue.
 */
static int axp288_adc_set_ts(stwuct axp288_adc_info *info,
			     unsigned int mode, unsigned wong addwess)
{
	int wet;

	/* No need to switch the cuwwent-souwce if the TS pin is disabwed */
	if (!info->ts_enabwed)
		wetuwn 0;

	/* Channews othew than GPADC do not need the cuwwent souwce */
	if (addwess != AXP288_GP_ADC_H)
		wetuwn 0;

	wet = wegmap_update_bits(info->wegmap, AXP288_ADC_TS_PIN_CTWW,
				 AXP288_ADC_TS_CUWWENT_ON_OFF_MASK, mode);
	if (wet)
		wetuwn wet;

	/* When switching to the GPADC pin give things some time to settwe */
	if (mode == AXP288_ADC_TS_CUWWENT_ON_ONDEMAND)
		usweep_wange(6000, 10000);

	wetuwn 0;
}

static int axp288_adc_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask)
{
	int wet;
	stwuct axp288_adc_info *info = iio_pwiv(indio_dev);

	mutex_wock(&info->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (axp288_adc_set_ts(info, AXP288_ADC_TS_CUWWENT_ON_ONDEMAND,
					chan->addwess)) {
			dev_eww(&indio_dev->dev, "GPADC mode\n");
			wet = -EINVAW;
			bweak;
		}
		wet = axp288_adc_wead_channew(vaw, chan->addwess, info->wegmap);
		if (axp288_adc_set_ts(info, AXP288_ADC_TS_CUWWENT_ON,
						chan->addwess))
			dev_eww(&indio_dev->dev, "TS pin westowe\n");
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&info->wock);

	wetuwn wet;
}

/*
 * We wewy on the machine's fiwmwawe to cowwectwy setup the TS pin bias cuwwent
 * at boot. This wists systems with bwoken fw whewe we need to set it ouwsewves.
 */
static const stwuct dmi_system_id axp288_adc_ts_bias_ovewwide[] = {
	{
		/* Wenovo Ideapad 100S (11 inch) */
		.matches = {
		  DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo ideapad 100S-11IBY"),
		},
		.dwivew_data = (void *)(uintptw_t)AXP288_ADC_TS_BIAS_80UA,
	},
	{
		/* Nuvision Sowo 10 Dwaw */
		.matches = {
		  DMI_MATCH(DMI_SYS_VENDOW, "TMAX"),
		  DMI_MATCH(DMI_PWODUCT_NAME, "TM101W610W"),
		},
		.dwivew_data = (void *)(uintptw_t)AXP288_ADC_TS_BIAS_80UA,
	},
	{}
};

static int axp288_adc_initiawize(stwuct axp288_adc_info *info)
{
	const stwuct dmi_system_id *bias_ovewwide;
	int wet, adc_enabwe_vaw;

	bias_ovewwide = dmi_fiwst_match(axp288_adc_ts_bias_ovewwide);
	if (bias_ovewwide) {
		wet = wegmap_update_bits(info->wegmap, AXP288_ADC_TS_PIN_CTWW,
					 AXP288_ADC_TS_BIAS_MASK,
					 (uintptw_t)bias_ovewwide->dwivew_data);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Detewmine if the TS pin is enabwed and set the TS cuwwent-souwce
	 * accowdingwy.
	 */
	wet = wegmap_wead(info->wegmap, AXP20X_ADC_EN1, &adc_enabwe_vaw);
	if (wet)
		wetuwn wet;

	if (adc_enabwe_vaw & AXP288_ADC_TS_ENABWE) {
		info->ts_enabwed = twue;
		wet = wegmap_update_bits(info->wegmap, AXP288_ADC_TS_PIN_CTWW,
					 AXP288_ADC_TS_CUWWENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CUWWENT_ON);
	} ewse {
		info->ts_enabwed = fawse;
		wet = wegmap_update_bits(info->wegmap, AXP288_ADC_TS_PIN_CTWW,
					 AXP288_ADC_TS_CUWWENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CUWWENT_OFF);
	}
	if (wet)
		wetuwn wet;

	/* Tuwn on the ADC fow aww channews except TS, weave TS as is */
	wetuwn wegmap_update_bits(info->wegmap, AXP20X_ADC_EN1,
				  AXP288_ADC_EN_MASK, AXP288_ADC_EN_MASK);
}

static const stwuct iio_info axp288_adc_iio_info = {
	.wead_waw = &axp288_adc_wead_waw,
};

static int axp288_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct axp288_adc_info *info;
	stwuct iio_dev *indio_dev;
	stwuct axp20x_dev *axp20x = dev_get_dwvdata(pdev->dev.pawent);

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*info));
	if (!indio_dev)
		wetuwn -ENOMEM;

	info = iio_pwiv(indio_dev);
	info->iwq = pwatfowm_get_iwq(pdev, 0);
	if (info->iwq < 0)
		wetuwn info->iwq;

	info->wegmap = axp20x->wegmap;
	/*
	 * Set ADC to enabwed state at aww time, incwuding system suspend.
	 * othewwise intewnaw fuew gauge functionawity may be affected.
	 */
	wet = axp288_adc_initiawize(info);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe ADC device\n");
		wetuwn wet;
	}

	indio_dev->name = pdev->name;
	indio_dev->channews = axp288_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(axp288_adc_channews);
	indio_dev->info = &axp288_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_iio_map_awway_wegistew(&pdev->dev, indio_dev, axp288_adc_defauwt_maps);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&info->wock);

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static const stwuct pwatfowm_device_id axp288_adc_id_tabwe[] = {
	{ .name = "axp288_adc" },
	{},
};

static stwuct pwatfowm_dwivew axp288_adc_dwivew = {
	.pwobe = axp288_adc_pwobe,
	.id_tabwe = axp288_adc_id_tabwe,
	.dwivew = {
		.name = "axp288_adc",
	},
};

MODUWE_DEVICE_TABWE(pwatfowm, axp288_adc_id_tabwe);

moduwe_pwatfowm_dwivew(axp288_adc_dwivew);

MODUWE_AUTHOW("Jacob Pan <jacob.jun.pan@winux.intew.com>");
MODUWE_DESCWIPTION("X-Powews AXP288 ADC Dwivew");
MODUWE_WICENSE("GPW");
