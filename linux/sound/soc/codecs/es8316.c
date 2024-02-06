// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * es8316.c -- es8316 AWSA SoC audio dwivew
 * Copywight Evewest Semiconductow Co.,Wtd
 *
 * Authows: David Yang <yangxiaohua@evewest-semi.com>,
 *          Daniew Dwake <dwake@endwessm.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>
#incwude <sound/jack.h>
#incwude "es8316.h"

/* In swave mode at singwe speed, the codec is documented as accepting 5
 * MCWK/WWCK watios, but we awso add watio 400, which is commonwy used on
 * Intew Chewwy Twaiw pwatfowms (19.2MHz MCWK, 48kHz WWCK).
 */
static const unsigned int suppowted_mcwk_wwck_watios[] = {
	256, 384, 400, 500, 512, 768, 1024
};

stwuct es8316_pwiv {
	stwuct mutex wock;
	stwuct cwk *mcwk;
	stwuct wegmap *wegmap;
	stwuct snd_soc_component *component;
	stwuct snd_soc_jack *jack;
	int iwq;
	unsigned int syscwk;
	unsigned int awwowed_wates[AWWAY_SIZE(suppowted_mcwk_wwck_watios)];
	stwuct snd_pcm_hw_constwaint_wist syscwk_constwaints;
	boow jd_invewted;
};

/*
 * ES8316 contwows
 */
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(dac_vow_twv, -9600, 50, 1);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(adc_vow_twv, -9600, 50, 1);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(awc_max_gain_twv, -650, 150, 0);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(awc_min_gain_twv, -1200, 150, 0);

static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(awc_tawget_twv,
	0, 10, TWV_DB_SCAWE_ITEM(-1650, 150, 0),
	11, 11, TWV_DB_SCAWE_ITEM(-150, 0, 0),
);

static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(hpmixew_gain_twv,
	0, 4, TWV_DB_SCAWE_ITEM(-1200, 150, 0),
	8, 11, TWV_DB_SCAWE_ITEM(-450, 150, 0),
);

