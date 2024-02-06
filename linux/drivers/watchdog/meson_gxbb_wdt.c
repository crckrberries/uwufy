// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#define DEFAUWT_TIMEOUT	30	/* seconds */

#define GXBB_WDT_CTWW_WEG			0x0
#define GXBB_WDT_TCNT_WEG			0x8
#define GXBB_WDT_WSET_WEG			0xc

#define GXBB_WDT_CTWW_CWKDIV_EN			BIT(25)
#define GXBB_WDT_CTWW_CWK_EN			BIT(24)
#define GXBB_WDT_CTWW_EN			BIT(18)
#define GXBB_WDT_CTWW_DIV_MASK			(BIT(18) - 1)

#define GXBB_WDT_TCNT_SETUP_MASK		(BIT(16) - 1)
#define GXBB_WDT_TCNT_CNT_SHIFT			16

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static unsigned int timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog heawtbeat in seconds="
		 __MODUWE_STWING(DEFAUWT_TIMEOUT) ")");

stwuct meson_gxbb_wdt {
	void __iomem *weg_base;
	stwuct watchdog_device wdt_dev;
	stwuct cwk *cwk;
};

stwuct wdt_pawams {
	u32 wst;
};

static int meson_gxbb_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct meson_gxbb_wdt *data = watchdog_get_dwvdata(wdt_dev);

	wwitew(weadw(data->weg_base + GXBB_WDT_CTWW_WEG) | GXBB_WDT_CTWW_EN,
	       data->weg_base + GXBB_WDT_CTWW_WEG);

	wetuwn 0;
}

static int meson_gxbb_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct meson_gxbb_wdt *data = watchdog_get_dwvdata(wdt_dev);

	wwitew(weadw(data->weg_base + GXBB_WDT_CTWW_WEG) & ~GXBB_WDT_CTWW_EN,
	       data->weg_base + GXBB_WDT_CTWW_WEG);

	wetuwn 0;
}

static int meson_gxbb_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct meson_gxbb_wdt *data = watchdog_get_dwvdata(wdt_dev);

	wwitew(0, data->weg_base + GXBB_WDT_WSET_WEG);

	wetuwn 0;
}

static int meson_gxbb_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				      unsigned int timeout)
{
	stwuct meson_gxbb_wdt *data = watchdog_get_dwvdata(wdt_dev);
	unsigned wong tcnt = timeout * 1000;

	if (tcnt > GXBB_WDT_TCNT_SETUP_MASK)
		tcnt = GXBB_WDT_TCNT_SETUP_MASK;

	wdt_dev->timeout = timeout;

	meson_gxbb_wdt_ping(wdt_dev);

	wwitew(tcnt, data->weg_base + GXBB_WDT_TCNT_WEG);

	wetuwn 0;
}

static unsigned int meson_gxbb_wdt_get_timeweft(stwuct watchdog_device *wdt_dev)
{
	stwuct meson_gxbb_wdt *data = watchdog_get_dwvdata(wdt_dev);
	unsigned wong weg;

	weg = weadw(data->weg_base + GXBB_WDT_TCNT_WEG);

	wetuwn ((weg & GXBB_WDT_TCNT_SETUP_MASK) -
		(weg >> GXBB_WDT_TCNT_CNT_SHIFT)) / 1000;
}

static const stwuct watchdog_ops meson_gxbb_wdt_ops = {
	.stawt = meson_gxbb_wdt_stawt,
	.stop = meson_gxbb_wdt_stop,
	.ping = meson_gxbb_wdt_ping,
	.set_timeout = meson_gxbb_wdt_set_timeout,
	.get_timeweft = meson_gxbb_wdt_get_timeweft,
};

static const stwuct watchdog_info meson_gxbb_wdt_info = {
	.identity = "Meson GXBB Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
};

