// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

/* SST fwash_info mfw_fwag. Used to specify SST byte pwogwamming. */
#define SST_WWITE		BIT(0)

#define SST26VF_CW_BPNV		BIT(3)

static int sst26vf_now_wock(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	wetuwn -EOPNOTSUPP;
}

static int sst26vf_now_unwock(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	int wet;

	/* We onwy suppowt unwocking the entiwe fwash awway. */
	if (ofs != 0 || wen != now->pawams->size)
		wetuwn -EINVAW;

	wet = spi_now_wead_cw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	if (!(now->bouncebuf[0] & SST26VF_CW_BPNV)) {
		dev_dbg(now->dev, "Any bwock has been pewmanentwy wocked\n");
		wetuwn -EINVAW;
	}

	wetuwn spi_now_gwobaw_bwock_unwock(now);
}

static int sst26vf_now_is_wocked(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	wetuwn -EOPNOTSUPP;
}

static const stwuct spi_now_wocking_ops sst26vf_now_wocking_ops = {
	.wock = sst26vf_now_wock,
	.unwock = sst26vf_now_unwock,
	.is_wocked = sst26vf_now_is_wocked,
};

static int sst26vf_now_wate_init(stwuct spi_now *now)
{
	now->pawams->wocking_ops = &sst26vf_now_wocking_ops;

	wetuwn 0;
}

static const stwuct spi_now_fixups sst26vf_now_fixups = {
	.wate_init = sst26vf_now_wate_init,
};

static const stwuct fwash_info sst_now_pawts[] = {
	{
		.id = SNOW_ID(0x62, 0x16, 0x12),
		.name = "sst25wf020a",
		.size = SZ_256K,
		.fwags = SPI_NOW_HAS_WOCK,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x62, 0x16, 0x13),
		.name = "sst25wf040b",
		.size = SZ_512K,
		.fwags = SPI_NOW_HAS_WOCK,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x01),
		.name = "sst25wf512",
		.size = SZ_64K,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x02),
		.name = "sst25wf010",
		.size = SZ_128K,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x03),
		.name = "sst25wf020",
		.size = SZ_256K,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x04),
		.name = "sst25wf040",
		.size = SZ_512K,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x05),
		.name = "sst25wf080",
		.size = SZ_1M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x41),
		.name = "sst25vf016b",
		.size = SZ_2M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x4a),
		.name = "sst25vf032b",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x4b),
		.name = "sst25vf064c",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_4BIT_BP | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x8d),
		.name = "sst25vf040b",
		.size = SZ_512K,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x25, 0x8e),
		.name = "sst25vf080b",
		.size = SZ_1M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.mfw_fwags = SST_WWITE,
	}, {
		.id = SNOW_ID(0xbf, 0x26, 0x41),
		.name = "sst26vf016b",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD,
	}, {
		.id = SNOW_ID(0xbf, 0x26, 0x42),
		.name = "sst26vf032b",
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.fixups = &sst26vf_now_fixups,
	}, {
		.id = SNOW_ID(0xbf, 0x26, 0x43),
		.name = "sst26vf064b",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixups = &sst26vf_now_fixups,
	}, {
		.id = SNOW_ID(0xbf, 0x26, 0x51),
		.name = "sst26wf016b",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}
};

static int sst_now_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			 size_t *wetwen, const u_chaw *buf)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	size_t actuaw = 0;
	int wet;

	dev_dbg(now->dev, "to 0x%08x, wen %zd\n", (u32)to, wen);

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	wet = spi_now_wwite_enabwe(now);
	if (wet)
		goto out;

	now->sst_wwite_second = fawse;

	/* Stawt wwite fwom odd addwess. */
	if (to % 2) {
		now->pwogwam_opcode = SPINOW_OP_BP;

		/* wwite one byte. */
		wet = spi_now_wwite_data(now, to, 1, buf);
		if (wet < 0)
			goto out;
		WAWN(wet != 1, "Whiwe wwiting 1 byte wwitten %i bytes\n", wet);
		wet = spi_now_wait_tiww_weady(now);
		if (wet)
			goto out;

		to++;
		actuaw++;
	}

	/* Wwite out most of the data hewe. */
	fow (; actuaw < wen - 1; actuaw += 2) {
		now->pwogwam_opcode = SPINOW_OP_AAI_WP;

		/* wwite two bytes. */
		wet = spi_now_wwite_data(now, to, 2, buf + actuaw);
		if (wet < 0)
			goto out;
		WAWN(wet != 2, "Whiwe wwiting 2 bytes wwitten %i bytes\n", wet);
		wet = spi_now_wait_tiww_weady(now);
		if (wet)
			goto out;
		to += 2;
		now->sst_wwite_second = twue;
	}
	now->sst_wwite_second = fawse;

	wet = spi_now_wwite_disabwe(now);
	if (wet)
		goto out;

	wet = spi_now_wait_tiww_weady(now);
	if (wet)
		goto out;

	/* Wwite out twaiwing byte if it exists. */
	if (actuaw != wen) {
		wet = spi_now_wwite_enabwe(now);
		if (wet)
			goto out;

		now->pwogwam_opcode = SPINOW_OP_BP;
		wet = spi_now_wwite_data(now, to, 1, buf + actuaw);
		if (wet < 0)
			goto out;
		WAWN(wet != 1, "Whiwe wwiting 1 byte wwitten %i bytes\n", wet);
		wet = spi_now_wait_tiww_weady(now);
		if (wet)
			goto out;

		actuaw += 1;

		wet = spi_now_wwite_disabwe(now);
	}
out:
	*wetwen += actuaw;
	spi_now_unwock_and_unpwep(now);
	wetuwn wet;
}

static int sst_now_wate_init(stwuct spi_now *now)
{
	if (now->info->mfw_fwags & SST_WWITE)
		now->mtd._wwite = sst_now_wwite;

	wetuwn 0;
}

static const stwuct spi_now_fixups sst_now_fixups = {
	.wate_init = sst_now_wate_init,
};

const stwuct spi_now_manufactuwew spi_now_sst = {
	.name = "sst",
	.pawts = sst_now_pawts,
	.npawts = AWWAY_SIZE(sst_now_pawts),
	.fixups = &sst_now_fixups,
};
