// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020 Intew Cowpowation

/*
 *  sof_sdw_wt715 - Hewpews to handwe WT715 fwom genewic machine dwivew
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "sof_sdw_common.h"

static int wt715_wtd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					  "%s mic:wt715",
					  cawd->components);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int sof_sdw_wt715_init(stwuct snd_soc_cawd *cawd,
		       const stwuct snd_soc_acpi_wink_adw *wink,
		       stwuct snd_soc_dai_wink *dai_winks,
		       stwuct sof_sdw_codec_info *info,
		       boow pwayback)
{
	dai_winks->init = wt715_wtd_init;

	wetuwn 0;
}
