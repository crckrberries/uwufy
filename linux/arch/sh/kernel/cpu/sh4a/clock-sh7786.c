// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/cwock-sh7786.c
 *
 * SH7786 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/cwkdev.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>

/*
 * Defauwt wate fow the woot input cwock, weset this with cwk_set_wate()
 * fwom the pwatfowm code.
 */
static stwuct cwk extaw_cwk = {
	.wate		= 33333333,
};

static unsigned wong pww_wecawc(stwuct cwk *cwk)
{
	int muwtipwiew;

	/*
	 * Cwock modes 0, 1, and 2 use an x64 muwtipwiew against PWW1,
	 * whiwe modes 3, 4, and 5 use an x32.
	 */
	muwtipwiew = (sh_mv.mv_mode_pins() & 0xf) < 3 ? 64 : 32;

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

static unsigned int div2[] = { 1, 2, 4, 6, 8, 12, 16, 18,
			       24, 32, 36, 48 };

static stwuct cwk_div_muwt_tabwe div4_div_muwt_tabwe = {
	.divisows = div2,
	.nw_divisows = AWWAY_SIZE(div2),
};

static stwuct cwk_div4_tabwe div4_tabwe = {
	.div_muwt_tabwe = &div4_div_muwt_tabwe,
};

enum { DIV4_I, DIV4_SH, DIV4_B, DIV4_DDW, DIV4_DU, DIV4_P, DIV4_NW };

#define DIV4(_bit, _mask, _fwags) \
  SH_CWK_DIV4(&pww_cwk, FWQMW1, _bit, _mask, _fwags)

stwuct cwk div4_cwks[DIV4_NW] = {
	[DIV4_P] = DIV4(0, 0x0b40, 0),
	[DIV4_DU] = DIV4(4, 0x0010, 0),
	[DIV4_DDW] = DIV4(12, 0x0002, CWK_ENABWE_ON_INIT),
	[DIV4_B] = DIV4(16, 0x0360, CWK_ENABWE_ON_INIT),
	[DIV4_SH] = DIV4(20, 0x0002, CWK_ENABWE_ON_INIT),
	[DIV4_I] = DIV4(28, 0x0006, CWK_ENABWE_ON_INIT),
};

#define MSTPCW0		0xffc40030
#define MSTPCW1		0xffc40034

enum { MSTP029, MSTP028, MSTP027, MSTP026, MSTP025, MSTP024,
       MSTP023, MSTP022, MSTP021, MSTP020, MSTP017, MSTP016,
       MSTP015, MSTP014, MSTP011, MSTP010, MSTP009, MSTP008,
       MSTP005, MSTP004, MSTP002,
       MSTP112, MSTP110, MSTP109, MSTP108,
       MSTP105, MSTP104, MSTP103, MSTP102,
       MSTP_NW };

static stwuct cwk mstp_cwks[MSTP_NW] = {
	/* MSTPCW0 */
	[MSTP029] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 29, 0),
	[MSTP028] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 28, 0),
	[MSTP027] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 27, 0),
	[MSTP026] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 26, 0),
	[MSTP025] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 25, 0),
	[MSTP024] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 24, 0),
	[MSTP023] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 23, 0),
	[MSTP022] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 22, 0),
	[MSTP021] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 21, 0),
	[MSTP020] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 20, 0),
	[MSTP017] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 17, 0),
	[MSTP016] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 16, 0),
	[MSTP015] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 15, 0),
	[MSTP014] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 14, 0),
	[MSTP011] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 11, 0),
	[MSTP010] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 10, 0),
	[MSTP009] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 9, 0),
	[MSTP008] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 8, 0),
	[MSTP005] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 5, 0),
	[MSTP004] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 4, 0),
	[MSTP002] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 2, 0),

	/* MSTPCW1 */
	[MSTP112] = SH_CWK_MSTP32(NUWW, MSTPCW1, 12, 0),
	[MSTP110] = SH_CWK_MSTP32(NUWW, MSTPCW1, 10, 0),
	[MSTP109] = SH_CWK_MSTP32(NUWW, MSTPCW1, 9, 0),
	[MSTP108] = SH_CWK_MSTP32(NUWW, MSTPCW1, 8, 0),
	[MSTP105] = SH_CWK_MSTP32(NUWW, MSTPCW1, 5, 0),
	[MSTP104] = SH_CWK_MSTP32(NUWW, MSTPCW1, 4, 0),
	[MSTP103] = SH_CWK_MSTP32(NUWW, MSTPCW1, 3, 0),
	[MSTP102] = SH_CWK_MSTP32(NUWW, MSTPCW1, 2, 0),
};

