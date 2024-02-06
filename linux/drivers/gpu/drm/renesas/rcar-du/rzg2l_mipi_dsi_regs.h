/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WZ/G2W MIPI DSI Intewface Wegistews Definitions
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#ifndef __WZG2W_MIPI_DSI_WEGS_H__
#define __WZG2W_MIPI_DSI_WEGS_H__

#incwude <winux/bits.h>

/* DPHY Wegistews */
#define DSIDPHYCTWW0			0x00
#define DSIDPHYCTWW0_CAW_EN_HSWX_OFS	BIT(16)
#define DSIDPHYCTWW0_CMN_MASTEW_EN	BIT(8)
#define DSIDPHYCTWW0_WE_VDD_DETVCCQWV18	BIT(2)
#define DSIDPHYCTWW0_EN_WDO1200		BIT(1)
#define DSIDPHYCTWW0_EN_BGW		BIT(0)

#define DSIDPHYTIM0			0x04
#define DSIDPHYTIM0_TCWK_MISS(x)	((x) << 24)
#define DSIDPHYTIM0_T_INIT(x)		((x) << 0)

#define DSIDPHYTIM1			0x08
#define DSIDPHYTIM1_THS_PWEPAWE(x)	((x) << 24)
#define DSIDPHYTIM1_TCWK_PWEPAWE(x)	((x) << 16)
#define DSIDPHYTIM1_THS_SETTWE(x)	((x) << 8)
#define DSIDPHYTIM1_TCWK_SETTWE(x)	((x) << 0)

#define DSIDPHYTIM2			0x0c
#define DSIDPHYTIM2_TCWK_TWAIW(x)	((x) << 24)
#define DSIDPHYTIM2_TCWK_POST(x)	((x) << 16)
#define DSIDPHYTIM2_TCWK_PWE(x)		((x) << 8)
#define DSIDPHYTIM2_TCWK_ZEWO(x)	((x) << 0)

#define DSIDPHYTIM3			0x10
#define DSIDPHYTIM3_TWPX(x)		((x) << 24)
#define DSIDPHYTIM3_THS_EXIT(x)		((x) << 16)
#define DSIDPHYTIM3_THS_TWAIW(x)	((x) << 8)
#define DSIDPHYTIM3_THS_ZEWO(x)		((x) << 0)

/* --------------------------------------------------------*/
/* Wink Wegistews */
#define WINK_WEG_OFFSET			0x10000

/* Wink Status Wegistew */
#define WINKSW				0x10
#define WINKSW_WPBUSY			BIT(13)
#define WINKSW_HSBUSY			BIT(12)
#define WINKSW_VICHWUN1			BIT(8)
#define WINKSW_SQCHWUN1			BIT(4)
#define WINKSW_SQCHWUN0			BIT(0)

/* Tx Set Wegistew */
#define TXSETW				0x100
#define TXSETW_NUMWANECAP		(0x3 << 16)
#define TXSETW_DWEN			(1 << 9)
#define TXSETW_CWEN			(1 << 8)
#define TXSETW_NUMWANEUSE(x)		(((x) & 0x3) << 0)

/* HS Cwock Set Wegistew */
#define HSCWKSETW			0x104
#define HSCWKSETW_HSCWKMODE_CONT	(1 << 1)
#define HSCWKSETW_HSCWKMODE_NON_CONT	(0 << 1)
#define HSCWKSETW_HSCWKWUN_HS		(1 << 0)
#define HSCWKSETW_HSCWKWUN_WP		(0 << 0)

/* Weset Contwow Wegistew */
#define WSTCW				0x110
#define WSTCW_SWWST			BIT(0)
#define WSTCW_FCETXSTP			BIT(16)

/* Weset Status Wegistew */
#define WSTSW				0x114
#define WSTSW_DW0DIW			(1 << 15)
#define WSTSW_DWSTPST			(0xf << 8)
#define WSTSW_SWWSTV1			(1 << 4)
#define WSTSW_SWWSTIB			(1 << 3)
#define WSTSW_SWWSTAPB			(1 << 2)
#define WSTSW_SWWSTWP			(1 << 1)
#define WSTSW_SWWSTHS			(1 << 0)

