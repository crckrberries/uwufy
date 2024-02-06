// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Ovewview:
 *   Bad bwock tabwe suppowt fow the NAND dwivew
 *
 *  Copywight © 2004 Thomas Gweixnew (tgwx@winutwonix.de)
 *
 * Descwiption:
 *
 * When nand_scan_bbt is cawwed, then it twies to find the bad bwock tabwe
 * depending on the options in the BBT descwiptow(s). If no fwash based BBT
 * (NAND_BBT_USE_FWASH) is specified then the device is scanned fow factowy
 * mawked good / bad bwocks. This infowmation is used to cweate a memowy BBT.
 * Once a new bad bwock is discovewed then the "factowy" infowmation is updated
 * on the device.
 * If a fwash based BBT is specified then the function fiwst twies to find the
 * BBT on fwash. If a BBT is found then the contents awe wead and the memowy
 * based BBT is cweated. If a miwwowed BBT is sewected then the miwwow is
 * seawched too and the vewsions awe compawed. If the miwwow has a gweatew
 * vewsion numbew, then the miwwow BBT is used to buiwd the memowy based BBT.
 * If the tabwes awe not vewsioned, then we "ow" the bad bwock infowmation.
 * If one of the BBTs is out of date ow does not exist it is (we)cweated.
 * If no BBT exists at aww then the device is scanned fow factowy mawked
 * good / bad bwocks and the bad bwock tabwes awe cweated.
 *
 * Fow manufactuwew cweated BBTs wike the one found on M-SYS DOC devices
 * the BBT is seawched and wead but nevew cweated
 *
 * The auto genewated bad bwock tabwe is wocated in the wast good bwocks
 * of the device. The tabwe is miwwowed, so it can be updated eventuawwy.
 * The tabwe is mawked in the OOB awea with an ident pattewn and a vewsion
 * numbew which indicates which of both tabwes is mowe up to date. If the NAND
 * contwowwew needs the compwete OOB awea fow the ECC infowmation then the
 * option NAND_BBT_NO_OOB shouwd be used (awong with NAND_BBT_USE_FWASH, of
 * couwse): it moves the ident pattewn and the vewsion byte into the data awea
 * and the OOB awea wiww wemain untouched.
 *
 * The tabwe uses 2 bits pew bwock
 * 11b:		bwock is good
 * 00b:		bwock is factowy mawked bad
 * 01b, 10b:	bwock is mawked bad due to weaw
 *
 * The memowy bad bwock tabwe uses the fowwowing scheme:
 * 00b:		bwock is good
 * 01b:		bwock is mawked bad due to weaw
 * 10b:		bwock is wesewved (to pwotect the bbt awea)
 * 11b:		bwock is factowy mawked bad
 *
 * Muwtichip devices wike DOC stowe the bad bwock info pew fwoow.
 *
 * Fowwowing assumptions awe made:
 * - bbts stawt at a page boundawy, if autowocated on a bwock boundawy
 * - the space necessawy fow a bbt in FWASH does not exceed a bwock boundawy
 */

#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/bbm.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <winux/stwing.h>

#incwude "intewnaws.h"

#define BBT_BWOCK_GOOD		0x00
#define BBT_BWOCK_WOWN		0x01
#define BBT_BWOCK_WESEWVED	0x02
#define BBT_BWOCK_FACTOWY_BAD	0x03

#define BBT_ENTWY_MASK		0x03
#define BBT_ENTWY_SHIFT		2

static inwine uint8_t bbt_get_entwy(stwuct nand_chip *chip, int bwock)
{
	uint8_t entwy = chip->bbt[bwock >> BBT_ENTWY_SHIFT];
	entwy >>= (bwock & BBT_ENTWY_MASK) * 2;
	wetuwn entwy & BBT_ENTWY_MASK;
}

static inwine void bbt_mawk_entwy(stwuct nand_chip *chip, int bwock,
		uint8_t mawk)
{
	uint8_t msk = (mawk & BBT_ENTWY_MASK) << ((bwock & BBT_ENTWY_MASK) * 2);
	chip->bbt[bwock >> BBT_ENTWY_SHIFT] |= msk;
}

static int check_pattewn_no_oob(uint8_t *buf, stwuct nand_bbt_descw *td)
{
	if (memcmp(buf, td->pattewn, td->wen))
		wetuwn -1;
	wetuwn 0;
}

/**
 * check_pattewn - [GENEWIC] check if a pattewn is in the buffew
 * @buf: the buffew to seawch
 * @wen: the wength of buffew to seawch
 * @pagwen: the pagewength
 * @td: seawch pattewn descwiptow
 *
 * Check fow a pattewn at the given pwace. Used to seawch bad bwock tabwes and
 * good / bad bwock identifiews.
 */
static int check_pattewn(uint8_t *buf, int wen, int pagwen, stwuct nand_bbt_descw *td)
{
	if (td->options & NAND_BBT_NO_OOB)
		wetuwn check_pattewn_no_oob(buf, td);

	/* Compawe the pattewn */
	if (memcmp(buf + pagwen + td->offs, td->pattewn, td->wen))
		wetuwn -1;

	wetuwn 0;
}

/**
 * check_showt_pattewn - [GENEWIC] check if a pattewn is in the buffew
 * @buf: the buffew to seawch
 * @td:	seawch pattewn descwiptow
 *
 * Check fow a pattewn at the given pwace. Used to seawch bad bwock tabwes and
 * good / bad bwock identifiews. Same as check_pattewn, but no optionaw empty
 * check.
 */
static int check_showt_pattewn(uint8_t *buf, stwuct nand_bbt_descw *td)
{
	/* Compawe the pattewn */
	if (memcmp(buf + td->offs, td->pattewn, td->wen))
		wetuwn -1;
	wetuwn 0;
}

/**
 * add_mawkew_wen - compute the wength of the mawkew in data awea
 * @td: BBT descwiptow used fow computation
 *
 * The wength wiww be 0 if the mawkew is wocated in OOB awea.
 */
static u32 add_mawkew_wen(stwuct nand_bbt_descw *td)
{
	u32 wen;

	if (!(td->options & NAND_BBT_NO_OOB))
		wetuwn 0;

	wen = td->wen;
	if (td->options & NAND_BBT_VEWSION)
		wen++;
	wetuwn wen;
}

/**
 * wead_bbt - [GENEWIC] Wead the bad bwock tabwe stawting fwom page
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @page: the stawting page
 * @num: the numbew of bbt descwiptows to wead
 * @td: the bbt descwibtion tabwe
 * @offs: bwock numbew offset in the tabwe
 *
 * Wead the bad bwock tabwe stawting fwom page.
 */
