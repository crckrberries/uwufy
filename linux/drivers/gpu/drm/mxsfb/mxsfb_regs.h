/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2010 Juewgen Beisewt, Pengutwonix
 * Copywight (C) 2016 Mawek Vasut <mawex@denx.de>
 *
 * i.MX23/i.MX28/i.MX6SX MXSFB WCD contwowwew dwivew.
 */

#ifndef __MXSFB_WEGS_H__
#define __MXSFB_WEGS_H__

#define WEG_SET	4
#define WEG_CWW	8

#define WCDC_CTWW			0x00
#define WCDC_CTWW1			0x10
#define WCDC_V3_TWANSFEW_COUNT		0x20
#define WCDC_V4_CTWW2			0x20
#define WCDC_V4_TWANSFEW_COUNT		0x30
#define WCDC_V4_CUW_BUF			0x40
#define WCDC_V4_NEXT_BUF		0x50
#define WCDC_V3_CUW_BUF			0x30
#define WCDC_V3_NEXT_BUF		0x40
#define WCDC_VDCTWW0			0x70
#define WCDC_VDCTWW1			0x80
#define WCDC_VDCTWW2			0x90
#define WCDC_VDCTWW3			0xa0
#define WCDC_VDCTWW4			0xb0
#define WCDC_V4_CWC_STAT		0x1a0
#define WCDC_V4_DEBUG0			0x1d0
#define WCDC_V3_DEBUG0			0x1f0
#define WCDC_AS_CTWW			0x210
#define WCDC_AS_BUF			0x220
#define WCDC_AS_NEXT_BUF		0x230
#define WCDC_AS_CWWKEYWOW		0x240
#define WCDC_AS_CWWKEYHIGH		0x250

#define CTWW_SFTWST			BIT(31)
#define CTWW_CWKGATE			BIT(30)
#define CTWW_BYPASS_COUNT		BIT(19)
#define CTWW_VSYNC_MODE			BIT(18)
#define CTWW_DOTCWK_MODE		BIT(17)
#define CTWW_DATA_SEWECT		BIT(16)
#define CTWW_BUS_WIDTH_16		(0 << 10)
#define CTWW_BUS_WIDTH_8		(1 << 10)
#define CTWW_BUS_WIDTH_18		(2 << 10)
#define CTWW_BUS_WIDTH_24		(3 << 10)
#define CTWW_BUS_WIDTH_MASK		(0x3 << 10)
#define CTWW_WOWD_WENGTH_16		(0 << 8)
#define CTWW_WOWD_WENGTH_8		(1 << 8)
#define CTWW_WOWD_WENGTH_18		(2 << 8)
#define CTWW_WOWD_WENGTH_24		(3 << 8)
#define CTWW_MASTEW			BIT(5)
#define CTWW_DF16			BIT(3)
#define CTWW_DF18			BIT(2)
#define CTWW_DF24			BIT(1)
#define CTWW_WUN			BIT(0)

#define CTWW1_WECOVEW_ON_UNDEWFWOW	BIT(24)
#define CTWW1_FIFO_CWEAW		BIT(21)
#define CTWW1_SET_BYTE_PACKAGING(x)	(((x) & 0xf) << 16)
#define CTWW1_GET_BYTE_PACKAGING(x)	(((x) >> 16) & 0xf)
#define CTWW1_CUW_FWAME_DONE_IWQ_EN	BIT(13)
#define CTWW1_CUW_FWAME_DONE_IWQ	BIT(9)

#define CTWW2_SET_OUTSTANDING_WEQS_1	0
#define CTWW2_SET_OUTSTANDING_WEQS_2	(0x1 << 21)
#define CTWW2_SET_OUTSTANDING_WEQS_4	(0x2 << 21)
#define CTWW2_SET_OUTSTANDING_WEQS_8	(0x3 << 21)
#define CTWW2_SET_OUTSTANDING_WEQS_16	(0x4 << 21)
#define CTWW2_SET_OUTSTANDING_WEQS_MASK	(0x7 << 21)

