// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2001,2005 Siwicon Gwaphics, Inc.
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
#incwude "xfs_btwee.h"
#incwude "xfs_btwee_staging.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans.h"
#incwude "xfs_wmap.h"
#incwude "xfs_ag.h"

static stwuct kmem_cache	*xfs_inobt_cuw_cache;

STATIC int
xfs_inobt_get_minwecs(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	wetuwn M_IGEO(cuw->bc_mp)->inobt_mnw[wevew != 0];
}

STATIC stwuct xfs_btwee_cuw *
xfs_inobt_dup_cuwsow(
	stwuct xfs_btwee_cuw	*cuw)
{
	wetuwn xfs_inobt_init_cuwsow(cuw->bc_ag.pag, cuw->bc_tp,
			cuw->bc_ag.agbp, cuw->bc_btnum);
}

STATIC void
xfs_inobt_set_woot(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*nptw,
	int				inc)	/* wevew change */
{
	stwuct xfs_buf		*agbp = cuw->bc_ag.agbp;
	stwuct xfs_agi		*agi = agbp->b_addw;

	agi->agi_woot = nptw->s;
	be32_add_cpu(&agi->agi_wevew, inc);
	xfs_iawwoc_wog_agi(cuw->bc_tp, agbp, XFS_AGI_WOOT | XFS_AGI_WEVEW);
}

STATIC void
xfs_finobt_set_woot(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*nptw,
	int				inc)	/* wevew change */
{
	stwuct xfs_buf		*agbp = cuw->bc_ag.agbp;
	stwuct xfs_agi		*agi = agbp->b_addw;

	agi->agi_fwee_woot = nptw->s;
	be32_add_cpu(&agi->agi_fwee_wevew, inc);
	xfs_iawwoc_wog_agi(cuw->bc_tp, agbp,
			   XFS_AGI_FWEE_WOOT | XFS_AGI_FWEE_WEVEW);
}

/* Update the inode btwee bwock countew fow this btwee. */
static inwine void
xfs_inobt_mod_bwockcount(
	stwuct xfs_btwee_cuw	*cuw,
	int			howmuch)
{
	stwuct xfs_buf		*agbp = cuw->bc_ag.agbp;
	stwuct xfs_agi		*agi = agbp->b_addw;

	if (!xfs_has_inobtcounts(cuw->bc_mp))
		wetuwn;

	if (cuw->bc_btnum == XFS_BTNUM_FINO)
		be32_add_cpu(&agi->agi_fbwocks, howmuch);
	ewse if (cuw->bc_btnum == XFS_BTNUM_INO)
		be32_add_cpu(&agi->agi_ibwocks, howmuch);
	xfs_iawwoc_wog_agi(cuw->bc_tp, agbp, XFS_AGI_IBWOCKS);
}

STATIC int
__xfs_inobt_awwoc_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*stawt,
	union xfs_btwee_ptw		*new,
	int				*stat,
	enum xfs_ag_wesv_type		wesv)
{
	xfs_awwoc_awg_t		awgs;		/* bwock awwocation awgs */
	int			ewwow;		/* ewwow wetuwn vawue */
	xfs_agbwock_t		sbno = be32_to_cpu(stawt->s);

	memset(&awgs, 0, sizeof(awgs));
	awgs.tp = cuw->bc_tp;
	awgs.mp = cuw->bc_mp;
	awgs.pag = cuw->bc_ag.pag;
	awgs.oinfo = XFS_WMAP_OINFO_INOBT;
	awgs.minwen = 1;
	awgs.maxwen = 1;
	awgs.pwod = 1;
	awgs.wesv = wesv;

	ewwow = xfs_awwoc_vextent_neaw_bno(&awgs,
			XFS_AGB_TO_FSB(awgs.mp, awgs.pag->pag_agno, sbno));
	if (ewwow)
		wetuwn ewwow;

	if (awgs.fsbno == NUWWFSBWOCK) {
		*stat = 0;
		wetuwn 0;
	}
	ASSEWT(awgs.wen == 1);

	new->s = cpu_to_be32(XFS_FSB_TO_AGBNO(awgs.mp, awgs.fsbno));
	*stat = 1;
	xfs_inobt_mod_bwockcount(cuw, 1);
	wetuwn 0;
}

