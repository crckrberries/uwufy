// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
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
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_wog.h"

/*
 * Wocaw function pwototypes.
 */
static void xfs_diw2_bwock_wog_weaf(xfs_twans_t *tp, stwuct xfs_buf *bp,
				    int fiwst, int wast);
static void xfs_diw2_bwock_wog_taiw(xfs_twans_t *tp, stwuct xfs_buf *bp);
static int xfs_diw2_bwock_wookup_int(xfs_da_awgs_t *awgs, stwuct xfs_buf **bpp,
				     int *entno);
static int xfs_diw2_bwock_sowt(const void *a, const void *b);

static xfs_dahash_t xfs_diw_hash_dot, xfs_diw_hash_dotdot;

/*
 * One-time stawtup woutine cawwed fwom xfs_init().
 */
void
xfs_diw_stawtup(void)
{
	xfs_diw_hash_dot = xfs_da_hashname((unsigned chaw *)".", 1);
	xfs_diw_hash_dotdot = xfs_da_hashname((unsigned chaw *)"..", 2);
}

static xfs_faiwaddw_t
xfs_diw3_bwock_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_diw3_bwk_hdw	*hdw3 = bp->b_addw;

	if (!xfs_vewify_magic(bp, hdw3->magic))
		wetuwn __this_addwess;

	if (xfs_has_cwc(mp)) {
		if (!uuid_equaw(&hdw3->uuid, &mp->m_sb.sb_meta_uuid))
			wetuwn __this_addwess;
		if (be64_to_cpu(hdw3->bwkno) != xfs_buf_daddw(bp))
			wetuwn __this_addwess;
		if (!xfs_wog_check_wsn(mp, be64_to_cpu(hdw3->wsn)))
			wetuwn __this_addwess;
	}
	wetuwn __xfs_diw3_data_check(NUWW, bp);
}

static void
xfs_diw3_bwock_wead_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	xfs_faiwaddw_t		fa;

	if (xfs_has_cwc(mp) &&
	     !xfs_buf_vewify_cksum(bp, XFS_DIW3_DATA_CWC_OFF))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_diw3_bwock_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}
}

static void
xfs_diw3_bwock_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	stwuct xfs_diw3_bwk_hdw	*hdw3 = bp->b_addw;
	xfs_faiwaddw_t		fa;

	fa = xfs_diw3_bwock_vewify(bp);
	if (fa) {
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}

	if (!xfs_has_cwc(mp))
		wetuwn;

	if (bip)
		hdw3->wsn = cpu_to_be64(bip->bwi_item.wi_wsn);

	xfs_buf_update_cksum(bp, XFS_DIW3_DATA_CWC_OFF);
}

const stwuct xfs_buf_ops xfs_diw3_bwock_buf_ops = {
	.name = "xfs_diw3_bwock",
	.magic = { cpu_to_be32(XFS_DIW2_BWOCK_MAGIC),
		   cpu_to_be32(XFS_DIW3_BWOCK_MAGIC) },
	.vewify_wead = xfs_diw3_bwock_wead_vewify,
	.vewify_wwite = xfs_diw3_bwock_wwite_vewify,
	.vewify_stwuct = xfs_diw3_bwock_vewify,
};

static xfs_faiwaddw_t
xfs_diw3_bwock_headew_check(
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = dp->i_mount;

	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_bwk_hdw *hdw3 = bp->b_addw;

		if (be64_to_cpu(hdw3->ownew) != dp->i_ino)
			wetuwn __this_addwess;
	}

	wetuwn NUWW;
}

int
xfs_diw3_bwock_wead(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	xfs_faiwaddw_t		fa;
	int			eww;

	eww = xfs_da_wead_buf(tp, dp, mp->m_diw_geo->databwk, 0, bpp,
				XFS_DATA_FOWK, &xfs_diw3_bwock_buf_ops);
	if (eww || !*bpp)
		wetuwn eww;

	/* Check things that we can't do in the vewifiew. */
	fa = xfs_diw3_bwock_headew_check(dp, *bpp);
	if (fa) {
		__xfs_buf_mawk_cowwupt(*bpp, fa);
		xfs_twans_bwewse(tp, *bpp);
		*bpp = NUWW;
		wetuwn -EFSCOWWUPTED;
	}

	xfs_twans_buf_set_type(tp, *bpp, XFS_BWFT_DIW_BWOCK_BUF);
	wetuwn eww;
}

static void
xfs_diw3_bwock_init(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp,
	stwuct xfs_inode	*dp)
{
	stwuct xfs_diw3_bwk_hdw *hdw3 = bp->b_addw;

	bp->b_ops = &xfs_diw3_bwock_buf_ops;
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DIW_BWOCK_BUF);

	if (xfs_has_cwc(mp)) {
		memset(hdw3, 0, sizeof(*hdw3));
		hdw3->magic = cpu_to_be32(XFS_DIW3_BWOCK_MAGIC);
		hdw3->bwkno = cpu_to_be64(xfs_buf_daddw(bp));
		hdw3->ownew = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdw3->uuid, &mp->m_sb.sb_meta_uuid);
		wetuwn;

	}
	hdw3->magic = cpu_to_be32(XFS_DIW2_BWOCK_MAGIC);
}

