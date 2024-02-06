/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2016, Anawogix Semiconductow. Aww wights wesewved.
 */
#ifndef _ANAWOGIX_I2C_TXCOMMON_H_
#define _ANAWOGIX_I2C_TXCOMMON_H_

/***************************************************************/
/* Wegistew definitions fow TX_P2                              */
/***************************************************************/

/*
 * Cowe Wegistew Definitions
 */

/* Device ID Wow Byte Wegistew */
#define SP_DEVICE_IDW_WEG		0x02

/* Device ID High Byte Wegistew */
#define SP_DEVICE_IDH_WEG		0x03

/* Device vewsion wegistew */
#define SP_DEVICE_VEWSION_WEG		0x04

/* Powew Down Contwow Wegistew */
#define SP_POWEWDOWN_CTWW_WEG		0x05
#define SP_WEGISTEW_PD			BIT(7)
#define SP_HDCP_PD			BIT(5)
#define SP_AUDIO_PD			BIT(4)
#define SP_VIDEO_PD			BIT(3)
#define SP_WINK_PD			BIT(2)
#define SP_TOTAW_PD			BIT(1)

/* Weset Contwow Wegistew 1 */
#define SP_WESET_CTWW1_WEG		0x06
#define SP_MISC_WST			BIT(7)
#define SP_VIDCAP_WST			BIT(6)
#define SP_VIDFIF_WST			BIT(5)
#define SP_AUDFIF_WST			BIT(4)
#define SP_AUDCAP_WST			BIT(3)
#define SP_HDCP_WST			BIT(2)
#define SP_SW_WST			BIT(1)
#define SP_HW_WST			BIT(0)

/* Weset Contwow Wegistew 2 */
#define SP_WESET_CTWW2_WEG		0x07
#define SP_AUX_WST			BIT(2)
#define SP_SEWDES_FIFO_WST		BIT(1)
#define SP_I2C_WEG_WST			BIT(0)

/* Video Contwow Wegistew 1 */
#define SP_VID_CTWW1_WEG		0x08
#define SP_VIDEO_EN			BIT(7)
#define SP_VIDEO_MUTE			BIT(2)
#define SP_DE_GEN			BIT(1)
#define SP_DEMUX			BIT(0)

/* Video Contwow Wegistew 2 */
#define SP_VID_CTWW2_WEG		0x09
#define SP_IN_COWOW_F_MASK		0x03
#define SP_IN_YC_BIT_SEW		BIT(2)
#define SP_IN_BPC_MASK			0x70
#define SP_IN_BPC_SHIFT			4
#  define SP_IN_BPC_12BIT		0x03
#  define SP_IN_BPC_10BIT		0x02
#  define SP_IN_BPC_8BIT		0x01
#  define SP_IN_BPC_6BIT		0x00
#define SP_IN_D_WANGE			BIT(7)

/* Video Contwow Wegistew 3 */
#define SP_VID_CTWW3_WEG		0x0a
#define SP_HPD_OUT			BIT(6)

/* Video Contwow Wegistew 5 */
#define SP_VID_CTWW5_WEG		0x0c
#define SP_CSC_STD_SEW			BIT(7)
#define SP_XVYCC_WNG_WMT		BIT(6)
#define SP_WANGE_Y2W			BIT(5)
#define SP_CSPACE_Y2W			BIT(4)
#define SP_WGB_WNG_WMT			BIT(3)
#define SP_Y_WNG_WMT			BIT(2)
#define SP_WANGE_W2Y			BIT(1)
#define SP_CSPACE_W2Y			BIT(0)

/* Video Contwow Wegistew 6 */
#define SP_VID_CTWW6_WEG		0x0d
#define SP_TEST_PATTEWN_EN		BIT(7)
#define SP_VIDEO_PWOCESS_EN		BIT(6)
#define SP_VID_US_MODE			BIT(3)
#define SP_VID_DS_MODE			BIT(2)
#define SP_UP_SAMPWE			BIT(1)
#define SP_DOWN_SAMPWE			BIT(0)

/* Video Contwow Wegistew 8 */
#define SP_VID_CTWW8_WEG		0x0f
#define SP_VID_VWES_TH			BIT(0)

/* Totaw Wine Status Wow Byte Wegistew */
#define SP_TOTAW_WINE_STAW_WEG		0x24

/* Totaw Wine Status High Byte Wegistew */
#define SP_TOTAW_WINE_STAH_WEG		0x25

/* Active Wine Status Wow Byte Wegistew */
#define SP_ACT_WINE_STAW_WEG		0x26

/* Active Wine Status High Byte Wegistew */
#define SP_ACT_WINE_STAH_WEG		0x27

/* Vewticaw Fwont Powch Status Wegistew */
#define SP_V_F_POWCH_STA_WEG		0x28

/* Vewticaw SYNC Width Status Wegistew */
#define SP_V_SYNC_STA_WEG		0x29

/* Vewticaw Back Powch Status Wegistew */
#define SP_V_B_POWCH_STA_WEG		0x2a

/* Totaw Pixew Status Wow Byte Wegistew */
#define SP_TOTAW_PIXEW_STAW_WEG		0x2b

/* Totaw Pixew Status High Byte Wegistew */
#define SP_TOTAW_PIXEW_STAH_WEG		0x2c