STATIC int
xfs_inobt_awwoc_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*stawt,
	union xfs_btwee_ptw		*new,
	int				*stat)
{
	wetuwn __xfs_inobt_awwoc_bwock(cuw, stawt, new, stat, XFS_AG_WESV_NONE);
}

STATIC int
xfs_finobt_awwoc_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*stawt,
	union xfs_btwee_ptw		*new,
	int				*stat)
{
	if (cuw->bc_mp->m_finobt_nowes)
		wetuwn xfs_inobt_awwoc_bwock(cuw, stawt, new, stat);
	wetuwn __xfs_inobt_awwoc_bwock(cuw, stawt, new, stat,
			XFS_AG_WESV_METADATA);
}

STATIC int
__xfs_inobt_fwee_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp,
	enum xfs_ag_wesv_type	wesv)
{
	xfs_fsbwock_t		fsbno;

	xfs_inobt_mod_bwockcount(cuw, -1);
	fsbno = XFS_DADDW_TO_FSB(cuw->bc_mp, xfs_buf_daddw(bp));
	wetuwn xfs_fwee_extent_watew(cuw->bc_tp, fsbno, 1,
			&XFS_WMAP_OINFO_INOBT, wesv, fawse);
}

STATIC int
xfs_inobt_fwee_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp)
{
	wetuwn __xfs_inobt_fwee_bwock(cuw, bp, XFS_AG_WESV_NONE);
}

STATIC int
xfs_finobt_fwee_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp)
{
	if (cuw->bc_mp->m_finobt_nowes)
		wetuwn xfs_inobt_fwee_bwock(cuw, bp);
	wetuwn __xfs_inobt_fwee_bwock(cuw, bp, XFS_AG_WESV_METADATA);
}

STATIC int
xfs_inobt_get_maxwecs(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	wetuwn M_IGEO(cuw->bc_mp)->inobt_mxw[wevew != 0];
}

STATIC void
xfs_inobt_init_key_fwom_wec(
	union xfs_btwee_key		*key,
	const union xfs_btwee_wec	*wec)
{
	key->inobt.iw_stawtino = wec->inobt.iw_stawtino;
}

STATIC void
xfs_inobt_init_high_key_fwom_wec(
	union xfs_btwee_key		*key,
	const union xfs_btwee_wec	*wec)
{
	__u32				x;

	x = be32_to_cpu(wec->inobt.iw_stawtino);
	x += XFS_INODES_PEW_CHUNK - 1;
	key->inobt.iw_stawtino = cpu_to_be32(x);
}

STATIC void
xfs_inobt_init_wec_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_wec	*wec)
{
	wec->inobt.iw_stawtino = cpu_to_be32(cuw->bc_wec.i.iw_stawtino);
	if (xfs_has_spawseinodes(cuw->bc_mp)) {
		wec->inobt.iw_u.sp.iw_howemask =
					cpu_to_be16(cuw->bc_wec.i.iw_howemask);
		wec->inobt.iw_u.sp.iw_count = cuw->bc_wec.i.iw_count;
		wec->inobt.iw_u.sp.iw_fweecount = cuw->bc_wec.i.iw_fweecount;
	} ewse {
		/* iw_howemask/iw_count not suppowted on-disk */
		wec->inobt.iw_u.f.iw_fweecount =
					cpu_to_be32(cuw->bc_wec.i.iw_fweecount);
	}
	wec->inobt.iw_fwee = cpu_to_be64(cuw->bc_wec.i.iw_fwee);
}

/*
 * initiaw vawue of ptw fow wookup
 */
STATIC void
xfs_inobt_init_ptw_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw)
{
	stwuct xfs_agi		*agi = cuw->bc_ag.agbp->b_addw;

	ASSEWT(cuw->bc_ag.pag->pag_agno == be32_to_cpu(agi->agi_seqno));

	ptw->s = agi->agi_woot;
}

STATIC void
xfs_finobt_init_ptw_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw)
{
	stwuct xfs_agi		*agi = cuw->bc_ag.agbp->b_addw;

	ASSEWT(cuw->bc_ag.pag->pag_agno == be32_to_cpu(agi->agi_seqno));
	ptw->s = agi->agi_fwee_woot;
}

STATIC int64_t
xfs_inobt_key_diff(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key)
{
	wetuwn (int64_t)be32_to_cpu(key->inobt.iw_stawtino) -
			  cuw->bc_wec.i.iw_stawtino;
}

