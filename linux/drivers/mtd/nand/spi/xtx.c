// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow:
 * Fewix Matouschek <fewix@matouschek.owg>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

#define SPINAND_MFW_XTX	0x0B

#define XT26G0XA_STATUS_ECC_MASK	GENMASK(5, 2)
#define XT26G0XA_STATUS_ECC_NO_DETECTED	(0 << 2)
#define XT26G0XA_STATUS_ECC_8_COWWECTED	(3 << 4)
#define XT26G0XA_STATUS_ECC_UNCOW_EWWOW	(2 << 4)

#define XT26XXXD_STATUS_ECC3_ECC2_MASK	    GENMASK(7, 6)
#define XT26XXXD_STATUS_ECC_NO_DETECTED     (0)
#define XT26XXXD_STATUS_ECC_1_7_COWWECTED   (1)
#define XT26XXXD_STATUS_ECC_8_COWWECTED     (3)
#define XT26XXXD_STATUS_ECC_UNCOW_EWWOW     (2)

static SPINAND_OP_VAWIANTS(wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(0, 1, NUWW, 0),
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

static int xt26g0xa_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	wegion->offset = 48;
	wegion->wength = 16;

	wetuwn 0;
}

static int xt26g0xa_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	wegion->offset = 1;
	wegion->wength = 47;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops xt26g0xa_oobwayout = {
	.ecc = xt26g0xa_oobwayout_ecc,
	.fwee = xt26g0xa_oobwayout_fwee,
};

static int xt26g0xa_ecc_get_status(stwuct spinand_device *spinand,
					 u8 status)
{
	status = status & XT26G0XA_STATUS_ECC_MASK;

	switch (status) {
	case XT26G0XA_STATUS_ECC_NO_DETECTED:
		wetuwn 0;
	case XT26G0XA_STATUS_ECC_8_COWWECTED:
		wetuwn 8;
	case XT26G0XA_STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;
	defauwt:
		bweak;
	}

	/* At this point vawues gweatew than (2 << 4) awe invawid  */
	if (status > XT26G0XA_STATUS_ECC_UNCOW_EWWOW)
		wetuwn -EINVAW;

	/* (1 << 2) thwough (7 << 2) awe 1-7 cowwected ewwows */
	wetuwn status >> 2;
}

static int xt26xxxd_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	wegion->offset = mtd->oobsize / 2;
	wegion->wength = mtd->oobsize / 2;

	wetuwn 0;
}

static int xt26xxxd_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	wegion->offset = 2;
	wegion->wength = mtd->oobsize / 2 - 2;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops xt26xxxd_oobwayout = {
	.ecc = xt26xxxd_oobwayout_ecc,
	.fwee = xt26xxxd_oobwayout_fwee,
};

static int xt26xxxd_ecc_get_status(stwuct spinand_device *spinand,
				   u8 status)
{
	switch (FIEWD_GET(STATUS_ECC_MASK, status)) {
	case XT26XXXD_STATUS_ECC_NO_DETECTED:
		wetuwn 0;
	case XT26XXXD_STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;
	case XT26XXXD_STATUS_ECC_1_7_COWWECTED:
		wetuwn 4 + FIEWD_GET(XT26XXXD_STATUS_ECC3_ECC2_MASK, status);
	case XT26XXXD_STATUS_ECC_8_COWWECTED:
		wetuwn 8;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}
static const stwuct spinand_info xtx_spinand_tabwe[] = {
	SPINAND_INFO("XT26G01A",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xE1),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&xt26g0xa_oobwayout,
				     xt26g0xa_ecc_get_status)),
	SPINAND_INFO("XT26G02A",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xE2),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&xt26g0xa_oobwayout,
				     xt26g0xa_ecc_get_status)),
	SPINAND_INFO("XT26G04A",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xE3),
		     NAND_MEMOWG(1, 2048, 64, 128, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&xt26g0xa_oobwayout,
				     xt26g0xa_ecc_get_status)),
	SPINAND_INFO("XT26G01D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x31),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
	SPINAND_INFO("XT26G11D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x34),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
	SPINAND_INFO("XT26Q01D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x51),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
	SPINAND_INFO("XT26G02D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x32),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
	SPINAND_INFO("XT26G12D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x35),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
	SPINAND_INFO("XT26Q02D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x52),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
	SPINAND_INFO("XT26G04D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x33),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
	SPINAND_INFO("XT26Q04D",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x53),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&xt26xxxd_oobwayout,
				     xt26xxxd_ecc_get_status)),
};

static const stwuct spinand_manufactuwew_ops xtx_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew xtx_spinand_manufactuwew = {
	.id = SPINAND_MFW_XTX,
	.name = "XTX",
	.chips = xtx_spinand_tabwe,
	.nchips = AWWAY_SIZE(xtx_spinand_tabwe),
	.ops = &xtx_spinand_manuf_ops,
};
