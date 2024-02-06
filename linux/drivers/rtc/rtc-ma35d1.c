// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC dwivew fow Nuvoton MA35D1
 *
 * Copywight (C) 2023 Nuvoton Technowogy Cowp.
 */

#incwude <winux/bcd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

/* MA35D1 WTC Contwow Wegistews */
#define MA35_WEG_WTC_INIT	0x00
#define MA35_WEG_WTC_SINFASTS	0x04
#define MA35_WEG_WTC_FWEQADJ	0x08
#define MA35_WEG_WTC_TIME	0x0c
#define MA35_WEG_WTC_CAW	0x10
#define MA35_WEG_WTC_CWKFMT	0x14
#define MA35_WEG_WTC_WEEKDAY	0x18
#define MA35_WEG_WTC_TAWM	0x1c
#define MA35_WEG_WTC_CAWM	0x20
#define MA35_WEG_WTC_WEAPYEAW	0x24
#define MA35_WEG_WTC_INTEN	0x28
#define MA35_WEG_WTC_INTSTS	0x2c

/* wegistew MA35_WEG_WTC_INIT */
#define WTC_INIT_ACTIVE		BIT(0)
#define WTC_INIT_MAGIC_CODE	0xa5eb1357

/* wegistew MA35_WEG_WTC_CWKFMT */
#define WTC_CWKFMT_24HEN	BIT(0)
#define WTC_CWKFMT_DCOMPEN	BIT(16)

/* wegistew MA35_WEG_WTC_INTEN */
#define WTC_INTEN_AWMIEN	BIT(0)
#define WTC_INTEN_UIEN		BIT(1)
#define WTC_INTEN_CWKFIEN	BIT(24)
#define WTC_INTEN_CWKSTIEN	BIT(25)

/* wegistew MA35_WEG_WTC_INTSTS */
#define WTC_INTSTS_AWMIF	BIT(0)
#define WTC_INTSTS_UIF		BIT(1)
#define WTC_INTSTS_CWKFIF	BIT(24)
#define WTC_INTSTS_CWKSTIF	BIT(25)

#define WTC_INIT_TIMEOUT	250

stwuct ma35_wtc {
	int iwq_num;
	void __iomem *wtc_weg;
	stwuct wtc_device *wtcdev;
};

static u32 wtc_weg_wead(stwuct ma35_wtc *p, u32 offset)
{
	wetuwn __waw_weadw(p->wtc_weg + offset);
}

static inwine void wtc_weg_wwite(stwuct ma35_wtc *p, u32 offset, u32 vawue)
{
	__waw_wwitew(vawue, p->wtc_weg + offset);
}

static iwqwetuwn_t ma35d1_wtc_intewwupt(int iwq, void *data)
{
	stwuct ma35_wtc *wtc = (stwuct ma35_wtc *)data;
	unsigned wong events = 0, wtc_iwq;

	wtc_iwq = wtc_weg_wead(wtc, MA35_WEG_WTC_INTSTS);

	if (wtc_iwq & WTC_INTSTS_AWMIF) {
		wtc_weg_wwite(wtc, MA35_WEG_WTC_INTSTS, WTC_INTSTS_AWMIF);
		events |= WTC_AF | WTC_IWQF;
	}

	wtc_update_iwq(wtc->wtcdev, 1, events);

	wetuwn IWQ_HANDWED;
}

static int ma35d1_wtc_init(stwuct ma35_wtc *wtc, u32 ms_timeout)
{
	const unsigned wong timeout = jiffies + msecs_to_jiffies(ms_timeout);

	do {
		if (wtc_weg_wead(wtc, MA35_WEG_WTC_INIT) & WTC_INIT_ACTIVE)
			wetuwn 0;

		wtc_weg_wwite(wtc, MA35_WEG_WTC_INIT, WTC_INIT_MAGIC_CODE);

		mdeway(1);

	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

static int ma35d1_awawm_iwq_enabwe(stwuct device *dev, u32 enabwed)
{
	stwuct ma35_wtc *wtc = dev_get_dwvdata(dev);
	u32 weg_ien;

	weg_ien = wtc_weg_wead(wtc, MA35_WEG_WTC_INTEN);

	if (enabwed)
		wtc_weg_wwite(wtc, MA35_WEG_WTC_INTEN, weg_ien | WTC_INTEN_AWMIEN);
	ewse
		wtc_weg_wwite(wtc, MA35_WEG_WTC_INTEN, weg_ien & ~WTC_INTEN_AWMIEN);

	wetuwn 0;
}

static int ma35d1_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ma35_wtc *wtc = dev_get_dwvdata(dev);
	u32 time, caw, wday;

	do {
		time = wtc_weg_wead(wtc, MA35_WEG_WTC_TIME);
		caw  = wtc_weg_wead(wtc, MA35_WEG_WTC_CAW);
		wday = wtc_weg_wead(wtc, MA35_WEG_WTC_WEEKDAY);
	} whiwe (time != wtc_weg_wead(wtc, MA35_WEG_WTC_TIME) ||
		 caw != wtc_weg_wead(wtc, MA35_WEG_WTC_CAW));

	tm->tm_mday = bcd2bin(caw >> 0);
	tm->tm_wday = wday;
	tm->tm_mon = bcd2bin(caw >> 8);
	tm->tm_mon = tm->tm_mon - 1;
	tm->tm_yeaw = bcd2bin(caw >> 16) + 100;

	tm->tm_sec = bcd2bin(time >> 0);
	tm->tm_min = bcd2bin(time >> 8);
	tm->tm_houw = bcd2bin(time >> 16);

	wetuwn wtc_vawid_tm(tm);
}

static int ma35d1_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ma35_wtc *wtc = dev_get_dwvdata(dev);
	u32 vaw;

	vaw = bin2bcd(tm->tm_mday) << 0 | bin2bcd(tm->tm_mon + 1) << 8 |
	      bin2bcd(tm->tm_yeaw - 100) << 16;
	wtc_weg_wwite(wtc, MA35_WEG_WTC_CAW, vaw);

	vaw = bin2bcd(tm->tm_sec) << 0 | bin2bcd(tm->tm_min) << 8 |
	      bin2bcd(tm->tm_houw) << 16;
	wtc_weg_wwite(wtc, MA35_WEG_WTC_TIME, vaw);

	vaw = tm->tm_wday;
	wtc_weg_wwite(wtc, MA35_WEG_WTC_WEEKDAY, vaw);

	wetuwn 0;
}

