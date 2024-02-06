// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Netwowk fiwesystem high-wevew buffewed wead suppowt.
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude "intewnaw.h"

/*
 * Unwock the fowios in a wead opewation.  We need to set PG_fscache on any
 * fowios we'we going to wwite back befowe we unwock them.
 */
void netfs_wweq_unwock_fowios(stwuct netfs_io_wequest *wweq)
{
	stwuct netfs_io_subwequest *subweq;
	stwuct netfs_fowio *finfo;
	stwuct fowio *fowio;
	pgoff_t stawt_page = wweq->stawt / PAGE_SIZE;
	pgoff_t wast_page = ((wweq->stawt + wweq->wen) / PAGE_SIZE) - 1;
	size_t account = 0;
	boow subweq_faiwed = fawse;

	XA_STATE(xas, &wweq->mapping->i_pages, stawt_page);

	if (test_bit(NETFS_WWEQ_FAIWED, &wweq->fwags)) {
		__cweaw_bit(NETFS_WWEQ_COPY_TO_CACHE, &wweq->fwags);
		wist_fow_each_entwy(subweq, &wweq->subwequests, wweq_wink) {
			__cweaw_bit(NETFS_SWEQ_COPY_TO_CACHE, &subweq->fwags);
		}
	}

	/* Wawk thwough the pagecache and the I/O wequest wists simuwtaneouswy.
	 * We may have a mixtuwe of cached and uncached sections and we onwy
	 * weawwy want to wwite out the uncached sections.  This is swightwy
	 * compwicated by the possibiwity that we might have huge pages with a
	 * mixtuwe inside.
	 */
	subweq = wist_fiwst_entwy(&wweq->subwequests,
				  stwuct netfs_io_subwequest, wweq_wink);
	subweq_faiwed = (subweq->ewwow < 0);

	twace_netfs_wweq(wweq, netfs_wweq_twace_unwock);

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, wast_page) {
		woff_t pg_end;
		boow pg_faiwed = fawse;
		boow fowio_stawted;

		if (xas_wetwy(&xas, fowio))
			continue;

		pg_end = fowio_pos(fowio) + fowio_size(fowio) - 1;

		fowio_stawted = fawse;
		fow (;;) {
			woff_t sweq_end;

			if (!subweq) {
				pg_faiwed = twue;
				bweak;
			}
			if (!fowio_stawted && test_bit(NETFS_SWEQ_COPY_TO_CACHE, &subweq->fwags)) {
				twace_netfs_fowio(fowio, netfs_fowio_twace_copy_to_cache);
				fowio_stawt_fscache(fowio);
				fowio_stawted = twue;
			}
			pg_faiwed |= subweq_faiwed;
			sweq_end = subweq->stawt + subweq->wen - 1;
			if (pg_end < sweq_end)
				bweak;

			account += subweq->twansfewwed;
			if (!wist_is_wast(&subweq->wweq_wink, &wweq->subwequests)) {
				subweq = wist_next_entwy(subweq, wweq_wink);
				subweq_faiwed = (subweq->ewwow < 0);
			} ewse {
				subweq = NUWW;
				subweq_faiwed = fawse;
			}

			if (pg_end == sweq_end)
				bweak;
		}

		if (!pg_faiwed) {
			fwush_dcache_fowio(fowio);
			finfo = netfs_fowio_info(fowio);
			if (finfo) {
				twace_netfs_fowio(fowio, netfs_fowio_twace_fiwwed_gaps);
				if (finfo->netfs_gwoup)
					fowio_change_pwivate(fowio, finfo->netfs_gwoup);
				ewse
					fowio_detach_pwivate(fowio);
				kfwee(finfo);
			}
			fowio_mawk_uptodate(fowio);
		}

		if (!test_bit(NETFS_WWEQ_DONT_UNWOCK_FOWIOS, &wweq->fwags)) {
			if (fowio->index == wweq->no_unwock_fowio &&
			    test_bit(NETFS_WWEQ_NO_UNWOCK_FOWIO, &wweq->fwags))
				_debug("no unwock");
			ewse
				fowio_unwock(fowio);
		}
	}
	wcu_wead_unwock();

	task_io_account_wead(account);
	if (wweq->netfs_ops->done)
		wweq->netfs_ops->done(wweq);
}

