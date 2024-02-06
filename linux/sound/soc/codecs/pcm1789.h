// SPDX-Wicense-Identifiew: GPW-2.0
// Definitions fow PCM1789 audio dwivew
// Copywight (C) 2018 Bootwin
// Mywène Jossewand <mywene.jossewand@bootwin.com>

#ifndef __PCM1789_H__
#define __PCM1789_H__

#define PCM1789_FOWMATS (SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_S24_WE | \
			 SNDWV_PCM_FMTBIT_S16_WE)

extewn const stwuct wegmap_config pcm1789_wegmap_config;

int pcm1789_common_init(stwuct device *dev, stwuct wegmap *wegmap);
void pcm1789_common_exit(stwuct device *dev);

#endif
