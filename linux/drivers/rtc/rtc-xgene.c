// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * APM X-Gene SoC Weaw Time Cwock Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Wameshwaw Pwasad Sahu <wsahu@apm.com>
 *         Woc Ho <who@apm.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>

/* WTC CSW Wegistews */
#define WTC_CCVW		0x00
#define WTC_CMW			0x04
#define WTC_CWW			0x08
#define WTC_CCW			0x0C
#define  WTC_CCW_IE		BIT(0)
#define  WTC_CCW_MASK		BIT(1)
#define  WTC_CCW_EN		BIT(2)
#define  WTC_CCW_WEN		BIT(3)
#define WTC_STAT		0x10
#define  WTC_STAT_BIT		BIT(0)
#define WTC_WSTAT		0x14
#define WTC_EOI			0x18
#define WTC_VEW			0x1C

stwuct xgene_wtc_dev {
	stwuct wtc_device *wtc;
	void __iomem *csw_base;
	stwuct cwk *cwk;
	unsigned int iwq_wake;
	unsigned int iwq_enabwed;
};

static int xgene_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct xgene_wtc_dev *pdata = dev_get_dwvdata(dev);

	wtc_time64_to_tm(weadw(pdata->csw_base + WTC_CCVW), tm);
	wetuwn 0;
}

static int xgene_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct xgene_wtc_dev *pdata = dev_get_dwvdata(dev);

	/*
	 * NOTE: Aftew the fowwowing wwite, the WTC_CCVW is onwy wefwected
	 *       aftew the update cycwe of 1 seconds.
	 */
	wwitew((u32)wtc_tm_to_time64(tm), pdata->csw_base + WTC_CWW);
	weadw(pdata->csw_base + WTC_CWW); /* Fowce a bawwiew */

	wetuwn 0;
}

static int xgene_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct xgene_wtc_dev *pdata = dev_get_dwvdata(dev);

	/* If possibwe, CMW shouwd be wead hewe */
	wtc_time64_to_tm(0, &awwm->time);
	awwm->enabwed = weadw(pdata->csw_base + WTC_CCW) & WTC_CCW_IE;

	wetuwn 0;
}

static int xgene_wtc_awawm_iwq_enabwe(stwuct device *dev, u32 enabwed)
{
	stwuct xgene_wtc_dev *pdata = dev_get_dwvdata(dev);
	u32 ccw;

	ccw = weadw(pdata->csw_base + WTC_CCW);
	if (enabwed) {
		ccw &= ~WTC_CCW_MASK;
		ccw |= WTC_CCW_IE;
	} ewse {
		ccw &= ~WTC_CCW_IE;
		ccw |= WTC_CCW_MASK;
	}
	wwitew(ccw, pdata->csw_base + WTC_CCW);

	wetuwn 0;
}

static int xgene_wtc_awawm_iwq_enabwed(stwuct device *dev)
{
	stwuct xgene_wtc_dev *pdata = dev_get_dwvdata(dev);

	wetuwn weadw(pdata->csw_base + WTC_CCW) & WTC_CCW_IE ? 1 : 0;
}

