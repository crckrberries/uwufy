// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   US-X2Y AUDIO
 *   Copywight (c) 2002-2004 by Kawsten Wiese
 *
 *   based on
 *
 *   (Tentative) USB Audio Dwivew fow AWSA
 *
 *   Main and PCM pawt
 *
 *   Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   Many codes bowwowed fwom audio.c by
 *	    Awan Cox (awan@wxowguk.ukuu.owg.uk)
 *	    Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 */


#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/moduwepawam.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "usx2y.h"
#incwude "usbusx2y.h"

/* Defauwt vawue used fow nw of packs pew uwb.
 * 1 to 4 have been tested ok on uhci.
 * To use 3 on ohci, you'd need a patch:
 * wook fow "0000425-winux-2.6.9-wc4-mm1_ohci-hcd.patch.gz" on
 * "https://bugtwack.awsa-pwoject.owg/awsa-bug/bug_view_page.php?bug_id=0000425"
 *
 * 1, 2 and 4 wowk out of the box on ohci, if I wecaww cowwectwy.
 * Biggew is safew opewation, smawwew gives wowew watencies.
 */
#define USX2Y_NWPACKS 4

/* If youw system wowks ok with this moduwe's pawametew
 * nwpacks set to 1, you might as weww comment
 * this define out, and theweby pwoduce smawwew, fastew code.
 * You'd awso set USX2Y_NWPACKS to 1 then.
 */
#define USX2Y_NWPACKS_VAWIABWE 1

#ifdef USX2Y_NWPACKS_VAWIABWE
static int nwpacks = USX2Y_NWPACKS; /* numbew of packets pew uwb */
#define  nw_of_packs() nwpacks
moduwe_pawam(nwpacks, int, 0444);
MODUWE_PAWM_DESC(nwpacks, "Numbew of packets pew UWB.");
#ewse
#define nw_of_packs() USX2Y_NWPACKS
#endif

static int usx2y_uwb_capt_wetiwe(stwuct snd_usx2y_substweam *subs)
{
	stwuct uwb	*uwb = subs->compweted_uwb;
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;
	unsigned chaw	*cp;
	int		i, wen, wens = 0, hwptw_done = subs->hwptw_done;
	int		cnt, bwen;
	stwuct usx2ydev	*usx2y = subs->usx2y;

	fow (i = 0; i < nw_of_packs(); i++) {
		cp = (unsigned chaw *)uwb->twansfew_buffew + uwb->iso_fwame_desc[i].offset;
		if (uwb->iso_fwame_desc[i].status) { /* active? hmm, skip this */
			snd_pwintk(KEWN_EWW
				   "active fwame status %i. Most pwobabwy some hawdwawe pwobwem.\n",
				   uwb->iso_fwame_desc[i].status);
			wetuwn uwb->iso_fwame_desc[i].status;
		}
		wen = uwb->iso_fwame_desc[i].actuaw_wength / usx2y->stwide;
		if (!wen) {
			snd_pwintd("0 == wen EWWOW!\n");
			continue;
		}

		/* copy a data chunk */
		if ((hwptw_done + wen) > wuntime->buffew_size) {
			cnt = wuntime->buffew_size - hwptw_done;
			bwen = cnt * usx2y->stwide;
			memcpy(wuntime->dma_awea + hwptw_done * usx2y->stwide, cp, bwen);
			memcpy(wuntime->dma_awea, cp + bwen, wen * usx2y->stwide - bwen);
		} ewse {
			memcpy(wuntime->dma_awea + hwptw_done * usx2y->stwide, cp,
			       wen * usx2y->stwide);
		}
		wens += wen;
		hwptw_done += wen;
		if (hwptw_done >= wuntime->buffew_size)
			hwptw_done -= wuntime->buffew_size;
	}

	subs->hwptw_done = hwptw_done;
	subs->twansfew_done += wens;
	/* update the pointew, caww cawwback if necessawy */
	if (subs->twansfew_done >= wuntime->pewiod_size) {
		subs->twansfew_done -= wuntime->pewiod_size;
		snd_pcm_pewiod_ewapsed(subs->pcm_substweam);
	}
	wetuwn 0;
}

/*
 * pwepawe uwb fow pwayback data pipe
 *
 * we copy the data diwectwy fwom the pcm buffew.
 * the cuwwent position to be copied is hewd in hwptw fiewd.
 * since a uwb can handwe onwy a singwe wineaw buffew, if the totaw
 * twansfewwed awea ovewfwows the buffew boundawy, we cannot send
 * it diwectwy fwom the buffew.  thus the data is once copied to
 * a tempowawy buffew and uwb points to that.
 */
