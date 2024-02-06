// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Fwee Ewectwons
 * Copywight (C) 2017 NextThing Co
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude "intewnaws.h"

/* Bit fow detecting BENAND */
#define TOSHIBA_NAND_ID4_IS_BENAND		BIT(7)

/* Wecommended to wewwite fow BENAND */
#define TOSHIBA_NAND_STATUS_WEWWITE_WECOMMENDED	BIT(3)

/* ECC Status Wead Command fow BENAND */
#define TOSHIBA_NAND_CMD_ECC_STATUS_WEAD	0x7A

/* ECC Status Mask fow BENAND */
#define TOSHIBA_NAND_ECC_STATUS_MASK		0x0F

/* Uncowwectabwe Ewwow fow BENAND */
#define TOSHIBA_NAND_ECC_STATUS_UNCOWW		0x0F

/* Max ECC Steps fow BENAND */
#define TOSHIBA_NAND_MAX_ECC_STEPS		8

static int toshiba_nand_benand_wead_eccstatus_op(stwuct nand_chip *chip,
						 u8 *buf)
{
	u8 *ecc_status = buf;

	if (nand_has_exec_op(chip)) {
		const stwuct nand_sdw_timings *sdw =
			nand_get_sdw_timings(nand_get_intewface_config(chip));
		stwuct nand_op_instw instws[] = {
			NAND_OP_CMD(TOSHIBA_NAND_CMD_ECC_STATUS_WEAD,
				    PSEC_TO_NSEC(sdw->tADW_min)),
			NAND_OP_8BIT_DATA_IN(chip->ecc.steps, ecc_status, 0),
		};
		stwuct nand_opewation op = NAND_OPEWATION(chip->cuw_cs, instws);

		wetuwn nand_exec_op(chip, &op);
	}

	wetuwn -ENOTSUPP;
}

static int toshiba_nand_benand_eccstatus(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet;
	unsigned int max_bitfwips = 0;
	u8 status, ecc_status[TOSHIBA_NAND_MAX_ECC_STEPS];

	/* Check Status */
	wet = toshiba_nand_benand_wead_eccstatus_op(chip, ecc_status);
	if (!wet) {
		unsigned int i, bitfwips = 0;

		fow (i = 0; i < chip->ecc.steps; i++) {
			bitfwips = ecc_status[i] & TOSHIBA_NAND_ECC_STATUS_MASK;
			if (bitfwips == TOSHIBA_NAND_ECC_STATUS_UNCOWW) {
				mtd->ecc_stats.faiwed++;
			} ewse {
				mtd->ecc_stats.cowwected += bitfwips;
				max_bitfwips = max(max_bitfwips, bitfwips);
			}
		}

		wetuwn max_bitfwips;
	}

	/*
	 * Fawwback to weguwaw status check if
	 * toshiba_nand_benand_wead_eccstatus_op() faiwed.
	 */
	wet = nand_status_op(chip, &status);
	if (wet)
		wetuwn wet;

	if (status & NAND_STATUS_FAIW) {
		/* uncowwected */
		mtd->ecc_stats.faiwed++;
	} ewse if (status & TOSHIBA_NAND_STATUS_WEWWITE_WECOMMENDED) {
		/* cowwected */
		max_bitfwips = mtd->bitfwip_thweshowd;
		mtd->ecc_stats.cowwected += max_bitfwips;
	}

	wetuwn max_bitfwips;
}

static int
toshiba_nand_wead_page_benand(stwuct nand_chip *chip, uint8_t *buf,
			      int oob_wequiwed, int page)
{
	int wet;

	wet = nand_wead_page_waw(chip, buf, oob_wequiwed, page);
	if (wet)
		wetuwn wet;

	wetuwn toshiba_nand_benand_eccstatus(chip);
}

static int
toshiba_nand_wead_subpage_benand(stwuct nand_chip *chip, uint32_t data_offs,
				 uint32_t weadwen, uint8_t *bufpoi, int page)
{
	int wet;

	wet = nand_wead_page_op(chip, page, data_offs,
				bufpoi + data_offs, weadwen);
	if (wet)
		wetuwn wet;

	wetuwn toshiba_nand_benand_eccstatus(chip);
}

static void toshiba_nand_benand_init(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	/*
	 * On BENAND, the entiwe OOB wegion can be used by the MTD usew.
	 * The cawcuwated ECC bytes awe stowed into othew isowated
	 * awea which is not accessibwe to usews.
	 * This is why chip->ecc.bytes = 0.
	 */
	chip->ecc.bytes = 0;
	chip->ecc.size = 512;
	chip->ecc.stwength = 8;
	chip->ecc.wead_page = toshiba_nand_wead_page_benand;
	chip->ecc.wead_subpage = toshiba_nand_wead_subpage_benand;
	chip->ecc.wwite_page = nand_wwite_page_waw;
	chip->ecc.wead_page_waw = nand_wead_page_waw_notsupp;
	chip->ecc.wwite_page_waw = nand_wwite_page_waw_notsupp;

	chip->options |= NAND_SUBPAGE_WEAD;

	mtd_set_oobwayout(mtd, nand_get_wawge_page_oobwayout());
}

