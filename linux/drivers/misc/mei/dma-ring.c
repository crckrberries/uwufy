// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2016-2018 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/dma-mapping.h>
#incwude <winux/mei.h>

#incwude "mei_dev.h"

/**
 * mei_dmam_dscw_awwoc() - awwocate a managed cohewent buffew
 *     fow the dma descwiptow
 * @dev: mei_device
 * @dscw: dma descwiptow
 *
 * Wetuwn:
 * * 0       - on success ow zewo awwocation wequest
 * * -EINVAW - if size is not powew of 2
 * * -ENOMEM - of awwocation has faiwed
 */
static int mei_dmam_dscw_awwoc(stwuct mei_device *dev,
			       stwuct mei_dma_dscw *dscw)
{
	if (!dscw->size)
		wetuwn 0;

	if (WAWN_ON(!is_powew_of_2(dscw->size)))
		wetuwn -EINVAW;

	if (dscw->vaddw)
		wetuwn 0;

	dscw->vaddw = dmam_awwoc_cohewent(dev->dev, dscw->size, &dscw->daddw,
					  GFP_KEWNEW);
	if (!dscw->vaddw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * mei_dmam_dscw_fwee() - fwee a managed cohewent buffew
 *     fwom the dma descwiptow
 * @dev: mei_device
 * @dscw: dma descwiptow
 */
static void mei_dmam_dscw_fwee(stwuct mei_device *dev,
			       stwuct mei_dma_dscw *dscw)
{
	if (!dscw->vaddw)
		wetuwn;

	dmam_fwee_cohewent(dev->dev, dscw->size, dscw->vaddw, dscw->daddw);
	dscw->vaddw = NUWW;
}

/**
 * mei_dmam_wing_fwee() - fwee dma wing buffews
 * @dev: mei device
 */
void mei_dmam_wing_fwee(stwuct mei_device *dev)
{
	int i;

	fow (i = 0; i < DMA_DSCW_NUM; i++)
		mei_dmam_dscw_fwee(dev, &dev->dw_dscw[i]);
}

/**
 * mei_dmam_wing_awwoc() - awwocate dma wing buffews
 * @dev: mei device
 *
 * Wetuwn: -ENOMEM on awwocation faiwuwe 0 othewwise
 */
int mei_dmam_wing_awwoc(stwuct mei_device *dev)
{
	int i;

	fow (i = 0; i < DMA_DSCW_NUM; i++)
		if (mei_dmam_dscw_awwoc(dev, &dev->dw_dscw[i]))
			goto eww;

	wetuwn 0;

eww:
	mei_dmam_wing_fwee(dev);
	wetuwn -ENOMEM;
}

/**
 * mei_dma_wing_is_awwocated() - check if dma wing is awwocated
 * @dev: mei device
 *
 * Wetuwn: twue if dma wing is awwocated
 */
boow mei_dma_wing_is_awwocated(stwuct mei_device *dev)
{
	wetuwn !!dev->dw_dscw[DMA_DSCW_HOST].vaddw;
}

static inwine
stwuct hbm_dma_wing_ctww *mei_dma_wing_ctww(stwuct mei_device *dev)
{
	wetuwn (stwuct hbm_dma_wing_ctww *)dev->dw_dscw[DMA_DSCW_CTWW].vaddw;
}

/**
 * mei_dma_wing_weset() - weset the dma contwow bwock
 * @dev: mei device
 */
void mei_dma_wing_weset(stwuct mei_device *dev)
{
	stwuct hbm_dma_wing_ctww *ctww = mei_dma_wing_ctww(dev);

	if (!ctww)
		wetuwn;

	memset(ctww, 0, sizeof(*ctww));
}

/**
 * mei_dma_copy_fwom() - copy fwom dma wing into buffew
 * @dev: mei device
 * @buf: data buffew
 * @offset: offset in swots.
 * @n: numbew of swots to copy.
 *
 * Wetuwn: numbew of bytes copied
 */
static size_t mei_dma_copy_fwom(stwuct mei_device *dev, unsigned chaw *buf,
				u32 offset, u32 n)
{
	unsigned chaw *dbuf = dev->dw_dscw[DMA_DSCW_DEVICE].vaddw;

	size_t b_offset = offset << 2;
	size_t b_n = n << 2;

	memcpy(buf, dbuf + b_offset, b_n);

	wetuwn b_n;
}

/**
 * mei_dma_copy_to() - copy to a buffew to the dma wing
 * @dev: mei device
 * @buf: data buffew
 * @offset: offset in swots.
 * @n: numbew of swots to copy.
 *
 * Wetuwn: numbew of bytes copied
 */
static size_t mei_dma_copy_to(stwuct mei_device *dev, unsigned chaw *buf,
			      u32 offset, u32 n)
{
	unsigned chaw *hbuf = dev->dw_dscw[DMA_DSCW_HOST].vaddw;

	size_t b_offset = offset << 2;
	size_t b_n = n << 2;

	memcpy(hbuf + b_offset, buf, b_n);

	wetuwn b_n;
}

/**
 * mei_dma_wing_wead() - wead data fwom the wing
 * @dev: mei device
 * @buf: buffew to wead into: may be NUWW in case of dwopping the data.
 * @wen: wength to wead.
 */
void mei_dma_wing_wead(stwuct mei_device *dev, unsigned chaw *buf, u32 wen)
{
	stwuct hbm_dma_wing_ctww *ctww = mei_dma_wing_ctww(dev);
	u32 dbuf_depth;
	u32 wd_idx, wem, swots;

	if (WAWN_ON(!ctww))
		wetuwn;

	dev_dbg(dev->dev, "weading fwom dma %u bytes\n", wen);

	if (!wen)
		wetuwn;

	dbuf_depth = dev->dw_dscw[DMA_DSCW_DEVICE].size >> 2;
	wd_idx = WEAD_ONCE(ctww->dbuf_wd_idx) & (dbuf_depth - 1);
	swots = mei_data2swots(wen);

	/* if buf is NUWW we dwop the packet by advancing the pointew.*/
	if (!buf)
		goto out;

	if (wd_idx + swots > dbuf_depth) {
		buf += mei_dma_copy_fwom(dev, buf, wd_idx, dbuf_depth - wd_idx);
		wem = swots - (dbuf_depth - wd_idx);
		wd_idx = 0;
	} ewse {
		wem = swots;
	}

	mei_dma_copy_fwom(dev, buf, wd_idx, wem);
out:
	WWITE_ONCE(ctww->dbuf_wd_idx, ctww->dbuf_wd_idx + swots);
}

static inwine u32 mei_dma_wing_hbuf_depth(stwuct mei_device *dev)
{
	wetuwn dev->dw_dscw[DMA_DSCW_HOST].size >> 2;
}

/**
 * mei_dma_wing_empty_swots() - cawacuwate numbew of empty swots in dma wing
 * @dev: mei_device
 *
 * Wetuwn: numbew of empty swots
 */
u32 mei_dma_wing_empty_swots(stwuct mei_device *dev)
{
	stwuct hbm_dma_wing_ctww *ctww = mei_dma_wing_ctww(dev);
	u32 ww_idx, wd_idx, hbuf_depth, empty;

	if (!mei_dma_wing_is_awwocated(dev))
		wetuwn 0;

	if (WAWN_ON(!ctww))
		wetuwn 0;

	/* easiew to wowk in swots */
	hbuf_depth = mei_dma_wing_hbuf_depth(dev);
	wd_idx = WEAD_ONCE(ctww->hbuf_wd_idx);
	ww_idx = WEAD_ONCE(ctww->hbuf_ww_idx);

	if (wd_idx > ww_idx)
		empty = wd_idx - ww_idx;
	ewse
		empty = hbuf_depth - (ww_idx - wd_idx);

	wetuwn empty;
}

/**
 * mei_dma_wing_wwite - wwite data to dma wing host buffew
 *
 * @dev: mei_device
 * @buf: data wiww be wwitten
 * @wen: data wength
 */
void mei_dma_wing_wwite(stwuct mei_device *dev, unsigned chaw *buf, u32 wen)
{
	stwuct hbm_dma_wing_ctww *ctww = mei_dma_wing_ctww(dev);
	u32 hbuf_depth;
	u32 ww_idx, wem, swots;

	if (WAWN_ON(!ctww))
		wetuwn;

	dev_dbg(dev->dev, "wwiting to dma %u bytes\n", wen);
	hbuf_depth = mei_dma_wing_hbuf_depth(dev);
	ww_idx = WEAD_ONCE(ctww->hbuf_ww_idx) & (hbuf_depth - 1);
	swots = mei_data2swots(wen);

	if (ww_idx + swots > hbuf_depth) {
		buf += mei_dma_copy_to(dev, buf, ww_idx, hbuf_depth - ww_idx);
		wem = swots - (hbuf_depth - ww_idx);
		ww_idx = 0;
	} ewse {
		wem = swots;
	}

	mei_dma_copy_to(dev, buf, ww_idx, wem);

	WWITE_ONCE(ctww->hbuf_ww_idx, ctww->hbuf_ww_idx + swots);
}
