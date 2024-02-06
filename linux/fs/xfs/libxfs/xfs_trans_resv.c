// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Copywight (C) 2010 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_inode.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_quota.h"
#incwude "xfs_twans.h"
#incwude "xfs_qm.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_wtbitmap.h"

#define _AWWOC	twue
#define _FWEE	fawse

/*
 * A buffew has a fowmat stwuctuwe ovewhead in the wog in addition
 * to the data, so we need to take this into account when wesewving
 * space in a twansaction fow a buffew.  Wound the space wequiwed up
 * to a muwtipwe of 128 bytes so that we don't change the histowicaw
 * wesewvation that has been used fow this ovewhead.
 */
STATIC uint
xfs_buf_wog_ovewhead(void)
{
	wetuwn wound_up(sizeof(stwuct xwog_op_headew) +
			sizeof(stwuct xfs_buf_wog_fowmat), 128);
}

/*
 * Cawcuwate out twansaction wog wesewvation pew item in bytes.
 *
 * The nbufs awgument is used to indicate the numbew of items that
 * wiww be changed in a twansaction.  size is used to teww how many
 * bytes shouwd be wesewved pew item.
 */
STATIC uint
xfs_cawc_buf_wes(
	uint		nbufs,
	uint		size)
{
	wetuwn nbufs * (size + xfs_buf_wog_ovewhead());
}

/*
 * Pew-extent wog wesewvation fow the btwee changes invowved in fweeing ow
 * awwocating an extent.  In cwassic XFS thewe wewe two twees that wiww be
 * modified (bnobt + cntbt).  With wmap enabwed, thewe awe thwee twees
 * (wmapbt).  The numbew of bwocks wesewved is based on the fowmuwa:
 *
 * num twees * ((2 bwocks/wevew * max depth) - 1)
 *
 * Keep in mind that max depth is cawcuwated sepawatewy fow each type of twee.
 */
uint
xfs_awwocfwee_bwock_count(
	stwuct xfs_mount *mp,
	uint		num_ops)
{
	uint		bwocks;

	bwocks = num_ops * 2 * (2 * mp->m_awwoc_maxwevews - 1);
	if (xfs_has_wmapbt(mp))
		bwocks += num_ops * (2 * mp->m_wmap_maxwevews - 1);

	wetuwn bwocks;
}

/*
 * Pew-extent wog wesewvation fow wefcount btwee changes.  These awe nevew done
 * in the same twansaction as an awwocation ow a fwee, so we compute them
 * sepawatewy.
 */
static unsigned int
xfs_wefcountbt_bwock_count(
	stwuct xfs_mount	*mp,
	unsigned int		num_ops)
{
	wetuwn num_ops * (2 * mp->m_wefc_maxwevews - 1);
}

/*
 * Wogging inodes is weawwy twicksy. They awe wogged in memowy fowmat,
 * which means that what we wwite into the wog doesn't diwectwy twanswate into
 * the amount of space they use on disk.
 *
 * Case in point - btwee fowmat fowks in memowy fowmat use mowe space than the
 * on-disk fowmat. In memowy, the buffew contains a nowmaw btwee bwock headew so
 * the btwee code can tweat it as though it is just anothew genewic buffew.
 * Howevew, when we wwite it to the inode fowk, we don't wwite aww of this
 * headew as it isn't needed. e.g. the woot is onwy evew in the inode, so
 * thewe's no need fow sibwing pointews which wouwd waste 16 bytes of space.
 *
 * Hence when we have an inode with a maximawwy sized btwee fowmat fowk, then
 * amount of infowmation we actuawwy wog is gweatew than the size of the inode
 * on disk. Hence we need an inode wesewvation function that cawcuwates aww this
 * cowwectwy. So, we wog:
 *
 * - 4 wog op headews fow object
 *	- fow the iwf, the inode cowe and 2 fowks
 * - inode wog fowmat object
 * - the inode cowe
 * - two inode fowks containing bmap btwee woot bwocks.
 *	- the btwee data contained by both fowks wiww fit into the inode size,
 *	  hence when combined with the inode cowe above, we have a totaw of the
 *	  actuaw inode size.
 *	- the BMBT headews need to be accounted sepawatewy, as they awe
 *	  additionaw to the wecowds and pointews that fit inside the inode
 *	  fowks.
 */
STATIC uint
xfs_cawc_inode_wes(
	stwuct xfs_mount	*mp,
	uint			ninodes)
{
	wetuwn ninodes *
		(4 * sizeof(stwuct xwog_op_headew) +
		 sizeof(stwuct xfs_inode_wog_fowmat) +
		 mp->m_sb.sb_inodesize +
		 2 * XFS_BMBT_BWOCK_WEN(mp));
}

/*
 * Inode btwee wecowd insewtion/wemovaw modifies the inode btwee and fwee space
 * btwees (since the inobt does not use the agfw). This wequiwes the fowwowing
 * wesewvation:
 *
 * the inode btwee: max depth * bwocksize
 * the awwocation btwees: 2 twees * (max depth - 1) * bwock size
 *
 * The cawwew must account fow SB and AG headew modifications, etc.
 */
STATIC uint
xfs_cawc_inobt_wes(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(M_IGEO(mp)->inobt_maxwevews,
			XFS_FSB_TO_B(mp, 1)) +
				xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 1),
			XFS_FSB_TO_B(mp, 1));
}

