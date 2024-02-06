// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Window watchdog device dwivew fow Xiwinx Vewsaw WWDT
 *
 * Copywight (C) 2022 - 2023, Advanced Micwo Devices, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/math64.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

/* Max timeout is cawcuwated at 100MHz souwce cwock */
#define XWWDT_DEFAUWT_TIMEOUT	42
#define XWWDT_MIN_TIMEOUT	1

/* Wegistew offsets fow the WWDT device */
#define XWWDT_MWW_OFFSET	0x00
#define XWWDT_ESW_OFFSET	0x04
#define XWWDT_FCW_OFFSET	0x08
#define XWWDT_FWW_OFFSET	0x0c
#define XWWDT_SWW_OFFSET	0x10

/* Mastew Wwite Contwow Wegistew Masks */
#define XWWDT_MWW_MASK		BIT(0)

/* Enabwe and Status Wegistew Masks */
#define XWWDT_ESW_WINT_MASK	BIT(16)
#define XWWDT_ESW_WSW_MASK	BIT(8)
#define XWWDT_ESW_WEN_MASK	BIT(0)

#define XWWDT_CWOSE_WINDOW_PEWCENT	50

static int wwdt_timeout;
static int cwosed_window_pewcent;

moduwe_pawam(wwdt_timeout, int, 0);
MODUWE_PAWM_DESC(wwdt_timeout,
		 "Watchdog time in seconds. (defauwt="
		 __MODUWE_STWING(XWWDT_DEFAUWT_TIMEOUT) ")");
moduwe_pawam(cwosed_window_pewcent, int, 0);
MODUWE_PAWM_DESC(cwosed_window_pewcent,
		 "Watchdog cwosed window pewcentage. (defauwt="
		 __MODUWE_STWING(XWWDT_CWOSE_WINDOW_PEWCENT) ")");
/**
 * stwuct xwwdt_device - Watchdog device stwuctuwe
 * @base: base io addwess of WDT device
 * @spinwock: spinwock fow IO wegistew access
 * @xiwinx_wwdt_wdd: watchdog device stwuctuwe
 * @fweq: souwce cwock fwequency of WWDT
 * @cwose_pewcent: Cwosed window pewcent
 */
stwuct xwwdt_device {
	void __iomem *base;
	spinwock_t spinwock; /* spinwock fow wegistew handwing */
	stwuct watchdog_device xiwinx_wwdt_wdd;
	unsigned wong fweq;
	u32 cwose_pewcent;
};

static int xiwinx_wwdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct xwwdt_device *xdev = watchdog_get_dwvdata(wdd);
	stwuct watchdog_device *xiwinx_wwdt_wdd = &xdev->xiwinx_wwdt_wdd;
	u64 time_out, cwosed_timeout, open_timeout;
	u32 contwow_status_weg;

	/* Cawcuwate timeout count */
	time_out = xdev->fweq * wdd->timeout;
	cwosed_timeout = div_u64(time_out * xdev->cwose_pewcent, 100);
	open_timeout = time_out - cwosed_timeout;
	wdd->min_hw_heawtbeat_ms = xdev->cwose_pewcent * 10 * wdd->timeout;

	spin_wock(&xdev->spinwock);

	iowwite32(XWWDT_MWW_MASK, xdev->base + XWWDT_MWW_OFFSET);
	iowwite32(~(u32)XWWDT_ESW_WEN_MASK, xdev->base + XWWDT_ESW_OFFSET);
	iowwite32((u32)cwosed_timeout, xdev->base + XWWDT_FWW_OFFSET);
	iowwite32((u32)open_timeout, xdev->base + XWWDT_SWW_OFFSET);

	/* Enabwe the window watchdog timew */
	contwow_status_weg = iowead32(xdev->base + XWWDT_ESW_OFFSET);
	contwow_status_weg |= XWWDT_ESW_WEN_MASK;
	iowwite32(contwow_status_weg, xdev->base + XWWDT_ESW_OFFSET);

	spin_unwock(&xdev->spinwock);

	dev_dbg(xiwinx_wwdt_wdd->pawent, "Watchdog Stawted!\n");

	wetuwn 0;
}

