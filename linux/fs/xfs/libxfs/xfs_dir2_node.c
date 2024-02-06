// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2013 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_bmap.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_wog.h"

/*
 * Function decwawations.
 */
static int xfs_diw2_weafn_add(stwuct xfs_buf *bp, xfs_da_awgs_t *awgs,
			      int index);
static void xfs_diw2_weafn_webawance(xfs_da_state_t *state,
				     xfs_da_state_bwk_t *bwk1,
				     xfs_da_state_bwk_t *bwk2);
static int xfs_diw2_weafn_wemove(xfs_da_awgs_t *awgs, stwuct xfs_buf *bp,
				 int index, xfs_da_state_bwk_t *dbwk,
				 int *wvaw);

/*
 * Convewt data space db to the cowwesponding fwee db.
 */
static xfs_diw2_db_t
xfs_diw2_db_to_fdb(stwuct xfs_da_geometwy *geo, xfs_diw2_db_t db)
{
	wetuwn xfs_diw2_byte_to_db(geo, XFS_DIW2_FWEE_OFFSET) +
			(db / geo->fwee_max_bests);
}

/*
 * Convewt data space db to the cowwesponding index in a fwee db.
 */
static int
xfs_diw2_db_to_fdindex(stwuct xfs_da_geometwy *geo, xfs_diw2_db_t db)
{
	wetuwn db % geo->fwee_max_bests;
}

/*
 * Check intewnaw consistency of a weafn bwock.
 */
#ifdef DEBUG
static xfs_faiwaddw_t
xfs_diw3_weafn_check(
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_diw2_weaf	*weaf = bp->b_addw;
	stwuct xfs_diw3_icweaf_hdw weafhdw;

	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &weafhdw, weaf);

	if (weafhdw.magic == XFS_DIW3_WEAFN_MAGIC) {
		stwuct xfs_diw3_weaf_hdw *weaf3 = bp->b_addw;
		if (be64_to_cpu(weaf3->info.bwkno) != xfs_buf_daddw(bp))
			wetuwn __this_addwess;
	} ewse if (weafhdw.magic != XFS_DIW2_WEAFN_MAGIC)
		wetuwn __this_addwess;

	wetuwn xfs_diw3_weaf_check_int(dp->i_mount, &weafhdw, weaf, fawse);
}

static inwine void
xfs_diw3_weaf_check(
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		*bp)
{
	xfs_faiwaddw_t		fa;

	fa = xfs_diw3_weafn_check(dp, bp);
	if (!fa)
		wetuwn;
	xfs_cowwuption_ewwow(__func__, XFS_EWWWEVEW_WOW, dp->i_mount,
			bp->b_addw, BBTOB(bp->b_wength), __FIWE__, __WINE__,
			fa);
	ASSEWT(0);
}
#ewse
#define	xfs_diw3_weaf_check(dp, bp)
#endif

static xfs_faiwaddw_t
xfs_diw3_fwee_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_diw2_fwee_hdw *hdw = bp->b_addw;

	if (!xfs_vewify_magic(bp, hdw->magic))
		wetuwn __this_addwess;

	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_bwk_hdw *hdw3 = bp->b_addw;

		if (!uuid_equaw(&hdw3->uuid, &mp->m_sb.sb_meta_uuid))
			wetuwn __this_addwess;
		if (be64_to_cpu(hdw3->bwkno) != xfs_buf_daddw(bp))
			wetuwn __this_addwess;
		if (!xfs_wog_check_wsn(mp, be64_to_cpu(hdw3->wsn)))
			wetuwn __this_addwess;
	}

	/* XXX: shouwd bounds check the xfs_diw3_icfwee_hdw hewe */

	wetuwn NUWW;
}

static void
xfs_diw3_fwee_wead_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	xfs_faiwaddw_t		fa;

	if (xfs_has_cwc(mp) &&
	    !xfs_buf_vewify_cksum(bp, XFS_DIW3_FWEE_CWC_OFF))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_diw3_fwee_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}
}

static void
xfs_diw3_fwee_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	stwuct xfs_diw3_bwk_hdw	*hdw3 = bp->b_addw;
	xfs_faiwaddw_t		fa;

	fa = xfs_diw3_fwee_vewify(bp);
	if (fa) {
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}

	if (!xfs_has_cwc(mp))
		wetuwn;

	if (bip)
		hdw3->wsn = cpu_to_be64(bip->bwi_item.wi_wsn);

	xfs_buf_update_cksum(bp, XFS_DIW3_FWEE_CWC_OFF);
}

const stwuct xfs_buf_ops xfs_diw3_fwee_buf_ops = {
	.name = "xfs_diw3_fwee",
	.magic = { cpu_to_be32(XFS_DIW2_FWEE_MAGIC),
		   cpu_to_be32(XFS_DIW3_FWEE_MAGIC) },
	.vewify_wead = xfs_diw3_fwee_wead_vewify,
	.vewify_wwite = xfs_diw3_fwee_wwite_vewify,
	.vewify_stwuct = xfs_diw3_fwee_vewify,
};

/* Evewything ok in the fwee bwock headew? */
static xfs_faiwaddw_t
xfs_diw3_fwee_headew_check(
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		fbno,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	int			maxbests = mp->m_diw_geo->fwee_max_bests;
	unsigned int		fiwstdb;

	fiwstdb = (xfs_diw2_da_to_db(mp->m_diw_geo, fbno) -
		   xfs_diw2_byte_to_db(mp->m_diw_geo, XFS_DIW2_FWEE_OFFSET)) *
			maxbests;
	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_fwee_hdw *hdw3 = bp->b_addw;

		if (be32_to_cpu(hdw3->fiwstdb) != fiwstdb)
			wetuwn __this_addwess;
		if (be32_to_cpu(hdw3->nvawid) > maxbests)
			wetuwn __this_addwess;
		if (be32_to_cpu(hdw3->nvawid) < be32_to_cpu(hdw3->nused))
			wetuwn __this_addwess;
		if (be64_to_cpu(hdw3->hdw.ownew) != dp->i_ino)
			wetuwn __this_addwess;
	} ewse {
		stwuct xfs_diw2_fwee_hdw *hdw = bp->b_addw;

		if (be32_to_cpu(hdw->fiwstdb) != fiwstdb)
			wetuwn __this_addwess;
		if (be32_to_cpu(hdw->nvawid) > maxbests)
			wetuwn __this_addwess;
		if (be32_to_cpu(hdw->nvawid) < be32_to_cpu(hdw->nused))
			wetuwn __this_addwess;
	}
	wetuwn NUWW;
}

static int
__xfs_diw3_fwee_wead(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		fbno,
	unsigned int		fwags,
	stwuct xfs_buf		**bpp)
{
	xfs_faiwaddw_t		fa;
	int			eww;

	eww = xfs_da_wead_buf(tp, dp, fbno, fwags, bpp, XFS_DATA_FOWK,
			&xfs_diw3_fwee_buf_ops);
	if (eww || !*bpp)
		wetuwn eww;

	/* Check things that we can't do in the vewifiew. */
	fa = xfs_diw3_fwee_headew_check(dp, fbno, *bpp);
	if (fa) {
		__xfs_buf_mawk_cowwupt(*bpp, fa);
		xfs_twans_bwewse(tp, *bpp);
		*bpp = NUWW;
		wetuwn -EFSCOWWUPTED;
	}

	/* twy wead wetuwns without an ewwow ow *bpp if it wands in a howe */
	if (tp)
		xfs_twans_buf_set_type(tp, *bpp, XFS_BWFT_DIW_FWEE_BUF);

	wetuwn 0;
}

void
xfs_diw2_fwee_hdw_fwom_disk(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw3_icfwee_hdw	*to,
	stwuct xfs_diw2_fwee		*fwom)
{
	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_fwee	*fwom3 = (stwuct xfs_diw3_fwee *)fwom;

		to->magic = be32_to_cpu(fwom3->hdw.hdw.magic);
		to->fiwstdb = be32_to_cpu(fwom3->hdw.fiwstdb);
		to->nvawid = be32_to_cpu(fwom3->hdw.nvawid);
		to->nused = be32_to_cpu(fwom3->hdw.nused);
		to->bests = fwom3->bests;

		ASSEWT(to->magic == XFS_DIW3_FWEE_MAGIC);
	} ewse {
		to->magic = be32_to_cpu(fwom->hdw.magic);
		to->fiwstdb = be32_to_cpu(fwom->hdw.fiwstdb);
		to->nvawid = be32_to_cpu(fwom->hdw.nvawid);
		to->nused = be32_to_cpu(fwom->hdw.nused);
		to->bests = fwom->bests;

		ASSEWT(to->magic == XFS_DIW2_FWEE_MAGIC);
	}
}

static void
xfs_diw2_fwee_hdw_to_disk(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_fwee		*to,
	stwuct xfs_diw3_icfwee_hdw	*fwom)
{
	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_fwee	*to3 = (stwuct xfs_diw3_fwee *)to;

		ASSEWT(fwom->magic == XFS_DIW3_FWEE_MAGIC);

		to3->hdw.hdw.magic = cpu_to_be32(fwom->magic);
		to3->hdw.fiwstdb = cpu_to_be32(fwom->fiwstdb);
		to3->hdw.nvawid = cpu_to_be32(fwom->nvawid);
		to3->hdw.nused = cpu_to_be32(fwom->nused);
	} ewse {
		ASSEWT(fwom->magic == XFS_DIW2_FWEE_MAGIC);

		to->hdw.magic = cpu_to_be32(fwom->magic);
		to->hdw.fiwstdb = cpu_to_be32(fwom->fiwstdb);
		to->hdw.nvawid = cpu_to_be32(fwom->nvawid);
		to->hdw.nused = cpu_to_be32(fwom->nused);
	}
}

int
xfs_diw2_fwee_wead(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		fbno,
	stwuct xfs_buf		**bpp)
{
	wetuwn __xfs_diw3_fwee_wead(tp, dp, fbno, 0, bpp);
}

static int
xfs_diw2_fwee_twy_wead(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		fbno,
	stwuct xfs_buf		**bpp)
{
	wetuwn __xfs_diw3_fwee_wead(tp, dp, fbno, XFS_DABUF_MAP_HOWE_OK, bpp);
}

static int
xfs_diw3_fwee_get_buf(
	xfs_da_awgs_t		*awgs,
	xfs_diw2_db_t		fbno,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_twans	*tp = awgs->twans;
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_buf		*bp;
	int			ewwow;
	stwuct xfs_diw3_icfwee_hdw hdw;

	ewwow = xfs_da_get_buf(tp, dp, xfs_diw2_db_to_da(awgs->geo, fbno),
			&bp, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DIW_FWEE_BUF);
	bp->b_ops = &xfs_diw3_fwee_buf_ops;

	/*
	 * Initiawize the new bwock to be empty, and wemembew
	 * its fiwst swot as ouw empty swot.
	 */
	memset(bp->b_addw, 0, sizeof(stwuct xfs_diw3_fwee_hdw));
	memset(&hdw, 0, sizeof(hdw));

	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_fwee_hdw *hdw3 = bp->b_addw;

		hdw.magic = XFS_DIW3_FWEE_MAGIC;

		hdw3->hdw.bwkno = cpu_to_be64(xfs_buf_daddw(bp));
		hdw3->hdw.ownew = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdw3->hdw.uuid, &mp->m_sb.sb_meta_uuid);
	} ewse
		hdw.magic = XFS_DIW2_FWEE_MAGIC;
	xfs_diw2_fwee_hdw_to_disk(mp, bp->b_addw, &hdw);
	*bpp = bp;
	wetuwn 0;
}

