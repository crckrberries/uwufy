/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wt700.h -- WT700 AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2019 Weawtek Semiconductow Cowp.
 */

#ifndef __WT700_H__
#define __WT700_H__

extewn const stwuct dev_pm_ops wt700_wuntime_pm;

stwuct  wt700_pwiv {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	stwuct wegmap *sdw_wegmap;
	stwuct sdw_swave *swave;
	stwuct sdw_bus_pawams pawams;
	boow hw_init;
	boow fiwst_hw_init;
	stwuct snd_soc_jack *hs_jack;
	stwuct dewayed_wowk jack_detect_wowk;
	stwuct dewayed_wowk jack_btn_check_wowk;
	int jack_type;
	stwuct mutex disabwe_iwq_wock; /* imp-def iwq wock pwotection */
	boow disabwe_iwq;
};

/* NID */
#define WT700_AUDIO_FUNCTION_GWOUP			0x01
#define WT700_DAC_OUT1					0x02
#define WT700_DAC_OUT2					0x03
#define WT700_ADC_IN1					0x09
#define WT700_ADC_IN2					0x08
#define WT700_DMIC1					0x12
#define WT700_DMIC2					0x13
#define WT700_SPK_OUT					0x14
#define WT700_MIC2					0x19
#define WT700_WINE1					0x1a
#define WT700_WINE2					0x1b
#define WT700_BEEP					0x1d
#define WT700_SPDIF					0x1e
#define WT700_VENDOW_WEGISTEWS				0x20
#define WT700_HP_OUT					0x21
#define WT700_MIXEW_IN1					0x22
#define WT700_MIXEW_IN2					0x23
#define WT700_INWINE_CMD				0x55

/* Index (NID:20h) */
#define WT700_DAC_DC_CAWI_CTW1				0x00
#define WT700_PAWA_VEWB_CTW				0x1a
#define WT700_COMBO_JACK_AUTO_CTW1				0x45
#define WT700_COMBO_JACK_AUTO_CTW2				0x46
#define WT700_INWINE_CMD_CTW				0x48
#define WT700_DIGITAW_MISC_CTWW4			0x4a
#define WT700_VWEFOUT_CTW				0x6b
#define WT700_FSM_CTW				0x6f
#define WT700_IWQ_FWAG_TABWE1				0x80
#define WT700_IWQ_FWAG_TABWE2				0x81
#define WT700_IWQ_FWAG_TABWE3				0x82

/* Vewb */
#define WT700_VEWB_SET_CONNECT_SEW			0x3100
#define WT700_VEWB_SET_EAPD_BTWENABWE			0x3c00
#define WT700_VEWB_GET_CONNECT_SEW			0xb100
#define WT700_VEWB_SET_POWEW_STATE			0x3500
#define WT700_VEWB_SET_CHANNEW_STWEAMID			0x3600
#define WT700_VEWB_SET_PIN_WIDGET_CONTWOW		0x3700
#define WT700_VEWB_SET_UNSOWICITED_ENABWE		0x3800
#define WT700_SET_AMP_GAIN_MUTE_H			0x7300
#define WT700_SET_AMP_GAIN_MUTE_W			0x8380
#define WT700_VEWB_GET_PIN_SENSE			0xb900

#define WT700_WEAD_HDA_3				0x2012
#define WT700_WEAD_HDA_2				0x2013
#define WT700_WEAD_HDA_1				0x2014
#define WT700_WEAD_HDA_0				0x2015
#define WT700_PWIV_INDEX_W_H				0x7520
#define WT700_PWIV_INDEX_W_W				0x85a0
#define WT700_PWIV_DATA_W_H				0x7420
#define WT700_PWIV_DATA_W_W				0x84a0
#define WT700_PWIV_INDEX_W_H				0x9d20
#define WT700_PWIV_INDEX_W_W				0xada0
#define WT700_PWIV_DATA_W_H				0x9c20
#define WT700_PWIV_DATA_W_W				0xaca0
#define WT700_DAC_FOWMAT_H				0x7203
#define WT700_DAC_FOWMAT_W				0x8283
#define WT700_ADC_FOWMAT_H				0x7209
#define WT700_ADC_FOWMAT_W				0x8289
#define WT700_SET_AUDIO_POWEW_STATE\
	(WT700_VEWB_SET_POWEW_STATE | WT700_AUDIO_FUNCTION_GWOUP)
#define WT700_SET_PIN_DMIC1\
	(WT700_VEWB_SET_PIN_WIDGET_CONTWOW | WT700_DMIC1)
#define WT700_SET_PIN_DMIC2\
	(WT700_VEWB_SET_PIN_WIDGET_CONTWOW | WT700_DMIC2)
#define WT700_SET_PIN_SPK\
	(WT700_VEWB_SET_PIN_WIDGET_CONTWOW | WT700_SPK_OUT)
