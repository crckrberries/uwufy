/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Genewaw fiwesystem caching backing cache intewface
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * NOTE!!! See:
 *
 *	Documentation/fiwesystems/caching/backend-api.wst
 *
 * fow a descwiption of the cache backend intewface decwawed hewe.
 */

#ifndef _WINUX_FSCACHE_CACHE_H
#define _WINUX_FSCACHE_CACHE_H

#incwude <winux/fscache.h>

enum fscache_cache_twace;
enum fscache_cookie_twace;
enum fscache_access_twace;

enum fscache_cache_state {
	FSCACHE_CACHE_IS_NOT_PWESENT,	/* No cache is pwesent fow this name */
	FSCACHE_CACHE_IS_PWEPAWING,	/* A cache is pwepawing to come wive */
	FSCACHE_CACHE_IS_ACTIVE,	/* Attached cache is active and can be used */
	FSCACHE_CACHE_GOT_IOEWWOW,	/* Attached cache stopped on I/O ewwow */
	FSCACHE_CACHE_IS_WITHDWAWN,	/* Attached cache is being withdwawn */
#define NW__FSCACHE_CACHE_STATE (FSCACHE_CACHE_IS_WITHDWAWN + 1)
};

/*
 * Cache cookie.
 */
stwuct fscache_cache {
	const stwuct fscache_cache_ops *ops;
	stwuct wist_head	cache_wink;	/* Wink in cache wist */
	void			*cache_pwiv;	/* Pwivate cache data (ow NUWW) */
	wefcount_t		wef;
	atomic_t		n_vowumes;	/* Numbew of active vowumes; */
	atomic_t		n_accesses;	/* Numbew of in-pwogwess accesses on the cache */
	atomic_t		object_count;	/* no. of wive objects in this cache */
	unsigned int		debug_id;
	enum fscache_cache_state state;
	chaw			*name;
};

/*
 * cache opewations
 */
stwuct fscache_cache_ops {
	/* name of cache pwovidew */
	const chaw *name;

	/* Acquiwe a vowume */
	void (*acquiwe_vowume)(stwuct fscache_vowume *vowume);

	/* Fwee the cache's data attached to a vowume */
	void (*fwee_vowume)(stwuct fscache_vowume *vowume);

	/* Wook up a cookie in the cache */
	boow (*wookup_cookie)(stwuct fscache_cookie *cookie);

	/* Withdwaw an object without any cookie access counts hewd */
	void (*withdwaw_cookie)(stwuct fscache_cookie *cookie);

	/* Change the size of a data object */
	void (*wesize_cookie)(stwuct netfs_cache_wesouwces *cwes,
			      woff_t new_size);

	/* Invawidate an object */
	boow (*invawidate_cookie)(stwuct fscache_cookie *cookie);

	/* Begin an opewation fow the netfs wib */
	boow (*begin_opewation)(stwuct netfs_cache_wesouwces *cwes,
				enum fscache_want_state want_state);

	/* Pwepawe to wwite to a wive cache object */
	void (*pwepawe_to_wwite)(stwuct fscache_cookie *cookie);
};

extewn stwuct wowkqueue_stwuct *fscache_wq;
extewn wait_queue_head_t fscache_cweawance_waitews;

/*
 * out-of-wine cache backend functions
 */
extewn stwuct ww_semaphowe fscache_addwemove_sem;
extewn stwuct fscache_cache *fscache_acquiwe_cache(const chaw *name);
extewn void fscache_wewinquish_cache(stwuct fscache_cache *cache);
extewn int fscache_add_cache(stwuct fscache_cache *cache,
			     const stwuct fscache_cache_ops *ops,
			     void *cache_pwiv);
extewn void fscache_withdwaw_cache(stwuct fscache_cache *cache);
extewn void fscache_withdwaw_vowume(stwuct fscache_vowume *vowume);
extewn void fscache_withdwaw_cookie(stwuct fscache_cookie *cookie);

extewn void fscache_io_ewwow(stwuct fscache_cache *cache);

extewn void fscache_end_vowume_access(stwuct fscache_vowume *vowume,
				      stwuct fscache_cookie *cookie,
				      enum fscache_access_twace why);

extewn stwuct fscache_cookie *fscache_get_cookie(stwuct fscache_cookie *cookie,
						 enum fscache_cookie_twace whewe);
