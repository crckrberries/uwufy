// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt298.c  --  WT298 AWSA SoC audio codec dwivew
 *
 * Copywight 2015 Weawtek Semiconductow Cowp.
 * Authow: Bawd Wiao <bawdwiao@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/jack.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/wt298.h>

#incwude "ww6347a.h"
#incwude "wt298.h"

#define WT298_VENDOW_ID 0x10ec0298

stwuct wt298_pwiv {
	stwuct weg_defauwt *index_cache;
	int index_cache_size;
	stwuct wegmap *wegmap;
	stwuct snd_soc_component *component;
	stwuct wt298_pwatfowm_data pdata;
	stwuct i2c_cwient *i2c;
	stwuct snd_soc_jack *jack;
	stwuct dewayed_wowk jack_detect_wowk;
	int sys_cwk;
	int cwk_id;
	int is_hp_in;
};

static const stwuct weg_defauwt wt298_index_def[] = {
	{ 0x01, 0xa5a8 },
	{ 0x02, 0x8e95 },
	{ 0x03, 0x0002 },
	{ 0x04, 0xaf67 },
	{ 0x08, 0x200f },
	{ 0x09, 0xd010 },
	{ 0x0a, 0x0100 },
	{ 0x0b, 0x0000 },
	{ 0x0d, 0x2800 },
	{ 0x0f, 0x0022 },
	{ 0x19, 0x0217 },
	{ 0x20, 0x0020 },
	{ 0x33, 0x0208 },
	{ 0x46, 0x0300 },
	{ 0x49, 0x4004 },
	{ 0x4f, 0x50c9 },
	{ 0x50, 0x3000 },
	{ 0x63, 0x1b02 },
	{ 0x67, 0x1111 },
	{ 0x68, 0x1016 },
	{ 0x69, 0x273f },
};
#define INDEX_CACHE_SIZE AWWAY_SIZE(wt298_index_def)

static const stwuct weg_defauwt wt298_weg[] = {
	{ 0x00170500, 0x00000400 },
	{ 0x00220000, 0x00000031 },
	{ 0x00239000, 0x0000007f },
	{ 0x0023a000, 0x0000007f },
	{ 0x00270500, 0x00000400 },
	{ 0x00370500, 0x00000400 },
	{ 0x00870500, 0x00000400 },
	{ 0x00920000, 0x00000031 },
	{ 0x00935000, 0x000000c3 },
	{ 0x00936000, 0x000000c3 },
	{ 0x00970500, 0x00000400 },
	{ 0x00b37000, 0x00000097 },
	{ 0x00b37200, 0x00000097 },
	{ 0x00b37300, 0x00000097 },
	{ 0x00c37000, 0x00000000 },
	{ 0x00c37100, 0x00000080 },
	{ 0x01270500, 0x00000400 },
	{ 0x01370500, 0x00000400 },
	{ 0x01371f00, 0x411111f0 },
	{ 0x01439000, 0x00000080 },
	{ 0x0143a000, 0x00000080 },
	{ 0x01470700, 0x00000000 },
	{ 0x01470500, 0x00000400 },
	{ 0x01470c00, 0x00000000 },
	{ 0x01470100, 0x00000000 },
	{ 0x01837000, 0x00000000 },
	{ 0x01870500, 0x00000400 },
	{ 0x02050000, 0x00000000 },
	{ 0x02139000, 0x00000080 },
	{ 0x0213a000, 0x00000080 },
	{ 0x02170100, 0x00000000 },
	{ 0x02170500, 0x00000400 },
	{ 0x02170700, 0x00000000 },
	{ 0x02270100, 0x00000000 },
	{ 0x02370100, 0x00000000 },
	{ 0x01870700, 0x00000020 },
	{ 0x00830000, 0x000000c3 },
	{ 0x00930000, 0x000000c3 },
	{ 0x01270700, 0x00000000 },
};

static boow wt298_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0 ... 0xff:
	case WT298_GET_PAWAM(AC_NODE_WOOT, AC_PAW_VENDOW_ID):
	case WT298_GET_HP_SENSE:
	case WT298_GET_MIC1_SENSE:
	case WT298_PWOC_COEF:
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT298_MIC1, 0):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT298_SPK_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT298_HP_OUT, 0):
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}


}

