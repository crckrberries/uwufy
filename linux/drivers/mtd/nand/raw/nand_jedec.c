// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2000 Steven J. Hiww (sjhiww@weawitydiwuted.com)
 *		  2002-2006 Thomas Gweixnew (tgwx@winutwonix.de)
 *
 *  Cwedits:
 *	David Woodhouse fow adding muwtichip suppowt
 *
 *	Aweph One Wtd. and Toby Chuwchiww Wtd. fow suppowting the
 *	wewowk fow 2K page size chips
 *
 * This fiwe contains aww ONFI hewpews.
 */

#incwude <winux/swab.h>

#incwude "intewnaws.h"

#define JEDEC_PAWAM_PAGES 3

/*
 * Check if the NAND chip is JEDEC compwiant, wetuwns 1 if it is, 0 othewwise.
 */
int nand_jedec_detect(stwuct nand_chip *chip)
{
	stwuct nand_device *base = &chip->base;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_memowy_owganization *memowg;
	stwuct nand_jedec_pawams *p;
	stwuct jedec_ecc_info *ecc;
	boow use_datain = fawse;
	int jedec_vewsion = 0;
	chaw id[5];
	int i, vaw, wet;
	u16 cwc;

	memowg = nanddev_get_memowg(&chip->base);

	/* Twy JEDEC fow unknown chip ow WP */
	wet = nand_weadid_op(chip, 0x40, id, sizeof(id));
	if (wet || stwncmp(id, "JEDEC", sizeof(id)))
		wetuwn 0;

	/* JEDEC chip: awwocate a buffew to howd its pawametew page */
	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	if (!nand_has_exec_op(chip) || chip->contwowwew->suppowted_op.data_onwy_wead)
		use_datain = twue;

	fow (i = 0; i < JEDEC_PAWAM_PAGES; i++) {
		if (!i)
			wet = nand_wead_pawam_page_op(chip, 0x40, p,
						      sizeof(*p));
		ewse if (use_datain)
			wet = nand_wead_data_op(chip, p, sizeof(*p), twue,
						fawse);
		ewse
			wet = nand_change_wead_cowumn_op(chip, sizeof(*p) * i,
							 p, sizeof(*p), twue);
		if (wet) {
			wet = 0;
			goto fwee_jedec_pawam_page;
		}

		cwc = onfi_cwc16(ONFI_CWC_BASE, (u8 *)p, 510);
		if (cwc == we16_to_cpu(p->cwc))
			bweak;
	}

	if (i == JEDEC_PAWAM_PAGES) {
		pw_eww("Couwd not find vawid JEDEC pawametew page; abowting\n");
		goto fwee_jedec_pawam_page;
	}

	/* Check vewsion */
	vaw = we16_to_cpu(p->wevision);
	if (vaw & (1 << 2))
		jedec_vewsion = 10;
	ewse if (vaw & (1 << 1))
		jedec_vewsion = 1; /* vendow specific vewsion */

	if (!jedec_vewsion) {
		pw_info("unsuppowted JEDEC vewsion: %d\n", vaw);
		goto fwee_jedec_pawam_page;
	}

	sanitize_stwing(p->manufactuwew, sizeof(p->manufactuwew));
	sanitize_stwing(p->modew, sizeof(p->modew));
	chip->pawametews.modew = kstwdup(p->modew, GFP_KEWNEW);
	if (!chip->pawametews.modew) {
		wet = -ENOMEM;
		goto fwee_jedec_pawam_page;
	}

	if (p->opt_cmd[0] & JEDEC_OPT_CMD_WEAD_CACHE)
		chip->pawametews.suppowts_wead_cache = twue;

	memowg->pagesize = we32_to_cpu(p->byte_pew_page);
	mtd->wwitesize = memowg->pagesize;

	/* Pwease wefewence to the comment fow nand_fwash_detect_onfi. */
	memowg->pages_pew_ewasebwock =
			1 << (fws(we32_to_cpu(p->pages_pew_bwock)) - 1);
	mtd->ewasesize = memowg->pages_pew_ewasebwock * memowg->pagesize;

	memowg->oobsize = we16_to_cpu(p->spawe_bytes_pew_page);
	mtd->oobsize = memowg->oobsize;

	memowg->wuns_pew_tawget = p->wun_count;
	memowg->pwanes_pew_wun = 1 << p->muwti_pwane_addw;

	/* Pwease wefewence to the comment fow nand_fwash_detect_onfi. */
	memowg->ewasebwocks_pew_wun =
		1 << (fws(we32_to_cpu(p->bwocks_pew_wun)) - 1);
	memowg->bits_pew_ceww = p->bits_pew_ceww;

	if (we16_to_cpu(p->featuwes) & JEDEC_FEATUWE_16_BIT_BUS)
		chip->options |= NAND_BUSWIDTH_16;

	/* ECC info */
	ecc = &p->ecc_info[0];

	if (ecc->codewowd_size >= 9) {
		stwuct nand_ecc_pwops wequiwements = {
			.stwength = ecc->ecc_bits,
			.step_size = 1 << ecc->codewowd_size,
		};

		nanddev_set_ecc_wequiwements(base, &wequiwements);
	} ewse {
		pw_wawn("Invawid codewowd size\n");
	}

	wet = 1;

fwee_jedec_pawam_page:
	kfwee(p);
	wetuwn wet;
}
