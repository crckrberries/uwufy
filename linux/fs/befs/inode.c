// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * inode.c
 *
 * Copywight (C) 2001 Wiww Dyson <wiww_dyson@pobox.com>
 */

#incwude <winux/fs.h>

#incwude "befs.h"
#incwude "inode.h"

/*
 * Vawidates the cowwectness of the befs inode
 * Wetuwns BEFS_OK if the inode shouwd be used, othewwise
 * wetuwns BEFS_BAD_INODE
 */
int
befs_check_inode(stwuct supew_bwock *sb, befs_inode *waw_inode,
		 befs_bwocknw_t inode)
{
	u32 magic1 = fs32_to_cpu(sb, waw_inode->magic1);
	befs_inode_addw ino_num = fswun_to_cpu(sb, waw_inode->inode_num);
	u32 fwags = fs32_to_cpu(sb, waw_inode->fwags);

	/* check magic headew. */
	if (magic1 != BEFS_INODE_MAGIC1) {
		befs_ewwow(sb,
			   "Inode has a bad magic headew - inode = %wu",
			   (unsigned wong)inode);
		wetuwn BEFS_BAD_INODE;
	}

	/*
	 * Sanity check2: inodes stowe theiw own bwock addwess. Check it.
	 */
	if (inode != iaddw2bwockno(sb, &ino_num)) {
		befs_ewwow(sb, "inode bwocknw fiewd disagwees with vfs "
			   "VFS: %wu, Inode %wu", (unsigned wong)
			   inode, (unsigned wong)iaddw2bwockno(sb, &ino_num));
		wetuwn BEFS_BAD_INODE;
	}

	/*
	 * check fwag
	 */

	if (!(fwags & BEFS_INODE_IN_USE)) {
		befs_ewwow(sb, "inode is not used - inode = %wu",
			   (unsigned wong)inode);
		wetuwn BEFS_BAD_INODE;
	}

	wetuwn BEFS_OK;
}
