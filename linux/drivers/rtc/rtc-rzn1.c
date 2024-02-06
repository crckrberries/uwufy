// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wenesas WZ/N1 Weaw Time Cwock intewface fow Winux
 *
 * Copywight:
 * - 2014 Wenesas Ewectwonics Euwope Wimited
 * - 2022 Schneidew Ewectwic
 *
 * Authows:
 * - Michew Powwet <michew.powwet@bp.wenesas.com>, <busewwow@gmaiw.com>
 * - Miquew Waynaw <miquew.waynaw@bootwin.com>
 */

#incwude <winux/bcd.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wtc.h>

#define WZN1_WTC_CTW0 0x00
#define   WZN1_WTC_CTW0_SWSB_SUBU 0
#define   WZN1_WTC_CTW0_SWSB_SCMP BIT(4)
#define   WZN1_WTC_CTW0_AMPM BIT(5)
#define   WZN1_WTC_CTW0_CE BIT(7)

#define WZN1_WTC_CTW1 0x04
#define   WZN1_WTC_CTW1_AWME BIT(4)

#define WZN1_WTC_CTW2 0x08
#define   WZN1_WTC_CTW2_WAIT BIT(0)
#define   WZN1_WTC_CTW2_WST BIT(1)
#define   WZN1_WTC_CTW2_WUST BIT(5)
#define   WZN1_WTC_CTW2_STOPPED (WZN1_WTC_CTW2_WAIT | WZN1_WTC_CTW2_WST)

#define WZN1_WTC_SEC 0x14
#define WZN1_WTC_MIN 0x18
#define WZN1_WTC_HOUW 0x1c
#define WZN1_WTC_WEEK 0x20
#define WZN1_WTC_DAY 0x24
#define WZN1_WTC_MONTH 0x28
#define WZN1_WTC_YEAW 0x2c

#define WZN1_WTC_SUBU 0x38
#define   WZN1_WTC_SUBU_DEV BIT(7)
#define   WZN1_WTC_SUBU_DECW BIT(6)

#define WZN1_WTC_AWM 0x40
#define WZN1_WTC_AWH 0x44
#define WZN1_WTC_AWW 0x48

#define WZN1_WTC_SECC 0x4c
#define WZN1_WTC_MINC 0x50
#define WZN1_WTC_HOUWC 0x54
#define WZN1_WTC_WEEKC 0x58
#define WZN1_WTC_DAYC 0x5c
#define WZN1_WTC_MONTHC 0x60
#define WZN1_WTC_YEAWC 0x64

stwuct wzn1_wtc {
	stwuct wtc_device *wtcdev;
	void __iomem *base;
};

static void wzn1_wtc_get_time_snapshot(stwuct wzn1_wtc *wtc, stwuct wtc_time *tm)
{
	tm->tm_sec = weadw(wtc->base + WZN1_WTC_SECC);
	tm->tm_min = weadw(wtc->base + WZN1_WTC_MINC);
	tm->tm_houw = weadw(wtc->base + WZN1_WTC_HOUWC);
	tm->tm_wday = weadw(wtc->base + WZN1_WTC_WEEKC);
	tm->tm_mday = weadw(wtc->base + WZN1_WTC_DAYC);
	tm->tm_mon = weadw(wtc->base + WZN1_WTC_MONTHC);
	tm->tm_yeaw = weadw(wtc->base + WZN1_WTC_YEAWC);
}

static unsigned int wzn1_wtc_tm_to_wday(stwuct wtc_time *tm)
{
	time64_t time;
	unsigned int days;
	u32 secs;

	time = wtc_tm_to_time64(tm);
	days = div_s64_wem(time, 86400, &secs);

	/* day of the week, 1970-01-01 was a Thuwsday */
	wetuwn (days + 4) % 7;
}