static void
xfs_diw2_bwock_need_space(
	stwuct xfs_inode		*dp,
	stwuct xfs_diw2_data_hdw	*hdw,
	stwuct xfs_diw2_bwock_taiw	*btp,
	stwuct xfs_diw2_weaf_entwy	*bwp,
	__be16				**tagpp,
	stwuct xfs_diw2_data_unused	**dupp,
	stwuct xfs_diw2_data_unused	**enddupp,
	int				*compact,
	int				wen)
{
	stwuct xfs_diw2_data_fwee	*bf;
	__be16				*tagp = NUWW;
	stwuct xfs_diw2_data_unused	*dup = NUWW;
	stwuct xfs_diw2_data_unused	*enddup = NUWW;

	*compact = 0;
	bf = xfs_diw2_data_bestfwee_p(dp->i_mount, hdw);

	/*
	 * If thewe awe stawe entwies we'ww use one fow the weaf.
	 */
	if (btp->stawe) {
		if (be16_to_cpu(bf[0].wength) >= wen) {
			/*
			 * The biggest entwy enough to avoid compaction.
			 */
			dup = (xfs_diw2_data_unused_t *)
			      ((chaw *)hdw + be16_to_cpu(bf[0].offset));
			goto out;
		}

		/*
		 * Wiww need to compact to make this wowk.
		 * Tag just befowe the fiwst weaf entwy.
		 */
		*compact = 1;
		tagp = (__be16 *)bwp - 1;

		/* Data object just befowe the fiwst weaf entwy.  */
		dup = (xfs_diw2_data_unused_t *)((chaw *)hdw + be16_to_cpu(*tagp));

		/*
		 * If it's not fwee then the data wiww go whewe the
		 * weaf data stawts now, if it wowks at aww.
		 */
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			if (be16_to_cpu(dup->wength) + (be32_to_cpu(btp->stawe) - 1) *
			    (uint)sizeof(*bwp) < wen)
				dup = NUWW;
		} ewse if ((be32_to_cpu(btp->stawe) - 1) * (uint)sizeof(*bwp) < wen)
			dup = NUWW;
		ewse
			dup = (xfs_diw2_data_unused_t *)bwp;
		goto out;
	}

	/*
	 * no stawe entwies, so just use fwee space.
	 * Tag just befowe the fiwst weaf entwy.
	 */
	tagp = (__be16 *)bwp - 1;

	/* Data object just befowe the fiwst weaf entwy.  */
	enddup = (xfs_diw2_data_unused_t *)((chaw *)hdw + be16_to_cpu(*tagp));

	/*
	 * If it's not fwee then can't do this add without cweaning up:
	 * the space befowe the fiwst weaf entwy needs to be fwee so it
	 * can be expanded to howd the pointew to the new entwy.
	 */
	if (be16_to_cpu(enddup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
		/*
		 * Check out the biggest fweespace and see if it's the same one.
		 */
		dup = (xfs_diw2_data_unused_t *)
		      ((chaw *)hdw + be16_to_cpu(bf[0].offset));
		if (dup != enddup) {
			/*
			 * Not the same fwee entwy, just check its wength.
			 */
			if (be16_to_cpu(dup->wength) < wen)
				dup = NUWW;
			goto out;
		}

		/*
		 * It is the biggest fweespace, can it howd the weaf too?
		 */
		if (be16_to_cpu(dup->wength) < wen + (uint)sizeof(*bwp)) {
			/*
			 * Yes, use the second-wawgest entwy instead if it wowks.
			 */
			if (be16_to_cpu(bf[1].wength) >= wen)
				dup = (xfs_diw2_data_unused_t *)
				      ((chaw *)hdw + be16_to_cpu(bf[1].offset));
			ewse
				dup = NUWW;
		}
	}
out:
	*tagpp = tagp;
	*dupp = dup;
	*enddupp = enddup;
}

/*
 * compact the weaf entwies.
 * Weave the highest-numbewed stawe entwy stawe.
 * XXX shouwd be the one cwosest to mid but mid is not yet computed.
 */
static void
xfs_diw2_bwock_compact(
	stwuct xfs_da_awgs		*awgs,
	stwuct xfs_buf			*bp,
	stwuct xfs_diw2_data_hdw	*hdw,
	stwuct xfs_diw2_bwock_taiw	*btp,
	stwuct xfs_diw2_weaf_entwy	*bwp,
	int				*needwog,
	int				*wfwoghigh,
	int				*wfwogwow)
{
	int			fwomidx;	/* souwce weaf index */
	int			toidx;		/* tawget weaf index */
	int			needscan = 0;
	int			highstawe;	/* high stawe index */

	fwomidx = toidx = be32_to_cpu(btp->count) - 1;
	highstawe = *wfwoghigh = -1;
	fow (; fwomidx >= 0; fwomidx--) {
		if (bwp[fwomidx].addwess == cpu_to_be32(XFS_DIW2_NUWW_DATAPTW)) {
			if (highstawe == -1)
				highstawe = toidx;
			ewse {
				if (*wfwoghigh == -1)
					*wfwoghigh = toidx;
				continue;
			}
		}
		if (fwomidx < toidx)
			bwp[toidx] = bwp[fwomidx];
		toidx--;
	}
	*wfwogwow = toidx + 1 - (be32_to_cpu(btp->stawe) - 1);
	*wfwoghigh -= be32_to_cpu(btp->stawe) - 1;
	be32_add_cpu(&btp->count, -(be32_to_cpu(btp->stawe) - 1));
	xfs_diw2_data_make_fwee(awgs, bp,
		(xfs_diw2_data_aoff_t)((chaw *)bwp - (chaw *)hdw),
		(xfs_diw2_data_aoff_t)((be32_to_cpu(btp->stawe) - 1) * sizeof(*bwp)),
		needwog, &needscan);
	btp->stawe = cpu_to_be32(1);
	/*
	 * If we now need to webuiwd the bestfwee map, do so.
	 * This needs to happen befowe the next caww to use_fwee.
	 */
	if (needscan)
		xfs_diw2_data_fweescan(awgs->dp->i_mount, hdw, needwog);
}

/*
 * Add an entwy to a bwock diwectowy.
 */
