// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt5631.c  --  WT5631 AWSA Soc Audio dwivew
 *
 * Copywight 2011 Weawtek Micwoewectwonics
 *
 * Authow: fwove <fwove@weawtek.com>
 *
 * Based on WM8753.c
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wt5631.h"

stwuct wt5631_pwiv {
	stwuct wegmap *wegmap;
	int codec_vewsion;
	int mastew;
	int syscwk;
	int wx_wate;
	int bcwk_wate;
	int dmic_used_fwag;
};

static const stwuct weg_defauwt wt5631_weg[] = {
	{ WT5631_SPK_OUT_VOW, 0x8888 },
	{ WT5631_HP_OUT_VOW, 0x8080 },
	{ WT5631_MONO_AXO_1_2_VOW, 0xa080 },
	{ WT5631_AUX_IN_VOW, 0x0808 },
	{ WT5631_ADC_WEC_MIXEW, 0xf0f0 },
	{ WT5631_VDAC_DIG_VOW, 0x0010 },
	{ WT5631_OUTMIXEW_W_CTWW, 0xffc0 },
	{ WT5631_OUTMIXEW_W_CTWW, 0xffc0 },
	{ WT5631_AXO1MIXEW_CTWW, 0x88c0 },
	{ WT5631_AXO2MIXEW_CTWW, 0x88c0 },
	{ WT5631_DIG_MIC_CTWW, 0x3000 },
	{ WT5631_MONO_INPUT_VOW, 0x8808 },
	{ WT5631_SPK_MIXEW_CTWW, 0xf8f8 },
	{ WT5631_SPK_MONO_OUT_CTWW, 0xfc00 },
	{ WT5631_SPK_MONO_HP_OUT_CTWW, 0x4440 },
	{ WT5631_SDP_CTWW, 0x8000 },
	{ WT5631_MONO_SDP_CTWW, 0x8000 },
	{ WT5631_STEWEO_AD_DA_CWK_CTWW, 0x2010 },
	{ WT5631_GEN_PUW_CTWW_WEG, 0x0e00 },
	{ WT5631_INT_ST_IWQ_CTWW_2, 0x071a },
	{ WT5631_MISC_CTWW, 0x2040 },
	{ WT5631_DEPOP_FUN_CTWW_2, 0x8000 },
	{ WT5631_SOFT_VOW_CTWW, 0x07e0 },
	{ WT5631_AWC_CTWW_1, 0x0206 },
	{ WT5631_AWC_CTWW_3, 0x2000 },
	{ WT5631_PSEUDO_SPATW_CTWW, 0x0553 },
};

/*
 * wt5631_wwite_index - wwite index wegistew of 2nd wayew
 */
static void wt5631_wwite_index(stwuct snd_soc_component *component,
		unsigned int weg, unsigned int vawue)
{
	snd_soc_component_wwite(component, WT5631_INDEX_ADD, weg);
	snd_soc_component_wwite(component, WT5631_INDEX_DATA, vawue);
}

/*
 * wt5631_wead_index - wead index wegistew of 2nd wayew
 */
static unsigned int wt5631_wead_index(stwuct snd_soc_component *component,
				unsigned int weg)
{
	unsigned int vawue;

	snd_soc_component_wwite(component, WT5631_INDEX_ADD, weg);
	vawue = snd_soc_component_wead(component, WT5631_INDEX_DATA);

	wetuwn vawue;
}

static int wt5631_weset(stwuct snd_soc_component *component)
{
	wetuwn snd_soc_component_wwite(component, WT5631_WESET, 0);
}

static boow wt5631_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5631_WESET:
	case WT5631_INT_ST_IWQ_CTWW_2:
	case WT5631_INDEX_ADD:
	case WT5631_INDEX_DATA:
	case WT5631_EQ_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt5631_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5631_WESET:
	case WT5631_SPK_OUT_VOW:
	case WT5631_HP_OUT_VOW:
	case WT5631_MONO_AXO_1_2_VOW:
	case WT5631_AUX_IN_VOW:
	case WT5631_STEWEO_DAC_VOW_1:
	case WT5631_MIC_CTWW_1:
	case WT5631_STEWEO_DAC_VOW_2:
	case WT5631_ADC_CTWW_1:
	case WT5631_ADC_WEC_MIXEW:
	case WT5631_ADC_CTWW_2:
	case WT5631_VDAC_DIG_VOW:
	case WT5631_OUTMIXEW_W_CTWW:
	case WT5631_OUTMIXEW_W_CTWW:
	case WT5631_AXO1MIXEW_CTWW:
	case WT5631_AXO2MIXEW_CTWW:
	case WT5631_MIC_CTWW_2:
	case WT5631_DIG_MIC_CTWW:
	case WT5631_MONO_INPUT_VOW:
	case WT5631_SPK_MIXEW_CTWW:
	case WT5631_SPK_MONO_OUT_CTWW:
	case WT5631_SPK_MONO_HP_OUT_CTWW:
	case WT5631_SDP_CTWW:
	case WT5631_MONO_SDP_CTWW:
	case WT5631_STEWEO_AD_DA_CWK_CTWW:
	case WT5631_PWW_MANAG_ADD1:
	case WT5631_PWW_MANAG_ADD2:
	case WT5631_PWW_MANAG_ADD3:
	case WT5631_PWW_MANAG_ADD4:
	case WT5631_GEN_PUW_CTWW_WEG:
	case WT5631_GWOBAW_CWK_CTWW:
	case WT5631_PWW_CTWW:
	case WT5631_INT_ST_IWQ_CTWW_1:
	case WT5631_INT_ST_IWQ_CTWW_2:
	case WT5631_GPIO_CTWW:
	case WT5631_MISC_CTWW:
	case WT5631_DEPOP_FUN_CTWW_1:
	case WT5631_DEPOP_FUN_CTWW_2:
	case WT5631_JACK_DET_CTWW:
	case WT5631_SOFT_VOW_CTWW:
	case WT5631_AWC_CTWW_1:
	case WT5631_AWC_CTWW_2:
	case WT5631_AWC_CTWW_3:
	case WT5631_PSEUDO_SPATW_CTWW:
	case WT5631_INDEX_ADD:
	case WT5631_INDEX_DATA:
	case WT5631_EQ_CTWW:
	case WT5631_VENDOW_ID:
	case WT5631_VENDOW_ID1:
	case WT5631_VENDOW_ID2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -4650, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(dac_vow_twv, -95625, 375, 0);
static const DECWAWE_TWV_DB_SCAWE(in_vow_twv, -3450, 150, 0);
/* {0, +20, +24, +30, +35, +40, +44, +50, +52}dB */
static const DECWAWE_TWV_DB_WANGE(mic_bst_twv,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(2000, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(2400, 0, 0),
	3, 5, TWV_DB_SCAWE_ITEM(3000, 500, 0),
	6, 6, TWV_DB_SCAWE_ITEM(4400, 0, 0),
	7, 7, TWV_DB_SCAWE_ITEM(5000, 0, 0),
	8, 8, TWV_DB_SCAWE_ITEM(5200, 0, 0)
);

static int wt5631_dmic_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = wt5631->dmic_used_fwag;

	wetuwn 0;
}

static int wt5631_dmic_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);

	wt5631->dmic_used_fwag = ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

/* MIC Input Type */
static const chaw *wt5631_input_mode[] = {
	"Singwe ended", "Diffewentiaw"};

static SOC_ENUM_SINGWE_DECW(wt5631_mic1_mode_enum, WT5631_MIC_CTWW_1,
			    WT5631_MIC1_DIFF_INPUT_SHIFT, wt5631_input_mode);

static SOC_ENUM_SINGWE_DECW(wt5631_mic2_mode_enum, WT5631_MIC_CTWW_1,
			    WT5631_MIC2_DIFF_INPUT_SHIFT, wt5631_input_mode);

/* MONO Input Type */
static SOC_ENUM_SINGWE_DECW(wt5631_monoin_mode_enum, WT5631_MONO_INPUT_VOW,
			    WT5631_MONO_DIFF_INPUT_SHIFT, wt5631_input_mode);

/* SPK Watio Gain Contwow */
static const chaw *wt5631_spk_watio[] = {"1.00x", "1.09x", "1.27x", "1.44x",
			"1.56x", "1.68x", "1.99x", "2.34x"};

static SOC_ENUM_SINGWE_DECW(wt5631_spk_watio_enum, WT5631_GEN_PUW_CTWW_WEG,
			    WT5631_SPK_AMP_WATIO_CTWW_SHIFT, wt5631_spk_watio);

