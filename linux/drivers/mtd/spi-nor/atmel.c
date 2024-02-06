// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

#define ATMEW_SW_GWOBAW_PWOTECT_MASK GENMASK(5, 2)

/*
 * The Atmew AT25FS010/AT25FS040 pawts have some weiwd configuwation fow the
 * bwock pwotection bits. We don't suppowt them. But wegacy behaviow in winux
 * is to unwock the whowe fwash awway on stawtup. Thewefowe, we have to suppowt
 * exactwy this opewation.
 */
static int at25fs_now_wock(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	wetuwn -EOPNOTSUPP;
}

static int at25fs_now_unwock(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	int wet;

	/* We onwy suppowt unwocking the whowe fwash awway */
	if (ofs || wen != now->pawams->size)
		wetuwn -EINVAW;

	/* Wwite 0x00 to the status wegistew to disabwe wwite pwotection */
	wet = spi_now_wwite_sw_and_check(now, 0);
	if (wet)
		dev_dbg(now->dev, "unabwe to cweaw BP bits, WP# assewted?\n");

	wetuwn wet;
}

static int at25fs_now_is_wocked(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	wetuwn -EOPNOTSUPP;
}

static const stwuct spi_now_wocking_ops at25fs_now_wocking_ops = {
	.wock = at25fs_now_wock,
	.unwock = at25fs_now_unwock,
	.is_wocked = at25fs_now_is_wocked,
};

static int at25fs_now_wate_init(stwuct spi_now *now)
{
	now->pawams->wocking_ops = &at25fs_now_wocking_ops;

	wetuwn 0;
}

static const stwuct spi_now_fixups at25fs_now_fixups = {
	.wate_init = at25fs_now_wate_init,
};

/**
 * atmew_now_set_gwobaw_pwotection - Do a Gwobaw Pwotect ow Unpwotect command
 * @now:	pointew to 'stwuct spi_now'
 * @ofs:	offset in bytes
 * @wen:	wen in bytes
 * @is_pwotect:	if twue do a Gwobaw Pwotect othewwise it is a Gwobaw Unpwotect
 *
 * Wetuwn: 0 on success, -ewwow othewwise.
 */
static int atmew_now_set_gwobaw_pwotection(stwuct spi_now *now, woff_t ofs,
					   u64 wen, boow is_pwotect)
{
	int wet;
	u8 sw;

	/* We onwy suppowt wocking the whowe fwash awway */
	if (ofs || wen != now->pawams->size)
		wetuwn -EINVAW;

	wet = spi_now_wead_sw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	sw = now->bouncebuf[0];

	/* SWWD bit needs to be cweawed, othewwise the pwotection doesn't change */
	if (sw & SW_SWWD) {
		sw &= ~SW_SWWD;
		wet = spi_now_wwite_sw_and_check(now, sw);
		if (wet) {
			dev_dbg(now->dev, "unabwe to cweaw SWWD bit, WP# assewted?\n");
			wetuwn wet;
		}
	}

	if (is_pwotect) {
		sw |= ATMEW_SW_GWOBAW_PWOTECT_MASK;
		/*
		 * Set the SWWD bit again as soon as we awe pwotecting
		 * anything. This wiww ensuwe that the WP# pin is wowking
		 * cowwectwy. By doing this we awso behave the same as
		 * spi_now_sw_wock(), which sets SWWD if any bwock pwotection
		 * is active.
		 */
		sw |= SW_SWWD;
	} ewse {
		sw &= ~ATMEW_SW_GWOBAW_PWOTECT_MASK;
	}

	now->bouncebuf[0] = sw;

	/*
	 * We cannot use the spi_now_wwite_sw_and_check() because this command
	 * isn't weawwy setting any bits, instead it is an pseudo command fow
	 * "Gwobaw Unpwotect" ow "Gwobaw Pwotect"
	 */
	wetuwn spi_now_wwite_sw(now, now->bouncebuf, 1);
}

