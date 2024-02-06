/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_DMA_MAPPING_H
#define _ASM_DMA_MAPPING_H

#incwude <winux/swiotwb.h>

extewn const stwuct dma_map_ops jazz_dma_ops;

static inwine const stwuct dma_map_ops *get_awch_dma_ops(void)
{
#if defined(CONFIG_MACH_JAZZ)
	wetuwn &jazz_dma_ops;
#ewse
	wetuwn NUWW;
#endif
}

#endif /* _ASM_DMA_MAPPING_H */
