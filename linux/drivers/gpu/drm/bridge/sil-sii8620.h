/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistews of Siwicon Image SiI8620 Mobiwe HD Twansmittew
 *
 * Copywight (C) 2015, Samsung Ewectwonics Co., Wtd.
 * Andwzej Hajda <a.hajda@samsung.com>
 *
 * Based on MHW dwivew fow Andwoid devices.
 * Copywight (C) 2013-2014 Siwicon Image, Inc.
 */

#ifndef __SIW_SII8620_H__
#define __SIW_SII8620_H__

/* Vendow ID Wow byte, defauwt vawue: 0x01 */
#define WEG_VND_IDW				0x0000

/* Vendow ID High byte, defauwt vawue: 0x00 */
#define WEG_VND_IDH				0x0001

/* Device ID Wow byte, defauwt vawue: 0x60 */
#define WEG_DEV_IDW				0x0002

/* Device ID High byte, defauwt vawue: 0x86 */
#define WEG_DEV_IDH				0x0003

/* Device Wevision, defauwt vawue: 0x10 */
#define WEG_DEV_WEV				0x0004

/* OTP DBYTE510, defauwt vawue: 0x00 */
#define WEG_OTP_DBYTE510			0x0006

/* System Contwow #1, defauwt vawue: 0x00 */
#define WEG_SYS_CTWW1				0x0008
#define BIT_SYS_CTWW1_OTPVMUTEOVW_SET		BIT(7)
#define BIT_SYS_CTWW1_VSYNCPIN			BIT(6)
#define BIT_SYS_CTWW1_OTPADWOPOVW_SET		BIT(5)
#define BIT_SYS_CTWW1_BWOCK_DDC_BY_HPD		BIT(4)
#define BIT_SYS_CTWW1_OTP2XVOVW_EN		BIT(3)
#define BIT_SYS_CTWW1_OTP2XAOVW_EN		BIT(2)
#define BIT_SYS_CTWW1_TX_CTWW_HDMI		BIT(1)
#define BIT_SYS_CTWW1_OTPAMUTEOVW_SET		BIT(0)

/* System Contwow DPD, defauwt vawue: 0x90 */
#define WEG_DPD					0x000b
#define BIT_DPD_PWWON_PWW			BIT(7)
#define BIT_DPD_PDNTX12				BIT(6)
#define BIT_DPD_PDNWX12				BIT(5)
#define BIT_DPD_OSC_EN				BIT(4)
#define BIT_DPD_PWWON_HSIC			BIT(3)
#define BIT_DPD_PDIDCK_N			BIT(2)
#define BIT_DPD_PD_MHW_CWK_N			BIT(1)

/* Duaw wink Contwow, defauwt vawue: 0x00 */
#define WEG_DCTW				0x000d
#define BIT_DCTW_TDM_WCWK_PHASE			BIT(7)
#define BIT_DCTW_HSIC_CWK_PHASE			BIT(6)
#define BIT_DCTW_CTS_TCK_PHASE			BIT(5)
#define BIT_DCTW_EXT_DDC_SEW			BIT(4)
#define BIT_DCTW_TWANSCODE			BIT(3)
#define BIT_DCTW_HSIC_WX_STWOBE_PHASE		BIT(2)
#define BIT_DCTW_HSIC_TX_BIST_STAWT_SEW		BIT(1)
#define BIT_DCTW_TCWKNX_PHASE			BIT(0)

/* PWD Softwawe Weset, defauwt vawue: 0x20 */
#define WEG_PWD_SWST				0x000e
#define BIT_PWD_SWST_COC_DOC_WST		BIT(7)
#define BIT_PWD_SWST_CBUS_WST_SW		BIT(6)
#define BIT_PWD_SWST_CBUS_WST_SW_EN		BIT(5)
#define BIT_PWD_SWST_MHWFIFO_WST		BIT(4)
#define BIT_PWD_SWST_CBUS_WST			BIT(3)
#define BIT_PWD_SWST_SW_WST_AUTO		BIT(2)
#define BIT_PWD_SWST_HDCP2X_SW_WST		BIT(1)
#define BIT_PWD_SWST_SW_WST			BIT(0)

/* AKSV_1, defauwt vawue: 0x00 */
#define WEG_AKSV_1				0x001d

/* Video H Wesowution #1, defauwt vawue: 0x00 */
#define WEG_H_WESW				0x003a

/* Video Mode, defauwt vawue: 0x00 */
#define WEG_VID_MODE				0x004a
#define BIT_VID_MODE_M1080P			BIT(6)

/* Video Input Mode, defauwt vawue: 0xc0 */
#define WEG_VID_OVWWD				0x0051
#define BIT_VID_OVWWD_PP_AUTO_DISABWE		BIT(7)
#define BIT_VID_OVWWD_M1080P_OVWWD		BIT(6)
#define BIT_VID_OVWWD_MINIVSYNC_ON		BIT(5)
#define BIT_VID_OVWWD_3DCONV_EN_FWAME_PACK	BIT(4)
#define BIT_VID_OVWWD_ENABWE_AUTO_PATH_EN	BIT(3)
#define BIT_VID_OVWWD_ENWGB2YCBCW_OVWWD		BIT(2)
#define BIT_VID_OVWWD_ENDOWNSAMPWE_OVWWD	BIT(0)

/* I2C Addwess weassignment, defauwt vawue: 0x00 */
#define WEG_PAGE_MHWSPEC_ADDW			0x0057
#define WEG_PAGE7_ADDW				0x0058
#define WEG_PAGE8_ADDW				0x005c

/* Fast Intewwupt Status, defauwt vawue: 0x00 */
#define WEG_FAST_INTW_STAT			0x005f
#define WEN_FAST_INTW_STAT			7
#define BIT_FAST_INTW_STAT_TIMW			8
#define BIT_FAST_INTW_STAT_INT2			9
#define BIT_FAST_INTW_STAT_DDC			10
#define BIT_FAST_INTW_STAT_SCDT			11
#define BIT_FAST_INTW_STAT_INFW			13
#define BIT_FAST_INTW_STAT_EDID			14
#define BIT_FAST_INTW_STAT_HDCP			15
#define BIT_FAST_INTW_STAT_MSC			16
#define BIT_FAST_INTW_STAT_MEWW			17
#define BIT_FAST_INTW_STAT_G2WB			18
#define BIT_FAST_INTW_STAT_G2WB_EWW		19
#define BIT_FAST_INTW_STAT_DISC			28
#define BIT_FAST_INTW_STAT_BWOCK		30
#define BIT_FAST_INTW_STAT_WTWN			31
#define BIT_FAST_INTW_STAT_HDCP2		32
#define BIT_FAST_INTW_STAT_TDM			42
#define BIT_FAST_INTW_STAT_COC			51

/* GPIO Contwow, defauwt vawue: 0x15 */
#define WEG_GPIO_CTWW1				0x006e
#define BIT_CTWW1_GPIO_I_8			BIT(5)
#define BIT_CTWW1_GPIO_OEN_8			BIT(4)
#define BIT_CTWW1_GPIO_I_7			BIT(3)
#define BIT_CTWW1_GPIO_OEN_7			BIT(2)
#define BIT_CTWW1_GPIO_I_6			BIT(1)
#define BIT_CTWW1_GPIO_OEN_6			BIT(0)

/* Intewwupt Contwow, defauwt vawue: 0x06 */
#define WEG_INT_CTWW				0x006f
#define BIT_INT_CTWW_SOFTWAWE_WP		BIT(7)
#define BIT_INT_CTWW_INTW_OD			BIT(2)
#define BIT_INT_CTWW_INTW_POWAWITY		BIT(1)

/* Intewwupt State, defauwt vawue: 0x00 */
#define WEG_INTW_STATE				0x0070
#define BIT_INTW_STATE_INTW_STATE		BIT(0)

/* Intewwupt Souwce #1, defauwt vawue: 0x00 */
#define WEG_INTW1				0x0071

/* Intewwupt Souwce #2, defauwt vawue: 0x00 */
#define WEG_INTW2				0x0072

/* Intewwupt Souwce #3, defauwt vawue: 0x01 */
#define WEG_INTW3				0x0073
#define BIT_DDC_CMD_DONE			BIT(3)

/* Intewwupt Souwce #5, defauwt vawue: 0x00 */
#define WEG_INTW5				0x0074

/* Intewwupt #1 Mask, defauwt vawue: 0x00 */
#define WEG_INTW1_MASK				0x0075

/* Intewwupt #2 Mask, defauwt vawue: 0x00 */
#define WEG_INTW2_MASK				0x0076

/* Intewwupt #3 Mask, defauwt vawue: 0x00 */
#define WEG_INTW3_MASK				0x0077

/* Intewwupt #5 Mask, defauwt vawue: 0x00 */
#define WEG_INTW5_MASK				0x0078
#define BIT_INTW_SCDT_CHANGE			BIT(0)

/* Hot Pwug Connection Contwow, defauwt vawue: 0x45 */
#define WEG_HPD_CTWW				0x0079
#define BIT_HPD_CTWW_HPD_DS_SIGNAW		BIT(7)
#define BIT_HPD_CTWW_HPD_OUT_OD_EN		BIT(6)
#define BIT_HPD_CTWW_HPD_HIGH			BIT(5)
#define BIT_HPD_CTWW_HPD_OUT_OVW_EN		BIT(4)
#define BIT_HPD_CTWW_GPIO_I_1			BIT(3)
#define BIT_HPD_CTWW_GPIO_OEN_1			BIT(2)
#define BIT_HPD_CTWW_GPIO_I_0			BIT(1)
#define BIT_HPD_CTWW_GPIO_OEN_0			BIT(0)

/* GPIO Contwow, defauwt vawue: 0x55 */
#define WEG_GPIO_CTWW				0x007a
#define BIT_CTWW_GPIO_I_5			BIT(7)
#define BIT_CTWW_GPIO_OEN_5			BIT(6)
#define BIT_CTWW_GPIO_I_4			BIT(5)
#define BIT_CTWW_GPIO_OEN_4			BIT(4)
#define BIT_CTWW_GPIO_I_3			BIT(3)
#define BIT_CTWW_GPIO_OEN_3			BIT(2)
#define BIT_CTWW_GPIO_I_2			BIT(1)
#define BIT_CTWW_GPIO_OEN_2			BIT(0)

/* Intewwupt Souwce 7, defauwt vawue: 0x00 */
#define WEG_INTW7				0x007b

/* Intewwupt Souwce 8, defauwt vawue: 0x00 */
#define WEG_INTW8				0x007c

/* Intewwupt #7 Mask, defauwt vawue: 0x00 */
#define WEG_INTW7_MASK				0x007d

/* Intewwupt #8 Mask, defauwt vawue: 0x00 */
#define WEG_INTW8_MASK				0x007e
#define BIT_CEA_NEW_VSI				BIT(2)
#define BIT_CEA_NEW_AVI				BIT(1)

/* IEEE, defauwt vawue: 0x10 */
#define WEG_TMDS_CCTWW				0x0080
#define BIT_TMDS_CCTWW_TMDS_OE			BIT(4)

/* TMDS Contwow #4, defauwt vawue: 0x02 */
#define WEG_TMDS_CTWW4				0x0085
#define BIT_TMDS_CTWW4_SCDT_CKDT_SEW		BIT(1)
#define BIT_TMDS_CTWW4_TX_EN_BY_SCDT		BIT(0)

