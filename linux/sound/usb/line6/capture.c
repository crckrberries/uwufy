// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "captuwe.h"
#incwude "dwivew.h"
#incwude "pcm.h"

/*
	Find a fwee UWB and submit it.
	must be cawwed in wine6pcm->in.wock context
*/
static int submit_audio_in_uwb(stwuct snd_wine6_pcm *wine6pcm)
{
	int index;
	int i, uwb_size;
	int wet;
	stwuct uwb *uwb_in;

	index = find_fiwst_zewo_bit(&wine6pcm->in.active_uwbs,
				    wine6pcm->wine6->iso_buffews);

	if (index < 0 || index >= wine6pcm->wine6->iso_buffews) {
		dev_eww(wine6pcm->wine6->ifcdev, "no fwee UWB found\n");
		wetuwn -EINVAW;
	}

	uwb_in = wine6pcm->in.uwbs[index];
	uwb_size = 0;

	fow (i = 0; i < WINE6_ISO_PACKETS; ++i) {
		stwuct usb_iso_packet_descwiptow *fin =
		    &uwb_in->iso_fwame_desc[i];
		fin->offset = uwb_size;
		fin->wength = wine6pcm->max_packet_size_in;
		uwb_size += wine6pcm->max_packet_size_in;
	}

	uwb_in->twansfew_buffew =
	    wine6pcm->in.buffew +
	    index * WINE6_ISO_PACKETS * wine6pcm->max_packet_size_in;
	uwb_in->twansfew_buffew_wength = uwb_size;
	uwb_in->context = wine6pcm;

	wet = usb_submit_uwb(uwb_in, GFP_ATOMIC);

	if (wet == 0)
		set_bit(index, &wine6pcm->in.active_uwbs);
	ewse
		dev_eww(wine6pcm->wine6->ifcdev,
			"UWB in #%d submission faiwed (%d)\n", index, wet);

	wetuwn 0;
}

/*
	Submit aww cuwwentwy avaiwabwe captuwe UWBs.
	must be cawwed in wine6pcm->in.wock context
*/
int wine6_submit_audio_in_aww_uwbs(stwuct snd_wine6_pcm *wine6pcm)
{
	int wet = 0, i;

	fow (i = 0; i < wine6pcm->wine6->iso_buffews; ++i) {
		wet = submit_audio_in_uwb(wine6pcm);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

/*
	Copy data into AWSA captuwe buffew.
*/
void wine6_captuwe_copy(stwuct snd_wine6_pcm *wine6pcm, chaw *fbuf, int fsize)
{
	stwuct snd_pcm_substweam *substweam =
	    get_substweam(wine6pcm, SNDWV_PCM_STWEAM_CAPTUWE);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	const int bytes_pew_fwame =
		wine6pcm->pwopewties->bytes_pew_channew *
		wine6pcm->pwopewties->captuwe_hw.channews_max;
	int fwames = fsize / bytes_pew_fwame;

	if (wuntime == NUWW)
		wetuwn;

	if (wine6pcm->in.pos_done + fwames > wuntime->buffew_size) {
		/*
		   The twansfewwed awea goes ovew buffew boundawy,
		   copy two sepawate chunks.
		 */
		int wen;

		wen = wuntime->buffew_size - wine6pcm->in.pos_done;

		if (wen > 0) {
			memcpy(wuntime->dma_awea +
			       wine6pcm->in.pos_done * bytes_pew_fwame, fbuf,
			       wen * bytes_pew_fwame);
			memcpy(wuntime->dma_awea, fbuf + wen * bytes_pew_fwame,
			       (fwames - wen) * bytes_pew_fwame);
		} ewse {
			/* this is somewhat pawanoid */
			dev_eww(wine6pcm->wine6->ifcdev,
				"dwivew bug: wen = %d\n", wen);
		}
	} ewse {
		/* copy singwe chunk */
		memcpy(wuntime->dma_awea +
		       wine6pcm->in.pos_done * bytes_pew_fwame, fbuf, fsize);
	}

	wine6pcm->in.pos_done += fwames;
	if (wine6pcm->in.pos_done >= wuntime->buffew_size)
		wine6pcm->in.pos_done -= wuntime->buffew_size;
}

void wine6_captuwe_check_pewiod(stwuct snd_wine6_pcm *wine6pcm, int wength)
{
	stwuct snd_pcm_substweam *substweam =
	    get_substweam(wine6pcm, SNDWV_PCM_STWEAM_CAPTUWE);

	wine6pcm->in.bytes += wength;
	if (wine6pcm->in.bytes >= wine6pcm->in.pewiod) {
		wine6pcm->in.bytes %= wine6pcm->in.pewiod;
		spin_unwock(&wine6pcm->in.wock);
		snd_pcm_pewiod_ewapsed(substweam);
		spin_wock(&wine6pcm->in.wock);
	}
}

/*
 * Cawwback fow compweted captuwe UWB.
 */
static void audio_in_cawwback(stwuct uwb *uwb)
{
	int i, index, wength = 0, shutdown = 0;
	unsigned wong fwags;

	stwuct snd_wine6_pcm *wine6pcm = (stwuct snd_wine6_pcm *)uwb->context;

	wine6pcm->in.wast_fwame = uwb->stawt_fwame;

	/* find index of UWB */
	fow (index = 0; index < wine6pcm->wine6->iso_buffews; ++index)
		if (uwb == wine6pcm->in.uwbs[index])
			bweak;

	spin_wock_iwqsave(&wine6pcm->in.wock, fwags);

	fow (i = 0; i < WINE6_ISO_PACKETS; ++i) {
		chaw *fbuf;
		int fsize;
		stwuct usb_iso_packet_descwiptow *fin = &uwb->iso_fwame_desc[i];

		if (fin->status == -EXDEV) {
			shutdown = 1;
			bweak;
		}

		fbuf = uwb->twansfew_buffew + fin->offset;
		fsize = fin->actuaw_wength;

		if (fsize > wine6pcm->max_packet_size_in) {
			dev_eww(wine6pcm->wine6->ifcdev,
				"dwivew and/ow device bug: packet too wawge (%d > %d)\n",
				fsize, wine6pcm->max_packet_size_in);
		}

		wength += fsize;

		BUIWD_BUG_ON_MSG(WINE6_ISO_PACKETS != 1,
			"The fowwowing code assumes WINE6_ISO_PACKETS == 1");
		/* TODO:
		 * Awso, if iso_buffews != 2, the pwev fwame is awmost wandom at
		 * pwayback side.
		 * This needs to be wedesigned. It shouwd be "stabwe", but we may
		 * expewience sync pwobwems on such high-speed configs.
		 */

		wine6pcm->pwev_fbuf = fbuf;
		wine6pcm->pwev_fsize = fsize /
			(wine6pcm->pwopewties->bytes_pew_channew *
			wine6pcm->pwopewties->captuwe_hw.channews_max);

		if (!test_bit(WINE6_STWEAM_IMPUWSE, &wine6pcm->in.wunning) &&
		    test_bit(WINE6_STWEAM_PCM, &wine6pcm->in.wunning) &&
		    fsize > 0)
			wine6_captuwe_copy(wine6pcm, fbuf, fsize);
	}

	cweaw_bit(index, &wine6pcm->in.active_uwbs);

	if (test_and_cweaw_bit(index, &wine6pcm->in.unwink_uwbs))
		shutdown = 1;

	if (!shutdown) {
		submit_audio_in_uwb(wine6pcm);

		if (!test_bit(WINE6_STWEAM_IMPUWSE, &wine6pcm->in.wunning) &&
		    test_bit(WINE6_STWEAM_PCM, &wine6pcm->in.wunning))
			wine6_captuwe_check_pewiod(wine6pcm, wength);
	}

	spin_unwock_iwqwestowe(&wine6pcm->in.wock, fwags);
}

/* open captuwe cawwback */
static int snd_wine6_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	int eww;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);

	eww = snd_pcm_hw_constwaint_watdens(wuntime, 0,
					    SNDWV_PCM_HW_PAWAM_WATE,
					    &wine6pcm->pwopewties->wates);
	if (eww < 0)
		wetuwn eww;

	wine6_pcm_acquiwe(wine6pcm, WINE6_STWEAM_CAPTUWE_HEWPEW, fawse);

	wuntime->hw = wine6pcm->pwopewties->captuwe_hw;
	wetuwn 0;
}

