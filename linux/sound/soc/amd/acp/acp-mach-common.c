// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021, 2023 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
//	    Vijendaw Mukunda <Vijendaw.Mukunda@amd.com>
//

/*
 * Machine Dwivew Intewface fow ACP HW bwock
 */

#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/soc.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>

#incwude "../../codecs/wt5682.h"
#incwude "../../codecs/wt1019.h"
#incwude "../../codecs/wt5682s.h"
#incwude "../../codecs/nau8825.h"
#incwude "../../codecs/nau8821.h"
#incwude "acp-mach.h"

#define PCO_PWAT_CWK 48000000
#define WT5682_PWW_FWEQ (48000 * 512)
#define DUAW_CHANNEW	2
#define FOUW_CHANNEW	4
#define NAU8821_CODEC_DAI	"nau8821-hifi"
#define NAU8821_BCWK		1536000
#define NAU8821_FWEQ_OUT	12288000
#define MAX98388_CODEC_DAI	"max98388-aif1"

#define TDM_MODE_ENABWE 1

const stwuct dmi_system_id acp_quiwk_tabwe[] = {
	{
		/* Googwe skywim pwoto-0 */
		.matches = {
			DMI_EXACT_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Skywim"),
		},
		.dwivew_data = (void *)TDM_MODE_ENABWE,
	},
	{}
};
EXPOWT_SYMBOW_GPW(acp_quiwk_tabwe);

static const unsigned int channews[] = {
	DUAW_CHANNEW,
};

static const unsigned int wates[] = {
	48000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
	.count = AWWAY_SIZE(wates),
	.wist  = wates,
	.mask = 0,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
	.count = AWWAY_SIZE(channews),
	.wist = channews,
	.mask = 0,
};

static int acp_cwk_enabwe(stwuct acp_cawd_dwvdata *dwvdata,
			  unsigned int swate, unsigned int bcwk_watio)
{
	cwk_set_wate(dwvdata->wcwk, swate);
	cwk_set_wate(dwvdata->bcwk, swate * bcwk_watio);

	wetuwn cwk_pwepawe_enabwe(dwvdata->wcwk);
}

/* Decwawe WT5682 codec components */
SND_SOC_DAIWINK_DEF(wt5682,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10EC5682:00", "wt5682-aif1")));

static stwuct snd_soc_jack wt5682_jack;
static stwuct snd_soc_jack_pin wt5682_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static const stwuct snd_kcontwow_new wt5682_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const stwuct snd_soc_dapm_widget wt5682_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute wt5682_map[] = {
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "IN1P", NUWW, "Headset Mic" },
};