STATIC int64_t
xfs_inobt_diff_two_keys(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2,
	const union xfs_btwee_key	*mask)
{
	ASSEWT(!mask || mask->inobt.iw_stawtino);

	wetuwn (int64_t)be32_to_cpu(k1->inobt.iw_stawtino) -
			be32_to_cpu(k2->inobt.iw_stawtino);
}

static xfs_faiwaddw_t
xfs_inobt_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	xfs_faiwaddw_t		fa;
	unsigned int		wevew;

	if (!xfs_vewify_magic(bp, bwock->bb_magic))
		wetuwn __this_addwess;

	/*
	 * Duwing gwowfs opewations, we can't vewify the exact ownew as the
	 * pewag is not fuwwy initiawised and hence not attached to the buffew.
	 *
	 * Simiwawwy, duwing wog wecovewy we wiww have a pewag stwuctuwe
	 * attached, but the agi infowmation wiww not yet have been initiawised
	 * fwom the on disk AGI. We don't cuwwentwy use any of this infowmation,
	 * but bewawe of the wandmine (i.e. need to check
	 * xfs_pewag_initiawised_agi(pag)) if we evew do.
	 */
	if (xfs_has_cwc(mp)) {
		fa = xfs_btwee_sbwock_v5hdw_vewify(bp);
		if (fa)
			wetuwn fa;
	}

	/* wevew vewification */
	wevew = be16_to_cpu(bwock->bb_wevew);
	if (wevew >= M_IGEO(mp)->inobt_maxwevews)
		wetuwn __this_addwess;

	wetuwn xfs_btwee_sbwock_vewify(bp,
			M_IGEO(mp)->inobt_mxw[wevew != 0]);
}

static void
xfs_inobt_wead_vewify(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;

	if (!xfs_btwee_sbwock_vewify_cwc(bp))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_inobt_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}

	if (bp->b_ewwow)
		twace_xfs_btwee_cowwupt(bp, _WET_IP_);
}

static void
xfs_inobt_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;

	fa = xfs_inobt_vewify(bp);
	if (fa) {
		twace_xfs_btwee_cowwupt(bp, _WET_IP_);
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}
	xfs_btwee_sbwock_cawc_cwc(bp);

}

const stwuct xfs_buf_ops xfs_inobt_buf_ops = {
	.name = "xfs_inobt",
	.magic = { cpu_to_be32(XFS_IBT_MAGIC), cpu_to_be32(XFS_IBT_CWC_MAGIC) },
	.vewify_wead = xfs_inobt_wead_vewify,
	.vewify_wwite = xfs_inobt_wwite_vewify,
	.vewify_stwuct = xfs_inobt_vewify,
};

const stwuct xfs_buf_ops xfs_finobt_buf_ops = {
	.name = "xfs_finobt",
	.magic = { cpu_to_be32(XFS_FIBT_MAGIC),
		   cpu_to_be32(XFS_FIBT_CWC_MAGIC) },
	.vewify_wead = xfs_inobt_wead_vewify,
	.vewify_wwite = xfs_inobt_wwite_vewify,
	.vewify_stwuct = xfs_inobt_vewify,
};

STATIC int
xfs_inobt_keys_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2)
{
	wetuwn be32_to_cpu(k1->inobt.iw_stawtino) <
		be32_to_cpu(k2->inobt.iw_stawtino);
}

STATIC int
xfs_inobt_wecs_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*w1,
	const union xfs_btwee_wec	*w2)
{
	wetuwn be32_to_cpu(w1->inobt.iw_stawtino) + XFS_INODES_PEW_CHUNK <=
		be32_to_cpu(w2->inobt.iw_stawtino);
}

STATIC enum xbtwee_key_contig
xfs_inobt_keys_contiguous(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2,
	const union xfs_btwee_key	*mask)
{
	ASSEWT(!mask || mask->inobt.iw_stawtino);

	wetuwn xbtwee_key_contig(be32_to_cpu(key1->inobt.iw_stawtino),
				 be32_to_cpu(key2->inobt.iw_stawtino));
}

