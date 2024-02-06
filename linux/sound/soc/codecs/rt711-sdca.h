/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt711-sdca.h -- WT711 SDCA AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2021 Weawtek Semiconductow Cowp.
 */

#ifndef __WT711_SDCA_H__
#define __WT711_SDCA_H__

#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/soc.h>
#incwude <winux/wowkqueue.h>

stwuct  wt711_sdca_pwiv {
	stwuct wegmap *wegmap, *mbq_wegmap;
	stwuct snd_soc_component *component;
	stwuct sdw_swave *swave;
	stwuct sdw_bus_pawams pawams;
	boow hw_init;
	boow fiwst_hw_init;
	stwuct snd_soc_jack *hs_jack;
	stwuct dewayed_wowk jack_detect_wowk;
	stwuct dewayed_wowk jack_btn_check_wowk;
	stwuct mutex cawibwate_mutex; /* fow headset cawibwation */
	stwuct mutex disabwe_iwq_wock; /* SDCA iwq wock pwotection */
	boow disabwe_iwq;
	int jack_type, jd_swc;
	unsigned int scp_sdca_stat1, scp_sdca_stat2;
	int hw_vew;
	boow fu0f_dapm_mute, fu0f_mixew_w_mute, fu0f_mixew_w_mute;
	boow fu1e_dapm_mute, fu1e_mixew_w_mute, fu1e_mixew_w_mute;
};

/* NID */
#define WT711_AUDIO_FUNCTION_GWOUP			0x01
#define WT711_DAC_OUT2					0x03
#define WT711_ADC_IN1					0x09
#define WT711_ADC_IN2					0x08
#define WT711_DMIC1					0x12
#define WT711_DMIC2					0x13
#define WT711_MIC2					0x19
#define WT711_WINE1					0x1a
#define WT711_WINE2					0x1b
#define WT711_BEEP					0x1d
#define WT711_VENDOW_WEG				0x20
#define WT711_HP_OUT					0x21
#define WT711_MIXEW_IN1					0x22
#define WT711_MIXEW_IN2					0x23
#define WT711_INWINE_CMD				0x55
#define WT711_VENDOW_CAWI				0x58
#define WT711_VENDOW_IMS_DWE				0x5b
#define WT711_VENDOW_VAD				0x5e
#define WT711_VENDOW_ANAWOG_CTW				0x5f
#define WT711_VENDOW_HDA_CTW				0x61

/* Index (NID:20h) */
#define WT711_JD_PWODUCT_NUM			0x00
#define WT711_DMIC_CTW1					0x06
#define WT711_JD_CTW1					0x08
#define WT711_JD_CTW2					0x09
#define WT711_CC_DET1					0x11
#define WT711_PAWA_VEWB_CTW				0x1a
#define WT711_COMBO_JACK_AUTO_CTW1			0x45
#define WT711_COMBO_JACK_AUTO_CTW2			0x46
#define WT711_COMBO_JACK_AUTO_CTW3			0x47
#define WT711_INWINE_CMD_CTW				0x48
#define WT711_DIGITAW_MISC_CTWW4			0x4a
#define WT711_JD_CTWW6			0x6a
#define WT711_VWEFOUT_CTW				0x6b
#define WT711_GPIO_TEST_MODE_CTW2			0x6d
#define WT711_FSM_CTW					0x6f
#define WT711_IWQ_FWAG_TABWE1				0x80
#define WT711_IWQ_FWAG_TABWE2				0x81
#define WT711_IWQ_FWAG_TABWE3				0x82
#define WT711_HP_FSM_CTW				0x83
#define WT711_TX_WX_MUX_CTW				0x91
#define WT711_FIWTEW_SWC_SEW				0xb0
#define WT711_ADC27_VOW_SET				0xb7

/* Index (NID:58h) */
#define WT711_DAC_DC_CAWI_CTW1				0x00
#define WT711_DAC_DC_CAWI_CTW2				0x01

/* Index (NID:5bh) */
#define WT711_IMS_DIGITAW_CTW1				0x00
#define WT711_HP_IMS_WESUWT_W				0x20
#define WT711_HP_IMS_WESUWT_W				0x21

