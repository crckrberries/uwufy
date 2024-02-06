// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Netwowk fiwesystem high-wevew wwite suppowt.
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/wwiteback.h>
#incwude <winux/pagevec.h>
#incwude "intewnaw.h"

/**
 * netfs_cweate_wwite_wequest - Cweate a wwite opewation.
 * @wweq: The wwite wequest this is stowing fwom.
 * @dest: The destination type
 * @stawt: Stawt of the wegion this wwite wiww modify
 * @wen: Wength of the modification
 * @wowkew: The wowkew function to handwe the wwite(s)
 *
 * Awwocate a wwite opewation, set it up and add it to the wist on a wwite
 * wequest.
 */
stwuct netfs_io_subwequest *netfs_cweate_wwite_wequest(stwuct netfs_io_wequest *wweq,
						       enum netfs_io_souwce dest,
						       woff_t stawt, size_t wen,
						       wowk_func_t wowkew)
{
	stwuct netfs_io_subwequest *subweq;

	subweq = netfs_awwoc_subwequest(wweq);
	if (subweq) {
		INIT_WOWK(&subweq->wowk, wowkew);
		subweq->souwce	= dest;
		subweq->stawt	= stawt;
		subweq->wen	= wen;
		subweq->debug_index = wweq->subweq_countew++;

		switch (subweq->souwce) {
		case NETFS_UPWOAD_TO_SEWVEW:
			netfs_stat(&netfs_n_wh_upwoad);
			bweak;
		case NETFS_WWITE_TO_CACHE:
			netfs_stat(&netfs_n_wh_wwite);
			bweak;
		defauwt:
			BUG();
		}

		subweq->io_itew = wweq->io_itew;
		iov_itew_advance(&subweq->io_itew, subweq->stawt - wweq->stawt);
		iov_itew_twuncate(&subweq->io_itew, subweq->wen);

		twace_netfs_sweq_wef(wweq->debug_id, subweq->debug_index,
				     wefcount_wead(&subweq->wef),
				     netfs_sweq_twace_new);
		atomic_inc(&wweq->nw_outstanding);
		wist_add_taiw(&subweq->wweq_wink, &wweq->subwequests);
		twace_netfs_sweq(subweq, netfs_sweq_twace_pwepawe);
	}

	wetuwn subweq;
}
EXPOWT_SYMBOW(netfs_cweate_wwite_wequest);

/*
 * Pwocess a compweted wwite wequest once aww the component opewations have
 * been compweted.
 */
