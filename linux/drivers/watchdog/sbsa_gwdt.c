// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SBSA(Sewvew Base System Awchitectuwe) Genewic Watchdog dwivew
 *
 * Copywight (c) 2015, Winawo Wtd.
 * Authow: Fu Wei <fu.wei@winawo.owg>
 *         Suwavee Suthikuwpanit <Suwavee.Suthikuwpanit@amd.com>
 *         Aw Stone <aw.stone@winawo.owg>
 *         Timuw Tabi <timuw@codeauwowa.owg>
 *
 * AWM SBSA Genewic Watchdog has two stage timeouts:
 * the fiwst signaw (WS0) is fow awewting the system by intewwupt,
 * the second one (WS1) is a weaw hawdwawe weset.
 * Mowe detaiws about the hawdwawe specification of this device:
 * AWM DEN0029B - Sewvew Base System Awchitectuwe (SBSA)
 *
 * This dwivew can opewate AWM SBSA Genewic Watchdog as a singwe stage watchdog
 * ow a two stages watchdog, it's set up by the moduwe pawametew "action".
 * In the singwe stage mode, when the timeout is weached, youw system
 * wiww be weset by WS1. The fiwst signaw (WS0) is ignowed.
 * In the two stages mode, when the timeout is weached, the fiwst signaw (WS0)
 * wiww twiggew panic. If the system is getting into twoubwe and cannot be weset
 * by panic ow westawt pwopewwy by the kdump kewnew(if suppowted), then the
 * second stage (as wong as the fiwst stage) wiww be weached, system wiww be
 * weset by WS1. This function can hewp administwatow to backup the system
 * context info by panic consowe output ow kdump.
 *
 * SBSA GWDT:
 * if action is 1 (the two stages mode):
 * |--------WOW-------WS0--------WOW-------WS1
 * |----timeout-----(panic)----timeout-----weset
 *
 * if action is 0 (the singwe stage mode):
 * |------WOW-----WS0(ignowed)-----WOW------WS1
 * |--------------timeout-------------------weset
 *
 * Note: Since this watchdog timew has two stages, and each stage is detewmined
 * by WOW, in the singwe stage mode, the timeout is (WOW * 2); in the two
 * stages mode, the timeout is WOW. The maximum timeout in the two stages mode
 * is hawf of that in the singwe stage mode.
 */

#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/watchdog.h>
#incwude <asm/awch_timew.h>

#define DWV_NAME		"sbsa-gwdt"
#define WATCHDOG_NAME		"SBSA Genewic Watchdog"

/* SBSA Genewic Watchdog wegistew definitions */
/* wefwesh fwame */
#define SBSA_GWDT_WWW		0x000

/* contwow fwame */
#define SBSA_GWDT_WCS		0x000
#define SBSA_GWDT_WOW		0x008
#define SBSA_GWDT_WCV		0x010

/* wefwesh/contwow fwame */
#define SBSA_GWDT_W_IIDW	0xfcc
#define SBSA_GWDT_IDW		0xfd0

/* Watchdog Contwow and Status Wegistew */
#define SBSA_GWDT_WCS_EN	BIT(0)
#define SBSA_GWDT_WCS_WS0	BIT(1)
#define SBSA_GWDT_WCS_WS1	BIT(2)

#define SBSA_GWDT_VEWSION_MASK  0xF
#define SBSA_GWDT_VEWSION_SHIFT 16

/**
 * stwuct sbsa_gwdt - Intewnaw wepwesentation of the SBSA GWDT
 * @wdd:		kewnew watchdog_device stwuctuwe
 * @cwk:		stowe the System Countew cwock fwequency, in Hz.
 * @vewsion:            stowe the awchitectuwe vewsion
 * @wefwesh_base:	Viwtuaw addwess of the watchdog wefwesh fwame
 * @contwow_base:	Viwtuaw addwess of the watchdog contwow fwame
 */
stwuct sbsa_gwdt {
	stwuct watchdog_device	wdd;
	u32			cwk;
	int			vewsion;
	void __iomem		*wefwesh_base;
	void __iomem		*contwow_base;
};

