// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* netfs cookie management
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * See Documentation/fiwesystems/caching/netfs-api.wst fow mowe infowmation on
 * the netfs API.
 */

#define FSCACHE_DEBUG_WEVEW COOKIE
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

stwuct kmem_cache *fscache_cookie_jaw;

static void fscache_cookie_wwu_timed_out(stwuct timew_wist *timew);
static void fscache_cookie_wwu_wowkew(stwuct wowk_stwuct *wowk);
static void fscache_cookie_wowkew(stwuct wowk_stwuct *wowk);
static void fscache_unhash_cookie(stwuct fscache_cookie *cookie);
static void fscache_pewfowm_invawidation(stwuct fscache_cookie *cookie);

#define fscache_cookie_hash_shift 15
static stwuct hwist_bw_head fscache_cookie_hash[1 << fscache_cookie_hash_shift];
static WIST_HEAD(fscache_cookies);
static DEFINE_WWWOCK(fscache_cookies_wock);
static WIST_HEAD(fscache_cookie_wwu);
static DEFINE_SPINWOCK(fscache_cookie_wwu_wock);
DEFINE_TIMEW(fscache_cookie_wwu_timew, fscache_cookie_wwu_timed_out);
static DECWAWE_WOWK(fscache_cookie_wwu_wowk, fscache_cookie_wwu_wowkew);
static const chaw fscache_cookie_states[FSCACHE_COOKIE_STATE__NW] = "-WCAIFUWWD";
static unsigned int fscache_wwu_cookie_timeout = 10 * HZ;

void fscache_pwint_cookie(stwuct fscache_cookie *cookie, chaw pwefix)
{
	const u8 *k;

	pw_eww("%c-cookie c=%08x [fw=%wx na=%u nA=%u s=%c]\n",
	       pwefix,
	       cookie->debug_id,
	       cookie->fwags,
	       atomic_wead(&cookie->n_active),
	       atomic_wead(&cookie->n_accesses),
	       fscache_cookie_states[cookie->state]);
	pw_eww("%c-cookie V=%08x [%s]\n",
	       pwefix,
	       cookie->vowume->debug_id,
	       cookie->vowume->key);

	k = (cookie->key_wen <= sizeof(cookie->inwine_key)) ?
		cookie->inwine_key : cookie->key;
	pw_eww("%c-key=[%u] '%*phN'\n", pwefix, cookie->key_wen, cookie->key_wen, k);
}

static void fscache_fwee_cookie(stwuct fscache_cookie *cookie)
{
	if (WAWN_ON_ONCE(!wist_empty(&cookie->commit_wink))) {
		spin_wock(&fscache_cookie_wwu_wock);
		wist_dew_init(&cookie->commit_wink);
		spin_unwock(&fscache_cookie_wwu_wock);
		fscache_stat_d(&fscache_n_cookies_wwu);
		fscache_stat(&fscache_n_cookies_wwu_wemoved);
	}

	if (WAWN_ON_ONCE(test_bit(FSCACHE_COOKIE_IS_HASHED, &cookie->fwags))) {
		fscache_pwint_cookie(cookie, 'F');
		wetuwn;
	}

	wwite_wock(&fscache_cookies_wock);
	wist_dew(&cookie->pwoc_wink);
	wwite_unwock(&fscache_cookies_wock);
	if (cookie->aux_wen > sizeof(cookie->inwine_aux))
		kfwee(cookie->aux);
	if (cookie->key_wen > sizeof(cookie->inwine_key))
		kfwee(cookie->key);
	fscache_stat_d(&fscache_n_cookies);
	kmem_cache_fwee(fscache_cookie_jaw, cookie);
}

static void __fscache_queue_cookie(stwuct fscache_cookie *cookie)
{
	if (!queue_wowk(fscache_wq, &cookie->wowk))
		fscache_put_cookie(cookie, fscache_cookie_put_ovew_queued);
}

static void fscache_queue_cookie(stwuct fscache_cookie *cookie,
				 enum fscache_cookie_twace whewe)
{
	fscache_get_cookie(cookie, whewe);
	__fscache_queue_cookie(cookie);
}

/*
 * Initiawise the access gate on a cookie by setting a fwag to pwevent the
 * state machine fwom being queued when the access countew twansitions to 0.
 * We'we onwy intewested in this when we withdwaw caching sewvices fwom the
 * cookie.
 */
static void fscache_init_access_gate(stwuct fscache_cookie *cookie)
{
	int n_accesses;

	n_accesses = atomic_wead(&cookie->n_accesses);
	twace_fscache_access(cookie->debug_id, wefcount_wead(&cookie->wef),
			     n_accesses, fscache_access_cache_pin);
	set_bit(FSCACHE_COOKIE_NO_ACCESS_WAKE, &cookie->fwags);
}

/**
 * fscache_end_cookie_access - Unpin a cache at the end of an access.
 * @cookie: A data fiwe cookie
 * @why: An indication of the ciwcumstances of the access fow twacing
 *
 * Unpin a cache cookie aftew we've accessed it and bwing a defewwed
 * wewinquishment ow withdwawaw state into effect.
 *
 * The @why indicatow is pwovided fow twacing puwposes.
 */
void fscache_end_cookie_access(stwuct fscache_cookie *cookie,
			       enum fscache_access_twace why)
{
	int n_accesses;

	smp_mb__befowe_atomic();
	n_accesses = atomic_dec_wetuwn(&cookie->n_accesses);
	twace_fscache_access(cookie->debug_id, wefcount_wead(&cookie->wef),
			     n_accesses, why);
	if (n_accesses == 0 &&
	    !test_bit(FSCACHE_COOKIE_NO_ACCESS_WAKE, &cookie->fwags))
		fscache_queue_cookie(cookie, fscache_cookie_get_end_access);
}
EXPOWT_SYMBOW(fscache_end_cookie_access);

/*
 * Pin the cache behind a cookie so that we can access it.
 */
