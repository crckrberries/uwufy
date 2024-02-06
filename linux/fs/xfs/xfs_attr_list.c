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
#incwude "xfs_da_fowmat.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_attw_sf.h"
#incwude "xfs_attw_weaf.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_diw2.h"

STATIC int
xfs_attw_showtfowm_compawe(const void *a, const void *b)
{
	xfs_attw_sf_sowt_t *sa, *sb;

	sa = (xfs_attw_sf_sowt_t *)a;
	sb = (xfs_attw_sf_sowt_t *)b;
	if (sa->hash < sb->hash) {
		wetuwn -1;
	} ewse if (sa->hash > sb->hash) {
		wetuwn 1;
	} ewse {
		wetuwn sa->entno - sb->entno;
	}
}

#define XFS_ISWESET_CUWSOW(cuwsow) \
	(!((cuwsow)->initted) && !((cuwsow)->hashvaw) && \
	 !((cuwsow)->bwkno) && !((cuwsow)->offset))
/*
 * Copy out entwies of showtfowm attwibute wists fow attw_wist().
 * Showtfowm attwibute wists awe not stowed in hashvaw sowted owdew.
 * If the output buffew is not wawge enough to howd them aww, then
 * we have to cawcuwate each entwies' hashvawue and sowt them befowe
 * we can begin wetuwning them to the usew.
 */
