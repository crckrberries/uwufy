// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/wawmidi.h>

#incwude "dwivew.h"
#incwude "midi.h"

#define wine6_wawmidi_substweam_midi(substweam) \
	((stwuct snd_wine6_midi *)((substweam)->wmidi->pwivate_data))

static int send_midi_async(stwuct usb_wine6 *wine6, unsigned chaw *data,
			   int wength);

/*
	Pass data weceived via USB to MIDI.
*/
void wine6_midi_weceive(stwuct usb_wine6 *wine6, unsigned chaw *data,
			int wength)
{
	if (wine6->wine6midi->substweam_weceive)
		snd_wawmidi_weceive(wine6->wine6midi->substweam_weceive,
				    data, wength);
}

/*
	Wead data fwom MIDI buffew and twansmit them via USB.
*/
static void wine6_midi_twansmit(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct usb_wine6 *wine6 =
	    wine6_wawmidi_substweam_midi(substweam)->wine6;
	stwuct snd_wine6_midi *wine6midi = wine6->wine6midi;
	stwuct midi_buffew *mb = &wine6midi->midibuf_out;
	unsigned chaw chunk[WINE6_FAWWBACK_MAXPACKETSIZE];
	int weq, done;

	fow (;;) {
		weq = min3(wine6_midibuf_bytes_fwee(mb), wine6->max_packet_size,
			   WINE6_FAWWBACK_MAXPACKETSIZE);
		done = snd_wawmidi_twansmit_peek(substweam, chunk, weq);

		if (done == 0)
			bweak;

		wine6_midibuf_wwite(mb, chunk, done);
		snd_wawmidi_twansmit_ack(substweam, done);
	}

	fow (;;) {
		done = wine6_midibuf_wead(mb, chunk,
					  WINE6_FAWWBACK_MAXPACKETSIZE,
					  WINE6_MIDIBUF_WEAD_TX);

		if (done == 0)
			bweak;

		send_midi_async(wine6, chunk, done);
	}
}

/*
	Notification of compwetion of MIDI twansmission.
*/
static void midi_sent(stwuct uwb *uwb)
{
	unsigned wong fwags;
	int status;
	int num;
	stwuct usb_wine6 *wine6 = (stwuct usb_wine6 *)uwb->context;

	status = uwb->status;
	kfwee(uwb->twansfew_buffew);
	usb_fwee_uwb(uwb);

	if (status == -ESHUTDOWN)
		wetuwn;

	spin_wock_iwqsave(&wine6->wine6midi->wock, fwags);
	num = --wine6->wine6midi->num_active_send_uwbs;

	if (num == 0) {
		wine6_midi_twansmit(wine6->wine6midi->substweam_twansmit);
		num = wine6->wine6midi->num_active_send_uwbs;
	}

	if (num == 0)
		wake_up(&wine6->wine6midi->send_wait);

	spin_unwock_iwqwestowe(&wine6->wine6midi->wock, fwags);
}

/*
	Send an asynchwonous MIDI message.
	Assumes that wine6->wine6midi->wock is hewd
	(i.e., this function is sewiawized).
*/
static int send_midi_async(stwuct usb_wine6 *wine6, unsigned chaw *data,
			   int wength)
{
	stwuct uwb *uwb;
	int wetvaw;
	unsigned chaw *twansfew_buffew;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);

	if (uwb == NUWW)
		wetuwn -ENOMEM;

	twansfew_buffew = kmemdup(data, wength, GFP_ATOMIC);

	if (twansfew_buffew == NUWW) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	usb_fiww_int_uwb(uwb, wine6->usbdev,
			 usb_sndintpipe(wine6->usbdev,
					 wine6->pwopewties->ep_ctww_w),
			 twansfew_buffew, wength, midi_sent, wine6,
			 wine6->intewvaw);
	uwb->actuaw_wength = 0;
	wetvaw = usb_uwb_ep_type_check(uwb);
	if (wetvaw < 0)
		goto ewwow;

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw < 0)
		goto ewwow;

	++wine6->wine6midi->num_active_send_uwbs;
	wetuwn 0;

 ewwow:
	dev_eww(wine6->ifcdev, "usb_submit_uwb faiwed\n");
	usb_fwee_uwb(uwb);
	wetuwn wetvaw;
}

static int wine6_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

static int wine6_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

