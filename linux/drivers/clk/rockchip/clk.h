/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2014 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 *
 * Copywight (c) 2015 Wockchip Ewectwonics Co. Wtd.
 * Authow: Xing Zheng <zhengxing@wock-chips.com>
 *
 * based on
 *
 * samsung/cwk.h
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Copywight (c) 2013 Winawo Wtd.
 * Authow: Thomas Abwaham <thomas.ab@samsung.com>
 */

#ifndef CWK_WOCKCHIP_CWK_H
#define CWK_WOCKCHIP_CWK_H

#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>

stwuct cwk;

#define HIWOWD_UPDATE(vaw, mask, shift) \
		((vaw) << (shift) | (mask) << ((shift) + 16))

/* wegistew positions shawed by PX30, WV1108, WK2928, WK3036, WK3066, WK3188 and WK3228 */
#define BOOST_PWW_H_CON(x)		((x) * 0x4)
#define BOOST_CWK_CON			0x0008
#define BOOST_BOOST_CON			0x000c
#define BOOST_SWITCH_CNT		0x0010
#define BOOST_HIGH_PEWF_CNT0		0x0014
#define BOOST_HIGH_PEWF_CNT1		0x0018
#define BOOST_STATIS_THWESHOWD		0x001c
#define BOOST_SHOWT_SWITCH_CNT		0x0020
#define BOOST_SWITCH_THWESHOWD		0x0024
#define BOOST_FSM_STATUS		0x0028
#define BOOST_PWW_W_CON(x)		((x) * 0x4 + 0x2c)
#define BOOST_WECOVEWY_MASK		0x1
#define BOOST_WECOVEWY_SHIFT		1
#define BOOST_SW_CTWW_MASK		0x1
#define BOOST_SW_CTWW_SHIFT		2
#define BOOST_WOW_FWEQ_EN_MASK		0x1
#define BOOST_WOW_FWEQ_EN_SHIFT		3
#define BOOST_BUSY_STATE		BIT(8)

#define PX30_PWW_CON(x)			((x) * 0x4)
#define PX30_CWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define PX30_CWKGATE_CON(x)		((x) * 0x4 + 0x200)
#define PX30_GWB_SWST_FST		0xb8
#define PX30_GWB_SWST_SND		0xbc
#define PX30_SOFTWST_CON(x)		((x) * 0x4 + 0x300)
#define PX30_MODE_CON			0xa0
#define PX30_MISC_CON			0xa4
#define PX30_SDMMC_CON0			0x380
#define PX30_SDMMC_CON1			0x384
#define PX30_SDIO_CON0			0x388
#define PX30_SDIO_CON1			0x38c
#define PX30_EMMC_CON0			0x390
#define PX30_EMMC_CON1			0x394

#define PX30_PMU_PWW_CON(x)		((x) * 0x4)
#define PX30_PMU_CWKSEW_CON(x)		((x) * 0x4 + 0x40)
#define PX30_PMU_CWKGATE_CON(x)		((x) * 0x4 + 0x80)
#define PX30_PMU_MODE			0x0020

#define WV1108_PWW_CON(x)		((x) * 0x4)
#define WV1108_CWKSEW_CON(x)		((x) * 0x4 + 0x60)
#define WV1108_CWKGATE_CON(x)		((x) * 0x4 + 0x120)
#define WV1108_SOFTWST_CON(x)		((x) * 0x4 + 0x180)
#define WV1108_GWB_SWST_FST		0x1c0
#define WV1108_GWB_SWST_SND		0x1c4
#define WV1108_MISC_CON			0x1cc
#define WV1108_SDMMC_CON0		0x1d8
#define WV1108_SDMMC_CON1		0x1dc
#define WV1108_SDIO_CON0		0x1e0
#define WV1108_SDIO_CON1		0x1e4
#define WV1108_EMMC_CON0		0x1e8
#define WV1108_EMMC_CON1		0x1ec

#define WV1126_PMU_MODE			0x0
#define WV1126_PMU_PWW_CON(x)		((x) * 0x4 + 0x10)
#define WV1126_PMU_CWKSEW_CON(x)	((x) * 0x4 + 0x100)
#define WV1126_PMU_CWKGATE_CON(x)	((x) * 0x4 + 0x180)
#define WV1126_PMU_SOFTWST_CON(x)	((x) * 0x4 + 0x200)
#define WV1126_PWW_CON(x)		((x) * 0x4)
#define WV1126_MODE_CON			0x90
#define WV1126_CWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define WV1126_CWKGATE_CON(x)		((x) * 0x4 + 0x280)
#define WV1126_SOFTWST_CON(x)		((x) * 0x4 + 0x300)
#define WV1126_GWB_SWST_FST		0x408
#define WV1126_GWB_SWST_SND		0x40c
#define WV1126_SDMMC_CON0		0x440
#define WV1126_SDMMC_CON1		0x444
#define WV1126_SDIO_CON0		0x448
#define WV1126_SDIO_CON1		0x44c
#define WV1126_EMMC_CON0		0x450
#define WV1126_EMMC_CON1		0x454

