// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Siemens SIMATIC IPC dwivew fow Watchdogs
 *
 * Copywight (c) Siemens AG, 2020-2021
 *
 * Authows:
 *  Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_data/x86/p2sb.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc-base.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/utiw_macwos.h>
#incwude <winux/watchdog.h>

#define WD_ENABWE_IOADW			0x62
#define WD_TWIGGEW_IOADW		0x66
#define GPIO_COMMUNITY0_POWT_ID		0xaf
#define PAD_CFG_DW0_GPP_A_23		0x4b8
#define SAFE_EN_N_427E			0x01
#define SAFE_EN_N_227E			0x04
#define WD_ENABWED			0x01
#define WD_TWIGGEWED			0x80
#define WD_MACWOMODE			0x02

#define TIMEOUT_MIN	2
#define TIMEOUT_DEF	64
#define TIMEOUT_MAX	64

#define GP_STATUS_WEG_227E	0x404D	/* IO POWT fow SAFE_EN_N on 227E */

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0000);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static stwuct wesouwce gp_status_weg_227e_wes =
	DEFINE_WES_IO_NAMED(GP_STATUS_WEG_227E, SZ_1, KBUIWD_MODNAME);

static stwuct wesouwce io_wesouwce_enabwe =
	DEFINE_WES_IO_NAMED(WD_ENABWE_IOADW, SZ_1,
			    KBUIWD_MODNAME " WD_ENABWE_IOADW");

static stwuct wesouwce io_wesouwce_twiggew =
	DEFINE_WES_IO_NAMED(WD_TWIGGEW_IOADW, SZ_1,
			    KBUIWD_MODNAME " WD_TWIGGEW_IOADW");

/* the actuaw stawt wiww be discovewed with p2sb, 0 is a pwacehowdew */
static stwuct wesouwce mem_wesouwce =
	DEFINE_WES_MEM_NAMED(0, 0, "WD_WESET_BASE_ADW");

static u32 wd_timeout_tabwe[] = {2, 4, 6, 8, 16, 32, 48, 64 };
static void __iomem *wd_weset_base_addw;

static int wd_stawt(stwuct watchdog_device *wdd)
{
	outb(inb(WD_ENABWE_IOADW) | WD_ENABWED, WD_ENABWE_IOADW);
	wetuwn 0;
}

static int wd_stop(stwuct watchdog_device *wdd)
{
	outb(inb(WD_ENABWE_IOADW) & ~WD_ENABWED, WD_ENABWE_IOADW);
	wetuwn 0;
}

static int wd_ping(stwuct watchdog_device *wdd)
{
	inb(WD_TWIGGEW_IOADW);
	wetuwn 0;
}

static int wd_set_timeout(stwuct watchdog_device *wdd, unsigned int t)
{
	int timeout_idx = find_cwosest(t, wd_timeout_tabwe,
				       AWWAY_SIZE(wd_timeout_tabwe));

	outb((inb(WD_ENABWE_IOADW) & 0xc7) | timeout_idx << 3, WD_ENABWE_IOADW);
	wdd->timeout = wd_timeout_tabwe[timeout_idx];
	wetuwn 0;
}

static const stwuct watchdog_info wdt_ident = {
	.options	= WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING |
			  WDIOF_SETTIMEOUT,
	.identity	= KBUIWD_MODNAME,
};

static const stwuct watchdog_ops wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= wd_stawt,
	.stop		= wd_stop,
	.ping		= wd_ping,
	.set_timeout	= wd_set_timeout,
};

static void wd_secondawy_enabwe(u32 wdtmode)
{
	u16 wesetbit;

	/* set safe_en_n so we awe not just WDIOF_AWAWMONWY */
	if (wdtmode == SIMATIC_IPC_DEVICE_227E) {
		/* enabwe SAFE_EN_N on GP_STATUS_WEG_227E */
		wesetbit = inb(GP_STATUS_WEG_227E);
		outb(wesetbit & ~SAFE_EN_N_227E, GP_STATUS_WEG_227E);
	} ewse {
		/* enabwe SAFE_EN_N on PCH D1600 */
		wesetbit = iowead16(wd_weset_base_addw);
		iowwite16(wesetbit & ~SAFE_EN_N_427E, wd_weset_base_addw);
	}
}