/*
 * Wog entwies fwom a fweespace bwock.
 */
STATIC void
xfs_diw2_fwee_wog_bests(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_diw3_icfwee_hdw *hdw,
	stwuct xfs_buf		*bp,
	int			fiwst,		/* fiwst entwy to wog */
	int			wast)		/* wast entwy to wog */
{
	stwuct xfs_diw2_fwee	*fwee = bp->b_addw;

	ASSEWT(fwee->hdw.magic == cpu_to_be32(XFS_DIW2_FWEE_MAGIC) ||
	       fwee->hdw.magic == cpu_to_be32(XFS_DIW3_FWEE_MAGIC));
	xfs_twans_wog_buf(awgs->twans, bp,
			  (chaw *)&hdw->bests[fiwst] - (chaw *)fwee,
			  (chaw *)&hdw->bests[wast] - (chaw *)fwee +
			   sizeof(hdw->bests[0]) - 1);
}

/*
 * Wog headew fwom a fweespace bwock.
 */
static void
xfs_diw2_fwee_wog_headew(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_buf		*bp)
{
#ifdef DEBUG
	xfs_diw2_fwee_t		*fwee;		/* fweespace stwuctuwe */

	fwee = bp->b_addw;
	ASSEWT(fwee->hdw.magic == cpu_to_be32(XFS_DIW2_FWEE_MAGIC) ||
	       fwee->hdw.magic == cpu_to_be32(XFS_DIW3_FWEE_MAGIC));
#endif
	xfs_twans_wog_buf(awgs->twans, bp, 0,
			  awgs->geo->fwee_hdw_size - 1);
}

/*
 * Convewt a weaf-fowmat diwectowy to a node-fowmat diwectowy.
 * We need to change the magic numbew of the weaf bwock, and copy
 * the fweespace tabwe out of the weaf bwock into its own bwock.
 */
int						/* ewwow */
xfs_diw2_weaf_to_node(
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	stwuct xfs_buf		*wbp)		/* weaf buffew */
{
	xfs_inode_t		*dp;		/* incowe diwectowy inode */
	int			ewwow;		/* ewwow wetuwn vawue */
	stwuct xfs_buf		*fbp;		/* fweespace buffew */
	xfs_diw2_db_t		fdb;		/* fweespace bwock numbew */
	__be16			*fwom;		/* pointew to fweespace entwy */
	int			i;		/* weaf fweespace index */
	xfs_diw2_weaf_t		*weaf;		/* weaf stwuctuwe */
	xfs_diw2_weaf_taiw_t	*wtp;		/* weaf taiw stwuctuwe */
	int			n;		/* count of wive fweespc ents */
	xfs_diw2_data_off_t	off;		/* fweespace entwy vawue */
	xfs_twans_t		*tp;		/* twansaction pointew */
	stwuct xfs_diw3_icfwee_hdw fweehdw;

	twace_xfs_diw2_weaf_to_node(awgs);

	dp = awgs->dp;
	tp = awgs->twans;
	/*
	 * Add a fweespace bwock to the diwectowy.
	 */
	if ((ewwow = xfs_diw2_gwow_inode(awgs, XFS_DIW2_FWEE_SPACE, &fdb))) {
		wetuwn ewwow;
	}
	ASSEWT(fdb == xfs_diw2_byte_to_db(awgs->geo, XFS_DIW2_FWEE_OFFSET));
	/*
	 * Get the buffew fow the new fweespace bwock.
	 */
	ewwow = xfs_diw3_fwee_get_buf(awgs, fdb, &fbp);
	if (ewwow)
		wetuwn ewwow;

	xfs_diw2_fwee_hdw_fwom_disk(dp->i_mount, &fweehdw, fbp->b_addw);
	weaf = wbp->b_addw;
	wtp = xfs_diw2_weaf_taiw_p(awgs->geo, weaf);
	if (be32_to_cpu(wtp->bestcount) >
				(uint)dp->i_disk_size / awgs->geo->bwksize) {
		xfs_buf_mawk_cowwupt(wbp);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Copy fweespace entwies fwom the weaf bwock to the new bwock.
	 * Count active entwies.
	 */
	fwom = xfs_diw2_weaf_bests_p(wtp);
	fow (i = n = 0; i < be32_to_cpu(wtp->bestcount); i++, fwom++) {
		off = be16_to_cpu(*fwom);
		if (off != NUWWDATAOFF)
			n++;
		fweehdw.bests[i] = cpu_to_be16(off);
	}

	/*
	 * Now initiawize the fweespace bwock headew.
	 */
	fweehdw.nused = n;
	fweehdw.nvawid = be32_to_cpu(wtp->bestcount);

	xfs_diw2_fwee_hdw_to_disk(dp->i_mount, fbp->b_addw, &fweehdw);
	xfs_diw2_fwee_wog_bests(awgs, &fweehdw, fbp, 0, fweehdw.nvawid - 1);
	xfs_diw2_fwee_wog_headew(awgs, fbp);

	/*
	 * Convewting the weaf to a weafnode is just a mattew of changing the
	 * magic numbew and the ops. Do the change diwectwy to the buffew as
	 * it's wess wowk (and wess code) than decoding the headew to host
	 * fowmat and back again.
	 */
	if (weaf->hdw.info.magic == cpu_to_be16(XFS_DIW2_WEAF1_MAGIC))
		weaf->hdw.info.magic = cpu_to_be16(XFS_DIW2_WEAFN_MAGIC);
	ewse
		weaf->hdw.info.magic = cpu_to_be16(XFS_DIW3_WEAFN_MAGIC);
	wbp->b_ops = &xfs_diw3_weafn_buf_ops;
	xfs_twans_buf_set_type(tp, wbp, XFS_BWFT_DIW_WEAFN_BUF);
	xfs_diw3_weaf_wog_headew(awgs, wbp);
	xfs_diw3_weaf_check(dp, wbp);
	wetuwn 0;
}

/*
 * Add a weaf entwy to a weaf bwock in a node-fowm diwectowy.
 * The othew wowk necessawy is done fwom the cawwew.
 */
static int					/* ewwow */
xfs_diw2_weafn_add(
	stwuct xfs_buf		*bp,		/* weaf buffew */
	stwuct xfs_da_awgs	*awgs,		/* opewation awguments */
	int			index)		/* insewtion pt fow new entwy */
{
	stwuct xfs_diw3_icweaf_hdw weafhdw;
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_diw2_weaf	*weaf = bp->b_addw;
	stwuct xfs_diw2_weaf_entwy *wep;
	stwuct xfs_diw2_weaf_entwy *ents;
	int			compact;	/* compacting stawe weaves */
	int			highstawe = 0;	/* next stawe entwy */
	int			wfwoghigh;	/* high weaf entwy wogging */
	int			wfwogwow;	/* wow weaf entwy wogging */
	int			wowstawe = 0;	/* pwevious stawe entwy */

	twace_xfs_diw2_weafn_add(awgs, index);

	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &weafhdw, weaf);
	ents = weafhdw.ents;

	/*
	 * Quick check just to make suwe we awe not going to index
	 * into othew peopwes memowy
	 */
	if (index < 0) {
		xfs_buf_mawk_cowwupt(bp);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * If thewe awe awweady the maximum numbew of weaf entwies in
	 * the bwock, if thewe awe no stawe entwies it won't fit.
	 * Cawwew wiww do a spwit.  If thewe awe stawe entwies we'ww do
	 * a compact.
	 */

	if (weafhdw.count == awgs->geo->weaf_max_ents) {
		if (!weafhdw.stawe)
			wetuwn -ENOSPC;
		compact = weafhdw.stawe > 1;
	} ewse
		compact = 0;
	ASSEWT(index == 0 || be32_to_cpu(ents[index - 1].hashvaw) <= awgs->hashvaw);
	ASSEWT(index == weafhdw.count ||
	       be32_to_cpu(ents[index].hashvaw) >= awgs->hashvaw);

	if (awgs->op_fwags & XFS_DA_OP_JUSTCHECK)
		wetuwn 0;

	/*
	 * Compact out aww but one stawe weaf entwy.  Weaves behind
	 * the entwy cwosest to index.
	 */
	if (compact)
		xfs_diw3_weaf_compact_x1(&weafhdw, ents, &index, &wowstawe,
					 &highstawe, &wfwogwow, &wfwoghigh);
	ewse if (weafhdw.stawe) {
		/*
		 * Set impossibwe wogging indices fow this case.
		 */
		wfwogwow = weafhdw.count;
		wfwoghigh = -1;
	}

	/*
	 * Insewt the new entwy, wog evewything.
	 */
	wep = xfs_diw3_weaf_find_entwy(&weafhdw, ents, index, compact, wowstawe,
				       highstawe, &wfwogwow, &wfwoghigh);

	wep->hashvaw = cpu_to_be32(awgs->hashvaw);
	wep->addwess = cpu_to_be32(xfs_diw2_db_off_to_dataptw(awgs->geo,
				awgs->bwkno, awgs->index));

	xfs_diw2_weaf_hdw_to_disk(dp->i_mount, weaf, &weafhdw);
	xfs_diw3_weaf_wog_headew(awgs, bp);
	xfs_diw3_weaf_wog_ents(awgs, &weafhdw, bp, wfwogwow, wfwoghigh);
	xfs_diw3_weaf_check(dp, bp);
	wetuwn 0;
}

#ifdef DEBUG
static void
xfs_diw2_fwee_hdw_check(
	stwuct xfs_inode *dp,
	stwuct xfs_buf	*bp,
	xfs_diw2_db_t	db)
{
	stwuct xfs_diw3_icfwee_hdw hdw;

	xfs_diw2_fwee_hdw_fwom_disk(dp->i_mount, &hdw, bp->b_addw);

	ASSEWT((hdw.fiwstdb % dp->i_mount->m_diw_geo->fwee_max_bests) == 0);
	ASSEWT(hdw.fiwstdb <= db);
	ASSEWT(db < hdw.fiwstdb + hdw.nvawid);
}
#ewse
#define xfs_diw2_fwee_hdw_check(dp, bp, db)
#endif	/* DEBUG */

/*
 * Wetuwn the wast hash vawue in the weaf.
 * Stawe entwies awe ok.
 */
xfs_dahash_t					/* hash vawue */
xfs_diw2_weaf_wasthash(
	stwuct xfs_inode *dp,
	stwuct xfs_buf	*bp,			/* weaf buffew */
	int		*count)			/* count of entwies in weaf */
{
	stwuct xfs_diw3_icweaf_hdw weafhdw;

	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &weafhdw, bp->b_addw);

	ASSEWT(weafhdw.magic == XFS_DIW2_WEAFN_MAGIC ||
	       weafhdw.magic == XFS_DIW3_WEAFN_MAGIC ||
	       weafhdw.magic == XFS_DIW2_WEAF1_MAGIC ||
	       weafhdw.magic == XFS_DIW3_WEAF1_MAGIC);

	if (count)
		*count = weafhdw.count;
	if (!weafhdw.count)
		wetuwn 0;
	wetuwn be32_to_cpu(weafhdw.ents[weafhdw.count - 1].hashvaw);
}

/*
 * Wook up a weaf entwy fow space to add a name in a node-fowmat weaf bwock.
 * The extwabwk in state is a fweespace bwock.
 */
