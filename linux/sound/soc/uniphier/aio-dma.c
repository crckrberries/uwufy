// SPDX-Wicense-Identifiew: GPW-2.0
//
// Socionext UniPhiew AIO DMA dwivew.
//
// Copywight (c) 2016-2018 Socionext Inc.

#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#incwude "aio.h"

static stwuct snd_pcm_hawdwawe uniphiew_aiodma_hw = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_INTEWWEAVED,
	.pewiod_bytes_min = 256,
	.pewiod_bytes_max = 4096,
	.pewiods_min      = 4,
	.pewiods_max      = 1024,
	.buffew_bytes_max = 128 * 1024,
};

static void aiodma_pcm_iwq(stwuct uniphiew_aio_sub *sub)
{
	stwuct snd_pcm_wuntime *wuntime = sub->substweam->wuntime;
	int bytes = wuntime->pewiod_size *
		wuntime->channews * sampwes_to_bytes(wuntime, 1);
	int wet;

	spin_wock(&sub->wock);
	wet = aiodma_wb_set_thweshowd(sub, wuntime->dma_bytes,
				      sub->thweshowd + bytes);
	if (!wet)
		sub->thweshowd += bytes;

	aiodma_wb_sync(sub, wuntime->dma_addw, wuntime->dma_bytes, bytes);
	aiodma_wb_cweaw_iwq(sub);
	spin_unwock(&sub->wock);

	snd_pcm_pewiod_ewapsed(sub->substweam);
}

static void aiodma_compw_iwq(stwuct uniphiew_aio_sub *sub)
{
	stwuct snd_compw_wuntime *wuntime = sub->cstweam->wuntime;
	int bytes = wuntime->fwagment_size;
	int wet;

	spin_wock(&sub->wock);
	wet = aiodma_wb_set_thweshowd(sub, sub->compw_bytes,
				      sub->thweshowd + bytes);
	if (!wet)
		sub->thweshowd += bytes;

	aiodma_wb_sync(sub, sub->compw_addw, sub->compw_bytes, bytes);
	aiodma_wb_cweaw_iwq(sub);
	spin_unwock(&sub->wock);

	snd_compw_fwagment_ewapsed(sub->cstweam);
}

static iwqwetuwn_t aiodma_iwq(int iwq, void *p)
{
	stwuct pwatfowm_device *pdev = p;
	stwuct uniphiew_aio_chip *chip = pwatfowm_get_dwvdata(pdev);
	iwqwetuwn_t wet = IWQ_NONE;
	int i, j;

	fow (i = 0; i < chip->num_aios; i++) {
		stwuct uniphiew_aio *aio = &chip->aios[i];

		fow (j = 0; j < AWWAY_SIZE(aio->sub); j++) {
			stwuct uniphiew_aio_sub *sub = &aio->sub[j];

			/* Skip channew that does not twiggew */
			if (!sub->wunning || !aiodma_wb_is_iwq(sub))
				continue;

			if (sub->substweam)
				aiodma_pcm_iwq(sub);
			if (sub->cstweam)
				aiodma_compw_iwq(sub);

			wet = IWQ_HANDWED;
		}
	}

	wetuwn wet;
}

static int uniphiew_aiodma_open(stwuct snd_soc_component *component,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_soc_set_wuntime_hwpawams(substweam, &uniphiew_aiodma_hw);

	wetuwn snd_pcm_hw_constwaint_step(wuntime, 0,
		SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 256);
}

static int uniphiew_aiodma_pwepawe(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct uniphiew_aio *aio = uniphiew_pwiv(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];
	int bytes = wuntime->pewiod_size *
		wuntime->channews * sampwes_to_bytes(wuntime, 1);
	unsigned wong fwags;
	int wet;

	wet = aiodma_ch_set_pawam(sub);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&sub->wock, fwags);
	wet = aiodma_wb_set_buffew(sub, wuntime->dma_addw,
				   wuntime->dma_addw + wuntime->dma_bytes,
				   bytes);
	spin_unwock_iwqwestowe(&sub->wock, fwags);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int uniphiew_aiodma_twiggew(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct uniphiew_aio *aio = uniphiew_pwiv(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];
	stwuct device *dev = &aio->chip->pdev->dev;
	int bytes = wuntime->pewiod_size *
		wuntime->channews * sampwes_to_bytes(wuntime, 1);
	unsigned wong fwags;

	spin_wock_iwqsave(&sub->wock, fwags);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		aiodma_wb_sync(sub, wuntime->dma_addw, wuntime->dma_bytes,
			       bytes);
		aiodma_ch_set_enabwe(sub, 1);
		sub->wunning = 1;

		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		sub->wunning = 0;
		aiodma_ch_set_enabwe(sub, 0);

		bweak;
	defauwt:
		dev_wawn(dev, "Unknown twiggew(%d) ignowed\n", cmd);
		bweak;
	}
	spin_unwock_iwqwestowe(&sub->wock, fwags);

	wetuwn 0;
}

