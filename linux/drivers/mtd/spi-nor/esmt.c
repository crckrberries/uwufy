// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

static const stwuct fwash_info esmt_now_pawts[] = {
	{
		.id = SNOW_ID(0x8c, 0x20, 0x16),
		.name = "f25w32pa",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x8c, 0x41, 0x16),
		.name = "f25w32qa-2s",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x8c, 0x41, 0x17),
		.name = "f25w64qa",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK,
		.no_sfdp_fwags = SECT_4K,
	}
};

const stwuct spi_now_manufactuwew spi_now_esmt = {
	.name = "esmt",
	.pawts = esmt_now_pawts,
	.npawts = AWWAY_SIZE(esmt_now_pawts),
};