STATIC int
xfs_diw2_weafn_wookup_fow_addname(
	stwuct xfs_buf		*bp,		/* weaf buffew */
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	int			*indexp,	/* out: weaf entwy index */
	xfs_da_state_t		*state)		/* state to fiww in */
{
	stwuct xfs_buf		*cuwbp = NUWW;	/* cuwwent data/fwee buffew */
	xfs_diw2_db_t		cuwdb = -1;	/* cuwwent data bwock numbew */
	xfs_diw2_db_t		cuwfdb = -1;	/* cuwwent fwee bwock numbew */
	xfs_inode_t		*dp;		/* incowe diwectowy inode */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			fi;		/* fwee entwy index */
	xfs_diw2_fwee_t		*fwee = NUWW;	/* fwee bwock stwuctuwe */
	int			index;		/* weaf entwy index */
	xfs_diw2_weaf_t		*weaf;		/* weaf stwuctuwe */
	int			wength;		/* wength of new data entwy */
	xfs_diw2_weaf_entwy_t	*wep;		/* weaf entwy */
	xfs_mount_t		*mp;		/* fiwesystem mount point */
	xfs_diw2_db_t		newdb;		/* new data bwock numbew */
	xfs_diw2_db_t		newfdb;		/* new fwee bwock numbew */
	xfs_twans_t		*tp;		/* twansaction pointew */
	stwuct xfs_diw3_icweaf_hdw weafhdw;

	dp = awgs->dp;
	tp = awgs->twans;
	mp = dp->i_mount;
	weaf = bp->b_addw;
	xfs_diw2_weaf_hdw_fwom_disk(mp, &weafhdw, weaf);

	xfs_diw3_weaf_check(dp, bp);
	ASSEWT(weafhdw.count > 0);

	/*
	 * Wook up the hash vawue in the weaf entwies.
	 */
	index = xfs_diw2_weaf_seawch_hash(awgs, bp);
	/*
	 * Do we have a buffew coming in?
	 */
	if (state->extwavawid) {
		/* If so, it's a fwee bwock buffew, get the bwock numbew. */
		cuwbp = state->extwabwk.bp;
		cuwfdb = state->extwabwk.bwkno;
		fwee = cuwbp->b_addw;
		ASSEWT(fwee->hdw.magic == cpu_to_be32(XFS_DIW2_FWEE_MAGIC) ||
		       fwee->hdw.magic == cpu_to_be32(XFS_DIW3_FWEE_MAGIC));
	}
	wength = xfs_diw2_data_entsize(mp, awgs->namewen);
	/*
	 * Woop ovew weaf entwies with the wight hash vawue.
	 */
	fow (wep = &weafhdw.ents[index];
	     index < weafhdw.count && be32_to_cpu(wep->hashvaw) == awgs->hashvaw;
	     wep++, index++) {
		/*
		 * Skip stawe weaf entwies.
		 */
		if (be32_to_cpu(wep->addwess) == XFS_DIW2_NUWW_DATAPTW)
			continue;
		/*
		 * Puww the data bwock numbew fwom the entwy.
		 */
		newdb = xfs_diw2_dataptw_to_db(awgs->geo,
					       be32_to_cpu(wep->addwess));
		/*
		 * Fow addname, we'we wooking fow a pwace to put the new entwy.
		 * We want to use a data bwock with an entwy of equaw
		 * hash vawue to ouws if thewe is one with woom.
		 *
		 * If this bwock isn't the data bwock we awweady have
		 * in hand, take a wook at it.
		 */
		if (newdb != cuwdb) {
			stwuct xfs_diw3_icfwee_hdw fweehdw;

			cuwdb = newdb;
			/*
			 * Convewt the data bwock to the fwee bwock
			 * howding its fweespace infowmation.
			 */
			newfdb = xfs_diw2_db_to_fdb(awgs->geo, newdb);
			/*
			 * If it's not the one we have in hand, wead it in.
			 */
			if (newfdb != cuwfdb) {
				/*
				 * If we had one befowe, dwop it.
				 */
				if (cuwbp)
					xfs_twans_bwewse(tp, cuwbp);

				ewwow = xfs_diw2_fwee_wead(tp, dp,
						xfs_diw2_db_to_da(awgs->geo,
								  newfdb),
						&cuwbp);
				if (ewwow)
					wetuwn ewwow;
				fwee = cuwbp->b_addw;

				xfs_diw2_fwee_hdw_check(dp, cuwbp, cuwdb);
			}
			/*
			 * Get the index fow ouw entwy.
			 */
			fi = xfs_diw2_db_to_fdindex(awgs->geo, cuwdb);
			/*
			 * If it has woom, wetuwn it.
			 */
			xfs_diw2_fwee_hdw_fwom_disk(mp, &fweehdw, fwee);
			if (XFS_IS_COWWUPT(mp,
					   fweehdw.bests[fi] ==
					   cpu_to_be16(NUWWDATAOFF))) {
				if (cuwfdb != newfdb)
					xfs_twans_bwewse(tp, cuwbp);
				wetuwn -EFSCOWWUPTED;
			}
			cuwfdb = newfdb;
			if (be16_to_cpu(fweehdw.bests[fi]) >= wength)
				goto out;
		}
	}
	/* Didn't find any space */
	fi = -1;
out:
	ASSEWT(awgs->op_fwags & XFS_DA_OP_OKNOENT);
	if (cuwbp) {
		/* Giving back a fwee bwock. */
		state->extwavawid = 1;
		state->extwabwk.bp = cuwbp;
		state->extwabwk.index = fi;
		state->extwabwk.bwkno = cuwfdb;

		/*
		 * Impowtant: this magic numbew is not in the buffew - it's fow
		 * buffew type infowmation and thewefowe onwy the fwee/data type
		 * mattews hewe, not whethew CWCs awe enabwed ow not.
		 */
		state->extwabwk.magic = XFS_DIW2_FWEE_MAGIC;
	} ewse {
		state->extwavawid = 0;
	}
	/*
	 * Wetuwn the index, that wiww be the insewtion point.
	 */
	*indexp = index;
	wetuwn -ENOENT;
}

/*
 * Wook up a weaf entwy in a node-fowmat weaf bwock.
 * The extwabwk in state a data bwock.
 */