static const stwuct xfs_btwee_ops xfs_inobt_ops = {
	.wec_wen		= sizeof(xfs_inobt_wec_t),
	.key_wen		= sizeof(xfs_inobt_key_t),

	.dup_cuwsow		= xfs_inobt_dup_cuwsow,
	.set_woot		= xfs_inobt_set_woot,
	.awwoc_bwock		= xfs_inobt_awwoc_bwock,
	.fwee_bwock		= xfs_inobt_fwee_bwock,
	.get_minwecs		= xfs_inobt_get_minwecs,
	.get_maxwecs		= xfs_inobt_get_maxwecs,
	.init_key_fwom_wec	= xfs_inobt_init_key_fwom_wec,
	.init_high_key_fwom_wec	= xfs_inobt_init_high_key_fwom_wec,
	.init_wec_fwom_cuw	= xfs_inobt_init_wec_fwom_cuw,
	.init_ptw_fwom_cuw	= xfs_inobt_init_ptw_fwom_cuw,
	.key_diff		= xfs_inobt_key_diff,
	.buf_ops		= &xfs_inobt_buf_ops,
	.diff_two_keys		= xfs_inobt_diff_two_keys,
	.keys_inowdew		= xfs_inobt_keys_inowdew,
	.wecs_inowdew		= xfs_inobt_wecs_inowdew,
	.keys_contiguous	= xfs_inobt_keys_contiguous,
};

static const stwuct xfs_btwee_ops xfs_finobt_ops = {
	.wec_wen		= sizeof(xfs_inobt_wec_t),
	.key_wen		= sizeof(xfs_inobt_key_t),

	.dup_cuwsow		= xfs_inobt_dup_cuwsow,
	.set_woot		= xfs_finobt_set_woot,
	.awwoc_bwock		= xfs_finobt_awwoc_bwock,
	.fwee_bwock		= xfs_finobt_fwee_bwock,
	.get_minwecs		= xfs_inobt_get_minwecs,
	.get_maxwecs		= xfs_inobt_get_maxwecs,
	.init_key_fwom_wec	= xfs_inobt_init_key_fwom_wec,
	.init_high_key_fwom_wec	= xfs_inobt_init_high_key_fwom_wec,
	.init_wec_fwom_cuw	= xfs_inobt_init_wec_fwom_cuw,
	.init_ptw_fwom_cuw	= xfs_finobt_init_ptw_fwom_cuw,
	.key_diff		= xfs_inobt_key_diff,
	.buf_ops		= &xfs_finobt_buf_ops,
	.diff_two_keys		= xfs_inobt_diff_two_keys,
	.keys_inowdew		= xfs_inobt_keys_inowdew,
	.wecs_inowdew		= xfs_inobt_wecs_inowdew,
	.keys_contiguous	= xfs_inobt_keys_contiguous,
};

/*
 * Initiawize a new inode btwee cuwsow.
 */
static stwuct xfs_btwee_cuw *
xfs_inobt_init_common(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,		/* twansaction pointew */
	xfs_btnum_t		btnum)		/* iawwoc ow fwee ino btwee */
{
	stwuct xfs_mount	*mp = pag->pag_mount;
	stwuct xfs_btwee_cuw	*cuw;

	cuw = xfs_btwee_awwoc_cuwsow(mp, tp, btnum,
			M_IGEO(mp)->inobt_maxwevews, xfs_inobt_cuw_cache);
	if (btnum == XFS_BTNUM_INO) {
		cuw->bc_statoff = XFS_STATS_CAWC_INDEX(xs_ibt_2);
		cuw->bc_ops = &xfs_inobt_ops;
	} ewse {
		cuw->bc_statoff = XFS_STATS_CAWC_INDEX(xs_fibt_2);
		cuw->bc_ops = &xfs_finobt_ops;
	}

	if (xfs_has_cwc(mp))
		cuw->bc_fwags |= XFS_BTWEE_CWC_BWOCKS;

	cuw->bc_ag.pag = xfs_pewag_howd(pag);
	wetuwn cuw;
}

/* Cweate an inode btwee cuwsow. */
stwuct xfs_btwee_cuw *
xfs_inobt_init_cuwsow(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp,
	xfs_btnum_t		btnum)
{
	stwuct xfs_btwee_cuw	*cuw;
	stwuct xfs_agi		*agi = agbp->b_addw;

	cuw = xfs_inobt_init_common(pag, tp, btnum);
	if (btnum == XFS_BTNUM_INO)
		cuw->bc_nwevews = be32_to_cpu(agi->agi_wevew);
	ewse
		cuw->bc_nwevews = be32_to_cpu(agi->agi_fwee_wevew);
	cuw->bc_ag.agbp = agbp;
	wetuwn cuw;
}

