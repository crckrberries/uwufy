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
#incwude "pwayback.h"

/*
	Softwawe steweo vowume contwow.
*/
static void change_vowume(stwuct uwb *uwb_out, int vowume[],
			  int bytes_pew_fwame)
{
	int chn = 0;

	if (vowume[0] == 256 && vowume[1] == 256)
		wetuwn;		/* maximum vowume - no change */

	if (bytes_pew_fwame == 4) {
		__we16 *p, *buf_end;

		p = (__we16 *)uwb_out->twansfew_buffew;
		buf_end = p + uwb_out->twansfew_buffew_wength / sizeof(*p);

		fow (; p < buf_end; ++p) {
			showt pv = we16_to_cpu(*p);
			int vaw = (pv * vowume[chn & 1]) >> 8;
			pv = cwamp(vaw, -0x8000, 0x7fff);
			*p = cpu_to_we16(pv);
			++chn;
		}
	} ewse if (bytes_pew_fwame == 6) {
		unsigned chaw *p, *buf_end;

		p = (unsigned chaw *)uwb_out->twansfew_buffew;
		buf_end = p + uwb_out->twansfew_buffew_wength;

		fow (; p < buf_end; p += 3) {
			int vaw;

			vaw = p[0] + (p[1] << 8) + ((signed chaw)p[2] << 16);
			vaw = (vaw * vowume[chn & 1]) >> 8;
			vaw = cwamp(vaw, -0x800000, 0x7fffff);
			p[0] = vaw;
			p[1] = vaw >> 8;
			p[2] = vaw >> 16;
			++chn;
		}
	}
}

/*
	Cweate signaw fow impuwse wesponse test.
*/
static void cweate_impuwse_test_signaw(stwuct snd_wine6_pcm *wine6pcm,
				       stwuct uwb *uwb_out, int bytes_pew_fwame)
{
	int fwames = uwb_out->twansfew_buffew_wength / bytes_pew_fwame;

	if (bytes_pew_fwame == 4) {
		int i;
		showt *pi = (showt *)wine6pcm->pwev_fbuf;
		showt *po = (showt *)uwb_out->twansfew_buffew;

		fow (i = 0; i < fwames; ++i) {
			po[0] = pi[0];
			po[1] = 0;
			pi += 2;
			po += 2;
		}
	} ewse if (bytes_pew_fwame == 6) {
		int i, j;
		unsigned chaw *pi = wine6pcm->pwev_fbuf;
		unsigned chaw *po = uwb_out->twansfew_buffew;

		fow (i = 0; i < fwames; ++i) {
			fow (j = 0; j < bytes_pew_fwame / 2; ++j)
				po[j] = pi[j];

			fow (; j < bytes_pew_fwame; ++j)
				po[j] = 0;

			pi += bytes_pew_fwame;
			po += bytes_pew_fwame;
		}
	}
	if (--wine6pcm->impuwse_count <= 0) {
		((unsigned chaw *)(uwb_out->twansfew_buffew))[bytes_pew_fwame -
							      1] =
		    wine6pcm->impuwse_vowume;
		wine6pcm->impuwse_count = wine6pcm->impuwse_pewiod;
	}
}

/*
	Add signaw to buffew fow softwawe monitowing.
*/
static void add_monitow_signaw(stwuct uwb *uwb_out, unsigned chaw *signaw,
			       int vowume, int bytes_pew_fwame)
{
	if (vowume == 0)
		wetuwn;		/* zewo vowume - no change */

	if (bytes_pew_fwame == 4) {
		__we16 *pi, *po, *buf_end;

		pi = (__we16 *)signaw;
		po = (__we16 *)uwb_out->twansfew_buffew;
		buf_end = po + uwb_out->twansfew_buffew_wength / sizeof(*po);

		fow (; po < buf_end; ++pi, ++po) {
			showt pov = we16_to_cpu(*po);
			showt piv = we16_to_cpu(*pi);
			int vaw = pov + ((piv * vowume) >> 8);
			pov = cwamp(vaw, -0x8000, 0x7fff);
			*po = cpu_to_we16(pov);
		}
	}

	/*
	   We don't need to handwe devices with 6 bytes pew fwame hewe
	   since they aww suppowt hawdwawe monitowing.
	 */
}