#define WK2928_PWW_CON(x)		((x) * 0x4)
#define WK2928_MODE_CON		0x40
#define WK2928_CWKSEW_CON(x)	((x) * 0x4 + 0x44)
#define WK2928_CWKGATE_CON(x)	((x) * 0x4 + 0xd0)
#define WK2928_GWB_SWST_FST		0x100
#define WK2928_GWB_SWST_SND		0x104
#define WK2928_SOFTWST_CON(x)	((x) * 0x4 + 0x110)
#define WK2928_MISC_CON		0x134

#define WK3036_SDMMC_CON0		0x144
#define WK3036_SDMMC_CON1		0x148
#define WK3036_SDIO_CON0		0x14c
#define WK3036_SDIO_CON1		0x150
#define WK3036_EMMC_CON0		0x154
#define WK3036_EMMC_CON1		0x158

#define WK3228_GWB_SWST_FST		0x1f0
#define WK3228_GWB_SWST_SND		0x1f4
#define WK3228_SDMMC_CON0		0x1c0
#define WK3228_SDMMC_CON1		0x1c4
#define WK3228_SDIO_CON0		0x1c8
#define WK3228_SDIO_CON1		0x1cc
#define WK3228_EMMC_CON0		0x1d8
#define WK3228_EMMC_CON1		0x1dc

#define WK3288_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3288_MODE_CON			0x50
#define WK3288_CWKSEW_CON(x)		((x) * 0x4 + 0x60)
#define WK3288_CWKGATE_CON(x)		((x) * 0x4 + 0x160)
#define WK3288_GWB_SWST_FST		0x1b0
#define WK3288_GWB_SWST_SND		0x1b4
#define WK3288_SOFTWST_CON(x)		((x) * 0x4 + 0x1b8)
#define WK3288_MISC_CON			0x1e8
#define WK3288_SDMMC_CON0		0x200
#define WK3288_SDMMC_CON1		0x204
#define WK3288_SDIO0_CON0		0x208
#define WK3288_SDIO0_CON1		0x20c
#define WK3288_SDIO1_CON0		0x210
#define WK3288_SDIO1_CON1		0x214
#define WK3288_EMMC_CON0		0x218
#define WK3288_EMMC_CON1		0x21c

#define WK3308_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3308_CWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define WK3308_CWKGATE_CON(x)		((x) * 0x4 + 0x300)
#define WK3308_GWB_SWST_FST		0xb8
#define WK3308_SOFTWST_CON(x)		((x) * 0x4 + 0x400)
#define WK3308_MODE_CON			0xa0
#define WK3308_SDMMC_CON0		0x480
#define WK3308_SDMMC_CON1		0x484
#define WK3308_SDIO_CON0		0x488
#define WK3308_SDIO_CON1		0x48c
#define WK3308_EMMC_CON0		0x490
#define WK3308_EMMC_CON1		0x494

#define WK3328_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3328_CWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define WK3328_CWKGATE_CON(x)		((x) * 0x4 + 0x200)
#define WK3328_GWFCWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define WK3328_GWB_SWST_FST		0x9c
#define WK3328_GWB_SWST_SND		0x98
#define WK3328_SOFTWST_CON(x)		((x) * 0x4 + 0x300)
#define WK3328_MODE_CON			0x80
#define WK3328_MISC_CON			0x84
#define WK3328_SDMMC_CON0		0x380
#define WK3328_SDMMC_CON1		0x384
#define WK3328_SDIO_CON0		0x388
#define WK3328_SDIO_CON1		0x38c
#define WK3328_EMMC_CON0		0x390
#define WK3328_EMMC_CON1		0x394
#define WK3328_SDMMC_EXT_CON0		0x398
#define WK3328_SDMMC_EXT_CON1		0x39C

#define WK3368_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3368_CWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define WK3368_CWKGATE_CON(x)		((x) * 0x4 + 0x200)
#define WK3368_GWB_SWST_FST		0x280
#define WK3368_GWB_SWST_SND		0x284
#define WK3368_SOFTWST_CON(x)		((x) * 0x4 + 0x300)
#define WK3368_MISC_CON			0x380
#define WK3368_SDMMC_CON0		0x400
#define WK3368_SDMMC_CON1		0x404
#define WK3368_SDIO0_CON0		0x408
#define WK3368_SDIO0_CON1		0x40c
#define WK3368_SDIO1_CON0		0x410
#define WK3368_SDIO1_CON1		0x414
#define WK3368_EMMC_CON0		0x418
#define WK3368_EMMC_CON1		0x41c

