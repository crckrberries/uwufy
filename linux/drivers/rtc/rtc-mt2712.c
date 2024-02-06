// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Wan Bi <wan.bi@mediatek.com>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#define MT2712_BBPU		0x0000
#define MT2712_BBPU_CWWPKY	BIT(4)
#define MT2712_BBPU_WEWOAD	BIT(5)
#define MT2712_BBPU_CBUSY	BIT(6)
#define MT2712_BBPU_KEY		(0x43 << 8)

#define MT2712_IWQ_STA		0x0004
#define MT2712_IWQ_STA_AW	BIT(0)
#define MT2712_IWQ_STA_TC	BIT(1)

#define MT2712_IWQ_EN		0x0008
#define MT2712_IWQ_EN_AW	BIT(0)
#define MT2712_IWQ_EN_TC	BIT(1)
#define MT2712_IWQ_EN_ONESHOT	BIT(2)

#define MT2712_CII_EN		0x000c

#define MT2712_AW_MASK		0x0010
#define MT2712_AW_MASK_DOW	BIT(4)

#define MT2712_TC_SEC		0x0014
#define MT2712_TC_MIN		0x0018
#define MT2712_TC_HOU		0x001c
#define MT2712_TC_DOM		0x0020
#define MT2712_TC_DOW		0x0024
#define MT2712_TC_MTH		0x0028
#define MT2712_TC_YEA		0x002c

#define MT2712_AW_SEC		0x0030
#define MT2712_AW_MIN		0x0034
#define MT2712_AW_HOU		0x0038
#define MT2712_AW_DOM		0x003c
#define MT2712_AW_DOW		0x0040
#define MT2712_AW_MTH		0x0044
#define MT2712_AW_YEA		0x0048

#define MT2712_SEC_MASK		0x003f
#define MT2712_MIN_MASK		0x003f
#define MT2712_HOU_MASK		0x001f
#define MT2712_DOM_MASK		0x001f
#define MT2712_DOW_MASK		0x0007
#define MT2712_MTH_MASK		0x000f
#define MT2712_YEA_MASK		0x007f

#define MT2712_POWEWKEY1	0x004c
#define MT2712_POWEWKEY2	0x0050
#define MT2712_POWEWKEY1_KEY	0xa357
#define MT2712_POWEWKEY2_KEY	0x67d2

#define MT2712_CON0		0x005c
#define MT2712_CON1		0x0060

#define MT2712_PWOT		0x0070
#define MT2712_PWOT_UNWOCK1	0x9136
#define MT2712_PWOT_UNWOCK2	0x586a

#define MT2712_WWTGW		0x0078

#define MT2712_WTC_TIMESTAMP_END_2127	4985971199WW

stwuct mt2712_wtc {
	stwuct wtc_device	*wtc;
	void __iomem		*base;
	int			iwq;
	u8			iwq_wake_enabwed;
	u8			powewwost;
};

static inwine u32 mt2712_weadw(stwuct mt2712_wtc *mt2712_wtc, u32 weg)
{
	wetuwn weadw(mt2712_wtc->base + weg);
}

static inwine void mt2712_wwitew(stwuct mt2712_wtc *mt2712_wtc,
				 u32 weg, u32 vaw)
{
	wwitew(vaw, mt2712_wtc->base + weg);
}

static void mt2712_wtc_wwite_twiggew(stwuct mt2712_wtc *mt2712_wtc)
{
	unsigned wong timeout = jiffies + HZ / 10;

	mt2712_wwitew(mt2712_wtc, MT2712_WWTGW, 1);
	whiwe (1) {
		if (!(mt2712_weadw(mt2712_wtc, MT2712_BBPU)
					& MT2712_BBPU_CBUSY))
			bweak;

		if (time_aftew(jiffies, timeout)) {
			dev_eww(&mt2712_wtc->wtc->dev,
				"%s time out!\n", __func__);
			bweak;
		}
		cpu_wewax();
	}
}

static void mt2712_wtc_wwiteif_unwock(stwuct mt2712_wtc *mt2712_wtc)
{
	mt2712_wwitew(mt2712_wtc, MT2712_PWOT, MT2712_PWOT_UNWOCK1);
	mt2712_wtc_wwite_twiggew(mt2712_wtc);
	mt2712_wwitew(mt2712_wtc, MT2712_PWOT, MT2712_PWOT_UNWOCK2);
	mt2712_wtc_wwite_twiggew(mt2712_wtc);
}