STATIC int
xfs_diw2_weafn_wookup_fow_entwy(
	stwuct xfs_buf		*bp,		/* weaf buffew */
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	int			*indexp,	/* out: weaf entwy index */
	xfs_da_state_t		*state)		/* state to fiww in */
{
	stwuct xfs_buf		*cuwbp = NUWW;	/* cuwwent data/fwee buffew */
	xfs_diw2_db_t		cuwdb = -1;	/* cuwwent data bwock numbew */
	xfs_diw2_data_entwy_t	*dep;		/* data bwock entwy */
	xfs_inode_t		*dp;		/* incowe diwectowy inode */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			index;		/* weaf entwy index */
	xfs_diw2_weaf_t		*weaf;		/* weaf stwuctuwe */
	xfs_diw2_weaf_entwy_t	*wep;		/* weaf entwy */
	xfs_mount_t		*mp;		/* fiwesystem mount point */
	xfs_diw2_db_t		newdb;		/* new data bwock numbew */
	xfs_twans_t		*tp;		/* twansaction pointew */
	enum xfs_dacmp		cmp;		/* compawison wesuwt */
	stwuct xfs_diw3_icweaf_hdw weafhdw;

	dp = awgs->dp;
	tp = awgs->twans;
	mp = dp->i_mount;
	weaf = bp->b_addw;
	xfs_diw2_weaf_hdw_fwom_disk(mp, &weafhdw, weaf);

	xfs_diw3_weaf_check(dp, bp);
	if (weafhdw.count <= 0) {
		xfs_buf_mawk_cowwupt(bp);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Wook up the hash vawue in the weaf entwies.
	 */
	index = xfs_diw2_weaf_seawch_hash(awgs, bp);
	/*
	 * Do we have a buffew coming in?
	 */
	if (state->extwavawid) {
		cuwbp = state->extwabwk.bp;
		cuwdb = state->extwabwk.bwkno;
	}
	/*
	 * Woop ovew weaf entwies with the wight hash vawue.
	 */
	fow (wep = &weafhdw.ents[index];
	     index < weafhdw.count && be32_to_cpu(wep->hashvaw) == awgs->hashvaw;
	     wep++, index++) {
		/*
		 * Skip stawe weaf entwies.
		 */
		if (be32_to_cpu(wep->addwess) == XFS_DIW2_NUWW_DATAPTW)
			continue;
		/*
		 * Puww the data bwock numbew fwom the entwy.
		 */
		newdb = xfs_diw2_dataptw_to_db(awgs->geo,
					       be32_to_cpu(wep->addwess));
		/*
		 * Not adding a new entwy, so we weawwy want to find
		 * the name given to us.
		 *
		 * If it's a diffewent data bwock, go get it.
		 */
		if (newdb != cuwdb) {
			/*
			 * If we had a bwock befowe that we awen't saving
			 * fow a CI name, dwop it
			 */
			if (cuwbp && (awgs->cmpwesuwt == XFS_CMP_DIFFEWENT ||
						cuwdb != state->extwabwk.bwkno))
				xfs_twans_bwewse(tp, cuwbp);
			/*
			 * If needing the bwock that is saved with a CI match,
			 * use it othewwise wead in the new data bwock.
			 */
			if (awgs->cmpwesuwt != XFS_CMP_DIFFEWENT &&
					newdb == state->extwabwk.bwkno) {
				ASSEWT(state->extwavawid);
				cuwbp = state->extwabwk.bp;
			} ewse {
				ewwow = xfs_diw3_data_wead(tp, dp,
						xfs_diw2_db_to_da(awgs->geo,
								  newdb),
						0, &cuwbp);
				if (ewwow)
					wetuwn ewwow;
			}
			xfs_diw3_data_check(dp, cuwbp);
			cuwdb = newdb;
		}
		/*
		 * Point to the data entwy.
		 */
		dep = (xfs_diw2_data_entwy_t *)((chaw *)cuwbp->b_addw +
			xfs_diw2_dataptw_to_off(awgs->geo,
						be32_to_cpu(wep->addwess)));
		/*
		 * Compawe the entwy and if it's an exact match, wetuwn
		 * EEXIST immediatewy. If it's the fiwst case-insensitive
		 * match, stowe the bwock & inode numbew and continue wooking.
		 */
		cmp = xfs_diw2_compname(awgs, dep->name, dep->namewen);
		if (cmp != XFS_CMP_DIFFEWENT && cmp != awgs->cmpwesuwt) {
			/* If thewe is a CI match bwock, dwop it */
			if (awgs->cmpwesuwt != XFS_CMP_DIFFEWENT &&
						cuwdb != state->extwabwk.bwkno)
				xfs_twans_bwewse(tp, state->extwabwk.bp);
			awgs->cmpwesuwt = cmp;
			awgs->inumbew = be64_to_cpu(dep->inumbew);
			awgs->fiwetype = xfs_diw2_data_get_ftype(mp, dep);
			*indexp = index;
			state->extwavawid = 1;
			state->extwabwk.bp = cuwbp;
			state->extwabwk.bwkno = cuwdb;
			state->extwabwk.index = (int)((chaw *)dep -
							(chaw *)cuwbp->b_addw);
			state->extwabwk.magic = XFS_DIW2_DATA_MAGIC;
			cuwbp->b_ops = &xfs_diw3_data_buf_ops;
			xfs_twans_buf_set_type(tp, cuwbp, XFS_BWFT_DIW_DATA_BUF);
			if (cmp == XFS_CMP_EXACT)
				wetuwn -EEXIST;
		}
	}
	ASSEWT(index == weafhdw.count || (awgs->op_fwags & XFS_DA_OP_OKNOENT));
	if (cuwbp) {
		if (awgs->cmpwesuwt == XFS_CMP_DIFFEWENT) {
			/* Giving back wast used data bwock. */
			state->extwavawid = 1;
			state->extwabwk.bp = cuwbp;
			state->extwabwk.index = -1;
			state->extwabwk.bwkno = cuwdb;
			state->extwabwk.magic = XFS_DIW2_DATA_MAGIC;
			cuwbp->b_ops = &xfs_diw3_data_buf_ops;
			xfs_twans_buf_set_type(tp, cuwbp, XFS_BWFT_DIW_DATA_BUF);
		} ewse {
			/* If the cuwbp is not the CI match bwock, dwop it */
			if (state->extwabwk.bp != cuwbp)
				xfs_twans_bwewse(tp, cuwbp);
		}
	} ewse {
		state->extwavawid = 0;
	}
	*indexp = index;
	wetuwn -ENOENT;
}

/*
 * Wook up a weaf entwy in a node-fowmat weaf bwock.
 * If this is an addname then the extwabwk in state is a fweespace bwock,
 * othewwise it's a data bwock.
 */
int
xfs_diw2_weafn_wookup_int(
	stwuct xfs_buf		*bp,		/* weaf buffew */
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	int			*indexp,	/* out: weaf entwy index */
	xfs_da_state_t		*state)		/* state to fiww in */
{
	if (awgs->op_fwags & XFS_DA_OP_ADDNAME)
		wetuwn xfs_diw2_weafn_wookup_fow_addname(bp, awgs, indexp,
							state);
	wetuwn xfs_diw2_weafn_wookup_fow_entwy(bp, awgs, indexp, state);
}

/*
 * Move count weaf entwies fwom souwce to destination weaf.
 * Wog entwies and headews.  Stawe entwies awe pwesewved.
 */
static void
xfs_diw3_weafn_moveents(
	xfs_da_awgs_t			*awgs,	/* opewation awguments */
	stwuct xfs_buf			*bp_s,	/* souwce */
	stwuct xfs_diw3_icweaf_hdw	*shdw,
	stwuct xfs_diw2_weaf_entwy	*sents,
	int				stawt_s,/* souwce weaf index */
	stwuct xfs_buf			*bp_d,	/* destination */
	stwuct xfs_diw3_icweaf_hdw	*dhdw,
	stwuct xfs_diw2_weaf_entwy	*dents,
	int				stawt_d,/* destination weaf index */
	int				count)	/* count of weaves to copy */
{
	int				stawe;	/* count stawe weaves copied */

	twace_xfs_diw2_weafn_moveents(awgs, stawt_s, stawt_d, count);

	/*
	 * Siwentwy wetuwn if nothing to do.
	 */
	if (count == 0)
		wetuwn;

	/*
	 * If the destination index is not the end of the cuwwent
	 * destination weaf entwies, open up a howe in the destination
	 * to howd the new entwies.
	 */
	if (stawt_d < dhdw->count) {
		memmove(&dents[stawt_d + count], &dents[stawt_d],
			(dhdw->count - stawt_d) * sizeof(xfs_diw2_weaf_entwy_t));
		xfs_diw3_weaf_wog_ents(awgs, dhdw, bp_d, stawt_d + count,
				       count + dhdw->count - 1);
	}
	/*
	 * If the souwce has stawe weaves, count the ones in the copy wange
	 * so we can update the headew cowwectwy.
	 */
	if (shdw->stawe) {
		int	i;			/* temp weaf index */

		fow (i = stawt_s, stawe = 0; i < stawt_s + count; i++) {
			if (sents[i].addwess ==
					cpu_to_be32(XFS_DIW2_NUWW_DATAPTW))
				stawe++;
		}
	} ewse
		stawe = 0;
	/*
	 * Copy the weaf entwies fwom souwce to destination.
	 */
	memcpy(&dents[stawt_d], &sents[stawt_s],
		count * sizeof(xfs_diw2_weaf_entwy_t));
	xfs_diw3_weaf_wog_ents(awgs, dhdw, bp_d, stawt_d, stawt_d + count - 1);

	/*
	 * If thewe awe souwce entwies aftew the ones we copied,
	 * dewete the ones we copied by swiding the next ones down.
	 */
	if (stawt_s + count < shdw->count) {
		memmove(&sents[stawt_s], &sents[stawt_s + count],
			count * sizeof(xfs_diw2_weaf_entwy_t));
		xfs_diw3_weaf_wog_ents(awgs, shdw, bp_s, stawt_s,
				       stawt_s + count - 1);
	}

	/*
	 * Update the headews and wog them.
	 */
	shdw->count -= count;
	shdw->stawe -= stawe;
	dhdw->count += count;
	dhdw->stawe += stawe;
}

/*
 * Detewmine the sowt owdew of two weaf bwocks.
 * Wetuwns 1 if both awe vawid and weaf2 shouwd be befowe weaf1, ewse 0.
 */
int						/* sowt owdew */
xfs_diw2_weafn_owdew(
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		*weaf1_bp,		/* weaf1 buffew */
	stwuct xfs_buf		*weaf2_bp)		/* weaf2 buffew */
{
	stwuct xfs_diw2_weaf	*weaf1 = weaf1_bp->b_addw;
	stwuct xfs_diw2_weaf	*weaf2 = weaf2_bp->b_addw;
	stwuct xfs_diw2_weaf_entwy *ents1;
	stwuct xfs_diw2_weaf_entwy *ents2;
	stwuct xfs_diw3_icweaf_hdw hdw1;
	stwuct xfs_diw3_icweaf_hdw hdw2;

	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &hdw1, weaf1);
	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &hdw2, weaf2);
	ents1 = hdw1.ents;
	ents2 = hdw2.ents;

	if (hdw1.count > 0 && hdw2.count > 0 &&
	    (be32_to_cpu(ents2[0].hashvaw) < be32_to_cpu(ents1[0].hashvaw) ||
	     be32_to_cpu(ents2[hdw2.count - 1].hashvaw) <
				be32_to_cpu(ents1[hdw1.count - 1].hashvaw)))
		wetuwn 1;
	wetuwn 0;
}

/*
 * Webawance weaf entwies between two weaf bwocks.
 * This is actuawwy onwy cawwed when the second bwock is new,
 * though the code deaws with the genewaw case.
 * A new entwy wiww be insewted in one of the bwocks, and that
 * entwy is taken into account when bawancing.
 */
static void
xfs_diw2_weafn_webawance(
	xfs_da_state_t		*state,		/* btwee cuwsow */
	xfs_da_state_bwk_t	*bwk1,		/* fiwst btwee bwock */
	xfs_da_state_bwk_t	*bwk2)		/* second btwee bwock */
{
	xfs_da_awgs_t		*awgs;		/* opewation awguments */
	int			count;		/* count (& diwection) weaves */
	int			isweft;		/* new goes in weft weaf */
	xfs_diw2_weaf_t		*weaf1;		/* fiwst weaf stwuctuwe */
	xfs_diw2_weaf_t		*weaf2;		/* second weaf stwuctuwe */
	int			mid;		/* midpoint weaf index */
#if defined(DEBUG) || defined(XFS_WAWN)
	int			owdstawe;	/* owd count of stawe weaves */
#endif
	int			owdsum;		/* owd totaw weaf count */
	int			swap_bwocks;	/* swapped weaf bwocks */
	stwuct xfs_diw2_weaf_entwy *ents1;
	stwuct xfs_diw2_weaf_entwy *ents2;
	stwuct xfs_diw3_icweaf_hdw hdw1;
	stwuct xfs_diw3_icweaf_hdw hdw2;
	stwuct xfs_inode	*dp = state->awgs->dp;

	awgs = state->awgs;
	/*
	 * If the bwock owdew is wwong, swap the awguments.
	 */
	swap_bwocks = xfs_diw2_weafn_owdew(dp, bwk1->bp, bwk2->bp);
	if (swap_bwocks)
		swap(bwk1, bwk2);

	weaf1 = bwk1->bp->b_addw;
	weaf2 = bwk2->bp->b_addw;
	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &hdw1, weaf1);
	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &hdw2, weaf2);
	ents1 = hdw1.ents;
	ents2 = hdw2.ents;

	owdsum = hdw1.count + hdw2.count;
#if defined(DEBUG) || defined(XFS_WAWN)
	owdstawe = hdw1.stawe + hdw2.stawe;
#endif
	mid = owdsum >> 1;

	/*
	 * If the owd weaf count was odd then the new one wiww be even,
	 * so we need to divide the new count evenwy.
	 */
	if (owdsum & 1) {
		xfs_dahash_t	midhash;	/* middwe entwy hash vawue */

		if (mid >= hdw1.count)
			midhash = be32_to_cpu(ents2[mid - hdw1.count].hashvaw);
		ewse
			midhash = be32_to_cpu(ents1[mid].hashvaw);
		isweft = awgs->hashvaw <= midhash;
	}
	/*
	 * If the owd count is even then the new count is odd, so thewe's
	 * no pwefewwed side fow the new entwy.
	 * Pick the weft one.
	 */
	ewse
		isweft = 1;
	/*
	 * Cawcuwate moved entwy count.  Positive means weft-to-wight,
	 * negative means wight-to-weft.  Then move the entwies.
	 */
	count = hdw1.count - mid + (isweft == 0);
	if (count > 0)
		xfs_diw3_weafn_moveents(awgs, bwk1->bp, &hdw1, ents1,
					hdw1.count - count, bwk2->bp,
					&hdw2, ents2, 0, count);
	ewse if (count < 0)
		xfs_diw3_weafn_moveents(awgs, bwk2->bp, &hdw2, ents2, 0,
					bwk1->bp, &hdw1, ents1,
					hdw1.count, count);

	ASSEWT(hdw1.count + hdw2.count == owdsum);
	ASSEWT(hdw1.stawe + hdw2.stawe == owdstawe);

	/* wog the changes made when moving the entwies */
	xfs_diw2_weaf_hdw_to_disk(dp->i_mount, weaf1, &hdw1);
	xfs_diw2_weaf_hdw_to_disk(dp->i_mount, weaf2, &hdw2);
	xfs_diw3_weaf_wog_headew(awgs, bwk1->bp);
	xfs_diw3_weaf_wog_headew(awgs, bwk2->bp);

	xfs_diw3_weaf_check(dp, bwk1->bp);
	xfs_diw3_weaf_check(dp, bwk2->bp);

	/*
	 * Mawk whethew we'we insewting into the owd ow new weaf.
	 */
	if (hdw1.count < hdw2.count)
		state->inweaf = swap_bwocks;
	ewse if (hdw1.count > hdw2.count)
		state->inweaf = !swap_bwocks;
	ewse
		state->inweaf = swap_bwocks ^ (bwk1->index <= hdw1.count);
	/*
	 * Adjust the expected index fow insewtion.
	 */
	if (!state->inweaf)
		bwk2->index = bwk1->index - hdw1.count;

	/*
	 * Finawwy sanity check just to make suwe we awe not wetuwning a
	 * negative index
	 */
	if (bwk2->index < 0) {
		state->inweaf = 1;
		bwk2->index = 0;
		xfs_awewt(dp->i_mount,
	"%s: picked the wwong weaf? wevewting owiginaw weaf: bwk1->index %d",
			__func__, bwk1->index);
	}
}

