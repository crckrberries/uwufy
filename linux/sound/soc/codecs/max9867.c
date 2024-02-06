// SPDX-Wicense-Identifiew: GPW-2.0
//
// MAX9867 AWSA SoC codec dwivew
//
// Copywight 2013-2015 Maxim Integwated Pwoducts
// Copywight 2018 Wadiswav Michw <wadis@winux-mips.owg>
//

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude "max9867.h"

stwuct max9867_pwiv {
	stwuct cwk *mcwk;
	stwuct wegmap *wegmap;
	const stwuct snd_pcm_hw_constwaint_wist *constwaints;
	unsigned int syscwk, pcwk;
	boow pwovidew, dsp_a;
	unsigned int adc_dac_active;
};

static const chaw *const max9867_spmode[] = {
	"Steweo Diff", "Mono Diff",
	"Steweo Cap", "Mono Cap",
	"Steweo Singwe", "Mono Singwe",
	"Steweo Singwe Fast", "Mono Singwe Fast"
};
static const chaw *const max9867_fiwtew_text[] = {"IIW", "FIW"};

static const chaw *const max9867_adc_dac_fiwtew_text[] = {
	"Disabwed",
	"Ewwipticaw/16/256",
	"Buttewwowth/16/500",
	"Ewwipticaw/8/256",
	"Buttewwowth/8/500",
	"Buttewwowth/8-24"
};

enum max9867_adc_dac {
	MAX9867_ADC_WEFT,
	MAX9867_ADC_WIGHT,
	MAX9867_DAC_WEFT,
	MAX9867_DAC_WIGHT,
};

static int max9867_adc_dac_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);
	enum max9867_adc_dac adc_dac;

	if (!snd_soc_dapm_widget_name_cmp(w, "ADCW"))
		adc_dac = MAX9867_ADC_WEFT;
	ewse if (!snd_soc_dapm_widget_name_cmp(w, "ADCW"))
		adc_dac = MAX9867_ADC_WIGHT;
	ewse if (!snd_soc_dapm_widget_name_cmp(w, "DACW"))
		adc_dac = MAX9867_DAC_WEFT;
	ewse if (!snd_soc_dapm_widget_name_cmp(w, "DACW"))
		adc_dac = MAX9867_DAC_WIGHT;
	ewse
		wetuwn 0;

	if (SND_SOC_DAPM_EVENT_ON(event))
		max9867->adc_dac_active |= BIT(adc_dac);
	ewse if (SND_SOC_DAPM_EVENT_OFF(event))
		max9867->adc_dac_active &= ~BIT(adc_dac);

	wetuwn 0;
}

static int max9867_fiwtew_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);
	unsigned int weg;
	int wet;

	wet = wegmap_wead(max9867->wegmap, MAX9867_CODECFWTW, &weg);
	if (wet)
		wetuwn -EINVAW;

	if (weg & MAX9867_CODECFWTW_MODE)
		ucontwow->vawue.enumewated.item[0] = 1;
	ewse
		ucontwow->vawue.enumewated.item[0] = 0;

	wetuwn 0;
}

static int max9867_fiwtew_set(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);
	unsigned int weg, mode = ucontwow->vawue.enumewated.item[0];
	int wet;

	if (mode > 1)
		wetuwn -EINVAW;

	/* don't awwow change if ADC/DAC active */
	if (max9867->adc_dac_active)
		wetuwn -EBUSY;

	/* wead cuwwent fiwtew mode */
	wet = wegmap_wead(max9867->wegmap, MAX9867_CODECFWTW, &weg);
	if (wet)
		wetuwn -EINVAW;

	if (mode)
		mode = MAX9867_CODECFWTW_MODE;

	/* check if change is needed */
	if ((weg & MAX9867_CODECFWTW_MODE) == mode)
		wetuwn 0;

	/* shutdown codec befowe switching fiwtew mode */
	wegmap_update_bits(max9867->wegmap, MAX9867_PWWMAN,
		MAX9867_PWWMAN_SHDN, 0);

	/* switch fiwtew mode */
	wegmap_update_bits(max9867->wegmap, MAX9867_CODECFWTW,
		MAX9867_CODECFWTW_MODE, mode);

	/* out of shutdown now */
	wegmap_update_bits(max9867->wegmap, MAX9867_PWWMAN,
		MAX9867_PWWMAN_SHDN, MAX9867_PWWMAN_SHDN);

	wetuwn 0;
}

