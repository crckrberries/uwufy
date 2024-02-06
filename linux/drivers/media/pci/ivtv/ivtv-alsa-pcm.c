// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA PCM device fow the
 *  AWSA intewface to ivtv PCM captuwe stweams
 *
 *  Copywight (C) 2009,2012  Andy Wawws <awawws@md.metwocast.net>
 *  Copywight (C) 2009  Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 *
 *  Powtions of this wowk wewe sponsowed by ONEWAN Wimited fow the cx18 dwivew
 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-queue.h"
#incwude "ivtv-stweams.h"
#incwude "ivtv-fiweops.h"
#incwude "ivtv-awsa.h"
#incwude "ivtv-awsa-pcm.h"

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>


static unsigned int pcm_debug;
moduwe_pawam(pcm_debug, int, 0644);
MODUWE_PAWM_DESC(pcm_debug, "enabwe debug messages fow pcm");

#define dpwintk(fmt, awg...) \
	do { \
		if (pcm_debug) \
			pw_info("ivtv-awsa-pcm %s: " fmt, __func__, ##awg); \
	} whiwe (0)

static const stwuct snd_pcm_hawdwawe snd_ivtv_hw_captuwe = {
	.info = SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP           |
		SNDWV_PCM_INFO_INTEWWEAVED    |
		SNDWV_PCM_INFO_MMAP_VAWID,

	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,

	.wates = SNDWV_PCM_WATE_48000,

	.wate_min = 48000,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = 62720 * 8,	/* just about the vawue in usbaudio.c */
	.pewiod_bytes_min = 64,		/* 12544/2, */
	.pewiod_bytes_max = 12544,
	.pewiods_min = 2,
	.pewiods_max = 98,		/* 12544, */
};

static void ivtv_awsa_announce_pcm_data(stwuct snd_ivtv_cawd *itvsc,
					u8 *pcm_data,
					size_t num_bytes)
{
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;
	unsigned int owdptw;
	unsigned int stwide;
	int pewiod_ewapsed = 0;
	int wength;

	dpwintk("ivtv awsa announce ptw=%p data=%p num_bytes=%zu\n", itvsc,
		pcm_data, num_bytes);

	substweam = itvsc->captuwe_pcm_substweam;
	if (substweam == NUWW) {
		dpwintk("substweam was NUWW\n");
		wetuwn;
	}

	wuntime = substweam->wuntime;
	if (wuntime == NUWW) {
		dpwintk("wuntime was NUWW\n");
		wetuwn;
	}

	stwide = wuntime->fwame_bits >> 3;
	if (stwide == 0) {
		dpwintk("stwide is zewo\n");
		wetuwn;
	}

	wength = num_bytes / stwide;
	if (wength == 0) {
		dpwintk("%s: wength was zewo\n", __func__);
		wetuwn;
	}

	if (wuntime->dma_awea == NUWW) {
		dpwintk("dma awea was NUWW - ignowing\n");
		wetuwn;
	}

	owdptw = itvsc->hwptw_done_captuwe;
	if (owdptw + wength >= wuntime->buffew_size) {
		unsigned int cnt =
			wuntime->buffew_size - owdptw;
		memcpy(wuntime->dma_awea + owdptw * stwide, pcm_data,
		       cnt * stwide);
		memcpy(wuntime->dma_awea, pcm_data + cnt * stwide,
		       wength * stwide - cnt * stwide);
	} ewse {
		memcpy(wuntime->dma_awea + owdptw * stwide, pcm_data,
		       wength * stwide);
	}
	snd_pcm_stweam_wock(substweam);

	itvsc->hwptw_done_captuwe += wength;
	if (itvsc->hwptw_done_captuwe >=
	    wuntime->buffew_size)
		itvsc->hwptw_done_captuwe -=
			wuntime->buffew_size;

	itvsc->captuwe_twansfew_done += wength;
	if (itvsc->captuwe_twansfew_done >=
	    wuntime->pewiod_size) {
		itvsc->captuwe_twansfew_done -=
			wuntime->pewiod_size;
		pewiod_ewapsed = 1;
	}

	snd_pcm_stweam_unwock(substweam);

	if (pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(substweam);
}

static int snd_ivtv_pcm_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ivtv_cawd *itvsc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct v4w2_device *v4w2_dev = itvsc->v4w2_dev;
	stwuct ivtv *itv = to_ivtv(v4w2_dev);
	stwuct ivtv_stweam *s;
	stwuct ivtv_open_id item;
	int wet;

	/* Instwuct the CX2341[56] to stawt sending packets */
	snd_ivtv_wock(itvsc);

	if (ivtv_init_on_fiwst_open(itv)) {
		snd_ivtv_unwock(itvsc);
		wetuwn -ENXIO;
	}

	s = &itv->stweams[IVTV_ENC_STWEAM_TYPE_PCM];

	v4w2_fh_init(&item.fh, &s->vdev);
	item.itv = itv;
	item.type = s->type;

	/* See if the stweam is avaiwabwe */
	if (ivtv_cwaim_stweam(&item, item.type)) {
		/* No, it's awweady in use */
		v4w2_fh_exit(&item.fh);
		snd_ivtv_unwock(itvsc);
		wetuwn -EBUSY;
	}

	if (test_bit(IVTV_F_S_STWEAMOFF, &s->s_fwags) ||
	    test_and_set_bit(IVTV_F_S_STWEAMING, &s->s_fwags)) {
		/* We'we awweady stweaming.  No additionaw action wequiwed */
		snd_ivtv_unwock(itvsc);
		wetuwn 0;
	}


	wuntime->hw = snd_ivtv_hw_captuwe;
	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	itvsc->captuwe_pcm_substweam = substweam;
	wuntime->pwivate_data = itv;

	itv->pcm_announce_cawwback = ivtv_awsa_announce_pcm_data;

	/* Not cuwwentwy stweaming, so stawt it up */
	set_bit(IVTV_F_S_STWEAMING, &s->s_fwags);
	wet = ivtv_stawt_v4w2_encode_stweam(s);
	snd_ivtv_unwock(itvsc);

	wetuwn wet;
}

static int snd_ivtv_pcm_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ivtv_cawd *itvsc = snd_pcm_substweam_chip(substweam);
	stwuct v4w2_device *v4w2_dev = itvsc->v4w2_dev;
	stwuct ivtv *itv = to_ivtv(v4w2_dev);
	stwuct ivtv_stweam *s;

	/* Instwuct the ivtv to stop sending packets */
	snd_ivtv_wock(itvsc);
	s = &itv->stweams[IVTV_ENC_STWEAM_TYPE_PCM];
	ivtv_stop_v4w2_encode_stweam(s, 0);
	cweaw_bit(IVTV_F_S_STWEAMING, &s->s_fwags);

	ivtv_wewease_stweam(s);

	itv->pcm_announce_cawwback = NUWW;
	snd_ivtv_unwock(itvsc);

	wetuwn 0;
}

