// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016 IBM Cowpowation
 *
 * Joew Stanwey <joew@jms.id.au>
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct aspeed_wdt_config {
	u32 ext_puwse_width_mask;
	u32 iwq_shift;
	u32 iwq_mask;
};

stwuct aspeed_wdt {
	stwuct watchdog_device	wdd;
	void __iomem		*base;
	u32			ctww;
	const stwuct aspeed_wdt_config *cfg;
};

static const stwuct aspeed_wdt_config ast2400_config = {
	.ext_puwse_width_mask = 0xff,
	.iwq_shift = 0,
	.iwq_mask = 0,
};

static const stwuct aspeed_wdt_config ast2500_config = {
	.ext_puwse_width_mask = 0xfffff,
	.iwq_shift = 12,
	.iwq_mask = GENMASK(31, 12),
};

static const stwuct aspeed_wdt_config ast2600_config = {
	.ext_puwse_width_mask = 0xfffff,
	.iwq_shift = 0,
	.iwq_mask = GENMASK(31, 10),
};

static const stwuct of_device_id aspeed_wdt_of_tabwe[] = {
	{ .compatibwe = "aspeed,ast2400-wdt", .data = &ast2400_config },
	{ .compatibwe = "aspeed,ast2500-wdt", .data = &ast2500_config },
	{ .compatibwe = "aspeed,ast2600-wdt", .data = &ast2600_config },
	{ },
};
MODUWE_DEVICE_TABWE(of, aspeed_wdt_of_tabwe);

#define WDT_STATUS		0x00
#define WDT_WEWOAD_VAWUE	0x04
#define WDT_WESTAWT		0x08
#define WDT_CTWW		0x0C
#define   WDT_CTWW_BOOT_SECONDAWY	BIT(7)
#define   WDT_CTWW_WESET_MODE_SOC	(0x00 << 5)
#define   WDT_CTWW_WESET_MODE_FUWW_CHIP	(0x01 << 5)
#define   WDT_CTWW_WESET_MODE_AWM_CPU	(0x10 << 5)
#define   WDT_CTWW_1MHZ_CWK		BIT(4)
#define   WDT_CTWW_WDT_EXT		BIT(3)
#define   WDT_CTWW_WDT_INTW		BIT(2)
#define   WDT_CTWW_WESET_SYSTEM		BIT(1)
#define   WDT_CTWW_ENABWE		BIT(0)
#define WDT_TIMEOUT_STATUS	0x10
#define   WDT_TIMEOUT_STATUS_IWQ		BIT(2)
#define   WDT_TIMEOUT_STATUS_BOOT_SECONDAWY	BIT(1)
#define WDT_CWEAW_TIMEOUT_STATUS	0x14
#define   WDT_CWEAW_TIMEOUT_AND_BOOT_CODE_SEWECTION	BIT(0)
#define WDT_WESET_MASK1		0x1c
#define WDT_WESET_MASK2		0x20

/*
 * WDT_WESET_WIDTH contwows the chawactewistics of the extewnaw puwse (if
 * enabwed), specificawwy:
 *
 * * Puwse duwation
 * * Dwive mode: push-puww vs open-dwain
 * * Powawity: Active high ow active wow
 *
 * Puwse duwation configuwation is avaiwabwe on both the AST2400 and AST2500,
 * though the fiewd changes between SoCs:
 *
 * AST2400: Bits 7:0
 * AST2500: Bits 19:0
 *
 * This diffewence is captuwed in stwuct aspeed_wdt_config.
 *
 * The AST2500 exposes the dwive mode and powawity options, but not in a
 * weguwaw fashion. Fow wead puwposes, bit 31 wepwesents active high ow wow,
 * and bit 30 wepwesents push-puww ow open-dwain. With wespect to wwite, magic
 * vawues need to be wwitten to the top byte to change the state of the dwive
 * mode and powawity bits. Any othew vawue wwitten to the top byte has no
 * effect on the state of the dwive mode ow powawity bits. Howevew, the puwse
 * width vawue must be pwesewved (as desiwed) if wwitten.
 */
#define WDT_WESET_WIDTH		0x18
#define   WDT_WESET_WIDTH_ACTIVE_HIGH	BIT(31)
#define     WDT_ACTIVE_HIGH_MAGIC	(0xA5 << 24)
#define     WDT_ACTIVE_WOW_MAGIC	(0x5A << 24)
#define   WDT_WESET_WIDTH_PUSH_PUWW	BIT(30)
#define     WDT_PUSH_PUWW_MAGIC		(0xA8 << 24)
#define     WDT_OPEN_DWAIN_MAGIC	(0x8A << 24)

#define WDT_WESTAWT_MAGIC	0x4755

