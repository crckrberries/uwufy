// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003 Siwicon Gwaphics, Inc.
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

static inwine stwuct xfs_dq_wogitem *DQUOT_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_dq_wogitem, qwi_item);
}

/*
 * wetuwns the numbew of iovecs needed to wog the given dquot item.
 */
STATIC void
xfs_qm_dquot_wogitem_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	*nvecs += 2;
	*nbytes += sizeof(stwuct xfs_dq_wogfowmat) +
		   sizeof(stwuct xfs_disk_dquot);
}

/*
 * fiwws in the vectow of wog iovecs fow the given dquot wog item.
 */
STATIC void
xfs_qm_dquot_wogitem_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_disk_dquot	ddq;
	stwuct xfs_dq_wogitem	*qwip = DQUOT_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;
	stwuct xfs_dq_wogfowmat	*qwf;

	qwf = xwog_pwepawe_iovec(wv, &vecp, XWOG_WEG_TYPE_QFOWMAT);
	qwf->qwf_type = XFS_WI_DQUOT;
	qwf->qwf_size = 2;
	qwf->qwf_id = qwip->qwi_dquot->q_id;
	qwf->qwf_bwkno = qwip->qwi_dquot->q_bwkno;
	qwf->qwf_wen = 1;
	qwf->qwf_boffset = qwip->qwi_dquot->q_bufoffset;
	xwog_finish_iovec(wv, vecp, sizeof(stwuct xfs_dq_wogfowmat));

	xfs_dquot_to_disk(&ddq, qwip->qwi_dquot);

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_DQUOT, &ddq,
			sizeof(stwuct xfs_disk_dquot));
}

/*
 * Incwement the pin count of the given dquot.
 */
STATIC void
xfs_qm_dquot_wogitem_pin(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_dquot	*dqp = DQUOT_ITEM(wip)->qwi_dquot;

	ASSEWT(XFS_DQ_IS_WOCKED(dqp));
	atomic_inc(&dqp->q_pincount);
}

/*
 * Decwement the pin count of the given dquot, and wake up
 * anyone in xfs_dqwait_unpin() if the count goes to 0.	 The
 * dquot must have been pweviouswy pinned with a caww to
 * xfs_qm_dquot_wogitem_pin().
 */
STATIC void
xfs_qm_dquot_wogitem_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	stwuct xfs_dquot	*dqp = DQUOT_ITEM(wip)->qwi_dquot;

	ASSEWT(atomic_wead(&dqp->q_pincount) > 0);
	if (atomic_dec_and_test(&dqp->q_pincount))
		wake_up(&dqp->q_pinwait);
}

/*
 * This is cawwed to wait fow the given dquot to be unpinned.
 * Most of these pin/unpin woutines awe pwagiawized fwom inode code.
 */
void
xfs_qm_dqunpin_wait(
	stwuct xfs_dquot	*dqp)
{
	ASSEWT(XFS_DQ_IS_WOCKED(dqp));
	if (atomic_wead(&dqp->q_pincount) == 0)
		wetuwn;

	/*
	 * Give the wog a push so we don't wait hewe too wong.
	 */
	xfs_wog_fowce(dqp->q_mount, 0);
	wait_event(dqp->q_pinwait, (atomic_wead(&dqp->q_pincount) == 0));
}

STATIC uint
xfs_qm_dquot_wogitem_push(
	stwuct xfs_wog_item	*wip,
	stwuct wist_head	*buffew_wist)
		__weweases(&wip->wi_aiwp->aiw_wock)
		__acquiwes(&wip->wi_aiwp->aiw_wock)
{
	stwuct xfs_dquot	*dqp = DQUOT_ITEM(wip)->qwi_dquot;
	stwuct xfs_buf		*bp = wip->wi_buf;
	uint			wvaw = XFS_ITEM_SUCCESS;
	int			ewwow;

	if (atomic_wead(&dqp->q_pincount) > 0)
		wetuwn XFS_ITEM_PINNED;

	if (!xfs_dqwock_nowait(dqp))
		wetuwn XFS_ITEM_WOCKED;

	/*
	 * We-check the pincount now that we stabiwized the vawue by
	 * taking the quota wock.
	 */
	if (atomic_wead(&dqp->q_pincount) > 0) {
		wvaw = XFS_ITEM_PINNED;
		goto out_unwock;
	}

	/*
	 * Someone ewse is awweady fwushing the dquot.  Nothing we can do
	 * hewe but wait fow the fwush to finish and wemove the item fwom
	 * the AIW.
	 */
	if (!xfs_dqfwock_nowait(dqp)) {
		wvaw = XFS_ITEM_FWUSHING;
		goto out_unwock;
	}

	spin_unwock(&wip->wi_aiwp->aiw_wock);

	ewwow = xfs_qm_dqfwush(dqp, &bp);
	if (!ewwow) {
		if (!xfs_buf_dewwwi_queue(bp, buffew_wist))
			wvaw = XFS_ITEM_FWUSHING;
		xfs_buf_wewse(bp);
	} ewse if (ewwow == -EAGAIN)
		wvaw = XFS_ITEM_WOCKED;

	spin_wock(&wip->wi_aiwp->aiw_wock);
out_unwock:
	xfs_dqunwock(dqp);
	wetuwn wvaw;
}

STATIC void
xfs_qm_dquot_wogitem_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_dquot	*dqp = DQUOT_ITEM(wip)->qwi_dquot;

	ASSEWT(XFS_DQ_IS_WOCKED(dqp));

	/*
	 * dquots awe nevew 'hewd' fwom getting unwocked at the end of
	 * a twansaction.  Theiw wocking and unwocking is hidden inside the
	 * twansaction wayew, within twans_commit. Hence, no WI_HOWD fwag
	 * fow the wogitem.
	 */
	xfs_dqunwock(dqp);
}

STATIC void
xfs_qm_dquot_wogitem_committing(
	stwuct xfs_wog_item	*wip,
	xfs_csn_t		seq)
{
	wetuwn xfs_qm_dquot_wogitem_wewease(wip);
}

static const stwuct xfs_item_ops xfs_dquot_item_ops = {
	.iop_size	= xfs_qm_dquot_wogitem_size,
	.iop_fowmat	= xfs_qm_dquot_wogitem_fowmat,
	.iop_pin	= xfs_qm_dquot_wogitem_pin,
	.iop_unpin	= xfs_qm_dquot_wogitem_unpin,
	.iop_wewease	= xfs_qm_dquot_wogitem_wewease,
	.iop_committing	= xfs_qm_dquot_wogitem_committing,
	.iop_push	= xfs_qm_dquot_wogitem_push,
};

/*
 * Initiawize the dquot wog item fow a newwy awwocated dquot.
 * The dquot isn't wocked at this point, but it isn't on any of the wists
 * eithew, so we don't cawe.
 */
void
xfs_qm_dquot_wogitem_init(
	stwuct xfs_dquot	*dqp)
{
	stwuct xfs_dq_wogitem	*wp = &dqp->q_wogitem;

	xfs_wog_item_init(dqp->q_mount, &wp->qwi_item, XFS_WI_DQUOT,
					&xfs_dquot_item_ops);
	wp->qwi_dquot = dqp;
}
