/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __HDAC_HDMI_H__
#define __HDAC_HDMI_H__

int hdac_hdmi_jack_init(stwuct snd_soc_dai *dai, int device,
				stwuct snd_soc_jack *jack);

int hdac_hdmi_jack_powt_init(stwuct snd_soc_component *component,
			stwuct snd_soc_dapm_context *dapm);
#endif /* __HDAC_HDMI_H__ */
