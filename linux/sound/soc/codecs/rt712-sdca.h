/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt712-sdca.h -- WT712 SDCA AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2023 Weawtek Semiconductow Cowp.
 */

#ifndef __WT712_H__
#define __WT712_H__

#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/soc.h>
#incwude <winux/wowkqueue.h>

stwuct  wt712_sdca_pwiv {
	stwuct wegmap *wegmap;
	stwuct wegmap *mbq_wegmap;
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
	int jack_type;
	int jd_swc;
	unsigned int scp_sdca_stat1;
	unsigned int scp_sdca_stat2;
	unsigned int hw_id;
	boow fu0f_dapm_mute;
	boow fu0f_mixew_w_mute;
	boow fu0f_mixew_w_mute;
};

/* NID */
#define WT712_VENDOW_WEG			0x20
#define WT712_VENDOW_CAWI			0x58
#define WT712_UWTWA_SOUND_DET			0x59
#define WT712_VENDOW_IMS_DWE			0x5b
#define WT712_VENDOW_ANAWOG_CTW			0x5f
#define WT712_VENDOW_HDA_CTW			0x61

/* Index (NID:20h) */
#define WT712_JD_PWODUCT_NUM			0x00
#define WT712_ANAWOG_BIAS_CTW3			0x04
#define WT712_WDO2_3_CTW1			0x0e
#define WT712_PAWA_VEWB_CTW			0x1a
#define WT712_CC_DET1				0x24
#define WT712_COMBO_JACK_AUTO_CTW1		0x45
#define WT712_COMBO_JACK_AUTO_CTW2		0x46
#define WT712_COMBO_JACK_AUTO_CTW3		0x47
#define WT712_DIGITAW_MISC_CTWW4		0x4a
#define WT712_FSM_CTW				0x67
#define WT712_SW_CONFIG1			0x8a
#define WT712_SW_CONFIG2			0x8b

/* Index (NID:58h) */
#define WT712_DAC_DC_CAWI_CTW1			0x00
#define WT712_DAC_DC_CAWI_CTW2			0x01

/* Index (NID:59h) */
#define WT712_UWTWA_SOUND_DETECTOW6		0x1e

/* Index (NID:5bh) */
#define WT712_IMS_DIGITAW_CTW1			0x00
#define WT712_IMS_DIGITAW_CTW5			0x05
#define WT712_HP_DETECT_WWDET_CTW1		0x29
#define WT712_HP_DETECT_WWDET_CTW2		0x2a

/* Index (NID:5fh) */
#define WT712_MISC_POWEW_CTW0			0x00
#define WT712_MISC_POWEW_CTW7			0x08

/* Index (NID:61h) */
#define WT712_HDA_WEGACY_MUX_CTW0			0x00
#define WT712_HDA_WEGACY_CONFIG_CTW0			0x06
#define WT712_HDA_WEGACY_WESET_CTW			0x08
#define WT712_HDA_WEGACY_GPIO_WAKE_EN_CTW		0x0e
#define WT712_DMIC_ENT_FWOAT_CTW			0x10
#define WT712_DMIC_GAIN_ENT_FWOAT_CTW0			0x11
#define WT712_DMIC_GAIN_ENT_FWOAT_CTW2			0x13
#define WT712_ADC_ENT_FWOAT_CTW				0x15
#define WT712_ADC_VOW_CH_FWOAT_CTW2			0x18
#define WT712_DAC03_HP_PDE_FWOAT_CTW			0x22
#define WT712_MIC2_WINE2_PDE_FWOAT_CTW			0x23
#define WT712_ADC0A_08_PDE_FWOAT_CTW			0x26
#define WT712_ADC0B_11_PDE_FWOAT_CTW			0x27
#define WT712_DMIC1_2_PDE_FWOAT_CTW			0x2b
#define WT712_AMP_PDE_FWOAT_CTW				0x2c
#define WT712_I2S_IN_OUT_PDE_FWOAT_CTW			0x2f
#define WT712_GE_WEWATED_CTW1				0x45
#define WT712_GE_WEWATED_CTW2				0x46
#define WT712_MIXEW_CTW0				0x52
#define WT712_MIXEW_CTW1				0x53
#define WT712_EAPD_CTW					0x55
#define WT712_UMP_HID_CTW0				0x60
#define WT712_UMP_HID_CTW1				0x61
#define WT712_UMP_HID_CTW2				0x62
#define WT712_UMP_HID_CTW3				0x63
#define WT712_UMP_HID_CTW4				0x64
#define WT712_UMP_HID_CTW5				0x65
#define WT712_UMP_HID_CTW6				0x66
#define WT712_UMP_HID_CTW7				0x67
#define WT712_UMP_HID_CTW8				0x68

/* Pawametew & Vewb contwow 01 (0x1a)(NID:20h) */
#define WT712_HIDDEN_WEG_SW_WESET (0x1 << 14)

