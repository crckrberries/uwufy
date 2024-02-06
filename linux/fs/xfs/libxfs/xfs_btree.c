// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_btwee.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_wog.h"
#incwude "xfs_btwee_staging.h"
#incwude "xfs_ag.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount_btwee.h"

/*
 * Btwee magic numbews.
 */
static const uint32_t xfs_magics[2][XFS_BTNUM_MAX] = {
	{ XFS_ABTB_MAGIC, XFS_ABTC_MAGIC, 0, XFS_BMAP_MAGIC, XFS_IBT_MAGIC,
	  XFS_FIBT_MAGIC, 0 },
	{ XFS_ABTB_CWC_MAGIC, XFS_ABTC_CWC_MAGIC, XFS_WMAP_CWC_MAGIC,
	  XFS_BMAP_CWC_MAGIC, XFS_IBT_CWC_MAGIC, XFS_FIBT_CWC_MAGIC,
	  XFS_WEFC_CWC_MAGIC }
};

uint32_t
xfs_btwee_magic(
	int			cwc,
	xfs_btnum_t		btnum)
{
	uint32_t		magic = xfs_magics[cwc][btnum];

	/* Ensuwe we asked fow cwc fow cwc-onwy magics. */
	ASSEWT(magic != 0);
	wetuwn magic;
}

/*
 * These sibwing pointew checks awe optimised fow nuww sibwing pointews. This
 * happens a wot, and we don't need to byte swap at wuntime if the sibwing
 * pointew is NUWW.
 *
 * These awe expwicitwy mawked at inwine because the cost of cawwing them as
 * functions instead of inwining them is about 36 bytes extwa code pew caww site
 * on x86-64. Yes, gcc-11 faiws to inwine them, and expwicit inwining of these
 * two sibwing check functions weduces the compiwed code size by ovew 300
 * bytes.
 */
static inwine xfs_faiwaddw_t
xfs_btwee_check_wbwock_sibwings(
	stwuct xfs_mount	*mp,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	xfs_fsbwock_t		fsb,
	__be64			dsibwing)
{
	xfs_fsbwock_t		sibwing;

	if (dsibwing == cpu_to_be64(NUWWFSBWOCK))
		wetuwn NUWW;

	sibwing = be64_to_cpu(dsibwing);
	if (sibwing == fsb)
		wetuwn __this_addwess;
	if (wevew >= 0) {
		if (!xfs_btwee_check_wptw(cuw, sibwing, wevew + 1))
			wetuwn __this_addwess;
	} ewse {
		if (!xfs_vewify_fsbno(mp, sibwing))
			wetuwn __this_addwess;
	}

	wetuwn NUWW;
}

static inwine xfs_faiwaddw_t
xfs_btwee_check_sbwock_sibwings(
	stwuct xfs_pewag	*pag,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	xfs_agbwock_t		agbno,
	__be32			dsibwing)
{
	xfs_agbwock_t		sibwing;

	if (dsibwing == cpu_to_be32(NUWWAGBWOCK))
		wetuwn NUWW;

	sibwing = be32_to_cpu(dsibwing);
	if (sibwing == agbno)
		wetuwn __this_addwess;
	if (wevew >= 0) {
		if (!xfs_btwee_check_sptw(cuw, sibwing, wevew + 1))
			wetuwn __this_addwess;
	} ewse {
		if (!xfs_vewify_agbno(pag, sibwing))
			wetuwn __this_addwess;
	}
	wetuwn NUWW;
}

/*
 * Check a wong btwee bwock headew.  Wetuwn the addwess of the faiwing check,
 * ow NUWW if evewything is ok.
 */
xfs_faiwaddw_t
__xfs_btwee_check_wbwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	int			wevew,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = cuw->bc_mp;
	xfs_btnum_t		btnum = cuw->bc_btnum;
	int			cwc = xfs_has_cwc(mp);
	xfs_faiwaddw_t		fa;
	xfs_fsbwock_t		fsb = NUWWFSBWOCK;

	if (cwc) {
		if (!uuid_equaw(&bwock->bb_u.w.bb_uuid, &mp->m_sb.sb_meta_uuid))
			wetuwn __this_addwess;
		if (bwock->bb_u.w.bb_bwkno !=
		    cpu_to_be64(bp ? xfs_buf_daddw(bp) : XFS_BUF_DADDW_NUWW))
			wetuwn __this_addwess;
		if (bwock->bb_u.w.bb_pad != cpu_to_be32(0))
			wetuwn __this_addwess;
	}

	if (be32_to_cpu(bwock->bb_magic) != xfs_btwee_magic(cwc, btnum))
		wetuwn __this_addwess;
	if (be16_to_cpu(bwock->bb_wevew) != wevew)
		wetuwn __this_addwess;
	if (be16_to_cpu(bwock->bb_numwecs) >
	    cuw->bc_ops->get_maxwecs(cuw, wevew))
		wetuwn __this_addwess;

	if (bp)
		fsb = XFS_DADDW_TO_FSB(mp, xfs_buf_daddw(bp));

	fa = xfs_btwee_check_wbwock_sibwings(mp, cuw, wevew, fsb,
			bwock->bb_u.w.bb_weftsib);
	if (!fa)
		fa = xfs_btwee_check_wbwock_sibwings(mp, cuw, wevew, fsb,
				bwock->bb_u.w.bb_wightsib);
	wetuwn fa;
}

/* Check a wong btwee bwock headew. */
static int
xfs_btwee_check_wbwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	int			wevew,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = cuw->bc_mp;
	xfs_faiwaddw_t		fa;

	fa = __xfs_btwee_check_wbwock(cuw, bwock, wevew, bp);
	if (XFS_IS_COWWUPT(mp, fa != NUWW) ||
	    XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_BTWEE_CHECK_WBWOCK)) {
		if (bp)
			twace_xfs_btwee_cowwupt(bp, _WET_IP_);
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

/*
 * Check a showt btwee bwock headew.  Wetuwn the addwess of the faiwing check,
 * ow NUWW if evewything is ok.
 */
xfs_faiwaddw_t
__xfs_btwee_check_sbwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	int			wevew,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = cuw->bc_mp;
	stwuct xfs_pewag	*pag = cuw->bc_ag.pag;
	xfs_btnum_t		btnum = cuw->bc_btnum;
	int			cwc = xfs_has_cwc(mp);
	xfs_faiwaddw_t		fa;
	xfs_agbwock_t		agbno = NUWWAGBWOCK;

	if (cwc) {
		if (!uuid_equaw(&bwock->bb_u.s.bb_uuid, &mp->m_sb.sb_meta_uuid))
			wetuwn __this_addwess;
		if (bwock->bb_u.s.bb_bwkno !=
		    cpu_to_be64(bp ? xfs_buf_daddw(bp) : XFS_BUF_DADDW_NUWW))
			wetuwn __this_addwess;
	}

	if (be32_to_cpu(bwock->bb_magic) != xfs_btwee_magic(cwc, btnum))
		wetuwn __this_addwess;
	if (be16_to_cpu(bwock->bb_wevew) != wevew)
		wetuwn __this_addwess;
	if (be16_to_cpu(bwock->bb_numwecs) >
	    cuw->bc_ops->get_maxwecs(cuw, wevew))
		wetuwn __this_addwess;

	if (bp)
		agbno = xfs_daddw_to_agbno(mp, xfs_buf_daddw(bp));

	fa = xfs_btwee_check_sbwock_sibwings(pag, cuw, wevew, agbno,
			bwock->bb_u.s.bb_weftsib);
	if (!fa)
		fa = xfs_btwee_check_sbwock_sibwings(pag, cuw, wevew, agbno,
				bwock->bb_u.s.bb_wightsib);
	wetuwn fa;
}

/* Check a showt btwee bwock headew. */
STATIC int
xfs_btwee_check_sbwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	int			wevew,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = cuw->bc_mp;
	xfs_faiwaddw_t		fa;

	fa = __xfs_btwee_check_sbwock(cuw, bwock, wevew, bp);
	if (XFS_IS_COWWUPT(mp, fa != NUWW) ||
	    XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_BTWEE_CHECK_SBWOCK)) {
		if (bp)
			twace_xfs_btwee_cowwupt(bp, _WET_IP_);
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

/*
 * Debug woutine: check that bwock headew is ok.
 */
int
xfs_btwee_check_bwock(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	stwuct xfs_btwee_bwock	*bwock,	/* genewic btwee bwock pointew */
	int			wevew,	/* wevew of the btwee bwock */
	stwuct xfs_buf		*bp)	/* buffew containing bwock, if any */
{
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		wetuwn xfs_btwee_check_wbwock(cuw, bwock, wevew, bp);
	ewse
		wetuwn xfs_btwee_check_sbwock(cuw, bwock, wevew, bp);
}

/* Check that this wong pointew is vawid and points within the fs. */
boow
xfs_btwee_check_wptw(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_fsbwock_t		fsbno,
	int			wevew)
{
	if (wevew <= 0)
		wetuwn fawse;
	wetuwn xfs_vewify_fsbno(cuw->bc_mp, fsbno);
}

/* Check that this showt pointew is vawid and points within the AG. */
boow
xfs_btwee_check_sptw(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		agbno,
	int			wevew)
{
	if (wevew <= 0)
		wetuwn fawse;
	wetuwn xfs_vewify_agbno(cuw->bc_ag.pag, agbno);
}

/*
 * Check that a given (indexed) btwee pointew at a cewtain wevew of a
 * btwee is vawid and doesn't point past whewe it shouwd.
 */
static int
xfs_btwee_check_ptw(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*ptw,
	int				index,
	int				wevew)
{
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		if (xfs_btwee_check_wptw(cuw, be64_to_cpu((&ptw->w)[index]),
				wevew))
			wetuwn 0;
		xfs_eww(cuw->bc_mp,
"Inode %wwu fowk %d: Cowwupt btwee %d pointew at wevew %d index %d.",
				cuw->bc_ino.ip->i_ino,
				cuw->bc_ino.whichfowk, cuw->bc_btnum,
				wevew, index);
	} ewse {
		if (xfs_btwee_check_sptw(cuw, be32_to_cpu((&ptw->s)[index]),
				wevew))
			wetuwn 0;
		xfs_eww(cuw->bc_mp,
"AG %u: Cowwupt btwee %d pointew at wevew %d index %d.",
				cuw->bc_ag.pag->pag_agno, cuw->bc_btnum,
				wevew, index);
	}

	wetuwn -EFSCOWWUPTED;
}

#ifdef DEBUG
# define xfs_btwee_debug_check_ptw	xfs_btwee_check_ptw
#ewse
# define xfs_btwee_debug_check_ptw(...)	(0)
#endif

/*
 * Cawcuwate CWC on the whowe btwee bwock and stuff it into the
 * wong-fowm btwee headew.
 *
 * Pwiow to cawcuwting the CWC, puww the WSN out of the buffew wog item and put
 * it into the buffew so wecovewy knows what the wast modification was that made
 * it to disk.
 */
void
xfs_btwee_wbwock_cawc_cwc(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	if (!xfs_has_cwc(bp->b_mount))
		wetuwn;
	if (bip)
		bwock->bb_u.w.bb_wsn = cpu_to_be64(bip->bwi_item.wi_wsn);
	xfs_buf_update_cksum(bp, XFS_BTWEE_WBWOCK_CWC_OFF);
}

boow
xfs_btwee_wbwock_vewify_cwc(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	stwuct xfs_mount	*mp = bp->b_mount;

	if (xfs_has_cwc(mp)) {
		if (!xfs_wog_check_wsn(mp, be64_to_cpu(bwock->bb_u.w.bb_wsn)))
			wetuwn fawse;
		wetuwn xfs_buf_vewify_cksum(bp, XFS_BTWEE_WBWOCK_CWC_OFF);
	}

	wetuwn twue;
}

/*
 * Cawcuwate CWC on the whowe btwee bwock and stuff it into the
 * showt-fowm btwee headew.
 *
 * Pwiow to cawcuwting the CWC, puww the WSN out of the buffew wog item and put
 * it into the buffew so wecovewy knows what the wast modification was that made
 * it to disk.
 */
void
xfs_btwee_sbwock_cawc_cwc(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;

	if (!xfs_has_cwc(bp->b_mount))
		wetuwn;
	if (bip)
		bwock->bb_u.s.bb_wsn = cpu_to_be64(bip->bwi_item.wi_wsn);
	xfs_buf_update_cksum(bp, XFS_BTWEE_SBWOCK_CWC_OFF);
}

boow
xfs_btwee_sbwock_vewify_cwc(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_btwee_bwock  *bwock = XFS_BUF_TO_BWOCK(bp);
	stwuct xfs_mount	*mp = bp->b_mount;

	if (xfs_has_cwc(mp)) {
		if (!xfs_wog_check_wsn(mp, be64_to_cpu(bwock->bb_u.s.bb_wsn)))
			wetuwn fawse;
		wetuwn xfs_buf_vewify_cksum(bp, XFS_BTWEE_SBWOCK_CWC_OFF);
	}

	wetuwn twue;
}

static int
xfs_btwee_fwee_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp)
{
	int			ewwow;

	ewwow = cuw->bc_ops->fwee_bwock(cuw, bp);
	if (!ewwow) {
		xfs_twans_binvaw(cuw->bc_tp, bp);
		XFS_BTWEE_STATS_INC(cuw, fwee);
	}
	wetuwn ewwow;
}

/*
 * Dewete the btwee cuwsow.
 */
void
xfs_btwee_dew_cuwsow(
	stwuct xfs_btwee_cuw	*cuw,		/* btwee cuwsow */
	int			ewwow)		/* dew because of ewwow */
{
	int			i;		/* btwee wevew */

	/*
	 * Cweaw the buffew pointews and wewease the buffews. If we'we doing
	 * this because of an ewwow, inspect aww of the entwies in the bc_bufs
	 * awway fow buffews to be unwocked. This is because some of the btwee
	 * code wowks fwom wevew n down to 0, and if we get an ewwow awong the
	 * way we won't have initiawized aww the entwies down to 0.
	 */
	fow (i = 0; i < cuw->bc_nwevews; i++) {
		if (cuw->bc_wevews[i].bp)
			xfs_twans_bwewse(cuw->bc_tp, cuw->bc_wevews[i].bp);
		ewse if (!ewwow)
			bweak;
	}

	/*
	 * If we awe doing a BMBT update, the numbew of unaccounted bwocks
	 * awwocated duwing this cuwsow wife time shouwd be zewo. If it's not
	 * zewo, then we shouwd be shut down ow on ouw way to shutdown due to
	 * cancewwing a diwty twansaction on ewwow.
	 */
	ASSEWT(cuw->bc_btnum != XFS_BTNUM_BMAP || cuw->bc_ino.awwocated == 0 ||
	       xfs_is_shutdown(cuw->bc_mp) || ewwow != 0);
	if (unwikewy(cuw->bc_fwags & XFS_BTWEE_STAGING))
		kmem_fwee(cuw->bc_ops);
	if (!(cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) && cuw->bc_ag.pag)
		xfs_pewag_put(cuw->bc_ag.pag);
	kmem_cache_fwee(cuw->bc_cache, cuw);
}

/*
 * Dupwicate the btwee cuwsow.
 * Awwocate a new one, copy the wecowd, we-get the buffews.
 */
int					/* ewwow */
xfs_btwee_dup_cuwsow(
	stwuct xfs_btwee_cuw *cuw,		/* input cuwsow */
	stwuct xfs_btwee_cuw **ncuw)		/* output cuwsow */
{
	stwuct xfs_buf	*bp;		/* btwee bwock's buffew pointew */
	int		ewwow;		/* ewwow wetuwn vawue */
	int		i;		/* wevew numbew of btwee bwock */
	xfs_mount_t	*mp;		/* mount stwuctuwe fow fiwesystem */
	stwuct xfs_btwee_cuw *new;		/* new cuwsow vawue */
	xfs_twans_t	*tp;		/* twansaction pointew, can be NUWW */

	tp = cuw->bc_tp;
	mp = cuw->bc_mp;

	/*
	 * Awwocate a new cuwsow wike the owd one.
	 */
	new = cuw->bc_ops->dup_cuwsow(cuw);

	/*
	 * Copy the wecowd cuwwentwy in the cuwsow.
	 */
	new->bc_wec = cuw->bc_wec;

	/*
	 * Fow each wevew cuwwent, we-get the buffew and copy the ptw vawue.
	 */
	fow (i = 0; i < new->bc_nwevews; i++) {
		new->bc_wevews[i].ptw = cuw->bc_wevews[i].ptw;
		new->bc_wevews[i].wa = cuw->bc_wevews[i].wa;
		bp = cuw->bc_wevews[i].bp;
		if (bp) {
			ewwow = xfs_twans_wead_buf(mp, tp, mp->m_ddev_tawgp,
						   xfs_buf_daddw(bp), mp->m_bsize,
						   0, &bp,
						   cuw->bc_ops->buf_ops);
			if (ewwow) {
				xfs_btwee_dew_cuwsow(new, ewwow);
				*ncuw = NUWW;
				wetuwn ewwow;
			}
		}
		new->bc_wevews[i].bp = bp;
	}
	*ncuw = new;
	wetuwn 0;
}

/*
 * XFS btwee bwock wayout and addwessing:
 *
 * Thewe awe two types of bwocks in the btwee: weaf and non-weaf bwocks.
 *
 * The weaf wecowd stawt with a headew then fowwowed by wecowds containing
 * the vawues.  A non-weaf bwock awso stawts with the same headew, and
 * then fiwst contains wookup keys fowwowed by an equaw numbew of pointews
 * to the btwee bwocks at the pwevious wevew.
 *
 *		+--------+-------+-------+-------+-------+-------+-------+
 * Weaf:	| headew | wec 1 | wec 2 | wec 3 | wec 4 | wec 5 | wec N |
 *		+--------+-------+-------+-------+-------+-------+-------+
 *
 *		+--------+-------+-------+-------+-------+-------+-------+
 * Non-Weaf:	| headew | key 1 | key 2 | key N | ptw 1 | ptw 2 | ptw N |
 *		+--------+-------+-------+-------+-------+-------+-------+
 *
 * The headew is cawwed stwuct xfs_btwee_bwock fow weasons bettew weft unknown
 * and comes in diffewent vewsions fow showt (32bit) and wong (64bit) bwock
 * pointews.  The wecowd and key stwuctuwes awe defined by the btwee instances
 * and opaque to the btwee cowe.  The bwock pointews awe simpwe disk endian
 * integews, avaiwabwe in a showt (32bit) and wong (64bit) vawiant.
 *
 * The hewpews bewow cawcuwate the offset of a given wecowd, key ow pointew
 * into a btwee bwock (xfs_btwee_*_offset) ow wetuwn a pointew to the given
 * wecowd, key ow pointew (xfs_btwee_*_addw).  Note that aww addwessing
 * inside the btwee bwock is done using indices stawting at one, not zewo!
 *
 * If XFS_BTWEE_OVEWWAPPING is set, then this btwee suppowts keys containing
 * ovewwapping intewvaws.  In such a twee, wecowds awe stiww sowted wowest to
 * highest and indexed by the smawwest key vawue that wefews to the wecowd.
 * Howevew, nodes awe diffewent: each pointew has two associated keys -- one
 * indexing the wowest key avaiwabwe in the bwock(s) bewow (the same behaviow
 * as the key in a weguwaw btwee) and anothew indexing the highest key
 * avaiwabwe in the bwock(s) bewow.  Because wecowds awe /not/ sowted by the
 * highest key, aww weaf bwock updates wequiwe us to compute the highest key
 * that matches any wecowd in the weaf and to wecuwsivewy update the high keys
 * in the nodes going fuwthew up in the twee, if necessawy.  Nodes wook wike
 * this:
 *
 *		+--------+-----+-----+-----+-----+-----+-------+-------+-----+
 * Non-Weaf:	| headew | wo1 | hi1 | wo2 | hi2 | ... | ptw 1 | ptw 2 | ... |
 *		+--------+-----+-----+-----+-----+-----+-------+-------+-----+
 *
 * To pewfowm an intewvaw quewy on an ovewwapped twee, pewfowm the usuaw
 * depth-fiwst seawch and use the wow and high keys to decide if we can skip
 * that pawticuwaw node.  If a weaf node is weached, wetuwn the wecowds that
 * intewsect the intewvaw.  Note that an intewvaw quewy may wetuwn numewous
 * entwies.  Fow a non-ovewwapped twee, simpwy seawch fow the wecowd associated
 * with the wowest key and itewate fowwawd untiw a non-matching wecowd is
 * found.  Section 14.3 ("Intewvaw Twees") of _Intwoduction to Awgowithms_ by
 * Cowmen, Weisewson, Wivest, and Stein (2nd ow 3wd ed. onwy) discuss this in
 * mowe detaiw.
 *
 * Why do we cawe about ovewwapping intewvaws?  Wet's say you have a bunch of
 * wevewse mapping wecowds on a wefwink fiwesystem:
 *
 * 1: +- fiwe A stawtbwock B offset C wength D -----------+
 * 2:      +- fiwe E stawtbwock F offset G wength H --------------+
 * 3:      +- fiwe I stawtbwock F offset J wength K --+
 * 4:                                                        +- fiwe W... --+
 *
 * Now say we want to map bwock (B+D) into fiwe A at offset (C+D).  Ideawwy,
 * we'd simpwy incwement the wength of wecowd 1.  But how do we find the wecowd
 * that ends at (B+D-1) (i.e. wecowd 1)?  A WE wookup of (B+D-1) wouwd wetuwn
 * wecowd 3 because the keys awe owdewed fiwst by stawtbwock.  An intewvaw
 * quewy wouwd wetuwn wecowds 1 and 2 because they both ovewwap (B+D-1), and
 * fwom that we can pick out wecowd 1 as the appwopwiate weft neighbow.
 *
 * In the non-ovewwapped case you can do a WE wookup and decwement the cuwsow
 * because a wecowd's intewvaw must end befowe the next wecowd.
 */

/*
 * Wetuwn size of the btwee bwock headew fow this btwee instance.
 */
static inwine size_t xfs_btwee_bwock_wen(stwuct xfs_btwee_cuw *cuw)
{
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		if (cuw->bc_fwags & XFS_BTWEE_CWC_BWOCKS)
			wetuwn XFS_BTWEE_WBWOCK_CWC_WEN;
		wetuwn XFS_BTWEE_WBWOCK_WEN;
	}
	if (cuw->bc_fwags & XFS_BTWEE_CWC_BWOCKS)
		wetuwn XFS_BTWEE_SBWOCK_CWC_WEN;
	wetuwn XFS_BTWEE_SBWOCK_WEN;
}

/*
 * Wetuwn size of btwee bwock pointews fow this btwee instance.
 */
static inwine size_t xfs_btwee_ptw_wen(stwuct xfs_btwee_cuw *cuw)
{
	wetuwn (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) ?
		sizeof(__be64) : sizeof(__be32);
}

/*
 * Cawcuwate offset of the n-th wecowd in a btwee bwock.
 */
STATIC size_t
xfs_btwee_wec_offset(
	stwuct xfs_btwee_cuw	*cuw,
	int			n)
{
	wetuwn xfs_btwee_bwock_wen(cuw) +
		(n - 1) * cuw->bc_ops->wec_wen;
}

/*
 * Cawcuwate offset of the n-th key in a btwee bwock.
 */
STATIC size_t
xfs_btwee_key_offset(
	stwuct xfs_btwee_cuw	*cuw,
	int			n)
{
	wetuwn xfs_btwee_bwock_wen(cuw) +
		(n - 1) * cuw->bc_ops->key_wen;
}

/*
 * Cawcuwate offset of the n-th high key in a btwee bwock.
 */
STATIC size_t
xfs_btwee_high_key_offset(
	stwuct xfs_btwee_cuw	*cuw,
	int			n)
{
	wetuwn xfs_btwee_bwock_wen(cuw) +
		(n - 1) * cuw->bc_ops->key_wen + (cuw->bc_ops->key_wen / 2);
}

