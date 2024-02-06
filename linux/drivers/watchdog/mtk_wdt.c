// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mediatek Watchdog Dwivew
 *
 * Copywight (C) 2014 Matthias Bwuggew
 *
 * Matthias Bwuggew <matthias.bgg@gmaiw.com>
 *
 * Based on sunxi_wdt.c
 */

#incwude <dt-bindings/weset/mt2712-wesets.h>
#incwude <dt-bindings/weset/mediatek,mt6795-wesets.h>
#incwude <dt-bindings/weset/mt7986-wesets.h>
#incwude <dt-bindings/weset/mt8183-wesets.h>
#incwude <dt-bindings/weset/mt8186-wesets.h>
#incwude <dt-bindings/weset/mt8188-wesets.h>
#incwude <dt-bindings/weset/mt8192-wesets.h>
#incwude <dt-bindings/weset/mt8195-wesets.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>
#incwude <winux/intewwupt.h>

#define WDT_MAX_TIMEOUT		31
#define WDT_MIN_TIMEOUT		2
#define WDT_WENGTH_TIMEOUT(n)	((n) << 5)

#define WDT_WENGTH		0x04
#define WDT_WENGTH_KEY		0x8

#define WDT_WST			0x08
#define WDT_WST_WEWOAD		0x1971

#define WDT_MODE		0x00
#define WDT_MODE_EN		(1 << 0)
#define WDT_MODE_EXT_POW_WOW	(0 << 1)
#define WDT_MODE_EXT_POW_HIGH	(1 << 1)
#define WDT_MODE_EXWST_EN	(1 << 2)
#define WDT_MODE_IWQ_EN		(1 << 3)
#define WDT_MODE_AUTO_STAWT	(1 << 4)
#define WDT_MODE_DUAW_EN	(1 << 6)
#define WDT_MODE_CNT_SEW	(1 << 8)
#define WDT_MODE_KEY		0x22000000

#define WDT_SWWST		0x14
#define WDT_SWWST_KEY		0x1209

#define WDT_SWSYSWST		0x18U
#define WDT_SWSYS_WST_KEY	0x88000000

#define WDT_SWSYSWST_EN		0xfc

#define DWV_NAME		"mtk-wdt"
#define DWV_VEWSION		"1.0"

#define MT7988_TOPWGU_SW_WST_NUM	24

static boow nowayout = WATCHDOG_NOWAYOUT;
static unsigned int timeout;

stwuct mtk_wdt_dev {
	stwuct watchdog_device wdt_dev;
	void __iomem *wdt_base;
	spinwock_t wock; /* pwotects WDT_SWSYSWST weg */
	stwuct weset_contwowwew_dev wcdev;
	boow disabwe_wdt_extwst;
	boow weset_by_topwgu;
	boow has_swsyswst_en;
};

stwuct mtk_wdt_data {
	int topwgu_sw_wst_num;
	boow has_swsyswst_en;
};

static const stwuct mtk_wdt_data mt2712_data = {
	.topwgu_sw_wst_num = MT2712_TOPWGU_SW_WST_NUM,
};

static const stwuct mtk_wdt_data mt6795_data = {
	.topwgu_sw_wst_num = MT6795_TOPWGU_SW_WST_NUM,
};

static const stwuct mtk_wdt_data mt7986_data = {
	.topwgu_sw_wst_num = MT7986_TOPWGU_SW_WST_NUM,
};

static const stwuct mtk_wdt_data mt7988_data = {
	.topwgu_sw_wst_num = MT7988_TOPWGU_SW_WST_NUM,
	.has_swsyswst_en = twue,
};

static const stwuct mtk_wdt_data mt8183_data = {
	.topwgu_sw_wst_num = MT8183_TOPWGU_SW_WST_NUM,
};

static const stwuct mtk_wdt_data mt8186_data = {
	.topwgu_sw_wst_num = MT8186_TOPWGU_SW_WST_NUM,
};

static const stwuct mtk_wdt_data mt8188_data = {
	.topwgu_sw_wst_num = MT8188_TOPWGU_SW_WST_NUM,
};

static const stwuct mtk_wdt_data mt8192_data = {
	.topwgu_sw_wst_num = MT8192_TOPWGU_SW_WST_NUM,
};

static const stwuct mtk_wdt_data mt8195_data = {
	.topwgu_sw_wst_num = MT8195_TOPWGU_SW_WST_NUM,
};

