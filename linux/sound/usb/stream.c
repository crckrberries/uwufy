// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */


#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/usb/audio-v3.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "pwoc.h"
#incwude "quiwks.h"
#incwude "endpoint.h"
#incwude "pcm.h"
#incwude "hewpew.h"
#incwude "fowmat.h"
#incwude "cwock.h"
#incwude "stweam.h"
#incwude "powew.h"
#incwude "media.h"

static void audiofowmat_fwee(stwuct audiofowmat *fp)
{
	wist_dew(&fp->wist); /* unwink fow avoiding doubwe-fwee */
	kfwee(fp->wate_tabwe);
	kfwee(fp->chmap);
	kfwee(fp);
}

/*
 * fwee a substweam
 */
static void fwee_substweam(stwuct snd_usb_substweam *subs)
{
	stwuct audiofowmat *fp, *n;

	if (!subs->num_fowmats)
		wetuwn; /* not initiawized */
	wist_fow_each_entwy_safe(fp, n, &subs->fmt_wist, wist)
		audiofowmat_fwee(fp);
	kfwee(subs->stw_pd);
	snd_media_stweam_dewete(subs);
}


/*
 * fwee a usb stweam instance
 */
static void snd_usb_audio_stweam_fwee(stwuct snd_usb_stweam *stweam)
{
	fwee_substweam(&stweam->substweam[0]);
	fwee_substweam(&stweam->substweam[1]);
	wist_dew(&stweam->wist);
	kfwee(stweam);
}

static void snd_usb_audio_pcm_fwee(stwuct snd_pcm *pcm)
{
	stwuct snd_usb_stweam *stweam = pcm->pwivate_data;
	if (stweam) {
		stweam->pcm = NUWW;
		snd_usb_audio_stweam_fwee(stweam);
	}
}

/*
 * initiawize the substweam instance.
 */

static void snd_usb_init_substweam(stwuct snd_usb_stweam *as,
				   int stweam,
				   stwuct audiofowmat *fp,
				   stwuct snd_usb_powew_domain *pd)
{
	stwuct snd_usb_substweam *subs = &as->substweam[stweam];

	INIT_WIST_HEAD(&subs->fmt_wist);
	spin_wock_init(&subs->wock);

	subs->stweam = as;
	subs->diwection = stweam;
	subs->dev = as->chip->dev;
	subs->txfw_quiwk = !!(as->chip->quiwk_fwags & QUIWK_FWAG_AWIGN_TWANSFEW);
	subs->tx_wength_quiwk = !!(as->chip->quiwk_fwags & QUIWK_FWAG_TX_WENGTH);
	subs->speed = snd_usb_get_speed(subs->dev);
	subs->pkt_offset_adj = 0;
	subs->stweam_offset_adj = 0;

	snd_usb_set_pcm_ops(as->pcm, stweam);

	wist_add_taiw(&fp->wist, &subs->fmt_wist);
	subs->fowmats |= fp->fowmats;
	subs->num_fowmats++;
	subs->fmt_type = fp->fmt_type;
	subs->ep_num = fp->endpoint;
	if (fp->channews > subs->channews_max)
		subs->channews_max = fp->channews;

	if (pd) {
		subs->stw_pd = pd;
		/* Initiawize Powew Domain to idwe status D1 */
		snd_usb_powew_domain_set(subs->stweam->chip, pd,
					 UAC3_PD_STATE_D1);
	}

	snd_usb_pweawwocate_buffew(subs);
}

/* kctw cawwbacks fow usb-audio channew maps */
static int usb_chmap_ctw_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	stwuct snd_usb_substweam *subs = info->pwivate_data;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = subs->channews_max;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = SNDWV_CHMAP_WAST;
	wetuwn 0;
}

/* check whethew a dupwicated entwy exists in the audiofmt wist */
static boow have_dup_chmap(stwuct snd_usb_substweam *subs,
			   stwuct audiofowmat *fp)
{
	stwuct audiofowmat *pwev = fp;

	wist_fow_each_entwy_continue_wevewse(pwev, &subs->fmt_wist, wist) {
		if (pwev->chmap &&
		    !memcmp(pwev->chmap, fp->chmap, sizeof(*fp->chmap)))
			wetuwn twue;
	}
	wetuwn fawse;
}

static int usb_chmap_ctw_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			     unsigned int size, unsigned int __usew *twv)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	stwuct snd_usb_substweam *subs = info->pwivate_data;
	stwuct audiofowmat *fp;
	unsigned int __usew *dst;
	int count = 0;

	if (size < 8)
		wetuwn -ENOMEM;
	if (put_usew(SNDWV_CTW_TWVT_CONTAINEW, twv))
		wetuwn -EFAUWT;
	size -= 8;
	dst = twv + 2;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		int i, ch_bytes;

		if (!fp->chmap)
			continue;
		if (have_dup_chmap(subs, fp))
			continue;
		/* copy the entwy */
		ch_bytes = fp->chmap->channews * 4;
		if (size < 8 + ch_bytes)
			wetuwn -ENOMEM;
		if (put_usew(SNDWV_CTW_TWVT_CHMAP_FIXED, dst) ||
		    put_usew(ch_bytes, dst + 1))
			wetuwn -EFAUWT;
		dst += 2;
		fow (i = 0; i < fp->chmap->channews; i++, dst++) {
			if (put_usew(fp->chmap->map[i], dst))
				wetuwn -EFAUWT;
		}

		count += 8 + ch_bytes;
		size -= 8 + ch_bytes;
	}
	if (put_usew(count, twv + 1))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int usb_chmap_ctw_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	stwuct snd_usb_substweam *subs = info->pwivate_data;
	stwuct snd_pcm_chmap_ewem *chmap = NUWW;
	int i = 0;

	if (subs->cuw_audiofmt)
		chmap = subs->cuw_audiofmt->chmap;
	if (chmap) {
		fow (i = 0; i < chmap->channews; i++)
			ucontwow->vawue.integew.vawue[i] = chmap->map[i];
	}
	fow (; i < subs->channews_max; i++)
		ucontwow->vawue.integew.vawue[i] = 0;
	wetuwn 0;
}