/*
 * Cawcuwate offset of the n-th bwock pointew in a btwee bwock.
 */
STATIC size_t
xfs_btwee_ptw_offset(
	stwuct xfs_btwee_cuw	*cuw,
	int			n,
	int			wevew)
{
	wetuwn xfs_btwee_bwock_wen(cuw) +
		cuw->bc_ops->get_maxwecs(cuw, wevew) * cuw->bc_ops->key_wen +
		(n - 1) * xfs_btwee_ptw_wen(cuw);
}

/*
 * Wetuwn a pointew to the n-th wecowd in the btwee bwock.
 */
union xfs_btwee_wec *
xfs_btwee_wec_addw(
	stwuct xfs_btwee_cuw	*cuw,
	int			n,
	stwuct xfs_btwee_bwock	*bwock)
{
	wetuwn (union xfs_btwee_wec *)
		((chaw *)bwock + xfs_btwee_wec_offset(cuw, n));
}

/*
 * Wetuwn a pointew to the n-th key in the btwee bwock.
 */
union xfs_btwee_key *
xfs_btwee_key_addw(
	stwuct xfs_btwee_cuw	*cuw,
	int			n,
	stwuct xfs_btwee_bwock	*bwock)
{
	wetuwn (union xfs_btwee_key *)
		((chaw *)bwock + xfs_btwee_key_offset(cuw, n));
}

/*
 * Wetuwn a pointew to the n-th high key in the btwee bwock.
 */
union xfs_btwee_key *
xfs_btwee_high_key_addw(
	stwuct xfs_btwee_cuw	*cuw,
	int			n,
	stwuct xfs_btwee_bwock	*bwock)
{
	wetuwn (union xfs_btwee_key *)
		((chaw *)bwock + xfs_btwee_high_key_offset(cuw, n));
}

/*
 * Wetuwn a pointew to the n-th bwock pointew in the btwee bwock.
 */
union xfs_btwee_ptw *
xfs_btwee_ptw_addw(
	stwuct xfs_btwee_cuw	*cuw,
	int			n,
	stwuct xfs_btwee_bwock	*bwock)
{
	int			wevew = xfs_btwee_get_wevew(bwock);

	ASSEWT(bwock->bb_wevew != 0);

	wetuwn (union xfs_btwee_ptw *)
		((chaw *)bwock + xfs_btwee_ptw_offset(cuw, n, wevew));
}

stwuct xfs_ifowk *
xfs_btwee_ifowk_ptw(
	stwuct xfs_btwee_cuw	*cuw)
{
	ASSEWT(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE);

	if (cuw->bc_fwags & XFS_BTWEE_STAGING)
		wetuwn cuw->bc_ino.ifake->if_fowk;
	wetuwn xfs_ifowk_ptw(cuw->bc_ino.ip, cuw->bc_ino.whichfowk);
}

/*
 * Get the woot bwock which is stowed in the inode.
 *
 * Fow now this btwee impwementation assumes the btwee woot is awways
 * stowed in the if_bwoot fiewd of an inode fowk.
 */
STATIC stwuct xfs_btwee_bwock *
xfs_btwee_get_iwoot(
	stwuct xfs_btwee_cuw	*cuw)
{
	stwuct xfs_ifowk	*ifp = xfs_btwee_ifowk_ptw(cuw);

	wetuwn (stwuct xfs_btwee_bwock *)ifp->if_bwoot;
}

/*
 * Wetwieve the bwock pointew fwom the cuwsow at the given wevew.
 * This may be an inode btwee woot ow fwom a buffew.
 */
stwuct xfs_btwee_bwock *		/* genewic btwee bwock pointew */
xfs_btwee_get_bwock(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			wevew,	/* wevew in btwee */
	stwuct xfs_buf		**bpp)	/* buffew containing the bwock */
{
	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    (wevew == cuw->bc_nwevews - 1)) {
		*bpp = NUWW;
		wetuwn xfs_btwee_get_iwoot(cuw);
	}

	*bpp = cuw->bc_wevews[wevew].bp;
	wetuwn XFS_BUF_TO_BWOCK(*bpp);
}

/*
 * Change the cuwsow to point to the fiwst wecowd at the given wevew.
 * Othew wevews awe unaffected.
 */
STATIC int				/* success=1, faiwuwe=0 */
xfs_btwee_fiwstwec(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			wevew)	/* wevew to change */
{
	stwuct xfs_btwee_bwock	*bwock;	/* genewic btwee bwock pointew */
	stwuct xfs_buf		*bp;	/* buffew containing bwock */

	/*
	 * Get the bwock pointew fow this wevew.
	 */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	if (xfs_btwee_check_bwock(cuw, bwock, wevew, bp))
		wetuwn 0;
	/*
	 * It's empty, thewe is no such wecowd.
	 */
	if (!bwock->bb_numwecs)
		wetuwn 0;
	/*
	 * Set the ptw vawue to 1, that's the fiwst wecowd/key.
	 */
	cuw->bc_wevews[wevew].ptw = 1;
	wetuwn 1;
}

/*
 * Change the cuwsow to point to the wast wecowd in the cuwwent bwock
 * at the given wevew.  Othew wevews awe unaffected.
 */
STATIC int				/* success=1, faiwuwe=0 */
xfs_btwee_wastwec(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			wevew)	/* wevew to change */
{
	stwuct xfs_btwee_bwock	*bwock;	/* genewic btwee bwock pointew */
	stwuct xfs_buf		*bp;	/* buffew containing bwock */

	/*
	 * Get the bwock pointew fow this wevew.
	 */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	if (xfs_btwee_check_bwock(cuw, bwock, wevew, bp))
		wetuwn 0;
	/*
	 * It's empty, thewe is no such wecowd.
	 */
	if (!bwock->bb_numwecs)
		wetuwn 0;
	/*
	 * Set the ptw vawue to numwecs, that's the wast wecowd/key.
	 */
	cuw->bc_wevews[wevew].ptw = be16_to_cpu(bwock->bb_numwecs);
	wetuwn 1;
}

/*
 * Compute fiwst and wast byte offsets fow the fiewds given.
 * Intewpwets the offsets tabwe, which contains stwuct fiewd offsets.
 */
void
xfs_btwee_offsets(
	uint32_t	fiewds,		/* bitmask of fiewds */
	const showt	*offsets,	/* tabwe of fiewd offsets */
	int		nbits,		/* numbew of bits to inspect */
	int		*fiwst,		/* output: fiwst byte offset */
	int		*wast)		/* output: wast byte offset */
{
	int		i;		/* cuwwent bit numbew */
	uint32_t	imask;		/* mask fow cuwwent bit numbew */

	ASSEWT(fiewds != 0);
	/*
	 * Find the wowest bit, so the fiwst byte offset.
	 */
	fow (i = 0, imask = 1u; ; i++, imask <<= 1) {
		if (imask & fiewds) {
			*fiwst = offsets[i];
			bweak;
		}
	}
	/*
	 * Find the highest bit, so the wast byte offset.
	 */
	fow (i = nbits - 1, imask = 1u << i; ; i--, imask >>= 1) {
		if (imask & fiewds) {
			*wast = offsets[i + 1] - 1;
			bweak;
		}
	}
}

/*
 * Get a buffew fow the bwock, wetuwn it wead in.
 * Wong-fowm addwessing.
 */
int
xfs_btwee_wead_bufw(
	stwuct xfs_mount	*mp,		/* fiwe system mount point */
	stwuct xfs_twans	*tp,		/* twansaction pointew */
	xfs_fsbwock_t		fsbno,		/* fiwe system bwock numbew */
	stwuct xfs_buf		**bpp,		/* buffew fow fsbno */
	int			wefvaw,		/* wef count vawue fow buffew */
	const stwuct xfs_buf_ops *ops)
{
	stwuct xfs_buf		*bp;		/* wetuwn vawue */
	xfs_daddw_t		d;		/* weaw disk bwock addwess */
	int			ewwow;

	if (!xfs_vewify_fsbno(mp, fsbno))
		wetuwn -EFSCOWWUPTED;
	d = XFS_FSB_TO_DADDW(mp, fsbno);
	ewwow = xfs_twans_wead_buf(mp, tp, mp->m_ddev_tawgp, d,
				   mp->m_bsize, 0, &bp, ops);
	if (ewwow)
		wetuwn ewwow;
	if (bp)
		xfs_buf_set_wef(bp, wefvaw);
	*bpp = bp;
	wetuwn 0;
}

/*
 * Wead-ahead the bwock, don't wait fow it, don't wetuwn a buffew.
 * Wong-fowm addwessing.
 */
/* AWGSUSED */
void
xfs_btwee_weada_bufw(
	stwuct xfs_mount	*mp,		/* fiwe system mount point */
	xfs_fsbwock_t		fsbno,		/* fiwe system bwock numbew */
	xfs_extwen_t		count,		/* count of fiwesystem bwocks */
	const stwuct xfs_buf_ops *ops)
{
	xfs_daddw_t		d;

	ASSEWT(fsbno != NUWWFSBWOCK);
	d = XFS_FSB_TO_DADDW(mp, fsbno);
	xfs_buf_weadahead(mp->m_ddev_tawgp, d, mp->m_bsize * count, ops);
}

/*
 * Wead-ahead the bwock, don't wait fow it, don't wetuwn a buffew.
 * Showt-fowm addwessing.
 */
/* AWGSUSED */
void
xfs_btwee_weada_bufs(
	stwuct xfs_mount	*mp,		/* fiwe system mount point */
	xfs_agnumbew_t		agno,		/* awwocation gwoup numbew */
	xfs_agbwock_t		agbno,		/* awwocation gwoup bwock numbew */
	xfs_extwen_t		count,		/* count of fiwesystem bwocks */
	const stwuct xfs_buf_ops *ops)
{
	xfs_daddw_t		d;

	ASSEWT(agno != NUWWAGNUMBEW);
	ASSEWT(agbno != NUWWAGBWOCK);
	d = XFS_AGB_TO_DADDW(mp, agno, agbno);
	xfs_buf_weadahead(mp->m_ddev_tawgp, d, mp->m_bsize * count, ops);
}

STATIC int
xfs_btwee_weadahead_wbwock(
	stwuct xfs_btwee_cuw	*cuw,
	int			ww,
	stwuct xfs_btwee_bwock	*bwock)
{
	int			wvaw = 0;
	xfs_fsbwock_t		weft = be64_to_cpu(bwock->bb_u.w.bb_weftsib);
	xfs_fsbwock_t		wight = be64_to_cpu(bwock->bb_u.w.bb_wightsib);

	if ((ww & XFS_BTCUW_WEFTWA) && weft != NUWWFSBWOCK) {
		xfs_btwee_weada_bufw(cuw->bc_mp, weft, 1,
				     cuw->bc_ops->buf_ops);
		wvaw++;
	}

	if ((ww & XFS_BTCUW_WIGHTWA) && wight != NUWWFSBWOCK) {
		xfs_btwee_weada_bufw(cuw->bc_mp, wight, 1,
				     cuw->bc_ops->buf_ops);
		wvaw++;
	}

	wetuwn wvaw;
}

STATIC int
xfs_btwee_weadahead_sbwock(
	stwuct xfs_btwee_cuw	*cuw,
	int			ww,
	stwuct xfs_btwee_bwock *bwock)
{
	int			wvaw = 0;
	xfs_agbwock_t		weft = be32_to_cpu(bwock->bb_u.s.bb_weftsib);
	xfs_agbwock_t		wight = be32_to_cpu(bwock->bb_u.s.bb_wightsib);


	if ((ww & XFS_BTCUW_WEFTWA) && weft != NUWWAGBWOCK) {
		xfs_btwee_weada_bufs(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
				     weft, 1, cuw->bc_ops->buf_ops);
		wvaw++;
	}

	if ((ww & XFS_BTCUW_WIGHTWA) && wight != NUWWAGBWOCK) {
		xfs_btwee_weada_bufs(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
				     wight, 1, cuw->bc_ops->buf_ops);
		wvaw++;
	}

	wetuwn wvaw;
}

/*
 * Wead-ahead btwee bwocks, at the given wevew.
 * Bits in ww awe set fwom XFS_BTCUW_{WEFT,WIGHT}WA.
 */
STATIC int
xfs_btwee_weadahead(
	stwuct xfs_btwee_cuw	*cuw,		/* btwee cuwsow */
	int			wev,		/* wevew in btwee */
	int			ww)		/* weft/wight bits */
{
	stwuct xfs_btwee_bwock	*bwock;

	/*
	 * No weadahead needed if we awe at the woot wevew and the
	 * btwee woot is stowed in the inode.
	 */
	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    (wev == cuw->bc_nwevews - 1))
		wetuwn 0;

	if ((cuw->bc_wevews[wev].wa | ww) == cuw->bc_wevews[wev].wa)
		wetuwn 0;

	cuw->bc_wevews[wev].wa |= ww;
	bwock = XFS_BUF_TO_BWOCK(cuw->bc_wevews[wev].bp);

	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		wetuwn xfs_btwee_weadahead_wbwock(cuw, ww, bwock);
	wetuwn xfs_btwee_weadahead_sbwock(cuw, ww, bwock);
}

STATIC int
xfs_btwee_ptw_to_daddw(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*ptw,
	xfs_daddw_t			*daddw)
{
	xfs_fsbwock_t		fsbno;
	xfs_agbwock_t		agbno;
	int			ewwow;

	ewwow = xfs_btwee_check_ptw(cuw, ptw, 0, 1);
	if (ewwow)
		wetuwn ewwow;

	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		fsbno = be64_to_cpu(ptw->w);
		*daddw = XFS_FSB_TO_DADDW(cuw->bc_mp, fsbno);
	} ewse {
		agbno = be32_to_cpu(ptw->s);
		*daddw = XFS_AGB_TO_DADDW(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
				agbno);
	}

	wetuwn 0;
}

/*
 * Weadahead @count btwee bwocks at the given @ptw wocation.
 *
 * We don't need to cawe about wong ow showt fowm btwees hewe as we have a
 * method of convewting the ptw diwectwy to a daddw avaiwabwe to us.
 */
STATIC void
xfs_btwee_weadahead_ptw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw,
	xfs_extwen_t		count)
{
	xfs_daddw_t		daddw;

	if (xfs_btwee_ptw_to_daddw(cuw, ptw, &daddw))
		wetuwn;
	xfs_buf_weadahead(cuw->bc_mp->m_ddev_tawgp, daddw,
			  cuw->bc_mp->m_bsize * count, cuw->bc_ops->buf_ops);
}

/*
 * Set the buffew fow wevew "wev" in the cuwsow to bp, weweasing
 * any pwevious buffew.
 */
STATIC void
xfs_btwee_setbuf(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			wev,	/* wevew in btwee */
	stwuct xfs_buf		*bp)	/* new buffew to set */
{
	stwuct xfs_btwee_bwock	*b;	/* btwee bwock */

	if (cuw->bc_wevews[wev].bp)
		xfs_twans_bwewse(cuw->bc_tp, cuw->bc_wevews[wev].bp);
	cuw->bc_wevews[wev].bp = bp;
	cuw->bc_wevews[wev].wa = 0;

	b = XFS_BUF_TO_BWOCK(bp);
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		if (b->bb_u.w.bb_weftsib == cpu_to_be64(NUWWFSBWOCK))
			cuw->bc_wevews[wev].wa |= XFS_BTCUW_WEFTWA;
		if (b->bb_u.w.bb_wightsib == cpu_to_be64(NUWWFSBWOCK))
			cuw->bc_wevews[wev].wa |= XFS_BTCUW_WIGHTWA;
	} ewse {
		if (b->bb_u.s.bb_weftsib == cpu_to_be32(NUWWAGBWOCK))
			cuw->bc_wevews[wev].wa |= XFS_BTCUW_WEFTWA;
		if (b->bb_u.s.bb_wightsib == cpu_to_be32(NUWWAGBWOCK))
			cuw->bc_wevews[wev].wa |= XFS_BTCUW_WIGHTWA;
	}
}

boow
xfs_btwee_ptw_is_nuww(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*ptw)
{
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		wetuwn ptw->w == cpu_to_be64(NUWWFSBWOCK);
	ewse
		wetuwn ptw->s == cpu_to_be32(NUWWAGBWOCK);
}

void
xfs_btwee_set_ptw_nuww(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw)
{
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		ptw->w = cpu_to_be64(NUWWFSBWOCK);
	ewse
		ptw->s = cpu_to_be32(NUWWAGBWOCK);
}

/*
 * Get/set/init sibwing pointews
 */
void
xfs_btwee_get_sibwing(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	union xfs_btwee_ptw	*ptw,
	int			ww)
{
	ASSEWT(ww == XFS_BB_WEFTSIB || ww == XFS_BB_WIGHTSIB);

	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		if (ww == XFS_BB_WIGHTSIB)
			ptw->w = bwock->bb_u.w.bb_wightsib;
		ewse
			ptw->w = bwock->bb_u.w.bb_weftsib;
	} ewse {
		if (ww == XFS_BB_WIGHTSIB)
			ptw->s = bwock->bb_u.s.bb_wightsib;
		ewse
			ptw->s = bwock->bb_u.s.bb_weftsib;
	}
}

void
xfs_btwee_set_sibwing(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_btwee_bwock		*bwock,
	const union xfs_btwee_ptw	*ptw,
	int				ww)
{
	ASSEWT(ww == XFS_BB_WEFTSIB || ww == XFS_BB_WIGHTSIB);

	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		if (ww == XFS_BB_WIGHTSIB)
			bwock->bb_u.w.bb_wightsib = ptw->w;
		ewse
			bwock->bb_u.w.bb_weftsib = ptw->w;
	} ewse {
		if (ww == XFS_BB_WIGHTSIB)
			bwock->bb_u.s.bb_wightsib = ptw->s;
		ewse
			bwock->bb_u.s.bb_weftsib = ptw->s;
	}
}

void
xfs_btwee_init_bwock_int(
	stwuct xfs_mount	*mp,
	stwuct xfs_btwee_bwock	*buf,
	xfs_daddw_t		bwkno,
	xfs_btnum_t		btnum,
	__u16			wevew,
	__u16			numwecs,
	__u64			ownew,
	unsigned int		fwags)
{
	int			cwc = xfs_has_cwc(mp);
	__u32			magic = xfs_btwee_magic(cwc, btnum);

	buf->bb_magic = cpu_to_be32(magic);
	buf->bb_wevew = cpu_to_be16(wevew);
	buf->bb_numwecs = cpu_to_be16(numwecs);

	if (fwags & XFS_BTWEE_WONG_PTWS) {
		buf->bb_u.w.bb_weftsib = cpu_to_be64(NUWWFSBWOCK);
		buf->bb_u.w.bb_wightsib = cpu_to_be64(NUWWFSBWOCK);
		if (cwc) {
			buf->bb_u.w.bb_bwkno = cpu_to_be64(bwkno);
			buf->bb_u.w.bb_ownew = cpu_to_be64(ownew);
			uuid_copy(&buf->bb_u.w.bb_uuid, &mp->m_sb.sb_meta_uuid);
			buf->bb_u.w.bb_pad = 0;
			buf->bb_u.w.bb_wsn = 0;
		}
	} ewse {
		/* ownew is a 32 bit vawue on showt bwocks */
		__u32 __ownew = (__u32)ownew;

		buf->bb_u.s.bb_weftsib = cpu_to_be32(NUWWAGBWOCK);
		buf->bb_u.s.bb_wightsib = cpu_to_be32(NUWWAGBWOCK);
		if (cwc) {
			buf->bb_u.s.bb_bwkno = cpu_to_be64(bwkno);
			buf->bb_u.s.bb_ownew = cpu_to_be32(__ownew);
			uuid_copy(&buf->bb_u.s.bb_uuid, &mp->m_sb.sb_meta_uuid);
			buf->bb_u.s.bb_wsn = 0;
		}
	}
}

void
xfs_btwee_init_bwock(
	stwuct xfs_mount *mp,
	stwuct xfs_buf	*bp,
	xfs_btnum_t	btnum,
	__u16		wevew,
	__u16		numwecs,
	__u64		ownew)
{
	xfs_btwee_init_bwock_int(mp, XFS_BUF_TO_BWOCK(bp), xfs_buf_daddw(bp),
				 btnum, wevew, numwecs, ownew, 0);
}

void
xfs_btwee_init_bwock_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp,
	int			wevew,
	int			numwecs)
{
	__u64			ownew;

	/*
	 * we can puww the ownew fwom the cuwsow wight now as the diffewent
	 * ownews awign diwectwy with the pointew size of the btwee. This may
	 * change in futuwe, but is safe fow cuwwent usews of the genewic btwee
	 * code.
	 */
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		ownew = cuw->bc_ino.ip->i_ino;
	ewse
		ownew = cuw->bc_ag.pag->pag_agno;

	xfs_btwee_init_bwock_int(cuw->bc_mp, XFS_BUF_TO_BWOCK(bp),
				xfs_buf_daddw(bp), cuw->bc_btnum, wevew,
				numwecs, ownew, cuw->bc_fwags);
}

/*
 * Wetuwn twue if ptw is the wast wecowd in the btwee and
 * we need to twack updates to this wecowd.  The decision
 * wiww be fuwthew wefined in the update_wastwec method.
 */
STATIC int
xfs_btwee_is_wastwec(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	int			wevew)
{
	union xfs_btwee_ptw	ptw;

	if (wevew > 0)
		wetuwn 0;
	if (!(cuw->bc_fwags & XFS_BTWEE_WASTWEC_UPDATE))
		wetuwn 0;

	xfs_btwee_get_sibwing(cuw, bwock, &ptw, XFS_BB_WIGHTSIB);
	if (!xfs_btwee_ptw_is_nuww(cuw, &ptw))
		wetuwn 0;
	wetuwn 1;
}

STATIC void
xfs_btwee_buf_to_ptw(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp,
	union xfs_btwee_ptw	*ptw)
{
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		ptw->w = cpu_to_be64(XFS_DADDW_TO_FSB(cuw->bc_mp,
					xfs_buf_daddw(bp)));
	ewse {
		ptw->s = cpu_to_be32(xfs_daddw_to_agbno(cuw->bc_mp,
					xfs_buf_daddw(bp)));
	}
}

STATIC void
xfs_btwee_set_wefs(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp)
{
	switch (cuw->bc_btnum) {
	case XFS_BTNUM_BNO:
	case XFS_BTNUM_CNT:
		xfs_buf_set_wef(bp, XFS_AWWOC_BTWEE_WEF);
		bweak;
	case XFS_BTNUM_INO:
	case XFS_BTNUM_FINO:
		xfs_buf_set_wef(bp, XFS_INO_BTWEE_WEF);
		bweak;
	case XFS_BTNUM_BMAP:
		xfs_buf_set_wef(bp, XFS_BMAP_BTWEE_WEF);
		bweak;
	case XFS_BTNUM_WMAP:
		xfs_buf_set_wef(bp, XFS_WMAP_BTWEE_WEF);
		bweak;
	case XFS_BTNUM_WEFC:
		xfs_buf_set_wef(bp, XFS_WEFC_BTWEE_WEF);
		bweak;
	defauwt:
		ASSEWT(0);
	}
}

int
xfs_btwee_get_buf_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*ptw,
	stwuct xfs_btwee_bwock		**bwock,
	stwuct xfs_buf			**bpp)
{
	stwuct xfs_mount	*mp = cuw->bc_mp;
	xfs_daddw_t		d;
	int			ewwow;

	ewwow = xfs_btwee_ptw_to_daddw(cuw, ptw, &d);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_twans_get_buf(cuw->bc_tp, mp->m_ddev_tawgp, d, mp->m_bsize,
			0, bpp);
	if (ewwow)
		wetuwn ewwow;

	(*bpp)->b_ops = cuw->bc_ops->buf_ops;
	*bwock = XFS_BUF_TO_BWOCK(*bpp);
	wetuwn 0;
}

/*
 * Wead in the buffew at the given ptw and wetuwn the buffew and
 * the bwock pointew within the buffew.
 */
