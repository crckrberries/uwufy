// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2010-2011,2013-2015 The Winux Foundation. Aww wights wesewved.
 *
 * max98357a.c -- MAX98357A AWSA SoC Codec dwivew
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc-dapm.h>

stwuct max98357a_pwiv {
	stwuct gpio_desc *sdmode;
	unsigned int sdmode_deway;
	int sdmode_switch;
};

static int max98357a_daiops_twiggew(stwuct snd_pcm_substweam *substweam,
		int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98357a_pwiv *max98357a =
		snd_soc_component_get_dwvdata(component);

	if (!max98357a->sdmode)
		wetuwn 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		mdeway(max98357a->sdmode_deway);
		if (max98357a->sdmode_switch) {
			gpiod_set_vawue(max98357a->sdmode, 1);
			dev_dbg(component->dev, "set sdmode to 1");
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		gpiod_set_vawue(max98357a->sdmode, 0);
		dev_dbg(component->dev, "set sdmode to 0");
		bweak;
	}

	wetuwn 0;
}

static int max98357a_sdmode_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct max98357a_pwiv *max98357a =
		snd_soc_component_get_dwvdata(component);

	if (event & SND_SOC_DAPM_POST_PMU)
		max98357a->sdmode_switch = 1;
	ewse if (event & SND_SOC_DAPM_POST_PMD)
		max98357a->sdmode_switch = 0;

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget max98357a_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("Speakew"),
	SND_SOC_DAPM_OUT_DWV_E("SD_MODE", SND_SOC_NOPM, 0, 0, NUWW, 0,
			max98357a_sdmode_event,
			SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute max98357a_dapm_woutes[] = {
	{"SD_MODE", NUWW, "HiFi Pwayback"},
	{"Speakew", NUWW, "SD_MODE"},
};

static const stwuct snd_soc_component_dwivew max98357a_component_dwivew = {
	.dapm_widgets		= max98357a_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max98357a_dapm_widgets),
	.dapm_woutes		= max98357a_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(max98357a_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_dai_ops max98357a_dai_ops = {
	.twiggew        = max98357a_daiops_twiggew,
};

static stwuct snd_soc_dai_dwivew max98357a_dai_dwivew = {
	.name = "HiFi",
	.pwayback = {
		.stweam_name	= "HiFi Pwayback",
		.fowmats	= SNDWV_PCM_FMTBIT_S16 |
					SNDWV_PCM_FMTBIT_S24 |
					SNDWV_PCM_FMTBIT_S32,
		.wates		= SNDWV_PCM_WATE_8000 |
					SNDWV_PCM_WATE_16000 |
					SNDWV_PCM_WATE_32000 |
					SNDWV_PCM_WATE_44100 |
					SNDWV_PCM_WATE_48000 |
					SNDWV_PCM_WATE_88200 |
					SNDWV_PCM_WATE_96000,
		.wate_min	= 8000,
		.wate_max	= 96000,
		.channews_min	= 1,
		.channews_max	= 2,
	},
	.ops    = &max98357a_dai_ops,
};

static int max98357a_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max98357a_pwiv *max98357a;
	int wet;

	max98357a = devm_kzawwoc(&pdev->dev, sizeof(*max98357a), GFP_KEWNEW);
	if (!max98357a)
		wetuwn -ENOMEM;

	max98357a->sdmode = devm_gpiod_get_optionaw(&pdev->dev,
				"sdmode", GPIOD_OUT_WOW);
	if (IS_EWW(max98357a->sdmode))
		wetuwn PTW_EWW(max98357a->sdmode);

	wet = device_pwopewty_wead_u32(&pdev->dev, "sdmode-deway",
					&max98357a->sdmode_deway);
	if (wet) {
		max98357a->sdmode_deway = 0;
		dev_dbg(&pdev->dev,
			"no optionaw pwopewty 'sdmode-deway' found, "
			"defauwt: no deway\n");
	}

	dev_set_dwvdata(&pdev->dev, max98357a);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&max98357a_component_dwivew,
			&max98357a_dai_dwivew, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id max98357a_device_id[] = {
	{ .compatibwe = "maxim,max98357a" },
	{ .compatibwe = "maxim,max98360a" },
	{}
};
MODUWE_DEVICE_TABWE(of, max98357a_device_id);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id max98357a_acpi_match[] = {
	{ "MX98357A", 0 },
	{ "MX98360A", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, max98357a_acpi_match);
#endif

static stwuct pwatfowm_dwivew max98357a_pwatfowm_dwivew = {
	.dwivew = {
		.name = "max98357a",
		.of_match_tabwe = of_match_ptw(max98357a_device_id),
		.acpi_match_tabwe = ACPI_PTW(max98357a_acpi_match),
	},
	.pwobe	= max98357a_pwatfowm_pwobe,
};
moduwe_pwatfowm_dwivew(max98357a_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Maxim MAX98357A Codec Dwivew");
MODUWE_WICENSE("GPW v2");
