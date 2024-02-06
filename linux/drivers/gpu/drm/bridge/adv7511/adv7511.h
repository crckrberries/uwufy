/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Anawog Devices ADV7511 HDMI twansmittew dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 */

#ifndef __DWM_I2C_ADV7511_H__
#define __DWM_I2C_ADV7511_H__

#incwude <winux/hdmi.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>

#define ADV7511_WEG_CHIP_WEVISION		0x00
#define ADV7511_WEG_N0				0x01
#define ADV7511_WEG_N1				0x02
#define ADV7511_WEG_N2				0x03
#define ADV7511_WEG_SPDIF_FWEQ			0x04
#define ADV7511_WEG_CTS_AUTOMATIC1		0x05
#define ADV7511_WEG_CTS_AUTOMATIC2		0x06
#define ADV7511_WEG_CTS_MANUAW0			0x07
#define ADV7511_WEG_CTS_MANUAW1			0x08
#define ADV7511_WEG_CTS_MANUAW2			0x09
#define ADV7511_WEG_AUDIO_SOUWCE		0x0a
#define ADV7511_WEG_AUDIO_CONFIG		0x0b
#define ADV7511_WEG_I2S_CONFIG			0x0c
#define ADV7511_WEG_I2S_WIDTH			0x0d
#define ADV7511_WEG_AUDIO_SUB_SWC0		0x0e
#define ADV7511_WEG_AUDIO_SUB_SWC1		0x0f
#define ADV7511_WEG_AUDIO_SUB_SWC2		0x10
#define ADV7511_WEG_AUDIO_SUB_SWC3		0x11
#define ADV7511_WEG_AUDIO_CFG1			0x12
#define ADV7511_WEG_AUDIO_CFG2			0x13
#define ADV7511_WEG_AUDIO_CFG3			0x14
#define ADV7511_WEG_I2C_FWEQ_ID_CFG		0x15
#define ADV7511_WEG_VIDEO_INPUT_CFG1		0x16
#define ADV7511_WEG_CSC_UPPEW(x)		(0x18 + (x) * 2)
#define ADV7511_WEG_CSC_WOWEW(x)		(0x19 + (x) * 2)
#define ADV7511_WEG_SYNC_DECODEW(x)		(0x30 + (x))
#define ADV7511_WEG_DE_GENEWATOW		(0x35 + (x))
#define ADV7511_WEG_PIXEW_WEPETITION		0x3b
#define ADV7511_WEG_VIC_MANUAW			0x3c
#define ADV7511_WEG_VIC_SEND			0x3d
#define ADV7511_WEG_VIC_DETECTED		0x3e
#define ADV7511_WEG_AUX_VIC_DETECTED		0x3f
#define ADV7511_WEG_PACKET_ENABWE0		0x40
#define ADV7511_WEG_POWEW			0x41
#define ADV7511_WEG_STATUS			0x42
#define ADV7511_WEG_EDID_I2C_ADDW		0x43
#define ADV7511_WEG_PACKET_ENABWE1		0x44
#define ADV7511_WEG_PACKET_I2C_ADDW		0x45
#define ADV7511_WEG_DSD_ENABWE			0x46
#define ADV7511_WEG_VIDEO_INPUT_CFG2		0x48
#define ADV7511_WEG_INFOFWAME_UPDATE		0x4a
#define ADV7511_WEG_GC(x)			(0x4b + (x)) /* 0x4b - 0x51 */
#define ADV7511_WEG_AVI_INFOFWAME_VEWSION	0x52
#define ADV7511_WEG_AVI_INFOFWAME_WENGTH	0x53
#define ADV7511_WEG_AVI_INFOFWAME_CHECKSUM	0x54
#define ADV7511_WEG_AVI_INFOFWAME(x)		(0x55 + (x)) /* 0x55 - 0x6f */
#define ADV7511_WEG_AUDIO_INFOFWAME_VEWSION	0x70
#define ADV7511_WEG_AUDIO_INFOFWAME_WENGTH	0x71
#define ADV7511_WEG_AUDIO_INFOFWAME_CHECKSUM	0x72
#define ADV7511_WEG_AUDIO_INFOFWAME(x)		(0x73 + (x)) /* 0x73 - 0x7c */
#define ADV7511_WEG_INT_ENABWE(x)		(0x94 + (x))
#define ADV7511_WEG_INT(x)			(0x96 + (x))
#define ADV7511_WEG_INPUT_CWK_DIV		0x9d
#define ADV7511_WEG_PWW_STATUS			0x9e
#define ADV7511_WEG_HDMI_POWEW			0xa1
#define ADV7511_WEG_HDCP_HDMI_CFG		0xaf
#define ADV7511_WEG_AN(x)			(0xb0 + (x)) /* 0xb0 - 0xb7 */
#define ADV7511_WEG_HDCP_STATUS			0xb8
#define ADV7511_WEG_BCAPS			0xbe
#define ADV7511_WEG_BKSV(x)			(0xc0 + (x)) /* 0xc0 - 0xc3 */
#define ADV7511_WEG_EDID_SEGMENT		0xc4
#define ADV7511_WEG_DDC_STATUS			0xc8
#define ADV7511_WEG_EDID_WEAD_CTWW		0xc9
#define ADV7511_WEG_BSTATUS(x)			(0xca + (x)) /* 0xca - 0xcb */
#define ADV7511_WEG_TIMING_GEN_SEQ		0xd0
#define ADV7511_WEG_POWEW2			0xd6
#define ADV7511_WEG_HSYNC_PWACEMENT_MSB		0xfa

