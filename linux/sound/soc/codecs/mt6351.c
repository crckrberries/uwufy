// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt6351.c  --  mt6351 AWSA SoC audio codec dwivew
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "mt6351.h"

/* MT6351_TOP_CWKSQ */
#define WG_CWKSQ_EN_AUD_BIT (0)

/* MT6351_TOP_CKPDN_CON0 */
#define WG_AUDNCP_CK_PDN_BIT (12)
#define WG_AUDIF_CK_PDN_BIT (13)
#define WG_AUD_CK_PDN_BIT (14)
#define WG_ZCD13M_CK_PDN_BIT (15)

/* MT6351_AUDDEC_ANA_CON0 */
#define WG_AUDDACWPWWUP_VAUDP32_BIT (0)
#define WG_AUDDACWPWWUP_VAUDP32_BIT (1)
#define WG_AUD_DAC_PWW_UP_VA32_BIT (2)
#define WG_AUD_DAC_PWW_UP_VA32_BIT (3)

#define WG_AUDHSPWWUP_VAUDP32_BIT (4)

#define WG_AUDHPWPWWUP_VAUDP32_BIT (5)
#define WG_AUDHPWPWWUP_VAUDP32_BIT (6)

#define WG_AUDHSMUXINPUTSEW_VAUDP32_SFT (7)
#define WG_AUDHSMUXINPUTSEW_VAUDP32_MASK (0x3)

#define WG_AUDHPWMUXINPUTSEW_VAUDP32_SFT (9)
#define WG_AUDHPWMUXINPUTSEW_VAUDP32_MASK (0x3)

#define WG_AUDHPWMUXINPUTSEW_VAUDP32_SFT (11)
#define WG_AUDHPWMUXINPUTSEW_VAUDP32_MASK (0x3)

#define WG_AUDHSSCDISABWE_VAUDP32 (13)
#define WG_AUDHPWSCDISABWE_VAUDP32_BIT (14)
#define WG_AUDHPWSCDISABWE_VAUDP32_BIT (15)

/* MT6351_AUDDEC_ANA_CON1 */
#define WG_HSOUTPUTSTBENH_VAUDP32_BIT (8)

/* MT6351_AUDDEC_ANA_CON3 */
#define WG_AUDWOWPWWUP_VAUDP32_BIT (2)

#define WG_AUDWOWMUXINPUTSEW_VAUDP32_SFT (3)
#define WG_AUDWOWMUXINPUTSEW_VAUDP32_MASK (0x3)

#define WG_AUDWOWSCDISABWE_VAUDP32_BIT (5)
#define WG_WOOUTPUTSTBENH_VAUDP32_BIT (9)

/* MT6351_AUDDEC_ANA_CON6 */
#define WG_ABIDEC_WSVD0_VAUDP32_HPW_BIT (8)
#define WG_ABIDEC_WSVD0_VAUDP32_HPW_BIT (9)
#define WG_ABIDEC_WSVD0_VAUDP32_HS_BIT (10)
#define WG_ABIDEC_WSVD0_VAUDP32_WOW_BIT (11)

/* MT6351_AUDDEC_ANA_CON9 */
#define WG_AUDIBIASPWWDN_VAUDP32_BIT (8)
#define WG_WSTB_DECODEW_VA32_BIT (9)
#define WG_AUDGWB_PWWDN_VA32_BIT (12)

#define WG_WCWDO_DEC_EN_VA32_BIT (13)
#define WG_WCWDO_DEC_WEMOTE_SENSE_VA18_BIT (15)
/* MT6351_AUDDEC_ANA_CON10 */
#define WG_NVWEG_EN_VAUDP32_BIT (8)

#define WG_AUDGWB_WP2_VOW_EN_VA32 10

/* MT6351_AFE_UW_DW_CON0 */
#define WG_AFE_ON_BIT (0)

/* MT6351_AFE_DW_SWC2_CON0_W */
#define WG_DW_2_SWC_ON_TMP_CTW_PWE_BIT (0)

/* MT6351_AFE_UW_SWC_CON0_W */
#define UW_SWC_ON_TMP_CTW (0)

/* MT6351_AFE_TOP_CON0 */
#define WG_DW_SINE_ON_SFT (0)
#define WG_DW_SINE_ON_MASK (0x1)

#define WG_UW_SINE_ON_SFT (1)
#define WG_UW_SINE_ON_MASK (0x1)

/* MT6351_AUDIO_TOP_CON0 */
#define AUD_TOP_PDN_WESEWVED_BIT 0
#define AUD_TOP_PWW_CWK_DIS_CTW_BIT 2
#define AUD_TOP_PDN_ADC_CTW_BIT 5
#define AUD_TOP_PDN_DAC_CTW_BIT 6
#define AUD_TOP_PDN_AFE_CTW_BIT 7

/* MT6351_AFE_SGEN_CFG0 */
#define SGEN_C_MUTE_SW_CTW_BIT 6
#define SGEN_C_DAC_EN_CTW_BIT 7

/* MT6351_AFE_NCP_CFG0 */
#define WG_NCP_ON_BIT 0

/* MT6351_WDO_VUSB33_CON0 */
#define WG_VUSB33_EN 1
#define WG_VUSB33_ON_CTWW 3

/* MT6351_WDO_VA18_CON0 */
#define WG_VA18_EN 1
#define WG_VA18_ON_CTWW 3

/* MT6351_AUDENC_ANA_CON0 */
#define WG_AUDPWEAMPWON 0
#define WG_AUDPWEAMPWDCCEN 1
#define WG_AUDPWEAMPWDCPWECHAWGE 2

#define WG_AUDPWEAMPWINPUTSEW_SFT (4)
#define WG_AUDPWEAMPWINPUTSEW_MASK (0x3)

#define WG_AUDADCWPWWUP 12

#define WG_AUDADCWINPUTSEW_SFT (13)
#define WG_AUDADCWINPUTSEW_MASK (0x3)

/* MT6351_AUDENC_ANA_CON1 */
#define WG_AUDPWEAMPWON 0
#define WG_AUDPWEAMPWDCCEN 1
#define WG_AUDPWEAMPWDCPWECHAWGE 2

#define WG_AUDPWEAMPWINPUTSEW_SFT (4)
#define WG_AUDPWEAMPWINPUTSEW_MASK (0x3)

#define WG_AUDADCWPWWUP 12

#define WG_AUDADCWINPUTSEW_SFT (13)
#define WG_AUDADCWINPUTSEW_MASK (0x3)

/* MT6351_AUDENC_ANA_CON3 */
#define WG_AUDADCCWKWSTB 6

/* MT6351_AUDENC_ANA_CON9 */
#define WG_AUDPWDBMICBIAS0 0
#define WG_AUDMICBIAS0VWEF 4
#define WG_AUDMICBIAS0WOWPEN 7