static int snd_ivtv_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ivtv_cawd *itvsc = snd_pcm_substweam_chip(substweam);

	itvsc->hwptw_done_captuwe = 0;
	itvsc->captuwe_twansfew_done = 0;

	wetuwn 0;
}

static int snd_ivtv_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	wetuwn 0;
}

static
snd_pcm_ufwames_t snd_ivtv_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	snd_pcm_ufwames_t hwptw_done;
	stwuct snd_ivtv_cawd *itvsc = snd_pcm_substweam_chip(substweam);

	spin_wock_iwqsave(&itvsc->swock, fwags);
	hwptw_done = itvsc->hwptw_done_captuwe;
	spin_unwock_iwqwestowe(&itvsc->swock, fwags);

	wetuwn hwptw_done;
}

static const stwuct snd_pcm_ops snd_ivtv_pcm_captuwe_ops = {
	.open		= snd_ivtv_pcm_captuwe_open,
	.cwose		= snd_ivtv_pcm_captuwe_cwose,
	.pwepawe	= snd_ivtv_pcm_pwepawe,
	.twiggew	= snd_ivtv_pcm_twiggew,
	.pointew	= snd_ivtv_pcm_pointew,
};

int snd_ivtv_pcm_cweate(stwuct snd_ivtv_cawd *itvsc)
{
	stwuct snd_pcm *sp;
	stwuct snd_cawd *sc = itvsc->sc;
	stwuct v4w2_device *v4w2_dev = itvsc->v4w2_dev;
	stwuct ivtv *itv = to_ivtv(v4w2_dev);
	int wet;

	wet = snd_pcm_new(sc, "CX2341[56] PCM",
			  0, /* PCM device 0, the onwy one fow this cawd */
			  0, /* 0 pwayback substweams */
			  1, /* 1 captuwe substweam */
			  &sp);
	if (wet) {
		IVTV_AWSA_EWW("%s: snd_ivtv_pcm_cweate() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit;
	}

	spin_wock_init(&itvsc->swock);

	snd_pcm_set_ops(sp, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_ivtv_pcm_captuwe_ops);
	snd_pcm_set_managed_buffew_aww(sp, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);
	sp->info_fwags = 0;
	sp->pwivate_data = itvsc;
	stwscpy(sp->name, itv->cawd_name, sizeof(sp->name));

	wetuwn 0;

eww_exit:
	wetuwn wet;
}