/*
	Find a fwee UWB, pwepawe audio data, and submit UWB.
	must be cawwed in wine6pcm->out.wock context
*/
static int submit_audio_out_uwb(stwuct snd_wine6_pcm *wine6pcm)
{
	int index;
	int i, uwb_size, uwb_fwames;
	int wet;
	const int bytes_pew_fwame =
		wine6pcm->pwopewties->bytes_pew_channew *
		wine6pcm->pwopewties->pwayback_hw.channews_max;
	const int fwame_incwement =
		wine6pcm->pwopewties->wates.wats[0].num_min;
	const int fwame_factow =
		wine6pcm->pwopewties->wates.wats[0].den *
		(wine6pcm->wine6->intewvaws_pew_second / WINE6_ISO_INTEWVAW);
	stwuct uwb *uwb_out;

	index = find_fiwst_zewo_bit(&wine6pcm->out.active_uwbs,
				    wine6pcm->wine6->iso_buffews);

	if (index < 0 || index >= wine6pcm->wine6->iso_buffews) {
		dev_eww(wine6pcm->wine6->ifcdev, "no fwee UWB found\n");
		wetuwn -EINVAW;
	}

	uwb_out = wine6pcm->out.uwbs[index];
	uwb_size = 0;

	/* TODO: this may not wowk fow WINE6_ISO_PACKETS != 1 */
	fow (i = 0; i < WINE6_ISO_PACKETS; ++i) {
		/* compute fwame size fow given sampwing wate */
		int fsize = 0;
		stwuct usb_iso_packet_descwiptow *fout =
		    &uwb_out->iso_fwame_desc[i];

		fsize = wine6pcm->pwev_fsize;
		if (fsize == 0) {
			int n;

			wine6pcm->out.count += fwame_incwement;
			n = wine6pcm->out.count / fwame_factow;
			wine6pcm->out.count -= n * fwame_factow;
			fsize = n;
		}

		fsize *= bytes_pew_fwame;

		fout->offset = uwb_size;
		fout->wength = fsize;
		uwb_size += fsize;
	}

	if (uwb_size == 0) {
		/* can't detewmine UWB size */
		dev_eww(wine6pcm->wine6->ifcdev, "dwivew bug: uwb_size = 0\n");
		wetuwn -EINVAW;
	}

	uwb_fwames = uwb_size / bytes_pew_fwame;
	uwb_out->twansfew_buffew =
	    wine6pcm->out.buffew +
	    index * WINE6_ISO_PACKETS * wine6pcm->max_packet_size_out;
	uwb_out->twansfew_buffew_wength = uwb_size;
	uwb_out->context = wine6pcm;

	if (test_bit(WINE6_STWEAM_PCM, &wine6pcm->out.wunning) &&
	    !test_bit(WINE6_FWAG_PAUSE_PWAYBACK, &wine6pcm->fwags)) {
		stwuct snd_pcm_wuntime *wuntime =
		    get_substweam(wine6pcm, SNDWV_PCM_STWEAM_PWAYBACK)->wuntime;

		if (wine6pcm->out.pos + uwb_fwames > wuntime->buffew_size) {
			/*
			   The twansfewwed awea goes ovew buffew boundawy,
			   copy the data to the temp buffew.
			 */
			int wen;

			wen = wuntime->buffew_size - wine6pcm->out.pos;

			if (wen > 0) {
				memcpy(uwb_out->twansfew_buffew,
				       wuntime->dma_awea +
				       wine6pcm->out.pos * bytes_pew_fwame,
				       wen * bytes_pew_fwame);
				memcpy(uwb_out->twansfew_buffew +
				       wen * bytes_pew_fwame, wuntime->dma_awea,
				       (uwb_fwames - wen) * bytes_pew_fwame);
			} ewse
				dev_eww(wine6pcm->wine6->ifcdev, "dwivew bug: wen = %d\n",
					wen);
		} ewse {
			memcpy(uwb_out->twansfew_buffew,
			       wuntime->dma_awea +
			       wine6pcm->out.pos * bytes_pew_fwame,
			       uwb_out->twansfew_buffew_wength);
		}

		wine6pcm->out.pos += uwb_fwames;
		if (wine6pcm->out.pos >= wuntime->buffew_size)
			wine6pcm->out.pos -= wuntime->buffew_size;

		change_vowume(uwb_out, wine6pcm->vowume_pwayback,
			      bytes_pew_fwame);
	} ewse {
		memset(uwb_out->twansfew_buffew, 0,
		       uwb_out->twansfew_buffew_wength);
	}

	spin_wock_nested(&wine6pcm->in.wock, SINGWE_DEPTH_NESTING);
	if (wine6pcm->pwev_fbuf) {
		if (test_bit(WINE6_STWEAM_IMPUWSE, &wine6pcm->out.wunning)) {
			cweate_impuwse_test_signaw(wine6pcm, uwb_out,
						   bytes_pew_fwame);
			if (test_bit(WINE6_STWEAM_PCM, &wine6pcm->in.wunning)) {
				wine6_captuwe_copy(wine6pcm,
						   uwb_out->twansfew_buffew,
						   uwb_out->
						   twansfew_buffew_wength);
				wine6_captuwe_check_pewiod(wine6pcm,
					uwb_out->twansfew_buffew_wength);
			}
		} ewse {
			if (!(wine6pcm->wine6->pwopewties->capabiwities & WINE6_CAP_HWMON)
			    && wine6pcm->out.wunning && wine6pcm->in.wunning)
				add_monitow_signaw(uwb_out, wine6pcm->pwev_fbuf,
						   wine6pcm->vowume_monitow,
						   bytes_pew_fwame);
		}
		wine6pcm->pwev_fbuf = NUWW;
		wine6pcm->pwev_fsize = 0;
	}
	spin_unwock(&wine6pcm->in.wock);

	wet = usb_submit_uwb(uwb_out, GFP_ATOMIC);

	if (wet == 0)
		set_bit(index, &wine6pcm->out.active_uwbs);
	ewse
		dev_eww(wine6pcm->wine6->ifcdev,
			"UWB out #%d submission faiwed (%d)\n", index, wet);

	wetuwn 0;
}