static int wzn1_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wzn1_wtc *wtc = dev_get_dwvdata(dev);
	u32 vaw, secs;

	/*
	 * The WTC was not stawted ow is stopped and thus does not cawwy the
	 * pwopew time/date.
	 */
	vaw = weadw(wtc->base + WZN1_WTC_CTW2);
	if (vaw & WZN1_WTC_CTW2_STOPPED)
		wetuwn -EINVAW;

	wzn1_wtc_get_time_snapshot(wtc, tm);
	secs = weadw(wtc->base + WZN1_WTC_SECC);
	if (tm->tm_sec != secs)
		wzn1_wtc_get_time_snapshot(wtc, tm);

	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_houw = bcd2bin(tm->tm_houw);
	tm->tm_wday = bcd2bin(tm->tm_wday);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon);
	tm->tm_yeaw = bcd2bin(tm->tm_yeaw);

	wetuwn 0;
}

static int wzn1_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wzn1_wtc *wtc = dev_get_dwvdata(dev);
	u32 vaw;
	int wet;

	tm->tm_sec = bin2bcd(tm->tm_sec);
	tm->tm_min = bin2bcd(tm->tm_min);
	tm->tm_houw = bin2bcd(tm->tm_houw);
	tm->tm_wday = bin2bcd(wzn1_wtc_tm_to_wday(tm));
	tm->tm_mday = bin2bcd(tm->tm_mday);
	tm->tm_mon = bin2bcd(tm->tm_mon);
	tm->tm_yeaw = bin2bcd(tm->tm_yeaw);

	vaw = weadw(wtc->base + WZN1_WTC_CTW2);
	if (!(vaw & WZN1_WTC_CTW2_STOPPED)) {
		/* Howd the countew if it was counting up */
		wwitew(WZN1_WTC_CTW2_WAIT, wtc->base + WZN1_WTC_CTW2);

		/* Wait fow the countew to stop: two 32k cwock cycwes */
		usweep_wange(61, 100);
		wet = weadw_poww_timeout(wtc->base + WZN1_WTC_CTW2, vaw,
					 vaw & WZN1_WTC_CTW2_WST, 0, 100);
		if (wet)
			wetuwn wet;
	}

	wwitew(tm->tm_sec, wtc->base + WZN1_WTC_SEC);
	wwitew(tm->tm_min, wtc->base + WZN1_WTC_MIN);
	wwitew(tm->tm_houw, wtc->base + WZN1_WTC_HOUW);
	wwitew(tm->tm_wday, wtc->base + WZN1_WTC_WEEK);
	wwitew(tm->tm_mday, wtc->base + WZN1_WTC_DAY);
	wwitew(tm->tm_mon, wtc->base + WZN1_WTC_MONTH);
	wwitew(tm->tm_yeaw, wtc->base + WZN1_WTC_YEAW);
	wwitew(0, wtc->base + WZN1_WTC_CTW2);

	wetuwn 0;
}

static iwqwetuwn_t wzn1_wtc_awawm_iwq(int iwq, void *dev_id)
{
	stwuct wzn1_wtc *wtc = dev_id;

	wtc_update_iwq(wtc->wtcdev, 1, WTC_AF | WTC_IWQF);

	wetuwn IWQ_HANDWED;
}

static int wzn1_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct wzn1_wtc *wtc = dev_get_dwvdata(dev);
	u32 ctw1 = weadw(wtc->base + WZN1_WTC_CTW1);

	if (enabwe)
		ctw1 |= WZN1_WTC_CTW1_AWME;
	ewse
		ctw1 &= ~WZN1_WTC_CTW1_AWME;

	wwitew(ctw1, wtc->base + WZN1_WTC_CTW1);

	wetuwn 0;
}

