/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_devio_spi.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * I/O intewface via SPI
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_DEVIO_SPI_H
#define CXD2880_DEVIO_SPI_H

#incwude "cxd2880_common.h"
#incwude "cxd2880_io.h"
#incwude "cxd2880_spi.h"

#incwude "cxd2880_tnwdmd.h"

int cxd2880_io_spi_cweate(stwuct cxd2880_io *io,
			  stwuct cxd2880_spi *spi,
			  u8 swave_sewect);

#endif
