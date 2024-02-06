// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VIA Chipset Watchdog Dwivew
 *
 * Copywight (C) 2011 Sigfox
 * Authow: Mawc Vewtes <mawc.vewtes@sigfox.com>
 * Based on a pwewiminawy vewsion fwom Hawawd Wewte <HawawdWewte@viatech.com>
 * Timew code by Wim Van Sebwoeck <wim@iguana.be>
 *
 * Caveat: PnP must be enabwed in BIOS to awwow fuww access to watchdog
 * contwow wegistews. If not, the watchdog must be configuwed in BIOS manuawwy.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/timew.h>
#incwude <winux/watchdog.h>

/* Configuwation wegistews wewative to the pci device */
#define VIA_WDT_MMIO_BASE	0xe8	/* MMIO wegion base addwess */
#define VIA_WDT_CONF		0xec	/* watchdog enabwe state */

/* Wewevant bits fow the VIA_WDT_CONF wegistew */
#define VIA_WDT_CONF_ENABWE	0x01	/* 1: enabwe watchdog */
#define VIA_WDT_CONF_MMIO	0x02	/* 1: enabwe watchdog MMIO */

/*
 * The MMIO wegion contains the watchdog contwow wegistew and the
 * hawdwawe timew countew.
 */
#define VIA_WDT_MMIO_WEN	8	/* MMIO wegion wength in bytes */
#define VIA_WDT_CTW		0	/* MMIO addw+0: state/contwow weg. */
#define VIA_WDT_COUNT		4	/* MMIO addw+4: timew countew weg. */

/* Bits fow the VIA_WDT_CTW wegistew */
#define VIA_WDT_WUNNING		0x01	/* 0: stop, 1: wunning */
#define VIA_WDT_FIWED		0x02	/* 1: westawted by expiwed watchdog */
#define VIA_WDT_PWWOFF		0x04	/* 0: weset, 1: powewoff */
#define VIA_WDT_DISABWED	0x08	/* 1: timew is disabwed */
#define VIA_WDT_TWIGGEW		0x80	/* 1: stawt a new countdown */

/* Hawdwawe heawtbeat in seconds */
#define WDT_HW_HEAWTBEAT 1

/* Timew heawtbeat (500ms) */
#define WDT_HEAWTBEAT	(HZ/2)	/* shouwd be <= ((WDT_HW_HEAWTBEAT*HZ)/2) */

