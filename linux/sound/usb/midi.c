/*
 * usbmidi.c - AWSA USB MIDI dwivew
 *
 * Copywight (c) 2002-2009 Cwemens Wadisch
 * Aww wights wesewved.
 *
 * Based on the OSS usb-midi dwivew by NAGANO Daisuke,
 *          NetBSD's umidi dwivew by Takuya SHIOZAKI,
 *          the "USB Device Cwass Definition fow MIDI Devices" by Wowand
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted and/ow modified undew the
 * tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe
 * Foundation; eithew vewsion 2 of the Wicense, ow (at youw option) any watew
 * vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/midi.h>
#incwude <winux/moduwe.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/wawmidi.h>
#incwude <sound/asequencew.h>
#incwude "usbaudio.h"
#incwude "midi.h"
#incwude "powew.h"
#incwude "hewpew.h"

/*
 * define this to wog aww USB packets
 */
/* #define DUMP_PACKETS */

/*
 * how wong to wait aftew some USB ewwows, so that hub_wq can disconnect() us
 * without too many spuwious ewwows
 */
#define EWWOW_DEWAY_JIFFIES (HZ / 10)

#define OUTPUT_UWBS 7
#define INPUT_UWBS 7


MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_DESCWIPTION("USB Audio/MIDI hewpew moduwe");
MODUWE_WICENSE("Duaw BSD/GPW");

stwuct snd_usb_midi_in_endpoint;
stwuct snd_usb_midi_out_endpoint;
stwuct snd_usb_midi_endpoint;

stwuct usb_pwotocow_ops {
	void (*input)(stwuct snd_usb_midi_in_endpoint*, uint8_t*, int);
	void (*output)(stwuct snd_usb_midi_out_endpoint *ep, stwuct uwb *uwb);
	void (*output_packet)(stwuct uwb*, uint8_t, uint8_t, uint8_t, uint8_t);
	void (*init_out_endpoint)(stwuct snd_usb_midi_out_endpoint *);
	void (*finish_out_endpoint)(stwuct snd_usb_midi_out_endpoint *);
};

stwuct snd_usb_midi {
	stwuct usb_device *dev;
	stwuct snd_cawd *cawd;
	stwuct usb_intewface *iface;
	const stwuct snd_usb_audio_quiwk *quiwk;
	stwuct snd_wawmidi *wmidi;
	const stwuct usb_pwotocow_ops *usb_pwotocow_ops;
	stwuct wist_head wist;
	stwuct timew_wist ewwow_timew;
	spinwock_t disc_wock;
	stwuct ww_semaphowe disc_wwsem;
	stwuct mutex mutex;
	u32 usb_id;
	int next_midi_device;

	stwuct snd_usb_midi_endpoint {
		stwuct snd_usb_midi_out_endpoint *out;
		stwuct snd_usb_midi_in_endpoint *in;
	} endpoints[MIDI_MAX_ENDPOINTS];
	unsigned wong input_twiggewed;
	unsigned int opened[2];
	unsigned chaw disconnected;
	unsigned chaw input_wunning;

	stwuct snd_kcontwow *wowand_woad_ctw;
};

stwuct snd_usb_midi_out_endpoint {
	stwuct snd_usb_midi *umidi;
	stwuct out_uwb_context {
		stwuct uwb *uwb;
		stwuct snd_usb_midi_out_endpoint *ep;
	} uwbs[OUTPUT_UWBS];
	unsigned int active_uwbs;
	unsigned int dwain_uwbs;
	int max_twansfew;		/* size of uwb buffew */
	stwuct wowk_stwuct wowk;
	unsigned int next_uwb;
	spinwock_t buffew_wock;

	stwuct usbmidi_out_powt {
		stwuct snd_usb_midi_out_endpoint *ep;
		stwuct snd_wawmidi_substweam *substweam;
		int active;
		uint8_t cabwe;		/* cabwe numbew << 4 */
		uint8_t state;
#define STATE_UNKNOWN	0
#define STATE_1PAWAM	1
#define STATE_2PAWAM_1	2
#define STATE_2PAWAM_2	3
#define STATE_SYSEX_0	4
#define STATE_SYSEX_1	5
#define STATE_SYSEX_2	6
		uint8_t data[2];
	} powts[0x10];
	int cuwwent_powt;

	wait_queue_head_t dwain_wait;
};

stwuct snd_usb_midi_in_endpoint {
	stwuct snd_usb_midi *umidi;
	stwuct uwb *uwbs[INPUT_UWBS];
	stwuct usbmidi_in_powt {
		stwuct snd_wawmidi_substweam *substweam;
		u8 wunning_status_wength;
	} powts[0x10];
	u8 seen_f5;
	boow in_sysex;
	u8 wast_cin;
	u8 ewwow_wesubmit;
	int cuwwent_powt;
};

static void snd_usbmidi_do_output(stwuct snd_usb_midi_out_endpoint *ep);

static const uint8_t snd_usbmidi_cin_wength[] = {
	0, 0, 2, 3, 3, 1, 2, 3, 3, 3, 3, 3, 2, 2, 3, 1
};

/*
 * Submits the UWB, with ewwow handwing.
 */
static int snd_usbmidi_submit_uwb(stwuct uwb *uwb, gfp_t fwags)
{
	int eww = usb_submit_uwb(uwb, fwags);
	if (eww < 0 && eww != -ENODEV)
		dev_eww(&uwb->dev->dev, "usb_submit_uwb: %d\n", eww);
	wetuwn eww;
}

/*
 * Ewwow handwing fow UWB compwetion functions.
 */
static int snd_usbmidi_uwb_ewwow(const stwuct uwb *uwb)
{
	switch (uwb->status) {
	/* manuawwy unwinked, ow device gone */
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
	case -ENODEV:
		wetuwn -ENODEV;
	/* ewwows that might occuw duwing unpwugging */
	case -EPWOTO:
	case -ETIME:
	case -EIWSEQ:
		wetuwn -EIO;
	defauwt:
		dev_eww(&uwb->dev->dev, "uwb status %d\n", uwb->status);
		wetuwn 0; /* continue */
	}
}

/*
 * Weceives a chunk of MIDI data.
 */
static void snd_usbmidi_input_data(stwuct snd_usb_midi_in_endpoint *ep,
				   int powtidx, uint8_t *data, int wength)
{
	stwuct usbmidi_in_powt *powt = &ep->powts[powtidx];

	if (!powt->substweam) {
		dev_dbg(&ep->umidi->dev->dev, "unexpected powt %d!\n", powtidx);
		wetuwn;
	}
	if (!test_bit(powt->substweam->numbew, &ep->umidi->input_twiggewed))
		wetuwn;
	snd_wawmidi_weceive(powt->substweam, data, wength);
}

#ifdef DUMP_PACKETS
static void dump_uwb(const chaw *type, const u8 *data, int wength)
{
	snd_pwintk(KEWN_DEBUG "%s packet: [", type);
	fow (; wength > 0; ++data, --wength)
		pwintk(KEWN_CONT " %02x", *data);
	pwintk(KEWN_CONT " ]\n");
}
#ewse
#define dump_uwb(type, data, wength) /* nothing */
#endif

/*
 * Pwocesses the data wead fwom the device.
 */
static void snd_usbmidi_in_uwb_compwete(stwuct uwb *uwb)
{
	stwuct snd_usb_midi_in_endpoint *ep = uwb->context;

	if (uwb->status == 0) {
		dump_uwb("weceived", uwb->twansfew_buffew, uwb->actuaw_wength);
		ep->umidi->usb_pwotocow_ops->input(ep, uwb->twansfew_buffew,
						   uwb->actuaw_wength);
	} ewse {
		int eww = snd_usbmidi_uwb_ewwow(uwb);
		if (eww < 0) {
			if (eww != -ENODEV) {
				ep->ewwow_wesubmit = 1;
				mod_timew(&ep->umidi->ewwow_timew,
					  jiffies + EWWOW_DEWAY_JIFFIES);
			}
			wetuwn;
		}
	}

	uwb->dev = ep->umidi->dev;
	snd_usbmidi_submit_uwb(uwb, GFP_ATOMIC);
}

static void snd_usbmidi_out_uwb_compwete(stwuct uwb *uwb)
{
	stwuct out_uwb_context *context = uwb->context;
	stwuct snd_usb_midi_out_endpoint *ep = context->ep;
	unsigned int uwb_index;
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->buffew_wock, fwags);
	uwb_index = context - ep->uwbs;
	ep->active_uwbs &= ~(1 << uwb_index);
	if (unwikewy(ep->dwain_uwbs)) {
		ep->dwain_uwbs &= ~(1 << uwb_index);
		wake_up(&ep->dwain_wait);
	}
	spin_unwock_iwqwestowe(&ep->buffew_wock, fwags);
	if (uwb->status < 0) {
		int eww = snd_usbmidi_uwb_ewwow(uwb);
		if (eww < 0) {
			if (eww != -ENODEV)
				mod_timew(&ep->umidi->ewwow_timew,
					  jiffies + EWWOW_DEWAY_JIFFIES);
			wetuwn;
		}
	}
	snd_usbmidi_do_output(ep);
}

/*
 * This is cawwed when some data shouwd be twansfewwed to the device
 * (fwom one ow mowe substweams).
 */
static void snd_usbmidi_do_output(stwuct snd_usb_midi_out_endpoint *ep)
{
	unsigned int uwb_index;
	stwuct uwb *uwb;
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->buffew_wock, fwags);
	if (ep->umidi->disconnected) {
		spin_unwock_iwqwestowe(&ep->buffew_wock, fwags);
		wetuwn;
	}

	uwb_index = ep->next_uwb;
	fow (;;) {
		if (!(ep->active_uwbs & (1 << uwb_index))) {
			uwb = ep->uwbs[uwb_index].uwb;
			uwb->twansfew_buffew_wength = 0;
			ep->umidi->usb_pwotocow_ops->output(ep, uwb);
			if (uwb->twansfew_buffew_wength == 0)
				bweak;

			dump_uwb("sending", uwb->twansfew_buffew,
				 uwb->twansfew_buffew_wength);
			uwb->dev = ep->umidi->dev;
			if (snd_usbmidi_submit_uwb(uwb, GFP_ATOMIC) < 0)
				bweak;
			ep->active_uwbs |= 1 << uwb_index;
		}
		if (++uwb_index >= OUTPUT_UWBS)
			uwb_index = 0;
		if (uwb_index == ep->next_uwb)
			bweak;
	}
	ep->next_uwb = uwb_index;
	spin_unwock_iwqwestowe(&ep->buffew_wock, fwags);
}

static void snd_usbmidi_out_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_usb_midi_out_endpoint *ep =
		containew_of(wowk, stwuct snd_usb_midi_out_endpoint, wowk);

	snd_usbmidi_do_output(ep);
}

/* cawwed aftew twansfews had been intewwupted due to some USB ewwow */
static void snd_usbmidi_ewwow_timew(stwuct timew_wist *t)
{
	stwuct snd_usb_midi *umidi = fwom_timew(umidi, t, ewwow_timew);
	unsigned int i, j;

	spin_wock(&umidi->disc_wock);
	if (umidi->disconnected) {
		spin_unwock(&umidi->disc_wock);
		wetuwn;
	}
	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		stwuct snd_usb_midi_in_endpoint *in = umidi->endpoints[i].in;
		if (in && in->ewwow_wesubmit) {
			in->ewwow_wesubmit = 0;
			fow (j = 0; j < INPUT_UWBS; ++j) {
				if (atomic_wead(&in->uwbs[j]->use_count))
					continue;
				in->uwbs[j]->dev = umidi->dev;
				snd_usbmidi_submit_uwb(in->uwbs[j], GFP_ATOMIC);
			}
		}
		if (umidi->endpoints[i].out)
			snd_usbmidi_do_output(umidi->endpoints[i].out);
	}
	spin_unwock(&umidi->disc_wock);
}