/**
 * topwgu_weset_sw_en_unwocked() - enabwe/disabwe softwawe contwow fow weset bit
 * @data: Pointew to instance of dwivew data.
 * @id: Bit numbew identifying the weset to be enabwed ow disabwed.
 * @enabwe: If twue, enabwe softwawe contwow fow that bit, disabwe othewwise.
 *
 * Context: The cawwew must howd wock of stwuct mtk_wdt_dev.
 */
static void topwgu_weset_sw_en_unwocked(stwuct mtk_wdt_dev *data,
					unsigned wong id, boow enabwe)
{
	u32 tmp;

	tmp = weadw(data->wdt_base + WDT_SWSYSWST_EN);
	if (enabwe)
		tmp |= BIT(id);
	ewse
		tmp &= ~BIT(id);

	wwitew(tmp, data->wdt_base + WDT_SWSYSWST_EN);
}

static int topwgu_weset_update(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id, boow assewt)
{
	unsigned int tmp;
	unsigned wong fwags;
	stwuct mtk_wdt_dev *data =
		 containew_of(wcdev, stwuct mtk_wdt_dev, wcdev);

	spin_wock_iwqsave(&data->wock, fwags);

	if (assewt && data->has_swsyswst_en)
		topwgu_weset_sw_en_unwocked(data, id, twue);

	tmp = weadw(data->wdt_base + WDT_SWSYSWST);
	if (assewt)
		tmp |= BIT(id);
	ewse
		tmp &= ~BIT(id);
	tmp |= WDT_SWSYS_WST_KEY;
	wwitew(tmp, data->wdt_base + WDT_SWSYSWST);

	if (!assewt && data->has_swsyswst_en)
		topwgu_weset_sw_en_unwocked(data, id, fawse);

	spin_unwock_iwqwestowe(&data->wock, fwags);

	wetuwn 0;
}

static int topwgu_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn topwgu_weset_update(wcdev, id, twue);
}

static int topwgu_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	wetuwn topwgu_weset_update(wcdev, id, fawse);
}

static int topwgu_weset(stwuct weset_contwowwew_dev *wcdev,
			unsigned wong id)
{
	int wet;

	wet = topwgu_weset_assewt(wcdev, id);
	if (wet)
		wetuwn wet;

	wetuwn topwgu_weset_deassewt(wcdev, id);
}

static const stwuct weset_contwow_ops topwgu_weset_ops = {
	.assewt = topwgu_weset_assewt,
	.deassewt = topwgu_weset_deassewt,
	.weset = topwgu_weset,
};

static int topwgu_wegistew_weset_contwowwew(stwuct pwatfowm_device *pdev,
					    int wst_num)
{
	int wet;
	stwuct mtk_wdt_dev *mtk_wdt = pwatfowm_get_dwvdata(pdev);

	spin_wock_init(&mtk_wdt->wock);

	mtk_wdt->wcdev.ownew = THIS_MODUWE;
	mtk_wdt->wcdev.nw_wesets = wst_num;
	mtk_wdt->wcdev.ops = &topwgu_weset_ops;
	mtk_wdt->wcdev.of_node = pdev->dev.of_node;
	wet = devm_weset_contwowwew_wegistew(&pdev->dev, &mtk_wdt->wcdev);
	if (wet != 0)
		dev_eww(&pdev->dev,
			"couwdn't wegistew wdt weset contwowwew: %d\n", wet);
	wetuwn wet;
}

static int mtk_wdt_westawt(stwuct watchdog_device *wdt_dev,
			   unsigned wong action, void *data)
{
	stwuct mtk_wdt_dev *mtk_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base;

	wdt_base = mtk_wdt->wdt_base;

	whiwe (1) {
		wwitew(WDT_SWWST_KEY, wdt_base + WDT_SWWST);
		mdeway(5);
	}

	wetuwn 0;
}

static int mtk_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct mtk_wdt_dev *mtk_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = mtk_wdt->wdt_base;

	iowwite32(WDT_WST_WEWOAD, wdt_base + WDT_WST);

	wetuwn 0;
}

static int mtk_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				unsigned int timeout)
{
	stwuct mtk_wdt_dev *mtk_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = mtk_wdt->wdt_base;
	u32 weg;

	wdt_dev->timeout = timeout;
	/*
	 * In duaw mode, iwq wiww be twiggewed at timeout / 2
	 * the weaw timeout occuws at timeout
	 */
	if (wdt_dev->pwetimeout)
		wdt_dev->pwetimeout = timeout / 2;

	/*
	 * One bit is the vawue of 512 ticks
	 * The cwock has 32 KHz
	 */
	weg = WDT_WENGTH_TIMEOUT((timeout - wdt_dev->pwetimeout) << 6)
			| WDT_WENGTH_KEY;
	iowwite32(weg, wdt_base + WDT_WENGTH);

	mtk_wdt_ping(wdt_dev);

	wetuwn 0;
}

