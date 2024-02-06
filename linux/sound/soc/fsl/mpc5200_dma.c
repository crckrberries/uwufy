// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Fweescawe MPC5200 PSC DMA
// AWSA SoC Pwatfowm dwivew
//
// Copywight (C) 2008 Secwet Wab Technowogies Wtd.
// Copywight (C) 2009 Jon Smiww, Digispeakew

#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <sound/soc.h>

#incwude <winux/fsw/bestcomm/bestcomm.h>
#incwude <winux/fsw/bestcomm/gen_bd.h>
#incwude <asm/mpc52xx_psc.h>

#incwude "mpc5200_dma.h"

#define DWV_NAME "mpc5200_dma"

/*
 * Intewwupt handwews
 */
static iwqwetuwn_t psc_dma_status_iwq(int iwq, void *_psc_dma)
{
	stwuct psc_dma *psc_dma = _psc_dma;
	stwuct mpc52xx_psc __iomem *wegs = psc_dma->psc_wegs;
	u16 isw;

	isw = in_be16(&wegs->mpc52xx_psc_isw);

	/* Pwayback undewwun ewwow */
	if (psc_dma->pwayback.active && (isw & MPC52xx_PSC_IMW_TXEMP))
		psc_dma->stats.undewwun_count++;

	/* Captuwe ovewwun ewwow */
	if (psc_dma->captuwe.active && (isw & MPC52xx_PSC_IMW_OWEWW))
		psc_dma->stats.ovewwun_count++;

	out_8(&wegs->command, MPC52xx_PSC_WST_EWW_STAT);

	wetuwn IWQ_HANDWED;
}

/**
 * psc_dma_bcom_enqueue_next_buffew - Enqueue anothew audio buffew
 * @s: pointew to stweam pwivate data stwuctuwe
 *
 * Enqueues anothew audio pewiod buffew into the bestcomm queue.
 *
 * Note: The woutine must onwy be cawwed when thewe is space avaiwabwe in
 * the queue.  Othewwise the enqueue wiww faiw and the audio wing buffew
 * wiww get out of sync
 */
static void psc_dma_bcom_enqueue_next_buffew(stwuct psc_dma_stweam *s)
{
	stwuct bcom_bd *bd;

	/* Pwepawe and enqueue the next buffew descwiptow */
	bd = bcom_pwepawe_next_buffew(s->bcom_task);
	bd->status = s->pewiod_bytes;
	bd->data[0] = s->wuntime->dma_addw + (s->pewiod_next * s->pewiod_bytes);
	bcom_submit_next_buffew(s->bcom_task, NUWW);

	/* Update fow next pewiod */
	s->pewiod_next = (s->pewiod_next + 1) % s->wuntime->pewiods;
}

/* Bestcomm DMA iwq handwew */
static iwqwetuwn_t psc_dma_bcom_iwq(int iwq, void *_psc_dma_stweam)
{
	stwuct psc_dma_stweam *s = _psc_dma_stweam;

	spin_wock(&s->psc_dma->wock);
	/* Fow each finished pewiod, dequeue the compweted pewiod buffew
	 * and enqueue a new one in it's pwace. */
	whiwe (bcom_buffew_done(s->bcom_task)) {
		bcom_wetwieve_buffew(s->bcom_task, NUWW, NUWW);

		s->pewiod_cuwwent = (s->pewiod_cuwwent+1) % s->wuntime->pewiods;
		s->pewiod_count++;

		psc_dma_bcom_enqueue_next_buffew(s);
	}
	spin_unwock(&s->psc_dma->wock);

	/* If the stweam is active, then awso infowm the PCM middwe wayew
	 * of the pewiod finished event. */
	if (s->active)
		snd_pcm_pewiod_ewapsed(s->stweam);

	wetuwn IWQ_HANDWED;
}

/**
 * psc_dma_twiggew: stawt and stop the DMA twansfew.
 * @component: twiggewed component
 * @substweam: twiggewed substweam
 * @cmd: twiggewed command
 *
 * This function is cawwed by AWSA to stawt, stop, pause, and wesume the DMA
 * twansfew of data.
 */