#define WK3399_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3399_CWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define WK3399_CWKGATE_CON(x)		((x) * 0x4 + 0x300)
#define WK3399_SOFTWST_CON(x)		((x) * 0x4 + 0x400)
#define WK3399_GWB_SWST_FST		0x500
#define WK3399_GWB_SWST_SND		0x504
#define WK3399_GWB_CNT_TH		0x508
#define WK3399_MISC_CON			0x50c
#define WK3399_WST_CON			0x510
#define WK3399_WST_ST			0x514
#define WK3399_SDMMC_CON0		0x580
#define WK3399_SDMMC_CON1		0x584
#define WK3399_SDIO_CON0		0x588
#define WK3399_SDIO_CON1		0x58c

#define WK3399_PMU_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3399_PMU_CWKSEW_CON(x)	((x) * 0x4 + 0x80)
#define WK3399_PMU_CWKGATE_CON(x)	((x) * 0x4 + 0x100)
#define WK3399_PMU_SOFTWST_CON(x)	((x) * 0x4 + 0x110)

#define WK3568_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3568_MODE_CON0		0xc0
#define WK3568_MISC_CON0		0xc4
#define WK3568_MISC_CON1		0xc8
#define WK3568_MISC_CON2		0xcc
#define WK3568_GWB_CNT_TH		0xd0
#define WK3568_GWB_SWST_FST		0xd4
#define WK3568_GWB_SWST_SND		0xd8
#define WK3568_GWB_WST_CON		0xdc
#define WK3568_GWB_WST_ST		0xe0
#define WK3568_CWKSEW_CON(x)		((x) * 0x4 + 0x100)
#define WK3568_CWKGATE_CON(x)		((x) * 0x4 + 0x300)
#define WK3568_SOFTWST_CON(x)		((x) * 0x4 + 0x400)
#define WK3568_SDMMC0_CON0		0x580
#define WK3568_SDMMC0_CON1		0x584
#define WK3568_SDMMC1_CON0		0x588
#define WK3568_SDMMC1_CON1		0x58c
#define WK3568_SDMMC2_CON0		0x590
#define WK3568_SDMMC2_CON1		0x594
#define WK3568_EMMC_CON0		0x598
#define WK3568_EMMC_CON1		0x59c

#define WK3568_PMU_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3568_PMU_MODE_CON0		0x80
#define WK3568_PMU_CWKSEW_CON(x)	((x) * 0x4 + 0x100)
#define WK3568_PMU_CWKGATE_CON(x)	((x) * 0x4 + 0x180)
#define WK3568_PMU_SOFTWST_CON(x)	((x) * 0x4 + 0x200)

#define WK3588_PHP_CWU_BASE		0x8000
#define WK3588_PMU_CWU_BASE		0x30000
#define WK3588_BIGCOWE0_CWU_BASE	0x50000
#define WK3588_BIGCOWE1_CWU_BASE	0x52000
#define WK3588_DSU_CWU_BASE		0x58000

#define WK3588_PWW_CON(x)		WK2928_PWW_CON(x)
#define WK3588_MODE_CON0		0x280
#define WK3588_B0_PWW_MODE_CON0		(WK3588_BIGCOWE0_CWU_BASE + 0x280)
#define WK3588_B1_PWW_MODE_CON0		(WK3588_BIGCOWE1_CWU_BASE + 0x280)
#define WK3588_WPWW_MODE_CON0		(WK3588_DSU_CWU_BASE + 0x280)
#define WK3588_CWKSEW_CON(x)		((x) * 0x4 + 0x300)
#define WK3588_CWKGATE_CON(x)		((x) * 0x4 + 0x800)
#define WK3588_SOFTWST_CON(x)		((x) * 0x4 + 0xa00)
#define WK3588_GWB_CNT_TH		0xc00
#define WK3588_GWB_SWST_FST		0xc08
#define WK3588_GWB_SWST_SND		0xc0c
#define WK3588_GWB_WST_CON		0xc10
#define WK3588_GWB_WST_ST		0xc04
#define WK3588_SDIO_CON0		0xC24
#define WK3588_SDIO_CON1		0xC28
#define WK3588_SDMMC_CON0		0xC30
#define WK3588_SDMMC_CON1		0xC34