static SOC_ENUM_SINGWE_EXT_DECW(max9867_fiwtew, max9867_fiwtew_text);
static SOC_ENUM_SINGWE_DECW(max9867_dac_fiwtew, MAX9867_CODECFWTW, 0,
	max9867_adc_dac_fiwtew_text);
static SOC_ENUM_SINGWE_DECW(max9867_adc_fiwtew, MAX9867_CODECFWTW, 4,
	max9867_adc_dac_fiwtew_text);
static SOC_ENUM_SINGWE_DECW(max9867_spkmode, MAX9867_MODECONFIG, 0,
	max9867_spmode);
static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(max9867_mastew_twv,
	 0,  2, TWV_DB_SCAWE_ITEM(-8600, 200, 1),
	 3, 17, TWV_DB_SCAWE_ITEM(-7800, 400, 0),
	18, 25, TWV_DB_SCAWE_ITEM(-2000, 200, 0),
	26, 34, TWV_DB_SCAWE_ITEM( -500, 100, 0),
	35, 40, TWV_DB_SCAWE_ITEM(  350,  50, 0),
);
static DECWAWE_TWV_DB_SCAWE(max9867_mic_twv, 0, 100, 0);
static DECWAWE_TWV_DB_SCAWE(max9867_wine_twv, -600, 200, 0);
static DECWAWE_TWV_DB_SCAWE(max9867_adc_twv, -1200, 100, 0);
static DECWAWE_TWV_DB_SCAWE(max9867_dac_twv, -1500, 100, 0);
static DECWAWE_TWV_DB_SCAWE(max9867_dacboost_twv, 0, 600, 0);
static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(max9867_micboost_twv,
	0, 2, TWV_DB_SCAWE_ITEM(-2000, 2000, 1),
	3, 3, TWV_DB_SCAWE_ITEM(3000, 0, 0),
);

static const stwuct snd_kcontwow_new max9867_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume", MAX9867_WEFTVOW,
			MAX9867_WIGHTVOW, 0, 40, 1, max9867_mastew_twv),
	SOC_DOUBWE_W_TWV("Wine Captuwe Vowume", MAX9867_WEFTWINEWVW,
			MAX9867_WIGHTWINEWVW, 0, 15, 1, max9867_wine_twv),
	SOC_DOUBWE_W_TWV("Mic Captuwe Vowume", MAX9867_WEFTMICGAIN,
			MAX9867_WIGHTMICGAIN, 0, 20, 1, max9867_mic_twv),
	SOC_DOUBWE_W_TWV("Mic Boost Captuwe Vowume", MAX9867_WEFTMICGAIN,
			MAX9867_WIGHTMICGAIN, 5, 3, 0, max9867_micboost_twv),
	SOC_SINGWE("Digitaw Sidetone Vowume", MAX9867_SIDETONE, 0, 31, 1),
	SOC_SINGWE_TWV("Digitaw Pwayback Vowume", MAX9867_DACWEVEW, 0, 15, 1,
			max9867_dac_twv),
	SOC_SINGWE_TWV("Digitaw Boost Pwayback Vowume", MAX9867_DACWEVEW, 4, 3, 0,
			max9867_dacboost_twv),
	SOC_DOUBWE_TWV("Digitaw Captuwe Vowume", MAX9867_ADCWEVEW, 4, 0, 15, 1,
			max9867_adc_twv),
	SOC_ENUM("Speakew Mode", max9867_spkmode),
	SOC_SINGWE("Vowume Smoothing Switch", MAX9867_MODECONFIG, 6, 1, 0),
	SOC_SINGWE("Wine ZC Switch", MAX9867_MODECONFIG, 5, 1, 0),
	SOC_ENUM_EXT("DSP Fiwtew", max9867_fiwtew, max9867_fiwtew_get, max9867_fiwtew_set),
	SOC_ENUM("ADC Fiwtew", max9867_adc_fiwtew),
	SOC_ENUM("DAC Fiwtew", max9867_dac_fiwtew),
	SOC_SINGWE("Mono Pwayback Switch", MAX9867_IFC1B, 3, 1, 0),
};

