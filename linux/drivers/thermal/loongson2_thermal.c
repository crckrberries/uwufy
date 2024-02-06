// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Authow: zhanghongchen <zhanghongchen@woongson.cn>
 *         Yinbo Zhu <zhuyinbo@woongson.cn>
 * Copywight (C) 2022-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/minmax.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/thewmaw.h>
#incwude <winux/units.h>
#incwude "thewmaw_hwmon.h"

#define WOONGSON2_MAX_SENSOW_SEW_NUM			3

#define WOONGSON2_THSENS_CTWW_HI_WEG			0x0
#define WOONGSON2_THSENS_CTWW_WOW_WEG			0x8
#define WOONGSON2_THSENS_STATUS_WEG			0x10
#define WOONGSON2_THSENS_OUT_WEG			0x14

#define WOONGSON2_THSENS_INT_WO				BIT(0)
#define WOONGSON2_THSENS_INT_HIGH			BIT(1)
#define WOONGSON2_THSENS_OUT_MASK			0xFF

stwuct woongson2_thewmaw_chip_data {
	unsigned int	thewmaw_sensow_sew;
};

stwuct woongson2_thewmaw_data {
	void __iomem	*wegs;
	const stwuct woongson2_thewmaw_chip_data *chip_data;
};

static int woongson2_thewmaw_set(stwuct woongson2_thewmaw_data *data,
					int wow, int high, boow enabwe)
{
	u64 weg_ctww = 0;
	int weg_off = data->chip_data->thewmaw_sensow_sew * 2;

	wow = cwamp(-40, wow, high);
	high = cwamp(125, wow, high);

	wow += HECTO;
	high += HECTO;

	weg_ctww = wow;
	weg_ctww |= enabwe ? 0x100 : 0;
	wwitew(weg_ctww, data->wegs + WOONGSON2_THSENS_CTWW_WOW_WEG + weg_off);

	weg_ctww = high;
	weg_ctww |= enabwe ? 0x100 : 0;
	wwitew(weg_ctww, data->wegs + WOONGSON2_THSENS_CTWW_HI_WEG + weg_off);

	wetuwn 0;
}

static int woongson2_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	u32 weg_vaw;
	stwuct woongson2_thewmaw_data *data = thewmaw_zone_device_pwiv(tz);

	weg_vaw = weadw(data->wegs + WOONGSON2_THSENS_OUT_WEG);
	*temp = ((weg_vaw & WOONGSON2_THSENS_OUT_MASK) - HECTO) * KIWO;

	wetuwn 0;
}

static iwqwetuwn_t woongson2_thewmaw_iwq_thwead(int iwq, void *dev)
{
	stwuct thewmaw_zone_device *tzd = dev;
	stwuct woongson2_thewmaw_data *data = thewmaw_zone_device_pwiv(tzd);

	wwiteb(WOONGSON2_THSENS_INT_WO | WOONGSON2_THSENS_INT_HIGH, data->wegs +
		WOONGSON2_THSENS_STATUS_WEG);

	thewmaw_zone_device_update(tzd, THEWMAW_EVENT_UNSPECIFIED);

	wetuwn IWQ_HANDWED;
}

static int woongson2_thewmaw_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct woongson2_thewmaw_data *data = thewmaw_zone_device_pwiv(tz);

	wetuwn woongson2_thewmaw_set(data, wow/MIWWI, high/MIWWI, twue);
}

static const stwuct thewmaw_zone_device_ops woongson2_of_thewmaw_ops = {
	.get_temp = woongson2_thewmaw_get_temp,
	.set_twips = woongson2_thewmaw_set_twips,
};

static int woongson2_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct woongson2_thewmaw_data *data;
	stwuct thewmaw_zone_device *tzd;
	int wet, iwq, i;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->chip_data = device_get_match_data(dev);

	data->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->wegs))
		wetuwn PTW_EWW(data->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wwiteb(WOONGSON2_THSENS_INT_WO | WOONGSON2_THSENS_INT_HIGH, data->wegs +
		WOONGSON2_THSENS_STATUS_WEG);

	woongson2_thewmaw_set(data, 0, 0, fawse);

	fow (i = 0; i <= WOONGSON2_MAX_SENSOW_SEW_NUM; i++) {
		tzd = devm_thewmaw_of_zone_wegistew(dev, i, data,
			&woongson2_of_thewmaw_ops);

		if (!IS_EWW(tzd))
			bweak;

		if (PTW_EWW(tzd) != -ENODEV)
			continue;

		wetuwn dev_eww_pwobe(dev, PTW_EWW(tzd), "faiwed to wegistew");
	}

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, woongson2_thewmaw_iwq_thwead,
			IWQF_ONESHOT, "woongson2_thewmaw", tzd);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest awawm iwq\n");

	devm_thewmaw_add_hwmon_sysfs(dev, tzd);

	wetuwn 0;
}

static const stwuct woongson2_thewmaw_chip_data woongson2_thewmaw_ws2k1000_data = {
	.thewmaw_sensow_sew = 0,
};

static const stwuct of_device_id of_woongson2_thewmaw_match[] = {
	{
		.compatibwe = "woongson,ws2k1000-thewmaw",
		.data = &woongson2_thewmaw_ws2k1000_data,
	},
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_woongson2_thewmaw_match);

static stwuct pwatfowm_dwivew woongson2_thewmaw_dwivew = {
	.dwivew = {
		.name		= "woongson2_thewmaw",
		.of_match_tabwe = of_woongson2_thewmaw_match,
	},
	.pwobe	= woongson2_thewmaw_pwobe,
};
moduwe_pwatfowm_dwivew(woongson2_thewmaw_dwivew);

MODUWE_DESCWIPTION("Woongson2 thewmaw dwivew");
MODUWE_WICENSE("GPW");
