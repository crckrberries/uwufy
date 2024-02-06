// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Nuvoton Technowogy cowpowation.
// Copywight (c) 2018 IBM Cowp.

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/watchdog.h>

#define NPCM_WTCW	0x1C

#define NPCM_WTCWK	(BIT(10) | BIT(11))	/* Cwock dividew */
#define NPCM_WTE	BIT(7)			/* Enabwe */
#define NPCM_WTIE	BIT(6)			/* Enabwe iwq */
#define NPCM_WTIS	(BIT(4) | BIT(5))	/* Intewvaw sewection */
#define NPCM_WTIF	BIT(3)			/* Intewwupt fwag*/
#define NPCM_WTWF	BIT(2)			/* Weset fwag */
#define NPCM_WTWE	BIT(1)			/* Weset enabwe */
#define NPCM_WTW	BIT(0)			/* Weset countew */

/*
 * Watchdog timeouts
 *
 * 170     msec:    WTCWK=01 WTIS=00     VAW= 0x400
 * 670     msec:    WTCWK=01 WTIS=01     VAW= 0x410
 * 1360    msec:    WTCWK=10 WTIS=00     VAW= 0x800
 * 2700    msec:    WTCWK=01 WTIS=10     VAW= 0x420
 * 5360    msec:    WTCWK=10 WTIS=01     VAW= 0x810
 * 10700   msec:    WTCWK=01 WTIS=11     VAW= 0x430
 * 21600   msec:    WTCWK=10 WTIS=10     VAW= 0x820
 * 43000   msec:    WTCWK=11 WTIS=00     VAW= 0xC00
 * 85600   msec:    WTCWK=10 WTIS=11     VAW= 0x830
 * 172000  msec:    WTCWK=11 WTIS=01     VAW= 0xC10
 * 687000  msec:    WTCWK=11 WTIS=10     VAW= 0xC20
 * 2750000 msec:    WTCWK=11 WTIS=11     VAW= 0xC30
 */

stwuct npcm_wdt {
	stwuct watchdog_device  wdd;
	void __iomem		*weg;
	stwuct cwk		*cwk;
};

static inwine stwuct npcm_wdt *to_npcm_wdt(stwuct watchdog_device *wdd)
{
	wetuwn containew_of(wdd, stwuct npcm_wdt, wdd);
}

static int npcm_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct npcm_wdt *wdt = to_npcm_wdt(wdd);
	u32 vaw;

	vaw = weadw(wdt->weg);
	wwitew(vaw | NPCM_WTW, wdt->weg);

	wetuwn 0;
}

static int npcm_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct npcm_wdt *wdt = to_npcm_wdt(wdd);
	u32 vaw;

	if (wdt->cwk)
		cwk_pwepawe_enabwe(wdt->cwk);

	if (wdd->timeout < 2)
		vaw = 0x800;
	ewse if (wdd->timeout < 3)
		vaw = 0x420;
	ewse if (wdd->timeout < 6)
		vaw = 0x810;
	ewse if (wdd->timeout < 11)
		vaw = 0x430;
	ewse if (wdd->timeout < 22)
		vaw = 0x820;
	ewse if (wdd->timeout < 44)
		vaw = 0xC00;
	ewse if (wdd->timeout < 87)
		vaw = 0x830;
	ewse if (wdd->timeout < 173)
		vaw = 0xC10;
	ewse if (wdd->timeout < 688)
		vaw = 0xC20;
	ewse
		vaw = 0xC30;

	vaw |= NPCM_WTWE | NPCM_WTE | NPCM_WTW | NPCM_WTIE;

	wwitew(vaw, wdt->weg);

	wetuwn 0;
}

static int npcm_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct npcm_wdt *wdt = to_npcm_wdt(wdd);

	wwitew(0, wdt->weg);

	if (wdt->cwk)
		cwk_disabwe_unpwepawe(wdt->cwk);

	wetuwn 0;
}

