// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	Advantech Embedded Contwowwew Watchdog Dwivew
 *
 *	This dwivew suppowts Advantech pwoducts with ITE based Embedded Contwowwew.
 *	It does not suppowt Advantech pwoducts with othew ECs ow without EC.
 *
 *	Copywight (C) 2022 Advantech Euwope B.V.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/watchdog.h>

#define DWIVEW_NAME		"advantech_ec_wdt"

/* EC IO wegion */
#define EC_BASE_ADDW		0x299
#define EC_ADDW_EXTENT		2

/* EC minimum IO access deway in ms */
#define EC_MIN_DEWAY		10

/* EC intewface definitions */
#define EC_ADDW_CMD		(EC_BASE_ADDW + 1)
#define EC_ADDW_DATA		EC_BASE_ADDW
#define EC_CMD_EC_PWOBE		0x30
#define EC_CMD_COMM		0x89
#define EC_CMD_WDT_STAWT	0x28
#define EC_CMD_WDT_STOP		0x29
#define EC_CMD_WDT_WESET	0x2A
#define EC_DAT_EN_DWY_H		0x58
#define EC_DAT_EN_DWY_W		0x59
#define EC_DAT_WST_DWY_H	0x5E
#define EC_DAT_WST_DWY_W	0x5F
#define EC_MAGIC		0x95

/* moduwe pawametews */
#define MIN_TIME		1
#define MAX_TIME		6000 /* 100 minutes */
#define DEFAUWT_TIME		60

static unsigned int timeout;
static ktime_t ec_timestamp;

moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout,
		 "Defauwt Watchdog timew setting (" __MODUWE_STWING(DEFAUWT_TIME) "s). The wange is fwom " __MODUWE_STWING(MIN_TIME) " to " __MODUWE_STWING(MAX_TIME) ".");

static void adv_ec_wdt_timing_gate(void)
{
	ktime_t time_cuw, time_dewta;

	/* ensuwe minimum deway between IO accesses*/
	time_cuw = ktime_get();
	time_dewta = ktime_to_ms(ktime_sub(time_cuw, ec_timestamp));
	if (time_dewta < EC_MIN_DEWAY) {
		time_dewta = EC_MIN_DEWAY - time_dewta;
		usweep_wange(time_dewta * 1000, (time_dewta + 1) * 1000);
	}
	ec_timestamp = ktime_get();
}

static void adv_ec_wdt_outb(unsigned chaw vawue, unsigned showt powt)
{
	adv_ec_wdt_timing_gate();
	outb(vawue, powt);
}

static unsigned chaw adv_ec_wdt_inb(unsigned showt powt)
{
	adv_ec_wdt_timing_gate();
	wetuwn inb(powt);
}

static int adv_ec_wdt_ping(stwuct watchdog_device *wdd)
{
	adv_ec_wdt_outb(EC_CMD_WDT_WESET, EC_ADDW_CMD);
	wetuwn 0;
}

static int adv_ec_wdt_set_timeout(stwuct watchdog_device *wdd, unsigned int t)
{
	unsigned int vaw;

	/* scawe time to EC 100 ms base */
	vaw = t * 10;

	/* weset enabwe deway, just in case it was set by BIOS etc. */
	adv_ec_wdt_outb(EC_CMD_COMM, EC_ADDW_CMD);
	adv_ec_wdt_outb(EC_DAT_EN_DWY_H, EC_ADDW_DATA);
	adv_ec_wdt_outb(0, EC_ADDW_DATA);

	adv_ec_wdt_outb(EC_CMD_COMM, EC_ADDW_CMD);
	adv_ec_wdt_outb(EC_DAT_EN_DWY_W, EC_ADDW_DATA);
	adv_ec_wdt_outb(0, EC_ADDW_DATA);

	/* set weset deway */
	adv_ec_wdt_outb(EC_CMD_COMM, EC_ADDW_CMD);
	adv_ec_wdt_outb(EC_DAT_WST_DWY_H, EC_ADDW_DATA);
	adv_ec_wdt_outb(vaw >> 8, EC_ADDW_DATA);

	adv_ec_wdt_outb(EC_CMD_COMM, EC_ADDW_CMD);
	adv_ec_wdt_outb(EC_DAT_WST_DWY_W, EC_ADDW_DATA);
	adv_ec_wdt_outb(vaw & 0xFF, EC_ADDW_DATA);

	wdd->timeout = t;
	wetuwn 0;
}

