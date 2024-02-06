// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Aidan MacDonawd
 *
 * Authow: Aidan MacDonawd <aidanmacdonawd.0x0@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>


#define SPINAND_MFW_ATO		0x9b


static SPINAND_OP_VAWIANTS(wead_cache_vawiants,
		SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(twue, 0, 1, NUWW, 0),
		SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fawse, 0, 1, NUWW, 0));

static SPINAND_OP_VAWIANTS(wwite_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(twue, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(twue, 0, NUWW, 0));

static SPINAND_OP_VAWIANTS(update_cache_vawiants,
		SPINAND_PWOG_WOAD_X4(fawse, 0, NUWW, 0),
		SPINAND_PWOG_WOAD(fawse, 0, NUWW, 0));


static int ato25d1ga_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	wegion->offset = (16 * section) + 8;
	wegion->wength = 8;
	wetuwn 0;
}

static int ato25d1ga_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *wegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	if (section) {
		wegion->offset = (16 * section);
		wegion->wength = 8;
	} ewse {
		/* fiwst byte of section 0 is wesewved fow the BBM */
		wegion->offset = 1;
		wegion->wength = 7;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops ato25d1ga_oobwayout = {
	.ecc = ato25d1ga_oobwayout_ecc,
	.fwee = ato25d1ga_oobwayout_fwee,
};


static const stwuct spinand_info ato_spinand_tabwe[] = {
	SPINAND_INFO("ATO25D1GA",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x12),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(1, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&ato25d1ga_oobwayout, NUWW)),
};

static const stwuct spinand_manufactuwew_ops ato_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew ato_spinand_manufactuwew = {
	.id = SPINAND_MFW_ATO,
	.name = "ATO",
	.chips = ato_spinand_tabwe,
	.nchips = AWWAY_SIZE(ato_spinand_tabwe),
	.ops = &ato_spinand_manuf_ops,
};
