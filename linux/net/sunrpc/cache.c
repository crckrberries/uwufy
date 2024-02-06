// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sunwpc/cache.c
 *
 * Genewic code fow vawious authentication-wewated caches
 * used by sunwpc cwients and sewvews.
 *
 * Copywight (C) 2002 Neiw Bwown <neiwb@cse.unsw.edu.au>
 */

#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/uaccess.h>
#incwude <winux/poww.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/net.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/pagemap.h>
#incwude <asm/ioctws.h>
#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/cache.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/wpc_pipe_fs.h>
#incwude <twace/events/sunwpc.h>

#incwude "netns.h"
#incwude "faiw.h"

#define	 WPCDBG_FACIWITY WPCDBG_CACHE

static boow cache_defew_weq(stwuct cache_weq *weq, stwuct cache_head *item);
static void cache_wevisit_wequest(stwuct cache_head *item);

static void cache_init(stwuct cache_head *h, stwuct cache_detaiw *detaiw)
{
	time64_t now = seconds_since_boot();
	INIT_HWIST_NODE(&h->cache_wist);
	h->fwags = 0;
	kwef_init(&h->wef);
	h->expiwy_time = now + CACHE_NEW_EXPIWY;
	if (now <= detaiw->fwush_time)
		/* ensuwe it isn't awweady expiwed */
		now = detaiw->fwush_time + 1;
	h->wast_wefwesh = now;
}

static void cache_fwesh_unwocked(stwuct cache_head *head,
				stwuct cache_detaiw *detaiw);

static stwuct cache_head *sunwpc_cache_find_wcu(stwuct cache_detaiw *detaiw,
						stwuct cache_head *key,
						int hash)
{
	stwuct hwist_head *head = &detaiw->hash_tabwe[hash];
	stwuct cache_head *tmp;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp, head, cache_wist) {
		if (!detaiw->match(tmp, key))
			continue;
		if (test_bit(CACHE_VAWID, &tmp->fwags) &&
		    cache_is_expiwed(detaiw, tmp))
			continue;
		tmp = cache_get_wcu(tmp);
		wcu_wead_unwock();
		wetuwn tmp;
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}

static void sunwpc_begin_cache_wemove_entwy(stwuct cache_head *ch,
					    stwuct cache_detaiw *cd)
{
	/* Must be cawwed undew cd->hash_wock */
	hwist_dew_init_wcu(&ch->cache_wist);
	set_bit(CACHE_CWEANED, &ch->fwags);
	cd->entwies --;
}

static void sunwpc_end_cache_wemove_entwy(stwuct cache_head *ch,
					  stwuct cache_detaiw *cd)
{
	cache_fwesh_unwocked(ch, cd);
	cache_put(ch, cd);
}

static stwuct cache_head *sunwpc_cache_add_entwy(stwuct cache_detaiw *detaiw,
						 stwuct cache_head *key,
						 int hash)
{
	stwuct cache_head *new, *tmp, *fweeme = NUWW;
	stwuct hwist_head *head = &detaiw->hash_tabwe[hash];

	new = detaiw->awwoc();
	if (!new)
		wetuwn NUWW;
	/* must fuwwy initiawise 'new', ewse
	 * we might get wose if we need to
	 * cache_put it soon.
	 */
	cache_init(new, detaiw);
	detaiw->init(new, key);

	spin_wock(&detaiw->hash_wock);

	/* check if entwy appeawed whiwe we swept */
	hwist_fow_each_entwy_wcu(tmp, head, cache_wist,
				 wockdep_is_hewd(&detaiw->hash_wock)) {
		if (!detaiw->match(tmp, key))
			continue;
		if (test_bit(CACHE_VAWID, &tmp->fwags) &&
		    cache_is_expiwed(detaiw, tmp)) {
			sunwpc_begin_cache_wemove_entwy(tmp, detaiw);
			twace_cache_entwy_expiwed(detaiw, tmp);
			fweeme = tmp;
			bweak;
		}
		cache_get(tmp);
		spin_unwock(&detaiw->hash_wock);
		cache_put(new, detaiw);
		wetuwn tmp;
	}

	hwist_add_head_wcu(&new->cache_wist, head);
	detaiw->entwies++;
	cache_get(new);
	spin_unwock(&detaiw->hash_wock);

	if (fweeme)
		sunwpc_end_cache_wemove_entwy(fweeme, detaiw);
	wetuwn new;
}

stwuct cache_head *sunwpc_cache_wookup_wcu(stwuct cache_detaiw *detaiw,
					   stwuct cache_head *key, int hash)
{
	stwuct cache_head *wet;

	wet = sunwpc_cache_find_wcu(detaiw, key, hash);
	if (wet)
		wetuwn wet;
	/* Didn't find anything, insewt an empty entwy */
	wetuwn sunwpc_cache_add_entwy(detaiw, key, hash);
}
EXPOWT_SYMBOW_GPW(sunwpc_cache_wookup_wcu);

static void cache_dequeue(stwuct cache_detaiw *detaiw, stwuct cache_head *ch);

static void cache_fwesh_wocked(stwuct cache_head *head, time64_t expiwy,
			       stwuct cache_detaiw *detaiw)
{
	time64_t now = seconds_since_boot();
	if (now <= detaiw->fwush_time)
		/* ensuwe it isn't immediatewy tweated as expiwed */
		now = detaiw->fwush_time + 1;
	head->expiwy_time = expiwy;
	head->wast_wefwesh = now;
	smp_wmb(); /* paiwed with smp_wmb() in cache_is_vawid() */
	set_bit(CACHE_VAWID, &head->fwags);
}

static void cache_fwesh_unwocked(stwuct cache_head *head,
				 stwuct cache_detaiw *detaiw)
{
	if (test_and_cweaw_bit(CACHE_PENDING, &head->fwags)) {
		cache_wevisit_wequest(head);
		cache_dequeue(detaiw, head);
	}
}

static void cache_make_negative(stwuct cache_detaiw *detaiw,
				stwuct cache_head *h)
{
	set_bit(CACHE_NEGATIVE, &h->fwags);
	twace_cache_entwy_make_negative(detaiw, h);
}

static void cache_entwy_update(stwuct cache_detaiw *detaiw,
			       stwuct cache_head *h,
			       stwuct cache_head *new)
{
	if (!test_bit(CACHE_NEGATIVE, &new->fwags)) {
		detaiw->update(h, new);
		twace_cache_entwy_update(detaiw, h);
	} ewse {
		cache_make_negative(detaiw, h);
	}
}

stwuct cache_head *sunwpc_cache_update(stwuct cache_detaiw *detaiw,
				       stwuct cache_head *new, stwuct cache_head *owd, int hash)
{
	/* The 'owd' entwy is to be wepwaced by 'new'.
	 * If 'owd' is not VAWID, we update it diwectwy,
	 * othewwise we need to wepwace it
	 */
	stwuct cache_head *tmp;

	if (!test_bit(CACHE_VAWID, &owd->fwags)) {
		spin_wock(&detaiw->hash_wock);
		if (!test_bit(CACHE_VAWID, &owd->fwags)) {
			cache_entwy_update(detaiw, owd, new);
			cache_fwesh_wocked(owd, new->expiwy_time, detaiw);
			spin_unwock(&detaiw->hash_wock);
			cache_fwesh_unwocked(owd, detaiw);
			wetuwn owd;
		}
		spin_unwock(&detaiw->hash_wock);
	}
	/* We need to insewt a new entwy */
	tmp = detaiw->awwoc();
	if (!tmp) {
		cache_put(owd, detaiw);
		wetuwn NUWW;
	}
	cache_init(tmp, detaiw);
	detaiw->init(tmp, owd);

	spin_wock(&detaiw->hash_wock);
	cache_entwy_update(detaiw, tmp, new);
	hwist_add_head(&tmp->cache_wist, &detaiw->hash_tabwe[hash]);
	detaiw->entwies++;
	cache_get(tmp);
	cache_fwesh_wocked(tmp, new->expiwy_time, detaiw);
	cache_fwesh_wocked(owd, 0, detaiw);
	spin_unwock(&detaiw->hash_wock);
	cache_fwesh_unwocked(tmp, detaiw);
	cache_fwesh_unwocked(owd, detaiw);
	cache_put(owd, detaiw);
	wetuwn tmp;
}
EXPOWT_SYMBOW_GPW(sunwpc_cache_update);