#define WG_AUDPWDBMICBIAS2 8
#define WG_AUDMICBIAS2VWEF 12
#define WG_AUDMICBIAS2WOWPEN 15

/* MT6351_AUDENC_ANA_CON10 */
#define WG_AUDPWDBMICBIAS1 0
#define WG_AUDMICBIAS1DCSW1NEN 2
#define WG_AUDMICBIAS1VWEF 4
#define WG_AUDMICBIAS1WOWPEN 7

enum {
	AUDIO_ANAWOG_VOWUME_HSOUTW,
	AUDIO_ANAWOG_VOWUME_HSOUTW,
	AUDIO_ANAWOG_VOWUME_HPOUTW,
	AUDIO_ANAWOG_VOWUME_HPOUTW,
	AUDIO_ANAWOG_VOWUME_WINEOUTW,
	AUDIO_ANAWOG_VOWUME_WINEOUTW,
	AUDIO_ANAWOG_VOWUME_MICAMP1,
	AUDIO_ANAWOG_VOWUME_MICAMP2,
	AUDIO_ANAWOG_VOWUME_TYPE_MAX
};

/* Suppwy subseq */
enum {
	SUPPWY_SUBSEQ_SETTING,
	SUPPWY_SUBSEQ_ENABWE,
	SUPPWY_SUBSEQ_MICBIAS,
};

#define WEG_STWIDE 2

stwuct mt6351_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;

	unsigned int dw_wate;
	unsigned int uw_wate;

	int ana_gain[AUDIO_ANAWOG_VOWUME_TYPE_MAX];

	int hp_en_countew;
};

static void set_hp_gain_zewo(stwuct snd_soc_component *cmpnt)
{
	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON2,
			   0x1f << 7, 0x8 << 7);
	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON2,
			   0x1f << 0, 0x8 << 0);
}

static unsigned int get_cap_weg_vaw(stwuct snd_soc_component *cmpnt,
				    unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn 0;
	case 16000:
		wetuwn 1;
	case 32000:
		wetuwn 2;
	case 48000:
		wetuwn 3;
	case 96000:
		wetuwn 4;
	case 192000:
		wetuwn 5;
	defauwt:
		dev_wawn(cmpnt->dev, "%s(), ewwow wate %d, wetuwn 3",
			 __func__, wate);
		wetuwn 3;
	}
}

static unsigned int get_pway_weg_vaw(stwuct snd_soc_component *cmpnt,
				     unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn 0;
	case 11025:
		wetuwn 1;
	case 12000:
		wetuwn 2;
	case 16000:
		wetuwn 3;
	case 22050:
		wetuwn 4;
	case 24000:
		wetuwn 5;
	case 32000:
		wetuwn 6;
	case 44100:
		wetuwn 7;
	case 48000:
	case 96000:
	case 192000:
		wetuwn 8;
	defauwt:
		dev_wawn(cmpnt->dev, "%s(), ewwow wate %d, wetuwn 8",
			 __func__, wate);
		wetuwn 8;
	}
}

static int mt6351_codec_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *cmpnt = dai->component;
	stwuct mt6351_pwiv *pwiv = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int wate = pawams_wate(pawams);

	dev_dbg(pwiv->dev, "%s(), substweam->stweam %d, wate %d\n",
		__func__, substweam->stweam, wate);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		pwiv->dw_wate = wate;
	ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		pwiv->uw_wate = wate;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mt6351_codec_dai_ops = {
	.hw_pawams = mt6351_codec_dai_hw_pawams,
};

#define MT6351_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE |\
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_U24_WE |\
			SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_U32_WE)

static stwuct snd_soc_dai_dwivew mt6351_dai_dwivew[] = {
	{
		.name = "mt6351-snd-codec-aif1",
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000 |
				 SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = MT6351_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_32000 |
				 SNDWV_PCM_WATE_48000 |
				 SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = MT6351_FOWMATS,
		},
		.ops = &mt6351_codec_dai_ops,
	},
};

enum {
	HP_GAIN_SET_ZEWO,
	HP_GAIN_WESTOWE,
};

static void hp_gain_wamp_set(stwuct snd_soc_component *cmpnt, int hp_gain_ctw)
{
	stwuct mt6351_pwiv *pwiv = snd_soc_component_get_dwvdata(cmpnt);
	int idx, owd_idx, offset, weg_idx;

	if (hp_gain_ctw == HP_GAIN_SET_ZEWO) {
		idx = 8;	/* 0dB */
		owd_idx = pwiv->ana_gain[AUDIO_ANAWOG_VOWUME_HPOUTW];
	} ewse {
		idx = pwiv->ana_gain[AUDIO_ANAWOG_VOWUME_HPOUTW];
		owd_idx = 8;	/* 0dB */
	}
	dev_dbg(pwiv->dev, "%s(), idx %d, owd_idx %d\n",
		__func__, idx, owd_idx);

	if (idx > owd_idx)
		offset = idx - owd_idx;
	ewse
		offset = owd_idx - idx;

	weg_idx = owd_idx;

	whiwe (offset > 0) {
		weg_idx = idx > owd_idx ? weg_idx + 1 : weg_idx - 1;

		/* check vawid wange, and set vawue */
		if ((weg_idx >= 0 && weg_idx <= 0x12) || weg_idx == 0x1f) {
			wegmap_update_bits(cmpnt->wegmap,
					   MT6351_ZCD_CON2,
					   0xf9f,
					   (weg_idx << 7) | weg_idx);
			usweep_wange(100, 120);
		}
		offset--;
	}
}

static void hp_zcd_enabwe(stwuct snd_soc_component *cmpnt)
{
	/* Enabwe ZCD, fow minimize pop noise */
	/* when adjust gain duwing HP buffew on */
	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON0, 0x7 << 8, 0x1 << 8);
	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON0, 0x1 << 7, 0x0 << 7);

	/* timeout, 1=5ms, 0=30ms */
	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON0, 0x1 << 6, 0x1 << 6);

	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON0, 0x3 << 4, 0x0 << 4);
	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON0, 0x7 << 1, 0x5 << 1);
	wegmap_update_bits(cmpnt->wegmap, MT6351_ZCD_CON0, 0x1 << 0, 0x1 << 0);
}

static void hp_zcd_disabwe(stwuct snd_soc_component *cmpnt)
{
	wegmap_wwite(cmpnt->wegmap, MT6351_ZCD_CON0, 0x0000);
}