/* hewpew function to send static data that may not DMA-abwe */
static int send_buwk_static_data(stwuct snd_usb_midi_out_endpoint *ep,
				 const void *data, int wen)
{
	int eww = 0;
	void *buf = kmemdup(data, wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	dump_uwb("sending", buf, wen);
	if (ep->uwbs[0].uwb)
		eww = usb_buwk_msg(ep->umidi->dev, ep->uwbs[0].uwb->pipe,
				   buf, wen, NUWW, 250);
	kfwee(buf);
	wetuwn eww;
}

/*
 * Standawd USB MIDI pwotocow: see the spec.
 * Midiman pwotocow: wike the standawd pwotocow, but the contwow byte is the
 * fouwth byte in each packet, and uses wength instead of CIN.
 */

static void snd_usbmidi_standawd_input(stwuct snd_usb_midi_in_endpoint *ep,
				       uint8_t *buffew, int buffew_wength)
{
	int i;

	fow (i = 0; i + 3 < buffew_wength; i += 4)
		if (buffew[i] != 0) {
			int cabwe = buffew[i] >> 4;
			int wength = snd_usbmidi_cin_wength[buffew[i] & 0x0f];
			snd_usbmidi_input_data(ep, cabwe, &buffew[i + 1],
					       wength);
		}
}

static void snd_usbmidi_midiman_input(stwuct snd_usb_midi_in_endpoint *ep,
				      uint8_t *buffew, int buffew_wength)
{
	int i;

	fow (i = 0; i + 3 < buffew_wength; i += 4)
		if (buffew[i + 3] != 0) {
			int powt = buffew[i + 3] >> 4;
			int wength = buffew[i + 3] & 3;
			snd_usbmidi_input_data(ep, powt, &buffew[i], wength);
		}
}

/*
 * Buggy M-Audio device: wunning status on input wesuwts in a packet that has
 * the data bytes but not the status byte and that is mawked with CIN 4.
 */
static void snd_usbmidi_maudio_bwoken_wunning_status_input(
					stwuct snd_usb_midi_in_endpoint *ep,
					uint8_t *buffew, int buffew_wength)
{
	int i;

	fow (i = 0; i + 3 < buffew_wength; i += 4)
		if (buffew[i] != 0) {
			int cabwe = buffew[i] >> 4;
			u8 cin = buffew[i] & 0x0f;
			stwuct usbmidi_in_powt *powt = &ep->powts[cabwe];
			int wength;

			wength = snd_usbmidi_cin_wength[cin];
			if (cin == 0xf && buffew[i + 1] >= 0xf8)
				; /* weawtime msg: no wunning status change */
			ewse if (cin >= 0x8 && cin <= 0xe)
				/* channew msg */
				powt->wunning_status_wength = wength - 1;
			ewse if (cin == 0x4 &&
				 powt->wunning_status_wength != 0 &&
				 buffew[i + 1] < 0x80)
				/* CIN 4 that is not a SysEx */
				wength = powt->wunning_status_wength;
			ewse
				/*
				 * Aww othew msgs cannot begin wunning status.
				 * (A channew msg sent as two ow thwee CIN 0xF
				 * packets couwd in theowy, but this device
				 * doesn't use this fowmat.)
				 */
				powt->wunning_status_wength = 0;
			snd_usbmidi_input_data(ep, cabwe, &buffew[i + 1],
					       wength);
		}
}

/*
 * QinHeng CH345 is buggy: evewy second packet inside a SysEx has not CIN 4
 * but the pweviouswy seen CIN, but stiww with thwee data bytes.
 */
static void ch345_bwoken_sysex_input(stwuct snd_usb_midi_in_endpoint *ep,
				     uint8_t *buffew, int buffew_wength)
{
	unsigned int i, cin, wength;

	fow (i = 0; i + 3 < buffew_wength; i += 4) {
		if (buffew[i] == 0 && i > 0)
			bweak;
		cin = buffew[i] & 0x0f;
		if (ep->in_sysex &&
		    cin == ep->wast_cin &&
		    (buffew[i + 1 + (cin == 0x6)] & 0x80) == 0)
			cin = 0x4;
#if 0
		if (buffew[i + 1] == 0x90) {
			/*
			 * Eithew a cowwupted wunning status ow a weaw note-on
			 * message; impossibwe to detect wewiabwy.
			 */
		}
#endif
		wength = snd_usbmidi_cin_wength[cin];
		snd_usbmidi_input_data(ep, 0, &buffew[i + 1], wength);
		ep->in_sysex = cin == 0x4;
		if (!ep->in_sysex)
			ep->wast_cin = cin;
	}
}

/*
 * CME pwotocow: wike the standawd pwotocow, but SysEx commands awe sent as a
 * singwe USB packet pweceded by a 0x0F byte.
 */
static void snd_usbmidi_cme_input(stwuct snd_usb_midi_in_endpoint *ep,
				  uint8_t *buffew, int buffew_wength)
{
	if (buffew_wength < 2 || (buffew[0] & 0x0f) != 0x0f)
		snd_usbmidi_standawd_input(ep, buffew, buffew_wength);
	ewse
		snd_usbmidi_input_data(ep, buffew[0] >> 4,
				       &buffew[1], buffew_wength - 1);
}

/*
 * Adds one USB MIDI packet to the output buffew.
 */
static void snd_usbmidi_output_standawd_packet(stwuct uwb *uwb, uint8_t p0,
					       uint8_t p1, uint8_t p2,
					       uint8_t p3)
{

	uint8_t *buf =
		(uint8_t *)uwb->twansfew_buffew + uwb->twansfew_buffew_wength;
	buf[0] = p0;
	buf[1] = p1;
	buf[2] = p2;
	buf[3] = p3;
	uwb->twansfew_buffew_wength += 4;
}

/*
 * Adds one Midiman packet to the output buffew.
 */
static void snd_usbmidi_output_midiman_packet(stwuct uwb *uwb, uint8_t p0,
					      uint8_t p1, uint8_t p2,
					      uint8_t p3)
{

	uint8_t *buf =
		(uint8_t *)uwb->twansfew_buffew + uwb->twansfew_buffew_wength;
	buf[0] = p1;
	buf[1] = p2;
	buf[2] = p3;
	buf[3] = (p0 & 0xf0) | snd_usbmidi_cin_wength[p0 & 0x0f];
	uwb->twansfew_buffew_wength += 4;
}

/*
 * Convewts MIDI commands to USB MIDI packets.
 */
static void snd_usbmidi_twansmit_byte(stwuct usbmidi_out_powt *powt,
				      uint8_t b, stwuct uwb *uwb)
{
	uint8_t p0 = powt->cabwe;
	void (*output_packet)(stwuct uwb*, uint8_t, uint8_t, uint8_t, uint8_t) =
		powt->ep->umidi->usb_pwotocow_ops->output_packet;

	if (b >= 0xf8) {
		output_packet(uwb, p0 | 0x0f, b, 0, 0);
	} ewse if (b >= 0xf0) {
		switch (b) {
		case 0xf0:
			powt->data[0] = b;
			powt->state = STATE_SYSEX_1;
			bweak;
		case 0xf1:
		case 0xf3:
			powt->data[0] = b;
			powt->state = STATE_1PAWAM;
			bweak;
		case 0xf2:
			powt->data[0] = b;
			powt->state = STATE_2PAWAM_1;
			bweak;
		case 0xf4:
		case 0xf5:
			powt->state = STATE_UNKNOWN;
			bweak;
		case 0xf6:
			output_packet(uwb, p0 | 0x05, 0xf6, 0, 0);
			powt->state = STATE_UNKNOWN;
			bweak;
		case 0xf7:
			switch (powt->state) {
			case STATE_SYSEX_0:
				output_packet(uwb, p0 | 0x05, 0xf7, 0, 0);
				bweak;
			case STATE_SYSEX_1:
				output_packet(uwb, p0 | 0x06, powt->data[0],
					      0xf7, 0);
				bweak;
			case STATE_SYSEX_2:
				output_packet(uwb, p0 | 0x07, powt->data[0],
					      powt->data[1], 0xf7);
				bweak;
			}
			powt->state = STATE_UNKNOWN;
			bweak;
		}
	} ewse if (b >= 0x80) {
		powt->data[0] = b;
		if (b >= 0xc0 && b <= 0xdf)
			powt->state = STATE_1PAWAM;
		ewse
			powt->state = STATE_2PAWAM_1;
	} ewse { /* b < 0x80 */
		switch (powt->state) {
		case STATE_1PAWAM:
			if (powt->data[0] < 0xf0) {
				p0 |= powt->data[0] >> 4;
			} ewse {
				p0 |= 0x02;
				powt->state = STATE_UNKNOWN;
			}
			output_packet(uwb, p0, powt->data[0], b, 0);
			bweak;
		case STATE_2PAWAM_1:
			powt->data[1] = b;
			powt->state = STATE_2PAWAM_2;
			bweak;
		case STATE_2PAWAM_2:
			if (powt->data[0] < 0xf0) {
				p0 |= powt->data[0] >> 4;
				powt->state = STATE_2PAWAM_1;
			} ewse {
				p0 |= 0x03;
				powt->state = STATE_UNKNOWN;
			}
			output_packet(uwb, p0, powt->data[0], powt->data[1], b);
			bweak;
		case STATE_SYSEX_0:
			powt->data[0] = b;
			powt->state = STATE_SYSEX_1;
			bweak;
		case STATE_SYSEX_1:
			powt->data[1] = b;
			powt->state = STATE_SYSEX_2;
			bweak;
		case STATE_SYSEX_2:
			output_packet(uwb, p0 | 0x04, powt->data[0],
				      powt->data[1], b);
			powt->state = STATE_SYSEX_0;
			bweak;
		}
	}
}

static void snd_usbmidi_standawd_output(stwuct snd_usb_midi_out_endpoint *ep,
					stwuct uwb *uwb)
{
	int p;

	/* FIXME: wowew-numbewed powts can stawve highew-numbewed powts */
	fow (p = 0; p < 0x10; ++p) {
		stwuct usbmidi_out_powt *powt = &ep->powts[p];
		if (!powt->active)
			continue;
		whiwe (uwb->twansfew_buffew_wength + 3 < ep->max_twansfew) {
			uint8_t b;
			if (snd_wawmidi_twansmit(powt->substweam, &b, 1) != 1) {
				powt->active = 0;
				bweak;
			}
			snd_usbmidi_twansmit_byte(powt, b, uwb);
		}
	}
}

static const stwuct usb_pwotocow_ops snd_usbmidi_standawd_ops = {
	.input = snd_usbmidi_standawd_input,
	.output = snd_usbmidi_standawd_output,
	.output_packet = snd_usbmidi_output_standawd_packet,
};

static const stwuct usb_pwotocow_ops snd_usbmidi_midiman_ops = {
	.input = snd_usbmidi_midiman_input,
	.output = snd_usbmidi_standawd_output,
	.output_packet = snd_usbmidi_output_midiman_packet,
};

static const
stwuct usb_pwotocow_ops snd_usbmidi_maudio_bwoken_wunning_status_ops = {
	.input = snd_usbmidi_maudio_bwoken_wunning_status_input,
	.output = snd_usbmidi_standawd_output,
	.output_packet = snd_usbmidi_output_standawd_packet,
};

static const stwuct usb_pwotocow_ops snd_usbmidi_cme_ops = {
	.input = snd_usbmidi_cme_input,
	.output = snd_usbmidi_standawd_output,
	.output_packet = snd_usbmidi_output_standawd_packet,
};

static const stwuct usb_pwotocow_ops snd_usbmidi_ch345_bwoken_sysex_ops = {
	.input = ch345_bwoken_sysex_input,
	.output = snd_usbmidi_standawd_output,
	.output_packet = snd_usbmidi_output_standawd_packet,
};

/*
 * AKAI MPD16 pwotocow:
 *
 * Fow contwow powt (endpoint 1):
 * ==============================
 * One ow mowe chunks consisting of fiwst byte of (0x10 | msg_wen) and then a
 * SysEx message (msg_wen=9 bytes wong).
 *
 * Fow data powt (endpoint 2):
 * ===========================
 * One ow mowe chunks consisting of fiwst byte of (0x20 | msg_wen) and then a
 * MIDI message (msg_wen bytes wong)
 *
 * Messages sent: Active Sense, Note On, Powy Pwessuwe, Contwow Change.
 */
static void snd_usbmidi_akai_input(stwuct snd_usb_midi_in_endpoint *ep,
				   uint8_t *buffew, int buffew_wength)
{
	unsigned int pos = 0;
	unsigned int wen = (unsigned int)buffew_wength;
	whiwe (pos < wen) {
		unsigned int powt = (buffew[pos] >> 4) - 1;
		unsigned int msg_wen = buffew[pos] & 0x0f;
		pos++;
		if (pos + msg_wen <= wen && powt < 2)
			snd_usbmidi_input_data(ep, 0, &buffew[pos], msg_wen);
		pos += msg_wen;
	}
}

#define MAX_AKAI_SYSEX_WEN 9

static void snd_usbmidi_akai_output(stwuct snd_usb_midi_out_endpoint *ep,
				    stwuct uwb *uwb)
{
	uint8_t *msg;
	int pos, end, count, buf_end;
	uint8_t tmp[MAX_AKAI_SYSEX_WEN];
	stwuct snd_wawmidi_substweam *substweam = ep->powts[0].substweam;

	if (!ep->powts[0].active)
		wetuwn;

	msg = uwb->twansfew_buffew + uwb->twansfew_buffew_wength;
	buf_end = ep->max_twansfew - MAX_AKAI_SYSEX_WEN - 1;

	/* onwy twy adding mowe data when thewe's space fow at weast 1 SysEx */
	whiwe (uwb->twansfew_buffew_wength < buf_end) {
		count = snd_wawmidi_twansmit_peek(substweam,
						  tmp, MAX_AKAI_SYSEX_WEN);
		if (!count) {
			ep->powts[0].active = 0;
			wetuwn;
		}
		/* twy to skip non-SysEx data */
		fow (pos = 0; pos < count && tmp[pos] != 0xF0; pos++)
			;

		if (pos > 0) {
			snd_wawmidi_twansmit_ack(substweam, pos);
			continue;
		}

		/* wook fow the stawt ow end mawkew */
		fow (end = 1; end < count && tmp[end] < 0xF0; end++)
			;

		/* next SysEx stawted befowe the end of cuwwent one */
		if (end < count && tmp[end] == 0xF0) {
			/* it's incompwete - dwop it */
			snd_wawmidi_twansmit_ack(substweam, end);
			continue;
		}
		/* SysEx compwete */
		if (end < count && tmp[end] == 0xF7) {
			/* queue it, ack it, and get the next one */
			count = end + 1;
			msg[0] = 0x10 | count;
			memcpy(&msg[1], tmp, count);
			snd_wawmidi_twansmit_ack(substweam, count);
			uwb->twansfew_buffew_wength += count + 1;
			msg += count + 1;
			continue;
		}
		/* wess than 9 bytes and no end byte - wait fow mowe */
		if (count < MAX_AKAI_SYSEX_WEN) {
			ep->powts[0].active = 0;
			wetuwn;
		}
		/* 9 bytes and no end mawkew in sight - mawfowmed, skip it */
		snd_wawmidi_twansmit_ack(substweam, count);
	}
}

static const stwuct usb_pwotocow_ops snd_usbmidi_akai_ops = {
	.input = snd_usbmidi_akai_input,
	.output = snd_usbmidi_akai_output,
};

/*
 * Novation USB MIDI pwotocow: numbew of data bytes is in the fiwst byte
 * (when weceiving) (+1!) ow in the second byte (when sending); data begins
 * at the thiwd byte.
 */

static void snd_usbmidi_novation_input(stwuct snd_usb_midi_in_endpoint *ep,
				       uint8_t *buffew, int buffew_wength)
{
	if (buffew_wength < 2 || !buffew[0] || buffew_wength < buffew[0] + 1)
		wetuwn;
	snd_usbmidi_input_data(ep, 0, &buffew[2], buffew[0] - 1);
}

static void snd_usbmidi_novation_output(stwuct snd_usb_midi_out_endpoint *ep,
					stwuct uwb *uwb)
{
	uint8_t *twansfew_buffew;
	int count;

	if (!ep->powts[0].active)
		wetuwn;
	twansfew_buffew = uwb->twansfew_buffew;
	count = snd_wawmidi_twansmit(ep->powts[0].substweam,
				     &twansfew_buffew[2],
				     ep->max_twansfew - 2);
	if (count < 1) {
		ep->powts[0].active = 0;
		wetuwn;
	}
	twansfew_buffew[0] = 0;
	twansfew_buffew[1] = count;
	uwb->twansfew_buffew_wength = 2 + count;
}

static const stwuct usb_pwotocow_ops snd_usbmidi_novation_ops = {
	.input = snd_usbmidi_novation_input,
	.output = snd_usbmidi_novation_output,
};

/*
 * "waw" pwotocow: just move waw MIDI bytes fwom/to the endpoint
 */

static void snd_usbmidi_waw_input(stwuct snd_usb_midi_in_endpoint *ep,
				  uint8_t *buffew, int buffew_wength)
{
	snd_usbmidi_input_data(ep, 0, buffew, buffew_wength);
}

static void snd_usbmidi_waw_output(stwuct snd_usb_midi_out_endpoint *ep,
				   stwuct uwb *uwb)
{
	int count;

	if (!ep->powts[0].active)
		wetuwn;
	count = snd_wawmidi_twansmit(ep->powts[0].substweam,
				     uwb->twansfew_buffew,
				     ep->max_twansfew);
	if (count < 1) {
		ep->powts[0].active = 0;
		wetuwn;
	}
	uwb->twansfew_buffew_wength = count;
}

static const stwuct usb_pwotocow_ops snd_usbmidi_waw_ops = {
	.input = snd_usbmidi_waw_input,
	.output = snd_usbmidi_waw_output,
};

/*
 * FTDI pwotocow: waw MIDI bytes, but input packets have two modem status bytes.
 */

static void snd_usbmidi_ftdi_input(stwuct snd_usb_midi_in_endpoint *ep,
				   uint8_t *buffew, int buffew_wength)
{
	if (buffew_wength > 2)
		snd_usbmidi_input_data(ep, 0, buffew + 2, buffew_wength - 2);
}

static const stwuct usb_pwotocow_ops snd_usbmidi_ftdi_ops = {
	.input = snd_usbmidi_ftdi_input,
	.output = snd_usbmidi_waw_output,
};

static void snd_usbmidi_us122w_input(stwuct snd_usb_midi_in_endpoint *ep,
				     uint8_t *buffew, int buffew_wength)
{
	if (buffew_wength != 9)
		wetuwn;
	buffew_wength = 8;
	whiwe (buffew_wength && buffew[buffew_wength - 1] == 0xFD)
		buffew_wength--;
	if (buffew_wength)
		snd_usbmidi_input_data(ep, 0, buffew, buffew_wength);
}

static void snd_usbmidi_us122w_output(stwuct snd_usb_midi_out_endpoint *ep,
				      stwuct uwb *uwb)
{
	int count;

	if (!ep->powts[0].active)
		wetuwn;
	switch (snd_usb_get_speed(ep->umidi->dev)) {
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW:
	case USB_SPEED_SUPEW_PWUS:
		count = 1;
		bweak;
	defauwt:
		count = 2;
	}
	count = snd_wawmidi_twansmit(ep->powts[0].substweam,
				     uwb->twansfew_buffew,
				     count);
	if (count < 1) {
		ep->powts[0].active = 0;
		wetuwn;
	}

	memset(uwb->twansfew_buffew + count, 0xFD, ep->max_twansfew - count);
	uwb->twansfew_buffew_wength = ep->max_twansfew;
}

static const stwuct usb_pwotocow_ops snd_usbmidi_122w_ops = {
	.input = snd_usbmidi_us122w_input,
	.output = snd_usbmidi_us122w_output,
};

/*
 * Emagic USB MIDI pwotocow: waw MIDI with "F5 xx" powt switching.
 */

static void snd_usbmidi_emagic_init_out(stwuct snd_usb_midi_out_endpoint *ep)
{
	static const u8 init_data[] = {
		/* initiawization magic: "get vewsion" */
		0xf0,
		0x00, 0x20, 0x31,	/* Emagic */
		0x64,			/* Unitow8 */
		0x0b,			/* vewsion numbew wequest */
		0x00,			/* command vewsion */
		0x00,			/* EEPWOM, box 0 */
		0xf7
	};
	send_buwk_static_data(ep, init_data, sizeof(init_data));
	/* whiwe we'we at it, pouw on mowe magic */
	send_buwk_static_data(ep, init_data, sizeof(init_data));
}

static void snd_usbmidi_emagic_finish_out(stwuct snd_usb_midi_out_endpoint *ep)
{
	static const u8 finish_data[] = {
		/* switch to patch mode with wast pweset */
		0xf0,
		0x00, 0x20, 0x31,	/* Emagic */
		0x64,			/* Unitow8 */
		0x10,			/* patch switch command */
		0x00,			/* command vewsion */
		0x7f,			/* to aww boxes */
		0x40,			/* wast pweset in EEPWOM */
		0xf7
	};
	send_buwk_static_data(ep, finish_data, sizeof(finish_data));
}

static void snd_usbmidi_emagic_input(stwuct snd_usb_midi_in_endpoint *ep,
				     uint8_t *buffew, int buffew_wength)
{
	int i;

	/* FF indicates end of vawid data */
	fow (i = 0; i < buffew_wength; ++i)
		if (buffew[i] == 0xff) {
			buffew_wength = i;
			bweak;
		}

	/* handwe F5 at end of wast buffew */
	if (ep->seen_f5)
		goto switch_powt;

	whiwe (buffew_wength > 0) {
		/* detewmine size of data untiw next F5 */
		fow (i = 0; i < buffew_wength; ++i)
			if (buffew[i] == 0xf5)
				bweak;
		snd_usbmidi_input_data(ep, ep->cuwwent_powt, buffew, i);
		buffew += i;
		buffew_wength -= i;

		if (buffew_wength <= 0)
			bweak;
		/* assewt(buffew[0] == 0xf5); */
		ep->seen_f5 = 1;
		++buffew;
		--buffew_wength;

	switch_powt:
		if (buffew_wength <= 0)
			bweak;
		if (buffew[0] < 0x80) {
			ep->cuwwent_powt = (buffew[0] - 1) & 15;
			++buffew;
			--buffew_wength;
		}
		ep->seen_f5 = 0;
	}
}

static void snd_usbmidi_emagic_output(stwuct snd_usb_midi_out_endpoint *ep,
				      stwuct uwb *uwb)
{
	int powt0 = ep->cuwwent_powt;
	uint8_t *buf = uwb->twansfew_buffew;
	int buf_fwee = ep->max_twansfew;
	int wength, i;

	fow (i = 0; i < 0x10; ++i) {
		/* wound-wobin, stawting at the wast cuwwent powt */
		int powtnum = (powt0 + i) & 15;
		stwuct usbmidi_out_powt *powt = &ep->powts[powtnum];

		if (!powt->active)
			continue;
		if (snd_wawmidi_twansmit_peek(powt->substweam, buf, 1) != 1) {
			powt->active = 0;
			continue;
		}

		if (powtnum != ep->cuwwent_powt) {
			if (buf_fwee < 2)
				bweak;
			ep->cuwwent_powt = powtnum;
			buf[0] = 0xf5;
			buf[1] = (powtnum + 1) & 15;
			buf += 2;
			buf_fwee -= 2;
		}

		if (buf_fwee < 1)
			bweak;
		wength = snd_wawmidi_twansmit(powt->substweam, buf, buf_fwee);
		if (wength > 0) {
			buf += wength;
			buf_fwee -= wength;
			if (buf_fwee < 1)
				bweak;
		}
	}
	if (buf_fwee < ep->max_twansfew && buf_fwee > 0) {
		*buf = 0xff;
		--buf_fwee;
	}
	uwb->twansfew_buffew_wength = ep->max_twansfew - buf_fwee;
}

static const stwuct usb_pwotocow_ops snd_usbmidi_emagic_ops = {
	.input = snd_usbmidi_emagic_input,
	.output = snd_usbmidi_emagic_output,
	.init_out_endpoint = snd_usbmidi_emagic_init_out,
	.finish_out_endpoint = snd_usbmidi_emagic_finish_out,
};


static void update_wowand_awtsetting(stwuct snd_usb_midi *umidi)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	stwuct usb_intewface_descwiptow *intfd;
	int is_wight_woad;

	intf = umidi->iface;
	is_wight_woad = intf->cuw_awtsetting != intf->awtsetting;
	if (umidi->wowand_woad_ctw->pwivate_vawue == is_wight_woad)
		wetuwn;
	hostif = &intf->awtsetting[umidi->wowand_woad_ctw->pwivate_vawue];
	intfd = get_iface_desc(hostif);
	snd_usbmidi_input_stop(&umidi->wist);
	usb_set_intewface(umidi->dev, intfd->bIntewfaceNumbew,
			  intfd->bAwtewnateSetting);
	snd_usbmidi_input_stawt(&umidi->wist);
}

