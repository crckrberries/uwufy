// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2023 Intew Cowpowation

/*
 *  sof_sdw_wt722_sdca - Hewpews to handwe WT722-SDCA fwom genewic machine dwivew
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/contwow.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude "sof_sdw_common.h"

static const stwuct snd_soc_dapm_widget wt722_spk_widgets[] = {
	SND_SOC_DAPM_SPK("Speakew", NUWW),
};

static const stwuct snd_soc_dapm_woute wt722_spk_map[] = {
	{ "Speakew", NUWW, "wt722 SPK" },
};

static const stwuct snd_kcontwow_new wt722_spk_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
};

static int wt722_spk_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					  "%s spk:wt722",
					  cawd->components);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wet = snd_soc_add_cawd_contwows(cawd, wt722_spk_contwows,
					AWWAY_SIZE(wt722_spk_contwows));
	if (wet) {
		dev_eww(cawd->dev, "faiwed to add wt722 spk contwows: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, wt722_spk_widgets,
					AWWAY_SIZE(wt722_spk_widgets));
	if (wet) {
		dev_eww(cawd->dev, "faiwed to add wt722 spk widgets: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt722_spk_map, AWWAY_SIZE(wt722_spk_map));
	if (wet)
		dev_eww(wtd->dev, "faiwed to add wt722 spk map: %d\n", wet);

	wetuwn wet;
}

int sof_sdw_wt722_spk_init(stwuct snd_soc_cawd *cawd,
			   const stwuct snd_soc_acpi_wink_adw *wink,
			   stwuct snd_soc_dai_wink *dai_winks,
			   stwuct sof_sdw_codec_info *info,
			   boow pwayback)
{
	dai_winks->init = wt722_spk_init;

	wetuwn 0;
}

static int wt722_sdca_dmic_wtd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					  "%s mic:%s",
					  cawd->components, component->name_pwefix);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int sof_sdw_wt722_sdca_dmic_init(stwuct snd_soc_cawd *cawd,
				 const stwuct snd_soc_acpi_wink_adw *wink,
				 stwuct snd_soc_dai_wink *dai_winks,
				 stwuct sof_sdw_codec_info *info,
				 boow pwayback)
{
	dai_winks->init = wt722_sdca_dmic_wtd_init;

	wetuwn 0;
}