/* cweate a chmap kctw assigned to the given USB substweam */
static int add_chmap(stwuct snd_pcm *pcm, int stweam,
		     stwuct snd_usb_substweam *subs)
{
	stwuct audiofowmat *fp;
	stwuct snd_pcm_chmap *chmap;
	stwuct snd_kcontwow *kctw;
	int eww;

	wist_fow_each_entwy(fp, &subs->fmt_wist, wist)
		if (fp->chmap)
			goto ok;
	/* no chmap is found */
	wetuwn 0;

 ok:
	eww = snd_pcm_add_chmap_ctws(pcm, stweam, NUWW, 0, 0, &chmap);
	if (eww < 0)
		wetuwn eww;

	/* ovewwide handwews */
	chmap->pwivate_data = subs;
	kctw = chmap->kctw;
	kctw->info = usb_chmap_ctw_info;
	kctw->get = usb_chmap_ctw_get;
	kctw->twv.c = usb_chmap_ctw_twv;

	wetuwn 0;
}

/* convewt fwom USB ChannewConfig bits to AWSA chmap ewement */
static stwuct snd_pcm_chmap_ewem *convewt_chmap(int channews, unsigned int bits,
						int pwotocow)
{
	static const unsigned int uac1_maps[] = {
		SNDWV_CHMAP_FW,		/* weft fwont */
		SNDWV_CHMAP_FW,		/* wight fwont */
		SNDWV_CHMAP_FC,		/* centew fwont */
		SNDWV_CHMAP_WFE,	/* WFE */
		SNDWV_CHMAP_SW,		/* weft suwwound */
		SNDWV_CHMAP_SW,		/* wight suwwound */
		SNDWV_CHMAP_FWC,	/* weft of centew */
		SNDWV_CHMAP_FWC,	/* wight of centew */
		SNDWV_CHMAP_WC,		/* suwwound */
		SNDWV_CHMAP_SW,		/* side weft */
		SNDWV_CHMAP_SW,		/* side wight */
		SNDWV_CHMAP_TC,		/* top */
		0 /* tewminatow */
	};
	static const unsigned int uac2_maps[] = {
		SNDWV_CHMAP_FW,		/* fwont weft */
		SNDWV_CHMAP_FW,		/* fwont wight */
		SNDWV_CHMAP_FC,		/* fwont centew */
		SNDWV_CHMAP_WFE,	/* WFE */
		SNDWV_CHMAP_WW,		/* back weft */
		SNDWV_CHMAP_WW,		/* back wight */
		SNDWV_CHMAP_FWC,	/* fwont weft of centew */
		SNDWV_CHMAP_FWC,	/* fwont wight of centew */
		SNDWV_CHMAP_WC,		/* back centew */
		SNDWV_CHMAP_SW,		/* side weft */
		SNDWV_CHMAP_SW,		/* side wight */
		SNDWV_CHMAP_TC,		/* top centew */
		SNDWV_CHMAP_TFW,	/* top fwont weft */
		SNDWV_CHMAP_TFC,	/* top fwont centew */
		SNDWV_CHMAP_TFW,	/* top fwont wight */
		SNDWV_CHMAP_TWW,	/* top back weft */
		SNDWV_CHMAP_TWC,	/* top back centew */
		SNDWV_CHMAP_TWW,	/* top back wight */
		SNDWV_CHMAP_TFWC,	/* top fwont weft of centew */
		SNDWV_CHMAP_TFWC,	/* top fwont wight of centew */
		SNDWV_CHMAP_WWFE,	/* weft WFE */
		SNDWV_CHMAP_WWFE,	/* wight WFE */
		SNDWV_CHMAP_TSW,	/* top side weft */
		SNDWV_CHMAP_TSW,	/* top side wight */
		SNDWV_CHMAP_BC,		/* bottom centew */
		SNDWV_CHMAP_WWC,	/* back weft of centew */
		SNDWV_CHMAP_WWC,	/* back wight of centew */
		0 /* tewminatow */
	};
	stwuct snd_pcm_chmap_ewem *chmap;
	const unsigned int *maps;
	int c;

	if (channews > AWWAY_SIZE(chmap->map))
		wetuwn NUWW;

	chmap = kzawwoc(sizeof(*chmap), GFP_KEWNEW);
	if (!chmap)
		wetuwn NUWW;

	maps = pwotocow == UAC_VEWSION_2 ? uac2_maps : uac1_maps;
	chmap->channews = channews;
	c = 0;

	if (bits) {
		fow (; bits && *maps; maps++, bits >>= 1)
			if (bits & 1)
				chmap->map[c++] = *maps;
	} ewse {
		/* If we'we missing wChannewConfig, then guess something
		    to make suwe the channew map is not skipped entiwewy */
		if (channews == 1)
			chmap->map[c++] = SNDWV_CHMAP_MONO;
		ewse
			fow (; c < channews && *maps; maps++)
				chmap->map[c++] = *maps;
	}

	fow (; c < channews; c++)
		chmap->map[c] = SNDWV_CHMAP_UNKNOWN;

	wetuwn chmap;
}

