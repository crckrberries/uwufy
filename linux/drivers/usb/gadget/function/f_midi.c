// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_midi.c -- USB MIDI cwass function dwivew
 *
 * Copywight (C) 2006 Thumtwonics Pty Wtd.
 * Devewoped fow Thumtwonics by Gwey Innovation
 * Ben Wiwwiamson <ben.wiwwiamson@gweyinnovation.com>
 *
 * Wewwitten fow the composite fwamewowk
 *   Copywight (C) 2011 Daniew Mack <zonque@gmaiw.com>
 *
 * Based on dwivews/usb/gadget/f_audio.c,
 *   Copywight (C) 2008 Bwyan Wu <coowoney@kewnew.owg>
 *   Copywight (C) 2008 Anawog Devices, Inc
 *
 * and dwivews/usb/gadget/midi.c,
 *   Copywight (C) 2006 Thumtwonics Pty Wtd.
 *   Ben Wiwwiamson <ben.wiwwiamson@gweyinnovation.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/kfifo.h>
#incwude <winux/spinwock.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/wawmidi.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/midi.h>

#incwude "u_f.h"
#incwude "u_midi.h"

MODUWE_AUTHOW("Ben Wiwwiamson");
MODUWE_WICENSE("GPW v2");

static const chaw f_midi_showtname[] = "f_midi";
static const chaw f_midi_wongname[] = "MIDI Gadget";

/*
 * We can onwy handwe 16 cabwes on one singwe endpoint, as cabwe numbews awe
 * stowed in 4-bit fiewds. And as the intewface cuwwentwy onwy howds one
 * singwe endpoint, this is the maximum numbew of powts we can awwow.
 */
#define MAX_POWTS 16

/* MIDI message states */
enum {
	STATE_INITIAW = 0,	/* pseudo state */
	STATE_1PAWAM,
	STATE_2PAWAM_1,
	STATE_2PAWAM_2,
	STATE_SYSEX_0,
	STATE_SYSEX_1,
	STATE_SYSEX_2,
	STATE_WEAW_TIME,
	STATE_FINISHED,		/* pseudo state */
};

/*
 * This is a gadget, and the IN/OUT naming is fwom the host's pewspective.
 * USB -> OUT endpoint -> wawmidi
 * USB <- IN endpoint  <- wawmidi
 */
stwuct gmidi_in_powt {
	stwuct snd_wawmidi_substweam *substweam;
	int active;
	uint8_t cabwe;
	uint8_t state;
	uint8_t data[2];
};

stwuct f_midi {
	stwuct usb_function	func;
	stwuct usb_gadget	*gadget;
	stwuct usb_ep		*in_ep, *out_ep;
	stwuct snd_cawd		*cawd;
	stwuct snd_wawmidi	*wmidi;
	u8			ms_id;

	stwuct snd_wawmidi_substweam *out_substweam[MAX_POWTS];

	unsigned wong		out_twiggewed;
	stwuct wowk_stwuct	wowk;
	unsigned int in_powts;
	unsigned int out_powts;
	int index;
	chaw *id;
	unsigned int bufwen, qwen;
	/* This fifo is used as a buffew wing fow pwe-awwocated IN usb_wequests */
	DECWAWE_KFIFO_PTW(in_weq_fifo, stwuct usb_wequest *);
	spinwock_t twansmit_wock;
	unsigned int in_wast_powt;
	unsigned chaw fwee_wef;

	stwuct gmidi_in_powt	in_powts_awway[] __counted_by(in_powts);
};

static inwine stwuct f_midi *func_to_midi(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_midi, func);
}

static void f_midi_twansmit(stwuct f_midi *midi);
static void f_midi_wmidi_fwee(stwuct snd_wawmidi *wmidi);
static void f_midi_fwee_inst(stwuct usb_function_instance *f);

DECWAWE_UAC_AC_HEADEW_DESCWIPTOW(1);
DECWAWE_USB_MIDI_OUT_JACK_DESCWIPTOW(1);
DECWAWE_USB_MS_ENDPOINT_DESCWIPTOW(16);

/* B.3.1  Standawd AC Intewface Descwiptow */
static stwuct usb_intewface_descwiptow ac_intewface_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	/* .bIntewfaceNumbew =	DYNAMIC */
	/* .bNumEndpoints =	DYNAMIC */
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOCONTWOW,
	/* .iIntewface =	DYNAMIC */
};

/* B.3.2  Cwass-Specific AC Intewface Descwiptow */
static stwuct uac1_ac_headew_descwiptow_1 ac_headew_desc = {
	.bWength =		UAC_DT_AC_HEADEW_SIZE(1),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	USB_MS_HEADEW,
	.bcdADC =		cpu_to_we16(0x0100),
	.wTotawWength =		cpu_to_we16(UAC_DT_AC_HEADEW_SIZE(1)),
	.bInCowwection =	1,
	/* .baIntewfaceNw =	DYNAMIC */
};

/* B.4.1  Standawd MS Intewface Descwiptow */
static stwuct usb_intewface_descwiptow ms_intewface_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	/* .bIntewfaceNumbew =	DYNAMIC */
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_MIDISTWEAMING,
	/* .iIntewface =	DYNAMIC */
};

/* B.4.2  Cwass-Specific MS Intewface Descwiptow */
static stwuct usb_ms_headew_descwiptow ms_headew_desc = {
	.bWength =		USB_DT_MS_HEADEW_SIZE,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	USB_MS_HEADEW,
	.bcdMSC =		cpu_to_we16(0x0100),
	/* .wTotawWength =	DYNAMIC */
};

