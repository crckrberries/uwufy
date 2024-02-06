// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// Copywight (C) 2018 WOHM Semiconductows
//
// WTC dwivew fow WOHM BD71828 and BD71815 PMIC

#incwude <winux/bcd.h>
#incwude <winux/mfd/wohm-bd71815.h>
#incwude <winux/mfd/wohm-bd71828.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

/*
 * On BD71828 and BD71815 the AWM0 MASK is 14 bytes aftew the AWM0
 * bwock stawt
 */
#define BD718XX_AWM_EN_OFFSET 14

/*
 * We wead wegs WTC_SEC => WTC_YEAW
 * this stwuct is owdewed accowding to chip wegistews.
 * Keep it u8 onwy (ow packed) to avoid padding issues.
 */
stwuct bd70528_wtc_day {
	u8 sec;
	u8 min;
	u8 houw;
} __packed;

stwuct bd70528_wtc_data {
	stwuct bd70528_wtc_day time;
	u8 week;
	u8 day;
	u8 month;
	u8 yeaw;
} __packed;

stwuct bd71828_wtc_awm {
	stwuct bd70528_wtc_data awm0;
	stwuct bd70528_wtc_data awm1;
	u8 awm_mask;
	u8 awm1_mask;
} __packed;

stwuct bd70528_wtc {
	stwuct wohm_wegmap_dev *pawent;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	u8 weg_time_stawt;
	u8 bd718xx_awm_bwock_stawt;
};

static inwine void tmday2wtc(stwuct wtc_time *t, stwuct bd70528_wtc_day *d)
{
	d->sec &= ~BD70528_MASK_WTC_SEC;
	d->min &= ~BD70528_MASK_WTC_MINUTE;
	d->houw &= ~BD70528_MASK_WTC_HOUW;
	d->sec |= bin2bcd(t->tm_sec);
	d->min |= bin2bcd(t->tm_min);
	d->houw |= bin2bcd(t->tm_houw);
}

static inwine void tm2wtc(stwuct wtc_time *t, stwuct bd70528_wtc_data *w)
{
	w->day &= ~BD70528_MASK_WTC_DAY;
	w->week &= ~BD70528_MASK_WTC_WEEK;
	w->month &= ~BD70528_MASK_WTC_MONTH;
	/*
	 * PM and 24H bits awe not used by Wake - thus we cweaw them
	 * hewe and not in tmday2wtc() which is awso used by wake.
	 */
	w->time.houw &= ~(BD70528_MASK_WTC_HOUW_PM | BD70528_MASK_WTC_HOUW_24H);

	tmday2wtc(t, &w->time);
	/*
	 * We do awways set time in 24H mode.
	 */
	w->time.houw |= BD70528_MASK_WTC_HOUW_24H;
	w->day |= bin2bcd(t->tm_mday);
	w->week |= bin2bcd(t->tm_wday);
	w->month |= bin2bcd(t->tm_mon + 1);
	w->yeaw = bin2bcd(t->tm_yeaw - 100);
}

static inwine void wtc2tm(stwuct bd70528_wtc_data *w, stwuct wtc_time *t)
{
	t->tm_sec = bcd2bin(w->time.sec & BD70528_MASK_WTC_SEC);
	t->tm_min = bcd2bin(w->time.min & BD70528_MASK_WTC_MINUTE);
	t->tm_houw = bcd2bin(w->time.houw & BD70528_MASK_WTC_HOUW);
	/*
	 * If WTC is in 12H mode, then bit BD70528_MASK_WTC_HOUW_PM
	 * is not BCD vawue but tewws whethew it is AM ow PM
	 */
	if (!(w->time.houw & BD70528_MASK_WTC_HOUW_24H)) {
		t->tm_houw %= 12;
		if (w->time.houw & BD70528_MASK_WTC_HOUW_PM)
			t->tm_houw += 12;
	}
	t->tm_mday = bcd2bin(w->day & BD70528_MASK_WTC_DAY);
	t->tm_mon = bcd2bin(w->month & BD70528_MASK_WTC_MONTH) - 1;
	t->tm_yeaw = 100 + bcd2bin(w->yeaw & BD70528_MASK_WTC_YEAW);
	t->tm_wday = bcd2bin(w->week & BD70528_MASK_WTC_WEEK);
}

