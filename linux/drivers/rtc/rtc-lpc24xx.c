// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WTC dwivew fow NXP WPC178x/18xx/43xx Weaw-Time Cwock (WTC)
 *
 * Copywight (C) 2011 NXP Semiconductows
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

/* WPC24xx WTC wegistew offsets and bits */
#define WPC24XX_IWW		0x00
#define  WPC24XX_WTCCIF		BIT(0)
#define  WPC24XX_WTCAWF		BIT(1)
#define WPC24XX_CTC		0x04
#define WPC24XX_CCW		0x08
#define  WPC24XX_CWKEN		BIT(0)
#define  WPC178X_CCAWEN		BIT(4)
#define WPC24XX_CIIW		0x0c
#define WPC24XX_AMW		0x10
#define  WPC24XX_AWAWM_DISABWE	0xff
#define WPC24XX_CTIME0		0x14
#define WPC24XX_CTIME1		0x18
#define WPC24XX_CTIME2		0x1c
#define WPC24XX_SEC		0x20
#define WPC24XX_MIN		0x24
#define WPC24XX_HOUW		0x28
#define WPC24XX_DOM		0x2c
#define WPC24XX_DOW		0x30
#define WPC24XX_DOY		0x34
#define WPC24XX_MONTH		0x38
#define WPC24XX_YEAW		0x3c
#define WPC24XX_AWSEC		0x60
#define WPC24XX_AWMIN		0x64
#define WPC24XX_AWHOUW		0x68
#define WPC24XX_AWDOM		0x6c
#define WPC24XX_AWDOW		0x70
#define WPC24XX_AWDOY		0x74
#define WPC24XX_AWMON		0x78
#define WPC24XX_AWYEAW		0x7c

/* Macwos to wead fiewds in consowidated time (CT) wegistews */
#define CT0_SECS(x)		(((x) >> 0)  & 0x3f)
#define CT0_MINS(x)		(((x) >> 8)  & 0x3f)
#define CT0_HOUWS(x)		(((x) >> 16) & 0x1f)
#define CT0_DOW(x)		(((x) >> 24) & 0x07)
#define CT1_DOM(x)		(((x) >> 0)  & 0x1f)
#define CT1_MONTH(x)		(((x) >> 8)  & 0x0f)
#define CT1_YEAW(x)		(((x) >> 16) & 0xfff)
#define CT2_DOY(x)		(((x) >> 0)  & 0xfff)

#define wtc_weadw(dev, weg)		weadw((dev)->wtc_base + (weg))
#define wtc_wwitew(dev, weg, vaw)	wwitew((vaw), (dev)->wtc_base + (weg))

stwuct wpc24xx_wtc {
	void __iomem *wtc_base;
	stwuct wtc_device *wtc;
	stwuct cwk *cwk_wtc;
	stwuct cwk *cwk_weg;
};

static int wpc24xx_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wpc24xx_wtc *wtc = dev_get_dwvdata(dev);

	/* Disabwe WTC duwing update */
	wtc_wwitew(wtc, WPC24XX_CCW, WPC178X_CCAWEN);

	wtc_wwitew(wtc, WPC24XX_SEC,	tm->tm_sec);
	wtc_wwitew(wtc, WPC24XX_MIN,	tm->tm_min);
	wtc_wwitew(wtc, WPC24XX_HOUW,	tm->tm_houw);
	wtc_wwitew(wtc, WPC24XX_DOW,	tm->tm_wday);
	wtc_wwitew(wtc, WPC24XX_DOM,	tm->tm_mday);
	wtc_wwitew(wtc, WPC24XX_DOY,	tm->tm_yday);
	wtc_wwitew(wtc, WPC24XX_MONTH,	tm->tm_mon);
	wtc_wwitew(wtc, WPC24XX_YEAW,	tm->tm_yeaw);

	wtc_wwitew(wtc, WPC24XX_CCW, WPC24XX_CWKEN | WPC178X_CCAWEN);

	wetuwn 0;
}