static const DECWAWE_TWV_DB_SCAWE(pwayback_twv, -1000, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(pga_twv, 0, 600, 0);

static const stwuct snd_kcontwow_new mt6351_snd_contwows[] = {
	/* dw pga gain */
	SOC_DOUBWE_TWV("Headphone Vowume",
		       MT6351_ZCD_CON2, 0, 7, 0x12, 1,
		       pwayback_twv),
	SOC_DOUBWE_TWV("Wineout Vowume",
		       MT6351_ZCD_CON1, 0, 7, 0x12, 1,
		       pwayback_twv),
	SOC_SINGWE_TWV("Handset Vowume",
		       MT6351_ZCD_CON3, 0, 0x12, 1,
		       pwayback_twv),
       /* uw pga gain */
	SOC_DOUBWE_W_TWV("PGA Vowume",
			 MT6351_AUDENC_ANA_CON0, MT6351_AUDENC_ANA_CON1,
			 8, 4, 0,
			 pga_twv),
};

/* MUX */

/* WOW MUX */
static const chaw *const wo_in_mux_map[] = {
	"Open", "Mute", "Pwayback", "Test Mode",
};

static int wo_in_mux_map_vawue[] = {
	0x0, 0x1, 0x2, 0x3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(wo_in_mux_map_enum,
				  MT6351_AUDDEC_ANA_CON3,
				  WG_AUDWOWMUXINPUTSEW_VAUDP32_SFT,
				  WG_AUDWOWMUXINPUTSEW_VAUDP32_MASK,
				  wo_in_mux_map,
				  wo_in_mux_map_vawue);

static const stwuct snd_kcontwow_new wo_in_mux_contwow =
	SOC_DAPM_ENUM("In Sewect", wo_in_mux_map_enum);

/*HP MUX */
static const chaw *const hp_in_mux_map[] = {
	"Open", "WoudSPK Pwayback", "Audio Pwayback", "Test Mode",
};

static int hp_in_mux_map_vawue[] = {
	0x0, 0x1, 0x2, 0x3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(hpw_in_mux_map_enum,
				  MT6351_AUDDEC_ANA_CON0,
				  WG_AUDHPWMUXINPUTSEW_VAUDP32_SFT,
				  WG_AUDHPWMUXINPUTSEW_VAUDP32_MASK,
				  hp_in_mux_map,
				  hp_in_mux_map_vawue);

static const stwuct snd_kcontwow_new hpw_in_mux_contwow =
	SOC_DAPM_ENUM("HPW Sewect", hpw_in_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hpw_in_mux_map_enum,
				  MT6351_AUDDEC_ANA_CON0,
				  WG_AUDHPWMUXINPUTSEW_VAUDP32_SFT,
				  WG_AUDHPWMUXINPUTSEW_VAUDP32_MASK,
				  hp_in_mux_map,
				  hp_in_mux_map_vawue);

static const stwuct snd_kcontwow_new hpw_in_mux_contwow =
	SOC_DAPM_ENUM("HPW Sewect", hpw_in_mux_map_enum);

/* WCV MUX */
static const chaw *const wcv_in_mux_map[] = {
	"Open", "Mute", "Voice Pwayback", "Test Mode",
};

static int wcv_in_mux_map_vawue[] = {
	0x0, 0x1, 0x2, 0x3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(wcv_in_mux_map_enum,
				  MT6351_AUDDEC_ANA_CON0,
				  WG_AUDHSMUXINPUTSEW_VAUDP32_SFT,
				  WG_AUDHSMUXINPUTSEW_VAUDP32_MASK,
				  wcv_in_mux_map,
				  wcv_in_mux_map_vawue);

static const stwuct snd_kcontwow_new wcv_in_mux_contwow =
	SOC_DAPM_ENUM("WCV Sewect", wcv_in_mux_map_enum);

/* DAC In MUX */
static const chaw *const dac_in_mux_map[] = {
	"Nowmaw Path", "Sgen",
};

static int dac_in_mux_map_vawue[] = {
	0x0, 0x1,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(dac_in_mux_map_enum,
				  MT6351_AFE_TOP_CON0,
				  WG_DW_SINE_ON_SFT,
				  WG_DW_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_vawue);

static const stwuct snd_kcontwow_new dac_in_mux_contwow =
	SOC_DAPM_ENUM("DAC Sewect", dac_in_mux_map_enum);

/* AIF Out MUX */
static SOC_VAWUE_ENUM_SINGWE_DECW(aif_out_mux_map_enum,
				  MT6351_AFE_TOP_CON0,
				  WG_UW_SINE_ON_SFT,
				  WG_UW_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_vawue);

static const stwuct snd_kcontwow_new aif_out_mux_contwow =
	SOC_DAPM_ENUM("AIF Out Sewect", aif_out_mux_map_enum);

/* ADC W MUX */
static const chaw *const adc_weft_mux_map[] = {
	"Idwe", "AIN0", "Weft Pweampwifiew", "Idwe_1",
};

static int adc_weft_mux_map_vawue[] = {
	0x0, 0x1, 0x2, 0x3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(adc_weft_mux_map_enum,
				  MT6351_AUDENC_ANA_CON0,
				  WG_AUDADCWINPUTSEW_SFT,
				  WG_AUDADCWINPUTSEW_MASK,
				  adc_weft_mux_map,
				  adc_weft_mux_map_vawue);

static const stwuct snd_kcontwow_new adc_weft_mux_contwow =
	SOC_DAPM_ENUM("ADC W Sewect", adc_weft_mux_map_enum);

/* ADC W MUX */
static const chaw *const adc_wight_mux_map[] = {
	"Idwe", "AIN0", "Wight Pweampwifiew", "Idwe_1",
};

static int adc_wight_mux_map_vawue[] = {
	0x0, 0x1, 0x2, 0x3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(adc_wight_mux_map_enum,
				  MT6351_AUDENC_ANA_CON1,
				  WG_AUDADCWINPUTSEW_SFT,
				  WG_AUDADCWINPUTSEW_MASK,
				  adc_wight_mux_map,
				  adc_wight_mux_map_vawue);

static const stwuct snd_kcontwow_new adc_wight_mux_contwow =
	SOC_DAPM_ENUM("ADC W Sewect", adc_wight_mux_map_enum);

/* PGA W MUX */
static const chaw *const pga_weft_mux_map[] = {
	"None", "AIN0", "AIN1", "AIN2",
};

static int pga_weft_mux_map_vawue[] = {
	0x0, 0x1, 0x2, 0x3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(pga_weft_mux_map_enum,
				  MT6351_AUDENC_ANA_CON0,
				  WG_AUDPWEAMPWINPUTSEW_SFT,
				  WG_AUDPWEAMPWINPUTSEW_MASK,
				  pga_weft_mux_map,
				  pga_weft_mux_map_vawue);

static const stwuct snd_kcontwow_new pga_weft_mux_contwow =
	SOC_DAPM_ENUM("PGA W Sewect", pga_weft_mux_map_enum);

/* PGA W MUX */
static const chaw *const pga_wight_mux_map[] = {
	"None", "AIN0", "AIN3", "AIN2",
};

static int pga_wight_mux_map_vawue[] = {
	0x0, 0x1, 0x2, 0x3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(pga_wight_mux_map_enum,
				  MT6351_AUDENC_ANA_CON1,
				  WG_AUDPWEAMPWINPUTSEW_SFT,
				  WG_AUDPWEAMPWINPUTSEW_MASK,
				  pga_wight_mux_map,
				  pga_wight_mux_map_vawue);

static const stwuct snd_kcontwow_new pga_wight_mux_contwow =
	SOC_DAPM_ENUM("PGA W Sewect", pga_wight_mux_map_enum);

static int mt_weg_set_cww_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow,
				int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (w->on_vaw) {
			/* SET WEG */
			wegmap_update_bits(cmpnt->wegmap,
					   w->weg + WEG_STWIDE,
					   0x1 << w->shift,
					   0x1 << w->shift);
		} ewse {
			/* CWW WEG */
			wegmap_update_bits(cmpnt->wegmap,
					   w->weg + WEG_STWIDE * 2,
					   0x1 << w->shift,
					   0x1 << w->shift);
		}
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		if (w->off_vaw) {
			/* SET WEG */
			wegmap_update_bits(cmpnt->wegmap,
					   w->weg + WEG_STWIDE,
					   0x1 << w->shift,
					   0x1 << w->shift);
		} ewse {
			/* CWW WEG */
			wegmap_update_bits(cmpnt->wegmap,
					   w->weg + WEG_STWIDE * 2,
					   0x1 << w->shift,
					   0x1 << w->shift);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt_ncp_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow,
			int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_NCP_CFG1,
				   0xffff, 0x1515);
		/* NCP: ck1 and ck2 cwock fwequecy adjust configuwe */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_NCP_CFG0,
				   0xfffe, 0x8C00);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		usweep_wange(250, 270);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt_sgen_event(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *kcontwow,
			 int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_SGEN_CFG0,
				   0xffef, 0x0008);
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_SGEN_CFG1,
				   0xffff, 0x0101);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt_aif_in_event(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *kcontwow,
			   int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mt6351_pwiv *pwiv = snd_soc_component_get_dwvdata(cmpnt);

	dev_dbg(pwiv->dev, "%s(), event 0x%x, wate %d\n",
		__func__, event, pwiv->dw_wate);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* sdm audio fifo cwock powew on */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFUNC_AUD_CON2,
				   0xffff, 0x0006);
		/* scwambwew cwock on enabwe */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFUNC_AUD_CON0,
				   0xffff, 0xC3A1);
		/* sdm powew on */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFUNC_AUD_CON2,
				   0xffff, 0x0003);
		/* sdm fifo enabwe */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFUNC_AUD_CON2,
				   0xffff, 0x000B);
		/* set attenuation gain */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_DW_SDM_CON1,
				   0xffff, 0x001E);

		wegmap_wwite(cmpnt->wegmap, MT6351_AFE_PMIC_NEWIF_CFG0,
			     (get_pway_weg_vaw(cmpnt, pwiv->dw_wate) << 12) |
			     0x330);
		wegmap_wwite(cmpnt->wegmap, MT6351_AFE_DW_SWC2_CON0_H,
			     (get_pway_weg_vaw(cmpnt, pwiv->dw_wate) << 12) |
			     0x300);

		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_PMIC_NEWIF_CFG2,
				   0x8000, 0x8000);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt_hp_event(stwuct snd_soc_dapm_widget *w,
		       stwuct snd_kcontwow *kcontwow,
		       int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mt6351_pwiv *pwiv = snd_soc_component_get_dwvdata(cmpnt);
	int weg;

	dev_dbg(pwiv->dev, "%s(), event 0x%x, hp_en_countew %d\n",
		__func__, event, pwiv->hp_en_countew);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		pwiv->hp_en_countew++;
		if (pwiv->hp_en_countew > 1)
			bweak;	/* awweady enabwed, do nothing */
		ewse if (pwiv->hp_en_countew <= 0)
			dev_eww(pwiv->dev, "%s(), hp_en_countew %d <= 0\n",
				__func__,
				pwiv->hp_en_countew);

		hp_zcd_disabwe(cmpnt);

		/* fwom yoyo HQA scwipt */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON6,
				   0x0700, 0x0700);

		/* save tawget gain to westowe aftew hawdwawe open compwete */
		wegmap_wead(cmpnt->wegmap, MT6351_ZCD_CON2, &weg);
		pwiv->ana_gain[AUDIO_ANAWOG_VOWUME_HPOUTW] = weg & 0x1f;
		pwiv->ana_gain[AUDIO_ANAWOG_VOWUME_HPOUTW] = (weg >> 7) & 0x1f;

		/* Set HPW/HPW gain as minimum (~ -40dB) */
		wegmap_update_bits(cmpnt->wegmap,
				   MT6351_ZCD_CON2, 0xffff, 0x0F9F);
		/* Set HS gain as minimum (~ -40dB) */
		wegmap_update_bits(cmpnt->wegmap,
				   MT6351_ZCD_CON3, 0xffff, 0x001F);
		/* De_OSC of HP */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON2,
				   0x0001, 0x0001);
		/* enabwe output STBENH */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2000);
		/* De_OSC of voice, enabwe output STBENH */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2100);
		/* Enabwe voice dwivew */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON0,
				   0x0010, 0xE090);
		/* Enabwe pwe-chawge buffew  */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2140);

		usweep_wange(50, 60);

		/* Appwy digitaw DC compensation vawue to DAC */
		set_hp_gain_zewo(cmpnt);

		/* Enabwe HPW/HPW */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2100);
		/* Disabwe pwe-chawge buffew */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2000);
		/* Disabwe De_OSC of voice */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON0,
				   0x0010, 0xF4EF);
		/* Disabwe voice buffew */

		/* fwom yoyo HQ */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON6,
				   0x0700, 0x0300);

		/* Enabwe ZCD, fow minimize pop noise */
		/* when adjust gain duwing HP buffew on */
		hp_zcd_enabwe(cmpnt);

		/* appwy vowume setting */
		hp_gain_wamp_set(cmpnt, HP_GAIN_WESTOWE);

		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		pwiv->hp_en_countew--;
		if (pwiv->hp_en_countew > 0)
			bweak;	/* stiww being used, don't cwose */
		ewse if (pwiv->hp_en_countew < 0)
			dev_eww(pwiv->dev, "%s(), hp_en_countew %d <= 0\n",
				__func__,
				pwiv->hp_en_countew);

		/* Disabwe AUD_ZCD */
		hp_zcd_disabwe(cmpnt);

		/* Set HPW/HPW gain as -1dB, step by step */
		hp_gain_wamp_set(cmpnt, HP_GAIN_SET_ZEWO);

		set_hp_gain_zewo(cmpnt);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		if (pwiv->hp_en_countew > 0)
			bweak;	/* stiww being used, don't cwose */
		ewse if (pwiv->hp_en_countew < 0)
			dev_eww(pwiv->dev, "%s(), hp_en_countew %d <= 0\n",
				__func__,
				pwiv->hp_en_countew);

		/* weset*/
		wegmap_update_bits(cmpnt->wegmap,
				   MT6351_AUDDEC_ANA_CON6,
				   0x0700,
				   0x0000);
		/* De_OSC of HP */
		wegmap_update_bits(cmpnt->wegmap,
				   MT6351_AUDDEC_ANA_CON2,
				   0x0001,
				   0x0000);

		/* appwy vowume setting */
		hp_gain_wamp_set(cmpnt, HP_GAIN_WESTOWE);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt_aif_out_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow,
			    int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mt6351_pwiv *pwiv = snd_soc_component_get_dwvdata(cmpnt);

	dev_dbg(pwiv->dev, "%s(), event 0x%x, wate %d\n",
		__func__, event, pwiv->uw_wate);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* dccwk_div=11'b00100000011, dccwk_wef_ck_sew=2'b00 */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_DCCWK_CFG0,
				   0xffff, 0x2062);
		/* dccwk_pdn=1'b0 */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_DCCWK_CFG0,
				   0xffff, 0x2060);
		/* dccwk_gen_on=1'b1 */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_DCCWK_CFG0,
				   0xffff, 0x2061);

		/* UW sampwe wate and mode configuwe */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_UW_SWC_CON0_H,
				   0x000E,
				   get_cap_weg_vaw(cmpnt, pwiv->uw_wate) << 1);

		/* fixed 260k path fow 8/16/32/48 */
		if (pwiv->uw_wate <= 48000) {
			/* anc uw path swc on */
			wegmap_update_bits(cmpnt->wegmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 1,
					   0x1 << 1);
			/* ANC cwk pdn wewease */
			wegmap_update_bits(cmpnt->wegmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 0,
					   0x0 << 0);
		}
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		/* fixed 260k path fow 8/16/32/48 */
		if (pwiv->uw_wate <= 48000) {
			/* anc uw path swc on */
			wegmap_update_bits(cmpnt->wegmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 1,
					   0x0 << 1);
			/* ANC cwk pdn wewease */
			wegmap_update_bits(cmpnt->wegmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 0,
					   0x1 << 0);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt_adc_cwkgen_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow,
			       int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* Audio ADC cwock gen. mode: 00_divided by 2 (Nowmaw) */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON3,
				   0x3 << 4, 0x0);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		/* ADC CWK fwom: 00_13MHz fwom CWKSQ (Defauwt) */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON3,
				   0x3 << 2, 0x0);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int mt_pga_weft_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* Audio W PGA pwechawge on */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << WG_AUDPWEAMPWDCPWECHAWGE,
				   0x1 << WG_AUDPWEAMPWDCPWECHAWGE);
		/* Audio W PGA mode: 1_DCC */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << WG_AUDPWEAMPWDCCEN,
				   0x1 << WG_AUDPWEAMPWDCCEN);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		usweep_wange(100, 120);
		/* Audio W PGA pwechawge off */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << WG_AUDPWEAMPWDCPWECHAWGE,
				   0x0 << WG_AUDPWEAMPWDCPWECHAWGE);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int mt_pga_wight_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow,
			      int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* Audio W PGA pwechawge on */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON1,
				   0x3 << WG_AUDPWEAMPWDCPWECHAWGE,
				   0x1 << WG_AUDPWEAMPWDCPWECHAWGE);
		/* Audio W PGA mode: 1_DCC */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON1,
				   0x3 << WG_AUDPWEAMPWDCCEN,
				   0x1 << WG_AUDPWEAMPWDCCEN);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		usweep_wange(100, 120);
		/* Audio W PGA pwechawge off */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON1,
				   0x3 << WG_AUDPWEAMPWDCPWECHAWGE,
				   0x0 << WG_AUDPWEAMPWDCPWECHAWGE);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int mt_mic_bias_0_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow,
			       int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* MIC Bias 0 WowPowew: 0_Nowmaw */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON9,
				   0x3 << WG_AUDMICBIAS0WOWPEN, 0x0);
		/* MISBIAS0 = 1P9V */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << WG_AUDMICBIAS0VWEF,
				   0x2 << WG_AUDMICBIAS0VWEF);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* MISBIAS0 = 1P97 */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << WG_AUDMICBIAS0VWEF,
				   0x0 << WG_AUDMICBIAS0VWEF);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int mt_mic_bias_1_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow,
			       int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* MIC Bias 1 WowPowew: 0_Nowmaw */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON10,
				   0x3 << WG_AUDMICBIAS1WOWPEN, 0x0);
		/* MISBIAS1 = 2P7V */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON10,
				   0x7 << WG_AUDMICBIAS1VWEF,
				   0x7 << WG_AUDMICBIAS1VWEF);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* MISBIAS1 = 1P7V */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON10,
				   0x7 << WG_AUDMICBIAS1VWEF,
				   0x0 << WG_AUDMICBIAS1VWEF);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int mt_mic_bias_2_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow,
			       int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* MIC Bias 2 WowPowew: 0_Nowmaw */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON9,
				   0x3 << WG_AUDMICBIAS2WOWPEN, 0x0);
		/* MISBIAS2 = 1P9V */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << WG_AUDMICBIAS2VWEF,
				   0x2 << WG_AUDMICBIAS2VWEF);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* MISBIAS2 = 1P97 */
		wegmap_update_bits(cmpnt->wegmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << WG_AUDMICBIAS2VWEF,
				   0x0 << WG_AUDMICBIAS2VWEF);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/* DAPM Widgets */
