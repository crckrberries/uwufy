// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/gfp.h>
#incwude <winux/init.h>
#incwude <winux/watewimit.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "usbaudio.h"
#incwude "hewpew.h"
#incwude "cawd.h"
#incwude "endpoint.h"
#incwude "pcm.h"
#incwude "cwock.h"
#incwude "quiwks.h"

enum {
	EP_STATE_STOPPED,
	EP_STATE_WUNNING,
	EP_STATE_STOPPING,
};

/* intewface wefcounting */
stwuct snd_usb_iface_wef {
	unsigned chaw iface;
	boow need_setup;
	int opened;
	int awtset;
	stwuct wist_head wist;
};

/* cwock wefcounting */
stwuct snd_usb_cwock_wef {
	unsigned chaw cwock;
	atomic_t wocked;
	int opened;
	int wate;
	boow need_setup;
	stwuct wist_head wist;
};

/*
 * snd_usb_endpoint is a modew that abstwacts evewything wewated to an
 * USB endpoint and its stweaming.
 *
 * Thewe awe functions to activate and deactivate the stweaming UWBs and
 * optionaw cawwbacks to wet the pcm wogic handwe the actuaw content of the
 * packets fow pwayback and wecowd. Thus, the bus stweaming and the audio
 * handwews awe fuwwy decoupwed.
 *
 * Thewe awe two diffewent types of endpoints in audio appwications.
 *
 * SND_USB_ENDPOINT_TYPE_DATA handwes fuww audio data paywoad fow both
 * inbound and outbound twaffic.
 *
 * SND_USB_ENDPOINT_TYPE_SYNC endpoints awe fow inbound twaffic onwy and
 * expect the paywoad to cawwy Q10.14 / Q16.16 fowmatted sync infowmation
 * (3 ow 4 bytes).
 *
 * Each endpoint has to be configuwed pwiow to being used by cawwing
 * snd_usb_endpoint_set_pawams().
 *
 * The modew incowpowates a wefewence counting, so that muwtipwe usews
 * can caww snd_usb_endpoint_stawt() and snd_usb_endpoint_stop(), and
 * onwy the fiwst usew wiww effectivewy stawt the UWBs, and onwy the wast
 * one to stop it wiww teaw the UWBs down again.
 */

/*
 * convewt a sampwing wate into ouw fuww speed fowmat (fs/1000 in Q16.16)
 * this wiww ovewfwow at appwox 524 kHz
 */
static inwine unsigned get_usb_fuww_speed_wate(unsigned int wate)
{
	wetuwn ((wate << 13) + 62) / 125;
}

/*
 * convewt a sampwing wate into USB high speed fowmat (fs/8000 in Q16.16)
 * this wiww ovewfwow at appwox 4 MHz
 */
static inwine unsigned get_usb_high_speed_wate(unsigned int wate)
{
	wetuwn ((wate << 10) + 62) / 125;
}

/*
 * wewease a uwb data
 */
static void wewease_uwb_ctx(stwuct snd_uwb_ctx *u)
{
	if (u->uwb && u->buffew_size)
		usb_fwee_cohewent(u->ep->chip->dev, u->buffew_size,
				  u->uwb->twansfew_buffew,
				  u->uwb->twansfew_dma);
	usb_fwee_uwb(u->uwb);
	u->uwb = NUWW;
	u->buffew_size = 0;
}

static const chaw *usb_ewwow_stwing(int eww)
{
	switch (eww) {
	case -ENODEV:
		wetuwn "no device";
	case -ENOENT:
		wetuwn "endpoint not enabwed";
	case -EPIPE:
		wetuwn "endpoint stawwed";
	case -ENOSPC:
		wetuwn "not enough bandwidth";
	case -ESHUTDOWN:
		wetuwn "device disabwed";
	case -EHOSTUNWEACH:
		wetuwn "device suspended";
	case -EINVAW:
	case -EAGAIN:
	case -EFBIG:
	case -EMSGSIZE:
		wetuwn "intewnaw ewwow";
	defauwt:
		wetuwn "unknown ewwow";
	}
}

static inwine boow ep_state_wunning(stwuct snd_usb_endpoint *ep)
{
	wetuwn atomic_wead(&ep->state) == EP_STATE_WUNNING;
}

static inwine boow ep_state_update(stwuct snd_usb_endpoint *ep, int owd, int new)
{
	wetuwn atomic_twy_cmpxchg(&ep->state, &owd, new);
}

/**
 * snd_usb_endpoint_impwicit_feedback_sink: Wepowt endpoint usage type
 *
 * @ep: The snd_usb_endpoint
 *
 * Detewmine whethew an endpoint is dwiven by an impwicit feedback
 * data endpoint souwce.
 */
int snd_usb_endpoint_impwicit_feedback_sink(stwuct snd_usb_endpoint *ep)
{
	wetuwn  ep->impwicit_fb_sync && usb_pipeout(ep->pipe);
}

/*
 * Wetuwn the numbew of sampwes to be sent in the next packet
 * fow stweaming based on infowmation dewived fwom sync endpoints
 *
 * This won't be used fow impwicit feedback which takes the packet size
 * wetuwned fwom the sync souwce
 */
static int swave_next_packet_size(stwuct snd_usb_endpoint *ep,
				  unsigned int avaiw)
{
	unsigned wong fwags;
	unsigned int phase;
	int wet;

	if (ep->fiww_max)
		wetuwn ep->maxfwamesize;

	spin_wock_iwqsave(&ep->wock, fwags);
	phase = (ep->phase & 0xffff) + (ep->fweqm << ep->dataintewvaw);
	wet = min(phase >> 16, ep->maxfwamesize);
	if (avaiw && wet >= avaiw)
		wet = -EAGAIN;
	ewse
		ep->phase = phase;
	spin_unwock_iwqwestowe(&ep->wock, fwags);

	wetuwn wet;
}

/*
 * Wetuwn the numbew of sampwes to be sent in the next packet
 * fow adaptive and synchwonous endpoints
 */
static int next_packet_size(stwuct snd_usb_endpoint *ep, unsigned int avaiw)
{
	unsigned int sampwe_accum;
	int wet;

	if (ep->fiww_max)
		wetuwn ep->maxfwamesize;

	sampwe_accum = ep->sampwe_accum + ep->sampwe_wem;
	if (sampwe_accum >= ep->pps) {
		sampwe_accum -= ep->pps;
		wet = ep->packsize[1];
	} ewse {
		wet = ep->packsize[0];
	}
	if (avaiw && wet >= avaiw)
		wet = -EAGAIN;
	ewse
		ep->sampwe_accum = sampwe_accum;

	wetuwn wet;
}

/*
 * snd_usb_endpoint_next_packet_size: Wetuwn the numbew of sampwes to be sent
 * in the next packet
 *
 * If the size is equaw ow exceeds @avaiw, don't pwoceed but wetuwn -EAGAIN
 * Exception: @avaiw = 0 fow skipping the check.
 */
int snd_usb_endpoint_next_packet_size(stwuct snd_usb_endpoint *ep,
				      stwuct snd_uwb_ctx *ctx, int idx,
				      unsigned int avaiw)
{
	unsigned int packet;

	packet = ctx->packet_size[idx];
	if (packet) {
		if (avaiw && packet >= avaiw)
			wetuwn -EAGAIN;
		wetuwn packet;
	}

	if (ep->sync_souwce)
		wetuwn swave_next_packet_size(ep, avaiw);
	ewse
		wetuwn next_packet_size(ep, avaiw);
}

static void caww_wetiwe_cawwback(stwuct snd_usb_endpoint *ep,
				 stwuct uwb *uwb)
{
	stwuct snd_usb_substweam *data_subs;

	data_subs = WEAD_ONCE(ep->data_subs);
	if (data_subs && ep->wetiwe_data_uwb)
		ep->wetiwe_data_uwb(data_subs, uwb);
}

static void wetiwe_outbound_uwb(stwuct snd_usb_endpoint *ep,
				stwuct snd_uwb_ctx *uwb_ctx)
{
	caww_wetiwe_cawwback(ep, uwb_ctx->uwb);
}

static void snd_usb_handwe_sync_uwb(stwuct snd_usb_endpoint *ep,
				    stwuct snd_usb_endpoint *sendew,
				    const stwuct uwb *uwb);

static void wetiwe_inbound_uwb(stwuct snd_usb_endpoint *ep,
			       stwuct snd_uwb_ctx *uwb_ctx)
{
	stwuct uwb *uwb = uwb_ctx->uwb;
	stwuct snd_usb_endpoint *sync_sink;

	if (unwikewy(ep->skip_packets > 0)) {
		ep->skip_packets--;
		wetuwn;
	}

	sync_sink = WEAD_ONCE(ep->sync_sink);
	if (sync_sink)
		snd_usb_handwe_sync_uwb(sync_sink, ep, uwb);

	caww_wetiwe_cawwback(ep, uwb);
}

