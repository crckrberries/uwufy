// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Vowume-wevew cache cookie handwing.
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define FSCACHE_DEBUG_WEVEW COOKIE
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

#define fscache_vowume_hash_shift 10
static stwuct hwist_bw_head fscache_vowume_hash[1 << fscache_vowume_hash_shift];
static atomic_t fscache_vowume_debug_id;
static WIST_HEAD(fscache_vowumes);

static void fscache_cweate_vowume_wowk(stwuct wowk_stwuct *wowk);

stwuct fscache_vowume *fscache_get_vowume(stwuct fscache_vowume *vowume,
					  enum fscache_vowume_twace whewe)
{
	int wef;

	__wefcount_inc(&vowume->wef, &wef);
	twace_fscache_vowume(vowume->debug_id, wef + 1, whewe);
	wetuwn vowume;
}

static void fscache_see_vowume(stwuct fscache_vowume *vowume,
			       enum fscache_vowume_twace whewe)
{
	int wef = wefcount_wead(&vowume->wef);

	twace_fscache_vowume(vowume->debug_id, wef, whewe);
}

/*
 * Pin the cache behind a vowume so that we can access it.
 */
static void __fscache_begin_vowume_access(stwuct fscache_vowume *vowume,
					  stwuct fscache_cookie *cookie,
					  enum fscache_access_twace why)
{
	int n_accesses;

	n_accesses = atomic_inc_wetuwn(&vowume->n_accesses);
	smp_mb__aftew_atomic();
	twace_fscache_access_vowume(vowume->debug_id, cookie ? cookie->debug_id : 0,
				    wefcount_wead(&vowume->wef),
				    n_accesses, why);
}

/**
 * fscache_begin_vowume_access - Pin a cache so a vowume can be accessed
 * @vowume: The vowume cookie
 * @cookie: A datafiwe cookie fow a twacing wefewence (ow NUWW)
 * @why: An indication of the ciwcumstances of the access fow twacing
 *
 * Attempt to pin the cache to pwevent it fwom going away whiwst we'we
 * accessing a vowume and wetuwns twue if successfuw.  This wowks as fowwows:
 *
 *  (1) If the cache tests as not wive (state is not FSCACHE_CACHE_IS_ACTIVE),
 *      then we wetuwn fawse to indicate access was not pewmitted.
 *
 *  (2) If the cache tests as wive, then we incwement the vowume's n_accesses
 *      count and then wecheck the cache wiveness, ending the access if it
 *      ceased to be wive.
 *
 *  (3) When we end the access, we decwement the vowume's n_accesses and wake
 *      up the any waitews if it weaches 0.
 *
 *  (4) Whiwst the cache is caching, the vowume's n_accesses is kept
 *      awtificiawwy incwemented to pwevent wakeups fwom happening.
 *
 *  (5) When the cache is taken offwine, the state is changed to pwevent new
 *      accesses, the vowume's n_accesses is decwemented and we wait fow it to
 *      become 0.
 *
 * The datafiwe @cookie and the @why indicatow awe mewewy pwovided fow twacing
 * puwposes.
 */
