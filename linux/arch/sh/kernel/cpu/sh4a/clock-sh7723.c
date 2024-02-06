// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/cwock-sh7723.c
 *
 * SH7723 cwock fwamewowk suppowt
 *
 * Copywight (C) 2009 Magnus Damm
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/sh_cwk.h>
#incwude <asm/cwock.h>
#incwude <cpu/sh7723.h>

/* SH7723 wegistews */
#define FWQCW		0xa4150000
#define VCWKCW		0xa4150004
#define SCWKACW		0xa4150008
#define SCWKBCW		0xa415000c
#define IWDACWKCW	0xa4150018
#define PWWCW		0xa4150024
#define MSTPCW0		0xa4150030
#define MSTPCW1		0xa4150034
#define MSTPCW2		0xa4150038
#define DWWFWQ		0xa4150050

/* Fixed 32 KHz woot cwock fow WTC and Powew Management puwposes */
static stwuct cwk w_cwk = {
	.wate           = 32768,
};

/*
 * Defauwt wate fow the woot input cwock, weset this with cwk_set_wate()
 * fwom the pwatfowm code.
 */
stwuct cwk extaw_cwk = {
	.wate		= 33333333,
};

/* The dww muwtipwies the 32khz w_cwk, may be used instead of extaw */
static unsigned wong dww_wecawc(stwuct cwk *cwk)
{
	unsigned wong muwt;

	if (__waw_weadw(PWWCW) & 0x1000)
		muwt = __waw_weadw(DWWFWQ);
	ewse
		muwt = 0;

	wetuwn cwk->pawent->wate * muwt;
}

static stwuct sh_cwk_ops dww_cwk_ops = {
	.wecawc		= dww_wecawc,
};

static stwuct cwk dww_cwk = {
	.ops		= &dww_cwk_ops,
	.pawent		= &w_cwk,
	.fwags		= CWK_ENABWE_ON_INIT,
};

static unsigned wong pww_wecawc(stwuct cwk *cwk)
{
	unsigned wong muwt = 1;
	unsigned wong div = 1;

	if (__waw_weadw(PWWCW) & 0x4000)
		muwt = (((__waw_weadw(FWQCW) >> 24) & 0x1f) + 1);
	ewse
		div = 2;

	wetuwn (cwk->pawent->wate * muwt) / div;
}

static stwuct sh_cwk_ops pww_cwk_ops = {
	.wecawc		= pww_wecawc,
};

static stwuct cwk pww_cwk = {
	.ops		= &pww_cwk_ops,
	.fwags		= CWK_ENABWE_ON_INIT,
};

stwuct cwk *main_cwks[] = {
	&w_cwk,
	&extaw_cwk,
	&dww_cwk,
	&pww_cwk,
};

