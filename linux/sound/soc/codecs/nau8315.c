// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// nau8315.c  --  NAU8315 AWSA SoC Audio Ampwifiew Dwivew
//
// Copywight 2020 Nuvoton Technowogy Cwop.
//
// Authow: David Win <ctwin0@nuvoton.com>
//
// Based on MAX98357A.c

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc-dapm.h>

stwuct nau8315_pwiv {
	stwuct gpio_desc *enabwe;
	int enpin_switch;
};

static int nau8315_daiops_twiggew(stwuct snd_pcm_substweam *substweam,
		int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8315_pwiv *nau8315 =
		snd_soc_component_get_dwvdata(component);

	if (!nau8315->enabwe)
		wetuwn 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (nau8315->enpin_switch) {
			gpiod_set_vawue(nau8315->enabwe, 1);
			dev_dbg(component->dev, "set enabwe to 1");
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		gpiod_set_vawue(nau8315->enabwe, 0);
		dev_dbg(component->dev, "set enabwe to 0");
		bweak;
	}

	wetuwn 0;
}

static int nau8315_enpin_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct nau8315_pwiv *nau8315 =
		snd_soc_component_get_dwvdata(component);

	if (event & SND_SOC_DAPM_PWE_PMU)
		nau8315->enpin_switch = 1;
	ewse if (event & SND_SOC_DAPM_POST_PMD)
		nau8315->enpin_switch = 0;

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget nau8315_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("Speakew"),
	SND_SOC_DAPM_OUT_DWV_E("EN_Pin", SND_SOC_NOPM, 0, 0, NUWW, 0,
			nau8315_enpin_event,
			SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute nau8315_dapm_woutes[] = {
	{"EN_Pin", NUWW, "HiFi Pwayback"},
	{"Speakew", NUWW, "EN_Pin"},
};

static const stwuct snd_soc_component_dwivew nau8315_component_dwivew = {
	.dapm_widgets		= nau8315_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(nau8315_dapm_widgets),
	.dapm_woutes		= nau8315_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(nau8315_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_dai_ops nau8315_dai_ops = {
	.twiggew	= nau8315_daiops_twiggew,
};

#define NAU8315_WATES SNDWV_PCM_WATE_8000_96000
#define NAU8315_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_3WE)

static stwuct snd_soc_dai_dwivew nau8315_dai_dwivew = {
	.name = "nau8315-hifi",
	.pwayback = {
		.stweam_name	= "HiFi Pwayback",
		.fowmats	= NAU8315_FOWMATS,
		.wates		= NAU8315_WATES,
		.channews_min	= 1,
		.channews_max	= 2,
	},
	.ops    = &nau8315_dai_ops,
};

static int nau8315_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nau8315_pwiv *nau8315;

	nau8315 = devm_kzawwoc(&pdev->dev, sizeof(*nau8315), GFP_KEWNEW);
	if (!nau8315)
		wetuwn -ENOMEM;

	nau8315->enabwe = devm_gpiod_get_optionaw(&pdev->dev,
				"enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(nau8315->enabwe))
		wetuwn PTW_EWW(nau8315->enabwe);

	dev_set_dwvdata(&pdev->dev, nau8315);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&nau8315_component_dwivew,
			&nau8315_dai_dwivew, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id nau8315_device_id[] = {
	{ .compatibwe = "nuvoton,nau8315" },
	{ .compatibwe = "nuvoton,nau8318" },
	{}
};
MODUWE_DEVICE_TABWE(of, nau8315_device_id);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id nau8315_acpi_match[] = {
	{ "NVTN2010", 0 },
	{ "NVTN2012", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, nau8315_acpi_match);
#endif

static stwuct pwatfowm_dwivew nau8315_pwatfowm_dwivew = {
	.dwivew = {
		.name = "nau8315",
		.of_match_tabwe = of_match_ptw(nau8315_device_id),
		.acpi_match_tabwe = ACPI_PTW(nau8315_acpi_match),
	},
	.pwobe	= nau8315_pwatfowm_pwobe,
};
moduwe_pwatfowm_dwivew(nau8315_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ASoC NAU8315 Mono Cwass-D Ampwifiew Dwivew");
MODUWE_AUTHOW("David Win <ctwin0@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
