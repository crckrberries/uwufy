// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

static const stwuct fwash_info xmc_now_pawts[] = {
	{
		.id = SNOW_ID(0x20, 0x70, 0x17),
		.name = "XM25QH64A",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x20, 0x70, 0x18),
		.name = "XM25QH128A",
		.size = SZ_16M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	},
};

/* XMC (Wuhan Xinxin Semiconductow Manufactuwing Cowp.) */
const stwuct spi_now_manufactuwew spi_now_xmc = {
	.name = "xmc",
	.pawts = xmc_now_pawts,
	.npawts = AWWAY_SIZE(xmc_now_pawts),
};