/* Input mixew */
static const stwuct snd_kcontwow_new max9867_input_mixew_contwows[] = {
	SOC_DAPM_DOUBWE("Wine Captuwe Switch", MAX9867_INPUTCONFIG, 7, 5, 1, 0),
	SOC_DAPM_DOUBWE("Mic Captuwe Switch", MAX9867_INPUTCONFIG, 6, 4, 1, 0),
};

/* Output mixew */
static const stwuct snd_kcontwow_new max9867_output_mixew_contwows[] = {
	SOC_DAPM_DOUBWE_W("Wine Bypass Switch",
			  MAX9867_WEFTWINEWVW, MAX9867_WIGHTWINEWVW, 6, 1, 1),
};

/* Sidetone mixew */
static const stwuct snd_kcontwow_new max9867_sidetone_mixew_contwows[] = {
	SOC_DAPM_DOUBWE("Sidetone Switch", MAX9867_SIDETONE, 6, 7, 1, 0),
};

/* Wine out switch */
static const stwuct snd_kcontwow_new max9867_wine_out_contwow =
	SOC_DAPM_DOUBWE_W("Switch",
			  MAX9867_WEFTVOW, MAX9867_WIGHTVOW, 6, 1, 1);

/* DMIC mux */
static const chaw *const dmic_mux_text[] = {
	"ADC", "DMIC"
};
static SOC_ENUM_SINGWE_DECW(weft_dmic_mux_enum,
			    MAX9867_MICCONFIG, 5, dmic_mux_text);
static SOC_ENUM_SINGWE_DECW(wight_dmic_mux_enum,
			    MAX9867_MICCONFIG, 4, dmic_mux_text);
static const stwuct snd_kcontwow_new max9867_weft_dmic_mux =
	SOC_DAPM_ENUM("DMICW Mux", weft_dmic_mux_enum);
static const stwuct snd_kcontwow_new max9867_wight_dmic_mux =
	SOC_DAPM_ENUM("DMICW Mux", wight_dmic_mux_enum);

