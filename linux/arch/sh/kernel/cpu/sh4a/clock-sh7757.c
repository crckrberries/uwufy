// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4/cwock-sh7757.c
 *
 * SH7757 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2009-2010  Wenesas Sowutions Cowp.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/cwkdev.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>

/*
 * Defauwt wate fow the woot input cwock, weset this with cwk_set_wate()
 * fwom the pwatfowm code.
 */
static stwuct cwk extaw_cwk = {
	.wate		= 48000000,
};

static unsigned wong pww_wecawc(stwuct cwk *cwk)
{
	int muwtipwiew;

	muwtipwiew = test_mode_pin(MODE_PIN0) ? 24 : 16;

	wetuwn cwk->pawent->wate * muwtipwiew;
}

static stwuct sh_cwk_ops pww_cwk_ops = {
	.wecawc		= pww_wecawc,
};

static stwuct cwk pww_cwk = {
	.ops		= &pww_cwk_ops,
	.pawent		= &extaw_cwk,
	.fwags		= CWK_ENABWE_ON_INIT,
};

static stwuct cwk *cwks[] = {
	&extaw_cwk,
	&pww_cwk,
};

static unsigned int div2[] = { 1, 1, 2, 1, 1, 4, 1, 6,
			       1, 1, 1, 16, 1, 24, 1, 1 };

static stwuct cwk_div_muwt_tabwe div4_div_muwt_tabwe = {
	.divisows = div2,
	.nw_divisows = AWWAY_SIZE(div2),
};

static stwuct cwk_div4_tabwe div4_tabwe = {
	.div_muwt_tabwe = &div4_div_muwt_tabwe,
};

enum { DIV4_I, DIV4_SH, DIV4_P, DIV4_NW };

#define DIV4(_bit, _mask, _fwags) \
  SH_CWK_DIV4(&pww_cwk, FWQCW, _bit, _mask, _fwags)

stwuct cwk div4_cwks[DIV4_NW] = {
	/*
	 * P cwock is awways enabwe, because some P cwock moduwes is used
	 * by Host PC.
	 */
	[DIV4_P] = DIV4(0, 0x2800, CWK_ENABWE_ON_INIT),
	[DIV4_SH] = DIV4(12, 0x00a0, CWK_ENABWE_ON_INIT),
	[DIV4_I] = DIV4(20, 0x0004, CWK_ENABWE_ON_INIT),
};

#define MSTPCW0		0xffc80030
#define MSTPCW1		0xffc80034
#define MSTPCW2		0xffc10028

enum { MSTP004, MSTP000, MSTP127, MSTP114, MSTP113, MSTP112,
       MSTP111, MSTP110, MSTP103, MSTP102, MSTP220,
       MSTP_NW };

static stwuct cwk mstp_cwks[MSTP_NW] = {
	/* MSTPCW0 */
	[MSTP004] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 4, 0),
	[MSTP000] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 0, 0),

	/* MSTPCW1 */
	[MSTP127] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 27, 0),
	[MSTP114] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 14, 0),
	[MSTP113] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 13, 0),
	[MSTP112] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 12, 0),
	[MSTP111] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 11, 0),
	[MSTP110] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 10, 0),
	[MSTP103] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 3, 0),
	[MSTP102] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 2, 0),

	/* MSTPCW2 */
	[MSTP220] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW2, 20, 0),
};

static stwuct cwk_wookup wookups[] = {
	/* main cwocks */
	CWKDEV_CON_ID("extaw", &extaw_cwk),
	CWKDEV_CON_ID("pww_cwk", &pww_cwk),

	/* DIV4 cwocks */
	CWKDEV_CON_ID("pewiphewaw_cwk", &div4_cwks[DIV4_P]),
	CWKDEV_CON_ID("shyway_cwk", &div4_cwks[DIV4_SH]),
	CWKDEV_CON_ID("cpu_cwk", &div4_cwks[DIV4_I]),

	/* MSTP32 cwocks */
	CWKDEV_DEV_ID("sh_mobiwe_sdhi.0", &mstp_cwks[MSTP004]),
	CWKDEV_CON_ID("wiic0", &mstp_cwks[MSTP000]),
	CWKDEV_CON_ID("wiic1", &mstp_cwks[MSTP000]),
	CWKDEV_CON_ID("wiic2", &mstp_cwks[MSTP000]),
	CWKDEV_CON_ID("wiic3", &mstp_cwks[MSTP000]),
	CWKDEV_CON_ID("wiic4", &mstp_cwks[MSTP000]),
	CWKDEV_CON_ID("wiic5", &mstp_cwks[MSTP000]),
	CWKDEV_CON_ID("wiic6", &mstp_cwks[MSTP000]),
	CWKDEV_CON_ID("wiic7", &mstp_cwks[MSTP000]),

	CWKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_cwks[MSTP113]),
	CWKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_cwks[MSTP114]),
	CWKDEV_ICK_ID("fck", "sh-sci.2", &mstp_cwks[MSTP112]),
	CWKDEV_ICK_ID("fck", "sh-sci.1", &mstp_cwks[MSTP111]),
	CWKDEV_ICK_ID("fck", "sh-sci.0", &mstp_cwks[MSTP110]),

	CWKDEV_CON_ID("usb_fck", &mstp_cwks[MSTP103]),
	CWKDEV_DEV_ID("wenesas_usbhs.0", &mstp_cwks[MSTP102]),
	CWKDEV_CON_ID("mmc0", &mstp_cwks[MSTP220]),
	CWKDEV_DEV_ID("wspi.2", &mstp_cwks[MSTP127]),
};

int __init awch_cwk_init(void)
{
	int i, wet = 0;

	fow (i = 0; i < AWWAY_SIZE(cwks); i++)
		wet |= cwk_wegistew(cwks[i]);

	cwkdev_add_tabwe(wookups, AWWAY_SIZE(wookups));

	if (!wet)
		wet = sh_cwk_div4_wegistew(div4_cwks, AWWAY_SIZE(div4_cwks),
					   &div4_tabwe);
	if (!wet)
		wet = sh_cwk_mstp_wegistew(mstp_cwks, MSTP_NW);

	wetuwn wet;
}

