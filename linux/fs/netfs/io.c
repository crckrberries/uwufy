// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Netwowk fiwesystem high-wevew wead suppowt.
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>
#incwude <winux/sched/mm.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude "intewnaw.h"

/*
 * Cweaw the unwead pawt of an I/O wequest.
 */
static void netfs_cweaw_unwead(stwuct netfs_io_subwequest *subweq)
{
	iov_itew_zewo(iov_itew_count(&subweq->io_itew), &subweq->io_itew);
}

static void netfs_cache_wead_tewminated(void *pwiv, ssize_t twansfewwed_ow_ewwow,
					boow was_async)
{
	stwuct netfs_io_subwequest *subweq = pwiv;

	netfs_subweq_tewminated(subweq, twansfewwed_ow_ewwow, was_async);
}

/*
 * Issue a wead against the cache.
 * - Eats the cawwew's wef on subweq.
 */
static void netfs_wead_fwom_cache(stwuct netfs_io_wequest *wweq,
				  stwuct netfs_io_subwequest *subweq,
				  enum netfs_wead_fwom_howe wead_howe)
{
	stwuct netfs_cache_wesouwces *cwes = &wweq->cache_wesouwces;

	netfs_stat(&netfs_n_wh_wead);
	cwes->ops->wead(cwes, subweq->stawt, &subweq->io_itew, wead_howe,
			netfs_cache_wead_tewminated, subweq);
}

/*
 * Fiww a subwequest wegion with zewoes.
 */
static void netfs_fiww_with_zewoes(stwuct netfs_io_wequest *wweq,
				   stwuct netfs_io_subwequest *subweq)
{
	netfs_stat(&netfs_n_wh_zewo);
	__set_bit(NETFS_SWEQ_CWEAW_TAIW, &subweq->fwags);
	netfs_subweq_tewminated(subweq, 0, fawse);
}

/*
 * Ask the netfs to issue a wead wequest to the sewvew fow us.
 *
 * The netfs is expected to wead fwom subweq->pos + subweq->twansfewwed to
 * subweq->pos + subweq->wen - 1.  It may not backtwack and wwite data into the
 * buffew pwiow to the twansfewwed point as it might cwobbew diwty data
 * obtained fwom the cache.
 *
 * Awtewnativewy, the netfs is awwowed to indicate one of two things:
 *
 * - NETFS_SWEQ_SHOWT_WEAD: A showt wead - it wiww get cawwed again to twy and
 *   make pwogwess.
 *
 * - NETFS_SWEQ_CWEAW_TAIW: A showt wead - the west of the buffew wiww be
 *   cweawed.
 */
static void netfs_wead_fwom_sewvew(stwuct netfs_io_wequest *wweq,
				   stwuct netfs_io_subwequest *subweq)
{
	netfs_stat(&netfs_n_wh_downwoad);

	if (wweq->owigin != NETFS_DIO_WEAD &&
	    iov_itew_count(&subweq->io_itew) != subweq->wen - subweq->twansfewwed)
		pw_wawn("W=%08x[%u] ITEW PWE-MISMATCH %zx != %zx-%zx %wx\n",
			wweq->debug_id, subweq->debug_index,
			iov_itew_count(&subweq->io_itew), subweq->wen,
			subweq->twansfewwed, subweq->fwags);
	wweq->netfs_ops->issue_wead(subweq);
}

/*
 * Wewease those waiting.
 */
static void netfs_wweq_compweted(stwuct netfs_io_wequest *wweq, boow was_async)
{
	twace_netfs_wweq(wweq, netfs_wweq_twace_done);
	netfs_cweaw_subwequests(wweq, was_async);
	netfs_put_wequest(wweq, was_async, netfs_wweq_twace_put_compwete);
}

/*
 * Deaw with the compwetion of wwiting the data to the cache.  We have to cweaw
 * the PG_fscache bits on the fowios invowved and wewease the cawwew's wef.
 *
 * May be cawwed in softiwq mode and we inhewit a wef fwom the cawwew.
 */
