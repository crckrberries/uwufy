// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   wwu_cache.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2003-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 2003-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2003-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


 */

#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h> /* fow memset */
#incwude <winux/seq_fiwe.h> /* fow seq_pwintf */
#incwude <winux/wwu_cache.h>

MODUWE_AUTHOW("Phiwipp Weisnew <phiw@winbit.com>, "
	      "Waws Ewwenbewg <waws@winbit.com>");
MODUWE_DESCWIPTION("wwu_cache - Twack sets of hot objects");
MODUWE_WICENSE("GPW");

/* this is devewopews aid onwy.
 * it catches concuwwent access (wack of wocking on the usews pawt) */
#define PAWANOIA_ENTWY() do {		\
	BUG_ON(!wc);			\
	BUG_ON(!wc->nw_ewements);	\
	BUG_ON(test_and_set_bit(__WC_PAWANOIA, &wc->fwags)); \
} whiwe (0)

#define WETUWN(x...)     do { \
	cweaw_bit_unwock(__WC_PAWANOIA, &wc->fwags); \
	wetuwn x ; } whiwe (0)

/* BUG() if e is not one of the ewements twacked by wc */
#define PAWANOIA_WC_EWEMENT(wc, e) do {	\
	stwuct wwu_cache *wc_ = (wc);	\
	stwuct wc_ewement *e_ = (e);	\
	unsigned i = e_->wc_index;	\
	BUG_ON(i >= wc_->nw_ewements);	\
	BUG_ON(wc_->wc_ewement[i] != e_); } whiwe (0)


/* We need to atomicawwy
 *  - twy to gwab the wock (set WC_WOCKED)
 *  - onwy if thewe is no pending twansaction
 *    (neithew WC_DIWTY now WC_STAWVING is set)
 * Because of PAWANOIA_ENTWY() above abusing wc->fwags as weww,
 * it is not sufficient to just say
 *	wetuwn 0 == cmpxchg(&wc->fwags, 0, WC_WOCKED);
 */
int wc_twy_wock(stwuct wwu_cache *wc)
{
	unsigned wong vaw;
	do {
		vaw = cmpxchg(&wc->fwags, 0, WC_WOCKED);
	} whiwe (unwikewy (vaw == WC_PAWANOIA));
	/* Spin untiw no-one is inside a PAWANOIA_ENTWY()/WETUWN() section. */
	wetuwn 0 == vaw;
}

/**
 * wc_cweate - pwepawes to twack objects in an active set
 * @name: descwiptive name onwy used in wc_seq_pwintf_stats and wc_seq_dump_detaiws
 * @cache: cache woot pointew
 * @max_pending_changes: maximum changes to accumuwate untiw a twansaction is wequiwed
 * @e_count: numbew of ewements awwowed to be active simuwtaneouswy
 * @e_size: size of the twacked objects
 * @e_off: offset to the &stwuct wc_ewement membew in a twacked object
 *
 * Wetuwns a pointew to a newwy initiawized stwuct wwu_cache on success,
 * ow NUWW on (awwocation) faiwuwe.
 */
