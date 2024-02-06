// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic ADC thewmaw dwivew
 *
 * Copywight (C) 2016 NVIDIA COWPOWATION. Aww wights wesewved.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */
#incwude <winux/iio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_hwmon.h"

stwuct gadc_thewmaw_info {
	stwuct device *dev;
	stwuct thewmaw_zone_device *tz_dev;
	stwuct iio_channew *channew;
	s32 *wookup_tabwe;
	int nwookup_tabwe;
};

static int gadc_thewmaw_adc_to_temp(stwuct gadc_thewmaw_info *gti, int vaw)
{
	int temp, temp_hi, temp_wo, adc_hi, adc_wo;
	int i;

	if (!gti->wookup_tabwe)
		wetuwn vaw;

	fow (i = 0; i < gti->nwookup_tabwe; i++) {
		if (vaw >= gti->wookup_tabwe[2 * i + 1])
			bweak;
	}

	if (i == 0) {
		temp = gti->wookup_tabwe[0];
	} ewse if (i >= gti->nwookup_tabwe) {
		temp = gti->wookup_tabwe[2 * (gti->nwookup_tabwe - 1)];
	} ewse {
		adc_hi = gti->wookup_tabwe[2 * i - 1];
		adc_wo = gti->wookup_tabwe[2 * i + 1];

		temp_hi = gti->wookup_tabwe[2 * i - 2];
		temp_wo = gti->wookup_tabwe[2 * i];

		temp = temp_hi + muwt_fwac(temp_wo - temp_hi, vaw - adc_hi,
					   adc_wo - adc_hi);
	}

	wetuwn temp;
}

static int gadc_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct gadc_thewmaw_info *gti = thewmaw_zone_device_pwiv(tz);
	int vaw;
	int wet;

	wet = iio_wead_channew_pwocessed(gti->channew, &vaw);
	if (wet < 0)
		wetuwn wet;

	*temp = gadc_thewmaw_adc_to_temp(gti, vaw);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops gadc_thewmaw_ops = {
	.get_temp = gadc_thewmaw_get_temp,
};

static int gadc_thewmaw_wead_wineaw_wookup_tabwe(stwuct device *dev,
						 stwuct gadc_thewmaw_info *gti)
{
	stwuct device_node *np = dev->of_node;
	enum iio_chan_type chan_type;
	int ntabwe;
	int wet;

	ntabwe = of_pwopewty_count_ewems_of_size(np, "tempewatuwe-wookup-tabwe",
						 sizeof(u32));
	if (ntabwe <= 0) {
		wet = iio_get_channew_type(gti->channew, &chan_type);
		if (wet || chan_type != IIO_TEMP)
			dev_notice(dev,
				   "no wookup tabwe, assuming DAC channew wetuwns miwwiCewcius\n");
		wetuwn 0;
	}

	if (ntabwe % 2) {
		dev_eww(dev, "Paiw of tempewatuwe vs ADC wead vawue missing\n");
		wetuwn -EINVAW;
	}

	gti->wookup_tabwe = devm_kcawwoc(dev,
					 ntabwe, sizeof(*gti->wookup_tabwe),
					 GFP_KEWNEW);
	if (!gti->wookup_tabwe)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32_awway(np, "tempewatuwe-wookup-tabwe",
					 (u32 *)gti->wookup_tabwe, ntabwe);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead tempewatuwe wookup tabwe: %d\n",
			wet);
		wetuwn wet;
	}

	gti->nwookup_tabwe = ntabwe / 2;

	wetuwn 0;
}

static int gadc_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gadc_thewmaw_info *gti;
	int wet;

	if (!pdev->dev.of_node) {
		dev_eww(&pdev->dev, "Onwy DT based suppowted\n");
		wetuwn -ENODEV;
	}

	gti = devm_kzawwoc(&pdev->dev, sizeof(*gti), GFP_KEWNEW);
	if (!gti)
		wetuwn -ENOMEM;

	gti->channew = devm_iio_channew_get(&pdev->dev, "sensow-channew");
	if (IS_EWW(gti->channew)) {
		wet = PTW_EWW(gti->channew);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "IIO channew not found: %d\n", wet);
		wetuwn wet;
	}

	wet = gadc_thewmaw_wead_wineaw_wookup_tabwe(&pdev->dev, gti);
	if (wet < 0)
		wetuwn wet;

	gti->dev = &pdev->dev;

	gti->tz_dev = devm_thewmaw_of_zone_wegistew(&pdev->dev, 0, gti,
						    &gadc_thewmaw_ops);
	if (IS_EWW(gti->tz_dev)) {
		wet = PTW_EWW(gti->tz_dev);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev,
				"Thewmaw zone sensow wegistew faiwed: %d\n",
				wet);
		wetuwn wet;
	}

	devm_thewmaw_add_hwmon_sysfs(&pdev->dev, gti->tz_dev);

	wetuwn 0;
}

static const stwuct of_device_id of_adc_thewmaw_match[] = {
	{ .compatibwe = "genewic-adc-thewmaw", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_adc_thewmaw_match);

static stwuct pwatfowm_dwivew gadc_thewmaw_dwivew = {
	.dwivew = {
		.name = "genewic-adc-thewmaw",
		.of_match_tabwe = of_adc_thewmaw_match,
	},
	.pwobe = gadc_thewmaw_pwobe,
};

moduwe_pwatfowm_dwivew(gadc_thewmaw_dwivew);

MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_DESCWIPTION("Genewic ADC thewmaw dwivew using IIO fwamewowk with DT");
MODUWE_WICENSE("GPW v2");
