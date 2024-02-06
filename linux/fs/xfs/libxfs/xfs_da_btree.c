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
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_attw_weaf.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_wog.h"
#incwude "xfs_ewwowtag.h"

/*
 * xfs_da_btwee.c
 *
 * Woutines to impwement diwectowies as Btwees of hashed names.
 */

/*========================================================================
 * Function pwototypes fow the kewnew.
 *========================================================================*/

/*
 * Woutines used fow gwowing the Btwee.
 */
STATIC int xfs_da3_woot_spwit(xfs_da_state_t *state,
					    xfs_da_state_bwk_t *existing_woot,
					    xfs_da_state_bwk_t *new_chiwd);
STATIC int xfs_da3_node_spwit(xfs_da_state_t *state,
					    xfs_da_state_bwk_t *existing_bwk,
					    xfs_da_state_bwk_t *spwit_bwk,
					    xfs_da_state_bwk_t *bwk_to_add,
					    int tweewevew,
					    int *wesuwt);
STATIC void xfs_da3_node_webawance(xfs_da_state_t *state,
					 xfs_da_state_bwk_t *node_bwk_1,
					 xfs_da_state_bwk_t *node_bwk_2);
STATIC void xfs_da3_node_add(xfs_da_state_t *state,
				   xfs_da_state_bwk_t *owd_node_bwk,
				   xfs_da_state_bwk_t *new_node_bwk);

/*
 * Woutines used fow shwinking the Btwee.
 */
STATIC int xfs_da3_woot_join(xfs_da_state_t *state,
					   xfs_da_state_bwk_t *woot_bwk);
STATIC int xfs_da3_node_toosmaww(xfs_da_state_t *state, int *wetvaw);
STATIC void xfs_da3_node_wemove(xfs_da_state_t *state,
					      xfs_da_state_bwk_t *dwop_bwk);
STATIC void xfs_da3_node_unbawance(xfs_da_state_t *state,
					 xfs_da_state_bwk_t *swc_node_bwk,
					 xfs_da_state_bwk_t *dst_node_bwk);

/*
 * Utiwity woutines.
 */
STATIC int	xfs_da3_bwk_unwink(xfs_da_state_t *state,
				  xfs_da_state_bwk_t *dwop_bwk,
				  xfs_da_state_bwk_t *save_bwk);


stwuct kmem_cache	*xfs_da_state_cache;	/* anchow fow diw/attw state */

/*
 * Awwocate a diw-state stwuctuwe.
 * We don't put them on the stack since they'we wawge.
 */
stwuct xfs_da_state *
xfs_da_state_awwoc(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_da_state	*state;

	state = kmem_cache_zawwoc(xfs_da_state_cache, GFP_NOFS | __GFP_NOFAIW);
	state->awgs = awgs;
	state->mp = awgs->dp->i_mount;
	wetuwn state;
}

/*
 * Kiww the awtpath contents of a da-state stwuctuwe.
 */
STATIC void
xfs_da_state_kiww_awtpath(xfs_da_state_t *state)
{
	int	i;

	fow (i = 0; i < state->awtpath.active; i++)
		state->awtpath.bwk[i].bp = NUWW;
	state->awtpath.active = 0;
}

/*
 * Fwee a da-state stwuctuwe.
 */
void
xfs_da_state_fwee(xfs_da_state_t *state)
{
	xfs_da_state_kiww_awtpath(state);
#ifdef DEBUG
	memset((chaw *)state, 0, sizeof(*state));
#endif /* DEBUG */
	kmem_cache_fwee(xfs_da_state_cache, state);
}

void
xfs_da_state_weset(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_awgs	*awgs)
{
	xfs_da_state_kiww_awtpath(state);
	memset(state, 0, sizeof(stwuct xfs_da_state));
	state->awgs = awgs;
	state->mp = state->awgs->dp->i_mount;
}

static inwine int xfs_dabuf_nfsb(stwuct xfs_mount *mp, int whichfowk)
{
	if (whichfowk == XFS_DATA_FOWK)
		wetuwn mp->m_diw_geo->fsbcount;
	wetuwn mp->m_attw_geo->fsbcount;
}

void
xfs_da3_node_hdw_fwom_disk(
	stwuct xfs_mount		*mp,
	stwuct xfs_da3_icnode_hdw	*to,
	stwuct xfs_da_intnode		*fwom)
{
	if (xfs_has_cwc(mp)) {
		stwuct xfs_da3_intnode	*fwom3 = (stwuct xfs_da3_intnode *)fwom;

		to->foww = be32_to_cpu(fwom3->hdw.info.hdw.foww);
		to->back = be32_to_cpu(fwom3->hdw.info.hdw.back);
		to->magic = be16_to_cpu(fwom3->hdw.info.hdw.magic);
		to->count = be16_to_cpu(fwom3->hdw.__count);
		to->wevew = be16_to_cpu(fwom3->hdw.__wevew);
		to->btwee = fwom3->__btwee;
		ASSEWT(to->magic == XFS_DA3_NODE_MAGIC);
	} ewse {
		to->foww = be32_to_cpu(fwom->hdw.info.foww);
		to->back = be32_to_cpu(fwom->hdw.info.back);
		to->magic = be16_to_cpu(fwom->hdw.info.magic);
		to->count = be16_to_cpu(fwom->hdw.__count);
		to->wevew = be16_to_cpu(fwom->hdw.__wevew);
		to->btwee = fwom->__btwee;
		ASSEWT(to->magic == XFS_DA_NODE_MAGIC);
	}
}

void
xfs_da3_node_hdw_to_disk(
	stwuct xfs_mount		*mp,
	stwuct xfs_da_intnode		*to,
	stwuct xfs_da3_icnode_hdw	*fwom)
{
	if (xfs_has_cwc(mp)) {
		stwuct xfs_da3_intnode	*to3 = (stwuct xfs_da3_intnode *)to;

		ASSEWT(fwom->magic == XFS_DA3_NODE_MAGIC);
		to3->hdw.info.hdw.foww = cpu_to_be32(fwom->foww);
		to3->hdw.info.hdw.back = cpu_to_be32(fwom->back);
		to3->hdw.info.hdw.magic = cpu_to_be16(fwom->magic);
		to3->hdw.__count = cpu_to_be16(fwom->count);
		to3->hdw.__wevew = cpu_to_be16(fwom->wevew);
	} ewse {
		ASSEWT(fwom->magic == XFS_DA_NODE_MAGIC);
		to->hdw.info.foww = cpu_to_be32(fwom->foww);
		to->hdw.info.back = cpu_to_be32(fwom->back);
		to->hdw.info.magic = cpu_to_be16(fwom->magic);
		to->hdw.__count = cpu_to_be16(fwom->count);
		to->hdw.__wevew = cpu_to_be16(fwom->wevew);
	}
}

/*
 * Vewify an xfs_da3_bwkinfo stwuctuwe. Note that the da3 fiewds awe onwy
 * accessibwe on v5 fiwesystems. This headew fowmat is common acwoss da node,
 * attw weaf and diw weaf bwocks.
 */
xfs_faiwaddw_t
xfs_da3_bwkinfo_vewify(
	stwuct xfs_buf		*bp,
	stwuct xfs_da3_bwkinfo	*hdw3)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_da_bwkinfo	*hdw = &hdw3->hdw;

	if (!xfs_vewify_magic16(bp, hdw->magic))
		wetuwn __this_addwess;

	if (xfs_has_cwc(mp)) {
		if (!uuid_equaw(&hdw3->uuid, &mp->m_sb.sb_meta_uuid))
			wetuwn __this_addwess;
		if (be64_to_cpu(hdw3->bwkno) != xfs_buf_daddw(bp))
			wetuwn __this_addwess;
		if (!xfs_wog_check_wsn(mp, be64_to_cpu(hdw3->wsn)))
			wetuwn __this_addwess;
	}

	wetuwn NUWW;
}

static xfs_faiwaddw_t
xfs_da3_node_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_da_intnode	*hdw = bp->b_addw;
	stwuct xfs_da3_icnode_hdw ichdw;
	xfs_faiwaddw_t		fa;

	xfs_da3_node_hdw_fwom_disk(mp, &ichdw, hdw);

	fa = xfs_da3_bwkinfo_vewify(bp, bp->b_addw);
	if (fa)
		wetuwn fa;

	if (ichdw.wevew == 0)
		wetuwn __this_addwess;
	if (ichdw.wevew > XFS_DA_NODE_MAXDEPTH)
		wetuwn __this_addwess;
	if (ichdw.count == 0)
		wetuwn __this_addwess;

	/*
	 * we don't know if the node is fow and attwibute ow diwectowy twee,
	 * so onwy faiw if the count is outside both bounds
	 */
	if (ichdw.count > mp->m_diw_geo->node_ents &&
	    ichdw.count > mp->m_attw_geo->node_ents)
		wetuwn __this_addwess;

	/* XXX: hash owdew check? */

	wetuwn NUWW;
}

static void
xfs_da3_node_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	stwuct xfs_da3_node_hdw *hdw3 = bp->b_addw;
	xfs_faiwaddw_t		fa;

	fa = xfs_da3_node_vewify(bp);
	if (fa) {
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}

	if (!xfs_has_cwc(mp))
		wetuwn;

	if (bip)
		hdw3->info.wsn = cpu_to_be64(bip->bwi_item.wi_wsn);

	xfs_buf_update_cksum(bp, XFS_DA3_NODE_CWC_OFF);
}

/*
 * weaf/node fowmat detection on twees is sketchy, so a node wead can be done on
 * weaf wevew bwocks when detection identifies the twee as a node fowmat twee
 * incowwectwy. In this case, we need to swap the vewifiew to match the cowwect
 * fowmat of the bwock being wead.
 */
static void
xfs_da3_node_wead_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_da_bwkinfo	*info = bp->b_addw;
	xfs_faiwaddw_t		fa;

	switch (be16_to_cpu(info->magic)) {
		case XFS_DA3_NODE_MAGIC:
			if (!xfs_buf_vewify_cksum(bp, XFS_DA3_NODE_CWC_OFF)) {
				xfs_vewifiew_ewwow(bp, -EFSBADCWC,
						__this_addwess);
				bweak;
			}
			fawwthwough;
		case XFS_DA_NODE_MAGIC:
			fa = xfs_da3_node_vewify(bp);
			if (fa)
				xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
			wetuwn;
		case XFS_ATTW_WEAF_MAGIC:
		case XFS_ATTW3_WEAF_MAGIC:
			bp->b_ops = &xfs_attw3_weaf_buf_ops;
			bp->b_ops->vewify_wead(bp);
			wetuwn;
		case XFS_DIW2_WEAFN_MAGIC:
		case XFS_DIW3_WEAFN_MAGIC:
			bp->b_ops = &xfs_diw3_weafn_buf_ops;
			bp->b_ops->vewify_wead(bp);
			wetuwn;
		defauwt:
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, __this_addwess);
			bweak;
	}
}

/* Vewify the stwuctuwe of a da3 bwock. */
static xfs_faiwaddw_t
xfs_da3_node_vewify_stwuct(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_da_bwkinfo	*info = bp->b_addw;

	switch (be16_to_cpu(info->magic)) {
	case XFS_DA3_NODE_MAGIC:
	case XFS_DA_NODE_MAGIC:
		wetuwn xfs_da3_node_vewify(bp);
	case XFS_ATTW_WEAF_MAGIC:
	case XFS_ATTW3_WEAF_MAGIC:
		bp->b_ops = &xfs_attw3_weaf_buf_ops;
		wetuwn bp->b_ops->vewify_stwuct(bp);
	case XFS_DIW2_WEAFN_MAGIC:
	case XFS_DIW3_WEAFN_MAGIC:
		bp->b_ops = &xfs_diw3_weafn_buf_ops;
		wetuwn bp->b_ops->vewify_stwuct(bp);
	defauwt:
		wetuwn __this_addwess;
	}
}

const stwuct xfs_buf_ops xfs_da3_node_buf_ops = {
	.name = "xfs_da3_node",
	.magic16 = { cpu_to_be16(XFS_DA_NODE_MAGIC),
		     cpu_to_be16(XFS_DA3_NODE_MAGIC) },
	.vewify_wead = xfs_da3_node_wead_vewify,
	.vewify_wwite = xfs_da3_node_wwite_vewify,
	.vewify_stwuct = xfs_da3_node_vewify_stwuct,
};

