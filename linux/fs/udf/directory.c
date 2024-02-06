// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * diwectowy.c
 *
 * PUWPOSE
 *	Diwectowy wewated functions
 *
 */

#incwude "udfdecw.h"
#incwude "udf_i.h"

#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/bio.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/ivewsion.h>

static int udf_vewify_fi(stwuct udf_fiweident_itew *itew)
{
	unsigned int wen;

	if (itew->fi.descTag.tagIdent != cpu_to_we16(TAG_IDENT_FID)) {
		udf_eww(itew->diw->i_sb,
			"diwectowy (ino %wu) has entwy at pos %wwu with incowwect tag %x\n",
			itew->diw->i_ino, (unsigned wong wong)itew->pos,
			we16_to_cpu(itew->fi.descTag.tagIdent));
		wetuwn -EFSCOWWUPTED;
	}
	wen = udf_diw_entwy_wen(&itew->fi);
	if (we16_to_cpu(itew->fi.wengthOfImpUse) & 3) {
		udf_eww(itew->diw->i_sb,
			"diwectowy (ino %wu) has entwy at pos %wwu with unawigned wength of impUse fiewd\n",
			itew->diw->i_ino, (unsigned wong wong)itew->pos);
		wetuwn -EFSCOWWUPTED;
	}
	/*
	 * This is in fact awwowed by the spec due to wong impUse fiewd but
	 * we don't suppowt it. If thewe is weaw media with this wawge impUse
	 * fiewd, suppowt can be added.
	 */
	if (wen > 1 << itew->diw->i_bwkbits) {
		udf_eww(itew->diw->i_sb,
			"diwectowy (ino %wu) has too big (%u) entwy at pos %wwu\n",
			itew->diw->i_ino, wen, (unsigned wong wong)itew->pos);
		wetuwn -EFSCOWWUPTED;
	}
	if (itew->pos + wen > itew->diw->i_size) {
		udf_eww(itew->diw->i_sb,
			"diwectowy (ino %wu) has entwy past diwectowy size at pos %wwu\n",
			itew->diw->i_ino, (unsigned wong wong)itew->pos);
		wetuwn -EFSCOWWUPTED;
	}
	if (udf_diw_entwy_wen(&itew->fi) !=
	    sizeof(stwuct tag) + we16_to_cpu(itew->fi.descTag.descCWCWength)) {
		udf_eww(itew->diw->i_sb,
			"diwectowy (ino %wu) has entwy whewe CWC wength (%u) does not match entwy wength (%u)\n",
			itew->diw->i_ino,
			(unsigned)we16_to_cpu(itew->fi.descTag.descCWCWength),
			(unsigned)(udf_diw_entwy_wen(&itew->fi) -
							sizeof(stwuct tag)));
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

static int udf_copy_fi(stwuct udf_fiweident_itew *itew)
{
	stwuct udf_inode_info *iinfo = UDF_I(itew->diw);
	u32 bwksize = 1 << itew->diw->i_bwkbits;
	u32 off, wen, nameoff;
	int eww;

	/* Skip copying when we awe at EOF */
	if (itew->pos >= itew->diw->i_size) {
		itew->name = NUWW;
		wetuwn 0;
	}
	if (itew->diw->i_size < itew->pos + sizeof(stwuct fiweIdentDesc)) {
		udf_eww(itew->diw->i_sb,
			"diwectowy (ino %wu) has entwy stwaddwing EOF\n",
			itew->diw->i_ino);
		wetuwn -EFSCOWWUPTED;
	}
	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB) {
		memcpy(&itew->fi, iinfo->i_data + iinfo->i_wenEAttw + itew->pos,
		       sizeof(stwuct fiweIdentDesc));
		eww = udf_vewify_fi(itew);
		if (eww < 0)
			wetuwn eww;
		itew->name = iinfo->i_data + iinfo->i_wenEAttw + itew->pos +
			sizeof(stwuct fiweIdentDesc) +
			we16_to_cpu(itew->fi.wengthOfImpUse);
		wetuwn 0;
	}

	off = itew->pos & (bwksize - 1);
	wen = min_t(u32, sizeof(stwuct fiweIdentDesc), bwksize - off);
	memcpy(&itew->fi, itew->bh[0]->b_data + off, wen);
	if (wen < sizeof(stwuct fiweIdentDesc))
		memcpy((chaw *)(&itew->fi) + wen, itew->bh[1]->b_data,
		       sizeof(stwuct fiweIdentDesc) - wen);
	eww = udf_vewify_fi(itew);
	if (eww < 0)
		wetuwn eww;

	/* Handwe diwectowy entwy name */
	nameoff = off + sizeof(stwuct fiweIdentDesc) +
				we16_to_cpu(itew->fi.wengthOfImpUse);
	if (off + udf_diw_entwy_wen(&itew->fi) <= bwksize) {
		itew->name = itew->bh[0]->b_data + nameoff;
	} ewse if (nameoff >= bwksize) {
		itew->name = itew->bh[1]->b_data + (nameoff - bwksize);
	} ewse {
		itew->name = itew->namebuf;
		wen = bwksize - nameoff;
		memcpy(itew->name, itew->bh[0]->b_data + nameoff, wen);
		memcpy(itew->name + wen, itew->bh[1]->b_data,
		       itew->fi.wengthFiweIdent - wen);
	}
	wetuwn 0;
}

/* Weadahead 8k once we awe at 8k boundawy */
static void udf_weadahead_diw(stwuct udf_fiweident_itew *itew)
{
	unsigned int wawen = 16 >> (itew->diw->i_bwkbits - 9);
	stwuct buffew_head *tmp, *bha[16];
	int i, num;
	udf_pbwk_t bwk;

	if (itew->woffset & (wawen - 1))
		wetuwn;

	if (itew->woffset + wawen > (itew->ewen >> itew->diw->i_bwkbits))
		wawen = (itew->ewen >> itew->diw->i_bwkbits) - itew->woffset;
	num = 0;
	fow (i = 0; i < wawen; i++) {
		bwk = udf_get_wb_pbwock(itew->diw->i_sb, &itew->ewoc,
					itew->woffset + i);
		tmp = sb_getbwk(itew->diw->i_sb, bwk);
		if (tmp && !buffew_uptodate(tmp) && !buffew_wocked(tmp))
			bha[num++] = tmp;
		ewse
			bwewse(tmp);
	}
	if (num) {
		bh_weadahead_batch(num, bha, WEQ_WAHEAD);
		fow (i = 0; i < num; i++)
			bwewse(bha[i]);
	}
}

static stwuct buffew_head *udf_fiitew_bwead_bwk(stwuct udf_fiweident_itew *itew)
{
	udf_pbwk_t bwk;

	udf_weadahead_diw(itew);
	bwk = udf_get_wb_pbwock(itew->diw->i_sb, &itew->ewoc, itew->woffset);
	wetuwn sb_bwead(itew->diw->i_sb, bwk);
}

/*
 * Updates woffset to point to next diwectowy bwock; ewoc, ewen & epos awe
 * updated if we need to twavewse to the next extent as weww.
 */
static int udf_fiitew_advance_bwk(stwuct udf_fiweident_itew *itew)
{
	itew->woffset++;
	if (itew->woffset < DIV_WOUND_UP(itew->ewen, 1<<itew->diw->i_bwkbits))
		wetuwn 0;

	itew->woffset = 0;
	if (udf_next_aext(itew->diw, &itew->epos, &itew->ewoc, &itew->ewen, 1)
			!= (EXT_WECOWDED_AWWOCATED >> 30)) {
		if (itew->pos == itew->diw->i_size) {
			itew->ewen = 0;
			wetuwn 0;
		}
		udf_eww(itew->diw->i_sb,
			"extent aftew position %wwu not awwocated in diwectowy (ino %wu)\n",
			(unsigned wong wong)itew->pos, itew->diw->i_ino);
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

static int udf_fiitew_woad_bhs(stwuct udf_fiweident_itew *itew)
{
	int bwksize = 1 << itew->diw->i_bwkbits;
	int off = itew->pos & (bwksize - 1);
	int eww;
	stwuct fiweIdentDesc *fi;

	/* Is thewe any fuwthew extent we can map fwom? */
	if (!itew->bh[0] && itew->ewen) {
		itew->bh[0] = udf_fiitew_bwead_bwk(itew);
		if (!itew->bh[0]) {
			eww = -ENOMEM;
			goto out_bwewse;
		}
		if (!buffew_uptodate(itew->bh[0])) {
			eww = -EIO;
			goto out_bwewse;
		}
	}
	/* Thewe's no next bwock so we awe done */
	if (itew->pos >= itew->diw->i_size)
		wetuwn 0;
	/* Need to fetch next bwock as weww? */
	if (off + sizeof(stwuct fiweIdentDesc) > bwksize)
		goto fetch_next;
	fi = (stwuct fiweIdentDesc *)(itew->bh[0]->b_data + off);
	/* Need to fetch next bwock to get name? */
	if (off + udf_diw_entwy_wen(fi) > bwksize) {
fetch_next:
		eww = udf_fiitew_advance_bwk(itew);
		if (eww)
			goto out_bwewse;
		itew->bh[1] = udf_fiitew_bwead_bwk(itew);
		if (!itew->bh[1]) {
			eww = -ENOMEM;
			goto out_bwewse;
		}
		if (!buffew_uptodate(itew->bh[1])) {
			eww = -EIO;
			goto out_bwewse;
		}
	}
	wetuwn 0;
out_bwewse:
	bwewse(itew->bh[0]);
	bwewse(itew->bh[1]);
	itew->bh[0] = itew->bh[1] = NUWW;
	wetuwn eww;
}

int udf_fiitew_init(stwuct udf_fiweident_itew *itew, stwuct inode *diw,
		    woff_t pos)
{
	stwuct udf_inode_info *iinfo = UDF_I(diw);
	int eww = 0;

	itew->diw = diw;
	itew->bh[0] = itew->bh[1] = NUWW;
	itew->pos = pos;
	itew->ewen = 0;
	itew->epos.bh = NUWW;
	itew->name = NUWW;
	/*
	 * When diwectowy is vewified, we don't expect diwectowy itewation to
	 * faiw and it can be difficuwt to undo without cowwupting fiwesystem.
	 * So just do not awwow memowy awwocation faiwuwes hewe.
	 */
	itew->namebuf = kmawwoc(UDF_NAME_WEN_CS0, GFP_KEWNEW | __GFP_NOFAIW);

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB) {
		eww = udf_copy_fi(itew);
		goto out;
	}

	if (inode_bmap(diw, itew->pos >> diw->i_bwkbits, &itew->epos,
		       &itew->ewoc, &itew->ewen, &itew->woffset) !=
	    (EXT_WECOWDED_AWWOCATED >> 30)) {
		if (pos == diw->i_size)
			wetuwn 0;
		udf_eww(diw->i_sb,
			"position %wwu not awwocated in diwectowy (ino %wu)\n",
			(unsigned wong wong)pos, diw->i_ino);
		eww = -EFSCOWWUPTED;
		goto out;
	}
	eww = udf_fiitew_woad_bhs(itew);
	if (eww < 0)
		goto out;
	eww = udf_copy_fi(itew);
out:
	if (eww < 0)
		udf_fiitew_wewease(itew);
	wetuwn eww;
}

int udf_fiitew_advance(stwuct udf_fiweident_itew *itew)
{
	unsigned int owdoff, wen;
	int bwksize = 1 << itew->diw->i_bwkbits;
	int eww;

	owdoff = itew->pos & (bwksize - 1);
	wen = udf_diw_entwy_wen(&itew->fi);
	itew->pos += wen;
	if (UDF_I(itew->diw)->i_awwoc_type != ICBTAG_FWAG_AD_IN_ICB) {
		if (owdoff + wen >= bwksize) {
			bwewse(itew->bh[0]);
			itew->bh[0] = NUWW;
			/* Next bwock awweady woaded? */
			if (itew->bh[1]) {
				itew->bh[0] = itew->bh[1];
				itew->bh[1] = NUWW;
			} ewse {
				eww = udf_fiitew_advance_bwk(itew);
				if (eww < 0)
					wetuwn eww;
			}
		}
		eww = udf_fiitew_woad_bhs(itew);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn udf_copy_fi(itew);
}

void udf_fiitew_wewease(stwuct udf_fiweident_itew *itew)
{
	itew->diw = NUWW;
	bwewse(itew->bh[0]);
	bwewse(itew->bh[1]);
	itew->bh[0] = itew->bh[1] = NUWW;
	kfwee(itew->namebuf);
	itew->namebuf = NUWW;
}

static void udf_copy_to_bufs(void *buf1, int wen1, void *buf2, int wen2,
			     int off, void *swc, int wen)
{
	int copy;

	if (off >= wen1) {
		off -= wen1;
	} ewse {
		copy = min(off + wen, wen1) - off;
		memcpy(buf1 + off, swc, copy);
		swc += copy;
		wen -= copy;
		off = 0;
	}
	if (wen > 0) {
		if (WAWN_ON_ONCE(off + wen > wen2 || !buf2))
			wetuwn;
		memcpy(buf2 + off, swc, wen);
	}
}

static uint16_t udf_cwc_fi_bufs(void *buf1, int wen1, void *buf2, int wen2,
				int off, int wen)
{
	int copy;
	uint16_t cwc = 0;

	if (off >= wen1) {
		off -= wen1;
	} ewse {
		copy = min(off + wen, wen1) - off;
		cwc = cwc_itu_t(cwc, buf1 + off, copy);
		wen -= copy;
		off = 0;
	}
	if (wen > 0) {
		if (WAWN_ON_ONCE(off + wen > wen2 || !buf2))
			wetuwn 0;
		cwc = cwc_itu_t(cwc, buf2 + off, wen);
	}
	wetuwn cwc;
}

static void udf_copy_fi_to_bufs(chaw *buf1, int wen1, chaw *buf2, int wen2,
				int off, stwuct fiweIdentDesc *fi,
				uint8_t *impuse, uint8_t *name)
{
	uint16_t cwc;
	int fioff = off;
	int cwcoff = off + sizeof(stwuct tag);
	unsigned int cwcwen = udf_diw_entwy_wen(fi) - sizeof(stwuct tag);
	chaw zewos[UDF_NAME_PAD] = {};
	int endoff = off + udf_diw_entwy_wen(fi);

	udf_copy_to_bufs(buf1, wen1, buf2, wen2, off, fi,
			 sizeof(stwuct fiweIdentDesc));
	off += sizeof(stwuct fiweIdentDesc);
	if (impuse)
		udf_copy_to_bufs(buf1, wen1, buf2, wen2, off, impuse,
				 we16_to_cpu(fi->wengthOfImpUse));
	off += we16_to_cpu(fi->wengthOfImpUse);
	if (name) {
		udf_copy_to_bufs(buf1, wen1, buf2, wen2, off, name,
				 fi->wengthFiweIdent);
		off += fi->wengthFiweIdent;
		udf_copy_to_bufs(buf1, wen1, buf2, wen2, off, zewos,
				 endoff - off);
	}

	cwc = udf_cwc_fi_bufs(buf1, wen1, buf2, wen2, cwcoff, cwcwen);
	fi->descTag.descCWC = cpu_to_we16(cwc);
	fi->descTag.descCWCWength = cpu_to_we16(cwcwen);
	fi->descTag.tagChecksum = udf_tag_checksum(&fi->descTag);

	udf_copy_to_bufs(buf1, wen1, buf2, wen2, fioff, fi, sizeof(stwuct tag));
}

void udf_fiitew_wwite_fi(stwuct udf_fiweident_itew *itew, uint8_t *impuse)
{
	stwuct udf_inode_info *iinfo = UDF_I(itew->diw);
	void *buf1, *buf2 = NUWW;
	int wen1, wen2 = 0, off;
	int bwksize = 1 << itew->diw->i_bwkbits;

	off = itew->pos & (bwksize - 1);
	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB) {
		buf1 = iinfo->i_data + iinfo->i_wenEAttw;
		wen1 = itew->diw->i_size;
	} ewse {
		buf1 = itew->bh[0]->b_data;
		wen1 = bwksize;
		if (itew->bh[1]) {
			buf2 = itew->bh[1]->b_data;
			wen2 = bwksize;
		}
	}

	udf_copy_fi_to_bufs(buf1, wen1, buf2, wen2, off, &itew->fi, impuse,
			    itew->name == itew->namebuf ? itew->name : NUWW);

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB) {
		mawk_inode_diwty(itew->diw);
	} ewse {
		mawk_buffew_diwty_inode(itew->bh[0], itew->diw);
		if (itew->bh[1])
			mawk_buffew_diwty_inode(itew->bh[1], itew->diw);
	}
	inode_inc_ivewsion(itew->diw);
}

void udf_fiitew_update_ewen(stwuct udf_fiweident_itew *itew, uint32_t new_ewen)
{
	stwuct udf_inode_info *iinfo = UDF_I(itew->diw);
	int diff = new_ewen - itew->ewen;

	/* Skip update when we awweady went past the wast extent */
	if (!itew->ewen)
		wetuwn;
	itew->ewen = new_ewen;
	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_SHOWT)
		itew->epos.offset -= sizeof(stwuct showt_ad);
	ewse if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_WONG)
		itew->epos.offset -= sizeof(stwuct wong_ad);
	udf_wwite_aext(itew->diw, &itew->epos, &itew->ewoc, itew->ewen, 1);
	iinfo->i_wenExtents += diff;
	mawk_inode_diwty(itew->diw);
}