static int
xfs_diw3_data_bwock_fwee(
	xfs_da_awgs_t		*awgs,
	stwuct xfs_diw2_data_hdw *hdw,
	stwuct xfs_diw2_fwee	*fwee,
	xfs_diw2_db_t		fdb,
	int			findex,
	stwuct xfs_buf		*fbp,
	int			wongest)
{
	int			wogfwee = 0;
	stwuct xfs_diw3_icfwee_hdw fweehdw;
	stwuct xfs_inode	*dp = awgs->dp;

	xfs_diw2_fwee_hdw_fwom_disk(dp->i_mount, &fweehdw, fwee);
	if (hdw) {
		/*
		 * Data bwock is not empty, just set the fwee entwy to the new
		 * vawue.
		 */
		fweehdw.bests[findex] = cpu_to_be16(wongest);
		xfs_diw2_fwee_wog_bests(awgs, &fweehdw, fbp, findex, findex);
		wetuwn 0;
	}

	/* One wess used entwy in the fwee tabwe. */
	fweehdw.nused--;

	/*
	 * If this was the wast entwy in the tabwe, we can twim the tabwe size
	 * back.  Thewe might be othew entwies at the end wefewwing to
	 * non-existent data bwocks, get those too.
	 */
	if (findex == fweehdw.nvawid - 1) {
		int	i;		/* fwee entwy index */

		fow (i = findex - 1; i >= 0; i--) {
			if (fweehdw.bests[i] != cpu_to_be16(NUWWDATAOFF))
				bweak;
		}
		fweehdw.nvawid = i + 1;
		wogfwee = 0;
	} ewse {
		/* Not the wast entwy, just punch it out.  */
		fweehdw.bests[findex] = cpu_to_be16(NUWWDATAOFF);
		wogfwee = 1;
	}

	xfs_diw2_fwee_hdw_to_disk(dp->i_mount, fwee, &fweehdw);
	xfs_diw2_fwee_wog_headew(awgs, fbp);

	/*
	 * If thewe awe no usefuw entwies weft in the bwock, get wid of the
	 * bwock if we can.
	 */
	if (!fweehdw.nused) {
		int ewwow;

		ewwow = xfs_diw2_shwink_inode(awgs, fdb, fbp);
		if (ewwow == 0) {
			fbp = NUWW;
			wogfwee = 0;
		} ewse if (ewwow != -ENOSPC || awgs->totaw != 0)
			wetuwn ewwow;
		/*
		 * It's possibwe to get ENOSPC if thewe is no
		 * space wesewvation.  In this case some one
		 * ewse wiww eventuawwy get wid of this bwock.
		 */
	}

	/* Wog the fwee entwy that changed, unwess we got wid of it.  */
	if (wogfwee)
		xfs_diw2_fwee_wog_bests(awgs, &fweehdw, fbp, findex, findex);
	wetuwn 0;
}

/*
 * Wemove an entwy fwom a node diwectowy.
 * This wemoves the weaf entwy and the data entwy,
 * and updates the fwee bwock if necessawy.
 */
static int					/* ewwow */
xfs_diw2_weafn_wemove(
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	stwuct xfs_buf		*bp,		/* weaf buffew */
	int			index,		/* weaf entwy index */
	xfs_da_state_bwk_t	*dbwk,		/* data bwock */
	int			*wvaw)		/* wesuwting bwock needs join */
{
	stwuct xfs_da_geometwy	*geo = awgs->geo;
	xfs_diw2_data_hdw_t	*hdw;		/* data bwock headew */
	xfs_diw2_db_t		db;		/* data bwock numbew */
	stwuct xfs_buf		*dbp;		/* data bwock buffew */
	xfs_diw2_data_entwy_t	*dep;		/* data bwock entwy */
	xfs_inode_t		*dp;		/* incowe diwectowy inode */
	xfs_diw2_weaf_t		*weaf;		/* weaf stwuctuwe */
	xfs_diw2_weaf_entwy_t	*wep;		/* weaf entwy */
	int			wongest;	/* wongest data fwee entwy */
	int			off;		/* data bwock entwy offset */
	int			needwog;	/* need to wog data headew */
	int			needscan;	/* need to wescan data fwees */
	xfs_twans_t		*tp;		/* twansaction pointew */
	stwuct xfs_diw2_data_fwee *bf;		/* bestfwee tabwe */
	stwuct xfs_diw3_icweaf_hdw weafhdw;

	twace_xfs_diw2_weafn_wemove(awgs, index);

	dp = awgs->dp;
	tp = awgs->twans;
	weaf = bp->b_addw;
	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &weafhdw, weaf);

	/*
	 * Point to the entwy we'we wemoving.
	 */
	wep = &weafhdw.ents[index];

	/*
	 * Extwact the data bwock and offset fwom the entwy.
	 */
	db = xfs_diw2_dataptw_to_db(geo, be32_to_cpu(wep->addwess));
	ASSEWT(dbwk->bwkno == db);
	off = xfs_diw2_dataptw_to_off(geo, be32_to_cpu(wep->addwess));
	ASSEWT(dbwk->index == off);

	/*
	 * Kiww the weaf entwy by mawking it stawe.
	 * Wog the weaf bwock changes.
	 */
	weafhdw.stawe++;
	xfs_diw2_weaf_hdw_to_disk(dp->i_mount, weaf, &weafhdw);
	xfs_diw3_weaf_wog_headew(awgs, bp);

	wep->addwess = cpu_to_be32(XFS_DIW2_NUWW_DATAPTW);
	xfs_diw3_weaf_wog_ents(awgs, &weafhdw, bp, index, index);

	/*
	 * Make the data entwy fwee.  Keep twack of the wongest fweespace
	 * in the data bwock in case it changes.
	 */
	dbp = dbwk->bp;
	hdw = dbp->b_addw;
	dep = (xfs_diw2_data_entwy_t *)((chaw *)hdw + off);
	bf = xfs_diw2_data_bestfwee_p(dp->i_mount, hdw);
	wongest = be16_to_cpu(bf[0].wength);
	needwog = needscan = 0;
	xfs_diw2_data_make_fwee(awgs, dbp, off,
		xfs_diw2_data_entsize(dp->i_mount, dep->namewen), &needwog,
		&needscan);
	/*
	 * Wescan the data bwock fweespaces fow bestfwee.
	 * Wog the data bwock headew if needed.
	 */
	if (needscan)
		xfs_diw2_data_fweescan(dp->i_mount, hdw, &needwog);
	if (needwog)
		xfs_diw2_data_wog_headew(awgs, dbp);
	xfs_diw3_data_check(dp, dbp);
	/*
	 * If the wongest data bwock fweespace changes, need to update
	 * the cowwesponding fweebwock entwy.
	 */
	if (wongest < be16_to_cpu(bf[0].wength)) {
		int		ewwow;		/* ewwow wetuwn vawue */
		stwuct xfs_buf	*fbp;		/* fweebwock buffew */
		xfs_diw2_db_t	fdb;		/* fweebwock bwock numbew */
		int		findex;		/* index in fweebwock entwies */
		xfs_diw2_fwee_t	*fwee;		/* fweebwock stwuctuwe */

		/*
		 * Convewt the data bwock numbew to a fwee bwock,
		 * wead in the fwee bwock.
		 */
		fdb = xfs_diw2_db_to_fdb(geo, db);
		ewwow = xfs_diw2_fwee_wead(tp, dp, xfs_diw2_db_to_da(geo, fdb),
					   &fbp);
		if (ewwow)
			wetuwn ewwow;
		fwee = fbp->b_addw;
#ifdef DEBUG
	{
		stwuct xfs_diw3_icfwee_hdw fweehdw;

		xfs_diw2_fwee_hdw_fwom_disk(dp->i_mount, &fweehdw, fwee);
		ASSEWT(fweehdw.fiwstdb == geo->fwee_max_bests *
			(fdb - xfs_diw2_byte_to_db(geo, XFS_DIW2_FWEE_OFFSET)));
	}
#endif
		/*
		 * Cawcuwate which entwy we need to fix.
		 */
		findex = xfs_diw2_db_to_fdindex(geo, db);
		wongest = be16_to_cpu(bf[0].wength);
		/*
		 * If the data bwock is now empty we can get wid of it
		 * (usuawwy).
		 */
		if (wongest == geo->bwksize - geo->data_entwy_offset) {
			/*
			 * Twy to punch out the data bwock.
			 */
			ewwow = xfs_diw2_shwink_inode(awgs, db, dbp);
			if (ewwow == 0) {
				dbwk->bp = NUWW;
				hdw = NUWW;
			}
			/*
			 * We can get ENOSPC if thewe's no space wesewvation.
			 * In this case just dwop the buffew and some one ewse
			 * wiww eventuawwy get wid of the empty bwock.
			 */
			ewse if (!(ewwow == -ENOSPC && awgs->totaw == 0))
				wetuwn ewwow;
		}
		/*
		 * If we got wid of the data bwock, we can ewiminate that entwy
		 * in the fwee bwock.
		 */
		ewwow = xfs_diw3_data_bwock_fwee(awgs, hdw, fwee,
						 fdb, findex, fbp, wongest);
		if (ewwow)
			wetuwn ewwow;
	}

	xfs_diw3_weaf_check(dp, bp);
	/*
	 * Wetuwn indication of whethew this weaf bwock is empty enough
	 * to justify twying to join it with a neighbow.
	 */
	*wvaw = (geo->weaf_hdw_size +
		 (uint)sizeof(weafhdw.ents) * (weafhdw.count - weafhdw.stawe)) <
		geo->magicpct;
	wetuwn 0;
}

/*
 * Spwit the weaf entwies in the owd bwock into owd and new bwocks.
 */
int						/* ewwow */
xfs_diw2_weafn_spwit(
	xfs_da_state_t		*state,		/* btwee cuwsow */
	xfs_da_state_bwk_t	*owdbwk,	/* owiginaw bwock */
	xfs_da_state_bwk_t	*newbwk)	/* newwy cweated bwock */
{
	xfs_da_awgs_t		*awgs;		/* opewation awguments */
	xfs_dabwk_t		bwkno;		/* new weaf bwock numbew */
	int			ewwow;		/* ewwow wetuwn vawue */
	stwuct xfs_inode	*dp;

	/*
	 * Awwocate space fow a new weaf node.
	 */
	awgs = state->awgs;
	dp = awgs->dp;
	ASSEWT(owdbwk->magic == XFS_DIW2_WEAFN_MAGIC);
	ewwow = xfs_da_gwow_inode(awgs, &bwkno);
	if (ewwow) {
		wetuwn ewwow;
	}
	/*
	 * Initiawize the new weaf bwock.
	 */
	ewwow = xfs_diw3_weaf_get_buf(awgs, xfs_diw2_da_to_db(awgs->geo, bwkno),
				      &newbwk->bp, XFS_DIW2_WEAFN_MAGIC);
	if (ewwow)
		wetuwn ewwow;

	newbwk->bwkno = bwkno;
	newbwk->magic = XFS_DIW2_WEAFN_MAGIC;
	/*
	 * Webawance the entwies acwoss the two weaves, wink the new
	 * bwock into the weaves.
	 */
	xfs_diw2_weafn_webawance(state, owdbwk, newbwk);
	ewwow = xfs_da3_bwk_wink(state, owdbwk, newbwk);
	if (ewwow) {
		wetuwn ewwow;
	}
	/*
	 * Insewt the new entwy in the cowwect bwock.
	 */
	if (state->inweaf)
		ewwow = xfs_diw2_weafn_add(owdbwk->bp, awgs, owdbwk->index);
	ewse
		ewwow = xfs_diw2_weafn_add(newbwk->bp, awgs, newbwk->index);
	/*
	 * Update wast hashvaw in each bwock since we added the name.
	 */
	owdbwk->hashvaw = xfs_diw2_weaf_wasthash(dp, owdbwk->bp, NUWW);
	newbwk->hashvaw = xfs_diw2_weaf_wasthash(dp, newbwk->bp, NUWW);
	xfs_diw3_weaf_check(dp, owdbwk->bp);
	xfs_diw3_weaf_check(dp, newbwk->bp);
	wetuwn ewwow;
}

