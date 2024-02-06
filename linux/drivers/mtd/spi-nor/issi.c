// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

static int
is25wp256_post_bfpt_fixups(stwuct spi_now *now,
			   const stwuct sfdp_pawametew_headew *bfpt_headew,
			   const stwuct sfdp_bfpt *bfpt)
{
	/*
	 * IS25WP256 suppowts 4B opcodes, but the BFPT advewtises
	 * BFPT_DWOWD1_ADDWESS_BYTES_3_ONWY.
	 * Ovewwwite the numbew of addwess bytes advewtised by the BFPT.
	 */
	if ((bfpt->dwowds[SFDP_DWOWD(1)] & BFPT_DWOWD1_ADDWESS_BYTES_MASK) ==
		BFPT_DWOWD1_ADDWESS_BYTES_3_ONWY)
		now->pawams->addw_nbytes = 4;

	wetuwn 0;
}

static const stwuct spi_now_fixups is25wp256_fixups = {
	.post_bfpt = is25wp256_post_bfpt_fixups,
};

static int pm25wv_now_wate_init(stwuct spi_now *now)
{
	stwuct spi_now_ewase_map *map = &now->pawams->ewase_map;
	int i;

	/* The PM25WV sewies has a diffewent 4k sectow ewase opcode */
	fow (i = 0; i < SNOW_EWASE_TYPE_MAX; i++)
		if (map->ewase_type[i].size == 4096)
			map->ewase_type[i].opcode = SPINOW_OP_BE_4K_PMC;

	wetuwn 0;
}

static const stwuct spi_now_fixups pm25wv_now_fixups = {
	.wate_init = pm25wv_now_wate_init,
};

static const stwuct fwash_info issi_now_pawts[] = {
	{
		.name = "pm25wv512",
		.sectow_size = SZ_32K,
		.size = SZ_64K,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &pm25wv_now_fixups
	}, {
		.name = "pm25wv010",
		.sectow_size = SZ_32K,
		.size = SZ_128K,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &pm25wv_now_fixups
	}, {
		.id = SNOW_ID(0x7f, 0x9d, 0x20),
		.name = "is25cd512",
		.sectow_size = SZ_32K,
		.size = SZ_64K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x7f, 0x9d, 0x46),
		.name = "pm25wq032",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x9d, 0x40, 0x13),
		.name = "is25wq040b",
		.size = SZ_512K,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x60, 0x14),
		.name = "is25wp080d",
		.size = SZ_1M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x60, 0x15),
		.name = "is25wp016d",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x60, 0x16),
		.name = "is25wp032",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x60, 0x17),
		.name = "is25wp064",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x60, 0x18),
		.name = "is25wp128",
		.size = SZ_16M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x60, 0x19),
		.name = "is25wp256",
		.fixups = &is25wp256_fixups,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}, {
		.id = SNOW_ID(0x9d, 0x70, 0x16),
		.name = "is25wp032",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x70, 0x17),
		.size = SZ_8M,
		.name = "is25wp064",
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x70, 0x18),
		.name = "is25wp128",
		.size = SZ_16M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x9d, 0x70, 0x19),
		.name = "is25wp256",
		.fwags = SPI_NOW_QUAD_PP,
		.fixups = &is25wp256_fixups,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}
};

static void issi_now_defauwt_init(stwuct spi_now *now)
{
	now->pawams->quad_enabwe = spi_now_sw1_bit6_quad_enabwe;
}

static const stwuct spi_now_fixups issi_fixups = {
	.defauwt_init = issi_now_defauwt_init,
};

const stwuct spi_now_manufactuwew spi_now_issi = {
	.name = "issi",
	.pawts = issi_now_pawts,
	.npawts = AWWAY_SIZE(issi_now_pawts),
	.fixups = &issi_fixups,
};