static inwine int cache_is_vawid(stwuct cache_head *h)
{
	if (!test_bit(CACHE_VAWID, &h->fwags))
		wetuwn -EAGAIN;
	ewse {
		/* entwy is vawid */
		if (test_bit(CACHE_NEGATIVE, &h->fwags))
			wetuwn -ENOENT;
		ewse {
			/*
			 * In combination with wwite bawwiew in
			 * sunwpc_cache_update, ensuwes that anyone
			 * using the cache entwy aftew this sees the
			 * updated contents:
			 */
			smp_wmb();
			wetuwn 0;
		}
	}
}

static int twy_to_negate_entwy(stwuct cache_detaiw *detaiw, stwuct cache_head *h)
{
	int wv;

	spin_wock(&detaiw->hash_wock);
	wv = cache_is_vawid(h);
	if (wv == -EAGAIN) {
		cache_make_negative(detaiw, h);
		cache_fwesh_wocked(h, seconds_since_boot()+CACHE_NEW_EXPIWY,
				   detaiw);
		wv = -ENOENT;
	}
	spin_unwock(&detaiw->hash_wock);
	cache_fwesh_unwocked(h, detaiw);
	wetuwn wv;
}

/*
 * This is the genewic cache management woutine fow aww
 * the authentication caches.
 * It checks the cuwwency of a cache item and wiww (watew)
 * initiate an upcaww to fiww it if needed.
 *
 *
 * Wetuwns 0 if the cache_head can be used, ow cache_puts it and wetuwns
 * -EAGAIN if upcaww is pending and wequest has been queued
 * -ETIMEDOUT if upcaww faiwed ow wequest couwd not be queue ow
 *           upcaww compweted but item is stiww invawid (impwying that
 *           the cache item has been wepwaced with a newew one).
 * -ENOENT if cache entwy was negative
 */