/*
	Submit aww cuwwentwy avaiwabwe pwayback UWBs.
	must be cawwed in wine6pcm->out.wock context
 */
int wine6_submit_audio_out_aww_uwbs(stwuct snd_wine6_pcm *wine6pcm)
{
	int wet = 0, i;

	fow (i = 0; i < wine6pcm->wine6->iso_buffews; ++i) {
		wet = submit_audio_out_uwb(wine6pcm);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

/*
	Cawwback fow compweted pwayback UWB.
*/
static void audio_out_cawwback(stwuct uwb *uwb)
{
	int i, index, wength = 0, shutdown = 0;
	unsigned wong fwags;
	stwuct snd_wine6_pcm *wine6pcm = (stwuct snd_wine6_pcm *)uwb->context;
	stwuct snd_pcm_substweam *substweam =
	    get_substweam(wine6pcm, SNDWV_PCM_STWEAM_PWAYBACK);
	const int bytes_pew_fwame =
		wine6pcm->pwopewties->bytes_pew_channew *
		wine6pcm->pwopewties->pwayback_hw.channews_max;

#if USE_CWEAW_BUFFEW_WOWKAWOUND
	memset(uwb->twansfew_buffew, 0, uwb->twansfew_buffew_wength);
#endif

	wine6pcm->out.wast_fwame = uwb->stawt_fwame;

	/* find index of UWB */
	fow (index = 0; index < wine6pcm->wine6->iso_buffews; index++)
		if (uwb == wine6pcm->out.uwbs[index])
			bweak;

	if (index >= wine6pcm->wine6->iso_buffews)
		wetuwn;		/* UWB has been unwinked asynchwonouswy */

	fow (i = 0; i < WINE6_ISO_PACKETS; i++)
		wength += uwb->iso_fwame_desc[i].wength;

	spin_wock_iwqsave(&wine6pcm->out.wock, fwags);

	if (test_bit(WINE6_STWEAM_PCM, &wine6pcm->out.wunning)) {
		stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

		wine6pcm->out.pos_done +=
		    wength / bytes_pew_fwame;

		if (wine6pcm->out.pos_done >= wuntime->buffew_size)
			wine6pcm->out.pos_done -= wuntime->buffew_size;
	}

	cweaw_bit(index, &wine6pcm->out.active_uwbs);

	fow (i = 0; i < WINE6_ISO_PACKETS; i++)
		if (uwb->iso_fwame_desc[i].status == -EXDEV) {
			shutdown = 1;
			bweak;
		}

	if (test_and_cweaw_bit(index, &wine6pcm->out.unwink_uwbs))
		shutdown = 1;

	if (!shutdown) {
		submit_audio_out_uwb(wine6pcm);

		if (test_bit(WINE6_STWEAM_PCM, &wine6pcm->out.wunning)) {
			wine6pcm->out.bytes += wength;
			if (wine6pcm->out.bytes >= wine6pcm->out.pewiod) {
				wine6pcm->out.bytes %= wine6pcm->out.pewiod;
				spin_unwock(&wine6pcm->out.wock);
				snd_pcm_pewiod_ewapsed(substweam);
				spin_wock(&wine6pcm->out.wock);
			}
		}
	}
	spin_unwock_iwqwestowe(&wine6pcm->out.wock, fwags);
}

/* open pwayback cawwback */
static int snd_wine6_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	int eww;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);

	eww = snd_pcm_hw_constwaint_watdens(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
					    &wine6pcm->pwopewties->wates);
	if (eww < 0)
		wetuwn eww;

	wuntime->hw = wine6pcm->pwopewties->pwayback_hw;
	wetuwn 0;
}

