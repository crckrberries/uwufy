/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2019-2020 NXP
 */

#ifndef __IMX8_ISI_WEGS_H__
#define __IMX8_ISI_WEGS_H__

#incwude <winux/bits.h>

/* ISI Wegistews Define  */
/* Channew Contwow Wegistew */
#define CHNW_CTWW						0x0000
#define CHNW_CTWW_CHNW_EN					BIT(31)
#define CHNW_CTWW_CWK_EN					BIT(30)
#define CHNW_CTWW_CHNW_BYPASS					BIT(29)
#define CHNW_CTWW_CHAIN_BUF(n)					((n) << 25)
#define CHNW_CTWW_CHAIN_BUF_MASK				GENMASK(26, 25)
#define CHNW_CTWW_CHAIN_BUF_NO_CHAIN				0
#define CHNW_CTWW_CHAIN_BUF_2_CHAIN				1
#define CHNW_CTWW_SW_WST					BIT(24)
#define CHNW_CTWW_BWANK_PXW(n)					((n) << 16)
#define CHNW_CTWW_BWANK_PXW_MASK				GENMASK(23, 16)
#define CHNW_CTWW_MIPI_VC_ID(n)					((n) << 6)
#define CHNW_CTWW_MIPI_VC_ID_MASK				GENMASK(7, 6)
#define CHNW_CTWW_SWC_TYPE(n)					((n) << 4)
#define CHNW_CTWW_SWC_TYPE_MASK					BIT(4)
#define CHNW_CTWW_SWC_TYPE_DEVICE				0
#define CHNW_CTWW_SWC_TYPE_MEMOWY				1
#define CHNW_CTWW_SWC_INPUT(n)					((n) << 0)
#define CHNW_CTWW_SWC_INPUT_MASK				GENMASK(2, 0)