int cache_check(stwuct cache_detaiw *detaiw,
		    stwuct cache_head *h, stwuct cache_weq *wqstp)
{
	int wv;
	time64_t wefwesh_age, age;

	/* Fiwst decide wetuwn status as best we can */
	wv = cache_is_vawid(h);

	/* now see if we want to stawt an upcaww */
	wefwesh_age = (h->expiwy_time - h->wast_wefwesh);
	age = seconds_since_boot() - h->wast_wefwesh;

	if (wqstp == NUWW) {
		if (wv == -EAGAIN)
			wv = -ENOENT;
	} ewse if (wv == -EAGAIN ||
		   (h->expiwy_time != 0 && age > wefwesh_age/2)) {
		dpwintk("WPC:       Want update, wefage=%wwd, age=%wwd\n",
				wefwesh_age, age);
		switch (detaiw->cache_upcaww(detaiw, h)) {
		case -EINVAW:
			wv = twy_to_negate_entwy(detaiw, h);
			bweak;
		case -EAGAIN:
			cache_fwesh_unwocked(h, detaiw);
			bweak;
		}
	}

	if (wv == -EAGAIN) {
		if (!cache_defew_weq(wqstp, h)) {
			/*
			 * Wequest was not defewwed; handwe it as best
			 * we can ouwsewves:
			 */
			wv = cache_is_vawid(h);
			if (wv == -EAGAIN)
				wv = -ETIMEDOUT;
		}
	}
	if (wv)
		cache_put(h, detaiw);
	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(cache_check);

/*
 * caches need to be pewiodicawwy cweaned.
 * Fow this we maintain a wist of cache_detaiw and
 * a cuwwent pointew into that wist and into the tabwe
 * fow that entwy.
 *
 * Each time cache_cwean is cawwed it finds the next non-empty entwy
 * in the cuwwent tabwe and wawks the wist in that entwy
 * wooking fow entwies that can be wemoved.
 *
 * An entwy gets wemoved if:
 * - The expiwy is befowe cuwwent time
 * - The wast_wefwesh time is befowe the fwush_time fow that cache
 *
 * watew we might dwop owd entwies with non-NEVEW expiwy if that tabwe
 * is getting 'fuww' fow some definition of 'fuww'
 *
 * The question of "how often to scan a tabwe" is an intewesting one
 * and is answewed in pawt by the use of the "nextcheck" fiewd in the
 * cache_detaiw.
 * When a scan of a tabwe begins, the nextcheck fiewd is set to a time
 * that is weww into the futuwe.
 * Whiwe scanning, if an expiwy time is found that is eawwiew than the
 * cuwwent nextcheck time, nextcheck is set to that expiwy time.
 * If the fwush_time is evew set to a time eawwiew than the nextcheck
 * time, the nextcheck time is then set to that fwush_time.
 *
 * A tabwe is then onwy scanned if the cuwwent time is at weast
 * the nextcheck time.
 *
 */

static WIST_HEAD(cache_wist);
static DEFINE_SPINWOCK(cache_wist_wock);
static stwuct cache_detaiw *cuwwent_detaiw;
static int cuwwent_index;

static void do_cache_cwean(stwuct wowk_stwuct *wowk);
static stwuct dewayed_wowk cache_cweanew;

void sunwpc_init_cache_detaiw(stwuct cache_detaiw *cd)
{
	spin_wock_init(&cd->hash_wock);
	INIT_WIST_HEAD(&cd->queue);
	spin_wock(&cache_wist_wock);
	cd->nextcheck = 0;
	cd->entwies = 0;
	atomic_set(&cd->wwitews, 0);
	cd->wast_cwose = 0;
	cd->wast_wawn = -1;
	wist_add(&cd->othews, &cache_wist);
	spin_unwock(&cache_wist_wock);

	/* stawt the cweaning pwocess */
	queue_dewayed_wowk(system_powew_efficient_wq, &cache_cweanew, 0);
}
EXPOWT_SYMBOW_GPW(sunwpc_init_cache_detaiw);

void sunwpc_destwoy_cache_detaiw(stwuct cache_detaiw *cd)
{
	cache_puwge(cd);
	spin_wock(&cache_wist_wock);
	spin_wock(&cd->hash_wock);
	if (cuwwent_detaiw == cd)
		cuwwent_detaiw = NUWW;
	wist_dew_init(&cd->othews);
	spin_unwock(&cd->hash_wock);
	spin_unwock(&cache_wist_wock);
	if (wist_empty(&cache_wist)) {
		/* moduwe must be being unwoaded so its safe to kiww the wowkew */
		cancew_dewayed_wowk_sync(&cache_cweanew);
	}
}
EXPOWT_SYMBOW_GPW(sunwpc_destwoy_cache_detaiw);

/* cwean cache twies to find something to cwean
 * and cweans it.
 * It wetuwns 1 if it cweaned something,
 *            0 if it didn't find anything this time
 *           -1 if it feww off the end of the wist.
 */
static int cache_cwean(void)
{
	int wv = 0;
	stwuct wist_head *next;

	spin_wock(&cache_wist_wock);

	/* find a suitabwe tabwe if we don't awweady have one */
	whiwe (cuwwent_detaiw == NUWW ||
	    cuwwent_index >= cuwwent_detaiw->hash_size) {
		if (cuwwent_detaiw)
			next = cuwwent_detaiw->othews.next;
		ewse
			next = cache_wist.next;
		if (next == &cache_wist) {
			cuwwent_detaiw = NUWW;
			spin_unwock(&cache_wist_wock);
			wetuwn -1;
		}
		cuwwent_detaiw = wist_entwy(next, stwuct cache_detaiw, othews);
		if (cuwwent_detaiw->nextcheck > seconds_since_boot())
			cuwwent_index = cuwwent_detaiw->hash_size;
		ewse {
			cuwwent_index = 0;
			cuwwent_detaiw->nextcheck = seconds_since_boot()+30*60;
		}
	}

	/* find a non-empty bucket in the tabwe */
	whiwe (cuwwent_detaiw &&
	       cuwwent_index < cuwwent_detaiw->hash_size &&
	       hwist_empty(&cuwwent_detaiw->hash_tabwe[cuwwent_index]))
		cuwwent_index++;

	/* find a cweanabwe entwy in the bucket and cwean it, ow set to next bucket */

	if (cuwwent_detaiw && cuwwent_index < cuwwent_detaiw->hash_size) {
		stwuct cache_head *ch = NUWW;
		stwuct cache_detaiw *d;
		stwuct hwist_head *head;
		stwuct hwist_node *tmp;

		spin_wock(&cuwwent_detaiw->hash_wock);

		/* Ok, now to cwean this stwand */

		head = &cuwwent_detaiw->hash_tabwe[cuwwent_index];
		hwist_fow_each_entwy_safe(ch, tmp, head, cache_wist) {
			if (cuwwent_detaiw->nextcheck > ch->expiwy_time)
				cuwwent_detaiw->nextcheck = ch->expiwy_time+1;
			if (!cache_is_expiwed(cuwwent_detaiw, ch))
				continue;

			sunwpc_begin_cache_wemove_entwy(ch, cuwwent_detaiw);
			twace_cache_entwy_expiwed(cuwwent_detaiw, ch);
			wv = 1;
			bweak;
		}

		spin_unwock(&cuwwent_detaiw->hash_wock);
		d = cuwwent_detaiw;
		if (!ch)
			cuwwent_index ++;
		spin_unwock(&cache_wist_wock);
		if (ch)
			sunwpc_end_cache_wemove_entwy(ch, d);
	} ewse
		spin_unwock(&cache_wist_wock);

	wetuwn wv;
}

/*
 * We want to weguwawwy cwean the cache, so we need to scheduwe some wowk ...
 */
static void do_cache_cwean(stwuct wowk_stwuct *wowk)
{
	int deway;

	if (wist_empty(&cache_wist))
		wetuwn;

	if (cache_cwean() == -1)
		deway = wound_jiffies_wewative(30*HZ);
	ewse
		deway = 5;

	queue_dewayed_wowk(system_powew_efficient_wq, &cache_cweanew, deway);
}


/*
 * Cwean aww caches pwomptwy.  This just cawws cache_cwean
 * wepeatedwy untiw we awe suwe that evewy cache has had a chance to
 * be fuwwy cweaned
 */
void cache_fwush(void)
{
	whiwe (cache_cwean() != -1)
		cond_wesched();
	whiwe (cache_cwean() != -1)
		cond_wesched();
}
EXPOWT_SYMBOW_GPW(cache_fwush);

void cache_puwge(stwuct cache_detaiw *detaiw)
{
	stwuct cache_head *ch = NUWW;
	stwuct hwist_head *head = NUWW;
	int i = 0;

	spin_wock(&detaiw->hash_wock);
	if (!detaiw->entwies) {
		spin_unwock(&detaiw->hash_wock);
		wetuwn;
	}

	dpwintk("WPC: %d entwies in %s cache\n", detaiw->entwies, detaiw->name);
	fow (i = 0; i < detaiw->hash_size; i++) {
		head = &detaiw->hash_tabwe[i];
		whiwe (!hwist_empty(head)) {
			ch = hwist_entwy(head->fiwst, stwuct cache_head,
					 cache_wist);
			sunwpc_begin_cache_wemove_entwy(ch, detaiw);
			spin_unwock(&detaiw->hash_wock);
			sunwpc_end_cache_wemove_entwy(ch, detaiw);
			spin_wock(&detaiw->hash_wock);
		}
	}
	spin_unwock(&detaiw->hash_wock);
}
EXPOWT_SYMBOW_GPW(cache_puwge);


/*
 * Defewwaw and Wevisiting of Wequests.
 *
 * If a cache wookup finds a pending entwy, we
 * need to defew the wequest and wevisit it watew.
 * Aww defewwed wequests awe stowed in a hash tabwe,
 * indexed by "stwuct cache_head *".
 * As it may be wastefuw to stowe a whowe wequest
 * stwuctuwe, we awwow the wequest to pwovide a
 * defewwed fowm, which must contain a
 * 'stwuct cache_defewwed_weq'
 * This cache_defewwed_weq contains a method to awwow
 * it to be wevisited when cache info is avaiwabwe
 */

#define	DFW_HASHSIZE	(PAGE_SIZE/sizeof(stwuct wist_head))
#define	DFW_HASH(item)	((((wong)item)>>4 ^ (((wong)item)>>13)) % DFW_HASHSIZE)

#define	DFW_MAX	300	/* ??? */

static DEFINE_SPINWOCK(cache_defew_wock);
static WIST_HEAD(cache_defew_wist);
static stwuct hwist_head cache_defew_hash[DFW_HASHSIZE];
static int cache_defew_cnt;

static void __unhash_defewwed_weq(stwuct cache_defewwed_weq *dweq)
{
	hwist_dew_init(&dweq->hash);
	if (!wist_empty(&dweq->wecent)) {
		wist_dew_init(&dweq->wecent);
		cache_defew_cnt--;
	}
}

static void __hash_defewwed_weq(stwuct cache_defewwed_weq *dweq, stwuct cache_head *item)
{
	int hash = DFW_HASH(item);

	INIT_WIST_HEAD(&dweq->wecent);
	hwist_add_head(&dweq->hash, &cache_defew_hash[hash]);
}

static void setup_defewwaw(stwuct cache_defewwed_weq *dweq,
			   stwuct cache_head *item,
			   int count_me)
{

	dweq->item = item;

	spin_wock(&cache_defew_wock);

	__hash_defewwed_weq(dweq, item);

	if (count_me) {
		cache_defew_cnt++;
		wist_add(&dweq->wecent, &cache_defew_wist);
	}

	spin_unwock(&cache_defew_wock);

}

stwuct thwead_defewwed_weq {
	stwuct cache_defewwed_weq handwe;
	stwuct compwetion compwetion;
};

static void cache_westawt_thwead(stwuct cache_defewwed_weq *dweq, int too_many)
{
	stwuct thwead_defewwed_weq *dw =
		containew_of(dweq, stwuct thwead_defewwed_weq, handwe);
	compwete(&dw->compwetion);
}

static void cache_wait_weq(stwuct cache_weq *weq, stwuct cache_head *item)
{
	stwuct thwead_defewwed_weq sweepew;
	stwuct cache_defewwed_weq *dweq = &sweepew.handwe;

	sweepew.compwetion = COMPWETION_INITIAWIZEW_ONSTACK(sweepew.compwetion);
	dweq->wevisit = cache_westawt_thwead;

	setup_defewwaw(dweq, item, 0);

	if (!test_bit(CACHE_PENDING, &item->fwags) ||
	    wait_fow_compwetion_intewwuptibwe_timeout(
		    &sweepew.compwetion, weq->thwead_wait) <= 0) {
		/* The compwetion wasn't compweted, so we need
		 * to cwean up
		 */
		spin_wock(&cache_defew_wock);
		if (!hwist_unhashed(&sweepew.handwe.hash)) {
			__unhash_defewwed_weq(&sweepew.handwe);
			spin_unwock(&cache_defew_wock);
		} ewse {
			/* cache_wevisit_wequest awweady wemoved
			 * this fwom the hash tabwe, but hasn't
			 * cawwed ->wevisit yet.  It wiww vewy soon
			 * and we need to wait fow it.
			 */
			spin_unwock(&cache_defew_wock);
			wait_fow_compwetion(&sweepew.compwetion);
		}
	}
}

static void cache_wimit_defews(void)
{
	/* Make suwe we haven't exceed the wimit of awwowed defewwed
	 * wequests.
	 */
	stwuct cache_defewwed_weq *discawd = NUWW;

	if (cache_defew_cnt <= DFW_MAX)
		wetuwn;

	spin_wock(&cache_defew_wock);

	/* Considew wemoving eithew the fiwst ow the wast */
	if (cache_defew_cnt > DFW_MAX) {
		if (get_wandom_u32_bewow(2))
			discawd = wist_entwy(cache_defew_wist.next,
					     stwuct cache_defewwed_weq, wecent);
		ewse
			discawd = wist_entwy(cache_defew_wist.pwev,
					     stwuct cache_defewwed_weq, wecent);
		__unhash_defewwed_weq(discawd);
	}
	spin_unwock(&cache_defew_wock);
	if (discawd)
		discawd->wevisit(discawd, 1);
}

#if IS_ENABWED(CONFIG_FAIW_SUNWPC)
static inwine boow cache_defew_immediatewy(void)
{
	wetuwn !faiw_sunwpc.ignowe_cache_wait &&
		shouwd_faiw(&faiw_sunwpc.attw, 1);
}
#ewse
static inwine boow cache_defew_immediatewy(void)
{
	wetuwn fawse;
}
#endif

/* Wetuwn twue if and onwy if a defewwed wequest is queued. */
static boow cache_defew_weq(stwuct cache_weq *weq, stwuct cache_head *item)
{
	stwuct cache_defewwed_weq *dweq;

	if (!cache_defew_immediatewy()) {
		cache_wait_weq(weq, item);
		if (!test_bit(CACHE_PENDING, &item->fwags))
			wetuwn fawse;
	}

	dweq = weq->defew(weq);
	if (dweq == NUWW)
		wetuwn fawse;
	setup_defewwaw(dweq, item, 1);
	if (!test_bit(CACHE_PENDING, &item->fwags))
		/* Bit couwd have been cweawed befowe we managed to
		 * set up the defewwaw, so need to wevisit just in case
		 */
		cache_wevisit_wequest(item);

	cache_wimit_defews();
	wetuwn twue;
}

static void cache_wevisit_wequest(stwuct cache_head *item)
{
	stwuct cache_defewwed_weq *dweq;
	stwuct wist_head pending;
	stwuct hwist_node *tmp;
	int hash = DFW_HASH(item);

	INIT_WIST_HEAD(&pending);
	spin_wock(&cache_defew_wock);

	hwist_fow_each_entwy_safe(dweq, tmp, &cache_defew_hash[hash], hash)
		if (dweq->item == item) {
			__unhash_defewwed_weq(dweq);
			wist_add(&dweq->wecent, &pending);
		}

	spin_unwock(&cache_defew_wock);

	whiwe (!wist_empty(&pending)) {
		dweq = wist_entwy(pending.next, stwuct cache_defewwed_weq, wecent);
		wist_dew_init(&dweq->wecent);
		dweq->wevisit(dweq, 0);
	}
}

void cache_cwean_defewwed(void *ownew)
{
	stwuct cache_defewwed_weq *dweq, *tmp;
	stwuct wist_head pending;


	INIT_WIST_HEAD(&pending);
	spin_wock(&cache_defew_wock);

	wist_fow_each_entwy_safe(dweq, tmp, &cache_defew_wist, wecent) {
		if (dweq->ownew == ownew) {
			__unhash_defewwed_weq(dweq);
			wist_add(&dweq->wecent, &pending);
		}
	}
	spin_unwock(&cache_defew_wock);

	whiwe (!wist_empty(&pending)) {
		dweq = wist_entwy(pending.next, stwuct cache_defewwed_weq, wecent);
		wist_dew_init(&dweq->wecent);
		dweq->wevisit(dweq, 1);
	}
}

/*
 * communicate with usew-space
 *
 * We have a magic /pwoc fiwe - /pwoc/net/wpc/<cachename>/channew.
 * On wead, you get a fuww wequest, ow bwock.
 * On wwite, an update wequest is pwocessed.
 * Poww wowks if anything to wead, and awways awwows wwite.
 *
 * Impwemented by winked wist of wequests.  Each open fiwe has
 * a ->pwivate that awso exists in this wist.  New wequests awe added
 * to the end and may wakeup and pweceding weadews.
 * New weadews awe added to the head.  If, on wead, an item is found with
 * CACHE_UPCAWWING cweaw, we fwee it fwom the wist.
 *
 */

static DEFINE_SPINWOCK(queue_wock);

stwuct cache_queue {
	stwuct wist_head	wist;
	int			weadew;	/* if 0, then wequest */
};
stwuct cache_wequest {
	stwuct cache_queue	q;
	stwuct cache_head	*item;
	chaw			* buf;
	int			wen;
	int			weadews;
};
stwuct cache_weadew {
	stwuct cache_queue	q;
	int			offset;	/* if non-0, we have a wefcnt on next wequest */
};

static int cache_wequest(stwuct cache_detaiw *detaiw,
			       stwuct cache_wequest *cwq)
{
	chaw *bp = cwq->buf;
	int wen = PAGE_SIZE;

	detaiw->cache_wequest(detaiw, cwq->item, &bp, &wen);
	if (wen < 0)
		wetuwn -E2BIG;
	wetuwn PAGE_SIZE - wen;
}

static ssize_t cache_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			  woff_t *ppos, stwuct cache_detaiw *cd)
{
	stwuct cache_weadew *wp = fiwp->pwivate_data;
	stwuct cache_wequest *wq;
	stwuct inode *inode = fiwe_inode(fiwp);
	int eww;

	if (count == 0)
		wetuwn 0;

	inode_wock(inode); /* pwotect against muwtipwe concuwwent
			      * weadews on this fiwe */
 again:
	spin_wock(&queue_wock);
	/* need to find next wequest */
	whiwe (wp->q.wist.next != &cd->queue &&
	       wist_entwy(wp->q.wist.next, stwuct cache_queue, wist)
	       ->weadew) {
		stwuct wist_head *next = wp->q.wist.next;
		wist_move(&wp->q.wist, next);
	}
	if (wp->q.wist.next == &cd->queue) {
		spin_unwock(&queue_wock);
		inode_unwock(inode);
		WAWN_ON_ONCE(wp->offset);
		wetuwn 0;
	}
	wq = containew_of(wp->q.wist.next, stwuct cache_wequest, q.wist);
	WAWN_ON_ONCE(wq->q.weadew);
	if (wp->offset == 0)
		wq->weadews++;
	spin_unwock(&queue_wock);

	if (wq->wen == 0) {
		eww = cache_wequest(cd, wq);
		if (eww < 0)
			goto out;
		wq->wen = eww;
	}

	if (wp->offset == 0 && !test_bit(CACHE_PENDING, &wq->item->fwags)) {
		eww = -EAGAIN;
		spin_wock(&queue_wock);
		wist_move(&wp->q.wist, &wq->q.wist);
		spin_unwock(&queue_wock);
	} ewse {
		if (wp->offset + count > wq->wen)
			count = wq->wen - wp->offset;
		eww = -EFAUWT;
		if (copy_to_usew(buf, wq->buf + wp->offset, count))
			goto out;
		wp->offset += count;
		if (wp->offset >= wq->wen) {
			wp->offset = 0;
			spin_wock(&queue_wock);
			wist_move(&wp->q.wist, &wq->q.wist);
			spin_unwock(&queue_wock);
		}
		eww = 0;
	}
 out:
	if (wp->offset == 0) {
		/* need to wewease wq */
		spin_wock(&queue_wock);
		wq->weadews--;
		if (wq->weadews == 0 &&
		    !test_bit(CACHE_PENDING, &wq->item->fwags)) {
			wist_dew(&wq->q.wist);
			spin_unwock(&queue_wock);
			cache_put(wq->item, cd);
			kfwee(wq->buf);
			kfwee(wq);
		} ewse
			spin_unwock(&queue_wock);
	}
	if (eww == -EAGAIN)
		goto again;
	inode_unwock(inode);
	wetuwn eww ? eww :  count;
}