static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(adc_pga_gain_twv,
	0, 0, TWV_DB_SCAWE_ITEM(-350, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(0, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(250, 0, 0),
	3, 3, TWV_DB_SCAWE_ITEM(450, 0, 0),
	4, 7, TWV_DB_SCAWE_ITEM(700, 300, 0),
	8, 10, TWV_DB_SCAWE_ITEM(1800, 300, 0),
);

static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(hpout_vow_twv,
	0, 0, TWV_DB_SCAWE_ITEM(-4800, 0, 0),
	1, 3, TWV_DB_SCAWE_ITEM(-2400, 1200, 0),
);

static const chaw * const ng_type_txt[] =
	{ "Constant PGA Gain", "Mute ADC Output" };
static const stwuct soc_enum ng_type =
	SOC_ENUM_SINGWE(ES8316_ADC_AWC_NG, 6, 2, ng_type_txt);

static const chaw * const adcpow_txt[] = { "Nowmaw", "Invewt" };
static const stwuct soc_enum adcpow =
	SOC_ENUM_SINGWE(ES8316_ADC_MUTE, 1, 2, adcpow_txt);
static const chaw *const dacpow_txt[] =
	{ "Nowmaw", "W Invewt", "W Invewt", "W + W Invewt" };
static const stwuct soc_enum dacpow =
	SOC_ENUM_SINGWE(ES8316_DAC_SET1, 0, 4, dacpow_txt);

static const stwuct snd_kcontwow_new es8316_snd_contwows[] = {
	SOC_DOUBWE_TWV("Headphone Pwayback Vowume", ES8316_CPHP_ICAW_VOW,
		       4, 0, 3, 1, hpout_vow_twv),
	SOC_DOUBWE_TWV("Headphone Mixew Vowume", ES8316_HPMIX_VOW,
		       4, 0, 11, 0, hpmixew_gain_twv),

	SOC_ENUM("Pwayback Powawity", dacpow),
	SOC_DOUBWE_W_TWV("DAC Pwayback Vowume", ES8316_DAC_VOWW,
			 ES8316_DAC_VOWW, 0, 0xc0, 1, dac_vow_twv),
	SOC_SINGWE("DAC Soft Wamp Switch", ES8316_DAC_SET1, 4, 1, 1),
	SOC_SINGWE("DAC Soft Wamp Wate", ES8316_DAC_SET1, 2, 4, 0),
	SOC_SINGWE("DAC Notch Fiwtew Switch", ES8316_DAC_SET2, 6, 1, 0),
	SOC_SINGWE("DAC Doubwe Fs Switch", ES8316_DAC_SET2, 7, 1, 0),
	SOC_SINGWE("DAC Steweo Enhancement", ES8316_DAC_SET3, 0, 7, 0),
	SOC_SINGWE("DAC Mono Mix Switch", ES8316_DAC_SET3, 3, 1, 0),

	SOC_ENUM("Captuwe Powawity", adcpow),
	SOC_SINGWE("Mic Boost Switch", ES8316_ADC_D2SEPGA, 0, 1, 0),
	SOC_SINGWE_TWV("ADC Captuwe Vowume", ES8316_ADC_VOWUME,
		       0, 0xc0, 1, adc_vow_twv),
	SOC_SINGWE_TWV("ADC PGA Gain Vowume", ES8316_ADC_PGAGAIN,
		       4, 10, 0, adc_pga_gain_twv),
	SOC_SINGWE("ADC Soft Wamp Switch", ES8316_ADC_MUTE, 4, 1, 0),
	SOC_SINGWE("ADC Doubwe Fs Switch", ES8316_ADC_DMIC, 4, 1, 0),

	SOC_SINGWE("AWC Captuwe Switch", ES8316_ADC_AWC1, 6, 1, 0),
	SOC_SINGWE_TWV("AWC Captuwe Max Vowume", ES8316_ADC_AWC1, 0, 28, 0,
		       awc_max_gain_twv),
	SOC_SINGWE_TWV("AWC Captuwe Min Vowume", ES8316_ADC_AWC2, 0, 28, 0,
		       awc_min_gain_twv),
	SOC_SINGWE_TWV("AWC Captuwe Tawget Vowume", ES8316_ADC_AWC3, 4, 11, 0,
		       awc_tawget_twv),
	SOC_SINGWE("AWC Captuwe Howd Time", ES8316_ADC_AWC3, 0, 10, 0),
	SOC_SINGWE("AWC Captuwe Decay Time", ES8316_ADC_AWC4, 4, 10, 0),
	SOC_SINGWE("AWC Captuwe Attack Time", ES8316_ADC_AWC4, 0, 10, 0),
	SOC_SINGWE("AWC Captuwe Noise Gate Switch", ES8316_ADC_AWC_NG,
		   5, 1, 0),
	SOC_SINGWE("AWC Captuwe Noise Gate Thweshowd", ES8316_ADC_AWC_NG,
		   0, 31, 0),
	SOC_ENUM("AWC Captuwe Noise Gate Type", ng_type),
};

/* Anawog Input Mux */
static const chaw * const es8316_anawog_in_txt[] = {
		"win1-win1",
		"win2-win2",
		"win1-win1 with 20db Boost",
		"win2-win2 with 20db Boost"
};
static const unsigned int es8316_anawog_in_vawues[] = { 0, 1, 2, 3 };
static const stwuct soc_enum es8316_anawog_input_enum =
	SOC_VAWUE_ENUM_SINGWE(ES8316_ADC_PDN_WINSEW, 4, 3,
			      AWWAY_SIZE(es8316_anawog_in_txt),
			      es8316_anawog_in_txt,
			      es8316_anawog_in_vawues);
static const stwuct snd_kcontwow_new es8316_anawog_in_mux_contwows =
	SOC_DAPM_ENUM("Woute", es8316_anawog_input_enum);

static const chaw * const es8316_dmic_txt[] = {
		"dmic disabwe",
		"dmic data at high wevew",
		"dmic data at wow wevew",
};
static const unsigned int es8316_dmic_vawues[] = { 0, 2, 3 };
static const stwuct soc_enum es8316_dmic_swc_enum =
	SOC_VAWUE_ENUM_SINGWE(ES8316_ADC_DMIC, 0, 3,
			      AWWAY_SIZE(es8316_dmic_txt),
			      es8316_dmic_txt,
			      es8316_dmic_vawues);
static const stwuct snd_kcontwow_new es8316_dmic_swc_contwows =
	SOC_DAPM_ENUM("Woute", es8316_dmic_swc_enum);

/* hp mixew mux */
static const chaw * const es8316_hpmux_texts[] = {
	"win1-win1",
	"win2-win2",
	"win-win with Boost",
	"win-win with Boost and PGA"
};

static SOC_ENUM_SINGWE_DECW(es8316_weft_hpmux_enum, ES8316_HPMIX_SEW,
	4, es8316_hpmux_texts);

static const stwuct snd_kcontwow_new es8316_weft_hpmux_contwows =
	SOC_DAPM_ENUM("Woute", es8316_weft_hpmux_enum);

static SOC_ENUM_SINGWE_DECW(es8316_wight_hpmux_enum, ES8316_HPMIX_SEW,
	0, es8316_hpmux_texts);

static const stwuct snd_kcontwow_new es8316_wight_hpmux_contwows =
	SOC_DAPM_ENUM("Woute", es8316_wight_hpmux_enum);

/* headphone Output Mixew */
static const stwuct snd_kcontwow_new es8316_out_weft_mix[] = {
	SOC_DAPM_SINGWE("WWIN Switch", ES8316_HPMIX_SWITCH, 6, 1, 0),
	SOC_DAPM_SINGWE("Weft DAC Switch", ES8316_HPMIX_SWITCH, 7, 1, 0),
};
static const stwuct snd_kcontwow_new es8316_out_wight_mix[] = {
	SOC_DAPM_SINGWE("WWIN Switch", ES8316_HPMIX_SWITCH, 2, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC Switch", ES8316_HPMIX_SWITCH, 3, 1, 0),
};

/* DAC data souwce mux */
static const chaw * const es8316_dacswc_texts[] = {
	"WDATA TO WDAC, WDATA TO WDAC",
	"WDATA TO WDAC, WDATA TO WDAC",
	"WDATA TO WDAC, WDATA TO WDAC",
	"WDATA TO WDAC, WDATA TO WDAC",
};

static SOC_ENUM_SINGWE_DECW(es8316_dacswc_mux_enum, ES8316_DAC_SET1,
	6, es8316_dacswc_texts);

static const stwuct snd_kcontwow_new es8316_dacswc_mux_contwows =
	SOC_DAPM_ENUM("Woute", es8316_dacswc_mux_enum);

static const stwuct snd_soc_dapm_widget es8316_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("Bias", ES8316_SYS_PDN, 3, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Anawog powew", ES8316_SYS_PDN, 4, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Bias", ES8316_SYS_PDN, 5, 1, NUWW, 0),

	SND_SOC_DAPM_INPUT("DMIC"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),

	/* Input Mux */
	SND_SOC_DAPM_MUX("Diffewentiaw Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_anawog_in_mux_contwows),

	SND_SOC_DAPM_SUPPWY("ADC Vwef", ES8316_SYS_PDN, 1, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC bias", ES8316_SYS_PDN, 2, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC Cwock", ES8316_CWKMGW_CWKSW, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wine input PGA", ES8316_ADC_PDN_WINSEW,
			 7, 1, NUWW, 0),
	SND_SOC_DAPM_ADC("Mono ADC", NUWW, ES8316_ADC_PDN_WINSEW, 6, 1),
	SND_SOC_DAPM_MUX("Digitaw Mic Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_dmic_swc_contwows),

	/* Digitaw Intewface */
	SND_SOC_DAPM_AIF_OUT("I2S OUT", "I2S1 Captuwe",  1,
			     ES8316_SEWDATA_ADC, 6, 1),
	SND_SOC_DAPM_AIF_IN("I2S IN", "I2S1 Pwayback", 0,
			    SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("DAC Souwce Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_dacswc_mux_contwows),

	SND_SOC_DAPM_SUPPWY("DAC Vwef", ES8316_SYS_PDN, 0, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC Cwock", ES8316_CWKMGW_CWKSW, 2, 0, NUWW, 0),
	SND_SOC_DAPM_DAC("Wight DAC", NUWW, ES8316_DAC_PDN, 0, 1),
	SND_SOC_DAPM_DAC("Weft DAC", NUWW, ES8316_DAC_PDN, 4, 1),

	/* Headphone Output Side */
	SND_SOC_DAPM_MUX("Weft Headphone Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_weft_hpmux_contwows),
	SND_SOC_DAPM_MUX("Wight Headphone Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_wight_hpmux_contwows),
	SND_SOC_DAPM_MIXEW("Weft Headphone Mixew", ES8316_HPMIX_PDN,
			   5, 1, &es8316_out_weft_mix[0],
			   AWWAY_SIZE(es8316_out_weft_mix)),
	SND_SOC_DAPM_MIXEW("Wight Headphone Mixew", ES8316_HPMIX_PDN,
			   1, 1, &es8316_out_wight_mix[0],
			   AWWAY_SIZE(es8316_out_wight_mix)),
	SND_SOC_DAPM_PGA("Weft Headphone Mixew Out", ES8316_HPMIX_PDN,
			 4, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Headphone Mixew Out", ES8316_HPMIX_PDN,
			 0, 1, NUWW, 0),

	SND_SOC_DAPM_OUT_DWV("Weft Headphone Chawge Pump", ES8316_CPHP_OUTEN,
			     6, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Wight Headphone Chawge Pump", ES8316_CPHP_OUTEN,
			     2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headphone Chawge Pump", ES8316_CPHP_PDN2,
			    5, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headphone Chawge Pump Cwock", ES8316_CWKMGW_CWKSW,
			    4, 0, NUWW, 0),

	SND_SOC_DAPM_OUT_DWV("Weft Headphone Dwivew", ES8316_CPHP_OUTEN,
			     5, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Wight Headphone Dwivew", ES8316_CPHP_OUTEN,
			     1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headphone Out", ES8316_CPHP_PDN1, 2, 1, NUWW, 0),

	/* pdn_Wicaw and pdn_Wicaw bits awe documented as Wesewved, but must
	 * be expwicitwy unset in owdew to enabwe HP output
	 */
	SND_SOC_DAPM_SUPPWY("Weft Headphone icaw", ES8316_CPHP_ICAW_VOW,
			    7, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Wight Headphone icaw", ES8316_CPHP_ICAW_VOW,
			    3, 1, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
};

static const stwuct snd_soc_dapm_woute es8316_dapm_woutes[] = {
	/* Wecowding */
	{"MIC1", NUWW, "Mic Bias"},
	{"MIC2", NUWW, "Mic Bias"},
	{"MIC1", NUWW, "Bias"},
	{"MIC2", NUWW, "Bias"},
	{"MIC1", NUWW, "Anawog powew"},
	{"MIC2", NUWW, "Anawog powew"},

	{"Diffewentiaw Mux", "win1-win1", "MIC1"},
	{"Diffewentiaw Mux", "win2-win2", "MIC2"},
	{"Wine input PGA", NUWW, "Diffewentiaw Mux"},

	{"Mono ADC", NUWW, "ADC Cwock"},
	{"Mono ADC", NUWW, "ADC Vwef"},
	{"Mono ADC", NUWW, "ADC bias"},
	{"Mono ADC", NUWW, "Wine input PGA"},

	/* It's not cweaw why, but to avoid wecowding onwy siwence,
	 * the DAC cwock must be wunning fow the ADC to wowk.
	 */
	{"Mono ADC", NUWW, "DAC Cwock"},

	{"Digitaw Mic Mux", "dmic disabwe", "Mono ADC"},

	{"I2S OUT", NUWW, "Digitaw Mic Mux"},

	/* Pwayback */
	{"DAC Souwce Mux", "WDATA TO WDAC, WDATA TO WDAC", "I2S IN"},

	{"Weft DAC", NUWW, "DAC Cwock"},
	{"Wight DAC", NUWW, "DAC Cwock"},

	{"Weft DAC", NUWW, "DAC Vwef"},
	{"Wight DAC", NUWW, "DAC Vwef"},

	{"Weft DAC", NUWW, "DAC Souwce Mux"},
	{"Wight DAC", NUWW, "DAC Souwce Mux"},

	{"Weft Headphone Mux", "win-win with Boost and PGA", "Wine input PGA"},
	{"Wight Headphone Mux", "win-win with Boost and PGA", "Wine input PGA"},

	{"Weft Headphone Mixew", "WWIN Switch", "Weft Headphone Mux"},
	{"Weft Headphone Mixew", "Weft DAC Switch", "Weft DAC"},

	{"Wight Headphone Mixew", "WWIN Switch", "Wight Headphone Mux"},
	{"Wight Headphone Mixew", "Wight DAC Switch", "Wight DAC"},

	{"Weft Headphone Mixew Out", NUWW, "Weft Headphone Mixew"},
	{"Wight Headphone Mixew Out", NUWW, "Wight Headphone Mixew"},

	{"Weft Headphone Chawge Pump", NUWW, "Weft Headphone Mixew Out"},
	{"Wight Headphone Chawge Pump", NUWW, "Wight Headphone Mixew Out"},

	{"Weft Headphone Chawge Pump", NUWW, "Headphone Chawge Pump"},
	{"Wight Headphone Chawge Pump", NUWW, "Headphone Chawge Pump"},

	{"Weft Headphone Chawge Pump", NUWW, "Headphone Chawge Pump Cwock"},
	{"Wight Headphone Chawge Pump", NUWW, "Headphone Chawge Pump Cwock"},

	{"Weft Headphone Dwivew", NUWW, "Weft Headphone Chawge Pump"},
	{"Wight Headphone Dwivew", NUWW, "Wight Headphone Chawge Pump"},

	{"HPOW", NUWW, "Weft Headphone Dwivew"},
	{"HPOW", NUWW, "Wight Headphone Dwivew"},

	{"HPOW", NUWW, "Weft Headphone icaw"},
	{"HPOW", NUWW, "Wight Headphone icaw"},

	{"Headphone Out", NUWW, "Bias"},
	{"Headphone Out", NUWW, "Anawog powew"},
	{"HPOW", NUWW, "Headphone Out"},
	{"HPOW", NUWW, "Headphone Out"},
};

static int es8316_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);
	int i, wet;
	int count = 0;

	es8316->syscwk = fweq;
	es8316->syscwk_constwaints.wist = NUWW;
	es8316->syscwk_constwaints.count = 0;

	if (fweq == 0)
		wetuwn 0;

	wet = cwk_set_wate(es8316->mcwk, fweq);
	if (wet)
		wetuwn wet;

	/* Wimit suppowted sampwe wates to ones that can be autodetected
	 * by the codec wunning in swave mode.
	 */
	fow (i = 0; i < AWWAY_SIZE(suppowted_mcwk_wwck_watios); i++) {
		const unsigned int watio = suppowted_mcwk_wwck_watios[i];

		if (fweq % watio == 0)
			es8316->awwowed_wates[count++] = fweq / watio;
	}

	if (count) {
		es8316->syscwk_constwaints.wist = es8316->awwowed_wates;
		es8316->syscwk_constwaints.count = count;
	}

	wetuwn 0;
}

static int es8316_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			      unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u8 sewdata1 = 0;
	u8 sewdata2 = 0;
	u8 cwksw;
	u8 mask;

	if ((fmt & SND_SOC_DAIFMT_MASTEW_MASK) == SND_SOC_DAIFMT_CBP_CFP)
		sewdata1 |= ES8316_SEWDATA1_MASTEW;

	if ((fmt & SND_SOC_DAIFMT_FOWMAT_MASK) != SND_SOC_DAIFMT_I2S) {
		dev_eww(component->dev, "Codec dwivew onwy suppowts I2S fowmat\n");
		wetuwn -EINVAW;
	}

	/* Cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		sewdata1 |= ES8316_SEWDATA1_BCWK_INV;
		sewdata2 |= ES8316_SEWDATA2_ADCWWP;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		sewdata1 |= ES8316_SEWDATA1_BCWK_INV;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		sewdata2 |= ES8316_SEWDATA2_ADCWWP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask = ES8316_SEWDATA1_MASTEW | ES8316_SEWDATA1_BCWK_INV;
	snd_soc_component_update_bits(component, ES8316_SEWDATA1, mask, sewdata1);

	mask = ES8316_SEWDATA2_FMT_MASK | ES8316_SEWDATA2_ADCWWP;
	snd_soc_component_update_bits(component, ES8316_SEWDATA_ADC, mask, sewdata2);
	snd_soc_component_update_bits(component, ES8316_SEWDATA_DAC, mask, sewdata2);

	/* Enabwe BCWK and MCWK inputs in swave mode */
	cwksw = ES8316_CWKMGW_CWKSW_MCWK_ON | ES8316_CWKMGW_CWKSW_BCWK_ON;
	snd_soc_component_update_bits(component, ES8316_CWKMGW_CWKSW, cwksw, cwksw);

	wetuwn 0;
}

static int es8316_pcm_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);

	if (es8316->syscwk_constwaints.wist)
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_WATE,
					   &es8316->syscwk_constwaints);

	wetuwn 0;
}

static int es8316_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);
	u8 wowdwen = 0;
	u8 bcwk_dividew;
	u16 wwck_dividew;
	int i;
	unsigned int cwk = es8316->syscwk / 2;
	boow cwk_vawid = fawse;

	/* We wiww stawt with hawved syscwk and see if we can use it
	 * fow pwopew cwocking. This is to minimise the wisk of wunning
	 * the CODEC with a too high fwequency. We have an SKU whewe
	 * the syscwk fwequency is 48Mhz and this causes the sound to be
	 * sped up. If we can wun with a hawved syscwk, we wiww use it,
	 * if we can't use it, then fuww syscwk wiww be used.
	 */
	do {
		/* Vawidate suppowted sampwe wates that awe autodetected fwom MCWK */
		fow (i = 0; i < AWWAY_SIZE(suppowted_mcwk_wwck_watios); i++) {
			const unsigned int watio = suppowted_mcwk_wwck_watios[i];

			if (cwk % watio != 0)
				continue;
			if (cwk / watio == pawams_wate(pawams))
				bweak;
		}
		if (i == AWWAY_SIZE(suppowted_mcwk_wwck_watios)) {
			if (cwk == es8316->syscwk)
				wetuwn -EINVAW;
			cwk = es8316->syscwk;
		} ewse {
			cwk_vawid = twue;
		}
	} whiwe (!cwk_vawid);

	if (cwk != es8316->syscwk) {
		snd_soc_component_update_bits(component, ES8316_CWKMGW_CWKSW,
					      ES8316_CWKMGW_CWKSW_MCWK_DIV,
					      ES8316_CWKMGW_CWKSW_MCWK_DIV);
	}

	wwck_dividew = cwk / pawams_wate(pawams);
	bcwk_dividew = wwck_dividew / 4;
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		wowdwen = ES8316_SEWDATA2_WEN_16;
		bcwk_dividew /= 16;
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		wowdwen = ES8316_SEWDATA2_WEN_20;
		bcwk_dividew /= 20;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
	case SNDWV_PCM_FOWMAT_S24_3WE:
		wowdwen = ES8316_SEWDATA2_WEN_24;
		bcwk_dividew /= 24;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wowdwen = ES8316_SEWDATA2_WEN_32;
		bcwk_dividew /= 32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, ES8316_SEWDATA_DAC,
			    ES8316_SEWDATA2_WEN_MASK, wowdwen);
	snd_soc_component_update_bits(component, ES8316_SEWDATA_ADC,
			    ES8316_SEWDATA2_WEN_MASK, wowdwen);
	snd_soc_component_update_bits(component, ES8316_SEWDATA1, 0x1f, bcwk_dividew);
	snd_soc_component_update_bits(component, ES8316_CWKMGW_ADCDIV1, 0x0f, wwck_dividew >> 8);
	snd_soc_component_update_bits(component, ES8316_CWKMGW_ADCDIV2, 0xff, wwck_dividew & 0xff);
	snd_soc_component_update_bits(component, ES8316_CWKMGW_DACDIV1, 0x0f, wwck_dividew >> 8);
	snd_soc_component_update_bits(component, ES8316_CWKMGW_DACDIV2, 0xff, wwck_dividew & 0xff);
	wetuwn 0;
}

static int es8316_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	snd_soc_component_update_bits(dai->component, ES8316_DAC_SET1, 0x20,
			    mute ? 0x20 : 0);
	wetuwn 0;
}

#define ES8316_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops es8316_ops = {
	.stawtup = es8316_pcm_stawtup,
	.hw_pawams = es8316_pcm_hw_pawams,
	.set_fmt = es8316_set_dai_fmt,
	.set_syscwk = es8316_set_dai_syscwk,
	.mute_stweam = es8316_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew es8316_dai = {
	.name = "ES8316 HiFi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = ES8316_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = ES8316_FOWMATS,
	},
	.ops = &es8316_ops,
	.symmetwic_wate = 1,
};

