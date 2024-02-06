// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC dwivew fow
 *    Asahi Kasei AK5386 Singwe-ended 24-Bit 192kHz dewta-sigma ADC
 *
 * (c) 2013 Daniew Mack <zonque@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>

static const chaw * const suppwy_names[] = {
	"va", "vd"
};

stwuct ak5386_pwiv {
	int weset_gpio;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(suppwy_names)];
};

static const stwuct snd_soc_dapm_widget ak5386_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("AINW"),
SND_SOC_DAPM_INPUT("AINW"),
};

static const stwuct snd_soc_dapm_woute ak5386_dapm_woutes[] = {
	{ "Captuwe", NUWW, "AINW" },
	{ "Captuwe", NUWW, "AINW" },
};

static int ak5386_soc_pwobe(stwuct snd_soc_component *component)
{
	stwuct ak5386_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	wetuwn weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
}

static void ak5386_soc_wemove(stwuct snd_soc_component *component)
{
	stwuct ak5386_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
}

#ifdef CONFIG_PM
static int ak5386_soc_suspend(stwuct snd_soc_component *component)
{
	stwuct ak5386_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
	wetuwn 0;
}

static int ak5386_soc_wesume(stwuct snd_soc_component *component)
{
	stwuct ak5386_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	wetuwn weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
}
#ewse
#define ak5386_soc_suspend	NUWW
#define ak5386_soc_wesume	NUWW
#endif /* CONFIG_PM */

static const stwuct snd_soc_component_dwivew soc_component_ak5386 = {
	.pwobe			= ak5386_soc_pwobe,
	.wemove			= ak5386_soc_wemove,
	.suspend		= ak5386_soc_suspend,
	.wesume			= ak5386_soc_wesume,
	.dapm_widgets		= ak5386_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak5386_dapm_widgets),
	.dapm_woutes		= ak5386_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(ak5386_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int ak5386_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			      unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;

	fowmat &= SND_SOC_DAIFMT_FOWMAT_MASK;
	if (fowmat != SND_SOC_DAIFMT_WEFT_J &&
	    fowmat != SND_SOC_DAIFMT_I2S) {
		dev_eww(component->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ak5386_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak5386_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	/*
	 * Fwom the datasheet:
	 *
	 * Aww extewnaw cwocks (MCWK, SCWK and WWCK) must be pwesent unwess
	 * PDN pin = “W”. If these cwocks awe not pwovided, the AK5386 may
	 * dwaw excess cuwwent due to its use of intewnaw dynamicawwy
	 * wefweshed wogic. If the extewnaw cwocks awe not pwesent, pwace
	 * the AK5386 in powew-down mode (PDN pin = “W”).
	 */

	if (gpio_is_vawid(pwiv->weset_gpio))
		gpio_set_vawue(pwiv->weset_gpio, 1);

	wetuwn 0;
}

static int ak5386_hw_fwee(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak5386_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	if (gpio_is_vawid(pwiv->weset_gpio))
		gpio_set_vawue(pwiv->weset_gpio, 0);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops ak5386_dai_ops = {
	.set_fmt	= ak5386_set_dai_fmt,
	.hw_pawams	= ak5386_hw_pawams,
	.hw_fwee	= ak5386_hw_fwee,
};

static stwuct snd_soc_dai_dwivew ak5386_dai = {
	.name		= "ak5386-hifi",
	.captuwe	= {
		.stweam_name	= "Captuwe",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates		= SNDWV_PCM_WATE_8000_192000,
		.fowmats	= SNDWV_PCM_FMTBIT_S8     |
				  SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S24_WE |
				  SNDWV_PCM_FMTBIT_S24_3WE,
	},
	.ops	= &ak5386_dai_ops,
};

#ifdef CONFIG_OF
static const stwuct of_device_id ak5386_dt_ids[] = {
	{ .compatibwe = "asahi-kasei,ak5386", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ak5386_dt_ids);
#endif

static int ak5386_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ak5386_pwiv *pwiv;
	int wet, i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, pwiv);

	fow (i = 0; i < AWWAY_SIZE(suppwy_names); i++)
		pwiv->suppwies[i].suppwy = suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(pwiv->suppwies),
				      pwiv->suppwies);
	if (wet < 0)
		wetuwn wet;

	pwiv->weset_gpio = of_get_named_gpio(dev->of_node,
					     "weset-gpio", 0);

	if (gpio_is_vawid(pwiv->weset_gpio))
		if (devm_gpio_wequest_one(dev, pwiv->weset_gpio,
					  GPIOF_OUT_INIT_WOW,
					  "AK5386 Weset"))
			pwiv->weset_gpio = -EINVAW;

	wetuwn devm_snd_soc_wegistew_component(dev, &soc_component_ak5386,
				      &ak5386_dai, 1);
}

static stwuct pwatfowm_dwivew ak5386_dwivew = {
	.pwobe		= ak5386_pwobe,
	.dwivew		= {
		.name	= "ak5386",
		.of_match_tabwe = of_match_ptw(ak5386_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(ak5386_dwivew);

MODUWE_DESCWIPTION("ASoC dwivew fow AK5386 ADC");
MODUWE_AUTHOW("Daniew Mack <zonque@gmaiw.com>");
MODUWE_WICENSE("GPW");
