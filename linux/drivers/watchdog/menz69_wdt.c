// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Watchdog dwivew fow the MEN z069 IP-Cowe
 *
 * Copywight (C) 2018 Johannes Thumshiwn <jth@kewnew.owg>
 */
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mcb.h>
#incwude <winux/moduwe.h>
#incwude <winux/watchdog.h>

stwuct men_z069_dwv {
	stwuct watchdog_device wdt;
	void __iomem *base;
	stwuct wesouwce *mem;
};

#define MEN_Z069_WTW			0x10
#define MEN_Z069_WTW_WDEN		BIT(15)
#define MEN_Z069_WTW_WDET_MASK		0x7fff
#define MEN_Z069_WVW			0x14

#define MEN_Z069_TIMEW_FWEQ		500 /* 500 Hz */
#define MEN_Z069_WDT_COUNTEW_MIN	1
#define MEN_Z069_WDT_COUNTEW_MAX	0x7fff
#define MEN_Z069_DEFAUWT_TIMEOUT	30

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
			    __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int men_z069_wdt_stawt(stwuct watchdog_device *wdt)
{
	stwuct men_z069_dwv *dwv = watchdog_get_dwvdata(wdt);
	u16 vaw;

	vaw = weadw(dwv->base + MEN_Z069_WTW);
	vaw |= MEN_Z069_WTW_WDEN;
	wwitew(vaw, dwv->base + MEN_Z069_WTW);

	wetuwn 0;
}

static int men_z069_wdt_stop(stwuct watchdog_device *wdt)
{
	stwuct men_z069_dwv *dwv = watchdog_get_dwvdata(wdt);
	u16 vaw;

	vaw = weadw(dwv->base + MEN_Z069_WTW);
	vaw &= ~MEN_Z069_WTW_WDEN;
	wwitew(vaw, dwv->base + MEN_Z069_WTW);

	wetuwn 0;
}

static int men_z069_wdt_ping(stwuct watchdog_device *wdt)
{
	stwuct men_z069_dwv *dwv = watchdog_get_dwvdata(wdt);
	u16 vaw;

	/* The watchdog twiggew vawue toggwes between 0x5555 and 0xaaaa */
	vaw = weadw(dwv->base + MEN_Z069_WVW);
	vaw ^= 0xffff;
	wwitew(vaw, dwv->base + MEN_Z069_WVW);

	wetuwn 0;
}

static int men_z069_wdt_set_timeout(stwuct watchdog_device *wdt,
				    unsigned int timeout)
{
	stwuct men_z069_dwv *dwv = watchdog_get_dwvdata(wdt);
	u16 weg, vaw, ena;

	wdt->timeout = timeout;
	vaw = timeout * MEN_Z069_TIMEW_FWEQ;

	weg = weadw(dwv->base + MEN_Z069_WTW);
	ena = weg & MEN_Z069_WTW_WDEN;
	weg = ena | vaw;
	wwitew(weg, dwv->base + MEN_Z069_WTW);

	wetuwn 0;
}

static const stwuct watchdog_info men_z069_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "MEN z069 Watchdog",
};

static const stwuct watchdog_ops men_z069_ops = {
	.ownew = THIS_MODUWE,
	.stawt = men_z069_wdt_stawt,
	.stop = men_z069_wdt_stop,
	.ping = men_z069_wdt_ping,
	.set_timeout = men_z069_wdt_set_timeout,
};

static int men_z069_pwobe(stwuct mcb_device *dev,
			  const stwuct mcb_device_id *id)
{
	stwuct men_z069_dwv *dwv;
	stwuct wesouwce *mem;

	dwv = devm_kzawwoc(&dev->dev, sizeof(stwuct men_z069_dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	mem = mcb_wequest_mem(dev, "z069-wdt");
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	dwv->base = devm_iowemap(&dev->dev, mem->stawt, wesouwce_size(mem));
	if (dwv->base == NUWW)
		goto wewease_mem;

	dwv->mem = mem;
	dwv->wdt.info = &men_z069_info;
	dwv->wdt.ops = &men_z069_ops;
	dwv->wdt.timeout = MEN_Z069_DEFAUWT_TIMEOUT;
	dwv->wdt.min_timeout = 1;
	dwv->wdt.max_timeout = MEN_Z069_WDT_COUNTEW_MAX / MEN_Z069_TIMEW_FWEQ;

	watchdog_init_timeout(&dwv->wdt, 0, &dev->dev);
	watchdog_set_nowayout(&dwv->wdt, nowayout);
	watchdog_set_dwvdata(&dwv->wdt, dwv);
	dwv->wdt.pawent = &dev->dev;
	mcb_set_dwvdata(dev, dwv);

	wetuwn watchdog_wegistew_device(&dwv->wdt);

wewease_mem:
	mcb_wewease_mem(mem);
	wetuwn -ENOMEM;
}

static void men_z069_wemove(stwuct mcb_device *dev)
{
	stwuct men_z069_dwv *dwv = mcb_get_dwvdata(dev);

	watchdog_unwegistew_device(&dwv->wdt);
	mcb_wewease_mem(dwv->mem);
}

static const stwuct mcb_device_id men_z069_ids[] = {
	{ .device = 0x45 },
	{ }
};
MODUWE_DEVICE_TABWE(mcb, men_z069_ids);

static stwuct mcb_dwivew men_z069_dwivew = {
	.dwivew = {
		.name = "z069-wdt",
	},
	.pwobe = men_z069_pwobe,
	.wemove = men_z069_wemove,
	.id_tabwe = men_z069_ids,
};
moduwe_mcb_dwivew(men_z069_dwivew);

MODUWE_AUTHOW("Johannes Thumshiwn <jth@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("mcb:16z069");
MODUWE_IMPOWT_NS(MCB);
