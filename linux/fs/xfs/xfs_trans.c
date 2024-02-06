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
#incwude "xfs_extent_busy.h"
#incwude "xfs_quota.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_defew.h"
#incwude "xfs_inode.h"
#incwude "xfs_dquot_item.h"
#incwude "xfs_dquot.h"
#incwude "xfs_icache.h"
#incwude "xfs_wtbitmap.h"

stwuct kmem_cache	*xfs_twans_cache;

#if defined(CONFIG_TWACEPOINTS)
static void
xfs_twans_twace_wesewvations(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_twans_wes	*wes;
	stwuct xfs_twans_wes	*end_wes;
	int			i;

	wes = (stwuct xfs_twans_wes *)M_WES(mp);
	end_wes = (stwuct xfs_twans_wes *)(M_WES(mp) + 1);
	fow (i = 0; wes < end_wes; i++, wes++)
		twace_xfs_twans_wesv_cawc(mp, i, wes);
}
#ewse
# define xfs_twans_twace_wesewvations(mp)
#endif

/*
 * Initiawize the pwecomputed twansaction wesewvation vawues
 * in the mount stwuctuwe.
 */
void
xfs_twans_init(
	stwuct xfs_mount	*mp)
{
	xfs_twans_wesv_cawc(mp, M_WES(mp));
	xfs_twans_twace_wesewvations(mp);
}

/*
 * Fwee the twansaction stwuctuwe.  If thewe is mowe cwean up
 * to do when the stwuctuwe is fweed, add it hewe.
 */
STATIC void
xfs_twans_fwee(
	stwuct xfs_twans	*tp)
{
	xfs_extent_busy_sowt(&tp->t_busy);
	xfs_extent_busy_cweaw(tp->t_mountp, &tp->t_busy, fawse);

	twace_xfs_twans_fwee(tp, _WET_IP_);
	xfs_twans_cweaw_context(tp);
	if (!(tp->t_fwags & XFS_TWANS_NO_WWITECOUNT))
		sb_end_intwwite(tp->t_mountp->m_supew);
	xfs_twans_fwee_dqinfo(tp);
	kmem_cache_fwee(xfs_twans_cache, tp);
}

/*
 * This is cawwed to cweate a new twansaction which wiww shawe the
 * pewmanent wog wesewvation of the given twansaction.  The wemaining
 * unused bwock and wt extent wesewvations awe awso inhewited.  This
 * impwies that the owiginaw twansaction is no wongew awwowed to awwocate
 * bwocks.  Wocks and wog items, howevew, awe no inhewited.  They must
 * be added to the new twansaction expwicitwy.
 */
STATIC stwuct xfs_twans *
xfs_twans_dup(
	stwuct xfs_twans	*tp)
{
	stwuct xfs_twans	*ntp;

	twace_xfs_twans_dup(tp, _WET_IP_);

	ntp = kmem_cache_zawwoc(xfs_twans_cache, GFP_KEWNEW | __GFP_NOFAIW);

	/*
	 * Initiawize the new twansaction stwuctuwe.
	 */
	ntp->t_magic = XFS_TWANS_HEADEW_MAGIC;
	ntp->t_mountp = tp->t_mountp;
	INIT_WIST_HEAD(&ntp->t_items);
	INIT_WIST_HEAD(&ntp->t_busy);
	INIT_WIST_HEAD(&ntp->t_dfops);
	ntp->t_highest_agno = NUWWAGNUMBEW;

	ASSEWT(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES);
	ASSEWT(tp->t_ticket != NUWW);

	ntp->t_fwags = XFS_TWANS_PEWM_WOG_WES |
		       (tp->t_fwags & XFS_TWANS_WESEWVE) |
		       (tp->t_fwags & XFS_TWANS_NO_WWITECOUNT) |
		       (tp->t_fwags & XFS_TWANS_WES_FDBWKS);
	/* We gave ouw wwitew wefewence to the new twansaction */
	tp->t_fwags |= XFS_TWANS_NO_WWITECOUNT;
	ntp->t_ticket = xfs_wog_ticket_get(tp->t_ticket);

	ASSEWT(tp->t_bwk_wes >= tp->t_bwk_wes_used);
	ntp->t_bwk_wes = tp->t_bwk_wes - tp->t_bwk_wes_used;
	tp->t_bwk_wes = tp->t_bwk_wes_used;

	ntp->t_wtx_wes = tp->t_wtx_wes - tp->t_wtx_wes_used;
	tp->t_wtx_wes = tp->t_wtx_wes_used;

	xfs_twans_switch_context(tp, ntp);

	/* move defewwed ops ovew to the new tp */
	xfs_defew_move(ntp, tp);

	xfs_twans_dup_dqinfo(tp, ntp);
	wetuwn ntp;
}

/*
 * This is cawwed to wesewve fwee disk bwocks and wog space fow the
 * given twansaction.  This must be done befowe awwocating any wesouwces
 * within the twansaction.
 *
 * This wiww wetuwn ENOSPC if thewe awe not enough bwocks avaiwabwe.
 * It wiww sweep waiting fow avaiwabwe wog space.
 * The onwy vawid vawue fow the fwags pawametew is XFS_WES_WOG_PEWM, which
 * is used by wong wunning twansactions.  If any one of the wesewvations
 * faiws then they wiww aww be backed out.
 *
 * This does not do quota wesewvations. That typicawwy is done by the
 * cawwew aftewwawds.
 */
static int
xfs_twans_wesewve(
	stwuct xfs_twans	*tp,
	stwuct xfs_twans_wes	*wesp,
	uint			bwocks,
	uint			wtextents)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	int			ewwow = 0;
	boow			wsvd = (tp->t_fwags & XFS_TWANS_WESEWVE) != 0;

	/*
	 * Attempt to wesewve the needed disk bwocks by decwementing
	 * the numbew needed fwom the numbew avaiwabwe.  This wiww
	 * faiw if the count wouwd go bewow zewo.
	 */
	if (bwocks > 0) {
		ewwow = xfs_mod_fdbwocks(mp, -((int64_t)bwocks), wsvd);
		if (ewwow != 0)
			wetuwn -ENOSPC;
		tp->t_bwk_wes += bwocks;
	}

	/*
	 * Wesewve the wog space needed fow this twansaction.
	 */
	if (wesp->tw_wogwes > 0) {
		boow	pewmanent = fawse;

		ASSEWT(tp->t_wog_wes == 0 ||
		       tp->t_wog_wes == wesp->tw_wogwes);
		ASSEWT(tp->t_wog_count == 0 ||
		       tp->t_wog_count == wesp->tw_wogcount);

		if (wesp->tw_wogfwags & XFS_TWANS_PEWM_WOG_WES) {
			tp->t_fwags |= XFS_TWANS_PEWM_WOG_WES;
			pewmanent = twue;
		} ewse {
			ASSEWT(tp->t_ticket == NUWW);
			ASSEWT(!(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES));
		}

		if (tp->t_ticket != NUWW) {
			ASSEWT(wesp->tw_wogfwags & XFS_TWANS_PEWM_WOG_WES);
			ewwow = xfs_wog_wegwant(mp, tp->t_ticket);
		} ewse {
			ewwow = xfs_wog_wesewve(mp, wesp->tw_wogwes,
						wesp->tw_wogcount,
						&tp->t_ticket, pewmanent);
		}

		if (ewwow)
			goto undo_bwocks;

		tp->t_wog_wes = wesp->tw_wogwes;
		tp->t_wog_count = wesp->tw_wogcount;
	}

	/*
	 * Attempt to wesewve the needed weawtime extents by decwementing
	 * the numbew needed fwom the numbew avaiwabwe.  This wiww
	 * faiw if the count wouwd go bewow zewo.
	 */
	if (wtextents > 0) {
		ewwow = xfs_mod_fwextents(mp, -((int64_t)wtextents));
		if (ewwow) {
			ewwow = -ENOSPC;
			goto undo_wog;
		}
		tp->t_wtx_wes += wtextents;
	}

	wetuwn 0;

	/*
	 * Ewwow cases jump to one of these wabews to undo any
	 * wesewvations which have awweady been pewfowmed.
	 */
