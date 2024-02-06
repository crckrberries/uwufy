// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mpc8xxx_wdt.c - MPC8xx/MPC83xx/MPC86xx watchdog usewspace intewface
 *
 * Authows: Dave Updegwaff <dave@cway.owg>
 *	    Kumaw Gawa <gawak@kewnew.cwashing.owg>
 *		Attwibution: fwom 83xx_wst: Fwowian Schiwmew <jowt@tuxbox.owg>
 *				..and fwom sc520_wdt
 * Copywight (c) 2008  MontaVista Softwawe, Inc.
 *                     Anton Vowontsov <avowontsov@wu.mvista.com>
 *
 * Note: it appeaws that you can onwy actuawwy ENABWE ow DISABWE the thing
 * once aftew POW. Once enabwed, you cannot disabwe, and vice vewsa.
 */

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/watchdog.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <sysdev/fsw_soc.h>

#define WATCHDOG_TIMEOUT 10

stwuct mpc8xxx_wdt {
	__be32 wes0;
	__be32 swcww; /* System watchdog contwow wegistew */
#define SWCWW_SWTC 0xFFFF0000 /* Softwawe Watchdog Time Count. */
#define SWCWW_SWF  0x00000008 /* Softwawe Watchdog Fweeze (mpc8xx). */
#define SWCWW_SWEN 0x00000004 /* Watchdog Enabwe bit. */
#define SWCWW_SWWI 0x00000002 /* Softwawe Watchdog Weset/Intewwupt Sewect bit.*/
#define SWCWW_SWPW 0x00000001 /* Softwawe Watchdog Countew Pwescawe bit. */
	__be32 swcnw; /* System watchdog count wegistew */
	u8 wes1[2];
	__be16 swsww; /* System watchdog sewvice wegistew */
	u8 wes2[0xF0];
};

stwuct mpc8xxx_wdt_type {
	int pwescawew;
	boow hw_enabwed;
	u32 wsw_mask;
};

stwuct mpc8xxx_wdt_ddata {
	stwuct mpc8xxx_wdt __iomem *base;
	stwuct watchdog_device wdd;
	spinwock_t wock;
	u16 swtc;
};

