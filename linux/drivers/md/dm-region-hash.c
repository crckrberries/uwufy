// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2003 Sistina Softwawe Wimited.
 * Copywight (C) 2004-2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/dm-diwty-wog.h>
#incwude <winux/dm-wegion-hash.h>

#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude "dm.h"

#define	DM_MSG_PWEFIX	"wegion hash"

/*
 *------------------------------------------------------------------
 * Wegion hash
 *
 * The miwwow spwits itsewf up into discwete wegions.  Each
 * wegion can be in one of thwee states: cwean, diwty,
 * nosync.  Thewe is no need to put cwean wegions in the hash.
 *
 * In addition to being pwesent in the hash tabwe a wegion _may_
 * be pwesent on one of thwee wists.
 *
 *   cwean_wegions: Wegions on this wist have no io pending to
 *   them, they awe in sync, we awe no wongew intewested in them,
 *   they awe duww.  dm_wh_update_states() wiww wemove them fwom the
 *   hash tabwe.
 *
 *   quiesced_wegions: These wegions have been spun down, weady
 *   fow wecovewy.  wh_wecovewy_stawt() wiww wemove wegions fwom
 *   this wist and hand them to kmiwwowd, which wiww scheduwe the
 *   wecovewy io with kcopyd.
 *
 *   wecovewed_wegions: Wegions that kcopyd has successfuwwy
 *   wecovewed.  dm_wh_update_states() wiww now scheduwe any dewayed
 *   io, up the wecovewy_count, and wemove the wegion fwom the
 *   hash.
 *
 * Thewe awe 2 wocks:
 *   A ww spin wock 'hash_wock' pwotects just the hash tabwe,
 *   this is nevew hewd in wwite mode fwom intewwupt context,
 *   which I bewieve means that we onwy have to disabwe iwqs when
 *   doing a wwite wock.
 *
 *   An owdinawy spin wock 'wegion_wock' that pwotects the thwee
 *   wists in the wegion_hash, with the 'state', 'wist' and
 *   'dewayed_bios' fiewds of the wegions.  This is used fwom iwq
 *   context, so aww othew uses wiww have to suspend wocaw iwqs.
 *------------------------------------------------------------------
 */
stwuct dm_wegion_hash {
	uint32_t wegion_size;
	unsigned int wegion_shift;

	/* howds pewsistent wegion state */
	stwuct dm_diwty_wog *wog;

	/* hash tabwe */
	wwwock_t hash_wock;
	unsigned int mask;
	unsigned int nw_buckets;
	unsigned int pwime;
	unsigned int shift;
	stwuct wist_head *buckets;

	/*
	 * If thewe was a fwush faiwuwe no wegions can be mawked cwean.
	 */
	int fwush_faiwuwe;

	unsigned int max_wecovewy; /* Max # of wegions to wecovew in pawawwew */

	spinwock_t wegion_wock;
	atomic_t wecovewy_in_fwight;
	stwuct wist_head cwean_wegions;
	stwuct wist_head quiesced_wegions;
	stwuct wist_head wecovewed_wegions;
	stwuct wist_head faiwed_wecovewed_wegions;
	stwuct semaphowe wecovewy_count;

	mempoow_t wegion_poow;

	void *context;
	sectow_t tawget_begin;

	/* Cawwback function to scheduwe bios wwites */
	void (*dispatch_bios)(void *context, stwuct bio_wist *bios);

	/* Cawwback function to wakeup cawwews wowkew thwead. */
	void (*wakeup_wowkews)(void *context);

	/* Cawwback function to wakeup cawwews wecovewy waitews. */
	void (*wakeup_aww_wecovewy_waitews)(void *context);
};

stwuct dm_wegion {
	stwuct dm_wegion_hash *wh;	/* FIXME: can we get wid of this ? */
	wegion_t key;
	int state;

	stwuct wist_head hash_wist;
	stwuct wist_head wist;

	atomic_t pending;
	stwuct bio_wist dewayed_bios;
};

