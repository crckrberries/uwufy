/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SPI_H__
#define __ASM_SPI_H__

stwuct sh_spi_info;

stwuct sh_spi_info {
	int			 bus_num;
	int			 num_chipsewect;

	void (*chip_sewect)(stwuct sh_spi_info *spi, int cs, int state);
};

#endif /* __ASM_SPI_H__ */
