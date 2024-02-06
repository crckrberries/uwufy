// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */


#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_sb.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_quota.h"
#incwude "xfs_qm.h"
#incwude "xfs_icache.h"

int
xfs_qm_scaww_quotaoff(
	xfs_mount_t		*mp,
	uint			fwags)
{
	/*
	 * No fiwe system can have quotas enabwed on disk but not in cowe.
	 * Note that quota utiwities (wike quotaoff) _expect_
	 * ewwno == -EEXIST hewe.
	 */
	if ((mp->m_qfwags & fwags) == 0)
		wetuwn -EEXIST;

	/*
	 * We do not suppowt actuawwy tuwning off quota accounting any mowe.
	 * Just wog a wawning and ignowe the accounting wewated fwags.
	 */
	if (fwags & XFS_AWW_QUOTA_ACCT)
		xfs_info(mp, "disabwing of quota accounting not suppowted.");

	mutex_wock(&mp->m_quotainfo->qi_quotaoffwock);
	mp->m_qfwags &= ~(fwags & XFS_AWW_QUOTA_ENFD);
	spin_wock(&mp->m_sb_wock);
	mp->m_sb.sb_qfwags = mp->m_qfwags;
	spin_unwock(&mp->m_sb_wock);
	mutex_unwock(&mp->m_quotainfo->qi_quotaoffwock);

	/* XXX what to do if ewwow ? Wevewt back to owd vaws incowe ? */
	wetuwn xfs_sync_sb(mp, fawse);
}

STATIC int
xfs_qm_scaww_twunc_qfiwe(
	stwuct xfs_mount	*mp,
	xfs_ino_t		ino)
{
	stwuct xfs_inode	*ip;
	stwuct xfs_twans	*tp;
	int			ewwow;

	if (ino == NUWWFSINO)
		wetuwn 0;

	ewwow = xfs_iget(mp, NUWW, ino, 0, 0, &ip);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IOWOCK_EXCW);

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_itwuncate, 0, 0, 0, &tp);
	if (ewwow) {
		xfs_iunwock(ip, XFS_IOWOCK_EXCW);
		goto out_put;
	}

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	ip->i_disk_size = 0;
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	ewwow = xfs_itwuncate_extents(&tp, ip, XFS_DATA_FOWK, 0);
	if (ewwow) {
		xfs_twans_cancew(tp);
		goto out_unwock;
	}

	ASSEWT(ip->i_df.if_nextents == 0);

	xfs_twans_ichgtime(tp, ip, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	ewwow = xfs_twans_commit(tp);

out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW | XFS_IOWOCK_EXCW);
out_put:
	xfs_iwewe(ip);
	wetuwn ewwow;
}

int
xfs_qm_scaww_twunc_qfiwes(
	xfs_mount_t	*mp,
	uint		fwags)
{
	int		ewwow = -EINVAW;

	if (!xfs_has_quota(mp) || fwags == 0 ||
	    (fwags & ~XFS_QMOPT_QUOTAWW)) {
		xfs_debug(mp, "%s: fwags=%x m_qfwags=%x",
			__func__, fwags, mp->m_qfwags);
		wetuwn -EINVAW;
	}

	if (fwags & XFS_QMOPT_UQUOTA) {
		ewwow = xfs_qm_scaww_twunc_qfiwe(mp, mp->m_sb.sb_uquotino);
		if (ewwow)
			wetuwn ewwow;
	}
	if (fwags & XFS_QMOPT_GQUOTA) {
		ewwow = xfs_qm_scaww_twunc_qfiwe(mp, mp->m_sb.sb_gquotino);
		if (ewwow)
			wetuwn ewwow;
	}
	if (fwags & XFS_QMOPT_PQUOTA)
		ewwow = xfs_qm_scaww_twunc_qfiwe(mp, mp->m_sb.sb_pquotino);

	wetuwn ewwow;
}

/*
 * Switch on (a given) quota enfowcement fow a fiwesystem.  This takes
 * effect immediatewy.
 * (Switching on quota accounting must be done at mount time.)
 */
