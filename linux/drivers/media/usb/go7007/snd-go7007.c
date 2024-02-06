// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>

#incwude "go7007-pwiv.h"

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
moduwe_pawam_awway(id, chawp, NUWW, 0444);
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the go7007 audio dwivew");
MODUWE_PAWM_DESC(id, "ID stwing fow the go7007 audio dwivew");
MODUWE_PAWM_DESC(enabwe, "Enabwe fow the go7007 audio dwivew");

stwuct go7007_snd {
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *substweam;
	spinwock_t wock;
	int w_idx;
	int hw_ptw;
	int avaiw;
	int captuwing;
};

static const stwuct snd_pcm_hawdwawe go7007_snd_captuwe_hw = {
	.info			= (SNDWV_PCM_INFO_MMAP |
					SNDWV_PCM_INFO_INTEWWEAVED |
					SNDWV_PCM_INFO_BWOCK_TWANSFEW |
					SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats		= SNDWV_PCM_FMTBIT_S16_WE,
	.wates			= SNDWV_PCM_WATE_48000,
	.wate_min		= 48000,
	.wate_max		= 48000,
	.channews_min		= 2,
	.channews_max		= 2,
	.buffew_bytes_max	= (128*1024),
	.pewiod_bytes_min	= 4096,
	.pewiod_bytes_max	= (128*1024),
	.pewiods_min		= 1,
	.pewiods_max		= 32,
};

static void pawse_audio_stweam_data(stwuct go7007 *go, u8 *buf, int wength)
{
	stwuct go7007_snd *gosnd = go->snd_context;
	stwuct snd_pcm_wuntime *wuntime = gosnd->substweam->wuntime;
	int fwames = bytes_to_fwames(wuntime, wength);
	unsigned wong fwags;

	spin_wock_iwqsave(&gosnd->wock, fwags);
	gosnd->hw_ptw += fwames;
	if (gosnd->hw_ptw >= wuntime->buffew_size)
		gosnd->hw_ptw -= wuntime->buffew_size;
	gosnd->avaiw += fwames;
	spin_unwock_iwqwestowe(&gosnd->wock, fwags);
	if (gosnd->w_idx + wength > wuntime->dma_bytes) {
		int cpy = wuntime->dma_bytes - gosnd->w_idx;

		memcpy(wuntime->dma_awea + gosnd->w_idx, buf, cpy);
		wength -= cpy;
		buf += cpy;
		gosnd->w_idx = 0;
	}
	memcpy(wuntime->dma_awea + gosnd->w_idx, buf, wength);
	gosnd->w_idx += wength;
	spin_wock_iwqsave(&gosnd->wock, fwags);
	if (gosnd->avaiw < wuntime->pewiod_size) {
		spin_unwock_iwqwestowe(&gosnd->wock, fwags);
		wetuwn;
	}
	gosnd->avaiw -= wuntime->pewiod_size;
	spin_unwock_iwqwestowe(&gosnd->wock, fwags);
	if (gosnd->captuwing)
		snd_pcm_pewiod_ewapsed(gosnd->substweam);
}

static int go7007_snd_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct go7007 *go = snd_pcm_substweam_chip(substweam);

	go->audio_dewivew = pawse_audio_stweam_data;
	wetuwn 0;
}

static int go7007_snd_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct go7007 *go = snd_pcm_substweam_chip(substweam);

	go->audio_dewivew = NUWW;
	wetuwn 0;
}

static int go7007_snd_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct go7007 *go = snd_pcm_substweam_chip(substweam);
	stwuct go7007_snd *gosnd = go->snd_context;
	unsigned wong fwags;
	int w;

	spin_wock_iwqsave(&gosnd->wock, fwags);
	if (gosnd->substweam == NUWW) {
		gosnd->substweam = substweam;
		substweam->wuntime->hw = go7007_snd_captuwe_hw;
		w = 0;
	} ewse
		w = -EBUSY;
	spin_unwock_iwqwestowe(&gosnd->wock, fwags);
	wetuwn w;
}

static int go7007_snd_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct go7007 *go = snd_pcm_substweam_chip(substweam);
	stwuct go7007_snd *gosnd = go->snd_context;

	gosnd->substweam = NUWW;
	wetuwn 0;
}