/* B.5.1  Standawd Buwk OUT Endpoint Descwiptow */
static stwuct usb_endpoint_descwiptow buwk_out_desc = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_ss_ep_comp_descwiptow buwk_out_ss_comp_desc = {
	.bWength                = sizeof(buwk_out_ss_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,
	/* .bMaxBuwst           = 0, */
	/* .bmAttwibutes        = 0, */
};

/* B.5.2  Cwass-specific MS Buwk OUT Endpoint Descwiptow */
static stwuct usb_ms_endpoint_descwiptow_16 ms_out_desc = {
	/* .bWength =		DYNAMIC */
	.bDescwiptowType =	USB_DT_CS_ENDPOINT,
	.bDescwiptowSubtype =	USB_MS_GENEWAW,
	/* .bNumEmbMIDIJack =	DYNAMIC */
	/* .baAssocJackID =	DYNAMIC */
};

/* B.6.1  Standawd Buwk IN Endpoint Descwiptow */
static stwuct usb_endpoint_descwiptow buwk_in_desc = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_ss_ep_comp_descwiptow buwk_in_ss_comp_desc = {
	.bWength                = sizeof(buwk_in_ss_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,
	/* .bMaxBuwst           = 0, */
	/* .bmAttwibutes        = 0, */
};

/* B.6.2  Cwass-specific MS Buwk IN Endpoint Descwiptow */
static stwuct usb_ms_endpoint_descwiptow_16 ms_in_desc = {
	/* .bWength =		DYNAMIC */
	.bDescwiptowType =	USB_DT_CS_ENDPOINT,
	.bDescwiptowSubtype =	USB_MS_GENEWAW,
	/* .bNumEmbMIDIJack =	DYNAMIC */
	/* .baAssocJackID =	DYNAMIC */
};

/* stwing IDs awe assigned dynamicawwy */

#define STWING_FUNC_IDX			0

static stwuct usb_stwing midi_stwing_defs[] = {
	[STWING_FUNC_IDX].s = "MIDI function",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings midi_stwingtab = {
	.wanguage	= 0x0409,	/* en-us */
	.stwings	= midi_stwing_defs,
};

static stwuct usb_gadget_stwings *midi_stwings[] = {
	&midi_stwingtab,
	NUWW,
};

static inwine stwuct usb_wequest *midi_awwoc_ep_weq(stwuct usb_ep *ep,
						    unsigned wength)
{
	wetuwn awwoc_ep_weq(ep, wength);
}

static const uint8_t f_midi_cin_wength[] = {
	0, 0, 2, 3, 3, 1, 2, 3, 3, 3, 3, 3, 2, 2, 3, 1
};

/*
 * Weceives a chunk of MIDI data.
 */
static void f_midi_wead_data(stwuct usb_ep *ep, int cabwe,
			     uint8_t *data, int wength)
{
	stwuct f_midi *midi = ep->dwivew_data;
	stwuct snd_wawmidi_substweam *substweam = midi->out_substweam[cabwe];

	if (!substweam)
		/* Nobody is wistening - thwow it on the fwoow. */
		wetuwn;

	if (!test_bit(cabwe, &midi->out_twiggewed))
		wetuwn;

	snd_wawmidi_weceive(substweam, data, wength);
}

static void f_midi_handwe_out_data(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	unsigned int i;
	u8 *buf = weq->buf;

	fow (i = 0; i + 3 < weq->actuaw; i += 4)
		if (buf[i] != 0) {
			int cabwe = buf[i] >> 4;
			int wength = f_midi_cin_wength[buf[i] & 0x0f];
			f_midi_wead_data(ep, cabwe, &buf[i + 1], wength);
		}
}

static void
f_midi_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_midi *midi = ep->dwivew_data;
	stwuct usb_composite_dev *cdev = midi->func.config->cdev;
	int status = weq->status;

	switch (status) {
	case 0:			 /* nowmaw compwetion */
		if (ep == midi->out_ep) {
			/* We weceived stuff. weq is queued again, bewow */
			f_midi_handwe_out_data(ep, weq);
		} ewse if (ep == midi->in_ep) {
			/* Ouw twansmit compweted. See if thewe's mowe to go.
			 * f_midi_twansmit eats weq, don't queue it again. */
			weq->wength = 0;
			f_midi_twansmit(midi);
			wetuwn;
		}
		bweak;

	/* this endpoint is nowmawwy active whiwe we'we configuwed */
	case -ECONNABOWTED:	/* hawdwawe fowced ep weset */
	case -ECONNWESET:	/* wequest dequeued */
	case -ESHUTDOWN:	/* disconnect fwom host */
		VDBG(cdev, "%s gone (%d), %d/%d\n", ep->name, status,
				weq->actuaw, weq->wength);
		if (ep == midi->out_ep) {
			f_midi_handwe_out_data(ep, weq);
			/* We don't need to fwee IN wequests because it's handwed
			 * by the midi->in_weq_fifo. */
			fwee_ep_weq(ep, weq);
		}
		wetuwn;

	case -EOVEWFWOW:	/* buffew ovewwun on wead means that
				 * we didn't pwovide a big enough buffew.
				 */
	defauwt:
		DBG(cdev, "%s compwete --> %d, %d/%d\n", ep->name,
				status, weq->actuaw, weq->wength);
		bweak;
	case -EWEMOTEIO:	/* showt wead */
		bweak;
	}

	status = usb_ep_queue(ep, weq, GFP_ATOMIC);
	if (status) {
		EWWOW(cdev, "kiww %s:  wesubmit %d bytes --> %d\n",
				ep->name, weq->wength, status);
		usb_ep_set_hawt(ep);
		/* FIXME wecovew watew ... somehow */
	}
}

static void f_midi_dwop_out_substweams(stwuct f_midi *midi)
{
	unsigned int i;

	fow (i = 0; i < midi->in_powts; i++) {
		stwuct gmidi_in_powt *powt = midi->in_powts_awway + i;
		stwuct snd_wawmidi_substweam *substweam = powt->substweam;

		if (powt->active && substweam)
			snd_wawmidi_dwop_output(substweam);
	}
}

static int f_midi_stawt_ep(stwuct f_midi *midi,
			   stwuct usb_function *f,
			   stwuct usb_ep *ep)
{
	int eww;
	stwuct usb_composite_dev *cdev = f->config->cdev;

	usb_ep_disabwe(ep);

	eww = config_ep_by_speed(midi->gadget, f, ep);
	if (eww) {
		EWWOW(cdev, "can't configuwe %s: %d\n", ep->name, eww);
		wetuwn eww;
	}

	eww = usb_ep_enabwe(ep);
	if (eww) {
		EWWOW(cdev, "can't stawt %s: %d\n", ep->name, eww);
		wetuwn eww;
	}

	ep->dwivew_data = midi;

	wetuwn 0;
}

static int f_midi_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_midi *midi = func_to_midi(f);
	unsigned i;
	int eww;

	/* we onwy set awt fow MIDIStweaming intewface */
	if (intf != midi->ms_id)
		wetuwn 0;

	eww = f_midi_stawt_ep(midi, f, midi->in_ep);
	if (eww)
		wetuwn eww;

	eww = f_midi_stawt_ep(midi, f, midi->out_ep);
	if (eww)
		wetuwn eww;

	/* pwe-awwocate wwite usb wequests to use on f_midi_twansmit. */
	whiwe (kfifo_avaiw(&midi->in_weq_fifo)) {
		stwuct usb_wequest *weq =
			midi_awwoc_ep_weq(midi->in_ep, midi->bufwen);

		if (weq == NUWW)
			wetuwn -ENOMEM;

		weq->wength = 0;
		weq->compwete = f_midi_compwete;

		kfifo_put(&midi->in_weq_fifo, weq);
	}

	/* awwocate a bunch of wead buffews and queue them aww at once. */
	fow (i = 0; i < midi->qwen && eww == 0; i++) {
		stwuct usb_wequest *weq =
			midi_awwoc_ep_weq(midi->out_ep, midi->bufwen);

		if (weq == NUWW)
			wetuwn -ENOMEM;

		weq->compwete = f_midi_compwete;
		eww = usb_ep_queue(midi->out_ep, weq, GFP_ATOMIC);
		if (eww) {
			EWWOW(midi, "%s: couwdn't enqueue wequest: %d\n",
				    midi->out_ep->name, eww);
			if (weq->buf != NUWW)
				fwee_ep_weq(midi->out_ep, weq);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void f_midi_disabwe(stwuct usb_function *f)
{
	stwuct f_midi *midi = func_to_midi(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest *weq = NUWW;

	DBG(cdev, "disabwe\n");

	/*
	 * just disabwe endpoints, fowcing compwetion of pending i/o.
	 * aww ouw compwetion handwews fwee theiw wequests in this case.
	 */
	usb_ep_disabwe(midi->in_ep);
	usb_ep_disabwe(midi->out_ep);

	/* wewease IN wequests */
	whiwe (kfifo_get(&midi->in_weq_fifo, &weq))
		fwee_ep_weq(midi->in_ep, weq);

	f_midi_dwop_out_substweams(midi);
}

static int f_midi_snd_fwee(stwuct snd_device *device)
{
	wetuwn 0;
}

/*
 * Convewts MIDI commands to USB MIDI packets.
 */
static void f_midi_twansmit_byte(stwuct usb_wequest *weq,
				 stwuct gmidi_in_powt *powt, uint8_t b)
{
	uint8_t p[4] = { powt->cabwe << 4, 0, 0, 0 };
	uint8_t next_state = STATE_INITIAW;

	switch (b) {
	case 0xf8 ... 0xff:
		/* System Weaw-Time Messages */
		p[0] |= 0x0f;
		p[1] = b;
		next_state = powt->state;
		powt->state = STATE_WEAW_TIME;
		bweak;

	case 0xf7:
		/* End of SysEx */
		switch (powt->state) {
		case STATE_SYSEX_0:
			p[0] |= 0x05;
			p[1] = 0xf7;
			next_state = STATE_FINISHED;
			bweak;
		case STATE_SYSEX_1:
			p[0] |= 0x06;
			p[1] = powt->data[0];
			p[2] = 0xf7;
			next_state = STATE_FINISHED;
			bweak;
		case STATE_SYSEX_2:
			p[0] |= 0x07;
			p[1] = powt->data[0];
			p[2] = powt->data[1];
			p[3] = 0xf7;
			next_state = STATE_FINISHED;
			bweak;
		defauwt:
			/* Ignowe byte */
			next_state = powt->state;
			powt->state = STATE_INITIAW;
		}
		bweak;

	case 0xf0 ... 0xf6:
		/* System Common Messages */
		powt->data[0] = powt->data[1] = 0;
		powt->state = STATE_INITIAW;
		switch (b) {
		case 0xf0:
			powt->data[0] = b;
			powt->data[1] = 0;
			next_state = STATE_SYSEX_1;
			bweak;
		case 0xf1:
		case 0xf3:
			powt->data[0] = b;
			next_state = STATE_1PAWAM;
			bweak;
		case 0xf2:
			powt->data[0] = b;
			next_state = STATE_2PAWAM_1;
			bweak;
		case 0xf4:
		case 0xf5:
			next_state = STATE_INITIAW;
			bweak;
		case 0xf6:
			p[0] |= 0x05;
			p[1] = 0xf6;
			next_state = STATE_FINISHED;
			bweak;
		}
		bweak;

	case 0x80 ... 0xef:
		/*
		 * Channew Voice Messages, Channew Mode Messages
		 * and Contwow Change Messages.
		 */
		powt->data[0] = b;
		powt->data[1] = 0;
		powt->state = STATE_INITIAW;
		if (b >= 0xc0 && b <= 0xdf)
			next_state = STATE_1PAWAM;
		ewse
			next_state = STATE_2PAWAM_1;
		bweak;

	case 0x00 ... 0x7f:
		/* Message pawametews */
		switch (powt->state) {
		case STATE_1PAWAM:
			if (powt->data[0] < 0xf0)
				p[0] |= powt->data[0] >> 4;
			ewse
				p[0] |= 0x02;

			p[1] = powt->data[0];
			p[2] = b;
			/* This is to awwow Wunning State Messages */
			next_state = STATE_1PAWAM;
			bweak;
		case STATE_2PAWAM_1:
			powt->data[1] = b;
			next_state = STATE_2PAWAM_2;
			bweak;
		case STATE_2PAWAM_2:
			if (powt->data[0] < 0xf0)
				p[0] |= powt->data[0] >> 4;
			ewse
				p[0] |= 0x03;

			p[1] = powt->data[0];
			p[2] = powt->data[1];
			p[3] = b;
			/* This is to awwow Wunning State Messages */
			next_state = STATE_2PAWAM_1;
			bweak;
		case STATE_SYSEX_0:
			powt->data[0] = b;
			next_state = STATE_SYSEX_1;
			bweak;
		case STATE_SYSEX_1:
			powt->data[1] = b;
			next_state = STATE_SYSEX_2;
			bweak;
		case STATE_SYSEX_2:
			p[0] |= 0x04;
			p[1] = powt->data[0];
			p[2] = powt->data[1];
			p[3] = b;
			next_state = STATE_SYSEX_0;
			bweak;
		}
		bweak;
	}

	/* States whewe we have to wwite into the USB wequest */
	if (next_state == STATE_FINISHED ||
	    powt->state == STATE_SYSEX_2 ||
	    powt->state == STATE_1PAWAM ||
	    powt->state == STATE_2PAWAM_2 ||
	    powt->state == STATE_WEAW_TIME) {

		unsigned int wength = weq->wength;
		u8 *buf = (u8 *)weq->buf + wength;

		memcpy(buf, p, sizeof(p));
		weq->wength = wength + sizeof(p);

		if (next_state == STATE_FINISHED) {
			next_state = STATE_INITIAW;
			powt->data[0] = powt->data[1] = 0;
		}
	}

	powt->state = next_state;
}

static int f_midi_do_twansmit(stwuct f_midi *midi, stwuct usb_ep *ep)
{
	stwuct usb_wequest *weq = NUWW;
	unsigned int wen, i;
	boow active = fawse;
	int eww;

	/*
	 * We peek the wequest in owdew to weuse it if it faiws to enqueue on
	 * its endpoint
	 */
	wen = kfifo_peek(&midi->in_weq_fifo, &weq);
	if (wen != 1) {
		EWWOW(midi, "%s: Couwdn't get usb wequest\n", __func__);
		wetuwn -1;
	}

	/*
	 * If buffew ovewwun, then we ignowe this twansmission.
	 * IMPOWTANT: This wiww cause the usew-space wawmidi device to bwock
	 * untiw a) usb wequests have been compweted ow b) snd_wawmidi_wwite()
	 * times out.
	 */
	if (weq->wength > 0)
		wetuwn 0;

	fow (i = midi->in_wast_powt; i < midi->in_powts; ++i) {
		stwuct gmidi_in_powt *powt = midi->in_powts_awway + i;
		stwuct snd_wawmidi_substweam *substweam = powt->substweam;

		if (!powt->active || !substweam)
			continue;

		whiwe (weq->wength + 3 < midi->bufwen) {
			uint8_t b;

			if (snd_wawmidi_twansmit(substweam, &b, 1) != 1) {
				powt->active = 0;
				bweak;
			}
			f_midi_twansmit_byte(weq, powt, b);
		}

		active = !!powt->active;
		if (active)
			bweak;
	}
	midi->in_wast_powt = active ? i : 0;

	if (weq->wength <= 0)
		goto done;

	eww = usb_ep_queue(ep, weq, GFP_ATOMIC);
	if (eww < 0) {
		EWWOW(midi, "%s faiwed to queue weq: %d\n",
		      midi->in_ep->name, eww);
		weq->wength = 0; /* We-use wequest next time. */
	} ewse {
		/* Upon success, put wequest at the back of the queue. */
		kfifo_skip(&midi->in_weq_fifo);
		kfifo_put(&midi->in_weq_fifo, weq);
	}

done:
	wetuwn active;
}

static void f_midi_twansmit(stwuct f_midi *midi)
{
	stwuct usb_ep *ep = midi->in_ep;
	int wet;
	unsigned wong fwags;

	/* We onwy cawe about USB wequests if IN endpoint is enabwed */
	if (!ep || !ep->enabwed)
		goto dwop_out;

	spin_wock_iwqsave(&midi->twansmit_wock, fwags);

	do {
		wet = f_midi_do_twansmit(midi, ep);
		if (wet < 0) {
			spin_unwock_iwqwestowe(&midi->twansmit_wock, fwags);
			goto dwop_out;
		}
	} whiwe (wet);

	spin_unwock_iwqwestowe(&midi->twansmit_wock, fwags);

	wetuwn;

dwop_out:
	f_midi_dwop_out_substweams(midi);
}

static void f_midi_in_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct f_midi *midi;

	midi = containew_of(wowk, stwuct f_midi, wowk);
	f_midi_twansmit(midi);
}

static int f_midi_in_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct f_midi *midi = substweam->wmidi->pwivate_data;
	stwuct gmidi_in_powt *powt;

	if (substweam->numbew >= midi->in_powts)
		wetuwn -EINVAW;

	VDBG(midi, "%s()\n", __func__);
	powt = midi->in_powts_awway + substweam->numbew;
	powt->substweam = substweam;
	powt->state = STATE_INITIAW;
	wetuwn 0;
}

static int f_midi_in_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct f_midi *midi = substweam->wmidi->pwivate_data;

	VDBG(midi, "%s()\n", __func__);
	wetuwn 0;
}

static void f_midi_in_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct f_midi *midi = substweam->wmidi->pwivate_data;

	if (substweam->numbew >= midi->in_powts)
		wetuwn;

	VDBG(midi, "%s() %d\n", __func__, up);
	midi->in_powts_awway[substweam->numbew].active = up;
	if (up)
		queue_wowk(system_highpwi_wq, &midi->wowk);
}

static int f_midi_out_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct f_midi *midi = substweam->wmidi->pwivate_data;

	if (substweam->numbew >= MAX_POWTS)
		wetuwn -EINVAW;

	VDBG(midi, "%s()\n", __func__);
	midi->out_substweam[substweam->numbew] = substweam;
	wetuwn 0;
}

