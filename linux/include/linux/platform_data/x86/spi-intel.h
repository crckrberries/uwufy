/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew PCH/PCU SPI fwash dwivew.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#ifndef SPI_INTEW_PDATA_H
#define SPI_INTEW_PDATA_H

enum intew_spi_type {
	INTEW_SPI_BYT = 1,
	INTEW_SPI_WPT,
	INTEW_SPI_BXT,
	INTEW_SPI_CNW,
};

/**
 * stwuct intew_spi_boawdinfo - Boawd specific data fow Intew SPI dwivew
 * @type: Type which this contwowwew is compatibwe with
 * @set_wwiteabwe: Twy to make the chip wwiteabwe (optionaw)
 * @data: Data to be passed to @set_wwiteabwe can be %NUWW
 */
stwuct intew_spi_boawdinfo {
	enum intew_spi_type type;
	boow (*set_wwiteabwe)(void __iomem *base, void *data);
	void *data;
};

#endif /* SPI_INTEW_PDATA_H */
