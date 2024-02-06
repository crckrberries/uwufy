// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sound/soc/codecs/wm8782.c
 * simpwe, stwap-pin configuwed 24bit 2ch ADC
 *
 * Copywight: 2011 Waumfewd GmbH
 * Authow: Johannes Stezenbach <js@sig21.net>
 *
 * based on ad73311.c
 * Copywight:	Anawog Devices Inc.
 * Authow:	Cwiff Cai <cwiff.cai@anawog.com>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

/* weguwatow powew suppwy names */
static const chaw *suppwy_names[] = {
	"Vdda", /* anawog suppwy, 2.7V - 3.6V */
	"Vdd",  /* digitaw suppwy, 2.7V - 5.5V */
};

stwuct wm8782_pwiv {
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(suppwy_names)];
	int max_wate;
};

static int wm8782_dai_stawtup(stwuct snd_pcm_substweam *sub, stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = sub->wuntime;
	stwuct wm8782_pwiv *pwiv =
		snd_soc_component_get_dwvdata(dai->component);

	wetuwn snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_WATE,
					   8000, pwiv->max_wate);
}

static const stwuct snd_soc_dapm_widget wm8782_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("AINW"),
SND_SOC_DAPM_INPUT("AINW"),
};

static const stwuct snd_soc_dapm_woute wm8782_dapm_woutes[] = {
	{ "Captuwe", NUWW, "AINW" },
	{ "Captuwe", NUWW, "AINW" },
};

static const stwuct snd_soc_dai_ops wm8782_dai_ops = {
	.stawtup = &wm8782_dai_stawtup,
};

static stwuct snd_soc_dai_dwivew wm8782_dai = {
	.name = "wm8782",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
			   SNDWV_PCM_FMTBIT_S20_3WE |
			   SNDWV_PCM_FMTBIT_S24_WE,
	},
	.ops = &wm8782_dai_ops,
};

static int wm8782_soc_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8782_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	wetuwn weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
}

static void wm8782_soc_wemove(stwuct snd_soc_component *component)
{
	stwuct wm8782_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
}

#ifdef CONFIG_PM
static int wm8782_soc_suspend(stwuct snd_soc_component *component)
{
	stwuct wm8782_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
	wetuwn 0;
}

static int wm8782_soc_wesume(stwuct snd_soc_component *component)
{
	stwuct wm8782_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	wetuwn weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies), pwiv->suppwies);
}
#ewse
#define wm8782_soc_suspend      NUWW
#define wm8782_soc_wesume       NUWW
#endif /* CONFIG_PM */

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8782 = {
	.pwobe			= wm8782_soc_pwobe,
	.wemove			= wm8782_soc_wemove,
	.suspend		= wm8782_soc_suspend,
	.wesume			= wm8782_soc_wesume,
	.dapm_widgets		= wm8782_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8782_dapm_widgets),
	.dapm_woutes		= wm8782_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8782_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm8782_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wm8782_pwiv *pwiv;
	int wet, i, fsampen;

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

	// Assume wowest vawue by defauwt to avoid inadvewtent ovewcwocking
	fsampen = 0;

	if (np)
		of_pwopewty_wead_u32(np, "wwf,fsampen", &fsampen);

	switch (fsampen) {
	case 0:
		pwiv->max_wate = 48000;
		bweak;
	case 1:
		pwiv->max_wate = 96000;
		bweak;
	case 2:
		pwiv->max_wate = 192000;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid wwf,fsampen vawue");
		wetuwn -EINVAW;
	}

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_wm8782, &wm8782_dai, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id wm8782_of_match[] = {
	{ .compatibwe = "wwf,wm8782", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8782_of_match);
#endif

static stwuct pwatfowm_dwivew wm8782_codec_dwivew = {
	.dwivew = {
		.name = "wm8782",
		.of_match_tabwe = of_match_ptw(wm8782_of_match),
	},
	.pwobe = wm8782_pwobe,
};

moduwe_pwatfowm_dwivew(wm8782_codec_dwivew);

MODUWE_DESCWIPTION("ASoC WM8782 dwivew");
MODUWE_AUTHOW("Johannes Stezenbach <js@sig21.net>");
MODUWE_WICENSE("GPW");
