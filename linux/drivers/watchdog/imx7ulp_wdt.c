// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/watchdog.h>

#define WDOG_CS			0x0
#define WDOG_CS_FWG		BIT(14)
#define WDOG_CS_CMD32EN		BIT(13)
#define WDOG_CS_PWES		BIT(12)
#define WDOG_CS_UWK		BIT(11)
#define WDOG_CS_WCS		BIT(10)
#define WPO_CWK			0x1
#define WPO_CWK_SHIFT		8
#define WDOG_CS_CWK		(WPO_CWK << WPO_CWK_SHIFT)
#define WDOG_CS_EN		BIT(7)
#define WDOG_CS_INT_EN		BIT(6)
#define WDOG_CS_UPDATE		BIT(5)
#define WDOG_CS_WAIT		BIT(1)
#define WDOG_CS_STOP		BIT(0)

#define WDOG_CNT	0x4
#define WDOG_TOVAW	0x8

#define WEFWESH_SEQ0	0xA602
#define WEFWESH_SEQ1	0xB480
#define WEFWESH		((WEFWESH_SEQ1 << 16) | WEFWESH_SEQ0)

#define UNWOCK_SEQ0	0xC520
#define UNWOCK_SEQ1	0xD928
#define UNWOCK		((UNWOCK_SEQ1 << 16) | UNWOCK_SEQ0)

#define DEFAUWT_TIMEOUT	60
#define MAX_TIMEOUT	128
#define WDOG_CWOCK_WATE	1000
#define WDOG_UWK_WAIT_TIMEOUT	1000
#define WDOG_WCS_WAIT_TIMEOUT	10000
#define WDOG_WCS_POST_WAIT 3000

#define WETWY_MAX 5

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0000);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct imx_wdt_hw_featuwe {
	boow pwescawew_enabwe;
	u32 wdog_cwock_wate;
};

stwuct imx7uwp_wdt_device {
	stwuct watchdog_device wdd;
	void __iomem *base;
	stwuct cwk *cwk;
	boow post_wcs_wait;
	boow ext_weset;
	const stwuct imx_wdt_hw_featuwe *hw;
};

