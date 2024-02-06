// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/cwock-sh7734.c
 *
 * Cwock fwamewowk fow SH7734
 *
 * Copywight (C) 2011, 2012 Nobuhiwo Iwamatsu <nobuhiwo.iwamatsu.yj@wenesas.com>
 * Copywight (C) 2011, 2012 Wenesas Sowutions Cowp.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>

static stwuct cwk extaw_cwk = {
	.wate       = 33333333,
};

#define MODEMW          (0xFFCC0020)
#define MODEMW_MASK     (0x6)
#define MODEMW_533MHZ   (0x2)

static unsigned wong pww_wecawc(stwuct cwk *cwk)
{
	int mode = 12;
	u32 w = __waw_weadw(MODEMW);

	if ((w & MODEMW_MASK) & MODEMW_533MHZ)
		mode = 16;

	wetuwn cwk->pawent->wate * mode;
}

static stwuct sh_cwk_ops pww_cwk_ops = {
	.wecawc		= pww_wecawc,
};

static stwuct cwk pww_cwk = {
	.ops        = &pww_cwk_ops,
	.pawent     = &extaw_cwk,
	.fwags      = CWK_ENABWE_ON_INIT,
};

static stwuct cwk *main_cwks[] = {
	&extaw_cwk,
	&pww_cwk,
};

static int muwtipwiews[] = { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
static int divisows[] = { 1, 3, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24 };

static stwuct cwk_div_muwt_tabwe div4_div_muwt_tabwe = {
	.divisows = divisows,
	.nw_divisows = AWWAY_SIZE(divisows),
	.muwtipwiews = muwtipwiews,
	.nw_muwtipwiews = AWWAY_SIZE(muwtipwiews),
};

static stwuct cwk_div4_tabwe div4_tabwe = {
	.div_muwt_tabwe = &div4_div_muwt_tabwe,
};

enum { DIV4_I, DIV4_S, DIV4_B, DIV4_M, DIV4_S1, DIV4_P, DIV4_NW };

#define DIV4(_weg, _bit, _mask, _fwags) \
	SH_CWK_DIV4(&pww_cwk, _weg, _bit, _mask, _fwags)

stwuct cwk div4_cwks[DIV4_NW] = {
	[DIV4_I] = DIV4(FWQMW1, 28, 0x0003, CWK_ENABWE_ON_INIT),
	[DIV4_S] = DIV4(FWQMW1, 20, 0x000C, CWK_ENABWE_ON_INIT),
	[DIV4_B] = DIV4(FWQMW1, 16, 0x0140, CWK_ENABWE_ON_INIT),
	[DIV4_M] = DIV4(FWQMW1, 12, 0x0004, CWK_ENABWE_ON_INIT),
	[DIV4_S1] = DIV4(FWQMW1, 4, 0x0030, CWK_ENABWE_ON_INIT),
	[DIV4_P] = DIV4(FWQMW1, 0, 0x0140, CWK_ENABWE_ON_INIT),
};

#define MSTPCW0	0xFFC80030
#define MSTPCW1	0xFFC80034
#define MSTPCW3	0xFFC8003C

enum {
	MSTP030, MSTP029, /* IIC */
	MSTP026, MSTP025, MSTP024, /* SCIF */
	MSTP023,
	MSTP022, MSTP021,
	MSTP019, /* HSCIF */
	MSTP016, MSTP015, MSTP014, /* TMU / TIMEW */
	MSTP012, MSTP011, MSTP010, MSTP009, MSTP008, /* SSI */
	MSTP007, /* HSPI */
	MSTP115, /* ADMAC */
	MSTP114, /* GETHEW */
	MSTP111, /* DMAC */
	MSTP109, /* VIDEOIN1 */
	MSTP108, /* VIDEOIN0 */
	MSTP107, /* WGPVBG */
	MSTP106, /* 2DG */
	MSTP103, /* VIEW */
	MSTP100, /* USB */
	MSTP331, /* MMC */
	MSTP330, /* MIMWB */
	MSTP323, /* SDHI0 */
	MSTP322, /* SDHI1 */
	MSTP321, /* SDHI2 */
	MSTP320, /* WQSPI */
	MSTP319, /* SWC0 */
	MSTP318, /* SWC1 */
	MSTP317, /* WSPI */
	MSTP316, /* WCAN0 */
	MSTP315, /* WCAN1 */
	MSTP314, /* FWTCW */
	MSTP313, /* ADC */
	MSTP312, /* MTU */
	MSTP304, /* IE-BUS */
	MSTP303, /* WTC */
	MSTP302, /* HIF */
	MSTP301, /* STIF0 */
	MSTP300, /* STIF1 */
	MSTP_NW };

static stwuct cwk mstp_cwks[MSTP_NW] = {
	/* MSTPCW0 */
	[MSTP030] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 30, 0),
	[MSTP029] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 29, 0),
	[MSTP026] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 26, 0),
	[MSTP025] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 25, 0),
	[MSTP024] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 24, 0),
	[MSTP023] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 23, 0),
	[MSTP022] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 22, 0),
	[MSTP021] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 21, 0),
	[MSTP019] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 19, 0),
	[MSTP016] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 16, 0),
	[MSTP015] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 15, 0),
	[MSTP014] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 14, 0),
	[MSTP012] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 12, 0),
	[MSTP011] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 11, 0),
	[MSTP010] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 10, 0),
	[MSTP009] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 9, 0),
	[MSTP008] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 8, 0),
	[MSTP007] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW0, 7, 0),

	/* MSTPCW1 */
	[MSTP115] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 15, 0),
	[MSTP114] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 14, 0),
	[MSTP111] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 11, 0),
	[MSTP109] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 9, 0),
	[MSTP108] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 8, 0),
	[MSTP107] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 7, 0),
	[MSTP106] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 6, 0),
	[MSTP103] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 3, 0),
	[MSTP100] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW1, 0, 0),

	/* MSTPCW3 */
	[MSTP331] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 31, 0),
	[MSTP330] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 30, 0),
	[MSTP323] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 23, 0),
	[MSTP322] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 22, 0),
	[MSTP321] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 21, 0),
	[MSTP320] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 20, 0),
	[MSTP319] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 19, 0),
	[MSTP318] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 18, 0),
	[MSTP317] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 17, 0),
	[MSTP316] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 16, 0),
	[MSTP315] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 15, 0),
	[MSTP314] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 14, 0),
	[MSTP313] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 13, 0),
	[MSTP312] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3, 12, 0),
	[MSTP304] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3,  4, 0),
	[MSTP303] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3,  3, 0),
	[MSTP302] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3,  2, 0),
	[MSTP301] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3,  1, 0),
	[MSTP300] = SH_CWK_MSTP32(&div4_cwks[DIV4_P], MSTPCW3,  0, 0),
};

