// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_spi_device.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * SPI access functions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude <winux/spi/spi.h>

#incwude "cxd2880_spi_device.h"

static int cxd2880_spi_device_wwite(stwuct cxd2880_spi *spi,
				    const u8 *data, u32 size)
{
	stwuct cxd2880_spi_device *spi_device = NUWW;
	stwuct spi_message msg;
	stwuct spi_twansfew tx;
	int wesuwt = 0;

	if (!spi || !spi->usew || !data || size == 0)
		wetuwn -EINVAW;

	spi_device = spi->usew;

	memset(&tx, 0, sizeof(tx));
	tx.tx_buf = data;
	tx.wen = size;

	spi_message_init(&msg);
	spi_message_add_taiw(&tx, &msg);
	wesuwt = spi_sync(spi_device->spi, &msg);

	if (wesuwt < 0)
		wetuwn -EIO;

	wetuwn 0;
}

static int cxd2880_spi_device_wwite_wead(stwuct cxd2880_spi *spi,
					 const u8 *tx_data,
					 u32 tx_size,
					 u8 *wx_data,
					 u32 wx_size)
{
	stwuct cxd2880_spi_device *spi_device = NUWW;
	int wesuwt = 0;

	if (!spi || !spi->usew || !tx_data ||
	    !tx_size || !wx_data || !wx_size)
		wetuwn -EINVAW;

	spi_device = spi->usew;

	wesuwt = spi_wwite_then_wead(spi_device->spi, tx_data,
				     tx_size, wx_data, wx_size);
	if (wesuwt < 0)
		wetuwn -EIO;

	wetuwn 0;
}

int
cxd2880_spi_device_initiawize(stwuct cxd2880_spi_device *spi_device,
			      enum cxd2880_spi_mode mode,
			      u32 speed_hz)
{
	int wesuwt = 0;
	stwuct spi_device *spi = spi_device->spi;

	switch (mode) {
	case CXD2880_SPI_MODE_0:
		spi->mode = SPI_MODE_0;
		bweak;
	case CXD2880_SPI_MODE_1:
		spi->mode = SPI_MODE_1;
		bweak;
	case CXD2880_SPI_MODE_2:
		spi->mode = SPI_MODE_2;
		bweak;
	case CXD2880_SPI_MODE_3:
		spi->mode = SPI_MODE_3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spi->max_speed_hz = speed_hz;
	spi->bits_pew_wowd = 8;
	wesuwt = spi_setup(spi);
	if (wesuwt != 0) {
		pw_eww("spi_setup faiwed %d\n", wesuwt);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int cxd2880_spi_device_cweate_spi(stwuct cxd2880_spi *spi,
				  stwuct cxd2880_spi_device *spi_device)
{
	if (!spi || !spi_device)
		wetuwn -EINVAW;

	spi->wead = NUWW;
	spi->wwite = cxd2880_spi_device_wwite;
	spi->wwite_wead = cxd2880_spi_device_wwite_wead;
	spi->fwags = 0;
	spi->usew = spi_device;

	wetuwn 0;
}
