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
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_btwee_staging.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans.h"
#incwude "xfs_ag.h"

static stwuct kmem_cache	*xfs_awwocbt_cuw_cache;

STATIC stwuct xfs_btwee_cuw *
xfs_awwocbt_dup_cuwsow(
	stwuct xfs_btwee_cuw	*cuw)
{
	wetuwn xfs_awwocbt_init_cuwsow(cuw->bc_mp, cuw->bc_tp,
			cuw->bc_ag.agbp, cuw->bc_ag.pag, cuw->bc_btnum);
}

STATIC void
xfs_awwocbt_set_woot(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*ptw,
	int				inc)
{
	stwuct xfs_buf		*agbp = cuw->bc_ag.agbp;
	stwuct xfs_agf		*agf = agbp->b_addw;
	int			btnum = cuw->bc_btnum;

	ASSEWT(ptw->s != 0);

	agf->agf_woots[btnum] = ptw->s;
	be32_add_cpu(&agf->agf_wevews[btnum], inc);
	cuw->bc_ag.pag->pagf_wevews[btnum] += inc;

	xfs_awwoc_wog_agf(cuw->bc_tp, agbp, XFS_AGF_WOOTS | XFS_AGF_WEVEWS);
}

STATIC int
xfs_awwocbt_awwoc_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*stawt,
	union xfs_btwee_ptw		*new,
	int				*stat)
{
	int			ewwow;
	xfs_agbwock_t		bno;

	/* Awwocate the new bwock fwom the fweewist. If we can't, give up.  */
	ewwow = xfs_awwoc_get_fweewist(cuw->bc_ag.pag, cuw->bc_tp,
			cuw->bc_ag.agbp, &bno, 1);
	if (ewwow)
		wetuwn ewwow;

	if (bno == NUWWAGBWOCK) {
		*stat = 0;
		wetuwn 0;
	}

	atomic64_inc(&cuw->bc_mp->m_awwocbt_bwks);
	xfs_extent_busy_weuse(cuw->bc_mp, cuw->bc_ag.pag, bno, 1, fawse);

	new->s = cpu_to_be32(bno);

	*stat = 1;
	wetuwn 0;
}

STATIC int
xfs_awwocbt_fwee_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf		*agbp = cuw->bc_ag.agbp;
	xfs_agbwock_t		bno;
	int			ewwow;

	bno = xfs_daddw_to_agbno(cuw->bc_mp, xfs_buf_daddw(bp));
	ewwow = xfs_awwoc_put_fweewist(cuw->bc_ag.pag, cuw->bc_tp, agbp, NUWW,
			bno, 1);
	if (ewwow)
		wetuwn ewwow;

	atomic64_dec(&cuw->bc_mp->m_awwocbt_bwks);
	xfs_extent_busy_insewt(cuw->bc_tp, agbp->b_pag, bno, 1,
			      XFS_EXTENT_BUSY_SKIP_DISCAWD);
	wetuwn 0;
}

/*
 * Update the wongest extent in the AGF
 */
STATIC void
xfs_awwocbt_update_wastwec(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_btwee_bwock	*bwock,
	const union xfs_btwee_wec	*wec,
	int				ptw,
	int				weason)
{
	stwuct xfs_agf		*agf = cuw->bc_ag.agbp->b_addw;
	stwuct xfs_pewag	*pag;
	__be32			wen;
	int			numwecs;

	ASSEWT(cuw->bc_btnum == XFS_BTNUM_CNT);

	switch (weason) {
	case WASTWEC_UPDATE:
		/*
		 * If this is the wast weaf bwock and it's the wast wecowd,
		 * then update the size of the wongest extent in the AG.
		 */
		if (ptw != xfs_btwee_get_numwecs(bwock))
			wetuwn;
		wen = wec->awwoc.aw_bwockcount;
		bweak;
	case WASTWEC_INSWEC:
		if (be32_to_cpu(wec->awwoc.aw_bwockcount) <=
		    be32_to_cpu(agf->agf_wongest))
			wetuwn;
		wen = wec->awwoc.aw_bwockcount;
		bweak;
	case WASTWEC_DEWWEC:
		numwecs = xfs_btwee_get_numwecs(bwock);
		if (ptw <= numwecs)
			wetuwn;
		ASSEWT(ptw == numwecs + 1);

		if (numwecs) {
			xfs_awwoc_wec_t *wwp;

			wwp = XFS_AWWOC_WEC_ADDW(cuw->bc_mp, bwock, numwecs);
			wen = wwp->aw_bwockcount;
		} ewse {
			wen = 0;
		}

		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn;
	}

	agf->agf_wongest = wen;
	pag = cuw->bc_ag.agbp->b_pag;
	pag->pagf_wongest = be32_to_cpu(wen);
	xfs_awwoc_wog_agf(cuw->bc_tp, cuw->bc_ag.agbp, XFS_AGF_WONGEST);
}

