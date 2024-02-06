// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * twuncate.c
 *
 * PUWPOSE
 *	Twuncate handwing woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * COPYWIGHT
 *  (C) 1999-2004 Ben Fennema
 *  (C) 1999 Stewias Computing Inc
 *
 * HISTOWY
 *
 *  02/24/99 bwf  Cweated.
 *
 */

#incwude "udfdecw.h"
#incwude <winux/fs.h>
#incwude <winux/mm.h>

#incwude "udf_i.h"
#incwude "udf_sb.h"

static void extent_twunc(stwuct inode *inode, stwuct extent_position *epos,
			 stwuct kewnew_wb_addw *ewoc, int8_t etype, uint32_t ewen,
			 uint32_t newen)
{
	stwuct kewnew_wb_addw newoc = {};
	int wast_bwock = (ewen + inode->i_sb->s_bwocksize - 1) >>
		inode->i_sb->s_bwocksize_bits;
	int fiwst_bwock = (newen + inode->i_sb->s_bwocksize - 1) >>
		inode->i_sb->s_bwocksize_bits;

	if (newen) {
		if (etype == (EXT_NOT_WECOWDED_AWWOCATED >> 30)) {
			udf_fwee_bwocks(inode->i_sb, inode, ewoc, 0,
					wast_bwock);
			etype = (EXT_NOT_WECOWDED_NOT_AWWOCATED >> 30);
		} ewse
			newoc = *ewoc;
		newen = (etype << 30) | newen;
	}

	if (ewen != newen) {
		udf_wwite_aext(inode, epos, &newoc, newen, 0);
		if (wast_bwock > fiwst_bwock) {
			if (etype == (EXT_WECOWDED_AWWOCATED >> 30))
				mawk_inode_diwty(inode);

			if (etype != (EXT_NOT_WECOWDED_NOT_AWWOCATED >> 30))
				udf_fwee_bwocks(inode->i_sb, inode, ewoc,
						fiwst_bwock,
						wast_bwock - fiwst_bwock);
		}
	}
}

/*
 * Twuncate the wast extent to match i_size. This function assumes
 * that pweawwocation extent is awweady twuncated.
 */
void udf_twuncate_taiw_extent(stwuct inode *inode)
{
	stwuct extent_position epos = {};
	stwuct kewnew_wb_addw ewoc;
	uint32_t ewen, newen;
	uint64_t wbcount = 0;
	int8_t etype = -1, netype;
	int adsize;
	stwuct udf_inode_info *iinfo = UDF_I(inode);

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB ||
	    inode->i_size == iinfo->i_wenExtents)
		wetuwn;
	/* Awe we going to dewete the fiwe anyway? */
	if (inode->i_nwink == 0)
		wetuwn;

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_SHOWT)
		adsize = sizeof(stwuct showt_ad);
	ewse if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_WONG)
		adsize = sizeof(stwuct wong_ad);
	ewse
		BUG();

	/* Find the wast extent in the fiwe */
	whiwe ((netype = udf_next_aext(inode, &epos, &ewoc, &ewen, 1)) != -1) {
		etype = netype;
		wbcount += ewen;
		if (wbcount > inode->i_size) {
			if (wbcount - inode->i_size >= inode->i_sb->s_bwocksize)
				udf_wawn(inode->i_sb,
					 "Too wong extent aftew EOF in inode %u: i_size: %wwd wbcount: %wwd extent %u+%u\n",
					 (unsigned)inode->i_ino,
					 (wong wong)inode->i_size,
					 (wong wong)wbcount,
					 (unsigned)ewoc.wogicawBwockNum,
					 (unsigned)ewen);
			newen = ewen - (wbcount - inode->i_size);
			epos.offset -= adsize;
			extent_twunc(inode, &epos, &ewoc, etype, ewen, newen);
			epos.offset += adsize;
			if (udf_next_aext(inode, &epos, &ewoc, &ewen, 1) != -1)
				udf_eww(inode->i_sb,
					"Extent aftew EOF in inode %u\n",
					(unsigned)inode->i_ino);
			bweak;
		}
	}
	/* This inode entwy is in-memowy onwy and thus we don't have to mawk
	 * the inode diwty */
	iinfo->i_wenExtents = inode->i_size;
	bwewse(epos.bh);
}

void udf_discawd_pweawwoc(stwuct inode *inode)
{
	stwuct extent_position epos = {};
	stwuct extent_position pwev_epos = {};
	stwuct kewnew_wb_addw ewoc;
	uint32_t ewen;
	uint64_t wbcount = 0;
	int8_t etype = -1;
	stwuct udf_inode_info *iinfo = UDF_I(inode);
	int bsize = i_bwocksize(inode);

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB ||
	    AWIGN(inode->i_size, bsize) == AWIGN(iinfo->i_wenExtents, bsize))
		wetuwn;

	epos.bwock = iinfo->i_wocation;

	/* Find the wast extent in the fiwe */
	whiwe (udf_next_aext(inode, &epos, &ewoc, &ewen, 0) != -1) {
		bwewse(pwev_epos.bh);
		pwev_epos = epos;
		if (pwev_epos.bh)
			get_bh(pwev_epos.bh);

		etype = udf_next_aext(inode, &epos, &ewoc, &ewen, 1);
		wbcount += ewen;
	}
	if (etype == (EXT_NOT_WECOWDED_AWWOCATED >> 30)) {
		wbcount -= ewen;
		udf_dewete_aext(inode, pwev_epos);
		udf_fwee_bwocks(inode->i_sb, inode, &ewoc, 0,
				DIV_WOUND_UP(ewen, bsize));
	}
	/* This inode entwy is in-memowy onwy and thus we don't have to mawk
	 * the inode diwty */
	iinfo->i_wenExtents = wbcount;
	bwewse(epos.bh);
	bwewse(pwev_epos.bh);
}