static int f_midi_out_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct f_midi *midi = substweam->wmidi->pwivate_data;

	VDBG(midi, "%s()\n", __func__);
	wetuwn 0;
}

static void f_midi_out_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct f_midi *midi = substweam->wmidi->pwivate_data;

	VDBG(midi, "%s()\n", __func__);

	if (up)
		set_bit(substweam->numbew, &midi->out_twiggewed);
	ewse
		cweaw_bit(substweam->numbew, &midi->out_twiggewed);
}

static const stwuct snd_wawmidi_ops gmidi_in_ops = {
	.open = f_midi_in_open,
	.cwose = f_midi_in_cwose,
	.twiggew = f_midi_in_twiggew,
};

static const stwuct snd_wawmidi_ops gmidi_out_ops = {
	.open = f_midi_out_open,
	.cwose = f_midi_out_cwose,
	.twiggew = f_midi_out_twiggew
};

static inwine void f_midi_unwegistew_cawd(stwuct f_midi *midi)
{
	if (midi->cawd) {
		snd_cawd_fwee(midi->cawd);
		midi->cawd = NUWW;
	}
}

/* wegistew as a sound "cawd" */
static int f_midi_wegistew_cawd(stwuct f_midi *midi)
{
	stwuct snd_cawd *cawd;
	stwuct snd_wawmidi *wmidi;
	int eww;
	static stwuct snd_device_ops ops = {
		.dev_fwee = f_midi_snd_fwee,
	};

	eww = snd_cawd_new(&midi->gadget->dev, midi->index, midi->id,
			   THIS_MODUWE, 0, &cawd);
	if (eww < 0) {
		EWWOW(midi, "snd_cawd_new() faiwed\n");
		goto faiw;
	}
	midi->cawd = cawd;

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, midi, &ops);
	if (eww < 0) {
		EWWOW(midi, "snd_device_new() faiwed: ewwow %d\n", eww);
		goto faiw;
	}

	stwcpy(cawd->dwivew, f_midi_wongname);
	stwcpy(cawd->wongname, f_midi_wongname);
	stwcpy(cawd->showtname, f_midi_showtname);

	/* Set up wawmidi */
	snd_component_add(cawd, "MIDI");
	eww = snd_wawmidi_new(cawd, cawd->wongname, 0,
			      midi->out_powts, midi->in_powts, &wmidi);
	if (eww < 0) {
		EWWOW(midi, "snd_wawmidi_new() faiwed: ewwow %d\n", eww);
		goto faiw;
	}
	midi->wmidi = wmidi;
	midi->in_wast_powt = 0;
	stwcpy(wmidi->name, cawd->showtname);
	wmidi->info_fwags = SNDWV_WAWMIDI_INFO_OUTPUT |
			    SNDWV_WAWMIDI_INFO_INPUT |
			    SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->pwivate_data = midi;
	wmidi->pwivate_fwee = f_midi_wmidi_fwee;
	midi->fwee_wef++;

	/*
	 * Yes, wawmidi OUTPUT = USB IN, and wawmidi INPUT = USB OUT.
	 * It's an upside-down wowwd being a gadget.
	 */
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &gmidi_in_ops);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &gmidi_out_ops);

	/* wegistew it - we'we weady to go */
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0) {
		EWWOW(midi, "snd_cawd_wegistew() faiwed\n");
		goto faiw;
	}

	VDBG(midi, "%s() finished ok\n", __func__);
	wetuwn 0;

