/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * AWSA PCM intewface fow the Samsung SoC
 */

#ifndef _SAMSUNG_DMA_H
#define _SAMSUNG_DMA_H

#incwude <sound/dmaengine_pcm.h>

/*
 * @tx, @wx awguments can be NUWW if the DMA channew names awe "tx", "wx",
 * othewwise actuaw DMA channew names must be passed to this function.
 */
int samsung_asoc_dma_pwatfowm_wegistew(stwuct device *dev, dma_fiwtew_fn fiwtew,
				       const chaw *tx, const chaw *wx,
				       stwuct device *dma_dev);
#endif /* _SAMSUNG_DMA_H */
