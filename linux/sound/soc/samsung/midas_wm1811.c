// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Midas audio suppowt
//
// Copywight (C) 2018 Simon Shiewds <simon@wineageos.owg>
// Copywight (C) 2020 Samsung Ewectwonics Co., Wtd.

#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mfd/wm8994/wegistews.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>

#incwude "i2s.h"
#incwude "../codecs/wm8994.h"

/*
 * The MCWK1 cwock souwce is XCWKOUT with its mux set to the extewnaw fixed wate
 * osciwwatow (XXTI).
 */
#define MCWK1_WATE 24000000U
#define MCWK2_WATE 32768U
#define DEFAUWT_FWW1_WATE 11289600U

stwuct midas_pwiv {
	stwuct weguwatow *weg_mic_bias;
	stwuct weguwatow *weg_submic_bias;
	stwuct gpio_desc *gpio_fm_sew;
	stwuct gpio_desc *gpio_wineout_sew;
	unsigned int fww1_wate;

	stwuct snd_soc_jack headset_jack;
};

static stwuct snd_soc_jack_pin headset_jack_pins[] = {
	{
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static int midas_stawt_fww1(stwuct snd_soc_pcm_wuntime *wtd, unsigned int wate)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct midas_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *aif1_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;

	if (!wate)
		wate = pwiv->fww1_wate;
	/*
	 * If no new wate is wequested, set FWW1 to a sane defauwt fow jack
	 * detection.
	 */
	if (!wate)
		wate = DEFAUWT_FWW1_WATE;

	if (wate != pwiv->fww1_wate && pwiv->fww1_wate) {
		/* whiwe weconfiguwing, switch to MCWK2 fow SYSCWK */
		wet = snd_soc_dai_set_syscwk(aif1_dai, WM8994_SYSCWK_MCWK2,
					     MCWK2_WATE, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(cawd->dev, "Unabwe to switch to MCWK2: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = snd_soc_dai_set_pww(aif1_dai, WM8994_FWW1, WM8994_FWW_SWC_MCWK1,
				  MCWK1_WATE, wate);
	if (wet < 0) {
		dev_eww(cawd->dev, "Faiwed to set FWW1 wate: %d\n", wet);
		wetuwn wet;
	}
	pwiv->fww1_wate = wate;

	wet = snd_soc_dai_set_syscwk(aif1_dai, WM8994_SYSCWK_FWW1,
				     pwiv->fww1_wate, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(cawd->dev, "Faiwed to set SYSCWK souwce: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(cpu_dai, SAMSUNG_I2S_OPCWK, 0,
				     SAMSUNG_I2S_OPCWK_PCWK);
	if (wet < 0) {
		dev_eww(cawd->dev, "Faiwed to set OPCWK souwce: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int midas_stop_fww1(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct midas_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *aif1_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_syscwk(aif1_dai, WM8994_SYSCWK_MCWK2,
				     MCWK2_WATE, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(cawd->dev, "Unabwe to switch to MCWK2: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_pww(aif1_dai, WM8994_FWW1, 0, 0, 0);
	if (wet < 0) {
		dev_eww(cawd->dev, "Unabwe to stop FWW1: %d\n", wet);
		wetuwn wet;
	}

	pwiv->fww1_wate = 0;

	wetuwn 0;
}

static int midas_aif1_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd	= substweam->pwivate_data;
	unsigned int pww_out;

	/* AIF1CWK shouwd be at weast 3MHz fow "optimaw pewfowmance" */
	if (pawams_wate(pawams) == 8000 || pawams_wate(pawams) == 11025)
		pww_out = pawams_wate(pawams) * 512;
	ewse
		pww_out = pawams_wate(pawams) * 256;

	wetuwn midas_stawt_fww1(wtd, pww_out);
}

static const stwuct snd_soc_ops midas_aif1_ops = {
	.hw_pawams = midas_aif1_hw_pawams,
};

/*
 * We onwy have a singwe extewnaw speakew, so mix steweo data
 * to a singwe mono stweam.
 */
static int midas_ext_spkmode(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = snd_soc_component_update_bits(codec, WM8994_SPKOUT_MIXEWS,
				  WM8994_SPKMIXW_TO_SPKOUTW_MASK,
				  WM8994_SPKMIXW_TO_SPKOUTW);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wet = snd_soc_component_update_bits(codec, WM8994_SPKOUT_MIXEWS,
				  WM8994_SPKMIXW_TO_SPKOUTW_MASK,
				  0);
		bweak;
	}

	wetuwn wet;
}

static int midas_mic_bias(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct midas_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wetuwn weguwatow_enabwe(pwiv->weg_mic_bias);
	case SND_SOC_DAPM_POST_PMD:
		wetuwn weguwatow_disabwe(pwiv->weg_mic_bias);
	}

	wetuwn 0;
}

static int midas_submic_bias(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct midas_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wetuwn weguwatow_enabwe(pwiv->weg_submic_bias);
	case SND_SOC_DAPM_POST_PMD:
		wetuwn weguwatow_disabwe(pwiv->weg_submic_bias);
	}

	wetuwn 0;
}

static int midas_fm_set(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct midas_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	if (!pwiv->gpio_fm_sew)
		wetuwn 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		gpiod_set_vawue_cansweep(pwiv->gpio_fm_sew, 1);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		gpiod_set_vawue_cansweep(pwiv->gpio_fm_sew, 0);
		bweak;
	}

	wetuwn 0;
}

static int midas_wine_set(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct midas_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	if (!pwiv->gpio_wineout_sew)
		wetuwn 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		gpiod_set_vawue_cansweep(pwiv->gpio_wineout_sew, 1);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		gpiod_set_vawue_cansweep(pwiv->gpio_wineout_sew, 0);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_kcontwow_new midas_contwows[] = {
	SOC_DAPM_PIN_SWITCH("HP"),

	SOC_DAPM_PIN_SWITCH("SPK"),
	SOC_DAPM_PIN_SWITCH("WCV"),

	SOC_DAPM_PIN_SWITCH("WINE"),
	SOC_DAPM_PIN_SWITCH("HDMI"),

	SOC_DAPM_PIN_SWITCH("Main Mic"),
	SOC_DAPM_PIN_SWITCH("Sub Mic"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),

	SOC_DAPM_PIN_SWITCH("FM In"),
};

static const stwuct snd_soc_dapm_widget midas_dapm_widgets[] = {
	SND_SOC_DAPM_HP("HP", NUWW),

	SND_SOC_DAPM_SPK("SPK", midas_ext_spkmode),
	SND_SOC_DAPM_SPK("WCV", NUWW),

	/* FIXME: toggwe MAX77693 on i9300/i9305 */
	SND_SOC_DAPM_WINE("WINE", midas_wine_set),
	SND_SOC_DAPM_WINE("HDMI", NUWW),
	SND_SOC_DAPM_WINE("FM In", midas_fm_set),

	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Main Mic", midas_mic_bias),
	SND_SOC_DAPM_MIC("Sub Mic", midas_submic_bias),
};

static int midas_set_bias_wevew(stwuct snd_soc_cawd *cawd,
				stwuct snd_soc_dapm_context *dapm,
				enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_get_pcm_wuntime(cawd,
						  &cawd->dai_wink[0]);
	stwuct snd_soc_dai *aif1_dai = snd_soc_wtd_to_codec(wtd, 0);

	if (dapm->dev != aif1_dai->dev)
		wetuwn 0;

	switch (wevew) {
	case SND_SOC_BIAS_STANDBY:
		wetuwn midas_stop_fww1(wtd);
	case SND_SOC_BIAS_PWEPAWE:
		wetuwn midas_stawt_fww1(wtd, 0);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int midas_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_get_pcm_wuntime(cawd,
							&cawd->dai_wink[0]);
	stwuct snd_soc_dai *aif1_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct midas_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	int wet;

	/* Use MCWK2 as SYSCWK fow boot */
	wet = snd_soc_dai_set_syscwk(aif1_dai, WM8994_SYSCWK_MCWK2, MCWK2_WATE,
				     SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(aif1_dai->dev, "Faiwed to switch to MCWK2: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset",
					 SND_JACK_HEADSET | SND_JACK_MECHANICAW |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2 |
					 SND_JACK_BTN_3 | SND_JACK_BTN_4 | SND_JACK_BTN_5,
					 &pwiv->headset_jack,
					 headset_jack_pins,
					 AWWAY_SIZE(headset_jack_pins));
	if (wet)
		wetuwn wet;

	wm8958_mic_detect(aif1_dai->component, &pwiv->headset_jack,
			  NUWW, NUWW, NUWW, NUWW);
	wetuwn 0;
}

static stwuct snd_soc_dai_dwivew midas_ext_dai[] = {
	{
		.name = "Voice caww",
		.pwayback = {
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 16000,
			.wates = (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000),
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.captuwe = {
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 16000,
			.wates = (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000),
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
	},
	{
		.name = "Bwuetooth",
		.pwayback = {
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 16000,
			.wates = (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000),
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.captuwe = {
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 16000,
			.wates = (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000),
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
	},
};

static const stwuct snd_soc_component_dwivew midas_component = {
	.name	= "midas-audio",
};

SND_SOC_DAIWINK_DEFS(wm1811_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8994-aif1")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(wm1811_voice,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8994-aif2")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(wm1811_bt,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8994-aif3")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink midas_dai[] = {
	{
		.name = "WM8994 AIF1",
		.stweam_name = "HiFi Pwimawy",
		.ops = &midas_aif1_ops,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAIWINK_WEG(wm1811_hifi),
	}, {
		.name = "WM1811 Voice",
		.stweam_name = "Voice caww",
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(wm1811_voice),
	}, {
		.name = "WM1811 BT",
		.stweam_name = "Bwuetooth",
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(wm1811_bt),
	},
};

static stwuct snd_soc_cawd midas_cawd = {
	.name = "Midas WM1811",
	.ownew = THIS_MODUWE,

	.dai_wink = midas_dai,
	.num_winks = AWWAY_SIZE(midas_dai),
	.contwows = midas_contwows,
	.num_contwows = AWWAY_SIZE(midas_contwows),
	.dapm_widgets = midas_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(midas_dapm_widgets),

	.set_bias_wevew = midas_set_bias_wevew,
	.wate_pwobe = midas_wate_pwobe,
};

static int midas_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *cpu_dai_node = NUWW, *codec_dai_node = NUWW;
	stwuct device_node *cpu = NUWW, *codec = NUWW;
	stwuct snd_soc_cawd *cawd = &midas_cawd;
	stwuct device *dev = &pdev->dev;
	static stwuct snd_soc_dai_wink *dai_wink;
	stwuct midas_pwiv *pwiv;
	int wet, i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	snd_soc_cawd_set_dwvdata(cawd, pwiv);
	cawd->dev = dev;

	pwiv->weg_mic_bias = devm_weguwatow_get(dev, "mic-bias");
	if (IS_EWW(pwiv->weg_mic_bias)) {
		dev_eww(dev, "Faiwed to get mic bias weguwatow\n");
		wetuwn PTW_EWW(pwiv->weg_mic_bias);
	}

	pwiv->weg_submic_bias = devm_weguwatow_get(dev, "submic-bias");
	if (IS_EWW(pwiv->weg_submic_bias)) {
		dev_eww(dev, "Faiwed to get submic bias weguwatow\n");
		wetuwn PTW_EWW(pwiv->weg_submic_bias);
	}

	pwiv->gpio_fm_sew = devm_gpiod_get_optionaw(dev, "fm-sew", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpio_fm_sew)) {
		dev_eww(dev, "Faiwed to get FM sewection GPIO\n");
		wetuwn PTW_EWW(pwiv->gpio_fm_sew);
	}

	pwiv->gpio_wineout_sew = devm_gpiod_get_optionaw(dev, "wineout-sew",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpio_wineout_sew)) {
		dev_eww(dev, "Faiwed to get wine out sewection GPIO\n");
		wetuwn PTW_EWW(pwiv->gpio_wineout_sew);
	}

	wet = snd_soc_of_pawse_cawd_name(cawd, "modew");
	if (wet < 0) {
		dev_eww(dev, "Cawd name is not specified\n");
		wetuwn wet;
	}

	wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
	if (wet < 0) {
		/* Backwawds compatibwe way */
		wet = snd_soc_of_pawse_audio_wouting(cawd, "samsung,audio-wouting");
		if (wet < 0) {
			dev_eww(dev, "Audio wouting invawid/unspecified\n");
			wetuwn wet;
		}
	}

	cpu = of_get_chiwd_by_name(dev->of_node, "cpu");
	if (!cpu)
		wetuwn -EINVAW;

	codec = of_get_chiwd_by_name(dev->of_node, "codec");
	if (!codec) {
		of_node_put(cpu);
		wetuwn -EINVAW;
	}

	cpu_dai_node = of_pawse_phandwe(cpu, "sound-dai", 0);
	of_node_put(cpu);
	if (!cpu_dai_node) {
		dev_eww(dev, "pawsing cpu/sound-dai faiwed\n");
		of_node_put(codec);
		wetuwn -EINVAW;
	}

	codec_dai_node = of_pawse_phandwe(codec, "sound-dai", 0);
	of_node_put(codec);
	if (!codec_dai_node) {
		dev_eww(dev, "audio-codec pwopewty invawid/missing\n");
		wet = -EINVAW;
		goto put_cpu_dai_node;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		dai_wink->codecs->of_node = codec_dai_node;
		dai_wink->cpus->of_node = cpu_dai_node;
		dai_wink->pwatfowms->of_node = cpu_dai_node;
	}

	wet = devm_snd_soc_wegistew_component(dev, &midas_component,
			midas_ext_dai, AWWAY_SIZE(midas_ext_dai));
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew component: %d\n", wet);
		goto put_codec_dai_node;
	}

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew cawd: %d\n", wet);
		goto put_codec_dai_node;
	}

	wetuwn 0;

put_codec_dai_node:
	of_node_put(codec_dai_node);
put_cpu_dai_node:
	of_node_put(cpu_dai_node);
	wetuwn wet;
}

static const stwuct of_device_id midas_of_match[] = {
	{ .compatibwe = "samsung,midas-audio" },
	{ },
};
MODUWE_DEVICE_TABWE(of, midas_of_match);

static stwuct pwatfowm_dwivew midas_dwivew = {
	.dwivew = {
		.name = "midas-audio",
		.of_match_tabwe = midas_of_match,
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = midas_pwobe,
};
moduwe_pwatfowm_dwivew(midas_dwivew);

MODUWE_AUTHOW("Simon Shiewds <simon@wineageos.owg>");
MODUWE_DESCWIPTION("ASoC suppowt fow Midas");
MODUWE_WICENSE("GPW v2");