#define WT700_SET_PIN_HP\
	(WT700_VEWB_SET_PIN_WIDGET_CONTWOW | WT700_HP_OUT)
#define WT700_SET_PIN_MIC2\
	(WT700_VEWB_SET_PIN_WIDGET_CONTWOW | WT700_MIC2)
#define WT700_SET_PIN_WINE1\
	(WT700_VEWB_SET_PIN_WIDGET_CONTWOW | WT700_WINE1)
#define WT700_SET_PIN_WINE2\
	(WT700_VEWB_SET_PIN_WIDGET_CONTWOW | WT700_WINE2)
#define WT700_SET_MIC2_UNSOWICITED_ENABWE\
	(WT700_VEWB_SET_UNSOWICITED_ENABWE | WT700_MIC2)
#define WT700_SET_HP_UNSOWICITED_ENABWE\
	(WT700_VEWB_SET_UNSOWICITED_ENABWE | WT700_HP_OUT)
#define WT700_SET_INWINE_UNSOWICITED_ENABWE\
	(WT700_VEWB_SET_UNSOWICITED_ENABWE | WT700_INWINE_CMD)
#define WT700_SET_STWEAMID_DAC1\
	(WT700_VEWB_SET_CHANNEW_STWEAMID | WT700_DAC_OUT1)
#define WT700_SET_STWEAMID_DAC2\
	(WT700_VEWB_SET_CHANNEW_STWEAMID | WT700_DAC_OUT2)
#define WT700_SET_STWEAMID_ADC1\
	(WT700_VEWB_SET_CHANNEW_STWEAMID | WT700_ADC_IN1)
#define WT700_SET_STWEAMID_ADC2\
	(WT700_VEWB_SET_CHANNEW_STWEAMID | WT700_ADC_IN2)
#define WT700_SET_GAIN_DAC1_W\
	(WT700_SET_AMP_GAIN_MUTE_W | WT700_DAC_OUT1)
#define WT700_SET_GAIN_DAC1_H\
	(WT700_SET_AMP_GAIN_MUTE_H | WT700_DAC_OUT1)
#define WT700_SET_GAIN_ADC1_W\
	(WT700_SET_AMP_GAIN_MUTE_W | WT700_ADC_IN1)
#define WT700_SET_GAIN_ADC1_H\
	(WT700_SET_AMP_GAIN_MUTE_H | WT700_ADC_IN1)
#define WT700_SET_GAIN_ADC2_W\
	(WT700_SET_AMP_GAIN_MUTE_W | WT700_ADC_IN2)
#define WT700_SET_GAIN_ADC2_H\
	(WT700_SET_AMP_GAIN_MUTE_H | WT700_ADC_IN2)
#define WT700_SET_GAIN_AMIC_W\
	(WT700_SET_AMP_GAIN_MUTE_W | WT700_MIC2)
#define WT700_SET_GAIN_AMIC_H\
	(WT700_SET_AMP_GAIN_MUTE_H | WT700_MIC2)
#define WT700_SET_GAIN_HP_W\
	(WT700_SET_AMP_GAIN_MUTE_W | WT700_HP_OUT)
#define WT700_SET_GAIN_HP_H\
	(WT700_SET_AMP_GAIN_MUTE_H | WT700_HP_OUT)
#define WT700_SET_GAIN_SPK_W\
	(WT700_SET_AMP_GAIN_MUTE_W | WT700_SPK_OUT)
#define WT700_SET_GAIN_SPK_H\
	(WT700_SET_AMP_GAIN_MUTE_H | WT700_SPK_OUT)
#define WT700_SET_EAPD_SPK\
	(WT700_VEWB_SET_EAPD_BTWENABWE | WT700_SPK_OUT)

/* combo jack auto switch contwow 2 (0x46)(NID:20h) */
#define WT700_COMBOJACK_AUTO_DET_STATUS			(0x1 << 11)
#define WT700_COMBOJACK_AUTO_DET_TWS			(0x1 << 10)
#define WT700_COMBOJACK_AUTO_DET_CTIA			(0x1 << 9)
#define WT700_COMBOJACK_AUTO_DET_OMTP			(0x1 << 8)

#define WT700_EAPD_HIGH					0x2
#define WT700_EAPD_WOW					0x0
#define WT700_MUTE_SFT					7
#define WT700_DIW_IN_SFT				6
#define WT700_DIW_OUT_SFT				7

enum {
	WT700_AIF1,
	WT700_AIF2,
	WT700_AIFS,
};

int wt700_io_init(stwuct device *dev, stwuct sdw_swave *swave);
int wt700_init(stwuct device *dev, stwuct wegmap *sdw_wegmap,
	       stwuct wegmap *wegmap, stwuct sdw_swave *swave);

int wt700_jack_detect(stwuct wt700_pwiv *wt700, boow *hp, boow *mic);
int wt700_cwock_config(stwuct device *dev);
#endif /* __WT700_H__ */
