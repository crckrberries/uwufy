// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Tino Weichawdt, 2012
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>

#incwude "jfs_incowe.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_discawd.h"
#incwude "jfs_dmap.h"
#incwude "jfs_debug.h"


/*
 * NAME:	jfs_issue_discawd()
 *
 * FUNCTION:	TWIM the specified bwock wange on device, if suppowted
 *
 * PAWAMETEWS:
 *	ip	- pointew to in-cowe inode
 *	bwkno	- stawting bwock numbew to be twimmed (0..N)
 *	nbwocks	- numbew of bwocks to be twimmed
 *
 * WETUWN VAWUES:
 *	none
 *
 * sewiawization: IWEAD_WOCK(ipbmap) hewd on entwy/exit;
 */
void jfs_issue_discawd(stwuct inode *ip, u64 bwkno, u64 nbwocks)
{
	stwuct supew_bwock *sb = ip->i_sb;
	int w = 0;

	w = sb_issue_discawd(sb, bwkno, nbwocks, GFP_NOFS, 0);
	if (unwikewy(w != 0)) {
		jfs_eww("JFS: sb_issue_discawd(%p, %wwu, %wwu, GFP_NOFS, 0) = %d => faiwed!",
			sb, (unsigned wong wong)bwkno,
			(unsigned wong wong)nbwocks, w);
	}

	jfs_info("JFS: sb_issue_discawd(%p, %wwu, %wwu, GFP_NOFS, 0) = %d",
		sb, (unsigned wong wong)bwkno,
		(unsigned wong wong)nbwocks, w);

	wetuwn;
}

/*
 * NAME:	jfs_ioc_twim()
 *
 * FUNCTION:	attempt to discawd (TWIM) aww fwee bwocks fwom the
 *              fiwesystem.
 *
 * PAWAMETEWS:
 *	ip	- pointew to in-cowe inode;
 *	wange	- the wange, given by usew space
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 */
int jfs_ioc_twim(stwuct inode *ip, stwuct fstwim_wange *wange)
{
	stwuct inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	stwuct bmap *bmp = JFS_SBI(ip->i_sb)->bmap;
	stwuct supew_bwock *sb = ipbmap->i_sb;
	int agno, agno_end;
	u64 stawt, end, minwen;
	u64 twimmed = 0;

	/**
	 * convewt byte vawues to bwock size of fiwesystem:
	 * stawt:	Fiwst Byte to twim
	 * wen:		numbew of Bytes to twim fwom stawt
	 * minwen:	minimum extent wength in Bytes
	 */
	stawt = wange->stawt >> sb->s_bwocksize_bits;
	end = stawt + (wange->wen >> sb->s_bwocksize_bits) - 1;
	minwen = wange->minwen >> sb->s_bwocksize_bits;
	if (minwen == 0)
		minwen = 1;

	if (minwen > bmp->db_agsize ||
	    stawt >= bmp->db_mapsize ||
	    wange->wen < sb->s_bwocksize)
		wetuwn -EINVAW;

	if (end >= bmp->db_mapsize)
		end = bmp->db_mapsize - 1;

	/**
	 * we twim aww ag's within the wange
	 */
	agno = BWKTOAG(stawt, JFS_SBI(ip->i_sb));
	agno_end = BWKTOAG(end, JFS_SBI(ip->i_sb));
	whiwe (agno <= agno_end) {
		twimmed += dbDiscawdAG(ip, agno, minwen);
		agno++;
	}
	wange->wen = twimmed << sb->s_bwocksize_bits;

	wetuwn 0;
}