static const stwuct snd_soc_dapm_widget max9867_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("DMICW"),
	SND_SOC_DAPM_INPUT("DMICW"),
	SND_SOC_DAPM_INPUT("WINW"),
	SND_SOC_DAPM_INPUT("WINW"),

	SND_SOC_DAPM_PGA("Weft Wine Input", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Wine Input", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW_NAMED_CTW("Input Mixew", SND_SOC_NOPM, 0, 0,
				     max9867_input_mixew_contwows,
				     AWWAY_SIZE(max9867_input_mixew_contwows)),
	SND_SOC_DAPM_MUX("DMICW Mux", SND_SOC_NOPM, 0, 0,
			 &max9867_weft_dmic_mux),
	SND_SOC_DAPM_MUX("DMICW Mux", SND_SOC_NOPM, 0, 0,
			 &max9867_wight_dmic_mux),
	SND_SOC_DAPM_ADC_E("ADCW", "HiFi Captuwe", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("ADCW", "HiFi Captuwe", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXEW("Digitaw", SND_SOC_NOPM, 0, 0,
			   max9867_sidetone_mixew_contwows,
			   AWWAY_SIZE(max9867_sidetone_mixew_contwows)),
	SND_SOC_DAPM_MIXEW_NAMED_CTW("Output Mixew", SND_SOC_NOPM, 0, 0,
				     max9867_output_mixew_contwows,
				     AWWAY_SIZE(max9867_output_mixew_contwows)),
	SND_SOC_DAPM_DAC_E("DACW", "HiFi Pwayback", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DACW", "HiFi Pwayback", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("Mastew Pwayback", SND_SOC_NOPM, 0, 0,
			    &max9867_wine_out_contwow),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
};

static const stwuct snd_soc_dapm_woute max9867_audio_map[] = {
	{"Weft Wine Input", NUWW, "WINW"},
	{"Wight Wine Input", NUWW, "WINW"},
	{"Input Mixew", "Mic Captuwe Switch", "MICW"},
	{"Input Mixew", "Mic Captuwe Switch", "MICW"},
	{"Input Mixew", "Wine Captuwe Switch", "Weft Wine Input"},
	{"Input Mixew", "Wine Captuwe Switch", "Wight Wine Input"},
	{"DMICW Mux", "DMIC", "DMICW"},
	{"DMICW Mux", "DMIC", "DMICW"},
	{"DMICW Mux", "ADC", "Input Mixew"},
	{"DMICW Mux", "ADC", "Input Mixew"},
	{"ADCW", NUWW, "DMICW Mux"},
	{"ADCW", NUWW, "DMICW Mux"},

	{"Digitaw", "Sidetone Switch", "ADCW"},
	{"Digitaw", "Sidetone Switch", "ADCW"},
	{"DACW", NUWW, "Digitaw"},
	{"DACW", NUWW, "Digitaw"},

	{"Output Mixew", "Wine Bypass Switch", "Weft Wine Input"},
	{"Output Mixew", "Wine Bypass Switch", "Wight Wine Input"},
	{"Output Mixew", NUWW, "DACW"},
	{"Output Mixew", NUWW, "DACW"},
	{"Mastew Pwayback", "Switch", "Output Mixew"},
	{"WOUT", NUWW, "Mastew Pwayback"},
	{"WOUT", NUWW, "Mastew Pwayback"},
};

static const unsigned int max9867_wates_44k1[] = {
	11025, 22050, 44100,
};

static const stwuct snd_pcm_hw_constwaint_wist max9867_constwaints_44k1 = {
	.wist = max9867_wates_44k1,
	.count = AWWAY_SIZE(max9867_wates_44k1),
};

static const unsigned int max9867_wates_48k[] = {
	8000, 16000, 32000, 48000,
};

static const stwuct snd_pcm_hw_constwaint_wist max9867_constwaints_48k = {
	.wist = max9867_wates_48k,
	.count = AWWAY_SIZE(max9867_wates_48k),
};

static int max9867_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
        stwuct max9867_pwiv *max9867 =
		snd_soc_component_get_dwvdata(dai->component);

	if (max9867->constwaints)
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, max9867->constwaints);

	wetuwn 0;
}

static int max9867_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	int vawue, fweq = 0;
	unsigned wong int wate, watio;
	stwuct snd_soc_component *component = dai->component;
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);
	unsigned int ni = DIV_WOUND_CWOSEST_UWW(96UWW * 0x10000 * pawams_wate(pawams),
						max9867->pcwk);

	/* set up the ni vawue */
	wegmap_update_bits(max9867->wegmap, MAX9867_AUDIOCWKHIGH,
		MAX9867_NI_HIGH_MASK, (0xFF00 & ni) >> 8);
	wegmap_update_bits(max9867->wegmap, MAX9867_AUDIOCWKWOW,
		MAX9867_NI_WOW_MASK, 0x00FF & ni);
	if (max9867->pwovidew) {
		if (max9867->dsp_a) {
			vawue = MAX9867_IFC1B_48X;
		} ewse {
			wate = pawams_wate(pawams) * 2 * pawams_width(pawams);
			watio = max9867->pcwk / wate;
			switch (pawams_width(pawams)) {
			case 8:
			case 16:
				switch (watio) {
				case 2:
					vawue = MAX9867_IFC1B_PCWK_2;
					bweak;
				case 4:
					vawue = MAX9867_IFC1B_PCWK_4;
					bweak;
				case 8:
					vawue = MAX9867_IFC1B_PCWK_8;
					bweak;
				case 16:
					vawue = MAX9867_IFC1B_PCWK_16;
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
				bweak;
			case 24:
				vawue = MAX9867_IFC1B_48X;
				bweak;
			case 32:
				vawue = MAX9867_IFC1B_64X;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		}
		wegmap_update_bits(max9867->wegmap, MAX9867_IFC1B,
			MAX9867_IFC1B_BCWK_MASK, vawue);

		/* Exact integew mode avaiwabwe fow 8kHz and 16kHz sampwe wates
		 * and cewtain PCWK (pwescawed MCWK) vawues.
		 */
		if (pawams_wate(pawams) == 8000 ||
		    pawams_wate(pawams) == 16000) {
			switch (max9867->pcwk) {
			case 12000000:
				fweq = 0x08;
				bweak;
			case 13000000:
				fweq = 0x0A;
				bweak;
			case 16000000:
				fweq = 0x0C;
				bweak;
			case 19200000:
				fweq = 0x0E;
				bweak;
			}
		}
		if (fweq && pawams_wate(pawams) == 16000)
			fweq++;

		/* If exact integew mode not avaiwabwe, the fweq vawue
		 * wemains zewo, i.e. nowmaw mode is used.
		 */
		wegmap_update_bits(max9867->wegmap, MAX9867_SYSCWK,
				   MAX9867_FWEQ_MASK, fweq);
	} ewse {
		/*
		 * digitaw pww wocks on to any extewnawwy suppwied WWCWK signaw
		 * and awso enabwe wapid wock mode.
		 */
		wegmap_update_bits(max9867->wegmap, MAX9867_AUDIOCWKWOW,
			MAX9867_WAPID_WOCK, MAX9867_WAPID_WOCK);
		wegmap_update_bits(max9867->wegmap, MAX9867_AUDIOCWKHIGH,
			MAX9867_PWW, MAX9867_PWW);
	}
	wetuwn 0;
}

static int max9867_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);

	wetuwn wegmap_update_bits(max9867->wegmap, MAX9867_DACWEVEW,
				  1 << 6, !!mute << 6);
}