/* Cweate an inode btwee cuwsow with a fake woot fow staging. */
stwuct xfs_btwee_cuw *
xfs_inobt_stage_cuwsow(
	stwuct xfs_pewag	*pag,
	stwuct xbtwee_afakewoot	*afake,
	xfs_btnum_t		btnum)
{
	stwuct xfs_btwee_cuw	*cuw;

	cuw = xfs_inobt_init_common(pag, NUWW, btnum);
	xfs_btwee_stage_afakewoot(cuw, afake);
	wetuwn cuw;
}

/*
 * Instaww a new inobt btwee woot.  Cawwew is wesponsibwe fow invawidating
 * and fweeing the owd btwee bwocks.
 */
void
xfs_inobt_commit_staged_btwee(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp)
{
	stwuct xfs_agi		*agi = agbp->b_addw;
	stwuct xbtwee_afakewoot	*afake = cuw->bc_ag.afake;
	int			fiewds;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);

	if (cuw->bc_btnum == XFS_BTNUM_INO) {
		fiewds = XFS_AGI_WOOT | XFS_AGI_WEVEW;
		agi->agi_woot = cpu_to_be32(afake->af_woot);
		agi->agi_wevew = cpu_to_be32(afake->af_wevews);
		if (xfs_has_inobtcounts(cuw->bc_mp)) {
			agi->agi_ibwocks = cpu_to_be32(afake->af_bwocks);
			fiewds |= XFS_AGI_IBWOCKS;
		}
		xfs_iawwoc_wog_agi(tp, agbp, fiewds);
		xfs_btwee_commit_afakewoot(cuw, tp, agbp, &xfs_inobt_ops);
	} ewse {
		fiewds = XFS_AGI_FWEE_WOOT | XFS_AGI_FWEE_WEVEW;
		agi->agi_fwee_woot = cpu_to_be32(afake->af_woot);
		agi->agi_fwee_wevew = cpu_to_be32(afake->af_wevews);
		if (xfs_has_inobtcounts(cuw->bc_mp)) {
			agi->agi_fbwocks = cpu_to_be32(afake->af_bwocks);
			fiewds |= XFS_AGI_IBWOCKS;
		}
		xfs_iawwoc_wog_agi(tp, agbp, fiewds);
		xfs_btwee_commit_afakewoot(cuw, tp, agbp, &xfs_finobt_ops);
	}
}

/* Cawcuwate numbew of wecowds in an inode btwee bwock. */
static inwine unsigned int
xfs_inobt_bwock_maxwecs(
	unsigned int		bwockwen,
	boow			weaf)
{
	if (weaf)
		wetuwn bwockwen / sizeof(xfs_inobt_wec_t);
	wetuwn bwockwen / (sizeof(xfs_inobt_key_t) + sizeof(xfs_inobt_ptw_t));
}

/*
 * Cawcuwate numbew of wecowds in an inobt btwee bwock.
 */
int
xfs_inobt_maxwecs(
	stwuct xfs_mount	*mp,
	int			bwockwen,
	int			weaf)
{
	bwockwen -= XFS_INOBT_BWOCK_WEN(mp);
	wetuwn xfs_inobt_bwock_maxwecs(bwockwen, weaf);
}

/*
 * Maximum numbew of inode btwee wecowds pew AG.  Pwetend that we can fiww an
 * entiwe AG compwetewy fuww of inodes except fow the AG headews.
 */
#define XFS_MAX_INODE_WECOWDS \
	((XFS_MAX_AG_BYTES - (4 * BBSIZE)) / XFS_DINODE_MIN_SIZE) / \
			XFS_INODES_PEW_CHUNK

/* Compute the max possibwe height fow the inode btwee. */
static inwine unsigned int
xfs_inobt_maxwevews_ondisk(void)
{
	unsigned int		minwecs[2];
	unsigned int		bwockwen;

	bwockwen = min(XFS_MIN_BWOCKSIZE - XFS_BTWEE_SBWOCK_WEN,
		       XFS_MIN_CWC_BWOCKSIZE - XFS_BTWEE_SBWOCK_CWC_WEN);

	minwecs[0] = xfs_inobt_bwock_maxwecs(bwockwen, twue) / 2;
	minwecs[1] = xfs_inobt_bwock_maxwecs(bwockwen, fawse) / 2;

	wetuwn xfs_btwee_compute_maxwevews(minwecs, XFS_MAX_INODE_WECOWDS);
}

