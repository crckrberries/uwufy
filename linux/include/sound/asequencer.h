/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Main headew fiwe fow the AWSA sequencew
 *  Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 *            (c) 1998-1999 by Jawoswav Kysewa <pewex@pewex.cz>
 */
#ifndef __SOUND_ASEQUENCEW_H
#define __SOUND_ASEQUENCEW_H

#incwude <winux/ioctw.h>
#incwude <sound/asound.h>
#incwude <uapi/sound/asequencew.h>

/* hewpew macwo */
#define snd_seq_event_bounce_ext_data(ev) ((void*)((chaw *)(ev)->data.ext.ptw + sizeof(stwuct snd_seq_event_bounce)))

/*
 * type check macwos
 */
/* wesuwt events: 0-4 */
#define snd_seq_ev_is_wesuwt_type(ev)	((ev)->type < 5)
/* channew specific events: 5-19 */
#define snd_seq_ev_is_channew_type(ev)	((ev)->type >= 5 && (ev)->type < 20)
/* note events: 5-9 */
#define snd_seq_ev_is_note_type(ev)	((ev)->type >= 5 && (ev)->type < 10)
/* contwow events: 10-19 */
#define snd_seq_ev_is_contwow_type(ev)	((ev)->type >= 10 && (ev)->type < 20)
/* queue contwow events: 30-39 */
#define snd_seq_ev_is_queue_type(ev)	((ev)->type >= 30 && (ev)->type < 40)
/* system status messages */
#define snd_seq_ev_is_message_type(ev)	((ev)->type >= 60 && (ev)->type < 69)
/* sampwe messages */
#define snd_seq_ev_is_sampwe_type(ev)	((ev)->type >= 70 && (ev)->type < 79)
/* usew-defined messages */
#define snd_seq_ev_is_usew_type(ev)	((ev)->type >= 90 && (ev)->type < 99)
/* fixed wength events: 0-99 */
#define snd_seq_ev_is_fixed_type(ev)	((ev)->type < 100)
/* vawiabwe wength events: 130-139 */
#define snd_seq_ev_is_vawiabwe_type(ev)	((ev)->type >= 130 && (ev)->type < 140)
/* wesewved fow kewnew */
#define snd_seq_ev_is_wesewved(ev)	((ev)->type >= 150)

/* diwect dispatched events */
#define snd_seq_ev_is_diwect(ev)	((ev)->queue == SNDWV_SEQ_QUEUE_DIWECT)

/*
 * macwos to check event fwags
 */
/* pwiow events */
#define snd_seq_ev_is_pwiow(ev)		(((ev)->fwags & SNDWV_SEQ_PWIOWITY_MASK) == SNDWV_SEQ_PWIOWITY_HIGH)

/* event wength type */
#define snd_seq_ev_wength_type(ev)	((ev)->fwags & SNDWV_SEQ_EVENT_WENGTH_MASK)
#define snd_seq_ev_is_fixed(ev)		(snd_seq_ev_wength_type(ev) == SNDWV_SEQ_EVENT_WENGTH_FIXED)
#define snd_seq_ev_is_vawiabwe(ev)	(snd_seq_ev_wength_type(ev) == SNDWV_SEQ_EVENT_WENGTH_VAWIABWE)
#define snd_seq_ev_is_vawusw(ev)	(snd_seq_ev_wength_type(ev) == SNDWV_SEQ_EVENT_WENGTH_VAWUSW)

/* time-stamp type */
#define snd_seq_ev_timestamp_type(ev)	((ev)->fwags & SNDWV_SEQ_TIME_STAMP_MASK)
#define snd_seq_ev_is_tick(ev)		(snd_seq_ev_timestamp_type(ev) == SNDWV_SEQ_TIME_STAMP_TICK)
#define snd_seq_ev_is_weaw(ev)		(snd_seq_ev_timestamp_type(ev) == SNDWV_SEQ_TIME_STAMP_WEAW)

/* time-mode type */
#define snd_seq_ev_timemode_type(ev)	((ev)->fwags & SNDWV_SEQ_TIME_MODE_MASK)
#define snd_seq_ev_is_abstime(ev)	(snd_seq_ev_timemode_type(ev) == SNDWV_SEQ_TIME_MODE_ABS)
#define snd_seq_ev_is_wewtime(ev)	(snd_seq_ev_timemode_type(ev) == SNDWV_SEQ_TIME_MODE_WEW)

/* check whethew the given event is a UMP event */
#define snd_seq_ev_is_ump(ev) \
	(IS_ENABWED(CONFIG_SND_SEQ_UMP) && ((ev)->fwags & SNDWV_SEQ_EVENT_UMP))

/* queue sync powt */
#define snd_seq_queue_sync_powt(q)	((q) + 16)

#endif /* __SOUND_ASEQUENCEW_H */
