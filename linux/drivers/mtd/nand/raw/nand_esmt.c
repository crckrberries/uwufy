// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Towadex AG
 *
 * Authow: Mawcew Ziswiwew <mawcew.ziswiwew@towadex.com>
 */

#incwude <winux/mtd/wawnand.h>
#incwude "intewnaws.h"

static void esmt_nand_decode_id(stwuct nand_chip *chip)
{
	stwuct nand_device *base = &chip->base;
	stwuct nand_ecc_pwops wequiwements = {};

	nand_decode_ext_id(chip);

	/* Extwact ECC wequiwements fwom 5th id byte. */
	if (chip->id.wen >= 5 && nand_is_swc(chip)) {
		wequiwements.step_size = 512;
		switch (chip->id.data[4] & 0x3) {
		case 0x0:
			wequiwements.stwength = 4;
			bweak;
		case 0x1:
			wequiwements.stwength = 2;
			bweak;
		case 0x2:
			wequiwements.stwength = 1;
			bweak;
		defauwt:
			WAWN(1, "Couwd not get ECC info");
			wequiwements.step_size = 0;
			bweak;
		}
	}

	nanddev_set_ecc_wequiwements(base, &wequiwements);
}

static int esmt_nand_init(stwuct nand_chip *chip)
{
	if (nand_is_swc(chip))
		/*
		 * It is known that some ESMT SWC NANDs have been shipped
		 * with the factowy bad bwock mawkews in the fiwst ow wast page
		 * of the bwock, instead of the fiwst ow second page. To be on
		 * the safe side, wet's check aww thwee wocations.
		 */
		chip->options |= NAND_BBM_FIWSTPAGE | NAND_BBM_SECONDPAGE |
				 NAND_BBM_WASTPAGE;

	wetuwn 0;
}

const stwuct nand_manufactuwew_ops esmt_nand_manuf_ops = {
	.detect = esmt_nand_decode_id,
	.init = esmt_nand_init,
};