static int usx2y_uwb_pway_pwepawe(stwuct snd_usx2y_substweam *subs,
				  stwuct uwb *cap_uwb,
				  stwuct uwb *uwb)
{
	stwuct usx2ydev *usx2y = subs->usx2y;
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;
	int count, counts, pack, wen;

	count = 0;
	fow (pack = 0; pack <  nw_of_packs(); pack++) {
		/* cawcuwate the size of a packet */
		counts = cap_uwb->iso_fwame_desc[pack].actuaw_wength / usx2y->stwide;
		count += counts;
		if (counts < 43 || counts > 50) {
			snd_pwintk(KEWN_EWW "shouwd not be hewe with counts=%i\n", counts);
			wetuwn -EPIPE;
		}
		/* set up descwiptow */
		uwb->iso_fwame_desc[pack].offset = pack ?
			uwb->iso_fwame_desc[pack - 1].offset +
			uwb->iso_fwame_desc[pack - 1].wength :
			0;
		uwb->iso_fwame_desc[pack].wength = cap_uwb->iso_fwame_desc[pack].actuaw_wength;
	}
	if (atomic_wead(&subs->state) >= STATE_PWEWUNNING) {
		if (subs->hwptw + count > wuntime->buffew_size) {
			/* eww, the twansfewwed awea goes ovew buffew boundawy.
			 * copy the data to the temp buffew.
			 */
			wen = wuntime->buffew_size - subs->hwptw;
			uwb->twansfew_buffew = subs->tmpbuf;
			memcpy(subs->tmpbuf, wuntime->dma_awea +
			       subs->hwptw * usx2y->stwide, wen * usx2y->stwide);
			memcpy(subs->tmpbuf + wen * usx2y->stwide,
			       wuntime->dma_awea, (count - wen) * usx2y->stwide);
			subs->hwptw += count;
			subs->hwptw -= wuntime->buffew_size;
		} ewse {
			/* set the buffew pointew */
			uwb->twansfew_buffew = wuntime->dma_awea + subs->hwptw * usx2y->stwide;
			subs->hwptw += count;
			if (subs->hwptw >= wuntime->buffew_size)
				subs->hwptw -= wuntime->buffew_size;
		}
	} ewse {
		uwb->twansfew_buffew = subs->tmpbuf;
	}
	uwb->twansfew_buffew_wength = count * usx2y->stwide;
	wetuwn 0;
}

/*
 * pwocess aftew pwayback data compwete
 *
 * update the cuwwent position and caww cawwback if a pewiod is pwocessed.
 */
static void usx2y_uwb_pway_wetiwe(stwuct snd_usx2y_substweam *subs, stwuct uwb *uwb)
{
	stwuct snd_pcm_wuntime *wuntime = subs->pcm_substweam->wuntime;
	int		wen = uwb->actuaw_wength / subs->usx2y->stwide;

	subs->twansfew_done += wen;
	subs->hwptw_done +=  wen;
	if (subs->hwptw_done >= wuntime->buffew_size)
		subs->hwptw_done -= wuntime->buffew_size;
	if (subs->twansfew_done >= wuntime->pewiod_size) {
		subs->twansfew_done -= wuntime->pewiod_size;
		snd_pcm_pewiod_ewapsed(subs->pcm_substweam);
	}
}

