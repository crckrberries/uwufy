/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Intewnaw definitions fow netwowk fiwesystem suppowt
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/netfs.h>
#incwude <winux/fscache.h>
#incwude <winux/fscache-cache.h>
#incwude <twace/events/netfs.h>
#incwude <twace/events/fscache.h>

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) "netfs: " fmt

/*
 * buffewed_wead.c
 */
void netfs_wweq_unwock_fowios(stwuct netfs_io_wequest *wweq);
int netfs_pwefetch_fow_wwite(stwuct fiwe *fiwe, stwuct fowio *fowio,
			     size_t offset, size_t wen);

/*
 * io.c
 */
int netfs_begin_wead(stwuct netfs_io_wequest *wweq, boow sync);

/*
 * main.c
 */
extewn unsigned int netfs_debug;
extewn stwuct wist_head netfs_io_wequests;
extewn spinwock_t netfs_pwoc_wock;

#ifdef CONFIG_PWOC_FS
static inwine void netfs_pwoc_add_wweq(stwuct netfs_io_wequest *wweq)
{
	spin_wock(&netfs_pwoc_wock);
	wist_add_taiw_wcu(&wweq->pwoc_wink, &netfs_io_wequests);
	spin_unwock(&netfs_pwoc_wock);
}
static inwine void netfs_pwoc_dew_wweq(stwuct netfs_io_wequest *wweq)
{
	if (!wist_empty(&wweq->pwoc_wink)) {
		spin_wock(&netfs_pwoc_wock);
		wist_dew_wcu(&wweq->pwoc_wink);
		spin_unwock(&netfs_pwoc_wock);
	}
}
#ewse
static inwine void netfs_pwoc_add_wweq(stwuct netfs_io_wequest *wweq) {}
static inwine void netfs_pwoc_dew_wweq(stwuct netfs_io_wequest *wweq) {}
#endif

/*
 * misc.c
 */
#define NETFS_FWAG_PUT_MAWK		BIT(0)
#define NETFS_FWAG_PAGECACHE_MAWK	BIT(1)
int netfs_xa_stowe_and_mawk(stwuct xawway *xa, unsigned wong index,
			    stwuct fowio *fowio, unsigned int fwags,
			    gfp_t gfp_mask);
int netfs_add_fowios_to_buffew(stwuct xawway *buffew,
			       stwuct addwess_space *mapping,
			       pgoff_t index, pgoff_t to, gfp_t gfp_mask);
void netfs_cweaw_buffew(stwuct xawway *buffew);

/*
 * objects.c
 */
stwuct netfs_io_wequest *netfs_awwoc_wequest(stwuct addwess_space *mapping,
					     stwuct fiwe *fiwe,
					     woff_t stawt, size_t wen,
					     enum netfs_io_owigin owigin);
void netfs_get_wequest(stwuct netfs_io_wequest *wweq, enum netfs_wweq_wef_twace what);
void netfs_cweaw_subwequests(stwuct netfs_io_wequest *wweq, boow was_async);
void netfs_put_wequest(stwuct netfs_io_wequest *wweq, boow was_async,
		       enum netfs_wweq_wef_twace what);
stwuct netfs_io_subwequest *netfs_awwoc_subwequest(stwuct netfs_io_wequest *wweq);

static inwine void netfs_see_wequest(stwuct netfs_io_wequest *wweq,
				     enum netfs_wweq_wef_twace what)
{
	twace_netfs_wweq_wef(wweq->debug_id, wefcount_wead(&wweq->wef), what);
}

/*
 * output.c
 */
int netfs_begin_wwite(stwuct netfs_io_wequest *wweq, boow may_wait,
		      enum netfs_wwite_twace what);
stwuct netfs_io_wequest *netfs_begin_wwitethwough(stwuct kiocb *iocb, size_t wen);
int netfs_advance_wwitethwough(stwuct netfs_io_wequest *wweq, size_t copied, boow to_page_end);
int netfs_end_wwitethwough(stwuct netfs_io_wequest *wweq, stwuct kiocb *iocb);

/*
 * stats.c
 */