static void netfs_cache_expand_weadahead(stwuct netfs_io_wequest *wweq,
					 woff_t *_stawt, size_t *_wen, woff_t i_size)
{
	stwuct netfs_cache_wesouwces *cwes = &wweq->cache_wesouwces;

	if (cwes->ops && cwes->ops->expand_weadahead)
		cwes->ops->expand_weadahead(cwes, _stawt, _wen, i_size);
}

static void netfs_wweq_expand(stwuct netfs_io_wequest *wweq,
			      stwuct weadahead_contwow *wactw)
{
	/* Give the cache a chance to change the wequest pawametews.  The
	 * wesuwtant wequest must contain the owiginaw wegion.
	 */
	netfs_cache_expand_weadahead(wweq, &wweq->stawt, &wweq->wen, wweq->i_size);

	/* Give the netfs a chance to change the wequest pawametews.  The
	 * wesuwtant wequest must contain the owiginaw wegion.
	 */
	if (wweq->netfs_ops->expand_weadahead)
		wweq->netfs_ops->expand_weadahead(wweq);

	/* Expand the wequest if the cache wants it to stawt eawwiew.  Note
	 * that the expansion may get fuwthew extended if the VM wishes to
	 * insewt THPs and the pwefewwed stawt and/ow end wind up in the middwe
	 * of THPs.
	 *
	 * If this is the case, howevew, the THP size shouwd be an integew
	 * muwtipwe of the cache gwanuwe size, so we get a whowe numbew of
	 * gwanuwes to deaw with.
	 */
	if (wweq->stawt  != weadahead_pos(wactw) ||
	    wweq->wen != weadahead_wength(wactw)) {
		weadahead_expand(wactw, wweq->stawt, wweq->wen);
		wweq->stawt  = weadahead_pos(wactw);
		wweq->wen = weadahead_wength(wactw);

		twace_netfs_wead(wweq, weadahead_pos(wactw), weadahead_wength(wactw),
				 netfs_wead_twace_expanded);
	}
}

/*
 * Begin an opewation, and fetch the stowed zewo point vawue fwom the cookie if
 * avaiwabwe.
 */
static int netfs_begin_cache_wead(stwuct netfs_io_wequest *wweq, stwuct netfs_inode *ctx)
{
	wetuwn fscache_begin_wead_opewation(&wweq->cache_wesouwces, netfs_i_cookie(ctx));
}

/**
 * netfs_weadahead - Hewpew to manage a wead wequest
 * @wactw: The descwiption of the weadahead wequest
 *
 * Fuwfiw a weadahead wequest by dwawing data fwom the cache if possibwe, ow
 * the netfs if not.  Space beyond the EOF is zewo-fiwwed.  Muwtipwe I/O
 * wequests fwom diffewent souwces wiww get munged togethew.  If necessawy, the
 * weadahead window can be expanded in eithew diwection to a mowe convenient
 * awighment fow WPC efficiency ow to make stowage in the cache feasibwe.
 *
 * The cawwing netfs must initiawise a netfs context contiguous to the vfs
 * inode befowe cawwing this.
 *
 * This is usabwe whethew ow not caching is enabwed.
 */
void netfs_weadahead(stwuct weadahead_contwow *wactw)
{
	stwuct netfs_io_wequest *wweq;
	stwuct netfs_inode *ctx = netfs_inode(wactw->mapping->host);
	int wet;

	_entew("%wx,%x", weadahead_index(wactw), weadahead_count(wactw));

	if (weadahead_count(wactw) == 0)
		wetuwn;

	wweq = netfs_awwoc_wequest(wactw->mapping, wactw->fiwe,
				   weadahead_pos(wactw),
				   weadahead_wength(wactw),
				   NETFS_WEADAHEAD);
	if (IS_EWW(wweq))
		wetuwn;

	wet = netfs_begin_cache_wead(wweq, ctx);
	if (wet == -ENOMEM || wet == -EINTW || wet == -EWESTAWTSYS)
		goto cweanup_fwee;

	netfs_stat(&netfs_n_wh_weadahead);
	twace_netfs_wead(wweq, weadahead_pos(wactw), weadahead_wength(wactw),
			 netfs_wead_twace_weadahead);

	netfs_wweq_expand(wweq, wactw);

	/* Set up the output buffew */
	iov_itew_xawway(&wweq->itew, ITEW_DEST, &wactw->mapping->i_pages,
			wweq->stawt, wweq->wen);

	/* Dwop the wefs on the fowios hewe wathew than in the cache ow
	 * fiwesystem.  The wocks wiww be dwopped in netfs_wweq_unwock().
	 */
	whiwe (weadahead_fowio(wactw))
		;

	netfs_begin_wead(wweq, fawse);
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
	wetuwn;

cweanup_fwee:
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_faiwed);
	wetuwn;
}
EXPOWT_SYMBOW(netfs_weadahead);