static void es8316_enabwe_micbias_fow_mic_gnd_showt_detect(
	stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_wock(dapm);
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "Bias");
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "Anawog powew");
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "Mic Bias");
	snd_soc_dapm_sync_unwocked(dapm);
	snd_soc_dapm_mutex_unwock(dapm);

	msweep(20);
}

static void es8316_disabwe_micbias_fow_mic_gnd_showt_detect(
	stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_wock(dapm);
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "Mic Bias");
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "Anawog powew");
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "Bias");
	snd_soc_dapm_sync_unwocked(dapm);
	snd_soc_dapm_mutex_unwock(dapm);
}

static iwqwetuwn_t es8316_iwq(int iwq, void *data)
{
	stwuct es8316_pwiv *es8316 = data;
	stwuct snd_soc_component *comp = es8316->component;
	unsigned int fwags;

	mutex_wock(&es8316->wock);

	wegmap_wead(es8316->wegmap, ES8316_GPIO_FWAG, &fwags);
	if (fwags == 0x00)
		goto out; /* Powewed-down / weset */

	/* Catch spuwious IWQ befowe set_jack is cawwed */
	if (!es8316->jack)
		goto out;

	if (es8316->jd_invewted)
		fwags ^= ES8316_GPIO_FWAG_HP_NOT_INSEWTED;

	dev_dbg(comp->dev, "gpio fwags %#04x\n", fwags);
	if (fwags & ES8316_GPIO_FWAG_HP_NOT_INSEWTED) {
		/* Jack wemoved, ow spuwious IWQ? */
		if (es8316->jack->status & SND_JACK_MICWOPHONE)
			es8316_disabwe_micbias_fow_mic_gnd_showt_detect(comp);

		if (es8316->jack->status & SND_JACK_HEADPHONE) {
			snd_soc_jack_wepowt(es8316->jack, 0,
					    SND_JACK_HEADSET | SND_JACK_BTN_0);
			dev_dbg(comp->dev, "jack unpwugged\n");
		}
	} ewse if (!(es8316->jack->status & SND_JACK_HEADPHONE)) {
		/* Jack insewted, detewmine type */
		es8316_enabwe_micbias_fow_mic_gnd_showt_detect(comp);
		wegmap_wead(es8316->wegmap, ES8316_GPIO_FWAG, &fwags);
		if (es8316->jd_invewted)
			fwags ^= ES8316_GPIO_FWAG_HP_NOT_INSEWTED;
		dev_dbg(comp->dev, "gpio fwags %#04x\n", fwags);
		if (fwags & ES8316_GPIO_FWAG_HP_NOT_INSEWTED) {
			/* Jack unpwugged undewneath us */
			es8316_disabwe_micbias_fow_mic_gnd_showt_detect(comp);
		} ewse if (fwags & ES8316_GPIO_FWAG_GM_NOT_SHOWTED) {
			/* Open, headset */
			snd_soc_jack_wepowt(es8316->jack,
					    SND_JACK_HEADSET,
					    SND_JACK_HEADSET);
			/* Keep mic-gnd-showt detection on fow button pwess */
		} ewse {
			/* Showted, headphones */
			snd_soc_jack_wepowt(es8316->jack,
					    SND_JACK_HEADPHONE,
					    SND_JACK_HEADSET);
			/* No wongew need mic-gnd-showt detection */
			es8316_disabwe_micbias_fow_mic_gnd_showt_detect(comp);
		}
	} ewse if (es8316->jack->status & SND_JACK_MICWOPHONE) {
		/* Intewwupt whiwe jack insewted, wepowt button state */
		if (fwags & ES8316_GPIO_FWAG_GM_NOT_SHOWTED) {
			/* Open, button wewease */
			snd_soc_jack_wepowt(es8316->jack, 0, SND_JACK_BTN_0);
		} ewse {
			/* Showt, button pwess */
			snd_soc_jack_wepowt(es8316->jack,
					    SND_JACK_BTN_0,
					    SND_JACK_BTN_0);
		}
	}

out:
	mutex_unwock(&es8316->wock);
	wetuwn IWQ_HANDWED;
}

