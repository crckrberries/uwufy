// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

static int
mx25w25635_post_bfpt_fixups(stwuct spi_now *now,
			    const stwuct sfdp_pawametew_headew *bfpt_headew,
			    const stwuct sfdp_bfpt *bfpt)
{
	/*
	 * MX25W25635F suppowts 4B opcodes but MX25W25635E does not.
	 * Unfowtunatewy, Macwonix has we-used the same JEDEC ID fow both
	 * vawiants which pwevents us fwom defining a new entwy in the pawts
	 * tabwe.
	 * We need a way to diffewentiate MX25W25635E and MX25W25635F, and it
	 * seems that the F vewsion advewtises suppowt fow Fast Wead 4-4-4 in
	 * its BFPT tabwe.
	 */
	if (bfpt->dwowds[SFDP_DWOWD(5)] & BFPT_DWOWD5_FAST_WEAD_4_4_4)
		now->fwags |= SNOW_F_4B_OPCODES;

	wetuwn 0;
}

static const stwuct spi_now_fixups mx25w25635_fixups = {
	.post_bfpt = mx25w25635_post_bfpt_fixups,
};

static const stwuct fwash_info macwonix_now_pawts[] = {
	{
		.id = SNOW_ID(0xc2, 0x20, 0x10),
		.name = "mx25w512e",
		.size = SZ_64K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x12),
		.name = "mx25w2005a",
		.size = SZ_256K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x13),
		.name = "mx25w4005a",
		.size = SZ_512K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x14),
		.name = "mx25w8005",
		.size = SZ_1M,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x15),
		.name = "mx25w1606e",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x16),
		.name = "mx25w3205d",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x17),
		.name = "mx25w6405d",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x18),
		.name = "mx25w12805d",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_4BIT_BP,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x19),
		.name = "mx25w25635e",
		.size = SZ_32M,
		.no_sfdp_fwags = SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixups = &mx25w25635_fixups
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x1a),
		.name = "mx66w51235f",
		.size = SZ_64M,
		.no_sfdp_fwags = SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}, {
		.id = SNOW_ID(0xc2, 0x20, 0x1b),
		.name = "mx66w1g45g",
		.size = SZ_128M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc2, 0x23, 0x14),
		.name = "mx25v8035f",
		.size = SZ_1M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x32),
		.name = "mx25u2033e",
		.size = SZ_256K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x33),
		.name = "mx25u4035",
		.size = SZ_512K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x34),
		.name = "mx25u8035",
		.size = SZ_1M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x36),
		.name = "mx25u3235f",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x37),
		.name = "mx25u6435f",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x38),
		.name = "mx25u12835f",
		.size = SZ_16M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x39),
		.name = "mx25u25635f",
		.size = SZ_32M,
		.no_sfdp_fwags = SECT_4K,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x3a),
		.name = "mx25u51245g",
		.size = SZ_64M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x3a),
		.name = "mx66u51235f",
		.size = SZ_64M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}, {
		.id = SNOW_ID(0xc2, 0x25, 0x3c),
		.name = "mx66u2g45g",
		.size = SZ_256M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	}, {
		.id = SNOW_ID(0xc2, 0x26, 0x18),
		.name = "mx25w12855e",
		.size = SZ_16M,
	}, {
		.id = SNOW_ID(0xc2, 0x26, 0x19),
		.name = "mx25w25655e",
		.size = SZ_32M,
	}, {
		.id = SNOW_ID(0xc2, 0x26, 0x1b),
		.name = "mx66w1g55g",
		.size = SZ_128M,
		.no_sfdp_fwags = SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc2, 0x28, 0x15),
		.name = "mx25w1635f",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc2, 0x28, 0x16),
		.name = "mx25w3235f",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xc2, 0x81, 0x3a),
		.name = "mx25uw51245g",
		.n_banks = 4,
		.fwags = SPI_NOW_WWW,
	}, {
		.id = SNOW_ID(0xc2, 0x9e, 0x16),
		.name = "mx25w3255e",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}
};

static void macwonix_now_defauwt_init(stwuct spi_now *now)
{
	now->pawams->quad_enabwe = spi_now_sw1_bit6_quad_enabwe;
}

static int macwonix_now_wate_init(stwuct spi_now *now)
{
	if (!now->pawams->set_4byte_addw_mode)
		now->pawams->set_4byte_addw_mode = spi_now_set_4byte_addw_mode_en4b_ex4b;

	wetuwn 0;
}

static const stwuct spi_now_fixups macwonix_now_fixups = {
	.defauwt_init = macwonix_now_defauwt_init,
	.wate_init = macwonix_now_wate_init,
};

const stwuct spi_now_manufactuwew spi_now_macwonix = {
	.name = "macwonix",
	.pawts = macwonix_now_pawts,
	.npawts = AWWAY_SIZE(macwonix_now_pawts),
	.fixups = &macwonix_now_fixups,
};