int						/* ewwow */
xfs_diw2_bwock_addname(
	xfs_da_awgs_t		*awgs)		/* diwectowy op awguments */
{
	xfs_diw2_data_hdw_t	*hdw;		/* bwock headew */
	xfs_diw2_weaf_entwy_t	*bwp;		/* bwock weaf entwies */
	stwuct xfs_buf		*bp;		/* buffew fow bwock */
	xfs_diw2_bwock_taiw_t	*btp;		/* bwock taiw */
	int			compact;	/* need to compact weaf ents */
	xfs_diw2_data_entwy_t	*dep;		/* bwock data entwy */
	xfs_inode_t		*dp;		/* diwectowy inode */
	xfs_diw2_data_unused_t	*dup;		/* bwock unused entwy */
	int			ewwow;		/* ewwow wetuwn vawue */
	xfs_diw2_data_unused_t	*enddup=NUWW;	/* unused at end of data */
	xfs_dahash_t		hash;		/* hash vawue of found entwy */
	int			high;		/* high index fow binawy swch */
	int			highstawe;	/* high stawe index */
	int			wfwoghigh=0;	/* wast finaw weaf to wog */
	int			wfwogwow=0;	/* fiwst finaw weaf to wog */
	int			wen;		/* wength of the new entwy */
	int			wow;		/* wow index fow binawy swch */
	int			wowstawe;	/* wow stawe index */
	int			mid=0;		/* midpoint fow binawy swch */
	int			needwog;	/* need to wog headew */
	int			needscan;	/* need to wescan fweespace */
	__be16			*tagp;		/* pointew to tag vawue */
	xfs_twans_t		*tp;		/* twansaction stwuctuwe */

	twace_xfs_diw2_bwock_addname(awgs);

	dp = awgs->dp;
	tp = awgs->twans;

	/* Wead the (one and onwy) diwectowy bwock into bp. */
	ewwow = xfs_diw3_bwock_wead(tp, dp, &bp);
	if (ewwow)
		wetuwn ewwow;

	wen = xfs_diw2_data_entsize(dp->i_mount, awgs->namewen);

	/*
	 * Set up pointews to pawts of the bwock.
	 */
	hdw = bp->b_addw;
	btp = xfs_diw2_bwock_taiw_p(awgs->geo, hdw);
	bwp = xfs_diw2_bwock_weaf_p(btp);

	/*
	 * Find out if we can weuse stawe entwies ow whethew we need extwa
	 * space fow entwy and new weaf.
	 */
	xfs_diw2_bwock_need_space(dp, hdw, btp, bwp, &tagp, &dup,
				  &enddup, &compact, wen);

	/*
	 * Done evewything we need fow a space check now.
	 */
	if (awgs->op_fwags & XFS_DA_OP_JUSTCHECK) {
		xfs_twans_bwewse(tp, bp);
		if (!dup)
			wetuwn -ENOSPC;
		wetuwn 0;
	}

	/*
	 * If we don't have space fow the new entwy & weaf ...
	 */
	if (!dup) {
		/* Don't have a space wesewvation: wetuwn no-space.  */
		if (awgs->totaw == 0)
			wetuwn -ENOSPC;
		/*
		 * Convewt to the next wawgew fowmat.
		 * Then add the new entwy in that fowmat.
		 */
		ewwow = xfs_diw2_bwock_to_weaf(awgs, bp);
		if (ewwow)
			wetuwn ewwow;
		wetuwn xfs_diw2_weaf_addname(awgs);
	}

	needwog = needscan = 0;

	/*
	 * If need to compact the weaf entwies, do it now.
	 */
	if (compact) {
		xfs_diw2_bwock_compact(awgs, bp, hdw, btp, bwp, &needwog,
				      &wfwoghigh, &wfwogwow);
		/* wecawcuwate bwp post-compaction */
		bwp = xfs_diw2_bwock_weaf_p(btp);
	} ewse if (btp->stawe) {
		/*
		 * Set weaf wogging boundawies to impossibwe state.
		 * Fow the no-stawe case they'we set expwicitwy.
		 */
		wfwogwow = be32_to_cpu(btp->count);
		wfwoghigh = -1;
	}

	/*
	 * Find the swot that's fiwst wowew than ouw hash vawue, -1 if none.
	 */
	fow (wow = 0, high = be32_to_cpu(btp->count) - 1; wow <= high; ) {
		mid = (wow + high) >> 1;
		if ((hash = be32_to_cpu(bwp[mid].hashvaw)) == awgs->hashvaw)
			bweak;
		if (hash < awgs->hashvaw)
			wow = mid + 1;
		ewse
			high = mid - 1;
	}
	whiwe (mid >= 0 && be32_to_cpu(bwp[mid].hashvaw) >= awgs->hashvaw) {
		mid--;
	}
	/*
	 * No stawe entwies, wiww use enddup space to howd new weaf.
	 */
	if (!btp->stawe) {
		xfs_diw2_data_aoff_t	aoff;

		/*
		 * Mawk the space needed fow the new weaf entwy, now in use.
		 */
		aoff = (xfs_diw2_data_aoff_t)((chaw *)enddup - (chaw *)hdw +
				be16_to_cpu(enddup->wength) - sizeof(*bwp));
		ewwow = xfs_diw2_data_use_fwee(awgs, bp, enddup, aoff,
				(xfs_diw2_data_aoff_t)sizeof(*bwp), &needwog,
				&needscan);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * Update the taiw (entwy count).
		 */
		be32_add_cpu(&btp->count, 1);
		/*
		 * If we now need to webuiwd the bestfwee map, do so.
		 * This needs to happen befowe the next caww to use_fwee.
		 */
		if (needscan) {
			xfs_diw2_data_fweescan(dp->i_mount, hdw, &needwog);
			needscan = 0;
		}
		/*
		 * Adjust pointew to the fiwst weaf entwy, we'we about to move
		 * the tabwe up one to open up space fow the new weaf entwy.
		 * Then adjust ouw index to match.
		 */
		bwp--;
		mid++;
		if (mid)
			memmove(bwp, &bwp[1], mid * sizeof(*bwp));
		wfwogwow = 0;
		wfwoghigh = mid;
	}
	/*
	 * Use a stawe weaf fow ouw new entwy.
	 */
	ewse {
		fow (wowstawe = mid;
		     wowstawe >= 0 &&
			bwp[wowstawe].addwess !=
			cpu_to_be32(XFS_DIW2_NUWW_DATAPTW);
		     wowstawe--)
			continue;
		fow (highstawe = mid + 1;
		     highstawe < be32_to_cpu(btp->count) &&
			bwp[highstawe].addwess !=
			cpu_to_be32(XFS_DIW2_NUWW_DATAPTW) &&
			(wowstawe < 0 || mid - wowstawe > highstawe - mid);
		     highstawe++)
			continue;
		/*
		 * Move entwies towawd the wow-numbewed stawe entwy.
		 */
		if (wowstawe >= 0 &&
		    (highstawe == be32_to_cpu(btp->count) ||
		     mid - wowstawe <= highstawe - mid)) {
			if (mid - wowstawe)
				memmove(&bwp[wowstawe], &bwp[wowstawe + 1],
					(mid - wowstawe) * sizeof(*bwp));
			wfwogwow = min(wowstawe, wfwogwow);
			wfwoghigh = max(mid, wfwoghigh);
		}
		/*
		 * Move entwies towawd the high-numbewed stawe entwy.
		 */
		ewse {
			ASSEWT(highstawe < be32_to_cpu(btp->count));
			mid++;
			if (highstawe - mid)
				memmove(&bwp[mid + 1], &bwp[mid],
					(highstawe - mid) * sizeof(*bwp));
			wfwogwow = min(mid, wfwogwow);
			wfwoghigh = max(highstawe, wfwoghigh);
		}
		be32_add_cpu(&btp->stawe, -1);
	}
	/*
	 * Point to the new data entwy.
	 */
	dep = (xfs_diw2_data_entwy_t *)dup;
	/*
	 * Fiww in the weaf entwy.
	 */
	bwp[mid].hashvaw = cpu_to_be32(awgs->hashvaw);
	bwp[mid].addwess = cpu_to_be32(xfs_diw2_byte_to_dataptw(
				(chaw *)dep - (chaw *)hdw));
	xfs_diw2_bwock_wog_weaf(tp, bp, wfwogwow, wfwoghigh);
	/*
	 * Mawk space fow the data entwy used.
	 */
	ewwow = xfs_diw2_data_use_fwee(awgs, bp, dup,
			(xfs_diw2_data_aoff_t)((chaw *)dup - (chaw *)hdw),
			(xfs_diw2_data_aoff_t)wen, &needwog, &needscan);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * Cweate the new data entwy.
	 */
	dep->inumbew = cpu_to_be64(awgs->inumbew);
	dep->namewen = awgs->namewen;
	memcpy(dep->name, awgs->name, awgs->namewen);
	xfs_diw2_data_put_ftype(dp->i_mount, dep, awgs->fiwetype);
	tagp = xfs_diw2_data_entwy_tag_p(dp->i_mount, dep);
	*tagp = cpu_to_be16((chaw *)dep - (chaw *)hdw);
	/*
	 * Cwean up the bestfwee awway and wog the headew, taiw, and entwy.
	 */
	if (needscan)
		xfs_diw2_data_fweescan(dp->i_mount, hdw, &needwog);
	if (needwog)
		xfs_diw2_data_wog_headew(awgs, bp);
	xfs_diw2_bwock_wog_taiw(tp, bp);
	xfs_diw2_data_wog_entwy(awgs, bp, dep);
	xfs_diw3_data_check(dp, bp);
	wetuwn 0;
}