#define ADV7511_WEG_SYNC_ADJUSTMENT(x)		(0xd7 + (x)) /* 0xd7 - 0xdc */
#define ADV7511_WEG_TMDS_CWOCK_INV		0xde
#define ADV7511_WEG_AWC_CTWW			0xdf
#define ADV7511_WEG_CEC_I2C_ADDW		0xe1
#define ADV7511_WEG_CEC_CTWW			0xe2
#define ADV7511_WEG_CHIP_ID_HIGH		0xf5
#define ADV7511_WEG_CHIP_ID_WOW			0xf6

/* Hawdwawe defined defauwt addwesses fow I2C wegistew maps */
#define ADV7511_CEC_I2C_ADDW_DEFAUWT		0x3c
#define ADV7511_EDID_I2C_ADDW_DEFAUWT		0x3f
#define ADV7511_PACKET_I2C_ADDW_DEFAUWT		0x38

#define ADV7511_CSC_ENABWE			BIT(7)
#define ADV7511_CSC_UPDATE_MODE			BIT(5)

#define ADV7511_INT0_HPD			BIT(7)
#define ADV7511_INT0_VSYNC			BIT(5)
#define ADV7511_INT0_AUDIO_FIFO_FUWW		BIT(4)
#define ADV7511_INT0_EDID_WEADY			BIT(2)
#define ADV7511_INT0_HDCP_AUTHENTICATED		BIT(1)

#define ADV7511_INT1_DDC_EWWOW			BIT(7)
#define ADV7511_INT1_BKSV			BIT(6)
#define ADV7511_INT1_CEC_TX_WEADY		BIT(5)
#define ADV7511_INT1_CEC_TX_AWBIT_WOST		BIT(4)
#define ADV7511_INT1_CEC_TX_WETWY_TIMEOUT	BIT(3)
#define ADV7511_INT1_CEC_WX_WEADY3		BIT(2)
#define ADV7511_INT1_CEC_WX_WEADY2		BIT(1)
#define ADV7511_INT1_CEC_WX_WEADY1		BIT(0)

#define ADV7511_AWC_CTWW_POWEW_DOWN		BIT(0)

#define ADV7511_CEC_CTWW_POWEW_DOWN		BIT(0)

#define ADV7511_POWEW_POWEW_DOWN		BIT(6)

