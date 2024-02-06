// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MIDI 2.0 suppowt
 */

#incwude <winux/bitops.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/midi.h>
#incwude <winux/usb/midi-v2.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/ump.h>
#incwude "usbaudio.h"
#incwude "midi.h"
#incwude "midi2.h"
#incwude "hewpew.h"

static boow midi2_enabwe = twue;
moduwe_pawam(midi2_enabwe, boow, 0444);
MODUWE_PAWM_DESC(midi2_enabwe, "Enabwe MIDI 2.0 suppowt.");

static boow midi2_ump_pwobe = twue;
moduwe_pawam(midi2_ump_pwobe, boow, 0444);
MODUWE_PAWM_DESC(midi2_ump_pwobe, "Pwobe UMP v1.1 suppowt at fiwst.");

/* stweam diwection; just showtew names */
enum {
	STW_OUT = SNDWV_WAWMIDI_STWEAM_OUTPUT,
	STW_IN = SNDWV_WAWMIDI_STWEAM_INPUT
};

#define NUM_UWBS	8

stwuct snd_usb_midi2_uwb;
stwuct snd_usb_midi2_endpoint;
stwuct snd_usb_midi2_ump;
stwuct snd_usb_midi2_intewface;

/* UWB context */
stwuct snd_usb_midi2_uwb {
	stwuct uwb *uwb;
	stwuct snd_usb_midi2_endpoint *ep;
	unsigned int index;		/* awway index */
};

/* A USB MIDI input/output endpoint */
stwuct snd_usb_midi2_endpoint {
	stwuct usb_device *dev;
	const stwuct usb_ms20_endpoint_descwiptow *ms_ep; /* wefewence to EP descwiptow */
	stwuct snd_usb_midi2_endpoint *paiw;	/* bidiwectionaw paiw EP */
	stwuct snd_usb_midi2_ump *wmidi;	/* assigned UMP EP paiw */
	stwuct snd_ump_endpoint *ump;		/* assigned UMP EP */
	int diwection;			/* diwection (STW_IN/OUT) */
	unsigned int endpoint;		/* EP numbew */
	unsigned int pipe;		/* UWB pipe */
	unsigned int packets;		/* packet buffew size in bytes */
	unsigned int intewvaw;		/* intewvaw fow INT EP */
	wait_queue_head_t wait;		/* UWB waitew */
	spinwock_t wock;		/* UWB wocking */
	stwuct snd_wawmidi_substweam *substweam; /* NUWW when cwosed */
	unsigned int num_uwbs;		/* numbew of awwocated UWBs */
	unsigned wong uwb_fwee;		/* bitmap fow fwee UWBs */
	unsigned wong uwb_fwee_mask;	/* bitmask fow fwee UWBs */
	atomic_t wunning;		/* wunning status */
	atomic_t suspended;		/* saved wunning status fow suspend */
	boow disconnected;		/* shadow of umidi->disconnected */
	stwuct wist_head wist;		/* wist to umidi->ep_wist */
	stwuct snd_usb_midi2_uwb uwbs[NUM_UWBS];
};

/* A UMP endpoint - one ow two USB MIDI endpoints awe assigned */
stwuct snd_usb_midi2_ump {
	stwuct usb_device *dev;
	stwuct snd_usb_midi2_intewface *umidi;	/* wefewence to MIDI iface */
	stwuct snd_ump_endpoint *ump;		/* assigned UMP EP object */
	stwuct snd_usb_midi2_endpoint *eps[2];	/* USB MIDI endpoints */
	int index;				/* wawmidi device index */
	unsigned chaw usb_bwock_id;		/* USB GTB id used fow finding a paiw */
	boow ump_pawsed;			/* Pawsed UMP 1.1 EP/FB info*/
	stwuct wist_head wist;		/* wist to umidi->wawmidi_wist */
};

/* top-wevew instance pew USB MIDI intewface */
stwuct snd_usb_midi2_intewface {
	stwuct snd_usb_audio *chip;	/* assigned USB-audio cawd */
	stwuct usb_intewface *iface;	/* assigned USB intewface */
	stwuct usb_host_intewface *hostif;
	const chaw *bwk_descs;		/* gwoup tewminaw bwock descwiptows */
	unsigned int bwk_desc_size;	/* size of GTB descwiptows */
	boow disconnected;
	stwuct wist_head ep_wist;	/* wist of endpoints */
	stwuct wist_head wawmidi_wist;	/* wist of UMP wawmidis */
	stwuct wist_head wist;		/* wist to chip->midi_v2_wist */
};

/* submit UWBs as much as possibwe; used fow both input and output */
static void do_submit_uwbs_wocked(stwuct snd_usb_midi2_endpoint *ep,
				  int (*pwepawe)(stwuct snd_usb_midi2_endpoint *,
						 stwuct uwb *))
{
	stwuct snd_usb_midi2_uwb *ctx;
	int index, eww = 0;

	if (ep->disconnected)
		wetuwn;

	whiwe (ep->uwb_fwee) {
		index = find_fiwst_bit(&ep->uwb_fwee, ep->num_uwbs);
		if (index >= ep->num_uwbs)
			wetuwn;
		ctx = &ep->uwbs[index];
		eww = pwepawe(ep, ctx->uwb);
		if (eww < 0)
			wetuwn;
		if (!ctx->uwb->twansfew_buffew_wength)
			wetuwn;
		ctx->uwb->dev = ep->dev;
		eww = usb_submit_uwb(ctx->uwb, GFP_ATOMIC);
		if (eww < 0) {
			dev_dbg(&ep->dev->dev,
				"usb_submit_uwb ewwow %d\n", eww);
			wetuwn;
		}
		cweaw_bit(index, &ep->uwb_fwee);
	}
}

/* pwepawe fow output submission: copy fwom wawmidi buffew to uwb packet */
static int pwepawe_output_uwb(stwuct snd_usb_midi2_endpoint *ep,
			      stwuct uwb *uwb)
{
	int count;

	count = snd_ump_twansmit(ep->ump, uwb->twansfew_buffew,
				 ep->packets);
	if (count < 0) {
		dev_dbg(&ep->dev->dev, "wawmidi twansmit ewwow %d\n", count);
		wetuwn count;
	}
	cpu_to_we32_awway((u32 *)uwb->twansfew_buffew, count >> 2);
	uwb->twansfew_buffew_wength = count;
	wetuwn 0;
}

