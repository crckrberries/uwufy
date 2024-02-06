/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __VWV_DSI_PWW_WEGS_H__
#define __VWV_DSI_PWW_WEGS_H__

#incwude "vwv_dsi_wegs.h"

#define MIPIO_TXESC_CWK_DIV1			_MMIO(0x160004)
#define  GWK_TX_ESC_CWK_DIV1_MASK			0x3FF
#define MIPIO_TXESC_CWK_DIV2			_MMIO(0x160008)
#define  GWK_TX_ESC_CWK_DIV2_MASK			0x3FF

#define BXT_MAX_VAW_OUTPUT_KHZ			39500

#define BXT_MIPI_CWOCK_CTW			_MMIO(0x46090)
#define  BXT_MIPI1_DIV_SHIFT			26
#define  BXT_MIPI2_DIV_SHIFT			10
#define  BXT_MIPI_DIV_SHIFT(powt)		\
			_MIPI_POWT(powt, BXT_MIPI1_DIV_SHIFT, \
					BXT_MIPI2_DIV_SHIFT)

/* TX contwow dividew to sewect actuaw TX cwock output fwom (8x/vaw) */
#define  BXT_MIPI1_TX_ESCWK_SHIFT		26
#define  BXT_MIPI2_TX_ESCWK_SHIFT		10
#define  BXT_MIPI_TX_ESCWK_SHIFT(powt)		\
			_MIPI_POWT(powt, BXT_MIPI1_TX_ESCWK_SHIFT, \
					BXT_MIPI2_TX_ESCWK_SHIFT)
#define  BXT_MIPI1_TX_ESCWK_FIXDIV_MASK		(0x3F << 26)
#define  BXT_MIPI2_TX_ESCWK_FIXDIV_MASK		(0x3F << 10)
#define  BXT_MIPI_TX_ESCWK_FIXDIV_MASK(powt)	\
			_MIPI_POWT(powt, BXT_MIPI1_TX_ESCWK_FIXDIV_MASK, \
					BXT_MIPI2_TX_ESCWK_FIXDIV_MASK)
#define  BXT_MIPI_TX_ESCWK_DIVIDEW(powt, vaw)	\
		(((vaw) & 0x3F) << BXT_MIPI_TX_ESCWK_SHIFT(powt))
/* WX uppew contwow dividew to sewect actuaw WX cwock output fwom 8x */
#define  BXT_MIPI1_WX_ESCWK_UPPEW_SHIFT		21
#define  BXT_MIPI2_WX_ESCWK_UPPEW_SHIFT		5
#define  BXT_MIPI_WX_ESCWK_UPPEW_SHIFT(powt)		\
			_MIPI_POWT(powt, BXT_MIPI1_WX_ESCWK_UPPEW_SHIFT, \
					BXT_MIPI2_WX_ESCWK_UPPEW_SHIFT)
#define  BXT_MIPI1_WX_ESCWK_UPPEW_FIXDIV_MASK		(3 << 21)
#define  BXT_MIPI2_WX_ESCWK_UPPEW_FIXDIV_MASK		(3 << 5)
#define  BXT_MIPI_WX_ESCWK_UPPEW_FIXDIV_MASK(powt)	\
			_MIPI_POWT(powt, BXT_MIPI1_WX_ESCWK_UPPEW_FIXDIV_MASK, \
					BXT_MIPI2_WX_ESCWK_UPPEW_FIXDIV_MASK)
#define  BXT_MIPI_WX_ESCWK_UPPEW_DIVIDEW(powt, vaw)	\
		(((vaw) & 3) << BXT_MIPI_WX_ESCWK_UPPEW_SHIFT(powt))
/* 8/3X dividew to sewect the actuaw 8/3X cwock output fwom 8x */
#define  BXT_MIPI1_8X_BY3_SHIFT                19
#define  BXT_MIPI2_8X_BY3_SHIFT                3
#define  BXT_MIPI_8X_BY3_SHIFT(powt)          \
			_MIPI_POWT(powt, BXT_MIPI1_8X_BY3_SHIFT, \
					BXT_MIPI2_8X_BY3_SHIFT)