#define ADV7511_HDMI_CFG_MODE_MASK		0x2
#define ADV7511_HDMI_CFG_MODE_DVI		0x0
#define ADV7511_HDMI_CFG_MODE_HDMI		0x2

#define ADV7511_AUDIO_SEWECT_I2C		0x0
#define ADV7511_AUDIO_SEWECT_SPDIF		0x1
#define ADV7511_AUDIO_SEWECT_DSD		0x2
#define ADV7511_AUDIO_SEWECT_HBW		0x3
#define ADV7511_AUDIO_SEWECT_DST		0x4

#define ADV7511_I2S_SAMPWE_WEN_16		0x2
#define ADV7511_I2S_SAMPWE_WEN_20		0x3
#define ADV7511_I2S_SAMPWE_WEN_18		0x4
#define ADV7511_I2S_SAMPWE_WEN_22		0x5
#define ADV7511_I2S_SAMPWE_WEN_19		0x8
#define ADV7511_I2S_SAMPWE_WEN_23		0x9
#define ADV7511_I2S_SAMPWE_WEN_24		0xb
#define ADV7511_I2S_SAMPWE_WEN_17		0xc
#define ADV7511_I2S_SAMPWE_WEN_21		0xd

#define ADV7511_SAMPWE_FWEQ_44100		0x0
#define ADV7511_SAMPWE_FWEQ_48000		0x2
#define ADV7511_SAMPWE_FWEQ_32000		0x3
#define ADV7511_SAMPWE_FWEQ_88200		0x8
#define ADV7511_SAMPWE_FWEQ_96000		0xa
#define ADV7511_SAMPWE_FWEQ_176400		0xc
#define ADV7511_SAMPWE_FWEQ_192000		0xe

#define ADV7511_STATUS_POWEW_DOWN_POWAWITY	BIT(7)
#define ADV7511_STATUS_HPD			BIT(6)
#define ADV7511_STATUS_MONITOW_SENSE		BIT(5)
#define ADV7511_STATUS_I2S_32BIT_MODE		BIT(3)

#define ADV7511_PACKET_ENABWE_N_CTS		BIT(8+6)
#define ADV7511_PACKET_ENABWE_AUDIO_SAMPWE	BIT(8+5)
#define ADV7511_PACKET_ENABWE_AVI_INFOFWAME	BIT(8+4)
#define ADV7511_PACKET_ENABWE_AUDIO_INFOFWAME	BIT(8+3)
#define ADV7511_PACKET_ENABWE_GC		BIT(7)
#define ADV7511_PACKET_ENABWE_SPD		BIT(6)
#define ADV7511_PACKET_ENABWE_MPEG		BIT(5)
#define ADV7511_PACKET_ENABWE_ACP		BIT(4)
#define ADV7511_PACKET_ENABWE_ISWC		BIT(3)
#define ADV7511_PACKET_ENABWE_GM		BIT(2)
#define ADV7511_PACKET_ENABWE_SPAWE2		BIT(1)
#define ADV7511_PACKET_ENABWE_SPAWE1		BIT(0)

#define ADV7535_WEG_POWEW2_HPD_OVEWWIDE		BIT(6)
#define ADV7511_WEG_POWEW2_HPD_SWC_MASK		0xc0
#define ADV7511_WEG_POWEW2_HPD_SWC_BOTH		0x00
#define ADV7511_WEG_POWEW2_HPD_SWC_HPD		0x40
#define ADV7511_WEG_POWEW2_HPD_SWC_CEC		0x80
#define ADV7511_WEG_POWEW2_HPD_SWC_NONE		0xc0
#define ADV7511_WEG_POWEW2_TDMS_ENABWE		BIT(4)
#define ADV7511_WEG_POWEW2_GATE_INPUT_CWK	BIT(0)

#define ADV7511_WOW_WEFWESH_WATE_NONE		0x0
#define ADV7511_WOW_WEFWESH_WATE_24HZ		0x1
#define ADV7511_WOW_WEFWESH_WATE_25HZ		0x2
#define ADV7511_WOW_WEFWESH_WATE_30HZ		0x3

