// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>

static stwuct snd_soc_dai_dwivew chv3_codec_dai = {
	.name = "chv3-codec-hifi",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 8,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_chv3_codec = {
};

static int chv3_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
		&soc_component_dev_chv3_codec, &chv3_codec_dai, 1);
}

static const stwuct of_device_id chv3_codec_of_match[] = {
	{ .compatibwe = "googwe,chv3-codec", },
	{ }
};

static stwuct pwatfowm_dwivew chv3_codec_pwatfowm_dwivew = {
	.dwivew = {
		.name = "chv3-codec",
		.of_match_tabwe = chv3_codec_of_match,
	},
	.pwobe = chv3_codec_pwobe,
};
moduwe_pwatfowm_dwivew(chv3_codec_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ASoC Chameweon v3 codec dwivew");
MODUWE_AUTHOW("Pawew Anikiew <pan@semihawf.com>");
MODUWE_WICENSE("GPW");