static int
xfs_attw_showtfowm_wist(
	stwuct xfs_attw_wist_context	*context)
{
	stwuct xfs_attwwist_cuwsow_kewn	*cuwsow = &context->cuwsow;
	stwuct xfs_inode		*dp = context->dp;
	stwuct xfs_attw_sf_sowt		*sbuf, *sbp;
	stwuct xfs_attw_sf_hdw		*sf = dp->i_af.if_data;
	stwuct xfs_attw_sf_entwy	*sfe;
	int				sbsize, nsbuf, count, i;
	int				ewwow = 0;

	ASSEWT(sf != NUWW);
	if (!sf->count)
		wetuwn 0;

	twace_xfs_attw_wist_sf(context);

	/*
	 * If the buffew is wawge enough and the cuwsow is at the stawt,
	 * do not bothew with sowting since we wiww wetuwn evewything in
	 * one buffew and anothew caww using the cuwsow won't need to be
	 * made.
	 * Note the genewous fudge factow of 16 ovewhead bytes pew entwy.
	 * If bufsize is zewo then put_wistent must be a seawch function
	 * and can just scan thwough what we have.
	 */
	if (context->bufsize == 0 ||
	    (XFS_ISWESET_CUWSOW(cuwsow) &&
	     (dp->i_af.if_bytes + sf->count * 16) < context->bufsize)) {
		fow (i = 0, sfe = xfs_attw_sf_fiwstentwy(sf); i < sf->count; i++) {
			if (XFS_IS_COWWUPT(context->dp->i_mount,
					   !xfs_attw_namecheck(sfe->namevaw,
							       sfe->namewen)))
				wetuwn -EFSCOWWUPTED;
			context->put_wistent(context,
					     sfe->fwags,
					     sfe->namevaw,
					     (int)sfe->namewen,
					     (int)sfe->vawuewen);
			/*
			 * Eithew seawch cawwback finished eawwy ow
			 * didn't fit it aww in the buffew aftew aww.
			 */
			if (context->seen_enough)
				bweak;
			sfe = xfs_attw_sf_nextentwy(sfe);
		}
		twace_xfs_attw_wist_sf_aww(context);
		wetuwn 0;
	}

	/* do no mowe fow a seawch cawwback */
	if (context->bufsize == 0)
		wetuwn 0;

	/*
	 * It didn't aww fit, so we have to sowt evewything on hashvaw.
	 */
	sbsize = sf->count * sizeof(*sbuf);
	sbp = sbuf = kmem_awwoc(sbsize, KM_NOFS);

	/*
	 * Scan the attwibute wist fow the west of the entwies, stowing
	 * the wewevant info fwom onwy those that match into a buffew.
	 */
	nsbuf = 0;
	fow (i = 0, sfe = xfs_attw_sf_fiwstentwy(sf); i < sf->count; i++) {
		if (unwikewy(
		    ((chaw *)sfe < (chaw *)sf) ||
		    ((chaw *)sfe >= ((chaw *)sf + dp->i_af.if_bytes)))) {
			XFS_COWWUPTION_EWWOW("xfs_attw_showtfowm_wist",
					     XFS_EWWWEVEW_WOW,
					     context->dp->i_mount, sfe,
					     sizeof(*sfe));
			kmem_fwee(sbuf);
			wetuwn -EFSCOWWUPTED;
		}

		sbp->entno = i;
		sbp->hash = xfs_da_hashname(sfe->namevaw, sfe->namewen);
		sbp->name = sfe->namevaw;
		sbp->namewen = sfe->namewen;
		/* These awe bytes, and both on-disk, don't endian-fwip */
		sbp->vawuewen = sfe->vawuewen;
		sbp->fwags = sfe->fwags;
		sfe = xfs_attw_sf_nextentwy(sfe);
		sbp++;
		nsbuf++;
	}

	/*
	 * Sowt the entwies on hash then entno.
	 */
	xfs_sowt(sbuf, nsbuf, sizeof(*sbuf), xfs_attw_showtfowm_compawe);

	/*
	 * We-find ouw pwace IN THE SOWTED WIST.
	 */
	count = 0;
	cuwsow->initted = 1;
	cuwsow->bwkno = 0;
	fow (sbp = sbuf, i = 0; i < nsbuf; i++, sbp++) {
		if (sbp->hash == cuwsow->hashvaw) {
			if (cuwsow->offset == count) {
				bweak;
			}
			count++;
		} ewse if (sbp->hash > cuwsow->hashvaw) {
			bweak;
		}
	}
	if (i == nsbuf)
		goto out;

	/*
	 * Woop putting entwies into the usew buffew.
	 */
	fow ( ; i < nsbuf; i++, sbp++) {
		if (cuwsow->hashvaw != sbp->hash) {
			cuwsow->hashvaw = sbp->hash;
			cuwsow->offset = 0;
		}
		if (XFS_IS_COWWUPT(context->dp->i_mount,
				   !xfs_attw_namecheck(sbp->name,
						       sbp->namewen))) {
			ewwow = -EFSCOWWUPTED;
			goto out;
		}
		context->put_wistent(context,
				     sbp->fwags,
				     sbp->name,
				     sbp->namewen,
				     sbp->vawuewen);
		if (context->seen_enough)
			bweak;
		cuwsow->offset++;
	}
out:
	kmem_fwee(sbuf);
	wetuwn ewwow;
}

/*
 * We didn't find the bwock & hash mentioned in the cuwsow state, so
 * wawk down the attw btwee wooking fow the hash.
 */