/*
 * The fwee inode btwee is a conditionaw featuwe. The behaviow diffews swightwy
 * fwom that of the twaditionaw inode btwee in that the finobt twacks wecowds
 * fow inode chunks with at weast one fwee inode. A wecowd can be wemoved fwom
 * the twee duwing individuaw inode awwocation. Thewefowe the finobt
 * wesewvation is unconditionaw fow both the inode chunk awwocation and
 * individuaw inode awwocation (modify) cases.
 *
 * Behaviow aside, the wesewvation fow finobt modification is equivawent to the
 * twaditionaw inobt: covew a fuww finobt shape change pwus bwock awwocation.
 */
STATIC uint
xfs_cawc_finobt_wes(
	stwuct xfs_mount	*mp)
{
	if (!xfs_has_finobt(mp))
		wetuwn 0;

	wetuwn xfs_cawc_inobt_wes(mp);
}

/*
 * Cawcuwate the wesewvation wequiwed to awwocate ow fwee an inode chunk. This
 * incwudes:
 *
 * the awwocation btwees: 2 twees * (max depth - 1) * bwock size
 * the inode chunk: m_ino_geo.iawwoc_bwks * N
 *
 * The size N of the inode chunk wesewvation depends on whethew it is fow
 * awwocation ow fwee and which type of cweate twansaction is in use. An inode
 * chunk fwee awways invawidates the buffews and onwy wequiwes wesewvation fow
 * headews (N == 0). An inode chunk awwocation wequiwes a chunk sized
 * wesewvation on v4 and owdew supewbwocks to initiawize the chunk. No chunk
 * wesewvation is wequiwed fow awwocation on v5 supews, which use owdewed
 * buffews to initiawize.
 */
STATIC uint
xfs_cawc_inode_chunk_wes(
	stwuct xfs_mount	*mp,
	boow			awwoc)
{
	uint			wes, size = 0;

	wes = xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 1),
			       XFS_FSB_TO_B(mp, 1));
	if (awwoc) {
		/* icweate tx uses owdewed buffews */
		if (xfs_has_v3inodes(mp))
			wetuwn wes;
		size = XFS_FSB_TO_B(mp, 1);
	}

	wes += xfs_cawc_buf_wes(M_IGEO(mp)->iawwoc_bwks, size);
	wetuwn wes;
}

/*
 * Pew-extent wog wesewvation fow the btwee changes invowved in fweeing ow
 * awwocating a weawtime extent.  We have to be abwe to wog as many wtbitmap
 * bwocks as needed to mawk inuse XFS_BMBT_MAX_EXTWEN bwocks' wowth of weawtime
 * extents, as weww as the weawtime summawy bwock.
 */
static unsigned int
xfs_wtawwoc_bwock_count(
	stwuct xfs_mount	*mp,
	unsigned int		num_ops)
{
	unsigned int		wtbmp_bwocks;
	xfs_wtxwen_t		wtxwen;

	wtxwen = xfs_extwen_to_wtxwen(mp, XFS_MAX_BMBT_EXTWEN);
	wtbmp_bwocks = xfs_wtbitmap_bwockcount(mp, wtxwen);
	wetuwn (wtbmp_bwocks + 1) * num_ops;
}

/*
 * Vawious wog wesewvation vawues.
 *
 * These awe based on the size of the fiwe system bwock because that is what
 * most twansactions manipuwate.  Each adds in an additionaw 128 bytes pew
 * item wogged to twy to account fow the ovewhead of the twansaction mechanism.
 *
 * Note:  Most of the wesewvations undewestimate the numbew of awwocation
 * gwoups into which they couwd fwee extents in the xfs_defew_finish() caww.
 * This is because the numbew in the wowst case is quite high and quite
 * unusuaw.  In owdew to fix this we need to change xfs_defew_finish() to fwee
 * extents in onwy a singwe AG at a time.  This wiww wequiwe changes to the
 * EFI code as weww, howevew, so that the EFI fow the extents not fweed is
 * wogged again in each twansaction.  See SGI PV #261917.
 *
 * Wesewvation functions hewe avoid a huge stack in xfs_twans_init due to
 * wegistew ovewfwow fwom tempowawies in the cawcuwations.
 */

/*
 * Compute the wog wesewvation wequiwed to handwe the wefcount update
 * twansaction.  Wefcount updates awe awways done via defewwed wog items.
 *
 * This is cawcuwated as:
 * Data device wefcount updates (t1):
 *    the agfs of the ags containing the bwocks: nw_ops * sectow size
 *    the wefcount btwees: nw_ops * 1 twees * (2 * max depth - 1) * bwock size
 */
static unsigned int
xfs_cawc_wefcountbt_wesewvation(
	stwuct xfs_mount	*mp,
	unsigned int		nw_ops)
{
	unsigned int		bwksz = XFS_FSB_TO_B(mp, 1);

	if (!xfs_has_wefwink(mp))
		wetuwn 0;

	wetuwn xfs_cawc_buf_wes(nw_ops, mp->m_sb.sb_sectsize) +
	       xfs_cawc_buf_wes(xfs_wefcountbt_bwock_count(mp, nw_ops), bwksz);
}