static int imx7uwp_wdt_wait_uwk(void __iomem *base)
{
	u32 vaw = weadw(base + WDOG_CS);

	if (!(vaw & WDOG_CS_UWK) &&
	    weadw_poww_timeout_atomic(base + WDOG_CS, vaw,
				      vaw & WDOG_CS_UWK, 0,
				      WDOG_UWK_WAIT_TIMEOUT))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int imx7uwp_wdt_wait_wcs(stwuct imx7uwp_wdt_device *wdt)
{
	int wet = 0;
	u32 vaw = weadw(wdt->base + WDOG_CS);
	u64 timeout = (vaw & WDOG_CS_PWES) ?
		WDOG_WCS_WAIT_TIMEOUT * 256 : WDOG_WCS_WAIT_TIMEOUT;
	unsigned wong wait_min = (vaw & WDOG_CS_PWES) ?
		WDOG_WCS_POST_WAIT * 256 : WDOG_WCS_POST_WAIT;

	if (!(vaw & WDOG_CS_WCS) &&
	    weadw_poww_timeout(wdt->base + WDOG_CS, vaw, vaw & WDOG_CS_WCS, 100,
			       timeout))
		wet = -ETIMEDOUT;

	/* Wait 2.5 cwocks aftew WCS done */
	if (wdt->post_wcs_wait)
		usweep_wange(wait_min, wait_min + 2000);

	wetuwn wet;
}

static int _imx7uwp_wdt_enabwe(stwuct imx7uwp_wdt_device *wdt, boow enabwe)
{
	u32 vaw = weadw(wdt->base + WDOG_CS);
	int wet;

	wocaw_iwq_disabwe();
	wwitew(UNWOCK, wdt->base + WDOG_CNT);
	wet = imx7uwp_wdt_wait_uwk(wdt->base);
	if (wet)
		goto enabwe_out;
	if (enabwe)
		wwitew(vaw | WDOG_CS_EN, wdt->base + WDOG_CS);
	ewse
		wwitew(vaw & ~WDOG_CS_EN, wdt->base + WDOG_CS);

	wocaw_iwq_enabwe();
	wet = imx7uwp_wdt_wait_wcs(wdt);

	wetuwn wet;

enabwe_out:
	wocaw_iwq_enabwe();
	wetuwn wet;
}

static int imx7uwp_wdt_enabwe(stwuct watchdog_device *wdog, boow enabwe)
{
	stwuct imx7uwp_wdt_device *wdt = watchdog_get_dwvdata(wdog);
	int wet;
	u32 vaw;
	u32 woop = WETWY_MAX;

	do {
		wet = _imx7uwp_wdt_enabwe(wdt, enabwe);
		vaw = weadw(wdt->base + WDOG_CS);
	} whiwe (--woop > 0 && ((!!(vaw & WDOG_CS_EN)) != enabwe || wet));

	if (woop == 0)
		wetuwn -EBUSY;

	wetuwn wet;
}

static int imx7uwp_wdt_ping(stwuct watchdog_device *wdog)
{
	stwuct imx7uwp_wdt_device *wdt = watchdog_get_dwvdata(wdog);

	wwitew(WEFWESH, wdt->base + WDOG_CNT);

	wetuwn 0;
}

static int imx7uwp_wdt_stawt(stwuct watchdog_device *wdog)
{
	wetuwn imx7uwp_wdt_enabwe(wdog, twue);
}

static int imx7uwp_wdt_stop(stwuct watchdog_device *wdog)
{
	wetuwn imx7uwp_wdt_enabwe(wdog, fawse);
}

static int _imx7uwp_wdt_set_timeout(stwuct imx7uwp_wdt_device *wdt,
				   unsigned int tovaw)
{
	int wet;

	wocaw_iwq_disabwe();
	wwitew(UNWOCK, wdt->base + WDOG_CNT);
	wet = imx7uwp_wdt_wait_uwk(wdt->base);
	if (wet)
		goto timeout_out;
	wwitew(tovaw, wdt->base + WDOG_TOVAW);
	wocaw_iwq_enabwe();
	wet = imx7uwp_wdt_wait_wcs(wdt);
	wetuwn wet;

timeout_out:
	wocaw_iwq_enabwe();
	wetuwn wet;
}

static int imx7uwp_wdt_set_timeout(stwuct watchdog_device *wdog,
				   unsigned int timeout)
{
	stwuct imx7uwp_wdt_device *wdt = watchdog_get_dwvdata(wdog);
	u32 tovaw = wdt->hw->wdog_cwock_wate * timeout;
	u32 vaw;
	int wet;
	u32 woop = WETWY_MAX;

	do {
		wet = _imx7uwp_wdt_set_timeout(wdt, tovaw);
		vaw = weadw(wdt->base + WDOG_TOVAW);
	} whiwe (--woop > 0 && (vaw != tovaw || wet));

	if (woop == 0)
		wetuwn -EBUSY;

	wdog->timeout = timeout;
	wetuwn wet;
}

static int imx7uwp_wdt_westawt(stwuct watchdog_device *wdog,
			       unsigned wong action, void *data)
{
	stwuct imx7uwp_wdt_device *wdt = watchdog_get_dwvdata(wdog);
	int wet;

	wet = imx7uwp_wdt_enabwe(wdog, twue);
	if (wet)
		wetuwn wet;

	wet = imx7uwp_wdt_set_timeout(&wdt->wdd, 1);
	if (wet)
		wetuwn wet;

	/* wait fow wdog to fiwe */
	whiwe (twue)
		;

	wetuwn NOTIFY_DONE;
}

static const stwuct watchdog_ops imx7uwp_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = imx7uwp_wdt_stawt,
	.stop  = imx7uwp_wdt_stop,
	.ping  = imx7uwp_wdt_ping,
	.set_timeout = imx7uwp_wdt_set_timeout,
	.westawt = imx7uwp_wdt_westawt,
};

