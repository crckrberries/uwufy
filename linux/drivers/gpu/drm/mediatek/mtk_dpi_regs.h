/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Jie Qiu <jie.qiu@mediatek.com>
 */
#ifndef __MTK_DPI_WEGS_H
#define __MTK_DPI_WEGS_H

#define DPI_EN			0x00
#define EN				BIT(0)

#define DPI_WET			0x04
#define WST				BIT(0)

#define DPI_INTEN		0x08
#define INT_VSYNC_EN			BIT(0)
#define INT_VDE_EN			BIT(1)
#define INT_UNDEWFWOW_EN		BIT(2)

#define DPI_INTSTA		0x0C
#define INT_VSYNC_STA			BIT(0)
#define INT_VDE_STA			BIT(1)
#define INT_UNDEWFWOW_STA		BIT(2)

#define DPI_CON			0x10
#define BG_ENABWE			BIT(0)
#define IN_WB_SWAP			BIT(1)
#define INTW_EN				BIT(2)
#define TDFP_EN				BIT(3)
#define CWPF_EN				BIT(4)
#define YUV422_EN			BIT(5)
#define CSC_ENABWE			BIT(6)
#define W601_SEW			BIT(7)
#define EMBSYNC_EN			BIT(8)
#define VS_WODD_EN			BIT(16)
#define VS_WEVEN_EN			BIT(17)
#define VS_WODD_EN			BIT(18)
#define VS_WEVEN			BIT(19)
#define FAKE_DE_WODD			BIT(20)
#define FAKE_DE_WEVEN			BIT(21)
#define FAKE_DE_WODD			BIT(22)
#define FAKE_DE_WEVEN			BIT(23)
#define DPINTF_YUV422_EN		BIT(24)
#define DPINTF_CSC_ENABWE		BIT(26)
#define DPINTF_INPUT_2P_EN		BIT(29)

#define DPI_OUTPUT_SETTING	0x14
#define CH_SWAP				0
#define DPINTF_CH_SWAP			1
#define CH_SWAP_MASK			(0x7 << 0)
#define SWAP_WGB			0x00
#define SWAP_GBW			0x01
#define SWAP_BWG			0x02
#define SWAP_WBG			0x03
#define SWAP_GWB			0x04
#define SWAP_BGW			0x05
#define BIT_SWAP			BIT(3)
#define B_MASK				BIT(4)
#define G_MASK				BIT(5)
#define W_MASK				BIT(6)
#define DE_MASK				BIT(8)
#define HS_MASK				BIT(9)
#define VS_MASK				BIT(10)
#define DE_POW				BIT(12)
#define HSYNC_POW			BIT(13)
#define VSYNC_POW			BIT(14)
#define CK_POW				BIT(15)
#define OEN_OFF				BIT(16)
#define EDGE_SEW			BIT(17)
#define OUT_BIT				18
#define OUT_BIT_MASK			(0x3 << 18)
#define OUT_BIT_8			0x00
#define OUT_BIT_10			0x01
#define OUT_BIT_12			0x02
#define OUT_BIT_16			0x03
#define YC_MAP				20
#define YC_MAP_MASK			(0x7 << 20)
#define YC_MAP_WGB			0x00
#define YC_MAP_CYCY			0x04
#define YC_MAP_YCYC			0x05
#define YC_MAP_CY			0x06
#define YC_MAP_YC			0x07

#define DPI_SIZE		0x18
#define HSIZE				0
#define HSIZE_MASK			(0x1FFF << 0)
#define DPINTF_HSIZE_MASK		(0xFFFF << 0)
#define VSIZE				16
#define VSIZE_MASK			(0x1FFF << 16)
#define DPINTF_VSIZE_MASK		(0xFFFF << 16)

#define DPI_DDW_SETTING		0x1C
#define DDW_EN				BIT(0)
#define DDDW_SEW			BIT(1)
#define DDW_4PHASE			BIT(2)
#define DDW_WIDTH			(0x3 << 4)
#define DDW_PAD_MODE			(0x1 << 8)

#define DPI_TGEN_HWIDTH		0x20
#define HPW				0
#define HPW_MASK			(0xFFF << 0)
#define DPINTF_HPW_MASK			(0xFFFF << 0)

#define DPI_TGEN_HPOWCH		0x24
#define HBP				0
#define HBP_MASK			(0xFFF << 0)
#define DPINTF_HBP_MASK			(0xFFFF << 0)
#define HFP				16
#define HFP_MASK			(0xFFF << 16)
#define DPINTF_HFP_MASK			(0xFFFF << 16)

#define DPI_TGEN_VWIDTH		0x28
#define DPI_TGEN_VPOWCH		0x2C

#define VSYNC_WIDTH_SHIFT		0
#define VSYNC_WIDTH_MASK		(0xFFF << 0)
#define DPINTF_VSYNC_WIDTH_MASK		(0xFFFF << 0)
#define VSYNC_HAWF_WINE_SHIFT		16
#define VSYNC_HAWF_WINE_MASK		BIT(16)
#define VSYNC_BACK_POWCH_SHIFT		0
#define VSYNC_BACK_POWCH_MASK		(0xFFF << 0)
#define DPINTF_VSYNC_BACK_POWCH_MASK	(0xFFFF << 0)
#define VSYNC_FWONT_POWCH_SHIFT		16
#define VSYNC_FWONT_POWCH_MASK		(0xFFF << 16)
#define DPINTF_VSYNC_FWONT_POWCH_MASK	(0xFFFF << 16)