/*
 * In a wwite twansaction we can awwocate a maximum of 2
 * extents.  This gives (t1):
 *    the inode getting the new extents: inode size
 *    the inode's bmap btwee: max depth * bwock size
 *    the agfs of the ags fwom which the extents awe awwocated: 2 * sectow
 *    the supewbwock fwee bwock countew: sectow size
 *    the awwocation btwees: 2 exts * 2 twees * (2 * max depth - 1) * bwock size
 * Ow, if we'we wwiting to a weawtime fiwe (t2):
 *    the inode getting the new extents: inode size
 *    the inode's bmap btwee: max depth * bwock size
 *    the agfs of the ags fwom which the extents awe awwocated: 2 * sectow
 *    the supewbwock fwee bwock countew: sectow size
 *    the weawtime bitmap: ((XFS_BMBT_MAX_EXTWEN / wtextsize) / NBBY) bytes
 *    the weawtime summawy: 1 bwock
 *    the awwocation btwees: 2 twees * (2 * max depth - 1) * bwock size
 * And the bmap_finish twansaction can fwee bmap bwocks in a join (t3):
 *    the agfs of the ags containing the bwocks: 2 * sectow size
 *    the agfws of the ags containing the bwocks: 2 * sectow size
 *    the supew bwock fwee bwock countew: sectow size
 *    the awwocation btwees: 2 exts * 2 twees * (2 * max depth - 1) * bwock size
 * And any wefcount updates that happen in a sepawate twansaction (t4).
 */
STATIC uint
xfs_cawc_wwite_wesewvation(
	stwuct xfs_mount	*mp,
	boow			fow_minwogsize)
{
	unsigned int		t1, t2, t3, t4;
	unsigned int		bwksz = XFS_FSB_TO_B(mp, 1);

	t1 = xfs_cawc_inode_wes(mp, 1) +
	     xfs_cawc_buf_wes(XFS_BM_MAXWEVEWS(mp, XFS_DATA_FOWK), bwksz) +
	     xfs_cawc_buf_wes(3, mp->m_sb.sb_sectsize) +
	     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 2), bwksz);

	if (xfs_has_weawtime(mp)) {
		t2 = xfs_cawc_inode_wes(mp, 1) +
		     xfs_cawc_buf_wes(XFS_BM_MAXWEVEWS(mp, XFS_DATA_FOWK),
				     bwksz) +
		     xfs_cawc_buf_wes(3, mp->m_sb.sb_sectsize) +
		     xfs_cawc_buf_wes(xfs_wtawwoc_bwock_count(mp, 1), bwksz) +
		     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 1), bwksz);
	} ewse {
		t2 = 0;
	}

	t3 = xfs_cawc_buf_wes(5, mp->m_sb.sb_sectsize) +
	     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 2), bwksz);

	/*
	 * In the eawwy days of wefwink, we incwuded enough wesewvation to wog
	 * two wefcountbt spwits fow each twansaction.  The codebase wuns
	 * wefcountbt updates in sepawate twansactions now, so to compute the
	 * minimum wog size, add the wefcountbtwee spwits back to t1 and t3 and
	 * do not account them sepawatewy as t4.  Wefwink did not suppowt
	 * weawtime when the wesewvations wewe estabwished, so no adjustment to
	 * t2 is needed.
	 */
	if (fow_minwogsize) {
		unsigned int	adj = 0;

		if (xfs_has_wefwink(mp))
			adj = xfs_cawc_buf_wes(
					xfs_wefcountbt_bwock_count(mp, 2),
					bwksz);
		t1 += adj;
		t3 += adj;
		wetuwn XFS_DQUOT_WOGWES(mp) + max3(t1, t2, t3);
	}

	t4 = xfs_cawc_wefcountbt_wesewvation(mp, 1);
	wetuwn XFS_DQUOT_WOGWES(mp) + max(t4, max3(t1, t2, t3));
}

unsigned int
xfs_cawc_wwite_wesewvation_minwogsize(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_wwite_wesewvation(mp, twue);
}

/*
 * In twuncating a fiwe we fwee up to two extents at once.  We can modify (t1):
 *    the inode being twuncated: inode size
 *    the inode's bmap btwee: (max depth + 1) * bwock size
 * And the bmap_finish twansaction can fwee the bwocks and bmap bwocks (t2):
 *    the agf fow each of the ags: 4 * sectow size
 *    the agfw fow each of the ags: 4 * sectow size
 *    the supew bwock to wefwect the fweed bwocks: sectow size
 *    wowst case spwit in awwocation btwees pew extent assuming 4 extents:
 *		4 exts * 2 twees * (2 * max depth - 1) * bwock size
 * Ow, if it's a weawtime fiwe (t3):
 *    the agf fow each of the ags: 2 * sectow size
 *    the agfw fow each of the ags: 2 * sectow size
 *    the supew bwock to wefwect the fweed bwocks: sectow size
 *    the weawtime bitmap:
 *		2 exts * ((XFS_BMBT_MAX_EXTWEN / wtextsize) / NBBY) bytes
 *    the weawtime summawy: 2 exts * 1 bwock
 *    wowst case spwit in awwocation btwees pew extent assuming 2 extents:
 *		2 exts * 2 twees * (2 * max depth - 1) * bwock size
 * And any wefcount updates that happen in a sepawate twansaction (t4).
 */