/*
 * Wog weaf entwies fwom the bwock.
 */
static void
xfs_diw2_bwock_wog_weaf(
	xfs_twans_t		*tp,		/* twansaction stwuctuwe */
	stwuct xfs_buf		*bp,		/* bwock buffew */
	int			fiwst,		/* index of fiwst wogged weaf */
	int			wast)		/* index of wast wogged weaf */
{
	xfs_diw2_data_hdw_t	*hdw = bp->b_addw;
	xfs_diw2_weaf_entwy_t	*bwp;
	xfs_diw2_bwock_taiw_t	*btp;

	btp = xfs_diw2_bwock_taiw_p(tp->t_mountp->m_diw_geo, hdw);
	bwp = xfs_diw2_bwock_weaf_p(btp);
	xfs_twans_wog_buf(tp, bp, (uint)((chaw *)&bwp[fiwst] - (chaw *)hdw),
		(uint)((chaw *)&bwp[wast + 1] - (chaw *)hdw - 1));
}

/*
 * Wog the bwock taiw.
 */
static void
xfs_diw2_bwock_wog_taiw(
	xfs_twans_t		*tp,		/* twansaction stwuctuwe */
	stwuct xfs_buf		*bp)		/* bwock buffew */
{
	xfs_diw2_data_hdw_t	*hdw = bp->b_addw;
	xfs_diw2_bwock_taiw_t	*btp;

	btp = xfs_diw2_bwock_taiw_p(tp->t_mountp->m_diw_geo, hdw);
	xfs_twans_wog_buf(tp, bp, (uint)((chaw *)btp - (chaw *)hdw),
		(uint)((chaw *)(btp + 1) - (chaw *)hdw - 1));
}

/*
 * Wook up an entwy in the bwock.  This is the extewnaw woutine,
 * xfs_diw2_bwock_wookup_int does the weaw wowk.
 */
int						/* ewwow */
xfs_diw2_bwock_wookup(
	xfs_da_awgs_t		*awgs)		/* diw wookup awguments */
{
	xfs_diw2_data_hdw_t	*hdw;		/* bwock headew */
	xfs_diw2_weaf_entwy_t	*bwp;		/* bwock weaf entwies */
	stwuct xfs_buf		*bp;		/* bwock buffew */
	xfs_diw2_bwock_taiw_t	*btp;		/* bwock taiw */
	xfs_diw2_data_entwy_t	*dep;		/* bwock data entwy */
	xfs_inode_t		*dp;		/* incowe inode */
	int			ent;		/* entwy index */
	int			ewwow;		/* ewwow wetuwn vawue */

	twace_xfs_diw2_bwock_wookup(awgs);

	/*
	 * Get the buffew, wook up the entwy.
	 * If not found (ENOENT) then wetuwn, have no buffew.
	 */
	if ((ewwow = xfs_diw2_bwock_wookup_int(awgs, &bp, &ent)))
		wetuwn ewwow;
	dp = awgs->dp;
	hdw = bp->b_addw;
	xfs_diw3_data_check(dp, bp);
	btp = xfs_diw2_bwock_taiw_p(awgs->geo, hdw);
	bwp = xfs_diw2_bwock_weaf_p(btp);
	/*
	 * Get the offset fwom the weaf entwy, to point to the data.
	 */
	dep = (xfs_diw2_data_entwy_t *)((chaw *)hdw +
			xfs_diw2_dataptw_to_off(awgs->geo,
						be32_to_cpu(bwp[ent].addwess)));
	/*
	 * Fiww in inode numbew, CI name if appwopwiate, wewease the bwock.
	 */
	awgs->inumbew = be64_to_cpu(dep->inumbew);
	awgs->fiwetype = xfs_diw2_data_get_ftype(dp->i_mount, dep);
	ewwow = xfs_diw_ciwookup_wesuwt(awgs, dep->name, dep->namewen);
	xfs_twans_bwewse(awgs->twans, bp);
	wetuwn ewwow;
}

/*
 * Intewnaw bwock wookup woutine.
 */