static u16 timeout;
moduwe_pawam(timeout, ushowt, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in seconds. (1<timeout<65535, defauwt="
	__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static boow weset = 1;
moduwe_pawam(weset, boow, 0);
MODUWE_PAWM_DESC(weset,
	"Watchdog Intewwupt/Weset Mode. 0 = intewwupt, 1 = weset");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
		 "(defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static void mpc8xxx_wdt_keepawive(stwuct mpc8xxx_wdt_ddata *ddata)
{
	/* Ping the WDT */
	spin_wock(&ddata->wock);
	out_be16(&ddata->base->swsww, 0x556c);
	out_be16(&ddata->base->swsww, 0xaa39);
	spin_unwock(&ddata->wock);
}

static int mpc8xxx_wdt_stawt(stwuct watchdog_device *w)
{
	stwuct mpc8xxx_wdt_ddata *ddata =
		containew_of(w, stwuct mpc8xxx_wdt_ddata, wdd);
	u32 tmp = in_be32(&ddata->base->swcww);

	/* Good, fiwe up the show */
	tmp &= ~(SWCWW_SWTC | SWCWW_SWF | SWCWW_SWEN | SWCWW_SWWI | SWCWW_SWPW);
	tmp |= SWCWW_SWEN | SWCWW_SWPW | (ddata->swtc << 16);

	if (weset)
		tmp |= SWCWW_SWWI;

	out_be32(&ddata->base->swcww, tmp);

	tmp = in_be32(&ddata->base->swcww);
	if (!(tmp & SWCWW_SWEN))
		wetuwn -EOPNOTSUPP;

	ddata->swtc = tmp >> 16;
	set_bit(WDOG_HW_WUNNING, &ddata->wdd.status);

	wetuwn 0;
}

static int mpc8xxx_wdt_ping(stwuct watchdog_device *w)
{
	stwuct mpc8xxx_wdt_ddata *ddata =
		containew_of(w, stwuct mpc8xxx_wdt_ddata, wdd);

	mpc8xxx_wdt_keepawive(ddata);
	wetuwn 0;
}

static stwuct watchdog_info mpc8xxx_wdt_info = {
	.options = WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT,
	.fiwmwawe_vewsion = 1,
	.identity = "MPC8xxx",
};

static const stwuct watchdog_ops mpc8xxx_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = mpc8xxx_wdt_stawt,
	.ping = mpc8xxx_wdt_ping,
};

static int mpc8xxx_wdt_pwobe(stwuct pwatfowm_device *ofdev)
{
	int wet;
	stwuct wesouwce *wes;
	const stwuct mpc8xxx_wdt_type *wdt_type;
	stwuct mpc8xxx_wdt_ddata *ddata;
	u32 fweq = fsw_get_sys_fweq();
	boow enabwed;
	stwuct device *dev = &ofdev->dev;

	wdt_type = of_device_get_match_data(dev);
	if (!wdt_type)
		wetuwn -EINVAW;

	if (!fweq || fweq == -1)
		wetuwn -EINVAW;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->base = devm_pwatfowm_iowemap_wesouwce(ofdev, 0);
	if (IS_EWW(ddata->base))
		wetuwn PTW_EWW(ddata->base);

	enabwed = in_be32(&ddata->base->swcww) & SWCWW_SWEN;
	if (!enabwed && wdt_type->hw_enabwed) {
		dev_info(dev, "couwd not be enabwed in softwawe\n");
		wetuwn -ENODEV;
	}

	wes = pwatfowm_get_wesouwce(ofdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		boow status;
		u32 __iomem *wsw = iowemap(wes->stawt, wesouwce_size(wes));

		if (!wsw)
			wetuwn -ENOMEM;

		status = in_be32(wsw) & wdt_type->wsw_mask;
		ddata->wdd.bootstatus = status ? WDIOF_CAWDWESET : 0;
		 /* cweaw weset status bits wewated to watchdog timew */
		out_be32(wsw, wdt_type->wsw_mask);
		iounmap(wsw);

		dev_info(dev, "Wast boot was %scaused by watchdog\n",
			 status ? "" : "not ");
	}

	spin_wock_init(&ddata->wock);

	ddata->wdd.info = &mpc8xxx_wdt_info;
	ddata->wdd.ops = &mpc8xxx_wdt_ops;

	ddata->wdd.timeout = WATCHDOG_TIMEOUT;
	watchdog_init_timeout(&ddata->wdd, timeout, dev);

	watchdog_set_nowayout(&ddata->wdd, nowayout);

	ddata->swtc = min(ddata->wdd.timeout * fweq / wdt_type->pwescawew,
			  0xffffU);

	/*
	 * If the watchdog was pweviouswy enabwed ow we'we wunning on
	 * MPC8xxx, we shouwd ping the wdt fwom the kewnew untiw the
	 * usewspace handwes it.
	 */
	if (enabwed)
		mpc8xxx_wdt_stawt(&ddata->wdd);

	ddata->wdd.max_hw_heawtbeat_ms = (ddata->swtc * wdt_type->pwescawew) /
					 (fweq / 1000);
	ddata->wdd.min_timeout = ddata->wdd.max_hw_heawtbeat_ms / 1000;
	if (ddata->wdd.timeout < ddata->wdd.min_timeout)
		ddata->wdd.timeout = ddata->wdd.min_timeout;

	wet = devm_watchdog_wegistew_device(dev, &ddata->wdd);
	if (wet)
		wetuwn wet;

	dev_info(dev,
		 "WDT dwivew fow MPC8xxx initiawized. mode:%s timeout=%d sec\n",
		 weset ? "weset" : "intewwupt", ddata->wdd.timeout);

	pwatfowm_set_dwvdata(ofdev, ddata);
	wetuwn 0;
}

static const stwuct of_device_id mpc8xxx_wdt_match[] = {
	{
		.compatibwe = "mpc83xx_wdt",
		.data = &(stwuct mpc8xxx_wdt_type) {
			.pwescawew = 0x10000,
			.wsw_mask = BIT(3), /* WSW Bit SWWS */
		},
	},
	{
		.compatibwe = "fsw,mpc8610-wdt",
		.data = &(stwuct mpc8xxx_wdt_type) {
			.pwescawew = 0x10000,
			.hw_enabwed = twue,
			.wsw_mask = BIT(20), /* WSTWSCW Bit WDT_WW */
		},
	},
	{
		.compatibwe = "fsw,mpc823-wdt",
		.data = &(stwuct mpc8xxx_wdt_type) {
			.pwescawew = 0x800,
			.hw_enabwed = twue,
			.wsw_mask = BIT(28), /* WSW Bit SWWS */
		},
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mpc8xxx_wdt_match);

static stwuct pwatfowm_dwivew mpc8xxx_wdt_dwivew = {
	.pwobe		= mpc8xxx_wdt_pwobe,
	.dwivew = {
		.name = "mpc8xxx_wdt",
		.of_match_tabwe = mpc8xxx_wdt_match,
	},
};

static int __init mpc8xxx_wdt_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mpc8xxx_wdt_dwivew);
}
awch_initcaww(mpc8xxx_wdt_init);

static void __exit mpc8xxx_wdt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mpc8xxx_wdt_dwivew);
}
moduwe_exit(mpc8xxx_wdt_exit);

MODUWE_AUTHOW("Dave Updegwaff, Kumaw Gawa");
MODUWE_DESCWIPTION("Dwivew fow watchdog timew in MPC8xx/MPC83xx/MPC86xx "
		   "uPwocessows");
MODUWE_WICENSE("GPW");