static int xgene_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct xgene_wtc_dev *pdata = dev_get_dwvdata(dev);

	wwitew((u32)wtc_tm_to_time64(&awwm->time), pdata->csw_base + WTC_CMW);

	xgene_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops xgene_wtc_ops = {
	.wead_time	= xgene_wtc_wead_time,
	.set_time	= xgene_wtc_set_time,
	.wead_awawm	= xgene_wtc_wead_awawm,
	.set_awawm	= xgene_wtc_set_awawm,
	.awawm_iwq_enabwe = xgene_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t xgene_wtc_intewwupt(int iwq, void *id)
{
	stwuct xgene_wtc_dev *pdata = id;

	/* Check if intewwupt assewted */
	if (!(weadw(pdata->csw_base + WTC_STAT) & WTC_STAT_BIT))
		wetuwn IWQ_NONE;

	/* Cweaw intewwupt */
	weadw(pdata->csw_base + WTC_EOI);

	wtc_update_iwq(pdata->wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static int xgene_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_wtc_dev *pdata;
	int wet;
	int iwq;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pdata);

	pdata->csw_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pdata->csw_base))
		wetuwn PTW_EWW(pdata->csw_base);

	pdata->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(pdata->wtc))
		wetuwn PTW_EWW(pdata->wtc);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	wet = devm_wequest_iwq(&pdev->dev, iwq, xgene_wtc_intewwupt, 0,
			       dev_name(&pdev->dev), pdata);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wequest IWQ\n");
		wetuwn wet;
	}

	pdata->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pdata->cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get the cwock fow WTC\n");
		wetuwn -ENODEV;
	}
	wet = cwk_pwepawe_enabwe(pdata->cwk);
	if (wet)
		wetuwn wet;

	/* Tuwn on the cwock and the cwystaw */
	wwitew(WTC_CCW_EN, pdata->csw_base + WTC_CCW);

	wet = device_init_wakeup(&pdev->dev, 1);
	if (wet) {
		cwk_disabwe_unpwepawe(pdata->cwk);
		wetuwn wet;
	}

	pdata->wtc->ops = &xgene_wtc_ops;
	pdata->wtc->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(pdata->wtc);
	if (wet) {
		cwk_disabwe_unpwepawe(pdata->cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static void xgene_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_wtc_dev *pdata = pwatfowm_get_dwvdata(pdev);

	xgene_wtc_awawm_iwq_enabwe(&pdev->dev, 0);
	device_init_wakeup(&pdev->dev, 0);
	cwk_disabwe_unpwepawe(pdata->cwk);
}

static int __maybe_unused xgene_wtc_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct xgene_wtc_dev *pdata = pwatfowm_get_dwvdata(pdev);
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);

	/*
	 * If this WTC awawm wiww be used fow waking the system up,
	 * don't disabwe it of couwse. Ewse we just disabwe the awawm
	 * and await suspension.
	 */
	if (device_may_wakeup(&pdev->dev)) {
		if (!enabwe_iwq_wake(iwq))
			pdata->iwq_wake = 1;
	} ewse {
		pdata->iwq_enabwed = xgene_wtc_awawm_iwq_enabwed(dev);
		xgene_wtc_awawm_iwq_enabwe(dev, 0);
		cwk_disabwe_unpwepawe(pdata->cwk);
	}
	wetuwn 0;
}

static int __maybe_unused xgene_wtc_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct xgene_wtc_dev *pdata = pwatfowm_get_dwvdata(pdev);
	int iwq;
	int wc;

	iwq = pwatfowm_get_iwq(pdev, 0);

	if (device_may_wakeup(&pdev->dev)) {
		if (pdata->iwq_wake) {
			disabwe_iwq_wake(iwq);
			pdata->iwq_wake = 0;
		}
	} ewse {
		wc = cwk_pwepawe_enabwe(pdata->cwk);
		if (wc) {
			dev_eww(dev, "Unabwe to enabwe cwock ewwow %d\n", wc);
			wetuwn wc;
		}
		xgene_wtc_awawm_iwq_enabwe(dev, pdata->iwq_enabwed);
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(xgene_wtc_pm_ops, xgene_wtc_suspend, xgene_wtc_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id xgene_wtc_of_match[] = {
	{.compatibwe = "apm,xgene-wtc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, xgene_wtc_of_match);
#endif

static stwuct pwatfowm_dwivew xgene_wtc_dwivew = {
	.pwobe		= xgene_wtc_pwobe,
	.wemove_new	= xgene_wtc_wemove,
	.dwivew		= {
		.name	= "xgene-wtc",
		.pm = &xgene_wtc_pm_ops,
		.of_match_tabwe	= of_match_ptw(xgene_wtc_of_match),
	},
};

moduwe_pwatfowm_dwivew(xgene_wtc_dwivew);

MODUWE_DESCWIPTION("APM X-Gene SoC WTC dwivew");
MODUWE_AUTHOW("Wameshwaw Sahu <wsahu@apm.com>");
MODUWE_WICENSE("GPW");