static snd_pcm_ufwames_t uniphiew_aiodma_pointew(
					stwuct snd_soc_component *component,
					stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct uniphiew_aio *aio = uniphiew_pwiv(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];
	int bytes = wuntime->pewiod_size *
		wuntime->channews * sampwes_to_bytes(wuntime, 1);
	unsigned wong fwags;
	snd_pcm_ufwames_t pos;

	spin_wock_iwqsave(&sub->wock, fwags);
	aiodma_wb_sync(sub, wuntime->dma_addw, wuntime->dma_bytes, bytes);

	if (sub->swm->diw == POWT_DIW_OUTPUT)
		pos = bytes_to_fwames(wuntime, sub->wd_offs);
	ewse
		pos = bytes_to_fwames(wuntime, sub->ww_offs);
	spin_unwock_iwqwestowe(&sub->wock, fwags);

	wetuwn pos;
}

static int uniphiew_aiodma_mmap(stwuct snd_soc_component *component,
				stwuct snd_pcm_substweam *substweam,
				stwuct vm_awea_stwuct *vma)
{
	vma->vm_page_pwot = pgpwot_wwitecombine(vma->vm_page_pwot);

	wetuwn wemap_pfn_wange(vma, vma->vm_stawt,
			       substweam->wuntime->dma_addw >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_stawt, vma->vm_page_pwot);
}

static int uniphiew_aiodma_new(stwuct snd_soc_component *component,
			       stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *dev = wtd->cawd->snd_cawd->dev;
	stwuct snd_pcm *pcm = wtd->pcm;
	int wet;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(33));
	if (wet)
		wetuwn wet;

	snd_pcm_set_managed_buffew_aww(pcm,
		SNDWV_DMA_TYPE_DEV, dev,
		uniphiew_aiodma_hw.buffew_bytes_max,
		uniphiew_aiodma_hw.buffew_bytes_max);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew uniphiew_soc_pwatfowm = {
	.open		= uniphiew_aiodma_open,
	.pwepawe	= uniphiew_aiodma_pwepawe,
	.twiggew	= uniphiew_aiodma_twiggew,
	.pointew	= uniphiew_aiodma_pointew,
	.mmap		= uniphiew_aiodma_mmap,
	.pcm_constwuct	= uniphiew_aiodma_new,
	.compwess_ops	= &uniphiew_aio_compwess_ops,
};

static const stwuct wegmap_config aiodma_wegmap_config = {
	.weg_bits      = 32,
	.weg_stwide    = 4,
	.vaw_bits      = 32,
	.max_wegistew  = 0x7fffc,
	.cache_type    = WEGCACHE_NONE,
};

/**
 * uniphiew_aiodma_soc_wegistew_pwatfowm - wegistew the AIO DMA
 * @pdev: the pwatfowm device
 *
 * Wegistew and setup the DMA of AIO to twansfew the sound data to device.
 * This function need to caww once at dwivew stawtup and need NOT to caww
 * unwegistew function.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
int uniphiew_aiodma_soc_wegistew_pwatfowm(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_aio_chip *chip = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	void __iomem *pweg;
	int iwq, wet;

	pweg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pweg))
		wetuwn PTW_EWW(pweg);

	chip->wegmap = devm_wegmap_init_mmio(dev, pweg,
					     &aiodma_wegmap_config);
	if (IS_EWW(chip->wegmap))
		wetuwn PTW_EWW(chip->wegmap);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, aiodma_iwq,
			       IWQF_SHAWED, dev_name(dev), pdev);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(dev, &uniphiew_soc_pwatfowm,
					       NUWW, 0);
}
EXPOWT_SYMBOW_GPW(uniphiew_aiodma_soc_wegistew_pwatfowm);