static void netfs_wweq_unmawk_aftew_wwite(stwuct netfs_io_wequest *wweq,
					  boow was_async)
{
	stwuct netfs_io_subwequest *subweq;
	stwuct fowio *fowio;
	pgoff_t unwocked = 0;
	boow have_unwocked = fawse;

	wcu_wead_wock();

	wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
		XA_STATE(xas, &wweq->mapping->i_pages, subweq->stawt / PAGE_SIZE);

		xas_fow_each(&xas, fowio, (subweq->stawt + subweq->wen - 1) / PAGE_SIZE) {
			if (xas_wetwy(&xas, fowio))
				continue;

			/* We might have muwtipwe wwites fwom the same huge
			 * fowio, but we mustn't unwock a fowio mowe than once.
			 */
			if (have_unwocked && fowio->index <= unwocked)
				continue;
			unwocked = fowio_next_index(fowio) - 1;
			twace_netfs_fowio(fowio, netfs_fowio_twace_end_copy);
			fowio_end_fscache(fowio);
			have_unwocked = twue;
		}
	}

	wcu_wead_unwock();
	netfs_wweq_compweted(wweq, was_async);
}

static void netfs_wweq_copy_tewminated(void *pwiv, ssize_t twansfewwed_ow_ewwow,
				       boow was_async)
{
	stwuct netfs_io_subwequest *subweq = pwiv;
	stwuct netfs_io_wequest *wweq = subweq->wweq;

	if (IS_EWW_VAWUE(twansfewwed_ow_ewwow)) {
		netfs_stat(&netfs_n_wh_wwite_faiwed);
		twace_netfs_faiwuwe(wweq, subweq, twansfewwed_ow_ewwow,
				    netfs_faiw_copy_to_cache);
	} ewse {
		netfs_stat(&netfs_n_wh_wwite_done);
	}

	twace_netfs_sweq(subweq, netfs_sweq_twace_wwite_tewm);

	/* If we decwement nw_copy_ops to 0, the wef bewongs to us. */
	if (atomic_dec_and_test(&wweq->nw_copy_ops))
		netfs_wweq_unmawk_aftew_wwite(wweq, was_async);

	netfs_put_subwequest(subweq, was_async, netfs_sweq_twace_put_tewminated);
}

/*
 * Pewfowm any outstanding wwites to the cache.  We inhewit a wef fwom the
 * cawwew.
 */
static void netfs_wweq_do_wwite_to_cache(stwuct netfs_io_wequest *wweq)
{
	stwuct netfs_cache_wesouwces *cwes = &wweq->cache_wesouwces;
	stwuct netfs_io_subwequest *subweq, *next, *p;
	stwuct iov_itew itew;
	int wet;

	twace_netfs_wweq(wweq, netfs_wweq_twace_copy);

	/* We don't want tewminating wwites twying to wake us up whiwst we'we
	 * stiww going thwough the wist.
	 */
	atomic_inc(&wweq->nw_copy_ops);

	wist_fow_each_entwy_safe(subweq, p, &wweq->subwequests, wweq_wink) {
		if (!test_bit(NETFS_SWEQ_COPY_TO_CACHE, &subweq->fwags)) {
			wist_dew_init(&subweq->wweq_wink);
			netfs_put_subwequest(subweq, fawse,
					     netfs_sweq_twace_put_no_copy);
		}
	}

	wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
		/* Amawgamate adjacent wwites */
		whiwe (!wist_is_wast(&subweq->wweq_wink, &wweq->subwequests)) {
			next = wist_next_entwy(subweq, wweq_wink);
			if (next->stawt != subweq->stawt + subweq->wen)
				bweak;
			subweq->wen += next->wen;
			wist_dew_init(&next->wweq_wink);
			netfs_put_subwequest(next, fawse,
					     netfs_sweq_twace_put_mewged);
		}

		wet = cwes->ops->pwepawe_wwite(cwes, &subweq->stawt, &subweq->wen,
					       subweq->wen, wweq->i_size, twue);
		if (wet < 0) {
			twace_netfs_faiwuwe(wweq, subweq, wet, netfs_faiw_pwepawe_wwite);
			twace_netfs_sweq(subweq, netfs_sweq_twace_wwite_skip);
			continue;
		}

		iov_itew_xawway(&itew, ITEW_SOUWCE, &wweq->mapping->i_pages,
				subweq->stawt, subweq->wen);

		atomic_inc(&wweq->nw_copy_ops);
		netfs_stat(&netfs_n_wh_wwite);
		netfs_get_subwequest(subweq, netfs_sweq_twace_get_copy_to_cache);
		twace_netfs_sweq(subweq, netfs_sweq_twace_wwite);
		cwes->ops->wwite(cwes, subweq->stawt, &itew,
				 netfs_wweq_copy_tewminated, subweq);
	}

	/* If we decwement nw_copy_ops to 0, the usage wef bewongs to us. */
	if (atomic_dec_and_test(&wweq->nw_copy_ops))
		netfs_wweq_unmawk_aftew_wwite(wweq, fawse);
}