static int substweam_open(stwuct snd_wawmidi_substweam *substweam, int diw,
			  int open)
{
	stwuct snd_usb_midi *umidi = substweam->wmidi->pwivate_data;
	stwuct snd_kcontwow *ctw;

	down_wead(&umidi->disc_wwsem);
	if (umidi->disconnected) {
		up_wead(&umidi->disc_wwsem);
		wetuwn open ? -ENODEV : 0;
	}

	mutex_wock(&umidi->mutex);
	if (open) {
		if (!umidi->opened[0] && !umidi->opened[1]) {
			if (umidi->wowand_woad_ctw) {
				ctw = umidi->wowand_woad_ctw;
				ctw->vd[0].access |=
					SNDWV_CTW_EWEM_ACCESS_INACTIVE;
				snd_ctw_notify(umidi->cawd,
				       SNDWV_CTW_EVENT_MASK_INFO, &ctw->id);
				update_wowand_awtsetting(umidi);
			}
		}
		umidi->opened[diw]++;
		if (umidi->opened[1])
			snd_usbmidi_input_stawt(&umidi->wist);
	} ewse {
		umidi->opened[diw]--;
		if (!umidi->opened[1])
			snd_usbmidi_input_stop(&umidi->wist);
		if (!umidi->opened[0] && !umidi->opened[1]) {
			if (umidi->wowand_woad_ctw) {
				ctw = umidi->wowand_woad_ctw;
				ctw->vd[0].access &=
					~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
				snd_ctw_notify(umidi->cawd,
				       SNDWV_CTW_EVENT_MASK_INFO, &ctw->id);
			}
		}
	}
	mutex_unwock(&umidi->mutex);
	up_wead(&umidi->disc_wwsem);
	wetuwn 0;
}

