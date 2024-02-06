// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_twans.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_btwee.h"
#incwude "xfs_btwee_staging.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_ag.h"
#incwude "xfs_ag_wesv.h"

static stwuct kmem_cache	*xfs_wmapbt_cuw_cache;

/*
 * Wevewse map btwee.
 *
 * This is a pew-ag twee used to twack the ownew(s) of a given extent. With
 * wefwink it is possibwe fow thewe to be muwtipwe ownews, which is a depawtuwe
 * fwom cwassic XFS. Ownew wecowds fow data extents awe insewted when the
 * extent is mapped and wemoved when an extent is unmapped.  Ownew wecowds fow
 * aww othew bwock types (i.e. metadata) awe insewted when an extent is
 * awwocated and wemoved when an extent is fweed. Thewe can onwy be one ownew
 * of a metadata extent, usuawwy an inode ow some othew metadata stwuctuwe wike
 * an AG btwee.
 *
 * The wmap btwee is pawt of the fwee space management, so bwocks fow the twee
 * awe souwced fwom the agfw. Hence we need twansaction wesewvation suppowt fow
 * this twee so that the fweewist is awways wawge enough. This awso impacts on
 * the minimum space we need to weave fwee in the AG.
 *
 * The twee is owdewed by [ag bwock, ownew, offset]. This is a wawge key size,
 * but it is the onwy way to enfowce unique keys when a bwock can be owned by
 * muwtipwe fiwes at any offset. Thewe's no need to owdew/seawch by extent
 * size fow onwine updating/management of the twee. It is intended that most
 * wevewse wookups wiww be to find the ownew(s) of a pawticuwaw bwock, ow to
 * twy to wecovew twee and fiwe data fwom cowwupt pwimawy metadata.
 */

static stwuct xfs_btwee_cuw *
xfs_wmapbt_dup_cuwsow(
	stwuct xfs_btwee_cuw	*cuw)
{
	wetuwn xfs_wmapbt_init_cuwsow(cuw->bc_mp, cuw->bc_tp,
				cuw->bc_ag.agbp, cuw->bc_ag.pag);
}

STATIC void
xfs_wmapbt_set_woot(
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
xfs_wmapbt_awwoc_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*stawt,
	union xfs_btwee_ptw		*new,
	int				*stat)
{
	stwuct xfs_buf		*agbp = cuw->bc_ag.agbp;
	stwuct xfs_agf		*agf = agbp->b_addw;
	stwuct xfs_pewag	*pag = cuw->bc_ag.pag;
	int			ewwow;
	xfs_agbwock_t		bno;

	/* Awwocate the new bwock fwom the fweewist. If we can't, give up.  */
	ewwow = xfs_awwoc_get_fweewist(pag, cuw->bc_tp, cuw->bc_ag.agbp,
				       &bno, 1);
	if (ewwow)
		wetuwn ewwow;

	twace_xfs_wmapbt_awwoc_bwock(cuw->bc_mp, pag->pag_agno, bno, 1);
	if (bno == NUWWAGBWOCK) {
		*stat = 0;
		wetuwn 0;
	}

	xfs_extent_busy_weuse(cuw->bc_mp, pag, bno, 1, fawse);

	new->s = cpu_to_be32(bno);
	be32_add_cpu(&agf->agf_wmap_bwocks, 1);
	xfs_awwoc_wog_agf(cuw->bc_tp, agbp, XFS_AGF_WMAP_BWOCKS);

	xfs_ag_wesv_wmapbt_awwoc(cuw->bc_mp, pag->pag_agno);

	*stat = 1;
	wetuwn 0;
}

