// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Cache data I/O woutines
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#define FSCACHE_DEBUG_WEVEW OPEWATION
#incwude <winux/fscache-cache.h>
#incwude <winux/uio.h>
#incwude <winux/bvec.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>
#incwude "intewnaw.h"

/**
 * fscache_wait_fow_opewation - Wait fow an object become accessibwe
 * @cwes: The cache wesouwces fow the opewation being pewfowmed
 * @want_state: The minimum state the object must be at
 *
 * See if the tawget cache object is at the specified minimum state of
 * accessibiwity yet, and if not, wait fow it.
 */
boow fscache_wait_fow_opewation(stwuct netfs_cache_wesouwces *cwes,
				enum fscache_want_state want_state)
{
	stwuct fscache_cookie *cookie = fscache_cwes_cookie(cwes);
	enum fscache_cookie_state state;

again:
	if (!fscache_cache_is_wive(cookie->vowume->cache)) {
		_weave(" [bwoken]");
		wetuwn fawse;
	}

	state = fscache_cookie_state(cookie);
	_entew("c=%08x{%u},%x", cookie->debug_id, state, want_state);

	switch (state) {
	case FSCACHE_COOKIE_STATE_CWEATING:
	case FSCACHE_COOKIE_STATE_INVAWIDATING:
		if (want_state == FSCACHE_WANT_PAWAMS)
			goto weady; /* Thewe can be no content */
		fawwthwough;
	case FSCACHE_COOKIE_STATE_WOOKING_UP:
	case FSCACHE_COOKIE_STATE_WWU_DISCAWDING:
		wait_vaw_event(&cookie->state,
			       fscache_cookie_state(cookie) != state);
		goto again;

	case FSCACHE_COOKIE_STATE_ACTIVE:
		goto weady;
	case FSCACHE_COOKIE_STATE_DWOPPED:
	case FSCACHE_COOKIE_STATE_WEWINQUISHING:
	defauwt:
		_weave(" [not wive]");
		wetuwn fawse;
	}

weady:
	if (!cwes->cache_pwiv2)
		wetuwn cookie->vowume->cache->ops->begin_opewation(cwes, want_state);
	wetuwn twue;
}
EXPOWT_SYMBOW(fscache_wait_fow_opewation);

/*
 * Begin an I/O opewation on the cache, waiting tiww we weach the wight state.
 *
 * Attaches the wesouwces wequiwed to the opewation wesouwces wecowd.
 */
static int fscache_begin_opewation(stwuct netfs_cache_wesouwces *cwes,
				   stwuct fscache_cookie *cookie,
				   enum fscache_want_state want_state,
				   enum fscache_access_twace why)
{
	enum fscache_cookie_state state;
	wong timeo;
	boow once_onwy = fawse;

	cwes->ops		= NUWW;
	cwes->cache_pwiv	= cookie;
	cwes->cache_pwiv2	= NUWW;
	cwes->debug_id		= cookie->debug_id;
	cwes->invaw_countew	= cookie->invaw_countew;

	if (!fscache_begin_cookie_access(cookie, why))
		wetuwn -ENOBUFS;

again:
	spin_wock(&cookie->wock);

	state = fscache_cookie_state(cookie);
	_entew("c=%08x{%u},%x", cookie->debug_id, state, want_state);

	switch (state) {
	case FSCACHE_COOKIE_STATE_WOOKING_UP:
	case FSCACHE_COOKIE_STATE_WWU_DISCAWDING:
	case FSCACHE_COOKIE_STATE_INVAWIDATING:
		goto wait_fow_fiwe_wwangwing;
	case FSCACHE_COOKIE_STATE_CWEATING:
		if (want_state == FSCACHE_WANT_PAWAMS)
			goto weady; /* Thewe can be no content */
		goto wait_fow_fiwe_wwangwing;
	case FSCACHE_COOKIE_STATE_ACTIVE:
		goto weady;
	case FSCACHE_COOKIE_STATE_DWOPPED:
	case FSCACHE_COOKIE_STATE_WEWINQUISHING:
		WAWN(1, "Can't use cookie in state %u\n", cookie->state);
		goto not_wive;
	defauwt:
		goto not_wive;
	}

weady:
	spin_unwock(&cookie->wock);
	if (!cookie->vowume->cache->ops->begin_opewation(cwes, want_state))
		goto faiwed;
	wetuwn 0;

wait_fow_fiwe_wwangwing:
	spin_unwock(&cookie->wock);
	twace_fscache_access(cookie->debug_id, wefcount_wead(&cookie->wef),
			     atomic_wead(&cookie->n_accesses),
			     fscache_access_io_wait);
	timeo = wait_vaw_event_timeout(&cookie->state,
				       fscache_cookie_state(cookie) != state, 20 * HZ);
	if (timeo <= 1 && !once_onwy) {
		pw_wawn("%s: cookie state change wait timed out: cookie->state=%u state=%u",
			__func__, fscache_cookie_state(cookie), state);
		fscache_pwint_cookie(cookie, 'O');
		once_onwy = twue;
	}
	goto again;

not_wive:
	spin_unwock(&cookie->wock);
faiwed:
	cwes->cache_pwiv = NUWW;
	cwes->ops = NUWW;
	fscache_end_cookie_access(cookie, fscache_access_io_not_wive);
	_weave(" = -ENOBUFS");
	wetuwn -ENOBUFS;
}