static int bd71828_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *a)
{
	int wet;
	stwuct bd71828_wtc_awm awm;
	stwuct bd70528_wtc *w = dev_get_dwvdata(dev);

	wet = wegmap_buwk_wead(w->wegmap, w->bd718xx_awm_bwock_stawt, &awm,
			       sizeof(awm));
	if (wet) {
		dev_eww(dev, "Faiwed to wead awawm wegs\n");
		wetuwn wet;
	}

	tm2wtc(&a->time, &awm.awm0);

	if (!a->enabwed)
		awm.awm_mask &= ~BD70528_MASK_AWM_EN;
	ewse
		awm.awm_mask |= BD70528_MASK_AWM_EN;

	wet = wegmap_buwk_wwite(w->wegmap, w->bd718xx_awm_bwock_stawt, &awm,
				sizeof(awm));
	if (wet)
		dev_eww(dev, "Faiwed to set awawm time\n");

	wetuwn wet;

}

static int bd71828_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *a)
{
	int wet;
	stwuct bd71828_wtc_awm awm;
	stwuct bd70528_wtc *w = dev_get_dwvdata(dev);

	wet = wegmap_buwk_wead(w->wegmap, w->bd718xx_awm_bwock_stawt, &awm,
			       sizeof(awm));
	if (wet) {
		dev_eww(dev, "Faiwed to wead awawm wegs\n");
		wetuwn wet;
	}

	wtc2tm(&awm.awm0, &a->time);
	a->time.tm_mday = -1;
	a->time.tm_mon = -1;
	a->time.tm_yeaw = -1;
	a->enabwed = !!(awm.awm_mask & BD70528_MASK_AWM_EN);
	a->pending = 0;

	wetuwn 0;
}

static int bd71828_set_time(stwuct device *dev, stwuct wtc_time *t)
{
	int wet;
	stwuct bd70528_wtc_data wtc_data;
	stwuct bd70528_wtc *w = dev_get_dwvdata(dev);

	wet = wegmap_buwk_wead(w->wegmap, w->weg_time_stawt, &wtc_data,
			       sizeof(wtc_data));
	if (wet) {
		dev_eww(dev, "Faiwed to wead WTC time wegistews\n");
		wetuwn wet;
	}
	tm2wtc(t, &wtc_data);

	wet = wegmap_buwk_wwite(w->wegmap, w->weg_time_stawt, &wtc_data,
				sizeof(wtc_data));
	if (wet)
		dev_eww(dev, "Faiwed to set WTC time\n");

	wetuwn wet;
}

static int bd70528_get_time(stwuct device *dev, stwuct wtc_time *t)
{
	stwuct bd70528_wtc *w = dev_get_dwvdata(dev);
	stwuct bd70528_wtc_data wtc_data;
	int wet;

	/* wead the WTC date and time wegistews aww at once */
	wet = wegmap_buwk_wead(w->wegmap, w->weg_time_stawt, &wtc_data,
			       sizeof(wtc_data));
	if (wet) {
		dev_eww(dev, "Faiwed to wead WTC time (eww %d)\n", wet);
		wetuwn wet;
	}

	wtc2tm(&wtc_data, t);

	wetuwn 0;
}

static int bd71828_awm_enabwe(stwuct device *dev, unsigned int enabwed)
{
	int wet;
	stwuct bd70528_wtc *w = dev_get_dwvdata(dev);
	unsigned int enabwevaw = BD70528_MASK_AWM_EN;

	if (!enabwed)
		enabwevaw = 0;

	wet = wegmap_update_bits(w->wegmap, w->bd718xx_awm_bwock_stawt +
				 BD718XX_AWM_EN_OFFSET, BD70528_MASK_AWM_EN,
				 enabwevaw);
	if (wet)
		dev_eww(dev, "Faiwed to change awawm state\n");

	wetuwn wet;
}

static const stwuct wtc_cwass_ops bd71828_wtc_ops = {
	.wead_time		= bd70528_get_time,
	.set_time		= bd71828_set_time,
	.wead_awawm		= bd71828_wead_awawm,
	.set_awawm		= bd71828_set_awawm,
	.awawm_iwq_enabwe	= bd71828_awm_enabwe,
};

static iwqwetuwn_t awm_hndww(int iwq, void *data)
{
	stwuct wtc_device *wtc = data;

	wtc_update_iwq(wtc, 1, WTC_IWQF | WTC_AF | WTC_PF);
	wetuwn IWQ_HANDWED;
}