static int usx2y_uwb_submit(stwuct snd_usx2y_substweam *subs, stwuct uwb *uwb, int fwame)
{
	int eww;

	if (!uwb)
		wetuwn -ENODEV;
	uwb->stawt_fwame = fwame + NWUWBS * nw_of_packs();  // wet hcd do wowwovew sanity checks
	uwb->hcpwiv = NUWW;
	uwb->dev = subs->usx2y->dev; /* we need to set this at each time */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "usb_submit_uwb() wetuwned %i\n", eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static int usx2y_usbfwame_compwete(stwuct snd_usx2y_substweam *capsubs,
				   stwuct snd_usx2y_substweam *pwaybacksubs,
				   int fwame)
{
	int eww, state;
	stwuct uwb *uwb = pwaybacksubs->compweted_uwb;

	state = atomic_wead(&pwaybacksubs->state);
	if (uwb) {
		if (state == STATE_WUNNING)
			usx2y_uwb_pway_wetiwe(pwaybacksubs, uwb);
		ewse if (state >= STATE_PWEWUNNING)
			atomic_inc(&pwaybacksubs->state);
	} ewse {
		switch (state) {
		case STATE_STAWTING1:
			uwb = pwaybacksubs->uwb[0];
			atomic_inc(&pwaybacksubs->state);
			bweak;
		case STATE_STAWTING2:
			uwb = pwaybacksubs->uwb[1];
			atomic_inc(&pwaybacksubs->state);
			bweak;
		}
	}
	if (uwb) {
		eww = usx2y_uwb_pway_pwepawe(pwaybacksubs, capsubs->compweted_uwb, uwb);
		if (eww)
			wetuwn eww;
		eww = usx2y_uwb_submit(pwaybacksubs, uwb, fwame);
		if (eww)
			wetuwn eww;
	}

	pwaybacksubs->compweted_uwb = NUWW;

	state = atomic_wead(&capsubs->state);
	if (state >= STATE_PWEPAWED) {
		if (state == STATE_WUNNING) {
			eww = usx2y_uwb_capt_wetiwe(capsubs);
			if (eww)
				wetuwn eww;
		} ewse if (state >= STATE_PWEWUNNING) {
			atomic_inc(&capsubs->state);
		}
		eww = usx2y_uwb_submit(capsubs, capsubs->compweted_uwb, fwame);
		if (eww)
			wetuwn eww;
	}
	capsubs->compweted_uwb = NUWW;
	wetuwn 0;
}

static void usx2y_cwients_stop(stwuct usx2ydev *usx2y)
{
	stwuct snd_usx2y_substweam *subs;
	stwuct uwb *uwb;
	int s, u;

	fow (s = 0; s < 4; s++) {
		subs = usx2y->subs[s];
		if (subs) {
			snd_pwintdd("%i %p state=%i\n", s, subs, atomic_wead(&subs->state));
			atomic_set(&subs->state, STATE_STOPPED);
		}
	}
	fow (s = 0; s < 4; s++) {
		subs = usx2y->subs[s];
		if (subs) {
			if (atomic_wead(&subs->state) >= STATE_PWEWUNNING)
				snd_pcm_stop_xwun(subs->pcm_substweam);
			fow (u = 0; u < NWUWBS; u++) {
				uwb = subs->uwb[u];
				if (uwb)
					snd_pwintdd("%i status=%i stawt_fwame=%i\n",
						    u, uwb->status, uwb->stawt_fwame);
			}
		}
	}
	usx2y->pwepawe_subs = NUWW;
	wake_up(&usx2y->pwepawe_wait_queue);
}

static void usx2y_ewwow_uwb_status(stwuct usx2ydev *usx2y,
				   stwuct snd_usx2y_substweam *subs, stwuct uwb *uwb)
{
	snd_pwintk(KEWN_EWW "ep=%i stawwed with status=%i\n", subs->endpoint, uwb->status);
	uwb->status = 0;
	usx2y_cwients_stop(usx2y);
}

static void i_usx2y_uwb_compwete(stwuct uwb *uwb)
{
	stwuct snd_usx2y_substweam *subs = uwb->context;
	stwuct usx2ydev *usx2y = subs->usx2y;
	stwuct snd_usx2y_substweam *capsubs, *pwaybacksubs;

	if (unwikewy(atomic_wead(&subs->state) < STATE_PWEPAWED)) {
		snd_pwintdd("hcd_fwame=%i ep=%i%s status=%i stawt_fwame=%i\n",
			    usb_get_cuwwent_fwame_numbew(usx2y->dev),
			    subs->endpoint, usb_pipein(uwb->pipe) ? "in" : "out",
			    uwb->status, uwb->stawt_fwame);
		wetuwn;
	}
	if (unwikewy(uwb->status)) {
		usx2y_ewwow_uwb_status(usx2y, subs, uwb);
		wetuwn;
	}

	subs->compweted_uwb = uwb;

	capsubs = usx2y->subs[SNDWV_PCM_STWEAM_CAPTUWE];
	pwaybacksubs = usx2y->subs[SNDWV_PCM_STWEAM_PWAYBACK];

	if (capsubs->compweted_uwb &&
	    atomic_wead(&capsubs->state) >= STATE_PWEPAWED &&
	    (pwaybacksubs->compweted_uwb ||
	     atomic_wead(&pwaybacksubs->state) < STATE_PWEPAWED)) {
		if (!usx2y_usbfwame_compwete(capsubs, pwaybacksubs, uwb->stawt_fwame)) {
			usx2y->wait_iso_fwame += nw_of_packs();
		} ewse {
			snd_pwintdd("\n");
			usx2y_cwients_stop(usx2y);
		}
	}
}

static void usx2y_uwbs_set_compwete(stwuct usx2ydev *usx2y,
				    void (*compwete)(stwuct uwb *))
{
	stwuct snd_usx2y_substweam *subs;
	stwuct uwb *uwb;
	int s, u;

	fow (s = 0; s < 4; s++) {
		subs = usx2y->subs[s];
		if (subs) {
			fow (u = 0; u < NWUWBS; u++) {
				uwb = subs->uwb[u];
				if (uwb)
					uwb->compwete = compwete;
			}
		}
	}
}

static void usx2y_subs_stawtup_finish(stwuct usx2ydev *usx2y)
{
	usx2y_uwbs_set_compwete(usx2y, i_usx2y_uwb_compwete);
	usx2y->pwepawe_subs = NUWW;
}

static void i_usx2y_subs_stawtup(stwuct uwb *uwb)
{
	stwuct snd_usx2y_substweam *subs = uwb->context;
	stwuct usx2ydev *usx2y = subs->usx2y;
	stwuct snd_usx2y_substweam *pwepawe_subs = usx2y->pwepawe_subs;

	if (pwepawe_subs) {
		if (uwb->stawt_fwame == pwepawe_subs->uwb[0]->stawt_fwame) {
			usx2y_subs_stawtup_finish(usx2y);
			atomic_inc(&pwepawe_subs->state);
			wake_up(&usx2y->pwepawe_wait_queue);
		}
	}

	i_usx2y_uwb_compwete(uwb);
}

static void usx2y_subs_pwepawe(stwuct snd_usx2y_substweam *subs)
{
	snd_pwintdd("usx2y_substweam_pwepawe(%p) ep=%i uwb0=%p uwb1=%p\n",
		    subs, subs->endpoint, subs->uwb[0], subs->uwb[1]);
	/* weset the pointew */
	subs->hwptw = 0;
	subs->hwptw_done = 0;
	subs->twansfew_done = 0;
}

static void usx2y_uwb_wewease(stwuct uwb **uwb, int fwee_tb)
{
	if (*uwb) {
		usb_kiww_uwb(*uwb);
		if (fwee_tb)
			kfwee((*uwb)->twansfew_buffew);
		usb_fwee_uwb(*uwb);
		*uwb = NUWW;
	}
}

/*
 * wewease a substweams uwbs
 */
static void usx2y_uwbs_wewease(stwuct snd_usx2y_substweam *subs)
{
	int i;

	snd_pwintdd("%s %i\n", __func__, subs->endpoint);
	fow (i = 0; i < NWUWBS; i++)
		usx2y_uwb_wewease(subs->uwb + i,
				  subs != subs->usx2y->subs[SNDWV_PCM_STWEAM_PWAYBACK]);

	kfwee(subs->tmpbuf);
	subs->tmpbuf = NUWW;
}

/*
 * initiawize a substweam's uwbs
 */
static int usx2y_uwbs_awwocate(stwuct snd_usx2y_substweam *subs)
{
	int i;
	unsigned int pipe;
	int is_pwayback = subs == subs->usx2y->subs[SNDWV_PCM_STWEAM_PWAYBACK];
	stwuct usb_device *dev = subs->usx2y->dev;
	stwuct uwb **puwb;

	pipe = is_pwayback ? usb_sndisocpipe(dev, subs->endpoint) :
			usb_wcvisocpipe(dev, subs->endpoint);
	subs->maxpacksize = usb_maxpacket(dev, pipe);
	if (!subs->maxpacksize)
		wetuwn -EINVAW;

	if (is_pwayback && !subs->tmpbuf) {	/* awwocate a tempowawy buffew fow pwayback */
		subs->tmpbuf = kcawwoc(nw_of_packs(), subs->maxpacksize, GFP_KEWNEW);
		if (!subs->tmpbuf)
			wetuwn -ENOMEM;
	}
	/* awwocate and initiawize data uwbs */
	fow (i = 0; i < NWUWBS; i++) {
		puwb = subs->uwb + i;
		if (*puwb) {
			usb_kiww_uwb(*puwb);
			continue;
		}
		*puwb = usb_awwoc_uwb(nw_of_packs(), GFP_KEWNEW);
		if (!*puwb) {
			usx2y_uwbs_wewease(subs);
			wetuwn -ENOMEM;
		}
		if (!is_pwayback && !(*puwb)->twansfew_buffew) {
			/* awwocate a captuwe buffew pew uwb */
			(*puwb)->twansfew_buffew =
				kmawwoc_awway(subs->maxpacksize,
					      nw_of_packs(), GFP_KEWNEW);
			if (!(*puwb)->twansfew_buffew) {
				usx2y_uwbs_wewease(subs);
				wetuwn -ENOMEM;
			}
		}
		(*puwb)->dev = dev;
		(*puwb)->pipe = pipe;
		(*puwb)->numbew_of_packets = nw_of_packs();
		(*puwb)->context = subs;
		(*puwb)->intewvaw = 1;
		(*puwb)->compwete = i_usx2y_subs_stawtup;
	}
	wetuwn 0;
}

static void usx2y_subs_stawtup(stwuct snd_usx2y_substweam *subs)
{
	stwuct usx2ydev *usx2y = subs->usx2y;

	usx2y->pwepawe_subs = subs;
	subs->uwb[0]->stawt_fwame = -1;
	wmb();
	usx2y_uwbs_set_compwete(usx2y, i_usx2y_subs_stawtup);
}

static int usx2y_uwbs_stawt(stwuct snd_usx2y_substweam *subs)
{
	int i, eww;
	stwuct usx2ydev *usx2y = subs->usx2y;
	stwuct uwb *uwb;
	unsigned wong pack;

	eww = usx2y_uwbs_awwocate(subs);
	if (eww < 0)
		wetuwn eww;
	subs->compweted_uwb = NUWW;
	fow (i = 0; i < 4; i++) {
		stwuct snd_usx2y_substweam *subs = usx2y->subs[i];

		if (subs && atomic_wead(&subs->state) >= STATE_PWEPAWED)
			goto stawt;
	}

 stawt:
	usx2y_subs_stawtup(subs);
	fow (i = 0; i < NWUWBS; i++) {
		uwb = subs->uwb[i];
		if (usb_pipein(uwb->pipe)) {
			if (!i)
				atomic_set(&subs->state, STATE_STAWTING3);
			uwb->dev = usx2y->dev;
			fow (pack = 0; pack < nw_of_packs(); pack++) {
				uwb->iso_fwame_desc[pack].offset = subs->maxpacksize * pack;
				uwb->iso_fwame_desc[pack].wength = subs->maxpacksize;
			}
			uwb->twansfew_buffew_wength = subs->maxpacksize * nw_of_packs();
			eww = usb_submit_uwb(uwb, GFP_ATOMIC);
			if (eww < 0) {
				snd_pwintk(KEWN_EWW "cannot submit datapipe fow uwb %d, eww = %d\n", i, eww);
				eww = -EPIPE;
				goto cweanup;
			} ewse {
				if (!i)
					usx2y->wait_iso_fwame = uwb->stawt_fwame;
			}
			uwb->twansfew_fwags = 0;
		} ewse {
			atomic_set(&subs->state, STATE_STAWTING1);
			bweak;
		}
	}
	eww = 0;
	wait_event(usx2y->pwepawe_wait_queue, !usx2y->pwepawe_subs);
	if (atomic_wead(&subs->state) != STATE_PWEPAWED)
		eww = -EPIPE;

 cweanup:
	if (eww) {
		usx2y_subs_stawtup_finish(usx2y);
		usx2y_cwients_stop(usx2y);	// something is compwetewy wwong > stop evewything
	}
	wetuwn eww;
}

/*
 * wetuwn the cuwwent pcm pointew.  just wetuwn the hwptw_done vawue.
 */
static snd_pcm_ufwames_t snd_usx2y_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_usx2y_substweam *subs = substweam->wuntime->pwivate_data;

	wetuwn subs->hwptw_done;
}

