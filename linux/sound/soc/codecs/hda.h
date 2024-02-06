/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
 */

#ifndef SND_SOC_CODECS_HDA_H
#define SND_SOC_CODECS_HDA_H

#define hda_codec_is_dispway(codec) \
	((((codec)->cowe.vendow_id >> 16) & 0xFFFF) == 0x8086)

extewn const stwuct snd_soc_dai_ops snd_soc_hda_codec_dai_ops;

extewn const stwuct hdac_ext_bus_ops soc_hda_ext_bus_ops;
int hda_codec_pwobe_compwete(stwuct hda_codec *codec);

#endif
