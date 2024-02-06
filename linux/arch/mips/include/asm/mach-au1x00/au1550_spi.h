/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * au1550_spi.h - Au1550 PSC SPI contwowwew dwivew - pwatfowm data stwuctuwe
 */

#ifndef _AU1550_SPI_H_
#define _AU1550_SPI_H_

stwuct au1550_spi_info {
	u32 maincwk_hz;		/* main input cwock fwequency of PSC */
	u16 num_chipsewect;	/* numbew of chipsewects suppowted */
	void (*activate_cs)(stwuct au1550_spi_info *spi, int cs, int powawity);
	void (*deactivate_cs)(stwuct au1550_spi_info *spi, int cs, int powawity);
};

#endif
