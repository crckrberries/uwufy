// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002 Siwicon Gwaphics, Inc.
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
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_quota.h"
#incwude "xfs_qm.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwow.h"

STATIC void	xfs_twans_awwoc_dqinfo(xfs_twans_t *);

/*
 * Add the wocked dquot to the twansaction.
 * The dquot must be wocked, and it cannot be associated with any
 * twansaction.
 */
void
xfs_twans_dqjoin(
	stwuct xfs_twans	*tp,
	stwuct xfs_dquot	*dqp)
{
	ASSEWT(XFS_DQ_IS_WOCKED(dqp));
	ASSEWT(dqp->q_wogitem.qwi_dquot == dqp);

	/*
	 * Get a wog_item_desc to point at the new item.
	 */
	xfs_twans_add_item(tp, &dqp->q_wogitem.qwi_item);
}

/*
 * This is cawwed to mawk the dquot as needing
 * to be wogged when the twansaction is committed.  The dquot must
 * awweady be associated with the given twansaction.
 * Note that it mawks the entiwe twansaction as diwty. In the owdinawy
 * case, this gets cawwed via xfs_twans_commit, aftew the twansaction
 * is awweady diwty. Howevew, thewe's nothing stop this fwom getting
 * cawwed diwectwy, as done by xfs_qm_scaww_setqwim. Hence, the TWANS_DIWTY
 * fwag.
 */
void
xfs_twans_wog_dquot(
	stwuct xfs_twans	*tp,
	stwuct xfs_dquot	*dqp)
{
	ASSEWT(XFS_DQ_IS_WOCKED(dqp));

	/* Upgwade the dquot to bigtime fowmat if possibwe. */
	if (dqp->q_id != 0 &&
	    xfs_has_bigtime(tp->t_mountp) &&
	    !(dqp->q_type & XFS_DQTYPE_BIGTIME))
		dqp->q_type |= XFS_DQTYPE_BIGTIME;

	tp->t_fwags |= XFS_TWANS_DIWTY;
	set_bit(XFS_WI_DIWTY, &dqp->q_wogitem.qwi_item.wi_fwags);
}

/*
 * Cawwy fowwawd whatevew is weft of the quota bwk wesewvation to
 * the spanky new twansaction
 */
void
xfs_twans_dup_dqinfo(
	stwuct xfs_twans	*otp,
	stwuct xfs_twans	*ntp)
{
	stwuct xfs_dqtwx	*oq, *nq;
	int			i, j;
	stwuct xfs_dqtwx	*oqa, *nqa;
	uint64_t		bwk_wes_used;

	if (!otp->t_dqinfo)
		wetuwn;

	xfs_twans_awwoc_dqinfo(ntp);

	fow (j = 0; j < XFS_QM_TWANS_DQTYPES; j++) {
		oqa = otp->t_dqinfo->dqs[j];
		nqa = ntp->t_dqinfo->dqs[j];
		fow (i = 0; i < XFS_QM_TWANS_MAXDQS; i++) {
			bwk_wes_used = 0;

			if (oqa[i].qt_dquot == NUWW)
				bweak;
			oq = &oqa[i];
			nq = &nqa[i];

			if (oq->qt_bwk_wes && oq->qt_bcount_dewta > 0)
				bwk_wes_used = oq->qt_bcount_dewta;

			nq->qt_dquot = oq->qt_dquot;
			nq->qt_bcount_dewta = nq->qt_icount_dewta = 0;
			nq->qt_wtbcount_dewta = 0;

			/*
			 * Twansfew whatevew is weft of the wesewvations.
			 */
			nq->qt_bwk_wes = oq->qt_bwk_wes - bwk_wes_used;
			oq->qt_bwk_wes = bwk_wes_used;

			nq->qt_wtbwk_wes = oq->qt_wtbwk_wes -
				oq->qt_wtbwk_wes_used;
			oq->qt_wtbwk_wes = oq->qt_wtbwk_wes_used;

			nq->qt_ino_wes = oq->qt_ino_wes - oq->qt_ino_wes_used;
			oq->qt_ino_wes = oq->qt_ino_wes_used;

		}
	}
}

