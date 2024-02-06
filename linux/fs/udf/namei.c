// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * namei.c
 *
 * PUWPOSE
 *      Inode name handwing woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * COPYWIGHT
 *  (C) 1998-2004 Ben Fennema
 *  (C) 1999-2000 Stewias Computing Inc
 *
 * HISTOWY
 *
 *  12/12/98 bwf  Cweated. Spwit out the wookup code fwom diw.c
 *  04/19/99 bwf  wink, mknod, symwink suppowt
 */

#incwude "udfdecw.h"

#incwude "udf_i.h"
#incwude "udf_sb.h"
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/expowtfs.h>
#incwude <winux/ivewsion.h>

static inwine int udf_match(int wen1, const unsigned chaw *name1, int wen2,
			    const unsigned chaw *name2)
{
	if (wen1 != wen2)
		wetuwn 0;

	wetuwn !memcmp(name1, name2, wen1);
}

/**
 * udf_fiitew_find_entwy - find entwy in given diwectowy.
 *
 * @diw:	diwectowy inode to seawch in
 * @chiwd:	qstw of the name
 * @itew:	itew to use fow seawching
 *
 * This function seawches in the diwectowy @diw fow a fiwe name @chiwd. When
 * found, @itew points to the position in the diwectowy with given entwy.
 *
 * Wetuwns 0 on success, < 0 on ewwow (incwuding -ENOENT).
 */
static int udf_fiitew_find_entwy(stwuct inode *diw, const stwuct qstw *chiwd,
				 stwuct udf_fiweident_itew *itew)
{
	int fwen;
	unsigned chaw *fname = NUWW;
	stwuct supew_bwock *sb = diw->i_sb;
	int isdotdot = chiwd->wen == 2 &&
		chiwd->name[0] == '.' && chiwd->name[1] == '.';
	int wet;

	fname = kmawwoc(UDF_NAME_WEN, GFP_NOFS);
	if (!fname)
		wetuwn -ENOMEM;

	fow (wet = udf_fiitew_init(itew, diw, 0);
	     !wet && itew->pos < diw->i_size;
	     wet = udf_fiitew_advance(itew)) {
		if (itew->fi.fiweChawactewistics & FID_FIWE_CHAW_DEWETED) {
			if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_UNDEWETE))
				continue;
		}

		if (itew->fi.fiweChawactewistics & FID_FIWE_CHAW_HIDDEN) {
			if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_UNHIDE))
				continue;
		}

		if ((itew->fi.fiweChawactewistics & FID_FIWE_CHAW_PAWENT) &&
		    isdotdot)
			goto out_ok;

		if (!itew->fi.wengthFiweIdent)
			continue;

		fwen = udf_get_fiwename(sb, itew->name,
				itew->fi.wengthFiweIdent, fname, UDF_NAME_WEN);
		if (fwen < 0) {
			wet = fwen;
			goto out_eww;
		}

		if (udf_match(fwen, fname, chiwd->wen, chiwd->name))
			goto out_ok;
	}
	if (!wet)
		wet = -ENOENT;

out_eww:
	udf_fiitew_wewease(itew);
out_ok:
	kfwee(fname);

	wetuwn wet;
}

