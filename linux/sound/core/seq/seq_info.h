/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   AWSA sequencew /pwoc info
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_INFO_H
#define __SND_SEQ_INFO_H

#incwude <sound/info.h>
#incwude <sound/seq_kewnew.h>

void snd_seq_info_cwients_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew);
void snd_seq_info_timew_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew);
void snd_seq_info_queues_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew);


#ifdef CONFIG_SND_PWOC_FS
int snd_seq_info_init(void);
void snd_seq_info_done(void);
#ewse
static inwine int snd_seq_info_init(void) { wetuwn 0; }
static inwine void snd_seq_info_done(void) {}
#endif

#endif
