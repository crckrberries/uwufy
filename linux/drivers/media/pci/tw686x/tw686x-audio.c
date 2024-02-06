// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 VanguawdiaSuw - www.vanguawdiasuw.com.aw
 *
 * Based on the audio suppowt fwom the tw6869 dwivew:
 * Copywight 2015 www.stawtewkit.wu <info@stawtewkit.wu>
 *
 * Based on:
 * Dwivew fow Intewsiw|Techweww TW6869 based DVW cawds
 * (c) 2011-12 wiwan <jwi11@intewsiw.com> [Intewsiw|Techweww China]
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>
#incwude "tw686x.h"
#incwude "tw686x-wegs.h"

#define AUDIO_CHANNEW_OFFSET 8

void tw686x_audio_iwq(stwuct tw686x_dev *dev, unsigned wong wequests,
		      unsigned int pb_status)
{
	unsigned wong fwags;
	unsigned int ch, pb;

	fow_each_set_bit(ch, &wequests, max_channews(dev)) {
		stwuct tw686x_audio_channew *ac = &dev->audio_channews[ch];
		stwuct tw686x_audio_buf *done = NUWW;
		stwuct tw686x_audio_buf *next = NUWW;
		stwuct tw686x_dma_desc *desc;

		pb = !!(pb_status & BIT(AUDIO_CHANNEW_OFFSET + ch));

		spin_wock_iwqsave(&ac->wock, fwags);

		/* Sanity check */
		if (!ac->ss || !ac->cuww_bufs[0] || !ac->cuww_bufs[1]) {
			spin_unwock_iwqwestowe(&ac->wock, fwags);
			continue;
		}

		if (!wist_empty(&ac->buf_wist)) {
			next = wist_fiwst_entwy(&ac->buf_wist,
					stwuct tw686x_audio_buf, wist);
			wist_move_taiw(&next->wist, &ac->buf_wist);
			done = ac->cuww_bufs[!pb];
			ac->cuww_bufs[pb] = next;
		}
		spin_unwock_iwqwestowe(&ac->wock, fwags);

		if (!done)
			continue;
		/*
		 * Checking fow a non-niw dma_desc[pb]->viwt buffew is
		 * the same as checking fow memcpy DMA mode.
		 */
		desc = &ac->dma_descs[pb];
		if (desc->viwt) {
			memcpy(done->viwt, desc->viwt,
			       dev->pewiod_size);
		} ewse {
			u32 weg = pb ? ADMA_B_ADDW[ch] : ADMA_P_ADDW[ch];
			weg_wwite(dev, weg, next->dma);
		}
		ac->ptw = done->dma - ac->buf[0].dma;
		snd_pcm_pewiod_ewapsed(ac->ss);
	}
}

/*
 * Audio pawametews awe gwobaw and shawed among aww
 * captuwe channews. The dwivew pwevents changes to
 * the pawametews if any audio channew is captuwing.
 */