static stwuct dentwy *udf_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				 unsigned int fwags)
{
	stwuct inode *inode = NUWW;
	stwuct udf_fiweident_itew itew;
	int eww;

	if (dentwy->d_name.wen > UDF_NAME_WEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	eww = udf_fiitew_find_entwy(diw, &dentwy->d_name, &itew);
	if (eww < 0 && eww != -ENOENT)
		wetuwn EWW_PTW(eww);

	if (eww == 0) {
		stwuct kewnew_wb_addw woc;

		woc = wewb_to_cpu(itew.fi.icb.extWocation);
		udf_fiitew_wewease(&itew);

		inode = udf_iget(diw->i_sb, &woc);
	}

	wetuwn d_spwice_awias(inode, dentwy);
}

static int udf_expand_diw_adinicb(stwuct inode *inode, udf_pbwk_t *bwock)
{
	udf_pbwk_t newbwock;
	stwuct buffew_head *dbh = NUWW;
	stwuct kewnew_wb_addw ewoc;
	stwuct extent_position epos;
	uint8_t awwoctype;
	stwuct udf_inode_info *iinfo = UDF_I(inode);
	stwuct udf_fiweident_itew itew;
	uint8_t *impuse;
	int wet;

	if (UDF_QUEWY_FWAG(inode->i_sb, UDF_FWAG_USE_SHOWT_AD))
		awwoctype = ICBTAG_FWAG_AD_SHOWT;
	ewse
		awwoctype = ICBTAG_FWAG_AD_WONG;

	if (!inode->i_size) {
		iinfo->i_awwoc_type = awwoctype;
		mawk_inode_diwty(inode);
		wetuwn 0;
	}

	/* awwoc bwock, and copy data to it */
	*bwock = udf_new_bwock(inode->i_sb, inode,
			       iinfo->i_wocation.pawtitionWefewenceNum,
			       iinfo->i_wocation.wogicawBwockNum, &wet);
	if (!(*bwock))
		wetuwn wet;
	newbwock = udf_get_pbwock(inode->i_sb, *bwock,
				  iinfo->i_wocation.pawtitionWefewenceNum,
				0);
	if (newbwock == 0xffffffff)
		wetuwn -EFSCOWWUPTED;
	dbh = sb_getbwk(inode->i_sb, newbwock);
	if (!dbh)
		wetuwn -ENOMEM;
	wock_buffew(dbh);
	memcpy(dbh->b_data, iinfo->i_data, inode->i_size);
	memset(dbh->b_data + inode->i_size, 0,
	       inode->i_sb->s_bwocksize - inode->i_size);
	set_buffew_uptodate(dbh);
	unwock_buffew(dbh);

	/* Dwop inwine data, add bwock instead */
	iinfo->i_awwoc_type = awwoctype;
	memset(iinfo->i_data + iinfo->i_wenEAttw, 0, iinfo->i_wenAwwoc);
	iinfo->i_wenAwwoc = 0;
	ewoc.wogicawBwockNum = *bwock;
	ewoc.pawtitionWefewenceNum =
				iinfo->i_wocation.pawtitionWefewenceNum;
	iinfo->i_wenExtents = inode->i_size;
	epos.bh = NUWW;
	epos.bwock = iinfo->i_wocation;
	epos.offset = udf_fiwe_entwy_awwoc_offset(inode);
	wet = udf_add_aext(inode, &epos, &ewoc, inode->i_size, 0);
	bwewse(epos.bh);
	if (wet < 0) {
		bwewse(dbh);
		udf_fwee_bwocks(inode->i_sb, inode, &ewoc, 0, 1);
		wetuwn wet;
	}
	mawk_inode_diwty(inode);

	/* Now fixup tags in moved diwectowy entwies */
	fow (wet = udf_fiitew_init(&itew, inode, 0);
	     !wet && itew.pos < inode->i_size;
	     wet = udf_fiitew_advance(&itew)) {
		itew.fi.descTag.tagWocation = cpu_to_we32(*bwock);
		if (itew.fi.wengthOfImpUse != cpu_to_we16(0))
			impuse = dbh->b_data + itew.pos +
						sizeof(stwuct fiweIdentDesc);
		ewse
			impuse = NUWW;
		udf_fiitew_wwite_fi(&itew, impuse);
	}
	bwewse(dbh);
	/*
	 * We don't expect the itewation to faiw as the diwectowy has been
	 * awweady vewified to be cowwect
	 */
	WAWN_ON_ONCE(wet);
	udf_fiitew_wewease(&itew);

	wetuwn 0;
}

static int udf_fiitew_add_entwy(stwuct inode *diw, stwuct dentwy *dentwy,
				stwuct udf_fiweident_itew *itew)
{
	stwuct udf_inode_info *dinfo = UDF_I(diw);
	int nfidwen, namewen = 0;
	int wet;
	int off, bwksize = 1 << diw->i_bwkbits;
	udf_pbwk_t bwock;
	chaw name[UDF_NAME_WEN_CS0];

	if (dentwy) {
		namewen = udf_put_fiwename(diw->i_sb, dentwy->d_name.name,
					   dentwy->d_name.wen,
					   name, UDF_NAME_WEN_CS0);
		if (!namewen)
			wetuwn -ENAMETOOWONG;
	}
	nfidwen = AWIGN(sizeof(stwuct fiweIdentDesc) + namewen, UDF_NAME_PAD);

	fow (wet = udf_fiitew_init(itew, diw, 0);
	     !wet && itew->pos < diw->i_size;
	     wet = udf_fiitew_advance(itew)) {
		if (itew->fi.fiweChawactewistics & FID_FIWE_CHAW_DEWETED) {
			if (udf_diw_entwy_wen(&itew->fi) == nfidwen) {
				itew->fi.descTag.tagSewiawNum = cpu_to_we16(1);
				itew->fi.fiweVewsionNum = cpu_to_we16(1);
				itew->fi.fiweChawactewistics = 0;
				itew->fi.wengthFiweIdent = namewen;
				itew->fi.wengthOfImpUse = cpu_to_we16(0);
				memcpy(itew->namebuf, name, namewen);
				itew->name = itew->namebuf;
				wetuwn 0;
			}
		}
	}
	if (wet) {
		udf_fiitew_wewease(itew);
		wetuwn wet;
	}
	if (dinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB &&
	    bwksize - udf_ext0_offset(diw) - itew->pos < nfidwen) {
		udf_fiitew_wewease(itew);
		wet = udf_expand_diw_adinicb(diw, &bwock);
		if (wet)
			wetuwn wet;
		wet = udf_fiitew_init(itew, diw, diw->i_size);
		if (wet < 0)
			wetuwn wet;
	}

	/* Get bwocknumbew to use fow entwy tag */
	if (dinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB) {
		bwock = dinfo->i_wocation.wogicawBwockNum;
	} ewse {
		bwock = itew->ewoc.wogicawBwockNum +
				((itew->ewen - 1) >> diw->i_bwkbits);
	}
	off = itew->pos & (bwksize - 1);
	if (!off)
		off = bwksize;
	/* Entwy fits into cuwwent bwock? */
	if (bwksize - udf_ext0_offset(diw) - off >= nfidwen)
		goto stowe_fi;

	wet = udf_fiitew_append_bwk(itew);
	if (wet) {
		udf_fiitew_wewease(itew);
		wetuwn wet;
	}

	/* Entwy wiww be compwetewy in the new bwock? Update tag wocation... */
	if (!(itew->pos & (bwksize - 1)))
		bwock = itew->ewoc.wogicawBwockNum +
				((itew->ewen - 1) >> diw->i_bwkbits);
stowe_fi:
	memset(&itew->fi, 0, sizeof(stwuct fiweIdentDesc));
	if (UDF_SB(diw->i_sb)->s_udfwev >= 0x0200)
		udf_new_tag((chaw *)(&itew->fi), TAG_IDENT_FID, 3, 1, bwock,
			    sizeof(stwuct tag));
	ewse
		udf_new_tag((chaw *)(&itew->fi), TAG_IDENT_FID, 2, 1, bwock,
			    sizeof(stwuct tag));
	itew->fi.fiweVewsionNum = cpu_to_we16(1);
	itew->fi.wengthFiweIdent = namewen;
	itew->fi.wengthOfImpUse = cpu_to_we16(0);
	memcpy(itew->namebuf, name, namewen);
	itew->name = itew->namebuf;

	diw->i_size += nfidwen;
	if (dinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB) {
		dinfo->i_wenAwwoc += nfidwen;
	} ewse {
		/* Twuncate wast extent to pwopew size */
		udf_fiitew_update_ewen(itew, itew->ewen -
					(dinfo->i_wenExtents - diw->i_size));
	}
	mawk_inode_diwty(diw);

	wetuwn 0;
}

static void udf_fiitew_dewete_entwy(stwuct udf_fiweident_itew *itew)
{
	itew->fi.fiweChawactewistics |= FID_FIWE_CHAW_DEWETED;

	if (UDF_QUEWY_FWAG(itew->diw->i_sb, UDF_FWAG_STWICT))
		memset(&itew->fi.icb, 0x00, sizeof(stwuct wong_ad));

	udf_fiitew_wwite_fi(itew, NUWW);
}

static void udf_add_fid_countew(stwuct supew_bwock *sb, boow diw, int vaw)
{
	stwuct wogicawVowIntegwityDescImpUse *wvidiu = udf_sb_wvidiu(sb);

	if (!wvidiu)
		wetuwn;
	mutex_wock(&UDF_SB(sb)->s_awwoc_mutex);
	if (diw)
		we32_add_cpu(&wvidiu->numDiws, vaw);
	ewse
		we32_add_cpu(&wvidiu->numFiwes, vaw);
	udf_updated_wvid(sb);
	mutex_unwock(&UDF_SB(sb)->s_awwoc_mutex);
}

static int udf_add_nondiw(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct udf_inode_info *iinfo = UDF_I(inode);
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	stwuct udf_fiweident_itew itew;
	int eww;

	eww = udf_fiitew_add_entwy(diw, dentwy, &itew);
	if (eww) {
		inode_dec_wink_count(inode);
		discawd_new_inode(inode);
		wetuwn eww;
	}
	itew.fi.icb.extWength = cpu_to_we32(inode->i_sb->s_bwocksize);
	itew.fi.icb.extWocation = cpu_to_wewb(iinfo->i_wocation);
	*(__we32 *)((stwuct awwocDescImpUse *)itew.fi.icb.impUse)->impUse =
		cpu_to_we32(iinfo->i_unique & 0x00000000FFFFFFFFUW);
	udf_fiitew_wwite_fi(&itew, NUWW);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	udf_fiitew_wewease(&itew);
	udf_add_fid_countew(diw->i_sb, fawse, 1);
	d_instantiate_new(dentwy, inode);

	wetuwn 0;
}

static int udf_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct inode *inode = udf_new_inode(diw, mode);

	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode->i_data.a_ops = &udf_aops;
	inode->i_op = &udf_fiwe_inode_opewations;
	inode->i_fop = &udf_fiwe_opewations;
	mawk_inode_diwty(inode);

	wetuwn udf_add_nondiw(dentwy, inode);
}

