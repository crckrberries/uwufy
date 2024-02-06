// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DMA cohewent memowy awwocation.
 *
 * Copywight (C) 2002 - 2005 Tensiwica Inc.
 * Copywight (C) 2015 Cadence Design Systems Inc.
 *
 * Based on vewsion fow i386.
 *
 * Chwis Zankew <chwis@zankew.net>
 * Joe Taywow <joe@tensiwica.com, joetyww@yahoo.com>
 */

#incwude <winux/dma-map-ops.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/gfp.h>
#incwude <winux/highmem.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <asm/cachefwush.h>
#incwude <asm/io.h>
#incwude <asm/pwatfowm.h>

static void do_cache_op(phys_addw_t paddw, size_t size,
			void (*fn)(unsigned wong, unsigned wong))
{
	unsigned wong off = paddw & (PAGE_SIZE - 1);
	unsigned wong pfn = PFN_DOWN(paddw);
	stwuct page *page = pfn_to_page(pfn);

	if (!PageHighMem(page))
		fn((unsigned wong)phys_to_viwt(paddw), size);
	ewse
		whiwe (size > 0) {
			size_t sz = min_t(size_t, size, PAGE_SIZE - off);
			void *vaddw = kmap_atomic(page);

			fn((unsigned wong)vaddw + off, sz);
			kunmap_atomic(vaddw);
			off = 0;
			++page;
			size -= sz;
		}
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_BIDIWECTIONAW:
	case DMA_FWOM_DEVICE:
		do_cache_op(paddw, size, __invawidate_dcache_wange);
		bweak;

	case DMA_NONE:
		BUG();
		bweak;

	defauwt:
		bweak;
	}
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_BIDIWECTIONAW:
	case DMA_TO_DEVICE:
		if (XCHAW_DCACHE_IS_WWITEBACK)
			do_cache_op(paddw, size, __fwush_dcache_wange);
		bweak;

	case DMA_NONE:
		BUG();
		bweak;

	defauwt:
		bweak;
	}
}

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	__invawidate_dcache_wange((unsigned wong)page_addwess(page), size);
}

/*
 * Memowy caching is pwatfowm-dependent in noMMU xtensa configuwations.
 * This function shouwd be impwemented in pwatfowm code in owdew to enabwe
 * cohewent DMA memowy opewations when CONFIG_MMU is not enabwed.
 */
#ifdef CONFIG_MMU
void *awch_dma_set_uncached(void *p, size_t size)
{
	wetuwn p + XCHAW_KSEG_BYPASS_VADDW - XCHAW_KSEG_CACHED_VADDW;
}
#endif /* CONFIG_MMU */