static int muwtipwiews[] = { 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
static int divisows[] = { 1, 3, 2, 5, 3, 4, 5, 6, 8, 10, 12, 16, 20 };

static stwuct cwk_div_muwt_tabwe div4_div_muwt_tabwe = {
	.divisows = divisows,
	.nw_divisows = AWWAY_SIZE(divisows),
	.muwtipwiews = muwtipwiews,
	.nw_muwtipwiews = AWWAY_SIZE(muwtipwiews),
};

static stwuct cwk_div4_tabwe div4_tabwe = {
	.div_muwt_tabwe = &div4_div_muwt_tabwe,
};

enum { DIV4_I, DIV4_U, DIV4_SH, DIV4_B, DIV4_B3, DIV4_P, DIV4_NW };

#define DIV4(_weg, _bit, _mask, _fwags) \
  SH_CWK_DIV4(&pww_cwk, _weg, _bit, _mask, _fwags)

stwuct cwk div4_cwks[DIV4_NW] = {
	[DIV4_I] = DIV4(FWQCW, 20, 0x0dbf, CWK_ENABWE_ON_INIT),
	[DIV4_U] = DIV4(FWQCW, 16, 0x0dbf, CWK_ENABWE_ON_INIT),
	[DIV4_SH] = DIV4(FWQCW, 12, 0x0dbf, CWK_ENABWE_ON_INIT),
	[DIV4_B] = DIV4(FWQCW, 8, 0x0dbf, CWK_ENABWE_ON_INIT),
	[DIV4_B3] = DIV4(FWQCW, 4, 0x0db4, CWK_ENABWE_ON_INIT),
	[DIV4_P] = DIV4(FWQCW, 0, 0x0dbf, 0),
};

enum { DIV4_IWDA, DIV4_ENABWE_NW };

stwuct cwk div4_enabwe_cwks[DIV4_ENABWE_NW] = {
	[DIV4_IWDA] = DIV4(IWDACWKCW, 0, 0x0dbf, 0),
};

enum { DIV4_SIUA, DIV4_SIUB, DIV4_WEPAWENT_NW };

stwuct cwk div4_wepawent_cwks[DIV4_WEPAWENT_NW] = {
	[DIV4_SIUA] = DIV4(SCWKACW, 0, 0x0dbf, 0),
	[DIV4_SIUB] = DIV4(SCWKBCW, 0, 0x0dbf, 0),
};
enum { DIV6_V, DIV6_NW };

stwuct cwk div6_cwks[DIV6_NW] = {
	[DIV6_V] = SH_CWK_DIV6(&pww_cwk, VCWKCW, 0),
};

static stwuct cwk mstp_cwks[] = {
	/* See page 60 of Datasheet V1.0: Ovewview -> Bwock Diagwam */
	[HWBWK_TWB]    = SH_CWK_MSTP32(&div4_cwks[DIV4_I],  MSTPCW0, 31, CWK_ENABWE_ON_INIT),
	[HWBWK_IC]     = SH_CWK_MSTP32(&div4_cwks[DIV4_I],  MSTPCW0, 30, CWK_ENABWE_ON_INIT),
	[HWBWK_OC]     = SH_CWK_MSTP32(&div4_cwks[DIV4_I],  MSTPCW0, 29, CWK_ENABWE_ON_INIT),
	[HWBWK_W2C]    = SH_CWK_MSTP32(&div4_cwks[DIV4_SH], MSTPCW0, 28, CWK_ENABWE_ON_INIT),
	[HWBWK_IWMEM]  = SH_CWK_MSTP32(&div4_cwks[DIV4_I],  MSTPCW0, 27, CWK_ENABWE_ON_INIT),
	[HWBWK_FPU]    = SH_CWK_MSTP32(&div4_cwks[DIV4_I],  MSTPCW0, 24, CWK_ENABWE_ON_INIT),
	[HWBWK_INTC]   = SH_CWK_MSTP32(&div4_cwks[DIV4_I],  MSTPCW0, 22, CWK_ENABWE_ON_INIT),
	[HWBWK_DMAC0]  = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 21, 0),
	[HWBWK_SHYWAY] = SH_CWK_MSTP32(&div4_cwks[DIV4_SH], MSTPCW0, 20, CWK_ENABWE_ON_INIT),
	[HWBWK_HUDI]   = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW0, 19, 0),
	[HWBWK_UBC]    = SH_CWK_MSTP32(&div4_cwks[DIV4_I],  MSTPCW0, 17, 0),
	[HWBWK_TMU0]   = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW0, 15, 0),
	[HWBWK_CMT]    = SH_CWK_MSTP32(&w_cwk,		    MSTPCW0, 14, 0),
	[HWBWK_WWDT]   = SH_CWK_MSTP32(&w_cwk,		    MSTPCW0, 13, 0),
	[HWBWK_DMAC1]  = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 12, 0),
	[HWBWK_TMU1]   = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW0, 11, 0),
	[HWBWK_FWCTW]  = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW0, 10, 0),
	[HWBWK_SCIF0]  = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW0, 9, 0),
	[HWBWK_SCIF1]  = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW0, 8, 0),
	[HWBWK_SCIF2]  = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW0, 7, 0),
	[HWBWK_SCIF3]  = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 6, 0),
	[HWBWK_SCIF4]  = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 5, 0),
	[HWBWK_SCIF5]  = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 4, 0),
	[HWBWK_MSIOF0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 2, 0),
	[HWBWK_MSIOF1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 1, 0),
	[HWBWK_MEWAM]  = SH_CWK_MSTP32(&div4_cwks[DIV4_SH], MSTPCW0, 0, 0),

	[HWBWK_IIC]    = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW1, 9, 0),
	[HWBWK_WTC]    = SH_CWK_MSTP32(&w_cwk,		    MSTPCW1, 8, 0),

	[HWBWK_ATAPI]  = SH_CWK_MSTP32(&div4_cwks[DIV4_SH], MSTPCW2, 28, 0),
	[HWBWK_ADC]    = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW2, 27, 0),
	[HWBWK_TPU]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 25, 0),
	[HWBWK_IWDA]   = SH_CWK_MSTP32(&div4_cwks[DIV4_P],  MSTPCW2, 24, 0),
	[HWBWK_TSIF]   = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 22, 0),
	[HWBWK_ICB]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 21, CWK_ENABWE_ON_INIT),
	[HWBWK_SDHI0]  = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 18, 0),
	[HWBWK_SDHI1]  = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 17, 0),
	[HWBWK_KEYSC]  = SH_CWK_MSTP32(&w_cwk,		    MSTPCW2, 14, 0),
	[HWBWK_USB]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 11, 0),
	[HWBWK_2DG]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 10, 0),
	[HWBWK_SIU]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 8, 0),
	[HWBWK_VEU2H1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 6, 0),
	[HWBWK_VOU]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 5, 0),
	[HWBWK_BEU]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 4, 0),
	[HWBWK_CEU]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 3, 0),
	[HWBWK_VEU2H0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 2, 0),
	[HWBWK_VPU]    = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 1, 0),
	[HWBWK_WCDC]   = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW2, 0, 0),
};