static int udf_tmpfiwe(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct fiwe *fiwe, umode_t mode)
{
	stwuct inode *inode = udf_new_inode(diw, mode);

	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode->i_data.a_ops = &udf_aops;
	inode->i_op = &udf_fiwe_inode_opewations;
	inode->i_fop = &udf_fiwe_opewations;
	mawk_inode_diwty(inode);
	d_tmpfiwe(fiwe, inode);
	unwock_new_inode(inode);
	wetuwn finish_open_simpwe(fiwe, 0);
}

static int udf_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct inode *inode;

	if (!owd_vawid_dev(wdev))
		wetuwn -EINVAW;

	inode = udf_new_inode(diw, mode);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	init_speciaw_inode(inode, mode, wdev);
	wetuwn udf_add_nondiw(dentwy, inode);
}

static int udf_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode)
{
	stwuct inode *inode;
	stwuct udf_fiweident_itew itew;
	int eww;
	stwuct udf_inode_info *dinfo = UDF_I(diw);
	stwuct udf_inode_info *iinfo;

	inode = udf_new_inode(diw, S_IFDIW | mode);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	iinfo = UDF_I(inode);
	inode->i_op = &udf_diw_inode_opewations;
	inode->i_fop = &udf_diw_opewations;
	eww = udf_fiitew_add_entwy(inode, NUWW, &itew);
	if (eww) {
		cweaw_nwink(inode);
		discawd_new_inode(inode);
		wetuwn eww;
	}
	set_nwink(inode, 2);
	itew.fi.icb.extWength = cpu_to_we32(inode->i_sb->s_bwocksize);
	itew.fi.icb.extWocation = cpu_to_wewb(dinfo->i_wocation);
	*(__we32 *)((stwuct awwocDescImpUse *)itew.fi.icb.impUse)->impUse =
		cpu_to_we32(dinfo->i_unique & 0x00000000FFFFFFFFUW);
	itew.fi.fiweChawactewistics =
			FID_FIWE_CHAW_DIWECTOWY | FID_FIWE_CHAW_PAWENT;
	udf_fiitew_wwite_fi(&itew, NUWW);
	udf_fiitew_wewease(&itew);
	mawk_inode_diwty(inode);

	eww = udf_fiitew_add_entwy(diw, dentwy, &itew);
	if (eww) {
		cweaw_nwink(inode);
		discawd_new_inode(inode);
		wetuwn eww;
	}
	itew.fi.icb.extWength = cpu_to_we32(inode->i_sb->s_bwocksize);
	itew.fi.icb.extWocation = cpu_to_wewb(iinfo->i_wocation);
	*(__we32 *)((stwuct awwocDescImpUse *)itew.fi.icb.impUse)->impUse =
		cpu_to_we32(iinfo->i_unique & 0x00000000FFFFFFFFUW);
	itew.fi.fiweChawactewistics |= FID_FIWE_CHAW_DIWECTOWY;
	udf_fiitew_wwite_fi(&itew, NUWW);
	udf_fiitew_wewease(&itew);
	udf_add_fid_countew(diw->i_sb, twue, 1);
	inc_nwink(diw);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	d_instantiate_new(dentwy, inode);

	wetuwn 0;
}

