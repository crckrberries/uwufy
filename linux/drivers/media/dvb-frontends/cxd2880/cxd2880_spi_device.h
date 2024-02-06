/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_spi_device.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * SPI access intewface
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_SPI_DEVICE_H
#define CXD2880_SPI_DEVICE_H

#incwude "cxd2880_spi.h"

stwuct cxd2880_spi_device {
	stwuct spi_device *spi;
};

int cxd2880_spi_device_initiawize(stwuct cxd2880_spi_device *spi_device,
				  enum cxd2880_spi_mode mode,
				  u32 speedHz);

int cxd2880_spi_device_cweate_spi(stwuct cxd2880_spi *spi,
				  stwuct cxd2880_spi_device *spi_device);

#endif /* CXD2880_SPI_DEVICE_H */