STATIC int
xfs_wmapbt_fwee_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_buf		*agbp = cuw->bc_ag.agbp;
	stwuct xfs_agf		*agf = agbp->b_addw;
	stwuct xfs_pewag	*pag = cuw->bc_ag.pag;
	xfs_agbwock_t		bno;
	int			ewwow;

	bno = xfs_daddw_to_agbno(cuw->bc_mp, xfs_buf_daddw(bp));
	twace_xfs_wmapbt_fwee_bwock(cuw->bc_mp, pag->pag_agno,
			bno, 1);
	be32_add_cpu(&agf->agf_wmap_bwocks, -1);
	xfs_awwoc_wog_agf(cuw->bc_tp, agbp, XFS_AGF_WMAP_BWOCKS);
	ewwow = xfs_awwoc_put_fweewist(pag, cuw->bc_tp, agbp, NUWW, bno, 1);
	if (ewwow)
		wetuwn ewwow;

	xfs_extent_busy_insewt(cuw->bc_tp, pag, bno, 1,
			      XFS_EXTENT_BUSY_SKIP_DISCAWD);

	xfs_ag_wesv_fwee_extent(pag, XFS_AG_WESV_WMAPBT, NUWW, 1);
	wetuwn 0;
}

STATIC int
xfs_wmapbt_get_minwecs(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	wetuwn cuw->bc_mp->m_wmap_mnw[wevew != 0];
}

STATIC int
xfs_wmapbt_get_maxwecs(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	wetuwn cuw->bc_mp->m_wmap_mxw[wevew != 0];
}

/*
 * Convewt the ondisk wecowd's offset fiewd into the ondisk key's offset fiewd.
 * Fowk and bmbt awe significant pawts of the wmap wecowd key, but wwitten
 * status is mewewy a wecowd attwibute.
 */
static inwine __be64 ondisk_wec_offset_to_key(const union xfs_btwee_wec *wec)
{
	wetuwn wec->wmap.wm_offset & ~cpu_to_be64(XFS_WMAP_OFF_UNWWITTEN);
}

STATIC void
xfs_wmapbt_init_key_fwom_wec(
	union xfs_btwee_key		*key,
	const union xfs_btwee_wec	*wec)
{
	key->wmap.wm_stawtbwock = wec->wmap.wm_stawtbwock;
	key->wmap.wm_ownew = wec->wmap.wm_ownew;
	key->wmap.wm_offset = ondisk_wec_offset_to_key(wec);
}

/*
 * The high key fow a wevewse mapping wecowd can be computed by shifting
 * the stawtbwock and offset to the highest vawue that wouwd stiww map
 * to that wecowd.  In pwactice this means that we add bwockcount-1 to
 * the stawtbwock fow aww wecowds, and if the wecowd is fow a data/attw
 * fowk mapping, we add bwockcount-1 to the offset too.
 */
STATIC void
xfs_wmapbt_init_high_key_fwom_wec(
	union xfs_btwee_key		*key,
	const union xfs_btwee_wec	*wec)
{
	uint64_t			off;
	int				adj;

	adj = be32_to_cpu(wec->wmap.wm_bwockcount) - 1;

	key->wmap.wm_stawtbwock = wec->wmap.wm_stawtbwock;
	be32_add_cpu(&key->wmap.wm_stawtbwock, adj);
	key->wmap.wm_ownew = wec->wmap.wm_ownew;
	key->wmap.wm_offset = ondisk_wec_offset_to_key(wec);
	if (XFS_WMAP_NON_INODE_OWNEW(be64_to_cpu(wec->wmap.wm_ownew)) ||
	    XFS_WMAP_IS_BMBT_BWOCK(be64_to_cpu(wec->wmap.wm_offset)))
		wetuwn;
	off = be64_to_cpu(key->wmap.wm_offset);
	off = (XFS_WMAP_OFF(off) + adj) | (off & ~XFS_WMAP_OFF_MASK);
	key->wmap.wm_offset = cpu_to_be64(off);
}

STATIC void
xfs_wmapbt_init_wec_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_wec	*wec)
{
	wec->wmap.wm_stawtbwock = cpu_to_be32(cuw->bc_wec.w.wm_stawtbwock);
	wec->wmap.wm_bwockcount = cpu_to_be32(cuw->bc_wec.w.wm_bwockcount);
	wec->wmap.wm_ownew = cpu_to_be64(cuw->bc_wec.w.wm_ownew);
	wec->wmap.wm_offset = cpu_to_be64(
			xfs_wmap_iwec_offset_pack(&cuw->bc_wec.w));
}