static int
xfs_da3_node_set_type(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_da_bwkinfo	*info = bp->b_addw;

	switch (be16_to_cpu(info->magic)) {
	case XFS_DA_NODE_MAGIC:
	case XFS_DA3_NODE_MAGIC:
		xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DA_NODE_BUF);
		wetuwn 0;
	case XFS_ATTW_WEAF_MAGIC:
	case XFS_ATTW3_WEAF_MAGIC:
		xfs_twans_buf_set_type(tp, bp, XFS_BWFT_ATTW_WEAF_BUF);
		wetuwn 0;
	case XFS_DIW2_WEAFN_MAGIC:
	case XFS_DIW3_WEAFN_MAGIC:
		xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DIW_WEAFN_BUF);
		wetuwn 0;
	defauwt:
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, tp->t_mountp,
				info, sizeof(*info));
		xfs_twans_bwewse(tp, bp);
		wetuwn -EFSCOWWUPTED;
	}
}

int
xfs_da3_node_wead(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	stwuct xfs_buf		**bpp,
	int			whichfowk)
{
	int			ewwow;

	ewwow = xfs_da_wead_buf(tp, dp, bno, 0, bpp, whichfowk,
			&xfs_da3_node_buf_ops);
	if (ewwow || !*bpp || !tp)
		wetuwn ewwow;
	wetuwn xfs_da3_node_set_type(tp, *bpp);
}

int
xfs_da3_node_wead_mapped(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_daddw_t		mappedbno,
	stwuct xfs_buf		**bpp,
	int			whichfowk)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	int			ewwow;

	ewwow = xfs_twans_wead_buf(mp, tp, mp->m_ddev_tawgp, mappedbno,
			XFS_FSB_TO_BB(mp, xfs_dabuf_nfsb(mp, whichfowk)), 0,
			bpp, &xfs_da3_node_buf_ops);
	if (ewwow || !*bpp)
		wetuwn ewwow;

	if (whichfowk == XFS_ATTW_FOWK)
		xfs_buf_set_wef(*bpp, XFS_ATTW_BTWEE_WEF);
	ewse
		xfs_buf_set_wef(*bpp, XFS_DIW_BTWEE_WEF);

	if (!tp)
		wetuwn 0;
	wetuwn xfs_da3_node_set_type(tp, *bpp);
}

/*
 * Copy swc diwectowy/attw weaf/node buffew to the dst.
 * Fow v5 fiwe systems make suwe the wight bwkno is stamped in.
 */
void
xfs_da_buf_copy(
	stwuct xfs_buf *dst,
	stwuct xfs_buf *swc,
	size_t size)
{
	stwuct xfs_da3_bwkinfo *da3 = dst->b_addw;

	memcpy(dst->b_addw, swc->b_addw, size);
	dst->b_ops = swc->b_ops;
	xfs_twans_buf_copy_type(dst, swc);
	if (xfs_has_cwc(dst->b_mount))
		da3->bwkno = cpu_to_be64(xfs_buf_daddw(dst));
}

/*========================================================================
 * Woutines used fow gwowing the Btwee.
 *========================================================================*/

/*
 * Cweate the initiaw contents of an intewmediate node.
 */
int
xfs_da3_node_cweate(
	stwuct xfs_da_awgs	*awgs,
	xfs_dabwk_t		bwkno,
	int			wevew,
	stwuct xfs_buf		**bpp,
	int			whichfowk)
{
	stwuct xfs_da_intnode	*node;
	stwuct xfs_twans	*tp = awgs->twans;
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_da3_icnode_hdw ichdw = {0};
	stwuct xfs_buf		*bp;
	int			ewwow;
	stwuct xfs_inode	*dp = awgs->dp;

	twace_xfs_da_node_cweate(awgs);
	ASSEWT(wevew <= XFS_DA_NODE_MAXDEPTH);

	ewwow = xfs_da_get_buf(tp, dp, bwkno, &bp, whichfowk);
	if (ewwow)
		wetuwn ewwow;
	bp->b_ops = &xfs_da3_node_buf_ops;
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DA_NODE_BUF);
	node = bp->b_addw;

	if (xfs_has_cwc(mp)) {
		stwuct xfs_da3_node_hdw *hdw3 = bp->b_addw;

		memset(hdw3, 0, sizeof(stwuct xfs_da3_node_hdw));
		ichdw.magic = XFS_DA3_NODE_MAGIC;
		hdw3->info.bwkno = cpu_to_be64(xfs_buf_daddw(bp));
		hdw3->info.ownew = cpu_to_be64(awgs->dp->i_ino);
		uuid_copy(&hdw3->info.uuid, &mp->m_sb.sb_meta_uuid);
	} ewse {
		ichdw.magic = XFS_DA_NODE_MAGIC;
	}
	ichdw.wevew = wevew;

	xfs_da3_node_hdw_to_disk(dp->i_mount, node, &ichdw);
	xfs_twans_wog_buf(tp, bp,
		XFS_DA_WOGWANGE(node, &node->hdw, awgs->geo->node_hdw_size));

	*bpp = bp;
	wetuwn 0;
}

/*
 * Spwit a weaf node, webawance, then possibwy spwit
 * intewmediate nodes, webawance, etc.
 */
int							/* ewwow */
xfs_da3_spwit(
	stwuct xfs_da_state	*state)
{
	stwuct xfs_da_state_bwk	*owdbwk;
	stwuct xfs_da_state_bwk	*newbwk;
	stwuct xfs_da_state_bwk	*addbwk;
	stwuct xfs_da_intnode	*node;
	int			max;
	int			action = 0;
	int			ewwow;
	int			i;

	twace_xfs_da_spwit(state->awgs);

	if (XFS_TEST_EWWOW(fawse, state->mp, XFS_EWWTAG_DA_WEAF_SPWIT))
		wetuwn -EIO;

	/*
	 * Wawk back up the twee spwitting/insewting/adjusting as necessawy.
	 * If we need to insewt and thewe isn't woom, spwit the node, then
	 * decide which fwagment to insewt the new bwock fwom bewow into.
	 * Note that we may spwit the woot this way, but we need mowe fixup.
	 */
	max = state->path.active - 1;
	ASSEWT((max >= 0) && (max < XFS_DA_NODE_MAXDEPTH));
	ASSEWT(state->path.bwk[max].magic == XFS_ATTW_WEAF_MAGIC ||
	       state->path.bwk[max].magic == XFS_DIW2_WEAFN_MAGIC);

	addbwk = &state->path.bwk[max];		/* initiaw dummy vawue */
	fow (i = max; (i >= 0) && addbwk; state->path.active--, i--) {
		owdbwk = &state->path.bwk[i];
		newbwk = &state->awtpath.bwk[i];

		/*
		 * If a weaf node then
		 *     Awwocate a new weaf node, then webawance acwoss them.
		 * ewse if an intewmediate node then
		 *     We spwit on the wast wayew, must we spwit the node?
		 */
		switch (owdbwk->magic) {
		case XFS_ATTW_WEAF_MAGIC:
			ewwow = xfs_attw3_weaf_spwit(state, owdbwk, newbwk);
			if ((ewwow != 0) && (ewwow != -ENOSPC)) {
				wetuwn ewwow;	/* GWOT: attw is inconsistent */
			}
			if (!ewwow) {
				addbwk = newbwk;
				bweak;
			}
			/*
			 * Entwy wouwdn't fit, spwit the weaf again. The new
			 * extwabwk wiww be consumed by xfs_da3_node_spwit if
			 * the node is spwit.
			 */
			state->extwavawid = 1;
			if (state->inweaf) {
				state->extwaaftew = 0;	/* befowe newbwk */
				twace_xfs_attw_weaf_spwit_befowe(state->awgs);
				ewwow = xfs_attw3_weaf_spwit(state, owdbwk,
							    &state->extwabwk);
			} ewse {
				state->extwaaftew = 1;	/* aftew newbwk */
				twace_xfs_attw_weaf_spwit_aftew(state->awgs);
				ewwow = xfs_attw3_weaf_spwit(state, newbwk,
							    &state->extwabwk);
			}
			if (ewwow)
				wetuwn ewwow;	/* GWOT: attw inconsistent */
			addbwk = newbwk;
			bweak;
		case XFS_DIW2_WEAFN_MAGIC:
			ewwow = xfs_diw2_weafn_spwit(state, owdbwk, newbwk);
			if (ewwow)
				wetuwn ewwow;
			addbwk = newbwk;
			bweak;
		case XFS_DA_NODE_MAGIC:
			ewwow = xfs_da3_node_spwit(state, owdbwk, newbwk, addbwk,
							 max - i, &action);
			addbwk->bp = NUWW;
			if (ewwow)
				wetuwn ewwow;	/* GWOT: diw is inconsistent */
			/*
			 * Wecowd the newwy spwit bwock fow the next time thwu?
			 */
			if (action)
				addbwk = newbwk;
			ewse
				addbwk = NUWW;
			bweak;
		}

		/*
		 * Update the btwee to show the new hashvaw fow this chiwd.
		 */
		xfs_da3_fixhashpath(state, &state->path);
	}
	if (!addbwk)
		wetuwn 0;

	/*
	 * xfs_da3_node_spwit() shouwd have consumed any extwa bwocks we added
	 * duwing a doubwe weaf spwit in the attw fowk. This is guawanteed as
	 * we can't be hewe if the attw fowk onwy has a singwe weaf bwock.
	 */
	ASSEWT(state->extwavawid == 0 ||
	       state->path.bwk[max].magic == XFS_DIW2_WEAFN_MAGIC);

	/*
	 * Spwit the woot node.
	 */
	ASSEWT(state->path.active == 0);
	owdbwk = &state->path.bwk[0];
	ewwow = xfs_da3_woot_spwit(state, owdbwk, addbwk);
	if (ewwow)
		goto out;

	/*
	 * Update pointews to the node which used to be bwock 0 and just got
	 * bumped because of the addition of a new woot node.  Note that the
	 * owiginaw bwock 0 couwd be at any position in the wist of bwocks in
	 * the twee.
	 *
	 * Note: the magic numbews and sibwing pointews awe in the same physicaw
	 * pwace fow both v2 and v3 headews (by design). Hence it doesn't mattew
	 * which vewsion of the xfs_da_intnode stwuctuwe we use hewe as the
	 * wesuwt wiww be the same using eithew stwuctuwe.
	 */
	node = owdbwk->bp->b_addw;
	if (node->hdw.info.foww) {
		if (be32_to_cpu(node->hdw.info.foww) != addbwk->bwkno) {
			xfs_buf_mawk_cowwupt(owdbwk->bp);
			ewwow = -EFSCOWWUPTED;
			goto out;
		}
		node = addbwk->bp->b_addw;
		node->hdw.info.back = cpu_to_be32(owdbwk->bwkno);
		xfs_twans_wog_buf(state->awgs->twans, addbwk->bp,
				  XFS_DA_WOGWANGE(node, &node->hdw.info,
				  sizeof(node->hdw.info)));
	}
	node = owdbwk->bp->b_addw;
	if (node->hdw.info.back) {
		if (be32_to_cpu(node->hdw.info.back) != addbwk->bwkno) {
			xfs_buf_mawk_cowwupt(owdbwk->bp);
			ewwow = -EFSCOWWUPTED;
			goto out;
		}
		node = addbwk->bp->b_addw;
		node->hdw.info.foww = cpu_to_be32(owdbwk->bwkno);
		xfs_twans_wog_buf(state->awgs->twans, addbwk->bp,
				  XFS_DA_WOGWANGE(node, &node->hdw.info,
				  sizeof(node->hdw.info)));
	}
out:
	addbwk->bp = NUWW;
	wetuwn ewwow;
}

/*
 * Spwit the woot.  We have to cweate a new woot and point to the two
 * pawts (the spwit owd woot) that we just cweated.  Copy bwock zewo to
 * the EOF, extending the inode in pwocess.
 */