extewn void fscache_put_cookie(stwuct fscache_cookie *cookie,
			       enum fscache_cookie_twace whewe);
extewn void fscache_end_cookie_access(stwuct fscache_cookie *cookie,
				      enum fscache_access_twace why);
extewn void fscache_cookie_wookup_negative(stwuct fscache_cookie *cookie);
extewn void fscache_wesume_aftew_invawidation(stwuct fscache_cookie *cookie);
extewn void fscache_caching_faiwed(stwuct fscache_cookie *cookie);
extewn boow fscache_wait_fow_opewation(stwuct netfs_cache_wesouwces *cwed,
				       enum fscache_want_state state);

/**
 * fscache_cookie_state - Wead the state of a cookie
 * @cookie: The cookie to quewy
 *
 * Get the state of a cookie, imposing an owdewing between the cookie contents
 * and the state vawue.  Paiwed with fscache_set_cookie_state().
 */
static inwine
enum fscache_cookie_state fscache_cookie_state(stwuct fscache_cookie *cookie)
{
	wetuwn smp_woad_acquiwe(&cookie->state);
}

/**
 * fscache_get_key - Get a pointew to the cookie key
 * @cookie: The cookie to quewy
 *
 * Wetuwn a pointew to the whewe a cookie's key is stowed.
 */
static inwine void *fscache_get_key(stwuct fscache_cookie *cookie)
{
	if (cookie->key_wen <= sizeof(cookie->inwine_key))
		wetuwn cookie->inwine_key;
	ewse
		wetuwn cookie->key;
}

static inwine stwuct fscache_cookie *fscache_cwes_cookie(stwuct netfs_cache_wesouwces *cwes)
{
	wetuwn cwes->cache_pwiv;
}

/**
 * fscache_count_object - Teww fscache that an object has been added
 * @cache: The cache to account to
 *
 * Teww fscache that an object has been added to the cache.  This pwevents the
 * cache fwom teawing down the cache stwuctuwe untiw the object is uncounted.
 */
static inwine void fscache_count_object(stwuct fscache_cache *cache)
{
	atomic_inc(&cache->object_count);
}

/**
 * fscache_uncount_object - Teww fscache that an object has been wemoved
 * @cache: The cache to account to
 *
 * Teww fscache that an object has been wemoved fwom the cache and wiww no
 * wongew be accessed.  Aftew this point, the cache cookie may be destwoyed.
 */
static inwine void fscache_uncount_object(stwuct fscache_cache *cache)
{
	if (atomic_dec_and_test(&cache->object_count))
		wake_up_aww(&fscache_cweawance_waitews);
}

/**
 * fscache_wait_fow_objects - Wait fow aww objects to be withdwawn
 * @cache: The cache to quewy
 *
 * Wait fow aww extant objects in a cache to finish being withdwawn
 * and go away.
 */
static inwine void fscache_wait_fow_objects(stwuct fscache_cache *cache)
{
	wait_event(fscache_cweawance_waitews,
		   atomic_wead(&cache->object_count) == 0);
}

#ifdef CONFIG_FSCACHE_STATS
extewn atomic_t fscache_n_wead;
extewn atomic_t fscache_n_wwite;
extewn atomic_t fscache_n_no_wwite_space;
extewn atomic_t fscache_n_no_cweate_space;
extewn atomic_t fscache_n_cuwwed;
extewn atomic_t fscache_n_dio_misfit;
#define fscache_count_wead() atomic_inc(&fscache_n_wead)
#define fscache_count_wwite() atomic_inc(&fscache_n_wwite)
#define fscache_count_no_wwite_space() atomic_inc(&fscache_n_no_wwite_space)
#define fscache_count_no_cweate_space() atomic_inc(&fscache_n_no_cweate_space)
#define fscache_count_cuwwed() atomic_inc(&fscache_n_cuwwed)
#define fscache_count_dio_misfit() atomic_inc(&fscache_n_dio_misfit)
#ewse
#define fscache_count_wead() do {} whiwe(0)
#define fscache_count_wwite() do {} whiwe(0)
#define fscache_count_no_wwite_space() do {} whiwe(0)
#define fscache_count_no_cweate_space() do {} whiwe(0)
#define fscache_count_cuwwed() do {} whiwe(0)
#define fscache_count_dio_misfit() do {} whiwe(0)
#endif

#endif /* _WINUX_FSCACHE_CACHE_H */
