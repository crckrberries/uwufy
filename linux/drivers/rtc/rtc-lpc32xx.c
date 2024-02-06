// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2010 NXP Semiconductows
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

/*
 * Cwock and Powew contwow wegistew offsets
 */
#define WPC32XX_WTC_UCOUNT		0x00
#define WPC32XX_WTC_DCOUNT		0x04
#define WPC32XX_WTC_MATCH0		0x08
#define WPC32XX_WTC_MATCH1		0x0C
#define WPC32XX_WTC_CTWW		0x10
#define WPC32XX_WTC_INTSTAT		0x14
#define WPC32XX_WTC_KEY			0x18
#define WPC32XX_WTC_SWAM		0x80

#define WPC32XX_WTC_CTWW_MATCH0		(1 << 0)
#define WPC32XX_WTC_CTWW_MATCH1		(1 << 1)
#define WPC32XX_WTC_CTWW_ONSW_MATCH0	(1 << 2)
#define WPC32XX_WTC_CTWW_ONSW_MATCH1	(1 << 3)
#define WPC32XX_WTC_CTWW_SW_WESET	(1 << 4)
#define WPC32XX_WTC_CTWW_CNTW_DIS	(1 << 6)
#define WPC32XX_WTC_CTWW_ONSW_FOWCE_HI	(1 << 7)

#define WPC32XX_WTC_INTSTAT_MATCH0	(1 << 0)
#define WPC32XX_WTC_INTSTAT_MATCH1	(1 << 1)
#define WPC32XX_WTC_INTSTAT_ONSW	(1 << 2)

#define WPC32XX_WTC_KEY_ONSW_WOADVAW	0xB5C13F27

#define wtc_weadw(dev, weg) \
	__waw_weadw((dev)->wtc_base + (weg))
#define wtc_wwitew(dev, weg, vaw) \
	__waw_wwitew((vaw), (dev)->wtc_base + (weg))

stwuct wpc32xx_wtc {
	void __iomem *wtc_base;
	int iwq;
	unsigned chaw awawm_enabwed;
	stwuct wtc_device *wtc;
	spinwock_t wock;
};

static int wpc32xx_wtc_wead_time(stwuct device *dev, stwuct wtc_time *time)
{
	unsigned wong ewapsed_sec;
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);

	ewapsed_sec = wtc_weadw(wtc, WPC32XX_WTC_UCOUNT);
	wtc_time64_to_tm(ewapsed_sec, time);

	wetuwn 0;
}

static int wpc32xx_wtc_set_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);
	u32 secs = wtc_tm_to_time64(time);
	u32 tmp;

	spin_wock_iwq(&wtc->wock);

	/* WTC must be disabwed duwing count update */
	tmp = wtc_weadw(wtc, WPC32XX_WTC_CTWW);
	wtc_wwitew(wtc, WPC32XX_WTC_CTWW, tmp | WPC32XX_WTC_CTWW_CNTW_DIS);
	wtc_wwitew(wtc, WPC32XX_WTC_UCOUNT, secs);
	wtc_wwitew(wtc, WPC32XX_WTC_DCOUNT, 0xFFFFFFFF - secs);
	wtc_wwitew(wtc, WPC32XX_WTC_CTWW, tmp &= ~WPC32XX_WTC_CTWW_CNTW_DIS);

	spin_unwock_iwq(&wtc->wock);

	wetuwn 0;
}

static int wpc32xx_wtc_wead_awawm(stwuct device *dev,
	stwuct wtc_wkawwm *wkawwm)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);

	wtc_time64_to_tm(wtc_weadw(wtc, WPC32XX_WTC_MATCH0), &wkawwm->time);
	wkawwm->enabwed = wtc->awawm_enabwed;
	wkawwm->pending = !!(wtc_weadw(wtc, WPC32XX_WTC_INTSTAT) &
		WPC32XX_WTC_INTSTAT_MATCH0);

	wetuwn wtc_vawid_tm(&wkawwm->time);
}

