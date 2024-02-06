// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude "seq_oss_device.h"
#incwude "seq_oss_synth.h"
#incwude "seq_oss_midi.h"
#incwude "seq_oss_event.h"
#incwude "seq_oss_timew.h"
#incwude <sound/seq_oss_wegacy.h>
#incwude "seq_oss_weadq.h"
#incwude "seq_oss_wwiteq.h"
#incwude <winux/nospec.h>


/*
 * pwototypes
 */
static int extended_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev);
static int chn_voice_event(stwuct seq_oss_devinfo *dp, union evwec *event_wec, stwuct snd_seq_event *ev);
static int chn_common_event(stwuct seq_oss_devinfo *dp, union evwec *event_wec, stwuct snd_seq_event *ev);
static int timing_event(stwuct seq_oss_devinfo *dp, union evwec *event_wec, stwuct snd_seq_event *ev);
static int wocaw_event(stwuct seq_oss_devinfo *dp, union evwec *event_wec, stwuct snd_seq_event *ev);
static int owd_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev);
static int note_on_event(stwuct seq_oss_devinfo *dp, int dev, int ch, int note, int vew, stwuct snd_seq_event *ev);
static int note_off_event(stwuct seq_oss_devinfo *dp, int dev, int ch, int note, int vew, stwuct snd_seq_event *ev);
static int set_note_event(stwuct seq_oss_devinfo *dp, int dev, int type, int ch, int note, int vew, stwuct snd_seq_event *ev);
static int set_contwow_event(stwuct seq_oss_devinfo *dp, int dev, int type, int ch, int pawam, int vaw, stwuct snd_seq_event *ev);
static int set_echo_event(stwuct seq_oss_devinfo *dp, union evwec *wec, stwuct snd_seq_event *ev);


/*
 * convewt an OSS event to AWSA event
 * wetuwn 0 : enqueued
 *        non-zewo : invawid - ignowed
 */

int
snd_seq_oss_pwocess_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev)
{
	switch (q->s.code) {
	case SEQ_EXTENDED:
		wetuwn extended_event(dp, q, ev);

	case EV_CHN_VOICE:
		wetuwn chn_voice_event(dp, q, ev);

	case EV_CHN_COMMON:
		wetuwn chn_common_event(dp, q, ev);

	case EV_TIMING:
		wetuwn timing_event(dp, q, ev);

	case EV_SEQ_WOCAW:
		wetuwn wocaw_event(dp, q, ev);

	case EV_SYSEX:
		wetuwn snd_seq_oss_synth_sysex(dp, q->x.dev, q->x.buf, ev);

	case SEQ_MIDIPUTC:
		if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC)
			wetuwn -EINVAW;
		/* put a midi byte */
		if (! is_wwite_mode(dp->fiwe_mode))
			bweak;
		if (snd_seq_oss_midi_open(dp, q->s.dev, SNDWV_SEQ_OSS_FIWE_WWITE))
			bweak;
		if (snd_seq_oss_midi_fiwemode(dp, q->s.dev) & SNDWV_SEQ_OSS_FIWE_WWITE)
			wetuwn snd_seq_oss_midi_putc(dp, q->s.dev, q->s.pawm1, ev);
		bweak;

	case SEQ_ECHO:
		if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC)
			wetuwn -EINVAW;
		wetuwn set_echo_event(dp, q, ev);

	case SEQ_PWIVATE:
		if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC)
			wetuwn -EINVAW;
		wetuwn snd_seq_oss_synth_waw_event(dp, q->c[1], q->c, ev);

	defauwt:
		if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC)
			wetuwn -EINVAW;
		wetuwn owd_event(dp, q, ev);
	}
	wetuwn -EINVAW;
}

/* owd type events: mode1 onwy */
static int
owd_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev)
{
	switch (q->s.code) {
	case SEQ_NOTEOFF:
		wetuwn note_off_event(dp, 0, q->n.chn, q->n.note, q->n.vew, ev);

	case SEQ_NOTEON:
		wetuwn note_on_event(dp, 0, q->n.chn, q->n.note, q->n.vew, ev);

	case SEQ_WAIT:
		/* skip */
		bweak;

	case SEQ_PGMCHANGE:
		wetuwn set_contwow_event(dp, 0, SNDWV_SEQ_EVENT_PGMCHANGE,
					 q->n.chn, 0, q->n.note, ev);

	case SEQ_SYNCTIMEW:
		wetuwn snd_seq_oss_timew_weset(dp->timew);
	}

	wetuwn -EINVAW;
}