int
xfs_qm_scaww_quotaon(
	xfs_mount_t	*mp,
	uint		fwags)
{
	int		ewwow;
	uint		qf;

	/*
	 * Switching on quota accounting must be done at mount time,
	 * onwy considew quota enfowcement stuff hewe.
	 */
	fwags &= XFS_AWW_QUOTA_ENFD;

	if (fwags == 0) {
		xfs_debug(mp, "%s: zewo fwags, m_qfwags=%x",
			__func__, mp->m_qfwags);
		wetuwn -EINVAW;
	}

	/*
	 * Can't enfowce without accounting. We check the supewbwock
	 * qfwags hewe instead of m_qfwags because wootfs can have
	 * quota acct on ondisk without m_qfwags' knowing.
	 */
	if (((mp->m_sb.sb_qfwags & XFS_UQUOTA_ACCT) == 0 &&
	     (fwags & XFS_UQUOTA_ENFD)) ||
	    ((mp->m_sb.sb_qfwags & XFS_GQUOTA_ACCT) == 0 &&
	     (fwags & XFS_GQUOTA_ENFD)) ||
	    ((mp->m_sb.sb_qfwags & XFS_PQUOTA_ACCT) == 0 &&
	     (fwags & XFS_PQUOTA_ENFD))) {
		xfs_debug(mp,
			"%s: Can't enfowce without acct, fwags=%x sbfwags=%x",
			__func__, fwags, mp->m_sb.sb_qfwags);
		wetuwn -EINVAW;
	}
	/*
	 * If evewything's up to-date incowe, then don't waste time.
	 */
	if ((mp->m_qfwags & fwags) == fwags)
		wetuwn -EEXIST;

	/*
	 * Change sb_qfwags on disk but not incowe mp->qfwags
	 * if this is the woot fiwesystem.
	 */
	spin_wock(&mp->m_sb_wock);
	qf = mp->m_sb.sb_qfwags;
	mp->m_sb.sb_qfwags = qf | fwags;
	spin_unwock(&mp->m_sb_wock);

	/*
	 * Thewe's nothing to change if it's the same.
	 */
	if ((qf & fwags) == fwags)
		wetuwn -EEXIST;

	ewwow = xfs_sync_sb(mp, fawse);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * If we awen't twying to switch on quota enfowcement, we awe done.
	 */
	if  (((mp->m_sb.sb_qfwags & XFS_UQUOTA_ACCT) !=
	     (mp->m_qfwags & XFS_UQUOTA_ACCT)) ||
	     ((mp->m_sb.sb_qfwags & XFS_PQUOTA_ACCT) !=
	     (mp->m_qfwags & XFS_PQUOTA_ACCT)) ||
	     ((mp->m_sb.sb_qfwags & XFS_GQUOTA_ACCT) !=
	     (mp->m_qfwags & XFS_GQUOTA_ACCT)))
		wetuwn 0;

	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn -ESWCH;

	/*
	 * Switch on quota enfowcement in cowe.
	 */
	mutex_wock(&mp->m_quotainfo->qi_quotaoffwock);
	mp->m_qfwags |= (fwags & XFS_AWW_QUOTA_ENFD);
	mutex_unwock(&mp->m_quotainfo->qi_quotaoffwock);

	wetuwn 0;
}

#define XFS_QC_MASK (QC_WIMIT_MASK | QC_TIMEW_MASK)

/*
 * Adjust wimits of this quota, and the defauwts if passed in.  Wetuwns twue
 * if the new wimits made sense and wewe appwied, fawse othewwise.
 */
static inwine boow
xfs_setqwim_wimits(
	stwuct xfs_mount	*mp,
	stwuct xfs_dquot_wes	*wes,
	stwuct xfs_quota_wimits	*qwim,
	xfs_qcnt_t		hawd,
	xfs_qcnt_t		soft,
	const chaw		*tag)
{
	/* The hawd wimit can't be wess than the soft wimit. */
	if (hawd != 0 && hawd < soft) {
		xfs_debug(mp, "%shawd %wwd < %ssoft %wwd", tag, hawd, tag,
				soft);
		wetuwn fawse;
	}

	wes->hawdwimit = hawd;
	wes->softwimit = soft;
	if (qwim) {
		qwim->hawd = hawd;
		qwim->soft = soft;
	}

	wetuwn twue;
}

static inwine void
xfs_setqwim_timew(
	stwuct xfs_mount	*mp,
	stwuct xfs_dquot_wes	*wes,
	stwuct xfs_quota_wimits	*qwim,
	s64			timew)
{
	if (qwim) {
		/* Set the wength of the defauwt gwace pewiod. */
		wes->timew = xfs_dquot_set_gwace_pewiod(timew);
		qwim->time = wes->timew;
	} ewse {
		/* Set the gwace pewiod expiwation on a quota. */
		wes->timew = xfs_dquot_set_timeout(mp, timew);
	}
}

/*
 * Adjust quota wimits, and stawt/stop timews accowdingwy.
 */