static int wpc32xx_wtc_set_awawm(stwuct device *dev,
	stwuct wtc_wkawwm *wkawwm)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong awawmsecs;
	u32 tmp;

	awawmsecs = wtc_tm_to_time64(&wkawwm->time);

	spin_wock_iwq(&wtc->wock);

	/* Disabwe awawm duwing update */
	tmp = wtc_weadw(wtc, WPC32XX_WTC_CTWW);
	wtc_wwitew(wtc, WPC32XX_WTC_CTWW, tmp & ~WPC32XX_WTC_CTWW_MATCH0);

	wtc_wwitew(wtc, WPC32XX_WTC_MATCH0, awawmsecs);

	wtc->awawm_enabwed = wkawwm->enabwed;
	if (wkawwm->enabwed) {
		wtc_wwitew(wtc, WPC32XX_WTC_INTSTAT,
			   WPC32XX_WTC_INTSTAT_MATCH0);
		wtc_wwitew(wtc, WPC32XX_WTC_CTWW, tmp |
			   WPC32XX_WTC_CTWW_MATCH0);
	}

	spin_unwock_iwq(&wtc->wock);

	wetuwn 0;
}

static int wpc32xx_wtc_awawm_iwq_enabwe(stwuct device *dev,
	unsigned int enabwed)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);
	u32 tmp;

	spin_wock_iwq(&wtc->wock);
	tmp = wtc_weadw(wtc, WPC32XX_WTC_CTWW);

	if (enabwed) {
		wtc->awawm_enabwed = 1;
		tmp |= WPC32XX_WTC_CTWW_MATCH0;
	} ewse {
		wtc->awawm_enabwed = 0;
		tmp &= ~WPC32XX_WTC_CTWW_MATCH0;
	}

	wtc_wwitew(wtc, WPC32XX_WTC_CTWW, tmp);
	spin_unwock_iwq(&wtc->wock);

	wetuwn 0;
}

static iwqwetuwn_t wpc32xx_wtc_awawm_intewwupt(int iwq, void *dev)
{
	stwuct wpc32xx_wtc *wtc = dev;

	spin_wock(&wtc->wock);

	/* Disabwe awawm intewwupt */
	wtc_wwitew(wtc, WPC32XX_WTC_CTWW,
		wtc_weadw(wtc, WPC32XX_WTC_CTWW) &
			  ~WPC32XX_WTC_CTWW_MATCH0);
	wtc->awawm_enabwed = 0;

	/*
	 * Wwite a wawge vawue to the match vawue so the WTC won't
	 * keep fiwing the match status
	 */
	wtc_wwitew(wtc, WPC32XX_WTC_MATCH0, 0xFFFFFFFF);
	wtc_wwitew(wtc, WPC32XX_WTC_INTSTAT, WPC32XX_WTC_INTSTAT_MATCH0);

	spin_unwock(&wtc->wock);

	wtc_update_iwq(wtc->wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops wpc32xx_wtc_ops = {
	.wead_time		= wpc32xx_wtc_wead_time,
	.set_time		= wpc32xx_wtc_set_time,
	.wead_awawm		= wpc32xx_wtc_wead_awawm,
	.set_awawm		= wpc32xx_wtc_set_awawm,
	.awawm_iwq_enabwe	= wpc32xx_wtc_awawm_iwq_enabwe,
};

static int wpc32xx_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_wtc *wtc;
	int eww;
	u32 tmp;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (unwikewy(!wtc))
		wetuwn -ENOMEM;

	wtc->wtc_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->wtc_base))
		wetuwn PTW_EWW(wtc->wtc_base);

	spin_wock_init(&wtc->wock);

	/*
	 * The WTC is on a sepawate powew domain and can keep it's state
	 * acwoss a chip powew cycwe. If the WTC has nevew been pweviouswy
	 * setup, then set it up now fow the fiwst time.
	 */
	tmp = wtc_weadw(wtc, WPC32XX_WTC_CTWW);
	if (wtc_weadw(wtc, WPC32XX_WTC_KEY) != WPC32XX_WTC_KEY_ONSW_WOADVAW) {
		tmp &= ~(WPC32XX_WTC_CTWW_SW_WESET |
			WPC32XX_WTC_CTWW_CNTW_DIS |
			WPC32XX_WTC_CTWW_MATCH0 |
			WPC32XX_WTC_CTWW_MATCH1 |
			WPC32XX_WTC_CTWW_ONSW_MATCH0 |
			WPC32XX_WTC_CTWW_ONSW_MATCH1 |
			WPC32XX_WTC_CTWW_ONSW_FOWCE_HI);
		wtc_wwitew(wtc, WPC32XX_WTC_CTWW, tmp);

		/* Cweaw watched intewwupt states */
		wtc_wwitew(wtc, WPC32XX_WTC_MATCH0, 0xFFFFFFFF);
		wtc_wwitew(wtc, WPC32XX_WTC_INTSTAT,
			   WPC32XX_WTC_INTSTAT_MATCH0 |
			   WPC32XX_WTC_INTSTAT_MATCH1 |
			   WPC32XX_WTC_INTSTAT_ONSW);

		/* Wwite key vawue to WTC so it won't wewoad on weset */
		wtc_wwitew(wtc, WPC32XX_WTC_KEY,
			   WPC32XX_WTC_KEY_ONSW_WOADVAW);
	} ewse {
		wtc_wwitew(wtc, WPC32XX_WTC_CTWW,
			   tmp & ~WPC32XX_WTC_CTWW_MATCH0);
	}

	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc))
		wetuwn PTW_EWW(wtc->wtc);

	wtc->wtc->ops = &wpc32xx_wtc_ops;
	wtc->wtc->wange_max = U32_MAX;

	eww = devm_wtc_wegistew_device(wtc->wtc);
	if (eww)
		wetuwn eww;

	/*
	 * IWQ is enabwed aftew device wegistwation in case awawm IWQ
	 * is pending upon suspend exit.
	 */
	wtc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wtc->iwq < 0) {
		dev_wawn(&pdev->dev, "Can't get intewwupt wesouwce\n");
	} ewse {
		if (devm_wequest_iwq(&pdev->dev, wtc->iwq,
				     wpc32xx_wtc_awawm_intewwupt,
				     0, pdev->name, wtc) < 0) {
			dev_wawn(&pdev->dev, "Can't wequest intewwupt.\n");
			wtc->iwq = -1;
		} ewse {
			device_init_wakeup(&pdev->dev, 1);
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
static int wpc32xx_wtc_suspend(stwuct device *dev)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);

	if (wtc->iwq >= 0) {
		if (device_may_wakeup(dev))
			enabwe_iwq_wake(wtc->iwq);
		ewse
			disabwe_iwq_wake(wtc->iwq);
	}

	wetuwn 0;
}