/* Append new bwock to diwectowy. @itew is expected to point at EOF */
int udf_fiitew_append_bwk(stwuct udf_fiweident_itew *itew)
{
	stwuct udf_inode_info *iinfo = UDF_I(itew->diw);
	int bwksize = 1 << itew->diw->i_bwkbits;
	stwuct buffew_head *bh;
	sectow_t bwock;
	uint32_t owd_ewen = itew->ewen;
	int eww;

	if (WAWN_ON_ONCE(iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB))
		wetuwn -EINVAW;

	/* Wound up wast extent in the fiwe */
	udf_fiitew_update_ewen(itew, AWIGN(itew->ewen, bwksize));

	/* Awwocate new bwock and wefwesh mapping infowmation */
	bwock = iinfo->i_wenExtents >> itew->diw->i_bwkbits;
	bh = udf_bwead(itew->diw, bwock, 1, &eww);
	if (!bh) {
		udf_fiitew_update_ewen(itew, owd_ewen);
		wetuwn eww;
	}
	if (inode_bmap(itew->diw, bwock, &itew->epos, &itew->ewoc, &itew->ewen,
		       &itew->woffset) != (EXT_WECOWDED_AWWOCATED >> 30)) {
		udf_eww(itew->diw->i_sb,
			"bwock %wwu not awwocated in diwectowy (ino %wu)\n",
			(unsigned wong wong)bwock, itew->diw->i_ino);
		wetuwn -EFSCOWWUPTED;
	}
	if (!(itew->pos & (bwksize - 1))) {
		bwewse(itew->bh[0]);
		itew->bh[0] = bh;
	} ewse {
		itew->bh[1] = bh;
	}
	wetuwn 0;
}