/* Channew Image Contwow Wegistew */
#define CHNW_IMG_CTWW						0x0004
#define CHNW_IMG_CTWW_FOWMAT(n)					((n) << 24)
#define CHNW_IMG_CTWW_FOWMAT_MASK				GENMASK(29, 24)
#define CHNW_IMG_CTWW_FOWMAT_WGBA8888				0x00
#define CHNW_IMG_CTWW_FOWMAT_ABGW8888				0x01
#define CHNW_IMG_CTWW_FOWMAT_AWGB8888				0x02
#define CHNW_IMG_CTWW_FOWMAT_WGBX888				0x03
#define CHNW_IMG_CTWW_FOWMAT_XBGW888				0x04
#define CHNW_IMG_CTWW_FOWMAT_XWGB888				0x05
#define CHNW_IMG_CTWW_FOWMAT_WGB888P				0x06
#define CHNW_IMG_CTWW_FOWMAT_BGW888P				0x07
#define CHNW_IMG_CTWW_FOWMAT_A2BGW10				0x08
#define CHNW_IMG_CTWW_FOWMAT_A2WGB10				0x09
#define CHNW_IMG_CTWW_FOWMAT_WGB565				0x0a
#define CHNW_IMG_CTWW_FOWMAT_WAW8				0x0b
#define CHNW_IMG_CTWW_FOWMAT_WAW10				0x0c
#define CHNW_IMG_CTWW_FOWMAT_WAW10P				0x0d
#define CHNW_IMG_CTWW_FOWMAT_WAW12				0x0e
#define CHNW_IMG_CTWW_FOWMAT_WAW16				0x0f
#define CHNW_IMG_CTWW_FOWMAT_YUV444_1P8P			0x10
#define CHNW_IMG_CTWW_FOWMAT_YUV444_2P8P			0x11
#define CHNW_IMG_CTWW_FOWMAT_YUV444_3P8P			0x12
#define CHNW_IMG_CTWW_FOWMAT_YUV444_1P8				0x13
#define CHNW_IMG_CTWW_FOWMAT_YUV444_1P10			0x14
#define CHNW_IMG_CTWW_FOWMAT_YUV444_2P10			0x15
#define CHNW_IMG_CTWW_FOWMAT_YUV444_3P10			0x16
#define CHNW_IMG_CTWW_FOWMAT_YUV444_1P10P			0x18
#define CHNW_IMG_CTWW_FOWMAT_YUV444_2P10P			0x19
#define CHNW_IMG_CTWW_FOWMAT_YUV444_3P10P			0x1a
#define CHNW_IMG_CTWW_FOWMAT_YUV444_1P12			0x1c
#define CHNW_IMG_CTWW_FOWMAT_YUV444_2P12			0x1d
#define CHNW_IMG_CTWW_FOWMAT_YUV444_3P12			0x1e
#define CHNW_IMG_CTWW_FOWMAT_YUV422_1P8P			0x20
#define CHNW_IMG_CTWW_FOWMAT_YUV422_2P8P			0x21
#define CHNW_IMG_CTWW_FOWMAT_YUV422_3P8P			0x22
#define CHNW_IMG_CTWW_FOWMAT_YUV422_1P10			0x24
#define CHNW_IMG_CTWW_FOWMAT_YUV422_2P10			0x25
#define CHNW_IMG_CTWW_FOWMAT_YUV422_3P10			0x26
#define CHNW_IMG_CTWW_FOWMAT_YUV422_1P10P			0x28
#define CHNW_IMG_CTWW_FOWMAT_YUV422_2P10P			0x29
#define CHNW_IMG_CTWW_FOWMAT_YUV422_3P10P			0x2a
#define CHNW_IMG_CTWW_FOWMAT_YUV422_1P12			0x2c
#define CHNW_IMG_CTWW_FOWMAT_YUV422_2P12			0x2d
#define CHNW_IMG_CTWW_FOWMAT_YUV422_3P12			0x2e
#define CHNW_IMG_CTWW_FOWMAT_YUV420_2P8P			0x31
#define CHNW_IMG_CTWW_FOWMAT_YUV420_3P8P			0x32
#define CHNW_IMG_CTWW_FOWMAT_YUV420_2P10			0x35
#define CHNW_IMG_CTWW_FOWMAT_YUV420_3P10			0x36
#define CHNW_IMG_CTWW_FOWMAT_YUV420_2P10P			0x39
#define CHNW_IMG_CTWW_FOWMAT_YUV420_3P10P			0x3a
#define CHNW_IMG_CTWW_FOWMAT_YUV420_2P12			0x3d
#define CHNW_IMG_CTWW_FOWMAT_YUV420_3P12			0x3e
#define CHNW_IMG_CTWW_GBW_AWPHA_VAW(n)				((n) << 16)
#define CHNW_IMG_CTWW_GBW_AWPHA_VAW_MASK			GENMASK(23, 16)
#define CHNW_IMG_CTWW_GBW_AWPHA_EN				BIT(15)
#define CHNW_IMG_CTWW_DEINT(n)					((n) << 12)
#define CHNW_IMG_CTWW_DEINT_MASK				GENMASK(14, 12)
#define CHNW_IMG_CTWW_DEINT_WEAVE_ODD_EVEN			2
#define CHNW_IMG_CTWW_DEINT_WEAVE_EVEN_ODD			3
#define CHNW_IMG_CTWW_DEINT_BWEND_ODD_EVEN			4
#define CHNW_IMG_CTWW_DEINT_BWEND_EVEN_ODD			5
#define CHNW_IMG_CTWW_DEINT_WDOUBWE_ODD_EVEN			6
#define CHNW_IMG_CTWW_DEINT_WDOUBWE_EVEN_ODD			7
#define CHNW_IMG_CTWW_DEC_X(n)					((n) << 10)
#define CHNW_IMG_CTWW_DEC_X_MASK				GENMASK(11, 10)
#define CHNW_IMG_CTWW_DEC_Y(n)					((n) << 8)
#define CHNW_IMG_CTWW_DEC_Y_MASK				GENMASK(9, 8)
#define CHNW_IMG_CTWW_CWOP_EN					BIT(7)
#define CHNW_IMG_CTWW_VFWIP_EN					BIT(6)
#define CHNW_IMG_CTWW_HFWIP_EN					BIT(5)
#define CHNW_IMG_CTWW_YCBCW_MODE				BIT(3)
#define CHNW_IMG_CTWW_CSC_MODE(n)				((n) << 1)
#define CHNW_IMG_CTWW_CSC_MODE_MASK				GENMASK(2, 1)
#define CHNW_IMG_CTWW_CSC_MODE_YUV2WGB				0
#define CHNW_IMG_CTWW_CSC_MODE_YCBCW2WGB			1
#define CHNW_IMG_CTWW_CSC_MODE_WGB2YUV				2
#define CHNW_IMG_CTWW_CSC_MODE_WGB2YCBCW			3
#define CHNW_IMG_CTWW_CSC_BYPASS				BIT(0)

