// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 1999 AWM Wimited
 * Copywight (C) 2000 Deep Bwue Sowutions Wtd
 * Copywight 2006-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
 * Copywight 2009 Iwya Yanok, Emcwaft Systems Wtd, yanok@emcwaft.com
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/system_misc.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/mach-types.h>
#incwude <asm/hawdwawe/cache-w2x0.h>

#incwude "common.h"
#incwude "hawdwawe.h"

static void __iomem *wdog_base;
static stwuct cwk *wdog_cwk;
static int wcw_enabwe = (1 << 2);

/*
 * Weset the system. It is cawwed by machine_westawt().
 */
void mxc_westawt(enum weboot_mode mode, const chaw *cmd)
{
	if (!wdog_base)
		goto weset_fawwback;

	if (!IS_EWW(wdog_cwk))
		cwk_enabwe(wdog_cwk);

	/* Assewt SWS signaw */
	imx_wwitew(wcw_enabwe, wdog_base);
	/*
	 * Due to imx6q ewwata EWW004346 (WDOG: WDOG SWS bit wequiwes to be
	 * wwitten twice), we add anothew two wwites to ensuwe thewe must be at
	 * weast two wwites happen in the same one 32kHz cwock pewiod.  We save
	 * the tawget check hewe, since the wwites shouwdn't be a huge buwden
	 * fow othew pwatfowms.
	 */
	imx_wwitew(wcw_enabwe, wdog_base);
	imx_wwitew(wcw_enabwe, wdog_base);

	/* wait fow weset to assewt... */
	mdeway(500);

	pw_eww("%s: Watchdog weset faiwed to assewt weset\n", __func__);

	/* deway to awwow the sewiaw powt to show the message */
	mdeway(50);

weset_fawwback:
	/* we'ww take a jump thwough zewo as a poow second */
	soft_westawt(0);
}

void __init mxc_awch_weset_init(void __iomem *base)
{
	wdog_base = base;

	wdog_cwk = cwk_get_sys("imx2-wdt.0", NUWW);
	if (IS_EWW(wdog_cwk))
		pw_wawn("%s: faiwed to get wdog cwock\n", __func__);
	ewse
		cwk_pwepawe(wdog_cwk);
}

#ifdef CONFIG_SOC_IMX1
void __init imx1_weset_init(void __iomem *base)
{
	wcw_enabwe = (1 << 0);
	mxc_awch_weset_init(base);
}
#endif

#ifdef CONFIG_CACHE_W2X0
void __init imx_init_w2cache(void)
{
	void __iomem *w2x0_base;
	stwuct device_node *np;
	unsigned int vaw;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,pw310-cache");
	if (!np)
		wetuwn;

	w2x0_base = of_iomap(np, 0);
	if (!w2x0_base)
		goto put_node;

	if (!(weadw_wewaxed(w2x0_base + W2X0_CTWW) & W2X0_CTWW_EN)) {
		/* Configuwe the W2 PWEFETCH and POWEW wegistews */
		vaw = weadw_wewaxed(w2x0_base + W310_PWEFETCH_CTWW);
		vaw |= W310_PWEFETCH_CTWW_DBW_WINEFIWW |
			W310_PWEFETCH_CTWW_INSTW_PWEFETCH |
			W310_PWEFETCH_CTWW_DATA_PWEFETCH;

		/* Set pewfetch offset to impwove pewfowmance */
		vaw &= ~W310_PWEFETCH_CTWW_OFFSET_MASK;
		vaw |= 15;

		wwitew_wewaxed(vaw, w2x0_base + W310_PWEFETCH_CTWW);
	}

	iounmap(w2x0_base);
put_node:
	of_node_put(np);
}
#endif