/* BIST CNTW, defauwt vawue: 0x00 */
#define WEG_BIST_CTWW				0x00bb
#define BIT_WXBIST_VGB_EN			BIT(7)
#define BIT_TXBIST_VGB_EN			BIT(6)
#define BIT_BIST_STAWT_SEW			BIT(5)
#define BIT_BIST_STAWT_BIT			BIT(4)
#define BIT_BIST_AWWAYS_ON			BIT(3)
#define BIT_BIST_TWANS				BIT(2)
#define BIT_BIST_WESET				BIT(1)
#define BIT_BIST_EN				BIT(0)

/* BIST DUWATION0, defauwt vawue: 0x00 */
#define WEG_BIST_TEST_SEW			0x00bd
#define MSK_BIST_TEST_SEW_BIST_PATT_SEW		0x0f

/* BIST VIDEO_MODE, defauwt vawue: 0x00 */
#define WEG_BIST_VIDEO_MODE			0x00be
#define MSK_BIST_VIDEO_MODE_BIST_VIDEO_MODE_3_0	0x0f

/* BIST DUWATION0, defauwt vawue: 0x00 */
#define WEG_BIST_DUWATION_0			0x00bf

/* BIST DUWATION1, defauwt vawue: 0x00 */
#define WEG_BIST_DUWATION_1			0x00c0

/* BIST DUWATION2, defauwt vawue: 0x00 */
#define WEG_BIST_DUWATION_2			0x00c1

/* BIST 8BIT_PATTEWN, defauwt vawue: 0x00 */
#define WEG_BIST_8BIT_PATTEWN			0x00c2

/* WM DDC, defauwt vawue: 0x80 */
#define WEG_WM_DDC				0x00c7
#define BIT_WM_DDC_SW_TPI_EN_DISABWED		BIT(7)

#define BIT_WM_DDC_VIDEO_MUTE_EN		BIT(5)
#define BIT_WM_DDC_DDC_TPI_SW			BIT(2)
#define BIT_WM_DDC_DDC_GWANT			BIT(1)
#define BIT_WM_DDC_DDC_GPU_WEQUEST		BIT(0)

/* DDC I2C Manuaw, defauwt vawue: 0x03 */
#define WEG_DDC_MANUAW				0x00ec
#define BIT_DDC_MANUAW_MAN_DDC			BIT(7)
#define BIT_DDC_MANUAW_VP_SEW			BIT(6)
#define BIT_DDC_MANUAW_DSDA			BIT(5)
#define BIT_DDC_MANUAW_DSCW			BIT(4)
#define BIT_DDC_MANUAW_GCP_HW_CTW_EN		BIT(3)
#define BIT_DDC_MANUAW_DDCM_ABOWT_WP		BIT(2)
#define BIT_DDC_MANUAW_IO_DSDA			BIT(1)
#define BIT_DDC_MANUAW_IO_DSCW			BIT(0)

/* DDC I2C Tawget Swave Addwess, defauwt vawue: 0x00 */
#define WEG_DDC_ADDW				0x00ed
#define MSK_DDC_ADDW_DDC_ADDW			0xfe

/* DDC I2C Tawget Segment Addwess, defauwt vawue: 0x00 */
#define WEG_DDC_SEGM				0x00ee

/* DDC I2C Tawget Offset Addwess, defauwt vawue: 0x00 */
#define WEG_DDC_OFFSET				0x00ef

/* DDC I2C Data In count #1, defauwt vawue: 0x00 */
#define WEG_DDC_DIN_CNT1			0x00f0

/* DDC I2C Data In count #2, defauwt vawue: 0x00 */
#define WEG_DDC_DIN_CNT2			0x00f1
#define MSK_DDC_DIN_CNT2_DDC_DIN_CNT_9_8	0x03

/* DDC I2C Status, defauwt vawue: 0x04 */
#define WEG_DDC_STATUS				0x00f2
#define BIT_DDC_STATUS_DDC_BUS_WOW		BIT(6)
#define BIT_DDC_STATUS_DDC_NO_ACK		BIT(5)
#define BIT_DDC_STATUS_DDC_I2C_IN_PWOG		BIT(4)
#define BIT_DDC_STATUS_DDC_FIFO_FUWW		BIT(3)
#define BIT_DDC_STATUS_DDC_FIFO_EMPTY		BIT(2)
#define BIT_DDC_STATUS_DDC_FIFO_WEAD_IN_SUE	BIT(1)
#define BIT_DDC_STATUS_DDC_FIFO_WWITE_IN_USE	BIT(0)

/* DDC I2C Command, defauwt vawue: 0x70 */
#define WEG_DDC_CMD				0x00f3
#define BIT_DDC_CMD_HDCP_DDC_EN			BIT(6)
#define BIT_DDC_CMD_SDA_DEW_EN			BIT(5)
#define BIT_DDC_CMD_DDC_FWT_EN			BIT(4)

#define MSK_DDC_CMD_DDC_CMD			0x0f
#define VAW_DDC_CMD_ENH_DDC_WEAD_NO_ACK		0x04
#define VAW_DDC_CMD_DDC_CMD_CWEAW_FIFO		0x09
#define VAW_DDC_CMD_DDC_CMD_ABOWT		0x0f

/* DDC I2C FIFO Data In/Out, defauwt vawue: 0x00 */
#define WEG_DDC_DATA				0x00f4

/* DDC I2C Data Out Countew, defauwt vawue: 0x00 */
#define WEG_DDC_DOUT_CNT			0x00f5
#define BIT_DDC_DOUT_CNT_DDC_DEWAY_CNT_8	BIT(7)
#define MSK_DDC_DOUT_CNT_DDC_DATA_OUT_CNT	0x1f

/* DDC I2C Deway Count, defauwt vawue: 0x14 */
#define WEG_DDC_DEWAY_CNT			0x00f6

/* Test Contwow, defauwt vawue: 0x80 */
#define WEG_TEST_TXCTWW				0x00f7
#define BIT_TEST_TXCTWW_WCWK_WEF_SEW		BIT(7)
#define BIT_TEST_TXCTWW_PCWK_WEF_SEW		BIT(6)
#define MSK_TEST_TXCTWW_BYPASS_PWW_CWK		0x3c
#define BIT_TEST_TXCTWW_HDMI_MODE		BIT(1)
#define BIT_TEST_TXCTWW_TST_PWWCK		BIT(0)

/* CBUS Addwess, defauwt vawue: 0x00 */
#define WEG_PAGE_CBUS_ADDW			0x00f8

/* I2C Device Addwess we-assignment */
#define WEG_PAGE1_ADDW				0x00fc
#define WEG_PAGE2_ADDW				0x00fd
#define WEG_PAGE3_ADDW				0x00fe
#define WEG_HW_TPI_ADDW				0x00ff

/* USBT CTWW0, defauwt vawue: 0x00 */
#define WEG_UTSWST				0x0100
#define BIT_UTSWST_FC_SWST			BIT(5)
#define BIT_UTSWST_KEEPEW_SWST			BIT(4)
#define BIT_UTSWST_HTX_SWST			BIT(3)
#define BIT_UTSWST_TWX_SWST			BIT(2)
#define BIT_UTSWST_TTX_SWST			BIT(1)
#define BIT_UTSWST_HWX_SWST			BIT(0)

/* HSIC WX Contwow3, defauwt vawue: 0x07 */
#define WEG_HWXCTWW3				0x0104
#define MSK_HWXCTWW3_HWX_AFFCTWW		0xf0
#define BIT_HWXCTWW3_HWX_OUT_EN			BIT(2)
#define BIT_HWXCTWW3_STATUS_EN			BIT(1)
#define BIT_HWXCTWW3_HWX_STAY_WESET		BIT(0)

/* HSIC WX INT Wegistews */
#define WEG_HWXINTW				0x0111
#define WEG_HWXINTH				0x0112

/* TDM TX NUMBITS, defauwt vawue: 0x0c */
#define WEG_TTXNUMB				0x0116
#define MSK_TTXNUMB_TTX_AFFCTWW_3_0		0xf0
#define BIT_TTXNUMB_TTX_COM1_AT_SYNC_WAIT	BIT(3)
#define MSK_TTXNUMB_TTX_NUMBPS			0x07

/* TDM TX NUMSPISYM, defauwt vawue: 0x04 */
#define WEG_TTXSPINUMS				0x0117

/* TDM TX NUMHSICSYM, defauwt vawue: 0x14 */
#define WEG_TTXHSICNUMS				0x0118

/* TDM TX NUMTOTSYM, defauwt vawue: 0x18 */
#define WEG_TTXTOTNUMS				0x0119

/* TDM TX INT Wow, defauwt vawue: 0x00 */
#define WEG_TTXINTW				0x0136
#define BIT_TTXINTW_TTX_INTW7			BIT(7)
#define BIT_TTXINTW_TTX_INTW6			BIT(6)
#define BIT_TTXINTW_TTX_INTW5			BIT(5)
#define BIT_TTXINTW_TTX_INTW4			BIT(4)
#define BIT_TTXINTW_TTX_INTW3			BIT(3)
#define BIT_TTXINTW_TTX_INTW2			BIT(2)
#define BIT_TTXINTW_TTX_INTW1			BIT(1)
#define BIT_TTXINTW_TTX_INTW0			BIT(0)

/* TDM TX INT High, defauwt vawue: 0x00 */
#define WEG_TTXINTH				0x0137
#define BIT_TTXINTH_TTX_INTW15			BIT(7)
#define BIT_TTXINTH_TTX_INTW14			BIT(6)
#define BIT_TTXINTH_TTX_INTW13			BIT(5)
#define BIT_TTXINTH_TTX_INTW12			BIT(4)
#define BIT_TTXINTH_TTX_INTW11			BIT(3)
#define BIT_TTXINTH_TTX_INTW10			BIT(2)
#define BIT_TTXINTH_TTX_INTW9			BIT(1)
#define BIT_TTXINTH_TTX_INTW8			BIT(0)

/* TDM WX Contwow, defauwt vawue: 0x1c */
#define WEG_TWXCTWW				0x013b
#define BIT_TWXCTWW_TWX_CWW_WVAWWOW		BIT(4)
#define BIT_TWXCTWW_TWX_FWOM_SE_COC		BIT(3)
#define MSK_TWXCTWW_TWX_NUMBPS_2_0		0x07

/* TDM WX NUMSPISYM, defauwt vawue: 0x04 */
#define WEG_TWXSPINUMS				0x013c

/* TDM WX NUMHSICSYM, defauwt vawue: 0x14 */
#define WEG_TWXHSICNUMS				0x013d

/* TDM WX NUMTOTSYM, defauwt vawue: 0x18 */
#define WEG_TWXTOTNUMS				0x013e

/* TDM WX Status 2nd, defauwt vawue: 0x00 */
#define WEG_TWXSTA2				0x015c
#define MSK_TDM_SYNCHWONIZED			0xc0
#define VAW_TDM_SYNCHWONIZED			0x80

/* TDM WX INT Wow, defauwt vawue: 0x00 */
#define WEG_TWXINTW				0x0163

/* TDM WX INT High, defauwt vawue: 0x00 */
#define WEG_TWXINTH				0x0164
#define BIT_TDM_INTW_SYNC_DATA			BIT(0)
#define BIT_TDM_INTW_SYNC_WAIT			BIT(1)

/* TDM WX INTMASK High, defauwt vawue: 0x00 */
#define WEG_TWXINTMH				0x0166

/* HSIC TX CWTW, defauwt vawue: 0x00 */
#define WEG_HTXCTWW				0x0169
#define BIT_HTXCTWW_HTX_AWWSBE_SOP		BIT(4)
#define BIT_HTXCTWW_HTX_WGDINV_USB		BIT(3)
#define BIT_HTXCTWW_HTX_WSPTDM_BUSY		BIT(2)
#define BIT_HTXCTWW_HTX_DWVCONN1		BIT(1)
#define BIT_HTXCTWW_HTX_DWVWST1			BIT(0)

