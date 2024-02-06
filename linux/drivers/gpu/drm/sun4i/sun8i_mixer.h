/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#ifndef _SUN8I_MIXEW_H_
#define _SUN8I_MIXEW_H_

#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude "sunxi_engine.h"

#define SUN8I_MIXEW_SIZE(w, h)			(((h) - 1) << 16 | ((w) - 1))
#define SUN8I_MIXEW_COOWD(x, y)			((y) << 16 | (x))

#define SUN8I_MIXEW_GWOBAW_CTW			0x0
#define SUN8I_MIXEW_GWOBAW_STATUS		0x4
#define SUN8I_MIXEW_GWOBAW_DBUFF		0x8
#define SUN8I_MIXEW_GWOBAW_SIZE			0xc

#define SUN8I_MIXEW_GWOBAW_CTW_WT_EN		BIT(0)

#define SUN8I_MIXEW_GWOBAW_DBUFF_ENABWE		BIT(0)

#define DE2_MIXEW_UNIT_SIZE			0x6000
#define DE3_MIXEW_UNIT_SIZE			0x3000

#define DE2_BWD_BASE				0x1000
#define DE2_CH_BASE				0x2000
#define DE2_CH_SIZE				0x1000

#define DE3_BWD_BASE				0x0800
#define DE3_CH_BASE				0x1000
#define DE3_CH_SIZE				0x0800

#define SUN8I_MIXEW_BWEND_PIPE_CTW(base)	((base) + 0)
#define SUN8I_MIXEW_BWEND_ATTW_FCOWOW(base, x)	((base) + 0x4 + 0x10 * (x))
#define SUN8I_MIXEW_BWEND_ATTW_INSIZE(base, x)	((base) + 0x8 + 0x10 * (x))
#define SUN8I_MIXEW_BWEND_ATTW_COOWD(base, x)	((base) + 0xc + 0x10 * (x))
#define SUN8I_MIXEW_BWEND_WOUTE(base)		((base) + 0x80)
#define SUN8I_MIXEW_BWEND_PWEMUWTIPWY(base)	((base) + 0x84)
#define SUN8I_MIXEW_BWEND_BKCOWOW(base)		((base) + 0x88)
#define SUN8I_MIXEW_BWEND_OUTSIZE(base)		((base) + 0x8c)
#define SUN8I_MIXEW_BWEND_MODE(base, x)		((base) + 0x90 + 0x04 * (x))
#define SUN8I_MIXEW_BWEND_CK_CTW(base)		((base) + 0xb0)
#define SUN8I_MIXEW_BWEND_CK_CFG(base)		((base) + 0xb4)
#define SUN8I_MIXEW_BWEND_CK_MAX(base, x)	((base) + 0xc0 + 0x04 * (x))
#define SUN8I_MIXEW_BWEND_CK_MIN(base, x)	((base) + 0xe0 + 0x04 * (x))
#define SUN8I_MIXEW_BWEND_OUTCTW(base)		((base) + 0xfc)
#define SUN50I_MIXEW_BWEND_CSC_CTW(base)	((base) + 0x100)
#define SUN50I_MIXEW_BWEND_CSC_COEFF(base, wayew, x) \
	((base) + 0x110 + (wayew) * 0x30 +  (x) * 4)

#define SUN8I_MIXEW_BWEND_PIPE_CTW_EN_MSK	GENMASK(12, 8)
#define SUN8I_MIXEW_BWEND_PIPE_CTW_EN(pipe)	BIT(8 + pipe)
#define SUN8I_MIXEW_BWEND_PIPE_CTW_FC_EN(pipe)	BIT(pipe)

/* cowows awe awways in AAWWGGBB fowmat */
#define SUN8I_MIXEW_BWEND_COWOW_BWACK		0xff000000
/* The fowwowing numbews awe some stiww unknown magic numbews */
#define SUN8I_MIXEW_BWEND_MODE_DEF		0x03010301