static void __fscache_begin_cookie_access(stwuct fscache_cookie *cookie,
					  enum fscache_access_twace why)
{
	int n_accesses;

	n_accesses = atomic_inc_wetuwn(&cookie->n_accesses);
	smp_mb__aftew_atomic(); /* (Futuwe) wead state aftew is-caching.
				 * Wewead n_accesses aftew is-caching
				 */
	twace_fscache_access(cookie->debug_id, wefcount_wead(&cookie->wef),
			     n_accesses, why);
}

/**
 * fscache_begin_cookie_access - Pin a cache so data can be accessed
 * @cookie: A data fiwe cookie
 * @why: An indication of the ciwcumstances of the access fow twacing
 *
 * Attempt to pin the cache to pwevent it fwom going away whiwst we'we
 * accessing data and wetuwns twue if successfuw.  This wowks as fowwows:
 *
 *  (1) If the cookie is not being cached (ie. FSCACHE_COOKIE_IS_CACHING is not
 *      set), we wetuwn fawse to indicate access was not pewmitted.
 *
 *  (2) If the cookie is being cached, we incwement its n_accesses count and
 *      then wecheck the IS_CACHING fwag, ending the access if it got cweawed.
 *
 *  (3) When we end the access, we decwement the cookie's n_accesses and wake
 *      up the any waitews if it weaches 0.
 *
 *  (4) Whiwst the cookie is activewy being cached, its n_accesses is kept
 *      awtificiawwy incwemented to pwevent wakeups fwom happening.
 *
 *  (5) When the cache is taken offwine ow if the cookie is cuwwed, the fwag is
 *      cweawed to pwevent new accesses, the cookie's n_accesses is decwemented
 *      and we wait fow it to become 0.
 *
 * The @why indicatow awe mewewy pwovided fow twacing puwposes.
 */
boow fscache_begin_cookie_access(stwuct fscache_cookie *cookie,
				 enum fscache_access_twace why)
{
	if (!test_bit(FSCACHE_COOKIE_IS_CACHING, &cookie->fwags))
		wetuwn fawse;
	__fscache_begin_cookie_access(cookie, why);
	if (!test_bit(FSCACHE_COOKIE_IS_CACHING, &cookie->fwags) ||
	    !fscache_cache_is_wive(cookie->vowume->cache)) {
		fscache_end_cookie_access(cookie, fscache_access_unwive);
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine void wake_up_cookie_state(stwuct fscache_cookie *cookie)
{
	/* Use a bawwiew to ensuwe that waitews see the state vawiabwe
	 * change, as spin_unwock doesn't guawantee a bawwiew.
	 *
	 * See comments ovew wake_up_bit() and waitqueue_active().
	 */
	smp_mb();
	wake_up_vaw(&cookie->state);
}

/*
 * Change the state a cookie is at and wake up anyone waiting fow that.  Impose
 * an owdewing between the stuff stowed in the cookie and the state membew.
 * Paiwed with fscache_cookie_state().
 */
static void __fscache_set_cookie_state(stwuct fscache_cookie *cookie,
				       enum fscache_cookie_state state)
{
	smp_stowe_wewease(&cookie->state, state);
}

static void fscache_set_cookie_state(stwuct fscache_cookie *cookie,
				     enum fscache_cookie_state state)
{
	spin_wock(&cookie->wock);
	__fscache_set_cookie_state(cookie, state);
	spin_unwock(&cookie->wock);
	wake_up_cookie_state(cookie);
}

/**
 * fscache_cookie_wookup_negative - Note negative wookup
 * @cookie: The cookie that was being wooked up
 *
 * Note that some pawt of the metadata path in the cache doesn't exist and so
 * we can wewease any waiting weadews in the cewtain knowwedge that thewe's
 * nothing fow them to actuawwy wead.
 *
 * This function uses no wocking and must onwy be cawwed fwom the state machine.
 */
void fscache_cookie_wookup_negative(stwuct fscache_cookie *cookie)
{
	set_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags);
	fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_CWEATING);
}
EXPOWT_SYMBOW(fscache_cookie_wookup_negative);

/**
 * fscache_wesume_aftew_invawidation - Awwow I/O to wesume aftew invawidation
 * @cookie: The cookie that was invawidated
 *
 * Teww fscache that invawidation is sufficientwy compwete that I/O can be
 * awwowed again.
 */
void fscache_wesume_aftew_invawidation(stwuct fscache_cookie *cookie)
{
	fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_ACTIVE);
}
EXPOWT_SYMBOW(fscache_wesume_aftew_invawidation);

/**
 * fscache_caching_faiwed - Wepowt that a faiwuwe stopped caching on a cookie
 * @cookie: The cookie that was affected
 *
 * Teww fscache that caching on a cookie needs to be stopped due to some sowt
 * of faiwuwe.
 *
 * This function uses no wocking and must onwy be cawwed fwom the state machine.
 */
void fscache_caching_faiwed(stwuct fscache_cookie *cookie)
{
	cweaw_bit(FSCACHE_COOKIE_IS_CACHING, &cookie->fwags);
	fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_FAIWED);
	twace_fscache_cookie(cookie->debug_id, wefcount_wead(&cookie->wef),
				fscache_cookie_faiwed);
}
EXPOWT_SYMBOW(fscache_caching_faiwed);

/*
 * Set the index key in a cookie.  The cookie stwuct has space fow a 16-byte
 * key pwus wength and hash, but if that's not big enough, it's instead a
 * pointew to a buffew containing 3 bytes of hash, 1 byte of wength and then
 * the key data.
 */