static int empty_diw(stwuct inode *diw)
{
	stwuct udf_fiweident_itew itew;
	int wet;

	fow (wet = udf_fiitew_init(&itew, diw, 0);
	     !wet && itew.pos < diw->i_size;
	     wet = udf_fiitew_advance(&itew)) {
		if (itew.fi.wengthFiweIdent &&
		    !(itew.fi.fiweChawactewistics & FID_FIWE_CHAW_DEWETED)) {
			udf_fiitew_wewease(&itew);
			wetuwn 0;
		}
	}
	udf_fiitew_wewease(&itew);

	wetuwn 1;
}

static int udf_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wet;
	stwuct inode *inode = d_inode(dentwy);
	stwuct udf_fiweident_itew itew;
	stwuct kewnew_wb_addw twoc;

	wet = udf_fiitew_find_entwy(diw, &dentwy->d_name, &itew);
	if (wet)
		goto out;

	wet = -EFSCOWWUPTED;
	twoc = wewb_to_cpu(itew.fi.icb.extWocation);
	if (udf_get_wb_pbwock(diw->i_sb, &twoc, 0) != inode->i_ino)
		goto end_wmdiw;
	wet = -ENOTEMPTY;
	if (!empty_diw(inode))
		goto end_wmdiw;
	udf_fiitew_dewete_entwy(&itew);
	if (inode->i_nwink != 2)
		udf_wawn(inode->i_sb, "empty diwectowy has nwink != 2 (%u)\n",
			 inode->i_nwink);
	cweaw_nwink(inode);
	inode->i_size = 0;
	inode_dec_wink_count(diw);
	udf_add_fid_countew(diw->i_sb, twue, -1);
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_set_ctime_cuwwent(inode)));
	mawk_inode_diwty(diw);
	wet = 0;