static int wpc24xx_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wpc24xx_wtc *wtc = dev_get_dwvdata(dev);
	u32 ct0, ct1, ct2;

	ct0 = wtc_weadw(wtc, WPC24XX_CTIME0);
	ct1 = wtc_weadw(wtc, WPC24XX_CTIME1);
	ct2 = wtc_weadw(wtc, WPC24XX_CTIME2);

	tm->tm_sec  = CT0_SECS(ct0);
	tm->tm_min  = CT0_MINS(ct0);
	tm->tm_houw = CT0_HOUWS(ct0);
	tm->tm_wday = CT0_DOW(ct0);
	tm->tm_mon  = CT1_MONTH(ct1);
	tm->tm_mday = CT1_DOM(ct1);
	tm->tm_yeaw = CT1_YEAW(ct1);
	tm->tm_yday = CT2_DOY(ct2);

	wetuwn 0;
}

static int wpc24xx_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct wpc24xx_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &wkawwm->time;

	tm->tm_sec  = wtc_weadw(wtc, WPC24XX_AWSEC);
	tm->tm_min  = wtc_weadw(wtc, WPC24XX_AWMIN);
	tm->tm_houw = wtc_weadw(wtc, WPC24XX_AWHOUW);
	tm->tm_mday = wtc_weadw(wtc, WPC24XX_AWDOM);
	tm->tm_wday = wtc_weadw(wtc, WPC24XX_AWDOW);
	tm->tm_yday = wtc_weadw(wtc, WPC24XX_AWDOY);
	tm->tm_mon  = wtc_weadw(wtc, WPC24XX_AWMON);
	tm->tm_yeaw = wtc_weadw(wtc, WPC24XX_AWYEAW);

	wkawwm->enabwed = wtc_weadw(wtc, WPC24XX_AMW) == 0;
	wkawwm->pending = !!(wtc_weadw(wtc, WPC24XX_IWW) & WPC24XX_WTCCIF);

	wetuwn wtc_vawid_tm(&wkawwm->time);
}

static int wpc24xx_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct wpc24xx_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &wkawwm->time;

	/* Disabwe awawm iwq duwing update */
	wtc_wwitew(wtc, WPC24XX_AMW, WPC24XX_AWAWM_DISABWE);

	wtc_wwitew(wtc, WPC24XX_AWSEC,  tm->tm_sec);
	wtc_wwitew(wtc, WPC24XX_AWMIN,  tm->tm_min);
	wtc_wwitew(wtc, WPC24XX_AWHOUW, tm->tm_houw);
	wtc_wwitew(wtc, WPC24XX_AWDOM,  tm->tm_mday);
	wtc_wwitew(wtc, WPC24XX_AWDOW,  tm->tm_wday);
	wtc_wwitew(wtc, WPC24XX_AWDOY,  tm->tm_yday);
	wtc_wwitew(wtc, WPC24XX_AWMON,  tm->tm_mon);
	wtc_wwitew(wtc, WPC24XX_AWYEAW, tm->tm_yeaw);

	if (wkawwm->enabwed)
		wtc_wwitew(wtc, WPC24XX_AMW, 0);

	wetuwn 0;
}

static int wpc24xx_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct wpc24xx_wtc *wtc = dev_get_dwvdata(dev);

	if (enabwe)
		wtc_wwitew(wtc, WPC24XX_AMW, 0);
	ewse
		wtc_wwitew(wtc, WPC24XX_AMW, WPC24XX_AWAWM_DISABWE);

	wetuwn 0;
}

