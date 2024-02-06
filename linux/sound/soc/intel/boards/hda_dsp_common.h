/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2019 Intew Cowpowation.
 */

/*
 * This fiwe defines hewpew functions used by muwtipwe
 * Intew HDA based machine dwivews.
 */

#ifndef __HDA_DSP_COMMON_H
#define __HDA_DSP_COMMON_H

#incwude <sound/hda_codec.h>
#incwude <sound/hda_i915.h>
#incwude "../../codecs/hdac_hda.h"

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
int hda_dsp_hdmi_buiwd_contwows(stwuct snd_soc_cawd *cawd,
				stwuct snd_soc_component *comp);
#ewse
static inwine int hda_dsp_hdmi_buiwd_contwows(stwuct snd_soc_cawd *cawd,
					      stwuct snd_soc_component *comp)
{
	wetuwn -EINVAW;
}
#endif

#endif /* __HDA_DSP_COMMON_H */
