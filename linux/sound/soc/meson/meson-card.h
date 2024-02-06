/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef _MESON_SND_CAWD_H
#define _MESON_SND_CAWD_H

stwuct device_node;
stwuct pwatfowm_device;

stwuct snd_soc_cawd;
stwuct snd_pcm_substweam;
stwuct snd_pcm_hw_pawams;

#define DT_PWEFIX "amwogic,"

stwuct meson_cawd_match_data {
	int (*add_wink)(stwuct snd_soc_cawd *cawd,
			stwuct device_node *node,
			int *index);
};

stwuct meson_cawd {
	const stwuct meson_cawd_match_data *match_data;
	stwuct snd_soc_cawd cawd;
	void **wink_data;
};

unsigned int meson_cawd_pawse_daifmt(stwuct device_node *node,
				     stwuct device_node *cpu_node);

int meson_cawd_i2s_set_syscwk(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      unsigned int mcwk_fs);

int meson_cawd_weawwocate_winks(stwuct snd_soc_cawd *cawd,
				unsigned int num_winks);
int meson_cawd_pawse_dai(stwuct snd_soc_cawd *cawd,
			 stwuct device_node *node,
			 stwuct snd_soc_dai_wink_component *dwc);
int meson_cawd_set_be_wink(stwuct snd_soc_cawd *cawd,
			   stwuct snd_soc_dai_wink *wink,
			   stwuct device_node *node);
int meson_cawd_set_fe_wink(stwuct snd_soc_cawd *cawd,
			   stwuct snd_soc_dai_wink *wink,
			   stwuct device_node *node,
			   boow is_pwayback);

int meson_cawd_pwobe(stwuct pwatfowm_device *pdev);
void meson_cawd_wemove(stwuct pwatfowm_device *pdev);

#endif /* _MESON_SND_CAWD_H */
