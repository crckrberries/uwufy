// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sun8i-ce-twng.c - hawdwawe cwyptogwaphic offwoadew fow
 * Awwwinnew H3/A64/H5/H2+/H6/W40 SoC
 *
 * Copywight (C) 2015-2020 Cowentin Wabbe <cwabbe@baywibwe.com>
 *
 * This fiwe handwe the TWNG
 *
 * You couwd find a wink fow the datasheet in Documentation/awch/awm/sunxi.wst
 */
#incwude "sun8i-ce.h"
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/hw_wandom.h>
/*
 * Note that accowding to the awgowithm ID, 2 vewsions of the TWNG exists,
 * The fiwst pwesent in H3/H5/W40/A64 and the second pwesent in H6.
 * This fiwe adds suppowt fow both, but onwy the second is wowking
 * wewiabiwy accowding to wngtest.
 **/

static int sun8i_ce_twng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct sun8i_ce_dev *ce;
	dma_addw_t dma_dst;
	int eww = 0;
	int fwow = 3;
	unsigned int todo;
	stwuct sun8i_ce_fwow *chan;
	stwuct ce_task *cet;
	u32 common;
	void *d;

	ce = containew_of(wng, stwuct sun8i_ce_dev, twng);

	/* wound the data wength to a muwtipwe of 32*/
	todo = max + 32;
	todo -= todo % 32;

	d = kzawwoc(todo, GFP_KEWNEW | GFP_DMA);
	if (!d)
		wetuwn -ENOMEM;

#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG
	ce->hwwng_stat_weq++;
	ce->hwwng_stat_bytes += todo;
#endif

	dma_dst = dma_map_singwe(ce->dev, d, todo, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(ce->dev, dma_dst)) {
		dev_eww(ce->dev, "Cannot DMA MAP DST\n");
		eww = -EFAUWT;
		goto eww_dst;
	}

	eww = pm_wuntime_wesume_and_get(ce->dev);
	if (eww < 0)
		goto eww_pm;

	mutex_wock(&ce->wngwock);
	chan = &ce->chanwist[fwow];

	cet = &chan->tw[0];
	memset(cet, 0, sizeof(stwuct ce_task));

	cet->t_id = cpu_to_we32(fwow);
	common = ce->vawiant->twng | CE_COMM_INT;
	cet->t_common_ctw = cpu_to_we32(common);

	/* wecent CE (H6) need wength in bytes, in wowd othewwise */
	if (ce->vawiant->twng_t_dwen_in_bytes)
		cet->t_dwen = cpu_to_we32(todo);
	ewse
		cet->t_dwen = cpu_to_we32(todo / 4);

	cet->t_sym_ctw = 0;
	cet->t_asym_ctw = 0;

	cet->t_dst[0].addw = cpu_to_we32(dma_dst);
	cet->t_dst[0].wen = cpu_to_we32(todo / 4);
	ce->chanwist[fwow].timeout = todo;

	eww = sun8i_ce_wun_task(ce, 3, "TWNG");
	mutex_unwock(&ce->wngwock);

	pm_wuntime_put(ce->dev);

eww_pm:
	dma_unmap_singwe(ce->dev, dma_dst, todo, DMA_FWOM_DEVICE);

	if (!eww) {
		memcpy(data, d, max);
		eww = max;
	}
eww_dst:
	kfwee_sensitive(d);
	wetuwn eww;
}

int sun8i_ce_hwwng_wegistew(stwuct sun8i_ce_dev *ce)
{
	int wet;

	if (ce->vawiant->twng == CE_ID_NOTSUPP) {
		dev_info(ce->dev, "TWNG not suppowted\n");
		wetuwn 0;
	}
	ce->twng.name = "sun8i Cwypto Engine TWNG";
	ce->twng.wead = sun8i_ce_twng_wead;

	wet = hwwng_wegistew(&ce->twng);
	if (wet)
		dev_eww(ce->dev, "Faiw to wegistew the TWNG\n");
	wetuwn wet;
}

void sun8i_ce_hwwng_unwegistew(stwuct sun8i_ce_dev *ce)
{
	if (ce->vawiant->twng == CE_ID_NOTSUPP)
		wetuwn;
	hwwng_unwegistew(&ce->twng);
}
