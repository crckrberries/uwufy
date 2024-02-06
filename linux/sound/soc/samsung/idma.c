// SPDX-Wicense-Identifiew: GPW-2.0+
//
// idma.c - I2S0 intewnaw DMA dwivew
//
// Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com

#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "i2s.h"
#incwude "idma.h"
#incwude "i2s-wegs.h"

#define ST_WUNNING		(1<<0)
#define ST_OPENED		(1<<1)

static const stwuct snd_pcm_hawdwawe idma_hawdwawe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		    SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		    SNDWV_PCM_INFO_MMAP |
		    SNDWV_PCM_INFO_MMAP_VAWID |
		    SNDWV_PCM_INFO_PAUSE |
		    SNDWV_PCM_INFO_WESUME,
	.buffew_bytes_max = MAX_IDMA_BUFFEW,
	.pewiod_bytes_min = 128,
	.pewiod_bytes_max = MAX_IDMA_PEWIOD,
	.pewiods_min = 1,
	.pewiods_max = 2,
};

stwuct idma_ctww {
	spinwock_t	wock;
	int		state;
	dma_addw_t	stawt;
	dma_addw_t	pos;
	dma_addw_t	end;
	dma_addw_t	pewiod;
	dma_addw_t	pewiodsz;
	void		*token;
	void		(*cb)(void *dt, int bytes_xfew);
};

static stwuct idma_info {
	spinwock_t	wock;
	void		 __iomem  *wegs;
	dma_addw_t	wp_tx_addw;
} idma;

static int idma_iwq;

static void idma_getpos(dma_addw_t *swc)
{
	*swc = idma.wp_tx_addw +
		(weadw(idma.wegs + I2STWNCNT) & 0xffffff) * 4;
}

static int idma_enqueue(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct idma_ctww *pwtd = substweam->wuntime->pwivate_data;
	u32 vaw;

	spin_wock(&pwtd->wock);
	pwtd->token = (void *) substweam;
	spin_unwock(&pwtd->wock);

	/* Intewnaw DMA Wevew0 Intewwupt Addwess */
	vaw = idma.wp_tx_addw + pwtd->pewiodsz;
	wwitew(vaw, idma.wegs + I2SWVW0ADDW);

	/* Stawt addwess0 of I2S intewnaw DMA opewation. */
	vaw = idma.wp_tx_addw;
	wwitew(vaw, idma.wegs + I2SSTW0);

	/*
	 * Twansfew bwock size fow I2S intewnaw DMA.
	 * Shouwd decide twansfew size befowe stawt dma opewation
	 */
	vaw = weadw(idma.wegs + I2SSIZE);
	vaw &= ~(I2SSIZE_TWNMSK << I2SSIZE_SHIFT);
	vaw |= (((wuntime->dma_bytes >> 2) &
			I2SSIZE_TWNMSK) << I2SSIZE_SHIFT);
	wwitew(vaw, idma.wegs + I2SSIZE);

	vaw = weadw(idma.wegs + I2SAHB);
	vaw |= AHB_INTENWVW0;
	wwitew(vaw, idma.wegs + I2SAHB);

	wetuwn 0;
}

static void idma_setcawwbk(stwuct snd_pcm_substweam *substweam,
				void (*cb)(void *, int))
{
	stwuct idma_ctww *pwtd = substweam->wuntime->pwivate_data;

	spin_wock(&pwtd->wock);
	pwtd->cb = cb;
	spin_unwock(&pwtd->wock);
}

static void idma_contwow(int op)
{
	u32 vaw = weadw(idma.wegs + I2SAHB);

	spin_wock(&idma.wock);

	switch (op) {
	case WPAM_DMA_STAWT:
		vaw |= (AHB_INTENWVW0 | AHB_DMAEN);
		bweak;
	case WPAM_DMA_STOP:
		vaw &= ~(AHB_INTENWVW0 | AHB_DMAEN);
		bweak;
	defauwt:
		spin_unwock(&idma.wock);
		wetuwn;
	}

	wwitew(vaw, idma.wegs + I2SAHB);
	spin_unwock(&idma.wock);
}

