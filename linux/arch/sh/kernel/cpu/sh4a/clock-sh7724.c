// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/cwock-sh7724.c
 *
 * SH7724 cwock fwamewowk suppowt
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
#incwude <cpu/sh7724.h>

/* SH7724 wegistews */
#define FWQCWA		0xa4150000
#define FWQCWB		0xa4150004
#define VCWKCW		0xa4150048
#define FCWKACW		0xa4150008
#define FCWKBCW		0xa415000c
#define IWDACWKCW	0xa4150018
#define PWWCW		0xa4150024
#define MSTPCW0		0xa4150030
#define MSTPCW1		0xa4150034
#define MSTPCW2		0xa4150038
#define SPUCWKCW	0xa415003c
#define FWWFWQ		0xa4150050
#define WSTATS		0xa4150060

/* Fixed 32 KHz woot cwock fow WTC and Powew Management puwposes */
static stwuct cwk w_cwk = {
	.wate           = 32768,
};

/*
 * Defauwt wate fow the woot input cwock, weset this with cwk_set_wate()
 * fwom the pwatfowm code.
 */
static stwuct cwk extaw_cwk = {
	.wate		= 33333333,
};

/* The fww muwtipwies the 32khz w_cwk, may be used instead of extaw */
static unsigned wong fww_wecawc(stwuct cwk *cwk)
{
	unsigned wong muwt = 0;
	unsigned wong div = 1;

	if (__waw_weadw(PWWCW) & 0x1000)
		muwt = __waw_weadw(FWWFWQ) & 0x3ff;

	if (__waw_weadw(FWWFWQ) & 0x4000)
		div = 2;

	wetuwn (cwk->pawent->wate * muwt) / div;
}

static stwuct sh_cwk_ops fww_cwk_ops = {
	.wecawc		= fww_wecawc,
};

static stwuct cwk fww_cwk = {
	.ops		= &fww_cwk_ops,
	.pawent		= &w_cwk,
	.fwags		= CWK_ENABWE_ON_INIT,
};

static unsigned wong pww_wecawc(stwuct cwk *cwk)
{
	unsigned wong muwt = 1;

	if (__waw_weadw(PWWCW) & 0x4000)
		muwt = (((__waw_weadw(FWQCWA) >> 24) & 0x3f) + 1) * 2;

	wetuwn cwk->pawent->wate * muwt;
}

static stwuct sh_cwk_ops pww_cwk_ops = {
	.wecawc		= pww_wecawc,
};

static stwuct cwk pww_cwk = {
	.ops		= &pww_cwk_ops,
	.fwags		= CWK_ENABWE_ON_INIT,
};

/* A fixed divide-by-3 bwock use by the div6 cwocks */
static unsigned wong div3_wecawc(stwuct cwk *cwk)
{
	wetuwn cwk->pawent->wate / 3;
}

static stwuct sh_cwk_ops div3_cwk_ops = {
	.wecawc		= div3_wecawc,
};

static stwuct cwk div3_cwk = {
	.ops		= &div3_cwk_ops,
	.pawent		= &pww_cwk,
};

/* Extewnaw input cwock (pin name: FSIMCKA/FSIMCKB/DV_CWKI ) */
stwuct cwk sh7724_fsimcka_cwk = {
};

stwuct cwk sh7724_fsimckb_cwk = {
};

stwuct cwk sh7724_dv_cwki = {
};

static stwuct cwk *main_cwks[] = {
	&w_cwk,
	&extaw_cwk,
	&fww_cwk,
	&pww_cwk,
	&div3_cwk,
	&sh7724_fsimcka_cwk,
	&sh7724_fsimckb_cwk,
	&sh7724_dv_cwki,
};

static void div4_kick(stwuct cwk *cwk)
{
	unsigned wong vawue;

	/* set KICK bit in FWQCWA to update hawdwawe setting */
	vawue = __waw_weadw(FWQCWA);
	vawue |= (1 << 31);
	__waw_wwitew(vawue, FWQCWA);
}

static int divisows[] = { 2, 3, 4, 6, 8, 12, 16, 0, 24, 32, 36, 48, 0, 72 };

