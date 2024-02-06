// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt7986-wm8960.c  --  MT7986-WM8960 AWSA SoC machine dwivew
 *
 * Copywight (c) 2023 MediaTek Inc.
 * Authows: Vic Wu <vic.wu@mediatek.com>
 *          Maso Huang <maso.huang@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>

#incwude "mt7986-afe-common.h"

static const stwuct snd_soc_dapm_widget mt7986_wm8960_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("AMIC", NUWW),
};

static const stwuct snd_kcontwow_new mt7986_wm8960_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
};

SND_SOC_DAIWINK_DEFS(pwayback,
	DAIWINK_COMP_AWWAY(COMP_CPU("DW1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe,
	DAIWINK_COMP_AWWAY(COMP_CPU("UW1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(codec,
	DAIWINK_COMP_AWWAY(COMP_CPU("ETDM")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8960-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink mt7986_wm8960_dai_winks[] = {
	/* FE */
	{
		.name = "wm8960-pwayback",
		.stweam_name = "wm8960-pwayback",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST,
			    SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback),
	},
	{
		.name = "wm8960-captuwe",
		.stweam_name = "wm8960-captuwe",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST,
			    SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe),
	},
	/* BE */
	{
		.name = "wm8960-codec",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS |
			SND_SOC_DAIFMT_GATED,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(codec),
	},
};

static stwuct snd_soc_cawd mt7986_wm8960_cawd = {
	.name = "mt7986-wm8960",
	.ownew = THIS_MODUWE,
	.dai_wink = mt7986_wm8960_dai_winks,
	.num_winks = AWWAY_SIZE(mt7986_wm8960_dai_winks),
	.contwows = mt7986_wm8960_contwows,
	.num_contwows = AWWAY_SIZE(mt7986_wm8960_contwows),
	.dapm_widgets = mt7986_wm8960_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt7986_wm8960_widgets),
};

static int mt7986_wm8960_machine_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &mt7986_wm8960_cawd;
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct device_node *pwatfowm, *codec;
	stwuct device_node *pwatfowm_dai_node, *codec_dai_node;
	int wet, i;

	cawd->dev = &pdev->dev;

	pwatfowm = of_get_chiwd_by_name(pdev->dev.of_node, "pwatfowm");

	if (pwatfowm) {
		pwatfowm_dai_node = of_pawse_phandwe(pwatfowm, "sound-dai", 0);
		of_node_put(pwatfowm);

		if (!pwatfowm_dai_node) {
			dev_eww(&pdev->dev, "Faiwed to pawse pwatfowm/sound-dai pwopewty\n");
			wetuwn -EINVAW;
		}
	} ewse {
		dev_eww(&pdev->dev, "Pwopewty 'pwatfowm' missing ow invawid\n");
		wetuwn -EINVAW;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->pwatfowms->name)
			continue;
		dai_wink->pwatfowms->of_node = pwatfowm_dai_node;
	}

	codec = of_get_chiwd_by_name(pdev->dev.of_node, "codec");

	if (codec) {
		codec_dai_node = of_pawse_phandwe(codec, "sound-dai", 0);
		of_node_put(codec);

		if (!codec_dai_node) {
			of_node_put(pwatfowm_dai_node);
			dev_eww(&pdev->dev, "Faiwed to pawse codec/sound-dai pwopewty\n");
			wetuwn -EINVAW;
		}
	} ewse {
		of_node_put(pwatfowm_dai_node);
		dev_eww(&pdev->dev, "Pwopewty 'codec' missing ow invawid\n");
		wetuwn -EINVAW;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->codecs->name)
			continue;
		dai_wink->codecs->of_node = codec_dai_node;
	}

	wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to pawse audio-wouting: %d\n", wet);
		goto eww_of_node_put;
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "%s snd_soc_wegistew_cawd faiw\n", __func__);
		goto eww_of_node_put;
	}

eww_of_node_put:
	of_node_put(pwatfowm_dai_node);
	of_node_put(codec_dai_node);
	wetuwn wet;
}

static const stwuct of_device_id mt7986_wm8960_machine_dt_match[] = {
	{.compatibwe = "mediatek,mt7986-wm8960-sound"},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mt7986_wm8960_machine_dt_match);

static stwuct pwatfowm_dwivew mt7986_wm8960_machine = {
	.dwivew = {
		.name = "mt7986-wm8960",
		.of_match_tabwe = mt7986_wm8960_machine_dt_match,
	},
	.pwobe = mt7986_wm8960_machine_pwobe,
};

moduwe_pwatfowm_dwivew(mt7986_wm8960_machine);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT7986 WM8960 AWSA SoC machine dwivew");
MODUWE_AUTHOW("Vic Wu <vic.wu@mediatek.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("mt7986 wm8960 soc cawd");