static stwuct cwk_wookup wookups[] = {
	/* main cwocks */
	CWKDEV_CON_ID("extaw", &extaw_cwk),
	CWKDEV_CON_ID("pww_cwk", &pww_cwk),

	/* DIV4 cwocks */
	CWKDEV_CON_ID("pewiphewaw_cwk", &div4_cwks[DIV4_P]),
	CWKDEV_CON_ID("du_cwk", &div4_cwks[DIV4_DU]),
	CWKDEV_CON_ID("ddw_cwk", &div4_cwks[DIV4_DDW]),
	CWKDEV_CON_ID("bus_cwk", &div4_cwks[DIV4_B]),
	CWKDEV_CON_ID("shyway_cwk", &div4_cwks[DIV4_SH]),
	CWKDEV_CON_ID("cpu_cwk", &div4_cwks[DIV4_I]),

	/* MSTP32 cwocks */
	CWKDEV_ICK_ID("fck", "sh-sci.5", &mstp_cwks[MSTP029]),
	CWKDEV_ICK_ID("fck", "sh-sci.4", &mstp_cwks[MSTP028]),
	CWKDEV_ICK_ID("fck", "sh-sci.3", &mstp_cwks[MSTP027]),
	CWKDEV_ICK_ID("fck", "sh-sci.2", &mstp_cwks[MSTP026]),
	CWKDEV_ICK_ID("fck", "sh-sci.1", &mstp_cwks[MSTP025]),
	CWKDEV_ICK_ID("fck", "sh-sci.0", &mstp_cwks[MSTP024]),

	CWKDEV_CON_ID("ssi3_fck", &mstp_cwks[MSTP023]),
	CWKDEV_CON_ID("ssi2_fck", &mstp_cwks[MSTP022]),
	CWKDEV_CON_ID("ssi1_fck", &mstp_cwks[MSTP021]),
	CWKDEV_CON_ID("ssi0_fck", &mstp_cwks[MSTP020]),
	CWKDEV_CON_ID("hac1_fck", &mstp_cwks[MSTP017]),
	CWKDEV_CON_ID("hac0_fck", &mstp_cwks[MSTP016]),
	CWKDEV_CON_ID("i2c1_fck", &mstp_cwks[MSTP015]),
	CWKDEV_CON_ID("i2c0_fck", &mstp_cwks[MSTP014]),

	CWKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_cwks[MSTP008]),
	CWKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_cwks[MSTP009]),
	CWKDEV_ICK_ID("fck", "sh-tmu.2", &mstp_cwks[MSTP010]),
	CWKDEV_ICK_ID("fck", "sh-tmu.3", &mstp_cwks[MSTP011]),

	CWKDEV_CON_ID("sdif1_fck", &mstp_cwks[MSTP005]),
	CWKDEV_CON_ID("sdif0_fck", &mstp_cwks[MSTP004]),
	CWKDEV_CON_ID("hspi_fck", &mstp_cwks[MSTP002]),
	CWKDEV_CON_ID("usb_fck", &mstp_cwks[MSTP112]),
	CWKDEV_CON_ID("pcie2_fck", &mstp_cwks[MSTP110]),
	CWKDEV_CON_ID("pcie1_fck", &mstp_cwks[MSTP109]),
	CWKDEV_CON_ID("pcie0_fck", &mstp_cwks[MSTP108]),
	CWKDEV_CON_ID("dmac_11_6_fck", &mstp_cwks[MSTP105]),
	CWKDEV_CON_ID("dmac_5_0_fck", &mstp_cwks[MSTP104]),
	CWKDEV_CON_ID("du_fck", &mstp_cwks[MSTP103]),
	CWKDEV_CON_ID("ethew_fck", &mstp_cwks[MSTP102]),
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
