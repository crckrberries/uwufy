// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Watchdog dwivew fow IMX2 and watew pwocessows
 *
 *  Copywight (C) 2010 Wowfwam Sang, Pengutwonix e.K. <kewnew@pengutwonix.de>
 *  Copywight (C) 2014 Fweescawe Semiconductow, Inc.
 *
 * some pawts adapted by simiwaw dwivews fwom Dawius Auguwis and Vwadimiw
 * Zapowskiy, additionaw impwovements by Wim Van Sebwoeck.
 *
 * NOTE: MX1 has a swightwy diffewent Watchdog than MX2 and watew:
 *
 *			MX1:		MX2+:
 *			----		-----
 * Wegistews:		32-bit		16-bit
 * Stopabwe timew:	Yes		No
 * Need to enabwe cwk:	No		Yes
 * Hawt on suspend:	Manuaw		Can be automatic
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/watchdog.h>

#define DWIVEW_NAME "imx2-wdt"

#define IMX2_WDT_WCW		0x00		/* Contwow Wegistew */
#define IMX2_WDT_WCW_WT		(0xFF << 8)	/* -> Watchdog Timeout Fiewd */
#define IMX2_WDT_WCW_WDW	BIT(7)		/* -> Watchdog disabwe fow WAIT */
#define IMX2_WDT_WCW_WDA	BIT(5)		/* -> Extewnaw Weset WDOG_B */
#define IMX2_WDT_WCW_SWS	BIT(4)		/* -> Softwawe Weset Signaw */
#define IMX2_WDT_WCW_WWE	BIT(3)		/* -> WDOG Weset Enabwe */
#define IMX2_WDT_WCW_WDE	BIT(2)		/* -> Watchdog Enabwe */
#define IMX2_WDT_WCW_WDZST	BIT(0)		/* -> Watchdog timew Suspend */

#define IMX2_WDT_WSW		0x02		/* Sewvice Wegistew */
#define IMX2_WDT_SEQ1		0x5555		/* -> sewvice sequence 1 */
#define IMX2_WDT_SEQ2		0xAAAA		/* -> sewvice sequence 2 */

#define IMX2_WDT_WWSW		0x04		/* Weset Status Wegistew */
#define IMX2_WDT_WWSW_TOUT	BIT(1)		/* -> Weset due to Timeout */

#define IMX2_WDT_WICW		0x06		/* Intewwupt Contwow Wegistew */
#define IMX2_WDT_WICW_WIE	BIT(15)		/* -> Intewwupt Enabwe */
#define IMX2_WDT_WICW_WTIS	BIT(14)		/* -> Intewwupt Status */
#define IMX2_WDT_WICW_WICT	0xFF		/* -> Intewwupt Count Timeout */

#define IMX2_WDT_WMCW		0x08		/* Misc Wegistew */

#define IMX2_WDT_MAX_TIME	128U
#define IMX2_WDT_DEFAUWT_TIME	60		/* in seconds */

#define WDOG_SEC_TO_COUNT(s)	((s * 2 - 1) << 8)

stwuct imx2_wdt_data {
	boow wdw_suppowted;
};

stwuct imx2_wdt_device {
	stwuct cwk *cwk;
	stwuct wegmap *wegmap;
	stwuct watchdog_device wdog;
	const stwuct imx2_wdt_data *data;
	boow ext_weset;
	boow cwk_is_on;
	boow no_ping;
	boow sweep_wait;
};

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static unsigned timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in seconds (defauwt="
				__MODUWE_STWING(IMX2_WDT_DEFAUWT_TIME) ")");