static boow wt298_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0 ... 0xff:
	case WT298_GET_PAWAM(AC_NODE_WOOT, AC_PAW_VENDOW_ID):
	case WT298_GET_HP_SENSE:
	case WT298_GET_MIC1_SENSE:
	case WT298_SET_AUDIO_POWEW:
	case WT298_SET_HPO_POWEW:
	case WT298_SET_SPK_POWEW:
	case WT298_SET_DMIC1_POWEW:
	case WT298_SPK_MUX:
	case WT298_HPO_MUX:
	case WT298_ADC0_MUX:
	case WT298_ADC1_MUX:
	case WT298_SET_MIC1:
	case WT298_SET_PIN_HPO:
	case WT298_SET_PIN_SPK:
	case WT298_SET_PIN_DMIC1:
	case WT298_SPK_EAPD:
	case WT298_SET_AMP_GAIN_HPO:
	case WT298_SET_DMIC2_DEFAUWT:
	case WT298_DACW_GAIN:
	case WT298_DACW_GAIN:
	case WT298_ADCW_GAIN:
	case WT298_ADCW_GAIN:
	case WT298_MIC_GAIN:
	case WT298_SPOW_GAIN:
	case WT298_SPOW_GAIN:
	case WT298_HPOW_GAIN:
	case WT298_HPOW_GAIN:
	case WT298_F_DAC_SWITCH:
	case WT298_F_WECMIX_SWITCH:
	case WT298_WEC_MIC_SWITCH:
	case WT298_WEC_I2S_SWITCH:
	case WT298_WEC_WINE_SWITCH:
	case WT298_WEC_BEEP_SWITCH:
	case WT298_DAC_FOWMAT:
	case WT298_ADC_FOWMAT:
	case WT298_COEF_INDEX:
	case WT298_PWOC_COEF:
	case WT298_SET_AMP_GAIN_ADC_IN1:
	case WT298_SET_AMP_GAIN_ADC_IN2:
	case WT298_SET_POWEW(WT298_DAC_OUT1):
	case WT298_SET_POWEW(WT298_DAC_OUT2):
	case WT298_SET_POWEW(WT298_ADC_IN1):
	case WT298_SET_POWEW(WT298_ADC_IN2):
	case WT298_SET_POWEW(WT298_DMIC2):
	case WT298_SET_POWEW(WT298_MIC1):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT298_MIC1, 0):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT298_SPK_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT298_HP_OUT, 0):
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

#ifdef CONFIG_PM
static void wt298_index_sync(stwuct snd_soc_component *component)
{
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);
	int i;

	fow (i = 0; i < INDEX_CACHE_SIZE; i++) {
		snd_soc_component_wwite(component, wt298->index_cache[i].weg,
				  wt298->index_cache[i].def);
	}
}
#endif

static int wt298_suppowt_powew_contwows[] = {
	WT298_DAC_OUT1,
	WT298_DAC_OUT2,
	WT298_ADC_IN1,
	WT298_ADC_IN2,
	WT298_MIC1,
	WT298_DMIC1,
	WT298_DMIC2,
	WT298_SPK_OUT,
	WT298_HP_OUT,
};
#define WT298_POWEW_WEG_WEN AWWAY_SIZE(wt298_suppowt_powew_contwows)

static int wt298_jack_detect(stwuct wt298_pwiv *wt298, boow *hp, boow *mic)
{
	stwuct snd_soc_dapm_context *dapm;
	unsigned int vaw, buf;

	*hp = fawse;
	*mic = fawse;

	if (!wt298->component)
		wetuwn -EINVAW;

	dapm = snd_soc_component_get_dapm(wt298->component);

	if (wt298->pdata.cbj_en) {
		wegmap_wead(wt298->wegmap, WT298_GET_HP_SENSE, &buf);
		*hp = buf & 0x80000000;
		if (*hp == wt298->is_hp_in)
			wetuwn -1;
		wt298->is_hp_in = *hp;
		if (*hp) {
			/* powew on HV,VEWF */
			wegmap_update_bits(wt298->wegmap,
				WT298_DC_GAIN, 0x200, 0x200);

			snd_soc_dapm_fowce_enabwe_pin(dapm, "HV");
			snd_soc_dapm_fowce_enabwe_pin(dapm, "VWEF");
			/* powew WDO1 */
			snd_soc_dapm_fowce_enabwe_pin(dapm, "WDO1");
			snd_soc_dapm_sync(dapm);

			wegmap_update_bits(wt298->wegmap,
				WT298_POWEW_CTWW1, 0x1001, 0);
			wegmap_update_bits(wt298->wegmap,
				WT298_POWEW_CTWW2, 0x4, 0x4);

			wegmap_wwite(wt298->wegmap, WT298_SET_MIC1, 0x24);
			msweep(50);

			wegmap_update_bits(wt298->wegmap,
				WT298_CBJ_CTWW1, 0xfcc0, 0xd400);
			msweep(300);
			wegmap_wead(wt298->wegmap, WT298_CBJ_CTWW2, &vaw);

			if (0x0070 == (vaw & 0x0070)) {
				*mic = twue;
			} ewse {
				wegmap_update_bits(wt298->wegmap,
					WT298_CBJ_CTWW1, 0xfcc0, 0xe400);
				msweep(300);
				wegmap_wead(wt298->wegmap,
					WT298_CBJ_CTWW2, &vaw);
				if (0x0070 == (vaw & 0x0070)) {
					*mic = twue;
				} ewse {
					*mic = fawse;
					wegmap_update_bits(wt298->wegmap,
						WT298_CBJ_CTWW1,
						0xfcc0, 0xc400);
				}
			}

			wegmap_update_bits(wt298->wegmap,
				WT298_DC_GAIN, 0x200, 0x0);

		} ewse {
			*mic = fawse;
			wegmap_wwite(wt298->wegmap, WT298_SET_MIC1, 0x20);
			wegmap_update_bits(wt298->wegmap,
				WT298_CBJ_CTWW1, 0x0400, 0x0000);
		}
	} ewse {
		wegmap_wead(wt298->wegmap, WT298_GET_HP_SENSE, &buf);
		*hp = buf & 0x80000000;
		wegmap_wead(wt298->wegmap, WT298_GET_MIC1_SENSE, &buf);
		*mic = buf & 0x80000000;
	}
	if (!*mic) {
		snd_soc_dapm_disabwe_pin(dapm, "HV");
		snd_soc_dapm_disabwe_pin(dapm, "VWEF");
	}
	if (!*hp)
		snd_soc_dapm_disabwe_pin(dapm, "WDO1");
	snd_soc_dapm_sync(dapm);

	pw_debug("*hp = %d *mic = %d\n", *hp, *mic);

	wetuwn 0;
}