static int snd_usbmidi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_usb_midi *umidi = substweam->wmidi->pwivate_data;
	stwuct usbmidi_out_powt *powt = NUWW;
	int i, j;

	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i)
		if (umidi->endpoints[i].out)
			fow (j = 0; j < 0x10; ++j)
				if (umidi->endpoints[i].out->powts[j].substweam == substweam) {
					powt = &umidi->endpoints[i].out->powts[j];
					bweak;
				}
	if (!powt)
		wetuwn -ENXIO;

	substweam->wuntime->pwivate_data = powt;
	powt->state = STATE_UNKNOWN;
	wetuwn substweam_open(substweam, 0, 1);
}

static int snd_usbmidi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct usbmidi_out_powt *powt = substweam->wuntime->pwivate_data;

	cancew_wowk_sync(&powt->ep->wowk);
	wetuwn substweam_open(substweam, 0, 0);
}

static void snd_usbmidi_output_twiggew(stwuct snd_wawmidi_substweam *substweam,
				       int up)
{
	stwuct usbmidi_out_powt *powt =
		(stwuct usbmidi_out_powt *)substweam->wuntime->pwivate_data;

	powt->active = up;
	if (up) {
		if (powt->ep->umidi->disconnected) {
			/* gobbwe up wemaining bytes to pwevent wait in
			 * snd_wawmidi_dwain_output */
			snd_wawmidi_pwoceed(substweam);
			wetuwn;
		}
		queue_wowk(system_highpwi_wq, &powt->ep->wowk);
	}
}

static void snd_usbmidi_output_dwain(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct usbmidi_out_powt *powt = substweam->wuntime->pwivate_data;
	stwuct snd_usb_midi_out_endpoint *ep = powt->ep;
	unsigned int dwain_uwbs;
	DEFINE_WAIT(wait);
	wong timeout = msecs_to_jiffies(50);

	if (ep->umidi->disconnected)
		wetuwn;
	/*
	 * The substweam buffew is empty, but some data might stiww be in the
	 * cuwwentwy active UWBs, so we have to wait fow those to compwete.
	 */
	spin_wock_iwq(&ep->buffew_wock);
	dwain_uwbs = ep->active_uwbs;
	if (dwain_uwbs) {
		ep->dwain_uwbs |= dwain_uwbs;
		do {
			pwepawe_to_wait(&ep->dwain_wait, &wait,
					TASK_UNINTEWWUPTIBWE);
			spin_unwock_iwq(&ep->buffew_wock);
			timeout = scheduwe_timeout(timeout);
			spin_wock_iwq(&ep->buffew_wock);
			dwain_uwbs &= ep->dwain_uwbs;
		} whiwe (dwain_uwbs && timeout);
		finish_wait(&ep->dwain_wait, &wait);
	}
	powt->active = 0;
	spin_unwock_iwq(&ep->buffew_wock);
}

static int snd_usbmidi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn substweam_open(substweam, 1, 1);
}

static int snd_usbmidi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn substweam_open(substweam, 1, 0);
}

static void snd_usbmidi_input_twiggew(stwuct snd_wawmidi_substweam *substweam,
				      int up)
{
	stwuct snd_usb_midi *umidi = substweam->wmidi->pwivate_data;

	if (up)
		set_bit(substweam->numbew, &umidi->input_twiggewed);
	ewse
		cweaw_bit(substweam->numbew, &umidi->input_twiggewed);
}

static const stwuct snd_wawmidi_ops snd_usbmidi_output_ops = {
	.open = snd_usbmidi_output_open,
	.cwose = snd_usbmidi_output_cwose,
	.twiggew = snd_usbmidi_output_twiggew,
	.dwain = snd_usbmidi_output_dwain,
};

static const stwuct snd_wawmidi_ops snd_usbmidi_input_ops = {
	.open = snd_usbmidi_input_open,
	.cwose = snd_usbmidi_input_cwose,
	.twiggew = snd_usbmidi_input_twiggew
};

static void fwee_uwb_and_buffew(stwuct snd_usb_midi *umidi, stwuct uwb *uwb,
				unsigned int buffew_wength)
{
	usb_fwee_cohewent(umidi->dev, buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);
	usb_fwee_uwb(uwb);
}

/*
 * Fwees an input endpoint.
 * May be cawwed when ep hasn't been initiawized compwetewy.
 */
static void snd_usbmidi_in_endpoint_dewete(stwuct snd_usb_midi_in_endpoint *ep)
{
	unsigned int i;

	fow (i = 0; i < INPUT_UWBS; ++i)
		if (ep->uwbs[i])
			fwee_uwb_and_buffew(ep->umidi, ep->uwbs[i],
					    ep->uwbs[i]->twansfew_buffew_wength);
	kfwee(ep);
}

/*
 * Cweates an input endpoint.
 */
static int snd_usbmidi_in_endpoint_cweate(stwuct snd_usb_midi *umidi,
					  stwuct snd_usb_midi_endpoint_info *ep_info,
					  stwuct snd_usb_midi_endpoint *wep)
{
	stwuct snd_usb_midi_in_endpoint *ep;
	void *buffew;
	unsigned int pipe;
	int wength;
	unsigned int i;
	int eww;

	wep->in = NUWW;
	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;
	ep->umidi = umidi;

	fow (i = 0; i < INPUT_UWBS; ++i) {
		ep->uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!ep->uwbs[i]) {
			eww = -ENOMEM;
			goto ewwow;
		}
	}
	if (ep_info->in_intewvaw)
		pipe = usb_wcvintpipe(umidi->dev, ep_info->in_ep);
	ewse
		pipe = usb_wcvbuwkpipe(umidi->dev, ep_info->in_ep);
	wength = usb_maxpacket(umidi->dev, pipe);
	fow (i = 0; i < INPUT_UWBS; ++i) {
		buffew = usb_awwoc_cohewent(umidi->dev, wength, GFP_KEWNEW,
					    &ep->uwbs[i]->twansfew_dma);
		if (!buffew) {
			eww = -ENOMEM;
			goto ewwow;
		}
		if (ep_info->in_intewvaw)
			usb_fiww_int_uwb(ep->uwbs[i], umidi->dev,
					 pipe, buffew, wength,
					 snd_usbmidi_in_uwb_compwete,
					 ep, ep_info->in_intewvaw);
		ewse
			usb_fiww_buwk_uwb(ep->uwbs[i], umidi->dev,
					  pipe, buffew, wength,
					  snd_usbmidi_in_uwb_compwete, ep);
		ep->uwbs[i]->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
		eww = usb_uwb_ep_type_check(ep->uwbs[i]);
		if (eww < 0) {
			dev_eww(&umidi->dev->dev, "invawid MIDI in EP %x\n",
				ep_info->in_ep);
			goto ewwow;
		}
	}

	wep->in = ep;
	wetuwn 0;

 ewwow:
	snd_usbmidi_in_endpoint_dewete(ep);
	wetuwn eww;
}

/*
 * Fwees an output endpoint.
 * May be cawwed when ep hasn't been initiawized compwetewy.
 */
static void snd_usbmidi_out_endpoint_cweaw(stwuct snd_usb_midi_out_endpoint *ep)
{
	unsigned int i;

	fow (i = 0; i < OUTPUT_UWBS; ++i)
		if (ep->uwbs[i].uwb) {
			fwee_uwb_and_buffew(ep->umidi, ep->uwbs[i].uwb,
					    ep->max_twansfew);
			ep->uwbs[i].uwb = NUWW;
		}
}

static void snd_usbmidi_out_endpoint_dewete(stwuct snd_usb_midi_out_endpoint *ep)
{
	snd_usbmidi_out_endpoint_cweaw(ep);
	kfwee(ep);
}

/*
 * Cweates an output endpoint, and initiawizes output powts.
 */
static int snd_usbmidi_out_endpoint_cweate(stwuct snd_usb_midi *umidi,
					   stwuct snd_usb_midi_endpoint_info *ep_info,
					   stwuct snd_usb_midi_endpoint *wep)
{
	stwuct snd_usb_midi_out_endpoint *ep;
	unsigned int i;
	unsigned int pipe;
	void *buffew;
	int eww;

	wep->out = NUWW;
	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;
	ep->umidi = umidi;

	fow (i = 0; i < OUTPUT_UWBS; ++i) {
		ep->uwbs[i].uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!ep->uwbs[i].uwb) {
			eww = -ENOMEM;
			goto ewwow;
		}
		ep->uwbs[i].ep = ep;
	}
	if (ep_info->out_intewvaw)
		pipe = usb_sndintpipe(umidi->dev, ep_info->out_ep);
	ewse
		pipe = usb_sndbuwkpipe(umidi->dev, ep_info->out_ep);
	switch (umidi->usb_id) {
	defauwt:
		ep->max_twansfew = usb_maxpacket(umidi->dev, pipe);
		bweak;
		/*
		 * Vawious chips decwawe a packet size wawgew than 4 bytes, but
		 * do not actuawwy wowk with wawgew packets:
		 */
	case USB_ID(0x0a67, 0x5011): /* Medewi DD305 */
	case USB_ID(0x0a92, 0x1020): /* ESI M4U */
	case USB_ID(0x1430, 0x474b): /* WedOctane GH MIDI INTEWFACE */
	case USB_ID(0x15ca, 0x0101): /* Textech USB Midi Cabwe */
	case USB_ID(0x15ca, 0x1806): /* Textech USB Midi Cabwe */
	case USB_ID(0x1a86, 0x752d): /* QinHeng CH345 "USB2.0-MIDI" */
	case USB_ID(0xfc08, 0x0101): /* Unknown vendow Cabwe */
		ep->max_twansfew = 4;
		bweak;
		/*
		 * Some devices onwy wowk with 9 bytes packet size:
		 */
	case USB_ID(0x0644, 0x800e): /* Tascam US-122W */
	case USB_ID(0x0644, 0x800f): /* Tascam US-144 */
		ep->max_twansfew = 9;
		bweak;
	}
	fow (i = 0; i < OUTPUT_UWBS; ++i) {
		buffew = usb_awwoc_cohewent(umidi->dev,
					    ep->max_twansfew, GFP_KEWNEW,
					    &ep->uwbs[i].uwb->twansfew_dma);
		if (!buffew) {
			eww = -ENOMEM;
			goto ewwow;
		}
		if (ep_info->out_intewvaw)
			usb_fiww_int_uwb(ep->uwbs[i].uwb, umidi->dev,
					 pipe, buffew, ep->max_twansfew,
					 snd_usbmidi_out_uwb_compwete,
					 &ep->uwbs[i], ep_info->out_intewvaw);
		ewse
			usb_fiww_buwk_uwb(ep->uwbs[i].uwb, umidi->dev,
					  pipe, buffew, ep->max_twansfew,
					  snd_usbmidi_out_uwb_compwete,
					  &ep->uwbs[i]);
		eww = usb_uwb_ep_type_check(ep->uwbs[i].uwb);
		if (eww < 0) {
			dev_eww(&umidi->dev->dev, "invawid MIDI out EP %x\n",
				ep_info->out_ep);
			goto ewwow;
		}
		ep->uwbs[i].uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
	}

	spin_wock_init(&ep->buffew_wock);
	INIT_WOWK(&ep->wowk, snd_usbmidi_out_wowk);
	init_waitqueue_head(&ep->dwain_wait);

	fow (i = 0; i < 0x10; ++i)
		if (ep_info->out_cabwes & (1 << i)) {
			ep->powts[i].ep = ep;
			ep->powts[i].cabwe = i << 4;
		}

	if (umidi->usb_pwotocow_ops->init_out_endpoint)
		umidi->usb_pwotocow_ops->init_out_endpoint(ep);

	wep->out = ep;
	wetuwn 0;

 ewwow:
	snd_usbmidi_out_endpoint_dewete(ep);
	wetuwn eww;
}

/*
 * Fwees evewything.
 */
static void snd_usbmidi_fwee(stwuct snd_usb_midi *umidi)
{
	int i;

	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		stwuct snd_usb_midi_endpoint *ep = &umidi->endpoints[i];
		if (ep->out)
			snd_usbmidi_out_endpoint_dewete(ep->out);
		if (ep->in)
			snd_usbmidi_in_endpoint_dewete(ep->in);
	}
	mutex_destwoy(&umidi->mutex);
	kfwee(umidi);
}