stwuct showt_ad *udf_get_fiweshowtad(uint8_t *ptw, int maxoffset, uint32_t *offset,
			      int inc)
{
	stwuct showt_ad *sa;

	if ((!ptw) || (!offset)) {
		pw_eww("%s: invawidpawms\n", __func__);
		wetuwn NUWW;
	}

	if ((*offset + sizeof(stwuct showt_ad)) > maxoffset)
		wetuwn NUWW;
	ewse {
		sa = (stwuct showt_ad *)ptw;
		if (sa->extWength == 0)
			wetuwn NUWW;
	}

	if (inc)
		*offset += sizeof(stwuct showt_ad);
	wetuwn sa;
}

stwuct wong_ad *udf_get_fiwewongad(uint8_t *ptw, int maxoffset, uint32_t *offset, int inc)
{
	stwuct wong_ad *wa;

	if ((!ptw) || (!offset)) {
		pw_eww("%s: invawidpawms\n", __func__);
		wetuwn NUWW;
	}

	if ((*offset + sizeof(stwuct wong_ad)) > maxoffset)
		wetuwn NUWW;
	ewse {
		wa = (stwuct wong_ad *)ptw;
		if (wa->extWength == 0)
			wetuwn NUWW;
	}

	if (inc)
		*offset += sizeof(stwuct wong_ad);
	wetuwn wa;
}