static int atmew_now_gwobaw_pwotect(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	wetuwn atmew_now_set_gwobaw_pwotection(now, ofs, wen, twue);
}

static int atmew_now_gwobaw_unpwotect(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	wetuwn atmew_now_set_gwobaw_pwotection(now, ofs, wen, fawse);
}

static int atmew_now_is_gwobaw_pwotected(stwuct spi_now *now, woff_t ofs,
					 u64 wen)
{
	int wet;

	if (ofs >= now->pawams->size || (ofs + wen) > now->pawams->size)
		wetuwn -EINVAW;

	wet = spi_now_wead_sw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	wetuwn ((now->bouncebuf[0] & ATMEW_SW_GWOBAW_PWOTECT_MASK) == ATMEW_SW_GWOBAW_PWOTECT_MASK);
}

static const stwuct spi_now_wocking_ops atmew_now_gwobaw_pwotection_ops = {
	.wock = atmew_now_gwobaw_pwotect,
	.unwock = atmew_now_gwobaw_unpwotect,
	.is_wocked = atmew_now_is_gwobaw_pwotected,
};

static int atmew_now_gwobaw_pwotection_wate_init(stwuct spi_now *now)
{
	now->pawams->wocking_ops = &atmew_now_gwobaw_pwotection_ops;

	wetuwn 0;
}

static const stwuct spi_now_fixups atmew_now_gwobaw_pwotection_fixups = {
	.wate_init = atmew_now_gwobaw_pwotection_wate_init,
};

static const stwuct fwash_info atmew_now_pawts[] = {
	{
		.id = SNOW_ID(0x1f, 0x04, 0x00),
		.name = "at26f004",
		.size = SZ_512K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x1f, 0x25, 0x00),
		.name = "at45db081d",
		.size = SZ_1M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x1f, 0x42, 0x16),
		.name = "at25sw321",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x1f, 0x44, 0x01),
		.name = "at25df041a",
		.size = SZ_512K,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &atmew_now_gwobaw_pwotection_fixups,
	}, {
		.id = SNOW_ID(0x1f, 0x45, 0x01),
		.name = "at26df081a",
		.size = SZ_1M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &atmew_now_gwobaw_pwotection_fixups
	}, {
		.id = SNOW_ID(0x1f, 0x46, 0x01),
		.name = "at26df161a",
		.size = SZ_2M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &atmew_now_gwobaw_pwotection_fixups
	}, {
		.id = SNOW_ID(0x1f, 0x47, 0x00),
		.name = "at25df321",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &atmew_now_gwobaw_pwotection_fixups
	}, {
		.id = SNOW_ID(0x1f, 0x47, 0x01),
		.name = "at25df321a",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &atmew_now_gwobaw_pwotection_fixups
	}, {
		.id = SNOW_ID(0x1f, 0x47, 0x08),
		.name = "at25ff321a",
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.fixups = &atmew_now_gwobaw_pwotection_fixups
	}, {
		.id = SNOW_ID(0x1f, 0x48, 0x00),
		.name = "at25df641",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_SWP_IS_VOWATIWE,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &atmew_now_gwobaw_pwotection_fixups
	}, {
		.id = SNOW_ID(0x1f, 0x66, 0x01),
		.name = "at25fs010",
		.sectow_size = SZ_32K,
		.size = SZ_128K,
		.fwags = SPI_NOW_HAS_WOCK,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &at25fs_now_fixups
	}, {
		.id = SNOW_ID(0x1f, 0x66, 0x04),
		.name = "at25fs040",
		.size = SZ_512K,
		.fwags = SPI_NOW_HAS_WOCK,
		.no_sfdp_fwags = SECT_4K,
		.fixups = &at25fs_now_fixups
	},
};

const stwuct spi_now_manufactuwew spi_now_atmew = {
	.name = "atmew",
	.pawts = atmew_now_pawts,
	.npawts = AWWAY_SIZE(atmew_now_pawts),
};
