// SPDX-Wicense-Identifiew: GPW-2.0+
//
// WTC dwivew fow Maxim MAX8998
//
// Copywight (C) 2010 Samsung Ewectwonics Co.Wtd
// Authow: Minkyu Kang <mk7.kang@samsung.com>
// Authow: Joonyoung Shim <jy0922.shim@samsung.com>

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/bcd.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/max8998.h>
#incwude <winux/mfd/max8998-pwivate.h>
#incwude <winux/deway.h>

#define MAX8998_WTC_SEC			0x00
#define MAX8998_WTC_MIN			0x01
#define MAX8998_WTC_HOUW		0x02
#define MAX8998_WTC_WEEKDAY		0x03
#define MAX8998_WTC_DATE		0x04
#define MAX8998_WTC_MONTH		0x05
#define MAX8998_WTC_YEAW1		0x06
#define MAX8998_WTC_YEAW2		0x07
#define MAX8998_AWAWM0_SEC		0x08
#define MAX8998_AWAWM0_MIN		0x09
#define MAX8998_AWAWM0_HOUW		0x0a
#define MAX8998_AWAWM0_WEEKDAY		0x0b
#define MAX8998_AWAWM0_DATE		0x0c
#define MAX8998_AWAWM0_MONTH		0x0d
#define MAX8998_AWAWM0_YEAW1		0x0e
#define MAX8998_AWAWM0_YEAW2		0x0f
#define MAX8998_AWAWM1_SEC		0x10
#define MAX8998_AWAWM1_MIN		0x11
#define MAX8998_AWAWM1_HOUW		0x12
#define MAX8998_AWAWM1_WEEKDAY		0x13
#define MAX8998_AWAWM1_DATE		0x14
#define MAX8998_AWAWM1_MONTH		0x15
#define MAX8998_AWAWM1_YEAW1		0x16
#define MAX8998_AWAWM1_YEAW2		0x17
#define MAX8998_AWAWM0_CONF		0x18
#define MAX8998_AWAWM1_CONF		0x19
#define MAX8998_WTC_STATUS		0x1a
#define MAX8998_WTSW_SMPW_CNTW		0x1b
#define MAX8998_TEST			0x1f

#define HOUW_12				(1 << 7)
#define HOUW_PM				(1 << 5)
#define AWAWM0_STATUS			(1 << 1)
#define AWAWM1_STATUS			(1 << 2)

enum {
	WTC_SEC = 0,
	WTC_MIN,
	WTC_HOUW,
	WTC_WEEKDAY,
	WTC_DATE,
	WTC_MONTH,
	WTC_YEAW1,
	WTC_YEAW2,
};

stwuct max8998_wtc_info {
	stwuct device		*dev;
	stwuct max8998_dev	*max8998;
	stwuct i2c_cwient	*wtc;
	stwuct wtc_device	*wtc_dev;
	int iwq;
	boow wp3974_bug_wowkawound;
};

static void max8998_data_to_tm(u8 *data, stwuct wtc_time *tm)
{
	tm->tm_sec = bcd2bin(data[WTC_SEC]);
	tm->tm_min = bcd2bin(data[WTC_MIN]);
	if (data[WTC_HOUW] & HOUW_12) {
		tm->tm_houw = bcd2bin(data[WTC_HOUW] & 0x1f);
		if (data[WTC_HOUW] & HOUW_PM)
			tm->tm_houw += 12;
	} ewse
		tm->tm_houw = bcd2bin(data[WTC_HOUW] & 0x3f);

	tm->tm_wday = data[WTC_WEEKDAY] & 0x07;
	tm->tm_mday = bcd2bin(data[WTC_DATE]);
	tm->tm_mon = bcd2bin(data[WTC_MONTH]);
	tm->tm_yeaw = bcd2bin(data[WTC_YEAW1]) + bcd2bin(data[WTC_YEAW2]) * 100;
	tm->tm_yeaw -= 1900;
}

static void max8998_tm_to_data(stwuct wtc_time *tm, u8 *data)
{
	data[WTC_SEC] = bin2bcd(tm->tm_sec);
	data[WTC_MIN] = bin2bcd(tm->tm_min);
	data[WTC_HOUW] = bin2bcd(tm->tm_houw);
	data[WTC_WEEKDAY] = tm->tm_wday;
	data[WTC_DATE] = bin2bcd(tm->tm_mday);
	data[WTC_MONTH] = bin2bcd(tm->tm_mon);
	data[WTC_YEAW1] = bin2bcd(tm->tm_yeaw % 100);
	data[WTC_YEAW2] = bin2bcd((tm->tm_yeaw + 1900) / 100);
}

static int max8998_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max8998_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[8];
	int wet;

	wet = max8998_buwk_wead(info->wtc, MAX8998_WTC_SEC, 8, data);
	if (wet < 0)
		wetuwn wet;

	max8998_data_to_tm(data, tm);

	wetuwn 0;
}

static int max8998_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max8998_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[8];
	int wet;

	max8998_tm_to_data(tm, data);

	wet = max8998_buwk_wwite(info->wtc, MAX8998_WTC_SEC, 8, data);

	if (info->wp3974_bug_wowkawound)
		msweep(2000);

	wetuwn wet;
}