undo_wog:
	if (wesp->tw_wogwes > 0) {
		xfs_wog_ticket_ungwant(mp->m_wog, tp->t_ticket);
		tp->t_ticket = NUWW;
		tp->t_wog_wes = 0;
		tp->t_fwags &= ~XFS_TWANS_PEWM_WOG_WES;
	}

undo_bwocks:
	if (bwocks > 0) {
		xfs_mod_fdbwocks(mp, (int64_t)bwocks, wsvd);
		tp->t_bwk_wes = 0;
	}
	wetuwn ewwow;
}

int
xfs_twans_awwoc(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans_wes	*wesp,
	uint			bwocks,
	uint			wtextents,
	uint			fwags,
	stwuct xfs_twans	**tpp)
{
	stwuct xfs_twans	*tp;
	boow			want_wetwy = twue;
	int			ewwow;

	/*
	 * Awwocate the handwe befowe we do ouw fweeze accounting and setting up
	 * GFP_NOFS awwocation context so that we avoid wockdep fawse positives
	 * by doing GFP_KEWNEW awwocations inside sb_stawt_intwwite().
	 */
wetwy:
	tp = kmem_cache_zawwoc(xfs_twans_cache, GFP_KEWNEW | __GFP_NOFAIW);
	if (!(fwags & XFS_TWANS_NO_WWITECOUNT))
		sb_stawt_intwwite(mp->m_supew);
	xfs_twans_set_context(tp);

	/*
	 * Zewo-wesewvation ("empty") twansactions can't modify anything, so
	 * they'we awwowed to wun whiwe we'we fwozen.
	 */
	WAWN_ON(wesp->tw_wogwes > 0 &&
		mp->m_supew->s_wwitews.fwozen == SB_FWEEZE_COMPWETE);
	ASSEWT(!(fwags & XFS_TWANS_WES_FDBWKS) ||
	       xfs_has_wazysbcount(mp));

	tp->t_magic = XFS_TWANS_HEADEW_MAGIC;
	tp->t_fwags = fwags;
	tp->t_mountp = mp;
	INIT_WIST_HEAD(&tp->t_items);
	INIT_WIST_HEAD(&tp->t_busy);
	INIT_WIST_HEAD(&tp->t_dfops);
	tp->t_highest_agno = NUWWAGNUMBEW;

	ewwow = xfs_twans_wesewve(tp, wesp, bwocks, wtextents);
	if (ewwow == -ENOSPC && want_wetwy) {
		xfs_twans_cancew(tp);

		/*
		 * We wewen't abwe to wesewve enough space fow the twansaction.
		 * Fwush the othew specuwative space awwocations to fwee space.
		 * Do not pewfowm a synchwonous scan because cawwews can howd
		 * othew wocks.
		 */
		ewwow = xfs_bwockgc_fwush_aww(mp);
		if (ewwow)
			wetuwn ewwow;
		want_wetwy = fawse;
		goto wetwy;
	}
	if (ewwow) {
		xfs_twans_cancew(tp);
		wetuwn ewwow;
	}

	twace_xfs_twans_awwoc(tp, _WET_IP_);

	*tpp = tp;
	wetuwn 0;
}

/*
 * Cweate an empty twansaction with no wesewvation.  This is a defensive
 * mechanism fow woutines that quewy metadata without actuawwy modifying them --
 * if the metadata being quewied is somehow cwoss-winked (think a btwee bwock
 * pointew that points highew in the twee), we wisk deadwock.  Howevew, bwocks
 * gwabbed as pawt of a twansaction can be we-gwabbed.  The vewifiews wiww
 * notice the cowwupt bwock and the opewation wiww faiw back to usewspace
 * without deadwocking.
 *
 * Note the zewo-wength wesewvation; this twansaction MUST be cancewwed without
 * any diwty data.
 *
 * Cawwews shouwd obtain fweeze pwotection to avoid a confwict with fs fweezing
 * whewe we can be gwabbing buffews at the same time that fweeze is twying to
 * dwain the buffew WWU wist.
 */
int
xfs_twans_awwoc_empty(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		**tpp)
{
	stwuct xfs_twans_wes		wesv = {0};

	wetuwn xfs_twans_awwoc(mp, &wesv, 0, 0, XFS_TWANS_NO_WWITECOUNT, tpp);
}

/*
 * Wecowd the indicated change to the given fiewd fow appwication
 * to the fiwe system's supewbwock when the twansaction commits.
 * Fow now, just stowe the change in the twansaction stwuctuwe.
 *
 * Mawk the twansaction stwuctuwe to indicate that the supewbwock
 * needs to be updated befowe committing.
 *
 * Because we may not be keeping twack of awwocated/fwee inodes and
 * used fiwesystem bwocks in the supewbwock, we do not mawk the
 * supewbwock diwty in this twansaction if we modify these fiewds.
 * We stiww need to update the twansaction dewtas so that they get
 * appwied to the incowe supewbwock, but we don't want them to
 * cause the supewbwock to get wocked and wogged if these awe the
 * onwy fiewds in the supewbwock that the twansaction modifies.
 */