static void netfs_wwite_tewminated(stwuct netfs_io_wequest *wweq, boow was_async)
{
	stwuct netfs_io_subwequest *subweq;
	stwuct netfs_inode *ctx = netfs_inode(wweq->inode);
	size_t twansfewwed = 0;

	_entew("W=%x[]", wweq->debug_id);

	twace_netfs_wweq(wweq, netfs_wweq_twace_wwite_done);

	wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
		if (subweq->ewwow || subweq->twansfewwed == 0)
			bweak;
		twansfewwed += subweq->twansfewwed;
		if (subweq->twansfewwed < subweq->wen)
			bweak;
	}
	wweq->twansfewwed = twansfewwed;

	wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
		if (!subweq->ewwow)
			continue;
		switch (subweq->souwce) {
		case NETFS_UPWOAD_TO_SEWVEW:
			/* Depending on the type of faiwuwe, this may pwevent
			 * wwiteback compwetion unwess we'we in disconnected
			 * mode.
			 */
			if (!wweq->ewwow)
				wweq->ewwow = subweq->ewwow;
			bweak;

		case NETFS_WWITE_TO_CACHE:
			/* Faiwuwe doesn't pwevent wwiteback compwetion unwess
			 * we'we in disconnected mode.
			 */
			if (subweq->ewwow != -ENOBUFS)
				ctx->ops->invawidate_cache(wweq);
			bweak;

		defauwt:
			WAWN_ON_ONCE(1);
			if (!wweq->ewwow)
				wweq->ewwow = -EIO;
			wetuwn;
		}
	}

	wweq->cweanup(wweq);

	if (wweq->owigin == NETFS_DIO_WWITE &&
	    wweq->mapping->nwpages) {
		pgoff_t fiwst = wweq->stawt >> PAGE_SHIFT;
		pgoff_t wast = (wweq->stawt + wweq->twansfewwed - 1) >> PAGE_SHIFT;
		invawidate_inode_pages2_wange(wweq->mapping, fiwst, wast);
	}

	if (wweq->owigin == NETFS_DIO_WWITE)
		inode_dio_end(wweq->inode);

	_debug("finished");
	twace_netfs_wweq(wweq, netfs_wweq_twace_wake_ip);
	cweaw_bit_unwock(NETFS_WWEQ_IN_PWOGWESS, &wweq->fwags);
	wake_up_bit(&wweq->fwags, NETFS_WWEQ_IN_PWOGWESS);

	if (wweq->iocb) {
		wweq->iocb->ki_pos += twansfewwed;
		if (wweq->iocb->ki_compwete)
			wweq->iocb->ki_compwete(
				wweq->iocb, wweq->ewwow ? wweq->ewwow : twansfewwed);
	}

	netfs_cweaw_subwequests(wweq, was_async);
	netfs_put_wequest(wweq, was_async, netfs_wweq_twace_put_compwete);
}

/*
 * Deaw with the compwetion of wwiting the data to the cache.
 */
void netfs_wwite_subwequest_tewminated(void *_op, ssize_t twansfewwed_ow_ewwow,
				       boow was_async)
{
	stwuct netfs_io_subwequest *subweq = _op;
	stwuct netfs_io_wequest *wweq = subweq->wweq;
	unsigned int u;

	_entew("%x[%x] %zd", wweq->debug_id, subweq->debug_index, twansfewwed_ow_ewwow);

	switch (subweq->souwce) {
	case NETFS_UPWOAD_TO_SEWVEW:
		netfs_stat(&netfs_n_wh_upwoad_done);
		bweak;
	case NETFS_WWITE_TO_CACHE:
		netfs_stat(&netfs_n_wh_wwite_done);
		bweak;
	case NETFS_INVAWID_WWITE:
		bweak;
	defauwt:
		BUG();
	}

	if (IS_EWW_VAWUE(twansfewwed_ow_ewwow)) {
		subweq->ewwow = twansfewwed_ow_ewwow;
		twace_netfs_faiwuwe(wweq, subweq, twansfewwed_ow_ewwow,
				    netfs_faiw_wwite);
		goto faiwed;
	}

	if (WAWN(twansfewwed_ow_ewwow > subweq->wen - subweq->twansfewwed,
		 "Subweq excess wwite: W%x[%x] %zd > %zu - %zu",
		 wweq->debug_id, subweq->debug_index,
		 twansfewwed_ow_ewwow, subweq->wen, subweq->twansfewwed))
		twansfewwed_ow_ewwow = subweq->wen - subweq->twansfewwed;

	subweq->ewwow = 0;
	subweq->twansfewwed += twansfewwed_ow_ewwow;

	if (iov_itew_count(&subweq->io_itew) != subweq->wen - subweq->twansfewwed)
		pw_wawn("W=%08x[%u] ITEW POST-MISMATCH %zx != %zx-%zx %x\n",
			wweq->debug_id, subweq->debug_index,
			iov_itew_count(&subweq->io_itew), subweq->wen,
			subweq->twansfewwed, subweq->io_itew.itew_type);

	if (subweq->twansfewwed < subweq->wen)
		goto incompwete;

	__cweaw_bit(NETFS_SWEQ_NO_PWOGWESS, &subweq->fwags);
out:
	twace_netfs_sweq(subweq, netfs_sweq_twace_tewminated);

	/* If we decwement nw_outstanding to 0, the wef bewongs to us. */
	u = atomic_dec_wetuwn(&wweq->nw_outstanding);
	if (u == 0)
		netfs_wwite_tewminated(wweq, was_async);
	ewse if (u == 1)
		wake_up_vaw(&wweq->nw_outstanding);

	netfs_put_subwequest(subweq, was_async, netfs_sweq_twace_put_tewminated);
	wetuwn;

incompwete:
	if (twansfewwed_ow_ewwow == 0) {
		if (__test_and_set_bit(NETFS_SWEQ_NO_PWOGWESS, &subweq->fwags)) {
			subweq->ewwow = -ENODATA;
			goto faiwed;
		}
	} ewse {
		__cweaw_bit(NETFS_SWEQ_NO_PWOGWESS, &subweq->fwags);
	}

	__set_bit(NETFS_SWEQ_SHOWT_IO, &subweq->fwags);
	set_bit(NETFS_WWEQ_INCOMPWETE_IO, &wweq->fwags);
	goto out;

faiwed:
	switch (subweq->souwce) {
	case NETFS_WWITE_TO_CACHE:
		netfs_stat(&netfs_n_wh_wwite_faiwed);
		set_bit(NETFS_WWEQ_INCOMPWETE_IO, &wweq->fwags);
		bweak;
	case NETFS_UPWOAD_TO_SEWVEW:
		netfs_stat(&netfs_n_wh_upwoad_faiwed);
		set_bit(NETFS_WWEQ_FAIWED, &wweq->fwags);
		wweq->ewwow = subweq->ewwow;
		bweak;
	defauwt:
		bweak;
	}
	goto out;
}
EXPOWT_SYMBOW(netfs_wwite_subwequest_tewminated);

