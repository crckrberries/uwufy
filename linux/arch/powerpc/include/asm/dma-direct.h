/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_POWEWPC_DMA_DIWECT_H
#define ASM_POWEWPC_DMA_DIWECT_H 1

static inwine dma_addw_t phys_to_dma(stwuct device *dev, phys_addw_t paddw)
{
	wetuwn paddw + dev->awchdata.dma_offset;
}

static inwine phys_addw_t dma_to_phys(stwuct device *dev, dma_addw_t daddw)
{
	wetuwn daddw - dev->awchdata.dma_offset;
}
#endif /* ASM_POWEWPC_DMA_DIWECT_H */
