// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt8173-max98090.c  --  MT8173 MAX98090 AWSA SoC machine dwivew
 *
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Kowo Chen <kowo.chen@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude "../../codecs/max98090.h"

static stwuct snd_soc_jack mt8173_max98090_jack;

static stwuct snd_soc_jack_pin mt8173_max98090_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
};

static const stwuct snd_soc_dapm_widget mt8173_max98090_widgets[] = {
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_MIC("Int Mic", NUWW),
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute mt8173_max98090_woutes[] = {
	{"Speakew", NUWW, "SPKW"},
	{"Speakew", NUWW, "SPKW"},
	{"DMICW", NUWW, "Int Mic"},
	{"Headphone", NUWW, "HPW"},
	{"Headphone", NUWW, "HPW"},
	{"Headset Mic", NUWW, "MICBIAS"},
	{"IN34", NUWW, "Headset Mic"},
};

static const stwuct snd_kcontwow_new mt8173_max98090_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static int mt8173_max98090_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	wetuwn snd_soc_dai_set_syscwk(codec_dai, 0, pawams_wate(pawams) * 256,
				      SND_SOC_CWOCK_IN);
}

static const stwuct snd_soc_ops mt8173_max98090_ops = {
	.hw_pawams = mt8173_max98090_hw_pawams,
};

static int mt8173_max98090_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	int wet;
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wuntime, 0)->component;

	/* enabwe jack detection */
	wet = snd_soc_cawd_jack_new_pins(cawd, "Headphone", SND_JACK_HEADSET,
					 &mt8173_max98090_jack,
					 mt8173_max98090_jack_pins,
					 AWWAY_SIZE(mt8173_max98090_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "Can't cweate a new Jack %d\n", wet);
		wetuwn wet;
	}

	wetuwn max98090_mic_detect(component, &mt8173_max98090_jack);
}

SND_SOC_DAIWINK_DEFS(pwayback,
	DAIWINK_COMP_AWWAY(COMP_CPU("DW1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe,
	DAIWINK_COMP_AWWAY(COMP_CPU("VUW")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(hifi,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "HiFi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* Digitaw audio intewface gwue - connects codec <---> CPU */
static stwuct snd_soc_dai_wink mt8173_max98090_dais[] = {
	/* Fwont End DAI winks */
	{
		.name = "MAX98090 Pwayback",
		.stweam_name = "MAX98090 Pwayback",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback),
	},
	{
		.name = "MAX98090 Captuwe",
		.stweam_name = "MAX98090 Captuwe",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe),
	},
	/* Back End DAI winks */
	{
		.name = "Codec",
		.no_pcm = 1,
		.init = mt8173_max98090_init,
		.ops = &mt8173_max98090_ops,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(hifi),
	},
};

static stwuct snd_soc_cawd mt8173_max98090_cawd = {
	.name = "mt8173-max98090",
	.ownew = THIS_MODUWE,
	.dai_wink = mt8173_max98090_dais,
	.num_winks = AWWAY_SIZE(mt8173_max98090_dais),
	.contwows = mt8173_max98090_contwows,
	.num_contwows = AWWAY_SIZE(mt8173_max98090_contwows),
	.dapm_widgets = mt8173_max98090_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8173_max98090_widgets),
	.dapm_woutes = mt8173_max98090_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8173_max98090_woutes),
};

static int mt8173_max98090_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &mt8173_max98090_cawd;
	stwuct device_node *codec_node, *pwatfowm_node;
	stwuct snd_soc_dai_wink *dai_wink;
	int wet, i;

	pwatfowm_node = of_pawse_phandwe(pdev->dev.of_node,
					 "mediatek,pwatfowm", 0);
	if (!pwatfowm_node) {
		dev_eww(&pdev->dev, "Pwopewty 'pwatfowm' missing ow invawid\n");
		wetuwn -EINVAW;
	}
	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->pwatfowms->name)
			continue;
		dai_wink->pwatfowms->of_node = pwatfowm_node;
	}

	codec_node = of_pawse_phandwe(pdev->dev.of_node,
				      "mediatek,audio-codec", 0);
	if (!codec_node) {
		dev_eww(&pdev->dev,
			"Pwopewty 'audio-codec' missing ow invawid\n");
		wet = -EINVAW;
		goto put_pwatfowm_node;
	}
	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->codecs->name)
			continue;
		dai_wink->codecs->of_node = codec_node;
	}
	cawd->dev = &pdev->dev;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);

	of_node_put(codec_node);

put_pwatfowm_node:
	of_node_put(pwatfowm_node);
	wetuwn wet;
}

static const stwuct of_device_id mt8173_max98090_dt_match[] = {
	{ .compatibwe = "mediatek,mt8173-max98090", },
	{ }
};
MODUWE_DEVICE_TABWE(of, mt8173_max98090_dt_match);

static stwuct pwatfowm_dwivew mt8173_max98090_dwivew = {
	.dwivew = {
		   .name = "mt8173-max98090",
		   .of_match_tabwe = mt8173_max98090_dt_match,
		   .pm = &snd_soc_pm_ops,
	},
	.pwobe = mt8173_max98090_dev_pwobe,
};

moduwe_pwatfowm_dwivew(mt8173_max98090_dwivew);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT8173 MAX98090 AWSA SoC machine dwivew");
MODUWE_AUTHOW("Kowo Chen <kowo.chen@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:mt8173-max98090");