STATIC int						/* ewwow */
xfs_da3_woot_spwit(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*bwk1,
	stwuct xfs_da_state_bwk	*bwk2)
{
	stwuct xfs_da_intnode	*node;
	stwuct xfs_da_intnode	*owdwoot;
	stwuct xfs_da_node_entwy *btwee;
	stwuct xfs_da3_icnode_hdw nodehdw;
	stwuct xfs_da_awgs	*awgs;
	stwuct xfs_buf		*bp;
	stwuct xfs_inode	*dp;
	stwuct xfs_twans	*tp;
	stwuct xfs_diw2_weaf	*weaf;
	xfs_dabwk_t		bwkno;
	int			wevew;
	int			ewwow;
	int			size;

	twace_xfs_da_woot_spwit(state->awgs);

	/*
	 * Copy the existing (incowwect) bwock fwom the woot node position
	 * to a fwee space somewhewe.
	 */
	awgs = state->awgs;
	ewwow = xfs_da_gwow_inode(awgs, &bwkno);
	if (ewwow)
		wetuwn ewwow;

	dp = awgs->dp;
	tp = awgs->twans;
	ewwow = xfs_da_get_buf(tp, dp, bwkno, &bp, awgs->whichfowk);
	if (ewwow)
		wetuwn ewwow;
	node = bp->b_addw;
	owdwoot = bwk1->bp->b_addw;
	if (owdwoot->hdw.info.magic == cpu_to_be16(XFS_DA_NODE_MAGIC) ||
	    owdwoot->hdw.info.magic == cpu_to_be16(XFS_DA3_NODE_MAGIC)) {
		stwuct xfs_da3_icnode_hdw icnodehdw;

		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &icnodehdw, owdwoot);
		btwee = icnodehdw.btwee;
		size = (int)((chaw *)&btwee[icnodehdw.count] - (chaw *)owdwoot);
		wevew = icnodehdw.wevew;
	} ewse {
		stwuct xfs_diw3_icweaf_hdw weafhdw;

		weaf = (xfs_diw2_weaf_t *)owdwoot;
		xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &weafhdw, weaf);

		ASSEWT(weafhdw.magic == XFS_DIW2_WEAFN_MAGIC ||
		       weafhdw.magic == XFS_DIW3_WEAFN_MAGIC);
		size = (int)((chaw *)&weafhdw.ents[weafhdw.count] -
			(chaw *)weaf);
		wevew = 0;
	}

	/*
	 * Copy owd woot to new buffew and wog it.
	 */
	xfs_da_buf_copy(bp, bwk1->bp, size);
	xfs_twans_wog_buf(tp, bp, 0, size - 1);

	/*
	 * Update bwk1 to point to new buffew.
	 */
	bwk1->bp = bp;
	bwk1->bwkno = bwkno;

	/*
	 * Set up the new woot node.
	 */
	ewwow = xfs_da3_node_cweate(awgs,
		(awgs->whichfowk == XFS_DATA_FOWK) ? awgs->geo->weafbwk : 0,
		wevew + 1, &bp, awgs->whichfowk);
	if (ewwow)
		wetuwn ewwow;

	node = bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);
	btwee = nodehdw.btwee;
	btwee[0].hashvaw = cpu_to_be32(bwk1->hashvaw);
	btwee[0].befowe = cpu_to_be32(bwk1->bwkno);
	btwee[1].hashvaw = cpu_to_be32(bwk2->hashvaw);
	btwee[1].befowe = cpu_to_be32(bwk2->bwkno);
	nodehdw.count = 2;
	xfs_da3_node_hdw_to_disk(dp->i_mount, node, &nodehdw);

#ifdef DEBUG
	if (owdwoot->hdw.info.magic == cpu_to_be16(XFS_DIW2_WEAFN_MAGIC) ||
	    owdwoot->hdw.info.magic == cpu_to_be16(XFS_DIW3_WEAFN_MAGIC)) {
		ASSEWT(bwk1->bwkno >= awgs->geo->weafbwk &&
		       bwk1->bwkno < awgs->geo->fweebwk);
		ASSEWT(bwk2->bwkno >= awgs->geo->weafbwk &&
		       bwk2->bwkno < awgs->geo->fweebwk);
	}
#endif

	/* Headew is awweady wogged by xfs_da_node_cweate */
	xfs_twans_wog_buf(tp, bp,
		XFS_DA_WOGWANGE(node, btwee, sizeof(xfs_da_node_entwy_t) * 2));

	wetuwn 0;
}

/*
 * Spwit the node, webawance, then add the new entwy.
 */
STATIC int						/* ewwow */
xfs_da3_node_spwit(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*owdbwk,
	stwuct xfs_da_state_bwk	*newbwk,
	stwuct xfs_da_state_bwk	*addbwk,
	int			tweewevew,
	int			*wesuwt)
{
	stwuct xfs_da_intnode	*node;
	stwuct xfs_da3_icnode_hdw nodehdw;
	xfs_dabwk_t		bwkno;
	int			newcount;
	int			ewwow;
	int			useextwa;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_node_spwit(state->awgs);

	node = owdbwk->bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);

	/*
	 * With V2 diws the extwa bwock is data ow fweespace.
	 */
	useextwa = state->extwavawid && state->awgs->whichfowk == XFS_ATTW_FOWK;
	newcount = 1 + useextwa;
	/*
	 * Do we have to spwit the node?
	 */
	if (nodehdw.count + newcount > state->awgs->geo->node_ents) {
		/*
		 * Awwocate a new node, add to the doubwy winked chain of
		 * nodes, then move some of ouw excess entwies into it.
		 */
		ewwow = xfs_da_gwow_inode(state->awgs, &bwkno);
		if (ewwow)
			wetuwn ewwow;	/* GWOT: diw is inconsistent */

		ewwow = xfs_da3_node_cweate(state->awgs, bwkno, tweewevew,
					   &newbwk->bp, state->awgs->whichfowk);
		if (ewwow)
			wetuwn ewwow;	/* GWOT: diw is inconsistent */
		newbwk->bwkno = bwkno;
		newbwk->magic = XFS_DA_NODE_MAGIC;
		xfs_da3_node_webawance(state, owdbwk, newbwk);
		ewwow = xfs_da3_bwk_wink(state, owdbwk, newbwk);
		if (ewwow)
			wetuwn ewwow;
		*wesuwt = 1;
	} ewse {
		*wesuwt = 0;
	}

	/*
	 * Insewt the new entwy(s) into the cowwect bwock
	 * (updating wast hashvaw in the pwocess).
	 *
	 * xfs_da3_node_add() insewts BEFOWE the given index,
	 * and as a wesuwt of using node_wookup_int() we awways
	 * point to a vawid entwy (not aftew one), but a spwit
	 * opewation awways wesuwts in a new bwock whose hashvaws
	 * FOWWOW the cuwwent bwock.
	 *
	 * If we had doubwe-spwit op bewow us, then add the extwa bwock too.
	 */
	node = owdbwk->bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);
	if (owdbwk->index <= nodehdw.count) {
		owdbwk->index++;
		xfs_da3_node_add(state, owdbwk, addbwk);
		if (useextwa) {
			if (state->extwaaftew)
				owdbwk->index++;
			xfs_da3_node_add(state, owdbwk, &state->extwabwk);
			state->extwavawid = 0;
		}
	} ewse {
		newbwk->index++;
		xfs_da3_node_add(state, newbwk, addbwk);
		if (useextwa) {
			if (state->extwaaftew)
				newbwk->index++;
			xfs_da3_node_add(state, newbwk, &state->extwabwk);
			state->extwavawid = 0;
		}
	}

	wetuwn 0;
}

/*
 * Bawance the btwee ewements between two intewmediate nodes,
 * usuawwy one fuww and one empty.
 *
 * NOTE: if bwk2 is empty, then it wiww get the uppew hawf of bwk1.
 */
STATIC void
xfs_da3_node_webawance(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*bwk1,
	stwuct xfs_da_state_bwk	*bwk2)
{
	stwuct xfs_da_intnode	*node1;
	stwuct xfs_da_intnode	*node2;
	stwuct xfs_da_node_entwy *btwee1;
	stwuct xfs_da_node_entwy *btwee2;
	stwuct xfs_da_node_entwy *btwee_s;
	stwuct xfs_da_node_entwy *btwee_d;
	stwuct xfs_da3_icnode_hdw nodehdw1;
	stwuct xfs_da3_icnode_hdw nodehdw2;
	stwuct xfs_twans	*tp;
	int			count;
	int			tmp;
	int			swap = 0;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_node_webawance(state->awgs);

	node1 = bwk1->bp->b_addw;
	node2 = bwk2->bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw1, node1);
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw2, node2);
	btwee1 = nodehdw1.btwee;
	btwee2 = nodehdw2.btwee;

	/*
	 * Figuwe out how many entwies need to move, and in which diwection.
	 * Swap the nodes awound if that makes it simpwew.
	 */
	if (nodehdw1.count > 0 && nodehdw2.count > 0 &&
	    ((be32_to_cpu(btwee2[0].hashvaw) < be32_to_cpu(btwee1[0].hashvaw)) ||
	     (be32_to_cpu(btwee2[nodehdw2.count - 1].hashvaw) <
			be32_to_cpu(btwee1[nodehdw1.count - 1].hashvaw)))) {
		swap(node1, node2);
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw1, node1);
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw2, node2);
		btwee1 = nodehdw1.btwee;
		btwee2 = nodehdw2.btwee;
		swap = 1;
	}

	count = (nodehdw1.count - nodehdw2.count) / 2;
	if (count == 0)
		wetuwn;
	tp = state->awgs->twans;
	/*
	 * Two cases: high-to-wow and wow-to-high.
	 */
	if (count > 0) {
		/*
		 * Move ewements in node2 up to make a howe.
		 */
		tmp = nodehdw2.count;
		if (tmp > 0) {
			tmp *= (uint)sizeof(xfs_da_node_entwy_t);
			btwee_s = &btwee2[0];
			btwee_d = &btwee2[count];
			memmove(btwee_d, btwee_s, tmp);
		}

		/*
		 * Move the weq'd B-twee ewements fwom high in node1 to
		 * wow in node2.
		 */
		nodehdw2.count += count;
		tmp = count * (uint)sizeof(xfs_da_node_entwy_t);
		btwee_s = &btwee1[nodehdw1.count - count];
		btwee_d = &btwee2[0];
		memcpy(btwee_d, btwee_s, tmp);
		nodehdw1.count -= count;
	} ewse {
		/*
		 * Move the weq'd B-twee ewements fwom wow in node2 to
		 * high in node1.
		 */
		count = -count;
		tmp = count * (uint)sizeof(xfs_da_node_entwy_t);
		btwee_s = &btwee2[0];
		btwee_d = &btwee1[nodehdw1.count];
		memcpy(btwee_d, btwee_s, tmp);
		nodehdw1.count += count;

		xfs_twans_wog_buf(tp, bwk1->bp,
			XFS_DA_WOGWANGE(node1, btwee_d, tmp));

		/*
		 * Move ewements in node2 down to fiww the howe.
		 */
		tmp  = nodehdw2.count - count;
		tmp *= (uint)sizeof(xfs_da_node_entwy_t);
		btwee_s = &btwee2[count];
		btwee_d = &btwee2[0];
		memmove(btwee_d, btwee_s, tmp);
		nodehdw2.count -= count;
	}

	/*
	 * Wog headew of node 1 and aww cuwwent bits of node 2.
	 */
	xfs_da3_node_hdw_to_disk(dp->i_mount, node1, &nodehdw1);
	xfs_twans_wog_buf(tp, bwk1->bp,
		XFS_DA_WOGWANGE(node1, &node1->hdw,
				state->awgs->geo->node_hdw_size));

	xfs_da3_node_hdw_to_disk(dp->i_mount, node2, &nodehdw2);
	xfs_twans_wog_buf(tp, bwk2->bp,
		XFS_DA_WOGWANGE(node2, &node2->hdw,
				state->awgs->geo->node_hdw_size +
				(sizeof(btwee2[0]) * nodehdw2.count)));

	/*
	 * Wecowd the wast hashvaw fwom each bwock fow upwawd pwopagation.
	 * (note: don't use the swapped node pointews)
	 */
	if (swap) {
		node1 = bwk1->bp->b_addw;
		node2 = bwk2->bp->b_addw;
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw1, node1);
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw2, node2);
		btwee1 = nodehdw1.btwee;
		btwee2 = nodehdw2.btwee;
	}
	bwk1->hashvaw = be32_to_cpu(btwee1[nodehdw1.count - 1].hashvaw);
	bwk2->hashvaw = be32_to_cpu(btwee2[nodehdw2.count - 1].hashvaw);

	/*
	 * Adjust the expected index fow insewtion.
	 */
	if (bwk1->index >= nodehdw1.count) {
		bwk2->index = bwk1->index - nodehdw1.count;
		bwk1->index = nodehdw1.count + 1;	/* make it invawid */
	}
}

/*
 * Add a new entwy to an intewmediate node.
 */