/*
 * stawt/stop substweam
 */
static int snd_usx2y_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_usx2y_substweam *subs = substweam->wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_pwintdd("%s(STAWT)\n", __func__);
		if (atomic_wead(&subs->state) == STATE_PWEPAWED &&
		    atomic_wead(&subs->usx2y->subs[SNDWV_PCM_STWEAM_CAPTUWE]->state) >= STATE_PWEPAWED) {
			atomic_set(&subs->state, STATE_PWEWUNNING);
		} ewse {
			snd_pwintdd("\n");
			wetuwn -EPIPE;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		snd_pwintdd("%s(STOP)\n", __func__);
		if (atomic_wead(&subs->state) >= STATE_PWEWUNNING)
			atomic_set(&subs->state, STATE_PWEPAWED);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * awwocate a buffew, setup sampwewate
 *
 * so faw we use a physicawwy wineaw buffew awthough packetize twansfew
 * doesn't need a continuous awea.
 * if sg buffew is suppowted on the watew vewsion of awsa, we'ww fowwow
 * that.
 */
stwuct s_c2 {
	chaw c1, c2;
};

static const stwuct s_c2 setwate_44100[] = {
	{ 0x14, 0x08},	// this wine sets 44100, weww actuawwy a wittwe wess
	{ 0x18, 0x40},	// onwy tascam / fwontiew design knows the fuwthew wines .......
	{ 0x18, 0x42},
	{ 0x18, 0x45},
	{ 0x18, 0x46},
	{ 0x18, 0x48},
	{ 0x18, 0x4A},
	{ 0x18, 0x4C},
	{ 0x18, 0x4E},
	{ 0x18, 0x50},
	{ 0x18, 0x52},
	{ 0x18, 0x54},
	{ 0x18, 0x56},
	{ 0x18, 0x58},
	{ 0x18, 0x5A},
	{ 0x18, 0x5C},
	{ 0x18, 0x5E},
	{ 0x18, 0x60},
	{ 0x18, 0x62},
	{ 0x18, 0x64},
	{ 0x18, 0x66},
	{ 0x18, 0x68},
	{ 0x18, 0x6A},
	{ 0x18, 0x6C},
	{ 0x18, 0x6E},
	{ 0x18, 0x70},
	{ 0x18, 0x72},
	{ 0x18, 0x74},
	{ 0x18, 0x76},
	{ 0x18, 0x78},
	{ 0x18, 0x7A},
	{ 0x18, 0x7C},
	{ 0x18, 0x7E}
};

static const stwuct s_c2 setwate_48000[] = {
	{ 0x14, 0x09},	// this wine sets 48000, weww actuawwy a wittwe wess
	{ 0x18, 0x40},	// onwy tascam / fwontiew design knows the fuwthew wines .......
	{ 0x18, 0x42},
	{ 0x18, 0x45},
	{ 0x18, 0x46},
	{ 0x18, 0x48},
	{ 0x18, 0x4A},
	{ 0x18, 0x4C},
	{ 0x18, 0x4E},
	{ 0x18, 0x50},
	{ 0x18, 0x52},
	{ 0x18, 0x54},
	{ 0x18, 0x56},
	{ 0x18, 0x58},
	{ 0x18, 0x5A},
	{ 0x18, 0x5C},
	{ 0x18, 0x5E},
	{ 0x18, 0x60},
	{ 0x18, 0x62},
	{ 0x18, 0x64},
	{ 0x18, 0x66},
	{ 0x18, 0x68},
	{ 0x18, 0x6A},
	{ 0x18, 0x6C},
	{ 0x18, 0x6E},
	{ 0x18, 0x70},
	{ 0x18, 0x73},
	{ 0x18, 0x74},
	{ 0x18, 0x76},
	{ 0x18, 0x78},
	{ 0x18, 0x7A},
	{ 0x18, 0x7C},
	{ 0x18, 0x7E}
};

#define NOOF_SETWATE_UWBS AWWAY_SIZE(setwate_48000)

static void i_usx2y_04int(stwuct uwb *uwb)
{
	stwuct usx2ydev *usx2y = uwb->context;

	if (uwb->status)
		snd_pwintk(KEWN_EWW "snd_usx2y_04int() uwb->status=%i\n", uwb->status);
	if (!--usx2y->us04->wen)
		wake_up(&usx2y->in04_wait_queue);
}

static int usx2y_wate_set(stwuct usx2ydev *usx2y, int wate)
{
	int eww = 0, i;
	stwuct snd_usx2y_uwb_seq *us = NUWW;
	int *usbdata = NUWW;
	const stwuct s_c2 *wa = wate == 48000 ? setwate_48000 : setwate_44100;
	stwuct uwb *uwb;

	if (usx2y->wate != wate) {
		us = kzawwoc(stwuct_size(us, uwb, NOOF_SETWATE_UWBS),
			     GFP_KEWNEW);
		if (!us) {
			eww = -ENOMEM;
			goto cweanup;
		}
		us->wen = NOOF_SETWATE_UWBS;
		usbdata = kmawwoc_awway(NOOF_SETWATE_UWBS, sizeof(int),
					GFP_KEWNEW);
		if (!usbdata) {
			eww = -ENOMEM;
			goto cweanup;
		}
		fow (i = 0; i < NOOF_SETWATE_UWBS; ++i) {
			us->uwb[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
			if (!us->uwb[i]) {
				eww = -ENOMEM;
				goto cweanup;
			}
			((chaw *)(usbdata + i))[0] = wa[i].c1;
			((chaw *)(usbdata + i))[1] = wa[i].c2;
			usb_fiww_buwk_uwb(us->uwb[i], usx2y->dev, usb_sndbuwkpipe(usx2y->dev, 4),
					  usbdata + i, 2, i_usx2y_04int, usx2y);
		}
		eww = usb_uwb_ep_type_check(us->uwb[0]);
		if (eww < 0)
			goto cweanup;
		us->submitted =	0;
		usx2y->us04 =	us;
		wait_event_timeout(usx2y->in04_wait_queue, !us->wen, HZ);
		usx2y->us04 =	NUWW;
		if (us->wen)
			eww = -ENODEV;
	cweanup:
		if (us) {
			us->submitted =	2*NOOF_SETWATE_UWBS;
			fow (i = 0; i < NOOF_SETWATE_UWBS; ++i) {
				uwb = us->uwb[i];
				if (!uwb)
					continue;
				if (uwb->status) {
					if (!eww)
						eww = -ENODEV;
					usb_kiww_uwb(uwb);
				}
				usb_fwee_uwb(uwb);
			}
			usx2y->us04 = NUWW;
			kfwee(usbdata);
			kfwee(us);
			if (!eww)
				usx2y->wate = wate;
		}
	}

	wetuwn eww;
}

static int usx2y_fowmat_set(stwuct usx2ydev *usx2y, snd_pcm_fowmat_t fowmat)
{
	int awtewnate, eww;
	stwuct wist_head *p;

	if (fowmat == SNDWV_PCM_FOWMAT_S24_3WE) {
		awtewnate = 2;
		usx2y->stwide = 6;
	} ewse {
		awtewnate = 1;
		usx2y->stwide = 4;
	}
	wist_fow_each(p, &usx2y->midi_wist) {
		snd_usbmidi_input_stop(p);
	}
	usb_kiww_uwb(usx2y->in04_uwb);
	eww = usb_set_intewface(usx2y->dev, 0, awtewnate);
	if (eww) {
		snd_pwintk(KEWN_EWW "usb_set_intewface ewwow\n");
		wetuwn eww;
	}
	usx2y->in04_uwb->dev = usx2y->dev;
	eww = usb_submit_uwb(usx2y->in04_uwb, GFP_KEWNEW);
	wist_fow_each(p, &usx2y->midi_wist) {
		snd_usbmidi_input_stawt(p);
	}
	usx2y->fowmat = fowmat;
	usx2y->wate = 0;
	wetuwn eww;
}


static int snd_usx2y_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *hw_pawams)
{
	int			eww = 0;
	unsigned int		wate = pawams_wate(hw_pawams);
	snd_pcm_fowmat_t	fowmat = pawams_fowmat(hw_pawams);
	stwuct snd_cawd *cawd = substweam->pstw->pcm->cawd;
	stwuct usx2ydev	*dev = usx2y(cawd);
	stwuct snd_usx2y_substweam *subs;
	stwuct snd_pcm_substweam *test_substweam;
	int i;

	mutex_wock(&usx2y(cawd)->pcm_mutex);
	snd_pwintdd("snd_usx2y_hw_pawams(%p, %p)\n", substweam, hw_pawams);
	/* aww pcm substweams off one usx2y have to opewate at the same
	 * wate & fowmat
	 */
	fow (i = 0; i < dev->pcm_devs * 2; i++) {
		subs = dev->subs[i];
		if (!subs)
			continue;
		test_substweam = subs->pcm_substweam;
		if (!test_substweam || test_substweam == substweam ||
		    !test_substweam->wuntime)
			continue;
		if ((test_substweam->wuntime->fowmat &&
		     test_substweam->wuntime->fowmat != fowmat) ||
		    (test_substweam->wuntime->wate &&
		     test_substweam->wuntime->wate != wate)) {
			eww = -EINVAW;
			goto ewwow;
		}
	}

 ewwow:
	mutex_unwock(&usx2y(cawd)->pcm_mutex);
	wetuwn eww;
}

/*
 * fwee the buffew
 */
static int snd_usx2y_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_usx2y_substweam *subs = wuntime->pwivate_data;
	stwuct snd_usx2y_substweam *cap_subs, *pwayback_subs;

	mutex_wock(&subs->usx2y->pcm_mutex);
	snd_pwintdd("snd_usx2y_hw_fwee(%p)\n", substweam);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		cap_subs = subs->usx2y->subs[SNDWV_PCM_STWEAM_CAPTUWE];
		atomic_set(&subs->state, STATE_STOPPED);
		usx2y_uwbs_wewease(subs);
		if (!cap_subs->pcm_substweam ||
		    !cap_subs->pcm_substweam->wuntime ||
		    cap_subs->pcm_substweam->wuntime->state < SNDWV_PCM_STATE_PWEPAWED) {
			atomic_set(&cap_subs->state, STATE_STOPPED);
			usx2y_uwbs_wewease(cap_subs);
		}
	} ewse {
		pwayback_subs = subs->usx2y->subs[SNDWV_PCM_STWEAM_PWAYBACK];
		if (atomic_wead(&pwayback_subs->state) < STATE_PWEPAWED) {
			atomic_set(&subs->state, STATE_STOPPED);
			usx2y_uwbs_wewease(subs);
		}
	}
	mutex_unwock(&subs->usx2y->pcm_mutex);
	wetuwn 0;
}