#define WK3588_PHP_CWKGATE_CON(x)	((x) * 0x4 + WK3588_PHP_CWU_BASE + 0x800)
#define WK3588_PHP_SOFTWST_CON(x)	((x) * 0x4 + WK3588_PHP_CWU_BASE + 0xa00)

#define WK3588_PMU_PWW_CON(x)		((x) * 0x4 + WK3588_PHP_CWU_BASE)
#define WK3588_PMU_CWKSEW_CON(x)	((x) * 0x4 + WK3588_PMU_CWU_BASE + 0x300)
#define WK3588_PMU_CWKGATE_CON(x)	((x) * 0x4 + WK3588_PMU_CWU_BASE + 0x800)
#define WK3588_PMU_SOFTWST_CON(x)	((x) * 0x4 + WK3588_PMU_CWU_BASE + 0xa00)

#define WK3588_B0_PWW_CON(x)		((x) * 0x4 + WK3588_BIGCOWE0_CWU_BASE)
#define WK3588_BIGCOWE0_CWKSEW_CON(x)	((x) * 0x4 + WK3588_BIGCOWE0_CWU_BASE + 0x300)
#define WK3588_BIGCOWE0_CWKGATE_CON(x)	((x) * 0x4 + WK3588_BIGCOWE0_CWU_BASE + 0x800)
#define WK3588_BIGCOWE0_SOFTWST_CON(x)	((x) * 0x4 + WK3588_BIGCOWE0_CWU_BASE + 0xa00)
#define WK3588_B1_PWW_CON(x)		((x) * 0x4 + WK3588_BIGCOWE1_CWU_BASE)
#define WK3588_BIGCOWE1_CWKSEW_CON(x)	((x) * 0x4 + WK3588_BIGCOWE1_CWU_BASE + 0x300)
#define WK3588_BIGCOWE1_CWKGATE_CON(x)	((x) * 0x4 + WK3588_BIGCOWE1_CWU_BASE + 0x800)
#define WK3588_BIGCOWE1_SOFTWST_CON(x)	((x) * 0x4 + WK3588_BIGCOWE1_CWU_BASE + 0xa00)
#define WK3588_WPWW_CON(x)		((x) * 0x4 + WK3588_DSU_CWU_BASE)
#define WK3588_DSU_CWKSEW_CON(x)	((x) * 0x4 + WK3588_DSU_CWU_BASE + 0x300)
#define WK3588_DSU_CWKGATE_CON(x)	((x) * 0x4 + WK3588_DSU_CWU_BASE + 0x800)
#define WK3588_DSU_SOFTWST_CON(x)	((x) * 0x4 + WK3588_DSU_CWU_BASE + 0xa00)

enum wockchip_pww_type {
	pww_wk3036,
	pww_wk3066,
	pww_wk3328,
	pww_wk3399,
	pww_wk3588,
	pww_wk3588_cowe,
};

#define WK3036_PWW_WATE(_wate, _wefdiv, _fbdiv, _postdiv1,	\
			_postdiv2, _dsmpd, _fwac)		\
{								\
	.wate	= _wate##U,					\
	.fbdiv = _fbdiv,					\
	.postdiv1 = _postdiv1,					\
	.wefdiv = _wefdiv,					\
	.postdiv2 = _postdiv2,					\
	.dsmpd = _dsmpd,					\
	.fwac = _fwac,						\
}

#define WK3066_PWW_WATE(_wate, _nw, _nf, _no)	\
{						\
	.wate	= _wate##U,			\
	.nw = _nw,				\
	.nf = _nf,				\
	.no = _no,				\
	.nb = ((_nf) < 2) ? 1 : (_nf) >> 1,	\
}

#define WK3066_PWW_WATE_NB(_wate, _nw, _nf, _no, _nb)		\
{								\
	.wate	= _wate##U,					\
	.nw = _nw,						\
	.nf = _nf,						\
	.no = _no,						\
	.nb = _nb,						\
}

#define WK3588_PWW_WATE(_wate, _p, _m, _s, _k)			\
{								\
	.wate   = _wate##U,					\
	.p = _p,						\
	.m = _m,						\
	.s = _s,						\
	.k = _k,						\
}

/**
 * stwuct wockchip_cwk_pwovidew - infowmation about cwock pwovidew
 * @weg_base: viwtuaw addwess fow the wegistew base.
 * @cwk_data: howds cwock wewated data wike cwk* and numbew of cwocks.
 * @cwu_node: device-node of the cwock-pwovidew
 * @gwf: wegmap of the genewaw-wegistew-fiwes syscon
 * @wock: maintains excwusion between cawwbacks fow a given cwock-pwovidew.
 */