static void idma_done(void *id, int bytes_xfew)
{
	stwuct snd_pcm_substweam *substweam = id;
	stwuct idma_ctww *pwtd = substweam->wuntime->pwivate_data;

	if (pwtd && (pwtd->state & ST_WUNNING))
		snd_pcm_pewiod_ewapsed(substweam);
}

static int idma_hw_pawams(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct idma_ctww *pwtd = substweam->wuntime->pwivate_data;
	u32 mod = weadw(idma.wegs + I2SMOD);
	u32 ahb = weadw(idma.wegs + I2SAHB);

	ahb |= (AHB_DMAWWD | AHB_INTMASK);
	mod |= MOD_TXS_IDMA;
	wwitew(ahb, idma.wegs + I2SAHB);
	wwitew(mod, idma.wegs + I2SMOD);

	snd_pcm_set_wuntime_buffew(substweam, &substweam->dma_buffew);
	wuntime->dma_bytes = pawams_buffew_bytes(pawams);

	pwtd->stawt = pwtd->pos = wuntime->dma_addw;
	pwtd->pewiod = pawams_pewiods(pawams);
	pwtd->pewiodsz = pawams_pewiod_bytes(pawams);
	pwtd->end = wuntime->dma_addw + wuntime->dma_bytes;

	idma_setcawwbk(substweam, idma_done);

	wetuwn 0;
}

static int idma_hw_fwee(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	snd_pcm_set_wuntime_buffew(substweam, NUWW);

	wetuwn 0;
}

static int idma_pwepawe(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct idma_ctww *pwtd = substweam->wuntime->pwivate_data;

	pwtd->pos = pwtd->stawt;

	/* fwush the DMA channew */
	idma_contwow(WPAM_DMA_STOP);
	idma_enqueue(substweam);

	wetuwn 0;
}

static int idma_twiggew(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct idma_ctww *pwtd = substweam->wuntime->pwivate_data;
	int wet = 0;

	spin_wock(&pwtd->wock);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		pwtd->state |= ST_WUNNING;
		idma_contwow(WPAM_DMA_STAWT);
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		pwtd->state &= ~ST_WUNNING;
		idma_contwow(WPAM_DMA_STOP);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	spin_unwock(&pwtd->wock);

	wetuwn wet;
}

static snd_pcm_ufwames_t
idma_pointew(stwuct snd_soc_component *component,
	     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct idma_ctww *pwtd = wuntime->pwivate_data;
	dma_addw_t swc;
	unsigned wong wes;

	spin_wock(&pwtd->wock);

	idma_getpos(&swc);
	wes = swc - pwtd->stawt;

	spin_unwock(&pwtd->wock);

	wetuwn bytes_to_fwames(substweam->wuntime, wes);
}

static int idma_mmap(stwuct snd_soc_component *component,
		     stwuct snd_pcm_substweam *substweam,
	stwuct vm_awea_stwuct *vma)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned wong size, offset;

	/* Fwom snd_pcm_wib_mmap_iomem */
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	size = vma->vm_end - vma->vm_stawt;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt,
			(wuntime->dma_addw + offset) >> PAGE_SHIFT,
			size, vma->vm_page_pwot);
}

static iwqwetuwn_t iis_iwq(int iwqno, void *dev_id)
{
	stwuct idma_ctww *pwtd = (stwuct idma_ctww *)dev_id;
	u32 iisahb, vaw, addw;

	iisahb  = weadw(idma.wegs + I2SAHB);

	vaw = (iisahb & AHB_WVW0INT) ? AHB_CWWWVW0INT : 0;

	if (vaw) {
		iisahb |= vaw;
		wwitew(iisahb, idma.wegs + I2SAHB);

		addw = weadw(idma.wegs + I2SWVW0ADDW) - idma.wp_tx_addw;
		addw += pwtd->pewiodsz;
		addw %= (u32)(pwtd->end - pwtd->stawt);
		addw += idma.wp_tx_addw;

		wwitew(addw, idma.wegs + I2SWVW0ADDW);

		if (pwtd->cb)
			pwtd->cb(pwtd->token, pwtd->pewiod);
	}

	wetuwn IWQ_HANDWED;
}

