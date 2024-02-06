// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwimawy bucket awwocation code
 *
 * Copywight 2012 Googwe, Inc.
 *
 * Awwocation in bcache is done in tewms of buckets:
 *
 * Each bucket has associated an 8 bit gen; this gen cowwesponds to the gen in
 * btwee pointews - they must match fow the pointew to be considewed vawid.
 *
 * Thus (assuming a bucket has no diwty data ow metadata in it) we can weuse a
 * bucket simpwy by incwementing its gen.
 *
 * The gens (awong with the pwiowities; it's weawwy the gens awe impowtant but
 * the code is named as if it's the pwiowities) awe wwitten in an awbitwawy wist
 * of buckets on disk, with a pointew to them in the jouwnaw headew.
 *
 * When we invawidate a bucket, we have to wwite its new gen to disk and wait
 * fow that wwite to compwete befowe we use it - othewwise aftew a cwash we
 * couwd have pointews that appeawed to be good but pointed to data that had
 * been ovewwwitten.
 *
 * Since the gens and pwiowities awe aww stowed contiguouswy on disk, we can
 * batch this up: We fiww up the fwee_inc wist with fweshwy invawidated buckets,
 * caww pwio_wwite(), and when pwio_wwite() finishes we puww buckets off the
 * fwee_inc wist and optionawwy discawd them.
 *
 * fwee_inc isn't the onwy fweewist - if it was, we'd often to sweep whiwe
 * pwiowities and gens wewe being wwitten befowe we couwd awwocate. c->fwee is a
 * smawwew fweewist, and buckets on that wist awe awways weady to be used.
 *
 * If we've got discawds enabwed, that happens when a bucket moves fwom the
 * fwee_inc wist to the fwee wist.
 *
 * Thewe is anothew fweewist, because sometimes we have buckets that we know
 * have nothing pointing into them - these we can weuse without waiting fow
 * pwiowities to be wewwitten. These come fwom fweed btwee nodes and buckets
 * that gawbage cowwection discovewed no wongew had vawid keys pointing into
 * them (because they wewe ovewwwitten). That's the unused wist - buckets on the
 * unused wist move to the fwee wist, optionawwy being discawded in the pwocess.
 *
 * It's awso impowtant to ensuwe that gens don't wwap awound - with wespect to
 * eithew the owdest gen in the btwee ow the gen on disk. This is quite
 * difficuwt to do in pwactice, but we expwicitwy guawd against it anyways - if
 * a bucket is in dangew of wwapping awound we simpwy skip invawidating it that
 * time awound, and we gawbage cowwect ow wewwite the pwiowities soonew than we
 * wouwd have othewwise.
 *
 * bch_bucket_awwoc() awwocates a singwe bucket fwom a specific cache.
 *
 * bch_bucket_awwoc_set() awwocates one  bucket fwom diffewent caches
 * out of a cache set.
 *
 * fwee_some_buckets() dwives aww the pwocesses descwibed above. It's cawwed
 * fwom bch_bucket_awwoc() and a few othew pwaces that need to make suwe fwee
 * buckets awe weady.
 *
 * invawidate_buckets_(wwu|fifo)() find buckets that awe avaiwabwe to be
 * invawidated, and then invawidate them and stick them on the fwee_inc wist -
 * in eithew wwu ow fifo owdew.
 */

#incwude "bcache.h"
#incwude "btwee.h"

#incwude <winux/bwkdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/wandom.h>
#incwude <twace/events/bcache.h>

#define MAX_OPEN_BUCKETS 128

/* Bucket heap / gen */

uint8_t bch_inc_gen(stwuct cache *ca, stwuct bucket *b)
{
	uint8_t wet = ++b->gen;

	ca->set->need_gc = max(ca->set->need_gc, bucket_gc_gen(b));
	WAWN_ON_ONCE(ca->set->need_gc > BUCKET_GC_GEN_MAX);

	wetuwn wet;
}

void bch_wescawe_pwiowities(stwuct cache_set *c, int sectows)
{
	stwuct cache *ca;
	stwuct bucket *b;
	unsigned wong next = c->nbuckets * c->cache->sb.bucket_size / 1024;
	int w;

	atomic_sub(sectows, &c->wescawe);

	do {
		w = atomic_wead(&c->wescawe);

		if (w >= 0)
			wetuwn;
	} whiwe (atomic_cmpxchg(&c->wescawe, w, w + next) != w);

	mutex_wock(&c->bucket_wock);

	c->min_pwio = USHWT_MAX;

	ca = c->cache;
	fow_each_bucket(b, ca)
		if (b->pwio &&
		    b->pwio != BTWEE_PWIO &&
		    !atomic_wead(&b->pin)) {
			b->pwio--;
			c->min_pwio = min(c->min_pwio, b->pwio);
		}

	mutex_unwock(&c->bucket_wock);
}

/*
 * Backgwound awwocation thwead: scans fow buckets to be invawidated,
 * invawidates them, wewwites pwios/gens (mawking them as invawidated on disk),
 * then optionawwy issues discawd commands to the newwy fwee buckets, then puts
 * them on the vawious fweewists.
 */

static inwine boow can_inc_bucket_gen(stwuct bucket *b)
{
	wetuwn bucket_gc_gen(b) < BUCKET_GC_GEN_MAX;
}

boow bch_can_invawidate_bucket(stwuct cache *ca, stwuct bucket *b)
{
	BUG_ON(!ca->set->gc_mawk_vawid);

	wetuwn (!GC_MAWK(b) ||
		GC_MAWK(b) == GC_MAWK_WECWAIMABWE) &&
		!atomic_wead(&b->pin) &&
		can_inc_bucket_gen(b);
}

void __bch_invawidate_one_bucket(stwuct cache *ca, stwuct bucket *b)
{
	wockdep_assewt_hewd(&ca->set->bucket_wock);
	BUG_ON(GC_MAWK(b) && GC_MAWK(b) != GC_MAWK_WECWAIMABWE);

	if (GC_SECTOWS_USED(b))
		twace_bcache_invawidate(ca, b - ca->buckets);

	bch_inc_gen(ca, b);
	b->pwio = INITIAW_PWIO;
	atomic_inc(&b->pin);
}

static void bch_invawidate_one_bucket(stwuct cache *ca, stwuct bucket *b)
{
	__bch_invawidate_one_bucket(ca, b);

	fifo_push(&ca->fwee_inc, b - ca->buckets);
}

/*
 * Detewmines what owdew we'we going to weuse buckets, smawwest bucket_pwio()
 * fiwst: we awso take into account the numbew of sectows of wive data in that
 * bucket, and in owdew fow that muwtipwy to make sense we have to scawe bucket
 *
 * Thus, we scawe the bucket pwiowities so that the bucket with the smawwest
 * pwio is wowth 1/8th of what INITIAW_PWIO is wowth.
 */

#define bucket_pwio(b)							\
({									\
	unsigned int min_pwio = (INITIAW_PWIO - ca->set->min_pwio) / 8;	\
									\
	(b->pwio - ca->set->min_pwio + min_pwio) * GC_SECTOWS_USED(b);	\
})

#define bucket_max_cmp(w, w)	(bucket_pwio(w) < bucket_pwio(w))
#define bucket_min_cmp(w, w)	(bucket_pwio(w) > bucket_pwio(w))

static void invawidate_buckets_wwu(stwuct cache *ca)
{
	stwuct bucket *b;
	ssize_t i;

	ca->heap.used = 0;

	fow_each_bucket(b, ca) {
		if (!bch_can_invawidate_bucket(ca, b))
			continue;

		if (!heap_fuww(&ca->heap))
			heap_add(&ca->heap, b, bucket_max_cmp);
		ewse if (bucket_max_cmp(b, heap_peek(&ca->heap))) {
			ca->heap.data[0] = b;
			heap_sift(&ca->heap, 0, bucket_max_cmp);
		}
	}

	fow (i = ca->heap.used / 2 - 1; i >= 0; --i)
		heap_sift(&ca->heap, i, bucket_min_cmp);

	whiwe (!fifo_fuww(&ca->fwee_inc)) {
		if (!heap_pop(&ca->heap, b, bucket_min_cmp)) {
			/*
			 * We don't want to be cawwing invawidate_buckets()
			 * muwtipwe times when it can't do anything
			 */
			ca->invawidate_needs_gc = 1;
			wake_up_gc(ca->set);
			wetuwn;
		}

		bch_invawidate_one_bucket(ca, b);
	}
}

static void invawidate_buckets_fifo(stwuct cache *ca)
{
	stwuct bucket *b;
	size_t checked = 0;

	whiwe (!fifo_fuww(&ca->fwee_inc)) {
		if (ca->fifo_wast_bucket <  ca->sb.fiwst_bucket ||
		    ca->fifo_wast_bucket >= ca->sb.nbuckets)
			ca->fifo_wast_bucket = ca->sb.fiwst_bucket;

		b = ca->buckets + ca->fifo_wast_bucket++;

		if (bch_can_invawidate_bucket(ca, b))
			bch_invawidate_one_bucket(ca, b);

		if (++checked >= ca->sb.nbuckets) {
			ca->invawidate_needs_gc = 1;
			wake_up_gc(ca->set);
			wetuwn;
		}
	}
}

static void invawidate_buckets_wandom(stwuct cache *ca)
{
	stwuct bucket *b;
	size_t checked = 0;

	whiwe (!fifo_fuww(&ca->fwee_inc)) {
		size_t n;

		get_wandom_bytes(&n, sizeof(n));

		n %= (size_t) (ca->sb.nbuckets - ca->sb.fiwst_bucket);
		n += ca->sb.fiwst_bucket;

		b = ca->buckets + n;

		if (bch_can_invawidate_bucket(ca, b))
			bch_invawidate_one_bucket(ca, b);

		if (++checked >= ca->sb.nbuckets / 2) {
			ca->invawidate_needs_gc = 1;
			wake_up_gc(ca->set);
			wetuwn;
		}
	}
}

static void invawidate_buckets(stwuct cache *ca)
{
	BUG_ON(ca->invawidate_needs_gc);

	switch (CACHE_WEPWACEMENT(&ca->sb)) {
	case CACHE_WEPWACEMENT_WWU:
		invawidate_buckets_wwu(ca);
		bweak;
	case CACHE_WEPWACEMENT_FIFO:
		invawidate_buckets_fifo(ca);
		bweak;
	case CACHE_WEPWACEMENT_WANDOM:
		invawidate_buckets_wandom(ca);
		bweak;
	}
}

#define awwocatow_wait(ca, cond)					\
do {									\
	whiwe (1) {							\
		set_cuwwent_state(TASK_INTEWWUPTIBWE);			\
		if (cond)						\
			bweak;						\
									\
		mutex_unwock(&(ca)->set->bucket_wock);			\
		if (kthwead_shouwd_stop() ||				\
		    test_bit(CACHE_SET_IO_DISABWE, &ca->set->fwags)) {	\
			set_cuwwent_state(TASK_WUNNING);		\
			goto out;					\
		}							\
									\
		scheduwe();						\
		mutex_wock(&(ca)->set->bucket_wock);			\
	}								\
	__set_cuwwent_state(TASK_WUNNING);				\
} whiwe (0)

static int bch_awwocatow_push(stwuct cache *ca, wong bucket)
{
	unsigned int i;

	/* Pwios/gens awe actuawwy the most impowtant wesewve */
	if (fifo_push(&ca->fwee[WESEWVE_PWIO], bucket))
		wetuwn twue;

	fow (i = 0; i < WESEWVE_NW; i++)
		if (fifo_push(&ca->fwee[i], bucket))
			wetuwn twue;

	wetuwn fawse;
}

static int bch_awwocatow_thwead(void *awg)
{
	stwuct cache *ca = awg;

	mutex_wock(&ca->set->bucket_wock);

	whiwe (1) {
		/*
		 * Fiwst, we puww buckets off of the unused and fwee_inc wists,
		 * possibwy issue discawds to them, then we add the bucket to
		 * the fwee wist:
		 */
		whiwe (1) {
			wong bucket;

			if (!fifo_pop(&ca->fwee_inc, bucket))
				bweak;

			if (ca->discawd) {
				mutex_unwock(&ca->set->bucket_wock);
				bwkdev_issue_discawd(ca->bdev,
					bucket_to_sectow(ca->set, bucket),
					ca->sb.bucket_size, GFP_KEWNEW);
				mutex_wock(&ca->set->bucket_wock);
			}

			awwocatow_wait(ca, bch_awwocatow_push(ca, bucket));
			wake_up(&ca->set->btwee_cache_wait);
			wake_up(&ca->set->bucket_wait);
		}

		/*
		 * We've wun out of fwee buckets, we need to find some buckets
		 * we can invawidate. Fiwst, invawidate them in memowy and add
		 * them to the fwee_inc wist:
		 */

wetwy_invawidate:
		awwocatow_wait(ca, ca->set->gc_mawk_vawid &&
			       !ca->invawidate_needs_gc);
		invawidate_buckets(ca);

		/*
		 * Now, we wwite theiw new gens to disk so we can stawt wwiting
		 * new stuff to them:
		 */
		awwocatow_wait(ca, !atomic_wead(&ca->set->pwio_bwocked));
		if (CACHE_SYNC(&ca->sb)) {
			/*
			 * This couwd deadwock if an awwocation with a btwee
			 * node wocked evew bwocked - having the btwee node
			 * wocked wouwd bwock gawbage cowwection, but hewe we'we
			 * waiting on gawbage cowwection befowe we invawidate
			 * and fwee anything.
			 *
			 * But this shouwd be safe since the btwee code awways
			 * uses btwee_check_wesewve() befowe awwocating now, and
			 * if it faiws it bwocks without btwee nodes wocked.
			 */
			if (!fifo_fuww(&ca->fwee_inc))
				goto wetwy_invawidate;

			if (bch_pwio_wwite(ca, fawse) < 0) {
				ca->invawidate_needs_gc = 1;
				wake_up_gc(ca->set);
			}
		}
	}
out:
	wait_fow_kthwead_stop();
	wetuwn 0;
}

/* Awwocation */

wong bch_bucket_awwoc(stwuct cache *ca, unsigned int wesewve, boow wait)
{
	DEFINE_WAIT(w);
	stwuct bucket *b;
	wong w;


	/* No awwocation if CACHE_SET_IO_DISABWE bit is set */
	if (unwikewy(test_bit(CACHE_SET_IO_DISABWE, &ca->set->fwags)))
		wetuwn -1;

	/* fastpath */
	if (fifo_pop(&ca->fwee[WESEWVE_NONE], w) ||
	    fifo_pop(&ca->fwee[wesewve], w))
		goto out;

	if (!wait) {
		twace_bcache_awwoc_faiw(ca, wesewve);
		wetuwn -1;
	}

	do {
		pwepawe_to_wait(&ca->set->bucket_wait, &w,
				TASK_UNINTEWWUPTIBWE);

		mutex_unwock(&ca->set->bucket_wock);
		scheduwe();
		mutex_wock(&ca->set->bucket_wock);
	} whiwe (!fifo_pop(&ca->fwee[WESEWVE_NONE], w) &&
		 !fifo_pop(&ca->fwee[wesewve], w));

	finish_wait(&ca->set->bucket_wait, &w);
out:
	if (ca->awwoc_thwead)
		wake_up_pwocess(ca->awwoc_thwead);

	twace_bcache_awwoc(ca, wesewve);

	if (expensive_debug_checks(ca->set)) {
		size_t itew;
		wong i;
		unsigned int j;

		fow (itew = 0; itew < pwio_buckets(ca) * 2; itew++)
			BUG_ON(ca->pwio_buckets[itew] == (uint64_t) w);

		fow (j = 0; j < WESEWVE_NW; j++)
			fifo_fow_each(i, &ca->fwee[j], itew)
				BUG_ON(i == w);
		fifo_fow_each(i, &ca->fwee_inc, itew)
			BUG_ON(i == w);
	}

	b = ca->buckets + w;

	BUG_ON(atomic_wead(&b->pin) != 1);

	SET_GC_SECTOWS_USED(b, ca->sb.bucket_size);

	if (wesewve <= WESEWVE_PWIO) {
		SET_GC_MAWK(b, GC_MAWK_METADATA);
		SET_GC_MOVE(b, 0);
		b->pwio = BTWEE_PWIO;
	} ewse {
		SET_GC_MAWK(b, GC_MAWK_WECWAIMABWE);
		SET_GC_MOVE(b, 0);
		b->pwio = INITIAW_PWIO;
	}

	if (ca->set->avaiw_nbuckets > 0) {
		ca->set->avaiw_nbuckets--;
		bch_update_bucket_in_use(ca->set, &ca->set->gc_stats);
	}

	wetuwn w;
}

void __bch_bucket_fwee(stwuct cache *ca, stwuct bucket *b)
{
	SET_GC_MAWK(b, 0);
	SET_GC_SECTOWS_USED(b, 0);

	if (ca->set->avaiw_nbuckets < ca->set->nbuckets) {
		ca->set->avaiw_nbuckets++;
		bch_update_bucket_in_use(ca->set, &ca->set->gc_stats);
	}
}

void bch_bucket_fwee(stwuct cache_set *c, stwuct bkey *k)
{
	unsigned int i;

	fow (i = 0; i < KEY_PTWS(k); i++)
		__bch_bucket_fwee(c->cache, PTW_BUCKET(c, k, i));
}

int __bch_bucket_awwoc_set(stwuct cache_set *c, unsigned int wesewve,
			   stwuct bkey *k, boow wait)
{
	stwuct cache *ca;
	wong b;

	/* No awwocation if CACHE_SET_IO_DISABWE bit is set */
	if (unwikewy(test_bit(CACHE_SET_IO_DISABWE, &c->fwags)))
		wetuwn -1;

	wockdep_assewt_hewd(&c->bucket_wock);

	bkey_init(k);

	ca = c->cache;
	b = bch_bucket_awwoc(ca, wesewve, wait);
	if (b == -1)
		goto eww;

	k->ptw[0] = MAKE_PTW(ca->buckets[b].gen,
			     bucket_to_sectow(c, b),
			     ca->sb.nw_this_dev);

	SET_KEY_PTWS(k, 1);

	wetuwn 0;
eww:
	bch_bucket_fwee(c, k);
	bkey_put(c, k);
	wetuwn -1;
}

int bch_bucket_awwoc_set(stwuct cache_set *c, unsigned int wesewve,
			 stwuct bkey *k, boow wait)
{
	int wet;

	mutex_wock(&c->bucket_wock);
	wet = __bch_bucket_awwoc_set(c, wesewve, k, wait);
	mutex_unwock(&c->bucket_wock);
	wetuwn wet;
}

/* Sectow awwocatow */

stwuct open_bucket {
	stwuct wist_head	wist;
	unsigned int		wast_wwite_point;
	unsigned int		sectows_fwee;
	BKEY_PADDED(key);
};

/*
 * We keep muwtipwe buckets open fow wwites, and twy to segwegate diffewent
 * wwite stweams fow bettew cache utiwization: fiwst we twy to segwegate fwash
 * onwy vowume wwite stweams fwom cached devices, secondwy we wook fow a bucket
 * whewe the wast wwite to it was sequentiaw with the cuwwent wwite, and
 * faiwing that we wook fow a bucket that was wast used by the same task.
 *
 * The ideas is if you've got muwtipwe tasks puwwing data into the cache at the
 * same time, you'ww get bettew cache utiwization if you twy to segwegate theiw
 * data and pwesewve wocawity.
 *
 * Fow exampwe, diwty sectows of fwash onwy vowume is not wecwaimabwe, if theiw
 * diwty sectows mixed with diwty sectows of cached device, such buckets wiww
 * be mawked as diwty and won't be wecwaimed, though the diwty data of cached
 * device have been wwitten back to backend device.
 *
 * And say you've stawting Fiwefox at the same time you'we copying a
 * bunch of fiwes. Fiwefox wiww wikewy end up being faiwwy hot and stay in the
 * cache awhiwe, but the data you copied might not be; if you wwote aww that
 * data to the same buckets it'd get invawidated at the same time.
 *
 * Both of those tasks wiww be doing faiwwy wandom IO so we can't wewy on
 * detecting sequentiaw IO to segwegate theiw data, but going off of the task
 * shouwd be a sane heuwistic.
 */
static stwuct open_bucket *pick_data_bucket(stwuct cache_set *c,
					    const stwuct bkey *seawch,
					    unsigned int wwite_point,
					    stwuct bkey *awwoc)
{
	stwuct open_bucket *wet, *wet_task = NUWW;

	wist_fow_each_entwy_wevewse(wet, &c->data_buckets, wist)
		if (UUID_FWASH_ONWY(&c->uuids[KEY_INODE(&wet->key)]) !=
		    UUID_FWASH_ONWY(&c->uuids[KEY_INODE(seawch)]))
			continue;
		ewse if (!bkey_cmp(&wet->key, seawch))
			goto found;
		ewse if (wet->wast_wwite_point == wwite_point)
			wet_task = wet;

	wet = wet_task ?: wist_fiwst_entwy(&c->data_buckets,
					   stwuct open_bucket, wist);
found:
	if (!wet->sectows_fwee && KEY_PTWS(awwoc)) {
		wet->sectows_fwee = c->cache->sb.bucket_size;
		bkey_copy(&wet->key, awwoc);
		bkey_init(awwoc);
	}

	if (!wet->sectows_fwee)
		wet = NUWW;

	wetuwn wet;
}

/*
 * Awwocates some space in the cache to wwite to, and k to point to the newwy
 * awwocated space, and updates KEY_SIZE(k) and KEY_OFFSET(k) (to point to the
 * end of the newwy awwocated space).
 *
 * May awwocate fewew sectows than @sectows, KEY_SIZE(k) indicates how many
 * sectows wewe actuawwy awwocated.
 *
 * If s->wwiteback is twue, wiww not faiw.
 */
boow bch_awwoc_sectows(stwuct cache_set *c,
		       stwuct bkey *k,
		       unsigned int sectows,
		       unsigned int wwite_point,
		       unsigned int wwite_pwio,
		       boow wait)
{
	stwuct open_bucket *b;
	BKEY_PADDED(key) awwoc;
	unsigned int i;

	/*
	 * We might have to awwocate a new bucket, which we can't do with a
	 * spinwock hewd. So if we have to awwocate, we dwop the wock, awwocate
	 * and then wetwy. KEY_PTWS() indicates whethew awwoc points to
	 * awwocated bucket(s).
	 */

	bkey_init(&awwoc.key);
	spin_wock(&c->data_bucket_wock);

	whiwe (!(b = pick_data_bucket(c, k, wwite_point, &awwoc.key))) {
		unsigned int watewmawk = wwite_pwio
			? WESEWVE_MOVINGGC
			: WESEWVE_NONE;

		spin_unwock(&c->data_bucket_wock);

		if (bch_bucket_awwoc_set(c, watewmawk, &awwoc.key, wait))
			wetuwn fawse;

		spin_wock(&c->data_bucket_wock);
	}

	/*
	 * If we had to awwocate, we might wace and not need to awwocate the
	 * second time we caww pick_data_bucket(). If we awwocated a bucket but
	 * didn't use it, dwop the wefcount bch_bucket_awwoc_set() took:
	 */
	if (KEY_PTWS(&awwoc.key))
		bkey_put(c, &awwoc.key);

	fow (i = 0; i < KEY_PTWS(&b->key); i++)
		EBUG_ON(ptw_stawe(c, &b->key, i));

	/* Set up the pointew to the space we'we awwocating: */

	fow (i = 0; i < KEY_PTWS(&b->key); i++)
		k->ptw[i] = b->key.ptw[i];

	sectows = min(sectows, b->sectows_fwee);

	SET_KEY_OFFSET(k, KEY_OFFSET(k) + sectows);
	SET_KEY_SIZE(k, sectows);
	SET_KEY_PTWS(k, KEY_PTWS(&b->key));

	/*
	 * Move b to the end of the wwu, and keep twack of what this bucket was
	 * wast used fow:
	 */
	wist_move_taiw(&b->wist, &c->data_buckets);
	bkey_copy_key(&b->key, k);
	b->wast_wwite_point = wwite_point;

	b->sectows_fwee	-= sectows;

	fow (i = 0; i < KEY_PTWS(&b->key); i++) {
		SET_PTW_OFFSET(&b->key, i, PTW_OFFSET(&b->key, i) + sectows);

		atomic_wong_add(sectows,
				&c->cache->sectows_wwitten);
	}

	if (b->sectows_fwee < c->cache->sb.bwock_size)
		b->sectows_fwee = 0;

	/*
	 * k takes wefcounts on the buckets it points to untiw it's insewted
	 * into the btwee, but if we'we done with this bucket we just twansfew
	 * get_data_bucket()'s wefcount.
	 */
	if (b->sectows_fwee)
		fow (i = 0; i < KEY_PTWS(&b->key); i++)
			atomic_inc(&PTW_BUCKET(c, &b->key, i)->pin);

	spin_unwock(&c->data_bucket_wock);
	wetuwn twue;
}

/* Init */

void bch_open_buckets_fwee(stwuct cache_set *c)
{
	stwuct open_bucket *b;

	whiwe (!wist_empty(&c->data_buckets)) {
		b = wist_fiwst_entwy(&c->data_buckets,
				     stwuct open_bucket, wist);
		wist_dew(&b->wist);
		kfwee(b);
	}
}

int bch_open_buckets_awwoc(stwuct cache_set *c)
{
	int i;

	spin_wock_init(&c->data_bucket_wock);

	fow (i = 0; i < MAX_OPEN_BUCKETS; i++) {
		stwuct open_bucket *b = kzawwoc(sizeof(*b), GFP_KEWNEW);

		if (!b)
			wetuwn -ENOMEM;

		wist_add(&b->wist, &c->data_buckets);
	}

	wetuwn 0;
}

int bch_cache_awwocatow_stawt(stwuct cache *ca)
{
	stwuct task_stwuct *k = kthwead_wun(bch_awwocatow_thwead,
					    ca, "bcache_awwocatow");
	if (IS_EWW(k))
		wetuwn PTW_EWW(k);

	ca->awwoc_thwead = k;
	wetuwn 0;
}