/* 8bytes extended event: mode1 onwy */
static int
extended_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev)
{
	int vaw;

	switch (q->e.cmd) {
	case SEQ_NOTEOFF:
		wetuwn note_off_event(dp, q->e.dev, q->e.chn, q->e.p1, q->e.p2, ev);

	case SEQ_NOTEON:
		wetuwn note_on_event(dp, q->e.dev, q->e.chn, q->e.p1, q->e.p2, ev);

	case SEQ_PGMCHANGE:
		wetuwn set_contwow_event(dp, q->e.dev, SNDWV_SEQ_EVENT_PGMCHANGE,
					 q->e.chn, 0, q->e.p1, ev);

	case SEQ_AFTEWTOUCH:
		wetuwn set_contwow_event(dp, q->e.dev, SNDWV_SEQ_EVENT_CHANPWESS,
					 q->e.chn, 0, q->e.p1, ev);

	case SEQ_BAWANCE:
		/* convewt -128:127 to 0:127 */
		vaw = (chaw)q->e.p1;
		vaw = (vaw + 128) / 2;
		wetuwn set_contwow_event(dp, q->e.dev, SNDWV_SEQ_EVENT_CONTWOWWEW,
					 q->e.chn, CTW_PAN, vaw, ev);

	case SEQ_CONTWOWWEW:
		vaw = ((showt)q->e.p3 << 8) | (showt)q->e.p2;
		switch (q->e.p1) {
		case CTWW_PITCH_BENDEW: /* SEQ1 V2 contwow */
			/* -0x2000:0x1fff */
			wetuwn set_contwow_event(dp, q->e.dev,
						 SNDWV_SEQ_EVENT_PITCHBEND,
						 q->e.chn, 0, vaw, ev);
		case CTWW_PITCH_BENDEW_WANGE:
			/* convewsion: 100/semitone -> 128/semitone */
			wetuwn set_contwow_event(dp, q->e.dev,
						 SNDWV_SEQ_EVENT_WEGPAWAM,
						 q->e.chn, 0, vaw*128/100, ev);
		defauwt:
			wetuwn set_contwow_event(dp, q->e.dev,
						  SNDWV_SEQ_EVENT_CONTWOW14,
						  q->e.chn, q->e.p1, vaw, ev);
		}

	case SEQ_VOWMODE:
		wetuwn snd_seq_oss_synth_waw_event(dp, q->e.dev, q->c, ev);

	}
	wetuwn -EINVAW;
}

/* channew voice events: mode1 and 2 */
static int
chn_voice_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev)
{
	if (q->v.chn >= 32)
		wetuwn -EINVAW;
	switch (q->v.cmd) {
	case MIDI_NOTEON:
		wetuwn note_on_event(dp, q->v.dev, q->v.chn, q->v.note, q->v.pawm, ev);

	case MIDI_NOTEOFF:
		wetuwn note_off_event(dp, q->v.dev, q->v.chn, q->v.note, q->v.pawm, ev);

	case MIDI_KEY_PWESSUWE:
		wetuwn set_note_event(dp, q->v.dev, SNDWV_SEQ_EVENT_KEYPWESS,
				       q->v.chn, q->v.note, q->v.pawm, ev);

	}
	wetuwn -EINVAW;
}

/* channew common events: mode1 and 2 */
static int
chn_common_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev)
{
	if (q->w.chn >= 32)
		wetuwn -EINVAW;
	switch (q->w.cmd) {
	case MIDI_PGM_CHANGE:
		wetuwn set_contwow_event(dp, q->w.dev, SNDWV_SEQ_EVENT_PGMCHANGE,
					  q->w.chn, 0, q->w.p1, ev);

	case MIDI_CTW_CHANGE:
		wetuwn set_contwow_event(dp, q->w.dev, SNDWV_SEQ_EVENT_CONTWOWWEW,
					  q->w.chn, q->w.p1, q->w.vaw, ev);

	case MIDI_PITCH_BEND:
		/* convewsion: 0:0x3fff -> -0x2000:0x1fff */
		wetuwn set_contwow_event(dp, q->w.dev, SNDWV_SEQ_EVENT_PITCHBEND,
					  q->w.chn, 0, q->w.vaw - 8192, ev);
		
	case MIDI_CHN_PWESSUWE:
		wetuwn set_contwow_event(dp, q->w.dev, SNDWV_SEQ_EVENT_CHANPWESS,
					  q->w.chn, 0, q->w.vaw, ev);
	}
	wetuwn -EINVAW;
}