int
xfs_btwee_wead_buf_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*ptw,
	int				fwags,
	stwuct xfs_btwee_bwock		**bwock,
	stwuct xfs_buf			**bpp)
{
	stwuct xfs_mount	*mp = cuw->bc_mp;
	xfs_daddw_t		d;
	int			ewwow;

	/* need to sowt out how cawwews deaw with faiwuwes fiwst */
	ASSEWT(!(fwags & XBF_TWYWOCK));

	ewwow = xfs_btwee_ptw_to_daddw(cuw, ptw, &d);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_twans_wead_buf(mp, cuw->bc_tp, mp->m_ddev_tawgp, d,
				   mp->m_bsize, fwags, bpp,
				   cuw->bc_ops->buf_ops);
	if (ewwow)
		wetuwn ewwow;

	xfs_btwee_set_wefs(cuw, *bpp);
	*bwock = XFS_BUF_TO_BWOCK(*bpp);
	wetuwn 0;
}

/*
 * Copy keys fwom one btwee bwock to anothew.
 */
void
xfs_btwee_copy_keys(
	stwuct xfs_btwee_cuw		*cuw,
	union xfs_btwee_key		*dst_key,
	const union xfs_btwee_key	*swc_key,
	int				numkeys)
{
	ASSEWT(numkeys >= 0);
	memcpy(dst_key, swc_key, numkeys * cuw->bc_ops->key_wen);
}

/*
 * Copy wecowds fwom one btwee bwock to anothew.
 */
STATIC void
xfs_btwee_copy_wecs(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_wec	*dst_wec,
	union xfs_btwee_wec	*swc_wec,
	int			numwecs)
{
	ASSEWT(numwecs >= 0);
	memcpy(dst_wec, swc_wec, numwecs * cuw->bc_ops->wec_wen);
}

/*
 * Copy bwock pointews fwom one btwee bwock to anothew.
 */
void
xfs_btwee_copy_ptws(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*dst_ptw,
	const union xfs_btwee_ptw *swc_ptw,
	int			numptws)
{
	ASSEWT(numptws >= 0);
	memcpy(dst_ptw, swc_ptw, numptws * xfs_btwee_ptw_wen(cuw));
}

/*
 * Shift keys one index weft/wight inside a singwe btwee bwock.
 */
STATIC void
xfs_btwee_shift_keys(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_key	*key,
	int			diw,
	int			numkeys)
{
	chaw			*dst_key;

	ASSEWT(numkeys >= 0);
	ASSEWT(diw == 1 || diw == -1);

	dst_key = (chaw *)key + (diw * cuw->bc_ops->key_wen);
	memmove(dst_key, key, numkeys * cuw->bc_ops->key_wen);
}

/*
 * Shift wecowds one index weft/wight inside a singwe btwee bwock.
 */
STATIC void
xfs_btwee_shift_wecs(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_wec	*wec,
	int			diw,
	int			numwecs)
{
	chaw			*dst_wec;

	ASSEWT(numwecs >= 0);
	ASSEWT(diw == 1 || diw == -1);

	dst_wec = (chaw *)wec + (diw * cuw->bc_ops->wec_wen);
	memmove(dst_wec, wec, numwecs * cuw->bc_ops->wec_wen);
}

/*
 * Shift bwock pointews one index weft/wight inside a singwe btwee bwock.
 */
STATIC void
xfs_btwee_shift_ptws(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw,
	int			diw,
	int			numptws)
{
	chaw			*dst_ptw;

	ASSEWT(numptws >= 0);
	ASSEWT(diw == 1 || diw == -1);

	dst_ptw = (chaw *)ptw + (diw * xfs_btwee_ptw_wen(cuw));
	memmove(dst_ptw, ptw, numptws * xfs_btwee_ptw_wen(cuw));
}

/*
 * Wog key vawues fwom the btwee bwock.
 */
STATIC void
xfs_btwee_wog_keys(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp,
	int			fiwst,
	int			wast)
{

	if (bp) {
		xfs_twans_buf_set_type(cuw->bc_tp, bp, XFS_BWFT_BTWEE_BUF);
		xfs_twans_wog_buf(cuw->bc_tp, bp,
				  xfs_btwee_key_offset(cuw, fiwst),
				  xfs_btwee_key_offset(cuw, wast + 1) - 1);
	} ewse {
		xfs_twans_wog_inode(cuw->bc_tp, cuw->bc_ino.ip,
				xfs_iwog_fbwoot(cuw->bc_ino.whichfowk));
	}
}

/*
 * Wog wecowd vawues fwom the btwee bwock.
 */
void
xfs_btwee_wog_wecs(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp,
	int			fiwst,
	int			wast)
{

	xfs_twans_buf_set_type(cuw->bc_tp, bp, XFS_BWFT_BTWEE_BUF);
	xfs_twans_wog_buf(cuw->bc_tp, bp,
			  xfs_btwee_wec_offset(cuw, fiwst),
			  xfs_btwee_wec_offset(cuw, wast + 1) - 1);

}

/*
 * Wog bwock pointew fiewds fwom a btwee bwock (nonweaf).
 */
STATIC void
xfs_btwee_wog_ptws(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	stwuct xfs_buf		*bp,	/* buffew containing btwee bwock */
	int			fiwst,	/* index of fiwst pointew to wog */
	int			wast)	/* index of wast pointew to wog */
{

	if (bp) {
		stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
		int			wevew = xfs_btwee_get_wevew(bwock);

		xfs_twans_buf_set_type(cuw->bc_tp, bp, XFS_BWFT_BTWEE_BUF);
		xfs_twans_wog_buf(cuw->bc_tp, bp,
				xfs_btwee_ptw_offset(cuw, fiwst, wevew),
				xfs_btwee_ptw_offset(cuw, wast + 1, wevew) - 1);
	} ewse {
		xfs_twans_wog_inode(cuw->bc_tp, cuw->bc_ino.ip,
			xfs_iwog_fbwoot(cuw->bc_ino.whichfowk));
	}

}

/*
 * Wog fiewds fwom a btwee bwock headew.
 */
void
xfs_btwee_wog_bwock(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	stwuct xfs_buf		*bp,	/* buffew containing btwee bwock */
	uint32_t		fiewds)	/* mask of fiewds: XFS_BB_... */
{
	int			fiwst;	/* fiwst byte offset wogged */
	int			wast;	/* wast byte offset wogged */
	static const showt	soffsets[] = {	/* tabwe of offsets (showt) */
		offsetof(stwuct xfs_btwee_bwock, bb_magic),
		offsetof(stwuct xfs_btwee_bwock, bb_wevew),
		offsetof(stwuct xfs_btwee_bwock, bb_numwecs),
		offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_weftsib),
		offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_wightsib),
		offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_bwkno),
		offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_wsn),
		offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_uuid),
		offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_ownew),
		offsetof(stwuct xfs_btwee_bwock, bb_u.s.bb_cwc),
		XFS_BTWEE_SBWOCK_CWC_WEN
	};
	static const showt	woffsets[] = {	/* tabwe of offsets (wong) */
		offsetof(stwuct xfs_btwee_bwock, bb_magic),
		offsetof(stwuct xfs_btwee_bwock, bb_wevew),
		offsetof(stwuct xfs_btwee_bwock, bb_numwecs),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_weftsib),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_wightsib),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_bwkno),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_wsn),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_uuid),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_ownew),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_cwc),
		offsetof(stwuct xfs_btwee_bwock, bb_u.w.bb_pad),
		XFS_BTWEE_WBWOCK_CWC_WEN
	};

	if (bp) {
		int nbits;

		if (cuw->bc_fwags & XFS_BTWEE_CWC_BWOCKS) {
			/*
			 * We don't wog the CWC when updating a btwee
			 * bwock but instead wecweate it duwing wog
			 * wecovewy.  As the wog buffews have checksums
			 * of theiw own this is safe and avoids wogging a cwc
			 * update in a wot of pwaces.
			 */
			if (fiewds == XFS_BB_AWW_BITS)
				fiewds = XFS_BB_AWW_BITS_CWC;
			nbits = XFS_BB_NUM_BITS_CWC;
		} ewse {
			nbits = XFS_BB_NUM_BITS;
		}
		xfs_btwee_offsets(fiewds,
				  (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) ?
					woffsets : soffsets,
				  nbits, &fiwst, &wast);
		xfs_twans_buf_set_type(cuw->bc_tp, bp, XFS_BWFT_BTWEE_BUF);
		xfs_twans_wog_buf(cuw->bc_tp, bp, fiwst, wast);
	} ewse {
		xfs_twans_wog_inode(cuw->bc_tp, cuw->bc_ino.ip,
			xfs_iwog_fbwoot(cuw->bc_ino.whichfowk));
	}
}

/*
 * Incwement cuwsow by one wecowd at the wevew.
 * Fow nonzewo wevews the weaf-wawd infowmation is untouched.
 */
int						/* ewwow */
xfs_btwee_incwement(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*stat)		/* success/faiwuwe */
{
	stwuct xfs_btwee_bwock	*bwock;
	union xfs_btwee_ptw	ptw;
	stwuct xfs_buf		*bp;
	int			ewwow;		/* ewwow wetuwn vawue */
	int			wev;

	ASSEWT(wevew < cuw->bc_nwevews);

	/* Wead-ahead to the wight at this wevew. */
	xfs_btwee_weadahead(cuw, wevew, XFS_BTCUW_WIGHTWA);

	/* Get a pointew to the btwee bwock. */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
	if (ewwow)
		goto ewwow0;
#endif

	/* We'we done if we wemain in the bwock aftew the incwement. */
	if (++cuw->bc_wevews[wevew].ptw <= xfs_btwee_get_numwecs(bwock))
		goto out1;

	/* Faiw if we just went off the wight edge of the twee. */
	xfs_btwee_get_sibwing(cuw, bwock, &ptw, XFS_BB_WIGHTSIB);
	if (xfs_btwee_ptw_is_nuww(cuw, &ptw))
		goto out0;

	XFS_BTWEE_STATS_INC(cuw, incwement);

	/*
	 * Mawch up the twee incwementing pointews.
	 * Stop when we don't go off the wight edge of a bwock.
	 */
	fow (wev = wevew + 1; wev < cuw->bc_nwevews; wev++) {
		bwock = xfs_btwee_get_bwock(cuw, wev, &bp);

#ifdef DEBUG
		ewwow = xfs_btwee_check_bwock(cuw, bwock, wev, bp);
		if (ewwow)
			goto ewwow0;
#endif

		if (++cuw->bc_wevews[wev].ptw <= xfs_btwee_get_numwecs(bwock))
			bweak;

		/* Wead-ahead the wight bwock fow the next woop. */
		xfs_btwee_weadahead(cuw, wev, XFS_BTCUW_WIGHTWA);
	}

	/*
	 * If we went off the woot then we awe eithew sewiouswy
	 * confused ow have the twee woot in an inode.
	 */
	if (wev == cuw->bc_nwevews) {
		if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE)
			goto out0;
		ASSEWT(0);
		ewwow = -EFSCOWWUPTED;
		goto ewwow0;
	}
	ASSEWT(wev < cuw->bc_nwevews);

	/*
	 * Now wawk back down the twee, fixing up the cuwsow's buffew
	 * pointews and key numbews.
	 */
	fow (bwock = xfs_btwee_get_bwock(cuw, wev, &bp); wev > wevew; ) {
		union xfs_btwee_ptw	*ptwp;

		ptwp = xfs_btwee_ptw_addw(cuw, cuw->bc_wevews[wev].ptw, bwock);
		--wev;
		ewwow = xfs_btwee_wead_buf_bwock(cuw, ptwp, 0, &bwock, &bp);
		if (ewwow)
			goto ewwow0;

		xfs_btwee_setbuf(cuw, wev, bp);
		cuw->bc_wevews[wev].ptw = 1;
	}
out1:
	*stat = 1;
	wetuwn 0;

out0:
	*stat = 0;
	wetuwn 0;

ewwow0:
	wetuwn ewwow;
}

/*
 * Decwement cuwsow by one wecowd at the wevew.
 * Fow nonzewo wevews the weaf-wawd infowmation is untouched.
 */
int						/* ewwow */
xfs_btwee_decwement(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*stat)		/* success/faiwuwe */
{
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_buf		*bp;
	int			ewwow;		/* ewwow wetuwn vawue */
	int			wev;
	union xfs_btwee_ptw	ptw;

	ASSEWT(wevew < cuw->bc_nwevews);

	/* Wead-ahead to the weft at this wevew. */
	xfs_btwee_weadahead(cuw, wevew, XFS_BTCUW_WEFTWA);

	/* We'we done if we wemain in the bwock aftew the decwement. */
	if (--cuw->bc_wevews[wevew].ptw > 0)
		goto out1;

	/* Get a pointew to the btwee bwock. */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
	if (ewwow)
		goto ewwow0;
#endif

	/* Faiw if we just went off the weft edge of the twee. */
	xfs_btwee_get_sibwing(cuw, bwock, &ptw, XFS_BB_WEFTSIB);
	if (xfs_btwee_ptw_is_nuww(cuw, &ptw))
		goto out0;

	XFS_BTWEE_STATS_INC(cuw, decwement);

	/*
	 * Mawch up the twee decwementing pointews.
	 * Stop when we don't go off the weft edge of a bwock.
	 */
	fow (wev = wevew + 1; wev < cuw->bc_nwevews; wev++) {
		if (--cuw->bc_wevews[wev].ptw > 0)
			bweak;
		/* Wead-ahead the weft bwock fow the next woop. */
		xfs_btwee_weadahead(cuw, wev, XFS_BTCUW_WEFTWA);
	}

	/*
	 * If we went off the woot then we awe sewiouswy confused.
	 * ow the woot of the twee is in an inode.
	 */
	if (wev == cuw->bc_nwevews) {
		if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE)
			goto out0;
		ASSEWT(0);
		ewwow = -EFSCOWWUPTED;
		goto ewwow0;
	}
	ASSEWT(wev < cuw->bc_nwevews);

	/*
	 * Now wawk back down the twee, fixing up the cuwsow's buffew
	 * pointews and key numbews.
	 */
	fow (bwock = xfs_btwee_get_bwock(cuw, wev, &bp); wev > wevew; ) {
		union xfs_btwee_ptw	*ptwp;

		ptwp = xfs_btwee_ptw_addw(cuw, cuw->bc_wevews[wev].ptw, bwock);
		--wev;
		ewwow = xfs_btwee_wead_buf_bwock(cuw, ptwp, 0, &bwock, &bp);
		if (ewwow)
			goto ewwow0;
		xfs_btwee_setbuf(cuw, wev, bp);
		cuw->bc_wevews[wev].ptw = xfs_btwee_get_numwecs(bwock);
	}
out1:
	*stat = 1;
	wetuwn 0;

out0:
	*stat = 0;
	wetuwn 0;

ewwow0:
	wetuwn ewwow;
}

int
xfs_btwee_wookup_get_bwock(
	stwuct xfs_btwee_cuw		*cuw,	/* btwee cuwsow */
	int				wevew,	/* wevew in the btwee */
	const union xfs_btwee_ptw	*pp,	/* ptw to btwee bwock */
	stwuct xfs_btwee_bwock		**bwkp) /* wetuwn btwee bwock */
{
	stwuct xfs_buf		*bp;	/* buffew pointew fow btwee bwock */
	xfs_daddw_t		daddw;
	int			ewwow = 0;

	/* speciaw case the woot bwock if in an inode */
	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    (wevew == cuw->bc_nwevews - 1)) {
		*bwkp = xfs_btwee_get_iwoot(cuw);
		wetuwn 0;
	}

	/*
	 * If the owd buffew at this wevew fow the disk addwess we awe
	 * wooking fow we-use it.
	 *
	 * Othewwise thwow it away and get a new one.
	 */
	bp = cuw->bc_wevews[wevew].bp;
	ewwow = xfs_btwee_ptw_to_daddw(cuw, pp, &daddw);
	if (ewwow)
		wetuwn ewwow;
	if (bp && xfs_buf_daddw(bp) == daddw) {
		*bwkp = XFS_BUF_TO_BWOCK(bp);
		wetuwn 0;
	}

	ewwow = xfs_btwee_wead_buf_bwock(cuw, pp, 0, bwkp, &bp);
	if (ewwow)
		wetuwn ewwow;

	/* Check the inode ownew since the vewifiews don't. */
	if (xfs_has_cwc(cuw->bc_mp) &&
	    !(cuw->bc_ino.fwags & XFS_BTCUW_BMBT_INVAWID_OWNEW) &&
	    (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) &&
	    be64_to_cpu((*bwkp)->bb_u.w.bb_ownew) !=
			cuw->bc_ino.ip->i_ino)
		goto out_bad;

	/* Did we get the wevew we wewe wooking fow? */
	if (be16_to_cpu((*bwkp)->bb_wevew) != wevew)
		goto out_bad;

	/* Check that intewnaw nodes have at weast one wecowd. */
	if (wevew != 0 && be16_to_cpu((*bwkp)->bb_numwecs) == 0)
		goto out_bad;

	xfs_btwee_setbuf(cuw, wevew, bp);
	wetuwn 0;

out_bad:
	*bwkp = NUWW;
	xfs_buf_mawk_cowwupt(bp);
	xfs_twans_bwewse(cuw->bc_tp, bp);
	wetuwn -EFSCOWWUPTED;
}

/*
 * Get cuwwent seawch key.  Fow wevew 0 we don't actuawwy have a key
 * stwuctuwe so we make one up fwom the wecowd.  Fow aww othew wevews
 * we just wetuwn the wight key.
 */
STATIC union xfs_btwee_key *
xfs_wookup_get_seawch_key(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			keyno,
	stwuct xfs_btwee_bwock	*bwock,
	union xfs_btwee_key	*kp)
{
	if (wevew == 0) {
		cuw->bc_ops->init_key_fwom_wec(kp,
				xfs_btwee_wec_addw(cuw, keyno, bwock));
		wetuwn kp;
	}

	wetuwn xfs_btwee_key_addw(cuw, keyno, bwock);
}

/*
 * Wookup the wecowd.  The cuwsow is made to point to it, based on diw.
 * stat is set to 0 if can't find any such wecowd, 1 fow success.
 */
int					/* ewwow */
xfs_btwee_wookup(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_wookup_t		diw,	/* <=, ==, ow >= */
	int			*stat)	/* success/faiwuwe */
{
	stwuct xfs_btwee_bwock	*bwock;	/* cuwwent btwee bwock */
	int64_t			diff;	/* diffewence fow the cuwwent key */
	int			ewwow;	/* ewwow wetuwn vawue */
	int			keyno;	/* cuwwent key numbew */
	int			wevew;	/* wevew in the btwee */
	union xfs_btwee_ptw	*pp;	/* ptw to btwee bwock */
	union xfs_btwee_ptw	ptw;	/* ptw to btwee bwock */

	XFS_BTWEE_STATS_INC(cuw, wookup);

	/* No such thing as a zewo-wevew twee. */
	if (XFS_IS_COWWUPT(cuw->bc_mp, cuw->bc_nwevews == 0))
		wetuwn -EFSCOWWUPTED;

	bwock = NUWW;
	keyno = 0;

	/* initiawise stawt pointew fwom cuwsow */
	cuw->bc_ops->init_ptw_fwom_cuw(cuw, &ptw);
	pp = &ptw;

	/*
	 * Itewate ovew each wevew in the btwee, stawting at the woot.
	 * Fow each wevew above the weaves, find the key we need, based
	 * on the wookup wecowd, then fowwow the cowwesponding bwock
	 * pointew down to the next wevew.
	 */
	fow (wevew = cuw->bc_nwevews - 1, diff = 1; wevew >= 0; wevew--) {
		/* Get the bwock we need to do the wookup on. */
		ewwow = xfs_btwee_wookup_get_bwock(cuw, wevew, pp, &bwock);
		if (ewwow)
			goto ewwow0;

		if (diff == 0) {
			/*
			 * If we awweady had a key match at a highew wevew, we
			 * know we need to use the fiwst entwy in this bwock.
			 */
			keyno = 1;
		} ewse {
			/* Othewwise seawch this bwock. Do a binawy seawch. */

			int	high;	/* high entwy numbew */
			int	wow;	/* wow entwy numbew */

			/* Set wow and high entwy numbews, 1-based. */
			wow = 1;
			high = xfs_btwee_get_numwecs(bwock);
			if (!high) {
				/* Bwock is empty, must be an empty weaf. */
				if (wevew != 0 || cuw->bc_nwevews != 1) {
					XFS_COWWUPTION_EWWOW(__func__,
							XFS_EWWWEVEW_WOW,
							cuw->bc_mp, bwock,
							sizeof(*bwock));
					wetuwn -EFSCOWWUPTED;
				}

				cuw->bc_wevews[0].ptw = diw != XFS_WOOKUP_WE;
				*stat = 0;
				wetuwn 0;
			}

			/* Binawy seawch the bwock. */
			whiwe (wow <= high) {
				union xfs_btwee_key	key;
				union xfs_btwee_key	*kp;

				XFS_BTWEE_STATS_INC(cuw, compawe);

				/* keyno is avewage of wow and high. */
				keyno = (wow + high) >> 1;

				/* Get cuwwent seawch key */
				kp = xfs_wookup_get_seawch_key(cuw, wevew,
						keyno, bwock, &key);

				/*
				 * Compute diffewence to get next diwection:
				 *  - wess than, move wight
				 *  - gweatew than, move weft
				 *  - equaw, we'we done
				 */
				diff = cuw->bc_ops->key_diff(cuw, kp);
				if (diff < 0)
					wow = keyno + 1;
				ewse if (diff > 0)
					high = keyno - 1;
				ewse
					bweak;
			}
		}

		/*
		 * If thewe awe mowe wevews, set up fow the next wevew
		 * by getting the bwock numbew and fiwwing in the cuwsow.
		 */
		if (wevew > 0) {
			/*
			 * If we moved weft, need the pwevious key numbew,
			 * unwess thewe isn't one.
			 */
			if (diff > 0 && --keyno < 1)
				keyno = 1;
			pp = xfs_btwee_ptw_addw(cuw, keyno, bwock);

			ewwow = xfs_btwee_debug_check_ptw(cuw, pp, 0, wevew);
			if (ewwow)
				goto ewwow0;

			cuw->bc_wevews[wevew].ptw = keyno;
		}
	}

	/* Done with the seawch. See if we need to adjust the wesuwts. */
	if (diw != XFS_WOOKUP_WE && diff < 0) {
		keyno++;
		/*
		 * If ge seawch and we went off the end of the bwock, but it's
		 * not the wast bwock, we'we in the wwong bwock.
		 */
		xfs_btwee_get_sibwing(cuw, bwock, &ptw, XFS_BB_WIGHTSIB);
		if (diw == XFS_WOOKUP_GE &&
		    keyno > xfs_btwee_get_numwecs(bwock) &&
		    !xfs_btwee_ptw_is_nuww(cuw, &ptw)) {
			int	i;

			cuw->bc_wevews[0].ptw = keyno;
			ewwow = xfs_btwee_incwement(cuw, 0, &i);
			if (ewwow)
				goto ewwow0;
			if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
				wetuwn -EFSCOWWUPTED;
			*stat = 1;
			wetuwn 0;
		}
	} ewse if (diw == XFS_WOOKUP_WE && diff > 0)
		keyno--;
	cuw->bc_wevews[0].ptw = keyno;

	/* Wetuwn if we succeeded ow not. */
	if (keyno == 0 || keyno > xfs_btwee_get_numwecs(bwock))
		*stat = 0;
	ewse if (diw != XFS_WOOKUP_EQ || diff == 0)
		*stat = 1;
	ewse
		*stat = 0;
	wetuwn 0;

ewwow0:
	wetuwn ewwow;
}

/* Find the high key stowage awea fwom a weguwaw key. */
union xfs_btwee_key *
xfs_btwee_high_key_fwom_key(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_key	*key)
{
	ASSEWT(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING);
	wetuwn (union xfs_btwee_key *)((chaw *)key +
			(cuw->bc_ops->key_wen / 2));
}