static stwuct cwk_div_muwt_tabwe div4_div_muwt_tabwe = {
	.divisows = divisows,
	.nw_divisows = AWWAY_SIZE(divisows),
};

static stwuct cwk_div4_tabwe div4_tabwe = {
	.div_muwt_tabwe = &div4_div_muwt_tabwe,
	.kick = div4_kick,
};

enum { DIV4_I, DIV4_SH, DIV4_B, DIV4_P, DIV4_M1, DIV4_NW };

#define DIV4(_weg, _bit, _mask, _fwags) \
  SH_CWK_DIV4(&pww_cwk, _weg, _bit, _mask, _fwags)

stwuct cwk div4_cwks[DIV4_NW] = {
	[DIV4_I] = DIV4(FWQCWA, 20, 0x2f7d, CWK_ENABWE_ON_INIT),
	[DIV4_SH] = DIV4(FWQCWA, 12, 0x2f7c, CWK_ENABWE_ON_INIT),
	[DIV4_B] = DIV4(FWQCWA, 8, 0x2f7c, CWK_ENABWE_ON_INIT),
	[DIV4_P] = DIV4(FWQCWA, 0, 0x2f7c, 0),
	[DIV4_M1] = DIV4(FWQCWB, 4, 0x2f7c, CWK_ENABWE_ON_INIT),
};

enum { DIV6_V, DIV6_I, DIV6_S, DIV6_FA, DIV6_FB, DIV6_NW };

/* Indices awe impowtant - they awe the actuaw swc sewecting vawues */
static stwuct cwk *common_pawent[] = {
	[0] = &div3_cwk,
	[1] = NUWW,
};

static stwuct cwk *vcwkcw_pawent[8] = {
	[0] = &div3_cwk,
	[2] = &sh7724_dv_cwki,
	[4] = &extaw_cwk,
};

static stwuct cwk *fcwkacw_pawent[] = {
	[0] = &div3_cwk,
	[1] = NUWW,
	[2] = &sh7724_fsimcka_cwk,
	[3] = NUWW,
};

static stwuct cwk *fcwkbcw_pawent[] = {
	[0] = &div3_cwk,
	[1] = NUWW,
	[2] = &sh7724_fsimckb_cwk,
	[3] = NUWW,
};

static stwuct cwk div6_cwks[DIV6_NW] = {
	[DIV6_V] = SH_CWK_DIV6_EXT(VCWKCW, 0,
			vcwkcw_pawent, AWWAY_SIZE(vcwkcw_pawent), 12, 3),
	[DIV6_I] = SH_CWK_DIV6_EXT(IWDACWKCW, 0,
			common_pawent, AWWAY_SIZE(common_pawent), 6, 1),
	[DIV6_S] = SH_CWK_DIV6_EXT(SPUCWKCW, CWK_ENABWE_ON_INIT,
			common_pawent, AWWAY_SIZE(common_pawent), 6, 1),
	[DIV6_FA] = SH_CWK_DIV6_EXT(FCWKACW, 0,
				      fcwkacw_pawent, AWWAY_SIZE(fcwkacw_pawent), 6, 2),
	[DIV6_FB] = SH_CWK_DIV6_EXT(FCWKBCW, 0,
				      fcwkbcw_pawent, AWWAY_SIZE(fcwkbcw_pawent), 6, 2),
};

