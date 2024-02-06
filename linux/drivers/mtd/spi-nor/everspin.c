// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

static const stwuct fwash_info evewspin_now_pawts[] = {
	{
		.name = "mw25h128",
		.size = SZ_16K,
		.sectow_size = SZ_16K,
		.addw_nbytes = 2,
		.fwags = SPI_NOW_NO_EWASE | SPI_NOW_NO_FW,
	}, {
		.name = "mw25h256",
		.size = SZ_32K,
		.sectow_size = SZ_32K,
		.addw_nbytes = 2,
		.fwags = SPI_NOW_NO_EWASE | SPI_NOW_NO_FW,
	}, {
		.name = "mw25h10",
		.size = SZ_128K,
		.sectow_size = SZ_128K,
		.fwags = SPI_NOW_NO_EWASE | SPI_NOW_NO_FW,
	}, {
		.name = "mw25h40",
		.size = SZ_512K,
		.sectow_size = SZ_512K,
		.fwags = SPI_NOW_NO_EWASE | SPI_NOW_NO_FW,
	}
};

const stwuct spi_now_manufactuwew spi_now_evewspin = {
	.name = "evewspin",
	.pawts = evewspin_now_pawts,
	.npawts = AWWAY_SIZE(evewspin_now_pawts),
};