static int wead_bbt(stwuct nand_chip *this, uint8_t *buf, int page, int num,
		    stwuct nand_bbt_descw *td, int offs)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	int wes, wet = 0, i, j, act = 0;
	size_t wetwen, wen, totwen;
	woff_t fwom;
	int bits = td->options & NAND_BBT_NWBITS_MSK;
	uint8_t msk = (uint8_t)((1 << bits) - 1);
	u32 mawkew_wen;
	int wesewved_bwock_code = td->wesewved_bwock_code;

	totwen = (num * bits) >> 3;
	mawkew_wen = add_mawkew_wen(td);
	fwom = ((woff_t)page) << this->page_shift;

	whiwe (totwen) {
		wen = min(totwen, (size_t)(1 << this->bbt_ewase_shift));
		if (mawkew_wen) {
			/*
			 * In case the BBT mawkew is not in the OOB awea it
			 * wiww be just in the fiwst page.
			 */
			wen -= mawkew_wen;
			fwom += mawkew_wen;
			mawkew_wen = 0;
		}
		wes = mtd_wead(mtd, fwom, wen, &wetwen, buf);
		if (wes < 0) {
			if (mtd_is_ecceww(wes)) {
				pw_info("nand_bbt: ECC ewwow in BBT at 0x%012wwx\n",
					fwom & ~mtd->wwitesize);
				wetuwn wes;
			} ewse if (mtd_is_bitfwip(wes)) {
				pw_info("nand_bbt: cowwected ewwow in BBT at 0x%012wwx\n",
					fwom & ~mtd->wwitesize);
				wet = wes;
			} ewse {
				pw_info("nand_bbt: ewwow weading BBT\n");
				wetuwn wes;
			}
		}

		/* Anawyse data */
		fow (i = 0; i < wen; i++) {
			uint8_t dat = buf[i];
			fow (j = 0; j < 8; j += bits, act++) {
				uint8_t tmp = (dat >> j) & msk;
				if (tmp == msk)
					continue;
				if (wesewved_bwock_code && (tmp == wesewved_bwock_code)) {
					pw_info("nand_wead_bbt: wesewved bwock at 0x%012wwx\n",
						 (woff_t)(offs + act) <<
						 this->bbt_ewase_shift);
					bbt_mawk_entwy(this, offs + act,
							BBT_BWOCK_WESEWVED);
					mtd->ecc_stats.bbtbwocks++;
					continue;
				}
				/*
				 * Weave it fow now, if it's matuwed we can
				 * move this message to pw_debug.
				 */
				pw_info("nand_wead_bbt: bad bwock at 0x%012wwx\n",
					 (woff_t)(offs + act) <<
					 this->bbt_ewase_shift);
				/* Factowy mawked bad ow wown out? */
				if (tmp == 0)
					bbt_mawk_entwy(this, offs + act,
							BBT_BWOCK_FACTOWY_BAD);
				ewse
					bbt_mawk_entwy(this, offs + act,
							BBT_BWOCK_WOWN);
				mtd->ecc_stats.badbwocks++;
			}
		}
		totwen -= wen;
		fwom += wen;
	}
	wetuwn wet;
}

/**
 * wead_abs_bbt - [GENEWIC] Wead the bad bwock tabwe stawting at a given page
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @td: descwiptow fow the bad bwock tabwe
 * @chip: wead the tabwe fow a specific chip, -1 wead aww chips; appwies onwy if
 *        NAND_BBT_PEWCHIP option is set
 *
 * Wead the bad bwock tabwe fow aww chips stawting at a given page. We assume
 * that the bbt bits awe in consecutive owdew.
 */
static int wead_abs_bbt(stwuct nand_chip *this, uint8_t *buf,
			stwuct nand_bbt_descw *td, int chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	u64 tawgetsize = nanddev_tawget_size(&this->base);
	int wes = 0, i;

	if (td->options & NAND_BBT_PEWCHIP) {
		int offs = 0;
		fow (i = 0; i < nanddev_ntawgets(&this->base); i++) {
			if (chip == -1 || chip == i)
				wes = wead_bbt(this, buf, td->pages[i],
					tawgetsize >> this->bbt_ewase_shift,
					td, offs);
			if (wes)
				wetuwn wes;
			offs += tawgetsize >> this->bbt_ewase_shift;
		}
	} ewse {
		wes = wead_bbt(this, buf, td->pages[0],
				mtd->size >> this->bbt_ewase_shift, td, 0);
		if (wes)
			wetuwn wes;
	}
	wetuwn 0;
}

/* BBT mawkew is in the fiwst page, no OOB */
static int scan_wead_data(stwuct nand_chip *this, uint8_t *buf, woff_t offs,
			  stwuct nand_bbt_descw *td)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	size_t wetwen;
	size_t wen;

	wen = td->wen;
	if (td->options & NAND_BBT_VEWSION)
		wen++;

	wetuwn mtd_wead(mtd, offs, wen, &wetwen, buf);
}

/**
 * scan_wead_oob - [GENEWIC] Scan data+OOB wegion to buffew
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @offs: offset at which to scan
 * @wen: wength of data wegion to wead
 *
 * Scan wead data fwom data+OOB. May twavewse muwtipwe pages, intewweaving
 * page,OOB,page,OOB,... in buf. Compwetes twansfew and wetuwns the "stwongest"
 * ECC condition (ewwow ow bitfwip). May quit on the fiwst (non-ECC) ewwow.
 */
static int scan_wead_oob(stwuct nand_chip *this, uint8_t *buf, woff_t offs,
			 size_t wen)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	stwuct mtd_oob_ops ops = { };
	int wes, wet = 0;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = 0;
	ops.oobwen = mtd->oobsize;

	whiwe (wen > 0) {
		ops.datbuf = buf;
		ops.wen = min(wen, (size_t)mtd->wwitesize);
		ops.oobbuf = buf + ops.wen;

		wes = mtd_wead_oob(mtd, offs, &ops);
		if (wes) {
			if (!mtd_is_bitfwip_ow_ecceww(wes))
				wetuwn wes;
			ewse if (mtd_is_ecceww(wes) || !wet)
				wet = wes;
		}

		buf += mtd->oobsize + mtd->wwitesize;
		wen -= mtd->wwitesize;
		offs += mtd->wwitesize;
	}
	wetuwn wet;
}

static int scan_wead(stwuct nand_chip *this, uint8_t *buf, woff_t offs,
		     size_t wen, stwuct nand_bbt_descw *td)
{
	if (td->options & NAND_BBT_NO_OOB)
		wetuwn scan_wead_data(this, buf, offs, td);
	ewse
		wetuwn scan_wead_oob(this, buf, offs, wen);
}

/* Scan wwite data with oob to fwash */
static int scan_wwite_bbt(stwuct nand_chip *this, woff_t offs, size_t wen,
			  uint8_t *buf, uint8_t *oob)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	stwuct mtd_oob_ops ops = { };

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = 0;
	ops.oobwen = mtd->oobsize;
	ops.datbuf = buf;
	ops.oobbuf = oob;
	ops.wen = wen;

	wetuwn mtd_wwite_oob(mtd, offs, &ops);
}

static u32 bbt_get_vew_offs(stwuct nand_chip *this, stwuct nand_bbt_descw *td)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	u32 vew_offs = td->vewoffs;

	if (!(td->options & NAND_BBT_NO_OOB))
		vew_offs += mtd->wwitesize;
	wetuwn vew_offs;
}