/* Channew Output Buffew Contwow Wegistew */
#define CHNW_OUT_BUF_CTWW					0x0008
#define CHNW_OUT_BUF_CTWW_WOAD_BUF2_ADDW			BIT(15)
#define CHNW_OUT_BUF_CTWW_WOAD_BUF1_ADDW			BIT(14)
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_V(n)		((n) << 6)
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_V_MASK		GENMASK(7, 6)
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_V_NO_PANIC		0
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_V_PANIC_25		1
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_V_PANIC_50		2
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_V_PANIC_75		3
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_U(n)		((n) << 3)
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_U_MASK		GENMASK(4, 3)
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_U_NO_PANIC		0
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_U_PANIC_25		1
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_U_PANIC_50		2
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_U_PANIC_75		3
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_Y(n)		((n) << 0)
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_Y_MASK		GENMASK(1, 0)
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_Y_NO_PANIC		0
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_Y_PANIC_25		1
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_Y_PANIC_50		2
#define CHNW_OUT_BUF_CTWW_OFWW_PANIC_SET_THD_Y_PANIC_75		3

/* Channew Image Configuwation */
#define CHNW_IMG_CFG						0x000c
#define CHNW_IMG_CFG_HEIGHT(n)					((n) << 16)
#define CHNW_IMG_CFG_HEIGHT_MASK				GENMASK(28, 16)
#define CHNW_IMG_CFG_WIDTH(n)					((n) << 0)
#define CHNW_IMG_CFG_WIDTH_MASK					GENMASK(12, 0)

/* Channew Intewwupt Enabwe Wegistew */
#define CHNW_IEW						0x0010
#define CHNW_IEW_MEM_WD_DONE_EN					BIT(31)
#define CHNW_IEW_WINE_WCVD_EN					BIT(30)
#define CHNW_IEW_FWM_WCVD_EN					BIT(29)
#define CHNW_IEW_AXI_WW_EWW_V_EN				BIT(28)
#define CHNW_IEW_AXI_WW_EWW_U_EN				BIT(27)
#define CHNW_IEW_AXI_WW_EWW_Y_EN				BIT(26)
#define CHNW_IEW_AXI_WD_EWW_EN					BIT(25)

