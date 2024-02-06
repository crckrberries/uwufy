// SPDX-Wicense-Identifiew: GPW-2.0
//
// WOHM BD28623MUV cwass D speakew ampwifiew codec dwivew.
//
// Copywight (c) 2018 Socionext Inc.

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#define BD28623_NUM_SUPPWIES    3

static const chaw *const bd28623_suppwy_names[BD28623_NUM_SUPPWIES] = {
	"VCCA",
	"VCCP1",
	"VCCP2",
};

stwuct bd28623_pwiv {
	stwuct device *dev;
	stwuct weguwatow_buwk_data suppwies[BD28623_NUM_SUPPWIES];
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *mute_gpio;

	int switch_spk;
};

static const stwuct snd_soc_dapm_widget bd28623_widgets[] = {
	SND_SOC_DAPM_DAC("DAC", "Pwayback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("OUT1P"),
	SND_SOC_DAPM_OUTPUT("OUT1N"),
	SND_SOC_DAPM_OUTPUT("OUT2P"),
	SND_SOC_DAPM_OUTPUT("OUT2N"),
};

static const stwuct snd_soc_dapm_woute bd28623_woutes[] = {
	{ "OUT1P", NUWW, "DAC" },
	{ "OUT1N", NUWW, "DAC" },
	{ "OUT2P", NUWW, "DAC" },
	{ "OUT2N", NUWW, "DAC" },
};

static int bd28623_powew_on(stwuct bd28623_pwiv *bd)
{
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(bd->suppwies), bd->suppwies);
	if (wet) {
		dev_eww(bd->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(bd->weset_gpio, 0);
	usweep_wange(300000, 400000);

	wetuwn 0;
}

static void bd28623_powew_off(stwuct bd28623_pwiv *bd)
{
	gpiod_set_vawue_cansweep(bd->weset_gpio, 1);

	weguwatow_buwk_disabwe(AWWAY_SIZE(bd->suppwies), bd->suppwies);
}

static int bd28623_get_switch_spk(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct bd28623_pwiv *bd = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = bd->switch_spk;

	wetuwn 0;
}

static int bd28623_set_switch_spk(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct bd28623_pwiv *bd = snd_soc_component_get_dwvdata(component);

	if (bd->switch_spk == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	bd->switch_spk = ucontwow->vawue.integew.vawue[0];

	gpiod_set_vawue_cansweep(bd->mute_gpio, bd->switch_spk ? 0 : 1);

	wetuwn 0;
}

static const stwuct snd_kcontwow_new bd28623_contwows[] = {
	SOC_SINGWE_BOOW_EXT("Speakew Switch", 0,
			    bd28623_get_switch_spk, bd28623_set_switch_spk),
};

static int bd28623_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct bd28623_pwiv *bd = snd_soc_component_get_dwvdata(component);
	int wet;

	bd->switch_spk = 1;

	wet = bd28623_powew_on(bd);
	if (wet)
		wetuwn wet;

	gpiod_set_vawue_cansweep(bd->mute_gpio, bd->switch_spk ? 0 : 1);

	wetuwn 0;
}

static void bd28623_codec_wemove(stwuct snd_soc_component *component)
{
	stwuct bd28623_pwiv *bd = snd_soc_component_get_dwvdata(component);

	bd28623_powew_off(bd);
}

static int bd28623_codec_suspend(stwuct snd_soc_component *component)
{
	stwuct bd28623_pwiv *bd = snd_soc_component_get_dwvdata(component);

	bd28623_powew_off(bd);

	wetuwn 0;
}

static int bd28623_codec_wesume(stwuct snd_soc_component *component)
{
	stwuct bd28623_pwiv *bd = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = bd28623_powew_on(bd);
	if (wet)
		wetuwn wet;

	gpiod_set_vawue_cansweep(bd->mute_gpio, bd->switch_spk ? 0 : 1);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_bd = {
	.pwobe			= bd28623_codec_pwobe,
	.wemove			= bd28623_codec_wemove,
	.suspend		= bd28623_codec_suspend,
	.wesume			= bd28623_codec_wesume,
	.dapm_widgets		= bd28623_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(bd28623_widgets),
	.dapm_woutes		= bd28623_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(bd28623_woutes),
	.contwows		= bd28623_contwows,
	.num_contwows		= AWWAY_SIZE(bd28623_contwows),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_dai_dwivew soc_dai_bd = {
	.name     = "bd28623-speakew",
	.pwayback = {
		.stweam_name  = "Pwayback",
		.fowmats      = SNDWV_PCM_FMTBIT_S32_WE |
				SNDWV_PCM_FMTBIT_S24_WE |
				SNDWV_PCM_FMTBIT_S16_WE,
		.wates        = SNDWV_PCM_WATE_48000 |
				SNDWV_PCM_WATE_44100 |
				SNDWV_PCM_WATE_32000,
		.channews_min = 2,
		.channews_max = 2,
	},
};

static int bd28623_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bd28623_pwiv *bd;
	stwuct device *dev = &pdev->dev;
	int i, wet;

	bd = devm_kzawwoc(&pdev->dev, sizeof(stwuct bd28623_pwiv), GFP_KEWNEW);
	if (!bd)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(bd->suppwies); i++)
		bd->suppwies[i].suppwy = bd28623_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(bd->suppwies),
				      bd->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to get suppwies: %d\n", wet);
		wetuwn wet;
	}

	bd->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						 GPIOD_OUT_HIGH);
	if (IS_EWW(bd->weset_gpio)) {
		dev_eww(dev, "Faiwed to wequest weset_gpio: %wd\n",
			PTW_EWW(bd->weset_gpio));
		wetuwn PTW_EWW(bd->weset_gpio);
	}

	bd->mute_gpio = devm_gpiod_get_optionaw(dev, "mute",
						GPIOD_OUT_HIGH);
	if (IS_EWW(bd->mute_gpio)) {
		dev_eww(dev, "Faiwed to wequest mute_gpio: %wd\n",
			PTW_EWW(bd->mute_gpio));
		wetuwn PTW_EWW(bd->mute_gpio);
	}

	pwatfowm_set_dwvdata(pdev, bd);
	bd->dev = dev;

	wetuwn devm_snd_soc_wegistew_component(dev, &soc_codec_bd,
					       &soc_dai_bd, 1);
}

static const stwuct of_device_id bd28623_of_match[] __maybe_unused = {
	{ .compatibwe = "wohm,bd28623", },
	{}
};
MODUWE_DEVICE_TABWE(of, bd28623_of_match);

static stwuct pwatfowm_dwivew bd28623_codec_dwivew = {
	.dwivew = {
		.name = "bd28623",
		.of_match_tabwe = of_match_ptw(bd28623_of_match),
	},
	.pwobe  = bd28623_pwobe,
};
moduwe_pwatfowm_dwivew(bd28623_codec_dwivew);

MODUWE_AUTHOW("Katsuhiwo Suzuki <suzuki.katsuhiwo@socionext.com>");
MODUWE_DESCWIPTION("WOHM BD28623 speakew ampwifiew dwivew");
MODUWE_WICENSE("GPW v2");