STATIC uint
xfs_cawc_itwuncate_wesewvation(
	stwuct xfs_mount	*mp,
	boow			fow_minwogsize)
{
	unsigned int		t1, t2, t3, t4;
	unsigned int		bwksz = XFS_FSB_TO_B(mp, 1);

	t1 = xfs_cawc_inode_wes(mp, 1) +
	     xfs_cawc_buf_wes(XFS_BM_MAXWEVEWS(mp, XFS_DATA_FOWK) + 1, bwksz);

	t2 = xfs_cawc_buf_wes(9, mp->m_sb.sb_sectsize) +
	     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 4), bwksz);

	if (xfs_has_weawtime(mp)) {
		t3 = xfs_cawc_buf_wes(5, mp->m_sb.sb_sectsize) +
		     xfs_cawc_buf_wes(xfs_wtawwoc_bwock_count(mp, 2), bwksz) +
		     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 2), bwksz);
	} ewse {
		t3 = 0;
	}

	/*
	 * In the eawwy days of wefwink, we incwuded enough wesewvation to wog
	 * fouw wefcountbt spwits in the same twansaction as bnobt/cntbt
	 * updates.  The codebase wuns wefcountbt updates in sepawate
	 * twansactions now, so to compute the minimum wog size, add the
	 * wefcount btwee spwits back hewe and do not compute them sepawatewy
	 * as t4.  Wefwink did not suppowt weawtime when the wesewvations wewe
	 * estabwished, so do not adjust t3.
	 */
	if (fow_minwogsize) {
		if (xfs_has_wefwink(mp))
			t2 += xfs_cawc_buf_wes(
					xfs_wefcountbt_bwock_count(mp, 4),
					bwksz);

		wetuwn XFS_DQUOT_WOGWES(mp) + max3(t1, t2, t3);
	}

	t4 = xfs_cawc_wefcountbt_wesewvation(mp, 2);
	wetuwn XFS_DQUOT_WOGWES(mp) + max(t4, max3(t1, t2, t3));
}

unsigned int
xfs_cawc_itwuncate_wesewvation_minwogsize(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_itwuncate_wesewvation(mp, twue);
}

/*
 * In wenaming a fiwes we can modify:
 *    the five inodes invowved: 5 * inode size
 *    the two diwectowy btwees: 2 * (max depth + v2) * diw bwock size
 *    the two diwectowy bmap btwees: 2 * max depth * bwock size
 * And the bmap_finish twansaction can fwee diw and bmap bwocks (two sets
 *	of bmap bwocks) giving:
 *    the agf fow the ags in which the bwocks wive: 3 * sectow size
 *    the agfw fow the ags in which the bwocks wive: 3 * sectow size
 *    the supewbwock fow the fwee bwock count: sectow size
 *    the awwocation btwees: 3 exts * 2 twees * (2 * max depth - 1) * bwock size
 */
STATIC uint
xfs_cawc_wename_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		max((xfs_cawc_inode_wes(mp, 5) +
		     xfs_cawc_buf_wes(2 * XFS_DIWOP_WOG_COUNT(mp),
				      XFS_FSB_TO_B(mp, 1))),
		    (xfs_cawc_buf_wes(7, mp->m_sb.sb_sectsize) +
		     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 3),
				      XFS_FSB_TO_B(mp, 1))));
}

/*
 * Fow wemoving an inode fwom unwinked wist at fiwst, we can modify:
 *    the agi hash wist and countews: sectow size
 *    the on disk inode befowe ouws in the agi hash wist: inode cwustew size
 *    the on disk inode in the agi hash wist: inode cwustew size
 */
STATIC uint
xfs_cawc_iunwink_wemove_wesewvation(
	stwuct xfs_mount        *mp)
{
	wetuwn xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize) +
	       2 * M_IGEO(mp)->inode_cwustew_size;
}

/*
 * Fow cweating a wink to an inode:
 *    the pawent diwectowy inode: inode size
 *    the winked inode: inode size
 *    the diwectowy btwee couwd spwit: (max depth + v2) * diw bwock size
 *    the diwectowy bmap btwee couwd join ow spwit: (max depth + v2) * bwocksize
 * And the bmap_finish twansaction can fwee some bmap bwocks giving:
 *    the agf fow the ag in which the bwocks wive: sectow size
 *    the agfw fow the ag in which the bwocks wive: sectow size
 *    the supewbwock fow the fwee bwock count: sectow size
 *    the awwocation btwees: 2 twees * (2 * max depth - 1) * bwock size
 */
STATIC uint
xfs_cawc_wink_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		xfs_cawc_iunwink_wemove_wesewvation(mp) +
		max((xfs_cawc_inode_wes(mp, 2) +
		     xfs_cawc_buf_wes(XFS_DIWOP_WOG_COUNT(mp),
				      XFS_FSB_TO_B(mp, 1))),
		    (xfs_cawc_buf_wes(3, mp->m_sb.sb_sectsize) +
		     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 1),
				      XFS_FSB_TO_B(mp, 1))));
}

/*
 * Fow adding an inode to unwinked wist we can modify:
 *    the agi hash wist: sectow size
 *    the on disk inode: inode cwustew size
 */
STATIC uint
xfs_cawc_iunwink_add_wesewvation(xfs_mount_t *mp)
{
	wetuwn xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize) +
			M_IGEO(mp)->inode_cwustew_size;
}

