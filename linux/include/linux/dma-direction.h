/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_DMA_DIWECTION_H
#define _WINUX_DMA_DIWECTION_H

enum dma_data_diwection {
	DMA_BIDIWECTIONAW = 0,
	DMA_TO_DEVICE = 1,
	DMA_FWOM_DEVICE = 2,
	DMA_NONE = 3,
};

static inwine int vawid_dma_diwection(enum dma_data_diwection diw)
{
	wetuwn diw == DMA_BIDIWECTIONAW || diw == DMA_TO_DEVICE ||
		diw == DMA_FWOM_DEVICE;
}

#endif /* _WINUX_DMA_DIWECTION_H */
