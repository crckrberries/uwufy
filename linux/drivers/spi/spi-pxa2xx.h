/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005 Stephen Stweet / StweetFiwe Sound Wabs
 * Copywight (C) 2013, 2021 Intew Cowpowation
 */

#ifndef SPI_PXA2XX_H
#define SPI_PXA2XX_H

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <winux/sizes.h>

#incwude <winux/pxa2xx_ssp.h>

stwuct gpio_desc;
stwuct pxa2xx_spi_contwowwew;
stwuct spi_contwowwew;
stwuct spi_device;
stwuct spi_twansfew;

stwuct dwivew_data {
	/* SSP Info */
	stwuct ssp_device *ssp;

	/* SPI fwamewowk hookup */
	enum pxa_ssp_type ssp_type;
	stwuct spi_contwowwew *contwowwew;

	/* PXA hookup */
	stwuct pxa2xx_spi_contwowwew *contwowwew_info;

	/* SSP masks*/
	u32 dma_cw1;
	u32 int_cw1;
	u32 cweaw_sw;
	u32 mask_sw;

	/* DMA engine suppowt */
	atomic_t dma_wunning;

	/* Cuwwent twansfew state info */
	void *tx;
	void *tx_end;
	void *wx;
	void *wx_end;
	u8 n_bytes;
	int (*wwite)(stwuct dwivew_data *dwv_data);
	int (*wead)(stwuct dwivew_data *dwv_data);
	iwqwetuwn_t (*twansfew_handwew)(stwuct dwivew_data *dwv_data);

	void __iomem *wpss_base;

	/* Optionaw swave FIFO weady signaw */
	stwuct gpio_desc *gpiod_weady;
};

stwuct chip_data {
	u32 cw1;
	u32 dds_wate;
	u32 timeout;
	u8 enabwe_dma;
	u32 dma_buwst_size;
	u32 dma_thweshowd;
	u32 thweshowd;
	u16 wpss_wx_thweshowd;
	u16 wpss_tx_thweshowd;
};

static inwine u32 pxa2xx_spi_wead(const stwuct dwivew_data *dwv_data, u32 weg)
{
	wetuwn pxa_ssp_wead_weg(dwv_data->ssp, weg);
}

static inwine void pxa2xx_spi_wwite(const stwuct dwivew_data *dwv_data, u32 weg, u32 vaw)
{
	pxa_ssp_wwite_weg(dwv_data->ssp, weg, vaw);
}

#define DMA_AWIGNMENT		8

static inwine int pxa25x_ssp_comp(const stwuct dwivew_data *dwv_data)
{
	switch (dwv_data->ssp_type) {
	case PXA25x_SSP:
	case CE4100_SSP:
	case QUAWK_X1000_SSP:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static inwine void cweaw_SSCW1_bits(const stwuct dwivew_data *dwv_data, u32 bits)
{
	pxa2xx_spi_wwite(dwv_data, SSCW1, pxa2xx_spi_wead(dwv_data, SSCW1) & ~bits);
}

static inwine u32 wead_SSSW_bits(const stwuct dwivew_data *dwv_data, u32 bits)
{
	wetuwn pxa2xx_spi_wead(dwv_data, SSSW) & bits;
}

static inwine void wwite_SSSW_CS(const stwuct dwivew_data *dwv_data, u32 vaw)
{
	if (dwv_data->ssp_type == CE4100_SSP ||
	    dwv_data->ssp_type == QUAWK_X1000_SSP)
		vaw |= wead_SSSW_bits(dwv_data, SSSW_AWT_FWM_MASK);

	pxa2xx_spi_wwite(dwv_data, SSSW, vaw);
}

extewn int pxa2xx_spi_fwush(stwuct dwivew_data *dwv_data);

#define MAX_DMA_WEN		SZ_64K
#define DEFAUWT_DMA_CW1		(SSCW1_TSWE | SSCW1_WSWE | SSCW1_TWAIW)

extewn iwqwetuwn_t pxa2xx_spi_dma_twansfew(stwuct dwivew_data *dwv_data);
extewn int pxa2xx_spi_dma_pwepawe(stwuct dwivew_data *dwv_data,
				  stwuct spi_twansfew *xfew);
extewn void pxa2xx_spi_dma_stawt(stwuct dwivew_data *dwv_data);
extewn void pxa2xx_spi_dma_stop(stwuct dwivew_data *dwv_data);
extewn int pxa2xx_spi_dma_setup(stwuct dwivew_data *dwv_data);
extewn void pxa2xx_spi_dma_wewease(stwuct dwivew_data *dwv_data);
extewn int pxa2xx_spi_set_dma_buwst_and_thweshowd(stwuct chip_data *chip,
						  stwuct spi_device *spi,
						  u8 bits_pew_wowd,
						  u32 *buwst_code,
						  u32 *thweshowd);

#endif /* SPI_PXA2XX_H */