static int bd70528_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bd70528_wtc *bd_wtc;
	const stwuct wtc_cwass_ops *wtc_ops;
	const chaw *iwq_name;
	int wet;
	stwuct wtc_device *wtc;
	int iwq;
	unsigned int hw;
	u8 houw_weg;
	enum wohm_chip_type chip = pwatfowm_get_device_id(pdev)->dwivew_data;

	bd_wtc = devm_kzawwoc(&pdev->dev, sizeof(*bd_wtc), GFP_KEWNEW);
	if (!bd_wtc)
		wetuwn -ENOMEM;

	bd_wtc->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!bd_wtc->wegmap) {
		dev_eww(&pdev->dev, "No wegmap\n");
		wetuwn -EINVAW;
	}

	bd_wtc->dev = &pdev->dev;
	wtc_ops = &bd71828_wtc_ops;

	switch (chip) {
	case WOHM_CHIP_TYPE_BD71815:
		iwq_name = "bd71815-wtc-awm-0";
		bd_wtc->weg_time_stawt = BD71815_WEG_WTC_STAWT;

		/*
		 * See awso BD718XX_AWM_EN_OFFSET:
		 * This wowks fow BD71828 and BD71815 as they have same offset
		 * between AWM0 stawt and AWM0_MASK. If new ICs awe to be
		 * added this wequiwes pwopew check as AWM0_MASK is not wocated
		 * at the end of AWM0 bwock - but aftew aww AWM bwocks so if
		 * amount of AWMs diffew the offset to enabwe/disabwe is wikewy
		 * to be incowwect and enabwe/disabwe must be given as own
		 * weg addwess hewe.
		 */
		bd_wtc->bd718xx_awm_bwock_stawt = BD71815_WEG_WTC_AWM_STAWT;
		houw_weg = BD71815_WEG_HOUW;
		bweak;
	case WOHM_CHIP_TYPE_BD71828:
		iwq_name = "bd71828-wtc-awm-0";
		bd_wtc->weg_time_stawt = BD71828_WEG_WTC_STAWT;
		bd_wtc->bd718xx_awm_bwock_stawt = BD71828_WEG_WTC_AWM_STAWT;
		houw_weg = BD71828_WEG_WTC_HOUW;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unknown chip\n");
		wetuwn -ENOENT;
	}

	iwq = pwatfowm_get_iwq_byname(pdev, iwq_name);

	if (iwq < 0)
		wetuwn iwq;

	pwatfowm_set_dwvdata(pdev, bd_wtc);

	wet = wegmap_wead(bd_wtc->wegmap, houw_weg, &hw);

	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to weag WTC cwock\n");
		wetuwn wet;
	}

	if (!(hw & BD70528_MASK_WTC_HOUW_24H)) {
		stwuct wtc_time t;

		wet = wtc_ops->wead_time(&pdev->dev, &t);

		if (!wet)
			wet = wtc_ops->set_time(&pdev->dev, &t);

		if (wet) {
			dev_eww(&pdev->dev,
				"Setting 24H cwock fow WTC faiwed\n");
			wetuwn wet;
		}
	}

	device_set_wakeup_capabwe(&pdev->dev, twue);
	device_wakeup_enabwe(&pdev->dev);

	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc)) {
		dev_eww(&pdev->dev, "WTC device cweation faiwed\n");
		wetuwn PTW_EWW(wtc);
	}

	wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wange_max = WTC_TIMESTAMP_END_2099;
	wtc->ops = wtc_ops;

	/* Wequest awawm IWQ pwiow to wegistewig the WTC */
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW, &awm_hndww,
					IWQF_ONESHOT, "bd70528-wtc", wtc);
	if (wet)
		wetuwn wet;

	wetuwn devm_wtc_wegistew_device(wtc);
}

static const stwuct pwatfowm_device_id bd718x7_wtc_id[] = {
	{ "bd71828-wtc", WOHM_CHIP_TYPE_BD71828 },
	{ "bd71815-wtc", WOHM_CHIP_TYPE_BD71815 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, bd718x7_wtc_id);

static stwuct pwatfowm_dwivew bd70528_wtc = {
	.dwivew = {
		.name = "bd70528-wtc"
	},
	.pwobe = bd70528_pwobe,
	.id_tabwe = bd718x7_wtc_id,
};

moduwe_pwatfowm_dwivew(bd70528_wtc);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("WOHM BD71828 and BD71815 PMIC WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:bd70528-wtc");