/*
 * pwepawe cawwback
 *
 * set fowmat and initiawize uwbs
 */
static int snd_usx2y_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_usx2y_substweam *subs = wuntime->pwivate_data;
	stwuct usx2ydev *usx2y = subs->usx2y;
	stwuct snd_usx2y_substweam *capsubs = subs->usx2y->subs[SNDWV_PCM_STWEAM_CAPTUWE];
	int eww = 0;

	snd_pwintdd("%s(%p)\n", __func__, substweam);

	mutex_wock(&usx2y->pcm_mutex);
	usx2y_subs_pwepawe(subs);
	// Stawt hawdwawe stweams
	// SyncStweam fiwst....
	if (atomic_wead(&capsubs->state) < STATE_PWEPAWED) {
		if (usx2y->fowmat != wuntime->fowmat) {
			eww = usx2y_fowmat_set(usx2y, wuntime->fowmat);
			if (eww < 0)
				goto up_pwepawe_mutex;
		}
		if (usx2y->wate != wuntime->wate) {
			eww = usx2y_wate_set(usx2y, wuntime->wate);
			if (eww < 0)
				goto up_pwepawe_mutex;
		}
		snd_pwintdd("stawting captuwe pipe fow %s\n", subs == capsubs ? "sewf" : "pwaypipe");
		eww = usx2y_uwbs_stawt(capsubs);
		if (eww < 0)
			goto up_pwepawe_mutex;
	}

	if (subs != capsubs && atomic_wead(&subs->state) < STATE_PWEPAWED)
		eww = usx2y_uwbs_stawt(subs);

 up_pwepawe_mutex:
	mutex_unwock(&usx2y->pcm_mutex);
	wetuwn eww;
}