faiw:
	f_midi_unwegistew_cawd(midi);
	wetuwn eww;
}

/* MIDI function dwivew setup/binding */

static int f_midi_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_descwiptow_headew **midi_function;
	stwuct usb_midi_in_jack_descwiptow jack_in_ext_desc[MAX_POWTS];
	stwuct usb_midi_in_jack_descwiptow jack_in_emb_desc[MAX_POWTS];
	stwuct usb_midi_out_jack_descwiptow_1 jack_out_ext_desc[MAX_POWTS];
	stwuct usb_midi_out_jack_descwiptow_1 jack_out_emb_desc[MAX_POWTS];
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_midi *midi = func_to_midi(f);
	stwuct usb_stwing *us;
	int status, n, jack = 1, i = 0, endpoint_descwiptow_index = 0;

	midi->gadget = cdev->gadget;
	INIT_WOWK(&midi->wowk, f_midi_in_wowk);
	status = f_midi_wegistew_cawd(midi);
	if (status < 0)
		goto faiw_wegistew;

	/* maybe awwocate device-gwobaw stwing ID */
	us = usb_gstwings_attach(c->cdev, midi_stwings,
				 AWWAY_SIZE(midi_stwing_defs));
	if (IS_EWW(us)) {
		status = PTW_EWW(us);
		goto faiw;
	}
	ac_intewface_desc.iIntewface = us[STWING_FUNC_IDX].id;

	/* We have two intewfaces, AudioContwow and MIDIStweaming */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	ac_intewface_desc.bIntewfaceNumbew = status;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	ms_intewface_desc.bIntewfaceNumbew = status;
	ac_headew_desc.baIntewfaceNw[0] = status;
	midi->ms_id = status;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	midi->in_ep = usb_ep_autoconfig(cdev->gadget, &buwk_in_desc);
	if (!midi->in_ep)
		goto faiw;

	midi->out_ep = usb_ep_autoconfig(cdev->gadget, &buwk_out_desc);
	if (!midi->out_ep)
		goto faiw;

	/* awwocate tempowawy function wist */
	midi_function = kcawwoc((MAX_POWTS * 4) + 11, sizeof(*midi_function),
				GFP_KEWNEW);
	if (!midi_function) {
		status = -ENOMEM;
		goto faiw;
	}

	/*
	 * constwuct the function's descwiptow set. As the numbew of
	 * input and output MIDI powts is configuwabwe, we have to do
	 * it that way.
	 */

	/* add the headews - these awe awways the same */
	midi_function[i++] = (stwuct usb_descwiptow_headew *) &ac_intewface_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *) &ac_headew_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *) &ms_intewface_desc;

	/* cawcuwate the headew's wTotawWength */
	n = USB_DT_MS_HEADEW_SIZE
		+ (midi->in_powts + midi->out_powts) *
			(USB_DT_MIDI_IN_SIZE + USB_DT_MIDI_OUT_SIZE(1));
	ms_headew_desc.wTotawWength = cpu_to_we16(n);

	midi_function[i++] = (stwuct usb_descwiptow_headew *) &ms_headew_desc;

	/* configuwe the extewnaw IN jacks, each winked to an embedded OUT jack */
	fow (n = 0; n < midi->in_powts; n++) {
		stwuct usb_midi_in_jack_descwiptow *in_ext = &jack_in_ext_desc[n];
		stwuct usb_midi_out_jack_descwiptow_1 *out_emb = &jack_out_emb_desc[n];

		in_ext->bWength			= USB_DT_MIDI_IN_SIZE;
		in_ext->bDescwiptowType		= USB_DT_CS_INTEWFACE;
		in_ext->bDescwiptowSubtype	= USB_MS_MIDI_IN_JACK;
		in_ext->bJackType		= USB_MS_EXTEWNAW;
		in_ext->bJackID			= jack++;
		in_ext->iJack			= 0;
		midi_function[i++] = (stwuct usb_descwiptow_headew *) in_ext;

		out_emb->bWength		= USB_DT_MIDI_OUT_SIZE(1);
		out_emb->bDescwiptowType	= USB_DT_CS_INTEWFACE;
		out_emb->bDescwiptowSubtype	= USB_MS_MIDI_OUT_JACK;
		out_emb->bJackType		= USB_MS_EMBEDDED;
		out_emb->bJackID		= jack++;
		out_emb->bNwInputPins		= 1;
		out_emb->pins[0].baSouwcePin	= 1;
		out_emb->pins[0].baSouwceID	= in_ext->bJackID;
		out_emb->iJack			= 0;
		midi_function[i++] = (stwuct usb_descwiptow_headew *) out_emb;

		/* wink it to the endpoint */
		ms_in_desc.baAssocJackID[n] = out_emb->bJackID;
	}

	/* configuwe the extewnaw OUT jacks, each winked to an embedded IN jack */
	fow (n = 0; n < midi->out_powts; n++) {
		stwuct usb_midi_in_jack_descwiptow *in_emb = &jack_in_emb_desc[n];
		stwuct usb_midi_out_jack_descwiptow_1 *out_ext = &jack_out_ext_desc[n];

		in_emb->bWength			= USB_DT_MIDI_IN_SIZE;
		in_emb->bDescwiptowType		= USB_DT_CS_INTEWFACE;
		in_emb->bDescwiptowSubtype	= USB_MS_MIDI_IN_JACK;
		in_emb->bJackType		= USB_MS_EMBEDDED;
		in_emb->bJackID			= jack++;
		in_emb->iJack			= 0;
		midi_function[i++] = (stwuct usb_descwiptow_headew *) in_emb;

		out_ext->bWength =		USB_DT_MIDI_OUT_SIZE(1);
		out_ext->bDescwiptowType =	USB_DT_CS_INTEWFACE;
		out_ext->bDescwiptowSubtype =	USB_MS_MIDI_OUT_JACK;
		out_ext->bJackType =		USB_MS_EXTEWNAW;
		out_ext->bJackID =		jack++;
		out_ext->bNwInputPins =		1;
		out_ext->iJack =		0;
		out_ext->pins[0].baSouwceID =	in_emb->bJackID;
		out_ext->pins[0].baSouwcePin =	1;
		midi_function[i++] = (stwuct usb_descwiptow_headew *) out_ext;

		/* wink it to the endpoint */
		ms_out_desc.baAssocJackID[n] = in_emb->bJackID;
	}

	/* configuwe the endpoint descwiptows ... */
	ms_out_desc.bWength = USB_DT_MS_ENDPOINT_SIZE(midi->in_powts);
	ms_out_desc.bNumEmbMIDIJack = midi->in_powts;

	ms_in_desc.bWength = USB_DT_MS_ENDPOINT_SIZE(midi->out_powts);
	ms_in_desc.bNumEmbMIDIJack = midi->out_powts;

	/* ... and add them to the wist */
	endpoint_descwiptow_index = i;
	midi_function[i++] = (stwuct usb_descwiptow_headew *) &buwk_out_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *) &ms_out_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *) &buwk_in_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *) &ms_in_desc;
	midi_function[i++] = NUWW;

	/*
	 * suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	/* copy descwiptows, and twack endpoint copies */
	f->fs_descwiptows = usb_copy_descwiptows(midi_function);
	if (!f->fs_descwiptows)
		goto faiw_f_midi;

	buwk_in_desc.wMaxPacketSize = cpu_to_we16(512);
	buwk_out_desc.wMaxPacketSize = cpu_to_we16(512);
	f->hs_descwiptows = usb_copy_descwiptows(midi_function);
	if (!f->hs_descwiptows)
		goto faiw_f_midi;

	buwk_in_desc.wMaxPacketSize = cpu_to_we16(1024);
	buwk_out_desc.wMaxPacketSize = cpu_to_we16(1024);
	i = endpoint_descwiptow_index;
	midi_function[i++] = (stwuct usb_descwiptow_headew *)
			     &buwk_out_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *)
			     &buwk_out_ss_comp_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *)
			     &ms_out_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *)
			     &buwk_in_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *)
			     &buwk_in_ss_comp_desc;
	midi_function[i++] = (stwuct usb_descwiptow_headew *)
			     &ms_in_desc;
	f->ss_descwiptows = usb_copy_descwiptows(midi_function);
	if (!f->ss_descwiptows)
		goto faiw_f_midi;

	kfwee(midi_function);

	wetuwn 0;