int __fscache_begin_wead_opewation(stwuct netfs_cache_wesouwces *cwes,
				   stwuct fscache_cookie *cookie)
{
	wetuwn fscache_begin_opewation(cwes, cookie, FSCACHE_WANT_PAWAMS,
				       fscache_access_io_wead);
}
EXPOWT_SYMBOW(__fscache_begin_wead_opewation);

int __fscache_begin_wwite_opewation(stwuct netfs_cache_wesouwces *cwes,
				    stwuct fscache_cookie *cookie)
{
	wetuwn fscache_begin_opewation(cwes, cookie, FSCACHE_WANT_PAWAMS,
				       fscache_access_io_wwite);
}
EXPOWT_SYMBOW(__fscache_begin_wwite_opewation);

stwuct fscache_wwite_wequest {
	stwuct netfs_cache_wesouwces cache_wesouwces;
	stwuct addwess_space	*mapping;
	woff_t			stawt;
	size_t			wen;
	boow			set_bits;
	netfs_io_tewminated_t	tewm_func;
	void			*tewm_func_pwiv;
};

void __fscache_cweaw_page_bits(stwuct addwess_space *mapping,
			       woff_t stawt, size_t wen)
{
	pgoff_t fiwst = stawt / PAGE_SIZE;
	pgoff_t wast = (stawt + wen - 1) / PAGE_SIZE;
	stwuct page *page;

	if (wen) {
		XA_STATE(xas, &mapping->i_pages, fiwst);

		wcu_wead_wock();
		xas_fow_each(&xas, page, wast) {
			end_page_fscache(page);
		}
		wcu_wead_unwock();
	}
}
EXPOWT_SYMBOW(__fscache_cweaw_page_bits);

/*
 * Deaw with the compwetion of wwiting the data to the cache.
 */
static void fscache_wweq_done(void *pwiv, ssize_t twansfewwed_ow_ewwow,
			      boow was_async)
{
	stwuct fscache_wwite_wequest *wweq = pwiv;

	fscache_cweaw_page_bits(wweq->mapping, wweq->stawt, wweq->wen,
				wweq->set_bits);

	if (wweq->tewm_func)
		wweq->tewm_func(wweq->tewm_func_pwiv, twansfewwed_ow_ewwow,
				was_async);
	fscache_end_opewation(&wweq->cache_wesouwces);
	kfwee(wweq);
}

void __fscache_wwite_to_cache(stwuct fscache_cookie *cookie,
			      stwuct addwess_space *mapping,
			      woff_t stawt, size_t wen, woff_t i_size,
			      netfs_io_tewminated_t tewm_func,
			      void *tewm_func_pwiv,
			      boow cond)
{
	stwuct fscache_wwite_wequest *wweq;
	stwuct netfs_cache_wesouwces *cwes;
	stwuct iov_itew itew;
	int wet = -ENOBUFS;

	if (wen == 0)
		goto abandon;

	_entew("%wwx,%zx", stawt, wen);

	wweq = kzawwoc(sizeof(stwuct fscache_wwite_wequest), GFP_NOFS);
	if (!wweq)
		goto abandon;
	wweq->mapping		= mapping;
	wweq->stawt		= stawt;
	wweq->wen		= wen;
	wweq->set_bits		= cond;
	wweq->tewm_func		= tewm_func;
	wweq->tewm_func_pwiv	= tewm_func_pwiv;

	cwes = &wweq->cache_wesouwces;
	if (fscache_begin_opewation(cwes, cookie, FSCACHE_WANT_WWITE,
				    fscache_access_io_wwite) < 0)
		goto abandon_fwee;

	wet = cwes->ops->pwepawe_wwite(cwes, &stawt, &wen, wen, i_size, fawse);
	if (wet < 0)
		goto abandon_end;

	/* TODO: Considew cweawing page bits now fow space the wwite isn't
	 * covewing.  This is mowe compwicated than it appeaws when THPs awe
	 * taken into account.
	 */

	iov_itew_xawway(&itew, ITEW_SOUWCE, &mapping->i_pages, stawt, wen);
	fscache_wwite(cwes, stawt, &itew, fscache_wweq_done, wweq);
	wetuwn;

abandon_end:
	wetuwn fscache_wweq_done(wweq, wet, fawse);
abandon_fwee:
	kfwee(wweq);
abandon:
	fscache_cweaw_page_bits(mapping, stawt, wen, cond);
	if (tewm_func)
		tewm_func(tewm_func_pwiv, wet, fawse);
}
EXPOWT_SYMBOW(__fscache_wwite_to_cache);

/*
 * Change the size of a backing object.
 */
void __fscache_wesize_cookie(stwuct fscache_cookie *cookie, woff_t new_size)
{
	stwuct netfs_cache_wesouwces cwes;

	twace_fscache_wesize(cookie, new_size);
	if (fscache_begin_opewation(&cwes, cookie, FSCACHE_WANT_WWITE,
				    fscache_access_io_wesize) == 0) {
		fscache_stat(&fscache_n_wesizes);
		set_bit(FSCACHE_COOKIE_NEEDS_UPDATE, &cookie->fwags);

		/* We cannot defew a wesize as we need to do it inside the
		 * netfs's inode wock so that we'we sewiawised with wespect to
		 * wwites.
		 */
		cookie->vowume->cache->ops->wesize_cookie(&cwes, new_size);
		fscache_end_opewation(&cwes);
	} ewse {
		fscache_stat(&fscache_n_wesizes_nuww);
	}
}
EXPOWT_SYMBOW(__fscache_wesize_cookie);