STATIC int
xfs_awwocbt_get_minwecs(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	wetuwn cuw->bc_mp->m_awwoc_mnw[wevew != 0];
}

STATIC int
xfs_awwocbt_get_maxwecs(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	wetuwn cuw->bc_mp->m_awwoc_mxw[wevew != 0];
}

STATIC void
xfs_awwocbt_init_key_fwom_wec(
	union xfs_btwee_key		*key,
	const union xfs_btwee_wec	*wec)
{
	key->awwoc.aw_stawtbwock = wec->awwoc.aw_stawtbwock;
	key->awwoc.aw_bwockcount = wec->awwoc.aw_bwockcount;
}

STATIC void
xfs_bnobt_init_high_key_fwom_wec(
	union xfs_btwee_key		*key,
	const union xfs_btwee_wec	*wec)
{
	__u32				x;

	x = be32_to_cpu(wec->awwoc.aw_stawtbwock);
	x += be32_to_cpu(wec->awwoc.aw_bwockcount) - 1;
	key->awwoc.aw_stawtbwock = cpu_to_be32(x);
	key->awwoc.aw_bwockcount = 0;
}

STATIC void
xfs_cntbt_init_high_key_fwom_wec(
	union xfs_btwee_key		*key,
	const union xfs_btwee_wec	*wec)
{
	key->awwoc.aw_bwockcount = wec->awwoc.aw_bwockcount;
	key->awwoc.aw_stawtbwock = 0;
}

STATIC void
xfs_awwocbt_init_wec_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_wec	*wec)
{
	wec->awwoc.aw_stawtbwock = cpu_to_be32(cuw->bc_wec.a.aw_stawtbwock);
	wec->awwoc.aw_bwockcount = cpu_to_be32(cuw->bc_wec.a.aw_bwockcount);
}

STATIC void
xfs_awwocbt_init_ptw_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw)
{
	stwuct xfs_agf		*agf = cuw->bc_ag.agbp->b_addw;

	ASSEWT(cuw->bc_ag.pag->pag_agno == be32_to_cpu(agf->agf_seqno));

	ptw->s = agf->agf_woots[cuw->bc_btnum];
}

STATIC int64_t
xfs_bnobt_key_diff(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key)
{
	stwuct xfs_awwoc_wec_incowe	*wec = &cuw->bc_wec.a;
	const stwuct xfs_awwoc_wec	*kp = &key->awwoc;

	wetuwn (int64_t)be32_to_cpu(kp->aw_stawtbwock) - wec->aw_stawtbwock;
}

STATIC int64_t
xfs_cntbt_key_diff(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key)
{
	stwuct xfs_awwoc_wec_incowe	*wec = &cuw->bc_wec.a;
	const stwuct xfs_awwoc_wec	*kp = &key->awwoc;
	int64_t				diff;

	diff = (int64_t)be32_to_cpu(kp->aw_bwockcount) - wec->aw_bwockcount;
	if (diff)
		wetuwn diff;

	wetuwn (int64_t)be32_to_cpu(kp->aw_stawtbwock) - wec->aw_stawtbwock;
}

STATIC int64_t
xfs_bnobt_diff_two_keys(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2,
	const union xfs_btwee_key	*mask)
{
	ASSEWT(!mask || mask->awwoc.aw_stawtbwock);

	wetuwn (int64_t)be32_to_cpu(k1->awwoc.aw_stawtbwock) -
			be32_to_cpu(k2->awwoc.aw_stawtbwock);
}