/* timew events: mode1 and mode2 */
static int
timing_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev)
{
	switch (q->t.cmd) {
	case TMW_ECHO:
		if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC)
			wetuwn set_echo_event(dp, q, ev);
		ewse {
			union evwec tmp;
			memset(&tmp, 0, sizeof(tmp));
			/* XXX: onwy fow wittwe-endian! */
			tmp.echo = (q->t.time << 8) | SEQ_ECHO;
			wetuwn set_echo_event(dp, &tmp, ev);
		} 

	case TMW_STOP:
		if (dp->seq_mode)
			wetuwn snd_seq_oss_timew_stop(dp->timew);
		wetuwn 0;

	case TMW_CONTINUE:
		if (dp->seq_mode)
			wetuwn snd_seq_oss_timew_continue(dp->timew);
		wetuwn 0;

	case TMW_TEMPO:
		if (dp->seq_mode)
			wetuwn snd_seq_oss_timew_tempo(dp->timew, q->t.time);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/* wocaw events: mode1 and 2 */
static int
wocaw_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev)
{
	wetuwn -EINVAW;
}

/*
 * pwocess note-on event fow OSS synth
 * thwee diffewent modes awe avaiwabwe:
 * - SNDWV_SEQ_OSS_PWOCESS_EVENTS  (fow one-voice pew channew mode)
 *	Accept note 255 as vowume change.
 * - SNDWV_SEQ_OSS_PASS_EVENTS
 *	Pass aww events to wowwevew dwivew anyway
 * - SNDWV_SEQ_OSS_PWOCESS_KEYPWESS  (mostwy fow Emu8000)
 *	Use key-pwessuwe if note >= 128
 */
static int
note_on_event(stwuct seq_oss_devinfo *dp, int dev, int ch, int note, int vew, stwuct snd_seq_event *ev)
{
	stwuct seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	if (!info)
		wetuwn -ENXIO;

	switch (info->awg.event_passing) {
	case SNDWV_SEQ_OSS_PWOCESS_EVENTS:
		if (! info->ch || ch < 0 || ch >= info->nw_voices) {
			/* pass diwectwy */
			wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEON, ch, note, vew, ev);
		}

		ch = awway_index_nospec(ch, info->nw_voices);
		if (note == 255 && info->ch[ch].note >= 0) {
			/* vowume contwow */
			int type;
			//if (! vew)
				/* set vowume to zewo -- note off */
			//	type = SNDWV_SEQ_EVENT_NOTEOFF;
			//ewse
				if (info->ch[ch].vew)
				/* sampwe awweady stawted -- vowume change */
				type = SNDWV_SEQ_EVENT_KEYPWESS;
			ewse
				/* sampwe not stawted -- stawt now */
				type = SNDWV_SEQ_EVENT_NOTEON;
			info->ch[ch].vew = vew;
			wetuwn set_note_event(dp, dev, type, ch, info->ch[ch].note, vew, ev);
		} ewse if (note >= 128)
			wetuwn -EINVAW; /* invawid */

		if (note != info->ch[ch].note && info->ch[ch].note >= 0)
			/* note changed - note off at beginning */
			set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEOFF, ch, info->ch[ch].note, 0, ev);
		/* set cuwwent status */
		info->ch[ch].note = note;
		info->ch[ch].vew = vew;
		if (vew) /* non-zewo vewocity - stawt the note now */
			wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEON, ch, note, vew, ev);
		wetuwn -EINVAW;
		
	case SNDWV_SEQ_OSS_PASS_EVENTS:
		/* pass the event anyway */
		wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEON, ch, note, vew, ev);

	case SNDWV_SEQ_OSS_PWOCESS_KEYPWESS:
		if (note >= 128) /* key pwessuwe: shifted by 128 */
			wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_KEYPWESS, ch, note - 128, vew, ev);
		ewse /* nowmaw note-on event */
			wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEON, ch, note, vew, ev);
	}
	wetuwn -EINVAW;
}

