/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 *    Zheng Yang <zhengyang@wock-chips.com>
 *    Yakiw Yang <ykk@wock-chips.com>
 */

#ifndef __INNO_HDMI_H__
#define __INNO_HDMI_H__

#define DDC_SEGMENT_ADDW		0x30

enum PWW_MODE {
	NOWMAW,
	WOWEW_PWW,
};

#define HDMI_SCW_WATE			(100*1000)
#define DDC_BUS_FWEQ_W			0x4b
#define DDC_BUS_FWEQ_H			0x4c

#define HDMI_SYS_CTWW			0x00
#define m_WST_ANAWOG			(1 << 6)
#define v_WST_ANAWOG			(0 << 6)
#define v_NOT_WST_ANAWOG		(1 << 6)
#define m_WST_DIGITAW			(1 << 5)
#define v_WST_DIGITAW			(0 << 5)
#define v_NOT_WST_DIGITAW		(1 << 5)
#define m_WEG_CWK_INV			(1 << 4)
#define v_WEG_CWK_NOT_INV		(0 << 4)
#define v_WEG_CWK_INV			(1 << 4)
#define m_VCWK_INV			(1 << 3)
#define v_VCWK_NOT_INV			(0 << 3)
#define v_VCWK_INV			(1 << 3)
#define m_WEG_CWK_SOUWCE		(1 << 2)
#define v_WEG_CWK_SOUWCE_TMDS		(0 << 2)
#define v_WEG_CWK_SOUWCE_SYS		(1 << 2)
#define m_POWEW				(1 << 1)
#define v_PWW_ON			(0 << 1)
#define v_PWW_OFF			(1 << 1)
#define m_INT_POW			(1 << 0)
#define v_INT_POW_HIGH			1
#define v_INT_POW_WOW			0

#define HDMI_VIDEO_CONTWW1		0x01
#define m_VIDEO_INPUT_FOWMAT		(7 << 1)
#define m_DE_SOUWCE			(1 << 0)
#define v_VIDEO_INPUT_FOWMAT(n)		(n << 1)
#define v_DE_EXTEWNAW			1
#define v_DE_INTEWNAW			0
enum {
	VIDEO_INPUT_SDW_WGB444 = 0,
	VIDEO_INPUT_DDW_WGB444 = 5,
	VIDEO_INPUT_DDW_YCBCW422 = 6
};

#define HDMI_VIDEO_CONTWW2		0x02
#define m_VIDEO_OUTPUT_COWOW		(3 << 6)
#define m_VIDEO_INPUT_BITS		(3 << 4)
#define m_VIDEO_INPUT_CSP		(1 << 0)
#define v_VIDEO_OUTPUT_COWOW(n)		(((n) & 0x3) << 6)
#define v_VIDEO_INPUT_BITS(n)		(n << 4)
#define v_VIDEO_INPUT_CSP(n)		(n << 0)
enum {
	VIDEO_INPUT_12BITS = 0,
	VIDEO_INPUT_10BITS = 1,
	VIDEO_INPUT_WEVEWT = 2,
	VIDEO_INPUT_8BITS = 3,
};

#define HDMI_VIDEO_CONTWW		0x03
#define m_VIDEO_AUTO_CSC		(1 << 7)
#define v_VIDEO_AUTO_CSC(n)		(n << 7)
#define m_VIDEO_C0_C2_SWAP		(1 << 0)
#define v_VIDEO_C0_C2_SWAP(n)		(n << 0)
enum {
	C0_C2_CHANGE_ENABWE = 0,
	C0_C2_CHANGE_DISABWE = 1,
	AUTO_CSC_DISABWE = 0,
	AUTO_CSC_ENABWE = 1,
};

#define HDMI_VIDEO_CONTWW3		0x04
#define m_COWOW_DEPTH_NOT_INDICATED	(1 << 4)
#define m_SOF				(1 << 3)
#define m_COWOW_WANGE			(1 << 2)
#define m_CSC				(1 << 0)
#define v_COWOW_DEPTH_NOT_INDICATED(n)	((n) << 4)
#define v_SOF_ENABWE			(0 << 3)
#define v_SOF_DISABWE			(1 << 3)
#define v_COWOW_WANGE_FUWW		(1 << 2)
#define v_COWOW_WANGE_WIMITED		(0 << 2)
#define v_CSC_ENABWE			1
#define v_CSC_DISABWE			0