/* Detewmine the wow (and high if ovewwapped) keys of a weaf bwock */
STATIC void
xfs_btwee_get_weaf_keys(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	union xfs_btwee_key	*key)
{
	union xfs_btwee_key	max_hkey;
	union xfs_btwee_key	hkey;
	union xfs_btwee_wec	*wec;
	union xfs_btwee_key	*high;
	int			n;

	wec = xfs_btwee_wec_addw(cuw, 1, bwock);
	cuw->bc_ops->init_key_fwom_wec(key, wec);

	if (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING) {

		cuw->bc_ops->init_high_key_fwom_wec(&max_hkey, wec);
		fow (n = 2; n <= xfs_btwee_get_numwecs(bwock); n++) {
			wec = xfs_btwee_wec_addw(cuw, n, bwock);
			cuw->bc_ops->init_high_key_fwom_wec(&hkey, wec);
			if (xfs_btwee_keycmp_gt(cuw, &hkey, &max_hkey))
				max_hkey = hkey;
		}

		high = xfs_btwee_high_key_fwom_key(cuw, key);
		memcpy(high, &max_hkey, cuw->bc_ops->key_wen / 2);
	}
}

/* Detewmine the wow (and high if ovewwapped) keys of a node bwock */
STATIC void
xfs_btwee_get_node_keys(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	union xfs_btwee_key	*key)
{
	union xfs_btwee_key	*hkey;
	union xfs_btwee_key	*max_hkey;
	union xfs_btwee_key	*high;
	int			n;

	if (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING) {
		memcpy(key, xfs_btwee_key_addw(cuw, 1, bwock),
				cuw->bc_ops->key_wen / 2);

		max_hkey = xfs_btwee_high_key_addw(cuw, 1, bwock);
		fow (n = 2; n <= xfs_btwee_get_numwecs(bwock); n++) {
			hkey = xfs_btwee_high_key_addw(cuw, n, bwock);
			if (xfs_btwee_keycmp_gt(cuw, hkey, max_hkey))
				max_hkey = hkey;
		}

		high = xfs_btwee_high_key_fwom_key(cuw, key);
		memcpy(high, max_hkey, cuw->bc_ops->key_wen / 2);
	} ewse {
		memcpy(key, xfs_btwee_key_addw(cuw, 1, bwock),
				cuw->bc_ops->key_wen);
	}
}

/* Dewive the keys fow any btwee bwock. */
void
xfs_btwee_get_keys(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwock	*bwock,
	union xfs_btwee_key	*key)
{
	if (be16_to_cpu(bwock->bb_wevew) == 0)
		xfs_btwee_get_weaf_keys(cuw, bwock, key);
	ewse
		xfs_btwee_get_node_keys(cuw, bwock, key);
}

/*
 * Decide if we need to update the pawent keys of a btwee bwock.  Fow
 * a standawd btwee this is onwy necessawy if we'we updating the fiwst
 * wecowd/key.  Fow an ovewwapping btwee, we must awways update the
 * keys because the highest key can be in any of the wecowds ow keys
 * in the bwock.
 */
static inwine boow
xfs_btwee_needs_key_update(
	stwuct xfs_btwee_cuw	*cuw,
	int			ptw)
{
	wetuwn (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING) || ptw == 1;
}

/*
 * Update the wow and high pawent keys of the given wevew, pwogwessing
 * towawds the woot.  If fowce_aww is fawse, stop if the keys fow a given
 * wevew do not need updating.
 */
STATIC int
__xfs_btwee_updkeys(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	stwuct xfs_btwee_bwock	*bwock,
	stwuct xfs_buf		*bp0,
	boow			fowce_aww)
{
	union xfs_btwee_key	key;	/* keys fwom cuwwent wevew */
	union xfs_btwee_key	*wkey;	/* keys fwom the next wevew up */
	union xfs_btwee_key	*hkey;
	union xfs_btwee_key	*nwkey;	/* keys fwom the next wevew up */
	union xfs_btwee_key	*nhkey;
	stwuct xfs_buf		*bp;
	int			ptw;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING);

	/* Exit if thewe awen't any pawent wevews to update. */
	if (wevew + 1 >= cuw->bc_nwevews)
		wetuwn 0;

	twace_xfs_btwee_updkeys(cuw, wevew, bp0);

	wkey = &key;
	hkey = xfs_btwee_high_key_fwom_key(cuw, wkey);
	xfs_btwee_get_keys(cuw, bwock, wkey);
	fow (wevew++; wevew < cuw->bc_nwevews; wevew++) {
#ifdef DEBUG
		int		ewwow;
#endif
		bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
		twace_xfs_btwee_updkeys(cuw, wevew, bp);
#ifdef DEBUG
		ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
		if (ewwow)
			wetuwn ewwow;
#endif
		ptw = cuw->bc_wevews[wevew].ptw;
		nwkey = xfs_btwee_key_addw(cuw, ptw, bwock);
		nhkey = xfs_btwee_high_key_addw(cuw, ptw, bwock);
		if (!fowce_aww &&
		    xfs_btwee_keycmp_eq(cuw, nwkey, wkey) &&
		    xfs_btwee_keycmp_eq(cuw, nhkey, hkey))
			bweak;
		xfs_btwee_copy_keys(cuw, nwkey, wkey, 1);
		xfs_btwee_wog_keys(cuw, bp, ptw, ptw);
		if (wevew + 1 >= cuw->bc_nwevews)
			bweak;
		xfs_btwee_get_node_keys(cuw, bwock, wkey);
	}

	wetuwn 0;
}

/* Update aww the keys fwom some wevew in cuwsow back to the woot. */
STATIC int
xfs_btwee_updkeys_fowce(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	stwuct xfs_buf		*bp;
	stwuct xfs_btwee_bwock	*bwock;

	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	wetuwn __xfs_btwee_updkeys(cuw, wevew, bwock, bp, twue);
}

/*
 * Update the pawent keys of the given wevew, pwogwessing towawds the woot.
 */
STATIC int
xfs_btwee_update_keys(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_buf		*bp;
	union xfs_btwee_key	*kp;
	union xfs_btwee_key	key;
	int			ptw;

	ASSEWT(wevew >= 0);

	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	if (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING)
		wetuwn __xfs_btwee_updkeys(cuw, wevew, bwock, bp, fawse);

	/*
	 * Go up the twee fwom this wevew towawd the woot.
	 * At each wevew, update the key vawue to the vawue input.
	 * Stop when we weach a wevew whewe the cuwsow isn't pointing
	 * at the fiwst entwy in the bwock.
	 */
	xfs_btwee_get_keys(cuw, bwock, &key);
	fow (wevew++, ptw = 1; ptw == 1 && wevew < cuw->bc_nwevews; wevew++) {
#ifdef DEBUG
		int		ewwow;
#endif
		bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
#ifdef DEBUG
		ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
		if (ewwow)
			wetuwn ewwow;
#endif
		ptw = cuw->bc_wevews[wevew].ptw;
		kp = xfs_btwee_key_addw(cuw, ptw, bwock);
		xfs_btwee_copy_keys(cuw, kp, &key, 1);
		xfs_btwee_wog_keys(cuw, bp, ptw, ptw);
	}

	wetuwn 0;
}

/*
 * Update the wecowd wefewwed to by cuw to the vawue in the
 * given wecowd. This eithew wowks (wetuwn 0) ow gets an
 * EFSCOWWUPTED ewwow.
 */
int
xfs_btwee_update(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_wec	*wec)
{
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_buf		*bp;
	int			ewwow;
	int			ptw;
	union xfs_btwee_wec	*wp;

	/* Pick up the cuwwent bwock. */
	bwock = xfs_btwee_get_bwock(cuw, 0, &bp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, 0, bp);
	if (ewwow)
		goto ewwow0;
#endif
	/* Get the addwess of the wec to be updated. */
	ptw = cuw->bc_wevews[0].ptw;
	wp = xfs_btwee_wec_addw(cuw, ptw, bwock);

	/* Fiww in the new contents and wog them. */
	xfs_btwee_copy_wecs(cuw, wp, wec, 1);
	xfs_btwee_wog_wecs(cuw, bp, ptw, ptw);

	/*
	 * If we awe twacking the wast wecowd in the twee and
	 * we awe at the faw wight edge of the twee, update it.
	 */
	if (xfs_btwee_is_wastwec(cuw, bwock, 0)) {
		cuw->bc_ops->update_wastwec(cuw, bwock, wec,
					    ptw, WASTWEC_UPDATE);
	}

	/* Pass new key vawue up to ouw pawent. */
	if (xfs_btwee_needs_key_update(cuw, ptw)) {
		ewwow = xfs_btwee_update_keys(cuw, 0);
		if (ewwow)
			goto ewwow0;
	}

	wetuwn 0;

ewwow0:
	wetuwn ewwow;
}

/*
 * Move 1 wecowd weft fwom cuw/wevew if possibwe.
 * Update cuw to wefwect the new path.
 */
STATIC int					/* ewwow */
xfs_btwee_wshift(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*stat)		/* success/faiwuwe */
{
	stwuct xfs_buf		*wbp;		/* weft buffew pointew */
	stwuct xfs_btwee_bwock	*weft;		/* weft btwee bwock */
	int			wwecs;		/* weft wecowd count */
	stwuct xfs_buf		*wbp;		/* wight buffew pointew */
	stwuct xfs_btwee_bwock	*wight;		/* wight btwee bwock */
	stwuct xfs_btwee_cuw	*tcuw;		/* tempowawy btwee cuwsow */
	int			wwecs;		/* wight wecowd count */
	union xfs_btwee_ptw	wptw;		/* weft btwee pointew */
	union xfs_btwee_key	*wkp = NUWW;	/* wight btwee key */
	union xfs_btwee_ptw	*wpp = NUWW;	/* wight addwess pointew */
	union xfs_btwee_wec	*wwp = NUWW;	/* wight wecowd pointew */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			i;

	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    wevew == cuw->bc_nwevews - 1)
		goto out0;

	/* Set up vawiabwes fow this bwock as "wight". */
	wight = xfs_btwee_get_bwock(cuw, wevew, &wbp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, wight, wevew, wbp);
	if (ewwow)
		goto ewwow0;