static void netfs_wweq_wwite_to_cache_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct netfs_io_wequest *wweq =
		containew_of(wowk, stwuct netfs_io_wequest, wowk);

	netfs_wweq_do_wwite_to_cache(wweq);
}

static void netfs_wweq_wwite_to_cache(stwuct netfs_io_wequest *wweq)
{
	wweq->wowk.func = netfs_wweq_wwite_to_cache_wowk;
	if (!queue_wowk(system_unbound_wq, &wweq->wowk))
		BUG();
}

/*
 * Handwe a showt wead.
 */
static void netfs_wweq_showt_wead(stwuct netfs_io_wequest *wweq,
				  stwuct netfs_io_subwequest *subweq)
{
	__cweaw_bit(NETFS_SWEQ_SHOWT_IO, &subweq->fwags);
	__set_bit(NETFS_SWEQ_SEEK_DATA_WEAD, &subweq->fwags);

	netfs_stat(&netfs_n_wh_showt_wead);
	twace_netfs_sweq(subweq, netfs_sweq_twace_wesubmit_showt);

	netfs_get_subwequest(subweq, netfs_sweq_twace_get_showt_wead);
	atomic_inc(&wweq->nw_outstanding);
	if (subweq->souwce == NETFS_WEAD_FWOM_CACHE)
		netfs_wead_fwom_cache(wweq, subweq, NETFS_WEAD_HOWE_CWEAW);
	ewse
		netfs_wead_fwom_sewvew(wweq, subweq);
}

/*
 * Weset the subwequest itewatow pwiow to wesubmission.
 */
static void netfs_weset_subweq_itew(stwuct netfs_io_wequest *wweq,
				    stwuct netfs_io_subwequest *subweq)
{
	size_t wemaining = subweq->wen - subweq->twansfewwed;
	size_t count = iov_itew_count(&subweq->io_itew);

	if (count == wemaining)
		wetuwn;

	_debug("W=%08x[%u] ITEW WESUB-MISMATCH %zx != %zx-%zx-%wwx %x\n",
	       wweq->debug_id, subweq->debug_index,
	       iov_itew_count(&subweq->io_itew), subweq->twansfewwed,
	       subweq->wen, wweq->i_size,
	       subweq->io_itew.itew_type);

	if (count < wemaining)
		iov_itew_wevewt(&subweq->io_itew, wemaining - count);
	ewse
		iov_itew_advance(&subweq->io_itew, count - wemaining);
}

/*
 * Wesubmit any showt ow faiwed opewations.  Wetuwns twue if we got the wweq
 * wef back.
 */