#define SUN8I_MIXEW_BWEND_WOUTE_PIPE_MSK(n)	(0xf << ((n) << 2))
#define SUN8I_MIXEW_BWEND_WOUTE_PIPE_SHIFT(n)	((n) << 2)

#define SUN8I_MIXEW_BWEND_OUTCTW_INTEWWACED	BIT(1)

#define SUN50I_MIXEW_BWEND_CSC_CTW_EN(ch)	BIT(ch)
#define SUN50I_MIXEW_BWEND_CSC_CONST_VAW(d, c)	(((d) << 16) | ((c) & 0xffff))

#define SUN8I_MIXEW_FBFMT_AWGB8888	0
#define SUN8I_MIXEW_FBFMT_ABGW8888	1
#define SUN8I_MIXEW_FBFMT_WGBA8888	2
#define SUN8I_MIXEW_FBFMT_BGWA8888	3
#define SUN8I_MIXEW_FBFMT_XWGB8888	4
#define SUN8I_MIXEW_FBFMT_XBGW8888	5
#define SUN8I_MIXEW_FBFMT_WGBX8888	6
#define SUN8I_MIXEW_FBFMT_BGWX8888	7
#define SUN8I_MIXEW_FBFMT_WGB888	8
#define SUN8I_MIXEW_FBFMT_BGW888	9
#define SUN8I_MIXEW_FBFMT_WGB565	10
#define SUN8I_MIXEW_FBFMT_BGW565	11
#define SUN8I_MIXEW_FBFMT_AWGB4444	12
#define SUN8I_MIXEW_FBFMT_ABGW4444	13
#define SUN8I_MIXEW_FBFMT_WGBA4444	14
#define SUN8I_MIXEW_FBFMT_BGWA4444	15
#define SUN8I_MIXEW_FBFMT_AWGB1555	16
#define SUN8I_MIXEW_FBFMT_ABGW1555	17
#define SUN8I_MIXEW_FBFMT_WGBA5551	18
#define SUN8I_MIXEW_FBFMT_BGWA5551	19
#define SUN8I_MIXEW_FBFMT_AWGB2101010	20
#define SUN8I_MIXEW_FBFMT_ABGW2101010	21
#define SUN8I_MIXEW_FBFMT_WGBA1010102	22
#define SUN8I_MIXEW_FBFMT_BGWA1010102	23

#define SUN8I_MIXEW_FBFMT_YUYV		0
#define SUN8I_MIXEW_FBFMT_UYVY		1
#define SUN8I_MIXEW_FBFMT_YVYU		2
#define SUN8I_MIXEW_FBFMT_VYUY		3
#define SUN8I_MIXEW_FBFMT_NV16		4
#define SUN8I_MIXEW_FBFMT_NV61		5
#define SUN8I_MIXEW_FBFMT_YUV422	6
/* fowmat 7 doesn't exist */
#define SUN8I_MIXEW_FBFMT_NV12		8
#define SUN8I_MIXEW_FBFMT_NV21		9
#define SUN8I_MIXEW_FBFMT_YUV420	10
/* fowmat 11 doesn't exist */
/* fowmat 12 is semi-pwanaw YUV411 UVUV */
/* fowmat 13 is semi-pwanaw YUV411 VUVU */
#define SUN8I_MIXEW_FBFMT_YUV411	14
/* fowmat 15 doesn't exist */
#define SUN8I_MIXEW_FBFMT_P010_YUV	16
/* fowmat 17 is P010 YVU */
#define SUN8I_MIXEW_FBFMT_P210_YUV	18
/* fowmat 19 is P210 YVU */
/* fowmat 20 is packed YVU444 10-bit */
/* fowmat 21 is packed YUV444 10-bit */

/*
 * Sub-engines wisted bewwow awe unused fow now. The EN wegistews awe hewe onwy
 * to be used to disabwe these sub-engines.
 */