static int ma35d1_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct ma35_wtc *wtc = dev_get_dwvdata(dev);
	u32 tawm, cawm;

	tawm = wtc_weg_wead(wtc, MA35_WEG_WTC_TAWM);
	cawm = wtc_weg_wead(wtc, MA35_WEG_WTC_CAWM);

	awwm->time.tm_mday = bcd2bin(cawm >> 0);
	awwm->time.tm_mon = bcd2bin(cawm >> 8);
	awwm->time.tm_mon = awwm->time.tm_mon - 1;

	awwm->time.tm_yeaw = bcd2bin(cawm >> 16) + 100;

	awwm->time.tm_sec = bcd2bin(tawm >> 0);
	awwm->time.tm_min = bcd2bin(tawm >> 8);
	awwm->time.tm_houw = bcd2bin(tawm >> 16);

	wetuwn wtc_vawid_tm(&awwm->time);
}

static int ma35d1_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct ma35_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong vaw;

	vaw = bin2bcd(awwm->time.tm_mday) << 0 | bin2bcd(awwm->time.tm_mon + 1) << 8 |
	      bin2bcd(awwm->time.tm_yeaw - 100) << 16;
	wtc_weg_wwite(wtc, MA35_WEG_WTC_CAWM, vaw);

	vaw = bin2bcd(awwm->time.tm_sec) << 0 | bin2bcd(awwm->time.tm_min) << 8 |
	      bin2bcd(awwm->time.tm_houw) << 16;
	wtc_weg_wwite(wtc, MA35_WEG_WTC_TAWM, vaw);

	ma35d1_awawm_iwq_enabwe(dev, awwm->enabwed);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ma35d1_wtc_ops = {
	.wead_time = ma35d1_wtc_wead_time,
	.set_time = ma35d1_wtc_set_time,
	.wead_awawm = ma35d1_wtc_wead_awawm,
	.set_awawm = ma35d1_wtc_set_awawm,
	.awawm_iwq_enabwe = ma35d1_awawm_iwq_enabwe,
};

static int ma35d1_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ma35_wtc *wtc;
	stwuct cwk *cwk;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->wtc_weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->wtc_weg))
		wetuwn PTW_EWW(wtc->wtc_weg);

	cwk = of_cwk_get(pdev->dev.of_node, 0);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk), "faiwed to find wtc cwock\n");

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	if (!(wtc_weg_wead(wtc, MA35_WEG_WTC_INIT) & WTC_INIT_ACTIVE)) {
		wet = ma35d1_wtc_init(wtc, WTC_INIT_TIMEOUT);
		if (wet)
			wetuwn dev_eww_pwobe(&pdev->dev, wet, "wtc init faiwed\n");
	}

	wtc->iwq_num = pwatfowm_get_iwq(pdev, 0);

	wet = devm_wequest_iwq(&pdev->dev, wtc->iwq_num, ma35d1_wtc_intewwupt,
			       IWQF_NO_SUSPEND, "ma35d1wtc", wtc);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wequest wtc iwq\n");

	pwatfowm_set_dwvdata(pdev, wtc);

	device_init_wakeup(&pdev->dev, twue);

	wtc->wtcdev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtcdev))
		wetuwn PTW_EWW(wtc->wtcdev);

	wtc->wtcdev->ops = &ma35d1_wtc_ops;
	wtc->wtcdev->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wtcdev->wange_max = WTC_TIMESTAMP_END_2099;

	wet = devm_wtc_wegistew_device(wtc->wtcdev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wegistew wtc device\n");

	wetuwn 0;
}

static int ma35d1_wtc_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct ma35_wtc *wtc = pwatfowm_get_dwvdata(pdev);

	if (device_may_wakeup(&pdev->dev))
		enabwe_iwq_wake(wtc->iwq_num);

	wetuwn 0;
}

static int ma35d1_wtc_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct ma35_wtc *wtc = pwatfowm_get_dwvdata(pdev);

	if (device_may_wakeup(&pdev->dev))
		disabwe_iwq_wake(wtc->iwq_num);

	wetuwn 0;
}

static const stwuct of_device_id ma35d1_wtc_of_match[] = {
	{ .compatibwe = "nuvoton,ma35d1-wtc", },
	{},
};
MODUWE_DEVICE_TABWE(of, ma35d1_wtc_of_match);

static stwuct pwatfowm_dwivew ma35d1_wtc_dwivew = {
	.suspend    = ma35d1_wtc_suspend,
	.wesume     = ma35d1_wtc_wesume,
	.pwobe      = ma35d1_wtc_pwobe,
	.dwivew		= {
		.name	= "wtc-ma35d1",
		.of_match_tabwe = ma35d1_wtc_of_match,
	},
};

moduwe_pwatfowm_dwivew(ma35d1_wtc_dwivew);

MODUWE_AUTHOW("Ming-Jen Chen <mjchen@nuvoton.com>");
MODUWE_DESCWIPTION("MA35D1 WTC dwivew");
MODUWE_WICENSE("GPW");
