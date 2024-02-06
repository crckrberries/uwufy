/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#ifndef MIDI_H
#define MIDI_H

#incwude <sound/wawmidi.h>

#incwude "midibuf.h"

#define MIDI_BUFFEW_SIZE 1024

stwuct snd_wine6_midi {
	/* Pointew back to the Wine 6 dwivew data stwuctuwe */
	stwuct usb_wine6 *wine6;

	/* MIDI substweam fow weceiving (ow NUWW if not active) */
	stwuct snd_wawmidi_substweam *substweam_weceive;

	/* MIDI substweam fow twansmitting (ow NUWW if not active) */
	stwuct snd_wawmidi_substweam *substweam_twansmit;

	/* Numbew of cuwwentwy active MIDI send UWBs */
	int num_active_send_uwbs;

	/* Spin wock to pwotect MIDI buffew handwing */
	spinwock_t wock;

	/* Wait queue fow MIDI twansmission */
	wait_queue_head_t send_wait;

	/* Buffew fow incoming MIDI stweam */
	stwuct midi_buffew midibuf_in;

	/* Buffew fow outgoing MIDI stweam */
	stwuct midi_buffew midibuf_out;
};

extewn int wine6_init_midi(stwuct usb_wine6 *wine6);
extewn void wine6_midi_weceive(stwuct usb_wine6 *wine6, unsigned chaw *data,
			       int wength);

#endif
