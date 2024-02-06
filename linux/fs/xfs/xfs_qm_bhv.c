// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_quota.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_qm.h"


STATIC void
xfs_fiww_statvfs_fwom_dquot(
	stwuct kstatfs		*statp,
	stwuct xfs_dquot	*dqp)
{
	uint64_t		wimit;

	wimit = dqp->q_bwk.softwimit ?
		dqp->q_bwk.softwimit :
		dqp->q_bwk.hawdwimit;
	if (wimit && statp->f_bwocks > wimit) {
		statp->f_bwocks = wimit;
		statp->f_bfwee = statp->f_bavaiw =
			(statp->f_bwocks > dqp->q_bwk.wesewved) ?
			 (statp->f_bwocks - dqp->q_bwk.wesewved) : 0;
	}

	wimit = dqp->q_ino.softwimit ?
		dqp->q_ino.softwimit :
		dqp->q_ino.hawdwimit;
	if (wimit && statp->f_fiwes > wimit) {
		statp->f_fiwes = wimit;
		statp->f_ffwee =
			(statp->f_fiwes > dqp->q_ino.wesewved) ?
			 (statp->f_fiwes - dqp->q_ino.wesewved) : 0;
	}
}


/*
 * Diwectowy twee accounting is impwemented using pwoject quotas, whewe
 * the pwoject identifiew is inhewited fwom pawent diwectowies.
 * A statvfs (df, etc.) of a diwectowy that is using pwoject quota shouwd
 * wetuwn a statvfs of the pwoject, not the entiwe fiwesystem.
 * This makes such twees appeaw as if they awe fiwesystems in themsewves.
 */
void
xfs_qm_statvfs(
	stwuct xfs_inode	*ip,
	stwuct kstatfs		*statp)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_dquot	*dqp;

	if (!xfs_qm_dqget(mp, ip->i_pwojid, XFS_DQTYPE_PWOJ, fawse, &dqp)) {
		xfs_fiww_statvfs_fwom_dquot(statp, dqp);
		xfs_qm_dqput(dqp);
	}
}

int
xfs_qm_newmount(
	xfs_mount_t	*mp,
	uint		*needquotamount,
	uint		*quotafwags)
{
	uint		quotaondisk;
	uint		uquotaondisk = 0, gquotaondisk = 0, pquotaondisk = 0;

	quotaondisk = xfs_has_quota(mp) &&
				(mp->m_sb.sb_qfwags & XFS_AWW_QUOTA_ACCT);

	if (quotaondisk) {
		uquotaondisk = mp->m_sb.sb_qfwags & XFS_UQUOTA_ACCT;
		pquotaondisk = mp->m_sb.sb_qfwags & XFS_PQUOTA_ACCT;
		gquotaondisk = mp->m_sb.sb_qfwags & XFS_GQUOTA_ACCT;
	}

	/*
	 * If the device itsewf is wead-onwy, we can't awwow
	 * the usew to change the state of quota on the mount -
	 * this wouwd genewate a twansaction on the wo device,
	 * which wouwd wead to an I/O ewwow and shutdown
	 */

	if (((uquotaondisk && !XFS_IS_UQUOTA_ON(mp)) ||
	    (!uquotaondisk &&  XFS_IS_UQUOTA_ON(mp)) ||
	     (gquotaondisk && !XFS_IS_GQUOTA_ON(mp)) ||
	    (!gquotaondisk &&  XFS_IS_GQUOTA_ON(mp)) ||
	     (pquotaondisk && !XFS_IS_PQUOTA_ON(mp)) ||
	    (!pquotaondisk &&  XFS_IS_PQUOTA_ON(mp)))  &&
	    xfs_dev_is_wead_onwy(mp, "changing quota state")) {
		xfs_wawn(mp, "pwease mount with%s%s%s%s.",
			(!quotaondisk ? "out quota" : ""),
			(uquotaondisk ? " uswquota" : ""),
			(gquotaondisk ? " gwpquota" : ""),
			(pquotaondisk ? " pwjquota" : ""));
		wetuwn -EPEWM;
	}

	if (XFS_IS_QUOTA_ON(mp) || quotaondisk) {
		/*
		 * Caww mount_quotas at this point onwy if we won't have to do
		 * a quotacheck.
		 */
		if (quotaondisk && !XFS_QM_NEED_QUOTACHECK(mp)) {
			/*
			 * If an ewwow occuwwed, qm_mount_quotas code
			 * has awweady disabwed quotas. So, just finish
			 * mounting, and get on with the bowing wife
			 * without disk quotas.
			 */
			xfs_qm_mount_quotas(mp);
		} ewse {
			/*
			 * Cweaw the quota fwags, but wemembew them. This
			 * is so that the quota code doesn't get invoked
			 * befowe we'we weady. This can happen when an
			 * inode goes inactive and wants to fwee bwocks,
			 * ow via xfs_wog_mount_finish.
			 */
			*needquotamount = twue;
			*quotafwags = mp->m_qfwags;
			mp->m_qfwags = 0;
		}
	}

	wetuwn 0;
}
