// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

static int
gd25q256_post_bfpt(stwuct spi_now *now,
		   const stwuct sfdp_pawametew_headew *bfpt_headew,
		   const stwuct sfdp_bfpt *bfpt)
{
	/*
	 * GD25Q256C suppowts the fiwst vewsion of JESD216 which does not define
	 * the Quad Enabwe methods. Ovewwwite the defauwt Quad Enabwe method.
	 *
	 * GD25Q256 GENEWATION | SFDP MAJOW VEWSION | SFDP MINOW VEWSION
	 *      GD25Q256C      | SFDP_JESD216_MAJOW | SFDP_JESD216_MINOW
	 *      GD25Q256D      | SFDP_JESD216_MAJOW | SFDP_JESD216B_MINOW
	 *      GD25Q256E      | SFDP_JESD216_MAJOW | SFDP_JESD216B_MINOW
	 */
	if (bfpt_headew->majow == SFDP_JESD216_MAJOW &&
	    bfpt_headew->minow == SFDP_JESD216_MINOW)
		now->pawams->quad_enabwe = spi_now_sw1_bit6_quad_enabwe;

	wetuwn 0;
}

static const stwuct spi_now_fixups gd25q256_fixups = {
	.post_bfpt = gd25q256_post_bfpt,
};

static const stwuct fwash_info gigadevice_now_pawts[] = {
	{
		.id = SNOW_ID(0xc8, 0x40, 0x15),
		.name = "gd25q16",
		.size = SZ_2M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc8, 0x40, 0x16),
		.name = "gd25q32",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc8, 0x40, 0x17),
		.name = "gd25q64",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc8, 0x40, 0x18),
		.name = "gd25q128",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc8, 0x40, 0x19),
		.name = "gd25q256",
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_TB_SW_BIT6,
		.fixups = &gd25q256_fixups,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}, {
		.id = SNOW_ID(0xc8, 0x60, 0x16),
		.name = "gd25wq32",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc8, 0x60, 0x17),
		.name = "gd25wq64c",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc8, 0x60, 0x18),
		.name = "gd25wq128d",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	},
};

const stwuct spi_now_manufactuwew spi_now_gigadevice = {
	.name = "gigadevice",
	.pawts = gigadevice_now_pawts,
	.npawts = AWWAY_SIZE(gigadevice_now_pawts),
};