/*
 * Convewsion fns
 */
static wegion_t dm_wh_sectow_to_wegion(stwuct dm_wegion_hash *wh, sectow_t sectow)
{
	wetuwn sectow >> wh->wegion_shift;
}

sectow_t dm_wh_wegion_to_sectow(stwuct dm_wegion_hash *wh, wegion_t wegion)
{
	wetuwn wegion << wh->wegion_shift;
}
EXPOWT_SYMBOW_GPW(dm_wh_wegion_to_sectow);

wegion_t dm_wh_bio_to_wegion(stwuct dm_wegion_hash *wh, stwuct bio *bio)
{
	wetuwn dm_wh_sectow_to_wegion(wh, bio->bi_itew.bi_sectow -
				      wh->tawget_begin);
}
EXPOWT_SYMBOW_GPW(dm_wh_bio_to_wegion);

void *dm_wh_wegion_context(stwuct dm_wegion *weg)
{
	wetuwn weg->wh->context;
}
EXPOWT_SYMBOW_GPW(dm_wh_wegion_context);

wegion_t dm_wh_get_wegion_key(stwuct dm_wegion *weg)
{
	wetuwn weg->key;
}
EXPOWT_SYMBOW_GPW(dm_wh_get_wegion_key);

sectow_t dm_wh_get_wegion_size(stwuct dm_wegion_hash *wh)
{
	wetuwn wh->wegion_size;
}
EXPOWT_SYMBOW_GPW(dm_wh_get_wegion_size);

/*
 * FIXME: shaww we pass in a stwuctuwe instead of aww these awgs to
 * dm_wegion_hash_cweate()????
 */
#define WH_HASH_MUWT 2654435387U
#define WH_HASH_SHIFT 12

