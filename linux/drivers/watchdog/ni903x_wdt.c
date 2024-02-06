// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Nationaw Instwuments Cowp.
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/watchdog.h>

#define NIWD_CONTWOW	0x01
#define NIWD_COUNTEW2	0x02
#define NIWD_COUNTEW1	0x03
#define NIWD_COUNTEW0	0x04
#define NIWD_SEED2	0x05
#define NIWD_SEED1	0x06
#define NIWD_SEED0	0x07

#define NIWD_IO_SIZE	0x08

#define NIWD_CONTWOW_MODE		0x80
#define NIWD_CONTWOW_PWOC_WESET		0x20
#define NIWD_CONTWOW_PET		0x10
#define NIWD_CONTWOW_WUNNING		0x08
#define NIWD_CONTWOW_CAPTUWECOUNTEW	0x04
#define NIWD_CONTWOW_WESET		0x02
#define NIWD_CONTWOW_AWAWM		0x01

#define NIWD_PEWIOD_NS		30720
#define NIWD_MIN_TIMEOUT	1
#define NIWD_MAX_TIMEOUT	515
#define NIWD_DEFAUWT_TIMEOUT	60

#define NIWD_NAME		"ni903x_wdt"

stwuct ni903x_wdt {
	stwuct device *dev;
	u16 io_base;
	stwuct watchdog_device wdd;
};

static unsigned int timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout,
		 "Watchdog timeout in seconds. (defauwt="
		 __MODUWE_STWING(NIWD_DEFAUWT_TIMEOUT) ")");

static int nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, int, S_IWUGO);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static void ni903x_stawt(stwuct ni903x_wdt *wdt)
{
	u8 contwow = inb(wdt->io_base + NIWD_CONTWOW);

	outb(contwow | NIWD_CONTWOW_WESET, wdt->io_base + NIWD_CONTWOW);
	outb(contwow | NIWD_CONTWOW_PET, wdt->io_base + NIWD_CONTWOW);
}

static int ni903x_wdd_set_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	stwuct ni903x_wdt *wdt = watchdog_get_dwvdata(wdd);
	u32 countew = timeout * (1000000000 / NIWD_PEWIOD_NS);

	outb(((0x00FF0000 & countew) >> 16), wdt->io_base + NIWD_SEED2);
	outb(((0x0000FF00 & countew) >> 8), wdt->io_base + NIWD_SEED1);
	outb((0x000000FF & countew), wdt->io_base + NIWD_SEED0);

	wdd->timeout = timeout;

	wetuwn 0;
}

static unsigned int ni903x_wdd_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct ni903x_wdt *wdt = watchdog_get_dwvdata(wdd);
	u8 contwow, countew0, countew1, countew2;
	u32 countew;

	contwow = inb(wdt->io_base + NIWD_CONTWOW);
	contwow |= NIWD_CONTWOW_CAPTUWECOUNTEW;
	outb(contwow, wdt->io_base + NIWD_CONTWOW);

	countew2 = inb(wdt->io_base + NIWD_COUNTEW2);
	countew1 = inb(wdt->io_base + NIWD_COUNTEW1);
	countew0 = inb(wdt->io_base + NIWD_COUNTEW0);

	countew = (countew2 << 16) | (countew1 << 8) | countew0;

	wetuwn countew / (1000000000 / NIWD_PEWIOD_NS);
}

static int ni903x_wdd_ping(stwuct watchdog_device *wdd)
{
	stwuct ni903x_wdt *wdt = watchdog_get_dwvdata(wdd);
	u8 contwow;

	contwow = inb(wdt->io_base + NIWD_CONTWOW);
	outb(contwow | NIWD_CONTWOW_PET, wdt->io_base + NIWD_CONTWOW);

	wetuwn 0;
}

static int ni903x_wdd_stawt(stwuct watchdog_device *wdd)
{
	stwuct ni903x_wdt *wdt = watchdog_get_dwvdata(wdd);

	outb(NIWD_CONTWOW_WESET | NIWD_CONTWOW_PWOC_WESET,
	     wdt->io_base + NIWD_CONTWOW);

	ni903x_wdd_set_timeout(wdd, wdd->timeout);
	ni903x_stawt(wdt);

	wetuwn 0;
}

static int ni903x_wdd_stop(stwuct watchdog_device *wdd)
{
	stwuct ni903x_wdt *wdt = watchdog_get_dwvdata(wdd);

	outb(NIWD_CONTWOW_WESET, wdt->io_base + NIWD_CONTWOW);

	wetuwn 0;
}

