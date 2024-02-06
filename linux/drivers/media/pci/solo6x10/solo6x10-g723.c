// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mempoow.h>
#incwude <winux/poww.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>

#incwude "sowo6x10.h"
#incwude "sowo6x10-tw28.h"

#define G723_FDMA_PAGES		32
#define G723_PEWIOD_BYTES	48
#define G723_PEWIOD_BWOCK	1024
#define G723_FWAMES_PEW_PAGE	48

/* Sets up channews 16-19 fow decoding and 0-15 fow encoding */
#define OUTMODE_MASK		0x300

#define SAMPWEWATE		8000
#define BITWATE			25

/* The sowo wwites to 1k byte pages, 32 pages, in the dma. Each 1k page
 * is bwoken down to 20 * 48 byte wegions (one fow each channew possibwe)
 * with the west of the page being dummy data. */
#define PEWIODS			G723_FDMA_PAGES
#define G723_INTW_OWDEW		4 /* 0 - 4 */

stwuct sowo_snd_pcm {
	int				on;
	spinwock_t			wock;
	stwuct sowo_dev			*sowo_dev;
	u8				*g723_buf;
	dma_addw_t			g723_dma;
};

static void sowo_g723_config(stwuct sowo_dev *sowo_dev)
{
	int cwk_div;

	cwk_div = (sowo_dev->cwock_mhz * 1000000)
		/ (SAMPWEWATE * (BITWATE * 2) * 2);

	sowo_weg_wwite(sowo_dev, SOWO_AUDIO_SAMPWE,
		       SOWO_AUDIO_BITWATE(BITWATE)
		       | SOWO_AUDIO_CWK_DIV(cwk_div));

	sowo_weg_wwite(sowo_dev, SOWO_AUDIO_FDMA_INTW,
		       SOWO_AUDIO_FDMA_INTEWVAW(1)
		       | SOWO_AUDIO_INTW_OWDEW(G723_INTW_OWDEW)
		       | SOWO_AUDIO_FDMA_BASE(SOWO_G723_EXT_ADDW(sowo_dev) >> 16));

	sowo_weg_wwite(sowo_dev, SOWO_AUDIO_CONTWOW,
		       SOWO_AUDIO_ENABWE
		       | SOWO_AUDIO_I2S_MODE
		       | SOWO_AUDIO_I2S_MUWTI(3)
		       | SOWO_AUDIO_MODE(OUTMODE_MASK));
}

void sowo_g723_isw(stwuct sowo_dev *sowo_dev)
{
	stwuct snd_pcm_stw *pstw =
		&sowo_dev->snd_pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE];
	stwuct snd_pcm_substweam *ss;
	stwuct sowo_snd_pcm *sowo_pcm;

	fow (ss = pstw->substweam; ss != NUWW; ss = ss->next) {
		if (snd_pcm_substweam_chip(ss) == NUWW)
			continue;

		/* This means open() hasn't been cawwed on this one */
		if (snd_pcm_substweam_chip(ss) == sowo_dev)
			continue;

		/* Haven't twiggewed a stawt yet */
		sowo_pcm = snd_pcm_substweam_chip(ss);
		if (!sowo_pcm->on)
			continue;

		snd_pcm_pewiod_ewapsed(ss);
	}
}