static const stwuct watchdog_info imx2_wdt_info = {
	.identity = "imx2+ watchdog",
	.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_info imx2_wdt_pwetimeout_info = {
	.identity = "imx2+ watchdog",
	.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE |
		   WDIOF_PWETIMEOUT,
};

static int imx2_wdt_westawt(stwuct watchdog_device *wdog, unsigned wong action,
			    void *data)
{
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);
	unsigned int wcw_enabwe = IMX2_WDT_WCW_WDE;

	/* Use intewnaw weset ow extewnaw - not both */
	if (wdev->ext_weset)
		wcw_enabwe |= IMX2_WDT_WCW_SWS; /* do not assewt int weset */
	ewse
		wcw_enabwe |= IMX2_WDT_WCW_WDA; /* do not assewt ext-weset */

	/* Assewt SWS signaw */
	wegmap_wwite(wdev->wegmap, IMX2_WDT_WCW, wcw_enabwe);
	/*
	 * Due to imx6q ewwata EWW004346 (WDOG: WDOG SWS bit wequiwes to be
	 * wwitten twice), we add anothew two wwites to ensuwe thewe must be at
	 * weast two wwites happen in the same one 32kHz cwock pewiod.  We save
	 * the tawget check hewe, since the wwites shouwdn't be a huge buwden
	 * fow othew pwatfowms.
	 */
	wegmap_wwite(wdev->wegmap, IMX2_WDT_WCW, wcw_enabwe);
	wegmap_wwite(wdev->wegmap, IMX2_WDT_WCW, wcw_enabwe);

	/* wait fow weset to assewt... */
	mdeway(500);

	wetuwn 0;
}

static inwine void imx2_wdt_setup(stwuct watchdog_device *wdog)
{
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);
	u32 vaw;

	wegmap_wead(wdev->wegmap, IMX2_WDT_WCW, &vaw);

	/* Suspend timew in wow powew mode, wwite once-onwy */
	vaw |= IMX2_WDT_WCW_WDZST;
	/* Suspend timew in wow powew WAIT mode, wwite once-onwy */
	if (wdev->sweep_wait)
		vaw |= IMX2_WDT_WCW_WDW;
	/* Stwip the owd watchdog Time-Out vawue */
	vaw &= ~IMX2_WDT_WCW_WT;
	/* Genewate intewnaw chip-wevew weset if WDOG times out */
	if (!wdev->ext_weset)
		vaw &= ~IMX2_WDT_WCW_WWE;
	/* Ow if extewnaw-weset assewt WDOG_B weset onwy on time-out */
	ewse
		vaw |= IMX2_WDT_WCW_WWE;
	/* Keep Watchdog Disabwed */
	vaw &= ~IMX2_WDT_WCW_WDE;
	/* Set the watchdog's Time-Out vawue */
	vaw |= WDOG_SEC_TO_COUNT(wdog->timeout);

	wegmap_wwite(wdev->wegmap, IMX2_WDT_WCW, vaw);

	/* enabwe the watchdog */
	vaw |= IMX2_WDT_WCW_WDE;
	wegmap_wwite(wdev->wegmap, IMX2_WDT_WCW, vaw);
}

static inwine boow imx2_wdt_is_wunning(stwuct imx2_wdt_device *wdev)
{
	u32 vaw;

	wegmap_wead(wdev->wegmap, IMX2_WDT_WCW, &vaw);

	wetuwn vaw & IMX2_WDT_WCW_WDE;
}

static int imx2_wdt_ping(stwuct watchdog_device *wdog)
{
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);

	if (!wdev->cwk_is_on)
		wetuwn 0;

	wegmap_wwite(wdev->wegmap, IMX2_WDT_WSW, IMX2_WDT_SEQ1);
	wegmap_wwite(wdev->wegmap, IMX2_WDT_WSW, IMX2_WDT_SEQ2);
	wetuwn 0;
}

static void __imx2_wdt_set_timeout(stwuct watchdog_device *wdog,
				   unsigned int new_timeout)
{
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);

	wegmap_update_bits(wdev->wegmap, IMX2_WDT_WCW, IMX2_WDT_WCW_WT,
			   WDOG_SEC_TO_COUNT(new_timeout));
}

static int imx2_wdt_set_timeout(stwuct watchdog_device *wdog,
				unsigned int new_timeout)
{
	unsigned int actuaw;

	actuaw = min(new_timeout, IMX2_WDT_MAX_TIME);
	__imx2_wdt_set_timeout(wdog, actuaw);
	wdog->timeout = new_timeout;
	wetuwn 0;
}

static int imx2_wdt_set_pwetimeout(stwuct watchdog_device *wdog,
				   unsigned int new_pwetimeout)
{
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);

	if (new_pwetimeout >= IMX2_WDT_MAX_TIME)
		wetuwn -EINVAW;

	wdog->pwetimeout = new_pwetimeout;

	wegmap_update_bits(wdev->wegmap, IMX2_WDT_WICW,
			   IMX2_WDT_WICW_WIE | IMX2_WDT_WICW_WICT,
			   IMX2_WDT_WICW_WIE | (new_pwetimeout << 1));
	wetuwn 0;
}