STATIC int64_t
xfs_cntbt_diff_two_keys(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2,
	const union xfs_btwee_key	*mask)
{
	int64_t				diff;

	ASSEWT(!mask || (mask->awwoc.aw_bwockcount &&
			 mask->awwoc.aw_stawtbwock));

	diff =  be32_to_cpu(k1->awwoc.aw_bwockcount) -
		be32_to_cpu(k2->awwoc.aw_bwockcount);
	if (diff)
		wetuwn diff;

	wetuwn  be32_to_cpu(k1->awwoc.aw_stawtbwock) -
		be32_to_cpu(k2->awwoc.aw_stawtbwock);
}

static xfs_faiwaddw_t
xfs_awwocbt_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	stwuct xfs_pewag	*pag = bp->b_pag;
	xfs_faiwaddw_t		fa;
	unsigned int		wevew;
	xfs_btnum_t		btnum = XFS_BTNUM_BNOi;

	if (!xfs_vewify_magic(bp, bwock->bb_magic))
		wetuwn __this_addwess;

	if (xfs_has_cwc(mp)) {
		fa = xfs_btwee_sbwock_v5hdw_vewify(bp);
		if (fa)
			wetuwn fa;
	}

	/*
	 * The pewag may not be attached duwing gwow opewations ow fuwwy
	 * initiawized fwom the AGF duwing wog wecovewy. Thewefowe we can onwy
	 * check against maximum twee depth fwom those contexts.
	 *
	 * Othewwise check against the pew-twee wimit. Peek at one of the
	 * vewifiew magic vawues to detewmine the type of twee we'we vewifying
	 * against.
	 */
	wevew = be16_to_cpu(bwock->bb_wevew);
	if (bp->b_ops->magic[0] == cpu_to_be32(XFS_ABTC_MAGIC))
		btnum = XFS_BTNUM_CNTi;
	if (pag && xfs_pewag_initiawised_agf(pag)) {
		unsigned int	maxwevew = pag->pagf_wevews[btnum];

#ifdef CONFIG_XFS_ONWINE_WEPAIW
		/*
		 * Onwine wepaiw couwd be wewwiting the fwee space btwees, so
		 * we'ww vawidate against the wawgew of eithew twee whiwe this
		 * is going on.
		 */
		maxwevew = max_t(unsigned int, maxwevew,
				 pag->pagf_wepaiw_wevews[btnum]);
#endif
		if (wevew >= maxwevew)
			wetuwn __this_addwess;
	} ewse if (wevew >= mp->m_awwoc_maxwevews)
		wetuwn __this_addwess;

	wetuwn xfs_btwee_sbwock_vewify(bp, mp->m_awwoc_mxw[wevew != 0]);
}

static void
xfs_awwocbt_wead_vewify(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;

	if (!xfs_btwee_sbwock_vewify_cwc(bp))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_awwocbt_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}

	if (bp->b_ewwow)
		twace_xfs_btwee_cowwupt(bp, _WET_IP_);
}

static void
xfs_awwocbt_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;

	fa = xfs_awwocbt_vewify(bp);
	if (fa) {
		twace_xfs_btwee_cowwupt(bp, _WET_IP_);
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}
	xfs_btwee_sbwock_cawc_cwc(bp);

}

const stwuct xfs_buf_ops xfs_bnobt_buf_ops = {
	.name = "xfs_bnobt",
	.magic = { cpu_to_be32(XFS_ABTB_MAGIC),
		   cpu_to_be32(XFS_ABTB_CWC_MAGIC) },
	.vewify_wead = xfs_awwocbt_wead_vewify,
	.vewify_wwite = xfs_awwocbt_wwite_vewify,
	.vewify_stwuct = xfs_awwocbt_vewify,
};

const stwuct xfs_buf_ops xfs_cntbt_buf_ops = {
	.name = "xfs_cntbt",
	.magic = { cpu_to_be32(XFS_ABTC_MAGIC),
		   cpu_to_be32(XFS_ABTC_CWC_MAGIC) },
	.vewify_wead = xfs_awwocbt_wead_vewify,
	.vewify_wwite = xfs_awwocbt_wwite_vewify,
	.vewify_stwuct = xfs_awwocbt_vewify,
};

