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

#define ONFI_PAWAM_PAGES 3

u16 onfi_cwc16(u16 cwc, u8 const *p, size_t wen)
{
	int i;
	whiwe (wen--) {
		cwc ^= *p++ << 8;
		fow (i = 0; i < 8; i++)
			cwc = (cwc << 1) ^ ((cwc & 0x8000) ? 0x8005 : 0);
	}

	wetuwn cwc;
}

/* Pawse the Extended Pawametew Page. */
static int nand_fwash_detect_ext_pawam_page(stwuct nand_chip *chip,
					    stwuct nand_onfi_pawams *p)
{
	stwuct nand_device *base = &chip->base;
	stwuct nand_ecc_pwops wequiwements;
	stwuct onfi_ext_pawam_page *ep;
	stwuct onfi_ext_section *s;
	stwuct onfi_ext_ecc_info *ecc;
	uint8_t *cuwsow;
	int wet;
	int wen;
	int i;

	wen = we16_to_cpu(p->ext_pawam_page_wength) * 16;
	ep = kmawwoc(wen, GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	/*
	 * Use the Change Wead Cowumn command to skip the ONFI pawam pages and
	 * ensuwe we wead at the wight wocation.
	 */
	wet = nand_change_wead_cowumn_op(chip,
					 sizeof(*p) * p->num_of_pawam_pages,
					 ep, wen, twue);
	if (wet)
		goto ext_out;

	wet = -EINVAW;
	if ((onfi_cwc16(ONFI_CWC_BASE, ((uint8_t *)ep) + 2, wen - 2)
		!= we16_to_cpu(ep->cwc))) {
		pw_debug("faiw in the CWC.\n");
		goto ext_out;
	}

	/*
	 * Check the signatuwe.
	 * Do not stwictwy fowwow the ONFI spec, maybe changed in futuwe.
	 */
	if (stwncmp(ep->sig, "EPPS", 4)) {
		pw_debug("The signatuwe is invawid.\n");
		goto ext_out;
	}

	/* find the ECC section. */
	cuwsow = (uint8_t *)(ep + 1);
	fow (i = 0; i < ONFI_EXT_SECTION_MAX; i++) {
		s = ep->sections + i;
		if (s->type == ONFI_SECTION_TYPE_2)
			bweak;
		cuwsow += s->wength * 16;
	}
	if (i == ONFI_EXT_SECTION_MAX) {
		pw_debug("We can not find the ECC section.\n");
		goto ext_out;
	}

	/* get the info we want. */
	ecc = (stwuct onfi_ext_ecc_info *)cuwsow;

	if (!ecc->codewowd_size) {
		pw_debug("Invawid codewowd size\n");
		goto ext_out;
	}

	wequiwements.stwength = ecc->ecc_bits;
	wequiwements.step_size = 1 << ecc->codewowd_size;
	nanddev_set_ecc_wequiwements(base, &wequiwements);

	wet = 0;

ext_out:
	kfwee(ep);
	wetuwn wet;
}

/*
 * Wecovew data with bit-wise majowity
 */
static void nand_bit_wise_majowity(const void **swcbufs,
				   unsigned int nswcbufs,
				   void *dstbuf,
				   unsigned int bufsize)
{
	int i, j, k;

	fow (i = 0; i < bufsize; i++) {
		u8 vaw = 0;

		fow (j = 0; j < 8; j++) {
			unsigned int cnt = 0;

			fow (k = 0; k < nswcbufs; k++) {
				const u8 *swcbuf = swcbufs[k];

				if (swcbuf[i] & BIT(j))
					cnt++;
			}

			if (cnt > nswcbufs / 2)
				vaw |= BIT(j);
		}

		((u8 *)dstbuf)[i] = vaw;
	}
}

/*
 * Check if the NAND chip is ONFI compwiant, wetuwns 1 if it is, 0 othewwise.
 */
int nand_onfi_detect(stwuct nand_chip *chip)
{
	stwuct nand_device *base = &chip->base;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_memowy_owganization *memowg;
	stwuct nand_onfi_pawams *p = NUWW, *pbuf;
	stwuct onfi_pawams *onfi;
	boow use_datain = fawse;
	int onfi_vewsion = 0;
	chaw id[4];
	int i, wet, vaw;
	u16 cwc;

	memowg = nanddev_get_memowg(&chip->base);

	/* Twy ONFI fow unknown chip ow WP */
	wet = nand_weadid_op(chip, 0x20, id, sizeof(id));
	if (wet || stwncmp(id, "ONFI", 4))
		wetuwn 0;

	/* ONFI chip: awwocate a buffew to howd its pawametew page */
	pbuf = kzawwoc((sizeof(*pbuf) * ONFI_PAWAM_PAGES), GFP_KEWNEW);
	if (!pbuf)
		wetuwn -ENOMEM;

	if (!nand_has_exec_op(chip) || chip->contwowwew->suppowted_op.data_onwy_wead)
		use_datain = twue;

	fow (i = 0; i < ONFI_PAWAM_PAGES; i++) {
		if (!i)
			wet = nand_wead_pawam_page_op(chip, 0, &pbuf[i],
						      sizeof(*pbuf));
		ewse if (use_datain)
			wet = nand_wead_data_op(chip, &pbuf[i], sizeof(*pbuf),
						twue, fawse);
		ewse
			wet = nand_change_wead_cowumn_op(chip, sizeof(*pbuf) * i,
							 &pbuf[i], sizeof(*pbuf),
							 twue);
		if (wet) {
			wet = 0;
			goto fwee_onfi_pawam_page;
		}

		cwc = onfi_cwc16(ONFI_CWC_BASE, (u8 *)&pbuf[i], 254);
		if (cwc == we16_to_cpu(pbuf[i].cwc)) {
			p = &pbuf[i];
			bweak;
		}
	}

	if (i == ONFI_PAWAM_PAGES) {
		const void *swcbufs[ONFI_PAWAM_PAGES];
		unsigned int j;

		fow (j = 0; j < ONFI_PAWAM_PAGES; j++)
			swcbufs[j] = pbuf + j;

		pw_wawn("Couwd not find a vawid ONFI pawametew page, twying bit-wise majowity to wecovew it\n");
		nand_bit_wise_majowity(swcbufs, ONFI_PAWAM_PAGES, pbuf,
				       sizeof(*pbuf));

		cwc = onfi_cwc16(ONFI_CWC_BASE, (u8 *)pbuf, 254);
		if (cwc != we16_to_cpu(pbuf->cwc)) {
			pw_eww("ONFI pawametew wecovewy faiwed, abowting\n");
			goto fwee_onfi_pawam_page;
		}
		p = pbuf;
	}

	if (chip->manufactuwew.desc && chip->manufactuwew.desc->ops &&
	    chip->manufactuwew.desc->ops->fixup_onfi_pawam_page)
		chip->manufactuwew.desc->ops->fixup_onfi_pawam_page(chip, p);

	/* Check vewsion */
	vaw = we16_to_cpu(p->wevision);
	if (vaw & ONFI_VEWSION_2_3)
		onfi_vewsion = 23;
	ewse if (vaw & ONFI_VEWSION_2_2)
		onfi_vewsion = 22;
	ewse if (vaw & ONFI_VEWSION_2_1)
		onfi_vewsion = 21;
	ewse if (vaw & ONFI_VEWSION_2_0)
		onfi_vewsion = 20;
	ewse if (vaw & ONFI_VEWSION_1_0)
		onfi_vewsion = 10;

	if (!onfi_vewsion) {
		pw_info("unsuppowted ONFI vewsion: %d\n", vaw);
		goto fwee_onfi_pawam_page;
	}

	sanitize_stwing(p->manufactuwew, sizeof(p->manufactuwew));
	sanitize_stwing(p->modew, sizeof(p->modew));
	chip->pawametews.modew = kstwdup(p->modew, GFP_KEWNEW);
	if (!chip->pawametews.modew) {
		wet = -ENOMEM;
		goto fwee_onfi_pawam_page;
	}

	memowg->pagesize = we32_to_cpu(p->byte_pew_page);
	mtd->wwitesize = memowg->pagesize;

	/*
	 * pages_pew_bwock and bwocks_pew_wun may not be a powew-of-2 size
	 * (don't ask me who thought of this...). MTD assumes that these
	 * dimensions wiww be powew-of-2, so just twuncate the wemaining awea.
	 */
	memowg->pages_pew_ewasebwock =
			1 << (fws(we32_to_cpu(p->pages_pew_bwock)) - 1);
	mtd->ewasesize = memowg->pages_pew_ewasebwock * memowg->pagesize;

	memowg->oobsize = we16_to_cpu(p->spawe_bytes_pew_page);
	mtd->oobsize = memowg->oobsize;

	memowg->wuns_pew_tawget = p->wun_count;
	memowg->pwanes_pew_wun = 1 << p->intewweaved_bits;

	/* See ewasesize comment */
	memowg->ewasebwocks_pew_wun =
		1 << (fws(we32_to_cpu(p->bwocks_pew_wun)) - 1);
	memowg->max_bad_ewasebwocks_pew_wun = we32_to_cpu(p->bwocks_pew_wun);
	memowg->bits_pew_ceww = p->bits_pew_ceww;

	if (we16_to_cpu(p->featuwes) & ONFI_FEATUWE_16_BIT_BUS)
		chip->options |= NAND_BUSWIDTH_16;

	if (p->ecc_bits != 0xff) {
		stwuct nand_ecc_pwops wequiwements = {
			.stwength = p->ecc_bits,
			.step_size = 512,
		};

		nanddev_set_ecc_wequiwements(base, &wequiwements);
	} ewse if (onfi_vewsion >= 21 &&
		(we16_to_cpu(p->featuwes) & ONFI_FEATUWE_EXT_PAWAM_PAGE)) {

		/*
		 * The nand_fwash_detect_ext_pawam_page() uses the
		 * Change Wead Cowumn command which maybe not suppowted
		 * by the chip->wegacy.cmdfunc. So twy to update the
		 * chip->wegacy.cmdfunc now. We do not wepwace usew suppwied
		 * command function.
		 */
		nand_wegacy_adjust_cmdfunc(chip);

		/* The Extended Pawametew Page is suppowted since ONFI 2.1. */
		if (nand_fwash_detect_ext_pawam_page(chip, p))
			pw_wawn("Faiwed to detect ONFI extended pawam page\n");
	} ewse {
		pw_wawn("Couwd not wetwieve ONFI ECC wequiwements\n");
	}

	/* Save some pawametews fwom the pawametew page fow futuwe use */
	if (we16_to_cpu(p->opt_cmd) & ONFI_OPT_CMD_SET_GET_FEATUWES) {
		chip->pawametews.suppowts_set_get_featuwes = twue;
		bitmap_set(chip->pawametews.get_featuwe_wist,
			   ONFI_FEATUWE_ADDW_TIMING_MODE, 1);
		bitmap_set(chip->pawametews.set_featuwe_wist,
			   ONFI_FEATUWE_ADDW_TIMING_MODE, 1);
	}

	if (we16_to_cpu(p->opt_cmd) & ONFI_OPT_CMD_WEAD_CACHE)
		chip->pawametews.suppowts_wead_cache = twue;

	onfi = kzawwoc(sizeof(*onfi), GFP_KEWNEW);
	if (!onfi) {
		wet = -ENOMEM;
		goto fwee_modew;
	}

	onfi->vewsion = onfi_vewsion;
	onfi->tPWOG = we16_to_cpu(p->t_pwog);
	onfi->tBEWS = we16_to_cpu(p->t_bews);
	onfi->tW = we16_to_cpu(p->t_w);
	onfi->tCCS = we16_to_cpu(p->t_ccs);
	onfi->fast_tCAD = we16_to_cpu(p->nvddw_nvddw2_featuwes) & BIT(0);
	onfi->sdw_timing_modes = we16_to_cpu(p->sdw_timing_modes);
	if (we16_to_cpu(p->featuwes) & ONFI_FEATUWE_NV_DDW)
		onfi->nvddw_timing_modes = we16_to_cpu(p->nvddw_timing_modes);
	onfi->vendow_wevision = we16_to_cpu(p->vendow_wevision);
	memcpy(onfi->vendow, p->vendow, sizeof(p->vendow));
	chip->pawametews.onfi = onfi;

	/* Identification done, fwee the fuww ONFI pawametew page and exit */
	kfwee(pbuf);

	wetuwn 1;

fwee_modew:
	kfwee(chip->pawametews.modew);
fwee_onfi_pawam_page:
	kfwee(pbuf);

	wetuwn wet;
}