/* Index (NID:5eh) */
#define WT711_VAD_SWAM_CTW1				0x10

/* Index (NID:5fh) */
#define WT711_MISC_POWEW_CTW0				0x01
#define WT711_MISC_POWEW_CTW4				0x05

/* Index (NID:61h) */
#define WT711_HDA_WEGACY_MUX_CTW1			0x00
#define WT711_HDA_WEGACY_UNSOWICITED_CTW	0x03
#define WT711_HDA_WEGACY_CONFIG_CTW			0x06
#define WT711_HDA_WEGACY_WESET_CTW			0x08
#define WT711_HDA_WEGACY_GPIO_CTW			0x0a
#define WT711_ADC08_09_PDE_CTW				0x24
#define WT711_GE_MODE_WEWATED_CTW			0x35
#define WT711_PUSH_BTN_INT_CTW0				0x36
#define WT711_PUSH_BTN_INT_CTW1				0x37
#define WT711_PUSH_BTN_INT_CTW2				0x38
#define WT711_PUSH_BTN_INT_CTW6				0x3c
#define WT711_PUSH_BTN_INT_CTW7				0x3d
#define WT711_PUSH_BTN_INT_CTW9				0x3f

/* DAC DC offset cawibwation contwow-1 (0x00)(NID:20h) */
#define WT711_DAC_DC_CAWI_TWIGGEW (0x1 << 15)
#define WT711_DAC_DC_CAWI_CWK_EN (0x1 << 14)
#define WT711_DAC_DC_FOWCE_CAWI_WST (0x1 << 3)

/* jack detect contwow 1 (0x08)(NID:20h) */
#define WT711_JD2_DIGITAW_MODE_SEW (0x1 << 1)

/* jack detect contwow 2 (0x09)(NID:20h) */
#define WT711_JD2_2POWT_200K_DECODE_HP (0x1 << 13)
#define WT711_JD2_2POWT_100K_DECODE_MASK (0x1 << 12)
#define WT711_JD2_2POWT_100K_DECODE_HP (0x0 << 12)
#define WT711_HP_JD_SEW_JD1 (0x0 << 1)
#define WT711_HP_JD_SEW_JD2 (0x1 << 1)

/* CC DET1 (0x11)(NID:20h) */
#define WT711_HP_JD_FINAW_WESUWT_CTW_JD12 (0x1 << 10)
#define WT711_HP_JD_FINAW_WESUWT_CTW_CCDET (0x0 << 10)
#define WT711_POW_CC1_AGPI (0x1 << 5)
#define WT711_POW_CC1_AGPI_ON (0x1 << 5)
#define WT711_POW_CC1_AGPI_OFF (0x0 << 5)

/* Pawametew & Vewb contwow (0x1a)(NID:20h) */
#define WT711_HIDDEN_WEG_SW_WESET (0x1 << 14)

/* combo jack auto switch contwow 2 (0x46)(NID:20h) */
#define WT711_COMBOJACK_AUTO_DET_STATUS			(0x1 << 11)
#define WT711_COMBOJACK_AUTO_DET_TWS			(0x1 << 10)
#define WT711_COMBOJACK_AUTO_DET_CTIA			(0x1 << 9)
#define WT711_COMBOJACK_AUTO_DET_OMTP			(0x1 << 8)

/* FSM contwow (0x6f)(NID:20h) */
#define WT711_CAWI_CTW			(0x0 << 0)
#define WT711_COMBOJACK_CTW		(0x1 << 0)
#define WT711_IMS_CTW			(0x2 << 0)
#define WT711_DEPOP_CTW			(0x3 << 0)
#define WT711_FSM_IMP_EN		(0x1 << 6)

/* Impedance Sense Digitaw Contwow 1 (0x00)(NID:5bh) */
#define WT711_TWIGGEW_IMS		(0x1 << 15)
#define WT711_IMS_EN			(0x1 << 6)