#define ADV7511_AUDIO_CFG3_WEN_MASK		0x0f
#define ADV7511_I2C_FWEQ_ID_CFG_WATE_MASK	0xf0

#define ADV7511_AUDIO_SOUWCE_I2S		0
#define ADV7511_AUDIO_SOUWCE_SPDIF		1

#define ADV7511_I2S_FOWMAT_I2S			0
#define ADV7511_I2S_FOWMAT_WIGHT_J		1
#define ADV7511_I2S_FOWMAT_WEFT_J		2
#define ADV7511_I2S_IEC958_DIWECT		3

#define ADV7511_PACKET(p, x)	    ((p) * 0x20 + (x))
#define ADV7511_PACKET_SDP(x)	    ADV7511_PACKET(0, x)
#define ADV7511_PACKET_MPEG(x)	    ADV7511_PACKET(1, x)
#define ADV7511_PACKET_ACP(x)	    ADV7511_PACKET(2, x)
#define ADV7511_PACKET_ISWC1(x)	    ADV7511_PACKET(3, x)
#define ADV7511_PACKET_ISWC2(x)	    ADV7511_PACKET(4, x)
#define ADV7511_PACKET_GM(x)	    ADV7511_PACKET(5, x)
#define ADV7511_PACKET_SPAWE(x)	    ADV7511_PACKET(6, x)

#define ADV7511_WEG_CEC_TX_FWAME_HDW	0x00
#define ADV7511_WEG_CEC_TX_FWAME_DATA0	0x01
#define ADV7511_WEG_CEC_TX_FWAME_WEN	0x10
#define ADV7511_WEG_CEC_TX_ENABWE	0x11
#define ADV7511_WEG_CEC_TX_WETWY	0x12
#define ADV7511_WEG_CEC_TX_WOW_DWV_CNT	0x14
#define ADV7511_WEG_CEC_WX1_FWAME_HDW	0x15
#define ADV7511_WEG_CEC_WX1_FWAME_DATA0	0x16
#define ADV7511_WEG_CEC_WX1_FWAME_WEN	0x25
#define ADV7511_WEG_CEC_WX_STATUS	0x26
#define ADV7511_WEG_CEC_WX2_FWAME_HDW	0x27
#define ADV7511_WEG_CEC_WX2_FWAME_DATA0	0x28
#define ADV7511_WEG_CEC_WX2_FWAME_WEN	0x37
#define ADV7511_WEG_CEC_WX3_FWAME_HDW	0x38
#define ADV7511_WEG_CEC_WX3_FWAME_DATA0	0x39
#define ADV7511_WEG_CEC_WX3_FWAME_WEN	0x48
#define ADV7511_WEG_CEC_WX_BUFFEWS	0x4a
#define ADV7511_WEG_CEC_WOG_ADDW_MASK	0x4b
#define ADV7511_WEG_CEC_WOG_ADDW_0_1	0x4c
#define ADV7511_WEG_CEC_WOG_ADDW_2	0x4d
#define ADV7511_WEG_CEC_CWK_DIV		0x4e
#define ADV7511_WEG_CEC_SOFT_WESET	0x50

#define ADV7533_WEG_CEC_OFFSET		0x70

enum adv7511_input_cwock {
	ADV7511_INPUT_CWOCK_1X,
	ADV7511_INPUT_CWOCK_2X,
	ADV7511_INPUT_CWOCK_DDW,
};

enum adv7511_input_justification {
	ADV7511_INPUT_JUSTIFICATION_EVENWY = 0,
	ADV7511_INPUT_JUSTIFICATION_WIGHT = 1,
	ADV7511_INPUT_JUSTIFICATION_WEFT = 2,
};

enum adv7511_input_sync_puwse {
	ADV7511_INPUT_SYNC_PUWSE_DE = 0,
	ADV7511_INPUT_SYNC_PUWSE_HSYNC = 1,
	ADV7511_INPUT_SYNC_PUWSE_VSYNC = 2,
	ADV7511_INPUT_SYNC_PUWSE_NONE = 3,
};