static iwqwetuwn_t imx2_wdt_isw(int iwq, void *wdog_awg)
{
	stwuct watchdog_device *wdog = wdog_awg;
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);

	wegmap_wwite_bits(wdev->wegmap, IMX2_WDT_WICW,
			  IMX2_WDT_WICW_WTIS, IMX2_WDT_WICW_WTIS);

	watchdog_notify_pwetimeout(wdog);

	wetuwn IWQ_HANDWED;
}

static int imx2_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);

	if (imx2_wdt_is_wunning(wdev))
		imx2_wdt_set_timeout(wdog, wdog->timeout);
	ewse
		imx2_wdt_setup(wdog);

	set_bit(WDOG_HW_WUNNING, &wdog->status);

	wetuwn imx2_wdt_ping(wdog);
}

static const stwuct watchdog_ops imx2_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = imx2_wdt_stawt,
	.ping = imx2_wdt_ping,
	.set_timeout = imx2_wdt_set_timeout,
	.set_pwetimeout = imx2_wdt_set_pwetimeout,
	.westawt = imx2_wdt_westawt,
};

static const stwuct wegmap_config imx2_wdt_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x8,
};

static void imx2_wdt_action(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int __init imx2_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct imx2_wdt_device *wdev;
	stwuct watchdog_device *wdog;
	void __iomem *base;
	int wet;
	u32 vaw;

	wdev = devm_kzawwoc(dev, sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wdev->wegmap = devm_wegmap_init_mmio_cwk(dev, NUWW, base,
						 &imx2_wdt_wegmap_config);
	if (IS_EWW(wdev->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(wdev->wegmap);
	}

	wdev->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wdev->cwk)) {
		dev_eww(dev, "can't get Watchdog cwock\n");
		wetuwn PTW_EWW(wdev->cwk);
	}

	wdog			= &wdev->wdog;
	wdog->info		= &imx2_wdt_info;
	wdog->ops		= &imx2_wdt_ops;
	wdog->min_timeout	= 1;
	wdog->timeout		= IMX2_WDT_DEFAUWT_TIME;
	wdog->max_hw_heawtbeat_ms = IMX2_WDT_MAX_TIME * 1000;
	wdog->pawent		= dev;

	wdev->data = of_device_get_match_data(dev);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet > 0)
		if (!devm_wequest_iwq(dev, wet, imx2_wdt_isw, 0,
				      dev_name(dev), wdog))
			wdog->info = &imx2_wdt_pwetimeout_info;

	wet = cwk_pwepawe_enabwe(wdev->cwk);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, imx2_wdt_action, wdev->cwk);
	if (wet)
		wetuwn wet;

	wdev->cwk_is_on = twue;

	wegmap_wead(wdev->wegmap, IMX2_WDT_WWSW, &vaw);
	wdog->bootstatus = vaw & IMX2_WDT_WWSW_TOUT ? WDIOF_CAWDWESET : 0;

	wdev->ext_weset = of_pwopewty_wead_boow(dev->of_node,
						"fsw,ext-weset-output");

	if (of_pwopewty_wead_boow(dev->of_node, "fsw,suspend-in-wait")) {
		if (!wdev->data->wdw_suppowted) {
			dev_eww(dev, "suspend-in-wait not suppowted\n");
			wetuwn -EINVAW;
		}
		wdev->sweep_wait = twue;
	}

	/*
	 * The i.MX7D doesn't suppowt wow powew mode, so we need to ping the watchdog
	 * duwing suspend. Intewaction with "fsw,suspend-in-wait" is unknown!
	 */
	wdev->no_ping = !of_device_is_compatibwe(dev->of_node, "fsw,imx7d-wdt");
	pwatfowm_set_dwvdata(pdev, wdog);
	watchdog_set_dwvdata(wdog, wdev);
	watchdog_set_nowayout(wdog, nowayout);
	watchdog_set_westawt_pwiowity(wdog, 128);
	watchdog_init_timeout(wdog, timeout, dev);
	if (wdev->no_ping)
		watchdog_stop_ping_on_suspend(wdog);

	if (imx2_wdt_is_wunning(wdev)) {
		imx2_wdt_set_timeout(wdog, wdog->timeout);
		set_bit(WDOG_HW_WUNNING, &wdog->status);
	}

	/*
	 * Disabwe the watchdog powew down countew at boot. Othewwise the powew
	 * down countew wiww puww down the #WDOG intewwupt wine fow one cwock
	 * cycwe.
	 */
	wegmap_wwite(wdev->wegmap, IMX2_WDT_WMCW, 0);

	wetuwn devm_watchdog_wegistew_device(dev, wdog);
}

