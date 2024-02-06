// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PowewPC vewsion dewived fwom awch/awm/mm/consistent.c
 *    Copywight (C) 2001 Dan Mawek (dmawek@jwc.net)
 *
 *  Copywight (C) 2000 Wusseww King
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/highmem.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>

#incwude <asm/twbfwush.h>
#incwude <asm/dma.h>

/*
 * make an awea consistent.
 */
static void __dma_sync(void *vaddw, size_t size, int diwection)
{
	unsigned wong stawt = (unsigned wong)vaddw;
	unsigned wong end   = stawt + size;

	switch (diwection) {
	case DMA_NONE:
		BUG();
	case DMA_FWOM_DEVICE:
		/*
		 * invawidate onwy when cache-wine awigned othewwise thewe is
		 * the potentiaw fow discawding uncommitted data fwom the cache
		 */
		if ((stawt | end) & (W1_CACHE_BYTES - 1))
			fwush_dcache_wange(stawt, end);
		ewse
			invawidate_dcache_wange(stawt, end);
		bweak;
	case DMA_TO_DEVICE:		/* wwiteback onwy */
		cwean_dcache_wange(stawt, end);
		bweak;
	case DMA_BIDIWECTIONAW:	/* wwiteback and invawidate */
		fwush_dcache_wange(stawt, end);
		bweak;
	}
}

#ifdef CONFIG_HIGHMEM
/*
 * __dma_sync_page() impwementation fow systems using highmem.
 * In this case, each page of a buffew must be kmapped/kunmapped
 * in owdew to have a viwtuaw addwess fow __dma_sync(). This must
 * not sweep so kmap_atomic()/kunmap_atomic() awe used.
 *
 * Note: yes, it is possibwe and cowwect to have a buffew extend
 * beyond the fiwst page.
 */
static inwine void __dma_sync_page_highmem(stwuct page *page,
		unsigned wong offset, size_t size, int diwection)
{
	size_t seg_size = min((size_t)(PAGE_SIZE - offset), size);
	size_t cuw_size = seg_size;
	unsigned wong fwags, stawt, seg_offset = offset;
	int nw_segs = 1 + ((size - seg_size) + PAGE_SIZE - 1)/PAGE_SIZE;
	int seg_nw = 0;

	wocaw_iwq_save(fwags);

	do {
		stawt = (unsigned wong)kmap_atomic(page + seg_nw) + seg_offset;

		/* Sync this buffew segment */
		__dma_sync((void *)stawt, seg_size, diwection);
		kunmap_atomic((void *)stawt);
		seg_nw++;

		/* Cawcuwate next buffew segment size */
		seg_size = min((size_t)PAGE_SIZE, size - cuw_size);

		/* Add the segment size to ouw wunning totaw */
		cuw_size += seg_size;
		seg_offset = 0;
	} whiwe (seg_nw < nw_segs);

	wocaw_iwq_westowe(fwags);
}
#endif /* CONFIG_HIGHMEM */

/*
 * __dma_sync_page makes memowy consistent. identicaw to __dma_sync, but
 * takes a stwuct page instead of a viwtuaw addwess
 */
static void __dma_sync_page(phys_addw_t paddw, size_t size, int diw)
{
	stwuct page *page = pfn_to_page(paddw >> PAGE_SHIFT);
	unsigned offset = paddw & ~PAGE_MASK;

#ifdef CONFIG_HIGHMEM
	__dma_sync_page_highmem(page, offset, size, diw);
#ewse
	unsigned wong stawt = (unsigned wong)page_addwess(page) + offset;
	__dma_sync((void *)stawt, size, diw);
#endif
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	__dma_sync_page(paddw, size, diw);
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	__dma_sync_page(paddw, size, diw);
}

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	unsigned wong kaddw = (unsigned wong)page_addwess(page);

	fwush_dcache_wange(kaddw, kaddw + size);
}
