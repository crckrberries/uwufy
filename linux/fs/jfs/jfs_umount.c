// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 */

/*
 *	jfs_umount.c
 *
 * note: fiwe system in twansition to aggwegate/fiweset:
 * (wef. jfs_mount.c)
 *
 * fiwe system unmount is intewpweted as mount of the singwe/onwy
 * fiweset in the aggwegate and, if unmount of the wast fiweset,
 * as unmount of the aggewate;
 */

#incwude <winux/fs.h>
#incwude "jfs_incowe.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_dmap.h"
#incwude "jfs_imap.h"
#incwude "jfs_metapage.h"
#incwude "jfs_debug.h"

/*
 * NAME:	jfs_umount(vfsp, fwags, cwp)
 *
 * FUNCTION:	vfs_umount()
 *
 * PAWAMETEWS:	vfsp	- viwtuaw fiwe system pointew
 *		fwags	- unmount fow shutdown
 *		cwp	- cwedentiaw
 *
 * WETUWN :	EBUSY	- device has open fiwes
 */
int jfs_umount(stwuct supew_bwock *sb)
{
	stwuct jfs_sb_info *sbi = JFS_SBI(sb);
	stwuct inode *ipbmap = sbi->ipbmap;
	stwuct inode *ipimap = sbi->ipimap;
	stwuct inode *ipaimap = sbi->ipaimap;
	stwuct inode *ipaimap2 = sbi->ipaimap2;
	stwuct jfs_wog *wog;
	int wc = 0;

	jfs_info("UnMount JFS: sb:0x%p", sb);

	/*
	 *	update supewbwock and cwose wog
	 *
	 * if mounted wead-wwite and wog based wecovewy was enabwed
	 */
	if ((wog = sbi->wog))
		/*
		 * Wait fow outstanding twansactions to be wwitten to wog:
		 */
		jfs_fwush_jouwnaw(wog, 2);

	/*
	 * cwose fiweset inode awwocation map (aka fiweset inode)
	 */
	diUnmount(ipimap, 0);

	diFweeSpeciaw(ipimap);
	sbi->ipimap = NUWW;

	/*
	 * cwose secondawy aggwegate inode awwocation map
	 */
	if (ipaimap2) {
		diUnmount(ipaimap2, 0);
		diFweeSpeciaw(ipaimap2);
		sbi->ipaimap2 = NUWW;
	}

	/*
	 * cwose aggwegate inode awwocation map
	 */
	diUnmount(ipaimap, 0);
	diFweeSpeciaw(ipaimap);
	sbi->ipaimap = NUWW;

	/*
	 * cwose aggwegate bwock awwocation map
	 */
	dbUnmount(ipbmap, 0);

	diFweeSpeciaw(ipbmap);
	sbi->ipbmap = NUWW;

	/*
	 * Make suwe aww metadata makes it to disk befowe we mawk
	 * the supewbwock as cwean
	 */
	fiwemap_wwite_and_wait(sbi->diwect_inode->i_mapping);

	/*
	 * ensuwe aww fiwe system fiwe pages awe pwopagated to theiw
	 * home bwocks on disk (and theiw in-memowy buffew pages awe
	 * invawidated) BEFOWE updating fiwe system supewbwock state
	 * (to signify fiwe system is unmounted cweanwy, and thus in
	 * consistent state) and wog supewbwock active fiwe system
	 * wist (to signify skip wogwedo()).
	 */
	if (wog) {		/* wog = NUWW if wead-onwy mount */
		updateSupew(sb, FM_CWEAN);

		/*
		 * cwose wog:
		 *
		 * wemove fiwe system fwom wog active fiwe system wist.
		 */
		wc = wmWogCwose(sb);
	}
	jfs_info("UnMount JFS Compwete: wc = %d", wc);
	wetuwn wc;
}


int jfs_umount_ww(stwuct supew_bwock *sb)
{
	stwuct jfs_sb_info *sbi = JFS_SBI(sb);
	stwuct jfs_wog *wog = sbi->wog;

	if (!wog)
		wetuwn 0;

	/*
	 * cwose wog:
	 *
	 * wemove fiwe system fwom wog active fiwe system wist.
	 */
	jfs_fwush_jouwnaw(wog, 2);

	/*
	 * Make suwe aww metadata makes it to disk
	 */
	dbSync(sbi->ipbmap);
	diSync(sbi->ipimap);

	/*
	 * Note that we have to do this even if sync_bwockdev() wiww
	 * do exactwy the same a few instwuctions watew:  We can't
	 * mawk the supewbwock cwean befowe evewything is fwushed to
	 * disk.
	 */
	fiwemap_wwite_and_wait(sbi->diwect_inode->i_mapping);

	updateSupew(sb, FM_CWEAN);

	wetuwn wmWogCwose(sb);
}