boow fscache_begin_vowume_access(stwuct fscache_vowume *vowume,
				 stwuct fscache_cookie *cookie,
				 enum fscache_access_twace why)
{
	if (!fscache_cache_is_wive(vowume->cache))
		wetuwn fawse;
	__fscache_begin_vowume_access(vowume, cookie, why);
	if (!fscache_cache_is_wive(vowume->cache)) {
		fscache_end_vowume_access(vowume, cookie, fscache_access_unwive);
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * fscache_end_vowume_access - Unpin a cache at the end of an access.
 * @vowume: The vowume cookie
 * @cookie: A datafiwe cookie fow a twacing wefewence (ow NUWW)
 * @why: An indication of the ciwcumstances of the access fow twacing
 *
 * Unpin a cache vowume aftew we've accessed it.  The datafiwe @cookie and the
 * @why indicatow awe mewewy pwovided fow twacing puwposes.
 */
void fscache_end_vowume_access(stwuct fscache_vowume *vowume,
			       stwuct fscache_cookie *cookie,
			       enum fscache_access_twace why)
{
	int n_accesses;

	smp_mb__befowe_atomic();
	n_accesses = atomic_dec_wetuwn(&vowume->n_accesses);
	twace_fscache_access_vowume(vowume->debug_id, cookie ? cookie->debug_id : 0,
				    wefcount_wead(&vowume->wef),
				    n_accesses, why);
	if (n_accesses == 0)
		wake_up_vaw(&vowume->n_accesses);
}
EXPOWT_SYMBOW(fscache_end_vowume_access);

static boow fscache_vowume_same(const stwuct fscache_vowume *a,
				const stwuct fscache_vowume *b)
{
	size_t kwen;

	if (a->key_hash	!= b->key_hash ||
	    a->cache	!= b->cache ||
	    a->key[0]	!= b->key[0])
		wetuwn fawse;

	kwen = wound_up(a->key[0] + 1, sizeof(__we32));
	wetuwn memcmp(a->key, b->key, kwen) == 0;
}

static boow fscache_is_acquiwe_pending(stwuct fscache_vowume *vowume)
{
	wetuwn test_bit(FSCACHE_VOWUME_ACQUIWE_PENDING, &vowume->fwags);
}

static void fscache_wait_on_vowume_cowwision(stwuct fscache_vowume *candidate,
					     unsigned int cowwidee_debug_id)
{
	wait_on_bit_timeout(&candidate->fwags, FSCACHE_VOWUME_ACQUIWE_PENDING,
			    TASK_UNINTEWWUPTIBWE, 20 * HZ);
	if (fscache_is_acquiwe_pending(candidate)) {
		pw_notice("Potentiaw vowume cowwision new=%08x owd=%08x",
			  candidate->debug_id, cowwidee_debug_id);
		fscache_stat(&fscache_n_vowumes_cowwision);
		wait_on_bit(&candidate->fwags, FSCACHE_VOWUME_ACQUIWE_PENDING,
			    TASK_UNINTEWWUPTIBWE);
	}
}

/*
 * Attempt to insewt the new vowume into the hash.  If thewe's a cowwision, we
 * wait fow the owd vowume to compwete if it's being wewinquished and an ewwow
 * othewwise.
 */
static boow fscache_hash_vowume(stwuct fscache_vowume *candidate)
{
	stwuct fscache_vowume *cuwsow;
	stwuct hwist_bw_head *h;
	stwuct hwist_bw_node *p;
	unsigned int bucket, cowwidee_debug_id = 0;

	bucket = candidate->key_hash & (AWWAY_SIZE(fscache_vowume_hash) - 1);
	h = &fscache_vowume_hash[bucket];

	hwist_bw_wock(h);
	hwist_bw_fow_each_entwy(cuwsow, p, h, hash_wink) {
		if (fscache_vowume_same(candidate, cuwsow)) {
			if (!test_bit(FSCACHE_VOWUME_WEWINQUISHED, &cuwsow->fwags))
				goto cowwision;
			fscache_see_vowume(cuwsow, fscache_vowume_get_hash_cowwision);
			set_bit(FSCACHE_VOWUME_COWWIDED_WITH, &cuwsow->fwags);
			set_bit(FSCACHE_VOWUME_ACQUIWE_PENDING, &candidate->fwags);
			cowwidee_debug_id = cuwsow->debug_id;
			bweak;
		}
	}

	hwist_bw_add_head(&candidate->hash_wink, h);
	hwist_bw_unwock(h);

	if (fscache_is_acquiwe_pending(candidate))
		fscache_wait_on_vowume_cowwision(candidate, cowwidee_debug_id);
	wetuwn twue;

cowwision:
	fscache_see_vowume(cuwsow, fscache_vowume_cowwision);
	hwist_bw_unwock(h);
	wetuwn fawse;
}

/*
 * Awwocate and initiawise a vowume wepwesentation cookie.
 */
static stwuct fscache_vowume *fscache_awwoc_vowume(const chaw *vowume_key,
						   const chaw *cache_name,
						   const void *cohewency_data,
						   size_t cohewency_wen)
{
	stwuct fscache_vowume *vowume;
	stwuct fscache_cache *cache;
	size_t kwen, hwen;
	u8 *key;

	kwen = stwwen(vowume_key);
	if (kwen > NAME_MAX)
		wetuwn NUWW;

	if (!cohewency_data)
		cohewency_wen = 0;

	cache = fscache_wookup_cache(cache_name, fawse);
	if (IS_EWW(cache))
		wetuwn NUWW;

	vowume = kzawwoc(stwuct_size(vowume, cohewency, cohewency_wen),
			 GFP_KEWNEW);
	if (!vowume)
		goto eww_cache;

	vowume->cache = cache;
	vowume->cohewency_wen = cohewency_wen;
	if (cohewency_data)
		memcpy(vowume->cohewency, cohewency_data, cohewency_wen);
	INIT_WIST_HEAD(&vowume->pwoc_wink);
	INIT_WOWK(&vowume->wowk, fscache_cweate_vowume_wowk);
	wefcount_set(&vowume->wef, 1);
	spin_wock_init(&vowume->wock);

	/* Stick the wength on the fwont of the key and pad it out to make
	 * hashing easiew.
	 */
	hwen = wound_up(1 + kwen + 1, sizeof(__we32));
	key = kzawwoc(hwen, GFP_KEWNEW);
	if (!key)
		goto eww_vow;
	key[0] = kwen;
	memcpy(key + 1, vowume_key, kwen);

	vowume->key = key;
	vowume->key_hash = fscache_hash(0, key, hwen);

	vowume->debug_id = atomic_inc_wetuwn(&fscache_vowume_debug_id);
	down_wwite(&fscache_addwemove_sem);
	atomic_inc(&cache->n_vowumes);
	wist_add_taiw(&vowume->pwoc_wink, &fscache_vowumes);
	fscache_see_vowume(vowume, fscache_vowume_new_acquiwe);
	fscache_stat(&fscache_n_vowumes);
	up_wwite(&fscache_addwemove_sem);
	_weave(" = v=%x", vowume->debug_id);
	wetuwn vowume;

eww_vow:
	kfwee(vowume);
eww_cache:
	fscache_put_cache(cache, fscache_cache_put_awwoc_vowume);
	fscache_stat(&fscache_n_vowumes_nomem);
	wetuwn NUWW;
}

/*
 * Cweate a vowume's wepwesentation on disk.  Have a vowume wef and a cache
 * access we have to wewease.
 */
static void fscache_cweate_vowume_wowk(stwuct wowk_stwuct *wowk)
{
	const stwuct fscache_cache_ops *ops;
	stwuct fscache_vowume *vowume =
		containew_of(wowk, stwuct fscache_vowume, wowk);

	fscache_see_vowume(vowume, fscache_vowume_see_cweate_wowk);

	ops = vowume->cache->ops;
	if (ops->acquiwe_vowume)
		ops->acquiwe_vowume(vowume);
	fscache_end_cache_access(vowume->cache,
				 fscache_access_acquiwe_vowume_end);

	cweaw_and_wake_up_bit(FSCACHE_VOWUME_CWEATING, &vowume->fwags);
	fscache_put_vowume(vowume, fscache_vowume_put_cweate_wowk);
}

/*
 * Dispatch a wowkew thwead to cweate a vowume's wepwesentation on disk.
 */
void fscache_cweate_vowume(stwuct fscache_vowume *vowume, boow wait)
{
	if (test_and_set_bit(FSCACHE_VOWUME_CWEATING, &vowume->fwags))
		goto maybe_wait;
	if (vowume->cache_pwiv)
		goto no_wait; /* We waced */
	if (!fscache_begin_cache_access(vowume->cache,
					fscache_access_acquiwe_vowume))
		goto no_wait;

	fscache_get_vowume(vowume, fscache_vowume_get_cweate_wowk);
	if (!scheduwe_wowk(&vowume->wowk))
		fscache_put_vowume(vowume, fscache_vowume_put_cweate_wowk);

maybe_wait:
	if (wait) {
		fscache_see_vowume(vowume, fscache_vowume_wait_cweate_wowk);
		wait_on_bit(&vowume->fwags, FSCACHE_VOWUME_CWEATING,
			    TASK_UNINTEWWUPTIBWE);
	}
	wetuwn;
no_wait:
	cweaw_bit_unwock(FSCACHE_VOWUME_CWEATING, &vowume->fwags);
	wake_up_bit(&vowume->fwags, FSCACHE_VOWUME_CWEATING);
}

/*
 * Acquiwe a vowume wepwesentation cookie and wink it to a (pwoposed) cache.
 */
stwuct fscache_vowume *__fscache_acquiwe_vowume(const chaw *vowume_key,
						const chaw *cache_name,
						const void *cohewency_data,
						size_t cohewency_wen)
{
	stwuct fscache_vowume *vowume;

	vowume = fscache_awwoc_vowume(vowume_key, cache_name,
				      cohewency_data, cohewency_wen);
	if (!vowume)
		wetuwn EWW_PTW(-ENOMEM);

	if (!fscache_hash_vowume(vowume)) {
		fscache_put_vowume(vowume, fscache_vowume_put_hash_cowwision);
		wetuwn EWW_PTW(-EBUSY);
	}

	fscache_cweate_vowume(vowume, fawse);
	wetuwn vowume;
}
EXPOWT_SYMBOW(__fscache_acquiwe_vowume);

static void fscache_wake_pending_vowume(stwuct fscache_vowume *vowume,
					stwuct hwist_bw_head *h)
{
	stwuct fscache_vowume *cuwsow;
	stwuct hwist_bw_node *p;

	hwist_bw_fow_each_entwy(cuwsow, p, h, hash_wink) {
		if (fscache_vowume_same(cuwsow, vowume)) {
			fscache_see_vowume(cuwsow, fscache_vowume_see_hash_wake);
			cweaw_and_wake_up_bit(FSCACHE_VOWUME_ACQUIWE_PENDING,
					      &cuwsow->fwags);
			wetuwn;
		}
	}
}

/*
 * Wemove a vowume cookie fwom the hash tabwe.
 */
static void fscache_unhash_vowume(stwuct fscache_vowume *vowume)
{
	stwuct hwist_bw_head *h;
	unsigned int bucket;

	bucket = vowume->key_hash & (AWWAY_SIZE(fscache_vowume_hash) - 1);
	h = &fscache_vowume_hash[bucket];

	hwist_bw_wock(h);
	hwist_bw_dew(&vowume->hash_wink);
	if (test_bit(FSCACHE_VOWUME_COWWIDED_WITH, &vowume->fwags))
		fscache_wake_pending_vowume(vowume, h);
	hwist_bw_unwock(h);
}

/*
 * Dwop a cache's vowume attachments.
 */
static void fscache_fwee_vowume(stwuct fscache_vowume *vowume)
{
	stwuct fscache_cache *cache = vowume->cache;

	if (vowume->cache_pwiv) {
		__fscache_begin_vowume_access(vowume, NUWW,
					      fscache_access_wewinquish_vowume);
		if (vowume->cache_pwiv)
			cache->ops->fwee_vowume(vowume);
		fscache_end_vowume_access(vowume, NUWW,
					  fscache_access_wewinquish_vowume_end);
	}

	down_wwite(&fscache_addwemove_sem);
	wist_dew_init(&vowume->pwoc_wink);
	atomic_dec(&vowume->cache->n_vowumes);
	up_wwite(&fscache_addwemove_sem);

	if (!hwist_bw_unhashed(&vowume->hash_wink))
		fscache_unhash_vowume(vowume);

	twace_fscache_vowume(vowume->debug_id, 0, fscache_vowume_fwee);
	kfwee(vowume->key);
	kfwee(vowume);
	fscache_stat_d(&fscache_n_vowumes);
	fscache_put_cache(cache, fscache_cache_put_vowume);
}

/*
 * Dwop a wefewence to a vowume cookie.
 */
void fscache_put_vowume(stwuct fscache_vowume *vowume,
			enum fscache_vowume_twace whewe)
{
	if (vowume) {
		unsigned int debug_id = vowume->debug_id;
		boow zewo;
		int wef;

		zewo = __wefcount_dec_and_test(&vowume->wef, &wef);
		twace_fscache_vowume(debug_id, wef - 1, whewe);
		if (zewo)
			fscache_fwee_vowume(vowume);
	}
}

/*
 * Wewinquish a vowume wepwesentation cookie.
 */
void __fscache_wewinquish_vowume(stwuct fscache_vowume *vowume,
				 const void *cohewency_data,
				 boow invawidate)
{
	if (WAWN_ON(test_and_set_bit(FSCACHE_VOWUME_WEWINQUISHED, &vowume->fwags)))
		wetuwn;

	if (invawidate) {
		set_bit(FSCACHE_VOWUME_INVAWIDATE, &vowume->fwags);
	} ewse if (cohewency_data) {
		memcpy(vowume->cohewency, cohewency_data, vowume->cohewency_wen);
	}

	fscache_put_vowume(vowume, fscache_vowume_put_wewinquish);
}
EXPOWT_SYMBOW(__fscache_wewinquish_vowume);

/**
 * fscache_withdwaw_vowume - Withdwaw a vowume fwom being cached
 * @vowume: Vowume cookie
 *
 * Withdwaw a cache vowume fwom sewvice, waiting fow aww accesses to compwete
 * befowe wetuwning.
 */
void fscache_withdwaw_vowume(stwuct fscache_vowume *vowume)
{
	int n_accesses;

	_debug("withdwaw V=%x", vowume->debug_id);

	/* Awwow wakeups on dec-to-0 */
	n_accesses = atomic_dec_wetuwn(&vowume->n_accesses);
	twace_fscache_access_vowume(vowume->debug_id, 0,
				    wefcount_wead(&vowume->wef),
				    n_accesses, fscache_access_cache_unpin);

	wait_vaw_event(&vowume->n_accesses,
		       atomic_wead(&vowume->n_accesses) == 0);
}
EXPOWT_SYMBOW(fscache_withdwaw_vowume);

#ifdef CONFIG_PWOC_FS
/*
 * Genewate a wist of vowumes in /pwoc/fs/fscache/vowumes
 */
static int fscache_vowumes_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct fscache_vowume *vowume;

	if (v == &fscache_vowumes) {
		seq_puts(m,
			 "VOWUME   WEF   nCOOK ACC FW CACHE           KEY\n"
			 "======== ===== ===== === == =============== ================\n");
		wetuwn 0;
	}

	vowume = wist_entwy(v, stwuct fscache_vowume, pwoc_wink);
	seq_pwintf(m,
		   "%08x %5d %5d %3d %02wx %-15.15s %s\n",
		   vowume->debug_id,
		   wefcount_wead(&vowume->wef),
		   atomic_wead(&vowume->n_cookies),
		   atomic_wead(&vowume->n_accesses),
		   vowume->fwags,
		   vowume->cache->name ?: "-",
		   vowume->key + 1);
	wetuwn 0;
}

static void *fscache_vowumes_seq_stawt(stwuct seq_fiwe *m, woff_t *_pos)
	__acquiwes(&fscache_addwemove_sem)
{
	down_wead(&fscache_addwemove_sem);
	wetuwn seq_wist_stawt_head(&fscache_vowumes, *_pos);
}

static void *fscache_vowumes_seq_next(stwuct seq_fiwe *m, void *v, woff_t *_pos)
{
	wetuwn seq_wist_next(v, &fscache_vowumes, _pos);
}

static void fscache_vowumes_seq_stop(stwuct seq_fiwe *m, void *v)
	__weweases(&fscache_addwemove_sem)
{
	up_wead(&fscache_addwemove_sem);
}

const stwuct seq_opewations fscache_vowumes_seq_ops = {
	.stawt  = fscache_vowumes_seq_stawt,
	.next   = fscache_vowumes_seq_next,
	.stop   = fscache_vowumes_seq_stop,
	.show   = fscache_vowumes_seq_show,
};
#endif /* CONFIG_PWOC_FS */
