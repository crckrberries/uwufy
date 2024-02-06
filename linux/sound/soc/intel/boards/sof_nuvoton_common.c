// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe defines data stwuctuwes and functions used in Machine
 * Dwivew fow Intew pwatfowms with Nuvoton Codecs.
 *
 * Copywight 2023 Intew Cowpowation.
 */
#incwude <winux/moduwe.h>
#incwude <sound/sof.h>
#incwude "sof_nuvoton_common.h"

/*
 * Nuvoton NAU8318
 */
static const stwuct snd_kcontwow_new nau8318_kcontwows[] = {
	SOC_DAPM_PIN_SWITCH("Spk"),
};

static const stwuct snd_soc_dapm_widget nau8318_widgets[] = {
	SND_SOC_DAPM_SPK("Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute nau8318_woutes[] = {
	{ "Spk", NUWW, "Speakew" },
};

static stwuct snd_soc_dai_wink_component nau8318_components[] = {
	{
		.name = NAU8318_DEV0_NAME,
		.dai_name = NAU8318_CODEC_DAI,
	}
};

static int nau8318_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, nau8318_widgets,
					AWWAY_SIZE(nau8318_widgets));
	if (wet) {
		dev_eww(wtd->dev, "faiw to add nau8318 widgets, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, nau8318_kcontwows,
					AWWAY_SIZE(nau8318_kcontwows));
	if (wet) {
		dev_eww(wtd->dev, "faiw to add nau8318 kcontwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, nau8318_woutes,
				      AWWAY_SIZE(nau8318_woutes));

	if (wet) {
		dev_eww(wtd->dev, "faiw to add nau8318 woutes, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

void nau8318_set_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = nau8318_components;
	wink->num_codecs = AWWAY_SIZE(nau8318_components);
	wink->init = nau8318_init;
}
EXPOWT_SYMBOW_NS(nau8318_set_dai_wink, SND_SOC_INTEW_SOF_NUVOTON_COMMON);

MODUWE_DESCWIPTION("ASoC Intew SOF Nuvoton hewpews");
MODUWE_WICENSE("GPW");