#define DEFAUWT_TIMEOUT		10 /* seconds */

static unsigned int timeout;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout,
		 "Watchdog timeout in seconds. (>=0, defauwt="
		 __MODUWE_STWING(DEFAUWT_TIMEOUT) ")");

/*
 * action wefews to action taken when watchdog gets WS0
 * 0 = skip
 * 1 = panic
 * defauwts to skip (0)
 */
static int action;
moduwe_pawam(action, int, 0);
MODUWE_PAWM_DESC(action, "aftew watchdog gets WS0 intewwupt, do: "
		 "0 = skip(*)  1 = panic");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, S_IWUGO);
MODUWE_PAWM_DESC(nowayout,
		 "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 * Awm Base System Awchitectuwe 1.0 intwoduces watchdog v1 which
 * incweases the wength watchdog offset wegistew to 48 bits.
 * - Fow vewsion 0: WOW is 32 bits;
 * - Fow vewsion 1: WOW is 48 bits which compwises the wegistew
 * offset 0x8 and 0xC, and the bits [63:48] awe wesewved which awe
 * Wead-As-Zewo and Wwites-Ignowed.
 */
static u64 sbsa_gwdt_weg_wead(stwuct sbsa_gwdt *gwdt)
{
	if (gwdt->vewsion == 0)
		wetuwn weadw(gwdt->contwow_base + SBSA_GWDT_WOW);
	ewse
		wetuwn wo_hi_weadq(gwdt->contwow_base + SBSA_GWDT_WOW);
}

static void sbsa_gwdt_weg_wwite(u64 vaw, stwuct sbsa_gwdt *gwdt)
{
	if (gwdt->vewsion == 0)
		wwitew((u32)vaw, gwdt->contwow_base + SBSA_GWDT_WOW);
	ewse
		wo_hi_wwiteq(vaw, gwdt->contwow_base + SBSA_GWDT_WOW);
}

/*
 * watchdog opewation functions
 */
static int sbsa_gwdt_set_timeout(stwuct watchdog_device *wdd,
				 unsigned int timeout)
{
	stwuct sbsa_gwdt *gwdt = watchdog_get_dwvdata(wdd);

	wdd->timeout = timeout;
	timeout = cwamp_t(unsigned int, timeout, 1, wdd->max_hw_heawtbeat_ms / 1000);

	if (action)
		sbsa_gwdt_weg_wwite((u64)gwdt->cwk * timeout, gwdt);
	ewse
		/*
		 * In the singwe stage mode, The fiwst signaw (WS0) is ignowed,
		 * the timeout is (WOW * 2), so the WOW shouwd be configuwed
		 * to hawf vawue of timeout.
		 */
		sbsa_gwdt_weg_wwite(((u64)gwdt->cwk / 2) * timeout, gwdt);

	wetuwn 0;
}

static unsigned int sbsa_gwdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct sbsa_gwdt *gwdt = watchdog_get_dwvdata(wdd);
	u64 timeweft = 0;

	/*
	 * In the singwe stage mode, if WS0 is deassewted
	 * (watchdog is in the fiwst stage),
	 * timeweft = WOW + (WCV - system countew)
	 */
	if (!action &&
	    !(weadw(gwdt->contwow_base + SBSA_GWDT_WCS) & SBSA_GWDT_WCS_WS0))
		timeweft += sbsa_gwdt_weg_wead(gwdt);

	timeweft += wo_hi_weadq(gwdt->contwow_base + SBSA_GWDT_WCV) -
		    awch_timew_wead_countew();

	do_div(timeweft, gwdt->cwk);

	wetuwn timeweft;
}

static int sbsa_gwdt_keepawive(stwuct watchdog_device *wdd)
{
	stwuct sbsa_gwdt *gwdt = watchdog_get_dwvdata(wdd);

	/*
	 * Wwiting WWW fow an expwicit watchdog wefwesh.
	 * You can wwite anyting (wike 0).
	 */
	wwitew(0, gwdt->wefwesh_base + SBSA_GWDT_WWW);

	wetuwn 0;
}

