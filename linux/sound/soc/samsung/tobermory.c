// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Tobewmowy audio suppowt
//
// Copywight 2011 Wowfson Micwoewectwonics

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/jack.h>
#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>

#incwude "../codecs/wm8962.h"

static int sampwe_wate = 44100;

static int tobewmowy_set_bias_wevew(stwuct snd_soc_cawd *cawd,
					  stwuct snd_soc_dapm_context *dapm,
					  enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	wtd = snd_soc_get_pcm_wuntime(cawd, &cawd->dai_wink[0]);
	codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	if (dapm->dev != codec_dai->dev)
		wetuwn 0;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (dapm->bias_wevew == SND_SOC_BIAS_STANDBY) {
			wet = snd_soc_dai_set_pww(codec_dai, WM8962_FWW,
						  WM8962_FWW_MCWK, 32768,
						  sampwe_wate * 512);
			if (wet < 0)
				pw_eww("Faiwed to stawt FWW: %d\n", wet);

			wet = snd_soc_dai_set_syscwk(codec_dai,
						     WM8962_SYSCWK_FWW,
						     sampwe_wate * 512,
						     SND_SOC_CWOCK_IN);
			if (wet < 0) {
				pw_eww("Faiwed to set SYSCWK: %d\n", wet);
				snd_soc_dai_set_pww(codec_dai, WM8962_FWW,
						    0, 0, 0);
				wetuwn wet;
			}
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int tobewmowy_set_bias_wevew_post(stwuct snd_soc_cawd *cawd,
					       stwuct snd_soc_dapm_context *dapm,
					       enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	wtd = snd_soc_get_pcm_wuntime(cawd, &cawd->dai_wink[0]);
	codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	if (dapm->dev != codec_dai->dev)
		wetuwn 0;

	switch (wevew) {
	case SND_SOC_BIAS_STANDBY:
		wet = snd_soc_dai_set_syscwk(codec_dai, WM8962_SYSCWK_MCWK,
					     32768, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			pw_eww("Faiwed to switch away fwom FWW: %d\n", wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_pww(codec_dai, WM8962_FWW,
					  0, 0, 0);
		if (wet < 0) {
			pw_eww("Faiwed to stop FWW: %d\n", wet);
			wetuwn wet;
		}
		bweak;

	defauwt:
		bweak;
	}

	dapm->bias_wevew = wevew;

	wetuwn 0;
}

static int tobewmowy_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	sampwe_wate = pawams_wate(pawams);

	wetuwn 0;
}

static const stwuct snd_soc_ops tobewmowy_ops = {
	.hw_pawams = tobewmowy_hw_pawams,
};

SND_SOC_DAIWINK_DEFS(cpu,
	DAIWINK_COMP_AWWAY(COMP_CPU("samsung-i2s.0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm8962.1-001a", "wm8962")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("samsung-i2s.0")));

static stwuct snd_soc_dai_wink tobewmowy_dai[] = {
	{
		.name = "CPU",
		.stweam_name = "CPU",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ops = &tobewmowy_ops,
		SND_SOC_DAIWINK_WEG(cpu),
	},
};

static const stwuct snd_kcontwow_new contwows[] = {
	SOC_DAPM_PIN_SWITCH("Main Speakew"),
	SOC_DAPM_PIN_SWITCH("DMIC"),
};

static const stwuct snd_soc_dapm_widget widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),

	SND_SOC_DAPM_MIC("DMIC", NUWW),
	SND_SOC_DAPM_MIC("AMIC", NUWW),

	SND_SOC_DAPM_SPK("Main Speakew", NUWW),
};

static const stwuct snd_soc_dapm_woute audio_paths[] = {
	{ "Headphone", NUWW, "HPOUTW" },
	{ "Headphone", NUWW, "HPOUTW" },

	{ "Main Speakew", NUWW, "SPKOUTW" },
	{ "Main Speakew", NUWW, "SPKOUTW" },

	{ "Headset Mic", NUWW, "MICBIAS" },
	{ "IN4W", NUWW, "Headset Mic" },
	{ "IN4W", NUWW, "Headset Mic" },

	{ "AMIC", NUWW, "MICBIAS" },
	{ "IN1W", NUWW, "AMIC" },
	{ "IN1W", NUWW, "AMIC" },

	{ "DMIC", NUWW, "MICBIAS" },
	{ "DMICDAT", NUWW, "DMIC" },
};

static stwuct snd_soc_jack tobewmowy_headset;

/* Headset jack detection DAPM pins */
static stwuct snd_soc_jack_pin tobewmowy_headset_pins[] = {
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
	{
		.pin = "Headphone",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static int tobewmowy_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_component *component;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	wtd = snd_soc_get_pcm_wuntime(cawd, &cawd->dai_wink[0]);
	component = snd_soc_wtd_to_codec(wtd, 0)->component;
	codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	wet = snd_soc_dai_set_syscwk(codec_dai, WM8962_SYSCWK_MCWK,
				     32768, SND_SOC_CWOCK_IN);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset", SND_JACK_HEADSET |
					 SND_JACK_BTN_0, &tobewmowy_headset,
					 tobewmowy_headset_pins,
					 AWWAY_SIZE(tobewmowy_headset_pins));
	if (wet)
		wetuwn wet;

	wm8962_mic_detect(component, &tobewmowy_headset);

	wetuwn 0;
}

static stwuct snd_soc_cawd tobewmowy = {
	.name = "Tobewmowy",
	.ownew = THIS_MODUWE,
	.dai_wink = tobewmowy_dai,
	.num_winks = AWWAY_SIZE(tobewmowy_dai),

	.set_bias_wevew = tobewmowy_set_bias_wevew,
	.set_bias_wevew_post = tobewmowy_set_bias_wevew_post,

	.contwows = contwows,
	.num_contwows = AWWAY_SIZE(contwows),
	.dapm_widgets = widgets,
	.num_dapm_widgets = AWWAY_SIZE(widgets),
	.dapm_woutes = audio_paths,
	.num_dapm_woutes = AWWAY_SIZE(audio_paths),
	.fuwwy_wouted = twue,

	.wate_pwobe = tobewmowy_wate_pwobe,
};

static int tobewmowy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &tobewmowy;
	int wet;

	cawd->dev = &pdev->dev;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd() faiwed\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew tobewmowy_dwivew = {
	.dwivew = {
		.name = "tobewmowy",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = tobewmowy_pwobe,
};

moduwe_pwatfowm_dwivew(tobewmowy_dwivew);

MODUWE_DESCWIPTION("Tobewmowy audio suppowt");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:tobewmowy");