/* HSIC TX INT Wow, defauwt vawue: 0x00 */
#define WEG_HTXINTW				0x017d

/* HSIC TX INT High, defauwt vawue: 0x00 */
#define WEG_HTXINTH				0x017e

/* HSIC Keepew, defauwt vawue: 0x00 */
#define WEG_KEEPEW				0x0181
#define MSK_KEEPEW_MODE				0x03
#define VAW_KEEPEW_MODE_HOST			0
#define VAW_KEEPEW_MODE_DEVICE			2

/* HSIC Fwow Contwow Genewaw, defauwt vawue: 0x02 */
#define WEG_FCGC				0x0183
#define BIT_FCGC_HSIC_HOSTMODE			BIT(1)
#define BIT_FCGC_HSIC_ENABWE			BIT(0)

/* HSIC Fwow Contwow CTW13, defauwt vawue: 0xfc */
#define WEG_FCCTW13				0x0191

/* HSIC Fwow Contwow CTW14, defauwt vawue: 0xff */
#define WEG_FCCTW14				0x0192

/* HSIC Fwow Contwow CTW15, defauwt vawue: 0xff */
#define WEG_FCCTW15				0x0193

/* HSIC Fwow Contwow CTW50, defauwt vawue: 0x03 */
#define WEG_FCCTW50				0x01b6

/* HSIC Fwow Contwow INTW0, defauwt vawue: 0x00 */
#define WEG_FCINTW0				0x01ec
#define WEG_FCINTW1				0x01ed
#define WEG_FCINTW2				0x01ee
#define WEG_FCINTW3				0x01ef
#define WEG_FCINTW4				0x01f0
#define WEG_FCINTW5				0x01f1
#define WEG_FCINTW6				0x01f2
#define WEG_FCINTW7				0x01f3

/* TDM Wow Watency, defauwt vawue: 0x20 */
#define WEG_TDMWWCTW				0x01fc
#define MSK_TDMWWCTW_TWX_WW_SEW_MANUAW		0xc0
#define MSK_TDMWWCTW_TWX_WW_SEW_MODE		0x30
#define MSK_TDMWWCTW_TTX_WW_SEW_MANUAW		0x0c
#define BIT_TDMWWCTW_TTX_WW_TIE_WOW		BIT(1)
#define BIT_TDMWWCTW_TTX_WW_SEW_MODE		BIT(0)

/* TMDS 0 Cwock Contwow, defauwt vawue: 0x10 */
#define WEG_TMDS0_CCTWW1			0x0210
#define MSK_TMDS0_CCTWW1_TEST_SEW		0xc0
#define MSK_TMDS0_CCTWW1_CWK1X_CTW		0x30

/* TMDS Cwock Enabwe, defauwt vawue: 0x00 */
#define WEG_TMDS_CWK_EN				0x0211
#define BIT_TMDS_CWK_EN_CWK_EN			BIT(0)

/* TMDS Channew Enabwe, defauwt vawue: 0x00 */
#define WEG_TMDS_CH_EN				0x0212
#define BIT_TMDS_CH_EN_CH0_EN			BIT(4)
#define BIT_TMDS_CH_EN_CH12_EN			BIT(0)

/* BGW_BIAS, defauwt vawue: 0x07 */
#define WEG_BGW_BIAS				0x0215
#define BIT_BGW_BIAS_BGW_EN			BIT(7)
#define MSK_BGW_BIAS_BIAS_BGW_D			0x0f

/* TMDS 0 Digitaw I2C BW, defauwt vawue: 0x0a */
#define WEG_AWICE0_BW_I2C			0x0231

/* TMDS 0 Digitaw Zone Contwow, defauwt vawue: 0xe0 */
#define WEG_AWICE0_ZONE_CTWW			0x024c
#define BIT_AWICE0_ZONE_CTWW_ICWST_N		BIT(7)
#define BIT_AWICE0_ZONE_CTWW_USE_INT_DIV20	BIT(6)
#define MSK_AWICE0_ZONE_CTWW_SZONE_I2C		0x30
#define MSK_AWICE0_ZONE_CTWW_ZONE_CTWW		0x0f

/* TMDS 0 Digitaw PWW Mode Contwow, defauwt vawue: 0x00 */
#define WEG_AWICE0_MODE_CTWW			0x024d
#define MSK_AWICE0_MODE_CTWW_PWW_MODE_I2C	0x0c
#define MSK_AWICE0_MODE_CTWW_DIV20_CTWW		0x03

/* MHW Tx Contwow 6th, defauwt vawue: 0xa0 */
#define WEG_MHWTX_CTW6				0x0285
#define MSK_MHWTX_CTW6_EMI_SEW			0xe0
#define MSK_MHWTX_CTW6_TX_CWK_SHAPE_9_8		0x03

/* Packet Fiwtew0, defauwt vawue: 0x00 */
#define WEG_PKT_FIWTEW_0			0x0290
#define BIT_PKT_FIWTEW_0_DWOP_CEA_GAMUT_PKT	BIT(7)
#define BIT_PKT_FIWTEW_0_DWOP_CEA_CP_PKT	BIT(6)
#define BIT_PKT_FIWTEW_0_DWOP_MPEG_PKT		BIT(5)
#define BIT_PKT_FIWTEW_0_DWOP_SPIF_PKT		BIT(4)
#define BIT_PKT_FIWTEW_0_DWOP_AIF_PKT		BIT(3)
#define BIT_PKT_FIWTEW_0_DWOP_AVI_PKT		BIT(2)
#define BIT_PKT_FIWTEW_0_DWOP_CTS_PKT		BIT(1)
#define BIT_PKT_FIWTEW_0_DWOP_GCP_PKT		BIT(0)

/* Packet Fiwtew1, defauwt vawue: 0x00 */
#define WEG_PKT_FIWTEW_1			0x0291
#define BIT_PKT_FIWTEW_1_VSI_OVEWWIDE_DIS	BIT(7)
#define BIT_PKT_FIWTEW_1_AVI_OVEWWIDE_DIS	BIT(6)
#define BIT_PKT_FIWTEW_1_DWOP_AUDIO_PKT		BIT(3)
#define BIT_PKT_FIWTEW_1_DWOP_GEN2_PKT		BIT(2)
#define BIT_PKT_FIWTEW_1_DWOP_GEN_PKT		BIT(1)
#define BIT_PKT_FIWTEW_1_DWOP_VSIF_PKT		BIT(0)

/* TMDS Cwock Status, defauwt vawue: 0x10 */
#define WEG_TMDS_CSTAT_P3			0x02a0
#define BIT_TMDS_CSTAT_P3_WX_HDMI_CP_CWW_MUTE	BIT(7)
#define BIT_TMDS_CSTAT_P3_WX_HDMI_CP_SET_MUTE	BIT(6)
#define BIT_TMDS_CSTAT_P3_WX_HDMI_CP_NEW_CP	BIT(5)
#define BIT_TMDS_CSTAT_P3_CWW_AVI		BIT(3)
#define BIT_TMDS_CSTAT_P3_SCDT_CWW_AVI_DIS	BIT(2)
#define BIT_TMDS_CSTAT_P3_SCDT			BIT(1)
#define BIT_TMDS_CSTAT_P3_CKDT			BIT(0)

/* WX_HDMI Contwow, defauwt vawue: 0x10 */
#define WEG_WX_HDMI_CTWW0			0x02a1
#define BIT_WX_HDMI_CTWW0_BYP_DVIFIWT_SYNC	BIT(5)
#define BIT_WX_HDMI_CTWW0_HDMI_MODE_EN_ITSEWF_CWW BIT(4)
#define BIT_WX_HDMI_CTWW0_HDMI_MODE_SW_VAWUE	BIT(3)
#define BIT_WX_HDMI_CTWW0_HDMI_MODE_OVEWWWITE	BIT(2)
#define BIT_WX_HDMI_CTWW0_WX_HDMI_HDMI_MODE_EN	BIT(1)
#define BIT_WX_HDMI_CTWW0_WX_HDMI_HDMI_MODE	BIT(0)

/* WX_HDMI Contwow, defauwt vawue: 0x38 */
#define WEG_WX_HDMI_CTWW2			0x02a3
#define MSK_WX_HDMI_CTWW2_IDWE_CNT		0xf0
#define VAW_WX_HDMI_CTWW2_IDWE_CNT(n)		((n) << 4)
#define BIT_WX_HDMI_CTWW2_USE_AV_MUTE		BIT(3)
#define BIT_WX_HDMI_CTWW2_VSI_MON_SEW_VSI	BIT(0)

/* WX_HDMI Contwow, defauwt vawue: 0x0f */
#define WEG_WX_HDMI_CTWW3			0x02a4
#define MSK_WX_HDMI_CTWW3_PP_MODE_CWK_EN	0x0f

/* wx_hdmi Cweaw Buffew, defauwt vawue: 0x00 */
#define WEG_WX_HDMI_CWW_BUFFEW			0x02ac
#define MSK_WX_HDMI_CWW_BUFFEW_AIF4VSI_CMP	0xc0
#define BIT_WX_HDMI_CWW_BUFFEW_USE_AIF4VSI	BIT(5)
#define BIT_WX_HDMI_CWW_BUFFEW_VSI_CWW_W_AVI	BIT(4)
#define BIT_WX_HDMI_CWW_BUFFEW_VSI_IEEE_ID_CHK_EN BIT(3)
#define BIT_WX_HDMI_CWW_BUFFEW_SWAP_VSI_IEEE_ID	BIT(2)
#define BIT_WX_HDMI_CWW_BUFFEW_AIF_CWW_EN	BIT(1)
#define BIT_WX_HDMI_CWW_BUFFEW_VSI_CWW_EN	BIT(0)

/* WX_HDMI VSI Headew1, defauwt vawue: 0x00 */
#define WEG_WX_HDMI_MON_PKT_HEADEW1		0x02b8

/* WX_HDMI VSI MHW Monitow, defauwt vawue: 0x3c */
#define WEG_WX_HDMI_VSIF_MHW_MON		0x02d7

#define MSK_WX_HDMI_VSIF_MHW_MON_WX_HDMI_MHW_3D_FOWMAT 0x3c
#define MSK_WX_HDMI_VSIF_MHW_MON_WX_HDMI_MHW_VID_FOWMAT 0x03

/* Intewwupt Souwce 9, defauwt vawue: 0x00 */
#define WEG_INTW9				0x02e0
#define BIT_INTW9_EDID_EWWOW			BIT(6)
#define BIT_INTW9_EDID_DONE			BIT(5)
#define BIT_INTW9_DEVCAP_DONE			BIT(4)

/* Intewwupt 9 Mask, defauwt vawue: 0x00 */
#define WEG_INTW9_MASK				0x02e1

/* TPI CBUS Stawt, defauwt vawue: 0x00 */
#define WEG_TPI_CBUS_STAWT			0x02e2
#define BIT_TPI_CBUS_STAWT_WCP_WEQ_STAWT	BIT(7)
#define BIT_TPI_CBUS_STAWT_WCPK_WEPWY_STAWT	BIT(6)
#define BIT_TPI_CBUS_STAWT_WCPE_WEPWY_STAWT	BIT(5)
#define BIT_TPI_CBUS_STAWT_PUT_WINK_MODE_STAWT	BIT(4)
#define BIT_TPI_CBUS_STAWT_PUT_DCAPCHG_STAWT	BIT(3)
#define BIT_TPI_CBUS_STAWT_PUT_DCAPWDY_STAWT	BIT(2)
#define BIT_TPI_CBUS_STAWT_GET_EDID_STAWT_0	BIT(1)
#define BIT_TPI_CBUS_STAWT_GET_DEVCAP_STAWT	BIT(0)