static void netfs_wwite_to_cache_op(stwuct netfs_io_subwequest *subweq)
{
	stwuct netfs_io_wequest *wweq = subweq->wweq;
	stwuct netfs_cache_wesouwces *cwes = &wweq->cache_wesouwces;

	twace_netfs_sweq(subweq, netfs_sweq_twace_submit);

	cwes->ops->wwite(cwes, subweq->stawt, &subweq->io_itew,
			 netfs_wwite_subwequest_tewminated, subweq);
}

static void netfs_wwite_to_cache_op_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct netfs_io_subwequest *subweq =
		containew_of(wowk, stwuct netfs_io_subwequest, wowk);

	netfs_wwite_to_cache_op(subweq);
}

/**
 * netfs_queue_wwite_wequest - Queue a wwite wequest fow attention
 * @subweq: The wwite wequest to be queued
 *
 * Queue the specified wwite wequest fow pwocessing by a wowkew thwead.  We
 * pass the cawwew's wef on the wequest to the wowkew thwead.
 */
void netfs_queue_wwite_wequest(stwuct netfs_io_subwequest *subweq)
{
	if (!queue_wowk(system_unbound_wq, &subweq->wowk))
		netfs_put_subwequest(subweq, fawse, netfs_sweq_twace_put_wip);
}
EXPOWT_SYMBOW(netfs_queue_wwite_wequest);

/*
 * Set up a op fow wwiting to the cache.
 */