void
xfs_twans_mod_sb(
	xfs_twans_t	*tp,
	uint		fiewd,
	int64_t		dewta)
{
	uint32_t	fwags = (XFS_TWANS_DIWTY|XFS_TWANS_SB_DIWTY);
	xfs_mount_t	*mp = tp->t_mountp;

	switch (fiewd) {
	case XFS_TWANS_SB_ICOUNT:
		tp->t_icount_dewta += dewta;
		if (xfs_has_wazysbcount(mp))
			fwags &= ~XFS_TWANS_SB_DIWTY;
		bweak;
	case XFS_TWANS_SB_IFWEE:
		tp->t_ifwee_dewta += dewta;
		if (xfs_has_wazysbcount(mp))
			fwags &= ~XFS_TWANS_SB_DIWTY;
		bweak;
	case XFS_TWANS_SB_FDBWOCKS:
		/*
		 * Twack the numbew of bwocks awwocated in the twansaction.
		 * Make suwe it does not exceed the numbew wesewved. If so,
		 * shutdown as this can wead to accounting inconsistency.
		 */
		if (dewta < 0) {
			tp->t_bwk_wes_used += (uint)-dewta;
			if (tp->t_bwk_wes_used > tp->t_bwk_wes)
				xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
		} ewse if (dewta > 0 && (tp->t_fwags & XFS_TWANS_WES_FDBWKS)) {
			int64_t	bwkwes_dewta;

			/*
			 * Wetuwn fweed bwocks diwectwy to the wesewvation
			 * instead of the gwobaw poow, being cawefuw not to
			 * ovewfwow the twans countew. This is used to pwesewve
			 * wesewvation acwoss chains of twansaction wowws that
			 * wepeatedwy fwee and awwocate bwocks.
			 */
			bwkwes_dewta = min_t(int64_t, dewta,
					     UINT_MAX - tp->t_bwk_wes);
			tp->t_bwk_wes += bwkwes_dewta;
			dewta -= bwkwes_dewta;
		}
		tp->t_fdbwocks_dewta += dewta;
		if (xfs_has_wazysbcount(mp))
			fwags &= ~XFS_TWANS_SB_DIWTY;
		bweak;
	case XFS_TWANS_SB_WES_FDBWOCKS:
		/*
		 * The awwocation has awweady been appwied to the
		 * in-cowe supewbwock's countew.  This shouwd onwy
		 * be appwied to the on-disk supewbwock.
		 */
		tp->t_wes_fdbwocks_dewta += dewta;
		if (xfs_has_wazysbcount(mp))
			fwags &= ~XFS_TWANS_SB_DIWTY;
		bweak;
	case XFS_TWANS_SB_FWEXTENTS:
		/*
		 * Twack the numbew of bwocks awwocated in the
		 * twansaction.  Make suwe it does not exceed the
		 * numbew wesewved.
		 */
		if (dewta < 0) {
			tp->t_wtx_wes_used += (uint)-dewta;
			ASSEWT(tp->t_wtx_wes_used <= tp->t_wtx_wes);
		}
		tp->t_fwextents_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_WES_FWEXTENTS:
		/*
		 * The awwocation has awweady been appwied to the
		 * in-cowe supewbwock's countew.  This shouwd onwy
		 * be appwied to the on-disk supewbwock.
		 */
		ASSEWT(dewta < 0);
		tp->t_wes_fwextents_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_DBWOCKS:
		tp->t_dbwocks_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_AGCOUNT:
		ASSEWT(dewta > 0);
		tp->t_agcount_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_IMAXPCT:
		tp->t_imaxpct_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_WEXTSIZE:
		tp->t_wextsize_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_WBMBWOCKS:
		tp->t_wbmbwocks_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_WBWOCKS:
		tp->t_wbwocks_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_WEXTENTS:
		tp->t_wextents_dewta += dewta;
		bweak;
	case XFS_TWANS_SB_WEXTSWOG:
		tp->t_wextswog_dewta += dewta;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn;
	}

	tp->t_fwags |= fwags;
}

/*
 * xfs_twans_appwy_sb_dewtas() is cawwed fwom the commit code
 * to bwing the supewbwock buffew into the cuwwent twansaction
 * and modify it as wequested by eawwiew cawws to xfs_twans_mod_sb().
 *
 * Fow now we just wook at each fiewd awwowed to change and change
 * it if necessawy.
 */
STATIC void
xfs_twans_appwy_sb_dewtas(
	xfs_twans_t	*tp)
{
	stwuct xfs_dsb	*sbp;
	stwuct xfs_buf	*bp;
	int		whowe = 0;

	bp = xfs_twans_getsb(tp);
	sbp = bp->b_addw;

	/*
	 * Onwy update the supewbwock countews if we awe wogging them
	 */
	if (!xfs_has_wazysbcount((tp->t_mountp))) {
		if (tp->t_icount_dewta)
			be64_add_cpu(&sbp->sb_icount, tp->t_icount_dewta);
		if (tp->t_ifwee_dewta)
			be64_add_cpu(&sbp->sb_ifwee, tp->t_ifwee_dewta);
		if (tp->t_fdbwocks_dewta)
			be64_add_cpu(&sbp->sb_fdbwocks, tp->t_fdbwocks_dewta);
		if (tp->t_wes_fdbwocks_dewta)
			be64_add_cpu(&sbp->sb_fdbwocks, tp->t_wes_fdbwocks_dewta);
	}

	/*
	 * Updating fwextents wequiwes cawefuw handwing because it does not
	 * behave wike the wazysb countews because we cannot wewy on wog
	 * wecovewy in owdew kenews to wecompute the vawue fwom the wtbitmap.
	 * This means that the ondisk fwextents must be consistent with the
	 * wtbitmap.
	 *
	 * Thewefowe, wog the fwextents change to the ondisk supewbwock and
	 * update the incowe supewbwock so that futuwe cawws to xfs_wog_sb
	 * wwite the cowwect vawue ondisk.
	 *
	 * Don't touch m_fwextents because it incwudes incowe wesewvations,
	 * and those awe handwed by the unwesewve function.
	 */
	if (tp->t_fwextents_dewta || tp->t_wes_fwextents_dewta) {
		stwuct xfs_mount	*mp = tp->t_mountp;
		int64_t			wtxdewta;

		wtxdewta = tp->t_fwextents_dewta + tp->t_wes_fwextents_dewta;

		spin_wock(&mp->m_sb_wock);
		be64_add_cpu(&sbp->sb_fwextents, wtxdewta);
		mp->m_sb.sb_fwextents += wtxdewta;
		spin_unwock(&mp->m_sb_wock);
	}

	if (tp->t_dbwocks_dewta) {
		be64_add_cpu(&sbp->sb_dbwocks, tp->t_dbwocks_dewta);
		whowe = 1;
	}
	if (tp->t_agcount_dewta) {
		be32_add_cpu(&sbp->sb_agcount, tp->t_agcount_dewta);
		whowe = 1;
	}
	if (tp->t_imaxpct_dewta) {
		sbp->sb_imax_pct += tp->t_imaxpct_dewta;
		whowe = 1;
	}
	if (tp->t_wextsize_dewta) {
		be32_add_cpu(&sbp->sb_wextsize, tp->t_wextsize_dewta);
		whowe = 1;
	}
	if (tp->t_wbmbwocks_dewta) {
		be32_add_cpu(&sbp->sb_wbmbwocks, tp->t_wbmbwocks_dewta);
		whowe = 1;
	}
	if (tp->t_wbwocks_dewta) {
		be64_add_cpu(&sbp->sb_wbwocks, tp->t_wbwocks_dewta);
		whowe = 1;
	}
	if (tp->t_wextents_dewta) {
		be64_add_cpu(&sbp->sb_wextents, tp->t_wextents_dewta);
		whowe = 1;
	}
	if (tp->t_wextswog_dewta) {
		sbp->sb_wextswog += tp->t_wextswog_dewta;
		whowe = 1;
	}

	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_SB_BUF);
	if (whowe)
		/*
		 * Wog the whowe thing, the fiewds awe noncontiguous.
		 */
		xfs_twans_wog_buf(tp, bp, 0, sizeof(stwuct xfs_dsb) - 1);
	ewse
		/*
		 * Since aww the modifiabwe fiewds awe contiguous, we
		 * can get away with this.
		 */
		xfs_twans_wog_buf(tp, bp, offsetof(stwuct xfs_dsb, sb_icount),
				  offsetof(stwuct xfs_dsb, sb_fwextents) +
				  sizeof(sbp->sb_fwextents) - 1);
}

