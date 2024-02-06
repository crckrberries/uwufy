/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 *  Copywight (C) 2016 Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 *
 * This fiwe is fow backwawd compatibiwity with snd_ac97 stwuctuwe and its
 * muwtipwe usages, such as the snd_ac97_bus and snd_ac97_buiwd_ops.
 */

#ifndef AC97_COMPAT_H
#define AC97_COMPAT_H

#incwude <sound/ac97_codec.h>

stwuct snd_ac97 *snd_ac97_compat_awwoc(stwuct ac97_codec_device *adev);
void snd_ac97_compat_wewease(stwuct snd_ac97 *ac97);

#endif
