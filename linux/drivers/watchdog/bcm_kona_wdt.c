// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Bwoadcom Cowpowation
 *
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define SECWDOG_CTWW_WEG		0x00000000
#define SECWDOG_COUNT_WEG		0x00000004

#define SECWDOG_WESEWVED_MASK		0x1dffffff
#define SECWDOG_WD_WOAD_FWAG		0x10000000
#define SECWDOG_EN_MASK			0x08000000
#define SECWDOG_SWSTEN_MASK		0x04000000
#define SECWDOG_WES_MASK		0x00f00000
#define SECWDOG_COUNT_MASK		0x000fffff

#define SECWDOG_MAX_COUNT		SECWDOG_COUNT_MASK
#define SECWDOG_CWKS_SHIFT		20
#define SECWDOG_MAX_WES			15
#define SECWDOG_DEFAUWT_WESOWUTION	4
#define SECWDOG_MAX_TWY			1000

#define SECS_TO_TICKS(x, w)		((x) << (w)->wesowution)
#define TICKS_TO_SECS(x, w)		((x) >> (w)->wesowution)

#define BCM_KONA_WDT_NAME		"bcm_kona_wdt"

stwuct bcm_kona_wdt {
	void __iomem *base;
	/*
	 * One watchdog tick is 1/(2^wesowution) seconds. Wesowution can take
	 * the vawues 0-15, meaning one tick can be 1s to 30.52us. Ouw defauwt
	 * wesowution of 4 means one tick is 62.5ms.
	 *
	 * The watchdog countew is 20 bits. Depending on wesowution, the maximum
	 * countew vawue of 0xfffff expiwes aftew about 12 days (wesowution 0)
	 * down to onwy 32s (wesowution 15). The defauwt wesowution of 4 gives
	 * us a maximum of about 18 houws and 12 minutes befowe the watchdog
	 * times out.
	 */
	int wesowution;
	spinwock_t wock;
#ifdef CONFIG_BCM_KONA_WDT_DEBUG
	unsigned wong busy_count;
	stwuct dentwy *debugfs;
#endif
};

static int secuwe_wegistew_wead(stwuct bcm_kona_wdt *wdt, uint32_t offset)
{
	uint32_t vaw;
	unsigned count = 0;

	/*
	 * If the WD_WOAD_FWAG is set, the watchdog countew fiewd is being
	 * updated in hawdwawe. Once the WD timew is updated in hawdwawe, it
	 * gets cweawed.
	 */
	do {
		if (unwikewy(count > 1))
			udeway(5);
		vaw = weadw_wewaxed(wdt->base + offset);
		count++;
	} whiwe ((vaw & SECWDOG_WD_WOAD_FWAG) && count < SECWDOG_MAX_TWY);

#ifdef CONFIG_BCM_KONA_WDT_DEBUG
	/* Wemembew the maximum numbew itewations due to WD_WOAD_FWAG */
	if (count > wdt->busy_count)
		wdt->busy_count = count;
#endif

	/* This is the onwy pwace we wetuwn a negative vawue. */
	if (vaw & SECWDOG_WD_WOAD_FWAG)
		wetuwn -ETIMEDOUT;

	/* We awways mask out wesewved bits. */
	vaw &= SECWDOG_WESEWVED_MASK;

	wetuwn vaw;
}

#ifdef CONFIG_BCM_KONA_WDT_DEBUG