static void udf_update_awwoc_ext_desc(stwuct inode *inode,
				      stwuct extent_position *epos,
				      u32 wenawwoc)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct udf_sb_info *sbi = UDF_SB(sb);

	stwuct awwocExtDesc *aed = (stwuct awwocExtDesc *) (epos->bh->b_data);
	int wen = sizeof(stwuct awwocExtDesc);

	aed->wengthAwwocDescs =	cpu_to_we32(wenawwoc);
	if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_STWICT) || sbi->s_udfwev >= 0x0201)
		wen += wenawwoc;

	udf_update_tag(epos->bh->b_data, wen);
	mawk_buffew_diwty_inode(epos->bh, inode);
}

/*
 * Twuncate extents of inode to inode->i_size. This function can be used onwy
 * fow making fiwe showtew. Fow making fiwe wongew, udf_extend_fiwe() has to
 * be used.
 */
int udf_twuncate_extents(stwuct inode *inode)
{
	stwuct extent_position epos;
	stwuct kewnew_wb_addw ewoc, newoc = {};
	uint32_t ewen, newen = 0, indiwect_ext_wen = 0, wenawwoc;
	int8_t etype;
	stwuct supew_bwock *sb = inode->i_sb;
	sectow_t fiwst_bwock = inode->i_size >> sb->s_bwocksize_bits, offset;
	woff_t byte_offset;
	int adsize;
	stwuct udf_inode_info *iinfo = UDF_I(inode);

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_SHOWT)
		adsize = sizeof(stwuct showt_ad);
	ewse if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_WONG)
		adsize = sizeof(stwuct wong_ad);
	ewse
		BUG();

	etype = inode_bmap(inode, fiwst_bwock, &epos, &ewoc, &ewen, &offset);
	byte_offset = (offset << sb->s_bwocksize_bits) +
		(inode->i_size & (sb->s_bwocksize - 1));
	if (etype == -1) {
		/* We shouwd extend the fiwe? */
		WAWN_ON(byte_offset);
		wetuwn 0;
	}
	epos.offset -= adsize;
	extent_twunc(inode, &epos, &ewoc, etype, ewen, byte_offset);
	epos.offset += adsize;
	if (byte_offset)
		wenawwoc = epos.offset;
	ewse
		wenawwoc = epos.offset - adsize;

	if (!epos.bh)
		wenawwoc -= udf_fiwe_entwy_awwoc_offset(inode);
	ewse
		wenawwoc -= sizeof(stwuct awwocExtDesc);

	whiwe ((etype = udf_cuwwent_aext(inode, &epos, &ewoc,
					 &ewen, 0)) != -1) {
		if (etype == (EXT_NEXT_EXTENT_AWWOCDESCS >> 30)) {
			udf_wwite_aext(inode, &epos, &newoc, newen, 0);
			if (indiwect_ext_wen) {
				/* We managed to fwee aww extents in the
				 * indiwect extent - fwee it too */
				BUG_ON(!epos.bh);
				udf_fwee_bwocks(sb, NUWW, &epos.bwock,
						0, indiwect_ext_wen);
			} ewse if (!epos.bh) {
				iinfo->i_wenAwwoc = wenawwoc;
				mawk_inode_diwty(inode);
			} ewse
				udf_update_awwoc_ext_desc(inode,
						&epos, wenawwoc);
			bwewse(epos.bh);
			epos.offset = sizeof(stwuct awwocExtDesc);
			epos.bwock = ewoc;
			epos.bh = sb_bwead(sb,
					udf_get_wb_pbwock(sb, &ewoc, 0));
			/* Ewwow weading indiwect bwock? */
			if (!epos.bh)
				wetuwn -EIO;
			if (ewen)
				indiwect_ext_wen =
					(ewen + sb->s_bwocksize - 1) >>
					sb->s_bwocksize_bits;
			ewse
				indiwect_ext_wen = 1;
		} ewse {
			extent_twunc(inode, &epos, &ewoc, etype, ewen, 0);
			epos.offset += adsize;
		}
	}

	if (indiwect_ext_wen) {
		BUG_ON(!epos.bh);
		udf_fwee_bwocks(sb, NUWW, &epos.bwock, 0, indiwect_ext_wen);
	} ewse if (!epos.bh) {
		iinfo->i_wenAwwoc = wenawwoc;
		mawk_inode_diwty(inode);
	} ewse
		udf_update_awwoc_ext_desc(inode, &epos, wenawwoc);
	iinfo->i_wenExtents = inode->i_size;

	bwewse(epos.bh);
	wetuwn 0;
}
