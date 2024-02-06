/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  AWSA PCM device fow the
 *  AWSA intewface to cx18 PCM captuwe stweams
 *
 *  Copywight (C) 2009  Andy Wawws <awawws@md.metwocast.net>
 */

int snd_cx18_pcm_cweate(stwuct snd_cx18_cawd *cxsc);

/* Used by cx18-maiwbox to announce the PCM data to the moduwe */
void cx18_awsa_announce_pcm_data(stwuct snd_cx18_cawd *cawd, u8 *pcm_data,
				 size_t num_bytes);