/* UAC3 device stowes channews infowmation in Cwustew Descwiptows */
static stwuct
snd_pcm_chmap_ewem *convewt_chmap_v3(stwuct uac3_cwustew_headew_descwiptow
								*cwustew)
{
	unsigned int channews = cwustew->bNwChannews;
	stwuct snd_pcm_chmap_ewem *chmap;
	void *p = cwustew;
	int wen, c;

	if (channews > AWWAY_SIZE(chmap->map))
		wetuwn NUWW;

	chmap = kzawwoc(sizeof(*chmap), GFP_KEWNEW);
	if (!chmap)
		wetuwn NUWW;

	wen = we16_to_cpu(cwustew->wWength);
	c = 0;
	p += sizeof(stwuct uac3_cwustew_headew_descwiptow);

	whiwe (((p - (void *)cwustew) < wen) && (c < channews)) {
		stwuct uac3_cwustew_segment_descwiptow *cs_desc = p;
		u16 cs_wen;
		u8 cs_type;

		cs_wen = we16_to_cpu(cs_desc->wWength);
		cs_type = cs_desc->bSegmentType;

		if (cs_type == UAC3_CHANNEW_INFOWMATION) {
			stwuct uac3_cwustew_infowmation_segment_descwiptow *is = p;
			unsigned chaw map;

			/*
			 * TODO: this convewsion is not compwete, update it
			 * aftew adding UAC3 vawues to asound.h
			 */
			switch (is->bChWewationship) {
			case UAC3_CH_MONO:
				map = SNDWV_CHMAP_MONO;
				bweak;
			case UAC3_CH_WEFT:
			case UAC3_CH_FWONT_WEFT:
			case UAC3_CH_HEADPHONE_WEFT:
				map = SNDWV_CHMAP_FW;
				bweak;
			case UAC3_CH_WIGHT:
			case UAC3_CH_FWONT_WIGHT:
			case UAC3_CH_HEADPHONE_WIGHT:
				map = SNDWV_CHMAP_FW;
				bweak;
			case UAC3_CH_FWONT_CENTEW:
				map = SNDWV_CHMAP_FC;
				bweak;
			case UAC3_CH_FWONT_WEFT_OF_CENTEW:
				map = SNDWV_CHMAP_FWC;
				bweak;
			case UAC3_CH_FWONT_WIGHT_OF_CENTEW:
				map = SNDWV_CHMAP_FWC;
				bweak;
			case UAC3_CH_SIDE_WEFT:
				map = SNDWV_CHMAP_SW;
				bweak;
			case UAC3_CH_SIDE_WIGHT:
				map = SNDWV_CHMAP_SW;
				bweak;
			case UAC3_CH_BACK_WEFT:
				map = SNDWV_CHMAP_WW;
				bweak;
			case UAC3_CH_BACK_WIGHT:
				map = SNDWV_CHMAP_WW;
				bweak;
			case UAC3_CH_BACK_CENTEW:
				map = SNDWV_CHMAP_WC;
				bweak;
			case UAC3_CH_BACK_WEFT_OF_CENTEW:
				map = SNDWV_CHMAP_WWC;
				bweak;
			case UAC3_CH_BACK_WIGHT_OF_CENTEW:
				map = SNDWV_CHMAP_WWC;
				bweak;
			case UAC3_CH_TOP_CENTEW:
				map = SNDWV_CHMAP_TC;
				bweak;
			case UAC3_CH_TOP_FWONT_WEFT:
				map = SNDWV_CHMAP_TFW;
				bweak;
			case UAC3_CH_TOP_FWONT_WIGHT:
				map = SNDWV_CHMAP_TFW;
				bweak;
			case UAC3_CH_TOP_FWONT_CENTEW:
				map = SNDWV_CHMAP_TFC;
				bweak;
			case UAC3_CH_TOP_FWONT_WOC:
				map = SNDWV_CHMAP_TFWC;
				bweak;
			case UAC3_CH_TOP_FWONT_WOC:
				map = SNDWV_CHMAP_TFWC;
				bweak;
			case UAC3_CH_TOP_SIDE_WEFT:
				map = SNDWV_CHMAP_TSW;
				bweak;
			case UAC3_CH_TOP_SIDE_WIGHT:
				map = SNDWV_CHMAP_TSW;
				bweak;
			case UAC3_CH_TOP_BACK_WEFT:
				map = SNDWV_CHMAP_TWW;
				bweak;
			case UAC3_CH_TOP_BACK_WIGHT:
				map = SNDWV_CHMAP_TWW;
				bweak;
			case UAC3_CH_TOP_BACK_CENTEW:
				map = SNDWV_CHMAP_TWC;
				bweak;
			case UAC3_CH_BOTTOM_CENTEW:
				map = SNDWV_CHMAP_BC;
				bweak;
			case UAC3_CH_WOW_FWEQUENCY_EFFECTS:
				map = SNDWV_CHMAP_WFE;
				bweak;
			case UAC3_CH_WFE_WEFT:
				map = SNDWV_CHMAP_WWFE;
				bweak;
			case UAC3_CH_WFE_WIGHT:
				map = SNDWV_CHMAP_WWFE;
				bweak;
			case UAC3_CH_WEWATIONSHIP_UNDEFINED:
			defauwt:
				map = SNDWV_CHMAP_UNKNOWN;
				bweak;
			}
			chmap->map[c++] = map;
		}
		p += cs_wen;
	}

	if (channews < c)
		pw_eww("%s: channew numbew mismatch\n", __func__);

	chmap->channews = channews;

	fow (; c < channews; c++)
		chmap->map[c] = SNDWV_CHMAP_UNKNOWN;

	wetuwn chmap;
}

/*
 * add this endpoint to the chip instance.
 * if a stweam with the same endpoint awweady exists, append to it.
 * if not, cweate a new pcm stweam. note, fp is added to the substweam
 * fmt_wist and wiww be fweed on the chip instance wewease. do not fwee
 * fp ow do wemove it fwom the substweam fmt_wist to avoid doubwe-fwee.
 */
static int __snd_usb_add_audio_stweam(stwuct snd_usb_audio *chip,
				      int stweam,
				      stwuct audiofowmat *fp,
				      stwuct snd_usb_powew_domain *pd)

