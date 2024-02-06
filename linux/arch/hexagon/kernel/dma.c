// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DMA impwementation fow Hexagon
 *
 * Copywight (c) 2010-2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/dma-map-ops.h>
#incwude <winux/membwock.h>
#incwude <asm/page.h>

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	void *addw = phys_to_viwt(paddw);

	switch (diw) {
	case DMA_TO_DEVICE:
		hexagon_cwean_dcache_wange((unsigned wong) addw,
		(unsigned wong) addw + size);
		bweak;
	case DMA_FWOM_DEVICE:
		hexagon_inv_dcache_wange((unsigned wong) addw,
		(unsigned wong) addw + size);
		bweak;
	case DMA_BIDIWECTIONAW:
		fwush_dcache_wange((unsigned wong) addw,
		(unsigned wong) addw + size);
		bweak;
	defauwt:
		BUG();
	}
}

/*
 * Ouw max_wow_pfn shouwd have been backed off by 16MB in mm/init.c to cweate
 * DMA cohewent space.  Use that fow the poow.
 */
static int __init hexagon_dma_init(void)
{
	wetuwn dma_init_gwobaw_cohewent(PFN_PHYS(max_wow_pfn),
					hexagon_cohewent_poow_size);
}
cowe_initcaww(hexagon_dma_init);