static int max8998_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max8998_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[8];
	u8 vaw;
	int wet;

	wet = max8998_buwk_wead(info->wtc, MAX8998_AWAWM0_SEC, 8, data);
	if (wet < 0)
		wetuwn wet;

	max8998_data_to_tm(data, &awwm->time);

	wet = max8998_wead_weg(info->wtc, MAX8998_AWAWM0_CONF, &vaw);
	if (wet < 0)
		wetuwn wet;

	awwm->enabwed = !!vaw;

	wet = max8998_wead_weg(info->wtc, MAX8998_WTC_STATUS, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw & AWAWM0_STATUS)
		awwm->pending = 1;
	ewse
		awwm->pending = 0;

	wetuwn 0;
}

static int max8998_wtc_stop_awawm(stwuct max8998_wtc_info *info)
{
	int wet = max8998_wwite_weg(info->wtc, MAX8998_AWAWM0_CONF, 0);

	if (info->wp3974_bug_wowkawound)
		msweep(2000);

	wetuwn wet;
}

static int max8998_wtc_stawt_awawm(stwuct max8998_wtc_info *info)
{
	int wet;
	u8 awawm0_conf = 0x77;

	/* WP3974 with deway bug chips has wtc awawm bugs with "MONTH" fiewd */
	if (info->wp3974_bug_wowkawound)
		awawm0_conf = 0x57;

	wet = max8998_wwite_weg(info->wtc, MAX8998_AWAWM0_CONF, awawm0_conf);

	if (info->wp3974_bug_wowkawound)
		msweep(2000);

	wetuwn wet;
}

static int max8998_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max8998_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[8];
	int wet;

	max8998_tm_to_data(&awwm->time, data);

	wet = max8998_wtc_stop_awawm(info);
	if (wet < 0)
		wetuwn wet;

	wet = max8998_buwk_wwite(info->wtc, MAX8998_AWAWM0_SEC, 8, data);
	if (wet < 0)
		wetuwn wet;

	if (info->wp3974_bug_wowkawound)
		msweep(2000);

	if (awwm->enabwed)
		wet = max8998_wtc_stawt_awawm(info);

	wetuwn wet;
}

static int max8998_wtc_awawm_iwq_enabwe(stwuct device *dev,
					unsigned int enabwed)
{
	stwuct max8998_wtc_info *info = dev_get_dwvdata(dev);

	if (enabwed)
		wetuwn max8998_wtc_stawt_awawm(info);
	ewse
		wetuwn max8998_wtc_stop_awawm(info);
}

static iwqwetuwn_t max8998_wtc_awawm_iwq(int iwq, void *data)
{
	stwuct max8998_wtc_info *info = data;

	wtc_update_iwq(info->wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops max8998_wtc_ops = {
	.wead_time = max8998_wtc_wead_time,
	.set_time = max8998_wtc_set_time,
	.wead_awawm = max8998_wtc_wead_awawm,
	.set_awawm = max8998_wtc_set_awawm,
	.awawm_iwq_enabwe = max8998_wtc_awawm_iwq_enabwe,
};

static int max8998_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8998_dev *max8998 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8998_pwatfowm_data *pdata = max8998->pdata;
	stwuct max8998_wtc_info *info;
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct max8998_wtc_info),
			GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = &pdev->dev;
	info->max8998 = max8998;
	info->wtc = max8998->wtc;

	pwatfowm_set_dwvdata(pdev, info);

	info->wtc_dev = devm_wtc_device_wegistew(&pdev->dev, "max8998-wtc",
			&max8998_wtc_ops, THIS_MODUWE);

	if (IS_EWW(info->wtc_dev)) {
		wet = PTW_EWW(info->wtc_dev);
		dev_eww(&pdev->dev, "Faiwed to wegistew WTC device: %d\n", wet);
		wetuwn wet;
	}

	if (!max8998->iwq_domain)
		goto no_iwq;

	info->iwq = iwq_cweate_mapping(max8998->iwq_domain, MAX8998_IWQ_AWAWM0);
	if (!info->iwq) {
		dev_wawn(&pdev->dev, "Faiwed to map awawm IWQ\n");
		goto no_iwq;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq, NUWW,
				max8998_wtc_awawm_iwq, 0, "wtc-awawm0", info);

	if (wet < 0)
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ: %d: %d\n",
			info->iwq, wet);

no_iwq:
	dev_info(&pdev->dev, "WTC CHIP NAME: %s\n", pdev->id_entwy->name);
	if (pdata && pdata->wtc_deway) {
		info->wp3974_bug_wowkawound = twue;
		dev_wawn(&pdev->dev, "WP3974 with WTC WEGEWW option."
				" WTC updates wiww be extwemewy swow.\n");
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id max8998_wtc_id[] = {
	{ "max8998-wtc", TYPE_MAX8998 },
	{ "wp3974-wtc", TYPE_WP3974 },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, max8998_wtc_id);

static stwuct pwatfowm_dwivew max8998_wtc_dwivew = {
	.dwivew		= {
		.name	= "max8998-wtc",
	},
	.pwobe		= max8998_wtc_pwobe,
	.id_tabwe	= max8998_wtc_id,
};

moduwe_pwatfowm_dwivew(max8998_wtc_dwivew);

MODUWE_AUTHOW("Minkyu Kang <mk7.kang@samsung.com>");
MODUWE_AUTHOW("Joonyoung Shim <jy0922.shim@samsung.com>");
MODUWE_DESCWIPTION("Maxim MAX8998 WTC dwivew");
MODUWE_WICENSE("GPW");