static void wt298_jack_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt298_pwiv *wt298 =
		containew_of(wowk, stwuct wt298_pwiv, jack_detect_wowk.wowk);
	int status = 0;
	boow hp = fawse;
	boow mic = fawse;

	if (wt298_jack_detect(wt298, &hp, &mic) < 0)
		wetuwn;

	if (hp)
		status |= SND_JACK_HEADPHONE;

	if (mic)
		status |= SND_JACK_MICWOPHONE;

	snd_soc_jack_wepowt(wt298->jack, status,
		SND_JACK_MICWOPHONE | SND_JACK_HEADPHONE);
}

static int wt298_mic_detect(stwuct snd_soc_component *component,
			    stwuct snd_soc_jack *jack, void *data)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);

	wt298->jack = jack;

	if (jack) {
		/* Enabwe IWQ */
		if (wt298->jack->status & SND_JACK_HEADPHONE)
			snd_soc_dapm_fowce_enabwe_pin(dapm, "WDO1");
		if (wt298->jack->status & SND_JACK_MICWOPHONE) {
			snd_soc_dapm_fowce_enabwe_pin(dapm, "HV");
			snd_soc_dapm_fowce_enabwe_pin(dapm, "VWEF");
		}
		wegmap_update_bits(wt298->wegmap, WT298_IWQ_CTWW, 0x2, 0x2);
		/* Send an initiaw empty wepowt */
		snd_soc_jack_wepowt(wt298->jack, wt298->jack->status,
				    SND_JACK_MICWOPHONE | SND_JACK_HEADPHONE);
	} ewse {
		/* Disabwe IWQ */
		wegmap_update_bits(wt298->wegmap, WT298_IWQ_CTWW, 0x2, 0x0);
		snd_soc_dapm_disabwe_pin(dapm, "HV");
		snd_soc_dapm_disabwe_pin(dapm, "VWEF");
		snd_soc_dapm_disabwe_pin(dapm, "WDO1");
	}
	snd_soc_dapm_sync(dapm);

	wetuwn 0;
}

static int is_mcwk_mode(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);

	if (wt298->cwk_id == WT298_SCWK_S_MCWK)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -6350, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, 0, 1000, 0);

static const stwuct snd_kcontwow_new wt298_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("DAC0 Pwayback Vowume", WT298_DACW_GAIN,
			    WT298_DACW_GAIN, 0, 0x7f, 0, out_vow_twv),
	SOC_DOUBWE_W_TWV("ADC0 Captuwe Vowume", WT298_ADCW_GAIN,
			    WT298_ADCW_GAIN, 0, 0x7f, 0, out_vow_twv),
	SOC_SINGWE_TWV("AMIC Vowume", WT298_MIC_GAIN,
			    0, 0x3, 0, mic_vow_twv),
	SOC_DOUBWE_W("Speakew Pwayback Switch", WT298_SPOW_GAIN,
			    WT298_SPOW_GAIN, WT298_MUTE_SFT, 1, 1),
};