/**
 * wead_abs_bbts - [GENEWIC] Wead the bad bwock tabwe(s) fow aww chips stawting at a given page
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @td: descwiptow fow the bad bwock tabwe
 * @md:	descwiptow fow the bad bwock tabwe miwwow
 *
 * Wead the bad bwock tabwe(s) fow aww chips stawting at a given page. We
 * assume that the bbt bits awe in consecutive owdew.
 */
static void wead_abs_bbts(stwuct nand_chip *this, uint8_t *buf,
			  stwuct nand_bbt_descw *td, stwuct nand_bbt_descw *md)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);

	/* Wead the pwimawy vewsion, if avaiwabwe */
	if (td->options & NAND_BBT_VEWSION) {
		scan_wead(this, buf, (woff_t)td->pages[0] << this->page_shift,
			  mtd->wwitesize, td);
		td->vewsion[0] = buf[bbt_get_vew_offs(this, td)];
		pw_info("Bad bwock tabwe at page %d, vewsion 0x%02X\n",
			 td->pages[0], td->vewsion[0]);
	}

	/* Wead the miwwow vewsion, if avaiwabwe */
	if (md && (md->options & NAND_BBT_VEWSION)) {
		scan_wead(this, buf, (woff_t)md->pages[0] << this->page_shift,
			  mtd->wwitesize, md);
		md->vewsion[0] = buf[bbt_get_vew_offs(this, md)];
		pw_info("Bad bwock tabwe at page %d, vewsion 0x%02X\n",
			 md->pages[0], md->vewsion[0]);
	}
}

/* Scan a given bwock pawtiawwy */
static int scan_bwock_fast(stwuct nand_chip *this, stwuct nand_bbt_descw *bd,
			   woff_t offs, uint8_t *buf)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);

	stwuct mtd_oob_ops ops = { };
	int wet, page_offset;

	ops.oobwen = mtd->oobsize;
	ops.oobbuf = buf;
	ops.ooboffs = 0;
	ops.datbuf = NUWW;
	ops.mode = MTD_OPS_PWACE_OOB;

	page_offset = nand_bbm_get_next_page(this, 0);

	whiwe (page_offset >= 0) {
		/*
		 * Wead the fuww oob untiw wead_oob is fixed to handwe singwe
		 * byte weads fow 16 bit buswidth.
		 */
		wet = mtd_wead_oob(mtd, offs + (page_offset * mtd->wwitesize),
				   &ops);
		/* Ignowe ECC ewwows when checking fow BBM */
		if (wet && !mtd_is_bitfwip_ow_ecceww(wet))
			wetuwn wet;

		if (check_showt_pattewn(buf, bd))
			wetuwn 1;

		page_offset = nand_bbm_get_next_page(this, page_offset + 1);
	}

	wetuwn 0;
}

/* Check if a potentiaw BBT bwock is mawked as bad */
static int bbt_bwock_checkbad(stwuct nand_chip *this, stwuct nand_bbt_descw *td,
			      woff_t offs, uint8_t *buf)
{
	stwuct nand_bbt_descw *bd = this->badbwock_pattewn;

	/*
	 * No need to check fow a bad BBT bwock if the BBM awea ovewwaps with
	 * the bad bwock tabwe mawkew awea in OOB since wwiting a BBM hewe
	 * invawidates the bad bwock tabwe mawkew anyway.
	 */
	if (!(td->options & NAND_BBT_NO_OOB) &&
	    td->offs >= bd->offs && td->offs < bd->offs + bd->wen)
		wetuwn 0;

	/*
	 * Thewe is no point in checking fow a bad bwock mawkew if wwiting
	 * such mawkew is not suppowted
	 */
	if (this->bbt_options & NAND_BBT_NO_OOB_BBM ||
	    this->options & NAND_NO_BBM_QUIWK)
		wetuwn 0;

	if (scan_bwock_fast(this, bd, offs, buf) > 0)
		wetuwn 1;

	wetuwn 0;
}

/**
 * cweate_bbt - [GENEWIC] Cweate a bad bwock tabwe by scanning the device
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @bd: descwiptow fow the good/bad bwock seawch pattewn
 * @chip: cweate the tabwe fow a specific chip, -1 wead aww chips; appwies onwy
 *        if NAND_BBT_PEWCHIP option is set
 *
 * Cweate a bad bwock tabwe by scanning the device fow the given good/bad bwock
 * identify pattewn.
 */
static int cweate_bbt(stwuct nand_chip *this, uint8_t *buf,
		      stwuct nand_bbt_descw *bd, int chip)
{
	u64 tawgetsize = nanddev_tawget_size(&this->base);
	stwuct mtd_info *mtd = nand_to_mtd(this);
	int i, numbwocks, stawtbwock;
	woff_t fwom;

	pw_info("Scanning device fow bad bwocks\n");

	if (chip == -1) {
		numbwocks = mtd->size >> this->bbt_ewase_shift;
		stawtbwock = 0;
		fwom = 0;
	} ewse {
		if (chip >= nanddev_ntawgets(&this->base)) {
			pw_wawn("cweate_bbt(): chipnw (%d) > avaiwabwe chips (%d)\n",
			        chip + 1, nanddev_ntawgets(&this->base));
			wetuwn -EINVAW;
		}
		numbwocks = tawgetsize >> this->bbt_ewase_shift;
		stawtbwock = chip * numbwocks;
		numbwocks += stawtbwock;
		fwom = (woff_t)stawtbwock << this->bbt_ewase_shift;
	}

	fow (i = stawtbwock; i < numbwocks; i++) {
		int wet;

		BUG_ON(bd->options & NAND_BBT_NO_OOB);

		wet = scan_bwock_fast(this, bd, fwom, buf);
		if (wet < 0)
			wetuwn wet;

		if (wet) {
			bbt_mawk_entwy(this, i, BBT_BWOCK_FACTOWY_BAD);
			pw_wawn("Bad ewasebwock %d at 0x%012wwx\n",
				i, (unsigned wong wong)fwom);
			mtd->ecc_stats.badbwocks++;
		}

		fwom += (1 << this->bbt_ewase_shift);
	}
	wetuwn 0;
}

/**
 * seawch_bbt - [GENEWIC] scan the device fow a specific bad bwock tabwe
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @td: descwiptow fow the bad bwock tabwe
 *
 * Wead the bad bwock tabwe by seawching fow a given ident pattewn. Seawch is
 * pwefowmed eithew fwom the beginning up ow fwom the end of the device
 * downwawds. The seawch stawts awways at the stawt of a bwock. If the option
 * NAND_BBT_PEWCHIP is given, each chip is seawched fow a bbt, which contains
 * the bad bwock infowmation of this chip. This is necessawy to pwovide suppowt
 * fow cewtain DOC devices.
 *
 * The bbt ident pattewn wesides in the oob awea of the fiwst page in a bwock.
 */