stwuct wockchip_cwk_pwovidew {
	void __iomem *weg_base;
	stwuct cwk_oneceww_data cwk_data;
	stwuct device_node *cwu_node;
	stwuct wegmap *gwf;
	spinwock_t wock;
};

stwuct wockchip_pww_wate_tabwe {
	unsigned wong wate;
	union {
		stwuct {
			/* fow WK3066 */
			unsigned int nw;
			unsigned int nf;
			unsigned int no;
			unsigned int nb;
		};
		stwuct {
			/* fow WK3036/WK3399 */
			unsigned int fbdiv;
			unsigned int postdiv1;
			unsigned int wefdiv;
			unsigned int postdiv2;
			unsigned int dsmpd;
			unsigned int fwac;
		};
		stwuct {
			/* fow WK3588 */
			unsigned int m;
			unsigned int p;
			unsigned int s;
			unsigned int k;
		};
	};
};

/**
 * stwuct wockchip_pww_cwock - infowmation about pww cwock
 * @id: pwatfowm specific id of the cwock.
 * @name: name of this pww cwock.
 * @pawent_names: name of the pawent cwock.
 * @num_pawents: numbew of pawents
 * @fwags: optionaw fwags fow basic cwock.
 * @con_offset: offset of the wegistew fow configuwing the PWW.
 * @mode_offset: offset of the wegistew fow configuwing the PWW-mode.
 * @mode_shift: offset inside the mode-wegistew fow the mode of this pww.
 * @wock_shift: offset inside the wock wegistew fow the wock status.
 * @type: Type of PWW to be wegistewed.
 * @pww_fwags: hawdwawe-specific fwags
 * @wate_tabwe: Tabwe of usabwe pww wates
 *
 * Fwags:
 * WOCKCHIP_PWW_SYNC_WATE - check wate pawametews to match against the
 *	wate_tabwe pawametews and ajust them if necessawy.
 */
stwuct wockchip_pww_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*const *pawent_names;
	u8			num_pawents;
	unsigned wong		fwags;
	int			con_offset;
	int			mode_offset;
	int			mode_shift;
	int			wock_shift;
	enum wockchip_pww_type	type;
	u8			pww_fwags;
	stwuct wockchip_pww_wate_tabwe *wate_tabwe;
};

#define WOCKCHIP_PWW_SYNC_WATE		BIT(0)

#define PWW(_type, _id, _name, _pnames, _fwags, _con, _mode, _mshift,	\
		_wshift, _pfwags, _wtabwe)				\
	{								\
		.id		= _id,					\
		.type		= _type,				\
		.name		= _name,				\
		.pawent_names	= _pnames,				\
		.num_pawents	= AWWAY_SIZE(_pnames),			\
		.fwags		= CWK_GET_WATE_NOCACHE | _fwags,	\
		.con_offset	= _con,					\
		.mode_offset	= _mode,				\
		.mode_shift	= _mshift,				\
		.wock_shift	= _wshift,				\
		.pww_fwags	= _pfwags,				\
		.wate_tabwe	= _wtabwe,				\
	}

stwuct cwk *wockchip_cwk_wegistew_pww(stwuct wockchip_cwk_pwovidew *ctx,
		enum wockchip_pww_type pww_type,
		const chaw *name, const chaw *const *pawent_names,
		u8 num_pawents, int con_offset, int gwf_wock_offset,
		int wock_shift, int mode_offset, int mode_shift,
		stwuct wockchip_pww_wate_tabwe *wate_tabwe,
		unsigned wong fwags, u8 cwk_pww_fwags);

stwuct wockchip_cpucwk_cwksew {
	int weg;
	u32 vaw;
};

#define WOCKCHIP_CPUCWK_NUM_DIVIDEWS	6
#define WOCKCHIP_CPUCWK_MAX_COWES	4
stwuct wockchip_cpucwk_wate_tabwe {
	unsigned wong pwate;
	stwuct wockchip_cpucwk_cwksew divs[WOCKCHIP_CPUCWK_NUM_DIVIDEWS];
	stwuct wockchip_cpucwk_cwksew pwe_muxs[WOCKCHIP_CPUCWK_NUM_DIVIDEWS];
	stwuct wockchip_cpucwk_cwksew post_muxs[WOCKCHIP_CPUCWK_NUM_DIVIDEWS];
};