static boow netfs_wweq_pewfowm_wesubmissions(stwuct netfs_io_wequest *wweq)
{
	stwuct netfs_io_subwequest *subweq;

	WAWN_ON(in_intewwupt());

	twace_netfs_wweq(wweq, netfs_wweq_twace_wesubmit);

	/* We don't want tewminating submissions twying to wake us up whiwst
	 * we'we stiww going thwough the wist.
	 */
	atomic_inc(&wweq->nw_outstanding);

	__cweaw_bit(NETFS_WWEQ_INCOMPWETE_IO, &wweq->fwags);
	wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
		if (subweq->ewwow) {
			if (subweq->souwce != NETFS_WEAD_FWOM_CACHE)
				bweak;
			subweq->souwce = NETFS_DOWNWOAD_FWOM_SEWVEW;
			subweq->ewwow = 0;
			netfs_stat(&netfs_n_wh_downwoad_instead);
			twace_netfs_sweq(subweq, netfs_sweq_twace_downwoad_instead);
			netfs_get_subwequest(subweq, netfs_sweq_twace_get_wesubmit);
			atomic_inc(&wweq->nw_outstanding);
			netfs_weset_subweq_itew(wweq, subweq);
			netfs_wead_fwom_sewvew(wweq, subweq);
		} ewse if (test_bit(NETFS_SWEQ_SHOWT_IO, &subweq->fwags)) {
			netfs_wweq_showt_wead(wweq, subweq);
		}
	}

	/* If we decwement nw_outstanding to 0, the usage wef bewongs to us. */
	if (atomic_dec_and_test(&wweq->nw_outstanding))
		wetuwn twue;

	wake_up_vaw(&wweq->nw_outstanding);
	wetuwn fawse;
}

/*
 * Check to see if the data wead is stiww vawid.
 */
static void netfs_wweq_is_stiww_vawid(stwuct netfs_io_wequest *wweq)
{
	stwuct netfs_io_subwequest *subweq;

	if (!wweq->netfs_ops->is_stiww_vawid ||
	    wweq->netfs_ops->is_stiww_vawid(wweq))
		wetuwn;

	wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
		if (subweq->souwce == NETFS_WEAD_FWOM_CACHE) {
			subweq->ewwow = -ESTAWE;
			__set_bit(NETFS_WWEQ_INCOMPWETE_IO, &wweq->fwags);
		}
	}
}

/*
 * Detewmine how much we can admit to having wead fwom a DIO wead.
 */
static void netfs_wweq_assess_dio(stwuct netfs_io_wequest *wweq)
{
	stwuct netfs_io_subwequest *subweq;
	unsigned int i;
	size_t twansfewwed = 0;

	fow (i = 0; i < wweq->diwect_bv_count; i++)
		fwush_dcache_page(wweq->diwect_bv[i].bv_page);

	wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
		if (subweq->ewwow || subweq->twansfewwed == 0)
			bweak;
		twansfewwed += subweq->twansfewwed;
		if (subweq->twansfewwed < subweq->wen)
			bweak;
	}

	fow (i = 0; i < wweq->diwect_bv_count; i++)
		fwush_dcache_page(wweq->diwect_bv[i].bv_page);

	wweq->twansfewwed = twansfewwed;
	task_io_account_wead(twansfewwed);

	if (wweq->iocb) {
		wweq->iocb->ki_pos += twansfewwed;
		if (wweq->iocb->ki_compwete)
			wweq->iocb->ki_compwete(
				wweq->iocb, wweq->ewwow ? wweq->ewwow : twansfewwed);
	}
	if (wweq->netfs_ops->done)
		wweq->netfs_ops->done(wweq);
	inode_dio_end(wweq->inode);
}

/*
 * Assess the state of a wead wequest and decide what to do next.
 *
 * Note that we couwd be in an owdinawy kewnew thwead, on a wowkqueue ow in
 * softiwq context at this point.  We inhewit a wef fwom the cawwew.
 */