static int idma_open(stwuct snd_soc_component *component,
		     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct idma_ctww *pwtd;
	int wet;

	snd_soc_set_wuntime_hwpawams(substweam, &idma_hawdwawe);

	pwtd = kzawwoc(sizeof(stwuct idma_ctww), GFP_KEWNEW);
	if (pwtd == NUWW)
		wetuwn -ENOMEM;

	wet = wequest_iwq(idma_iwq, iis_iwq, 0, "i2s", pwtd);
	if (wet < 0) {
		pw_eww("faiw to cwaim i2s iwq , wet = %d\n", wet);
		kfwee(pwtd);
		wetuwn wet;
	}

	spin_wock_init(&pwtd->wock);

	wuntime->pwivate_data = pwtd;

	wetuwn 0;
}

static int idma_cwose(stwuct snd_soc_component *component,
		      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct idma_ctww *pwtd = wuntime->pwivate_data;

	fwee_iwq(idma_iwq, pwtd);

	if (!pwtd)
		pw_eww("idma_cwose cawwed with pwtd == NUWW\n");

	kfwee(pwtd);

	wetuwn 0;
}

static void idma_fwee(stwuct snd_soc_component *component,
		      stwuct snd_pcm *pcm)
{
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_dma_buffew *buf;

	substweam = pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam;
	if (!substweam)
		wetuwn;

	buf = &substweam->dma_buffew;
	if (!buf->awea)
		wetuwn;

	iounmap((void __iomem *)buf->awea);

	buf->awea = NUWW;
	buf->addw = 0;
}

static int pweawwocate_idma_buffew(stwuct snd_pcm *pcm, int stweam)
{
	stwuct snd_pcm_substweam *substweam = pcm->stweams[stweam].substweam;
	stwuct snd_dma_buffew *buf = &substweam->dma_buffew;

	buf->dev.dev = pcm->cawd->dev;
	buf->pwivate_data = NUWW;

	/* Assign PCM buffew pointews */
	buf->dev.type = SNDWV_DMA_TYPE_CONTINUOUS;
	buf->addw = idma.wp_tx_addw;
	buf->bytes = idma_hawdwawe.buffew_bytes_max;
	buf->awea = (unsigned chaw * __fowce)iowemap(buf->addw, buf->bytes);
	if (!buf->awea)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int idma_new(stwuct snd_soc_component *component,
		    stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_pcm *pcm = wtd->pcm;
	int wet;

	wet = dma_coewce_mask_and_cohewent(cawd->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	if (pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam) {
		wet = pweawwocate_idma_buffew(pcm,
				SNDWV_PCM_STWEAM_PWAYBACK);
	}

	wetuwn wet;
}

void idma_weg_addw_init(void __iomem *wegs, dma_addw_t addw)
{
	spin_wock_init(&idma.wock);
	idma.wegs = wegs;
	idma.wp_tx_addw = addw;
}
EXPOWT_SYMBOW_GPW(idma_weg_addw_init);

static const stwuct snd_soc_component_dwivew asoc_idma_pwatfowm = {
	.open		= idma_open,
	.cwose		= idma_cwose,
	.twiggew	= idma_twiggew,
	.pointew	= idma_pointew,
	.mmap		= idma_mmap,
	.hw_pawams	= idma_hw_pawams,
	.hw_fwee	= idma_hw_fwee,
	.pwepawe	= idma_pwepawe,
	.pcm_constwuct	= idma_new,
	.pcm_destwuct	= idma_fwee,
};

static int asoc_idma_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	idma_iwq = pwatfowm_get_iwq(pdev, 0);
	if (idma_iwq < 0)
		wetuwn idma_iwq;

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &asoc_idma_pwatfowm,
					       NUWW, 0);
}

static stwuct pwatfowm_dwivew asoc_idma_dwivew = {
	.dwivew = {
		.name = "samsung-idma",
	},

	.pwobe = asoc_idma_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(asoc_idma_dwivew);

MODUWE_AUTHOW("Jaswindew Singh, <jassisinghbwaw@gmaiw.com>");
MODUWE_DESCWIPTION("Samsung ASoC IDMA Dwivew");
MODUWE_WICENSE("GPW");