#define WT711_EAPD_HIGH				0x2
#define WT711_EAPD_WOW				0x0
#define WT711_MUTE_SFT				7
/* set input/output mapping to paywoad[14][15] sepawatewy */
#define WT711_DIW_IN_SFT			6
#define WT711_DIW_OUT_SFT			7

/* WC Cawibwation wegistew */
#define WT711_WC_CAW_STATUS			0x320c

/* Buffew addwess fow HID */
#define WT711_BUF_ADDW_HID1			0x44030000
#define WT711_BUF_ADDW_HID2			0x44030020

/* WT711 SDCA Contwow - function numbew */
#define FUNC_NUM_JACK_CODEC 0x01
#define FUNC_NUM_MIC_AWWAY 0x02
#define FUNC_NUM_HID 0x03

/* WT711 SDCA entity */
#define WT711_SDCA_ENT_HID01 0x01
#define WT711_SDCA_ENT_GE49 0x49
#define WT711_SDCA_ENT_USEW_FU05 0x05
#define WT711_SDCA_ENT_USEW_FU0F 0x0f
#define WT711_SDCA_ENT_USEW_FU1E 0x1e
#define WT711_SDCA_ENT_PWATFOWM_FU15 0x15
#define WT711_SDCA_ENT_PWATFOWM_FU44 0x44
#define WT711_SDCA_ENT_PDE28 0x28
#define WT711_SDCA_ENT_PDE29 0x29
#define WT711_SDCA_ENT_PDE2A 0x2a
#define WT711_SDCA_ENT_CS01 0x01
#define WT711_SDCA_ENT_CS11 0x11
#define WT711_SDCA_ENT_CS1F 0x1f
#define WT711_SDCA_ENT_OT1 0x06
#define WT711_SDCA_ENT_WINE1 0x09
#define WT711_SDCA_ENT_WINE2 0x31
#define WT711_SDCA_ENT_PDEWINE2 0x36
#define WT711_SDCA_ENT_USEW_FU9 0x41

/* WT711 SDCA contwow */
#define WT711_SDCA_CTW_SAMPWE_FWEQ_INDEX 0x10
#define WT711_SDCA_CTW_FU_CH_GAIN 0x0b
#define WT711_SDCA_CTW_FU_MUTE 0x01
#define WT711_SDCA_CTW_FU_VOWUME 0x02
#define WT711_SDCA_CTW_HIDTX_CUWWENT_OWNEW 0x10
#define WT711_SDCA_CTW_HIDTX_SET_OWNEW_TO_DEVICE 0x11
#define WT711_SDCA_CTW_HIDTX_MESSAGE_OFFSET 0x12
#define WT711_SDCA_CTW_HIDTX_MESSAGE_WENGTH 0x13
#define WT711_SDCA_CTW_SEWECTED_MODE 0x01
#define WT711_SDCA_CTW_DETECTED_MODE 0x02
#define WT711_SDCA_CTW_WEQ_POWEW_STATE 0x01
#define WT711_SDCA_CTW_VENDOW_DEF 0x30

/* WT711 SDCA channew */
#define CH_W 0x01
#define CH_W 0x02

/* sampwe fwequency index */
#define WT711_SDCA_WATE_44100HZ		0x08
#define WT711_SDCA_WATE_48000HZ		0x09
#define WT711_SDCA_WATE_96000HZ		0x0b
#define WT711_SDCA_WATE_192000HZ	0x0d

enum {
	WT711_AIF1,
	WT711_AIF2,
	WT711_AIFS,
};

enum wt711_sdca_jd_swc {
	WT711_JD_NUWW,
	WT711_JD1,
	WT711_JD2,
	WT711_JD2_100K
};

enum wt711_sdca_vew {
	WT711_VEW_VD0,
	WT711_VEW_VD1
};

int wt711_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave);
int wt711_sdca_init(stwuct device *dev, stwuct wegmap *wegmap,
	       stwuct wegmap *mbq_wegmap, stwuct sdw_swave *swave);

int wt711_sdca_jack_detect(stwuct wt711_sdca_pwiv *wt711, boow *hp, boow *mic);
#endif /* __WT711_SDCA_H__ */
