/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Copywight (c) 2020 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef _MESON_AIU_FIFO_H
#define _MESON_AIU_FIFO_H

stwuct snd_pcm_hawdwawe;
stwuct snd_soc_component_dwivew;
stwuct snd_soc_dai_dwivew;
stwuct cwk;
stwuct snd_pcm_ops;
stwuct snd_pcm_substweam;
stwuct snd_soc_dai;
stwuct snd_pcm_hw_pawams;
stwuct pwatfowm_device;

stwuct aiu_fifo {
	stwuct snd_pcm_hawdwawe *pcm;
	unsigned int mem_offset;
	unsigned int fifo_bwock;
	stwuct cwk *pcwk;
	int iwq;
};

int aiu_fifo_dai_pwobe(stwuct snd_soc_dai *dai);
int aiu_fifo_dai_wemove(stwuct snd_soc_dai *dai);

snd_pcm_ufwames_t aiu_fifo_pointew(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam);

int aiu_fifo_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
		     stwuct snd_soc_dai *dai);
int aiu_fifo_pwepawe(stwuct snd_pcm_substweam *substweam,
		     stwuct snd_soc_dai *dai);
int aiu_fifo_hw_pawams(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_pcm_hw_pawams *pawams,
		       stwuct snd_soc_dai *dai);
int aiu_fifo_hw_fwee(stwuct snd_pcm_substweam *substweam,
		     stwuct snd_soc_dai *dai);
int aiu_fifo_stawtup(stwuct snd_pcm_substweam *substweam,
		     stwuct snd_soc_dai *dai);
void aiu_fifo_shutdown(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai);
int aiu_fifo_pcm_new(stwuct snd_soc_pcm_wuntime *wtd,
		     stwuct snd_soc_dai *dai);

#endif /* _MESON_AIU_FIFO_H */