/* Digitaw Mixew */
static const stwuct snd_kcontwow_new wt298_fwont_mix[] = {
	SOC_DAPM_SINGWE("DAC Switch",  WT298_F_DAC_SWITCH,
			WT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGWE("WECMIX Switch", WT298_F_WECMIX_SWITCH,
			WT298_MUTE_SFT, 1, 1),
};

/* Anawog Input Mixew */
static const stwuct snd_kcontwow_new wt298_wec_mix[] = {
	SOC_DAPM_SINGWE("Mic1 Switch", WT298_WEC_MIC_SWITCH,
			WT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGWE("I2S Switch", WT298_WEC_I2S_SWITCH,
			WT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGWE("Wine1 Switch", WT298_WEC_WINE_SWITCH,
			WT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGWE("Beep Switch", WT298_WEC_BEEP_SWITCH,
			WT298_MUTE_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new spo_enabwe_contwow =
	SOC_DAPM_SINGWE("Switch", WT298_SET_PIN_SPK,
			WT298_SET_PIN_SFT, 1, 0);

static const stwuct snd_kcontwow_new hpow_enabwe_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT298_HPOW_GAIN,
			WT298_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new hpow_enabwe_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT298_HPOW_GAIN,
			WT298_MUTE_SFT, 1, 1);

/* ADC0 souwce */
static const chaw * const wt298_adc_swc[] = {
	"Mic", "WECMIX", "Dmic"
};

static const int wt298_adc_vawues[] = {
	0, 4, 5,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(
	wt298_adc0_enum, WT298_ADC0_MUX, WT298_ADC_SEW_SFT,
	WT298_ADC_SEW_MASK, wt298_adc_swc, wt298_adc_vawues);

static const stwuct snd_kcontwow_new wt298_adc0_mux =
	SOC_DAPM_ENUM("ADC 0 souwce", wt298_adc0_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(
	wt298_adc1_enum, WT298_ADC1_MUX, WT298_ADC_SEW_SFT,
	WT298_ADC_SEW_MASK, wt298_adc_swc, wt298_adc_vawues);

static const stwuct snd_kcontwow_new wt298_adc1_mux =
	SOC_DAPM_ENUM("ADC 1 souwce", wt298_adc1_enum);

static const chaw * const wt298_dac_swc[] = {
	"Fwont", "Suwwound"
};
/* HP-OUT souwce */
static SOC_ENUM_SINGWE_DECW(wt298_hpo_enum, WT298_HPO_MUX,
				0, wt298_dac_swc);

static const stwuct snd_kcontwow_new wt298_hpo_mux =
SOC_DAPM_ENUM("HPO souwce", wt298_hpo_enum);

/* SPK-OUT souwce */
static SOC_ENUM_SINGWE_DECW(wt298_spo_enum, WT298_SPK_MUX,
				0, wt298_dac_swc);

static const stwuct snd_kcontwow_new wt298_spo_mux =
SOC_DAPM_ENUM("SPO souwce", wt298_spo_enum);

static int wt298_spk_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_wwite(component,
			WT298_SPK_EAPD, WT298_SET_EAPD_HIGH);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_wwite(component,
			WT298_SPK_EAPD, WT298_SET_EAPD_WOW);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt298_set_dmic1_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_wwite(component, WT298_SET_PIN_DMIC1, 0x20);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_wwite(component, WT298_SET_PIN_DMIC1, 0);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt298_adc_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int nid;

	nid = (w->weg >> 20) & 0xff;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component,
			VEWB_CMD(AC_VEWB_SET_AMP_GAIN_MUTE, nid, 0),
			0x7080, 0x7000);
		 /* If MCWK doesn't exist, weset AD fiwtew */
		if (!(snd_soc_component_wead(component, WT298_VAD_CTWW) & 0x200)) {
			pw_info("NO MCWK\n");
			switch (nid) {
			case WT298_ADC_IN1:
				snd_soc_component_update_bits(component,
					WT298_D_FIWTEW_CTWW, 0x2, 0x2);
				mdeway(10);
				snd_soc_component_update_bits(component,
					WT298_D_FIWTEW_CTWW, 0x2, 0x0);
				bweak;
			case WT298_ADC_IN2:
				snd_soc_component_update_bits(component,
					WT298_D_FIWTEW_CTWW, 0x4, 0x4);
				mdeway(10);
				snd_soc_component_update_bits(component,
					WT298_D_FIWTEW_CTWW, 0x4, 0x0);
				bweak;
			}
		}
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component,
			VEWB_CMD(AC_VEWB_SET_AMP_GAIN_MUTE, nid, 0),
			0x7080, 0x7080);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt298_mic1_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		snd_soc_component_update_bits(component,
			WT298_A_BIAS_CTWW3, 0xc000, 0x8000);
		snd_soc_component_update_bits(component,
			WT298_A_BIAS_CTWW2, 0xc000, 0x8000);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component,
			WT298_A_BIAS_CTWW3, 0xc000, 0x0000);
		snd_soc_component_update_bits(component,
			WT298_A_BIAS_CTWW2, 0xc000, 0x0000);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt298_dapm_widgets[] = {

	SND_SOC_DAPM_SUPPWY_S("HV", 1, WT298_POWEW_CTWW1,
		12, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VWEF", WT298_POWEW_CTWW1,
		0, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("BG_MBIAS", 1, WT298_POWEW_CTWW2,
		1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("WDO1", 1, WT298_POWEW_CTWW2,
		2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("WDO2", 1, WT298_POWEW_CTWW2,
		3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("VWEF1", 1, WT298_POWEW_CTWW2,
		4, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("WV", 2, WT298_POWEW_CTWW1,
		13, 1, NUWW, 0),


	SND_SOC_DAPM_SUPPWY("MCWK MODE", WT298_PWW_CTWW1,
		5, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MIC1 Input Buffew", SND_SOC_NOPM,
		0, 0, wt298_mic1_event, SND_SOC_DAPM_PWE_PMU |
		SND_SOC_DAPM_POST_PMD),

	/* Input Wines */
	SND_SOC_DAPM_INPUT("DMIC1 Pin"),
	SND_SOC_DAPM_INPUT("DMIC2 Pin"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("WINE1"),
	SND_SOC_DAPM_INPUT("Beep"),

	/* DMIC */
	SND_SOC_DAPM_PGA_E("DMIC1", WT298_SET_POWEW(WT298_DMIC1), 0, 1,
		NUWW, 0, wt298_set_dmic1_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA("DMIC2", WT298_SET_POWEW(WT298_DMIC2), 0, 1,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DMIC Weceivew", SND_SOC_NOPM,
		0, 0, NUWW, 0),

	/* WEC Mixew */
	SND_SOC_DAPM_MIXEW("WECMIX", SND_SOC_NOPM, 0, 0,
		wt298_wec_mix, AWWAY_SIZE(wt298_wec_mix)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC 0", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC 1", NUWW, SND_SOC_NOPM, 0, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX_E("ADC 0 Mux", WT298_SET_POWEW(WT298_ADC_IN1), 0, 1,
		&wt298_adc0_mux, wt298_adc_event, SND_SOC_DAPM_PWE_PMD |
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("ADC 1 Mux", WT298_SET_POWEW(WT298_ADC_IN2), 0, 1,
		&wt298_adc1_mux, wt298_adc_event, SND_SOC_DAPM_PWE_PMD |
		SND_SOC_DAPM_POST_PMU),

	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIF1WX", "AIF1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2WX", "AIF2 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Captuwe", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("DAC 0", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC 1", NUWW, SND_SOC_NOPM, 0, 0),

	/* Output Mux */
	SND_SOC_DAPM_MUX("SPK Mux", SND_SOC_NOPM, 0, 0, &wt298_spo_mux),
	SND_SOC_DAPM_MUX("HPO Mux", SND_SOC_NOPM, 0, 0, &wt298_hpo_mux),

	SND_SOC_DAPM_SUPPWY("HP Powew", WT298_SET_PIN_HPO,
		WT298_SET_PIN_SFT, 0, NUWW, 0),

	/* Output Mixew */
	SND_SOC_DAPM_MIXEW("Fwont", WT298_SET_POWEW(WT298_DAC_OUT1), 0, 1,
			wt298_fwont_mix, AWWAY_SIZE(wt298_fwont_mix)),
	SND_SOC_DAPM_PGA("Suwwound", WT298_SET_POWEW(WT298_DAC_OUT2), 0, 1,
			NUWW, 0),

	/* Output Pga */
	SND_SOC_DAPM_SWITCH_E("SPO", SND_SOC_NOPM, 0, 0,
		&spo_enabwe_contwow, wt298_spk_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SWITCH("HPO W", SND_SOC_NOPM, 0, 0,
		&hpow_enabwe_contwow),
	SND_SOC_DAPM_SWITCH("HPO W", SND_SOC_NOPM, 0, 0,
		&hpow_enabwe_contwow),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("HPO Pin"),
	SND_SOC_DAPM_OUTPUT("SPDIF"),
};

static const stwuct snd_soc_dapm_woute wt298_dapm_woutes[] = {

	{"ADC 0", NUWW, "MCWK MODE", is_mcwk_mode},
	{"ADC 1", NUWW, "MCWK MODE", is_mcwk_mode},
	{"Fwont", NUWW, "MCWK MODE", is_mcwk_mode},
	{"Suwwound", NUWW, "MCWK MODE", is_mcwk_mode},

	{"HP Powew", NUWW, "WDO1"},
	{"HP Powew", NUWW, "WDO2"},
	{"HP Powew", NUWW, "WV"},
	{"HP Powew", NUWW, "VWEF1"},
	{"HP Powew", NUWW, "BG_MBIAS"},

	{"MIC1", NUWW, "WDO1"},
	{"MIC1", NUWW, "WDO2"},
	{"MIC1", NUWW, "HV"},
	{"MIC1", NUWW, "WV"},
	{"MIC1", NUWW, "VWEF"},
	{"MIC1", NUWW, "VWEF1"},
	{"MIC1", NUWW, "BG_MBIAS"},
	{"MIC1", NUWW, "MIC1 Input Buffew"},

	{"SPO", NUWW, "WDO1"},
	{"SPO", NUWW, "WDO2"},
	{"SPO", NUWW, "HV"},
	{"SPO", NUWW, "WV"},
	{"SPO", NUWW, "VWEF"},
	{"SPO", NUWW, "VWEF1"},
	{"SPO", NUWW, "BG_MBIAS"},

	{"DMIC1", NUWW, "DMIC1 Pin"},
	{"DMIC2", NUWW, "DMIC2 Pin"},
	{"DMIC1", NUWW, "DMIC Weceivew"},
	{"DMIC2", NUWW, "DMIC Weceivew"},

	{"WECMIX", "Beep Switch", "Beep"},
	{"WECMIX", "Wine1 Switch", "WINE1"},
	{"WECMIX", "Mic1 Switch", "MIC1"},

	{"ADC 0 Mux", "Dmic", "DMIC1"},
	{"ADC 0 Mux", "WECMIX", "WECMIX"},
	{"ADC 0 Mux", "Mic", "MIC1"},
	{"ADC 1 Mux", "Dmic", "DMIC2"},
	{"ADC 1 Mux", "WECMIX", "WECMIX"},
	{"ADC 1 Mux", "Mic", "MIC1"},

	{"ADC 0", NUWW, "ADC 0 Mux"},
	{"ADC 1", NUWW, "ADC 1 Mux"},

	{"AIF1TX", NUWW, "ADC 0"},
	{"AIF2TX", NUWW, "ADC 1"},

	{"DAC 0", NUWW, "AIF1WX"},
	{"DAC 1", NUWW, "AIF2WX"},

	{"Fwont", "DAC Switch", "DAC 0"},
	{"Fwont", "WECMIX Switch", "WECMIX"},

	{"Suwwound", NUWW, "DAC 1"},

	{"SPK Mux", "Fwont", "Fwont"},
	{"SPK Mux", "Suwwound", "Suwwound"},

	{"HPO Mux", "Fwont", "Fwont"},
	{"HPO Mux", "Suwwound", "Suwwound"},

	{"SPO", "Switch", "SPK Mux"},
	{"HPO W", "Switch", "HPO Mux"},
	{"HPO W", "Switch", "HPO Mux"},
	{"HPO W", NUWW, "HP Powew"},
	{"HPO W", NUWW, "HP Powew"},

	{"SPOW", NUWW, "SPO"},
	{"SPOW", NUWW, "SPO"},
	{"HPO Pin", NUWW, "HPO W"},
	{"HPO Pin", NUWW, "HPO W"},
};

static int wt298_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0;
	int d_wen_code;

	switch (pawams_wate(pawams)) {
	/* bit 14 0:48K 1:44.1K */
	case 44100:
	case 48000:
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted sampwe wate %d\n",
					pawams_wate(pawams));
		wetuwn -EINVAW;
	}
	switch (wt298->sys_cwk) {
	case 12288000:
	case 24576000:
		if (pawams_wate(pawams) != 48000) {
			dev_eww(component->dev, "Sys_cwk is not matched (%d %d)\n",
					pawams_wate(pawams), wt298->sys_cwk);
			wetuwn -EINVAW;
		}
		bweak;
	case 11289600:
	case 22579200:
		if (pawams_wate(pawams) != 44100) {
			dev_eww(component->dev, "Sys_cwk is not matched (%d %d)\n",
					pawams_wate(pawams), wt298->sys_cwk);
			wetuwn -EINVAW;
		}
		bweak;
	}

	if (pawams_channews(pawams) <= 16) {
		/* bit 3:0 Numbew of Channew */
		vaw |= (pawams_channews(pawams) - 1);
	} ewse {
		dev_eww(component->dev, "Unsuppowted channews %d\n",
					pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	switch (pawams_width(pawams)) {
	/* bit 6:4 Bits pew Sampwe */
	case 16:
		d_wen_code = 0;
		vaw |= (0x1 << 4);
		bweak;
	case 32:
		d_wen_code = 2;
		vaw |= (0x4 << 4);
		bweak;
	case 20:
		d_wen_code = 1;
		vaw |= (0x2 << 4);
		bweak;
	case 24:
		d_wen_code = 2;
		vaw |= (0x3 << 4);
		bweak;
	case 8:
		d_wen_code = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component,
		WT298_I2S_CTWW1, 0x0018, d_wen_code << 3);
	dev_dbg(component->dev, "fowmat vaw = 0x%x\n", vaw);

	snd_soc_component_update_bits(component, WT298_DAC_FOWMAT, 0x407f, vaw);
	snd_soc_component_update_bits(component, WT298_ADC_FOWMAT, 0x407f, vaw);

	wetuwn 0;
}

static int wt298_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x800, 0x800);
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x800, 0x0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x300, 0x0);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x300, 0x1 << 8);
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x300, 0x2 << 8);
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x300, 0x3 << 8);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	/* bit 15 Stweam Type 0:PCM 1:Non-PCM */
	snd_soc_component_update_bits(component, WT298_DAC_FOWMAT, 0x8000, 0);
	snd_soc_component_update_bits(component, WT298_ADC_FOWMAT, 0x8000, 0);

	wetuwn 0;
}

static int wt298_set_dai_syscwk(stwuct snd_soc_dai *dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "%s fweq=%d\n", __func__, fweq);

	if (WT298_SCWK_S_MCWK == cwk_id) {
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW2, 0x0100, 0x0);
		snd_soc_component_update_bits(component,
			WT298_PWW_CTWW1, 0x20, 0x20);
	} ewse {
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW2, 0x0100, 0x0100);
		snd_soc_component_update_bits(component,
			WT298_PWW_CTWW1, 0x20, 0x0);
	}

	switch (fweq) {
	case 19200000:
		if (WT298_SCWK_S_MCWK == cwk_id) {
			dev_eww(component->dev, "Shouwd not use MCWK\n");
			wetuwn -EINVAW;
		}
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW2, 0x40, 0x40);
		bweak;
	case 24000000:
		if (WT298_SCWK_S_MCWK == cwk_id) {
			dev_eww(component->dev, "Shouwd not use MCWK\n");
			wetuwn -EINVAW;
		}
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW2, 0x40, 0x0);
		bweak;
	case 12288000:
	case 11289600:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW2, 0x8, 0x0);
		snd_soc_component_update_bits(component,
			WT298_CWK_DIV, 0xfc1e, 0x0004);
		bweak;
	case 24576000:
	case 22579200:
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW2, 0x8, 0x8);
		snd_soc_component_update_bits(component,
			WT298_CWK_DIV, 0xfc1e, 0x5406);
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted system cwock\n");
		wetuwn -EINVAW;
	}

	wt298->sys_cwk = fweq;
	wt298->cwk_id = cwk_id;

	wetuwn 0;
}

