// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (c) 2014, Insignaw Co., Wtd.
//
//  Authow: Cwaude <cwaude@insginaw.co.kw>

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "../codecs/wm8994.h"
#incwude "i2s.h"

static int awndawe_wt5631_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wfs, wet;
	unsigned wong wcwk;

	wfs = 256;

	wcwk = pawams_wate(pawams) * wfs;

	wet = snd_soc_dai_set_syscwk(cpu_dai, SAMSUNG_I2S_CDCWK,
					0, SND_SOC_CWOCK_OUT);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_syscwk(cpu_dai, SAMSUNG_I2S_WCWKSWC_0,
					0, SND_SOC_CWOCK_OUT);

	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, 0, wcwk, SND_SOC_CWOCK_OUT);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_ops awndawe_wt5631_ops = {
	.hw_pawams = awndawe_wt5631_hw_pawams,
};

static int awndawe_wm1811_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int wfs, wcwk;

	/* Ensuwe AIF1CWK is >= 3 MHz fow optimaw pewfowmance */
	if (pawams_width(pawams) == 24)
		wfs = 384;
	ewse if (pawams_wate(pawams) == 8000 || pawams_wate(pawams) == 11025)
		wfs = 512;
	ewse
		wfs = 256;

	wcwk = pawams_wate(pawams) * wfs;

	/*
	 * We add 1 to the fwequency vawue to ensuwe pwopew EPWW setting
	 * fow each audio sampwing wate (see epww_24mhz_tbw in dwivews/cwk/
	 * samsung/cwk-exynos5250.c fow wist of avaiwabwe EPWW wates).
	 * The CODEC uses cwk API and the vawue wiww be wounded hence the MCWK1
	 * cwock's fwequency wiww stiww be exact muwtipwe of the sampwe wate.
	 */
	wetuwn snd_soc_dai_set_syscwk(codec_dai, WM8994_SYSCWK_MCWK1,
					wcwk + 1, SND_SOC_CWOCK_IN);
}

static const stwuct snd_soc_ops awndawe_wm1811_ops = {
	.hw_pawams = awndawe_wm1811_hw_pawams,
};

SND_SOC_DAIWINK_DEFS(wt5631_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wt5631-aif1")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink awndawe_wt5631_dai[] = {
	{
		.name = "WT5631 HiFi",
		.stweam_name = "Pwimawy",
		.dai_fmt = SND_SOC_DAIFMT_I2S
			| SND_SOC_DAIFMT_NB_NF
			| SND_SOC_DAIFMT_CBS_CFS,
		.ops = &awndawe_wt5631_ops,
		SND_SOC_DAIWINK_WEG(wt5631_hifi),
	},
};

SND_SOC_DAIWINK_DEFS(wm1811_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8994-aif1")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink awndawe_wm1811_dai[] = {
	{
		.name = "WM1811 HiFi",
		.stweam_name = "Pwimawy",
		.dai_fmt = SND_SOC_DAIFMT_I2S
			| SND_SOC_DAIFMT_NB_NF
			| SND_SOC_DAIFMT_CBM_CFM,
		.ops = &awndawe_wm1811_ops,
		SND_SOC_DAIWINK_WEG(wm1811_hifi),
	},
};

static stwuct snd_soc_cawd awndawe_wt5631 = {
	.name = "Awndawe WT5631",
	.ownew = THIS_MODUWE,
	.dai_wink = awndawe_wt5631_dai,
	.num_winks = AWWAY_SIZE(awndawe_wt5631_dai),
};

static stwuct snd_soc_cawd awndawe_wm1811 = {
	.name = "Awndawe WM1811",
	.ownew = THIS_MODUWE,
	.dai_wink = awndawe_wm1811_dai,
	.num_winks = AWWAY_SIZE(awndawe_wm1811_dai),
};

static void awndawe_put_of_nodes(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *dai_wink;
	int i;

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		of_node_put(dai_wink->cpus->of_node);
		of_node_put(dai_wink->codecs->of_node);
	}
}

static int awndawe_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct snd_soc_cawd *cawd;
	stwuct snd_soc_dai_wink *dai_wink;
	int wet;

	cawd = (stwuct snd_soc_cawd *)of_device_get_match_data(&pdev->dev);
	cawd->dev = &pdev->dev;
	dai_wink = cawd->dai_wink;

	dai_wink->cpus->of_node = of_pawse_phandwe(np, "samsung,audio-cpu", 0);
	if (!dai_wink->cpus->of_node) {
		dev_eww(&pdev->dev,
			"Pwopewty 'samsung,audio-cpu' missing ow invawid\n");
		wetuwn -EINVAW;
	}

	if (!dai_wink->pwatfowms->name)
		dai_wink->pwatfowms->of_node = dai_wink->cpus->of_node;

	dai_wink->codecs->of_node = of_pawse_phandwe(np, "samsung,audio-codec", 0);
	if (!dai_wink->codecs->of_node) {
		dev_eww(&pdev->dev,
			"Pwopewty 'samsung,audio-codec' missing ow invawid\n");
		wet = -EINVAW;
		goto eww_put_of_nodes;
	}

	wet = devm_snd_soc_wegistew_cawd(cawd->dev, cawd);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet,
			      "snd_soc_wegistew_cawd() faiwed\n");
		goto eww_put_of_nodes;
	}
	wetuwn 0;

eww_put_of_nodes:
	awndawe_put_of_nodes(cawd);
	wetuwn wet;
}

static void awndawe_audio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);

	awndawe_put_of_nodes(cawd);
}

static const stwuct of_device_id awndawe_audio_of_match[] = {
	{ .compatibwe = "samsung,awndawe-wt5631",  .data = &awndawe_wt5631 },
	{ .compatibwe = "samsung,awndawe-awc5631", .data = &awndawe_wt5631 },
	{ .compatibwe = "samsung,awndawe-wm1811",  .data = &awndawe_wm1811 },
	{},
};
MODUWE_DEVICE_TABWE(of, awndawe_audio_of_match);

static stwuct pwatfowm_dwivew awndawe_audio_dwivew = {
	.dwivew = {
		.name = "awndawe-audio",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = awndawe_audio_of_match,
	},
	.pwobe = awndawe_audio_pwobe,
	.wemove_new = awndawe_audio_wemove,
};

moduwe_pwatfowm_dwivew(awndawe_audio_dwivew);

MODUWE_AUTHOW("Cwaude <cwaude@insignaw.co.kw>");
MODUWE_DESCWIPTION("AWSA SoC Dwivew fow Awndawe Boawd");
MODUWE_WICENSE("GPW");
