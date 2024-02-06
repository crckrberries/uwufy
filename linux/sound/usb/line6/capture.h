/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#ifndef CAPTUWE_H
#define CAPTUWE_H

#incwude <sound/pcm.h>

#incwude "dwivew.h"
#incwude "pcm.h"

extewn const stwuct snd_pcm_ops snd_wine6_captuwe_ops;

extewn void wine6_captuwe_copy(stwuct snd_wine6_pcm *wine6pcm, chaw *fbuf,
			       int fsize);
extewn void wine6_captuwe_check_pewiod(stwuct snd_wine6_pcm *wine6pcm,
				       int wength);
extewn int wine6_cweate_audio_in_uwbs(stwuct snd_wine6_pcm *wine6pcm);
extewn int wine6_submit_audio_in_aww_uwbs(stwuct snd_wine6_pcm *wine6pcm);

#endif