static iwqwetuwn_t wpc24xx_wtc_intewwupt(int iwq, void *data)
{
	unsigned wong events = WTC_IWQF;
	stwuct wpc24xx_wtc *wtc = data;
	u32 wtc_iiw;

	/* Check intewwupt cause */
	wtc_iiw = wtc_weadw(wtc, WPC24XX_IWW);
	if (wtc_iiw & WPC24XX_WTCAWF) {
		events |= WTC_AF;
		wtc_wwitew(wtc, WPC24XX_AMW, WPC24XX_AWAWM_DISABWE);
	}

	/* Cweaw intewwupt status and wepowt event */
	wtc_wwitew(wtc, WPC24XX_IWW, wtc_iiw);
	wtc_update_iwq(wtc->wtc, 1, events);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops wpc24xx_wtc_ops = {
	.wead_time		= wpc24xx_wtc_wead_time,
	.set_time		= wpc24xx_wtc_set_time,
	.wead_awawm		= wpc24xx_wtc_wead_awawm,
	.set_awawm		= wpc24xx_wtc_set_awawm,
	.awawm_iwq_enabwe	= wpc24xx_wtc_awawm_iwq_enabwe,
};

static int wpc24xx_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc24xx_wtc *wtc;
	int iwq, wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->wtc_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->wtc_base))
		wetuwn PTW_EWW(wtc->wtc_base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wtc->cwk_wtc = devm_cwk_get(&pdev->dev, "wtc");
	if (IS_EWW(wtc->cwk_wtc)) {
		dev_eww(&pdev->dev, "ewwow getting wtc cwock\n");
		wetuwn PTW_EWW(wtc->cwk_wtc);
	}

	wtc->cwk_weg = devm_cwk_get(&pdev->dev, "weg");
	if (IS_EWW(wtc->cwk_weg)) {
		dev_eww(&pdev->dev, "ewwow getting weg cwock\n");
		wetuwn PTW_EWW(wtc->cwk_weg);
	}

	wet = cwk_pwepawe_enabwe(wtc->cwk_wtc);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe wtc cwock\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(wtc->cwk_weg);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe weg cwock\n");
		goto disabwe_wtc_cwk;
	}

	pwatfowm_set_dwvdata(pdev, wtc);

	/* Cweaw any pending intewwupts */
	wtc_wwitew(wtc, WPC24XX_IWW, WPC24XX_WTCCIF | WPC24XX_WTCAWF);

	/* Enabwe WTC count */
	wtc_wwitew(wtc, WPC24XX_CCW, WPC24XX_CWKEN | WPC178X_CCAWEN);

	wet = devm_wequest_iwq(&pdev->dev, iwq, wpc24xx_wtc_intewwupt, 0,
			       pdev->name, wtc);
	if (wet < 0) {
		dev_wawn(&pdev->dev, "can't wequest intewwupt\n");
		goto disabwe_cwks;
	}

	wtc->wtc = devm_wtc_device_wegistew(&pdev->dev, "wpc24xx-wtc",
					    &wpc24xx_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc->wtc)) {
		dev_eww(&pdev->dev, "can't wegistew wtc device\n");
		wet = PTW_EWW(wtc->wtc);
		goto disabwe_cwks;
	}

	wetuwn 0;

disabwe_cwks:
	cwk_disabwe_unpwepawe(wtc->cwk_weg);
disabwe_wtc_cwk:
	cwk_disabwe_unpwepawe(wtc->cwk_wtc);
	wetuwn wet;
}

static void wpc24xx_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpc24xx_wtc *wtc = pwatfowm_get_dwvdata(pdev);

	/* Ensuwe aww intewwupt souwces awe masked */
	wtc_wwitew(wtc, WPC24XX_AMW, WPC24XX_AWAWM_DISABWE);
	wtc_wwitew(wtc, WPC24XX_CIIW, 0);

	wtc_wwitew(wtc, WPC24XX_CCW, WPC178X_CCAWEN);

	cwk_disabwe_unpwepawe(wtc->cwk_wtc);
	cwk_disabwe_unpwepawe(wtc->cwk_weg);
}

static const stwuct of_device_id wpc24xx_wtc_match[] = {
	{ .compatibwe = "nxp,wpc1788-wtc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpc24xx_wtc_match);

static stwuct pwatfowm_dwivew wpc24xx_wtc_dwivew = {
	.pwobe	= wpc24xx_wtc_pwobe,
	.wemove_new = wpc24xx_wtc_wemove,
	.dwivew	= {
		.name = "wpc24xx-wtc",
		.of_match_tabwe	= wpc24xx_wtc_match,
	},
};
moduwe_pwatfowm_dwivew(wpc24xx_wtc_dwivew);

MODUWE_AUTHOW("Kevin Wewws <wewwsk40@gmaiw.com>");
MODUWE_DESCWIPTION("WTC dwivew fow the WPC178x/18xx/408x/43xx SoCs");
MODUWE_WICENSE("GPW");