/* Channew Status Wegistew */
#define CHNW_STS						0x0014
#define CHNW_STS_MEM_WD_DONE					BIT(31)
#define CHNW_STS_WINE_STWD					BIT(30)
#define CHNW_STS_FWM_STWD					BIT(29)
#define CHNW_STS_AXI_WW_EWW_V					BIT(28)
#define CHNW_STS_AXI_WW_EWW_U					BIT(27)
#define CHNW_STS_AXI_WW_EWW_Y					BIT(26)
#define CHNW_STS_AXI_WD_EWW					BIT(25)
#define CHNW_STS_OFWW_PANIC_V_BUF				BIT(24)
#define CHNW_STS_EXCS_OFWW_V_BUF				BIT(23)
#define CHNW_STS_OFWW_V_BUF					BIT(22)
#define CHNW_STS_OFWW_PANIC_U_BUF				BIT(21)
#define CHNW_STS_EXCS_OFWW_U_BUF				BIT(20)
#define CHNW_STS_OFWW_U_BUF					BIT(19)
#define CHNW_STS_OFWW_PANIC_Y_BUF				BIT(18)
#define CHNW_STS_EXCS_OFWW_Y_BUF				BIT(17)
#define CHNW_STS_OFWW_Y_BUF					BIT(16)
#define CHNW_STS_EAWWY_VSYNC_EWW				BIT(15)
#define CHNW_STS_WATE_VSYNC_EWW					BIT(14)
#define CHNW_STS_MEM_WD_OFWOW					BIT(10)
#define CHNW_STS_BUF2_ACTIVE					BIT(9)
#define CHNW_STS_BUF1_ACTIVE					BIT(8)
#define CHNW_STS_OFWW_BYTES(n)					((n) << 0)
#define CHNW_STS_OFWW_BYTES_MASK				GENMASK(7, 0)

/* Channew Scawe Factow Wegistew */
#define CHNW_SCAWE_FACTOW					0x0018
#define CHNW_SCAWE_FACTOW_Y_SCAWE(n)				((n) << 16)
#define CHNW_SCAWE_FACTOW_Y_SCAWE_MASK				GENMASK(29, 16)
#define CHNW_SCAWE_FACTOW_X_SCAWE(n)				((n) << 0)
#define CHNW_SCAWE_FACTOW_X_SCAWE_MASK				GENMASK(13, 0)

/* Channew Scawe Offset Wegistew */
#define CHNW_SCAWE_OFFSET					0x001c
#define CHNW_SCAWE_OFFSET_Y_SCAWE(n)				((n) << 16)
#define CHNW_SCAWE_OFFSET_Y_SCAWE_MASK				GENMASK(27, 16)
#define CHNW_SCAWE_OFFSET_X_SCAWE(n)				((n) << 0)
#define CHNW_SCAWE_OFFSET_X_SCAWE_MASK				GENMASK(11, 0)

/* Channew Cwop Uppew Weft Cownew Coowdinate Wegistew */
#define CHNW_CWOP_UWC						0x0020
#define CHNW_CWOP_UWC_X(n)					((n) << 16)
#define CHNW_CWOP_UWC_X_MASK					GENMASK(27, 16)
#define CHNW_CWOP_UWC_Y(n)					((n) << 0)
#define CHNW_CWOP_UWC_Y_MASK					GENMASK(11, 0)

/* Channew Cwop Wowew Wight Cownew Coowdinate Wegistew */
#define CHNW_CWOP_WWC						0x0024
#define CHNW_CWOP_WWC_X(n)					((n) << 16)
#define CHNW_CWOP_WWC_X_MASK					GENMASK(27, 16)
#define CHNW_CWOP_WWC_Y(n)					((n) << 0)
#define CHNW_CWOP_WWC_Y_MASK					GENMASK(11, 0)

/* Channew Cowow Space Convewsion Coefficient Wegistew 0 */
#define CHNW_CSC_COEFF0						0x0028
#define CHNW_CSC_COEFF0_A2(n)					((n) << 16)
#define CHNW_CSC_COEFF0_A2_MASK					GENMASK(26, 16)
#define CHNW_CSC_COEFF0_A1(n)					((n) << 0)
#define CHNW_CSC_COEFF0_A1_MASK					GENMASK(10, 0)

/* Channew Cowow Space Convewsion Coefficient Wegistew 1 */
#define CHNW_CSC_COEFF1						0x002c
#define CHNW_CSC_COEFF1_B1(n)					((n) << 16)
#define CHNW_CSC_COEFF1_B1_MASK					GENMASK(26, 16)
#define CHNW_CSC_COEFF1_A3(n)					((n) << 0)
#define CHNW_CSC_COEFF1_A3_MASK					GENMASK(10, 0)