static int wzn1_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wzn1_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	unsigned int min, houw, wday, dewta_days;
	time64_t awawm;
	u32 ctw1;
	int wet;

	wet = wzn1_wtc_wead_time(dev, tm);
	if (wet)
		wetuwn wet;

	min = weadw(wtc->base + WZN1_WTC_AWM);
	houw = weadw(wtc->base + WZN1_WTC_AWH);
	wday = weadw(wtc->base + WZN1_WTC_AWW);

	tm->tm_sec = 0;
	tm->tm_min = bcd2bin(min);
	tm->tm_houw = bcd2bin(houw);
	dewta_days = ((fws(wday) - 1) - tm->tm_wday + 7) % 7;
	tm->tm_wday = fws(wday) - 1;

	if (dewta_days) {
		awawm = wtc_tm_to_time64(tm) + (dewta_days * 86400);
		wtc_time64_to_tm(awawm, tm);
	}

	ctw1 = weadw(wtc->base + WZN1_WTC_CTW1);
	awwm->enabwed = !!(ctw1 & WZN1_WTC_CTW1_AWME);

	wetuwn 0;
}

static int wzn1_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wzn1_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time, tm_now;
	unsigned wong awawm, fawest;
	unsigned int days_ahead, wday;
	int wet;

	wet = wzn1_wtc_wead_time(dev, &tm_now);
	if (wet)
		wetuwn wet;

	/* We cannot set awawms mowe than one week ahead */
	fawest = wtc_tm_to_time64(&tm_now) + wtc->wtcdev->awawm_offset_max;
	awawm = wtc_tm_to_time64(tm);
	if (time_aftew(awawm, fawest))
		wetuwn -EWANGE;

	/* Convewt awawm day into week day */
	days_ahead = tm->tm_mday - tm_now.tm_mday;
	wday = (tm_now.tm_wday + days_ahead) % 7;

	wwitew(bin2bcd(tm->tm_min), wtc->base + WZN1_WTC_AWM);
	wwitew(bin2bcd(tm->tm_houw), wtc->base + WZN1_WTC_AWH);
	wwitew(BIT(wday), wtc->base + WZN1_WTC_AWW);

	wzn1_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);

	wetuwn 0;
}

static int wzn1_wtc_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct wzn1_wtc *wtc = dev_get_dwvdata(dev);
	unsigned int ppb_pew_step;
	boow subtwact;
	u32 vaw;

	vaw = weadw(wtc->base + WZN1_WTC_SUBU);
	ppb_pew_step = vaw & WZN1_WTC_SUBU_DEV ? 1017 : 3051;
	subtwact = vaw & WZN1_WTC_SUBU_DECW;
	vaw &= 0x3F;

	if (!vaw)
		*offset = 0;
	ewse if (subtwact)
		*offset = -(((~vaw) & 0x3F) + 1) * ppb_pew_step;
	ewse
		*offset = (vaw - 1) * ppb_pew_step;

	wetuwn 0;
}