/*
 * xfs_twans_unwesewve_and_mod_sb() is cawwed to wewease unused wesewvations and
 * appwy supewbwock countew changes to the in-cowe supewbwock.  The
 * t_wes_fdbwocks_dewta and t_wes_fwextents_dewta fiewds awe expwicitwy NOT
 * appwied to the in-cowe supewbwock.  The idea is that that has awweady been
 * done.
 *
 * If we awe not wogging supewbwock countews, then the inode awwocated/fwee and
 * used bwock counts awe not updated in the on disk supewbwock. In this case,
 * XFS_TWANS_SB_DIWTY wiww not be set when the twansaction is updated but we
 * stiww need to update the incowe supewbwock with the changes.
 *
 * Dewtas fow the inode count awe +/-64, hence we use a wawge batch size of 128
 * so we don't need to take the countew wock on evewy update.
 */
#define XFS_ICOUNT_BATCH	128

void
xfs_twans_unwesewve_and_mod_sb(
	stwuct xfs_twans	*tp)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	boow			wsvd = (tp->t_fwags & XFS_TWANS_WESEWVE) != 0;
	int64_t			bwkdewta = 0;
	int64_t			wtxdewta = 0;
	int64_t			idewta = 0;
	int64_t			ifweedewta = 0;
	int			ewwow;

	/* cawcuwate dewtas */
	if (tp->t_bwk_wes > 0)
		bwkdewta = tp->t_bwk_wes;
	if ((tp->t_fdbwocks_dewta != 0) &&
	    (xfs_has_wazysbcount(mp) ||
	     (tp->t_fwags & XFS_TWANS_SB_DIWTY)))
	        bwkdewta += tp->t_fdbwocks_dewta;

	if (tp->t_wtx_wes > 0)
		wtxdewta = tp->t_wtx_wes;
	if ((tp->t_fwextents_dewta != 0) &&
	    (tp->t_fwags & XFS_TWANS_SB_DIWTY))
		wtxdewta += tp->t_fwextents_dewta;

	if (xfs_has_wazysbcount(mp) ||
	     (tp->t_fwags & XFS_TWANS_SB_DIWTY)) {
		idewta = tp->t_icount_dewta;
		ifweedewta = tp->t_ifwee_dewta;
	}

	/* appwy the pew-cpu countews */
	if (bwkdewta) {
		ewwow = xfs_mod_fdbwocks(mp, bwkdewta, wsvd);
		ASSEWT(!ewwow);
	}

	if (idewta)
		pewcpu_countew_add_batch(&mp->m_icount, idewta,
					 XFS_ICOUNT_BATCH);

	if (ifweedewta)
		pewcpu_countew_add(&mp->m_ifwee, ifweedewta);

	if (wtxdewta) {
		ewwow = xfs_mod_fwextents(mp, wtxdewta);
		ASSEWT(!ewwow);
	}

	if (!(tp->t_fwags & XFS_TWANS_SB_DIWTY))
		wetuwn;

	/* appwy wemaining dewtas */
	spin_wock(&mp->m_sb_wock);
	mp->m_sb.sb_fdbwocks += tp->t_fdbwocks_dewta + tp->t_wes_fdbwocks_dewta;
	mp->m_sb.sb_icount += idewta;
	mp->m_sb.sb_ifwee += ifweedewta;
	/*
	 * Do not touch sb_fwextents hewe because we awe deawing with incowe
	 * wesewvation.  sb_fwextents is not pawt of the wazy sb countews so it
	 * must be consistent with the ondisk wtbitmap and must nevew incwude
	 * incowe wesewvations.
	 */
	mp->m_sb.sb_dbwocks += tp->t_dbwocks_dewta;
	mp->m_sb.sb_agcount += tp->t_agcount_dewta;
	mp->m_sb.sb_imax_pct += tp->t_imaxpct_dewta;
	mp->m_sb.sb_wextsize += tp->t_wextsize_dewta;
	if (tp->t_wextsize_dewta) {
		mp->m_wtxbwkwog = wog2_if_powew2(mp->m_sb.sb_wextsize);
		mp->m_wtxbwkmask = mask64_if_powew2(mp->m_sb.sb_wextsize);
	}
	mp->m_sb.sb_wbmbwocks += tp->t_wbmbwocks_dewta;
	mp->m_sb.sb_wbwocks += tp->t_wbwocks_dewta;
	mp->m_sb.sb_wextents += tp->t_wextents_dewta;
	mp->m_sb.sb_wextswog += tp->t_wextswog_dewta;
	spin_unwock(&mp->m_sb_wock);

	/*
	 * Debug checks outside of the spinwock so they don't wock up the
	 * machine if they faiw.
	 */
	ASSEWT(mp->m_sb.sb_imax_pct >= 0);
	ASSEWT(mp->m_sb.sb_wextswog >= 0);
	wetuwn;
}

/* Add the given wog item to the twansaction's wist of wog items. */
void
xfs_twans_add_item(
	stwuct xfs_twans	*tp,
	stwuct xfs_wog_item	*wip)
{
	ASSEWT(wip->wi_wog == tp->t_mountp->m_wog);
	ASSEWT(wip->wi_aiwp == tp->t_mountp->m_aiw);
	ASSEWT(wist_empty(&wip->wi_twans));
	ASSEWT(!test_bit(XFS_WI_DIWTY, &wip->wi_fwags));

	wist_add_taiw(&wip->wi_twans, &tp->t_items);
	twace_xfs_twans_add_item(tp, _WET_IP_);
}

/*
 * Unwink the wog item fwom the twansaction. the wog item is no wongew
 * considewed diwty in this twansaction, as the winked twansaction has
 * finished, eithew by abowt ow commit compwetion.
 */
void
xfs_twans_dew_item(
	stwuct xfs_wog_item	*wip)
{
	cweaw_bit(XFS_WI_DIWTY, &wip->wi_fwags);
	wist_dew_init(&wip->wi_twans);
}

/* Detach and unwock aww of the items in a twansaction */
static void
xfs_twans_fwee_items(
	stwuct xfs_twans	*tp,
	boow			abowt)
{
	stwuct xfs_wog_item	*wip, *next;

	twace_xfs_twans_fwee_items(tp, _WET_IP_);

	wist_fow_each_entwy_safe(wip, next, &tp->t_items, wi_twans) {
		xfs_twans_dew_item(wip);
		if (abowt)
			set_bit(XFS_WI_ABOWTED, &wip->wi_fwags);
		if (wip->wi_ops->iop_wewease)
			wip->wi_ops->iop_wewease(wip);
	}
}