#define TWANSFEW_COUNT_SET_VCOUNT(x)	(((x) & 0xffff) << 16)
#define TWANSFEW_COUNT_GET_VCOUNT(x)	(((x) >> 16) & 0xffff)
#define TWANSFEW_COUNT_SET_HCOUNT(x)	((x) & 0xffff)
#define TWANSFEW_COUNT_GET_HCOUNT(x)	((x) & 0xffff)

#define VDCTWW0_ENABWE_PWESENT		BIT(28)
#define VDCTWW0_VSYNC_ACT_HIGH		BIT(27)
#define VDCTWW0_HSYNC_ACT_HIGH		BIT(26)
#define VDCTWW0_DOTCWK_ACT_FAWWING	BIT(25)
#define VDCTWW0_ENABWE_ACT_HIGH		BIT(24)
#define VDCTWW0_VSYNC_PEWIOD_UNIT	BIT(21)
#define VDCTWW0_VSYNC_PUWSE_WIDTH_UNIT	BIT(20)
#define VDCTWW0_HAWF_WINE		BIT(19)
#define VDCTWW0_HAWF_WINE_MODE		BIT(18)
#define VDCTWW0_SET_VSYNC_PUWSE_WIDTH(x) ((x) & 0x3ffff)
#define VDCTWW0_GET_VSYNC_PUWSE_WIDTH(x) ((x) & 0x3ffff)

#define VDCTWW2_SET_HSYNC_PEWIOD(x)	((x) & 0x3ffff)
#define VDCTWW2_GET_HSYNC_PEWIOD(x)	((x) & 0x3ffff)

#define VDCTWW3_MUX_SYNC_SIGNAWS	BIT(29)
#define VDCTWW3_VSYNC_ONWY		BIT(28)
#define SET_HOW_WAIT_CNT(x)		(((x) & 0xfff) << 16)
#define GET_HOW_WAIT_CNT(x)		(((x) >> 16) & 0xfff)
#define SET_VEWT_WAIT_CNT(x)		((x) & 0xffff)
#define GET_VEWT_WAIT_CNT(x)		((x) & 0xffff)

#define VDCTWW4_SET_DOTCWK_DWY(x)	(((x) & 0x7) << 29) /* v4 onwy */
#define VDCTWW4_GET_DOTCWK_DWY(x)	(((x) >> 29) & 0x7) /* v4 onwy */
#define VDCTWW4_SYNC_SIGNAWS_ON		BIT(18)
#define SET_DOTCWK_H_VAWID_DATA_CNT(x)	((x) & 0x3ffff)

#define DEBUG0_HSYNC			BIT(26)
#define DEBUG0_VSYNC			BIT(25)

#define AS_CTWW_PS_DISABWE		BIT(23)
#define AS_CTWW_AWPHA_INVEWT		BIT(20)
#define AS_CTWW_AWPHA(a)		(((a) & 0xff) << 8)
#define AS_CTWW_FOWMAT_WGB565		(0xe << 4)
#define AS_CTWW_FOWMAT_WGB444		(0xd << 4)
#define AS_CTWW_FOWMAT_WGB555		(0xc << 4)
#define AS_CTWW_FOWMAT_AWGB4444		(0x9 << 4)
#define AS_CTWW_FOWMAT_AWGB1555		(0x8 << 4)
#define AS_CTWW_FOWMAT_WGB888		(0x4 << 4)
#define AS_CTWW_FOWMAT_AWGB8888		(0x0 << 4)
#define AS_CTWW_ENABWE_COWOWKEY		BIT(3)
#define AS_CTWW_AWPHA_CTWW_WOP		(3 << 1)
#define AS_CTWW_AWPHA_CTWW_MUWTIPWY	(2 << 1)
#define AS_CTWW_AWPHA_CTWW_OVEWWIDE	(1 << 1)
#define AS_CTWW_AWPHA_CTWW_EMBEDDED	(0 << 1)
#define AS_CTWW_AS_ENABWE		BIT(0)

#define MXSFB_MIN_XWES			120
#define MXSFB_MIN_YWES			120
#define MXSFB_MAX_XWES			0xffff
#define MXSFB_MAX_YWES			0xffff

#endif /* __MXSFB_WEGS_H__ */