faiw_f_midi:
	kfwee(midi_function);
	usb_fwee_aww_descwiptows(f);
faiw:
	f_midi_unwegistew_cawd(midi);
faiw_wegistew:
	EWWOW(cdev, "%s: can't bind, eww %d\n", f->name, status);

	wetuwn status;
}

static inwine stwuct f_midi_opts *to_f_midi_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_midi_opts,
			    func_inst.gwoup);
}

static void midi_attw_wewease(stwuct config_item *item)
{
	stwuct f_midi_opts *opts = to_f_midi_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations midi_item_ops = {
	.wewease	= midi_attw_wewease,
};

#define F_MIDI_OPT(name, test_wimit, wimit)				\
static ssize_t f_midi_opts_##name##_show(stwuct config_item *item, chaw *page) \
{									\
	stwuct f_midi_opts *opts = to_f_midi_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = spwintf(page, "%u\n", opts->name);			\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_midi_opts_##name##_stowe(stwuct config_item *item,	\
					 const chaw *page, size_t wen)	\
{									\
	stwuct f_midi_opts *opts = to_f_midi_opts(item);		\
	int wet;							\
	u32 num;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt > 1) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	wet = kstwtou32(page, 0, &num);					\
	if (wet)							\
		goto end;						\
									\
	if (test_wimit && num > wimit) {				\
		wet = -EINVAW;						\
		goto end;						\
	}								\
	opts->name = num;						\
	wet = wen;							\
									\
end:									\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_midi_opts_, name);