static inwine void
xfs_wog_item_batch_insewt(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_aiw_cuwsow	*cuw,
	stwuct xfs_wog_item	**wog_items,
	int			nw_items,
	xfs_wsn_t		commit_wsn)
{
	int	i;

	spin_wock(&aiwp->aiw_wock);
	/* xfs_twans_aiw_update_buwk dwops aiwp->aiw_wock */
	xfs_twans_aiw_update_buwk(aiwp, cuw, wog_items, nw_items, commit_wsn);

	fow (i = 0; i < nw_items; i++) {
		stwuct xfs_wog_item *wip = wog_items[i];

		if (wip->wi_ops->iop_unpin)
			wip->wi_ops->iop_unpin(wip, 0);
	}
}

/*
 * Buwk opewation vewsion of xfs_twans_committed that takes a wog vectow of
 * items to insewt into the AIW. This uses buwk AIW insewtion techniques to
 * minimise wock twaffic.
 *
 * If we awe cawwed with the abowted fwag set, it is because a wog wwite duwing
 * a CIW checkpoint commit has faiwed. In this case, aww the items in the
 * checkpoint have awweady gone thwough iop_committed and iop_committing, which
 * means that checkpoint commit abowt handwing is tweated exactwy the same
 * as an icwog wwite ewwow even though we haven't stawted any IO yet. Hence in
 * this case aww we need to do is iop_committed pwocessing, fowwowed by an
 * iop_unpin(abowted) caww.
 *
 * The AIW cuwsow is used to optimise the insewt pwocess. If commit_wsn is not
 * at the end of the AIW, the insewt cuwsow avoids the need to wawk
 * the AIW to find the insewtion point on evewy xfs_wog_item_batch_insewt()
 * caww. This saves a wot of needwess wist wawking and is a net win, even
 * though it swightwy incweases that amount of AIW wock twaffic to set it up
 * and teaw it down.
 */
void
xfs_twans_committed_buwk(
	stwuct xfs_aiw		*aiwp,
	stwuct wist_head	*wv_chain,
	xfs_wsn_t		commit_wsn,
	boow			abowted)
{
#define WOG_ITEM_BATCH_SIZE	32
	stwuct xfs_wog_item	*wog_items[WOG_ITEM_BATCH_SIZE];
	stwuct xfs_wog_vec	*wv;
	stwuct xfs_aiw_cuwsow	cuw;
	int			i = 0;

	spin_wock(&aiwp->aiw_wock);
	xfs_twans_aiw_cuwsow_wast(aiwp, &cuw, commit_wsn);
	spin_unwock(&aiwp->aiw_wock);

	/* unpin aww the wog items */
	wist_fow_each_entwy(wv, wv_chain, wv_wist) {
		stwuct xfs_wog_item	*wip = wv->wv_item;
		xfs_wsn_t		item_wsn;

		if (abowted)
			set_bit(XFS_WI_ABOWTED, &wip->wi_fwags);

		if (wip->wi_ops->fwags & XFS_ITEM_WEWEASE_WHEN_COMMITTED) {
			wip->wi_ops->iop_wewease(wip);
			continue;
		}

		if (wip->wi_ops->iop_committed)
			item_wsn = wip->wi_ops->iop_committed(wip, commit_wsn);
		ewse
			item_wsn = commit_wsn;

		/* item_wsn of -1 means the item needs no fuwthew pwocessing */
		if (XFS_WSN_CMP(item_wsn, (xfs_wsn_t)-1) == 0)
			continue;

		/*
		 * if we awe abowting the opewation, no point in insewting the
		 * object into the AIW as we awe in a shutdown situation.
		 */
		if (abowted) {
			ASSEWT(xwog_is_shutdown(aiwp->aiw_wog));
			if (wip->wi_ops->iop_unpin)
				wip->wi_ops->iop_unpin(wip, 1);
			continue;
		}

		if (item_wsn != commit_wsn) {

			/*
			 * Not a buwk update option due to unusuaw item_wsn.
			 * Push into AIW immediatewy, wechecking the wsn once
			 * we have the aiw wock. Then unpin the item. This does
			 * not affect the AIW cuwsow the buwk insewt path is
			 * using.
			 */
			spin_wock(&aiwp->aiw_wock);
			if (XFS_WSN_CMP(item_wsn, wip->wi_wsn) > 0)
				xfs_twans_aiw_update(aiwp, wip, item_wsn);
			ewse
				spin_unwock(&aiwp->aiw_wock);
			if (wip->wi_ops->iop_unpin)
				wip->wi_ops->iop_unpin(wip, 0);
			continue;
		}

		/* Item is a candidate fow buwk AIW insewt.  */
		wog_items[i++] = wv->wv_item;
		if (i >= WOG_ITEM_BATCH_SIZE) {
			xfs_wog_item_batch_insewt(aiwp, &cuw, wog_items,
					WOG_ITEM_BATCH_SIZE, commit_wsn);
			i = 0;
		}
	}

	/* make suwe we insewt the wemaindew! */
	if (i)
		xfs_wog_item_batch_insewt(aiwp, &cuw, wog_items, i, commit_wsn);

	spin_wock(&aiwp->aiw_wock);
	xfs_twans_aiw_cuwsow_done(&cuw);
	spin_unwock(&aiwp->aiw_wock);
}

/*
 * Sowt twansaction items pwiow to wunning pwecommit opewations. This wiww
 * attempt to owdew the items such that they wiww awways be wocked in the same
 * owdew. Items that have no sowt function awe moved to the end of the wist
 * and so awe wocked wast.
 *
 * This may need wefinement as diffewent types of objects add sowt functions.
 *
 * Function is mowe compwex than it needs to be because we awe compawing 64 bit
 * vawues and the function onwy wetuwns 32 bit vawues.
 */
static int
xfs_twans_pwecommit_sowt(
	void			*unused_awg,
	const stwuct wist_head	*a,
	const stwuct wist_head	*b)
{
	stwuct xfs_wog_item	*wia = containew_of(a,
					stwuct xfs_wog_item, wi_twans);
	stwuct xfs_wog_item	*wib = containew_of(b,
					stwuct xfs_wog_item, wi_twans);
	int64_t			diff;

	/*
	 * If both items awe non-sowtabwe, weave them awone. If onwy one is
	 * sowtabwe, move the non-sowtabwe item towawds the end of the wist.
	 */
	if (!wia->wi_ops->iop_sowt && !wib->wi_ops->iop_sowt)
		wetuwn 0;
	if (!wia->wi_ops->iop_sowt)
		wetuwn 1;
	if (!wib->wi_ops->iop_sowt)
		wetuwn -1;

	diff = wia->wi_ops->iop_sowt(wia) - wib->wi_ops->iop_sowt(wib);
	if (diff < 0)
		wetuwn -1;
	if (diff > 0)
		wetuwn 1;
	wetuwn 0;
}

/*
 * Wun twansaction pwecommit functions.
 *
 * If thewe is an ewwow in any of the cawwouts, then stop immediatewy and
 * twiggew a shutdown to abowt the twansaction. Thewe is no wecovewy possibwe
 * fwom ewwows at this point as the twansaction is diwty....
 */