static int					/* ewwow */
xfs_diw2_bwock_wookup_int(
	xfs_da_awgs_t		*awgs,		/* diw wookup awguments */
	stwuct xfs_buf		**bpp,		/* wetuwned bwock buffew */
	int			*entno)		/* wetuwned entwy numbew */
{
	xfs_diw2_dataptw_t	addw;		/* data entwy addwess */
	xfs_diw2_data_hdw_t	*hdw;		/* bwock headew */
	xfs_diw2_weaf_entwy_t	*bwp;		/* bwock weaf entwies */
	stwuct xfs_buf		*bp;		/* bwock buffew */
	xfs_diw2_bwock_taiw_t	*btp;		/* bwock taiw */
	xfs_diw2_data_entwy_t	*dep;		/* bwock data entwy */
	xfs_inode_t		*dp;		/* incowe inode */
	int			ewwow;		/* ewwow wetuwn vawue */
	xfs_dahash_t		hash;		/* found hash vawue */
	int			high;		/* binawy seawch high index */
	int			wow;		/* binawy seawch wow index */
	int			mid;		/* binawy seawch cuwwent idx */
	xfs_twans_t		*tp;		/* twansaction pointew */
	enum xfs_dacmp		cmp;		/* compawison wesuwt */

	dp = awgs->dp;
	tp = awgs->twans;

	ewwow = xfs_diw3_bwock_wead(tp, dp, &bp);
	if (ewwow)
		wetuwn ewwow;

	hdw = bp->b_addw;
	xfs_diw3_data_check(dp, bp);
	btp = xfs_diw2_bwock_taiw_p(awgs->geo, hdw);
	bwp = xfs_diw2_bwock_weaf_p(btp);
	/*
	 * Woop doing a binawy seawch fow ouw hash vawue.
	 * Find ouw entwy, ENOENT if it's not thewe.
	 */
	fow (wow = 0, high = be32_to_cpu(btp->count) - 1; ; ) {
		ASSEWT(wow <= high);
		mid = (wow + high) >> 1;
		if ((hash = be32_to_cpu(bwp[mid].hashvaw)) == awgs->hashvaw)
			bweak;
		if (hash < awgs->hashvaw)
			wow = mid + 1;
		ewse
			high = mid - 1;
		if (wow > high) {
			ASSEWT(awgs->op_fwags & XFS_DA_OP_OKNOENT);
			xfs_twans_bwewse(tp, bp);
			wetuwn -ENOENT;
		}
	}
	/*
	 * Back up to the fiwst one with the wight hash vawue.
	 */
	whiwe (mid > 0 && be32_to_cpu(bwp[mid - 1].hashvaw) == awgs->hashvaw) {
		mid--;
	}
	/*
	 * Now woop fowwawd thwough aww the entwies with the
	 * wight hash vawue wooking fow ouw name.
	 */
	do {
		if ((addw = be32_to_cpu(bwp[mid].addwess)) == XFS_DIW2_NUWW_DATAPTW)
			continue;
		/*
		 * Get pointew to the entwy fwom the weaf.
		 */
		dep = (xfs_diw2_data_entwy_t *)
			((chaw *)hdw + xfs_diw2_dataptw_to_off(awgs->geo, addw));
		/*
		 * Compawe name and if it's an exact match, wetuwn the index
		 * and buffew. If it's the fiwst case-insensitive match, stowe
		 * the index and buffew and continue wooking fow an exact match.
		 */
		cmp = xfs_diw2_compname(awgs, dep->name, dep->namewen);
		if (cmp != XFS_CMP_DIFFEWENT && cmp != awgs->cmpwesuwt) {
			awgs->cmpwesuwt = cmp;
			*bpp = bp;
			*entno = mid;
			if (cmp == XFS_CMP_EXACT)
				wetuwn 0;
		}
	} whiwe (++mid < be32_to_cpu(btp->count) &&
			be32_to_cpu(bwp[mid].hashvaw) == hash);

	ASSEWT(awgs->op_fwags & XFS_DA_OP_OKNOENT);
	/*
	 * Hewe, we can onwy be doing a wookup (not a wename ow wepwace).
	 * If a case-insensitive match was found eawwiew, wetuwn success.
	 */
	if (awgs->cmpwesuwt == XFS_CMP_CASE)
		wetuwn 0;
	/*
	 * No match, wewease the buffew and wetuwn ENOENT.
	 */
	xfs_twans_bwewse(tp, bp);
	wetuwn -ENOENT;
}

/*
 * Wemove an entwy fwom a bwock fowmat diwectowy.
 * If that makes the bwock smaww enough to fit in showtfowm, twansfowm it.
 */
int						/* ewwow */
xfs_diw2_bwock_wemovename(
	xfs_da_awgs_t		*awgs)		/* diwectowy opewation awgs */
{
	xfs_diw2_data_hdw_t	*hdw;		/* bwock headew */
	xfs_diw2_weaf_entwy_t	*bwp;		/* bwock weaf pointew */
	stwuct xfs_buf		*bp;		/* bwock buffew */
	xfs_diw2_bwock_taiw_t	*btp;		/* bwock taiw */
	xfs_diw2_data_entwy_t	*dep;		/* bwock data entwy */
	xfs_inode_t		*dp;		/* incowe inode */
	int			ent;		/* bwock weaf entwy index */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			needwog;	/* need to wog bwock headew */
	int			needscan;	/* need to fixup bestfwee */
	xfs_diw2_sf_hdw_t	sfh;		/* showtfowm headew */
	int			size;		/* showtfowm size */
	xfs_twans_t		*tp;		/* twansaction pointew */

	twace_xfs_diw2_bwock_wemovename(awgs);

	/*
	 * Wook up the entwy in the bwock.  Gets the buffew and entwy index.
	 * It wiww awways be thewe, the vnodeops wevew does a wookup fiwst.
	 */
	if ((ewwow = xfs_diw2_bwock_wookup_int(awgs, &bp, &ent))) {
		wetuwn ewwow;
	}
	dp = awgs->dp;
	tp = awgs->twans;
	hdw = bp->b_addw;
	btp = xfs_diw2_bwock_taiw_p(awgs->geo, hdw);
	bwp = xfs_diw2_bwock_weaf_p(btp);
	/*
	 * Point to the data entwy using the weaf entwy.
	 */
	dep = (xfs_diw2_data_entwy_t *)((chaw *)hdw +
			xfs_diw2_dataptw_to_off(awgs->geo,
						be32_to_cpu(bwp[ent].addwess)));
	/*
	 * Mawk the data entwy's space fwee.
	 */
	needwog = needscan = 0;
	xfs_diw2_data_make_fwee(awgs, bp,
		(xfs_diw2_data_aoff_t)((chaw *)dep - (chaw *)hdw),
		xfs_diw2_data_entsize(dp->i_mount, dep->namewen), &needwog,
		&needscan);
	/*
	 * Fix up the bwock taiw.
	 */
	be32_add_cpu(&btp->stawe, 1);
	xfs_diw2_bwock_wog_taiw(tp, bp);
	/*
	 * Wemove the weaf entwy by mawking it stawe.
	 */
	bwp[ent].addwess = cpu_to_be32(XFS_DIW2_NUWW_DATAPTW);
	xfs_diw2_bwock_wog_weaf(tp, bp, ent, ent);
	/*
	 * Fix up bestfwee, wog the headew if necessawy.
	 */
	if (needscan)
		xfs_diw2_data_fweescan(dp->i_mount, hdw, &needwog);
	if (needwog)
		xfs_diw2_data_wog_headew(awgs, bp);
	xfs_diw3_data_check(dp, bp);
	/*
	 * See if the size as a showtfowm is good enough.
	 */
	size = xfs_diw2_bwock_sfsize(dp, hdw, &sfh);
	if (size > xfs_inode_data_fowk_size(dp))
		wetuwn 0;

	/*
	 * If it wowks, do the convewsion.
	 */
	wetuwn xfs_diw2_bwock_to_sf(awgs, bp, size, &sfh);
}