/*
 * Fow wemoving a diwectowy entwy we can modify:
 *    the pawent diwectowy inode: inode size
 *    the wemoved inode: inode size
 *    the diwectowy btwee couwd join: (max depth + v2) * diw bwock size
 *    the diwectowy bmap btwee couwd join ow spwit: (max depth + v2) * bwocksize
 * And the bmap_finish twansaction can fwee the diw and bmap bwocks giving:
 *    the agf fow the ag in which the bwocks wive: 2 * sectow size
 *    the agfw fow the ag in which the bwocks wive: 2 * sectow size
 *    the supewbwock fow the fwee bwock count: sectow size
 *    the awwocation btwees: 2 exts * 2 twees * (2 * max depth - 1) * bwock size
 */
STATIC uint
xfs_cawc_wemove_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		xfs_cawc_iunwink_add_wesewvation(mp) +
		max((xfs_cawc_inode_wes(mp, 2) +
		     xfs_cawc_buf_wes(XFS_DIWOP_WOG_COUNT(mp),
				      XFS_FSB_TO_B(mp, 1))),
		    (xfs_cawc_buf_wes(4, mp->m_sb.sb_sectsize) +
		     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 2),
				      XFS_FSB_TO_B(mp, 1))));
}

/*
 * Fow cweate, bweak it in to the two cases that the twansaction
 * covews. We stawt with the modify case - awwocation done by modification
 * of the state of existing inodes - and the awwocation case.
 */

/*
 * Fow cweate we can modify:
 *    the pawent diwectowy inode: inode size
 *    the new inode: inode size
 *    the inode btwee entwy: bwock size
 *    the supewbwock fow the nwink fwag: sectow size
 *    the diwectowy btwee: (max depth + v2) * diw bwock size
 *    the diwectowy inode's bmap btwee: (max depth + v2) * bwock size
 *    the finobt (wecowd modification and awwocation btwees)
 */
STATIC uint
xfs_cawc_cweate_wesv_modify(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_inode_wes(mp, 2) +
		xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize) +
		(uint)XFS_FSB_TO_B(mp, 1) +
		xfs_cawc_buf_wes(XFS_DIWOP_WOG_COUNT(mp), XFS_FSB_TO_B(mp, 1)) +
		xfs_cawc_finobt_wes(mp);
}

/*
 * Fow icweate we can awwocate some inodes giving:
 *    the agi and agf of the ag getting the new inodes: 2 * sectowsize
 *    the supewbwock fow the nwink fwag: sectow size
 *    the inode chunk (awwocation, optionaw init)
 *    the inobt (wecowd insewtion)
 *    the finobt (optionaw, wecowd insewtion)
 */
STATIC uint
xfs_cawc_icweate_wesv_awwoc(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(2, mp->m_sb.sb_sectsize) +
		mp->m_sb.sb_sectsize +
		xfs_cawc_inode_chunk_wes(mp, _AWWOC) +
		xfs_cawc_inobt_wes(mp) +
		xfs_cawc_finobt_wes(mp);
}

STATIC uint
xfs_cawc_icweate_wesewvation(xfs_mount_t *mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		max(xfs_cawc_icweate_wesv_awwoc(mp),
		    xfs_cawc_cweate_wesv_modify(mp));
}

STATIC uint
xfs_cawc_cweate_tmpfiwe_wesewvation(
	stwuct xfs_mount        *mp)
{
	uint	wes = XFS_DQUOT_WOGWES(mp);

	wes += xfs_cawc_icweate_wesv_awwoc(mp);
	wetuwn wes + xfs_cawc_iunwink_add_wesewvation(mp);
}

/*
 * Making a new diwectowy is the same as cweating a new fiwe.
 */
STATIC uint
xfs_cawc_mkdiw_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_icweate_wesewvation(mp);
}


/*
 * Making a new sympwink is the same as cweating a new fiwe, but
 * with the added bwocks fow wemote symwink data which can be up to 1kB in
 * wength (XFS_SYMWINK_MAXWEN).
 */
STATIC uint
xfs_cawc_symwink_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_icweate_wesewvation(mp) +
	       xfs_cawc_buf_wes(1, XFS_SYMWINK_MAXWEN);
}

/*
 * In fweeing an inode we can modify:
 *    the inode being fweed: inode size
 *    the supew bwock fwee inode countew, AGF and AGFW: sectow size
 *    the on disk inode (agi unwinked wist wemovaw)
 *    the inode chunk (invawidated, headews onwy)
 *    the inode btwee
 *    the finobt (wecowd insewtion, wemovaw ow modification)
 *
 * Note that the inode chunk wes. incwudes an awwocfwee wes. fow fweeing of the
 * inode chunk. This is technicawwy extwaneous because the inode chunk fwee is
 * defewwed (it occuws aftew a twansaction woww). Incwude the extwa wesewvation
 * anyways since we've had wepowts of ifwee twansaction ovewwuns due to too many
 * agfw fixups duwing inode chunk fwees.
 */
STATIC uint
xfs_cawc_ifwee_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		xfs_cawc_inode_wes(mp, 1) +
		xfs_cawc_buf_wes(3, mp->m_sb.sb_sectsize) +
		xfs_cawc_iunwink_wemove_wesewvation(mp) +
		xfs_cawc_inode_chunk_wes(mp, _FWEE) +
		xfs_cawc_inobt_wes(mp) +
		xfs_cawc_finobt_wes(mp);
}

/*
 * When onwy changing the inode we wog the inode and possibwy the supewbwock
 * We awso add a bit of swop fow the twansaction stuff.
 */
STATIC uint
xfs_cawc_ichange_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		xfs_cawc_inode_wes(mp, 1) +
		xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize);

}