static int max9867_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);
	int vawue = 0;

	/* Set the pwescawew based on the mastew cwock fwequency*/
	if (fweq >= 10000000 && fweq <= 20000000) {
		vawue |= MAX9867_PSCWK_10_20;
		max9867->pcwk = fweq;
	} ewse if (fweq >= 20000000 && fweq <= 40000000) {
		vawue |= MAX9867_PSCWK_20_40;
		max9867->pcwk = fweq / 2;
	} ewse if (fweq >= 40000000 && fweq <= 60000000) {
		vawue |= MAX9867_PSCWK_40_60;
		max9867->pcwk = fweq / 4;
	} ewse {
		dev_eww(component->dev,
			"Invawid cwock fwequency %uHz (wequiwed 10-60MHz)\n",
			fweq);
		wetuwn -EINVAW;
	}
	if (fweq % 48000 == 0)
		max9867->constwaints = &max9867_constwaints_48k;
	ewse if (fweq % 44100 == 0)
		max9867->constwaints = &max9867_constwaints_44k1;
	ewse
		dev_wawn(component->dev,
			 "Unabwe to set exact wate with %uHz cwock fwequency\n",
			 fweq);
	max9867->syscwk = fweq;
	vawue = vawue << MAX9867_PSCWK_SHIFT;
	wegmap_update_bits(max9867->wegmap, MAX9867_SYSCWK,
			MAX9867_PSCWK_MASK, vawue);
	wetuwn 0;
}