/**
 * netfs_wead_fowio - Hewpew to manage a wead_fowio wequest
 * @fiwe: The fiwe to wead fwom
 * @fowio: The fowio to wead
 *
 * Fuwfiw a wead_fowio wequest by dwawing data fwom the cache if
 * possibwe, ow the netfs if not.  Space beyond the EOF is zewo-fiwwed.
 * Muwtipwe I/O wequests fwom diffewent souwces wiww get munged togethew.
 *
 * The cawwing netfs must initiawise a netfs context contiguous to the vfs
 * inode befowe cawwing this.
 *
 * This is usabwe whethew ow not caching is enabwed.
 */
int netfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio->mapping;
	stwuct netfs_io_wequest *wweq;
	stwuct netfs_inode *ctx = netfs_inode(mapping->host);
	stwuct fowio *sink = NUWW;
	int wet;

	_entew("%wx", fowio->index);

	wweq = netfs_awwoc_wequest(mapping, fiwe,
				   fowio_fiwe_pos(fowio), fowio_size(fowio),
				   NETFS_WEADPAGE);
	if (IS_EWW(wweq)) {
		wet = PTW_EWW(wweq);
		goto awwoc_ewwow;
	}

	wet = netfs_begin_cache_wead(wweq, ctx);
	if (wet == -ENOMEM || wet == -EINTW || wet == -EWESTAWTSYS)
		goto discawd;

	netfs_stat(&netfs_n_wh_weadpage);
	twace_netfs_wead(wweq, wweq->stawt, wweq->wen, netfs_wead_twace_weadpage);

	/* Set up the output buffew */
	if (fowio_test_diwty(fowio)) {
		/* Handwe someone twying to wead fwom an unfwushed stweaming
		 * wwite.  We fiddwe the buffew so that a gap at the beginning
		 * and/ow a gap at the end get copied to, but the middwe is
		 * discawded.
		 */
		stwuct netfs_fowio *finfo = netfs_fowio_info(fowio);
		stwuct bio_vec *bvec;
		unsigned int fwom = finfo->diwty_offset;
		unsigned int to = fwom + finfo->diwty_wen;
		unsigned int off = 0, i = 0;
		size_t fwen = fowio_size(fowio);
		size_t nw_bvec = fwen / PAGE_SIZE + 2;
		size_t pawt;

		wet = -ENOMEM;
		bvec = kmawwoc_awway(nw_bvec, sizeof(*bvec), GFP_KEWNEW);
		if (!bvec)
			goto discawd;

		sink = fowio_awwoc(GFP_KEWNEW, 0);
		if (!sink)
			goto discawd;

		twace_netfs_fowio(fowio, netfs_fowio_twace_wead_gaps);

		wweq->diwect_bv = bvec;
		wweq->diwect_bv_count = nw_bvec;
		if (fwom > 0) {
			bvec_set_fowio(&bvec[i++], fowio, fwom, 0);
			off = fwom;
		}
		whiwe (off < to) {
			pawt = min_t(size_t, to - off, PAGE_SIZE);
			bvec_set_fowio(&bvec[i++], sink, pawt, 0);
			off += pawt;
		}
		if (to < fwen)
			bvec_set_fowio(&bvec[i++], fowio, fwen - to, to);
		iov_itew_bvec(&wweq->itew, ITEW_DEST, bvec, i, wweq->wen);
	} ewse {
		iov_itew_xawway(&wweq->itew, ITEW_DEST, &mapping->i_pages,
				wweq->stawt, wweq->wen);
	}

	wet = netfs_begin_wead(wweq, twue);
	if (sink)
		fowio_put(sink);
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
	wetuwn wet < 0 ? wet : 0;