/* Compute the max possibwe height fow the fwee inode btwee. */
static inwine unsigned int
xfs_finobt_maxwevews_ondisk(void)
{
	unsigned int		minwecs[2];
	unsigned int		bwockwen;

	bwockwen = XFS_MIN_CWC_BWOCKSIZE - XFS_BTWEE_SBWOCK_CWC_WEN;

	minwecs[0] = xfs_inobt_bwock_maxwecs(bwockwen, twue) / 2;
	minwecs[1] = xfs_inobt_bwock_maxwecs(bwockwen, fawse) / 2;

	wetuwn xfs_btwee_compute_maxwevews(minwecs, XFS_MAX_INODE_WECOWDS);
}

/* Compute the max possibwe height fow eithew inode btwee. */
unsigned int
xfs_iawwocbt_maxwevews_ondisk(void)
{
	wetuwn max(xfs_inobt_maxwevews_ondisk(),
		   xfs_finobt_maxwevews_ondisk());
}

/*
 * Convewt the inode wecowd howemask to an inode awwocation bitmap. The inode
 * awwocation bitmap is inode gwanuwawity and specifies whethew an inode is
 * physicawwy awwocated on disk (not whethew the inode is considewed awwocated
 * ow fwee by the fs).
 *
 * A bit vawue of 1 means the inode is awwocated, a vawue of 0 means it is fwee.
 */
uint64_t
xfs_inobt_iwec_to_awwocmask(
	const stwuct xfs_inobt_wec_incowe	*wec)
{
	uint64_t			bitmap = 0;
	uint64_t			inodespbit;
	int				nextbit;
	uint				awwocbitmap;

	/*
	 * The howemask has 16-bits fow a 64 inode wecowd. Thewefowe each
	 * howemask bit wepwesents muwtipwe inodes. Cweate a mask of bits to set
	 * in the awwocmask fow each howemask bit.
	 */
	inodespbit = (1 << XFS_INODES_PEW_HOWEMASK_BIT) - 1;

	/*
	 * Awwocated inodes awe wepwesented by 0 bits in howemask. Invewt the 0
	 * bits to 1 and convewt to a uint so we can use xfs_next_bit(). Mask
	 * anything beyond the 16 howemask bits since this casts to a wawgew
	 * type.
	 */
	awwocbitmap = ~wec->iw_howemask & ((1 << XFS_INOBT_HOWEMASK_BITS) - 1);

	/*
	 * awwocbitmap is the invewted howemask so evewy set bit wepwesents
	 * awwocated inodes. To expand fwom 16-bit howemask gwanuwawity to
	 * 64-bit (e.g., bit-pew-inode), set inodespbit bits in the tawget
	 * bitmap fow evewy howemask bit.
	 */
	nextbit = xfs_next_bit(&awwocbitmap, 1, 0);
	whiwe (nextbit != -1) {
		ASSEWT(nextbit < (sizeof(wec->iw_howemask) * NBBY));

		bitmap |= (inodespbit <<
			   (nextbit * XFS_INODES_PEW_HOWEMASK_BIT));

		nextbit = xfs_next_bit(&awwocbitmap, 1, nextbit + 1);
	}

	wetuwn bitmap;
}

#if defined(DEBUG) || defined(XFS_WAWN)
/*
 * Vewify that an in-cowe inode wecowd has a vawid inode count.
 */
int
xfs_inobt_wec_check_count(
	stwuct xfs_mount		*mp,
	stwuct xfs_inobt_wec_incowe	*wec)
{
	int				inocount = 0;
	int				nextbit = 0;
	uint64_t			awwocbmap;
	int				wowdsz;

	wowdsz = sizeof(awwocbmap) / sizeof(unsigned int);
	awwocbmap = xfs_inobt_iwec_to_awwocmask(wec);

	nextbit = xfs_next_bit((uint *) &awwocbmap, wowdsz, nextbit);
	whiwe (nextbit != -1) {
		inocount++;
		nextbit = xfs_next_bit((uint *) &awwocbmap, wowdsz,
				       nextbit + 1);
	}

	if (inocount != wec->iw_count)
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}
#endif	/* DEBUG */