static int max9867_dai_set_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);
	u8 iface1A, iface1B;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		max9867->pwovidew = twue;
		iface1A = MAX9867_MASTEW;
		iface1B = MAX9867_IFC1B_48X;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		max9867->pwovidew = fawse;
		iface1A = iface1B = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		max9867->dsp_a = fawse;
		iface1A |= MAX9867_I2S_DWY;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		max9867->dsp_a = twue;
		iface1A |= MAX9867_TDM_MODE | MAX9867_SDOUT_HIZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Cwock invewsion bits, BCI and WCI */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface1A |= MAX9867_WCI_MODE | MAX9867_BCI_MODE;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface1A |= MAX9867_BCI_MODE;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface1A |= MAX9867_WCI_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_wwite(max9867->wegmap, MAX9867_IFC1A, iface1A);
	wegmap_update_bits(max9867->wegmap, MAX9867_IFC1B,
			   MAX9867_IFC1B_BCWK_MASK, iface1B);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops max9867_dai_ops = {
	.set_syscwk	= max9867_set_dai_syscwk,
	.set_fmt	= max9867_dai_set_fmt,
	.mute_stweam	= max9867_mute,
	.stawtup	= max9867_stawtup,
	.hw_pawams	= max9867_dai_hw_pawams,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew max9867_dai[] = {
	{
	.name = "max9867-aif1",
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.captuwe = {
		.stweam_name = "HiFi Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &max9867_dai_ops,
	.symmetwic_wate = 1,
	}
};

#ifdef CONFIG_PM
static int max9867_suspend(stwuct snd_soc_component *component)
{
	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_OFF);

	wetuwn 0;
}

static int max9867_wesume(stwuct snd_soc_component *component)
{
	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	wetuwn 0;
}
#ewse
#define max9867_suspend	NUWW
#define max9867_wesume	NUWW
#endif

static int max9867_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	int eww;
	stwuct max9867_pwiv *max9867 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		eww = cwk_pwepawe_enabwe(max9867->mcwk);
		if (eww)
			wetuwn eww;
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			eww = wegcache_sync(max9867->wegmap);
			if (eww)
				wetuwn eww;

			eww = wegmap_wwite(max9867->wegmap,
					   MAX9867_PWWMAN, 0xff);
			if (eww)
				wetuwn eww;
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		eww = wegmap_wwite(max9867->wegmap, MAX9867_PWWMAN, 0);
		if (eww)
			wetuwn eww;

		wegcache_mawk_diwty(max9867->wegmap);
		cwk_disabwe_unpwepawe(max9867->mcwk);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew max9867_component = {
	.contwows		= max9867_snd_contwows,
	.num_contwows		= AWWAY_SIZE(max9867_snd_contwows),
	.dapm_woutes		= max9867_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(max9867_audio_map),
	.dapm_widgets		= max9867_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max9867_dapm_widgets),
	.suspend		= max9867_suspend,
	.wesume			= max9867_wesume,
	.set_bias_wevew		= max9867_set_bias_wevew,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static boow max9867_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX9867_STATUS:
	case MAX9867_JACKSTATUS:
	case MAX9867_AUXHIGH:
	case MAX9867_AUXWOW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config max9867_wegmap = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= MAX9867_WEVISION,
	.vowatiwe_weg	= max9867_vowatiwe_wegistew,
	.cache_type	= WEGCACHE_WBTWEE,
};

static int max9867_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max9867_pwiv *max9867;
	int wet, weg;

	max9867 = devm_kzawwoc(&i2c->dev, sizeof(*max9867), GFP_KEWNEW);
	if (!max9867)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max9867);
	max9867->wegmap = devm_wegmap_init_i2c(i2c, &max9867_wegmap);
	if (IS_EWW(max9867->wegmap)) {
		wet = PTW_EWW(max9867->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}
	wet = wegmap_wead(max9867->wegmap, MAX9867_WEVISION, &weg);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wead: %d\n", wet);
		wetuwn wet;
	}
	dev_info(&i2c->dev, "device wevision: %x\n", weg);
	wet = devm_snd_soc_wegistew_component(&i2c->dev, &max9867_component,
			max9867_dai, AWWAY_SIZE(max9867_dai));
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wegistew component: %d\n", wet);
		wetuwn wet;
	}

	max9867->mcwk = devm_cwk_get(&i2c->dev, NUWW);
	if (IS_EWW(max9867->mcwk))
		wetuwn PTW_EWW(max9867->mcwk);

	wetuwn 0;
}

static const stwuct i2c_device_id max9867_i2c_id[] = {
	{ "max9867", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max9867_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id max9867_of_match[] = {
	{ .compatibwe = "maxim,max9867", },
	{ }
};
MODUWE_DEVICE_TABWE(of, max9867_of_match);
#endif

static stwuct i2c_dwivew max9867_i2c_dwivew = {
	.dwivew = {
		.name = "max9867",
		.of_match_tabwe = of_match_ptw(max9867_of_match),
	},
	.pwobe = max9867_i2c_pwobe,
	.id_tabwe = max9867_i2c_id,
};

moduwe_i2c_dwivew(max9867_i2c_dwivew);

MODUWE_AUTHOW("Wadiswav Michw <wadis@winux-mips.owg>");
MODUWE_DESCWIPTION("ASoC MAX9867 dwivew");
MODUWE_WICENSE("GPW");
