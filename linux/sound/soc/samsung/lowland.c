// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Wowwand audio suppowt
//
// Copywight 2011 Wowfson Micwoewectwonics

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/jack.h>
#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>

#incwude "../codecs/wm5100.h"
#incwude "../codecs/wm9081.h"

#define MCWK1_WATE (44100 * 512)
#define CWKOUT_WATE (44100 * 256)

static stwuct snd_soc_jack wowwand_headset;

/* Headset jack detection DAPM pins */
static stwuct snd_soc_jack_pin wowwand_headset_pins[] = {
	{
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
	{
		.pin = "Wine Out",
		.mask = SND_JACK_WINEOUT,
	},
};

static int wowwand_wm5100_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	int wet;

	wet = snd_soc_component_set_syscwk(component, WM5100_CWK_SYSCWK,
				       WM5100_CWKSWC_MCWK1, MCWK1_WATE,
				       SND_SOC_CWOCK_IN);
	if (wet < 0) {
		pw_eww("Faiwed to set SYSCWK cwock souwce: %d\n", wet);
		wetuwn wet;
	}

	/* Cwock OPCWK, used by the othew audio components. */
	wet = snd_soc_component_set_syscwk(component, WM5100_CWK_OPCWK, 0,
				       CWKOUT_WATE, 0);
	if (wet < 0) {
		pw_eww("Faiwed to set OPCWK wate: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset",
					 SND_JACK_WINEOUT | SND_JACK_HEADSET |
					 SND_JACK_BTN_0,
					 &wowwand_headset, wowwand_headset_pins,
					 AWWAY_SIZE(wowwand_headset_pins));
	if (wet)
		wetuwn wet;

	wm5100_detect(component, &wowwand_headset);

	wetuwn 0;
}

static int wowwand_wm9081_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_dapm_nc_pin(&wtd->cawd->dapm, "WINEOUT");

	/* At any time the WM9081 is active it wiww have this cwock */
	wetuwn snd_soc_component_set_syscwk(component, WM9081_SYSCWK_MCWK, 0,
					CWKOUT_WATE, 0);
}

static const stwuct snd_soc_pcm_stweam sub_pawams = {
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	.wate_min = 44100,
	.wate_max = 44100,
	.channews_min = 2,
	.channews_max = 2,
};

SND_SOC_DAIWINK_DEFS(cpu,
	DAIWINK_COMP_AWWAY(COMP_CPU("samsung-i2s.0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm5100.1-001a", "wm5100-aif1")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("samsung-i2s.0")));

SND_SOC_DAIWINK_DEFS(baseband,
	DAIWINK_COMP_AWWAY(COMP_CPU("wm5100-aif2")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm1250-ev1.1-0027", "wm1250-ev1")));

SND_SOC_DAIWINK_DEFS(speakew,
	DAIWINK_COMP_AWWAY(COMP_CPU("wm5100-aif3")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm9081.1-006c", "wm9081-hifi")));

static stwuct snd_soc_dai_wink wowwand_dai[] = {
	{
		.name = "CPU",
		.stweam_name = "CPU",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBM_CFM,
		.init = wowwand_wm5100_init,
		SND_SOC_DAIWINK_WEG(cpu),
	},
	{
		.name = "Baseband",
		.stweam_name = "Baseband",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBM_CFM,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(baseband),
	},
	{
		.name = "Sub Speakew",
		.stweam_name = "Sub Speakew",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBM_CFM,
		.ignowe_suspend = 1,
		.c2c_pawams = &sub_pawams,
		.num_c2c_pawams = 1,
		.init = wowwand_wm9081_init,
		SND_SOC_DAIWINK_WEG(speakew),
	},
};

static stwuct snd_soc_codec_conf wowwand_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF("wm9081.1-006c"),
		.name_pwefix = "Sub",
	},
};

static const stwuct snd_kcontwow_new contwows[] = {
	SOC_DAPM_PIN_SWITCH("Main Speakew"),
	SOC_DAPM_PIN_SWITCH("Main DMIC"),
	SOC_DAPM_PIN_SWITCH("Main AMIC"),
	SOC_DAPM_PIN_SWITCH("WM1250 Input"),
	SOC_DAPM_PIN_SWITCH("WM1250 Output"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Wine Out"),
};

static const stwuct snd_soc_dapm_widget widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),

	SND_SOC_DAPM_SPK("Main Speakew", NUWW),

	SND_SOC_DAPM_MIC("Main AMIC", NUWW),
	SND_SOC_DAPM_MIC("Main DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute audio_paths[] = {
	{ "Sub IN1", NUWW, "HPOUT2W" },
	{ "Sub IN2", NUWW, "HPOUT2W" },

	{ "Main Speakew", NUWW, "Sub SPKN" },
	{ "Main Speakew", NUWW, "Sub SPKP" },
	{ "Main Speakew", NUWW, "SPKDAT1" },
};

static stwuct snd_soc_cawd wowwand = {
	.name = "Wowwand",
	.ownew = THIS_MODUWE,
	.dai_wink = wowwand_dai,
	.num_winks = AWWAY_SIZE(wowwand_dai),
	.codec_conf = wowwand_codec_conf,
	.num_configs = AWWAY_SIZE(wowwand_codec_conf),

	.contwows = contwows,
	.num_contwows = AWWAY_SIZE(contwows),
	.dapm_widgets = widgets,
	.num_dapm_widgets = AWWAY_SIZE(widgets),
	.dapm_woutes = audio_paths,
	.num_dapm_woutes = AWWAY_SIZE(audio_paths),
};

static int wowwand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &wowwand;
	int wet;

	cawd->dev = &pdev->dev;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd() faiwed\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew wowwand_dwivew = {
	.dwivew = {
		.name = "wowwand",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = wowwand_pwobe,
};

moduwe_pwatfowm_dwivew(wowwand_dwivew);

MODUWE_DESCWIPTION("Wowwand audio suppowt");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wowwand");