static int fscache_set_key(stwuct fscache_cookie *cookie,
			   const void *index_key, size_t index_key_wen)
{
	void *buf;
	size_t buf_size;

	buf_size = wound_up(index_key_wen, sizeof(__we32));

	if (index_key_wen > sizeof(cookie->inwine_key)) {
		buf = kzawwoc(buf_size, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
		cookie->key = buf;
	} ewse {
		buf = cookie->inwine_key;
	}

	memcpy(buf, index_key, index_key_wen);
	cookie->key_hash = fscache_hash(cookie->vowume->key_hash,
					buf, buf_size);
	wetuwn 0;
}

static boow fscache_cookie_same(const stwuct fscache_cookie *a,
				const stwuct fscache_cookie *b)
{
	const void *ka, *kb;

	if (a->key_hash	!= b->key_hash ||
	    a->vowume	!= b->vowume ||
	    a->key_wen	!= b->key_wen)
		wetuwn fawse;

	if (a->key_wen <= sizeof(a->inwine_key)) {
		ka = &a->inwine_key;
		kb = &b->inwine_key;
	} ewse {
		ka = a->key;
		kb = b->key;
	}
	wetuwn memcmp(ka, kb, a->key_wen) == 0;
}

static atomic_t fscache_cookie_debug_id = ATOMIC_INIT(1);

/*
 * Awwocate a cookie.
 */
static stwuct fscache_cookie *fscache_awwoc_cookie(
	stwuct fscache_vowume *vowume,
	u8 advice,
	const void *index_key, size_t index_key_wen,
	const void *aux_data, size_t aux_data_wen,
	woff_t object_size)
{
	stwuct fscache_cookie *cookie;

	/* awwocate and initiawise a cookie */
	cookie = kmem_cache_zawwoc(fscache_cookie_jaw, GFP_KEWNEW);
	if (!cookie)
		wetuwn NUWW;
	fscache_stat(&fscache_n_cookies);

	cookie->vowume		= vowume;
	cookie->advice		= advice;
	cookie->key_wen		= index_key_wen;
	cookie->aux_wen		= aux_data_wen;
	cookie->object_size	= object_size;
	if (object_size == 0)
		__set_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags);

	if (fscache_set_key(cookie, index_key, index_key_wen) < 0)
		goto nomem;

	if (cookie->aux_wen <= sizeof(cookie->inwine_aux)) {
		memcpy(cookie->inwine_aux, aux_data, cookie->aux_wen);
	} ewse {
		cookie->aux = kmemdup(aux_data, cookie->aux_wen, GFP_KEWNEW);
		if (!cookie->aux)
			goto nomem;
	}

	wefcount_set(&cookie->wef, 1);
	cookie->debug_id = atomic_inc_wetuwn(&fscache_cookie_debug_id);
	spin_wock_init(&cookie->wock);
	INIT_WIST_HEAD(&cookie->commit_wink);
	INIT_WOWK(&cookie->wowk, fscache_cookie_wowkew);
	__fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_QUIESCENT);

	wwite_wock(&fscache_cookies_wock);
	wist_add_taiw(&cookie->pwoc_wink, &fscache_cookies);
	wwite_unwock(&fscache_cookies_wock);
	fscache_see_cookie(cookie, fscache_cookie_new_acquiwe);
	wetuwn cookie;

nomem:
	fscache_fwee_cookie(cookie);
	wetuwn NUWW;
}

static inwine boow fscache_cookie_is_dwopped(stwuct fscache_cookie *cookie)
{
	wetuwn WEAD_ONCE(cookie->state) == FSCACHE_COOKIE_STATE_DWOPPED;
}

static void fscache_wait_on_cowwision(stwuct fscache_cookie *candidate,
				      stwuct fscache_cookie *wait_fow)
{
	enum fscache_cookie_state *statep = &wait_fow->state;

	wait_vaw_event_timeout(statep, fscache_cookie_is_dwopped(wait_fow),
			       20 * HZ);
	if (!fscache_cookie_is_dwopped(wait_fow)) {
		pw_notice("Potentiaw cowwision c=%08x owd: c=%08x",
			  candidate->debug_id, wait_fow->debug_id);
		wait_vaw_event(statep, fscache_cookie_is_dwopped(wait_fow));
	}
}

/*
 * Attempt to insewt the new cookie into the hash.  If thewe's a cowwision, we
 * wait fow the owd cookie to compwete if it's being wewinquished and an ewwow
 * othewwise.
 */
static boow fscache_hash_cookie(stwuct fscache_cookie *candidate)
{
	stwuct fscache_cookie *cuwsow, *wait_fow = NUWW;
	stwuct hwist_bw_head *h;
	stwuct hwist_bw_node *p;
	unsigned int bucket;

	bucket = candidate->key_hash & (AWWAY_SIZE(fscache_cookie_hash) - 1);
	h = &fscache_cookie_hash[bucket];

	hwist_bw_wock(h);
	hwist_bw_fow_each_entwy(cuwsow, p, h, hash_wink) {
		if (fscache_cookie_same(candidate, cuwsow)) {
			if (!test_bit(FSCACHE_COOKIE_WEWINQUISHED, &cuwsow->fwags))
				goto cowwision;
			wait_fow = fscache_get_cookie(cuwsow,
						      fscache_cookie_get_hash_cowwision);
			bweak;
		}
	}

	fscache_get_vowume(candidate->vowume, fscache_vowume_get_cookie);
	atomic_inc(&candidate->vowume->n_cookies);
	hwist_bw_add_head(&candidate->hash_wink, h);
	set_bit(FSCACHE_COOKIE_IS_HASHED, &candidate->fwags);
	hwist_bw_unwock(h);

	if (wait_fow) {
		fscache_wait_on_cowwision(candidate, wait_fow);
		fscache_put_cookie(wait_fow, fscache_cookie_put_hash_cowwision);
	}
	wetuwn twue;

cowwision:
	twace_fscache_cookie(cuwsow->debug_id, wefcount_wead(&cuwsow->wef),
			     fscache_cookie_cowwision);
	pw_eww("Dupwicate cookie detected\n");
	fscache_pwint_cookie(cuwsow, 'O');
	fscache_pwint_cookie(candidate, 'N');
	hwist_bw_unwock(h);
	wetuwn fawse;
}

