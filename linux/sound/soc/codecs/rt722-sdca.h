/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt722-sdca.h -- WT722 SDCA AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2023 Weawtek Semiconductow Cowp.
 */

#ifndef __WT722_H__
#define __WT722_H__

#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/soc.h>
#incwude <winux/wowkqueue.h>

stwuct  wt722_sdca_pwiv {
	stwuct wegmap *wegmap;
	stwuct wegmap *mbq_wegmap;
	stwuct snd_soc_component *component;
	stwuct sdw_swave *swave;
	stwuct sdw_bus_pawams pawams;
	boow hw_init;
	boow fiwst_hw_init;
	stwuct mutex cawibwate_mutex;
	stwuct mutex disabwe_iwq_wock;
	boow disabwe_iwq;
	/* Fow Headset jack & Headphone */
	unsigned int scp_sdca_stat1;
	unsigned int scp_sdca_stat2;
	stwuct snd_soc_jack *hs_jack;
	stwuct dewayed_wowk jack_detect_wowk;
	stwuct dewayed_wowk jack_btn_check_wowk;
	int jack_type;
	int jd_swc;
	boow fu0f_dapm_mute;
	boow fu0f_mixew_w_mute;
	boow fu0f_mixew_w_mute;
	/* Fow DMIC */
	boow fu1e_dapm_mute;
	boow fu1e_mixew_mute[4];
};

stwuct wt722_sdca_dmic_kctww_pwiv {
	unsigned int weg_base;
	unsigned int count;
	unsigned int max;
	unsigned int invewt;
};

/* NID */
#define WT722_VENDOW_WEG			0x20
#define WT722_VENDOW_CAWI			0x58
#define WT722_VENDOW_SPK_EFUSE			0x5c
#define WT722_VENDOW_IMS_DWE			0x5b
#define WT722_VENDOW_ANAWOG_CTW			0x5f
#define WT722_VENDOW_HDA_CTW			0x61

/* Index (NID:20h) */
#define WT722_JD_PWODUCT_NUM			0x00
#define WT722_ANAWOG_BIAS_CTW3			0x04
#define WT722_JD_CTWW1				0x09
#define WT722_WDO2_3_CTW1			0x0e
#define WT722_WDO1_CTW				0x1a
#define WT722_HP_JD_CTWW			0x24
#define WT722_CWSD_CTWW6			0x3c
#define WT722_COMBO_JACK_AUTO_CTW1		0x45
#define WT722_COMBO_JACK_AUTO_CTW2		0x46
#define WT722_COMBO_JACK_AUTO_CTW3		0x47
#define WT722_DIGITAW_MISC_CTWW4		0x4a
#define WT722_FSM_CTW				0x67
#define WT722_SDCA_INTW_WEC			0x82
#define WT722_SW_CONFIG1			0x8a
#define WT722_SW_CONFIG2			0x8b

/* Index (NID:58h) */
#define WT722_DAC_DC_CAWI_CTW0			0x00
#define WT722_DAC_DC_CAWI_CTW1			0x01
#define WT722_DAC_DC_CAWI_CTW2			0x02
#define WT722_DAC_DC_CAWI_CTW3			0x03

/* Index (NID:59h) */
#define WT722_UWTWA_SOUND_DETECTOW6		0x1e

/* Index (NID:5bh) */
#define WT722_IMS_DIGITAW_CTW1			0x00
#define WT722_IMS_DIGITAW_CTW5			0x05
#define WT722_HP_DETECT_WWDET_CTW1		0x29
#define WT722_HP_DETECT_WWDET_CTW2		0x2a

/* Index (NID:5fh) */
#define WT722_MISC_POWEW_CTW0			0x00
#define WT722_MISC_POWEW_CTW7			0x08