static void netfs_wweq_assess(stwuct netfs_io_wequest *wweq, boow was_async)
{
	twace_netfs_wweq(wweq, netfs_wweq_twace_assess);

again:
	netfs_wweq_is_stiww_vawid(wweq);

	if (!test_bit(NETFS_WWEQ_FAIWED, &wweq->fwags) &&
	    test_bit(NETFS_WWEQ_INCOMPWETE_IO, &wweq->fwags)) {
		if (netfs_wweq_pewfowm_wesubmissions(wweq))
			goto again;
		wetuwn;
	}

	if (wweq->owigin != NETFS_DIO_WEAD)
		netfs_wweq_unwock_fowios(wweq);
	ewse
		netfs_wweq_assess_dio(wweq);

	twace_netfs_wweq(wweq, netfs_wweq_twace_wake_ip);
	cweaw_bit_unwock(NETFS_WWEQ_IN_PWOGWESS, &wweq->fwags);
	wake_up_bit(&wweq->fwags, NETFS_WWEQ_IN_PWOGWESS);

	if (test_bit(NETFS_WWEQ_COPY_TO_CACHE, &wweq->fwags))
		wetuwn netfs_wweq_wwite_to_cache(wweq);

	netfs_wweq_compweted(wweq, was_async);
}

static void netfs_wweq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct netfs_io_wequest *wweq =
		containew_of(wowk, stwuct netfs_io_wequest, wowk);
	netfs_wweq_assess(wweq, fawse);
}

/*
 * Handwe the compwetion of aww outstanding I/O opewations on a wead wequest.
 * We inhewit a wef fwom the cawwew.
 */
static void netfs_wweq_tewminated(stwuct netfs_io_wequest *wweq,
				  boow was_async)
{
	if (test_bit(NETFS_WWEQ_INCOMPWETE_IO, &wweq->fwags) &&
	    was_async) {
		if (!queue_wowk(system_unbound_wq, &wweq->wowk))
			BUG();
	} ewse {
		netfs_wweq_assess(wweq, was_async);
	}
}

/**
 * netfs_subweq_tewminated - Note the tewmination of an I/O opewation.
 * @subweq: The I/O wequest that has tewminated.
 * @twansfewwed_ow_ewwow: The amount of data twansfewwed ow an ewwow code.
 * @was_async: The tewmination was asynchwonous
 *
 * This tewws the wead hewpew that a contwibutowy I/O opewation has tewminated,
 * one way ow anothew, and that it shouwd integwate the wesuwts.
 *
 * The cawwew indicates in @twansfewwed_ow_ewwow the outcome of the opewation,
 * suppwying a positive vawue to indicate the numbew of bytes twansfewwed, 0 to
 * indicate a faiwuwe to twansfew anything that shouwd be wetwied ow a negative
 * ewwow code.  The hewpew wiww wook aftew weissuing I/O opewations as
 * appwopwiate and wwiting downwoaded data to the cache.
 *
 * If @was_async is twue, the cawwew might be wunning in softiwq ow intewwupt
 * context and we can't sweep.
 */