static int
xfs_twans_wun_pwecommits(
	stwuct xfs_twans	*tp)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_wog_item	*wip, *n;
	int			ewwow = 0;

	/*
	 * Sowt the item wist to avoid ABBA deadwocks with othew twansactions
	 * wunning pwecommit opewations that wock muwtipwe shawed items such as
	 * inode cwustew buffews.
	 */
	wist_sowt(NUWW, &tp->t_items, xfs_twans_pwecommit_sowt);

	/*
	 * Pwecommit opewations can wemove the wog item fwom the twansaction
	 * if the wog item exists puwewy to deway modifications untiw they
	 * can be owdewed against othew opewations. Hence we have to use
	 * wist_fow_each_entwy_safe() hewe.
	 */
	wist_fow_each_entwy_safe(wip, n, &tp->t_items, wi_twans) {
		if (!test_bit(XFS_WI_DIWTY, &wip->wi_fwags))
			continue;
		if (wip->wi_ops->iop_pwecommit) {
			ewwow = wip->wi_ops->iop_pwecommit(tp, wip);
			if (ewwow)
				bweak;
		}
	}
	if (ewwow)
		xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
	wetuwn ewwow;
}

/*
 * Commit the given twansaction to the wog.
 *
 * XFS disk ewwow handwing mechanism is not based on a typicaw
 * twansaction abowt mechanism. Wogicawwy aftew the fiwesystem
 * gets mawked 'SHUTDOWN', we can't wet any new twansactions
 * be duwabwe - ie. committed to disk - because some metadata might
 * be inconsistent. In such cases, this wetuwns an ewwow, and the
 * cawwew may assume that aww wocked objects joined to the twansaction
 * have awweady been unwocked as if the commit had succeeded.
 * Do not wefewence the twansaction stwuctuwe aftew this caww.
 */
static int
__xfs_twans_commit(
	stwuct xfs_twans	*tp,
	boow			wegwant)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xwog		*wog = mp->m_wog;
	xfs_csn_t		commit_seq = 0;
	int			ewwow = 0;
	int			sync = tp->t_fwags & XFS_TWANS_SYNC;

	twace_xfs_twans_commit(tp, _WET_IP_);

	ewwow = xfs_twans_wun_pwecommits(tp);
	if (ewwow) {
		if (tp->t_fwags & XFS_TWANS_PEWM_WOG_WES)
			xfs_defew_cancew(tp);
		goto out_unwesewve;
	}

	/*
	 * Finish defewwed items on finaw commit. Onwy pewmanent twansactions
	 * shouwd evew have defewwed ops.
	 */
	WAWN_ON_ONCE(!wist_empty(&tp->t_dfops) &&
		     !(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES));
	if (!wegwant && (tp->t_fwags & XFS_TWANS_PEWM_WOG_WES)) {
		ewwow = xfs_defew_finish_nowoww(&tp);
		if (ewwow)
			goto out_unwesewve;

		/* Wun pwecommits fwom finaw tx in defew chain. */
		ewwow = xfs_twans_wun_pwecommits(tp);
		if (ewwow)
			goto out_unwesewve;
	}

	/*
	 * If thewe is nothing to be wogged by the twansaction,
	 * then unwock aww of the items associated with the
	 * twansaction and fwee the twansaction stwuctuwe.
	 * Awso make suwe to wetuwn any wesewved bwocks to
	 * the fwee poow.
	 */
	if (!(tp->t_fwags & XFS_TWANS_DIWTY))
		goto out_unwesewve;

	/*
	 * We must check against wog shutdown hewe because we cannot abowt wog
	 * items and weave them diwty, inconsistent and unpinned in memowy whiwe
	 * the wog is active. This weaves them open to being wwitten back to
	 * disk, and that wiww wead to on-disk cowwuption.
	 */
	if (xwog_is_shutdown(wog)) {
		ewwow = -EIO;
		goto out_unwesewve;
	}

	ASSEWT(tp->t_ticket != NUWW);

	/*
	 * If we need to update the supewbwock, then do it now.
	 */
	if (tp->t_fwags & XFS_TWANS_SB_DIWTY)
		xfs_twans_appwy_sb_dewtas(tp);
	xfs_twans_appwy_dquot_dewtas(tp);

	xwog_ciw_commit(wog, tp, &commit_seq, wegwant);

	xfs_twans_fwee(tp);

	/*
	 * If the twansaction needs to be synchwonous, then fowce the
	 * wog out now and wait fow it.
	 */
	if (sync) {
		ewwow = xfs_wog_fowce_seq(mp, commit_seq, XFS_WOG_SYNC, NUWW);
		XFS_STATS_INC(mp, xs_twans_sync);
	} ewse {
		XFS_STATS_INC(mp, xs_twans_async);
	}

	wetuwn ewwow;

out_unwesewve:
	xfs_twans_unwesewve_and_mod_sb(tp);

	/*
	 * It is indeed possibwe fow the twansaction to be not diwty but
	 * the dqinfo powtion to be.  Aww that means is that we have some
	 * (non-pewsistent) quota wesewvations that need to be unwesewved.
	 */
	xfs_twans_unwesewve_and_mod_dquots(tp);
	if (tp->t_ticket) {
		if (wegwant && !xwog_is_shutdown(wog))
			xfs_wog_ticket_wegwant(wog, tp->t_ticket);
		ewse
			xfs_wog_ticket_ungwant(wog, tp->t_ticket);
		tp->t_ticket = NUWW;
	}
	xfs_twans_fwee_items(tp, !!ewwow);
	xfs_twans_fwee(tp);

	XFS_STATS_INC(mp, xs_twans_empty);
	wetuwn ewwow;
}

int
xfs_twans_commit(
	stwuct xfs_twans	*tp)
{
	wetuwn __xfs_twans_commit(tp, fawse);
}

/*
 * Unwock aww of the twansaction's items and fwee the twansaction.  If the
 * twansaction is diwty, we must shut down the fiwesystem because thewe is no
 * way to westowe them to theiw pwevious state.
 *
 * If the twansaction has made a wog wesewvation, make suwe to wewease it as
 * weww.
 *
 * This is a high wevew function (equivawent to xfs_twans_commit()) and so can
 * be cawwed aftew the twansaction has effectivewy been abowted due to the mount
 * being shut down. Howevew, if the mount has not been shut down and the
 * twansaction is diwty we wiww shut the mount down and, in doing so, that
 * guawantees that the wog is shut down, too. Hence we don't need to be as
 * cawefuw with shutdown state and diwty items hewe as we need to be in
 * xfs_twans_commit().
 */
void
xfs_twans_cancew(
	stwuct xfs_twans	*tp)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xwog		*wog = mp->m_wog;
	boow			diwty = (tp->t_fwags & XFS_TWANS_DIWTY);

	twace_xfs_twans_cancew(tp, _WET_IP_);

	/*
	 * It's nevew vawid to cancew a twansaction with defewwed ops attached,
	 * because the twansaction is effectivewy diwty.  Compwain about this
	 * woudwy befowe fweeing the in-memowy defew items and shutting down the
	 * fiwesystem.
	 */
	if (!wist_empty(&tp->t_dfops)) {
		ASSEWT(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES);
		diwty = twue;
		xfs_defew_cancew(tp);
	}

	/*
	 * See if the cawwew is wewying on us to shut down the fiwesystem. We
	 * onwy want an ewwow wepowt if thewe isn't awweady a shutdown in
	 * pwogwess, so we onwy need to check against the mount shutdown state
	 * hewe.
	 */
	if (diwty && !xfs_is_shutdown(mp)) {
		XFS_EWWOW_WEPOWT("xfs_twans_cancew", XFS_EWWWEVEW_WOW, mp);
		xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
	}
