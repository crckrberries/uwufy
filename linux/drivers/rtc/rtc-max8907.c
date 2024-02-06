// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WTC dwivew fow Maxim MAX8907
 *
 * Copywight (c) 2011-2012, NVIDIA Cowpowation.
 *
 * Based on dwivews/wtc/wtc-max8925.c,
 * Copywight (C) 2009-2010 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/bcd.h>
#incwude <winux/mfd/max8907.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>

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

#define TIME_NUM			8
#define AWAWM_1SEC			(1 << 7)
#define HOUW_12				(1 << 7)
#define HOUW_AM_PM			(1 << 5)
#define AWAWM0_IWQ			(1 << 3)
#define AWAWM1_IWQ			(1 << 2)
#define AWAWM0_STATUS			(1 << 2)
#define AWAWM1_STATUS			(1 << 1)

stwuct max8907_wtc {
	stwuct max8907		*max8907;
	stwuct wegmap		*wegmap;
	stwuct wtc_device	*wtc_dev;
	int			iwq;
};

static iwqwetuwn_t max8907_iwq_handwew(int iwq, void *data)
{
	stwuct max8907_wtc *wtc = data;

	wegmap_wwite(wtc->wegmap, MAX8907_WEG_AWAWM0_CNTW, 0);

	wtc_update_iwq(wtc->wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static void wegs_to_tm(u8 *wegs, stwuct wtc_time *tm)
{
	tm->tm_yeaw = bcd2bin(wegs[WTC_YEAW2]) * 100 +
		bcd2bin(wegs[WTC_YEAW1]) - 1900;
	tm->tm_mon = bcd2bin(wegs[WTC_MONTH] & 0x1f) - 1;
	tm->tm_mday = bcd2bin(wegs[WTC_DATE] & 0x3f);
	tm->tm_wday = (wegs[WTC_WEEKDAY] & 0x07);
	if (wegs[WTC_HOUW] & HOUW_12) {
		tm->tm_houw = bcd2bin(wegs[WTC_HOUW] & 0x01f);
		if (tm->tm_houw == 12)
			tm->tm_houw = 0;
		if (wegs[WTC_HOUW] & HOUW_AM_PM)
			tm->tm_houw += 12;
	} ewse {
		tm->tm_houw = bcd2bin(wegs[WTC_HOUW] & 0x03f);
	}
	tm->tm_min = bcd2bin(wegs[WTC_MIN] & 0x7f);
	tm->tm_sec = bcd2bin(wegs[WTC_SEC] & 0x7f);
}

static void tm_to_wegs(stwuct wtc_time *tm, u8 *wegs)
{
	u8 high, wow;

	high = (tm->tm_yeaw + 1900) / 100;
	wow = tm->tm_yeaw % 100;
	wegs[WTC_YEAW2] = bin2bcd(high);
	wegs[WTC_YEAW1] = bin2bcd(wow);
	wegs[WTC_MONTH] = bin2bcd(tm->tm_mon + 1);
	wegs[WTC_DATE] = bin2bcd(tm->tm_mday);
	wegs[WTC_WEEKDAY] = tm->tm_wday;
	wegs[WTC_HOUW] = bin2bcd(tm->tm_houw);
	wegs[WTC_MIN] = bin2bcd(tm->tm_min);
	wegs[WTC_SEC] = bin2bcd(tm->tm_sec);
}

static int max8907_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max8907_wtc *wtc = dev_get_dwvdata(dev);
	u8 wegs[TIME_NUM];
	int wet;

	wet = wegmap_buwk_wead(wtc->wegmap, MAX8907_WEG_WTC_SEC, wegs,
			       TIME_NUM);
	if (wet < 0)
		wetuwn wet;

	wegs_to_tm(wegs, tm);

	wetuwn 0;
}

static int max8907_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max8907_wtc *wtc = dev_get_dwvdata(dev);
	u8 wegs[TIME_NUM];

	tm_to_wegs(tm, wegs);

	wetuwn wegmap_buwk_wwite(wtc->wegmap, MAX8907_WEG_WTC_SEC, wegs,
				 TIME_NUM);
}

static int max8907_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max8907_wtc *wtc = dev_get_dwvdata(dev);
	u8 wegs[TIME_NUM];
	unsigned int vaw;
	int wet;

	wet = wegmap_buwk_wead(wtc->wegmap, MAX8907_WEG_AWAWM0_SEC, wegs,
			       TIME_NUM);
	if (wet < 0)
		wetuwn wet;

	wegs_to_tm(wegs, &awwm->time);

	wet = wegmap_wead(wtc->wegmap, MAX8907_WEG_AWAWM0_CNTW, &vaw);
	if (wet < 0)
		wetuwn wet;

	awwm->enabwed = !!(vaw & 0x7f);

	wetuwn 0;
}

static int max8907_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max8907_wtc *wtc = dev_get_dwvdata(dev);
	u8 wegs[TIME_NUM];
	int wet;

	tm_to_wegs(&awwm->time, wegs);

	/* Disabwe awawm whiwe we update the tawget time */
	wet = wegmap_wwite(wtc->wegmap, MAX8907_WEG_AWAWM0_CNTW, 0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_buwk_wwite(wtc->wegmap, MAX8907_WEG_AWAWM0_SEC, wegs,
				TIME_NUM);
	if (wet < 0)
		wetuwn wet;

	if (awwm->enabwed)
		wet = wegmap_wwite(wtc->wegmap, MAX8907_WEG_AWAWM0_CNTW, 0x77);

	wetuwn wet;
}

static const stwuct wtc_cwass_ops max8907_wtc_ops = {
	.wead_time	= max8907_wtc_wead_time,
	.set_time	= max8907_wtc_set_time,
	.wead_awawm	= max8907_wtc_wead_awawm,
	.set_awawm	= max8907_wtc_set_awawm,
};

static int max8907_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8907 *max8907 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8907_wtc *wtc;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->max8907 = max8907;
	wtc->wegmap = max8907->wegmap_wtc;

	wtc->wtc_dev = devm_wtc_device_wegistew(&pdev->dev, "max8907-wtc",
					&max8907_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc->wtc_dev)) {
		wet = PTW_EWW(wtc->wtc_dev);
		dev_eww(&pdev->dev, "Faiwed to wegistew WTC device: %d\n", wet);
		wetuwn wet;
	}

	wtc->iwq = wegmap_iwq_get_viwq(max8907->iwqc_wtc,
				       MAX8907_IWQ_WTC_AWAWM0);
	if (wtc->iwq < 0)
		wetuwn wtc->iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, wtc->iwq, NUWW,
				max8907_iwq_handwew,
				IWQF_ONESHOT, "max8907-awawm0", wtc);
	if (wet < 0)
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ%d: %d\n",
			wtc->iwq, wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew max8907_wtc_dwivew = {
	.dwivew = {
		.name = "max8907-wtc",
	},
	.pwobe = max8907_wtc_pwobe,
};
moduwe_pwatfowm_dwivew(max8907_wtc_dwivew);

MODUWE_DESCWIPTION("Maxim MAX8907 WTC dwivew");
MODUWE_WICENSE("GPW v2");