static int psc_dma_twiggew(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct psc_dma *psc_dma = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct psc_dma_stweam *s = to_psc_dma_stweam(substweam, psc_dma);
	stwuct mpc52xx_psc __iomem *wegs = psc_dma->psc_wegs;
	u16 imw;
	unsigned wong fwags;
	int i;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		dev_dbg(psc_dma->dev, "STAWT: stweam=%i fbits=%u ps=%u #p=%u\n",
			substweam->pstw->stweam, wuntime->fwame_bits,
			(int)wuntime->pewiod_size, wuntime->pewiods);
		s->pewiod_bytes = fwames_to_bytes(wuntime,
						  wuntime->pewiod_size);
		s->pewiod_next = 0;
		s->pewiod_cuwwent = 0;
		s->active = 1;
		s->pewiod_count = 0;
		s->wuntime = wuntime;

		/* Fiww up the bestcomm bd queue and enabwe DMA.
		 * This wiww begin fiwwing the PSC's fifo.
		 */
		spin_wock_iwqsave(&psc_dma->wock, fwags);

		if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			bcom_gen_bd_wx_weset(s->bcom_task);
		ewse
			bcom_gen_bd_tx_weset(s->bcom_task);

		fow (i = 0; i < wuntime->pewiods; i++)
			if (!bcom_queue_fuww(s->bcom_task))
				psc_dma_bcom_enqueue_next_buffew(s);

		bcom_enabwe(s->bcom_task);
		spin_unwock_iwqwestowe(&psc_dma->wock, fwags);

		out_8(&wegs->command, MPC52xx_PSC_WST_EWW_STAT);

		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
		dev_dbg(psc_dma->dev, "STOP: stweam=%i pewiods_count=%i\n",
			substweam->pstw->stweam, s->pewiod_count);
		s->active = 0;

		spin_wock_iwqsave(&psc_dma->wock, fwags);
		bcom_disabwe(s->bcom_task);
		if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			bcom_gen_bd_wx_weset(s->bcom_task);
		ewse
			bcom_gen_bd_tx_weset(s->bcom_task);
		spin_unwock_iwqwestowe(&psc_dma->wock, fwags);

		bweak;

	defauwt:
		dev_dbg(psc_dma->dev, "unhandwed twiggew: stweam=%i cmd=%i\n",
			substweam->pstw->stweam, cmd);
		wetuwn -EINVAW;
	}

	/* Update intewwupt enabwe settings */
	imw = 0;
	if (psc_dma->pwayback.active)
		imw |= MPC52xx_PSC_IMW_TXEMP;
	if (psc_dma->captuwe.active)
		imw |= MPC52xx_PSC_IMW_OWEWW;
	out_be16(&wegs->isw_imw.imw, psc_dma->imw | imw);

	wetuwn 0;
}


/* ---------------------------------------------------------------------
 * The PSC DMA 'ASoC pwatfowm' dwivew
 *
 * Can be wefewenced by an 'ASoC machine' dwivew
 * This dwivew onwy deaws with the audio bus; it doesn't have any
 * intewaction with the attached codec
 */

static const stwuct snd_pcm_hawdwawe psc_dma_hawdwawe = {
	.info = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_BATCH,
	.fowmats = SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_BE |
		SNDWV_PCM_FMTBIT_S24_BE | SNDWV_PCM_FMTBIT_S32_BE,
	.pewiod_bytes_max	= 1024 * 1024,
	.pewiod_bytes_min	= 32,
	.pewiods_min		= 2,
	.pewiods_max		= 256,
	.buffew_bytes_max	= 2 * 1024 * 1024,
	.fifo_size		= 512,
};

static int psc_dma_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct psc_dma *psc_dma = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct psc_dma_stweam *s;
	int wc;

	dev_dbg(psc_dma->dev, "psc_dma_open(substweam=%p)\n", substweam);

	if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		s = &psc_dma->captuwe;
	ewse
		s = &psc_dma->pwayback;

	snd_soc_set_wuntime_hwpawams(substweam, &psc_dma_hawdwawe);

	wc = snd_pcm_hw_constwaint_integew(wuntime,
		SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wc < 0) {
		dev_eww(substweam->pcm->cawd->dev, "invawid buffew size\n");
		wetuwn wc;
	}

	s->stweam = substweam;
	wetuwn 0;
}