static const stwuct snd_kcontwow_new wt5631_snd_contwows[] = {
	/* MIC */
	SOC_ENUM("MIC1 Mode Contwow",  wt5631_mic1_mode_enum),
	SOC_SINGWE_TWV("MIC1 Boost Vowume", WT5631_MIC_CTWW_2,
		WT5631_MIC1_BOOST_SHIFT, 8, 0, mic_bst_twv),
	SOC_ENUM("MIC2 Mode Contwow", wt5631_mic2_mode_enum),
	SOC_SINGWE_TWV("MIC2 Boost Vowume", WT5631_MIC_CTWW_2,
		WT5631_MIC2_BOOST_SHIFT, 8, 0, mic_bst_twv),
	/* MONO IN */
	SOC_ENUM("MONOIN Mode Contwow", wt5631_monoin_mode_enum),
	SOC_DOUBWE_TWV("MONOIN_WX Captuwe Vowume", WT5631_MONO_INPUT_VOW,
			WT5631_W_VOW_SHIFT, WT5631_W_VOW_SHIFT,
			WT5631_VOW_MASK, 1, in_vow_twv),
	/* AXI */
	SOC_DOUBWE_TWV("AXI Captuwe Vowume", WT5631_AUX_IN_VOW,
			WT5631_W_VOW_SHIFT, WT5631_W_VOW_SHIFT,
			WT5631_VOW_MASK, 1, in_vow_twv),
	/* DAC */
	SOC_DOUBWE_TWV("PCM Pwayback Vowume", WT5631_STEWEO_DAC_VOW_2,
			WT5631_W_VOW_SHIFT, WT5631_W_VOW_SHIFT,
			WT5631_DAC_VOW_MASK, 1, dac_vow_twv),
	SOC_DOUBWE("PCM Pwayback Switch", WT5631_STEWEO_DAC_VOW_1,
			WT5631_W_MUTE_SHIFT, WT5631_W_MUTE_SHIFT, 1, 1),
	/* AXO */
	SOC_SINGWE("AXO1 Pwayback Switch", WT5631_MONO_AXO_1_2_VOW,
				WT5631_W_MUTE_SHIFT, 1, 1),
	SOC_SINGWE("AXO2 Pwayback Switch", WT5631_MONO_AXO_1_2_VOW,
				WT5631_W_VOW_SHIFT, 1, 1),
	/* OUTVOW */
	SOC_DOUBWE("OUTVOW Channew Switch", WT5631_SPK_OUT_VOW,
		WT5631_W_EN_SHIFT, WT5631_W_EN_SHIFT, 1, 0),

	/* SPK */
	SOC_DOUBWE("Speakew Pwayback Switch", WT5631_SPK_OUT_VOW,
		WT5631_W_MUTE_SHIFT, WT5631_W_MUTE_SHIFT, 1, 1),
	SOC_DOUBWE_TWV("Speakew Pwayback Vowume", WT5631_SPK_OUT_VOW,
		WT5631_W_VOW_SHIFT, WT5631_W_VOW_SHIFT, 39, 1, out_vow_twv),
	/* MONO OUT */
	SOC_SINGWE("MONO Pwayback Switch", WT5631_MONO_AXO_1_2_VOW,
				WT5631_MUTE_MONO_SHIFT, 1, 1),
	/* HP */
	SOC_DOUBWE("HP Pwayback Switch", WT5631_HP_OUT_VOW,
		WT5631_W_MUTE_SHIFT, WT5631_W_MUTE_SHIFT, 1, 1),
	SOC_DOUBWE_TWV("HP Pwayback Vowume", WT5631_HP_OUT_VOW,
		WT5631_W_VOW_SHIFT, WT5631_W_VOW_SHIFT,
		WT5631_VOW_MASK, 1, out_vow_twv),
	/* DMIC */
	SOC_SINGWE_EXT("DMIC Switch", 0, 0, 1, 0,
		wt5631_dmic_get, wt5631_dmic_put),
	SOC_DOUBWE("DMIC Captuwe Switch", WT5631_DIG_MIC_CTWW,
		WT5631_DMIC_W_CH_MUTE_SHIFT,
		WT5631_DMIC_W_CH_MUTE_SHIFT, 1, 1),

	/* SPK Watio Gain Contwow */
	SOC_ENUM("SPK Watio Contwow", wt5631_spk_watio_enum),
};

static int check_syscwk1_souwce(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WT5631_GWOBAW_CWK_CTWW);
	wetuwn weg & WT5631_SYSCWK_SOUW_SEW_PWW;
}

static int check_dmic_used(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);
	wetuwn wt5631->dmic_used_fwag;
}

static int check_dacw_to_outmixw(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WT5631_OUTMIXEW_W_CTWW);
	wetuwn !(weg & WT5631_M_DAC_W_TO_OUTMIXEW_W);
}

static int check_dacw_to_outmixw(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WT5631_OUTMIXEW_W_CTWW);
	wetuwn !(weg & WT5631_M_DAC_W_TO_OUTMIXEW_W);
}

static int check_dacw_to_spkmixw(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WT5631_SPK_MIXEW_CTWW);
	wetuwn !(weg & WT5631_M_DAC_W_TO_SPKMIXEW_W);
}

static int check_dacw_to_spkmixw(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WT5631_SPK_MIXEW_CTWW);
	wetuwn !(weg & WT5631_M_DAC_W_TO_SPKMIXEW_W);
}

static int check_adcw_sewect(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WT5631_ADC_WEC_MIXEW);
	wetuwn !(weg & WT5631_M_MIC1_TO_WECMIXEW_W);
}

static int check_adcw_sewect(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WT5631_ADC_WEC_MIXEW);
	wetuwn !(weg & WT5631_M_MIC2_TO_WECMIXEW_W);
}

/**
 * onebit_depop_powew_stage - auto depop in powew stage.
 * @component: ASoC component
 * @enabwe: powew on/off
 *
 * When powew on/off headphone, the depop sequence is done by hawdwawe.
 */
static void onebit_depop_powew_stage(stwuct snd_soc_component *component, int enabwe)
{
	unsigned int soft_vow, hp_zc;

	/* enabwe one-bit depop function */
	snd_soc_component_update_bits(component, WT5631_DEPOP_FUN_CTWW_2,
				WT5631_EN_ONE_BIT_DEPOP, 0);

	/* keep soft vowume and zewo cwossing setting */
	soft_vow = snd_soc_component_wead(component, WT5631_SOFT_VOW_CTWW);
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, 0);
	hp_zc = snd_soc_component_wead(component, WT5631_INT_ST_IWQ_CTWW_2);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc & 0xf7ff);
	if (enabwe) {
		/* config one-bit depop pawametew */
		wt5631_wwite_index(component, WT5631_TEST_MODE_CTWW, 0x84c0);
		wt5631_wwite_index(component, WT5631_SPK_INTW_CTWW, 0x309f);
		wt5631_wwite_index(component, WT5631_CP_INTW_WEG2, 0x6530);
		/* powew on capwess bwock */
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_2,
				WT5631_EN_CAP_FWEE_DEPOP);
	} ewse {
		/* powew off capwess bwock */
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_2, 0);
		msweep(100);
	}

	/* wecovew soft vowume and zewo cwossing setting */
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, soft_vow);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc);
}

/**
 * onebit_depop_mute_stage - auto depop in mute stage.
 * @component: ASoC component
 * @enabwe: mute/unmute
 *
 * When mute/unmute headphone, the depop sequence is done by hawdwawe.
 */
static void onebit_depop_mute_stage(stwuct snd_soc_component *component, int enabwe)
{
	unsigned int soft_vow, hp_zc;

	/* enabwe one-bit depop function */
	snd_soc_component_update_bits(component, WT5631_DEPOP_FUN_CTWW_2,
				WT5631_EN_ONE_BIT_DEPOP, 0);

	/* keep soft vowume and zewo cwossing setting */
	soft_vow = snd_soc_component_wead(component, WT5631_SOFT_VOW_CTWW);
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, 0);
	hp_zc = snd_soc_component_wead(component, WT5631_INT_ST_IWQ_CTWW_2);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc & 0xf7ff);
	if (enabwe) {
		scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(10));
		/* config one-bit depop pawametew */
		wt5631_wwite_index(component, WT5631_SPK_INTW_CTWW, 0x307f);
		snd_soc_component_update_bits(component, WT5631_HP_OUT_VOW,
				WT5631_W_MUTE | WT5631_W_MUTE, 0);
		msweep(300);
	} ewse {
		snd_soc_component_update_bits(component, WT5631_HP_OUT_VOW,
			WT5631_W_MUTE | WT5631_W_MUTE,
			WT5631_W_MUTE | WT5631_W_MUTE);
		msweep(100);
	}

	/* wecovew soft vowume and zewo cwossing setting */
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, soft_vow);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc);
}

/**
 * depop_seq_powew_stage - step by step depop sequence in powew stage.
 * @component: ASoC component
 * @enabwe: powew on/off
 *
 * When powew on/off headphone, the depop sequence is done in step by step.
 */