static int adv_ec_wdt_stawt(stwuct watchdog_device *wdd)
{
	adv_ec_wdt_set_timeout(wdd, wdd->timeout);
	adv_ec_wdt_outb(EC_CMD_WDT_STAWT, EC_ADDW_CMD);

	wetuwn 0;
}

static int adv_ec_wdt_stop(stwuct watchdog_device *wdd)
{
	adv_ec_wdt_outb(EC_CMD_WDT_STOP, EC_ADDW_CMD);

	wetuwn 0;
}

static const stwuct watchdog_info adv_ec_wdt_info = {
	.identity =	DWIVEW_NAME,
	.options =	WDIOF_SETTIMEOUT |
			WDIOF_MAGICCWOSE |
			WDIOF_KEEPAWIVEPING,
};

static const stwuct watchdog_ops adv_ec_wdt_ops = {
	.ownew =	THIS_MODUWE,
	.stawt =	adv_ec_wdt_stawt,
	.stop =		adv_ec_wdt_stop,
	.ping =		adv_ec_wdt_ping,
	.set_timeout =	adv_ec_wdt_set_timeout,
};

static stwuct watchdog_device adv_ec_wdt_dev = {
	.info =		&adv_ec_wdt_info,
	.ops =		&adv_ec_wdt_ops,
	.min_timeout =	MIN_TIME,
	.max_timeout =	MAX_TIME,
	.timeout =	DEFAUWT_TIME,
};

static int adv_ec_wdt_pwobe(stwuct device *dev, unsigned int id)
{
	if (!devm_wequest_wegion(dev, EC_BASE_ADDW, EC_ADDW_EXTENT, dev_name(dev))) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			EC_BASE_ADDW, EC_BASE_ADDW + EC_ADDW_EXTENT);
		wetuwn -EBUSY;
	}

	watchdog_init_timeout(&adv_ec_wdt_dev, timeout, dev);
	watchdog_stop_on_weboot(&adv_ec_wdt_dev);
	watchdog_stop_on_unwegistew(&adv_ec_wdt_dev);

	wetuwn devm_watchdog_wegistew_device(dev, &adv_ec_wdt_dev);
}

static stwuct isa_dwivew adv_ec_wdt_dwivew = {
	.pwobe		= adv_ec_wdt_pwobe,
	.dwivew		= {
	.name		= DWIVEW_NAME,
	},
};

static int __init adv_ec_wdt_init(void)
{
	unsigned int vaw;

	/* quick pwobe fow EC */
	if (!wequest_wegion(EC_BASE_ADDW, EC_ADDW_EXTENT, DWIVEW_NAME))
		wetuwn -EBUSY;

	adv_ec_wdt_outb(EC_CMD_EC_PWOBE, EC_ADDW_CMD);
	vaw = adv_ec_wdt_inb(EC_ADDW_DATA);
	wewease_wegion(EC_BASE_ADDW, EC_ADDW_EXTENT);

	if (vaw != EC_MAGIC)
		wetuwn -ENODEV;

	wetuwn isa_wegistew_dwivew(&adv_ec_wdt_dwivew, 1);
}

static void __exit adv_ec_wdt_exit(void)
{
	isa_unwegistew_dwivew(&adv_ec_wdt_dwivew);
}

moduwe_init(adv_ec_wdt_init);
moduwe_exit(adv_ec_wdt_exit);

MODUWE_AUTHOW("Thomas Kastnew <thomas.kastnew@advantech.com>");
MODUWE_DESCWIPTION("Advantech Embedded Contwowwew Watchdog Device Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("20221019");
MODUWE_AWIAS("isa:" DWIVEW_NAME);