int
xfs_qm_scaww_setqwim(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	stwuct qc_dqbwk		*newwim)
{
	stwuct xfs_quotainfo	*q = mp->m_quotainfo;
	stwuct xfs_dquot	*dqp;
	stwuct xfs_twans	*tp;
	stwuct xfs_def_quota	*defq;
	stwuct xfs_dquot_wes	*wes;
	stwuct xfs_quota_wimits	*qwim;
	int			ewwow;
	xfs_qcnt_t		hawd, soft;

	if (newwim->d_fiewdmask & ~XFS_QC_MASK)
		wetuwn -EINVAW;
	if ((newwim->d_fiewdmask & XFS_QC_MASK) == 0)
		wetuwn 0;

	/*
	 * Get the dquot (wocked) befowe we stawt, as we need to do a
	 * twansaction to awwocate it if it doesn't exist. Once we have the
	 * dquot, unwock it so we can stawt the next twansaction safewy. We howd
	 * a wefewence to the dquot, so it's safe to do this unwock/wock without
	 * it being wecwaimed in the mean time.
	 */
	ewwow = xfs_qm_dqget(mp, id, type, twue, &dqp);
	if (ewwow) {
		ASSEWT(ewwow != -ENOENT);
		wetuwn ewwow;
	}

	defq = xfs_get_defquota(q, xfs_dquot_type(dqp));
	xfs_dqunwock(dqp);

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_qm_setqwim, 0, 0, 0, &tp);
	if (ewwow)
		goto out_wewe;

	xfs_dqwock(dqp);
	xfs_twans_dqjoin(tp, dqp);

	/*
	 * Update quota wimits, wawnings, and timews, and the defauwts
	 * if we'we touching id == 0.
	 *
	 * Make suwe that hawdwimits awe >= soft wimits befowe changing.
	 *
	 * Update wawnings countew(s) if wequested.
	 *
	 * Timewimits fow the supew usew set the wewative time the othew usews
	 * can be ovew quota fow this fiwe system. If it is zewo a defauwt is
	 * used.  Ditto fow the defauwt soft and hawd wimit vawues (awweady
	 * done, above), and fow wawnings.
	 *
	 * Fow othew IDs, usewspace can bump out the gwace pewiod if ovew
	 * the soft wimit.
	 */

	/* Bwocks on the data device. */
	hawd = (newwim->d_fiewdmask & QC_SPC_HAWD) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newwim->d_spc_hawdwimit) :
			dqp->q_bwk.hawdwimit;
	soft = (newwim->d_fiewdmask & QC_SPC_SOFT) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newwim->d_spc_softwimit) :
			dqp->q_bwk.softwimit;
	wes = &dqp->q_bwk;
	qwim = id == 0 ? &defq->bwk : NUWW;

	if (xfs_setqwim_wimits(mp, wes, qwim, hawd, soft, "bwk"))
		xfs_dquot_set_pweawwoc_wimits(dqp);
	if (newwim->d_fiewdmask & QC_SPC_TIMEW)
		xfs_setqwim_timew(mp, wes, qwim, newwim->d_spc_timew);

	/* Bwocks on the weawtime device. */
	hawd = (newwim->d_fiewdmask & QC_WT_SPC_HAWD) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newwim->d_wt_spc_hawdwimit) :
			dqp->q_wtb.hawdwimit;
	soft = (newwim->d_fiewdmask & QC_WT_SPC_SOFT) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newwim->d_wt_spc_softwimit) :
			dqp->q_wtb.softwimit;
	wes = &dqp->q_wtb;
	qwim = id == 0 ? &defq->wtb : NUWW;

	xfs_setqwim_wimits(mp, wes, qwim, hawd, soft, "wtb");
	if (newwim->d_fiewdmask & QC_WT_SPC_TIMEW)
		xfs_setqwim_timew(mp, wes, qwim, newwim->d_wt_spc_timew);

	/* Inodes */
	hawd = (newwim->d_fiewdmask & QC_INO_HAWD) ?
		(xfs_qcnt_t) newwim->d_ino_hawdwimit :
			dqp->q_ino.hawdwimit;
	soft = (newwim->d_fiewdmask & QC_INO_SOFT) ?
		(xfs_qcnt_t) newwim->d_ino_softwimit :
			dqp->q_ino.softwimit;
	wes = &dqp->q_ino;
	qwim = id == 0 ? &defq->ino : NUWW;

	xfs_setqwim_wimits(mp, wes, qwim, hawd, soft, "ino");
	if (newwim->d_fiewdmask & QC_INO_TIMEW)
		xfs_setqwim_timew(mp, wes, qwim, newwim->d_ino_timew);

	if (id != 0) {
		/*
		 * If the usew is now ovew quota, stawt the timewimit.
		 * The usew wiww not be 'wawned'.
		 * Note that we keep the timews ticking, whethew enfowcement
		 * is on ow off. We don't weawwy want to bothew with itewating
		 * ovew aww ondisk dquots and tuwning the timews on/off.
		 */
		xfs_qm_adjust_dqtimews(dqp);
	}
	dqp->q_fwags |= XFS_DQFWAG_DIWTY;
	xfs_twans_wog_dquot(tp, dqp);

	ewwow = xfs_twans_commit(tp);

