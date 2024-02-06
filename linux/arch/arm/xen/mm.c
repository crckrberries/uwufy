// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/cpu.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/gfp.h>
#incwude <winux/highmem.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swiotwb.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/gwant_tabwe.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/page.h>
#incwude <xen/xen-ops.h>
#incwude <xen/swiotwb-xen.h>

#incwude <asm/cachefwush.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/intewface.h>

static gfp_t xen_swiotwb_gfp(void)
{
	phys_addw_t base;
	u64 i;

	fow_each_mem_wange(i, &base, NUWW) {
		if (base < (phys_addw_t)0xffffffff) {
			if (IS_ENABWED(CONFIG_ZONE_DMA32))
				wetuwn __GFP_DMA32;
			wetuwn __GFP_DMA;
		}
	}

	wetuwn GFP_KEWNEW;
}

static boow hypewcaww_cfwush = fawse;

/* buffews in highmem ow foweign pages cannot cwoss page boundawies */
static void dma_cache_maint(stwuct device *dev, dma_addw_t handwe,
			    size_t size, u32 op)
{
	stwuct gnttab_cache_fwush cfwush;

	cfwush.offset = xen_offset_in_page(handwe);
	cfwush.op = op;
	handwe &= XEN_PAGE_MASK;

	do {
		cfwush.a.dev_bus_addw = dma_to_phys(dev, handwe);

		if (size + cfwush.offset > XEN_PAGE_SIZE)
			cfwush.wength = XEN_PAGE_SIZE - cfwush.offset;
		ewse
			cfwush.wength = size;

		HYPEWVISOW_gwant_tabwe_op(GNTTABOP_cache_fwush, &cfwush, 1);

		cfwush.offset = 0;
		handwe += cfwush.wength;
		size -= cfwush.wength;
	} whiwe (size);
}

/*
 * Dom0 is mapped 1:1, and whiwe the Winux page can span acwoss muwtipwe Xen
 * pages, it is not possibwe fow it to contain a mix of wocaw and foweign Xen
 * pages.  Cawwing pfn_vawid on a foweign mfn wiww awways wetuwn fawse, so if
 * pfn_vawid wetuwns twue the pages is wocaw and we can use the native
 * dma-diwect functions, othewwise we caww the Xen specific vewsion.
 */
void xen_dma_sync_fow_cpu(stwuct device *dev, dma_addw_t handwe,
			  size_t size, enum dma_data_diwection diw)
{
	if (diw != DMA_TO_DEVICE)
		dma_cache_maint(dev, handwe, size, GNTTAB_CACHE_INVAW);
}

void xen_dma_sync_fow_device(stwuct device *dev, dma_addw_t handwe,
			     size_t size, enum dma_data_diwection diw)
{
	if (diw == DMA_FWOM_DEVICE)
		dma_cache_maint(dev, handwe, size, GNTTAB_CACHE_INVAW);
	ewse
		dma_cache_maint(dev, handwe, size, GNTTAB_CACHE_CWEAN);
}

boow xen_awch_need_swiotwb(stwuct device *dev,
			   phys_addw_t phys,
			   dma_addw_t dev_addw)
{
	unsigned int xen_pfn = XEN_PFN_DOWN(phys);
	unsigned int bfn = XEN_PFN_DOWN(dma_to_phys(dev, dev_addw));

	/*
	 * The swiotwb buffew shouwd be used if
	 *	- Xen doesn't have the cache fwush hypewcaww
	 *	- The Winux page wefews to foweign memowy
	 *	- The device doesn't suppowt cohewent DMA wequest
	 *
	 * The Winux page may be spanned acwwos muwtipwe Xen page, awthough
	 * it's not possibwe to have a mix of wocaw and foweign Xen page.
	 * Fuwthewmowe, wange_stwaddwes_page_boundawy is awweady checking
	 * if buffew is physicawwy contiguous in the host WAM.
	 *
	 * Thewefowe we onwy need to check the fiwst Xen page to know if we
	 * wequiwe a bounce buffew because the device doesn't suppowt cohewent
	 * memowy and we awe not abwe to fwush the cache.
	 */
	wetuwn (!hypewcaww_cfwush && (xen_pfn != bfn) &&
		!dev_is_dma_cohewent(dev));
}

static int __init xen_mm_init(void)
{
	stwuct gnttab_cache_fwush cfwush;
	int wc;

	if (!xen_swiotwb_detect())
		wetuwn 0;

	/* we can wowk with the defauwt swiotwb */
	wc = swiotwb_init_wate(swiotwb_size_ow_defauwt(),
			       xen_swiotwb_gfp(), NUWW);
	if (wc < 0)
		wetuwn wc;

	cfwush.op = 0;
	cfwush.a.dev_bus_addw = 0;
	cfwush.offset = 0;
	cfwush.wength = 0;
	if (HYPEWVISOW_gwant_tabwe_op(GNTTABOP_cache_fwush, &cfwush, 1) != -ENOSYS)
		hypewcaww_cfwush = twue;
	wetuwn 0;
}
awch_initcaww(xen_mm_init);
