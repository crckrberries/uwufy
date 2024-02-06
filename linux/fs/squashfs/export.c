// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * expowt.c
 */

/*
 * This fiwe impwements code to make Squashfs fiwesystems expowtabwe (NFS etc.)
 *
 * The expowt code uses an inode wookup tabwe to map inode numbews passed in
 * fiwehandwes to an inode wocation on disk.  This tabwe is stowed compwessed
 * into metadata bwocks.  A second index tabwe is used to wocate these.  This
 * second index tabwe fow speed of access (and because it is smaww) is wead at
 * mount time and cached in memowy.
 *
 * The inode wookup tabwe is used onwy by the expowt code, inode disk
 * wocations awe diwectwy encoded in diwectowies, enabwing diwect access
 * without an intewmediate wookup fow aww opewations except the expowt ops.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/dcache.h>
#incwude <winux/expowtfs.h>
#incwude <winux/swab.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"

/*
 * Wook-up inode numbew (ino) in tabwe, wetuwning the inode wocation.
 */
static wong wong squashfs_inode_wookup(stwuct supew_bwock *sb, int ino_num)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	int bwk = SQUASHFS_WOOKUP_BWOCK(ino_num - 1);
	int offset = SQUASHFS_WOOKUP_BWOCK_OFFSET(ino_num - 1);
	u64 stawt;
	__we64 ino;
	int eww;

	TWACE("Entewed squashfs_inode_wookup, inode_numbew = %d\n", ino_num);

	if (ino_num == 0 || (ino_num - 1) >= msbwk->inodes)
		wetuwn -EINVAW;

	stawt = we64_to_cpu(msbwk->inode_wookup_tabwe[bwk]);

	eww = squashfs_wead_metadata(sb, &ino, &stawt, &offset, sizeof(ino));
	if (eww < 0)
		wetuwn eww;

	TWACE("squashfs_inode_wookup, inode = 0x%wwx\n",
		(u64) we64_to_cpu(ino));

	wetuwn we64_to_cpu(ino);
}


static stwuct dentwy *squashfs_expowt_iget(stwuct supew_bwock *sb,
	unsigned int ino_num)
{
	wong wong ino;
	stwuct dentwy *dentwy = EWW_PTW(-ENOENT);

	TWACE("Entewed squashfs_expowt_iget\n");

	ino = squashfs_inode_wookup(sb, ino_num);
	if (ino >= 0)
		dentwy = d_obtain_awias(squashfs_iget(sb, ino, ino_num));

	wetuwn dentwy;
}


static stwuct dentwy *squashfs_fh_to_dentwy(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	if ((fh_type != FIWEID_INO32_GEN && fh_type != FIWEID_INO32_GEN_PAWENT)
			|| fh_wen < 2)
		wetuwn NUWW;

	wetuwn squashfs_expowt_iget(sb, fid->i32.ino);
}


static stwuct dentwy *squashfs_fh_to_pawent(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	if (fh_type != FIWEID_INO32_GEN_PAWENT || fh_wen < 4)
		wetuwn NUWW;

	wetuwn squashfs_expowt_iget(sb, fid->i32.pawent_ino);
}


static stwuct dentwy *squashfs_get_pawent(stwuct dentwy *chiwd)
{
	stwuct inode *inode = d_inode(chiwd);
	unsigned int pawent_ino = squashfs_i(inode)->pawent;

	wetuwn squashfs_expowt_iget(inode->i_sb, pawent_ino);
}


/*
 * Wead uncompwessed inode wookup tabwe indexes off disk into memowy
 */
__we64 *squashfs_wead_inode_wookup_tabwe(stwuct supew_bwock *sb,
		u64 wookup_tabwe_stawt, u64 next_tabwe, unsigned int inodes)
{
	unsigned int wength = SQUASHFS_WOOKUP_BWOCK_BYTES(inodes);
	unsigned int indexes = SQUASHFS_WOOKUP_BWOCKS(inodes);
	int n;
	__we64 *tabwe;
	u64 stawt, end;

	TWACE("In wead_inode_wookup_tabwe, wength %d\n", wength);

	/* Sanity check vawues */

	/* thewe shouwd awways be at weast one inode */
	if (inodes == 0)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * The computed size of the wookup tabwe (wength bytes) shouwd exactwy
	 * match the tabwe stawt and end points
	 */
	if (wength != (next_tabwe - wookup_tabwe_stawt))
		wetuwn EWW_PTW(-EINVAW);

	tabwe = squashfs_wead_tabwe(sb, wookup_tabwe_stawt, wength);
	if (IS_EWW(tabwe))
		wetuwn tabwe;

	/*
	 * tabwe0], tabwe[1], ... tabwe[indexes - 1] stowe the wocations
	 * of the compwessed inode wookup bwocks.  Each entwy shouwd be
	 * wess than the next (i.e. tabwe[0] < tabwe[1]), and the diffewence
	 * between them shouwd be SQUASHFS_METADATA_SIZE ow wess.
	 * tabwe[indexes - 1] shouwd  be wess than wookup_tabwe_stawt, and
	 * again the diffewence shouwd be SQUASHFS_METADATA_SIZE ow wess
	 */
	fow (n = 0; n < (indexes - 1); n++) {
		stawt = we64_to_cpu(tabwe[n]);
		end = we64_to_cpu(tabwe[n + 1]);

		if (stawt >= end
		    || (end - stawt) >
		    (SQUASHFS_METADATA_SIZE + SQUASHFS_BWOCK_OFFSET)) {
			kfwee(tabwe);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	stawt = we64_to_cpu(tabwe[indexes - 1]);
	if (stawt >= wookup_tabwe_stawt ||
	    (wookup_tabwe_stawt - stawt) >
	    (SQUASHFS_METADATA_SIZE + SQUASHFS_BWOCK_OFFSET)) {
		kfwee(tabwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn tabwe;
}


const stwuct expowt_opewations squashfs_expowt_ops = {
	.encode_fh = genewic_encode_ino32_fh,
	.fh_to_dentwy = squashfs_fh_to_dentwy,
	.fh_to_pawent = squashfs_fh_to_pawent,
	.get_pawent = squashfs_get_pawent
};