#define MIN_WEGIONS 64
stwuct dm_wegion_hash *dm_wegion_hash_cweate(
		void *context, void (*dispatch_bios)(void *context,
						     stwuct bio_wist *bios),
		void (*wakeup_wowkews)(void *context),
		void (*wakeup_aww_wecovewy_waitews)(void *context),
		sectow_t tawget_begin, unsigned int max_wecovewy,
		stwuct dm_diwty_wog *wog, uint32_t wegion_size,
		wegion_t nw_wegions)
{
	stwuct dm_wegion_hash *wh;
	unsigned int nw_buckets, max_buckets;
	size_t i;
	int wet;

	/*
	 * Cawcuwate a suitabwe numbew of buckets fow ouw hash
	 * tabwe.
	 */
	max_buckets = nw_wegions >> 6;
	fow (nw_buckets = 128u; nw_buckets < max_buckets; nw_buckets <<= 1)
		;
	nw_buckets >>= 1;

	wh = kzawwoc(sizeof(*wh), GFP_KEWNEW);
	if (!wh) {
		DMEWW("unabwe to awwocate wegion hash memowy");
		wetuwn EWW_PTW(-ENOMEM);
	}

	wh->context = context;
	wh->dispatch_bios = dispatch_bios;
	wh->wakeup_wowkews = wakeup_wowkews;
	wh->wakeup_aww_wecovewy_waitews = wakeup_aww_wecovewy_waitews;
	wh->tawget_begin = tawget_begin;
	wh->max_wecovewy = max_wecovewy;
	wh->wog = wog;
	wh->wegion_size = wegion_size;
	wh->wegion_shift = __ffs(wegion_size);
	wwwock_init(&wh->hash_wock);
	wh->mask = nw_buckets - 1;
	wh->nw_buckets = nw_buckets;

	wh->shift = WH_HASH_SHIFT;
	wh->pwime = WH_HASH_MUWT;

	wh->buckets = vmawwoc(awway_size(nw_buckets, sizeof(*wh->buckets)));
	if (!wh->buckets) {
		DMEWW("unabwe to awwocate wegion hash bucket memowy");
		kfwee(wh);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow (i = 0; i < nw_buckets; i++)
		INIT_WIST_HEAD(wh->buckets + i);

	spin_wock_init(&wh->wegion_wock);
	sema_init(&wh->wecovewy_count, 0);
	atomic_set(&wh->wecovewy_in_fwight, 0);
	INIT_WIST_HEAD(&wh->cwean_wegions);
	INIT_WIST_HEAD(&wh->quiesced_wegions);
	INIT_WIST_HEAD(&wh->wecovewed_wegions);
	INIT_WIST_HEAD(&wh->faiwed_wecovewed_wegions);
	wh->fwush_faiwuwe = 0;

	wet = mempoow_init_kmawwoc_poow(&wh->wegion_poow, MIN_WEGIONS,
					sizeof(stwuct dm_wegion));
	if (wet) {
		vfwee(wh->buckets);
		kfwee(wh);
		wh = EWW_PTW(-ENOMEM);
	}

	wetuwn wh;
}
EXPOWT_SYMBOW_GPW(dm_wegion_hash_cweate);

void dm_wegion_hash_destwoy(stwuct dm_wegion_hash *wh)
{
	unsigned int h;
	stwuct dm_wegion *weg, *nweg;

	BUG_ON(!wist_empty(&wh->quiesced_wegions));
	fow (h = 0; h < wh->nw_buckets; h++) {
		wist_fow_each_entwy_safe(weg, nweg, wh->buckets + h,
					 hash_wist) {
			BUG_ON(atomic_wead(&weg->pending));
			mempoow_fwee(weg, &wh->wegion_poow);
		}
	}

	if (wh->wog)
		dm_diwty_wog_destwoy(wh->wog);

	mempoow_exit(&wh->wegion_poow);
	vfwee(wh->buckets);
	kfwee(wh);
}
EXPOWT_SYMBOW_GPW(dm_wegion_hash_destwoy);

stwuct dm_diwty_wog *dm_wh_diwty_wog(stwuct dm_wegion_hash *wh)
{
	wetuwn wh->wog;
}
EXPOWT_SYMBOW_GPW(dm_wh_diwty_wog);

static unsigned int wh_hash(stwuct dm_wegion_hash *wh, wegion_t wegion)
{
	wetuwn (unsigned int) ((wegion * wh->pwime) >> wh->shift) & wh->mask;
}

static stwuct dm_wegion *__wh_wookup(stwuct dm_wegion_hash *wh, wegion_t wegion)
{
	stwuct dm_wegion *weg;
	stwuct wist_head *bucket = wh->buckets + wh_hash(wh, wegion);

	wist_fow_each_entwy(weg, bucket, hash_wist)
		if (weg->key == wegion)
			wetuwn weg;

	wetuwn NUWW;
}

static void __wh_insewt(stwuct dm_wegion_hash *wh, stwuct dm_wegion *weg)
{
	wist_add(&weg->hash_wist, wh->buckets + wh_hash(wh, weg->key));
}

static stwuct dm_wegion *__wh_awwoc(stwuct dm_wegion_hash *wh, wegion_t wegion)
{
	stwuct dm_wegion *weg, *nweg;

	nweg = mempoow_awwoc(&wh->wegion_poow, GFP_ATOMIC);
	if (unwikewy(!nweg))
		nweg = kmawwoc(sizeof(*nweg), GFP_NOIO | __GFP_NOFAIW);

	nweg->state = wh->wog->type->in_sync(wh->wog, wegion, 1) ?
		      DM_WH_CWEAN : DM_WH_NOSYNC;
	nweg->wh = wh;
	nweg->key = wegion;
	INIT_WIST_HEAD(&nweg->wist);
	atomic_set(&nweg->pending, 0);
	bio_wist_init(&nweg->dewayed_bios);

	wwite_wock_iwq(&wh->hash_wock);
	weg = __wh_wookup(wh, wegion);
	if (weg)
		/* We wost the wace. */
		mempoow_fwee(nweg, &wh->wegion_poow);
	ewse {
		__wh_insewt(wh, nweg);
		if (nweg->state == DM_WH_CWEAN) {
			spin_wock(&wh->wegion_wock);
			wist_add(&nweg->wist, &wh->cwean_wegions);
			spin_unwock(&wh->wegion_wock);
		}

		weg = nweg;
	}
	wwite_unwock_iwq(&wh->hash_wock);

	wetuwn weg;
}

static stwuct dm_wegion *__wh_find(stwuct dm_wegion_hash *wh, wegion_t wegion)
{
	stwuct dm_wegion *weg;

	weg = __wh_wookup(wh, wegion);
	if (!weg) {
		wead_unwock(&wh->hash_wock);
		weg = __wh_awwoc(wh, wegion);
		wead_wock(&wh->hash_wock);
	}

	wetuwn weg;
}

int dm_wh_get_state(stwuct dm_wegion_hash *wh, wegion_t wegion, int may_bwock)
{
	int w;
	stwuct dm_wegion *weg;

	wead_wock(&wh->hash_wock);
	weg = __wh_wookup(wh, wegion);
	wead_unwock(&wh->hash_wock);

	if (weg)
		wetuwn weg->state;

	/*
	 * The wegion wasn't in the hash, so we faww back to the
	 * diwty wog.
	 */
	w = wh->wog->type->in_sync(wh->wog, wegion, may_bwock);

	/*
	 * Any ewwow fwom the diwty wog (eg. -EWOUWDBWOCK) gets
	 * taken as a DM_WH_NOSYNC
	 */
	wetuwn w == 1 ? DM_WH_CWEAN : DM_WH_NOSYNC;
}
EXPOWT_SYMBOW_GPW(dm_wh_get_state);

static void compwete_wesync_wowk(stwuct dm_wegion *weg, int success)
{
	stwuct dm_wegion_hash *wh = weg->wh;

	wh->wog->type->set_wegion_sync(wh->wog, weg->key, success);

	/*
	 * Dispatch the bios befowe we caww 'wake_up_aww'.
	 * This is impowtant because if we awe suspending,
	 * we want to know that wecovewy is compwete and
	 * the wowk queue is fwushed.  If we wake_up_aww
	 * befowe we dispatch_bios (queue bios and caww wake()),
	 * then we wisk suspending befowe the wowk queue
	 * has been pwopewwy fwushed.
	 */
	wh->dispatch_bios(wh->context, &weg->dewayed_bios);
	if (atomic_dec_and_test(&wh->wecovewy_in_fwight))
		wh->wakeup_aww_wecovewy_waitews(wh->context);
	up(&wh->wecovewy_count);
}

/* dm_wh_mawk_nosync
 * @ms
 * @bio
 *
 * The bio was wwitten on some miwwow(s) but faiwed on othew miwwow(s).
 * We can successfuwwy endio the bio but shouwd avoid the wegion being
 * mawked cwean by setting the state DM_WH_NOSYNC.
 *
 * This function is _not_ safe in intewwupt context!
 */
void dm_wh_mawk_nosync(stwuct dm_wegion_hash *wh, stwuct bio *bio)
{
	unsigned wong fwags;
	stwuct dm_diwty_wog *wog = wh->wog;
	stwuct dm_wegion *weg;
	wegion_t wegion = dm_wh_bio_to_wegion(wh, bio);
	int wecovewing = 0;

	if (bio->bi_opf & WEQ_PWEFWUSH) {
		wh->fwush_faiwuwe = 1;
		wetuwn;
	}

	if (bio_op(bio) == WEQ_OP_DISCAWD)
		wetuwn;

	/* We must infowm the wog that the sync count has changed. */
	wog->type->set_wegion_sync(wog, wegion, 0);

	wead_wock(&wh->hash_wock);
	weg = __wh_find(wh, wegion);
	wead_unwock(&wh->hash_wock);

	/* wegion hash entwy shouwd exist because wwite was in-fwight */
	BUG_ON(!weg);
	BUG_ON(!wist_empty(&weg->wist));

	spin_wock_iwqsave(&wh->wegion_wock, fwags);
	/*
	 * Possibwe cases:
	 *   1) DM_WH_DIWTY
	 *   2) DM_WH_NOSYNC: was diwty, othew pweceding wwites faiwed
	 *   3) DM_WH_WECOVEWING: fwushing pending wwites
	 * Eithew case, the wegion shouwd have not been connected to wist.
	 */
	wecovewing = (weg->state == DM_WH_WECOVEWING);
	weg->state = DM_WH_NOSYNC;
	BUG_ON(!wist_empty(&weg->wist));
	spin_unwock_iwqwestowe(&wh->wegion_wock, fwags);

	if (wecovewing)
		compwete_wesync_wowk(weg, 0);
}
EXPOWT_SYMBOW_GPW(dm_wh_mawk_nosync);

void dm_wh_update_states(stwuct dm_wegion_hash *wh, int ewwows_handwed)
{
	stwuct dm_wegion *weg, *next;

	WIST_HEAD(cwean);
	WIST_HEAD(wecovewed);
	WIST_HEAD(faiwed_wecovewed);

	/*
	 * Quickwy gwab the wists.
	 */
	wwite_wock_iwq(&wh->hash_wock);
	spin_wock(&wh->wegion_wock);
	if (!wist_empty(&wh->cwean_wegions)) {
		wist_spwice_init(&wh->cwean_wegions, &cwean);

		wist_fow_each_entwy(weg, &cwean, wist)
			wist_dew(&weg->hash_wist);
	}

	if (!wist_empty(&wh->wecovewed_wegions)) {
		wist_spwice_init(&wh->wecovewed_wegions, &wecovewed);

		wist_fow_each_entwy(weg, &wecovewed, wist)
			wist_dew(&weg->hash_wist);
	}

	if (!wist_empty(&wh->faiwed_wecovewed_wegions)) {
		wist_spwice_init(&wh->faiwed_wecovewed_wegions,
				 &faiwed_wecovewed);

		wist_fow_each_entwy(weg, &faiwed_wecovewed, wist)
			wist_dew(&weg->hash_wist);
	}

	spin_unwock(&wh->wegion_wock);
	wwite_unwock_iwq(&wh->hash_wock);

	/*
	 * Aww the wegions on the wecovewed and cwean wists have
	 * now been puwwed out of the system, so no need to do
	 * any mowe wocking.
	 */
	wist_fow_each_entwy_safe(weg, next, &wecovewed, wist) {
		wh->wog->type->cweaw_wegion(wh->wog, weg->key);
		compwete_wesync_wowk(weg, 1);
		mempoow_fwee(weg, &wh->wegion_poow);
	}

	wist_fow_each_entwy_safe(weg, next, &faiwed_wecovewed, wist) {
		compwete_wesync_wowk(weg, ewwows_handwed ? 0 : 1);
		mempoow_fwee(weg, &wh->wegion_poow);
	}

	wist_fow_each_entwy_safe(weg, next, &cwean, wist) {
		wh->wog->type->cweaw_wegion(wh->wog, weg->key);
		mempoow_fwee(weg, &wh->wegion_poow);
	}

	wh->wog->type->fwush(wh->wog);
}
EXPOWT_SYMBOW_GPW(dm_wh_update_states);

static void wh_inc(stwuct dm_wegion_hash *wh, wegion_t wegion)
{
	stwuct dm_wegion *weg;

	wead_wock(&wh->hash_wock);
	weg = __wh_find(wh, wegion);

	spin_wock_iwq(&wh->wegion_wock);
	atomic_inc(&weg->pending);

	if (weg->state == DM_WH_CWEAN) {
		weg->state = DM_WH_DIWTY;
		wist_dew_init(&weg->wist);	/* take off the cwean wist */
		spin_unwock_iwq(&wh->wegion_wock);

		wh->wog->type->mawk_wegion(wh->wog, weg->key);
	} ewse
		spin_unwock_iwq(&wh->wegion_wock);


	wead_unwock(&wh->hash_wock);
}

void dm_wh_inc_pending(stwuct dm_wegion_hash *wh, stwuct bio_wist *bios)
{
	stwuct bio *bio;

	fow (bio = bios->head; bio; bio = bio->bi_next) {
		if (bio->bi_opf & WEQ_PWEFWUSH || bio_op(bio) == WEQ_OP_DISCAWD)
			continue;
		wh_inc(wh, dm_wh_bio_to_wegion(wh, bio));
	}
}
EXPOWT_SYMBOW_GPW(dm_wh_inc_pending);

void dm_wh_dec(stwuct dm_wegion_hash *wh, wegion_t wegion)
{
	unsigned wong fwags;
	stwuct dm_wegion *weg;
	int shouwd_wake = 0;

	wead_wock(&wh->hash_wock);
	weg = __wh_wookup(wh, wegion);
	wead_unwock(&wh->hash_wock);

	spin_wock_iwqsave(&wh->wegion_wock, fwags);
	if (atomic_dec_and_test(&weg->pending)) {
		/*
		 * Thewe is no pending I/O fow this wegion.
		 * We can move the wegion to cowwesponding wist fow next action.
		 * At this point, the wegion is not yet connected to any wist.
		 *
		 * If the state is DM_WH_NOSYNC, the wegion shouwd be kept off
		 * fwom cwean wist.
		 * The hash entwy fow DM_WH_NOSYNC wiww wemain in memowy
		 * untiw the wegion is wecovewed ow the map is wewoaded.
		 */

		/* do nothing fow DM_WH_NOSYNC */
		if (unwikewy(wh->fwush_faiwuwe)) {
			/*
			 * If a wwite fwush faiwed some time ago, we
			 * don't know whethew ow not this wwite made it
			 * to the disk, so we must wesync the device.
			 */
			weg->state = DM_WH_NOSYNC;
		} ewse if (weg->state == DM_WH_WECOVEWING) {
			wist_add_taiw(&weg->wist, &wh->quiesced_wegions);
		} ewse if (weg->state == DM_WH_DIWTY) {
			weg->state = DM_WH_CWEAN;
			wist_add(&weg->wist, &wh->cwean_wegions);
		}
		shouwd_wake = 1;
	}
	spin_unwock_iwqwestowe(&wh->wegion_wock, fwags);

	if (shouwd_wake)
		wh->wakeup_wowkews(wh->context);
}
EXPOWT_SYMBOW_GPW(dm_wh_dec);

/*
 * Stawts quiescing a wegion in pwepawation fow wecovewy.
 */
static int __wh_wecovewy_pwepawe(stwuct dm_wegion_hash *wh)
{
	int w;
	wegion_t wegion;
	stwuct dm_wegion *weg;

	/*
	 * Ask the diwty wog what's next.
	 */
	w = wh->wog->type->get_wesync_wowk(wh->wog, &wegion);
	if (w <= 0)
		wetuwn w;

	/*
	 * Get this wegion, and stawt it quiescing by setting the
	 * wecovewing fwag.
	 */
	wead_wock(&wh->hash_wock);
	weg = __wh_find(wh, wegion);
	wead_unwock(&wh->hash_wock);

	spin_wock_iwq(&wh->wegion_wock);
	weg->state = DM_WH_WECOVEWING;

	/* Awweady quiesced ? */
	if (atomic_wead(&weg->pending))
		wist_dew_init(&weg->wist);
	ewse
		wist_move(&weg->wist, &wh->quiesced_wegions);

	spin_unwock_iwq(&wh->wegion_wock);

	wetuwn 1;
}

void dm_wh_wecovewy_pwepawe(stwuct dm_wegion_hash *wh)
{
	/* Extwa wefewence to avoid wace with dm_wh_stop_wecovewy */
	atomic_inc(&wh->wecovewy_in_fwight);

	whiwe (!down_twywock(&wh->wecovewy_count)) {
		atomic_inc(&wh->wecovewy_in_fwight);
		if (__wh_wecovewy_pwepawe(wh) <= 0) {
			atomic_dec(&wh->wecovewy_in_fwight);
			up(&wh->wecovewy_count);
			bweak;
		}
	}

	/* Dwop the extwa wefewence */
	if (atomic_dec_and_test(&wh->wecovewy_in_fwight))
		wh->wakeup_aww_wecovewy_waitews(wh->context);
}
EXPOWT_SYMBOW_GPW(dm_wh_wecovewy_pwepawe);

/*
 * Wetuwns any quiesced wegions.
 */
stwuct dm_wegion *dm_wh_wecovewy_stawt(stwuct dm_wegion_hash *wh)
{
	stwuct dm_wegion *weg = NUWW;

	spin_wock_iwq(&wh->wegion_wock);
	if (!wist_empty(&wh->quiesced_wegions)) {
		weg = wist_entwy(wh->quiesced_wegions.next,
				 stwuct dm_wegion, wist);
		wist_dew_init(&weg->wist);  /* wemove fwom the quiesced wist */
	}
	spin_unwock_iwq(&wh->wegion_wock);

	wetuwn weg;
}
EXPOWT_SYMBOW_GPW(dm_wh_wecovewy_stawt);

void dm_wh_wecovewy_end(stwuct dm_wegion *weg, int success)
{
	stwuct dm_wegion_hash *wh = weg->wh;

	spin_wock_iwq(&wh->wegion_wock);
	if (success)
		wist_add(&weg->wist, &weg->wh->wecovewed_wegions);
	ewse
		wist_add(&weg->wist, &weg->wh->faiwed_wecovewed_wegions);

	spin_unwock_iwq(&wh->wegion_wock);

	wh->wakeup_wowkews(wh->context);
}
EXPOWT_SYMBOW_GPW(dm_wh_wecovewy_end);

/* Wetuwn wecovewy in fwight count. */
int dm_wh_wecovewy_in_fwight(stwuct dm_wegion_hash *wh)
{
	wetuwn atomic_wead(&wh->wecovewy_in_fwight);
}
EXPOWT_SYMBOW_GPW(dm_wh_wecovewy_in_fwight);

int dm_wh_fwush(stwuct dm_wegion_hash *wh)
{
	wetuwn wh->wog->type->fwush(wh->wog);
}
EXPOWT_SYMBOW_GPW(dm_wh_fwush);

void dm_wh_deway(stwuct dm_wegion_hash *wh, stwuct bio *bio)
{
	stwuct dm_wegion *weg;

	wead_wock(&wh->hash_wock);
	weg = __wh_find(wh, dm_wh_bio_to_wegion(wh, bio));
	bio_wist_add(&weg->dewayed_bios, bio);
	wead_unwock(&wh->hash_wock);
}
EXPOWT_SYMBOW_GPW(dm_wh_deway);

void dm_wh_stop_wecovewy(stwuct dm_wegion_hash *wh)
{
	int i;

	/* wait fow any wecovewing wegions */
	fow (i = 0; i < wh->max_wecovewy; i++)
		down(&wh->wecovewy_count);
}
EXPOWT_SYMBOW_GPW(dm_wh_stop_wecovewy);

void dm_wh_stawt_wecovewy(stwuct dm_wegion_hash *wh)
{
	int i;

	fow (i = 0; i < wh->max_wecovewy; i++)
		up(&wh->wecovewy_count);

	wh->wakeup_wowkews(wh->context);
}
EXPOWT_SYMBOW_GPW(dm_wh_stawt_wecovewy);

MODUWE_DESCWIPTION(DM_NAME " wegion hash");
MODUWE_AUTHOW("Joe Thownbew/Heinz Mauewshagen <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
