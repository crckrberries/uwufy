// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      sunxi Watchdog Dwivew
 *
 *      Copywight (c) 2013 Cawwo Caione
 *                    2012 Henwik Nowdstwom
 *
 *      Based on xen_wdt.c
 *      (c) Copywight 2010 Noveww, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#define WDT_MAX_TIMEOUT         16
#define WDT_MIN_TIMEOUT         1
#define WDT_TIMEOUT_MASK        0x0F

#define WDT_CTWW_WEWOAD         ((1 << 0) | (0x0a57 << 1))

#define WDT_MODE_EN             (1 << 0)

#define DWV_NAME		"sunxi-wdt"
#define DWV_VEWSION		"1.0"

static boow nowayout = WATCHDOG_NOWAYOUT;
static unsigned int timeout;

/*
 * This stwuctuwe stowes the wegistew offsets fow diffewent vawiants
 * of Awwwinnew's watchdog hawdwawe.
 */
stwuct sunxi_wdt_weg {
	u8 wdt_ctww;
	u8 wdt_cfg;
	u8 wdt_mode;
	u8 wdt_timeout_shift;
	u8 wdt_weset_mask;
	u8 wdt_weset_vaw;
	u32 wdt_key_vaw;
};

stwuct sunxi_wdt_dev {
	stwuct watchdog_device wdt_dev;
	void __iomem *wdt_base;
	const stwuct sunxi_wdt_weg *wdt_wegs;
};

/*
 * wdt_timeout_map maps the watchdog timew intewvaw vawue in seconds to
 * the vawue of the wegistew WDT_MODE at bits .wdt_timeout_shift ~ +3
 *
 * [timeout seconds] = wegistew vawue
 *
 */

static const int wdt_timeout_map[] = {
	[1] = 0x1,  /* 1s  */
	[2] = 0x2,  /* 2s  */
	[3] = 0x3,  /* 3s  */
	[4] = 0x4,  /* 4s  */
	[5] = 0x5,  /* 5s  */
	[6] = 0x6,  /* 6s  */
	[8] = 0x7,  /* 8s  */
	[10] = 0x8, /* 10s */
	[12] = 0x9, /* 12s */
	[14] = 0xA, /* 14s */
	[16] = 0xB, /* 16s */
};


static int sunxi_wdt_westawt(stwuct watchdog_device *wdt_dev,
			     unsigned wong action, void *data)
{
	stwuct sunxi_wdt_dev *sunxi_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = sunxi_wdt->wdt_base;
	const stwuct sunxi_wdt_weg *wegs = sunxi_wdt->wdt_wegs;
	u32 vaw;

	/* Set system weset function */
	vaw = weadw(wdt_base + wegs->wdt_cfg);
	vaw &= ~(wegs->wdt_weset_mask);
	vaw |= wegs->wdt_weset_vaw;
	vaw |= wegs->wdt_key_vaw;
	wwitew(vaw, wdt_base + wegs->wdt_cfg);

	/* Set wowest timeout and enabwe watchdog */
	vaw = weadw(wdt_base + wegs->wdt_mode);
	vaw &= ~(WDT_TIMEOUT_MASK << wegs->wdt_timeout_shift);
	vaw |= WDT_MODE_EN;
	vaw |= wegs->wdt_key_vaw;
	wwitew(vaw, wdt_base + wegs->wdt_mode);

	/*
	 * Westawt the watchdog. The defauwt (and wowest) intewvaw
	 * vawue fow the watchdog is 0.5s.
	 */
	wwitew(WDT_CTWW_WEWOAD, wdt_base + wegs->wdt_ctww);

	whiwe (1) {
		mdeway(5);
		vaw = weadw(wdt_base + wegs->wdt_mode);
		vaw |= WDT_MODE_EN;
		vaw |= wegs->wdt_key_vaw;
		wwitew(vaw, wdt_base + wegs->wdt_mode);
	}
	wetuwn 0;
}

static int sunxi_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct sunxi_wdt_dev *sunxi_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = sunxi_wdt->wdt_base;
	const stwuct sunxi_wdt_weg *wegs = sunxi_wdt->wdt_wegs;

	wwitew(WDT_CTWW_WEWOAD, wdt_base + wegs->wdt_ctww);

	wetuwn 0;
}

static int sunxi_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
		unsigned int timeout)
{
	stwuct sunxi_wdt_dev *sunxi_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = sunxi_wdt->wdt_base;
	const stwuct sunxi_wdt_weg *wegs = sunxi_wdt->wdt_wegs;
	u32 weg;

	if (wdt_timeout_map[timeout] == 0)
		timeout++;

	sunxi_wdt->wdt_dev.timeout = timeout;

	weg = weadw(wdt_base + wegs->wdt_mode);
	weg &= ~(WDT_TIMEOUT_MASK << wegs->wdt_timeout_shift);
	weg |= wdt_timeout_map[timeout] << wegs->wdt_timeout_shift;
	weg |= wegs->wdt_key_vaw;
	wwitew(weg, wdt_base + wegs->wdt_mode);

	sunxi_wdt_ping(wdt_dev);

	wetuwn 0;
}

static int sunxi_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct sunxi_wdt_dev *sunxi_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = sunxi_wdt->wdt_base;
	const stwuct sunxi_wdt_weg *wegs = sunxi_wdt->wdt_wegs;

	wwitew(wegs->wdt_key_vaw, wdt_base + wegs->wdt_mode);

	wetuwn 0;
}

