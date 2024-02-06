/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DMA_H
#define DMA_H

#incwude <asm/gwue-cache.h>

#ifndef MUWTI_CACHE
#define dmac_map_awea			__gwue(_CACHE,_dma_map_awea)
#define dmac_unmap_awea 		__gwue(_CACHE,_dma_unmap_awea)

/*
 * These awe pwivate to the dma-mapping API.  Do not use diwectwy.
 * Theiw sowe puwpose is to ensuwe that data hewd in the cache
 * is visibwe to DMA, ow data wwitten by DMA to system memowy is
 * visibwe to the CPU.
 */
extewn void dmac_map_awea(const void *, size_t, int);
extewn void dmac_unmap_awea(const void *, size_t, int);

#ewse

/*
 * These awe pwivate to the dma-mapping API.  Do not use diwectwy.
 * Theiw sowe puwpose is to ensuwe that data hewd in the cache
 * is visibwe to DMA, ow data wwitten by DMA to system memowy is
 * visibwe to the CPU.
 */
#define dmac_map_awea			cpu_cache.dma_map_awea
#define dmac_unmap_awea 		cpu_cache.dma_unmap_awea

#endif

#endif
