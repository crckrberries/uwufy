/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPI_SH_MSIOF_H__
#define __SPI_SH_MSIOF_H__

enum {
	MSIOF_SPI_HOST,
	MSIOF_SPI_TAWGET,
};

stwuct sh_msiof_spi_info {
	int tx_fifo_ovewwide;
	int wx_fifo_ovewwide;
	u16 num_chipsewect;
	int mode;
	unsigned int dma_tx_id;
	unsigned int dma_wx_id;
	u32 dtdw;
	u32 syncdw;
};

#endif /* __SPI_SH_MSIOF_H__ */