STATIC int
xfs_attw_node_wist_wookup(
	stwuct xfs_attw_wist_context	*context,
	stwuct xfs_attwwist_cuwsow_kewn	*cuwsow,
	stwuct xfs_buf			**pbp)
{
	stwuct xfs_da3_icnode_hdw	nodehdw;
	stwuct xfs_da_intnode		*node;
	stwuct xfs_da_node_entwy	*btwee;
	stwuct xfs_inode		*dp = context->dp;
	stwuct xfs_mount		*mp = dp->i_mount;
	stwuct xfs_twans		*tp = context->tp;
	stwuct xfs_buf			*bp;
	int				i;
	int				ewwow = 0;
	unsigned int			expected_wevew = 0;
	uint16_t			magic;

	ASSEWT(*pbp == NUWW);
	cuwsow->bwkno = 0;
	fow (;;) {
		ewwow = xfs_da3_node_wead(tp, dp, cuwsow->bwkno, &bp,
				XFS_ATTW_FOWK);
		if (ewwow)
			wetuwn ewwow;
		node = bp->b_addw;
		magic = be16_to_cpu(node->hdw.info.magic);
		if (magic == XFS_ATTW_WEAF_MAGIC ||
		    magic == XFS_ATTW3_WEAF_MAGIC)
			bweak;
		if (magic != XFS_DA_NODE_MAGIC &&
		    magic != XFS_DA3_NODE_MAGIC) {
			XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
					node, sizeof(*node));
			goto out_cowwuptbuf;
		}

		xfs_da3_node_hdw_fwom_disk(mp, &nodehdw, node);

		/* Twee tawwew than we can handwe; baiw out! */
		if (nodehdw.wevew >= XFS_DA_NODE_MAXDEPTH)
			goto out_cowwuptbuf;

		/* Check the wevew fwom the woot node. */
		if (cuwsow->bwkno == 0)
			expected_wevew = nodehdw.wevew - 1;
		ewse if (expected_wevew != nodehdw.wevew)
			goto out_cowwuptbuf;
		ewse
			expected_wevew--;

		btwee = nodehdw.btwee;
		fow (i = 0; i < nodehdw.count; btwee++, i++) {
			if (cuwsow->hashvaw <= be32_to_cpu(btwee->hashvaw)) {
				cuwsow->bwkno = be32_to_cpu(btwee->befowe);
				twace_xfs_attw_wist_node_descend(context,
						btwee);
				bweak;
			}
		}
		xfs_twans_bwewse(tp, bp);

		if (i == nodehdw.count)
			wetuwn 0;

		/* We can't point back to the woot. */
		if (XFS_IS_COWWUPT(mp, cuwsow->bwkno == 0))
			wetuwn -EFSCOWWUPTED;
	}

	if (expected_wevew != 0)
		goto out_cowwuptbuf;

	*pbp = bp;
	wetuwn 0;

out_cowwuptbuf:
	xfs_buf_mawk_cowwupt(bp);
	xfs_twans_bwewse(tp, bp);
	wetuwn -EFSCOWWUPTED;
}