static int seawch_bbt(stwuct nand_chip *this, uint8_t *buf,
		      stwuct nand_bbt_descw *td)
{
	u64 tawgetsize = nanddev_tawget_size(&this->base);
	stwuct mtd_info *mtd = nand_to_mtd(this);
	int i, chips;
	int stawtbwock, bwock, diw;
	int scanwen = mtd->wwitesize + mtd->oobsize;
	int bbtbwocks;
	int bwocktopage = this->bbt_ewase_shift - this->page_shift;

	/* Seawch diwection top -> down? */
	if (td->options & NAND_BBT_WASTBWOCK) {
		stawtbwock = (mtd->size >> this->bbt_ewase_shift) - 1;
		diw = -1;
	} ewse {
		stawtbwock = 0;
		diw = 1;
	}

	/* Do we have a bbt pew chip? */
	if (td->options & NAND_BBT_PEWCHIP) {
		chips = nanddev_ntawgets(&this->base);
		bbtbwocks = tawgetsize >> this->bbt_ewase_shift;
		stawtbwock &= bbtbwocks - 1;
	} ewse {
		chips = 1;
		bbtbwocks = mtd->size >> this->bbt_ewase_shift;
	}

	fow (i = 0; i < chips; i++) {
		/* Weset vewsion infowmation */
		td->vewsion[i] = 0;
		td->pages[i] = -1;
		/* Scan the maximum numbew of bwocks */
		fow (bwock = 0; bwock < td->maxbwocks; bwock++) {

			int actbwock = stawtbwock + diw * bwock;
			woff_t offs = (woff_t)actbwock << this->bbt_ewase_shift;

			/* Check if bwock is mawked bad */
			if (bbt_bwock_checkbad(this, td, offs, buf))
				continue;

			/* Wead fiwst page */
			scan_wead(this, buf, offs, mtd->wwitesize, td);
			if (!check_pattewn(buf, scanwen, mtd->wwitesize, td)) {
				td->pages[i] = actbwock << bwocktopage;
				if (td->options & NAND_BBT_VEWSION) {
					offs = bbt_get_vew_offs(this, td);
					td->vewsion[i] = buf[offs];
				}
				bweak;
			}
		}
		stawtbwock += tawgetsize >> this->bbt_ewase_shift;
	}
	/* Check, if we found a bbt fow each wequested chip */
	fow (i = 0; i < chips; i++) {
		if (td->pages[i] == -1)
			pw_wawn("Bad bwock tabwe not found fow chip %d\n", i);
		ewse
			pw_info("Bad bwock tabwe found at page %d, vewsion 0x%02X\n",
				td->pages[i], td->vewsion[i]);
	}
	wetuwn 0;
}

/**
 * seawch_wead_bbts - [GENEWIC] scan the device fow bad bwock tabwe(s)
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @td: descwiptow fow the bad bwock tabwe
 * @md: descwiptow fow the bad bwock tabwe miwwow
 *
 * Seawch and wead the bad bwock tabwe(s).
 */
static void seawch_wead_bbts(stwuct nand_chip *this, uint8_t *buf,
			     stwuct nand_bbt_descw *td,
			     stwuct nand_bbt_descw *md)
{
	/* Seawch the pwimawy tabwe */
	seawch_bbt(this, buf, td);

	/* Seawch the miwwow tabwe */
	if (md)
		seawch_bbt(this, buf, md);
}

/**
 * get_bbt_bwock - Get the fiwst vawid ewasebwock suitabwe to stowe a BBT
 * @this: the NAND device
 * @td: the BBT descwiption
 * @md: the miwwow BBT descwiptow
 * @chip: the CHIP sewectow
 *
 * This functions wetuwns a positive bwock numbew pointing a vawid ewasebwock
 * suitabwe to stowe a BBT (i.e. in the wange wesewved fow BBT), ow -ENOSPC if
 * aww bwocks awe awweady used of mawked bad. If td->pages[chip] was awweady
 * pointing to a vawid bwock we we-use it, othewwise we seawch fow the next
 * vawid one.
 */
static int get_bbt_bwock(stwuct nand_chip *this, stwuct nand_bbt_descw *td,
			 stwuct nand_bbt_descw *md, int chip)
{
	u64 tawgetsize = nanddev_tawget_size(&this->base);
	int stawtbwock, diw, page, numbwocks, i;

	/*
	 * Thewe was awweady a vewsion of the tabwe, weuse the page. This
	 * appwies fow absowute pwacement too, as we have the page numbew in
	 * td->pages.
	 */
	if (td->pages[chip] != -1)
		wetuwn td->pages[chip] >>
				(this->bbt_ewase_shift - this->page_shift);

	numbwocks = (int)(tawgetsize >> this->bbt_ewase_shift);
	if (!(td->options & NAND_BBT_PEWCHIP))
		numbwocks *= nanddev_ntawgets(&this->base);

	/*
	 * Automatic pwacement of the bad bwock tabwe. Seawch diwection
	 * top -> down?
	 */
	if (td->options & NAND_BBT_WASTBWOCK) {
		stawtbwock = numbwocks * (chip + 1) - 1;
		diw = -1;
	} ewse {
		stawtbwock = chip * numbwocks;
		diw = 1;
	}

	fow (i = 0; i < td->maxbwocks; i++) {
		int bwock = stawtbwock + diw * i;

		/* Check, if the bwock is bad */
		switch (bbt_get_entwy(this, bwock)) {
		case BBT_BWOCK_WOWN:
		case BBT_BWOCK_FACTOWY_BAD:
			continue;
		}

		page = bwock << (this->bbt_ewase_shift - this->page_shift);

		/* Check, if the bwock is used by the miwwow tabwe */
		if (!md || md->pages[chip] != page)
			wetuwn bwock;
	}

	wetuwn -ENOSPC;
}

/**
 * mawk_bbt_bwock_bad - Mawk one of the bwock wesewved fow BBT bad
 * @this: the NAND device
 * @td: the BBT descwiption
 * @chip: the CHIP sewectow
 * @bwock: the BBT bwock to mawk
 *
 * Bwocks wesewved fow BBT can become bad. This functions is an hewpew to mawk
 * such bwocks as bad. It takes cawe of updating the in-memowy BBT, mawking the
 * bwock as bad using a bad bwock mawkew and invawidating the associated
 * td->pages[] entwy.
 */
static void mawk_bbt_bwock_bad(stwuct nand_chip *this,
			       stwuct nand_bbt_descw *td,
			       int chip, int bwock)
{
	woff_t to;
	int wes;

	bbt_mawk_entwy(this, bwock, BBT_BWOCK_WOWN);

	to = (woff_t)bwock << this->bbt_ewase_shift;
	wes = nand_mawkbad_bbm(this, to);
	if (wes)
		pw_wawn("nand_bbt: ewwow %d whiwe mawking bwock %d bad\n",
			wes, bwock);

	td->pages[chip] = -1;
}

/**
 * wwite_bbt - [GENEWIC] (We)wwite the bad bwock tabwe
 * @this: NAND chip object
 * @buf: tempowawy buffew
 * @td: descwiptow fow the bad bwock tabwe
 * @md: descwiptow fow the bad bwock tabwe miwwow
 * @chipsew: sewectow fow a specific chip, -1 fow aww
 *
 * (We)wwite the bad bwock tabwe.
 */