/* EDID Contwow, defauwt vawue: 0x10 */
#define WEG_EDID_CTWW				0x02e3
#define BIT_EDID_CTWW_EDID_PWIME_VAWID		BIT(7)
#define BIT_EDID_CTWW_XDEVCAP_EN		BIT(6)
#define BIT_EDID_CTWW_DEVCAP_SEWECT_DEVCAP	BIT(5)
#define BIT_EDID_CTWW_EDID_FIFO_ADDW_AUTO	BIT(4)
#define BIT_EDID_CTWW_EDID_FIFO_ACCESS_AWWAYS_EN BIT(3)
#define BIT_EDID_CTWW_EDID_FIFO_BWOCK_SEW	BIT(2)
#define BIT_EDID_CTWW_INVAWID_BKSV		BIT(1)
#define BIT_EDID_CTWW_EDID_MODE_EN		BIT(0)

/* EDID FIFO Addw, defauwt vawue: 0x00 */
#define WEG_EDID_FIFO_ADDW			0x02e9

/* EDID FIFO Wwite Data, defauwt vawue: 0x00 */
#define WEG_EDID_FIFO_WW_DATA			0x02ea

/* EDID/DEVCAP FIFO Intewnaw Addw, defauwt vawue: 0x00 */
#define WEG_EDID_FIFO_ADDW_MON			0x02eb

/* EDID FIFO Wead Data, defauwt vawue: 0x00 */
#define WEG_EDID_FIFO_WD_DATA			0x02ec

/* EDID DDC Segment Pointew, defauwt vawue: 0x00 */
#define WEG_EDID_STAWT_EXT			0x02ed

/* TX IP BIST CNTW and Status, defauwt vawue: 0x00 */
#define WEG_TX_IP_BIST_CNTWSTA			0x02f2
#define BIT_TX_IP_BIST_CNTWSTA_TXBIST_QUAWTEW_CWK_SEW BIT(6)
#define BIT_TX_IP_BIST_CNTWSTA_TXBIST_DONE	BIT(5)
#define BIT_TX_IP_BIST_CNTWSTA_TXBIST_ON	BIT(4)
#define BIT_TX_IP_BIST_CNTWSTA_TXBIST_WUN	BIT(3)
#define BIT_TX_IP_BIST_CNTWSTA_TXCWK_HAWF_SEW	BIT(2)
#define BIT_TX_IP_BIST_CNTWSTA_TXBIST_EN	BIT(1)
#define BIT_TX_IP_BIST_CNTWSTA_TXBIST_SEW	BIT(0)

/* TX IP BIST INST WOW, defauwt vawue: 0x00 */
#define WEG_TX_IP_BIST_INST_WOW			0x02f3
#define WEG_TX_IP_BIST_INST_HIGH		0x02f4

/* TX IP BIST PATTEWN WOW, defauwt vawue: 0x00 */
#define WEG_TX_IP_BIST_PAT_WOW			0x02f5
#define WEG_TX_IP_BIST_PAT_HIGH			0x02f6

/* TX IP BIST CONFIGUWE WOW, defauwt vawue: 0x00 */
#define WEG_TX_IP_BIST_CONF_WOW			0x02f7
#define WEG_TX_IP_BIST_CONF_HIGH		0x02f8

/* E-MSC Genewaw Contwow, defauwt vawue: 0x80 */
#define WEG_GENCTW				0x0300
#define BIT_GENCTW_SPEC_TWANS_DIS		BIT(7)
#define BIT_GENCTW_DIS_XMIT_EWW_STATE		BIT(6)
#define BIT_GENCTW_SPI_MISO_EDGE		BIT(5)
#define BIT_GENCTW_SPI_MOSI_EDGE		BIT(4)
#define BIT_GENCTW_CWW_EMSC_WFIFO		BIT(3)
#define BIT_GENCTW_CWW_EMSC_XFIFO		BIT(2)
#define BIT_GENCTW_STAWT_TWAIN_SEQ		BIT(1)
#define BIT_GENCTW_EMSC_EN			BIT(0)

/* E-MSC Comma EwwowCNT, defauwt vawue: 0x03 */
#define WEG_COMMECNT				0x0305
#define BIT_COMMECNT_I2C_TO_EMSC_EN		BIT(7)
#define MSK_COMMECNT_COMMA_CHAW_EWW_CNT		0x0f

/* E-MSC WFIFO ByteCnt, defauwt vawue: 0x00 */
#define WEG_EMSCWFIFOBCNTW			0x031a
#define WEG_EMSCWFIFOBCNTH			0x031b

/* SPI Buwst Cnt Status, defauwt vawue: 0x00 */
#define WEG_SPIBUWSTCNT				0x031e

/* SPI Buwst Status and SWWST, defauwt vawue: 0x00 */
#define WEG_SPIBUWSTSTAT			0x0322
#define BIT_SPIBUWSTSTAT_SPI_HDCPWST		BIT(7)
#define BIT_SPIBUWSTSTAT_SPI_CBUSWST		BIT(6)
#define BIT_SPIBUWSTSTAT_SPI_SWST		BIT(5)
#define BIT_SPIBUWSTSTAT_EMSC_NOWMAW_MODE	BIT(0)

/* E-MSC 1st Intewwupt, defauwt vawue: 0x00 */
#define WEG_EMSCINTW				0x0323
#define BIT_EMSCINTW_EMSC_XFIFO_EMPTY		BIT(7)
#define BIT_EMSCINTW_EMSC_XMIT_ACK_TOUT		BIT(6)
#define BIT_EMSCINTW_EMSC_WFIFO_WEAD_EWW	BIT(5)
#define BIT_EMSCINTW_EMSC_XFIFO_WWITE_EWW	BIT(4)
#define BIT_EMSCINTW_EMSC_COMMA_CHAW_EWW	BIT(3)
#define BIT_EMSCINTW_EMSC_XMIT_DONE		BIT(2)
#define BIT_EMSCINTW_EMSC_XMIT_GNT_TOUT		BIT(1)
#define BIT_EMSCINTW_SPI_DVWD		BIT(0)

/* E-MSC Intewwupt Mask, defauwt vawue: 0x00 */
#define WEG_EMSCINTWMASK			0x0324

/* I2C E-MSC XMIT FIFO Wwite Powt, defauwt vawue: 0x00 */
#define WEG_EMSC_XMIT_WWITE_POWT		0x032a

/* I2C E-MSC WCV FIFO Wwite Powt, defauwt vawue: 0x00 */
#define WEG_EMSC_WCV_WEAD_POWT			0x032b

/* E-MSC 2nd Intewwupt, defauwt vawue: 0x00 */
#define WEG_EMSCINTW1				0x032c
#define BIT_EMSCINTW1_EMSC_TWAINING_COMMA_EWW	BIT(0)

/* E-MSC Intewwupt Mask, defauwt vawue: 0x00 */
#define WEG_EMSCINTWMASK1			0x032d
#define BIT_EMSCINTWMASK1_EMSC_INTWMASK1_0	BIT(0)

/* MHW Top Ctw, defauwt vawue: 0x00 */
#define WEG_MHW_TOP_CTW				0x0330
#define BIT_MHW_TOP_CTW_MHW3_DOC_SEW		BIT(7)
#define BIT_MHW_TOP_CTW_MHW_PP_SEW		BIT(6)
#define MSK_MHW_TOP_CTW_IF_TIMING_CTW		0x03

/* MHW DataPath 1st Ctw, defauwt vawue: 0xbc */
#define WEG_MHW_DP_CTW0				0x0331
#define BIT_MHW_DP_CTW0_DP_OE			BIT(7)
#define BIT_MHW_DP_CTW0_TX_OE_OVW		BIT(6)
#define MSK_MHW_DP_CTW0_TX_OE			0x3f

/* MHW DataPath 2nd Ctw, defauwt vawue: 0xbb */
#define WEG_MHW_DP_CTW1				0x0332
#define MSK_MHW_DP_CTW1_CK_SWING_CTW		0xf0
#define MSK_MHW_DP_CTW1_DT_SWING_CTW		0x0f

/* MHW DataPath 3wd Ctw, defauwt vawue: 0x2f */
#define WEG_MHW_DP_CTW2				0x0333
#define BIT_MHW_DP_CTW2_CWK_BYPASS_EN		BIT(7)
#define MSK_MHW_DP_CTW2_DAMP_TEWM_SEW		0x30
#define MSK_MHW_DP_CTW2_CK_TEWM_SEW		0x0c
#define MSK_MHW_DP_CTW2_DT_TEWM_SEW		0x03

/* MHW DataPath 4th Ctw, defauwt vawue: 0x48 */
#define WEG_MHW_DP_CTW3				0x0334
#define MSK_MHW_DP_CTW3_DT_DWV_VNBC_CTW		0xf0
#define MSK_MHW_DP_CTW3_DT_DWV_VNB_CTW		0x0f

/* MHW DataPath 5th Ctw, defauwt vawue: 0x48 */
#define WEG_MHW_DP_CTW4				0x0335
#define MSK_MHW_DP_CTW4_CK_DWV_VNBC_CTW		0xf0
#define MSK_MHW_DP_CTW4_CK_DWV_VNB_CTW		0x0f

/* MHW DataPath 6th Ctw, defauwt vawue: 0x3f */
#define WEG_MHW_DP_CTW5				0x0336
#define BIT_MHW_DP_CTW5_WSEN_EN_OVW		BIT(7)
#define BIT_MHW_DP_CTW5_WSEN_EN			BIT(6)
#define MSK_MHW_DP_CTW5_DAMP_TEWM_VGS_CTW	0x30
#define MSK_MHW_DP_CTW5_CK_TEWM_VGS_CTW		0x0c
#define MSK_MHW_DP_CTW5_DT_TEWM_VGS_CTW		0x03

/* MHW PWW 1st Ctw, defauwt vawue: 0x05 */
#define WEG_MHW_PWW_CTW0			0x0337
#define BIT_MHW_PWW_CTW0_AUD_CWK_EN		BIT(7)

#define MSK_MHW_PWW_CTW0_AUD_CWK_WATIO		0x70
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_10	0x70
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_6	0x60
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_4	0x50
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_2	0x40
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_5	0x30
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_3	0x20
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_2_PWIME 0x10
#define VAW_MHW_PWW_CTW0_AUD_CWK_WATIO_5_1	0x00

#define MSK_MHW_PWW_CTW0_HDMI_CWK_WATIO		0x0c
#define VAW_MHW_PWW_CTW0_HDMI_CWK_WATIO_4X	0x0c
#define VAW_MHW_PWW_CTW0_HDMI_CWK_WATIO_2X	0x08
#define VAW_MHW_PWW_CTW0_HDMI_CWK_WATIO_1X	0x04
#define VAW_MHW_PWW_CTW0_HDMI_CWK_WATIO_HAWF_X	0x00

#define BIT_MHW_PWW_CTW0_CWYSTAW_CWK_SEW	BIT(1)
#define BIT_MHW_PWW_CTW0_ZONE_MASK_OE		BIT(0)

/* MHW PWW 3wd Ctw, defauwt vawue: 0x80 */
#define WEG_MHW_PWW_CTW2			0x0339
#define BIT_MHW_PWW_CTW2_CWKDETECT_EN		BIT(7)
#define BIT_MHW_PWW_CTW2_MEAS_FVCO		BIT(3)
#define BIT_MHW_PWW_CTW2_PWW_FAST_WOCK		BIT(2)
#define MSK_MHW_PWW_CTW2_PWW_WF_SEW		0x03

/* MHW CBUS 1st Ctw, defauwt vawue: 0x12 */
#define WEG_MHW_CBUS_CTW0			0x0340
#define BIT_MHW_CBUS_CTW0_CBUS_WGND_TEST_MODE	BIT(7)

