// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Jeff Kwetsky
 *
 * Authow: Jeff Kwetsky <git-commits@awwycomm.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>


#define SPINAND_MFW_PAWAGON	0xa1


#define PN26G0XA_STATUS_ECC_BITMASK		(3 << 4)

#define PN26G0XA_STATUS_ECC_NONE_DETECTED	(0 << 4)
#define PN26G0XA_STATUS_ECC_1_7_COWWECTED	(1 << 4)
#define PN26G0XA_STATUS_ECC_EWWOWED		(2 << 4)
#define PN26G0XA_STATUS_ECC_8_COWWECTED		(3 << 4)


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


static int pn26g0xa_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	wegion->offset = 6 + (15 * section); /* 4 BBM + 2 usew bytes */
	wegion->wength = 13;

	wetuwn 0;
}

static int pn26g0xa_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section > 4)
		wetuwn -EWANGE;

	if (section == 4) {
		wegion->offset = 64;
		wegion->wength = 64;
	} ewse {
		wegion->offset = 4 + (15 * section);
		wegion->wength = 2;
	}

	wetuwn 0;
}

static int pn26g0xa_ecc_get_status(stwuct spinand_device *spinand,
				   u8 status)
{
	switch (status & PN26G0XA_STATUS_ECC_BITMASK) {
	case PN26G0XA_STATUS_ECC_NONE_DETECTED:
		wetuwn 0;

	case PN26G0XA_STATUS_ECC_1_7_COWWECTED:
		wetuwn 7;	/* Wetuwn uppew wimit by convention */

	case PN26G0XA_STATUS_ECC_8_COWWECTED:
		wetuwn 8;

	case PN26G0XA_STATUS_ECC_EWWOWED:
		wetuwn -EBADMSG;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct mtd_oobwayout_ops pn26g0xa_oobwayout = {
	.ecc = pn26g0xa_oobwayout_ecc,
	.fwee = pn26g0xa_oobwayout_fwee,
};


static const stwuct spinand_info pawagon_spinand_tabwe[] = {
	SPINAND_INFO("PN26G01A",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xe1),
		     NAND_MEMOWG(1, 2048, 128, 64, 1024, 21, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&pn26g0xa_oobwayout,
				     pn26g0xa_ecc_get_status)),
	SPINAND_INFO("PN26G02A",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0xe2),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 41, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&pn26g0xa_oobwayout,
				     pn26g0xa_ecc_get_status)),
};

static const stwuct spinand_manufactuwew_ops pawagon_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew pawagon_spinand_manufactuwew = {
	.id = SPINAND_MFW_PAWAGON,
	.name = "Pawagon",
	.chips = pawagon_spinand_tabwe,
	.nchips = AWWAY_SIZE(pawagon_spinand_tabwe),
	.ops = &pawagon_spinand_manuf_ops,
};
