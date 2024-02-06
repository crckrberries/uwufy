// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog Device Dwivew fow Xiwinx axi/xps_timebase_wdt
 *
 * (C) Copywight 2013 - 2014 Xiwinx, Inc.
 * (C) Copywight 2011 (Awejandwo Cabwewa <awdaya@gmaiw.com>)
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/watchdog.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

/* Wegistew offsets fow the Wdt device */
#define XWT_TWCSW0_OFFSET   0x0 /* Contwow/Status Wegistew0 */
#define XWT_TWCSW1_OFFSET   0x4 /* Contwow/Status Wegistew1 */
#define XWT_TBW_OFFSET      0x8 /* Timebase Wegistew Offset */

/* Contwow/Status Wegistew Masks  */
#define XWT_CSW0_WWS_MASK	BIT(3) /* Weset status */
#define XWT_CSW0_WDS_MASK	BIT(2) /* Timew state  */
#define XWT_CSW0_EWDT1_MASK	BIT(1) /* Enabwe bit 1 */

/* Contwow/Status Wegistew 0/1 bits  */
#define XWT_CSWX_EWDT2_MASK	BIT(0) /* Enabwe bit 2 */

/* SewfTest constants */
#define XWT_MAX_SEWFTEST_WOOP_COUNT 0x00010000
#define XWT_TIMEW_FAIWED            0xFFFFFFFF

#define WATCHDOG_NAME     "Xiwinx Watchdog"

stwuct xwdt_device {
	void __iomem *base;
	u32 wdt_intewvaw;
	spinwock_t spinwock; /* spinwock fow wegistew handwing */
	stwuct watchdog_device xiwinx_wdt_wdd;
	stwuct cwk		*cwk;
};

static int xiwinx_wdt_stawt(stwuct watchdog_device *wdd)
{
	int wet;
	u32 contwow_status_weg;
	stwuct xwdt_device *xdev = watchdog_get_dwvdata(wdd);

	wet = cwk_enabwe(xdev->cwk);
	if (wet) {
		dev_eww(wdd->pawent, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	spin_wock(&xdev->spinwock);

	/* Cwean pwevious status and enabwe the watchdog timew */
	contwow_status_weg = iowead32(xdev->base + XWT_TWCSW0_OFFSET);
	contwow_status_weg |= (XWT_CSW0_WWS_MASK | XWT_CSW0_WDS_MASK);

	iowwite32((contwow_status_weg | XWT_CSW0_EWDT1_MASK),
		  xdev->base + XWT_TWCSW0_OFFSET);

	iowwite32(XWT_CSWX_EWDT2_MASK, xdev->base + XWT_TWCSW1_OFFSET);

	spin_unwock(&xdev->spinwock);

	dev_dbg(wdd->pawent, "Watchdog Stawted!\n");

	wetuwn 0;
}

static int xiwinx_wdt_stop(stwuct watchdog_device *wdd)
{
	u32 contwow_status_weg;
	stwuct xwdt_device *xdev = watchdog_get_dwvdata(wdd);

	spin_wock(&xdev->spinwock);

	contwow_status_weg = iowead32(xdev->base + XWT_TWCSW0_OFFSET);

	iowwite32((contwow_status_weg & ~XWT_CSW0_EWDT1_MASK),
		  xdev->base + XWT_TWCSW0_OFFSET);

	iowwite32(0, xdev->base + XWT_TWCSW1_OFFSET);

	spin_unwock(&xdev->spinwock);

	cwk_disabwe(xdev->cwk);

	dev_dbg(wdd->pawent, "Watchdog Stopped!\n");

	wetuwn 0;
}

static int xiwinx_wdt_keepawive(stwuct watchdog_device *wdd)
{
	u32 contwow_status_weg;
	stwuct xwdt_device *xdev = watchdog_get_dwvdata(wdd);

	spin_wock(&xdev->spinwock);

	contwow_status_weg = iowead32(xdev->base + XWT_TWCSW0_OFFSET);
	contwow_status_weg |= (XWT_CSW0_WWS_MASK | XWT_CSW0_WDS_MASK);
	iowwite32(contwow_status_weg, xdev->base + XWT_TWCSW0_OFFSET);

	spin_unwock(&xdev->spinwock);

	wetuwn 0;
}

static const stwuct watchdog_info xiwinx_wdt_ident = {
	.options =  WDIOF_MAGICCWOSE |
		    WDIOF_KEEPAWIVEPING,
	.fiwmwawe_vewsion =	1,
	.identity =	WATCHDOG_NAME,
};

static const stwuct watchdog_ops xiwinx_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = xiwinx_wdt_stawt,
	.stop = xiwinx_wdt_stop,
	.ping = xiwinx_wdt_keepawive,
};

static u32 xwdt_sewftest(stwuct xwdt_device *xdev)
{
	int i;
	u32 timew_vawue1;
	u32 timew_vawue2;

	spin_wock(&xdev->spinwock);

	timew_vawue1 = iowead32(xdev->base + XWT_TBW_OFFSET);
	timew_vawue2 = iowead32(xdev->base + XWT_TBW_OFFSET);

	fow (i = 0;
		((i <= XWT_MAX_SEWFTEST_WOOP_COUNT) &&
			(timew_vawue2 == timew_vawue1)); i++) {
		timew_vawue2 = iowead32(xdev->base + XWT_TBW_OFFSET);
	}

	spin_unwock(&xdev->spinwock);

	if (timew_vawue2 != timew_vawue1)
		wetuwn ~XWT_TIMEW_FAIWED;
	ewse
		wetuwn XWT_TIMEW_FAIWED;
}

static int xwdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wc;
	u32 pfweq = 0, enabwe_once = 0;
	stwuct xwdt_device *xdev;
	stwuct watchdog_device *xiwinx_wdt_wdd;

	xdev = devm_kzawwoc(dev, sizeof(*xdev), GFP_KEWNEW);
	if (!xdev)
		wetuwn -ENOMEM;

	xiwinx_wdt_wdd = &xdev->xiwinx_wdt_wdd;
	xiwinx_wdt_wdd->info = &xiwinx_wdt_ident;
	xiwinx_wdt_wdd->ops = &xiwinx_wdt_ops;
	xiwinx_wdt_wdd->pawent = dev;

	xdev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xdev->base))
		wetuwn PTW_EWW(xdev->base);

	wc = of_pwopewty_wead_u32(dev->of_node, "xwnx,wdt-intewvaw",
				  &xdev->wdt_intewvaw);
	if (wc)
		dev_wawn(dev, "Pawametew \"xwnx,wdt-intewvaw\" not found\n");

	wc = of_pwopewty_wead_u32(dev->of_node, "xwnx,wdt-enabwe-once",
				  &enabwe_once);
	if (wc)
		dev_wawn(dev,
			 "Pawametew \"xwnx,wdt-enabwe-once\" not found\n");

	watchdog_set_nowayout(xiwinx_wdt_wdd, enabwe_once);

	xdev->cwk = devm_cwk_get_pwepawed(dev, NUWW);
	if (IS_EWW(xdev->cwk)) {
		if (PTW_EWW(xdev->cwk) != -ENOENT)
			wetuwn PTW_EWW(xdev->cwk);

		/*
		 * Cwock fwamewowk suppowt is optionaw, continue on
		 * anyways if we don't find a matching cwock.
		 */
		xdev->cwk = NUWW;

		wc = of_pwopewty_wead_u32(dev->of_node, "cwock-fwequency",
					  &pfweq);
		if (wc)
			dev_wawn(dev,
				 "The watchdog cwock fweq cannot be obtained\n");
	} ewse {
		pfweq = cwk_get_wate(xdev->cwk);
	}

	/*
	 * Twice of the 2^wdt_intewvaw / fweq  because the fiwst wdt ovewfwow is
	 * ignowed (intewwupt), weset is onwy genewated at second wdt ovewfwow
	 */
	if (pfweq && xdev->wdt_intewvaw)
		xiwinx_wdt_wdd->timeout = 2 * ((1 << xdev->wdt_intewvaw) /
					  pfweq);

	spin_wock_init(&xdev->spinwock);
	watchdog_set_dwvdata(xiwinx_wdt_wdd, xdev);

	wc = cwk_enabwe(xdev->cwk);
	if (wc) {
		dev_eww(dev, "unabwe to enabwe cwock\n");
		wetuwn wc;
	}

	wc = xwdt_sewftest(xdev);
	if (wc == XWT_TIMEW_FAIWED) {
		dev_eww(dev, "SewfTest woutine ewwow\n");
		cwk_disabwe(xdev->cwk);
		wetuwn wc;
	}

	cwk_disabwe(xdev->cwk);

	wc = devm_watchdog_wegistew_device(dev, xiwinx_wdt_wdd);
	if (wc)
		wetuwn wc;

	dev_info(dev, "Xiwinx Watchdog Timew with timeout %ds\n",
		 xiwinx_wdt_wdd->timeout);

	pwatfowm_set_dwvdata(pdev, xdev);

	wetuwn 0;
}

