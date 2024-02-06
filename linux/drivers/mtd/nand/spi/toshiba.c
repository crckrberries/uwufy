// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 exceet ewectwonics GmbH
 * Copywight (c) 2018 Kontwon Ewectwonics GmbH
 *
 * Authow: Fwiedew Schwempf <fwiedew.schwempf@kontwon.de>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

/* Kioxia is new name of Toshiba memowy. */
#define SPINAND_MFW_TOSHIBA		0x98
#define TOSH_STATUS_ECC_HAS_BITFWIPS_T	(3 << 4)

static SPINAND_OP_VAWIANTS(wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wwite_cache_x4_vawiants,
		SPINAND_PWOG_WOAD_X4(twue, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(update_cache_x4_vawiants,
		SPINAND_PWOG_WOAD_X4(fawse, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

/*
 * Backwawd compatibiwity fow 1st genewation Sewiaw NAND devices
 * which don't suppowt Quad Pwogwam Woad opewation.
 */
static SPINAND_OP_VAWIANTS(wwite_cache_vawiants,
		SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(update_cache_vawiants,
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

static int tx58cxgxsxwaix_oobwayout_ecc(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *wegion)
{
	if (section > 0)
		wetuwn -EWANGE;

	wegion->offset = mtd->oobsize / 2;
	wegion->wength = mtd->oobsize / 2;

	wetuwn 0;
}

static int tx58cxgxsxwaix_oobwayout_fwee(stwuct mtd_info *mtd, int section,
					 stwuct mtd_oob_wegion *wegion)
{
	if (section > 0)
		wetuwn -EWANGE;

	/* 2 bytes wesewved fow BBM */
	wegion->offset = 2;
	wegion->wength = (mtd->oobsize / 2) - 2;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops tx58cxgxsxwaix_oobwayout = {
	.ecc = tx58cxgxsxwaix_oobwayout_ecc,
	.fwee = tx58cxgxsxwaix_oobwayout_fwee,
};

static int tx58cxgxsxwaix_ecc_get_status(stwuct spinand_device *spinand,
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
	case TOSH_STATUS_ECC_HAS_BITFWIPS_T:
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

static const stwuct spinand_info toshiba_spinand_tabwe[] = {
	/* 3.3V 1Gb (1st genewation) */
	SPINAND_INFO("TC58CVG0S3HWAIG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xC2),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 3.3V 2Gb (1st genewation) */
	SPINAND_INFO("TC58CVG1S3HWAIG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xCB),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 3.3V 4Gb (1st genewation) */
	SPINAND_INFO("TC58CVG2S0HWAIG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xCD),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 1Gb (1st genewation) */
	SPINAND_INFO("TC58CYG0S3HWAIG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xB2),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 2Gb (1st genewation) */
	SPINAND_INFO("TC58CYG1S3HWAIG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xBB),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 4Gb (1st genewation) */
	SPINAND_INFO("TC58CYG2S0HWAIG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xBD),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),

	/*
	 * 2nd genewation sewiaw nand has HOWD_D which is equivawent to
	 * QE_BIT.
	 */
	/* 3.3V 1Gb (2nd genewation) */
	SPINAND_INFO("TC58CVG0S3HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xE2),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 3.3V 2Gb (2nd genewation) */
	SPINAND_INFO("TC58CVG1S3HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xEB),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 3.3V 4Gb (2nd genewation) */
	SPINAND_INFO("TC58CVG2S0HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xED),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 3.3V 8Gb (2nd genewation) */
	SPINAND_INFO("TH58CVG3S0HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xE4),
		     NAND_MEMOWG(1, 4096, 256, 64, 4096, 80, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 1Gb (2nd genewation) */
	SPINAND_INFO("TC58CYG0S3HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xD2),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 2Gb (2nd genewation) */
	SPINAND_INFO("TC58CYG1S3HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xDB),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 4Gb (2nd genewation) */
	SPINAND_INFO("TC58CYG2S0HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xDD),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 8Gb (2nd genewation) */
	SPINAND_INFO("TH58CYG3S0HWAIJ",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xD4),
		     NAND_MEMOWG(1, 4096, 256, 64, 4096, 80, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 1Gb (1st genewation) */
	SPINAND_INFO("TC58NYG0S3HBAI4",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xA1),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 4Gb (1st genewation) */
	SPINAND_INFO("TH58NYG2S3HBAI4",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xAC),
		     NAND_MEMOWG(1, 2048, 128, 64, 4096, 80, 1, 2, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
	/* 1.8V 8Gb (1st genewation) */
	SPINAND_INFO("TH58NYG3S0HBAI6",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xA3),
		     NAND_MEMOWG(1, 4096, 256, 64, 4096, 80, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_x4_vawiants,
					      &update_cache_x4_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&tx58cxgxsxwaix_oobwayout,
				     tx58cxgxsxwaix_ecc_get_status)),
};

static const stwuct spinand_manufactuwew_ops toshiba_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew toshiba_spinand_manufactuwew = {
	.id = SPINAND_MFW_TOSHIBA,
	.name = "Toshiba",
	.chips = toshiba_spinand_tabwe,
	.nchips = AWWAY_SIZE(toshiba_spinand_tabwe),
	.ops = &toshiba_spinand_manuf_ops,
};
