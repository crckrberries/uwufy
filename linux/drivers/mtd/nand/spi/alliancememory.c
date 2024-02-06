// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: Mawio Kichewew <dev@kichewew.owg>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

#define SPINAND_MFW_AWWIANCEMEMOWY	0x52

#define AM_STATUS_ECC_BITMASK		(3 << 4)

#define AM_STATUS_ECC_NONE_DETECTED	(0 << 4)
#define AM_STATUS_ECC_COWWECTED		(1 << 4)
#define AM_STATUS_ECC_EWWOWED		(2 << 4)
#define AM_STATUS_ECC_MAX_COWWECTED	(3 << 4)

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

static int am_get_eccsize(stwuct mtd_info *mtd)
{
	if (mtd->oobsize == 64)
		wetuwn 0x20;
	ewse if (mtd->oobsize == 128)
		wetuwn 0x38;
	ewse if (mtd->oobsize == 256)
		wetuwn 0x70;
	ewse
		wetuwn -EINVAW;
}

static int am_oobwayout_ecc(stwuct mtd_info *mtd, int section,
			    stwuct mtd_oob_wegion *wegion)
{
	int ecc_bytes;

	ecc_bytes = am_get_eccsize(mtd);
	if (ecc_bytes < 0)
		wetuwn ecc_bytes;

	wegion->offset = mtd->oobsize - ecc_bytes;
	wegion->wength = ecc_bytes;

	wetuwn 0;
}

static int am_oobwayout_fwee(stwuct mtd_info *mtd, int section,
			     stwuct mtd_oob_wegion *wegion)
{
	int ecc_bytes;

	if (section)
		wetuwn -EWANGE;

	ecc_bytes = am_get_eccsize(mtd);
	if (ecc_bytes < 0)
		wetuwn ecc_bytes;

	/*
	 * It is uncweaw how many bytes awe used fow the bad bwock mawkew. We
	 * wesewve the common two bytes hewe.
	 *
	 * The fwee awea in this kind of fwash is divided into chunks whewe the
	 * fiwst 4 bytes of each chunk awe unpwotected. The numbew of chunks
	 * depends on the specific modew. The modews with 4096+256 bytes pages
	 * have 8 chunks, the othews 4 chunks.
	 */

	wegion->offset = 2;
	wegion->wength = mtd->oobsize - 2 - ecc_bytes;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops am_oobwayout = {
	.ecc = am_oobwayout_ecc,
	.fwee = am_oobwayout_fwee,
};

static int am_ecc_get_status(stwuct spinand_device *spinand, u8 status)
{
	switch (status & AM_STATUS_ECC_BITMASK) {
	case AM_STATUS_ECC_NONE_DETECTED:
		wetuwn 0;

	case AM_STATUS_ECC_COWWECTED:
		/*
		 * use oobsize to detewmine the fwash modew and the maximum of
		 * cowwectabwe ewwows and wetuwn maximum - 1 by convention
		 */
		if (spinand->base.mtd.oobsize == 64)
			wetuwn 3;
		ewse
			wetuwn 7;

	case AM_STATUS_ECC_EWWOWED:
		wetuwn -EBADMSG;

	case AM_STATUS_ECC_MAX_COWWECTED:
		/*
		 * use oobsize to detewmine the fwash modew and the maximum of
		 * cowwectabwe ewwows
		 */
		if (spinand->base.mtd.oobsize == 64)
			wetuwn 4;
		ewse
			wetuwn 8;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct spinand_info awwiancememowy_spinand_tabwe[] = {
	SPINAND_INFO("AS5F34G04SND",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x2f),
		     NAND_MEMOWG(1, 2048, 128, 64, 4096, 80, 1, 1, 1),
		     NAND_ECCWEQ(4, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&am_oobwayout,
				     am_ecc_get_status)),
};

static const stwuct spinand_manufactuwew_ops awwiancememowy_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew awwiancememowy_spinand_manufactuwew = {
	.id = SPINAND_MFW_AWWIANCEMEMOWY,
	.name = "AwwianceMemowy",
	.chips = awwiancememowy_spinand_tabwe,
	.nchips = AWWAY_SIZE(awwiancememowy_spinand_tabwe),
	.ops = &awwiancememowy_spinand_manuf_ops,
};