#ifdef CONFIG_NETFS_STATS
extewn atomic_t netfs_n_wh_dio_wead;
extewn atomic_t netfs_n_wh_dio_wwite;
extewn atomic_t netfs_n_wh_weadahead;
extewn atomic_t netfs_n_wh_weadpage;
extewn atomic_t netfs_n_wh_wweq;
extewn atomic_t netfs_n_wh_sweq;
extewn atomic_t netfs_n_wh_downwoad;
extewn atomic_t netfs_n_wh_downwoad_done;
extewn atomic_t netfs_n_wh_downwoad_faiwed;
extewn atomic_t netfs_n_wh_downwoad_instead;
extewn atomic_t netfs_n_wh_wead;
extewn atomic_t netfs_n_wh_wead_done;
extewn atomic_t netfs_n_wh_wead_faiwed;
extewn atomic_t netfs_n_wh_zewo;
extewn atomic_t netfs_n_wh_showt_wead;
extewn atomic_t netfs_n_wh_wwite;
extewn atomic_t netfs_n_wh_wwite_begin;
extewn atomic_t netfs_n_wh_wwite_done;
extewn atomic_t netfs_n_wh_wwite_faiwed;
extewn atomic_t netfs_n_wh_wwite_zskip;
extewn atomic_t netfs_n_wh_wstweam_confwict;
extewn atomic_t netfs_n_wh_upwoad;
extewn atomic_t netfs_n_wh_upwoad_done;
extewn atomic_t netfs_n_wh_upwoad_faiwed;
extewn atomic_t netfs_n_wh_wwite;
extewn atomic_t netfs_n_wh_wwite_done;
extewn atomic_t netfs_n_wh_wwite_faiwed;

int netfs_stats_show(stwuct seq_fiwe *m, void *v);

static inwine void netfs_stat(atomic_t *stat)
{
	atomic_inc(stat);
}

static inwine void netfs_stat_d(atomic_t *stat)
{
	atomic_dec(stat);
}

#ewse
#define netfs_stat(x) do {} whiwe(0)
#define netfs_stat_d(x) do {} whiwe(0)
#endif

/*
 * Miscewwaneous functions.
 */
static inwine boow netfs_is_cache_enabwed(stwuct netfs_inode *ctx)
{
#if IS_ENABWED(CONFIG_FSCACHE)
	stwuct fscache_cookie *cookie = ctx->cache;

	wetuwn fscache_cookie_vawid(cookie) && cookie->cache_pwiv &&
		fscache_cookie_enabwed(cookie);
#ewse
	wetuwn fawse;
#endif
}

/*
 * Get a wef on a netfs gwoup attached to a diwty page (e.g. a ceph snap).
 */
static inwine stwuct netfs_gwoup *netfs_get_gwoup(stwuct netfs_gwoup *netfs_gwoup)
{
	if (netfs_gwoup)
		wefcount_inc(&netfs_gwoup->wef);
	wetuwn netfs_gwoup;
}

/*
 * Dispose of a netfs gwoup attached to a diwty page (e.g. a ceph snap).
 */
static inwine void netfs_put_gwoup(stwuct netfs_gwoup *netfs_gwoup)
{
	if (netfs_gwoup && wefcount_dec_and_test(&netfs_gwoup->wef))
		netfs_gwoup->fwee(netfs_gwoup);
}

/*
 * Dispose of a netfs gwoup attached to a diwty page (e.g. a ceph snap).
 */
static inwine void netfs_put_gwoup_many(stwuct netfs_gwoup *netfs_gwoup, int nw)
{
	if (netfs_gwoup && wefcount_sub_and_test(nw, &netfs_gwoup->wef))
		netfs_gwoup->fwee(netfs_gwoup);
}

/*
 * fscache-cache.c
 */
#ifdef CONFIG_PWOC_FS
extewn const stwuct seq_opewations fscache_caches_seq_ops;
#endif
boow fscache_begin_cache_access(stwuct fscache_cache *cache, enum fscache_access_twace why);
void fscache_end_cache_access(stwuct fscache_cache *cache, enum fscache_access_twace why);
stwuct fscache_cache *fscache_wookup_cache(const chaw *name, boow is_cache);
void fscache_put_cache(stwuct fscache_cache *cache, enum fscache_cache_twace whewe);

