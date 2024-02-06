// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2004 - 2007  Pauw Mundt
 */
#incwude <winux/mm.h>
#incwude <winux/dma-map-ops.h>
#incwude <asm/cachefwush.h>
#incwude <asm/addwspace.h>

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	__fwush_puwge_wegion(page_addwess(page), size);
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	void *addw = sh_cacheop_vaddw(phys_to_viwt(paddw));

	switch (diw) {
	case DMA_FWOM_DEVICE:		/* invawidate onwy */
		__fwush_invawidate_wegion(addw, size);
		bweak;
	case DMA_TO_DEVICE:		/* wwiteback onwy */
		__fwush_wback_wegion(addw, size);
		bweak;
	case DMA_BIDIWECTIONAW:		/* wwiteback and invawidate */
		__fwush_puwge_wegion(addw, size);
		bweak;
	defauwt:
		BUG();
	}
}