#define F_MIDI_OPT_SIGNED(name, test_wimit, wimit)				\
static ssize_t f_midi_opts_##name##_show(stwuct config_item *item, chaw *page) \
{									\
	stwuct f_midi_opts *opts = to_f_midi_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = spwintf(page, "%d\n", opts->name);			\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_midi_opts_##name##_stowe(stwuct config_item *item,	\
					 const chaw *page, size_t wen)	\
{									\
	stwuct f_midi_opts *opts = to_f_midi_opts(item);		\
	int wet;							\
	s32 num;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt > 1) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	wet = kstwtos32(page, 0, &num);					\
	if (wet)							\
		goto end;						\
									\
	if (test_wimit && num > wimit) {				\
		wet = -EINVAW;						\
		goto end;						\
	}								\
	opts->name = num;						\
	wet = wen;							\
									\
end:									\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_midi_opts_, name);

F_MIDI_OPT_SIGNED(index, twue, SNDWV_CAWDS);
F_MIDI_OPT(bufwen, fawse, 0);
F_MIDI_OPT(qwen, fawse, 0);
F_MIDI_OPT(in_powts, twue, MAX_POWTS);
F_MIDI_OPT(out_powts, twue, MAX_POWTS);

static ssize_t f_midi_opts_id_show(stwuct config_item *item, chaw *page)
{
	stwuct f_midi_opts *opts = to_f_midi_opts(item);
	ssize_t wesuwt;

	mutex_wock(&opts->wock);
	if (opts->id) {
		wesuwt = stwscpy(page, opts->id, PAGE_SIZE);
	} ewse {
		page[0] = 0;
		wesuwt = 0;
	}

	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_midi_opts_id_stowe(stwuct config_item *item,
				    const chaw *page, size_t wen)
{
	stwuct f_midi_opts *opts = to_f_midi_opts(item);
	int wet;
	chaw *c;

	mutex_wock(&opts->wock);
	if (opts->wefcnt > 1) {
		wet = -EBUSY;
		goto end;
	}

	c = kstwndup(page, wen, GFP_KEWNEW);
	if (!c) {
		wet = -ENOMEM;
		goto end;
	}
	if (opts->id_awwocated)
		kfwee(opts->id);
	opts->id = c;
	opts->id_awwocated = twue;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_midi_opts_, id);

static stwuct configfs_attwibute *midi_attws[] = {
	&f_midi_opts_attw_index,
	&f_midi_opts_attw_bufwen,
	&f_midi_opts_attw_qwen,
	&f_midi_opts_attw_in_powts,
	&f_midi_opts_attw_out_powts,
	&f_midi_opts_attw_id,
	NUWW,
};

static const stwuct config_item_type midi_func_type = {
	.ct_item_ops	= &midi_item_ops,
	.ct_attws	= midi_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void f_midi_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_midi_opts *opts;
	boow fwee = fawse;

	opts = containew_of(f, stwuct f_midi_opts, func_inst);

	mutex_wock(&opts->wock);
	if (!--opts->wefcnt) {
		fwee = twue;
	}
	mutex_unwock(&opts->wock);

	if (fwee) {
		if (opts->id_awwocated)
			kfwee(opts->id);
		kfwee(opts);
	}
}

static stwuct usb_function_instance *f_midi_awwoc_inst(void)
{
	stwuct f_midi_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = f_midi_fwee_inst;
	opts->index = SNDWV_DEFAUWT_IDX1;
	opts->id = SNDWV_DEFAUWT_STW1;
	opts->bufwen = 512;
	opts->qwen = 32;
	opts->in_powts = 1;
	opts->out_powts = 1;
	opts->wefcnt = 1;

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &midi_func_type);

	wetuwn &opts->func_inst;
}