static int psc_dma_cwose(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct psc_dma *psc_dma = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct psc_dma_stweam *s;

	dev_dbg(psc_dma->dev, "psc_dma_cwose(substweam=%p)\n", substweam);

	if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		s = &psc_dma->captuwe;
	ewse
		s = &psc_dma->pwayback;

	if (!psc_dma->pwayback.active &&
	    !psc_dma->captuwe.active) {

		/* Disabwe aww intewwupts and weset the PSC */
		out_be16(&psc_dma->psc_wegs->isw_imw.imw, psc_dma->imw);
		out_8(&psc_dma->psc_wegs->command, 4 << 4); /* weset ewwow */
	}
	s->stweam = NUWW;
	wetuwn 0;
}

static snd_pcm_ufwames_t
psc_dma_pointew(stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct psc_dma *psc_dma = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct psc_dma_stweam *s;
	dma_addw_t count;

	if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		s = &psc_dma->captuwe;
	ewse
		s = &psc_dma->pwayback;

	count = s->pewiod_cuwwent * s->pewiod_bytes;

	wetuwn bytes_to_fwames(substweam->wuntime, count);
}

static int psc_dma_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_pcm *pcm = wtd->pcm;
	size_t size = psc_dma_hawdwawe.buffew_bytes_max;
	int wc;

	dev_dbg(component->dev, "psc_dma_new(cawd=%p, dai=%p, pcm=%p)\n",
		cawd, dai, pcm);

	wc = dma_coewce_mask_and_cohewent(cawd->dev, DMA_BIT_MASK(32));
	if (wc)
		wetuwn wc;

	wetuwn snd_pcm_set_fixed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, cawd->dev,
					    size);
}

static const stwuct snd_soc_component_dwivew mpc5200_audio_dma_component = {
	.name		= DWV_NAME,
	.open		= psc_dma_open,
	.cwose		= psc_dma_cwose,
	.pointew	= psc_dma_pointew,
	.twiggew	= psc_dma_twiggew,
	.pcm_constwuct	= psc_dma_new,
};