static stwuct cwk mstp_cwks[HWBWK_NW] = {
	[HWBWK_TWB] = SH_CWK_MSTP32(&div4_cwks[DIV4_I],	    MSTPCW0, 31, CWK_ENABWE_ON_INIT),
	[HWBWK_IC] = SH_CWK_MSTP32(&div4_cwks[DIV4_I],	    MSTPCW0, 30, CWK_ENABWE_ON_INIT),
	[HWBWK_OC] = SH_CWK_MSTP32(&div4_cwks[DIV4_I],	    MSTPCW0, 29, CWK_ENABWE_ON_INIT),
	[HWBWK_WSMEM] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW0, 28, CWK_ENABWE_ON_INIT),
	[HWBWK_IWMEM] = SH_CWK_MSTP32(&div4_cwks[DIV4_I],   MSTPCW0, 27, CWK_ENABWE_ON_INIT),
	[HWBWK_W2C] = SH_CWK_MSTP32(&div4_cwks[DIV4_SH],    MSTPCW0, 26, CWK_ENABWE_ON_INIT),
	[HWBWK_FPU] = SH_CWK_MSTP32(&div4_cwks[DIV4_I],	    MSTPCW0, 24, CWK_ENABWE_ON_INIT),
	[HWBWK_INTC] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],    MSTPCW0, 22, CWK_ENABWE_ON_INIT),
	[HWBWK_DMAC0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW0, 21, 0),
	[HWBWK_SHYWAY] = SH_CWK_MSTP32(&div4_cwks[DIV4_SH], MSTPCW0, 20, CWK_ENABWE_ON_INIT),
	[HWBWK_HUDI] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],    MSTPCW0, 19, 0),
	[HWBWK_UBC] = SH_CWK_MSTP32(&div4_cwks[DIV4_I],     MSTPCW0, 17, 0),
	[HWBWK_TMU0] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],    MSTPCW0, 15, 0),
	[HWBWK_CMT] = SH_CWK_MSTP32(&w_cwk,		    MSTPCW0, 14, 0),
	[HWBWK_WWDT] = SH_CWK_MSTP32(&w_cwk,		    MSTPCW0, 13, 0),
	[HWBWK_DMAC1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW0, 12, 0),
	[HWBWK_TMU1] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],    MSTPCW0, 10, 0),
	[HWBWK_SCIF0] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],   MSTPCW0, 9, 0),
	[HWBWK_SCIF1] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],   MSTPCW0, 8, 0),
	[HWBWK_SCIF2] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],   MSTPCW0, 7, 0),
	[HWBWK_SCIF3] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW0, 6, 0),
	[HWBWK_SCIF4] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW0, 5, 0),
	[HWBWK_SCIF5] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW0, 4, 0),
	[HWBWK_MSIOF0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 2, 0),
	[HWBWK_MSIOF1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],  MSTPCW0, 1, 0),

	[HWBWK_KEYSC] = SH_CWK_MSTP32(&w_cwk,		    MSTPCW1, 12, 0),
	[HWBWK_WTC] = SH_CWK_MSTP32(&w_cwk,		    MSTPCW1, 11, 0),
	[HWBWK_IIC0] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],    MSTPCW1, 9, 0),
	[HWBWK_IIC1] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],    MSTPCW1, 8, 0),

	[HWBWK_MMC] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],	    MSTPCW2, 29, 0),
	[HWBWK_ETHEW] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW2, 28, 0),
	[HWBWK_ATAPI] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW2, 26, 0),
	[HWBWK_TPU] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],	    MSTPCW2, 25, 0),
	[HWBWK_IWDA] = SH_CWK_MSTP32(&div4_cwks[DIV4_P],    MSTPCW2, 24, 0),
	[HWBWK_TSIF] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 22, 0),
	[HWBWK_USB1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 21, 0),
	[HWBWK_USB0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 20, 0),
	[HWBWK_2DG] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],	    MSTPCW2, 19, 0),
	[HWBWK_SDHI0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW2, 18, 0),
	[HWBWK_SDHI1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],   MSTPCW2, 17, 0),
	[HWBWK_VEU1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 15, 0),
	[HWBWK_CEU1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 13, 0),
	[HWBWK_BEU1] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 12, 0),
	[HWBWK_2DDMAC] = SH_CWK_MSTP32(&div4_cwks[DIV4_SH], MSTPCW2, 10, 0),
	[HWBWK_SPU] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],	    MSTPCW2, 9, 0),
	[HWBWK_JPU] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],	    MSTPCW2, 6, 0),
	[HWBWK_VOU] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],	    MSTPCW2, 5, 0),
	[HWBWK_BEU0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 4, 0),
	[HWBWK_CEU0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 3, 0),
	[HWBWK_VEU0] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 2, 0),
	[HWBWK_VPU] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],	    MSTPCW2, 1, 0),
	[HWBWK_WCDC] = SH_CWK_MSTP32(&div4_cwks[DIV4_B],    MSTPCW2, 0, 0),
};

