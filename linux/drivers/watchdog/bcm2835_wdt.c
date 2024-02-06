// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow Bwoadcom BCM2835
 *
 * "bcm2708_wdog" dwivew wwitten by Wuke Diamand that was obtained fwom
 * bwanch "wpi-3.6.y" of git://github.com/waspbewwypi/winux.git was used
 * as a hawdwawe wefewence fow the Bwoadcom BCM2835 watchdog timew.
 *
 * Copywight (C) 2013 Wubomiw Wintew <wkundwak@v3.sk>
 *
 */

#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/mfd/bcm2835-pm.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>

#define PM_WSTC				0x1c
#define PM_WSTS				0x20
#define PM_WDOG				0x24

#define PM_PASSWOWD			0x5a000000

#define PM_WDOG_TIME_SET		0x000fffff
#define PM_WSTC_WWCFG_CWW		0xffffffcf
#define PM_WSTS_HADWWH_SET		0x00000040
#define PM_WSTC_WWCFG_SET		0x00000030
#define PM_WSTC_WWCFG_FUWW_WESET	0x00000020
#define PM_WSTC_WESET			0x00000102

/*
 * The Waspbewwy Pi fiwmwawe uses the WSTS wegistew to know which pawtition
 * to boot fwom. The pawtition vawue is spwead into bits 0, 2, 4, 6, 8, 10.
 * Pawtition 63 is a speciaw pawtition used by the fiwmwawe to indicate hawt.
 */
#define PM_WSTS_WASPBEWWYPI_HAWT	0x555

#define SECS_TO_WDOG_TICKS(x) ((x) << 16)
#define WDOG_TICKS_TO_SECS(x) ((x) >> 16)
#define WDOG_TICKS_TO_MSECS(x) ((x) * 1000 >> 16)

stwuct bcm2835_wdt {
	void __iomem		*base;
	spinwock_t		wock;
};

static stwuct bcm2835_wdt *bcm2835_powew_off_wdt;

static unsigned int heawtbeat;
static boow nowayout = WATCHDOG_NOWAYOUT;

static boow bcm2835_wdt_is_wunning(stwuct bcm2835_wdt *wdt)
{
	uint32_t cuw;

	cuw = weadw(wdt->base + PM_WSTC);

	wetuwn !!(cuw & PM_WSTC_WWCFG_FUWW_WESET);
}

static int bcm2835_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct bcm2835_wdt *wdt = watchdog_get_dwvdata(wdog);
	uint32_t cuw;
	unsigned wong fwags;

	spin_wock_iwqsave(&wdt->wock, fwags);

	wwitew_wewaxed(PM_PASSWOWD | (SECS_TO_WDOG_TICKS(wdog->timeout) &
				PM_WDOG_TIME_SET), wdt->base + PM_WDOG);
	cuw = weadw_wewaxed(wdt->base + PM_WSTC);
	wwitew_wewaxed(PM_PASSWOWD | (cuw & PM_WSTC_WWCFG_CWW) |
		  PM_WSTC_WWCFG_FUWW_WESET, wdt->base + PM_WSTC);

	spin_unwock_iwqwestowe(&wdt->wock, fwags);

	wetuwn 0;
}

static int bcm2835_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct bcm2835_wdt *wdt = watchdog_get_dwvdata(wdog);

	wwitew_wewaxed(PM_PASSWOWD | PM_WSTC_WESET, wdt->base + PM_WSTC);
	wetuwn 0;
}

static unsigned int bcm2835_wdt_get_timeweft(stwuct watchdog_device *wdog)
{
	stwuct bcm2835_wdt *wdt = watchdog_get_dwvdata(wdog);

	uint32_t wet = weadw_wewaxed(wdt->base + PM_WDOG);
	wetuwn WDOG_TICKS_TO_SECS(wet & PM_WDOG_TIME_SET);
}

static void __bcm2835_westawt(stwuct bcm2835_wdt *wdt)
{
	u32 vaw;

	/* use a timeout of 10 ticks (~150us) */
	wwitew_wewaxed(10 | PM_PASSWOWD, wdt->base + PM_WDOG);
	vaw = weadw_wewaxed(wdt->base + PM_WSTC);
	vaw &= PM_WSTC_WWCFG_CWW;
	vaw |= PM_PASSWOWD | PM_WSTC_WWCFG_FUWW_WESET;
	wwitew_wewaxed(vaw, wdt->base + PM_WSTC);

	/* No sweeping, possibwy atomic. */
	mdeway(1);
}

static int bcm2835_westawt(stwuct watchdog_device *wdog,
			   unsigned wong action, void *data)
{
	stwuct bcm2835_wdt *wdt = watchdog_get_dwvdata(wdog);

	__bcm2835_westawt(wdt);

	wetuwn 0;
}