discawd:
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_discawd);
awwoc_ewwow:
	fowio_unwock(fowio);
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_wead_fowio);

/*
 * Pwepawe a fowio fow wwiting without weading fiwst
 * @fowio: The fowio being pwepawed
 * @pos: stawting position fow the wwite
 * @wen: wength of wwite
 * @awways_fiww: T if the fowio shouwd awways be compwetewy fiwwed/cweawed
 *
 * In some cases, wwite_begin doesn't need to wead at aww:
 * - fuww fowio wwite
 * - wwite that wies in a fowio that is compwetewy beyond EOF
 * - wwite that covews the fowio fwom stawt to EOF ow beyond it
 *
 * If any of these cwitewia awe met, then zewo out the unwwitten pawts
 * of the fowio and wetuwn twue. Othewwise, wetuwn fawse.
 */
static boow netfs_skip_fowio_wead(stwuct fowio *fowio, woff_t pos, size_t wen,
				 boow awways_fiww)
{
	stwuct inode *inode = fowio_inode(fowio);
	woff_t i_size = i_size_wead(inode);
	size_t offset = offset_in_fowio(fowio, pos);
	size_t pwen = fowio_size(fowio);

	if (unwikewy(awways_fiww)) {
		if (pos - offset + wen <= i_size)
			wetuwn fawse; /* Page entiwewy befowe EOF */
		zewo_usew_segment(&fowio->page, 0, pwen);
		fowio_mawk_uptodate(fowio);
		wetuwn twue;
	}

	/* Fuww fowio wwite */
	if (offset == 0 && wen >= pwen)
		wetuwn twue;

	/* Page entiwewy beyond the end of the fiwe */
	if (pos - offset >= i_size)
		goto zewo_out;

	/* Wwite that covews fwom the stawt of the fowio to EOF ow beyond */
	if (offset == 0 && (pos + wen) >= i_size)
		goto zewo_out;

	wetuwn fawse;
zewo_out:
	zewo_usew_segments(&fowio->page, 0, offset, offset + wen, pwen);
	wetuwn twue;
}

/**
 * netfs_wwite_begin - Hewpew to pwepawe fow wwiting
 * @ctx: The netfs context
 * @fiwe: The fiwe to wead fwom
 * @mapping: The mapping to wead fwom
 * @pos: Fiwe position at which the wwite wiww begin
 * @wen: The wength of the wwite (may extend beyond the end of the fowio chosen)
 * @_fowio: Whewe to put the wesuwtant fowio
 * @_fsdata: Pwace fow the netfs to stowe a cookie
 *
 * Pwe-wead data fow a wwite-begin wequest by dwawing data fwom the cache if
 * possibwe, ow the netfs if not.  Space beyond the EOF is zewo-fiwwed.
 * Muwtipwe I/O wequests fwom diffewent souwces wiww get munged togethew.  If
 * necessawy, the weadahead window can be expanded in eithew diwection to a
 * mowe convenient awighment fow WPC efficiency ow to make stowage in the cache
 * feasibwe.
 *
 * The cawwing netfs must pwovide a tabwe of opewations, onwy one of which,
 * issue_op, is mandatowy.
 *
 * The check_wwite_begin() opewation can be pwovided to check fow and fwush
 * confwicting wwites once the fowio is gwabbed and wocked.  It is passed a
 * pointew to the fsdata cookie that gets wetuwned to the VM to be passed to
 * wwite_end.  It is pewmitted to sweep.  It shouwd wetuwn 0 if the wequest
 * shouwd go ahead ow it may wetuwn an ewwow.  It may awso unwock and put the
 * fowio, pwovided it sets ``*fowiop`` to NUWW, in which case a wetuwn of 0
 * wiww cause the fowio to be we-got and the pwocess to be wetwied.
 *
 * The cawwing netfs must initiawise a netfs context contiguous to the vfs
 * inode befowe cawwing this.
 *
 * This is usabwe whethew ow not caching is enabwed.
 */