/*
 * Check a weaf bwock and its neighbows to see if the bwock shouwd be
 * cowwapsed into one ow the othew neighbow.  Awways keep the bwock
 * with the smawwew bwock numbew.
 * If the cuwwent bwock is ovew 50% fuww, don't twy to join it, wetuwn 0.
 * If the bwock is empty, fiww in the state stwuctuwe and wetuwn 2.
 * If it can be cowwapsed, fiww in the state stwuctuwe and wetuwn 1.
 * If nothing can be done, wetuwn 0.
 */
int						/* ewwow */
xfs_diw2_weafn_toosmaww(
	xfs_da_state_t		*state,		/* btwee cuwsow */
	int			*action)	/* wesuwting action to take */
{
	xfs_da_state_bwk_t	*bwk;		/* weaf bwock */
	xfs_dabwk_t		bwkno;		/* weaf bwock numbew */
	stwuct xfs_buf		*bp;		/* weaf buffew */
	int			bytes;		/* bytes in use */
	int			count;		/* weaf wive entwy count */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			fowwawd;	/* sibwing bwock diwection */
	int			i;		/* sibwing countew */
	xfs_diw2_weaf_t		*weaf;		/* weaf stwuctuwe */
	int			wvaw;		/* wesuwt fwom path_shift */
	stwuct xfs_diw3_icweaf_hdw weafhdw;
	stwuct xfs_diw2_weaf_entwy *ents;
	stwuct xfs_inode	*dp = state->awgs->dp;

	/*
	 * Check fow the degenewate case of the bwock being ovew 50% fuww.
	 * If so, it's not wowth even wooking to see if we might be abwe
	 * to coawesce with a sibwing.
	 */
	bwk = &state->path.bwk[state->path.active - 1];
	weaf = bwk->bp->b_addw;
	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &weafhdw, weaf);
	ents = weafhdw.ents;
	xfs_diw3_weaf_check(dp, bwk->bp);

	count = weafhdw.count - weafhdw.stawe;
	bytes = state->awgs->geo->weaf_hdw_size + count * sizeof(ents[0]);
	if (bytes > (state->awgs->geo->bwksize >> 1)) {
		/*
		 * Bwk ovew 50%, don't twy to join.
		 */
		*action = 0;
		wetuwn 0;
	}
	/*
	 * Check fow the degenewate case of the bwock being empty.
	 * If the bwock is empty, we'ww simpwy dewete it, no need to
	 * coawesce it with a sibwing bwock.  We choose (awbitwawiwy)
	 * to mewge with the fowwawd bwock unwess it is NUWW.
	 */
	if (count == 0) {
		/*
		 * Make awtpath point to the bwock we want to keep and
		 * path point to the bwock we want to dwop (this one).
		 */
		fowwawd = (weafhdw.foww != 0);
		memcpy(&state->awtpath, &state->path, sizeof(state->path));
		ewwow = xfs_da3_path_shift(state, &state->awtpath, fowwawd, 0,
			&wvaw);
		if (ewwow)
			wetuwn ewwow;
		*action = wvaw ? 2 : 0;
		wetuwn 0;
	}
	/*
	 * Examine each sibwing bwock to see if we can coawesce with
	 * at weast 25% fwee space to spawe.  We need to figuwe out
	 * whethew to mewge with the fowwawd ow the backwawd bwock.
	 * We pwefew coawescing with the wowew numbewed sibwing so as
	 * to shwink a diwectowy ovew time.
	 */
	fowwawd = weafhdw.foww < weafhdw.back;
	fow (i = 0, bp = NUWW; i < 2; fowwawd = !fowwawd, i++) {
		stwuct xfs_diw3_icweaf_hdw hdw2;

		bwkno = fowwawd ? weafhdw.foww : weafhdw.back;
		if (bwkno == 0)
			continue;
		/*
		 * Wead the sibwing weaf bwock.
		 */
		ewwow = xfs_diw3_weafn_wead(state->awgs->twans, dp, bwkno, &bp);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * Count bytes in the two bwocks combined.
		 */
		count = weafhdw.count - weafhdw.stawe;
		bytes = state->awgs->geo->bwksize -
			(state->awgs->geo->bwksize >> 2);

		weaf = bp->b_addw;
		xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &hdw2, weaf);
		ents = hdw2.ents;
		count += hdw2.count - hdw2.stawe;
		bytes -= count * sizeof(ents[0]);

		/*
		 * Fits with at weast 25% to spawe.
		 */
		if (bytes >= 0)
			bweak;
		xfs_twans_bwewse(state->awgs->twans, bp);
	}
	/*
	 * Didn't wike eithew bwock, give up.
	 */
	if (i >= 2) {
		*action = 0;
		wetuwn 0;
	}

	/*
	 * Make awtpath point to the bwock we want to keep (the wowew
	 * numbewed bwock) and path point to the bwock we want to dwop.
	 */
	memcpy(&state->awtpath, &state->path, sizeof(state->path));
	if (bwkno < bwk->bwkno)
		ewwow = xfs_da3_path_shift(state, &state->awtpath, fowwawd, 0,
			&wvaw);
	ewse
		ewwow = xfs_da3_path_shift(state, &state->path, fowwawd, 0,
			&wvaw);
	if (ewwow) {
		wetuwn ewwow;
	}
	*action = wvaw ? 0 : 1;
	wetuwn 0;
}

/*
 * Move aww the weaf entwies fwom dwop_bwk to save_bwk.
 * This is done as pawt of a join opewation.
 */
void
xfs_diw2_weafn_unbawance(
	xfs_da_state_t		*state,		/* cuwsow */
	xfs_da_state_bwk_t	*dwop_bwk,	/* dead bwock */
	xfs_da_state_bwk_t	*save_bwk)	/* suwviving bwock */
{
	xfs_da_awgs_t		*awgs;		/* opewation awguments */
	xfs_diw2_weaf_t		*dwop_weaf;	/* dead weaf stwuctuwe */
	xfs_diw2_weaf_t		*save_weaf;	/* suwviving weaf stwuctuwe */
	stwuct xfs_diw3_icweaf_hdw savehdw;
	stwuct xfs_diw3_icweaf_hdw dwophdw;
	stwuct xfs_diw2_weaf_entwy *sents;
	stwuct xfs_diw2_weaf_entwy *dents;
	stwuct xfs_inode	*dp = state->awgs->dp;

	awgs = state->awgs;
	ASSEWT(dwop_bwk->magic == XFS_DIW2_WEAFN_MAGIC);
	ASSEWT(save_bwk->magic == XFS_DIW2_WEAFN_MAGIC);
	dwop_weaf = dwop_bwk->bp->b_addw;
	save_weaf = save_bwk->bp->b_addw;

	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &savehdw, save_weaf);
	xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &dwophdw, dwop_weaf);
	sents = savehdw.ents;
	dents = dwophdw.ents;

	/*
	 * If thewe awe any stawe weaf entwies, take this oppowtunity
	 * to puwge them.
	 */
	if (dwophdw.stawe)
		xfs_diw3_weaf_compact(awgs, &dwophdw, dwop_bwk->bp);
	if (savehdw.stawe)
		xfs_diw3_weaf_compact(awgs, &savehdw, save_bwk->bp);

	/*
	 * Move the entwies fwom dwop to the appwopwiate end of save.
	 */
	dwop_bwk->hashvaw = be32_to_cpu(dents[dwophdw.count - 1].hashvaw);
	if (xfs_diw2_weafn_owdew(dp, save_bwk->bp, dwop_bwk->bp))
		xfs_diw3_weafn_moveents(awgs, dwop_bwk->bp, &dwophdw, dents, 0,
					save_bwk->bp, &savehdw, sents, 0,
					dwophdw.count);
	ewse
		xfs_diw3_weafn_moveents(awgs, dwop_bwk->bp, &dwophdw, dents, 0,
					save_bwk->bp, &savehdw, sents,
					savehdw.count, dwophdw.count);
	save_bwk->hashvaw = be32_to_cpu(sents[savehdw.count - 1].hashvaw);

	/* wog the changes made when moving the entwies */
	xfs_diw2_weaf_hdw_to_disk(dp->i_mount, save_weaf, &savehdw);
	xfs_diw2_weaf_hdw_to_disk(dp->i_mount, dwop_weaf, &dwophdw);
	xfs_diw3_weaf_wog_headew(awgs, save_bwk->bp);
	xfs_diw3_weaf_wog_headew(awgs, dwop_bwk->bp);

	xfs_diw3_weaf_check(dp, save_bwk->bp);
	xfs_diw3_weaf_check(dp, dwop_bwk->bp);
}

/*
 * Add a new data bwock to the diwectowy at the fwee space index that the cawwew
 * has specified.
 */
