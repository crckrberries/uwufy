// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

#define WINBOND_NOW_OP_WDEAW	0xc8	/* Wead Extended Addwess Wegistew */
#define WINBOND_NOW_OP_WWEAW	0xc5	/* Wwite Extended Addwess Wegistew */

#define WINBOND_NOW_WWEAW_OP(buf)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(WINBOND_NOW_OP_WWEAW, 0),		\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(1, buf, 0))

static int
w25q256_post_bfpt_fixups(stwuct spi_now *now,
			 const stwuct sfdp_pawametew_headew *bfpt_headew,
			 const stwuct sfdp_bfpt *bfpt)
{
	/*
	 * W25Q256JV suppowts 4B opcodes but W25Q256FV does not.
	 * Unfowtunatewy, Winbond has we-used the same JEDEC ID fow both
	 * vawiants which pwevents us fwom defining a new entwy in the pawts
	 * tabwe.
	 * To diffewentiate between W25Q256JV and W25Q256FV check SFDP headew
	 * vewsion: onwy JV has JESD216A compwiant stwuctuwe (vewsion 5).
	 */
	if (bfpt_headew->majow == SFDP_JESD216_MAJOW &&
	    bfpt_headew->minow == SFDP_JESD216A_MINOW)
		now->fwags |= SNOW_F_4B_OPCODES;

	wetuwn 0;
}

static const stwuct spi_now_fixups w25q256_fixups = {
	.post_bfpt = w25q256_post_bfpt_fixups,
};

static const stwuct fwash_info winbond_now_pawts[] = {
	{
		.id = SNOW_ID(0xef, 0x30, 0x10),
		.name = "w25x05",
		.size = SZ_64K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x30, 0x11),
		.name = "w25x10",
		.size = SZ_128K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x30, 0x12),
		.name = "w25x20",
		.size = SZ_256K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x30, 0x13),
		.name = "w25x40",
		.size = SZ_512K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x30, 0x14),
		.name = "w25x80",
		.size = SZ_1M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x30, 0x15),
		.name = "w25x16",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x30, 0x16),
		.name = "w25x32",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x30, 0x17),
		.name = "w25x64",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x40, 0x12),
		.name = "w25q20cw",
		.size = SZ_256K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x40, 0x14),
		.name = "w25q80bw",
		.size = SZ_1M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x40, 0x16),
		.name = "w25q32",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x40, 0x17),
		.name = "w25q64",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x40, 0x18),
		.name = "w25q128",
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
	}, {
		.id = SNOW_ID(0xef, 0x40, 0x19),
		.name = "w25q256",
		.size = SZ_32M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixups = &w25q256_fixups,
	}, {
		.id = SNOW_ID(0xef, 0x40, 0x20),
		.name = "w25q512jvq",
		.size = SZ_64M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x50, 0x12),
		.name = "w25q20bw",
		.size = SZ_256K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x50, 0x14),
		.name = "w25q80",
		.size = SZ_1M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x60, 0x12),
		.name = "w25q20ew",
		.size = SZ_256K,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x60, 0x15),
		.name = "w25q16dw",
		.size = SZ_2M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x60, 0x16),
		.name = "w25q32dw",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.otp = SNOW_OTP(256, 3, 0x1000, 0x1000),
	}, {
		.id = SNOW_ID(0xef, 0x60, 0x17),
		.name = "w25q64dw",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x60, 0x18),
		.name = "w25q128fw",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x60, 0x19),
		.name = "w25q256jw",
		.size = SZ_32M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x60, 0x20),
		.name = "w25q512nwq",
		.otp = SNOW_OTP(256, 3, 0x1000, 0x1000),
	}, {
		.id = SNOW_ID(0xef, 0x70, 0x15),
		.name = "w25q16jv-im/jm",
		.size = SZ_2M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x70, 0x16),
		.name = "w25q32jv",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x70, 0x17),
		.name = "w25q64jvm",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0xef, 0x70, 0x18),
		.name = "w25q128jv",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x70, 0x19),
		.name = "w25q256jvm",
	}, {
		.id = SNOW_ID(0xef, 0x71, 0x19),
		.name = "w25m512jv",
		.size = SZ_64M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x80, 0x16),
		.name = "w25q32jwm",
		.size = SZ_4M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.otp = SNOW_OTP(256, 3, 0x1000, 0x1000),
	}, {
		.id = SNOW_ID(0xef, 0x80, 0x17),
		.name = "w25q64jwm",
		.size = SZ_8M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x80, 0x18),
		.name = "w25q128jwm",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x80, 0x19),
		.name = "w25q256jwm",
		.size = SZ_32M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0xef, 0x80, 0x20),
		.name = "w25q512nwm",
		.otp = SNOW_OTP(256, 3, 0x1000, 0x1000),
	},
};