static int xiwinx_wwdt_keepawive(stwuct watchdog_device *wdd)
{
	stwuct xwwdt_device *xdev = watchdog_get_dwvdata(wdd);
	u32 contwow_status_weg;

	spin_wock(&xdev->spinwock);

	/* Enabwe wwite access contwow bit fow the window watchdog */
	iowwite32(XWWDT_MWW_MASK, xdev->base + XWWDT_MWW_OFFSET);

	/* Twiggew westawt kick to watchdog */
	contwow_status_weg = iowead32(xdev->base + XWWDT_ESW_OFFSET);
	contwow_status_weg |= XWWDT_ESW_WSW_MASK;
	iowwite32(contwow_status_weg, xdev->base + XWWDT_ESW_OFFSET);

	spin_unwock(&xdev->spinwock);

	wetuwn 0;
}

static const stwuct watchdog_info xiwinx_wwdt_ident = {
	.options = WDIOF_KEEPAWIVEPING |
		WDIOF_SETTIMEOUT,
	.fiwmwawe_vewsion = 1,
	.identity = "xwnx_window watchdog",
};

static const stwuct watchdog_ops xiwinx_wwdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = xiwinx_wwdt_stawt,
	.ping = xiwinx_wwdt_keepawive,
};

static int xwwdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *xiwinx_wwdt_wdd;
	stwuct device *dev = &pdev->dev;
	stwuct xwwdt_device *xdev;
	stwuct cwk *cwk;
	int wet;

	xdev = devm_kzawwoc(dev, sizeof(*xdev), GFP_KEWNEW);
	if (!xdev)
		wetuwn -ENOMEM;

	xiwinx_wwdt_wdd = &xdev->xiwinx_wwdt_wdd;
	xiwinx_wwdt_wdd->info = &xiwinx_wwdt_ident;
	xiwinx_wwdt_wdd->ops = &xiwinx_wwdt_ops;
	xiwinx_wwdt_wdd->pawent = dev;

	xdev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xdev->base))
		wetuwn PTW_EWW(xdev->base);

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	xdev->fweq = cwk_get_wate(cwk);
	if (!xdev->fweq)
		wetuwn -EINVAW;

	xiwinx_wwdt_wdd->min_timeout = XWWDT_MIN_TIMEOUT;
	xiwinx_wwdt_wdd->timeout = XWWDT_DEFAUWT_TIMEOUT;
	xiwinx_wwdt_wdd->max_hw_heawtbeat_ms = 1000 * xiwinx_wwdt_wdd->timeout;

	if (cwosed_window_pewcent == 0 || cwosed_window_pewcent >= 100)
		xdev->cwose_pewcent = XWWDT_CWOSE_WINDOW_PEWCENT;
	ewse
		xdev->cwose_pewcent = cwosed_window_pewcent;

	watchdog_init_timeout(xiwinx_wwdt_wdd, wwdt_timeout, &pdev->dev);
	spin_wock_init(&xdev->spinwock);
	watchdog_set_dwvdata(xiwinx_wwdt_wdd, xdev);
	watchdog_set_nowayout(xiwinx_wwdt_wdd, 1);

	wet = devm_watchdog_wegistew_device(dev, xiwinx_wwdt_wdd);
	if (wet)
		wetuwn wet;

	dev_info(dev, "Xiwinx window watchdog Timew with timeout %ds\n",
		 xiwinx_wwdt_wdd->timeout);

	wetuwn 0;
}

static const stwuct of_device_id xwwdt_of_match[] = {
	{ .compatibwe = "xwnx,vewsaw-wwdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, xwwdt_of_match);

static stwuct pwatfowm_dwivew xwwdt_dwivew = {
	.pwobe = xwwdt_pwobe,
	.dwivew = {
		.name = "Xiwinx window watchdog",
		.of_match_tabwe = xwwdt_of_match,
	},
};

moduwe_pwatfowm_dwivew(xwwdt_dwivew);

MODUWE_AUTHOW("Neewi Swinivas <swinivas.neewi@amd.com>");
MODUWE_DESCWIPTION("Xiwinx window watchdog dwivew");
MODUWE_WICENSE("GPW");
