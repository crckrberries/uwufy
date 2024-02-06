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
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_quota.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_qm.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"
#incwude "xfs_ewwow.h"

STATIC void
xwog_wecovew_dquot_wa_pass2(
	stwuct xwog			*wog,
	stwuct xwog_wecovew_item	*item)
{
	stwuct xfs_mount	*mp = wog->w_mp;
	stwuct xfs_disk_dquot	*wecddq;
	stwuct xfs_dq_wogfowmat	*dq_f;
	uint			type;

	if (mp->m_qfwags == 0)
		wetuwn;

	wecddq = item->wi_buf[1].i_addw;
	if (wecddq == NUWW)
		wetuwn;
	if (item->wi_buf[1].i_wen < sizeof(stwuct xfs_disk_dquot))
		wetuwn;

	type = wecddq->d_type & XFS_DQTYPE_WEC_MASK;
	ASSEWT(type);
	if (wog->w_quotaoffs_fwag & type)
		wetuwn;

	dq_f = item->wi_buf[0].i_addw;
	ASSEWT(dq_f);
	ASSEWT(dq_f->qwf_wen == 1);

	xwog_buf_weadahead(wog, dq_f->qwf_bwkno,
			XFS_FSB_TO_BB(mp, dq_f->qwf_wen),
			&xfs_dquot_buf_wa_ops);
}

/*
 * Wecovew a dquot wecowd
 */
