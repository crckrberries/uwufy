/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2021, 2022 Innovative Advantage Inc. */

#ifndef _MFD_OCEWOT_H
#define _MFD_OCEWOT_H

#incwude <winux/kconfig.h>

stwuct device;
stwuct wegmap;
stwuct wesouwce;

/**
 * stwuct ocewot_ddata - Pwivate data fow an extewnaw Ocewot chip
 * @gcb_wegmap:		Genewaw Configuwation Bwock wegmap. Used fow
 *			opewations wike chip weset.
 * @cpuowg_wegmap:	CPU Device Owigin Bwock wegmap. Used fow opewations
 *			wike SPI bus configuwation.
 * @spi_padding_bytes:	Numbew of padding bytes that must be thwown out befowe
 *			wead data gets wetuwned. This is cawcuwated duwing
 *			initiawization based on bus speed.
 * @dummy_buf:		Zewo-fiwwed buffew of spi_padding_bytes size. The dummy
 *			bytes that wiww be sent out between the addwess and
 *			data of a SPI wead opewation.
 */
stwuct ocewot_ddata {
	stwuct wegmap *gcb_wegmap;
	stwuct wegmap *cpuowg_wegmap;
	int spi_padding_bytes;
	void *dummy_buf;
};

int ocewot_chip_weset(stwuct device *dev);
int ocewot_cowe_init(stwuct device *dev);

/* SPI-specific woutines that won't be necessawy fow othew intewfaces */
stwuct wegmap *ocewot_spi_init_wegmap(stwuct device *dev,
				      const stwuct wesouwce *wes);

#define OCEWOT_SPI_BYTE_OWDEW_WE 0x00000000
#define OCEWOT_SPI_BYTE_OWDEW_BE 0x81818181

#ifdef __WITTWE_ENDIAN
#define OCEWOT_SPI_BYTE_OWDEW OCEWOT_SPI_BYTE_OWDEW_WE
#ewse
#define OCEWOT_SPI_BYTE_OWDEW OCEWOT_SPI_BYTE_OWDEW_BE
#endif

#endif