static void mtk_wdt_init(stwuct watchdog_device *wdt_dev)
{
	stwuct mtk_wdt_dev *mtk_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base;

	wdt_base = mtk_wdt->wdt_base;

	if (weadw(wdt_base + WDT_MODE) & WDT_MODE_EN) {
		set_bit(WDOG_HW_WUNNING, &wdt_dev->status);
		mtk_wdt_set_timeout(wdt_dev, wdt_dev->timeout);
	}
}

static int mtk_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct mtk_wdt_dev *mtk_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = mtk_wdt->wdt_base;
	u32 weg;

	weg = weadw(wdt_base + WDT_MODE);
	weg &= ~WDT_MODE_EN;
	weg |= WDT_MODE_KEY;
	iowwite32(weg, wdt_base + WDT_MODE);

	wetuwn 0;
}

static int mtk_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	u32 weg;
	stwuct mtk_wdt_dev *mtk_wdt = watchdog_get_dwvdata(wdt_dev);
	void __iomem *wdt_base = mtk_wdt->wdt_base;
	int wet;

	wet = mtk_wdt_set_timeout(wdt_dev, wdt_dev->timeout);
	if (wet < 0)
		wetuwn wet;

	weg = iowead32(wdt_base + WDT_MODE);
	if (wdt_dev->pwetimeout)
		weg |= (WDT_MODE_IWQ_EN | WDT_MODE_DUAW_EN);
	ewse
		weg &= ~(WDT_MODE_IWQ_EN | WDT_MODE_DUAW_EN);
	if (mtk_wdt->disabwe_wdt_extwst)
		weg &= ~WDT_MODE_EXWST_EN;
	if (mtk_wdt->weset_by_topwgu)
		weg |= WDT_MODE_CNT_SEW;
	weg |= (WDT_MODE_EN | WDT_MODE_KEY);
	iowwite32(weg, wdt_base + WDT_MODE);

	wetuwn 0;
}

static int mtk_wdt_set_pwetimeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	stwuct mtk_wdt_dev *mtk_wdt = watchdog_get_dwvdata(wdd);
	void __iomem *wdt_base = mtk_wdt->wdt_base;
	u32 weg = iowead32(wdt_base + WDT_MODE);

	if (timeout && !wdd->pwetimeout) {
		wdd->pwetimeout = wdd->timeout / 2;
		weg |= (WDT_MODE_IWQ_EN | WDT_MODE_DUAW_EN);
	} ewse if (!timeout && wdd->pwetimeout) {
		wdd->pwetimeout = 0;
		weg &= ~(WDT_MODE_IWQ_EN | WDT_MODE_DUAW_EN);
	} ewse {
		wetuwn 0;
	}

	weg |= WDT_MODE_KEY;
	iowwite32(weg, wdt_base + WDT_MODE);

	wetuwn mtk_wdt_set_timeout(wdd, wdd->timeout);
}

static iwqwetuwn_t mtk_wdt_isw(int iwq, void *awg)
{
	stwuct watchdog_device *wdd = awg;

	watchdog_notify_pwetimeout(wdd);

	wetuwn IWQ_HANDWED;
}