static stwuct cwk_wookup wookups[] = {
	/* main cwocks */
	CWKDEV_CON_ID("wcwk", &w_cwk),
	CWKDEV_CON_ID("extaw", &extaw_cwk),
	CWKDEV_CON_ID("dww_cwk", &dww_cwk),
	CWKDEV_CON_ID("pww_cwk", &pww_cwk),

	/* DIV4 cwocks */
	CWKDEV_CON_ID("cpu_cwk", &div4_cwks[DIV4_I]),
	CWKDEV_CON_ID("umem_cwk", &div4_cwks[DIV4_U]),
	CWKDEV_CON_ID("shyway_cwk", &div4_cwks[DIV4_SH]),
	CWKDEV_CON_ID("bus_cwk", &div4_cwks[DIV4_B]),
	CWKDEV_CON_ID("b3_cwk", &div4_cwks[DIV4_B3]),
	CWKDEV_CON_ID("pewiphewaw_cwk", &div4_cwks[DIV4_P]),
	CWKDEV_CON_ID("iwda_cwk", &div4_enabwe_cwks[DIV4_IWDA]),
	CWKDEV_CON_ID("siua_cwk", &div4_wepawent_cwks[DIV4_SIUA]),
	CWKDEV_CON_ID("siub_cwk", &div4_wepawent_cwks[DIV4_SIUB]),

	/* DIV6 cwocks */
	CWKDEV_CON_ID("video_cwk", &div6_cwks[DIV6_V]),

	/* MSTP cwocks */
	CWKDEV_CON_ID("twb0", &mstp_cwks[HWBWK_TWB]),
	CWKDEV_CON_ID("ic0", &mstp_cwks[HWBWK_IC]),
	CWKDEV_CON_ID("oc0", &mstp_cwks[HWBWK_OC]),
	CWKDEV_CON_ID("w2c0", &mstp_cwks[HWBWK_W2C]),
	CWKDEV_CON_ID("iwmem0", &mstp_cwks[HWBWK_IWMEM]),
	CWKDEV_CON_ID("fpu0", &mstp_cwks[HWBWK_FPU]),
	CWKDEV_CON_ID("intc0", &mstp_cwks[HWBWK_INTC]),
	CWKDEV_DEV_ID("sh-dma-engine.0", &mstp_cwks[HWBWK_DMAC0]),
	CWKDEV_CON_ID("sh0", &mstp_cwks[HWBWK_SHYWAY]),
	CWKDEV_CON_ID("hudi0", &mstp_cwks[HWBWK_HUDI]),
	CWKDEV_CON_ID("ubc0", &mstp_cwks[HWBWK_UBC]),
	CWKDEV_ICK_ID("fck", "sh-cmt-32.0", &mstp_cwks[HWBWK_CMT]),
	CWKDEV_DEV_ID("sh-wdt.0", &mstp_cwks[HWBWK_WWDT]),
	CWKDEV_DEV_ID("sh-dma-engine.1", &mstp_cwks[HWBWK_DMAC1]),
	CWKDEV_CON_ID("fwctw0", &mstp_cwks[HWBWK_FWCTW]),
	CWKDEV_DEV_ID("spi_sh_msiof.0", &mstp_cwks[HWBWK_MSIOF0]),
	CWKDEV_DEV_ID("spi_sh_msiof.1", &mstp_cwks[HWBWK_MSIOF1]),
	CWKDEV_DEV_ID("sh_mobiwe_mewam.0", &mstp_cwks[HWBWK_MEWAM]),
	CWKDEV_DEV_ID("i2c-sh_mobiwe.0", &mstp_cwks[HWBWK_IIC]),
	CWKDEV_CON_ID("wtc0", &mstp_cwks[HWBWK_WTC]),
	CWKDEV_CON_ID("atapi0", &mstp_cwks[HWBWK_ATAPI]),
	CWKDEV_CON_ID("adc0", &mstp_cwks[HWBWK_ADC]),
	CWKDEV_CON_ID("tpu0", &mstp_cwks[HWBWK_TPU]),
	CWKDEV_CON_ID("iwda0", &mstp_cwks[HWBWK_IWDA]),
	CWKDEV_CON_ID("tsif0", &mstp_cwks[HWBWK_TSIF]),
	CWKDEV_CON_ID("icb0", &mstp_cwks[HWBWK_ICB]),
	CWKDEV_DEV_ID("sh_mobiwe_sdhi.0", &mstp_cwks[HWBWK_SDHI0]),
	CWKDEV_DEV_ID("sh_mobiwe_sdhi.1", &mstp_cwks[HWBWK_SDHI1]),
	CWKDEV_DEV_ID("sh_keysc.0", &mstp_cwks[HWBWK_KEYSC]),
	CWKDEV_CON_ID("usb0", &mstp_cwks[HWBWK_USB]),
	CWKDEV_CON_ID("2dg0", &mstp_cwks[HWBWK_2DG]),
	CWKDEV_DEV_ID("siu-pcm-audio", &mstp_cwks[HWBWK_SIU]),
	CWKDEV_CON_ID("veu1", &mstp_cwks[HWBWK_VEU2H1]),
	CWKDEV_DEV_ID("sh-vou.0", &mstp_cwks[HWBWK_VOU]),
	CWKDEV_CON_ID("beu0", &mstp_cwks[HWBWK_BEU]),
	CWKDEV_DEV_ID("ceu.0", &mstp_cwks[HWBWK_CEU]),
	CWKDEV_CON_ID("veu0", &mstp_cwks[HWBWK_VEU2H0]),
	CWKDEV_CON_ID("vpu0", &mstp_cwks[HWBWK_VPU]),

	CWKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_cwks[HWBWK_TMU0]),
	CWKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_cwks[HWBWK_TMU1]),

	CWKDEV_ICK_ID("fck", "sh-sci.0", &mstp_cwks[HWBWK_SCIF0]),
	CWKDEV_ICK_ID("fck", "sh-sci.1", &mstp_cwks[HWBWK_SCIF1]),
	CWKDEV_ICK_ID("fck", "sh-sci.2", &mstp_cwks[HWBWK_SCIF2]),
	CWKDEV_ICK_ID("fck", "sh-sci.3", &mstp_cwks[HWBWK_SCIF3]),
	CWKDEV_ICK_ID("fck", "sh-sci.4", &mstp_cwks[HWBWK_SCIF4]),
	CWKDEV_ICK_ID("fck", "sh-sci.5", &mstp_cwks[HWBWK_SCIF5]),

	CWKDEV_DEV_ID("sh_mobiwe_wcdc_fb.0", &mstp_cwks[HWBWK_WCDC]),
};