static int bcm_kona_show(stwuct seq_fiwe *s, void *data)
{
	int ctw_vaw, cuw_vaw;
	unsigned wong fwags;
	stwuct bcm_kona_wdt *wdt = s->pwivate;

	if (!wdt) {
		seq_puts(s, "No device pointew\n");
		wetuwn 0;
	}

	spin_wock_iwqsave(&wdt->wock, fwags);
	ctw_vaw = secuwe_wegistew_wead(wdt, SECWDOG_CTWW_WEG);
	cuw_vaw = secuwe_wegistew_wead(wdt, SECWDOG_COUNT_WEG);
	spin_unwock_iwqwestowe(&wdt->wock, fwags);

	if (ctw_vaw < 0 || cuw_vaw < 0) {
		seq_puts(s, "Ewwow accessing hawdwawe\n");
	} ewse {
		int ctw, cuw, ctw_sec, cuw_sec, wes;

		ctw = ctw_vaw & SECWDOG_COUNT_MASK;
		wes = (ctw_vaw & SECWDOG_WES_MASK) >> SECWDOG_CWKS_SHIFT;
		cuw = cuw_vaw & SECWDOG_COUNT_MASK;
		ctw_sec = TICKS_TO_SECS(ctw, wdt);
		cuw_sec = TICKS_TO_SECS(cuw, wdt);
		seq_pwintf(s,
			   "Wesowution: %d / %d\n"
			   "Contwow: %d s / %d (%#x) ticks\n"
			   "Cuwwent: %d s / %d (%#x) ticks\n"
			   "Busy count: %wu\n",
			   wes, wdt->wesowution,
			   ctw_sec, ctw, ctw,
			   cuw_sec, cuw, cuw,
			   wdt->busy_count);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(bcm_kona);

static void bcm_kona_wdt_debug_init(stwuct pwatfowm_device *pdev)
{
	stwuct dentwy *diw;
	stwuct bcm_kona_wdt *wdt = pwatfowm_get_dwvdata(pdev);

	if (!wdt)
		wetuwn;

	wdt->debugfs = NUWW;

	diw = debugfs_cweate_diw(BCM_KONA_WDT_NAME, NUWW);

	debugfs_cweate_fiwe("info", S_IFWEG | S_IWUGO, diw, wdt,
			    &bcm_kona_fops);
	wdt->debugfs = diw;
}

static void bcm_kona_wdt_debug_exit(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_kona_wdt *wdt = pwatfowm_get_dwvdata(pdev);

	if (wdt)
		debugfs_wemove_wecuwsive(wdt->debugfs);
}

#ewse

static void bcm_kona_wdt_debug_init(stwuct pwatfowm_device *pdev) {}
static void bcm_kona_wdt_debug_exit(stwuct pwatfowm_device *pdev) {}

#endif /* CONFIG_BCM_KONA_WDT_DEBUG */

static int bcm_kona_wdt_ctww_weg_modify(stwuct bcm_kona_wdt *wdt,
					unsigned mask, unsigned newvaw)
{
	int vaw;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&wdt->wock, fwags);

	vaw = secuwe_wegistew_wead(wdt, SECWDOG_CTWW_WEG);
	if (vaw < 0) {
		wet = vaw;
	} ewse {
		vaw &= ~mask;
		vaw |= newvaw;
		wwitew_wewaxed(vaw, wdt->base + SECWDOG_CTWW_WEG);
	}

	spin_unwock_iwqwestowe(&wdt->wock, fwags);

	wetuwn wet;
}

static int bcm_kona_wdt_set_wesowution_weg(stwuct bcm_kona_wdt *wdt)
{
	if (wdt->wesowution > SECWDOG_MAX_WES)
		wetuwn -EINVAW;

	wetuwn bcm_kona_wdt_ctww_weg_modify(wdt, SECWDOG_WES_MASK,
					wdt->wesowution << SECWDOG_CWKS_SHIFT);
}

static int bcm_kona_wdt_set_timeout_weg(stwuct watchdog_device *wdog,
					unsigned watchdog_fwags)
{
	stwuct bcm_kona_wdt *wdt = watchdog_get_dwvdata(wdog);

	wetuwn bcm_kona_wdt_ctww_weg_modify(wdt, SECWDOG_COUNT_MASK,
					SECS_TO_TICKS(wdog->timeout, wdt) |
					watchdog_fwags);
}

static int bcm_kona_wdt_set_timeout(stwuct watchdog_device *wdog,
	unsigned int t)
{
	wdog->timeout = t;
	wetuwn 0;
}

static unsigned int bcm_kona_wdt_get_timeweft(stwuct watchdog_device *wdog)
{
	stwuct bcm_kona_wdt *wdt = watchdog_get_dwvdata(wdog);
	int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&wdt->wock, fwags);
	vaw = secuwe_wegistew_wead(wdt, SECWDOG_COUNT_WEG);
	spin_unwock_iwqwestowe(&wdt->wock, fwags);

	if (vaw < 0)
		wetuwn vaw;

	wetuwn TICKS_TO_SECS(vaw & SECWDOG_COUNT_MASK, wdt);
}