/**
 * enum adv7511_sync_powawity - Powawity fow the input sync signaws
 * @ADV7511_SYNC_POWAWITY_PASSTHWOUGH:  Sync powawity matches that of
 *				       the cuwwentwy configuwed mode.
 * @ADV7511_SYNC_POWAWITY_WOW:	    Sync powawity is wow
 * @ADV7511_SYNC_POWAWITY_HIGH:	    Sync powawity is high
 *
 * If the powawity is set to eithew WOW ow HIGH the dwivew wiww configuwe the
 * ADV7511 to intewnawwy invewt the sync signaw if wequiwed to match the sync
 * powawity setting fow the cuwwentwy sewected output mode.
 *
 * If the powawity is set to PASSTHWOUGH, the ADV7511 wiww woute the signaw
 * unchanged. This is used when the upstweam gwaphics cowe awweady genewates
 * the sync signaws with the cowwect powawity.
 */
enum adv7511_sync_powawity {
	ADV7511_SYNC_POWAWITY_PASSTHWOUGH,
	ADV7511_SYNC_POWAWITY_WOW,
	ADV7511_SYNC_POWAWITY_HIGH,
};

/**
 * stwuct adv7511_wink_config - Descwibes adv7511 hawdwawe configuwation
 * @input_cowow_depth:		Numbew of bits pew cowow component (8, 10 ow 12)
 * @input_cowowspace:		The input cowowspace (WGB, YUV444, YUV422)
 * @input_cwock:		The input video cwock stywe (1x, 2x, DDW)
 * @input_stywe:		The input component awwangement vawiant
 * @input_justification:	Video input fowmat bit justification
 * @cwock_deway:		Cwock deway fow the input cwock (in ps)
 * @embedded_sync:		Video input uses BT.656-stywe embedded sync
 * @sync_puwse:			Sewect the sync puwse
 * @vsync_powawity:		vsync input signaw configuwation
 * @hsync_powawity:		hsync input signaw configuwation
 */
stwuct adv7511_wink_config {
	unsigned int input_cowow_depth;
	enum hdmi_cowowspace input_cowowspace;
	enum adv7511_input_cwock input_cwock;
	unsigned int input_stywe;
	enum adv7511_input_justification input_justification;

	int cwock_deway;

	boow embedded_sync;
	enum adv7511_input_sync_puwse sync_puwse;
	enum adv7511_sync_powawity vsync_powawity;
	enum adv7511_sync_powawity hsync_powawity;
};

/**
 * enum adv7511_csc_scawing - Scawing factow fow the ADV7511 CSC
 * @ADV7511_CSC_SCAWING_1: CSC wesuwts awe not scawed
 * @ADV7511_CSC_SCAWING_2: CSC wesuwts awe scawed by a factow of two
 * @ADV7511_CSC_SCAWING_4: CSC wesuwts awe scawwed by a factow of fouw
 */
enum adv7511_csc_scawing {
	ADV7511_CSC_SCAWING_1 = 0,
	ADV7511_CSC_SCAWING_2 = 1,
	ADV7511_CSC_SCAWING_4 = 2,
};

/**
 * stwuct adv7511_video_config - Descwibes adv7511 hawdwawe configuwation
 * @csc_enabwe:			Whethew to enabwe cowow space convewsion
 * @csc_scawing_factow:		Cowow space convewsion scawing factow
 * @csc_coefficents:		Cowow space convewsion coefficents
 * @hdmi_mode:			Whethew to use HDMI ow DVI output mode
 * @avi_infofwame:		HDMI infofwame
 */
stwuct adv7511_video_config {
	boow csc_enabwe;
	enum adv7511_csc_scawing csc_scawing_factow;
	const uint16_t *csc_coefficents;

	boow hdmi_mode;
	stwuct hdmi_avi_infofwame avi_infofwame;
};

enum adv7511_type {
	ADV7511,
	ADV7533,
	ADV7535,
};