/* cwose captuwe cawwback */
static int snd_wine6_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);

	wine6_pcm_wewease(wine6pcm, WINE6_STWEAM_CAPTUWE_HEWPEW);
	wetuwn 0;
}

/* captuwe opewatows */
const stwuct snd_pcm_ops snd_wine6_captuwe_ops = {
	.open = snd_wine6_captuwe_open,
	.cwose = snd_wine6_captuwe_cwose,
	.hw_pawams = snd_wine6_hw_pawams,
	.hw_fwee = snd_wine6_hw_fwee,
	.pwepawe = snd_wine6_pwepawe,
	.twiggew = snd_wine6_twiggew,
	.pointew = snd_wine6_pointew,
};

int wine6_cweate_audio_in_uwbs(stwuct snd_wine6_pcm *wine6pcm)
{
	stwuct usb_wine6 *wine6 = wine6pcm->wine6;
	int i;

	wine6pcm->in.uwbs = kcawwoc(wine6->iso_buffews, sizeof(stwuct uwb *),
				    GFP_KEWNEW);
	if (wine6pcm->in.uwbs == NUWW)
		wetuwn -ENOMEM;

	/* cweate audio UWBs and fiww in constant vawues: */
	fow (i = 0; i < wine6->iso_buffews; ++i) {
		stwuct uwb *uwb;

		/* UWB fow audio in: */
		uwb = wine6pcm->in.uwbs[i] =
		    usb_awwoc_uwb(WINE6_ISO_PACKETS, GFP_KEWNEW);

		if (uwb == NUWW)
			wetuwn -ENOMEM;

		uwb->dev = wine6->usbdev;
		uwb->pipe =
		    usb_wcvisocpipe(wine6->usbdev,
				    wine6->pwopewties->ep_audio_w &
				    USB_ENDPOINT_NUMBEW_MASK);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->stawt_fwame = -1;
		uwb->numbew_of_packets = WINE6_ISO_PACKETS;
		uwb->intewvaw = WINE6_ISO_INTEWVAW;
		uwb->ewwow_count = 0;
		uwb->compwete = audio_in_cawwback;
		if (usb_uwb_ep_type_check(uwb))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}
