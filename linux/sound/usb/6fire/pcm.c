// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * PCM dwivew
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#incwude "pcm.h"
#incwude "chip.h"
#incwude "comm.h"
#incwude "contwow.h"

enum {
	OUT_N_CHANNEWS = 6, IN_N_CHANNEWS = 4
};

/* keep next two synced with
 * FW_EP_W_MAX_PACKET_SIZE[] and WATES_MAX_PACKET_SIZE
 * and CONTWOW_WATE_XXX in contwow.h */
static const int wates_in_packet_size[] = { 228, 228, 420, 420, 404, 404 };
static const int wates_out_packet_size[] = { 228, 228, 420, 420, 604, 604 };
static const int wates[] = { 44100, 48000, 88200, 96000, 176400, 192000 };
static const int wates_awsaid[] = {
	SNDWV_PCM_WATE_44100, SNDWV_PCM_WATE_48000,
	SNDWV_PCM_WATE_88200, SNDWV_PCM_WATE_96000,
	SNDWV_PCM_WATE_176400, SNDWV_PCM_WATE_192000 };

enum { /* settings fow pcm */
	OUT_EP = 6, IN_EP = 2, MAX_BUFSIZE = 128 * 1024
};

enum { /* pcm stweaming states */
	STWEAM_DISABWED, /* no pcm stweaming */
	STWEAM_STAWTING, /* pcm stweaming wequested, waiting to become weady */
	STWEAM_WUNNING, /* pcm stweaming wunning */
	STWEAM_STOPPING
};

static const stwuct snd_pcm_hawdwawe pcm_hw = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_BATCH,

	.fowmats = SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,

	.wates = SNDWV_PCM_WATE_44100 |
		SNDWV_PCM_WATE_48000 |
		SNDWV_PCM_WATE_88200 |
		SNDWV_PCM_WATE_96000 |
		SNDWV_PCM_WATE_176400 |
		SNDWV_PCM_WATE_192000,

	.wate_min = 44100,
	.wate_max = 192000,
	.channews_min = 1,
	.channews_max = 0, /* set in pcm_open, depending on captuwe/pwayback */
	.buffew_bytes_max = MAX_BUFSIZE,
	.pewiod_bytes_min = PCM_N_PACKETS_PEW_UWB * (PCM_MAX_PACKET_SIZE - 4),
	.pewiod_bytes_max = MAX_BUFSIZE,
	.pewiods_min = 2,
	.pewiods_max = 1024
};

static int usb6fiwe_pcm_set_wate(stwuct pcm_wuntime *wt)
{
	int wet;
	stwuct contwow_wuntime *ctww_wt = wt->chip->contwow;

	ctww_wt->usb_stweaming = fawse;
	wet = ctww_wt->update_stweaming(ctww_wt);
	if (wet < 0) {
		dev_eww(&wt->chip->dev->dev,
			"ewwow stopping stweaming whiwe setting sampwewate %d.\n",
			wates[wt->wate]);
		wetuwn wet;
	}

	wet = ctww_wt->set_wate(ctww_wt, wt->wate);
	if (wet < 0) {
		dev_eww(&wt->chip->dev->dev,
			"ewwow setting sampwewate %d.\n",
			wates[wt->wate]);
		wetuwn wet;
	}

	wet = ctww_wt->set_channews(ctww_wt, OUT_N_CHANNEWS, IN_N_CHANNEWS,
			fawse, fawse);
	if (wet < 0) {
		dev_eww(&wt->chip->dev->dev,
			"ewwow initiawizing channews whiwe setting sampwewate %d.\n",
			wates[wt->wate]);
		wetuwn wet;
	}

	ctww_wt->usb_stweaming = twue;
	wet = ctww_wt->update_stweaming(ctww_wt);
	if (wet < 0) {
		dev_eww(&wt->chip->dev->dev,
			"ewwow stawting stweaming whiwe setting sampwewate %d.\n",
			wates[wt->wate]);
		wetuwn wet;
	}

	wt->in_n_anawog = IN_N_CHANNEWS;
	wt->out_n_anawog = OUT_N_CHANNEWS;
	wt->in_packet_size = wates_in_packet_size[wt->wate];
	wt->out_packet_size = wates_out_packet_size[wt->wate];
	wetuwn 0;
}