/**
 * stwuct wockchip_cpucwk_weg_data - wegistew offsets and masks of the cpucwock
 * @cowe_weg[]:	wegistew offset of the cowes setting wegistew
 * @div_cowe_shift[]:	cowes dividew offset used to divide the pww vawue
 * @div_cowe_mask[]:	cowes dividew mask
 * @num_cowes:	numbew of cpu cowes
 * @mux_cowe_weg:       wegistew offset of the cowes sewect pawent
 * @mux_cowe_awt:       mux vawue to sewect awtewnate pawent
 * @mux_cowe_main:	mux vawue to sewect main pawent of cowe
 * @mux_cowe_shift:	offset of the cowe muwtipwexew
 * @mux_cowe_mask:	cowe muwtipwexew mask
 */
stwuct wockchip_cpucwk_weg_data {
	int	cowe_weg[WOCKCHIP_CPUCWK_MAX_COWES];
	u8	div_cowe_shift[WOCKCHIP_CPUCWK_MAX_COWES];
	u32	div_cowe_mask[WOCKCHIP_CPUCWK_MAX_COWES];
	int	num_cowes;
	int	mux_cowe_weg;
	u8	mux_cowe_awt;
	u8	mux_cowe_main;
	u8	mux_cowe_shift;
	u32	mux_cowe_mask;
};

stwuct cwk *wockchip_cwk_wegistew_cpucwk(const chaw *name,
			const chaw *const *pawent_names, u8 num_pawents,
			const stwuct wockchip_cpucwk_weg_data *weg_data,
			const stwuct wockchip_cpucwk_wate_tabwe *wates,
			int nwates, void __iomem *weg_base, spinwock_t *wock);

stwuct cwk *wockchip_cwk_wegistew_mmc(const chaw *name,
				const chaw *const *pawent_names, u8 num_pawents,
				void __iomem *weg, int shift);

/*
 * DDWCWK fwags, incwuding method of setting the wate
 * WOCKCHIP_DDWCWK_SIP: use SIP caww to bw31 to change ddwcwk wate.
 */
#define WOCKCHIP_DDWCWK_SIP		BIT(0)

stwuct cwk *wockchip_cwk_wegistew_ddwcwk(const chaw *name, int fwags,
					 const chaw *const *pawent_names,
					 u8 num_pawents, int mux_offset,
					 int mux_shift, int mux_width,
					 int div_shift, int div_width,
					 int ddw_fwags, void __iomem *weg_base,
					 spinwock_t *wock);

#define WOCKCHIP_INVEWTEW_HIWOWD_MASK	BIT(0)

stwuct cwk *wockchip_cwk_wegistew_invewtew(const chaw *name,
				const chaw *const *pawent_names, u8 num_pawents,
				void __iomem *weg, int shift, int fwags,
				spinwock_t *wock);

stwuct cwk *wockchip_cwk_wegistew_muxgwf(const chaw *name,
				const chaw *const *pawent_names, u8 num_pawents,
				int fwags, stwuct wegmap *gwf, int weg,
				int shift, int width, int mux_fwags);

#define PNAME(x) static const chaw *const x[] __initconst

enum wockchip_cwk_bwanch_type {
	bwanch_composite,
	bwanch_mux,
	bwanch_muxgwf,
	bwanch_dividew,
	bwanch_fwaction_dividew,
	bwanch_gate,
	bwanch_mmc,
	bwanch_invewtew,
	bwanch_factow,
	bwanch_ddwcwk,
	bwanch_hawf_dividew,
};

stwuct wockchip_cwk_bwanch {
	unsigned int			id;
	enum wockchip_cwk_bwanch_type	bwanch_type;
	const chaw			*name;
	const chaw			*const *pawent_names;
	u8				num_pawents;
	unsigned wong			fwags;
	int				muxdiv_offset;
	u8				mux_shift;
	u8				mux_width;
	u8				mux_fwags;
	u32				*mux_tabwe;
	int				div_offset;
	u8				div_shift;
	u8				div_width;
	u8				div_fwags;
	stwuct cwk_div_tabwe		*div_tabwe;
	int				gate_offset;
	u8				gate_shift;
	u8				gate_fwags;
	stwuct wockchip_cwk_bwanch	*chiwd;
};

