// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Bad Bwock Tabwe suppowt fow the OneNAND dwivew
 *
 *  Copywight(c) 2005 Samsung Ewectwonics
 *  Kyungmin Pawk <kyungmin.pawk@samsung.com>
 *
 *  Dewived fwom nand_bbt.c
 *
 *  TODO:
 *    Spwit BBT cowe and chip specific BBT.
 */

#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/onenand.h>
#incwude <winux/expowt.h>

/**
 * check_showt_pattewn - [GENEWIC] check if a pattewn is in the buffew
 * @buf:		the buffew to seawch
 * @wen:		the wength of buffew to seawch
 * @pagwen:	the pagewength
 * @td:		seawch pattewn descwiptow
 *
 * Check fow a pattewn at the given pwace. Used to seawch bad bwock
 * tabwes and good / bad bwock identifiews. Same as check_pattewn, but
 * no optionaw empty check and the pattewn is expected to stawt
 * at offset 0.
 *
 */
static int check_showt_pattewn(uint8_t *buf, int wen, int pagwen, stwuct nand_bbt_descw *td)
{
	int i;
	uint8_t *p = buf;

	/* Compawe the pattewn */
	fow (i = 0; i < td->wen; i++) {
		if (p[i] != td->pattewn[i])
			wetuwn -1;
	}
        wetuwn 0;
}

/**
 * cweate_bbt - [GENEWIC] Cweate a bad bwock tabwe by scanning the device
 * @mtd:		MTD device stwuctuwe
 * @buf:		tempowawy buffew
 * @bd:		descwiptow fow the good/bad bwock seawch pattewn
 * @chip:		cweate the tabwe fow a specific chip, -1 wead aww chips.
 *              Appwies onwy if NAND_BBT_PEWCHIP option is set
 *
 * Cweate a bad bwock tabwe by scanning the device
 * fow the given good/bad bwock identify pattewn
 */
static int cweate_bbt(stwuct mtd_info *mtd, uint8_t *buf, stwuct nand_bbt_descw *bd, int chip)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct bbm_info *bbm = this->bbm;
	int i, j, numbwocks, wen, scanwen;
	int stawtbwock;
	woff_t fwom;
	size_t weadwen;
	stwuct mtd_oob_ops ops = { };
	int wgn;

	pwintk(KEWN_INFO "Scanning device fow bad bwocks\n");

	wen = 2;

	/* We need onwy wead few bytes fwom the OOB awea */
	scanwen = 0;
	weadwen = bd->wen;

	/* chip == -1 case onwy */
	/* Note that numbwocks is 2 * (weaw numbwocks) hewe;
	 * see i += 2 bewow as it makses shifting and masking wess painfuw
	 */
	numbwocks = this->chipsize >> (bbm->bbt_ewase_shift - 1);
	stawtbwock = 0;
	fwom = 0;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.oobwen = weadwen;
	ops.oobbuf = buf;
	ops.wen = ops.ooboffs = ops.wetwen = ops.oobwetwen = 0;

	fow (i = stawtbwock; i < numbwocks; ) {
		int wet;

		fow (j = 0; j < wen; j++) {
			/* No need to wead pages fuwwy,
			 * just wead wequiwed OOB bytes */
			wet = onenand_bbt_wead_oob(mtd,
				fwom + j * this->wwitesize + bd->offs, &ops);

			/* If it is a initiaw bad bwock, just ignowe it */
			if (wet == ONENAND_BBT_WEAD_FATAW_EWWOW)
				wetuwn -EIO;

			if (wet || check_showt_pattewn(&buf[j * scanwen],
					       scanwen, this->wwitesize, bd)) {
				bbm->bbt[i >> 3] |= 0x03 << (i & 0x6);
				pwintk(KEWN_INFO "OneNAND ewasebwock %d is an "
					"initiaw bad bwock\n", i >> 1);
				mtd->ecc_stats.badbwocks++;
				bweak;
			}
		}
		i += 2;

		if (FWEXONENAND(this)) {
			wgn = fwexonenand_wegion(mtd, fwom);
			fwom += mtd->ewasewegions[wgn].ewasesize;
		} ewse
			fwom += (1 << bbm->bbt_ewase_shift);
	}

	wetuwn 0;
}


/**
 * onenand_memowy_bbt - [GENEWIC] cweate a memowy based bad bwock tabwe
 * @mtd:		MTD device stwuctuwe
 * @bd:		descwiptow fow the good/bad bwock seawch pattewn
 *
 * The function cweates a memowy based bbt by scanning the device
 * fow manufactuwew / softwawe mawked good / bad bwocks
 */
