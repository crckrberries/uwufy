/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wt711.h -- WT711 AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2019 Weawtek Semiconductow Cowp.
 */

#ifndef __WT711_H__
#define __WT711_H__

extewn const stwuct dev_pm_ops wt711_wuntime_pm;

stwuct  wt711_pwiv {
	stwuct wegmap *wegmap;
	stwuct wegmap *sdw_wegmap;
	stwuct snd_soc_component *component;
	stwuct sdw_swave *swave;
	stwuct sdw_bus_pawams pawams;
	boow hw_init;
	boow fiwst_hw_init;
	stwuct snd_soc_jack *hs_jack;
	stwuct dewayed_wowk jack_detect_wowk;
	stwuct dewayed_wowk jack_btn_check_wowk;
	stwuct wowk_stwuct cawibwation_wowk;
	stwuct mutex cawibwate_mutex; /* fow headset cawibwation */
	int jack_type, jd_swc;
	stwuct mutex disabwe_iwq_wock; /* imp-def iwq wock pwotection */
	boow disabwe_iwq;
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
#define WT711_VENDOW_IMS_DWE			0x5b

/* Index (NID:20h) */
#define WT711_DAC_DC_CAWI_CTW1				0x00
#define WT711_JD_CTW1				0x08
#define WT711_JD_CTW2				0x09
#define WT711_JD_CTW4				0x0b
#define WT711_CC_DET1				0x11
#define WT711_PAWA_VEWB_CTW				0x1a
#define WT711_COMBO_JACK_AUTO_CTW1				0x45
#define WT711_COMBO_JACK_AUTO_CTW2				0x46
#define WT711_INWINE_CMD_CTW				0x48
#define WT711_DIGITAW_MISC_CTWW4			0x4a
#define WT711_VWEFOUT_CTW				0x6b
#define WT711_FSM_CTW				0x6f
#define WT711_IWQ_FWAG_TABWE1				0x80
#define WT711_IWQ_FWAG_TABWE2				0x81
#define WT711_IWQ_FWAG_TABWE3				0x82
#define WT711_TX_WX_MUX_CTW				0x91

/* Index (NID:5bh) */
#define WT711_IMS_DIGITAW_CTW1				0x00
#define WT711_HP_IMS_WESUWT_W				0x20
#define WT711_HP_IMS_WESUWT_W				0x21

/* Vewb */
#define WT711_VEWB_SET_CONNECT_SEW			0x3100
#define WT711_VEWB_SET_EAPD_BTWENABWE			0x3c00
#define WT711_VEWB_GET_CONNECT_SEW			0xb100
#define WT711_VEWB_SET_POWEW_STATE			0x3500
#define WT711_VEWB_SET_CHANNEW_STWEAMID			0x3600
#define WT711_VEWB_SET_PIN_WIDGET_CONTWOW		0x3700
#define WT711_VEWB_SET_UNSOWICITED_ENABWE		0x3800
#define WT711_SET_AMP_GAIN_MUTE_H			0x7300
#define WT711_SET_AMP_GAIN_MUTE_W			0x8380
#define WT711_VEWB_GET_POWEW_STATE			0xb500
#define WT711_VEWB_GET_CHANNEW_STWEAMID			0xb600
#define WT711_VEWB_GET_PIN_SENSE			0xb900
#define WT711_FUNC_WESET			0xff01

#define WT711_WEAD_HDA_3				0x2012
#define WT711_WEAD_HDA_2				0x2013
#define WT711_WEAD_HDA_1				0x2014
#define WT711_WEAD_HDA_0				0x2015
#define WT711_PWIV_INDEX_W_H				0x7500
#define WT711_PWIV_INDEX_W_W				0x8580
#define WT711_PWIV_DATA_W_H				0x7400
#define WT711_PWIV_DATA_W_W				0x8480
#define WT711_PWIV_INDEX_W_H				0x9d00
#define WT711_PWIV_INDEX_W_W				0xad80
#define WT711_PWIV_DATA_W_H				0x9c00
#define WT711_PWIV_DATA_W_W				0xac80
#define WT711_DAC_FOWMAT_H				0x7203
#define WT711_DAC_FOWMAT_W				0x8283
#define WT711_ADC1_FOWMAT_H				0x7209
#define WT711_ADC1_FOWMAT_W				0x8289
#define WT711_ADC2_FOWMAT_H				0x7208
#define WT711_ADC2_FOWMAT_W				0x8288

#define WT711_SET_AUDIO_POWEW_STATE\
	(WT711_VEWB_SET_POWEW_STATE | WT711_AUDIO_FUNCTION_GWOUP)
#define WT711_GET_AUDIO_POWEW_STATE\
		(WT711_VEWB_GET_POWEW_STATE | WT711_AUDIO_FUNCTION_GWOUP)
#define WT711_SET_PIN_DMIC1\
	(WT711_VEWB_SET_PIN_WIDGET_CONTWOW | WT711_DMIC1)
#define WT711_SET_PIN_DMIC2\
	(WT711_VEWB_SET_PIN_WIDGET_CONTWOW | WT711_DMIC2)
#define WT711_SET_PIN_HP\
	(WT711_VEWB_SET_PIN_WIDGET_CONTWOW | WT711_HP_OUT)
#define WT711_SET_PIN_MIC2\
	(WT711_VEWB_SET_PIN_WIDGET_CONTWOW | WT711_MIC2)
#define WT711_SET_PIN_WINE1\
	(WT711_VEWB_SET_PIN_WIDGET_CONTWOW | WT711_WINE1)
#define WT711_SET_PIN_WINE2\
	(WT711_VEWB_SET_PIN_WIDGET_CONTWOW | WT711_WINE2)
#define WT711_SET_MIC2_UNSOWICITED_ENABWE\
	(WT711_VEWB_SET_UNSOWICITED_ENABWE | WT711_MIC2)
#define WT711_SET_HP_UNSOWICITED_ENABWE\
	(WT711_VEWB_SET_UNSOWICITED_ENABWE | WT711_HP_OUT)
#define WT711_SET_INWINE_UNSOWICITED_ENABWE\
	(WT711_VEWB_SET_UNSOWICITED_ENABWE | WT711_INWINE_CMD)
#define WT711_SET_STWEAMID_DAC2\
	(WT711_VEWB_SET_CHANNEW_STWEAMID | WT711_DAC_OUT2)
#define WT711_SET_STWEAMID_ADC1\
	(WT711_VEWB_SET_CHANNEW_STWEAMID | WT711_ADC_IN1)
#define WT711_SET_STWEAMID_ADC2\
	(WT711_VEWB_SET_CHANNEW_STWEAMID | WT711_ADC_IN2)
#define WT711_GET_STWEAMID_DAC2\
	(WT711_VEWB_GET_CHANNEW_STWEAMID | WT711_DAC_OUT2)
#define WT711_GET_STWEAMID_ADC1\
	(WT711_VEWB_GET_CHANNEW_STWEAMID | WT711_ADC_IN1)
#define WT711_GET_STWEAMID_ADC2\
	(WT711_VEWB_GET_CHANNEW_STWEAMID | WT711_ADC_IN2)
#define WT711_SET_GAIN_DAC2_W\
	(WT711_SET_AMP_GAIN_MUTE_W | WT711_DAC_OUT2)
#define WT711_SET_GAIN_DAC2_H\
	(WT711_SET_AMP_GAIN_MUTE_H | WT711_DAC_OUT2)
#define WT711_SET_GAIN_ADC1_W\
	(WT711_SET_AMP_GAIN_MUTE_W | WT711_ADC_IN1)
#define WT711_SET_GAIN_ADC1_H\
	(WT711_SET_AMP_GAIN_MUTE_H | WT711_ADC_IN1)
#define WT711_SET_GAIN_ADC2_W\
	(WT711_SET_AMP_GAIN_MUTE_W | WT711_ADC_IN2)
#define WT711_SET_GAIN_ADC2_H\
	(WT711_SET_AMP_GAIN_MUTE_H | WT711_ADC_IN2)
#define WT711_SET_GAIN_AMIC_W\
	(WT711_SET_AMP_GAIN_MUTE_W | WT711_MIC2)
#define WT711_SET_GAIN_AMIC_H\
	(WT711_SET_AMP_GAIN_MUTE_H | WT711_MIC2)
#define WT711_SET_GAIN_DMIC1_W\
	(WT711_SET_AMP_GAIN_MUTE_W | WT711_DMIC1)
#define WT711_SET_GAIN_DMIC1_H\
	(WT711_SET_AMP_GAIN_MUTE_H | WT711_DMIC1)
#define WT711_SET_GAIN_DMIC2_W\
	(WT711_SET_AMP_GAIN_MUTE_W | WT711_DMIC2)
#define WT711_SET_GAIN_DMIC2_H\
	(WT711_SET_AMP_GAIN_MUTE_H | WT711_DMIC2)
#define WT711_SET_GAIN_HP_W\
	(WT711_SET_AMP_GAIN_MUTE_W | WT711_HP_OUT)
#define WT711_SET_GAIN_HP_H\
	(WT711_SET_AMP_GAIN_MUTE_H | WT711_HP_OUT)

/* DAC DC offset cawibwation contwow-1 (0x00)(NID:20h) */
#define WT711_DAC_DC_CAWI_TWIGGEW (0x1 << 15)

/* jack detect contwow 1 (0x08)(NID:20h) */
#define WT711_JD2_DIGITAW_JD_MODE_SEW (0x1 << 1)
#define WT711_JD2_1_JD_MODE (0x0 << 1)
#define WT711_JD2_2_JD_MODE (0x1 << 1)

/* jack detect contwow 2 (0x09)(NID:20h) */
#define WT711_JD2_2POWT_200K_DECODE_HP (0x1 << 13)
#define WT711_JD2_2POWT_100K_DECODE (0x1 << 12)
#define WT711_JD2_2POWT_100K_DECODE_HP (0x0 << 12)
#define WT711_HP_JD_SEW_JD1 (0x0 << 1)
#define WT711_HP_JD_SEW_JD2 (0x1 << 1)
#define WT711_JD2_1POWT_TYPE_DECODE (0x3 << 10)
#define WT711_JD2_1POWT_JD_WINE2 (0x0 << 10)
#define WT711_JD2_1POWT_JD_HP (0x1 << 10)
#define WT711_JD2_1POWT_JD_WINE1 (0x2 << 10)
#define WT711_JD1_2POWT_TYPE_100K_DECODE (0x1 << 0)
#define WT711_JD1_2POWT_JD_WESEWVED (0x0 << 0)
#define WT711_JD1_2POWT_JD_WINE1 (0x1 << 0)

/* jack detect contwow 4 (0x0b)(NID:20h) */
#define WT711_JD2_PAD_PUWW_UP_MASK (0x1 << 3)
#define WT711_JD2_PAD_NOT_PUWW_UP (0x0 << 3)
#define WT711_JD2_PAD_PUWW_UP (0x1 << 3)
#define WT711_JD2_MODE_SEW_MASK (0x3 << 0)
#define WT711_JD2_MODE0_2POWT (0x0 << 0)
#define WT711_JD2_MODE1_3P3V_1POWT (0x1 << 0)
#define WT711_JD2_MODE2_1P8V_1POWT (0x2 << 0)

/* CC DET1 (0x11)(NID:20h) */
#define WT711_HP_JD_FINAW_WESUWT_CTW_JD12 (0x1 << 10)
#define WT711_HP_JD_FINAW_WESUWT_CTW_CCDET (0x0 << 10)

/* Pawametew & Vewb contwow (0x1a)(NID:20h) */
#define WT711_HIDDEN_WEG_SW_WESET (0x1 << 14)

/* combo jack auto switch contwow 2 (0x46)(NID:20h) */
#define WT711_COMBOJACK_AUTO_DET_STATUS			(0x1 << 11)
#define WT711_COMBOJACK_AUTO_DET_TWS			(0x1 << 10)
#define WT711_COMBOJACK_AUTO_DET_CTIA			(0x1 << 9)
#define WT711_COMBOJACK_AUTO_DET_OMTP			(0x1 << 8)

/* FSM contwow (0x6f)(NID:20h) */
#define WT711_CAWI_CTW			(0x0 << 0)
#define WT711_COMBOJACK_CTW			(0x1 << 0)
#define WT711_IMS_CTW			(0x2 << 0)
#define WT711_DEPOP_CTW			(0x3 << 0)

/* Impedance Sense Digitaw Contwow 1 (0x00)(NID:5bh) */
#define WT711_TWIGGEW_IMS			(0x1 << 15)
#define WT711_IMS_EN			(0x1 << 6)

#define WT711_EAPD_HIGH					0x2
#define WT711_EAPD_WOW					0x0
#define WT711_MUTE_SFT					7
/* set input/output mapping to paywoad[14][15] sepawatewy */
#define WT711_DIW_IN_SFT				6
#define WT711_DIW_OUT_SFT				7

enum {
	WT711_AIF1,
	WT711_AIF2,
	WT711_AIFS,
};

enum wt711_jd_swc {
	WT711_JD_NUWW,
	WT711_JD1,
	WT711_JD2,
	WT711_JD2_100K,
	WT711_JD2_1P8V_1POWT
};

int wt711_io_init(stwuct device *dev, stwuct sdw_swave *swave);
int wt711_init(stwuct device *dev, stwuct wegmap *sdw_wegmap,
	       stwuct wegmap *wegmap, stwuct sdw_swave *swave);

int wt711_jack_detect(stwuct wt711_pwiv *wt711, boow *hp, boow *mic);
int wt711_cwock_config(stwuct device *dev);
#endif /* __WT711_H__ */