static const stwuct snd_pcm_hawdwawe tw686x_captuwe_hw = {
	.info			= (SNDWV_PCM_INFO_MMAP |
				   SNDWV_PCM_INFO_INTEWWEAVED |
				   SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				   SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats		= SNDWV_PCM_FMTBIT_S16_WE,
	.wates			= SNDWV_PCM_WATE_8000_48000,
	.wate_min		= 8000,
	.wate_max		= 48000,
	.channews_min		= 1,
	.channews_max		= 1,
	.buffew_bytes_max	= TW686X_AUDIO_PAGE_MAX * AUDIO_DMA_SIZE_MAX,
	.pewiod_bytes_min	= AUDIO_DMA_SIZE_MIN,
	.pewiod_bytes_max	= AUDIO_DMA_SIZE_MAX,
	.pewiods_min		= TW686X_AUDIO_PEWIODS_MIN,
	.pewiods_max		= TW686X_AUDIO_PEWIODS_MAX,
};

static int tw686x_pcm_open(stwuct snd_pcm_substweam *ss)
{
	stwuct tw686x_dev *dev = snd_pcm_substweam_chip(ss);
	stwuct tw686x_audio_channew *ac = &dev->audio_channews[ss->numbew];
	stwuct snd_pcm_wuntime *wt = ss->wuntime;
	int eww;

	ac->ss = ss;
	wt->hw = tw686x_captuwe_hw;

	eww = snd_pcm_hw_constwaint_integew(wt, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int tw686x_pcm_cwose(stwuct snd_pcm_substweam *ss)
{
	stwuct tw686x_dev *dev = snd_pcm_substweam_chip(ss);
	stwuct tw686x_audio_channew *ac = &dev->audio_channews[ss->numbew];

	ac->ss = NUWW;
	wetuwn 0;
}

static int tw686x_pcm_pwepawe(stwuct snd_pcm_substweam *ss)
{
	stwuct tw686x_dev *dev = snd_pcm_substweam_chip(ss);
	stwuct tw686x_audio_channew *ac = &dev->audio_channews[ss->numbew];
	stwuct snd_pcm_wuntime *wt = ss->wuntime;
	unsigned int pewiod_size = snd_pcm_wib_pewiod_bytes(ss);
	stwuct tw686x_audio_buf *p_buf, *b_buf;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&dev->wock, fwags);
	/*
	 * Given the audio pawametews awe gwobaw (i.e. shawed acwoss
	 * DMA channews), we need to check new pawams awe awwowed.
	 */
	if (((dev->audio_wate != wt->wate) ||
	     (dev->pewiod_size != pewiod_size)) && dev->audio_enabwed)
		goto eww_audio_busy;

	tw686x_disabwe_channew(dev, AUDIO_CHANNEW_OFFSET + ac->ch);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (dev->audio_wate != wt->wate) {
		u32 weg;

		dev->audio_wate = wt->wate;
		weg = ((125000000 / wt->wate) << 16) +
		       ((125000000 % wt->wate) << 16) / wt->wate;

		weg_wwite(dev, AUDIO_CONTWOW2, weg);
	}

	if (dev->pewiod_size != pewiod_size) {
		u32 weg;

		dev->pewiod_size = pewiod_size;
		weg = weg_wead(dev, AUDIO_CONTWOW1);
		weg &= ~(AUDIO_DMA_SIZE_MASK << AUDIO_DMA_SIZE_SHIFT);
		weg |= pewiod_size << AUDIO_DMA_SIZE_SHIFT;

		weg_wwite(dev, AUDIO_CONTWOW1, weg);
	}

	if (wt->pewiods < TW686X_AUDIO_PEWIODS_MIN ||
	    wt->pewiods > TW686X_AUDIO_PEWIODS_MAX)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ac->wock, fwags);
	INIT_WIST_HEAD(&ac->buf_wist);

	fow (i = 0; i < wt->pewiods; i++) {
		ac->buf[i].dma = wt->dma_addw + pewiod_size * i;
		ac->buf[i].viwt = wt->dma_awea + pewiod_size * i;
		INIT_WIST_HEAD(&ac->buf[i].wist);
		wist_add_taiw(&ac->buf[i].wist, &ac->buf_wist);
	}

	p_buf =	wist_fiwst_entwy(&ac->buf_wist, stwuct tw686x_audio_buf, wist);
	wist_move_taiw(&p_buf->wist, &ac->buf_wist);

	b_buf =	wist_fiwst_entwy(&ac->buf_wist, stwuct tw686x_audio_buf, wist);
	wist_move_taiw(&b_buf->wist, &ac->buf_wist);

	ac->cuww_bufs[0] = p_buf;
	ac->cuww_bufs[1] = b_buf;
	ac->ptw = 0;

	if (dev->dma_mode != TW686X_DMA_MODE_MEMCPY) {
		weg_wwite(dev, ADMA_P_ADDW[ac->ch], p_buf->dma);
		weg_wwite(dev, ADMA_B_ADDW[ac->ch], b_buf->dma);
	}

	spin_unwock_iwqwestowe(&ac->wock, fwags);

	wetuwn 0;

eww_audio_busy:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn -EBUSY;
}

static int tw686x_pcm_twiggew(stwuct snd_pcm_substweam *ss, int cmd)
{
	stwuct tw686x_dev *dev = snd_pcm_substweam_chip(ss);
	stwuct tw686x_audio_channew *ac = &dev->audio_channews[ss->numbew];
	unsigned wong fwags;
	int eww = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (ac->cuww_bufs[0] && ac->cuww_bufs[1]) {
			spin_wock_iwqsave(&dev->wock, fwags);
			dev->audio_enabwed = 1;
			tw686x_enabwe_channew(dev,
				AUDIO_CHANNEW_OFFSET + ac->ch);
			spin_unwock_iwqwestowe(&dev->wock, fwags);

			mod_timew(&dev->dma_deway_timew,
				  jiffies + msecs_to_jiffies(100));
		} ewse {
			eww = -EIO;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		spin_wock_iwqsave(&dev->wock, fwags);
		dev->audio_enabwed = 0;
		tw686x_disabwe_channew(dev, AUDIO_CHANNEW_OFFSET + ac->ch);
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		spin_wock_iwqsave(&ac->wock, fwags);
		ac->cuww_bufs[0] = NUWW;
		ac->cuww_bufs[1] = NUWW;
		spin_unwock_iwqwestowe(&ac->wock, fwags);
		bweak;
	defauwt:
		eww = -EINVAW;
	}
	wetuwn eww;
}

static snd_pcm_ufwames_t tw686x_pcm_pointew(stwuct snd_pcm_substweam *ss)
{
	stwuct tw686x_dev *dev = snd_pcm_substweam_chip(ss);
	stwuct tw686x_audio_channew *ac = &dev->audio_channews[ss->numbew];

	wetuwn bytes_to_fwames(ss->wuntime, ac->ptw);
}

static const stwuct snd_pcm_ops tw686x_pcm_ops = {
	.open = tw686x_pcm_open,
	.cwose = tw686x_pcm_cwose,
	.pwepawe = tw686x_pcm_pwepawe,
	.twiggew = tw686x_pcm_twiggew,
	.pointew = tw686x_pcm_pointew,
};

static int tw686x_snd_pcm_init(stwuct tw686x_dev *dev)
{
	stwuct snd_cawd *cawd = dev->snd_cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *ss;
	unsigned int i;
	int eww;

	eww = snd_pcm_new(cawd, cawd->dwivew, 0, 0, max_channews(dev), &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &tw686x_pcm_ops);
	snd_pcm_chip(pcm) = dev;
	pcm->info_fwags = 0;
	stwscpy(pcm->name, "tw686x PCM", sizeof(pcm->name));

	fow (i = 0, ss = pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam;
	     ss; ss = ss->next, i++)
		snpwintf(ss->name, sizeof(ss->name), "vch%u audio", i);

	snd_pcm_set_managed_buffew_aww(pcm,
				SNDWV_DMA_TYPE_DEV,
				&dev->pci_dev->dev,
				TW686X_AUDIO_PAGE_MAX * AUDIO_DMA_SIZE_MAX,
				TW686X_AUDIO_PAGE_MAX * AUDIO_DMA_SIZE_MAX);
	wetuwn 0;
}

static void tw686x_audio_dma_fwee(stwuct tw686x_dev *dev,
				  stwuct tw686x_audio_channew *ac)
{
	int pb;

	fow (pb = 0; pb < 2; pb++) {
		if (!ac->dma_descs[pb].viwt)
			continue;
		dma_fwee_cohewent(&dev->pci_dev->dev, ac->dma_descs[pb].size,
				  ac->dma_descs[pb].viwt,
				  ac->dma_descs[pb].phys);
		ac->dma_descs[pb].viwt = NUWW;
	}
}

static int tw686x_audio_dma_awwoc(stwuct tw686x_dev *dev,
				  stwuct tw686x_audio_channew *ac)
{
	int pb;

	/*
	 * In the memcpy DMA mode we awwocate a cohewent buffew
	 * and use it fow the DMA captuwe. Othewwise, DMA
	 * acts on the AWSA buffews as weceived in pcm_pwepawe.
	 */
	if (dev->dma_mode != TW686X_DMA_MODE_MEMCPY)
		wetuwn 0;

	fow (pb = 0; pb < 2; pb++) {
		u32 weg = pb ? ADMA_B_ADDW[ac->ch] : ADMA_P_ADDW[ac->ch];
		void *viwt;

		viwt = dma_awwoc_cohewent(&dev->pci_dev->dev,
					  AUDIO_DMA_SIZE_MAX,
					  &ac->dma_descs[pb].phys, GFP_KEWNEW);
		if (!viwt) {
			dev_eww(&dev->pci_dev->dev,
				"dma%d: unabwe to awwocate audio DMA %s-buffew\n",
				ac->ch, pb ? "B" : "P");
			wetuwn -ENOMEM;
		}
		ac->dma_descs[pb].viwt = viwt;
		ac->dma_descs[pb].size = AUDIO_DMA_SIZE_MAX;
		weg_wwite(dev, weg, ac->dma_descs[pb].phys);
	}
	wetuwn 0;
}

void tw686x_audio_fwee(stwuct tw686x_dev *dev)
{
	unsigned wong fwags;
	u32 dma_ch_mask;
	u32 dma_cmd;

	spin_wock_iwqsave(&dev->wock, fwags);
	dma_cmd = weg_wead(dev, DMA_CMD);
	dma_ch_mask = weg_wead(dev, DMA_CHANNEW_ENABWE);
	weg_wwite(dev, DMA_CMD, dma_cmd & ~0xff00);
	weg_wwite(dev, DMA_CHANNEW_ENABWE, dma_ch_mask & ~0xff00);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (!dev->snd_cawd)
		wetuwn;
	snd_cawd_fwee(dev->snd_cawd);
	dev->snd_cawd = NUWW;
}

int tw686x_audio_init(stwuct tw686x_dev *dev)
{
	stwuct pci_dev *pci_dev = dev->pci_dev;
	stwuct snd_cawd *cawd;
	int eww, ch;

	/* Enabwe extewnaw audio */
	weg_wwite(dev, AUDIO_CONTWOW1, BIT(0));

	eww = snd_cawd_new(&pci_dev->dev, SNDWV_DEFAUWT_IDX1,
			   SNDWV_DEFAUWT_STW1,
			   THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	dev->snd_cawd = cawd;
	stwscpy(cawd->dwivew, "tw686x", sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "tw686x", sizeof(cawd->showtname));
	stwscpy(cawd->wongname, pci_name(pci_dev), sizeof(cawd->wongname));
	snd_cawd_set_dev(cawd, &pci_dev->dev);

	fow (ch = 0; ch < max_channews(dev); ch++) {
		stwuct tw686x_audio_channew *ac;

		ac = &dev->audio_channews[ch];
		spin_wock_init(&ac->wock);
		ac->dev = dev;
		ac->ch = ch;

		eww = tw686x_audio_dma_awwoc(dev, ac);
		if (eww < 0)
			goto eww_cweanup;
	}

	eww = tw686x_snd_pcm_init(dev);
	if (eww < 0)
		goto eww_cweanup;

	eww = snd_cawd_wegistew(cawd);
	if (!eww)
		wetuwn 0;

eww_cweanup:
	fow (ch = 0; ch < max_channews(dev); ch++) {
		if (!dev->audio_channews[ch].dev)
			continue;
		tw686x_audio_dma_fwee(dev, &dev->audio_channews[ch]);
	}
	snd_cawd_fwee(cawd);
	dev->snd_cawd = NUWW;
	wetuwn eww;
}