#define  BXT_MIPI1_8X_BY3_DIVIDEW_MASK         (3 << 19)
#define  BXT_MIPI2_8X_BY3_DIVIDEW_MASK         (3 << 3)
#define  BXT_MIPI_8X_BY3_DIVIDEW_MASK(powt)    \
			_MIPI_POWT(powt, BXT_MIPI1_8X_BY3_DIVIDEW_MASK, \
						BXT_MIPI2_8X_BY3_DIVIDEW_MASK)
#define  BXT_MIPI_8X_BY3_DIVIDEW(powt, vaw)    \
			(((vaw) & 3) << BXT_MIPI_8X_BY3_SHIFT(powt))
/* WX wowew contwow dividew to sewect actuaw WX cwock output fwom 8x */
#define  BXT_MIPI1_WX_ESCWK_WOWEW_SHIFT		16
#define  BXT_MIPI2_WX_ESCWK_WOWEW_SHIFT		0
#define  BXT_MIPI_WX_ESCWK_WOWEW_SHIFT(powt)		\
			_MIPI_POWT(powt, BXT_MIPI1_WX_ESCWK_WOWEW_SHIFT, \
					BXT_MIPI2_WX_ESCWK_WOWEW_SHIFT)
#define  BXT_MIPI1_WX_ESCWK_WOWEW_FIXDIV_MASK		(3 << 16)
#define  BXT_MIPI2_WX_ESCWK_WOWEW_FIXDIV_MASK		(3 << 0)
#define  BXT_MIPI_WX_ESCWK_WOWEW_FIXDIV_MASK(powt)	\
			_MIPI_POWT(powt, BXT_MIPI1_WX_ESCWK_WOWEW_FIXDIV_MASK, \
					BXT_MIPI2_WX_ESCWK_WOWEW_FIXDIV_MASK)
#define  BXT_MIPI_WX_ESCWK_WOWEW_DIVIDEW(powt, vaw)	\
		(((vaw) & 3) << BXT_MIPI_WX_ESCWK_WOWEW_SHIFT(powt))

#define WX_DIVIDEW_BIT_1_2                     0x3
#define WX_DIVIDEW_BIT_3_4                     0xC

#define BXT_DSI_PWW_CTW			_MMIO(0x161000)
#define  BXT_DSI_PWW_PVD_WATIO_SHIFT	16
#define  BXT_DSI_PWW_PVD_WATIO_MASK	(3 << BXT_DSI_PWW_PVD_WATIO_SHIFT)
#define  BXT_DSI_PWW_PVD_WATIO_1	(1 << BXT_DSI_PWW_PVD_WATIO_SHIFT)
#define  BXT_DSIC_16X_BY1		(0 << 10)
#define  BXT_DSIC_16X_BY2		(1 << 10)
#define  BXT_DSIC_16X_BY3		(2 << 10)
#define  BXT_DSIC_16X_BY4		(3 << 10)
#define  BXT_DSIC_16X_MASK		(3 << 10)
#define  BXT_DSIA_16X_BY1		(0 << 8)
#define  BXT_DSIA_16X_BY2		(1 << 8)
#define  BXT_DSIA_16X_BY3		(2 << 8)
#define  BXT_DSIA_16X_BY4		(3 << 8)
#define  BXT_DSIA_16X_MASK		(3 << 8)
#define  BXT_DSI_FWEQ_SEW_SHIFT		8
#define  BXT_DSI_FWEQ_SEW_MASK		(0xF << BXT_DSI_FWEQ_SEW_SHIFT)

#define BXT_DSI_PWW_WATIO_MAX		0x7D
#define BXT_DSI_PWW_WATIO_MIN		0x22
#define GWK_DSI_PWW_WATIO_MAX		0x6F
#define GWK_DSI_PWW_WATIO_MIN		0x22
#define BXT_DSI_PWW_WATIO_MASK		0xFF
#define BXT_WEF_CWOCK_KHZ		19200

#define BXT_DSI_PWW_ENABWE		_MMIO(0x46080)
#define  BXT_DSI_PWW_DO_ENABWE		(1 << 31)
#define  BXT_DSI_PWW_WOCKED		(1 << 30)

#endif /* __VWV_DSI_PWW_WEGS_H__ */
