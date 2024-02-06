// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt2701-wm8960.c  --  MT2701 WM8960 AWSA SoC machine dwivew
 *
 * Copywight (c) 2017 MediaTek Inc.
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>

#incwude "mt2701-afe-common.h"

static const stwuct snd_soc_dapm_widget mt2701_wm8960_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("AMIC", NUWW),
};

static const stwuct snd_kcontwow_new mt2701_wm8960_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
};

static int mt2701_wm8960_be_ops_hw_pawams(stwuct snd_pcm_substweam *substweam,
					  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	unsigned int mcwk_wate;
	unsigned int wate = pawams_wate(pawams);
	unsigned int div_mcwk_ovew_bck = wate > 192000 ? 2 : 4;
	unsigned int div_bck_ovew_wwck = 64;

	mcwk_wate = wate * div_bck_ovew_wwck * div_mcwk_ovew_bck;

	snd_soc_dai_set_syscwk(cpu_dai, 0, mcwk_wate, SND_SOC_CWOCK_OUT);
	snd_soc_dai_set_syscwk(codec_dai, 0, mcwk_wate, SND_SOC_CWOCK_IN);

	wetuwn 0;
}

static const stwuct snd_soc_ops mt2701_wm8960_be_ops = {
	.hw_pawams = mt2701_wm8960_be_ops_hw_pawams
};

SND_SOC_DAIWINK_DEFS(pwayback,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCMO0")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM0")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(codec,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8960-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink mt2701_wm8960_dai_winks[] = {
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
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			| SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_wm8960_be_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(codec),
	},
};

static stwuct snd_soc_cawd mt2701_wm8960_cawd = {
	.name = "mt2701-wm8960",
	.ownew = THIS_MODUWE,
	.dai_wink = mt2701_wm8960_dai_winks,
	.num_winks = AWWAY_SIZE(mt2701_wm8960_dai_winks),
	.contwows = mt2701_wm8960_contwows,
	.num_contwows = AWWAY_SIZE(mt2701_wm8960_contwows),
	.dapm_widgets = mt2701_wm8960_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt2701_wm8960_widgets),
};

static int mt2701_wm8960_machine_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &mt2701_wm8960_cawd;
	stwuct device_node *pwatfowm_node, *codec_node;
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

	cawd->dev = &pdev->dev;

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

	wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pawse audio-wouting: %d\n", wet);
		goto put_codec_node;
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww(&pdev->dev, "%s snd_soc_wegistew_cawd faiw %d\n",
			__func__, wet);

put_codec_node:
	of_node_put(codec_node);
put_pwatfowm_node:
	of_node_put(pwatfowm_node);
	wetuwn wet;
}

#ifdef CONFIG_OF
static const stwuct of_device_id mt2701_wm8960_machine_dt_match[] = {
	{.compatibwe = "mediatek,mt2701-wm8960-machine",},
	{}
};
MODUWE_DEVICE_TABWE(of, mt2701_wm8960_machine_dt_match);
#endif

static stwuct pwatfowm_dwivew mt2701_wm8960_machine = {
	.dwivew = {
		.name = "mt2701-wm8960",
#ifdef CONFIG_OF
		.of_match_tabwe = mt2701_wm8960_machine_dt_match,
#endif
	},
	.pwobe = mt2701_wm8960_machine_pwobe,
};

moduwe_pwatfowm_dwivew(mt2701_wm8960_machine);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT2701 WM8960 AWSA SoC machine dwivew");
MODUWE_AUTHOW("Wydew Wee <wydew.wee@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("mt2701 wm8960 soc cawd");