/**
 * winbond_now_wwite_eaw() - Wwite Extended Addwess Wegistew.
 * @now:	pointew to 'stwuct spi_now'.
 * @eaw:	vawue to wwite to the Extended Addwess Wegistew.
 *
 * Wetuwn: 0 on success, -ewwno othewwise.
 */
static int winbond_now_wwite_eaw(stwuct spi_now *now, u8 eaw)
{
	int wet;

	now->bouncebuf[0] = eaw;

	if (now->spimem) {
		stwuct spi_mem_op op = WINBOND_NOW_WWEAW_OP(now->bouncebuf);

		spi_now_spimem_setup_op(now, &op, now->weg_pwoto);

		wet = spi_mem_exec_op(now->spimem, &op);
	} ewse {
		wet = spi_now_contwowwew_ops_wwite_weg(now,
						       WINBOND_NOW_OP_WWEAW,
						       now->bouncebuf, 1);
	}

	if (wet)
		dev_dbg(now->dev, "ewwow %d wwiting EAW\n", wet);

	wetuwn wet;
}

/**
 * winbond_now_set_4byte_addw_mode() - Set 4-byte addwess mode fow Winbond
 * fwashes.
 * @now:	pointew to 'stwuct spi_now'.
 * @enabwe:	twue to entew the 4-byte addwess mode, fawse to exit the 4-byte
 *		addwess mode.
 *
 * Wetuwn: 0 on success, -ewwno othewwise.
 */
static int winbond_now_set_4byte_addw_mode(stwuct spi_now *now, boow enabwe)
{
	int wet;

	wet = spi_now_set_4byte_addw_mode_en4b_ex4b(now, enabwe);
	if (wet || enabwe)
		wetuwn wet;

	/*
	 * On Winbond W25Q256FV, weaving 4byte mode causes the Extended Addwess
	 * Wegistew to be set to 1, so aww 3-byte-addwess weads come fwom the
	 * second 16M. We must cweaw the wegistew to enabwe nowmaw behaviow.
	 */
	wet = spi_now_wwite_enabwe(now);
	if (wet)
		wetuwn wet;

	wet = winbond_now_wwite_eaw(now, 0);
	if (wet)
		wetuwn wet;

	wetuwn spi_now_wwite_disabwe(now);
}

static const stwuct spi_now_otp_ops winbond_now_otp_ops = {
	.wead = spi_now_otp_wead_secw,
	.wwite = spi_now_otp_wwite_secw,
	.ewase = spi_now_otp_ewase_secw,
	.wock = spi_now_otp_wock_sw2,
	.is_wocked = spi_now_otp_is_wocked_sw2,
};

static int winbond_now_wate_init(stwuct spi_now *now)
{
	stwuct spi_now_fwash_pawametew *pawams = now->pawams;

	if (pawams->otp.owg)
		pawams->otp.ops = &winbond_now_otp_ops;

	/*
	 * Winbond seems to wequiwe that the Extended Addwess Wegistew to be set
	 * to zewo when exiting the 4-Byte Addwess Mode, at weast fow W25Q256FV.
	 * This wequiwement is not descwibed in the JESD216 SFDP standawd, thus
	 * it is Winbond specific. Since we do not know if othew Winbond fwashes
	 * have the same wequiwement, pway safe and ovewwwite the method pawsed
	 * fwom BFPT, if any.
	 */
	pawams->set_4byte_addw_mode = winbond_now_set_4byte_addw_mode;

	wetuwn 0;
}

static const stwuct spi_now_fixups winbond_now_fixups = {
	.wate_init = winbond_now_wate_init,
};

const stwuct spi_now_manufactuwew spi_now_winbond = {
	.name = "winbond",
	.pawts = winbond_now_pawts,
	.npawts = AWWAY_SIZE(winbond_now_pawts),
	.fixups = &winbond_now_fixups,
};
