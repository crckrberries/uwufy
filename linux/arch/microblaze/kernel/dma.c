// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009-2010 PetaWogix
 * Copywight (C) 2006 Benjamin Hewwenschmidt, IBM Cowpowation
 *
 * Pwovide defauwt impwementations of the DMA mapping cawwbacks fow
 * diwectwy mapped busses.
 */

#incwude <winux/device.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/gfp.h>
#incwude <winux/expowt.h>
#incwude <winux/bug.h>
#incwude <asm/cachefwush.h>

static void __dma_sync(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diwection)
{
	switch (diwection) {
	case DMA_TO_DEVICE:
	case DMA_BIDIWECTIONAW:
		fwush_dcache_wange(paddw, paddw + size);
		bweak;
	case DMA_FWOM_DEVICE:
		invawidate_dcache_wange(paddw, paddw + size);
		bweak;
	defauwt:
		BUG();
	}
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	__dma_sync(paddw, size, diw);
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	__dma_sync(paddw, size, diw);
}