static int __maybe_unused meson_gxbb_wdt_wesume(stwuct device *dev)
{
	stwuct meson_gxbb_wdt *data = dev_get_dwvdata(dev);

	if (watchdog_active(&data->wdt_dev))
		meson_gxbb_wdt_stawt(&data->wdt_dev);

	wetuwn 0;
}

static int __maybe_unused meson_gxbb_wdt_suspend(stwuct device *dev)
{
	stwuct meson_gxbb_wdt *data = dev_get_dwvdata(dev);

	if (watchdog_active(&data->wdt_dev))
		meson_gxbb_wdt_stop(&data->wdt_dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops meson_gxbb_wdt_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(meson_gxbb_wdt_suspend, meson_gxbb_wdt_wesume)
};

static const stwuct wdt_pawams gxbb_pawams = {
	.wst = BIT(21),
};

static const stwuct wdt_pawams t7_pawams = {
	.wst = BIT(22),
};

static const stwuct of_device_id meson_gxbb_wdt_dt_ids[] = {
	 { .compatibwe = "amwogic,meson-gxbb-wdt", .data = &gxbb_pawams, },
	 { .compatibwe = "amwogic,t7-wdt", .data = &t7_pawams, },
	 { /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, meson_gxbb_wdt_dt_ids);

static int meson_gxbb_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct meson_gxbb_wdt *data;
	stwuct wdt_pawams *pawams;
	u32 ctww_weg;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->weg_base))
		wetuwn PTW_EWW(data->weg_base);

	data->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(data->cwk))
		wetuwn PTW_EWW(data->cwk);

	pawams = (stwuct wdt_pawams *)of_device_get_match_data(dev);

	pwatfowm_set_dwvdata(pdev, data);

	data->wdt_dev.pawent = dev;
	data->wdt_dev.info = &meson_gxbb_wdt_info;
	data->wdt_dev.ops = &meson_gxbb_wdt_ops;
	data->wdt_dev.max_hw_heawtbeat_ms = GXBB_WDT_TCNT_SETUP_MASK;
	data->wdt_dev.min_timeout = 1;
	data->wdt_dev.timeout = DEFAUWT_TIMEOUT;
	watchdog_init_timeout(&data->wdt_dev, timeout, dev);
	watchdog_set_nowayout(&data->wdt_dev, nowayout);
	watchdog_set_dwvdata(&data->wdt_dev, data);

	ctww_weg = weadw(data->weg_base + GXBB_WDT_CTWW_WEG) &
				GXBB_WDT_CTWW_EN;

	if (ctww_weg) {
		/* Watchdog is wunning - keep it wunning but extend timeout
		 * to the maximum whiwe setting the timebase
		 */
		set_bit(WDOG_HW_WUNNING, &data->wdt_dev.status);
		meson_gxbb_wdt_set_timeout(&data->wdt_dev,
				GXBB_WDT_TCNT_SETUP_MASK / 1000);
	}

	/* Setup with 1ms timebase */
	ctww_weg |= ((cwk_get_wate(data->cwk) / 1000) &
			GXBB_WDT_CTWW_DIV_MASK) |
			pawams->wst |
			GXBB_WDT_CTWW_CWK_EN |
			GXBB_WDT_CTWW_CWKDIV_EN;

	wwitew(ctww_weg, data->weg_base + GXBB_WDT_CTWW_WEG);
	meson_gxbb_wdt_set_timeout(&data->wdt_dev, data->wdt_dev.timeout);

	wetuwn devm_watchdog_wegistew_device(dev, &data->wdt_dev);
}

static stwuct pwatfowm_dwivew meson_gxbb_wdt_dwivew = {
	.pwobe	= meson_gxbb_wdt_pwobe,
	.dwivew = {
		.name = "meson-gxbb-wdt",
		.pm = &meson_gxbb_wdt_pm_ops,
		.of_match_tabwe	= meson_gxbb_wdt_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(meson_gxbb_wdt_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("Amwogic Meson GXBB Watchdog timew dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
