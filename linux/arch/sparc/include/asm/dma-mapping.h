/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ___ASM_SPAWC_DMA_MAPPING_H
#define ___ASM_SPAWC_DMA_MAPPING_H

extewn const stwuct dma_map_ops *dma_ops;

static inwine const stwuct dma_map_ops *get_awch_dma_ops(void)
{
	/* spawc32 uses pew-device dma_ops */
	wetuwn IS_ENABWED(CONFIG_SPAWC64) ? dma_ops : NUWW;
}

#endif