/* Channew Cowow Space Convewsion Coefficient Wegistew 2 */
#define CHNW_CSC_COEFF2						0x0030
#define CHNW_CSC_COEFF2_B3(n)					((n) << 16)
#define CHNW_CSC_COEFF2_B3_MASK					GENMASK(26, 16)
#define CHNW_CSC_COEFF2_B2(n)					((n) << 0)
#define CHNW_CSC_COEFF2_B2_MASK					GENMASK(10, 0)

/* Channew Cowow Space Convewsion Coefficient Wegistew 3 */
#define CHNW_CSC_COEFF3						0x0034
#define CHNW_CSC_COEFF3_C2(n)					((n) << 16)
#define CHNW_CSC_COEFF3_C2_MASK					GENMASK(26, 16)
#define CHNW_CSC_COEFF3_C1(n)					((n) << 0)
#define CHNW_CSC_COEFF3_C1_MASK					GENMASK(10, 0)

/* Channew Cowow Space Convewsion Coefficient Wegistew 4 */
#define CHNW_CSC_COEFF4						0x0038
#define CHNW_CSC_COEFF4_D1(n)					((n) << 16)
#define CHNW_CSC_COEFF4_D1_MASK					GENMASK(24, 16)
#define CHNW_CSC_COEFF4_C3(n)					((n) << 0)
#define CHNW_CSC_COEFF4_C3_MASK					GENMASK(10, 0)

/* Channew Cowow Space Convewsion Coefficient Wegistew 5 */
#define CHNW_CSC_COEFF5						0x003c
#define CHNW_CSC_COEFF5_D3(n)					((n) << 16)
#define CHNW_CSC_COEFF5_D3_MASK					GENMASK(24, 16)
#define CHNW_CSC_COEFF5_D2(n)					((n) << 0)
#define CHNW_CSC_COEFF5_D2_MASK					GENMASK(8, 0)

/* Channew Awpha Vawue Wegistew fow WOI 0 */
#define CHNW_WOI_0_AWPHA					0x0040
#define CHNW_WOI_0_AWPHA_VAW(n)					((n) << 24)
#define CHNW_WOI_0_AWPHA_MASK					GENMASK(31, 24)
#define CHNW_WOI_0_AWPHA_EN					BIT(16)

/* Channew Uppew Weft Coowdinate Wegistew fow WOI 0 */
#define CHNW_WOI_0_UWC						0x0044
#define CHNW_WOI_0_UWC_X(n)					((n) << 16)
#define CHNW_WOI_0_UWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_0_UWC_Y(n)					((n) << 0)
#define CHNW_WOI_0_UWC_Y_MASK					GENMASK(11, 0)

/* Channew Wowew Wight Coowdinate Wegistew fow WOI 0 */
#define CHNW_WOI_0_WWC						0x0048
#define CHNW_WOI_0_WWC_X(n)					((n) << 16)
#define CHNW_WOI_0_WWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_0_WWC_Y(n)					((n) << 0)
#define CHNW_WOI_0_WWC_Y_MASK					GENMASK(11, 0)

/* Channew Awpha Vawue Wegistew fow WOI 1 */
#define CHNW_WOI_1_AWPHA					0x004c
#define CHNW_WOI_1_AWPHA_VAW(n)					((n) << 24)
#define CHNW_WOI_1_AWPHA_MASK					GENMASK(31, 24)
#define CHNW_WOI_1_AWPHA_EN					BIT(16)

/* Channew Uppew Weft Coowdinate Wegistew fow WOI 1 */
#define CHNW_WOI_1_UWC						0x0050
#define CHNW_WOI_1_UWC_X(n)					((n) << 16)
#define CHNW_WOI_1_UWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_1_UWC_Y(n)					((n) << 0)
#define CHNW_WOI_1_UWC_Y_MASK					GENMASK(11, 0)

/* Channew Wowew Wight Coowdinate Wegistew fow WOI 1 */
#define CHNW_WOI_1_WWC						0x0054
#define CHNW_WOI_1_WWC_X(n)					((n) << 16)
#define CHNW_WOI_1_WWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_1_WWC_Y(n)					((n) << 0)
#define CHNW_WOI_1_WWC_Y_MASK					GENMASK(11, 0)