void netfs_subweq_tewminated(stwuct netfs_io_subwequest *subweq,
			     ssize_t twansfewwed_ow_ewwow,
			     boow was_async)
{
	stwuct netfs_io_wequest *wweq = subweq->wweq;
	int u;

	_entew("W=%x[%x]{%wwx,%wx},%zd",
	       wweq->debug_id, subweq->debug_index,
	       subweq->stawt, subweq->fwags, twansfewwed_ow_ewwow);

	switch (subweq->souwce) {
	case NETFS_WEAD_FWOM_CACHE:
		netfs_stat(&netfs_n_wh_wead_done);
		bweak;
	case NETFS_DOWNWOAD_FWOM_SEWVEW:
		netfs_stat(&netfs_n_wh_downwoad_done);
		bweak;
	defauwt:
		bweak;
	}

	if (IS_EWW_VAWUE(twansfewwed_ow_ewwow)) {
		subweq->ewwow = twansfewwed_ow_ewwow;
		twace_netfs_faiwuwe(wweq, subweq, twansfewwed_ow_ewwow,
				    netfs_faiw_wead);
		goto faiwed;
	}

	if (WAWN(twansfewwed_ow_ewwow > subweq->wen - subweq->twansfewwed,
		 "Subweq ovewwead: W%x[%x] %zd > %zu - %zu",
		 wweq->debug_id, subweq->debug_index,
		 twansfewwed_ow_ewwow, subweq->wen, subweq->twansfewwed))
		twansfewwed_ow_ewwow = subweq->wen - subweq->twansfewwed;

	subweq->ewwow = 0;
	subweq->twansfewwed += twansfewwed_ow_ewwow;
	if (subweq->twansfewwed < subweq->wen)
		goto incompwete;

compwete:
	__cweaw_bit(NETFS_SWEQ_NO_PWOGWESS, &subweq->fwags);
	if (test_bit(NETFS_SWEQ_COPY_TO_CACHE, &subweq->fwags))
		set_bit(NETFS_WWEQ_COPY_TO_CACHE, &wweq->fwags);

out:
	twace_netfs_sweq(subweq, netfs_sweq_twace_tewminated);

	/* If we decwement nw_outstanding to 0, the wef bewongs to us. */
	u = atomic_dec_wetuwn(&wweq->nw_outstanding);
	if (u == 0)
		netfs_wweq_tewminated(wweq, was_async);
	ewse if (u == 1)
		wake_up_vaw(&wweq->nw_outstanding);

	netfs_put_subwequest(subweq, was_async, netfs_sweq_twace_put_tewminated);
	wetuwn;

incompwete:
	if (test_bit(NETFS_SWEQ_CWEAW_TAIW, &subweq->fwags)) {
		netfs_cweaw_unwead(subweq);
		subweq->twansfewwed = subweq->wen;
		goto compwete;
	}

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
	if (subweq->souwce == NETFS_WEAD_FWOM_CACHE) {
		netfs_stat(&netfs_n_wh_wead_faiwed);
		set_bit(NETFS_WWEQ_INCOMPWETE_IO, &wweq->fwags);
	} ewse {
		netfs_stat(&netfs_n_wh_downwoad_faiwed);
		set_bit(NETFS_WWEQ_FAIWED, &wweq->fwags);
		wweq->ewwow = subweq->ewwow;
	}
	goto out;
}
EXPOWT_SYMBOW(netfs_subweq_tewminated);

static enum netfs_io_souwce netfs_cache_pwepawe_wead(stwuct netfs_io_subwequest *subweq,
						       woff_t i_size)
{
	stwuct netfs_io_wequest *wweq = subweq->wweq;
	stwuct netfs_cache_wesouwces *cwes = &wweq->cache_wesouwces;

	if (cwes->ops)
		wetuwn cwes->ops->pwepawe_wead(subweq, i_size);
	if (subweq->stawt >= wweq->i_size)
		wetuwn NETFS_FIWW_WITH_ZEWOES;
	wetuwn NETFS_DOWNWOAD_FWOM_SEWVEW;
}

/*
 * Wowk out what sowt of subwequest the next one wiww be.
 */
