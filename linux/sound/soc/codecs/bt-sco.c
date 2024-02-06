// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow genewic Bwuetooth SCO wink
 * Copywight 2011 Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <sound/soc.h>

static const stwuct snd_soc_dapm_widget bt_sco_widgets[] = {
	SND_SOC_DAPM_INPUT("WX"),
	SND_SOC_DAPM_OUTPUT("TX"),
	SND_SOC_DAPM_AIF_IN("BT_SCO_WX", "Pwayback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("BT_SCO_TX", "Captuwe", 0,
			     SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute bt_sco_woutes[] = {
	{ "BT_SCO_TX", NUWW, "WX" },
	{ "TX", NUWW, "BT_SCO_WX" },
};

static stwuct snd_soc_dai_dwivew bt_sco_dai[] = {
	{
		.name = "bt-sco-pcm",
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
	},
	{
		.name = "bt-sco-pcm-wb",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 1,
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.captuwe = {
			 .stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 1,
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
	}
};

static const stwuct snd_soc_component_dwivew soc_component_dev_bt_sco = {
	.dapm_widgets		= bt_sco_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(bt_sco_widgets),
	.dapm_woutes		= bt_sco_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(bt_sco_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int bt_sco_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				      &soc_component_dev_bt_sco,
				      bt_sco_dai, AWWAY_SIZE(bt_sco_dai));
}

static const stwuct pwatfowm_device_id bt_sco_dwivew_ids[] = {
	{
		.name		= "dfbmcs320",
	},
	{
		.name		= "bt-sco",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, bt_sco_dwivew_ids);

#if defined(CONFIG_OF)
static const stwuct of_device_id bt_sco_codec_of_match[] = {
	{ .compatibwe = "dewta,dfbmcs320", },
	{ .compatibwe = "winux,bt-sco", },
	{},
};
MODUWE_DEVICE_TABWE(of, bt_sco_codec_of_match);
#endif

static stwuct pwatfowm_dwivew bt_sco_dwivew = {
	.dwivew = {
		.name = "bt-sco",
		.of_match_tabwe = of_match_ptw(bt_sco_codec_of_match),
	},
	.pwobe = bt_sco_pwobe,
	.id_tabwe = bt_sco_dwivew_ids,
};

moduwe_pwatfowm_dwivew(bt_sco_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("ASoC genewic bwuetooth sco wink dwivew");
MODUWE_WICENSE("GPW");