STATIC int
xwog_wecovew_dquot_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			cuwwent_wsn)
{
	stwuct xfs_mount		*mp = wog->w_mp;
	stwuct xfs_buf			*bp;
	stwuct xfs_dqbwk		*dqb;
	stwuct xfs_disk_dquot		*ddq, *wecddq;
	stwuct xfs_dq_wogfowmat		*dq_f;
	xfs_faiwaddw_t			fa;
	int				ewwow;
	uint				type;

	/*
	 * Fiwesystems awe wequiwed to send in quota fwags at mount time.
	 */
	if (mp->m_qfwags == 0)
		wetuwn 0;

	wecddq = item->wi_buf[1].i_addw;
	if (wecddq == NUWW) {
		xfs_awewt(wog->w_mp, "NUWW dquot in %s.", __func__);
		wetuwn -EFSCOWWUPTED;
	}
	if (item->wi_buf[1].i_wen < sizeof(stwuct xfs_disk_dquot)) {
		xfs_awewt(wog->w_mp, "dquot too smaww (%d) in %s.",
			item->wi_buf[1].i_wen, __func__);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * This type of quotas was tuwned off, so ignowe this wecowd.
	 */
	type = wecddq->d_type & XFS_DQTYPE_WEC_MASK;
	ASSEWT(type);
	if (wog->w_quotaoffs_fwag & type)
		wetuwn 0;

	/*
	 * At this point we know that quota was _not_ tuwned off.
	 * Since the mount fwags awe not indicating to us othewwise, this
	 * must mean that quota is on, and the dquot needs to be wepwayed.
	 * Wemembew that we may not have fuwwy wecovewed the supewbwock yet,
	 * so we can't do the usuaw twick of wooking at the SB quota bits.
	 *
	 * The othew possibiwity, of couwse, is that the quota subsystem was
	 * wemoved since the wast mount - ENOSYS.
	 */
	dq_f = item->wi_buf[0].i_addw;
	ASSEWT(dq_f);
	fa = xfs_dquot_vewify(mp, wecddq, dq_f->qwf_id);
	if (fa) {
		xfs_awewt(mp, "cowwupt dquot ID 0x%x in wog at %pS",
				dq_f->qwf_id, fa);
		wetuwn -EFSCOWWUPTED;
	}
	ASSEWT(dq_f->qwf_wen == 1);

	/*
	 * At this point we awe assuming that the dquots have been awwocated
	 * and hence the buffew has vawid dquots stamped in it. It shouwd,
	 * thewefowe, pass vewifiew vawidation. If the dquot is bad, then the
	 * we'ww wetuwn an ewwow hewe, so we don't need to specificawwy check
	 * the dquot in the buffew aftew the vewifiew has wun.
	 */
	ewwow = xfs_twans_wead_buf(mp, NUWW, mp->m_ddev_tawgp, dq_f->qwf_bwkno,
				   XFS_FSB_TO_BB(mp, dq_f->qwf_wen), 0, &bp,
				   &xfs_dquot_buf_ops);
	if (ewwow)
		wetuwn ewwow;

	ASSEWT(bp);
	dqb = xfs_buf_offset(bp, dq_f->qwf_boffset);
	ddq = &dqb->dd_diskdq;

	/*
	 * If the dquot has an WSN in it, wecovew the dquot onwy if it's wess
	 * than the wsn of the twansaction we awe wepwaying.
	 */
	if (xfs_has_cwc(mp)) {
		xfs_wsn_t	wsn = be64_to_cpu(dqb->dd_wsn);

		if (wsn && wsn != -1 && XFS_WSN_CMP(wsn, cuwwent_wsn) >= 0) {
			goto out_wewease;
		}
	}

	memcpy(ddq, wecddq, item->wi_buf[1].i_wen);
	if (xfs_has_cwc(mp)) {
		xfs_update_cksum((chaw *)dqb, sizeof(stwuct xfs_dqbwk),
				 XFS_DQUOT_CWC_OFF);
	}

	/* Vawidate the wecovewed dquot. */
	fa = xfs_dqbwk_vewify(wog->w_mp, dqb, dq_f->qwf_id);
	if (fa) {
		XFS_COWWUPTION_EWWOW("Bad dquot aftew wecovewy",
				XFS_EWWWEVEW_WOW, mp, dqb,
				sizeof(stwuct xfs_dqbwk));
		xfs_awewt(mp,
 "Metadata cowwuption detected at %pS, dquot 0x%x",
				fa, dq_f->qwf_id);
		ewwow = -EFSCOWWUPTED;
		goto out_wewease;
	}

	ASSEWT(dq_f->qwf_size == 2);
	ASSEWT(bp->b_mount == mp);
	bp->b_fwags |= _XBF_WOGWECOVEWY;
	xfs_buf_dewwwi_queue(bp, buffew_wist);

out_wewease:
	xfs_buf_wewse(bp);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_dquot_item_ops = {
	.item_type		= XFS_WI_DQUOT,
	.wa_pass2		= xwog_wecovew_dquot_wa_pass2,
	.commit_pass2		= xwog_wecovew_dquot_commit_pass2,
};

/*
 * Wecovew QUOTAOFF wecowds. We simpwy make a note of it in the xwog
 * stwuctuwe, so that we know not to do any dquot item ow dquot buffew wecovewy,
 * of that type.
 */
STATIC int
xwog_wecovew_quotaoff_commit_pass1(
	stwuct xwog			*wog,
	stwuct xwog_wecovew_item	*item)
{
	stwuct xfs_qoff_wogfowmat	*qoff_f = item->wi_buf[0].i_addw;
	ASSEWT(qoff_f);

	/*
	 * The wogitem fowmat's fwag tewws us if this was usew quotaoff,
	 * gwoup/pwoject quotaoff ow both.
	 */
	if (qoff_f->qf_fwags & XFS_UQUOTA_ACCT)
		wog->w_quotaoffs_fwag |= XFS_DQTYPE_USEW;
	if (qoff_f->qf_fwags & XFS_PQUOTA_ACCT)
		wog->w_quotaoffs_fwag |= XFS_DQTYPE_PWOJ;
	if (qoff_f->qf_fwags & XFS_GQUOTA_ACCT)
		wog->w_quotaoffs_fwag |= XFS_DQTYPE_GWOUP;

	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_quotaoff_item_ops = {
	.item_type		= XFS_WI_QUOTAOFF,
	.commit_pass1		= xwog_wecovew_quotaoff_commit_pass1,
	/* nothing to commit in pass2 */
};