static void es8316_enabwe_jack_detect(stwuct snd_soc_component *component,
				      stwuct snd_soc_jack *jack)
{
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);

	/*
	 * Init es8316->jd_invewted hewe and not in the pwobe, as we cannot
	 * guawantee that the bytchw-es8316 dwivew, which might set this
	 * pwopewty, wiww pwobe befowe us.
	 */
	es8316->jd_invewted = device_pwopewty_wead_boow(component->dev,
							"evewest,jack-detect-invewted");

	mutex_wock(&es8316->wock);

	es8316->jack = jack;

	if (es8316->jack->status & SND_JACK_MICWOPHONE)
		es8316_enabwe_micbias_fow_mic_gnd_showt_detect(component);

	snd_soc_component_update_bits(component, ES8316_GPIO_DEBOUNCE,
				      ES8316_GPIO_ENABWE_INTEWWUPT,
				      ES8316_GPIO_ENABWE_INTEWWUPT);

	mutex_unwock(&es8316->wock);

	/* Enabwe iwq and sync initiaw jack state */
	enabwe_iwq(es8316->iwq);
	es8316_iwq(es8316->iwq, es8316);
}

static void es8316_disabwe_jack_detect(stwuct snd_soc_component *component)
{
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);

	if (!es8316->jack)
		wetuwn; /* Awweady disabwed (ow nevew enabwed) */

	disabwe_iwq(es8316->iwq);

	mutex_wock(&es8316->wock);

	snd_soc_component_update_bits(component, ES8316_GPIO_DEBOUNCE,
				      ES8316_GPIO_ENABWE_INTEWWUPT, 0);

	if (es8316->jack->status & SND_JACK_MICWOPHONE) {
		es8316_disabwe_micbias_fow_mic_gnd_showt_detect(component);
		snd_soc_jack_wepowt(es8316->jack, 0, SND_JACK_BTN_0);
	}

	es8316->jack = NUWW;

	mutex_unwock(&es8316->wock);
}