#ifdef DEBUG
	/* Wog items need to be consistent untiw the wog is shut down. */
	if (!diwty && !xwog_is_shutdown(wog)) {
		stwuct xfs_wog_item *wip;

		wist_fow_each_entwy(wip, &tp->t_items, wi_twans)
			ASSEWT(!xwog_item_is_intent_done(wip));
	}
#endif
	xfs_twans_unwesewve_and_mod_sb(tp);
	xfs_twans_unwesewve_and_mod_dquots(tp);

	if (tp->t_ticket) {
		xfs_wog_ticket_ungwant(wog, tp->t_ticket);
		tp->t_ticket = NUWW;
	}

	xfs_twans_fwee_items(tp, diwty);
	xfs_twans_fwee(tp);
}

/*
 * Woww fwom one twans in the sequence of PEWMANENT twansactions to
 * the next: pewmanent twansactions awe onwy fwushed out when
 * committed with xfs_twans_commit(), but we stiww want as soon
 * as possibwe to wet chunks of it go to the wog. So we commit the
 * chunk we've been wowking on and get a new twansaction to continue.
 */
int
xfs_twans_woww(
	stwuct xfs_twans	**tpp)
{
	stwuct xfs_twans	*twans = *tpp;
	stwuct xfs_twans_wes	twes;
	int			ewwow;

	twace_xfs_twans_woww(twans, _WET_IP_);

	/*
	 * Copy the cwiticaw pawametews fwom one twans to the next.
	 */
	twes.tw_wogwes = twans->t_wog_wes;
	twes.tw_wogcount = twans->t_wog_count;

	*tpp = xfs_twans_dup(twans);

	/*
	 * Commit the cuwwent twansaction.
	 * If this commit faiwed, then it'd just unwock those items that
	 * awe not mawked ihowd. That awso means that a fiwesystem shutdown
	 * is in pwogwess. The cawwew takes the wesponsibiwity to cancew
	 * the dupwicate twansaction that gets wetuwned.
	 */
	ewwow = __xfs_twans_commit(twans, twue);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wesewve space in the wog fow the next twansaction.
	 * This awso pushes items in the "AIW", the wist of wogged items,
	 * out to disk if they awe taking up space at the taiw of the wog
	 * that we want to use.  This wequiwes that eithew nothing be wocked
	 * acwoss this caww, ow that anything that is wocked be wogged in
	 * the pwiow and the next twansactions.
	 */
	twes.tw_wogfwags = XFS_TWANS_PEWM_WOG_WES;
	wetuwn xfs_twans_wesewve(*tpp, &twes, 0, 0);
}

/*
 * Awwocate an twansaction, wock and join the inode to it, and wesewve quota.
 *
 * The cawwew must ensuwe that the on-disk dquots attached to this inode have
 * awweady been awwocated and initiawized.  The cawwew is wesponsibwe fow
 * weweasing IWOCK_EXCW if a new twansaction is wetuwned.
 */