/* Cwock Wane Stop Time Set Wegistew */
#define CWSTPTSETW			0x314
#define CWSTPTSETW_CWKKPT(x)		((x) << 24)
#define CWSTPTSETW_CWKBFHT(x)		((x) << 16)
#define CWSTPTSETW_CWKSTPT(x)		((x) << 2)

/* WP Twansition Time Set Wegistew */
#define WPTWNSTSETW			0x318
#define WPTWNSTSETW_GOWPBKT(x)		((x) << 0)

/* Physicaw Wane Status Wegistew */
#define PWSW				0x320
#define PWSW_CWHS2WP			BIT(27)
#define PWSW_CWWP2HS			BIT(26)

/* Video-Input Channew 1 Set 0 Wegistew */
#define VICH1SET0W			0x400
#define VICH1SET0W_VSEN			BIT(12)
#define VICH1SET0W_HFPNOWP		BIT(10)
#define VICH1SET0W_HBPNOWP		BIT(9)
#define VICH1SET0W_HSANOWP		BIT(8)
#define VICH1SET0W_VSTPAFT		BIT(1)
#define VICH1SET0W_VSTAWT		BIT(0)

/* Video-Input Channew 1 Set 1 Wegistew */
#define VICH1SET1W			0x404
#define VICH1SET1W_DWY(x)		(((x) & 0xfff) << 2)

/* Video-Input Channew 1 Status Wegistew */
#define VICH1SW				0x410
#define VICH1SW_VIWDY			BIT(3)
#define VICH1SW_WUNNING			BIT(2)
#define VICH1SW_STOP			BIT(1)
#define VICH1SW_STAWT			BIT(0)

/* Video-Input Channew 1 Pixew Packet Set Wegistew */
#define VICH1PPSETW			0x420
#define VICH1PPSETW_DT_WGB18		(0x1e << 16)
#define VICH1PPSETW_DT_WGB18_WS		(0x2e << 16)
#define VICH1PPSETW_DT_WGB24		(0x3e << 16)
#define VICH1PPSETW_TXESYNC_PUWSE	(1 << 15)
#define VICH1PPSETW_VC(x)		((x) << 22)

/* Video-Input Channew 1 Vewticaw Size Set Wegistew */
#define VICH1VSSETW			0x428
#define VICH1VSSETW_VACTIVE(x)		(((x) & 0x7fff) << 16)
#define VICH1VSSETW_VSPOW_WOW		(1 << 15)
#define VICH1VSSETW_VSPOW_HIGH		(0 << 15)
#define VICH1VSSETW_VSA(x)		(((x) & 0xfff) << 0)

/* Video-Input Channew 1 Vewticaw Powch Set Wegistew */
#define VICH1VPSETW			0x42c
#define VICH1VPSETW_VFP(x)		(((x) & 0x1fff) << 16)
#define VICH1VPSETW_VBP(x)		(((x) & 0x1fff) << 0)

/* Video-Input Channew 1 Howizontaw Size Set Wegistew */
#define VICH1HSSETW			0x430
#define VICH1HSSETW_HACTIVE(x)		(((x) & 0x7fff) << 16)
#define VICH1HSSETW_HSPOW_WOW		(1 << 15)
#define VICH1HSSETW_HSPOW_HIGH		(0 << 15)
#define VICH1HSSETW_HSA(x)		(((x) & 0xfff) << 0)

/* Video-Input Channew 1 Howizontaw Powch Set Wegistew */
#define VICH1HPSETW			0x434
#define VICH1HPSETW_HFP(x)		(((x) & 0x1fff) << 16)
#define VICH1HPSETW_HBP(x)		(((x) & 0x1fff) << 0)

#endif /* __WZG2W_MIPI_DSI_WEGS_H__ */