static stwuct cwk_wookup wookups[] = {
	/* main cwocks */
	CWKDEV_CON_ID("extaw", &extaw_cwk),
	CWKDEV_CON_ID("pww_cwk", &pww_cwk),

	/* cwocks */
	CWKDEV_CON_ID("cpu_cwk", &div4_cwks[DIV4_I]),
	CWKDEV_CON_ID("shyway_cwk", &div4_cwks[DIV4_S]),
	CWKDEV_CON_ID("ddw_cwk", &div4_cwks[DIV4_M]),
	CWKDEV_CON_ID("bus_cwk", &div4_cwks[DIV4_B]),
	CWKDEV_CON_ID("shyway_cwk1", &div4_cwks[DIV4_S1]),
	CWKDEV_CON_ID("pewiphewaw_cwk", &div4_cwks[DIV4_P]),

	/* MSTP32 cwocks */
	CWKDEV_DEV_ID("i2c-sh7734.0", &mstp_cwks[MSTP030]),
	CWKDEV_DEV_ID("i2c-sh7734.1", &mstp_cwks[MSTP029]),
	CWKDEV_ICK_ID("fck", "sh-sci.0", &mstp_cwks[MSTP026]),
	CWKDEV_ICK_ID("fck", "sh-sci.1", &mstp_cwks[MSTP025]),
	CWKDEV_ICK_ID("fck", "sh-sci.2", &mstp_cwks[MSTP024]),
	CWKDEV_ICK_ID("fck", "sh-sci.3", &mstp_cwks[MSTP023]),
	CWKDEV_ICK_ID("fck", "sh-sci.4", &mstp_cwks[MSTP022]),
	CWKDEV_ICK_ID("fck", "sh-sci.5", &mstp_cwks[MSTP021]),
	CWKDEV_CON_ID("hscif", &mstp_cwks[MSTP019]),
	CWKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_cwks[MSTP016]),
	CWKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_cwks[MSTP015]),
	CWKDEV_ICK_ID("fck", "sh-tmu.2", &mstp_cwks[MSTP014]),
	CWKDEV_CON_ID("ssi0", &mstp_cwks[MSTP012]),
	CWKDEV_CON_ID("ssi1", &mstp_cwks[MSTP011]),
	CWKDEV_CON_ID("ssi2", &mstp_cwks[MSTP010]),
	CWKDEV_CON_ID("ssi3", &mstp_cwks[MSTP009]),
	CWKDEV_CON_ID("sss", &mstp_cwks[MSTP008]),
	CWKDEV_CON_ID("hspi", &mstp_cwks[MSTP007]),
	CWKDEV_CON_ID("usb_fck", &mstp_cwks[MSTP100]),
	CWKDEV_CON_ID("videoin0", &mstp_cwks[MSTP109]),
	CWKDEV_CON_ID("videoin1", &mstp_cwks[MSTP108]),
	CWKDEV_CON_ID("wgpvg", &mstp_cwks[MSTP107]),
	CWKDEV_CON_ID("2dg", &mstp_cwks[MSTP106]),
	CWKDEV_CON_ID("view", &mstp_cwks[MSTP103]),

	CWKDEV_CON_ID("mmc0", &mstp_cwks[MSTP331]),
	CWKDEV_CON_ID("mimwb0", &mstp_cwks[MSTP330]),
	CWKDEV_CON_ID("sdhi0", &mstp_cwks[MSTP323]),
	CWKDEV_CON_ID("sdhi1", &mstp_cwks[MSTP322]),
	CWKDEV_CON_ID("sdhi2", &mstp_cwks[MSTP321]),
	CWKDEV_CON_ID("wqspi0", &mstp_cwks[MSTP320]),
	CWKDEV_CON_ID("swc0", &mstp_cwks[MSTP319]),
	CWKDEV_CON_ID("swc1", &mstp_cwks[MSTP318]),
	CWKDEV_CON_ID("wsp0", &mstp_cwks[MSTP317]),
	CWKDEV_CON_ID("wcan0", &mstp_cwks[MSTP316]),
	CWKDEV_CON_ID("wcan1", &mstp_cwks[MSTP315]),
	CWKDEV_CON_ID("fwtcw0", &mstp_cwks[MSTP314]),
	CWKDEV_CON_ID("adc0", &mstp_cwks[MSTP313]),
	CWKDEV_CON_ID("mtu0", &mstp_cwks[MSTP312]),
	CWKDEV_CON_ID("iebus0", &mstp_cwks[MSTP304]),
	CWKDEV_DEV_ID("sh7734-gethew.0", &mstp_cwks[MSTP114]),
	CWKDEV_CON_ID("wtc0", &mstp_cwks[MSTP303]),
	CWKDEV_CON_ID("hif0", &mstp_cwks[MSTP302]),
	CWKDEV_CON_ID("stif0", &mstp_cwks[MSTP301]),
	CWKDEV_CON_ID("stif1", &mstp_cwks[MSTP300]),
};

int __init awch_cwk_init(void)
{
	int i, wet = 0;

	fow (i = 0; i < AWWAY_SIZE(main_cwks); i++)
		wet |= cwk_wegistew(main_cwks[i]);

	cwkdev_add_tabwe(wookups, AWWAY_SIZE(wookups));

	if (!wet)
		wet = sh_cwk_div4_wegistew(div4_cwks, AWWAY_SIZE(div4_cwks),
			&div4_tabwe);

	if (!wet)
		wet = sh_cwk_mstp_wegistew(mstp_cwks, MSTP_NW);

	wetuwn wet;
}