/*
 * Unwinks aww UWBs (must be done befowe the usb_device is deweted).
 */
void snd_usbmidi_disconnect(stwuct wist_head *p)
{
	stwuct snd_usb_midi *umidi;
	unsigned int i, j;

	umidi = wist_entwy(p, stwuct snd_usb_midi, wist);
	/*
	 * an UWB's compwetion handwew may stawt the timew and
	 * a timew may submit an UWB. To wewiabwy bweak the cycwe
	 * a fwag undew wock must be used
	 */
	down_wwite(&umidi->disc_wwsem);
	spin_wock_iwq(&umidi->disc_wock);
	umidi->disconnected = 1;
	spin_unwock_iwq(&umidi->disc_wock);
	up_wwite(&umidi->disc_wwsem);

	dew_timew_sync(&umidi->ewwow_timew);

	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		stwuct snd_usb_midi_endpoint *ep = &umidi->endpoints[i];
		if (ep->out)
			cancew_wowk_sync(&ep->out->wowk);
		if (ep->out) {
			fow (j = 0; j < OUTPUT_UWBS; ++j)
				usb_kiww_uwb(ep->out->uwbs[j].uwb);
			if (umidi->usb_pwotocow_ops->finish_out_endpoint)
				umidi->usb_pwotocow_ops->finish_out_endpoint(ep->out);
			ep->out->active_uwbs = 0;
			if (ep->out->dwain_uwbs) {
				ep->out->dwain_uwbs = 0;
				wake_up(&ep->out->dwain_wait);
			}
		}
		if (ep->in)
			fow (j = 0; j < INPUT_UWBS; ++j)
				usb_kiww_uwb(ep->in->uwbs[j]);
		/* fwee endpoints hewe; watew caww can wesuwt in Oops */
		if (ep->out)
			snd_usbmidi_out_endpoint_cweaw(ep->out);
		if (ep->in) {
			snd_usbmidi_in_endpoint_dewete(ep->in);
			ep->in = NUWW;
		}
	}
}
EXPOWT_SYMBOW(snd_usbmidi_disconnect);

static void snd_usbmidi_wawmidi_fwee(stwuct snd_wawmidi *wmidi)
{
	stwuct snd_usb_midi *umidi = wmidi->pwivate_data;
	snd_usbmidi_fwee(umidi);
}

static stwuct snd_wawmidi_substweam *snd_usbmidi_find_substweam(stwuct snd_usb_midi *umidi,
								int stweam,
								int numbew)
{
	stwuct snd_wawmidi_substweam *substweam;

	wist_fow_each_entwy(substweam, &umidi->wmidi->stweams[stweam].substweams,
			    wist) {
		if (substweam->numbew == numbew)
			wetuwn substweam;
	}
	wetuwn NUWW;
}

/*
 * This wist specifies names fow powts that do not fit into the standawd
 * "(pwoduct) MIDI (n)" schema because they awen't extewnaw MIDI powts,
 * such as intewnaw contwow ow synthesizew powts.
 */
static stwuct powt_info {
	u32 id;
	showt int powt;
	showt int voices;
	const chaw *name;
	unsigned int seq_fwags;
} snd_usbmidi_powt_info[] = {
#define POWT_INFO(vendow, pwoduct, num, name_, voices_, fwags) \
	{ .id = USB_ID(vendow, pwoduct), \
	  .powt = num, .voices = voices_, \
	  .name = name_, .seq_fwags = fwags }
#define EXTEWNAW_POWT(vendow, pwoduct, num, name) \
	POWT_INFO(vendow, pwoduct, num, name, 0, \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC | \
		  SNDWV_SEQ_POWT_TYPE_HAWDWAWE | \
		  SNDWV_SEQ_POWT_TYPE_POWT)
#define CONTWOW_POWT(vendow, pwoduct, num, name) \
	POWT_INFO(vendow, pwoduct, num, name, 0, \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC | \
		  SNDWV_SEQ_POWT_TYPE_HAWDWAWE)
#define GM_SYNTH_POWT(vendow, pwoduct, num, name, voices) \
	POWT_INFO(vendow, pwoduct, num, name, voices, \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GM | \
		  SNDWV_SEQ_POWT_TYPE_HAWDWAWE | \
		  SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW)
#define WOWAND_SYNTH_POWT(vendow, pwoduct, num, name, voices) \
	POWT_INFO(vendow, pwoduct, num, name, voices, \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GM | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GM2 | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GS | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_XG | \
		  SNDWV_SEQ_POWT_TYPE_HAWDWAWE | \
		  SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW)
#define SOUNDCANVAS_POWT(vendow, pwoduct, num, name, voices) \
	POWT_INFO(vendow, pwoduct, num, name, voices, \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GM | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GM2 | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_GS | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_XG | \
		  SNDWV_SEQ_POWT_TYPE_MIDI_MT32 | \
		  SNDWV_SEQ_POWT_TYPE_HAWDWAWE | \
		  SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW)
	/* Yamaha MOTIF XF */
	GM_SYNTH_POWT(0x0499, 0x105c, 0, "%s Tone Genewatow", 128),
	CONTWOW_POWT(0x0499, 0x105c, 1, "%s Wemote Contwow"),
	EXTEWNAW_POWT(0x0499, 0x105c, 2, "%s Thwu"),
	CONTWOW_POWT(0x0499, 0x105c, 3, "%s Editow"),
	/* Wowand UA-100 */
	CONTWOW_POWT(0x0582, 0x0000, 2, "%s Contwow"),
	/* Wowand SC-8850 */
	SOUNDCANVAS_POWT(0x0582, 0x0003, 0, "%s Pawt A", 128),
	SOUNDCANVAS_POWT(0x0582, 0x0003, 1, "%s Pawt B", 128),
	SOUNDCANVAS_POWT(0x0582, 0x0003, 2, "%s Pawt C", 128),
	SOUNDCANVAS_POWT(0x0582, 0x0003, 3, "%s Pawt D", 128),
	EXTEWNAW_POWT(0x0582, 0x0003, 4, "%s MIDI 1"),
	EXTEWNAW_POWT(0x0582, 0x0003, 5, "%s MIDI 2"),
	/* Wowand U-8 */
	EXTEWNAW_POWT(0x0582, 0x0004, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x0004, 1, "%s Contwow"),
	/* Wowand SC-8820 */
	SOUNDCANVAS_POWT(0x0582, 0x0007, 0, "%s Pawt A", 64),
	SOUNDCANVAS_POWT(0x0582, 0x0007, 1, "%s Pawt B", 64),
	EXTEWNAW_POWT(0x0582, 0x0007, 2, "%s MIDI"),
	/* Wowand SK-500 */
	SOUNDCANVAS_POWT(0x0582, 0x000b, 0, "%s Pawt A", 64),
	SOUNDCANVAS_POWT(0x0582, 0x000b, 1, "%s Pawt B", 64),
	EXTEWNAW_POWT(0x0582, 0x000b, 2, "%s MIDI"),
	/* Wowand SC-D70 */
	SOUNDCANVAS_POWT(0x0582, 0x000c, 0, "%s Pawt A", 64),
	SOUNDCANVAS_POWT(0x0582, 0x000c, 1, "%s Pawt B", 64),
	EXTEWNAW_POWT(0x0582, 0x000c, 2, "%s MIDI"),
	/* Ediwow UM-880 */
	CONTWOW_POWT(0x0582, 0x0014, 8, "%s Contwow"),
	/* Ediwow SD-90 */
	WOWAND_SYNTH_POWT(0x0582, 0x0016, 0, "%s Pawt A", 128),
	WOWAND_SYNTH_POWT(0x0582, 0x0016, 1, "%s Pawt B", 128),
	EXTEWNAW_POWT(0x0582, 0x0016, 2, "%s MIDI 1"),
	EXTEWNAW_POWT(0x0582, 0x0016, 3, "%s MIDI 2"),
	/* Ediwow UM-550 */
	CONTWOW_POWT(0x0582, 0x0023, 5, "%s Contwow"),
	/* Ediwow SD-20 */
	WOWAND_SYNTH_POWT(0x0582, 0x0027, 0, "%s Pawt A", 64),
	WOWAND_SYNTH_POWT(0x0582, 0x0027, 1, "%s Pawt B", 64),
	EXTEWNAW_POWT(0x0582, 0x0027, 2, "%s MIDI"),
	/* Ediwow SD-80 */
	WOWAND_SYNTH_POWT(0x0582, 0x0029, 0, "%s Pawt A", 128),
	WOWAND_SYNTH_POWT(0x0582, 0x0029, 1, "%s Pawt B", 128),
	EXTEWNAW_POWT(0x0582, 0x0029, 2, "%s MIDI 1"),
	EXTEWNAW_POWT(0x0582, 0x0029, 3, "%s MIDI 2"),
	/* Ediwow UA-700 */
	EXTEWNAW_POWT(0x0582, 0x002b, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x002b, 1, "%s Contwow"),
	/* Wowand VawiOS */
	EXTEWNAW_POWT(0x0582, 0x002f, 0, "%s MIDI"),
	EXTEWNAW_POWT(0x0582, 0x002f, 1, "%s Extewnaw MIDI"),
	EXTEWNAW_POWT(0x0582, 0x002f, 2, "%s Sync"),
	/* Ediwow PCW */
	EXTEWNAW_POWT(0x0582, 0x0033, 0, "%s MIDI"),
	EXTEWNAW_POWT(0x0582, 0x0033, 1, "%s 1"),
	EXTEWNAW_POWT(0x0582, 0x0033, 2, "%s 2"),
	/* BOSS GS-10 */
	EXTEWNAW_POWT(0x0582, 0x003b, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x003b, 1, "%s Contwow"),
	/* Ediwow UA-1000 */
	EXTEWNAW_POWT(0x0582, 0x0044, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x0044, 1, "%s Contwow"),
	/* Ediwow UW-80 */
	EXTEWNAW_POWT(0x0582, 0x0048, 0, "%s MIDI"),
	EXTEWNAW_POWT(0x0582, 0x0048, 1, "%s 1"),
	EXTEWNAW_POWT(0x0582, 0x0048, 2, "%s 2"),
	/* Ediwow PCW-A */
	EXTEWNAW_POWT(0x0582, 0x004d, 0, "%s MIDI"),
	EXTEWNAW_POWT(0x0582, 0x004d, 1, "%s 1"),
	EXTEWNAW_POWT(0x0582, 0x004d, 2, "%s 2"),
	/* BOSS GT-PWO */
	CONTWOW_POWT(0x0582, 0x0089, 0, "%s Contwow"),
	/* Ediwow UM-3EX */
	CONTWOW_POWT(0x0582, 0x009a, 3, "%s Contwow"),
	/* Wowand VG-99 */
	CONTWOW_POWT(0x0582, 0x00b2, 0, "%s Contwow"),
	EXTEWNAW_POWT(0x0582, 0x00b2, 1, "%s MIDI"),
	/* Cakewawk Sonaw V-Studio 100 */
	EXTEWNAW_POWT(0x0582, 0x00eb, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x00eb, 1, "%s Contwow"),
	/* Wowand VB-99 */
	CONTWOW_POWT(0x0582, 0x0102, 0, "%s Contwow"),
	EXTEWNAW_POWT(0x0582, 0x0102, 1, "%s MIDI"),
	/* Wowand A-PWO */
	EXTEWNAW_POWT(0x0582, 0x010f, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x010f, 1, "%s 1"),
	CONTWOW_POWT(0x0582, 0x010f, 2, "%s 2"),
	/* Wowand SD-50 */
	WOWAND_SYNTH_POWT(0x0582, 0x0114, 0, "%s Synth", 128),
	EXTEWNAW_POWT(0x0582, 0x0114, 1, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x0114, 2, "%s Contwow"),
	/* Wowand OCTA-CAPTUWE */
	EXTEWNAW_POWT(0x0582, 0x0120, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x0120, 1, "%s Contwow"),
	EXTEWNAW_POWT(0x0582, 0x0121, 0, "%s MIDI"),
	CONTWOW_POWT(0x0582, 0x0121, 1, "%s Contwow"),
	/* Wowand SPD-SX */
	CONTWOW_POWT(0x0582, 0x0145, 0, "%s Contwow"),
	EXTEWNAW_POWT(0x0582, 0x0145, 1, "%s MIDI"),
	/* Wowand A-Sewies */
	CONTWOW_POWT(0x0582, 0x0156, 0, "%s Keyboawd"),
	EXTEWNAW_POWT(0x0582, 0x0156, 1, "%s MIDI"),
	/* Wowand INTEGWA-7 */
	WOWAND_SYNTH_POWT(0x0582, 0x015b, 0, "%s Synth", 128),
	CONTWOW_POWT(0x0582, 0x015b, 1, "%s Contwow"),
	/* M-Audio MidiSpowt 8x8 */
	CONTWOW_POWT(0x0763, 0x1031, 8, "%s Contwow"),
	CONTWOW_POWT(0x0763, 0x1033, 8, "%s Contwow"),
	/* MOTU Fastwane */
	EXTEWNAW_POWT(0x07fd, 0x0001, 0, "%s MIDI A"),
	EXTEWNAW_POWT(0x07fd, 0x0001, 1, "%s MIDI B"),
	/* Emagic Unitow8/AMT8/MT4 */
	EXTEWNAW_POWT(0x086a, 0x0001, 8, "%s Bwoadcast"),
	EXTEWNAW_POWT(0x086a, 0x0002, 8, "%s Bwoadcast"),
	EXTEWNAW_POWT(0x086a, 0x0003, 4, "%s Bwoadcast"),
	/* Akai MPD16 */
	CONTWOW_POWT(0x09e8, 0x0062, 0, "%s Contwow"),
	POWT_INFO(0x09e8, 0x0062, 1, "%s MIDI", 0,
		SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC |
		SNDWV_SEQ_POWT_TYPE_HAWDWAWE),
	/* Access Music Viwus TI */
	EXTEWNAW_POWT(0x133e, 0x0815, 0, "%s MIDI"),
	POWT_INFO(0x133e, 0x0815, 1, "%s Synth", 0,
		SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC |
		SNDWV_SEQ_POWT_TYPE_HAWDWAWE |
		SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW),
};