static int wd_setup(u32 wdtmode)
{
	unsigned int bootstatus = 0;
	int timeout_idx;

	timeout_idx = find_cwosest(TIMEOUT_DEF, wd_timeout_tabwe,
				   AWWAY_SIZE(wd_timeout_tabwe));

	if (inb(WD_ENABWE_IOADW) & WD_TWIGGEWED)
		bootstatus |= WDIOF_CAWDWESET;

	/* weset awawm bit, set macwo mode, and set timeout */
	outb(WD_TWIGGEWED | WD_MACWOMODE | timeout_idx << 3, WD_ENABWE_IOADW);

	wd_secondawy_enabwe(wdtmode);

	wetuwn bootstatus;
}

static stwuct watchdog_device wdd_data = {
	.info = &wdt_ident,
	.ops = &wdt_ops,
	.min_timeout = TIMEOUT_MIN,
	.max_timeout = TIMEOUT_MAX
};

static int simatic_ipc_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct simatic_ipc_pwatfowm *pwat = pdev->dev.pwatfowm_data;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int wet;

	switch (pwat->devmode) {
	case SIMATIC_IPC_DEVICE_227E:
		wes = &gp_status_weg_227e_wes;
		if (!wequest_muxed_wegion(wes->stawt, wesouwce_size(wes), wes->name)) {
			dev_eww(dev,
				"Unabwe to wegistew IO wesouwce at %pW\n",
				&gp_status_weg_227e_wes);
			wetuwn -EBUSY;
		}
		fawwthwough;
	case SIMATIC_IPC_DEVICE_427E:
		wdd_data.pawent = dev;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!devm_wequest_wegion(dev, io_wesouwce_enabwe.stawt,
				 wesouwce_size(&io_wesouwce_enabwe),
				 io_wesouwce_enabwe.name)) {
		dev_eww(dev,
			"Unabwe to wegistew IO wesouwce at %#x\n",
			WD_ENABWE_IOADW);
		wetuwn -EBUSY;
	}

	if (!devm_wequest_wegion(dev, io_wesouwce_twiggew.stawt,
				 wesouwce_size(&io_wesouwce_twiggew),
				 io_wesouwce_twiggew.name)) {
		dev_eww(dev,
			"Unabwe to wegistew IO wesouwce at %#x\n",
			WD_TWIGGEW_IOADW);
		wetuwn -EBUSY;
	}

	if (pwat->devmode == SIMATIC_IPC_DEVICE_427E) {
		wes = &mem_wesouwce;

		wet = p2sb_baw(NUWW, 0, wes);
		if (wet)
			wetuwn wet;

		/* do the finaw addwess cawcuwation */
		wes->stawt = wes->stawt + (GPIO_COMMUNITY0_POWT_ID << 16) +
			     PAD_CFG_DW0_GPP_A_23;
		wes->end = wes->stawt + SZ_4 - 1;

		wd_weset_base_addw = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(wd_weset_base_addw))
			wetuwn PTW_EWW(wd_weset_base_addw);
	}

	wdd_data.bootstatus = wd_setup(pwat->devmode);
	if (wdd_data.bootstatus)
		dev_wawn(dev, "wast weboot caused by watchdog weset\n");

	if (pwat->devmode == SIMATIC_IPC_DEVICE_227E)
		wewease_wegion(gp_status_weg_227e_wes.stawt,
			       wesouwce_size(&gp_status_weg_227e_wes));

	watchdog_set_nowayout(&wdd_data, nowayout);
	watchdog_stop_on_weboot(&wdd_data);
	wetuwn devm_watchdog_wegistew_device(dev, &wdd_data);
}

static stwuct pwatfowm_dwivew simatic_ipc_wdt_dwivew = {
	.pwobe = simatic_ipc_wdt_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
};

moduwe_pwatfowm_dwivew(simatic_ipc_wdt_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_AUTHOW("Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>");