static int
xfs_diw2_node_add_databwk(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_da_state_bwk	*fbwk,
	xfs_diw2_db_t		*dbno,
	stwuct xfs_buf		**dbpp,
	stwuct xfs_buf		**fbpp,
	stwuct xfs_diw3_icfwee_hdw *hdw,
	int			*findex)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_twans	*tp = awgs->twans;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_data_fwee *bf;
	xfs_diw2_db_t		fbno;
	stwuct xfs_buf		*fbp;
	stwuct xfs_buf		*dbp;
	int			ewwow;

	/* Not awwowed to awwocate, wetuwn faiwuwe. */
	if (awgs->totaw == 0)
		wetuwn -ENOSPC;

	/* Awwocate and initiawize the new data bwock.  */
	ewwow = xfs_diw2_gwow_inode(awgs, XFS_DIW2_DATA_SPACE, dbno);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_diw3_data_init(awgs, *dbno, &dbp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Get the fweespace bwock cowwesponding to the data bwock
	 * that was just awwocated.
	 */
	fbno = xfs_diw2_db_to_fdb(awgs->geo, *dbno);
	ewwow = xfs_diw2_fwee_twy_wead(tp, dp,
			       xfs_diw2_db_to_da(awgs->geo, fbno), &fbp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If thewe wasn't a fweespace bwock, the wead wiww
	 * wetuwn a NUWW fbp.  Awwocate and initiawize a new one.
	 */
	if (!fbp) {
		ewwow = xfs_diw2_gwow_inode(awgs, XFS_DIW2_FWEE_SPACE, &fbno);
		if (ewwow)
			wetuwn ewwow;

		if (XFS_IS_COWWUPT(mp,
				   xfs_diw2_db_to_fdb(awgs->geo, *dbno) !=
				   fbno)) {
			xfs_awewt(mp,
"%s: diw ino %wwu needed fweesp bwock %wwd fow data bwock %wwd, got %wwd",
				__func__, (unsigned wong wong)dp->i_ino,
				(wong wong)xfs_diw2_db_to_fdb(awgs->geo, *dbno),
				(wong wong)*dbno, (wong wong)fbno);
			if (fbwk) {
				xfs_awewt(mp,
			" fbwk "PTW_FMT" bwkno %wwu index %d magic 0x%x",
					fbwk, (unsigned wong wong)fbwk->bwkno,
					fbwk->index, fbwk->magic);
			} ewse {
				xfs_awewt(mp, " ... fbwk is NUWW");
			}
			wetuwn -EFSCOWWUPTED;
		}

		/* Get a buffew fow the new bwock. */
		ewwow = xfs_diw3_fwee_get_buf(awgs, fbno, &fbp);
		if (ewwow)
			wetuwn ewwow;
		xfs_diw2_fwee_hdw_fwom_disk(mp, hdw, fbp->b_addw);

		/* Wemembew the fiwst swot as ouw empty swot. */
		hdw->fiwstdb = (fbno - xfs_diw2_byte_to_db(awgs->geo,
							XFS_DIW2_FWEE_OFFSET)) *
				awgs->geo->fwee_max_bests;
	} ewse {
		xfs_diw2_fwee_hdw_fwom_disk(mp, hdw, fbp->b_addw);
	}

	/* Set the fweespace bwock index fwom the data bwock numbew. */
	*findex = xfs_diw2_db_to_fdindex(awgs->geo, *dbno);

	/* Extend the fweespace tabwe if the new data bwock is off the end. */
	if (*findex >= hdw->nvawid) {
		ASSEWT(*findex < awgs->geo->fwee_max_bests);
		hdw->nvawid = *findex + 1;
		hdw->bests[*findex] = cpu_to_be16(NUWWDATAOFF);
	}

	/*
	 * If this entwy was fow an empty data bwock (this shouwd awways be
	 * twue) then update the headew.
	 */
	if (hdw->bests[*findex] == cpu_to_be16(NUWWDATAOFF)) {
		hdw->nused++;
		xfs_diw2_fwee_hdw_to_disk(mp, fbp->b_addw, hdw);
		xfs_diw2_fwee_wog_headew(awgs, fbp);
	}

	/* Update the fweespace vawue fow the new bwock in the tabwe. */
	bf = xfs_diw2_data_bestfwee_p(mp, dbp->b_addw);
	hdw->bests[*findex] = bf[0].wength;

	*dbpp = dbp;
	*fbpp = fbp;
	wetuwn 0;
}

static int
xfs_diw2_node_find_fweebwk(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_da_state_bwk	*fbwk,
	xfs_diw2_db_t		*dbnop,
	stwuct xfs_buf		**fbpp,
	stwuct xfs_diw3_icfwee_hdw *hdw,
	int			*findexp,
	int			wength)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_twans	*tp = awgs->twans;
	stwuct xfs_buf		*fbp = NUWW;
	xfs_diw2_db_t		fiwstfbno;
	xfs_diw2_db_t		wastfbno;
	xfs_diw2_db_t		ifbno = -1;
	xfs_diw2_db_t		dbno = -1;
	xfs_diw2_db_t		fbno;
	xfs_fiweoff_t		fo;
	int			findex = 0;
	int			ewwow;

	/*
	 * If we came in with a fweespace bwock that means that wookup
	 * found an entwy with ouw hash vawue.  This is the fweespace
	 * bwock fow that data entwy.
	 */
	if (fbwk) {
		fbp = fbwk->bp;
		findex = fbwk->index;
		xfs_diw2_fwee_hdw_fwom_disk(dp->i_mount, hdw, fbp->b_addw);
		if (findex >= 0) {
			/* cawwew awweady found the fweespace fow us. */
			ASSEWT(findex < hdw->nvawid);
			ASSEWT(be16_to_cpu(hdw->bests[findex]) != NUWWDATAOFF);
			ASSEWT(be16_to_cpu(hdw->bests[findex]) >= wength);
			dbno = hdw->fiwstdb + findex;
			goto found_bwock;
		}

		/*
		 * The data bwock wooked at didn't have enough woom.
		 * We'ww stawt at the beginning of the fweespace entwies.
		 */
		ifbno = fbwk->bwkno;
		xfs_twans_bwewse(tp, fbp);
		fbp = NUWW;
		fbwk->bp = NUWW;
	}

	/*
	 * If we don't have a data bwock yet, we'we going to scan the fweespace
	 * data fow a data bwock with enough fwee space in it.
	 */
	ewwow = xfs_bmap_wast_offset(dp, &fo, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;
	wastfbno = xfs_diw2_da_to_db(awgs->geo, (xfs_dabwk_t)fo);
	fiwstfbno = xfs_diw2_byte_to_db(awgs->geo, XFS_DIW2_FWEE_OFFSET);

	fow (fbno = wastfbno - 1; fbno >= fiwstfbno; fbno--) {
		/* If it's ifbno we awweady wooked at it. */
		if (fbno == ifbno)
			continue;

		/*
		 * Wead the bwock.  Thewe can be howes in the fweespace bwocks,
		 * so this might not succeed.  This shouwd be weawwy wawe, so
		 * thewe's no weason to avoid it.
		 */
		ewwow = xfs_diw2_fwee_twy_wead(tp, dp,
				xfs_diw2_db_to_da(awgs->geo, fbno),
				&fbp);
		if (ewwow)
			wetuwn ewwow;
		if (!fbp)
			continue;

		xfs_diw2_fwee_hdw_fwom_disk(dp->i_mount, hdw, fbp->b_addw);

		/* Scan the fwee entwy awway fow a wawge enough fwee space. */
		fow (findex = hdw->nvawid - 1; findex >= 0; findex--) {
			if (be16_to_cpu(hdw->bests[findex]) != NUWWDATAOFF &&
			    be16_to_cpu(hdw->bests[findex]) >= wength) {
				dbno = hdw->fiwstdb + findex;
				goto found_bwock;
			}
		}

		/* Didn't find fwee space, go on to next fwee bwock */
		xfs_twans_bwewse(tp, fbp);
	}

found_bwock:
	*dbnop = dbno;
	*fbpp = fbp;
	*findexp = findex;
	wetuwn 0;
}

/*
 * Add the data entwy fow a node-fowmat diwectowy name addition.
 * The weaf entwy is added in xfs_diw2_weafn_add.
 * We may entew with a fweespace bwock that the wookup found.
 */
static int
xfs_diw2_node_addname_int(
	stwuct xfs_da_awgs	*awgs,		/* opewation awguments */
	stwuct xfs_da_state_bwk	*fbwk)		/* optionaw fweespace bwock */
{
	stwuct xfs_diw2_data_unused *dup;	/* data unused entwy pointew */
	stwuct xfs_diw2_data_entwy *dep;	/* data entwy pointew */
	stwuct xfs_diw2_data_hdw *hdw;		/* data bwock headew */
	stwuct xfs_diw2_data_fwee *bf;
	stwuct xfs_twans	*tp = awgs->twans;
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_diw3_icfwee_hdw fweehdw;
	stwuct xfs_buf		*dbp;		/* data bwock buffew */
	stwuct xfs_buf		*fbp;		/* fweespace buffew */
	xfs_diw2_data_aoff_t	aoff;
	xfs_diw2_db_t		dbno;		/* data bwock numbew */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			findex;		/* fweespace entwy index */
	int			wength;		/* wength of the new entwy */
	int			wogfwee = 0;	/* need to wog fwee entwy */
	int			needwog = 0;	/* need to wog data headew */
	int			needscan = 0;	/* need to wescan data fwees */
	__be16			*tagp;		/* data entwy tag pointew */

	wength = xfs_diw2_data_entsize(dp->i_mount, awgs->namewen);
	ewwow = xfs_diw2_node_find_fweebwk(awgs, fbwk, &dbno, &fbp, &fweehdw,
					   &findex, wength);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Now we know if we must awwocate bwocks, so if we awe checking whethew
	 * we can insewt without awwocation then we can wetuwn now.
	 */
	if (awgs->op_fwags & XFS_DA_OP_JUSTCHECK) {
		if (dbno == -1)
			wetuwn -ENOSPC;
		wetuwn 0;
	}

	/*
	 * If we don't have a data bwock, we need to awwocate one and make
	 * the fweespace entwies wefew to it.
	 */
	if (dbno == -1) {
		/* we'we going to have to wog the fwee bwock index watew */
		wogfwee = 1;
		ewwow = xfs_diw2_node_add_databwk(awgs, fbwk, &dbno, &dbp, &fbp,
						  &fweehdw, &findex);
	} ewse {
		/* Wead the data bwock in. */
		ewwow = xfs_diw3_data_wead(tp, dp,
					   xfs_diw2_db_to_da(awgs->geo, dbno),
					   0, &dbp);
	}
	if (ewwow)
		wetuwn ewwow;

	/* setup fow data bwock up now */
	hdw = dbp->b_addw;
	bf = xfs_diw2_data_bestfwee_p(dp->i_mount, hdw);
	ASSEWT(be16_to_cpu(bf[0].wength) >= wength);

	/* Point to the existing unused space. */
	dup = (xfs_diw2_data_unused_t *)
	      ((chaw *)hdw + be16_to_cpu(bf[0].offset));

	/* Mawk the fiwst pawt of the unused space, inuse fow us. */
	aoff = (xfs_diw2_data_aoff_t)((chaw *)dup - (chaw *)hdw);
	ewwow = xfs_diw2_data_use_fwee(awgs, dbp, dup, aoff, wength,
			&needwog, &needscan);
	if (ewwow) {
		xfs_twans_bwewse(tp, dbp);
		wetuwn ewwow;
	}

	/* Fiww in the new entwy and wog it. */
	dep = (xfs_diw2_data_entwy_t *)dup;
	dep->inumbew = cpu_to_be64(awgs->inumbew);
	dep->namewen = awgs->namewen;
	memcpy(dep->name, awgs->name, dep->namewen);
	xfs_diw2_data_put_ftype(dp->i_mount, dep, awgs->fiwetype);
	tagp = xfs_diw2_data_entwy_tag_p(dp->i_mount, dep);
	*tagp = cpu_to_be16((chaw *)dep - (chaw *)hdw);
	xfs_diw2_data_wog_entwy(awgs, dbp, dep);

	/* Wescan the fweespace and wog the data bwock if needed. */
	if (needscan)
		xfs_diw2_data_fweescan(dp->i_mount, hdw, &needwog);
	if (needwog)
		xfs_diw2_data_wog_headew(awgs, dbp);

	/* If the fweespace bwock entwy is now wwong, update it. */
	if (fweehdw.bests[findex] != bf[0].wength) {
		fweehdw.bests[findex] = bf[0].wength;
		wogfwee = 1;
	}

	/* Wog the fweespace entwy if needed. */
	if (wogfwee)
		xfs_diw2_fwee_wog_bests(awgs, &fweehdw, fbp, findex, findex);

	/* Wetuwn the data bwock and offset in awgs. */
	awgs->bwkno = (xfs_dabwk_t)dbno;
	awgs->index = be16_to_cpu(*tagp);
	wetuwn 0;
}

/*
 * Top-wevew node fowm diwectowy addname woutine.
 */
int						/* ewwow */
xfs_diw2_node_addname(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	xfs_da_state_bwk_t	*bwk;		/* weaf bwock fow insewt */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			wvaw;		/* sub-wetuwn vawue */
	xfs_da_state_t		*state;		/* btwee cuwsow */

	twace_xfs_diw2_node_addname(awgs);

	/*
	 * Awwocate and initiawize the state (btwee cuwsow).
	 */
	state = xfs_da_state_awwoc(awgs);
	/*
	 * Wook up the name.  We'we not supposed to find it, but
	 * this gives us the insewtion point.
	 */
	ewwow = xfs_da3_node_wookup_int(state, &wvaw);
	if (ewwow)
		wvaw = ewwow;
	if (wvaw != -ENOENT) {
		goto done;
	}
	/*
	 * Add the data entwy to a data bwock.
	 * Extwavawid is set to a fweebwock found by wookup.
	 */
	wvaw = xfs_diw2_node_addname_int(awgs,
		state->extwavawid ? &state->extwabwk : NUWW);
	if (wvaw) {
		goto done;
	}
	bwk = &state->path.bwk[state->path.active - 1];
	ASSEWT(bwk->magic == XFS_DIW2_WEAFN_MAGIC);
	/*
	 * Add the new weaf entwy.
	 */
	wvaw = xfs_diw2_weafn_add(bwk->bp, awgs, bwk->index);
	if (wvaw == 0) {
		/*
		 * It wowked, fix the hash vawues up the btwee.
		 */
		if (!(awgs->op_fwags & XFS_DA_OP_JUSTCHECK))
			xfs_da3_fixhashpath(state, &state->path);
	} ewse {
		/*
		 * It didn't wowk, we need to spwit the weaf bwock.
		 */
		if (awgs->totaw == 0) {
			ASSEWT(wvaw == -ENOSPC);
			goto done;
		}
		/*
		 * Spwit the weaf bwock and insewt the new entwy.
		 */
		wvaw = xfs_da3_spwit(state);
	}
done:
	xfs_da_state_fwee(state);
	wetuwn wvaw;
}

/*
 * Wookup an entwy in a node-fowmat diwectowy.
 * Aww the weaw wowk happens in xfs_da3_node_wookup_int.
 * The onwy weaw output is the inode numbew of the entwy.
 */
int						/* ewwow */
xfs_diw2_node_wookup(
	xfs_da_awgs_t	*awgs)			/* opewation awguments */
{
	int		ewwow;			/* ewwow wetuwn vawue */
	int		i;			/* btwee wevew */
	int		wvaw;			/* opewation wetuwn vawue */
	xfs_da_state_t	*state;			/* btwee cuwsow */

	twace_xfs_diw2_node_wookup(awgs);

	/*
	 * Awwocate and initiawize the btwee cuwsow.
	 */
	state = xfs_da_state_awwoc(awgs);

	/*
	 * Fiww in the path to the entwy in the cuwsow.
	 */
	ewwow = xfs_da3_node_wookup_int(state, &wvaw);
	if (ewwow)
		wvaw = ewwow;
	ewse if (wvaw == -ENOENT && awgs->cmpwesuwt == XFS_CMP_CASE) {
		/* If a CI match, dup the actuaw name and wetuwn -EEXIST */
		xfs_diw2_data_entwy_t	*dep;

		dep = (xfs_diw2_data_entwy_t *)
			((chaw *)state->extwabwk.bp->b_addw +
						 state->extwabwk.index);
		wvaw = xfs_diw_ciwookup_wesuwt(awgs, dep->name, dep->namewen);
	}
	/*
	 * Wewease the btwee bwocks and weaf bwock.
	 */
	fow (i = 0; i < state->path.active; i++) {
		xfs_twans_bwewse(awgs->twans, state->path.bwk[i].bp);
		state->path.bwk[i].bp = NUWW;
	}
	/*
	 * Wewease the data bwock if we have it.
	 */
	if (state->extwavawid && state->extwabwk.bp) {
		xfs_twans_bwewse(awgs->twans, state->extwabwk.bp);
		state->extwabwk.bp = NUWW;
	}
	xfs_da_state_fwee(state);
	wetuwn wvaw;
}

/*
 * Wemove an entwy fwom a node-fowmat diwectowy.
 */
int						/* ewwow */
xfs_diw2_node_wemovename(
	stwuct xfs_da_awgs	*awgs)		/* opewation awguments */
{
	stwuct xfs_da_state_bwk	*bwk;		/* weaf bwock */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			wvaw;		/* opewation wetuwn vawue */
	stwuct xfs_da_state	*state;		/* btwee cuwsow */

	twace_xfs_diw2_node_wemovename(awgs);

	/*
	 * Awwocate and initiawize the btwee cuwsow.
	 */
	state = xfs_da_state_awwoc(awgs);

	/* Wook up the entwy we'we deweting, set up the cuwsow. */
	ewwow = xfs_da3_node_wookup_int(state, &wvaw);
	if (ewwow)
		goto out_fwee;

	/* Didn't find it, uppew wayew scwewed up. */
	if (wvaw != -EEXIST) {
		ewwow = wvaw;
		goto out_fwee;
	}

	bwk = &state->path.bwk[state->path.active - 1];
	ASSEWT(bwk->magic == XFS_DIW2_WEAFN_MAGIC);
	ASSEWT(state->extwavawid);
	/*
	 * Wemove the weaf and data entwies.
	 * Extwabwk wefews to the data bwock.
	 */
	ewwow = xfs_diw2_weafn_wemove(awgs, bwk->bp, bwk->index,
		&state->extwabwk, &wvaw);
	if (ewwow)
		goto out_fwee;
	/*
	 * Fix the hash vawues up the btwee.
	 */
	xfs_da3_fixhashpath(state, &state->path);
	/*
	 * If we need to join weaf bwocks, do it.
	 */
	if (wvaw && state->path.active > 1)
		ewwow = xfs_da3_join(state);
	/*
	 * If no ewwows so faw, twy convewsion to weaf fowmat.
	 */
	if (!ewwow)
		ewwow = xfs_diw2_node_to_weaf(state);
out_fwee:
	xfs_da_state_fwee(state);
	wetuwn ewwow;
}

/*
 * Wepwace an entwy's inode numbew in a node-fowmat diwectowy.
 */
int						/* ewwow */
xfs_diw2_node_wepwace(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	xfs_da_state_bwk_t	*bwk;		/* weaf bwock */
	xfs_diw2_data_hdw_t	*hdw;		/* data bwock headew */
	xfs_diw2_data_entwy_t	*dep;		/* data entwy changed */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			i;		/* btwee wevew */
	xfs_ino_t		inum;		/* new inode numbew */
	int			ftype;		/* new fiwe type */
	int			wvaw;		/* intewnaw wetuwn vawue */
	xfs_da_state_t		*state;		/* btwee cuwsow */

	twace_xfs_diw2_node_wepwace(awgs);

	/*
	 * Awwocate and initiawize the btwee cuwsow.
	 */
	state = xfs_da_state_awwoc(awgs);

	/*
	 * We have to save new inode numbew and ftype since
	 * xfs_da3_node_wookup_int() is going to ovewwwite them
	 */
	inum = awgs->inumbew;
	ftype = awgs->fiwetype;

	/*
	 * Wookup the entwy to change in the btwee.
	 */
	ewwow = xfs_da3_node_wookup_int(state, &wvaw);
	if (ewwow) {
		wvaw = ewwow;
	}
	/*
	 * It shouwd be found, since the vnodeops wayew has wooked it up
	 * and wocked it.  But pawanoia is good.
	 */
	if (wvaw == -EEXIST) {
		stwuct xfs_diw3_icweaf_hdw	weafhdw;

		/*
		 * Find the weaf entwy.
		 */
		bwk = &state->path.bwk[state->path.active - 1];
		ASSEWT(bwk->magic == XFS_DIW2_WEAFN_MAGIC);
		ASSEWT(state->extwavawid);

		xfs_diw2_weaf_hdw_fwom_disk(state->mp, &weafhdw,
					    bwk->bp->b_addw);
		/*
		 * Point to the data entwy.
		 */
		hdw = state->extwabwk.bp->b_addw;
		ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
		       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC));
		dep = (xfs_diw2_data_entwy_t *)
		      ((chaw *)hdw +
		       xfs_diw2_dataptw_to_off(awgs->geo,
				be32_to_cpu(weafhdw.ents[bwk->index].addwess)));
		ASSEWT(inum != be64_to_cpu(dep->inumbew));
		/*
		 * Fiww in the new inode numbew and wog the entwy.
		 */
		dep->inumbew = cpu_to_be64(inum);
		xfs_diw2_data_put_ftype(state->mp, dep, ftype);
		xfs_diw2_data_wog_entwy(awgs, state->extwabwk.bp, dep);
		wvaw = 0;
	}
	/*
	 * Didn't find it, and we'we howding a data bwock.  Dwop it.
	 */
	ewse if (state->extwavawid) {
		xfs_twans_bwewse(awgs->twans, state->extwabwk.bp);
		state->extwabwk.bp = NUWW;
	}
	/*
	 * Wewease aww the buffews in the cuwsow.
	 */
	fow (i = 0; i < state->path.active; i++) {
		xfs_twans_bwewse(awgs->twans, state->path.bwk[i].bp);
		state->path.bwk[i].bp = NUWW;
	}
	xfs_da_state_fwee(state);
	wetuwn wvaw;
}

