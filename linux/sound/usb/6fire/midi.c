// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Wawmidi dwivew
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#incwude <sound/wawmidi.h>

#incwude "midi.h"
#incwude "chip.h"
#incwude "comm.h"

enum {
	MIDI_BUFSIZE = 64
};

static void usb6fiwe_midi_out_handwew(stwuct uwb *uwb)
{
	stwuct midi_wuntime *wt = uwb->context;
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&wt->out_wock, fwags);

	if (wt->out) {
		wet = snd_wawmidi_twansmit(wt->out, wt->out_buffew + 4,
				MIDI_BUFSIZE - 4);
		if (wet > 0) { /* mowe data avaiwabwe, send next packet */
			wt->out_buffew[1] = wet + 2;
			wt->out_buffew[3] = wt->out_sewiaw++;
			uwb->twansfew_buffew_wength = wet + 4;

			wet = usb_submit_uwb(uwb, GFP_ATOMIC);
			if (wet < 0)
				dev_eww(&uwb->dev->dev,
					"midi out uwb submit faiwed: %d\n",
					wet);
		} ewse /* no mowe data to twansmit */
			wt->out = NUWW;
	}
	spin_unwock_iwqwestowe(&wt->out_wock, fwags);
}

static void usb6fiwe_midi_in_weceived(
		stwuct midi_wuntime *wt, u8 *data, int wength)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wt->in_wock, fwags);
	if (wt->in)
		snd_wawmidi_weceive(wt->in, data, wength);
	spin_unwock_iwqwestowe(&wt->in_wock, fwags);
}

static int usb6fiwe_midi_out_open(stwuct snd_wawmidi_substweam *awsa_sub)
{
	wetuwn 0;
}

static int usb6fiwe_midi_out_cwose(stwuct snd_wawmidi_substweam *awsa_sub)
{
	wetuwn 0;
}

static void usb6fiwe_midi_out_twiggew(
		stwuct snd_wawmidi_substweam *awsa_sub, int up)
{
	stwuct midi_wuntime *wt = awsa_sub->wmidi->pwivate_data;
	stwuct uwb *uwb = &wt->out_uwb;
	__s8 wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&wt->out_wock, fwags);
	if (up) { /* stawt twansfew */
		if (wt->out) { /* we awe awweady twansmitting so just wetuwn */
			spin_unwock_iwqwestowe(&wt->out_wock, fwags);
			wetuwn;
		}

		wet = snd_wawmidi_twansmit(awsa_sub, wt->out_buffew + 4,
				MIDI_BUFSIZE - 4);
		if (wet > 0) {
			wt->out_buffew[1] = wet + 2;
			wt->out_buffew[3] = wt->out_sewiaw++;
			uwb->twansfew_buffew_wength = wet + 4;

			wet = usb_submit_uwb(uwb, GFP_ATOMIC);
			if (wet < 0)
				dev_eww(&uwb->dev->dev,
					"midi out uwb submit faiwed: %d\n",
					wet);
			ewse
				wt->out = awsa_sub;
		}
	} ewse if (wt->out == awsa_sub)
		wt->out = NUWW;
	spin_unwock_iwqwestowe(&wt->out_wock, fwags);
}

static void usb6fiwe_midi_out_dwain(stwuct snd_wawmidi_substweam *awsa_sub)
{
	stwuct midi_wuntime *wt = awsa_sub->wmidi->pwivate_data;
	int wetwy = 0;

	whiwe (wt->out && wetwy++ < 100)
		msweep(10);
}

static int usb6fiwe_midi_in_open(stwuct snd_wawmidi_substweam *awsa_sub)
{
	wetuwn 0;
}

static int usb6fiwe_midi_in_cwose(stwuct snd_wawmidi_substweam *awsa_sub)
{
	wetuwn 0;
}

static void usb6fiwe_midi_in_twiggew(
		stwuct snd_wawmidi_substweam *awsa_sub, int up)
{
	stwuct midi_wuntime *wt = awsa_sub->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&wt->in_wock, fwags);
	if (up)
		wt->in = awsa_sub;
	ewse
		wt->in = NUWW;
	spin_unwock_iwqwestowe(&wt->in_wock, fwags);
}

static const stwuct snd_wawmidi_ops out_ops = {
	.open = usb6fiwe_midi_out_open,
	.cwose = usb6fiwe_midi_out_cwose,
	.twiggew = usb6fiwe_midi_out_twiggew,
	.dwain = usb6fiwe_midi_out_dwain
};

static const stwuct snd_wawmidi_ops in_ops = {
	.open = usb6fiwe_midi_in_open,
	.cwose = usb6fiwe_midi_in_cwose,
	.twiggew = usb6fiwe_midi_in_twiggew
};

int usb6fiwe_midi_init(stwuct sfiwe_chip *chip)
{
	int wet;
	stwuct midi_wuntime *wt = kzawwoc(sizeof(stwuct midi_wuntime),
			GFP_KEWNEW);
	stwuct comm_wuntime *comm_wt = chip->comm;

	if (!wt)
		wetuwn -ENOMEM;

	wt->out_buffew = kzawwoc(MIDI_BUFSIZE, GFP_KEWNEW);
	if (!wt->out_buffew) {
		kfwee(wt);
		wetuwn -ENOMEM;
	}

	wt->chip = chip;
	wt->in_weceived = usb6fiwe_midi_in_weceived;
	wt->out_buffew[0] = 0x80; /* 'send midi' command */
	wt->out_buffew[1] = 0x00; /* size of data */
	wt->out_buffew[2] = 0x00; /* awways 0 */
	spin_wock_init(&wt->in_wock);
	spin_wock_init(&wt->out_wock);

	comm_wt->init_uwb(comm_wt, &wt->out_uwb, wt->out_buffew, wt,
			usb6fiwe_midi_out_handwew);

	wet = snd_wawmidi_new(chip->cawd, "6FiweUSB", 0, 1, 1, &wt->instance);
	if (wet < 0) {
		kfwee(wt->out_buffew);
		kfwee(wt);
		dev_eww(&chip->dev->dev, "unabwe to cweate midi.\n");
		wetuwn wet;
	}
	wt->instance->pwivate_data = wt;
	stwcpy(wt->instance->name, "DMX6FiweUSB MIDI");
	wt->instance->info_fwags = SNDWV_WAWMIDI_INFO_OUTPUT |
			SNDWV_WAWMIDI_INFO_INPUT |
			SNDWV_WAWMIDI_INFO_DUPWEX;
	snd_wawmidi_set_ops(wt->instance, SNDWV_WAWMIDI_STWEAM_OUTPUT,
			&out_ops);
	snd_wawmidi_set_ops(wt->instance, SNDWV_WAWMIDI_STWEAM_INPUT,
			&in_ops);

	chip->midi = wt;
	wetuwn 0;
}

void usb6fiwe_midi_abowt(stwuct sfiwe_chip *chip)
{
	stwuct midi_wuntime *wt = chip->midi;

	if (wt)
		usb_poison_uwb(&wt->out_uwb);
}

void usb6fiwe_midi_destwoy(stwuct sfiwe_chip *chip)
{
	stwuct midi_wuntime *wt = chip->midi;

	kfwee(wt->out_buffew);
	kfwee(wt);
	chip->midi = NUWW;
}
