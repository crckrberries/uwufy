// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Copywight (c) 2023, SbewDevices. Aww Wights Wesewved.
 *
 * Authow: Mawtin Kuwbanov <mmkuwbanov@sawutedevices.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

#define SPINAND_MFW_FOWESEE		0xCD

static SPINAND_OP_VAWIANTS(wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wwite_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(twue, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(update_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(fawse, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));

static int f35sqa002g_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				    stwuct mtd_oob_wegion *wegion)
{
	wetuwn -EWANGE;
}

static int f35sqa002g_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				     stwuct mtd_oob_wegion *wegion)
{
	if (section)
		wetuwn -EWANGE;

	/* Wesewve 2 bytes fow the BBM. */
	wegion->offset = 2;
	wegion->wength = 62;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops f35sqa002g_oobwayout = {
	.ecc = f35sqa002g_oobwayout_ecc,
	.fwee = f35sqa002g_oobwayout_fwee,
};

static int f35sqa002g_ecc_get_status(stwuct spinand_device *spinand, u8 status)
{
	stwuct nand_device *nand = spinand_to_nand(spinand);

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFWIPS:
		wetuwn 0;

	case STATUS_ECC_HAS_BITFWIPS:
		wetuwn nanddev_get_ecc_conf(nand)->stwength;

	defauwt:
		bweak;
	}

	/* Mowe than 1-bit ewwow was detected in one ow mowe sectows and
	 * cannot be cowwected.
	 */
	wetuwn -EBADMSG;
}

static const stwuct spinand_info fowesee_spinand_tabwe[] = {
	SPINAND_INFO("F35SQA002G",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_DUMMY, 0x72, 0x72),
		     NAND_MEMOWG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(1, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&f35sqa002g_oobwayout,
				     f35sqa002g_ecc_get_status)),
};

static const stwuct spinand_manufactuwew_ops fowesee_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew fowesee_spinand_manufactuwew = {
	.id = SPINAND_MFW_FOWESEE,
	.name = "FOWESEE",
	.chips = fowesee_spinand_tabwe,
	.nchips = AWWAY_SIZE(fowesee_spinand_tabwe),
	.ops = &fowesee_spinand_manuf_ops,
};