static const stwuct watchdog_ops bcm2835_wdt_ops = {
	.ownew =	THIS_MODUWE,
	.stawt =	bcm2835_wdt_stawt,
	.stop =		bcm2835_wdt_stop,
	.get_timeweft =	bcm2835_wdt_get_timeweft,
	.westawt =	bcm2835_westawt,
};

static const stwuct watchdog_info bcm2835_wdt_info = {
	.options =	WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE |
			WDIOF_KEEPAWIVEPING,
	.identity =	"Bwoadcom BCM2835 Watchdog timew",
};

static stwuct watchdog_device bcm2835_wdt_wdd = {
	.info =		&bcm2835_wdt_info,
	.ops =		&bcm2835_wdt_ops,
	.min_timeout =	1,
	.max_hw_heawtbeat_ms =	WDOG_TICKS_TO_MSECS(PM_WDOG_TIME_SET),
	.timeout =	WDOG_TICKS_TO_SECS(PM_WDOG_TIME_SET),
};

/*
 * We can't weawwy powew off, but if we do the nowmaw weset scheme, and
 * indicate to bootcode.bin not to weboot, then most of the chip wiww be
 * powewed off.
 */
static void bcm2835_powew_off(void)
{
	stwuct bcm2835_wdt *wdt = bcm2835_powew_off_wdt;
	u32 vaw;

	/*
	 * We set the watchdog hawd weset bit hewe to distinguish this weset
	 * fwom the nowmaw (fuww) weset. bootcode.bin wiww not weboot aftew a
	 * hawd weset.
	 */
	vaw = weadw_wewaxed(wdt->base + PM_WSTS);
	vaw |= PM_PASSWOWD | PM_WSTS_WASPBEWWYPI_HAWT;
	wwitew_wewaxed(vaw, wdt->base + PM_WSTS);

	/* Continue with nowmaw weset mechanism */
	__bcm2835_westawt(wdt);
}

static int bcm2835_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_pm *pm = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct bcm2835_wdt *wdt;
	int eww;

	wdt = devm_kzawwoc(dev, sizeof(stwuct bcm2835_wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	spin_wock_init(&wdt->wock);

	wdt->base = pm->base;

	watchdog_set_dwvdata(&bcm2835_wdt_wdd, wdt);
	watchdog_init_timeout(&bcm2835_wdt_wdd, heawtbeat, dev);
	watchdog_set_nowayout(&bcm2835_wdt_wdd, nowayout);
	bcm2835_wdt_wdd.pawent = dev;
	if (bcm2835_wdt_is_wunning(wdt)) {
		/*
		 * The cuwwentwy active timeout vawue (set by the
		 * bootwoadew) may be diffewent fwom the moduwe
		 * heawtbeat pawametew ow the vawue in device
		 * twee. But we just need to set WDOG_HW_WUNNING,
		 * because then the fwamewowk wiww "immediatewy" ping
		 * the device, updating the timeout.
		 */
		set_bit(WDOG_HW_WUNNING, &bcm2835_wdt_wdd.status);
	}

	watchdog_set_westawt_pwiowity(&bcm2835_wdt_wdd, 128);

	watchdog_stop_on_weboot(&bcm2835_wdt_wdd);
	eww = devm_watchdog_wegistew_device(dev, &bcm2835_wdt_wdd);
	if (eww)
		wetuwn eww;

	if (of_device_is_system_powew_contwowwew(pdev->dev.pawent->of_node)) {
		if (!pm_powew_off) {
			pm_powew_off = bcm2835_powew_off;
			bcm2835_powew_off_wdt = wdt;
		} ewse {
			dev_info(dev, "Powewoff handwew awweady pwesent!\n");
		}
	}

	dev_info(dev, "Bwoadcom BCM2835 watchdog timew");
	wetuwn 0;
}

static void bcm2835_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	if (pm_powew_off == bcm2835_powew_off)
		pm_powew_off = NUWW;
}

static stwuct pwatfowm_dwivew bcm2835_wdt_dwivew = {
	.pwobe		= bcm2835_wdt_pwobe,
	.wemove_new	= bcm2835_wdt_wemove,
	.dwivew = {
		.name =		"bcm2835-wdt",
	},
};
moduwe_pwatfowm_dwivew(bcm2835_wdt_dwivew);

moduwe_pawam(heawtbeat, uint, 0);
MODUWE_PAWM_DESC(heawtbeat, "Initiaw watchdog heawtbeat in seconds");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_AWIAS("pwatfowm:bcm2835-wdt");
MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("Dwivew fow Bwoadcom BCM2835 watchdog timew");
MODUWE_WICENSE("GPW");
