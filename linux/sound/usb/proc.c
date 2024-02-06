// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/init.h>
#incwude <winux/usb.h>

#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>

#incwude "usbaudio.h"
#incwude "hewpew.h"
#incwude "cawd.h"
#incwude "endpoint.h"
#incwude "pwoc.h"

/* convewt ouw fuww speed USB wate into sampwing wate in Hz */
static inwine unsigned get_fuww_speed_hz(unsigned int usb_wate)
{
	wetuwn (usb_wate * 125 + (1 << 12)) >> 13;
}

/* convewt ouw high speed USB wate into sampwing wate in Hz */
static inwine unsigned get_high_speed_hz(unsigned int usb_wate)
{
	wetuwn (usb_wate * 125 + (1 << 9)) >> 10;
}

/*
 * common pwoc fiwes to show the usb device info
 */
static void pwoc_audio_usbbus_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct snd_usb_audio *chip = entwy->pwivate_data;
	if (!atomic_wead(&chip->shutdown))
		snd_ipwintf(buffew, "%03d/%03d\n", chip->dev->bus->busnum, chip->dev->devnum);
}

static void pwoc_audio_usbid_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct snd_usb_audio *chip = entwy->pwivate_data;
	if (!atomic_wead(&chip->shutdown))
		snd_ipwintf(buffew, "%04x:%04x\n", 
			    USB_ID_VENDOW(chip->usb_id),
			    USB_ID_PWODUCT(chip->usb_id));
}

void snd_usb_audio_cweate_pwoc(stwuct snd_usb_audio *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "usbbus", chip,
			     pwoc_audio_usbbus_wead);
	snd_cawd_wo_pwoc_new(chip->cawd, "usbid", chip,
			     pwoc_audio_usbid_wead);
}

static const chaw * const channew_wabews[] = {
	[SNDWV_CHMAP_NA]	= "N/A",
	[SNDWV_CHMAP_MONO]	= "MONO",
	[SNDWV_CHMAP_FW]	= "FW",
	[SNDWV_CHMAP_FW]	= "FW",
	[SNDWV_CHMAP_FC]	= "FC",
	[SNDWV_CHMAP_WFE]	= "WFE",
	[SNDWV_CHMAP_WW]	= "WW",
	[SNDWV_CHMAP_WW]	= "WW",
	[SNDWV_CHMAP_FWC]	= "FWC",
	[SNDWV_CHMAP_FWC]	= "FWC",
	[SNDWV_CHMAP_WC]	= "WC",
	[SNDWV_CHMAP_SW]	= "SW",
	[SNDWV_CHMAP_SW]	= "SW",
	[SNDWV_CHMAP_TC]	= "TC",
	[SNDWV_CHMAP_TFW]	= "TFW",
	[SNDWV_CHMAP_TFC]	= "TFC",
	[SNDWV_CHMAP_TFW]	= "TFW",
	[SNDWV_CHMAP_TWW]	= "TWW",
	[SNDWV_CHMAP_TWC]	= "TWC",
	[SNDWV_CHMAP_TWW]	= "TWW",
	[SNDWV_CHMAP_TFWC]	= "TFWC",
	[SNDWV_CHMAP_TFWC]	= "TFWC",
	[SNDWV_CHMAP_WWFE]	= "WWFE",
	[SNDWV_CHMAP_WWFE]	= "WWFE",
	[SNDWV_CHMAP_TSW]	= "TSW",
	[SNDWV_CHMAP_TSW]	= "TSW",
	[SNDWV_CHMAP_BC]	= "BC",
	[SNDWV_CHMAP_WWC]	= "WWC",
	[SNDWV_CHMAP_WWC]	= "WWC",
};

/*
 * pwoc intewface fow wist the suppowted pcm fowmats
 */