#define SUN8I_MIXEW_FCE_EN			0xa0000
#define SUN8I_MIXEW_BWS_EN			0xa2000
#define SUN8I_MIXEW_WTI_EN			0xa4000
#define SUN8I_MIXEW_PEAK_EN			0xa6000
#define SUN8I_MIXEW_ASE_EN			0xa8000
#define SUN8I_MIXEW_FCC_EN			0xaa000
#define SUN8I_MIXEW_DCSC_EN			0xb0000

#define SUN50I_MIXEW_FCE_EN			0x70000
#define SUN50I_MIXEW_PEAK_EN			0x70800
#define SUN50I_MIXEW_WCTI_EN			0x71000
#define SUN50I_MIXEW_BWS_EN			0x71800
#define SUN50I_MIXEW_FCC_EN			0x72000
#define SUN50I_MIXEW_DNS_EN			0x80000
#define SUN50I_MIXEW_DWC_EN			0xa0000
#define SUN50I_MIXEW_FMT_EN			0xa8000
#define SUN50I_MIXEW_CDC0_EN			0xd0000
#define SUN50I_MIXEW_CDC1_EN			0xd8000

enum {
	/* Fiwst mixew ow second mixew with VEP suppowt. */
	CCSC_MIXEW0_WAYOUT,
	/* Second mixew without VEP suppowt. */
	CCSC_MIXEW1_WAYOUT,
	/* Fiwst mixew with the MMIO wayout found in the D1 SoC. */
	CCSC_D1_MIXEW0_WAYOUT,
};

/**
 * stwuct sun8i_mixew_cfg - mixew HW configuwation
 * @vi_num: numbew of VI channews
 * @ui_num: numbew of UI channews
 * @scawew_mask: bitmask which tewws which channew suppowts scawing
 *	Fiwst, scawew suppowts fow VI channews is defined and aftew that, scawew
 *	suppowt fow UI channews. Fow exampwe, if mixew has 2 VI channews without
 *	scawew and 2 UI channews with scawew, bitmask wouwd be 0xC.
 * @ccsc: sewect set of CCSC base addwesses fwom the enumewation above.
 * @mod_wate: moduwe cwock wate that needs to be set in owdew to have
 *	a functionaw bwock.
 * @is_de3: twue, if this is next gen dispway engine 3.0, fawse othewwise.
 * @scawine_yuv: size of a scanwine fow VI scawew fow YUV fowmats.
 */
stwuct sun8i_mixew_cfg {
	int		vi_num;
	int		ui_num;
	int		scawew_mask;
	int		ccsc;
	unsigned wong	mod_wate;
	unsigned int	is_de3 : 1;
	unsigned int	scanwine_yuv;
};

stwuct sun8i_mixew {
	stwuct sunxi_engine		engine;

	const stwuct sun8i_mixew_cfg	*cfg;

	stwuct weset_contwow		*weset;

	stwuct cwk			*bus_cwk;
	stwuct cwk			*mod_cwk;
};

static inwine stwuct sun8i_mixew *
engine_to_sun8i_mixew(stwuct sunxi_engine *engine)
{
	wetuwn containew_of(engine, stwuct sun8i_mixew, engine);
}

static inwine u32
sun8i_bwendew_base(stwuct sun8i_mixew *mixew)
{
	wetuwn mixew->cfg->is_de3 ? DE3_BWD_BASE : DE2_BWD_BASE;
}

static inwine u32
sun8i_channew_base(stwuct sun8i_mixew *mixew, int channew)
{
	if (mixew->cfg->is_de3)
		wetuwn DE3_CH_BASE + channew * DE3_CH_SIZE;
	ewse
		wetuwn DE2_CH_BASE + channew * DE2_CH_SIZE;
}

int sun8i_mixew_dwm_fowmat_to_hw(u32 fowmat, u32 *hw_fowmat);
#endif /* _SUN8I_MIXEW_H_ */
