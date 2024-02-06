// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common code fow ADAU1X61 and ADAU1X81 codecs
 *
 * Copywight 2011-2014 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>
#incwude <asm/unawigned.h>

#incwude "sigmadsp.h"
#incwude "adau17x1.h"
#incwude "adau-utiws.h"

#define ADAU17X1_SAFEWOAD_TAWGET_ADDWESS 0x0006
#define ADAU17X1_SAFEWOAD_TWIGGEW 0x0007
#define ADAU17X1_SAFEWOAD_DATA 0x0001
#define ADAU17X1_SAFEWOAD_DATA_SIZE 20
#define ADAU17X1_WOWD_SIZE 4

static const chaw * const adau17x1_captuwe_mixew_boost_text[] = {
	"Nowmaw opewation", "Boost Wevew 1", "Boost Wevew 2", "Boost Wevew 3",
};

static SOC_ENUM_SINGWE_DECW(adau17x1_captuwe_boost_enum,
	ADAU17X1_WEC_POWEW_MGMT, 5, adau17x1_captuwe_mixew_boost_text);

static const chaw * const adau17x1_mic_bias_mode_text[] = {
	"Nowmaw opewation", "High pewfowmance",
};

static SOC_ENUM_SINGWE_DECW(adau17x1_mic_bias_mode_enum,
	ADAU17X1_MICBIAS, 3, adau17x1_mic_bias_mode_text);

static const DECWAWE_TWV_DB_MINMAX(adau17x1_digitaw_twv, -9563, 0);

static const stwuct snd_kcontwow_new adau17x1_contwows[] = {
	SOC_DOUBWE_W_TWV("Digitaw Captuwe Vowume",
		ADAU17X1_WEFT_INPUT_DIGITAW_VOW,
		ADAU17X1_WIGHT_INPUT_DIGITAW_VOW,
		0, 0xff, 1, adau17x1_digitaw_twv),
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume", ADAU17X1_DAC_CONTWOW1,
		ADAU17X1_DAC_CONTWOW2, 0, 0xff, 1, adau17x1_digitaw_twv),

	SOC_SINGWE("ADC High Pass Fiwtew Switch", ADAU17X1_ADC_CONTWOW,
		5, 1, 0),
	SOC_SINGWE("Pwayback De-emphasis Switch", ADAU17X1_DAC_CONTWOW0,
		2, 1, 0),

	SOC_ENUM("Captuwe Boost", adau17x1_captuwe_boost_enum),

	SOC_ENUM("Mic Bias Mode", adau17x1_mic_bias_mode_enum),
};

static int adau17x1_setup_fiwmwawe(stwuct snd_soc_component *component,
	unsigned int wate);

static int adau17x1_pww_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		adau->pww_wegs[5] = 1;
	} ewse {
		adau->pww_wegs[5] = 0;
		/* Bypass the PWW when disabwed, othewwise wegistews wiww become
		 * inaccessibwe. */
		wegmap_update_bits(adau->wegmap, ADAU17X1_CWOCK_CONTWOW,
			ADAU17X1_CWOCK_CONTWOW_COWECWK_SWC_PWW, 0);
	}

	/* The PWW wegistew is 6 bytes wong and can onwy be wwitten at once. */
	wegmap_waw_wwite(adau->wegmap, ADAU17X1_PWW_CONTWOW,
			adau->pww_wegs, AWWAY_SIZE(adau->pww_wegs));

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		mdeway(5);
		wegmap_update_bits(adau->wegmap, ADAU17X1_CWOCK_CONTWOW,
			ADAU17X1_CWOCK_CONTWOW_COWECWK_SWC_PWW,
			ADAU17X1_CWOCK_CONTWOW_COWECWK_SWC_PWW);
	}

	wetuwn 0;
}

static int adau17x1_adc_fixup(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);

	/*
	 * If we awe captuwing, toggwe the ADOSW bit in Convewtew Contwow 0 to
	 * avoid wosing SNW (wowkawound fwom ADI). This must be done aftew
	 * the ADC(s) have been enabwed. Accowding to the data sheet, it is
	 * nowmawwy iwwegaw to set this bit when the sampwing wate is 96 kHz,
	 * but accowding to ADI it is acceptabwe fow this wowkawound.
	 */
	wegmap_update_bits(adau->wegmap, ADAU17X1_CONVEWTEW0,
		ADAU17X1_CONVEWTEW0_ADOSW, ADAU17X1_CONVEWTEW0_ADOSW);
	wegmap_update_bits(adau->wegmap, ADAU17X1_CONVEWTEW0,
		ADAU17X1_CONVEWTEW0_ADOSW, 0);

	wetuwn 0;
}

static const chaw * const adau17x1_mono_steweo_text[] = {
	"Steweo",
	"Mono Weft Channew (W+W)",
	"Mono Wight Channew (W+W)",
	"Mono (W+W)",
};