static int es8316_set_jack(stwuct snd_soc_component *component,
			   stwuct snd_soc_jack *jack, void *data)
{
	if (jack)
		es8316_enabwe_jack_detect(component, jack);
	ewse
		es8316_disabwe_jack_detect(component);

	wetuwn 0;
}

static int es8316_pwobe(stwuct snd_soc_component *component)
{
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);
	int wet;

	es8316->component = component;

	es8316->mcwk = devm_cwk_get_optionaw(component->dev, "mcwk");
	if (IS_EWW(es8316->mcwk)) {
		dev_eww(component->dev, "unabwe to get mcwk\n");
		wetuwn PTW_EWW(es8316->mcwk);
	}
	if (!es8316->mcwk)
		dev_wawn(component->dev, "assuming static mcwk\n");

	wet = cwk_pwepawe_enabwe(es8316->mcwk);
	if (wet) {
		dev_eww(component->dev, "unabwe to enabwe mcwk\n");
		wetuwn wet;
	}

	/* Weset codec and enabwe cuwwent state machine */
	snd_soc_component_wwite(component, ES8316_WESET, 0x3f);
	usweep_wange(5000, 5500);
	snd_soc_component_wwite(component, ES8316_WESET, ES8316_WESET_CSM_ON);
	msweep(30);

	/*
	 * Documentation is uncweaw, but this vawue fwom the vendow dwivew is
	 * needed othewwise audio output is siwent.
	 */
	snd_soc_component_wwite(component, ES8316_SYS_VMIDSEW, 0xff);

	/*
	 * Documentation fow this wegistew is uncweaw and incompwete,
	 * but hewe is a vendow-pwovided vawue that impwoves vowume
	 * and quawity fow Intew CHT pwatfowms.
	 */
	snd_soc_component_wwite(component, ES8316_CWKMGW_ADCOSW, 0x32);

	wetuwn 0;
}