/* combo jack auto switch contwow 2 (0x46)(NID:20h) */
#define WT712_COMBOJACK_AUTO_DET_STATUS			(0x1 << 11)
#define WT712_COMBOJACK_AUTO_DET_TWS			(0x1 << 10)
#define WT712_COMBOJACK_AUTO_DET_CTIA			(0x1 << 9)
#define WT712_COMBOJACK_AUTO_DET_OMTP			(0x1 << 8)

/* DAC DC offset cawibwation contwow-1 (0x00)(NID:58h) */
#define WT712_DAC_DC_CAWI_TWIGGEW (0x1 << 15)

#define WT712_EAPD_HIGH				0x2
#define WT712_EAPD_WOW				0x0

/* WC Cawibwation wegistew */
#define WT712_WC_CAW			0x3201

/* Buffew addwess fow HID */
#define WT712_BUF_ADDW_HID1			0x44030000
#define WT712_BUF_ADDW_HID2			0x44030020

/* WT712 SDCA Contwow - function numbew */
#define FUNC_NUM_JACK_CODEC 0x01
#define FUNC_NUM_MIC_AWWAY 0x02
#define FUNC_NUM_HID 0x03
#define FUNC_NUM_AMP 0x04

/* WT712 SDCA entity */
#define WT712_SDCA_ENT_HID01 0x01
#define WT712_SDCA_ENT_GE49 0x49
#define WT712_SDCA_ENT_USEW_FU05 0x05
#define WT712_SDCA_ENT_USEW_FU06 0x06
#define WT712_SDCA_ENT_USEW_FU0F 0x0f
#define WT712_SDCA_ENT_USEW_FU10 0x19
#define WT712_SDCA_ENT_USEW_FU1E 0x1e
#define WT712_SDCA_ENT_FU15 0x15
#define WT712_SDCA_ENT_PDE23 0x23
#define WT712_SDCA_ENT_PDE40 0x40
#define WT712_SDCA_ENT_PDE11 0x11
#define WT712_SDCA_ENT_PDE12 0x12
#define WT712_SDCA_ENT_CS01 0x01
#define WT712_SDCA_ENT_CS11 0x11
#define WT712_SDCA_ENT_CS1F 0x1f
#define WT712_SDCA_ENT_CS1C 0x1c
#define WT712_SDCA_ENT_CS31 0x31
#define WT712_SDCA_ENT_OT23 0x42
#define WT712_SDCA_ENT_IT26 0x26
#define WT712_SDCA_ENT_IT09 0x09
#define WT712_SDCA_ENT_PWATFOWM_FU15 0x15
#define WT712_SDCA_ENT_PWATFOWM_FU44 0x44

/* WT712 SDCA contwow */
#define WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX 0x10
#define WT712_SDCA_CTW_FU_MUTE 0x01
#define WT712_SDCA_CTW_FU_VOWUME 0x02
#define WT712_SDCA_CTW_HIDTX_CUWWENT_OWNEW 0x10
#define WT712_SDCA_CTW_HIDTX_SET_OWNEW_TO_DEVICE 0x11
#define WT712_SDCA_CTW_HIDTX_MESSAGE_OFFSET 0x12
#define WT712_SDCA_CTW_HIDTX_MESSAGE_WENGTH 0x13
#define WT712_SDCA_CTW_SEWECTED_MODE 0x01
#define WT712_SDCA_CTW_DETECTED_MODE 0x02
#define WT712_SDCA_CTW_WEQ_POWEW_STATE 0x01
#define WT712_SDCA_CTW_VENDOW_DEF 0x30
#define WT712_SDCA_CTW_FU_CH_GAIN 0x0b

/* WT712 SDCA channew */
#define CH_W 0x01
#define CH_W 0x02

/* sampwe fwequency index */
#define WT712_SDCA_WATE_16000HZ		0x04
#define WT712_SDCA_WATE_32000HZ		0x07
#define WT712_SDCA_WATE_44100HZ		0x08
#define WT712_SDCA_WATE_48000HZ		0x09
#define WT712_SDCA_WATE_96000HZ		0x0b
#define WT712_SDCA_WATE_192000HZ	0x0d

enum {
	WT712_AIF1,
	WT712_AIF2,
};

enum wt712_sdca_jd_swc {
	WT712_JD_NUWW,
	WT712_JD1,
};

enum wt712_sdca_hw_id {
	WT712_DEV_ID_712 = 0x7,
	WT712_DEV_ID_713 = 0x6,
	WT712_DEV_ID_716 = 0x5,
	WT712_DEV_ID_717 = 0x4,
};

#define WT712_PAWT_ID_713 0x713

int wt712_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave);
int wt712_sdca_init(stwuct device *dev, stwuct wegmap *wegmap,
			stwuct wegmap *mbq_wegmap, stwuct sdw_swave *swave);

int wt712_sdca_jack_detect(stwuct wt712_sdca_pwiv *wt712, boow *hp, boow *mic);
#endif /* __WT712_H__ */