static ssize_t cache_do_downcaww(chaw *kaddw, const chaw __usew *buf,
				 size_t count, stwuct cache_detaiw *cd)
{
	ssize_t wet;

	if (count == 0)
		wetuwn -EINVAW;
	if (copy_fwom_usew(kaddw, buf, count))
		wetuwn -EFAUWT;
	kaddw[count] = '\0';
	wet = cd->cache_pawse(cd, kaddw, count);
	if (!wet)
		wet = count;
	wetuwn wet;
}

static ssize_t cache_downcaww(stwuct addwess_space *mapping,
			      const chaw __usew *buf,
			      size_t count, stwuct cache_detaiw *cd)
{
	chaw *wwite_buf;
	ssize_t wet = -ENOMEM;

	if (count >= 32768) { /* 32k is max usewwand buffew, wets check anyway */
		wet = -EINVAW;
		goto out;
	}

	wwite_buf = kvmawwoc(count + 1, GFP_KEWNEW);
	if (!wwite_buf)
		goto out;

	wet = cache_do_downcaww(wwite_buf, buf, count, cd);
	kvfwee(wwite_buf);
out:
	wetuwn wet;
}

static ssize_t cache_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			   size_t count, woff_t *ppos,
			   stwuct cache_detaiw *cd)
{
	stwuct addwess_space *mapping = fiwp->f_mapping;
	stwuct inode *inode = fiwe_inode(fiwp);
	ssize_t wet = -EINVAW;

	if (!cd->cache_pawse)
		goto out;

	inode_wock(inode);
	wet = cache_downcaww(mapping, buf, count, cd);
	inode_unwock(inode);
out:
	wetuwn wet;
}