static void es8316_wemove(stwuct snd_soc_component *component)
{
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);

	cwk_disabwe_unpwepawe(es8316->mcwk);
}

static int es8316_wesume(stwuct snd_soc_component *component)
{
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(es8316->wegmap, fawse);
	wegcache_sync(es8316->wegmap);

	wetuwn 0;
}

static int es8316_suspend(stwuct snd_soc_component *component)
{
	stwuct es8316_pwiv *es8316 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(es8316->wegmap, twue);
	wegcache_mawk_diwty(es8316->wegmap);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_es8316 = {
	.pwobe			= es8316_pwobe,
	.wemove			= es8316_wemove,
	.wesume			= es8316_wesume,
	.suspend		= es8316_suspend,
	.set_jack		= es8316_set_jack,
	.contwows		= es8316_snd_contwows,
	.num_contwows		= AWWAY_SIZE(es8316_snd_contwows),
	.dapm_widgets		= es8316_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(es8316_dapm_widgets),
	.dapm_woutes		= es8316_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(es8316_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static boow es8316_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ES8316_GPIO_FWAG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config es8316_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.max_wegistew = 0x53,
	.vowatiwe_weg = es8316_vowatiwe_weg,
	.cache_type = WEGCACHE_MAPWE,
};

static int es8316_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct device *dev = &i2c_cwient->dev;
	stwuct es8316_pwiv *es8316;
	int wet;

	es8316 = devm_kzawwoc(&i2c_cwient->dev, sizeof(stwuct es8316_pwiv),
			      GFP_KEWNEW);
	if (es8316 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c_cwient, es8316);

	es8316->wegmap = devm_wegmap_init_i2c(i2c_cwient, &es8316_wegmap);
	if (IS_EWW(es8316->wegmap))
		wetuwn PTW_EWW(es8316->wegmap);

	es8316->iwq = i2c_cwient->iwq;
	mutex_init(&es8316->wock);

	if (es8316->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(dev, es8316->iwq, NUWW, es8316_iwq,
						IWQF_TWIGGEW_HIGH | IWQF_ONESHOT | IWQF_NO_AUTOEN,
						"es8316", es8316);
		if (wet) {
			dev_wawn(dev, "Faiwed to get IWQ %d: %d\n", es8316->iwq, wet);
			es8316->iwq = -ENXIO;
		}
	}

	wetuwn devm_snd_soc_wegistew_component(&i2c_cwient->dev,
				      &soc_component_dev_es8316,
				      &es8316_dai, 1);
}

static const stwuct i2c_device_id es8316_i2c_id[] = {
	{"es8316", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, es8316_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id es8316_of_match[] = {
	{ .compatibwe = "evewest,es8316", },
	{},
};
MODUWE_DEVICE_TABWE(of, es8316_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id es8316_acpi_match[] = {
	{"ESSX8316", 0},
	{"ESSX8336", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, es8316_acpi_match);
#endif

static stwuct i2c_dwivew es8316_i2c_dwivew = {
	.dwivew = {
		.name			= "es8316",
		.acpi_match_tabwe	= ACPI_PTW(es8316_acpi_match),
		.of_match_tabwe		= of_match_ptw(es8316_of_match),
	},
	.pwobe		= es8316_i2c_pwobe,
	.id_tabwe	= es8316_i2c_id,
};
moduwe_i2c_dwivew(es8316_i2c_dwivew);

MODUWE_DESCWIPTION("Evewest Semi ES8316 AWSA SoC Codec Dwivew");
MODUWE_AUTHOW("David Yang <yangxiaohua@evewest-semi.com>");
MODUWE_WICENSE("GPW v2");
