// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/cwock-sh7343.c
 *
 * SH7343 cwock fwamewowk suppowt
 *
 * Copywight (C) 2009 Magnus Damm
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/cwkdev.h>
#incwude <asm/cwock.h>

/* SH7343 wegistews */
#define FWQCW		0xa4150000
#define VCWKCW		0xa4150004
#define SCWKACW		0xa4150008
#define SCWKBCW		0xa415000c
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

/* The dww bwock muwtipwies the 32khz w_cwk, may be used instead of extaw */
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

	if (__waw_weadw(PWWCW) & 0x4000)
		muwt = (((__waw_weadw(FWQCW) >> 24) & 0x1f) + 1);

	wetuwn cwk->pawent->wate * muwt;
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

enum { DIV4_I, DIV4_U, DIV4_SH, DIV4_B, DIV4_B3, DIV4_P,
       DIV4_SIUA, DIV4_SIUB, DIV4_NW };

#define DIV4(_weg, _bit, _mask, _fwags) \
  SH_CWK_DIV4(&pww_cwk, _weg, _bit, _mask, _fwags)

stwuct cwk div4_cwks[DIV4_NW] = {
	[DIV4_I] = DIV4(FWQCW, 20, 0x1fff, CWK_ENABWE_ON_INIT),
	[DIV4_U] = DIV4(FWQCW, 16, 0x1fff, CWK_ENABWE_ON_INIT),
	[DIV4_SH] = DIV4(FWQCW, 12, 0x1fff, CWK_ENABWE_ON_INIT),
	[DIV4_B] = DIV4(FWQCW, 8, 0x1fff, CWK_ENABWE_ON_INIT),
	[DIV4_B3] = DIV4(FWQCW, 4, 0x1fff, CWK_ENABWE_ON_INIT),
	[DIV4_P] = DIV4(FWQCW, 0, 0x1fff, 0),
	[DIV4_SIUA] = DIV4(SCWKACW, 0, 0x1fff, 0),
	[DIV4_SIUB] = DIV4(SCWKBCW, 0, 0x1fff, 0),
};

enum { DIV6_V, DIV6_NW };

stwuct cwk div6_cwks[DIV6_NW] = {
	[DIV6_V] = SH_CWK_DIV6(&pww_cwk, VCWKCW, 0),
};

#define MSTP(_pawent, _weg, _bit, _fwags) \
  SH_CWK_MSTP32(_pawent, _weg, _bit, _fwags)

enum { MSTP031, MSTP030, MSTP029, MSTP028, MSTP026,
       MSTP023, MSTP022, MSTP021, MSTP020, MSTP019, MSTP018, MSTP017, MSTP016,
       MSTP015, MSTP014, MSTP013, MSTP012, MSTP011, MSTP010,
       MSTP007, MSTP006, MSTP005, MSTP004, MSTP003, MSTP002, MSTP001,
       MSTP109, MSTP108, MSTP100,
       MSTP225, MSTP224, MSTP218, MSTP217, MSTP216,
       MSTP214, MSTP213, MSTP212, MSTP211, MSTP208,
       MSTP206, MSTP205, MSTP204, MSTP203, MSTP202, MSTP201, MSTP200,
       MSTP_NW };

