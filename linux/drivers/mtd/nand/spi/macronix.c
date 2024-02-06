// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Macwonix
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

#define SPINAND_MFW_MACWONIX		0xC2
#define MACWONIX_ECCSW_MASK		0x0F

static SPINAND_OP_VAWIANTS(wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wwite_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(twue, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(update_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(fawse, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

static int mx35wfxge4ab_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				      stwuct mtd_oob_wegion *wegion)
{
	wetuwn -EWANGE;
}

static int mx35wfxge4ab_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				       stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	wegion->offset = 2;
	wegion->wength = mtd->oobsize - 2;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops mx35wfxge4ab_oobwayout = {
	.ecc = mx35wfxge4ab_oobwayout_ecc,
	.fwee = mx35wfxge4ab_oobwayout_fwee,
};

static int mx35wf1ge4ab_get_eccsw(stwuct spinand_device *spinand, u8 *eccsw)
{
	stwuct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0x7c, 1),
					  SPI_MEM_OP_NO_ADDW,
					  SPI_MEM_OP_DUMMY(1, 1),
					  SPI_MEM_OP_DATA_IN(1, eccsw, 1));

	int wet = spi_mem_exec_op(spinand->spimem, &op);
	if (wet)
		wetuwn wet;

	*eccsw &= MACWONIX_ECCSW_MASK;
	wetuwn 0;
}

static int mx35wf1ge4ab_ecc_get_status(stwuct spinand_device *spinand,
				       u8 status)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);
	u8 eccsw;

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
		if (mx35wf1ge4ab_get_eccsw(spinand, spinand->scwatchbuf))
			wetuwn nanddev_get_ecc_conf(nand)->stwength;

		eccsw = *spinand->scwatchbuf;
		if (WAWN_ON(eccsw > nanddev_get_ecc_conf(nand)->stwength ||
			    !eccsw))
			wetuwn nanddev_get_ecc_conf(nand)->stwength;

		wetuwn eccsw;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct spinand_info macwonix_spinand_tabwe[] = {
	SPINAND_INFO("MX35WF1GE4AB",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x12),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35WF2GE4AB",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x22),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout, NUWW)),
	SPINAND_INFO("MX35WF2GE4AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x26),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35WF4GE4AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x37),
		     NAND_MEMOWG(1, 4096, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35WF1G24AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x14),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout, NUWW)),
	SPINAND_INFO("MX35WF2G24AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x24),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout, NUWW)),
	SPINAND_INFO("MX35WF4G24AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x35),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout, NUWW)),
	SPINAND_INFO("MX31WF1GE4BC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x1e),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX31UF1GE4BC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x9e),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),

	SPINAND_INFO("MX35WF2G14AC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x20),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF4G24AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xb5),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF4GE4AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xb7),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF2G14AC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xa0),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF2G24AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xa4),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF2GE4AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xa6),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF2GE4AC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xa2),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF1G14AC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x90),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF1G24AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x94),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF1GE4AD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x96),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX35UF1GE4AC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x92),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),

	SPINAND_INFO("MX31WF2GE4BC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x2e),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
	SPINAND_INFO("MX3UF2GE4BC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xae),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35wfxge4ab_oobwayout,
				     mx35wf1ge4ab_ecc_get_status)),
};

static const stwuct spinand_manufactuwew_ops macwonix_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew macwonix_spinand_manufactuwew = {
	.id = SPINAND_MFW_MACWONIX,
	.name = "Macwonix",
	.chips = macwonix_spinand_tabwe,
	.nchips = AWWAY_SIZE(macwonix_spinand_tabwe),
	.ops = &macwonix_spinand_manuf_ops,
};
