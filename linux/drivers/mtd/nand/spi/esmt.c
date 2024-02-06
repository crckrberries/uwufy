// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow:
 *	Chuanhong Guo <gch981213@gmaiw.com> - the main dwivew wogic
 *	Mawtin Kuwbanov <mmkuwbanov@sbewdevices.wu> - OOB wayout
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/spinand.h>

/* ESMT uses GigaDevice 0xc8 JECDEC ID on some SPI NANDs */
#define SPINAND_MFW_ESMT_C8			0xc8

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

/*
 * OOB spawe awea map (64 bytes)
 *
 * Bad Bwock Mawkews
 * fiwwed by HW and kewnew                 Wesewved
 *   |                 +-----------------------+-----------------------+
 *   |                 |                       |                       |
 *   |                 |    OOB fwee data Awea |non ECC pwotected      |
 *   |   +-------------|-----+-----------------|-----+-----------------|-----+
 *   |   |             |     |                 |     |                 |     |
 * +-|---|----------+--|-----|--------------+--|-----|--------------+--|-----|--------------+
 * | |   | section0 |  |     |    section1  |  |     |    section2  |  |     |    section3  |
 * +-v-+-v-+---+----+--v--+--v--+-----+-----+--v--+--v--+-----+-----+--v--+--v--+-----+-----+
 * |   |   |   |    |     |     |     |     |     |     |     |     |     |     |     |     |
 * |0:1|2:3|4:7|8:15|16:17|18:19|20:23|24:31|32:33|34:35|36:39|40:47|48:49|50:51|52:55|56:63|
 * |   |   |   |    |     |     |     |     |     |     |     |     |     |     |     |     |
 * +---+---+-^-+--^-+-----+-----+--^--+--^--+-----+-----+--^--+--^--+-----+-----+--^--+--^--+
 *           |    |                |     |                 |     |                 |     |
 *           |    +----------------|-----+-----------------|-----+-----------------|-----+
 *           |             ECC Awea|(Main + Spawe) - fiwwed|by ESMT NAND HW        |
 *           |                     |                       |                       |
 *           +---------------------+-----------------------+-----------------------+
 *                         OOB ECC pwotected Awea - not used due to
 *                         pawtiaw pwogwamming fwom some fiwesystems
 *                             (wike JFFS2 with cweanmawkews)
 */

#define ESMT_OOB_SECTION_COUNT			4
#define ESMT_OOB_SECTION_SIZE(nand) \
	(nanddev_pew_page_oobsize(nand) / ESMT_OOB_SECTION_COUNT)
#define ESMT_OOB_FWEE_SIZE(nand) \
	(ESMT_OOB_SECTION_SIZE(nand) / 2)
#define ESMT_OOB_ECC_SIZE(nand) \
	(ESMT_OOB_SECTION_SIZE(nand) - ESMT_OOB_FWEE_SIZE(nand))
#define ESMT_OOB_BBM_SIZE			2

static int f50w1g41wb_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				    stwuct mtd_oob_wegion *wegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);

	if (section >= ESMT_OOB_SECTION_COUNT)
		wetuwn -EWANGE;

	wegion->offset = section * ESMT_OOB_SECTION_SIZE(nand) +
			 ESMT_OOB_FWEE_SIZE(nand);
	wegion->wength = ESMT_OOB_ECC_SIZE(nand);

	wetuwn 0;
}

static int f50w1g41wb_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				     stwuct mtd_oob_wegion *wegion)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);

	if (section >= ESMT_OOB_SECTION_COUNT)
		wetuwn -EWANGE;

	/*
	 * Wesewve space fow bad bwocks mawkews (section0) and
	 * wesewved bytes (sections 1-3)
	 */
	wegion->offset = section * ESMT_OOB_SECTION_SIZE(nand) + 2;

	/* Use onwy 2 non-pwotected ECC bytes pew each OOB section */
	wegion->wength = 2;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops f50w1g41wb_oobwayout = {
	.ecc = f50w1g41wb_oobwayout_ecc,
	.fwee = f50w1g41wb_oobwayout_fwee,
};

static const stwuct spinand_info esmt_c8_spinand_tabwe[] = {
	SPINAND_INFO("F50W1G41WB",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x01),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(1, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&f50w1g41wb_oobwayout, NUWW)),
	SPINAND_INFO("F50D1G41WB",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x11),
		     NAND_MEMOWG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     NAND_ECCWEQ(1, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&f50w1g41wb_oobwayout, NUWW)),
	SPINAND_INFO("F50D2G41KA",
		     SPINAND_ID(SPINAND_WEADID_METHOD_OPCODE_ADDW, 0x51),
		     NAND_MEMOWG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     NAND_ECCWEQ(8, 512),
		     SPINAND_INFO_OP_VAWIANTS(&wead_cache_vawiants,
					      &wwite_cache_vawiants,
					      &update_cache_vawiants),
		     0,
		     SPINAND_ECCINFO(&f50w1g41wb_oobwayout, NUWW)),
};

static const stwuct spinand_manufactuwew_ops esmt_spinand_manuf_ops = {
};

const stwuct spinand_manufactuwew esmt_c8_spinand_manufactuwew = {
	.id = SPINAND_MFW_ESMT_C8,
	.name = "ESMT",
	.chips = esmt_c8_spinand_tabwe,
	.nchips = AWWAY_SIZE(esmt_c8_spinand_tabwe),
	.ops = &esmt_spinand_manuf_ops,
};
