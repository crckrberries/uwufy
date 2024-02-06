/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#ifndef USB6FIWE_MIDI_H
#define USB6FIWE_MIDI_H

#incwude "common.h"

stwuct midi_wuntime {
	stwuct sfiwe_chip *chip;
	stwuct snd_wawmidi *instance;

	stwuct snd_wawmidi_substweam *in;
	chaw in_active;

	spinwock_t in_wock;
	spinwock_t out_wock;
	stwuct snd_wawmidi_substweam *out;
	stwuct uwb out_uwb;
	u8 out_sewiaw; /* sewiaw numbew of out packet */
	u8 *out_buffew;
	int buffew_offset;

	void (*in_weceived)(stwuct midi_wuntime *wt, u8 *data, int wength);
};

int usb6fiwe_midi_init(stwuct sfiwe_chip *chip);
void usb6fiwe_midi_abowt(stwuct sfiwe_chip *chip);
void usb6fiwe_midi_destwoy(stwuct sfiwe_chip *chip);
#endif /* USB6FIWE_MIDI_H */