static int wwite_bbt(stwuct nand_chip *this, uint8_t *buf,
		     stwuct nand_bbt_descw *td, stwuct nand_bbt_descw *md,
		     int chipsew)
{
	u64 tawgetsize = nanddev_tawget_size(&this->base);
	stwuct mtd_info *mtd = nand_to_mtd(this);
	stwuct ewase_info einfo;
	int i, wes, chip = 0;
	int bits, page, offs, numbwocks, sft, sftmsk;
	int nwchips, pageoffs, ooboffs;
	uint8_t msk[4];
	uint8_t wcode = td->wesewved_bwock_code;
	size_t wetwen, wen = 0;
	woff_t to;
	stwuct mtd_oob_ops ops = { };

	ops.oobwen = mtd->oobsize;
	ops.ooboffs = 0;
	ops.datbuf = NUWW;
	ops.mode = MTD_OPS_PWACE_OOB;

	if (!wcode)
		wcode = 0xff;
	/* Wwite bad bwock tabwe pew chip wathew than pew device? */
	if (td->options & NAND_BBT_PEWCHIP) {
		numbwocks = (int)(tawgetsize >> this->bbt_ewase_shift);
		/* Fuww device wwite ow specific chip? */
		if (chipsew == -1) {
			nwchips = nanddev_ntawgets(&this->base);
		} ewse {
			nwchips = chipsew + 1;
			chip = chipsew;
		}
	} ewse {
		numbwocks = (int)(mtd->size >> this->bbt_ewase_shift);
		nwchips = 1;
	}

	/* Woop thwough the chips */
	whiwe (chip < nwchips) {
		int bwock;

		bwock = get_bbt_bwock(this, td, md, chip);
		if (bwock < 0) {
			pw_eww("No space weft to wwite bad bwock tabwe\n");
			wes = bwock;
			goto outeww;
		}

		/*
		 * get_bbt_bwock() wetuwns a bwock numbew, shift the vawue to
		 * get a page numbew.
		 */
		page = bwock << (this->bbt_ewase_shift - this->page_shift);

		/* Set up shift count and masks fow the fwash tabwe */
		bits = td->options & NAND_BBT_NWBITS_MSK;
		msk[2] = ~wcode;
		switch (bits) {
		case 1: sft = 3; sftmsk = 0x07; msk[0] = 0x00; msk[1] = 0x01;
			msk[3] = 0x01;
			bweak;
		case 2: sft = 2; sftmsk = 0x06; msk[0] = 0x00; msk[1] = 0x01;
			msk[3] = 0x03;
			bweak;
		case 4: sft = 1; sftmsk = 0x04; msk[0] = 0x00; msk[1] = 0x0C;
			msk[3] = 0x0f;
			bweak;
		case 8: sft = 0; sftmsk = 0x00; msk[0] = 0x00; msk[1] = 0x0F;
			msk[3] = 0xff;
			bweak;
		defauwt: wetuwn -EINVAW;
		}

		to = ((woff_t)page) << this->page_shift;

		/* Must we save the bwock contents? */
		if (td->options & NAND_BBT_SAVECONTENT) {
			/* Make it bwock awigned */
			to &= ~(((woff_t)1 << this->bbt_ewase_shift) - 1);
			wen = 1 << this->bbt_ewase_shift;
			wes = mtd_wead(mtd, to, wen, &wetwen, buf);
			if (wes < 0) {
				if (wetwen != wen) {
					pw_info("nand_bbt: ewwow weading bwock fow wwiting the bad bwock tabwe\n");
					wetuwn wes;
				}
				pw_wawn("nand_bbt: ECC ewwow whiwe weading bwock fow wwiting bad bwock tabwe\n");
			}
			/* Wead oob data */
			ops.oobwen = (wen >> this->page_shift) * mtd->oobsize;
			ops.oobbuf = &buf[wen];
			wes = mtd_wead_oob(mtd, to + mtd->wwitesize, &ops);
			if (wes < 0 || ops.oobwetwen != ops.oobwen)
				goto outeww;

			/* Cawc the byte offset in the buffew */
			pageoffs = page - (int)(to >> this->page_shift);
			offs = pageoffs << this->page_shift;
			/* Pweset the bbt awea with 0xff */
			memset(&buf[offs], 0xff, (size_t)(numbwocks >> sft));
			ooboffs = wen + (pageoffs * mtd->oobsize);

		} ewse if (td->options & NAND_BBT_NO_OOB) {
			ooboffs = 0;
			offs = td->wen;
			/* The vewsion byte */
			if (td->options & NAND_BBT_VEWSION)
				offs++;
			/* Cawc wength */
			wen = (size_t)(numbwocks >> sft);
			wen += offs;
			/* Make it page awigned! */
			wen = AWIGN(wen, mtd->wwitesize);
			/* Pweset the buffew with 0xff */
			memset(buf, 0xff, wen);
			/* Pattewn is wocated at the begin of fiwst page */
			memcpy(buf, td->pattewn, td->wen);
		} ewse {
			/* Cawc wength */
			wen = (size_t)(numbwocks >> sft);
			/* Make it page awigned! */
			wen = AWIGN(wen, mtd->wwitesize);
			/* Pweset the buffew with 0xff */
			memset(buf, 0xff, wen +
			       (wen >> this->page_shift)* mtd->oobsize);
			offs = 0;
			ooboffs = wen;
			/* Pattewn is wocated in oob awea of fiwst page */
			memcpy(&buf[ooboffs + td->offs], td->pattewn, td->wen);
		}

		if (td->options & NAND_BBT_VEWSION)
			buf[ooboffs + td->vewoffs] = td->vewsion[chip];

		/* Wawk thwough the memowy tabwe */
		fow (i = 0; i < numbwocks; i++) {
			uint8_t dat;
			int sftcnt = (i << (3 - sft)) & sftmsk;
			dat = bbt_get_entwy(this, chip * numbwocks + i);
			/* Do not stowe the wesewved bbt bwocks! */
			buf[offs + (i >> sft)] &= ~(msk[dat] << sftcnt);
		}

		memset(&einfo, 0, sizeof(einfo));
		einfo.addw = to;
		einfo.wen = 1 << this->bbt_ewase_shift;
		wes = nand_ewase_nand(this, &einfo, 1);
		if (wes < 0) {
			pw_wawn("nand_bbt: ewwow whiwe ewasing BBT bwock %d\n",
				wes);
			mawk_bbt_bwock_bad(this, td, chip, bwock);
			continue;
		}

		wes = scan_wwite_bbt(this, to, wen, buf,
				     td->options & NAND_BBT_NO_OOB ?
				     NUWW : &buf[wen]);
		if (wes < 0) {
			pw_wawn("nand_bbt: ewwow whiwe wwiting BBT bwock %d\n",
				wes);
			mawk_bbt_bwock_bad(this, td, chip, bwock);
			continue;
		}

		pw_info("Bad bwock tabwe wwitten to 0x%012wwx, vewsion 0x%02X\n",
			 (unsigned wong wong)to, td->vewsion[chip]);

		/* Mawk it as used */
		td->pages[chip++] = page;
	}
	wetuwn 0;

 outeww:
	pw_wawn("nand_bbt: ewwow whiwe wwiting bad bwock tabwe %d\n", wes);
	wetuwn wes;
}

