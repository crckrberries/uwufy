// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt5651.c  --  WT5651 AWSA SoC audio codec dwivew
 *
 * Copywight 2014 Weawtek Semiconductow Cowp.
 * Authow: Bawd Wiao <bawdwiao@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/acpi.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/jack.h>

#incwude "ww6231.h"
#incwude "wt5651.h"

#define WT5651_DEVICE_ID_VAWUE 0x6281

#define WT5651_PW_WANGE_BASE (0xff + 1)
#define WT5651_PW_SPACING 0x100

#define WT5651_PW_BASE (WT5651_PW_WANGE_BASE + (0 * WT5651_PW_SPACING))

static const stwuct wegmap_wange_cfg wt5651_wanges[] = {
	{ .name = "PW", .wange_min = WT5651_PW_BASE,
	  .wange_max = WT5651_PW_BASE + 0xb4,
	  .sewectow_weg = WT5651_PWIV_INDEX,
	  .sewectow_mask = 0xff,
	  .sewectow_shift = 0x0,
	  .window_stawt = WT5651_PWIV_DATA,
	  .window_wen = 0x1, },
};

static const stwuct weg_sequence init_wist[] = {
	{WT5651_PW_BASE + 0x3d,	0x3e00},
};

static const stwuct weg_defauwt wt5651_weg[] = {
	{ 0x00, 0x0000 },
	{ 0x02, 0xc8c8 },
	{ 0x03, 0xc8c8 },
	{ 0x05, 0x0000 },
	{ 0x0d, 0x0000 },
	{ 0x0e, 0x0000 },
	{ 0x0f, 0x0808 },
	{ 0x10, 0x0808 },
	{ 0x19, 0xafaf },
	{ 0x1a, 0xafaf },
	{ 0x1b, 0x0c00 },
	{ 0x1c, 0x2f2f },
	{ 0x1d, 0x2f2f },
	{ 0x1e, 0x0000 },
	{ 0x27, 0x7860 },
	{ 0x28, 0x7070 },
	{ 0x29, 0x8080 },
	{ 0x2a, 0x5252 },
	{ 0x2b, 0x5454 },
	{ 0x2f, 0x0000 },
	{ 0x30, 0x5000 },
	{ 0x3b, 0x0000 },
	{ 0x3c, 0x006f },
	{ 0x3d, 0x0000 },
	{ 0x3e, 0x006f },
	{ 0x45, 0x6000 },
	{ 0x4d, 0x0000 },
	{ 0x4e, 0x0000 },
	{ 0x4f, 0x0279 },
	{ 0x50, 0x0000 },
	{ 0x51, 0x0000 },
	{ 0x52, 0x0279 },
	{ 0x53, 0xf000 },
	{ 0x61, 0x0000 },
	{ 0x62, 0x0000 },
	{ 0x63, 0x00c0 },
	{ 0x64, 0x0000 },
	{ 0x65, 0x0000 },
	{ 0x66, 0x0000 },
	{ 0x70, 0x8000 },
	{ 0x71, 0x8000 },
	{ 0x73, 0x1104 },
	{ 0x74, 0x0c00 },
	{ 0x75, 0x1400 },
	{ 0x77, 0x0c00 },
	{ 0x78, 0x4000 },
	{ 0x79, 0x0123 },
	{ 0x80, 0x0000 },
	{ 0x81, 0x0000 },
	{ 0x82, 0x0000 },
	{ 0x83, 0x0800 },
	{ 0x84, 0x0000 },
	{ 0x85, 0x0008 },
	{ 0x89, 0x0000 },
	{ 0x8e, 0x0004 },
	{ 0x8f, 0x1100 },
	{ 0x90, 0x0000 },
	{ 0x93, 0x2000 },
	{ 0x94, 0x0200 },
	{ 0xb0, 0x2080 },
	{ 0xb1, 0x0000 },
	{ 0xb4, 0x2206 },
	{ 0xb5, 0x1f00 },
	{ 0xb6, 0x0000 },
	{ 0xbb, 0x0000 },
	{ 0xbc, 0x0000 },
	{ 0xbd, 0x0000 },
	{ 0xbe, 0x0000 },
	{ 0xbf, 0x0000 },
	{ 0xc0, 0x0400 },
	{ 0xc1, 0x0000 },
	{ 0xc2, 0x0000 },
	{ 0xcf, 0x0013 },
	{ 0xd0, 0x0680 },
	{ 0xd1, 0x1c17 },
	{ 0xd3, 0xb320 },
	{ 0xd9, 0x0809 },
	{ 0xfa, 0x0010 },
	{ 0xfe, 0x10ec },
	{ 0xff, 0x6281 },
};

static boow wt5651_vowatiwe_wegistew(stwuct device *dev,  unsigned int weg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wt5651_wanges); i++) {
		if ((weg >= wt5651_wanges[i].window_stawt &&
		     weg <= wt5651_wanges[i].window_stawt +
		     wt5651_wanges[i].window_wen) ||
		    (weg >= wt5651_wanges[i].wange_min &&
		     weg <= wt5651_wanges[i].wange_max)) {
			wetuwn twue;
		}
	}

	switch (weg) {
	case WT5651_WESET:
	case WT5651_PWIV_DATA:
	case WT5651_EQ_CTWW1:
	case WT5651_AWC_1:
	case WT5651_IWQ_CTWW2:
	case WT5651_INT_IWQ_ST:
	case WT5651_PGM_WEG_AWW1:
	case WT5651_PGM_WEG_AWW3:
	case WT5651_VENDOW_ID:
	case WT5651_DEVICE_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt5651_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wt5651_wanges); i++) {
		if ((weg >= wt5651_wanges[i].window_stawt &&
		     weg <= wt5651_wanges[i].window_stawt +
		     wt5651_wanges[i].window_wen) ||
		    (weg >= wt5651_wanges[i].wange_min &&
		     weg <= wt5651_wanges[i].wange_max)) {
			wetuwn twue;
		}
	}

	switch (weg) {
	case WT5651_WESET:
	case WT5651_VEWSION_ID:
	case WT5651_VENDOW_ID:
	case WT5651_DEVICE_ID:
	case WT5651_HP_VOW:
	case WT5651_WOUT_CTWW1:
	case WT5651_WOUT_CTWW2:
	case WT5651_IN1_IN2:
	case WT5651_IN3:
	case WT5651_INW1_INW1_VOW:
	case WT5651_INW2_INW2_VOW:
	case WT5651_DAC1_DIG_VOW:
	case WT5651_DAC2_DIG_VOW:
	case WT5651_DAC2_CTWW:
	case WT5651_ADC_DIG_VOW:
	case WT5651_ADC_DATA:
	case WT5651_ADC_BST_VOW:
	case WT5651_STO1_ADC_MIXEW:
	case WT5651_STO2_ADC_MIXEW:
	case WT5651_AD_DA_MIXEW:
	case WT5651_STO_DAC_MIXEW:
	case WT5651_DD_MIXEW:
	case WT5651_DIG_INF_DATA:
	case WT5651_PDM_CTW:
	case WT5651_WEC_W1_MIXEW:
	case WT5651_WEC_W2_MIXEW:
	case WT5651_WEC_W1_MIXEW:
	case WT5651_WEC_W2_MIXEW:
	case WT5651_HPO_MIXEW:
	case WT5651_OUT_W1_MIXEW:
	case WT5651_OUT_W2_MIXEW:
	case WT5651_OUT_W3_MIXEW:
	case WT5651_OUT_W1_MIXEW:
	case WT5651_OUT_W2_MIXEW:
	case WT5651_OUT_W3_MIXEW:
	case WT5651_WOUT_MIXEW:
	case WT5651_PWW_DIG1:
	case WT5651_PWW_DIG2:
	case WT5651_PWW_ANWG1:
	case WT5651_PWW_ANWG2:
	case WT5651_PWW_MIXEW:
	case WT5651_PWW_VOW:
	case WT5651_PWIV_INDEX:
	case WT5651_PWIV_DATA:
	case WT5651_I2S1_SDP:
	case WT5651_I2S2_SDP:
	case WT5651_ADDA_CWK1:
	case WT5651_ADDA_CWK2:
	case WT5651_DMIC:
	case WT5651_TDM_CTW_1:
	case WT5651_TDM_CTW_2:
	case WT5651_TDM_CTW_3:
	case WT5651_GWB_CWK:
	case WT5651_PWW_CTWW1:
	case WT5651_PWW_CTWW2:
	case WT5651_PWW_MODE_1:
	case WT5651_PWW_MODE_2:
	case WT5651_PWW_MODE_3:
	case WT5651_PWW_MODE_4:
	case WT5651_PWW_MODE_5:
	case WT5651_PWW_MODE_6:
	case WT5651_PWW_MODE_7:
	case WT5651_DEPOP_M1:
	case WT5651_DEPOP_M2:
	case WT5651_DEPOP_M3:
	case WT5651_CHAWGE_PUMP:
	case WT5651_MICBIAS:
	case WT5651_A_JD_CTW1:
	case WT5651_EQ_CTWW1:
	case WT5651_EQ_CTWW2:
	case WT5651_AWC_1:
	case WT5651_AWC_2:
	case WT5651_AWC_3:
	case WT5651_JD_CTWW1:
	case WT5651_JD_CTWW2:
	case WT5651_IWQ_CTWW1:
	case WT5651_IWQ_CTWW2:
	case WT5651_INT_IWQ_ST:
	case WT5651_GPIO_CTWW1:
	case WT5651_GPIO_CTWW2:
	case WT5651_GPIO_CTWW3:
	case WT5651_PGM_WEG_AWW1:
	case WT5651_PGM_WEG_AWW2:
	case WT5651_PGM_WEG_AWW3:
	case WT5651_PGM_WEG_AWW4:
	case WT5651_PGM_WEG_AWW5:
	case WT5651_SCB_FUNC:
	case WT5651_SCB_CTWW:
	case WT5651_BASE_BACK:
	case WT5651_MP3_PWUS1:
	case WT5651_MP3_PWUS2:
	case WT5651_ADJ_HPF_CTWW1:
	case WT5651_ADJ_HPF_CTWW2:
	case WT5651_HP_CAWIB_AMP_DET:
	case WT5651_HP_CAWIB2:
	case WT5651_SV_ZCD1:
	case WT5651_SV_ZCD2:
	case WT5651_D_MISC:
	case WT5651_DUMMY2:
	case WT5651_DUMMY3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -4650, 150, 0);
static const DECWAWE_TWV_DB_MINMAX(dac_vow_twv, -6562, 0);
static const DECWAWE_TWV_DB_SCAWE(in_vow_twv, -3450, 150, 0);
static const DECWAWE_TWV_DB_MINMAX(adc_vow_twv, -1762, 3000);
static const DECWAWE_TWV_DB_SCAWE(adc_bst_twv, 0, 1200, 0);