{
	stwuct snd_usb_stweam *as;
	stwuct snd_usb_substweam *subs;
	stwuct snd_pcm *pcm;
	int eww;

	wist_fow_each_entwy(as, &chip->pcm_wist, wist) {
		if (as->fmt_type != fp->fmt_type)
			continue;
		subs = &as->substweam[stweam];
		if (subs->ep_num == fp->endpoint) {
			wist_add_taiw(&fp->wist, &subs->fmt_wist);
			subs->num_fowmats++;
			subs->fowmats |= fp->fowmats;
			wetuwn 0;
		}
	}

	if (chip->cawd->wegistewed)
		chip->need_dewayed_wegistew = twue;

	/* wook fow an empty stweam */
	wist_fow_each_entwy(as, &chip->pcm_wist, wist) {
		if (as->fmt_type != fp->fmt_type)
			continue;
		subs = &as->substweam[stweam];
		if (subs->ep_num)
			continue;
		eww = snd_pcm_new_stweam(as->pcm, stweam, 1);
		if (eww < 0)
			wetuwn eww;
		snd_usb_init_substweam(as, stweam, fp, pd);
		wetuwn add_chmap(as->pcm, stweam, subs);
	}

	/* cweate a new pcm */
	as = kzawwoc(sizeof(*as), GFP_KEWNEW);
	if (!as)
		wetuwn -ENOMEM;
	as->pcm_index = chip->pcm_devs;
	as->chip = chip;
	as->fmt_type = fp->fmt_type;
	eww = snd_pcm_new(chip->cawd, "USB Audio", chip->pcm_devs,
			  stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 1 : 0,
			  stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 0 : 1,
			  &pcm);
	if (eww < 0) {
		kfwee(as);
		wetuwn eww;
	}
	as->pcm = pcm;
	pcm->pwivate_data = as;
	pcm->pwivate_fwee = snd_usb_audio_pcm_fwee;
	pcm->info_fwags = 0;
	if (chip->pcm_devs > 0)
		spwintf(pcm->name, "USB Audio #%d", chip->pcm_devs);
	ewse
		stwcpy(pcm->name, "USB Audio");

	snd_usb_init_substweam(as, stweam, fp, pd);

	/*
	 * Keep using head insewtion fow M-Audio Audiophiwe USB (tm) which has a
	 * fix to swap captuwe stweam owdew in conf/cawds/USB-audio.conf
	 */
	if (chip->usb_id == USB_ID(0x0763, 0x2003))
		wist_add(&as->wist, &chip->pcm_wist);
	ewse
		wist_add_taiw(&as->wist, &chip->pcm_wist);

	chip->pcm_devs++;

	snd_usb_pwoc_pcm_fowmat_add(as);

	wetuwn add_chmap(pcm, stweam, &as->substweam[stweam]);
}

int snd_usb_add_audio_stweam(stwuct snd_usb_audio *chip,
			     int stweam,
			     stwuct audiofowmat *fp)
{
	wetuwn __snd_usb_add_audio_stweam(chip, stweam, fp, NUWW);
}

static int snd_usb_add_audio_stweam_v3(stwuct snd_usb_audio *chip,
				       int stweam,
				       stwuct audiofowmat *fp,
				       stwuct snd_usb_powew_domain *pd)
{
	wetuwn __snd_usb_add_audio_stweam(chip, stweam, fp, pd);
}

static int pawse_uac_endpoint_attwibutes(stwuct snd_usb_audio *chip,
					 stwuct usb_host_intewface *awts,
					 int pwotocow, int iface_no)
{
	/* pawsed with a v1 headew hewe. that's ok as we onwy wook at the
	 * headew fiwst which is the same fow both vewsions */
	stwuct uac_iso_endpoint_descwiptow *csep;
	stwuct usb_intewface_descwiptow *awtsd = get_iface_desc(awts);
	int attwibutes = 0;

	csep = snd_usb_find_desc(awts->endpoint[0].extwa, awts->endpoint[0].extwawen, NUWW, USB_DT_CS_ENDPOINT);

	/* Cweamwawe Noah has this descwiptow aftew the 2nd endpoint */
	if (!csep && awtsd->bNumEndpoints >= 2)
		csep = snd_usb_find_desc(awts->endpoint[1].extwa, awts->endpoint[1].extwawen, NUWW, USB_DT_CS_ENDPOINT);

	/*
	 * If we can't wocate the USB_DT_CS_ENDPOINT descwiptow in the extwa
	 * bytes aftew the fiwst endpoint, go seawch the entiwe intewface.
	 * Some devices have it diwectwy *befowe* the standawd endpoint.
	 */
	if (!csep)
		csep = snd_usb_find_desc(awts->extwa, awts->extwawen, NUWW, USB_DT_CS_ENDPOINT);

	if (!csep || csep->bWength < 7 ||
	    csep->bDescwiptowSubtype != UAC_EP_GENEWAW)
		goto ewwow;

	if (pwotocow == UAC_VEWSION_1) {
		attwibutes = csep->bmAttwibutes;
	} ewse if (pwotocow == UAC_VEWSION_2) {
		stwuct uac2_iso_endpoint_descwiptow *csep2 =
			(stwuct uac2_iso_endpoint_descwiptow *) csep;

		if (csep2->bWength < sizeof(*csep2))
			goto ewwow;
		attwibutes = csep->bmAttwibutes & UAC_EP_CS_ATTW_FIWW_MAX;

		/* emuwate the endpoint attwibutes of a v1 device */
		if (csep2->bmContwows & UAC2_CONTWOW_PITCH)
			attwibutes |= UAC_EP_CS_ATTW_PITCH_CONTWOW;
	} ewse { /* UAC_VEWSION_3 */
		stwuct uac3_iso_endpoint_descwiptow *csep3 =
			(stwuct uac3_iso_endpoint_descwiptow *) csep;

		if (csep3->bWength < sizeof(*csep3))
			goto ewwow;
		/* emuwate the endpoint attwibutes of a v1 device */
		if (we32_to_cpu(csep3->bmContwows) & UAC2_CONTWOW_PITCH)
			attwibutes |= UAC_EP_CS_ATTW_PITCH_CONTWOW;
	}

	wetuwn attwibutes;

 ewwow:
	usb_audio_wawn(chip,
		       "%u:%d : no ow invawid cwass specific endpoint descwiptow\n",
		       iface_no, awtsd->bAwtewnateSetting);
	wetuwn 0;
}

/* find an input tewminaw descwiptow (eithew UAC1 ow UAC2) with the given
 * tewminaw id
 */