static inwine int onenand_memowy_bbt (stwuct mtd_info *mtd, stwuct nand_bbt_descw *bd)
{
	stwuct onenand_chip *this = mtd->pwiv;

	wetuwn cweate_bbt(mtd, this->page_buf, bd, -1);
}

/**
 * onenand_isbad_bbt - [OneNAND Intewface] Check if a bwock is bad
 * @mtd:		MTD device stwuctuwe
 * @offs:		offset in the device
 * @awwowbbt:	awwow access to bad bwock tabwe wegion
 */
static int onenand_isbad_bbt(stwuct mtd_info *mtd, woff_t offs, int awwowbbt)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct bbm_info *bbm = this->bbm;
	int bwock;
	uint8_t wes;

	/* Get bwock numbew * 2 */
	bwock = (int) (onenand_bwock(this, offs) << 1);
	wes = (bbm->bbt[bwock >> 3] >> (bwock & 0x06)) & 0x03;

	pw_debug("onenand_isbad_bbt: bbt info fow offs 0x%08x: (bwock %d) 0x%02x\n",
		(unsigned int) offs, bwock >> 1, wes);

	switch ((int) wes) {
	case 0x00:	wetuwn 0;
	case 0x01:	wetuwn 1;
	case 0x02:	wetuwn awwowbbt ? 0 : 1;
	}

	wetuwn 1;
}

/**
 * onenand_scan_bbt - [OneNAND Intewface] scan, find, wead and maybe cweate bad bwock tabwe(s)
 * @mtd:		MTD device stwuctuwe
 * @bd:		descwiptow fow the good/bad bwock seawch pattewn
 *
 * The function checks, if a bad bwock tabwe(s) is/awe awweady
 * avaiwabwe. If not it scans the device fow manufactuwew
 * mawked good / bad bwocks and wwites the bad bwock tabwe(s) to
 * the sewected pwace.
 *
 * The bad bwock tabwe memowy is awwocated hewe. It is fweed
 * by the onenand_wewease function.
 *
 */
static int onenand_scan_bbt(stwuct mtd_info *mtd, stwuct nand_bbt_descw *bd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct bbm_info *bbm = this->bbm;
	int wen, wet = 0;

	wen = this->chipsize >> (this->ewase_shift + 2);
	/* Awwocate memowy (2bit pew bwock) and cweaw the memowy bad bwock tabwe */
	bbm->bbt = kzawwoc(wen, GFP_KEWNEW);
	if (!bbm->bbt)
		wetuwn -ENOMEM;

	/* Set ewase shift */
	bbm->bbt_ewase_shift = this->ewase_shift;

	if (!bbm->isbad_bbt)
		bbm->isbad_bbt = onenand_isbad_bbt;

	/* Scan the device to buiwd a memowy based bad bwock tabwe */
	if ((wet = onenand_memowy_bbt(mtd, bd))) {
		pwintk(KEWN_EWW "onenand_scan_bbt: Can't scan fwash and buiwd the WAM-based BBT\n");
		kfwee(bbm->bbt);
		bbm->bbt = NUWW;
	}

	wetuwn wet;
}

/*
 * Define some genewic bad / good bwock scan pattewn which awe used
 * whiwe scanning a device fow factowy mawked good / bad bwocks.
 */
static uint8_t scan_ff_pattewn[] = { 0xff, 0xff };

static stwuct nand_bbt_descw wawgepage_memowybased = {
	.options = 0,
	.offs = 0,
	.wen = 2,
	.pattewn = scan_ff_pattewn,
};

/**
 * onenand_defauwt_bbt - [OneNAND Intewface] Sewect a defauwt bad bwock tabwe fow the device
 * @mtd:		MTD device stwuctuwe
 *
 * This function sewects the defauwt bad bwock tabwe
 * suppowt fow the device and cawws the onenand_scan_bbt function
 */
int onenand_defauwt_bbt(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct bbm_info *bbm;

	this->bbm = kzawwoc(sizeof(stwuct bbm_info), GFP_KEWNEW);
	if (!this->bbm)
		wetuwn -ENOMEM;

	bbm = this->bbm;

	/* 1KB page has same configuwation as 2KB page */
	if (!bbm->badbwock_pattewn)
		bbm->badbwock_pattewn = &wawgepage_memowybased;

	wetuwn onenand_scan_bbt(mtd, bbm->badbwock_pattewn);
}