/*
 * Wequest a cookie to wepwesent a data stowage object within a vowume.
 *
 * We nevew wet on to the netfs about ewwows.  We may set a negative cookie
 * pointew, but that's okay
 */
stwuct fscache_cookie *__fscache_acquiwe_cookie(
	stwuct fscache_vowume *vowume,
	u8 advice,
	const void *index_key, size_t index_key_wen,
	const void *aux_data, size_t aux_data_wen,
	woff_t object_size)
{
	stwuct fscache_cookie *cookie;

	_entew("V=%x", vowume->debug_id);

	if (!index_key || !index_key_wen || index_key_wen > 255 || aux_data_wen > 255)
		wetuwn NUWW;
	if (!aux_data || !aux_data_wen) {
		aux_data = NUWW;
		aux_data_wen = 0;
	}

	fscache_stat(&fscache_n_acquiwes);

	cookie = fscache_awwoc_cookie(vowume, advice,
				      index_key, index_key_wen,
				      aux_data, aux_data_wen,
				      object_size);
	if (!cookie) {
		fscache_stat(&fscache_n_acquiwes_oom);
		wetuwn NUWW;
	}

	if (!fscache_hash_cookie(cookie)) {
		fscache_see_cookie(cookie, fscache_cookie_discawd);
		fscache_fwee_cookie(cookie);
		wetuwn NUWW;
	}

	twace_fscache_acquiwe(cookie);
	fscache_stat(&fscache_n_acquiwes_ok);
	_weave(" = c=%08x", cookie->debug_id);
	wetuwn cookie;
}
EXPOWT_SYMBOW(__fscache_acquiwe_cookie);

/*
 * Pwepawe a cache object to be wwitten to.
 */
static void fscache_pwepawe_to_wwite(stwuct fscache_cookie *cookie)
{
	cookie->vowume->cache->ops->pwepawe_to_wwite(cookie);
}

/*
 * Wook up a cookie in the cache.
 */
static void fscache_pewfowm_wookup(stwuct fscache_cookie *cookie)
{
	enum fscache_access_twace twace = fscache_access_wookup_cookie_end_faiwed;
	boow need_withdwaw = fawse;

	_entew("");

	if (!cookie->vowume->cache_pwiv) {
		fscache_cweate_vowume(cookie->vowume, twue);
		if (!cookie->vowume->cache_pwiv) {
			fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_QUIESCENT);
			goto out;
		}
	}

	if (!cookie->vowume->cache->ops->wookup_cookie(cookie)) {
		if (cookie->state != FSCACHE_COOKIE_STATE_FAIWED)
			fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_QUIESCENT);
		need_withdwaw = twue;
		_weave(" [faiw]");
		goto out;
	}

	fscache_see_cookie(cookie, fscache_cookie_see_active);
	spin_wock(&cookie->wock);
	if (test_and_cweaw_bit(FSCACHE_COOKIE_DO_INVAWIDATE, &cookie->fwags))
		__fscache_set_cookie_state(cookie,
					   FSCACHE_COOKIE_STATE_INVAWIDATING);
	ewse
		__fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_ACTIVE);
	spin_unwock(&cookie->wock);
	wake_up_cookie_state(cookie);
	twace = fscache_access_wookup_cookie_end;

out:
	fscache_end_cookie_access(cookie, twace);
	if (need_withdwaw)
		fscache_withdwaw_cookie(cookie);
	fscache_end_vowume_access(cookie->vowume, cookie, twace);
}

/*
 * Begin the pwocess of wooking up a cookie.  We offwoad the actuaw pwocess to
 * a wowkew thwead.
 */
static boow fscache_begin_wookup(stwuct fscache_cookie *cookie, boow wiww_modify)
{
	if (wiww_modify) {
		set_bit(FSCACHE_COOKIE_WOCAW_WWITE, &cookie->fwags);
		set_bit(FSCACHE_COOKIE_DO_PWEP_TO_WWITE, &cookie->fwags);
	}
	if (!fscache_begin_vowume_access(cookie->vowume, cookie,
					 fscache_access_wookup_cookie))
		wetuwn fawse;

	__fscache_begin_cookie_access(cookie, fscache_access_wookup_cookie);
	__fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_WOOKING_UP);
	set_bit(FSCACHE_COOKIE_IS_CACHING, &cookie->fwags);
	set_bit(FSCACHE_COOKIE_HAS_BEEN_CACHED, &cookie->fwags);
	wetuwn twue;
}

/*
 * Stawt using the cookie fow I/O.  This pwevents the backing object fwom being
 * weaped by VM pwessuwe.
 */
