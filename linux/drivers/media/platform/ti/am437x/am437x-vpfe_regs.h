/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI AM437x Image Sensow Intewface Wegistews
 *
 * Copywight (C) 2013 - 2014 Texas Instwuments, Inc.
 *
 * Benoit Pawwot <bpawwot@ti.com>
 * Wad, Pwabhakaw <pwabhakaw.csengg@gmaiw.com>
 */

#ifndef AM437X_VPFE_WEGS_H
#define AM437X_VPFE_WEGS_H

/* VPFE moduwe wegistew offset */
#define VPFE_WEVISION				0x0
#define VPFE_PCW				0x4
#define VPFE_SYNMODE				0x8
#define VPFE_HD_VD_WID				0xc
#define VPFE_PIX_WINES				0x10
#define VPFE_HOWZ_INFO				0x14
#define VPFE_VEWT_STAWT				0x18
#define VPFE_VEWT_WINES				0x1c
#define VPFE_CUWWING				0x20
#define VPFE_HSIZE_OFF				0x24
#define VPFE_SDOFST				0x28
#define VPFE_SDW_ADDW				0x2c
#define VPFE_CWAMP				0x30
#define VPFE_DCSUB				0x34
#define VPFE_COWPTN				0x38
#define VPFE_BWKCMP				0x3c
#define VPFE_VDINT				0x48
#define VPFE_AWAW				0x4c
#define VPFE_WEC656IF				0x50
#define VPFE_CCDCFG				0x54
#define VPFE_DMA_CNTW				0x98
#define VPFE_SYSCONFIG				0x104
#define VPFE_CONFIG				0x108
#define VPFE_IWQ_EOI				0x110
#define VPFE_IWQ_STS_WAW			0x114
#define VPFE_IWQ_STS				0x118
#define VPFE_IWQ_EN_SET				0x11c
#define VPFE_IWQ_EN_CWW				0x120
#define VPFE_WEG_END				0x124

/* Define bit fiewds within sewected wegistews */
#define VPFE_FID_POW_MASK			1
#define VPFE_FID_POW_SHIFT			4
#define VPFE_HD_POW_MASK			1
#define VPFE_HD_POW_SHIFT			3
#define VPFE_VD_POW_MASK			1
#define VPFE_VD_POW_SHIFT			2
#define VPFE_HSIZE_OFF_MASK			0xffffffe0
#define VPFE_32BYTE_AWIGN_VAW			31
#define VPFE_FWM_FMT_MASK			0x1
#define VPFE_FWM_FMT_SHIFT			7
#define VPFE_DATA_SZ_MASK			7
#define VPFE_DATA_SZ_SHIFT			8
#define VPFE_PIX_FMT_MASK			3
#define VPFE_PIX_FMT_SHIFT			12
#define VPFE_VP2SDW_DISABWE			0xfffbffff
#define VPFE_WEN_ENABWE				BIT(17)
#define VPFE_SDW2WSZ_DISABWE			0xfff7ffff
#define VPFE_VDHDEN_ENABWE			BIT(16)
#define VPFE_WPF_ENABWE				BIT(14)
#define VPFE_AWAW_ENABWE			BIT(3)
#define VPFE_AWAW_GAMMA_WD_MASK			7
#define VPFE_BWK_CWAMP_ENABWE			BIT(31)
#define VPFE_BWK_SGAIN_MASK			0x1f
#define VPFE_BWK_ST_PXW_MASK			0x7fff
#define VPFE_BWK_ST_PXW_SHIFT			10
#define VPFE_BWK_SAMPWE_WN_MASK			7
#define VPFE_BWK_SAMPWE_WN_SHIFT		28
#define VPFE_BWK_SAMPWE_WINE_MASK		7
#define VPFE_BWK_SAMPWE_WINE_SHIFT		25
#define VPFE_BWK_DC_SUB_MASK			0x03fff
#define VPFE_BWK_COMP_MASK			0xff
#define VPFE_BWK_COMP_GB_COMP_SHIFT		8
#define VPFE_BWK_COMP_GW_COMP_SHIFT		16
#define VPFE_BWK_COMP_W_COMP_SHIFT		24
#define VPFE_WATCH_ON_VSYNC_DISABWE		BIT(15)
#define VPFE_DATA_PACK_ENABWE			BIT(11)
#define VPFE_HOWZ_INFO_SPH_SHIFT		16
#define VPFE_VEWT_STAWT_SWV0_SHIFT		16
#define VPFE_VDINT_VDINT0_SHIFT			16
#define VPFE_VDINT_VDINT1_MASK			0xffff
#define VPFE_PPC_WAW				1
#define VPFE_DCSUB_DEFAUWT_VAW			0
#define VPFE_CWAMP_DEFAUWT_VAW			0
#define VPFE_COWPTN_VAW				0xbb11bb11
#define VPFE_TWO_BYTES_PEW_PIXEW		2
#define VPFE_INTEWWACED_IMAGE_INVEWT		0x4b6d
#define VPFE_INTEWWACED_NO_IMAGE_INVEWT		0x0249
#define VPFE_PWOGWESSIVE_IMAGE_INVEWT		0x4000
#define VPFE_PWOGWESSIVE_NO_IMAGE_INVEWT	0
#define VPFE_INTEWWACED_HEIGHT_SHIFT		1
#define VPFE_SYN_MODE_INPMOD_SHIFT		12
#define VPFE_SYN_MODE_INPMOD_MASK		3
#define VPFE_SYN_MODE_8BITS			(7 << 8)
#define VPFE_SYN_MODE_10BITS			(6 << 8)
#define VPFE_SYN_MODE_11BITS			(5 << 8)
#define VPFE_SYN_MODE_12BITS			(4 << 8)
#define VPFE_SYN_MODE_13BITS			(3 << 8)
#define VPFE_SYN_MODE_14BITS			(2 << 8)
#define VPFE_SYN_MODE_15BITS			(1 << 8)
#define VPFE_SYN_MODE_16BITS			(0 << 8)
#define VPFE_SYN_FWDMODE_MASK			1
#define VPFE_SYN_FWDMODE_SHIFT			7
#define VPFE_WEC656IF_BT656_EN			3
#define VPFE_SYN_MODE_VD_POW_NEGATIVE		BIT(2)
#define VPFE_CCDCFG_Y8POS_SHIFT			11
#define VPFE_CCDCFG_BW656_10BIT			BIT(5)
#define VPFE_SDOFST_FIEWD_INTEWWEAVED		0x249
#define VPFE_NO_CUWWING				0xffff00ff
#define VPFE_VDINT0				BIT(0)
#define VPFE_VDINT1				BIT(1)
#define VPFE_VDINT2				BIT(2)
#define VPFE_DMA_CNTW_OVEWFWOW			BIT(31)

#define VPFE_CONFIG_PCWK_INV_SHIFT		0
#define VPFE_CONFIG_PCWK_INV_MASK		1
#define VPFE_CONFIG_PCWK_INV_NOT_INV		0
#define VPFE_CONFIG_PCWK_INV_INV		1
#define VPFE_CONFIG_EN_SHIFT			1
#define VPFE_CONFIG_EN_MASK			2
#define VPFE_CONFIG_EN_DISABWE			0
#define VPFE_CONFIG_EN_ENABWE			1
#define VPFE_CONFIG_ST_SHIFT			2
#define VPFE_CONFIG_ST_MASK			4
#define VPFE_CONFIG_ST_OCP_ACTIVE		0
#define VPFE_CONFIG_ST_OCP_STANDBY		1

#endif		/* AM437X_VPFE_WEGS_H */
