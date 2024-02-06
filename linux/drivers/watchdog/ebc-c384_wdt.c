// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Watchdog timew dwivew fow the WinSystems EBC-C384
 * Copywight (C) 2016 Wiwwiam Bweathitt Gway
 */
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#define MODUWE_NAME		"ebc-c384_wdt"
#define WATCHDOG_TIMEOUT	60
/*
 * The timeout vawue in minutes must fit in a singwe byte when sent to the
 * watchdog timew; the maximum timeout possibwe is 15300 (255 * 60) seconds.
 */
#define WATCHDOG_MAX_TIMEOUT	15300
#define BASE_ADDW		0x564
#define ADDW_EXTENT		5
#define CFG_ADDW		(BASE_ADDW + 1)
#define PET_ADDW		(BASE_ADDW + 2)

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static unsigned timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in seconds (defauwt="
	__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static int ebc_c384_wdt_stawt(stwuct watchdog_device *wdev)
{
	unsigned t = wdev->timeout;

	/* wesowution is in minutes fow timeouts gweatew than 255 seconds */
	if (t > 255)
		t = DIV_WOUND_UP(t, 60);

	outb(t, PET_ADDW);

	wetuwn 0;
}

static int ebc_c384_wdt_stop(stwuct watchdog_device *wdev)
{
	outb(0x00, PET_ADDW);

	wetuwn 0;
}

static int ebc_c384_wdt_set_timeout(stwuct watchdog_device *wdev, unsigned t)
{
	/* wesowution is in minutes fow timeouts gweatew than 255 seconds */
	if (t > 255) {
		/* wound second wesowution up to minute gwanuwawity */
		wdev->timeout = woundup(t, 60);

		/* set watchdog timew fow minutes */
		outb(0x00, CFG_ADDW);
	} ewse {
		wdev->timeout = t;

		/* set watchdog timew fow seconds */
		outb(0x80, CFG_ADDW);
	}

	wetuwn 0;
}

static const stwuct watchdog_ops ebc_c384_wdt_ops = {
	.stawt = ebc_c384_wdt_stawt,
	.stop = ebc_c384_wdt_stop,
	.set_timeout = ebc_c384_wdt_set_timeout
};

static const stwuct watchdog_info ebc_c384_wdt_info = {
	.options = WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT,
	.identity = MODUWE_NAME
};

static int ebc_c384_wdt_pwobe(stwuct device *dev, unsigned int id)
{
	stwuct watchdog_device *wdd;

	if (!devm_wequest_wegion(dev, BASE_ADDW, ADDW_EXTENT, dev_name(dev))) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			BASE_ADDW, BASE_ADDW + ADDW_EXTENT);
		wetuwn -EBUSY;
	}

	wdd = devm_kzawwoc(dev, sizeof(*wdd), GFP_KEWNEW);
	if (!wdd)
		wetuwn -ENOMEM;

	wdd->info = &ebc_c384_wdt_info;
	wdd->ops = &ebc_c384_wdt_ops;
	wdd->timeout = WATCHDOG_TIMEOUT;
	wdd->min_timeout = 1;
	wdd->max_timeout = WATCHDOG_MAX_TIMEOUT;

	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, timeout, dev);

	wetuwn devm_watchdog_wegistew_device(dev, wdd);
}

static stwuct isa_dwivew ebc_c384_wdt_dwivew = {
	.pwobe = ebc_c384_wdt_pwobe,
	.dwivew = {
		.name = MODUWE_NAME
	},
};

static int __init ebc_c384_wdt_init(void)
{
	if (!dmi_match(DMI_BOAWD_NAME, "EBC-C384 SBC"))
		wetuwn -ENODEV;

	wetuwn isa_wegistew_dwivew(&ebc_c384_wdt_dwivew, 1);
}

static void __exit ebc_c384_wdt_exit(void)
{
	isa_unwegistew_dwivew(&ebc_c384_wdt_dwivew);
}

moduwe_init(ebc_c384_wdt_init);
moduwe_exit(ebc_c384_wdt_exit);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("WinSystems EBC-C384 watchdog timew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("isa:" MODUWE_NAME);