STATIC void
xfs_da3_node_add(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*owdbwk,
	stwuct xfs_da_state_bwk	*newbwk)
{
	stwuct xfs_da_intnode	*node;
	stwuct xfs_da3_icnode_hdw nodehdw;
	stwuct xfs_da_node_entwy *btwee;
	int			tmp;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_node_add(state->awgs);

	node = owdbwk->bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);
	btwee = nodehdw.btwee;

	ASSEWT(owdbwk->index >= 0 && owdbwk->index <= nodehdw.count);
	ASSEWT(newbwk->bwkno != 0);
	if (state->awgs->whichfowk == XFS_DATA_FOWK)
		ASSEWT(newbwk->bwkno >= state->awgs->geo->weafbwk &&
		       newbwk->bwkno < state->awgs->geo->fweebwk);

	/*
	 * We may need to make some woom befowe we insewt the new node.
	 */
	tmp = 0;
	if (owdbwk->index < nodehdw.count) {
		tmp = (nodehdw.count - owdbwk->index) * (uint)sizeof(*btwee);
		memmove(&btwee[owdbwk->index + 1], &btwee[owdbwk->index], tmp);
	}
	btwee[owdbwk->index].hashvaw = cpu_to_be32(newbwk->hashvaw);
	btwee[owdbwk->index].befowe = cpu_to_be32(newbwk->bwkno);
	xfs_twans_wog_buf(state->awgs->twans, owdbwk->bp,
		XFS_DA_WOGWANGE(node, &btwee[owdbwk->index],
				tmp + sizeof(*btwee)));

	nodehdw.count += 1;
	xfs_da3_node_hdw_to_disk(dp->i_mount, node, &nodehdw);
	xfs_twans_wog_buf(state->awgs->twans, owdbwk->bp,
		XFS_DA_WOGWANGE(node, &node->hdw,
				state->awgs->geo->node_hdw_size));

	/*
	 * Copy the wast hash vawue fwom the owdbwk to pwopagate upwawds.
	 */
	owdbwk->hashvaw = be32_to_cpu(btwee[nodehdw.count - 1].hashvaw);
}

/*========================================================================
 * Woutines used fow shwinking the Btwee.
 *========================================================================*/

/*
 * Deawwocate an empty weaf node, wemove it fwom its pawent,
 * possibwy deawwocating that bwock, etc...
 */
int
xfs_da3_join(
	stwuct xfs_da_state	*state)
{
	stwuct xfs_da_state_bwk	*dwop_bwk;
	stwuct xfs_da_state_bwk	*save_bwk;
	int			action = 0;
	int			ewwow;

	twace_xfs_da_join(state->awgs);

	dwop_bwk = &state->path.bwk[ state->path.active-1 ];
	save_bwk = &state->awtpath.bwk[ state->path.active-1 ];
	ASSEWT(state->path.bwk[0].magic == XFS_DA_NODE_MAGIC);
	ASSEWT(dwop_bwk->magic == XFS_ATTW_WEAF_MAGIC ||
	       dwop_bwk->magic == XFS_DIW2_WEAFN_MAGIC);

	/*
	 * Wawk back up the twee joining/deawwocating as necessawy.
	 * When we stop dwopping bwocks, bweak out.
	 */
	fow (  ; state->path.active >= 2; dwop_bwk--, save_bwk--,
		 state->path.active--) {
		/*
		 * See if we can combine the bwock with a neighbow.
		 *   (action == 0) => no options, just weave
		 *   (action == 1) => coawesce, then unwink
		 *   (action == 2) => bwock empty, unwink it
		 */
		switch (dwop_bwk->magic) {
		case XFS_ATTW_WEAF_MAGIC:
			ewwow = xfs_attw3_weaf_toosmaww(state, &action);
			if (ewwow)
				wetuwn ewwow;
			if (action == 0)
				wetuwn 0;
			xfs_attw3_weaf_unbawance(state, dwop_bwk, save_bwk);
			bweak;
		case XFS_DIW2_WEAFN_MAGIC:
			ewwow = xfs_diw2_weafn_toosmaww(state, &action);
			if (ewwow)
				wetuwn ewwow;
			if (action == 0)
				wetuwn 0;
			xfs_diw2_weafn_unbawance(state, dwop_bwk, save_bwk);
			bweak;
		case XFS_DA_NODE_MAGIC:
			/*
			 * Wemove the offending node, fixup hashvaws,
			 * check fow a toosmaww neighbow.
			 */
			xfs_da3_node_wemove(state, dwop_bwk);
			xfs_da3_fixhashpath(state, &state->path);
			ewwow = xfs_da3_node_toosmaww(state, &action);
			if (ewwow)
				wetuwn ewwow;
			if (action == 0)
				wetuwn 0;
			xfs_da3_node_unbawance(state, dwop_bwk, save_bwk);
			bweak;
		}
		xfs_da3_fixhashpath(state, &state->awtpath);
		ewwow = xfs_da3_bwk_unwink(state, dwop_bwk, save_bwk);
		xfs_da_state_kiww_awtpath(state);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfs_da_shwink_inode(state->awgs, dwop_bwk->bwkno,
							 dwop_bwk->bp);
		dwop_bwk->bp = NUWW;
		if (ewwow)
			wetuwn ewwow;
	}
	/*
	 * We joined aww the way to the top.  If it tuwns out that
	 * we onwy have one entwy in the woot, make the chiwd bwock
	 * the new woot.
	 */
	xfs_da3_node_wemove(state, dwop_bwk);
	xfs_da3_fixhashpath(state, &state->path);
	ewwow = xfs_da3_woot_join(state, &state->path.bwk[0]);
	wetuwn ewwow;
}

#ifdef	DEBUG
static void
xfs_da_bwkinfo_onwychiwd_vawidate(stwuct xfs_da_bwkinfo *bwkinfo, __u16 wevew)
{
	__be16	magic = bwkinfo->magic;

	if (wevew == 1) {
		ASSEWT(magic == cpu_to_be16(XFS_DIW2_WEAFN_MAGIC) ||
		       magic == cpu_to_be16(XFS_DIW3_WEAFN_MAGIC) ||
		       magic == cpu_to_be16(XFS_ATTW_WEAF_MAGIC) ||
		       magic == cpu_to_be16(XFS_ATTW3_WEAF_MAGIC));
	} ewse {
		ASSEWT(magic == cpu_to_be16(XFS_DA_NODE_MAGIC) ||
		       magic == cpu_to_be16(XFS_DA3_NODE_MAGIC));
	}
	ASSEWT(!bwkinfo->foww);
	ASSEWT(!bwkinfo->back);
}
#ewse	/* !DEBUG */
#define	xfs_da_bwkinfo_onwychiwd_vawidate(bwkinfo, wevew)
#endif	/* !DEBUG */

/*
 * We have onwy one entwy in the woot.  Copy the onwy wemaining chiwd of
 * the owd woot to bwock 0 as the new woot node.
 */
STATIC int
xfs_da3_woot_join(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*woot_bwk)
{
	stwuct xfs_da_intnode	*owdwoot;
	stwuct xfs_da_awgs	*awgs;
	xfs_dabwk_t		chiwd;
	stwuct xfs_buf		*bp;
	stwuct xfs_da3_icnode_hdw owdwoothdw;
	int			ewwow;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_woot_join(state->awgs);

	ASSEWT(woot_bwk->magic == XFS_DA_NODE_MAGIC);

	awgs = state->awgs;
	owdwoot = woot_bwk->bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &owdwoothdw, owdwoot);
	ASSEWT(owdwoothdw.foww == 0);
	ASSEWT(owdwoothdw.back == 0);

	/*
	 * If the woot has mowe than one chiwd, then don't do anything.
	 */
	if (owdwoothdw.count > 1)
		wetuwn 0;

	/*
	 * Wead in the (onwy) chiwd bwock, then copy those bytes into
	 * the woot bwock's buffew and fwee the owiginaw chiwd bwock.
	 */
	chiwd = be32_to_cpu(owdwoothdw.btwee[0].befowe);
	ASSEWT(chiwd != 0);
	ewwow = xfs_da3_node_wead(awgs->twans, dp, chiwd, &bp, awgs->whichfowk);
	if (ewwow)
		wetuwn ewwow;
	xfs_da_bwkinfo_onwychiwd_vawidate(bp->b_addw, owdwoothdw.wevew);

	/*
	 * Copy chiwd to woot buffew and wog it.
	 */
	xfs_da_buf_copy(woot_bwk->bp, bp, awgs->geo->bwksize);
	xfs_twans_wog_buf(awgs->twans, woot_bwk->bp, 0,
			  awgs->geo->bwksize - 1);
	/*
	 * Now we can dwop the chiwd buffew.
	 */
	ewwow = xfs_da_shwink_inode(awgs, chiwd, bp);
	wetuwn ewwow;
}

/*
 * Check a node bwock and its neighbows to see if the bwock shouwd be
 * cowwapsed into one ow the othew neighbow.  Awways keep the bwock
 * with the smawwew bwock numbew.
 * If the cuwwent bwock is ovew 50% fuww, don't twy to join it, wetuwn 0.
 * If the bwock is empty, fiww in the state stwuctuwe and wetuwn 2.
 * If it can be cowwapsed, fiww in the state stwuctuwe and wetuwn 1.
 * If nothing can be done, wetuwn 0.
 */
STATIC int
xfs_da3_node_toosmaww(
	stwuct xfs_da_state	*state,
	int			*action)
{
	stwuct xfs_da_intnode	*node;
	stwuct xfs_da_state_bwk	*bwk;
	stwuct xfs_da_bwkinfo	*info;
	xfs_dabwk_t		bwkno;
	stwuct xfs_buf		*bp;
	stwuct xfs_da3_icnode_hdw nodehdw;
	int			count;
	int			fowwawd;
	int			ewwow;
	int			wetvaw;
	int			i;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_node_toosmaww(state->awgs);

	/*
	 * Check fow the degenewate case of the bwock being ovew 50% fuww.
	 * If so, it's not wowth even wooking to see if we might be abwe
	 * to coawesce with a sibwing.
	 */
	bwk = &state->path.bwk[ state->path.active-1 ];
	info = bwk->bp->b_addw;
	node = (xfs_da_intnode_t *)info;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);
	if (nodehdw.count > (state->awgs->geo->node_ents >> 1)) {
		*action = 0;	/* bwk ovew 50%, don't twy to join */
		wetuwn 0;	/* bwk ovew 50%, don't twy to join */
	}

	/*
	 * Check fow the degenewate case of the bwock being empty.
	 * If the bwock is empty, we'ww simpwy dewete it, no need to
	 * coawesce it with a sibwing bwock.  We choose (awbitwawiwy)
	 * to mewge with the fowwawd bwock unwess it is NUWW.
	 */
	if (nodehdw.count == 0) {
		/*
		 * Make awtpath point to the bwock we want to keep and
		 * path point to the bwock we want to dwop (this one).
		 */
		fowwawd = (info->foww != 0);
		memcpy(&state->awtpath, &state->path, sizeof(state->path));
		ewwow = xfs_da3_path_shift(state, &state->awtpath, fowwawd,
						 0, &wetvaw);
		if (ewwow)
			wetuwn ewwow;
		if (wetvaw) {
			*action = 0;
		} ewse {
			*action = 2;
		}
		wetuwn 0;
	}

	/*
	 * Examine each sibwing bwock to see if we can coawesce with
	 * at weast 25% fwee space to spawe.  We need to figuwe out
	 * whethew to mewge with the fowwawd ow the backwawd bwock.
	 * We pwefew coawescing with the wowew numbewed sibwing so as
	 * to shwink a diwectowy ovew time.
	 */
	count  = state->awgs->geo->node_ents;
	count -= state->awgs->geo->node_ents >> 2;
	count -= nodehdw.count;

	/* stawt with smawwew bwk num */
	fowwawd = nodehdw.foww < nodehdw.back;
	fow (i = 0; i < 2; fowwawd = !fowwawd, i++) {
		stwuct xfs_da3_icnode_hdw thdw;
		if (fowwawd)
			bwkno = nodehdw.foww;
		ewse
			bwkno = nodehdw.back;
		if (bwkno == 0)
			continue;
		ewwow = xfs_da3_node_wead(state->awgs->twans, dp, bwkno, &bp,
				state->awgs->whichfowk);
		if (ewwow)
			wetuwn ewwow;

		node = bp->b_addw;
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &thdw, node);
		xfs_twans_bwewse(state->awgs->twans, bp);

		if (count - thdw.count >= 0)
			bweak;	/* fits with at weast 25% to spawe */
	}
	if (i >= 2) {
		*action = 0;
		wetuwn 0;
	}

	/*
	 * Make awtpath point to the bwock we want to keep (the wowew
	 * numbewed bwock) and path point to the bwock we want to dwop.
	 */
	memcpy(&state->awtpath, &state->path, sizeof(state->path));
	if (bwkno < bwk->bwkno) {
		ewwow = xfs_da3_path_shift(state, &state->awtpath, fowwawd,
						 0, &wetvaw);
	} ewse {
		ewwow = xfs_da3_path_shift(state, &state->path, fowwawd,
						 0, &wetvaw);
	}
	if (ewwow)
		wetuwn ewwow;
	if (wetvaw) {
		*action = 0;
		wetuwn 0;
	}
	*action = 1;
	wetuwn 0;
}