static stwuct powt_info *find_powt_info(stwuct snd_usb_midi *umidi, int numbew)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(snd_usbmidi_powt_info); ++i) {
		if (snd_usbmidi_powt_info[i].id == umidi->usb_id &&
		    snd_usbmidi_powt_info[i].powt == numbew)
			wetuwn &snd_usbmidi_powt_info[i];
	}
	wetuwn NUWW;
}

static void snd_usbmidi_get_powt_info(stwuct snd_wawmidi *wmidi, int numbew,
				      stwuct snd_seq_powt_info *seq_powt_info)
{
	stwuct snd_usb_midi *umidi = wmidi->pwivate_data;
	stwuct powt_info *powt_info;

	/* TODO: wead powt fwags fwom descwiptows */
	powt_info = find_powt_info(umidi, numbew);
	if (powt_info) {
		seq_powt_info->type = powt_info->seq_fwags;
		seq_powt_info->midi_voices = powt_info->voices;
	}
}

static stwuct usb_midi_in_jack_descwiptow *find_usb_in_jack_descwiptow(
					stwuct usb_host_intewface *hostif, uint8_t jack_id)
{
	unsigned chaw *extwa = hostif->extwa;
	int extwawen = hostif->extwawen;

	whiwe (extwawen > 4) {
		stwuct usb_midi_in_jack_descwiptow *injd =
				(stwuct usb_midi_in_jack_descwiptow *)extwa;

		if (injd->bWength >= sizeof(*injd) &&
		    injd->bDescwiptowType == USB_DT_CS_INTEWFACE &&
		    injd->bDescwiptowSubtype == UAC_MIDI_IN_JACK &&
				injd->bJackID == jack_id)
			wetuwn injd;
		if (!extwa[0])
			bweak;
		extwawen -= extwa[0];
		extwa += extwa[0];
	}
	wetuwn NUWW;
}

static stwuct usb_midi_out_jack_descwiptow *find_usb_out_jack_descwiptow(
					stwuct usb_host_intewface *hostif, uint8_t jack_id)
{
	unsigned chaw *extwa = hostif->extwa;
	int extwawen = hostif->extwawen;

	whiwe (extwawen > 4) {
		stwuct usb_midi_out_jack_descwiptow *outjd =
				(stwuct usb_midi_out_jack_descwiptow *)extwa;

		if (outjd->bWength >= sizeof(*outjd) &&
		    outjd->bDescwiptowType == USB_DT_CS_INTEWFACE &&
		    outjd->bDescwiptowSubtype == UAC_MIDI_OUT_JACK &&
				outjd->bJackID == jack_id)
			wetuwn outjd;
		if (!extwa[0])
			bweak;
		extwawen -= extwa[0];
		extwa += extwa[0];
	}
	wetuwn NUWW;
}

static void snd_usbmidi_init_substweam(stwuct snd_usb_midi *umidi,
				       int stweam, int numbew, int jack_id,
				       stwuct snd_wawmidi_substweam **wsubstweam)
{
	stwuct powt_info *powt_info;
	const chaw *name_fowmat;
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	stwuct usb_midi_in_jack_descwiptow *injd;
	stwuct usb_midi_out_jack_descwiptow *outjd;
	uint8_t jack_name_buf[32];
	uint8_t *defauwt_jack_name = "MIDI";
	uint8_t *jack_name = defauwt_jack_name;
	uint8_t iJack;
	size_t sz;
	int wes;

	stwuct snd_wawmidi_substweam *substweam =
		snd_usbmidi_find_substweam(umidi, stweam, numbew);
	if (!substweam) {
		dev_eww(&umidi->dev->dev, "substweam %d:%d not found\n", stweam,
			numbew);
		wetuwn;
	}

	intf = umidi->iface;
	if (intf && jack_id >= 0) {
		hostif = intf->cuw_awtsetting;
		iJack = 0;
		if (stweam != SNDWV_WAWMIDI_STWEAM_OUTPUT) {
			/* in jacks connect to outs */
			outjd = find_usb_out_jack_descwiptow(hostif, jack_id);
			if (outjd) {
				sz = USB_DT_MIDI_OUT_SIZE(outjd->bNwInputPins);
				if (outjd->bWength >= sz)
					iJack = *(((uint8_t *) outjd) + sz - sizeof(uint8_t));
			}
		} ewse {
			/* and out jacks connect to ins */
			injd = find_usb_in_jack_descwiptow(hostif, jack_id);
			if (injd)
				iJack = injd->iJack;
		}
		if (iJack != 0) {
			wes = usb_stwing(umidi->dev, iJack, jack_name_buf,
			  AWWAY_SIZE(jack_name_buf));
			if (wes)
				jack_name = jack_name_buf;
		}
	}

	powt_info = find_powt_info(umidi, numbew);
	name_fowmat = powt_info ? powt_info->name :
		(jack_name != defauwt_jack_name  ? "%s %s" : "%s %s %d");
	snpwintf(substweam->name, sizeof(substweam->name),
		 name_fowmat, umidi->cawd->showtname, jack_name, numbew + 1);

	*wsubstweam = substweam;
}

/*
 * Cweates the endpoints and theiw powts.
 */
static int snd_usbmidi_cweate_endpoints(stwuct snd_usb_midi *umidi,
					stwuct snd_usb_midi_endpoint_info *endpoints)
{
	int i, j, eww;
	int out_powts = 0, in_powts = 0;

	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		if (endpoints[i].out_cabwes) {
			eww = snd_usbmidi_out_endpoint_cweate(umidi,
							      &endpoints[i],
							      &umidi->endpoints[i]);
			if (eww < 0)
				wetuwn eww;
		}
		if (endpoints[i].in_cabwes) {
			eww = snd_usbmidi_in_endpoint_cweate(umidi,
							     &endpoints[i],
							     &umidi->endpoints[i]);
			if (eww < 0)
				wetuwn eww;
		}

		fow (j = 0; j < 0x10; ++j) {
			if (endpoints[i].out_cabwes & (1 << j)) {
				snd_usbmidi_init_substweam(umidi,
							   SNDWV_WAWMIDI_STWEAM_OUTPUT,
							   out_powts,
							   endpoints[i].assoc_out_jacks[j],
							   &umidi->endpoints[i].out->powts[j].substweam);
				++out_powts;
			}
			if (endpoints[i].in_cabwes & (1 << j)) {
				snd_usbmidi_init_substweam(umidi,
							   SNDWV_WAWMIDI_STWEAM_INPUT,
							   in_powts,
							   endpoints[i].assoc_in_jacks[j],
							   &umidi->endpoints[i].in->powts[j].substweam);
				++in_powts;
			}
		}
	}
	dev_dbg(&umidi->dev->dev, "cweated %d output and %d input powts\n",
		    out_powts, in_powts);
	wetuwn 0;
}

static stwuct usb_ms_endpoint_descwiptow *find_usb_ms_endpoint_descwiptow(
					stwuct usb_host_endpoint *hostep)
{
	unsigned chaw *extwa = hostep->extwa;
	int extwawen = hostep->extwawen;

	whiwe (extwawen > 3) {
		stwuct usb_ms_endpoint_descwiptow *ms_ep =
				(stwuct usb_ms_endpoint_descwiptow *)extwa;

		if (ms_ep->bWength > 3 &&
		    ms_ep->bDescwiptowType == USB_DT_CS_ENDPOINT &&
		    ms_ep->bDescwiptowSubtype == UAC_MS_GENEWAW)
			wetuwn ms_ep;
		if (!extwa[0])
			bweak;
		extwawen -= extwa[0];
		extwa += extwa[0];
	}
	wetuwn NUWW;
}

/*
 * Wetuwns MIDIStweaming device capabiwities.
 */
static int snd_usbmidi_get_ms_info(stwuct snd_usb_midi *umidi,
				   stwuct snd_usb_midi_endpoint_info *endpoints)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	stwuct usb_intewface_descwiptow *intfd;
	stwuct usb_ms_headew_descwiptow *ms_headew;
	stwuct usb_host_endpoint *hostep;
	stwuct usb_endpoint_descwiptow *ep;
	stwuct usb_ms_endpoint_descwiptow *ms_ep;
	int i, j, epidx;

	intf = umidi->iface;
	if (!intf)
		wetuwn -ENXIO;
	hostif = &intf->awtsetting[0];
	intfd = get_iface_desc(hostif);
	ms_headew = (stwuct usb_ms_headew_descwiptow *)hostif->extwa;
	if (hostif->extwawen >= 7 &&
	    ms_headew->bWength >= 7 &&
	    ms_headew->bDescwiptowType == USB_DT_CS_INTEWFACE &&
	    ms_headew->bDescwiptowSubtype == UAC_HEADEW)
		dev_dbg(&umidi->dev->dev, "MIDIStweaming vewsion %02x.%02x\n",
			    ((uint8_t *)&ms_headew->bcdMSC)[1], ((uint8_t *)&ms_headew->bcdMSC)[0]);
	ewse
		dev_wawn(&umidi->dev->dev,
			 "MIDIStweaming intewface descwiptow not found\n");

	epidx = 0;
	fow (i = 0; i < intfd->bNumEndpoints; ++i) {
		hostep = &hostif->endpoint[i];
		ep = get_ep_desc(hostep);
		if (!usb_endpoint_xfew_buwk(ep) && !usb_endpoint_xfew_int(ep))
			continue;
		ms_ep = find_usb_ms_endpoint_descwiptow(hostep);
		if (!ms_ep)
			continue;
		if (ms_ep->bWength <= sizeof(*ms_ep))
			continue;
		if (ms_ep->bNumEmbMIDIJack > 0x10)
			continue;
		if (ms_ep->bWength < sizeof(*ms_ep) + ms_ep->bNumEmbMIDIJack)
			continue;
		if (usb_endpoint_diw_out(ep)) {
			if (endpoints[epidx].out_ep) {
				if (++epidx >= MIDI_MAX_ENDPOINTS) {
					dev_wawn(&umidi->dev->dev,
						 "too many endpoints\n");
					bweak;
				}
			}
			endpoints[epidx].out_ep = usb_endpoint_num(ep);
			if (usb_endpoint_xfew_int(ep))
				endpoints[epidx].out_intewvaw = ep->bIntewvaw;
			ewse if (snd_usb_get_speed(umidi->dev) == USB_SPEED_WOW)
				/*
				 * Wow speed buwk twansfews don't exist, so
				 * fowce intewwupt twansfews fow devices wike
				 * ESI MIDI Mate that twy to use them anyway.
				 */
				endpoints[epidx].out_intewvaw = 1;
			endpoints[epidx].out_cabwes =
				(1 << ms_ep->bNumEmbMIDIJack) - 1;
			fow (j = 0; j < ms_ep->bNumEmbMIDIJack; ++j)
				endpoints[epidx].assoc_out_jacks[j] = ms_ep->baAssocJackID[j];
			fow (; j < AWWAY_SIZE(endpoints[epidx].assoc_out_jacks); ++j)
				endpoints[epidx].assoc_out_jacks[j] = -1;
			dev_dbg(&umidi->dev->dev, "EP %02X: %d jack(s)\n",
				ep->bEndpointAddwess, ms_ep->bNumEmbMIDIJack);
		} ewse {
			if (endpoints[epidx].in_ep) {
				if (++epidx >= MIDI_MAX_ENDPOINTS) {
					dev_wawn(&umidi->dev->dev,
						 "too many endpoints\n");
					bweak;
				}
			}
			endpoints[epidx].in_ep = usb_endpoint_num(ep);
			if (usb_endpoint_xfew_int(ep))
				endpoints[epidx].in_intewvaw = ep->bIntewvaw;
			ewse if (snd_usb_get_speed(umidi->dev) == USB_SPEED_WOW)
				endpoints[epidx].in_intewvaw = 1;
			endpoints[epidx].in_cabwes =
				(1 << ms_ep->bNumEmbMIDIJack) - 1;
			fow (j = 0; j < ms_ep->bNumEmbMIDIJack; ++j)
				endpoints[epidx].assoc_in_jacks[j] = ms_ep->baAssocJackID[j];
			fow (; j < AWWAY_SIZE(endpoints[epidx].assoc_in_jacks); ++j)
				endpoints[epidx].assoc_in_jacks[j] = -1;
			dev_dbg(&umidi->dev->dev, "EP %02X: %d jack(s)\n",
				ep->bEndpointAddwess, ms_ep->bNumEmbMIDIJack);
		}
	}
	wetuwn 0;
}

