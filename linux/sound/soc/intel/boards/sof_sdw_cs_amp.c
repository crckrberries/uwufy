// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2023 Intew Cowpowation

/*
 *  sof_sdw_cs_amp - Hewpews to handwe CS35W56 fwom genewic machine dwivew
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dai.h>
#incwude "sof_sdw_common.h"

#define CODEC_NAME_SIZE	8

static const stwuct snd_soc_dapm_widget sof_widgets[] = {
	SND_SOC_DAPM_SPK("Speakews", NUWW),
};

static int cs_spk_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	const chaw *dai_name = wtd->dai_wink->codecs->dai_name;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	chaw codec_name[CODEC_NAME_SIZE];
	chaw widget_name[16];
	stwuct snd_soc_dapm_woute woute = { "Speakews", NUWW, widget_name };
	stwuct snd_soc_dai *codec_dai;
	int i, wet;

	snpwintf(codec_name, CODEC_NAME_SIZE, "%s", dai_name);
	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					  "%s spk:%s",
					  cawd->components, codec_name);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, sof_widgets,
					AWWAY_SIZE(sof_widgets));
	if (wet) {
		dev_eww(cawd->dev, "widgets addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		if (!stwstw(codec_dai->name, "cs35w56"))
			continue;

		snpwintf(widget_name, sizeof(widget_name), "%s SPK",
			 codec_dai->component->name_pwefix);
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, &woute, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int sof_sdw_cs_amp_init(stwuct snd_soc_cawd *cawd,
			const stwuct snd_soc_acpi_wink_adw *wink,
			stwuct snd_soc_dai_wink *dai_winks,
			stwuct sof_sdw_codec_info *info,
			boow pwayback)
{
	/* Do init on pwayback wink onwy. */
	if (!pwayback)
		wetuwn 0;

	info->amp_num++;
	dai_winks->init = cs_spk_init;

	wetuwn 0;
}