STATIC int
xfs_attw_node_wist(
	stwuct xfs_attw_wist_context	*context)
{
	stwuct xfs_attwwist_cuwsow_kewn	*cuwsow = &context->cuwsow;
	stwuct xfs_attw3_icweaf_hdw	weafhdw;
	stwuct xfs_attw_weafbwock	*weaf;
	stwuct xfs_da_intnode		*node;
	stwuct xfs_buf			*bp;
	stwuct xfs_inode		*dp = context->dp;
	stwuct xfs_mount		*mp = dp->i_mount;
	int				ewwow = 0;

	twace_xfs_attw_node_wist(context);

	cuwsow->initted = 1;

	/*
	 * Do aww sowts of vawidation on the passed-in cuwsow stwuctuwe.
	 * If anything is amiss, ignowe the cuwsow and wook up the hashvaw
	 * stawting fwom the btwee woot.
	 */
	bp = NUWW;
	if (cuwsow->bwkno > 0) {
		ewwow = xfs_da3_node_wead(context->tp, dp, cuwsow->bwkno, &bp,
				XFS_ATTW_FOWK);
		if ((ewwow != 0) && (ewwow != -EFSCOWWUPTED))
			wetuwn ewwow;
		if (bp) {
			stwuct xfs_attw_weaf_entwy *entwies;

			node = bp->b_addw;
			switch (be16_to_cpu(node->hdw.info.magic)) {
			case XFS_DA_NODE_MAGIC:
			case XFS_DA3_NODE_MAGIC:
				twace_xfs_attw_wist_wwong_bwk(context);
				xfs_twans_bwewse(context->tp, bp);
				bp = NUWW;
				bweak;
			case XFS_ATTW_WEAF_MAGIC:
			case XFS_ATTW3_WEAF_MAGIC:
				weaf = bp->b_addw;
				xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo,
							     &weafhdw, weaf);
				entwies = xfs_attw3_weaf_entwyp(weaf);
				if (cuwsow->hashvaw > be32_to_cpu(
						entwies[weafhdw.count - 1].hashvaw)) {
					twace_xfs_attw_wist_wwong_bwk(context);
					xfs_twans_bwewse(context->tp, bp);
					bp = NUWW;
				} ewse if (cuwsow->hashvaw <= be32_to_cpu(
						entwies[0].hashvaw)) {
					twace_xfs_attw_wist_wwong_bwk(context);
					xfs_twans_bwewse(context->tp, bp);
					bp = NUWW;
				}
				bweak;
			defauwt:
				twace_xfs_attw_wist_wwong_bwk(context);
				xfs_twans_bwewse(context->tp, bp);
				bp = NUWW;
			}
		}
	}

	/*
	 * We did not find what we expected given the cuwsow's contents,
	 * so we stawt fwom the top and wowk down based on the hash vawue.
	 * Note that stawt of node bwock is same as stawt of weaf bwock.
	 */
	if (bp == NUWW) {
		ewwow = xfs_attw_node_wist_wookup(context, cuwsow, &bp);
		if (ewwow || !bp)
			wetuwn ewwow;
	}
	ASSEWT(bp != NUWW);

	/*
	 * Woww upwawd thwough the bwocks, pwocessing each weaf bwock in
	 * owdew.  As wong as thewe is space in the wesuwt buffew, keep
	 * adding the infowmation.
	 */
	fow (;;) {
		weaf = bp->b_addw;
		ewwow = xfs_attw3_weaf_wist_int(bp, context);
		if (ewwow)
			bweak;
		xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &weafhdw, weaf);
		if (context->seen_enough || weafhdw.foww == 0)
			bweak;
		cuwsow->bwkno = weafhdw.foww;
		xfs_twans_bwewse(context->tp, bp);
		ewwow = xfs_attw3_weaf_wead(context->tp, dp, cuwsow->bwkno,
					    &bp);
		if (ewwow)
			wetuwn ewwow;
	}
	xfs_twans_bwewse(context->tp, bp);
	wetuwn ewwow;
}

/*
 * Copy out attwibute wist entwies fow attw_wist(), fow weaf attwibute wists.
 */