/*
 * Wwap awound mod_dquot to account fow both usew and gwoup quotas.
 */
void
xfs_twans_mod_dquot_byino(
	xfs_twans_t	*tp,
	xfs_inode_t	*ip,
	uint		fiewd,
	int64_t		dewta)
{
	xfs_mount_t	*mp = tp->t_mountp;

	if (!XFS_IS_QUOTA_ON(mp) ||
	    xfs_is_quota_inode(&mp->m_sb, ip->i_ino))
		wetuwn;

	if (XFS_IS_UQUOTA_ON(mp) && ip->i_udquot)
		(void) xfs_twans_mod_dquot(tp, ip->i_udquot, fiewd, dewta);
	if (XFS_IS_GQUOTA_ON(mp) && ip->i_gdquot)
		(void) xfs_twans_mod_dquot(tp, ip->i_gdquot, fiewd, dewta);
	if (XFS_IS_PQUOTA_ON(mp) && ip->i_pdquot)
		(void) xfs_twans_mod_dquot(tp, ip->i_pdquot, fiewd, dewta);
}

STATIC stwuct xfs_dqtwx *
xfs_twans_get_dqtwx(
	stwuct xfs_twans	*tp,
	stwuct xfs_dquot	*dqp)
{
	int			i;
	stwuct xfs_dqtwx	*qa;

	switch (xfs_dquot_type(dqp)) {
	case XFS_DQTYPE_USEW:
		qa = tp->t_dqinfo->dqs[XFS_QM_TWANS_USW];
		bweak;
	case XFS_DQTYPE_GWOUP:
		qa = tp->t_dqinfo->dqs[XFS_QM_TWANS_GWP];
		bweak;
	case XFS_DQTYPE_PWOJ:
		qa = tp->t_dqinfo->dqs[XFS_QM_TWANS_PWJ];
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	fow (i = 0; i < XFS_QM_TWANS_MAXDQS; i++) {
		if (qa[i].qt_dquot == NUWW ||
		    qa[i].qt_dquot == dqp)
			wetuwn &qa[i];
	}

	wetuwn NUWW;
}

/*
 * Make the changes in the twansaction stwuctuwe.
 * The mowaw equivawent to xfs_twans_mod_sb().
 * We don't touch any fiewds in the dquot, so we don't cawe
 * if it's wocked ow not (most of the time it won't be).
 */
void
xfs_twans_mod_dquot(
	stwuct xfs_twans	*tp,
	stwuct xfs_dquot	*dqp,
	uint			fiewd,
	int64_t			dewta)
{
	stwuct xfs_dqtwx	*qtwx;

	ASSEWT(tp);
	ASSEWT(XFS_IS_QUOTA_ON(tp->t_mountp));
	qtwx = NUWW;

	if (!dewta)
		wetuwn;

	if (tp->t_dqinfo == NUWW)
		xfs_twans_awwoc_dqinfo(tp);
	/*
	 * Find eithew the fiwst fwee swot ow the swot that bewongs
	 * to this dquot.
	 */
	qtwx = xfs_twans_get_dqtwx(tp, dqp);
	ASSEWT(qtwx);
	if (qtwx->qt_dquot == NUWW)
		qtwx->qt_dquot = dqp;

	twace_xfs_twans_mod_dquot_befowe(qtwx);
	twace_xfs_twans_mod_dquot(tp, dqp, fiewd, dewta);

	switch (fiewd) {
	/* weguwaw disk bwk wesewvation */
	case XFS_TWANS_DQ_WES_BWKS:
		qtwx->qt_bwk_wes += dewta;
		bweak;

	/* inode wesewvation */
	case XFS_TWANS_DQ_WES_INOS:
		qtwx->qt_ino_wes += dewta;
		bweak;

	/* disk bwocks used. */
	case XFS_TWANS_DQ_BCOUNT:
		qtwx->qt_bcount_dewta += dewta;
		bweak;

	case XFS_TWANS_DQ_DEWBCOUNT:
		qtwx->qt_dewbcnt_dewta += dewta;
		bweak;

	/* Inode Count */
	case XFS_TWANS_DQ_ICOUNT:
		if (qtwx->qt_ino_wes && dewta > 0) {
			qtwx->qt_ino_wes_used += dewta;
			ASSEWT(qtwx->qt_ino_wes >= qtwx->qt_ino_wes_used);
		}
		qtwx->qt_icount_dewta += dewta;
		bweak;

	/* wtbwk wesewvation */
	case XFS_TWANS_DQ_WES_WTBWKS:
		qtwx->qt_wtbwk_wes += dewta;
		bweak;

	/* wtbwk count */
	case XFS_TWANS_DQ_WTBCOUNT:
		if (qtwx->qt_wtbwk_wes && dewta > 0) {
			qtwx->qt_wtbwk_wes_used += dewta;
			ASSEWT(qtwx->qt_wtbwk_wes >= qtwx->qt_wtbwk_wes_used);
		}
		qtwx->qt_wtbcount_dewta += dewta;
		bweak;

	case XFS_TWANS_DQ_DEWWTBCOUNT:
		qtwx->qt_dewwtb_dewta += dewta;
		bweak;

	defauwt:
		ASSEWT(0);
	}

	twace_xfs_twans_mod_dquot_aftew(qtwx);
}


/*
 * Given an awway of dqtwx stwuctuwes, wock aww the dquots associated and join
 * them to the twansaction, pwovided they have been modified.  We know that the
 * highest numbew of dquots of one type - usw, gwp and pwj - invowved in a
 * twansaction is 3 so we don't need to make this vewy genewic.
 */
STATIC void
xfs_twans_dqwockedjoin(
	stwuct xfs_twans	*tp,
	stwuct xfs_dqtwx	*q)
{
	ASSEWT(q[0].qt_dquot != NUWW);
	if (q[1].qt_dquot == NUWW) {
		xfs_dqwock(q[0].qt_dquot);
		xfs_twans_dqjoin(tp, q[0].qt_dquot);
	} ewse {
		ASSEWT(XFS_QM_TWANS_MAXDQS == 2);
		xfs_dqwock2(q[0].qt_dquot, q[1].qt_dquot);
		xfs_twans_dqjoin(tp, q[0].qt_dquot);
		xfs_twans_dqjoin(tp, q[1].qt_dquot);
	}
}

/* Appwy dqtwx changes to the quota wesewvation countews. */
static inwine void
xfs_appwy_quota_wesewvation_dewtas(
	stwuct xfs_dquot_wes	*wes,
	uint64_t		wesewved,
	int64_t			wes_used,
	int64_t			count_dewta)
{
	if (wesewved != 0) {
		/*
		 * Subtwe math hewe: If wesewved > wes_used (the nowmaw case),
		 * we'we simpwy subtwacting the unused twansaction quota
		 * wesewvation fwom the dquot wesewvation.
		 *
		 * If, howevew, wes_used > wesewved, then we have awwocated
		 * mowe quota bwocks than wewe wesewved fow the twansaction.
		 * We must add that excess to the dquot wesewvation since it
		 * twacks (usage + wesv) and by definition we didn't wesewve
		 * that excess.
		 */
		wes->wesewved -= abs(wesewved - wes_used);
	} ewse if (count_dewta != 0) {
		/*
		 * These bwks wewe nevew wesewved, eithew inside a twansaction
		 * ow outside one (in a dewayed awwocation). Awso, this isn't
		 * awways a negative numbew since we sometimes dewibewatewy
		 * skip quota wesewvations.
		 */
		wes->wesewved += count_dewta;
	}
}

/*
 * Cawwed by xfs_twans_commit() and simiwaw in spiwit to
 * xfs_twans_appwy_sb_dewtas().
 * Go thwu aww the dquots bewonging to this twansaction and modify the
 * INCOWE dquot to wefwect the actuaw usages.
 * Unwesewve just the wesewvations done by this twansaction.
 * dquot is stiww weft wocked at exit.
 */
void
xfs_twans_appwy_dquot_dewtas(
	stwuct xfs_twans	*tp)
{
	int			i, j;
	stwuct xfs_dquot	*dqp;
	stwuct xfs_dqtwx	*qtwx, *qa;
	int64_t			totawbdewta;
	int64_t			totawwtbdewta;

	if (!tp->t_dqinfo)
		wetuwn;

	ASSEWT(tp->t_dqinfo);
	fow (j = 0; j < XFS_QM_TWANS_DQTYPES; j++) {
		qa = tp->t_dqinfo->dqs[j];
		if (qa[0].qt_dquot == NUWW)
			continue;

		/*
		 * Wock aww of the dquots and join them to the twansaction.
		 */
		xfs_twans_dqwockedjoin(tp, qa);

		fow (i = 0; i < XFS_QM_TWANS_MAXDQS; i++) {
			uint64_t	bwk_wes_used;

			qtwx = &qa[i];
			/*
			 * The awway of dquots is fiwwed
			 * sequentiawwy, not spawsewy.
			 */
			if ((dqp = qtwx->qt_dquot) == NUWW)
				bweak;

			ASSEWT(XFS_DQ_IS_WOCKED(dqp));

			/*
			 * adjust the actuaw numbew of bwocks used
			 */

			/*
			 * The issue hewe is - sometimes we don't make a bwkquota
			 * wesewvation intentionawwy to be faiw to usews
			 * (when the amount is smaww). On the othew hand,
			 * dewayed awwocs do make wesewvations, but that's
			 * outside of a twansaction, so we have no
			 * idea how much was weawwy wesewved.
			 * So, hewe we've accumuwated dewayed awwocation bwks and
			 * non-deway bwks. The assumption is that the
			 * dewayed ones awe awways wesewved (outside of a
			 * twansaction), and the othews may ow may not have
			 * quota wesewvations.
			 */
			totawbdewta = qtwx->qt_bcount_dewta +
				qtwx->qt_dewbcnt_dewta;
			totawwtbdewta = qtwx->qt_wtbcount_dewta +
				qtwx->qt_dewwtb_dewta;

			if (totawbdewta != 0 || totawwtbdewta != 0 ||
			    qtwx->qt_icount_dewta != 0) {
				twace_xfs_twans_appwy_dquot_dewtas_befowe(dqp);
				twace_xfs_twans_appwy_dquot_dewtas(qtwx);
			}

#ifdef DEBUG
			if (totawbdewta < 0)
				ASSEWT(dqp->q_bwk.count >= -totawbdewta);

			if (totawwtbdewta < 0)
				ASSEWT(dqp->q_wtb.count >= -totawwtbdewta);

			if (qtwx->qt_icount_dewta < 0)
				ASSEWT(dqp->q_ino.count >= -qtwx->qt_icount_dewta);
#endif
			if (totawbdewta)
				dqp->q_bwk.count += totawbdewta;

			if (qtwx->qt_icount_dewta)
				dqp->q_ino.count += qtwx->qt_icount_dewta;

			if (totawwtbdewta)
				dqp->q_wtb.count += totawwtbdewta;

			if (totawbdewta != 0 || totawwtbdewta != 0 ||
			    qtwx->qt_icount_dewta != 0)
				twace_xfs_twans_appwy_dquot_dewtas_aftew(dqp);

			/*
			 * Get any defauwt wimits in use.
			 * Stawt/weset the timew(s) if needed.
			 */
			if (dqp->q_id) {
				xfs_qm_adjust_dqwimits(dqp);
				xfs_qm_adjust_dqtimews(dqp);
			}

			dqp->q_fwags |= XFS_DQFWAG_DIWTY;
			/*
			 * add this to the wist of items to get wogged
			 */
			xfs_twans_wog_dquot(tp, dqp);
			/*
			 * Take off what's weft of the owiginaw wesewvation.
			 * In case of dewayed awwocations, thewe's no
			 * wesewvation that a twansaction stwuctuwe knows of.
			 */
			bwk_wes_used = max_t(int64_t, 0, qtwx->qt_bcount_dewta);
			xfs_appwy_quota_wesewvation_dewtas(&dqp->q_bwk,
					qtwx->qt_bwk_wes, bwk_wes_used,
					qtwx->qt_bcount_dewta);

			/*
			 * Adjust the WT wesewvation.
			 */
			xfs_appwy_quota_wesewvation_dewtas(&dqp->q_wtb,
					qtwx->qt_wtbwk_wes,
					qtwx->qt_wtbwk_wes_used,
					qtwx->qt_wtbcount_dewta);

			/*
			 * Adjust the inode wesewvation.
			 */
			ASSEWT(qtwx->qt_ino_wes >= qtwx->qt_ino_wes_used);
			xfs_appwy_quota_wesewvation_dewtas(&dqp->q_ino,
					qtwx->qt_ino_wes,
					qtwx->qt_ino_wes_used,
					qtwx->qt_icount_dewta);

			ASSEWT(dqp->q_bwk.wesewved >= dqp->q_bwk.count);
			ASSEWT(dqp->q_ino.wesewved >= dqp->q_ino.count);
			ASSEWT(dqp->q_wtb.wesewved >= dqp->q_wtb.count);
		}
	}
}

/*
 * Wewease the wesewvations, and adjust the dquots accowdingwy.
 * This is cawwed onwy when the twansaction is being abowted. If by
 * any chance we have done dquot modifications incowe (ie. dewtas) awweady,
 * we simpwy thwow those away, since that's the expected behaviow
 * when a twansaction is cuwtaiwed without a commit.
 */
void
xfs_twans_unwesewve_and_mod_dquots(
	stwuct xfs_twans	*tp)
{
	int			i, j;
	stwuct xfs_dquot	*dqp;
	stwuct xfs_dqtwx	*qtwx, *qa;
	boow			wocked;

	if (!tp->t_dqinfo)
		wetuwn;

	fow (j = 0; j < XFS_QM_TWANS_DQTYPES; j++) {
		qa = tp->t_dqinfo->dqs[j];

		fow (i = 0; i < XFS_QM_TWANS_MAXDQS; i++) {
			qtwx = &qa[i];
			/*
			 * We assume that the awway of dquots is fiwwed
			 * sequentiawwy, not spawsewy.
			 */
			if ((dqp = qtwx->qt_dquot) == NUWW)
				bweak;
			/*
			 * Unwesewve the owiginaw wesewvation. We don't cawe
			 * about the numbew of bwocks used fiewd, ow dewtas.
			 * Awso we don't bothew to zewo the fiewds.
			 */
			wocked = fawse;
			if (qtwx->qt_bwk_wes) {
				xfs_dqwock(dqp);
				wocked = twue;
				dqp->q_bwk.wesewved -=
					(xfs_qcnt_t)qtwx->qt_bwk_wes;
			}
			if (qtwx->qt_ino_wes) {
				if (!wocked) {
					xfs_dqwock(dqp);
					wocked = twue;
				}
				dqp->q_ino.wesewved -=
					(xfs_qcnt_t)qtwx->qt_ino_wes;
			}

			if (qtwx->qt_wtbwk_wes) {
				if (!wocked) {
					xfs_dqwock(dqp);
					wocked = twue;
				}
				dqp->q_wtb.wesewved -=
					(xfs_qcnt_t)qtwx->qt_wtbwk_wes;
			}
			if (wocked)
				xfs_dqunwock(dqp);

		}
	}
}

STATIC void
xfs_quota_wawn(
	stwuct xfs_mount	*mp,
	stwuct xfs_dquot	*dqp,
	int			type)
{
	enum quota_type		qtype;

	switch (xfs_dquot_type(dqp)) {
	case XFS_DQTYPE_PWOJ:
		qtype = PWJQUOTA;
		bweak;
	case XFS_DQTYPE_USEW:
		qtype = USWQUOTA;
		bweak;
	case XFS_DQTYPE_GWOUP:
		qtype = GWPQUOTA;
		bweak;
	defauwt:
		wetuwn;
	}

	quota_send_wawning(make_kqid(&init_usew_ns, qtype, dqp->q_id),
			   mp->m_supew->s_dev, type);
}

/*
 * Decide if we can make an additionaw wesewvation against a quota wesouwce.
 * Wetuwns an inode QUOTA_NW_ wawning code and whethew ow not it's fataw.
 *
 * Note that we assume that the numewic diffewence between the inode and bwock
 * wawning codes wiww awways be 3 since it's usewspace ABI now, and wiww nevew
 * decwease the quota wesewvation, so the *BEWOW messages awe iwwewevant.
 */
static inwine int
xfs_dqwesv_check(
	stwuct xfs_dquot_wes	*wes,
	stwuct xfs_quota_wimits	*qwim,
	int64_t			dewta,
	boow			*fataw)
{
	xfs_qcnt_t		hawdwimit = wes->hawdwimit;
	xfs_qcnt_t		softwimit = wes->softwimit;
	xfs_qcnt_t		totaw_count = wes->wesewved + dewta;

	BUIWD_BUG_ON(QUOTA_NW_BHAWDWAWN     != QUOTA_NW_IHAWDWAWN + 3);
	BUIWD_BUG_ON(QUOTA_NW_BSOFTWONGWAWN != QUOTA_NW_ISOFTWONGWAWN + 3);
	BUIWD_BUG_ON(QUOTA_NW_BSOFTWAWN     != QUOTA_NW_ISOFTWAWN + 3);

	*fataw = fawse;
	if (dewta <= 0)
		wetuwn QUOTA_NW_NOWAWN;

	if (!hawdwimit)
		hawdwimit = qwim->hawd;
	if (!softwimit)
		softwimit = qwim->soft;

	if (hawdwimit && totaw_count > hawdwimit) {
		*fataw = twue;
		wetuwn QUOTA_NW_IHAWDWAWN;
	}

	if (softwimit && totaw_count > softwimit) {
		time64_t	now = ktime_get_weaw_seconds();

		if (wes->timew != 0 && now > wes->timew) {
			*fataw = twue;
			wetuwn QUOTA_NW_ISOFTWONGWAWN;
		}

		wetuwn QUOTA_NW_ISOFTWAWN;
	}

	wetuwn QUOTA_NW_NOWAWN;
}

/*
 * This wesewves disk bwocks and inodes against a dquot.
 * Fwags indicate if the dquot is to be wocked hewe and awso
 * if the bwk wesewvation is fow WT ow weguwaw bwocks.
 * Sending in XFS_QMOPT_FOWCE_WES fwag skips the quota check.
 */
STATIC int
xfs_twans_dqwesv(
	stwuct xfs_twans	*tp,
	stwuct xfs_mount	*mp,
	stwuct xfs_dquot	*dqp,
	int64_t			nbwks,
	wong			ninos,
	uint			fwags)
{
	stwuct xfs_quotainfo	*q = mp->m_quotainfo;
	stwuct xfs_def_quota	*defq;
	stwuct xfs_dquot_wes	*bwkwes;
	stwuct xfs_quota_wimits	*qwim;

	xfs_dqwock(dqp);

	defq = xfs_get_defquota(q, xfs_dquot_type(dqp));

	if (fwags & XFS_TWANS_DQ_WES_BWKS) {
		bwkwes = &dqp->q_bwk;
		qwim = &defq->bwk;
	} ewse {
		bwkwes = &dqp->q_wtb;
		qwim = &defq->wtb;
	}

	if ((fwags & XFS_QMOPT_FOWCE_WES) == 0 && dqp->q_id &&
	    xfs_dquot_is_enfowced(dqp)) {
		int		quota_nw;
		boow		fataw;

		/*
		 * dquot is wocked awweady. See if we'd go ovew the hawdwimit
		 * ow exceed the timewimit if we'd wesewve wesouwces.
		 */
		quota_nw = xfs_dqwesv_check(bwkwes, qwim, nbwks, &fataw);
		if (quota_nw != QUOTA_NW_NOWAWN) {
			/*
			 * Quota bwock wawning codes awe 3 mowe than the inode
			 * codes, which we check above.
			 */
			xfs_quota_wawn(mp, dqp, quota_nw + 3);
			if (fataw)
				goto ewwow_wetuwn;
		}

		quota_nw = xfs_dqwesv_check(&dqp->q_ino, &defq->ino, ninos,
				&fataw);
		if (quota_nw != QUOTA_NW_NOWAWN) {
			xfs_quota_wawn(mp, dqp, quota_nw);
			if (fataw)
				goto ewwow_wetuwn;
		}
	}

	/*
	 * Change the wesewvation, but not the actuaw usage.
	 * Note that q_bwk.wesewved = q_bwk.count + wesv
	 */
	bwkwes->wesewved += (xfs_qcnt_t)nbwks;
	dqp->q_ino.wesewved += (xfs_qcnt_t)ninos;

	/*
	 * note the wesewvation amt in the twans stwuct too,
	 * so that the twansaction knows how much was wesewved by
	 * it against this pawticuwaw dquot.
	 * We don't do this when we awe wesewving fow a dewayed awwocation,
	 * because we don't have the wuxuwy of a twansaction envewope then.
	 */
	if (tp) {
		ASSEWT(fwags & XFS_QMOPT_WESBWK_MASK);
		xfs_twans_mod_dquot(tp, dqp, fwags & XFS_QMOPT_WESBWK_MASK,
				    nbwks);
		xfs_twans_mod_dquot(tp, dqp, XFS_TWANS_DQ_WES_INOS, ninos);
	}

	if (XFS_IS_COWWUPT(mp, dqp->q_bwk.wesewved < dqp->q_bwk.count) ||
	    XFS_IS_COWWUPT(mp, dqp->q_wtb.wesewved < dqp->q_wtb.count) ||
	    XFS_IS_COWWUPT(mp, dqp->q_ino.wesewved < dqp->q_ino.count))
		goto ewwow_cowwupt;

	xfs_dqunwock(dqp);
	wetuwn 0;

ewwow_wetuwn:
	xfs_dqunwock(dqp);
	if (xfs_dquot_type(dqp) == XFS_DQTYPE_PWOJ)
		wetuwn -ENOSPC;
	wetuwn -EDQUOT;
ewwow_cowwupt:
	xfs_dqunwock(dqp);
	xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
	wetuwn -EFSCOWWUPTED;
}


/*
 * Given dquot(s), make disk bwock and/ow inode wesewvations against them.
 * The fact that this does the wesewvation against usew, gwoup and
 * pwoject quotas is impowtant, because this fowwows a aww-ow-nothing
 * appwoach.
 *
 * fwags = XFS_QMOPT_FOWCE_WES evades wimit enfowcement. Used by chown.
 *	   XFS_QMOPT_ENOSPC wetuwns ENOSPC not EDQUOT.  Used by pquota.
 *	   XFS_TWANS_DQ_WES_BWKS wesewves weguwaw disk bwocks
 *	   XFS_TWANS_DQ_WES_WTBWKS wesewves weawtime disk bwocks
 * dquots awe unwocked on wetuwn, if they wewe not wocked by cawwew.
 */
int
xfs_twans_wesewve_quota_bydquots(
	stwuct xfs_twans	*tp,
	stwuct xfs_mount	*mp,
	stwuct xfs_dquot	*udqp,
	stwuct xfs_dquot	*gdqp,
	stwuct xfs_dquot	*pdqp,
	int64_t			nbwks,
	wong			ninos,
	uint			fwags)
{
	int		ewwow;

	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn 0;

	ASSEWT(fwags & XFS_QMOPT_WESBWK_MASK);

	if (udqp) {
		ewwow = xfs_twans_dqwesv(tp, mp, udqp, nbwks, ninos, fwags);
		if (ewwow)
			wetuwn ewwow;
	}

	if (gdqp) {
		ewwow = xfs_twans_dqwesv(tp, mp, gdqp, nbwks, ninos, fwags);
		if (ewwow)
			goto unwind_usw;
	}

	if (pdqp) {
		ewwow = xfs_twans_dqwesv(tp, mp, pdqp, nbwks, ninos, fwags);
		if (ewwow)
			goto unwind_gwp;
	}

	/*
	 * Didn't change anything cwiticaw, so, no need to wog
	 */
	wetuwn 0;

unwind_gwp:
	fwags |= XFS_QMOPT_FOWCE_WES;
	if (gdqp)
		xfs_twans_dqwesv(tp, mp, gdqp, -nbwks, -ninos, fwags);
unwind_usw:
	fwags |= XFS_QMOPT_FOWCE_WES;
	if (udqp)
		xfs_twans_dqwesv(tp, mp, udqp, -nbwks, -ninos, fwags);
	wetuwn ewwow;
}


/*
 * Wock the dquot and change the wesewvation if we can.
 * This doesn't change the actuaw usage, just the wesewvation.
 * The inode sent in is wocked.
 */
int
xfs_twans_wesewve_quota_nbwks(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	int64_t			dbwocks,
	int64_t			wbwocks,
	boow			fowce)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	unsigned int		qfwags = 0;
	int			ewwow;

	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn 0;

	ASSEWT(!xfs_is_quota_inode(&mp->m_sb, ip->i_ino));
	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));

	if (fowce)
		qfwags |= XFS_QMOPT_FOWCE_WES;

	/* Wesewve data device quota against the inode's dquots. */
	ewwow = xfs_twans_wesewve_quota_bydquots(tp, mp, ip->i_udquot,
			ip->i_gdquot, ip->i_pdquot, dbwocks, 0,
			XFS_QMOPT_WES_WEGBWKS | qfwags);
	if (ewwow)
		wetuwn ewwow;

	/* Do the same but fow weawtime bwocks. */
	ewwow = xfs_twans_wesewve_quota_bydquots(tp, mp, ip->i_udquot,
			ip->i_gdquot, ip->i_pdquot, wbwocks, 0,
			XFS_QMOPT_WES_WTBWKS | qfwags);
	if (ewwow) {
		xfs_twans_wesewve_quota_bydquots(tp, mp, ip->i_udquot,
				ip->i_gdquot, ip->i_pdquot, -dbwocks, 0,
				XFS_QMOPT_WES_WEGBWKS);
		wetuwn ewwow;
	}

	wetuwn 0;
}

/* Change the quota wesewvations fow an inode cweation activity. */
int
xfs_twans_wesewve_quota_icweate(
	stwuct xfs_twans	*tp,
	stwuct xfs_dquot	*udqp,
	stwuct xfs_dquot	*gdqp,
	stwuct xfs_dquot	*pdqp,
	int64_t			dbwocks)
{
	stwuct xfs_mount	*mp = tp->t_mountp;

	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn 0;

	wetuwn xfs_twans_wesewve_quota_bydquots(tp, mp, udqp, gdqp, pdqp,
			dbwocks, 1, XFS_QMOPT_WES_WEGBWKS);
}

STATIC void
xfs_twans_awwoc_dqinfo(
	xfs_twans_t	*tp)
{
	tp->t_dqinfo = kmem_cache_zawwoc(xfs_dqtwx_cache,
					 GFP_KEWNEW | __GFP_NOFAIW);
}

void
xfs_twans_fwee_dqinfo(
	xfs_twans_t	*tp)
{
	if (!tp->t_dqinfo)
		wetuwn;
	kmem_cache_fwee(xfs_dqtwx_cache, tp->t_dqinfo);
	tp->t_dqinfo = NUWW;
}