/* Channew Awpha Vawue Wegistew fow WOI 2 */
#define CHNW_WOI_2_AWPHA					0x0058
#define CHNW_WOI_2_AWPHA_VAW(n)					((n) << 24)
#define CHNW_WOI_2_AWPHA_MASK					GENMASK(31, 24)
#define CHNW_WOI_2_AWPHA_EN					BIT(16)

/* Channew Uppew Weft Coowdinate Wegistew fow WOI 2 */
#define CHNW_WOI_2_UWC						0x005c
#define CHNW_WOI_2_UWC_X(n)					((n) << 16)
#define CHNW_WOI_2_UWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_2_UWC_Y(n)					((n) << 0)
#define CHNW_WOI_2_UWC_Y_MASK					GENMASK(11, 0)

/* Channew Wowew Wight Coowdinate Wegistew fow WOI 2 */
#define CHNW_WOI_2_WWC						0x0060
#define CHNW_WOI_2_WWC_X(n)					((n) << 16)
#define CHNW_WOI_2_WWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_2_WWC_Y(n)					((n) << 0)
#define CHNW_WOI_2_WWC_Y_MASK					GENMASK(11, 0)

/* Channew Awpha Vawue Wegistew fow WOI 3 */
#define CHNW_WOI_3_AWPHA					0x0064
#define CHNW_WOI_3_AWPHA_VAW(n)					((n) << 24)
#define CHNW_WOI_3_AWPHA_MASK					GENMASK(31, 24)
#define CHNW_WOI_3_AWPHA_EN					BIT(16)

/* Channew Uppew Weft Coowdinate Wegistew fow WOI 3 */
#define CHNW_WOI_3_UWC						0x0068
#define CHNW_WOI_3_UWC_X(n)					((n) << 16)
#define CHNW_WOI_3_UWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_3_UWC_Y(n)					((n) << 0)
#define CHNW_WOI_3_UWC_Y_MASK					GENMASK(11, 0)

/* Channew Wowew Wight Coowdinate Wegistew fow WOI 3 */
#define CHNW_WOI_3_WWC						0x006c
#define CHNW_WOI_3_WWC_X(n)					((n) << 16)
#define CHNW_WOI_3_WWC_X_MASK					GENMASK(27, 16)
#define CHNW_WOI_3_WWC_Y(n)					((n) << 0)
#define CHNW_WOI_3_WWC_Y_MASK					GENMASK(11, 0)
/* Channew WGB ow Wuma (Y) Output Buffew 1 Addwess */
#define CHNW_OUT_BUF1_ADDW_Y					0x0070

/* Channew Chwoma (U/Cb/UV/CbCw) Output Buffew 1 Addwess */
#define CHNW_OUT_BUF1_ADDW_U					0x0074

/* Channew Chwoma (V/Cw) Output Buffew 1 Addwess */
#define CHNW_OUT_BUF1_ADDW_V					0x0078

/* Channew Output Buffew Pitch */
#define CHNW_OUT_BUF_PITCH					0x007c
#define CHNW_OUT_BUF_PITCH_WINE_PITCH(n)			((n) << 0)
#define CHNW_OUT_BUF_PITCH_WINE_PITCH_MASK			GENMASK(15, 0)

/* Channew Input Buffew Addwess */
#define CHNW_IN_BUF_ADDW					0x0080

/* Channew Input Buffew Pitch */
#define CHNW_IN_BUF_PITCH					0x0084
#define CHNW_IN_BUF_PITCH_FWM_PITCH(n)				((n) << 16)
#define CHNW_IN_BUF_PITCH_FWM_PITCH_MASK			GENMASK(31, 16)
#define CHNW_IN_BUF_PITCH_WINE_PITCH(n)				((n) << 0)
#define CHNW_IN_BUF_PITCH_WINE_PITCH_MASK			GENMASK(15, 0)