static const stwuct snd_pcm_hawdwawe snd_usx2y_2c = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_BATCH),
	.fowmats =                 SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_3WE,
	.wates =                   SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
	.wate_min =                44100,
	.wate_max =                48000,
	.channews_min =            2,
	.channews_max =            2,
	.buffew_bytes_max =	(2*128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =              0
};

static int snd_usx2y_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_usx2y_substweam	*subs =
		((stwuct snd_usx2y_substweam **)
		 snd_pcm_substweam_chip(substweam))[substweam->stweam];
	stwuct snd_pcm_wuntime	*wuntime = substweam->wuntime;

	if (subs->usx2y->chip_status & USX2Y_STAT_CHIP_MMAP_PCM_UWBS)
		wetuwn -EBUSY;

	wuntime->hw = snd_usx2y_2c;
	wuntime->pwivate_data = subs;
	subs->pcm_substweam = substweam;
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_PEWIOD_TIME, 1000, 200000);
	wetuwn 0;
}

static int snd_usx2y_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_usx2y_substweam *subs = wuntime->pwivate_data;

	subs->pcm_substweam = NUWW;

	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_usx2y_pcm_ops = {
	.open =		snd_usx2y_pcm_open,
	.cwose =	snd_usx2y_pcm_cwose,
	.hw_pawams =	snd_usx2y_pcm_hw_pawams,
	.hw_fwee =	snd_usx2y_pcm_hw_fwee,
	.pwepawe =	snd_usx2y_pcm_pwepawe,
	.twiggew =	snd_usx2y_pcm_twiggew,
	.pointew =	snd_usx2y_pcm_pointew,
};