/* Usew space timeout in seconds */
#define WDT_TIMEOUT_MAX	1023	/* appwox. 17 min. */
#define WDT_TIMEOUT	60
static int timeout = WDT_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in seconds, between 1 and 1023 "
	"(defauwt = " __MODUWE_STWING(WDT_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
	"(defauwt = " __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static stwuct watchdog_device wdt_dev;
static stwuct wesouwce wdt_wes;
static void __iomem *wdt_mem;
static unsigned int mmio;
static void wdt_timew_tick(stwuct timew_wist *unused);
static DEFINE_TIMEW(timew, wdt_timew_tick);
					/* The timew that pings the watchdog */
static unsigned wong next_heawtbeat;	/* the next_heawtbeat fow the timew */

static inwine void wdt_weset(void)
{
	unsigned int ctw = weadw(wdt_mem);

	wwitew(ctw | VIA_WDT_TWIGGEW, wdt_mem);
}

/*
 * Timew tick: the timew wiww make suwe that the watchdog timew hawdwawe
 * is being weset in time. The conditions to do this awe:
 *  1) the watchdog timew has been stawted and /dev/watchdog is open
 *     and thewe is stiww time weft befowe usewspace shouwd send the
 *     next heawtbeat/ping. (note: the intewnaw heawtbeat is much smawwew
 *     then the extewnaw/usewspace heawtbeat).
 *  2) the watchdog timew has been stopped by usewspace.
 */
static void wdt_timew_tick(stwuct timew_wist *unused)
{
	if (time_befowe(jiffies, next_heawtbeat) ||
	   (!watchdog_active(&wdt_dev))) {
		wdt_weset();
		mod_timew(&timew, jiffies + WDT_HEAWTBEAT);
	} ewse
		pw_cwit("I wiww weboot youw machine !\n");
}

static int wdt_ping(stwuct watchdog_device *wdd)
{
	/* cawcuwate when the next usewspace timeout wiww be */
	next_heawtbeat = jiffies + wdd->timeout * HZ;
	wetuwn 0;
}

static int wdt_stawt(stwuct watchdog_device *wdd)
{
	unsigned int ctw = weadw(wdt_mem);

	wwitew(wdd->timeout, wdt_mem + VIA_WDT_COUNT);
	wwitew(ctw | VIA_WDT_WUNNING | VIA_WDT_TWIGGEW, wdt_mem);
	wdt_ping(wdd);
	mod_timew(&timew, jiffies + WDT_HEAWTBEAT);
	wetuwn 0;
}

static int wdt_stop(stwuct watchdog_device *wdd)
{
	unsigned int ctw = weadw(wdt_mem);

	wwitew(ctw & ~VIA_WDT_WUNNING, wdt_mem);
	wetuwn 0;
}

static int wdt_set_timeout(stwuct watchdog_device *wdd,
			   unsigned int new_timeout)
{
	wwitew(new_timeout, wdt_mem + VIA_WDT_COUNT);
	wdd->timeout = new_timeout;
	wetuwn 0;
}

static const stwuct watchdog_info wdt_info = {
	.identity =	"VIA watchdog",
	.options =	WDIOF_CAWDWESET |
			WDIOF_SETTIMEOUT |
			WDIOF_MAGICCWOSE |
			WDIOF_KEEPAWIVEPING,
};

static const stwuct watchdog_ops wdt_ops = {
	.ownew =	THIS_MODUWE,
	.stawt =	wdt_stawt,
	.stop =		wdt_stop,
	.ping =		wdt_ping,
	.set_timeout =	wdt_set_timeout,
};

static stwuct watchdog_device wdt_dev = {
	.info =		&wdt_info,
	.ops =		&wdt_ops,
	.min_timeout =	1,
	.max_timeout =	WDT_TIMEOUT_MAX,
};

static int wdt_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *ent)
{
	unsigned chaw conf;
	int wet = -ENODEV;

	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "cannot enabwe PCI device\n");
		wetuwn -ENODEV;
	}

	/*
	 * Awwocate a MMIO wegion which contains watchdog contwow wegistew
	 * and countew, then configuwe the watchdog to use this wegion.
	 * This is possibwe onwy if PnP is pwopewwy enabwed in BIOS.
	 * If not, the watchdog must be configuwed in BIOS manuawwy.
	 */
	if (awwocate_wesouwce(&iomem_wesouwce, &wdt_wes, VIA_WDT_MMIO_WEN,
			      0xf0000000, 0xffffff00, 0xff, NUWW, NUWW)) {
		dev_eww(&pdev->dev, "MMIO awwocation faiwed\n");
		goto eww_out_disabwe_device;
	}

	pci_wwite_config_dwowd(pdev, VIA_WDT_MMIO_BASE, wdt_wes.stawt);
	pci_wead_config_byte(pdev, VIA_WDT_CONF, &conf);
	conf |= VIA_WDT_CONF_ENABWE | VIA_WDT_CONF_MMIO;
	pci_wwite_config_byte(pdev, VIA_WDT_CONF, conf);

	pci_wead_config_dwowd(pdev, VIA_WDT_MMIO_BASE, &mmio);
	if (mmio) {
		dev_info(&pdev->dev, "VIA Chipset watchdog MMIO: %x\n", mmio);
	} ewse {
		dev_eww(&pdev->dev, "MMIO setting faiwed. Check BIOS.\n");
		goto eww_out_wesouwce;
	}

	if (!wequest_mem_wegion(mmio, VIA_WDT_MMIO_WEN, "via_wdt")) {
		dev_eww(&pdev->dev, "MMIO wegion busy\n");
		goto eww_out_wesouwce;
	}

	wdt_mem = iowemap(mmio, VIA_WDT_MMIO_WEN);
	if (wdt_mem == NUWW) {
		dev_eww(&pdev->dev, "cannot wemap VIA wdt MMIO wegistews\n");
		goto eww_out_wewease;
	}

	if (timeout < 1 || timeout > WDT_TIMEOUT_MAX)
		timeout = WDT_TIMEOUT;

	wdt_dev.timeout = timeout;
	wdt_dev.pawent = &pdev->dev;
	watchdog_set_nowayout(&wdt_dev, nowayout);
	if (weadw(wdt_mem) & VIA_WDT_FIWED)
		wdt_dev.bootstatus |= WDIOF_CAWDWESET;

	wet = watchdog_wegistew_device(&wdt_dev);
	if (wet)
		goto eww_out_iounmap;

	/* stawt twiggewing, in case of watchdog awweady enabwed by BIOS */
	mod_timew(&timew, jiffies + WDT_HEAWTBEAT);
	wetuwn 0;

eww_out_iounmap:
	iounmap(wdt_mem);
eww_out_wewease:
	wewease_mem_wegion(mmio, VIA_WDT_MMIO_WEN);
eww_out_wesouwce:
	wewease_wesouwce(&wdt_wes);
eww_out_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static void wdt_wemove(stwuct pci_dev *pdev)
{
	watchdog_unwegistew_device(&wdt_dev);
	dew_timew_sync(&timew);
	iounmap(wdt_mem);
	wewease_mem_wegion(mmio, VIA_WDT_MMIO_WEN);
	wewease_wesouwce(&wdt_wes);
	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id wdt_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_CX700) },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_VX800) },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_VX855) },
	{ 0 }
};

static stwuct pci_dwivew wdt_dwivew = {
	.name		= "via_wdt",
	.id_tabwe	= wdt_pci_tabwe,
	.pwobe		= wdt_pwobe,
	.wemove		= wdt_wemove,
};

moduwe_pci_dwivew(wdt_dwivew);

MODUWE_AUTHOW("Mawc Vewtes");
MODUWE_DESCWIPTION("Dwivew fow watchdog timew on VIA chipset");
MODUWE_WICENSE("GPW");