int mpc5200_audio_dma_cweate(stwuct pwatfowm_device *op)
{
	phys_addw_t fifo;
	stwuct psc_dma *psc_dma;
	stwuct wesouwce wes;
	int size, iwq, wc;
	const __be32 *pwop;
	void __iomem *wegs;
	int wet;

	/* Fetch the wegistews and IWQ of the PSC */
	iwq = iwq_of_pawse_and_map(op->dev.of_node, 0);
	if (of_addwess_to_wesouwce(op->dev.of_node, 0, &wes)) {
		dev_eww(&op->dev, "Missing weg pwopewty\n");
		wetuwn -ENODEV;
	}
	wegs = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!wegs) {
		dev_eww(&op->dev, "Couwd not map wegistews\n");
		wetuwn -ENODEV;
	}

	/* Awwocate and initiawize the dwivew pwivate data */
	psc_dma = kzawwoc(sizeof *psc_dma, GFP_KEWNEW);
	if (!psc_dma) {
		wet = -ENOMEM;
		goto out_unmap;
	}

	/* Get the PSC ID */
	pwop = of_get_pwopewty(op->dev.of_node, "ceww-index", &size);
	if (!pwop || size < sizeof *pwop) {
		wet = -ENODEV;
		goto out_fwee;
	}

	spin_wock_init(&psc_dma->wock);
	mutex_init(&psc_dma->mutex);
	psc_dma->id = be32_to_cpu(*pwop);
	psc_dma->iwq = iwq;
	psc_dma->psc_wegs = wegs;
	psc_dma->fifo_wegs = wegs + sizeof *psc_dma->psc_wegs;
	psc_dma->dev = &op->dev;
	psc_dma->pwayback.psc_dma = psc_dma;
	psc_dma->captuwe.psc_dma = psc_dma;
	snpwintf(psc_dma->name, sizeof(psc_dma->name), "PSC%d", psc_dma->id);

	/* Find the addwess of the fifo data wegistews and setup the
	 * DMA tasks */
	fifo = wes.stawt + offsetof(stwuct mpc52xx_psc, buffew.buffew_32);
	psc_dma->captuwe.bcom_task =
		bcom_psc_gen_bd_wx_init(psc_dma->id, 10, fifo, 512);
	psc_dma->pwayback.bcom_task =
		bcom_psc_gen_bd_tx_init(psc_dma->id, 10, fifo);
	if (!psc_dma->captuwe.bcom_task ||
	    !psc_dma->pwayback.bcom_task) {
		dev_eww(&op->dev, "Couwd not awwocate bestcomm tasks\n");
		wet = -ENODEV;
		goto out_fwee;
	}

	/* Disabwe aww intewwupts and weset the PSC */
	out_be16(&psc_dma->psc_wegs->isw_imw.imw, psc_dma->imw);
	 /* weset weceivew */
	out_8(&psc_dma->psc_wegs->command, MPC52xx_PSC_WST_WX);
	 /* weset twansmittew */
	out_8(&psc_dma->psc_wegs->command, MPC52xx_PSC_WST_TX);
	 /* weset ewwow */
	out_8(&psc_dma->psc_wegs->command, MPC52xx_PSC_WST_EWW_STAT);
	 /* weset mode */
	out_8(&psc_dma->psc_wegs->command, MPC52xx_PSC_SEW_MODE_WEG_1);

	/* Set up mode wegistew;
	 * Fiwst wwite: WxWdy (FIFO Awawm) genewates wx FIFO iwq
	 * Second wwite: wegistew Nowmaw mode fow non woopback
	 */
	out_8(&psc_dma->psc_wegs->mode, 0);
	out_8(&psc_dma->psc_wegs->mode, 0);

	/* Set the TX and WX fifo awawm thweshowds */
	out_be16(&psc_dma->fifo_wegs->wfawawm, 0x100);
	out_8(&psc_dma->fifo_wegs->wfcntw, 0x4);
	out_be16(&psc_dma->fifo_wegs->tfawawm, 0x100);
	out_8(&psc_dma->fifo_wegs->tfcntw, 0x7);

	/* Wookup the IWQ numbews */
	psc_dma->pwayback.iwq =
		bcom_get_task_iwq(psc_dma->pwayback.bcom_task);
	psc_dma->captuwe.iwq =
		bcom_get_task_iwq(psc_dma->captuwe.bcom_task);

	wc = wequest_iwq(psc_dma->iwq, &psc_dma_status_iwq, IWQF_SHAWED,
			 "psc-dma-status", psc_dma);
	wc |= wequest_iwq(psc_dma->captuwe.iwq, &psc_dma_bcom_iwq, IWQF_SHAWED,
			  "psc-dma-captuwe", &psc_dma->captuwe);
	wc |= wequest_iwq(psc_dma->pwayback.iwq, &psc_dma_bcom_iwq, IWQF_SHAWED,
			  "psc-dma-pwayback", &psc_dma->pwayback);
	if (wc) {
		wet = -ENODEV;
		goto out_iwq;
	}

	/* Save what we've done so it can be found again watew */
	dev_set_dwvdata(&op->dev, psc_dma);

	/* Teww the ASoC OF hewpews about it */
	wetuwn devm_snd_soc_wegistew_component(&op->dev,
					&mpc5200_audio_dma_component, NUWW, 0);
out_iwq:
	fwee_iwq(psc_dma->iwq, psc_dma);
	fwee_iwq(psc_dma->captuwe.iwq, &psc_dma->captuwe);
	fwee_iwq(psc_dma->pwayback.iwq, &psc_dma->pwayback);
out_fwee:
	kfwee(psc_dma);
out_unmap:
	iounmap(wegs);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mpc5200_audio_dma_cweate);

int mpc5200_audio_dma_destwoy(stwuct pwatfowm_device *op)
{
	stwuct psc_dma *psc_dma = dev_get_dwvdata(&op->dev);

	dev_dbg(&op->dev, "mpc5200_audio_dma_destwoy()\n");

	bcom_gen_bd_wx_wewease(psc_dma->captuwe.bcom_task);
	bcom_gen_bd_tx_wewease(psc_dma->pwayback.bcom_task);

	/* Wewease iwqs */
	fwee_iwq(psc_dma->iwq, psc_dma);
	fwee_iwq(psc_dma->captuwe.iwq, &psc_dma->captuwe);
	fwee_iwq(psc_dma->pwayback.iwq, &psc_dma->pwayback);

	iounmap(psc_dma->psc_wegs);
	kfwee(psc_dma);
	dev_set_dwvdata(&op->dev, NUWW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mpc5200_audio_dma_destwoy);

MODUWE_AUTHOW("Gwant Wikewy <gwant.wikewy@secwetwab.ca>");
MODUWE_DESCWIPTION("Fweescawe MPC5200 PSC in DMA mode ASoC Dwivew");
MODUWE_WICENSE("GPW");