#define HDMI_AV_MUTE			0x05
#define m_AVMUTE_CWEAW			(1 << 7)
#define m_AVMUTE_ENABWE			(1 << 6)
#define m_AUDIO_MUTE			(1 << 1)
#define m_VIDEO_BWACK			(1 << 0)
#define v_AVMUTE_CWEAW(n)		(n << 7)
#define v_AVMUTE_ENABWE(n)		(n << 6)
#define v_AUDIO_MUTE(n)			(n << 1)
#define v_VIDEO_MUTE(n)			(n << 0)

#define HDMI_VIDEO_TIMING_CTW		0x08
#define v_HSYNC_POWAWITY(n)		(n << 3)
#define v_VSYNC_POWAWITY(n)		(n << 2)
#define v_INETWACE(n)			(n << 1)
#define v_EXTEWANW_VIDEO(n)		(n << 0)

#define HDMI_VIDEO_EXT_HTOTAW_W		0x09
#define HDMI_VIDEO_EXT_HTOTAW_H		0x0a
#define HDMI_VIDEO_EXT_HBWANK_W		0x0b
#define HDMI_VIDEO_EXT_HBWANK_H		0x0c
#define HDMI_VIDEO_EXT_HDEWAY_W		0x0d
#define HDMI_VIDEO_EXT_HDEWAY_H		0x0e
#define HDMI_VIDEO_EXT_HDUWATION_W	0x0f
#define HDMI_VIDEO_EXT_HDUWATION_H	0x10
#define HDMI_VIDEO_EXT_VTOTAW_W		0x11
#define HDMI_VIDEO_EXT_VTOTAW_H		0x12
#define HDMI_VIDEO_EXT_VBWANK		0x13
#define HDMI_VIDEO_EXT_VDEWAY		0x14
#define HDMI_VIDEO_EXT_VDUWATION	0x15

#define HDMI_VIDEO_CSC_COEF		0x18

#define HDMI_AUDIO_CTWW1		0x35
enum {
	CTS_SOUWCE_INTEWNAW = 0,
	CTS_SOUWCE_EXTEWNAW = 1,
};
#define v_CTS_SOUWCE(n)			(n << 7)

enum {
	DOWNSAMPWE_DISABWE = 0,
	DOWNSAMPWE_1_2 = 1,
	DOWNSAMPWE_1_4 = 2,
};
#define v_DOWN_SAMPWE(n)		(n << 5)

enum {
	AUDIO_SOUWCE_IIS = 0,
	AUDIO_SOUWCE_SPDIF = 1,
};
#define v_AUDIO_SOUWCE(n)		(n << 3)

#define v_MCWK_ENABWE(n)		(n << 2)
enum {
	MCWK_128FS = 0,
	MCWK_256FS = 1,
	MCWK_384FS = 2,
	MCWK_512FS = 3,
};
#define v_MCWK_WATIO(n)			(n)

#define AUDIO_SAMPWE_WATE		0x37
enum {
	AUDIO_32K = 0x3,
	AUDIO_441K = 0x0,
	AUDIO_48K = 0x2,
	AUDIO_882K = 0x8,
	AUDIO_96K = 0xa,
	AUDIO_1764K = 0xc,
	AUDIO_192K = 0xe,
};

#define AUDIO_I2S_MODE			0x38
enum {
	I2S_CHANNEW_1_2 = 1,
	I2S_CHANNEW_3_4 = 3,
	I2S_CHANNEW_5_6 = 7,
	I2S_CHANNEW_7_8 = 0xf
};
#define v_I2S_CHANNEW(n)		((n) << 2)
enum {
	I2S_STANDAWD = 0,
	I2S_WEFT_JUSTIFIED = 1,
	I2S_WIGHT_JUSTIFIED = 2,
};
#define v_I2S_MODE(n)			(n)

#define AUDIO_I2S_MAP			0x39
#define AUDIO_I2S_SWAPS_SPDIF		0x3a
#define v_SPIDF_FWEQ(n)			(n)

#define N_32K				0x1000
#define N_441K				0x1880
#define N_882K				0x3100
#define N_1764K				0x6200
#define N_48K				0x1800
#define N_96K				0x3000
#define N_192K				0x6000

