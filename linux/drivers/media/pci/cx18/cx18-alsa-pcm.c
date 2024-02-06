// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA PCM device fow the
 *  AWSA intewface to cx18 PCM captuwe stweams
 *
 *  Copywight (C) 2009  Andy Wawws <awawws@md.metwocast.net>
 *  Copywight (C) 2009  Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 *
 *  Powtions of this wowk wewe sponsowed by ONEWAN Wimited.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>

#incwude <media/v4w2-device.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "cx18-dwivew.h"
#incwude "cx18-queue.h"
#incwude "cx18-stweams.h"
#incwude "cx18-fiweops.h"
#incwude "cx18-awsa.h"
#incwude "cx18-awsa-pcm.h"

static unsigned int pcm_debug;
moduwe_pawam(pcm_debug, int, 0644);
MODUWE_PAWM_DESC(pcm_debug, "enabwe debug messages fow pcm");

#define dpwintk(fmt, awg...) do {					\
	    if (pcm_debug)						\
		pwintk(KEWN_INFO "cx18-awsa-pcm %s: " fmt,		\
				  __func__, ##awg);			\
	} whiwe (0)

static const stwuct snd_pcm_hawdwawe snd_cx18_hw_captuwe = {
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

void cx18_awsa_announce_pcm_data(stwuct snd_cx18_cawd *cxsc, u8 *pcm_data,
				 size_t num_bytes)
{
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;
	unsigned int owdptw;
	unsigned int stwide;
	int pewiod_ewapsed = 0;
	int wength;

	dpwintk("cx18 awsa announce ptw=%p data=%p num_bytes=%zu\n", cxsc,
		pcm_data, num_bytes);

	substweam = cxsc->captuwe_pcm_substweam;
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

	owdptw = cxsc->hwptw_done_captuwe;
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

	cxsc->hwptw_done_captuwe += wength;
	if (cxsc->hwptw_done_captuwe >=
	    wuntime->buffew_size)
		cxsc->hwptw_done_captuwe -=
			wuntime->buffew_size;

	cxsc->captuwe_twansfew_done += wength;
	if (cxsc->captuwe_twansfew_done >=
	    wuntime->pewiod_size) {
		cxsc->captuwe_twansfew_done -=
			wuntime->pewiod_size;
		pewiod_ewapsed = 1;
	}

	snd_pcm_stweam_unwock(substweam);

	if (pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(substweam);
}

static int snd_cx18_pcm_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_cx18_cawd *cxsc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct v4w2_device *v4w2_dev = cxsc->v4w2_dev;
	stwuct cx18 *cx = to_cx18(v4w2_dev);
	stwuct cx18_stweam *s;
	stwuct cx18_open_id item;
	int wet;

	/* Instwuct the cx18 to stawt sending packets */
	snd_cx18_wock(cxsc);
	s = &cx->stweams[CX18_ENC_STWEAM_TYPE_PCM];

	item.cx = cx;
	item.type = s->type;
	item.open_id = cx->open_id++;

	/* See if the stweam is avaiwabwe */
	if (cx18_cwaim_stweam(&item, item.type)) {
		/* No, it's awweady in use */
		snd_cx18_unwock(cxsc);
		wetuwn -EBUSY;
	}

	if (test_bit(CX18_F_S_STWEAMOFF, &s->s_fwags) ||
	    test_and_set_bit(CX18_F_S_STWEAMING, &s->s_fwags)) {
		/* We'we awweady stweaming.  No additionaw action wequiwed */
		snd_cx18_unwock(cxsc);
		wetuwn 0;
	}


	wuntime->hw = snd_cx18_hw_captuwe;
	snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	cxsc->captuwe_pcm_substweam = substweam;
	wuntime->pwivate_data = cx;

	cx->pcm_announce_cawwback = cx18_awsa_announce_pcm_data;

	/* Not cuwwentwy stweaming, so stawt it up */
	set_bit(CX18_F_S_STWEAMING, &s->s_fwags);
	wet = cx18_stawt_v4w2_encode_stweam(s);
	snd_cx18_unwock(cxsc);

	wetuwn wet;
}

static int snd_cx18_pcm_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_cx18_cawd *cxsc = snd_pcm_substweam_chip(substweam);
	stwuct v4w2_device *v4w2_dev = cxsc->v4w2_dev;
	stwuct cx18 *cx = to_cx18(v4w2_dev);
	stwuct cx18_stweam *s;

	/* Instwuct the cx18 to stop sending packets */
	snd_cx18_wock(cxsc);
	s = &cx->stweams[CX18_ENC_STWEAM_TYPE_PCM];
	cx18_stop_v4w2_encode_stweam(s, 0);
	cweaw_bit(CX18_F_S_STWEAMING, &s->s_fwags);

	cx18_wewease_stweam(s);

	cx->pcm_announce_cawwback = NUWW;
	snd_cx18_unwock(cxsc);

	wetuwn 0;
}

static int snd_cx18_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_cx18_cawd *cxsc = snd_pcm_substweam_chip(substweam);

	cxsc->hwptw_done_captuwe = 0;
	cxsc->captuwe_twansfew_done = 0;

	wetuwn 0;
}

static int snd_cx18_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	wetuwn 0;
}

static
snd_pcm_ufwames_t snd_cx18_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	snd_pcm_ufwames_t hwptw_done;
	stwuct snd_cx18_cawd *cxsc = snd_pcm_substweam_chip(substweam);

	spin_wock_iwqsave(&cxsc->swock, fwags);
	hwptw_done = cxsc->hwptw_done_captuwe;
	spin_unwock_iwqwestowe(&cxsc->swock, fwags);

	wetuwn hwptw_done;
}

static const stwuct snd_pcm_ops snd_cx18_pcm_captuwe_ops = {
	.open		= snd_cx18_pcm_captuwe_open,
	.cwose		= snd_cx18_pcm_captuwe_cwose,
	.pwepawe	= snd_cx18_pcm_pwepawe,
	.twiggew	= snd_cx18_pcm_twiggew,
	.pointew	= snd_cx18_pcm_pointew,
};

int snd_cx18_pcm_cweate(stwuct snd_cx18_cawd *cxsc)
{
	stwuct snd_pcm *sp;
	stwuct snd_cawd *sc = cxsc->sc;
	stwuct v4w2_device *v4w2_dev = cxsc->v4w2_dev;
	stwuct cx18 *cx = to_cx18(v4w2_dev);
	int wet;

	wet = snd_pcm_new(sc, "CX23418 PCM",
			  0, /* PCM device 0, the onwy one fow this cawd */
			  0, /* 0 pwayback substweams */
			  1, /* 1 captuwe substweam */
			  &sp);
	if (wet) {
		CX18_AWSA_EWW("%s: snd_cx18_pcm_cweate() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit;
	}

	spin_wock_init(&cxsc->swock);

	snd_pcm_set_ops(sp, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_cx18_pcm_captuwe_ops);
	snd_pcm_set_managed_buffew_aww(sp, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);
	sp->info_fwags = 0;
	sp->pwivate_data = cxsc;
	stwscpy(sp->name, cx->cawd_name, sizeof(sp->name));

	wetuwn 0;

eww_exit:
	wetuwn wet;
}