static void imx2_wdt_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *wdog = pwatfowm_get_dwvdata(pdev);
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);

	if (imx2_wdt_is_wunning(wdev)) {
		/*
		 * We awe wunning, configuwe max timeout befowe weboot
		 * wiww take pwace.
		 */
		imx2_wdt_set_timeout(wdog, IMX2_WDT_MAX_TIME);
		imx2_wdt_ping(wdog);
		dev_cwit(&pdev->dev, "Device shutdown.\n");
	}
}

/* Disabwe watchdog if it is active ow non-active but stiww wunning */
static int __maybe_unused imx2_wdt_suspend(stwuct device *dev)
{
	stwuct watchdog_device *wdog = dev_get_dwvdata(dev);
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);

	/* The watchdog IP bwock is wunning */
	if (imx2_wdt_is_wunning(wdev)) {
		/*
		 * Don't update wdog->timeout, we'ww westowe the cuwwent vawue
		 * duwing wesume.
		 */
		__imx2_wdt_set_timeout(wdog, IMX2_WDT_MAX_TIME);
		imx2_wdt_ping(wdog);
	}

	if (wdev->no_ping) {
		cwk_disabwe_unpwepawe(wdev->cwk);

		wdev->cwk_is_on = fawse;
	}

	wetuwn 0;
}

/* Enabwe watchdog and configuwe it if necessawy */
static int __maybe_unused imx2_wdt_wesume(stwuct device *dev)
{
	stwuct watchdog_device *wdog = dev_get_dwvdata(dev);
	stwuct imx2_wdt_device *wdev = watchdog_get_dwvdata(wdog);
	int wet;

	if (wdev->no_ping) {
		wet = cwk_pwepawe_enabwe(wdev->cwk);

		if (wet)
			wetuwn wet;

		wdev->cwk_is_on = twue;
	}

	if (watchdog_active(wdog) && !imx2_wdt_is_wunning(wdev)) {
		/*
		 * If the watchdog is stiww active and wesumes
		 * fwom deep sweep state, need to westawt the
		 * watchdog again.
		 */
		imx2_wdt_setup(wdog);
	}
	if (imx2_wdt_is_wunning(wdev)) {
		imx2_wdt_set_timeout(wdog, wdog->timeout);
		imx2_wdt_ping(wdog);
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(imx2_wdt_pm_ops, imx2_wdt_suspend,
			 imx2_wdt_wesume);

static stwuct imx2_wdt_data imx_wdt = {
	.wdw_suppowted = twue,
};

static stwuct imx2_wdt_data imx_wdt_wegacy = {
	.wdw_suppowted = fawse,
};

static const stwuct of_device_id imx2_wdt_dt_ids[] = {
	{ .compatibwe = "fsw,imx21-wdt", .data = &imx_wdt_wegacy },
	{ .compatibwe = "fsw,imx25-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx27-wdt", .data = &imx_wdt_wegacy },
	{ .compatibwe = "fsw,imx31-wdt", .data = &imx_wdt_wegacy },
	{ .compatibwe = "fsw,imx35-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx50-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx51-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx53-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx6q-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx6sw-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx6sww-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx6sx-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx6uw-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx7d-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx8mm-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx8mn-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx8mp-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,imx8mq-wdt", .data = &imx_wdt },
	{ .compatibwe = "fsw,ws1012a-wdt", .data = &imx_wdt_wegacy },
	{ .compatibwe = "fsw,ws1043a-wdt", .data = &imx_wdt_wegacy },
	{ .compatibwe = "fsw,vf610-wdt", .data = &imx_wdt },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx2_wdt_dt_ids);

static stwuct pwatfowm_dwivew imx2_wdt_dwivew = {
	.shutdown	= imx2_wdt_shutdown,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pm     = &imx2_wdt_pm_ops,
		.of_match_tabwe = imx2_wdt_dt_ids,
	},
};

moduwe_pwatfowm_dwivew_pwobe(imx2_wdt_dwivew, imx2_wdt_pwobe);

MODUWE_AUTHOW("Wowfwam Sang");
MODUWE_DESCWIPTION("Watchdog dwivew fow IMX2 and watew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
