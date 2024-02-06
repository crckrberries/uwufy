/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MXS_DMA_H_
#define _MXS_DMA_H_

#incwude <winux/dmaengine.h>

#define MXS_DMA_CTWW_WAIT4END	BIT(31)
#define MXS_DMA_CTWW_WAIT4WDY	BIT(30)

/*
 * The mxs dmaengine can do PIO twansfews. We pass a pointew to the PIO wowds
 * in the second awgument to dmaengine_pwep_swave_sg when the diwection is
 * set to DMA_TWANS_NONE. To make this cweaw and to pwevent usews fwom doing
 * the ewwow pwone casting we have this wwappew function
 */
static inwine stwuct dma_async_tx_descwiptow *mxs_dmaengine_pwep_pio(
        stwuct dma_chan *chan, u32 *pio, unsigned int npio,
        enum dma_twansfew_diwection diw, unsigned wong fwags)
{
	wetuwn dmaengine_pwep_swave_sg(chan, (stwuct scattewwist *)pio, npio,
				       diw, fwags);
}

#endif /* _MXS_DMA_H_ */
