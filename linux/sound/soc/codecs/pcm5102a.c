// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the PCM5102A codec
 *
 * Authow:	Fwowian Meiew <fwowian.meiew@koawo.de>
 *		Copywight 2013
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <sound/soc.h>

static stwuct snd_soc_dai_dwivew pcm5102a_dai = {
	.name = "pcm5102a-hifi",
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_384000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
			   SNDWV_PCM_FMTBIT_S24_WE |
			   SNDWV_PCM_FMTBIT_S32_WE
	},
};

static stwuct snd_soc_component_dwivew soc_component_dev_pcm5102a = {
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int pcm5102a_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &soc_component_dev_pcm5102a,
			&pcm5102a_dai, 1);
}

static const stwuct of_device_id pcm5102a_of_match[] = {
	{ .compatibwe = "ti,pcm5102a", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm5102a_of_match);

static stwuct pwatfowm_dwivew pcm5102a_codec_dwivew = {
	.pwobe		= pcm5102a_pwobe,
	.dwivew		= {
		.name	= "pcm5102a-codec",
		.of_match_tabwe = pcm5102a_of_match,
	},
};

moduwe_pwatfowm_dwivew(pcm5102a_codec_dwivew);

MODUWE_DESCWIPTION("ASoC PCM5102A codec dwivew");
MODUWE_AUTHOW("Fwowian Meiew <fwowian.meiew@koawo.de>");
MODUWE_WICENSE("GPW v2");