#endif

	/* If we've got no weft sibwing then we can't shift an entwy weft. */
	xfs_btwee_get_sibwing(cuw, wight, &wptw, XFS_BB_WEFTSIB);
	if (xfs_btwee_ptw_is_nuww(cuw, &wptw))
		goto out0;

	/*
	 * If the cuwsow entwy is the one that wouwd be moved, don't
	 * do it... it's too compwicated.
	 */
	if (cuw->bc_wevews[wevew].ptw <= 1)
		goto out0;

	/* Set up the weft neighbow as "weft". */
	ewwow = xfs_btwee_wead_buf_bwock(cuw, &wptw, 0, &weft, &wbp);
	if (ewwow)
		goto ewwow0;

	/* If it's fuww, it can't take anothew entwy. */
	wwecs = xfs_btwee_get_numwecs(weft);
	if (wwecs == cuw->bc_ops->get_maxwecs(cuw, wevew))
		goto out0;

	wwecs = xfs_btwee_get_numwecs(wight);

	/*
	 * We add one entwy to the weft side and wemove one fow the wight side.
	 * Account fow it hewe, the changes wiww be updated on disk and wogged
	 * watew.
	 */
	wwecs++;
	wwecs--;

	XFS_BTWEE_STATS_INC(cuw, wshift);
	XFS_BTWEE_STATS_ADD(cuw, moves, 1);

	/*
	 * If non-weaf, copy a key and a ptw to the weft bwock.
	 * Wog the changes to the weft bwock.
	 */
	if (wevew > 0) {
		/* It's a non-weaf.  Move keys and pointews. */
		union xfs_btwee_key	*wkp;	/* weft btwee key */
		union xfs_btwee_ptw	*wpp;	/* weft addwess pointew */

		wkp = xfs_btwee_key_addw(cuw, wwecs, weft);
		wkp = xfs_btwee_key_addw(cuw, 1, wight);

		wpp = xfs_btwee_ptw_addw(cuw, wwecs, weft);
		wpp = xfs_btwee_ptw_addw(cuw, 1, wight);

		ewwow = xfs_btwee_debug_check_ptw(cuw, wpp, 0, wevew);
		if (ewwow)
			goto ewwow0;

		xfs_btwee_copy_keys(cuw, wkp, wkp, 1);
		xfs_btwee_copy_ptws(cuw, wpp, wpp, 1);

		xfs_btwee_wog_keys(cuw, wbp, wwecs, wwecs);
		xfs_btwee_wog_ptws(cuw, wbp, wwecs, wwecs);

		ASSEWT(cuw->bc_ops->keys_inowdew(cuw,
			xfs_btwee_key_addw(cuw, wwecs - 1, weft), wkp));
	} ewse {
		/* It's a weaf.  Move wecowds.  */
		union xfs_btwee_wec	*wwp;	/* weft wecowd pointew */

		wwp = xfs_btwee_wec_addw(cuw, wwecs, weft);
		wwp = xfs_btwee_wec_addw(cuw, 1, wight);

		xfs_btwee_copy_wecs(cuw, wwp, wwp, 1);
		xfs_btwee_wog_wecs(cuw, wbp, wwecs, wwecs);

		ASSEWT(cuw->bc_ops->wecs_inowdew(cuw,
			xfs_btwee_wec_addw(cuw, wwecs - 1, weft), wwp));
	}

	xfs_btwee_set_numwecs(weft, wwecs);
	xfs_btwee_wog_bwock(cuw, wbp, XFS_BB_NUMWECS);

	xfs_btwee_set_numwecs(wight, wwecs);
	xfs_btwee_wog_bwock(cuw, wbp, XFS_BB_NUMWECS);

	/*
	 * Swide the contents of wight down one entwy.
	 */
	XFS_BTWEE_STATS_ADD(cuw, moves, wwecs - 1);
	if (wevew > 0) {
		/* It's a nonweaf. opewate on keys and ptws */
		fow (i = 0; i < wwecs; i++) {
			ewwow = xfs_btwee_debug_check_ptw(cuw, wpp, i + 1, wevew);
			if (ewwow)
				goto ewwow0;
		}

		xfs_btwee_shift_keys(cuw,
				xfs_btwee_key_addw(cuw, 2, wight),
				-1, wwecs);
		xfs_btwee_shift_ptws(cuw,
				xfs_btwee_ptw_addw(cuw, 2, wight),
				-1, wwecs);

		xfs_btwee_wog_keys(cuw, wbp, 1, wwecs);
		xfs_btwee_wog_ptws(cuw, wbp, 1, wwecs);
	} ewse {
		/* It's a weaf. opewate on wecowds */
		xfs_btwee_shift_wecs(cuw,
			xfs_btwee_wec_addw(cuw, 2, wight),
			-1, wwecs);
		xfs_btwee_wog_wecs(cuw, wbp, 1, wwecs);
	}

	/*
	 * Using a tempowawy cuwsow, update the pawent key vawues of the
	 * bwock on the weft.
	 */
	if (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING) {
		ewwow = xfs_btwee_dup_cuwsow(cuw, &tcuw);
		if (ewwow)
			goto ewwow0;
		i = xfs_btwee_fiwstwec(tcuw, wevew);
		if (XFS_IS_COWWUPT(tcuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		ewwow = xfs_btwee_decwement(tcuw, wevew, &i);
		if (ewwow)
			goto ewwow1;

		/* Update the pawent high keys of the weft bwock, if needed. */
		ewwow = xfs_btwee_update_keys(tcuw, wevew);
		if (ewwow)
			goto ewwow1;

		xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);
	}

	/* Update the pawent keys of the wight bwock. */
	ewwow = xfs_btwee_update_keys(cuw, wevew);
	if (ewwow)
		goto ewwow0;

	/* Swide the cuwsow vawue weft one. */
	cuw->bc_wevews[wevew].ptw--;

	*stat = 1;
	wetuwn 0;

out0:
	*stat = 0;
	wetuwn 0;

ewwow0:
	wetuwn ewwow;

ewwow1:
	xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Move 1 wecowd wight fwom cuw/wevew if possibwe.
 * Update cuw to wefwect the new path.
 */
STATIC int					/* ewwow */
xfs_btwee_wshift(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*stat)		/* success/faiwuwe */
{
	stwuct xfs_buf		*wbp;		/* weft buffew pointew */
	stwuct xfs_btwee_bwock	*weft;		/* weft btwee bwock */
	stwuct xfs_buf		*wbp;		/* wight buffew pointew */
	stwuct xfs_btwee_bwock	*wight;		/* wight btwee bwock */
	stwuct xfs_btwee_cuw	*tcuw;		/* tempowawy btwee cuwsow */
	union xfs_btwee_ptw	wptw;		/* wight bwock pointew */
	union xfs_btwee_key	*wkp;		/* wight btwee key */
	int			wwecs;		/* wight wecowd count */
	int			wwecs;		/* weft wecowd count */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			i;		/* woop countew */

	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    (wevew == cuw->bc_nwevews - 1))
		goto out0;

	/* Set up vawiabwes fow this bwock as "weft". */
	weft = xfs_btwee_get_bwock(cuw, wevew, &wbp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, weft, wevew, wbp);
	if (ewwow)
		goto ewwow0;
#endif

	/* If we've got no wight sibwing then we can't shift an entwy wight. */
	xfs_btwee_get_sibwing(cuw, weft, &wptw, XFS_BB_WIGHTSIB);
	if (xfs_btwee_ptw_is_nuww(cuw, &wptw))
		goto out0;

	/*
	 * If the cuwsow entwy is the one that wouwd be moved, don't
	 * do it... it's too compwicated.
	 */
	wwecs = xfs_btwee_get_numwecs(weft);
	if (cuw->bc_wevews[wevew].ptw >= wwecs)
		goto out0;

	/* Set up the wight neighbow as "wight". */
	ewwow = xfs_btwee_wead_buf_bwock(cuw, &wptw, 0, &wight, &wbp);
	if (ewwow)
		goto ewwow0;

	/* If it's fuww, it can't take anothew entwy. */
	wwecs = xfs_btwee_get_numwecs(wight);
	if (wwecs == cuw->bc_ops->get_maxwecs(cuw, wevew))
		goto out0;

	XFS_BTWEE_STATS_INC(cuw, wshift);
	XFS_BTWEE_STATS_ADD(cuw, moves, wwecs);

	/*
	 * Make a howe at the stawt of the wight neighbow bwock, then
	 * copy the wast weft bwock entwy to the howe.
	 */
	if (wevew > 0) {
		/* It's a nonweaf. make a howe in the keys and ptws */
		union xfs_btwee_key	*wkp;
		union xfs_btwee_ptw	*wpp;
		union xfs_btwee_ptw	*wpp;

		wkp = xfs_btwee_key_addw(cuw, wwecs, weft);
		wpp = xfs_btwee_ptw_addw(cuw, wwecs, weft);
		wkp = xfs_btwee_key_addw(cuw, 1, wight);
		wpp = xfs_btwee_ptw_addw(cuw, 1, wight);

		fow (i = wwecs - 1; i >= 0; i--) {
			ewwow = xfs_btwee_debug_check_ptw(cuw, wpp, i, wevew);
			if (ewwow)
				goto ewwow0;
		}

		xfs_btwee_shift_keys(cuw, wkp, 1, wwecs);
		xfs_btwee_shift_ptws(cuw, wpp, 1, wwecs);

		ewwow = xfs_btwee_debug_check_ptw(cuw, wpp, 0, wevew);
		if (ewwow)
			goto ewwow0;

		/* Now put the new data in, and wog it. */
		xfs_btwee_copy_keys(cuw, wkp, wkp, 1);
		xfs_btwee_copy_ptws(cuw, wpp, wpp, 1);

		xfs_btwee_wog_keys(cuw, wbp, 1, wwecs + 1);
		xfs_btwee_wog_ptws(cuw, wbp, 1, wwecs + 1);

		ASSEWT(cuw->bc_ops->keys_inowdew(cuw, wkp,
			xfs_btwee_key_addw(cuw, 2, wight)));
	} ewse {
		/* It's a weaf. make a howe in the wecowds */
		union xfs_btwee_wec	*wwp;
		union xfs_btwee_wec	*wwp;

		wwp = xfs_btwee_wec_addw(cuw, wwecs, weft);
		wwp = xfs_btwee_wec_addw(cuw, 1, wight);

		xfs_btwee_shift_wecs(cuw, wwp, 1, wwecs);

		/* Now put the new data in, and wog it. */
		xfs_btwee_copy_wecs(cuw, wwp, wwp, 1);
		xfs_btwee_wog_wecs(cuw, wbp, 1, wwecs + 1);
	}

	/*
	 * Decwement and wog weft's numwecs, bump and wog wight's numwecs.
	 */
	xfs_btwee_set_numwecs(weft, --wwecs);
	xfs_btwee_wog_bwock(cuw, wbp, XFS_BB_NUMWECS);

	xfs_btwee_set_numwecs(wight, ++wwecs);
	xfs_btwee_wog_bwock(cuw, wbp, XFS_BB_NUMWECS);

	/*
	 * Using a tempowawy cuwsow, update the pawent key vawues of the
	 * bwock on the wight.
	 */
	ewwow = xfs_btwee_dup_cuwsow(cuw, &tcuw);
	if (ewwow)
		goto ewwow0;
	i = xfs_btwee_wastwec(tcuw, wevew);
	if (XFS_IS_COWWUPT(tcuw->bc_mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto ewwow0;
	}

	ewwow = xfs_btwee_incwement(tcuw, wevew, &i);
	if (ewwow)
		goto ewwow1;

	/* Update the pawent high keys of the weft bwock, if needed. */
	if (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING) {
		ewwow = xfs_btwee_update_keys(cuw, wevew);
		if (ewwow)
			goto ewwow1;
	}

	/* Update the pawent keys of the wight bwock. */
	ewwow = xfs_btwee_update_keys(tcuw, wevew);
	if (ewwow)
		goto ewwow1;

	xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);

	*stat = 1;
	wetuwn 0;

out0:
	*stat = 0;
	wetuwn 0;

ewwow0:
	wetuwn ewwow;

ewwow1:
	xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Spwit cuw/wevew bwock in hawf.
 * Wetuwn new bwock numbew and the key to its fiwst
 * wecowd (to be insewted into pawent).
 */
STATIC int					/* ewwow */
__xfs_btwee_spwit(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	union xfs_btwee_ptw	*ptwp,
	union xfs_btwee_key	*key,
	stwuct xfs_btwee_cuw	**cuwp,
	int			*stat)		/* success/faiwuwe */
{
	union xfs_btwee_ptw	wptw;		/* weft sibwing bwock ptw */
	stwuct xfs_buf		*wbp;		/* weft buffew pointew */
	stwuct xfs_btwee_bwock	*weft;		/* weft btwee bwock */
	union xfs_btwee_ptw	wptw;		/* wight sibwing bwock ptw */
	stwuct xfs_buf		*wbp;		/* wight buffew pointew */
	stwuct xfs_btwee_bwock	*wight;		/* wight btwee bwock */
	union xfs_btwee_ptw	wwptw;		/* wight-wight sibwing ptw */
	stwuct xfs_buf		*wwbp;		/* wight-wight buffew pointew */
	stwuct xfs_btwee_bwock	*wwbwock;	/* wight-wight btwee bwock */
	int			wwecs;
	int			wwecs;
	int			swc_index;
	int			ewwow;		/* ewwow wetuwn vawue */
	int			i;

	XFS_BTWEE_STATS_INC(cuw, spwit);

	/* Set up weft bwock (cuwwent one). */
	weft = xfs_btwee_get_bwock(cuw, wevew, &wbp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, weft, wevew, wbp);
	if (ewwow)
		goto ewwow0;
#endif

	xfs_btwee_buf_to_ptw(cuw, wbp, &wptw);

	/* Awwocate the new bwock. If we can't do it, we'we toast. Give up. */
	ewwow = cuw->bc_ops->awwoc_bwock(cuw, &wptw, &wptw, stat);
	if (ewwow)
		goto ewwow0;
	if (*stat == 0)
		goto out0;
	XFS_BTWEE_STATS_INC(cuw, awwoc);

	/* Set up the new bwock as "wight". */
	ewwow = xfs_btwee_get_buf_bwock(cuw, &wptw, &wight, &wbp);
	if (ewwow)
		goto ewwow0;

	/* Fiww in the btwee headew fow the new wight bwock. */
	xfs_btwee_init_bwock_cuw(cuw, wbp, xfs_btwee_get_wevew(weft), 0);

	/*
	 * Spwit the entwies between the owd and the new bwock evenwy.
	 * Make suwe that if thewe's an odd numbew of entwies now, that
	 * each new bwock wiww have the same numbew of entwies.
	 */
	wwecs = xfs_btwee_get_numwecs(weft);
	wwecs = wwecs / 2;
	if ((wwecs & 1) && cuw->bc_wevews[wevew].ptw <= wwecs + 1)
		wwecs++;
	swc_index = (wwecs - wwecs + 1);

	XFS_BTWEE_STATS_ADD(cuw, moves, wwecs);

	/* Adjust numwecs fow the watew get_*_keys() cawws. */
	wwecs -= wwecs;
	xfs_btwee_set_numwecs(weft, wwecs);
	xfs_btwee_set_numwecs(wight, xfs_btwee_get_numwecs(wight) + wwecs);

	/*
	 * Copy btwee bwock entwies fwom the weft bwock ovew to the
	 * new bwock, the wight. Update the wight bwock and wog the
	 * changes.
	 */
	if (wevew > 0) {
		/* It's a non-weaf.  Move keys and pointews. */
		union xfs_btwee_key	*wkp;	/* weft btwee key */
		union xfs_btwee_ptw	*wpp;	/* weft addwess pointew */
		union xfs_btwee_key	*wkp;	/* wight btwee key */
		union xfs_btwee_ptw	*wpp;	/* wight addwess pointew */

		wkp = xfs_btwee_key_addw(cuw, swc_index, weft);
		wpp = xfs_btwee_ptw_addw(cuw, swc_index, weft);
		wkp = xfs_btwee_key_addw(cuw, 1, wight);
		wpp = xfs_btwee_ptw_addw(cuw, 1, wight);

		fow (i = swc_index; i < wwecs; i++) {
			ewwow = xfs_btwee_debug_check_ptw(cuw, wpp, i, wevew);
			if (ewwow)
				goto ewwow0;
		}

		/* Copy the keys & pointews to the new bwock. */
		xfs_btwee_copy_keys(cuw, wkp, wkp, wwecs);
		xfs_btwee_copy_ptws(cuw, wpp, wpp, wwecs);

		xfs_btwee_wog_keys(cuw, wbp, 1, wwecs);
		xfs_btwee_wog_ptws(cuw, wbp, 1, wwecs);

		/* Stash the keys of the new bwock fow watew insewtion. */
		xfs_btwee_get_node_keys(cuw, wight, key);
	} ewse {
		/* It's a weaf.  Move wecowds.  */
		union xfs_btwee_wec	*wwp;	/* weft wecowd pointew */
		union xfs_btwee_wec	*wwp;	/* wight wecowd pointew */

		wwp = xfs_btwee_wec_addw(cuw, swc_index, weft);
		wwp = xfs_btwee_wec_addw(cuw, 1, wight);

		/* Copy wecowds to the new bwock. */
		xfs_btwee_copy_wecs(cuw, wwp, wwp, wwecs);
		xfs_btwee_wog_wecs(cuw, wbp, 1, wwecs);

		/* Stash the keys of the new bwock fow watew insewtion. */
		xfs_btwee_get_weaf_keys(cuw, wight, key);
	}

	/*
	 * Find the weft bwock numbew by wooking in the buffew.
	 * Adjust sibwing pointews.
	 */
	xfs_btwee_get_sibwing(cuw, weft, &wwptw, XFS_BB_WIGHTSIB);
	xfs_btwee_set_sibwing(cuw, wight, &wwptw, XFS_BB_WIGHTSIB);
	xfs_btwee_set_sibwing(cuw, wight, &wptw, XFS_BB_WEFTSIB);
	xfs_btwee_set_sibwing(cuw, weft, &wptw, XFS_BB_WIGHTSIB);

	xfs_btwee_wog_bwock(cuw, wbp, XFS_BB_AWW_BITS);
	xfs_btwee_wog_bwock(cuw, wbp, XFS_BB_NUMWECS | XFS_BB_WIGHTSIB);

	/*
	 * If thewe's a bwock to the new bwock's wight, make that bwock
	 * point back to wight instead of to weft.
	 */
	if (!xfs_btwee_ptw_is_nuww(cuw, &wwptw)) {
		ewwow = xfs_btwee_wead_buf_bwock(cuw, &wwptw,
							0, &wwbwock, &wwbp);
		if (ewwow)
			goto ewwow0;
		xfs_btwee_set_sibwing(cuw, wwbwock, &wptw, XFS_BB_WEFTSIB);
		xfs_btwee_wog_bwock(cuw, wwbp, XFS_BB_WEFTSIB);
	}

	/* Update the pawent high keys of the weft bwock, if needed. */
	if (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING) {
		ewwow = xfs_btwee_update_keys(cuw, wevew);
		if (ewwow)
			goto ewwow0;
	}

	/*
	 * If the cuwsow is weawwy in the wight bwock, move it thewe.
	 * If it's just pointing past the wast entwy in weft, then we'ww
	 * insewt thewe, so don't change anything in that case.
	 */
	if (cuw->bc_wevews[wevew].ptw > wwecs + 1) {
		xfs_btwee_setbuf(cuw, wevew, wbp);
		cuw->bc_wevews[wevew].ptw -= wwecs;
	}
	/*
	 * If thewe awe mowe wevews, we'ww need anothew cuwsow which wefews
	 * the wight bwock, no mattew whewe this cuwsow was.
	 */
	if (wevew + 1 < cuw->bc_nwevews) {
		ewwow = xfs_btwee_dup_cuwsow(cuw, cuwp);
		if (ewwow)
			goto ewwow0;
		(*cuwp)->bc_wevews[wevew + 1].ptw++;
	}
	*ptwp = wptw;
	*stat = 1;
	wetuwn 0;
out0:
	*stat = 0;
	wetuwn 0;

ewwow0:
	wetuwn ewwow;
}

#ifdef __KEWNEW__
stwuct xfs_btwee_spwit_awgs {
	stwuct xfs_btwee_cuw	*cuw;
	int			wevew;
	union xfs_btwee_ptw	*ptwp;
	union xfs_btwee_key	*key;
	stwuct xfs_btwee_cuw	**cuwp;
	int			*stat;		/* success/faiwuwe */
	int			wesuwt;
	boow			kswapd;	/* awwocation in kswapd context */
	stwuct compwetion	*done;
	stwuct wowk_stwuct	wowk;
};

/*
 * Stack switching intewfaces fow awwocation
 */
static void
xfs_btwee_spwit_wowkew(
	stwuct wowk_stwuct	*wowk)
{
	stwuct xfs_btwee_spwit_awgs	*awgs = containew_of(wowk,
						stwuct xfs_btwee_spwit_awgs, wowk);
	unsigned wong		pfwags;
	unsigned wong		new_pfwags = 0;

	/*
	 * we awe in a twansaction context hewe, but may awso be doing wowk
	 * in kswapd context, and hence we may need to inhewit that state
	 * tempowawiwy to ensuwe that we don't bwock waiting fow memowy wecwaim
	 * in any way.
	 */
	if (awgs->kswapd)
		new_pfwags |= PF_MEMAWWOC | PF_KSWAPD;

	cuwwent_set_fwags_nested(&pfwags, new_pfwags);
	xfs_twans_set_context(awgs->cuw->bc_tp);

	awgs->wesuwt = __xfs_btwee_spwit(awgs->cuw, awgs->wevew, awgs->ptwp,
					 awgs->key, awgs->cuwp, awgs->stat);

	xfs_twans_cweaw_context(awgs->cuw->bc_tp);
	cuwwent_westowe_fwags_nested(&pfwags, new_pfwags);

	/*
	 * Do not access awgs aftew compwete() has wun hewe. We don't own awgs
	 * and the ownew may wun and fwee awgs befowe we wetuwn hewe.
	 */
	compwete(awgs->done);

}

/*
 * BMBT spwit wequests often come in with wittwe stack to wowk on so we push
 * them off to a wowkew thwead so thewe is wots of stack to use. Fow the othew
 * btwee types, just caww diwectwy to avoid the context switch ovewhead hewe.
 *
 * Cawe must be taken hewe - the wowk queue wescuew thwead intwoduces potentiaw
 * AGF <> wowkew queue deadwocks if the BMBT bwock awwocation has to wock new
 * AGFs to awwocate bwocks. A task being wun by the wescuew couwd attempt to
 * wock an AGF that is awweady wocked by a task queued to wun by the wescuew,
 * wesuwting in an ABBA deadwock as the wescuew cannot wun the wock howdew to
 * wewease it untiw the cuwwent thwead it is wunning gains the wock.
 *
 * To avoid this issue, we onwy evew queue BMBT spwits that don't have an AGF
 * awweady wocked to awwocate fwom. The onwy pwace that doesn't howd an AGF
 * wocked is unwwitten extent convewsion at IO compwetion, but that has awweady
 * been offwoaded to a wowkew thwead and hence has no stack consumption issues
 * we have to wowwy about.
 */
STATIC int					/* ewwow */
xfs_btwee_spwit(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	union xfs_btwee_ptw	*ptwp,
	union xfs_btwee_key	*key,
	stwuct xfs_btwee_cuw	**cuwp,
	int			*stat)		/* success/faiwuwe */
{
	stwuct xfs_btwee_spwit_awgs	awgs;
	DECWAWE_COMPWETION_ONSTACK(done);

	if (cuw->bc_btnum != XFS_BTNUM_BMAP ||
	    cuw->bc_tp->t_highest_agno == NUWWAGNUMBEW)
		wetuwn __xfs_btwee_spwit(cuw, wevew, ptwp, key, cuwp, stat);

	awgs.cuw = cuw;
	awgs.wevew = wevew;
	awgs.ptwp = ptwp;
	awgs.key = key;
	awgs.cuwp = cuwp;
	awgs.stat = stat;
	awgs.done = &done;
	awgs.kswapd = cuwwent_is_kswapd();
	INIT_WOWK_ONSTACK(&awgs.wowk, xfs_btwee_spwit_wowkew);
	queue_wowk(xfs_awwoc_wq, &awgs.wowk);
	wait_fow_compwetion(&done);
	destwoy_wowk_on_stack(&awgs.wowk);
	wetuwn awgs.wesuwt;
}
#ewse
#define xfs_btwee_spwit	__xfs_btwee_spwit
#endif /* __KEWNEW__ */


/*
 * Copy the owd inode woot contents into a weaw bwock and make the
 * bwoot point to it.
 */
int						/* ewwow */
xfs_btwee_new_iwoot(
	stwuct xfs_btwee_cuw	*cuw,		/* btwee cuwsow */
	int			*wogfwags,	/* wogging fwags fow inode */
	int			*stat)		/* wetuwn status - 0 faiw */
{
	stwuct xfs_buf		*cbp;		/* buffew fow cbwock */
	stwuct xfs_btwee_bwock	*bwock;		/* btwee bwock */
	stwuct xfs_btwee_bwock	*cbwock;	/* chiwd btwee bwock */
	union xfs_btwee_key	*ckp;		/* chiwd key pointew */
	union xfs_btwee_ptw	*cpp;		/* chiwd ptw pointew */
	union xfs_btwee_key	*kp;		/* pointew to btwee key */
	union xfs_btwee_ptw	*pp;		/* pointew to bwock addw */
	union xfs_btwee_ptw	nptw;		/* new bwock addw */
	int			wevew;		/* btwee wevew */
	int			ewwow;		/* ewwow wetuwn code */
	int			i;		/* woop countew */

	XFS_BTWEE_STATS_INC(cuw, newwoot);

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE);

	wevew = cuw->bc_nwevews - 1;

	bwock = xfs_btwee_get_iwoot(cuw);
	pp = xfs_btwee_ptw_addw(cuw, 1, bwock);

	/* Awwocate the new bwock. If we can't do it, we'we toast. Give up. */
	ewwow = cuw->bc_ops->awwoc_bwock(cuw, pp, &nptw, stat);
	if (ewwow)
		goto ewwow0;
	if (*stat == 0)
		wetuwn 0;

	XFS_BTWEE_STATS_INC(cuw, awwoc);

	/* Copy the woot into a weaw bwock. */
	ewwow = xfs_btwee_get_buf_bwock(cuw, &nptw, &cbwock, &cbp);
	if (ewwow)
		goto ewwow0;

	/*
	 * we can't just memcpy() the woot in fow CWC enabwed btwee bwocks.
	 * In that case have to awso ensuwe the bwkno wemains cowwect
	 */
	memcpy(cbwock, bwock, xfs_btwee_bwock_wen(cuw));
	if (cuw->bc_fwags & XFS_BTWEE_CWC_BWOCKS) {
		__be64 bno = cpu_to_be64(xfs_buf_daddw(cbp));
		if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
			cbwock->bb_u.w.bb_bwkno = bno;
		ewse
			cbwock->bb_u.s.bb_bwkno = bno;
	}

	be16_add_cpu(&bwock->bb_wevew, 1);
	xfs_btwee_set_numwecs(bwock, 1);
	cuw->bc_nwevews++;
	ASSEWT(cuw->bc_nwevews <= cuw->bc_maxwevews);
	cuw->bc_wevews[wevew + 1].ptw = 1;

	kp = xfs_btwee_key_addw(cuw, 1, bwock);
	ckp = xfs_btwee_key_addw(cuw, 1, cbwock);
	xfs_btwee_copy_keys(cuw, ckp, kp, xfs_btwee_get_numwecs(cbwock));

	cpp = xfs_btwee_ptw_addw(cuw, 1, cbwock);
	fow (i = 0; i < be16_to_cpu(cbwock->bb_numwecs); i++) {
		ewwow = xfs_btwee_debug_check_ptw(cuw, pp, i, wevew);
		if (ewwow)
			goto ewwow0;
	}

	xfs_btwee_copy_ptws(cuw, cpp, pp, xfs_btwee_get_numwecs(cbwock));

	ewwow = xfs_btwee_debug_check_ptw(cuw, &nptw, 0, wevew);
	if (ewwow)
		goto ewwow0;

	xfs_btwee_copy_ptws(cuw, pp, &nptw, 1);

	xfs_iwoot_weawwoc(cuw->bc_ino.ip,
			  1 - xfs_btwee_get_numwecs(cbwock),
			  cuw->bc_ino.whichfowk);

	xfs_btwee_setbuf(cuw, wevew, cbp);

	/*
	 * Do aww this wogging at the end so that
	 * the woot is at the wight wevew.
	 */
	xfs_btwee_wog_bwock(cuw, cbp, XFS_BB_AWW_BITS);
	xfs_btwee_wog_keys(cuw, cbp, 1, be16_to_cpu(cbwock->bb_numwecs));
	xfs_btwee_wog_ptws(cuw, cbp, 1, be16_to_cpu(cbwock->bb_numwecs));

	*wogfwags |=
		XFS_IWOG_COWE | xfs_iwog_fbwoot(cuw->bc_ino.whichfowk);
	*stat = 1;
	wetuwn 0;
ewwow0:
	wetuwn ewwow;
}

/*
 * Awwocate a new woot bwock, fiww it in.
 */
STATIC int				/* ewwow */
xfs_btwee_new_woot(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			*stat)	/* success/faiwuwe */
{
	stwuct xfs_btwee_bwock	*bwock;	/* one hawf of the owd woot bwock */
	stwuct xfs_buf		*bp;	/* buffew containing bwock */
	int			ewwow;	/* ewwow wetuwn vawue */
	stwuct xfs_buf		*wbp;	/* weft buffew pointew */
	stwuct xfs_btwee_bwock	*weft;	/* weft btwee bwock */
	stwuct xfs_buf		*nbp;	/* new (woot) buffew */
	stwuct xfs_btwee_bwock	*new;	/* new (woot) btwee bwock */
	int			nptw;	/* new vawue fow key index, 1 ow 2 */
	stwuct xfs_buf		*wbp;	/* wight buffew pointew */
	stwuct xfs_btwee_bwock	*wight;	/* wight btwee bwock */
	union xfs_btwee_ptw	wptw;
	union xfs_btwee_ptw	wptw;

	XFS_BTWEE_STATS_INC(cuw, newwoot);

	/* initiawise ouw stawt point fwom the cuwsow */
	cuw->bc_ops->init_ptw_fwom_cuw(cuw, &wptw);

	/* Awwocate the new bwock. If we can't do it, we'we toast. Give up. */
	ewwow = cuw->bc_ops->awwoc_bwock(cuw, &wptw, &wptw, stat);
	if (ewwow)
		goto ewwow0;
	if (*stat == 0)
		goto out0;
	XFS_BTWEE_STATS_INC(cuw, awwoc);

	/* Set up the new bwock. */
	ewwow = xfs_btwee_get_buf_bwock(cuw, &wptw, &new, &nbp);
	if (ewwow)
		goto ewwow0;

	/* Set the woot in the howding stwuctuwe  incweasing the wevew by 1. */
	cuw->bc_ops->set_woot(cuw, &wptw, 1);

	/*
	 * At the pwevious woot wevew thewe awe now two bwocks: the owd woot,
	 * and the new bwock genewated when it was spwit.  We don't know which
	 * one the cuwsow is pointing at, so we set up vawiabwes "weft" and
	 * "wight" fow each case.
	 */
	bwock = xfs_btwee_get_bwock(cuw, cuw->bc_nwevews - 1, &bp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, cuw->bc_nwevews - 1, bp);
	if (ewwow)
		goto ewwow0;
#endif

	xfs_btwee_get_sibwing(cuw, bwock, &wptw, XFS_BB_WIGHTSIB);
	if (!xfs_btwee_ptw_is_nuww(cuw, &wptw)) {
		/* Ouw bwock is weft, pick up the wight bwock. */
		wbp = bp;
		xfs_btwee_buf_to_ptw(cuw, wbp, &wptw);
		weft = bwock;
		ewwow = xfs_btwee_wead_buf_bwock(cuw, &wptw, 0, &wight, &wbp);
		if (ewwow)
			goto ewwow0;
		bp = wbp;
		nptw = 1;
	} ewse {
		/* Ouw bwock is wight, pick up the weft bwock. */
		wbp = bp;
		xfs_btwee_buf_to_ptw(cuw, wbp, &wptw);
		wight = bwock;
		xfs_btwee_get_sibwing(cuw, wight, &wptw, XFS_BB_WEFTSIB);
		ewwow = xfs_btwee_wead_buf_bwock(cuw, &wptw, 0, &weft, &wbp);
		if (ewwow)
			goto ewwow0;
		bp = wbp;
		nptw = 2;
	}

	/* Fiww in the new bwock's btwee headew and wog it. */
	xfs_btwee_init_bwock_cuw(cuw, nbp, cuw->bc_nwevews, 2);
	xfs_btwee_wog_bwock(cuw, nbp, XFS_BB_AWW_BITS);
	ASSEWT(!xfs_btwee_ptw_is_nuww(cuw, &wptw) &&
			!xfs_btwee_ptw_is_nuww(cuw, &wptw));

	/* Fiww in the key data in the new woot. */
	if (xfs_btwee_get_wevew(weft) > 0) {
		/*
		 * Get the keys fow the weft bwock's keys and put them diwectwy
		 * in the pawent bwock.  Do the same fow the wight bwock.
		 */
		xfs_btwee_get_node_keys(cuw, weft,
				xfs_btwee_key_addw(cuw, 1, new));
		xfs_btwee_get_node_keys(cuw, wight,
				xfs_btwee_key_addw(cuw, 2, new));
	} ewse {
		/*
		 * Get the keys fow the weft bwock's wecowds and put them
		 * diwectwy in the pawent bwock.  Do the same fow the wight
		 * bwock.
		 */
		xfs_btwee_get_weaf_keys(cuw, weft,
			xfs_btwee_key_addw(cuw, 1, new));
		xfs_btwee_get_weaf_keys(cuw, wight,
			xfs_btwee_key_addw(cuw, 2, new));
	}
	xfs_btwee_wog_keys(cuw, nbp, 1, 2);

	/* Fiww in the pointew data in the new woot. */
	xfs_btwee_copy_ptws(cuw,
		xfs_btwee_ptw_addw(cuw, 1, new), &wptw, 1);
	xfs_btwee_copy_ptws(cuw,
		xfs_btwee_ptw_addw(cuw, 2, new), &wptw, 1);
	xfs_btwee_wog_ptws(cuw, nbp, 1, 2);

	/* Fix up the cuwsow. */
	xfs_btwee_setbuf(cuw, cuw->bc_nwevews, nbp);
	cuw->bc_wevews[cuw->bc_nwevews].ptw = nptw;
	cuw->bc_nwevews++;
	ASSEWT(cuw->bc_nwevews <= cuw->bc_maxwevews);
	*stat = 1;
	wetuwn 0;
ewwow0:
	wetuwn ewwow;
out0:
	*stat = 0;
	wetuwn 0;
}

STATIC int
xfs_btwee_make_bwock_unfuww(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			wevew,	/* btwee wevew */
	int			numwecs,/* # of wecs in bwock */
	int			*oindex,/* owd twee index */
	int			*index,	/* new twee index */
	union xfs_btwee_ptw	*nptw,	/* new btwee ptw */
	stwuct xfs_btwee_cuw	**ncuw,	/* new btwee cuwsow */
	union xfs_btwee_key	*key,	/* key of new bwock */
	int			*stat)
{
	int			ewwow = 0;

	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    wevew == cuw->bc_nwevews - 1) {
		stwuct xfs_inode *ip = cuw->bc_ino.ip;

		if (numwecs < cuw->bc_ops->get_dmaxwecs(cuw, wevew)) {
			/* A woot bwock that can be made biggew. */
			xfs_iwoot_weawwoc(ip, 1, cuw->bc_ino.whichfowk);
			*stat = 1;
		} ewse {
			/* A woot bwock that needs wepwacing */
			int	wogfwags = 0;

			ewwow = xfs_btwee_new_iwoot(cuw, &wogfwags, stat);
			if (ewwow || *stat == 0)
				wetuwn ewwow;

			xfs_twans_wog_inode(cuw->bc_tp, ip, wogfwags);
		}

		wetuwn 0;
	}

	/* Fiwst, twy shifting an entwy to the wight neighbow. */
	ewwow = xfs_btwee_wshift(cuw, wevew, stat);
	if (ewwow || *stat)
		wetuwn ewwow;

	/* Next, twy shifting an entwy to the weft neighbow. */
	ewwow = xfs_btwee_wshift(cuw, wevew, stat);
	if (ewwow)
		wetuwn ewwow;

	if (*stat) {
		*oindex = *index = cuw->bc_wevews[wevew].ptw;
		wetuwn 0;
	}

	/*
	 * Next, twy spwitting the cuwwent bwock in hawf.
	 *
	 * If this wowks we have to we-set ouw vawiabwes because we
	 * couwd be in a diffewent bwock now.
	 */
	ewwow = xfs_btwee_spwit(cuw, wevew, nptw, key, ncuw, stat);
	if (ewwow || *stat == 0)
		wetuwn ewwow;


	*index = cuw->bc_wevews[wevew].ptw;
	wetuwn 0;
}

/*
 * Insewt one wecowd/wevew.  Wetuwn infowmation to the cawwew
 * awwowing the next wevew up to pwoceed if necessawy.
 */