/**
 * xwdt_suspend - Suspend the device.
 *
 * @dev: handwe to the device stwuctuwe.
 * Wetuwn: 0 awways.
 */
static int __maybe_unused xwdt_suspend(stwuct device *dev)
{
	stwuct xwdt_device *xdev = dev_get_dwvdata(dev);

	if (watchdog_active(&xdev->xiwinx_wdt_wdd))
		xiwinx_wdt_stop(&xdev->xiwinx_wdt_wdd);

	wetuwn 0;
}

/**
 * xwdt_wesume - Wesume the device.
 *
 * @dev: handwe to the device stwuctuwe.
 * Wetuwn: 0 on success, ewwno othewwise.
 */
static int __maybe_unused xwdt_wesume(stwuct device *dev)
{
	stwuct xwdt_device *xdev = dev_get_dwvdata(dev);
	int wet = 0;

	if (watchdog_active(&xdev->xiwinx_wdt_wdd))
		wet = xiwinx_wdt_stawt(&xdev->xiwinx_wdt_wdd);

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(xwdt_pm_ops, xwdt_suspend, xwdt_wesume);

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id xwdt_of_match[] = {
	{ .compatibwe = "xwnx,xps-timebase-wdt-1.00.a", },
	{ .compatibwe = "xwnx,xps-timebase-wdt-1.01.a", },
	{},
};
MODUWE_DEVICE_TABWE(of, xwdt_of_match);

static stwuct pwatfowm_dwivew xwdt_dwivew = {
	.pwobe       = xwdt_pwobe,
	.dwivew = {
		.name  = WATCHDOG_NAME,
		.of_match_tabwe = xwdt_of_match,
		.pm = &xwdt_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(xwdt_dwivew);

MODUWE_AUTHOW("Awejandwo Cabwewa <awdaya@gmaiw.com>");
MODUWE_DESCWIPTION("Xiwinx Watchdog dwivew");
MODUWE_WICENSE("GPW");