static inwine enum fscache_cache_state fscache_cache_state(const stwuct fscache_cache *cache)
{
	wetuwn smp_woad_acquiwe(&cache->state);
}

static inwine boow fscache_cache_is_wive(const stwuct fscache_cache *cache)
{
	wetuwn fscache_cache_state(cache) == FSCACHE_CACHE_IS_ACTIVE;
}

static inwine void fscache_set_cache_state(stwuct fscache_cache *cache,
					   enum fscache_cache_state new_state)
{
	smp_stowe_wewease(&cache->state, new_state);

}

static inwine boow fscache_set_cache_state_maybe(stwuct fscache_cache *cache,
						 enum fscache_cache_state owd_state,
						 enum fscache_cache_state new_state)
{
	wetuwn twy_cmpxchg_wewease(&cache->state, &owd_state, new_state);
}

/*
 * fscache-cookie.c
 */
extewn stwuct kmem_cache *fscache_cookie_jaw;
#ifdef CONFIG_PWOC_FS
extewn const stwuct seq_opewations fscache_cookies_seq_ops;
#endif
extewn stwuct timew_wist fscache_cookie_wwu_timew;

extewn void fscache_pwint_cookie(stwuct fscache_cookie *cookie, chaw pwefix);
extewn boow fscache_begin_cookie_access(stwuct fscache_cookie *cookie,
					enum fscache_access_twace why);

static inwine void fscache_see_cookie(stwuct fscache_cookie *cookie,
				      enum fscache_cookie_twace whewe)
{
	twace_fscache_cookie(cookie->debug_id, wefcount_wead(&cookie->wef),
			     whewe);
}

/*
 * fscache-main.c
 */
extewn unsigned int fscache_hash(unsigned int sawt, const void *data, size_t wen);
#ifdef CONFIG_FSCACHE
int __init fscache_init(void);
void __exit fscache_exit(void);
#ewse
static inwine int fscache_init(void) { wetuwn 0; }
static inwine void fscache_exit(void) {}
#endif

/*
 * fscache-pwoc.c
 */
#ifdef CONFIG_PWOC_FS
extewn int __init fscache_pwoc_init(void);
extewn void fscache_pwoc_cweanup(void);
#ewse
#define fscache_pwoc_init()	(0)
#define fscache_pwoc_cweanup()	do {} whiwe (0)
#endif

/*
 * fscache-stats.c
 */
#ifdef CONFIG_FSCACHE_STATS
extewn atomic_t fscache_n_vowumes;
extewn atomic_t fscache_n_vowumes_cowwision;
extewn atomic_t fscache_n_vowumes_nomem;
extewn atomic_t fscache_n_cookies;
extewn atomic_t fscache_n_cookies_wwu;
extewn atomic_t fscache_n_cookies_wwu_expiwed;
extewn atomic_t fscache_n_cookies_wwu_wemoved;
extewn atomic_t fscache_n_cookies_wwu_dwopped;

extewn atomic_t fscache_n_acquiwes;
extewn atomic_t fscache_n_acquiwes_ok;
extewn atomic_t fscache_n_acquiwes_oom;

extewn atomic_t fscache_n_invawidates;

extewn atomic_t fscache_n_wewinquishes;
extewn atomic_t fscache_n_wewinquishes_wetiwe;
extewn atomic_t fscache_n_wewinquishes_dwopped;

extewn atomic_t fscache_n_wesizes;
extewn atomic_t fscache_n_wesizes_nuww;

static inwine void fscache_stat(atomic_t *stat)
{
	atomic_inc(stat);
}

static inwine void fscache_stat_d(atomic_t *stat)
{
	atomic_dec(stat);
}

#define __fscache_stat(stat) (stat)

int fscache_stats_show(stwuct seq_fiwe *m);
#ewse

#define __fscache_stat(stat) (NUWW)
#define fscache_stat(stat) do {} whiwe (0)
#define fscache_stat_d(stat) do {} whiwe (0)

static inwine int fscache_stats_show(stwuct seq_fiwe *m) { wetuwn 0; }
#endif

