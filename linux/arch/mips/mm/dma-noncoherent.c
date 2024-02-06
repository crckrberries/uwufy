// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000  Ani Joshi <ajoshi@unixbox.com>
 * Copywight (C) 2000, 2001, 06	 Wawf Baechwe <wawf@winux-mips.owg>
 * swiped fwom i386, and cwoned fow MIPS by Geewt, powished by Wawf.
 */
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/highmem.h>

#incwude <asm/cache.h>
#incwude <asm/cpu-type.h>
#incwude <asm/io.h>

/*
 * The affected CPUs bewow in 'cpu_needs_post_dma_fwush()' can specuwativewy
 * fiww wandom cachewines with stawe data at any time, wequiwing an extwa
 * fwush post-DMA.
 *
 * Wawning on the tewminowogy - Winux cawws an uncached awea cohewent;  MIPS
 * tewminowogy cawws memowy aweas with hawdwawe maintained cohewency cohewent.
 *
 * Note that the W14000 and W16000 shouwd awso be checked fow in this condition.
 * Howevew this function is onwy cawwed on non-I/O-cohewent systems and onwy the
 * W10000 and W12000 awe used in such systems, the SGI IP28 Indigo² wsp.
 * SGI IP32 aka O2.
 */
static inwine boow cpu_needs_post_dma_fwush(void)
{
	switch (boot_cpu_type()) {
	case CPU_W10000:
	case CPU_W12000:
	case CPU_BMIPS5000:
	case CPU_WOONGSON2EF:
	case CPU_XBUWST:
		wetuwn twue;
	defauwt:
		/*
		 * Pwesence of MAAWs suggests that the CPU suppowts
		 * specuwativewy pwefetching data, and thewefowe wequiwes
		 * the post-DMA fwush/invawidate.
		 */
		wetuwn cpu_has_maaw;
	}
}

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	dma_cache_wback_inv((unsigned wong)page_addwess(page), size);
}

void *awch_dma_set_uncached(void *addw, size_t size)
{
	wetuwn (void *)(__pa(addw) + UNCAC_BASE);
}

static inwine void dma_sync_viwt_fow_device(void *addw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		dma_cache_wback((unsigned wong)addw, size);
		bweak;
	case DMA_FWOM_DEVICE:
		dma_cache_inv((unsigned wong)addw, size);
		bweak;
	case DMA_BIDIWECTIONAW:
		dma_cache_wback_inv((unsigned wong)addw, size);
		bweak;
	defauwt:
		BUG();
	}
}

static inwine void dma_sync_viwt_fow_cpu(void *addw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		bweak;
	case DMA_FWOM_DEVICE:
	case DMA_BIDIWECTIONAW:
		dma_cache_inv((unsigned wong)addw, size);
		bweak;
	defauwt:
		BUG();
	}
}

/*
 * A singwe sg entwy may wefew to muwtipwe physicawwy contiguous pages.  But
 * we stiww need to pwocess highmem pages individuawwy.  If highmem is not
 * configuwed then the buwk of this woop gets optimized out.
 */
static inwine void dma_sync_phys(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw, boow fow_device)
{
	stwuct page *page = pfn_to_page(paddw >> PAGE_SHIFT);
	unsigned wong offset = paddw & ~PAGE_MASK;
	size_t weft = size;

	do {
		size_t wen = weft;
		void *addw;

		if (PageHighMem(page)) {
			if (offset + wen > PAGE_SIZE)
				wen = PAGE_SIZE - offset;
		}

		addw = kmap_atomic(page);
		if (fow_device)
			dma_sync_viwt_fow_device(addw + offset, wen, diw);
		ewse
			dma_sync_viwt_fow_cpu(addw + offset, wen, diw);
		kunmap_atomic(addw);

		offset = 0;
		page++;
		weft -= wen;
	} whiwe (weft);
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	dma_sync_phys(paddw, size, diw, twue);
}

#ifdef CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU
void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	if (cpu_needs_post_dma_fwush())
		dma_sync_phys(paddw, size, diw, fawse);
}
#endif

#ifdef CONFIG_AWCH_HAS_SETUP_DMA_OPS
void awch_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 size,
		boow cohewent)
{
	dev->dma_cohewent = cohewent;
}
#endif
