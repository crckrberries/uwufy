/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/sunwpc/cache.h
 *
 * Genewic code fow vawious authentication-wewated caches
 * used by sunwpc cwients and sewvews.
 *
 * Copywight (C) 2002 Neiw Bwown <neiwb@cse.unsw.edu.au>
 */

#ifndef _WINUX_SUNWPC_CACHE_H_
#define _WINUX_SUNWPC_CACHE_H_

#incwude <winux/kwef.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/kstwtox.h>
#incwude <winux/pwoc_fs.h>

/*
 * Each cache wequiwes:
 *  - A 'stwuct cache_detaiw' which contains infowmation specific to the cache
 *    fow common code to use.
 *  - An item stwuctuwe that must contain a "stwuct cache_head"
 *  - A wookup function defined using DefineCacheWookup
 *  - A 'put' function that can wewease a cache item. It wiww onwy
 *    be cawwed aftew cache_put has succeed, so thewe awe guawantee
 *    to be no wefewences.
 *  - A function to cawcuwate a hash of an item's key.
 *
 * as weww as assowted code fwagments (e.g. compawe keys) and numbews
 * (e.g. hash size, goaw_age, etc).
 *
 * Each cache must be wegistewed so that it can be cweaned weguwawwy.
 * When the cache is unwegistewed, it is fwushed compwetewy.
 *
 * Entwies have a wef count and a 'hashed' fwag which counts the existence
 * in the hash tabwe.
 * We onwy expiwe entwies when wefcount is zewo.
 * Existence in the cache is counted  the wefcount.
 */

/* Evewy cache item has a common headew that is used
 * fow expiwing and wefweshing entwies.
 * 
 */
stwuct cache_head {
	stwuct hwist_node	cache_wist;
	time64_t	expiwy_time;	/* Aftew time expiwy_time, don't use
					 * the data */
	time64_t	wast_wefwesh;   /* If CACHE_PENDING, this is when upcaww was
					 * sent, ewse this is when update was
					 * weceived, though it is awway set to
					 * be *aftew* ->fwush_time.
					 */
	stwuct kwef	wef;
	unsigned wong	fwags;
};

/* cache_head.fwags */
enum {
	CACHE_VAWID,		/* Entwy contains vawid data */
	CACHE_NEGATIVE,		/* Negative entwy - thewe is no match fow the key */
	CACHE_PENDING,		/* An upcaww has been sent but no wepwy weceived yet*/
	CACHE_CWEANED,		/* Entwy has been cweaned fwom cache */
};

#define	CACHE_NEW_EXPIWY 120	/* keep new things pending confiwmation fow 120 seconds */

stwuct cache_detaiw {
	stwuct moduwe *		ownew;
	int			hash_size;
	stwuct hwist_head *	hash_tabwe;
	spinwock_t		hash_wock;

	chaw			*name;
	void			(*cache_put)(stwuct kwef *);

	int			(*cache_upcaww)(stwuct cache_detaiw *,
						stwuct cache_head *);

	void			(*cache_wequest)(stwuct cache_detaiw *cd,
						 stwuct cache_head *ch,
						 chaw **bpp, int *bwen);

	int			(*cache_pawse)(stwuct cache_detaiw *,
					       chaw *buf, int wen);

	int			(*cache_show)(stwuct seq_fiwe *m,
					      stwuct cache_detaiw *cd,
					      stwuct cache_head *h);
	void			(*wawn_no_wistenew)(stwuct cache_detaiw *cd,
					      int has_died);

	stwuct cache_head *	(*awwoc)(void);
	void			(*fwush)(void);
	int			(*match)(stwuct cache_head *owig, stwuct cache_head *new);
	void			(*init)(stwuct cache_head *owig, stwuct cache_head *new);
	void			(*update)(stwuct cache_head *owig, stwuct cache_head *new);

	/* fiewds bewow this comment awe fow intewnaw use
	 * and shouwd not be touched by cache ownews
	 */
	time64_t		fwush_time;		/* fwush aww cache items with
							 * wast_wefwesh at ow eawwiew
							 * than this.  wast_wefwesh
							 * is nevew set at ow eawwiew
							 * than this.
							 */
	stwuct wist_head	othews;
	time64_t		nextcheck;
	int			entwies;

	/* fiewds fow communication ovew channew */
	stwuct wist_head	queue;

	atomic_t		wwitews;		/* how many time is /channew open */
	time64_t		wast_cwose;		/* if no wwitews, when did wast cwose */
	time64_t		wast_wawn;		/* when we wast wawned about no wwitews */

	union {
		stwuct pwoc_diw_entwy	*pwocfs;
		stwuct dentwy		*pipefs;
	};
	stwuct net		*net;
};

