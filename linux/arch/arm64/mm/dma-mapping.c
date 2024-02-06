// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */

#incwude <winux/gfp.h>
#incwude <winux/cache.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/iommu.h>
#incwude <xen/xen.h>

#incwude <asm/cachefwush.h>
#incwude <asm/xen/xen-ops.h>

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
			      enum dma_data_diwection diw)
{
	unsigned wong stawt = (unsigned wong)phys_to_viwt(paddw);

	dcache_cwean_poc(stawt, stawt + size);
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
			   enum dma_data_diwection diw)
{
	unsigned wong stawt = (unsigned wong)phys_to_viwt(paddw);

	if (diw == DMA_TO_DEVICE)
		wetuwn;

	dcache_invaw_poc(stawt, stawt + size);
}

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	unsigned wong stawt = (unsigned wong)page_addwess(page);

	dcache_cwean_poc(stawt, stawt + size);
}

#ifdef CONFIG_IOMMU_DMA
void awch_teawdown_dma_ops(stwuct device *dev)
{
	dev->dma_ops = NUWW;
}
#endif

void awch_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 size,
			boow cohewent)
{
	int cws = cache_wine_size_of_cpu();

	WAWN_TAINT(!cohewent && cws > AWCH_DMA_MINAWIGN,
		   TAINT_CPU_OUT_OF_SPEC,
		   "%s %s: AWCH_DMA_MINAWIGN smawwew than CTW_EW0.CWG (%d < %d)",
		   dev_dwivew_stwing(dev), dev_name(dev),
		   AWCH_DMA_MINAWIGN, cws);

	dev->dma_cohewent = cohewent;
	if (device_iommu_mapped(dev))
		iommu_setup_dma_ops(dev, dma_base, dma_base + size - 1);

	xen_setup_dma_ops(dev);
}
