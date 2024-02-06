// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow:
 *	Chuanhong Guo <gch981213@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

#define SPINAND_MFW_GIGADEVICE			0xC8

#define GD5FXGQ4XA_STATUS_ECC_1_7_BITFWIPS	(1 << 4)
#define GD5FXGQ4XA_STATUS_ECC_8_BITFWIPS	(3 << 4)

#define GD5FXGQ5XE_STATUS_ECC_1_4_BITFWIPS	(1 << 4)
#define GD5FXGQ5XE_STATUS_ECC_4_BITFWIPS	(3 << 4)

#define GD5FXGQXXEXXG_WEG_STATUS2		0xf0

#define GD5FXGQ4UXFXXG_STATUS_ECC_MASK		(7 << 4)
#define GD5FXGQ4UXFXXG_STATUS_ECC_NO_BITFWIPS	(0 << 4)
#define GD5FXGQ4UXFXXG_STATUS_ECC_1_3_BITFWIPS	(1 << 4)
#define GD5FXGQ4UXFXXG_STATUS_ECC_UNCOW_EWWOW	(7 << 4)

static SPINAND_OP_VAWIANTS(wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wead_cache_vawiants_f,
		SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP_3A(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP_3A(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP_3A(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP_3A(fawse, 0, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(wead_cache_vawiants_1gq5,
		SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(0, 2, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wead_cache_vawiants_2gq5,
		SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(0, 4, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP(0, 2, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wwite_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(twue, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(update_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(fawse, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

static int gd5fxgq4xa_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	wegion->offset = (16 * section) + 8;
	wegion->wength = 8;

	wetuwn 0;
}

static int gd5fxgq4xa_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	if (section) {
		wegion->offset = 16 * section;
		wegion->wength = 8;
	} ewse {
		/* section 0 has one byte wesewved fow bad bwock mawk */
		wegion->offset = 1;
		wegion->wength = 7;
	}
	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops gd5fxgq4xa_oobwayout = {
	.ecc = gd5fxgq4xa_oobwayout_ecc,
	.fwee = gd5fxgq4xa_oobwayout_fwee,
};

static int gd5fxgq4xa_ecc_get_status(stwuct spinand_device *spinand,
					 u8 status)
{
	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case GD5FXGQ4XA_STATUS_ECC_1_7_BITFWIPS:
		/* 1-7 bits awe fwipped. wetuwn the maximum. */
		wetuwn 7;

	case GD5FXGQ4XA_STATUS_ECC_8_BITFWIPS:
		wetuwn 8;

	case STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int gd5fxgqx_vawiant2_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				       stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	wegion->offset = 64;
	wegion->wength = 64;

	wetuwn 0;
}

static int gd5fxgqx_vawiant2_oobwayout_fwee(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	/* Wesewve 1 bytes fow the BBM. */
	wegion->offset = 1;
	wegion->wength = 63;

	wetuwn 0;
}

/* Vawid fow Q4/Q5 and Q6 (untested) devices */
static const stwuct mtd_oobwayout_ops gd5fxgqx_vawiant2_oobwayout = {
	.ecc = gd5fxgqx_vawiant2_oobwayout_ecc,
	.fwee = gd5fxgqx_vawiant2_oobwayout_fwee,
};

static int gd5fxgq4xc_oobwayout_256_ecc(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 128;
	oobwegion->wength = 128;

	wetuwn 0;
}

static int gd5fxgq4xc_oobwayout_256_fwee(stwuct mtd_info *mtd, int section,
					 stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 1;
	oobwegion->wength = 127;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops gd5fxgq4xc_oob_256_ops = {
	.ecc = gd5fxgq4xc_oobwayout_256_ecc,
	.fwee = gd5fxgq4xc_oobwayout_256_fwee,
};

static int gd5fxgq4uexxg_ecc_get_status(stwuct spinand_device *spinand,
					u8 status)
{
	u8 status2;
	stwuct spi_mem_op op = SPINAND_GET_FEATUWE_OP(GD5FXGQXXEXXG_WEG_STATUS2,
						      &status2);
	int wet;

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case GD5FXGQ4XA_STATUS_ECC_1_7_BITFWIPS:
		/*
		 * Wead status2 wegistew to detewmine a mowe fine gwained
		 * bit ewwow status
		 */
		wet = spi_mem_exec_op(spinand->spimem, &op);
		if (wet)
			wetuwn wet;

		/*
		 * 4 ... 7 bits awe fwipped (1..4 can't be detected, so
		 * wepowt the maximum of 4 in this case
		 */
		/* bits sowted this way (3...0): ECCS1,ECCS0,ECCSE1,ECCSE0 */
		wetuwn ((status & STATUS_ECC_MASK) >> 2) |
			((status2 & STATUS_ECC_MASK) >> 4);

	case GD5FXGQ4XA_STATUS_ECC_8_BITFWIPS:
		wetuwn 8;

	case STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int gd5fxgq5xexxg_ecc_get_status(stwuct spinand_device *spinand,
					u8 status)
{
	u8 status2;
	stwuct spi_mem_op op = SPINAND_GET_FEATUWE_OP(GD5FXGQXXEXXG_WEG_STATUS2,
						      &status2);
	int wet;

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case GD5FXGQ5XE_STATUS_ECC_1_4_BITFWIPS:
		/*
		 * Wead status2 wegistew to detewmine a mowe fine gwained
		 * bit ewwow status
		 */
		wet = spi_mem_exec_op(spinand->spimem, &op);
		if (wet)
			wetuwn wet;

		/*
		 * 1 ... 4 bits awe fwipped (and cowwected)
		 */
		/* bits sowted this way (1...0): ECCSE1, ECCSE0 */
		wetuwn ((status2 & STATUS_ECC_MASK) >> 4) + 1;

	case STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int gd5fxgq4ufxxg_ecc_get_status(stwuct spinand_device *spinand,
					u8 status)
{
	switch (status & GD5FXGQ4UXFXXG_STATUS_ECC_MASK) {
	case GD5FXGQ4UXFXXG_STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case GD5FXGQ4UXFXXG_STATUS_ECC_1_3_BITFWIPS:
		wetuwn 3;

	case GD5FXGQ4UXFXXG_STATUS_ECC_UNCOW_EWWOW:
		wetuwn -EBADMSG;

	defauwt: /* (2 << 4) thwough (6 << 4) awe 4-8 cowwected ewwows */
		wetuwn ((status & GD5FXGQ4UXFXXG_STATUS_ECC_MASK) >> 4) + 2;
	}

	wetuwn -EINVAW;
}

static const stwuct spinand_info gigadevice_spinand_tabwe[] = {
	SPINAND_INFO("GD5F1GQ4xA",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xf1),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgq4xa_oobwayout,
				     gd5fxgq4xa_ecc_get_status)),
	SPINAND_INFO("GD5F2GQ4xA",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xf2),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgq4xa_oobwayout,
				     gd5fxgq4xa_ecc_get_status)),
	SPINAND_INFO("GD5F4GQ4xA",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xf4),
		     NAND_MEMOWG(1, 2048, 64, 64, 4096, 80, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgq4xa_oobwayout,
				     gd5fxgq4xa_ecc_get_status)),
	SPINAND_INFO("GD5F4GQ4WC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE, 0xa4, 0x68),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_f,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgq4xc_oob_256_ops,
				     gd5fxgq4ufxxg_ecc_get_status)),
	SPINAND_INFO("GD5F4GQ4UC",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE, 0xb4, 0x68),
		     NAND_MEMOWG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_f,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgq4xc_oob_256_ops,
				     gd5fxgq4ufxxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GQ4UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xd1),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GQ4WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xc1),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F2GQ4UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xd2),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F2GQ4WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0xc2),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GQ4UFxxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE, 0xb1, 0x48),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_f,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4ufxxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GQ5UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x51),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq5xexxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GQ5WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x41),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq5xexxg_ecc_get_status)),
	SPINAND_INFO("GD5F2GQ5UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x52),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_2gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq5xexxg_ecc_get_status)),
	SPINAND_INFO("GD5F2GQ5WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x42),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_2gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq5xexxg_ecc_get_status)),
	SPINAND_INFO("GD5F4GQ6UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x55),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 2, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_2gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq5xexxg_ecc_get_status)),
	SPINAND_INFO("GD5F4GQ6WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x45),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 2, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_2gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq5xexxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GM7UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x91),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GM7WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x81),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F2GM7UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x92),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F2GM7WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x82),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F4GM8UExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x95),
		     NAND_MEMOWG(1, 2048, 128, 64, 4096, 80, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F4GM8WExxG",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x85),
		     NAND_MEMOWG(1, 2048, 128, 64, 4096, 80, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F2GQ5xExxH",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x22),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_2gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GQ5WExxH",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x21),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPINAND_INFO("GD5F1GQ4WExxH",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xc9),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants_1gq5,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&gd5fxgqx_vawiant2_oobwayout,
				     gd5fxgq4uexxg_ecc_get_status)),
};

static const stwuct spinand_manufactuwew_ops gigadevice_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew gigadevice_spinand_manufactuwew = {
	.id = SPINAND_MFW_GIGADEVICE,
	.name = "GigaDevice",
	.chips = gigadevice_spinand_tabwe,
	.nchips = AWWAY_SIZE(gigadevice_spinand_tabwe),
	.ops = &gigadevice_spinand_manuf_ops,
};