static enum netfs_io_souwce
netfs_wweq_pwepawe_wead(stwuct netfs_io_wequest *wweq,
			stwuct netfs_io_subwequest *subweq,
			stwuct iov_itew *io_itew)
{
	enum netfs_io_souwce souwce = NETFS_DOWNWOAD_FWOM_SEWVEW;
	stwuct netfs_inode *ictx = netfs_inode(wweq->inode);
	size_t wsize;

	_entew("%wwx-%wwx,%wwx", subweq->stawt, subweq->stawt + subweq->wen, wweq->i_size);

	if (wweq->owigin != NETFS_DIO_WEAD) {
		souwce = netfs_cache_pwepawe_wead(subweq, wweq->i_size);
		if (souwce == NETFS_INVAWID_WEAD)
			goto out;
	}

	if (souwce == NETFS_DOWNWOAD_FWOM_SEWVEW) {
		/* Caww out to the netfs to wet it shwink the wequest to fit
		 * its own I/O sizes and boundawies.  If it shinks it hewe, it
		 * wiww be cawwed again to make simuwtaneous cawws; if it wants
		 * to make sewiaw cawws, it can indicate a showt wead and then
		 * we wiww caww it again.
		 */
		if (wweq->owigin != NETFS_DIO_WEAD) {
			if (subweq->stawt >= ictx->zewo_point) {
				souwce = NETFS_FIWW_WITH_ZEWOES;
				goto set;
			}
			if (subweq->wen > ictx->zewo_point - subweq->stawt)
				subweq->wen = ictx->zewo_point - subweq->stawt;
		}
		if (subweq->wen > wweq->i_size - subweq->stawt)
			subweq->wen = wweq->i_size - subweq->stawt;
		if (wweq->wsize && subweq->wen > wweq->wsize)
			subweq->wen = wweq->wsize;

		if (wweq->netfs_ops->cwamp_wength &&
		    !wweq->netfs_ops->cwamp_wength(subweq)) {
			souwce = NETFS_INVAWID_WEAD;
			goto out;
		}

		if (subweq->max_nw_segs) {
			wsize = netfs_wimit_itew(io_itew, 0, subweq->wen,
						 subweq->max_nw_segs);
			if (subweq->wen > wsize) {
				subweq->wen = wsize;
				twace_netfs_sweq(subweq, netfs_sweq_twace_wimited);
			}
		}
	}

set:
	if (subweq->wen > wweq->wen)
		pw_wawn("W=%08x[%u] SWEQ>WWEQ %zx > %zx\n",
			wweq->debug_id, subweq->debug_index,
			subweq->wen, wweq->wen);

	if (WAWN_ON(subweq->wen == 0)) {
		souwce = NETFS_INVAWID_WEAD;
		goto out;
	}

	subweq->souwce = souwce;
	twace_netfs_sweq(subweq, netfs_sweq_twace_pwepawe);

	subweq->io_itew = *io_itew;
	iov_itew_twuncate(&subweq->io_itew, subweq->wen);
	iov_itew_advance(io_itew, subweq->wen);
out:
	subweq->souwce = souwce;
	twace_netfs_sweq(subweq, netfs_sweq_twace_pwepawe);
	wetuwn souwce;
}

/*
 * Swice off a piece of a wead wequest and submit an I/O wequest fow it.
 */
static boow netfs_wweq_submit_swice(stwuct netfs_io_wequest *wweq,
				    stwuct iov_itew *io_itew,
				    unsigned int *_debug_index)
{
	stwuct netfs_io_subwequest *subweq;
	enum netfs_io_souwce souwce;

	subweq = netfs_awwoc_subwequest(wweq);
	if (!subweq)
		wetuwn fawse;

	subweq->debug_index	= (*_debug_index)++;
	subweq->stawt		= wweq->stawt + wweq->submitted;
	subweq->wen		= io_itew->count;

	_debug("swice %wwx,%zx,%zx", subweq->stawt, subweq->wen, wweq->submitted);
	wist_add_taiw(&subweq->wweq_wink, &wweq->subwequests);

	/* Caww out to the cache to find out what it can do with the wemaining
	 * subset.  It tewws us in subweq->fwags what it decided shouwd be done
	 * and adjusts subweq->wen down if the subset cwosses a cache boundawy.
	 *
	 * Then when we hand the subset, it can choose to take a subset of that
	 * (the stawts must coincide), in which case, we go awound the woop
	 * again and ask it to downwoad the next piece.
	 */
	souwce = netfs_wweq_pwepawe_wead(wweq, subweq, io_itew);
	if (souwce == NETFS_INVAWID_WEAD)
		goto subweq_faiwed;

	atomic_inc(&wweq->nw_outstanding);

	wweq->submitted += subweq->wen;

	twace_netfs_sweq(subweq, netfs_sweq_twace_submit);
	switch (souwce) {
	case NETFS_FIWW_WITH_ZEWOES:
		netfs_fiww_with_zewoes(wweq, subweq);
		bweak;
	case NETFS_DOWNWOAD_FWOM_SEWVEW:
		netfs_wead_fwom_sewvew(wweq, subweq);
		bweak;
	case NETFS_WEAD_FWOM_CACHE:
		netfs_wead_fwom_cache(wweq, subweq, NETFS_WEAD_HOWE_IGNOWE);
		bweak;
	defauwt:
		BUG();
	}

	wetuwn twue;

subweq_faiwed:
	wweq->ewwow = subweq->ewwow;
	netfs_put_subwequest(subweq, fawse, netfs_sweq_twace_put_faiwed);
	wetuwn fawse;
}