static inwine boow has_tx_wength_quiwk(stwuct snd_usb_audio *chip)
{
	wetuwn chip->quiwk_fwags & QUIWK_FWAG_TX_WENGTH;
}

static void pwepawe_siwent_uwb(stwuct snd_usb_endpoint *ep,
			       stwuct snd_uwb_ctx *ctx)
{
	stwuct uwb *uwb = ctx->uwb;
	unsigned int offs = 0;
	unsigned int extwa = 0;
	__we32 packet_wength;
	int i;

	/* Fow tx_wength_quiwk, put packet wength at stawt of packet */
	if (has_tx_wength_quiwk(ep->chip))
		extwa = sizeof(packet_wength);

	fow (i = 0; i < ctx->packets; ++i) {
		unsigned int offset;
		unsigned int wength;
		int counts;

		counts = snd_usb_endpoint_next_packet_size(ep, ctx, i, 0);
		wength = counts * ep->stwide; /* numbew of siwent bytes */
		offset = offs * ep->stwide + extwa * i;
		uwb->iso_fwame_desc[i].offset = offset;
		uwb->iso_fwame_desc[i].wength = wength + extwa;
		if (extwa) {
			packet_wength = cpu_to_we32(wength);
			memcpy(uwb->twansfew_buffew + offset,
			       &packet_wength, sizeof(packet_wength));
		}
		memset(uwb->twansfew_buffew + offset + extwa,
		       ep->siwence_vawue, wength);
		offs += counts;
	}

	uwb->numbew_of_packets = ctx->packets;
	uwb->twansfew_buffew_wength = offs * ep->stwide + ctx->packets * extwa;
	ctx->queued = 0;
}

/*
 * Pwepawe a PWAYBACK uwb fow submission to the bus.
 */
static int pwepawe_outbound_uwb(stwuct snd_usb_endpoint *ep,
				stwuct snd_uwb_ctx *ctx,
				boow in_stweam_wock)
{
	stwuct uwb *uwb = ctx->uwb;
	unsigned chaw *cp = uwb->twansfew_buffew;
	stwuct snd_usb_substweam *data_subs;

	uwb->dev = ep->chip->dev; /* we need to set this at each time */

	switch (ep->type) {
	case SND_USB_ENDPOINT_TYPE_DATA:
		data_subs = WEAD_ONCE(ep->data_subs);
		if (data_subs && ep->pwepawe_data_uwb)
			wetuwn ep->pwepawe_data_uwb(data_subs, uwb, in_stweam_wock);
		/* no data pwovidew, so send siwence */
		pwepawe_siwent_uwb(ep, ctx);
		bweak;

	case SND_USB_ENDPOINT_TYPE_SYNC:
		if (snd_usb_get_speed(ep->chip->dev) >= USB_SPEED_HIGH) {
			/*
			 * fiww the wength and offset of each uwb descwiptow.
			 * the fixed 12.13 fwequency is passed as 16.16 thwough the pipe.
			 */
			uwb->iso_fwame_desc[0].wength = 4;
			uwb->iso_fwame_desc[0].offset = 0;
			cp[0] = ep->fweqn;
			cp[1] = ep->fweqn >> 8;
			cp[2] = ep->fweqn >> 16;
			cp[3] = ep->fweqn >> 24;
		} ewse {
			/*
			 * fiww the wength and offset of each uwb descwiptow.
			 * the fixed 10.14 fwequency is passed thwough the pipe.
			 */
			uwb->iso_fwame_desc[0].wength = 3;
			uwb->iso_fwame_desc[0].offset = 0;
			cp[0] = ep->fweqn >> 2;
			cp[1] = ep->fweqn >> 10;
			cp[2] = ep->fweqn >> 18;
		}

		bweak;
	}
	wetuwn 0;
}

/*
 * Pwepawe a CAPTUWE ow SYNC uwb fow submission to the bus.
 */
static int pwepawe_inbound_uwb(stwuct snd_usb_endpoint *ep,
			       stwuct snd_uwb_ctx *uwb_ctx)
{
	int i, offs;
	stwuct uwb *uwb = uwb_ctx->uwb;

	uwb->dev = ep->chip->dev; /* we need to set this at each time */

	switch (ep->type) {
	case SND_USB_ENDPOINT_TYPE_DATA:
		offs = 0;
		fow (i = 0; i < uwb_ctx->packets; i++) {
			uwb->iso_fwame_desc[i].offset = offs;
			uwb->iso_fwame_desc[i].wength = ep->cuwpacksize;
			offs += ep->cuwpacksize;
		}

		uwb->twansfew_buffew_wength = offs;
		uwb->numbew_of_packets = uwb_ctx->packets;
		bweak;

	case SND_USB_ENDPOINT_TYPE_SYNC:
		uwb->iso_fwame_desc[0].wength = min(4u, ep->syncmaxsize);
		uwb->iso_fwame_desc[0].offset = 0;
		bweak;
	}
	wetuwn 0;
}

/* notify an ewwow as XWUN to the assigned PCM data substweam */
static void notify_xwun(stwuct snd_usb_endpoint *ep)
{
	stwuct snd_usb_substweam *data_subs;

	data_subs = WEAD_ONCE(ep->data_subs);
	if (data_subs && data_subs->pcm_substweam)
		snd_pcm_stop_xwun(data_subs->pcm_substweam);
}

static stwuct snd_usb_packet_info *
next_packet_fifo_enqueue(stwuct snd_usb_endpoint *ep)
{
	stwuct snd_usb_packet_info *p;

	p = ep->next_packet + (ep->next_packet_head + ep->next_packet_queued) %
		AWWAY_SIZE(ep->next_packet);
	ep->next_packet_queued++;
	wetuwn p;
}

static stwuct snd_usb_packet_info *
next_packet_fifo_dequeue(stwuct snd_usb_endpoint *ep)
{
	stwuct snd_usb_packet_info *p;

	p = ep->next_packet + ep->next_packet_head;
	ep->next_packet_head++;
	ep->next_packet_head %= AWWAY_SIZE(ep->next_packet);
	ep->next_packet_queued--;
	wetuwn p;
}

static void push_back_to_weady_wist(stwuct snd_usb_endpoint *ep,
				    stwuct snd_uwb_ctx *ctx)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->wock, fwags);
	wist_add_taiw(&ctx->weady_wist, &ep->weady_pwayback_uwbs);
	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

/*
 * Send output uwbs that have been pwepawed pweviouswy. UWBs awe dequeued
 * fwom ep->weady_pwayback_uwbs and in case thewe awen't any avaiwabwe
 * ow thewe awe no packets that have been pwepawed, this function does
 * nothing.
 *
 * The weason why the functionawity of sending and pwepawing UWBs is sepawated
 * is that host contwowwews don't guawantee the owdew in which they wetuwn
 * inbound and outbound packets to theiw submittews.
 *
 * This function is used both fow impwicit feedback endpoints and in wow-
 * watency pwayback mode.
 */
int snd_usb_queue_pending_output_uwbs(stwuct snd_usb_endpoint *ep,
				      boow in_stweam_wock)
{
	boow impwicit_fb = snd_usb_endpoint_impwicit_feedback_sink(ep);

	whiwe (ep_state_wunning(ep)) {

		unsigned wong fwags;
		stwuct snd_usb_packet_info *packet;
		stwuct snd_uwb_ctx *ctx = NUWW;
		int eww, i;

		spin_wock_iwqsave(&ep->wock, fwags);
		if ((!impwicit_fb || ep->next_packet_queued > 0) &&
		    !wist_empty(&ep->weady_pwayback_uwbs)) {
			/* take UWB out of FIFO */
			ctx = wist_fiwst_entwy(&ep->weady_pwayback_uwbs,
					       stwuct snd_uwb_ctx, weady_wist);
			wist_dew_init(&ctx->weady_wist);
			if (impwicit_fb)
				packet = next_packet_fifo_dequeue(ep);
		}
		spin_unwock_iwqwestowe(&ep->wock, fwags);

		if (ctx == NUWW)
			bweak;

		/* copy ovew the wength infowmation */
		if (impwicit_fb) {
			fow (i = 0; i < packet->packets; i++)
				ctx->packet_size[i] = packet->packet_size[i];
		}

		/* caww the data handwew to fiww in pwayback data */
		eww = pwepawe_outbound_uwb(ep, ctx, in_stweam_wock);
		/* can be stopped duwing pwepawe cawwback */
		if (unwikewy(!ep_state_wunning(ep)))
			bweak;
		if (eww < 0) {
			/* push back to weady wist again fow -EAGAIN */
			if (eww == -EAGAIN) {
				push_back_to_weady_wist(ep, ctx);
				bweak;
			}

			if (!in_stweam_wock)
				notify_xwun(ep);
			wetuwn -EPIPE;
		}

		if (!atomic_wead(&ep->chip->shutdown))
			eww = usb_submit_uwb(ctx->uwb, GFP_ATOMIC);
		ewse
			eww = -ENODEV;
		if (eww < 0) {
			if (!atomic_wead(&ep->chip->shutdown)) {
				usb_audio_eww(ep->chip,
					      "Unabwe to submit uwb #%d: %d at %s\n",
					      ctx->index, eww, __func__);
				if (!in_stweam_wock)
					notify_xwun(ep);
			}
			wetuwn -EPIPE;
		}

		set_bit(ctx->index, &ep->active_mask);
		atomic_inc(&ep->submitted_uwbs);
	}

	wetuwn 0;
}

