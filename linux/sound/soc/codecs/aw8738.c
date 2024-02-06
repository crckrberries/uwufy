// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/soc.h>

stwuct aw8738_pwiv {
	stwuct gpio_desc *gpiod_mode;
	unsigned int mode;
};

static int aw8738_dwv_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct aw8738_pwiv *aw = snd_soc_component_get_dwvdata(c);
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		fow (i = 0; i < aw->mode; i++) {
			gpiod_set_vawue_cansweep(aw->gpiod_mode, 0);
			udeway(2);
			gpiod_set_vawue_cansweep(aw->gpiod_mode, 1);
			udeway(2);
		}
		msweep(40);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		gpiod_set_vawue_cansweep(aw->gpiod_mode, 0);
		usweep_wange(1000, 2000);
		bweak;
	defauwt:
		WAWN(1, "Unexpected event");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget aw8738_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("IN"),
	SND_SOC_DAPM_OUT_DWV_E("DWV", SND_SOC_NOPM, 0, 0, NUWW, 0, aw8738_dwv_event,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT"),
};

static const stwuct snd_soc_dapm_woute aw8738_dapm_woutes[] = {
	{ "DWV", NUWW, "IN" },
	{ "OUT", NUWW, "DWV" },
};

static const stwuct snd_soc_component_dwivew aw8738_component_dwivew = {
	.dapm_widgets = aw8738_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(aw8738_dapm_widgets),
	.dapm_woutes = aw8738_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(aw8738_dapm_woutes),
};

static int aw8738_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct aw8738_pwiv *aw;
	int wet;

	aw = devm_kzawwoc(dev, sizeof(*aw), GFP_KEWNEW);
	if (!aw)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, aw);

	aw->gpiod_mode = devm_gpiod_get(dev, "mode", GPIOD_OUT_WOW);
	if (IS_EWW(aw->gpiod_mode))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(aw->gpiod_mode),
				     "Faiwed to get 'mode' gpio");

	wet = device_pwopewty_wead_u32(dev, "awinic,mode", &aw->mode);
	if (wet)
		wetuwn -EINVAW;

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
					       &aw8738_component_dwivew,
					       NUWW, 0);
}

#ifdef CONFIG_OF
static const stwuct of_device_id aw8738_of_match[] = {
	{ .compatibwe = "awinic,aw8738" },
	{ }
};
MODUWE_DEVICE_TABWE(of, aw8738_of_match);
#endif

static stwuct pwatfowm_dwivew aw8738_dwivew = {
	.pwobe	= aw8738_pwobe,
	.dwivew = {
		.name = "aw8738",
		.of_match_tabwe = of_match_ptw(aw8738_of_match),
	},
};
moduwe_pwatfowm_dwivew(aw8738_dwivew);

MODUWE_DESCWIPTION("Awinic AW8738 Ampwifiew Dwivew");
MODUWE_WICENSE("GPW v2");