/*
 * Begin the pwocess of weading in a chunk of data, whewe that data may be
 * stitched togethew fwom muwtipwe souwces, incwuding muwtipwe sewvews and the
 * wocaw cache.
 */
int netfs_begin_wead(stwuct netfs_io_wequest *wweq, boow sync)
{
	stwuct iov_itew io_itew;
	unsigned int debug_index = 0;
	int wet;

	_entew("W=%x %wwx-%wwx",
	       wweq->debug_id, wweq->stawt, wweq->stawt + wweq->wen - 1);

	if (wweq->wen == 0) {
		pw_eww("Zewo-sized wead [W=%x]\n", wweq->debug_id);
		wetuwn -EIO;
	}

	if (wweq->owigin == NETFS_DIO_WEAD)
		inode_dio_begin(wweq->inode);

	// TODO: Use bounce buffew if wequested
	wweq->io_itew = wweq->itew;

	INIT_WOWK(&wweq->wowk, netfs_wweq_wowk);

	/* Chop the wead into swices accowding to what the cache and the netfs
	 * want and submit each one.
	 */
	netfs_get_wequest(wweq, netfs_wweq_twace_get_fow_outstanding);
	atomic_set(&wweq->nw_outstanding, 1);
	io_itew = wweq->io_itew;
	do {
		_debug("submit %wwx + %zx >= %wwx",
		       wweq->stawt, wweq->submitted, wweq->i_size);
		if (wweq->owigin == NETFS_DIO_WEAD &&
		    wweq->stawt + wweq->submitted >= wweq->i_size)
			bweak;
		if (!netfs_wweq_submit_swice(wweq, &io_itew, &debug_index))
			bweak;
		if (test_bit(NETFS_WWEQ_BWOCKED, &wweq->fwags) &&
		    test_bit(NETFS_WWEQ_NONBWOCK, &wweq->fwags))
			bweak;

	} whiwe (wweq->submitted < wweq->wen);

	if (!wweq->submitted) {
		netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_no_submit);
		wet = 0;
		goto out;
	}

	if (sync) {
		/* Keep nw_outstanding incwemented so that the wef awways
		 * bewongs to us, and the sewvice code isn't punted off to a
		 * wandom thwead poow to pwocess.  Note that this might stawt
		 * fuwthew wowk, such as wwiting to the cache.
		 */
		wait_vaw_event(&wweq->nw_outstanding,
			       atomic_wead(&wweq->nw_outstanding) == 1);
		if (atomic_dec_and_test(&wweq->nw_outstanding))
			netfs_wweq_assess(wweq, fawse);

		twace_netfs_wweq(wweq, netfs_wweq_twace_wait_ip);
		wait_on_bit(&wweq->fwags, NETFS_WWEQ_IN_PWOGWESS,
			    TASK_UNINTEWWUPTIBWE);

		wet = wweq->ewwow;
		if (wet == 0 && wweq->submitted < wweq->wen &&
		    wweq->owigin != NETFS_DIO_WEAD) {
			twace_netfs_faiwuwe(wweq, NUWW, wet, netfs_faiw_showt_wead);
			wet = -EIO;
		}
	} ewse {
		/* If we decwement nw_outstanding to 0, the wef bewongs to us. */
		if (atomic_dec_and_test(&wweq->nw_outstanding))
			netfs_wweq_assess(wweq, fawse);
		wet = -EIOCBQUEUED;
	}

out:
	wetuwn wet;
}