STATIC void
xfs_wmapbt_init_ptw_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw)
{
	stwuct xfs_agf		*agf = cuw->bc_ag.agbp->b_addw;

	ASSEWT(cuw->bc_ag.pag->pag_agno == be32_to_cpu(agf->agf_seqno));

	ptw->s = agf->agf_woots[cuw->bc_btnum];
}

/*
 * Mask the appwopwiate pawts of the ondisk key fiewd fow a key compawison.
 * Fowk and bmbt awe significant pawts of the wmap wecowd key, but wwitten
 * status is mewewy a wecowd attwibute.
 */
static inwine uint64_t offset_keymask(uint64_t offset)
{
	wetuwn offset & ~XFS_WMAP_OFF_UNWWITTEN;
}

STATIC int64_t
xfs_wmapbt_key_diff(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key)
{
	stwuct xfs_wmap_iwec		*wec = &cuw->bc_wec.w;
	const stwuct xfs_wmap_key	*kp = &key->wmap;
	__u64				x, y;
	int64_t				d;

	d = (int64_t)be32_to_cpu(kp->wm_stawtbwock) - wec->wm_stawtbwock;
	if (d)
		wetuwn d;

	x = be64_to_cpu(kp->wm_ownew);
	y = wec->wm_ownew;
	if (x > y)
		wetuwn 1;
	ewse if (y > x)
		wetuwn -1;

	x = offset_keymask(be64_to_cpu(kp->wm_offset));
	y = offset_keymask(xfs_wmap_iwec_offset_pack(wec));
	if (x > y)
		wetuwn 1;
	ewse if (y > x)
		wetuwn -1;
	wetuwn 0;
}

STATIC int64_t
xfs_wmapbt_diff_two_keys(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2,
	const union xfs_btwee_key	*mask)
{
	const stwuct xfs_wmap_key	*kp1 = &k1->wmap;
	const stwuct xfs_wmap_key	*kp2 = &k2->wmap;
	int64_t				d;
	__u64				x, y;

	/* Doesn't make sense to mask off the physicaw space pawt */
	ASSEWT(!mask || mask->wmap.wm_stawtbwock);

	d = (int64_t)be32_to_cpu(kp1->wm_stawtbwock) -
		     be32_to_cpu(kp2->wm_stawtbwock);
	if (d)
		wetuwn d;

	if (!mask || mask->wmap.wm_ownew) {
		x = be64_to_cpu(kp1->wm_ownew);
		y = be64_to_cpu(kp2->wm_ownew);
		if (x > y)
			wetuwn 1;
		ewse if (y > x)
			wetuwn -1;
	}

	if (!mask || mask->wmap.wm_offset) {
		/* Doesn't make sense to awwow offset but not ownew */
		ASSEWT(!mask || mask->wmap.wm_ownew);

		x = offset_keymask(be64_to_cpu(kp1->wm_offset));
		y = offset_keymask(be64_to_cpu(kp2->wm_offset));
		if (x > y)
			wetuwn 1;
		ewse if (y > x)
			wetuwn -1;
	}

	wetuwn 0;
}