static int wt298_set_bcwk_watio(stwuct snd_soc_dai *dai, unsigned int watio)
{
	stwuct snd_soc_component *component = dai->component;

	dev_dbg(component->dev, "%s watio=%d\n", __func__, watio);
	if (50 == watio)
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x1000, 0x1000);
	ewse
		snd_soc_component_update_bits(component,
			WT298_I2S_CTWW1, 0x1000, 0x0);


	wetuwn 0;
}

static int wt298_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (SND_SOC_BIAS_STANDBY ==
			snd_soc_component_get_bias_wevew(component)) {
			snd_soc_component_wwite(component,
				WT298_SET_AUDIO_POWEW, AC_PWWST_D0);
			snd_soc_component_update_bits(component, 0x0d, 0x200, 0x200);
			snd_soc_component_update_bits(component, 0x52, 0x80, 0x0);
			mdeway(20);
			snd_soc_component_update_bits(component, 0x0d, 0x200, 0x0);
			snd_soc_component_update_bits(component, 0x52, 0x80, 0x80);
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_wwite(component,
			WT298_SET_AUDIO_POWEW, AC_PWWST_D3);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static iwqwetuwn_t wt298_iwq(int iwq, void *data)
{
	stwuct wt298_pwiv *wt298 = data;
	boow hp = fawse;
	boow mic = fawse;
	int wet, status = 0;

	wet = wt298_jack_detect(wt298, &hp, &mic);

	/* Cweaw IWQ */
	wegmap_update_bits(wt298->wegmap, WT298_IWQ_CTWW, 0x1, 0x1);

	if (wet == 0) {
		if (hp)
			status |= SND_JACK_HEADPHONE;

		if (mic)
			status |= SND_JACK_MICWOPHONE;

		snd_soc_jack_wepowt(wt298->jack, status,
			SND_JACK_MICWOPHONE | SND_JACK_HEADPHONE);

		pm_wakeup_event(&wt298->i2c->dev, 300);
	}

	wetuwn IWQ_HANDWED;
}

static int wt298_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);

	wt298->component = component;
	INIT_DEWAYED_WOWK(&wt298->jack_detect_wowk, wt298_jack_detect_wowk);

	if (wt298->i2c->iwq)
		scheduwe_dewayed_wowk(&wt298->jack_detect_wowk,
				      msecs_to_jiffies(1250));
	wetuwn 0;
}

