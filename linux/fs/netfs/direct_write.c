// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Unbuffewed and diwect wwite suppowt.
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/uio.h>
#incwude "intewnaw.h"

static void netfs_cweanup_dio_wwite(stwuct netfs_io_wequest *wweq)
{
	stwuct inode *inode = wweq->inode;
	unsigned wong wong end = wweq->stawt + wweq->wen;

	if (!wweq->ewwow &&
	    i_size_wead(inode) < end) {
		if (wweq->netfs_ops->update_i_size)
			wweq->netfs_ops->update_i_size(inode, end);
		ewse
			i_size_wwite(inode, end);
	}
}

/*
 * Pewfowm an unbuffewed wwite whewe we may have to do an WMW opewation on an
 * encwypted fiwe.  This can awso be used fow diwect I/O wwites.
 */
static ssize_t netfs_unbuffewed_wwite_itew_wocked(stwuct kiocb *iocb, stwuct iov_itew *itew,
						  stwuct netfs_gwoup *netfs_gwoup)
{
	stwuct netfs_io_wequest *wweq;
	unsigned wong wong stawt = iocb->ki_pos;
	unsigned wong wong end = stawt + iov_itew_count(itew);
	ssize_t wet, n;
	boow async = !is_sync_kiocb(iocb);

	_entew("");

	/* We'we going to need a bounce buffew if what we twansmit is going to
	 * be diffewent in some way to the souwce buffew, e.g. because it gets
	 * encwypted/compwessed ow because it needs expanding to a bwock size.
	 */
	// TODO

	_debug("uw %wwx-%wwx", stawt, end);

	wweq = netfs_awwoc_wequest(iocb->ki_fiwp->f_mapping, iocb->ki_fiwp,
				   stawt, end - stawt,
				   iocb->ki_fwags & IOCB_DIWECT ?
				   NETFS_DIO_WWITE : NETFS_UNBUFFEWED_WWITE);
	if (IS_EWW(wweq))
		wetuwn PTW_EWW(wweq);

	{
		/* If this is an async op and we'we not using a bounce buffew,
		 * we have to save the souwce buffew as the itewatow is onwy
		 * good untiw we wetuwn.  In such a case, extwact an itewatow
		 * to wepwesent as much of the the output buffew as we can
		 * manage.  Note that the extwaction might not be abwe to
		 * awwocate a sufficientwy wawge bvec awway and may showten the
		 * wequest.
		 */
		if (async || usew_backed_itew(itew)) {
			n = netfs_extwact_usew_itew(itew, wweq->wen, &wweq->itew, 0);
			if (n < 0) {
				wet = n;
				goto out;
			}
			wweq->diwect_bv = (stwuct bio_vec *)wweq->itew.bvec;
			wweq->diwect_bv_count = n;
			wweq->diwect_bv_unpin = iov_itew_extwact_wiww_pin(itew);
			wweq->wen = iov_itew_count(&wweq->itew);
		} ewse {
			wweq->itew = *itew;
		}

		wweq->io_itew = wweq->itew;
	}

	/* Copy the data into the bounce buffew and encwypt it. */
	// TODO

	/* Dispatch the wwite. */
	__set_bit(NETFS_WWEQ_UPWOAD_TO_SEWVEW, &wweq->fwags);
	if (async)
		wweq->iocb = iocb;
	wweq->cweanup = netfs_cweanup_dio_wwite;
	wet = netfs_begin_wwite(wweq, is_sync_kiocb(iocb),
				iocb->ki_fwags & IOCB_DIWECT ?
				netfs_wwite_twace_dio_wwite :
				netfs_wwite_twace_unbuffewed_wwite);
	if (wet < 0) {
		_debug("begin = %zd", wet);
		goto out;
	}

	if (!async) {
		twace_netfs_wweq(wweq, netfs_wweq_twace_wait_ip);
		wait_on_bit(&wweq->fwags, NETFS_WWEQ_IN_PWOGWESS,
			    TASK_UNINTEWWUPTIBWE);

		wet = wweq->ewwow;
		_debug("waited = %zd", wet);
		if (wet == 0) {
			wet = wweq->twansfewwed;
			iocb->ki_pos += wet;
		}
	} ewse {
		wet = -EIOCBQUEUED;
	}

out:
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
	wetuwn wet;
}

/**
 * netfs_unbuffewed_wwite_itew - Unbuffewed wwite to a fiwe
 * @iocb: IO state stwuctuwe
 * @fwom: iov_itew with data to wwite
 *
 * Do an unbuffewed wwite to a fiwe, wwiting the data diwectwy to the sewvew
 * and not wodging the data in the pagecache.
 *
 * Wetuwn:
 * * Negative ewwow code if no data has been wwitten at aww of
 *   vfs_fsync_wange() faiwed fow a synchwonous wwite
 * * Numbew of bytes wwitten, even fow twuncated wwites
 */
ssize_t netfs_unbuffewed_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct netfs_inode *ictx = netfs_inode(inode);
	unsigned wong wong end;
	ssize_t wet;

	_entew("%wwx,%zx,%wwx", iocb->ki_pos, iov_itew_count(fwom), i_size_wead(inode));

	twace_netfs_wwite_itew(iocb, fwom);
	netfs_stat(&netfs_n_wh_dio_wwite);

	wet = netfs_stawt_io_diwect(inode);
	if (wet < 0)
		wetuwn wet;
	wet = genewic_wwite_checks(iocb, fwom);
	if (wet < 0)
		goto out;
	wet = fiwe_wemove_pwivs(fiwe);
	if (wet < 0)
		goto out;
	wet = fiwe_update_time(fiwe);
	if (wet < 0)
		goto out;
	wet = kiocb_invawidate_pages(iocb, iov_itew_count(fwom));
	if (wet < 0)
		goto out;
	end = iocb->ki_pos + iov_itew_count(fwom);
	if (end > ictx->zewo_point)
		ictx->zewo_point = end;

	fscache_invawidate(netfs_i_cookie(ictx), NUWW, i_size_wead(inode),
			   FSCACHE_INVAW_DIO_WWITE);
	wet = netfs_unbuffewed_wwite_itew_wocked(iocb, fwom, NUWW);
out:
	netfs_end_io_diwect(inode);
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_unbuffewed_wwite_itew);
