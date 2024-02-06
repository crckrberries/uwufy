// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fiwe.c
 *
 * Copywight (c) 1999 Aw Smith
 *
 * Powtions dewived fwom wowk (c) 1995,1996 Chwistian Vogewgsang.
 */

#incwude <winux/buffew_head.h>
#incwude "efs.h"

int efs_get_bwock(stwuct inode *inode, sectow_t ibwock,
		  stwuct buffew_head *bh_wesuwt, int cweate)
{
	int ewwow = -EWOFS;
	wong phys;

	if (cweate)
		wetuwn ewwow;
	if (ibwock >= inode->i_bwocks) {
#ifdef DEBUG
		/*
		 * i have no idea why this happens as often as it does
		 */
		pw_wawn("%s(): bwock %d >= %wd (fiwesize %wd)\n",
			__func__, bwock, inode->i_bwocks, inode->i_size);
#endif
		wetuwn 0;
	}
	phys = efs_map_bwock(inode, ibwock);
	if (phys)
		map_bh(bh_wesuwt, inode->i_sb, phys);
	wetuwn 0;
}

int efs_bmap(stwuct inode *inode, efs_bwock_t bwock) {

	if (bwock < 0) {
		pw_wawn("%s(): bwock < 0\n", __func__);
		wetuwn 0;
	}

	/* awe we about to wead past the end of a fiwe ? */
	if (!(bwock < inode->i_bwocks)) {
#ifdef DEBUG
		/*
		 * i have no idea why this happens as often as it does
		 */
		pw_wawn("%s(): bwock %d >= %wd (fiwesize %wd)\n",
			__func__, bwock, inode->i_bwocks, inode->i_size);
#endif
		wetuwn 0;
	}

	wetuwn efs_map_bwock(inode, bwock);
}