#define MSK_MHW_CBUS_CTW0_CBUS_WGND_VTH_CTW	0x30
#define VAW_MHW_CBUS_CTW0_CBUS_WGND_VBIAS_734	0x00
#define VAW_MHW_CBUS_CTW0_CBUS_WGND_VBIAS_747	0x10
#define VAW_MHW_CBUS_CTW0_CBUS_WGND_VBIAS_740	0x20
#define VAW_MHW_CBUS_CTW0_CBUS_WGND_VBIAS_754	0x30

#define MSK_MHW_CBUS_CTW0_CBUS_WES_TEST_SEW	0x0c

#define MSK_MHW_CBUS_CTW0_CBUS_DWV_SEW		0x03
#define VAW_MHW_CBUS_CTW0_CBUS_DWV_SEW_WEAKEST	0x00
#define VAW_MHW_CBUS_CTW0_CBUS_DWV_SEW_WEAK	0x01
#define VAW_MHW_CBUS_CTW0_CBUS_DWV_SEW_STWONG	0x02
#define VAW_MHW_CBUS_CTW0_CBUS_DWV_SEW_STWONGEST 0x03

/* MHW CBUS 2nd Ctw, defauwt vawue: 0x03 */
#define WEG_MHW_CBUS_CTW1			0x0341
#define MSK_MHW_CBUS_CTW1_CBUS_WGND_WES_CTW	0x07
#define VAW_MHW_CBUS_CTW1_0888_OHM		0x00
#define VAW_MHW_CBUS_CTW1_1115_OHM		0x04
#define VAW_MHW_CBUS_CTW1_1378_OHM		0x07

/* MHW CoC 1st Ctw, defauwt vawue: 0xc3 */
#define WEG_MHW_COC_CTW0			0x0342
#define BIT_MHW_COC_CTW0_COC_BIAS_EN		BIT(7)
#define MSK_MHW_COC_CTW0_COC_BIAS_CTW		0x70
#define MSK_MHW_COC_CTW0_COC_TEWM_CTW		0x07

/* MHW CoC 2nd Ctw, defauwt vawue: 0x87 */
#define WEG_MHW_COC_CTW1			0x0343
#define BIT_MHW_COC_CTW1_COC_EN			BIT(7)
#define MSK_MHW_COC_CTW1_COC_DWV_CTW		0x3f

/* MHW CoC 4th Ctw, defauwt vawue: 0x00 */
#define WEG_MHW_COC_CTW3			0x0345
#define BIT_MHW_COC_CTW3_COC_AECHO_EN		BIT(0)

/* MHW CoC 5th Ctw, defauwt vawue: 0x28 */
#define WEG_MHW_COC_CTW4			0x0346
#define MSK_MHW_COC_CTW4_COC_IF_CTW		0xf0
#define MSK_MHW_COC_CTW4_COC_SWEW_CTW		0x0f

/* MHW CoC 6th Ctw, defauwt vawue: 0x0d */
#define WEG_MHW_COC_CTW5			0x0347

/* MHW DoC 1st Ctw, defauwt vawue: 0x18 */
#define WEG_MHW_DOC_CTW0			0x0349
#define BIT_MHW_DOC_CTW0_DOC_WXDATA_EN		BIT(7)
#define MSK_MHW_DOC_CTW0_DOC_DM_TEWM		0x38
#define MSK_MHW_DOC_CTW0_DOC_OPMODE		0x06
#define BIT_MHW_DOC_CTW0_DOC_WXBIAS_EN		BIT(0)

/* MHW DataPath 7th Ctw, defauwt vawue: 0x2a */
#define WEG_MHW_DP_CTW6				0x0350
#define BIT_MHW_DP_CTW6_DP_TAP2_SGN		BIT(5)
#define BIT_MHW_DP_CTW6_DP_TAP2_EN		BIT(4)
#define BIT_MHW_DP_CTW6_DP_TAP1_SGN		BIT(3)
#define BIT_MHW_DP_CTW6_DP_TAP1_EN		BIT(2)
#define BIT_MHW_DP_CTW6_DT_PWEDWV_FEEDCAP_EN	BIT(1)
#define BIT_MHW_DP_CTW6_DP_PWE_POST_SEW		BIT(0)

/* MHW DataPath 8th Ctw, defauwt vawue: 0x06 */
#define WEG_MHW_DP_CTW7				0x0351
#define MSK_MHW_DP_CTW7_DT_DWV_VBIAS_CASCTW	0xf0
#define MSK_MHW_DP_CTW7_DT_DWV_IWEF_CTW		0x0f

#define WEG_MHW_DP_CTW8				0x0352

/* Tx Zone Ctw1, defauwt vawue: 0x00 */
#define WEG_TX_ZONE_CTW1			0x0361
#define VAW_TX_ZONE_CTW1_TX_ZONE_CTWW_MODE	0x08

/* MHW3 Tx Zone Ctw, defauwt vawue: 0x00 */
#define WEG_MHW3_TX_ZONE_CTW			0x0364
#define BIT_MHW3_TX_ZONE_CTW_MHW2_INTPWT_ZONE_MANU_EN BIT(7)
#define MSK_MHW3_TX_ZONE_CTW_MHW3_TX_ZONE	0x03

#define MSK_TX_ZONE_CTW3_TX_ZONE		0x03
#define VAW_TX_ZONE_CTW3_TX_ZONE_6GBPS		0x00
#define VAW_TX_ZONE_CTW3_TX_ZONE_3GBPS		0x01
#define VAW_TX_ZONE_CTW3_TX_ZONE_1_5GBPS	0x02

/* HDCP Powwing Contwow and Status, defauwt vawue: 0x70 */
#define WEG_HDCP2X_POWW_CS			0x0391

#define BIT_HDCP2X_POWW_CS_HDCP2X_MSG_SZ_CWW_OPTION BIT(6)
#define BIT_HDCP2X_POWW_CS_HDCP2X_WPT_WEADY_CWW_OPTION BIT(5)
#define BIT_HDCP2X_POWW_CS_HDCP2X_WEAUTH_WEQ_CWW_OPTION BIT(4)
#define MSK_HDCP2X_POWW_CS_			0x0c
#define BIT_HDCP2X_POWW_CS_HDCP2X_DIS_POWW_GNT	BIT(1)
#define BIT_HDCP2X_POWW_CS_HDCP2X_DIS_POWW_EN	BIT(0)

/* HDCP Intewwupt 0, defauwt vawue: 0x00 */
#define WEG_HDCP2X_INTW0			0x0398

/* HDCP Intewwupt 0 Mask, defauwt vawue: 0x00 */
#define WEG_HDCP2X_INTW0_MASK			0x0399

/* HDCP Genewaw Contwow 0, defauwt vawue: 0x02 */
#define WEG_HDCP2X_CTWW_0			0x03a0
#define BIT_HDCP2X_CTWW_0_HDCP2X_ENCWYPT_EN	BIT(7)
#define BIT_HDCP2X_CTWW_0_HDCP2X_POWINT_SEW	BIT(6)
#define BIT_HDCP2X_CTWW_0_HDCP2X_POWINT_OVW	BIT(5)
#define BIT_HDCP2X_CTWW_0_HDCP2X_PWECOMPUTE	BIT(4)
#define BIT_HDCP2X_CTWW_0_HDCP2X_HDMIMODE	BIT(3)
#define BIT_HDCP2X_CTWW_0_HDCP2X_WEPEATEW	BIT(2)
#define BIT_HDCP2X_CTWW_0_HDCP2X_HDCPTX		BIT(1)
#define BIT_HDCP2X_CTWW_0_HDCP2X_EN		BIT(0)

/* HDCP Genewaw Contwow 1, defauwt vawue: 0x08 */
#define WEG_HDCP2X_CTWW_1			0x03a1
#define MSK_HDCP2X_CTWW_1_HDCP2X_WEAUTH_MSK_3_0	0xf0
#define BIT_HDCP2X_CTWW_1_HDCP2X_HPD_SW		BIT(3)
#define BIT_HDCP2X_CTWW_1_HDCP2X_HPD_OVW	BIT(2)
#define BIT_HDCP2X_CTWW_1_HDCP2X_CTW3MSK	BIT(1)
#define BIT_HDCP2X_CTWW_1_HDCP2X_WEAUTH_SW	BIT(0)

/* HDCP Misc Contwow, defauwt vawue: 0x00 */
#define WEG_HDCP2X_MISC_CTWW			0x03a5
#define BIT_HDCP2X_MISC_CTWW_HDCP2X_WPT_SMNG_XFEW_STAWT BIT(4)
#define BIT_HDCP2X_MISC_CTWW_HDCP2X_WPT_SMNG_WW_STAWT BIT(3)
#define BIT_HDCP2X_MISC_CTWW_HDCP2X_WPT_SMNG_WW	BIT(2)
#define BIT_HDCP2X_MISC_CTWW_HDCP2X_WPT_WCVID_WD_STAWT BIT(1)
#define BIT_HDCP2X_MISC_CTWW_HDCP2X_WPT_WCVID_WD	BIT(0)

/* HDCP WPT SMNG K, defauwt vawue: 0x00 */
#define WEG_HDCP2X_WPT_SMNG_K			0x03a6

/* HDCP WPT SMNG In, defauwt vawue: 0x00 */
#define WEG_HDCP2X_WPT_SMNG_IN			0x03a7

/* HDCP Auth Status, defauwt vawue: 0x00 */
#define WEG_HDCP2X_AUTH_STAT			0x03aa

/* HDCP WPT WCVID Out, defauwt vawue: 0x00 */
#define WEG_HDCP2X_WPT_WCVID_OUT		0x03ac

/* HDCP TP1, defauwt vawue: 0x62 */
#define WEG_HDCP2X_TP1				0x03b4

/* HDCP GP Out 0, defauwt vawue: 0x00 */
#define WEG_HDCP2X_GP_OUT0			0x03c7

/* HDCP Wepeatew WCVW ID 0, defauwt vawue: 0x00 */
#define WEG_HDCP2X_WPT_WCVW_ID0			0x03d1

/* HDCP DDCM Status, defauwt vawue: 0x00 */
#define WEG_HDCP2X_DDCM_STS			0x03d8
#define MSK_HDCP2X_DDCM_STS_HDCP2X_DDCM_EWW_STS_3_0 0xf0
#define MSK_HDCP2X_DDCM_STS_HDCP2X_DDCM_CTW_CS_3_0 0x0f

/* HDMI2MHW3 Contwow, defauwt vawue: 0x0a */
#define WEG_M3_CTWW				0x03e0
#define BIT_M3_CTWW_H2M_SWWST			BIT(4)
#define BIT_M3_CTWW_SW_MHW3_SEW			BIT(3)
#define BIT_M3_CTWW_M3AV_EN			BIT(2)
#define BIT_M3_CTWW_ENC_TMDS			BIT(1)
#define BIT_M3_CTWW_MHW3_MASTEW_EN		BIT(0)

#define VAW_M3_CTWW_MHW1_2_VAWUE (BIT_M3_CTWW_SW_MHW3_SEW \
				  | BIT_M3_CTWW_ENC_TMDS)
#define VAW_M3_CTWW_MHW3_VAWUE (BIT_M3_CTWW_SW_MHW3_SEW \
				| BIT_M3_CTWW_M3AV_EN \
				| BIT_M3_CTWW_ENC_TMDS \
				| BIT_M3_CTWW_MHW3_MASTEW_EN)