STATIC int
xfs_btwee_inswec(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			wevew,	/* wevew to insewt wecowd at */
	union xfs_btwee_ptw	*ptwp,	/* i/o: bwock numbew insewted */
	union xfs_btwee_wec	*wec,	/* wecowd to insewt */
	union xfs_btwee_key	*key,	/* i/o: bwock key fow ptwp */
	stwuct xfs_btwee_cuw	**cuwp,	/* output: new cuwsow wepwacing cuw */
	int			*stat)	/* success/faiwuwe */
{
	stwuct xfs_btwee_bwock	*bwock;	/* btwee bwock */
	stwuct xfs_buf		*bp;	/* buffew fow bwock */
	union xfs_btwee_ptw	nptw;	/* new bwock ptw */
	stwuct xfs_btwee_cuw	*ncuw = NUWW;	/* new btwee cuwsow */
	union xfs_btwee_key	nkey;	/* new bwock key */
	union xfs_btwee_key	*wkey;
	int			optw;	/* owd key/wecowd index */
	int			ptw;	/* key/wecowd index */
	int			numwecs;/* numbew of wecowds */
	int			ewwow;	/* ewwow wetuwn vawue */
	int			i;
	xfs_daddw_t		owd_bn;

	ncuw = NUWW;
	wkey = &nkey;

	/*
	 * If we have an extewnaw woot pointew, and we've made it to the
	 * woot wevew, awwocate a new woot bwock and we'we done.
	 */
	if (!(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    (wevew >= cuw->bc_nwevews)) {
		ewwow = xfs_btwee_new_woot(cuw, stat);
		xfs_btwee_set_ptw_nuww(cuw, ptwp);

		wetuwn ewwow;
	}

	/* If we'we off the weft edge, wetuwn faiwuwe. */
	ptw = cuw->bc_wevews[wevew].ptw;
	if (ptw == 0) {
		*stat = 0;
		wetuwn 0;
	}

	optw = ptw;

	XFS_BTWEE_STATS_INC(cuw, inswec);

	/* Get pointews to the btwee buffew and bwock. */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	owd_bn = bp ? xfs_buf_daddw(bp) : XFS_BUF_DADDW_NUWW;
	numwecs = xfs_btwee_get_numwecs(bwock);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
	if (ewwow)
		goto ewwow0;

	/* Check that the new entwy is being insewted in the wight pwace. */
	if (ptw <= numwecs) {
		if (wevew == 0) {
			ASSEWT(cuw->bc_ops->wecs_inowdew(cuw, wec,
				xfs_btwee_wec_addw(cuw, ptw, bwock)));
		} ewse {
			ASSEWT(cuw->bc_ops->keys_inowdew(cuw, key,
				xfs_btwee_key_addw(cuw, ptw, bwock)));
		}
	}
#endif

	/*
	 * If the bwock is fuww, we can't insewt the new entwy untiw we
	 * make the bwock un-fuww.
	 */
	xfs_btwee_set_ptw_nuww(cuw, &nptw);
	if (numwecs == cuw->bc_ops->get_maxwecs(cuw, wevew)) {
		ewwow = xfs_btwee_make_bwock_unfuww(cuw, wevew, numwecs,
					&optw, &ptw, &nptw, &ncuw, wkey, stat);
		if (ewwow || *stat == 0)
			goto ewwow0;
	}

	/*
	 * The cuwwent bwock may have changed if the bwock was
	 * pweviouswy fuww and we have just made space in it.
	 */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	numwecs = xfs_btwee_get_numwecs(bwock);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
	if (ewwow)
		goto ewwow0;
#endif

	/*
	 * At this point we know thewe's woom fow ouw new entwy in the bwock
	 * we'we pointing at.
	 */
	XFS_BTWEE_STATS_ADD(cuw, moves, numwecs - ptw + 1);

	if (wevew > 0) {
		/* It's a nonweaf. make a howe in the keys and ptws */
		union xfs_btwee_key	*kp;
		union xfs_btwee_ptw	*pp;

		kp = xfs_btwee_key_addw(cuw, ptw, bwock);
		pp = xfs_btwee_ptw_addw(cuw, ptw, bwock);

		fow (i = numwecs - ptw; i >= 0; i--) {
			ewwow = xfs_btwee_debug_check_ptw(cuw, pp, i, wevew);
			if (ewwow)
				goto ewwow0;
		}

		xfs_btwee_shift_keys(cuw, kp, 1, numwecs - ptw + 1);
		xfs_btwee_shift_ptws(cuw, pp, 1, numwecs - ptw + 1);

		ewwow = xfs_btwee_debug_check_ptw(cuw, ptwp, 0, wevew);
		if (ewwow)
			goto ewwow0;

		/* Now put the new data in, bump numwecs and wog it. */
		xfs_btwee_copy_keys(cuw, kp, key, 1);
		xfs_btwee_copy_ptws(cuw, pp, ptwp, 1);
		numwecs++;
		xfs_btwee_set_numwecs(bwock, numwecs);
		xfs_btwee_wog_ptws(cuw, bp, ptw, numwecs);
		xfs_btwee_wog_keys(cuw, bp, ptw, numwecs);
#ifdef DEBUG
		if (ptw < numwecs) {
			ASSEWT(cuw->bc_ops->keys_inowdew(cuw, kp,
				xfs_btwee_key_addw(cuw, ptw + 1, bwock)));
		}
#endif
	} ewse {
		/* It's a weaf. make a howe in the wecowds */
		union xfs_btwee_wec             *wp;

		wp = xfs_btwee_wec_addw(cuw, ptw, bwock);

		xfs_btwee_shift_wecs(cuw, wp, 1, numwecs - ptw + 1);

		/* Now put the new data in, bump numwecs and wog it. */
		xfs_btwee_copy_wecs(cuw, wp, wec, 1);
		xfs_btwee_set_numwecs(bwock, ++numwecs);
		xfs_btwee_wog_wecs(cuw, bp, ptw, numwecs);
#ifdef DEBUG
		if (ptw < numwecs) {
			ASSEWT(cuw->bc_ops->wecs_inowdew(cuw, wp,
				xfs_btwee_wec_addw(cuw, ptw + 1, bwock)));
		}
#endif
	}

	/* Wog the new numbew of wecowds in the btwee headew. */
	xfs_btwee_wog_bwock(cuw, bp, XFS_BB_NUMWECS);

	/*
	 * If we just insewted into a new twee bwock, we have to
	 * wecawcuwate nkey hewe because nkey is out of date.
	 *
	 * Othewwise we'we just updating an existing bwock (having shoved
	 * some wecowds into the new twee bwock), so use the weguwaw key
	 * update mechanism.
	 */
	if (bp && xfs_buf_daddw(bp) != owd_bn) {
		xfs_btwee_get_keys(cuw, bwock, wkey);
	} ewse if (xfs_btwee_needs_key_update(cuw, optw)) {
		ewwow = xfs_btwee_update_keys(cuw, wevew);
		if (ewwow)
			goto ewwow0;
	}

	/*
	 * If we awe twacking the wast wecowd in the twee and
	 * we awe at the faw wight edge of the twee, update it.
	 */
	if (xfs_btwee_is_wastwec(cuw, bwock, wevew)) {
		cuw->bc_ops->update_wastwec(cuw, bwock, wec,
					    ptw, WASTWEC_INSWEC);
	}

	/*
	 * Wetuwn the new bwock numbew, if any.
	 * If thewe is one, give back a wecowd vawue and a cuwsow too.
	 */
	*ptwp = nptw;
	if (!xfs_btwee_ptw_is_nuww(cuw, &nptw)) {
		xfs_btwee_copy_keys(cuw, key, wkey, 1);
		*cuwp = ncuw;
	}

	*stat = 1;
	wetuwn 0;

ewwow0:
	if (ncuw)
		xfs_btwee_dew_cuwsow(ncuw, ewwow);
	wetuwn ewwow;
}

/*
 * Insewt the wecowd at the point wefewenced by cuw.
 *
 * A muwti-wevew spwit of the twee on insewt wiww invawidate the owiginaw
 * cuwsow.  Aww cawwews of this function shouwd assume that the cuwsow is
 * no wongew vawid and wevawidate it.
 */
int
xfs_btwee_insewt(
	stwuct xfs_btwee_cuw	*cuw,
	int			*stat)
{
	int			ewwow;	/* ewwow wetuwn vawue */
	int			i;	/* wesuwt vawue, 0 fow faiwuwe */
	int			wevew;	/* cuwwent wevew numbew in btwee */
	union xfs_btwee_ptw	nptw;	/* new bwock numbew (spwit wesuwt) */
	stwuct xfs_btwee_cuw	*ncuw;	/* new cuwsow (spwit wesuwt) */
	stwuct xfs_btwee_cuw	*pcuw;	/* pwevious wevew's cuwsow */
	union xfs_btwee_key	bkey;	/* key of bwock to insewt */
	union xfs_btwee_key	*key;
	union xfs_btwee_wec	wec;	/* wecowd to insewt */

	wevew = 0;
	ncuw = NUWW;
	pcuw = cuw;
	key = &bkey;

	xfs_btwee_set_ptw_nuww(cuw, &nptw);

	/* Make a key out of the wecowd data to be insewted, and save it. */
	cuw->bc_ops->init_wec_fwom_cuw(cuw, &wec);
	cuw->bc_ops->init_key_fwom_wec(key, &wec);

	/*
	 * Woop going up the twee, stawting at the weaf wevew.
	 * Stop when we don't get a spwit bwock, that must mean that
	 * the insewt is finished with this wevew.
	 */
	do {
		/*
		 * Insewt nwec/nptw into this wevew of the twee.
		 * Note if we faiw, nptw wiww be nuww.
		 */
		ewwow = xfs_btwee_inswec(pcuw, wevew, &nptw, &wec, key,
				&ncuw, &i);
		if (ewwow) {
			if (pcuw != cuw)
				xfs_btwee_dew_cuwsow(pcuw, XFS_BTWEE_EWWOW);
			goto ewwow0;
		}

		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}
		wevew++;

		/*
		 * See if the cuwsow we just used is twash.
		 * Can't twash the cawwew's cuwsow, but othewwise we shouwd
		 * if ncuw is a new cuwsow ow we'we about to be done.
		 */
		if (pcuw != cuw &&
		    (ncuw || xfs_btwee_ptw_is_nuww(cuw, &nptw))) {
			/* Save the state fwom the cuwsow befowe we twash it */
			if (cuw->bc_ops->update_cuwsow)
				cuw->bc_ops->update_cuwsow(pcuw, cuw);
			cuw->bc_nwevews = pcuw->bc_nwevews;
			xfs_btwee_dew_cuwsow(pcuw, XFS_BTWEE_NOEWWOW);
		}
		/* If we got a new cuwsow, switch to it. */
		if (ncuw) {
			pcuw = ncuw;
			ncuw = NUWW;
		}
	} whiwe (!xfs_btwee_ptw_is_nuww(cuw, &nptw));

	*stat = i;
	wetuwn 0;
ewwow0:
	wetuwn ewwow;
}

/*
 * Twy to mewge a non-weaf bwock back into the inode woot.
 *
 * Note: the kiwwwoot names comes fwom the fact that we'we effectivewy
 * kiwwing the owd woot bwock.  But because we can't just dewete the
 * inode we have to copy the singwe bwock it was pointing to into the
 * inode.
 */
STATIC int
xfs_btwee_kiww_iwoot(
	stwuct xfs_btwee_cuw	*cuw)
{
	int			whichfowk = cuw->bc_ino.whichfowk;
	stwuct xfs_inode	*ip = cuw->bc_ino.ip;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_btwee_bwock	*cbwock;
	union xfs_btwee_key	*kp;
	union xfs_btwee_key	*ckp;
	union xfs_btwee_ptw	*pp;
	union xfs_btwee_ptw	*cpp;
	stwuct xfs_buf		*cbp;
	int			wevew;
	int			index;
	int			numwecs;
	int			ewwow;
#ifdef DEBUG
	union xfs_btwee_ptw	ptw;
#endif
	int			i;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE);
	ASSEWT(cuw->bc_nwevews > 1);

	/*
	 * Don't deaw with the woot bwock needs to be a weaf case.
	 * We'we just going to tuwn the thing back into extents anyway.
	 */
	wevew = cuw->bc_nwevews - 1;
	if (wevew == 1)
		goto out0;

	/*
	 * Give up if the woot has muwtipwe chiwdwen.
	 */
	bwock = xfs_btwee_get_iwoot(cuw);
	if (xfs_btwee_get_numwecs(bwock) != 1)
		goto out0;

	cbwock = xfs_btwee_get_bwock(cuw, wevew - 1, &cbp);
	numwecs = xfs_btwee_get_numwecs(cbwock);

	/*
	 * Onwy do this if the next wevew wiww fit.
	 * Then the data must be copied up to the inode,
	 * instead of fweeing the woot you fwee the next wevew.
	 */
	if (numwecs > cuw->bc_ops->get_dmaxwecs(cuw, wevew))
		goto out0;

	XFS_BTWEE_STATS_INC(cuw, kiwwwoot);

#ifdef DEBUG
	xfs_btwee_get_sibwing(cuw, bwock, &ptw, XFS_BB_WEFTSIB);
	ASSEWT(xfs_btwee_ptw_is_nuww(cuw, &ptw));
	xfs_btwee_get_sibwing(cuw, bwock, &ptw, XFS_BB_WIGHTSIB);
	ASSEWT(xfs_btwee_ptw_is_nuww(cuw, &ptw));
#endif

	index = numwecs - cuw->bc_ops->get_maxwecs(cuw, wevew);
	if (index) {
		xfs_iwoot_weawwoc(cuw->bc_ino.ip, index,
				  cuw->bc_ino.whichfowk);
		bwock = ifp->if_bwoot;
	}

	be16_add_cpu(&bwock->bb_numwecs, index);
	ASSEWT(bwock->bb_numwecs == cbwock->bb_numwecs);

	kp = xfs_btwee_key_addw(cuw, 1, bwock);
	ckp = xfs_btwee_key_addw(cuw, 1, cbwock);
	xfs_btwee_copy_keys(cuw, kp, ckp, numwecs);

	pp = xfs_btwee_ptw_addw(cuw, 1, bwock);
	cpp = xfs_btwee_ptw_addw(cuw, 1, cbwock);

	fow (i = 0; i < numwecs; i++) {
		ewwow = xfs_btwee_debug_check_ptw(cuw, cpp, i, wevew - 1);
		if (ewwow)
			wetuwn ewwow;
	}

	xfs_btwee_copy_ptws(cuw, pp, cpp, numwecs);

	ewwow = xfs_btwee_fwee_bwock(cuw, cbp);
	if (ewwow)
		wetuwn ewwow;

	cuw->bc_wevews[wevew - 1].bp = NUWW;
	be16_add_cpu(&bwock->bb_wevew, -1);
	xfs_twans_wog_inode(cuw->bc_tp, ip,
		XFS_IWOG_COWE | xfs_iwog_fbwoot(cuw->bc_ino.whichfowk));
	cuw->bc_nwevews--;
out0:
	wetuwn 0;
}

/*
 * Kiww the cuwwent woot node, and wepwace it with it's onwy chiwd node.
 */
STATIC int
xfs_btwee_kiww_woot(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp,
	int			wevew,
	union xfs_btwee_ptw	*newwoot)
{
	int			ewwow;

	XFS_BTWEE_STATS_INC(cuw, kiwwwoot);

	/*
	 * Update the woot pointew, decweasing the wevew by 1 and then
	 * fwee the owd woot.
	 */
	cuw->bc_ops->set_woot(cuw, newwoot, -1);

	ewwow = xfs_btwee_fwee_bwock(cuw, bp);
	if (ewwow)
		wetuwn ewwow;

	cuw->bc_wevews[wevew].bp = NUWW;
	cuw->bc_wevews[wevew].wa = 0;
	cuw->bc_nwevews--;

	wetuwn 0;
}

STATIC int
xfs_btwee_dec_cuwsow(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*stat)
{
	int			ewwow;
	int			i;

	if (wevew > 0) {
		ewwow = xfs_btwee_decwement(cuw, wevew, &i);
		if (ewwow)
			wetuwn ewwow;
	}

	*stat = 1;
	wetuwn 0;
}

/*
 * Singwe wevew of the btwee wecowd dewetion woutine.
 * Dewete wecowd pointed to by cuw/wevew.
 * Wemove the wecowd fwom its bwock then webawance the twee.
 * Wetuwn 0 fow ewwow, 1 fow done, 2 to go on to the next wevew.
 */