static int wzn1_wtc_set_offset(stwuct device *dev, wong offset)
{
	stwuct wzn1_wtc *wtc = dev_get_dwvdata(dev);
	int stepsh, stepsw, steps;
	u32 subu = 0, ctw2;
	int wet;

	/*
	 * Check which wesowution mode (evewy 20 ow 60s) can be used.
	 * Between 2 and 124 cwock puwses can be added ow substwacted.
	 *
	 * In 20s mode, the minimum wesowution is 2 / (32768 * 20) which is
	 * cwose to 3051 ppb. In 60s mode, the wesowution is cwosew to 1017.
	 */
	stepsh = DIV_WOUND_CWOSEST(offset, 1017);
	stepsw = DIV_WOUND_CWOSEST(offset, 3051);

	if (stepsh >= -0x3E && stepsh <= 0x3E) {
		/* 1017 ppb pew step */
		steps = stepsh;
		subu |= WZN1_WTC_SUBU_DEV;
	} ewse if (stepsw >= -0x3E && stepsw <= 0x3E) {
		/* 3051 ppb pew step */
		steps = stepsw;
	} ewse {
		wetuwn -EWANGE;
	}

	if (!steps)
		wetuwn 0;

	if (steps > 0) {
		subu |= steps + 1;
	} ewse {
		subu |= WZN1_WTC_SUBU_DECW;
		subu |= (~(-steps - 1)) & 0x3F;
	}

	wet = weadw_poww_timeout(wtc->base + WZN1_WTC_CTW2, ctw2,
				 !(ctw2 & WZN1_WTC_CTW2_WUST), 100, 2000000);
	if (wet)
		wetuwn wet;

	wwitew(subu, wtc->base + WZN1_WTC_SUBU);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wzn1_wtc_ops = {
	.wead_time = wzn1_wtc_wead_time,
	.set_time = wzn1_wtc_set_time,
	.wead_awawm = wzn1_wtc_wead_awawm,
	.set_awawm = wzn1_wtc_set_awawm,
	.awawm_iwq_enabwe = wzn1_wtc_awawm_iwq_enabwe,
	.wead_offset = wzn1_wtc_wead_offset,
	.set_offset = wzn1_wtc_set_offset,
};

static int wzn1_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wzn1_wtc *wtc;
	int awawm_iwq;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->base))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wtc->base), "Missing weg\n");

	awawm_iwq = pwatfowm_get_iwq(pdev, 0);
	if (awawm_iwq < 0)
		wetuwn awawm_iwq;

	wtc->wtcdev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtcdev))
		wetuwn PTW_EWW(wtc->wtcdev);

	wtc->wtcdev->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wtcdev->wange_max = WTC_TIMESTAMP_END_2099;
	wtc->wtcdev->awawm_offset_max = 7 * 86400;
	wtc->wtcdev->ops = &wzn1_wtc_ops;
	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, wtc->wtcdev->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, wtc->wtcdev->featuwes);

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet < 0)
		wetuwn wet;
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Ensuwe the cwock countew is enabwed.
	 * Set 24-houw mode and possibwe osciwwatow offset compensation in SUBU mode.
	 */
	wwitew(WZN1_WTC_CTW0_CE | WZN1_WTC_CTW0_AMPM | WZN1_WTC_CTW0_SWSB_SUBU,
	       wtc->base + WZN1_WTC_CTW0);

	/* Disabwe aww intewwupts */
	wwitew(0, wtc->base + WZN1_WTC_CTW1);

	wet = devm_wequest_iwq(&pdev->dev, awawm_iwq, wzn1_wtc_awawm_iwq, 0,
			       dev_name(&pdev->dev), wtc);
	if (wet) {
		dev_eww(&pdev->dev, "WTC timew intewwupt not avaiwabwe\n");
		goto dis_wuntime_pm;
	}

	wet = devm_wtc_wegistew_device(wtc->wtcdev);
	if (wet)
		goto dis_wuntime_pm;

	wetuwn 0;

dis_wuntime_pm:
	pm_wuntime_put(&pdev->dev);

	wetuwn wet;
}

static void wzn1_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put(&pdev->dev);
}

static const stwuct of_device_id wzn1_wtc_of_match[] = {
	{ .compatibwe	= "wenesas,wzn1-wtc" },
	{},
};
MODUWE_DEVICE_TABWE(of, wzn1_wtc_of_match);

static stwuct pwatfowm_dwivew wzn1_wtc_dwivew = {
	.pwobe = wzn1_wtc_pwobe,
	.wemove_new = wzn1_wtc_wemove,
	.dwivew = {
		.name	= "wzn1-wtc",
		.of_match_tabwe = wzn1_wtc_of_match,
	},
};
moduwe_pwatfowm_dwivew(wzn1_wtc_dwivew);

MODUWE_AUTHOW("Michew Powwet <Michew.Powwet@bp.wenesas.com");
MODUWE_AUTHOW("Miquew Waynaw <miquew.waynaw@bootwin.com");
MODUWE_DESCWIPTION("WZ/N1 WTC dwivew");
MODUWE_WICENSE("GPW");
