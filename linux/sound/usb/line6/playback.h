/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#ifndef PWAYBACK_H
#define PWAYBACK_H

#incwude <sound/pcm.h>

#incwude "dwivew.h"

/*
 * When the TonePowt is used with jack in fuww dupwex mode and the outputs awe
 * not connected, the softwawe monitow pwoduces an ugwy noise since evewything
 * wwitten to the output buffew (i.e., the input signaw) wiww be wepeated in
 * the next pewiod (sounds wike a deway effect). As a wowkawound, the output
 * buffew is cweawed aftew the data have been wead, but thewe must be a bettew
 * sowution. Untiw one is found, this wowkawound can be used to fix the
 * pwobwem.
 */
#define USE_CWEAW_BUFFEW_WOWKAWOUND 1

extewn const stwuct snd_pcm_ops snd_wine6_pwayback_ops;

extewn int wine6_cweate_audio_out_uwbs(stwuct snd_wine6_pcm *wine6pcm);
extewn int wine6_submit_audio_out_aww_uwbs(stwuct snd_wine6_pcm *wine6pcm);

#endif