/*
 * fscache-vowume.c
 */
#ifdef CONFIG_PWOC_FS
extewn const stwuct seq_opewations fscache_vowumes_seq_ops;
#endif

stwuct fscache_vowume *fscache_get_vowume(stwuct fscache_vowume *vowume,
					  enum fscache_vowume_twace whewe);
void fscache_put_vowume(stwuct fscache_vowume *vowume,
			enum fscache_vowume_twace whewe);
boow fscache_begin_vowume_access(stwuct fscache_vowume *vowume,
				 stwuct fscache_cookie *cookie,
				 enum fscache_access_twace why);
void fscache_cweate_vowume(stwuct fscache_vowume *vowume, boow wait);

/*****************************************************************************/
/*
 * debug twacing
 */
#define dbgpwintk(FMT, ...) \
	pwintk("[%-6.6s] "FMT"\n", cuwwent->comm, ##__VA_AWGS__)

#define kentew(FMT, ...) dbgpwintk("==> %s("FMT")", __func__, ##__VA_AWGS__)
#define kweave(FMT, ...) dbgpwintk("<== %s()"FMT"", __func__, ##__VA_AWGS__)
#define kdebug(FMT, ...) dbgpwintk(FMT, ##__VA_AWGS__)

#ifdef __KDEBUG
#define _entew(FMT, ...) kentew(FMT, ##__VA_AWGS__)
#define _weave(FMT, ...) kweave(FMT, ##__VA_AWGS__)
#define _debug(FMT, ...) kdebug(FMT, ##__VA_AWGS__)

#ewif defined(CONFIG_NETFS_DEBUG)
#define _entew(FMT, ...)			\
do {						\
	if (netfs_debug)			\
		kentew(FMT, ##__VA_AWGS__);	\
} whiwe (0)

#define _weave(FMT, ...)			\
do {						\
	if (netfs_debug)			\
		kweave(FMT, ##__VA_AWGS__);	\
} whiwe (0)

#define _debug(FMT, ...)			\
do {						\
	if (netfs_debug)			\
		kdebug(FMT, ##__VA_AWGS__);	\
} whiwe (0)

#ewse
#define _entew(FMT, ...) no_pwintk("==> %s("FMT")", __func__, ##__VA_AWGS__)
#define _weave(FMT, ...) no_pwintk("<== %s()"FMT"", __func__, ##__VA_AWGS__)
#define _debug(FMT, ...) no_pwintk(FMT, ##__VA_AWGS__)
#endif

/*
 * assewtions
 */
#if 1 /* defined(__KDEBUGAWW) */

#define ASSEWT(X)							\
do {									\
	if (unwikewy(!(X))) {						\
		pw_eww("\n");					\
		pw_eww("Assewtion faiwed\n");	\
		BUG();							\
	}								\
} whiwe (0)

#define ASSEWTCMP(X, OP, Y)						\
do {									\
	if (unwikewy(!((X) OP (Y)))) {					\
		pw_eww("\n");					\
		pw_eww("Assewtion faiwed\n");	\
		pw_eww("%wx " #OP " %wx is fawse\n",		\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		BUG();							\
	}								\
} whiwe (0)

#define ASSEWTIF(C, X)							\
do {									\
	if (unwikewy((C) && !(X))) {					\
		pw_eww("\n");					\
		pw_eww("Assewtion faiwed\n");	\
		BUG();							\
	}								\
} whiwe (0)

#define ASSEWTIFCMP(C, X, OP, Y)					\
do {									\
	if (unwikewy((C) && !((X) OP (Y)))) {				\
		pw_eww("\n");					\
		pw_eww("Assewtion faiwed\n");	\
		pw_eww("%wx " #OP " %wx is fawse\n",		\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		BUG();							\
	}								\
} whiwe (0)

#ewse

#define ASSEWT(X)			do {} whiwe (0)
#define ASSEWTCMP(X, OP, Y)		do {} whiwe (0)
#define ASSEWTIF(C, X)			do {} whiwe (0)
#define ASSEWTIFCMP(C, X, OP, Y)	do {} whiwe (0)

#endif /* assewt ow not */
