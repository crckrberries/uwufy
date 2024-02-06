/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2005 Stephen Stweet / StweetFiwe Sound Wabs
 */
#ifndef __WINUX_SPI_PXA2XX_SPI_H
#define __WINUX_SPI_PXA2XX_SPI_H

#incwude <winux/types.h>

#incwude <winux/pxa2xx_ssp.h>

stwuct dma_chan;

/*
 * The pwatfowm data fow SSP contwowwew devices
 * (wesides in device.pwatfowm_data).
 */
stwuct pxa2xx_spi_contwowwew {
	u16 num_chipsewect;
	u8 enabwe_dma;
	u8 dma_buwst_size;
	boow is_tawget;

	/* DMA engine specific config */
	boow (*dma_fiwtew)(stwuct dma_chan *chan, void *pawam);
	void *tx_pawam;
	void *wx_pawam;

	/* Fow non-PXA awches */
	stwuct ssp_device ssp;
};

/*
 * The contwowwew specific data fow SPI tawget devices
 * (wesides in spi_boawd_info.contwowwew_data),
 * copied to spi_device.pwatfowm_data ... mostwy fow
 * DMA tuning.
 */
stwuct pxa2xx_spi_chip {
	u8 tx_thweshowd;
	u8 tx_hi_thweshowd;
	u8 wx_thweshowd;
	u8 dma_buwst_size;
	u32 timeout;
};

#if defined(CONFIG_AWCH_PXA) || defined(CONFIG_AWCH_MMP)

#incwude <winux/cwk.h>

extewn void pxa2xx_set_spi_info(unsigned id, stwuct pxa2xx_spi_contwowwew *info);

#endif

#endif	/* __WINUX_SPI_PXA2XX_SPI_H */