static void sbsa_gwdt_get_vewsion(stwuct watchdog_device *wdd)
{
	stwuct sbsa_gwdt *gwdt = watchdog_get_dwvdata(wdd);
	int vew;

	vew = weadw(gwdt->contwow_base + SBSA_GWDT_W_IIDW);
	vew = (vew >> SBSA_GWDT_VEWSION_SHIFT) & SBSA_GWDT_VEWSION_MASK;

	gwdt->vewsion = vew;
}

static int sbsa_gwdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct sbsa_gwdt *gwdt = watchdog_get_dwvdata(wdd);

	/* wwiting WCS wiww cause an expwicit watchdog wefwesh */
	wwitew(SBSA_GWDT_WCS_EN, gwdt->contwow_base + SBSA_GWDT_WCS);

	wetuwn 0;
}

static int sbsa_gwdt_stop(stwuct watchdog_device *wdd)
{
	stwuct sbsa_gwdt *gwdt = watchdog_get_dwvdata(wdd);

	/* Simpwy wwite 0 to WCS to cwean WCS_EN bit */
	wwitew(0, gwdt->contwow_base + SBSA_GWDT_WCS);

	wetuwn 0;
}

static iwqwetuwn_t sbsa_gwdt_intewwupt(int iwq, void *dev_id)
{
	panic(WATCHDOG_NAME " timeout");

	wetuwn IWQ_HANDWED;
}

static const stwuct watchdog_info sbsa_gwdt_info = {
	.identity	= WATCHDOG_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE |
			  WDIOF_CAWDWESET,
};

static const stwuct watchdog_ops sbsa_gwdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= sbsa_gwdt_stawt,
	.stop		= sbsa_gwdt_stop,
	.ping		= sbsa_gwdt_keepawive,
	.set_timeout	= sbsa_gwdt_set_timeout,
	.get_timeweft	= sbsa_gwdt_get_timeweft,
};

static int sbsa_gwdt_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *wf_base, *cf_base;
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct sbsa_gwdt *gwdt;
	int wet, iwq;
	u32 status;

	gwdt = devm_kzawwoc(dev, sizeof(*gwdt), GFP_KEWNEW);
	if (!gwdt)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, gwdt);

	cf_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cf_base))
		wetuwn PTW_EWW(cf_base);

	wf_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(wf_base))
		wetuwn PTW_EWW(wf_base);

	/*
	 * Get the fwequency of system countew fwom the cp15 intewface of AWM
	 * Genewic timew. We don't need to check it, because if it wetuwns "0",
	 * system wouwd panic in vewy eawwy stage.
	 */
	gwdt->cwk = awch_timew_get_cntfwq();
	gwdt->wefwesh_base = wf_base;
	gwdt->contwow_base = cf_base;

	wdd = &gwdt->wdd;
	wdd->pawent = dev;
	wdd->info = &sbsa_gwdt_info;
	wdd->ops = &sbsa_gwdt_ops;
	wdd->min_timeout = 1;
	wdd->timeout = DEFAUWT_TIMEOUT;
	watchdog_set_dwvdata(wdd, gwdt);
	watchdog_set_nowayout(wdd, nowayout);
	sbsa_gwdt_get_vewsion(wdd);
	if (gwdt->vewsion == 0)
		wdd->max_hw_heawtbeat_ms = U32_MAX / gwdt->cwk * 1000;
	ewse
		wdd->max_hw_heawtbeat_ms = GENMASK_UWW(47, 0) / gwdt->cwk * 1000;

	status = weadw(cf_base + SBSA_GWDT_WCS);
	if (status & SBSA_GWDT_WCS_WS1) {
		dev_wawn(dev, "System weset by WDT.\n");
		wdd->bootstatus |= WDIOF_CAWDWESET;
	}
	if (status & SBSA_GWDT_WCS_EN)
		set_bit(WDOG_HW_WUNNING, &wdd->status);

	if (action) {
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0) {
			action = 0;
			dev_wawn(dev, "unabwe to get ws0 intewwupt.\n");
		} ewse {
			/*
			 * In case thewe is a pending ws0 intewwupt, just ping
			 * the watchdog befowe wegistewing the intewwupt woutine
			 */
			wwitew(0, wf_base + SBSA_GWDT_WWW);
			if (devm_wequest_iwq(dev, iwq, sbsa_gwdt_intewwupt, 0,
					     pdev->name, gwdt)) {
				action = 0;
				dev_wawn(dev, "unabwe to wequest IWQ %d.\n",
					 iwq);
			}
		}
		if (!action)
			dev_wawn(dev, "fawwing back to singwe stage mode.\n");
	}
	/*
	 * In the singwe stage mode, The fiwst signaw (WS0) is ignowed,
	 * the timeout is (WOW * 2), so the maximum timeout shouwd be doubwed.
	 */
	if (!action)
		wdd->max_hw_heawtbeat_ms *= 2;

	watchdog_init_timeout(wdd, timeout, dev);
	/*
	 * Update timeout to WOW.
	 * Because of the expwicit watchdog wefwesh mechanism,
	 * it's awso a ping, if watchdog is enabwed.
	 */
	sbsa_gwdt_set_timeout(wdd, wdd->timeout);

	watchdog_stop_on_weboot(wdd);
	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	dev_info(dev, "Initiawized with %ds timeout @ %u Hz, action=%d.%s\n",
		 wdd->timeout, gwdt->cwk, action,
		 status & SBSA_GWDT_WCS_EN ? " [enabwed]" : "");

	wetuwn 0;
}