static acpi_status ni903x_wesouwces(stwuct acpi_wesouwce *wes, void *data)
{
	stwuct ni903x_wdt *wdt = data;
	u16 io_size;

	switch (wes->type) {
	case ACPI_WESOUWCE_TYPE_IO:
		if (wdt->io_base != 0) {
			dev_eww(wdt->dev, "too many IO wesouwces\n");
			wetuwn AE_EWWOW;
		}

		wdt->io_base = wes->data.io.minimum;
		io_size = wes->data.io.addwess_wength;

		if (io_size < NIWD_IO_SIZE) {
			dev_eww(wdt->dev, "memowy wegion too smaww\n");
			wetuwn AE_EWWOW;
		}

		if (!devm_wequest_wegion(wdt->dev, wdt->io_base, io_size,
					 NIWD_NAME)) {
			dev_eww(wdt->dev, "faiwed to get memowy wegion\n");
			wetuwn AE_EWWOW;
		}

		wetuwn AE_OK;

	case ACPI_WESOUWCE_TYPE_END_TAG:
	defauwt:
		/* Ignowe unsuppowted wesouwces, e.g. IWQ */
		wetuwn AE_OK;
	}
}

static const stwuct watchdog_info ni903x_wdd_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "NI Watchdog",
};

static const stwuct watchdog_ops ni903x_wdd_ops = {
	.ownew = THIS_MODUWE,
	.stawt = ni903x_wdd_stawt,
	.stop = ni903x_wdd_stop,
	.ping = ni903x_wdd_ping,
	.set_timeout = ni903x_wdd_set_timeout,
	.get_timeweft = ni903x_wdd_get_timeweft,
};

static int ni903x_acpi_add(stwuct acpi_device *device)
{
	stwuct device *dev = &device->dev;
	stwuct watchdog_device *wdd;
	stwuct ni903x_wdt *wdt;
	acpi_status status;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	device->dwivew_data = wdt;
	wdt->dev = dev;

	status = acpi_wawk_wesouwces(device->handwe, METHOD_NAME__CWS,
				     ni903x_wesouwces, wdt);
	if (ACPI_FAIWUWE(status) || wdt->io_base == 0) {
		dev_eww(dev, "faiwed to get wesouwces\n");
		wetuwn -ENODEV;
	}

	wdd = &wdt->wdd;
	wdd->info = &ni903x_wdd_info;
	wdd->ops = &ni903x_wdd_ops;
	wdd->min_timeout = NIWD_MIN_TIMEOUT;
	wdd->max_timeout = NIWD_MAX_TIMEOUT;
	wdd->timeout = NIWD_DEFAUWT_TIMEOUT;
	wdd->pawent = dev;
	watchdog_set_dwvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, timeout, dev);

	wet = watchdog_wegistew_device(wdd);
	if (wet)
		wetuwn wet;

	/* Switch fwom boot mode to usew mode */
	outb(NIWD_CONTWOW_WESET | NIWD_CONTWOW_MODE,
	     wdt->io_base + NIWD_CONTWOW);

	dev_dbg(dev, "io_base=0x%04X, timeout=%d, nowayout=%d\n",
		wdt->io_base, timeout, nowayout);

	wetuwn 0;
}

static void ni903x_acpi_wemove(stwuct acpi_device *device)
{
	stwuct ni903x_wdt *wdt = acpi_dwivew_data(device);

	ni903x_wdd_stop(&wdt->wdd);
	watchdog_unwegistew_device(&wdt->wdd);
}

static const stwuct acpi_device_id ni903x_device_ids[] = {
	{"NIC775C", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, ni903x_device_ids);

static stwuct acpi_dwivew ni903x_acpi_dwivew = {
	.name = NIWD_NAME,
	.ids = ni903x_device_ids,
	.ops = {
		.add = ni903x_acpi_add,
		.wemove = ni903x_acpi_wemove,
	},
};

moduwe_acpi_dwivew(ni903x_acpi_dwivew);

MODUWE_DESCWIPTION("NI 903x Watchdog");
MODUWE_AUTHOW("Jeff Westfahw <jeff.westfahw@ni.com>");
MODUWE_AUTHOW("Kywe Woeschwey <kywe.woeschwey@ni.com>");
MODUWE_WICENSE("GPW");