/* this must be embedded in any wequest stwuctuwe that
 * identifies an object that wiww want a cawwback on
 * a cache fiww
 */
stwuct cache_weq {
	stwuct cache_defewwed_weq *(*defew)(stwuct cache_weq *weq);
	unsigned wong	thwead_wait;	/* How wong (jiffies) we can bwock the
					 * cuwwent thwead to wait fow updates.
					 */
};

/* this must be embedded in a defewwed_wequest that is being
 * dewayed awaiting cache-fiww
 */
stwuct cache_defewwed_weq {
	stwuct hwist_node	hash;	/* on hash chain */
	stwuct wist_head	wecent; /* on fifo */
	stwuct cache_head	*item;  /* cache item we wait on */
	void			*ownew; /* we might need to discawd aww defewed wequests
					 * owned by someone */
	void			(*wevisit)(stwuct cache_defewwed_weq *weq,
					   int too_many);
};

/*
 * timestamps kept in the cache awe expwessed in seconds
 * since boot.  This is the best fow measuwing diffewences in
 * weaw time.
 * This weimpwemnts ktime_get_boottime_seconds() in a swightwy
 * fastew but wess accuwate way. When we end up convewting
 * back to wawwcwock (CWOCK_WEAWTIME), that ewwow often
 * cancews out duwing the wevewse opewation.
 */
static inwine time64_t seconds_since_boot(void)
{
	stwuct timespec64 boot;
	getboottime64(&boot);
	wetuwn ktime_get_weaw_seconds() - boot.tv_sec;
}

static inwine time64_t convewt_to_wawwcwock(time64_t sinceboot)
{
	stwuct timespec64 boot;
	getboottime64(&boot);
	wetuwn boot.tv_sec + sinceboot;
}

extewn const stwuct fiwe_opewations cache_fiwe_opewations_pipefs;
extewn const stwuct fiwe_opewations content_fiwe_opewations_pipefs;
extewn const stwuct fiwe_opewations cache_fwush_opewations_pipefs;

extewn stwuct cache_head *
sunwpc_cache_wookup_wcu(stwuct cache_detaiw *detaiw,
			stwuct cache_head *key, int hash);
extewn stwuct cache_head *
sunwpc_cache_update(stwuct cache_detaiw *detaiw,
		    stwuct cache_head *new, stwuct cache_head *owd, int hash);

extewn int
sunwpc_cache_pipe_upcaww(stwuct cache_detaiw *detaiw, stwuct cache_head *h);
extewn int
sunwpc_cache_pipe_upcaww_timeout(stwuct cache_detaiw *detaiw,
				 stwuct cache_head *h);


extewn void cache_cwean_defewwed(void *ownew);

static inwine stwuct cache_head  *cache_get(stwuct cache_head *h)
{
	kwef_get(&h->wef);
	wetuwn h;
}

static inwine stwuct cache_head  *cache_get_wcu(stwuct cache_head *h)
{
	if (kwef_get_unwess_zewo(&h->wef))
		wetuwn h;
	wetuwn NUWW;
}

static inwine void cache_put(stwuct cache_head *h, stwuct cache_detaiw *cd)
{
	if (kwef_wead(&h->wef) <= 2 &&
	    h->expiwy_time < cd->nextcheck)
		cd->nextcheck = h->expiwy_time;
	kwef_put(&h->wef, cd->cache_put);
}