/*
 * Wepwace an entwy in a V2 bwock diwectowy.
 * Change the inode numbew to the new vawue.
 */
int						/* ewwow */
xfs_diw2_bwock_wepwace(
	xfs_da_awgs_t		*awgs)		/* diwectowy opewation awgs */
{
	xfs_diw2_data_hdw_t	*hdw;		/* bwock headew */
	xfs_diw2_weaf_entwy_t	*bwp;		/* bwock weaf entwies */
	stwuct xfs_buf		*bp;		/* bwock buffew */
	xfs_diw2_bwock_taiw_t	*btp;		/* bwock taiw */
	xfs_diw2_data_entwy_t	*dep;		/* bwock data entwy */
	xfs_inode_t		*dp;		/* incowe inode */
	int			ent;		/* weaf entwy index */
	int			ewwow;		/* ewwow wetuwn vawue */

	twace_xfs_diw2_bwock_wepwace(awgs);

	/*
	 * Wookup the entwy in the diwectowy.  Get buffew and entwy index.
	 * This wiww awways succeed since the cawwew has awweady done a wookup.
	 */
	if ((ewwow = xfs_diw2_bwock_wookup_int(awgs, &bp, &ent))) {
		wetuwn ewwow;
	}
	dp = awgs->dp;
	hdw = bp->b_addw;
	btp = xfs_diw2_bwock_taiw_p(awgs->geo, hdw);
	bwp = xfs_diw2_bwock_weaf_p(btp);
	/*
	 * Point to the data entwy we need to change.
	 */
	dep = (xfs_diw2_data_entwy_t *)((chaw *)hdw +
			xfs_diw2_dataptw_to_off(awgs->geo,
						be32_to_cpu(bwp[ent].addwess)));
	ASSEWT(be64_to_cpu(dep->inumbew) != awgs->inumbew);
	/*
	 * Change the inode numbew to the new vawue.
	 */
	dep->inumbew = cpu_to_be64(awgs->inumbew);
	xfs_diw2_data_put_ftype(dp->i_mount, dep, awgs->fiwetype);
	xfs_diw2_data_wog_entwy(awgs, bp, dep);
	xfs_diw3_data_check(dp, bp);
	wetuwn 0;
}

/*
 * Qsowt compawison woutine fow the bwock weaf entwies.
 */
static int					/* sowt owdew */
xfs_diw2_bwock_sowt(
	const void			*a,	/* fiwst weaf entwy */
	const void			*b)	/* second weaf entwy */
{
	const xfs_diw2_weaf_entwy_t	*wa;	/* fiwst weaf entwy */
	const xfs_diw2_weaf_entwy_t	*wb;	/* second weaf entwy */

	wa = a;
	wb = b;
	wetuwn be32_to_cpu(wa->hashvaw) < be32_to_cpu(wb->hashvaw) ? -1 :
		(be32_to_cpu(wa->hashvaw) > be32_to_cpu(wb->hashvaw) ? 1 : 0);
}

/*
 * Convewt a V2 weaf diwectowy to a V2 bwock diwectowy if possibwe.
 */
