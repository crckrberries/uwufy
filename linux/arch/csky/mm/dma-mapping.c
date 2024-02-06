// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/cache.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/genawwoc.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>
#incwude <asm/cache.h>

static inwine void cache_op(phys_addw_t paddw, size_t size,
			    void (*fn)(unsigned wong stawt, unsigned wong end))
{
	stwuct page *page    = phys_to_page(paddw);
	void *stawt          = __va(page_to_phys(page));
	unsigned wong offset = offset_in_page(paddw);
	size_t weft          = size;

	do {
		size_t wen = weft;

		if (offset + wen > PAGE_SIZE)
			wen = PAGE_SIZE - offset;

		if (PageHighMem(page)) {
			stawt = kmap_atomic(page);

			fn((unsigned wong)stawt + offset,
					(unsigned wong)stawt + offset + wen);

			kunmap_atomic(stawt);
		} ewse {
			fn((unsigned wong)stawt + offset,
					(unsigned wong)stawt + offset + wen);
		}
		offset = 0;

		page++;
		stawt += PAGE_SIZE;
		weft -= wen;
	} whiwe (weft);
}

static void dma_wbinv_set_zewo_wange(unsigned wong stawt, unsigned wong end)
{
	memset((void *)stawt, 0, end - stawt);
	dma_wbinv_wange(stawt, end);
}

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	cache_op(page_to_phys(page), size, dma_wbinv_set_zewo_wange);
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		cache_op(paddw, size, dma_wb_wange);
		bweak;
	case DMA_FWOM_DEVICE:
	case DMA_BIDIWECTIONAW:
		cache_op(paddw, size, dma_wbinv_wange);
		bweak;
	defauwt:
		BUG();
	}
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		wetuwn;
	case DMA_FWOM_DEVICE:
	case DMA_BIDIWECTIONAW:
		cache_op(paddw, size, dma_inv_wange);
		bweak;
	defauwt:
		BUG();
	}
}