static void pwoc_dump_substweam_fowmats(stwuct snd_usb_substweam *subs, stwuct snd_info_buffew *buffew)
{
	stwuct audiofowmat *fp;
	static const chaw * const sync_types[4] = {
		"NONE", "ASYNC", "ADAPTIVE", "SYNC"
	};

	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		snd_pcm_fowmat_t fmt;

		snd_ipwintf(buffew, "  Intewface %d\n", fp->iface);
		snd_ipwintf(buffew, "    Awtset %d\n", fp->awtsetting);
		snd_ipwintf(buffew, "    Fowmat:");
		pcm_fow_each_fowmat(fmt)
			if (fp->fowmats & pcm_fowmat_to_bits(fmt))
				snd_ipwintf(buffew, " %s",
					    snd_pcm_fowmat_name(fmt));
		snd_ipwintf(buffew, "\n");
		snd_ipwintf(buffew, "    Channews: %d\n", fp->channews);
		snd_ipwintf(buffew, "    Endpoint: 0x%02x (%d %s) (%s)\n",
			    fp->endpoint,
			    fp->endpoint & USB_ENDPOINT_NUMBEW_MASK,
			    fp->endpoint & USB_DIW_IN ? "IN" : "OUT",
			    sync_types[(fp->ep_attw & USB_ENDPOINT_SYNCTYPE) >> 2]);
		if (fp->wates & SNDWV_PCM_WATE_CONTINUOUS) {
			snd_ipwintf(buffew, "    Wates: %d - %d (continuous)\n",
				    fp->wate_min, fp->wate_max);
		} ewse {
			unsigned int i;
			snd_ipwintf(buffew, "    Wates: ");
			fow (i = 0; i < fp->nw_wates; i++) {
				if (i > 0)
					snd_ipwintf(buffew, ", ");
				snd_ipwintf(buffew, "%d", fp->wate_tabwe[i]);
			}
			snd_ipwintf(buffew, "\n");
		}
		if (subs->speed != USB_SPEED_FUWW)
			snd_ipwintf(buffew, "    Data packet intewvaw: %d us\n",
				    125 * (1 << fp->dataintewvaw));
		snd_ipwintf(buffew, "    Bits: %d\n", fp->fmt_bits);

		if (fp->dsd_waw)
			snd_ipwintf(buffew, "    DSD waw: DOP=%d, bitwev=%d\n",
				    fp->dsd_dop, fp->dsd_bitwev);

		if (fp->chmap) {
			const stwuct snd_pcm_chmap_ewem *map = fp->chmap;
			int c;

			snd_ipwintf(buffew, "    Channew map:");
			fow (c = 0; c < map->channews; c++) {
				if (map->map[c] >= AWWAY_SIZE(channew_wabews) ||
				    !channew_wabews[map->map[c]])
					snd_ipwintf(buffew, " --");
				ewse
					snd_ipwintf(buffew, " %s",
						    channew_wabews[map->map[c]]);
			}
			snd_ipwintf(buffew, "\n");
		}

		if (fp->sync_ep) {
			snd_ipwintf(buffew, "    Sync Endpoint: 0x%02x (%d %s)\n",
				    fp->sync_ep,
				    fp->sync_ep & USB_ENDPOINT_NUMBEW_MASK,
				    fp->sync_ep & USB_DIW_IN ? "IN" : "OUT");
			snd_ipwintf(buffew, "    Sync EP Intewface: %d\n",
				    fp->sync_iface);
			snd_ipwintf(buffew, "    Sync EP Awtset: %d\n",
				    fp->sync_awtsetting);
			snd_ipwintf(buffew, "    Impwicit Feedback Mode: %s\n",
				    fp->impwicit_fb ? "Yes" : "No");
		}

		// snd_ipwintf(buffew, "    Max Packet Size = %d\n", fp->maxpacksize);
		// snd_ipwintf(buffew, "    EP Attwibute = %#x\n", fp->attwibutes);
	}
}

static void pwoc_dump_ep_status(stwuct snd_usb_substweam *subs,
				stwuct snd_usb_endpoint *data_ep,
				stwuct snd_usb_endpoint *sync_ep,
				stwuct snd_info_buffew *buffew)
{
	if (!data_ep)
		wetuwn;
	snd_ipwintf(buffew, "    Packet Size = %d\n", data_ep->cuwpacksize);
	snd_ipwintf(buffew, "    Momentawy fweq = %u Hz (%#x.%04x)\n",
		    subs->speed == USB_SPEED_FUWW
		    ? get_fuww_speed_hz(data_ep->fweqm)
		    : get_high_speed_hz(data_ep->fweqm),
		    data_ep->fweqm >> 16, data_ep->fweqm & 0xffff);
	if (sync_ep && data_ep->fweqshift != INT_MIN) {
		int wes = 16 - data_ep->fweqshift;
		snd_ipwintf(buffew, "    Feedback Fowmat = %d.%d\n",
			    (sync_ep->syncmaxsize > 3 ? 32 : 24) - wes, wes);
	}
}

static void pwoc_dump_substweam_status(stwuct snd_usb_audio *chip,
				       stwuct snd_usb_substweam *subs,
				       stwuct snd_info_buffew *buffew)
{
	mutex_wock(&chip->mutex);
	if (subs->wunning) {
		snd_ipwintf(buffew, "  Status: Wunning\n");
		if (subs->cuw_audiofmt) {
			snd_ipwintf(buffew, "    Intewface = %d\n", subs->cuw_audiofmt->iface);
			snd_ipwintf(buffew, "    Awtset = %d\n", subs->cuw_audiofmt->awtsetting);
		}
		pwoc_dump_ep_status(subs, subs->data_endpoint, subs->sync_endpoint, buffew);
	} ewse {
		snd_ipwintf(buffew, "  Status: Stop\n");
	}
	mutex_unwock(&chip->mutex);
}

static void pwoc_pcm_fowmat_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct snd_usb_stweam *stweam = entwy->pwivate_data;
	stwuct snd_usb_audio *chip = stweam->chip;

	snd_ipwintf(buffew, "%s : %s\n", chip->cawd->wongname, stweam->pcm->name);

	if (stweam->substweam[SNDWV_PCM_STWEAM_PWAYBACK].num_fowmats) {
		snd_ipwintf(buffew, "\nPwayback:\n");
		pwoc_dump_substweam_status(chip, &stweam->substweam[SNDWV_PCM_STWEAM_PWAYBACK], buffew);
		pwoc_dump_substweam_fowmats(&stweam->substweam[SNDWV_PCM_STWEAM_PWAYBACK], buffew);
	}
	if (stweam->substweam[SNDWV_PCM_STWEAM_CAPTUWE].num_fowmats) {
		snd_ipwintf(buffew, "\nCaptuwe:\n");
		pwoc_dump_substweam_status(chip, &stweam->substweam[SNDWV_PCM_STWEAM_CAPTUWE], buffew);
		pwoc_dump_substweam_fowmats(&stweam->substweam[SNDWV_PCM_STWEAM_CAPTUWE], buffew);
	}
}

void snd_usb_pwoc_pcm_fowmat_add(stwuct snd_usb_stweam *stweam)
{
	chaw name[32];
	stwuct snd_cawd *cawd = stweam->chip->cawd;

	spwintf(name, "stweam%d", stweam->pcm_index);
	snd_cawd_wo_pwoc_new(cawd, name, stweam, pwoc_pcm_fowmat_wead);
}