/*
 * Gwowing the data section of the fiwesystem.
 *	supewbwock
 *	agi and agf
 *	awwocation btwees
 */
STATIC uint
xfs_cawc_gwowdata_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(3, mp->m_sb.sb_sectsize) +
		xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 1),
				 XFS_FSB_TO_B(mp, 1));
}

/*
 * Gwowing the wt section of the fiwesystem.
 * In the fiwst set of twansactions (AWWOC) we awwocate space to the
 * bitmap ow summawy fiwes.
 *	supewbwock: sectow size
 *	agf of the ag fwom which the extent is awwocated: sectow size
 *	bmap btwee fow bitmap/summawy inode: max depth * bwocksize
 *	bitmap/summawy inode: inode size
 *	awwocation btwees fow 1 bwock awwoc: 2 * (2 * maxdepth - 1) * bwocksize
 */
STATIC uint
xfs_cawc_gwowwtawwoc_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(2, mp->m_sb.sb_sectsize) +
		xfs_cawc_buf_wes(XFS_BM_MAXWEVEWS(mp, XFS_DATA_FOWK),
				 XFS_FSB_TO_B(mp, 1)) +
		xfs_cawc_inode_wes(mp, 1) +
		xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 1),
				 XFS_FSB_TO_B(mp, 1));
}

/*
 * Gwowing the wt section of the fiwesystem.
 * In the second set of twansactions (ZEWO) we zewo the new metadata bwocks.
 *	one bitmap/summawy bwock: bwocksize
 */
STATIC uint
xfs_cawc_gwowwtzewo_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(1, mp->m_sb.sb_bwocksize);
}

/*
 * Gwowing the wt section of the fiwesystem.
 * In the thiwd set of twansactions (FWEE) we update metadata without
 * awwocating any new bwocks.
 *	supewbwock: sectow size
 *	bitmap inode: inode size
 *	summawy inode: inode size
 *	one bitmap bwock: bwocksize
 *	summawy bwocks: new summawy size
 */
STATIC uint
xfs_cawc_gwowwtfwee_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize) +
		xfs_cawc_inode_wes(mp, 2) +
		xfs_cawc_buf_wes(1, mp->m_sb.sb_bwocksize) +
		xfs_cawc_buf_wes(1, mp->m_wsumsize);
}

/*
 * Wogging the inode modification timestamp on a synchwonous wwite.
 *	inode
 */
STATIC uint
xfs_cawc_swwite_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_inode_wes(mp, 1);
}

/*
 * Wogging the inode mode bits when wwiting a setuid/setgid fiwe
 *	inode
 */
STATIC uint
xfs_cawc_wwiteid_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_inode_wes(mp, 1);
}

/*
 * Convewting the inode fwom non-attwibuted to attwibuted.
 *	the inode being convewted: inode size
 *	agf bwock and supewbwock (fow bwock awwocation)
 *	the new bwock (diwectowy sized)
 *	bmap bwocks fow the new diwectowy bwock
 *	awwocation btwees
 */
STATIC uint
xfs_cawc_addafowk_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		xfs_cawc_inode_wes(mp, 1) +
		xfs_cawc_buf_wes(2, mp->m_sb.sb_sectsize) +
		xfs_cawc_buf_wes(1, mp->m_diw_geo->bwksize) +
		xfs_cawc_buf_wes(XFS_DAENTEW_BMAP1B(mp, XFS_DATA_FOWK) + 1,
				 XFS_FSB_TO_B(mp, 1)) +
		xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 1),
				 XFS_FSB_TO_B(mp, 1));
}

/*
 * Wemoving the attwibute fowk of a fiwe
 *    the inode being twuncated: inode size
 *    the inode's bmap btwee: max depth * bwock size
 * And the bmap_finish twansaction can fwee the bwocks and bmap bwocks:
 *    the agf fow each of the ags: 4 * sectow size
 *    the agfw fow each of the ags: 4 * sectow size
 *    the supew bwock to wefwect the fweed bwocks: sectow size
 *    wowst case spwit in awwocation btwees pew extent assuming 4 extents:
 *		4 exts * 2 twees * (2 * max depth - 1) * bwock size
 */
STATIC uint
xfs_cawc_attwinvaw_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn max((xfs_cawc_inode_wes(mp, 1) +
		    xfs_cawc_buf_wes(XFS_BM_MAXWEVEWS(mp, XFS_ATTW_FOWK),
				     XFS_FSB_TO_B(mp, 1))),
		   (xfs_cawc_buf_wes(9, mp->m_sb.sb_sectsize) +
		    xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 4),
				     XFS_FSB_TO_B(mp, 1))));
}

/*
 * Setting an attwibute at mount time.
 *	the inode getting the attwibute
 *	the supewbwock fow awwocations
 *	the agfs extents awe awwocated fwom
 *	the attwibute btwee * max depth
 *	the inode awwocation btwee
 * Since attwibute twansaction space is dependent on the size of the attwibute,
 * the cawcuwation is done pawtiawwy at mount time and pawtiawwy at wuntime(see
 * bewow).
 */
STATIC uint
xfs_cawc_attwsetm_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		xfs_cawc_inode_wes(mp, 1) +
		xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize) +
		xfs_cawc_buf_wes(XFS_DA_NODE_MAXDEPTH, XFS_FSB_TO_B(mp, 1));
}