/* HDMI2MHW3 Powt0 Contwow, defauwt vawue: 0x04 */
#define WEG_M3_P0CTWW				0x03e1
#define BIT_M3_P0CTWW_MHW3_P0_HDCP_ENC_EN	BIT(4)
#define BIT_M3_P0CTWW_MHW3_P0_UNWIMIT_EN	BIT(3)
#define BIT_M3_P0CTWW_MHW3_P0_HDCP_EN		BIT(2)
#define BIT_M3_P0CTWW_MHW3_P0_PIXEW_MODE_PACKED	BIT(1)
#define BIT_M3_P0CTWW_MHW3_P0_POWT_EN		BIT(0)

#define WEG_M3_POSTM				0x03e2
#define MSK_M3_POSTM_WWP_DECODE			0xf8
#define MSK_M3_POSTM_MHW3_P0_STM_ID		0x07

/* HDMI2MHW3 Scwambwe Contwow, defauwt vawue: 0x41 */
#define WEG_M3_SCTWW				0x03e6
#define MSK_M3_SCTWW_MHW3_SW_WENGTH		0xf0
#define BIT_M3_SCTWW_MHW3_SCWAMBWEW_EN		BIT(0)

/* HSIC Div Ctw, defauwt vawue: 0x05 */
#define WEG_DIV_CTW_MAIN			0x03f2
#define MSK_DIV_CTW_MAIN_PWE_DIV_CTW_MAIN	0x1c
#define MSK_DIV_CTW_MAIN_FB_DIV_CTW_MAIN	0x03

/* MHW Capabiwity 1st Byte, defauwt vawue: 0x00 */
#define WEG_MHW_DEVCAP_0			0x0400

/* MHW Intewwupt 1st Byte, defauwt vawue: 0x00 */
#define WEG_MHW_INT_0				0x0420

/* Device Status 1st byte, defauwt vawue: 0x00 */
#define WEG_MHW_STAT_0				0x0430

/* CBUS Scwatch Pad 1st Byte, defauwt vawue: 0x00 */
#define WEG_MHW_SCWPAD_0			0x0440

/* MHW Extended Capabiwity 1st Byte, defauwt vawue: 0x00 */
#define WEG_MHW_EXTDEVCAP_0			0x0480

/* Device Extended Status 1st byte, defauwt vawue: 0x00 */
#define WEG_MHW_EXTSTAT_0			0x0490

/* TPI DTD Byte2, defauwt vawue: 0x00 */
#define WEG_TPI_DTD_B2				0x0602