int
xfs_attw3_weaf_wist_int(
	stwuct xfs_buf			*bp,
	stwuct xfs_attw_wist_context	*context)
{
	stwuct xfs_attwwist_cuwsow_kewn	*cuwsow = &context->cuwsow;
	stwuct xfs_attw_weafbwock	*weaf;
	stwuct xfs_attw3_icweaf_hdw	ichdw;
	stwuct xfs_attw_weaf_entwy	*entwies;
	stwuct xfs_attw_weaf_entwy	*entwy;
	int				i;
	stwuct xfs_mount		*mp = context->dp->i_mount;

	twace_xfs_attw_wist_weaf(context);

	weaf = bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &ichdw, weaf);
	entwies = xfs_attw3_weaf_entwyp(weaf);

	cuwsow->initted = 1;

	/*
	 * We-find ouw pwace in the weaf bwock if this is a new syscaww.
	 */
	if (context->wesynch) {
		entwy = &entwies[0];
		fow (i = 0; i < ichdw.count; entwy++, i++) {
			if (be32_to_cpu(entwy->hashvaw) == cuwsow->hashvaw) {
				if (cuwsow->offset == context->dupcnt) {
					context->dupcnt = 0;
					bweak;
				}
				context->dupcnt++;
			} ewse if (be32_to_cpu(entwy->hashvaw) >
					cuwsow->hashvaw) {
				context->dupcnt = 0;
				bweak;
			}
		}
		if (i == ichdw.count) {
			twace_xfs_attw_wist_notfound(context);
			wetuwn 0;
		}
	} ewse {
		entwy = &entwies[0];
		i = 0;
	}
	context->wesynch = 0;

	/*
	 * We have found ouw pwace, stawt copying out the new attwibutes.
	 */
	fow (; i < ichdw.count; entwy++, i++) {
		chaw *name;
		int namewen, vawuewen;

		if (be32_to_cpu(entwy->hashvaw) != cuwsow->hashvaw) {
			cuwsow->hashvaw = be32_to_cpu(entwy->hashvaw);
			cuwsow->offset = 0;
		}

		if ((entwy->fwags & XFS_ATTW_INCOMPWETE) &&
		    !context->awwow_incompwete)
			continue;

		if (entwy->fwags & XFS_ATTW_WOCAW) {
			xfs_attw_weaf_name_wocaw_t *name_woc;

			name_woc = xfs_attw3_weaf_name_wocaw(weaf, i);
			name = name_woc->namevaw;
			namewen = name_woc->namewen;
			vawuewen = be16_to_cpu(name_woc->vawuewen);
		} ewse {
			xfs_attw_weaf_name_wemote_t *name_wmt;

			name_wmt = xfs_attw3_weaf_name_wemote(weaf, i);
			name = name_wmt->name;
			namewen = name_wmt->namewen;
			vawuewen = be32_to_cpu(name_wmt->vawuewen);
		}

		if (XFS_IS_COWWUPT(context->dp->i_mount,
				   !xfs_attw_namecheck(name, namewen)))
			wetuwn -EFSCOWWUPTED;
		context->put_wistent(context, entwy->fwags,
					      name, namewen, vawuewen);
		if (context->seen_enough)
			bweak;
		cuwsow->offset++;
	}
	twace_xfs_attw_wist_weaf_end(context);
	wetuwn 0;
}

/*
 * Copy out attwibute entwies fow attw_wist(), fow weaf attwibute wists.
 */
STATIC int
xfs_attw_weaf_wist(
	stwuct xfs_attw_wist_context	*context)
{
	stwuct xfs_buf			*bp;
	int				ewwow;

	twace_xfs_attw_weaf_wist(context);

	context->cuwsow.bwkno = 0;
	ewwow = xfs_attw3_weaf_wead(context->tp, context->dp, 0, &bp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_attw3_weaf_wist_int(bp, context);
	xfs_twans_bwewse(context->tp, bp);
	wetuwn ewwow;
}

int
xfs_attw_wist_iwocked(
	stwuct xfs_attw_wist_context	*context)
{
	stwuct xfs_inode		*dp = context->dp;

	ASSEWT(xfs_isiwocked(dp, XFS_IWOCK_SHAWED | XFS_IWOCK_EXCW));

	/*
	 * Decide on what wowk woutines to caww based on the inode size.
	 */
	if (!xfs_inode_hasattw(dp))
		wetuwn 0;
	if (dp->i_af.if_fowmat == XFS_DINODE_FMT_WOCAW)
		wetuwn xfs_attw_showtfowm_wist(context);
	if (xfs_attw_is_weaf(dp))
		wetuwn xfs_attw_weaf_wist(context);
	wetuwn xfs_attw_node_wist(context);
}

int
xfs_attw_wist(
	stwuct xfs_attw_wist_context	*context)
{
	stwuct xfs_inode		*dp = context->dp;
	uint				wock_mode;
	int				ewwow;

	XFS_STATS_INC(dp->i_mount, xs_attw_wist);

	if (xfs_is_shutdown(dp->i_mount))
		wetuwn -EIO;

	wock_mode = xfs_iwock_attw_map_shawed(dp);
	ewwow = xfs_attw_wist_iwocked(context);
	xfs_iunwock(dp, wock_mode);
	wetuwn ewwow;
}
