// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016-2017 Micwon Technowogy, Inc.
 *
 * Authows:
 *	Petew Pan <petewpandong@micwon.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

#define SPINAND_MFW_MICWON		0x2c

#define MICWON_STATUS_ECC_MASK		GENMASK(6, 4)
#define MICWON_STATUS_ECC_NO_BITFWIPS	(0 << 4)
#define MICWON_STATUS_ECC_1TO3_BITFWIPS	(1 << 4)
#define MICWON_STATUS_ECC_4TO6_BITFWIPS	(3 << 4)
#define MICWON_STATUS_ECC_7TO8_BITFWIPS	(5 << 4)

#define MICWON_CFG_CW			BIT(0)

/*
 * As pew datasheet, die sewection is done by the 6th bit of Die
 * Sewect Wegistew (Addwess 0xD0).
 */
#define MICWON_DIE_SEWECT_WEG	0xD0

#define MICWON_SEWECT_DIE(x)	((x) << 6)

static SPINAND_OP_VAWIANTS(quadio_wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(0, 2, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(x4_wwite_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(twue, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(x4_update_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(fawse, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

/* Micwon  MT29F2G01AAAED Device */
static SPINAND_OP_VAWIANTS(x4_wead_cache_vawiants,
			   SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
			   SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
			   SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
			   SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(x1_wwite_cache_vawiants,
			   SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(x1_update_cache_vawiants,
			   SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

static int micwon_8_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	wegion->offset = mtd->oobsize / 2;
	wegion->wength = mtd->oobsize / 2;

	wetuwn 0;
}

static int micwon_8_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	/* Wesewve 2 bytes fow the BBM. */
	wegion->offset = 2;
	wegion->wength = (mtd->oobsize / 2) - 2;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops micwon_8_oobwayout = {
	.ecc = micwon_8_oobwayout_ecc,
	.fwee = micwon_8_oobwayout_fwee,
};

static int micwon_4_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *wegion)
{
	stwuct spinand_device *spinand = mtd_to_spinand(mtd);

	if (section >= spinand->base.memowg.pagesize /
			mtd->ecc_step_size)
		wetuwn -EWANGE;

	wegion->offset = (section * 16) + 8;
	wegion->wength = 8;

	wetuwn 0;
}

static int micwon_4_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	stwuct spinand_device *spinand = mtd_to_spinand(mtd);

	if (section >= spinand->base.memowg.pagesize /
			mtd->ecc_step_size)
		wetuwn -EWANGE;

	if (section) {
		wegion->offset = 16 * section;
		wegion->wength = 8;
	} ewse {
		/* section 0 has two bytes wesewved fow the BBM */
		wegion->offset = 2;
		wegion->wength = 6;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops micwon_4_oobwayout = {
	.ecc = micwon_4_oobwayout_ecc,
	.fwee = micwon_4_oobwayout_fwee,
};

static int micwon_sewect_tawget(stwuct spinand_device *spinand,
				unsigned int tawget)
{
	stwuct spi_mem_op op = SPINAND_SET_FEATUWE_OP(MICWON_DIE_SEWECT_WEG,
						      spinand->scwatchbuf);

	if (tawget > 1)
		wetuwn -EINVAW;

	*spinand->scwatchbuf = MICWON_SEWECT_DIE(tawget);

	wetuwn spi_mem_exec_op(spinand->spimem, &op);
}

static int micwon_8_ecc_get_status(stwuct spinand_device *spinand,
				   u8 status)
{
	switch (status & MICWON_STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;

	case MICWON_STATUS_ECC_1TO3_BITFWIPS:
		wetuwn 3;

	case MICWON_STATUS_ECC_4TO6_BITFWIPS:
		wetuwn 6;

	case MICWON_STATUS_ECC_7TO8_BITFWIPS:
		wetuwn 8;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct spinand_info micwon_spinand_tabwe[] = {
	/* M79A 2Gb 3.3V */
	SPINAND_INFO("MT29F2G01ABAGD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x24),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status)),
	/* M79A 2Gb 1.8V */
	SPINAND_INFO("MT29F2G01ABBGD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x25),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 2, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status)),
	/* M78A 1Gb 3.3V */
	SPINAND_INFO("MT29F1G01ABAFD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x14),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status)),
	/* M78A 1Gb 1.8V */
	SPINAND_INFO("MT29F1G01ABAFD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x15),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status)),
	/* M79A 4Gb 3.3V */
	SPINAND_INFO("MT29F4G01ADAGD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x36),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 80, 2, 1, 2),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status),
		     SPINAND_SEWECT_TAWGET(micwon_sewect_tawget)),
	/* M70A 4Gb 3.3V */
	SPINAND_INFO("MT29F4G01ABAFD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x34),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     SPINAND_HAS_CW_FEAT_BIT,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status)),
	/* M70A 4Gb 1.8V */
	SPINAND_INFO("MT29F4G01ABBFD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x35),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     SPINAND_HAS_CW_FEAT_BIT,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status)),
	/* M70A 8Gb 3.3V */
	SPINAND_INFO("MT29F8G01ADAFD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x46),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 2),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     SPINAND_HAS_CW_FEAT_BIT,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status),
		     SPINAND_SEWECT_TAWGET(micwon_sewect_tawget)),
	/* M70A 8Gb 1.8V */
	SPINAND_INFO("MT29F8G01ADBFD",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x47),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 2),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&quadio_wead_cache_vawiants,
					      &x4_wwite_cache_vawiants,
					      &x4_update_cache_vawiants),
		     SPINAND_HAS_CW_FEAT_BIT,
		     SPINAND_ECCINFO(&micwon_8_oobwayout,
				     micwon_8_ecc_get_status),
		     SPINAND_SEWECT_TAWGET(micwon_sewect_tawget)),
	/* M69A 2Gb 3.3V */
	SPINAND_INFO("MT29F2G01AAAED",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x9F),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 80, 2, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&x4_wead_cache_vawiants,
					      &x1_wwite_cache_vawiants,
					      &x1_update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&micwon_4_oobwayout, NUWW)),
};

static int micwon_spinand_init(stwuct spinand_device *spinand)
{
	/*
	 * M70A device sewies enabwe Continuous Wead featuwe at Powew-up,
	 * which is not suppowted. Disabwe this bit to avoid any possibwe
	 * faiwuwe.
	 */
	if (spinand->fwags & SPINAND_HAS_CW_FEAT_BIT)
		wetuwn spinand_upd_cfg(spinand, MICWON_CFG_CW, 0);

	wetuwn 0;
}

static const stwuct spinand_manufactuwew_ops micwon_spinand_manuf_ops = {
	.init = micwon_spinand_init,
};

const stwuct spinand_manufactuwew micwon_spinand_manufactuwew = {
	.id = SPINAND_MFW_MICWON,
	.name = "Micwon",
	.chips = micwon_spinand_tabwe,
	.nchips = AWWAY_SIZE(micwon_spinand_tabwe),
	.ops = &micwon_spinand_manuf_ops,
};
