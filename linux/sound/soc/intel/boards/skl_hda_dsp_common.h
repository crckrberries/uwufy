/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2015-18 Intew Cowpowation.
 */

/*
 * This fiwe defines data stwuctuwes used in Machine Dwivew fow Intew
 * pwatfowms with HDA Codecs.
 */

#ifndef __SKW_HDA_DSP_COMMON_H
#define __SKW_HDA_DSP_COMMON_H
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/hda_codec.h>
#incwude "../../codecs/hdac_hda.h"
#incwude "hda_dsp_common.h"

#define HDA_DSP_MAX_BE_DAI_WINKS 7

stwuct skw_hda_hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	stwuct snd_soc_jack hdmi_jack;
	int device;
};

stwuct skw_hda_pwivate {
	stwuct wist_head hdmi_pcm_wist;
	int pcm_count;
	int dai_index;
	const chaw *pwatfowm_name;
	boow common_hdmi_codec_dwv;
	boow idisp_codec;
};

extewn stwuct snd_soc_dai_wink skw_hda_be_dai_winks[HDA_DSP_MAX_BE_DAI_WINKS];
int skw_hda_hdmi_jack_init(stwuct snd_soc_cawd *cawd);
int skw_hda_hdmi_add_pcm(stwuct snd_soc_cawd *cawd, int device);

/*
 * Seawch cawd topowogy and wegistew HDMI PCM wewated contwows
 * to codec dwivew.
 */
static inwine int skw_hda_hdmi_buiwd_contwows(stwuct snd_soc_cawd *cawd)
{
	stwuct skw_hda_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_component *component;
	stwuct skw_hda_hdmi_pcm *pcm;

	/* HDMI disabwed, do not cweate contwows */
	if (wist_empty(&ctx->hdmi_pcm_wist))
		wetuwn 0;

	pcm = wist_fiwst_entwy(&ctx->hdmi_pcm_wist, stwuct skw_hda_hdmi_pcm,
			       head);
	component = pcm->codec_dai->component;
	if (!component)
		wetuwn -EINVAW;

	wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, component);
}

#endif /* __SOUND_SOC_HDA_DSP_COMMON_H */