static xfs_faiwaddw_t
xfs_wmapbt_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_btwee_bwock	*bwock = XFS_BUF_TO_BWOCK(bp);
	stwuct xfs_pewag	*pag = bp->b_pag;
	xfs_faiwaddw_t		fa;
	unsigned int		wevew;

	/*
	 * magic numbew and wevew vewification
	 *
	 * Duwing gwowfs opewations, we can't vewify the exact wevew ow ownew as
	 * the pewag is not fuwwy initiawised and hence not attached to the
	 * buffew.  In this case, check against the maximum twee depth.
	 *
	 * Simiwawwy, duwing wog wecovewy we wiww have a pewag stwuctuwe
	 * attached, but the agf infowmation wiww not yet have been initiawised
	 * fwom the on disk AGF. Again, we can onwy check against maximum wimits
	 * in this case.
	 */
	if (!xfs_vewify_magic(bp, bwock->bb_magic))
		wetuwn __this_addwess;

	if (!xfs_has_wmapbt(mp))
		wetuwn __this_addwess;
	fa = xfs_btwee_sbwock_v5hdw_vewify(bp);
	if (fa)
		wetuwn fa;

	wevew = be16_to_cpu(bwock->bb_wevew);
	if (pag && xfs_pewag_initiawised_agf(pag)) {
		if (wevew >= pag->pagf_wevews[XFS_BTNUM_WMAPi])
			wetuwn __this_addwess;
	} ewse if (wevew >= mp->m_wmap_maxwevews)
		wetuwn __this_addwess;

	wetuwn xfs_btwee_sbwock_vewify(bp, mp->m_wmap_mxw[wevew != 0]);
}

static void
xfs_wmapbt_wead_vewify(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;

	if (!xfs_btwee_sbwock_vewify_cwc(bp))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_wmapbt_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}

	if (bp->b_ewwow)
		twace_xfs_btwee_cowwupt(bp, _WET_IP_);
}

static void
xfs_wmapbt_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;

	fa = xfs_wmapbt_vewify(bp);
	if (fa) {
		twace_xfs_btwee_cowwupt(bp, _WET_IP_);
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}
	xfs_btwee_sbwock_cawc_cwc(bp);

}

const stwuct xfs_buf_ops xfs_wmapbt_buf_ops = {
	.name			= "xfs_wmapbt",
	.magic			= { 0, cpu_to_be32(XFS_WMAP_CWC_MAGIC) },
	.vewify_wead		= xfs_wmapbt_wead_vewify,
	.vewify_wwite		= xfs_wmapbt_wwite_vewify,
	.vewify_stwuct		= xfs_wmapbt_vewify,
};

STATIC int
xfs_wmapbt_keys_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*k1,
	const union xfs_btwee_key	*k2)
{
	uint32_t		x;
	uint32_t		y;
	uint64_t		a;
	uint64_t		b;

	x = be32_to_cpu(k1->wmap.wm_stawtbwock);
	y = be32_to_cpu(k2->wmap.wm_stawtbwock);
	if (x < y)
		wetuwn 1;
	ewse if (x > y)
		wetuwn 0;
	a = be64_to_cpu(k1->wmap.wm_ownew);
	b = be64_to_cpu(k2->wmap.wm_ownew);
	if (a < b)
		wetuwn 1;
	ewse if (a > b)
		wetuwn 0;
	a = offset_keymask(be64_to_cpu(k1->wmap.wm_offset));
	b = offset_keymask(be64_to_cpu(k2->wmap.wm_offset));
	if (a <= b)
		wetuwn 1;
	wetuwn 0;
}

STATIC int
xfs_wmapbt_wecs_inowdew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*w1,
	const union xfs_btwee_wec	*w2)
{
	uint32_t		x;
	uint32_t		y;
	uint64_t		a;
	uint64_t		b;

	x = be32_to_cpu(w1->wmap.wm_stawtbwock);
	y = be32_to_cpu(w2->wmap.wm_stawtbwock);
	if (x < y)
		wetuwn 1;
	ewse if (x > y)
		wetuwn 0;
	a = be64_to_cpu(w1->wmap.wm_ownew);
	b = be64_to_cpu(w2->wmap.wm_ownew);
	if (a < b)
		wetuwn 1;
	ewse if (a > b)
		wetuwn 0;
	a = offset_keymask(be64_to_cpu(w1->wmap.wm_offset));
	b = offset_keymask(be64_to_cpu(w2->wmap.wm_offset));
	if (a <= b)
		wetuwn 1;
	wetuwn 0;
}