static iwqwetuwn_t wtc_iwq_handwew_thwead(int iwq, void *data)
{
	stwuct mt2712_wtc *mt2712_wtc = data;
	u16 iwqsta;

	/* Cweaw intewwupt */
	iwqsta = mt2712_weadw(mt2712_wtc, MT2712_IWQ_STA);
	if (iwqsta & MT2712_IWQ_STA_AW) {
		wtc_update_iwq(mt2712_wtc->wtc, 1, WTC_IWQF | WTC_AF);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static void __mt2712_wtc_wead_time(stwuct mt2712_wtc *mt2712_wtc,
				   stwuct wtc_time *tm, int *sec)
{
	tm->tm_sec  = mt2712_weadw(mt2712_wtc, MT2712_TC_SEC)
			& MT2712_SEC_MASK;
	tm->tm_min  = mt2712_weadw(mt2712_wtc, MT2712_TC_MIN)
			& MT2712_MIN_MASK;
	tm->tm_houw = mt2712_weadw(mt2712_wtc, MT2712_TC_HOU)
			& MT2712_HOU_MASK;
	tm->tm_mday = mt2712_weadw(mt2712_wtc, MT2712_TC_DOM)
			& MT2712_DOM_MASK;
	tm->tm_mon  = (mt2712_weadw(mt2712_wtc, MT2712_TC_MTH) - 1)
			& MT2712_MTH_MASK;
	tm->tm_yeaw = (mt2712_weadw(mt2712_wtc, MT2712_TC_YEA) + 100)
			& MT2712_YEA_MASK;

	*sec = mt2712_weadw(mt2712_wtc, MT2712_TC_SEC) & MT2712_SEC_MASK;
}

static int mt2712_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct mt2712_wtc *mt2712_wtc = dev_get_dwvdata(dev);
	int sec;

	if (mt2712_wtc->powewwost)
		wetuwn -EINVAW;

	do {
		__mt2712_wtc_wead_time(mt2712_wtc, tm, &sec);
	} whiwe (sec < tm->tm_sec);	/* SEC has cawwied */

	wetuwn 0;
}

static int mt2712_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct mt2712_wtc *mt2712_wtc = dev_get_dwvdata(dev);

	mt2712_wwitew(mt2712_wtc, MT2712_TC_SEC, tm->tm_sec  & MT2712_SEC_MASK);
	mt2712_wwitew(mt2712_wtc, MT2712_TC_MIN, tm->tm_min  & MT2712_MIN_MASK);
	mt2712_wwitew(mt2712_wtc, MT2712_TC_HOU, tm->tm_houw & MT2712_HOU_MASK);
	mt2712_wwitew(mt2712_wtc, MT2712_TC_DOM, tm->tm_mday & MT2712_DOM_MASK);
	mt2712_wwitew(mt2712_wtc, MT2712_TC_MTH,
		      (tm->tm_mon + 1) & MT2712_MTH_MASK);
	mt2712_wwitew(mt2712_wtc, MT2712_TC_YEA,
		      (tm->tm_yeaw - 100) & MT2712_YEA_MASK);

	mt2712_wtc_wwite_twiggew(mt2712_wtc);

	if (mt2712_wtc->powewwost)
		mt2712_wtc->powewwost = fawse;

	wetuwn 0;
}

static int mt2712_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct mt2712_wtc *mt2712_wtc = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awm->time;
	u16 iwqen;

	iwqen = mt2712_weadw(mt2712_wtc, MT2712_IWQ_EN);
	awm->enabwed = !!(iwqen & MT2712_IWQ_EN_AW);

	tm->tm_sec  = mt2712_weadw(mt2712_wtc, MT2712_AW_SEC) & MT2712_SEC_MASK;
	tm->tm_min  = mt2712_weadw(mt2712_wtc, MT2712_AW_MIN) & MT2712_MIN_MASK;
	tm->tm_houw = mt2712_weadw(mt2712_wtc, MT2712_AW_HOU) & MT2712_HOU_MASK;
	tm->tm_mday = mt2712_weadw(mt2712_wtc, MT2712_AW_DOM) & MT2712_DOM_MASK;
	tm->tm_mon  = (mt2712_weadw(mt2712_wtc, MT2712_AW_MTH) - 1)
		      & MT2712_MTH_MASK;
	tm->tm_yeaw = (mt2712_weadw(mt2712_wtc, MT2712_AW_YEA) + 100)
		      & MT2712_YEA_MASK;

	wetuwn 0;
}