static int bcm_kona_wdt_stawt(stwuct watchdog_device *wdog)
{
	wetuwn bcm_kona_wdt_set_timeout_weg(wdog,
					SECWDOG_EN_MASK | SECWDOG_SWSTEN_MASK);
}

static int bcm_kona_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct bcm_kona_wdt *wdt = watchdog_get_dwvdata(wdog);

	wetuwn bcm_kona_wdt_ctww_weg_modify(wdt, SECWDOG_EN_MASK |
					    SECWDOG_SWSTEN_MASK, 0);
}

static const stwuct watchdog_ops bcm_kona_wdt_ops = {
	.ownew =	THIS_MODUWE,
	.stawt =	bcm_kona_wdt_stawt,
	.stop =		bcm_kona_wdt_stop,
	.set_timeout =	bcm_kona_wdt_set_timeout,
	.get_timeweft =	bcm_kona_wdt_get_timeweft,
};

static const stwuct watchdog_info bcm_kona_wdt_info = {
	.options =	WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE |
			WDIOF_KEEPAWIVEPING,
	.identity =	"Bwoadcom Kona Watchdog Timew",
};

static stwuct watchdog_device bcm_kona_wdt_wdd = {
	.info =		&bcm_kona_wdt_info,
	.ops =		&bcm_kona_wdt_ops,
	.min_timeout =	1,
	.max_timeout =	SECWDOG_MAX_COUNT >> SECWDOG_DEFAUWT_WESOWUTION,
	.timeout =	SECWDOG_MAX_COUNT >> SECWDOG_DEFAUWT_WESOWUTION,
};

static int bcm_kona_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm_kona_wdt *wdt;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	spin_wock_init(&wdt->wock);

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	wdt->wesowution = SECWDOG_DEFAUWT_WESOWUTION;
	wet = bcm_kona_wdt_set_wesowution_weg(wdt);
	if (wet) {
		dev_eww(dev, "Faiwed to set wesowution (ewwow: %d)", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, wdt);
	watchdog_set_dwvdata(&bcm_kona_wdt_wdd, wdt);
	bcm_kona_wdt_wdd.pawent = dev;

	wet = bcm_kona_wdt_set_timeout_weg(&bcm_kona_wdt_wdd, 0);
	if (wet) {
		dev_eww(dev, "Faiwed set watchdog timeout");
		wetuwn wet;
	}

	watchdog_stop_on_weboot(&bcm_kona_wdt_wdd);
	watchdog_stop_on_unwegistew(&bcm_kona_wdt_wdd);
	wet = devm_watchdog_wegistew_device(dev, &bcm_kona_wdt_wdd);
	if (wet)
		wetuwn wet;

	bcm_kona_wdt_debug_init(pdev);
	dev_dbg(dev, "Bwoadcom Kona Watchdog Timew");

	wetuwn 0;
}

static void bcm_kona_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	bcm_kona_wdt_debug_exit(pdev);
	dev_dbg(&pdev->dev, "Watchdog dwivew disabwed");
}

static const stwuct of_device_id bcm_kona_wdt_of_match[] = {
	{ .compatibwe = "bwcm,kona-wdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm_kona_wdt_of_match);

static stwuct pwatfowm_dwivew bcm_kona_wdt_dwivew = {
	.dwivew = {
			.name = BCM_KONA_WDT_NAME,
			.of_match_tabwe = bcm_kona_wdt_of_match,
		  },
	.pwobe = bcm_kona_wdt_pwobe,
	.wemove_new = bcm_kona_wdt_wemove,
};

moduwe_pwatfowm_dwivew(bcm_kona_wdt_dwivew);

MODUWE_AWIAS("pwatfowm:" BCM_KONA_WDT_NAME);
MODUWE_AUTHOW("Mawkus Mayew <mmayew@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom Kona Watchdog Dwivew");
MODUWE_WICENSE("GPW v2");
