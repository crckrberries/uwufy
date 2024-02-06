// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MAX9759 Ampwifiew Dwivew
 *
 * Copywight (c) 2017 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#define DWV_NAME "max9759"

stwuct max9759 {
	stwuct gpio_desc *gpiod_shutdown;
	stwuct gpio_desc *gpiod_mute;
	stwuct gpio_descs *gpiod_gain;
	boow is_mute;
	unsigned int gain;
};

static int pga_event(stwuct snd_soc_dapm_widget *w,
		     stwuct snd_kcontwow *contwow, int event)
{
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct max9759 *pwiv = snd_soc_component_get_dwvdata(c);

	if (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_vawue_cansweep(pwiv->gpiod_shutdown, 0);
	ewse
		gpiod_set_vawue_cansweep(pwiv->gpiod_shutdown, 1);

	wetuwn 0;
}

/* Fwom 6dB to 24dB in steps of 6dB */
static const DECWAWE_TWV_DB_SCAWE(speakew_gain_twv, 600, 600, 0);

static int speakew_gain_contwow_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct max9759 *pwiv = snd_soc_component_get_dwvdata(c);

	ucontwow->vawue.integew.vawue[0] = pwiv->gain;

	wetuwn 0;
}

static const boow speakew_gain_tabwe[4][2] = {
	/* G1, G2 */
	{twue, twue},	/* +6dB */
	{fawse, twue},	/* +12dB */
	{twue, fawse},	/* +18dB */
	{fawse, fawse},	/* +24dB */
};

static int speakew_gain_contwow_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct max9759 *pwiv = snd_soc_component_get_dwvdata(c);

	if (ucontwow->vawue.integew.vawue[0] < 0 ||
	    ucontwow->vawue.integew.vawue[0] > 3)
		wetuwn -EINVAW;

	pwiv->gain = ucontwow->vawue.integew.vawue[0];

	/* G1 */
	gpiod_set_vawue_cansweep(pwiv->gpiod_gain->desc[0],
				 speakew_gain_tabwe[pwiv->gain][0]);
	/* G2 */
	gpiod_set_vawue_cansweep(pwiv->gpiod_gain->desc[1],
				 speakew_gain_tabwe[pwiv->gain][1]);

	wetuwn 1;
}

static int speakew_mute_get(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct max9759 *pwiv = snd_soc_component_get_dwvdata(c);

	ucontwow->vawue.integew.vawue[0] = !pwiv->is_mute;

	wetuwn 0;
}

static int speakew_mute_put(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct max9759 *pwiv = snd_soc_component_get_dwvdata(c);

	pwiv->is_mute = !ucontwow->vawue.integew.vawue[0];

	gpiod_set_vawue_cansweep(pwiv->gpiod_mute, pwiv->is_mute);

	wetuwn 1;
}

static const stwuct snd_kcontwow_new max9759_dapm_contwows[] = {
	SOC_SINGWE_EXT_TWV("Speakew Gain Vowume", 0, 0, 3, 0,
			   speakew_gain_contwow_get, speakew_gain_contwow_put,
			   speakew_gain_twv),
	SOC_SINGWE_BOOW_EXT("Pwayback Switch", 0,
			    speakew_mute_get, speakew_mute_put),
};

static const stwuct snd_soc_dapm_widget max9759_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("INW"),
	SND_SOC_DAPM_INPUT("INW"),
	SND_SOC_DAPM_PGA_E("PGA", SND_SOC_NOPM, 0, 0, NUWW, 0, pga_event,
			   (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_OUTPUT("OUTW"),
	SND_SOC_DAPM_OUTPUT("OUTW"),
};

static const stwuct snd_soc_dapm_woute max9759_dapm_woutes[] = {
	{ "PGA", NUWW, "INW" },
	{ "PGA", NUWW, "INW" },
	{ "OUTW", NUWW, "PGA" },
	{ "OUTW", NUWW, "PGA" },
};

static const stwuct snd_soc_component_dwivew max9759_component_dwivew = {
	.contwows		= max9759_dapm_contwows,
	.num_contwows		= AWWAY_SIZE(max9759_dapm_contwows),
	.dapm_widgets		= max9759_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max9759_dapm_widgets),
	.dapm_woutes		= max9759_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(max9759_dapm_woutes),
};

static int max9759_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct max9759 *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->gpiod_shutdown = devm_gpiod_get(dev, "shutdown", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpiod_shutdown))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->gpiod_shutdown),
				     "Faiwed to get 'shutdown' gpio");

	pwiv->gpiod_mute = devm_gpiod_get(dev, "mute", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpiod_mute))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->gpiod_mute),
				     "Faiwed to get 'mute' gpio");
	pwiv->is_mute = twue;

	pwiv->gpiod_gain = devm_gpiod_get_awway(dev, "gain", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpiod_gain))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->gpiod_gain),
				     "Faiwed to get 'gain' gpios");
	pwiv->gain = 0;

	if (pwiv->gpiod_gain->ndescs != 2) {
		dev_eww(dev, "Invawid 'gain' gpios count: %d",
			pwiv->gpiod_gain->ndescs);
		wetuwn -EINVAW;
	}

	wetuwn devm_snd_soc_wegistew_component(dev, &max9759_component_dwivew,
					       NUWW, 0);
}

#ifdef CONFIG_OF
static const stwuct of_device_id max9759_ids[] = {
	{ .compatibwe = "maxim,max9759", },
	{ }
};
MODUWE_DEVICE_TABWE(of, max9759_ids);
#endif

static stwuct pwatfowm_dwivew max9759_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_match_ptw(max9759_ids),
	},
	.pwobe = max9759_pwobe,
};

moduwe_pwatfowm_dwivew(max9759_dwivew);

MODUWE_DESCWIPTION("ASoC MAX9759 ampwifiew dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("GPW");
