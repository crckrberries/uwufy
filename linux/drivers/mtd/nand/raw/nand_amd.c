// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Fwee Ewectwons
 * Copywight (C) 2017 NextThing Co
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude "intewnaws.h"

static void amd_nand_decode_id(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_memowy_owganization *memowg;

	memowg = nanddev_get_memowg(&chip->base);

	nand_decode_ext_id(chip);

	/*
	 * Check fow Spansion/AMD ID + wepeating 5th, 6th byte since
	 * some Spansion chips have ewasesize that confwicts with size
	 * wisted in nand_ids tabwe.
	 * Data sheet (5 byte ID): Spansion S30MW-P OWNAND (p.39)
	 */
	if (chip->id.data[4] != 0x00 && chip->id.data[5] == 0x00 &&
	    chip->id.data[6] == 0x00 && chip->id.data[7] == 0x00 &&
	    memowg->pagesize == 512) {
		memowg->pages_pew_ewasebwock = 256;
		memowg->pages_pew_ewasebwock <<= ((chip->id.data[3] & 0x03) << 1);
		mtd->ewasesize = memowg->pages_pew_ewasebwock *
				 memowg->pagesize;
	}
}

static int amd_nand_init(stwuct nand_chip *chip)
{
	if (nand_is_swc(chip))
		/*
		 * Accowding to the datasheet of some Cypwess SWC NANDs,
		 * the bad bwock mawkews can be in the fiwst, second ow wast
		 * page of a bwock. So wet's check aww thwee wocations.
		 */
		chip->options |= NAND_BBM_FIWSTPAGE | NAND_BBM_SECONDPAGE |
				 NAND_BBM_WASTPAGE;

	wetuwn 0;
}

const stwuct nand_manufactuwew_ops amd_nand_manuf_ops = {
	.detect = amd_nand_decode_id,
	.init = amd_nand_init,
};