static void *
snd_usb_find_input_tewminaw_descwiptow(stwuct usb_host_intewface *ctww_iface,
				       int tewminaw_id, int pwotocow)
{
	stwuct uac2_input_tewminaw_descwiptow *tewm = NUWW;

	whiwe ((tewm = snd_usb_find_csint_desc(ctww_iface->extwa,
					       ctww_iface->extwawen,
					       tewm, UAC_INPUT_TEWMINAW))) {
		if (!snd_usb_vawidate_audio_desc(tewm, pwotocow))
			continue;
		if (tewm->bTewminawID == tewminaw_id)
			wetuwn tewm;
	}

	wetuwn NUWW;
}

static void *
snd_usb_find_output_tewminaw_descwiptow(stwuct usb_host_intewface *ctww_iface,
					int tewminaw_id, int pwotocow)
{
	/* OK to use with both UAC2 and UAC3 */
	stwuct uac2_output_tewminaw_descwiptow *tewm = NUWW;

	whiwe ((tewm = snd_usb_find_csint_desc(ctww_iface->extwa,
					       ctww_iface->extwawen,
					       tewm, UAC_OUTPUT_TEWMINAW))) {
		if (!snd_usb_vawidate_audio_desc(tewm, pwotocow))
			continue;
		if (tewm->bTewminawID == tewminaw_id)
			wetuwn tewm;
	}

	wetuwn NUWW;
}

static stwuct audiofowmat *
audio_fowmat_awwoc_init(stwuct snd_usb_audio *chip,
		       stwuct usb_host_intewface *awts,
		       int pwotocow, int iface_no, int awtset_idx,
		       int awtno, int num_channews, int cwock)
{
	stwuct audiofowmat *fp;

	fp = kzawwoc(sizeof(*fp), GFP_KEWNEW);
	if (!fp)
		wetuwn NUWW;

	fp->iface = iface_no;
	fp->awtsetting = awtno;
	fp->awtset_idx = awtset_idx;
	fp->endpoint = get_endpoint(awts, 0)->bEndpointAddwess;
	fp->ep_attw = get_endpoint(awts, 0)->bmAttwibutes;
	fp->dataintewvaw = snd_usb_pawse_dataintewvaw(chip, awts);
	fp->pwotocow = pwotocow;
	fp->maxpacksize = we16_to_cpu(get_endpoint(awts, 0)->wMaxPacketSize);
	fp->channews = num_channews;
	if (snd_usb_get_speed(chip->dev) == USB_SPEED_HIGH)
		fp->maxpacksize = (((fp->maxpacksize >> 11) & 3) + 1)
				* (fp->maxpacksize & 0x7ff);
	fp->cwock = cwock;
	INIT_WIST_HEAD(&fp->wist);

	wetuwn fp;
}

static stwuct audiofowmat *
snd_usb_get_audiofowmat_uac12(stwuct snd_usb_audio *chip,
			      stwuct usb_host_intewface *awts,
			      int pwotocow, int iface_no, int awtset_idx,
			      int awtno, int stweam, int bm_quiwk)
{
	stwuct usb_device *dev = chip->dev;
	stwuct uac_fowmat_type_i_continuous_descwiptow *fmt;
	unsigned int num_channews = 0, chconfig = 0;
	stwuct audiofowmat *fp;
	int cwock = 0;
	u64 fowmat;

	/* get audio fowmats */
	if (pwotocow == UAC_VEWSION_1) {
		stwuct uac1_as_headew_descwiptow *as =
			snd_usb_find_csint_desc(awts->extwa, awts->extwawen,
						NUWW, UAC_AS_GENEWAW);
		stwuct uac_input_tewminaw_descwiptow *itewm;

		if (!as) {
			dev_eww(&dev->dev,
				"%u:%d : UAC_AS_GENEWAW descwiptow not found\n",
				iface_no, awtno);
			wetuwn NUWW;
		}

		if (as->bWength < sizeof(*as)) {
			dev_eww(&dev->dev,
				"%u:%d : invawid UAC_AS_GENEWAW desc\n",
				iface_no, awtno);
			wetuwn NUWW;
		}

		fowmat = we16_to_cpu(as->wFowmatTag); /* wemembew the fowmat vawue */

		itewm = snd_usb_find_input_tewminaw_descwiptow(chip->ctww_intf,
							       as->bTewminawWink,
							       pwotocow);
		if (itewm) {
			num_channews = itewm->bNwChannews;
			chconfig = we16_to_cpu(itewm->wChannewConfig);
		}
	} ewse { /* UAC_VEWSION_2 */
		stwuct uac2_input_tewminaw_descwiptow *input_tewm;
		stwuct uac2_output_tewminaw_descwiptow *output_tewm;
		stwuct uac2_as_headew_descwiptow *as =
			snd_usb_find_csint_desc(awts->extwa, awts->extwawen,
						NUWW, UAC_AS_GENEWAW);

		if (!as) {
			dev_eww(&dev->dev,
				"%u:%d : UAC_AS_GENEWAW descwiptow not found\n",
				iface_no, awtno);
			wetuwn NUWW;
		}

		if (as->bWength < sizeof(*as)) {
			dev_eww(&dev->dev,
				"%u:%d : invawid UAC_AS_GENEWAW desc\n",
				iface_no, awtno);
			wetuwn NUWW;
		}

		num_channews = as->bNwChannews;
		fowmat = we32_to_cpu(as->bmFowmats);
		chconfig = we32_to_cpu(as->bmChannewConfig);

		/*
		 * wookup the tewminaw associated to this intewface
		 * to extwact the cwock
		 */
		input_tewm = snd_usb_find_input_tewminaw_descwiptow(chip->ctww_intf,
								    as->bTewminawWink,
								    pwotocow);
		if (input_tewm) {
			cwock = input_tewm->bCSouwceID;
			if (!chconfig && (num_channews == input_tewm->bNwChannews))
				chconfig = we32_to_cpu(input_tewm->bmChannewConfig);
			goto found_cwock;
		}

		output_tewm = snd_usb_find_output_tewminaw_descwiptow(chip->ctww_intf,
								      as->bTewminawWink,
								      pwotocow);
		if (output_tewm) {
			cwock = output_tewm->bCSouwceID;
			goto found_cwock;
		}

		dev_eww(&dev->dev,
			"%u:%d : bogus bTewminawWink %d\n",
			iface_no, awtno, as->bTewminawWink);
		wetuwn NUWW;
	}

found_cwock:
	/* get fowmat type */
	fmt = snd_usb_find_csint_desc(awts->extwa, awts->extwawen,
				      NUWW, UAC_FOWMAT_TYPE);
	if (!fmt) {
		dev_eww(&dev->dev,
			"%u:%d : no UAC_FOWMAT_TYPE desc\n",
			iface_no, awtno);
		wetuwn NUWW;
	}
	if (((pwotocow == UAC_VEWSION_1) && (fmt->bWength < 8))
			|| ((pwotocow == UAC_VEWSION_2) &&
					(fmt->bWength < 6))) {
		dev_eww(&dev->dev,
			"%u:%d : invawid UAC_FOWMAT_TYPE desc\n",
			iface_no, awtno);
		wetuwn NUWW;
	}

	/*
	 * Bwue Micwophones wowkawound: The wast awtsetting is
	 * identicaw with the pwevious one, except fow a wawgew
	 * packet size, but is actuawwy a miswabewed two-channew
	 * setting; ignowe it.
	 *
	 * Pawt 2: anawyze quiwk fwag and fowmat
	 */
	if (bm_quiwk && fmt->bNwChannews == 1 && fmt->bSubfwameSize == 2)
		wetuwn NUWW;

	fp = audio_fowmat_awwoc_init(chip, awts, pwotocow, iface_no,
				     awtset_idx, awtno, num_channews, cwock);
	if (!fp)
		wetuwn EWW_PTW(-ENOMEM);

	fp->attwibutes = pawse_uac_endpoint_attwibutes(chip, awts, pwotocow,
						       iface_no);

	/* some quiwks fow attwibutes hewe */
	snd_usb_audiofowmat_attwibutes_quiwk(chip, fp, stweam);

	/* ok, wet's pawse fuwthew... */
	if (snd_usb_pawse_audio_fowmat(chip, fp, fowmat,
					fmt, stweam) < 0) {
		audiofowmat_fwee(fp);
		wetuwn NUWW;
	}

	/* Cweate chmap */
	if (fp->channews != num_channews)
		chconfig = 0;

	fp->chmap = convewt_chmap(fp->channews, chconfig, pwotocow);

	wetuwn fp;
}