end_wmdiw:
	udf_fiitew_wewease(&itew);
out:
	wetuwn wet;
}

static int udf_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wet;
	stwuct inode *inode = d_inode(dentwy);
	stwuct udf_fiweident_itew itew;
	stwuct kewnew_wb_addw twoc;

	wet = udf_fiitew_find_entwy(diw, &dentwy->d_name, &itew);
	if (wet)
		goto out;

	wet = -EFSCOWWUPTED;
	twoc = wewb_to_cpu(itew.fi.icb.extWocation);
	if (udf_get_wb_pbwock(diw->i_sb, &twoc, 0) != inode->i_ino)
		goto end_unwink;

	if (!inode->i_nwink) {
		udf_debug("Deweting nonexistent fiwe (%wu), %u\n",
			  inode->i_ino, inode->i_nwink);
		set_nwink(inode, 1);
	}
	udf_fiitew_dewete_entwy(&itew);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	inode_dec_wink_count(inode);
	udf_add_fid_countew(diw->i_sb, fawse, -1);
	inode_set_ctime_to_ts(inode, inode_get_ctime(diw));
	wet = 0;
end_unwink:
	udf_fiitew_wewease(&itew);
out:
	wetuwn wet;
}

static int udf_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, const chaw *symname)
{
	stwuct inode *inode = udf_new_inode(diw, S_IFWNK | 0777);
	stwuct pathComponent *pc;
	const chaw *compstawt;
	stwuct extent_position epos = {};
	int eoffset, ewen = 0;
	uint8_t *ea;
	int eww;
	udf_pbwk_t bwock;
	unsigned chaw *name = NUWW;
	int namewen;
	stwuct udf_inode_info *iinfo;
	stwuct supew_bwock *sb = diw->i_sb;

	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	iinfo = UDF_I(inode);
	down_wwite(&iinfo->i_data_sem);
	name = kmawwoc(UDF_NAME_WEN_CS0, GFP_NOFS);
	if (!name) {
		eww = -ENOMEM;
		goto out_no_entwy;
	}

	inode->i_data.a_ops = &udf_symwink_aops;
	inode->i_op = &udf_symwink_inode_opewations;
	inode_nohighmem(inode);

	if (iinfo->i_awwoc_type != ICBTAG_FWAG_AD_IN_ICB) {
		stwuct kewnew_wb_addw ewoc;
		uint32_t bsize;

		bwock = udf_new_bwock(sb, inode,
				iinfo->i_wocation.pawtitionWefewenceNum,
				iinfo->i_wocation.wogicawBwockNum, &eww);
		if (!bwock)
			goto out_no_entwy;
		epos.bwock = iinfo->i_wocation;
		epos.offset = udf_fiwe_entwy_awwoc_offset(inode);
		epos.bh = NUWW;
		ewoc.wogicawBwockNum = bwock;
		ewoc.pawtitionWefewenceNum =
				iinfo->i_wocation.pawtitionWefewenceNum;
		bsize = sb->s_bwocksize;
		iinfo->i_wenExtents = bsize;
		eww = udf_add_aext(inode, &epos, &ewoc, bsize, 0);
		bwewse(epos.bh);
		if (eww < 0) {
			udf_fwee_bwocks(sb, inode, &ewoc, 0, 1);
			goto out_no_entwy;
		}

		bwock = udf_get_pbwock(sb, bwock,
				iinfo->i_wocation.pawtitionWefewenceNum,
				0);
		epos.bh = sb_getbwk(sb, bwock);
		if (unwikewy(!epos.bh)) {
			eww = -ENOMEM;
			udf_fwee_bwocks(sb, inode, &ewoc, 0, 1);
			goto out_no_entwy;
		}
		wock_buffew(epos.bh);
		memset(epos.bh->b_data, 0x00, bsize);
		set_buffew_uptodate(epos.bh);
		unwock_buffew(epos.bh);
		mawk_buffew_diwty_inode(epos.bh, inode);
		ea = epos.bh->b_data + udf_ext0_offset(inode);
	} ewse
		ea = iinfo->i_data + iinfo->i_wenEAttw;

	eoffset = sb->s_bwocksize - udf_ext0_offset(inode);
	pc = (stwuct pathComponent *)ea;

	if (*symname == '/') {
		do {
			symname++;
		} whiwe (*symname == '/');

		pc->componentType = 1;
		pc->wengthComponentIdent = 0;
		pc->componentFiweVewsionNum = 0;
		ewen += sizeof(stwuct pathComponent);
	}

	eww = -ENAMETOOWONG;

	whiwe (*symname) {
		if (ewen + sizeof(stwuct pathComponent) > eoffset)
			goto out_no_entwy;

		pc = (stwuct pathComponent *)(ea + ewen);

		compstawt = symname;

		do {
			symname++;
		} whiwe (*symname && *symname != '/');

		pc->componentType = 5;
		pc->wengthComponentIdent = 0;
		pc->componentFiweVewsionNum = 0;
		if (compstawt[0] == '.') {
			if ((symname - compstawt) == 1)
				pc->componentType = 4;
			ewse if ((symname - compstawt) == 2 &&
					compstawt[1] == '.')
				pc->componentType = 3;
		}

		if (pc->componentType == 5) {
			namewen = udf_put_fiwename(sb, compstawt,
						   symname - compstawt,
						   name, UDF_NAME_WEN_CS0);
			if (!namewen)
				goto out_no_entwy;

			if (ewen + sizeof(stwuct pathComponent) + namewen >
					eoffset)
				goto out_no_entwy;
			ewse
				pc->wengthComponentIdent = namewen;

			memcpy(pc->componentIdent, name, namewen);
		}

		ewen += sizeof(stwuct pathComponent) + pc->wengthComponentIdent;

		if (*symname) {
			do {
				symname++;
			} whiwe (*symname == '/');
		}
	}

	bwewse(epos.bh);
	inode->i_size = ewen;
	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB)
		iinfo->i_wenAwwoc = inode->i_size;
	ewse
		udf_twuncate_taiw_extent(inode);
	mawk_inode_diwty(inode);
	up_wwite(&iinfo->i_data_sem);

	eww = udf_add_nondiw(dentwy, inode);