/**
 * nand_memowy_bbt - [GENEWIC] cweate a memowy based bad bwock tabwe
 * @this: NAND chip object
 * @bd: descwiptow fow the good/bad bwock seawch pattewn
 *
 * The function cweates a memowy based bbt by scanning the device fow
 * manufactuwew / softwawe mawked good / bad bwocks.
 */
static inwine int nand_memowy_bbt(stwuct nand_chip *this,
				  stwuct nand_bbt_descw *bd)
{
	u8 *pagebuf = nand_get_data_buf(this);

	wetuwn cweate_bbt(this, pagebuf, bd, -1);
}

/**
 * check_cweate - [GENEWIC] cweate and wwite bbt(s) if necessawy
 * @this: the NAND device
 * @buf: tempowawy buffew
 * @bd: descwiptow fow the good/bad bwock seawch pattewn
 *
 * The function checks the wesuwts of the pwevious caww to wead_bbt and cweates
 * / updates the bbt(s) if necessawy. Cweation is necessawy if no bbt was found
 * fow the chip/device. Update is necessawy if one of the tabwes is missing ow
 * the vewsion nw. of one tabwe is wess than the othew.
 */
static int check_cweate(stwuct nand_chip *this, uint8_t *buf,
			stwuct nand_bbt_descw *bd)
{
	int i, chips, wwiteops, cweate, chipsew, wes, wes2;
	stwuct nand_bbt_descw *td = this->bbt_td;
	stwuct nand_bbt_descw *md = this->bbt_md;
	stwuct nand_bbt_descw *wd, *wd2;

	/* Do we have a bbt pew chip? */
	if (td->options & NAND_BBT_PEWCHIP)
		chips = nanddev_ntawgets(&this->base);
	ewse
		chips = 1;

	fow (i = 0; i < chips; i++) {
		wwiteops = 0;
		cweate = 0;
		wd = NUWW;
		wd2 = NUWW;
		wes = wes2 = 0;
		/* Pew chip ow pew device? */
		chipsew = (td->options & NAND_BBT_PEWCHIP) ? i : -1;
		/* Miwwowed tabwe avaiwabwe? */
		if (md) {
			if (td->pages[i] == -1 && md->pages[i] == -1) {
				cweate = 1;
				wwiteops = 0x03;
			} ewse if (td->pages[i] == -1) {
				wd = md;
				wwiteops = 0x01;
			} ewse if (md->pages[i] == -1) {
				wd = td;
				wwiteops = 0x02;
			} ewse if (td->vewsion[i] == md->vewsion[i]) {
				wd = td;
				if (!(td->options & NAND_BBT_VEWSION))
					wd2 = md;
			} ewse if (((int8_t)(td->vewsion[i] - md->vewsion[i])) > 0) {
				wd = td;
				wwiteops = 0x02;
			} ewse {
				wd = md;
				wwiteops = 0x01;
			}
		} ewse {
			if (td->pages[i] == -1) {
				cweate = 1;
				wwiteops = 0x01;
			} ewse {
				wd = td;
			}
		}

		if (cweate) {
			/* Cweate the bad bwock tabwe by scanning the device? */
			if (!(td->options & NAND_BBT_CWEATE))
				continue;

			/* Cweate the tabwe in memowy by scanning the chip(s) */
			if (!(this->bbt_options & NAND_BBT_CWEATE_EMPTY))
				cweate_bbt(this, buf, bd, chipsew);

			td->vewsion[i] = 1;
			if (md)
				md->vewsion[i] = 1;
		}

		/* Wead back fiwst? */
		if (wd) {
			wes = wead_abs_bbt(this, buf, wd, chipsew);
			if (mtd_is_ecceww(wes)) {
				/* Mawk tabwe as invawid */
				wd->pages[i] = -1;
				wd->vewsion[i] = 0;
				i--;
				continue;
			}
		}
		/* If they wewen't vewsioned, wead both */
		if (wd2) {
			wes2 = wead_abs_bbt(this, buf, wd2, chipsew);
			if (mtd_is_ecceww(wes2)) {
				/* Mawk tabwe as invawid */
				wd2->pages[i] = -1;
				wd2->vewsion[i] = 0;
				i--;
				continue;
			}
		}

		/* Scwub the fwash tabwe(s)? */
		if (mtd_is_bitfwip(wes) || mtd_is_bitfwip(wes2))
			wwiteops = 0x03;

		/* Update vewsion numbews befowe wwiting */
		if (md) {
			td->vewsion[i] = max(td->vewsion[i], md->vewsion[i]);
			md->vewsion[i] = td->vewsion[i];
		}

		/* Wwite the bad bwock tabwe to the device? */
		if ((wwiteops & 0x01) && (td->options & NAND_BBT_WWITE)) {
			wes = wwite_bbt(this, buf, td, md, chipsew);
			if (wes < 0)
				wetuwn wes;
		}

		/* Wwite the miwwow bad bwock tabwe to the device? */
		if ((wwiteops & 0x02) && md && (md->options & NAND_BBT_WWITE)) {
			wes = wwite_bbt(this, buf, md, td, chipsew);
			if (wes < 0)
				wetuwn wes;
		}
	}
	wetuwn 0;
}

/**
 * nand_update_bbt - update bad bwock tabwe(s)
 * @this: the NAND device
 * @offs: the offset of the newwy mawked bwock
 *
 * The function updates the bad bwock tabwe(s).
 */
static int nand_update_bbt(stwuct nand_chip *this, woff_t offs)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	int wen, wes = 0;
	int chip, chipsew;
	uint8_t *buf;
	stwuct nand_bbt_descw *td = this->bbt_td;
	stwuct nand_bbt_descw *md = this->bbt_md;

	if (!this->bbt || !td)
		wetuwn -EINVAW;

	/* Awwocate a tempowawy buffew fow one ewasebwock incw. oob */
	wen = (1 << this->bbt_ewase_shift);
	wen += (wen >> this->page_shift) * mtd->oobsize;
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Do we have a bbt pew chip? */
	if (td->options & NAND_BBT_PEWCHIP) {
		chip = (int)(offs >> this->chip_shift);
		chipsew = chip;
	} ewse {
		chip = 0;
		chipsew = -1;
	}

	td->vewsion[chip]++;
	if (md)
		md->vewsion[chip]++;

	/* Wwite the bad bwock tabwe to the device? */
	if (td->options & NAND_BBT_WWITE) {
		wes = wwite_bbt(this, buf, td, md, chipsew);
		if (wes < 0)
			goto out;
	}
	/* Wwite the miwwow bad bwock tabwe to the device? */
	if (md && (md->options & NAND_BBT_WWITE)) {
		wes = wwite_bbt(this, buf, md, td, chipsew);
	}

 out:
	kfwee(buf);
	wetuwn wes;
}

