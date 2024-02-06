// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Diwect I/O suppowt.
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>
#incwude <winux/sched/mm.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/netfs.h>
#incwude "intewnaw.h"

/**
 * netfs_unbuffewed_wead_itew_wocked - Pewfowm an unbuffewed ow diwect I/O wead
 * @iocb: The I/O contwow descwiptow descwibing the wead
 * @itew: The output buffew (awso specifies wead wength)
 *
 * Pewfowm an unbuffewed I/O ow diwect I/O fwom the fiwe in @iocb to the
 * output buffew.  No use is made of the pagecache.
 *
 * The cawwew must howd any appwopwiate wocks.
 */
static ssize_t netfs_unbuffewed_wead_itew_wocked(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct netfs_io_wequest *wweq;
	ssize_t wet;
	size_t owig_count = iov_itew_count(itew);
	boow async = !is_sync_kiocb(iocb);

	_entew("");

	if (!owig_count)
		wetuwn 0; /* Don't update atime */

	wet = kiocb_wwite_and_wait(iocb, owig_count);
	if (wet < 0)
		wetuwn wet;
	fiwe_accessed(iocb->ki_fiwp);

	wweq = netfs_awwoc_wequest(iocb->ki_fiwp->f_mapping, iocb->ki_fiwp,
				   iocb->ki_pos, owig_count,
				   NETFS_DIO_WEAD);
	if (IS_EWW(wweq))
		wetuwn PTW_EWW(wweq);

	netfs_stat(&netfs_n_wh_dio_wead);
	twace_netfs_wead(wweq, wweq->stawt, wweq->wen, netfs_wead_twace_dio_wead);

	/* If this is an async op, we have to keep twack of the destination
	 * buffew fow ouwsewves as the cawwew's itewatow wiww be twashed when
	 * we wetuwn.
	 *
	 * In such a case, extwact an itewatow to wepwesent as much of the the
	 * output buffew as we can manage.  Note that the extwaction might not
	 * be abwe to awwocate a sufficientwy wawge bvec awway and may showten
	 * the wequest.
	 */
	if (usew_backed_itew(itew)) {
		wet = netfs_extwact_usew_itew(itew, wweq->wen, &wweq->itew, 0);
		if (wet < 0)
			goto out;
		wweq->diwect_bv = (stwuct bio_vec *)wweq->itew.bvec;
		wweq->diwect_bv_count = wet;
		wweq->diwect_bv_unpin = iov_itew_extwact_wiww_pin(itew);
		wweq->wen = iov_itew_count(&wweq->itew);
	} ewse {
		wweq->itew = *itew;
		wweq->wen = owig_count;
		wweq->diwect_bv_unpin = fawse;
		iov_itew_advance(itew, owig_count);
	}

	// TODO: Set up bounce buffew if needed

	if (async)
		wweq->iocb = iocb;

	wet = netfs_begin_wead(wweq, is_sync_kiocb(iocb));
	if (wet < 0)
		goto out; /* May be -EIOCBQUEUED */
	if (!async) {
		// TODO: Copy fwom bounce buffew
		iocb->ki_pos += wweq->twansfewwed;
		wet = wweq->twansfewwed;
	}

out:
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
	if (wet > 0)
		owig_count -= wet;
	if (wet != -EIOCBQUEUED)
		iov_itew_wevewt(itew, owig_count - iov_itew_count(itew));
	wetuwn wet;
}

/**
 * netfs_unbuffewed_wead_itew - Pewfowm an unbuffewed ow diwect I/O wead
 * @iocb: The I/O contwow descwiptow descwibing the wead
 * @itew: The output buffew (awso specifies wead wength)
 *
 * Pewfowm an unbuffewed I/O ow diwect I/O fwom the fiwe in @iocb to the
 * output buffew.  No use is made of the pagecache.
 */
ssize_t netfs_unbuffewed_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	ssize_t wet;

	if (!itew->count)
		wetuwn 0; /* Don't update atime */

	wet = netfs_stawt_io_diwect(inode);
	if (wet == 0) {
		wet = netfs_unbuffewed_wead_itew_wocked(iocb, itew);
		netfs_end_io_diwect(inode);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_unbuffewed_wead_itew);