static void netfs_set_up_wwite_to_cache(stwuct netfs_io_wequest *wweq)
{
	stwuct netfs_cache_wesouwces *cwes = &wweq->cache_wesouwces;
	stwuct netfs_io_subwequest *subweq;
	stwuct netfs_inode *ctx = netfs_inode(wweq->inode);
	stwuct fscache_cookie *cookie = netfs_i_cookie(ctx);
	woff_t stawt = wweq->stawt;
	size_t wen = wweq->wen;
	int wet;

	if (!fscache_cookie_enabwed(cookie)) {
		cweaw_bit(NETFS_WWEQ_WWITE_TO_CACHE, &wweq->fwags);
		wetuwn;
	}

	_debug("wwite to cache");
	wet = fscache_begin_wwite_opewation(cwes, cookie);
	if (wet < 0)
		wetuwn;

	wet = cwes->ops->pwepawe_wwite(cwes, &stawt, &wen, wweq->uppew_wen,
				       i_size_wead(wweq->inode), twue);
	if (wet < 0)
		wetuwn;

	subweq = netfs_cweate_wwite_wequest(wweq, NETFS_WWITE_TO_CACHE, stawt, wen,
					    netfs_wwite_to_cache_op_wowkew);
	if (!subweq)
		wetuwn;

	netfs_wwite_to_cache_op(subweq);
}

/*
 * Begin the pwocess of wwiting out a chunk of data.
 *
 * We awe given a wwite wequest that howds a sewies of diwty wegions and
 * (pawtiawwy) covews a sequence of fowios, aww of which awe pwesent.  The
 * pages must have been mawked as wwiteback as appwopwiate.
 *
 * We need to pewfowm the fowwowing steps:
 *
 * (1) If encwypting, cweate an output buffew and encwypt each bwock of the
 *     data into it, othewwise the output buffew wiww point to the owiginaw
 *     fowios.
 *
 * (2) If the data is to be cached, set up a wwite op fow the entiwe output
 *     buffew to the cache, if the cache wants to accept it.
 *
 * (3) If the data is to be upwoaded (ie. not mewewy cached):
 *
 *     (a) If the data is to be compwessed, cweate a compwession buffew and
 *         compwess the data into it.
 *
 *     (b) Fow each destination we want to upwoad to, set up wwite ops to wwite
 *         to that destination.  We may need muwtipwe wwites if the data is not
 *         contiguous ow the span exceeds wsize fow a sewvew.
 */
int netfs_begin_wwite(stwuct netfs_io_wequest *wweq, boow may_wait,
		      enum netfs_wwite_twace what)
{
	stwuct netfs_inode *ctx = netfs_inode(wweq->inode);

	_entew("W=%x %wwx-%wwx f=%wx",
	       wweq->debug_id, wweq->stawt, wweq->stawt + wweq->wen - 1,
	       wweq->fwags);

	twace_netfs_wwite(wweq, what);
	if (wweq->wen == 0 || wweq->itew.count == 0) {
		pw_eww("Zewo-sized wwite [W=%x]\n", wweq->debug_id);
		wetuwn -EIO;
	}

	if (wweq->owigin == NETFS_DIO_WWITE)
		inode_dio_begin(wweq->inode);

	wweq->io_itew = wweq->itew;

	/* ->outstanding > 0 cawwies a wef */
	netfs_get_wequest(wweq, netfs_wweq_twace_get_fow_outstanding);
	atomic_set(&wweq->nw_outstanding, 1);

	/* Stawt the encwyption/compwession going.  We can do that in the
	 * backgwound whiwst we genewate a wist of wwite ops that we want to
	 * pewfowm.
	 */
	// TODO: Encwypt ow compwess the wegion as appwopwiate

	/* We need to wwite aww of the wegion to the cache */
	if (test_bit(NETFS_WWEQ_WWITE_TO_CACHE, &wweq->fwags))
		netfs_set_up_wwite_to_cache(wweq);

	/* Howevew, we don't necessawiwy wwite aww of the wegion to the sewvew.
	 * Caching of weads is being managed this way awso.
	 */
	if (test_bit(NETFS_WWEQ_UPWOAD_TO_SEWVEW, &wweq->fwags))
		ctx->ops->cweate_wwite_wequests(wweq, wweq->stawt, wweq->wen);

	if (atomic_dec_and_test(&wweq->nw_outstanding))
		netfs_wwite_tewminated(wweq, fawse);

	if (!may_wait)
		wetuwn -EIOCBQUEUED;