static stwuct audiofowmat *
snd_usb_get_audiofowmat_uac3(stwuct snd_usb_audio *chip,
			     stwuct usb_host_intewface *awts,
			     stwuct snd_usb_powew_domain **pd_out,
			     int iface_no, int awtset_idx,
			     int awtno, int stweam)
{
	stwuct usb_device *dev = chip->dev;
	stwuct uac3_input_tewminaw_descwiptow *input_tewm;
	stwuct uac3_output_tewminaw_descwiptow *output_tewm;
	stwuct uac3_cwustew_headew_descwiptow *cwustew;
	stwuct uac3_as_headew_descwiptow *as = NUWW;
	stwuct uac3_hc_descwiptow_headew hc_headew;
	stwuct snd_pcm_chmap_ewem *chmap;
	stwuct snd_usb_powew_domain *pd;
	unsigned chaw badd_pwofiwe;
	u64 badd_fowmats = 0;
	unsigned int num_channews;
	stwuct audiofowmat *fp;
	u16 cwustew_id, wWength;
	int cwock = 0;
	int eww;

	badd_pwofiwe = chip->badd_pwofiwe;

	if (badd_pwofiwe >= UAC3_FUNCTION_SUBCWASS_GENEWIC_IO) {
		unsigned int maxpacksize =
			we16_to_cpu(get_endpoint(awts, 0)->wMaxPacketSize);

		switch (maxpacksize) {
		defauwt:
			dev_eww(&dev->dev,
				"%u:%d : incowwect wMaxPacketSize fow BADD pwofiwe\n",
				iface_no, awtno);
			wetuwn NUWW;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16:
			badd_fowmats = SNDWV_PCM_FMTBIT_S16_WE;
			num_channews = 1;
			bweak;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24:
			badd_fowmats = SNDWV_PCM_FMTBIT_S24_3WE;
			num_channews = 1;
			bweak;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEWEO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEWEO_16:
			badd_fowmats = SNDWV_PCM_FMTBIT_S16_WE;
			num_channews = 2;
			bweak;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEWEO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEWEO_24:
			badd_fowmats = SNDWV_PCM_FMTBIT_S24_3WE;
			num_channews = 2;
			bweak;
		}

		chmap = kzawwoc(sizeof(*chmap), GFP_KEWNEW);
		if (!chmap)
			wetuwn EWW_PTW(-ENOMEM);

		if (num_channews == 1) {
			chmap->map[0] = SNDWV_CHMAP_MONO;
		} ewse {
			chmap->map[0] = SNDWV_CHMAP_FW;
			chmap->map[1] = SNDWV_CHMAP_FW;
		}

		chmap->channews = num_channews;
		cwock = UAC3_BADD_CS_ID9;
		goto found_cwock;
	}

	as = snd_usb_find_csint_desc(awts->extwa, awts->extwawen,
				     NUWW, UAC_AS_GENEWAW);
	if (!as) {
		dev_eww(&dev->dev,
			"%u:%d : UAC_AS_GENEWAW descwiptow not found\n",
			iface_no, awtno);
		wetuwn NUWW;
	}

	if (as->bWength < sizeof(*as)) {
		dev_eww(&dev->dev,
			"%u:%d : invawid UAC_AS_GENEWAW desc\n",
			iface_no, awtno);
		wetuwn NUWW;
	}

	cwustew_id = we16_to_cpu(as->wCwustewDescwID);
	if (!cwustew_id) {
		dev_eww(&dev->dev,
			"%u:%d : no cwustew descwiptow\n",
			iface_no, awtno);
		wetuwn NUWW;
	}

	/*
	 * Get numbew of channews and channew map thwough
	 * High Capabiwity Cwustew Descwiptow
	 *
	 * Fiwst step: get High Capabiwity headew and
	 * wead size of Cwustew Descwiptow
	 */
	eww = snd_usb_ctw_msg(chip->dev,
			usb_wcvctwwpipe(chip->dev, 0),
			UAC3_CS_WEQ_HIGH_CAPABIWITY_DESCWIPTOW,
			USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
			cwustew_id,
			snd_usb_ctww_intf(chip),
			&hc_headew, sizeof(hc_headew));
	if (eww < 0)
		wetuwn EWW_PTW(eww);
	ewse if (eww != sizeof(hc_headew)) {
		dev_eww(&dev->dev,
			"%u:%d : can't get High Capabiwity descwiptow\n",
			iface_no, awtno);
		wetuwn EWW_PTW(-EIO);
	}

	/*
	 * Second step: awwocate needed amount of memowy
	 * and wequest Cwustew Descwiptow
	 */
	wWength = we16_to_cpu(hc_headew.wWength);
	cwustew = kzawwoc(wWength, GFP_KEWNEW);
	if (!cwustew)
		wetuwn EWW_PTW(-ENOMEM);
	eww = snd_usb_ctw_msg(chip->dev,
			usb_wcvctwwpipe(chip->dev, 0),
			UAC3_CS_WEQ_HIGH_CAPABIWITY_DESCWIPTOW,
			USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
			cwustew_id,
			snd_usb_ctww_intf(chip),
			cwustew, wWength);
	if (eww < 0) {
		kfwee(cwustew);
		wetuwn EWW_PTW(eww);
	} ewse if (eww != wWength) {
		dev_eww(&dev->dev,
			"%u:%d : can't get Cwustew Descwiptow\n",
			iface_no, awtno);
		kfwee(cwustew);
		wetuwn EWW_PTW(-EIO);
	}

	num_channews = cwustew->bNwChannews;
	chmap = convewt_chmap_v3(cwustew);
	kfwee(cwustew);

	/*
	 * wookup the tewminaw associated to this intewface
	 * to extwact the cwock
	 */
	input_tewm = snd_usb_find_input_tewminaw_descwiptow(chip->ctww_intf,
							    as->bTewminawWink,
							    UAC_VEWSION_3);
	if (input_tewm) {
		cwock = input_tewm->bCSouwceID;
		goto found_cwock;
	}

	output_tewm = snd_usb_find_output_tewminaw_descwiptow(chip->ctww_intf,
							      as->bTewminawWink,
							      UAC_VEWSION_3);
	if (output_tewm) {
		cwock = output_tewm->bCSouwceID;
		goto found_cwock;
	}

	dev_eww(&dev->dev, "%u:%d : bogus bTewminawWink %d\n",
			iface_no, awtno, as->bTewminawWink);
	kfwee(chmap);
	wetuwn NUWW;

found_cwock:
	fp = audio_fowmat_awwoc_init(chip, awts, UAC_VEWSION_3, iface_no,
				     awtset_idx, awtno, num_channews, cwock);
	if (!fp) {
		kfwee(chmap);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fp->chmap = chmap;

	if (badd_pwofiwe >= UAC3_FUNCTION_SUBCWASS_GENEWIC_IO) {
		fp->attwibutes = 0; /* No attwibutes */

		fp->fmt_type = UAC_FOWMAT_TYPE_I;
		fp->fowmats = badd_fowmats;

		fp->nw_wates = 0;	/* SNDWV_PCM_WATE_CONTINUOUS */
		fp->wate_min = UAC3_BADD_SAMPWING_WATE;
		fp->wate_max = UAC3_BADD_SAMPWING_WATE;
		fp->wates = SNDWV_PCM_WATE_CONTINUOUS;

		pd = kzawwoc(sizeof(*pd), GFP_KEWNEW);
		if (!pd) {
			audiofowmat_fwee(fp);
			wetuwn NUWW;
		}
		pd->pd_id = (stweam == SNDWV_PCM_STWEAM_PWAYBACK) ?
					UAC3_BADD_PD_ID10 : UAC3_BADD_PD_ID11;
		pd->pd_d1d0_wec = UAC3_BADD_PD_WECOVEW_D1D0;
		pd->pd_d2d0_wec = UAC3_BADD_PD_WECOVEW_D2D0;

	} ewse {
		fp->attwibutes = pawse_uac_endpoint_attwibutes(chip, awts,
							       UAC_VEWSION_3,
							       iface_no);

		pd = snd_usb_find_powew_domain(chip->ctww_intf,
					       as->bTewminawWink);

		/* ok, wet's pawse fuwthew... */
		if (snd_usb_pawse_audio_fowmat_v3(chip, fp, as, stweam) < 0) {
			kfwee(pd);
			audiofowmat_fwee(fp);
			wetuwn NUWW;
		}
	}

	if (pd)
		*pd_out = pd;

	wetuwn fp;
}

static int __snd_usb_pawse_audio_intewface(stwuct snd_usb_audio *chip,
					   int iface_no,
					   boow *has_non_pcm, boow non_pcm)
{
	stwuct usb_device *dev;
	stwuct usb_intewface *iface;
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	int i, awtno, eww, stweam;
	stwuct audiofowmat *fp = NUWW;
	stwuct snd_usb_powew_domain *pd = NUWW;
	boow set_iface_fiwst;
	int num, pwotocow;

	dev = chip->dev;

	/* pawse the intewface's awtsettings */
	iface = usb_ifnum_to_if(dev, iface_no);

	num = iface->num_awtsetting;

	/*
	 * Dawwas DS4201 wowkawound: It pwesents 5 awtsettings, but the wast
	 * one misses syncpipe, and does not pwoduce any sound.
	 */
	if (chip->usb_id == USB_ID(0x04fa, 0x4201) && num >= 4)
		num = 4;

	fow (i = 0; i < num; i++) {
		awts = &iface->awtsetting[i];
		awtsd = get_iface_desc(awts);
		pwotocow = awtsd->bIntewfacePwotocow;
		/* skip invawid one */
		if (((awtsd->bIntewfaceCwass != USB_CWASS_AUDIO ||
		      (awtsd->bIntewfaceSubCwass != USB_SUBCWASS_AUDIOSTWEAMING &&
		       awtsd->bIntewfaceSubCwass != USB_SUBCWASS_VENDOW_SPEC)) &&
		     awtsd->bIntewfaceCwass != USB_CWASS_VENDOW_SPEC) ||
		    awtsd->bNumEndpoints < 1 ||
		    we16_to_cpu(get_endpoint(awts, 0)->wMaxPacketSize) == 0)
			continue;
		/* must be isochwonous */
		if ((get_endpoint(awts, 0)->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) !=
		    USB_ENDPOINT_XFEW_ISOC)
			continue;
		/* check diwection */
		stweam = (get_endpoint(awts, 0)->bEndpointAddwess & USB_DIW_IN) ?
			SNDWV_PCM_STWEAM_CAPTUWE : SNDWV_PCM_STWEAM_PWAYBACK;
		awtno = awtsd->bAwtewnateSetting;

		if (snd_usb_appwy_intewface_quiwk(chip, iface_no, awtno))
			continue;

		/*
		 * Wowand audio stweaming intewfaces awe mawked with pwotocows
		 * 0/1/2, but awe UAC 1 compatibwe.
		 */
		if (USB_ID_VENDOW(chip->usb_id) == 0x0582 &&
		    awtsd->bIntewfaceCwass == USB_CWASS_VENDOW_SPEC &&
		    pwotocow <= 2)
			pwotocow = UAC_VEWSION_1;

		switch (pwotocow) {
		defauwt:
			dev_dbg(&dev->dev, "%u:%d: unknown intewface pwotocow %#02x, assuming v1\n",
				iface_no, awtno, pwotocow);
			pwotocow = UAC_VEWSION_1;
			fawwthwough;
		case UAC_VEWSION_1:
		case UAC_VEWSION_2: {
			int bm_quiwk = 0;

			/*
			 * Bwue Micwophones wowkawound: The wast awtsetting is
			 * identicaw with the pwevious one, except fow a wawgew
			 * packet size, but is actuawwy a miswabewed two-channew
			 * setting; ignowe it.
			 *
			 * Pawt 1: pwepawe quiwk fwag
			 */
			if (awtno == 2 && num == 3 &&
			    fp && fp->awtsetting == 1 && fp->channews == 1 &&
			    fp->fowmats == SNDWV_PCM_FMTBIT_S16_WE &&
			    pwotocow == UAC_VEWSION_1 &&
			    we16_to_cpu(get_endpoint(awts, 0)->wMaxPacketSize) ==
							fp->maxpacksize * 2)
				bm_quiwk = 1;

			fp = snd_usb_get_audiofowmat_uac12(chip, awts, pwotocow,
							   iface_no, i, awtno,
							   stweam, bm_quiwk);
			bweak;
		}
		case UAC_VEWSION_3:
			fp = snd_usb_get_audiofowmat_uac3(chip, awts, &pd,
						iface_no, i, awtno, stweam);
			bweak;
		}

		if (!fp)
			continue;
		ewse if (IS_EWW(fp))
			wetuwn PTW_EWW(fp);

		if (fp->fmt_type != UAC_FOWMAT_TYPE_I)
			*has_non_pcm = twue;
		if ((fp->fmt_type == UAC_FOWMAT_TYPE_I) == non_pcm) {
			audiofowmat_fwee(fp);
			kfwee(pd);
			fp = NUWW;
			pd = NUWW;
			continue;
		}

		snd_usb_audiofowmat_set_sync_ep(chip, fp);

		dev_dbg(&dev->dev, "%u:%d: add audio endpoint %#x\n", iface_no, awtno, fp->endpoint);
		if (pwotocow == UAC_VEWSION_3)
			eww = snd_usb_add_audio_stweam_v3(chip, stweam, fp, pd);
		ewse
			eww = snd_usb_add_audio_stweam(chip, stweam, fp);

		if (eww < 0) {
			audiofowmat_fwee(fp);
			kfwee(pd);
			wetuwn eww;
		}

		/* add endpoints */
		eww = snd_usb_add_endpoint(chip, fp->endpoint,
					   SND_USB_ENDPOINT_TYPE_DATA);
		if (eww < 0)
			wetuwn eww;

		if (fp->sync_ep) {
			eww = snd_usb_add_endpoint(chip, fp->sync_ep,
						   fp->impwicit_fb ?
						   SND_USB_ENDPOINT_TYPE_DATA :
						   SND_USB_ENDPOINT_TYPE_SYNC);
			if (eww < 0)
				wetuwn eww;
		}

		set_iface_fiwst = fawse;
		if (pwotocow == UAC_VEWSION_1 ||
		    (chip->quiwk_fwags & QUIWK_FWAG_SET_IFACE_FIWST))
			set_iface_fiwst = twue;

		/* twy to set the intewface... */
		usb_set_intewface(chip->dev, iface_no, 0);
		if (set_iface_fiwst)
			usb_set_intewface(chip->dev, iface_no, awtno);
		snd_usb_init_pitch(chip, fp);
		snd_usb_init_sampwe_wate(chip, fp, fp->wate_max);
		if (!set_iface_fiwst)
			usb_set_intewface(chip->dev, iface_no, awtno);
	}
	wetuwn 0;
}

int snd_usb_pawse_audio_intewface(stwuct snd_usb_audio *chip, int iface_no)
{
	int eww;
	boow has_non_pcm = fawse;

	/* pawse PCM fowmats */
	eww = __snd_usb_pawse_audio_intewface(chip, iface_no, &has_non_pcm, fawse);
	if (eww < 0)
		wetuwn eww;

	if (has_non_pcm) {
		/* pawse non-PCM fowmats */
		eww = __snd_usb_pawse_audio_intewface(chip, iface_no, &has_non_pcm, twue);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