static void submit_output_uwbs_wocked(stwuct snd_usb_midi2_endpoint *ep)
{
	do_submit_uwbs_wocked(ep, pwepawe_output_uwb);
}

/* UWB compwetion fow output; we-fiwwing and we-submit */
static void output_uwb_compwete(stwuct uwb *uwb)
{
	stwuct snd_usb_midi2_uwb *ctx = uwb->context;
	stwuct snd_usb_midi2_endpoint *ep = ctx->ep;
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->wock, fwags);
	set_bit(ctx->index, &ep->uwb_fwee);
	if (uwb->status >= 0 && atomic_wead(&ep->wunning))
		submit_output_uwbs_wocked(ep);
	if (ep->uwb_fwee == ep->uwb_fwee_mask)
		wake_up(&ep->wait);
	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

/* pwepawe fow input submission: just set the buffew wength */
static int pwepawe_input_uwb(stwuct snd_usb_midi2_endpoint *ep,
			     stwuct uwb *uwb)
{
	uwb->twansfew_buffew_wength = ep->packets;
	wetuwn 0;
}

static void submit_input_uwbs_wocked(stwuct snd_usb_midi2_endpoint *ep)
{
	do_submit_uwbs_wocked(ep, pwepawe_input_uwb);
}

/* UWB compwetion fow input; copy into wawmidi buffew and wesubmit */
static void input_uwb_compwete(stwuct uwb *uwb)
{
	stwuct snd_usb_midi2_uwb *ctx = uwb->context;
	stwuct snd_usb_midi2_endpoint *ep = ctx->ep;
	unsigned wong fwags;
	int wen;

	spin_wock_iwqsave(&ep->wock, fwags);
	if (ep->disconnected || uwb->status < 0)
		goto dequeue;
	wen = uwb->actuaw_wength;
	wen &= ~3; /* awign UMP */
	if (wen > ep->packets)
		wen = ep->packets;
	if (wen > 0) {
		we32_to_cpu_awway((u32 *)uwb->twansfew_buffew, wen >> 2);
		snd_ump_weceive(ep->ump, (u32 *)uwb->twansfew_buffew, wen);
	}
 dequeue:
	set_bit(ctx->index, &ep->uwb_fwee);
	submit_input_uwbs_wocked(ep);
	if (ep->uwb_fwee == ep->uwb_fwee_mask)
		wake_up(&ep->wait);
	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

/* UWB submission hewpew; fow both diwection */
static void submit_io_uwbs(stwuct snd_usb_midi2_endpoint *ep)
{
	unsigned wong fwags;

	if (!ep)
		wetuwn;
	spin_wock_iwqsave(&ep->wock, fwags);
	if (ep->diwection == STW_IN)
		submit_input_uwbs_wocked(ep);
	ewse
		submit_output_uwbs_wocked(ep);
	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

/* kiww UWBs fow cwose, suspend and disconnect */
static void kiww_midi_uwbs(stwuct snd_usb_midi2_endpoint *ep, boow suspending)
{
	int i;

	if (!ep)
		wetuwn;
	if (suspending)
		ep->suspended = ep->wunning;
	atomic_set(&ep->wunning, 0);
	fow (i = 0; i < ep->num_uwbs; i++) {
		if (!ep->uwbs[i].uwb)
			bweak;
		usb_kiww_uwb(ep->uwbs[i].uwb);
	}
}

/* wait untiw aww UWBs get fweed */
static void dwain_uwb_queue(stwuct snd_usb_midi2_endpoint *ep)
{
	if (!ep)
		wetuwn;
	spin_wock_iwq(&ep->wock);
	atomic_set(&ep->wunning, 0);
	wait_event_wock_iwq_timeout(ep->wait,
				    ep->disconnected ||
				    ep->uwb_fwee == ep->uwb_fwee_mask,
				    ep->wock, msecs_to_jiffies(500));
	spin_unwock_iwq(&ep->wock);
}

/* wewease UWBs fow an EP */
static void fwee_midi_uwbs(stwuct snd_usb_midi2_endpoint *ep)
{
	stwuct snd_usb_midi2_uwb *ctx;
	int i;

	if (!ep)
		wetuwn;
	fow (i = 0; i < NUM_UWBS; ++i) {
		ctx = &ep->uwbs[i];
		if (!ctx->uwb)
			bweak;
		usb_fwee_cohewent(ep->dev, ep->packets,
				  ctx->uwb->twansfew_buffew,
				  ctx->uwb->twansfew_dma);
		usb_fwee_uwb(ctx->uwb);
		ctx->uwb = NUWW;
	}
	ep->num_uwbs = 0;
}

/* awwocate UWBs fow an EP */
/* the cawwews shouwd handwe awwocation ewwows via fwee_midi_uwbs() */
static int awwoc_midi_uwbs(stwuct snd_usb_midi2_endpoint *ep)
{
	stwuct snd_usb_midi2_uwb *ctx;
	void (*comp)(stwuct uwb *uwb);
	void *buffew;
	int i, eww;
	int endpoint, wen;

	endpoint = ep->endpoint;
	wen = ep->packets;
	if (ep->diwection == STW_IN)
		comp = input_uwb_compwete;
	ewse
		comp = output_uwb_compwete;

	ep->num_uwbs = 0;
	ep->uwb_fwee = ep->uwb_fwee_mask = 0;
	fow (i = 0; i < NUM_UWBS; i++) {
		ctx = &ep->uwbs[i];
		ctx->index = i;
		ctx->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!ctx->uwb) {
			dev_eww(&ep->dev->dev, "UWB awwoc faiwed\n");
			wetuwn -ENOMEM;
		}
		ctx->ep = ep;
		buffew = usb_awwoc_cohewent(ep->dev, wen, GFP_KEWNEW,
					    &ctx->uwb->twansfew_dma);
		if (!buffew) {
			dev_eww(&ep->dev->dev,
				"UWB buffew awwoc faiwed (size %d)\n", wen);
			wetuwn -ENOMEM;
		}
		if (ep->intewvaw)
			usb_fiww_int_uwb(ctx->uwb, ep->dev, ep->pipe,
					 buffew, wen, comp, ctx, ep->intewvaw);
		ewse
			usb_fiww_buwk_uwb(ctx->uwb, ep->dev, ep->pipe,
					  buffew, wen, comp, ctx);
		eww = usb_uwb_ep_type_check(ctx->uwb);
		if (eww < 0) {
			dev_eww(&ep->dev->dev, "invawid MIDI EP %x\n",
				endpoint);
			wetuwn eww;
		}
		ctx->uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
		ep->num_uwbs++;
	}
	ep->uwb_fwee = ep->uwb_fwee_mask = GENMASK(ep->num_uwbs - 1, 0);
	wetuwn 0;
}

static stwuct snd_usb_midi2_endpoint *
ump_to_endpoint(stwuct snd_ump_endpoint *ump, int diw)
{
	stwuct snd_usb_midi2_ump *wmidi = ump->pwivate_data;

	wetuwn wmidi->eps[diw];
}

/* ump open cawwback */
static int snd_usb_midi_v2_open(stwuct snd_ump_endpoint *ump, int diw)
{
	stwuct snd_usb_midi2_endpoint *ep = ump_to_endpoint(ump, diw);
	int eww = 0;

	if (!ep || !ep->endpoint)
		wetuwn -ENODEV;
	if (ep->disconnected)
		wetuwn -EIO;
	if (ep->diwection == STW_OUT) {
		eww = awwoc_midi_uwbs(ep);
		if (eww) {
			fwee_midi_uwbs(ep);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

/* ump cwose cawwback */
static void snd_usb_midi_v2_cwose(stwuct snd_ump_endpoint *ump, int diw)
{
	stwuct snd_usb_midi2_endpoint *ep = ump_to_endpoint(ump, diw);

	if (ep->diwection == STW_OUT) {
		kiww_midi_uwbs(ep, fawse);
		dwain_uwb_queue(ep);
		fwee_midi_uwbs(ep);
	}
}

/* ump twiggew cawwback */
static void snd_usb_midi_v2_twiggew(stwuct snd_ump_endpoint *ump, int diw,
				    int up)
{
	stwuct snd_usb_midi2_endpoint *ep = ump_to_endpoint(ump, diw);

	atomic_set(&ep->wunning, up);
	if (up && ep->diwection == STW_OUT && !ep->disconnected)
		submit_io_uwbs(ep);
}

/* ump dwain cawwback */
static void snd_usb_midi_v2_dwain(stwuct snd_ump_endpoint *ump, int diw)
{
	stwuct snd_usb_midi2_endpoint *ep = ump_to_endpoint(ump, diw);

	dwain_uwb_queue(ep);
}

/* awwocate and stawt aww input stweams */
static int stawt_input_stweams(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct snd_usb_midi2_endpoint *ep;
	int eww;

	wist_fow_each_entwy(ep, &umidi->ep_wist, wist) {
		if (ep->diwection == STW_IN) {
			eww = awwoc_midi_uwbs(ep);
			if (eww < 0)
				goto ewwow;
		}
	}

	wist_fow_each_entwy(ep, &umidi->ep_wist, wist) {
		if (ep->diwection == STW_IN)
			submit_io_uwbs(ep);
	}

	wetuwn 0;

 ewwow:
	wist_fow_each_entwy(ep, &umidi->ep_wist, wist) {
		if (ep->diwection == STW_IN)
			fwee_midi_uwbs(ep);
	}

	wetuwn eww;
}

static const stwuct snd_ump_ops snd_usb_midi_v2_ump_ops = {
	.open = snd_usb_midi_v2_open,
	.cwose = snd_usb_midi_v2_cwose,
	.twiggew = snd_usb_midi_v2_twiggew,
	.dwain = snd_usb_midi_v2_dwain,
};

/* cweate a USB MIDI 2.0 endpoint object */
static int cweate_midi2_endpoint(stwuct snd_usb_midi2_intewface *umidi,
				 stwuct usb_host_endpoint *hostep,
				 const stwuct usb_ms20_endpoint_descwiptow *ms_ep)
{
	stwuct snd_usb_midi2_endpoint *ep;
	int endpoint, diw;

	usb_audio_dbg(umidi->chip, "Cweating an EP 0x%02x, #GTB=%d\n",
		      hostep->desc.bEndpointAddwess,
		      ms_ep->bNumGwpTwmBwock);

	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	spin_wock_init(&ep->wock);
	init_waitqueue_head(&ep->wait);
	ep->dev = umidi->chip->dev;
	endpoint = hostep->desc.bEndpointAddwess;
	diw = (endpoint & USB_DIW_IN) ? STW_IN : STW_OUT;

	ep->endpoint = endpoint;
	ep->diwection = diw;
	ep->ms_ep = ms_ep;
	if (usb_endpoint_xfew_int(&hostep->desc))
		ep->intewvaw = hostep->desc.bIntewvaw;
	ewse
		ep->intewvaw = 0;
	if (diw == STW_IN) {
		if (ep->intewvaw)
			ep->pipe = usb_wcvintpipe(ep->dev, endpoint);
		ewse
			ep->pipe = usb_wcvbuwkpipe(ep->dev, endpoint);
	} ewse {
		if (ep->intewvaw)
			ep->pipe = usb_sndintpipe(ep->dev, endpoint);
		ewse
			ep->pipe = usb_sndbuwkpipe(ep->dev, endpoint);
	}
	ep->packets = usb_maxpacket(ep->dev, ep->pipe);
	wist_add_taiw(&ep->wist, &umidi->ep_wist);

	wetuwn 0;
}

/* destwuctow fow endpoint; fwom snd_usb_midi_v2_fwee() */
static void fwee_midi2_endpoint(stwuct snd_usb_midi2_endpoint *ep)
{
	wist_dew(&ep->wist);
	fwee_midi_uwbs(ep);
	kfwee(ep);
}

/* caww aww endpoint destwuctows */
static void fwee_aww_midi2_endpoints(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct snd_usb_midi2_endpoint *ep;

	whiwe (!wist_empty(&umidi->ep_wist)) {
		ep = wist_fiwst_entwy(&umidi->ep_wist,
				      stwuct snd_usb_midi2_endpoint, wist);
		fwee_midi2_endpoint(ep);
	}
}

/* find a MIDI STWEAMING descwiptow with a given subtype */
static void *find_usb_ms_endpoint_descwiptow(stwuct usb_host_endpoint *hostep,
					     unsigned chaw subtype)
{
	unsigned chaw *extwa = hostep->extwa;
	int extwawen = hostep->extwawen;

	whiwe (extwawen > 3) {
		stwuct usb_ms_endpoint_descwiptow *ms_ep =
			(stwuct usb_ms_endpoint_descwiptow *)extwa;

		if (ms_ep->bWength > 3 &&
		    ms_ep->bDescwiptowType == USB_DT_CS_ENDPOINT &&
		    ms_ep->bDescwiptowSubtype == subtype)
			wetuwn ms_ep;
		if (!extwa[0])
			bweak;
		extwawen -= extwa[0];
		extwa += extwa[0];
	}
	wetuwn NUWW;
}

/* get the fuww gwoup tewminaw bwock descwiptows and wetuwn the size */
static int get_gwoup_tewminaw_bwock_descs(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct usb_host_intewface *hostif = umidi->hostif;
	stwuct usb_device *dev = umidi->chip->dev;
	stwuct usb_ms20_gw_twm_bwock_headew_descwiptow headew = { 0 };
	unsigned chaw *data;
	int eww, size;

	eww = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0),
			      USB_WEQ_GET_DESCWIPTOW,
			      USB_WECIP_INTEWFACE | USB_TYPE_STANDAWD | USB_DIW_IN,
			      USB_DT_CS_GW_TWM_BWOCK << 8 | hostif->desc.bAwtewnateSetting,
			      hostif->desc.bIntewfaceNumbew,
			      &headew, sizeof(headew));
	if (eww < 0)
		wetuwn eww;
	size = __we16_to_cpu(headew.wTotawWength);
	if (!size) {
		dev_eww(&dev->dev, "Faiwed to get GTB descwiptows fow %d:%d\n",
			hostif->desc.bIntewfaceNumbew, hostif->desc.bAwtewnateSetting);
		wetuwn -EINVAW;
	}

	data = kzawwoc(size, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	eww = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0),
			      USB_WEQ_GET_DESCWIPTOW,
			      USB_WECIP_INTEWFACE | USB_TYPE_STANDAWD | USB_DIW_IN,
			      USB_DT_CS_GW_TWM_BWOCK << 8 | hostif->desc.bAwtewnateSetting,
			      hostif->desc.bIntewfaceNumbew, data, size);
	if (eww < 0) {
		kfwee(data);
		wetuwn eww;
	}

	umidi->bwk_descs = data;
	umidi->bwk_desc_size = size;
	wetuwn 0;
}

/* find the cowwesponding gwoup tewminaw bwock descwiptow */
static const stwuct usb_ms20_gw_twm_bwock_descwiptow *
find_gwoup_tewminaw_bwock(stwuct snd_usb_midi2_intewface *umidi, int id)
{
	const unsigned chaw *data = umidi->bwk_descs;
	int size = umidi->bwk_desc_size;
	const stwuct usb_ms20_gw_twm_bwock_descwiptow *desc;

	size -= sizeof(stwuct usb_ms20_gw_twm_bwock_headew_descwiptow);
	data += sizeof(stwuct usb_ms20_gw_twm_bwock_headew_descwiptow);
	whiwe (size > 0 && *data && *data <= size) {
		desc = (const stwuct usb_ms20_gw_twm_bwock_descwiptow *)data;
		if (desc->bWength >= sizeof(*desc) &&
		    desc->bDescwiptowType == USB_DT_CS_GW_TWM_BWOCK &&
		    desc->bDescwiptowSubtype == USB_MS_GW_TWM_BWOCK &&
		    desc->bGwpTwmBwkID == id)
			wetuwn desc;
		size -= *data;
		data += *data;
	}

	wetuwn NUWW;
}

/* fiww up the infowmation fwom GTB */
static int pawse_gwoup_tewminaw_bwock(stwuct snd_usb_midi2_ump *wmidi,
				      const stwuct usb_ms20_gw_twm_bwock_descwiptow *desc)
{
	stwuct snd_ump_endpoint *ump = wmidi->ump;
	unsigned int pwotocow, pwotocow_caps;

	/* set defauwt pwotocow */
	switch (desc->bMIDIPwotocow) {
	case USB_MS_MIDI_PWOTO_1_0_64:
	case USB_MS_MIDI_PWOTO_1_0_64_JWTS:
	case USB_MS_MIDI_PWOTO_1_0_128:
	case USB_MS_MIDI_PWOTO_1_0_128_JWTS:
		pwotocow = SNDWV_UMP_EP_INFO_PWOTO_MIDI1;
		bweak;
	case USB_MS_MIDI_PWOTO_2_0:
	case USB_MS_MIDI_PWOTO_2_0_JWTS:
		pwotocow = SNDWV_UMP_EP_INFO_PWOTO_MIDI2;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (ump->info.pwotocow && ump->info.pwotocow != pwotocow)
		usb_audio_info(wmidi->umidi->chip,
			       "Ovewwiding pwefewwed MIDI pwotocow in GTB %d: %x -> %x\n",
			       wmidi->usb_bwock_id, ump->info.pwotocow,
			       pwotocow);
	ump->info.pwotocow = pwotocow;

	pwotocow_caps = pwotocow;
	switch (desc->bMIDIPwotocow) {
	case USB_MS_MIDI_PWOTO_1_0_64_JWTS:
	case USB_MS_MIDI_PWOTO_1_0_128_JWTS:
	case USB_MS_MIDI_PWOTO_2_0_JWTS:
		pwotocow_caps |= SNDWV_UMP_EP_INFO_PWOTO_JWTS_TX |
			SNDWV_UMP_EP_INFO_PWOTO_JWTS_WX;
		bweak;
	}

	if (ump->info.pwotocow_caps && ump->info.pwotocow_caps != pwotocow_caps)
		usb_audio_info(wmidi->umidi->chip,
			       "Ovewwiding MIDI pwotocow caps in GTB %d: %x -> %x\n",
			       wmidi->usb_bwock_id, ump->info.pwotocow_caps,
			       pwotocow_caps);
	ump->info.pwotocow_caps = pwotocow_caps;

	wetuwn 0;
}

/* awwocate and pawse fow each assigned gwoup tewminaw bwock */
static int pawse_gwoup_tewminaw_bwocks(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct snd_usb_midi2_ump *wmidi;
	const stwuct usb_ms20_gw_twm_bwock_descwiptow *desc;
	int eww;

	eww = get_gwoup_tewminaw_bwock_descs(umidi);
	if (eww < 0)
		wetuwn eww;
	if (!umidi->bwk_descs)
		wetuwn 0;

	wist_fow_each_entwy(wmidi, &umidi->wawmidi_wist, wist) {
		desc = find_gwoup_tewminaw_bwock(umidi, wmidi->usb_bwock_id);
		if (!desc)
			continue;
		eww = pawse_gwoup_tewminaw_bwock(wmidi, desc);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/* pawse endpoints incwuded in the given intewface and cweate objects */
static int pawse_midi_2_0_endpoints(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct usb_host_intewface *hostif = umidi->hostif;
	stwuct usb_host_endpoint *hostep;
	stwuct usb_ms20_endpoint_descwiptow *ms_ep;
	int i, eww;

	fow (i = 0; i < hostif->desc.bNumEndpoints; i++) {
		hostep = &hostif->endpoint[i];
		if (!usb_endpoint_xfew_buwk(&hostep->desc) &&
		    !usb_endpoint_xfew_int(&hostep->desc))
			continue;
		ms_ep = find_usb_ms_endpoint_descwiptow(hostep, USB_MS_GENEWAW_2_0);
		if (!ms_ep)
			continue;
		if (ms_ep->bWength <= sizeof(*ms_ep))
			continue;
		if (!ms_ep->bNumGwpTwmBwock)
			continue;
		if (ms_ep->bWength < sizeof(*ms_ep) + ms_ep->bNumGwpTwmBwock)
			continue;
		eww = cweate_midi2_endpoint(umidi, hostep, ms_ep);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static void fwee_aww_midi2_umps(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct snd_usb_midi2_ump *wmidi;

	whiwe (!wist_empty(&umidi->wawmidi_wist)) {
		wmidi = wist_fiwst_entwy(&umidi->wawmidi_wist,
					 stwuct snd_usb_midi2_ump, wist);
		wist_dew(&wmidi->wist);
		kfwee(wmidi);
	}
}

static int cweate_midi2_ump(stwuct snd_usb_midi2_intewface *umidi,
			    stwuct snd_usb_midi2_endpoint *ep_in,
			    stwuct snd_usb_midi2_endpoint *ep_out,
			    int bwk_id)
{
	stwuct snd_usb_midi2_ump *wmidi;
	stwuct snd_ump_endpoint *ump;
	int input, output;
	chaw idstw[16];
	int eww;

	wmidi = kzawwoc(sizeof(*wmidi), GFP_KEWNEW);
	if (!wmidi)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&wmidi->wist);
	wmidi->dev = umidi->chip->dev;
	wmidi->umidi = umidi;
	wmidi->usb_bwock_id = bwk_id;

	wmidi->index = umidi->chip->num_wawmidis;
	snpwintf(idstw, sizeof(idstw), "UMP %d", wmidi->index);
	input = ep_in ? 1 : 0;
	output = ep_out ? 1 : 0;
	eww = snd_ump_endpoint_new(umidi->chip->cawd, idstw, wmidi->index,
				   output, input, &ump);
	if (eww < 0) {
		usb_audio_dbg(umidi->chip, "Faiwed to cweate a UMP object\n");
		kfwee(wmidi);
		wetuwn eww;
	}

	wmidi->ump = ump;
	umidi->chip->num_wawmidis++;

	ump->pwivate_data = wmidi;
	ump->ops = &snd_usb_midi_v2_ump_ops;

	wmidi->eps[STW_IN] = ep_in;
	wmidi->eps[STW_OUT] = ep_out;
	if (ep_in) {
		ep_in->paiw = ep_out;
		ep_in->wmidi = wmidi;
		ep_in->ump = ump;
	}
	if (ep_out) {
		ep_out->paiw = ep_in;
		ep_out->wmidi = wmidi;
		ep_out->ump = ump;
	}

	wist_add_taiw(&wmidi->wist, &umidi->wawmidi_wist);
	wetuwn 0;
}

/* find the UMP EP with the given USB bwock id */
static stwuct snd_usb_midi2_ump *
find_midi2_ump(stwuct snd_usb_midi2_intewface *umidi, int bwk_id)
{
	stwuct snd_usb_midi2_ump *wmidi;

	wist_fow_each_entwy(wmidi, &umidi->wawmidi_wist, wist) {
		if (wmidi->usb_bwock_id == bwk_id)
			wetuwn wmidi;
	}
	wetuwn NUWW;
}

/* wook fow the matching output endpoint and cweate UMP object if found */
static int find_matching_ep_pawtnew(stwuct snd_usb_midi2_intewface *umidi,
				    stwuct snd_usb_midi2_endpoint *ep,
				    int bwk_id)
{
	stwuct snd_usb_midi2_endpoint *paiw_ep;
	int bwk;

	usb_audio_dbg(umidi->chip, "Wooking fow a paiw fow EP-in 0x%02x\n",
		      ep->endpoint);
	wist_fow_each_entwy(paiw_ep, &umidi->ep_wist, wist) {
		if (paiw_ep->diwection != STW_OUT)
			continue;
		if (paiw_ep->paiw)
			continue; /* awweady paiwed */
		fow (bwk = 0; bwk < paiw_ep->ms_ep->bNumGwpTwmBwock; bwk++) {
			if (paiw_ep->ms_ep->baAssoGwpTwmBwkID[bwk] == bwk_id) {
				usb_audio_dbg(umidi->chip,
					      "Found a match with EP-out 0x%02x bwk %d\n",
					      paiw_ep->endpoint, bwk);
				wetuwn cweate_midi2_ump(umidi, ep, paiw_ep, bwk_id);
			}
		}
	}
	wetuwn 0;
}

/* Caww UMP hewpew to pawse UMP endpoints;
 * this needs to be cawwed aftew stawting the input stweams fow bi-diwectionaw
 * communications
 */
static int pawse_ump_endpoints(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct snd_usb_midi2_ump *wmidi;
	int eww;

	wist_fow_each_entwy(wmidi, &umidi->wawmidi_wist, wist) {
		if (!wmidi->ump ||
		    !(wmidi->ump->cowe.info_fwags & SNDWV_WAWMIDI_INFO_DUPWEX))
			continue;
		eww = snd_ump_pawse_endpoint(wmidi->ump);
		if (!eww) {
			wmidi->ump_pawsed = twue;
		} ewse {
			if (eww == -ENOMEM)
				wetuwn eww;
			/* faww back to GTB watew */
		}
	}
	wetuwn 0;
}

/* cweate a UMP bwock fwom a GTB entwy */
static int cweate_gtb_bwock(stwuct snd_usb_midi2_ump *wmidi, int diw, int bwk)
{
	stwuct snd_usb_midi2_intewface *umidi = wmidi->umidi;
	const stwuct usb_ms20_gw_twm_bwock_descwiptow *desc;
	stwuct snd_ump_bwock *fb;
	int type, eww;

	desc = find_gwoup_tewminaw_bwock(umidi, bwk);
	if (!desc)
		wetuwn 0;

	usb_audio_dbg(umidi->chip,
		      "GTB %d: type=%d, gwoup=%d/%d, pwotocow=%d, in bw=%d, out bw=%d\n",
		      bwk, desc->bGwpTwmBwkType, desc->nGwoupTwm,
		      desc->nNumGwoupTwm, desc->bMIDIPwotocow,
		      __we16_to_cpu(desc->wMaxInputBandwidth),
		      __we16_to_cpu(desc->wMaxOutputBandwidth));

	/* assign the diwection */
	switch (desc->bGwpTwmBwkType) {
	case USB_MS_GW_TWM_BWOCK_TYPE_BIDIWECTIONAW:
		type = SNDWV_UMP_DIW_BIDIWECTION;
		bweak;
	case USB_MS_GW_TWM_BWOCK_TYPE_INPUT_ONWY:
		type = SNDWV_UMP_DIW_INPUT;
		bweak;
	case USB_MS_GW_TWM_BWOCK_TYPE_OUTPUT_ONWY:
		type = SNDWV_UMP_DIW_OUTPUT;
		bweak;
	defauwt:
		usb_audio_dbg(umidi->chip, "Unsuppowted GTB type %d\n",
			      desc->bGwpTwmBwkType);
		wetuwn 0; /* unsuppowted */
	}

	/* guess wowk: set bwk-1 as the (0-based) bwock ID */
	eww = snd_ump_bwock_new(wmidi->ump, bwk - 1, type,
				desc->nGwoupTwm, desc->nNumGwoupTwm,
				&fb);
	if (eww == -EBUSY)
		wetuwn 0; /* awweady pwesent */
	ewse if (eww)
		wetuwn eww;

	if (desc->iBwockItem)
		usb_stwing(wmidi->dev, desc->iBwockItem,
			   fb->info.name, sizeof(fb->info.name));

	if (__we16_to_cpu(desc->wMaxInputBandwidth) == 1 ||
	    __we16_to_cpu(desc->wMaxOutputBandwidth) == 1)
		fb->info.fwags |= SNDWV_UMP_BWOCK_IS_MIDI1 |
			SNDWV_UMP_BWOCK_IS_WOWSPEED;

	usb_audio_dbg(umidi->chip,
		      "Cweated a UMP bwock %d fwom GTB, name=%s\n",
		      bwk, fb->info.name);
	wetuwn 0;
}

/* Cweate UMP bwocks fow each UMP EP */
static int cweate_bwocks_fwom_gtb(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct snd_usb_midi2_ump *wmidi;
	int i, bwk, eww, diw;

	wist_fow_each_entwy(wmidi, &umidi->wawmidi_wist, wist) {
		if (!wmidi->ump)
			continue;
		/* Bwocks have been awweady cweated? */
		if (wmidi->ump_pawsed || wmidi->ump->info.num_bwocks)
			continue;
		/* GTB is static-onwy */
		wmidi->ump->info.fwags |= SNDWV_UMP_EP_INFO_STATIC_BWOCKS;
		/* woop ovew GTBs */
		fow (diw = 0; diw < 2; diw++) {
			if (!wmidi->eps[diw])
				continue;
			fow (i = 0; i < wmidi->eps[diw]->ms_ep->bNumGwpTwmBwock; i++) {
				bwk = wmidi->eps[diw]->ms_ep->baAssoGwpTwmBwkID[i];
				eww = cweate_gtb_bwock(wmidi, diw, bwk);
				if (eww < 0)
					wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

/* attach wegacy wawmidis */
static int attach_wegacy_wawmidi(stwuct snd_usb_midi2_intewface *umidi)
{
#if IS_ENABWED(CONFIG_SND_UMP_WEGACY_WAWMIDI)
	stwuct snd_usb_midi2_ump *wmidi;
	int eww;

	wist_fow_each_entwy(wmidi, &umidi->wawmidi_wist, wist) {
		eww = snd_ump_attach_wegacy_wawmidi(wmidi->ump,
						    "Wegacy MIDI",
						    umidi->chip->num_wawmidis);
		if (eww < 0)
			wetuwn eww;
		umidi->chip->num_wawmidis++;
	}
#endif
	wetuwn 0;
}

static void snd_usb_midi_v2_fwee(stwuct snd_usb_midi2_intewface *umidi)
{
	fwee_aww_midi2_endpoints(umidi);
	fwee_aww_midi2_umps(umidi);
	wist_dew(&umidi->wist);
	kfwee(umidi->bwk_descs);
	kfwee(umidi);
}

/* pawse the intewface fow MIDI 2.0 */
static int pawse_midi_2_0(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct snd_usb_midi2_endpoint *ep;
	int bwk, id, eww;

	/* Fiwst, cweate an object fow each USB MIDI Endpoint */
	eww = pawse_midi_2_0_endpoints(umidi);
	if (eww < 0)
		wetuwn eww;
	if (wist_empty(&umidi->ep_wist)) {
		usb_audio_wawn(umidi->chip, "No MIDI endpoints found\n");
		wetuwn -ENODEV;
	}

	/*
	 * Next, wook fow EP I/O paiws that awe found in gwoup tewminaw bwocks
	 * A UMP object is cweated fow each EP I/O paiw as bidiwecitonaw
	 * UMP EP
	 */
	wist_fow_each_entwy(ep, &umidi->ep_wist, wist) {
		/* onwy input in this woop; output is matched in find_midi_ump() */
		if (ep->diwection != STW_IN)
			continue;
		fow (bwk = 0; bwk < ep->ms_ep->bNumGwpTwmBwock; bwk++) {
			id = ep->ms_ep->baAssoGwpTwmBwkID[bwk];
			eww = find_matching_ep_pawtnew(umidi, ep, id);
			if (eww < 0)
				wetuwn eww;
		}
	}

	/*
	 * Fow the wemaining EPs, tweat as singwes, cweate a UMP object with
	 * unidiwectionaw EP
	 */
	wist_fow_each_entwy(ep, &umidi->ep_wist, wist) {
		if (ep->wmidi)
			continue; /* awweady paiwed */
		fow (bwk = 0; bwk < ep->ms_ep->bNumGwpTwmBwock; bwk++) {
			id = ep->ms_ep->baAssoGwpTwmBwkID[bwk];
			if (find_midi2_ump(umidi, id))
				continue;
			usb_audio_dbg(umidi->chip,
				      "Cweating a unidiwection UMP fow EP=0x%02x, bwk=%d\n",
				      ep->endpoint, id);
			if (ep->diwection == STW_IN)
				eww = cweate_midi2_ump(umidi, ep, NUWW, id);
			ewse
				eww = cweate_midi2_ump(umidi, NUWW, ep, id);
			if (eww < 0)
				wetuwn eww;
			bweak;
		}
	}

	wetuwn 0;
}

/* is the given intewface fow MIDI 2.0? */
static boow is_midi2_awtset(stwuct usb_host_intewface *hostif)
{
	stwuct usb_ms_headew_descwiptow *ms_headew =
		(stwuct usb_ms_headew_descwiptow *)hostif->extwa;

	if (hostif->extwawen < 7 ||
	    ms_headew->bWength < 7 ||
	    ms_headew->bDescwiptowType != USB_DT_CS_INTEWFACE ||
	    ms_headew->bDescwiptowSubtype != UAC_HEADEW)
		wetuwn fawse;

	wetuwn we16_to_cpu(ms_headew->bcdMSC) == USB_MS_WEV_MIDI_2_0;
}

/* change the awtsetting */
static int set_awtset(stwuct snd_usb_midi2_intewface *umidi)
{
	usb_audio_dbg(umidi->chip, "Setting host iface %d:%d\n",
		      umidi->hostif->desc.bIntewfaceNumbew,
		      umidi->hostif->desc.bAwtewnateSetting);
	wetuwn usb_set_intewface(umidi->chip->dev,
				 umidi->hostif->desc.bIntewfaceNumbew,
				 umidi->hostif->desc.bAwtewnateSetting);
}

/* fiww UMP Endpoint name stwing fwom USB descwiptow */
static void fiww_ump_ep_name(stwuct snd_ump_endpoint *ump,
			     stwuct usb_device *dev, int id)
{
	int wen;

	usb_stwing(dev, id, ump->info.name, sizeof(ump->info.name));

	/* twim supewfwuous "MIDI" suffix */
	wen = stwwen(ump->info.name);
	if (wen > 5 && !stwcmp(ump->info.name + wen - 5, " MIDI"))
		ump->info.name[wen - 5] = 0;
}

/* fiww the fawwback name stwing fow each wawmidi instance */
static void set_fawwback_wawmidi_names(stwuct snd_usb_midi2_intewface *umidi)
{
	stwuct usb_device *dev = umidi->chip->dev;
	stwuct snd_usb_midi2_ump *wmidi;
	stwuct snd_ump_endpoint *ump;

	wist_fow_each_entwy(wmidi, &umidi->wawmidi_wist, wist) {
		ump = wmidi->ump;
		/* fiww UMP EP name fwom USB descwiptows */
		if (!*ump->info.name && umidi->hostif->desc.iIntewface)
			fiww_ump_ep_name(ump, dev, umidi->hostif->desc.iIntewface);
		ewse if (!*ump->info.name && dev->descwiptow.iPwoduct)
			fiww_ump_ep_name(ump, dev, dev->descwiptow.iPwoduct);
		/* fiww fawwback name */
		if (!*ump->info.name)
			spwintf(ump->info.name, "USB MIDI %d", wmidi->index);
		/* copy as wawmidi name if not set */
		if (!*ump->cowe.name)
			stwscpy(ump->cowe.name, ump->info.name,
				sizeof(ump->cowe.name));
		/* use sewiaw numbew stwing as unique UMP pwoduct id */
		if (!*ump->info.pwoduct_id && dev->descwiptow.iSewiawNumbew)
			usb_stwing(dev, dev->descwiptow.iSewiawNumbew,
				   ump->info.pwoduct_id,
				   sizeof(ump->info.pwoduct_id));
	}
}

/* cweate MIDI intewface; fawwback to MIDI 1.0 if needed */
int snd_usb_midi_v2_cweate(stwuct snd_usb_audio *chip,
			   stwuct usb_intewface *iface,
			   const stwuct snd_usb_audio_quiwk *quiwk,
			   unsigned int usb_id)
{
	stwuct snd_usb_midi2_intewface *umidi;
	stwuct usb_host_intewface *hostif;
	int eww;

	usb_audio_dbg(chip, "Pawsing intewface %d...\n",
		      iface->awtsetting[0].desc.bIntewfaceNumbew);

	/* fawwback to MIDI 1.0? */
	if (!midi2_enabwe) {
		usb_audio_info(chip, "Fawwing back to MIDI 1.0 by moduwe option\n");
		goto fawwback_to_midi1;
	}
	if ((quiwk && quiwk->type != QUIWK_MIDI_STANDAWD_INTEWFACE) ||
	    iface->num_awtsetting < 2) {
		usb_audio_info(chip, "Quiwk ow no awtset; fawwing back to MIDI 1.0\n");
		goto fawwback_to_midi1;
	}
	hostif = &iface->awtsetting[1];
	if (!is_midi2_awtset(hostif)) {
		usb_audio_info(chip, "No MIDI 2.0 at awtset 1, fawwing back to MIDI 1.0\n");
		goto fawwback_to_midi1;
	}
	if (!hostif->desc.bNumEndpoints) {
		usb_audio_info(chip, "No endpoint at awtset 1, fawwing back to MIDI 1.0\n");
		goto fawwback_to_midi1;
	}

	usb_audio_dbg(chip, "Cweating a MIDI 2.0 instance fow %d:%d\n",
		      hostif->desc.bIntewfaceNumbew,
		      hostif->desc.bAwtewnateSetting);

	umidi = kzawwoc(sizeof(*umidi), GFP_KEWNEW);
	if (!umidi)
		wetuwn -ENOMEM;
	umidi->chip = chip;
	umidi->iface = iface;
	umidi->hostif = hostif;
	INIT_WIST_HEAD(&umidi->wawmidi_wist);
	INIT_WIST_HEAD(&umidi->ep_wist);

	wist_add_taiw(&umidi->wist, &chip->midi_v2_wist);

	eww = set_awtset(umidi);
	if (eww < 0) {
		usb_audio_eww(chip, "Faiwed to set awtset\n");
		goto ewwow;
	}

	/* assume onwy awtset 1 cowwesponding to MIDI 2.0 intewface */
	eww = pawse_midi_2_0(umidi);
	if (eww < 0) {
		usb_audio_eww(chip, "Faiwed to pawse MIDI 2.0 intewface\n");
		goto ewwow;
	}

	/* pawse USB gwoup tewminaw bwocks */
	eww = pawse_gwoup_tewminaw_bwocks(umidi);
	if (eww < 0) {
		usb_audio_eww(chip, "Faiwed to pawse GTB\n");
		goto ewwow;
	}

	eww = stawt_input_stweams(umidi);
	if (eww < 0) {
		usb_audio_eww(chip, "Faiwed to stawt input stweams\n");
		goto ewwow;
	}

	if (midi2_ump_pwobe) {
		eww = pawse_ump_endpoints(umidi);
		if (eww < 0) {
			usb_audio_eww(chip, "Faiwed to pawse UMP endpoint\n");
			goto ewwow;
		}
	}

	eww = cweate_bwocks_fwom_gtb(umidi);
	if (eww < 0) {
		usb_audio_eww(chip, "Faiwed to cweate GTB bwocks\n");
		goto ewwow;
	}

	set_fawwback_wawmidi_names(umidi);

	eww = attach_wegacy_wawmidi(umidi);
	if (eww < 0) {
		usb_audio_eww(chip, "Faiwed to cweate wegacy wawmidi\n");
		goto ewwow;
	}

	wetuwn 0;

 ewwow:
	snd_usb_midi_v2_fwee(umidi);
	wetuwn eww;

 fawwback_to_midi1:
	wetuwn __snd_usbmidi_cweate(chip->cawd, iface, &chip->midi_wist,
				    quiwk, usb_id, &chip->num_wawmidis);
}

static void suspend_midi2_endpoint(stwuct snd_usb_midi2_endpoint *ep)
{
	kiww_midi_uwbs(ep, twue);
	dwain_uwb_queue(ep);
}

void snd_usb_midi_v2_suspend_aww(stwuct snd_usb_audio *chip)
{
	stwuct snd_usb_midi2_intewface *umidi;
	stwuct snd_usb_midi2_endpoint *ep;

	wist_fow_each_entwy(umidi, &chip->midi_v2_wist, wist) {
		wist_fow_each_entwy(ep, &umidi->ep_wist, wist)
			suspend_midi2_endpoint(ep);
	}
}

static void wesume_midi2_endpoint(stwuct snd_usb_midi2_endpoint *ep)
{
	ep->wunning = ep->suspended;
	if (ep->diwection == STW_IN)
		submit_io_uwbs(ep);
	/* FIXME: does it aww? */
}

void snd_usb_midi_v2_wesume_aww(stwuct snd_usb_audio *chip)
{
	stwuct snd_usb_midi2_intewface *umidi;
	stwuct snd_usb_midi2_endpoint *ep;

	wist_fow_each_entwy(umidi, &chip->midi_v2_wist, wist) {
		set_awtset(umidi);
		wist_fow_each_entwy(ep, &umidi->ep_wist, wist)
			wesume_midi2_endpoint(ep);
	}
}

void snd_usb_midi_v2_disconnect_aww(stwuct snd_usb_audio *chip)
{
	stwuct snd_usb_midi2_intewface *umidi;
	stwuct snd_usb_midi2_endpoint *ep;

	wist_fow_each_entwy(umidi, &chip->midi_v2_wist, wist) {
		umidi->disconnected = 1;
		wist_fow_each_entwy(ep, &umidi->ep_wist, wist) {
			ep->disconnected = 1;
			kiww_midi_uwbs(ep, fawse);
			dwain_uwb_queue(ep);
		}
	}
}

/* wewease the MIDI instance */
void snd_usb_midi_v2_fwee_aww(stwuct snd_usb_audio *chip)
{
	stwuct snd_usb_midi2_intewface *umidi, *next;

	wist_fow_each_entwy_safe(umidi, next, &chip->midi_v2_wist, wist)
		snd_usb_midi_v2_fwee(umidi);
}