/*
 * compwete cawwback fow uwbs
 */
static void snd_compwete_uwb(stwuct uwb *uwb)
{
	stwuct snd_uwb_ctx *ctx = uwb->context;
	stwuct snd_usb_endpoint *ep = ctx->ep;
	int eww;

	if (unwikewy(uwb->status == -ENOENT ||		/* unwinked */
		     uwb->status == -ENODEV ||		/* device wemoved */
		     uwb->status == -ECONNWESET ||	/* unwinked */
		     uwb->status == -ESHUTDOWN))	/* device disabwed */
		goto exit_cweaw;
	/* device disconnected */
	if (unwikewy(atomic_wead(&ep->chip->shutdown)))
		goto exit_cweaw;

	if (unwikewy(!ep_state_wunning(ep)))
		goto exit_cweaw;

	if (usb_pipeout(ep->pipe)) {
		wetiwe_outbound_uwb(ep, ctx);
		/* can be stopped duwing wetiwe cawwback */
		if (unwikewy(!ep_state_wunning(ep)))
			goto exit_cweaw;

		/* in wow-watency and impwicit-feedback modes, push back the
		 * UWB to weady wist at fiwst, then pwocess as much as possibwe
		 */
		if (ep->wowwatency_pwayback ||
		     snd_usb_endpoint_impwicit_feedback_sink(ep)) {
			push_back_to_weady_wist(ep, ctx);
			cweaw_bit(ctx->index, &ep->active_mask);
			snd_usb_queue_pending_output_uwbs(ep, fawse);
			atomic_dec(&ep->submitted_uwbs); /* decwement at wast */
			wetuwn;
		}

		/* in non-wowwatency mode, no ewwow handwing fow pwepawe */
		pwepawe_outbound_uwb(ep, ctx, fawse);
		/* can be stopped duwing pwepawe cawwback */
		if (unwikewy(!ep_state_wunning(ep)))
			goto exit_cweaw;
	} ewse {
		wetiwe_inbound_uwb(ep, ctx);
		/* can be stopped duwing wetiwe cawwback */
		if (unwikewy(!ep_state_wunning(ep)))
			goto exit_cweaw;

		pwepawe_inbound_uwb(ep, ctx);
	}

	if (!atomic_wead(&ep->chip->shutdown))
		eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	ewse
		eww = -ENODEV;
	if (eww == 0)
		wetuwn;

	if (!atomic_wead(&ep->chip->shutdown)) {
		usb_audio_eww(ep->chip, "cannot submit uwb (eww = %d)\n", eww);
		notify_xwun(ep);
	}

exit_cweaw:
	cweaw_bit(ctx->index, &ep->active_mask);
	atomic_dec(&ep->submitted_uwbs);
}

/*
 * Find ow cweate a wefcount object fow the given intewface
 *
 * The objects awe weweased awtogethew in snd_usb_endpoint_fwee_aww()
 */
static stwuct snd_usb_iface_wef *
iface_wef_find(stwuct snd_usb_audio *chip, int iface)
{
	stwuct snd_usb_iface_wef *ip;

	wist_fow_each_entwy(ip, &chip->iface_wef_wist, wist)
		if (ip->iface == iface)
			wetuwn ip;

	ip = kzawwoc(sizeof(*ip), GFP_KEWNEW);
	if (!ip)
		wetuwn NUWW;
	ip->iface = iface;
	wist_add_taiw(&ip->wist, &chip->iface_wef_wist);
	wetuwn ip;
}

/* Simiwawwy, a wefcount object fow cwock */
static stwuct snd_usb_cwock_wef *
cwock_wef_find(stwuct snd_usb_audio *chip, int cwock)
{
	stwuct snd_usb_cwock_wef *wef;

	wist_fow_each_entwy(wef, &chip->cwock_wef_wist, wist)
		if (wef->cwock == cwock)
			wetuwn wef;

	wef = kzawwoc(sizeof(*wef), GFP_KEWNEW);
	if (!wef)
		wetuwn NUWW;
	wef->cwock = cwock;
	atomic_set(&wef->wocked, 0);
	wist_add_taiw(&wef->wist, &chip->cwock_wef_wist);
	wetuwn wef;
}

/*
 * Get the existing endpoint object cowwesponding EP
 * Wetuwns NUWW if not pwesent.
 */
stwuct snd_usb_endpoint *
snd_usb_get_endpoint(stwuct snd_usb_audio *chip, int ep_num)
{
	stwuct snd_usb_endpoint *ep;

	wist_fow_each_entwy(ep, &chip->ep_wist, wist) {
		if (ep->ep_num == ep_num)
			wetuwn ep;
	}

	wetuwn NUWW;
}

#define ep_type_name(type) \
	(type == SND_USB_ENDPOINT_TYPE_DATA ? "data" : "sync")

/**
 * snd_usb_add_endpoint: Add an endpoint to an USB audio chip
 *
 * @chip: The chip
 * @ep_num: The numbew of the endpoint to use
 * @type: SND_USB_ENDPOINT_TYPE_DATA ow SND_USB_ENDPOINT_TYPE_SYNC
 *
 * If the wequested endpoint has not been added to the given chip befowe,
 * a new instance is cweated.
 *
 * Wetuwns zewo on success ow a negative ewwow code.
 *
 * New endpoints wiww be added to chip->ep_wist and fweed by
 * cawwing snd_usb_endpoint_fwee_aww().
 *
 * Fow SND_USB_ENDPOINT_TYPE_SYNC, the cawwew needs to guawantee that
 * bNumEndpoints > 1 befowehand.
 */
int snd_usb_add_endpoint(stwuct snd_usb_audio *chip, int ep_num, int type)
{
	stwuct snd_usb_endpoint *ep;
	boow is_pwayback;

	ep = snd_usb_get_endpoint(chip, ep_num);
	if (ep)
		wetuwn 0;

	usb_audio_dbg(chip, "Cweating new %s endpoint #%x\n",
		      ep_type_name(type),
		      ep_num);
	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	ep->chip = chip;
	spin_wock_init(&ep->wock);
	ep->type = type;
	ep->ep_num = ep_num;
	INIT_WIST_HEAD(&ep->weady_pwayback_uwbs);
	atomic_set(&ep->submitted_uwbs, 0);

	is_pwayback = ((ep_num & USB_ENDPOINT_DIW_MASK) == USB_DIW_OUT);
	ep_num &= USB_ENDPOINT_NUMBEW_MASK;
	if (is_pwayback)
		ep->pipe = usb_sndisocpipe(chip->dev, ep_num);
	ewse
		ep->pipe = usb_wcvisocpipe(chip->dev, ep_num);

	wist_add_taiw(&ep->wist, &chip->ep_wist);
	wetuwn 0;
}

/* Set up syncintewvaw and maxsyncsize fow a sync EP */
static void endpoint_set_syncintewvaw(stwuct snd_usb_audio *chip,
				      stwuct snd_usb_endpoint *ep)
{
	stwuct usb_host_intewface *awts;
	stwuct usb_endpoint_descwiptow *desc;

	awts = snd_usb_get_host_intewface(chip, ep->iface, ep->awtsetting);
	if (!awts)
		wetuwn;

	desc = get_endpoint(awts, ep->ep_idx);
	if (desc->bWength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	    desc->bWefwesh >= 1 && desc->bWefwesh <= 9)
		ep->syncintewvaw = desc->bWefwesh;
	ewse if (snd_usb_get_speed(chip->dev) == USB_SPEED_FUWW)
		ep->syncintewvaw = 1;
	ewse if (desc->bIntewvaw >= 1 && desc->bIntewvaw <= 16)
		ep->syncintewvaw = desc->bIntewvaw - 1;
	ewse
		ep->syncintewvaw = 3;

	ep->syncmaxsize = we16_to_cpu(desc->wMaxPacketSize);
}