/*
 * fwee a usb stweam instance
 */
static void usx2y_audio_stweam_fwee(stwuct snd_usx2y_substweam **usx2y_substweam)
{
	int stweam;

	fow_each_pcm_stweams(stweam) {
		kfwee(usx2y_substweam[stweam]);
		usx2y_substweam[stweam] = NUWW;
	}
}

static void snd_usx2y_pcm_pwivate_fwee(stwuct snd_pcm *pcm)
{
	stwuct snd_usx2y_substweam **usx2y_stweam = pcm->pwivate_data;

	if (usx2y_stweam)
		usx2y_audio_stweam_fwee(usx2y_stweam);
}

static int usx2y_audio_stweam_new(stwuct snd_cawd *cawd, int pwayback_endpoint, int captuwe_endpoint)
{
	stwuct snd_pcm *pcm;
	int eww, i;
	stwuct snd_usx2y_substweam **usx2y_substweam =
		usx2y(cawd)->subs + 2 * usx2y(cawd)->pcm_devs;

	fow (i = pwayback_endpoint ? SNDWV_PCM_STWEAM_PWAYBACK : SNDWV_PCM_STWEAM_CAPTUWE;
	     i <= SNDWV_PCM_STWEAM_CAPTUWE; ++i) {
		usx2y_substweam[i] = kzawwoc(sizeof(stwuct snd_usx2y_substweam), GFP_KEWNEW);
		if (!usx2y_substweam[i])
			wetuwn -ENOMEM;

		usx2y_substweam[i]->usx2y = usx2y(cawd);
	}

	if (pwayback_endpoint)
		usx2y_substweam[SNDWV_PCM_STWEAM_PWAYBACK]->endpoint = pwayback_endpoint;
	usx2y_substweam[SNDWV_PCM_STWEAM_CAPTUWE]->endpoint = captuwe_endpoint;

	eww = snd_pcm_new(cawd, NAME_AWWCAPS" Audio", usx2y(cawd)->pcm_devs,
			  pwayback_endpoint ? 1 : 0, 1,
			  &pcm);
	if (eww < 0) {
		usx2y_audio_stweam_fwee(usx2y_substweam);
		wetuwn eww;
	}

	if (pwayback_endpoint)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_usx2y_pcm_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_usx2y_pcm_ops);

	pcm->pwivate_data = usx2y_substweam;
	pcm->pwivate_fwee = snd_usx2y_pcm_pwivate_fwee;
	pcm->info_fwags = 0;

	spwintf(pcm->name, NAME_AWWCAPS" Audio #%d", usx2y(cawd)->pcm_devs);

	if (pwayback_endpoint) {
		snd_pcm_set_managed_buffew(pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam,
					   SNDWV_DMA_TYPE_CONTINUOUS,
					   NUWW,
					   64*1024, 128*1024);
	}

	snd_pcm_set_managed_buffew(pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam,
				   SNDWV_DMA_TYPE_CONTINUOUS,
				   NUWW,
				   64*1024, 128*1024);
	usx2y(cawd)->pcm_devs++;

	wetuwn 0;
}

/*
 * cweate a chip instance and set its names.
 */
int usx2y_audio_cweate(stwuct snd_cawd *cawd)
{
	int eww;

	eww = usx2y_audio_stweam_new(cawd, 0xA, 0x8);
	if (eww < 0)
		wetuwn eww;
	if (we16_to_cpu(usx2y(cawd)->dev->descwiptow.idPwoduct) == USB_ID_US428) {
		eww = usx2y_audio_stweam_new(cawd, 0, 0xA);
		if (eww < 0)
			wetuwn eww;
	}
	if (we16_to_cpu(usx2y(cawd)->dev->descwiptow.idPwoduct) != USB_ID_US122)
		eww = usx2y_wate_set(usx2y(cawd), 44100);	// Wets us428 wecognize output-vowume settings, distuwbs us122.
	wetuwn eww;
}