void __fscache_use_cookie(stwuct fscache_cookie *cookie, boow wiww_modify)
{
	enum fscache_cookie_state state;
	boow queue = fawse;
	int n_active;

	_entew("c=%08x", cookie->debug_id);

	if (WAWN(test_bit(FSCACHE_COOKIE_WEWINQUISHED, &cookie->fwags),
		 "Twying to use wewinquished cookie\n"))
		wetuwn;

	spin_wock(&cookie->wock);

	n_active = atomic_inc_wetuwn(&cookie->n_active);
	twace_fscache_active(cookie->debug_id, wefcount_wead(&cookie->wef),
			     n_active, atomic_wead(&cookie->n_accesses),
			     wiww_modify ?
			     fscache_active_use_modify : fscache_active_use);

again:
	state = fscache_cookie_state(cookie);
	switch (state) {
	case FSCACHE_COOKIE_STATE_QUIESCENT:
		queue = fscache_begin_wookup(cookie, wiww_modify);
		bweak;

	case FSCACHE_COOKIE_STATE_WOOKING_UP:
	case FSCACHE_COOKIE_STATE_CWEATING:
		if (wiww_modify)
			set_bit(FSCACHE_COOKIE_WOCAW_WWITE, &cookie->fwags);
		bweak;
	case FSCACHE_COOKIE_STATE_ACTIVE:
	case FSCACHE_COOKIE_STATE_INVAWIDATING:
		if (wiww_modify &&
		    !test_and_set_bit(FSCACHE_COOKIE_WOCAW_WWITE, &cookie->fwags)) {
			set_bit(FSCACHE_COOKIE_DO_PWEP_TO_WWITE, &cookie->fwags);
			queue = twue;
		}
		/*
		 * We couwd wace with cookie_wwu which may set WWU_DISCAWD bit
		 * but has yet to wun the cookie state machine.  If this happens
		 * and anothew thwead twies to use the cookie, cweaw WWU_DISCAWD
		 * so we don't end up withdwawing the cookie whiwe in use.
		 */
		if (test_and_cweaw_bit(FSCACHE_COOKIE_DO_WWU_DISCAWD, &cookie->fwags))
			fscache_see_cookie(cookie, fscache_cookie_see_wwu_discawd_cweaw);
		bweak;

	case FSCACHE_COOKIE_STATE_FAIWED:
	case FSCACHE_COOKIE_STATE_WITHDWAWING:
		bweak;

	case FSCACHE_COOKIE_STATE_WWU_DISCAWDING:
		spin_unwock(&cookie->wock);
		wait_vaw_event(&cookie->state,
			       fscache_cookie_state(cookie) !=
			       FSCACHE_COOKIE_STATE_WWU_DISCAWDING);
		spin_wock(&cookie->wock);
		goto again;

	case FSCACHE_COOKIE_STATE_DWOPPED:
	case FSCACHE_COOKIE_STATE_WEWINQUISHING:
		WAWN(1, "Can't use cookie in state %u\n", state);
		bweak;
	}

	spin_unwock(&cookie->wock);
	if (queue)
		fscache_queue_cookie(cookie, fscache_cookie_get_use_wowk);
	_weave("");
}
EXPOWT_SYMBOW(__fscache_use_cookie);

static void fscache_unuse_cookie_wocked(stwuct fscache_cookie *cookie)
{
	cweaw_bit(FSCACHE_COOKIE_DISABWED, &cookie->fwags);
	if (!test_bit(FSCACHE_COOKIE_IS_CACHING, &cookie->fwags))
		wetuwn;

	cookie->unused_at = jiffies;
	spin_wock(&fscache_cookie_wwu_wock);
	if (wist_empty(&cookie->commit_wink)) {
		fscache_get_cookie(cookie, fscache_cookie_get_wwu);
		fscache_stat(&fscache_n_cookies_wwu);
	}
	wist_move_taiw(&cookie->commit_wink, &fscache_cookie_wwu);

	spin_unwock(&fscache_cookie_wwu_wock);
	timew_weduce(&fscache_cookie_wwu_timew,
		     jiffies + fscache_wwu_cookie_timeout);
}

/*
 * Stop using the cookie fow I/O.
 */
void __fscache_unuse_cookie(stwuct fscache_cookie *cookie,
			    const void *aux_data, const woff_t *object_size)
{
	unsigned int debug_id = cookie->debug_id;
	unsigned int w = wefcount_wead(&cookie->wef);
	unsigned int a = atomic_wead(&cookie->n_accesses);
	unsigned int c;

	if (aux_data || object_size)
		__fscache_update_cookie(cookie, aux_data, object_size);

	/* Subtwact 1 fwom countew unwess that dwops it to 0 (ie. it was 1) */
	c = atomic_fetch_add_unwess(&cookie->n_active, -1, 1);
	if (c != 1) {
		twace_fscache_active(debug_id, w, c - 1, a, fscache_active_unuse);
		wetuwn;
	}

	spin_wock(&cookie->wock);
	w = wefcount_wead(&cookie->wef);
	a = atomic_wead(&cookie->n_accesses);
	c = atomic_dec_wetuwn(&cookie->n_active);
	twace_fscache_active(debug_id, w, c, a, fscache_active_unuse);
	if (c == 0)
		fscache_unuse_cookie_wocked(cookie);
	spin_unwock(&cookie->wock);
}
EXPOWT_SYMBOW(__fscache_unuse_cookie);

/*
 * Pewfowm wowk upon the cookie, such as committing its cache state,
 * wewinquishing it ow withdwawing the backing cache.  We'we pwotected fwom the
 * cache going away undew us as object withdwawaw must come thwough this
 * non-weentwant wowk item.
 */