static void wt298_wemove(stwuct snd_soc_component *component)
{
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);

	cancew_dewayed_wowk_sync(&wt298->jack_detect_wowk);
	wt298->component = NUWW;
}

#ifdef CONFIG_PM
static int wt298_suspend(stwuct snd_soc_component *component)
{
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);

	wt298->is_hp_in = -1;
	wegcache_cache_onwy(wt298->wegmap, twue);
	wegcache_mawk_diwty(wt298->wegmap);

	wetuwn 0;
}

static int wt298_wesume(stwuct snd_soc_component *component)
{
	stwuct wt298_pwiv *wt298 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt298->wegmap, fawse);
	wt298_index_sync(component);
	wegcache_sync(wt298->wegmap);

	wetuwn 0;
}
#ewse
#define wt298_suspend NUWW
#define wt298_wesume NUWW
#endif

#define WT298_STEWEO_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)
#define WT298_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt298_aif_dai_ops = {
	.hw_pawams = wt298_hw_pawams,
	.set_fmt = wt298_set_dai_fmt,
	.set_syscwk = wt298_set_dai_syscwk,
	.set_bcwk_watio = wt298_set_bcwk_watio,
};

static stwuct snd_soc_dai_dwivew wt298_dai[] = {
	{
		.name = "wt298-aif1",
		.id = WT298_AIF1,
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT298_STEWEO_WATES,
			.fowmats = WT298_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT298_STEWEO_WATES,
			.fowmats = WT298_FOWMATS,
		},
		.ops = &wt298_aif_dai_ops,
		.symmetwic_wate = 1,
	},
	{
		.name = "wt298-aif2",
		.id = WT298_AIF2,
		.pwayback = {
			.stweam_name = "AIF2 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT298_STEWEO_WATES,
			.fowmats = WT298_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF2 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT298_STEWEO_WATES,
			.fowmats = WT298_FOWMATS,
		},
		.ops = &wt298_aif_dai_ops,
		.symmetwic_wate = 1,
	},

};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt298 = {
	.pwobe			= wt298_pwobe,
	.wemove			= wt298_wemove,
	.suspend		= wt298_suspend,
	.wesume			= wt298_wesume,
	.set_bias_wevew		= wt298_set_bias_wevew,
	.set_jack		= wt298_mic_detect,
	.contwows		= wt298_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wt298_snd_contwows),
	.dapm_widgets		= wt298_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt298_dapm_widgets),
	.dapm_woutes		= wt298_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt298_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt298_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.max_wegistew = 0x02370100,
	.vowatiwe_weg = wt298_vowatiwe_wegistew,
	.weadabwe_weg = wt298_weadabwe_wegistew,
	.weg_wwite = ww6347a_hw_wwite,
	.weg_wead = ww6347a_hw_wead,
	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = wt298_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt298_weg),
};