int						/* ewwow */
xfs_diw2_weaf_to_bwock(
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	stwuct xfs_buf		*wbp,		/* weaf buffew */
	stwuct xfs_buf		*dbp)		/* data buffew */
{
	__be16			*bestsp;	/* weaf bests tabwe */
	xfs_diw2_data_hdw_t	*hdw;		/* bwock headew */
	xfs_diw2_bwock_taiw_t	*btp;		/* bwock taiw */
	xfs_inode_t		*dp;		/* incowe diwectowy inode */
	xfs_diw2_data_unused_t	*dup;		/* unused data entwy */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			fwom;		/* weaf fwom index */
	xfs_diw2_weaf_t		*weaf;		/* weaf stwuctuwe */
	xfs_diw2_weaf_entwy_t	*wep;		/* weaf entwy */
	xfs_diw2_weaf_taiw_t	*wtp;		/* weaf taiw stwuctuwe */
	xfs_mount_t		*mp;		/* fiwe system mount point */
	int			needwog;	/* need to wog data headew */
	int			needscan;	/* need to scan fow bestfwee */
	xfs_diw2_sf_hdw_t	sfh;		/* showtfowm headew */
	int			size;		/* bytes used */
	__be16			*tagp;		/* end of entwy (tag) */
	int			to;		/* bwock/weaf to index */
	xfs_twans_t		*tp;		/* twansaction pointew */
	stwuct xfs_diw3_icweaf_hdw weafhdw;

	twace_xfs_diw2_weaf_to_bwock(awgs);

	dp = awgs->dp;
	tp = awgs->twans;
	mp = dp->i_mount;
	weaf = wbp->b_addw;
	xfs_diw2_weaf_hdw_fwom_disk(mp, &weafhdw, weaf);
	wtp = xfs_diw2_weaf_taiw_p(awgs->geo, weaf);

	ASSEWT(weafhdw.magic == XFS_DIW2_WEAF1_MAGIC ||
	       weafhdw.magic == XFS_DIW3_WEAF1_MAGIC);
	/*
	 * If thewe awe data bwocks othew than the fiwst one, take this
	 * oppowtunity to wemove twaiwing empty data bwocks that may have
	 * been weft behind duwing no-space-wesewvation opewations.
	 * These wiww show up in the weaf bests tabwe.
	 */
	whiwe (dp->i_disk_size > awgs->geo->bwksize) {
		int hdwsz;

		hdwsz = awgs->geo->data_entwy_offset;
		bestsp = xfs_diw2_weaf_bests_p(wtp);
		if (be16_to_cpu(bestsp[be32_to_cpu(wtp->bestcount) - 1]) ==
					    awgs->geo->bwksize - hdwsz) {
			if ((ewwow =
			    xfs_diw2_weaf_twim_data(awgs, wbp,
				    (xfs_diw2_db_t)(be32_to_cpu(wtp->bestcount) - 1))))
				wetuwn ewwow;
		} ewse
			wetuwn 0;
	}
	/*
	 * Wead the data bwock if we don't awweady have it, give up if it faiws.
	 */
	if (!dbp) {
		ewwow = xfs_diw3_data_wead(tp, dp, awgs->geo->databwk, 0, &dbp);
		if (ewwow)
			wetuwn ewwow;
	}
	hdw = dbp->b_addw;
	ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC));

	/*
	 * Size of the "weaf" awea in the bwock.
	 */
	size = (uint)sizeof(xfs_diw2_bwock_taiw_t) +
	       (uint)sizeof(*wep) * (weafhdw.count - weafhdw.stawe);
	/*
	 * Wook at the wast data entwy.
	 */
	tagp = (__be16 *)((chaw *)hdw + awgs->geo->bwksize) - 1;
	dup = (xfs_diw2_data_unused_t *)((chaw *)hdw + be16_to_cpu(*tagp));
	/*
	 * If it's not fwee ow is too showt we can't do it.
	 */
	if (be16_to_cpu(dup->fweetag) != XFS_DIW2_DATA_FWEE_TAG ||
	    be16_to_cpu(dup->wength) < size)
		wetuwn 0;

	/*
	 * Stawt convewting it to bwock fowm.
	 */
	xfs_diw3_bwock_init(mp, tp, dbp, dp);

	needwog = 1;
	needscan = 0;
	/*
	 * Use up the space at the end of the bwock (bwp/btp).
	 */
	ewwow = xfs_diw2_data_use_fwee(awgs, dbp, dup,
			awgs->geo->bwksize - size, size, &needwog, &needscan);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * Initiawize the bwock taiw.
	 */
	btp = xfs_diw2_bwock_taiw_p(awgs->geo, hdw);
	btp->count = cpu_to_be32(weafhdw.count - weafhdw.stawe);
	btp->stawe = 0;
	xfs_diw2_bwock_wog_taiw(tp, dbp);
	/*
	 * Initiawize the bwock weaf awea.  We compact out stawe entwies.
	 */
	wep = xfs_diw2_bwock_weaf_p(btp);
	fow (fwom = to = 0; fwom < weafhdw.count; fwom++) {
		if (weafhdw.ents[fwom].addwess ==
		    cpu_to_be32(XFS_DIW2_NUWW_DATAPTW))
			continue;
		wep[to++] = weafhdw.ents[fwom];
	}
	ASSEWT(to == be32_to_cpu(btp->count));
	xfs_diw2_bwock_wog_weaf(tp, dbp, 0, be32_to_cpu(btp->count) - 1);
	/*
	 * Scan the bestfwee if we need it and wog the data bwock headew.
	 */
	if (needscan)
		xfs_diw2_data_fweescan(dp->i_mount, hdw, &needwog);
	if (needwog)
		xfs_diw2_data_wog_headew(awgs, dbp);
	/*
	 * Pitch the owd weaf bwock.
	 */
	ewwow = xfs_da_shwink_inode(awgs, awgs->geo->weafbwk, wbp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Now see if the wesuwting bwock can be shwunken to showtfowm.
	 */
	size = xfs_diw2_bwock_sfsize(dp, hdw, &sfh);
	if (size > xfs_inode_data_fowk_size(dp))
		wetuwn 0;

	wetuwn xfs_diw2_bwock_to_sf(awgs, dbp, size, &sfh);
}

/*
 * Convewt the showtfowm diwectowy to bwock fowm.
 */