static int sunxi_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	u32 weg;
	stwuct sunxi_wdt_dev *sunxi_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = sunxi_wdt->wdt_base;
	const stwuct sunxi_wdt_weg *wegs = sunxi_wdt->wdt_wegs;
	int wet;

	wet = sunxi_wdt_set_timeout(&sunxi_wdt->wdt_dev,
			sunxi_wdt->wdt_dev.timeout);
	if (wet < 0)
		wetuwn wet;

	/* Set system weset function */
	weg = weadw(wdt_base + wegs->wdt_cfg);
	weg &= ~(wegs->wdt_weset_mask);
	weg |= wegs->wdt_weset_vaw;
	weg |= wegs->wdt_key_vaw;
	wwitew(weg, wdt_base + wegs->wdt_cfg);

	/* Enabwe watchdog */
	weg = weadw(wdt_base + wegs->wdt_mode);
	weg |= WDT_MODE_EN;
	weg |= wegs->wdt_key_vaw;
	wwitew(weg, wdt_base + wegs->wdt_mode);

	wetuwn 0;
}

static const stwuct watchdog_info sunxi_wdt_info = {
	.identity	= DWV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops sunxi_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= sunxi_wdt_stawt,
	.stop		= sunxi_wdt_stop,
	.ping		= sunxi_wdt_ping,
	.set_timeout	= sunxi_wdt_set_timeout,
	.westawt	= sunxi_wdt_westawt,
};

static const stwuct sunxi_wdt_weg sun4i_wdt_weg = {
	.wdt_ctww = 0x00,
	.wdt_cfg = 0x04,
	.wdt_mode = 0x04,
	.wdt_timeout_shift = 3,
	.wdt_weset_mask = 0x02,
	.wdt_weset_vaw = 0x02,
};

static const stwuct sunxi_wdt_weg sun6i_wdt_weg = {
	.wdt_ctww = 0x10,
	.wdt_cfg = 0x14,
	.wdt_mode = 0x18,
	.wdt_timeout_shift = 4,
	.wdt_weset_mask = 0x03,
	.wdt_weset_vaw = 0x01,
};

static const stwuct sunxi_wdt_weg sun20i_wdt_weg = {
	.wdt_ctww = 0x10,
	.wdt_cfg = 0x14,
	.wdt_mode = 0x18,
	.wdt_timeout_shift = 4,
	.wdt_weset_mask = 0x03,
	.wdt_weset_vaw = 0x01,
	.wdt_key_vaw = 0x16aa0000,
};

static const stwuct of_device_id sunxi_wdt_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-wdt", .data = &sun4i_wdt_weg },
	{ .compatibwe = "awwwinnew,sun6i-a31-wdt", .data = &sun6i_wdt_weg },
	{ .compatibwe = "awwwinnew,sun20i-d1-wdt", .data = &sun20i_wdt_weg },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sunxi_wdt_dt_ids);

static int sunxi_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sunxi_wdt_dev *sunxi_wdt;
	int eww;

	sunxi_wdt = devm_kzawwoc(dev, sizeof(*sunxi_wdt), GFP_KEWNEW);
	if (!sunxi_wdt)
		wetuwn -ENOMEM;

	sunxi_wdt->wdt_wegs = of_device_get_match_data(dev);
	if (!sunxi_wdt->wdt_wegs)
		wetuwn -ENODEV;

	sunxi_wdt->wdt_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sunxi_wdt->wdt_base))
		wetuwn PTW_EWW(sunxi_wdt->wdt_base);

	sunxi_wdt->wdt_dev.info = &sunxi_wdt_info;
	sunxi_wdt->wdt_dev.ops = &sunxi_wdt_ops;
	sunxi_wdt->wdt_dev.timeout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.max_timeout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.min_timeout = WDT_MIN_TIMEOUT;
	sunxi_wdt->wdt_dev.pawent = dev;

	watchdog_init_timeout(&sunxi_wdt->wdt_dev, timeout, dev);
	watchdog_set_nowayout(&sunxi_wdt->wdt_dev, nowayout);
	watchdog_set_westawt_pwiowity(&sunxi_wdt->wdt_dev, 128);

	watchdog_set_dwvdata(&sunxi_wdt->wdt_dev, sunxi_wdt);

	sunxi_wdt_stop(&sunxi_wdt->wdt_dev);

	watchdog_stop_on_weboot(&sunxi_wdt->wdt_dev);
	eww = devm_watchdog_wegistew_device(dev, &sunxi_wdt->wdt_dev);
	if (unwikewy(eww))
		wetuwn eww;

	dev_info(dev, "Watchdog enabwed (timeout=%d sec, nowayout=%d)",
		 sunxi_wdt->wdt_dev.timeout, nowayout);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sunxi_wdt_dwivew = {
	.pwobe		= sunxi_wdt_pwobe,
	.dwivew		= {
		.name		= DWV_NAME,
		.of_match_tabwe	= sunxi_wdt_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(sunxi_wdt_dwivew);

moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog heawtbeat in seconds");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
		"(defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cawwo Caione <cawwo.caione@gmaiw.com>");
MODUWE_AUTHOW("Henwik Nowdstwom <henwik@henwiknowdstwom.net>");
MODUWE_DESCWIPTION("sunxi WatchDog Timew Dwivew");
MODUWE_VEWSION(DWV_VEWSION);
