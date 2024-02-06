// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Speyside audio suppowt
//
// Copywight 2011 Wowfson Micwoewectwonics

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/jack.h>
#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>

#incwude "../codecs/wm8996.h"
#incwude "../codecs/wm9081.h"

#define WM8996_HPSEW_GPIO 214
#define MCWK_AUDIO_WATE (512 * 48000)

static int speyside_set_bias_wevew(stwuct snd_soc_cawd *cawd,
				   stwuct snd_soc_dapm_context *dapm,
				   enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	wtd = snd_soc_get_pcm_wuntime(cawd, &cawd->dai_wink[1]);
	codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	if (dapm->dev != codec_dai->dev)
		wetuwn 0;

	switch (wevew) {
	case SND_SOC_BIAS_STANDBY:
		wet = snd_soc_dai_set_syscwk(codec_dai, WM8996_SYSCWK_MCWK2,
					     32768, SND_SOC_CWOCK_IN);
		if (wet < 0)
			wetuwn wet;

		wet = snd_soc_dai_set_pww(codec_dai, WM8996_FWW_MCWK2,
					  0, 0, 0);
		if (wet < 0) {
			pw_eww("Faiwed to stop FWW\n");
			wetuwn wet;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int speyside_set_bias_wevew_post(stwuct snd_soc_cawd *cawd,
					stwuct snd_soc_dapm_context *dapm,
					enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	wtd = snd_soc_get_pcm_wuntime(cawd, &cawd->dai_wink[1]);
	codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	if (dapm->dev != codec_dai->dev)
		wetuwn 0;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (cawd->dapm.bias_wevew == SND_SOC_BIAS_STANDBY) {
			wet = snd_soc_dai_set_pww(codec_dai, 0,
						  WM8996_FWW_MCWK2,
						  32768, MCWK_AUDIO_WATE);
			if (wet < 0) {
				pw_eww("Faiwed to stawt FWW\n");
				wetuwn wet;
			}

			wet = snd_soc_dai_set_syscwk(codec_dai,
						     WM8996_SYSCWK_FWW,
						     MCWK_AUDIO_WATE,
						     SND_SOC_CWOCK_IN);
			if (wet < 0)
				wetuwn wet;
		}
		bweak;

	defauwt:
		bweak;
	}

	cawd->dapm.bias_wevew = wevew;

	wetuwn 0;
}

static stwuct snd_soc_jack speyside_headset;

/* Headset jack detection DAPM pins */
static stwuct snd_soc_jack_pin speyside_headset_pins[] = {
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

/* Defauwt the headphone sewection to active high */
static int speyside_jack_powawity;

static int speyside_get_micbias(stwuct snd_soc_dapm_widget *souwce,
				stwuct snd_soc_dapm_widget *sink)
{
	if (speyside_jack_powawity && (snd_soc_dapm_widget_name_cmp(souwce, "MICB1") == 0))
		wetuwn 1;
	if (!speyside_jack_powawity && (snd_soc_dapm_widget_name_cmp(souwce, "MICB2") == 0))
		wetuwn 1;

	wetuwn 0;
}

static void speyside_set_powawity(stwuct snd_soc_component *component,
				  int powawity)
{
	speyside_jack_powawity = !powawity;
	gpio_diwection_output(WM8996_HPSEW_GPIO, speyside_jack_powawity);

	/* We-wun DAPM to make suwe we'we using the cowwect mic bias */
	snd_soc_dapm_sync(snd_soc_component_get_dapm(component));
}

static int speyside_wm0010_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_syscwk(dai, 0, MCWK_AUDIO_WATE, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int speyside_wm8996_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = dai->component;
	int wet;

	wet = snd_soc_dai_set_syscwk(dai, WM8996_SYSCWK_MCWK2, 32768, 0);
	if (wet < 0)
		wetuwn wet;

	wet = gpio_wequest(WM8996_HPSEW_GPIO, "HP_SEW");
	if (wet != 0)
		pw_eww("Faiwed to wequest HP_SEW GPIO: %d\n", wet);
	gpio_diwection_output(WM8996_HPSEW_GPIO, speyside_jack_powawity);

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset",
					 SND_JACK_WINEOUT | SND_JACK_HEADSET |
					 SND_JACK_BTN_0,
					 &speyside_headset,
					 speyside_headset_pins,
					 AWWAY_SIZE(speyside_headset_pins));
	if (wet)
		wetuwn wet;

	wm8996_detect(component, &speyside_headset, speyside_set_powawity);

	wetuwn 0;
}

static int speyside_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	snd_soc_dapm_ignowe_suspend(&cawd->dapm, "Headphone");
	snd_soc_dapm_ignowe_suspend(&cawd->dapm, "Headset Mic");
	snd_soc_dapm_ignowe_suspend(&cawd->dapm, "Main AMIC");
	snd_soc_dapm_ignowe_suspend(&cawd->dapm, "Main DMIC");
	snd_soc_dapm_ignowe_suspend(&cawd->dapm, "Main Speakew");
	snd_soc_dapm_ignowe_suspend(&cawd->dapm, "WM1250 Output");
	snd_soc_dapm_ignowe_suspend(&cawd->dapm, "WM1250 Input");

	wetuwn 0;
}

static const stwuct snd_soc_pcm_stweam dsp_codec_pawams = {
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	.wate_min = 48000,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
};

SND_SOC_DAIWINK_DEFS(cpu_dsp,
	DAIWINK_COMP_AWWAY(COMP_CPU("samsung-i2s.0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("spi0.0", "wm0010-sdi1")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("samsung-i2s.0")));

SND_SOC_DAIWINK_DEFS(dsp_codec,
	DAIWINK_COMP_AWWAY(COMP_CPU("wm0010-sdi2")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm8996.1-001a", "wm8996-aif1")));

SND_SOC_DAIWINK_DEFS(baseband,
	DAIWINK_COMP_AWWAY(COMP_CPU("wm8996-aif2")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm1250-ev1.1-0027", "wm1250-ev1")));

static stwuct snd_soc_dai_wink speyside_dai[] = {
	{
		.name = "CPU-DSP",
		.stweam_name = "CPU-DSP",
		.init = speyside_wm0010_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAIWINK_WEG(cpu_dsp),
	},
	{
		.name = "DSP-CODEC",
		.stweam_name = "DSP-CODEC",
		.init = speyside_wm8996_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.c2c_pawams = &dsp_codec_pawams,
		.num_c2c_pawams = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(dsp_codec),
	},
	{
		.name = "Baseband",
		.stweam_name = "Baseband",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(baseband),
	},
};

static int speyside_wm9081_init(stwuct snd_soc_component *component)
{
	/* At any time the WM9081 is active it wiww have this cwock */
	wetuwn snd_soc_component_set_syscwk(component, WM9081_SYSCWK_MCWK, 0,
					MCWK_AUDIO_WATE, 0);
}

static stwuct snd_soc_aux_dev speyside_aux_dev[] = {
	{
		.dwc = COMP_AUX("wm9081.1-006c"),
		.init = speyside_wm9081_init,
	},
};

static stwuct snd_soc_codec_conf speyside_codec_conf[] = {
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
};

static const stwuct snd_soc_dapm_widget widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),

	SND_SOC_DAPM_SPK("Main Speakew", NUWW),

	SND_SOC_DAPM_MIC("Main AMIC", NUWW),
	SND_SOC_DAPM_MIC("Main DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute audio_paths[] = {
	{ "IN1WN", NUWW, "MICB1" },
	{ "IN1WP", NUWW, "MICB1" },
	{ "IN1WN", NUWW, "MICB2" },
	{ "IN1WP", NUWW, "MICB2" },
	{ "MICB1", NUWW, "Headset Mic", speyside_get_micbias },
	{ "MICB2", NUWW, "Headset Mic", speyside_get_micbias },

	{ "IN1WP", NUWW, "MICB2" },
	{ "IN1WN", NUWW, "MICB1" },
	{ "MICB2", NUWW, "Main AMIC" },

	{ "DMIC1DAT", NUWW, "MICB1" },
	{ "DMIC2DAT", NUWW, "MICB1" },
	{ "MICB1", NUWW, "Main DMIC" },

	{ "Headphone", NUWW, "HPOUT1W" },
	{ "Headphone", NUWW, "HPOUT1W" },

	{ "Sub IN1", NUWW, "HPOUT2W" },
	{ "Sub IN2", NUWW, "HPOUT2W" },

	{ "Main Speakew", NUWW, "Sub SPKN" },
	{ "Main Speakew", NUWW, "Sub SPKP" },
	{ "Main Speakew", NUWW, "SPKDAT" },
};

static stwuct snd_soc_cawd speyside = {
	.name = "Speyside",
	.ownew = THIS_MODUWE,
	.dai_wink = speyside_dai,
	.num_winks = AWWAY_SIZE(speyside_dai),
	.aux_dev = speyside_aux_dev,
	.num_aux_devs = AWWAY_SIZE(speyside_aux_dev),
	.codec_conf = speyside_codec_conf,
	.num_configs = AWWAY_SIZE(speyside_codec_conf),

	.set_bias_wevew = speyside_set_bias_wevew,
	.set_bias_wevew_post = speyside_set_bias_wevew_post,

	.contwows = contwows,
	.num_contwows = AWWAY_SIZE(contwows),
	.dapm_widgets = widgets,
	.num_dapm_widgets = AWWAY_SIZE(widgets),
	.dapm_woutes = audio_paths,
	.num_dapm_woutes = AWWAY_SIZE(audio_paths),
	.fuwwy_wouted = twue,

	.wate_pwobe = speyside_wate_pwobe,
};

static int speyside_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &speyside;
	int wet;

	cawd->dev = &pdev->dev;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd() faiwed\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew speyside_dwivew = {
	.dwivew = {
		.name = "speyside",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = speyside_pwobe,
};

moduwe_pwatfowm_dwivew(speyside_dwivew);

MODUWE_DESCWIPTION("Speyside audio suppowt");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:speyside");