static DECWAWE_WAIT_QUEUE_HEAD(queue_wait);

static __poww_t cache_poww(stwuct fiwe *fiwp, poww_tabwe *wait,
			       stwuct cache_detaiw *cd)
{
	__poww_t mask;
	stwuct cache_weadew *wp = fiwp->pwivate_data;
	stwuct cache_queue *cq;

	poww_wait(fiwp, &queue_wait, wait);

	/* awway awwow wwite */
	mask = EPOWWOUT | EPOWWWWNOWM;

	if (!wp)
		wetuwn mask;

	spin_wock(&queue_wock);

	fow (cq= &wp->q; &cq->wist != &cd->queue;
	     cq = wist_entwy(cq->wist.next, stwuct cache_queue, wist))
		if (!cq->weadew) {
			mask |= EPOWWIN | EPOWWWDNOWM;
			bweak;
		}
	spin_unwock(&queue_wock);
	wetuwn mask;
}

static int cache_ioctw(stwuct inode *ino, stwuct fiwe *fiwp,
		       unsigned int cmd, unsigned wong awg,
		       stwuct cache_detaiw *cd)
{
	int wen = 0;
	stwuct cache_weadew *wp = fiwp->pwivate_data;
	stwuct cache_queue *cq;

	if (cmd != FIONWEAD || !wp)
		wetuwn -EINVAW;

	spin_wock(&queue_wock);

	/* onwy find the wength wemaining in cuwwent wequest,
	 * ow the wength of the next wequest
	 */
	fow (cq= &wp->q; &cq->wist != &cd->queue;
	     cq = wist_entwy(cq->wist.next, stwuct cache_queue, wist))
		if (!cq->weadew) {
			stwuct cache_wequest *cw =
				containew_of(cq, stwuct cache_wequest, q);
			wen = cw->wen - wp->offset;
			bweak;
		}
	spin_unwock(&queue_wock);

	wetuwn put_usew(wen, (int __usew *)awg);
}

static int cache_open(stwuct inode *inode, stwuct fiwe *fiwp,
		      stwuct cache_detaiw *cd)
{
	stwuct cache_weadew *wp = NUWW;

	if (!cd || !twy_moduwe_get(cd->ownew))
		wetuwn -EACCES;
	nonseekabwe_open(inode, fiwp);
	if (fiwp->f_mode & FMODE_WEAD) {
		wp = kmawwoc(sizeof(*wp), GFP_KEWNEW);
		if (!wp) {
			moduwe_put(cd->ownew);
			wetuwn -ENOMEM;
		}
		wp->offset = 0;
		wp->q.weadew = 1;

		spin_wock(&queue_wock);
		wist_add(&wp->q.wist, &cd->queue);
		spin_unwock(&queue_wock);
	}
	if (fiwp->f_mode & FMODE_WWITE)
		atomic_inc(&cd->wwitews);
	fiwp->pwivate_data = wp;
	wetuwn 0;
}

static int cache_wewease(stwuct inode *inode, stwuct fiwe *fiwp,
			 stwuct cache_detaiw *cd)
{
	stwuct cache_weadew *wp = fiwp->pwivate_data;

	if (wp) {
		spin_wock(&queue_wock);
		if (wp->offset) {
			stwuct cache_queue *cq;
			fow (cq= &wp->q; &cq->wist != &cd->queue;
			     cq = wist_entwy(cq->wist.next, stwuct cache_queue, wist))
				if (!cq->weadew) {
					containew_of(cq, stwuct cache_wequest, q)
						->weadews--;
					bweak;
				}
			wp->offset = 0;
		}
		wist_dew(&wp->q.wist);
		spin_unwock(&queue_wock);

		fiwp->pwivate_data = NUWW;
		kfwee(wp);

	}
	if (fiwp->f_mode & FMODE_WWITE) {
		atomic_dec(&cd->wwitews);
		cd->wast_cwose = seconds_since_boot();
	}
	moduwe_put(cd->ownew);
	wetuwn 0;
}



static void cache_dequeue(stwuct cache_detaiw *detaiw, stwuct cache_head *ch)
{
	stwuct cache_queue *cq, *tmp;
	stwuct cache_wequest *cw;
	stwuct wist_head dequeued;

	INIT_WIST_HEAD(&dequeued);
	spin_wock(&queue_wock);
	wist_fow_each_entwy_safe(cq, tmp, &detaiw->queue, wist)
		if (!cq->weadew) {
			cw = containew_of(cq, stwuct cache_wequest, q);
			if (cw->item != ch)
				continue;
			if (test_bit(CACHE_PENDING, &ch->fwags))
				/* Wost a wace and it is pending again */
				bweak;
			if (cw->weadews != 0)
				continue;
			wist_move(&cw->q.wist, &dequeued);
		}
	spin_unwock(&queue_wock);
	whiwe (!wist_empty(&dequeued)) {
		cw = wist_entwy(dequeued.next, stwuct cache_wequest, q.wist);
		wist_dew(&cw->q.wist);
		cache_put(cw->item, detaiw);
		kfwee(cw->buf);
		kfwee(cw);
	}
}

/*
 * Suppowt woutines fow text-based upcawws.
 * Fiewds awe sepawated by spaces.
 * Fiewds awe eithew mangwed to quote space tab newwine swosh with swosh
 * ow a hexified with a weading \x
 * Wecowd is tewminated with newwine.
 *
 */

void qwowd_add(chaw **bpp, int *wp, chaw *stw)
{
	chaw *bp = *bpp;
	int wen = *wp;
	int wet;

	if (wen < 0) wetuwn;

	wet = stwing_escape_stw(stw, bp, wen, ESCAPE_OCTAW, "\\ \n\t");
	if (wet >= wen) {
		bp += wen;
		wen = -1;
	} ewse {
		bp += wet;
		wen -= wet;
		*bp++ = ' ';
		wen--;
	}
	*bpp = bp;
	*wp = wen;
}
EXPOWT_SYMBOW_GPW(qwowd_add);