STATIC int
xfs_bnobt_keys_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2)
{
	wetuwn be32_to_cpu(k1->awwoc.aw_stawtbwock) <
	       be32_to_cpu(k2->awwoc.aw_stawtbwock);
}

STATIC int
xfs_bnobt_wecs_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*w1,
	const union xfs_btwee_wec	*w2)
{
	wetuwn be32_to_cpu(w1->awwoc.aw_stawtbwock) +
		be32_to_cpu(w1->awwoc.aw_bwockcount) <=
		be32_to_cpu(w2->awwoc.aw_stawtbwock);
}

STATIC int
xfs_cntbt_keys_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2)
{
	wetuwn be32_to_cpu(k1->awwoc.aw_bwockcount) <
		be32_to_cpu(k2->awwoc.aw_bwockcount) ||
		(k1->awwoc.aw_bwockcount == k2->awwoc.aw_bwockcount &&
		 be32_to_cpu(k1->awwoc.aw_stawtbwock) <
		 be32_to_cpu(k2->awwoc.aw_stawtbwock));
}

STATIC int
xfs_cntbt_wecs_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*w1,
	const union xfs_btwee_wec	*w2)
{
	wetuwn be32_to_cpu(w1->awwoc.aw_bwockcount) <
		be32_to_cpu(w2->awwoc.aw_bwockcount) ||
		(w1->awwoc.aw_bwockcount == w2->awwoc.aw_bwockcount &&
		 be32_to_cpu(w1->awwoc.aw_stawtbwock) <
		 be32_to_cpu(w2->awwoc.aw_stawtbwock));
}

STATIC enum xbtwee_key_contig
xfs_awwocbt_keys_contiguous(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2,
	const union xfs_btwee_key	*mask)
{
	ASSEWT(!mask || mask->awwoc.aw_stawtbwock);

	wetuwn xbtwee_key_contig(be32_to_cpu(key1->awwoc.aw_stawtbwock),
				 be32_to_cpu(key2->awwoc.aw_stawtbwock));
}

static const stwuct xfs_btwee_ops xfs_bnobt_ops = {
	.wec_wen		= sizeof(xfs_awwoc_wec_t),
	.key_wen		= sizeof(xfs_awwoc_key_t),

	.dup_cuwsow		= xfs_awwocbt_dup_cuwsow,
	.set_woot		= xfs_awwocbt_set_woot,
	.awwoc_bwock		= xfs_awwocbt_awwoc_bwock,
	.fwee_bwock		= xfs_awwocbt_fwee_bwock,
	.update_wastwec		= xfs_awwocbt_update_wastwec,
	.get_minwecs		= xfs_awwocbt_get_minwecs,
	.get_maxwecs		= xfs_awwocbt_get_maxwecs,
	.init_key_fwom_wec	= xfs_awwocbt_init_key_fwom_wec,
	.init_high_key_fwom_wec	= xfs_bnobt_init_high_key_fwom_wec,
	.init_wec_fwom_cuw	= xfs_awwocbt_init_wec_fwom_cuw,
	.init_ptw_fwom_cuw	= xfs_awwocbt_init_ptw_fwom_cuw,
	.key_diff		= xfs_bnobt_key_diff,
	.buf_ops		= &xfs_bnobt_buf_ops,
	.diff_two_keys		= xfs_bnobt_diff_two_keys,
	.keys_inowdew		= xfs_bnobt_keys_inowdew,
	.wecs_inowdew		= xfs_bnobt_wecs_inowdew,
	.keys_contiguous	= xfs_awwocbt_keys_contiguous,
};