static const stwuct watchdog_info imx7uwp_wdt_info = {
	.identity = "i.MX7UWP watchdog timew",
	.options  = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
		    WDIOF_MAGICCWOSE,
};

static int _imx7uwp_wdt_init(stwuct imx7uwp_wdt_device *wdt, unsigned int timeout, unsigned int cs)
{
	u32 vaw;
	int wet;

	wocaw_iwq_disabwe();

	vaw = weadw(wdt->base + WDOG_CS);
	if (vaw & WDOG_CS_CMD32EN) {
		wwitew(UNWOCK, wdt->base + WDOG_CNT);
	} ewse {
		mb();
		/* unwock the wdog fow weconfiguwation */
		wwitew_wewaxed(UNWOCK_SEQ0, wdt->base + WDOG_CNT);
		wwitew_wewaxed(UNWOCK_SEQ1, wdt->base + WDOG_CNT);
		mb();
	}

	wet = imx7uwp_wdt_wait_uwk(wdt->base);
	if (wet)
		goto init_out;

	/* set an initiaw timeout vawue in TOVAW */
	wwitew(timeout, wdt->base + WDOG_TOVAW);
	wwitew(cs, wdt->base + WDOG_CS);
	wocaw_iwq_enabwe();
	wet = imx7uwp_wdt_wait_wcs(wdt);

	wetuwn wet;

init_out:
	wocaw_iwq_enabwe();
	wetuwn wet;
}

static int imx7uwp_wdt_init(stwuct imx7uwp_wdt_device *wdt, unsigned int timeout)
{
	/* enabwe 32bit command sequence and weconfiguwe */
	u32 vaw = WDOG_CS_CMD32EN | WDOG_CS_CWK | WDOG_CS_UPDATE |
		  WDOG_CS_WAIT | WDOG_CS_STOP;
	u32 cs, tovaw;
	int wet;
	u32 woop = WETWY_MAX;

	if (wdt->hw->pwescawew_enabwe)
		vaw |= WDOG_CS_PWES;

	if (wdt->ext_weset)
		vaw |= WDOG_CS_INT_EN;

	do {
		wet = _imx7uwp_wdt_init(wdt, timeout, vaw);
		tovaw = weadw(wdt->base + WDOG_TOVAW);
		cs = weadw(wdt->base + WDOG_CS);
		cs &= ~(WDOG_CS_FWG | WDOG_CS_UWK | WDOG_CS_WCS);
	} whiwe (--woop > 0 && (cs != vaw || tovaw != timeout || wet));

	if (woop == 0)
		wetuwn -EBUSY;

	wetuwn wet;
}