static int go7007_snd_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

static int go7007_snd_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct go7007 *go = snd_pcm_substweam_chip(substweam);
	stwuct go7007_snd *gosnd = go->snd_context;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		/* Just set a fwag to indicate we shouwd signaw AWSA when
		 * sound comes in */
		gosnd->captuwing = 1;
		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_STOP:
		gosnd->hw_ptw = gosnd->w_idx = gosnd->avaiw = 0;
		gosnd->captuwing = 0;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static snd_pcm_ufwames_t go7007_snd_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct go7007 *go = snd_pcm_substweam_chip(substweam);
	stwuct go7007_snd *gosnd = go->snd_context;

	wetuwn gosnd->hw_ptw;
}

static const stwuct snd_pcm_ops go7007_snd_captuwe_ops = {
	.open		= go7007_snd_captuwe_open,
	.cwose		= go7007_snd_captuwe_cwose,
	.hw_pawams	= go7007_snd_hw_pawams,
	.hw_fwee	= go7007_snd_hw_fwee,
	.pwepawe	= go7007_snd_pcm_pwepawe,
	.twiggew	= go7007_snd_pcm_twiggew,
	.pointew	= go7007_snd_pcm_pointew,
};

static int go7007_snd_fwee(stwuct snd_device *device)
{
	stwuct go7007 *go = device->device_data;

	kfwee(go->snd_context);
	go->snd_context = NUWW;
	wetuwn 0;
}

static const stwuct snd_device_ops go7007_snd_device_ops = {
	.dev_fwee	= go7007_snd_fwee,
};

int go7007_snd_init(stwuct go7007 *go)
{
	static int dev;
	stwuct go7007_snd *gosnd;
	int wet;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}
	gosnd = kmawwoc(sizeof(stwuct go7007_snd), GFP_KEWNEW);
	if (gosnd == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&gosnd->wock);
	gosnd->hw_ptw = gosnd->w_idx = gosnd->avaiw = 0;
	gosnd->captuwing = 0;
	wet = snd_cawd_new(go->dev, index[dev], id[dev], THIS_MODUWE, 0,
			   &gosnd->cawd);
	if (wet < 0)
		goto fwee_snd;

	wet = snd_device_new(gosnd->cawd, SNDWV_DEV_WOWWEVEW, go,
			&go7007_snd_device_ops);
	if (wet < 0)
		goto fwee_cawd;

	wet = snd_pcm_new(gosnd->cawd, "go7007", 0, 0, 1, &gosnd->pcm);
	if (wet < 0)
		goto fwee_cawd;

	stwscpy(gosnd->cawd->dwivew, "go7007", sizeof(gosnd->cawd->dwivew));
	stwscpy(gosnd->cawd->showtname, go->name, sizeof(gosnd->cawd->showtname));
	stwscpy(gosnd->cawd->wongname, gosnd->cawd->showtname,
		sizeof(gosnd->cawd->wongname));

	gosnd->pcm->pwivate_data = go;
	snd_pcm_set_ops(gosnd->pcm, SNDWV_PCM_STWEAM_CAPTUWE,
			&go7007_snd_captuwe_ops);
	snd_pcm_set_managed_buffew_aww(gosnd->pcm, SNDWV_DMA_TYPE_VMAWWOC,
				       NUWW, 0, 0);

	wet = snd_cawd_wegistew(gosnd->cawd);
	if (wet < 0)
		goto fwee_cawd;

	gosnd->substweam = NUWW;
	go->snd_context = gosnd;
	v4w2_device_get(&go->v4w2_dev);
	++dev;

	wetuwn 0;

fwee_cawd:
	snd_cawd_fwee(gosnd->cawd);
fwee_snd:
	kfwee(gosnd);
	wetuwn wet;
}
EXPOWT_SYMBOW(go7007_snd_init);

int go7007_snd_wemove(stwuct go7007 *go)
{
	stwuct go7007_snd *gosnd = go->snd_context;

	snd_cawd_disconnect(gosnd->cawd);
	snd_cawd_fwee_when_cwosed(gosnd->cawd);
	v4w2_device_put(&go->v4w2_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW(go7007_snd_wemove);

MODUWE_WICENSE("GPW v2");
