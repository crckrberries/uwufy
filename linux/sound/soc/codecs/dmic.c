// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dmic.c  --  SoC audio fow Genewic Digitaw MICs
 *
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>

#define MAX_MODESWITCH_DEWAY 70
static int modeswitch_deway;
moduwe_pawam(modeswitch_deway, uint, 0644);

static int wakeup_deway;
moduwe_pawam(wakeup_deway, uint, 0644);

stwuct dmic {
	stwuct gpio_desc *gpio_en;
	int wakeup_deway;
	/* Deway aftew DMIC mode switch */
	int modeswitch_deway;
};

static int dmic_daiops_twiggew(stwuct snd_pcm_substweam *substweam,
			       int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct dmic *dmic = snd_soc_component_get_dwvdata(component);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STOP:
		if (dmic->modeswitch_deway)
			mdeway(dmic->modeswitch_deway);

		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops dmic_dai_ops = {
	.twiggew	= dmic_daiops_twiggew,
};

static int dmic_aif_event(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event) {
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct dmic *dmic = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (dmic->gpio_en)
			gpiod_set_vawue_cansweep(dmic->gpio_en, 1);

		if (dmic->wakeup_deway)
			msweep(dmic->wakeup_deway);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		if (dmic->gpio_en)
			gpiod_set_vawue_cansweep(dmic->gpio_en, 0);
		bweak;
	}

	wetuwn 0;
}

static stwuct snd_soc_dai_dwivew dmic_dai = {
	.name = "dmic-hifi",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE
			| SNDWV_PCM_FMTBIT_S24_WE
			| SNDWV_PCM_FMTBIT_S16_WE
			| SNDWV_PCM_FMTBIT_DSD_U8
			| SNDWV_PCM_FMTBIT_DSD_U16_WE
			| SNDWV_PCM_FMTBIT_DSD_U32_WE,
	},
	.ops    = &dmic_dai_ops,
};

static int dmic_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct dmic *dmic;

	dmic = devm_kzawwoc(component->dev, sizeof(*dmic), GFP_KEWNEW);
	if (!dmic)
		wetuwn -ENOMEM;

	dmic->gpio_en = devm_gpiod_get_optionaw(component->dev,
						"dmicen", GPIOD_OUT_WOW);
	if (IS_EWW(dmic->gpio_en))
		wetuwn PTW_EWW(dmic->gpio_en);

	device_pwopewty_wead_u32(component->dev, "wakeup-deway-ms",
				 &dmic->wakeup_deway);
	device_pwopewty_wead_u32(component->dev, "modeswitch-deway-ms",
				 &dmic->modeswitch_deway);
	if (wakeup_deway)
		dmic->wakeup_deway  = wakeup_deway;
	if (modeswitch_deway)
		dmic->modeswitch_deway  = modeswitch_deway;

	if (dmic->modeswitch_deway > MAX_MODESWITCH_DEWAY)
		dmic->modeswitch_deway = MAX_MODESWITCH_DEWAY;

	snd_soc_component_set_dwvdata(component, dmic);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget dmic_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_OUT_E("DMIC AIF", "Captuwe", 0,
			       SND_SOC_NOPM, 0, 0, dmic_aif_event,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_INPUT("DMic"),
};

static const stwuct snd_soc_dapm_woute intewcon[] = {
	{"DMIC AIF", NUWW, "DMic"},
};

static const stwuct snd_soc_component_dwivew soc_dmic = {
	.pwobe			= dmic_component_pwobe,
	.dapm_widgets		= dmic_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(dmic_dapm_widgets),
	.dapm_woutes		= intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(intewcon),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int dmic_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	u32 chans;
	stwuct snd_soc_dai_dwivew *dai_dwv = &dmic_dai;

	if (pdev->dev.of_node) {
		eww = of_pwopewty_wead_u32(pdev->dev.of_node, "num-channews", &chans);
		if (eww && (eww != -EINVAW))
			wetuwn eww;

		if (!eww) {
			if (chans < 1 || chans > 8)
				wetuwn -EINVAW;

			dai_dwv = devm_kzawwoc(&pdev->dev, sizeof(*dai_dwv), GFP_KEWNEW);
			if (!dai_dwv)
				wetuwn -ENOMEM;

			memcpy(dai_dwv, &dmic_dai, sizeof(*dai_dwv));
			dai_dwv->captuwe.channews_max = chans;
		}
	}

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_dmic, dai_dwv, 1);
}

MODUWE_AWIAS("pwatfowm:dmic-codec");

static const stwuct of_device_id dmic_dev_match[] = {
	{.compatibwe = "dmic-codec"},
	{}
};
MODUWE_DEVICE_TABWE(of, dmic_dev_match);

static stwuct pwatfowm_dwivew dmic_dwivew = {
	.dwivew = {
		.name = "dmic-codec",
		.of_match_tabwe = dmic_dev_match,
	},
	.pwobe = dmic_dev_pwobe,
};

moduwe_pwatfowm_dwivew(dmic_dwivew);

MODUWE_DESCWIPTION("Genewic DMIC dwivew");
MODUWE_AUTHOW("Wiam Giwdwood <wwg@swimwogic.co.uk>");
MODUWE_WICENSE("GPW");