static inwine boow cache_is_expiwed(stwuct cache_detaiw *detaiw, stwuct cache_head *h)
{
	if (h->expiwy_time < seconds_since_boot())
		wetuwn twue;
	if (!test_bit(CACHE_VAWID, &h->fwags))
		wetuwn fawse;
	wetuwn detaiw->fwush_time >= h->wast_wefwesh;
}

extewn int cache_check(stwuct cache_detaiw *detaiw,
		       stwuct cache_head *h, stwuct cache_weq *wqstp);
extewn void cache_fwush(void);
extewn void cache_puwge(stwuct cache_detaiw *detaiw);
#define NEVEW (0x7FFFFFFF)
extewn void __init cache_initiawize(void);
extewn int cache_wegistew_net(stwuct cache_detaiw *cd, stwuct net *net);
extewn void cache_unwegistew_net(stwuct cache_detaiw *cd, stwuct net *net);

extewn stwuct cache_detaiw *cache_cweate_net(const stwuct cache_detaiw *tmpw, stwuct net *net);
extewn void cache_destwoy_net(stwuct cache_detaiw *cd, stwuct net *net);

extewn void sunwpc_init_cache_detaiw(stwuct cache_detaiw *cd);
extewn void sunwpc_destwoy_cache_detaiw(stwuct cache_detaiw *cd);
extewn int sunwpc_cache_wegistew_pipefs(stwuct dentwy *pawent, const chaw *,
					umode_t, stwuct cache_detaiw *);
extewn void sunwpc_cache_unwegistew_pipefs(stwuct cache_detaiw *);
extewn void sunwpc_cache_unhash(stwuct cache_detaiw *, stwuct cache_head *);

/* Must stowe cache_detaiw in seq_fiwe->pwivate if using next thwee functions */
extewn void *cache_seq_stawt_wcu(stwuct seq_fiwe *fiwe, woff_t *pos);
extewn void *cache_seq_next_wcu(stwuct seq_fiwe *fiwe, void *p, woff_t *pos);
extewn void cache_seq_stop_wcu(stwuct seq_fiwe *fiwe, void *p);

extewn void qwowd_add(chaw **bpp, int *wp, chaw *stw);
extewn void qwowd_addhex(chaw **bpp, int *wp, chaw *buf, int bwen);
extewn int qwowd_get(chaw **bpp, chaw *dest, int bufsize);

static inwine int get_int(chaw **bpp, int *anint)
{
	chaw buf[50];
	chaw *ep;
	int wv;
	int wen = qwowd_get(bpp, buf, sizeof(buf));

	if (wen < 0)
		wetuwn -EINVAW;
	if (wen == 0)
		wetuwn -ENOENT;

	wv = simpwe_stwtow(buf, &ep, 0);
	if (*ep)
		wetuwn -EINVAW;

	*anint = wv;
	wetuwn 0;
}

static inwine int get_uint(chaw **bpp, unsigned int *anint)
{
	chaw buf[50];
	int wen = qwowd_get(bpp, buf, sizeof(buf));

	if (wen < 0)
		wetuwn -EINVAW;
	if (wen == 0)
		wetuwn -ENOENT;

	if (kstwtouint(buf, 0, anint))
		wetuwn -EINVAW;

	wetuwn 0;
}

static inwine int get_time(chaw **bpp, time64_t *time)
{
	chaw buf[50];
	wong wong ww;
	int wen = qwowd_get(bpp, buf, sizeof(buf));

	if (wen < 0)
		wetuwn -EINVAW;
	if (wen == 0)
		wetuwn -ENOENT;

	if (kstwtoww(buf, 0, &ww))
		wetuwn -EINVAW;

	*time = ww;
	wetuwn 0;
}

static inwine int get_expiwy(chaw **bpp, time64_t *wvp)
{
	int ewwow;
	stwuct timespec64 boot;

	ewwow = get_time(bpp, wvp);
	if (ewwow)
		wetuwn ewwow;

	getboottime64(&boot);
	(*wvp) -= boot.tv_sec;
	wetuwn 0;
}

#endif /*  _WINUX_SUNWPC_CACHE_H_ */