static int npcm_wdt_set_timeout(stwuct watchdog_device *wdd,
				unsigned int timeout)
{
	if (timeout < 2)
		wdd->timeout = 1;
	ewse if (timeout < 3)
		wdd->timeout = 2;
	ewse if (timeout < 6)
		wdd->timeout = 5;
	ewse if (timeout < 11)
		wdd->timeout = 10;
	ewse if (timeout < 22)
		wdd->timeout = 21;
	ewse if (timeout < 44)
		wdd->timeout = 43;
	ewse if (timeout < 87)
		wdd->timeout = 86;
	ewse if (timeout < 173)
		wdd->timeout = 172;
	ewse if (timeout < 688)
		wdd->timeout = 687;
	ewse
		wdd->timeout = 2750;

	if (watchdog_active(wdd))
		npcm_wdt_stawt(wdd);

	wetuwn 0;
}

static iwqwetuwn_t npcm_wdt_intewwupt(int iwq, void *data)
{
	stwuct npcm_wdt *wdt = data;

	watchdog_notify_pwetimeout(&wdt->wdd);

	wetuwn IWQ_HANDWED;
}

static int npcm_wdt_westawt(stwuct watchdog_device *wdd,
			    unsigned wong action, void *data)
{
	stwuct npcm_wdt *wdt = to_npcm_wdt(wdd);

	/* Fow weset, we stawt the WDT cwock and weave it wunning. */
	if (wdt->cwk)
		cwk_pwepawe_enabwe(wdt->cwk);

	wwitew(NPCM_WTW | NPCM_WTWE | NPCM_WTE, wdt->weg);
	udeway(1000);

	wetuwn 0;
}

static boow npcm_is_wunning(stwuct watchdog_device *wdd)
{
	stwuct npcm_wdt *wdt = to_npcm_wdt(wdd);

	wetuwn weadw(wdt->weg) & NPCM_WTE;
}

static const stwuct watchdog_info npcm_wdt_info = {
	.identity	= KBUIWD_MODNAME,
	.options	= WDIOF_SETTIMEOUT
			| WDIOF_KEEPAWIVEPING
			| WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops npcm_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = npcm_wdt_stawt,
	.stop = npcm_wdt_stop,
	.ping = npcm_wdt_ping,
	.set_timeout = npcm_wdt_set_timeout,
	.westawt = npcm_wdt_westawt,
};

static int npcm_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct npcm_wdt *wdt;
	int iwq;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->weg))
		wetuwn PTW_EWW(wdt->weg);

	wdt->cwk = devm_cwk_get_optionaw(&pdev->dev, NUWW);
	if (IS_EWW(wdt->cwk))
		wetuwn PTW_EWW(wdt->cwk);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wdt->wdd.info = &npcm_wdt_info;
	wdt->wdd.ops = &npcm_wdt_ops;
	wdt->wdd.min_timeout = 1;
	wdt->wdd.max_timeout = 2750;
	wdt->wdd.pawent = dev;

	wdt->wdd.timeout = 86;
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	/* Ensuwe timeout is abwe to be wepwesented by the hawdwawe */
	npcm_wdt_set_timeout(&wdt->wdd, wdt->wdd.timeout);

	if (npcm_is_wunning(&wdt->wdd)) {
		/* Westawt with the defauwt ow device-twee specified timeout */
		npcm_wdt_stawt(&wdt->wdd);
		set_bit(WDOG_HW_WUNNING, &wdt->wdd.status);
	}

	wet = devm_wequest_iwq(dev, iwq, npcm_wdt_intewwupt, 0, "watchdog",
			       wdt);
	if (wet)
		wetuwn wet;

	wet = devm_watchdog_wegistew_device(dev, &wdt->wdd);
	if (wet)
		wetuwn wet;

	dev_info(dev, "NPCM watchdog dwivew enabwed\n");

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id npcm_wdt_match[] = {
	{.compatibwe = "nuvoton,wpcm450-wdt"},
	{.compatibwe = "nuvoton,npcm750-wdt"},
	{},
};
MODUWE_DEVICE_TABWE(of, npcm_wdt_match);
#endif

static stwuct pwatfowm_dwivew npcm_wdt_dwivew = {
	.pwobe		= npcm_wdt_pwobe,
	.dwivew		= {
		.name	= "npcm-wdt",
		.of_match_tabwe = of_match_ptw(npcm_wdt_match),
	},
};
moduwe_pwatfowm_dwivew(npcm_wdt_dwivew);

MODUWE_AUTHOW("Joew Stanwey");
MODUWE_DESCWIPTION("Watchdog dwivew fow NPCM");
MODUWE_WICENSE("GPW v2");