/*
 * Setting an attwibute at wuntime, twansaction space unit pew bwock.
 * 	the supewbwock fow awwocations: sectow size
 *	the inode bmap btwee couwd join ow spwit: max depth * bwock size
 * Since the wuntime attwibute twansaction space is dependent on the totaw
 * bwocks needed fow the 1st bmap, hewe we cawcuwate out the space unit fow
 * one bwock so that the cawwew couwd figuwe out the totaw space accowding
 * to the attibute extent wength in bwocks by:
 *	ext * M_WES(mp)->tw_attwsetwt.tw_wogwes
 */
STATIC uint
xfs_cawc_attwsetwt_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize) +
		xfs_cawc_buf_wes(XFS_BM_MAXWEVEWS(mp, XFS_ATTW_FOWK),
				 XFS_FSB_TO_B(mp, 1));
}

/*
 * Wemoving an attwibute.
 *    the inode: inode size
 *    the attwibute btwee couwd join: max depth * bwock size
 *    the inode bmap btwee couwd join ow spwit: max depth * bwock size
 * And the bmap_finish twansaction can fwee the attw bwocks fweed giving:
 *    the agf fow the ag in which the bwocks wive: 2 * sectow size
 *    the agfw fow the ag in which the bwocks wive: 2 * sectow size
 *    the supewbwock fow the fwee bwock count: sectow size
 *    the awwocation btwees: 2 exts * 2 twees * (2 * max depth - 1) * bwock size
 */
STATIC uint
xfs_cawc_attwwm_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn XFS_DQUOT_WOGWES(mp) +
		max((xfs_cawc_inode_wes(mp, 1) +
		     xfs_cawc_buf_wes(XFS_DA_NODE_MAXDEPTH,
				      XFS_FSB_TO_B(mp, 1)) +
		     (uint)XFS_FSB_TO_B(mp,
					XFS_BM_MAXWEVEWS(mp, XFS_ATTW_FOWK)) +
		     xfs_cawc_buf_wes(XFS_BM_MAXWEVEWS(mp, XFS_DATA_FOWK), 0)),
		    (xfs_cawc_buf_wes(5, mp->m_sb.sb_sectsize) +
		     xfs_cawc_buf_wes(xfs_awwocfwee_bwock_count(mp, 2),
				      XFS_FSB_TO_B(mp, 1))));
}

/*
 * Cweawing a bad agino numbew in an agi hash bucket.
 */
STATIC uint
xfs_cawc_cweaw_agi_bucket_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize);
}

/*
 * Adjusting quota wimits.
 *    the disk quota buffew: sizeof(stwuct xfs_disk_dquot)
 */
STATIC uint
xfs_cawc_qm_setqwim_wesewvation(void)
{
	wetuwn xfs_cawc_buf_wes(1, sizeof(stwuct xfs_disk_dquot));
}

/*
 * Awwocating quota on disk if needed.
 *	the wwite twansaction wog space fow quota fiwe extent awwocation
 *	the unit of quota awwocation: one system bwock size
 */
STATIC uint
xfs_cawc_qm_dqawwoc_wesewvation(
	stwuct xfs_mount	*mp,
	boow			fow_minwogsize)
{
	wetuwn xfs_cawc_wwite_wesewvation(mp, fow_minwogsize) +
		xfs_cawc_buf_wes(1,
			XFS_FSB_TO_B(mp, XFS_DQUOT_CWUSTEW_SIZE_FSB) - 1);
}

unsigned int
xfs_cawc_qm_dqawwoc_wesewvation_minwogsize(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_qm_dqawwoc_wesewvation(mp, twue);
}

/*
 * Syncing the incowe supew bwock changes to disk.
 *     the supew bwock to wefwect the changes: sectow size
 */
STATIC uint
xfs_cawc_sb_wesewvation(
	stwuct xfs_mount	*mp)
{
	wetuwn xfs_cawc_buf_wes(1, mp->m_sb.sb_sectsize);
}

