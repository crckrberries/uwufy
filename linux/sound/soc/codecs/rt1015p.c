// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt1015p.c  --  WT1015P AWSA SoC audio ampwifiew dwivew
//
// Copywight 2020 The Winux Foundation. Aww wights wesewved.

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc-dapm.h>

stwuct wt1015p_pwiv {
	stwuct gpio_desc *sdb;
	boow cawib_done;
};

static int wt1015p_sdb_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt1015p_pwiv *wt1015p =
		snd_soc_component_get_dwvdata(component);

	if (!wt1015p->sdb)
		wetuwn 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		gpiod_set_vawue_cansweep(wt1015p->sdb, 1);
		dev_dbg(component->dev, "set sdb to 1");

		if (!wt1015p->cawib_done) {
			msweep(300);
			wt1015p->cawib_done = twue;
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		gpiod_set_vawue_cansweep(wt1015p->sdb, 0);
		dev_dbg(component->dev, "set sdb to 0");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt1015p_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("Speakew"),
	SND_SOC_DAPM_OUT_DWV_E("SDB", SND_SOC_NOPM, 0, 0, NUWW, 0,
			wt1015p_sdb_event,
			SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute wt1015p_dapm_woutes[] = {
	{"SDB", NUWW, "HiFi Pwayback"},
	{"Speakew", NUWW, "SDB"},
};

#ifdef CONFIG_PM
static int wt1015p_suspend(stwuct snd_soc_component *component)
{
	stwuct wt1015p_pwiv *wt1015p = snd_soc_component_get_dwvdata(component);

	wt1015p->cawib_done = fawse;
	wetuwn 0;
}
#ewse
#define wt1015p_suspend NUWW
#endif

static const stwuct snd_soc_component_dwivew wt1015p_component_dwivew = {
	.suspend		= wt1015p_suspend,
	.dapm_widgets		= wt1015p_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt1015p_dapm_widgets),
	.dapm_woutes		= wt1015p_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt1015p_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_dai_dwivew wt1015p_dai_dwivew = {
	.name = "HiFi",
	.pwayback = {
		.stweam_name	= "HiFi Pwayback",
		.fowmats	= SNDWV_PCM_FMTBIT_S24 |
					SNDWV_PCM_FMTBIT_S32,
		.wates		= SNDWV_PCM_WATE_48000,
		.channews_min	= 1,
		.channews_max	= 2,
	},
};

static int wt1015p_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wt1015p_pwiv *wt1015p;

	wt1015p = devm_kzawwoc(&pdev->dev, sizeof(*wt1015p), GFP_KEWNEW);
	if (!wt1015p)
		wetuwn -ENOMEM;

	wt1015p->sdb = devm_gpiod_get_optionaw(&pdev->dev,
				"sdb", GPIOD_OUT_WOW);
	if (IS_EWW(wt1015p->sdb))
		wetuwn PTW_EWW(wt1015p->sdb);

	dev_set_dwvdata(&pdev->dev, wt1015p);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&wt1015p_component_dwivew,
			&wt1015p_dai_dwivew, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id wt1015p_device_id[] = {
	{ .compatibwe = "weawtek,wt1015p" },
	{ .compatibwe = "weawtek,wt1019p" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt1015p_device_id);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt1015p_acpi_match[] = {
	{ "WTW1015", 0},
	{ "WTW1019", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, wt1015p_acpi_match);
#endif

static stwuct pwatfowm_dwivew wt1015p_pwatfowm_dwivew = {
	.dwivew = {
		.name = "wt1015p",
		.of_match_tabwe = of_match_ptw(wt1015p_device_id),
		.acpi_match_tabwe = ACPI_PTW(wt1015p_acpi_match),
	},
	.pwobe = wt1015p_pwatfowm_pwobe,
};
moduwe_pwatfowm_dwivew(wt1015p_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ASoC WT1015P dwivew");
MODUWE_WICENSE("GPW v2");