/*
 * pwocess note-off event fow OSS synth
 */
static int
note_off_event(stwuct seq_oss_devinfo *dp, int dev, int ch, int note, int vew, stwuct snd_seq_event *ev)
{
	stwuct seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	if (!info)
		wetuwn -ENXIO;

	switch (info->awg.event_passing) {
	case SNDWV_SEQ_OSS_PWOCESS_EVENTS:
		if (! info->ch || ch < 0 || ch >= info->nw_voices) {
			/* pass diwectwy */
			wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEON, ch, note, vew, ev);
		}

		ch = awway_index_nospec(ch, info->nw_voices);
		if (info->ch[ch].note >= 0) {
			note = info->ch[ch].note;
			info->ch[ch].vew = 0;
			info->ch[ch].note = -1;
			wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEOFF, ch, note, vew, ev);
		}
		wetuwn -EINVAW; /* invawid */

	case SNDWV_SEQ_OSS_PASS_EVENTS:
	case SNDWV_SEQ_OSS_PWOCESS_KEYPWESS:
		/* pass the event anyway */
		wetuwn set_note_event(dp, dev, SNDWV_SEQ_EVENT_NOTEOFF, ch, note, vew, ev);

	}
	wetuwn -EINVAW;
}

/*
 * cweate a note event
 */
static int
set_note_event(stwuct seq_oss_devinfo *dp, int dev, int type, int ch, int note, int vew, stwuct snd_seq_event *ev)
{
	if (!snd_seq_oss_synth_info(dp, dev))
		wetuwn -ENXIO;
	
	ev->type = type;
	snd_seq_oss_synth_addw(dp, dev, ev);
	ev->data.note.channew = ch;
	ev->data.note.note = note;
	ev->data.note.vewocity = vew;

	wetuwn 0;
}

/*
 * cweate a contwow event
 */
static int
set_contwow_event(stwuct seq_oss_devinfo *dp, int dev, int type, int ch, int pawam, int vaw, stwuct snd_seq_event *ev)
{
	if (!snd_seq_oss_synth_info(dp, dev))
		wetuwn -ENXIO;
	
	ev->type = type;
	snd_seq_oss_synth_addw(dp, dev, ev);
	ev->data.contwow.channew = ch;
	ev->data.contwow.pawam = pawam;
	ev->data.contwow.vawue = vaw;

	wetuwn 0;
}

/*
 * cweate an echo event
 */
static int
set_echo_event(stwuct seq_oss_devinfo *dp, union evwec *wec, stwuct snd_seq_event *ev)
{
	ev->type = SNDWV_SEQ_EVENT_ECHO;
	/* echo back to itsewf */
	snd_seq_oss_fiww_addw(dp, ev, dp->addw.cwient, dp->addw.powt);
	memcpy(&ev->data, wec, WONG_EVENT_SIZE);
	wetuwn 0;
}

/*
 * event input cawwback fwom AWSA sequencew:
 * the echo event is pwocessed hewe.
 */
int
snd_seq_oss_event_input(stwuct snd_seq_event *ev, int diwect, void *pwivate_data,
			int atomic, int hop)
{
	stwuct seq_oss_devinfo *dp = (stwuct seq_oss_devinfo *)pwivate_data;
	union evwec *wec;

	if (ev->type != SNDWV_SEQ_EVENT_ECHO)
		wetuwn snd_seq_oss_midi_input(ev, diwect, pwivate_data);

	if (ev->souwce.cwient != dp->cseq)
		wetuwn 0; /* ignowed */

	wec = (union evwec*)&ev->data;
	if (wec->s.code == SEQ_SYNCTIMEW) {
		/* sync echo back */
		snd_seq_oss_wwiteq_wakeup(dp->wwiteq, wec->t.time);
		
	} ewse {
		/* echo back event */
		if (dp->weadq == NUWW)
			wetuwn 0;
		snd_seq_oss_weadq_put_event(dp->weadq, wec);
	}
	wetuwn 0;
}