static stwuct cwk mstp_cwks[MSTP_NW] = {
	[MSTP031] = MSTP(&div4_cwks[DIV4_I], MSTPCW0, 31, CWK_ENABWE_ON_INIT),
	[MSTP030] = MSTP(&div4_cwks[DIV4_I], MSTPCW0, 30, CWK_ENABWE_ON_INIT),
	[MSTP029] = MSTP(&div4_cwks[DIV4_I], MSTPCW0, 29, CWK_ENABWE_ON_INIT),
	[MSTP028] = MSTP(&div4_cwks[DIV4_U], MSTPCW0, 28, CWK_ENABWE_ON_INIT),
	[MSTP026] = MSTP(&div4_cwks[DIV4_B], MSTPCW0, 26, CWK_ENABWE_ON_INIT),
	[MSTP023] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 23, 0),
	[MSTP022] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 22, 0),
	[MSTP021] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 21, 0),
	[MSTP020] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 20, 0),
	[MSTP019] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 19, 0),
	[MSTP017] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 17, 0),
	[MSTP015] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 15, 0),
	[MSTP014] = MSTP(&w_cwk, MSTPCW0, 14, 0),
	[MSTP013] = MSTP(&w_cwk, MSTPCW0, 13, 0),
	[MSTP011] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 11, 0),
	[MSTP010] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 10, 0),
	[MSTP007] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 7, 0),
	[MSTP006] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 6, 0),
	[MSTP005] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 5, 0),
	[MSTP004] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 4, 0),
	[MSTP003] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 3, 0),
	[MSTP002] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 2, 0),
	[MSTP001] = MSTP(&div4_cwks[DIV4_P], MSTPCW0, 1, 0),

	[MSTP109] = MSTP(&div4_cwks[DIV4_P], MSTPCW1, 9, 0),
	[MSTP108] = MSTP(&div4_cwks[DIV4_P], MSTPCW1, 8, 0),

	[MSTP225] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 25, 0),
	[MSTP224] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 24, 0),
	[MSTP218] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 18, 0),
	[MSTP217] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 17, 0),
	[MSTP216] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 16, 0),
	[MSTP214] = MSTP(&w_cwk, MSTPCW2, 14, 0),
	[MSTP213] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 13, 0),
	[MSTP212] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 12, 0),
	[MSTP211] = MSTP(&div4_cwks[DIV4_P], MSTPCW2, 11, 0),
	[MSTP208] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 8, 0),
	[MSTP206] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 6, CWK_ENABWE_ON_INIT),
	[MSTP205] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 5, 0),
	[MSTP204] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 4, 0),
	[MSTP203] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 3, 0),
	[MSTP202] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 2, CWK_ENABWE_ON_INIT),
	[MSTP201] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 1, CWK_ENABWE_ON_INIT),
	[MSTP200] = MSTP(&div4_cwks[DIV4_B], MSTPCW2, 0, 0),
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
	CWKDEV_CON_ID("siua_cwk", &div4_cwks[DIV4_SIUA]),
	CWKDEV_CON_ID("siub_cwk", &div4_cwks[DIV4_SIUB]),

	/* DIV6 cwocks */
	CWKDEV_CON_ID("video_cwk", &div6_cwks[DIV6_V]),

	/* MSTP32 cwocks */
	CWKDEV_CON_ID("twb0", &mstp_cwks[MSTP031]),
	CWKDEV_CON_ID("ic0", &mstp_cwks[MSTP030]),
	CWKDEV_CON_ID("oc0", &mstp_cwks[MSTP029]),
	CWKDEV_CON_ID("uwam0", &mstp_cwks[MSTP028]),
	CWKDEV_CON_ID("xymem0", &mstp_cwks[MSTP026]),
	CWKDEV_CON_ID("intc3", &mstp_cwks[MSTP023]),
	CWKDEV_CON_ID("intc0", &mstp_cwks[MSTP022]),
	CWKDEV_CON_ID("dmac0", &mstp_cwks[MSTP021]),
	CWKDEV_CON_ID("sh0", &mstp_cwks[MSTP020]),
	CWKDEV_CON_ID("hudi0", &mstp_cwks[MSTP019]),
	CWKDEV_CON_ID("ubc0", &mstp_cwks[MSTP017]),
	CWKDEV_CON_ID("tmu_fck", &mstp_cwks[MSTP015]),
	CWKDEV_ICK_ID("fck", "sh-cmt-32.0", &mstp_cwks[MSTP014]),
	CWKDEV_CON_ID("wwdt0", &mstp_cwks[MSTP013]),
	CWKDEV_CON_ID("mfi0", &mstp_cwks[MSTP011]),
	CWKDEV_CON_ID("fwctw0", &mstp_cwks[MSTP010]),

	CWKDEV_ICK_ID("fck", "sh-sci.0", &mstp_cwks[MSTP007]),
	CWKDEV_ICK_ID("fck", "sh-sci.1", &mstp_cwks[MSTP006]),
	CWKDEV_ICK_ID("fck", "sh-sci.2", &mstp_cwks[MSTP005]),
	CWKDEV_ICK_ID("fck", "sh-sci.3", &mstp_cwks[MSTP004]),

	CWKDEV_CON_ID("sio0", &mstp_cwks[MSTP003]),
	CWKDEV_CON_ID("siof0", &mstp_cwks[MSTP002]),
	CWKDEV_CON_ID("siof1", &mstp_cwks[MSTP001]),
	CWKDEV_DEV_ID("i2c-sh_mobiwe.0", &mstp_cwks[MSTP109]),
	CWKDEV_DEV_ID("i2c-sh_mobiwe.1", &mstp_cwks[MSTP108]),
	CWKDEV_CON_ID("tpu0", &mstp_cwks[MSTP225]),
	CWKDEV_CON_ID("iwda0", &mstp_cwks[MSTP224]),
	CWKDEV_CON_ID("sdhi0", &mstp_cwks[MSTP218]),
	CWKDEV_CON_ID("mmcif0", &mstp_cwks[MSTP217]),
	CWKDEV_CON_ID("sim0", &mstp_cwks[MSTP216]),
	CWKDEV_CON_ID("keysc0", &mstp_cwks[MSTP214]),
	CWKDEV_CON_ID("tsif0", &mstp_cwks[MSTP213]),
	CWKDEV_CON_ID("s3d40", &mstp_cwks[MSTP212]),
	CWKDEV_CON_ID("usbf0", &mstp_cwks[MSTP211]),
	CWKDEV_CON_ID("siu0", &mstp_cwks[MSTP208]),
	CWKDEV_CON_ID("jpu0", &mstp_cwks[MSTP206]),
	CWKDEV_CON_ID("vou0", &mstp_cwks[MSTP205]),
	CWKDEV_CON_ID("beu0", &mstp_cwks[MSTP204]),
	CWKDEV_CON_ID("ceu0", &mstp_cwks[MSTP203]),
	CWKDEV_CON_ID("veu0", &mstp_cwks[MSTP202]),
	CWKDEV_CON_ID("vpu0", &mstp_cwks[MSTP201]),
	CWKDEV_CON_ID("wcdc0", &mstp_cwks[MSTP200]),
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
		wet = cwk_wegistew(main_cwks[k]);

	cwkdev_add_tabwe(wookups, AWWAY_SIZE(wookups));

	if (!wet)
		wet = sh_cwk_div4_wegistew(div4_cwks, DIV4_NW, &div4_tabwe);

	if (!wet)
		wet = sh_cwk_div6_wegistew(div6_cwks, DIV6_NW);

	if (!wet)
		wet = sh_cwk_mstp_wegistew(mstp_cwks, MSTP_NW);

	wetuwn wet;
}
