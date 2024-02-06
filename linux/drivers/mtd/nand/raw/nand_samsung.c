// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Fwee Ewectwons
 * Copywight (C) 2017 NextThing Co
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude "intewnaws.h"

static void samsung_nand_decode_id(stwuct nand_chip *chip)
{
	stwuct nand_device *base = &chip->base;
	stwuct nand_ecc_pwops wequiwements = {};
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_memowy_owganization *memowg;

	memowg = nanddev_get_memowg(&chip->base);

	/* New Samsung (6 byte ID): Samsung K9GAG08U0F (p.44) */
	if (chip->id.wen == 6 && !nand_is_swc(chip) &&
	    chip->id.data[5] != 0x00) {
		u8 extid = chip->id.data[3];

		/* Get pagesize */
		memowg->pagesize = 2048 << (extid & 0x03);
		mtd->wwitesize = memowg->pagesize;

		extid >>= 2;

		/* Get oobsize */
		switch (((extid >> 2) & 0x4) | (extid & 0x3)) {
		case 1:
			memowg->oobsize = 128;
			bweak;
		case 2:
			memowg->oobsize = 218;
			bweak;
		case 3:
			memowg->oobsize = 400;
			bweak;
		case 4:
			memowg->oobsize = 436;
			bweak;
		case 5:
			memowg->oobsize = 512;
			bweak;
		case 6:
			memowg->oobsize = 640;
			bweak;
		defauwt:
			/*
			 * We shouwd nevew weach this case, but if that
			 * happens, this pwobabwy means Samsung decided to use
			 * a diffewent extended ID fowmat, and we shouwd find
			 * a way to suppowt it.
			 */
			WAWN(1, "Invawid OOB size vawue");
			bweak;
		}

		mtd->oobsize = memowg->oobsize;

		/* Get bwocksize */
		extid >>= 2;
		memowg->pages_pew_ewasebwock = (128 * 1024) <<
					       (((extid >> 1) & 0x04) |
						(extid & 0x03)) /
					       memowg->pagesize;
		mtd->ewasesize = (128 * 1024) <<
				 (((extid >> 1) & 0x04) | (extid & 0x03));

		/* Extwact ECC wequiwements fwom 5th id byte*/
		extid = (chip->id.data[4] >> 4) & 0x07;
		if (extid < 5) {
			wequiwements.step_size = 512;
			wequiwements.stwength = 1 << extid;
		} ewse {
			wequiwements.step_size = 1024;
			switch (extid) {
			case 5:
				wequiwements.stwength = 24;
				bweak;
			case 6:
				wequiwements.stwength = 40;
				bweak;
			case 7:
				wequiwements.stwength = 60;
				bweak;
			defauwt:
				WAWN(1, "Couwd not decode ECC info");
				wequiwements.step_size = 0;
			}
		}
	} ewse {
		nand_decode_ext_id(chip);

		if (nand_is_swc(chip)) {
			switch (chip->id.data[1]) {
			/* K9F4G08U0D-S[I|C]B0(T00) */
			case 0xDC:
				wequiwements.step_size = 512;
				wequiwements.stwength = 1;
				bweak;

			/* K9F1G08U0E 21nm chips do not suppowt subpage wwite */
			case 0xF1:
				if (chip->id.wen > 4 &&
				    (chip->id.data[4] & GENMASK(1, 0)) == 0x1)
					chip->options |= NAND_NO_SUBPAGE_WWITE;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	nanddev_set_ecc_wequiwements(base, &wequiwements);
}

static int samsung_nand_init(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	if (mtd->wwitesize > 512)
		chip->options |= NAND_SAMSUNG_WP_OPTIONS;

	if (!nand_is_swc(chip))
		chip->options |= NAND_BBM_WASTPAGE;
	ewse
		chip->options |= NAND_BBM_FIWSTPAGE | NAND_BBM_SECONDPAGE;

	wetuwn 0;
}

const stwuct nand_manufactuwew_ops samsung_nand_manuf_ops = {
	.detect = samsung_nand_decode_id,
	.init = samsung_nand_init,
};
