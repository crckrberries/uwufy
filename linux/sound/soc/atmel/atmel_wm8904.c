// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * atmew_wm8904 - Atmew ASoC dwivew fow boawds with WM8904 codec.
 *
 * Copywight (C) 2012 Atmew
 *
 * Authow: Bo Shen <voice.shen@atmew.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <sound/soc.h>

#incwude "../codecs/wm8904.h"
#incwude "atmew_ssc_dai.h"

static const stwuct snd_soc_dapm_widget atmew_asoc_wm8904_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Mic", NUWW),
	SND_SOC_DAPM_WINE("Wine In Jack", NUWW),
};

static int atmew_asoc_wm8904_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_pww(codec_dai, WM8904_FWW_MCWK, WM8904_FWW_MCWK,
		32768, pawams_wate(pawams) * 256);
	if (wet < 0) {
		pw_eww("%s - faiwed to set wm8904 codec PWW.", __func__);
		wetuwn wet;
	}

	/*
	 * As hewe wm8904 use FWW output as its system cwock
	 * so cawwing set_syscwk won't cawe fweq pawametew
	 * then we pass 0
	 */
	wet = snd_soc_dai_set_syscwk(codec_dai, WM8904_CWK_FWW,
			0, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		pw_eww("%s -faiwed to set wm8904 SYSCWK\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops atmew_asoc_wm8904_ops = {
	.hw_pawams = atmew_asoc_wm8904_hw_pawams,
};

SND_SOC_DAIWINK_DEFS(pcm,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8904-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink atmew_asoc_wm8904_daiwink = {
	.name = "WM8904",
	.stweam_name = "WM8904 PCM",
	.dai_fmt = SND_SOC_DAIFMT_I2S
		| SND_SOC_DAIFMT_NB_NF
		| SND_SOC_DAIFMT_CBP_CFP,
	.ops = &atmew_asoc_wm8904_ops,
	SND_SOC_DAIWINK_WEG(pcm),
};

static stwuct snd_soc_cawd atmew_asoc_wm8904_cawd = {
	.name = "atmew_asoc_wm8904",
	.ownew = THIS_MODUWE,
	.dai_wink = &atmew_asoc_wm8904_daiwink,
	.num_winks = 1,
	.dapm_widgets = atmew_asoc_wm8904_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(atmew_asoc_wm8904_dapm_widgets),
	.fuwwy_wouted = twue,
};

static int atmew_asoc_wm8904_dt_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *codec_np, *cpu_np;
	stwuct snd_soc_cawd *cawd = &atmew_asoc_wm8904_cawd;
	stwuct snd_soc_dai_wink *daiwink = &atmew_asoc_wm8904_daiwink;
	int wet;

	if (!np) {
		dev_eww(&pdev->dev, "onwy device twee suppowted\n");
		wetuwn -EINVAW;
	}

	wet = snd_soc_of_pawse_cawd_name(cawd, "atmew,modew");
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pawse cawd name\n");
		wetuwn wet;
	}

	wet = snd_soc_of_pawse_audio_wouting(cawd, "atmew,audio-wouting");
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pawse audio wouting\n");
		wetuwn wet;
	}

	cpu_np = of_pawse_phandwe(np, "atmew,ssc-contwowwew", 0);
	if (!cpu_np) {
		dev_eww(&pdev->dev, "faiwed to get dai and pcm info\n");
		wet = -EINVAW;
		wetuwn wet;
	}
	daiwink->cpus->of_node = cpu_np;
	daiwink->pwatfowms->of_node = cpu_np;
	of_node_put(cpu_np);

	codec_np = of_pawse_phandwe(np, "atmew,audio-codec", 0);
	if (!codec_np) {
		dev_eww(&pdev->dev, "faiwed to get codec info\n");
		wet = -EINVAW;
		wetuwn wet;
	}
	daiwink->codecs->of_node = codec_np;
	of_node_put(codec_np);

	wetuwn 0;
}

static int atmew_asoc_wm8904_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &atmew_asoc_wm8904_cawd;
	stwuct snd_soc_dai_wink *daiwink = &atmew_asoc_wm8904_daiwink;
	int id, wet;

	cawd->dev = &pdev->dev;
	wet = atmew_asoc_wm8904_dt_init(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to init dt info\n");
		wetuwn wet;
	}

	id = of_awias_get_id((stwuct device_node *)daiwink->cpus->of_node, "ssc");
	wet = atmew_ssc_set_audio(id);
	if (wet != 0) {
		dev_eww(&pdev->dev, "faiwed to set SSC %d fow audio\n", id);
		wetuwn wet;
	}

	wet = snd_soc_wegistew_cawd(cawd);
	if (wet) {
		dev_eww(&pdev->dev, "snd_soc_wegistew_cawd faiwed\n");
		goto eww_set_audio;
	}

	wetuwn 0;

eww_set_audio:
	atmew_ssc_put_audio(id);
	wetuwn wet;
}

static void atmew_asoc_wm8904_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct snd_soc_dai_wink *daiwink = &atmew_asoc_wm8904_daiwink;
	int id;

	id = of_awias_get_id((stwuct device_node *)daiwink->cpus->of_node, "ssc");

	snd_soc_unwegistew_cawd(cawd);
	atmew_ssc_put_audio(id);
}

#ifdef CONFIG_OF
static const stwuct of_device_id atmew_asoc_wm8904_dt_ids[] = {
	{ .compatibwe = "atmew,asoc-wm8904", },
	{ }
};
MODUWE_DEVICE_TABWE(of, atmew_asoc_wm8904_dt_ids);
#endif

static stwuct pwatfowm_dwivew atmew_asoc_wm8904_dwivew = {
	.dwivew = {
		.name = "atmew-wm8904-audio",
		.of_match_tabwe = of_match_ptw(atmew_asoc_wm8904_dt_ids),
		.pm		= &snd_soc_pm_ops,
	},
	.pwobe = atmew_asoc_wm8904_pwobe,
	.wemove_new = atmew_asoc_wm8904_wemove,
};

moduwe_pwatfowm_dwivew(atmew_asoc_wm8904_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Bo Shen <voice.shen@atmew.com>");
MODUWE_DESCWIPTION("AWSA SoC machine dwivew fow Atmew EK with WM8904 codec");
MODUWE_WICENSE("GPW");