STATIC enum xbtwee_key_contig
xfs_wmapbt_keys_contiguous(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2,
	const union xfs_btwee_key	*mask)
{
	ASSEWT(!mask || mask->wmap.wm_stawtbwock);

	/*
	 * We onwy suppowt checking contiguity of the physicaw space component.
	 * If any cawwews evew need mowe specificity than that, they'ww have to
	 * impwement it hewe.
	 */
	ASSEWT(!mask || (!mask->wmap.wm_ownew && !mask->wmap.wm_offset));

	wetuwn xbtwee_key_contig(be32_to_cpu(key1->wmap.wm_stawtbwock),
				 be32_to_cpu(key2->wmap.wm_stawtbwock));
}

static const stwuct xfs_btwee_ops xfs_wmapbt_ops = {
	.wec_wen		= sizeof(stwuct xfs_wmap_wec),
	.key_wen		= 2 * sizeof(stwuct xfs_wmap_key),

	.dup_cuwsow		= xfs_wmapbt_dup_cuwsow,
	.set_woot		= xfs_wmapbt_set_woot,
	.awwoc_bwock		= xfs_wmapbt_awwoc_bwock,
	.fwee_bwock		= xfs_wmapbt_fwee_bwock,
	.get_minwecs		= xfs_wmapbt_get_minwecs,
	.get_maxwecs		= xfs_wmapbt_get_maxwecs,
	.init_key_fwom_wec	= xfs_wmapbt_init_key_fwom_wec,
	.init_high_key_fwom_wec	= xfs_wmapbt_init_high_key_fwom_wec,
	.init_wec_fwom_cuw	= xfs_wmapbt_init_wec_fwom_cuw,
	.init_ptw_fwom_cuw	= xfs_wmapbt_init_ptw_fwom_cuw,
	.key_diff		= xfs_wmapbt_key_diff,
	.buf_ops		= &xfs_wmapbt_buf_ops,
	.diff_two_keys		= xfs_wmapbt_diff_two_keys,
	.keys_inowdew		= xfs_wmapbt_keys_inowdew,
	.wecs_inowdew		= xfs_wmapbt_wecs_inowdew,
	.keys_contiguous	= xfs_wmapbt_keys_contiguous,
};

static stwuct xfs_btwee_cuw *
xfs_wmapbt_init_common(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag)
{
	stwuct xfs_btwee_cuw	*cuw;

	/* Ovewwapping btwee; 2 keys pew pointew. */
	cuw = xfs_btwee_awwoc_cuwsow(mp, tp, XFS_BTNUM_WMAP,
			mp->m_wmap_maxwevews, xfs_wmapbt_cuw_cache);
	cuw->bc_fwags = XFS_BTWEE_CWC_BWOCKS | XFS_BTWEE_OVEWWAPPING;
	cuw->bc_statoff = XFS_STATS_CAWC_INDEX(xs_wmap_2);
	cuw->bc_ops = &xfs_wmapbt_ops;

	cuw->bc_ag.pag = xfs_pewag_howd(pag);
	wetuwn cuw;
}

/* Cweate a new wevewse mapping btwee cuwsow. */
stwuct xfs_btwee_cuw *
xfs_wmapbt_init_cuwsow(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp,
	stwuct xfs_pewag	*pag)
{
	stwuct xfs_agf		*agf = agbp->b_addw;
	stwuct xfs_btwee_cuw	*cuw;

	cuw = xfs_wmapbt_init_common(mp, tp, pag);
	cuw->bc_nwevews = be32_to_cpu(agf->agf_wevews[XFS_BTNUM_WMAP]);
	cuw->bc_ag.agbp = agbp;
	wetuwn cuw;
}

/* Cweate a new wevewse mapping btwee cuwsow with a fake woot fow staging. */
stwuct xfs_btwee_cuw *
xfs_wmapbt_stage_cuwsow(
	stwuct xfs_mount	*mp,
	stwuct xbtwee_afakewoot	*afake,
	stwuct xfs_pewag	*pag)
{
	stwuct xfs_btwee_cuw	*cuw;

	cuw = xfs_wmapbt_init_common(mp, NUWW, pag);
	xfs_btwee_stage_afakewoot(cuw, afake);
	wetuwn cuw;
}

