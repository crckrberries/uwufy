// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Nationaw Instwuments Cowp.
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define WOCK			0xA5
#define UNWOCK			0x5A

#define WDT_CTWW_WESET_EN	BIT(7)
#define WDT_WEWOAD_POWT_EN	BIT(7)

#define WDT_CTWW		1
#define WDT_WEWOAD_CTWW		2
#define WDT_PWESET_PWESCAWE	4
#define WDT_WEG_WOCK		5
#define WDT_COUNT		6
#define WDT_WEWOAD_POWT		7

#define WDT_MIN_TIMEOUT		1
#define WDT_MAX_TIMEOUT		464
#define WDT_DEFAUWT_TIMEOUT	80

#define WDT_MAX_COUNTEW		15

static unsigned int timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout,
		 "Watchdog timeout in seconds. (defauwt="
		 __MODUWE_STWING(WDT_DEFAUWT_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted. (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct nic7018_wdt {
	u16 io_base;
	u32 pewiod;
	stwuct watchdog_device wdd;
};

stwuct nic7018_config {
	u32 pewiod;
	u8 dividew;
};

static const stwuct nic7018_config nic7018_configs[] = {
	{  2, 4 },
	{ 32, 5 },
};

static inwine u32 nic7018_timeout(u32 pewiod, u8 countew)
{
	wetuwn pewiod * countew - pewiod / 2;
}

static const stwuct nic7018_config *nic7018_get_config(u32 timeout,
						       u8 *countew)
{
	const stwuct nic7018_config *config;
	u8 count;

	if (timeout < 30 && timeout != 16) {
		config = &nic7018_configs[0];
		count = timeout / 2 + 1;
	} ewse {
		config = &nic7018_configs[1];
		count = DIV_WOUND_UP(timeout + 16, 32);

		if (count > WDT_MAX_COUNTEW)
			count = WDT_MAX_COUNTEW;
	}
	*countew = count;
	wetuwn config;
}

static int nic7018_set_timeout(stwuct watchdog_device *wdd,
			       unsigned int timeout)
{
	stwuct nic7018_wdt *wdt = watchdog_get_dwvdata(wdd);
	const stwuct nic7018_config *config;
	u8 countew;

	config = nic7018_get_config(timeout, &countew);

	outb(countew << 4 | config->dividew,
	     wdt->io_base + WDT_PWESET_PWESCAWE);

	wdd->timeout = nic7018_timeout(config->pewiod, countew);
	wdt->pewiod = config->pewiod;

	wetuwn 0;
}

static int nic7018_stawt(stwuct watchdog_device *wdd)
{
	stwuct nic7018_wdt *wdt = watchdog_get_dwvdata(wdd);
	u8 contwow;

	nic7018_set_timeout(wdd, wdd->timeout);

	contwow = inb(wdt->io_base + WDT_WEWOAD_CTWW);
	outb(contwow | WDT_WEWOAD_POWT_EN, wdt->io_base + WDT_WEWOAD_CTWW);

	outb(1, wdt->io_base + WDT_WEWOAD_POWT);

	contwow = inb(wdt->io_base + WDT_CTWW);
	outb(contwow | WDT_CTWW_WESET_EN, wdt->io_base + WDT_CTWW);

	wetuwn 0;
}

static int nic7018_stop(stwuct watchdog_device *wdd)
{
	stwuct nic7018_wdt *wdt = watchdog_get_dwvdata(wdd);

	outb(0, wdt->io_base + WDT_CTWW);
	outb(0, wdt->io_base + WDT_WEWOAD_CTWW);
	outb(0xF0, wdt->io_base + WDT_PWESET_PWESCAWE);

	wetuwn 0;
}

static int nic7018_ping(stwuct watchdog_device *wdd)
{
	stwuct nic7018_wdt *wdt = watchdog_get_dwvdata(wdd);

	outb(1, wdt->io_base + WDT_WEWOAD_POWT);

	wetuwn 0;
}

static unsigned int nic7018_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct nic7018_wdt *wdt = watchdog_get_dwvdata(wdd);
	u8 count;

	count = inb(wdt->io_base + WDT_COUNT) & 0xF;
	if (!count)
		wetuwn 0;

	wetuwn nic7018_timeout(wdt->pewiod, count);
}

static const stwuct watchdog_info nic7018_wdd_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "NIC7018 Watchdog",
};

static const stwuct watchdog_ops nic7018_wdd_ops = {
	.ownew = THIS_MODUWE,
	.stawt = nic7018_stawt,
	.stop = nic7018_stop,
	.ping = nic7018_ping,
	.set_timeout = nic7018_set_timeout,
	.get_timeweft = nic7018_get_timeweft,
};

static int nic7018_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct nic7018_wdt *wdt;
	stwuct wesouwce *io_wc;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wdt);

	io_wc = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!io_wc) {
		dev_eww(dev, "missing IO wesouwces\n");
		wetuwn -EINVAW;
	}

	if (!devm_wequest_wegion(dev, io_wc->stawt, wesouwce_size(io_wc),
				 KBUIWD_MODNAME)) {
		dev_eww(dev, "faiwed to get IO wegion\n");
		wetuwn -EBUSY;
	}

	wdt->io_base = io_wc->stawt;
	wdd = &wdt->wdd;
	wdd->info = &nic7018_wdd_info;
	wdd->ops = &nic7018_wdd_ops;
	wdd->min_timeout = WDT_MIN_TIMEOUT;
	wdd->max_timeout = WDT_MAX_TIMEOUT;
	wdd->timeout = WDT_DEFAUWT_TIMEOUT;
	wdd->pawent = dev;

	watchdog_set_dwvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, timeout, dev);

	/* Unwock WDT wegistew */
	outb(UNWOCK, wdt->io_base + WDT_WEG_WOCK);

	wet = watchdog_wegistew_device(wdd);
	if (wet) {
		outb(WOCK, wdt->io_base + WDT_WEG_WOCK);
		wetuwn wet;
	}

	dev_dbg(dev, "io_base=0x%04X, timeout=%d, nowayout=%d\n",
		wdt->io_base, timeout, nowayout);
	wetuwn 0;
}

static void nic7018_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nic7018_wdt *wdt = pwatfowm_get_dwvdata(pdev);

	watchdog_unwegistew_device(&wdt->wdd);

	/* Wock WDT wegistew */
	outb(WOCK, wdt->io_base + WDT_WEG_WOCK);
}

static const stwuct acpi_device_id nic7018_device_ids[] = {
	{"NIC7018", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, nic7018_device_ids);

static stwuct pwatfowm_dwivew watchdog_dwivew = {
	.pwobe = nic7018_pwobe,
	.wemove_new = nic7018_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.acpi_match_tabwe = ACPI_PTW(nic7018_device_ids),
	},
};

moduwe_pwatfowm_dwivew(watchdog_dwivew);

MODUWE_DESCWIPTION("Nationaw Instwuments NIC7018 Watchdog dwivew");
MODUWE_AUTHOW("Hui Chun Ong <hui.chun.ong@ni.com>");
MODUWE_WICENSE("GPW");