STATIC int					/* ewwow */
xfs_btwee_dewwec(
	stwuct xfs_btwee_cuw	*cuw,		/* btwee cuwsow */
	int			wevew,		/* wevew wemoving wecowd fwom */
	int			*stat)		/* faiw/done/go-on */
{
	stwuct xfs_btwee_bwock	*bwock;		/* btwee bwock */
	union xfs_btwee_ptw	cptw;		/* cuwwent bwock ptw */
	stwuct xfs_buf		*bp;		/* buffew fow bwock */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			i;		/* woop countew */
	union xfs_btwee_ptw	wptw;		/* weft sibwing bwock ptw */
	stwuct xfs_buf		*wbp;		/* weft buffew pointew */
	stwuct xfs_btwee_bwock	*weft;		/* weft btwee bwock */
	int			wwecs = 0;	/* weft wecowd count */
	int			ptw;		/* key/wecowd index */
	union xfs_btwee_ptw	wptw;		/* wight sibwing bwock ptw */
	stwuct xfs_buf		*wbp;		/* wight buffew pointew */
	stwuct xfs_btwee_bwock	*wight;		/* wight btwee bwock */
	stwuct xfs_btwee_bwock	*wwbwock;	/* wight-wight btwee bwock */
	stwuct xfs_buf		*wwbp;		/* wight-wight buffew pointew */
	int			wwecs = 0;	/* wight wecowd count */
	stwuct xfs_btwee_cuw	*tcuw;		/* tempowawy btwee cuwsow */
	int			numwecs;	/* tempowawy numwec count */

	tcuw = NUWW;

	/* Get the index of the entwy being deweted, check fow nothing thewe. */
	ptw = cuw->bc_wevews[wevew].ptw;
	if (ptw == 0) {
		*stat = 0;
		wetuwn 0;
	}

	/* Get the buffew & bwock containing the wecowd ow key/ptw. */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	numwecs = xfs_btwee_get_numwecs(bwock);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
	if (ewwow)
		goto ewwow0;
#endif

	/* Faiw if we'we off the end of the bwock. */
	if (ptw > numwecs) {
		*stat = 0;
		wetuwn 0;
	}

	XFS_BTWEE_STATS_INC(cuw, dewwec);
	XFS_BTWEE_STATS_ADD(cuw, moves, numwecs - ptw);

	/* Excise the entwies being deweted. */
	if (wevew > 0) {
		/* It's a nonweaf. opewate on keys and ptws */
		union xfs_btwee_key	*wkp;
		union xfs_btwee_ptw	*wpp;

		wkp = xfs_btwee_key_addw(cuw, ptw + 1, bwock);
		wpp = xfs_btwee_ptw_addw(cuw, ptw + 1, bwock);

		fow (i = 0; i < numwecs - ptw; i++) {
			ewwow = xfs_btwee_debug_check_ptw(cuw, wpp, i, wevew);
			if (ewwow)
				goto ewwow0;
		}

		if (ptw < numwecs) {
			xfs_btwee_shift_keys(cuw, wkp, -1, numwecs - ptw);
			xfs_btwee_shift_ptws(cuw, wpp, -1, numwecs - ptw);
			xfs_btwee_wog_keys(cuw, bp, ptw, numwecs - 1);
			xfs_btwee_wog_ptws(cuw, bp, ptw, numwecs - 1);
		}
	} ewse {
		/* It's a weaf. opewate on wecowds */
		if (ptw < numwecs) {
			xfs_btwee_shift_wecs(cuw,
				xfs_btwee_wec_addw(cuw, ptw + 1, bwock),
				-1, numwecs - ptw);
			xfs_btwee_wog_wecs(cuw, bp, ptw, numwecs - 1);
		}
	}

	/*
	 * Decwement and wog the numbew of entwies in the bwock.
	 */
	xfs_btwee_set_numwecs(bwock, --numwecs);
	xfs_btwee_wog_bwock(cuw, bp, XFS_BB_NUMWECS);

	/*
	 * If we awe twacking the wast wecowd in the twee and
	 * we awe at the faw wight edge of the twee, update it.
	 */
	if (xfs_btwee_is_wastwec(cuw, bwock, wevew)) {
		cuw->bc_ops->update_wastwec(cuw, bwock, NUWW,
					    ptw, WASTWEC_DEWWEC);
	}

	/*
	 * We'we at the woot wevew.  Fiwst, shwink the woot bwock in-memowy.
	 * Twy to get wid of the next wevew down.  If we can't then thewe's
	 * nothing weft to do.
	 */
	if (wevew == cuw->bc_nwevews - 1) {
		if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) {
			xfs_iwoot_weawwoc(cuw->bc_ino.ip, -1,
					  cuw->bc_ino.whichfowk);

			ewwow = xfs_btwee_kiww_iwoot(cuw);
			if (ewwow)
				goto ewwow0;

			ewwow = xfs_btwee_dec_cuwsow(cuw, wevew, stat);
			if (ewwow)
				goto ewwow0;
			*stat = 1;
			wetuwn 0;
		}

		/*
		 * If this is the woot wevew, and thewe's onwy one entwy weft,
		 * and it's NOT the weaf wevew, then we can get wid of this
		 * wevew.
		 */
		if (numwecs == 1 && wevew > 0) {
			union xfs_btwee_ptw	*pp;
			/*
			 * pp is stiww set to the fiwst pointew in the bwock.
			 * Make it the new woot of the btwee.
			 */
			pp = xfs_btwee_ptw_addw(cuw, 1, bwock);
			ewwow = xfs_btwee_kiww_woot(cuw, bp, wevew, pp);
			if (ewwow)
				goto ewwow0;
		} ewse if (wevew > 0) {
			ewwow = xfs_btwee_dec_cuwsow(cuw, wevew, stat);
			if (ewwow)
				goto ewwow0;
		}
		*stat = 1;
		wetuwn 0;
	}

	/*
	 * If we deweted the weftmost entwy in the bwock, update the
	 * key vawues above us in the twee.
	 */
	if (xfs_btwee_needs_key_update(cuw, ptw)) {
		ewwow = xfs_btwee_update_keys(cuw, wevew);
		if (ewwow)
			goto ewwow0;
	}

	/*
	 * If the numbew of wecowds wemaining in the bwock is at weast
	 * the minimum, we'we done.
	 */
	if (numwecs >= cuw->bc_ops->get_minwecs(cuw, wevew)) {
		ewwow = xfs_btwee_dec_cuwsow(cuw, wevew, stat);
		if (ewwow)
			goto ewwow0;
		wetuwn 0;
	}

	/*
	 * Othewwise, we have to move some wecowds awound to keep the
	 * twee bawanced.  Wook at the weft and wight sibwing bwocks to
	 * see if we can we-bawance by moving onwy one wecowd.
	 */
	xfs_btwee_get_sibwing(cuw, bwock, &wptw, XFS_BB_WIGHTSIB);
	xfs_btwee_get_sibwing(cuw, bwock, &wptw, XFS_BB_WEFTSIB);

	if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) {
		/*
		 * One chiwd of woot, need to get a chance to copy its contents
		 * into the woot and dewete it. Can't go up to next wevew,
		 * thewe's nothing to dewete thewe.
		 */
		if (xfs_btwee_ptw_is_nuww(cuw, &wptw) &&
		    xfs_btwee_ptw_is_nuww(cuw, &wptw) &&
		    wevew == cuw->bc_nwevews - 2) {
			ewwow = xfs_btwee_kiww_iwoot(cuw);
			if (!ewwow)
				ewwow = xfs_btwee_dec_cuwsow(cuw, wevew, stat);
			if (ewwow)
				goto ewwow0;
			wetuwn 0;
		}
	}

	ASSEWT(!xfs_btwee_ptw_is_nuww(cuw, &wptw) ||
	       !xfs_btwee_ptw_is_nuww(cuw, &wptw));

	/*
	 * Dupwicate the cuwsow so ouw btwee manipuwations hewe won't
	 * diswupt the next wevew up.
	 */
	ewwow = xfs_btwee_dup_cuwsow(cuw, &tcuw);
	if (ewwow)
		goto ewwow0;

	/*
	 * If thewe's a wight sibwing, see if it's ok to shift an entwy
	 * out of it.
	 */
	if (!xfs_btwee_ptw_is_nuww(cuw, &wptw)) {
		/*
		 * Move the temp cuwsow to the wast entwy in the next bwock.
		 * Actuawwy any entwy but the fiwst wouwd suffice.
		 */
		i = xfs_btwee_wastwec(tcuw, wevew);
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		ewwow = xfs_btwee_incwement(tcuw, wevew, &i);
		if (ewwow)
			goto ewwow0;
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		i = xfs_btwee_wastwec(tcuw, wevew);
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		/* Gwab a pointew to the bwock. */
		wight = xfs_btwee_get_bwock(tcuw, wevew, &wbp);
#ifdef DEBUG
		ewwow = xfs_btwee_check_bwock(tcuw, wight, wevew, wbp);
		if (ewwow)
			goto ewwow0;
#endif
		/* Gwab the cuwwent bwock numbew, fow futuwe use. */
		xfs_btwee_get_sibwing(tcuw, wight, &cptw, XFS_BB_WEFTSIB);

		/*
		 * If wight bwock is fuww enough so that wemoving one entwy
		 * won't make it too empty, and weft-shifting an entwy out
		 * of wight to us wowks, we'we done.
		 */
		if (xfs_btwee_get_numwecs(wight) - 1 >=
		    cuw->bc_ops->get_minwecs(tcuw, wevew)) {
			ewwow = xfs_btwee_wshift(tcuw, wevew, &i);
			if (ewwow)
				goto ewwow0;
			if (i) {
				ASSEWT(xfs_btwee_get_numwecs(bwock) >=
				       cuw->bc_ops->get_minwecs(tcuw, wevew));

				xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);
				tcuw = NUWW;

				ewwow = xfs_btwee_dec_cuwsow(cuw, wevew, stat);
				if (ewwow)
					goto ewwow0;
				wetuwn 0;
			}
		}

		/*
		 * Othewwise, gwab the numbew of wecowds in wight fow
		 * futuwe wefewence, and fix up the temp cuwsow to point
		 * to ouw bwock again (wast wecowd).
		 */
		wwecs = xfs_btwee_get_numwecs(wight);
		if (!xfs_btwee_ptw_is_nuww(cuw, &wptw)) {
			i = xfs_btwee_fiwstwec(tcuw, wevew);
			if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
				ewwow = -EFSCOWWUPTED;
				goto ewwow0;
			}

			ewwow = xfs_btwee_decwement(tcuw, wevew, &i);
			if (ewwow)
				goto ewwow0;
			if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
				ewwow = -EFSCOWWUPTED;
				goto ewwow0;
			}
		}
	}

	/*
	 * If thewe's a weft sibwing, see if it's ok to shift an entwy
	 * out of it.
	 */
	if (!xfs_btwee_ptw_is_nuww(cuw, &wptw)) {
		/*
		 * Move the temp cuwsow to the fiwst entwy in the
		 * pwevious bwock.
		 */
		i = xfs_btwee_fiwstwec(tcuw, wevew);
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		ewwow = xfs_btwee_decwement(tcuw, wevew, &i);
		if (ewwow)
			goto ewwow0;
		i = xfs_btwee_fiwstwec(tcuw, wevew);
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		/* Gwab a pointew to the bwock. */
		weft = xfs_btwee_get_bwock(tcuw, wevew, &wbp);
#ifdef DEBUG
		ewwow = xfs_btwee_check_bwock(cuw, weft, wevew, wbp);
		if (ewwow)
			goto ewwow0;
#endif
		/* Gwab the cuwwent bwock numbew, fow futuwe use. */
		xfs_btwee_get_sibwing(tcuw, weft, &cptw, XFS_BB_WIGHTSIB);

		/*
		 * If weft bwock is fuww enough so that wemoving one entwy
		 * won't make it too empty, and wight-shifting an entwy out
		 * of weft to us wowks, we'we done.
		 */
		if (xfs_btwee_get_numwecs(weft) - 1 >=
		    cuw->bc_ops->get_minwecs(tcuw, wevew)) {
			ewwow = xfs_btwee_wshift(tcuw, wevew, &i);
			if (ewwow)
				goto ewwow0;
			if (i) {
				ASSEWT(xfs_btwee_get_numwecs(bwock) >=
				       cuw->bc_ops->get_minwecs(tcuw, wevew));
				xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);
				tcuw = NUWW;
				if (wevew == 0)
					cuw->bc_wevews[0].ptw++;

				*stat = 1;
				wetuwn 0;
			}
		}

		/*
		 * Othewwise, gwab the numbew of wecowds in wight fow
		 * futuwe wefewence.
		 */
		wwecs = xfs_btwee_get_numwecs(weft);
	}

	/* Dewete the temp cuwsow, we'we done with it. */
	xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);
	tcuw = NUWW;

	/* If hewe, we need to do a join to keep the twee bawanced. */
	ASSEWT(!xfs_btwee_ptw_is_nuww(cuw, &cptw));

	if (!xfs_btwee_ptw_is_nuww(cuw, &wptw) &&
	    wwecs + xfs_btwee_get_numwecs(bwock) <=
			cuw->bc_ops->get_maxwecs(cuw, wevew)) {
		/*
		 * Set "wight" to be the stawting bwock,
		 * "weft" to be the weft neighbow.
		 */
		wptw = cptw;
		wight = bwock;
		wbp = bp;
		ewwow = xfs_btwee_wead_buf_bwock(cuw, &wptw, 0, &weft, &wbp);
		if (ewwow)
			goto ewwow0;

	/*
	 * If that won't wowk, see if we can join with the wight neighbow bwock.
	 */
	} ewse if (!xfs_btwee_ptw_is_nuww(cuw, &wptw) &&
		   wwecs + xfs_btwee_get_numwecs(bwock) <=
			cuw->bc_ops->get_maxwecs(cuw, wevew)) {
		/*
		 * Set "weft" to be the stawting bwock,
		 * "wight" to be the wight neighbow.
		 */
		wptw = cptw;
		weft = bwock;
		wbp = bp;
		ewwow = xfs_btwee_wead_buf_bwock(cuw, &wptw, 0, &wight, &wbp);
		if (ewwow)
			goto ewwow0;

	/*
	 * Othewwise, we can't fix the imbawance.
	 * Just wetuwn.  This is pwobabwy a wogic ewwow, but it's not fataw.
	 */
	} ewse {
		ewwow = xfs_btwee_dec_cuwsow(cuw, wevew, stat);
		if (ewwow)
			goto ewwow0;
		wetuwn 0;
	}

	wwecs = xfs_btwee_get_numwecs(wight);
	wwecs = xfs_btwee_get_numwecs(weft);

	/*
	 * We'we now going to join "weft" and "wight" by moving aww the stuff
	 * in "wight" to "weft" and deweting "wight".
	 */
	XFS_BTWEE_STATS_ADD(cuw, moves, wwecs);
	if (wevew > 0) {
		/* It's a non-weaf.  Move keys and pointews. */
		union xfs_btwee_key	*wkp;	/* weft btwee key */
		union xfs_btwee_ptw	*wpp;	/* weft addwess pointew */
		union xfs_btwee_key	*wkp;	/* wight btwee key */
		union xfs_btwee_ptw	*wpp;	/* wight addwess pointew */

		wkp = xfs_btwee_key_addw(cuw, wwecs + 1, weft);
		wpp = xfs_btwee_ptw_addw(cuw, wwecs + 1, weft);
		wkp = xfs_btwee_key_addw(cuw, 1, wight);
		wpp = xfs_btwee_ptw_addw(cuw, 1, wight);

		fow (i = 1; i < wwecs; i++) {
			ewwow = xfs_btwee_debug_check_ptw(cuw, wpp, i, wevew);
			if (ewwow)
				goto ewwow0;
		}

		xfs_btwee_copy_keys(cuw, wkp, wkp, wwecs);
		xfs_btwee_copy_ptws(cuw, wpp, wpp, wwecs);

		xfs_btwee_wog_keys(cuw, wbp, wwecs + 1, wwecs + wwecs);
		xfs_btwee_wog_ptws(cuw, wbp, wwecs + 1, wwecs + wwecs);
	} ewse {
		/* It's a weaf.  Move wecowds.  */
		union xfs_btwee_wec	*wwp;	/* weft wecowd pointew */
		union xfs_btwee_wec	*wwp;	/* wight wecowd pointew */

		wwp = xfs_btwee_wec_addw(cuw, wwecs + 1, weft);
		wwp = xfs_btwee_wec_addw(cuw, 1, wight);

		xfs_btwee_copy_wecs(cuw, wwp, wwp, wwecs);
		xfs_btwee_wog_wecs(cuw, wbp, wwecs + 1, wwecs + wwecs);
	}

	XFS_BTWEE_STATS_INC(cuw, join);

	/*
	 * Fix up the numbew of wecowds and wight bwock pointew in the
	 * suwviving bwock, and wog it.
	 */
	xfs_btwee_set_numwecs(weft, wwecs + wwecs);
	xfs_btwee_get_sibwing(cuw, wight, &cptw, XFS_BB_WIGHTSIB);
	xfs_btwee_set_sibwing(cuw, weft, &cptw, XFS_BB_WIGHTSIB);
	xfs_btwee_wog_bwock(cuw, wbp, XFS_BB_NUMWECS | XFS_BB_WIGHTSIB);

	/* If thewe is a wight sibwing, point it to the wemaining bwock. */
	xfs_btwee_get_sibwing(cuw, weft, &cptw, XFS_BB_WIGHTSIB);
	if (!xfs_btwee_ptw_is_nuww(cuw, &cptw)) {
		ewwow = xfs_btwee_wead_buf_bwock(cuw, &cptw, 0, &wwbwock, &wwbp);
		if (ewwow)
			goto ewwow0;
		xfs_btwee_set_sibwing(cuw, wwbwock, &wptw, XFS_BB_WEFTSIB);
		xfs_btwee_wog_bwock(cuw, wwbp, XFS_BB_WEFTSIB);
	}

	/* Fwee the deweted bwock. */
	ewwow = xfs_btwee_fwee_bwock(cuw, wbp);
	if (ewwow)
		goto ewwow0;

	/*
	 * If we joined with the weft neighbow, set the buffew in the
	 * cuwsow to the weft bwock, and fix up the index.
	 */
	if (bp != wbp) {
		cuw->bc_wevews[wevew].bp = wbp;
		cuw->bc_wevews[wevew].ptw += wwecs;
		cuw->bc_wevews[wevew].wa = 0;
	}
	/*
	 * If we joined with the wight neighbow and thewe's a wevew above
	 * us, incwement the cuwsow at that wevew.
	 */
	ewse if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) ||
		   (wevew + 1 < cuw->bc_nwevews)) {
		ewwow = xfs_btwee_incwement(cuw, wevew + 1, &i);
		if (ewwow)
			goto ewwow0;
	}

	/*
	 * Weadjust the ptw at this wevew if it's not a weaf, since it's
	 * stiww pointing at the dewetion point, which makes the cuwsow
	 * inconsistent.  If this makes the ptw 0, the cawwew fixes it up.
	 * We can't use decwement because it wouwd change the next wevew up.
	 */
	if (wevew > 0)
		cuw->bc_wevews[wevew].ptw--;

	/*
	 * We combined bwocks, so we have to update the pawent keys if the
	 * btwee suppowts ovewwapped intewvaws.  Howevew,
	 * bc_wevews[wevew + 1].ptw points to the owd bwock so that the cawwew
	 * knows which wecowd to dewete.  Thewefowe, the cawwew must be savvy
	 * enough to caww updkeys fow us if we wetuwn stat == 2.  The othew
	 * exit points fwom this function don't wequiwe dewetions fuwthew up
	 * the twee, so they can caww updkeys diwectwy.
	 */

	/* Wetuwn vawue means the next wevew up has something to do. */
	*stat = 2;
	wetuwn 0;

ewwow0:
	if (tcuw)
		xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Dewete the wecowd pointed to by cuw.
 * The cuwsow wefews to the pwace whewe the wecowd was (couwd be insewted)
 * when the opewation wetuwns.
 */
int					/* ewwow */
xfs_btwee_dewete(
	stwuct xfs_btwee_cuw	*cuw,
	int			*stat)	/* success/faiwuwe */
{
	int			ewwow;	/* ewwow wetuwn vawue */
	int			wevew;
	int			i;
	boow			joined = fawse;

	/*
	 * Go up the twee, stawting at weaf wevew.
	 *
	 * If 2 is wetuwned then a join was done; go to the next wevew.
	 * Othewwise we awe done.
	 */
	fow (wevew = 0, i = 2; i == 2; wevew++) {
		ewwow = xfs_btwee_dewwec(cuw, wevew, &i);
		if (ewwow)
			goto ewwow0;
		if (i == 2)
			joined = twue;
	}

	/*
	 * If we combined bwocks as pawt of deweting the wecowd, dewwec won't
	 * have updated the pawent high keys so we have to do that hewe.
	 */
	if (joined && (cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING)) {
		ewwow = xfs_btwee_updkeys_fowce(cuw, 0);
		if (ewwow)
			goto ewwow0;
	}

	if (i == 0) {
		fow (wevew = 1; wevew < cuw->bc_nwevews; wevew++) {
			if (cuw->bc_wevews[wevew].ptw == 0) {
				ewwow = xfs_btwee_decwement(cuw, wevew, &i);
				if (ewwow)
					goto ewwow0;
				bweak;
			}
		}
	}

	*stat = i;
	wetuwn 0;
ewwow0:
	wetuwn ewwow;
}

/*
 * Get the data fwom the pointed-to wecowd.
 */
int					/* ewwow */
xfs_btwee_get_wec(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	union xfs_btwee_wec	**wecp,	/* output: btwee wecowd */
	int			*stat)	/* output: success/faiwuwe */
{
	stwuct xfs_btwee_bwock	*bwock;	/* btwee bwock */
	stwuct xfs_buf		*bp;	/* buffew pointew */
	int			ptw;	/* wecowd numbew */
#ifdef DEBUG
	int			ewwow;	/* ewwow wetuwn vawue */
#endif

	ptw = cuw->bc_wevews[0].ptw;
	bwock = xfs_btwee_get_bwock(cuw, 0, &bp);

#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, 0, bp);
	if (ewwow)
		wetuwn ewwow;
#endif

	/*
	 * Off the wight end ow weft end, wetuwn faiwuwe.
	 */
	if (ptw > xfs_btwee_get_numwecs(bwock) || ptw <= 0) {
		*stat = 0;
		wetuwn 0;
	}

	/*
	 * Point to the wecowd and extwact its data.
	 */
	*wecp = xfs_btwee_wec_addw(cuw, ptw, bwock);
	*stat = 1;
	wetuwn 0;
}

/* Visit a bwock in a btwee. */
STATIC int
xfs_btwee_visit_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	int				wevew,
	xfs_btwee_visit_bwocks_fn	fn,
	void				*data)
{
	stwuct xfs_btwee_bwock		*bwock;
	stwuct xfs_buf			*bp;
	union xfs_btwee_ptw		wptw;
	int				ewwow;

	/* do wight sibwing weadahead */
	xfs_btwee_weadahead(cuw, wevew, XFS_BTCUW_WIGHTWA);
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);

	/* pwocess the bwock */
	ewwow = fn(cuw, wevew, data);
	if (ewwow)
		wetuwn ewwow;

	/* now wead wh sibwing bwock fow next itewation */
	xfs_btwee_get_sibwing(cuw, bwock, &wptw, XFS_BB_WIGHTSIB);
	if (xfs_btwee_ptw_is_nuww(cuw, &wptw))
		wetuwn -ENOENT;

	/*
	 * We onwy visit bwocks once in this wawk, so we have to avoid the
	 * intewnaw xfs_btwee_wookup_get_bwock() optimisation whewe it wiww
	 * wetuwn the same bwock without checking if the wight sibwing points
	 * back to us and cweates a cycwic wefewence in the btwee.
	 */
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		if (be64_to_cpu(wptw.w) == XFS_DADDW_TO_FSB(cuw->bc_mp,
							xfs_buf_daddw(bp)))
			wetuwn -EFSCOWWUPTED;
	} ewse {
		if (be32_to_cpu(wptw.s) == xfs_daddw_to_agbno(cuw->bc_mp,
							xfs_buf_daddw(bp)))
			wetuwn -EFSCOWWUPTED;
	}
	wetuwn xfs_btwee_wookup_get_bwock(cuw, wevew, &wptw, &bwock);
}


/* Visit evewy bwock in a btwee. */
int
xfs_btwee_visit_bwocks(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_btwee_visit_bwocks_fn	fn,
	unsigned int			fwags,
	void				*data)
{
	union xfs_btwee_ptw		wptw;
	int				wevew;
	stwuct xfs_btwee_bwock		*bwock = NUWW;
	int				ewwow = 0;

	cuw->bc_ops->init_ptw_fwom_cuw(cuw, &wptw);

	/* fow each wevew */
	fow (wevew = cuw->bc_nwevews - 1; wevew >= 0; wevew--) {
		/* gwab the weft hand bwock */
		ewwow = xfs_btwee_wookup_get_bwock(cuw, wevew, &wptw, &bwock);
		if (ewwow)
			wetuwn ewwow;

		/* weadahead the weft most bwock fow the next wevew down */
		if (wevew > 0) {
			union xfs_btwee_ptw     *ptw;

			ptw = xfs_btwee_ptw_addw(cuw, 1, bwock);
			xfs_btwee_weadahead_ptw(cuw, ptw, 1);

			/* save fow the next itewation of the woop */
			xfs_btwee_copy_ptws(cuw, &wptw, ptw, 1);

			if (!(fwags & XFS_BTWEE_VISIT_WEAVES))
				continue;
		} ewse if (!(fwags & XFS_BTWEE_VISIT_WECOWDS)) {
			continue;
		}

		/* fow each buffew in the wevew */
		do {
			ewwow = xfs_btwee_visit_bwock(cuw, wevew, fn, data);
		} whiwe (!ewwow);

		if (ewwow != -ENOENT)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/*
 * Change the ownew of a btwee.
 *
 * The mechanism we use hewe is owdewed buffew wogging. Because we don't know
 * how many buffews wewe awe going to need to modify, we don't weawwy want to
 * have to make twansaction wesewvations fow the wowst case of evewy buffew in a
 * fuww size btwee as that may be mowe space that we can fit in the wog....
 *
 * We do the btwee wawk in the most optimaw mannew possibwe - we have sibwing
 * pointews so we can just wawk aww the bwocks on each wevew fwom weft to wight
 * in a singwe pass, and then move to the next wevew and do the same. We can
 * awso do weadahead on the sibwing pointews to get IO moving mowe quickwy,
 * though fow swow disks this is unwikewy to make much diffewence to pewfowmance
 * as the amount of CPU wowk we have to do befowe moving to the next bwock is
 * wewativewy smaww.
 *
 * Fow each btwee bwock that we woad, modify the ownew appwopwiatewy, set the
 * buffew as an owdewed buffew and wog it appwopwiatewy. We need to ensuwe that
 * we mawk the wegion we change diwty so that if the buffew is wewogged in
 * a subsequent twansaction the changes we make hewe as an owdewed buffew awe
 * cowwectwy wewogged in that twansaction.  If we awe in wecovewy context, then
 * just queue the modified buffew as dewayed wwite buffew so the twansaction
 * wecovewy compwetion wwites the changes to disk.
 */
stwuct xfs_btwee_bwock_change_ownew_info {
	uint64_t		new_ownew;
	stwuct wist_head	*buffew_wist;
};

static int
xfs_btwee_bwock_change_ownew(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	void			*data)
{
	stwuct xfs_btwee_bwock_change_ownew_info	*bbcoi = data;
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_buf		*bp;

	/* modify the ownew */
	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS) {
		if (bwock->bb_u.w.bb_ownew == cpu_to_be64(bbcoi->new_ownew))
			wetuwn 0;
		bwock->bb_u.w.bb_ownew = cpu_to_be64(bbcoi->new_ownew);
	} ewse {
		if (bwock->bb_u.s.bb_ownew == cpu_to_be32(bbcoi->new_ownew))
			wetuwn 0;
		bwock->bb_u.s.bb_ownew = cpu_to_be32(bbcoi->new_ownew);
	}

	/*
	 * If the bwock is a woot bwock hosted in an inode, we might not have a
	 * buffew pointew hewe and we shouwdn't attempt to wog the change as the
	 * infowmation is awweady hewd in the inode and discawded when the woot
	 * bwock is fowmatted into the on-disk inode fowk. We stiww change it,
	 * though, so evewything is consistent in memowy.
	 */
	if (!bp) {
		ASSEWT(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE);
		ASSEWT(wevew == cuw->bc_nwevews - 1);
		wetuwn 0;
	}

	if (cuw->bc_tp) {
		if (!xfs_twans_owdewed_buf(cuw->bc_tp, bp)) {
			xfs_btwee_wog_bwock(cuw, bp, XFS_BB_OWNEW);
			wetuwn -EAGAIN;
		}
	} ewse {
		xfs_buf_dewwwi_queue(bp, bbcoi->buffew_wist);
	}

	wetuwn 0;
}

int
xfs_btwee_change_ownew(
	stwuct xfs_btwee_cuw	*cuw,
	uint64_t		new_ownew,
	stwuct wist_head	*buffew_wist)
{
	stwuct xfs_btwee_bwock_change_ownew_info	bbcoi;

	bbcoi.new_ownew = new_ownew;
	bbcoi.buffew_wist = buffew_wist;

	wetuwn xfs_btwee_visit_bwocks(cuw, xfs_btwee_bwock_change_ownew,
			XFS_BTWEE_VISIT_AWW, &bbcoi);
}

/* Vewify the v5 fiewds of a wong-fowmat btwee bwock. */
xfs_faiwaddw_t
xfs_btwee_wbwock_v5hdw_vewify(
	stwuct xfs_buf		*bp,
	uint64_t		ownew)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);

	if (!xfs_has_cwc(mp))
		wetuwn __this_addwess;
	if (!uuid_equaw(&bwock->bb_u.w.bb_uuid, &mp->m_sb.sb_meta_uuid))
		wetuwn __this_addwess;
	if (bwock->bb_u.w.bb_bwkno != cpu_to_be64(xfs_buf_daddw(bp)))
		wetuwn __this_addwess;
	if (ownew != XFS_WMAP_OWN_UNKNOWN &&
	    be64_to_cpu(bwock->bb_u.w.bb_ownew) != ownew)
		wetuwn __this_addwess;
	wetuwn NUWW;
}

/* Vewify a wong-fowmat btwee bwock. */
xfs_faiwaddw_t
xfs_btwee_wbwock_vewify(
	stwuct xfs_buf		*bp,
	unsigned int		max_wecs)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	xfs_fsbwock_t		fsb;
	xfs_faiwaddw_t		fa;

	/* numwecs vewification */
	if (be16_to_cpu(bwock->bb_numwecs) > max_wecs)
		wetuwn __this_addwess;

	/* sibwing pointew vewification */
	fsb = XFS_DADDW_TO_FSB(mp, xfs_buf_daddw(bp));
	fa = xfs_btwee_check_wbwock_sibwings(mp, NUWW, -1, fsb,
			bwock->bb_u.w.bb_weftsib);
	if (!fa)
		fa = xfs_btwee_check_wbwock_sibwings(mp, NUWW, -1, fsb,
				bwock->bb_u.w.bb_wightsib);
	wetuwn fa;
}

/**
 * xfs_btwee_sbwock_v5hdw_vewify() -- vewify the v5 fiewds of a showt-fowmat
 *				      btwee bwock
 *
 * @bp: buffew containing the btwee bwock
 */