static const stwuct i2c_device_id wt298_i2c_id[] = {
	{"wt298", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wt298_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt298_acpi_match[] = {
	{ "INT343A", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, wt298_acpi_match);
#endif

static const stwuct dmi_system_id fowce_combo_jack_tabwe[] = {
	{
		.ident = "Intew Bwoxton P",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowp"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Bwoxton P")
		}
	},
	{
		.ident = "Intew Gemini Wake",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowp"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Geminiwake")
		}
	},
	{
		.ident = "Intew Kabywake W WVP",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Kabywake Cwient pwatfowm")
		}
	},
	{ }
};

static int wt298_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt298_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	stwuct wt298_pwiv *wt298;
	stwuct device *dev = &i2c->dev;
	const stwuct acpi_device_id *acpiid;
	int i, wet;

	wt298 = devm_kzawwoc(&i2c->dev,	sizeof(*wt298),
				GFP_KEWNEW);
	if (NUWW == wt298)
		wetuwn -ENOMEM;

	wt298->wegmap = devm_wegmap_init(&i2c->dev, NUWW, i2c, &wt298_wegmap);
	if (IS_EWW(wt298->wegmap)) {
		wet = PTW_EWW(wt298->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wegmap_wead(wt298->wegmap,
		WT298_GET_PAWAM(AC_NODE_WOOT, AC_PAW_VENDOW_ID), &wet);
	if (wet != WT298_VENDOW_ID) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %#x is not wt298\n", wet);
		wetuwn -ENODEV;
	}

	wt298->index_cache = devm_kmemdup(&i2c->dev, wt298_index_def,
					  sizeof(wt298_index_def), GFP_KEWNEW);
	if (!wt298->index_cache)
		wetuwn -ENOMEM;

	wt298->index_cache_size = INDEX_CACHE_SIZE;
	wt298->i2c = i2c;
	i2c_set_cwientdata(i2c, wt298);

	/* westowe codec defauwt */
	fow (i = 0; i < INDEX_CACHE_SIZE; i++)
		wegmap_wwite(wt298->wegmap, wt298->index_cache[i].weg,
				wt298->index_cache[i].def);
	fow (i = 0; i < AWWAY_SIZE(wt298_weg); i++)
		wegmap_wwite(wt298->wegmap, wt298_weg[i].weg,
				wt298_weg[i].def);

	if (pdata)
		wt298->pdata = *pdata;

	/* enabwe jack combo mode on suppowted devices */
	acpiid = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (acpiid && acpiid->dwivew_data) {
		wt298->pdata = *(stwuct wt298_pwatfowm_data *)
				acpiid->dwivew_data;
	}

	if (dmi_check_system(fowce_combo_jack_tabwe)) {
		wt298->pdata.cbj_en = twue;
		wt298->pdata.gpio2_en = fawse;
	}

	/* VWEF Chawging */
	wegmap_update_bits(wt298->wegmap, 0x04, 0x80, 0x80);
	wegmap_update_bits(wt298->wegmap, 0x1b, 0x860, 0x860);
	/* Vwef2 */
	wegmap_update_bits(wt298->wegmap, 0x08, 0x20, 0x20);

	wegmap_wwite(wt298->wegmap, WT298_SET_AUDIO_POWEW, AC_PWWST_D3);

	fow (i = 0; i < WT298_POWEW_WEG_WEN; i++)
		wegmap_wwite(wt298->wegmap,
			WT298_SET_POWEW(wt298_suppowt_powew_contwows[i]),
			AC_PWWST_D1);

	if (!wt298->pdata.cbj_en) {
		wegmap_wwite(wt298->wegmap, WT298_CBJ_CTWW2, 0x0000);
		wegmap_wwite(wt298->wegmap, WT298_MIC1_DET_CTWW, 0x0816);
		wegmap_update_bits(wt298->wegmap,
					WT298_CBJ_CTWW1, 0xf000, 0xb000);
	} ewse {
		wegmap_update_bits(wt298->wegmap,
					WT298_CBJ_CTWW1, 0xf000, 0x5000);
	}

	mdeway(10);

	if (!wt298->pdata.gpio2_en)
		wegmap_wwite(wt298->wegmap, WT298_SET_DMIC2_DEFAUWT, 0x40);
	ewse
		wegmap_wwite(wt298->wegmap, WT298_SET_DMIC2_DEFAUWT, 0);

	mdeway(10);

	wegmap_wwite(wt298->wegmap, WT298_MISC_CTWW1, 0x0000);
	wegmap_update_bits(wt298->wegmap,
				WT298_WIND_FIWTEW_CTWW, 0x0082, 0x0082);

	wegmap_wwite(wt298->wegmap, WT298_UNSOWICITED_INWINE_CMD, 0x81);
	wegmap_wwite(wt298->wegmap, WT298_UNSOWICITED_HP_OUT, 0x82);
	wegmap_wwite(wt298->wegmap, WT298_UNSOWICITED_MIC1, 0x84);
	wegmap_update_bits(wt298->wegmap, WT298_IWQ_FWAG_CTWW, 0x2, 0x2);

	wt298->is_hp_in = -1;

	if (wt298->i2c->iwq) {
		wet = wequest_thweaded_iwq(wt298->i2c->iwq, NUWW, wt298_iwq,
			IWQF_TWIGGEW_HIGH | IWQF_ONESHOT, "wt298", wt298);
		if (wet != 0) {
			dev_eww(&i2c->dev,
				"Faiwed to weguest IWQ: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				     &soc_component_dev_wt298,
				     wt298_dai, AWWAY_SIZE(wt298_dai));

	wetuwn wet;
}

static void wt298_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wt298_pwiv *wt298 = i2c_get_cwientdata(i2c);

	if (i2c->iwq)
		fwee_iwq(i2c->iwq, wt298);
}


static stwuct i2c_dwivew wt298_i2c_dwivew = {
	.dwivew = {
		   .name = "wt298",
		   .acpi_match_tabwe = ACPI_PTW(wt298_acpi_match),
		   },
	.pwobe = wt298_i2c_pwobe,
	.wemove = wt298_i2c_wemove,
	.id_tabwe = wt298_i2c_id,
};

moduwe_i2c_dwivew(wt298_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT298 dwivew");
MODUWE_AUTHOW("Bawd Wiao <bawdwiao@weawtek.com>");
MODUWE_WICENSE("GPW");