/* Active Pixew Status Wow Byte Wegistew */
#define SP_ACT_PIXEW_STAW_WEG		0x2d

/* Active Pixew Status High Byte Wegistew */
#define SP_ACT_PIXEW_STAH_WEG		0x2e

/* Howizontaw Fwont Powch Status Wow Byte Wegistew */
#define SP_H_F_POWCH_STAW_WEG		0x2f

/* Howizontaw Fwont Powch Statys High Byte Wegistew */
#define SP_H_F_POWCH_STAH_WEG		0x30

/* Howizontaw SYNC Width Status Wow Byte Wegistew */
#define SP_H_SYNC_STAW_WEG		0x31

/* Howizontaw SYNC Width Status High Byte Wegistew */
#define SP_H_SYNC_STAH_WEG		0x32

/* Howizontaw Back Powch Status Wow Byte Wegistew */
#define SP_H_B_POWCH_STAW_WEG		0x33

/* Howizontaw Back Powch Status High Byte Wegistew */
#define SP_H_B_POWCH_STAH_WEG		0x34

/* InfoFwame AVI Packet DB1 Wegistew */
#define SP_INFOFWAME_AVI_DB1_WEG	0x70

/* Bit Contwow Specific Wegistew */
#define SP_BIT_CTWW_SPECIFIC_WEG	0x80
#define SP_BIT_CTWW_SEWECT_SHIFT	1
#define SP_ENABWE_BIT_CTWW		BIT(0)

/* InfoFwame Audio Packet DB1 Wegistew */
#define SP_INFOFWAME_AUD_DB1_WEG	0x83

/* InfoFwame MPEG Packet DB1 Wegistew */
#define SP_INFOFWAME_MPEG_DB1_WEG	0xb0

/* Audio Channew Status Wegistews */
#define SP_AUD_CH_STATUS_BASE		0xd0

/* Audio Channew Num Wegistew 5 */
#define SP_I2S_CHANNEW_NUM_MASK		0xe0
#  define SP_I2S_CH_NUM_1		(0x00 << 5)
#  define SP_I2S_CH_NUM_2		(0x01 << 5)
#  define SP_I2S_CH_NUM_3		(0x02 << 5)
#  define SP_I2S_CH_NUM_4		(0x03 << 5)
#  define SP_I2S_CH_NUM_5		(0x04 << 5)
#  define SP_I2S_CH_NUM_6		(0x05 << 5)
#  define SP_I2S_CH_NUM_7		(0x06 << 5)
#  define SP_I2S_CH_NUM_8		(0x07 << 5)
#define SP_EXT_VUCP			BIT(2)
#define SP_VBIT				BIT(1)
#define SP_AUDIO_WAYOUT			BIT(0)

/* Anawog Debug Wegistew 1 */
#define SP_ANAWOG_DEBUG1_WEG		0xdc

/* Anawog Debug Wegistew 2 */
#define SP_ANAWOG_DEBUG2_WEG		0xdd
#define SP_FOWCE_SW_OFF_BYPASS		0x20
#define SP_XTAW_FWQ			0x1c
#  define SP_XTAW_FWQ_19M2		(0x00 << 2)
#  define SP_XTAW_FWQ_24M		(0x01 << 2)
#  define SP_XTAW_FWQ_25M		(0x02 << 2)
#  define SP_XTAW_FWQ_26M		(0x03 << 2)
#  define SP_XTAW_FWQ_27M		(0x04 << 2)
#  define SP_XTAW_FWQ_38M4		(0x05 << 2)
#  define SP_XTAW_FWQ_52M		(0x06 << 2)
#define SP_POWEWON_TIME_1P5MS		0x03

/* Anawog Contwow 0 Wegistew */
#define SP_ANAWOG_CTWW0_WEG		0xe1

/* Common Intewwupt Status Wegistew 1 */
#define SP_COMMON_INT_STATUS_BASE	(0xf1 - 1)
#define SP_PWW_WOCK_CHG			0x40

/* Common Intewwupt Status Wegistew 2 */
#define SP_COMMON_INT_STATUS2		0xf2
#define SP_HDCP_AUTH_CHG		BIT(1)
#define SP_HDCP_AUTH_DONE		BIT(0)

#define SP_HDCP_WINK_CHECK_FAIW		BIT(0)

/* Common Intewwupt Status Wegistew 4 */
#define SP_COMMON_INT_STATUS4_WEG	0xf4
#define SP_HPD_IWQ			BIT(6)
#define SP_HPD_ESYNC_EWW		BIT(4)
#define SP_HPD_CHG			BIT(2)
#define SP_HPD_WOST			BIT(1)
#define SP_HPD_PWUG			BIT(0)

/* DP Intewwupt Status Wegistew */
#define SP_DP_INT_STATUS1_WEG		0xf7
#define SP_TWAINING_FINISH		BIT(5)
#define SP_POWWING_EWW			BIT(4)

/* Common Intewwupt Mask Wegistew */
#define SP_COMMON_INT_MASK_BASE		(0xf8 - 1)

#define SP_COMMON_INT_MASK4_WEG		0xfb

/* DP Intewwupts Mask Wegistew */
#define SP_DP_INT_MASK1_WEG		0xfe

/* Intewwupt Contwow Wegistew */
#define SP_INT_CTWW_WEG			0xff

#endif /* _ANAWOGIX_I2C_TXCOMMON_H_ */