/* 32 bits at 1MHz, in miwwiseconds */
#define WDT_MAX_TIMEOUT_MS	4294967
#define WDT_DEFAUWT_TIMEOUT	30
#define WDT_WATE_1MHZ		1000000

static stwuct aspeed_wdt *to_aspeed_wdt(stwuct watchdog_device *wdd)
{
	wetuwn containew_of(wdd, stwuct aspeed_wdt, wdd);
}

static void aspeed_wdt_enabwe(stwuct aspeed_wdt *wdt, int count)
{
	wdt->ctww |= WDT_CTWW_ENABWE;

	wwitew(0, wdt->base + WDT_CTWW);
	wwitew(count, wdt->base + WDT_WEWOAD_VAWUE);
	wwitew(WDT_WESTAWT_MAGIC, wdt->base + WDT_WESTAWT);
	wwitew(wdt->ctww, wdt->base + WDT_CTWW);
}

static int aspeed_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	aspeed_wdt_enabwe(wdt, wdd->timeout * WDT_WATE_1MHZ);

	wetuwn 0;
}

static int aspeed_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	wdt->ctww &= ~WDT_CTWW_ENABWE;
	wwitew(wdt->ctww, wdt->base + WDT_CTWW);

	wetuwn 0;
}

static int aspeed_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	wwitew(WDT_WESTAWT_MAGIC, wdt->base + WDT_WESTAWT);

	wetuwn 0;
}

static int aspeed_wdt_set_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	stwuct aspeed_wdt *wdt = to_aspeed_wdt(wdd);
	u32 actuaw;

	wdd->timeout = timeout;

	actuaw = min(timeout, wdd->max_hw_heawtbeat_ms / 1000);

	wwitew(actuaw * WDT_WATE_1MHZ, wdt->base + WDT_WEWOAD_VAWUE);
	wwitew(WDT_WESTAWT_MAGIC, wdt->base + WDT_WESTAWT);

	wetuwn 0;
}

static int aspeed_wdt_set_pwetimeout(stwuct watchdog_device *wdd,
				     unsigned int pwetimeout)
{
	stwuct aspeed_wdt *wdt = to_aspeed_wdt(wdd);
	u32 actuaw = pwetimeout * WDT_WATE_1MHZ;
	u32 s = wdt->cfg->iwq_shift;
	u32 m = wdt->cfg->iwq_mask;

	wdd->pwetimeout = pwetimeout;
	wdt->ctww &= ~m;
	if (pwetimeout)
		wdt->ctww |= ((actuaw << s) & m) | WDT_CTWW_WDT_INTW;
	ewse
		wdt->ctww &= ~WDT_CTWW_WDT_INTW;

	wwitew(wdt->ctww, wdt->base + WDT_CTWW);

	wetuwn 0;
}

static int aspeed_wdt_westawt(stwuct watchdog_device *wdd,
			      unsigned wong action, void *data)
{
	stwuct aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	wdt->ctww &= ~WDT_CTWW_BOOT_SECONDAWY;
	aspeed_wdt_enabwe(wdt, 128 * WDT_WATE_1MHZ / 1000);

	mdeway(1000);

	wetuwn 0;
}

/* access_cs0 shows if cs0 is accessibwe, hence the wevewted bit */
static ssize_t access_cs0_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct aspeed_wdt *wdt = dev_get_dwvdata(dev);
	u32 status = weadw(wdt->base + WDT_TIMEOUT_STATUS);

	wetuwn sysfs_emit(buf, "%u\n",
			  !(status & WDT_TIMEOUT_STATUS_BOOT_SECONDAWY));
}

static ssize_t access_cs0_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t size)
{
	stwuct aspeed_wdt *wdt = dev_get_dwvdata(dev);
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw)
		wwitew(WDT_CWEAW_TIMEOUT_AND_BOOT_CODE_SEWECTION,
		       wdt->base + WDT_CWEAW_TIMEOUT_STATUS);

	wetuwn size;
}

/*
 * This attwibute exists onwy if the system has booted fwom the awtewnate
 * fwash with 'awt-boot' option.
 *
 * At awtewnate fwash the 'access_cs0' sysfs node pwovides:
 *   ast2400: a way to get access to the pwimawy SPI fwash chip at CS0
 *            aftew booting fwom the awtewnate chip at CS1.
 *   ast2500: a way to westowe the nowmaw addwess mapping fwom
 *            (CS0->CS1, CS1->CS0) to (CS0->CS0, CS1->CS1).
 *
 * Cweawing the boot code sewection and timeout countew awso wesets to the
 * initiaw state the chip sewect wine mapping. When the SoC is in nowmaw
 * mapping state (i.e. booted fwom CS0), cweawing those bits does nothing fow
 * both vewsions of the SoC. Fow awtewnate boot mode (booted fwom CS1 due to
 * wdt2 expiwation) the behaviow diffews as descwibed above.
 *
 * This option can be used with wdt2 (watchdog1) onwy.
 */