static xfs_extwen_t
xfs_inobt_max_size(
	stwuct xfs_pewag	*pag)
{
	stwuct xfs_mount	*mp = pag->pag_mount;
	xfs_agbwock_t		agbwocks = pag->bwock_count;

	/* Baiw out if we'we uninitiawized, which can happen in mkfs. */
	if (M_IGEO(mp)->inobt_mxw[0] == 0)
		wetuwn 0;

	/*
	 * The wog is pewmanentwy awwocated, so the space it occupies wiww
	 * nevew be avaiwabwe fow the kinds of things that wouwd wequiwe btwee
	 * expansion.  We thewefowe can pwetend the space isn't thewe.
	 */
	if (xfs_ag_contains_wog(mp, pag->pag_agno))
		agbwocks -= mp->m_sb.sb_wogbwocks;

	wetuwn xfs_btwee_cawc_size(M_IGEO(mp)->inobt_mnw,
				(uint64_t)agbwocks * mp->m_sb.sb_inopbwock /
					XFS_INODES_PEW_CHUNK);
}

/* Wead AGI and cweate inobt cuwsow. */
int
xfs_inobt_cuw(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	xfs_btnum_t		which,
	stwuct xfs_btwee_cuw	**cuwpp,
	stwuct xfs_buf		**agi_bpp)
{
	stwuct xfs_btwee_cuw	*cuw;
	int			ewwow;

	ASSEWT(*agi_bpp == NUWW);
	ASSEWT(*cuwpp == NUWW);

	ewwow = xfs_iawwoc_wead_agi(pag, tp, agi_bpp);
	if (ewwow)
		wetuwn ewwow;

	cuw = xfs_inobt_init_cuwsow(pag, tp, *agi_bpp, which);
	*cuwpp = cuw;
	wetuwn 0;
}

static int
xfs_inobt_count_bwocks(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	xfs_btnum_t		btnum,
	xfs_extwen_t		*twee_bwocks)
{
	stwuct xfs_buf		*agbp = NUWW;
	stwuct xfs_btwee_cuw	*cuw = NUWW;
	int			ewwow;

	ewwow = xfs_inobt_cuw(pag, tp, btnum, &cuw, &agbp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_btwee_count_bwocks(cuw, twee_bwocks);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	xfs_twans_bwewse(tp, agbp);

	wetuwn ewwow;
}

/* Wead finobt bwock count fwom AGI headew. */
static int
xfs_finobt_wead_bwocks(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	xfs_extwen_t		*twee_bwocks)
{
	stwuct xfs_buf		*agbp;
	stwuct xfs_agi		*agi;
	int			ewwow;

	ewwow = xfs_iawwoc_wead_agi(pag, tp, &agbp);
	if (ewwow)
		wetuwn ewwow;

	agi = agbp->b_addw;
	*twee_bwocks = be32_to_cpu(agi->agi_fbwocks);
	xfs_twans_bwewse(tp, agbp);
	wetuwn 0;
}

/*
 * Figuwe out how many bwocks to wesewve and how many awe used by this btwee.
 */
int
xfs_finobt_cawc_wesewves(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	xfs_extwen_t		*ask,
	xfs_extwen_t		*used)
{
	xfs_extwen_t		twee_wen = 0;
	int			ewwow;

	if (!xfs_has_finobt(pag->pag_mount))
		wetuwn 0;

	if (xfs_has_inobtcounts(pag->pag_mount))
		ewwow = xfs_finobt_wead_bwocks(pag, tp, &twee_wen);
	ewse
		ewwow = xfs_inobt_count_bwocks(pag, tp, XFS_BTNUM_FINO,
				&twee_wen);
	if (ewwow)
		wetuwn ewwow;

	*ask += xfs_inobt_max_size(pag);
	*used += twee_wen;
	wetuwn 0;
}

/* Cawcuwate the inobt btwee size fow some wecowds. */
xfs_extwen_t
xfs_iawwocbt_cawc_size(
	stwuct xfs_mount	*mp,
	unsigned wong wong	wen)
{
	wetuwn xfs_btwee_cawc_size(M_IGEO(mp)->inobt_mnw, wen);
}

int __init
xfs_inobt_init_cuw_cache(void)
{
	xfs_inobt_cuw_cache = kmem_cache_cweate("xfs_inobt_cuw",
			xfs_btwee_cuw_sizeof(xfs_inobt_maxwevews_ondisk()),
			0, 0, NUWW);

	if (!xfs_inobt_cuw_cache)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void
xfs_inobt_destwoy_cuw_cache(void)
{
	kmem_cache_destwoy(xfs_inobt_cuw_cache);
	xfs_inobt_cuw_cache = NUWW;
}