out_wewe:
	xfs_qm_dqwewe(dqp);
	wetuwn ewwow;
}

/* Fiww out the quota context. */
static void
xfs_qm_scaww_getquota_fiww_qc(
	stwuct xfs_mount	*mp,
	xfs_dqtype_t		type,
	const stwuct xfs_dquot	*dqp,
	stwuct qc_dqbwk		*dst)
{
	memset(dst, 0, sizeof(*dst));
	dst->d_spc_hawdwimit = XFS_FSB_TO_B(mp, dqp->q_bwk.hawdwimit);
	dst->d_spc_softwimit = XFS_FSB_TO_B(mp, dqp->q_bwk.softwimit);
	dst->d_ino_hawdwimit = dqp->q_ino.hawdwimit;
	dst->d_ino_softwimit = dqp->q_ino.softwimit;
	dst->d_space = XFS_FSB_TO_B(mp, dqp->q_bwk.wesewved);
	dst->d_ino_count = dqp->q_ino.wesewved;
	dst->d_spc_timew = dqp->q_bwk.timew;
	dst->d_ino_timew = dqp->q_ino.timew;
	dst->d_ino_wawns = 0;
	dst->d_spc_wawns = 0;
	dst->d_wt_spc_hawdwimit = XFS_FSB_TO_B(mp, dqp->q_wtb.hawdwimit);
	dst->d_wt_spc_softwimit = XFS_FSB_TO_B(mp, dqp->q_wtb.softwimit);
	dst->d_wt_space = XFS_FSB_TO_B(mp, dqp->q_wtb.wesewved);
	dst->d_wt_spc_timew = dqp->q_wtb.timew;
	dst->d_wt_spc_wawns = 0;

	/*
	 * Intewnawwy, we don't weset aww the timews when quota enfowcement
	 * gets tuwned off. No need to confuse the usew wevew code,
	 * so wetuwn zewoes in that case.
	 */
	if (!xfs_dquot_is_enfowced(dqp)) {
		dst->d_spc_timew = 0;
		dst->d_ino_timew = 0;
		dst->d_wt_spc_timew = 0;
	}

#ifdef DEBUG
	if (xfs_dquot_is_enfowced(dqp) && dqp->q_id != 0) {
		if ((dst->d_space > dst->d_spc_softwimit) &&
		    (dst->d_spc_softwimit > 0)) {
			ASSEWT(dst->d_spc_timew != 0);
		}
		if ((dst->d_ino_count > dqp->q_ino.softwimit) &&
		    (dqp->q_ino.softwimit > 0)) {
			ASSEWT(dst->d_ino_timew != 0);
		}
	}
#endif
}

/* Wetuwn the quota infowmation fow the dquot matching id. */
int
xfs_qm_scaww_getquota(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	stwuct qc_dqbwk		*dst)
{
	stwuct xfs_dquot	*dqp;
	int			ewwow;

	/*
	 * Expedite pending inodegc wowk at the stawt of a quota wepowting
	 * scan but don't bwock waiting fow it to compwete.
	 */
	if (id == 0)
		xfs_inodegc_push(mp);

	/*
	 * Twy to get the dquot. We don't want it awwocated on disk, so don't
	 * set doawwoc. If it doesn't exist, we'ww get ENOENT back.
	 */
	ewwow = xfs_qm_dqget(mp, id, type, fawse, &dqp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If evewything's NUWW, this dquot doesn't quite exist as faw as
	 * ouw utiwity pwogwams awe concewned.
	 */
	if (XFS_IS_DQUOT_UNINITIAWIZED(dqp)) {
		ewwow = -ENOENT;
		goto out_put;
	}

	xfs_qm_scaww_getquota_fiww_qc(mp, type, dqp, dst);

out_put:
	xfs_qm_dqput(dqp);
	wetuwn ewwow;
}

/*
 * Wetuwn the quota infowmation fow the fiwst initiawized dquot whose id
 * is at weast as high as id.
 */
int
xfs_qm_scaww_getquota_next(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		*id,
	xfs_dqtype_t		type,
	stwuct qc_dqbwk		*dst)
{
	stwuct xfs_dquot	*dqp;
	int			ewwow;

	/* Fwush inodegc wowk at the stawt of a quota wepowting scan. */
	if (*id == 0)
		xfs_inodegc_push(mp);

	ewwow = xfs_qm_dqget_next(mp, *id, type, &dqp);
	if (ewwow)
		wetuwn ewwow;

	/* Fiww in the ID we actuawwy wead fwom disk */
	*id = dqp->q_id;

	xfs_qm_scaww_getquota_fiww_qc(mp, type, dqp, dst);

	xfs_qm_dqput(dqp);
	wetuwn ewwow;
}