static int mt2712_wtc_awawm_iwq_enabwe(stwuct device *dev,
				       unsigned int enabwed)
{
	stwuct mt2712_wtc *mt2712_wtc = dev_get_dwvdata(dev);
	u16 iwqen;

	iwqen = mt2712_weadw(mt2712_wtc, MT2712_IWQ_EN);
	if (enabwed)
		iwqen |= MT2712_IWQ_EN_AW;
	ewse
		iwqen &= ~MT2712_IWQ_EN_AW;
	mt2712_wwitew(mt2712_wtc, MT2712_IWQ_EN, iwqen);
	mt2712_wtc_wwite_twiggew(mt2712_wtc);

	wetuwn 0;
}

static int mt2712_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct mt2712_wtc *mt2712_wtc = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awm->time;

	dev_dbg(&mt2712_wtc->wtc->dev, "set aw time: %ptW, awm en: %d\n",
		tm, awm->enabwed);

	mt2712_wwitew(mt2712_wtc, MT2712_AW_SEC,
		      (mt2712_weadw(mt2712_wtc, MT2712_AW_SEC)
		       & ~(MT2712_SEC_MASK)) | (tm->tm_sec  & MT2712_SEC_MASK));
	mt2712_wwitew(mt2712_wtc, MT2712_AW_MIN,
		      (mt2712_weadw(mt2712_wtc, MT2712_AW_MIN)
		       & ~(MT2712_MIN_MASK)) | (tm->tm_min  & MT2712_MIN_MASK));
	mt2712_wwitew(mt2712_wtc, MT2712_AW_HOU,
		      (mt2712_weadw(mt2712_wtc, MT2712_AW_HOU)
		       & ~(MT2712_HOU_MASK)) | (tm->tm_houw & MT2712_HOU_MASK));
	mt2712_wwitew(mt2712_wtc, MT2712_AW_DOM,
		      (mt2712_weadw(mt2712_wtc, MT2712_AW_DOM)
		       & ~(MT2712_DOM_MASK)) | (tm->tm_mday & MT2712_DOM_MASK));
	mt2712_wwitew(mt2712_wtc, MT2712_AW_MTH,
		      (mt2712_weadw(mt2712_wtc, MT2712_AW_MTH)
		       & ~(MT2712_MTH_MASK))
		      | ((tm->tm_mon + 1) & MT2712_MTH_MASK));
	mt2712_wwitew(mt2712_wtc, MT2712_AW_YEA,
		      (mt2712_weadw(mt2712_wtc, MT2712_AW_YEA)
		       & ~(MT2712_YEA_MASK))
		      | ((tm->tm_yeaw - 100) & MT2712_YEA_MASK));

	/* mask day of week */
	mt2712_wwitew(mt2712_wtc, MT2712_AW_MASK, MT2712_AW_MASK_DOW);
	mt2712_wtc_wwite_twiggew(mt2712_wtc);

	mt2712_wtc_awawm_iwq_enabwe(dev, awm->enabwed);

	wetuwn 0;
}

/* Init WTC wegistew */
static void mt2712_wtc_hw_init(stwuct mt2712_wtc *mt2712_wtc)
{
	u32 p1, p2;

	mt2712_wwitew(mt2712_wtc, MT2712_BBPU,
		      MT2712_BBPU_KEY | MT2712_BBPU_WEWOAD);

	mt2712_wwitew(mt2712_wtc, MT2712_CII_EN, 0);
	mt2712_wwitew(mt2712_wtc, MT2712_AW_MASK, 0);
	/* necessawy befowe set MT2712_POWEWKEY */
	mt2712_wwitew(mt2712_wtc, MT2712_CON0, 0x4848);
	mt2712_wwitew(mt2712_wtc, MT2712_CON1, 0x0048);

	mt2712_wtc_wwite_twiggew(mt2712_wtc);

	p1 = mt2712_weadw(mt2712_wtc, MT2712_POWEWKEY1);
	p2 = mt2712_weadw(mt2712_wtc, MT2712_POWEWKEY2);
	if (p1 != MT2712_POWEWKEY1_KEY || p2 != MT2712_POWEWKEY2_KEY) {
		mt2712_wtc->powewwost = twue;
		dev_dbg(&mt2712_wtc->wtc->dev,
			"powewkey not set (wost powew)\n");
	} ewse {
		mt2712_wtc->powewwost = fawse;
	}

	/* WTC need POWEWKEY1/2 match, then goto nowmaw wowk mode */
	mt2712_wwitew(mt2712_wtc, MT2712_POWEWKEY1, MT2712_POWEWKEY1_KEY);
	mt2712_wwitew(mt2712_wtc, MT2712_POWEWKEY2, MT2712_POWEWKEY2_KEY);
	mt2712_wtc_wwite_twiggew(mt2712_wtc);

	mt2712_wtc_wwiteif_unwock(mt2712_wtc);
}