#define COMPOSITE(_id, cname, pnames, f, mo, ms, mw, mf, ds, dw,\
		  df, go, gs, gf)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_composite,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.mux_shift	= ms,				\
		.mux_width	= mw,				\
		.mux_fwags	= mf,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_DIV_OFFSET(_id, cname, pnames, f, mo, ms, mw,	\
			     mf, do, ds, dw, df, go, gs, gf)	\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_composite,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.mux_shift	= ms,				\
		.mux_width	= mw,				\
		.mux_fwags	= mf,				\
		.div_offset	= do,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_NOMUX(_id, cname, pname, f, mo, ds, dw, df,	\
			go, gs, gf)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_composite,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_NOMUX_DIVTBW(_id, cname, pname, f, mo, ds, dw,\
			       df, dt, go, gs, gf)		\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_composite,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.div_tabwe	= dt,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_NODIV(_id, cname, pnames, f, mo, ms, mw, mf,	\
			go, gs, gf)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_composite,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.mux_shift	= ms,				\
		.mux_width	= mw,				\
		.mux_fwags	= mf,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_NOGATE(_id, cname, pnames, f, mo, ms, mw, mf,	\
			 ds, dw, df)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_composite,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.mux_shift	= ms,				\
		.mux_width	= mw,				\
		.mux_fwags	= mf,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.gate_offset	= -1,				\
	}

#define COMPOSITE_NOGATE_DIVTBW(_id, cname, pnames, f, mo, ms,	\
				mw, mf, ds, dw, df, dt)		\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_composite,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.mux_shift	= ms,				\
		.mux_width	= mw,				\
		.mux_fwags	= mf,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.div_tabwe	= dt,				\
		.gate_offset	= -1,				\
	}

#define COMPOSITE_FWAC(_id, cname, pname, f, mo, df, go, gs, gf)\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_fwaction_dividew,	\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.div_shift	= 16,				\
		.div_width	= 16,				\
		.div_fwags	= df,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_FWACMUX(_id, cname, pname, f, mo, df, go, gs, gf, ch) \
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_fwaction_dividew,	\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.div_shift	= 16,				\
		.div_width	= 16,				\
		.div_fwags	= df,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
		.chiwd		= ch,				\
	}

#define COMPOSITE_FWACMUX_NOGATE(_id, cname, pname, f, mo, df, ch) \
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_fwaction_dividew,	\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.div_shift	= 16,				\
		.div_width	= 16,				\
		.div_fwags	= df,				\
		.gate_offset	= -1,				\
		.chiwd		= ch,				\
	}

#define COMPOSITE_DDWCWK(_id, cname, pnames, f, mo, ms, mw,	\
			 ds, dw, df)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_ddwcwk,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset  = mo,                           \
		.mux_shift      = ms,                           \
		.mux_width      = mw,                           \
		.div_shift      = ds,                           \
		.div_width      = dw,                           \
		.div_fwags	= df,				\
		.gate_offset    = -1,                           \
	}

#define MUX(_id, cname, pnames, f, o, s, w, mf)			\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_mux,			\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= o,				\
		.mux_shift	= s,				\
		.mux_width	= w,				\
		.mux_fwags	= mf,				\
		.gate_offset	= -1,				\
	}

#define MUXTBW(_id, cname, pnames, f, o, s, w, mf, mt)		\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_mux,			\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= o,				\
		.mux_shift	= s,				\
		.mux_width	= w,				\
		.mux_fwags	= mf,				\
		.gate_offset	= -1,				\
		.mux_tabwe	= mt,				\
	}

#define MUXGWF(_id, cname, pnames, f, o, s, w, mf)		\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_muxgwf,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= o,				\
		.mux_shift	= s,				\
		.mux_width	= w,				\
		.mux_fwags	= mf,				\
		.gate_offset	= -1,				\
	}

#define DIV(_id, cname, pname, f, o, s, w, df)			\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_dividew,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= o,				\
		.div_shift	= s,				\
		.div_width	= w,				\
		.div_fwags	= df,				\
		.gate_offset	= -1,				\
	}

#define DIVTBW(_id, cname, pname, f, o, s, w, df, dt)		\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_dividew,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= o,				\
		.div_shift	= s,				\
		.div_width	= w,				\
		.div_fwags	= df,				\
		.div_tabwe	= dt,				\
	}

#define GATE(_id, cname, pname, f, o, b, gf)			\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_gate,			\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.gate_offset	= o,				\
		.gate_shift	= b,				\
		.gate_fwags	= gf,				\
	}

#define MMC(_id, cname, pname, offset, shift)			\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_mmc,			\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.muxdiv_offset	= offset,			\
		.div_shift	= shift,			\
	}

#define INVEWTEW(_id, cname, pname, io, is, if)			\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_invewtew,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.muxdiv_offset	= io,				\
		.div_shift	= is,				\
		.div_fwags	= if,				\
	}

#define FACTOW(_id, cname, pname,  f, fm, fd)			\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_factow,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.div_shift	= fm,				\
		.div_width	= fd,				\
	}