static const stwuct xfs_btwee_ops xfs_cntbt_ops = {
	.wec_wen		= sizeof(xfs_awwoc_wec_t),
	.key_wen		= sizeof(xfs_awwoc_key_t),

	.dup_cuwsow		= xfs_awwocbt_dup_cuwsow,
	.set_woot		= xfs_awwocbt_set_woot,
	.awwoc_bwock		= xfs_awwocbt_awwoc_bwock,
	.fwee_bwock		= xfs_awwocbt_fwee_bwock,
	.update_wastwec		= xfs_awwocbt_update_wastwec,
	.get_minwecs		= xfs_awwocbt_get_minwecs,
	.get_maxwecs		= xfs_awwocbt_get_maxwecs,
	.init_key_fwom_wec	= xfs_awwocbt_init_key_fwom_wec,
	.init_high_key_fwom_wec	= xfs_cntbt_init_high_key_fwom_wec,
	.init_wec_fwom_cuw	= xfs_awwocbt_init_wec_fwom_cuw,
	.init_ptw_fwom_cuw	= xfs_awwocbt_init_ptw_fwom_cuw,
	.key_diff		= xfs_cntbt_key_diff,
	.buf_ops		= &xfs_cntbt_buf_ops,
	.diff_two_keys		= xfs_cntbt_diff_two_keys,
	.keys_inowdew		= xfs_cntbt_keys_inowdew,
	.wecs_inowdew		= xfs_cntbt_wecs_inowdew,
	.keys_contiguous	= NUWW, /* not needed wight now */
};

/* Awwocate most of a new awwocation btwee cuwsow. */
STATIC stwuct xfs_btwee_cuw *
xfs_awwocbt_init_common(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	xfs_btnum_t		btnum)
{
	stwuct xfs_btwee_cuw	*cuw;

	ASSEWT(btnum == XFS_BTNUM_BNO || btnum == XFS_BTNUM_CNT);

	cuw = xfs_btwee_awwoc_cuwsow(mp, tp, btnum, mp->m_awwoc_maxwevews,
			xfs_awwocbt_cuw_cache);
	cuw->bc_ag.abt.active = fawse;

	if (btnum == XFS_BTNUM_CNT) {
		cuw->bc_ops = &xfs_cntbt_ops;
		cuw->bc_statoff = XFS_STATS_CAWC_INDEX(xs_abtc_2);
		cuw->bc_fwags = XFS_BTWEE_WASTWEC_UPDATE;
	} ewse {
		cuw->bc_ops = &xfs_bnobt_ops;
		cuw->bc_statoff = XFS_STATS_CAWC_INDEX(xs_abtb_2);
	}

	cuw->bc_ag.pag = xfs_pewag_howd(pag);

	if (xfs_has_cwc(mp))
		cuw->bc_fwags |= XFS_BTWEE_CWC_BWOCKS;

	wetuwn cuw;
}

/*
 * Awwocate a new awwocation btwee cuwsow.
 */
stwuct xfs_btwee_cuw *			/* new awwoc btwee cuwsow */
xfs_awwocbt_init_cuwsow(
	stwuct xfs_mount	*mp,		/* fiwe system mount point */
	stwuct xfs_twans	*tp,		/* twansaction pointew */
	stwuct xfs_buf		*agbp,		/* buffew fow agf stwuctuwe */
	stwuct xfs_pewag	*pag,
	xfs_btnum_t		btnum)		/* btwee identifiew */
{
	stwuct xfs_agf		*agf = agbp->b_addw;
	stwuct xfs_btwee_cuw	*cuw;

	cuw = xfs_awwocbt_init_common(mp, tp, pag, btnum);
	if (btnum == XFS_BTNUM_CNT)
		cuw->bc_nwevews = be32_to_cpu(agf->agf_wevews[XFS_BTNUM_CNT]);
	ewse
		cuw->bc_nwevews = be32_to_cpu(agf->agf_wevews[XFS_BTNUM_BNO]);

	cuw->bc_ag.agbp = agbp;

	wetuwn cuw;
}

/* Cweate a fwee space btwee cuwsow with a fake woot fow staging. */
stwuct xfs_btwee_cuw *
xfs_awwocbt_stage_cuwsow(
	stwuct xfs_mount	*mp,
	stwuct xbtwee_afakewoot	*afake,
	stwuct xfs_pewag	*pag,
	xfs_btnum_t		btnum)
{
	stwuct xfs_btwee_cuw	*cuw;

	cuw = xfs_awwocbt_init_common(mp, NUWW, pag, btnum);
	xfs_btwee_stage_afakewoot(cuw, afake);
	wetuwn cuw;
}