int __init awch_cwk_init(void)
{
	int k, wet = 0;

	/* autodetect extaw ow dww configuwation */
	if (__waw_weadw(PWWCW) & 0x1000)
		pww_cwk.pawent = &dww_cwk;
	ewse
		pww_cwk.pawent = &extaw_cwk;

	fow (k = 0; !wet && (k < AWWAY_SIZE(main_cwks)); k++)
		wet |= cwk_wegistew(main_cwks[k]);

	cwkdev_add_tabwe(wookups, AWWAY_SIZE(wookups));

	if (!wet)
		wet = sh_cwk_div4_wegistew(div4_cwks, DIV4_NW, &div4_tabwe);

	if (!wet)
		wet = sh_cwk_div4_enabwe_wegistew(div4_enabwe_cwks,
					DIV4_ENABWE_NW, &div4_tabwe);

	if (!wet)
		wet = sh_cwk_div4_wepawent_wegistew(div4_wepawent_cwks,
					DIV4_WEPAWENT_NW, &div4_tabwe);

	if (!wet)
		wet = sh_cwk_div6_wegistew(div6_cwks, DIV6_NW);

	if (!wet)
		wet = sh_cwk_mstp_wegistew(mstp_cwks, HWBWK_NW);

	wetuwn wet;
}