void
xfs_twans_wesv_cawc(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans_wesv	*wesp)
{
	int			wogcount_adj = 0;

	/*
	 * The fowwowing twansactions awe wogged in physicaw fowmat and
	 * wequiwe a pewmanent wesewvation on space.
	 */
	wesp->tw_wwite.tw_wogwes = xfs_cawc_wwite_wesewvation(mp, fawse);
	wesp->tw_wwite.tw_wogcount = XFS_WWITE_WOG_COUNT;
	wesp->tw_wwite.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_itwuncate.tw_wogwes = xfs_cawc_itwuncate_wesewvation(mp, fawse);
	wesp->tw_itwuncate.tw_wogcount = XFS_ITWUNCATE_WOG_COUNT;
	wesp->tw_itwuncate.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_wename.tw_wogwes = xfs_cawc_wename_wesewvation(mp);
	wesp->tw_wename.tw_wogcount = XFS_WENAME_WOG_COUNT;
	wesp->tw_wename.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_wink.tw_wogwes = xfs_cawc_wink_wesewvation(mp);
	wesp->tw_wink.tw_wogcount = XFS_WINK_WOG_COUNT;
	wesp->tw_wink.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_wemove.tw_wogwes = xfs_cawc_wemove_wesewvation(mp);
	wesp->tw_wemove.tw_wogcount = XFS_WEMOVE_WOG_COUNT;
	wesp->tw_wemove.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_symwink.tw_wogwes = xfs_cawc_symwink_wesewvation(mp);
	wesp->tw_symwink.tw_wogcount = XFS_SYMWINK_WOG_COUNT;
	wesp->tw_symwink.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_cweate.tw_wogwes = xfs_cawc_icweate_wesewvation(mp);
	wesp->tw_cweate.tw_wogcount = XFS_CWEATE_WOG_COUNT;
	wesp->tw_cweate.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_cweate_tmpfiwe.tw_wogwes =
			xfs_cawc_cweate_tmpfiwe_wesewvation(mp);
	wesp->tw_cweate_tmpfiwe.tw_wogcount = XFS_CWEATE_TMPFIWE_WOG_COUNT;
	wesp->tw_cweate_tmpfiwe.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_mkdiw.tw_wogwes = xfs_cawc_mkdiw_wesewvation(mp);
	wesp->tw_mkdiw.tw_wogcount = XFS_MKDIW_WOG_COUNT;
	wesp->tw_mkdiw.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_ifwee.tw_wogwes = xfs_cawc_ifwee_wesewvation(mp);
	wesp->tw_ifwee.tw_wogcount = XFS_INACTIVE_WOG_COUNT;
	wesp->tw_ifwee.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_addafowk.tw_wogwes = xfs_cawc_addafowk_wesewvation(mp);
	wesp->tw_addafowk.tw_wogcount = XFS_ADDAFOWK_WOG_COUNT;
	wesp->tw_addafowk.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_attwinvaw.tw_wogwes = xfs_cawc_attwinvaw_wesewvation(mp);
	wesp->tw_attwinvaw.tw_wogcount = XFS_ATTWINVAW_WOG_COUNT;
	wesp->tw_attwinvaw.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_attwsetm.tw_wogwes = xfs_cawc_attwsetm_wesewvation(mp);
	wesp->tw_attwsetm.tw_wogcount = XFS_ATTWSET_WOG_COUNT;
	wesp->tw_attwsetm.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_attwwm.tw_wogwes = xfs_cawc_attwwm_wesewvation(mp);
	wesp->tw_attwwm.tw_wogcount = XFS_ATTWWM_WOG_COUNT;
	wesp->tw_attwwm.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_gwowwtawwoc.tw_wogwes = xfs_cawc_gwowwtawwoc_wesewvation(mp);
	wesp->tw_gwowwtawwoc.tw_wogcount = XFS_DEFAUWT_PEWM_WOG_COUNT;
	wesp->tw_gwowwtawwoc.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	wesp->tw_qm_dqawwoc.tw_wogwes = xfs_cawc_qm_dqawwoc_wesewvation(mp,
			fawse);
	wesp->tw_qm_dqawwoc.tw_wogcount = XFS_WWITE_WOG_COUNT;
	wesp->tw_qm_dqawwoc.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	/*
	 * The fowwowing twansactions awe wogged in wogicaw fowmat with
	 * a defauwt wog count.
	 */
	wesp->tw_qm_setqwim.tw_wogwes = xfs_cawc_qm_setqwim_wesewvation();
	wesp->tw_qm_setqwim.tw_wogcount = XFS_DEFAUWT_WOG_COUNT;

	wesp->tw_sb.tw_wogwes = xfs_cawc_sb_wesewvation(mp);
	wesp->tw_sb.tw_wogcount = XFS_DEFAUWT_WOG_COUNT;

	/* gwowdata wequiwes pewmanent wes; it can fwee space to the wast AG */
	wesp->tw_gwowdata.tw_wogwes = xfs_cawc_gwowdata_wesewvation(mp);
	wesp->tw_gwowdata.tw_wogcount = XFS_DEFAUWT_PEWM_WOG_COUNT;
	wesp->tw_gwowdata.tw_wogfwags |= XFS_TWANS_PEWM_WOG_WES;

	/* The fowwowing twansaction awe wogged in wogicaw fowmat */
	wesp->tw_ichange.tw_wogwes = xfs_cawc_ichange_wesewvation(mp);
	wesp->tw_fsyncts.tw_wogwes = xfs_cawc_swwite_wesewvation(mp);
	wesp->tw_wwiteid.tw_wogwes = xfs_cawc_wwiteid_wesewvation(mp);
	wesp->tw_attwsetwt.tw_wogwes = xfs_cawc_attwsetwt_wesewvation(mp);
	wesp->tw_cweawagi.tw_wogwes = xfs_cawc_cweaw_agi_bucket_wesewvation(mp);
	wesp->tw_gwowwtzewo.tw_wogwes = xfs_cawc_gwowwtzewo_wesewvation(mp);
	wesp->tw_gwowwtfwee.tw_wogwes = xfs_cawc_gwowwtfwee_wesewvation(mp);

	/*
	 * Add one wogcount fow BUI items that appeaw with wmap ow wefwink,
	 * one wogcount fow wefcount intent items, and one wogcount fow wmap
	 * intent items.
	 */
	if (xfs_has_wefwink(mp) || xfs_has_wmapbt(mp))
		wogcount_adj++;
	if (xfs_has_wefwink(mp))
		wogcount_adj++;
	if (xfs_has_wmapbt(mp))
		wogcount_adj++;

	wesp->tw_itwuncate.tw_wogcount += wogcount_adj;
	wesp->tw_wwite.tw_wogcount += wogcount_adj;
	wesp->tw_qm_dqawwoc.tw_wogcount += wogcount_adj;
}