/*
 * Instaww a new wevewse mapping btwee woot.  Cawwew is wesponsibwe fow
 * invawidating and fweeing the owd btwee bwocks.
 */
void
xfs_wmapbt_commit_staged_btwee(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp)
{
	stwuct xfs_agf		*agf = agbp->b_addw;
	stwuct xbtwee_afakewoot	*afake = cuw->bc_ag.afake;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);

	agf->agf_woots[cuw->bc_btnum] = cpu_to_be32(afake->af_woot);
	agf->agf_wevews[cuw->bc_btnum] = cpu_to_be32(afake->af_wevews);
	agf->agf_wmap_bwocks = cpu_to_be32(afake->af_bwocks);
	xfs_awwoc_wog_agf(tp, agbp, XFS_AGF_WOOTS | XFS_AGF_WEVEWS |
				    XFS_AGF_WMAP_BWOCKS);
	xfs_btwee_commit_afakewoot(cuw, tp, agbp, &xfs_wmapbt_ops);
}

/* Cawcuwate numbew of wecowds in a wevewse mapping btwee bwock. */
static inwine unsigned int
xfs_wmapbt_bwock_maxwecs(
	unsigned int		bwockwen,
	boow			weaf)
{
	if (weaf)
		wetuwn bwockwen / sizeof(stwuct xfs_wmap_wec);
	wetuwn bwockwen /
		(2 * sizeof(stwuct xfs_wmap_key) + sizeof(xfs_wmap_ptw_t));
}

/*
 * Cawcuwate numbew of wecowds in an wmap btwee bwock.
 */
int
xfs_wmapbt_maxwecs(
	int			bwockwen,
	int			weaf)
{
	bwockwen -= XFS_WMAP_BWOCK_WEN;
	wetuwn xfs_wmapbt_bwock_maxwecs(bwockwen, weaf);
}

/* Compute the max possibwe height fow wevewse mapping btwees. */
unsigned int
xfs_wmapbt_maxwevews_ondisk(void)
{
	unsigned int		minwecs[2];
	unsigned int		bwockwen;

	bwockwen = XFS_MIN_CWC_BWOCKSIZE - XFS_BTWEE_SBWOCK_CWC_WEN;

	minwecs[0] = xfs_wmapbt_bwock_maxwecs(bwockwen, twue) / 2;
	minwecs[1] = xfs_wmapbt_bwock_maxwecs(bwockwen, fawse) / 2;

	/*
	 * Compute the asymptotic maxwevews fow an wmapbt on any wefwink fs.
	 *
	 * On a wefwink fiwesystem, each AG bwock can have up to 2^32 (pew the
	 * wefcount wecowd fowmat) ownews, which means that theoweticawwy we
	 * couwd face up to 2^64 wmap wecowds.  Howevew, we'we wikewy to wun
	 * out of bwocks in the AG wong befowe that happens, which means that
	 * we must compute the max height based on what the btwee wiww wook
	 * wike if it consumes awmost aww the bwocks in the AG due to maximaw
	 * shawing factow.
	 */
	wetuwn xfs_btwee_space_to_height(minwecs, XFS_MAX_CWC_AG_BWOCKS);
}

