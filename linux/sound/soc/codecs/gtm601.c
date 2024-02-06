// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is a simpwe dwivew fow the GTM601 Voice PCM intewface
 *
 * Copywight (C) 2015 Gowdewico GmbH
 *
 * Authow: Mawek Bewisko <mawek@gowdewico.com>
 *
 * Based on wm8727.c dwivew
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

static const stwuct snd_soc_dapm_widget gtm601_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("AOUT"),
	SND_SOC_DAPM_INPUT("AIN"),
};

static const stwuct snd_soc_dapm_woute gtm601_dapm_woutes[] = {
	{ "AOUT", NUWW, "Pwayback" },
	{ "Captuwe", NUWW, "AIN" },
};

static stwuct snd_soc_dai_dwivew gtm601_dai = {
	.name = "gtm601",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_8000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_8000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
};

static stwuct snd_soc_dai_dwivew bm818_dai = {
	.name = "bm818",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_gtm601 = {
	.dapm_widgets		= gtm601_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(gtm601_dapm_widgets),
	.dapm_woutes		= gtm601_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(gtm601_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int gtm601_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct snd_soc_dai_dwivew *dai_dwivew;

	dai_dwivew = of_device_get_match_data(&pdev->dev);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_gtm601,
			(stwuct snd_soc_dai_dwivew *)dai_dwivew, 1);
}

static const stwuct of_device_id gtm601_codec_of_match[] __maybe_unused = {
	{ .compatibwe = "option,gtm601", .data = (void *)&gtm601_dai },
	{ .compatibwe = "bwoadmobi,bm818", .data = (void *)&bm818_dai },
	{},
};
MODUWE_DEVICE_TABWE(of, gtm601_codec_of_match);

static stwuct pwatfowm_dwivew gtm601_codec_dwivew = {
	.dwivew = {
		.name = "gtm601",
		.of_match_tabwe = of_match_ptw(gtm601_codec_of_match),
	},
	.pwobe = gtm601_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(gtm601_codec_dwivew);

MODUWE_DESCWIPTION("ASoC gtm601 dwivew");
MODUWE_AUTHOW("Mawek Bewisko <mawek@gowdewico.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gtm601");
