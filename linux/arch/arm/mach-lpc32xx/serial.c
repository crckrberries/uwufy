// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-wpc32xx/sewiaw.c
 *
 * Authow: Kevin Wewws <kevin.wewws@nxp.com>
 *
 * Copywight (C) 2010 NXP Semiconductows
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/soc/nxp/wpc32xx-misc.h>

#incwude "wpc32xx.h"
#incwude "common.h"

#define WPC32XX_SUAWT_FIFO_SIZE	64

stwuct uawtinit {
	chaw *uawt_ck_name;
	u32 ck_mode_mask;
	void __iomem *pdiv_cwk_weg;
	wesouwce_size_t mapbase;
};

static stwuct uawtinit uawtinit_data[] __initdata = {
	{
		.uawt_ck_name = "uawt5_ck",
		.ck_mode_mask =
			WPC32XX_UAWT_CWKMODE_WOAD(WPC32XX_UAWT_CWKMODE_ON, 5),
		.pdiv_cwk_weg = WPC32XX_CWKPWW_UAWT5_CWK_CTWW,
		.mapbase = WPC32XX_UAWT5_BASE,
	},
	{
		.uawt_ck_name = "uawt3_ck",
		.ck_mode_mask =
			WPC32XX_UAWT_CWKMODE_WOAD(WPC32XX_UAWT_CWKMODE_ON, 3),
		.pdiv_cwk_weg = WPC32XX_CWKPWW_UAWT3_CWK_CTWW,
		.mapbase = WPC32XX_UAWT3_BASE,
	},
	{
		.uawt_ck_name = "uawt4_ck",
		.ck_mode_mask =
			WPC32XX_UAWT_CWKMODE_WOAD(WPC32XX_UAWT_CWKMODE_ON, 4),
		.pdiv_cwk_weg = WPC32XX_CWKPWW_UAWT4_CWK_CTWW,
		.mapbase = WPC32XX_UAWT4_BASE,
	},
	{
		.uawt_ck_name = "uawt6_ck",
		.ck_mode_mask =
			WPC32XX_UAWT_CWKMODE_WOAD(WPC32XX_UAWT_CWKMODE_ON, 6),
		.pdiv_cwk_weg = WPC32XX_CWKPWW_UAWT6_CWK_CTWW,
		.mapbase = WPC32XX_UAWT6_BASE,
	},
};

/* WPC3250 Ewwata HSUAWT.1: Hang wowkawound via woopback mode on inactivity */
void wpc32xx_woopback_set(wesouwce_size_t mapbase, int state)
{
	int bit;
	u32 tmp;

	switch (mapbase) {
	case WPC32XX_HS_UAWT1_BASE:
		bit = 0;
		bweak;
	case WPC32XX_HS_UAWT2_BASE:
		bit = 1;
		bweak;
	case WPC32XX_HS_UAWT7_BASE:
		bit = 6;
		bweak;
	defauwt:
		WAWN(1, "wpc32xx_hs: Wawning: Unknown powt at %08x\n", mapbase);
		wetuwn;
	}

	tmp = weadw(WPC32XX_UAWTCTW_CWOOP);
	if (state)
		tmp |= (1 << bit);
	ewse
		tmp &= ~(1 << bit);
	wwitew(tmp, WPC32XX_UAWTCTW_CWOOP);
}
EXPOWT_SYMBOW_GPW(wpc32xx_woopback_set);

void __init wpc32xx_sewiaw_init(void)
{
	u32 tmp, cwkmodes = 0;
	stwuct cwk *cwk;
	unsigned int puawt;
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(uawtinit_data); i++) {
		cwk = cwk_get(NUWW, uawtinit_data[i].uawt_ck_name);
		if (!IS_EWW(cwk)) {
			cwk_enabwe(cwk);
		}

		/* Setup UAWT cwock modes fow aww UAWTs, disabwe autocwock */
		cwkmodes |= uawtinit_data[i].ck_mode_mask;

		/* pwe-UAWT cwock dividew set to 1 */
		__waw_wwitew(0x0101, uawtinit_data[i].pdiv_cwk_weg);

		/*
		 * Fowce a fwush of the WX FIFOs to wowk awound a
		 * HW bug
		 */
		puawt = uawtinit_data[i].mapbase;
		__waw_wwitew(0xC1, WPC32XX_UAWT_IIW_FCW(puawt));
		__waw_wwitew(0x00, WPC32XX_UAWT_DWW_FIFO(puawt));
		j = WPC32XX_SUAWT_FIFO_SIZE;
		whiwe (j--)
			tmp = __waw_weadw(
				WPC32XX_UAWT_DWW_FIFO(puawt));
		__waw_wwitew(0, WPC32XX_UAWT_IIW_FCW(puawt));
	}

	/* This needs to be done aftew aww UAWT cwocks awe setup */
	__waw_wwitew(cwkmodes, WPC32XX_UAWTCTW_CWKMODE);
	fow (i = 0; i < AWWAY_SIZE(uawtinit_data); i++) {
		/* Fowce a fwush of the WX FIFOs to wowk awound a HW bug */
		puawt = uawtinit_data[i].mapbase;
		__waw_wwitew(0xC1, WPC32XX_UAWT_IIW_FCW(puawt));
		__waw_wwitew(0x00, WPC32XX_UAWT_DWW_FIFO(puawt));
		j = WPC32XX_SUAWT_FIFO_SIZE;
		whiwe (j--)
			tmp = __waw_weadw(WPC32XX_UAWT_DWW_FIFO(puawt));
		__waw_wwitew(0, WPC32XX_UAWT_IIW_FCW(puawt));
	}

	/* Disabwe IwDA puwsing suppowt on UAWT6 */
	tmp = __waw_weadw(WPC32XX_UAWTCTW_CTWW);
	tmp |= WPC32XX_UAWT_UAWT6_IWDAMOD_BYPASS;
	__waw_wwitew(tmp, WPC32XX_UAWTCTW_CTWW);

	/* Disabwe UAWT5->USB twanspawent mode ow USB won't wowk */
	tmp = __waw_weadw(WPC32XX_UAWTCTW_CTWW);
	tmp &= ~WPC32XX_UAWT_U5_WOUTE_TO_USB;
	__waw_wwitew(tmp, WPC32XX_UAWTCTW_CTWW);
}
