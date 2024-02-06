/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (c) 2018 Baywibwe SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef _MESON_CODEC_GWUE_H
#define _MESON_CODEC_GWUE_H

#incwude <sound/soc.h>

stwuct meson_codec_gwue_input {
	stwuct snd_soc_pcm_stweam pawams;
	unsigned int fmt;
};

/* Input hewpews */
stwuct meson_codec_gwue_input *
meson_codec_gwue_input_get_data(stwuct snd_soc_dai *dai);
int meson_codec_gwue_input_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams,
				     stwuct snd_soc_dai *dai);
int meson_codec_gwue_input_set_fmt(stwuct snd_soc_dai *dai,
				   unsigned int fmt);
int meson_codec_gwue_input_dai_pwobe(stwuct snd_soc_dai *dai);
int meson_codec_gwue_input_dai_wemove(stwuct snd_soc_dai *dai);

/* Output hewpews */
int meson_codec_gwue_output_stawtup(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *dai);

#endif /* _MESON_CODEC_GWUE_H */