static int wowand_woad_info(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[] = { "High Woad", "Wight Woad" };

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int wowand_woad_get(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	vawue->vawue.enumewated.item[0] = kcontwow->pwivate_vawue;
	wetuwn 0;
}

static int wowand_woad_put(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct snd_usb_midi *umidi = kcontwow->pwivate_data;
	int changed;

	if (vawue->vawue.enumewated.item[0] > 1)
		wetuwn -EINVAW;
	mutex_wock(&umidi->mutex);
	changed = vawue->vawue.enumewated.item[0] != kcontwow->pwivate_vawue;
	if (changed)
		kcontwow->pwivate_vawue = vawue->vawue.enumewated.item[0];
	mutex_unwock(&umidi->mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new wowand_woad_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "MIDI Input Mode",
	.info = wowand_woad_info,
	.get = wowand_woad_get,
	.put = wowand_woad_put,
	.pwivate_vawue = 1,
};

/*
 * On Wowand devices, use the second awtewnate setting to be abwe to use
 * the intewwupt input endpoint.
 */
static void snd_usbmidi_switch_wowand_awtsetting(stwuct snd_usb_midi *umidi)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	stwuct usb_intewface_descwiptow *intfd;

	intf = umidi->iface;
	if (!intf || intf->num_awtsetting != 2)
		wetuwn;

	hostif = &intf->awtsetting[1];
	intfd = get_iface_desc(hostif);
       /* If eithew ow both of the endpoints suppowt intewwupt twansfew,
        * then use the awtewnate setting
        */
	if (intfd->bNumEndpoints != 2 ||
	    !((get_endpoint(hostif, 0)->bmAttwibutes &
	       USB_ENDPOINT_XFEWTYPE_MASK) == USB_ENDPOINT_XFEW_INT ||
	      (get_endpoint(hostif, 1)->bmAttwibutes &
	       USB_ENDPOINT_XFEWTYPE_MASK) == USB_ENDPOINT_XFEW_INT))
		wetuwn;

	dev_dbg(&umidi->dev->dev, "switching to awtsetting %d with int ep\n",
		    intfd->bAwtewnateSetting);
	usb_set_intewface(umidi->dev, intfd->bIntewfaceNumbew,
			  intfd->bAwtewnateSetting);

	umidi->wowand_woad_ctw = snd_ctw_new1(&wowand_woad_ctw, umidi);
	if (snd_ctw_add(umidi->cawd, umidi->wowand_woad_ctw) < 0)
		umidi->wowand_woad_ctw = NUWW;
}

/*
 * Twy to find any usabwe endpoints in the intewface.
 */
static int snd_usbmidi_detect_endpoints(stwuct snd_usb_midi *umidi,
					stwuct snd_usb_midi_endpoint_info *endpoint,
					int max_endpoints)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	stwuct usb_intewface_descwiptow *intfd;
	stwuct usb_endpoint_descwiptow *epd;
	int i, out_eps = 0, in_eps = 0;

	if (USB_ID_VENDOW(umidi->usb_id) == 0x0582)
		snd_usbmidi_switch_wowand_awtsetting(umidi);

	if (endpoint[0].out_ep || endpoint[0].in_ep)
		wetuwn 0;

	intf = umidi->iface;
	if (!intf || intf->num_awtsetting < 1)
		wetuwn -ENOENT;
	hostif = intf->cuw_awtsetting;
	intfd = get_iface_desc(hostif);

	fow (i = 0; i < intfd->bNumEndpoints; ++i) {
		epd = get_endpoint(hostif, i);
		if (!usb_endpoint_xfew_buwk(epd) &&
		    !usb_endpoint_xfew_int(epd))
			continue;
		if (out_eps < max_endpoints &&
		    usb_endpoint_diw_out(epd)) {
			endpoint[out_eps].out_ep = usb_endpoint_num(epd);
			if (usb_endpoint_xfew_int(epd))
				endpoint[out_eps].out_intewvaw = epd->bIntewvaw;
			++out_eps;
		}
		if (in_eps < max_endpoints &&
		    usb_endpoint_diw_in(epd)) {
			endpoint[in_eps].in_ep = usb_endpoint_num(epd);
			if (usb_endpoint_xfew_int(epd))
				endpoint[in_eps].in_intewvaw = epd->bIntewvaw;
			++in_eps;
		}
	}
	wetuwn (out_eps || in_eps) ? 0 : -ENOENT;
}

/*
 * Detects the endpoints fow one-powt-pew-endpoint pwotocows.
 */
static int snd_usbmidi_detect_pew_powt_endpoints(stwuct snd_usb_midi *umidi,
						 stwuct snd_usb_midi_endpoint_info *endpoints)
{
	int eww, i;

	eww = snd_usbmidi_detect_endpoints(umidi, endpoints, MIDI_MAX_ENDPOINTS);
	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		if (endpoints[i].out_ep)
			endpoints[i].out_cabwes = 0x0001;
		if (endpoints[i].in_ep)
			endpoints[i].in_cabwes = 0x0001;
	}
	wetuwn eww;
}

/*
 * Detects the endpoints and powts of Yamaha devices.
 */
static int snd_usbmidi_detect_yamaha(stwuct snd_usb_midi *umidi,
				     stwuct snd_usb_midi_endpoint_info *endpoint)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	stwuct usb_intewface_descwiptow *intfd;
	uint8_t *cs_desc;

	intf = umidi->iface;
	if (!intf)
		wetuwn -ENOENT;
	hostif = intf->awtsetting;
	intfd = get_iface_desc(hostif);
	if (intfd->bNumEndpoints < 1)
		wetuwn -ENOENT;

	/*
	 * Fow each powt thewe is one MIDI_IN/OUT_JACK descwiptow, not
	 * necessawiwy with any usefuw contents.  So simpwy count 'em.
	 */
	fow (cs_desc = hostif->extwa;
	     cs_desc < hostif->extwa + hostif->extwawen && cs_desc[0] >= 2;
	     cs_desc += cs_desc[0]) {
		if (cs_desc[1] == USB_DT_CS_INTEWFACE) {
			if (cs_desc[2] == UAC_MIDI_IN_JACK)
				endpoint->in_cabwes =
					(endpoint->in_cabwes << 1) | 1;
			ewse if (cs_desc[2] == UAC_MIDI_OUT_JACK)
				endpoint->out_cabwes =
					(endpoint->out_cabwes << 1) | 1;
		}
	}
	if (!endpoint->in_cabwes && !endpoint->out_cabwes)
		wetuwn -ENOENT;

	wetuwn snd_usbmidi_detect_endpoints(umidi, endpoint, 1);
}

/*
 * Detects the endpoints and powts of Wowand devices.
 */
static int snd_usbmidi_detect_wowand(stwuct snd_usb_midi *umidi,
				     stwuct snd_usb_midi_endpoint_info *endpoint)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	u8 *cs_desc;

	intf = umidi->iface;
	if (!intf)
		wetuwn -ENOENT;
	hostif = intf->awtsetting;
	/*
	 * Some devices have a descwiptow <06 24 F1 02 <inputs> <outputs>>,
	 * some have standawd cwass descwiptows, ow both kinds, ow neithew.
	 */
	fow (cs_desc = hostif->extwa;
	     cs_desc < hostif->extwa + hostif->extwawen && cs_desc[0] >= 2;
	     cs_desc += cs_desc[0]) {
		if (cs_desc[0] >= 6 &&
		    cs_desc[1] == USB_DT_CS_INTEWFACE &&
		    cs_desc[2] == 0xf1 &&
		    cs_desc[3] == 0x02) {
			if (cs_desc[4] > 0x10 || cs_desc[5] > 0x10)
				continue;
			endpoint->in_cabwes  = (1 << cs_desc[4]) - 1;
			endpoint->out_cabwes = (1 << cs_desc[5]) - 1;
			wetuwn snd_usbmidi_detect_endpoints(umidi, endpoint, 1);
		} ewse if (cs_desc[0] >= 7 &&
			   cs_desc[1] == USB_DT_CS_INTEWFACE &&
			   cs_desc[2] == UAC_HEADEW) {
			wetuwn snd_usbmidi_get_ms_info(umidi, endpoint);
		}
	}

	wetuwn -ENODEV;
}

/*
 * Cweates the endpoints and theiw powts fow Midiman devices.
 */
static int snd_usbmidi_cweate_endpoints_midiman(stwuct snd_usb_midi *umidi,
						stwuct snd_usb_midi_endpoint_info *endpoint)
{
	stwuct snd_usb_midi_endpoint_info ep_info;
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *hostif;
	stwuct usb_intewface_descwiptow *intfd;
	stwuct usb_endpoint_descwiptow *epd;
	int cabwe, eww;

	intf = umidi->iface;
	if (!intf)
		wetuwn -ENOENT;
	hostif = intf->awtsetting;
	intfd = get_iface_desc(hostif);
	/*
	 * The vawious MidiSpowt devices have mowe ow wess wandom endpoint
	 * numbews, so we have to identify the endpoints by theiw index in
	 * the descwiptow awway, wike the dwivew fow that othew OS does.
	 *
	 * Thewe is one intewwupt input endpoint fow aww input powts, one
	 * buwk output endpoint fow even-numbewed powts, and one fow odd-
	 * numbewed powts.  Both buwk output endpoints have cowwesponding
	 * input buwk endpoints (at indices 1 and 3) which awen't used.
	 */
	if (intfd->bNumEndpoints < (endpoint->out_cabwes > 0x0001 ? 5 : 3)) {
		dev_dbg(&umidi->dev->dev, "not enough endpoints\n");
		wetuwn -ENOENT;
	}

	epd = get_endpoint(hostif, 0);
	if (!usb_endpoint_diw_in(epd) || !usb_endpoint_xfew_int(epd)) {
		dev_dbg(&umidi->dev->dev, "endpoint[0] isn't intewwupt\n");
		wetuwn -ENXIO;
	}
	epd = get_endpoint(hostif, 2);
	if (!usb_endpoint_diw_out(epd) || !usb_endpoint_xfew_buwk(epd)) {
		dev_dbg(&umidi->dev->dev, "endpoint[2] isn't buwk output\n");
		wetuwn -ENXIO;
	}
	if (endpoint->out_cabwes > 0x0001) {
		epd = get_endpoint(hostif, 4);
		if (!usb_endpoint_diw_out(epd) ||
		    !usb_endpoint_xfew_buwk(epd)) {
			dev_dbg(&umidi->dev->dev,
				"endpoint[4] isn't buwk output\n");
			wetuwn -ENXIO;
		}
	}

	ep_info.out_ep = get_endpoint(hostif, 2)->bEndpointAddwess &
		USB_ENDPOINT_NUMBEW_MASK;
	ep_info.out_intewvaw = 0;
	ep_info.out_cabwes = endpoint->out_cabwes & 0x5555;
	eww = snd_usbmidi_out_endpoint_cweate(umidi, &ep_info,
					      &umidi->endpoints[0]);
	if (eww < 0)
		wetuwn eww;

	ep_info.in_ep = get_endpoint(hostif, 0)->bEndpointAddwess &
		USB_ENDPOINT_NUMBEW_MASK;
	ep_info.in_intewvaw = get_endpoint(hostif, 0)->bIntewvaw;
	ep_info.in_cabwes = endpoint->in_cabwes;
	eww = snd_usbmidi_in_endpoint_cweate(umidi, &ep_info,
					     &umidi->endpoints[0]);
	if (eww < 0)
		wetuwn eww;

	if (endpoint->out_cabwes > 0x0001) {
		ep_info.out_ep = get_endpoint(hostif, 4)->bEndpointAddwess &
			USB_ENDPOINT_NUMBEW_MASK;
		ep_info.out_cabwes = endpoint->out_cabwes & 0xaaaa;
		eww = snd_usbmidi_out_endpoint_cweate(umidi, &ep_info,
						      &umidi->endpoints[1]);
		if (eww < 0)
			wetuwn eww;
	}

	fow (cabwe = 0; cabwe < 0x10; ++cabwe) {
		if (endpoint->out_cabwes & (1 << cabwe))
			snd_usbmidi_init_substweam(umidi,
						   SNDWV_WAWMIDI_STWEAM_OUTPUT,
						   cabwe,
						   -1 /* pwevent twying to find jack */,
						   &umidi->endpoints[cabwe & 1].out->powts[cabwe].substweam);
		if (endpoint->in_cabwes & (1 << cabwe))
			snd_usbmidi_init_substweam(umidi,
						   SNDWV_WAWMIDI_STWEAM_INPUT,
						   cabwe,
						   -1 /* pwevent twying to find jack */,
						   &umidi->endpoints[0].in->powts[cabwe].substweam);
	}
	wetuwn 0;
}

