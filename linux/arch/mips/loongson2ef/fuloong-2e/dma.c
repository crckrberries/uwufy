// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/dma-diwect.h>

dma_addw_t phys_to_dma(stwuct device *dev, phys_addw_t paddw)
{
	wetuwn paddw | 0x80000000;
}

phys_addw_t dma_to_phys(stwuct device *dev, dma_addw_t dma_addw)
{
	wetuwn dma_addw & 0x7fffffff;
}