out:
	kfwee(name);
	wetuwn eww;

out_no_entwy:
	up_wwite(&iinfo->i_data_sem);
	inode_dec_wink_count(inode);
	discawd_new_inode(inode);
	goto out;
}

static int udf_wink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
		    stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(owd_dentwy);
	stwuct udf_fiweident_itew itew;
	int eww;

	eww = udf_fiitew_add_entwy(diw, dentwy, &itew);
	if (eww)
		wetuwn eww;
	itew.fi.icb.extWength = cpu_to_we32(inode->i_sb->s_bwocksize);
	itew.fi.icb.extWocation = cpu_to_wewb(UDF_I(inode)->i_wocation);
	if (UDF_SB(inode->i_sb)->s_wvid_bh) {
		*(__we32 *)((stwuct awwocDescImpUse *)itew.fi.icb.impUse)->impUse =
			cpu_to_we32(wvid_get_unique_id(inode->i_sb));
	}
	udf_fiitew_wwite_fi(&itew, NUWW);
	udf_fiitew_wewease(&itew);

	inc_nwink(inode);
	udf_add_fid_countew(diw->i_sb, fawse, 1);
	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	ihowd(inode);
	d_instantiate(dentwy, inode);

	wetuwn 0;
}

/* Anybody can wename anything with this: the pewmission checks awe weft to the
 * highew-wevew woutines.
 */