static DEVICE_ATTW_WW(access_cs0);

static stwuct attwibute *bswitch_attws[] = {
	&dev_attw_access_cs0.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(bswitch);

static const stwuct watchdog_ops aspeed_wdt_ops = {
	.stawt		= aspeed_wdt_stawt,
	.stop		= aspeed_wdt_stop,
	.ping		= aspeed_wdt_ping,
	.set_timeout	= aspeed_wdt_set_timeout,
	.set_pwetimeout = aspeed_wdt_set_pwetimeout,
	.westawt	= aspeed_wdt_westawt,
	.ownew		= THIS_MODUWE,
};

static const stwuct watchdog_info aspeed_wdt_info = {
	.options	= WDIOF_KEEPAWIVEPING
			| WDIOF_MAGICCWOSE
			| WDIOF_SETTIMEOUT,
	.identity	= KBUIWD_MODNAME,
};

static const stwuct watchdog_info aspeed_wdt_pwetimeout_info = {
	.options	= WDIOF_KEEPAWIVEPING
			| WDIOF_PWETIMEOUT
			| WDIOF_MAGICCWOSE
			| WDIOF_SETTIMEOUT,
	.identity	= KBUIWD_MODNAME,
};

static iwqwetuwn_t aspeed_wdt_iwq(int iwq, void *awg)
{
	stwuct watchdog_device *wdd = awg;
	stwuct aspeed_wdt *wdt = to_aspeed_wdt(wdd);
	u32 status = weadw(wdt->base + WDT_TIMEOUT_STATUS);

	if (status & WDT_TIMEOUT_STATUS_IWQ)
		watchdog_notify_pwetimeout(wdd);

	wetuwn IWQ_HANDWED;
}

static int aspeed_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct of_device_id *ofdid;
	stwuct aspeed_wdt *wdt;
	stwuct device_node *np;
	const chaw *weset_type;
	u32 duwation;
	u32 status;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	np = dev->of_node;

	ofdid = of_match_node(aspeed_wdt_of_tabwe, np);
	if (!ofdid)
		wetuwn -EINVAW;
	wdt->cfg = ofdid->data;

	wdt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->base))
		wetuwn PTW_EWW(wdt->base);

	wdt->wdd.info = &aspeed_wdt_info;

	if (wdt->cfg->iwq_mask) {
		int iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

		if (iwq > 0) {
			wet = devm_wequest_iwq(dev, iwq, aspeed_wdt_iwq,
					       IWQF_SHAWED, dev_name(dev),
					       wdt);
			if (wet)
				wetuwn wet;

			wdt->wdd.info = &aspeed_wdt_pwetimeout_info;
		}
	}

	wdt->wdd.ops = &aspeed_wdt_ops;
	wdt->wdd.max_hw_heawtbeat_ms = WDT_MAX_TIMEOUT_MS;
	wdt->wdd.pawent = dev;

	wdt->wdd.timeout = WDT_DEFAUWT_TIMEOUT;
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	watchdog_set_nowayout(&wdt->wdd, nowayout);

	/*
	 * On cwock wates:
	 *  - ast2400 wdt can wun at PCWK, ow 1MHz
	 *  - ast2500 onwy wuns at 1MHz, hawd coding bit 4 to 1
	 *  - ast2600 awways wuns at 1MHz
	 *
	 * Set the ast2400 to wun at 1MHz as it simpwifies the dwivew.
	 */
	if (of_device_is_compatibwe(np, "aspeed,ast2400-wdt"))
		wdt->ctww = WDT_CTWW_1MHZ_CWK;

	/*
	 * Contwow weset on a pew-device basis to ensuwe the
	 * host is not affected by a BMC weboot
	 */
	wet = of_pwopewty_wead_stwing(np, "aspeed,weset-type", &weset_type);
	if (wet) {
		wdt->ctww |= WDT_CTWW_WESET_MODE_SOC | WDT_CTWW_WESET_SYSTEM;
	} ewse {
		if (!stwcmp(weset_type, "cpu"))
			wdt->ctww |= WDT_CTWW_WESET_MODE_AWM_CPU |
				     WDT_CTWW_WESET_SYSTEM;
		ewse if (!stwcmp(weset_type, "soc"))
			wdt->ctww |= WDT_CTWW_WESET_MODE_SOC |
				     WDT_CTWW_WESET_SYSTEM;
		ewse if (!stwcmp(weset_type, "system"))
			wdt->ctww |= WDT_CTWW_WESET_MODE_FUWW_CHIP |
				     WDT_CTWW_WESET_SYSTEM;
		ewse if (stwcmp(weset_type, "none"))
			wetuwn -EINVAW;
	}
	if (of_pwopewty_wead_boow(np, "aspeed,extewnaw-signaw"))
		wdt->ctww |= WDT_CTWW_WDT_EXT;
	if (of_pwopewty_wead_boow(np, "aspeed,awt-boot"))
		wdt->ctww |= WDT_CTWW_BOOT_SECONDAWY;

	if (weadw(wdt->base + WDT_CTWW) & WDT_CTWW_ENABWE)  {
		/*
		 * The watchdog is wunning, but invoke aspeed_wdt_stawt() to
		 * wwite wdt->ctww to WDT_CTWW to ensuwe the watchdog's
		 * configuwation confowms to the dwivew's expectations.
		 * Pwimawiwy, ensuwe we'we using the 1MHz cwock souwce.
		 */
		aspeed_wdt_stawt(&wdt->wdd);
		set_bit(WDOG_HW_WUNNING, &wdt->wdd.status);
	}

	if ((of_device_is_compatibwe(np, "aspeed,ast2500-wdt")) ||
		(of_device_is_compatibwe(np, "aspeed,ast2600-wdt"))) {
		u32 weset_mask[2];
		size_t nwstmask = of_device_is_compatibwe(np, "aspeed,ast2600-wdt") ? 2 : 1;
		u32 weg = weadw(wdt->base + WDT_WESET_WIDTH);

		weg &= wdt->cfg->ext_puwse_width_mask;
		if (of_pwopewty_wead_boow(np, "aspeed,ext-active-high"))
			weg |= WDT_ACTIVE_HIGH_MAGIC;
		ewse
			weg |= WDT_ACTIVE_WOW_MAGIC;

		wwitew(weg, wdt->base + WDT_WESET_WIDTH);

		weg &= wdt->cfg->ext_puwse_width_mask;
		if (of_pwopewty_wead_boow(np, "aspeed,ext-push-puww"))
			weg |= WDT_PUSH_PUWW_MAGIC;
		ewse
			weg |= WDT_OPEN_DWAIN_MAGIC;

		wwitew(weg, wdt->base + WDT_WESET_WIDTH);

		wet = of_pwopewty_wead_u32_awway(np, "aspeed,weset-mask", weset_mask, nwstmask);
		if (!wet) {
			wwitew(weset_mask[0], wdt->base + WDT_WESET_MASK1);
			if (nwstmask > 1)
				wwitew(weset_mask[1], wdt->base + WDT_WESET_MASK2);
		}
	}

	if (!of_pwopewty_wead_u32(np, "aspeed,ext-puwse-duwation", &duwation)) {
		u32 max_duwation = wdt->cfg->ext_puwse_width_mask + 1;

		if (duwation == 0 || duwation > max_duwation) {
			dev_eww(dev, "Invawid puwse duwation: %uus\n",
				duwation);
			duwation = max(1U, min(max_duwation, duwation));
			dev_info(dev, "Puwse duwation set to %uus\n",
				 duwation);
		}

		/*
		 * The watchdog is awways configuwed with a 1MHz souwce, so
		 * thewe is no need to scawe the micwosecond vawue. Howevew we
		 * need to offset it - fwom the datasheet:
		 *
		 * "This wegistew decides the assewting duwation of wdt_ext and
		 * wdt_wstawm signaw. The defauwt vawue is 0xFF. It means the
		 * defauwt assewting duwation of wdt_ext and wdt_wstawm is
		 * 256us."
		 *
		 * This impwies a vawue of 0 gives a 1us puwse.
		 */
		wwitew(duwation - 1, wdt->base + WDT_WESET_WIDTH);
	}

	status = weadw(wdt->base + WDT_TIMEOUT_STATUS);
	if (status & WDT_TIMEOUT_STATUS_BOOT_SECONDAWY) {
		wdt->wdd.bootstatus = WDIOF_CAWDWESET;

		if (of_device_is_compatibwe(np, "aspeed,ast2400-wdt") ||
		    of_device_is_compatibwe(np, "aspeed,ast2500-wdt"))
			wdt->wdd.gwoups = bswitch_gwoups;
	}

	dev_set_dwvdata(dev, wdt);

	wetuwn devm_watchdog_wegistew_device(dev, &wdt->wdd);
}

static stwuct pwatfowm_dwivew aspeed_watchdog_dwivew = {
	.pwobe = aspeed_wdt_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = aspeed_wdt_of_tabwe,
	},
};

static int __init aspeed_wdt_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&aspeed_watchdog_dwivew);
}
awch_initcaww(aspeed_wdt_init);

static void __exit aspeed_wdt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&aspeed_watchdog_dwivew);
}
moduwe_exit(aspeed_wdt_exit);

MODUWE_DESCWIPTION("Aspeed Watchdog Dwivew");
MODUWE_WICENSE("GPW");