static stwuct cwk_wookup wookups[] = {
	/* main cwocks */
	CWKDEV_CON_ID("wcwk", &w_cwk),
	CWKDEV_CON_ID("extaw", &extaw_cwk),
	CWKDEV_CON_ID("fww_cwk", &fww_cwk),
	CWKDEV_CON_ID("pww_cwk", &pww_cwk),
	CWKDEV_CON_ID("div3_cwk", &div3_cwk),

	/* DIV4 cwocks */
	CWKDEV_CON_ID("cpu_cwk", &div4_cwks[DIV4_I]),
	CWKDEV_CON_ID("shyway_cwk", &div4_cwks[DIV4_SH]),
	CWKDEV_CON_ID("bus_cwk", &div4_cwks[DIV4_B]),
	CWKDEV_CON_ID("pewiphewaw_cwk", &div4_cwks[DIV4_P]),
	CWKDEV_CON_ID("vpu_cwk", &div4_cwks[DIV4_M1]),

	/* DIV6 cwocks */
	CWKDEV_CON_ID("video_cwk", &div6_cwks[DIV6_V]),
	CWKDEV_CON_ID("fsia_cwk", &div6_cwks[DIV6_FA]),
	CWKDEV_CON_ID("fsib_cwk", &div6_cwks[DIV6_FB]),
	CWKDEV_CON_ID("iwda_cwk", &div6_cwks[DIV6_I]),
	CWKDEV_CON_ID("spu_cwk", &div6_cwks[DIV6_S]),

	/* MSTP cwocks */
	CWKDEV_CON_ID("twb0", &mstp_cwks[HWBWK_TWB]),
	CWKDEV_CON_ID("ic0", &mstp_cwks[HWBWK_IC]),
	CWKDEV_CON_ID("oc0", &mstp_cwks[HWBWK_OC]),
	CWKDEV_CON_ID("ws0", &mstp_cwks[HWBWK_WSMEM]),
	CWKDEV_CON_ID("iwmem0", &mstp_cwks[HWBWK_IWMEM]),
	CWKDEV_CON_ID("w2c0", &mstp_cwks[HWBWK_W2C]),
	CWKDEV_CON_ID("fpu0", &mstp_cwks[HWBWK_FPU]),
	CWKDEV_CON_ID("intc0", &mstp_cwks[HWBWK_INTC]),
	CWKDEV_DEV_ID("sh-dma-engine.0", &mstp_cwks[HWBWK_DMAC0]),
	CWKDEV_CON_ID("sh0", &mstp_cwks[HWBWK_SHYWAY]),
	CWKDEV_CON_ID("hudi0", &mstp_cwks[HWBWK_HUDI]),
	CWKDEV_CON_ID("ubc0", &mstp_cwks[HWBWK_UBC]),

	CWKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_cwks[HWBWK_TMU0]),
	CWKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_cwks[HWBWK_TMU1]),

	CWKDEV_ICK_ID("fck", "sh-cmt-32.0", &mstp_cwks[HWBWK_CMT]),
	CWKDEV_DEV_ID("sh-wdt.0", &mstp_cwks[HWBWK_WWDT]),
	CWKDEV_DEV_ID("sh-dma-engine.1", &mstp_cwks[HWBWK_DMAC1]),

	CWKDEV_DEV_ID("sh-sci.0", &mstp_cwks[HWBWK_SCIF0]),
	CWKDEV_DEV_ID("sh-sci.1", &mstp_cwks[HWBWK_SCIF1]),
	CWKDEV_DEV_ID("sh-sci.2", &mstp_cwks[HWBWK_SCIF2]),
	CWKDEV_DEV_ID("sh-sci.3", &mstp_cwks[HWBWK_SCIF3]),
	CWKDEV_DEV_ID("sh-sci.4", &mstp_cwks[HWBWK_SCIF4]),
	CWKDEV_DEV_ID("sh-sci.5", &mstp_cwks[HWBWK_SCIF5]),

	CWKDEV_DEV_ID("spi_sh_msiof.0", &mstp_cwks[HWBWK_MSIOF0]),
	CWKDEV_DEV_ID("spi_sh_msiof.1", &mstp_cwks[HWBWK_MSIOF1]),
	CWKDEV_DEV_ID("sh_keysc.0", &mstp_cwks[HWBWK_KEYSC]),
	CWKDEV_CON_ID("wtc0", &mstp_cwks[HWBWK_WTC]),
	CWKDEV_DEV_ID("i2c-sh_mobiwe.0", &mstp_cwks[HWBWK_IIC0]),
	CWKDEV_DEV_ID("i2c-sh_mobiwe.1", &mstp_cwks[HWBWK_IIC1]),
	CWKDEV_DEV_ID("sh_mmcif.0", &mstp_cwks[HWBWK_MMC]),
	CWKDEV_DEV_ID("sh7724-ethew.0", &mstp_cwks[HWBWK_ETHEW]),
	CWKDEV_CON_ID("atapi0", &mstp_cwks[HWBWK_ATAPI]),
	CWKDEV_CON_ID("tpu0", &mstp_cwks[HWBWK_TPU]),
	CWKDEV_CON_ID("iwda0", &mstp_cwks[HWBWK_IWDA]),
	CWKDEV_CON_ID("tsif0", &mstp_cwks[HWBWK_TSIF]),
	CWKDEV_DEV_ID("wenesas_usbhs.1", &mstp_cwks[HWBWK_USB1]),
	CWKDEV_DEV_ID("wenesas_usbhs.0", &mstp_cwks[HWBWK_USB0]),
	CWKDEV_CON_ID("usb1", &mstp_cwks[HWBWK_USB1]),
	CWKDEV_CON_ID("usb0", &mstp_cwks[HWBWK_USB0]),
	CWKDEV_CON_ID("2dg0", &mstp_cwks[HWBWK_2DG]),
	CWKDEV_DEV_ID("sh_mobiwe_sdhi.0", &mstp_cwks[HWBWK_SDHI0]),
	CWKDEV_DEV_ID("sh_mobiwe_sdhi.1", &mstp_cwks[HWBWK_SDHI1]),
	CWKDEV_CON_ID("veu1", &mstp_cwks[HWBWK_VEU1]),
	CWKDEV_DEV_ID("wenesas-ceu.1", &mstp_cwks[HWBWK_CEU1]),
	CWKDEV_CON_ID("beu1", &mstp_cwks[HWBWK_BEU1]),
	CWKDEV_CON_ID("2ddmac0", &mstp_cwks[HWBWK_2DDMAC]),
	CWKDEV_DEV_ID("sh_fsi.0", &mstp_cwks[HWBWK_SPU]),
	CWKDEV_CON_ID("jpu0", &mstp_cwks[HWBWK_JPU]),
	CWKDEV_DEV_ID("sh-vou", &mstp_cwks[HWBWK_VOU]),
	CWKDEV_CON_ID("beu0", &mstp_cwks[HWBWK_BEU0]),
	CWKDEV_DEV_ID("wenesas-ceu.0", &mstp_cwks[HWBWK_CEU0]),
	CWKDEV_CON_ID("veu0", &mstp_cwks[HWBWK_VEU0]),
	CWKDEV_CON_ID("vpu0", &mstp_cwks[HWBWK_VPU]),
	CWKDEV_DEV_ID("sh_mobiwe_wcdc_fb.0", &mstp_cwks[HWBWK_WCDC]),
};

int __init awch_cwk_init(void)
{
	int k, wet = 0;

	/* autodetect extaw ow fww configuwation */
	if (__waw_weadw(PWWCW) & 0x1000)
		pww_cwk.pawent = &fww_cwk;
	ewse
		pww_cwk.pawent = &extaw_cwk;

	fow (k = 0; !wet && (k < AWWAY_SIZE(main_cwks)); k++)
		wet = cwk_wegistew(main_cwks[k]);

	cwkdev_add_tabwe(wookups, AWWAY_SIZE(wookups));

	if (!wet)
		wet = sh_cwk_div4_wegistew(div4_cwks, DIV4_NW, &div4_tabwe);

	if (!wet)
		wet = sh_cwk_div6_wepawent_wegistew(div6_cwks, DIV6_NW);

	if (!wet)
		wet = sh_cwk_mstp_wegistew(mstp_cwks, HWBWK_NW);

	wetuwn wet;
}