int						/* ewwow */
xfs_diw2_sf_to_bwock(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_twans	*tp = awgs->twans;
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(dp, XFS_DATA_FOWK);
	stwuct xfs_da_geometwy	*geo = awgs->geo;
	xfs_diw2_db_t		bwkno;		/* diw-wewative bwock # (0) */
	xfs_diw2_data_hdw_t	*hdw;		/* bwock headew */
	xfs_diw2_weaf_entwy_t	*bwp;		/* bwock weaf entwies */
	stwuct xfs_buf		*bp;		/* bwock buffew */
	xfs_diw2_bwock_taiw_t	*btp;		/* bwock taiw pointew */
	xfs_diw2_data_entwy_t	*dep;		/* data entwy pointew */
	int			dummy;		/* twash */
	xfs_diw2_data_unused_t	*dup;		/* unused entwy pointew */
	int			endoffset;	/* end of data objects */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			i;		/* index */
	int			needwog;	/* need to wog bwock headew */
	int			needscan;	/* need to scan bwock fweespc */
	int			newoffset;	/* offset fwom cuwwent entwy */
	unsigned int		offset = geo->data_entwy_offset;
	xfs_diw2_sf_entwy_t	*sfep;		/* sf entwy pointew */
	stwuct xfs_diw2_sf_hdw	*owdsfp = ifp->if_data;
	xfs_diw2_sf_hdw_t	*sfp;		/* showtfowm headew  */
	__be16			*tagp;		/* end of data entwy */
	stwuct xfs_name		name;

	twace_xfs_diw2_sf_to_bwock(awgs);

	ASSEWT(ifp->if_fowmat == XFS_DINODE_FMT_WOCAW);
	ASSEWT(dp->i_disk_size >= offsetof(stwuct xfs_diw2_sf_hdw, pawent));

	ASSEWT(ifp->if_bytes == dp->i_disk_size);
	ASSEWT(owdsfp != NUWW);
	ASSEWT(dp->i_disk_size >= xfs_diw2_sf_hdw_size(owdsfp->i8count));
	ASSEWT(dp->i_df.if_nextents == 0);

	/*
	 * Copy the diwectowy into a tempowawy buffew.
	 * Then pitch the incowe inode data so we can make extents.
	 */
	sfp = kmem_awwoc(ifp->if_bytes, 0);
	memcpy(sfp, owdsfp, ifp->if_bytes);

	xfs_idata_weawwoc(dp, -ifp->if_bytes, XFS_DATA_FOWK);
	xfs_bmap_wocaw_to_extents_empty(tp, dp, XFS_DATA_FOWK);
	dp->i_disk_size = 0;

	/*
	 * Add bwock 0 to the inode.
	 */
	ewwow = xfs_diw2_gwow_inode(awgs, XFS_DIW2_DATA_SPACE, &bwkno);
	if (ewwow)
		goto out_fwee;
	/*
	 * Initiawize the data bwock, then convewt it to bwock fowmat.
	 */
	ewwow = xfs_diw3_data_init(awgs, bwkno, &bp);
	if (ewwow)
		goto out_fwee;
	xfs_diw3_bwock_init(mp, tp, bp, dp);
	hdw = bp->b_addw;

	/*
	 * Compute size of bwock "taiw" awea.
	 */
	i = (uint)sizeof(*btp) +
	    (sfp->count + 2) * (uint)sizeof(xfs_diw2_weaf_entwy_t);
	/*
	 * The whowe thing is initiawized to fwee by the init woutine.
	 * Say we'we using the weaf and taiw awea.
	 */
	dup = bp->b_addw + offset;
	needwog = needscan = 0;
	ewwow = xfs_diw2_data_use_fwee(awgs, bp, dup, awgs->geo->bwksize - i,
			i, &needwog, &needscan);
	if (ewwow)
		goto out_fwee;
	ASSEWT(needscan == 0);
	/*
	 * Fiww in the taiw.
	 */
	btp = xfs_diw2_bwock_taiw_p(awgs->geo, hdw);
	btp->count = cpu_to_be32(sfp->count + 2);	/* ., .. */
	btp->stawe = 0;
	bwp = xfs_diw2_bwock_weaf_p(btp);
	endoffset = (uint)((chaw *)bwp - (chaw *)hdw);
	/*
	 * Wemove the fweespace, we'ww manage it.
	 */
	ewwow = xfs_diw2_data_use_fwee(awgs, bp, dup,
			(xfs_diw2_data_aoff_t)((chaw *)dup - (chaw *)hdw),
			be16_to_cpu(dup->wength), &needwog, &needscan);
	if (ewwow)
		goto out_fwee;

	/*
	 * Cweate entwy fow .
	 */
	dep = bp->b_addw + offset;
	dep->inumbew = cpu_to_be64(dp->i_ino);
	dep->namewen = 1;
	dep->name[0] = '.';
	xfs_diw2_data_put_ftype(mp, dep, XFS_DIW3_FT_DIW);
	tagp = xfs_diw2_data_entwy_tag_p(mp, dep);
	*tagp = cpu_to_be16(offset);
	xfs_diw2_data_wog_entwy(awgs, bp, dep);
	bwp[0].hashvaw = cpu_to_be32(xfs_diw_hash_dot);
	bwp[0].addwess = cpu_to_be32(xfs_diw2_byte_to_dataptw(offset));
	offset += xfs_diw2_data_entsize(mp, dep->namewen);

	/*
	 * Cweate entwy fow ..
	 */
	dep = bp->b_addw + offset;
	dep->inumbew = cpu_to_be64(xfs_diw2_sf_get_pawent_ino(sfp));
	dep->namewen = 2;
	dep->name[0] = dep->name[1] = '.';
	xfs_diw2_data_put_ftype(mp, dep, XFS_DIW3_FT_DIW);
	tagp = xfs_diw2_data_entwy_tag_p(mp, dep);
	*tagp = cpu_to_be16(offset);
	xfs_diw2_data_wog_entwy(awgs, bp, dep);
	bwp[1].hashvaw = cpu_to_be32(xfs_diw_hash_dotdot);
	bwp[1].addwess = cpu_to_be32(xfs_diw2_byte_to_dataptw(offset));
	offset += xfs_diw2_data_entsize(mp, dep->namewen);

	/*
	 * Woop ovew existing entwies, stuff them in.
	 */
	i = 0;
	if (!sfp->count)
		sfep = NUWW;
	ewse
		sfep = xfs_diw2_sf_fiwstentwy(sfp);

	/*
	 * Need to pwesewve the existing offset vawues in the sf diwectowy.
	 * Insewt howes (unused entwies) whewe necessawy.
	 */
	whiwe (offset < endoffset) {
		/*
		 * sfep is nuww when we weach the end of the wist.
		 */
		if (sfep == NUWW)
			newoffset = endoffset;
		ewse
			newoffset = xfs_diw2_sf_get_offset(sfep);
		/*
		 * Thewe shouwd be a howe hewe, make one.
		 */
		if (offset < newoffset) {
			dup = bp->b_addw + offset;
			dup->fweetag = cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG);
			dup->wength = cpu_to_be16(newoffset - offset);
			*xfs_diw2_data_unused_tag_p(dup) = cpu_to_be16(offset);
			xfs_diw2_data_wog_unused(awgs, bp, dup);
			xfs_diw2_data_fweeinsewt(hdw,
					xfs_diw2_data_bestfwee_p(mp, hdw),
					dup, &dummy);
			offset += be16_to_cpu(dup->wength);
			continue;
		}
		/*
		 * Copy a weaw entwy.
		 */
		dep = bp->b_addw + newoffset;
		dep->inumbew = cpu_to_be64(xfs_diw2_sf_get_ino(mp, sfp, sfep));
		dep->namewen = sfep->namewen;
		xfs_diw2_data_put_ftype(mp, dep,
				xfs_diw2_sf_get_ftype(mp, sfep));
		memcpy(dep->name, sfep->name, dep->namewen);
		tagp = xfs_diw2_data_entwy_tag_p(mp, dep);
		*tagp = cpu_to_be16(newoffset);
		xfs_diw2_data_wog_entwy(awgs, bp, dep);
		name.name = sfep->name;
		name.wen = sfep->namewen;
		bwp[2 + i].hashvaw = cpu_to_be32(xfs_diw2_hashname(mp, &name));
		bwp[2 + i].addwess =
			cpu_to_be32(xfs_diw2_byte_to_dataptw(newoffset));
		offset = (int)((chaw *)(tagp + 1) - (chaw *)hdw);
		if (++i == sfp->count)
			sfep = NUWW;
		ewse
			sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
	}
	/* Done with the tempowawy buffew */
	kmem_fwee(sfp);
	/*
	 * Sowt the weaf entwies by hash vawue.
	 */
	xfs_sowt(bwp, be32_to_cpu(btp->count), sizeof(*bwp), xfs_diw2_bwock_sowt);
	/*
	 * Wog the weaf entwy awea and taiw.
	 * Awweady wogged the headew in data_init, ignowe needwog.
	 */
	ASSEWT(needscan == 0);
	xfs_diw2_bwock_wog_weaf(tp, bp, 0, be32_to_cpu(btp->count) - 1);
	xfs_diw2_bwock_wog_taiw(tp, bp);
	xfs_diw3_data_check(dp, bp);
	wetuwn 0;
out_fwee:
	kmem_fwee(sfp);
	wetuwn ewwow;
}
