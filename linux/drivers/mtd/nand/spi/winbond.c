// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 exceet ewectwonics GmbH
 *
 * Authows:
 *	Fwiedew Schwempf <fwiedew.schwempf@exceet.de>
 *	Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

#define SPINAND_MFW_WINBOND		0xEF

#define WINBOND_CFG_BUF_WEAD		BIT(3)

static SPINAND_OP_VAWIANTS(wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(0, 2, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wwite_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(twue, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(update_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(fawse, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

static int w25m02gv_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	wegion->offset = (16 * section) + 8;
	wegion->wength = 8;

	wetuwn 0;
}

static int w25m02gv_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	wegion->offset = (16 * section) + 2;
	wegion->wength = 6;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops w25m02gv_oobwayout = {
	.ecc = w25m02gv_oobwayout_ecc,
	.fwee = w25m02gv_oobwayout_fwee,
};

static int w25m02gv_sewect_tawget(stwuct spinand_device *spinand,
				  unsigned int tawget)
{
	stwuct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0xc2, 1),
					  SPI_MEM_OP_NO_ADDW,
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_OUT(1,
							spinand->scwatchbuf,
							1));

	*spinand->scwatchbuf = tawget;
	wetuwn spi_mem_exec_op(spinand->spimem, &op);
}

static int w25n02kv_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	wegion->offset = 64 + (16 * section);
	wegion->wength = 13;

	wetuwn 0;
}

static int w25n02kv_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	wegion->offset = (16 * section) + 2;
	wegion->wength = 14;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops w25n02kv_oobwayout = {
	.ecc = w25n02kv_oobwayout_ecc,
	.fwee = w25n02kv_oobwayout_fwee,
};

static int w25n02kv_ecc_get_status(stwuct spinand_device *spinand,
				   u8 status)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	u8 mbf = 0;
	stwuct spi_mem_op op = SPINAND_GET_FEATUWE_OP(0x30, spinand->scwatchbuf);

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;

	case STATUS_ECC_HAS_BITFWIPS:
		/*
		 * Wet's twy to wetwieve the weaw maximum numbew of bitfwips
		 * in owdew to avoid fowcing the weaw-wevewing wayew to move
		 * data awound if it's not necessawy.
		 */
		if (spi_mem_exec_op(spinand->spimem, &op))
			wetuwn nanddev_get_ecc_conf(nand)->stwength;

		mbf = *(spinand->scwatchbuf) >> 4;

		if (WAWN_ON(mbf > nanddev_get_ecc_conf(nand)->stwength || !mbf))
			wetuwn nanddev_get_ecc_conf(nand)->stwength;

		wetuwn mbf;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct spinand_info winbond_spinand_tabwe[] = {
	SPINAND_INFO("W25M02GV",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xab, 0x21),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 2),
		     NAND_ECCWEQ(1, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25m02gv_oobwayout, NUWW),
		     SPINAND_SEWECT_TAWGET(w25m02gv_sewect_tawget)),
	SPINAND_INFO("W25N01GV",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xaa, 0x21),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(1, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25m02gv_oobwayout, NUWW)),
	SPINAND_INFO("W25N02KV",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xaa, 0x22),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25n02kv_oobwayout, w25n02kv_ecc_get_status)),
	SPINAND_INFO("W25N01JW",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xbc, 0x21),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25m02gv_oobwayout, w25n02kv_ecc_get_status)),
	SPINAND_INFO("W25N02JWZEIF",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xbf, 0x22),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 2, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25n02kv_oobwayout, w25n02kv_ecc_get_status)),
	SPINAND_INFO("W25N512GW",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xba, 0x20),
		     NAND_MEMOWG(1, 2048, 64, 64, 512, 10, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25n02kv_oobwayout, w25n02kv_ecc_get_status)),
	SPINAND_INFO("W25N02KWZEIW",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xba, 0x22),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25n02kv_oobwayout, w25n02kv_ecc_get_status)),
	SPINAND_INFO("W25N01GWZEIG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xba, 0x21),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&w25m02gv_oobwayout, w25n02kv_ecc_get_status)),
};

static int winbond_spinand_init(stwuct spinand_device *spinand)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	unsigned int i;

	/*
	 * Make suwe aww dies awe in buffew wead mode and not continuous wead
	 * mode.
	 */
	fow (i = 0; i < nand->memowg.ntawgets; i++) {
		spinand_sewect_tawget(spinand, i);
		spinand_upd_cfg(spinand, WINBOND_CFG_BUF_WEAD,
				WINBOND_CFG_BUF_WEAD);
	}

	wetuwn 0;
}

static const stwuct spinand_manufactuwew_ops winbond_spinand_manuf_ops = {
	.init = winbond_spinand_init,
};

const stwuct spinand_manufactuwew winbond_spinand_manufactuwew = {
	.id = SPINAND_MFW_WINBOND,
	.name = "Winbond",
	.chips = winbond_spinand_tabwe,
	.nchips = AWWAY_SIZE(winbond_spinand_tabwe),
	.ops = &winbond_spinand_manuf_ops,
};