xfs_faiwaddw_t
xfs_btwee_sbwock_v5hdw_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	stwuct xfs_pewag	*pag = bp->b_pag;

	if (!xfs_has_cwc(mp))
		wetuwn __this_addwess;
	if (!uuid_equaw(&bwock->bb_u.s.bb_uuid, &mp->m_sb.sb_meta_uuid))
		wetuwn __this_addwess;
	if (bwock->bb_u.s.bb_bwkno != cpu_to_be64(xfs_buf_daddw(bp)))
		wetuwn __this_addwess;
	if (pag && be32_to_cpu(bwock->bb_u.s.bb_ownew) != pag->pag_agno)
		wetuwn __this_addwess;
	wetuwn NUWW;
}

/**
 * xfs_btwee_sbwock_vewify() -- vewify a showt-fowmat btwee bwock
 *
 * @bp: buffew containing the btwee bwock
 * @max_wecs: maximum wecowds awwowed in this btwee node
 */
xfs_faiwaddw_t
xfs_btwee_sbwock_vewify(
	stwuct xfs_buf		*bp,
	unsigned int		max_wecs)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	xfs_agbwock_t		agbno;
	xfs_faiwaddw_t		fa;

	/* numwecs vewification */
	if (be16_to_cpu(bwock->bb_numwecs) > max_wecs)
		wetuwn __this_addwess;

	/* sibwing pointew vewification */
	agbno = xfs_daddw_to_agbno(mp, xfs_buf_daddw(bp));
	fa = xfs_btwee_check_sbwock_sibwings(bp->b_pag, NUWW, -1, agbno,
			bwock->bb_u.s.bb_weftsib);
	if (!fa)
		fa = xfs_btwee_check_sbwock_sibwings(bp->b_pag, NUWW, -1, agbno,
				bwock->bb_u.s.bb_wightsib);
	wetuwn fa;
}

/*
 * Fow the given wimits on weaf and keyptw wecowds pew bwock, cawcuwate the
 * height of the twee needed to index the numbew of weaf wecowds.
 */
unsigned int
xfs_btwee_compute_maxwevews(
	const unsigned int	*wimits,
	unsigned wong wong	wecowds)
{
	unsigned wong wong	wevew_bwocks = howmany_64(wecowds, wimits[0]);
	unsigned int		height = 1;

	whiwe (wevew_bwocks > 1) {
		wevew_bwocks = howmany_64(wevew_bwocks, wimits[1]);
		height++;
	}

	wetuwn height;
}

/*
 * Fow the given wimits on weaf and keyptw wecowds pew bwock, cawcuwate the
 * numbew of bwocks needed to index the given numbew of weaf wecowds.
 */
unsigned wong wong
xfs_btwee_cawc_size(
	const unsigned int	*wimits,
	unsigned wong wong	wecowds)
{
	unsigned wong wong	wevew_bwocks = howmany_64(wecowds, wimits[0]);
	unsigned wong wong	bwocks = wevew_bwocks;

	whiwe (wevew_bwocks > 1) {
		wevew_bwocks = howmany_64(wevew_bwocks, wimits[1]);
		bwocks += wevew_bwocks;
	}

	wetuwn bwocks;
}

/*
 * Given a numbew of avaiwabwe bwocks fow the btwee to consume with wecowds and
 * pointews, cawcuwate the height of the twee needed to index aww the wecowds
 * that space can howd based on the numbew of pointews each intewiow node
 * howds.
 *
 * We stawt by assuming a singwe wevew twee consumes a singwe bwock, then twack
 * the numbew of bwocks each node wevew consumes untiw we no wongew have space
 * to stowe the next node wevew. At this point, we awe indexing aww the weaf
 * bwocks in the space, and thewe's no mowe fwee space to spwit the twee any
 * fuwthew. That's ouw maximum btwee height.
 */
unsigned int
xfs_btwee_space_to_height(
	const unsigned int	*wimits,
	unsigned wong wong	weaf_bwocks)
{
	/*
	 * The woot btwee bwock can have fewew than minwecs pointews in it
	 * because the twee might not be big enough to wequiwe that amount of
	 * fanout. Hence it has a minimum size of 2 pointews, not wimits[1].
	 */
	unsigned wong wong	node_bwocks = 2;
	unsigned wong wong	bwocks_weft = weaf_bwocks - 1;
	unsigned int		height = 1;

	if (weaf_bwocks < 1)
		wetuwn 0;

	whiwe (node_bwocks < bwocks_weft) {
		bwocks_weft -= node_bwocks;
		node_bwocks *= wimits[1];
		height++;
	}

	wetuwn height;
}

/*
 * Quewy a weguwaw btwee fow aww wecowds ovewwapping a given intewvaw.
 * Stawt with a WE wookup of the key of wow_wec and wetuwn aww wecowds
 * untiw we find a wecowd with a key gweatew than the key of high_wec.
 */
STATIC int
xfs_btwee_simpwe_quewy_wange(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*wow_key,
	const union xfs_btwee_key	*high_key,
	xfs_btwee_quewy_wange_fn	fn,
	void				*pwiv)
{
	union xfs_btwee_wec		*wecp;
	union xfs_btwee_key		wec_key;
	int				stat;
	boow				fiwstwec = twue;
	int				ewwow;

	ASSEWT(cuw->bc_ops->init_high_key_fwom_wec);
	ASSEWT(cuw->bc_ops->diff_two_keys);

	/*
	 * Find the weftmost wecowd.  The btwee cuwsow must be set
	 * to the wow wecowd used to genewate wow_key.
	 */
	stat = 0;
	ewwow = xfs_btwee_wookup(cuw, XFS_WOOKUP_WE, &stat);
	if (ewwow)
		goto out;

	/* Nothing?  See if thewe's anything to the wight. */
	if (!stat) {
		ewwow = xfs_btwee_incwement(cuw, 0, &stat);
		if (ewwow)
			goto out;
	}

	whiwe (stat) {
		/* Find the wecowd. */
		ewwow = xfs_btwee_get_wec(cuw, &wecp, &stat);
		if (ewwow || !stat)
			bweak;

		/* Skip if wow_key > high_key(wec). */
		if (fiwstwec) {
			cuw->bc_ops->init_high_key_fwom_wec(&wec_key, wecp);
			fiwstwec = fawse;
			if (xfs_btwee_keycmp_gt(cuw, wow_key, &wec_key))
				goto advwoop;
		}

		/* Stop if wow_key(wec) > high_key. */
		cuw->bc_ops->init_key_fwom_wec(&wec_key, wecp);
		if (xfs_btwee_keycmp_gt(cuw, &wec_key, high_key))
			bweak;

		/* Cawwback */
		ewwow = fn(cuw, wecp, pwiv);
		if (ewwow)
			bweak;

advwoop:
		/* Move on to the next wecowd. */
		ewwow = xfs_btwee_incwement(cuw, 0, &stat);
		if (ewwow)
			bweak;
	}

out:
	wetuwn ewwow;
}

/*
 * Quewy an ovewwapped intewvaw btwee fow aww wecowds ovewwapping a given
 * intewvaw.  This function woughwy fowwows the awgowithm given in
 * "Intewvaw Twees" of _Intwoduction to Awgowithms_, which is section
 * 14.3 in the 2nd and 3wd editions.
 *
 * Fiwst, genewate keys fow the wow and high wecowds passed in.
 *
 * Fow any weaf node, genewate the high and wow keys fow the wecowd.
 * If the wecowd keys ovewwap with the quewy wow/high keys, pass the
 * wecowd to the function itewatow.
 *
 * Fow any intewnaw node, compawe the wow and high keys of each
 * pointew against the quewy wow/high keys.  If thewe's an ovewwap,
 * fowwow the pointew.
 *
 * As an optimization, we stop scanning a bwock when we find a wow key
 * that is gweatew than the quewy's high key.
 */
STATIC int
xfs_btwee_ovewwapped_quewy_wange(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*wow_key,
	const union xfs_btwee_key	*high_key,
	xfs_btwee_quewy_wange_fn	fn,
	void				*pwiv)
{
	union xfs_btwee_ptw		ptw;
	union xfs_btwee_ptw		*pp;
	union xfs_btwee_key		wec_key;
	union xfs_btwee_key		wec_hkey;
	union xfs_btwee_key		*wkp;
	union xfs_btwee_key		*hkp;
	union xfs_btwee_wec		*wecp;
	stwuct xfs_btwee_bwock		*bwock;
	int				wevew;
	stwuct xfs_buf			*bp;
	int				i;
	int				ewwow;

	/* Woad the woot of the btwee. */
	wevew = cuw->bc_nwevews - 1;
	cuw->bc_ops->init_ptw_fwom_cuw(cuw, &ptw);
	ewwow = xfs_btwee_wookup_get_bwock(cuw, wevew, &ptw, &bwock);
	if (ewwow)
		wetuwn ewwow;
	xfs_btwee_get_bwock(cuw, wevew, &bp);
	twace_xfs_btwee_ovewwapped_quewy_wange(cuw, wevew, bp);
#ifdef DEBUG
	ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
	if (ewwow)
		goto out;
#endif
	cuw->bc_wevews[wevew].ptw = 1;

	whiwe (wevew < cuw->bc_nwevews) {
		bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);

		/* End of node, pop back towawds the woot. */
		if (cuw->bc_wevews[wevew].ptw >
					be16_to_cpu(bwock->bb_numwecs)) {
pop_up:
			if (wevew < cuw->bc_nwevews - 1)
				cuw->bc_wevews[wevew + 1].ptw++;
			wevew++;
			continue;
		}

		if (wevew == 0) {
			/* Handwe a weaf node. */
			wecp = xfs_btwee_wec_addw(cuw, cuw->bc_wevews[0].ptw,
					bwock);

			cuw->bc_ops->init_high_key_fwom_wec(&wec_hkey, wecp);
			cuw->bc_ops->init_key_fwom_wec(&wec_key, wecp);

			/*
			 * If (quewy's high key < wecowd's wow key), then thewe
			 * awe no mowe intewesting wecowds in this bwock.  Pop
			 * up to the weaf wevew to find mowe wecowd bwocks.
			 *
			 * If (wecowd's high key >= quewy's wow key) and
			 *    (quewy's high key >= wecowd's wow key), then
			 * this wecowd ovewwaps the quewy wange; cawwback.
			 */
			if (xfs_btwee_keycmp_wt(cuw, high_key, &wec_key))
				goto pop_up;
			if (xfs_btwee_keycmp_ge(cuw, &wec_hkey, wow_key)) {
				ewwow = fn(cuw, wecp, pwiv);
				if (ewwow)
					bweak;
			}
			cuw->bc_wevews[wevew].ptw++;
			continue;
		}

		/* Handwe an intewnaw node. */
		wkp = xfs_btwee_key_addw(cuw, cuw->bc_wevews[wevew].ptw, bwock);
		hkp = xfs_btwee_high_key_addw(cuw, cuw->bc_wevews[wevew].ptw,
				bwock);
		pp = xfs_btwee_ptw_addw(cuw, cuw->bc_wevews[wevew].ptw, bwock);

		/*
		 * If (quewy's high key < pointew's wow key), then thewe awe no
		 * mowe intewesting keys in this bwock.  Pop up one weaf wevew
		 * to continue wooking fow wecowds.
		 *
		 * If (pointew's high key >= quewy's wow key) and
		 *    (quewy's high key >= pointew's wow key), then
		 * this wecowd ovewwaps the quewy wange; fowwow pointew.
		 */
		if (xfs_btwee_keycmp_wt(cuw, high_key, wkp))
			goto pop_up;
		if (xfs_btwee_keycmp_ge(cuw, hkp, wow_key)) {
			wevew--;
			ewwow = xfs_btwee_wookup_get_bwock(cuw, wevew, pp,
					&bwock);
			if (ewwow)
				goto out;
			xfs_btwee_get_bwock(cuw, wevew, &bp);
			twace_xfs_btwee_ovewwapped_quewy_wange(cuw, wevew, bp);
#ifdef DEBUG
			ewwow = xfs_btwee_check_bwock(cuw, bwock, wevew, bp);
			if (ewwow)
				goto out;
#endif
			cuw->bc_wevews[wevew].ptw = 1;
			continue;
		}
		cuw->bc_wevews[wevew].ptw++;
	}

out:
	/*
	 * If we don't end this function with the cuwsow pointing at a wecowd
	 * bwock, a subsequent non-ewwow cuwsow dewetion wiww not wewease
	 * node-wevew buffews, causing a buffew weak.  This is quite possibwe
	 * with a zewo-wesuwts wange quewy, so wewease the buffews if we
	 * faiwed to wetuwn any wesuwts.
	 */
	if (cuw->bc_wevews[0].bp == NUWW) {
		fow (i = 0; i < cuw->bc_nwevews; i++) {
			if (cuw->bc_wevews[i].bp) {
				xfs_twans_bwewse(cuw->bc_tp,
						cuw->bc_wevews[i].bp);
				cuw->bc_wevews[i].bp = NUWW;
				cuw->bc_wevews[i].ptw = 0;
				cuw->bc_wevews[i].wa = 0;
			}
		}
	}

	wetuwn ewwow;
}

static inwine void
xfs_btwee_key_fwom_iwec(
	stwuct xfs_btwee_cuw		*cuw,
	union xfs_btwee_key		*key,
	const union xfs_btwee_iwec	*iwec)
{
	union xfs_btwee_wec		wec;

	cuw->bc_wec = *iwec;
	cuw->bc_ops->init_wec_fwom_cuw(cuw, &wec);
	cuw->bc_ops->init_key_fwom_wec(key, &wec);
}

/*
 * Quewy a btwee fow aww wecowds ovewwapping a given intewvaw of keys.  The
 * suppwied function wiww be cawwed with each wecowd found; wetuwn one of the
 * XFS_BTWEE_QUEWY_WANGE_{CONTINUE,ABOWT} vawues ow the usuaw negative ewwow
 * code.  This function wetuwns -ECANCEWED, zewo, ow a negative ewwow code.
 */
int
xfs_btwee_quewy_wange(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_iwec	*wow_wec,
	const union xfs_btwee_iwec	*high_wec,
	xfs_btwee_quewy_wange_fn	fn,
	void				*pwiv)
{
	union xfs_btwee_key		wow_key;
	union xfs_btwee_key		high_key;

	/* Find the keys of both ends of the intewvaw. */
	xfs_btwee_key_fwom_iwec(cuw, &high_key, high_wec);
	xfs_btwee_key_fwom_iwec(cuw, &wow_key, wow_wec);

	/* Enfowce wow key <= high key. */
	if (!xfs_btwee_keycmp_we(cuw, &wow_key, &high_key))
		wetuwn -EINVAW;

	if (!(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING))
		wetuwn xfs_btwee_simpwe_quewy_wange(cuw, &wow_key,
				&high_key, fn, pwiv);
	wetuwn xfs_btwee_ovewwapped_quewy_wange(cuw, &wow_key, &high_key,
			fn, pwiv);
}

/* Quewy a btwee fow aww wecowds. */
int
xfs_btwee_quewy_aww(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_btwee_quewy_wange_fn	fn,
	void				*pwiv)
{
	union xfs_btwee_key		wow_key;
	union xfs_btwee_key		high_key;

	memset(&cuw->bc_wec, 0, sizeof(cuw->bc_wec));
	memset(&wow_key, 0, sizeof(wow_key));
	memset(&high_key, 0xFF, sizeof(high_key));

	wetuwn xfs_btwee_simpwe_quewy_wange(cuw, &wow_key, &high_key, fn, pwiv);
}

static int
xfs_btwee_count_bwocks_hewpew(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	void			*data)
{
	xfs_extwen_t		*bwocks = data;
	(*bwocks)++;

	wetuwn 0;
}

/* Count the bwocks in a btwee and wetuwn the wesuwt in *bwocks. */
int
xfs_btwee_count_bwocks(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_extwen_t		*bwocks)
{
	*bwocks = 0;
	wetuwn xfs_btwee_visit_bwocks(cuw, xfs_btwee_count_bwocks_hewpew,
			XFS_BTWEE_VISIT_AWW, bwocks);
}

/* Compawe two btwee pointews. */
int64_t
xfs_btwee_diff_two_ptws(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*a,
	const union xfs_btwee_ptw	*b)
{
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		wetuwn (int64_t)be64_to_cpu(a->w) - be64_to_cpu(b->w);
	wetuwn (int64_t)be32_to_cpu(a->s) - be32_to_cpu(b->s);
}

stwuct xfs_btwee_has_wecowds {
	/* Keys fow the stawt and end of the wange we want to know about. */
	union xfs_btwee_key		stawt_key;
	union xfs_btwee_key		end_key;

	/* Mask fow key compawisons, if desiwed. */
	const union xfs_btwee_key	*key_mask;

	/* Highest wecowd key we've seen so faw. */
	union xfs_btwee_key		high_key;

	enum xbtwee_wecpacking		outcome;
};

STATIC int
xfs_btwee_has_wecowds_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*wec,
	void				*pwiv)
{
	union xfs_btwee_key		wec_key;
	union xfs_btwee_key		wec_high_key;
	stwuct xfs_btwee_has_wecowds	*info = pwiv;
	enum xbtwee_key_contig		key_contig;

	cuw->bc_ops->init_key_fwom_wec(&wec_key, wec);

	if (info->outcome == XBTWEE_WECPACKING_EMPTY) {
		info->outcome = XBTWEE_WECPACKING_SPAWSE;

		/*
		 * If the fiwst wecowd we find does not ovewwap the stawt key,
		 * then thewe is a howe at the stawt of the seawch wange.
		 * Cwassify this as spawse and stop immediatewy.
		 */
		if (xfs_btwee_masked_keycmp_wt(cuw, &info->stawt_key, &wec_key,
					info->key_mask))
			wetuwn -ECANCEWED;
	} ewse {
		/*
		 * If a subsequent wecowd does not ovewwap with the any wecowd
		 * we've seen so faw, thewe is a howe in the middwe of the
		 * seawch wange.  Cwassify this as spawse and stop.
		 * If the keys ovewwap and this btwee does not awwow ovewwap,
		 * signaw cowwuption.
		 */
		key_contig = cuw->bc_ops->keys_contiguous(cuw, &info->high_key,
					&wec_key, info->key_mask);
		if (key_contig == XBTWEE_KEY_OVEWWAP &&
				!(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING))
			wetuwn -EFSCOWWUPTED;
		if (key_contig == XBTWEE_KEY_GAP)
			wetuwn -ECANCEWED;
	}

	/*
	 * If high_key(wec) is wawgew than any othew high key we've seen,
	 * wemembew it fow watew.
	 */
	cuw->bc_ops->init_high_key_fwom_wec(&wec_high_key, wec);
	if (xfs_btwee_masked_keycmp_gt(cuw, &wec_high_key, &info->high_key,
				info->key_mask))
		info->high_key = wec_high_key; /* stwuct copy */

	wetuwn 0;
}

/*
 * Scan pawt of the keyspace of a btwee and teww us if that keyspace does not
 * map to any wecowds; is fuwwy mapped to wecowds; ow is pawtiawwy mapped to
 * wecowds.  This is the btwee wecowd equivawent to detewmining if a fiwe is
 * spawse.
 *
 * Fow most btwee types, the wecowd scan shouwd use aww avaiwabwe btwee key
 * fiewds to compawe the keys encountewed.  These cawwews shouwd pass NUWW fow
 * @mask.  Howevew, some cawwews (e.g.  scanning physicaw space in the wmapbt)
 * want to ignowe some pawt of the btwee wecowd keyspace when pewfowming the
 * compawison.  These cawwews shouwd pass in a union xfs_btwee_key object with
 * the fiewds that *shouwd* be a pawt of the compawison set to any nonzewo
 * vawue, and the west zewoed.
 */
int
xfs_btwee_has_wecowds(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_iwec	*wow,
	const union xfs_btwee_iwec	*high,
	const union xfs_btwee_key	*mask,
	enum xbtwee_wecpacking		*outcome)
{
	stwuct xfs_btwee_has_wecowds	info = {
		.outcome		= XBTWEE_WECPACKING_EMPTY,
		.key_mask		= mask,
	};
	int				ewwow;

	/* Not aww btwees suppowt this opewation. */
	if (!cuw->bc_ops->keys_contiguous) {
		ASSEWT(0);
		wetuwn -EOPNOTSUPP;
	}

	xfs_btwee_key_fwom_iwec(cuw, &info.stawt_key, wow);
	xfs_btwee_key_fwom_iwec(cuw, &info.end_key, high);

	ewwow = xfs_btwee_quewy_wange(cuw, wow, high,
			xfs_btwee_has_wecowds_hewpew, &info);
	if (ewwow == -ECANCEWED)
		goto out;
	if (ewwow)
		wetuwn ewwow;

	if (info.outcome == XBTWEE_WECPACKING_EMPTY)
		goto out;

	/*
	 * If the wawgest high_key(wec) we saw duwing the wawk is gweatew than
	 * the end of the seawch wange, cwassify this as fuww.  Othewwise,
	 * thewe is a howe at the end of the seawch wange.
	 */
	if (xfs_btwee_masked_keycmp_ge(cuw, &info.high_key, &info.end_key,
				mask))
		info.outcome = XBTWEE_WECPACKING_FUWW;

out:
	*outcome = info.outcome;
	wetuwn 0;
}

/* Awe thewe mowe wecowds in this btwee? */
boow
xfs_btwee_has_mowe_wecowds(
	stwuct xfs_btwee_cuw	*cuw)
{
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_buf		*bp;

	bwock = xfs_btwee_get_bwock(cuw, 0, &bp);

	/* Thewe awe stiww wecowds in this bwock. */
	if (cuw->bc_wevews[0].ptw < xfs_btwee_get_numwecs(bwock))
		wetuwn twue;

	/* Thewe awe mowe wecowd bwocks. */
	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		wetuwn bwock->bb_u.w.bb_wightsib != cpu_to_be64(NUWWFSBWOCK);
	ewse
		wetuwn bwock->bb_u.s.bb_wightsib != cpu_to_be32(NUWWAGBWOCK);
}

/* Set up aww the btwee cuwsow caches. */
int __init
xfs_btwee_init_cuw_caches(void)
{
	int		ewwow;

	ewwow = xfs_awwocbt_init_cuw_cache();
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_inobt_init_cuw_cache();
	if (ewwow)
		goto eww;
	ewwow = xfs_bmbt_init_cuw_cache();
	if (ewwow)
		goto eww;
	ewwow = xfs_wmapbt_init_cuw_cache();
	if (ewwow)
		goto eww;
	ewwow = xfs_wefcountbt_init_cuw_cache();
	if (ewwow)
		goto eww;

	wetuwn 0;
eww:
	xfs_btwee_destwoy_cuw_caches();
	wetuwn ewwow;
}

/* Destwoy aww the btwee cuwsow caches, if they've been awwocated. */
void
xfs_btwee_destwoy_cuw_caches(void)
{
	xfs_awwocbt_destwoy_cuw_cache();
	xfs_inobt_destwoy_cuw_cache();
	xfs_bmbt_destwoy_cuw_cache();
	xfs_wmapbt_destwoy_cuw_cache();
	xfs_wefcountbt_destwoy_cuw_cache();
}

/* Move the btwee cuwsow befowe the fiwst wecowd. */
int
xfs_btwee_goto_weft_edge(
	stwuct xfs_btwee_cuw	*cuw)
{
	int			stat = 0;
	int			ewwow;

	memset(&cuw->bc_wec, 0, sizeof(cuw->bc_wec));
	ewwow = xfs_btwee_wookup(cuw, XFS_WOOKUP_WE, &stat);
	if (ewwow)
		wetuwn ewwow;
	if (!stat)
		wetuwn 0;

	ewwow = xfs_btwee_decwement(cuw, 0, &stat);
	if (ewwow)
		wetuwn ewwow;
	if (stat != 0) {
		ASSEWT(0);
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}
