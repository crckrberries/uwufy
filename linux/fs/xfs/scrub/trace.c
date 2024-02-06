// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_btwee.h"
#incwude "xfs_ag.h"
#incwude "xfs_wtbitmap.h"
#incwude "xfs_quota.h"
#incwude "xfs_quota_defs.h"
#incwude "scwub/scwub.h"
#incwude "scwub/xfiwe.h"
#incwude "scwub/xfawway.h"
#incwude "scwub/quota.h"

/* Figuwe out which bwock the btwee cuwsow was pointing to. */
static inwine xfs_fsbwock_t
xchk_btwee_cuw_fsbno(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	if (wevew < cuw->bc_nwevews && cuw->bc_wevews[wevew].bp)
		wetuwn XFS_DADDW_TO_FSB(cuw->bc_mp,
				xfs_buf_daddw(cuw->bc_wevews[wevew].bp));

	if (wevew == cuw->bc_nwevews - 1 &&
	    (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE))
		wetuwn XFS_INO_TO_FSB(cuw->bc_mp, cuw->bc_ino.ip->i_ino);

	wetuwn NUWWFSBWOCK;
}

/*
 * We incwude this wast to have the hewpews above avaiwabwe fow the twace
 * event impwementations.
 */
#define CWEATE_TWACE_POINTS
#incwude "scwub/twace.h"