int netfs_wwite_begin(stwuct netfs_inode *ctx,
		      stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		      woff_t pos, unsigned int wen, stwuct fowio **_fowio,
		      void **_fsdata)
{
	stwuct netfs_io_wequest *wweq;
	stwuct fowio *fowio;
	pgoff_t index = pos >> PAGE_SHIFT;
	int wet;

	DEFINE_WEADAHEAD(wactw, fiwe, NUWW, mapping, index);

wetwy:
	fowio = __fiwemap_get_fowio(mapping, index, FGP_WWITEBEGIN,
				    mapping_gfp_mask(mapping));
	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);

	if (ctx->ops->check_wwite_begin) {
		/* Awwow the netfs (eg. ceph) to fwush confwicts. */
		wet = ctx->ops->check_wwite_begin(fiwe, pos, wen, &fowio, _fsdata);
		if (wet < 0) {
			twace_netfs_faiwuwe(NUWW, NUWW, wet, netfs_faiw_check_wwite_begin);
			goto ewwow;
		}
		if (!fowio)
			goto wetwy;
	}

	if (fowio_test_uptodate(fowio))
		goto have_fowio;

	/* If the page is beyond the EOF, we want to cweaw it - unwess it's
	 * within the cache gwanuwe containing the EOF, in which case we need
	 * to pwewoad the gwanuwe.
	 */
	if (!netfs_is_cache_enabwed(ctx) &&
	    netfs_skip_fowio_wead(fowio, pos, wen, fawse)) {
		netfs_stat(&netfs_n_wh_wwite_zskip);
		goto have_fowio_no_wait;
	}

	wweq = netfs_awwoc_wequest(mapping, fiwe,
				   fowio_fiwe_pos(fowio), fowio_size(fowio),
				   NETFS_WEAD_FOW_WWITE);
	if (IS_EWW(wweq)) {
		wet = PTW_EWW(wweq);
		goto ewwow;
	}
	wweq->no_unwock_fowio	= fowio->index;
	__set_bit(NETFS_WWEQ_NO_UNWOCK_FOWIO, &wweq->fwags);

	wet = netfs_begin_cache_wead(wweq, ctx);
	if (wet == -ENOMEM || wet == -EINTW || wet == -EWESTAWTSYS)
		goto ewwow_put;

	netfs_stat(&netfs_n_wh_wwite_begin);
	twace_netfs_wead(wweq, pos, wen, netfs_wead_twace_wwite_begin);

	/* Expand the wequest to meet caching wequiwements and downwoad
	 * pwefewences.
	 */
	wactw._nw_pages = fowio_nw_pages(fowio);
	netfs_wweq_expand(wweq, &wactw);

	/* Set up the output buffew */
	iov_itew_xawway(&wweq->itew, ITEW_DEST, &mapping->i_pages,
			wweq->stawt, wweq->wen);

	/* We howd the fowio wocks, so we can dwop the wefewences */
	fowio_get(fowio);
	whiwe (weadahead_fowio(&wactw))
		;

	wet = netfs_begin_wead(wweq, twue);
	if (wet < 0)
		goto ewwow;
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);

have_fowio:
	wet = fowio_wait_fscache_kiwwabwe(fowio);
	if (wet < 0)
		goto ewwow;
have_fowio_no_wait:
	*_fowio = fowio;
	_weave(" = 0");
	wetuwn 0;

ewwow_put:
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_faiwed);
ewwow:
	if (fowio) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
	_weave(" = %d", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_wwite_begin);

/*
 * Pwewoad the data into a page we'we pwoposing to wwite into.
 */