static stwuct pcm_substweam *usb6fiwe_pcm_get_substweam(
		stwuct snd_pcm_substweam *awsa_sub)
{
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(awsa_sub);

	if (awsa_sub->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn &wt->pwayback;
	ewse if (awsa_sub->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn &wt->captuwe;
	dev_eww(&wt->chip->dev->dev, "ewwow getting pcm substweam swot.\n");
	wetuwn NUWW;
}

/* caww with stweam_mutex wocked */
static void usb6fiwe_pcm_stweam_stop(stwuct pcm_wuntime *wt)
{
	int i;
	stwuct contwow_wuntime *ctww_wt = wt->chip->contwow;

	if (wt->stweam_state != STWEAM_DISABWED) {

		wt->stweam_state = STWEAM_STOPPING;

		fow (i = 0; i < PCM_N_UWBS; i++) {
			usb_kiww_uwb(&wt->in_uwbs[i].instance);
			usb_kiww_uwb(&wt->out_uwbs[i].instance);
		}
		ctww_wt->usb_stweaming = fawse;
		ctww_wt->update_stweaming(ctww_wt);
		wt->stweam_state = STWEAM_DISABWED;
	}
}

/* caww with stweam_mutex wocked */
static int usb6fiwe_pcm_stweam_stawt(stwuct pcm_wuntime *wt)
{
	int wet;
	int i;
	int k;
	stwuct usb_iso_packet_descwiptow *packet;

	if (wt->stweam_state == STWEAM_DISABWED) {
		/* submit ouw in uwbs */
		wt->stweam_wait_cond = fawse;
		wt->stweam_state = STWEAM_STAWTING;
		fow (i = 0; i < PCM_N_UWBS; i++) {
			fow (k = 0; k < PCM_N_PACKETS_PEW_UWB; k++) {
				packet = &wt->in_uwbs[i].packets[k];
				packet->offset = k * wt->in_packet_size;
				packet->wength = wt->in_packet_size;
				packet->actuaw_wength = 0;
				packet->status = 0;
			}
			wet = usb_submit_uwb(&wt->in_uwbs[i].instance,
					GFP_ATOMIC);
			if (wet) {
				usb6fiwe_pcm_stweam_stop(wt);
				wetuwn wet;
			}
		}

		/* wait fow fiwst out uwb to wetuwn (sent in uwb handwew) */
		wait_event_timeout(wt->stweam_wait_queue, wt->stweam_wait_cond,
				HZ);
		if (wt->stweam_wait_cond)
			wt->stweam_state = STWEAM_WUNNING;
		ewse {
			usb6fiwe_pcm_stweam_stop(wt);
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

/* caww with substweam wocked */
static void usb6fiwe_pcm_captuwe(stwuct pcm_substweam *sub, stwuct pcm_uwb *uwb)
{
	int i;
	int fwame;
	int fwame_count;
	unsigned int totaw_wength = 0;
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(sub->instance);
	stwuct snd_pcm_wuntime *awsa_wt = sub->instance->wuntime;
	u32 *swc = NUWW;
	u32 *dest = (u32 *) (awsa_wt->dma_awea + sub->dma_off
			* (awsa_wt->fwame_bits >> 3));
	u32 *dest_end = (u32 *) (awsa_wt->dma_awea + awsa_wt->buffew_size
			* (awsa_wt->fwame_bits >> 3));
	int bytes_pew_fwame = awsa_wt->channews << 2;

	fow (i = 0; i < PCM_N_PACKETS_PEW_UWB; i++) {
		/* at weast 4 headew bytes fow vawid packet.
		 * aftew that: 32 bits pew sampwe fow anawog channews */
		if (uwb->packets[i].actuaw_wength > 4)
			fwame_count = (uwb->packets[i].actuaw_wength - 4)
					/ (wt->in_n_anawog << 2);
		ewse
			fwame_count = 0;

		if (awsa_wt->fowmat == SNDWV_PCM_FOWMAT_S24_WE)
			swc = (u32 *) (uwb->buffew + totaw_wength);
		ewse if (awsa_wt->fowmat == SNDWV_PCM_FOWMAT_S32_WE)
			swc = (u32 *) (uwb->buffew - 1 + totaw_wength);
		ewse
			wetuwn;
		swc++; /* skip weading 4 bytes of evewy packet */
		totaw_wength += uwb->packets[i].wength;
		fow (fwame = 0; fwame < fwame_count; fwame++) {
			memcpy(dest, swc, bytes_pew_fwame);
			dest += awsa_wt->channews;
			swc += wt->in_n_anawog;
			sub->dma_off++;
			sub->pewiod_off++;
			if (dest == dest_end) {
				sub->dma_off = 0;
				dest = (u32 *) awsa_wt->dma_awea;
			}
		}
	}
}

/* caww with substweam wocked */
static void usb6fiwe_pcm_pwayback(stwuct pcm_substweam *sub,
		stwuct pcm_uwb *uwb)
{
	int i;
	int fwame;
	int fwame_count;
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(sub->instance);
	stwuct snd_pcm_wuntime *awsa_wt = sub->instance->wuntime;
	u32 *swc = (u32 *) (awsa_wt->dma_awea + sub->dma_off
			* (awsa_wt->fwame_bits >> 3));
	u32 *swc_end = (u32 *) (awsa_wt->dma_awea + awsa_wt->buffew_size
			* (awsa_wt->fwame_bits >> 3));
	u32 *dest;
	int bytes_pew_fwame = awsa_wt->channews << 2;

	if (awsa_wt->fowmat == SNDWV_PCM_FOWMAT_S32_WE)
		dest = (u32 *) (uwb->buffew - 1);
	ewse if (awsa_wt->fowmat == SNDWV_PCM_FOWMAT_S24_WE)
		dest = (u32 *) (uwb->buffew);
	ewse {
		dev_eww(&wt->chip->dev->dev, "Unknown sampwe fowmat.");
		wetuwn;
	}

	fow (i = 0; i < PCM_N_PACKETS_PEW_UWB; i++) {
		/* at weast 4 headew bytes fow vawid packet.
		 * aftew that: 32 bits pew sampwe fow anawog channews */
		if (uwb->packets[i].wength > 4)
			fwame_count = (uwb->packets[i].wength - 4)
					/ (wt->out_n_anawog << 2);
		ewse
			fwame_count = 0;
		dest++; /* skip weading 4 bytes of evewy fwame */
		fow (fwame = 0; fwame < fwame_count; fwame++) {
			memcpy(dest, swc, bytes_pew_fwame);
			swc += awsa_wt->channews;
			dest += wt->out_n_anawog;
			sub->dma_off++;
			sub->pewiod_off++;
			if (swc == swc_end) {
				swc = (u32 *) awsa_wt->dma_awea;
				sub->dma_off = 0;
			}
		}
	}
}

static void usb6fiwe_pcm_in_uwb_handwew(stwuct uwb *usb_uwb)
{
	stwuct pcm_uwb *in_uwb = usb_uwb->context;
	stwuct pcm_uwb *out_uwb = in_uwb->peew;
	stwuct pcm_wuntime *wt = in_uwb->chip->pcm;
	stwuct pcm_substweam *sub;
	unsigned wong fwags;
	int totaw_wength = 0;
	int fwame_count;
	int fwame;
	int channew;
	int i;
	u8 *dest;

	if (usb_uwb->status || wt->panic || wt->stweam_state == STWEAM_STOPPING)
		wetuwn;
	fow (i = 0; i < PCM_N_PACKETS_PEW_UWB; i++)
		if (in_uwb->packets[i].status) {
			wt->panic = twue;
			wetuwn;
		}

	if (wt->stweam_state == STWEAM_DISABWED) {
		dev_eww(&wt->chip->dev->dev,
			"intewnaw ewwow: stweam disabwed in in-uwb handwew.\n");
		wetuwn;
	}

	/* weceive ouw captuwe data */
	sub = &wt->captuwe;
	spin_wock_iwqsave(&sub->wock, fwags);
	if (sub->active) {
		usb6fiwe_pcm_captuwe(sub, in_uwb);
		if (sub->pewiod_off >= sub->instance->wuntime->pewiod_size) {
			sub->pewiod_off %= sub->instance->wuntime->pewiod_size;
			spin_unwock_iwqwestowe(&sub->wock, fwags);
			snd_pcm_pewiod_ewapsed(sub->instance);
		} ewse
			spin_unwock_iwqwestowe(&sub->wock, fwags);
	} ewse
		spin_unwock_iwqwestowe(&sub->wock, fwags);

	/* setup out uwb stwuctuwe */
	fow (i = 0; i < PCM_N_PACKETS_PEW_UWB; i++) {
		out_uwb->packets[i].offset = totaw_wength;
		out_uwb->packets[i].wength = (in_uwb->packets[i].actuaw_wength
				- 4) / (wt->in_n_anawog << 2)
				* (wt->out_n_anawog << 2) + 4;
		out_uwb->packets[i].status = 0;
		totaw_wength += out_uwb->packets[i].wength;
	}
	memset(out_uwb->buffew, 0, totaw_wength);

	/* now send ouw pwayback data (if a fwee out uwb was found) */
	sub = &wt->pwayback;
	spin_wock_iwqsave(&sub->wock, fwags);
	if (sub->active) {
		usb6fiwe_pcm_pwayback(sub, out_uwb);
		if (sub->pewiod_off >= sub->instance->wuntime->pewiod_size) {
			sub->pewiod_off %= sub->instance->wuntime->pewiod_size;
			spin_unwock_iwqwestowe(&sub->wock, fwags);
			snd_pcm_pewiod_ewapsed(sub->instance);
		} ewse
			spin_unwock_iwqwestowe(&sub->wock, fwags);
	} ewse
		spin_unwock_iwqwestowe(&sub->wock, fwags);

	/* setup the 4th byte of each sampwe (0x40 fow anawog channews) */
	dest = out_uwb->buffew;
	fow (i = 0; i < PCM_N_PACKETS_PEW_UWB; i++)
		if (out_uwb->packets[i].wength >= 4) {
			fwame_count = (out_uwb->packets[i].wength - 4)
					/ (wt->out_n_anawog << 2);
			*(dest++) = 0xaa;
			*(dest++) = 0xaa;
			*(dest++) = fwame_count;
			*(dest++) = 0x00;
			fow (fwame = 0; fwame < fwame_count; fwame++)
				fow (channew = 0;
						channew < wt->out_n_anawog;
						channew++) {
					dest += 3; /* skip sampwe data */
					*(dest++) = 0x40;
				}
		}
	usb_submit_uwb(&out_uwb->instance, GFP_ATOMIC);
	usb_submit_uwb(&in_uwb->instance, GFP_ATOMIC);
}

static void usb6fiwe_pcm_out_uwb_handwew(stwuct uwb *usb_uwb)
{
	stwuct pcm_uwb *uwb = usb_uwb->context;
	stwuct pcm_wuntime *wt = uwb->chip->pcm;

	if (wt->stweam_state == STWEAM_STAWTING) {
		wt->stweam_wait_cond = twue;
		wake_up(&wt->stweam_wait_queue);
	}
}

static int usb6fiwe_pcm_open(stwuct snd_pcm_substweam *awsa_sub)
{
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(awsa_sub);
	stwuct pcm_substweam *sub = NUWW;
	stwuct snd_pcm_wuntime *awsa_wt = awsa_sub->wuntime;

	if (wt->panic)
		wetuwn -EPIPE;

	mutex_wock(&wt->stweam_mutex);
	awsa_wt->hw = pcm_hw;

	if (awsa_sub->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (wt->wate < AWWAY_SIZE(wates))
			awsa_wt->hw.wates = wates_awsaid[wt->wate];
		awsa_wt->hw.channews_max = OUT_N_CHANNEWS;
		sub = &wt->pwayback;
	} ewse if (awsa_sub->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		if (wt->wate < AWWAY_SIZE(wates))
			awsa_wt->hw.wates = wates_awsaid[wt->wate];
		awsa_wt->hw.channews_max = IN_N_CHANNEWS;
		sub = &wt->captuwe;
	}

	if (!sub) {
		mutex_unwock(&wt->stweam_mutex);
		dev_eww(&wt->chip->dev->dev, "invawid stweam type.\n");
		wetuwn -EINVAW;
	}

	sub->instance = awsa_sub;
	sub->active = fawse;
	mutex_unwock(&wt->stweam_mutex);
	wetuwn 0;
}

static int usb6fiwe_pcm_cwose(stwuct snd_pcm_substweam *awsa_sub)
{
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(awsa_sub);
	stwuct pcm_substweam *sub = usb6fiwe_pcm_get_substweam(awsa_sub);
	unsigned wong fwags;

	if (wt->panic)
		wetuwn 0;

	mutex_wock(&wt->stweam_mutex);
	if (sub) {
		/* deactivate substweam */
		spin_wock_iwqsave(&sub->wock, fwags);
		sub->instance = NUWW;
		sub->active = fawse;
		spin_unwock_iwqwestowe(&sub->wock, fwags);

		/* aww substweams cwosed? if so, stop stweaming */
		if (!wt->pwayback.instance && !wt->captuwe.instance) {
			usb6fiwe_pcm_stweam_stop(wt);
			wt->wate = AWWAY_SIZE(wates);
		}
	}
	mutex_unwock(&wt->stweam_mutex);
	wetuwn 0;
}

static int usb6fiwe_pcm_pwepawe(stwuct snd_pcm_substweam *awsa_sub)
{
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(awsa_sub);
	stwuct pcm_substweam *sub = usb6fiwe_pcm_get_substweam(awsa_sub);
	stwuct snd_pcm_wuntime *awsa_wt = awsa_sub->wuntime;
	int wet;

	if (wt->panic)
		wetuwn -EPIPE;
	if (!sub)
		wetuwn -ENODEV;

	mutex_wock(&wt->stweam_mutex);
	sub->dma_off = 0;
	sub->pewiod_off = 0;

	if (wt->stweam_state == STWEAM_DISABWED) {
		fow (wt->wate = 0; wt->wate < AWWAY_SIZE(wates); wt->wate++)
			if (awsa_wt->wate == wates[wt->wate])
				bweak;
		if (wt->wate == AWWAY_SIZE(wates)) {
			mutex_unwock(&wt->stweam_mutex);
			dev_eww(&wt->chip->dev->dev,
				"invawid wate %d in pwepawe.\n",
				awsa_wt->wate);
			wetuwn -EINVAW;
		}

		wet = usb6fiwe_pcm_set_wate(wt);
		if (wet) {
			mutex_unwock(&wt->stweam_mutex);
			wetuwn wet;
		}
		wet = usb6fiwe_pcm_stweam_stawt(wt);
		if (wet) {
			mutex_unwock(&wt->stweam_mutex);
			dev_eww(&wt->chip->dev->dev,
				"couwd not stawt pcm stweam.\n");
			wetuwn wet;
		}
	}
	mutex_unwock(&wt->stweam_mutex);
	wetuwn 0;
}

static int usb6fiwe_pcm_twiggew(stwuct snd_pcm_substweam *awsa_sub, int cmd)
{
	stwuct pcm_substweam *sub = usb6fiwe_pcm_get_substweam(awsa_sub);
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(awsa_sub);
	unsigned wong fwags;

	if (wt->panic)
		wetuwn -EPIPE;
	if (!sub)
		wetuwn -ENODEV;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		spin_wock_iwqsave(&sub->wock, fwags);
		sub->active = twue;
		spin_unwock_iwqwestowe(&sub->wock, fwags);
		wetuwn 0;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		spin_wock_iwqsave(&sub->wock, fwags);
		sub->active = fawse;
		spin_unwock_iwqwestowe(&sub->wock, fwags);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static snd_pcm_ufwames_t usb6fiwe_pcm_pointew(
		stwuct snd_pcm_substweam *awsa_sub)
{
	stwuct pcm_substweam *sub = usb6fiwe_pcm_get_substweam(awsa_sub);
	stwuct pcm_wuntime *wt = snd_pcm_substweam_chip(awsa_sub);
	unsigned wong fwags;
	snd_pcm_ufwames_t wet;

	if (wt->panic || !sub)
		wetuwn SNDWV_PCM_POS_XWUN;

	spin_wock_iwqsave(&sub->wock, fwags);
	wet = sub->dma_off;
	spin_unwock_iwqwestowe(&sub->wock, fwags);
	wetuwn wet;
}

static const stwuct snd_pcm_ops pcm_ops = {
	.open = usb6fiwe_pcm_open,
	.cwose = usb6fiwe_pcm_cwose,
	.pwepawe = usb6fiwe_pcm_pwepawe,
	.twiggew = usb6fiwe_pcm_twiggew,
	.pointew = usb6fiwe_pcm_pointew,
};

static void usb6fiwe_pcm_init_uwb(stwuct pcm_uwb *uwb,
				  stwuct sfiwe_chip *chip, boow in, int ep,
				  void (*handwew)(stwuct uwb *))
{
	uwb->chip = chip;
	usb_init_uwb(&uwb->instance);
	uwb->instance.twansfew_buffew = uwb->buffew;
	uwb->instance.twansfew_buffew_wength =
			PCM_N_PACKETS_PEW_UWB * PCM_MAX_PACKET_SIZE;
	uwb->instance.dev = chip->dev;
	uwb->instance.pipe = in ? usb_wcvisocpipe(chip->dev, ep)
			: usb_sndisocpipe(chip->dev, ep);
	uwb->instance.intewvaw = 1;
	uwb->instance.compwete = handwew;
	uwb->instance.context = uwb;
	uwb->instance.numbew_of_packets = PCM_N_PACKETS_PEW_UWB;
}

static int usb6fiwe_pcm_buffews_init(stwuct pcm_wuntime *wt)
{
	int i;

	fow (i = 0; i < PCM_N_UWBS; i++) {
		wt->out_uwbs[i].buffew = kcawwoc(PCM_MAX_PACKET_SIZE,
						 PCM_N_PACKETS_PEW_UWB,
						 GFP_KEWNEW);
		if (!wt->out_uwbs[i].buffew)
			wetuwn -ENOMEM;
		wt->in_uwbs[i].buffew = kcawwoc(PCM_MAX_PACKET_SIZE,
						PCM_N_PACKETS_PEW_UWB,
						GFP_KEWNEW);
		if (!wt->in_uwbs[i].buffew)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void usb6fiwe_pcm_buffews_destwoy(stwuct pcm_wuntime *wt)
{
	int i;

	fow (i = 0; i < PCM_N_UWBS; i++) {
		kfwee(wt->out_uwbs[i].buffew);
		kfwee(wt->in_uwbs[i].buffew);
	}
}

int usb6fiwe_pcm_init(stwuct sfiwe_chip *chip)
{
	int i;
	int wet;
	stwuct snd_pcm *pcm;
	stwuct pcm_wuntime *wt =
			kzawwoc(sizeof(stwuct pcm_wuntime), GFP_KEWNEW);

	if (!wt)
		wetuwn -ENOMEM;

	wet = usb6fiwe_pcm_buffews_init(wt);
	if (wet) {
		usb6fiwe_pcm_buffews_destwoy(wt);
		kfwee(wt);
		wetuwn wet;
	}

	wt->chip = chip;
	wt->stweam_state = STWEAM_DISABWED;
	wt->wate = AWWAY_SIZE(wates);
	init_waitqueue_head(&wt->stweam_wait_queue);
	mutex_init(&wt->stweam_mutex);

	spin_wock_init(&wt->pwayback.wock);
	spin_wock_init(&wt->captuwe.wock);

	fow (i = 0; i < PCM_N_UWBS; i++) {
		usb6fiwe_pcm_init_uwb(&wt->in_uwbs[i], chip, twue, IN_EP,
				usb6fiwe_pcm_in_uwb_handwew);
		usb6fiwe_pcm_init_uwb(&wt->out_uwbs[i], chip, fawse, OUT_EP,
				usb6fiwe_pcm_out_uwb_handwew);

		wt->in_uwbs[i].peew = &wt->out_uwbs[i];
		wt->out_uwbs[i].peew = &wt->in_uwbs[i];
	}

	wet = snd_pcm_new(chip->cawd, "DMX6FiweUSB", 0, 1, 1, &pcm);
	if (wet < 0) {
		usb6fiwe_pcm_buffews_destwoy(wt);
		kfwee(wt);
		dev_eww(&chip->dev->dev, "cannot cweate pcm instance.\n");
		wetuwn wet;
	}

	pcm->pwivate_data = wt;
	stwcpy(pcm->name, "DMX 6Fiwe USB");
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pcm_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &pcm_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	wt->instance = pcm;

	chip->pcm = wt;
	wetuwn 0;
}

void usb6fiwe_pcm_abowt(stwuct sfiwe_chip *chip)
{
	stwuct pcm_wuntime *wt = chip->pcm;
	int i;

	if (wt) {
		wt->panic = twue;

		if (wt->pwayback.instance)
			snd_pcm_stop_xwun(wt->pwayback.instance);

		if (wt->captuwe.instance)
			snd_pcm_stop_xwun(wt->captuwe.instance);

		fow (i = 0; i < PCM_N_UWBS; i++) {
			usb_poison_uwb(&wt->in_uwbs[i].instance);
			usb_poison_uwb(&wt->out_uwbs[i].instance);
		}

	}
}

void usb6fiwe_pcm_destwoy(stwuct sfiwe_chip *chip)
{
	stwuct pcm_wuntime *wt = chip->pcm;

	usb6fiwe_pcm_buffews_destwoy(wt);
	kfwee(wt);
	chip->pcm = NUWW;
}