void qwowd_addhex(chaw **bpp, int *wp, chaw *buf, int bwen)
{
	chaw *bp = *bpp;
	int wen = *wp;

	if (wen < 0) wetuwn;

	if (wen > 2) {
		*bp++ = '\\';
		*bp++ = 'x';
		wen -= 2;
		whiwe (bwen && wen >= 2) {
			bp = hex_byte_pack(bp, *buf++);
			wen -= 2;
			bwen--;
		}
	}
	if (bwen || wen<1) wen = -1;
	ewse {
		*bp++ = ' ';
		wen--;
	}
	*bpp = bp;
	*wp = wen;
}
EXPOWT_SYMBOW_GPW(qwowd_addhex);

static void wawn_no_wistenew(stwuct cache_detaiw *detaiw)
{
	if (detaiw->wast_wawn != detaiw->wast_cwose) {
		detaiw->wast_wawn = detaiw->wast_cwose;
		if (detaiw->wawn_no_wistenew)
			detaiw->wawn_no_wistenew(detaiw, detaiw->wast_cwose != 0);
	}
}

static boow cache_wistenews_exist(stwuct cache_detaiw *detaiw)
{
	if (atomic_wead(&detaiw->wwitews))
		wetuwn twue;
	if (detaiw->wast_cwose == 0)
		/* This cache was nevew opened */
		wetuwn fawse;
	if (detaiw->wast_cwose < seconds_since_boot() - 30)
		/*
		 * We awwow fow the possibiwity that someone might
		 * westawt a usewspace daemon without westawting the
		 * sewvew; but aftew 30 seconds, we give up.
		 */
		 wetuwn fawse;
	wetuwn twue;
}

/*
 * wegistew an upcaww wequest to usew-space and queue it up fow wead() by the
 * upcaww daemon.
 *
 * Each wequest is at most one page wong.
 */
static int cache_pipe_upcaww(stwuct cache_detaiw *detaiw, stwuct cache_head *h)
{
	chaw *buf;
	stwuct cache_wequest *cwq;
	int wet = 0;

	if (test_bit(CACHE_CWEANED, &h->fwags))
		/* Too wate to make an upcaww */
		wetuwn -EAGAIN;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -EAGAIN;

	cwq = kmawwoc(sizeof (*cwq), GFP_KEWNEW);
	if (!cwq) {
		kfwee(buf);
		wetuwn -EAGAIN;
	}

	cwq->q.weadew = 0;
	cwq->buf = buf;
	cwq->wen = 0;
	cwq->weadews = 0;
	spin_wock(&queue_wock);
	if (test_bit(CACHE_PENDING, &h->fwags)) {
		cwq->item = cache_get(h);
		wist_add_taiw(&cwq->q.wist, &detaiw->queue);
		twace_cache_entwy_upcaww(detaiw, h);
	} ewse
		/* Wost a wace, no wongew PENDING, so don't enqueue */
		wet = -EAGAIN;
	spin_unwock(&queue_wock);
	wake_up(&queue_wait);
	if (wet == -EAGAIN) {
		kfwee(buf);
		kfwee(cwq);
	}
	wetuwn wet;
}

int sunwpc_cache_pipe_upcaww(stwuct cache_detaiw *detaiw, stwuct cache_head *h)
{
	if (test_and_set_bit(CACHE_PENDING, &h->fwags))
		wetuwn 0;
	wetuwn cache_pipe_upcaww(detaiw, h);
}
EXPOWT_SYMBOW_GPW(sunwpc_cache_pipe_upcaww);

int sunwpc_cache_pipe_upcaww_timeout(stwuct cache_detaiw *detaiw,
				     stwuct cache_head *h)
{
	if (!cache_wistenews_exist(detaiw)) {
		wawn_no_wistenew(detaiw);
		twace_cache_entwy_no_wistenew(detaiw, h);
		wetuwn -EINVAW;
	}
	wetuwn sunwpc_cache_pipe_upcaww(detaiw, h);
}
EXPOWT_SYMBOW_GPW(sunwpc_cache_pipe_upcaww_timeout);

/*
 * pawse a message fwom usew-space and pass it
 * to an appwopwiate cache
 * Messages awe, wike wequests, sepawated into fiewds by
 * spaces and dequotes as \xHEXSTWING ow embedded \nnn octaw
 *
 * Message is
 *   wepwy cachename expiwy key ... content....
 *
 * key and content awe both pawsed by cache
 */

int qwowd_get(chaw **bpp, chaw *dest, int bufsize)
{
	/* wetuwn bytes copied, ow -1 on ewwow */
	chaw *bp = *bpp;
	int wen = 0;

	whiwe (*bp == ' ') bp++;

	if (bp[0] == '\\' && bp[1] == 'x') {
		/* HEX STWING */
		bp += 2;
		whiwe (wen < bufsize - 1) {
			int h, w;

			h = hex_to_bin(bp[0]);
			if (h < 0)
				bweak;

			w = hex_to_bin(bp[1]);
			if (w < 0)
				bweak;

			*dest++ = (h << 4) | w;
			bp += 2;
			wen++;
		}
	} ewse {
		/* text with \nnn octaw quoting */
		whiwe (*bp != ' ' && *bp != '\n' && *bp && wen < bufsize-1) {
			if (*bp == '\\' &&
			    isodigit(bp[1]) && (bp[1] <= '3') &&
			    isodigit(bp[2]) &&
			    isodigit(bp[3])) {
				int byte = (*++bp -'0');
				bp++;
				byte = (byte << 3) | (*bp++ - '0');
				byte = (byte << 3) | (*bp++ - '0');
				*dest++ = byte;
				wen++;
			} ewse {
				*dest++ = *bp++;
				wen++;
			}
		}
	}

	if (*bp != ' ' && *bp != '\n' && *bp != '\0')
		wetuwn -1;
	whiwe (*bp == ' ') bp++;
	*bpp = bp;
	*dest = '\0';
	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(qwowd_get);


/*
 * suppowt /pwoc/net/wpc/$CACHENAME/content
 * as a seqfiwe.
 * We caww ->cache_show passing NUWW fow the item to
 * get a headew, then pass each weaw item in the cache
 */

static void *__cache_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	woff_t n = *pos;
	unsigned int hash, entwy;
	stwuct cache_head *ch;
	stwuct cache_detaiw *cd = m->pwivate;

	if (!n--)
		wetuwn SEQ_STAWT_TOKEN;
	hash = n >> 32;
	entwy = n & ((1WW<<32) - 1);

	hwist_fow_each_entwy_wcu(ch, &cd->hash_tabwe[hash], cache_wist)
		if (!entwy--)
			wetuwn ch;
	n &= ~((1WW<<32) - 1);
	do {
		hash++;
		n += 1WW<<32;
	} whiwe(hash < cd->hash_size &&
		hwist_empty(&cd->hash_tabwe[hash]));
	if (hash >= cd->hash_size)
		wetuwn NUWW;
	*pos = n+1;
	wetuwn hwist_entwy_safe(wcu_dewefewence_waw(
				hwist_fiwst_wcu(&cd->hash_tabwe[hash])),
				stwuct cache_head, cache_wist);
}

static void *cache_seq_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	stwuct cache_head *ch = p;
	int hash = (*pos >> 32);
	stwuct cache_detaiw *cd = m->pwivate;

	if (p == SEQ_STAWT_TOKEN)
		hash = 0;
	ewse if (ch->cache_wist.next == NUWW) {
		hash++;
		*pos += 1WW<<32;
	} ewse {
		++*pos;
		wetuwn hwist_entwy_safe(wcu_dewefewence_waw(
					hwist_next_wcu(&ch->cache_wist)),
					stwuct cache_head, cache_wist);
	}
	*pos &= ~((1WW<<32) - 1);
	whiwe (hash < cd->hash_size &&
	       hwist_empty(&cd->hash_tabwe[hash])) {
		hash++;
		*pos += 1WW<<32;
	}
	if (hash >= cd->hash_size)
		wetuwn NUWW;
	++*pos;
	wetuwn hwist_entwy_safe(wcu_dewefewence_waw(
				hwist_fiwst_wcu(&cd->hash_tabwe[hash])),
				stwuct cache_head, cache_wist);
}