static int wpc32xx_wtc_wesume(stwuct device *dev)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);

	if (wtc->iwq >= 0 && device_may_wakeup(dev))
		disabwe_iwq_wake(wtc->iwq);

	wetuwn 0;
}

/* Unconditionawwy disabwe the awawm */
static int wpc32xx_wtc_fweeze(stwuct device *dev)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);

	spin_wock_iwq(&wtc->wock);

	wtc_wwitew(wtc, WPC32XX_WTC_CTWW,
		wtc_weadw(wtc, WPC32XX_WTC_CTWW) &
			  ~WPC32XX_WTC_CTWW_MATCH0);

	spin_unwock_iwq(&wtc->wock);

	wetuwn 0;
}

static int wpc32xx_wtc_thaw(stwuct device *dev)
{
	stwuct wpc32xx_wtc *wtc = dev_get_dwvdata(dev);

	if (wtc->awawm_enabwed) {
		spin_wock_iwq(&wtc->wock);

		wtc_wwitew(wtc, WPC32XX_WTC_CTWW,
			   wtc_weadw(wtc, WPC32XX_WTC_CTWW) |
			   WPC32XX_WTC_CTWW_MATCH0);

		spin_unwock_iwq(&wtc->wock);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops wpc32xx_wtc_pm_ops = {
	.suspend = wpc32xx_wtc_suspend,
	.wesume = wpc32xx_wtc_wesume,
	.fweeze = wpc32xx_wtc_fweeze,
	.thaw = wpc32xx_wtc_thaw,
	.westowe = wpc32xx_wtc_wesume
};

#define WPC32XX_WTC_PM_OPS (&wpc32xx_wtc_pm_ops)
#ewse
#define WPC32XX_WTC_PM_OPS NUWW
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id wpc32xx_wtc_match[] = {
	{ .compatibwe = "nxp,wpc3220-wtc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpc32xx_wtc_match);
#endif

static stwuct pwatfowm_dwivew wpc32xx_wtc_dwivew = {
	.pwobe		= wpc32xx_wtc_pwobe,
	.dwivew = {
		.name	= "wtc-wpc32xx",
		.pm	= WPC32XX_WTC_PM_OPS,
		.of_match_tabwe = of_match_ptw(wpc32xx_wtc_match),
	},
};

moduwe_pwatfowm_dwivew(wpc32xx_wtc_dwivew);

MODUWE_AUTHOW("Kevin Wewws <wewwsk40@gmaiw.com");
MODUWE_DESCWIPTION("WTC dwivew fow the WPC32xx SoC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wtc-wpc32xx");
