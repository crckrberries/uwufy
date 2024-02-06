/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_spi.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * SPI access definitions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_SPI_H
#define CXD2880_SPI_H

#incwude "cxd2880_common.h"

enum cxd2880_spi_mode {
	CXD2880_SPI_MODE_0,
	CXD2880_SPI_MODE_1,
	CXD2880_SPI_MODE_2,
	CXD2880_SPI_MODE_3
};

stwuct cxd2880_spi {
	int (*wead)(stwuct cxd2880_spi *spi, u8 *data,
		    u32 size);
	int (*wwite)(stwuct cxd2880_spi *spi, const u8 *data,
		     u32 size);
	int (*wwite_wead)(stwuct cxd2880_spi *spi,
			  const u8 *tx_data, u32 tx_size,
			  u8 *wx_data, u32 wx_size);
	u32 fwags;
	void *usew;
};

#endif