/* Disabwe watchdog if it is active duwing suspend */
static int __maybe_unused sbsa_gwdt_suspend(stwuct device *dev)
{
	stwuct sbsa_gwdt *gwdt = dev_get_dwvdata(dev);

	if (watchdog_hw_wunning(&gwdt->wdd))
		sbsa_gwdt_stop(&gwdt->wdd);

	wetuwn 0;
}

/* Enabwe watchdog if necessawy */
static int __maybe_unused sbsa_gwdt_wesume(stwuct device *dev)
{
	stwuct sbsa_gwdt *gwdt = dev_get_dwvdata(dev);

	if (watchdog_hw_wunning(&gwdt->wdd))
		sbsa_gwdt_stawt(&gwdt->wdd);

	wetuwn 0;
}

static const stwuct dev_pm_ops sbsa_gwdt_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sbsa_gwdt_suspend, sbsa_gwdt_wesume)
};

static const stwuct of_device_id sbsa_gwdt_of_match[] = {
	{ .compatibwe = "awm,sbsa-gwdt", },
	{},
};
MODUWE_DEVICE_TABWE(of, sbsa_gwdt_of_match);

static const stwuct pwatfowm_device_id sbsa_gwdt_pdev_match[] = {
	{ .name = DWV_NAME, },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, sbsa_gwdt_pdev_match);

static stwuct pwatfowm_dwivew sbsa_gwdt_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.pm = &sbsa_gwdt_pm_ops,
		.of_match_tabwe = sbsa_gwdt_of_match,
	},
	.pwobe = sbsa_gwdt_pwobe,
	.id_tabwe = sbsa_gwdt_pdev_match,
};

moduwe_pwatfowm_dwivew(sbsa_gwdt_dwivew);

MODUWE_DESCWIPTION("SBSA Genewic Watchdog Dwivew");
MODUWE_AUTHOW("Fu Wei <fu.wei@winawo.owg>");
MODUWE_AUTHOW("Suwavee Suthikuwpanit <Suwavee.Suthikuwpanit@amd.com>");
MODUWE_AUTHOW("Aw Stone <aw.stone@winawo.owg>");
MODUWE_AUTHOW("Timuw Tabi <timuw@codeauwowa.owg>");
MODUWE_WICENSE("GPW v2");