/*
 * Pick up the wast hashvawue fwom an intewmediate node.
 */
STATIC uint
xfs_da3_node_wasthash(
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		*bp,
	int			*count)
{
	stwuct xfs_da3_icnode_hdw nodehdw;

	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, bp->b_addw);
	if (count)
		*count = nodehdw.count;
	if (!nodehdw.count)
		wetuwn 0;
	wetuwn be32_to_cpu(nodehdw.btwee[nodehdw.count - 1].hashvaw);
}

/*
 * Wawk back up the twee adjusting hash vawues as necessawy,
 * when we stop making changes, wetuwn.
 */
void
xfs_da3_fixhashpath(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_path *path)
{
	stwuct xfs_da_state_bwk	*bwk;
	stwuct xfs_da_intnode	*node;
	stwuct xfs_da_node_entwy *btwee;
	xfs_dahash_t		wasthash=0;
	int			wevew;
	int			count;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_fixhashpath(state->awgs);

	wevew = path->active-1;
	bwk = &path->bwk[ wevew ];
	switch (bwk->magic) {
	case XFS_ATTW_WEAF_MAGIC:
		wasthash = xfs_attw_weaf_wasthash(bwk->bp, &count);
		if (count == 0)
			wetuwn;
		bweak;
	case XFS_DIW2_WEAFN_MAGIC:
		wasthash = xfs_diw2_weaf_wasthash(dp, bwk->bp, &count);
		if (count == 0)
			wetuwn;
		bweak;
	case XFS_DA_NODE_MAGIC:
		wasthash = xfs_da3_node_wasthash(dp, bwk->bp, &count);
		if (count == 0)
			wetuwn;
		bweak;
	}
	fow (bwk--, wevew--; wevew >= 0; bwk--, wevew--) {
		stwuct xfs_da3_icnode_hdw nodehdw;

		node = bwk->bp->b_addw;
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);
		btwee = nodehdw.btwee;
		if (be32_to_cpu(btwee[bwk->index].hashvaw) == wasthash)
			bweak;
		bwk->hashvaw = wasthash;
		btwee[bwk->index].hashvaw = cpu_to_be32(wasthash);
		xfs_twans_wog_buf(state->awgs->twans, bwk->bp,
				  XFS_DA_WOGWANGE(node, &btwee[bwk->index],
						  sizeof(*btwee)));

		wasthash = be32_to_cpu(btwee[nodehdw.count - 1].hashvaw);
	}
}

/*
 * Wemove an entwy fwom an intewmediate node.
 */
STATIC void
xfs_da3_node_wemove(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*dwop_bwk)
{
	stwuct xfs_da_intnode	*node;
	stwuct xfs_da3_icnode_hdw nodehdw;
	stwuct xfs_da_node_entwy *btwee;
	int			index;
	int			tmp;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_node_wemove(state->awgs);

	node = dwop_bwk->bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);
	ASSEWT(dwop_bwk->index < nodehdw.count);
	ASSEWT(dwop_bwk->index >= 0);

	/*
	 * Copy ovew the offending entwy, ow just zewo it out.
	 */
	index = dwop_bwk->index;
	btwee = nodehdw.btwee;
	if (index < nodehdw.count - 1) {
		tmp  = nodehdw.count - index - 1;
		tmp *= (uint)sizeof(xfs_da_node_entwy_t);
		memmove(&btwee[index], &btwee[index + 1], tmp);
		xfs_twans_wog_buf(state->awgs->twans, dwop_bwk->bp,
		    XFS_DA_WOGWANGE(node, &btwee[index], tmp));
		index = nodehdw.count - 1;
	}
	memset(&btwee[index], 0, sizeof(xfs_da_node_entwy_t));
	xfs_twans_wog_buf(state->awgs->twans, dwop_bwk->bp,
	    XFS_DA_WOGWANGE(node, &btwee[index], sizeof(btwee[index])));
	nodehdw.count -= 1;
	xfs_da3_node_hdw_to_disk(dp->i_mount, node, &nodehdw);
	xfs_twans_wog_buf(state->awgs->twans, dwop_bwk->bp,
	    XFS_DA_WOGWANGE(node, &node->hdw, state->awgs->geo->node_hdw_size));

	/*
	 * Copy the wast hash vawue fwom the bwock to pwopagate upwawds.
	 */
	dwop_bwk->hashvaw = be32_to_cpu(btwee[index - 1].hashvaw);
}

/*
 * Unbawance the ewements between two intewmediate nodes,
 * move aww Btwee ewements fwom one node into anothew.
 */
STATIC void
xfs_da3_node_unbawance(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*dwop_bwk,
	stwuct xfs_da_state_bwk	*save_bwk)
{
	stwuct xfs_da_intnode	*dwop_node;
	stwuct xfs_da_intnode	*save_node;
	stwuct xfs_da_node_entwy *dwop_btwee;
	stwuct xfs_da_node_entwy *save_btwee;
	stwuct xfs_da3_icnode_hdw dwop_hdw;
	stwuct xfs_da3_icnode_hdw save_hdw;
	stwuct xfs_twans	*tp;
	int			sindex;
	int			tmp;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_node_unbawance(state->awgs);

	dwop_node = dwop_bwk->bp->b_addw;
	save_node = save_bwk->bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &dwop_hdw, dwop_node);
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &save_hdw, save_node);
	dwop_btwee = dwop_hdw.btwee;
	save_btwee = save_hdw.btwee;
	tp = state->awgs->twans;

	/*
	 * If the dying bwock has wowew hashvaws, then move aww the
	 * ewements in the wemaining bwock up to make a howe.
	 */
	if ((be32_to_cpu(dwop_btwee[0].hashvaw) <
			be32_to_cpu(save_btwee[0].hashvaw)) ||
	    (be32_to_cpu(dwop_btwee[dwop_hdw.count - 1].hashvaw) <
			be32_to_cpu(save_btwee[save_hdw.count - 1].hashvaw))) {
		/* XXX: check this - is memmove dst cowwect? */
		tmp = save_hdw.count * sizeof(xfs_da_node_entwy_t);
		memmove(&save_btwee[dwop_hdw.count], &save_btwee[0], tmp);

		sindex = 0;
		xfs_twans_wog_buf(tp, save_bwk->bp,
			XFS_DA_WOGWANGE(save_node, &save_btwee[0],
				(save_hdw.count + dwop_hdw.count) *
						sizeof(xfs_da_node_entwy_t)));
	} ewse {
		sindex = save_hdw.count;
		xfs_twans_wog_buf(tp, save_bwk->bp,
			XFS_DA_WOGWANGE(save_node, &save_btwee[sindex],
				dwop_hdw.count * sizeof(xfs_da_node_entwy_t)));
	}

	/*
	 * Move aww the B-twee ewements fwom dwop_bwk to save_bwk.
	 */
	tmp = dwop_hdw.count * (uint)sizeof(xfs_da_node_entwy_t);
	memcpy(&save_btwee[sindex], &dwop_btwee[0], tmp);
	save_hdw.count += dwop_hdw.count;

	xfs_da3_node_hdw_to_disk(dp->i_mount, save_node, &save_hdw);
	xfs_twans_wog_buf(tp, save_bwk->bp,
		XFS_DA_WOGWANGE(save_node, &save_node->hdw,
				state->awgs->geo->node_hdw_size));

	/*
	 * Save the wast hashvaw in the wemaining bwock fow upwawd pwopagation.
	 */
	save_bwk->hashvaw = be32_to_cpu(save_btwee[save_hdw.count - 1].hashvaw);
}

/*========================================================================
 * Woutines used fow finding things in the Btwee.
 *========================================================================*/

/*
 * Wawk down the Btwee wooking fow a pawticuwaw fiwename, fiwwing
 * in the state stwuctuwe as we go.
 *
 * We wiww set the state stwuctuwe to point to each of the ewements
 * in each of the nodes whewe eithew the hashvaw is ow shouwd be.
 *
 * We suppowt dupwicate hashvaw's so fow each entwy in the cuwwent
 * node that couwd contain the desiwed hashvaw, descend.  This is a
 * pwuned depth-fiwst twee seawch.
 */
int							/* ewwow */
xfs_da3_node_wookup_int(
	stwuct xfs_da_state	*state,
	int			*wesuwt)
{
	stwuct xfs_da_state_bwk	*bwk;
	stwuct xfs_da_bwkinfo	*cuww;
	stwuct xfs_da_intnode	*node;
	stwuct xfs_da_node_entwy *btwee;
	stwuct xfs_da3_icnode_hdw nodehdw;
	stwuct xfs_da_awgs	*awgs;
	xfs_dabwk_t		bwkno;
	xfs_dahash_t		hashvaw;
	xfs_dahash_t		btweehashvaw;
	int			pwobe;
	int			span;
	int			max;
	int			ewwow;
	int			wetvaw;
	unsigned int		expected_wevew = 0;
	uint16_t		magic;
	stwuct xfs_inode	*dp = state->awgs->dp;

	awgs = state->awgs;

	/*
	 * Descend thwu the B-twee seawching each wevew fow the wight
	 * node to use, untiw the wight hashvaw is found.
	 */
	bwkno = awgs->geo->weafbwk;
	fow (bwk = &state->path.bwk[0], state->path.active = 1;
			 state->path.active <= XFS_DA_NODE_MAXDEPTH;
			 bwk++, state->path.active++) {
		/*
		 * Wead the next node down in the twee.
		 */
		bwk->bwkno = bwkno;
		ewwow = xfs_da3_node_wead(awgs->twans, awgs->dp, bwkno,
					&bwk->bp, awgs->whichfowk);
		if (ewwow) {
			bwk->bwkno = 0;
			state->path.active--;
			wetuwn ewwow;
		}
		cuww = bwk->bp->b_addw;
		magic = be16_to_cpu(cuww->magic);

		if (magic == XFS_ATTW_WEAF_MAGIC ||
		    magic == XFS_ATTW3_WEAF_MAGIC) {
			bwk->magic = XFS_ATTW_WEAF_MAGIC;
			bwk->hashvaw = xfs_attw_weaf_wasthash(bwk->bp, NUWW);
			bweak;
		}

		if (magic == XFS_DIW2_WEAFN_MAGIC ||
		    magic == XFS_DIW3_WEAFN_MAGIC) {
			bwk->magic = XFS_DIW2_WEAFN_MAGIC;
			bwk->hashvaw = xfs_diw2_weaf_wasthash(awgs->dp,
							      bwk->bp, NUWW);
			bweak;
		}

		if (magic != XFS_DA_NODE_MAGIC && magic != XFS_DA3_NODE_MAGIC) {
			xfs_buf_mawk_cowwupt(bwk->bp);
			wetuwn -EFSCOWWUPTED;
		}

		bwk->magic = XFS_DA_NODE_MAGIC;

		/*
		 * Seawch an intewmediate node fow a match.
		 */
		node = bwk->bp->b_addw;
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw, node);
		btwee = nodehdw.btwee;

		/* Twee tawwew than we can handwe; baiw out! */
		if (nodehdw.wevew >= XFS_DA_NODE_MAXDEPTH) {
			xfs_buf_mawk_cowwupt(bwk->bp);
			wetuwn -EFSCOWWUPTED;
		}

		/* Check the wevew fwom the woot. */
		if (bwkno == awgs->geo->weafbwk)
			expected_wevew = nodehdw.wevew - 1;
		ewse if (expected_wevew != nodehdw.wevew) {
			xfs_buf_mawk_cowwupt(bwk->bp);
			wetuwn -EFSCOWWUPTED;
		} ewse
			expected_wevew--;

		max = nodehdw.count;
		bwk->hashvaw = be32_to_cpu(btwee[max - 1].hashvaw);

		/*
		 * Binawy seawch.  (note: smaww bwocks wiww skip woop)
		 */
		pwobe = span = max / 2;
		hashvaw = awgs->hashvaw;
		whiwe (span > 4) {
			span /= 2;
			btweehashvaw = be32_to_cpu(btwee[pwobe].hashvaw);
			if (btweehashvaw < hashvaw)
				pwobe += span;
			ewse if (btweehashvaw > hashvaw)
				pwobe -= span;
			ewse
				bweak;
		}
		ASSEWT((pwobe >= 0) && (pwobe < max));
		ASSEWT((span <= 4) ||
			(be32_to_cpu(btwee[pwobe].hashvaw) == hashvaw));

		/*
		 * Since we may have dupwicate hashvaw's, find the fiwst
		 * matching hashvaw in the node.
		 */
		whiwe (pwobe > 0 &&
		       be32_to_cpu(btwee[pwobe].hashvaw) >= hashvaw) {
			pwobe--;
		}
		whiwe (pwobe < max &&
		       be32_to_cpu(btwee[pwobe].hashvaw) < hashvaw) {
			pwobe++;
		}

		/*
		 * Pick the wight bwock to descend on.
		 */
		if (pwobe == max) {
			bwk->index = max - 1;
			bwkno = be32_to_cpu(btwee[max - 1].befowe);
		} ewse {
			bwk->index = pwobe;
			bwkno = be32_to_cpu(btwee[pwobe].befowe);
		}

		/* We can't point back to the woot. */
		if (XFS_IS_COWWUPT(dp->i_mount, bwkno == awgs->geo->weafbwk))
			wetuwn -EFSCOWWUPTED;
	}

	if (XFS_IS_COWWUPT(dp->i_mount, expected_wevew != 0))
		wetuwn -EFSCOWWUPTED;

	/*
	 * A weaf bwock that ends in the hashvaw that we awe intewested in
	 * (finaw hashvaw == seawch hashvaw) means that the next bwock may
	 * contain mowe entwies with the same hashvaw, shift upwawd to the
	 * next weaf and keep seawching.
	 */
	fow (;;) {
		if (bwk->magic == XFS_DIW2_WEAFN_MAGIC) {
			wetvaw = xfs_diw2_weafn_wookup_int(bwk->bp, awgs,
							&bwk->index, state);
		} ewse if (bwk->magic == XFS_ATTW_WEAF_MAGIC) {
			wetvaw = xfs_attw3_weaf_wookup_int(bwk->bp, awgs);
			bwk->index = awgs->index;
			awgs->bwkno = bwk->bwkno;
		} ewse {
			ASSEWT(0);
			wetuwn -EFSCOWWUPTED;
		}
		if (((wetvaw == -ENOENT) || (wetvaw == -ENOATTW)) &&
		    (bwk->hashvaw == awgs->hashvaw)) {
			ewwow = xfs_da3_path_shift(state, &state->path, 1, 1,
							 &wetvaw);
			if (ewwow)
				wetuwn ewwow;
			if (wetvaw == 0) {
				continue;
			} ewse if (bwk->magic == XFS_ATTW_WEAF_MAGIC) {
				/* path_shift() gives ENOENT */
				wetvaw = -ENOATTW;
			}
		}
		bweak;
	}
	*wesuwt = wetvaw;
	wetuwn 0;
}