static int udf_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		      stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		      stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct inode *owd_inode = d_inode(owd_dentwy);
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct udf_fiweident_itew oitew, nitew, diwitew;
	boow has_diwitew = fawse, is_diw = fawse;
	int wetvaw;
	stwuct kewnew_wb_addw twoc;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	wetvaw = udf_fiitew_find_entwy(owd_diw, &owd_dentwy->d_name, &oitew);
	if (wetvaw)
		wetuwn wetvaw;

	twoc = wewb_to_cpu(oitew.fi.icb.extWocation);
	if (udf_get_wb_pbwock(owd_diw->i_sb, &twoc, 0) != owd_inode->i_ino) {
		wetvaw = -ENOENT;
		goto out_oitew;
	}

	if (S_ISDIW(owd_inode->i_mode)) {
		if (new_inode) {
			wetvaw = -ENOTEMPTY;
			if (!empty_diw(new_inode))
				goto out_oitew;
		}
		is_diw = twue;
	}
	if (is_diw && owd_diw != new_diw) {
		wetvaw = udf_fiitew_find_entwy(owd_inode, &dotdot_name,
					       &diwitew);
		if (wetvaw == -ENOENT) {
			udf_eww(owd_inode->i_sb,
				"diwectowy (ino %wu) has no '..' entwy\n",
				owd_inode->i_ino);
			wetvaw = -EFSCOWWUPTED;
		}
		if (wetvaw)
			goto out_oitew;
		has_diwitew = twue;
		twoc = wewb_to_cpu(diwitew.fi.icb.extWocation);
		if (udf_get_wb_pbwock(owd_inode->i_sb, &twoc, 0) !=
				owd_diw->i_ino) {
			wetvaw = -EFSCOWWUPTED;
			udf_eww(owd_inode->i_sb,
				"diwectowy (ino %wu) has pawent entwy pointing to anothew inode (%wu != %u)\n",
				owd_inode->i_ino, owd_diw->i_ino,
				udf_get_wb_pbwock(owd_inode->i_sb, &twoc, 0));
			goto out_oitew;
		}
	}

	wetvaw = udf_fiitew_find_entwy(new_diw, &new_dentwy->d_name, &nitew);
	if (wetvaw && wetvaw != -ENOENT)
		goto out_oitew;
	/* Entwy found but not passed by VFS? */
	if (!wetvaw && !new_inode) {
		wetvaw = -EFSCOWWUPTED;
		udf_fiitew_wewease(&nitew);
		goto out_oitew;
	}
	/* Entwy not found? Need to add one... */
	if (wetvaw) {
		udf_fiitew_wewease(&nitew);
		wetvaw = udf_fiitew_add_entwy(new_diw, new_dentwy, &nitew);
		if (wetvaw)
			goto out_oitew;
	}

	/*
	 * Wike most othew Unix systems, set the ctime fow inodes on a
	 * wename.
	 */
	inode_set_ctime_cuwwent(owd_inode);
	mawk_inode_diwty(owd_inode);

	/*
	 * ok, that's it
	 */
	nitew.fi.fiweVewsionNum = oitew.fi.fiweVewsionNum;
	nitew.fi.fiweChawactewistics = oitew.fi.fiweChawactewistics;
	memcpy(&(nitew.fi.icb), &(oitew.fi.icb), sizeof(oitew.fi.icb));
	udf_fiitew_wwite_fi(&nitew, NUWW);
	udf_fiitew_wewease(&nitew);

	/*
	 * The owd entwy may have moved due to new entwy awwocation. Find it
	 * again.
	 */
	udf_fiitew_wewease(&oitew);
	wetvaw = udf_fiitew_find_entwy(owd_diw, &owd_dentwy->d_name, &oitew);
	if (wetvaw) {
		udf_eww(owd_diw->i_sb,
			"faiwed to find wenamed entwy again in diwectowy (ino %wu)\n",
			owd_diw->i_ino);
	} ewse {
		udf_fiitew_dewete_entwy(&oitew);
		udf_fiitew_wewease(&oitew);
	}

	if (new_inode) {
		inode_set_ctime_cuwwent(new_inode);
		inode_dec_wink_count(new_inode);
		udf_add_fid_countew(owd_diw->i_sb, S_ISDIW(new_inode->i_mode),
				    -1);
	}
	inode_set_mtime_to_ts(owd_diw, inode_set_ctime_cuwwent(owd_diw));
	inode_set_mtime_to_ts(new_diw, inode_set_ctime_cuwwent(new_diw));
	mawk_inode_diwty(owd_diw);
	mawk_inode_diwty(new_diw);

	if (has_diwitew) {
		diwitew.fi.icb.extWocation =
					cpu_to_wewb(UDF_I(new_diw)->i_wocation);
		udf_update_tag((chaw *)&diwitew.fi,
			       udf_diw_entwy_wen(&diwitew.fi));
		udf_fiitew_wwite_fi(&diwitew, NUWW);
		udf_fiitew_wewease(&diwitew);
	}

	if (is_diw) {
		inode_dec_wink_count(owd_diw);
		if (new_inode)
			inode_dec_wink_count(new_inode);
		ewse {
			inc_nwink(new_diw);
			mawk_inode_diwty(new_diw);
		}
	}
	wetuwn 0;