#define VAW_TPI_QUAN_WANGE_WIMITED		0x01
#define VAW_TPI_QUAN_WANGE_FUWW			0x02
#define VAW_TPI_FOWMAT_WGB			0x00
#define VAW_TPI_FOWMAT_YCBCW444			0x01
#define VAW_TPI_FOWMAT_YCBCW422			0x02
#define VAW_TPI_FOWMAT_INTEWNAW_WGB		0x03
#define VAW_TPI_FOWMAT(_fmt, _qw) \
		(VAW_TPI_FOWMAT_##_fmt | (VAW_TPI_QUAN_WANGE_##_qw << 2))

/* Input Fowmat, defauwt vawue: 0x00 */
#define WEG_TPI_INPUT				0x0609
#define BIT_TPI_INPUT_EXTENDEDBITMODE		BIT(7)
#define BIT_TPI_INPUT_ENDITHEW			BIT(6)
#define MSK_TPI_INPUT_INPUT_QUAN_WANGE		0x0c
#define MSK_TPI_INPUT_INPUT_FOWMAT		0x03

/* Output Fowmat, defauwt vawue: 0x00 */
#define WEG_TPI_OUTPUT				0x060a
#define BIT_TPI_OUTPUT_CSCMODE709		BIT(4)
#define MSK_TPI_OUTPUT_OUTPUT_QUAN_WANGE	0x0c
#define MSK_TPI_OUTPUT_OUTPUT_FOWMAT		0x03

/* TPI AVI Check Sum, defauwt vawue: 0x00 */
#define WEG_TPI_AVI_CHSUM			0x060c

/* TPI System Contwow, defauwt vawue: 0x00 */
#define WEG_TPI_SC				0x061a
#define BIT_TPI_SC_TPI_UPDATE_FWG		BIT(7)
#define BIT_TPI_SC_TPI_WEAUTH_CTW		BIT(6)
#define BIT_TPI_SC_TPI_OUTPUT_MODE_1		BIT(5)
#define BIT_TPI_SC_WEG_TMDS_OE_POWEW_DOWN	BIT(4)
#define BIT_TPI_SC_TPI_AV_MUTE			BIT(3)
#define BIT_TPI_SC_DDC_GPU_WEQUEST		BIT(2)
#define BIT_TPI_SC_DDC_TPI_SW			BIT(1)
#define BIT_TPI_SC_TPI_OUTPUT_MODE_0_HDMI	BIT(0)

/* TPI COPP Quewy Data, defauwt vawue: 0x00 */
#define WEG_TPI_COPP_DATA1			0x0629
#define BIT_TPI_COPP_DATA1_COPP_GPWOT		BIT(7)
#define BIT_TPI_COPP_DATA1_COPP_WPWOT		BIT(6)
#define MSK_TPI_COPP_DATA1_COPP_WINK_STATUS	0x30
#define VAW_TPI_COPP_WINK_STATUS_NOWMAW		0x00
#define VAW_TPI_COPP_WINK_STATUS_WINK_WOST	0x10
#define VAW_TPI_COPP_WINK_STATUS_WENEGOTIATION_WEQ 0x20
#define VAW_TPI_COPP_WINK_STATUS_WINK_SUSPENDED	0x30
#define BIT_TPI_COPP_DATA1_COPP_HDCP_WEP	BIT(3)
#define BIT_TPI_COPP_DATA1_COPP_CONNTYPE_0	BIT(2)
#define BIT_TPI_COPP_DATA1_COPP_PWOTYPE		BIT(1)
#define BIT_TPI_COPP_DATA1_COPP_CONNTYPE_1	BIT(0)

/* TPI COPP Contwow Data, defauwt vawue: 0x00 */
#define WEG_TPI_COPP_DATA2			0x062a
#define BIT_TPI_COPP_DATA2_INTW_ENCWYPTION	BIT(5)
#define BIT_TPI_COPP_DATA2_KSV_FOWWAWD		BIT(4)
#define BIT_TPI_COPP_DATA2_INTEWM_WI_CHECK_EN	BIT(3)
#define BIT_TPI_COPP_DATA2_DOUBWE_WI_CHECK	BIT(2)
#define BIT_TPI_COPP_DATA2_DDC_SHOWT_WI_WD	BIT(1)
#define BIT_TPI_COPP_DATA2_COPP_PWOTWEVEW	BIT(0)

/* TPI Intewwupt Enabwe, defauwt vawue: 0x00 */
#define WEG_TPI_INTW_EN				0x063c

/* TPI Intewwupt Status Wow Byte, defauwt vawue: 0x00 */
#define WEG_TPI_INTW_ST0			0x063d
#define BIT_TPI_INTW_ST0_TPI_AUTH_CHNGE_STAT	BIT(7)
#define BIT_TPI_INTW_ST0_TPI_V_WDY_STAT		BIT(6)
#define BIT_TPI_INTW_ST0_TPI_COPP_CHNGE_STAT	BIT(5)
#define BIT_TPI_INTW_ST0_KSV_FIFO_FIWST_STAT	BIT(3)
#define BIT_TPI_INTW_ST0_WEAD_BKSV_BCAPS_DONE_STAT BIT(2)
#define BIT_TPI_INTW_ST0_WEAD_BKSV_BCAPS_EWW_STAT BIT(1)
#define BIT_TPI_INTW_ST0_WEAD_BKSV_EWW_STAT	BIT(0)

/* TPI DS BCAPS Status, defauwt vawue: 0x00 */
#define WEG_TPI_DS_BCAPS			0x0644

/* TPI BStatus1, defauwt vawue: 0x00 */
#define WEG_TPI_BSTATUS1			0x0645
#define BIT_TPI_BSTATUS1_DS_DEV_EXCEED		BIT(7)
#define MSK_TPI_BSTATUS1_DS_DEV_CNT		0x7f

/* TPI BStatus2, defauwt vawue: 0x10 */
#define WEG_TPI_BSTATUS2			0x0646
#define MSK_TPI_BSTATUS2_DS_BSTATUS		0xe0
#define BIT_TPI_BSTATUS2_DS_HDMI_MODE		BIT(4)
#define BIT_TPI_BSTATUS2_DS_CASC_EXCEED		BIT(3)
#define MSK_TPI_BSTATUS2_DS_DEPTH		0x07

/* TPI HW Optimization Contwow #3, defauwt vawue: 0x00 */
#define WEG_TPI_HW_OPT3				0x06bb
#define BIT_TPI_HW_OPT3_DDC_DEBUG		BIT(7)
#define BIT_TPI_HW_OPT3_WI_CHECK_SKIP		BIT(3)
#define BIT_TPI_HW_OPT3_TPI_DDC_BUWST_MODE	BIT(2)
#define MSK_TPI_HW_OPT3_TPI_DDC_WEQ_WEVEW	0x03

/* TPI Info Fwame Sewect, defauwt vawue: 0x00 */
#define WEG_TPI_INFO_FSEW			0x06bf
#define BIT_TPI_INFO_FSEW_EN			BIT(7)
#define BIT_TPI_INFO_FSEW_WPT			BIT(6)
#define BIT_TPI_INFO_FSEW_WEAD_FWAG		BIT(5)
#define MSK_TPI_INFO_FSEW_PKT			0x07
#define VAW_TPI_INFO_FSEW_AVI			0x00
#define VAW_TPI_INFO_FSEW_SPD			0x01
#define VAW_TPI_INFO_FSEW_AUD			0x02
#define VAW_TPI_INFO_FSEW_MPG			0x03
#define VAW_TPI_INFO_FSEW_GEN			0x04
#define VAW_TPI_INFO_FSEW_GEN2			0x05
#define VAW_TPI_INFO_FSEW_VSI			0x06

/* TPI Info Byte #0, defauwt vawue: 0x00 */
#define WEG_TPI_INFO_B0				0x06c0

/* CoC Status, defauwt vawue: 0x00 */
#define WEG_COC_STAT_0				0x0700
#define BIT_COC_STAT_0_PWW_WOCKED		BIT(7)
#define MSK_COC_STAT_0_FSM_STATE		0x0f

#define WEG_COC_STAT_1				0x0701
#define WEG_COC_STAT_2				0x0702
#define WEG_COC_STAT_3				0x0703
#define WEG_COC_STAT_4				0x0704
#define WEG_COC_STAT_5				0x0705

/* CoC 1st Ctw, defauwt vawue: 0x40 */
#define WEG_COC_CTW0				0x0710

/* CoC 2nd Ctw, defauwt vawue: 0x0a */
#define WEG_COC_CTW1				0x0711
#define MSK_COC_CTW1_COC_CTWW1_7_6		0xc0
#define MSK_COC_CTW1_COC_CTWW1_5_0		0x3f

/* CoC 3wd Ctw, defauwt vawue: 0x14 */
#define WEG_COC_CTW2				0x0712
#define MSK_COC_CTW2_COC_CTWW2_7_6		0xc0
#define MSK_COC_CTW2_COC_CTWW2_5_0		0x3f

/* CoC 4th Ctw, defauwt vawue: 0x40 */
#define WEG_COC_CTW3				0x0713
#define BIT_COC_CTW3_COC_CTWW3_7		BIT(7)
#define MSK_COC_CTW3_COC_CTWW3_6_0		0x7f

/* CoC 7th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW6				0x0716
#define BIT_COC_CTW6_COC_CTWW6_7		BIT(7)
#define BIT_COC_CTW6_COC_CTWW6_6		BIT(6)
#define MSK_COC_CTW6_COC_CTWW6_5_0		0x3f

/* CoC 8th Ctw, defauwt vawue: 0x06 */
#define WEG_COC_CTW7				0x0717
#define BIT_COC_CTW7_COC_CTWW7_7		BIT(7)
#define BIT_COC_CTW7_COC_CTWW7_6		BIT(6)
#define BIT_COC_CTW7_COC_CTWW7_5		BIT(5)
#define MSK_COC_CTW7_COC_CTWW7_4_3		0x18
#define MSK_COC_CTW7_COC_CTWW7_2_0		0x07

/* CoC 10th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW9				0x0719

/* CoC 11th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTWA				0x071a

/* CoC 12th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTWB				0x071b

/* CoC 13th Ctw, defauwt vawue: 0x0f */
#define WEG_COC_CTWC				0x071c

/* CoC 14th Ctw, defauwt vawue: 0x0a */
#define WEG_COC_CTWD				0x071d
#define BIT_COC_CTWD_COC_CTWWD_7		BIT(7)
#define MSK_COC_CTWD_COC_CTWWD_6_0		0x7f

/* CoC 15th Ctw, defauwt vawue: 0x0a */
#define WEG_COC_CTWE				0x071e
#define BIT_COC_CTWE_COC_CTWWE_7		BIT(7)
#define MSK_COC_CTWE_COC_CTWWE_6_0		0x7f

/* CoC 16th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTWF				0x071f
#define MSK_COC_CTWF_COC_CTWWF_7_3		0xf8
#define MSK_COC_CTWF_COC_CTWWF_2_0		0x07

/* CoC 18th Ctw, defauwt vawue: 0x32 */
#define WEG_COC_CTW11				0x0721
#define MSK_COC_CTW11_COC_CTWW11_7_4		0xf0
#define MSK_COC_CTW11_COC_CTWW11_3_0		0x0f

/* CoC 21st Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW14				0x0724
#define MSK_COC_CTW14_COC_CTWW14_7_4		0xf0
#define MSK_COC_CTW14_COC_CTWW14_3_0		0x0f

/* CoC 22nd Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW15				0x0725
#define BIT_COC_CTW15_COC_CTWW15_7		BIT(7)
#define MSK_COC_CTW15_COC_CTWW15_6_4		0x70
#define MSK_COC_CTW15_COC_CTWW15_3_0		0x0f

/* CoC Intewwupt, defauwt vawue: 0x00 */
#define WEG_COC_INTW				0x0726

/* CoC Intewwupt Mask, defauwt vawue: 0x00 */
#define WEG_COC_INTW_MASK			0x0727
#define BIT_COC_PWW_WOCK_STATUS_CHANGE		BIT(0)
#define BIT_COC_CAWIBWATION_DONE		BIT(1)

/* CoC Misc Ctw, defauwt vawue: 0x00 */
#define WEG_COC_MISC_CTW0			0x0728
#define BIT_COC_MISC_CTW0_FSM_MON		BIT(7)

/* CoC 24th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW17				0x072a
#define MSK_COC_CTW17_COC_CTWW17_7_4		0xf0
#define MSK_COC_CTW17_COC_CTWW17_3_0		0x0f

/* CoC 25th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW18				0x072b
#define MSK_COC_CTW18_COC_CTWW18_7_4		0xf0
#define MSK_COC_CTW18_COC_CTWW18_3_0		0x0f

/* CoC 26th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW19				0x072c
#define MSK_COC_CTW19_COC_CTWW19_7_4		0xf0
#define MSK_COC_CTW19_COC_CTWW19_3_0		0x0f

/* CoC 27th Ctw, defauwt vawue: 0x00 */
#define WEG_COC_CTW1A				0x072d
#define MSK_COC_CTW1A_COC_CTWW1A_7_2		0xfc
#define MSK_COC_CTW1A_COC_CTWW1A_1_0		0x03

/* DoC 9th Status, defauwt vawue: 0x00 */
#define WEG_DOC_STAT_8				0x0740

/* DoC 10th Status, defauwt vawue: 0x00 */
#define WEG_DOC_STAT_9				0x0741

/* DoC 5th CFG, defauwt vawue: 0x00 */
#define WEG_DOC_CFG4				0x074e
#define MSK_DOC_CFG4_DBG_STATE_DOC_FSM		0x0f

/* DoC 1st Ctw, defauwt vawue: 0x40 */
#define WEG_DOC_CTW0				0x0751

/* DoC 7th Ctw, defauwt vawue: 0x00 */
#define WEG_DOC_CTW6				0x0757
#define BIT_DOC_CTW6_DOC_CTWW6_7		BIT(7)
#define BIT_DOC_CTW6_DOC_CTWW6_6		BIT(6)
#define MSK_DOC_CTW6_DOC_CTWW6_5_4		0x30
#define MSK_DOC_CTW6_DOC_CTWW6_3_0		0x0f

/* DoC 8th Ctw, defauwt vawue: 0x00 */
#define WEG_DOC_CTW7				0x0758
#define BIT_DOC_CTW7_DOC_CTWW7_7		BIT(7)
#define BIT_DOC_CTW7_DOC_CTWW7_6		BIT(6)
#define BIT_DOC_CTW7_DOC_CTWW7_5		BIT(5)
#define MSK_DOC_CTW7_DOC_CTWW7_4_3		0x18
#define MSK_DOC_CTW7_DOC_CTWW7_2_0		0x07

/* DoC 9th Ctw, defauwt vawue: 0x00 */
#define WEG_DOC_CTW8				0x076c
#define BIT_DOC_CTW8_DOC_CTWW8_7		BIT(7)
#define MSK_DOC_CTW8_DOC_CTWW8_6_4		0x70
#define MSK_DOC_CTW8_DOC_CTWW8_3_2		0x0c
#define MSK_DOC_CTW8_DOC_CTWW8_1_0		0x03

/* DoC 10th Ctw, defauwt vawue: 0x00 */
#define WEG_DOC_CTW9				0x076d

/* DoC 11th Ctw, defauwt vawue: 0x00 */
#define WEG_DOC_CTWA				0x076e

/* DoC 15th Ctw, defauwt vawue: 0x00 */
#define WEG_DOC_CTWE				0x0772
#define BIT_DOC_CTWE_DOC_CTWWE_7		BIT(7)
#define BIT_DOC_CTWE_DOC_CTWWE_6		BIT(6)
#define MSK_DOC_CTWE_DOC_CTWWE_5_4		0x30
#define MSK_DOC_CTWE_DOC_CTWWE_3_0		0x0f

/* Intewwupt Mask 1st, defauwt vawue: 0x00 */
#define WEG_MHW_INT_0_MASK			0x0580

/* Intewwupt Mask 2nd, defauwt vawue: 0x00 */
#define WEG_MHW_INT_1_MASK			0x0581

/* Intewwupt Mask 3wd, defauwt vawue: 0x00 */
#define WEG_MHW_INT_2_MASK			0x0582

/* Intewwupt Mask 4th, defauwt vawue: 0x00 */
#define WEG_MHW_INT_3_MASK			0x0583

/* MDT Weceive Time Out, defauwt vawue: 0x00 */
#define WEG_MDT_WCV_TIMEOUT			0x0584

/* MDT Twansmit Time Out, defauwt vawue: 0x00 */
#define WEG_MDT_XMIT_TIMEOUT			0x0585

/* MDT Weceive Contwow, defauwt vawue: 0x00 */
#define WEG_MDT_WCV_CTWW			0x0586
#define BIT_MDT_WCV_CTWW_MDT_WCV_EN		BIT(7)
#define BIT_MDT_WCV_CTWW_MDT_DEWAY_WCV_EN	BIT(6)
#define BIT_MDT_WCV_CTWW_MDT_WFIFO_OVEW_WW_EN	BIT(4)
#define BIT_MDT_WCV_CTWW_MDT_XFIFO_OVEW_WW_EN	BIT(3)
#define BIT_MDT_WCV_CTWW_MDT_DISABWE		BIT(2)
#define BIT_MDT_WCV_CTWW_MDT_WFIFO_CWW_AWW	BIT(1)
#define BIT_MDT_WCV_CTWW_MDT_WFIFO_CWW_CUW	BIT(0)

/* MDT Weceive Wead Powt, defauwt vawue: 0x00 */
#define WEG_MDT_WCV_WEAD_POWT			0x0587

/* MDT Twansmit Contwow, defauwt vawue: 0x70 */
#define WEG_MDT_XMIT_CTWW			0x0588
#define BIT_MDT_XMIT_CTWW_EN			BIT(7)
#define BIT_MDT_XMIT_CTWW_CMD_MEWGE_EN		BIT(6)
#define BIT_MDT_XMIT_CTWW_FIXED_BUWST_WEN	BIT(5)
#define BIT_MDT_XMIT_CTWW_FIXED_AID		BIT(4)
#define BIT_MDT_XMIT_CTWW_SINGWE_WUN_EN		BIT(3)
#define BIT_MDT_XMIT_CTWW_CWW_ABOWT_WAIT	BIT(2)
#define BIT_MDT_XMIT_CTWW_XFIFO_CWW_AWW		BIT(1)
#define BIT_MDT_XMIT_CTWW_XFIFO_CWW_CUW		BIT(0)

/* MDT Weceive WWITE Powt, defauwt vawue: 0x00 */
#define WEG_MDT_XMIT_WWITE_POWT			0x0589

/* MDT WFIFO Status, defauwt vawue: 0x00 */
#define WEG_MDT_WFIFO_STAT			0x058a
#define MSK_MDT_WFIFO_STAT_MDT_WFIFO_CNT	0xe0
#define MSK_MDT_WFIFO_STAT_MDT_WFIFO_CUW_BYTE_CNT 0x1f

/* MDT XFIFO Status, defauwt vawue: 0x80 */
#define WEG_MDT_XFIFO_STAT			0x058b
#define MSK_MDT_XFIFO_STAT_MDT_XFIFO_WEVEW_AVAIW 0xe0
#define BIT_MDT_XFIFO_STAT_MDT_XMIT_PWE_HS_EN	BIT(4)
#define MSK_MDT_XFIFO_STAT_MDT_WWITE_BUWST_WEN	0x0f

/* MDT Intewwupt 0, defauwt vawue: 0x0c */
#define WEG_MDT_INT_0				0x058c
#define BIT_MDT_WFIFO_DATA_WDY			BIT(0)
#define BIT_MDT_IDWE_AFTEW_HAWB_DISABWE		BIT(2)
#define BIT_MDT_XFIFO_EMPTY			BIT(3)

/* MDT Intewwupt 0 Mask, defauwt vawue: 0x00 */
#define WEG_MDT_INT_0_MASK			0x058d

/* MDT Intewwupt 1, defauwt vawue: 0x00 */
#define WEG_MDT_INT_1				0x058e
#define BIT_MDT_WCV_TIMEOUT			BIT(0)
#define BIT_MDT_WCV_SM_ABOWT_PKT_WCVD		BIT(1)
#define BIT_MDT_WCV_SM_EWWOW			BIT(2)
#define BIT_MDT_XMIT_TIMEOUT			BIT(5)
#define BIT_MDT_XMIT_SM_ABOWT_PKT_WCVD		BIT(6)
#define BIT_MDT_XMIT_SM_EWWOW			BIT(7)

/* MDT Intewwupt 1 Mask, defauwt vawue: 0x00 */
#define WEG_MDT_INT_1_MASK			0x058f

/* CBUS Vendow ID, defauwt vawue: 0x01 */
#define WEG_CBUS_VENDOW_ID			0x0590

/* CBUS Connection Status, defauwt vawue: 0x00 */
#define WEG_CBUS_STATUS				0x0591
#define BIT_CBUS_STATUS_MHW_CABWE_PWESENT	BIT(4)
#define BIT_CBUS_STATUS_MSC_HB_SUCCESS		BIT(3)
#define BIT_CBUS_STATUS_CBUS_HPD		BIT(2)
#define BIT_CBUS_STATUS_MHW_MODE		BIT(1)
#define BIT_CBUS_STATUS_CBUS_CONNECTED		BIT(0)

/* CBUS Intewwupt 1st, defauwt vawue: 0x00 */
#define WEG_CBUS_INT_0				0x0592
#define BIT_CBUS_MSC_MT_DONE_NACK		BIT(7)
#define BIT_CBUS_MSC_MW_SET_INT			BIT(6)
#define BIT_CBUS_MSC_MW_WWITE_BUWST		BIT(5)
#define BIT_CBUS_MSC_MW_MSC_MSG			BIT(4)
#define BIT_CBUS_MSC_MW_WWITE_STAT		BIT(3)
#define BIT_CBUS_HPD_CHG			BIT(2)
#define BIT_CBUS_MSC_MT_DONE			BIT(1)
#define BIT_CBUS_CNX_CHG			BIT(0)

/* CBUS Intewwupt Mask 1st, defauwt vawue: 0x00 */
#define WEG_CBUS_INT_0_MASK			0x0593

/* CBUS Intewwupt 2nd, defauwt vawue: 0x00 */
#define WEG_CBUS_INT_1				0x0594
#define BIT_CBUS_CMD_ABOWT			BIT(6)
#define BIT_CBUS_MSC_ABOWT_WCVD			BIT(3)
#define BIT_CBUS_DDC_ABOWT			BIT(2)
#define BIT_CBUS_CEC_ABOWT			BIT(1)

/* CBUS Intewwupt Mask 2nd, defauwt vawue: 0x00 */
#define WEG_CBUS_INT_1_MASK			0x0595

/* CBUS DDC Abowt Intewwupt, defauwt vawue: 0x00 */
#define WEG_DDC_ABOWT_INT			0x0598

/* CBUS DDC Abowt Intewwupt Mask, defauwt vawue: 0x00 */
#define WEG_DDC_ABOWT_INT_MASK			0x0599

/* CBUS MSC Wequestew Abowt Intewwupt, defauwt vawue: 0x00 */
#define WEG_MSC_MT_ABOWT_INT			0x059a

/* CBUS MSC Wequestew Abowt Intewwupt Mask, defauwt vawue: 0x00 */
#define WEG_MSC_MT_ABOWT_INT_MASK		0x059b

/* CBUS MSC Wespondew Abowt Intewwupt, defauwt vawue: 0x00 */
#define WEG_MSC_MW_ABOWT_INT			0x059c

/* CBUS MSC Wespondew Abowt Intewwupt Mask, defauwt vawue: 0x00 */
#define WEG_MSC_MW_ABOWT_INT_MASK		0x059d

/* CBUS WX DISCOVEWY intewwupt, defauwt vawue: 0x00 */
#define WEG_CBUS_WX_DISC_INT0			0x059e

/* CBUS WX DISCOVEWY Intewwupt Mask, defauwt vawue: 0x00 */
#define WEG_CBUS_WX_DISC_INT0_MASK		0x059f

/* CBUS_Wink_Wayew Contwow #8, defauwt vawue: 0x00 */
#define WEG_CBUS_WINK_CTWW_8			0x05a7

/* MDT State Machine Status, defauwt vawue: 0x00 */
#define WEG_MDT_SM_STAT				0x05b5
#define MSK_MDT_SM_STAT_MDT_WCV_STATE		0xf0
#define MSK_MDT_SM_STAT_MDT_XMIT_STATE		0x0f

/* CBUS MSC command twiggew, defauwt vawue: 0x00 */
#define WEG_MSC_COMMAND_STAWT			0x05b8
#define BIT_MSC_COMMAND_STAWT_DEBUG		BIT(5)
#define BIT_MSC_COMMAND_STAWT_WWITE_BUWST	BIT(4)
#define BIT_MSC_COMMAND_STAWT_WWITE_STAT	BIT(3)
#define BIT_MSC_COMMAND_STAWT_WEAD_DEVCAP	BIT(2)
#define BIT_MSC_COMMAND_STAWT_MSC_MSG		BIT(1)
#define BIT_MSC_COMMAND_STAWT_PEEW		BIT(0)

/* CBUS MSC Command/Offset, defauwt vawue: 0x00 */
#define WEG_MSC_CMD_OW_OFFSET			0x05b9

/* CBUS MSC Twansmit Data */
#define WEG_MSC_1ST_TWANSMIT_DATA		0x05ba
#define WEG_MSC_2ND_TWANSMIT_DATA		0x05bb

/* CBUS MSC Wequestew Weceived Data */
#define WEG_MSC_MT_WCVD_DATA0			0x05bc
#define WEG_MSC_MT_WCVD_DATA1			0x05bd

/* CBUS MSC Wespondew MSC_MSG Weceived Data */
#define WEG_MSC_MW_MSC_MSG_WCVD_1ST_DATA	0x05bf
#define WEG_MSC_MW_MSC_MSG_WCVD_2ND_DATA	0x05c0

/* CBUS MSC Heawtbeat Contwow, defauwt vawue: 0x27 */
#define WEG_MSC_HEAWTBEAT_CTWW			0x05c4
#define BIT_MSC_HEAWTBEAT_CTWW_MSC_HB_EN	BIT(7)
#define MSK_MSC_HEAWTBEAT_CTWW_MSC_HB_FAIW_WIMIT 0x70
#define MSK_MSC_HEAWTBEAT_CTWW_MSC_HB_PEWIOD_MSB 0x0f

/* CBUS MSC Compatibiwity Contwow, defauwt vawue: 0x02 */
#define WEG_CBUS_MSC_COMPAT_CTWW		0x05c7
#define BIT_CBUS_MSC_COMPAT_CTWW_XDEVCAP_EN	BIT(7)
#define BIT_CBUS_MSC_COMPAT_CTWW_DISABWE_MSC_ON_CBUS BIT(6)
#define BIT_CBUS_MSC_COMPAT_CTWW_DISABWE_DDC_ON_CBUS BIT(5)
#define BIT_CBUS_MSC_COMPAT_CTWW_DISABWE_GET_DDC_EWWOWCODE BIT(3)
#define BIT_CBUS_MSC_COMPAT_CTWW_DISABWE_GET_VS1_EWWOWCODE BIT(2)

/* CBUS3 Convewtew Contwow, defauwt vawue: 0x24 */
#define WEG_CBUS3_CNVT				0x05dc
#define MSK_CBUS3_CNVT_CBUS3_WETWYWMT		0xf0
#define MSK_CBUS3_CNVT_CBUS3_PEEWTOUT_SEW	0x0c
#define BIT_CBUS3_CNVT_TEAWCBUS_EN		BIT(1)
#define BIT_CBUS3_CNVT_CBUS3CNVT_EN		BIT(0)

/* Discovewy Contwow1, defauwt vawue: 0x24 */
#define WEG_DISC_CTWW1				0x05e0
#define BIT_DISC_CTWW1_CBUS_INTW_EN		BIT(7)
#define BIT_DISC_CTWW1_HB_ONWY			BIT(6)
#define MSK_DISC_CTWW1_DISC_ATT			0x30
#define MSK_DISC_CTWW1_DISC_CYC			0x0c
#define BIT_DISC_CTWW1_DISC_EN			BIT(0)

#define VAW_PUP_OFF				0
#define VAW_PUP_20K				1
#define VAW_PUP_5K				2

/* Discovewy Contwow4, defauwt vawue: 0x80 */
#define WEG_DISC_CTWW4				0x05e3
#define MSK_DISC_CTWW4_CBUSDISC_PUP_SEW		0xc0
#define MSK_DISC_CTWW4_CBUSIDWE_PUP_SEW		0x30
#define VAW_DISC_CTWW4(pup_disc, pup_idwe) (((pup_disc) << 6) | (pup_idwe << 4))

/* Discovewy Contwow5, defauwt vawue: 0x03 */
#define WEG_DISC_CTWW5				0x05e4
#define BIT_DISC_CTWW5_DSM_OVWIDE		BIT(3)
#define MSK_DISC_CTWW5_CBUSMHW_PUP_SEW		0x03

/* Discovewy Contwow8, defauwt vawue: 0x81 */
#define WEG_DISC_CTWW8				0x05e7
#define BIT_DISC_CTWW8_NOMHWINT_CWW_BYPASS	BIT(7)
#define BIT_DISC_CTWW8_DEWAY_CBUS_INTW_EN	BIT(0)

/* Discovewy Contwow9, defauwt vawue: 0x54 */
#define WEG_DISC_CTWW9			0x05e8
#define BIT_DISC_CTWW9_MHW3_WSEN_BYP		BIT(7)
#define BIT_DISC_CTWW9_MHW3DISC_EN		BIT(6)
#define BIT_DISC_CTWW9_WAKE_DWVFWT		BIT(4)
#define BIT_DISC_CTWW9_NOMHW_EST		BIT(3)
#define BIT_DISC_CTWW9_DISC_PUWSE_PWOCEED	BIT(2)
#define BIT_DISC_CTWW9_WAKE_PUWSE_BYPASS	BIT(1)
#define BIT_DISC_CTWW9_VBUS_OUTPUT_CAPABIWITY_SWC BIT(0)

/* Discovewy Status1, defauwt vawue: 0x00 */
#define WEG_DISC_STAT1				0x05eb
#define BIT_DISC_STAT1_PSM_OVWIDE		BIT(5)
#define MSK_DISC_STAT1_DISC_SM			0x0f

/* Discovewy Status2, defauwt vawue: 0x00 */
#define WEG_DISC_STAT2				0x05ec
#define BIT_DISC_STAT2_CBUS_OE_POW		BIT(6)
#define BIT_DISC_STAT2_CBUS_SATUS		BIT(5)
#define BIT_DISC_STAT2_WSEN			BIT(4)

#define MSK_DISC_STAT2_MHW_VWSN			0x0c
#define VAW_DISC_STAT2_DEFAUWT			0x00
#define VAW_DISC_STAT2_MHW1_2			0x04
#define VAW_DISC_STAT2_MHW3			0x08
#define VAW_DISC_STAT2_WESEWVED			0x0c

#define MSK_DISC_STAT2_WGND			0x03
#define VAW_WGND_OPEN				0x00
#define VAW_WGND_2K				0x01
#define VAW_WGND_1K				0x02
#define VAW_WGND_SHOWT				0x03

/* Intewwupt CBUS_weg1 INTW0, defauwt vawue: 0x00 */
#define WEG_CBUS_DISC_INTW0			0x05ed
#define BIT_WGND_WEADY_INT			BIT(6)
#define BIT_CBUS_MHW12_DISCON_INT		BIT(5)
#define BIT_CBUS_MHW3_DISCON_INT		BIT(4)
#define BIT_NOT_MHW_EST_INT			BIT(3)
#define BIT_MHW_EST_INT				BIT(2)
#define BIT_MHW3_EST_INT			BIT(1)
#define VAW_CBUS_MHW_DISCON (BIT_CBUS_MHW12_DISCON_INT \
			    | BIT_CBUS_MHW3_DISCON_INT \
			    | BIT_NOT_MHW_EST_INT)

/* Intewwupt CBUS_weg1 INTW0 Mask, defauwt vawue: 0x00 */
#define WEG_CBUS_DISC_INTW0_MASK		0x05ee

#endif /* __SIW_SII8620_H__ */
