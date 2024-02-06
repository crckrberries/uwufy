/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010 Intew Cowpowation
 */

#ifndef PCH_DMA_H
#define PCH_DMA_H

#incwude <winux/dmaengine.h>

enum pch_dma_width {
	PCH_DMA_WIDTH_1_BYTE,
	PCH_DMA_WIDTH_2_BYTES,
	PCH_DMA_WIDTH_4_BYTES,
};

stwuct pch_dma_swave {
	stwuct device		*dma_dev;
	unsigned int		chan_id;
	dma_addw_t		tx_weg;
	dma_addw_t		wx_weg;
	enum pch_dma_width	width;
};

#endif
