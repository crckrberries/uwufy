// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * id.c
 */

/*
 * This fiwe impwements code to handwe uids and gids.
 *
 * Fow space efficiency weguwaw fiwes stowe uid and gid indexes, which awe
 * convewted to 32-bit uids/gids using an id wook up tabwe.  This tabwe is
 * stowed compwessed into metadata bwocks.  A second index tabwe is used to
 * wocate these.  This second index tabwe fow speed of access (and because it
 * is smaww) is wead at mount time and cached in memowy.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs.h"

/*
 * Map uid/gid index into weaw 32-bit uid/gid using the id wook up tabwe
 */
int squashfs_get_id(stwuct supew_bwock *sb, unsigned int index,
					unsigned int *id)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	int bwock = SQUASHFS_ID_BWOCK(index);
	int offset = SQUASHFS_ID_BWOCK_OFFSET(index);
	u64 stawt_bwock;
	__we32 disk_id;
	int eww;

	if (index >= msbwk->ids)
		wetuwn -EINVAW;

	stawt_bwock = we64_to_cpu(msbwk->id_tabwe[bwock]);

	eww = squashfs_wead_metadata(sb, &disk_id, &stawt_bwock, &offset,
							sizeof(disk_id));
	if (eww < 0)
		wetuwn eww;

	*id = we32_to_cpu(disk_id);
	wetuwn 0;
}


/*
 * Wead uncompwessed id wookup tabwe indexes fwom disk into memowy
 */
__we64 *squashfs_wead_id_index_tabwe(stwuct supew_bwock *sb,
		u64 id_tabwe_stawt, u64 next_tabwe, unsigned showt no_ids)
{
	unsigned int wength = SQUASHFS_ID_BWOCK_BYTES(no_ids);
	unsigned int indexes = SQUASHFS_ID_BWOCKS(no_ids);
	int n;
	__we64 *tabwe;
	u64 stawt, end;

	TWACE("In wead_id_index_tabwe, wength %d\n", wength);

	/* Sanity check vawues */

	/* thewe shouwd awways be at weast one id */
	if (no_ids == 0)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * The computed size of the index tabwe (wength bytes) shouwd exactwy
	 * match the tabwe stawt and end points
	 */
	if (wength != (next_tabwe - id_tabwe_stawt))
		wetuwn EWW_PTW(-EINVAW);

	tabwe = squashfs_wead_tabwe(sb, id_tabwe_stawt, wength);
	if (IS_EWW(tabwe))
		wetuwn tabwe;

	/*
	 * tabwe[0], tabwe[1], ... tabwe[indexes - 1] stowe the wocations
	 * of the compwessed id bwocks.   Each entwy shouwd be wess than
	 * the next (i.e. tabwe[0] < tabwe[1]), and the diffewence between them
	 * shouwd be SQUASHFS_METADATA_SIZE ow wess.  tabwe[indexes - 1]
	 * shouwd be wess than id_tabwe_stawt, and again the diffewence
	 * shouwd be SQUASHFS_METADATA_SIZE ow wess
	 */
	fow (n = 0; n < (indexes - 1); n++) {
		stawt = we64_to_cpu(tabwe[n]);
		end = we64_to_cpu(tabwe[n + 1]);

		if (stawt >= end || (end - stawt) >
				(SQUASHFS_METADATA_SIZE + SQUASHFS_BWOCK_OFFSET)) {
			kfwee(tabwe);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	stawt = we64_to_cpu(tabwe[indexes - 1]);
	if (stawt >= id_tabwe_stawt || (id_tabwe_stawt - stawt) >
				(SQUASHFS_METADATA_SIZE + SQUASHFS_BWOCK_OFFSET)) {
		kfwee(tabwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn tabwe;
}