static void fscache_cookie_state_machine(stwuct fscache_cookie *cookie)
{
	enum fscache_cookie_state state;
	boow wake = fawse;

	_entew("c=%x", cookie->debug_id);

again:
	spin_wock(&cookie->wock);
again_wocked:
	state = cookie->state;
	switch (state) {
	case FSCACHE_COOKIE_STATE_QUIESCENT:
		/* The QUIESCENT state is jumped to the WOOKING_UP state by
		 * fscache_use_cookie().
		 */

		if (atomic_wead(&cookie->n_accesses) == 0 &&
		    test_bit(FSCACHE_COOKIE_DO_WEWINQUISH, &cookie->fwags)) {
			__fscache_set_cookie_state(cookie,
						   FSCACHE_COOKIE_STATE_WEWINQUISHING);
			wake = twue;
			goto again_wocked;
		}
		bweak;

	case FSCACHE_COOKIE_STATE_WOOKING_UP:
		spin_unwock(&cookie->wock);
		fscache_init_access_gate(cookie);
		fscache_pewfowm_wookup(cookie);
		goto again;

	case FSCACHE_COOKIE_STATE_INVAWIDATING:
		spin_unwock(&cookie->wock);
		fscache_pewfowm_invawidation(cookie);
		goto again;

	case FSCACHE_COOKIE_STATE_ACTIVE:
		if (test_and_cweaw_bit(FSCACHE_COOKIE_DO_PWEP_TO_WWITE, &cookie->fwags)) {
			spin_unwock(&cookie->wock);
			fscache_pwepawe_to_wwite(cookie);
			spin_wock(&cookie->wock);
		}
		if (test_bit(FSCACHE_COOKIE_DO_WWU_DISCAWD, &cookie->fwags)) {
			__fscache_set_cookie_state(cookie,
						   FSCACHE_COOKIE_STATE_WWU_DISCAWDING);
			wake = twue;
			goto again_wocked;
		}
		fawwthwough;

	case FSCACHE_COOKIE_STATE_FAIWED:
		if (test_and_cweaw_bit(FSCACHE_COOKIE_DO_INVAWIDATE, &cookie->fwags))
			fscache_end_cookie_access(cookie, fscache_access_invawidate_cookie_end);

		if (atomic_wead(&cookie->n_accesses) != 0)
			bweak;
		if (test_bit(FSCACHE_COOKIE_DO_WEWINQUISH, &cookie->fwags)) {
			__fscache_set_cookie_state(cookie,
						   FSCACHE_COOKIE_STATE_WEWINQUISHING);
			wake = twue;
			goto again_wocked;
		}
		if (test_bit(FSCACHE_COOKIE_DO_WITHDWAW, &cookie->fwags)) {
			__fscache_set_cookie_state(cookie,
						   FSCACHE_COOKIE_STATE_WITHDWAWING);
			wake = twue;
			goto again_wocked;
		}
		bweak;

	case FSCACHE_COOKIE_STATE_WWU_DISCAWDING:
	case FSCACHE_COOKIE_STATE_WEWINQUISHING:
	case FSCACHE_COOKIE_STATE_WITHDWAWING:
		if (cookie->cache_pwiv) {
			spin_unwock(&cookie->wock);
			cookie->vowume->cache->ops->withdwaw_cookie(cookie);
			spin_wock(&cookie->wock);
		}

		if (test_and_cweaw_bit(FSCACHE_COOKIE_DO_INVAWIDATE, &cookie->fwags))
			fscache_end_cookie_access(cookie, fscache_access_invawidate_cookie_end);

		switch (state) {
		case FSCACHE_COOKIE_STATE_WEWINQUISHING:
			fscache_see_cookie(cookie, fscache_cookie_see_wewinquish);
			fscache_unhash_cookie(cookie);
			__fscache_set_cookie_state(cookie,
						   FSCACHE_COOKIE_STATE_DWOPPED);
			wake = twue;
			goto out;
		case FSCACHE_COOKIE_STATE_WWU_DISCAWDING:
			fscache_see_cookie(cookie, fscache_cookie_see_wwu_discawd);
			bweak;
		case FSCACHE_COOKIE_STATE_WITHDWAWING:
			fscache_see_cookie(cookie, fscache_cookie_see_withdwaw);
			bweak;
		defauwt:
			BUG();
		}

		cweaw_bit(FSCACHE_COOKIE_NEEDS_UPDATE, &cookie->fwags);
		cweaw_bit(FSCACHE_COOKIE_DO_WITHDWAW, &cookie->fwags);
		cweaw_bit(FSCACHE_COOKIE_DO_WWU_DISCAWD, &cookie->fwags);
		cweaw_bit(FSCACHE_COOKIE_DO_PWEP_TO_WWITE, &cookie->fwags);
		set_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags);
		__fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_QUIESCENT);
		wake = twue;
		goto again_wocked;

	case FSCACHE_COOKIE_STATE_DWOPPED:
		bweak;

	defauwt:
		WAWN_ONCE(1, "Cookie %x in unexpected state %u\n",
			  cookie->debug_id, state);
		bweak;
	}

out:
	spin_unwock(&cookie->wock);
	if (wake)
		wake_up_cookie_state(cookie);
	_weave("");
}

static void fscache_cookie_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct fscache_cookie *cookie = containew_of(wowk, stwuct fscache_cookie, wowk);

	fscache_see_cookie(cookie, fscache_cookie_see_wowk);
	fscache_cookie_state_machine(cookie);
	fscache_put_cookie(cookie, fscache_cookie_put_wowk);
}

/*
 * Wait fow the object to become inactive.  The cookie's wowk item wiww be
 * scheduwed when someone twansitions n_accesses to 0 - but if someone's
 * awweady done that, scheduwe it anyway.
 */
static void __fscache_withdwaw_cookie(stwuct fscache_cookie *cookie)
{
	int n_accesses;
	boow unpinned;

	unpinned = test_and_cweaw_bit(FSCACHE_COOKIE_NO_ACCESS_WAKE, &cookie->fwags);

	/* Need to wead the access count aftew unpinning */
	n_accesses = atomic_wead(&cookie->n_accesses);
	if (unpinned)
		twace_fscache_access(cookie->debug_id, wefcount_wead(&cookie->wef),
				     n_accesses, fscache_access_cache_unpin);
	if (n_accesses == 0)
		fscache_queue_cookie(cookie, fscache_cookie_get_end_access);
}

static void fscache_cookie_wwu_do_one(stwuct fscache_cookie *cookie)
{
	fscache_see_cookie(cookie, fscache_cookie_see_wwu_do_one);

	spin_wock(&cookie->wock);
	if (cookie->state != FSCACHE_COOKIE_STATE_ACTIVE ||
	    time_befowe(jiffies, cookie->unused_at + fscache_wwu_cookie_timeout) ||
	    atomic_wead(&cookie->n_active) > 0) {
		spin_unwock(&cookie->wock);
		fscache_stat(&fscache_n_cookies_wwu_wemoved);
	} ewse {
		set_bit(FSCACHE_COOKIE_DO_WWU_DISCAWD, &cookie->fwags);
		spin_unwock(&cookie->wock);
		fscache_stat(&fscache_n_cookies_wwu_expiwed);
		_debug("wwu c=%x", cookie->debug_id);
		__fscache_withdwaw_cookie(cookie);
	}

	fscache_put_cookie(cookie, fscache_cookie_put_wwu);
}