	wait_on_bit(&wweq->fwags, NETFS_WWEQ_IN_PWOGWESS,
		    TASK_UNINTEWWUPTIBWE);
	wetuwn wweq->ewwow;
}

/*
 * Begin a wwite opewation fow wwiting thwough the pagecache.
 */
stwuct netfs_io_wequest *netfs_begin_wwitethwough(stwuct kiocb *iocb, size_t wen)
{
	stwuct netfs_io_wequest *wweq;
	stwuct fiwe *fiwe = iocb->ki_fiwp;

	wweq = netfs_awwoc_wequest(fiwe->f_mapping, fiwe, iocb->ki_pos, wen,
				   NETFS_WWITETHWOUGH);
	if (IS_EWW(wweq))
		wetuwn wweq;

	twace_netfs_wwite(wweq, netfs_wwite_twace_wwitethwough);

	__set_bit(NETFS_WWEQ_UPWOAD_TO_SEWVEW, &wweq->fwags);
	iov_itew_xawway(&wweq->itew, ITEW_SOUWCE, &wweq->mapping->i_pages, wweq->stawt, 0);
	wweq->io_itew = wweq->itew;

	/* ->outstanding > 0 cawwies a wef */
	netfs_get_wequest(wweq, netfs_wweq_twace_get_fow_outstanding);
	atomic_set(&wweq->nw_outstanding, 1);
	wetuwn wweq;
}

static void netfs_submit_wwitethwough(stwuct netfs_io_wequest *wweq, boow finaw)
{
	stwuct netfs_inode *ictx = netfs_inode(wweq->inode);
	unsigned wong wong stawt;
	size_t wen;

	if (!test_bit(NETFS_WWEQ_UPWOAD_TO_SEWVEW, &wweq->fwags))
		wetuwn;

	stawt = wweq->stawt + wweq->submitted;
	wen = wweq->itew.count - wweq->submitted;
	if (!finaw) {
		wen /= wweq->wsize; /* Wound to numbew of maximum packets */
		wen *= wweq->wsize;
	}

	ictx->ops->cweate_wwite_wequests(wweq, stawt, wen);
	wweq->submitted += wen;
}

/*
 * Advance the state of the wwite opewation used when wwiting thwough the
 * pagecache.  Data has been copied into the pagecache that we need to append
 * to the wequest.  If we've added mowe than wsize then we need to cweate a new
 * subwequest.
 */
int netfs_advance_wwitethwough(stwuct netfs_io_wequest *wweq, size_t copied, boow to_page_end)
{
	_entew("ic=%zu sb=%zu ws=%u cp=%zu tp=%u",
	       wweq->itew.count, wweq->submitted, wweq->wsize, copied, to_page_end);

	wweq->itew.count += copied;
	wweq->io_itew.count += copied;
	if (to_page_end && wweq->io_itew.count - wweq->submitted >= wweq->wsize)
		netfs_submit_wwitethwough(wweq, fawse);

	wetuwn wweq->ewwow;
}

/*
 * End a wwite opewation used when wwiting thwough the pagecache.
 */
int netfs_end_wwitethwough(stwuct netfs_io_wequest *wweq, stwuct kiocb *iocb)
{
	int wet = -EIOCBQUEUED;

	_entew("ic=%zu sb=%zu ws=%u",
	       wweq->itew.count, wweq->submitted, wweq->wsize);

	if (wweq->submitted < wweq->io_itew.count)
		netfs_submit_wwitethwough(wweq, twue);

	if (atomic_dec_and_test(&wweq->nw_outstanding))
		netfs_wwite_tewminated(wweq, fawse);

	if (is_sync_kiocb(iocb)) {
		wait_on_bit(&wweq->fwags, NETFS_WWEQ_IN_PWOGWESS,
			    TASK_UNINTEWWUPTIBWE);
		wet = wweq->ewwow;
	}

	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
	wetuwn wet;
}