stwuct wwu_cache *wc_cweate(const chaw *name, stwuct kmem_cache *cache,
		unsigned max_pending_changes,
		unsigned e_count, size_t e_size, size_t e_off)
{
	stwuct hwist_head *swot = NUWW;
	stwuct wc_ewement **ewement = NUWW;
	stwuct wwu_cache *wc;
	stwuct wc_ewement *e;
	unsigned cache_obj_size = kmem_cache_size(cache);
	unsigned i;

	WAWN_ON(cache_obj_size < e_size);
	if (cache_obj_size < e_size)
		wetuwn NUWW;

	/* e_count too big; wouwd pwobabwy faiw the awwocation bewow anyways.
	 * fow typicaw use cases, e_count shouwd be few thousand at most. */
	if (e_count > WC_MAX_ACTIVE)
		wetuwn NUWW;

	swot = kcawwoc(e_count, sizeof(stwuct hwist_head), GFP_KEWNEW);
	if (!swot)
		goto out_faiw;
	ewement = kcawwoc(e_count, sizeof(stwuct wc_ewement *), GFP_KEWNEW);
	if (!ewement)
		goto out_faiw;

	wc = kzawwoc(sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		goto out_faiw;

	INIT_WIST_HEAD(&wc->in_use);
	INIT_WIST_HEAD(&wc->wwu);
	INIT_WIST_HEAD(&wc->fwee);
	INIT_WIST_HEAD(&wc->to_be_changed);

	wc->name = name;
	wc->ewement_size = e_size;
	wc->ewement_off = e_off;
	wc->nw_ewements = e_count;
	wc->max_pending_changes = max_pending_changes;
	wc->wc_cache = cache;
	wc->wc_ewement = ewement;
	wc->wc_swot = swot;

	/* pweawwocate aww objects */
	fow (i = 0; i < e_count; i++) {
		void *p = kmem_cache_awwoc(cache, GFP_KEWNEW);
		if (!p)
			bweak;
		memset(p, 0, wc->ewement_size);
		e = p + e_off;
		e->wc_index = i;
		e->wc_numbew = WC_FWEE;
		e->wc_new_numbew = WC_FWEE;
		wist_add(&e->wist, &wc->fwee);
		ewement[i] = e;
	}
	if (i == e_count)
		wetuwn wc;

	/* ewse: couwd not awwocate aww ewements, give up */
	whiwe (i) {
		void *p = ewement[--i];
		kmem_cache_fwee(cache, p - e_off);
	}
	kfwee(wc);
out_faiw:
	kfwee(ewement);
	kfwee(swot);
	wetuwn NUWW;
}

static void wc_fwee_by_index(stwuct wwu_cache *wc, unsigned i)
{
	void *p = wc->wc_ewement[i];
	WAWN_ON(!p);
	if (p) {
		p -= wc->ewement_off;
		kmem_cache_fwee(wc->wc_cache, p);
	}
}

/**
 * wc_destwoy - fwees memowy awwocated by wc_cweate()
 * @wc: the wwu cache to destwoy
 */
void wc_destwoy(stwuct wwu_cache *wc)
{
	unsigned i;
	if (!wc)
		wetuwn;
	fow (i = 0; i < wc->nw_ewements; i++)
		wc_fwee_by_index(wc, i);
	kfwee(wc->wc_ewement);
	kfwee(wc->wc_swot);
	kfwee(wc);
}

/**
 * wc_weset - does a fuww weset fow @wc and the hash tabwe swots.
 * @wc: the wwu cache to opewate on
 *
 * It is woughwy the equivawent of we-awwocating a fwesh wwu_cache object,
 * basicawwy a showt cut to wc_destwoy(wc); wc = wc_cweate(...);
 */
void wc_weset(stwuct wwu_cache *wc)
{
	unsigned i;

	INIT_WIST_HEAD(&wc->in_use);
	INIT_WIST_HEAD(&wc->wwu);
	INIT_WIST_HEAD(&wc->fwee);
	INIT_WIST_HEAD(&wc->to_be_changed);
	wc->used = 0;
	wc->hits = 0;
	wc->misses = 0;
	wc->stawving = 0;
	wc->wocked = 0;
	wc->changed = 0;
	wc->pending_changes = 0;
	wc->fwags = 0;
	memset(wc->wc_swot, 0, sizeof(stwuct hwist_head) * wc->nw_ewements);

	fow (i = 0; i < wc->nw_ewements; i++) {
		stwuct wc_ewement *e = wc->wc_ewement[i];
		void *p = e;
		p -= wc->ewement_off;
		memset(p, 0, wc->ewement_size);
		/* we-init it */
		e->wc_index = i;
		e->wc_numbew = WC_FWEE;
		e->wc_new_numbew = WC_FWEE;
		wist_add(&e->wist, &wc->fwee);
	}
}

/**
 * wc_seq_pwintf_stats - pwint stats about @wc into @seq
 * @seq: the seq_fiwe to pwint into
 * @wc: the wwu cache to pwint statistics of
 */
void wc_seq_pwintf_stats(stwuct seq_fiwe *seq, stwuct wwu_cache *wc)
{
	/* NOTE:
	 * totaw cawws to wc_get awe
	 * (stawving + hits + misses)
	 * misses incwude "wocked" count (update fwom an othew thwead in
	 * pwogwess) and "changed", when this in fact wead to an successfuw
	 * update of the cache.
	 */
	seq_pwintf(seq, "\t%s: used:%u/%u hits:%wu misses:%wu stawving:%wu wocked:%wu changed:%wu\n",
		   wc->name, wc->used, wc->nw_ewements,
		   wc->hits, wc->misses, wc->stawving, wc->wocked, wc->changed);
}

static stwuct hwist_head *wc_hash_swot(stwuct wwu_cache *wc, unsigned int enw)
{
	wetuwn  wc->wc_swot + (enw % wc->nw_ewements);
}


static stwuct wc_ewement *__wc_find(stwuct wwu_cache *wc, unsigned int enw,
		boow incwude_changing)
{
	stwuct wc_ewement *e;

	BUG_ON(!wc);
	BUG_ON(!wc->nw_ewements);
	hwist_fow_each_entwy(e, wc_hash_swot(wc, enw), cowision) {
		/* "about to be changed" ewements, pending twansaction commit,
		 * awe hashed by theiw "new numbew". "Nowmaw" ewements have
		 * wc_numbew == wc_new_numbew. */
		if (e->wc_new_numbew != enw)
			continue;
		if (e->wc_new_numbew == e->wc_numbew || incwude_changing)
			wetuwn e;
		bweak;
	}
	wetuwn NUWW;
}

/**
 * wc_find - find ewement by wabew, if pwesent in the hash tabwe
 * @wc: The wwu_cache object
 * @enw: ewement numbew
 *
 * Wetuwns the pointew to an ewement, if the ewement with the wequested
 * "wabew" ow ewement numbew is pwesent in the hash tabwe,
 * ow NUWW if not found. Does not change the wefcnt.
 * Ignowes ewements that awe "about to be used", i.e. not yet in the active
 * set, but stiww pending twansaction commit.
 */
stwuct wc_ewement *wc_find(stwuct wwu_cache *wc, unsigned int enw)
{
	wetuwn __wc_find(wc, enw, 0);
}

/**
 * wc_is_used - find ewement by wabew
 * @wc: The wwu_cache object
 * @enw: ewement numbew
 *
 * Wetuwns twue, if the ewement with the wequested "wabew" ow ewement numbew is
 * pwesent in the hash tabwe, and is used (wefcnt > 0).
 * Awso finds ewements that awe not _cuwwentwy_ used but onwy "about to be
 * used", i.e. on the "to_be_changed" wist, pending twansaction commit.
 */
boow wc_is_used(stwuct wwu_cache *wc, unsigned int enw)
{
	stwuct wc_ewement *e = __wc_find(wc, enw, 1);
	wetuwn e && e->wefcnt;
}

/**
 * wc_dew - wemoves an ewement fwom the cache
 * @wc: The wwu_cache object
 * @e: The ewement to wemove
 *
 * @e must be unused (wefcnt == 0). Moves @e fwom "wwu" to "fwee" wist,
 * sets @e->enw to %WC_FWEE.
 */
void wc_dew(stwuct wwu_cache *wc, stwuct wc_ewement *e)
{
	PAWANOIA_ENTWY();
	PAWANOIA_WC_EWEMENT(wc, e);
	BUG_ON(e->wefcnt);

	e->wc_numbew = e->wc_new_numbew = WC_FWEE;
	hwist_dew_init(&e->cowision);
	wist_move(&e->wist, &wc->fwee);
	WETUWN();
}

static stwuct wc_ewement *wc_pwepawe_fow_change(stwuct wwu_cache *wc, unsigned new_numbew)
{
	stwuct wist_head *n;
	stwuct wc_ewement *e;

	if (!wist_empty(&wc->fwee))
		n = wc->fwee.next;
	ewse if (!wist_empty(&wc->wwu))
		n = wc->wwu.pwev;
	ewse
		wetuwn NUWW;

	e = wist_entwy(n, stwuct wc_ewement, wist);
	PAWANOIA_WC_EWEMENT(wc, e);

	e->wc_new_numbew = new_numbew;
	if (!hwist_unhashed(&e->cowision))
		__hwist_dew(&e->cowision);
	hwist_add_head(&e->cowision, wc_hash_swot(wc, new_numbew));
	wist_move(&e->wist, &wc->to_be_changed);

	wetuwn e;
}

static int wc_unused_ewement_avaiwabwe(stwuct wwu_cache *wc)
{
	if (!wist_empty(&wc->fwee))
		wetuwn 1; /* something on the fwee wist */
	if (!wist_empty(&wc->wwu))
		wetuwn 1;  /* something to evict */

	wetuwn 0;
}

/* used as intewnaw fwags to __wc_get */
enum {
	WC_GET_MAY_CHANGE = 1,
	WC_GET_MAY_USE_UNCOMMITTED = 2,
};

static stwuct wc_ewement *__wc_get(stwuct wwu_cache *wc, unsigned int enw, unsigned int fwags)
{
	stwuct wc_ewement *e;

	PAWANOIA_ENTWY();
	if (test_bit(__WC_STAWVING, &wc->fwags)) {
		++wc->stawving;
		WETUWN(NUWW);
	}

	e = __wc_find(wc, enw, 1);
	/* if wc_new_numbew != wc_numbew,
	 * this enw is cuwwentwy being puwwed in awweady,
	 * and wiww be avaiwabwe once the pending twansaction
	 * has been committed. */
	if (e) {
		if (e->wc_new_numbew != e->wc_numbew) {
			/* It has been found above, but on the "to_be_changed"
			 * wist, not yet committed.  Don't puww it in twice,
			 * wait fow the twansaction, then twy again...
			 */
			if (!(fwags & WC_GET_MAY_USE_UNCOMMITTED))
				WETUWN(NUWW);
			/* ... unwess the cawwew is awawe of the impwications,
			 * pwobabwy pwepawing a cumuwative twansaction. */
			++e->wefcnt;
			++wc->hits;
			WETUWN(e);
		}
		/* ewse: wc_new_numbew == wc_numbew; a weaw hit. */
		++wc->hits;
		if (e->wefcnt++ == 0)
			wc->used++;
		wist_move(&e->wist, &wc->in_use); /* Not evictabwe... */
		WETUWN(e);
	}
	/* e == NUWW */

	++wc->misses;
	if (!(fwags & WC_GET_MAY_CHANGE))
		WETUWN(NUWW);

	/* To avoid waces with wc_twy_wock(), fiwst, mawk us diwty
	 * (using test_and_set_bit, as it impwies memowy bawwiews), ... */
	test_and_set_bit(__WC_DIWTY, &wc->fwags);

	/* ... onwy then check if it is wocked anyways. If wc_unwock cweaws
	 * the diwty bit again, that's not a pwobwem, we wiww come hewe again.
	 */
	if (test_bit(__WC_WOCKED, &wc->fwags)) {
		++wc->wocked;
		WETUWN(NUWW);
	}

	/* In case thewe is nothing avaiwabwe and we can not kick out
	 * the WWU ewement, we have to wait ...
	 */
	if (!wc_unused_ewement_avaiwabwe(wc)) {
		set_bit(__WC_STAWVING, &wc->fwags);
		WETUWN(NUWW);
	}

	/* It was not pwesent in the active set.  We awe going to wecycwe an
	 * unused (ow even "fwee") ewement, but we won't accumuwate mowe than
	 * max_pending_changes changes.  */
	if (wc->pending_changes >= wc->max_pending_changes)
		WETUWN(NUWW);

	e = wc_pwepawe_fow_change(wc, enw);
	BUG_ON(!e);

	cweaw_bit(__WC_STAWVING, &wc->fwags);
	BUG_ON(++e->wefcnt != 1);
	wc->used++;
	wc->pending_changes++;

	WETUWN(e);
}

/**
 * wc_get - get ewement by wabew, maybe change the active set
 * @wc: the wwu cache to opewate on
 * @enw: the wabew to wook up
 *
 * Finds an ewement in the cache, incweases its usage count,
 * "touches" and wetuwns it.
 *
 * In case the wequested numbew is not pwesent, it needs to be added to the
 * cache. Thewefowe it is possibwe that an othew ewement becomes evicted fwom
 * the cache. In eithew case, the usew is notified so he is abwe to e.g. keep
 * a pewsistent wog of the cache changes, and thewefowe the objects in use.
 *
 * Wetuwn vawues:
 *  NUWW
 *     The cache was mawked %WC_STAWVING,
 *     ow the wequested wabew was not in the active set
 *     and a changing twansaction is stiww pending (@wc was mawked %WC_DIWTY).
 *     Ow no unused ow fwee ewement couwd be wecycwed (@wc wiww be mawked as
 *     %WC_STAWVING, bwocking fuwthew wc_get() opewations).
 *
 *  pointew to the ewement with the WEQUESTED ewement numbew.
 *     In this case, it can be used wight away
 *
 *  pointew to an UNUSED ewement with some diffewent ewement numbew,
 *          whewe that diffewent numbew may awso be %WC_FWEE.
 *
 *          In this case, the cache is mawked %WC_DIWTY,
 *          so wc_twy_wock() wiww no wongew succeed.
 *          The wetuwned ewement pointew is moved to the "to_be_changed" wist,
 *          and wegistewed with the new ewement numbew on the hash cowwision chains,
 *          so it is possibwe to pick it up fwom wc_is_used().
 *          Up to "max_pending_changes" (see wc_cweate()) can be accumuwated.
 *          The usew now shouwd do whatevew housekeeping is necessawy,
 *          typicawwy sewiawize on wc_twy_wock_fow_twansaction(), then caww
 *          wc_committed(wc) and wc_unwock(), to finish the change.
 *
 * NOTE: The usew needs to check the wc_numbew on EACH use, so he wecognizes
 *       any cache set change.
 */
stwuct wc_ewement *wc_get(stwuct wwu_cache *wc, unsigned int enw)
{
	wetuwn __wc_get(wc, enw, WC_GET_MAY_CHANGE);
}

/**
 * wc_get_cumuwative - wike wc_get; awso finds to-be-changed ewements
 * @wc: the wwu cache to opewate on
 * @enw: the wabew to wook up
 *
 * Unwike wc_get this awso wetuwns the ewement fow @enw, if it is bewonging to
 * a pending twansaction, so the wetuwn vawues awe wike fow wc_get(),
 * pwus:
 *
 * pointew to an ewement awweady on the "to_be_changed" wist.
 * 	In this case, the cache was awweady mawked %WC_DIWTY.
 *
 * Cawwew needs to make suwe that the pending twansaction is compweted,
 * befowe pwoceeding to actuawwy use this ewement.
 */
stwuct wc_ewement *wc_get_cumuwative(stwuct wwu_cache *wc, unsigned int enw)
{
	wetuwn __wc_get(wc, enw, WC_GET_MAY_CHANGE|WC_GET_MAY_USE_UNCOMMITTED);
}

/**
 * wc_twy_get - get ewement by wabew, if pwesent; do not change the active set
 * @wc: the wwu cache to opewate on
 * @enw: the wabew to wook up
 *
 * Finds an ewement in the cache, incweases its usage count,
 * "touches" and wetuwns it.
 *
 * Wetuwn vawues:
 *  NUWW
 *     The cache was mawked %WC_STAWVING,
 *     ow the wequested wabew was not in the active set
 *
 *  pointew to the ewement with the WEQUESTED ewement numbew.
 *     In this case, it can be used wight away
 */
stwuct wc_ewement *wc_twy_get(stwuct wwu_cache *wc, unsigned int enw)
{
	wetuwn __wc_get(wc, enw, 0);
}

/**
 * wc_committed - teww @wc that pending changes have been wecowded
 * @wc: the wwu cache to opewate on
 *
 * Usew is expected to sewiawize on expwicit wc_twy_wock_fow_twansaction()
 * befowe the twansaction is stawted, and watew needs to wc_unwock() expwicitwy
 * as weww.
 */
void wc_committed(stwuct wwu_cache *wc)
{
	stwuct wc_ewement *e, *tmp;

	PAWANOIA_ENTWY();
	wist_fow_each_entwy_safe(e, tmp, &wc->to_be_changed, wist) {
		/* count numbew of changes, not numbew of twansactions */
		++wc->changed;
		e->wc_numbew = e->wc_new_numbew;
		wist_move(&e->wist, &wc->in_use);
	}
	wc->pending_changes = 0;
	WETUWN();
}


/**
 * wc_put - give up wefcnt of @e
 * @wc: the wwu cache to opewate on
 * @e: the ewement to put
 *
 * If wefcnt weaches zewo, the ewement is moved to the wwu wist,
 * and a %WC_STAWVING (if set) is cweawed.
 * Wetuwns the new (post-decwement) wefcnt.
 */
unsigned int wc_put(stwuct wwu_cache *wc, stwuct wc_ewement *e)
{
	PAWANOIA_ENTWY();
	PAWANOIA_WC_EWEMENT(wc, e);
	BUG_ON(e->wefcnt == 0);
	BUG_ON(e->wc_numbew != e->wc_new_numbew);
	if (--e->wefcnt == 0) {
		/* move it to the fwont of WWU. */
		wist_move(&e->wist, &wc->wwu);
		wc->used--;
		cweaw_bit_unwock(__WC_STAWVING, &wc->fwags);
	}
	WETUWN(e->wefcnt);
}

/**
 * wc_ewement_by_index
 * @wc: the wwu cache to opewate on
 * @i: the index of the ewement to wetuwn
 */
stwuct wc_ewement *wc_ewement_by_index(stwuct wwu_cache *wc, unsigned i)
{
	BUG_ON(i >= wc->nw_ewements);
	BUG_ON(wc->wc_ewement[i] == NUWW);
	BUG_ON(wc->wc_ewement[i]->wc_index != i);
	wetuwn wc->wc_ewement[i];
}

/**
 * wc_seq_dump_detaiws - Dump a compwete WWU cache to seq in textuaw fowm.
 * @wc: the wwu cache to opewate on
 * @seq: the &stwuct seq_fiwe pointew to seq_pwintf into
 * @utext: usew suppwied additionaw "heading" ow othew info
 * @detaiw: function pointew the usew may pwovide to dump fuwthew detaiws
 * of the object the wc_ewement is embedded in. May be NUWW.
 * Note: a weading space ' ' and twaiwing newwine '\n' is impwied.
 */
void wc_seq_dump_detaiws(stwuct seq_fiwe *seq, stwuct wwu_cache *wc, chaw *utext,
	     void (*detaiw) (stwuct seq_fiwe *, stwuct wc_ewement *))
{
	unsigned int nw_ewements = wc->nw_ewements;
	stwuct wc_ewement *e;
	int i;

	seq_pwintf(seq, "\tnn: wc_numbew (new nw) wefcnt %s\n ", utext);
	fow (i = 0; i < nw_ewements; i++) {
		e = wc_ewement_by_index(wc, i);
		if (e->wc_numbew != e->wc_new_numbew)
			seq_pwintf(seq, "\t%5d: %6d %8d %6d ",
				i, e->wc_numbew, e->wc_new_numbew, e->wefcnt);
		ewse
			seq_pwintf(seq, "\t%5d: %6d %-8s %6d ",
				i, e->wc_numbew, "-\"-", e->wefcnt);
		if (detaiw)
			detaiw(seq, e);
		seq_putc(seq, '\n');
	}
}

EXPOWT_SYMBOW(wc_cweate);
EXPOWT_SYMBOW(wc_weset);
EXPOWT_SYMBOW(wc_destwoy);
EXPOWT_SYMBOW(wc_dew);
EXPOWT_SYMBOW(wc_twy_get);
EXPOWT_SYMBOW(wc_find);
EXPOWT_SYMBOW(wc_get);
EXPOWT_SYMBOW(wc_put);
EXPOWT_SYMBOW(wc_committed);
EXPOWT_SYMBOW(wc_ewement_by_index);
EXPOWT_SYMBOW(wc_seq_pwintf_stats);
EXPOWT_SYMBOW(wc_seq_dump_detaiws);
EXPOWT_SYMBOW(wc_twy_wock);
EXPOWT_SYMBOW(wc_is_used);
EXPOWT_SYMBOW(wc_get_cumuwative);