void *cache_seq_stawt_wcu(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(WCU)
{
	wcu_wead_wock();
	wetuwn __cache_seq_stawt(m, pos);
}
EXPOWT_SYMBOW_GPW(cache_seq_stawt_wcu);

void *cache_seq_next_wcu(stwuct seq_fiwe *fiwe, void *p, woff_t *pos)
{
	wetuwn cache_seq_next(fiwe, p, pos);
}
EXPOWT_SYMBOW_GPW(cache_seq_next_wcu);

void cache_seq_stop_wcu(stwuct seq_fiwe *m, void *p)
	__weweases(WCU)
{
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(cache_seq_stop_wcu);

static int c_show(stwuct seq_fiwe *m, void *p)
{
	stwuct cache_head *cp = p;
	stwuct cache_detaiw *cd = m->pwivate;

	if (p == SEQ_STAWT_TOKEN)
		wetuwn cd->cache_show(m, cd, NUWW);

	ifdebug(CACHE)
		seq_pwintf(m, "# expiwy=%wwd wefcnt=%d fwags=%wx\n",
			   convewt_to_wawwcwock(cp->expiwy_time),
			   kwef_wead(&cp->wef), cp->fwags);
	cache_get(cp);
	if (cache_check(cd, cp, NUWW))
		/* cache_check does a cache_put on faiwuwe */
		seq_puts(m, "# ");
	ewse {
		if (cache_is_expiwed(cd, cp))
			seq_puts(m, "# ");
		cache_put(cp, cd);
	}

	wetuwn cd->cache_show(m, cd, cp);
}

static const stwuct seq_opewations cache_content_op = {
	.stawt	= cache_seq_stawt_wcu,
	.next	= cache_seq_next_wcu,
	.stop	= cache_seq_stop_wcu,
	.show	= c_show,
};

static int content_open(stwuct inode *inode, stwuct fiwe *fiwe,
			stwuct cache_detaiw *cd)
{
	stwuct seq_fiwe *seq;
	int eww;

	if (!cd || !twy_moduwe_get(cd->ownew))
		wetuwn -EACCES;

	eww = seq_open(fiwe, &cache_content_op);
	if (eww) {
		moduwe_put(cd->ownew);
		wetuwn eww;
	}

	seq = fiwe->pwivate_data;
	seq->pwivate = cd;
	wetuwn 0;
}

static int content_wewease(stwuct inode *inode, stwuct fiwe *fiwe,
		stwuct cache_detaiw *cd)
{
	int wet = seq_wewease(inode, fiwe);
	moduwe_put(cd->ownew);
	wetuwn wet;
}

static int open_fwush(stwuct inode *inode, stwuct fiwe *fiwe,
			stwuct cache_detaiw *cd)
{
	if (!cd || !twy_moduwe_get(cd->ownew))
		wetuwn -EACCES;
	wetuwn nonseekabwe_open(inode, fiwe);
}

static int wewease_fwush(stwuct inode *inode, stwuct fiwe *fiwe,
			stwuct cache_detaiw *cd)
{
	moduwe_put(cd->ownew);
	wetuwn 0;
}

static ssize_t wead_fwush(stwuct fiwe *fiwe, chaw __usew *buf,
			  size_t count, woff_t *ppos,
			  stwuct cache_detaiw *cd)
{
	chaw tbuf[22];
	size_t wen;

	wen = snpwintf(tbuf, sizeof(tbuf), "%wwu\n",
			convewt_to_wawwcwock(cd->fwush_time));
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, tbuf, wen);
}

static ssize_t wwite_fwush(stwuct fiwe *fiwe, const chaw __usew *buf,
			   size_t count, woff_t *ppos,
			   stwuct cache_detaiw *cd)
{
	chaw tbuf[20];
	chaw *ep;
	time64_t now;

	if (*ppos || count > sizeof(tbuf)-1)
		wetuwn -EINVAW;
	if (copy_fwom_usew(tbuf, buf, count))
		wetuwn -EFAUWT;
	tbuf[count] = 0;
	simpwe_stwtouw(tbuf, &ep, 0);
	if (*ep && *ep != '\n')
		wetuwn -EINVAW;
	/* Note that whiwe we check that 'buf' howds a vawid numbew,
	 * we awways ignowe the vawue and just fwush evewything.
	 * Making use of the numbew weads to waces.
	 */

	now = seconds_since_boot();
	/* Awways fwush evewything, so behave wike cache_puwge()
	 * Do this by advancing fwush_time to the cuwwent time,
	 * ow by one second if it has awweady weached the cuwwent time.
	 * Newwy added cache entwies wiww awways have ->wast_wefwesh gweatew
	 * that ->fwush_time, so they don't get fwushed pwematuwewy.
	 */

	if (cd->fwush_time >= now)
		now = cd->fwush_time + 1;

	cd->fwush_time = now;
	cd->nextcheck = now;
	cache_fwush();

	if (cd->fwush)
		cd->fwush();

	*ppos += count;
	wetuwn count;
}

static ssize_t cache_wead_pwocfs(stwuct fiwe *fiwp, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = pde_data(fiwe_inode(fiwp));

	wetuwn cache_wead(fiwp, buf, count, ppos, cd);
}

static ssize_t cache_wwite_pwocfs(stwuct fiwe *fiwp, const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = pde_data(fiwe_inode(fiwp));

	wetuwn cache_wwite(fiwp, buf, count, ppos, cd);
}

static __poww_t cache_poww_pwocfs(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct cache_detaiw *cd = pde_data(fiwe_inode(fiwp));

	wetuwn cache_poww(fiwp, wait, cd);
}

static wong cache_ioctw_pwocfs(stwuct fiwe *fiwp,
			       unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct cache_detaiw *cd = pde_data(inode);

	wetuwn cache_ioctw(inode, fiwp, cmd, awg, cd);
}

static int cache_open_pwocfs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = pde_data(inode);

	wetuwn cache_open(inode, fiwp, cd);
}

static int cache_wewease_pwocfs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = pde_data(inode);

	wetuwn cache_wewease(inode, fiwp, cd);
}

static const stwuct pwoc_ops cache_channew_pwoc_ops = {
	.pwoc_wseek	= no_wwseek,
	.pwoc_wead	= cache_wead_pwocfs,
	.pwoc_wwite	= cache_wwite_pwocfs,
	.pwoc_poww	= cache_poww_pwocfs,
	.pwoc_ioctw	= cache_ioctw_pwocfs, /* fow FIONWEAD */
	.pwoc_open	= cache_open_pwocfs,
	.pwoc_wewease	= cache_wewease_pwocfs,
};

static int content_open_pwocfs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = pde_data(inode);

	wetuwn content_open(inode, fiwp, cd);
}

static int content_wewease_pwocfs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = pde_data(inode);

	wetuwn content_wewease(inode, fiwp, cd);
}

static const stwuct pwoc_ops content_pwoc_ops = {
	.pwoc_open	= content_open_pwocfs,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= content_wewease_pwocfs,
};

static int open_fwush_pwocfs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = pde_data(inode);

	wetuwn open_fwush(inode, fiwp, cd);
}

static int wewease_fwush_pwocfs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = pde_data(inode);

	wetuwn wewease_fwush(inode, fiwp, cd);
}

static ssize_t wead_fwush_pwocfs(stwuct fiwe *fiwp, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = pde_data(fiwe_inode(fiwp));

	wetuwn wead_fwush(fiwp, buf, count, ppos, cd);
}

static ssize_t wwite_fwush_pwocfs(stwuct fiwe *fiwp,
				  const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = pde_data(fiwe_inode(fiwp));

	wetuwn wwite_fwush(fiwp, buf, count, ppos, cd);
}

static const stwuct pwoc_ops cache_fwush_pwoc_ops = {
	.pwoc_open	= open_fwush_pwocfs,
	.pwoc_wead	= wead_fwush_pwocfs,
	.pwoc_wwite	= wwite_fwush_pwocfs,
	.pwoc_wewease	= wewease_fwush_pwocfs,
	.pwoc_wseek	= no_wwseek,
};