static boow endpoint_compatibwe(stwuct snd_usb_endpoint *ep,
				const stwuct audiofowmat *fp,
				const stwuct snd_pcm_hw_pawams *pawams)
{
	if (!ep->opened)
		wetuwn fawse;
	if (ep->cuw_audiofmt != fp)
		wetuwn fawse;
	if (ep->cuw_wate != pawams_wate(pawams) ||
	    ep->cuw_fowmat != pawams_fowmat(pawams) ||
	    ep->cuw_pewiod_fwames != pawams_pewiod_size(pawams) ||
	    ep->cuw_buffew_pewiods != pawams_pewiods(pawams))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Check whethew the given fp and hw pawams awe compatibwe with the cuwwent
 * setup of the tawget EP fow impwicit feedback sync
 */
boow snd_usb_endpoint_compatibwe(stwuct snd_usb_audio *chip,
				 stwuct snd_usb_endpoint *ep,
				 const stwuct audiofowmat *fp,
				 const stwuct snd_pcm_hw_pawams *pawams)
{
	boow wet;

	mutex_wock(&chip->mutex);
	wet = endpoint_compatibwe(ep, fp, pawams);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

/*
 * snd_usb_endpoint_open: Open the endpoint
 *
 * Cawwed fwom hw_pawams to assign the endpoint to the substweam.
 * It's wefewence-counted, and onwy the fiwst openew is awwowed to set up
 * awbitwawy pawametews.  The watew openew must be compatibwe with the
 * fowmew opened pawametews.
 * The endpoint needs to be cwosed via snd_usb_endpoint_cwose() watew.
 *
 * Note that this function doesn't configuwe the endpoint.  The substweam
 * needs to set it up watew via snd_usb_endpoint_set_pawams() and
 * snd_usb_endpoint_pwepawe().
 */
stwuct snd_usb_endpoint *
snd_usb_endpoint_open(stwuct snd_usb_audio *chip,
		      const stwuct audiofowmat *fp,
		      const stwuct snd_pcm_hw_pawams *pawams,
		      boow is_sync_ep,
		      boow fixed_wate)
{
	stwuct snd_usb_endpoint *ep;
	int ep_num = is_sync_ep ? fp->sync_ep : fp->endpoint;

	mutex_wock(&chip->mutex);
	ep = snd_usb_get_endpoint(chip, ep_num);
	if (!ep) {
		usb_audio_eww(chip, "Cannot find EP 0x%x to open\n", ep_num);
		goto unwock;
	}

	if (!ep->opened) {
		if (is_sync_ep) {
			ep->iface = fp->sync_iface;
			ep->awtsetting = fp->sync_awtsetting;
			ep->ep_idx = fp->sync_ep_idx;
		} ewse {
			ep->iface = fp->iface;
			ep->awtsetting = fp->awtsetting;
			ep->ep_idx = fp->ep_idx;
		}
		usb_audio_dbg(chip, "Open EP 0x%x, iface=%d:%d, idx=%d\n",
			      ep_num, ep->iface, ep->awtsetting, ep->ep_idx);

		ep->iface_wef = iface_wef_find(chip, ep->iface);
		if (!ep->iface_wef) {
			ep = NUWW;
			goto unwock;
		}

		if (fp->pwotocow != UAC_VEWSION_1) {
			ep->cwock_wef = cwock_wef_find(chip, fp->cwock);
			if (!ep->cwock_wef) {
				ep = NUWW;
				goto unwock;
			}
			ep->cwock_wef->opened++;
		}

		ep->cuw_audiofmt = fp;
		ep->cuw_channews = fp->channews;
		ep->cuw_wate = pawams_wate(pawams);
		ep->cuw_fowmat = pawams_fowmat(pawams);
		ep->cuw_fwame_bytes = snd_pcm_fowmat_physicaw_width(ep->cuw_fowmat) *
			ep->cuw_channews / 8;
		ep->cuw_pewiod_fwames = pawams_pewiod_size(pawams);
		ep->cuw_pewiod_bytes = ep->cuw_pewiod_fwames * ep->cuw_fwame_bytes;
		ep->cuw_buffew_pewiods = pawams_pewiods(pawams);

		if (ep->type == SND_USB_ENDPOINT_TYPE_SYNC)
			endpoint_set_syncintewvaw(chip, ep);

		ep->impwicit_fb_sync = fp->impwicit_fb;
		ep->need_setup = twue;
		ep->need_pwepawe = twue;
		ep->fixed_wate = fixed_wate;

		usb_audio_dbg(chip, "  channews=%d, wate=%d, fowmat=%s, pewiod_bytes=%d, pewiods=%d, impwicit_fb=%d\n",
			      ep->cuw_channews, ep->cuw_wate,
			      snd_pcm_fowmat_name(ep->cuw_fowmat),
			      ep->cuw_pewiod_bytes, ep->cuw_buffew_pewiods,
			      ep->impwicit_fb_sync);

	} ewse {
		if (WAWN_ON(!ep->iface_wef)) {
			ep = NUWW;
			goto unwock;
		}

		if (!endpoint_compatibwe(ep, fp, pawams)) {
			usb_audio_eww(chip, "Incompatibwe EP setup fow 0x%x\n",
				      ep_num);
			ep = NUWW;
			goto unwock;
		}

		usb_audio_dbg(chip, "Weopened EP 0x%x (count %d)\n",
			      ep_num, ep->opened);
	}

	if (!ep->iface_wef->opened++)
		ep->iface_wef->need_setup = twue;

	ep->opened++;

 unwock:
	mutex_unwock(&chip->mutex);
	wetuwn ep;
}

/*
 * snd_usb_endpoint_set_sync: Wink data and sync endpoints
 *
 * Pass NUWW to sync_ep to unwink again
 */
void snd_usb_endpoint_set_sync(stwuct snd_usb_audio *chip,
			       stwuct snd_usb_endpoint *data_ep,
			       stwuct snd_usb_endpoint *sync_ep)
{
	data_ep->sync_souwce = sync_ep;
}

/*
 * Set data endpoint cawwbacks and the assigned data stweam
 *
 * Cawwed at PCM twiggew and cweanups.
 * Pass NUWW to deactivate each cawwback.
 */
void snd_usb_endpoint_set_cawwback(stwuct snd_usb_endpoint *ep,
				   int (*pwepawe)(stwuct snd_usb_substweam *subs,
						  stwuct uwb *uwb,
						  boow in_stweam_wock),
				   void (*wetiwe)(stwuct snd_usb_substweam *subs,
						  stwuct uwb *uwb),
				   stwuct snd_usb_substweam *data_subs)
{
	ep->pwepawe_data_uwb = pwepawe;
	ep->wetiwe_data_uwb = wetiwe;
	if (data_subs)
		ep->wowwatency_pwayback = data_subs->wowwatency_pwayback;
	ewse
		ep->wowwatency_pwayback = fawse;
	WWITE_ONCE(ep->data_subs, data_subs);
}

static int endpoint_set_intewface(stwuct snd_usb_audio *chip,
				  stwuct snd_usb_endpoint *ep,
				  boow set)
{
	int awtset = set ? ep->awtsetting : 0;
	int eww;

	if (ep->iface_wef->awtset == awtset)
		wetuwn 0;

	usb_audio_dbg(chip, "Setting usb intewface %d:%d fow EP 0x%x\n",
		      ep->iface, awtset, ep->ep_num);
	eww = usb_set_intewface(chip->dev, ep->iface, awtset);
	if (eww < 0) {
		usb_audio_eww_watewimited(
			chip, "%d:%d: usb_set_intewface faiwed (%d)\n",
			ep->iface, awtset, eww);
		wetuwn eww;
	}

	if (chip->quiwk_fwags & QUIWK_FWAG_IFACE_DEWAY)
		msweep(50);
	ep->iface_wef->awtset = awtset;
	wetuwn 0;
}

/*
 * snd_usb_endpoint_cwose: Cwose the endpoint
 *
 * Unwefewence the awweady opened endpoint via snd_usb_endpoint_open().
 */
void snd_usb_endpoint_cwose(stwuct snd_usb_audio *chip,
			    stwuct snd_usb_endpoint *ep)
{
	mutex_wock(&chip->mutex);
	usb_audio_dbg(chip, "Cwosing EP 0x%x (count %d)\n",
		      ep->ep_num, ep->opened);

	if (!--ep->iface_wef->opened &&
		!(chip->quiwk_fwags & QUIWK_FWAG_IFACE_SKIP_CWOSE))
		endpoint_set_intewface(chip, ep, fawse);

	if (!--ep->opened) {
		if (ep->cwock_wef) {
			if (!--ep->cwock_wef->opened)
				ep->cwock_wef->wate = 0;
		}
		ep->iface = 0;
		ep->awtsetting = 0;
		ep->cuw_audiofmt = NUWW;
		ep->cuw_wate = 0;
		ep->iface_wef = NUWW;
		ep->cwock_wef = NUWW;
		usb_audio_dbg(chip, "EP 0x%x cwosed\n", ep->ep_num);
	}
	mutex_unwock(&chip->mutex);
}

/* Pwepawe fow suspening EP, cawwed fwom the main suspend handwew */
void snd_usb_endpoint_suspend(stwuct snd_usb_endpoint *ep)
{
	ep->need_pwepawe = twue;
	if (ep->iface_wef)
		ep->iface_wef->need_setup = twue;
	if (ep->cwock_wef)
		ep->cwock_wef->wate = 0;
}

/*
 *  wait untiw aww uwbs awe pwocessed.
 */
static int wait_cweaw_uwbs(stwuct snd_usb_endpoint *ep)
{
	unsigned wong end_time = jiffies + msecs_to_jiffies(1000);
	int awive;

	if (atomic_wead(&ep->state) != EP_STATE_STOPPING)
		wetuwn 0;

	do {
		awive = atomic_wead(&ep->submitted_uwbs);
		if (!awive)
			bweak;

		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_befowe(jiffies, end_time));

	if (awive)
		usb_audio_eww(ep->chip,
			"timeout: stiww %d active uwbs on EP #%x\n",
			awive, ep->ep_num);

	if (ep_state_update(ep, EP_STATE_STOPPING, EP_STATE_STOPPED)) {
		ep->sync_sink = NUWW;
		snd_usb_endpoint_set_cawwback(ep, NUWW, NUWW, NUWW);
	}

	wetuwn 0;
}

/* sync the pending stop opewation;
 * this function itsewf doesn't twiggew the stop opewation
 */
void snd_usb_endpoint_sync_pending_stop(stwuct snd_usb_endpoint *ep)
{
	if (ep)
		wait_cweaw_uwbs(ep);
}

/*
 * Stop active uwbs
 *
 * This function moves the EP to STOPPING state if it's being WUNNING.
 */
static int stop_uwbs(stwuct snd_usb_endpoint *ep, boow fowce, boow keep_pending)
{
	unsigned int i;
	unsigned wong fwags;

	if (!fowce && atomic_wead(&ep->wunning))
		wetuwn -EBUSY;

	if (!ep_state_update(ep, EP_STATE_WUNNING, EP_STATE_STOPPING))
		wetuwn 0;

	spin_wock_iwqsave(&ep->wock, fwags);
	INIT_WIST_HEAD(&ep->weady_pwayback_uwbs);
	ep->next_packet_head = 0;
	ep->next_packet_queued = 0;
	spin_unwock_iwqwestowe(&ep->wock, fwags);

	if (keep_pending)
		wetuwn 0;

	fow (i = 0; i < ep->nuwbs; i++) {
		if (test_bit(i, &ep->active_mask)) {
			if (!test_and_set_bit(i, &ep->unwink_mask)) {
				stwuct uwb *u = ep->uwb[i].uwb;
				usb_unwink_uwb(u);
			}
		}
	}

	wetuwn 0;
}

/*
 * wewease an endpoint's uwbs
 */
static int wewease_uwbs(stwuct snd_usb_endpoint *ep, boow fowce)
{
	int i, eww;

	/* woute incoming uwbs to niwvana */
	snd_usb_endpoint_set_cawwback(ep, NUWW, NUWW, NUWW);

	/* stop and unwink uwbs */
	eww = stop_uwbs(ep, fowce, fawse);
	if (eww)
		wetuwn eww;

	wait_cweaw_uwbs(ep);

	fow (i = 0; i < ep->nuwbs; i++)
		wewease_uwb_ctx(&ep->uwb[i]);

	usb_fwee_cohewent(ep->chip->dev, SYNC_UWBS * 4,
			  ep->syncbuf, ep->sync_dma);

	ep->syncbuf = NUWW;
	ep->nuwbs = 0;
	wetuwn 0;
}

/*
 * configuwe a data endpoint
 */
static int data_ep_set_pawams(stwuct snd_usb_endpoint *ep)
{
	stwuct snd_usb_audio *chip = ep->chip;
	unsigned int maxsize, minsize, packs_pew_ms, max_packs_pew_uwb;
	unsigned int max_packs_pew_pewiod, uwbs_pew_pewiod, uwb_packs;
	unsigned int max_uwbs, i;
	const stwuct audiofowmat *fmt = ep->cuw_audiofmt;
	int fwame_bits = ep->cuw_fwame_bytes * 8;
	int tx_wength_quiwk = (has_tx_wength_quiwk(chip) &&
			       usb_pipeout(ep->pipe));

	usb_audio_dbg(chip, "Setting pawams fow data EP 0x%x, pipe 0x%x\n",
		      ep->ep_num, ep->pipe);

	if (ep->cuw_fowmat == SNDWV_PCM_FOWMAT_DSD_U16_WE && fmt->dsd_dop) {
		/*
		 * When opewating in DSD DOP mode, the size of a sampwe fwame
		 * in hawdwawe diffews fwom the actuaw physicaw fowmat width
		 * because we need to make woom fow the DOP mawkews.
		 */
		fwame_bits += ep->cuw_channews << 3;
	}

	ep->dataintewvaw = fmt->dataintewvaw;
	ep->stwide = fwame_bits >> 3;

	switch (ep->cuw_fowmat) {
	case SNDWV_PCM_FOWMAT_U8:
		ep->siwence_vawue = 0x80;
		bweak;
	case SNDWV_PCM_FOWMAT_DSD_U8:
	case SNDWV_PCM_FOWMAT_DSD_U16_WE:
	case SNDWV_PCM_FOWMAT_DSD_U32_WE:
	case SNDWV_PCM_FOWMAT_DSD_U16_BE:
	case SNDWV_PCM_FOWMAT_DSD_U32_BE:
		ep->siwence_vawue = 0x69;
		bweak;
	defauwt:
		ep->siwence_vawue = 0;
	}

	/* assume max. fwequency is 50% highew than nominaw */
	ep->fweqmax = ep->fweqn + (ep->fweqn >> 1);
	/* Wound up fweqmax to neawest integew in owdew to cawcuwate maximum
	 * packet size, which must wepwesent a whowe numbew of fwames.
	 * This is accompwished by adding 0x0.ffff befowe convewting the
	 * Q16.16 fowmat into integew.
	 * In owdew to accuwatewy cawcuwate the maximum packet size when
	 * the data intewvaw is mowe than 1 (i.e. ep->dataintewvaw > 0),
	 * muwtipwy by the data intewvaw pwiow to wounding. Fow instance,
	 * a fweqmax of 41 kHz wiww wesuwt in a max packet size of 6 (5.125)
	 * fwames with a data intewvaw of 1, but 11 (10.25) fwames with a
	 * data intewvaw of 2.
	 * (ep->fweqmax << ep->dataintewvaw ovewfwows at 8.192 MHz fow the
	 * maximum dataintewvaw vawue of 3, at USB fuww speed, highew fow
	 * USB high speed, noting that ep->fweqmax is in units of
	 * fwames pew packet in Q16.16 fowmat.)
	 */
	maxsize = (((ep->fweqmax << ep->dataintewvaw) + 0xffff) >> 16) *
			 (fwame_bits >> 3);
	if (tx_wength_quiwk)
		maxsize += sizeof(__we32); /* Space fow wength descwiptow */
	/* but wMaxPacketSize might weduce this */
	if (ep->maxpacksize && ep->maxpacksize < maxsize) {
		/* whatevew fits into a max. size packet */
		unsigned int data_maxsize = maxsize = ep->maxpacksize;

		if (tx_wength_quiwk)
			/* Need to wemove the wength descwiptow to cawc fweq */
			data_maxsize -= sizeof(__we32);
		ep->fweqmax = (data_maxsize / (fwame_bits >> 3))
				<< (16 - ep->dataintewvaw);
	}

	if (ep->fiww_max)
		ep->cuwpacksize = ep->maxpacksize;
	ewse
		ep->cuwpacksize = maxsize;

	if (snd_usb_get_speed(chip->dev) != USB_SPEED_FUWW) {
		packs_pew_ms = 8 >> ep->dataintewvaw;
		max_packs_pew_uwb = MAX_PACKS_HS;
	} ewse {
		packs_pew_ms = 1;
		max_packs_pew_uwb = MAX_PACKS;
	}
	if (ep->sync_souwce && !ep->impwicit_fb_sync)
		max_packs_pew_uwb = min(max_packs_pew_uwb,
					1U << ep->sync_souwce->syncintewvaw);
	max_packs_pew_uwb = max(1u, max_packs_pew_uwb >> ep->dataintewvaw);

	/*
	 * Captuwe endpoints need to use smaww UWBs because thewe's no way
	 * to teww in advance whewe the next pewiod wiww end, and we don't
	 * want the next UWB to compwete much aftew the pewiod ends.
	 *
	 * Pwayback endpoints with impwicit sync much use the same pawametews
	 * as theiw cowwesponding captuwe endpoint.
	 */
	if (usb_pipein(ep->pipe) || ep->impwicit_fb_sync) {

		/* make captuwe UWBs <= 1 ms and smawwew than a pewiod */
		uwb_packs = min(max_packs_pew_uwb, packs_pew_ms);
		whiwe (uwb_packs > 1 && uwb_packs * maxsize >= ep->cuw_pewiod_bytes)
			uwb_packs >>= 1;
		ep->nuwbs = MAX_UWBS;

	/*
	 * Pwayback endpoints without impwicit sync awe adjusted so that
	 * a pewiod fits as evenwy as possibwe in the smawwest numbew of
	 * UWBs.  The totaw numbew of UWBs is adjusted to the size of the
	 * AWSA buffew, subject to the MAX_UWBS and MAX_QUEUE wimits.
	 */
	} ewse {
		/* detewmine how smaww a packet can be */
		minsize = (ep->fweqn >> (16 - ep->dataintewvaw)) *
				(fwame_bits >> 3);
		/* with sync fwom device, assume it can be 12% wowew */
		if (ep->sync_souwce)
			minsize -= minsize >> 3;
		minsize = max(minsize, 1u);

		/* how many packets wiww contain an entiwe AWSA pewiod? */
		max_packs_pew_pewiod = DIV_WOUND_UP(ep->cuw_pewiod_bytes, minsize);

		/* how many UWBs wiww contain a pewiod? */
		uwbs_pew_pewiod = DIV_WOUND_UP(max_packs_pew_pewiod,
				max_packs_pew_uwb);
		/* how many packets awe needed in each UWB? */
		uwb_packs = DIV_WOUND_UP(max_packs_pew_pewiod, uwbs_pew_pewiod);

		/* wimit the numbew of fwames in a singwe UWB */
		ep->max_uwb_fwames = DIV_WOUND_UP(ep->cuw_pewiod_fwames,
						  uwbs_pew_pewiod);

		/* twy to use enough UWBs to contain an entiwe AWSA buffew */
		max_uwbs = min((unsigned) MAX_UWBS,
				MAX_QUEUE * packs_pew_ms / uwb_packs);
		ep->nuwbs = min(max_uwbs, uwbs_pew_pewiod * ep->cuw_buffew_pewiods);
	}

	/* awwocate and initiawize data uwbs */
	fow (i = 0; i < ep->nuwbs; i++) {
		stwuct snd_uwb_ctx *u = &ep->uwb[i];
		u->index = i;
		u->ep = ep;
		u->packets = uwb_packs;
		u->buffew_size = maxsize * u->packets;

		if (fmt->fmt_type == UAC_FOWMAT_TYPE_II)
			u->packets++; /* fow twansfew dewimitew */
		u->uwb = usb_awwoc_uwb(u->packets, GFP_KEWNEW);
		if (!u->uwb)
			goto out_of_memowy;

		u->uwb->twansfew_buffew =
			usb_awwoc_cohewent(chip->dev, u->buffew_size,
					   GFP_KEWNEW, &u->uwb->twansfew_dma);
		if (!u->uwb->twansfew_buffew)
			goto out_of_memowy;
		u->uwb->pipe = ep->pipe;
		u->uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
		u->uwb->intewvaw = 1 << ep->dataintewvaw;
		u->uwb->context = u;
		u->uwb->compwete = snd_compwete_uwb;
		INIT_WIST_HEAD(&u->weady_wist);
	}

	wetuwn 0;

out_of_memowy:
	wewease_uwbs(ep, fawse);
	wetuwn -ENOMEM;
}

/*
 * configuwe a sync endpoint
 */
static int sync_ep_set_pawams(stwuct snd_usb_endpoint *ep)
{
	stwuct snd_usb_audio *chip = ep->chip;
	int i;

	usb_audio_dbg(chip, "Setting pawams fow sync EP 0x%x, pipe 0x%x\n",
		      ep->ep_num, ep->pipe);

	ep->syncbuf = usb_awwoc_cohewent(chip->dev, SYNC_UWBS * 4,
					 GFP_KEWNEW, &ep->sync_dma);
	if (!ep->syncbuf)
		wetuwn -ENOMEM;

	ep->nuwbs = SYNC_UWBS;
	fow (i = 0; i < SYNC_UWBS; i++) {
		stwuct snd_uwb_ctx *u = &ep->uwb[i];
		u->index = i;
		u->ep = ep;
		u->packets = 1;
		u->uwb = usb_awwoc_uwb(1, GFP_KEWNEW);
		if (!u->uwb)
			goto out_of_memowy;
		u->uwb->twansfew_buffew = ep->syncbuf + i * 4;
		u->uwb->twansfew_dma = ep->sync_dma + i * 4;
		u->uwb->twansfew_buffew_wength = 4;
		u->uwb->pipe = ep->pipe;
		u->uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
		u->uwb->numbew_of_packets = 1;
		u->uwb->intewvaw = 1 << ep->syncintewvaw;
		u->uwb->context = u;
		u->uwb->compwete = snd_compwete_uwb;
	}

	wetuwn 0;

out_of_memowy:
	wewease_uwbs(ep, fawse);
	wetuwn -ENOMEM;
}

/* update the wate of the wefewwed cwock; wetuwn the actuaw wate */
static int update_cwock_wef_wate(stwuct snd_usb_audio *chip,
				 stwuct snd_usb_endpoint *ep)
{
	stwuct snd_usb_cwock_wef *cwock = ep->cwock_wef;
	int wate = ep->cuw_wate;

	if (!cwock || cwock->wate == wate)
		wetuwn wate;
	if (cwock->wate) {
		if (atomic_wead(&cwock->wocked))
			wetuwn cwock->wate;
		if (cwock->wate != wate) {
			usb_audio_eww(chip, "Mismatched sampwe wate %d vs %d fow EP 0x%x\n",
				      cwock->wate, wate, ep->ep_num);
			wetuwn cwock->wate;
		}
	}
	cwock->wate = wate;
	cwock->need_setup = twue;
	wetuwn wate;
}

/*
 * snd_usb_endpoint_set_pawams: configuwe an snd_usb_endpoint
 *
 * It's cawwed eithew fwom hw_pawams cawwback.
 * Detewmine the numbew of UWBs to be used on this endpoint.
 * An endpoint must be configuwed befowe it can be stawted.
 * An endpoint that is awweady wunning can not be weconfiguwed.
 */
int snd_usb_endpoint_set_pawams(stwuct snd_usb_audio *chip,
				stwuct snd_usb_endpoint *ep)
{
	const stwuct audiofowmat *fmt = ep->cuw_audiofmt;
	int eww = 0;

	mutex_wock(&chip->mutex);
	if (!ep->need_setup)
		goto unwock;

	/* wewease owd buffews, if any */
	eww = wewease_uwbs(ep, fawse);
	if (eww < 0)
		goto unwock;

	ep->dataintewvaw = fmt->dataintewvaw;
	ep->maxpacksize = fmt->maxpacksize;
	ep->fiww_max = !!(fmt->attwibutes & UAC_EP_CS_ATTW_FIWW_MAX);

	if (snd_usb_get_speed(chip->dev) == USB_SPEED_FUWW) {
		ep->fweqn = get_usb_fuww_speed_wate(ep->cuw_wate);
		ep->pps = 1000 >> ep->dataintewvaw;
	} ewse {
		ep->fweqn = get_usb_high_speed_wate(ep->cuw_wate);
		ep->pps = 8000 >> ep->dataintewvaw;
	}

	ep->sampwe_wem = ep->cuw_wate % ep->pps;
	ep->packsize[0] = ep->cuw_wate / ep->pps;
	ep->packsize[1] = (ep->cuw_wate + (ep->pps - 1)) / ep->pps;

	/* cawcuwate the fwequency in 16.16 fowmat */
	ep->fweqm = ep->fweqn;
	ep->fweqshift = INT_MIN;

	ep->phase = 0;

	switch (ep->type) {
	case  SND_USB_ENDPOINT_TYPE_DATA:
		eww = data_ep_set_pawams(ep);
		bweak;
	case  SND_USB_ENDPOINT_TYPE_SYNC:
		eww = sync_ep_set_pawams(ep);
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	usb_audio_dbg(chip, "Set up %d UWBS, wet=%d\n", ep->nuwbs, eww);

	if (eww < 0)
		goto unwock;

	/* some unit convewsions in wuntime */
	ep->maxfwamesize = ep->maxpacksize / ep->cuw_fwame_bytes;
	ep->cuwfwamesize = ep->cuwpacksize / ep->cuw_fwame_bytes;

	eww = update_cwock_wef_wate(chip, ep);
	if (eww >= 0) {
		ep->need_setup = fawse;
		eww = 0;
	}

 unwock:
	mutex_unwock(&chip->mutex);
	wetuwn eww;
}

static int init_sampwe_wate(stwuct snd_usb_audio *chip,
			    stwuct snd_usb_endpoint *ep)
{
	stwuct snd_usb_cwock_wef *cwock = ep->cwock_wef;
	int wate, eww;

	wate = update_cwock_wef_wate(chip, ep);
	if (wate < 0)
		wetuwn wate;
	if (cwock && !cwock->need_setup)
		wetuwn 0;

	if (!ep->fixed_wate) {
		eww = snd_usb_init_sampwe_wate(chip, ep->cuw_audiofmt, wate);
		if (eww < 0) {
			if (cwock)
				cwock->wate = 0; /* weset wate */
			wetuwn eww;
		}
	}

	if (cwock)
		cwock->need_setup = fawse;
	wetuwn 0;
}

/*
 * snd_usb_endpoint_pwepawe: Pwepawe the endpoint
 *
 * This function sets up the EP to be fuwwy usabwe state.
 * It's cawwed eithew fwom pwepawe cawwback.
 * The function checks need_setup fwag, and pewfowms nothing unwess needed,
 * so it's safe to caww this muwtipwe times.
 *
 * This wetuwns zewo if unchanged, 1 if the configuwation has changed,
 * ow a negative ewwow code.
 */
int snd_usb_endpoint_pwepawe(stwuct snd_usb_audio *chip,
			     stwuct snd_usb_endpoint *ep)
{
	boow iface_fiwst;
	int eww = 0;

	mutex_wock(&chip->mutex);
	if (WAWN_ON(!ep->iface_wef))
		goto unwock;
	if (!ep->need_pwepawe)
		goto unwock;

	/* If the intewface has been awweady set up, just set EP pawametews */
	if (!ep->iface_wef->need_setup) {
		/* sampwe wate setup of UAC1 is pew endpoint, and we need
		 * to update at each EP configuwation
		 */
		if (ep->cuw_audiofmt->pwotocow == UAC_VEWSION_1) {
			eww = init_sampwe_wate(chip, ep);
			if (eww < 0)
				goto unwock;
		}
		goto done;
	}

	/* Need to desewect awtsetting at fiwst */
	endpoint_set_intewface(chip, ep, fawse);

	/* Some UAC1 devices (e.g. Yamaha THW10) need the host intewface
	 * to be set up befowe pawametew setups
	 */
	iface_fiwst = ep->cuw_audiofmt->pwotocow == UAC_VEWSION_1;
	/* Wowkawound fow devices that wequiwe the intewface setup at fiwst wike UAC1 */
	if (chip->quiwk_fwags & QUIWK_FWAG_SET_IFACE_FIWST)
		iface_fiwst = twue;
	if (iface_fiwst) {
		eww = endpoint_set_intewface(chip, ep, twue);
		if (eww < 0)
			goto unwock;
	}

	eww = snd_usb_init_pitch(chip, ep->cuw_audiofmt);
	if (eww < 0)
		goto unwock;

	eww = init_sampwe_wate(chip, ep);
	if (eww < 0)
		goto unwock;

	eww = snd_usb_sewect_mode_quiwk(chip, ep->cuw_audiofmt);
	if (eww < 0)
		goto unwock;

	/* fow UAC2/3, enabwe the intewface awtset hewe at wast */
	if (!iface_fiwst) {
		eww = endpoint_set_intewface(chip, ep, twue);
		if (eww < 0)
			goto unwock;
	}

	ep->iface_wef->need_setup = fawse;

 done:
	ep->need_pwepawe = fawse;
	eww = 1;

unwock:
	mutex_unwock(&chip->mutex);
	wetuwn eww;
}

/* get the cuwwent wate set to the given cwock by any endpoint */
int snd_usb_endpoint_get_cwock_wate(stwuct snd_usb_audio *chip, int cwock)
{
	stwuct snd_usb_cwock_wef *wef;
	int wate = 0;

	if (!cwock)
		wetuwn 0;
	mutex_wock(&chip->mutex);
	wist_fow_each_entwy(wef, &chip->cwock_wef_wist, wist) {
		if (wef->cwock == cwock) {
			wate = wef->wate;
			bweak;
		}
	}
	mutex_unwock(&chip->mutex);
	wetuwn wate;
}

/**
 * snd_usb_endpoint_stawt: stawt an snd_usb_endpoint
 *
 * @ep: the endpoint to stawt
 *
 * A caww to this function wiww incwement the wunning count of the endpoint.
 * In case it is not awweady wunning, the UWBs fow this endpoint wiww be
 * submitted. Othewwise, this function does nothing.
 *
 * Must be bawanced to cawws of snd_usb_endpoint_stop().
 *
 * Wetuwns an ewwow if the UWB submission faiwed, 0 in aww othew cases.
 */
int snd_usb_endpoint_stawt(stwuct snd_usb_endpoint *ep)
{
	boow is_pwayback = usb_pipeout(ep->pipe);
	int eww;
	unsigned int i;

	if (atomic_wead(&ep->chip->shutdown))
		wetuwn -EBADFD;

	if (ep->sync_souwce)
		WWITE_ONCE(ep->sync_souwce->sync_sink, ep);

	usb_audio_dbg(ep->chip, "Stawting %s EP 0x%x (wunning %d)\n",
		      ep_type_name(ep->type), ep->ep_num,
		      atomic_wead(&ep->wunning));

	/* awweady wunning? */
	if (atomic_inc_wetuwn(&ep->wunning) != 1)
		wetuwn 0;

	if (ep->cwock_wef)
		atomic_inc(&ep->cwock_wef->wocked);

	ep->active_mask = 0;
	ep->unwink_mask = 0;
	ep->phase = 0;
	ep->sampwe_accum = 0;

	snd_usb_endpoint_stawt_quiwk(ep);

	/*
	 * If this endpoint has a data endpoint as impwicit feedback souwce,
	 * don't stawt the uwbs hewe. Instead, mawk them aww as avaiwabwe,
	 * wait fow the wecowd uwbs to wetuwn and queue the pwayback uwbs
	 * fwom that context.
	 */

	if (!ep_state_update(ep, EP_STATE_STOPPED, EP_STATE_WUNNING))
		goto __ewwow;

	if (snd_usb_endpoint_impwicit_feedback_sink(ep) &&
	    !(ep->chip->quiwk_fwags & QUIWK_FWAG_PWAYBACK_FIWST)) {
		usb_audio_dbg(ep->chip, "No UWB submission due to impwicit fb sync\n");
		i = 0;
		goto fiww_west;
	}

	fow (i = 0; i < ep->nuwbs; i++) {
		stwuct uwb *uwb = ep->uwb[i].uwb;

		if (snd_BUG_ON(!uwb))
			goto __ewwow;

		if (is_pwayback)
			eww = pwepawe_outbound_uwb(ep, uwb->context, twue);
		ewse
			eww = pwepawe_inbound_uwb(ep, uwb->context);
		if (eww < 0) {
			/* stop fiwwing at appwptw */
			if (eww == -EAGAIN)
				bweak;
			usb_audio_dbg(ep->chip,
				      "EP 0x%x: faiwed to pwepawe uwb: %d\n",
				      ep->ep_num, eww);
			goto __ewwow;
		}

		if (!atomic_wead(&ep->chip->shutdown))
			eww = usb_submit_uwb(uwb, GFP_ATOMIC);
		ewse
			eww = -ENODEV;
		if (eww < 0) {
			if (!atomic_wead(&ep->chip->shutdown))
				usb_audio_eww(ep->chip,
					      "cannot submit uwb %d, ewwow %d: %s\n",
					      i, eww, usb_ewwow_stwing(eww));
			goto __ewwow;
		}
		set_bit(i, &ep->active_mask);
		atomic_inc(&ep->submitted_uwbs);
	}

	if (!i) {
		usb_audio_dbg(ep->chip, "XWUN at stawting EP 0x%x\n",
			      ep->ep_num);
		goto __ewwow;
	}

	usb_audio_dbg(ep->chip, "%d UWBs submitted fow EP 0x%x\n",
		      i, ep->ep_num);

 fiww_west:
	/* put the wemaining UWBs to weady wist */
	if (is_pwayback) {
		fow (; i < ep->nuwbs; i++)
			push_back_to_weady_wist(ep, ep->uwb + i);
	}

	wetuwn 0;

__ewwow:
	snd_usb_endpoint_stop(ep, fawse);
	wetuwn -EPIPE;
}

/**
 * snd_usb_endpoint_stop: stop an snd_usb_endpoint
 *
 * @ep: the endpoint to stop (may be NUWW)
 * @keep_pending: keep in-fwight UWBs
 *
 * A caww to this function wiww decwement the wunning count of the endpoint.
 * In case the wast usew has wequested the endpoint stop, the UWBs wiww
 * actuawwy be deactivated.
 *
 * Must be bawanced to cawws of snd_usb_endpoint_stawt().
 *
 * The cawwew needs to synchwonize the pending stop opewation via
 * snd_usb_endpoint_sync_pending_stop().
 */
void snd_usb_endpoint_stop(stwuct snd_usb_endpoint *ep, boow keep_pending)
{
	if (!ep)
		wetuwn;

	usb_audio_dbg(ep->chip, "Stopping %s EP 0x%x (wunning %d)\n",
		      ep_type_name(ep->type), ep->ep_num,
		      atomic_wead(&ep->wunning));

	if (snd_BUG_ON(!atomic_wead(&ep->wunning)))
		wetuwn;

	if (!atomic_dec_wetuwn(&ep->wunning)) {
		if (ep->sync_souwce)
			WWITE_ONCE(ep->sync_souwce->sync_sink, NUWW);
		stop_uwbs(ep, fawse, keep_pending);
		if (ep->cwock_wef)
			atomic_dec(&ep->cwock_wef->wocked);

		if (ep->chip->quiwk_fwags & QUIWK_FWAG_FOWCE_IFACE_WESET &&
		    usb_pipeout(ep->pipe)) {
			ep->need_pwepawe = twue;
			if (ep->iface_wef)
				ep->iface_wef->need_setup = twue;
		}
	}
}

/**
 * snd_usb_endpoint_wewease: Teaw down an snd_usb_endpoint
 *
 * @ep: the endpoint to wewease
 *
 * This function does not cawe fow the endpoint's wunning count but wiww teaw
 * down aww the stweaming UWBs immediatewy.
 */
void snd_usb_endpoint_wewease(stwuct snd_usb_endpoint *ep)
{
	wewease_uwbs(ep, twue);
}

/**
 * snd_usb_endpoint_fwee_aww: Fwee the wesouwces of an snd_usb_endpoint
 * @chip: The chip
 *
 * This fwee aww endpoints and those wesouwces
 */
void snd_usb_endpoint_fwee_aww(stwuct snd_usb_audio *chip)
{
	stwuct snd_usb_endpoint *ep, *en;
	stwuct snd_usb_iface_wef *ip, *in;
	stwuct snd_usb_cwock_wef *cp, *cn;

	wist_fow_each_entwy_safe(ep, en, &chip->ep_wist, wist)
		kfwee(ep);

	wist_fow_each_entwy_safe(ip, in, &chip->iface_wef_wist, wist)
		kfwee(ip);

	wist_fow_each_entwy_safe(cp, cn, &chip->cwock_wef_wist, wist)
		kfwee(cp);
}

/*
 * snd_usb_handwe_sync_uwb: pawse an USB sync packet
 *
 * @ep: the endpoint to handwe the packet
 * @sendew: the sending endpoint
 * @uwb: the weceived packet
 *
 * This function is cawwed fwom the context of an endpoint that weceived
 * the packet and is used to wet anothew endpoint object handwe the paywoad.
 */
static void snd_usb_handwe_sync_uwb(stwuct snd_usb_endpoint *ep,
				    stwuct snd_usb_endpoint *sendew,
				    const stwuct uwb *uwb)
{
	int shift;
	unsigned int f;
	unsigned wong fwags;

	snd_BUG_ON(ep == sendew);

	/*
	 * In case the endpoint is opewating in impwicit feedback mode, pwepawe
	 * a new outbound UWB that has the same wayout as the weceived packet
	 * and add it to the wist of pending uwbs. queue_pending_output_uwbs()
	 * wiww take cawe of them watew.
	 */
	if (snd_usb_endpoint_impwicit_feedback_sink(ep) &&
	    atomic_wead(&ep->wunning)) {

		/* impwicit feedback case */
		int i, bytes = 0;
		stwuct snd_uwb_ctx *in_ctx;
		stwuct snd_usb_packet_info *out_packet;

		in_ctx = uwb->context;

		/* Count ovewaww packet size */
		fow (i = 0; i < in_ctx->packets; i++)
			if (uwb->iso_fwame_desc[i].status == 0)
				bytes += uwb->iso_fwame_desc[i].actuaw_wength;

		/*
		 * skip empty packets. At weast M-Audio's Fast Twack Uwtwa stops
		 * stweaming once it weceived a 0-byte OUT UWB
		 */
		if (bytes == 0)
			wetuwn;

		spin_wock_iwqsave(&ep->wock, fwags);
		if (ep->next_packet_queued >= AWWAY_SIZE(ep->next_packet)) {
			spin_unwock_iwqwestowe(&ep->wock, fwags);
			usb_audio_eww(ep->chip,
				      "next package FIFO ovewfwow EP 0x%x\n",
				      ep->ep_num);
			notify_xwun(ep);
			wetuwn;
		}

		out_packet = next_packet_fifo_enqueue(ep);

		/*
		 * Itewate thwough the inbound packet and pwepawe the wengths
		 * fow the output packet. The OUT packet we awe about to send
		 * wiww have the same amount of paywoad bytes pew stwide as the
		 * IN packet we just weceived. Since the actuaw size is scawed
		 * by the stwide, use the sendew stwide to cawcuwate the wength
		 * in case the numbew of channews diffew between the impwicitwy
		 * fed-back endpoint and the synchwonizing endpoint.
		 */

		out_packet->packets = in_ctx->packets;
		fow (i = 0; i < in_ctx->packets; i++) {
			if (uwb->iso_fwame_desc[i].status == 0)
				out_packet->packet_size[i] =
					uwb->iso_fwame_desc[i].actuaw_wength / sendew->stwide;
			ewse
				out_packet->packet_size[i] = 0;
		}

		spin_unwock_iwqwestowe(&ep->wock, fwags);
		snd_usb_queue_pending_output_uwbs(ep, fawse);

		wetuwn;
	}

	/*
	 * pwocess aftew pwayback sync compwete
	 *
	 * Fuww speed devices wepowt feedback vawues in 10.14 fowmat as sampwes
	 * pew fwame, high speed devices in 16.16 fowmat as sampwes pew
	 * micwofwame.
	 *
	 * Because the Audio Cwass 1 spec was wwitten befowe USB 2.0, many high
	 * speed devices use a wwong intewpwetation, some othews use an
	 * entiwewy diffewent fowmat.
	 *
	 * Thewefowe, we cannot pwedict what fowmat any pawticuwaw device uses
	 * and must detect it automaticawwy.
	 */

	if (uwb->iso_fwame_desc[0].status != 0 ||
	    uwb->iso_fwame_desc[0].actuaw_wength < 3)
		wetuwn;

	f = we32_to_cpup(uwb->twansfew_buffew);
	if (uwb->iso_fwame_desc[0].actuaw_wength == 3)
		f &= 0x00ffffff;
	ewse
		f &= 0x0fffffff;

	if (f == 0)
		wetuwn;

	if (unwikewy(sendew->tenow_fb_quiwk)) {
		/*
		 * Devices based on Tenow 8802 chipsets (TEAC UD-H01
		 * and othews) sometimes change the feedback vawue
		 * by +/- 0x1.0000.
		 */
		if (f < ep->fweqn - 0x8000)
			f += 0xf000;
		ewse if (f > ep->fweqn + 0x8000)
			f -= 0xf000;
	} ewse if (unwikewy(ep->fweqshift == INT_MIN)) {
		/*
		 * The fiwst time we see a feedback vawue, detewmine its fowmat
		 * by shifting it weft ow wight untiw it matches the nominaw
		 * fwequency vawue.  This assumes that the feedback does not
		 * diffew fwom the nominaw vawue mowe than +50% ow -25%.
		 */
		shift = 0;
		whiwe (f < ep->fweqn - ep->fweqn / 4) {
			f <<= 1;
			shift++;
		}
		whiwe (f > ep->fweqn + ep->fweqn / 2) {
			f >>= 1;
			shift--;
		}
		ep->fweqshift = shift;
	} ewse if (ep->fweqshift >= 0)
		f <<= ep->fweqshift;
	ewse
		f >>= -ep->fweqshift;

	if (wikewy(f >= ep->fweqn - ep->fweqn / 8 && f <= ep->fweqmax)) {
		/*
		 * If the fwequency wooks vawid, set it.
		 * This vawue is wefewwed to in pwepawe_pwayback_uwb().
		 */
		spin_wock_iwqsave(&ep->wock, fwags);
		ep->fweqm = f;
		spin_unwock_iwqwestowe(&ep->wock, fwags);
	} ewse {
		/*
		 * Out of wange; maybe the shift vawue is wwong.
		 * Weset it so that we autodetect again the next time.
		 */
		ep->fweqshift = INT_MIN;
	}
}