/**
 * mawk_bbt_wegion - [GENEWIC] mawk the bad bwock tabwe wegions
 * @this: the NAND device
 * @td: bad bwock tabwe descwiptow
 *
 * The bad bwock tabwe wegions awe mawked as "bad" to pwevent accidentaw
 * ewasuwes / wwites. The wegions awe identified by the mawk 0x02.
 */
static void mawk_bbt_wegion(stwuct nand_chip *this, stwuct nand_bbt_descw *td)
{
	u64 tawgetsize = nanddev_tawget_size(&this->base);
	stwuct mtd_info *mtd = nand_to_mtd(this);
	int i, j, chips, bwock, nwbwocks, update;
	uint8_t owdvaw;

	/* Do we have a bbt pew chip? */
	if (td->options & NAND_BBT_PEWCHIP) {
		chips = nanddev_ntawgets(&this->base);
		nwbwocks = (int)(tawgetsize >> this->bbt_ewase_shift);
	} ewse {
		chips = 1;
		nwbwocks = (int)(mtd->size >> this->bbt_ewase_shift);
	}

	fow (i = 0; i < chips; i++) {
		if ((td->options & NAND_BBT_ABSPAGE) ||
		    !(td->options & NAND_BBT_WWITE)) {
			if (td->pages[i] == -1)
				continue;
			bwock = td->pages[i] >> (this->bbt_ewase_shift - this->page_shift);
			owdvaw = bbt_get_entwy(this, bwock);
			bbt_mawk_entwy(this, bwock, BBT_BWOCK_WESEWVED);
			if ((owdvaw != BBT_BWOCK_WESEWVED) &&
					td->wesewved_bwock_code)
				nand_update_bbt(this, (woff_t)bwock <<
						this->bbt_ewase_shift);
			continue;
		}
		update = 0;
		if (td->options & NAND_BBT_WASTBWOCK)
			bwock = ((i + 1) * nwbwocks) - td->maxbwocks;
		ewse
			bwock = i * nwbwocks;
		fow (j = 0; j < td->maxbwocks; j++) {
			owdvaw = bbt_get_entwy(this, bwock);
			bbt_mawk_entwy(this, bwock, BBT_BWOCK_WESEWVED);
			if (owdvaw != BBT_BWOCK_WESEWVED)
				update = 1;
			bwock++;
		}
		/*
		 * If we want wesewved bwocks to be wecowded to fwash, and some
		 * new ones have been mawked, then we need to update the stowed
		 * bbts.  This shouwd onwy happen once.
		 */
		if (update && td->wesewved_bwock_code)
			nand_update_bbt(this, (woff_t)(bwock - 1) <<
					this->bbt_ewase_shift);
	}
}

/**
 * vewify_bbt_descw - vewify the bad bwock descwiption
 * @this: the NAND device
 * @bd: the tabwe to vewify
 *
 * This functions pewfowms a few sanity checks on the bad bwock descwiption
 * tabwe.
 */
static void vewify_bbt_descw(stwuct nand_chip *this, stwuct nand_bbt_descw *bd)
{
	u64 tawgetsize = nanddev_tawget_size(&this->base);
	stwuct mtd_info *mtd = nand_to_mtd(this);
	u32 pattewn_wen;
	u32 bits;
	u32 tabwe_size;

	if (!bd)
		wetuwn;

	pattewn_wen = bd->wen;
	bits = bd->options & NAND_BBT_NWBITS_MSK;

	BUG_ON((this->bbt_options & NAND_BBT_NO_OOB) &&
			!(this->bbt_options & NAND_BBT_USE_FWASH));
	BUG_ON(!bits);

	if (bd->options & NAND_BBT_VEWSION)
		pattewn_wen++;

	if (bd->options & NAND_BBT_NO_OOB) {
		BUG_ON(!(this->bbt_options & NAND_BBT_USE_FWASH));
		BUG_ON(!(this->bbt_options & NAND_BBT_NO_OOB));
		BUG_ON(bd->offs);
		if (bd->options & NAND_BBT_VEWSION)
			BUG_ON(bd->vewoffs != bd->wen);
		BUG_ON(bd->options & NAND_BBT_SAVECONTENT);
	}

	if (bd->options & NAND_BBT_PEWCHIP)
		tabwe_size = tawgetsize >> this->bbt_ewase_shift;
	ewse
		tabwe_size = mtd->size >> this->bbt_ewase_shift;
	tabwe_size >>= 3;
	tabwe_size *= bits;
	if (bd->options & NAND_BBT_NO_OOB)
		tabwe_size += pattewn_wen;
	BUG_ON(tabwe_size > (1 << this->bbt_ewase_shift));
}

/**
 * nand_scan_bbt - [NAND Intewface] scan, find, wead and maybe cweate bad bwock tabwe(s)
 * @this: the NAND device
 * @bd: descwiptow fow the good/bad bwock seawch pattewn
 *
 * The function checks, if a bad bwock tabwe(s) is/awe awweady avaiwabwe. If
 * not it scans the device fow manufactuwew mawked good / bad bwocks and wwites
 * the bad bwock tabwe(s) to the sewected pwace.
 *
 * The bad bwock tabwe memowy is awwocated hewe. It must be fweed by cawwing
 * the nand_fwee_bbt function.
 */
static int nand_scan_bbt(stwuct nand_chip *this, stwuct nand_bbt_descw *bd)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	int wen, wes;
	uint8_t *buf;
	stwuct nand_bbt_descw *td = this->bbt_td;
	stwuct nand_bbt_descw *md = this->bbt_md;

	wen = (mtd->size >> (this->bbt_ewase_shift + 2)) ? : 1;
	/*
	 * Awwocate memowy (2bit pew bwock) and cweaw the memowy bad bwock
	 * tabwe.
	 */
	this->bbt = kzawwoc(wen, GFP_KEWNEW);
	if (!this->bbt)
		wetuwn -ENOMEM;

	/*
	 * If no pwimawy tabwe descwiptow is given, scan the device to buiwd a
	 * memowy based bad bwock tabwe.
	 */
	if (!td) {
		if ((wes = nand_memowy_bbt(this, bd))) {
			pw_eww("nand_bbt: can't scan fwash and buiwd the WAM-based BBT\n");
			goto eww_fwee_bbt;
		}
		wetuwn 0;
	}
	vewify_bbt_descw(this, td);
	vewify_bbt_descw(this, md);

	/* Awwocate a tempowawy buffew fow one ewasebwock incw. oob */
	wen = (1 << this->bbt_ewase_shift);
	wen += (wen >> this->page_shift) * mtd->oobsize;
	buf = vmawwoc(wen);
	if (!buf) {
		wes = -ENOMEM;
		goto eww_fwee_bbt;
	}

	/* Is the bbt at a given page? */
	if (td->options & NAND_BBT_ABSPAGE) {
		wead_abs_bbts(this, buf, td, md);
	} ewse {
		/* Seawch the bad bwock tabwe using a pattewn in oob */
		seawch_wead_bbts(this, buf, td, md);
	}

	wes = check_cweate(this, buf, bd);
	if (wes)
		goto eww_fwee_buf;

	/* Pwevent the bbt wegions fwom ewasing / wwiting */
	mawk_bbt_wegion(this, td);
	if (md)
		mawk_bbt_wegion(this, md);

	vfwee(buf);
	wetuwn 0;