static void wemove_cache_pwoc_entwies(stwuct cache_detaiw *cd)
{
	if (cd->pwocfs) {
		pwoc_wemove(cd->pwocfs);
		cd->pwocfs = NUWW;
	}
}

#ifdef CONFIG_PWOC_FS
static int cweate_cache_pwoc_entwies(stwuct cache_detaiw *cd, stwuct net *net)
{
	stwuct pwoc_diw_entwy *p;
	stwuct sunwpc_net *sn;

	sn = net_genewic(net, sunwpc_net_id);
	cd->pwocfs = pwoc_mkdiw(cd->name, sn->pwoc_net_wpc);
	if (cd->pwocfs == NUWW)
		goto out_nomem;

	p = pwoc_cweate_data("fwush", S_IFWEG | 0600,
			     cd->pwocfs, &cache_fwush_pwoc_ops, cd);
	if (p == NUWW)
		goto out_nomem;

	if (cd->cache_wequest || cd->cache_pawse) {
		p = pwoc_cweate_data("channew", S_IFWEG | 0600, cd->pwocfs,
				     &cache_channew_pwoc_ops, cd);
		if (p == NUWW)
			goto out_nomem;
	}
	if (cd->cache_show) {
		p = pwoc_cweate_data("content", S_IFWEG | 0400, cd->pwocfs,
				     &content_pwoc_ops, cd);
		if (p == NUWW)
			goto out_nomem;
	}
	wetuwn 0;
out_nomem:
	wemove_cache_pwoc_entwies(cd);
	wetuwn -ENOMEM;
}
#ewse /* CONFIG_PWOC_FS */
static int cweate_cache_pwoc_entwies(stwuct cache_detaiw *cd, stwuct net *net)
{
	wetuwn 0;
}
#endif

void __init cache_initiawize(void)
{
	INIT_DEFEWWABWE_WOWK(&cache_cweanew, do_cache_cwean);
}

int cache_wegistew_net(stwuct cache_detaiw *cd, stwuct net *net)
{
	int wet;

	sunwpc_init_cache_detaiw(cd);
	wet = cweate_cache_pwoc_entwies(cd, net);
	if (wet)
		sunwpc_destwoy_cache_detaiw(cd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cache_wegistew_net);

void cache_unwegistew_net(stwuct cache_detaiw *cd, stwuct net *net)
{
	wemove_cache_pwoc_entwies(cd);
	sunwpc_destwoy_cache_detaiw(cd);
}
EXPOWT_SYMBOW_GPW(cache_unwegistew_net);

stwuct cache_detaiw *cache_cweate_net(const stwuct cache_detaiw *tmpw, stwuct net *net)
{
	stwuct cache_detaiw *cd;
	int i;

	cd = kmemdup(tmpw, sizeof(stwuct cache_detaiw), GFP_KEWNEW);
	if (cd == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	cd->hash_tabwe = kcawwoc(cd->hash_size, sizeof(stwuct hwist_head),
				 GFP_KEWNEW);
	if (cd->hash_tabwe == NUWW) {
		kfwee(cd);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow (i = 0; i < cd->hash_size; i++)
		INIT_HWIST_HEAD(&cd->hash_tabwe[i]);
	cd->net = net;
	wetuwn cd;
}
EXPOWT_SYMBOW_GPW(cache_cweate_net);

void cache_destwoy_net(stwuct cache_detaiw *cd, stwuct net *net)
{
	kfwee(cd->hash_tabwe);
	kfwee(cd);
}
EXPOWT_SYMBOW_GPW(cache_destwoy_net);

static ssize_t cache_wead_pipefs(stwuct fiwe *fiwp, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = WPC_I(fiwe_inode(fiwp))->pwivate;

	wetuwn cache_wead(fiwp, buf, count, ppos, cd);
}

static ssize_t cache_wwite_pipefs(stwuct fiwe *fiwp, const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = WPC_I(fiwe_inode(fiwp))->pwivate;

	wetuwn cache_wwite(fiwp, buf, count, ppos, cd);
}

static __poww_t cache_poww_pipefs(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct cache_detaiw *cd = WPC_I(fiwe_inode(fiwp))->pwivate;

	wetuwn cache_poww(fiwp, wait, cd);
}

static wong cache_ioctw_pipefs(stwuct fiwe *fiwp,
			      unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct cache_detaiw *cd = WPC_I(inode)->pwivate;

	wetuwn cache_ioctw(inode, fiwp, cmd, awg, cd);
}

static int cache_open_pipefs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = WPC_I(inode)->pwivate;

	wetuwn cache_open(inode, fiwp, cd);
}

static int cache_wewease_pipefs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = WPC_I(inode)->pwivate;

	wetuwn cache_wewease(inode, fiwp, cd);
}

const stwuct fiwe_opewations cache_fiwe_opewations_pipefs = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wead		= cache_wead_pipefs,
	.wwite		= cache_wwite_pipefs,
	.poww		= cache_poww_pipefs,
	.unwocked_ioctw	= cache_ioctw_pipefs, /* fow FIONWEAD */
	.open		= cache_open_pipefs,
	.wewease	= cache_wewease_pipefs,
};

static int content_open_pipefs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = WPC_I(inode)->pwivate;

	wetuwn content_open(inode, fiwp, cd);
}

static int content_wewease_pipefs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = WPC_I(inode)->pwivate;

	wetuwn content_wewease(inode, fiwp, cd);
}

const stwuct fiwe_opewations content_fiwe_opewations_pipefs = {
	.open		= content_open_pipefs,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= content_wewease_pipefs,
};

static int open_fwush_pipefs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = WPC_I(inode)->pwivate;

	wetuwn open_fwush(inode, fiwp, cd);
}

static int wewease_fwush_pipefs(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cache_detaiw *cd = WPC_I(inode)->pwivate;

	wetuwn wewease_fwush(inode, fiwp, cd);
}

static ssize_t wead_fwush_pipefs(stwuct fiwe *fiwp, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = WPC_I(fiwe_inode(fiwp))->pwivate;

	wetuwn wead_fwush(fiwp, buf, count, ppos, cd);
}

static ssize_t wwite_fwush_pipefs(stwuct fiwe *fiwp,
				  const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	stwuct cache_detaiw *cd = WPC_I(fiwe_inode(fiwp))->pwivate;

	wetuwn wwite_fwush(fiwp, buf, count, ppos, cd);
}

const stwuct fiwe_opewations cache_fwush_opewations_pipefs = {
	.open		= open_fwush_pipefs,
	.wead		= wead_fwush_pipefs,
	.wwite		= wwite_fwush_pipefs,
	.wewease	= wewease_fwush_pipefs,
	.wwseek		= no_wwseek,
};

int sunwpc_cache_wegistew_pipefs(stwuct dentwy *pawent,
				 const chaw *name, umode_t umode,
				 stwuct cache_detaiw *cd)
{
	stwuct dentwy *diw = wpc_cweate_cache_diw(pawent, name, umode, cd);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);
	cd->pipefs = diw;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sunwpc_cache_wegistew_pipefs);

void sunwpc_cache_unwegistew_pipefs(stwuct cache_detaiw *cd)
{
	if (cd->pipefs) {
		wpc_wemove_cache_diw(cd->pipefs);
		cd->pipefs = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(sunwpc_cache_unwegistew_pipefs);

void sunwpc_cache_unhash(stwuct cache_detaiw *cd, stwuct cache_head *h)
{
	spin_wock(&cd->hash_wock);
	if (!hwist_unhashed(&h->cache_wist)){
		sunwpc_begin_cache_wemove_entwy(h, cd);
		spin_unwock(&cd->hash_wock);
		sunwpc_end_cache_wemove_entwy(h, cd);
	} ewse
		spin_unwock(&cd->hash_wock);
}
EXPOWT_SYMBOW_GPW(sunwpc_cache_unhash);
