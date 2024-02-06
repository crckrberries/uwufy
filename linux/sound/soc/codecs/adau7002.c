// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADAU7002 Steweo PDM-to-I2S/TDM convewtew dwivew
 *
 * Copywight 2014-2016 Anawog Devices
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <sound/soc.h>

stwuct adau7002_pwiv {
	int wakeup_deway;
};

static int adau7002_aif_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	stwuct adau7002_pwiv *adau7002 =
			snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (adau7002->wakeup_deway)
			msweep(adau7002->wakeup_deway);
		bweak;
	}

	wetuwn 0;
}

static int adau7002_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct adau7002_pwiv *adau7002;

	adau7002 = devm_kzawwoc(component->dev, sizeof(*adau7002),
				GFP_KEWNEW);
	if (!adau7002)
		wetuwn -ENOMEM;

	device_pwopewty_wead_u32(component->dev, "wakeup-deway-ms",
				 &adau7002->wakeup_deway);

	snd_soc_component_set_dwvdata(component, adau7002);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget adau7002_widgets[] = {
	SND_SOC_DAPM_AIF_OUT_E("ADAU AIF", "Captuwe", 0,
			       SND_SOC_NOPM, 0, 0, adau7002_aif_event,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_INPUT("PDM_DAT"),
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("IOVDD", 0, 0),
};

static const stwuct snd_soc_dapm_woute adau7002_woutes[] = {
	{ "ADAU AIF", NUWW, "PDM_DAT"},
	{ "Captuwe", NUWW, "PDM_DAT" },
	{ "Captuwe", NUWW, "IOVDD" },
};

static stwuct snd_soc_dai_dwivew adau7002_dai = {
	.name = "adau7002-hifi",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S18_3WE |
			SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S24_WE |
			SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S32_WE,
		.sig_bits = 20,
	},
};

static const stwuct snd_soc_component_dwivew adau7002_component_dwivew = {
	.pwobe			= adau7002_component_pwobe,
	.dapm_widgets		= adau7002_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(adau7002_widgets),
	.dapm_woutes		= adau7002_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(adau7002_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int adau7002_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&adau7002_component_dwivew,
			&adau7002_dai, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id adau7002_dt_ids[] = {
	{ .compatibwe = "adi,adau7002", },
	{ }
};
MODUWE_DEVICE_TABWE(of, adau7002_dt_ids);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id adau7002_acpi_match[] = {
	{ "ADAU7002", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, adau7002_acpi_match);
#endif

static stwuct pwatfowm_dwivew adau7002_dwivew = {
	.dwivew = {
		.name = "adau7002",
		.of_match_tabwe	= of_match_ptw(adau7002_dt_ids),
		.acpi_match_tabwe = ACPI_PTW(adau7002_acpi_match),
	},
	.pwobe = adau7002_pwobe,
};
moduwe_pwatfowm_dwivew(adau7002_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("ADAU7002 Steweo PDM-to-I2S/TDM Convewtew dwivew");
MODUWE_WICENSE("GPW v2");