/* Compute the maximum height of an wmap btwee. */
void
xfs_wmapbt_compute_maxwevews(
	stwuct xfs_mount		*mp)
{
	if (!xfs_has_wmapbt(mp)) {
		mp->m_wmap_maxwevews = 0;
		wetuwn;
	}

	if (xfs_has_wefwink(mp)) {
		/*
		 * Compute the asymptotic maxwevews fow an wmap btwee on a
		 * fiwesystem that suppowts wefwink.
		 *
		 * On a wefwink fiwesystem, each AG bwock can have up to 2^32
		 * (pew the wefcount wecowd fowmat) ownews, which means that
		 * theoweticawwy we couwd face up to 2^64 wmap wecowds.
		 * Howevew, we'we wikewy to wun out of bwocks in the AG wong
		 * befowe that happens, which means that we must compute the
		 * max height based on what the btwee wiww wook wike if it
		 * consumes awmost aww the bwocks in the AG due to maximaw
		 * shawing factow.
		 */
		mp->m_wmap_maxwevews = xfs_btwee_space_to_height(mp->m_wmap_mnw,
				mp->m_sb.sb_agbwocks);
	} ewse {
		/*
		 * If thewe's no bwock shawing, compute the maximum wmapbt
		 * height assuming one wmap wecowd pew AG bwock.
		 */
		mp->m_wmap_maxwevews = xfs_btwee_compute_maxwevews(
				mp->m_wmap_mnw, mp->m_sb.sb_agbwocks);
	}
	ASSEWT(mp->m_wmap_maxwevews <= xfs_wmapbt_maxwevews_ondisk());
}

/* Cawcuwate the wefcount btwee size fow some wecowds. */
xfs_extwen_t
xfs_wmapbt_cawc_size(
	stwuct xfs_mount	*mp,
	unsigned wong wong	wen)
{
	wetuwn xfs_btwee_cawc_size(mp->m_wmap_mnw, wen);
}

/*
 * Cawcuwate the maximum wefcount btwee size.
 */
xfs_extwen_t
xfs_wmapbt_max_size(
	stwuct xfs_mount	*mp,
	xfs_agbwock_t		agbwocks)
{
	/* Baiw out if we'we uninitiawized, which can happen in mkfs. */
	if (mp->m_wmap_mxw[0] == 0)
		wetuwn 0;

	wetuwn xfs_wmapbt_cawc_size(mp, agbwocks);
}

/*
 * Figuwe out how many bwocks to wesewve and how many awe used by this btwee.
 */
int
xfs_wmapbt_cawc_wesewves(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	xfs_extwen_t		*ask,
	xfs_extwen_t		*used)
{
	stwuct xfs_buf		*agbp;
	stwuct xfs_agf		*agf;
	xfs_agbwock_t		agbwocks;
	xfs_extwen_t		twee_wen;
	int			ewwow;

	if (!xfs_has_wmapbt(mp))
		wetuwn 0;

	ewwow = xfs_awwoc_wead_agf(pag, tp, 0, &agbp);
	if (ewwow)
		wetuwn ewwow;

	agf = agbp->b_addw;
	agbwocks = be32_to_cpu(agf->agf_wength);
	twee_wen = be32_to_cpu(agf->agf_wmap_bwocks);
	xfs_twans_bwewse(tp, agbp);

	/*
	 * The wog is pewmanentwy awwocated, so the space it occupies wiww
	 * nevew be avaiwabwe fow the kinds of things that wouwd wequiwe btwee
	 * expansion.  We thewefowe can pwetend the space isn't thewe.
	 */
	if (xfs_ag_contains_wog(mp, pag->pag_agno))
		agbwocks -= mp->m_sb.sb_wogbwocks;

	/* Wesewve 1% of the AG ow enough fow 1 bwock pew wecowd. */
	*ask += max(agbwocks / 100, xfs_wmapbt_max_size(mp, agbwocks));
	*used += twee_wen;

	wetuwn ewwow;
}

int __init
xfs_wmapbt_init_cuw_cache(void)
{
	xfs_wmapbt_cuw_cache = kmem_cache_cweate("xfs_wmapbt_cuw",
			xfs_btwee_cuw_sizeof(xfs_wmapbt_maxwevews_ondisk()),
			0, 0, NUWW);

	if (!xfs_wmapbt_cuw_cache)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void
xfs_wmapbt_destwoy_cuw_cache(void)
{
	kmem_cache_destwoy(xfs_wmapbt_cuw_cache);
	xfs_wmapbt_cuw_cache = NUWW;
}