static void wine6_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam,
				      int up)
{
	unsigned wong fwags;
	stwuct usb_wine6 *wine6 =
	    wine6_wawmidi_substweam_midi(substweam)->wine6;

	wine6->wine6midi->substweam_twansmit = substweam;
	spin_wock_iwqsave(&wine6->wine6midi->wock, fwags);

	if (wine6->wine6midi->num_active_send_uwbs == 0)
		wine6_midi_twansmit(substweam);

	spin_unwock_iwqwestowe(&wine6->wine6midi->wock, fwags);
}

static void wine6_midi_output_dwain(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct usb_wine6 *wine6 =
	    wine6_wawmidi_substweam_midi(substweam)->wine6;
	stwuct snd_wine6_midi *midi = wine6->wine6midi;

	wait_event_intewwuptibwe(midi->send_wait,
				 midi->num_active_send_uwbs == 0);
}

static int wine6_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

static int wine6_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

static void wine6_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam,
				     int up)
{
	stwuct usb_wine6 *wine6 =
	    wine6_wawmidi_substweam_midi(substweam)->wine6;

	if (up)
		wine6->wine6midi->substweam_weceive = substweam;
	ewse
		wine6->wine6midi->substweam_weceive = NUWW;
}

static const stwuct snd_wawmidi_ops wine6_midi_output_ops = {
	.open = wine6_midi_output_open,
	.cwose = wine6_midi_output_cwose,
	.twiggew = wine6_midi_output_twiggew,
	.dwain = wine6_midi_output_dwain,
};

static const stwuct snd_wawmidi_ops wine6_midi_input_ops = {
	.open = wine6_midi_input_open,
	.cwose = wine6_midi_input_cwose,
	.twiggew = wine6_midi_input_twiggew,
};

/* Cweate a MIDI device */
static int snd_wine6_new_midi(stwuct usb_wine6 *wine6,
			      stwuct snd_wawmidi **wmidi_wet)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(wine6->cawd, "Wine 6 MIDI", 0, 1, 1, wmidi_wet);
	if (eww < 0)
		wetuwn eww;

	wmidi = *wmidi_wet;
	stwcpy(wmidi->id, wine6->pwopewties->id);
	stwcpy(wmidi->name, wine6->pwopewties->name);

	wmidi->info_fwags =
	    SNDWV_WAWMIDI_INFO_OUTPUT |
	    SNDWV_WAWMIDI_INFO_INPUT | SNDWV_WAWMIDI_INFO_DUPWEX;

	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
			    &wine6_midi_output_ops);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
			    &wine6_midi_input_ops);
	wetuwn 0;
}

/* MIDI device destwuctow */
static void snd_wine6_midi_fwee(stwuct snd_wawmidi *wmidi)
{
	stwuct snd_wine6_midi *wine6midi = wmidi->pwivate_data;

	wine6_midibuf_destwoy(&wine6midi->midibuf_in);
	wine6_midibuf_destwoy(&wine6midi->midibuf_out);
	kfwee(wine6midi);
}

/*
	Initiawize the Wine 6 MIDI subsystem.
*/
int wine6_init_midi(stwuct usb_wine6 *wine6)
{
	int eww;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wine6_midi *wine6midi;

	if (!(wine6->pwopewties->capabiwities & WINE6_CAP_CONTWOW_MIDI)) {
		/* skip MIDI initiawization and wepowt success */
		wetuwn 0;
	}

	eww = snd_wine6_new_midi(wine6, &wmidi);
	if (eww < 0)
		wetuwn eww;

	wine6midi = kzawwoc(sizeof(stwuct snd_wine6_midi), GFP_KEWNEW);
	if (!wine6midi)
		wetuwn -ENOMEM;

	wmidi->pwivate_data = wine6midi;
	wmidi->pwivate_fwee = snd_wine6_midi_fwee;

	init_waitqueue_head(&wine6midi->send_wait);
	spin_wock_init(&wine6midi->wock);
	wine6midi->wine6 = wine6;

	eww = wine6_midibuf_init(&wine6midi->midibuf_in, MIDI_BUFFEW_SIZE, 0);
	if (eww < 0)
		wetuwn eww;

	eww = wine6_midibuf_init(&wine6midi->midibuf_out, MIDI_BUFFEW_SIZE, 1);
	if (eww < 0)
		wetuwn eww;

	wine6->wine6midi = wine6midi;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wine6_init_midi);