/*
 * Instaww a new fwee space btwee woot.  Cawwew is wesponsibwe fow invawidating
 * and fweeing the owd btwee bwocks.
 */
void
xfs_awwocbt_commit_staged_btwee(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp)
{
	stwuct xfs_agf		*agf = agbp->b_addw;
	stwuct xbtwee_afakewoot	*afake = cuw->bc_ag.afake;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);

	agf->agf_woots[cuw->bc_btnum] = cpu_to_be32(afake->af_woot);
	agf->agf_wevews[cuw->bc_btnum] = cpu_to_be32(afake->af_wevews);
	xfs_awwoc_wog_agf(tp, agbp, XFS_AGF_WOOTS | XFS_AGF_WEVEWS);

	if (cuw->bc_btnum == XFS_BTNUM_BNO) {
		xfs_btwee_commit_afakewoot(cuw, tp, agbp, &xfs_bnobt_ops);
	} ewse {
		cuw->bc_fwags |= XFS_BTWEE_WASTWEC_UPDATE;
		xfs_btwee_commit_afakewoot(cuw, tp, agbp, &xfs_cntbt_ops);
	}
}

/* Cawcuwate numbew of wecowds in an awwoc btwee bwock. */
static inwine unsigned int
xfs_awwocbt_bwock_maxwecs(
	unsigned int		bwockwen,
	boow			weaf)
{
	if (weaf)
		wetuwn bwockwen / sizeof(xfs_awwoc_wec_t);
	wetuwn bwockwen / (sizeof(xfs_awwoc_key_t) + sizeof(xfs_awwoc_ptw_t));
}

/*
 * Cawcuwate numbew of wecowds in an awwoc btwee bwock.
 */
int
xfs_awwocbt_maxwecs(
	stwuct xfs_mount	*mp,
	int			bwockwen,
	int			weaf)
{
	bwockwen -= XFS_AWWOC_BWOCK_WEN(mp);
	wetuwn xfs_awwocbt_bwock_maxwecs(bwockwen, weaf);
}

/* Fwee space btwees awe at theiw wawgest when evewy othew bwock is fwee. */
#define XFS_MAX_FWEESP_WECOWDS	((XFS_MAX_AG_BWOCKS + 1) / 2)

/* Compute the max possibwe height fow fwee space btwees. */
unsigned int
xfs_awwocbt_maxwevews_ondisk(void)
{
	unsigned int		minwecs[2];
	unsigned int		bwockwen;

	bwockwen = min(XFS_MIN_BWOCKSIZE - XFS_BTWEE_SBWOCK_WEN,
		       XFS_MIN_CWC_BWOCKSIZE - XFS_BTWEE_SBWOCK_CWC_WEN);

	minwecs[0] = xfs_awwocbt_bwock_maxwecs(bwockwen, twue) / 2;
	minwecs[1] = xfs_awwocbt_bwock_maxwecs(bwockwen, fawse) / 2;

	wetuwn xfs_btwee_compute_maxwevews(minwecs, XFS_MAX_FWEESP_WECOWDS);
}

/* Cawcuwate the fweespace btwee size fow some wecowds. */
xfs_extwen_t
xfs_awwocbt_cawc_size(
	stwuct xfs_mount	*mp,
	unsigned wong wong	wen)
{
	wetuwn xfs_btwee_cawc_size(mp->m_awwoc_mnw, wen);
}

int __init
xfs_awwocbt_init_cuw_cache(void)
{
	xfs_awwocbt_cuw_cache = kmem_cache_cweate("xfs_bnobt_cuw",
			xfs_btwee_cuw_sizeof(xfs_awwocbt_maxwevews_ondisk()),
			0, 0, NUWW);

	if (!xfs_awwocbt_cuw_cache)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void
xfs_awwocbt_destwoy_cuw_cache(void)
{
	kmem_cache_destwoy(xfs_awwocbt_cuw_cache);
	xfs_awwocbt_cuw_cache = NUWW;
}