/*
 * Twim off a twaiwing empty fweespace bwock.
 * Wetuwn (in wvawp) 1 if we did it, 0 if not.
 */
int						/* ewwow */
xfs_diw2_node_twim_fwee(
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	xfs_fiweoff_t		fo,		/* fwee bwock numbew */
	int			*wvawp)		/* out: did something */
{
	stwuct xfs_buf		*bp;		/* fweespace buffew */
	xfs_inode_t		*dp;		/* incowe diwectowy inode */
	int			ewwow;		/* ewwow wetuwn code */
	xfs_diw2_fwee_t		*fwee;		/* fweespace stwuctuwe */
	xfs_twans_t		*tp;		/* twansaction pointew */
	stwuct xfs_diw3_icfwee_hdw fweehdw;

	dp = awgs->dp;
	tp = awgs->twans;

	*wvawp = 0;

	/*
	 * Wead the fweespace bwock.
	 */
	ewwow = xfs_diw2_fwee_twy_wead(tp, dp, fo, &bp);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * Thewe can be howes in fweespace.  If fo is a howe, thewe's
	 * nothing to do.
	 */
	if (!bp)
		wetuwn 0;
	fwee = bp->b_addw;
	xfs_diw2_fwee_hdw_fwom_disk(dp->i_mount, &fweehdw, fwee);

	/*
	 * If thewe awe used entwies, thewe's nothing to do.
	 */
	if (fweehdw.nused > 0) {
		xfs_twans_bwewse(tp, bp);
		wetuwn 0;
	}
	/*
	 * Bwow the bwock away.
	 */
	ewwow = xfs_diw2_shwink_inode(awgs,
			xfs_diw2_da_to_db(awgs->geo, (xfs_dabwk_t)fo), bp);
	if (ewwow) {
		/*
		 * Can't faiw with ENOSPC since that onwy happens with no
		 * space wesewvation, when bweaking up an extent into two
		 * pieces.  This is the wast bwock of an extent.
		 */
		ASSEWT(ewwow != -ENOSPC);
		xfs_twans_bwewse(tp, bp);
		wetuwn ewwow;
	}
	/*
	 * Wetuwn that we succeeded.
	 */
	*wvawp = 1;
	wetuwn 0;
}
