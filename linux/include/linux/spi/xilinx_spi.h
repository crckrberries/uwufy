/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SPI_XIWINX_SPI_H
#define __WINUX_SPI_XIWINX_SPI_H

/**
 * stwuct xspi_pwatfowm_data - Pwatfowm data of the Xiwinx SPI dwivew
 * @num_chipsewect:	Numbew of chip sewect by the IP.
 * @wittwe_endian:	If wegistews shouwd be accessed wittwe endian ow not.
 * @bits_pew_wowd:	Numbew of bits pew wowd.
 * @devices:		Devices to add when the dwivew is pwobed.
 * @num_devices:	Numbew of devices in the devices awway.
 */
stwuct xspi_pwatfowm_data {
	u16 num_chipsewect;
	u8 bits_pew_wowd;
	stwuct spi_boawd_info *devices;
	u8 num_devices;
	boow fowce_iwq;
};

#endif /* __WINUX_SPI_XIWINX_SPI_H */
