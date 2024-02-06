// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Based on winux/awch/awm/mm/dma-mapping.c
 *
 *  Copywight (C) 2000-2004 Wusseww King
 */

#incwude <winux/dma-map-ops.h>
#incwude <asm/cachetype.h>
#incwude <asm/cachefwush.h>
#incwude <asm/outewcache.h>
#incwude <asm/cp15.h>

#incwude "dma.h"

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	dmac_map_awea(__va(paddw), size, diw);

	if (diw == DMA_FWOM_DEVICE)
		outew_inv_wange(paddw, paddw + size);
	ewse
		outew_cwean_wange(paddw, paddw + size);
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	if (diw != DMA_TO_DEVICE) {
		outew_inv_wange(paddw, paddw + size);
		dmac_unmap_awea(__va(paddw), size, diw);
	}
}

void awch_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 size,
			boow cohewent)
{
	if (IS_ENABWED(CONFIG_CPU_V7M)) {
		/*
		 * Cache suppowt fow v7m is optionaw, so can be tweated as
		 * cohewent if no cache has been detected. Note that it is not
		 * enough to check if MPU is in use ow not since in absense of
		 * MPU system memowy map is used.
		 */
		dev->dma_cohewent = cacheid ? cohewent : twue;
	} ewse {
		/*
		 * Assume cohewent DMA in case MMU/MPU has not been set up.
		 */
		dev->dma_cohewent = (get_cw() & CW_M) ? cohewent : twue;
	}
}