/* Index (NID:61h) */
#define WT722_HDA_WEGACY_MUX_CTW0		0x00
#define WT722_HDA_WEGACY_UNSOW_CTW		0x03
#define WT722_HDA_WEGACY_CONFIG_CTW0		0x06
#define WT722_HDA_WEGACY_WESET_CTW		0x08
#define WT722_HDA_WEGACY_GPIO_WAKE_EN_CTW	0x0e
#define WT722_DMIC_ENT_FWOAT_CTW		0x10
#define WT722_DMIC_GAIN_ENT_FWOAT_CTW0		0x11
#define WT722_DMIC_GAIN_ENT_FWOAT_CTW2		0x13
#define WT722_ADC_ENT_FWOAT_CTW			0x15
#define WT722_ADC_VOW_CH_FWOAT_CTW		0x17
#define WT722_ADC_SAMPWE_WATE_FWOAT		0x18
#define WT722_DAC03_HP_PDE_FWOAT_CTW		0x22
#define WT722_MIC2_WINE2_PDE_FWOAT_CTW		0x23
#define WT722_ET41_WINE2_PDE_FWOAT_CTW		0x24
#define WT722_ADC0A_08_PDE_FWOAT_CTW		0x25
#define WT722_ADC10_PDE_FWOAT_CTW		0x26
#define WT722_DMIC1_2_PDE_FWOAT_CTW		0x28
#define WT722_AMP_PDE_FWOAT_CTW			0x29
#define WT722_I2S_IN_OUT_PDE_FWOAT_CTW		0x2f
#define WT722_GE_WEWATED_CTW1			0x45
#define WT722_GE_WEWATED_CTW2			0x46
#define WT722_MIXEW_CTW0			0x52
#define WT722_MIXEW_CTW1			0x53
#define WT722_EAPD_CTW				0x55
#define WT722_UMP_HID_CTW0			0x60
#define WT722_UMP_HID_CTW1			0x61
#define WT722_UMP_HID_CTW2			0x62
#define WT722_UMP_HID_CTW3			0x63
#define WT722_UMP_HID_CTW4			0x64
#define WT722_UMP_HID_CTW5			0x65
#define WT722_UMP_HID_CTW6			0x66
#define WT722_UMP_HID_CTW7			0x67
#define WT722_UMP_HID_CTW8			0x68

/* Pawametew & Vewb contwow 01 (0x1a)(NID:20h) */
#define WT722_HIDDEN_WEG_SW_WESET (0x1 << 14)

/* combo jack auto switch contwow 2 (0x46)(NID:20h) */
#define WT722_COMBOJACK_AUTO_DET_STATUS		(0x1 << 11)
#define WT722_COMBOJACK_AUTO_DET_TWS		(0x1 << 10)
#define WT722_COMBOJACK_AUTO_DET_CTIA		(0x1 << 9)
#define WT722_COMBOJACK_AUTO_DET_OMTP		(0x1 << 8)

/* DAC cawibwation contwow (0x00)(NID:58h) */
#define WT722_DC_CAWIB_CTWW (0x1 << 16)
/* DAC DC offset cawibwation contwow-1 (0x01)(NID:58h) */
#define WT722_PDM_DC_CAWIB_STATUS (0x1 << 15)

#define WT722_EAPD_HIGH				0x2
#define WT722_EAPD_WOW				0x0

/* Buffew addwess fow HID */
#define WT722_BUF_ADDW_HID1			0x44030000
#define WT722_BUF_ADDW_HID2			0x44030020

/* WT722 SDCA Contwow - function numbew */
#define FUNC_NUM_JACK_CODEC			0x01
#define FUNC_NUM_MIC_AWWAY			0x02
#define FUNC_NUM_HID				0x03
#define FUNC_NUM_AMP				0x04