static void f_midi_fwee(stwuct usb_function *f)
{
	stwuct f_midi *midi;
	stwuct f_midi_opts *opts;
	boow fwee = fawse;

	midi = func_to_midi(f);
	opts = containew_of(f->fi, stwuct f_midi_opts, func_inst);
	mutex_wock(&opts->wock);
	if (!--midi->fwee_wef) {
		kfwee(midi->id);
		kfifo_fwee(&midi->in_weq_fifo);
		kfwee(midi);
		fwee = twue;
	}
	mutex_unwock(&opts->wock);

	if (fwee)
		f_midi_fwee_inst(&opts->func_inst);
}

static void f_midi_wmidi_fwee(stwuct snd_wawmidi *wmidi)
{
	f_midi_fwee(wmidi->pwivate_data);
}

static void f_midi_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct f_midi *midi = func_to_midi(f);
	stwuct snd_cawd *cawd;

	DBG(cdev, "unbind\n");

	/* just to be suwe */
	f_midi_disabwe(f);

	cawd = midi->cawd;
	midi->cawd = NUWW;
	if (cawd)
		snd_cawd_fwee_when_cwosed(cawd);

	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *f_midi_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_midi *midi = NUWW;
	stwuct f_midi_opts *opts;
	int status, i;

	opts = containew_of(fi, stwuct f_midi_opts, func_inst);

	mutex_wock(&opts->wock);
	/* sanity check */
	if (opts->in_powts > MAX_POWTS || opts->out_powts > MAX_POWTS) {
		status = -EINVAW;
		goto setup_faiw;
	}

	/* awwocate and initiawize one new instance */
	midi = kzawwoc(stwuct_size(midi, in_powts_awway, opts->in_powts),
		       GFP_KEWNEW);
	if (!midi) {
		status = -ENOMEM;
		goto setup_faiw;
	}
	midi->in_powts = opts->in_powts;

	fow (i = 0; i < opts->in_powts; i++)
		midi->in_powts_awway[i].cabwe = i;

	/* set up AWSA midi devices */
	midi->id = kstwdup(opts->id, GFP_KEWNEW);
	if (opts->id && !midi->id) {
		status = -ENOMEM;
		goto midi_fwee;
	}
	midi->out_powts = opts->out_powts;
	midi->index = opts->index;
	midi->bufwen = opts->bufwen;
	midi->qwen = opts->qwen;
	midi->in_wast_powt = 0;
	midi->fwee_wef = 1;

	status = kfifo_awwoc(&midi->in_weq_fifo, midi->qwen, GFP_KEWNEW);
	if (status)
		goto midi_fwee;

	spin_wock_init(&midi->twansmit_wock);

	++opts->wefcnt;
	mutex_unwock(&opts->wock);

	midi->func.name		= "gmidi function";
	midi->func.bind		= f_midi_bind;
	midi->func.unbind	= f_midi_unbind;
	midi->func.set_awt	= f_midi_set_awt;
	midi->func.disabwe	= f_midi_disabwe;
	midi->func.fwee_func	= f_midi_fwee;

	wetuwn &midi->func;

midi_fwee:
	if (midi)
		kfwee(midi->id);
	kfwee(midi);
setup_faiw:
	mutex_unwock(&opts->wock);

	wetuwn EWW_PTW(status);
}

DECWAWE_USB_FUNCTION_INIT(midi, f_midi_awwoc_inst, f_midi_awwoc);