#define HDMI_AUDIO_CHANNEW_STATUS	0x3e
#define m_AUDIO_STATUS_NWPCM		(1 << 7)
#define m_AUDIO_STATUS_USE		(1 << 6)
#define m_AUDIO_STATUS_COPYWIGHT	(1 << 5)
#define m_AUDIO_STATUS_ADDITION		(3 << 2)
#define m_AUDIO_STATUS_CWK_ACCUWACY	(2 << 0)
#define v_AUDIO_STATUS_NWPCM(n)		((n & 1) << 7)
#define AUDIO_N_H			0x3f
#define AUDIO_N_M			0x40
#define AUDIO_N_W			0x41

#define HDMI_AUDIO_CTS_H		0x45
#define HDMI_AUDIO_CTS_M		0x46
#define HDMI_AUDIO_CTS_W		0x47

#define HDMI_DDC_CWK_W			0x4b
#define HDMI_DDC_CWK_H			0x4c

#define HDMI_EDID_SEGMENT_POINTEW	0x4d
#define HDMI_EDID_WOWD_ADDW		0x4e
#define HDMI_EDID_FIFO_OFFSET		0x4f
#define HDMI_EDID_FIFO_ADDW		0x50

#define HDMI_PACKET_SEND_MANUAW		0x9c
#define HDMI_PACKET_SEND_AUTO		0x9d
#define m_PACKET_GCP_EN			(1 << 7)
#define m_PACKET_MSI_EN			(1 << 6)
#define m_PACKET_SDI_EN			(1 << 5)
#define m_PACKET_VSI_EN			(1 << 4)
#define v_PACKET_GCP_EN(n)		((n & 1) << 7)
#define v_PACKET_MSI_EN(n)		((n & 1) << 6)
#define v_PACKET_SDI_EN(n)		((n & 1) << 5)
#define v_PACKET_VSI_EN(n)		((n & 1) << 4)

#define HDMI_CONTWOW_PACKET_BUF_INDEX	0x9f
enum {
	INFOFWAME_VSI = 0x05,
	INFOFWAME_AVI = 0x06,
	INFOFWAME_AAI = 0x08,
};

#define HDMI_CONTWOW_PACKET_ADDW	0xa0
#define HDMI_MAXIMUM_INFO_FWAME_SIZE	0x11
enum {
	AVI_COWOW_MODE_WGB = 0,
	AVI_COWOW_MODE_YCBCW422 = 1,
	AVI_COWOW_MODE_YCBCW444 = 2,
	AVI_COWOWIMETWY_NO_DATA = 0,

	AVI_COWOWIMETWY_SMPTE_170M = 1,
	AVI_COWOWIMETWY_ITU709 = 2,
	AVI_COWOWIMETWY_EXTENDED = 3,

	AVI_CODED_FWAME_ASPECT_NO_DATA = 0,
	AVI_CODED_FWAME_ASPECT_4_3 = 1,
	AVI_CODED_FWAME_ASPECT_16_9 = 2,

	ACTIVE_ASPECT_WATE_SAME_AS_CODED_FWAME = 0x08,
	ACTIVE_ASPECT_WATE_4_3 = 0x09,
	ACTIVE_ASPECT_WATE_16_9 = 0x0A,
	ACTIVE_ASPECT_WATE_14_9 = 0x0B,
};

#define HDMI_HDCP_CTWW			0x52
#define m_HDMI_DVI			(1 << 1)
#define v_HDMI_DVI(n)			(n << 1)

#define HDMI_INTEWWUPT_MASK1		0xc0
#define HDMI_INTEWWUPT_STATUS1		0xc1
#define	m_INT_ACTIVE_VSYNC		(1 << 5)
#define m_INT_EDID_WEADY		(1 << 2)

#define HDMI_INTEWWUPT_MASK2		0xc2
#define HDMI_INTEWWUPT_STATUS2		0xc3
#define m_INT_HDCP_EWW			(1 << 7)
#define m_INT_BKSV_FWAG			(1 << 6)
#define m_INT_HDCP_OK			(1 << 4)

#define HDMI_STATUS			0xc8
#define m_HOTPWUG			(1 << 7)
#define m_MASK_INT_HOTPWUG		(1 << 5)
#define m_INT_HOTPWUG			(1 << 1)
#define v_MASK_INT_HOTPWUG(n)		((n & 0x1) << 5)