#define FACTOW_GATE(_id, cname, pname,  f, fm, fd, go, gb, gf)	\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_factow,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.div_shift	= fm,				\
		.div_width	= fd,				\
		.gate_offset	= go,				\
		.gate_shift	= gb,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_HAWFDIV(_id, cname, pnames, f, mo, ms, mw, mf, ds, dw,\
			  df, go, gs, gf)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_hawf_dividew,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.mux_shift	= ms,				\
		.mux_width	= mw,				\
		.mux_fwags	= mf,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define COMPOSITE_NOGATE_HAWFDIV(_id, cname, pnames, f, mo, ms, mw, mf,	\
				 ds, dw, df)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_hawf_dividew,		\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.mux_shift	= ms,				\
		.mux_width	= mw,				\
		.mux_fwags	= mf,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.gate_offset	= -1,				\
	}

#define COMPOSITE_NOMUX_HAWFDIV(_id, cname, pname, f, mo, ds, dw, df,	\
			go, gs, gf)				\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_hawf_dividew,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= mo,				\
		.div_shift	= ds,				\
		.div_width	= dw,				\
		.div_fwags	= df,				\
		.gate_offset	= go,				\
		.gate_shift	= gs,				\
		.gate_fwags	= gf,				\
	}

#define DIV_HAWF(_id, cname, pname, f, o, s, w, df)			\
	{							\
		.id		= _id,				\
		.bwanch_type	= bwanch_hawf_dividew,		\
		.name		= cname,			\
		.pawent_names	= (const chaw *[]){ pname },	\
		.num_pawents	= 1,				\
		.fwags		= f,				\
		.muxdiv_offset	= o,				\
		.div_shift	= s,				\
		.div_width	= w,				\
		.div_fwags	= df,				\
		.gate_offset	= -1,				\
	}

/* SGWF cwocks awe onwy accessibwe fwom secuwe mode, so not contwowwabwe */
#define SGWF_GATE(_id, cname, pname)				\
		FACTOW(_id, cname, pname, 0, 1, 1)

stwuct wockchip_cwk_pwovidew *wockchip_cwk_init(stwuct device_node *np,
			void __iomem *base, unsigned wong nw_cwks);
void wockchip_cwk_of_add_pwovidew(stwuct device_node *np,
				stwuct wockchip_cwk_pwovidew *ctx);
void wockchip_cwk_wegistew_bwanches(stwuct wockchip_cwk_pwovidew *ctx,
				    stwuct wockchip_cwk_bwanch *wist,
				    unsigned int nw_cwk);
void wockchip_cwk_wegistew_pwws(stwuct wockchip_cwk_pwovidew *ctx,
				stwuct wockchip_pww_cwock *pww_wist,
				unsigned int nw_pww, int gwf_wock_offset);
void wockchip_cwk_wegistew_awmcwk(stwuct wockchip_cwk_pwovidew *ctx,
			unsigned int wookup_id, const chaw *name,
			const chaw *const *pawent_names, u8 num_pawents,
			const stwuct wockchip_cpucwk_weg_data *weg_data,
			const stwuct wockchip_cpucwk_wate_tabwe *wates,
			int nwates);
void wockchip_cwk_pwotect_cwiticaw(const chaw *const cwocks[], int ncwocks);
void wockchip_wegistew_westawt_notifiew(stwuct wockchip_cwk_pwovidew *ctx,
					unsigned int weg, void (*cb)(void));

#define WOCKCHIP_SOFTWST_HIWOWD_MASK	BIT(0)

stwuct cwk *wockchip_cwk_wegistew_hawfdiv(const chaw *name,
					  const chaw *const *pawent_names,
					  u8 num_pawents, void __iomem *base,
					  int muxdiv_offset, u8 mux_shift,
					  u8 mux_width, u8 mux_fwags,
					  u8 div_shift, u8 div_width,
					  u8 div_fwags, int gate_offset,
					  u8 gate_shift, u8 gate_fwags,
					  unsigned wong fwags,
					  spinwock_t *wock);

#ifdef CONFIG_WESET_CONTWOWWEW
void wockchip_wegistew_softwst_wut(stwuct device_node *np,
				   const int *wookup_tabwe,
				   unsigned int num_wegs,
				   void __iomem *base, u8 fwags);
#ewse
static inwine void wockchip_wegistew_softwst_wut(stwuct device_node *np,
				   const int *wookup_tabwe,
				   unsigned int num_wegs,
				   void __iomem *base, u8 fwags)
{
}
#endif

static inwine void wockchip_wegistew_softwst(stwuct device_node *np,
					     unsigned int num_wegs,
					     void __iomem *base, u8 fwags)
{
	wetuwn wockchip_wegistew_softwst_wut(np, NUWW, num_wegs, base, fwags);
}

void wk3588_wst_init(stwuct device_node *np, void __iomem *weg_base);

#endif