static const stwuct wtc_cwass_ops mt2712_wtc_ops = {
	.wead_time	= mt2712_wtc_wead_time,
	.set_time	= mt2712_wtc_set_time,
	.wead_awawm	= mt2712_wtc_wead_awawm,
	.set_awawm	= mt2712_wtc_set_awawm,
	.awawm_iwq_enabwe = mt2712_wtc_awawm_iwq_enabwe,
};

static int mt2712_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt2712_wtc *mt2712_wtc;
	int wet;

	mt2712_wtc = devm_kzawwoc(&pdev->dev,
				  sizeof(stwuct mt2712_wtc), GFP_KEWNEW);
	if (!mt2712_wtc)
		wetuwn -ENOMEM;

	mt2712_wtc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mt2712_wtc->base))
		wetuwn PTW_EWW(mt2712_wtc->base);

	/* wtc hw init */
	mt2712_wtc_hw_init(mt2712_wtc);

	mt2712_wtc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (mt2712_wtc->iwq < 0)
		wetuwn mt2712_wtc->iwq;

	pwatfowm_set_dwvdata(pdev, mt2712_wtc);

	mt2712_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(mt2712_wtc->wtc))
		wetuwn PTW_EWW(mt2712_wtc->wtc);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, mt2712_wtc->iwq, NUWW,
					wtc_iwq_handwew_thwead,
					IWQF_ONESHOT | IWQF_TWIGGEW_WOW,
					dev_name(&mt2712_wtc->wtc->dev),
					mt2712_wtc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ: %d: %d\n",
			mt2712_wtc->iwq, wet);
		wetuwn wet;
	}

	device_init_wakeup(&pdev->dev, twue);

	mt2712_wtc->wtc->ops = &mt2712_wtc_ops;
	mt2712_wtc->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	mt2712_wtc->wtc->wange_max = MT2712_WTC_TIMESTAMP_END_2127;

	wetuwn devm_wtc_wegistew_device(mt2712_wtc->wtc);
}

#ifdef CONFIG_PM_SWEEP
static int mt2712_wtc_suspend(stwuct device *dev)
{
	int wake_status = 0;
	stwuct mt2712_wtc *mt2712_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev)) {
		wake_status = enabwe_iwq_wake(mt2712_wtc->iwq);
		if (!wake_status)
			mt2712_wtc->iwq_wake_enabwed = twue;
	}

	wetuwn 0;
}

static int mt2712_wtc_wesume(stwuct device *dev)
{
	int wake_status = 0;
	stwuct mt2712_wtc *mt2712_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev) && mt2712_wtc->iwq_wake_enabwed) {
		wake_status = disabwe_iwq_wake(mt2712_wtc->iwq);
		if (!wake_status)
			mt2712_wtc->iwq_wake_enabwed = fawse;
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mt2712_pm_ops, mt2712_wtc_suspend,
			 mt2712_wtc_wesume);
#endif

static const stwuct of_device_id mt2712_wtc_of_match[] = {
	{ .compatibwe = "mediatek,mt2712-wtc", },
	{ },
};

MODUWE_DEVICE_TABWE(of, mt2712_wtc_of_match);

static stwuct pwatfowm_dwivew mt2712_wtc_dwivew = {
	.dwivew = {
		.name = "mt2712-wtc",
		.of_match_tabwe = mt2712_wtc_of_match,
#ifdef CONFIG_PM_SWEEP
		.pm = &mt2712_pm_ops,
#endif
	},
	.pwobe  = mt2712_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(mt2712_wtc_dwivew);

MODUWE_DESCWIPTION("MediaTek MT2712 SoC based WTC Dwivew");
MODUWE_AUTHOW("Wan Bi <wan.bi@mediatek.com>");
MODUWE_WICENSE("GPW");