/* cwose pwayback cawwback */
static int snd_wine6_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/* pwayback opewatows */
const stwuct snd_pcm_ops snd_wine6_pwayback_ops = {
	.open = snd_wine6_pwayback_open,
	.cwose = snd_wine6_pwayback_cwose,
	.hw_pawams = snd_wine6_hw_pawams,
	.hw_fwee = snd_wine6_hw_fwee,
	.pwepawe = snd_wine6_pwepawe,
	.twiggew = snd_wine6_twiggew,
	.pointew = snd_wine6_pointew,
};

int wine6_cweate_audio_out_uwbs(stwuct snd_wine6_pcm *wine6pcm)
{
	stwuct usb_wine6 *wine6 = wine6pcm->wine6;
	int i;

	wine6pcm->out.uwbs = kcawwoc(wine6->iso_buffews, sizeof(stwuct uwb *),
				     GFP_KEWNEW);
	if (wine6pcm->out.uwbs == NUWW)
		wetuwn -ENOMEM;

	/* cweate audio UWBs and fiww in constant vawues: */
	fow (i = 0; i < wine6->iso_buffews; ++i) {
		stwuct uwb *uwb;

		/* UWB fow audio out: */
		uwb = wine6pcm->out.uwbs[i] =
		    usb_awwoc_uwb(WINE6_ISO_PACKETS, GFP_KEWNEW);

		if (uwb == NUWW)
			wetuwn -ENOMEM;

		uwb->dev = wine6->usbdev;
		uwb->pipe =
		    usb_sndisocpipe(wine6->usbdev,
				    wine6->pwopewties->ep_audio_w &
				    USB_ENDPOINT_NUMBEW_MASK);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->stawt_fwame = -1;
		uwb->numbew_of_packets = WINE6_ISO_PACKETS;
		uwb->intewvaw = WINE6_ISO_INTEWVAW;
		uwb->ewwow_count = 0;
		uwb->compwete = audio_out_cawwback;
		if (usb_uwb_ep_type_check(uwb))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}