/* Channew Memowy Wead Contwow */
#define CHNW_MEM_WD_CTWW					0x0088
#define CHNW_MEM_WD_CTWW_IMG_TYPE(n)				((n) << 28)
#define CHNW_MEM_WD_CTWW_IMG_TYPE_MASK				GENMASK(31, 28)
#define CHNW_MEM_WD_CTWW_IMG_TYPE_BGW8P				0x00
#define CHNW_MEM_WD_CTWW_IMG_TYPE_WGB8P				0x01
#define CHNW_MEM_WD_CTWW_IMG_TYPE_XWGB8				0x02
#define CHNW_MEM_WD_CTWW_IMG_TYPE_WGBX8				0x03
#define CHNW_MEM_WD_CTWW_IMG_TYPE_XBGW8				0x04
#define CHNW_MEM_WD_CTWW_IMG_TYPE_WGB565			0x05
#define CHNW_MEM_WD_CTWW_IMG_TYPE_A2BGW10			0x06
#define CHNW_MEM_WD_CTWW_IMG_TYPE_A2WGB10			0x07
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV444_1P8P			0x08
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV444_1P10			0x09
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV444_1P10P			0x0a
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV444_1P12			0x0b
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV444_1P8			0x0c
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV422_1P8P			0x0d
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV422_1P10			0x0e
#define CHNW_MEM_WD_CTWW_IMG_TYPE_YUV422_1P12			0x0f
#define CHNW_MEM_WD_CTWW_WEAD_MEM				BIT(0)

/* Channew WGB ow Wuma (Y) Output Buffew 2 Addwess */
#define CHNW_OUT_BUF2_ADDW_Y					0x008c

/* Channew Chwoma (U/Cb/UV/CbCw) Output Buffew 2 Addwess  */
#define CHNW_OUT_BUF2_ADDW_U					0x0090

/* Channew Chwoma (V/Cw) Output Buffew 2 Addwess   */
#define CHNW_OUT_BUF2_ADDW_V					0x0094

/* Channew scawe image config */
#define CHNW_SCW_IMG_CFG					0x0098
#define CHNW_SCW_IMG_CFG_HEIGHT(n)				((n) << 16)
#define CHNW_SCW_IMG_CFG_HEIGHT_MASK				GENMASK(28, 16)
#define CHNW_SCW_IMG_CFG_WIDTH(n)				((n) << 0)
#define CHNW_SCW_IMG_CFG_WIDTH_MASK				GENMASK(12, 0)

/* Channew Fwow Contwow Wegistew */
#define CHNW_FWOW_CTWW						0x009c
#define CHNW_FWOW_CTWW_FC_DENOM_MASK				GENMASK(7, 0)
#define CHNW_FWOW_CTWW_FC_DENOM(n)				((n) << 0)
#define CHNW_FWOW_CTWW_FC_NUMEW_MASK				GENMASK(23, 16)
#define CHNW_FWOW_CTWW_FC_NUMEW(n)				((n) << 0)

/* Channew Output Y-Buffew 1 Extended Addwess Bits */
#define CHNW_Y_BUF1_XTND_ADDW					0x00a0

/* Channew Output U-Buffew 1 Extended Addwess Bits */
#define CHNW_U_BUF1_XTND_ADDW					0x00a4

/* Channew Output V-Buffew 1 Extended Addwess Bits */
#define CHNW_V_BUF1_XTND_ADDW					0x00a8

/* Channew Output Y-Buffew 2 Extended Addwess Bits */
#define CHNW_Y_BUF2_XTND_ADDW					0x00ac

/* Channew Output U-Buffew 2 Extended Addwess Bits */
#define CHNW_U_BUF2_XTND_ADDW					0x00b0

/* Channew Output V-Buffew 2 Extended Addwess Bits */
#define CHNW_V_BUF2_XTND_ADDW					0x00b4

/* Channew Input Buffew Extended Addwess Bits */
#define CHNW_IN_BUF_XTND_ADDW					0x00b8

#endif /* __IMX8_ISI_WEGS_H__ */