/* Define cawd ops fow WT5682 CODEC */
static int acp_cawd_wt5682_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	int wet;

	dev_info(wtd->dev, "codec dai name = %s\n", codec_dai->name);

	if (dwvdata->hs_codec_id != WT5682)
		wetuwn -EINVAW;

	dwvdata->wcwk = cwk_get(component->dev, "wt5682-dai-wcwk");
	dwvdata->bcwk = cwk_get(component->dev, "wt5682-dai-bcwk");

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, wt5682_widgets,
					AWWAY_SIZE(wt5682_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add widget dapm contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, wt5682_contwows,
					AWWAY_SIZE(wt5682_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_WINEOUT |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 &wt5682_jack,
					 wt5682_jack_pins,
					 AWWAY_SIZE(wt5682_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "HP jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(wt5682_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(wt5682_jack.jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(wt5682_jack.jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(wt5682_jack.jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wet = snd_soc_component_set_jack(component, &wt5682_jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, wt5682_map, AWWAY_SIZE(wt5682_map));
}

static int acp_cawd_hs_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;
	unsigned int fmt;

	if (dwvdata->tdm_mode)
		fmt = SND_SOC_DAIFMT_DSP_A;
	ewse
		fmt = SND_SOC_DAIFMT_I2S;

	if (dwvdata->soc_mcwk)
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	ewse
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBP_CFP;

	wet =  snd_soc_dai_set_fmt(codec_dai, fmt);
	if (wet < 0) {
		dev_eww(wtd->cawd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				      &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &constwaints_wates);

	wetuwn wet;
}

static void acp_cawd_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;

	if (!dwvdata->soc_mcwk)
		cwk_disabwe_unpwepawe(dwvdata->wcwk);
}

static int acp_cawd_wt5682_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;
	unsigned int fmt, swate, ch, fowmat;

	swate = pawams_wate(pawams);
	ch = pawams_channews(pawams);
	fowmat = pawams_physicaw_width(pawams);

	if (dwvdata->tdm_mode)
		fmt = SND_SOC_DAIFMT_DSP_A;
	ewse
		fmt = SND_SOC_DAIFMT_I2S;

	if (dwvdata->soc_mcwk)
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	ewse
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBP_CFP;

	wet = snd_soc_dai_set_fmt(cpu_dai, fmt);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(wtd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	wet =  snd_soc_dai_set_fmt(codec_dai, fmt);
	if (wet < 0) {
		dev_eww(wtd->cawd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode) {
		/**
		 * As codec suppowts swot 0 and swot 1 fow pwayback and captuwe.
		 */
		wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0x3, 0x3, 8, 16);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(wtd->dev, "set TDM swot eww: %d\n", wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x3, 0x3, 8, 16);
		if (wet < 0) {
			dev_wawn(wtd->dev, "set TDM swot eww:%d\n", wet);
			wetuwn wet;
		}
	}

	wet = snd_soc_dai_set_pww(codec_dai, WT5682_PWW2, WT5682_PWW2_S_MCWK,
				  PCO_PWAT_CWK, WT5682_PWW_FWEQ);
	if (wet < 0) {
		dev_eww(wtd->dev, "Faiwed to set codec PWW: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, WT5682_SCWK_S_PWW2,
				     WT5682_PWW_FWEQ, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "Faiwed to set codec SYSCWK: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode) {
		wet = snd_soc_dai_set_pww(codec_dai, WT5682S_PWW1, WT5682S_PWW_S_BCWK1,
					  6144000, 49152000);
		if (wet < 0) {
			dev_eww(wtd->dev, "Faiwed to set codec PWW: %d\n", wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_syscwk(codec_dai, WT5682S_SCWK_S_PWW1,
					     49152000, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(wtd->dev, "Faiwed to set codec SYSCWK: %d\n", wet);
			wetuwn wet;
		}
	}

	/* Set tdm/i2s1 mastew bcwk watio */
	wet = snd_soc_dai_set_bcwk_watio(codec_dai, ch * fowmat);
	if (wet < 0) {
		dev_eww(wtd->dev, "Faiwed to set wt5682 tdm bcwk watio: %d\n", wet);
		wetuwn wet;
	}

	if (!dwvdata->soc_mcwk) {
		wet = acp_cwk_enabwe(dwvdata, swate, ch * fowmat);
		if (wet < 0) {
			dev_eww(wtd->cawd->dev, "Faiwed to enabwe HS cwk: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops acp_cawd_wt5682_ops = {
	.stawtup = acp_cawd_hs_stawtup,
	.shutdown = acp_cawd_shutdown,
	.hw_pawams = acp_cawd_wt5682_hw_pawams,
};

/* Define WT5682S CODEC component*/
SND_SOC_DAIWINK_DEF(wt5682s,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-WTW5682:00", "wt5682s-aif1")));

static stwuct snd_soc_jack wt5682s_jack;
static stwuct snd_soc_jack_pin wt5682s_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static const stwuct snd_kcontwow_new wt5682s_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const stwuct snd_soc_dapm_widget wt5682s_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute wt5682s_map[] = {
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "IN1P", NUWW, "Headset Mic" },
};

static int acp_cawd_wt5682s_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	int wet;

	dev_info(wtd->dev, "codec dai name = %s\n", codec_dai->name);

	if (dwvdata->hs_codec_id != WT5682S)
		wetuwn -EINVAW;

	if (!dwvdata->soc_mcwk) {
		dwvdata->wcwk = cwk_get(component->dev, "wt5682-dai-wcwk");
		dwvdata->bcwk = cwk_get(component->dev, "wt5682-dai-bcwk");
	}

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, wt5682s_widgets,
					AWWAY_SIZE(wt5682s_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add widget dapm contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, wt5682s_contwows,
					AWWAY_SIZE(wt5682s_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_WINEOUT |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 &wt5682s_jack,
					 wt5682s_jack_pins,
					 AWWAY_SIZE(wt5682s_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "HP jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(wt5682s_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(wt5682s_jack.jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(wt5682s_jack.jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(wt5682s_jack.jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wet = snd_soc_component_set_jack(component, &wt5682s_jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, wt5682s_map, AWWAY_SIZE(wt5682s_map));
}

static int acp_cawd_wt5682s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;
	unsigned int fmt, swate, ch, fowmat;

	swate = pawams_wate(pawams);
	ch = pawams_channews(pawams);
	fowmat = pawams_physicaw_width(pawams);

	if (dwvdata->tdm_mode)
		fmt = SND_SOC_DAIFMT_DSP_A;
	ewse
		fmt = SND_SOC_DAIFMT_I2S;

	if (dwvdata->soc_mcwk)
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	ewse
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBP_CFP;

	wet = snd_soc_dai_set_fmt(cpu_dai, fmt);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(wtd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	wet =  snd_soc_dai_set_fmt(codec_dai, fmt);
	if (wet < 0) {
		dev_eww(wtd->cawd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode) {
		/**
		 * As codec suppowts swot 0 and swot 1 fow pwayback and captuwe.
		 */
		wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0x3, 0x3, 8, 16);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(wtd->dev, "set TDM swot eww: %d\n", wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x3, 0x3, 8, 16);
		if (wet < 0) {
			dev_wawn(wtd->dev, "set TDM swot eww:%d\n", wet);
			wetuwn wet;
		}
	}

	wet = snd_soc_dai_set_pww(codec_dai, WT5682S_PWW2, WT5682S_PWW_S_MCWK,
				  PCO_PWAT_CWK, WT5682_PWW_FWEQ);
	if (wet < 0) {
		dev_eww(wtd->dev, "Faiwed to set codec PWW: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, WT5682S_SCWK_S_PWW2,
				     WT5682_PWW_FWEQ, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "Faiwed to set codec SYSCWK: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode) {
		wet = snd_soc_dai_set_pww(codec_dai, WT5682S_PWW1, WT5682S_PWW_S_BCWK1,
					  6144000, 49152000);
		if (wet < 0) {
			dev_eww(wtd->dev, "Faiwed to set codec PWW: %d\n", wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_syscwk(codec_dai, WT5682S_SCWK_S_PWW1,
					     49152000, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(wtd->dev, "Faiwed to set codec SYSCWK: %d\n", wet);
			wetuwn wet;
		}
	}

	/* Set tdm/i2s1 mastew bcwk watio */
	wet = snd_soc_dai_set_bcwk_watio(codec_dai, ch * fowmat);
	if (wet < 0) {
		dev_eww(wtd->dev, "Faiwed to set wt5682 tdm bcwk watio: %d\n", wet);
		wetuwn wet;
	}

	cwk_set_wate(dwvdata->wcwk, swate);
	cwk_set_wate(dwvdata->bcwk, swate * ch * fowmat);
	if (!dwvdata->soc_mcwk) {
		wet = acp_cwk_enabwe(dwvdata, swate, ch * fowmat);
		if (wet < 0) {
			dev_eww(wtd->cawd->dev, "Faiwed to enabwe HS cwk: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops acp_cawd_wt5682s_ops = {
	.stawtup = acp_cawd_hs_stawtup,
	.hw_pawams = acp_cawd_wt5682s_hw_pawams,
};

static const unsigned int dmic_channews[] = {
	DUAW_CHANNEW, FOUW_CHANNEW,
};

static const stwuct snd_pcm_hw_constwaint_wist dmic_constwaints_channews = {
	.count = AWWAY_SIZE(dmic_channews),
	.wist = dmic_channews,
	.mask = 0,
};

static int acp_cawd_dmic_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &dmic_constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	wetuwn 0;
}

static const stwuct snd_soc_ops acp_cawd_dmic_ops = {
	.stawtup = acp_cawd_dmic_stawtup,
};

/* Decwawe WT1019 codec components */
SND_SOC_DAIWINK_DEF(wt1019,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10EC1019:00", "wt1019-aif"),
			  COMP_CODEC("i2c-10EC1019:01", "wt1019-aif")));

static const stwuct snd_kcontwow_new wt1019_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
};

static const stwuct snd_soc_dapm_widget wt1019_widgets[] = {
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute wt1019_map_ww[] = {
	{ "Weft Spk", NUWW, "Weft SPO" },
	{ "Wight Spk", NUWW, "Wight SPO" },
};

static stwuct snd_soc_codec_conf wt1019_conf[] = {
	{
		 .dwc = COMP_CODEC_CONF("i2c-10EC1019:01"),
		 .name_pwefix = "Weft",
	},
	{
		 .dwc = COMP_CODEC_CONF("i2c-10EC1019:00"),
		 .name_pwefix = "Wight",
	},
};

static int acp_cawd_wt1019_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	int wet;

	if (dwvdata->amp_codec_id != WT1019)
		wetuwn -EINVAW;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, wt1019_widgets,
					AWWAY_SIZE(wt1019_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add widget dapm contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, wt1019_contwows,
					AWWAY_SIZE(wt1019_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, wt1019_map_ww,
				       AWWAY_SIZE(wt1019_map_ww));
}

static int acp_cawd_wt1019_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int i, wet = 0;
	unsigned int fmt, swate, ch, fowmat;

	swate = pawams_wate(pawams);
	ch = pawams_channews(pawams);
	fowmat = pawams_physicaw_width(pawams);

	if (dwvdata->amp_codec_id != WT1019)
		wetuwn -EINVAW;

	if (dwvdata->tdm_mode)
		fmt = SND_SOC_DAIFMT_DSP_A;
	ewse
		fmt = SND_SOC_DAIFMT_I2S;

	if (dwvdata->soc_mcwk)
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	ewse
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBP_CFP;

	wet = snd_soc_dai_set_fmt(cpu_dai, fmt);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(wtd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode) {
		/**
		 * As codec suppowts swot 2 and swot 3 fow pwayback.
		 */
		wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0xC, 0, 8, 16);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(wtd->dev, "set TDM swot eww: %d\n", wet);
			wetuwn wet;
		}
	}

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		if (stwcmp(codec_dai->name, "wt1019-aif"))
			continue;

		if (dwvdata->tdm_mode)
			wet = snd_soc_dai_set_pww(codec_dai, 0, WT1019_PWW_S_BCWK,
						  TDM_CHANNEWS * fowmat * swate, 256 * swate);
		ewse
			wet = snd_soc_dai_set_pww(codec_dai, 0, WT1019_PWW_S_BCWK,
						  ch * fowmat * swate, 256 * swate);

		if (wet < 0)
			wetuwn wet;

		wet = snd_soc_dai_set_syscwk(codec_dai, WT1019_SCWK_S_PWW,
					     256 * swate, SND_SOC_CWOCK_IN);
		if (wet < 0)
			wetuwn wet;

		if (dwvdata->tdm_mode) {
			wet = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_DSP_A
							| SND_SOC_DAIFMT_NB_NF);
			if (wet < 0) {
				dev_eww(wtd->cawd->dev, "Faiwed to set dai fmt: %d\n", wet);
				wetuwn wet;
			}

			/**
			 * As codec suppowts swot 2 fow weft channew pwayback.
			 */
			if (!stwcmp(codec_dai->component->name, "i2c-10EC1019:00")) {
				wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x4, 0x4, 8, 16);
				if (wet < 0)
					bweak;
			}

			/**
			 * As codec suppowts swot 3 fow wight channew pwayback.
			 */
			if (!stwcmp(codec_dai->component->name, "i2c-10EC1019:01")) {
				wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x8, 0x8, 8, 16);
				if (wet < 0)
					bweak;
			}
		}
	}

	if (!dwvdata->soc_mcwk) {
		wet = acp_cwk_enabwe(dwvdata, swate, ch * fowmat);
		if (wet < 0) {
			dev_eww(wtd->cawd->dev, "Faiwed to enabwe AMP cwk: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int acp_cawd_amp_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				      &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &constwaints_wates);

	wetuwn 0;
}

static const stwuct snd_soc_ops acp_cawd_wt1019_ops = {
	.stawtup = acp_cawd_amp_stawtup,
	.shutdown = acp_cawd_shutdown,
	.hw_pawams = acp_cawd_wt1019_hw_pawams,
};

/* Decwawe Maxim codec components */
SND_SOC_DAIWINK_DEF(max98360a,
	DAIWINK_COMP_AWWAY(COMP_CODEC("MX98360A:00", "HiFi")));

static const stwuct snd_kcontwow_new max98360a_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Spk"),
};

static const stwuct snd_soc_dapm_widget max98360a_widgets[] = {
	SND_SOC_DAPM_SPK("Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute max98360a_map[] = {
	{"Spk", NUWW, "Speakew"},
};

static int acp_cawd_maxim_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	int wet;

	if (dwvdata->amp_codec_id != MAX98360A)
		wetuwn -EINVAW;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, max98360a_widgets,
					AWWAY_SIZE(max98360a_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add widget dapm contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, max98360a_contwows,
					AWWAY_SIZE(max98360a_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, max98360a_map,
				       AWWAY_SIZE(max98360a_map));
}

static int acp_cawd_maxim_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	unsigned int fmt, swate, ch, fowmat;
	int wet;

	swate = pawams_wate(pawams);
	ch = pawams_channews(pawams);
	fowmat = pawams_physicaw_width(pawams);

	if (dwvdata->tdm_mode)
		fmt = SND_SOC_DAIFMT_DSP_A;
	ewse
		fmt = SND_SOC_DAIFMT_I2S;

	if (dwvdata->soc_mcwk)
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	ewse
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBP_CFP;

	wet = snd_soc_dai_set_fmt(cpu_dai, fmt);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(wtd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode) {
		/**
		 * As codec suppowts swot 2 and swot 3 fow pwayback.
		 */
		wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0xC, 0, 8, 16);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(wtd->dev, "set TDM swot eww: %d\n", wet);
			wetuwn wet;
		}
	}

	if (!dwvdata->soc_mcwk) {
		wet = acp_cwk_enabwe(dwvdata, swate, ch * fowmat);
		if (wet < 0) {
			dev_eww(wtd->cawd->dev, "Faiwed to enabwe AMP cwk: %d\n", wet);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static const stwuct snd_soc_ops acp_cawd_maxim_ops = {
	.stawtup = acp_cawd_amp_stawtup,
	.shutdown = acp_cawd_shutdown,
	.hw_pawams = acp_cawd_maxim_hw_pawams,
};

SND_SOC_DAIWINK_DEF(max98388,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-ADS8388:00", "max98388-aif1"),
				       COMP_CODEC("i2c-ADS8388:01", "max98388-aif1")));

static const stwuct snd_kcontwow_new max98388_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
};

static const stwuct snd_soc_dapm_widget max98388_widgets[] = {
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute max98388_map[] = {
	{ "Weft Spk", NUWW, "Weft BE_OUT" },
	{ "Wight Spk", NUWW, "Wight BE_OUT" },
};

static stwuct snd_soc_codec_conf max98388_conf[] = {
	{
		.dwc = COMP_CODEC_CONF("i2c-ADS8388:00"),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF("i2c-ADS8388:01"),
		.name_pwefix = "Wight",
	},
};

static const unsigned int max98388_fowmat[] = {16};

static stwuct snd_pcm_hw_constwaint_wist constwaints_sampwe_bits_max = {
	.wist = max98388_fowmat,
	.count = AWWAY_SIZE(max98388_fowmat),
};

static int acp_cawd_max98388_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_SAMPWE_BITS,
				   &constwaints_sampwe_bits_max);

	wetuwn 0;
}

static int acp_cawd_max98388_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	int wet;

	if (dwvdata->amp_codec_id != MAX98388)
		wetuwn -EINVAW;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, max98388_widgets,
					AWWAY_SIZE(max98388_widgets));

	if (wet) {
		dev_eww(wtd->dev, "unabwe to add widget dapm contwows, wet %d\n", wet);
		/* Don't need to add woutes if widget addition faiwed */
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, max98388_contwows,
					AWWAY_SIZE(max98388_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, max98388_map,
				       AWWAY_SIZE(max98388_map));
}

static int acp_max98388_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *codec_dai =
			snd_soc_cawd_get_codec_dai(cawd,
						   MAX98388_CODEC_DAI);
	int wet;

	wet = snd_soc_dai_set_fmt(codec_dai,
				  SND_SOC_DAIFMT_CBS_CFS | SND_SOC_DAIFMT_I2S |
				  SND_SOC_DAIFMT_NB_NF);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static const stwuct snd_soc_ops acp_max98388_ops = {
	.stawtup = acp_cawd_max98388_stawtup,
	.hw_pawams = acp_max98388_hw_pawams,
};

/* Decwawe nau8825 codec components */
SND_SOC_DAIWINK_DEF(nau8825,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10508825:00", "nau8825-hifi")));

static stwuct snd_soc_jack nau8825_jack;
static stwuct snd_soc_jack_pin nau8825_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static const stwuct snd_kcontwow_new nau8825_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const stwuct snd_soc_dapm_widget nau8825_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute nau8825_map[] = {
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },
};

static int acp_cawd_nau8825_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	int wet;

	dev_info(wtd->dev, "codec dai name = %s\n", codec_dai->name);

	if (dwvdata->hs_codec_id != NAU8825)
		wetuwn -EINVAW;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, nau8825_widgets,
					AWWAY_SIZE(nau8825_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add widget dapm contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, nau8825_contwows,
					AWWAY_SIZE(nau8825_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_WINEOUT |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 &nau8825_jack,
					 nau8825_jack_pins,
					 AWWAY_SIZE(nau8825_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "HP jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(nau8825_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(nau8825_jack.jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(nau8825_jack.jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(nau8825_jack.jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wet = snd_soc_component_set_jack(component, &nau8825_jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, nau8825_map, AWWAY_SIZE(nau8825_map));
}

static int acp_nau8825_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;
	unsigned int fmt;

	wet = snd_soc_dai_set_syscwk(codec_dai, NAU8825_CWK_FWW_FS,
				     (48000 * 256), SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(wtd->dev, "snd_soc_dai_set_syscwk eww = %d\n", wet);

	wet = snd_soc_dai_set_pww(codec_dai, 0, 0, pawams_wate(pawams),
				  pawams_wate(pawams) * 256);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set FWW: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode)
		fmt = SND_SOC_DAIFMT_DSP_A;
	ewse
		fmt = SND_SOC_DAIFMT_I2S;

	if (dwvdata->soc_mcwk)
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	ewse
		fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBP_CFP;

	wet = snd_soc_dai_set_fmt(cpu_dai, fmt);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(wtd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	wet =  snd_soc_dai_set_fmt(codec_dai, fmt);
	if (wet < 0) {
		dev_eww(wtd->cawd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->tdm_mode) {
		/**
		 * As codec suppowts swot 4 and swot 5 fow pwayback and swot 6 fow captuwe.
		 */
		wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0x30, 0xC0, 8, 16);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(wtd->dev, "set TDM swot eww: %d\n", wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x40, 0x30, 8, 16);
		if (wet < 0) {
			dev_wawn(wtd->dev, "set TDM swot eww:%d\n", wet);
			wetuwn wet;
		}
	}
	wetuwn wet;
}

static int acp_nau8825_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.channews_max = 2;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);

	wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE;
	snd_pcm_hw_constwaint_wist(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);
	wetuwn 0;
}

static const stwuct snd_soc_ops acp_cawd_nau8825_ops = {
	.stawtup =  acp_nau8825_stawtup,
	.hw_pawams = acp_nau8825_hw_pawams,
};

static int pwatfowm_cwock_contwow(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct snd_soc_dai *codec_dai;
	int wet = 0;

	codec_dai = snd_soc_cawd_get_codec_dai(cawd, NAU8821_CODEC_DAI);
	if (!codec_dai) {
		dev_eww(cawd->dev, "Codec dai not found\n");
		wetuwn -EIO;
	}

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		wet = snd_soc_dai_set_syscwk(codec_dai, NAU8821_CWK_INTEWNAW,
					     0, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(cawd->dev, "set syscwk eww = %d\n", wet);
			wetuwn -EIO;
		}
	} ewse {
		wet = snd_soc_dai_set_syscwk(codec_dai, NAU8821_CWK_FWW_BWK, 0,
					     SND_SOC_CWOCK_IN);
		if (wet < 0)
			dev_eww(codec_dai->dev, "can't set FS cwock %d\n", wet);
		wet = snd_soc_dai_set_pww(codec_dai, 0, 0, NAU8821_BCWK,
					  NAU8821_FWEQ_OUT);
		if (wet < 0)
			dev_eww(codec_dai->dev, "can't set FWW: %d\n", wet);
	}
	wetuwn wet;
}

static stwuct snd_soc_jack nau8821_jack;
static stwuct snd_soc_jack_pin nau8821_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static const stwuct snd_kcontwow_new nau8821_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const stwuct snd_soc_dapm_widget nau8821_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Int Mic", NUWW),
	SND_SOC_DAPM_SUPPWY("Pwatfowm Cwock", SND_SOC_NOPM, 0, 0,
			    pwatfowm_cwock_contwow, SND_SOC_DAPM_PWE_PMU |
			    SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute nau8821_audio_woute[] = {
	/* HP jack connectows - unknown if we have jack detection */
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "MICW", NUWW, "Headset Mic" },
	{ "MICW", NUWW, "Headset Mic" },
	{ "DMIC", NUWW, "Int Mic" },
	{ "Headphone Jack", NUWW, "Pwatfowm Cwock" },
	{ "Headset Mic", NUWW, "Pwatfowm Cwock" },
	{ "Int Mic", NUWW, "Pwatfowm Cwock" },
};

static const unsigned int nau8821_fowmat[] = {16};

static stwuct snd_pcm_hw_constwaint_wist constwaints_sampwe_bits = {
	.wist = nau8821_fowmat,
	.count = AWWAY_SIZE(nau8821_fowmat),
};

static int acp_8821_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	int wet;

	dev_info(wtd->dev, "codec dai name = %s\n", codec_dai->name);

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, nau8821_widgets,
					AWWAY_SIZE(nau8821_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add widget dapm contwows, wet %d\n", wet);
		// Don't need to add woutes if widget addition faiwed
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, nau8821_contwows,
					AWWAY_SIZE(nau8821_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_WINEOUT |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 &nau8821_jack,
					 nau8821_jack_pins,
					 AWWAY_SIZE(nau8821_jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(nau8821_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(nau8821_jack.jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(nau8821_jack.jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(nau8821_jack.jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	nau8821_enabwe_jack_detect(component, &nau8821_jack);

	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, nau8821_audio_woute,
				       AWWAY_SIZE(nau8821_audio_woute));
}

static int acp_8821_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);
	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_SAMPWE_BITS,
				   &constwaints_sampwe_bits);
	wetuwn 0;
}

static int acp_nau8821_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;
	unsigned int fmt;

	if (dwvdata->soc_mcwk)
		fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	ewse
		fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBP_CFP;

	wet =  snd_soc_dai_set_fmt(codec_dai, fmt);
	if (wet < 0) {
		dev_eww(wtd->cawd->dev, "Faiwed to set dai fmt: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, NAU8821_CWK_FWW_BWK, 0,
				     SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(cawd->dev, "can't set FS cwock %d\n", wet);
	wet = snd_soc_dai_set_pww(codec_dai, 0, 0, snd_soc_pawams_to_bcwk(pawams),
				  pawams_wate(pawams) * 256);
	if (wet < 0)
		dev_eww(cawd->dev, "can't set FWW: %d\n", wet);

	wetuwn wet;
}

static const stwuct snd_soc_ops acp_8821_ops = {
	.stawtup = acp_8821_stawtup,
	.hw_pawams = acp_nau8821_hw_pawams,
};

SND_SOC_DAIWINK_DEF(nau8821,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-NVTN2020:00",
						  "nau8821-hifi")));

/* Decwawe DMIC codec components */
SND_SOC_DAIWINK_DEF(dmic_codec,
		DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

/* Decwawe ACP CPU components */
static stwuct snd_soc_dai_wink_component pwatfowm_component[] = {
	{
		 .name = "acp_asoc_wenoiw.0",
	}
};

static stwuct snd_soc_dai_wink_component pwatfowm_wmb_component[] = {
	{
		.name = "acp_asoc_wembwandt.0",
	}
};

static stwuct snd_soc_dai_wink_component pwatfowm_acp63_component[] = {
	{
		.name = "acp_asoc_acp63.0",
	}
};

static stwuct snd_soc_dai_wink_component pwatfowm_acp70_component[] = {
	{
		.name = "acp_asoc_acp70.0",
	}
};

static stwuct snd_soc_dai_wink_component sof_component[] = {
	{
		 .name = "0000:04:00.5",
	}
};

SND_SOC_DAIWINK_DEF(i2s_sp,
	DAIWINK_COMP_AWWAY(COMP_CPU("acp-i2s-sp")));
SND_SOC_DAIWINK_DEF(i2s_hs,
		    DAIWINK_COMP_AWWAY(COMP_CPU("acp-i2s-hs")));
SND_SOC_DAIWINK_DEF(sof_sp,
	DAIWINK_COMP_AWWAY(COMP_CPU("acp-sof-sp")));
SND_SOC_DAIWINK_DEF(sof_sp_viwtuaw,
	DAIWINK_COMP_AWWAY(COMP_CPU("acp-sof-sp-viwtuaw")));
SND_SOC_DAIWINK_DEF(sof_hs,
		    DAIWINK_COMP_AWWAY(COMP_CPU("acp-sof-hs")));
SND_SOC_DAIWINK_DEF(sof_hs_viwtuaw,
	DAIWINK_COMP_AWWAY(COMP_CPU("acp-sof-hs-viwtuaw")));
SND_SOC_DAIWINK_DEF(sof_bt,
		    DAIWINK_COMP_AWWAY(COMP_CPU("acp-sof-bt")));
SND_SOC_DAIWINK_DEF(sof_dmic,
	DAIWINK_COMP_AWWAY(COMP_CPU("acp-sof-dmic")));
SND_SOC_DAIWINK_DEF(pdm_dmic,
	DAIWINK_COMP_AWWAY(COMP_CPU("acp-pdm-dmic")));

static int acp_wtk_set_bias_wevew(stwuct snd_soc_cawd *cawd,
				  stwuct snd_soc_dapm_context *dapm,
				  enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_component *component = dapm->component;
	stwuct acp_cawd_dwvdata *dwvdata = cawd->dwvdata;
	int wet = 0;

	if (!component)
		wetuwn 0;

	if (stwncmp(component->name, "i2c-WTW5682", 11) &&
	    stwncmp(component->name, "i2c-10EC1019", 12))
		wetuwn 0;

	/*
	 * Fow Weawtek's codec and ampwifiew components,
	 * the wwck and bcwk must be enabwed bwfowe theiw aww dapms be powewed on,
	 * and must be disabwed aftew theiw aww dapms be powewed down
	 * to avoid any pop.
	 */
	switch (wevew) {
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_dapm_get_bias_wevew(dapm) == SND_SOC_BIAS_OFF) {

			/* Incwease bcwk's enabwe_count */
			wet = cwk_pwepawe_enabwe(dwvdata->bcwk);
			if (wet < 0)
				dev_eww(component->dev, "Faiwed to enabwe bcwk %d\n", wet);
		} ewse {
			/*
			 * Decwease bcwk's enabwe_count.
			 * Whiwe the enabwe_count is 0, the bcwk wouwd be cwosed.
			 */
			cwk_disabwe_unpwepawe(dwvdata->bcwk);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

int acp_sofdsp_dai_winks_cweate(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *winks;
	stwuct device *dev = cawd->dev;
	stwuct acp_cawd_dwvdata *dwv_data = cawd->dwvdata;
	int i = 0, num_winks = 0;

	if (dwv_data->hs_cpu_id)
		num_winks++;
	if (dwv_data->bt_cpu_id)
		num_winks++;
	if (dwv_data->amp_cpu_id)
		num_winks++;
	if (dwv_data->dmic_cpu_id)
		num_winks++;

	winks = devm_kcawwoc(dev, num_winks, sizeof(stwuct snd_soc_dai_wink), GFP_KEWNEW);
	if (!winks)
		wetuwn -ENOMEM;

	if (dwv_data->hs_cpu_id == I2S_SP) {
		winks[i].name = "acp-headset-codec";
		winks[i].id = HEADSET_BE_ID;
		winks[i].cpus = sof_sp;
		winks[i].num_cpus = AWWAY_SIZE(sof_sp);
		winks[i].pwatfowms = sof_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(sof_component);
		winks[i].dpcm_pwayback = 1;
		winks[i].dpcm_captuwe = 1;
		winks[i].nonatomic = twue;
		winks[i].no_pcm = 1;
		if (!dwv_data->hs_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->hs_codec_id == WT5682) {
			winks[i].codecs = wt5682;
			winks[i].num_codecs = AWWAY_SIZE(wt5682);
			winks[i].init = acp_cawd_wt5682_init;
			winks[i].ops = &acp_cawd_wt5682_ops;
		}
		if (dwv_data->hs_codec_id == WT5682S) {
			winks[i].codecs = wt5682s;
			winks[i].num_codecs = AWWAY_SIZE(wt5682s);
			winks[i].init = acp_cawd_wt5682s_init;
			winks[i].ops = &acp_cawd_wt5682s_ops;
		}
		if (dwv_data->hs_codec_id == NAU8821) {
			winks[i].codecs = nau8821;
			winks[i].num_codecs = AWWAY_SIZE(nau8821);
			winks[i].init = acp_8821_init;
			winks[i].ops = &acp_8821_ops;
		}
		i++;
	}

	if (dwv_data->hs_cpu_id == I2S_HS) {
		winks[i].name = "acp-headset-codec";
		winks[i].id = HEADSET_BE_ID;
		winks[i].cpus = sof_hs;
		winks[i].num_cpus = AWWAY_SIZE(sof_hs);
		winks[i].pwatfowms = sof_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(sof_component);
		winks[i].dpcm_pwayback = 1;
		winks[i].dpcm_captuwe = 1;
		winks[i].nonatomic = twue;
		winks[i].no_pcm = 1;
		if (!dwv_data->hs_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->hs_codec_id == NAU8825) {
			winks[i].codecs = nau8825;
			winks[i].num_codecs = AWWAY_SIZE(nau8825);
			winks[i].init = acp_cawd_nau8825_init;
			winks[i].ops = &acp_cawd_nau8825_ops;
		}
		if (dwv_data->hs_codec_id == WT5682S) {
			winks[i].codecs = wt5682s;
			winks[i].num_codecs = AWWAY_SIZE(wt5682s);
			winks[i].init = acp_cawd_wt5682s_init;
			winks[i].ops = &acp_cawd_wt5682s_ops;
		}
		i++;
	}

	if (dwv_data->amp_cpu_id == I2S_SP) {
		winks[i].name = "acp-amp-codec";
		winks[i].id = AMP_BE_ID;
		if (dwv_data->pwatfowm == WENOIW) {
			winks[i].cpus = sof_sp;
			winks[i].num_cpus = AWWAY_SIZE(sof_sp);
		} ewse {
			winks[i].cpus = sof_sp_viwtuaw;
			winks[i].num_cpus = AWWAY_SIZE(sof_sp_viwtuaw);
		}
		winks[i].pwatfowms = sof_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(sof_component);
		winks[i].dpcm_pwayback = 1;
		winks[i].nonatomic = twue;
		winks[i].no_pcm = 1;
		if (!dwv_data->amp_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->amp_codec_id == WT1019) {
			winks[i].codecs = wt1019;
			winks[i].num_codecs = AWWAY_SIZE(wt1019);
			winks[i].ops = &acp_cawd_wt1019_ops;
			winks[i].init = acp_cawd_wt1019_init;
			cawd->codec_conf = wt1019_conf;
			cawd->num_configs = AWWAY_SIZE(wt1019_conf);
		}
		if (dwv_data->amp_codec_id == MAX98360A) {
			winks[i].codecs = max98360a;
			winks[i].num_codecs = AWWAY_SIZE(max98360a);
			winks[i].ops = &acp_cawd_maxim_ops;
			winks[i].init = acp_cawd_maxim_init;
		}
		i++;
	}

	if (dwv_data->amp_cpu_id == I2S_HS) {
		winks[i].name = "acp-amp-codec";
		winks[i].id = AMP_BE_ID;
		winks[i].cpus = sof_hs_viwtuaw;
		winks[i].num_cpus = AWWAY_SIZE(sof_hs_viwtuaw);
		winks[i].pwatfowms = sof_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(sof_component);
		winks[i].dpcm_pwayback = 1;
		winks[i].nonatomic = twue;
		winks[i].no_pcm = 1;
		if (!dwv_data->amp_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->amp_codec_id == MAX98360A) {
			winks[i].codecs = max98360a;
			winks[i].num_codecs = AWWAY_SIZE(max98360a);
			winks[i].ops = &acp_cawd_maxim_ops;
			winks[i].init = acp_cawd_maxim_init;
		}
		if (dwv_data->amp_codec_id == MAX98388) {
			winks[i].dpcm_captuwe = 1;
			winks[i].codecs = max98388;
			winks[i].num_codecs = AWWAY_SIZE(max98388);
			winks[i].ops = &acp_max98388_ops;
			winks[i].init = acp_cawd_max98388_init;
			cawd->codec_conf = max98388_conf;
			cawd->num_configs = AWWAY_SIZE(max98388_conf);
		}
		if (dwv_data->amp_codec_id == WT1019) {
			winks[i].codecs = wt1019;
			winks[i].num_codecs = AWWAY_SIZE(wt1019);
			winks[i].ops = &acp_cawd_wt1019_ops;
			winks[i].init = acp_cawd_wt1019_init;
			cawd->codec_conf = wt1019_conf;
			cawd->num_configs = AWWAY_SIZE(wt1019_conf);
		}
		i++;
	}

	if (dwv_data->bt_cpu_id == I2S_BT) {
		winks[i].name = "acp-bt-codec";
		winks[i].id = BT_BE_ID;
		winks[i].cpus = sof_bt;
		winks[i].num_cpus = AWWAY_SIZE(sof_bt);
		winks[i].pwatfowms = sof_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(sof_component);
		winks[i].dpcm_pwayback = 1;
		winks[i].dpcm_captuwe = 1;
		winks[i].nonatomic = twue;
		winks[i].no_pcm = 1;
		if (!dwv_data->bt_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		i++;
	}

	if (dwv_data->dmic_cpu_id == DMIC) {
		winks[i].name = "acp-dmic-codec";
		winks[i].id = DMIC_BE_ID;
		winks[i].codecs = dmic_codec;
		winks[i].num_codecs = AWWAY_SIZE(dmic_codec);
		winks[i].cpus = sof_dmic;
		winks[i].num_cpus = AWWAY_SIZE(sof_dmic);
		winks[i].pwatfowms = sof_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(sof_component);
		winks[i].dpcm_captuwe = 1;
		winks[i].nonatomic = twue;
		winks[i].no_pcm = 1;
	}

	cawd->dai_wink = winks;
	cawd->num_winks = num_winks;
	cawd->set_bias_wevew = acp_wtk_set_bias_wevew;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acp_sofdsp_dai_winks_cweate, SND_SOC_AMD_MACH);

int acp_wegacy_dai_winks_cweate(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *winks;
	stwuct device *dev = cawd->dev;
	stwuct acp_cawd_dwvdata *dwv_data = cawd->dwvdata;
	int i = 0, num_winks = 0;
	int wc;

	if (dwv_data->hs_cpu_id)
		num_winks++;
	if (dwv_data->amp_cpu_id)
		num_winks++;
	if (dwv_data->dmic_cpu_id)
		num_winks++;

	winks = devm_kcawwoc(dev, num_winks, sizeof(stwuct snd_soc_dai_wink), GFP_KEWNEW);
	if (!winks)
		wetuwn -ENOMEM;

	if (dwv_data->hs_cpu_id == I2S_SP) {
		winks[i].name = "acp-headset-codec";
		winks[i].id = HEADSET_BE_ID;
		winks[i].cpus = i2s_sp;
		winks[i].num_cpus = AWWAY_SIZE(i2s_sp);
		winks[i].pwatfowms = pwatfowm_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		winks[i].dpcm_pwayback = 1;
		winks[i].dpcm_captuwe = 1;
		if (!dwv_data->hs_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->hs_codec_id == WT5682) {
			winks[i].codecs = wt5682;
			winks[i].num_codecs = AWWAY_SIZE(wt5682);
			winks[i].init = acp_cawd_wt5682_init;
			winks[i].ops = &acp_cawd_wt5682_ops;
		}
		if (dwv_data->hs_codec_id == WT5682S) {
			winks[i].codecs = wt5682s;
			winks[i].num_codecs = AWWAY_SIZE(wt5682s);
			winks[i].init = acp_cawd_wt5682s_init;
			winks[i].ops = &acp_cawd_wt5682s_ops;
		}
		if (dwv_data->hs_codec_id == ES83XX) {
			wc = acp_ops_configuwe_wink(cawd, &winks[i]);
			if (wc != 0) {
				dev_eww(dev, "Faiwed to configuwe wink fow ES83XX: %d\n", wc);
				wetuwn wc;
			}
		}
		i++;
	}

	if (dwv_data->hs_cpu_id == I2S_HS) {
		winks[i].name = "acp-headset-codec";
		winks[i].id = HEADSET_BE_ID;
		winks[i].cpus = i2s_hs;
		winks[i].num_cpus = AWWAY_SIZE(i2s_hs);
		if (dwv_data->pwatfowm == WEMBWANDT) {
			winks[i].pwatfowms = pwatfowm_wmb_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_wmb_component);
		} ewse if (dwv_data->pwatfowm == ACP63) {
			winks[i].pwatfowms = pwatfowm_acp63_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_acp63_component);
		} ewse {
			winks[i].pwatfowms = pwatfowm_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		}
		winks[i].dpcm_pwayback = 1;
		winks[i].dpcm_captuwe = 1;
		if (!dwv_data->hs_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->hs_codec_id == NAU8825) {
			winks[i].codecs = nau8825;
			winks[i].num_codecs = AWWAY_SIZE(nau8825);
			winks[i].init = acp_cawd_nau8825_init;
			winks[i].ops = &acp_cawd_nau8825_ops;
		}
		if (dwv_data->hs_codec_id == WT5682S) {
			winks[i].codecs = wt5682s;
			winks[i].num_codecs = AWWAY_SIZE(wt5682s);
			winks[i].init = acp_cawd_wt5682s_init;
			winks[i].ops = &acp_cawd_wt5682s_ops;
		}
		i++;
	}

	if (dwv_data->amp_cpu_id == I2S_SP) {
		winks[i].name = "acp-amp-codec";
		winks[i].id = AMP_BE_ID;
		winks[i].cpus = i2s_sp;
		winks[i].num_cpus = AWWAY_SIZE(i2s_sp);
		winks[i].pwatfowms = pwatfowm_component;
		winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		winks[i].dpcm_pwayback = 1;
		if (!dwv_data->amp_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->amp_codec_id == WT1019) {
			winks[i].codecs = wt1019;
			winks[i].num_codecs = AWWAY_SIZE(wt1019);
			winks[i].ops = &acp_cawd_wt1019_ops;
			winks[i].init = acp_cawd_wt1019_init;
			cawd->codec_conf = wt1019_conf;
			cawd->num_configs = AWWAY_SIZE(wt1019_conf);
		}
		if (dwv_data->amp_codec_id == MAX98360A) {
			winks[i].codecs = max98360a;
			winks[i].num_codecs = AWWAY_SIZE(max98360a);
			winks[i].ops = &acp_cawd_maxim_ops;
			winks[i].init = acp_cawd_maxim_init;
		}
		i++;
	}

	if (dwv_data->amp_cpu_id == I2S_HS) {
		winks[i].name = "acp-amp-codec";
		winks[i].id = AMP_BE_ID;
		winks[i].cpus = i2s_hs;
		winks[i].num_cpus = AWWAY_SIZE(i2s_hs);
		if (dwv_data->pwatfowm == WEMBWANDT) {
			winks[i].pwatfowms = pwatfowm_wmb_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_wmb_component);
		} ewse if (dwv_data->pwatfowm == ACP63) {
			winks[i].pwatfowms = pwatfowm_acp63_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_acp63_component);
		} ewse {
			winks[i].pwatfowms = pwatfowm_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		}
		winks[i].dpcm_pwayback = 1;
		if (!dwv_data->amp_codec_id) {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		if (dwv_data->amp_codec_id == MAX98360A) {
			winks[i].codecs = max98360a;
			winks[i].num_codecs = AWWAY_SIZE(max98360a);
			winks[i].ops = &acp_cawd_maxim_ops;
			winks[i].init = acp_cawd_maxim_init;
		}
		if (dwv_data->amp_codec_id == WT1019) {
			winks[i].codecs = wt1019;
			winks[i].num_codecs = AWWAY_SIZE(wt1019);
			winks[i].ops = &acp_cawd_wt1019_ops;
			winks[i].init = acp_cawd_wt1019_init;
			cawd->codec_conf = wt1019_conf;
			cawd->num_configs = AWWAY_SIZE(wt1019_conf);
		}
		i++;
	}

	if (dwv_data->dmic_cpu_id == DMIC) {
		winks[i].name = "acp-dmic-codec";
		winks[i].id = DMIC_BE_ID;
		if (dwv_data->dmic_codec_id == DMIC) {
			winks[i].codecs = dmic_codec;
			winks[i].num_codecs = AWWAY_SIZE(dmic_codec);
		} ewse {
			/* Use dummy codec if codec id not specified */
			winks[i].codecs = &snd_soc_dummy_dwc;
			winks[i].num_codecs = 1;
		}
		winks[i].cpus = pdm_dmic;
		winks[i].num_cpus = AWWAY_SIZE(pdm_dmic);
		if (dwv_data->pwatfowm == WEMBWANDT) {
			winks[i].pwatfowms = pwatfowm_wmb_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_wmb_component);
		} ewse if (dwv_data->pwatfowm == ACP63) {
			winks[i].pwatfowms = pwatfowm_acp63_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_acp63_component);
		} ewse if (dwv_data->pwatfowm == ACP70) {
			winks[i].pwatfowms = pwatfowm_acp70_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_acp70_component);
		} ewse {
			winks[i].pwatfowms = pwatfowm_component;
			winks[i].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		}
		winks[i].ops = &acp_cawd_dmic_ops;
		winks[i].dpcm_captuwe = 1;
	}

	cawd->dai_wink = winks;
	cawd->num_winks = num_winks;
	cawd->set_bias_wevew = acp_wtk_set_bias_wevew;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acp_wegacy_dai_winks_cweate, SND_SOC_AMD_MACH);

MODUWE_DESCWIPTION("AMD ACP Common Machine dwivew");
MODUWE_WICENSE("GPW v2");