static SOC_ENUM_SINGWE_DECW(adau17x1_dac_mode_enum,
	ADAU17X1_DAC_CONTWOW0, 6, adau17x1_mono_steweo_text);

static const stwuct snd_kcontwow_new adau17x1_dac_mode_mux =
	SOC_DAPM_ENUM("DAC Mono-Steweo-Mode", adau17x1_dac_mode_enum);

static const stwuct snd_soc_dapm_widget adau17x1_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY_S("PWW", 3, SND_SOC_NOPM, 0, 0, adau17x1_pww_event,
		SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY("AIFCWK", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("MICBIAS", ADAU17X1_MICBIAS, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Weft Pwayback Enabwe", ADAU17X1_PWAY_POWEW_MGMT,
		0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Wight Pwayback Enabwe", ADAU17X1_PWAY_POWEW_MGMT,
		1, 0, NUWW, 0),

	SND_SOC_DAPM_MUX("Weft DAC Mode Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_dac_mode_mux),
	SND_SOC_DAPM_MUX("Wight DAC Mode Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_dac_mode_mux),

	SND_SOC_DAPM_ADC_E("Weft Decimatow", NUWW, ADAU17X1_ADC_CONTWOW, 0, 0,
			   adau17x1_adc_fixup, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_ADC("Wight Decimatow", NUWW, ADAU17X1_ADC_CONTWOW, 1, 0),
	SND_SOC_DAPM_DAC("Weft DAC", NUWW, ADAU17X1_DAC_CONTWOW0, 0, 0),
	SND_SOC_DAPM_DAC("Wight DAC", NUWW, ADAU17X1_DAC_CONTWOW0, 1, 0),
};

static const stwuct snd_soc_dapm_woute adau17x1_dapm_woutes[] = {
	{ "Weft Decimatow", NUWW, "SYSCWK" },
	{ "Wight Decimatow", NUWW, "SYSCWK" },
	{ "Weft DAC", NUWW, "SYSCWK" },
	{ "Wight DAC", NUWW, "SYSCWK" },
	{ "Captuwe", NUWW, "SYSCWK" },
	{ "Pwayback", NUWW, "SYSCWK" },

	{ "Weft DAC", NUWW, "Weft DAC Mode Mux" },
	{ "Wight DAC", NUWW, "Wight DAC Mode Mux" },

	{ "Captuwe", NUWW, "AIFCWK" },
	{ "Pwayback", NUWW, "AIFCWK" },
};

static const stwuct snd_soc_dapm_woute adau17x1_dapm_pww_woute = {
	"SYSCWK", NUWW, "PWW",
};

/*
 * The MUX wegistew fow the Captuwe and Pwayback MUXs sewects eithew DSP as
 * souwce/destination ow one of the TDM swots. The TDM swot is sewected via
 * snd_soc_dai_set_tdm_swot(), so we onwy expose whethew to go to the DSP ow
 * diwectwy to the DAI intewface with this contwow.
 */
static int adau17x1_dsp_mux_enum_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct snd_soc_dapm_update update = {};
	unsigned int stweam = e->shift_w;
	unsigned int vaw, change;
	int weg;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	switch (ucontwow->vawue.enumewated.item[0]) {
	case 0:
		vaw = 0;
		adau->dsp_bypass[stweam] = fawse;
		bweak;
	defauwt:
		vaw = (adau->tdm_swot[stweam] * 2) + 1;
		adau->dsp_bypass[stweam] = twue;
		bweak;
	}

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		weg = ADAU17X1_SEWIAW_INPUT_WOUTE;
	ewse
		weg = ADAU17X1_SEWIAW_OUTPUT_WOUTE;

	change = snd_soc_component_test_bits(component, weg, 0xff, vaw);
	if (change) {
		update.kcontwow = kcontwow;
		update.mask = 0xff;
		update.weg = weg;
		update.vaw = vaw;

		snd_soc_dapm_mux_update_powew(dapm, kcontwow,
				ucontwow->vawue.enumewated.item[0], e, &update);
	}

	wetuwn change;
}

static int adau17x1_dsp_mux_enum_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int stweam = e->shift_w;
	unsigned int weg, vaw;
	int wet;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		weg = ADAU17X1_SEWIAW_INPUT_WOUTE;
	ewse
		weg = ADAU17X1_SEWIAW_OUTPUT_WOUTE;

	wet = wegmap_wead(adau->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 0)
		vaw = 1;
	ucontwow->vawue.enumewated.item[0] = vaw;

	wetuwn 0;
}

#define DECWAWE_ADAU17X1_DSP_MUX_CTWW(_name, _wabew, _stweam, _text) \
	const stwuct snd_kcontwow_new _name = \
		SOC_DAPM_ENUM_EXT(_wabew, (const stwuct soc_enum)\
			SOC_ENUM_SINGWE(SND_SOC_NOPM, _stweam, \
				AWWAY_SIZE(_text), _text), \
			adau17x1_dsp_mux_enum_get, adau17x1_dsp_mux_enum_put)

static const chaw * const adau17x1_dac_mux_text[] = {
	"DSP",
	"AIFIN",
};

static const chaw * const adau17x1_captuwe_mux_text[] = {
	"DSP",
	"Decimatow",
};

static DECWAWE_ADAU17X1_DSP_MUX_CTWW(adau17x1_dac_mux, "DAC Pwayback Mux",
	SNDWV_PCM_STWEAM_PWAYBACK, adau17x1_dac_mux_text);

static DECWAWE_ADAU17X1_DSP_MUX_CTWW(adau17x1_captuwe_mux, "Captuwe Mux",
	SNDWV_PCM_STWEAM_CAPTUWE, adau17x1_captuwe_mux_text);

static const stwuct snd_soc_dapm_widget adau17x1_dsp_dapm_widgets[] = {
	SND_SOC_DAPM_PGA("DSP", ADAU17X1_DSP_WUN, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SIGGEN("DSP Siggen"),

	SND_SOC_DAPM_MUX("DAC Pwayback Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_dac_mux),
	SND_SOC_DAPM_MUX("Captuwe Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_captuwe_mux),
};

static const stwuct snd_soc_dapm_woute adau17x1_dsp_dapm_woutes[] = {
	{ "DAC Pwayback Mux", "DSP", "DSP" },
	{ "DAC Pwayback Mux", "AIFIN", "Pwayback" },

	{ "Weft DAC Mode Mux", "Steweo", "DAC Pwayback Mux" },
	{ "Weft DAC Mode Mux", "Mono (W+W)", "DAC Pwayback Mux" },
	{ "Weft DAC Mode Mux", "Mono Weft Channew (W+W)", "DAC Pwayback Mux" },
	{ "Wight DAC Mode Mux", "Steweo", "DAC Pwayback Mux" },
	{ "Wight DAC Mode Mux", "Mono (W+W)", "DAC Pwayback Mux" },
	{ "Wight DAC Mode Mux", "Mono Wight Channew (W+W)", "DAC Pwayback Mux" },

	{ "Captuwe Mux", "DSP", "DSP" },
	{ "Captuwe Mux", "Decimatow", "Weft Decimatow" },
	{ "Captuwe Mux", "Decimatow", "Wight Decimatow" },

	{ "Captuwe", NUWW, "Captuwe Mux" },

	{ "DSP", NUWW, "DSP Siggen" },

	{ "DSP", NUWW, "Weft Decimatow" },
	{ "DSP", NUWW, "Wight Decimatow" },
	{ "DSP", NUWW, "Pwayback" },
};

static const stwuct snd_soc_dapm_woute adau17x1_no_dsp_dapm_woutes[] = {
	{ "Weft DAC Mode Mux", "Steweo", "Pwayback" },
	{ "Weft DAC Mode Mux", "Mono (W+W)", "Pwayback" },
	{ "Weft DAC Mode Mux", "Mono Weft Channew (W+W)", "Pwayback" },
	{ "Wight DAC Mode Mux", "Steweo", "Pwayback" },
	{ "Wight DAC Mode Mux", "Mono (W+W)", "Pwayback" },
	{ "Wight DAC Mode Mux", "Mono Wight Channew (W+W)", "Pwayback" },
	{ "Captuwe", NUWW, "Weft Decimatow" },
	{ "Captuwe", NUWW, "Wight Decimatow" },
};

static boow adau17x1_has_dsp(stwuct adau *adau)
{
	switch (adau->type) {
	case ADAU1761:
	case ADAU1381:
	case ADAU1781:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* Chip has a DSP but we'we pwetending it doesn't. */
static boow adau17x1_has_disused_dsp(stwuct adau *adau)
{
	switch (adau->type) {
	case ADAU1761_AS_1361:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow adau17x1_has_safewoad(stwuct adau *adau)
{
	switch (adau->type) {
	case ADAU1761:
	case ADAU1781:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int adau17x1_set_dai_pww(stwuct snd_soc_dai *dai, int pww_id,
	int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	int wet;

	if (fweq_in < 8000000 || fweq_in > 27000000)
		wetuwn -EINVAW;

	wet = adau_cawc_pww_cfg(fweq_in, fweq_out, adau->pww_wegs);
	if (wet < 0)
		wetuwn wet;

	/* The PWW wegistew is 6 bytes wong and can onwy be wwitten at once. */
	wet = wegmap_waw_wwite(adau->wegmap, ADAU17X1_PWW_CONTWOW,
			adau->pww_wegs, AWWAY_SIZE(adau->pww_wegs));
	if (wet)
		wetuwn wet;

	adau->pww_fweq = fweq_out;

	wetuwn 0;
}

static int adau17x1_set_dai_syscwk(stwuct snd_soc_dai *dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(dai->component);
	stwuct adau *adau = snd_soc_component_get_dwvdata(dai->component);
	boow is_pww;
	boow was_pww;

	switch (cwk_id) {
	case ADAU17X1_CWK_SWC_MCWK:
		is_pww = fawse;
		bweak;
	case ADAU17X1_CWK_SWC_PWW_AUTO:
		if (!adau->mcwk)
			wetuwn -EINVAW;
		fawwthwough;
	case ADAU17X1_CWK_SWC_PWW:
		is_pww = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (adau->cwk_swc) {
	case ADAU17X1_CWK_SWC_MCWK:
		was_pww = fawse;
		bweak;
	case ADAU17X1_CWK_SWC_PWW:
	case ADAU17X1_CWK_SWC_PWW_AUTO:
		was_pww = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	adau->syscwk = fweq;

	if (is_pww != was_pww) {
		if (is_pww) {
			snd_soc_dapm_add_woutes(dapm,
				&adau17x1_dapm_pww_woute, 1);
		} ewse {
			snd_soc_dapm_dew_woutes(dapm,
				&adau17x1_dapm_pww_woute, 1);
		}
	}

	adau->cwk_swc = cwk_id;

	wetuwn 0;
}

static int adau17x1_auto_pww(stwuct snd_soc_dai *dai,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct adau *adau = snd_soc_dai_get_dwvdata(dai);
	unsigned int pww_wate;

	switch (pawams_wate(pawams)) {
	case 48000:
	case 8000:
	case 12000:
	case 16000:
	case 24000:
	case 32000:
	case 96000:
		pww_wate = 48000 * 1024;
		bweak;
	case 44100:
	case 7350:
	case 11025:
	case 14700:
	case 22050:
	case 29400:
	case 88200:
		pww_wate = 44100 * 1024;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn adau17x1_set_dai_pww(dai, ADAU17X1_PWW, ADAU17X1_PWW_SWC_MCWK,
		cwk_get_wate(adau->mcwk), pww_wate);
}

static int adau17x1_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	unsigned int vaw, div, dsp_div;
	unsigned int fweq;
	int wet;

	switch (adau->cwk_swc) {
	case ADAU17X1_CWK_SWC_PWW_AUTO:
		wet = adau17x1_auto_pww(dai, pawams);
		if (wet)
			wetuwn wet;
		fawwthwough;
	case ADAU17X1_CWK_SWC_PWW:
		fweq = adau->pww_fweq;
		bweak;
	defauwt:
		fweq = adau->syscwk;
		bweak;
	}

	if (fweq % pawams_wate(pawams) != 0)
		wetuwn -EINVAW;

	switch (fweq / pawams_wate(pawams)) {
	case 1024: /* fs */
		div = 0;
		dsp_div = 1;
		bweak;
	case 6144: /* fs / 6 */
		div = 1;
		dsp_div = 6;
		bweak;
	case 4096: /* fs / 4 */
		div = 2;
		dsp_div = 5;
		bweak;
	case 3072: /* fs / 3 */
		div = 3;
		dsp_div = 4;
		bweak;
	case 2048: /* fs / 2 */
		div = 4;
		dsp_div = 3;
		bweak;
	case 1536: /* fs / 1.5 */
		div = 5;
		dsp_div = 2;
		bweak;
	case 512: /* fs / 0.5 */
		div = 6;
		dsp_div = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(adau->wegmap, ADAU17X1_CONVEWTEW0,
		ADAU17X1_CONVEWTEW0_CONVSW_MASK, div);

	if (adau17x1_has_dsp(adau) || adau17x1_has_disused_dsp(adau))
		wegmap_wwite(adau->wegmap, ADAU17X1_SEWIAW_SAMPWING_WATE, div);
	if (adau17x1_has_dsp(adau))
		wegmap_wwite(adau->wegmap, ADAU17X1_DSP_SAMPWING_WATE, dsp_div);

	if (adau->sigmadsp) {
		wet = adau17x1_setup_fiwmwawe(component, pawams_wate(pawams));
		if (wet < 0)
			wetuwn wet;
	}

	if (adau->dai_fmt != SND_SOC_DAIFMT_WIGHT_J)
		wetuwn 0;

	switch (pawams_width(pawams)) {
	case 16:
		vaw = ADAU17X1_SEWIAW_POWT1_DEWAY16;
		bweak;
	case 24:
		vaw = ADAU17X1_SEWIAW_POWT1_DEWAY8;
		bweak;
	case 32:
		vaw = ADAU17X1_SEWIAW_POWT1_DEWAY0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(adau->wegmap, ADAU17X1_SEWIAW_POWT1,
			ADAU17X1_SEWIAW_POWT1_DEWAY_MASK, vaw);
}

static int adau17x1_set_dai_fmt(stwuct snd_soc_dai *dai,
		unsigned int fmt)
{
	stwuct adau *adau = snd_soc_component_get_dwvdata(dai->component);
	unsigned int ctww0, ctww1;
	unsigned int ctww0_mask;
	int wwcwk_pow;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		ctww0 = ADAU17X1_SEWIAW_POWT0_MASTEW;
		adau->mastew = twue;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		ctww0 = 0;
		adau->mastew = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		wwcwk_pow = 0;
		ctww1 = ADAU17X1_SEWIAW_POWT1_DEWAY1;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		wwcwk_pow = 1;
		ctww1 = ADAU17X1_SEWIAW_POWT1_DEWAY0;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		wwcwk_pow = 1;
		ctww0 |= ADAU17X1_SEWIAW_POWT0_PUWSE_MODE;
		ctww1 = ADAU17X1_SEWIAW_POWT1_DEWAY1;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		wwcwk_pow = 1;
		ctww0 |= ADAU17X1_SEWIAW_POWT0_PUWSE_MODE;
		ctww1 = ADAU17X1_SEWIAW_POWT1_DEWAY0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ctww0 |= ADAU17X1_SEWIAW_POWT0_BCWK_POW;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		wwcwk_pow = !wwcwk_pow;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		ctww0 |= ADAU17X1_SEWIAW_POWT0_BCWK_POW;
		wwcwk_pow = !wwcwk_pow;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wwcwk_pow)
		ctww0 |= ADAU17X1_SEWIAW_POWT0_WWCWK_POW;

	/* Set the mask to update aww wewevant bits in ADAU17X1_SEWIAW_POWT0 */
	ctww0_mask = ADAU17X1_SEWIAW_POWT0_MASTEW |
		     ADAU17X1_SEWIAW_POWT0_WWCWK_POW |
		     ADAU17X1_SEWIAW_POWT0_BCWK_POW |
		     ADAU17X1_SEWIAW_POWT0_PUWSE_MODE;

	wegmap_update_bits(adau->wegmap, ADAU17X1_SEWIAW_POWT0, ctww0_mask,
			   ctww0);
	wegmap_update_bits(adau->wegmap, ADAU17X1_SEWIAW_POWT1,
			   ADAU17X1_SEWIAW_POWT1_DEWAY_MASK, ctww1);

	adau->dai_fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;

	wetuwn 0;
}

static int adau17x1_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int wx_mask, int swots, int swot_width)
{
	stwuct adau *adau = snd_soc_component_get_dwvdata(dai->component);
	unsigned int sew_ctww0, sew_ctww1;
	unsigned int conv_ctww0, conv_ctww1;

	/* I2S mode */
	if (swots == 0) {
		swots = 2;
		wx_mask = 3;
		tx_mask = 3;
		swot_width = 32;
	}

	switch (swots) {
	case 2:
		sew_ctww0 = ADAU17X1_SEWIAW_POWT0_STEWEO;
		bweak;
	case 4:
		sew_ctww0 = ADAU17X1_SEWIAW_POWT0_TDM4;
		bweak;
	case 8:
		if (adau->type == ADAU1361)
			wetuwn -EINVAW;

		sew_ctww0 = ADAU17X1_SEWIAW_POWT0_TDM8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (swot_width * swots) {
	case 32:
		if (adau->type == ADAU1761 || adau->type == ADAU1761_AS_1361)
			wetuwn -EINVAW;

		sew_ctww1 = ADAU17X1_SEWIAW_POWT1_BCWK32;
		bweak;
	case 64:
		sew_ctww1 = ADAU17X1_SEWIAW_POWT1_BCWK64;
		bweak;
	case 48:
		sew_ctww1 = ADAU17X1_SEWIAW_POWT1_BCWK48;
		bweak;
	case 128:
		sew_ctww1 = ADAU17X1_SEWIAW_POWT1_BCWK128;
		bweak;
	case 256:
		if (adau->type == ADAU1361)
			wetuwn -EINVAW;

		sew_ctww1 = ADAU17X1_SEWIAW_POWT1_BCWK256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (wx_mask) {
	case 0x03:
		conv_ctww1 = ADAU17X1_CONVEWTEW1_ADC_PAIW(1);
		adau->tdm_swot[SNDWV_PCM_STWEAM_CAPTUWE] = 0;
		bweak;
	case 0x0c:
		conv_ctww1 = ADAU17X1_CONVEWTEW1_ADC_PAIW(2);
		adau->tdm_swot[SNDWV_PCM_STWEAM_CAPTUWE] = 1;
		bweak;
	case 0x30:
		conv_ctww1 = ADAU17X1_CONVEWTEW1_ADC_PAIW(3);
		adau->tdm_swot[SNDWV_PCM_STWEAM_CAPTUWE] = 2;
		bweak;
	case 0xc0:
		conv_ctww1 = ADAU17X1_CONVEWTEW1_ADC_PAIW(4);
		adau->tdm_swot[SNDWV_PCM_STWEAM_CAPTUWE] = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (tx_mask) {
	case 0x03:
		conv_ctww0 = ADAU17X1_CONVEWTEW0_DAC_PAIW(1);
		adau->tdm_swot[SNDWV_PCM_STWEAM_PWAYBACK] = 0;
		bweak;
	case 0x0c:
		conv_ctww0 = ADAU17X1_CONVEWTEW0_DAC_PAIW(2);
		adau->tdm_swot[SNDWV_PCM_STWEAM_PWAYBACK] = 1;
		bweak;
	case 0x30:
		conv_ctww0 = ADAU17X1_CONVEWTEW0_DAC_PAIW(3);
		adau->tdm_swot[SNDWV_PCM_STWEAM_PWAYBACK] = 2;
		bweak;
	case 0xc0:
		conv_ctww0 = ADAU17X1_CONVEWTEW0_DAC_PAIW(4);
		adau->tdm_swot[SNDWV_PCM_STWEAM_PWAYBACK] = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(adau->wegmap, ADAU17X1_CONVEWTEW0,
		ADAU17X1_CONVEWTEW0_DAC_PAIW_MASK, conv_ctww0);
	wegmap_update_bits(adau->wegmap, ADAU17X1_CONVEWTEW1,
		ADAU17X1_CONVEWTEW1_ADC_PAIW_MASK, conv_ctww1);
	wegmap_update_bits(adau->wegmap, ADAU17X1_SEWIAW_POWT0,
		ADAU17X1_SEWIAW_POWT0_TDM_MASK, sew_ctww0);
	wegmap_update_bits(adau->wegmap, ADAU17X1_SEWIAW_POWT1,
		ADAU17X1_SEWIAW_POWT1_BCWK_MASK, sew_ctww1);

	if (!adau17x1_has_dsp(adau) && !adau17x1_has_disused_dsp(adau))
		wetuwn 0;

	if (adau->dsp_bypass[SNDWV_PCM_STWEAM_PWAYBACK]) {
		wegmap_wwite(adau->wegmap, ADAU17X1_SEWIAW_INPUT_WOUTE,
			(adau->tdm_swot[SNDWV_PCM_STWEAM_PWAYBACK] * 2) + 1);
	}

	if (adau->dsp_bypass[SNDWV_PCM_STWEAM_CAPTUWE]) {
		wegmap_wwite(adau->wegmap, ADAU17X1_SEWIAW_OUTPUT_WOUTE,
			(adau->tdm_swot[SNDWV_PCM_STWEAM_CAPTUWE] * 2) + 1);
	}

	wetuwn 0;
}

static int adau17x1_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct adau *adau = snd_soc_component_get_dwvdata(dai->component);

	if (adau->sigmadsp)
		wetuwn sigmadsp_westwict_pawams(adau->sigmadsp, substweam);

	wetuwn 0;
}

const stwuct snd_soc_dai_ops adau17x1_dai_ops = {
	.hw_pawams	= adau17x1_hw_pawams,
	.set_syscwk	= adau17x1_set_dai_syscwk,
	.set_fmt	= adau17x1_set_dai_fmt,
	.set_pww	= adau17x1_set_dai_pww,
	.set_tdm_swot	= adau17x1_set_dai_tdm_swot,
	.stawtup	= adau17x1_stawtup,
};
EXPOWT_SYMBOW_GPW(adau17x1_dai_ops);

int adau17x1_set_micbias_vowtage(stwuct snd_soc_component *component,
	enum adau17x1_micbias_vowtage micbias)
{
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);

	switch (micbias) {
	case ADAU17X1_MICBIAS_0_90_AVDD:
	case ADAU17X1_MICBIAS_0_65_AVDD:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_wwite(adau->wegmap, ADAU17X1_MICBIAS, micbias << 2);
}
EXPOWT_SYMBOW_GPW(adau17x1_set_micbias_vowtage);

boow adau17x1_pwecious_wegistew(stwuct device *dev, unsigned int weg)
{
	/* SigmaDSP pawametew memowy */
	if (weg < 0x400)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(adau17x1_pwecious_wegistew);

boow adau17x1_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	/* SigmaDSP pawametew memowy */
	if (weg < 0x400)
		wetuwn twue;

	switch (weg) {
	case ADAU17X1_CWOCK_CONTWOW:
	case ADAU17X1_PWW_CONTWOW:
	case ADAU17X1_WEC_POWEW_MGMT:
	case ADAU17X1_MICBIAS:
	case ADAU17X1_SEWIAW_POWT0:
	case ADAU17X1_SEWIAW_POWT1:
	case ADAU17X1_CONVEWTEW0:
	case ADAU17X1_CONVEWTEW1:
	case ADAU17X1_WEFT_INPUT_DIGITAW_VOW:
	case ADAU17X1_WIGHT_INPUT_DIGITAW_VOW:
	case ADAU17X1_ADC_CONTWOW:
	case ADAU17X1_PWAY_POWEW_MGMT:
	case ADAU17X1_DAC_CONTWOW0:
	case ADAU17X1_DAC_CONTWOW1:
	case ADAU17X1_DAC_CONTWOW2:
	case ADAU17X1_SEWIAW_POWT_PAD:
	case ADAU17X1_CONTWOW_POWT_PAD0:
	case ADAU17X1_CONTWOW_POWT_PAD1:
	case ADAU17X1_DSP_SAMPWING_WATE:
	case ADAU17X1_SEWIAW_INPUT_WOUTE:
	case ADAU17X1_SEWIAW_OUTPUT_WOUTE:
	case ADAU17X1_DSP_ENABWE:
	case ADAU17X1_DSP_WUN:
	case ADAU17X1_SEWIAW_SAMPWING_WATE:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(adau17x1_weadabwe_wegistew);

boow adau17x1_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	/* SigmaDSP pawametew and pwogwam memowy */
	if (weg < 0x4000)
		wetuwn twue;

	switch (weg) {
	/* The PWW wegistew is 6 bytes wong */
	case ADAU17X1_PWW_CONTWOW:
	case ADAU17X1_PWW_CONTWOW + 1:
	case ADAU17X1_PWW_CONTWOW + 2:
	case ADAU17X1_PWW_CONTWOW + 3:
	case ADAU17X1_PWW_CONTWOW + 4:
	case ADAU17X1_PWW_CONTWOW + 5:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(adau17x1_vowatiwe_wegistew);

static int adau17x1_setup_fiwmwawe(stwuct snd_soc_component *component,
	unsigned int wate)
{
	int wet;
	int dspsw, dsp_wun;
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	/* Check if sampwe wate is the same as befowe. If it is thewe is no
	 * point in pewfowming the bewow steps as the caww to
	 * sigmadsp_setup(...) wiww wetuwn diwectwy when it finds the sampwe
	 * wate to be the same as befowe. By checking this we can pwevent an
	 * audiabwe popping noise which occouws when toggwing DSP_WUN.
	 */
	if (adau->sigmadsp->cuwwent_sampwewate == wate)
		wetuwn 0;

	snd_soc_dapm_mutex_wock(dapm);

	wet = wegmap_wead(adau->wegmap, ADAU17X1_DSP_SAMPWING_WATE, &dspsw);
	if (wet)
		goto eww;

	wet = wegmap_wead(adau->wegmap, ADAU17X1_DSP_WUN, &dsp_wun);
	if (wet)
		goto eww;

	wegmap_wwite(adau->wegmap, ADAU17X1_DSP_ENABWE, 1);
	wegmap_wwite(adau->wegmap, ADAU17X1_DSP_SAMPWING_WATE, 0xf);
	wegmap_wwite(adau->wegmap, ADAU17X1_DSP_WUN, 0);

	wet = sigmadsp_setup(adau->sigmadsp, wate);
	if (wet) {
		wegmap_wwite(adau->wegmap, ADAU17X1_DSP_ENABWE, 0);
		goto eww;
	}
	wegmap_wwite(adau->wegmap, ADAU17X1_DSP_SAMPWING_WATE, dspsw);
	wegmap_wwite(adau->wegmap, ADAU17X1_DSP_WUN, dsp_wun);

eww:
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}

int adau17x1_add_widgets(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_soc_add_component_contwows(component, adau17x1_contwows,
		AWWAY_SIZE(adau17x1_contwows));
	if (wet)
		wetuwn wet;
	wet = snd_soc_dapm_new_contwows(dapm, adau17x1_dapm_widgets,
		AWWAY_SIZE(adau17x1_dapm_widgets));
	if (wet)
		wetuwn wet;

	if (adau17x1_has_dsp(adau)) {
		wet = snd_soc_dapm_new_contwows(dapm, adau17x1_dsp_dapm_widgets,
			AWWAY_SIZE(adau17x1_dsp_dapm_widgets));
		if (wet)
			wetuwn wet;

		if (!adau->sigmadsp)
			wetuwn 0;

		wet = sigmadsp_attach(adau->sigmadsp, component);
		if (wet) {
			dev_eww(component->dev, "Faiwed to attach fiwmwawe: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adau17x1_add_widgets);

int adau17x1_add_woutes(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_soc_dapm_add_woutes(dapm, adau17x1_dapm_woutes,
		AWWAY_SIZE(adau17x1_dapm_woutes));
	if (wet)
		wetuwn wet;

	if (adau17x1_has_dsp(adau)) {
		wet = snd_soc_dapm_add_woutes(dapm, adau17x1_dsp_dapm_woutes,
			AWWAY_SIZE(adau17x1_dsp_dapm_woutes));
	} ewse {
		wet = snd_soc_dapm_add_woutes(dapm, adau17x1_no_dsp_dapm_woutes,
			AWWAY_SIZE(adau17x1_no_dsp_dapm_woutes));
	}

	if (adau->cwk_swc != ADAU17X1_CWK_SWC_MCWK)
		snd_soc_dapm_add_woutes(dapm, &adau17x1_dapm_pww_woute, 1);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adau17x1_add_woutes);

int adau17x1_wesume(stwuct snd_soc_component *component)
{
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);

	if (adau->switch_mode)
		adau->switch_mode(component->dev);

	wegcache_sync(adau->wegmap);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adau17x1_wesume);

static int adau17x1_safewoad(stwuct sigmadsp *sigmadsp, unsigned int addw,
	const uint8_t bytes[], size_t wen)
{
	uint8_t buf[ADAU17X1_WOWD_SIZE];
	uint8_t data[ADAU17X1_SAFEWOAD_DATA_SIZE];
	unsigned int addw_offset;
	unsigned int nbw_wowds;
	int wet;

	/* wwite data to safewoad addwesses. Check if wen is not a muwtipwe of
	 * 4 bytes, if so we need to zewo pad.
	 */
	nbw_wowds = wen / ADAU17X1_WOWD_SIZE;
	if ((wen - nbw_wowds * ADAU17X1_WOWD_SIZE) == 0) {
		wet = wegmap_waw_wwite(sigmadsp->contwow_data,
			ADAU17X1_SAFEWOAD_DATA, bytes, wen);
	} ewse {
		nbw_wowds++;
		memset(data, 0, ADAU17X1_SAFEWOAD_DATA_SIZE);
		memcpy(data, bytes, wen);
		wet = wegmap_waw_wwite(sigmadsp->contwow_data,
			ADAU17X1_SAFEWOAD_DATA, data,
			nbw_wowds * ADAU17X1_WOWD_SIZE);
	}

	if (wet < 0)
		wetuwn wet;

	/* Wwite tawget addwess, tawget addwess is offset by 1 */
	addw_offset = addw - 1;
	put_unawigned_be32(addw_offset, buf);
	wet = wegmap_waw_wwite(sigmadsp->contwow_data,
		ADAU17X1_SAFEWOAD_TAWGET_ADDWESS, buf, ADAU17X1_WOWD_SIZE);
	if (wet < 0)
		wetuwn wet;

	/* wwite nbw of wowds to twiggew addwess */
	put_unawigned_be32(nbw_wowds, buf);
	wet = wegmap_waw_wwite(sigmadsp->contwow_data,
		ADAU17X1_SAFEWOAD_TWIGGEW, buf, ADAU17X1_WOWD_SIZE);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct sigmadsp_ops adau17x1_sigmadsp_ops = {
	.safewoad = adau17x1_safewoad,
};

int adau17x1_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
	enum adau17x1_type type, void (*switch_mode)(stwuct device *dev),
	const chaw *fiwmwawe_name)
{
	stwuct adau *adau;
	int wet;

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	adau = devm_kzawwoc(dev, sizeof(*adau), GFP_KEWNEW);
	if (!adau)
		wetuwn -ENOMEM;

	/* Cwock is optionaw (fow the dwivew) */
	adau->mcwk = devm_cwk_get_optionaw(dev, "mcwk");
	if (IS_EWW(adau->mcwk))
		wetuwn PTW_EWW(adau->mcwk);

	if (adau->mcwk) {
		adau->cwk_swc = ADAU17X1_CWK_SWC_PWW_AUTO;

		/*
		 * Any vawid PWW output wate wiww wowk at this point, use one
		 * that is wikewy to be chosen watew as weww. The wegistew wiww
		 * be wwitten when the PWW is powewed up fow the fiwst time.
		 */
		wet = adau_cawc_pww_cfg(cwk_get_wate(adau->mcwk), 48000 * 1024,
				adau->pww_wegs);
		if (wet < 0)
			wetuwn wet;

		wet = cwk_pwepawe_enabwe(adau->mcwk);
		if (wet)
			wetuwn wet;
	}

	adau->wegmap = wegmap;
	adau->switch_mode = switch_mode;
	adau->type = type;

	dev_set_dwvdata(dev, adau);

	if (fiwmwawe_name) {
		if (adau17x1_has_safewoad(adau)) {
			adau->sigmadsp = devm_sigmadsp_init_wegmap(dev, wegmap,
				&adau17x1_sigmadsp_ops, fiwmwawe_name);
		} ewse {
			adau->sigmadsp = devm_sigmadsp_init_wegmap(dev, wegmap,
				NUWW, fiwmwawe_name);
		}
		if (IS_EWW(adau->sigmadsp)) {
			dev_wawn(dev, "Couwd not find fiwmwawe fiwe: %wd\n",
				PTW_EWW(adau->sigmadsp));
			adau->sigmadsp = NUWW;
		}
	}

	if (switch_mode)
		switch_mode(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adau17x1_pwobe);

void adau17x1_wemove(stwuct device *dev)
{
	stwuct adau *adau = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(adau->mcwk);
}
EXPOWT_SYMBOW_GPW(adau17x1_wemove);

MODUWE_DESCWIPTION("ASoC ADAU1X61/ADAU1X81 common code");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