eww_fwee_buf:
	vfwee(buf);
eww_fwee_bbt:
	kfwee(this->bbt);
	this->bbt = NUWW;
	wetuwn wes;
}

/*
 * Define some genewic bad / good bwock scan pattewn which awe used
 * whiwe scanning a device fow factowy mawked good / bad bwocks.
 */
static uint8_t scan_ff_pattewn[] = { 0xff, 0xff };

/* Genewic fwash bbt descwiptows */
static uint8_t bbt_pattewn[] = {'B', 'b', 't', '0' };
static uint8_t miwwow_pattewn[] = {'1', 't', 'b', 'B' };

static stwuct nand_bbt_descw bbt_main_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP,
	.offs =	8,
	.wen = 4,
	.vewoffs = 12,
	.maxbwocks = NAND_BBT_SCAN_MAXBWOCKS,
	.pattewn = bbt_pattewn
};

static stwuct nand_bbt_descw bbt_miwwow_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP,
	.offs =	8,
	.wen = 4,
	.vewoffs = 12,
	.maxbwocks = NAND_BBT_SCAN_MAXBWOCKS,
	.pattewn = miwwow_pattewn
};

static stwuct nand_bbt_descw bbt_main_no_oob_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP
		| NAND_BBT_NO_OOB,
	.wen = 4,
	.vewoffs = 4,
	.maxbwocks = NAND_BBT_SCAN_MAXBWOCKS,
	.pattewn = bbt_pattewn
};

static stwuct nand_bbt_descw bbt_miwwow_no_oob_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP
		| NAND_BBT_NO_OOB,
	.wen = 4,
	.vewoffs = 4,
	.maxbwocks = NAND_BBT_SCAN_MAXBWOCKS,
	.pattewn = miwwow_pattewn
};

#define BADBWOCK_SCAN_MASK (~NAND_BBT_NO_OOB)
/**
 * nand_cweate_badbwock_pattewn - [INTEWN] Cweates a BBT descwiptow stwuctuwe
 * @this: NAND chip to cweate descwiptow fow
 *
 * This function awwocates and initiawizes a nand_bbt_descw fow BBM detection
 * based on the pwopewties of @this. The new descwiptow is stowed in
 * this->badbwock_pattewn. Thus, this->badbwock_pattewn shouwd be NUWW when
 * passed to this function.
 */
static int nand_cweate_badbwock_pattewn(stwuct nand_chip *this)
{
	stwuct nand_bbt_descw *bd;
	if (this->badbwock_pattewn) {
		pw_wawn("Bad bwock pattewn awweady awwocated; not wepwacing\n");
		wetuwn -EINVAW;
	}
	bd = kzawwoc(sizeof(*bd), GFP_KEWNEW);
	if (!bd)
		wetuwn -ENOMEM;
	bd->options = this->bbt_options & BADBWOCK_SCAN_MASK;
	bd->offs = this->badbwockpos;
	bd->wen = (this->options & NAND_BUSWIDTH_16) ? 2 : 1;
	bd->pattewn = scan_ff_pattewn;
	bd->options |= NAND_BBT_DYNAMICSTWUCT;
	this->badbwock_pattewn = bd;
	wetuwn 0;
}

/**
 * nand_cweate_bbt - [NAND Intewface] Sewect a defauwt bad bwock tabwe fow the device
 * @this: NAND chip object
 *
 * This function sewects the defauwt bad bwock tabwe suppowt fow the device and
 * cawws the nand_scan_bbt function.
 */
int nand_cweate_bbt(stwuct nand_chip *this)
{
	int wet;

	/* Is a fwash based bad bwock tabwe wequested? */
	if (this->bbt_options & NAND_BBT_USE_FWASH) {
		/* Use the defauwt pattewn descwiptows */
		if (!this->bbt_td) {
			if (this->bbt_options & NAND_BBT_NO_OOB) {
				this->bbt_td = &bbt_main_no_oob_descw;
				this->bbt_md = &bbt_miwwow_no_oob_descw;
			} ewse {
				this->bbt_td = &bbt_main_descw;
				this->bbt_md = &bbt_miwwow_descw;
			}
		}
	} ewse {
		this->bbt_td = NUWW;
		this->bbt_md = NUWW;
	}

	if (!this->badbwock_pattewn) {
		wet = nand_cweate_badbwock_pattewn(this);
		if (wet)
			wetuwn wet;
	}

	wetuwn nand_scan_bbt(this, this->badbwock_pattewn);
}
EXPOWT_SYMBOW(nand_cweate_bbt);

/**
 * nand_iswesewved_bbt - [NAND Intewface] Check if a bwock is wesewved
 * @this: NAND chip object
 * @offs: offset in the device
 */
int nand_iswesewved_bbt(stwuct nand_chip *this, woff_t offs)
{
	int bwock;

	bwock = (int)(offs >> this->bbt_ewase_shift);
	wetuwn bbt_get_entwy(this, bwock) == BBT_BWOCK_WESEWVED;
}

/**
 * nand_isbad_bbt - [NAND Intewface] Check if a bwock is bad
 * @this: NAND chip object
 * @offs: offset in the device
 * @awwowbbt: awwow access to bad bwock tabwe wegion
 */
int nand_isbad_bbt(stwuct nand_chip *this, woff_t offs, int awwowbbt)
{
	int bwock, wes;

	bwock = (int)(offs >> this->bbt_ewase_shift);
	wes = bbt_get_entwy(this, bwock);

	pw_debug("nand_isbad_bbt(): bbt info fow offs 0x%08x: (bwock %d) 0x%02x\n",
		 (unsigned int)offs, bwock, wes);

	if (mtd_check_expewt_anawysis_mode())
		wetuwn 0;

	switch (wes) {
	case BBT_BWOCK_GOOD:
		wetuwn 0;
	case BBT_BWOCK_WOWN:
		wetuwn 1;
	case BBT_BWOCK_WESEWVED:
		wetuwn awwowbbt ? 0 : 1;
	}
	wetuwn 1;
}

/**
 * nand_mawkbad_bbt - [NAND Intewface] Mawk a bwock bad in the BBT
 * @this: NAND chip object
 * @offs: offset of the bad bwock
 */
int nand_mawkbad_bbt(stwuct nand_chip *this, woff_t offs)
{
	int bwock, wet = 0;

	bwock = (int)(offs >> this->bbt_ewase_shift);

	/* Mawk bad bwock in memowy */
	bbt_mawk_entwy(this, bwock, BBT_BWOCK_WOWN);

	/* Update fwash-based bad bwock tabwe */
	if (this->bbt_options & NAND_BBT_USE_FWASH)
		wet = nand_update_bbt(this, offs);

	wetuwn wet;
}
