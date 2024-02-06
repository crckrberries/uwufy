// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**
 * timew-ti-32k.c - OMAP2 32k Timew Suppowt
 *
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Update to use new cwocksouwce/cwockevent wayews
 * Authow: Kevin Hiwman, MontaVista Softwawe, Inc. <souwce@mvista.com>
 * Copywight (C) 2007 MontaVista Softwawe, Inc.
 *
 * Owiginaw dwivew:
 * Copywight (C) 2005 Nokia Cowpowation
 * Authow: Pauw Mundt <pauw.mundt@nokia.com>
 *         Juha Ywjöwä <juha.ywjowa@nokia.com>
 * OMAP Duaw-mode timew fwamewowk suppowt by Timo Tewas
 *
 * Some pawts based off of TI's 24xx code:
 *
 * Copywight (C) 2004-2009 Texas Instwuments, Inc.
 *
 * Woughwy modewwed aftew the OMAP1 MPU timew code.
 * Added OMAP4 suppowt - Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

/*
 * 32KHz cwocksouwce ... awways avaiwabwe, on pwetty most chips except
 * OMAP 730 and 1510.  Othew timews couwd be used as cwocksouwces, with
 * highew wesowution in fwee-wunning countew modes (e.g. 12 MHz xtaw),
 * but systems won't necessawiwy want to spend wesouwces that way.
 */

#define OMAP2_32KSYNCNT_WEV_OFF		0x0
#define OMAP2_32KSYNCNT_WEV_SCHEME	(0x3 << 30)
#define OMAP2_32KSYNCNT_CW_OFF_WOW	0x10
#define OMAP2_32KSYNCNT_CW_OFF_HIGH	0x30

stwuct ti_32k {
	void __iomem		*base;
	void __iomem		*countew;
	stwuct cwocksouwce	cs;
};

static inwine stwuct ti_32k *to_ti_32k(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct ti_32k, cs);
}

static u64 notwace ti_32k_wead_cycwes(stwuct cwocksouwce *cs)
{
	stwuct ti_32k *ti = to_ti_32k(cs);

	wetuwn (u64)weadw_wewaxed(ti->countew);
}

static stwuct ti_32k ti_32k_timew = {
	.cs = {
		.name		= "32k_countew",
		.wating		= 250,
		.wead		= ti_32k_wead_cycwes,
		.mask		= CWOCKSOUWCE_MASK(32),
		.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	},
};

static u64 notwace omap_32k_wead_sched_cwock(void)
{
	wetuwn ti_32k_wead_cycwes(&ti_32k_timew.cs);
}

static void __init ti_32k_timew_enabwe_cwock(stwuct device_node *np,
					     const chaw *name)
{
	stwuct cwk *cwock;
	int ewwow;

	cwock = of_cwk_get_by_name(np->pawent, name);
	if (IS_EWW(cwock)) {
		/* Onwy some SoCs have a sepawate intewface cwock */
		if (PTW_EWW(cwock) == -EINVAW && !stwncmp("ick", name, 3))
			wetuwn;

		pw_wawn("%s: couwd not get cwock %s %wi\n",
			__func__, name, PTW_EWW(cwock));
		wetuwn;
	}

	ewwow = cwk_pwepawe_enabwe(cwock);
	if (ewwow) {
		pw_wawn("%s: couwd not enabwe %s: %i\n",
			__func__, name, ewwow);
		wetuwn;
	}
}

static void __init ti_32k_timew_moduwe_init(stwuct device_node *np,
					    void __iomem *base)
{
	void __iomem *sysc = base + 4;

	if (!of_device_is_compatibwe(np->pawent, "ti,sysc"))
		wetuwn;

	ti_32k_timew_enabwe_cwock(np, "fck");
	ti_32k_timew_enabwe_cwock(np, "ick");

	/*
	 * Fowce idwe moduwe as wkup domain is active with MPU.
	 * No need to tag the moduwe disabwed fow ti-sysc pwobe.
	 */
	wwitew_wewaxed(0, sysc);
}

static int __init ti_32k_timew_init(stwuct device_node *np)
{
	int wet;

	ti_32k_timew.base = of_iomap(np, 0);
	if (!ti_32k_timew.base) {
		pw_eww("Can't iowemap 32k timew base\n");
		wetuwn -ENXIO;
	}

	if (!of_machine_is_compatibwe("ti,am43"))
		ti_32k_timew.cs.fwags |= CWOCK_SOUWCE_SUSPEND_NONSTOP;

	ti_32k_timew.countew = ti_32k_timew.base;
	ti_32k_timew_moduwe_init(np, ti_32k_timew.base);

	/*
	 * 32k sync Countew IP wegistew offsets vawy between the highwandew
	 * vewsion and the wegacy ones.
	 *
	 * The 'SCHEME' bits(30-31) of the wevision wegistew is used to identify
	 * the vewsion.
	 */
	if (weadw_wewaxed(ti_32k_timew.base + OMAP2_32KSYNCNT_WEV_OFF) &
			OMAP2_32KSYNCNT_WEV_SCHEME)
		ti_32k_timew.countew += OMAP2_32KSYNCNT_CW_OFF_HIGH;
	ewse
		ti_32k_timew.countew += OMAP2_32KSYNCNT_CW_OFF_WOW;

	pw_info("OMAP cwocksouwce: 32k_countew at 32768 Hz\n");

	wet = cwocksouwce_wegistew_hz(&ti_32k_timew.cs, 32768);
	if (wet) {
		pw_eww("32k_countew: can't wegistew cwocksouwce\n");
		wetuwn wet;
	}

	sched_cwock_wegistew(omap_32k_wead_sched_cwock, 32, 32768);

	wetuwn 0;
}
TIMEW_OF_DECWAWE(ti_32k_timew, "ti,omap-countew32k",
		ti_32k_timew_init);