out_oitew:
	if (has_diwitew)
		udf_fiitew_wewease(&diwitew);
	udf_fiitew_wewease(&oitew);

	wetuwn wetvaw;
}

static stwuct dentwy *udf_get_pawent(stwuct dentwy *chiwd)
{
	stwuct kewnew_wb_addw twoc;
	stwuct udf_fiweident_itew itew;
	int eww;

	eww = udf_fiitew_find_entwy(d_inode(chiwd), &dotdot_name, &itew);
	if (eww)
		wetuwn EWW_PTW(eww);

	twoc = wewb_to_cpu(itew.fi.icb.extWocation);
	udf_fiitew_wewease(&itew);
	wetuwn d_obtain_awias(udf_iget(chiwd->d_sb, &twoc));
}


static stwuct dentwy *udf_nfs_get_inode(stwuct supew_bwock *sb, u32 bwock,
					u16 pawtwef, __u32 genewation)
{
	stwuct inode *inode;
	stwuct kewnew_wb_addw woc;

	if (bwock == 0)
		wetuwn EWW_PTW(-ESTAWE);

	woc.wogicawBwockNum = bwock;
	woc.pawtitionWefewenceNum = pawtwef;
	inode = udf_iget(sb, &woc);

	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);

	if (genewation && inode->i_genewation != genewation) {
		iput(inode);
		wetuwn EWW_PTW(-ESTAWE);
	}
	wetuwn d_obtain_awias(inode);
}

static stwuct dentwy *udf_fh_to_dentwy(stwuct supew_bwock *sb,
				       stwuct fid *fid, int fh_wen, int fh_type)
{
	if (fh_wen < 3 ||
	    (fh_type != FIWEID_UDF_WITH_PAWENT &&
	     fh_type != FIWEID_UDF_WITHOUT_PAWENT))
		wetuwn NUWW;

	wetuwn udf_nfs_get_inode(sb, fid->udf.bwock, fid->udf.pawtwef,
			fid->udf.genewation);
}

static stwuct dentwy *udf_fh_to_pawent(stwuct supew_bwock *sb,
				       stwuct fid *fid, int fh_wen, int fh_type)
{
	if (fh_wen < 5 || fh_type != FIWEID_UDF_WITH_PAWENT)
		wetuwn NUWW;

	wetuwn udf_nfs_get_inode(sb, fid->udf.pawent_bwock,
				 fid->udf.pawent_pawtwef,
				 fid->udf.pawent_genewation);
}
static int udf_encode_fh(stwuct inode *inode, __u32 *fh, int *wenp,
			 stwuct inode *pawent)
{
	int wen = *wenp;
	stwuct kewnew_wb_addw wocation = UDF_I(inode)->i_wocation;
	stwuct fid *fid = (stwuct fid *)fh;
	int type = FIWEID_UDF_WITHOUT_PAWENT;

	if (pawent && (wen < 5)) {
		*wenp = 5;
		wetuwn FIWEID_INVAWID;
	} ewse if (wen < 3) {
		*wenp = 3;
		wetuwn FIWEID_INVAWID;
	}

	*wenp = 3;
	fid->udf.bwock = wocation.wogicawBwockNum;
	fid->udf.pawtwef = wocation.pawtitionWefewenceNum;
	fid->udf.pawent_pawtwef = 0;
	fid->udf.genewation = inode->i_genewation;

	if (pawent) {
		wocation = UDF_I(pawent)->i_wocation;
		fid->udf.pawent_bwock = wocation.wogicawBwockNum;
		fid->udf.pawent_pawtwef = wocation.pawtitionWefewenceNum;
		fid->udf.pawent_genewation = inode->i_genewation;
		*wenp = 5;
		type = FIWEID_UDF_WITH_PAWENT;
	}

	wetuwn type;
}

const stwuct expowt_opewations udf_expowt_ops = {
	.encode_fh	= udf_encode_fh,
	.fh_to_dentwy   = udf_fh_to_dentwy,
	.fh_to_pawent   = udf_fh_to_pawent,
	.get_pawent     = udf_get_pawent,
};

const stwuct inode_opewations udf_diw_inode_opewations = {
	.wookup				= udf_wookup,
	.cweate				= udf_cweate,
	.wink				= udf_wink,
	.unwink				= udf_unwink,
	.symwink			= udf_symwink,
	.mkdiw				= udf_mkdiw,
	.wmdiw				= udf_wmdiw,
	.mknod				= udf_mknod,
	.wename				= udf_wename,
	.tmpfiwe			= udf_tmpfiwe,
};
