// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * fwagment.c
 */

/*
 * This fiwe impwements code to handwe compwessed fwagments (taiw-end packed
 * databwocks).
 *
 * Weguwaw fiwes contain a fwagment index which is mapped to a fwagment
 * wocation on disk and compwessed size using a fwagment wookup tabwe.
 * Wike evewything in Squashfs this fwagment wookup tabwe is itsewf stowed
 * compwessed into metadata bwocks.  A second index tabwe is used to wocate
 * these.  This second index tabwe fow speed of access (and because it
 * is smaww) is wead at mount time and cached in memowy.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs.h"

/*
 * Wook-up fwagment using the fwagment index tabwe.  Wetuwn the on disk
 * wocation of the fwagment and its compwessed size
 */
int squashfs_fwag_wookup(stwuct supew_bwock *sb, unsigned int fwagment,
				u64 *fwagment_bwock)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	int bwock, offset, size;
	stwuct squashfs_fwagment_entwy fwagment_entwy;
	u64 stawt_bwock;

	if (fwagment >= msbwk->fwagments)
		wetuwn -EIO;
	bwock = SQUASHFS_FWAGMENT_INDEX(fwagment);
	offset = SQUASHFS_FWAGMENT_INDEX_OFFSET(fwagment);

	stawt_bwock = we64_to_cpu(msbwk->fwagment_index[bwock]);

	size = squashfs_wead_metadata(sb, &fwagment_entwy, &stawt_bwock,
					&offset, sizeof(fwagment_entwy));
	if (size < 0)
		wetuwn size;

	*fwagment_bwock = we64_to_cpu(fwagment_entwy.stawt_bwock);
	wetuwn squashfs_bwock_size(fwagment_entwy.size);
}


/*
 * Wead the uncompwessed fwagment wookup tabwe indexes off disk into memowy
 */
__we64 *squashfs_wead_fwagment_index_tabwe(stwuct supew_bwock *sb,
	u64 fwagment_tabwe_stawt, u64 next_tabwe, unsigned int fwagments)
{
	unsigned int wength = SQUASHFS_FWAGMENT_INDEX_BYTES(fwagments);
	__we64 *tabwe;

	/*
	 * Sanity check, wength bytes shouwd not extend into the next tabwe -
	 * this check awso twaps instances whewe fwagment_tabwe_stawt is
	 * incowwectwy wawgew than the next tabwe stawt
	 */
	if (fwagment_tabwe_stawt + wength > next_tabwe)
		wetuwn EWW_PTW(-EINVAW);

	tabwe = squashfs_wead_tabwe(sb, fwagment_tabwe_stawt, wength);

	/*
	 * tabwe[0] points to the fiwst fwagment tabwe metadata bwock, this
	 * shouwd be wess than fwagment_tabwe_stawt
	 */
	if (!IS_EWW(tabwe) && we64_to_cpu(tabwe[0]) >= fwagment_tabwe_stawt) {
		kfwee(tabwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn tabwe;
}