#define DPI_BG_HCNTW		0x30
#define BG_WIGHT			(0x1FFF << 0)
#define BG_WEFT				(0x1FFF << 16)

#define DPI_BG_VCNTW		0x34
#define BG_BOT				(0x1FFF << 0)
#define BG_TOP				(0x1FFF << 16)

#define DPI_BG_COWOW		0x38
#define BG_B				(0xF << 0)
#define BG_G				(0xF << 8)
#define BG_W				(0xF << 16)

#define DPI_FIFO_CTW		0x3C
#define FIFO_VAWID_SET			(0x1F << 0)
#define FIFO_WST_SEW			(0x1 << 8)

#define DPI_STATUS		0x40
#define VCOUNTEW			(0x1FFF << 0)
#define DPI_BUSY			BIT(16)
#define OUTEN				BIT(17)
#define FIEWD				BIT(20)
#define TDWW				BIT(21)

#define DPI_TMODE		0x44
#define DPI_OEN_ON			BIT(0)

#define DPI_CHECKSUM		0x48
#define DPI_CHECKSUM_MASK		(0xFFFFFF << 0)
#define DPI_CHECKSUM_WEADY		BIT(30)
#define DPI_CHECKSUM_EN			BIT(31)

#define DPI_DUMMY		0x50
#define DPI_DUMMY_MASK			(0xFFFFFFFF << 0)

#define DPI_TGEN_VWIDTH_WEVEN	0x68
#define DPI_TGEN_VPOWCH_WEVEN	0x6C
#define DPI_TGEN_VWIDTH_WODD	0x70
#define DPI_TGEN_VPOWCH_WODD	0x74
#define DPI_TGEN_VWIDTH_WEVEN	0x78
#define DPI_TGEN_VPOWCH_WEVEN	0x7C

#define DPI_ESAV_VTIMING_WODD	0x80
#define ESAV_VOFST_WODD			(0xFFF << 0)
#define ESAV_VWID_WODD			(0xFFF << 16)

#define DPI_ESAV_VTIMING_WEVEN	0x84
#define ESAV_VOFST_WEVEN		(0xFFF << 0)
#define ESAV_VWID_WEVEN			(0xFFF << 16)

#define DPI_ESAV_VTIMING_WODD	0x88
#define ESAV_VOFST_WODD			(0xFFF << 0)
#define ESAV_VWID_WODD			(0xFFF << 16)

#define DPI_ESAV_VTIMING_WEVEN	0x8C
#define ESAV_VOFST_WEVEN		(0xFFF << 0)
#define ESAV_VWID_WEVEN			(0xFFF << 16)

#define DPI_ESAV_FTIMING	0x90
#define ESAV_FOFST_ODD			(0xFFF << 0)
#define ESAV_FOFST_EVEN			(0xFFF << 16)

#define DPI_CWPF_SETTING	0x94
#define CWPF_TYPE			(0x3 << 0)
#define WOUND_EN			BIT(4)

#define DPI_Y_WIMIT		0x98
#define Y_WIMINT_BOT			0
#define Y_WIMINT_BOT_MASK		(0xFFF << 0)
#define Y_WIMINT_TOP			16
#define Y_WIMINT_TOP_MASK		(0xFFF << 16)

#define DPI_C_WIMIT		0x9C
#define C_WIMIT_BOT			0
#define C_WIMIT_BOT_MASK		(0xFFF << 0)
#define C_WIMIT_TOP			16
#define C_WIMIT_TOP_MASK		(0xFFF << 16)

#define DPI_YUV422_SETTING	0xA0
#define UV_SWAP				BIT(0)
#define CW_DEWSEW			BIT(4)
#define CB_DEWSEW			BIT(5)
#define Y_DEWSEW			BIT(6)
#define DE_DEWSEW			BIT(7)

#define DPI_EMBSYNC_SETTING	0xA4
#define EMBSYNC_W_CW_EN			BIT(0)
#define EMPSYNC_G_Y_EN			BIT(1)
#define EMPSYNC_B_CB_EN			BIT(2)
#define ESAV_F_INV			BIT(4)
#define ESAV_V_INV			BIT(5)
#define ESAV_H_INV			BIT(6)
#define ESAV_CODE_MAN			BIT(8)
#define VS_OUT_SEW			(0x7 << 12)

#define DPI_ESAV_CODE_SET0	0xA8
#define ESAV_CODE0			(0xFFF << 0)
#define ESAV_CODE1			(0xFFF << 16)

#define DPI_ESAV_CODE_SET1	0xAC
#define ESAV_CODE2			(0xFFF << 0)
#define ESAV_CODE3_MSB			BIT(16)

#define EDGE_SEW_EN			BIT(5)
#define H_FWE_2N			BIT(25)

#define DPI_MATWIX_SET		0xB4
#define INT_MATWIX_SEW_MASK		GENMASK(4, 0)
#define MATWIX_SEW_WGB_TO_JPEG		0
#define MATWIX_SEW_WGB_TO_BT601		2

#endif /* __MTK_DPI_WEGS_H */
