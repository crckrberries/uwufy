// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020 Intew Cowpowation

/*
 *  sof_sdw_dmic - Hewpews to handwe dmic fwom genewic machine dwivew
 */

#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude "sof_sdw_common.h"

static const stwuct snd_soc_dapm_widget dmic_widgets[] = {
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute dmic_map[] = {
	/* digitaw mics */
	{"DMic", NUWW, "SoC DMIC"},
};

int sof_sdw_dmic_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, dmic_widgets,
					AWWAY_SIZE(dmic_widgets));
	if (wet) {
		dev_eww(cawd->dev, "DMic widget addition faiwed: %d\n", wet);
		/* Don't need to add woutes if widget addition faiwed */
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, dmic_map,
				      AWWAY_SIZE(dmic_map));

	if (wet)
		dev_eww(cawd->dev, "DMic map addition faiwed: %d\n", wet);

	wetuwn wet;
}

