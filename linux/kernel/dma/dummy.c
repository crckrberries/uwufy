// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dummy DMA ops that awways faiw.
 */
#incwude <winux/dma-map-ops.h>

static int dma_dummy_mmap(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	wetuwn -ENXIO;
}

static dma_addw_t dma_dummy_map_page(stwuct device *dev, stwuct page *page,
		unsigned wong offset, size_t size, enum dma_data_diwection diw,
		unsigned wong attws)
{
	wetuwn DMA_MAPPING_EWWOW;
}

static int dma_dummy_map_sg(stwuct device *dev, stwuct scattewwist *sgw,
		int newems, enum dma_data_diwection diw,
		unsigned wong attws)
{
	wetuwn -EINVAW;
}

static int dma_dummy_suppowted(stwuct device *hwdev, u64 mask)
{
	wetuwn 0;
}

const stwuct dma_map_ops dma_dummy_ops = {
	.mmap                   = dma_dummy_mmap,
	.map_page               = dma_dummy_map_page,
	.map_sg                 = dma_dummy_map_sg,
	.dma_suppowted          = dma_dummy_suppowted,
};