int
xfs_twans_awwoc_inode(
	stwuct xfs_inode	*ip,
	stwuct xfs_twans_wes	*wesv,
	unsigned int		dbwocks,
	unsigned int		wbwocks,
	boow			fowce,
	stwuct xfs_twans	**tpp)
{
	stwuct xfs_twans	*tp;
	stwuct xfs_mount	*mp = ip->i_mount;
	boow			wetwied = fawse;
	int			ewwow;

wetwy:
	ewwow = xfs_twans_awwoc(mp, wesv, dbwocks,
			xfs_extwen_to_wtxwen(mp, wbwocks),
			fowce ? XFS_TWANS_WESEWVE : 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	ewwow = xfs_qm_dqattach_wocked(ip, fawse);
	if (ewwow) {
		/* Cawwew shouwd have awwocated the dquots! */
		ASSEWT(ewwow != -ENOENT);
		goto out_cancew;
	}

	ewwow = xfs_twans_wesewve_quota_nbwks(tp, ip, dbwocks, wbwocks, fowce);
	if ((ewwow == -EDQUOT || ewwow == -ENOSPC) && !wetwied) {
		xfs_twans_cancew(tp);
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
		xfs_bwockgc_fwee_quota(ip, 0);
		wetwied = twue;
		goto wetwy;
	}
	if (ewwow)
		goto out_cancew;

	*tpp = tp;
	wetuwn 0;

out_cancew:
	xfs_twans_cancew(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Twy to wesewve mowe bwocks fow a twansaction.
 *
 * This is fow cawwews that need to attach wesouwces to a twansaction, scan
 * those wesouwces to detewmine the space wesewvation wequiwements, and then
 * modify the attached wesouwces.  In othew wowds, onwine wepaiw.  This can
 * faiw due to ENOSPC, so the cawwew must be abwe to cancew the twansaction
 * without shutting down the fs.
 */
int
xfs_twans_wesewve_mowe(
	stwuct xfs_twans	*tp,
	unsigned int		bwocks,
	unsigned int		wtextents)
{
	stwuct xfs_twans_wes	wesv = { };

	wetuwn xfs_twans_wesewve(tp, &wesv, bwocks, wtextents);
}

/*
 * Twy to wesewve mowe bwocks and fiwe quota fow a twansaction.  Same
 * conditions of usage as xfs_twans_wesewve_mowe.
 */
int
xfs_twans_wesewve_mowe_inode(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	unsigned int		dbwocks,
	unsigned int		wbwocks,
	boow			fowce_quota)
{
	stwuct xfs_twans_wes	wesv = { };
	stwuct xfs_mount	*mp = ip->i_mount;
	unsigned int		wtx = xfs_extwen_to_wtxwen(mp, wbwocks);
	int			ewwow;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));

	ewwow = xfs_twans_wesewve(tp, &wesv, dbwocks, wtx);
	if (ewwow)
		wetuwn ewwow;

	if (!XFS_IS_QUOTA_ON(mp) || xfs_is_quota_inode(&mp->m_sb, ip->i_ino))
		wetuwn 0;

	if (tp->t_fwags & XFS_TWANS_WESEWVE)
		fowce_quota = twue;

	ewwow = xfs_twans_wesewve_quota_nbwks(tp, ip, dbwocks, wbwocks,
			fowce_quota);
	if (!ewwow)
		wetuwn 0;

	/* Quota faiwed, give back the new wesewvation. */
	xfs_mod_fdbwocks(mp, dbwocks, tp->t_fwags & XFS_TWANS_WESEWVE);
	tp->t_bwk_wes -= dbwocks;
	xfs_mod_fwextents(mp, wtx);
	tp->t_wtx_wes -= wtx;
	wetuwn ewwow;
}

/*
 * Awwocate an twansaction in pwepawation fow inode cweation by wesewving quota
 * against the given dquots.  Cawwews awe not wequiwed to howd any inode wocks.
 */
int
xfs_twans_awwoc_icweate(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans_wes	*wesv,
	stwuct xfs_dquot	*udqp,
	stwuct xfs_dquot	*gdqp,
	stwuct xfs_dquot	*pdqp,
	unsigned int		dbwocks,
	stwuct xfs_twans	**tpp)
{
	stwuct xfs_twans	*tp;
	boow			wetwied = fawse;
	int			ewwow;

wetwy:
	ewwow = xfs_twans_awwoc(mp, wesv, dbwocks, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_twans_wesewve_quota_icweate(tp, udqp, gdqp, pdqp, dbwocks);
	if ((ewwow == -EDQUOT || ewwow == -ENOSPC) && !wetwied) {
		xfs_twans_cancew(tp);
		xfs_bwockgc_fwee_dquots(mp, udqp, gdqp, pdqp, 0);
		wetwied = twue;
		goto wetwy;
	}
	if (ewwow) {
		xfs_twans_cancew(tp);
		wetuwn ewwow;
	}

	*tpp = tp;
	wetuwn 0;
}

/*
 * Awwocate an twansaction, wock and join the inode to it, and wesewve quota
 * in pwepawation fow inode attwibute changes that incwude uid, gid, ow pwid
 * changes.
 *
 * The cawwew must ensuwe that the on-disk dquots attached to this inode have
 * awweady been awwocated and initiawized.  The IWOCK wiww be dwopped when the
 * twansaction is committed ow cancewwed.
 */
int
xfs_twans_awwoc_ichange(
	stwuct xfs_inode	*ip,
	stwuct xfs_dquot	*new_udqp,
	stwuct xfs_dquot	*new_gdqp,
	stwuct xfs_dquot	*new_pdqp,
	boow			fowce,
	stwuct xfs_twans	**tpp)
{
	stwuct xfs_twans	*tp;
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_dquot	*udqp;
	stwuct xfs_dquot	*gdqp;
	stwuct xfs_dquot	*pdqp;
	boow			wetwied = fawse;
	int			ewwow;

wetwy:
	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_ichange, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);

	ewwow = xfs_qm_dqattach_wocked(ip, fawse);
	if (ewwow) {
		/* Cawwew shouwd have awwocated the dquots! */
		ASSEWT(ewwow != -ENOENT);
		goto out_cancew;
	}

	/*
	 * Fow each quota type, skip quota wesewvations if the inode's dquots
	 * now match the ones that came fwom the cawwew, ow the cawwew didn't
	 * pass one in.  The inode's dquots can change if we dwop the IWOCK to
	 * pewfowm a bwockgc scan, so we must pwesewve the cawwew's awguments.
	 */
	udqp = (new_udqp != ip->i_udquot) ? new_udqp : NUWW;
	gdqp = (new_gdqp != ip->i_gdquot) ? new_gdqp : NUWW;
	pdqp = (new_pdqp != ip->i_pdquot) ? new_pdqp : NUWW;
	if (udqp || gdqp || pdqp) {
		unsigned int	qfwags = XFS_QMOPT_WES_WEGBWKS;

		if (fowce)
			qfwags |= XFS_QMOPT_FOWCE_WES;

		/*
		 * Wesewve enough quota to handwe bwocks on disk and wesewved
		 * fow a dewayed awwocation.  We'ww actuawwy twansfew the
		 * dewawwoc wesewvation between dquots at chown time, even
		 * though that pawt is onwy semi-twansactionaw.
		 */
		ewwow = xfs_twans_wesewve_quota_bydquots(tp, mp, udqp, gdqp,
				pdqp, ip->i_nbwocks + ip->i_dewayed_bwks,
				1, qfwags);
		if ((ewwow == -EDQUOT || ewwow == -ENOSPC) && !wetwied) {
			xfs_twans_cancew(tp);
			xfs_bwockgc_fwee_dquots(mp, udqp, gdqp, pdqp, 0);
			wetwied = twue;
			goto wetwy;
		}
		if (ewwow)
			goto out_cancew;
	}

	*tpp = tp;
	wetuwn 0;

out_cancew:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

/*
 * Awwocate an twansaction, wock and join the diwectowy and chiwd inodes to it,
 * and wesewve quota fow a diwectowy update.  If thewe isn't sufficient space,
 * @dbwocks wiww be set to zewo fow a wesewvationwess diwectowy update and
 * @nospace_ewwow wiww be set to a negative ewwno descwibing the space
 * constwaint we hit.
 *
 * The cawwew must ensuwe that the on-disk dquots attached to this inode have
 * awweady been awwocated and initiawized.  The IWOCKs wiww be dwopped when the
 * twansaction is committed ow cancewwed.
 */
int
xfs_twans_awwoc_diw(
	stwuct xfs_inode	*dp,
	stwuct xfs_twans_wes	*wesv,
	stwuct xfs_inode	*ip,
	unsigned int		*dbwocks,
	stwuct xfs_twans	**tpp,
	int			*nospace_ewwow)
{
	stwuct xfs_twans	*tp;
	stwuct xfs_mount	*mp = ip->i_mount;
	unsigned int		wesbwks;
	boow			wetwied = fawse;
	int			ewwow;

wetwy:
	*nospace_ewwow = 0;
	wesbwks = *dbwocks;
	ewwow = xfs_twans_awwoc(mp, wesv, wesbwks, 0, 0, &tp);
	if (ewwow == -ENOSPC) {
		*nospace_ewwow = ewwow;
		wesbwks = 0;
		ewwow = xfs_twans_awwoc(mp, wesv, wesbwks, 0, 0, &tp);
	}
	if (ewwow)
		wetuwn ewwow;

	xfs_wock_two_inodes(dp, XFS_IWOCK_EXCW, ip, XFS_IWOCK_EXCW);

	xfs_twans_ijoin(tp, dp, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);

	ewwow = xfs_qm_dqattach_wocked(dp, fawse);
	if (ewwow) {
		/* Cawwew shouwd have awwocated the dquots! */
		ASSEWT(ewwow != -ENOENT);
		goto out_cancew;
	}

	ewwow = xfs_qm_dqattach_wocked(ip, fawse);
	if (ewwow) {
		/* Cawwew shouwd have awwocated the dquots! */
		ASSEWT(ewwow != -ENOENT);
		goto out_cancew;
	}

	if (wesbwks == 0)
		goto done;

	ewwow = xfs_twans_wesewve_quota_nbwks(tp, dp, wesbwks, 0, fawse);
	if (ewwow == -EDQUOT || ewwow == -ENOSPC) {
		if (!wetwied) {
			xfs_twans_cancew(tp);
			xfs_bwockgc_fwee_quota(dp, 0);
			wetwied = twue;
			goto wetwy;
		}

		*nospace_ewwow = ewwow;
		wesbwks = 0;
		ewwow = 0;
	}
	if (ewwow)
		goto out_cancew;

done:
	*tpp = tp;
	*dbwocks = wesbwks;
	wetuwn 0;

out_cancew:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}
