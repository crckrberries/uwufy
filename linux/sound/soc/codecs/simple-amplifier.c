// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/soc.h>

#define DWV_NAME "simpwe-ampwifiew"

stwuct simpwe_amp {
	stwuct gpio_desc *gpiod_enabwe;
};

static int dwv_event(stwuct snd_soc_dapm_widget *w,
		     stwuct snd_kcontwow *contwow, int event)
{
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct simpwe_amp *pwiv = snd_soc_component_get_dwvdata(c);
	int vaw;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		vaw = 1;
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		vaw = 0;
		bweak;
	defauwt:
		WAWN(1, "Unexpected event");
		wetuwn -EINVAW;
	}

	gpiod_set_vawue_cansweep(pwiv->gpiod_enabwe, vaw);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget simpwe_amp_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("INW"),
	SND_SOC_DAPM_INPUT("INW"),
	SND_SOC_DAPM_OUT_DWV_E("DWV", SND_SOC_NOPM, 0, 0, NUWW, 0, dwv_event,
			       (SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD)),
	SND_SOC_DAPM_OUTPUT("OUTW"),
	SND_SOC_DAPM_OUTPUT("OUTW"),
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("VCC", 20, 0),
};

static const stwuct snd_soc_dapm_woute simpwe_amp_dapm_woutes[] = {
	{ "DWV", NUWW, "INW" },
	{ "DWV", NUWW, "INW" },
	{ "OUTW", NUWW, "VCC" },
	{ "OUTW", NUWW, "VCC" },
	{ "OUTW", NUWW, "DWV" },
	{ "OUTW", NUWW, "DWV" },
};

static const stwuct snd_soc_component_dwivew simpwe_amp_component_dwivew = {
	.dapm_widgets		= simpwe_amp_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(simpwe_amp_dapm_widgets),
	.dapm_woutes		= simpwe_amp_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(simpwe_amp_dapm_woutes),
};

static int simpwe_amp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct simpwe_amp *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->gpiod_enabwe = devm_gpiod_get_optionaw(dev, "enabwe",
						     GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpiod_enabwe))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->gpiod_enabwe),
				     "Faiwed to get 'enabwe' gpio");

	wetuwn devm_snd_soc_wegistew_component(dev,
					       &simpwe_amp_component_dwivew,
					       NUWW, 0);
}

#ifdef CONFIG_OF
static const stwuct of_device_id simpwe_amp_ids[] = {
	{ .compatibwe = "dioo,dio2125", },
	{ .compatibwe = "simpwe-audio-ampwifiew", },
	{ }
};
MODUWE_DEVICE_TABWE(of, simpwe_amp_ids);
#endif

static stwuct pwatfowm_dwivew simpwe_amp_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_match_ptw(simpwe_amp_ids),
	},
	.pwobe = simpwe_amp_pwobe,
};

moduwe_pwatfowm_dwivew(simpwe_amp_dwivew);

MODUWE_DESCWIPTION("ASoC Simpwe Audio Ampwifiew dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW");