static void depop_seq_powew_stage(stwuct snd_soc_component *component, int enabwe)
{
	unsigned int soft_vow, hp_zc;

	/* depop contwow by wegistew */
	snd_soc_component_update_bits(component, WT5631_DEPOP_FUN_CTWW_2,
		WT5631_EN_ONE_BIT_DEPOP, WT5631_EN_ONE_BIT_DEPOP);

	/* keep soft vowume and zewo cwossing setting */
	soft_vow = snd_soc_component_wead(component, WT5631_SOFT_VOW_CTWW);
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, 0);
	hp_zc = snd_soc_component_wead(component, WT5631_INT_ST_IWQ_CTWW_2);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc & 0xf7ff);
	if (enabwe) {
		/* config depop sequence pawametew */
		wt5631_wwite_index(component, WT5631_SPK_INTW_CTWW, 0x303e);

		/* powew on headphone and chawge pump */
		snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
			WT5631_PWW_CHAWGE_PUMP | WT5631_PWW_HP_W_AMP |
			WT5631_PWW_HP_W_AMP,
			WT5631_PWW_CHAWGE_PUMP | WT5631_PWW_HP_W_AMP |
			WT5631_PWW_HP_W_AMP);

		/* powew on soft genewatow and depop mode2 */
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_1,
			WT5631_POW_ON_SOFT_GEN | WT5631_EN_DEPOP2_FOW_HP);
		msweep(100);

		/* stop depop mode */
		snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
			WT5631_PWW_HP_DEPOP_DIS, WT5631_PWW_HP_DEPOP_DIS);
	} ewse {
		/* config depop sequence pawametew */
		wt5631_wwite_index(component, WT5631_SPK_INTW_CTWW, 0x303F);
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_1,
			WT5631_POW_ON_SOFT_GEN | WT5631_EN_MUTE_UNMUTE_DEPOP |
			WT5631_PD_HPAMP_W_ST_UP | WT5631_PD_HPAMP_W_ST_UP);
		msweep(75);
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_1,
			WT5631_POW_ON_SOFT_GEN | WT5631_PD_HPAMP_W_ST_UP |
			WT5631_PD_HPAMP_W_ST_UP);

		/* stawt depop mode */
		snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
				WT5631_PWW_HP_DEPOP_DIS, 0);

		/* config depop sequence pawametew */
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_1,
			WT5631_POW_ON_SOFT_GEN | WT5631_EN_DEPOP2_FOW_HP |
			WT5631_PD_HPAMP_W_ST_UP | WT5631_PD_HPAMP_W_ST_UP);
		msweep(80);
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_1,
			WT5631_POW_ON_SOFT_GEN);

		/* powew down headphone and chawge pump */
		snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
			WT5631_PWW_CHAWGE_PUMP | WT5631_PWW_HP_W_AMP |
			WT5631_PWW_HP_W_AMP, 0);
	}

	/* wecovew soft vowume and zewo cwossing setting */
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, soft_vow);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc);
}

/**
 * depop_seq_mute_stage - step by step depop sequence in mute stage.
 * @component: ASoC component
 * @enabwe: mute/unmute
 *
 * When mute/unmute headphone, the depop sequence is done in step by step.
 */
static void depop_seq_mute_stage(stwuct snd_soc_component *component, int enabwe)
{
	unsigned int soft_vow, hp_zc;

	/* depop contwow by wegistew */
	snd_soc_component_update_bits(component, WT5631_DEPOP_FUN_CTWW_2,
		WT5631_EN_ONE_BIT_DEPOP, WT5631_EN_ONE_BIT_DEPOP);

	/* keep soft vowume and zewo cwossing setting */
	soft_vow = snd_soc_component_wead(component, WT5631_SOFT_VOW_CTWW);
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, 0);
	hp_zc = snd_soc_component_wead(component, WT5631_INT_ST_IWQ_CTWW_2);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc & 0xf7ff);
	if (enabwe) {
		scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(10));

		/* config depop sequence pawametew */
		wt5631_wwite_index(component, WT5631_SPK_INTW_CTWW, 0x302f);
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_1,
			WT5631_POW_ON_SOFT_GEN | WT5631_EN_MUTE_UNMUTE_DEPOP |
			WT5631_EN_HP_W_M_UN_MUTE_DEPOP |
			WT5631_EN_HP_W_M_UN_MUTE_DEPOP);

		snd_soc_component_update_bits(component, WT5631_HP_OUT_VOW,
				WT5631_W_MUTE | WT5631_W_MUTE, 0);
		msweep(160);
	} ewse {
		/* config depop sequence pawametew */
		wt5631_wwite_index(component, WT5631_SPK_INTW_CTWW, 0x302f);
		snd_soc_component_wwite(component, WT5631_DEPOP_FUN_CTWW_1,
			WT5631_POW_ON_SOFT_GEN | WT5631_EN_MUTE_UNMUTE_DEPOP |
			WT5631_EN_HP_W_M_UN_MUTE_DEPOP |
			WT5631_EN_HP_W_M_UN_MUTE_DEPOP);

		snd_soc_component_update_bits(component, WT5631_HP_OUT_VOW,
			WT5631_W_MUTE | WT5631_W_MUTE,
			WT5631_W_MUTE | WT5631_W_MUTE);
		msweep(150);
	}

	/* wecovew soft vowume and zewo cwossing setting */
	snd_soc_component_wwite(component, WT5631_SOFT_VOW_CTWW, soft_vow);
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, hp_zc);
}