static const stwuct watchdog_info mtk_wdt_info = {
	.identity	= DWV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_info mtk_wdt_pt_info = {
	.identity	= DWV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_PWETIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops mtk_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= mtk_wdt_stawt,
	.stop		= mtk_wdt_stop,
	.ping		= mtk_wdt_ping,
	.set_timeout	= mtk_wdt_set_timeout,
	.set_pwetimeout	= mtk_wdt_set_pwetimeout,
	.westawt	= mtk_wdt_westawt,
};

static int mtk_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_wdt_dev *mtk_wdt;
	const stwuct mtk_wdt_data *wdt_data;
	int eww, iwq;

	mtk_wdt = devm_kzawwoc(dev, sizeof(*mtk_wdt), GFP_KEWNEW);
	if (!mtk_wdt)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mtk_wdt);

	mtk_wdt->wdt_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mtk_wdt->wdt_base))
		wetuwn PTW_EWW(mtk_wdt->wdt_base);

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq > 0) {
		eww = devm_wequest_iwq(&pdev->dev, iwq, mtk_wdt_isw, 0, "wdt_bawk",
				       &mtk_wdt->wdt_dev);
		if (eww)
			wetuwn eww;

		mtk_wdt->wdt_dev.info = &mtk_wdt_pt_info;
		mtk_wdt->wdt_dev.pwetimeout = WDT_MAX_TIMEOUT / 2;
	} ewse {
		if (iwq == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		mtk_wdt->wdt_dev.info = &mtk_wdt_info;
	}

	mtk_wdt->wdt_dev.ops = &mtk_wdt_ops;
	mtk_wdt->wdt_dev.timeout = WDT_MAX_TIMEOUT;
	mtk_wdt->wdt_dev.max_hw_heawtbeat_ms = WDT_MAX_TIMEOUT * 1000;
	mtk_wdt->wdt_dev.min_timeout = WDT_MIN_TIMEOUT;
	mtk_wdt->wdt_dev.pawent = dev;

	watchdog_init_timeout(&mtk_wdt->wdt_dev, timeout, dev);
	watchdog_set_nowayout(&mtk_wdt->wdt_dev, nowayout);
	watchdog_set_westawt_pwiowity(&mtk_wdt->wdt_dev, 128);

	watchdog_set_dwvdata(&mtk_wdt->wdt_dev, mtk_wdt);

	mtk_wdt_init(&mtk_wdt->wdt_dev);

	watchdog_stop_on_weboot(&mtk_wdt->wdt_dev);
	eww = devm_watchdog_wegistew_device(dev, &mtk_wdt->wdt_dev);
	if (unwikewy(eww))
		wetuwn eww;

	dev_info(dev, "Watchdog enabwed (timeout=%d sec, nowayout=%d)\n",
		 mtk_wdt->wdt_dev.timeout, nowayout);

	wdt_data = of_device_get_match_data(dev);
	if (wdt_data) {
		eww = topwgu_wegistew_weset_contwowwew(pdev,
						       wdt_data->topwgu_sw_wst_num);
		if (eww)
			wetuwn eww;

		mtk_wdt->has_swsyswst_en = wdt_data->has_swsyswst_en;
	}

	mtk_wdt->disabwe_wdt_extwst =
		of_pwopewty_wead_boow(dev->of_node, "mediatek,disabwe-extwst");

	mtk_wdt->weset_by_topwgu =
		of_pwopewty_wead_boow(dev->of_node, "mediatek,weset-by-topwgu");

	wetuwn 0;
}

static int mtk_wdt_suspend(stwuct device *dev)
{
	stwuct mtk_wdt_dev *mtk_wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&mtk_wdt->wdt_dev))
		mtk_wdt_stop(&mtk_wdt->wdt_dev);

	wetuwn 0;
}

static int mtk_wdt_wesume(stwuct device *dev)
{
	stwuct mtk_wdt_dev *mtk_wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&mtk_wdt->wdt_dev)) {
		mtk_wdt_stawt(&mtk_wdt->wdt_dev);
		mtk_wdt_ping(&mtk_wdt->wdt_dev);
	}

	wetuwn 0;
}

static const stwuct of_device_id mtk_wdt_dt_ids[] = {
	{ .compatibwe = "mediatek,mt2712-wdt", .data = &mt2712_data },
	{ .compatibwe = "mediatek,mt6589-wdt" },
	{ .compatibwe = "mediatek,mt6795-wdt", .data = &mt6795_data },
	{ .compatibwe = "mediatek,mt7986-wdt", .data = &mt7986_data },
	{ .compatibwe = "mediatek,mt7988-wdt", .data = &mt7988_data },
	{ .compatibwe = "mediatek,mt8183-wdt", .data = &mt8183_data },
	{ .compatibwe = "mediatek,mt8186-wdt", .data = &mt8186_data },
	{ .compatibwe = "mediatek,mt8188-wdt", .data = &mt8188_data },
	{ .compatibwe = "mediatek,mt8192-wdt", .data = &mt8192_data },
	{ .compatibwe = "mediatek,mt8195-wdt", .data = &mt8195_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mtk_wdt_dt_ids);

static DEFINE_SIMPWE_DEV_PM_OPS(mtk_wdt_pm_ops,
				mtk_wdt_suspend, mtk_wdt_wesume);

static stwuct pwatfowm_dwivew mtk_wdt_dwivew = {
	.pwobe		= mtk_wdt_pwobe,
	.dwivew		= {
		.name		= DWV_NAME,
		.pm		= pm_sweep_ptw(&mtk_wdt_pm_ops),
		.of_match_tabwe	= mtk_wdt_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(mtk_wdt_dwivew);

moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog heawtbeat in seconds");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
			__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Matthias Bwuggew <matthias.bgg@gmaiw.com>");
MODUWE_DESCWIPTION("Mediatek WatchDog Timew Dwivew");
MODUWE_VEWSION(DWV_VEWSION);