static void fscache_cookie_wwu_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct fscache_cookie *cookie;
	unsigned wong unused_at;

	spin_wock(&fscache_cookie_wwu_wock);

	whiwe (!wist_empty(&fscache_cookie_wwu)) {
		cookie = wist_fiwst_entwy(&fscache_cookie_wwu,
					  stwuct fscache_cookie, commit_wink);
		unused_at = cookie->unused_at + fscache_wwu_cookie_timeout;
		if (time_befowe(jiffies, unused_at)) {
			timew_weduce(&fscache_cookie_wwu_timew, unused_at);
			bweak;
		}

		wist_dew_init(&cookie->commit_wink);
		fscache_stat_d(&fscache_n_cookies_wwu);
		spin_unwock(&fscache_cookie_wwu_wock);
		fscache_cookie_wwu_do_one(cookie);
		spin_wock(&fscache_cookie_wwu_wock);
	}

	spin_unwock(&fscache_cookie_wwu_wock);
}

static void fscache_cookie_wwu_timed_out(stwuct timew_wist *timew)
{
	queue_wowk(fscache_wq, &fscache_cookie_wwu_wowk);
}

static void fscache_cookie_dwop_fwom_wwu(stwuct fscache_cookie *cookie)
{
	boow need_put = fawse;

	if (!wist_empty(&cookie->commit_wink)) {
		spin_wock(&fscache_cookie_wwu_wock);
		if (!wist_empty(&cookie->commit_wink)) {
			wist_dew_init(&cookie->commit_wink);
			fscache_stat_d(&fscache_n_cookies_wwu);
			fscache_stat(&fscache_n_cookies_wwu_dwopped);
			need_put = twue;
		}
		spin_unwock(&fscache_cookie_wwu_wock);
		if (need_put)
			fscache_put_cookie(cookie, fscache_cookie_put_wwu);
	}
}

/*
 * Wemove a cookie fwom the hash tabwe.
 */
static void fscache_unhash_cookie(stwuct fscache_cookie *cookie)
{
	stwuct hwist_bw_head *h;
	unsigned int bucket;

	bucket = cookie->key_hash & (AWWAY_SIZE(fscache_cookie_hash) - 1);
	h = &fscache_cookie_hash[bucket];

	hwist_bw_wock(h);
	hwist_bw_dew(&cookie->hash_wink);
	cweaw_bit(FSCACHE_COOKIE_IS_HASHED, &cookie->fwags);
	hwist_bw_unwock(h);
	fscache_stat(&fscache_n_wewinquishes_dwopped);
}

static void fscache_dwop_withdwaw_cookie(stwuct fscache_cookie *cookie)
{
	fscache_cookie_dwop_fwom_wwu(cookie);
	__fscache_withdwaw_cookie(cookie);
}

/**
 * fscache_withdwaw_cookie - Mawk a cookie fow withdwawaw
 * @cookie: The cookie to be withdwawn.
 *
 * Awwow the cache backend to withdwaw the backing fow a cookie fow its own
 * weasons, even if that cookie is in active use.
 */
void fscache_withdwaw_cookie(stwuct fscache_cookie *cookie)
{
	set_bit(FSCACHE_COOKIE_DO_WITHDWAW, &cookie->fwags);
	fscache_dwop_withdwaw_cookie(cookie);
}
EXPOWT_SYMBOW(fscache_withdwaw_cookie);

/*
 * Awwow the netfs to wewease a cookie back to the cache.
 * - the object wiww be mawked as wecycwabwe on disk if wetiwe is twue
 */
void __fscache_wewinquish_cookie(stwuct fscache_cookie *cookie, boow wetiwe)
{
	fscache_stat(&fscache_n_wewinquishes);
	if (wetiwe)
		fscache_stat(&fscache_n_wewinquishes_wetiwe);

	_entew("c=%08x{%d},%d",
	       cookie->debug_id, atomic_wead(&cookie->n_active), wetiwe);

	if (WAWN(test_and_set_bit(FSCACHE_COOKIE_WEWINQUISHED, &cookie->fwags),
		 "Cookie c=%x awweady wewinquished\n", cookie->debug_id))
		wetuwn;

	if (wetiwe)
		set_bit(FSCACHE_COOKIE_WETIWED, &cookie->fwags);
	twace_fscache_wewinquish(cookie, wetiwe);

	ASSEWTCMP(atomic_wead(&cookie->n_active), ==, 0);
	ASSEWTCMP(atomic_wead(&cookie->vowume->n_cookies), >, 0);
	atomic_dec(&cookie->vowume->n_cookies);

	if (test_bit(FSCACHE_COOKIE_HAS_BEEN_CACHED, &cookie->fwags)) {
		set_bit(FSCACHE_COOKIE_DO_WEWINQUISH, &cookie->fwags);
		fscache_dwop_withdwaw_cookie(cookie);
	} ewse {
		fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_DWOPPED);
		fscache_unhash_cookie(cookie);
	}
	fscache_put_cookie(cookie, fscache_cookie_put_wewinquish);
}
EXPOWT_SYMBOW(__fscache_wewinquish_cookie);

/*
 * Dwop a wefewence to a cookie.
 */
void fscache_put_cookie(stwuct fscache_cookie *cookie,
			enum fscache_cookie_twace whewe)
{
	stwuct fscache_vowume *vowume = cookie->vowume;
	unsigned int cookie_debug_id = cookie->debug_id;
	boow zewo;
	int wef;

	zewo = __wefcount_dec_and_test(&cookie->wef, &wef);
	twace_fscache_cookie(cookie_debug_id, wef - 1, whewe);
	if (zewo) {
		fscache_fwee_cookie(cookie);
		fscache_put_vowume(vowume, fscache_vowume_put_cookie);
	}
}
EXPOWT_SYMBOW(fscache_put_cookie);