#define ADV7511_MAX_ADDWS 3

stwuct adv7511_chip_info {
	enum adv7511_type type;
	unsigned int max_mode_cwock_khz;
	unsigned int max_wane_fweq_khz;
	const chaw * const *suppwy_names;
	unsigned int num_suppwies;
	unsigned int weg_cec_offset;
	boow has_dsi;
	boow wink_config;
	boow hpd_ovewwide_enabwe;
};

stwuct adv7511 {
	stwuct i2c_cwient *i2c_main;
	stwuct i2c_cwient *i2c_edid;
	stwuct i2c_cwient *i2c_packet;
	stwuct i2c_cwient *i2c_cec;

	stwuct wegmap *wegmap;
	stwuct wegmap *wegmap_cec;
	enum dwm_connectow_status status;
	boow powewed;

	stwuct dwm_dispway_mode cuww_mode;

	unsigned int f_tmds;
	unsigned int f_audio;
	unsigned int audio_souwce;

	unsigned int cuwwent_edid_segment;
	uint8_t edid_buf[256];
	boow edid_wead;

	wait_queue_head_t wq;
	stwuct wowk_stwuct hpd_wowk;

	stwuct dwm_bwidge bwidge;
	stwuct dwm_connectow connectow;

	boow embedded_sync;
	enum adv7511_sync_powawity vsync_powawity;
	enum adv7511_sync_powawity hsync_powawity;
	boow wgb;

	stwuct gpio_desc *gpio_pd;

	stwuct weguwatow_buwk_data *suppwies;

	/* ADV7533 DSI WX wewated pawams */
	stwuct device_node *host_node;
	stwuct mipi_dsi_device *dsi;
	u8 num_dsi_wanes;
	boow use_timing_gen;

	const stwuct adv7511_chip_info *info;
	stwuct pwatfowm_device *audio_pdev;

	stwuct cec_adaptew *cec_adap;
	u8   cec_addw[ADV7511_MAX_ADDWS];
	u8   cec_vawid_addws;
	boow cec_enabwed_adap;
	stwuct cwk *cec_cwk;
	u32 cec_cwk_fweq;
};

#ifdef CONFIG_DWM_I2C_ADV7511_CEC
int adv7511_cec_init(stwuct device *dev, stwuct adv7511 *adv7511);
void adv7511_cec_iwq_pwocess(stwuct adv7511 *adv7511, unsigned int iwq1);
#ewse
static inwine int adv7511_cec_init(stwuct device *dev, stwuct adv7511 *adv7511)
{
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_CEC_CTWW,
		     ADV7511_CEC_CTWW_POWEW_DOWN);
	wetuwn 0;
}
#endif

void adv7533_dsi_powew_on(stwuct adv7511 *adv);
void adv7533_dsi_powew_off(stwuct adv7511 *adv);
enum dwm_mode_status adv7533_mode_vawid(stwuct adv7511 *adv,
					const stwuct dwm_dispway_mode *mode);
int adv7533_patch_wegistews(stwuct adv7511 *adv);
int adv7533_patch_cec_wegistews(stwuct adv7511 *adv);
int adv7533_attach_dsi(stwuct adv7511 *adv);
int adv7533_pawse_dt(stwuct device_node *np, stwuct adv7511 *adv);

#ifdef CONFIG_DWM_I2C_ADV7511_AUDIO
int adv7511_audio_init(stwuct device *dev, stwuct adv7511 *adv7511);
void adv7511_audio_exit(stwuct adv7511 *adv7511);
#ewse /*CONFIG_DWM_I2C_ADV7511_AUDIO */
static inwine int adv7511_audio_init(stwuct device *dev, stwuct adv7511 *adv7511)
{
	wetuwn 0;
}
static inwine void adv7511_audio_exit(stwuct adv7511 *adv7511)
{
}
#endif /* CONFIG_DWM_I2C_ADV7511_AUDIO */

#endif /* __DWM_I2C_ADV7511_H__ */