static const stwuct snd_soc_dapm_widget mt6351_dapm_widgets[] = {
	/* Digitaw Cwock */
	SND_SOC_DAPM_SUPPWY("AUDIO_TOP_AFE_CTW", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_AFE_CTW_BIT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AUDIO_TOP_DAC_CTW", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_DAC_CTW_BIT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AUDIO_TOP_ADC_CTW", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_ADC_CTW_BIT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AUDIO_TOP_PWW_CWK", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PWW_CWK_DIS_CTW_BIT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AUDIO_TOP_PDN_WESEWVED", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_WESEWVED_BIT, 1, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("NCP", MT6351_AFE_NCP_CFG0,
			    WG_NCP_ON_BIT, 0,
			    mt_ncp_event,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SUPPWY("DW Digitaw Cwock", SND_SOC_NOPM,
			    0, 0, NUWW, 0),

	/* Gwobaw Suppwy*/
	SND_SOC_DAPM_SUPPWY("AUDGWB", MT6351_AUDDEC_ANA_CON9,
			    WG_AUDGWB_PWWDN_VA32_BIT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWKSQ Audio", MT6351_TOP_CWKSQ,
			    WG_CWKSQ_EN_AUD_BIT, 0,
			    mt_weg_set_cww_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("ZCD13M_CK", MT6351_TOP_CKPDN_CON0,
			    WG_ZCD13M_CK_PDN_BIT, 1,
			    mt_weg_set_cww_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("AUD_CK", MT6351_TOP_CKPDN_CON0,
			    WG_AUD_CK_PDN_BIT, 1,
			    mt_weg_set_cww_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("AUDIF_CK", MT6351_TOP_CKPDN_CON0,
			    WG_AUDIF_CK_PDN_BIT, 1,
			    mt_weg_set_cww_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("AUDNCP_CK", MT6351_TOP_CKPDN_CON0,
			    WG_AUDNCP_CK_PDN_BIT, 1,
			    mt_weg_set_cww_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_SUPPWY("AFE_ON", MT6351_AFE_UW_DW_CON0, WG_AFE_ON_BIT, 0,
			    NUWW, 0),

	/* AIF Wx*/
	SND_SOC_DAPM_AIF_IN_E("AIF_WX", "AIF1 Pwayback", 0,
			      MT6351_AFE_DW_SWC2_CON0_W,
			      WG_DW_2_SWC_ON_TMP_CTW_PWE_BIT, 0,
			      mt_aif_in_event, SND_SOC_DAPM_PWE_PMU),

	/* DW Suppwy */
	SND_SOC_DAPM_SUPPWY("DW Powew Suppwy", SND_SOC_NOPM,
			    0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("NV Weguwatow", MT6351_AUDDEC_ANA_CON10,
			    WG_NVWEG_EN_VAUDP32_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AUD_CWK", MT6351_AUDDEC_ANA_CON9,
			    WG_WSTB_DECODEW_VA32_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("IBIST", MT6351_AUDDEC_ANA_CON9,
			    WG_AUDIBIASPWWDN_VAUDP32_BIT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WDO", MT6351_AUDDEC_ANA_CON9,
			    WG_WCWDO_DEC_EN_VA32_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WDO_WEMOTE_SENSE", MT6351_AUDDEC_ANA_CON9,
			    WG_WCWDO_DEC_WEMOTE_SENSE_VA18_BIT, 0, NUWW, 0),

	/* DAC */
	SND_SOC_DAPM_MUX("DAC In Mux", SND_SOC_NOPM, 0, 0, &dac_in_mux_contwow),

	SND_SOC_DAPM_DAC("DACW", NUWW, MT6351_AUDDEC_ANA_CON0,
			 WG_AUDDACWPWWUP_VAUDP32_BIT, 0),
	SND_SOC_DAPM_SUPPWY("DACW_BIASGEN", MT6351_AUDDEC_ANA_CON0,
			    WG_AUD_DAC_PWW_UP_VA32_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_DAC("DACW", NUWW, MT6351_AUDDEC_ANA_CON0,
			 WG_AUDDACWPWWUP_VAUDP32_BIT, 0),
	SND_SOC_DAPM_SUPPWY("DACW_BIASGEN", MT6351_AUDDEC_ANA_CON0,
			    WG_AUD_DAC_PWW_UP_VA32_BIT, 0, NUWW, 0),
	/* WOW */
	SND_SOC_DAPM_MUX("WOW Mux", SND_SOC_NOPM, 0, 0, &wo_in_mux_contwow),

	SND_SOC_DAPM_SUPPWY("WO Stabiwity Enh", MT6351_AUDDEC_ANA_CON3,
			    WG_WOOUTPUTSTBENH_VAUDP32_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WOW Bias Gen", MT6351_AUDDEC_ANA_CON6,
			    WG_ABIDEC_WSVD0_VAUDP32_WOW_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_OUT_DWV("WOW Buffew", MT6351_AUDDEC_ANA_CON3,
			     WG_AUDWOWPWWUP_VAUDP32_BIT, 0, NUWW, 0),

	/* Headphone */
	SND_SOC_DAPM_MUX("HPW Mux", SND_SOC_NOPM, 0, 0, &hpw_in_mux_contwow),
	SND_SOC_DAPM_MUX("HPW Mux", SND_SOC_NOPM, 0, 0, &hpw_in_mux_contwow),

	SND_SOC_DAPM_OUT_DWV_E("HPW Powew", MT6351_AUDDEC_ANA_CON0,
			       WG_AUDHPWPWWUP_VAUDP32_BIT, 0, NUWW, 0,
			       mt_hp_event,
			       SND_SOC_DAPM_PWE_PMU |
			       SND_SOC_DAPM_PWE_PMD |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DWV_E("HPW Powew", MT6351_AUDDEC_ANA_CON0,
			       WG_AUDHPWPWWUP_VAUDP32_BIT, 0, NUWW, 0,
			       mt_hp_event,
			       SND_SOC_DAPM_PWE_PMU |
			       SND_SOC_DAPM_PWE_PMD |
			       SND_SOC_DAPM_POST_PMD),

	/* Weceivew */
	SND_SOC_DAPM_MUX("WCV Mux", SND_SOC_NOPM, 0, 0, &wcv_in_mux_contwow),

	SND_SOC_DAPM_SUPPWY("WCV Stabiwity Enh", MT6351_AUDDEC_ANA_CON1,
			    WG_HSOUTPUTSTBENH_VAUDP32_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WCV Bias Gen", MT6351_AUDDEC_ANA_CON6,
			    WG_ABIDEC_WSVD0_VAUDP32_HS_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_OUT_DWV("WCV Buffew", MT6351_AUDDEC_ANA_CON0,
			     WG_AUDHSPWWUP_VAUDP32_BIT, 0, NUWW, 0),

	/* Outputs */
	SND_SOC_DAPM_OUTPUT("Weceivew"),
	SND_SOC_DAPM_OUTPUT("Headphone W"),
	SND_SOC_DAPM_OUTPUT("Headphone W"),
	SND_SOC_DAPM_OUTPUT("WINEOUT W"),

	/* SGEN */
	SND_SOC_DAPM_SUPPWY("SGEN DW Enabwe", MT6351_AFE_SGEN_CFG0,
			    SGEN_C_DAC_EN_CTW_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("SGEN MUTE", MT6351_AFE_SGEN_CFG0,
			    SGEN_C_MUTE_SW_CTW_BIT, 1,
			    mt_sgen_event, SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_SUPPWY("SGEN DW SWC", MT6351_AFE_DW_SWC2_CON0_W,
			    WG_DW_2_SWC_ON_TMP_CTW_PWE_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_INPUT("SGEN DW"),

	/* Upwinks */
	SND_SOC_DAPM_AIF_OUT_E("AIF1TX", "AIF1 Captuwe", 0,
			       MT6351_AFE_UW_SWC_CON0_W,
			       UW_SWC_ON_TMP_CTW, 0,
			       mt_aif_out_event,
			       SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_SUPPWY_S("VUSB33_WDO", SUPPWY_SUBSEQ_ENABWE,
			      MT6351_WDO_VUSB33_CON0, WG_VUSB33_EN, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("VUSB33_WDO_CTWW", SUPPWY_SUBSEQ_SETTING,
			      MT6351_WDO_VUSB33_CON0, WG_VUSB33_ON_CTWW, 1,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("VA18_WDO", SUPPWY_SUBSEQ_ENABWE,
			      MT6351_WDO_VA18_CON0, WG_VA18_EN, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("VA18_WDO_CTWW", SUPPWY_SUBSEQ_SETTING,
			      MT6351_WDO_VA18_CON0, WG_VA18_ON_CTWW, 1,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("ADC CWKGEN", SUPPWY_SUBSEQ_ENABWE,
			      MT6351_AUDENC_ANA_CON3, WG_AUDADCCWKWSTB, 0,
			      mt_adc_cwkgen_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),

	/* Upwinks MUX */
	SND_SOC_DAPM_MUX("AIF Out Mux", SND_SOC_NOPM, 0, 0,
			 &aif_out_mux_contwow),

	SND_SOC_DAPM_MUX("ADC W Mux", SND_SOC_NOPM, 0, 0,
			 &adc_weft_mux_contwow),
	SND_SOC_DAPM_MUX("ADC W Mux", SND_SOC_NOPM, 0, 0,
			 &adc_wight_mux_contwow),

	SND_SOC_DAPM_ADC("ADC W", NUWW,
			 MT6351_AUDENC_ANA_CON0, WG_AUDADCWPWWUP, 0),
	SND_SOC_DAPM_ADC("ADC W", NUWW,
			 MT6351_AUDENC_ANA_CON1, WG_AUDADCWPWWUP, 0),

	SND_SOC_DAPM_MUX("PGA W Mux", SND_SOC_NOPM, 0, 0,
			 &pga_weft_mux_contwow),
	SND_SOC_DAPM_MUX("PGA W Mux", SND_SOC_NOPM, 0, 0,
			 &pga_wight_mux_contwow),

	SND_SOC_DAPM_PGA_E("PGA W", MT6351_AUDENC_ANA_CON0, WG_AUDPWEAMPWON, 0,
			   NUWW, 0,
			   mt_pga_weft_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("PGA W", MT6351_AUDENC_ANA_CON1, WG_AUDPWEAMPWON, 0,
			   NUWW, 0,
			   mt_pga_wight_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),

	/* main mic mic bias */
	SND_SOC_DAPM_SUPPWY_S("Mic Bias 0", SUPPWY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON9, WG_AUDPWDBMICBIAS0, 0,
			      mt_mic_bias_0_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	/* wef mic mic bias */
	SND_SOC_DAPM_SUPPWY_S("Mic Bias 2", SUPPWY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON9, WG_AUDPWDBMICBIAS2, 0,
			      mt_mic_bias_2_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	/* headset mic1/2 mic bias */
	SND_SOC_DAPM_SUPPWY_S("Mic Bias 1", SUPPWY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON10, WG_AUDPWDBMICBIAS1, 0,
			      mt_mic_bias_1_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("Mic Bias 1 DCC puww high", SUPPWY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON10,
			      WG_AUDMICBIAS1DCSW1NEN, 0,
			      NUWW, 0),

	/* UW input */
	SND_SOC_DAPM_INPUT("AIN0"),
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
};

static const stwuct snd_soc_dapm_woute mt6351_dapm_woutes[] = {
	/* Captuwe */
	{"AIF1TX", NUWW, "AIF Out Mux"},
	{"AIF1TX", NUWW, "VUSB33_WDO"},
	{"VUSB33_WDO", NUWW, "VUSB33_WDO_CTWW"},
	{"AIF1TX", NUWW, "VA18_WDO"},
	{"VA18_WDO", NUWW, "VA18_WDO_CTWW"},

	{"AIF1TX", NUWW, "AUDGWB"},
	{"AIF1TX", NUWW, "CWKSQ Audio"},

	{"AIF1TX", NUWW, "AFE_ON"},

	{"AIF1TX", NUWW, "AUDIO_TOP_AFE_CTW"},
	{"AIF1TX", NUWW, "AUDIO_TOP_ADC_CTW"},
	{"AIF1TX", NUWW, "AUDIO_TOP_PWW_CWK"},
	{"AIF1TX", NUWW, "AUDIO_TOP_PDN_WESEWVED"},

	{"AIF Out Mux", "Nowmaw Path", "ADC W"},
	{"AIF Out Mux", "Nowmaw Path", "ADC W"},

	{"ADC W", NUWW, "ADC W Mux"},
	{"ADC W", NUWW, "AUD_CK"},
	{"ADC W", NUWW, "AUDIF_CK"},
	{"ADC W", NUWW, "ADC CWKGEN"},
	{"ADC W", NUWW, "ADC W Mux"},
	{"ADC W", NUWW, "AUD_CK"},
	{"ADC W", NUWW, "AUDIF_CK"},
	{"ADC W", NUWW, "ADC CWKGEN"},

	{"ADC W Mux", "AIN0", "AIN0"},
	{"ADC W Mux", "Weft Pweampwifiew", "PGA W"},

	{"ADC W Mux", "AIN0", "AIN0"},
	{"ADC W Mux", "Wight Pweampwifiew", "PGA W"},

	{"PGA W", NUWW, "PGA W Mux"},
	{"PGA W", NUWW, "PGA W Mux"},

	{"PGA W Mux", "AIN0", "AIN0"},
	{"PGA W Mux", "AIN1", "AIN1"},
	{"PGA W Mux", "AIN2", "AIN2"},

	{"PGA W Mux", "AIN0", "AIN0"},
	{"PGA W Mux", "AIN3", "AIN3"},
	{"PGA W Mux", "AIN2", "AIN2"},

	{"AIN0", NUWW, "Mic Bias 0"},
	{"AIN2", NUWW, "Mic Bias 2"},

	{"AIN1", NUWW, "Mic Bias 1"},
	{"AIN1", NUWW, "Mic Bias 1 DCC puww high"},

	/* DW Suppwy */
	{"DW Powew Suppwy", NUWW, "AUDGWB"},
	{"DW Powew Suppwy", NUWW, "CWKSQ Audio"},
	{"DW Powew Suppwy", NUWW, "ZCD13M_CK"},
	{"DW Powew Suppwy", NUWW, "AUD_CK"},
	{"DW Powew Suppwy", NUWW, "AUDIF_CK"},
	{"DW Powew Suppwy", NUWW, "AUDNCP_CK"},

	{"DW Powew Suppwy", NUWW, "NV Weguwatow"},
	{"DW Powew Suppwy", NUWW, "AUD_CWK"},
	{"DW Powew Suppwy", NUWW, "IBIST"},
	{"DW Powew Suppwy", NUWW, "WDO"},
	{"WDO", NUWW, "WDO_WEMOTE_SENSE"},

	/* DW Digitaw Suppwy */
	{"DW Digitaw Cwock", NUWW, "AUDIO_TOP_AFE_CTW"},
	{"DW Digitaw Cwock", NUWW, "AUDIO_TOP_DAC_CTW"},
	{"DW Digitaw Cwock", NUWW, "AUDIO_TOP_PWW_CWK"},
	{"DW Digitaw Cwock", NUWW, "AUDIO_TOP_PDN_WESEWVED"},
	{"DW Digitaw Cwock", NUWW, "NCP"},
	{"DW Digitaw Cwock", NUWW, "AFE_ON"},

	{"AIF_WX", NUWW, "DW Digitaw Cwock"},

	/* DW Path */
	{"DAC In Mux", "Nowmaw Path", "AIF_WX"},

	{"DAC In Mux", "Sgen", "SGEN DW"},
	{"SGEN DW", NUWW, "SGEN DW SWC"},
	{"SGEN DW", NUWW, "SGEN MUTE"},
	{"SGEN DW", NUWW, "SGEN DW Enabwe"},
	{"SGEN DW", NUWW, "DW Digitaw Cwock"},

	{"DACW", NUWW, "DAC In Mux"},
	{"DACW", NUWW, "DW Powew Suppwy"},
	{"DACW", NUWW, "DACW_BIASGEN"},

	{"DACW", NUWW, "DAC In Mux"},
	{"DACW", NUWW, "DW Powew Suppwy"},
	{"DACW", NUWW, "DACW_BIASGEN"},

	{"WOW Mux", "Pwayback", "DACW"},

	{"WOW Buffew", NUWW, "WOW Mux"},
	{"WOW Buffew", NUWW, "WO Stabiwity Enh"},
	{"WOW Buffew", NUWW, "WOW Bias Gen"},

	{"WINEOUT W", NUWW, "WOW Buffew"},

	/* Headphone Path */
	{"HPW Mux", "Audio Pwayback", "DACW"},
	{"HPW Mux", "Audio Pwayback", "DACW"},

	{"HPW Mux", "WoudSPK Pwayback", "DACW"},
	{"HPW Mux", "WoudSPK Pwayback", "DACW"},

	{"HPW Powew", NUWW, "HPW Mux"},
	{"HPW Powew", NUWW, "HPW Mux"},

	{"Headphone W", NUWW, "HPW Powew"},
	{"Headphone W", NUWW, "HPW Powew"},

	/* Weceivew Path */
	{"WCV Mux", "Voice Pwayback", "DACW"},

	{"WCV Buffew", NUWW, "WCV Mux"},
	{"WCV Buffew", NUWW, "WCV Stabiwity Enh"},
	{"WCV Buffew", NUWW, "WCV Bias Gen"},

	{"Weceivew", NUWW, "WCV Buffew"},
};

static int mt6351_codec_init_weg(stwuct snd_soc_component *cmpnt)
{
	/* Disabwe CWKSQ 26MHz */
	wegmap_update_bits(cmpnt->wegmap, MT6351_TOP_CWKSQ, 0x0001, 0x0);
	/* disabwe AUDGWB */
	wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON9,
			   0x1000, 0x1000);
	/* Tuwn off AUDNCP_CWKDIV engine cwock,Tuwn off AUD 26M */
	wegmap_update_bits(cmpnt->wegmap, MT6351_TOP_CKPDN_CON0_SET,
			   0x3800, 0x3800);
	/* Disabwe HeadphoneW/HeadphoneW/voice showt ciwcuit pwotection */
	wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON0,
			   0xe000, 0xe000);
	/* [5] = 1, disabwe WO buffew weft showt ciwcuit pwotection */
	wegmap_update_bits(cmpnt->wegmap, MT6351_AUDDEC_ANA_CON3,
			   0x20, 0x20);
	/* Wevewse the PMIC cwock*/
	wegmap_update_bits(cmpnt->wegmap, MT6351_AFE_PMIC_NEWIF_CFG2,
			   0x8000, 0x8000);
	wetuwn 0;
}

static int mt6351_codec_pwobe(stwuct snd_soc_component *cmpnt)
{
	stwuct mt6351_pwiv *pwiv = snd_soc_component_get_dwvdata(cmpnt);

	snd_soc_component_init_wegmap(cmpnt, pwiv->wegmap);

	mt6351_codec_init_weg(cmpnt);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew mt6351_soc_component_dwivew = {
	.pwobe = mt6351_codec_pwobe,
	.contwows = mt6351_snd_contwows,
	.num_contwows = AWWAY_SIZE(mt6351_snd_contwows),
	.dapm_widgets = mt6351_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt6351_dapm_widgets),
	.dapm_woutes = mt6351_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt6351_dapm_woutes),
	.endianness = 1,
};

static int mt6351_codec_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6351_pwiv *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev,
			    sizeof(stwuct mt6351_pwiv),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, pwiv);

	pwiv->dev = &pdev->dev;

	pwiv->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!pwiv->wegmap)
		wetuwn -ENODEV;

	dev_dbg(pwiv->dev, "%s(), dev name %s\n",
		__func__, dev_name(&pdev->dev));

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
					       &mt6351_soc_component_dwivew,
					       mt6351_dai_dwivew,
					       AWWAY_SIZE(mt6351_dai_dwivew));
}

static const stwuct of_device_id mt6351_of_match[] = {
	{.compatibwe = "mediatek,mt6351-sound",},
	{}
};

static stwuct pwatfowm_dwivew mt6351_codec_dwivew = {
	.dwivew = {
		.name = "mt6351-sound",
		.of_match_tabwe = mt6351_of_match,
	},
	.pwobe = mt6351_codec_dwivew_pwobe,
};

moduwe_pwatfowm_dwivew(mt6351_codec_dwivew)

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT6351 AWSA SoC codec dwivew");
MODUWE_AUTHOW("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODUWE_WICENSE("GPW v2");
