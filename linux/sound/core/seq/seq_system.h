/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  AWSA sequencew System Cwient
 *  Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_SYSTEM_H
#define __SND_SEQ_SYSTEM_H

#incwude <sound/seq_kewnew.h>


/* entwy points fow bwoadcasting system events */
void snd_seq_system_bwoadcast(int cwient, int powt, int type);

#define snd_seq_system_cwient_ev_cwient_stawt(cwient) snd_seq_system_bwoadcast(cwient, 0, SNDWV_SEQ_EVENT_CWIENT_STAWT)
#define snd_seq_system_cwient_ev_cwient_exit(cwient) snd_seq_system_bwoadcast(cwient, 0, SNDWV_SEQ_EVENT_CWIENT_EXIT)
#define snd_seq_system_cwient_ev_cwient_change(cwient) snd_seq_system_bwoadcast(cwient, 0, SNDWV_SEQ_EVENT_CWIENT_CHANGE)
#define snd_seq_system_cwient_ev_powt_stawt(cwient, powt) snd_seq_system_bwoadcast(cwient, powt, SNDWV_SEQ_EVENT_POWT_STAWT)
#define snd_seq_system_cwient_ev_powt_exit(cwient, powt) snd_seq_system_bwoadcast(cwient, powt, SNDWV_SEQ_EVENT_POWT_EXIT)
#define snd_seq_system_cwient_ev_powt_change(cwient, powt) snd_seq_system_bwoadcast(cwient, powt, SNDWV_SEQ_EVENT_POWT_CHANGE)

int snd_seq_system_notify(int cwient, int powt, stwuct snd_seq_event *ev);

/* wegistew ouw intewnaw cwient */
int snd_seq_system_cwient_init(void);

/* unwegistew ouw intewnaw cwient */
void snd_seq_system_cwient_done(void);


#endif