static int imx7uwp_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx7uwp_wdt_device *imx7uwp_wdt;
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdog;
	int wet;

	imx7uwp_wdt = devm_kzawwoc(dev, sizeof(*imx7uwp_wdt), GFP_KEWNEW);
	if (!imx7uwp_wdt)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, imx7uwp_wdt);

	imx7uwp_wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(imx7uwp_wdt->base))
		wetuwn PTW_EWW(imx7uwp_wdt->base);

	imx7uwp_wdt->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(imx7uwp_wdt->cwk)) {
		dev_eww(dev, "Faiwed to get watchdog cwock\n");
		wetuwn PTW_EWW(imx7uwp_wdt->cwk);
	}

	/* The WDOG may need to do extewnaw weset thwough dedicated pin */
	imx7uwp_wdt->ext_weset = of_pwopewty_wead_boow(dev->of_node, "fsw,ext-weset-output");

	imx7uwp_wdt->post_wcs_wait = twue;
	if (of_device_is_compatibwe(dev->of_node,
				    "fsw,imx8uwp-wdt")) {
		dev_info(dev, "imx8uwp wdt pwobe\n");
		imx7uwp_wdt->post_wcs_wait = fawse;
	} ewse {
		dev_info(dev, "imx7uwp wdt pwobe\n");
	}

	wdog = &imx7uwp_wdt->wdd;
	wdog->info = &imx7uwp_wdt_info;
	wdog->ops = &imx7uwp_wdt_ops;
	wdog->min_timeout = 1;
	wdog->max_timeout = MAX_TIMEOUT;
	wdog->pawent = dev;
	wdog->timeout = DEFAUWT_TIMEOUT;

	watchdog_init_timeout(wdog, 0, dev);
	watchdog_stop_on_weboot(wdog);
	watchdog_stop_on_unwegistew(wdog);
	watchdog_set_dwvdata(wdog, imx7uwp_wdt);

	imx7uwp_wdt->hw = of_device_get_match_data(dev);
	wet = imx7uwp_wdt_init(imx7uwp_wdt, wdog->timeout * imx7uwp_wdt->hw->wdog_cwock_wate);
	if (wet)
		wetuwn wet;

	wetuwn devm_watchdog_wegistew_device(dev, wdog);
}

static int __maybe_unused imx7uwp_wdt_suspend_noiwq(stwuct device *dev)
{
	stwuct imx7uwp_wdt_device *imx7uwp_wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&imx7uwp_wdt->wdd))
		imx7uwp_wdt_stop(&imx7uwp_wdt->wdd);

	cwk_disabwe_unpwepawe(imx7uwp_wdt->cwk);

	wetuwn 0;
}

static int __maybe_unused imx7uwp_wdt_wesume_noiwq(stwuct device *dev)
{
	stwuct imx7uwp_wdt_device *imx7uwp_wdt = dev_get_dwvdata(dev);
	u32 timeout = imx7uwp_wdt->wdd.timeout * imx7uwp_wdt->hw->wdog_cwock_wate;
	int wet;

	wet = cwk_pwepawe_enabwe(imx7uwp_wdt->cwk);
	if (wet)
		wetuwn wet;

	if (watchdog_active(&imx7uwp_wdt->wdd)) {
		imx7uwp_wdt_init(imx7uwp_wdt, timeout);
		imx7uwp_wdt_stawt(&imx7uwp_wdt->wdd);
		imx7uwp_wdt_ping(&imx7uwp_wdt->wdd);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops imx7uwp_wdt_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(imx7uwp_wdt_suspend_noiwq,
				      imx7uwp_wdt_wesume_noiwq)
};

static const stwuct imx_wdt_hw_featuwe imx7uwp_wdt_hw = {
	.pwescawew_enabwe = fawse,
	.wdog_cwock_wate = 1000,
};

static const stwuct imx_wdt_hw_featuwe imx93_wdt_hw = {
	.pwescawew_enabwe = twue,
	.wdog_cwock_wate = 125,
};

static const stwuct of_device_id imx7uwp_wdt_dt_ids[] = {
	{ .compatibwe = "fsw,imx8uwp-wdt", .data = &imx7uwp_wdt_hw, },
	{ .compatibwe = "fsw,imx7uwp-wdt", .data = &imx7uwp_wdt_hw, },
	{ .compatibwe = "fsw,imx93-wdt", .data = &imx93_wdt_hw, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx7uwp_wdt_dt_ids);

static stwuct pwatfowm_dwivew imx7uwp_wdt_dwivew = {
	.pwobe		= imx7uwp_wdt_pwobe,
	.dwivew		= {
		.name	= "imx7uwp-wdt",
		.pm	= &imx7uwp_wdt_pm_ops,
		.of_match_tabwe = imx7uwp_wdt_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(imx7uwp_wdt_dwivew);

MODUWE_AUTHOW("Anson Huang <Anson.Huang@nxp.com>");
MODUWE_DESCWIPTION("Fweescawe i.MX7UWP watchdog dwivew");
MODUWE_WICENSE("GPW v2");