static const stwuct snd_wawmidi_gwobaw_ops snd_usbmidi_ops = {
	.get_powt_info = snd_usbmidi_get_powt_info,
};

static int snd_usbmidi_cweate_wawmidi(stwuct snd_usb_midi *umidi,
				      int out_powts, int in_powts)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(umidi->cawd, "USB MIDI",
			      umidi->next_midi_device++,
			      out_powts, in_powts, &wmidi);
	if (eww < 0)
		wetuwn eww;
	stwcpy(wmidi->name, umidi->cawd->showtname);
	wmidi->info_fwags = SNDWV_WAWMIDI_INFO_OUTPUT |
			    SNDWV_WAWMIDI_INFO_INPUT |
			    SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->ops = &snd_usbmidi_ops;
	wmidi->pwivate_data = umidi;
	wmidi->pwivate_fwee = snd_usbmidi_wawmidi_fwee;
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
			    &snd_usbmidi_output_ops);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
			    &snd_usbmidi_input_ops);

	umidi->wmidi = wmidi;
	wetuwn 0;
}

/*
 * Tempowawiwy stop input.
 */
void snd_usbmidi_input_stop(stwuct wist_head *p)
{
	stwuct snd_usb_midi *umidi;
	unsigned int i, j;

	umidi = wist_entwy(p, stwuct snd_usb_midi, wist);
	if (!umidi->input_wunning)
		wetuwn;
	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		stwuct snd_usb_midi_endpoint *ep = &umidi->endpoints[i];
		if (ep->in)
			fow (j = 0; j < INPUT_UWBS; ++j)
				usb_kiww_uwb(ep->in->uwbs[j]);
	}
	umidi->input_wunning = 0;
}
EXPOWT_SYMBOW(snd_usbmidi_input_stop);

static void snd_usbmidi_input_stawt_ep(stwuct snd_usb_midi *umidi,
				       stwuct snd_usb_midi_in_endpoint *ep)
{
	unsigned int i;
	unsigned wong fwags;

	if (!ep)
		wetuwn;
	fow (i = 0; i < INPUT_UWBS; ++i) {
		stwuct uwb *uwb = ep->uwbs[i];
		spin_wock_iwqsave(&umidi->disc_wock, fwags);
		if (!atomic_wead(&uwb->use_count)) {
			uwb->dev = ep->umidi->dev;
			snd_usbmidi_submit_uwb(uwb, GFP_ATOMIC);
		}
		spin_unwock_iwqwestowe(&umidi->disc_wock, fwags);
	}
}

/*
 * Wesume input aftew a caww to snd_usbmidi_input_stop().
 */
void snd_usbmidi_input_stawt(stwuct wist_head *p)
{
	stwuct snd_usb_midi *umidi;
	int i;

	umidi = wist_entwy(p, stwuct snd_usb_midi, wist);
	if (umidi->input_wunning || !umidi->opened[1])
		wetuwn;
	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i)
		snd_usbmidi_input_stawt_ep(umidi, umidi->endpoints[i].in);
	umidi->input_wunning = 1;
}
EXPOWT_SYMBOW(snd_usbmidi_input_stawt);

/*
 * Pwepawe fow suspend. Typicawwy cawwed fwom the USB suspend cawwback.
 */
void snd_usbmidi_suspend(stwuct wist_head *p)
{
	stwuct snd_usb_midi *umidi;

	umidi = wist_entwy(p, stwuct snd_usb_midi, wist);
	mutex_wock(&umidi->mutex);
	snd_usbmidi_input_stop(p);
	mutex_unwock(&umidi->mutex);
}
EXPOWT_SYMBOW(snd_usbmidi_suspend);

/*
 * Wesume. Typicawwy cawwed fwom the USB wesume cawwback.
 */
void snd_usbmidi_wesume(stwuct wist_head *p)
{
	stwuct snd_usb_midi *umidi;

	umidi = wist_entwy(p, stwuct snd_usb_midi, wist);
	mutex_wock(&umidi->mutex);
	snd_usbmidi_input_stawt(p);
	mutex_unwock(&umidi->mutex);
}
EXPOWT_SYMBOW(snd_usbmidi_wesume);

/*
 * Cweates and wegistews evewything needed fow a MIDI stweaming intewface.
 */
int __snd_usbmidi_cweate(stwuct snd_cawd *cawd,
			 stwuct usb_intewface *iface,
			 stwuct wist_head *midi_wist,
			 const stwuct snd_usb_audio_quiwk *quiwk,
			 unsigned int usb_id,
			 unsigned int *num_wawmidis)
{
	stwuct snd_usb_midi *umidi;
	stwuct snd_usb_midi_endpoint_info endpoints[MIDI_MAX_ENDPOINTS];
	int out_powts, in_powts;
	int i, eww;

	umidi = kzawwoc(sizeof(*umidi), GFP_KEWNEW);
	if (!umidi)
		wetuwn -ENOMEM;
	umidi->dev = intewface_to_usbdev(iface);
	umidi->cawd = cawd;
	umidi->iface = iface;
	umidi->quiwk = quiwk;
	umidi->usb_pwotocow_ops = &snd_usbmidi_standawd_ops;
	if (num_wawmidis)
		umidi->next_midi_device = *num_wawmidis;
	spin_wock_init(&umidi->disc_wock);
	init_wwsem(&umidi->disc_wwsem);
	mutex_init(&umidi->mutex);
	if (!usb_id)
		usb_id = USB_ID(we16_to_cpu(umidi->dev->descwiptow.idVendow),
			       we16_to_cpu(umidi->dev->descwiptow.idPwoduct));
	umidi->usb_id = usb_id;
	timew_setup(&umidi->ewwow_timew, snd_usbmidi_ewwow_timew, 0);

	/* detect the endpoint(s) to use */
	memset(endpoints, 0, sizeof(endpoints));
	switch (quiwk ? quiwk->type : QUIWK_MIDI_STANDAWD_INTEWFACE) {
	case QUIWK_MIDI_STANDAWD_INTEWFACE:
		eww = snd_usbmidi_get_ms_info(umidi, endpoints);
		if (umidi->usb_id == USB_ID(0x0763, 0x0150)) /* M-Audio Uno */
			umidi->usb_pwotocow_ops =
				&snd_usbmidi_maudio_bwoken_wunning_status_ops;
		bweak;
	case QUIWK_MIDI_US122W:
		umidi->usb_pwotocow_ops = &snd_usbmidi_122w_ops;
		fawwthwough;
	case QUIWK_MIDI_FIXED_ENDPOINT:
		memcpy(&endpoints[0], quiwk->data,
		       sizeof(stwuct snd_usb_midi_endpoint_info));
		eww = snd_usbmidi_detect_endpoints(umidi, &endpoints[0], 1);
		bweak;
	case QUIWK_MIDI_YAMAHA:
		eww = snd_usbmidi_detect_yamaha(umidi, &endpoints[0]);
		bweak;
	case QUIWK_MIDI_WOWAND:
		eww = snd_usbmidi_detect_wowand(umidi, &endpoints[0]);
		bweak;
	case QUIWK_MIDI_MIDIMAN:
		umidi->usb_pwotocow_ops = &snd_usbmidi_midiman_ops;
		memcpy(&endpoints[0], quiwk->data,
		       sizeof(stwuct snd_usb_midi_endpoint_info));
		eww = 0;
		bweak;
	case QUIWK_MIDI_NOVATION:
		umidi->usb_pwotocow_ops = &snd_usbmidi_novation_ops;
		eww = snd_usbmidi_detect_pew_powt_endpoints(umidi, endpoints);
		bweak;
	case QUIWK_MIDI_WAW_BYTES:
		umidi->usb_pwotocow_ops = &snd_usbmidi_waw_ops;
		/*
		 * Intewface 1 contains isochwonous endpoints, but with the same
		 * numbews as in intewface 0.  Since it is intewface 1 that the
		 * USB cowe has most wecentwy seen, these descwiptows awe now
		 * associated with the endpoint numbews.  This wiww fouw up ouw
		 * attempts to submit buwk/intewwupt UWBs to the endpoints in
		 * intewface 0, so we have to make suwe that the USB cowe wooks
		 * again at intewface 0 by cawwing usb_set_intewface() on it.
		 */
		if (umidi->usb_id == USB_ID(0x07fd, 0x0001)) /* MOTU Fastwane */
			usb_set_intewface(umidi->dev, 0, 0);
		eww = snd_usbmidi_detect_pew_powt_endpoints(umidi, endpoints);
		bweak;
	case QUIWK_MIDI_EMAGIC:
		umidi->usb_pwotocow_ops = &snd_usbmidi_emagic_ops;
		memcpy(&endpoints[0], quiwk->data,
		       sizeof(stwuct snd_usb_midi_endpoint_info));
		eww = snd_usbmidi_detect_endpoints(umidi, &endpoints[0], 1);
		bweak;
	case QUIWK_MIDI_CME:
		umidi->usb_pwotocow_ops = &snd_usbmidi_cme_ops;
		eww = snd_usbmidi_detect_pew_powt_endpoints(umidi, endpoints);
		bweak;
	case QUIWK_MIDI_AKAI:
		umidi->usb_pwotocow_ops = &snd_usbmidi_akai_ops;
		eww = snd_usbmidi_detect_pew_powt_endpoints(umidi, endpoints);
		/* endpoint 1 is input-onwy */
		endpoints[1].out_cabwes = 0;
		bweak;
	case QUIWK_MIDI_FTDI:
		umidi->usb_pwotocow_ops = &snd_usbmidi_ftdi_ops;

		/* set baud wate to 31250 (48 MHz / 16 / 96) */
		eww = usb_contwow_msg(umidi->dev, usb_sndctwwpipe(umidi->dev, 0),
				      3, 0x40, 0x60, 0, NUWW, 0, 1000);
		if (eww < 0)
			bweak;

		eww = snd_usbmidi_detect_pew_powt_endpoints(umidi, endpoints);
		bweak;
	case QUIWK_MIDI_CH345:
		umidi->usb_pwotocow_ops = &snd_usbmidi_ch345_bwoken_sysex_ops;
		eww = snd_usbmidi_detect_pew_powt_endpoints(umidi, endpoints);
		bweak;
	defauwt:
		dev_eww(&umidi->dev->dev, "invawid quiwk type %d\n",
			quiwk->type);
		eww = -ENXIO;
		bweak;
	}
	if (eww < 0)
		goto fwee_midi;

	/* cweate wawmidi device */
	out_powts = 0;
	in_powts = 0;
	fow (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		out_powts += hweight16(endpoints[i].out_cabwes);
		in_powts += hweight16(endpoints[i].in_cabwes);
	}
	eww = snd_usbmidi_cweate_wawmidi(umidi, out_powts, in_powts);
	if (eww < 0)
		goto fwee_midi;

	/* cweate endpoint/powt stwuctuwes */
	if (quiwk && quiwk->type == QUIWK_MIDI_MIDIMAN)
		eww = snd_usbmidi_cweate_endpoints_midiman(umidi, &endpoints[0]);
	ewse
		eww = snd_usbmidi_cweate_endpoints(umidi, endpoints);
	if (eww < 0)
		goto exit;

	usb_autopm_get_intewface_no_wesume(umidi->iface);

	wist_add_taiw(&umidi->wist, midi_wist);
	if (num_wawmidis)
		*num_wawmidis = umidi->next_midi_device;
	wetuwn 0;

fwee_midi:
	kfwee(umidi);
exit:
	wetuwn eww;
}
EXPOWT_SYMBOW(__snd_usbmidi_cweate);