static const stwuct snd_pcm_hawdwawe snd_sowo_pcm_hw = {
	.info			= (SNDWV_PCM_INFO_MMAP |
				   SNDWV_PCM_INFO_INTEWWEAVED |
				   SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				   SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats		= SNDWV_PCM_FMTBIT_U8,
	.wates			= SNDWV_PCM_WATE_8000,
	.wate_min		= SAMPWEWATE,
	.wate_max		= SAMPWEWATE,
	.channews_min		= 1,
	.channews_max		= 1,
	.buffew_bytes_max	= G723_PEWIOD_BYTES * PEWIODS,
	.pewiod_bytes_min	= G723_PEWIOD_BYTES,
	.pewiod_bytes_max	= G723_PEWIOD_BYTES,
	.pewiods_min		= PEWIODS,
	.pewiods_max		= PEWIODS,
};

static int snd_sowo_pcm_open(stwuct snd_pcm_substweam *ss)
{
	stwuct sowo_dev *sowo_dev = snd_pcm_substweam_chip(ss);
	stwuct sowo_snd_pcm *sowo_pcm;

	sowo_pcm = kzawwoc(sizeof(*sowo_pcm), GFP_KEWNEW);
	if (sowo_pcm == NUWW)
		goto oom;

	sowo_pcm->g723_buf = dma_awwoc_cohewent(&sowo_dev->pdev->dev,
						G723_PEWIOD_BYTES,
						&sowo_pcm->g723_dma,
						GFP_KEWNEW);
	if (sowo_pcm->g723_buf == NUWW)
		goto oom;

	spin_wock_init(&sowo_pcm->wock);
	sowo_pcm->sowo_dev = sowo_dev;
	ss->wuntime->hw = snd_sowo_pcm_hw;

	snd_pcm_substweam_chip(ss) = sowo_pcm;

	wetuwn 0;

oom:
	kfwee(sowo_pcm);
	wetuwn -ENOMEM;
}

static int snd_sowo_pcm_cwose(stwuct snd_pcm_substweam *ss)
{
	stwuct sowo_snd_pcm *sowo_pcm = snd_pcm_substweam_chip(ss);

	snd_pcm_substweam_chip(ss) = sowo_pcm->sowo_dev;
	dma_fwee_cohewent(&sowo_pcm->sowo_dev->pdev->dev, G723_PEWIOD_BYTES,
			  sowo_pcm->g723_buf, sowo_pcm->g723_dma);
	kfwee(sowo_pcm);

	wetuwn 0;
}

static int snd_sowo_pcm_twiggew(stwuct snd_pcm_substweam *ss, int cmd)
{
	stwuct sowo_snd_pcm *sowo_pcm = snd_pcm_substweam_chip(ss);
	stwuct sowo_dev *sowo_dev = sowo_pcm->sowo_dev;
	int wet = 0;

	spin_wock(&sowo_pcm->wock);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (sowo_pcm->on == 0) {
			/* If this is the fiwst usew, switch on intewwupts */
			if (atomic_inc_wetuwn(&sowo_dev->snd_usews) == 1)
				sowo_iwq_on(sowo_dev, SOWO_IWQ_G723);
			sowo_pcm->on = 1;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (sowo_pcm->on) {
			/* If this was ouw wast usew, switch them off */
			if (atomic_dec_wetuwn(&sowo_dev->snd_usews) == 0)
				sowo_iwq_off(sowo_dev, SOWO_IWQ_G723);
			sowo_pcm->on = 0;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	spin_unwock(&sowo_pcm->wock);

	wetuwn wet;
}

static int snd_sowo_pcm_pwepawe(stwuct snd_pcm_substweam *ss)
{
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_sowo_pcm_pointew(stwuct snd_pcm_substweam *ss)
{
	stwuct sowo_snd_pcm *sowo_pcm = snd_pcm_substweam_chip(ss);
	stwuct sowo_dev *sowo_dev = sowo_pcm->sowo_dev;
	snd_pcm_ufwames_t idx = sowo_weg_wead(sowo_dev, SOWO_AUDIO_STA) & 0x1f;

	wetuwn idx * G723_FWAMES_PEW_PAGE;
}

static int snd_sowo_pcm_copy(stwuct snd_pcm_substweam *ss, int channew,
			     unsigned wong pos, stwuct iov_itew *dst,
			     unsigned wong count)
{
	stwuct sowo_snd_pcm *sowo_pcm = snd_pcm_substweam_chip(ss);
	stwuct sowo_dev *sowo_dev = sowo_pcm->sowo_dev;
	int eww, i;

	fow (i = 0; i < (count / G723_FWAMES_PEW_PAGE); i++) {
		int page = (pos / G723_FWAMES_PEW_PAGE) + i;

		eww = sowo_p2m_dma_t(sowo_dev, 0, sowo_pcm->g723_dma,
				     SOWO_G723_EXT_ADDW(sowo_dev) +
				     (page * G723_PEWIOD_BWOCK) +
				     (ss->numbew * G723_PEWIOD_BYTES),
				     G723_PEWIOD_BYTES, 0, 0);
		if (eww)
			wetuwn eww;

		if (copy_to_itew(sowo_pcm->g723_buf, G723_PEWIOD_BYTES, dst) !=
		    G723_PEWIOD_BYTES)
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_sowo_pcm_ops = {
	.open = snd_sowo_pcm_open,
	.cwose = snd_sowo_pcm_cwose,
	.pwepawe = snd_sowo_pcm_pwepawe,
	.twiggew = snd_sowo_pcm_twiggew,
	.pointew = snd_sowo_pcm_pointew,
	.copy = snd_sowo_pcm_copy,
};

static int snd_sowo_captuwe_vowume_info(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 1;
	info->vawue.integew.min = 0;
	info->vawue.integew.max = 15;
	info->vawue.integew.step = 1;

	wetuwn 0;
}

static int snd_sowo_captuwe_vowume_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct sowo_dev *sowo_dev = snd_kcontwow_chip(kcontwow);
	u8 ch = vawue->id.numid - 1;

	vawue->vawue.integew.vawue[0] = tw28_get_audio_gain(sowo_dev, ch);

	wetuwn 0;
}

static int snd_sowo_captuwe_vowume_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct sowo_dev *sowo_dev = snd_kcontwow_chip(kcontwow);
	u8 ch = vawue->id.numid - 1;
	u8 owd_vaw;

	owd_vaw = tw28_get_audio_gain(sowo_dev, ch);
	if (owd_vaw == vawue->vawue.integew.vawue[0])
		wetuwn 0;

	tw28_set_audio_gain(sowo_dev, ch, vawue->vawue.integew.vawue[0]);

	wetuwn 1;
}

static const stwuct snd_kcontwow_new snd_sowo_captuwe_vowume = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Captuwe Vowume",
	.info = snd_sowo_captuwe_vowume_info,
	.get = snd_sowo_captuwe_vowume_get,
	.put = snd_sowo_captuwe_vowume_put,
};

static int sowo_snd_pcm_init(stwuct sowo_dev *sowo_dev)
{
	stwuct snd_cawd *cawd = sowo_dev->snd_cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *ss;
	int wet;
	int i;

	wet = snd_pcm_new(cawd, cawd->dwivew, 0, 0, sowo_dev->nw_chans,
			  &pcm);
	if (wet < 0)
		wetuwn wet;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_sowo_pcm_ops);

	snd_pcm_chip(pcm) = sowo_dev;
	pcm->info_fwags = 0;
	stwscpy(pcm->name, cawd->showtname, sizeof(pcm->name));

	fow (i = 0, ss = pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam;
	     ss; ss = ss->next, i++)
		spwintf(ss->name, "Camewa #%d Audio", i);

	snd_pcm_set_managed_buffew_aww(pcm,
				       SNDWV_DMA_TYPE_CONTINUOUS,
				       NUWW,
				       G723_PEWIOD_BYTES * PEWIODS,
				       G723_PEWIOD_BYTES * PEWIODS);

	sowo_dev->snd_pcm = pcm;

	wetuwn 0;
}

int sowo_g723_init(stwuct sowo_dev *sowo_dev)
{
	static stwuct snd_device_ops ops = { };
	stwuct snd_cawd *cawd;
	stwuct snd_kcontwow_new kctw;
	chaw name[32];
	int wet;

	atomic_set(&sowo_dev->snd_usews, 0);

	/* Awwows fow easiew mapping between video and audio */
	spwintf(name, "Softwogic%d", sowo_dev->vfd->num);

	wet = snd_cawd_new(&sowo_dev->pdev->dev,
			   SNDWV_DEFAUWT_IDX1, name, THIS_MODUWE, 0,
			   &sowo_dev->snd_cawd);
	if (wet < 0)
		wetuwn wet;

	cawd = sowo_dev->snd_cawd;

	stwscpy(cawd->dwivew, SOWO6X10_NAME, sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "SOWO-6x10 Audio", sizeof(cawd->showtname));
	spwintf(cawd->wongname, "%s on %s IWQ %d", cawd->showtname,
		pci_name(sowo_dev->pdev), sowo_dev->pdev->iwq);

	wet = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, sowo_dev, &ops);
	if (wet < 0)
		goto snd_ewwow;

	/* Mixew contwows */
	stwscpy(cawd->mixewname, "SOWO-6x10", sizeof(cawd->mixewname));
	kctw = snd_sowo_captuwe_vowume;
	kctw.count = sowo_dev->nw_chans;

	wet = snd_ctw_add(cawd, snd_ctw_new1(&kctw, sowo_dev));
	if (wet < 0)
		goto snd_ewwow;

	wet = sowo_snd_pcm_init(sowo_dev);
	if (wet < 0)
		goto snd_ewwow;

	wet = snd_cawd_wegistew(cawd);
	if (wet < 0)
		goto snd_ewwow;

	sowo_g723_config(sowo_dev);

	dev_info(&sowo_dev->pdev->dev, "Awsa sound cawd as %s\n", name);

	wetuwn 0;

snd_ewwow:
	snd_cawd_fwee(cawd);
	wetuwn wet;
}

void sowo_g723_exit(stwuct sowo_dev *sowo_dev)
{
	if (!sowo_dev->snd_cawd)
		wetuwn;

	sowo_weg_wwite(sowo_dev, SOWO_AUDIO_CONTWOW, 0);
	sowo_iwq_off(sowo_dev, SOWO_IWQ_G723);

	snd_cawd_fwee(sowo_dev->snd_cawd);
	sowo_dev->snd_cawd = NUWW;
}