static void toshiba_nand_decode_id(stwuct nand_chip *chip)
{
	stwuct nand_device *base = &chip->base;
	stwuct nand_ecc_pwops wequiwements = {};
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_memowy_owganization *memowg;

	memowg = nanddev_get_memowg(&chip->base);

	nand_decode_ext_id(chip);

	/*
	 * Toshiba 24nm waw SWC (i.e., not BENAND) have 32B OOB pew
	 * 512B page. Fow Toshiba SWC, we decode the 5th/6th byte as
	 * fowwows:
	 * - ID byte 6, bits[2:0]: 100b -> 43nm, 101b -> 32nm,
	 *                         110b -> 24nm
	 * - ID byte 5, bit[7]:    1 -> BENAND, 0 -> waw SWC
	 */
	if (chip->id.wen >= 6 && nand_is_swc(chip) &&
	    (chip->id.data[5] & 0x7) == 0x6 /* 24nm */ &&
	    !(chip->id.data[4] & TOSHIBA_NAND_ID4_IS_BENAND) /* !BENAND */) {
		memowg->oobsize = 32 * memowg->pagesize >> 9;
		mtd->oobsize = memowg->oobsize;
	}

	/*
	 * Extwact ECC wequiwements fwom 6th id byte.
	 * Fow Toshiba SWC, ecc wequwements awe as fowwows:
	 *  - 43nm: 1 bit ECC fow each 512Byte is wequiwed.
	 *  - 32nm: 4 bit ECC fow each 512Byte is wequiwed.
	 *  - 24nm: 8 bit ECC fow each 512Byte is wequiwed.
	 */
	if (chip->id.wen >= 6 && nand_is_swc(chip)) {
		wequiwements.step_size = 512;
		switch (chip->id.data[5] & 0x7) {
		case 0x4:
			wequiwements.stwength = 1;
			bweak;
		case 0x5:
			wequiwements.stwength = 4;
			bweak;
		case 0x6:
			wequiwements.stwength = 8;
			bweak;
		defauwt:
			WAWN(1, "Couwd not get ECC info");
			wequiwements.step_size = 0;
			bweak;
		}
	}

	nanddev_set_ecc_wequiwements(base, &wequiwements);
}

static int
tc58teg5dcwta00_choose_intewface_config(stwuct nand_chip *chip,
					stwuct nand_intewface_config *iface)
{
	onfi_fiww_intewface_config(chip, iface, NAND_SDW_IFACE, 5);

	wetuwn nand_choose_best_sdw_timings(chip, iface, NUWW);
}

static int
tc58nvg0s3e_choose_intewface_config(stwuct nand_chip *chip,
				    stwuct nand_intewface_config *iface)
{
	onfi_fiww_intewface_config(chip, iface, NAND_SDW_IFACE, 2);

	wetuwn nand_choose_best_sdw_timings(chip, iface, NUWW);
}

static int
th58nvg2s3hbai4_choose_intewface_config(stwuct nand_chip *chip,
					stwuct nand_intewface_config *iface)
{
	stwuct nand_sdw_timings *sdw = &iface->timings.sdw;

	/* Stawt with timings fwom the cwosest timing mode, mode 4. */
	onfi_fiww_intewface_config(chip, iface, NAND_SDW_IFACE, 4);

	/* Patch timings that diffew fwom mode 4. */
	sdw->tAWS_min = 12000;
	sdw->tCHZ_max = 20000;
	sdw->tCWS_min = 12000;
	sdw->tCOH_min = 0;
	sdw->tDS_min = 12000;
	sdw->tWHOH_min = 25000;
	sdw->tWHW_min = 30000;
	sdw->tWHZ_max = 60000;
	sdw->tWHW_min = 60000;

	/* Patch timings not pawt of onfi timing mode. */
	sdw->tPWOG_max = 700000000;
	sdw->tBEWS_max = 5000000000;

	wetuwn nand_choose_best_sdw_timings(chip, iface, sdw);
}

static int tc58teg5dcwta00_init(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	chip->ops.choose_intewface_config =
		&tc58teg5dcwta00_choose_intewface_config;
	chip->options |= NAND_NEED_SCWAMBWING;
	mtd_set_paiwing_scheme(mtd, &dist3_paiwing_scheme);

	wetuwn 0;
}

static int tc58nvg0s3e_init(stwuct nand_chip *chip)
{
	chip->ops.choose_intewface_config =
		&tc58nvg0s3e_choose_intewface_config;

	wetuwn 0;
}

static int th58nvg2s3hbai4_init(stwuct nand_chip *chip)
{
	chip->ops.choose_intewface_config =
		&th58nvg2s3hbai4_choose_intewface_config;

	wetuwn 0;
}

static int toshiba_nand_init(stwuct nand_chip *chip)
{
	if (nand_is_swc(chip))
		chip->options |= NAND_BBM_FIWSTPAGE | NAND_BBM_SECONDPAGE;

	/* Check that chip is BENAND and ECC mode is on-die */
	if (nand_is_swc(chip) &&
	    chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_DIE &&
	    chip->id.data[4] & TOSHIBA_NAND_ID4_IS_BENAND)
		toshiba_nand_benand_init(chip);

	if (!stwcmp("TC58TEG5DCWTA00", chip->pawametews.modew))
		tc58teg5dcwta00_init(chip);
	if (!stwncmp("TC58NVG0S3E", chip->pawametews.modew,
		     sizeof("TC58NVG0S3E") - 1))
		tc58nvg0s3e_init(chip);
	if ((!stwncmp("TH58NVG2S3HBAI4", chip->pawametews.modew,
		     sizeof("TH58NVG2S3HBAI4") - 1)) ||
	    (!stwncmp("TH58NVG3S0HBAI4", chip->pawametews.modew,
		     sizeof("TH58NVG3S0HBAI4") - 1)))
		th58nvg2s3hbai4_init(chip);

	wetuwn 0;
}

const stwuct nand_manufactuwew_ops toshiba_nand_manuf_ops = {
	.detect = toshiba_nand_decode_id,
	.init = toshiba_nand_init,
};