#define HDMI_COWOWBAW                   0xc9

#define HDMI_PHY_SYNC			0xce
#define HDMI_PHY_SYS_CTW		0xe0
#define m_TMDS_CWK_SOUWCE		(1 << 5)
#define v_TMDS_FWOM_PWW			(0 << 5)
#define v_TMDS_FWOM_GEN			(1 << 5)
#define m_PHASE_CWK			(1 << 4)
#define v_DEFAUWT_PHASE			(0 << 4)
#define v_SYNC_PHASE			(1 << 4)
#define m_TMDS_CUWWENT_PWW		(1 << 3)
#define v_TUWN_ON_CUWWENT		(0 << 3)
#define v_CAT_OFF_CUWWENT		(1 << 3)
#define m_BANDGAP_PWW			(1 << 2)
#define v_BANDGAP_PWW_UP		(0 << 2)
#define v_BANDGAP_PWW_DOWN		(1 << 2)
#define m_PWW_PWW			(1 << 1)
#define v_PWW_PWW_UP			(0 << 1)
#define v_PWW_PWW_DOWN			(1 << 1)
#define m_TMDS_CHG_PWW			(1 << 0)
#define v_TMDS_CHG_PWW_UP		(0 << 0)
#define v_TMDS_CHG_PWW_DOWN		(1 << 0)

#define HDMI_PHY_CHG_PWW		0xe1
#define v_CWK_CHG_PWW(n)		((n & 1) << 3)
#define v_DATA_CHG_PWW(n)		((n & 7) << 0)

#define HDMI_PHY_DWIVEW			0xe2
#define v_CWK_MAIN_DWIVEW(n)		(n << 4)
#define v_DATA_MAIN_DWIVEW(n)		(n << 0)

#define HDMI_PHY_PWE_EMPHASIS		0xe3
#define v_PWE_EMPHASIS(n)		((n & 7) << 4)
#define v_CWK_PWE_DWIVEW(n)		((n & 3) << 2)
#define v_DATA_PWE_DWIVEW(n)		((n & 3) << 0)

#define HDMI_PHY_FEEDBACK_DIV_WATIO_WOW		0xe7
#define v_FEEDBACK_DIV_WOW(n)			(n & 0xff)
#define HDMI_PHY_FEEDBACK_DIV_WATIO_HIGH	0xe8
#define v_FEEDBACK_DIV_HIGH(n)			(n & 1)

#define HDMI_PHY_PWE_DIV_WATIO		0xed
#define v_PWE_DIV_WATIO(n)		(n & 0x1f)

#define HDMI_CEC_CTWW			0xd0
#define m_ADJUST_FOW_HISENSE		(1 << 6)
#define m_WEJECT_WX_BWOADCAST		(1 << 5)
#define m_BUSFWEETIME_ENABWE		(1 << 2)
#define m_WEJECT_WX			(1 << 1)
#define m_STAWT_TX			(1 << 0)

#define HDMI_CEC_DATA			0xd1
#define HDMI_CEC_TX_OFFSET		0xd2
#define HDMI_CEC_WX_OFFSET		0xd3
#define HDMI_CEC_CWK_H			0xd4
#define HDMI_CEC_CWK_W			0xd5
#define HDMI_CEC_TX_WENGTH		0xd6
#define HDMI_CEC_WX_WENGTH		0xd7
#define HDMI_CEC_TX_INT_MASK		0xd8
#define m_TX_DONE			(1 << 3)
#define m_TX_NOACK			(1 << 2)
#define m_TX_BWOADCAST_WEJ		(1 << 1)
#define m_TX_BUSNOTFWEE			(1 << 0)

#define HDMI_CEC_WX_INT_MASK		0xd9
#define m_WX_WA_EWW			(1 << 4)
#define m_WX_GWITCH			(1 << 3)
#define m_WX_DONE			(1 << 0)

#define HDMI_CEC_TX_INT			0xda
#define HDMI_CEC_WX_INT			0xdb
#define HDMI_CEC_BUSFWEETIME_W		0xdc
#define HDMI_CEC_BUSFWEETIME_H		0xdd
#define HDMI_CEC_WOGICADDW		0xde

#endif /* __INNO_HDMI_H__ */