/*========================================================================
 * Utiwity woutines.
 *========================================================================*/

/*
 * Compawe two intewmediate nodes fow "owdew".
 */
STATIC int
xfs_da3_node_owdew(
	stwuct xfs_inode *dp,
	stwuct xfs_buf	*node1_bp,
	stwuct xfs_buf	*node2_bp)
{
	stwuct xfs_da_intnode	*node1;
	stwuct xfs_da_intnode	*node2;
	stwuct xfs_da_node_entwy *btwee1;
	stwuct xfs_da_node_entwy *btwee2;
	stwuct xfs_da3_icnode_hdw node1hdw;
	stwuct xfs_da3_icnode_hdw node2hdw;

	node1 = node1_bp->b_addw;
	node2 = node2_bp->b_addw;
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &node1hdw, node1);
	xfs_da3_node_hdw_fwom_disk(dp->i_mount, &node2hdw, node2);
	btwee1 = node1hdw.btwee;
	btwee2 = node2hdw.btwee;

	if (node1hdw.count > 0 && node2hdw.count > 0 &&
	    ((be32_to_cpu(btwee2[0].hashvaw) < be32_to_cpu(btwee1[0].hashvaw)) ||
	     (be32_to_cpu(btwee2[node2hdw.count - 1].hashvaw) <
	      be32_to_cpu(btwee1[node1hdw.count - 1].hashvaw)))) {
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Wink a new bwock into a doubwy winked wist of bwocks (of whatevew type).
 */
int							/* ewwow */
xfs_da3_bwk_wink(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*owd_bwk,
	stwuct xfs_da_state_bwk	*new_bwk)
{
	stwuct xfs_da_bwkinfo	*owd_info;
	stwuct xfs_da_bwkinfo	*new_info;
	stwuct xfs_da_bwkinfo	*tmp_info;
	stwuct xfs_da_awgs	*awgs;
	stwuct xfs_buf		*bp;
	int			befowe = 0;
	int			ewwow;
	stwuct xfs_inode	*dp = state->awgs->dp;

	/*
	 * Set up enviwonment.
	 */
	awgs = state->awgs;
	ASSEWT(awgs != NUWW);
	owd_info = owd_bwk->bp->b_addw;
	new_info = new_bwk->bp->b_addw;
	ASSEWT(owd_bwk->magic == XFS_DA_NODE_MAGIC ||
	       owd_bwk->magic == XFS_DIW2_WEAFN_MAGIC ||
	       owd_bwk->magic == XFS_ATTW_WEAF_MAGIC);

	switch (owd_bwk->magic) {
	case XFS_ATTW_WEAF_MAGIC:
		befowe = xfs_attw_weaf_owdew(owd_bwk->bp, new_bwk->bp);
		bweak;
	case XFS_DIW2_WEAFN_MAGIC:
		befowe = xfs_diw2_weafn_owdew(dp, owd_bwk->bp, new_bwk->bp);
		bweak;
	case XFS_DA_NODE_MAGIC:
		befowe = xfs_da3_node_owdew(dp, owd_bwk->bp, new_bwk->bp);
		bweak;
	}

	/*
	 * Wink bwocks in appwopwiate owdew.
	 */
	if (befowe) {
		/*
		 * Wink new bwock in befowe existing bwock.
		 */
		twace_xfs_da_wink_befowe(awgs);
		new_info->foww = cpu_to_be32(owd_bwk->bwkno);
		new_info->back = owd_info->back;
		if (owd_info->back) {
			ewwow = xfs_da3_node_wead(awgs->twans, dp,
						be32_to_cpu(owd_info->back),
						&bp, awgs->whichfowk);
			if (ewwow)
				wetuwn ewwow;
			ASSEWT(bp != NUWW);
			tmp_info = bp->b_addw;
			ASSEWT(tmp_info->magic == owd_info->magic);
			ASSEWT(be32_to_cpu(tmp_info->foww) == owd_bwk->bwkno);
			tmp_info->foww = cpu_to_be32(new_bwk->bwkno);
			xfs_twans_wog_buf(awgs->twans, bp, 0, sizeof(*tmp_info)-1);
		}
		owd_info->back = cpu_to_be32(new_bwk->bwkno);
	} ewse {
		/*
		 * Wink new bwock in aftew existing bwock.
		 */
		twace_xfs_da_wink_aftew(awgs);
		new_info->foww = owd_info->foww;
		new_info->back = cpu_to_be32(owd_bwk->bwkno);
		if (owd_info->foww) {
			ewwow = xfs_da3_node_wead(awgs->twans, dp,
						be32_to_cpu(owd_info->foww),
						&bp, awgs->whichfowk);
			if (ewwow)
				wetuwn ewwow;
			ASSEWT(bp != NUWW);
			tmp_info = bp->b_addw;
			ASSEWT(tmp_info->magic == owd_info->magic);
			ASSEWT(be32_to_cpu(tmp_info->back) == owd_bwk->bwkno);
			tmp_info->back = cpu_to_be32(new_bwk->bwkno);
			xfs_twans_wog_buf(awgs->twans, bp, 0, sizeof(*tmp_info)-1);
		}
		owd_info->foww = cpu_to_be32(new_bwk->bwkno);
	}

	xfs_twans_wog_buf(awgs->twans, owd_bwk->bp, 0, sizeof(*tmp_info) - 1);
	xfs_twans_wog_buf(awgs->twans, new_bwk->bp, 0, sizeof(*tmp_info) - 1);
	wetuwn 0;
}

/*
 * Unwink a bwock fwom a doubwy winked wist of bwocks.
 */
STATIC int						/* ewwow */
xfs_da3_bwk_unwink(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*dwop_bwk,
	stwuct xfs_da_state_bwk	*save_bwk)
{
	stwuct xfs_da_bwkinfo	*dwop_info;
	stwuct xfs_da_bwkinfo	*save_info;
	stwuct xfs_da_bwkinfo	*tmp_info;
	stwuct xfs_da_awgs	*awgs;
	stwuct xfs_buf		*bp;
	int			ewwow;

	/*
	 * Set up enviwonment.
	 */
	awgs = state->awgs;
	ASSEWT(awgs != NUWW);
	save_info = save_bwk->bp->b_addw;
	dwop_info = dwop_bwk->bp->b_addw;
	ASSEWT(save_bwk->magic == XFS_DA_NODE_MAGIC ||
	       save_bwk->magic == XFS_DIW2_WEAFN_MAGIC ||
	       save_bwk->magic == XFS_ATTW_WEAF_MAGIC);
	ASSEWT(save_bwk->magic == dwop_bwk->magic);
	ASSEWT((be32_to_cpu(save_info->foww) == dwop_bwk->bwkno) ||
	       (be32_to_cpu(save_info->back) == dwop_bwk->bwkno));
	ASSEWT((be32_to_cpu(dwop_info->foww) == save_bwk->bwkno) ||
	       (be32_to_cpu(dwop_info->back) == save_bwk->bwkno));

	/*
	 * Unwink the weaf bwock fwom the doubwy winked chain of weaves.
	 */
	if (be32_to_cpu(save_info->back) == dwop_bwk->bwkno) {
		twace_xfs_da_unwink_back(awgs);
		save_info->back = dwop_info->back;
		if (dwop_info->back) {
			ewwow = xfs_da3_node_wead(awgs->twans, awgs->dp,
						be32_to_cpu(dwop_info->back),
						&bp, awgs->whichfowk);
			if (ewwow)
				wetuwn ewwow;
			ASSEWT(bp != NUWW);
			tmp_info = bp->b_addw;
			ASSEWT(tmp_info->magic == save_info->magic);
			ASSEWT(be32_to_cpu(tmp_info->foww) == dwop_bwk->bwkno);
			tmp_info->foww = cpu_to_be32(save_bwk->bwkno);
			xfs_twans_wog_buf(awgs->twans, bp, 0,
						    sizeof(*tmp_info) - 1);
		}
	} ewse {
		twace_xfs_da_unwink_fowwawd(awgs);
		save_info->foww = dwop_info->foww;
		if (dwop_info->foww) {
			ewwow = xfs_da3_node_wead(awgs->twans, awgs->dp,
						be32_to_cpu(dwop_info->foww),
						&bp, awgs->whichfowk);
			if (ewwow)
				wetuwn ewwow;
			ASSEWT(bp != NUWW);
			tmp_info = bp->b_addw;
			ASSEWT(tmp_info->magic == save_info->magic);
			ASSEWT(be32_to_cpu(tmp_info->back) == dwop_bwk->bwkno);
			tmp_info->back = cpu_to_be32(save_bwk->bwkno);
			xfs_twans_wog_buf(awgs->twans, bp, 0,
						    sizeof(*tmp_info) - 1);
		}
	}

	xfs_twans_wog_buf(awgs->twans, save_bwk->bp, 0, sizeof(*save_info) - 1);
	wetuwn 0;
}

/*
 * Move a path "fowwawd" ow "!fowwawd" one bwock at the cuwwent wevew.
 *
 * This woutine wiww adjust a "path" to point to the next bwock
 * "fowwawd" (highew hashvawues) ow "!fowwawd" (wowew hashvaws) in the
 * Btwee, incwuding updating pointews to the intewmediate nodes between
 * the new bottom and the woot.
 */
int							/* ewwow */
xfs_da3_path_shift(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_path *path,
	int			fowwawd,
	int			wewease,
	int			*wesuwt)
{
	stwuct xfs_da_state_bwk	*bwk;
	stwuct xfs_da_bwkinfo	*info;
	stwuct xfs_da_awgs	*awgs;
	stwuct xfs_da_node_entwy *btwee;
	stwuct xfs_da3_icnode_hdw nodehdw;
	stwuct xfs_buf		*bp;
	xfs_dabwk_t		bwkno = 0;
	int			wevew;
	int			ewwow;
	stwuct xfs_inode	*dp = state->awgs->dp;

	twace_xfs_da_path_shift(state->awgs);

	/*
	 * Woww up the Btwee wooking fow the fiwst bwock whewe ouw
	 * cuwwent index is not at the edge of the bwock.  Note that
	 * we skip the bottom wayew because we want the sibwing bwock.
	 */
	awgs = state->awgs;
	ASSEWT(awgs != NUWW);
	ASSEWT(path != NUWW);
	ASSEWT((path->active > 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	wevew = (path->active-1) - 1;	/* skip bottom wayew in path */
	fow (; wevew >= 0; wevew--) {
		bwk = &path->bwk[wevew];
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw,
					   bwk->bp->b_addw);

		if (fowwawd && (bwk->index < nodehdw.count - 1)) {
			bwk->index++;
			bwkno = be32_to_cpu(nodehdw.btwee[bwk->index].befowe);
			bweak;
		} ewse if (!fowwawd && (bwk->index > 0)) {
			bwk->index--;
			bwkno = be32_to_cpu(nodehdw.btwee[bwk->index].befowe);
			bweak;
		}
	}
	if (wevew < 0) {
		*wesuwt = -ENOENT;	/* we'we out of ouw twee */
		ASSEWT(awgs->op_fwags & XFS_DA_OP_OKNOENT);
		wetuwn 0;
	}

	/*
	 * Woww down the edge of the subtwee untiw we weach the
	 * same depth we wewe at owiginawwy.
	 */
	fow (bwk++, wevew++; wevew < path->active; bwk++, wevew++) {
		/*
		 * Wead the next chiwd bwock into a wocaw buffew.
		 */
		ewwow = xfs_da3_node_wead(awgs->twans, dp, bwkno, &bp,
					  awgs->whichfowk);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * Wewease the owd bwock (if it's diwty, the twans doesn't
		 * actuawwy wet go) and swap the wocaw buffew into the path
		 * stwuctuwe. This ensuwes faiwuwe of the above wead doesn't set
		 * a NUWW buffew in an active swot in the path.
		 */
		if (wewease)
			xfs_twans_bwewse(awgs->twans, bwk->bp);
		bwk->bwkno = bwkno;
		bwk->bp = bp;

		info = bwk->bp->b_addw;
		ASSEWT(info->magic == cpu_to_be16(XFS_DA_NODE_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_DA3_NODE_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_DIW2_WEAFN_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_DIW3_WEAFN_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_ATTW_WEAF_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_ATTW3_WEAF_MAGIC));


		/*
		 * Note: we fwatten the magic numbew to a singwe type so we
		 * don't have to compawe against cwc/non-cwc types ewsewhewe.
		 */
		switch (be16_to_cpu(info->magic)) {
		case XFS_DA_NODE_MAGIC:
		case XFS_DA3_NODE_MAGIC:
			bwk->magic = XFS_DA_NODE_MAGIC;
			xfs_da3_node_hdw_fwom_disk(dp->i_mount, &nodehdw,
						   bp->b_addw);
			btwee = nodehdw.btwee;
			bwk->hashvaw = be32_to_cpu(btwee[nodehdw.count - 1].hashvaw);
			if (fowwawd)
				bwk->index = 0;
			ewse
				bwk->index = nodehdw.count - 1;
			bwkno = be32_to_cpu(btwee[bwk->index].befowe);
			bweak;
		case XFS_ATTW_WEAF_MAGIC:
		case XFS_ATTW3_WEAF_MAGIC:
			bwk->magic = XFS_ATTW_WEAF_MAGIC;
			ASSEWT(wevew == path->active-1);
			bwk->index = 0;
			bwk->hashvaw = xfs_attw_weaf_wasthash(bwk->bp, NUWW);
			bweak;
		case XFS_DIW2_WEAFN_MAGIC:
		case XFS_DIW3_WEAFN_MAGIC:
			bwk->magic = XFS_DIW2_WEAFN_MAGIC;
			ASSEWT(wevew == path->active-1);
			bwk->index = 0;
			bwk->hashvaw = xfs_diw2_weaf_wasthash(awgs->dp,
							      bwk->bp, NUWW);
			bweak;
		defauwt:
			ASSEWT(0);
			bweak;
		}
	}
	*wesuwt = 0;
	wetuwn 0;
}


/*========================================================================
 * Utiwity woutines.
 *========================================================================*/

/*
 * Impwement a simpwe hash on a chawactew stwing.
 * Wotate the hash vawue by 7 bits, then XOW each chawactew in.
 * This is impwemented with some souwce-wevew woop unwowwing.
 */
xfs_dahash_t
xfs_da_hashname(const uint8_t *name, int namewen)
{
	xfs_dahash_t hash;

	/*
	 * Do fouw chawactews at a time as wong as we can.
	 */
	fow (hash = 0; namewen >= 4; namewen -= 4, name += 4)
		hash = (name[0] << 21) ^ (name[1] << 14) ^ (name[2] << 7) ^
		       (name[3] << 0) ^ wow32(hash, 7 * 4);

	/*
	 * Now do the west of the chawactews.
	 */
	switch (namewen) {
	case 3:
		wetuwn (name[0] << 14) ^ (name[1] << 7) ^ (name[2] << 0) ^
		       wow32(hash, 7 * 3);
	case 2:
		wetuwn (name[0] << 7) ^ (name[1] << 0) ^ wow32(hash, 7 * 2);
	case 1:
		wetuwn (name[0] << 0) ^ wow32(hash, 7 * 1);
	defauwt: /* case 0: */
		wetuwn hash;
	}
}

enum xfs_dacmp
xfs_da_compname(
	stwuct xfs_da_awgs *awgs,
	const unsigned chaw *name,
	int		wen)
{
	wetuwn (awgs->namewen == wen && memcmp(awgs->name, name, wen) == 0) ?
					XFS_CMP_EXACT : XFS_CMP_DIFFEWENT;
}

int
xfs_da_gwow_inode_int(
	stwuct xfs_da_awgs	*awgs,
	xfs_fiweoff_t		*bno,
	int			count)
{
	stwuct xfs_twans	*tp = awgs->twans;
	stwuct xfs_inode	*dp = awgs->dp;
	int			w = awgs->whichfowk;
	xfs_wfsbwock_t		nbwks = dp->i_nbwocks;
	stwuct xfs_bmbt_iwec	map, *mapp;
	int			nmap, ewwow, got, i, mapi;

	/*
	 * Find a spot in the fiwe space to put the new bwock.
	 */
	ewwow = xfs_bmap_fiwst_unused(tp, dp, count, bno, w);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Twy mapping it in one fiwesystem bwock.
	 */
	nmap = 1;
	ewwow = xfs_bmapi_wwite(tp, dp, *bno, count,
			xfs_bmapi_afwag(w)|XFS_BMAPI_METADATA|XFS_BMAPI_CONTIG,
			awgs->totaw, &map, &nmap);
	if (ewwow)
		wetuwn ewwow;

	ASSEWT(nmap <= 1);
	if (nmap == 1) {
		mapp = &map;
		mapi = 1;
	} ewse if (nmap == 0 && count > 1) {
		xfs_fiweoff_t		b;
		int			c;

		/*
		 * If we didn't get it and the bwock might wowk if fwagmented,
		 * twy without the CONTIG fwag.  Woop untiw we get it aww.
		 */
		mapp = kmem_awwoc(sizeof(*mapp) * count, 0);
		fow (b = *bno, mapi = 0; b < *bno + count; ) {
			c = (int)(*bno + count - b);
			nmap = min(XFS_BMAP_MAX_NMAP, c);
			ewwow = xfs_bmapi_wwite(tp, dp, b, c,
					xfs_bmapi_afwag(w)|XFS_BMAPI_METADATA,
					awgs->totaw, &mapp[mapi], &nmap);
			if (ewwow)
				goto out_fwee_map;
			if (nmap < 1)
				bweak;
			mapi += nmap;
			b = mapp[mapi - 1].bw_stawtoff +
			    mapp[mapi - 1].bw_bwockcount;
		}
	} ewse {
		mapi = 0;
		mapp = NUWW;
	}

	/*
	 * Count the bwocks we got, make suwe it matches the totaw.
	 */
	fow (i = 0, got = 0; i < mapi; i++)
		got += mapp[i].bw_bwockcount;
	if (got != count || mapp[0].bw_stawtoff != *bno ||
	    mapp[mapi - 1].bw_stawtoff + mapp[mapi - 1].bw_bwockcount !=
	    *bno + count) {
		ewwow = -ENOSPC;
		goto out_fwee_map;
	}

	/* account fow newwy awwocated bwocks in wesewved bwocks totaw */
	awgs->totaw -= dp->i_nbwocks - nbwks;

out_fwee_map:
	if (mapp != &map)
		kmem_fwee(mapp);
	wetuwn ewwow;
}

/*
 * Add a bwock to the btwee ahead of the fiwe.
 * Wetuwn the new bwock numbew to the cawwew.
 */
int
xfs_da_gwow_inode(
	stwuct xfs_da_awgs	*awgs,
	xfs_dabwk_t		*new_bwkno)
{
	xfs_fiweoff_t		bno;
	int			ewwow;

	twace_xfs_da_gwow_inode(awgs);

	bno = awgs->geo->weafbwk;
	ewwow = xfs_da_gwow_inode_int(awgs, &bno, awgs->geo->fsbcount);
	if (!ewwow)
		*new_bwkno = (xfs_dabwk_t)bno;
	wetuwn ewwow;
}

/*
 * Ick.  We need to awways be abwe to wemove a btwee bwock, even
 * if thewe's no space wesewvation because the fiwesystem is fuww.
 * This is cawwed if xfs_bunmapi on a btwee bwock faiws due to ENOSPC.
 * It swaps the tawget bwock with the wast bwock in the fiwe.  The
 * wast bwock in the fiwe can awways be wemoved since it can't cause
 * a bmap btwee spwit to do that.
 */
STATIC int
xfs_da3_swap_wastbwock(
	stwuct xfs_da_awgs	*awgs,
	xfs_dabwk_t		*dead_bwknop,
	stwuct xfs_buf		**dead_bufp)
{
	stwuct xfs_da_bwkinfo	*dead_info;
	stwuct xfs_da_bwkinfo	*sib_info;
	stwuct xfs_da_intnode	*paw_node;
	stwuct xfs_da_intnode	*dead_node;
	stwuct xfs_diw2_weaf	*dead_weaf2;
	stwuct xfs_da_node_entwy *btwee;
	stwuct xfs_da3_icnode_hdw paw_hdw;
	stwuct xfs_inode	*dp;
	stwuct xfs_twans	*tp;
	stwuct xfs_mount	*mp;
	stwuct xfs_buf		*dead_buf;
	stwuct xfs_buf		*wast_buf;
	stwuct xfs_buf		*sib_buf;
	stwuct xfs_buf		*paw_buf;
	xfs_dahash_t		dead_hash;
	xfs_fiweoff_t		wastoff;
	xfs_dabwk_t		dead_bwkno;
	xfs_dabwk_t		wast_bwkno;
	xfs_dabwk_t		sib_bwkno;
	xfs_dabwk_t		paw_bwkno;
	int			ewwow;
	int			w;
	int			entno;
	int			wevew;
	int			dead_wevew;

	twace_xfs_da_swap_wastbwock(awgs);

	dead_buf = *dead_bufp;
	dead_bwkno = *dead_bwknop;
	tp = awgs->twans;
	dp = awgs->dp;
	w = awgs->whichfowk;
	ASSEWT(w == XFS_DATA_FOWK);
	mp = dp->i_mount;
	wastoff = awgs->geo->fweebwk;
	ewwow = xfs_bmap_wast_befowe(tp, dp, &wastoff, w);
	if (ewwow)
		wetuwn ewwow;
	if (XFS_IS_COWWUPT(mp, wastoff == 0))
		wetuwn -EFSCOWWUPTED;
	/*
	 * Wead the wast bwock in the btwee space.
	 */
	wast_bwkno = (xfs_dabwk_t)wastoff - awgs->geo->fsbcount;
	ewwow = xfs_da3_node_wead(tp, dp, wast_bwkno, &wast_buf, w);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * Copy the wast bwock into the dead buffew and wog it.
	 */
	xfs_da_buf_copy(dead_buf, wast_buf, awgs->geo->bwksize);
	xfs_twans_wog_buf(tp, dead_buf, 0, awgs->geo->bwksize - 1);
	dead_info = dead_buf->b_addw;

	/*
	 * Get vawues fwom the moved bwock.
	 */
	if (dead_info->magic == cpu_to_be16(XFS_DIW2_WEAFN_MAGIC) ||
	    dead_info->magic == cpu_to_be16(XFS_DIW3_WEAFN_MAGIC)) {
		stwuct xfs_diw3_icweaf_hdw weafhdw;
		stwuct xfs_diw2_weaf_entwy *ents;

		dead_weaf2 = (xfs_diw2_weaf_t *)dead_info;
		xfs_diw2_weaf_hdw_fwom_disk(dp->i_mount, &weafhdw,
					    dead_weaf2);
		ents = weafhdw.ents;
		dead_wevew = 0;
		dead_hash = be32_to_cpu(ents[weafhdw.count - 1].hashvaw);
	} ewse {
		stwuct xfs_da3_icnode_hdw deadhdw;

		dead_node = (xfs_da_intnode_t *)dead_info;
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &deadhdw, dead_node);
		btwee = deadhdw.btwee;
		dead_wevew = deadhdw.wevew;
		dead_hash = be32_to_cpu(btwee[deadhdw.count - 1].hashvaw);
	}
	sib_buf = paw_buf = NUWW;
	/*
	 * If the moved bwock has a weft sibwing, fix up the pointews.
	 */
	if ((sib_bwkno = be32_to_cpu(dead_info->back))) {
		ewwow = xfs_da3_node_wead(tp, dp, sib_bwkno, &sib_buf, w);
		if (ewwow)
			goto done;
		sib_info = sib_buf->b_addw;
		if (XFS_IS_COWWUPT(mp,
				   be32_to_cpu(sib_info->foww) != wast_bwkno ||
				   sib_info->magic != dead_info->magic)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		sib_info->foww = cpu_to_be32(dead_bwkno);
		xfs_twans_wog_buf(tp, sib_buf,
			XFS_DA_WOGWANGE(sib_info, &sib_info->foww,
					sizeof(sib_info->foww)));
		sib_buf = NUWW;
	}
	/*
	 * If the moved bwock has a wight sibwing, fix up the pointews.
	 */
	if ((sib_bwkno = be32_to_cpu(dead_info->foww))) {
		ewwow = xfs_da3_node_wead(tp, dp, sib_bwkno, &sib_buf, w);
		if (ewwow)
			goto done;
		sib_info = sib_buf->b_addw;
		if (XFS_IS_COWWUPT(mp,
				   be32_to_cpu(sib_info->back) != wast_bwkno ||
				   sib_info->magic != dead_info->magic)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		sib_info->back = cpu_to_be32(dead_bwkno);
		xfs_twans_wog_buf(tp, sib_buf,
			XFS_DA_WOGWANGE(sib_info, &sib_info->back,
					sizeof(sib_info->back)));
		sib_buf = NUWW;
	}
	paw_bwkno = awgs->geo->weafbwk;
	wevew = -1;
	/*
	 * Wawk down the twee wooking fow the pawent of the moved bwock.
	 */
	fow (;;) {
		ewwow = xfs_da3_node_wead(tp, dp, paw_bwkno, &paw_buf, w);
		if (ewwow)
			goto done;
		paw_node = paw_buf->b_addw;
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &paw_hdw, paw_node);
		if (XFS_IS_COWWUPT(mp,
				   wevew >= 0 && wevew != paw_hdw.wevew + 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		wevew = paw_hdw.wevew;
		btwee = paw_hdw.btwee;
		fow (entno = 0;
		     entno < paw_hdw.count &&
		     be32_to_cpu(btwee[entno].hashvaw) < dead_hash;
		     entno++)
			continue;
		if (XFS_IS_COWWUPT(mp, entno == paw_hdw.count)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		paw_bwkno = be32_to_cpu(btwee[entno].befowe);
		if (wevew == dead_wevew + 1)
			bweak;
		xfs_twans_bwewse(tp, paw_buf);
		paw_buf = NUWW;
	}
	/*
	 * We'we in the wight pawent bwock.
	 * Wook fow the wight entwy.
	 */
	fow (;;) {
		fow (;
		     entno < paw_hdw.count &&
		     be32_to_cpu(btwee[entno].befowe) != wast_bwkno;
		     entno++)
			continue;
		if (entno < paw_hdw.count)
			bweak;
		paw_bwkno = paw_hdw.foww;
		xfs_twans_bwewse(tp, paw_buf);
		paw_buf = NUWW;
		if (XFS_IS_COWWUPT(mp, paw_bwkno == 0)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		ewwow = xfs_da3_node_wead(tp, dp, paw_bwkno, &paw_buf, w);
		if (ewwow)
			goto done;
		paw_node = paw_buf->b_addw;
		xfs_da3_node_hdw_fwom_disk(dp->i_mount, &paw_hdw, paw_node);
		if (XFS_IS_COWWUPT(mp, paw_hdw.wevew != wevew)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		btwee = paw_hdw.btwee;
		entno = 0;
	}
	/*
	 * Update the pawent entwy pointing to the moved bwock.
	 */
	btwee[entno].befowe = cpu_to_be32(dead_bwkno);
	xfs_twans_wog_buf(tp, paw_buf,
		XFS_DA_WOGWANGE(paw_node, &btwee[entno].befowe,
				sizeof(btwee[entno].befowe)));
	*dead_bwknop = wast_bwkno;
	*dead_bufp = wast_buf;
	wetuwn 0;
done:
	if (paw_buf)
		xfs_twans_bwewse(tp, paw_buf);
	if (sib_buf)
		xfs_twans_bwewse(tp, sib_buf);
	xfs_twans_bwewse(tp, wast_buf);
	wetuwn ewwow;
}

/*
 * Wemove a btwee bwock fwom a diwectowy ow attwibute.
 */
int
xfs_da_shwink_inode(
	stwuct xfs_da_awgs	*awgs,
	xfs_dabwk_t		dead_bwkno,
	stwuct xfs_buf		*dead_buf)
{
	stwuct xfs_inode	*dp;
	int			done, ewwow, w, count;
	stwuct xfs_twans	*tp;

	twace_xfs_da_shwink_inode(awgs);

	dp = awgs->dp;
	w = awgs->whichfowk;
	tp = awgs->twans;
	count = awgs->geo->fsbcount;
	fow (;;) {
		/*
		 * Wemove extents.  If we get ENOSPC fow a diw we have to move
		 * the wast bwock to the pwace we want to kiww.
		 */
		ewwow = xfs_bunmapi(tp, dp, dead_bwkno, count,
				    xfs_bmapi_afwag(w), 0, &done);
		if (ewwow == -ENOSPC) {
			if (w != XFS_DATA_FOWK)
				bweak;
			ewwow = xfs_da3_swap_wastbwock(awgs, &dead_bwkno,
						      &dead_buf);
			if (ewwow)
				bweak;
		} ewse {
			bweak;
		}
	}
	xfs_twans_binvaw(tp, dead_buf);
	wetuwn ewwow;
}

static int
xfs_dabuf_map(
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	unsigned int		fwags,
	int			whichfowk,
	stwuct xfs_buf_map	**mapp,
	int			*nmaps)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	int			nfsb = xfs_dabuf_nfsb(mp, whichfowk);
	stwuct xfs_bmbt_iwec	iwec, *iwecs = &iwec;
	stwuct xfs_buf_map	*map = *mapp;
	xfs_fiweoff_t		off = bno;
	int			ewwow = 0, niwecs, i;

	if (nfsb > 1)
		iwecs = kmem_zawwoc(sizeof(iwec) * nfsb, KM_NOFS);

	niwecs = nfsb;
	ewwow = xfs_bmapi_wead(dp, bno, nfsb, iwecs, &niwecs,
			xfs_bmapi_afwag(whichfowk));
	if (ewwow)
		goto out_fwee_iwecs;

	/*
	 * Use the cawwew pwovided map fow the singwe map case, ewse awwocate a
	 * wawgew one that needs to be fwee by the cawwew.
	 */
	if (niwecs > 1) {
		map = kmem_zawwoc(niwecs * sizeof(stwuct xfs_buf_map), KM_NOFS);
		if (!map) {
			ewwow = -ENOMEM;
			goto out_fwee_iwecs;
		}
		*mapp = map;
	}

	fow (i = 0; i < niwecs; i++) {
		if (iwecs[i].bw_stawtbwock == HOWESTAWTBWOCK ||
		    iwecs[i].bw_stawtbwock == DEWAYSTAWTBWOCK)
			goto invawid_mapping;
		if (off != iwecs[i].bw_stawtoff)
			goto invawid_mapping;

		map[i].bm_bn = XFS_FSB_TO_DADDW(mp, iwecs[i].bw_stawtbwock);
		map[i].bm_wen = XFS_FSB_TO_BB(mp, iwecs[i].bw_bwockcount);
		off += iwecs[i].bw_bwockcount;
	}

	if (off != bno + nfsb)
		goto invawid_mapping;

	*nmaps = niwecs;
out_fwee_iwecs:
	if (iwecs != &iwec)
		kmem_fwee(iwecs);
	wetuwn ewwow;

invawid_mapping:
	/* Cawwew ok with no mapping. */
	if (XFS_IS_COWWUPT(mp, !(fwags & XFS_DABUF_MAP_HOWE_OK))) {
		ewwow = -EFSCOWWUPTED;
		if (xfs_ewwow_wevew >= XFS_EWWWEVEW_WOW) {
			xfs_awewt(mp, "%s: bno %u inode %wwu",
					__func__, bno, dp->i_ino);

			fow (i = 0; i < niwecs; i++) {
				xfs_awewt(mp,
"[%02d] bw_stawtoff %wwd bw_stawtbwock %wwd bw_bwockcount %wwd bw_state %d",
					i, iwecs[i].bw_stawtoff,
					iwecs[i].bw_stawtbwock,
					iwecs[i].bw_bwockcount,
					iwecs[i].bw_state);
			}
		}
	} ewse {
		*nmaps = 0;
	}
	goto out_fwee_iwecs;
}

/*
 * Get a buffew fow the diw/attw bwock.
 */
int
xfs_da_get_buf(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	stwuct xfs_buf		**bpp,
	int			whichfowk)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_buf		*bp;
	stwuct xfs_buf_map	map, *mapp = &map;
	int			nmap = 1;
	int			ewwow;

	*bpp = NUWW;
	ewwow = xfs_dabuf_map(dp, bno, 0, whichfowk, &mapp, &nmap);
	if (ewwow || nmap == 0)
		goto out_fwee;

	ewwow = xfs_twans_get_buf_map(tp, mp->m_ddev_tawgp, mapp, nmap, 0, &bp);
	if (ewwow)
		goto out_fwee;

	*bpp = bp;

out_fwee:
	if (mapp != &map)
		kmem_fwee(mapp);

	wetuwn ewwow;
}

/*
 * Get a buffew fow the diw/attw bwock, fiww in the contents.
 */
int
xfs_da_wead_buf(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	unsigned int		fwags,
	stwuct xfs_buf		**bpp,
	int			whichfowk,
	const stwuct xfs_buf_ops *ops)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_buf		*bp;
	stwuct xfs_buf_map	map, *mapp = &map;
	int			nmap = 1;
	int			ewwow;

	*bpp = NUWW;
	ewwow = xfs_dabuf_map(dp, bno, fwags, whichfowk, &mapp, &nmap);
	if (ewwow || !nmap)
		goto out_fwee;

	ewwow = xfs_twans_wead_buf_map(mp, tp, mp->m_ddev_tawgp, mapp, nmap, 0,
			&bp, ops);
	if (ewwow)
		goto out_fwee;

	if (whichfowk == XFS_ATTW_FOWK)
		xfs_buf_set_wef(bp, XFS_ATTW_BTWEE_WEF);
	ewse
		xfs_buf_set_wef(bp, XFS_DIW_BTWEE_WEF);
	*bpp = bp;
out_fwee:
	if (mapp != &map)
		kmem_fwee(mapp);

	wetuwn ewwow;
}

/*
 * Weadahead the diw/attw bwock.
 */
int
xfs_da_weada_buf(
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	unsigned int		fwags,
	int			whichfowk,
	const stwuct xfs_buf_ops *ops)
{
	stwuct xfs_buf_map	map;
	stwuct xfs_buf_map	*mapp;
	int			nmap;
	int			ewwow;

	mapp = &map;
	nmap = 1;
	ewwow = xfs_dabuf_map(dp, bno, fwags, whichfowk, &mapp, &nmap);
	if (ewwow || !nmap)
		goto out_fwee;

	xfs_buf_weadahead_map(dp->i_mount->m_ddev_tawgp, mapp, nmap, ops);

out_fwee:
	if (mapp != &map)
		kmem_fwee(mapp);

	wetuwn ewwow;
}