/* {0, +20, +24, +30, +35, +40, +44, +50, +52} dB */
static const DECWAWE_TWV_DB_WANGE(bst_twv,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(2000, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(2400, 0, 0),
	3, 5, TWV_DB_SCAWE_ITEM(3000, 500, 0),
	6, 6, TWV_DB_SCAWE_ITEM(4400, 0, 0),
	7, 7, TWV_DB_SCAWE_ITEM(5000, 0, 0),
	8, 8, TWV_DB_SCAWE_ITEM(5200, 0, 0)
);

/* Intewface data sewect */
static const chaw * const wt5651_data_sewect[] = {
	"Nowmaw", "Swap", "weft copy to wight", "wight copy to weft"};

static SOC_ENUM_SINGWE_DECW(wt5651_if2_dac_enum, WT5651_DIG_INF_DATA,
				WT5651_IF2_DAC_SEW_SFT, wt5651_data_sewect);

static SOC_ENUM_SINGWE_DECW(wt5651_if2_adc_enum, WT5651_DIG_INF_DATA,
				WT5651_IF2_ADC_SEW_SFT, wt5651_data_sewect);

static const stwuct snd_kcontwow_new wt5651_snd_contwows[] = {
	/* Headphone Output Vowume */
	SOC_DOUBWE_TWV("HP Pwayback Vowume", WT5651_HP_VOW,
		WT5651_W_VOW_SFT, WT5651_W_VOW_SFT, 39, 1, out_vow_twv),
	/* OUTPUT Contwow */
	SOC_DOUBWE_TWV("OUT Pwayback Vowume", WT5651_WOUT_CTWW1,
		WT5651_W_VOW_SFT, WT5651_W_VOW_SFT, 39, 1, out_vow_twv),

	/* DAC Digitaw Vowume */
	SOC_DOUBWE("DAC2 Pwayback Switch", WT5651_DAC2_CTWW,
		WT5651_M_DAC_W2_VOW_SFT, WT5651_M_DAC_W2_VOW_SFT, 1, 1),
	SOC_DOUBWE_TWV("DAC1 Pwayback Vowume", WT5651_DAC1_DIG_VOW,
			WT5651_W_VOW_SFT, WT5651_W_VOW_SFT,
			175, 0, dac_vow_twv),
	SOC_DOUBWE_TWV("Mono DAC Pwayback Vowume", WT5651_DAC2_DIG_VOW,
			WT5651_W_VOW_SFT, WT5651_W_VOW_SFT,
			175, 0, dac_vow_twv),
	/* IN1/IN2/IN3 Contwow */
	SOC_SINGWE_TWV("IN1 Boost", WT5651_IN1_IN2,
		WT5651_BST_SFT1, 8, 0, bst_twv),
	SOC_SINGWE_TWV("IN2 Boost", WT5651_IN1_IN2,
		WT5651_BST_SFT2, 8, 0, bst_twv),
	SOC_SINGWE_TWV("IN3 Boost", WT5651_IN3,
		WT5651_BST_SFT1, 8, 0, bst_twv),
	/* INW/INW Vowume Contwow */
	SOC_DOUBWE_TWV("IN Captuwe Vowume", WT5651_INW1_INW1_VOW,
			WT5651_INW_VOW_SFT, WT5651_INW_VOW_SFT,
			31, 1, in_vow_twv),
	/* ADC Digitaw Vowume Contwow */
	SOC_DOUBWE("ADC Captuwe Switch", WT5651_ADC_DIG_VOW,
		WT5651_W_MUTE_SFT, WT5651_W_MUTE_SFT, 1, 1),
	SOC_DOUBWE_TWV("ADC Captuwe Vowume", WT5651_ADC_DIG_VOW,
			WT5651_W_VOW_SFT, WT5651_W_VOW_SFT,
			127, 0, adc_vow_twv),
	SOC_DOUBWE_TWV("Mono ADC Captuwe Vowume", WT5651_ADC_DATA,
			WT5651_W_VOW_SFT, WT5651_W_VOW_SFT,
			127, 0, adc_vow_twv),
	/* ADC Boost Vowume Contwow */
	SOC_DOUBWE_TWV("ADC Boost Gain", WT5651_ADC_BST_VOW,
			WT5651_ADC_W_BST_SFT, WT5651_ADC_W_BST_SFT,
			3, 0, adc_bst_twv),

	/* ASWC */
	SOC_SINGWE("IF1 ASWC Switch", WT5651_PWW_MODE_1,
		WT5651_STO1_T_SFT, 1, 0),
	SOC_SINGWE("IF2 ASWC Switch", WT5651_PWW_MODE_1,
		WT5651_STO2_T_SFT, 1, 0),
	SOC_SINGWE("DMIC ASWC Switch", WT5651_PWW_MODE_1,
		WT5651_DMIC_1_M_SFT, 1, 0),

	SOC_ENUM("ADC IF2 Data Switch", wt5651_if2_adc_enum),
	SOC_ENUM("DAC IF2 Data Switch", wt5651_if2_dac_enum),
};

/**
 * set_dmic_cwk - Set pawametew of dmic.
 *
 * @w: DAPM widget.
 * @kcontwow: The kcontwow of this widget.
 * @event: Event id.
 *
 */
static int set_dmic_cwk(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	int idx, wate;

	wate = wt5651->syscwk / ww6231_get_pwe_div(wt5651->wegmap,
		WT5651_ADDA_CWK1, WT5651_I2S_PD1_SFT);
	idx = ww6231_cawc_dmic_cwk(wate);
	if (idx < 0)
		dev_eww(component->dev, "Faiwed to set DMIC cwock\n");
	ewse
		snd_soc_component_update_bits(component, WT5651_DMIC, WT5651_DMIC_CWK_MASK,
					idx << WT5651_DMIC_CWK_SFT);

	wetuwn idx;
}

/* Digitaw Mixew */
static const stwuct snd_kcontwow_new wt5651_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5651_STO1_ADC_MIXEW,
			WT5651_M_STO1_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5651_STO1_ADC_MIXEW,
			WT5651_M_STO1_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5651_STO1_ADC_MIXEW,
			WT5651_M_STO1_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5651_STO1_ADC_MIXEW,
			WT5651_M_STO1_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_sto2_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5651_STO2_ADC_MIXEW,
			WT5651_M_STO2_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5651_STO2_ADC_MIXEW,
			WT5651_M_STO2_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_sto2_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5651_STO2_ADC_MIXEW,
			WT5651_M_STO2_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5651_STO2_ADC_MIXEW,
			WT5651_M_STO2_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_dac_w_mix[] = {
	SOC_DAPM_SINGWE("Steweo ADC Switch", WT5651_AD_DA_MIXEW,
			WT5651_M_ADCMIX_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INF1 Switch", WT5651_AD_DA_MIXEW,
			WT5651_M_IF1_DAC_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_dac_w_mix[] = {
	SOC_DAPM_SINGWE("Steweo ADC Switch", WT5651_AD_DA_MIXEW,
			WT5651_M_ADCMIX_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INF1 Switch", WT5651_AD_DA_MIXEW,
			WT5651_M_IF1_DAC_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_sto_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_STO_DAC_MIXEW,
			WT5651_M_DAC_W1_MIXW_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5651_STO_DAC_MIXEW,
			WT5651_M_DAC_W2_MIXW_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_STO_DAC_MIXEW,
			WT5651_M_DAC_W1_MIXW_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_sto_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_STO_DAC_MIXEW,
			WT5651_M_DAC_W1_MIXW_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5651_STO_DAC_MIXEW,
			WT5651_M_DAC_W2_MIXW_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_STO_DAC_MIXEW,
			WT5651_M_DAC_W1_MIXW_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_dd_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_DD_MIXEW,
			WT5651_M_STO_DD_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5651_DD_MIXEW,
			WT5651_M_STO_DD_W2_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5651_DD_MIXEW,
			WT5651_M_STO_DD_W2_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_dd_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_DD_MIXEW,
			WT5651_M_STO_DD_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5651_DD_MIXEW,
			WT5651_M_STO_DD_W2_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5651_DD_MIXEW,
			WT5651_M_STO_DD_W2_W_SFT, 1, 1),
};

/* Anawog Input Mixew */
static const stwuct snd_kcontwow_new wt5651_wec_w_mix[] = {
	SOC_DAPM_SINGWE("INW1 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_IN1_W_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST3 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_BST3_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST2 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_BST2_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_BST1_WM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_wec_w_mix[] = {
	SOC_DAPM_SINGWE("INW1 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_IN1_W_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST3 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_BST3_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST2 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_BST2_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 Switch", WT5651_WEC_W2_MIXEW,
			WT5651_M_BST1_WM_W_SFT, 1, 1),
};

/* Anawog Output Mixew */

static const stwuct snd_kcontwow_new wt5651_out_w_mix[] = {
	SOC_DAPM_SINGWE("BST1 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_BST1_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST2 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_BST2_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW1 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_IN1_W_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("WEC MIXW Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_WM_W_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_DAC_W1_OM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_out_w_mix[] = {
	SOC_DAPM_SINGWE("BST2 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_BST2_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_BST1_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW1 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_IN1_W_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("WEC MIXW Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_WM_W_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_OUT_W3_MIXEW,
			WT5651_M_DAC_W1_OM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_hpo_mix[] = {
	SOC_DAPM_SINGWE("HPO MIX DAC1 Switch", WT5651_HPO_MIXEW,
			WT5651_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGWE("HPO MIX HPVOW Switch", WT5651_HPO_MIXEW,
			WT5651_M_HPVOW_HM_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5651_wout_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_WOUT_MIXEW,
			WT5651_M_DAC_W1_WM_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5651_WOUT_MIXEW,
			WT5651_M_DAC_W1_WM_SFT, 1, 1),
	SOC_DAPM_SINGWE("OUTVOW W Switch", WT5651_WOUT_MIXEW,
			WT5651_M_OV_W_WM_SFT, 1, 1),
	SOC_DAPM_SINGWE("OUTVOW W Switch", WT5651_WOUT_MIXEW,
			WT5651_M_OV_W_WM_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new outvow_w_contwow =
	SOC_DAPM_SINGWE("Switch", WT5651_WOUT_CTWW1,
			WT5651_VOW_W_SFT, 1, 1);

static const stwuct snd_kcontwow_new outvow_w_contwow =
	SOC_DAPM_SINGWE("Switch", WT5651_WOUT_CTWW1,
			WT5651_VOW_W_SFT, 1, 1);

static const stwuct snd_kcontwow_new wout_w_mute_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5651_WOUT_CTWW1,
				    WT5651_W_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new wout_w_mute_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5651_WOUT_CTWW1,
				    WT5651_W_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new hpovow_w_contwow =
	SOC_DAPM_SINGWE("Switch", WT5651_HP_VOW,
			WT5651_VOW_W_SFT, 1, 1);

static const stwuct snd_kcontwow_new hpovow_w_contwow =
	SOC_DAPM_SINGWE("Switch", WT5651_HP_VOW,
			WT5651_VOW_W_SFT, 1, 1);

static const stwuct snd_kcontwow_new hpo_w_mute_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5651_HP_VOW,
				    WT5651_W_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new hpo_w_mute_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5651_HP_VOW,
				    WT5651_W_MUTE_SFT, 1, 1);

/* Steweo ADC souwce */
static const chaw * const wt5651_steweo1_adc1_swc[] = {"DD MIX", "ADC"};

static SOC_ENUM_SINGWE_DECW(
	wt5651_steweo1_adc1_enum, WT5651_STO1_ADC_MIXEW,
	WT5651_STO1_ADC_1_SWC_SFT, wt5651_steweo1_adc1_swc);

static const stwuct snd_kcontwow_new wt5651_sto1_adc_w1_mux =
	SOC_DAPM_ENUM("Steweo1 ADC W1 souwce", wt5651_steweo1_adc1_enum);

static const stwuct snd_kcontwow_new wt5651_sto1_adc_w1_mux =
	SOC_DAPM_ENUM("Steweo1 ADC W1 souwce", wt5651_steweo1_adc1_enum);

static const chaw * const wt5651_steweo1_adc2_swc[] = {"DMIC", "DD MIX"};

static SOC_ENUM_SINGWE_DECW(
	wt5651_steweo1_adc2_enum, WT5651_STO1_ADC_MIXEW,
	WT5651_STO1_ADC_2_SWC_SFT, wt5651_steweo1_adc2_swc);

static const stwuct snd_kcontwow_new wt5651_sto1_adc_w2_mux =
	SOC_DAPM_ENUM("Steweo1 ADC W2 souwce", wt5651_steweo1_adc2_enum);

static const stwuct snd_kcontwow_new wt5651_sto1_adc_w2_mux =
	SOC_DAPM_ENUM("Steweo1 ADC W2 souwce", wt5651_steweo1_adc2_enum);

/* Mono ADC souwce */
static const chaw * const wt5651_sto2_adc_w1_swc[] = {"DD MIXW", "ADCW"};

static SOC_ENUM_SINGWE_DECW(
	wt5651_sto2_adc_w1_enum, WT5651_STO1_ADC_MIXEW,
	WT5651_STO2_ADC_W1_SWC_SFT, wt5651_sto2_adc_w1_swc);

static const stwuct snd_kcontwow_new wt5651_sto2_adc_w1_mux =
	SOC_DAPM_ENUM("Steweo2 ADC1 weft souwce", wt5651_sto2_adc_w1_enum);

static const chaw * const wt5651_sto2_adc_w2_swc[] = {"DMIC W", "DD MIXW"};

static SOC_ENUM_SINGWE_DECW(
	wt5651_sto2_adc_w2_enum, WT5651_STO1_ADC_MIXEW,
	WT5651_STO2_ADC_W2_SWC_SFT, wt5651_sto2_adc_w2_swc);

static const stwuct snd_kcontwow_new wt5651_sto2_adc_w2_mux =
	SOC_DAPM_ENUM("Steweo2 ADC2 weft souwce", wt5651_sto2_adc_w2_enum);

static const chaw * const wt5651_sto2_adc_w1_swc[] = {"DD MIXW", "ADCW"};

static SOC_ENUM_SINGWE_DECW(
	wt5651_sto2_adc_w1_enum, WT5651_STO1_ADC_MIXEW,
	WT5651_STO2_ADC_W1_SWC_SFT, wt5651_sto2_adc_w1_swc);

static const stwuct snd_kcontwow_new wt5651_sto2_adc_w1_mux =
	SOC_DAPM_ENUM("Steweo2 ADC1 wight souwce", wt5651_sto2_adc_w1_enum);

static const chaw * const wt5651_sto2_adc_w2_swc[] = {"DMIC W", "DD MIXW"};

static SOC_ENUM_SINGWE_DECW(
	wt5651_sto2_adc_w2_enum, WT5651_STO1_ADC_MIXEW,
	WT5651_STO2_ADC_W2_SWC_SFT, wt5651_sto2_adc_w2_swc);

static const stwuct snd_kcontwow_new wt5651_sto2_adc_w2_mux =
	SOC_DAPM_ENUM("Steweo2 ADC2 wight souwce", wt5651_sto2_adc_w2_enum);

/* DAC2 channew souwce */

static const chaw * const wt5651_dac_swc[] = {"IF1", "IF2"};

static SOC_ENUM_SINGWE_DECW(wt5651_dac_w2_enum, WT5651_DAC2_CTWW,
				WT5651_SEW_DAC_W2_SFT, wt5651_dac_swc);

static const stwuct snd_kcontwow_new wt5651_dac_w2_mux =
	SOC_DAPM_ENUM("DAC2 weft channew souwce", wt5651_dac_w2_enum);

static SOC_ENUM_SINGWE_DECW(
	wt5651_dac_w2_enum, WT5651_DAC2_CTWW,
	WT5651_SEW_DAC_W2_SFT, wt5651_dac_swc);

static const stwuct snd_kcontwow_new wt5651_dac_w2_mux =
	SOC_DAPM_ENUM("DAC2 wight channew souwce", wt5651_dac_w2_enum);

/* IF2_ADC channew souwce */

static const chaw * const wt5651_adc_swc[] = {"IF1 ADC1", "IF1 ADC2"};

static SOC_ENUM_SINGWE_DECW(wt5651_if2_adc_swc_enum, WT5651_DIG_INF_DATA,
				WT5651_IF2_ADC_SWC_SFT, wt5651_adc_swc);

static const stwuct snd_kcontwow_new wt5651_if2_adc_swc_mux =
	SOC_DAPM_ENUM("IF2 ADC channew souwce", wt5651_if2_adc_swc_enum);

/* PDM sewect */
static const chaw * const wt5651_pdm_sew[] = {"DD MIX", "Steweo DAC MIX"};

static SOC_ENUM_SINGWE_DECW(
	wt5651_pdm_w_sew_enum, WT5651_PDM_CTW,
	WT5651_PDM_W_SEW_SFT, wt5651_pdm_sew);

static SOC_ENUM_SINGWE_DECW(
	wt5651_pdm_w_sew_enum, WT5651_PDM_CTW,
	WT5651_PDM_W_SEW_SFT, wt5651_pdm_sew);

static const stwuct snd_kcontwow_new wt5651_pdm_w_mux =
	SOC_DAPM_ENUM("PDM W sewect", wt5651_pdm_w_sew_enum);

static const stwuct snd_kcontwow_new wt5651_pdm_w_mux =
	SOC_DAPM_ENUM("PDM W sewect", wt5651_pdm_w_sew_enum);

static int wt5651_amp_powew_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* depop pawametews */
		wegmap_update_bits(wt5651->wegmap, WT5651_PW_BASE +
			WT5651_CHPUMP_INT_WEG1, 0x0700, 0x0200);
		wegmap_update_bits(wt5651->wegmap, WT5651_DEPOP_M2,
			WT5651_DEPOP_MASK, WT5651_DEPOP_MAN);
		wegmap_update_bits(wt5651->wegmap, WT5651_DEPOP_M1,
			WT5651_HP_CP_MASK | WT5651_HP_SG_MASK |
			WT5651_HP_CB_MASK, WT5651_HP_CP_PU |
			WT5651_HP_SG_DIS | WT5651_HP_CB_PU);
		wegmap_wwite(wt5651->wegmap, WT5651_PW_BASE +
				WT5651_HP_DCC_INT1, 0x9f00);
		/* headphone amp powew on */
		wegmap_update_bits(wt5651->wegmap, WT5651_PWW_ANWG1,
			WT5651_PWW_FV1 | WT5651_PWW_FV2, 0);
		wegmap_update_bits(wt5651->wegmap, WT5651_PWW_ANWG1,
			WT5651_PWW_HA,
			WT5651_PWW_HA);
		usweep_wange(10000, 15000);
		wegmap_update_bits(wt5651->wegmap, WT5651_PWW_ANWG1,
			WT5651_PWW_FV1 | WT5651_PWW_FV2 ,
			WT5651_PWW_FV1 | WT5651_PWW_FV2);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5651_hp_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* headphone unmute sequence */
		wegmap_update_bits(wt5651->wegmap, WT5651_DEPOP_M2,
			WT5651_DEPOP_MASK | WT5651_DIG_DP_MASK,
			WT5651_DEPOP_AUTO | WT5651_DIG_DP_EN);
		wegmap_update_bits(wt5651->wegmap, WT5651_CHAWGE_PUMP,
			WT5651_PM_HP_MASK, WT5651_PM_HP_HV);

		wegmap_update_bits(wt5651->wegmap, WT5651_DEPOP_M3,
			WT5651_CP_FQ1_MASK | WT5651_CP_FQ2_MASK |
			WT5651_CP_FQ3_MASK,
			(WT5651_CP_FQ_192_KHZ << WT5651_CP_FQ1_SFT) |
			(WT5651_CP_FQ_12_KHZ << WT5651_CP_FQ2_SFT) |
			(WT5651_CP_FQ_192_KHZ << WT5651_CP_FQ3_SFT));

		wegmap_wwite(wt5651->wegmap, WT5651_PW_BASE +
			WT5651_MAMP_INT_WEG2, 0x1c00);
		wegmap_update_bits(wt5651->wegmap, WT5651_DEPOP_M1,
			WT5651_HP_CP_MASK | WT5651_HP_SG_MASK,
			WT5651_HP_CP_PD | WT5651_HP_SG_EN);
		wegmap_update_bits(wt5651->wegmap, WT5651_PW_BASE +
			WT5651_CHPUMP_INT_WEG1, 0x0700, 0x0400);
		wt5651->hp_mute = fawse;
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		wt5651->hp_mute = twue;
		usweep_wange(70000, 75000);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5651_hp_post_event(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *kcontwow, int event)
{

	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (!wt5651->hp_mute)
			usweep_wange(80000, 85000);

		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5651_bst1_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
			WT5651_PWW_BST1_OP2, WT5651_PWW_BST1_OP2);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
			WT5651_PWW_BST1_OP2, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5651_bst2_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
			WT5651_PWW_BST2_OP2, WT5651_PWW_BST2_OP2);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
			WT5651_PWW_BST2_OP2, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5651_bst3_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
			WT5651_PWW_BST3_OP2, WT5651_PWW_BST3_OP2);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
			WT5651_PWW_BST3_OP2, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt5651_dapm_widgets[] = {
	/* ASWC */
	SND_SOC_DAPM_SUPPWY_S("I2S1 ASWC", 1, WT5651_PWW_MODE_2,
			      15, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("I2S2 ASWC", 1, WT5651_PWW_MODE_2,
			      14, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("STO1 DAC ASWC", 1, WT5651_PWW_MODE_2,
			      13, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("STO2 DAC ASWC", 1, WT5651_PWW_MODE_2,
			      12, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("ADC ASWC", 1, WT5651_PWW_MODE_2,
			      11, 0, NUWW, 0),

	/* micbias */
	SND_SOC_DAPM_SUPPWY("WDO", WT5651_PWW_ANWG1,
			WT5651_PWW_WDO_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("micbias1", WT5651_PWW_ANWG2,
			WT5651_PWW_MB1_BIT, 0, NUWW, 0),
	/* Input Wines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("MIC3"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),
	SND_SOC_DAPM_INPUT("IN3P"),
	SND_SOC_DAPM_INPUT("DMIC W1"),
	SND_SOC_DAPM_INPUT("DMIC W1"),
	SND_SOC_DAPM_SUPPWY("DMIC CWK", WT5651_DMIC, WT5651_DMIC_1_EN_SFT,
			    0, set_dmic_cwk, SND_SOC_DAPM_PWE_PMU),
	/* Boost */
	SND_SOC_DAPM_PGA_E("BST1", WT5651_PWW_ANWG2,
		WT5651_PWW_BST1_BIT, 0, NUWW, 0, wt5651_bst1_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("BST2", WT5651_PWW_ANWG2,
		WT5651_PWW_BST2_BIT, 0, NUWW, 0, wt5651_bst2_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("BST3", WT5651_PWW_ANWG2,
		WT5651_PWW_BST3_BIT, 0, NUWW, 0, wt5651_bst3_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	/* Input Vowume */
	SND_SOC_DAPM_PGA("INW1 VOW", WT5651_PWW_VOW,
			 WT5651_PWW_IN1_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INW1 VOW", WT5651_PWW_VOW,
			 WT5651_PWW_IN1_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INW2 VOW", WT5651_PWW_VOW,
			 WT5651_PWW_IN2_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INW2 VOW", WT5651_PWW_VOW,
			 WT5651_PWW_IN2_W_BIT, 0, NUWW, 0),

	/* WEC Mixew */
	SND_SOC_DAPM_MIXEW("WECMIXW", WT5651_PWW_MIXEW, WT5651_PWW_WM_W_BIT, 0,
			   wt5651_wec_w_mix, AWWAY_SIZE(wt5651_wec_w_mix)),
	SND_SOC_DAPM_MIXEW("WECMIXW", WT5651_PWW_MIXEW, WT5651_PWW_WM_W_BIT, 0,
			   wt5651_wec_w_mix, AWWAY_SIZE(wt5651_wec_w_mix)),
	/* ADCs */
	SND_SOC_DAPM_ADC("ADC W", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC W", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPWY("ADC W Powew", WT5651_PWW_DIG1,
			    WT5651_PWW_ADC_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC W Powew", WT5651_PWW_DIG1,
			    WT5651_PWW_ADC_W_BIT, 0, NUWW, 0),
	/* ADC Mux */
	SND_SOC_DAPM_MUX("Steweo1 ADC W2 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto1_adc_w2_mux),
	SND_SOC_DAPM_MUX("Steweo1 ADC W2 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto1_adc_w2_mux),
	SND_SOC_DAPM_MUX("Steweo1 ADC W1 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto1_adc_w1_mux),
	SND_SOC_DAPM_MUX("Steweo1 ADC W1 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto1_adc_w1_mux),
	SND_SOC_DAPM_MUX("Steweo2 ADC W2 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto2_adc_w2_mux),
	SND_SOC_DAPM_MUX("Steweo2 ADC W1 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto2_adc_w1_mux),
	SND_SOC_DAPM_MUX("Steweo2 ADC W1 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto2_adc_w1_mux),
	SND_SOC_DAPM_MUX("Steweo2 ADC W2 Mux", SND_SOC_NOPM, 0, 0,
			 &wt5651_sto2_adc_w2_mux),
	/* ADC Mixew */
	SND_SOC_DAPM_SUPPWY("Steweo1 Fiwtew", WT5651_PWW_DIG2,
			    WT5651_PWW_ADC_STO1_F_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Steweo2 Fiwtew", WT5651_PWW_DIG2,
			    WT5651_PWW_ADC_STO2_F_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Steweo1 ADC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_sto1_adc_w_mix,
			   AWWAY_SIZE(wt5651_sto1_adc_w_mix)),
	SND_SOC_DAPM_MIXEW("Steweo1 ADC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_sto1_adc_w_mix,
			   AWWAY_SIZE(wt5651_sto1_adc_w_mix)),
	SND_SOC_DAPM_MIXEW("Steweo2 ADC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_sto2_adc_w_mix,
			   AWWAY_SIZE(wt5651_sto2_adc_w_mix)),
	SND_SOC_DAPM_MIXEW("Steweo2 ADC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_sto2_adc_w_mix,
			   AWWAY_SIZE(wt5651_sto2_adc_w_mix)),

	/* Digitaw Intewface */
	SND_SOC_DAPM_SUPPWY("I2S1", WT5651_PWW_DIG1,
			    WT5651_PWW_I2S1_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 ADC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 ADC2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S2", WT5651_PWW_DIG1,
			    WT5651_PWW_I2S2_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF2 DAC", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF2 DAC W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF2 DAC W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MUX("IF2 ADC", SND_SOC_NOPM, 0, 0,
			 &wt5651_if2_adc_swc_mux),

	/* Digitaw Intewface Sewect */

	SND_SOC_DAPM_MUX("PDM W Mux", WT5651_PDM_CTW,
			 WT5651_M_PDM_W_SFT, 1, &wt5651_pdm_w_mux),
	SND_SOC_DAPM_MUX("PDM W Mux", WT5651_PDM_CTW,
			 WT5651_M_PDM_W_SFT, 1, &wt5651_pdm_w_mux),
	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIF1WX", "AIF1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2WX", "AIF2 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Captuwe", 0, SND_SOC_NOPM, 0, 0),

	/* Audio DSP */
	SND_SOC_DAPM_PGA("Audio DSP", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Output Side */
	/* DAC mixew befowe sound effect  */
	SND_SOC_DAPM_MIXEW("DAC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_dac_w_mix, AWWAY_SIZE(wt5651_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("DAC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_dac_w_mix, AWWAY_SIZE(wt5651_dac_w_mix)),

	/* DAC2 channew Mux */
	SND_SOC_DAPM_MUX("DAC W2 Mux", SND_SOC_NOPM, 0, 0, &wt5651_dac_w2_mux),
	SND_SOC_DAPM_MUX("DAC W2 Mux", SND_SOC_NOPM, 0, 0, &wt5651_dac_w2_mux),
	SND_SOC_DAPM_PGA("DAC W2 Vowume", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DAC W2 Vowume", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Stewo1 DAC Powew", WT5651_PWW_DIG2,
			    WT5651_PWW_DAC_STO1_F_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Stewo2 DAC Powew", WT5651_PWW_DIG2,
			    WT5651_PWW_DAC_STO2_F_BIT, 0, NUWW, 0),
	/* DAC Mixew */
	SND_SOC_DAPM_MIXEW("Steweo DAC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_sto_dac_w_mix,
			   AWWAY_SIZE(wt5651_sto_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("Steweo DAC MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_sto_dac_w_mix,
			   AWWAY_SIZE(wt5651_sto_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("DD MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_dd_dac_w_mix,
			   AWWAY_SIZE(wt5651_dd_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("DD MIXW", SND_SOC_NOPM, 0, 0,
			   wt5651_dd_dac_w_mix,
			   AWWAY_SIZE(wt5651_dd_dac_w_mix)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC W1", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC W1", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPWY("DAC W1 Powew", WT5651_PWW_DIG1,
			    WT5651_PWW_DAC_W1_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC W1 Powew", WT5651_PWW_DIG1,
			    WT5651_PWW_DAC_W1_BIT, 0, NUWW, 0),
	/* OUT Mixew */
	SND_SOC_DAPM_MIXEW("OUT MIXW", WT5651_PWW_MIXEW, WT5651_PWW_OM_W_BIT,
			   0, wt5651_out_w_mix, AWWAY_SIZE(wt5651_out_w_mix)),
	SND_SOC_DAPM_MIXEW("OUT MIXW", WT5651_PWW_MIXEW, WT5651_PWW_OM_W_BIT,
			   0, wt5651_out_w_mix, AWWAY_SIZE(wt5651_out_w_mix)),
	/* Ouput Vowume */
	SND_SOC_DAPM_SWITCH("OUTVOW W", WT5651_PWW_VOW,
			    WT5651_PWW_OV_W_BIT, 0, &outvow_w_contwow),
	SND_SOC_DAPM_SWITCH("OUTVOW W", WT5651_PWW_VOW,
			    WT5651_PWW_OV_W_BIT, 0, &outvow_w_contwow),
	SND_SOC_DAPM_SWITCH("HPOVOW W", WT5651_PWW_VOW,
			    WT5651_PWW_HV_W_BIT, 0, &hpovow_w_contwow),
	SND_SOC_DAPM_SWITCH("HPOVOW W", WT5651_PWW_VOW,
			    WT5651_PWW_HV_W_BIT, 0, &hpovow_w_contwow),
	SND_SOC_DAPM_PGA("INW1", WT5651_PWW_VOW,
			 WT5651_PWW_IN1_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INW1", WT5651_PWW_VOW,
			 WT5651_PWW_IN1_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INW2", WT5651_PWW_VOW,
			 WT5651_PWW_IN2_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INW2", WT5651_PWW_VOW,
			 WT5651_PWW_IN2_W_BIT, 0, NUWW, 0),
	/* HPO/WOUT/Mono Mixew */
	SND_SOC_DAPM_MIXEW("HPOW MIX", SND_SOC_NOPM, 0, 0,
			   wt5651_hpo_mix, AWWAY_SIZE(wt5651_hpo_mix)),
	SND_SOC_DAPM_MIXEW("HPOW MIX", SND_SOC_NOPM, 0, 0,
			   wt5651_hpo_mix, AWWAY_SIZE(wt5651_hpo_mix)),
	SND_SOC_DAPM_SUPPWY("HP W Amp", WT5651_PWW_ANWG1,
			    WT5651_PWW_HP_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("HP W Amp", WT5651_PWW_ANWG1,
			    WT5651_PWW_HP_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("WOUT MIX", WT5651_PWW_ANWG1, WT5651_PWW_WM_BIT, 0,
			   wt5651_wout_mix, AWWAY_SIZE(wt5651_wout_mix)),

	SND_SOC_DAPM_SUPPWY("Amp Powew", WT5651_PWW_ANWG1,
			    WT5651_PWW_HA_BIT, 0, wt5651_amp_powew_event,
			    SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0, wt5651_hp_event,
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SWITCH("HPO W Pwayback", SND_SOC_NOPM, 0, 0,
			    &hpo_w_mute_contwow),
	SND_SOC_DAPM_SWITCH("HPO W Pwayback", SND_SOC_NOPM, 0, 0,
			    &hpo_w_mute_contwow),
	SND_SOC_DAPM_SWITCH("WOUT W Pwayback", SND_SOC_NOPM, 0, 0,
			    &wout_w_mute_contwow),
	SND_SOC_DAPM_SWITCH("WOUT W Pwayback", SND_SOC_NOPM, 0, 0,
			    &wout_w_mute_contwow),
	SND_SOC_DAPM_POST("HP Post", wt5651_hp_post_event),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("WOUTW"),
	SND_SOC_DAPM_OUTPUT("WOUTW"),
	SND_SOC_DAPM_OUTPUT("PDMW"),
	SND_SOC_DAPM_OUTPUT("PDMW"),
};

static const stwuct snd_soc_dapm_woute wt5651_dapm_woutes[] = {
	{"Stewo1 DAC Powew", NUWW, "STO1 DAC ASWC"},
	{"Stewo2 DAC Powew", NUWW, "STO2 DAC ASWC"},
	{"I2S1", NUWW, "I2S1 ASWC"},
	{"I2S2", NUWW, "I2S2 ASWC"},

	{"IN1P", NUWW, "WDO"},
	{"IN2P", NUWW, "WDO"},
	{"IN3P", NUWW, "WDO"},

	{"IN1P", NUWW, "MIC1"},
	{"IN2P", NUWW, "MIC2"},
	{"IN2N", NUWW, "MIC2"},
	{"IN3P", NUWW, "MIC3"},

	{"BST1", NUWW, "IN1P"},
	{"BST2", NUWW, "IN2P"},
	{"BST2", NUWW, "IN2N"},
	{"BST3", NUWW, "IN3P"},

	{"INW1 VOW", NUWW, "IN2P"},
	{"INW1 VOW", NUWW, "IN2N"},

	{"WECMIXW", "INW1 Switch", "INW1 VOW"},
	{"WECMIXW", "BST3 Switch", "BST3"},
	{"WECMIXW", "BST2 Switch", "BST2"},
	{"WECMIXW", "BST1 Switch", "BST1"},

	{"WECMIXW", "INW1 Switch", "INW1 VOW"},
	{"WECMIXW", "BST3 Switch", "BST3"},
	{"WECMIXW", "BST2 Switch", "BST2"},
	{"WECMIXW", "BST1 Switch", "BST1"},

	{"ADC W", NUWW, "WECMIXW"},
	{"ADC W", NUWW, "ADC W Powew"},
	{"ADC W", NUWW, "WECMIXW"},
	{"ADC W", NUWW, "ADC W Powew"},

	{"DMIC W1", NUWW, "DMIC CWK"},
	{"DMIC W1", NUWW, "DMIC CWK"},

	{"Steweo1 ADC W2 Mux", "DMIC", "DMIC W1"},
	{"Steweo1 ADC W2 Mux", "DD MIX", "DD MIXW"},
	{"Steweo1 ADC W1 Mux", "ADC", "ADC W"},
	{"Steweo1 ADC W1 Mux", "DD MIX", "DD MIXW"},

	{"Steweo1 ADC W1 Mux", "ADC", "ADC W"},
	{"Steweo1 ADC W1 Mux", "DD MIX", "DD MIXW"},
	{"Steweo1 ADC W2 Mux", "DMIC", "DMIC W1"},
	{"Steweo1 ADC W2 Mux", "DD MIX", "DD MIXW"},

	{"Steweo2 ADC W2 Mux", "DMIC W", "DMIC W1"},
	{"Steweo2 ADC W2 Mux", "DD MIXW", "DD MIXW"},
	{"Steweo2 ADC W1 Mux", "DD MIXW", "DD MIXW"},
	{"Steweo2 ADC W1 Mux", "ADCW", "ADC W"},

	{"Steweo2 ADC W1 Mux", "DD MIXW", "DD MIXW"},
	{"Steweo2 ADC W1 Mux", "ADCW", "ADC W"},
	{"Steweo2 ADC W2 Mux", "DMIC W", "DMIC W1"},
	{"Steweo2 ADC W2 Mux", "DD MIXW", "DD MIXW"},

	{"Steweo1 ADC MIXW", "ADC1 Switch", "Steweo1 ADC W1 Mux"},
	{"Steweo1 ADC MIXW", "ADC2 Switch", "Steweo1 ADC W2 Mux"},
	{"Steweo1 ADC MIXW", NUWW, "Steweo1 Fiwtew"},
	{"Steweo1 Fiwtew", NUWW, "ADC ASWC"},

	{"Steweo1 ADC MIXW", "ADC1 Switch", "Steweo1 ADC W1 Mux"},
	{"Steweo1 ADC MIXW", "ADC2 Switch", "Steweo1 ADC W2 Mux"},
	{"Steweo1 ADC MIXW", NUWW, "Steweo1 Fiwtew"},

	{"Steweo2 ADC MIXW", "ADC1 Switch", "Steweo2 ADC W1 Mux"},
	{"Steweo2 ADC MIXW", "ADC2 Switch", "Steweo2 ADC W2 Mux"},
	{"Steweo2 ADC MIXW", NUWW, "Steweo2 Fiwtew"},
	{"Steweo2 Fiwtew", NUWW, "ADC ASWC"},

	{"Steweo2 ADC MIXW", "ADC1 Switch", "Steweo2 ADC W1 Mux"},
	{"Steweo2 ADC MIXW", "ADC2 Switch", "Steweo2 ADC W2 Mux"},
	{"Steweo2 ADC MIXW", NUWW, "Steweo2 Fiwtew"},

	{"IF1 ADC2", NUWW, "Steweo2 ADC MIXW"},
	{"IF1 ADC2", NUWW, "Steweo2 ADC MIXW"},
	{"IF1 ADC1", NUWW, "Steweo1 ADC MIXW"},
	{"IF1 ADC1", NUWW, "Steweo1 ADC MIXW"},

	{"IF1 ADC1", NUWW, "I2S1"},

	{"IF2 ADC", "IF1 ADC1", "IF1 ADC1"},
	{"IF2 ADC", "IF1 ADC2", "IF1 ADC2"},
	{"IF2 ADC", NUWW, "I2S2"},

	{"AIF1TX", NUWW, "IF1 ADC1"},
	{"AIF1TX", NUWW, "IF1 ADC2"},
	{"AIF2TX", NUWW, "IF2 ADC"},

	{"IF1 DAC", NUWW, "AIF1WX"},
	{"IF1 DAC", NUWW, "I2S1"},
	{"IF2 DAC", NUWW, "AIF2WX"},
	{"IF2 DAC", NUWW, "I2S2"},

	{"IF1 DAC1 W", NUWW, "IF1 DAC"},
	{"IF1 DAC1 W", NUWW, "IF1 DAC"},
	{"IF1 DAC2 W", NUWW, "IF1 DAC"},
	{"IF1 DAC2 W", NUWW, "IF1 DAC"},
	{"IF2 DAC W", NUWW, "IF2 DAC"},
	{"IF2 DAC W", NUWW, "IF2 DAC"},

	{"DAC MIXW", "Steweo ADC Switch", "Steweo1 ADC MIXW"},
	{"DAC MIXW", "INF1 Switch", "IF1 DAC1 W"},
	{"DAC MIXW", "Steweo ADC Switch", "Steweo1 ADC MIXW"},
	{"DAC MIXW", "INF1 Switch", "IF1 DAC1 W"},

	{"Audio DSP", NUWW, "DAC MIXW"},
	{"Audio DSP", NUWW, "DAC MIXW"},

	{"DAC W2 Mux", "IF1", "IF1 DAC2 W"},
	{"DAC W2 Mux", "IF2", "IF2 DAC W"},
	{"DAC W2 Vowume", NUWW, "DAC W2 Mux"},

	{"DAC W2 Mux", "IF1", "IF1 DAC2 W"},
	{"DAC W2 Mux", "IF2", "IF2 DAC W"},
	{"DAC W2 Vowume", NUWW, "DAC W2 Mux"},

	{"Steweo DAC MIXW", "DAC W1 Switch", "Audio DSP"},
	{"Steweo DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume"},
	{"Steweo DAC MIXW", "DAC W1 Switch", "DAC MIXW"},
	{"Steweo DAC MIXW", NUWW, "Stewo1 DAC Powew"},
	{"Steweo DAC MIXW", NUWW, "Stewo2 DAC Powew"},
	{"Steweo DAC MIXW", "DAC W1 Switch", "Audio DSP"},
	{"Steweo DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume"},
	{"Steweo DAC MIXW", "DAC W1 Switch", "DAC MIXW"},
	{"Steweo DAC MIXW", NUWW, "Stewo1 DAC Powew"},
	{"Steweo DAC MIXW", NUWW, "Stewo2 DAC Powew"},

	{"PDM W Mux", "Steweo DAC MIX", "Steweo DAC MIXW"},
	{"PDM W Mux", "DD MIX", "DAC MIXW"},
	{"PDM W Mux", "Steweo DAC MIX", "Steweo DAC MIXW"},
	{"PDM W Mux", "DD MIX", "DAC MIXW"},

	{"DAC W1", NUWW, "Steweo DAC MIXW"},
	{"DAC W1", NUWW, "DAC W1 Powew"},
	{"DAC W1", NUWW, "Steweo DAC MIXW"},
	{"DAC W1", NUWW, "DAC W1 Powew"},

	{"DD MIXW", "DAC W1 Switch", "DAC MIXW"},
	{"DD MIXW", "DAC W2 Switch", "DAC W2 Vowume"},
	{"DD MIXW", "DAC W2 Switch", "DAC W2 Vowume"},
	{"DD MIXW", NUWW, "Stewo2 DAC Powew"},

	{"DD MIXW", "DAC W1 Switch", "DAC MIXW"},
	{"DD MIXW", "DAC W2 Switch", "DAC W2 Vowume"},
	{"DD MIXW", "DAC W2 Switch", "DAC W2 Vowume"},
	{"DD MIXW", NUWW, "Stewo2 DAC Powew"},

	{"OUT MIXW", "BST1 Switch", "BST1"},
	{"OUT MIXW", "BST2 Switch", "BST2"},
	{"OUT MIXW", "INW1 Switch", "INW1 VOW"},
	{"OUT MIXW", "WEC MIXW Switch", "WECMIXW"},
	{"OUT MIXW", "DAC W1 Switch", "DAC W1"},

	{"OUT MIXW", "BST2 Switch", "BST2"},
	{"OUT MIXW", "BST1 Switch", "BST1"},
	{"OUT MIXW", "INW1 Switch", "INW1 VOW"},
	{"OUT MIXW", "WEC MIXW Switch", "WECMIXW"},
	{"OUT MIXW", "DAC W1 Switch", "DAC W1"},

	{"HPOVOW W", "Switch", "OUT MIXW"},
	{"HPOVOW W", "Switch", "OUT MIXW"},
	{"OUTVOW W", "Switch", "OUT MIXW"},
	{"OUTVOW W", "Switch", "OUT MIXW"},

	{"HPOW MIX", "HPO MIX DAC1 Switch", "DAC W1"},
	{"HPOW MIX", "HPO MIX HPVOW Switch", "HPOVOW W"},
	{"HPOW MIX", NUWW, "HP W Amp"},
	{"HPOW MIX", "HPO MIX DAC1 Switch", "DAC W1"},
	{"HPOW MIX", "HPO MIX HPVOW Switch", "HPOVOW W"},
	{"HPOW MIX", NUWW, "HP W Amp"},

	{"WOUT MIX", "DAC W1 Switch", "DAC W1"},
	{"WOUT MIX", "DAC W1 Switch", "DAC W1"},
	{"WOUT MIX", "OUTVOW W Switch", "OUTVOW W"},
	{"WOUT MIX", "OUTVOW W Switch", "OUTVOW W"},

	{"HP Amp", NUWW, "HPOW MIX"},
	{"HP Amp", NUWW, "HPOW MIX"},
	{"HP Amp", NUWW, "Amp Powew"},
	{"HPO W Pwayback", "Switch", "HP Amp"},
	{"HPO W Pwayback", "Switch", "HP Amp"},
	{"HPOW", NUWW, "HPO W Pwayback"},
	{"HPOW", NUWW, "HPO W Pwayback"},

	{"WOUT W Pwayback", "Switch", "WOUT MIX"},
	{"WOUT W Pwayback", "Switch", "WOUT MIX"},
	{"WOUTW", NUWW, "WOUT W Pwayback"},
	{"WOUTW", NUWW, "Amp Powew"},
	{"WOUTW", NUWW, "WOUT W Pwayback"},
	{"WOUTW", NUWW, "Amp Powew"},

	{"PDMW", NUWW, "PDM W Mux"},
	{"PDMW", NUWW, "PDM W Mux"},
};

static int wt5651_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_wen = 0, vaw_cwk, mask_cwk;
	int pwe_div, bcwk_ms, fwame_size;

	wt5651->wwck[dai->id] = pawams_wate(pawams);
	pwe_div = ww6231_get_cwk_info(wt5651->syscwk, wt5651->wwck[dai->id]);

	if (pwe_div < 0) {
		dev_eww(component->dev, "Unsuppowted cwock setting\n");
		wetuwn -EINVAW;
	}
	fwame_size = snd_soc_pawams_to_fwame_size(pawams);
	if (fwame_size < 0) {
		dev_eww(component->dev, "Unsuppowted fwame size: %d\n", fwame_size);
		wetuwn -EINVAW;
	}
	bcwk_ms = fwame_size > 32 ? 1 : 0;
	wt5651->bcwk[dai->id] = wt5651->wwck[dai->id] * (32 << bcwk_ms);

	dev_dbg(dai->dev, "bcwk is %dHz and wwck is %dHz\n",
		wt5651->bcwk[dai->id], wt5651->wwck[dai->id]);
	dev_dbg(dai->dev, "bcwk_ms is %d and pwe_div is %d fow iis %d\n",
				bcwk_ms, pwe_div, dai->id);

	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		vaw_wen |= WT5651_I2S_DW_20;
		bweak;
	case 24:
		vaw_wen |= WT5651_I2S_DW_24;
		bweak;
	case 8:
		vaw_wen |= WT5651_I2S_DW_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dai->id) {
	case WT5651_AIF1:
		mask_cwk = WT5651_I2S_PD1_MASK;
		vaw_cwk = pwe_div << WT5651_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, WT5651_I2S1_SDP,
			WT5651_I2S_DW_MASK, vaw_wen);
		snd_soc_component_update_bits(component, WT5651_ADDA_CWK1, mask_cwk, vaw_cwk);
		bweak;
	case WT5651_AIF2:
		mask_cwk = WT5651_I2S_BCWK_MS2_MASK | WT5651_I2S_PD2_MASK;
		vaw_cwk = pwe_div << WT5651_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, WT5651_I2S2_SDP,
			WT5651_I2S_DW_MASK, vaw_wen);
		snd_soc_component_update_bits(component, WT5651_ADDA_CWK1, mask_cwk, vaw_cwk);
		bweak;
	defauwt:
		dev_eww(component->dev, "Wwong dai->id: %d\n", dai->id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wt5651_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		wt5651->mastew[dai->id] = 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		weg_vaw |= WT5651_I2S_MS_S;
		wt5651->mastew[dai->id] = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		weg_vaw |= WT5651_I2S_BP_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		weg_vaw |= WT5651_I2S_DF_WEFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		weg_vaw |= WT5651_I2S_DF_PCM_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		weg_vaw |= WT5651_I2S_DF_PCM_B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dai->id) {
	case WT5651_AIF1:
		snd_soc_component_update_bits(component, WT5651_I2S1_SDP,
			WT5651_I2S_MS_MASK | WT5651_I2S_BP_MASK |
			WT5651_I2S_DF_MASK, weg_vaw);
		bweak;
	case WT5651_AIF2:
		snd_soc_component_update_bits(component, WT5651_I2S2_SDP,
			WT5651_I2S_MS_MASK | WT5651_I2S_BP_MASK |
			WT5651_I2S_DF_MASK, weg_vaw);
		bweak;
	defauwt:
		dev_eww(component->dev, "Wwong dai->id: %d\n", dai->id);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wt5651_set_dai_syscwk(stwuct snd_soc_dai *dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;
	unsigned int pww_bit = 0;

	if (fweq == wt5651->syscwk && cwk_id == wt5651->syscwk_swc)
		wetuwn 0;

	switch (cwk_id) {
	case WT5651_SCWK_S_MCWK:
		weg_vaw |= WT5651_SCWK_SWC_MCWK;
		bweak;
	case WT5651_SCWK_S_PWW1:
		weg_vaw |= WT5651_SCWK_SWC_PWW1;
		pww_bit |= WT5651_PWW_PWW;
		bweak;
	case WT5651_SCWK_S_WCCWK:
		weg_vaw |= WT5651_SCWK_SWC_WCCWK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
		WT5651_PWW_PWW, pww_bit);
	snd_soc_component_update_bits(component, WT5651_GWB_CWK,
		WT5651_SCWK_SWC_MASK, weg_vaw);
	wt5651->syscwk = fweq;
	wt5651->syscwk_swc = cwk_id;

	dev_dbg(dai->dev, "Syscwk is %dHz and cwock id is %d\n", fweq, cwk_id);

	wetuwn 0;
}

static int wt5651_set_dai_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
			unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	stwuct ww6231_pww_code pww_code;
	int wet;

	if (souwce == wt5651->pww_swc && fweq_in == wt5651->pww_in &&
	    fweq_out == wt5651->pww_out)
		wetuwn 0;

	if (!fweq_in || !fweq_out) {
		dev_dbg(component->dev, "PWW disabwed\n");

		wt5651->pww_in = 0;
		wt5651->pww_out = 0;
		snd_soc_component_update_bits(component, WT5651_GWB_CWK,
			WT5651_SCWK_SWC_MASK, WT5651_SCWK_SWC_MCWK);
		wetuwn 0;
	}

	switch (souwce) {
	case WT5651_PWW1_S_MCWK:
		snd_soc_component_update_bits(component, WT5651_GWB_CWK,
			WT5651_PWW1_SWC_MASK, WT5651_PWW1_SWC_MCWK);
		bweak;
	case WT5651_PWW1_S_BCWK1:
		snd_soc_component_update_bits(component, WT5651_GWB_CWK,
				WT5651_PWW1_SWC_MASK, WT5651_PWW1_SWC_BCWK1);
		bweak;
	case WT5651_PWW1_S_BCWK2:
			snd_soc_component_update_bits(component, WT5651_GWB_CWK,
				WT5651_PWW1_SWC_MASK, WT5651_PWW1_SWC_BCWK2);
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown PWW souwce %d\n", souwce);
		wetuwn -EINVAW;
	}

	wet = ww6231_pww_cawc(fweq_in, fweq_out, &pww_code);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pww_code.m_bp, (pww_code.m_bp ? 0 : pww_code.m_code),
		pww_code.n_code, pww_code.k_code);

	snd_soc_component_wwite(component, WT5651_PWW_CTWW1,
		pww_code.n_code << WT5651_PWW_N_SFT | pww_code.k_code);
	snd_soc_component_wwite(component, WT5651_PWW_CTWW2,
		((pww_code.m_bp ? 0 : pww_code.m_code) << WT5651_PWW_M_SFT) |
		(pww_code.m_bp << WT5651_PWW_M_BP_SFT));

	wt5651->pww_in = fweq_in;
	wt5651->pww_out = fweq_out;
	wt5651->pww_swc = souwce;

	wetuwn 0;
}

static int wt5651_set_bias_wevew(stwuct snd_soc_component *component,
			enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (SND_SOC_BIAS_STANDBY == snd_soc_component_get_bias_wevew(component)) {
			if (snd_soc_component_wead(component, WT5651_PWW_MODE_1) & 0x9200)
				snd_soc_component_update_bits(component, WT5651_D_MISC,
						    0xc00, 0xc00);
		}
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (SND_SOC_BIAS_OFF == snd_soc_component_get_bias_wevew(component)) {
			snd_soc_component_update_bits(component, WT5651_PWW_ANWG1,
				WT5651_PWW_VWEF1 | WT5651_PWW_MB |
				WT5651_PWW_BG | WT5651_PWW_VWEF2,
				WT5651_PWW_VWEF1 | WT5651_PWW_MB |
				WT5651_PWW_BG | WT5651_PWW_VWEF2);
			usweep_wange(10000, 15000);
			snd_soc_component_update_bits(component, WT5651_PWW_ANWG1,
				WT5651_PWW_FV1 | WT5651_PWW_FV2,
				WT5651_PWW_FV1 | WT5651_PWW_FV2);
			snd_soc_component_update_bits(component, WT5651_D_MISC, 0x1, 0x1);
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WT5651_D_MISC, 0x0010);
		snd_soc_component_wwite(component, WT5651_PWW_DIG1, 0x0000);
		snd_soc_component_wwite(component, WT5651_PWW_DIG2, 0x0000);
		snd_soc_component_wwite(component, WT5651_PWW_VOW, 0x0000);
		snd_soc_component_wwite(component, WT5651_PWW_MIXEW, 0x0000);
		/* Do not touch the WDO vowtage sewect bits on bias-off */
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG1,
			~WT5651_PWW_WDO_DVO_MASK, 0);
		/* Weave PWW1 and jack-detect powew as is, aww othews off */
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
				    ~(WT5651_PWW_PWW | WT5651_PWW_JD_M), 0);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void wt5651_enabwe_micbias1_fow_ovcd(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_wock(dapm);
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "WDO");
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "micbias1");
	/* OVCD is unwewiabwe when used with WCCWK as syscwk-souwce */
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "Pwatfowm Cwock");
	snd_soc_dapm_sync_unwocked(dapm);
	snd_soc_dapm_mutex_unwock(dapm);
}

static void wt5651_disabwe_micbias1_fow_ovcd(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_wock(dapm);
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "Pwatfowm Cwock");
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "micbias1");
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "WDO");
	snd_soc_dapm_sync_unwocked(dapm);
	snd_soc_dapm_mutex_unwock(dapm);
}

static void wt5651_enabwe_micbias1_ovcd_iwq(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	snd_soc_component_update_bits(component, WT5651_IWQ_CTWW2,
		WT5651_IWQ_MB1_OC_MASK, WT5651_IWQ_MB1_OC_NOW);
	wt5651->ovcd_iwq_enabwed = twue;
}

static void wt5651_disabwe_micbias1_ovcd_iwq(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	snd_soc_component_update_bits(component, WT5651_IWQ_CTWW2,
		WT5651_IWQ_MB1_OC_MASK, WT5651_IWQ_MB1_OC_BP);
	wt5651->ovcd_iwq_enabwed = fawse;
}

static void wt5651_cweaw_micbias1_ovcd(stwuct snd_soc_component *component)
{
	snd_soc_component_update_bits(component, WT5651_IWQ_CTWW2,
		WT5651_MB1_OC_CWW, 0);
}

static boow wt5651_micbias1_ovcd(stwuct snd_soc_component *component)
{
	int vaw;

	vaw = snd_soc_component_wead(component, WT5651_IWQ_CTWW2);
	dev_dbg(component->dev, "iwq ctww2 %#04x\n", vaw);

	wetuwn (vaw & WT5651_MB1_OC_CWW);
}

static boow wt5651_jack_insewted(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	int vaw;

	if (wt5651->gpiod_hp_det) {
		vaw = gpiod_get_vawue_cansweep(wt5651->gpiod_hp_det);
		dev_dbg(component->dev, "jack-detect gpio %d\n", vaw);
		wetuwn vaw;
	}

	vaw = snd_soc_component_wead(component, WT5651_INT_IWQ_ST);
	dev_dbg(component->dev, "iwq status %#04x\n", vaw);

	switch (wt5651->jd_swc) {
	case WT5651_JD1_1:
		vaw &= 0x1000;
		bweak;
	case WT5651_JD1_2:
		vaw &= 0x2000;
		bweak;
	case WT5651_JD2:
		vaw &= 0x4000;
		bweak;
	defauwt:
		bweak;
	}

	if (wt5651->jd_active_high)
		wetuwn vaw != 0;
	ewse
		wetuwn vaw == 0;
}

/* Jack detect and button-pwess timings */
#define JACK_SETTWE_TIME	100 /* miwwi seconds */
#define JACK_DETECT_COUNT	5
#define JACK_DETECT_MAXCOUNT	20  /* Apwox. 2 seconds wowth of twies */
#define JACK_UNPWUG_TIME	80  /* miwwi seconds */
#define BP_POWW_TIME		10  /* miwwi seconds */
#define BP_POWW_MAXCOUNT	200 /* assume something is wwong aftew this */
#define BP_THWESHOWD		3

static void wt5651_stawt_button_pwess_wowk(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	wt5651->poww_count = 0;
	wt5651->pwess_count = 0;
	wt5651->wewease_count = 0;
	wt5651->pwessed = fawse;
	wt5651->pwess_wepowted = fawse;
	wt5651_cweaw_micbias1_ovcd(component);
	scheduwe_dewayed_wowk(&wt5651->bp_wowk, msecs_to_jiffies(BP_POWW_TIME));
}

static void wt5651_button_pwess_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5651_pwiv *wt5651 =
		containew_of(wowk, stwuct wt5651_pwiv, bp_wowk.wowk);
	stwuct snd_soc_component *component = wt5651->component;

	/* Check the jack was not wemoved undewneath us */
	if (!wt5651_jack_insewted(component))
		wetuwn;

	if (wt5651_micbias1_ovcd(component)) {
		wt5651->wewease_count = 0;
		wt5651->pwess_count++;
		/* Wemembew tiww aftew JACK_UNPWUG_TIME wait */
		if (wt5651->pwess_count >= BP_THWESHOWD)
			wt5651->pwessed = twue;
		wt5651_cweaw_micbias1_ovcd(component);
	} ewse {
		wt5651->pwess_count = 0;
		wt5651->wewease_count++;
	}

	/*
	 * The pins get tempowawiwy showted on jack unpwug, so we poww fow
	 * at weast JACK_UNPWUG_TIME miwwi-seconds befowe wepowting a pwess.
	 */
	wt5651->poww_count++;
	if (wt5651->poww_count < (JACK_UNPWUG_TIME / BP_POWW_TIME)) {
		scheduwe_dewayed_wowk(&wt5651->bp_wowk,
				      msecs_to_jiffies(BP_POWW_TIME));
		wetuwn;
	}

	if (wt5651->pwessed && !wt5651->pwess_wepowted) {
		dev_dbg(component->dev, "headset button pwess\n");
		snd_soc_jack_wepowt(wt5651->hp_jack, SND_JACK_BTN_0,
				    SND_JACK_BTN_0);
		wt5651->pwess_wepowted = twue;
	}

	if (wt5651->wewease_count >= BP_THWESHOWD) {
		if (wt5651->pwess_wepowted) {
			dev_dbg(component->dev, "headset button wewease\n");
			snd_soc_jack_wepowt(wt5651->hp_jack, 0, SND_JACK_BTN_0);
		}
		/* We-enabwe OVCD IWQ to detect next pwess */
		wt5651_enabwe_micbias1_ovcd_iwq(component);
		wetuwn; /* Stop powwing */
	}

	scheduwe_dewayed_wowk(&wt5651->bp_wowk, msecs_to_jiffies(BP_POWW_TIME));
}

static int wt5651_detect_headset(stwuct snd_soc_component *component)
{
	int i, headset_count = 0, headphone_count = 0;

	/*
	 * We get the insewtion event befowe the jack is fuwwy insewted at which
	 * point the second wing on a TWWS connectow may showt the 2nd wing and
	 * sweeve contacts, awso the ovewcuwwent detection is not entiwewy
	 * wewiabwe. So we twy sevewaw times with a wait in between untiw we
	 * detect the same type JACK_DETECT_COUNT times in a wow.
	 */
	fow (i = 0; i < JACK_DETECT_MAXCOUNT; i++) {
		/* Cweaw any pwevious ovew-cuwwent status fwag */
		wt5651_cweaw_micbias1_ovcd(component);

		msweep(JACK_SETTWE_TIME);

		/* Check the jack is stiww connected befowe checking ovcd */
		if (!wt5651_jack_insewted(component))
			wetuwn 0;

		if (wt5651_micbias1_ovcd(component)) {
			/*
			 * Ovew cuwwent detected, thewe is a showt between the
			 * 2nd wing contact and the gwound, so a TWS connectow
			 * without a mic contact and thus pwain headphones.
			 */
			dev_dbg(component->dev, "mic-gnd showted\n");
			headset_count = 0;
			headphone_count++;
			if (headphone_count == JACK_DETECT_COUNT)
				wetuwn SND_JACK_HEADPHONE;
		} ewse {
			dev_dbg(component->dev, "mic-gnd open\n");
			headphone_count = 0;
			headset_count++;
			if (headset_count == JACK_DETECT_COUNT)
				wetuwn SND_JACK_HEADSET;
		}
	}

	dev_eww(component->dev, "Ewwow detecting headset vs headphones, bad contact?, assuming headphones\n");
	wetuwn SND_JACK_HEADPHONE;
}

static boow wt5651_suppowt_button_pwess(stwuct wt5651_pwiv *wt5651)
{
	if (!wt5651->hp_jack)
		wetuwn fawse;

	/* Button pwess suppowt onwy wowks with intewnaw jack-detection */
	wetuwn (wt5651->hp_jack->status & SND_JACK_MICWOPHONE) &&
		wt5651->gpiod_hp_det == NUWW;
}

static void wt5651_jack_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5651_pwiv *wt5651 =
		containew_of(wowk, stwuct wt5651_pwiv, jack_detect_wowk);
	stwuct snd_soc_component *component = wt5651->component;
	int wepowt;

	if (!wt5651_jack_insewted(component)) {
		/* Jack wemoved, ow spuwious IWQ? */
		if (wt5651->hp_jack->status & SND_JACK_HEADPHONE) {
			if (wt5651->hp_jack->status & SND_JACK_MICWOPHONE) {
				cancew_dewayed_wowk_sync(&wt5651->bp_wowk);
				wt5651_disabwe_micbias1_ovcd_iwq(component);
				wt5651_disabwe_micbias1_fow_ovcd(component);
			}
			snd_soc_jack_wepowt(wt5651->hp_jack, 0,
					    SND_JACK_HEADSET | SND_JACK_BTN_0);
			dev_dbg(component->dev, "jack unpwugged\n");
		}
	} ewse if (!(wt5651->hp_jack->status & SND_JACK_HEADPHONE)) {
		/* Jack insewted */
		WAWN_ON(wt5651->ovcd_iwq_enabwed);
		wt5651_enabwe_micbias1_fow_ovcd(component);
		wepowt = wt5651_detect_headset(component);
		dev_dbg(component->dev, "detect wepowt %#02x\n", wepowt);
		snd_soc_jack_wepowt(wt5651->hp_jack, wepowt, SND_JACK_HEADSET);
		if (wt5651_suppowt_button_pwess(wt5651)) {
			/* Enabwe ovcd IWQ fow button pwess detect. */
			wt5651_enabwe_micbias1_ovcd_iwq(component);
		} ewse {
			/* No mowe need fow ovewcuwwent detect. */
			wt5651_disabwe_micbias1_fow_ovcd(component);
		}
	} ewse if (wt5651->ovcd_iwq_enabwed && wt5651_micbias1_ovcd(component)) {
		dev_dbg(component->dev, "OVCD IWQ\n");

		/*
		 * The ovcd IWQ keeps fiwing whiwe the button is pwessed, so
		 * we disabwe it and stawt powwing the button untiw weweased.
		 *
		 * The disabwe wiww make the IWQ pin 0 again and since we get
		 * IWQs on both edges (so as to detect both jack pwugin and
		 * unpwug) this means we wiww immediatewy get anothew IWQ.
		 * The ovcd_iwq_enabwed check above makes the 2ND IWQ a NOP.
		 */
		wt5651_disabwe_micbias1_ovcd_iwq(component);
		wt5651_stawt_button_pwess_wowk(component);

		/*
		 * If the jack-detect IWQ fwag goes high (unpwug) aftew ouw
		 * above wt5651_jack_insewted() check and befowe we have
		 * disabwed the OVCD IWQ, the IWQ pin wiww stay high and as
		 * we weact to edges, we miss the unpwug event -> wecheck.
		 */
		queue_wowk(system_wong_wq, &wt5651->jack_detect_wowk);
	}
}

static iwqwetuwn_t wt5651_iwq(int iwq, void *data)
{
	stwuct wt5651_pwiv *wt5651 = data;

	queue_wowk(system_powew_efficient_wq, &wt5651->jack_detect_wowk);

	wetuwn IWQ_HANDWED;
}

static void wt5651_cancew_wowk(void *data)
{
	stwuct wt5651_pwiv *wt5651 = data;

	cancew_wowk_sync(&wt5651->jack_detect_wowk);
	cancew_dewayed_wowk_sync(&wt5651->bp_wowk);
}

static void wt5651_enabwe_jack_detect(stwuct snd_soc_component *component,
				      stwuct snd_soc_jack *hp_jack,
				      stwuct gpio_desc *gpiod_hp_det)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	boow using_intewnaw_jack_detect = twue;

	/* Sewect jack detect souwce */
	switch (wt5651->jd_swc) {
	case WT5651_JD_NUWW:
		wt5651->gpiod_hp_det = gpiod_hp_det;
		if (!wt5651->gpiod_hp_det)
			wetuwn; /* No jack detect */
		using_intewnaw_jack_detect = fawse;
		bweak;
	case WT5651_JD1_1:
		snd_soc_component_update_bits(component, WT5651_JD_CTWW2,
			WT5651_JD_TWG_SEW_MASK, WT5651_JD_TWG_SEW_JD1_1);
		/* active-wow is nowmaw, set inv fwag fow active-high */
		if (wt5651->jd_active_high)
			snd_soc_component_update_bits(component,
				WT5651_IWQ_CTWW1,
				WT5651_JD1_1_IWQ_EN | WT5651_JD1_1_INV,
				WT5651_JD1_1_IWQ_EN | WT5651_JD1_1_INV);
		ewse
			snd_soc_component_update_bits(component,
				WT5651_IWQ_CTWW1,
				WT5651_JD1_1_IWQ_EN | WT5651_JD1_1_INV,
				WT5651_JD1_1_IWQ_EN);
		bweak;
	case WT5651_JD1_2:
		snd_soc_component_update_bits(component, WT5651_JD_CTWW2,
			WT5651_JD_TWG_SEW_MASK, WT5651_JD_TWG_SEW_JD1_2);
		/* active-wow is nowmaw, set inv fwag fow active-high */
		if (wt5651->jd_active_high)
			snd_soc_component_update_bits(component,
				WT5651_IWQ_CTWW1,
				WT5651_JD1_2_IWQ_EN | WT5651_JD1_2_INV,
				WT5651_JD1_2_IWQ_EN | WT5651_JD1_2_INV);
		ewse
			snd_soc_component_update_bits(component,
				WT5651_IWQ_CTWW1,
				WT5651_JD1_2_IWQ_EN | WT5651_JD1_2_INV,
				WT5651_JD1_2_IWQ_EN);
		bweak;
	case WT5651_JD2:
		snd_soc_component_update_bits(component, WT5651_JD_CTWW2,
			WT5651_JD_TWG_SEW_MASK, WT5651_JD_TWG_SEW_JD2);
		/* active-wow is nowmaw, set inv fwag fow active-high */
		if (wt5651->jd_active_high)
			snd_soc_component_update_bits(component,
				WT5651_IWQ_CTWW1,
				WT5651_JD2_IWQ_EN | WT5651_JD2_INV,
				WT5651_JD2_IWQ_EN | WT5651_JD2_INV);
		ewse
			snd_soc_component_update_bits(component,
				WT5651_IWQ_CTWW1,
				WT5651_JD2_IWQ_EN | WT5651_JD2_INV,
				WT5651_JD2_IWQ_EN);
		bweak;
	defauwt:
		dev_eww(component->dev, "Cuwwentwy onwy JD1_1 / JD1_2 / JD2 awe suppowted\n");
		wetuwn;
	}

	if (using_intewnaw_jack_detect) {
		/* IWQ output on GPIO1 */
		snd_soc_component_update_bits(component, WT5651_GPIO_CTWW1,
			WT5651_GP1_PIN_MASK, WT5651_GP1_PIN_IWQ);

		/* Enabwe jack detect powew */
		snd_soc_component_update_bits(component, WT5651_PWW_ANWG2,
			WT5651_PWW_JD_M, WT5651_PWW_JD_M);
	}

	/* Set OVCD thweshowd cuwwent and scawe-factow */
	snd_soc_component_wwite(component, WT5651_PW_BASE + WT5651_BIAS_CUW4,
				0xa800 | wt5651->ovcd_sf);

	snd_soc_component_update_bits(component, WT5651_MICBIAS,
				      WT5651_MIC1_OVCD_MASK |
				      WT5651_MIC1_OVTH_MASK |
				      WT5651_PWW_CWK12M_MASK |
				      WT5651_PWW_MB_MASK,
				      WT5651_MIC1_OVCD_EN |
				      wt5651->ovcd_th |
				      WT5651_PWW_MB_PU |
				      WT5651_PWW_CWK12M_PU);

	/*
	 * The ovew-cuwwent-detect is onwy wewiabwe in detecting the absence
	 * of ovew-cuwwent, when the mic-contact in the jack is showt-ciwcuited,
	 * the hawdwawe pewiodicawwy wetwies if it can appwy the bias-cuwwent
	 * weading to the ovcd status fwip-fwopping 1-0-1 with it being 0 about
	 * 10% of the time, as we poww the ovcd status bit we might hit that
	 * 10%, so we enabwe sticky mode and when checking OVCD we cweaw the
	 * status, msweep() a bit and then check to get a wewiabwe weading.
	 */
	snd_soc_component_update_bits(component, WT5651_IWQ_CTWW2,
		WT5651_MB1_OC_STKY_MASK, WT5651_MB1_OC_STKY_EN);

	wt5651->hp_jack = hp_jack;
	if (wt5651_suppowt_button_pwess(wt5651)) {
		wt5651_enabwe_micbias1_fow_ovcd(component);
		wt5651_enabwe_micbias1_ovcd_iwq(component);
	}

	enabwe_iwq(wt5651->iwq);
	/* sync initiaw jack state */
	queue_wowk(system_powew_efficient_wq, &wt5651->jack_detect_wowk);
}

static void wt5651_disabwe_jack_detect(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	disabwe_iwq(wt5651->iwq);
	wt5651_cancew_wowk(wt5651);

	if (wt5651_suppowt_button_pwess(wt5651)) {
		wt5651_disabwe_micbias1_ovcd_iwq(component);
		wt5651_disabwe_micbias1_fow_ovcd(component);
		snd_soc_jack_wepowt(wt5651->hp_jack, 0, SND_JACK_BTN_0);
	}

	wt5651->hp_jack = NUWW;
}

static int wt5651_set_jack(stwuct snd_soc_component *component,
			   stwuct snd_soc_jack *jack, void *data)
{
	if (jack)
		wt5651_enabwe_jack_detect(component, jack, data);
	ewse
		wt5651_disabwe_jack_detect(component);

	wetuwn 0;
}

/*
 * Note on some pwatfowms the pwatfowm code may need to add device-pwopewties,
 * wathew then wewying onwy on pwopewties set by the fiwmwawe. Thewefow the
 * pwopewty pawsing MUST be done fwom the component dwivew's pwobe function,
 * wathew then fwom the i2c dwivew's pwobe function, so that the pwatfowm-code
 * can attach extwa pwopewties befowe cawwing snd_soc_wegistew_cawd().
 */
static void wt5651_appwy_pwopewties(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);
	u32 vaw;

	if (device_pwopewty_wead_boow(component->dev, "weawtek,in2-diffewentiaw"))
		snd_soc_component_update_bits(component, WT5651_IN1_IN2,
				WT5651_IN_DF2, WT5651_IN_DF2);

	if (device_pwopewty_wead_boow(component->dev, "weawtek,dmic-en"))
		snd_soc_component_update_bits(component, WT5651_GPIO_CTWW1,
				WT5651_GP2_PIN_MASK, WT5651_GP2_PIN_DMIC1_SCW);

	if (device_pwopewty_wead_u32(component->dev,
				     "weawtek,jack-detect-souwce", &vaw) == 0)
		wt5651->jd_swc = vaw;

	if (device_pwopewty_wead_boow(component->dev, "weawtek,jack-detect-not-invewted"))
		wt5651->jd_active_high = twue;

	/*
	 * Testing on vawious boawds has shown that good defauwts fow the OVCD
	 * thweshowd and scawe-factow awe 2000µA and 0.75. Fow an effective
	 * wimit of 1500µA, this seems to be mowe wewiabwe then 1500µA and 1.0.
	 */
	wt5651->ovcd_th = WT5651_MIC1_OVTH_2000UA;
	wt5651->ovcd_sf = WT5651_MIC_OVCD_SF_0P75;

	if (device_pwopewty_wead_u32(component->dev,
			"weawtek,ovew-cuwwent-thweshowd-micwoamp", &vaw) == 0) {
		switch (vaw) {
		case 600:
			wt5651->ovcd_th = WT5651_MIC1_OVTH_600UA;
			bweak;
		case 1500:
			wt5651->ovcd_th = WT5651_MIC1_OVTH_1500UA;
			bweak;
		case 2000:
			wt5651->ovcd_th = WT5651_MIC1_OVTH_2000UA;
			bweak;
		defauwt:
			dev_wawn(component->dev, "Wawning: Invawid ovew-cuwwent-thweshowd-micwoamp vawue: %d, defauwting to 2000uA\n",
				 vaw);
		}
	}

	if (device_pwopewty_wead_u32(component->dev,
			"weawtek,ovew-cuwwent-scawe-factow", &vaw) == 0) {
		if (vaw <= WT5651_OVCD_SF_1P5)
			wt5651->ovcd_sf = vaw << WT5651_MIC_OVCD_SF_SFT;
		ewse
			dev_wawn(component->dev, "Wawning: Invawid ovew-cuwwent-scawe-factow vawue: %d, defauwting to 0.75\n",
				 vaw);
	}
}

static int wt5651_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	wt5651->component = component;

	snd_soc_component_update_bits(component, WT5651_PWW_ANWG1,
		WT5651_PWW_WDO_DVO_MASK, WT5651_PWW_WDO_DVO_1_2V);

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_OFF);

	wt5651_appwy_pwopewties(component);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int wt5651_suspend(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt5651->wegmap, twue);
	wegcache_mawk_diwty(wt5651->wegmap);
	wetuwn 0;
}

static int wt5651_wesume(stwuct snd_soc_component *component)
{
	stwuct wt5651_pwiv *wt5651 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt5651->wegmap, fawse);
	snd_soc_component_cache_sync(component);

	wetuwn 0;
}
#ewse
#define wt5651_suspend NUWW
#define wt5651_wesume NUWW
#endif

#define WT5651_STEWEO_WATES SNDWV_PCM_WATE_8000_96000
#define WT5651_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt5651_aif_dai_ops = {
	.hw_pawams = wt5651_hw_pawams,
	.set_fmt = wt5651_set_dai_fmt,
	.set_syscwk = wt5651_set_dai_syscwk,
	.set_pww = wt5651_set_dai_pww,
};

static stwuct snd_soc_dai_dwivew wt5651_dai[] = {
	{
		.name = "wt5651-aif1",
		.id = WT5651_AIF1,
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5651_STEWEO_WATES,
			.fowmats = WT5651_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5651_STEWEO_WATES,
			.fowmats = WT5651_FOWMATS,
		},
		.ops = &wt5651_aif_dai_ops,
	},
	{
		.name = "wt5651-aif2",
		.id = WT5651_AIF2,
		.pwayback = {
			.stweam_name = "AIF2 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5651_STEWEO_WATES,
			.fowmats = WT5651_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF2 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5651_STEWEO_WATES,
			.fowmats = WT5651_FOWMATS,
		},
		.ops = &wt5651_aif_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt5651 = {
	.pwobe			= wt5651_pwobe,
	.suspend		= wt5651_suspend,
	.wesume			= wt5651_wesume,
	.set_bias_wevew		= wt5651_set_bias_wevew,
	.set_jack		= wt5651_set_jack,
	.contwows		= wt5651_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wt5651_snd_contwows),
	.dapm_widgets		= wt5651_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt5651_dapm_widgets),
	.dapm_woutes		= wt5651_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt5651_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt5651_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,

	.max_wegistew = WT5651_DEVICE_ID + 1 + (AWWAY_SIZE(wt5651_wanges) *
					       WT5651_PW_SPACING),
	.vowatiwe_weg = wt5651_vowatiwe_wegistew,
	.weadabwe_weg = wt5651_weadabwe_wegistew,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt5651_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt5651_weg),
	.wanges = wt5651_wanges,
	.num_wanges = AWWAY_SIZE(wt5651_wanges),
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

#if defined(CONFIG_OF)
static const stwuct of_device_id wt5651_of_match[] = {
	{ .compatibwe = "weawtek,wt5651", },
	{},
};
MODUWE_DEVICE_TABWE(of, wt5651_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt5651_acpi_match[] = {
	{ "10EC5651", 0 },
	{ "10EC5640", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, wt5651_acpi_match);
#endif

static const stwuct i2c_device_id wt5651_i2c_id[] = {
	{ "wt5651", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt5651_i2c_id);

/*
 * Note this function MUST not wook at device-pwopewties, see the comment
 * above wt5651_appwy_pwopewties().
 */
static int wt5651_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt5651_pwiv *wt5651;
	int wet;
	int eww;

	wt5651 = devm_kzawwoc(&i2c->dev, sizeof(*wt5651),
				GFP_KEWNEW);
	if (NUWW == wt5651)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wt5651);

	wt5651->wegmap = devm_wegmap_init_i2c(i2c, &wt5651_wegmap);
	if (IS_EWW(wt5651->wegmap)) {
		wet = PTW_EWW(wt5651->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	eww = wegmap_wead(wt5651->wegmap, WT5651_DEVICE_ID, &wet);
	if (eww)
		wetuwn eww;

	if (wet != WT5651_DEVICE_ID_VAWUE) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %#x is not wt5651\n", wet);
		wetuwn -ENODEV;
	}

	wegmap_wwite(wt5651->wegmap, WT5651_WESET, 0);

	wet = wegmap_wegistew_patch(wt5651->wegmap, init_wist,
				    AWWAY_SIZE(init_wist));
	if (wet != 0)
		dev_wawn(&i2c->dev, "Faiwed to appwy wegmap patch: %d\n", wet);

	wt5651->iwq = i2c->iwq;
	wt5651->hp_mute = twue;

	INIT_DEWAYED_WOWK(&wt5651->bp_wowk, wt5651_button_pwess_wowk);
	INIT_WOWK(&wt5651->jack_detect_wowk, wt5651_jack_detect_wowk);

	/* Make suwe wowk is stopped on pwobe-ewwow / wemove */
	wet = devm_add_action_ow_weset(&i2c->dev, wt5651_cancew_wowk, wt5651);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(&i2c->dev, wt5651->iwq, wt5651_iwq,
			       IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING
			       | IWQF_ONESHOT | IWQF_NO_AUTOEN, "wt5651", wt5651);
	if (wet) {
		dev_wawn(&i2c->dev, "Faiwed to weguest IWQ %d: %d\n",
			 wt5651->iwq, wet);
		wt5651->iwq = -ENXIO;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				&soc_component_dev_wt5651,
				wt5651_dai, AWWAY_SIZE(wt5651_dai));

	wetuwn wet;
}

static stwuct i2c_dwivew wt5651_i2c_dwivew = {
	.dwivew = {
		.name = "wt5651",
		.acpi_match_tabwe = ACPI_PTW(wt5651_acpi_match),
		.of_match_tabwe = of_match_ptw(wt5651_of_match),
	},
	.pwobe = wt5651_i2c_pwobe,
	.id_tabwe = wt5651_i2c_id,
};
moduwe_i2c_dwivew(wt5651_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT5651 dwivew");
MODUWE_AUTHOW("Bawd Wiao <bawdwiao@weawtek.com>");
MODUWE_WICENSE("GPW v2");
