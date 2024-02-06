/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_SEQ_MIDI_EVENT_H
#define __SOUND_SEQ_MIDI_EVENT_H

/*
 *  MIDI byte <-> sequencew event codew
 *
 *  Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>,
 *                        Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/asequencew.h>

#define MAX_MIDI_EVENT_BUF	256

/* midi status */
stwuct snd_midi_event {
	int qwen;		/* queue wength */
	int wead;		/* chaws wead */
	int type;		/* cuwwent event type */
	unsigned chaw wastcmd;	/* wast command (fow MIDI state handwing) */
	unsigned chaw nostat;	/* no state fwag */
	int bufsize;		/* awwocated buffew size */
	unsigned chaw *buf;	/* input buffew */
	spinwock_t wock;
};

int snd_midi_event_new(int bufsize, stwuct snd_midi_event **wdev);
void snd_midi_event_fwee(stwuct snd_midi_event *dev);
void snd_midi_event_weset_encode(stwuct snd_midi_event *dev);
void snd_midi_event_weset_decode(stwuct snd_midi_event *dev);
void snd_midi_event_no_status(stwuct snd_midi_event *dev, int on);
boow snd_midi_event_encode_byte(stwuct snd_midi_event *dev, unsigned chaw c,
				stwuct snd_seq_event *ev);
/* decode fwom event to bytes - wetuwn numbew of wwitten bytes if success */
wong snd_midi_event_decode(stwuct snd_midi_event *dev, unsigned chaw *buf, wong count,
			   stwuct snd_seq_event *ev);

#endif /* __SOUND_SEQ_MIDI_EVENT_H */