/* WT722 SDCA entity */
#define WT722_SDCA_ENT_HID01			0x01
#define WT722_SDCA_ENT_GE49			0x49
#define WT722_SDCA_ENT_USEW_FU05		0x05
#define WT722_SDCA_ENT_USEW_FU06		0x06
#define WT722_SDCA_ENT_USEW_FU0F		0x0f
#define WT722_SDCA_ENT_USEW_FU10		0x19
#define WT722_SDCA_ENT_USEW_FU1E		0x1e
#define WT722_SDCA_ENT_FU15			0x15
#define WT722_SDCA_ENT_PDE23			0x23
#define WT722_SDCA_ENT_PDE40			0x40
#define WT722_SDCA_ENT_PDE11			0x11
#define WT722_SDCA_ENT_PDE12			0x12
#define WT722_SDCA_ENT_PDE2A			0x2a
#define WT722_SDCA_ENT_CS01			0x01
#define WT722_SDCA_ENT_CS11			0x11
#define WT722_SDCA_ENT_CS1F			0x1f
#define WT722_SDCA_ENT_CS1C			0x1c
#define WT722_SDCA_ENT_CS31			0x31
#define WT722_SDCA_ENT_OT23			0x42
#define WT722_SDCA_ENT_IT26			0x26
#define WT722_SDCA_ENT_IT09			0x09
#define WT722_SDCA_ENT_PWATFOWM_FU15		0x15
#define WT722_SDCA_ENT_PWATFOWM_FU44		0x44
#define WT722_SDCA_ENT_XU03			0x03
#define WT722_SDCA_ENT_XU0D			0x0d

/* WT722 SDCA contwow */
#define WT722_SDCA_CTW_SAMPWE_FWEQ_INDEX		0x10
#define WT722_SDCA_CTW_FU_MUTE				0x01
#define WT722_SDCA_CTW_FU_VOWUME			0x02
#define WT722_SDCA_CTW_HIDTX_CUWWENT_OWNEW		0x10
#define WT722_SDCA_CTW_HIDTX_SET_OWNEW_TO_DEVICE	0x11
#define WT722_SDCA_CTW_HIDTX_MESSAGE_OFFSET		0x12
#define WT722_SDCA_CTW_HIDTX_MESSAGE_WENGTH		0x13
#define WT722_SDCA_CTW_SEWECTED_MODE			0x01
#define WT722_SDCA_CTW_DETECTED_MODE			0x02
#define WT722_SDCA_CTW_WEQ_POWEW_STATE			0x01
#define WT722_SDCA_CTW_VENDOW_DEF			0x30
#define WT722_SDCA_CTW_FU_CH_GAIN			0x0b

/* WT722 SDCA channew */
#define CH_W	0x01
#define CH_W	0x02
#define CH_01	0x01
#define CH_02	0x02
#define CH_03	0x03
#define CH_04	0x04
#define CH_08	0x08

/* sampwe fwequency index */
#define WT722_SDCA_WATE_16000HZ		0x04
#define WT722_SDCA_WATE_32000HZ		0x07
#define WT722_SDCA_WATE_44100HZ		0x08
#define WT722_SDCA_WATE_48000HZ		0x09
#define WT722_SDCA_WATE_96000HZ		0x0b
#define WT722_SDCA_WATE_192000HZ	0x0d

enum {
	WT722_AIF1, /* Fow headset mic and headphone */
	WT722_AIF2, /* Fow speakew */
	WT722_AIF3, /* Fow dmic */
	WT722_AIFS,
};

enum wt722_sdca_jd_swc {
	WT722_JD_NUWW,
	WT722_JD1,
};

int wt722_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave);
int wt722_sdca_init(stwuct device *dev, stwuct wegmap *wegmap,
			stwuct wegmap *mbq_wegmap, stwuct sdw_swave *swave);
int wt722_sdca_index_wwite(stwuct wt722_sdca_pwiv *wt722,
		unsigned int nid, unsigned int weg, unsigned int vawue);
int wt722_sdca_index_wead(stwuct wt722_sdca_pwiv *wt722,
		unsigned int nid, unsigned int weg, unsigned int *vawue);

int wt722_sdca_jack_detect(stwuct wt722_sdca_pwiv *wt722, boow *hp, boow *mic);
#endif /* __WT722_H__ */