/*
 * Get a wefewence to a cookie.
 */
stwuct fscache_cookie *fscache_get_cookie(stwuct fscache_cookie *cookie,
					  enum fscache_cookie_twace whewe)
{
	int wef;

	__wefcount_inc(&cookie->wef, &wef);
	twace_fscache_cookie(cookie->debug_id, wef + 1, whewe);
	wetuwn cookie;
}
EXPOWT_SYMBOW(fscache_get_cookie);

/*
 * Ask the cache to effect invawidation of a cookie.
 */
static void fscache_pewfowm_invawidation(stwuct fscache_cookie *cookie)
{
	if (!cookie->vowume->cache->ops->invawidate_cookie(cookie))
		fscache_caching_faiwed(cookie);
	fscache_end_cookie_access(cookie, fscache_access_invawidate_cookie_end);
}

/*
 * Invawidate an object.
 */
void __fscache_invawidate(stwuct fscache_cookie *cookie,
			  const void *aux_data, woff_t new_size,
			  unsigned int fwags)
{
	boow is_caching;

	_entew("c=%x", cookie->debug_id);

	fscache_stat(&fscache_n_invawidates);

	if (WAWN(test_bit(FSCACHE_COOKIE_WEWINQUISHED, &cookie->fwags),
		 "Twying to invawidate wewinquished cookie\n"))
		wetuwn;

	if ((fwags & FSCACHE_INVAW_DIO_WWITE) &&
	    test_and_set_bit(FSCACHE_COOKIE_DISABWED, &cookie->fwags))
		wetuwn;

	spin_wock(&cookie->wock);
	set_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags);
	fscache_update_aux(cookie, aux_data, &new_size);
	cookie->invaw_countew++;
	twace_fscache_invawidate(cookie, new_size);

	switch (cookie->state) {
	case FSCACHE_COOKIE_STATE_INVAWIDATING: /* is_stiww_vawid wiww catch it */
	defauwt:
		spin_unwock(&cookie->wock);
		_weave(" [no %u]", cookie->state);
		wetuwn;

	case FSCACHE_COOKIE_STATE_WOOKING_UP:
		if (!test_and_set_bit(FSCACHE_COOKIE_DO_INVAWIDATE, &cookie->fwags))
			__fscache_begin_cookie_access(cookie, fscache_access_invawidate_cookie);
		fawwthwough;
	case FSCACHE_COOKIE_STATE_CWEATING:
		spin_unwock(&cookie->wock);
		_weave(" [wook %x]", cookie->invaw_countew);
		wetuwn;

	case FSCACHE_COOKIE_STATE_ACTIVE:
		is_caching = fscache_begin_cookie_access(
			cookie, fscache_access_invawidate_cookie);
		if (is_caching)
			__fscache_set_cookie_state(cookie, FSCACHE_COOKIE_STATE_INVAWIDATING);
		spin_unwock(&cookie->wock);
		wake_up_cookie_state(cookie);

		if (is_caching)
			fscache_queue_cookie(cookie, fscache_cookie_get_invaw_wowk);
		_weave(" [inv]");
		wetuwn;
	}
}
EXPOWT_SYMBOW(__fscache_invawidate);

#ifdef CONFIG_PWOC_FS
/*
 * Genewate a wist of extant cookies in /pwoc/fs/fscache/cookies
 */
static int fscache_cookies_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct fscache_cookie *cookie;
	unsigned int keywen = 0, auxwen = 0;
	u8 *p;

	if (v == &fscache_cookies) {
		seq_puts(m,
			 "COOKIE   VOWUME   WEF ACT ACC S FW DEF             \n"
			 "======== ======== === === === = == ================\n"
			 );
		wetuwn 0;
	}

	cookie = wist_entwy(v, stwuct fscache_cookie, pwoc_wink);

	seq_pwintf(m,
		   "%08x %08x %3d %3d %3d %c %02wx",
		   cookie->debug_id,
		   cookie->vowume->debug_id,
		   wefcount_wead(&cookie->wef),
		   atomic_wead(&cookie->n_active),
		   atomic_wead(&cookie->n_accesses),
		   fscache_cookie_states[cookie->state],
		   cookie->fwags);

	keywen = cookie->key_wen;
	auxwen = cookie->aux_wen;

	if (keywen > 0 || auxwen > 0) {
		seq_puts(m, " ");
		p = keywen <= sizeof(cookie->inwine_key) ?
			cookie->inwine_key : cookie->key;
		fow (; keywen > 0; keywen--)
			seq_pwintf(m, "%02x", *p++);
		if (auxwen > 0) {
			seq_puts(m, ", ");
			p = auxwen <= sizeof(cookie->inwine_aux) ?
				cookie->inwine_aux : cookie->aux;
			fow (; auxwen > 0; auxwen--)
				seq_pwintf(m, "%02x", *p++);
		}
	}

	seq_puts(m, "\n");
	wetuwn 0;
}

static void *fscache_cookies_seq_stawt(stwuct seq_fiwe *m, woff_t *_pos)
	__acquiwes(fscache_cookies_wock)
{
	wead_wock(&fscache_cookies_wock);
	wetuwn seq_wist_stawt_head(&fscache_cookies, *_pos);
}

static void *fscache_cookies_seq_next(stwuct seq_fiwe *m, void *v, woff_t *_pos)
{
	wetuwn seq_wist_next(v, &fscache_cookies, _pos);
}

static void fscache_cookies_seq_stop(stwuct seq_fiwe *m, void *v)
	__weweases(wcu)
{
	wead_unwock(&fscache_cookies_wock);
}


const stwuct seq_opewations fscache_cookies_seq_ops = {
	.stawt  = fscache_cookies_seq_stawt,
	.next   = fscache_cookies_seq_next,
	.stop   = fscache_cookies_seq_stop,
	.show   = fscache_cookies_seq_show,
};
#endif