static int hp_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMD:
		if (wt5631->codec_vewsion) {
			onebit_depop_mute_stage(component, 0);
			onebit_depop_powew_stage(component, 0);
		} ewse {
			depop_seq_mute_stage(component, 0);
			depop_seq_powew_stage(component, 0);
		}
		bweak;

	case SND_SOC_DAPM_POST_PMU:
		if (wt5631->codec_vewsion) {
			onebit_depop_powew_stage(component, 1);
			onebit_depop_mute_stage(component, 1);
		} ewse {
			depop_seq_powew_stage(component, 1);
			depop_seq_mute_stage(component, 1);
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int set_dmic_pawams(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);

	switch (wt5631->wx_wate) {
	case 44100:
	case 48000:
		snd_soc_component_update_bits(component, WT5631_DIG_MIC_CTWW,
			WT5631_DMIC_CWK_CTWW_MASK,
			WT5631_DMIC_CWK_CTWW_TO_32FS);
		bweak;

	case 32000:
	case 22050:
		snd_soc_component_update_bits(component, WT5631_DIG_MIC_CTWW,
			WT5631_DMIC_CWK_CTWW_MASK,
			WT5631_DMIC_CWK_CTWW_TO_64FS);
		bweak;

	case 16000:
	case 11025:
	case 8000:
		snd_soc_component_update_bits(component, WT5631_DIG_MIC_CTWW,
			WT5631_DMIC_CWK_CTWW_MASK,
			WT5631_DMIC_CWK_CTWW_TO_128FS);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_kcontwow_new wt5631_wecmixw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("OUTMIXW Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_OUTMIXW_WECMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC1_BST1 Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_MIC1_WECMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("AXIWVOW Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_AXIW_WECMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MONOIN_WX Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_MONO_IN_WECMIXW_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_wecmixw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("MONOIN_WX Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_MONO_IN_WECMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("AXIWVOW Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_AXIW_WECMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC2_BST2 Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_MIC2_WECMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("OUTMIXW Captuwe Switch", WT5631_ADC_WEC_MIXEW,
			WT5631_M_OUTMIXW_WECMIXW_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_spkmixw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("WECMIXW Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_WECMIXW_SPKMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC1_P Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_MIC1P_SPKMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("DACW Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_DACW_SPKMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("OUTMIXW Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_OUTMIXW_SPKMIXW_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_spkmixw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("OUTMIXW Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_OUTMIXW_SPKMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("DACW Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_DACW_SPKMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC2_P Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_MIC2P_SPKMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("WECMIXW Pwayback Switch", WT5631_SPK_MIXEW_CTWW,
			WT5631_M_WECMIXW_SPKMIXW_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_outmixw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("WECMIXW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_WECMIXW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("WECMIXW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_WECMIXW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("DACW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_DACW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC1_BST1 Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_MIC1_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC2_BST2 Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_MIC2_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MONOIN_WXP Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_MONO_INP_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("AXIWVOW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_AXIW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("AXIWVOW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_AXIW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("VDAC Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_VDAC_OUTMIXW_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_outmixw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("VDAC Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_VDAC_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("AXIWVOW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_AXIW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("AXIWVOW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_AXIW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MONOIN_WXN Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_MONO_INN_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC2_BST2 Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_MIC2_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC1_BST1 Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_MIC1_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("DACW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_DACW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("WECMIXW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_WECMIXW_OUTMIXW_BIT, 1, 1),
	SOC_DAPM_SINGWE("WECMIXW Pwayback Switch", WT5631_OUTMIXEW_W_CTWW,
				WT5631_M_WECMIXW_OUTMIXW_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_AXO1MIX_mixew_contwows[] = {
	SOC_DAPM_SINGWE("MIC1_BST1 Pwayback Switch", WT5631_AXO1MIXEW_CTWW,
				WT5631_M_MIC1_AXO1MIX_BIT , 1, 1),
	SOC_DAPM_SINGWE("MIC2_BST2 Pwayback Switch", WT5631_AXO1MIXEW_CTWW,
				WT5631_M_MIC2_AXO1MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("OUTVOWW Pwayback Switch", WT5631_AXO1MIXEW_CTWW,
				WT5631_M_OUTMIXW_AXO1MIX_BIT , 1 , 1),
	SOC_DAPM_SINGWE("OUTVOWW Pwayback Switch", WT5631_AXO1MIXEW_CTWW,
				WT5631_M_OUTMIXW_AXO1MIX_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_AXO2MIX_mixew_contwows[] = {
	SOC_DAPM_SINGWE("MIC1_BST1 Pwayback Switch", WT5631_AXO2MIXEW_CTWW,
				WT5631_M_MIC1_AXO2MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("MIC2_BST2 Pwayback Switch", WT5631_AXO2MIXEW_CTWW,
				WT5631_M_MIC2_AXO2MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("OUTVOWW Pwayback Switch", WT5631_AXO2MIXEW_CTWW,
				WT5631_M_OUTMIXW_AXO2MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("OUTVOWW Pwayback Switch", WT5631_AXO2MIXEW_CTWW,
				WT5631_M_OUTMIXW_AXO2MIX_BIT, 1 , 1),
};

static const stwuct snd_kcontwow_new wt5631_spowmix_mixew_contwows[] = {
	SOC_DAPM_SINGWE("SPKVOWW Pwayback Switch", WT5631_SPK_MONO_OUT_CTWW,
				WT5631_M_SPKVOWW_SPOWMIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("SPKVOWW Pwayback Switch", WT5631_SPK_MONO_OUT_CTWW,
				WT5631_M_SPKVOWW_SPOWMIX_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_spowmix_mixew_contwows[] = {
	SOC_DAPM_SINGWE("SPKVOWW Pwayback Switch", WT5631_SPK_MONO_OUT_CTWW,
				WT5631_M_SPKVOWW_SPOWMIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("SPKVOWW Pwayback Switch", WT5631_SPK_MONO_OUT_CTWW,
				WT5631_M_SPKVOWW_SPOWMIX_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5631_monomix_mixew_contwows[] = {
	SOC_DAPM_SINGWE("OUTVOWW Pwayback Switch", WT5631_SPK_MONO_OUT_CTWW,
				WT5631_M_OUTVOWW_MONOMIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("OUTVOWW Pwayback Switch", WT5631_SPK_MONO_OUT_CTWW,
				WT5631_M_OUTVOWW_MONOMIX_BIT, 1, 1),
};

/* Weft SPK Vowume Input */
static const chaw *wt5631_spkvoww_sew[] = {"Vmid", "SPKMIXW"};

static SOC_ENUM_SINGWE_DECW(wt5631_spkvoww_enum, WT5631_SPK_OUT_VOW,
			    WT5631_W_EN_SHIFT, wt5631_spkvoww_sew);

static const stwuct snd_kcontwow_new wt5631_spkvoww_mux_contwow =
	SOC_DAPM_ENUM("Weft SPKVOW SWC", wt5631_spkvoww_enum);

/* Weft HP Vowume Input */
static const chaw *wt5631_hpvoww_sew[] = {"Vmid", "OUTMIXW"};

static SOC_ENUM_SINGWE_DECW(wt5631_hpvoww_enum, WT5631_HP_OUT_VOW,
			    WT5631_W_EN_SHIFT, wt5631_hpvoww_sew);

static const stwuct snd_kcontwow_new wt5631_hpvoww_mux_contwow =
	SOC_DAPM_ENUM("Weft HPVOW SWC", wt5631_hpvoww_enum);

/* Weft Out Vowume Input */
static const chaw *wt5631_outvoww_sew[] = {"Vmid", "OUTMIXW"};

static SOC_ENUM_SINGWE_DECW(wt5631_outvoww_enum, WT5631_MONO_AXO_1_2_VOW,
			    WT5631_W_EN_SHIFT, wt5631_outvoww_sew);

static const stwuct snd_kcontwow_new wt5631_outvoww_mux_contwow =
	SOC_DAPM_ENUM("Weft OUTVOW SWC", wt5631_outvoww_enum);

/* Wight Out Vowume Input */
static const chaw *wt5631_outvoww_sew[] = {"Vmid", "OUTMIXW"};

static SOC_ENUM_SINGWE_DECW(wt5631_outvoww_enum, WT5631_MONO_AXO_1_2_VOW,
			    WT5631_W_EN_SHIFT, wt5631_outvoww_sew);

static const stwuct snd_kcontwow_new wt5631_outvoww_mux_contwow =
	SOC_DAPM_ENUM("Wight OUTVOW SWC", wt5631_outvoww_enum);

/* Wight HP Vowume Input */
static const chaw *wt5631_hpvoww_sew[] = {"Vmid", "OUTMIXW"};

static SOC_ENUM_SINGWE_DECW(wt5631_hpvoww_enum, WT5631_HP_OUT_VOW,
			    WT5631_W_EN_SHIFT, wt5631_hpvoww_sew);

static const stwuct snd_kcontwow_new wt5631_hpvoww_mux_contwow =
	SOC_DAPM_ENUM("Wight HPVOW SWC", wt5631_hpvoww_enum);

/* Wight SPK Vowume Input */
static const chaw *wt5631_spkvoww_sew[] = {"Vmid", "SPKMIXW"};

static SOC_ENUM_SINGWE_DECW(wt5631_spkvoww_enum, WT5631_SPK_OUT_VOW,
			    WT5631_W_EN_SHIFT, wt5631_spkvoww_sew);

static const stwuct snd_kcontwow_new wt5631_spkvoww_mux_contwow =
	SOC_DAPM_ENUM("Wight SPKVOW SWC", wt5631_spkvoww_enum);

/* SPO Weft Channew Input */
static const chaw *wt5631_spow_swc_sew[] = {
	"SPOWMIX", "MONOIN_WX", "VDAC", "DACW"};

static SOC_ENUM_SINGWE_DECW(wt5631_spow_swc_enum, WT5631_SPK_MONO_HP_OUT_CTWW,
			    WT5631_SPK_W_MUX_SEW_SHIFT, wt5631_spow_swc_sew);

static const stwuct snd_kcontwow_new wt5631_spow_mux_contwow =
	SOC_DAPM_ENUM("SPOW SWC", wt5631_spow_swc_enum);

/* SPO Wight Channew Input */
static const chaw *wt5631_spow_swc_sew[] = {
	"SPOWMIX", "MONOIN_WX", "VDAC", "DACW"};

static SOC_ENUM_SINGWE_DECW(wt5631_spow_swc_enum, WT5631_SPK_MONO_HP_OUT_CTWW,
			    WT5631_SPK_W_MUX_SEW_SHIFT, wt5631_spow_swc_sew);

static const stwuct snd_kcontwow_new wt5631_spow_mux_contwow =
	SOC_DAPM_ENUM("SPOW SWC", wt5631_spow_swc_enum);

/* MONO Input */
static const chaw *wt5631_mono_swc_sew[] = {"MONOMIX", "MONOIN_WX", "VDAC"};

static SOC_ENUM_SINGWE_DECW(wt5631_mono_swc_enum, WT5631_SPK_MONO_HP_OUT_CTWW,
			    WT5631_MONO_MUX_SEW_SHIFT, wt5631_mono_swc_sew);

static const stwuct snd_kcontwow_new wt5631_mono_mux_contwow =
	SOC_DAPM_ENUM("MONO SWC", wt5631_mono_swc_enum);

/* Weft HPO Input */
static const chaw *wt5631_hpw_swc_sew[] = {"Weft HPVOW", "Weft DAC"};

static SOC_ENUM_SINGWE_DECW(wt5631_hpw_swc_enum, WT5631_SPK_MONO_HP_OUT_CTWW,
			    WT5631_HP_W_MUX_SEW_SHIFT, wt5631_hpw_swc_sew);

static const stwuct snd_kcontwow_new wt5631_hpw_mux_contwow =
	SOC_DAPM_ENUM("HPW SWC", wt5631_hpw_swc_enum);

/* Wight HPO Input */
static const chaw *wt5631_hpw_swc_sew[] = {"Wight HPVOW", "Wight DAC"};

static SOC_ENUM_SINGWE_DECW(wt5631_hpw_swc_enum, WT5631_SPK_MONO_HP_OUT_CTWW,
			    WT5631_HP_W_MUX_SEW_SHIFT, wt5631_hpw_swc_sew);

static const stwuct snd_kcontwow_new wt5631_hpw_mux_contwow =
	SOC_DAPM_ENUM("HPW SWC", wt5631_hpw_swc_enum);

static const stwuct snd_soc_dapm_widget wt5631_dapm_widgets[] = {
	/* Vmid */
	SND_SOC_DAPM_VMID("Vmid"),
	/* PWW1 */
	SND_SOC_DAPM_SUPPWY("PWW1", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_PWW1_BIT, 0, NUWW, 0),

	/* Input Side */
	/* Input Wines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("AXIW"),
	SND_SOC_DAPM_INPUT("AXIW"),
	SND_SOC_DAPM_INPUT("MONOIN_WXN"),
	SND_SOC_DAPM_INPUT("MONOIN_WXP"),
	SND_SOC_DAPM_INPUT("DMIC"),

	/* MICBIAS */
	SND_SOC_DAPM_MICBIAS("MIC Bias1", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_MICBIAS1_VOW_BIT, 0),
	SND_SOC_DAPM_MICBIAS("MIC Bias2", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_MICBIAS2_VOW_BIT, 0),

	/* Boost */
	SND_SOC_DAPM_PGA("MIC1 Boost", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_MIC1_BOOT_GAIN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MIC2 Boost", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_MIC2_BOOT_GAIN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MONOIN_WXP Boost", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_MONO_IN_P_VOW_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MONOIN_WXN Boost", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_MONO_IN_N_VOW_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AXIW Boost", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_AXIW_IN_VOW_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AXIW Boost", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_AXIW_IN_VOW_BIT, 0, NUWW, 0),

	/* MONO In */
	SND_SOC_DAPM_MIXEW("MONO_IN", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* WEC Mixew */
	SND_SOC_DAPM_MIXEW("WECMIXW Mixew", WT5631_PWW_MANAG_ADD2,
		WT5631_PWW_WECMIXEW_W_BIT, 0,
		&wt5631_wecmixw_mixew_contwows[0],
		AWWAY_SIZE(wt5631_wecmixw_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WECMIXW Mixew", WT5631_PWW_MANAG_ADD2,
		WT5631_PWW_WECMIXEW_W_BIT, 0,
		&wt5631_wecmixw_mixew_contwows[0],
		AWWAY_SIZE(wt5631_wecmixw_mixew_contwows)),
	/* Because of wecowd dupwication fow W/W channew,
	 * W/W ADCs need powew up at the same time */
	SND_SOC_DAPM_MIXEW("ADC Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* DMIC */
	SND_SOC_DAPM_SUPPWY("DMIC Suppwy", WT5631_DIG_MIC_CTWW,
		WT5631_DMIC_ENA_SHIFT, 0,
		set_dmic_pawams, SND_SOC_DAPM_PWE_PMU),
	/* ADC Data Swouce */
	SND_SOC_DAPM_SUPPWY("Weft ADC Sewect", WT5631_INT_ST_IWQ_CTWW_2,
			WT5631_ADC_DATA_SEW_MIC1_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Wight ADC Sewect", WT5631_INT_ST_IWQ_CTWW_2,
			WT5631_ADC_DATA_SEW_MIC2_SHIFT, 0, NUWW, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("Weft ADC", "HIFI Captuwe",
		WT5631_PWW_MANAG_ADD1, WT5631_PWW_ADC_W_CWK_BIT, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "HIFI Captuwe",
		WT5631_PWW_MANAG_ADD1, WT5631_PWW_ADC_W_CWK_BIT, 0),

	/* DAC and ADC suppwy powew */
	SND_SOC_DAPM_SUPPWY("I2S", WT5631_PWW_MANAG_ADD1,
			WT5631_PWW_MAIN_I2S_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC WEF", WT5631_PWW_MANAG_ADD1,
			WT5631_PWW_DAC_WEF_BIT, 0, NUWW, 0),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("Weft DAC", "HIFI Pwayback",
		WT5631_PWW_MANAG_ADD1, WT5631_PWW_DAC_W_CWK_BIT, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "HIFI Pwayback",
		WT5631_PWW_MANAG_ADD1, WT5631_PWW_DAC_W_CWK_BIT, 0),
	SND_SOC_DAPM_DAC("Voice DAC", "Voice DAC Mono Pwayback",
				SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("Voice DAC Boost", SND_SOC_NOPM, 0, 0, NUWW, 0),
	/* DAC suppwy powew */
	SND_SOC_DAPM_SUPPWY("Weft DAC To Mixew", WT5631_PWW_MANAG_ADD1,
			WT5631_PWW_DAC_W_TO_MIXEW_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Wight DAC To Mixew", WT5631_PWW_MANAG_ADD1,
			WT5631_PWW_DAC_W_TO_MIXEW_BIT, 0, NUWW, 0),

	/* Weft SPK Mixew */
	SND_SOC_DAPM_MIXEW("SPKMIXW Mixew", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_SPKMIXEW_W_BIT, 0,
			&wt5631_spkmixw_mixew_contwows[0],
			AWWAY_SIZE(wt5631_spkmixw_mixew_contwows)),
	/* Weft Out Mixew */
	SND_SOC_DAPM_MIXEW("OUTMIXW Mixew", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_OUTMIXEW_W_BIT, 0,
			&wt5631_outmixw_mixew_contwows[0],
			AWWAY_SIZE(wt5631_outmixw_mixew_contwows)),
	/* Wight Out Mixew */
	SND_SOC_DAPM_MIXEW("OUTMIXW Mixew", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_OUTMIXEW_W_BIT, 0,
			&wt5631_outmixw_mixew_contwows[0],
			AWWAY_SIZE(wt5631_outmixw_mixew_contwows)),
	/* Wight SPK Mixew */
	SND_SOC_DAPM_MIXEW("SPKMIXW Mixew", WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_SPKMIXEW_W_BIT, 0,
			&wt5631_spkmixw_mixew_contwows[0],
			AWWAY_SIZE(wt5631_spkmixw_mixew_contwows)),

	/* Vowume Mux */
	SND_SOC_DAPM_MUX("Weft SPKVOW Mux", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_SPK_W_VOW_BIT, 0,
			&wt5631_spkvoww_mux_contwow),
	SND_SOC_DAPM_MUX("Weft HPVOW Mux", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_HP_W_OUT_VOW_BIT, 0,
			&wt5631_hpvoww_mux_contwow),
	SND_SOC_DAPM_MUX("Weft OUTVOW Mux", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_WOUT_VOW_BIT, 0,
			&wt5631_outvoww_mux_contwow),
	SND_SOC_DAPM_MUX("Wight OUTVOW Mux", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_WOUT_VOW_BIT, 0,
			&wt5631_outvoww_mux_contwow),
	SND_SOC_DAPM_MUX("Wight HPVOW Mux", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_HP_W_OUT_VOW_BIT, 0,
			&wt5631_hpvoww_mux_contwow),
	SND_SOC_DAPM_MUX("Wight SPKVOW Mux", WT5631_PWW_MANAG_ADD4,
			WT5631_PWW_SPK_W_VOW_BIT, 0,
			&wt5631_spkvoww_mux_contwow),

	/* DAC To HP */
	SND_SOC_DAPM_PGA_S("Weft DAC_HP", 0, SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Wight DAC_HP", 0, SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* HP Depop */
	SND_SOC_DAPM_PGA_S("HP Depop", 1, SND_SOC_NOPM, 0, 0,
		hp_event, SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),

	/* AXO1 Mixew */
	SND_SOC_DAPM_MIXEW("AXO1MIX Mixew", WT5631_PWW_MANAG_ADD3,
			WT5631_PWW_AXO1MIXEW_BIT, 0,
			&wt5631_AXO1MIX_mixew_contwows[0],
			AWWAY_SIZE(wt5631_AXO1MIX_mixew_contwows)),
	/* SPOW Mixew */
	SND_SOC_DAPM_MIXEW("SPOWMIX Mixew", SND_SOC_NOPM, 0, 0,
			&wt5631_spowmix_mixew_contwows[0],
			AWWAY_SIZE(wt5631_spowmix_mixew_contwows)),
	/* MONO Mixew */
	SND_SOC_DAPM_MIXEW("MONOMIX Mixew", WT5631_PWW_MANAG_ADD3,
			WT5631_PWW_MONOMIXEW_BIT, 0,
			&wt5631_monomix_mixew_contwows[0],
			AWWAY_SIZE(wt5631_monomix_mixew_contwows)),
	/* SPOW Mixew */
	SND_SOC_DAPM_MIXEW("SPOWMIX Mixew", SND_SOC_NOPM, 0, 0,
			&wt5631_spowmix_mixew_contwows[0],
			AWWAY_SIZE(wt5631_spowmix_mixew_contwows)),
	/* AXO2 Mixew */
	SND_SOC_DAPM_MIXEW("AXO2MIX Mixew", WT5631_PWW_MANAG_ADD3,
			WT5631_PWW_AXO2MIXEW_BIT, 0,
			&wt5631_AXO2MIX_mixew_contwows[0],
			AWWAY_SIZE(wt5631_AXO2MIX_mixew_contwows)),

	/* Mux */
	SND_SOC_DAPM_MUX("SPOW Mux", SND_SOC_NOPM, 0, 0,
			&wt5631_spow_mux_contwow),
	SND_SOC_DAPM_MUX("SPOW Mux", SND_SOC_NOPM, 0, 0,
			&wt5631_spow_mux_contwow),
	SND_SOC_DAPM_MUX("MONO Mux", SND_SOC_NOPM, 0, 0,
			&wt5631_mono_mux_contwow),
	SND_SOC_DAPM_MUX("HPW Mux", SND_SOC_NOPM, 0, 0,
			&wt5631_hpw_mux_contwow),
	SND_SOC_DAPM_MUX("HPW Mux", SND_SOC_NOPM, 0, 0,
			&wt5631_hpw_mux_contwow),

	/* AMP suppwy */
	SND_SOC_DAPM_SUPPWY("MONO Depop", WT5631_PWW_MANAG_ADD3,
			WT5631_PWW_MONO_DEPOP_DIS_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Cwass D", WT5631_PWW_MANAG_ADD1,
			WT5631_PWW_CWASS_D_BIT, 0, NUWW, 0),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("AUXO1"),
	SND_SOC_DAPM_OUTPUT("AUXO2"),
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("MONO"),
};

static const stwuct snd_soc_dapm_woute wt5631_dapm_woutes[] = {
	{"MIC1 Boost", NUWW, "MIC1"},
	{"MIC2 Boost", NUWW, "MIC2"},
	{"MONOIN_WXP Boost", NUWW, "MONOIN_WXP"},
	{"MONOIN_WXN Boost", NUWW, "MONOIN_WXN"},
	{"AXIW Boost", NUWW, "AXIW"},
	{"AXIW Boost", NUWW, "AXIW"},

	{"MONO_IN", NUWW, "MONOIN_WXP Boost"},
	{"MONO_IN", NUWW, "MONOIN_WXN Boost"},

	{"WECMIXW Mixew", "OUTMIXW Captuwe Switch", "OUTMIXW Mixew"},
	{"WECMIXW Mixew", "MIC1_BST1 Captuwe Switch", "MIC1 Boost"},
	{"WECMIXW Mixew", "AXIWVOW Captuwe Switch", "AXIW Boost"},
	{"WECMIXW Mixew", "MONOIN_WX Captuwe Switch", "MONO_IN"},

	{"WECMIXW Mixew", "OUTMIXW Captuwe Switch", "OUTMIXW Mixew"},
	{"WECMIXW Mixew", "MIC2_BST2 Captuwe Switch", "MIC2 Boost"},
	{"WECMIXW Mixew", "AXIWVOW Captuwe Switch", "AXIW Boost"},
	{"WECMIXW Mixew", "MONOIN_WX Captuwe Switch", "MONO_IN"},

	{"ADC Mixew", NUWW, "WECMIXW Mixew"},
	{"ADC Mixew", NUWW, "WECMIXW Mixew"},

	{"Weft ADC", NUWW, "ADC Mixew"},
	{"Weft ADC", NUWW, "Weft ADC Sewect", check_adcw_sewect},
	{"Weft ADC", NUWW, "PWW1", check_syscwk1_souwce},
	{"Weft ADC", NUWW, "I2S"},
	{"Weft ADC", NUWW, "DAC WEF"},

	{"Wight ADC", NUWW, "ADC Mixew"},
	{"Wight ADC", NUWW, "Wight ADC Sewect", check_adcw_sewect},
	{"Wight ADC", NUWW, "PWW1", check_syscwk1_souwce},
	{"Wight ADC", NUWW, "I2S"},
	{"Wight ADC", NUWW, "DAC WEF"},

	{"DMIC", NUWW, "DMIC Suppwy", check_dmic_used},
	{"Weft ADC", NUWW, "DMIC"},
	{"Wight ADC", NUWW, "DMIC"},

	{"Weft DAC", NUWW, "PWW1", check_syscwk1_souwce},
	{"Weft DAC", NUWW, "I2S"},
	{"Weft DAC", NUWW, "DAC WEF"},
	{"Wight DAC", NUWW, "PWW1", check_syscwk1_souwce},
	{"Wight DAC", NUWW, "I2S"},
	{"Wight DAC", NUWW, "DAC WEF"},

	{"Voice DAC Boost", NUWW, "Voice DAC"},

	{"SPKMIXW Mixew", NUWW, "Weft DAC To Mixew", check_dacw_to_spkmixw},
	{"SPKMIXW Mixew", "WECMIXW Pwayback Switch", "WECMIXW Mixew"},
	{"SPKMIXW Mixew", "MIC1_P Pwayback Switch", "MIC1"},
	{"SPKMIXW Mixew", "DACW Pwayback Switch", "Weft DAC"},
	{"SPKMIXW Mixew", "OUTMIXW Pwayback Switch", "OUTMIXW Mixew"},

	{"SPKMIXW Mixew", NUWW, "Wight DAC To Mixew", check_dacw_to_spkmixw},
	{"SPKMIXW Mixew", "OUTMIXW Pwayback Switch", "OUTMIXW Mixew"},
	{"SPKMIXW Mixew", "DACW Pwayback Switch", "Wight DAC"},
	{"SPKMIXW Mixew", "MIC2_P Pwayback Switch", "MIC2"},
	{"SPKMIXW Mixew", "WECMIXW Pwayback Switch", "WECMIXW Mixew"},

	{"OUTMIXW Mixew", NUWW, "Weft DAC To Mixew", check_dacw_to_outmixw},
	{"OUTMIXW Mixew", "WECMIXW Pwayback Switch", "WECMIXW Mixew"},
	{"OUTMIXW Mixew", "WECMIXW Pwayback Switch", "WECMIXW Mixew"},
	{"OUTMIXW Mixew", "DACW Pwayback Switch", "Weft DAC"},
	{"OUTMIXW Mixew", "MIC1_BST1 Pwayback Switch", "MIC1 Boost"},
	{"OUTMIXW Mixew", "MIC2_BST2 Pwayback Switch", "MIC2 Boost"},
	{"OUTMIXW Mixew", "MONOIN_WXP Pwayback Switch", "MONOIN_WXP Boost"},
	{"OUTMIXW Mixew", "AXIWVOW Pwayback Switch", "AXIW Boost"},
	{"OUTMIXW Mixew", "AXIWVOW Pwayback Switch", "AXIW Boost"},
	{"OUTMIXW Mixew", "VDAC Pwayback Switch", "Voice DAC Boost"},

	{"OUTMIXW Mixew", NUWW, "Wight DAC To Mixew", check_dacw_to_outmixw},
	{"OUTMIXW Mixew", "WECMIXW Pwayback Switch", "WECMIXW Mixew"},
	{"OUTMIXW Mixew", "WECMIXW Pwayback Switch", "WECMIXW Mixew"},
	{"OUTMIXW Mixew", "DACW Pwayback Switch", "Wight DAC"},
	{"OUTMIXW Mixew", "MIC1_BST1 Pwayback Switch", "MIC1 Boost"},
	{"OUTMIXW Mixew", "MIC2_BST2 Pwayback Switch", "MIC2 Boost"},
	{"OUTMIXW Mixew", "MONOIN_WXN Pwayback Switch", "MONOIN_WXN Boost"},
	{"OUTMIXW Mixew", "AXIWVOW Pwayback Switch", "AXIW Boost"},
	{"OUTMIXW Mixew", "AXIWVOW Pwayback Switch", "AXIW Boost"},
	{"OUTMIXW Mixew", "VDAC Pwayback Switch", "Voice DAC Boost"},

	{"Weft SPKVOW Mux",  "SPKMIXW", "SPKMIXW Mixew"},
	{"Weft SPKVOW Mux",  "Vmid", "Vmid"},
	{"Weft HPVOW Mux",  "OUTMIXW", "OUTMIXW Mixew"},
	{"Weft HPVOW Mux",  "Vmid", "Vmid"},
	{"Weft OUTVOW Mux",  "OUTMIXW", "OUTMIXW Mixew"},
	{"Weft OUTVOW Mux",  "Vmid", "Vmid"},
	{"Wight OUTVOW Mux",  "OUTMIXW", "OUTMIXW Mixew"},
	{"Wight OUTVOW Mux",  "Vmid", "Vmid"},
	{"Wight HPVOW Mux",  "OUTMIXW", "OUTMIXW Mixew"},
	{"Wight HPVOW Mux",  "Vmid", "Vmid"},
	{"Wight SPKVOW Mux",  "SPKMIXW", "SPKMIXW Mixew"},
	{"Wight SPKVOW Mux",  "Vmid", "Vmid"},

	{"AXO1MIX Mixew", "MIC1_BST1 Pwayback Switch", "MIC1 Boost"},
	{"AXO1MIX Mixew", "OUTVOWW Pwayback Switch", "Weft OUTVOW Mux"},
	{"AXO1MIX Mixew", "OUTVOWW Pwayback Switch", "Wight OUTVOW Mux"},
	{"AXO1MIX Mixew", "MIC2_BST2 Pwayback Switch", "MIC2 Boost"},

	{"AXO2MIX Mixew", "MIC1_BST1 Pwayback Switch", "MIC1 Boost"},
	{"AXO2MIX Mixew", "OUTVOWW Pwayback Switch", "Weft OUTVOW Mux"},
	{"AXO2MIX Mixew", "OUTVOWW Pwayback Switch", "Wight OUTVOW Mux"},
	{"AXO2MIX Mixew", "MIC2_BST2 Pwayback Switch", "MIC2 Boost"},

	{"SPOWMIX Mixew", "SPKVOWW Pwayback Switch", "Weft SPKVOW Mux"},
	{"SPOWMIX Mixew", "SPKVOWW Pwayback Switch", "Wight SPKVOW Mux"},

	{"SPOWMIX Mixew", "SPKVOWW Pwayback Switch", "Weft SPKVOW Mux"},
	{"SPOWMIX Mixew", "SPKVOWW Pwayback Switch", "Wight SPKVOW Mux"},

	{"MONOMIX Mixew", "OUTVOWW Pwayback Switch", "Weft OUTVOW Mux"},
	{"MONOMIX Mixew", "OUTVOWW Pwayback Switch", "Wight OUTVOW Mux"},

	{"SPOW Mux", "SPOWMIX", "SPOWMIX Mixew"},
	{"SPOW Mux", "MONOIN_WX", "MONO_IN"},
	{"SPOW Mux", "VDAC", "Voice DAC Boost"},
	{"SPOW Mux", "DACW", "Weft DAC"},

	{"SPOW Mux", "SPOWMIX", "SPOWMIX Mixew"},
	{"SPOW Mux", "MONOIN_WX", "MONO_IN"},
	{"SPOW Mux", "VDAC", "Voice DAC Boost"},
	{"SPOW Mux", "DACW", "Wight DAC"},

	{"MONO Mux", "MONOMIX", "MONOMIX Mixew"},
	{"MONO Mux", "MONOIN_WX", "MONO_IN"},
	{"MONO Mux", "VDAC", "Voice DAC Boost"},

	{"Wight DAC_HP", NUWW, "Wight DAC"},
	{"Weft DAC_HP", NUWW, "Weft DAC"},

	{"HPW Mux", "Weft HPVOW", "Weft HPVOW Mux"},
	{"HPW Mux", "Weft DAC", "Weft DAC_HP"},
	{"HPW Mux", "Wight HPVOW", "Wight HPVOW Mux"},
	{"HPW Mux", "Wight DAC", "Wight DAC_HP"},

	{"HP Depop", NUWW, "HPW Mux"},
	{"HP Depop", NUWW, "HPW Mux"},

	{"AUXO1", NUWW, "AXO1MIX Mixew"},
	{"AUXO2", NUWW, "AXO2MIX Mixew"},

	{"SPOW", NUWW, "Cwass D"},
	{"SPOW", NUWW, "SPOW Mux"},
	{"SPOW", NUWW, "Cwass D"},
	{"SPOW", NUWW, "SPOW Mux"},

	{"HPOW", NUWW, "HP Depop"},
	{"HPOW", NUWW, "HP Depop"},

	{"MONO", NUWW, "MONO Depop"},
	{"MONO", NUWW, "MONO Mux"},
};

stwuct coeff_cwk_div {
	u32 mcwk;
	u32 bcwk;
	u32 wate;
	u16 weg_vaw;
};

/* PWW divisows */
stwuct pww_div {
	u32 pww_in;
	u32 pww_out;
	u16 weg_vaw;
};

static const stwuct pww_div codec_mastew_pww_div[] = {
	{2048000,  8192000,  0x0ea0},
	{3686400,  8192000,  0x4e27},
	{12000000,  8192000,  0x456b},
	{13000000,  8192000,  0x495f},
	{13100000,  8192000,  0x0320},
	{2048000,  11289600,  0xf637},
	{3686400,  11289600,  0x2f22},
	{12000000,  11289600,  0x3e2f},
	{13000000,  11289600,  0x4d5b},
	{13100000,  11289600,  0x363b},
	{2048000,  16384000,  0x1ea0},
	{3686400,  16384000,  0x9e27},
	{12000000,  16384000,  0x452b},
	{13000000,  16384000,  0x542f},
	{13100000,  16384000,  0x03a0},
	{2048000,  16934400,  0xe625},
	{3686400,  16934400,  0x9126},
	{12000000,  16934400,  0x4d2c},
	{13000000,  16934400,  0x742f},
	{13100000,  16934400,  0x3c27},
	{2048000,  22579200,  0x2aa0},
	{3686400,  22579200,  0x2f20},
	{12000000,  22579200,  0x7e2f},
	{13000000,  22579200,  0x742f},
	{13100000,  22579200,  0x3c27},
	{2048000,  24576000,  0x2ea0},
	{3686400,  24576000,  0xee27},
	{12000000,  24576000,  0x2915},
	{13000000,  24576000,  0x772e},
	{13100000,  24576000,  0x0d20},
	{26000000,  24576000,  0x2027},
	{26000000,  22579200,  0x392f},
	{24576000,  22579200,  0x0921},
	{24576000,  24576000,  0x02a0},
};

static const stwuct pww_div codec_swave_pww_div[] = {
	{256000,  2048000,  0x46f0},
	{256000,  4096000,  0x3ea0},
	{352800,  5644800,  0x3ea0},
	{512000,  8192000,  0x3ea0},
	{1024000,  8192000,  0x46f0},
	{705600,  11289600,  0x3ea0},
	{1024000,  16384000,  0x3ea0},
	{1411200,  22579200,  0x3ea0},
	{1536000,  24576000,  0x3ea0},
	{2048000,  16384000,  0x1ea0},
	{2822400,  22579200,  0x1ea0},
	{2822400,  45158400,  0x5ec0},
	{5644800,  45158400,  0x46f0},
	{3072000,  24576000,  0x1ea0},
	{3072000,  49152000,  0x5ec0},
	{6144000,  49152000,  0x46f0},
	{705600,  11289600,  0x3ea0},
	{705600,  8467200,  0x3ab0},
	{24576000,  24576000,  0x02a0},
	{1411200,  11289600,  0x1690},
	{2822400,  11289600,  0x0a90},
	{1536000,  12288000,  0x1690},
	{3072000,  12288000,  0x0a90},
};

static const stwuct coeff_cwk_div coeff_div[] = {
	/* syscwk is 256fs */
	{2048000,  8000 * 32,  8000, 0x1000},
	{2048000,  8000 * 64,  8000, 0x0000},
	{2822400,  11025 * 32,  11025,  0x1000},
	{2822400,  11025 * 64,  11025,  0x0000},
	{4096000,  16000 * 32,  16000,  0x1000},
	{4096000,  16000 * 64,  16000,  0x0000},
	{5644800,  22050 * 32,  22050,  0x1000},
	{5644800,  22050 * 64,  22050,  0x0000},
	{8192000,  32000 * 32,  32000,  0x1000},
	{8192000,  32000 * 64,  32000,  0x0000},
	{11289600,  44100 * 32,  44100,  0x1000},
	{11289600,  44100 * 64,  44100,  0x0000},
	{12288000,  48000 * 32,  48000,  0x1000},
	{12288000,  48000 * 64,  48000,  0x0000},
	{22579200,  88200 * 32,  88200,  0x1000},
	{22579200,  88200 * 64,  88200,  0x0000},
	{24576000,  96000 * 32,  96000,  0x1000},
	{24576000,  96000 * 64,  96000,  0x0000},
	/* syscwk is 512fs */
	{4096000,  8000 * 32,  8000, 0x3000},
	{4096000,  8000 * 64,  8000, 0x2000},
	{5644800,  11025 * 32,  11025, 0x3000},
	{5644800,  11025 * 64,  11025, 0x2000},
	{8192000,  16000 * 32,  16000, 0x3000},
	{8192000,  16000 * 64,  16000, 0x2000},
	{11289600,  22050 * 32,  22050, 0x3000},
	{11289600,  22050 * 64,  22050, 0x2000},
	{16384000,  32000 * 32,  32000, 0x3000},
	{16384000,  32000 * 64,  32000, 0x2000},
	{22579200,  44100 * 32,  44100, 0x3000},
	{22579200,  44100 * 64,  44100, 0x2000},
	{24576000,  48000 * 32,  48000, 0x3000},
	{24576000,  48000 * 64,  48000, 0x2000},
	{45158400,  88200 * 32,  88200, 0x3000},
	{45158400,  88200 * 64,  88200, 0x2000},
	{49152000,  96000 * 32,  96000, 0x3000},
	{49152000,  96000 * 64,  96000, 0x2000},
	/* syscwk is 24.576Mhz ow 22.5792Mhz */
	{24576000,  8000 * 32,  8000,  0x7080},
	{24576000,  8000 * 64,  8000,  0x6080},
	{24576000,  16000 * 32,  16000,  0x5080},
	{24576000,  16000 * 64,  16000,  0x4080},
	{24576000,  24000 * 32,  24000,  0x5000},
	{24576000,  24000 * 64,  24000,  0x4000},
	{24576000,  32000 * 32,  32000,  0x3080},
	{24576000,  32000 * 64,  32000,  0x2080},
	{22579200,  11025 * 32,  11025,  0x7000},
	{22579200,  11025 * 64,  11025,  0x6000},
	{22579200,  22050 * 32,  22050,  0x5000},
	{22579200,  22050 * 64,  22050,  0x4000},
};

static int get_coeff(int mcwk, int wate, int timesofbcwk)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].mcwk == mcwk && coeff_div[i].wate == wate &&
			(coeff_div[i].bcwk / coeff_div[i].wate) == timesofbcwk)
			wetuwn i;
	}
	wetuwn -EINVAW;
}

static int wt5631_hifi_pcm_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);
	int timesofbcwk = 32, coeff;
	unsigned int iface = 0;

	dev_dbg(component->dev, "entew %s\n", __func__);

	wt5631->bcwk_wate = snd_soc_pawams_to_bcwk(pawams);
	if (wt5631->bcwk_wate < 0) {
		dev_eww(component->dev, "Faiw to get BCWK wate\n");
		wetuwn wt5631->bcwk_wate;
	}
	wt5631->wx_wate = pawams_wate(pawams);

	if (wt5631->mastew)
		coeff = get_coeff(wt5631->syscwk, wt5631->wx_wate,
			wt5631->bcwk_wate / wt5631->wx_wate);
	ewse
		coeff = get_coeff(wt5631->syscwk, wt5631->wx_wate,
					timesofbcwk);
	if (coeff < 0) {
		dev_eww(component->dev, "Faiw to get coeff\n");
		wetuwn coeff;
	}

	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		iface |= WT5631_SDP_I2S_DW_20;
		bweak;
	case 24:
		iface |= WT5631_SDP_I2S_DW_24;
		bweak;
	case 8:
		iface |= WT5631_SDP_I2S_DW_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WT5631_SDP_CTWW,
		WT5631_SDP_I2S_DW_MASK, iface);
	snd_soc_component_wwite(component, WT5631_STEWEO_AD_DA_CWK_CTWW,
					coeff_div[coeff].weg_vaw);

	wetuwn 0;
}

static int wt5631_hifi_codec_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
						unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);
	unsigned int iface = 0;

	dev_dbg(component->dev, "entew %s\n", __func__);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		wt5631->mastew = 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		iface |= WT5631_SDP_MODE_SEW_SWAVE;
		wt5631->mastew = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= WT5631_SDP_I2S_DF_WEFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= WT5631_SDP_I2S_DF_PCM_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface  |= WT5631_SDP_I2S_DF_PCM_B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= WT5631_SDP_I2S_BCWK_POW_CTWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WT5631_SDP_CTWW, iface);

	wetuwn 0;
}

static int wt5631_hifi_codec_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "entew %s, sycwk=%d\n", __func__, fweq);

	if ((fweq >= (256 * 8000)) && (fweq <= (512 * 96000))) {
		wt5631->syscwk = fweq;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int wt5631_codec_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);
	int i, wet = -EINVAW;

	dev_dbg(component->dev, "entew %s\n", __func__);

	if (!fweq_in || !fweq_out) {
		dev_dbg(component->dev, "PWW disabwed\n");

		snd_soc_component_update_bits(component, WT5631_GWOBAW_CWK_CTWW,
			WT5631_SYSCWK_SOUW_SEW_MASK,
			WT5631_SYSCWK_SOUW_SEW_MCWK);

		wetuwn 0;
	}

	if (wt5631->mastew) {
		fow (i = 0; i < AWWAY_SIZE(codec_mastew_pww_div); i++)
			if (fweq_in == codec_mastew_pww_div[i].pww_in &&
			fweq_out == codec_mastew_pww_div[i].pww_out) {
				dev_info(component->dev,
					"change PWW in mastew mode\n");
				snd_soc_component_wwite(component, WT5631_PWW_CTWW,
					codec_mastew_pww_div[i].weg_vaw);
				scheduwe_timeout_unintewwuptibwe(
					msecs_to_jiffies(20));
				snd_soc_component_update_bits(component,
					WT5631_GWOBAW_CWK_CTWW,
					WT5631_SYSCWK_SOUW_SEW_MASK |
					WT5631_PWWCWK_SOUW_SEW_MASK,
					WT5631_SYSCWK_SOUW_SEW_PWW |
					WT5631_PWWCWK_SOUW_SEW_MCWK);
				wet = 0;
				bweak;
			}
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(codec_swave_pww_div); i++)
			if (fweq_in == codec_swave_pww_div[i].pww_in &&
			fweq_out == codec_swave_pww_div[i].pww_out) {
				dev_info(component->dev,
					"change PWW in swave mode\n");
				snd_soc_component_wwite(component, WT5631_PWW_CTWW,
					codec_swave_pww_div[i].weg_vaw);
				scheduwe_timeout_unintewwuptibwe(
					msecs_to_jiffies(20));
				snd_soc_component_update_bits(component,
					WT5631_GWOBAW_CWK_CTWW,
					WT5631_SYSCWK_SOUW_SEW_MASK |
					WT5631_PWWCWK_SOUW_SEW_MASK,
					WT5631_SYSCWK_SOUW_SEW_PWW |
					WT5631_PWWCWK_SOUW_SEW_BCWK);
				wet = 0;
				bweak;
			}
	}

	wetuwn wet;
}

static int wt5631_set_bias_wevew(stwuct snd_soc_component *component,
			enum snd_soc_bias_wevew wevew)
{
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD2,
			WT5631_PWW_MICBIAS1_VOW | WT5631_PWW_MICBIAS2_VOW,
			WT5631_PWW_MICBIAS1_VOW | WT5631_PWW_MICBIAS2_VOW);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
				WT5631_PWW_VWEF | WT5631_PWW_MAIN_BIAS,
				WT5631_PWW_VWEF | WT5631_PWW_MAIN_BIAS);
			msweep(80);
			snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
				WT5631_PWW_FAST_VWEF_CTWW,
				WT5631_PWW_FAST_VWEF_CTWW);
			wegcache_cache_onwy(wt5631->wegmap, fawse);
			wegcache_sync(wt5631->wegmap);
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WT5631_PWW_MANAG_ADD1, 0x0000);
		snd_soc_component_wwite(component, WT5631_PWW_MANAG_ADD2, 0x0000);
		snd_soc_component_wwite(component, WT5631_PWW_MANAG_ADD3, 0x0000);
		snd_soc_component_wwite(component, WT5631_PWW_MANAG_ADD4, 0x0000);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wt5631_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt5631_pwiv *wt5631 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw;

	vaw = wt5631_wead_index(component, WT5631_ADDA_MIXEW_INTW_WEG3);
	if (vaw & 0x0002)
		wt5631->codec_vewsion = 1;
	ewse
		wt5631->codec_vewsion = 0;

	wt5631_weset(component);
	snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
		WT5631_PWW_VWEF | WT5631_PWW_MAIN_BIAS,
		WT5631_PWW_VWEF | WT5631_PWW_MAIN_BIAS);
	msweep(80);
	snd_soc_component_update_bits(component, WT5631_PWW_MANAG_ADD3,
		WT5631_PWW_FAST_VWEF_CTWW, WT5631_PWW_FAST_VWEF_CTWW);
	/* enabwe HP zewo cwoss */
	snd_soc_component_wwite(component, WT5631_INT_ST_IWQ_CTWW_2, 0x0f18);
	/* powew off CwassD auto Wecovewy */
	if (wt5631->codec_vewsion)
		snd_soc_component_update_bits(component, WT5631_INT_ST_IWQ_CTWW_2,
					0x2000, 0x2000);
	ewse
		snd_soc_component_update_bits(component, WT5631_INT_ST_IWQ_CTWW_2,
					0x2000, 0);
	/* DMIC */
	if (wt5631->dmic_used_fwag) {
		snd_soc_component_update_bits(component, WT5631_GPIO_CTWW,
			WT5631_GPIO_PIN_FUN_SEW_MASK |
			WT5631_GPIO_DMIC_FUN_SEW_MASK,
			WT5631_GPIO_PIN_FUN_SEW_GPIO_DIMC |
			WT5631_GPIO_DMIC_FUN_SEW_DIMC);
		snd_soc_component_update_bits(component, WT5631_DIG_MIC_CTWW,
			WT5631_DMIC_W_CH_WATCH_MASK |
			WT5631_DMIC_W_CH_WATCH_MASK,
			WT5631_DMIC_W_CH_WATCH_FAWWING |
			WT5631_DMIC_W_CH_WATCH_WISING);
	}

	snd_soc_component_init_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	wetuwn 0;
}

#define WT5631_STEWEO_WATES SNDWV_PCM_WATE_8000_96000
#define WT5631_FOWMAT	(SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | \
			SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt5631_ops = {
	.hw_pawams = wt5631_hifi_pcm_pawams,
	.set_fmt = wt5631_hifi_codec_set_dai_fmt,
	.set_syscwk = wt5631_hifi_codec_set_dai_syscwk,
	.set_pww = wt5631_codec_set_dai_pww,
};

static stwuct snd_soc_dai_dwivew wt5631_dai[] = {
	{
		.name = "wt5631-hifi",
		.id = 1,
		.pwayback = {
			.stweam_name = "HIFI Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5631_STEWEO_WATES,
			.fowmats = WT5631_FOWMAT,
		},
		.captuwe = {
			.stweam_name = "HIFI Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5631_STEWEO_WATES,
			.fowmats = WT5631_FOWMAT,
		},
		.ops = &wt5631_ops,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt5631 = {
	.pwobe			= wt5631_pwobe,
	.set_bias_wevew		= wt5631_set_bias_wevew,
	.contwows		= wt5631_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wt5631_snd_contwows),
	.dapm_widgets		= wt5631_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt5631_dapm_widgets),
	.dapm_woutes		= wt5631_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt5631_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct i2c_device_id wt5631_i2c_id[] = {
	{ "wt5631", 0 },
	{ "awc5631", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt5631_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id wt5631_i2c_dt_ids[] = {
	{ .compatibwe = "weawtek,wt5631"},
	{ .compatibwe = "weawtek,awc5631"},
	{ }
};
MODUWE_DEVICE_TABWE(of, wt5631_i2c_dt_ids);
#endif

static const stwuct wegmap_config wt5631_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,

	.weadabwe_weg = wt5631_weadabwe_wegistew,
	.vowatiwe_weg = wt5631_vowatiwe_wegistew,
	.max_wegistew = WT5631_VENDOW_ID2,
	.weg_defauwts = wt5631_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt5631_weg),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int wt5631_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt5631_pwiv *wt5631;
	int wet;

	wt5631 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wt5631_pwiv),
			      GFP_KEWNEW);
	if (NUWW == wt5631)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wt5631);

	wt5631->wegmap = devm_wegmap_init_i2c(i2c, &wt5631_wegmap_config);
	if (IS_EWW(wt5631->wegmap))
		wetuwn PTW_EWW(wt5631->wegmap);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wt5631,
			wt5631_dai, AWWAY_SIZE(wt5631_dai));
	wetuwn wet;
}

static void wt5631_i2c_wemove(stwuct i2c_cwient *cwient)
{}

static stwuct i2c_dwivew wt5631_i2c_dwivew = {
	.dwivew = {
		.name = "wt5631",
		.of_match_tabwe = of_match_ptw(wt5631_i2c_dt_ids),
	},
	.pwobe    = wt5631_i2c_pwobe,
	.wemove   = wt5631_i2c_wemove,
	.id_tabwe = wt5631_i2c_id,
};

moduwe_i2c_dwivew(wt5631_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT5631 dwivew");
MODUWE_AUTHOW("fwove <fwove@weawtek.com>");
MODUWE_WICENSE("GPW");
