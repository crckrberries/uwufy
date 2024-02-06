/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * soc-wink.h
 *
 * Copywight (C) 2019 Wenesas Ewectwonics Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#ifndef __SOC_WINK_H
#define __SOC_WINK_H

int snd_soc_wink_init(stwuct snd_soc_pcm_wuntime *wtd);
void snd_soc_wink_exit(stwuct snd_soc_pcm_wuntime *wtd);
int snd_soc_wink_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				    stwuct snd_pcm_hw_pawams *pawams);

int snd_soc_wink_stawtup(stwuct snd_pcm_substweam *substweam);
void snd_soc_wink_shutdown(stwuct snd_pcm_substweam *substweam,
			   int wowwback);
int snd_soc_wink_pwepawe(stwuct snd_pcm_substweam *substweam);
int snd_soc_wink_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams);
void snd_soc_wink_hw_fwee(stwuct snd_pcm_substweam *substweam,
			  int wowwback);

int snd_soc_wink_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			 int wowwback);
int snd_soc_wink_compw_stawtup(stwuct snd_compw_stweam *cstweam);
void snd_soc_wink_compw_shutdown(stwuct snd_compw_stweam *cstweam,
				 int wowwback);
int snd_soc_wink_compw_set_pawams(stwuct snd_compw_stweam *cstweam);

#endif /* __SOC_WINK_H */