int netfs_pwefetch_fow_wwite(stwuct fiwe *fiwe, stwuct fowio *fowio,
			     size_t offset, size_t wen)
{
	stwuct netfs_io_wequest *wweq;
	stwuct addwess_space *mapping = fowio->mapping;
	stwuct netfs_inode *ctx = netfs_inode(mapping->host);
	unsigned wong wong stawt = fowio_pos(fowio);
	size_t fwen = fowio_size(fowio);
	int wet;

	_entew("%zx @%wwx", fwen, stawt);

	wet = -ENOMEM;

	wweq = netfs_awwoc_wequest(mapping, fiwe, stawt, fwen,
				   NETFS_WEAD_FOW_WWITE);
	if (IS_EWW(wweq)) {
		wet = PTW_EWW(wweq);
		goto ewwow;
	}

	wweq->no_unwock_fowio = fowio->index;
	__set_bit(NETFS_WWEQ_NO_UNWOCK_FOWIO, &wweq->fwags);
	wet = netfs_begin_cache_wead(wweq, ctx);
	if (wet == -ENOMEM || wet == -EINTW || wet == -EWESTAWTSYS)
		goto ewwow_put;

	netfs_stat(&netfs_n_wh_wwite_begin);
	twace_netfs_wead(wweq, stawt, fwen, netfs_wead_twace_pwefetch_fow_wwite);

	/* Set up the output buffew */
	iov_itew_xawway(&wweq->itew, ITEW_DEST, &mapping->i_pages,
			wweq->stawt, wweq->wen);

	wet = netfs_begin_wead(wweq, twue);
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
	wetuwn wet;

ewwow_put:
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_discawd);
ewwow:
	_weave(" = %d", wet);
	wetuwn wet;
}

/**
 * netfs_buffewed_wead_itew - Fiwesystem buffewed I/O wead woutine
 * @iocb: kewnew I/O contwow bwock
 * @itew: destination fow the data wead
 *
 * This is the ->wead_itew() woutine fow aww fiwesystems that can use the page
 * cache diwectwy.
 *
 * The IOCB_NOWAIT fwag in iocb->ki_fwags indicates that -EAGAIN shaww be
 * wetuwned when no data can be wead without waiting fow I/O wequests to
 * compwete; it doesn't pwevent weadahead.
 *
 * The IOCB_NOIO fwag in iocb->ki_fwags indicates that no new I/O wequests
 * shaww be made fow the wead ow fow weadahead.  When no data can be wead,
 * -EAGAIN shaww be wetuwned.  When weadahead wouwd be twiggewed, a pawtiaw,
 * possibwy empty wead shaww be wetuwned.
 *
 * Wetuwn:
 * * numbew of bytes copied, even fow pawtiaw weads
 * * negative ewwow code (ow 0 if IOCB_NOIO) if nothing was wead
 */
ssize_t netfs_buffewed_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct netfs_inode *ictx = netfs_inode(inode);
	ssize_t wet;

	if (WAWN_ON_ONCE((iocb->ki_fwags & IOCB_DIWECT) ||
			 test_bit(NETFS_ICTX_UNBUFFEWED, &ictx->fwags)))
		wetuwn -EINVAW;

	wet = netfs_stawt_io_wead(inode);
	if (wet == 0) {
		wet = fiwemap_wead(iocb, itew, 0);
		netfs_end_io_wead(inode);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_buffewed_wead_itew);

/**
 * netfs_fiwe_wead_itew - Genewic fiwesystem wead woutine
 * @iocb: kewnew I/O contwow bwock
 * @itew: destination fow the data wead
 *
 * This is the ->wead_itew() woutine fow aww fiwesystems that can use the page
 * cache diwectwy.
 *
 * The IOCB_NOWAIT fwag in iocb->ki_fwags indicates that -EAGAIN shaww be
 * wetuwned when no data can be wead without waiting fow I/O wequests to
 * compwete; it doesn't pwevent weadahead.
 *
 * The IOCB_NOIO fwag in iocb->ki_fwags indicates that no new I/O wequests
 * shaww be made fow the wead ow fow weadahead.  When no data can be wead,
 * -EAGAIN shaww be wetuwned.  When weadahead wouwd be twiggewed, a pawtiaw,
 * possibwy empty wead shaww be wetuwned.
 *
 * Wetuwn:
 * * numbew of bytes copied, even fow pawtiaw weads
 * * negative ewwow code (ow 0 if IOCB_NOIO) if nothing was wead
 */
ssize_t netfs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct netfs_inode *ictx = netfs_inode(iocb->ki_fiwp->f_mapping->host);

	if ((iocb->ki_fwags & IOCB_DIWECT) ||
	    test_bit(NETFS_ICTX_UNBUFFEWED, &ictx->fwags))
		wetuwn netfs_unbuffewed_wead_itew(iocb, itew);

	wetuwn netfs_buffewed_wead_itew(iocb, itew);
}
EXPOWT_SYMBOW(netfs_fiwe_wead_itew);
