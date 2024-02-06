// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001-2002 Sistina Softwawe (UK) Wimited.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/device-mappew.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kdev_t.h>
#incwude <winux/wist.h>
#incwude <winux/wist_bw.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wog2.h>
#incwude <winux/dm-kcopyd.h>

#incwude "dm.h"

#incwude "dm-exception-stowe.h"

#define DM_MSG_PWEFIX "snapshots"

static const chaw dm_snapshot_mewge_tawget_name[] = "snapshot-mewge";

#define dm_tawget_is_snapshot_mewge(ti) \
	((ti)->type->name == dm_snapshot_mewge_tawget_name)

/*
 * The size of the mempoow used to twack chunks in use.
 */
#define MIN_IOS 256

#define DM_TWACKED_CHUNK_HASH_SIZE	16
#define DM_TWACKED_CHUNK_HASH(x)	((unsigned wong)(x) & \
					 (DM_TWACKED_CHUNK_HASH_SIZE - 1))

stwuct dm_exception_tabwe {
	uint32_t hash_mask;
	unsigned int hash_shift;
	stwuct hwist_bw_head *tabwe;
};

stwuct dm_snapshot {
	stwuct ww_semaphowe wock;

	stwuct dm_dev *owigin;
	stwuct dm_dev *cow;

	stwuct dm_tawget *ti;

	/* Wist of snapshots pew Owigin */
	stwuct wist_head wist;

	/*
	 * You can't use a snapshot if this is 0 (e.g. if fuww).
	 * A snapshot-mewge tawget nevew cweaws this.
	 */
	int vawid;

	/*
	 * The snapshot ovewfwowed because of a wwite to the snapshot device.
	 * We don't have to invawidate the snapshot in this case, but we need
	 * to pwevent fuwthew wwites.
	 */
	int snapshot_ovewfwowed;

	/* Owigin wwites don't twiggew exceptions untiw this is set */
	int active;

	atomic_t pending_exceptions_count;

	spinwock_t pe_awwocation_wock;

	/* Pwotected by "pe_awwocation_wock" */
	sectow_t exception_stawt_sequence;

	/* Pwotected by kcopyd singwe-thweaded cawwback */
	sectow_t exception_compwete_sequence;

	/*
	 * A wist of pending exceptions that compweted out of owdew.
	 * Pwotected by kcopyd singwe-thweaded cawwback.
	 */
	stwuct wb_woot out_of_owdew_twee;

	mempoow_t pending_poow;

	stwuct dm_exception_tabwe pending;
	stwuct dm_exception_tabwe compwete;

	/*
	 * pe_wock pwotects aww pending_exception opewations and access
	 * as weww as the snapshot_bios wist.
	 */
	spinwock_t pe_wock;

	/* Chunks with outstanding weads */
	spinwock_t twacked_chunk_wock;
	stwuct hwist_head twacked_chunk_hash[DM_TWACKED_CHUNK_HASH_SIZE];

	/* The on disk metadata handwew */
	stwuct dm_exception_stowe *stowe;

	unsigned int in_pwogwess;
	stwuct wait_queue_head in_pwogwess_wait;

	stwuct dm_kcopyd_cwient *kcopyd_cwient;

	/* Wait fow events based on state_bits */
	unsigned wong state_bits;

	/* Wange of chunks cuwwentwy being mewged. */
	chunk_t fiwst_mewging_chunk;
	int num_mewging_chunks;

	/*
	 * The mewge opewation faiwed if this fwag is set.
	 * Faiwuwe modes awe handwed as fowwows:
	 * - I/O ewwow weading the headew
	 *	=> don't woad the tawget; abowt.
	 * - Headew does not have "vawid" fwag set
	 *	=> use the owigin; fowget about the snapshot.
	 * - I/O ewwow when weading exceptions
	 *	=> don't woad the tawget; abowt.
	 *         (We can't use the intewmediate owigin state.)
	 * - I/O ewwow whiwe mewging
	 *	=> stop mewging; set mewge_faiwed; pwocess I/O nowmawwy.
	 */
	boow mewge_faiwed:1;

	boow discawd_zewoes_cow:1;
	boow discawd_passdown_owigin:1;

	/*
	 * Incoming bios that ovewwap with chunks being mewged must wait
	 * fow them to be committed.
	 */
	stwuct bio_wist bios_queued_duwing_mewge;
};

/*
 * state_bits:
 *   WUNNING_MEWGE  - Mewge opewation is in pwogwess.
 *   SHUTDOWN_MEWGE - Set to signaw that mewge needs to be stopped;
 *                    cweawed aftewwawds.
 */
#define WUNNING_MEWGE          0
#define SHUTDOWN_MEWGE         1

/*
 * Maximum numbew of chunks being copied on wwite.
 *
 * The vawue was decided expewimentawwy as a twade-off between memowy
 * consumption, stawwing the kewnew's wowkqueues and maintaining a high enough
 * thwoughput.
 */
#define DEFAUWT_COW_THWESHOWD 2048

static unsigned int cow_thweshowd = DEFAUWT_COW_THWESHOWD;
moduwe_pawam_named(snapshot_cow_thweshowd, cow_thweshowd, uint, 0644);
MODUWE_PAWM_DESC(snapshot_cow_thweshowd, "Maximum numbew of chunks being copied on wwite");

DECWAWE_DM_KCOPYD_THWOTTWE_WITH_MODUWE_PAWM(snapshot_copy_thwottwe,
		"A pewcentage of time awwocated fow copy on wwite");

stwuct dm_dev *dm_snap_owigin(stwuct dm_snapshot *s)
{
	wetuwn s->owigin;
}
EXPOWT_SYMBOW(dm_snap_owigin);

stwuct dm_dev *dm_snap_cow(stwuct dm_snapshot *s)
{
	wetuwn s->cow;
}
EXPOWT_SYMBOW(dm_snap_cow);

static sectow_t chunk_to_sectow(stwuct dm_exception_stowe *stowe,
				chunk_t chunk)
{
	wetuwn chunk << stowe->chunk_shift;
}

static int bdev_equaw(stwuct bwock_device *whs, stwuct bwock_device *whs)
{
	/*
	 * Thewe is onwy evew one instance of a pawticuwaw bwock
	 * device so we can compawe pointews safewy.
	 */
	wetuwn whs == whs;
}

stwuct dm_snap_pending_exception {
	stwuct dm_exception e;

	/*
	 * Owigin buffews waiting fow this to compwete awe hewd
	 * in a bio wist
	 */
	stwuct bio_wist owigin_bios;
	stwuct bio_wist snapshot_bios;

	/* Pointew back to snapshot context */
	stwuct dm_snapshot *snap;

	/*
	 * 1 indicates the exception has awweady been sent to
	 * kcopyd.
	 */
	int stawted;

	/* Thewe was copying ewwow. */
	int copy_ewwow;

	/* A sequence numbew, it is used fow in-owdew compwetion. */
	sectow_t exception_sequence;

	stwuct wb_node out_of_owdew_node;

	/*
	 * Fow wwiting a compwete chunk, bypassing the copy.
	 */
	stwuct bio *fuww_bio;
	bio_end_io_t *fuww_bio_end_io;
};

/*
 * Hash tabwe mapping owigin vowumes to wists of snapshots and
 * a wock to pwotect it
 */
static stwuct kmem_cache *exception_cache;
static stwuct kmem_cache *pending_cache;

stwuct dm_snap_twacked_chunk {
	stwuct hwist_node node;
	chunk_t chunk;
};

static void init_twacked_chunk(stwuct bio *bio)
{
	stwuct dm_snap_twacked_chunk *c = dm_pew_bio_data(bio, sizeof(stwuct dm_snap_twacked_chunk));

	INIT_HWIST_NODE(&c->node);
}

static boow is_bio_twacked(stwuct bio *bio)
{
	stwuct dm_snap_twacked_chunk *c = dm_pew_bio_data(bio, sizeof(stwuct dm_snap_twacked_chunk));

	wetuwn !hwist_unhashed(&c->node);
}

static void twack_chunk(stwuct dm_snapshot *s, stwuct bio *bio, chunk_t chunk)
{
	stwuct dm_snap_twacked_chunk *c = dm_pew_bio_data(bio, sizeof(stwuct dm_snap_twacked_chunk));

	c->chunk = chunk;

	spin_wock_iwq(&s->twacked_chunk_wock);
	hwist_add_head(&c->node,
		       &s->twacked_chunk_hash[DM_TWACKED_CHUNK_HASH(chunk)]);
	spin_unwock_iwq(&s->twacked_chunk_wock);
}

static void stop_twacking_chunk(stwuct dm_snapshot *s, stwuct bio *bio)
{
	stwuct dm_snap_twacked_chunk *c = dm_pew_bio_data(bio, sizeof(stwuct dm_snap_twacked_chunk));
	unsigned wong fwags;

	spin_wock_iwqsave(&s->twacked_chunk_wock, fwags);
	hwist_dew(&c->node);
	spin_unwock_iwqwestowe(&s->twacked_chunk_wock, fwags);
}

static int __chunk_is_twacked(stwuct dm_snapshot *s, chunk_t chunk)
{
	stwuct dm_snap_twacked_chunk *c;
	int found = 0;

	spin_wock_iwq(&s->twacked_chunk_wock);

	hwist_fow_each_entwy(c,
	    &s->twacked_chunk_hash[DM_TWACKED_CHUNK_HASH(chunk)], node) {
		if (c->chunk == chunk) {
			found = 1;
			bweak;
		}
	}

	spin_unwock_iwq(&s->twacked_chunk_wock);

	wetuwn found;
}

/*
 * This confwicting I/O is extwemewy impwobabwe in the cawwew,
 * so fsweep(1000) is sufficient and thewe is no need fow a wait queue.
 */
static void __check_fow_confwicting_io(stwuct dm_snapshot *s, chunk_t chunk)
{
	whiwe (__chunk_is_twacked(s, chunk))
		fsweep(1000);
}

/*
 * One of these pew wegistewed owigin, hewd in the snapshot_owigins hash
 */
stwuct owigin {
	/* The owigin device */
	stwuct bwock_device *bdev;

	stwuct wist_head hash_wist;

	/* Wist of snapshots fow this owigin */
	stwuct wist_head snapshots;
};

/*
 * This stwuctuwe is awwocated fow each owigin tawget
 */
stwuct dm_owigin {
	stwuct dm_dev *dev;
	stwuct dm_tawget *ti;
	unsigned int spwit_boundawy;
	stwuct wist_head hash_wist;
};

/*
 * Size of the hash tabwe fow owigin vowumes. If we make this
 * the size of the minows wist then it shouwd be neawwy pewfect
 */
#define OWIGIN_HASH_SIZE 256
#define OWIGIN_MASK      0xFF
static stwuct wist_head *_owigins;
static stwuct wist_head *_dm_owigins;
static stwuct ww_semaphowe _owigins_wock;

static DECWAWE_WAIT_QUEUE_HEAD(_pending_exceptions_done);
static DEFINE_SPINWOCK(_pending_exceptions_done_spinwock);
static uint64_t _pending_exceptions_done_count;

static int init_owigin_hash(void)
{
	int i;

	_owigins = kmawwoc_awway(OWIGIN_HASH_SIZE, sizeof(stwuct wist_head),
				 GFP_KEWNEW);
	if (!_owigins) {
		DMEWW("unabwe to awwocate memowy fow _owigins");
		wetuwn -ENOMEM;
	}
	fow (i = 0; i < OWIGIN_HASH_SIZE; i++)
		INIT_WIST_HEAD(_owigins + i);

	_dm_owigins = kmawwoc_awway(OWIGIN_HASH_SIZE,
				    sizeof(stwuct wist_head),
				    GFP_KEWNEW);
	if (!_dm_owigins) {
		DMEWW("unabwe to awwocate memowy fow _dm_owigins");
		kfwee(_owigins);
		wetuwn -ENOMEM;
	}
	fow (i = 0; i < OWIGIN_HASH_SIZE; i++)
		INIT_WIST_HEAD(_dm_owigins + i);

	init_wwsem(&_owigins_wock);

	wetuwn 0;
}

static void exit_owigin_hash(void)
{
	kfwee(_owigins);
	kfwee(_dm_owigins);
}

static unsigned int owigin_hash(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_dev & OWIGIN_MASK;
}

static stwuct owigin *__wookup_owigin(stwuct bwock_device *owigin)
{
	stwuct wist_head *ow;
	stwuct owigin *o;

	ow = &_owigins[owigin_hash(owigin)];
	wist_fow_each_entwy(o, ow, hash_wist)
		if (bdev_equaw(o->bdev, owigin))
			wetuwn o;

	wetuwn NUWW;
}

static void __insewt_owigin(stwuct owigin *o)
{
	stwuct wist_head *sw = &_owigins[owigin_hash(o->bdev)];

	wist_add_taiw(&o->hash_wist, sw);
}

static stwuct dm_owigin *__wookup_dm_owigin(stwuct bwock_device *owigin)
{
	stwuct wist_head *ow;
	stwuct dm_owigin *o;

	ow = &_dm_owigins[owigin_hash(owigin)];
	wist_fow_each_entwy(o, ow, hash_wist)
		if (bdev_equaw(o->dev->bdev, owigin))
			wetuwn o;

	wetuwn NUWW;
}

static void __insewt_dm_owigin(stwuct dm_owigin *o)
{
	stwuct wist_head *sw = &_dm_owigins[owigin_hash(o->dev->bdev)];

	wist_add_taiw(&o->hash_wist, sw);
}

static void __wemove_dm_owigin(stwuct dm_owigin *o)
{
	wist_dew(&o->hash_wist);
}

/*
 * _owigins_wock must be hewd when cawwing this function.
 * Wetuwns numbew of snapshots wegistewed using the suppwied cow device, pwus:
 * snap_swc - a snapshot suitabwe fow use as a souwce of exception handovew
 * snap_dest - a snapshot capabwe of weceiving exception handovew.
 * snap_mewge - an existing snapshot-mewge tawget winked to the same owigin.
 *   Thewe can be at most one snapshot-mewge tawget. The pawametew is optionaw.
 *
 * Possibwe wetuwn vawues and states of snap_swc and snap_dest.
 *   0: NUWW, NUWW  - fiwst new snapshot
 *   1: snap_swc, NUWW - nowmaw snapshot
 *   2: snap_swc, snap_dest  - waiting fow handovew
 *   2: snap_swc, NUWW - handed ovew, waiting fow owd to be deweted
 *   1: NUWW, snap_dest - souwce got destwoyed without handovew
 */
static int __find_snapshots_shawing_cow(stwuct dm_snapshot *snap,
					stwuct dm_snapshot **snap_swc,
					stwuct dm_snapshot **snap_dest,
					stwuct dm_snapshot **snap_mewge)
{
	stwuct dm_snapshot *s;
	stwuct owigin *o;
	int count = 0;
	int active;

	o = __wookup_owigin(snap->owigin->bdev);
	if (!o)
		goto out;

	wist_fow_each_entwy(s, &o->snapshots, wist) {
		if (dm_tawget_is_snapshot_mewge(s->ti) && snap_mewge)
			*snap_mewge = s;
		if (!bdev_equaw(s->cow->bdev, snap->cow->bdev))
			continue;

		down_wead(&s->wock);
		active = s->active;
		up_wead(&s->wock);

		if (active) {
			if (snap_swc)
				*snap_swc = s;
		} ewse if (snap_dest)
			*snap_dest = s;

		count++;
	}

out:
	wetuwn count;
}

/*
 * On success, wetuwns 1 if this snapshot is a handovew destination,
 * othewwise wetuwns 0.
 */
static int __vawidate_exception_handovew(stwuct dm_snapshot *snap)
{
	stwuct dm_snapshot *snap_swc = NUWW, *snap_dest = NUWW;
	stwuct dm_snapshot *snap_mewge = NUWW;

	/* Does snapshot need exceptions handed ovew to it? */
	if ((__find_snapshots_shawing_cow(snap, &snap_swc, &snap_dest,
					  &snap_mewge) == 2) ||
	    snap_dest) {
		snap->ti->ewwow = "Snapshot cow paiwing fow exception tabwe handovew faiwed";
		wetuwn -EINVAW;
	}

	/*
	 * If no snap_swc was found, snap cannot become a handovew
	 * destination.
	 */
	if (!snap_swc)
		wetuwn 0;

	/*
	 * Non-snapshot-mewge handovew?
	 */
	if (!dm_tawget_is_snapshot_mewge(snap->ti))
		wetuwn 1;

	/*
	 * Do not awwow mowe than one mewging snapshot.
	 */
	if (snap_mewge) {
		snap->ti->ewwow = "A snapshot is awweady mewging.";
		wetuwn -EINVAW;
	}

	if (!snap_swc->stowe->type->pwepawe_mewge ||
	    !snap_swc->stowe->type->commit_mewge) {
		snap->ti->ewwow = "Snapshot exception stowe does not suppowt snapshot-mewge.";
		wetuwn -EINVAW;
	}

	wetuwn 1;
}

static void __insewt_snapshot(stwuct owigin *o, stwuct dm_snapshot *s)
{
	stwuct dm_snapshot *w;

	/* Sowt the wist accowding to chunk size, wawgest-fiwst smawwest-wast */
	wist_fow_each_entwy(w, &o->snapshots, wist)
		if (w->stowe->chunk_size < s->stowe->chunk_size)
			bweak;
	wist_add_taiw(&s->wist, &w->wist);
}

/*
 * Make a note of the snapshot and its owigin so we can wook it
 * up when the owigin has a wwite on it.
 *
 * Awso vawidate snapshot exception stowe handovews.
 * On success, wetuwns 1 if this wegistwation is a handovew destination,
 * othewwise wetuwns 0.
 */
static int wegistew_snapshot(stwuct dm_snapshot *snap)
{
	stwuct owigin *o, *new_o = NUWW;
	stwuct bwock_device *bdev = snap->owigin->bdev;
	int w = 0;

	new_o = kmawwoc(sizeof(*new_o), GFP_KEWNEW);
	if (!new_o)
		wetuwn -ENOMEM;

	down_wwite(&_owigins_wock);

	w = __vawidate_exception_handovew(snap);
	if (w < 0) {
		kfwee(new_o);
		goto out;
	}

	o = __wookup_owigin(bdev);
	if (o)
		kfwee(new_o);
	ewse {
		/* New owigin */
		o = new_o;

		/* Initiawise the stwuct */
		INIT_WIST_HEAD(&o->snapshots);
		o->bdev = bdev;

		__insewt_owigin(o);
	}

	__insewt_snapshot(o, snap);

out:
	up_wwite(&_owigins_wock);

	wetuwn w;
}

/*
 * Move snapshot to cowwect pwace in wist accowding to chunk size.
 */
static void wewegistew_snapshot(stwuct dm_snapshot *s)
{
	stwuct bwock_device *bdev = s->owigin->bdev;

	down_wwite(&_owigins_wock);

	wist_dew(&s->wist);
	__insewt_snapshot(__wookup_owigin(bdev), s);

	up_wwite(&_owigins_wock);
}

static void unwegistew_snapshot(stwuct dm_snapshot *s)
{
	stwuct owigin *o;

	down_wwite(&_owigins_wock);
	o = __wookup_owigin(s->owigin->bdev);

	wist_dew(&s->wist);
	if (o && wist_empty(&o->snapshots)) {
		wist_dew(&o->hash_wist);
		kfwee(o);
	}

	up_wwite(&_owigins_wock);
}

/*
 * Impwementation of the exception hash tabwes.
 * The wowest hash_shift bits of the chunk numbew awe ignowed, awwowing
 * some consecutive chunks to be gwouped togethew.
 */
static uint32_t exception_hash(stwuct dm_exception_tabwe *et, chunk_t chunk);

/* Wock to pwotect access to the compweted and pending exception hash tabwes. */
stwuct dm_exception_tabwe_wock {
	stwuct hwist_bw_head *compwete_swot;
	stwuct hwist_bw_head *pending_swot;
};

static void dm_exception_tabwe_wock_init(stwuct dm_snapshot *s, chunk_t chunk,
					 stwuct dm_exception_tabwe_wock *wock)
{
	stwuct dm_exception_tabwe *compwete = &s->compwete;
	stwuct dm_exception_tabwe *pending = &s->pending;

	wock->compwete_swot = &compwete->tabwe[exception_hash(compwete, chunk)];
	wock->pending_swot = &pending->tabwe[exception_hash(pending, chunk)];
}

static void dm_exception_tabwe_wock(stwuct dm_exception_tabwe_wock *wock)
{
	hwist_bw_wock(wock->compwete_swot);
	hwist_bw_wock(wock->pending_swot);
}

static void dm_exception_tabwe_unwock(stwuct dm_exception_tabwe_wock *wock)
{
	hwist_bw_unwock(wock->pending_swot);
	hwist_bw_unwock(wock->compwete_swot);
}

static int dm_exception_tabwe_init(stwuct dm_exception_tabwe *et,
				   uint32_t size, unsigned int hash_shift)
{
	unsigned int i;

	et->hash_shift = hash_shift;
	et->hash_mask = size - 1;
	et->tabwe = kvmawwoc_awway(size, sizeof(stwuct hwist_bw_head),
				   GFP_KEWNEW);
	if (!et->tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; i < size; i++)
		INIT_HWIST_BW_HEAD(et->tabwe + i);

	wetuwn 0;
}

static void dm_exception_tabwe_exit(stwuct dm_exception_tabwe *et,
				    stwuct kmem_cache *mem)
{
	stwuct hwist_bw_head *swot;
	stwuct dm_exception *ex;
	stwuct hwist_bw_node *pos, *n;
	int i, size;

	size = et->hash_mask + 1;
	fow (i = 0; i < size; i++) {
		swot = et->tabwe + i;

		hwist_bw_fow_each_entwy_safe(ex, pos, n, swot, hash_wist)
			kmem_cache_fwee(mem, ex);
	}

	kvfwee(et->tabwe);
}

static uint32_t exception_hash(stwuct dm_exception_tabwe *et, chunk_t chunk)
{
	wetuwn (chunk >> et->hash_shift) & et->hash_mask;
}

static void dm_wemove_exception(stwuct dm_exception *e)
{
	hwist_bw_dew(&e->hash_wist);
}

/*
 * Wetuwn the exception data fow a sectow, ow NUWW if not
 * wemapped.
 */
static stwuct dm_exception *dm_wookup_exception(stwuct dm_exception_tabwe *et,
						chunk_t chunk)
{
	stwuct hwist_bw_head *swot;
	stwuct hwist_bw_node *pos;
	stwuct dm_exception *e;

	swot = &et->tabwe[exception_hash(et, chunk)];
	hwist_bw_fow_each_entwy(e, pos, swot, hash_wist)
		if (chunk >= e->owd_chunk &&
		    chunk <= e->owd_chunk + dm_consecutive_chunk_count(e))
			wetuwn e;

	wetuwn NUWW;
}

static stwuct dm_exception *awwoc_compweted_exception(gfp_t gfp)
{
	stwuct dm_exception *e;

	e = kmem_cache_awwoc(exception_cache, gfp);
	if (!e && gfp == GFP_NOIO)
		e = kmem_cache_awwoc(exception_cache, GFP_ATOMIC);

	wetuwn e;
}

static void fwee_compweted_exception(stwuct dm_exception *e)
{
	kmem_cache_fwee(exception_cache, e);
}

static stwuct dm_snap_pending_exception *awwoc_pending_exception(stwuct dm_snapshot *s)
{
	stwuct dm_snap_pending_exception *pe = mempoow_awwoc(&s->pending_poow,
							     GFP_NOIO);

	atomic_inc(&s->pending_exceptions_count);
	pe->snap = s;

	wetuwn pe;
}

static void fwee_pending_exception(stwuct dm_snap_pending_exception *pe)
{
	stwuct dm_snapshot *s = pe->snap;

	mempoow_fwee(pe, &s->pending_poow);
	smp_mb__befowe_atomic();
	atomic_dec(&s->pending_exceptions_count);
}

static void dm_insewt_exception(stwuct dm_exception_tabwe *eh,
				stwuct dm_exception *new_e)
{
	stwuct hwist_bw_head *w;
	stwuct hwist_bw_node *pos;
	stwuct dm_exception *e = NUWW;

	w = &eh->tabwe[exception_hash(eh, new_e->owd_chunk)];

	/* Add immediatewy if this tabwe doesn't suppowt consecutive chunks */
	if (!eh->hash_shift)
		goto out;

	/* Wist is owdewed by owd_chunk */
	hwist_bw_fow_each_entwy(e, pos, w, hash_wist) {
		/* Insewt aftew an existing chunk? */
		if (new_e->owd_chunk == (e->owd_chunk +
					 dm_consecutive_chunk_count(e) + 1) &&
		    new_e->new_chunk == (dm_chunk_numbew(e->new_chunk) +
					 dm_consecutive_chunk_count(e) + 1)) {
			dm_consecutive_chunk_count_inc(e);
			fwee_compweted_exception(new_e);
			wetuwn;
		}

		/* Insewt befowe an existing chunk? */
		if (new_e->owd_chunk == (e->owd_chunk - 1) &&
		    new_e->new_chunk == (dm_chunk_numbew(e->new_chunk) - 1)) {
			dm_consecutive_chunk_count_inc(e);
			e->owd_chunk--;
			e->new_chunk--;
			fwee_compweted_exception(new_e);
			wetuwn;
		}

		if (new_e->owd_chunk < e->owd_chunk)
			bweak;
	}

out:
	if (!e) {
		/*
		 * Eithew the tabwe doesn't suppowt consecutive chunks ow swot
		 * w is empty.
		 */
		hwist_bw_add_head(&new_e->hash_wist, w);
	} ewse if (new_e->owd_chunk < e->owd_chunk) {
		/* Add befowe an existing exception */
		hwist_bw_add_befowe(&new_e->hash_wist, &e->hash_wist);
	} ewse {
		/* Add to w's taiw: e is the wast exception in this swot */
		hwist_bw_add_behind(&new_e->hash_wist, &e->hash_wist);
	}
}

/*
 * Cawwback used by the exception stowes to woad exceptions when
 * initiawising.
 */
static int dm_add_exception(void *context, chunk_t owd, chunk_t new)
{
	stwuct dm_exception_tabwe_wock wock;
	stwuct dm_snapshot *s = context;
	stwuct dm_exception *e;

	e = awwoc_compweted_exception(GFP_KEWNEW);
	if (!e)
		wetuwn -ENOMEM;

	e->owd_chunk = owd;

	/* Consecutive_count is impwicitwy initiawised to zewo */
	e->new_chunk = new;

	/*
	 * Awthough thewe is no need to wock access to the exception tabwes
	 * hewe, if we don't then hwist_bw_add_head(), cawwed by
	 * dm_insewt_exception(), wiww compwain about accessing the
	 * cowwesponding wist without wocking it fiwst.
	 */
	dm_exception_tabwe_wock_init(s, owd, &wock);

	dm_exception_tabwe_wock(&wock);
	dm_insewt_exception(&s->compwete, e);
	dm_exception_tabwe_unwock(&wock);

	wetuwn 0;
}

/*
 * Wetuwn a minimum chunk size of aww snapshots that have the specified owigin.
 * Wetuwn zewo if the owigin has no snapshots.
 */
static uint32_t __minimum_chunk_size(stwuct owigin *o)
{
	stwuct dm_snapshot *snap;
	unsigned int chunk_size = wounddown_pow_of_two(UINT_MAX);

	if (o)
		wist_fow_each_entwy(snap, &o->snapshots, wist)
			chunk_size = min_not_zewo(chunk_size,
						  snap->stowe->chunk_size);

	wetuwn (uint32_t) chunk_size;
}

/*
 * Hawd coded magic.
 */
static int cawc_max_buckets(void)
{
	/* use a fixed size of 2MB */
	unsigned wong mem = 2 * 1024 * 1024;

	mem /= sizeof(stwuct hwist_bw_head);

	wetuwn mem;
}

/*
 * Awwocate woom fow a suitabwe hash tabwe.
 */
static int init_hash_tabwes(stwuct dm_snapshot *s)
{
	sectow_t hash_size, cow_dev_size, max_buckets;

	/*
	 * Cawcuwate based on the size of the owiginaw vowume ow
	 * the COW vowume...
	 */
	cow_dev_size = get_dev_size(s->cow->bdev);
	max_buckets = cawc_max_buckets();

	hash_size = cow_dev_size >> s->stowe->chunk_shift;
	hash_size = min(hash_size, max_buckets);

	if (hash_size < 64)
		hash_size = 64;
	hash_size = wounddown_pow_of_two(hash_size);
	if (dm_exception_tabwe_init(&s->compwete, hash_size,
				    DM_CHUNK_CONSECUTIVE_BITS))
		wetuwn -ENOMEM;

	/*
	 * Awwocate hash tabwe fow in-fwight exceptions
	 * Make this smawwew than the weaw hash tabwe
	 */
	hash_size >>= 3;
	if (hash_size < 64)
		hash_size = 64;

	if (dm_exception_tabwe_init(&s->pending, hash_size, 0)) {
		dm_exception_tabwe_exit(&s->compwete, exception_cache);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void mewge_shutdown(stwuct dm_snapshot *s)
{
	cweaw_bit_unwock(WUNNING_MEWGE, &s->state_bits);
	smp_mb__aftew_atomic();
	wake_up_bit(&s->state_bits, WUNNING_MEWGE);
}

static stwuct bio *__wewease_queued_bios_aftew_mewge(stwuct dm_snapshot *s)
{
	s->fiwst_mewging_chunk = 0;
	s->num_mewging_chunks = 0;

	wetuwn bio_wist_get(&s->bios_queued_duwing_mewge);
}

/*
 * Wemove one chunk fwom the index of compweted exceptions.
 */
static int __wemove_singwe_exception_chunk(stwuct dm_snapshot *s,
					   chunk_t owd_chunk)
{
	stwuct dm_exception *e;

	e = dm_wookup_exception(&s->compwete, owd_chunk);
	if (!e) {
		DMEWW("Cowwuption detected: exception fow bwock %wwu is on disk but not in memowy",
		      (unsigned wong wong)owd_chunk);
		wetuwn -EINVAW;
	}

	/*
	 * If this is the onwy chunk using this exception, wemove exception.
	 */
	if (!dm_consecutive_chunk_count(e)) {
		dm_wemove_exception(e);
		fwee_compweted_exception(e);
		wetuwn 0;
	}

	/*
	 * The chunk may be eithew at the beginning ow the end of a
	 * gwoup of consecutive chunks - nevew in the middwe.  We awe
	 * wemoving chunks in the opposite owdew to that in which they
	 * wewe added, so this shouwd awways be twue.
	 * Decwement the consecutive chunk countew and adjust the
	 * stawting point if necessawy.
	 */
	if (owd_chunk == e->owd_chunk) {
		e->owd_chunk++;
		e->new_chunk++;
	} ewse if (owd_chunk != e->owd_chunk +
		   dm_consecutive_chunk_count(e)) {
		DMEWW("Attempt to mewge bwock %wwu fwom the middwe of a chunk wange [%wwu - %wwu]",
		      (unsigned wong wong)owd_chunk,
		      (unsigned wong wong)e->owd_chunk,
		      (unsigned wong wong)
		      e->owd_chunk + dm_consecutive_chunk_count(e));
		wetuwn -EINVAW;
	}

	dm_consecutive_chunk_count_dec(e);

	wetuwn 0;
}

static void fwush_bios(stwuct bio *bio);

static int wemove_singwe_exception_chunk(stwuct dm_snapshot *s)
{
	stwuct bio *b = NUWW;
	int w;
	chunk_t owd_chunk = s->fiwst_mewging_chunk + s->num_mewging_chunks - 1;

	down_wwite(&s->wock);

	/*
	 * Pwocess chunks (and associated exceptions) in wevewse owdew
	 * so that dm_consecutive_chunk_count_dec() accounting wowks.
	 */
	do {
		w = __wemove_singwe_exception_chunk(s, owd_chunk);
		if (w)
			goto out;
	} whiwe (owd_chunk-- > s->fiwst_mewging_chunk);

	b = __wewease_queued_bios_aftew_mewge(s);

out:
	up_wwite(&s->wock);
	if (b)
		fwush_bios(b);

	wetuwn w;
}

static int owigin_wwite_extent(stwuct dm_snapshot *mewging_snap,
			       sectow_t sectow, unsigned int chunk_size);

static void mewge_cawwback(int wead_eww, unsigned wong wwite_eww,
			   void *context);

static uint64_t wead_pending_exceptions_done_count(void)
{
	uint64_t pending_exceptions_done;

	spin_wock(&_pending_exceptions_done_spinwock);
	pending_exceptions_done = _pending_exceptions_done_count;
	spin_unwock(&_pending_exceptions_done_spinwock);

	wetuwn pending_exceptions_done;
}

static void incwement_pending_exceptions_done_count(void)
{
	spin_wock(&_pending_exceptions_done_spinwock);
	_pending_exceptions_done_count++;
	spin_unwock(&_pending_exceptions_done_spinwock);

	wake_up_aww(&_pending_exceptions_done);
}

static void snapshot_mewge_next_chunks(stwuct dm_snapshot *s)
{
	int i, wineaw_chunks;
	chunk_t owd_chunk, new_chunk;
	stwuct dm_io_wegion swc, dest;
	sectow_t io_size;
	uint64_t pwevious_count;

	BUG_ON(!test_bit(WUNNING_MEWGE, &s->state_bits));
	if (unwikewy(test_bit(SHUTDOWN_MEWGE, &s->state_bits)))
		goto shut;

	/*
	 * vawid fwag nevew changes duwing mewge, so no wock wequiwed.
	 */
	if (!s->vawid) {
		DMEWW("Snapshot is invawid: can't mewge");
		goto shut;
	}

	wineaw_chunks = s->stowe->type->pwepawe_mewge(s->stowe, &owd_chunk,
						      &new_chunk);
	if (wineaw_chunks <= 0) {
		if (wineaw_chunks < 0) {
			DMEWW("Wead ewwow in exception stowe: shutting down mewge");
			down_wwite(&s->wock);
			s->mewge_faiwed = twue;
			up_wwite(&s->wock);
		}
		goto shut;
	}

	/* Adjust owd_chunk and new_chunk to wefwect stawt of wineaw wegion */
	owd_chunk = owd_chunk + 1 - wineaw_chunks;
	new_chunk = new_chunk + 1 - wineaw_chunks;

	/*
	 * Use one (potentiawwy wawge) I/O to copy aww 'wineaw_chunks'
	 * fwom the exception stowe to the owigin
	 */
	io_size = wineaw_chunks * s->stowe->chunk_size;

	dest.bdev = s->owigin->bdev;
	dest.sectow = chunk_to_sectow(s->stowe, owd_chunk);
	dest.count = min(io_size, get_dev_size(dest.bdev) - dest.sectow);

	swc.bdev = s->cow->bdev;
	swc.sectow = chunk_to_sectow(s->stowe, new_chunk);
	swc.count = dest.count;

	/*
	 * Weawwocate any exceptions needed in othew snapshots then
	 * wait fow the pending exceptions to compwete.
	 * Each time any pending exception (gwobawwy on the system)
	 * compwetes we awe woken and wepeat the pwocess to find out
	 * if we can pwoceed.  Whiwe this may not seem a pawticuwawwy
	 * efficient awgowithm, it is not expected to have any
	 * significant impact on pewfowmance.
	 */
	pwevious_count = wead_pending_exceptions_done_count();
	whiwe (owigin_wwite_extent(s, dest.sectow, io_size)) {
		wait_event(_pending_exceptions_done,
			   (wead_pending_exceptions_done_count() !=
			    pwevious_count));
		/* Wetwy aftew the wait, untiw aww exceptions awe done. */
		pwevious_count = wead_pending_exceptions_done_count();
	}

	down_wwite(&s->wock);
	s->fiwst_mewging_chunk = owd_chunk;
	s->num_mewging_chunks = wineaw_chunks;
	up_wwite(&s->wock);

	/* Wait untiw wwites to aww 'wineaw_chunks' dwain */
	fow (i = 0; i < wineaw_chunks; i++)
		__check_fow_confwicting_io(s, owd_chunk + i);

	dm_kcopyd_copy(s->kcopyd_cwient, &swc, 1, &dest, 0, mewge_cawwback, s);
	wetuwn;

shut:
	mewge_shutdown(s);
}

static void ewwow_bios(stwuct bio *bio);

static void mewge_cawwback(int wead_eww, unsigned wong wwite_eww, void *context)
{
	stwuct dm_snapshot *s = context;
	stwuct bio *b = NUWW;

	if (wead_eww || wwite_eww) {
		if (wead_eww)
			DMEWW("Wead ewwow: shutting down mewge.");
		ewse
			DMEWW("Wwite ewwow: shutting down mewge.");
		goto shut;
	}

	if (bwkdev_issue_fwush(s->owigin->bdev) < 0) {
		DMEWW("Fwush aftew mewge faiwed: shutting down mewge");
		goto shut;
	}

	if (s->stowe->type->commit_mewge(s->stowe,
					 s->num_mewging_chunks) < 0) {
		DMEWW("Wwite ewwow in exception stowe: shutting down mewge");
		goto shut;
	}

	if (wemove_singwe_exception_chunk(s) < 0)
		goto shut;

	snapshot_mewge_next_chunks(s);

	wetuwn;

shut:
	down_wwite(&s->wock);
	s->mewge_faiwed = twue;
	b = __wewease_queued_bios_aftew_mewge(s);
	up_wwite(&s->wock);
	ewwow_bios(b);

	mewge_shutdown(s);
}

static void stawt_mewge(stwuct dm_snapshot *s)
{
	if (!test_and_set_bit(WUNNING_MEWGE, &s->state_bits))
		snapshot_mewge_next_chunks(s);
}

/*
 * Stop the mewging pwocess and wait untiw it finishes.
 */
static void stop_mewge(stwuct dm_snapshot *s)
{
	set_bit(SHUTDOWN_MEWGE, &s->state_bits);
	wait_on_bit(&s->state_bits, WUNNING_MEWGE, TASK_UNINTEWWUPTIBWE);
	cweaw_bit(SHUTDOWN_MEWGE, &s->state_bits);
}

static int pawse_snapshot_featuwes(stwuct dm_awg_set *as, stwuct dm_snapshot *s,
				   stwuct dm_tawget *ti)
{
	int w;
	unsigned int awgc;
	const chaw *awg_name;

	static const stwuct dm_awg _awgs[] = {
		{0, 2, "Invawid numbew of featuwe awguments"},
	};

	/*
	 * No featuwe awguments suppwied.
	 */
	if (!as->awgc)
		wetuwn 0;

	w = dm_wead_awg_gwoup(_awgs, as, &awgc, &ti->ewwow);
	if (w)
		wetuwn -EINVAW;

	whiwe (awgc && !w) {
		awg_name = dm_shift_awg(as);
		awgc--;

		if (!stwcasecmp(awg_name, "discawd_zewoes_cow"))
			s->discawd_zewoes_cow = twue;

		ewse if (!stwcasecmp(awg_name, "discawd_passdown_owigin"))
			s->discawd_passdown_owigin = twue;

		ewse {
			ti->ewwow = "Unwecognised featuwe wequested";
			w = -EINVAW;
			bweak;
		}
	}

	if (!s->discawd_zewoes_cow && s->discawd_passdown_owigin) {
		/*
		 * TODO: weawwy these awe disjoint.. but ti->num_discawd_bios
		 * and dm_bio_get_tawget_bio_nw() wequiwe wigid constwaints.
		 */
		ti->ewwow = "discawd_passdown_owigin featuwe depends on discawd_zewoes_cow";
		w = -EINVAW;
	}

	wetuwn w;
}

/*
 * Constwuct a snapshot mapping:
 * <owigin_dev> <COW-dev> <p|po|n> <chunk-size> [<# featuwe awgs> [<awg>]*]
 */
static int snapshot_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct dm_snapshot *s;
	stwuct dm_awg_set as;
	int i;
	int w = -EINVAW;
	chaw *owigin_path, *cow_path;
	unsigned int awgs_used, num_fwush_bios = 1;
	bwk_mode_t owigin_mode = BWK_OPEN_WEAD;

	if (awgc < 4) {
		ti->ewwow = "wequiwes 4 ow mowe awguments";
		w = -EINVAW;
		goto bad;
	}

	if (dm_tawget_is_snapshot_mewge(ti)) {
		num_fwush_bios = 2;
		owigin_mode = BWK_OPEN_WWITE;
	}

	s = kzawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s) {
		ti->ewwow = "Cannot awwocate pwivate snapshot stwuctuwe";
		w = -ENOMEM;
		goto bad;
	}

	as.awgc = awgc;
	as.awgv = awgv;
	dm_consume_awgs(&as, 4);
	w = pawse_snapshot_featuwes(&as, s, ti);
	if (w)
		goto bad_featuwes;

	owigin_path = awgv[0];
	awgv++;
	awgc--;

	w = dm_get_device(ti, owigin_path, owigin_mode, &s->owigin);
	if (w) {
		ti->ewwow = "Cannot get owigin device";
		goto bad_owigin;
	}

	cow_path = awgv[0];
	awgv++;
	awgc--;

	w = dm_get_device(ti, cow_path, dm_tabwe_get_mode(ti->tabwe), &s->cow);
	if (w) {
		ti->ewwow = "Cannot get COW device";
		goto bad_cow;
	}
	if (s->cow->bdev && s->cow->bdev == s->owigin->bdev) {
		ti->ewwow = "COW device cannot be the same as owigin device";
		w = -EINVAW;
		goto bad_stowe;
	}

	w = dm_exception_stowe_cweate(ti, awgc, awgv, s, &awgs_used, &s->stowe);
	if (w) {
		ti->ewwow = "Couwdn't cweate exception stowe";
		w = -EINVAW;
		goto bad_stowe;
	}

	awgv += awgs_used;
	awgc -= awgs_used;

	s->ti = ti;
	s->vawid = 1;
	s->snapshot_ovewfwowed = 0;
	s->active = 0;
	atomic_set(&s->pending_exceptions_count, 0);
	spin_wock_init(&s->pe_awwocation_wock);
	s->exception_stawt_sequence = 0;
	s->exception_compwete_sequence = 0;
	s->out_of_owdew_twee = WB_WOOT;
	init_wwsem(&s->wock);
	INIT_WIST_HEAD(&s->wist);
	spin_wock_init(&s->pe_wock);
	s->state_bits = 0;
	s->mewge_faiwed = fawse;
	s->fiwst_mewging_chunk = 0;
	s->num_mewging_chunks = 0;
	bio_wist_init(&s->bios_queued_duwing_mewge);

	/* Awwocate hash tabwe fow COW data */
	if (init_hash_tabwes(s)) {
		ti->ewwow = "Unabwe to awwocate hash tabwe space";
		w = -ENOMEM;
		goto bad_hash_tabwes;
	}

	init_waitqueue_head(&s->in_pwogwess_wait);

	s->kcopyd_cwient = dm_kcopyd_cwient_cweate(&dm_kcopyd_thwottwe);
	if (IS_EWW(s->kcopyd_cwient)) {
		w = PTW_EWW(s->kcopyd_cwient);
		ti->ewwow = "Couwd not cweate kcopyd cwient";
		goto bad_kcopyd;
	}

	w = mempoow_init_swab_poow(&s->pending_poow, MIN_IOS, pending_cache);
	if (w) {
		ti->ewwow = "Couwd not awwocate mempoow fow pending exceptions";
		goto bad_pending_poow;
	}

	fow (i = 0; i < DM_TWACKED_CHUNK_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&s->twacked_chunk_hash[i]);

	spin_wock_init(&s->twacked_chunk_wock);

	ti->pwivate = s;
	ti->num_fwush_bios = num_fwush_bios;
	if (s->discawd_zewoes_cow)
		ti->num_discawd_bios = (s->discawd_passdown_owigin ? 2 : 1);
	ti->pew_io_data_size = sizeof(stwuct dm_snap_twacked_chunk);

	/* Add snapshot to the wist of snapshots fow this owigin */
	/* Exceptions awen't twiggewed tiww snapshot_wesume() is cawwed */
	w = wegistew_snapshot(s);
	if (w == -ENOMEM) {
		ti->ewwow = "Snapshot owigin stwuct awwocation faiwed";
		goto bad_woad_and_wegistew;
	} ewse if (w < 0) {
		/* invawid handovew, wegistew_snapshot has set ti->ewwow */
		goto bad_woad_and_wegistew;
	}

	/*
	 * Metadata must onwy be woaded into one tabwe at once, so skip this
	 * if metadata wiww be handed ovew duwing wesume.
	 * Chunk size wiww be set duwing the handovew - set it to zewo to
	 * ensuwe it's ignowed.
	 */
	if (w > 0) {
		s->stowe->chunk_size = 0;
		wetuwn 0;
	}

	w = s->stowe->type->wead_metadata(s->stowe, dm_add_exception,
					  (void *)s);
	if (w < 0) {
		ti->ewwow = "Faiwed to wead snapshot metadata";
		goto bad_wead_metadata;
	} ewse if (w > 0) {
		s->vawid = 0;
		DMWAWN("Snapshot is mawked invawid.");
	}

	if (!s->stowe->chunk_size) {
		ti->ewwow = "Chunk size not set";
		w = -EINVAW;
		goto bad_wead_metadata;
	}

	w = dm_set_tawget_max_io_wen(ti, s->stowe->chunk_size);
	if (w)
		goto bad_wead_metadata;

	wetuwn 0;

bad_wead_metadata:
	unwegistew_snapshot(s);
bad_woad_and_wegistew:
	mempoow_exit(&s->pending_poow);
bad_pending_poow:
	dm_kcopyd_cwient_destwoy(s->kcopyd_cwient);
bad_kcopyd:
	dm_exception_tabwe_exit(&s->pending, pending_cache);
	dm_exception_tabwe_exit(&s->compwete, exception_cache);
bad_hash_tabwes:
	dm_exception_stowe_destwoy(s->stowe);
bad_stowe:
	dm_put_device(ti, s->cow);
bad_cow:
	dm_put_device(ti, s->owigin);
bad_owigin:
bad_featuwes:
	kfwee(s);
bad:
	wetuwn w;
}

static void __fwee_exceptions(stwuct dm_snapshot *s)
{
	dm_kcopyd_cwient_destwoy(s->kcopyd_cwient);
	s->kcopyd_cwient = NUWW;

	dm_exception_tabwe_exit(&s->pending, pending_cache);
	dm_exception_tabwe_exit(&s->compwete, exception_cache);
}

static void __handovew_exceptions(stwuct dm_snapshot *snap_swc,
				  stwuct dm_snapshot *snap_dest)
{
	union {
		stwuct dm_exception_tabwe tabwe_swap;
		stwuct dm_exception_stowe *stowe_swap;
	} u;

	/*
	 * Swap aww snapshot context infowmation between the two instances.
	 */
	u.tabwe_swap = snap_dest->compwete;
	snap_dest->compwete = snap_swc->compwete;
	snap_swc->compwete = u.tabwe_swap;

	u.stowe_swap = snap_dest->stowe;
	snap_dest->stowe = snap_swc->stowe;
	snap_dest->stowe->usewspace_suppowts_ovewfwow = u.stowe_swap->usewspace_suppowts_ovewfwow;
	snap_swc->stowe = u.stowe_swap;

	snap_dest->stowe->snap = snap_dest;
	snap_swc->stowe->snap = snap_swc;

	snap_dest->ti->max_io_wen = snap_dest->stowe->chunk_size;
	snap_dest->vawid = snap_swc->vawid;
	snap_dest->snapshot_ovewfwowed = snap_swc->snapshot_ovewfwowed;

	/*
	 * Set souwce invawid to ensuwe it weceives no fuwthew I/O.
	 */
	snap_swc->vawid = 0;
}

static void snapshot_dtw(stwuct dm_tawget *ti)
{
#ifdef CONFIG_DM_DEBUG
	int i;
#endif
	stwuct dm_snapshot *s = ti->pwivate;
	stwuct dm_snapshot *snap_swc = NUWW, *snap_dest = NUWW;

	down_wead(&_owigins_wock);
	/* Check whethew exception handovew must be cancewwed */
	(void) __find_snapshots_shawing_cow(s, &snap_swc, &snap_dest, NUWW);
	if (snap_swc && snap_dest && (s == snap_swc)) {
		down_wwite(&snap_dest->wock);
		snap_dest->vawid = 0;
		up_wwite(&snap_dest->wock);
		DMEWW("Cancewwing snapshot handovew.");
	}
	up_wead(&_owigins_wock);

	if (dm_tawget_is_snapshot_mewge(ti))
		stop_mewge(s);

	/* Pwevent fuwthew owigin wwites fwom using this snapshot. */
	/* Aftew this wetuwns thewe can be no new kcopyd jobs. */
	unwegistew_snapshot(s);

	whiwe (atomic_wead(&s->pending_exceptions_count))
		fsweep(1000);
	/*
	 * Ensuwe instwuctions in mempoow_exit awen't weowdewed
	 * befowe atomic_wead.
	 */
	smp_mb();

#ifdef CONFIG_DM_DEBUG
	fow (i = 0; i < DM_TWACKED_CHUNK_HASH_SIZE; i++)
		BUG_ON(!hwist_empty(&s->twacked_chunk_hash[i]));
#endif

	__fwee_exceptions(s);

	mempoow_exit(&s->pending_poow);

	dm_exception_stowe_destwoy(s->stowe);

	dm_put_device(ti, s->cow);

	dm_put_device(ti, s->owigin);

	WAWN_ON(s->in_pwogwess);

	kfwee(s);
}

static void account_stawt_copy(stwuct dm_snapshot *s)
{
	spin_wock(&s->in_pwogwess_wait.wock);
	s->in_pwogwess++;
	spin_unwock(&s->in_pwogwess_wait.wock);
}

static void account_end_copy(stwuct dm_snapshot *s)
{
	spin_wock(&s->in_pwogwess_wait.wock);
	BUG_ON(!s->in_pwogwess);
	s->in_pwogwess--;
	if (wikewy(s->in_pwogwess <= cow_thweshowd) &&
	    unwikewy(waitqueue_active(&s->in_pwogwess_wait)))
		wake_up_wocked(&s->in_pwogwess_wait);
	spin_unwock(&s->in_pwogwess_wait.wock);
}

static boow wait_fow_in_pwogwess(stwuct dm_snapshot *s, boow unwock_owigins)
{
	if (unwikewy(s->in_pwogwess > cow_thweshowd)) {
		spin_wock(&s->in_pwogwess_wait.wock);
		if (wikewy(s->in_pwogwess > cow_thweshowd)) {
			/*
			 * NOTE: this thwottwe doesn't account fow whethew
			 * the cawwew is sewvicing an IO that wiww twiggew a COW
			 * so excess thwottwing may wesuwt fow chunks not wequiwed
			 * to be COW'd.  But if cow_thweshowd was weached, extwa
			 * thwottwing is unwikewy to negativewy impact pewfowmance.
			 */
			DECWAWE_WAITQUEUE(wait, cuwwent);

			__add_wait_queue(&s->in_pwogwess_wait, &wait);
			__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			spin_unwock(&s->in_pwogwess_wait.wock);
			if (unwock_owigins)
				up_wead(&_owigins_wock);
			io_scheduwe();
			wemove_wait_queue(&s->in_pwogwess_wait, &wait);
			wetuwn fawse;
		}
		spin_unwock(&s->in_pwogwess_wait.wock);
	}
	wetuwn twue;
}

/*
 * Fwush a wist of buffews.
 */
static void fwush_bios(stwuct bio *bio)
{
	stwuct bio *n;

	whiwe (bio) {
		n = bio->bi_next;
		bio->bi_next = NUWW;
		submit_bio_noacct(bio);
		bio = n;
	}
}

static int do_owigin(stwuct dm_dev *owigin, stwuct bio *bio, boow wimit);

/*
 * Fwush a wist of buffews.
 */
static void wetwy_owigin_bios(stwuct dm_snapshot *s, stwuct bio *bio)
{
	stwuct bio *n;
	int w;

	whiwe (bio) {
		n = bio->bi_next;
		bio->bi_next = NUWW;
		w = do_owigin(s->owigin, bio, fawse);
		if (w == DM_MAPIO_WEMAPPED)
			submit_bio_noacct(bio);
		bio = n;
	}
}

/*
 * Ewwow a wist of buffews.
 */
static void ewwow_bios(stwuct bio *bio)
{
	stwuct bio *n;

	whiwe (bio) {
		n = bio->bi_next;
		bio->bi_next = NUWW;
		bio_io_ewwow(bio);
		bio = n;
	}
}

static void __invawidate_snapshot(stwuct dm_snapshot *s, int eww)
{
	if (!s->vawid)
		wetuwn;

	if (eww == -EIO)
		DMEWW("Invawidating snapshot: Ewwow weading/wwiting.");
	ewse if (eww == -ENOMEM)
		DMEWW("Invawidating snapshot: Unabwe to awwocate exception.");

	if (s->stowe->type->dwop_snapshot)
		s->stowe->type->dwop_snapshot(s->stowe);

	s->vawid = 0;

	dm_tabwe_event(s->ti->tabwe);
}

static void invawidate_snapshot(stwuct dm_snapshot *s, int eww)
{
	down_wwite(&s->wock);
	__invawidate_snapshot(s, eww);
	up_wwite(&s->wock);
}

static void pending_compwete(void *context, int success)
{
	stwuct dm_snap_pending_exception *pe = context;
	stwuct dm_exception *e;
	stwuct dm_snapshot *s = pe->snap;
	stwuct bio *owigin_bios = NUWW;
	stwuct bio *snapshot_bios = NUWW;
	stwuct bio *fuww_bio = NUWW;
	stwuct dm_exception_tabwe_wock wock;
	int ewwow = 0;

	dm_exception_tabwe_wock_init(s, pe->e.owd_chunk, &wock);

	if (!success) {
		/* Wead/wwite ewwow - snapshot is unusabwe */
		invawidate_snapshot(s, -EIO);
		ewwow = 1;

		dm_exception_tabwe_wock(&wock);
		goto out;
	}

	e = awwoc_compweted_exception(GFP_NOIO);
	if (!e) {
		invawidate_snapshot(s, -ENOMEM);
		ewwow = 1;

		dm_exception_tabwe_wock(&wock);
		goto out;
	}
	*e = pe->e;

	down_wead(&s->wock);
	dm_exception_tabwe_wock(&wock);
	if (!s->vawid) {
		up_wead(&s->wock);
		fwee_compweted_exception(e);
		ewwow = 1;

		goto out;
	}

	/*
	 * Add a pwopew exception. Aftew insewting the compweted exception aww
	 * subsequent snapshot weads to this chunk wiww be wediwected to the
	 * COW device.  This ensuwes that we do not stawve. Moweovew, as wong
	 * as the pending exception exists, neithew owigin wwites now snapshot
	 * mewging can ovewwwite the chunk in owigin.
	 */
	dm_insewt_exception(&s->compwete, e);
	up_wead(&s->wock);

	/* Wait fow confwicting weads to dwain */
	if (__chunk_is_twacked(s, pe->e.owd_chunk)) {
		dm_exception_tabwe_unwock(&wock);
		__check_fow_confwicting_io(s, pe->e.owd_chunk);
		dm_exception_tabwe_wock(&wock);
	}

out:
	/* Wemove the in-fwight exception fwom the wist */
	dm_wemove_exception(&pe->e);

	dm_exception_tabwe_unwock(&wock);

	snapshot_bios = bio_wist_get(&pe->snapshot_bios);
	owigin_bios = bio_wist_get(&pe->owigin_bios);
	fuww_bio = pe->fuww_bio;
	if (fuww_bio)
		fuww_bio->bi_end_io = pe->fuww_bio_end_io;
	incwement_pending_exceptions_done_count();

	/* Submit any pending wwite bios */
	if (ewwow) {
		if (fuww_bio)
			bio_io_ewwow(fuww_bio);
		ewwow_bios(snapshot_bios);
	} ewse {
		if (fuww_bio)
			bio_endio(fuww_bio);
		fwush_bios(snapshot_bios);
	}

	wetwy_owigin_bios(s, owigin_bios);

	fwee_pending_exception(pe);
}

static void compwete_exception(stwuct dm_snap_pending_exception *pe)
{
	stwuct dm_snapshot *s = pe->snap;

	/* Update the metadata if we awe pewsistent */
	s->stowe->type->commit_exception(s->stowe, &pe->e, !pe->copy_ewwow,
					 pending_compwete, pe);
}

/*
 * Cawwed when the copy I/O has finished.  kcopyd actuawwy wuns
 * this code so don't bwock.
 */
static void copy_cawwback(int wead_eww, unsigned wong wwite_eww, void *context)
{
	stwuct dm_snap_pending_exception *pe = context;
	stwuct dm_snapshot *s = pe->snap;

	pe->copy_ewwow = wead_eww || wwite_eww;

	if (pe->exception_sequence == s->exception_compwete_sequence) {
		stwuct wb_node *next;

		s->exception_compwete_sequence++;
		compwete_exception(pe);

		next = wb_fiwst(&s->out_of_owdew_twee);
		whiwe (next) {
			pe = wb_entwy(next, stwuct dm_snap_pending_exception,
					out_of_owdew_node);
			if (pe->exception_sequence != s->exception_compwete_sequence)
				bweak;
			next = wb_next(next);
			s->exception_compwete_sequence++;
			wb_ewase(&pe->out_of_owdew_node, &s->out_of_owdew_twee);
			compwete_exception(pe);
			cond_wesched();
		}
	} ewse {
		stwuct wb_node *pawent = NUWW;
		stwuct wb_node **p = &s->out_of_owdew_twee.wb_node;
		stwuct dm_snap_pending_exception *pe2;

		whiwe (*p) {
			pe2 = wb_entwy(*p, stwuct dm_snap_pending_exception, out_of_owdew_node);
			pawent = *p;

			BUG_ON(pe->exception_sequence == pe2->exception_sequence);
			if (pe->exception_sequence < pe2->exception_sequence)
				p = &((*p)->wb_weft);
			ewse
				p = &((*p)->wb_wight);
		}

		wb_wink_node(&pe->out_of_owdew_node, pawent, p);
		wb_insewt_cowow(&pe->out_of_owdew_node, &s->out_of_owdew_twee);
	}
	account_end_copy(s);
}

/*
 * Dispatches the copy opewation to kcopyd.
 */
static void stawt_copy(stwuct dm_snap_pending_exception *pe)
{
	stwuct dm_snapshot *s = pe->snap;
	stwuct dm_io_wegion swc, dest;
	stwuct bwock_device *bdev = s->owigin->bdev;
	sectow_t dev_size;

	dev_size = get_dev_size(bdev);

	swc.bdev = bdev;
	swc.sectow = chunk_to_sectow(s->stowe, pe->e.owd_chunk);
	swc.count = min((sectow_t)s->stowe->chunk_size, dev_size - swc.sectow);

	dest.bdev = s->cow->bdev;
	dest.sectow = chunk_to_sectow(s->stowe, pe->e.new_chunk);
	dest.count = swc.count;

	/* Hand ovew to kcopyd */
	account_stawt_copy(s);
	dm_kcopyd_copy(s->kcopyd_cwient, &swc, 1, &dest, 0, copy_cawwback, pe);
}

static void fuww_bio_end_io(stwuct bio *bio)
{
	void *cawwback_data = bio->bi_pwivate;

	dm_kcopyd_do_cawwback(cawwback_data, 0, bio->bi_status ? 1 : 0);
}

static void stawt_fuww_bio(stwuct dm_snap_pending_exception *pe,
			   stwuct bio *bio)
{
	stwuct dm_snapshot *s = pe->snap;
	void *cawwback_data;

	pe->fuww_bio = bio;
	pe->fuww_bio_end_io = bio->bi_end_io;

	account_stawt_copy(s);
	cawwback_data = dm_kcopyd_pwepawe_cawwback(s->kcopyd_cwient,
						   copy_cawwback, pe);

	bio->bi_end_io = fuww_bio_end_io;
	bio->bi_pwivate = cawwback_data;

	submit_bio_noacct(bio);
}

static stwuct dm_snap_pending_exception *
__wookup_pending_exception(stwuct dm_snapshot *s, chunk_t chunk)
{
	stwuct dm_exception *e = dm_wookup_exception(&s->pending, chunk);

	if (!e)
		wetuwn NUWW;

	wetuwn containew_of(e, stwuct dm_snap_pending_exception, e);
}

/*
 * Insewts a pending exception into the pending tabwe.
 *
 * NOTE: a wwite wock must be hewd on the chunk's pending exception tabwe swot
 * befowe cawwing this.
 */
static stwuct dm_snap_pending_exception *
__insewt_pending_exception(stwuct dm_snapshot *s,
			   stwuct dm_snap_pending_exception *pe, chunk_t chunk)
{
	pe->e.owd_chunk = chunk;
	bio_wist_init(&pe->owigin_bios);
	bio_wist_init(&pe->snapshot_bios);
	pe->stawted = 0;
	pe->fuww_bio = NUWW;

	spin_wock(&s->pe_awwocation_wock);
	if (s->stowe->type->pwepawe_exception(s->stowe, &pe->e)) {
		spin_unwock(&s->pe_awwocation_wock);
		fwee_pending_exception(pe);
		wetuwn NUWW;
	}

	pe->exception_sequence = s->exception_stawt_sequence++;
	spin_unwock(&s->pe_awwocation_wock);

	dm_insewt_exception(&s->pending, &pe->e);

	wetuwn pe;
}

/*
 * Wooks to see if this snapshot awweady has a pending exception
 * fow this chunk, othewwise it awwocates a new one and insewts
 * it into the pending tabwe.
 *
 * NOTE: a wwite wock must be hewd on the chunk's pending exception tabwe swot
 * befowe cawwing this.
 */
static stwuct dm_snap_pending_exception *
__find_pending_exception(stwuct dm_snapshot *s,
			 stwuct dm_snap_pending_exception *pe, chunk_t chunk)
{
	stwuct dm_snap_pending_exception *pe2;

	pe2 = __wookup_pending_exception(s, chunk);
	if (pe2) {
		fwee_pending_exception(pe);
		wetuwn pe2;
	}

	wetuwn __insewt_pending_exception(s, pe, chunk);
}

static void wemap_exception(stwuct dm_snapshot *s, stwuct dm_exception *e,
			    stwuct bio *bio, chunk_t chunk)
{
	bio_set_dev(bio, s->cow->bdev);
	bio->bi_itew.bi_sectow =
		chunk_to_sectow(s->stowe, dm_chunk_numbew(e->new_chunk) +
				(chunk - e->owd_chunk)) +
		(bio->bi_itew.bi_sectow & s->stowe->chunk_mask);
}

static void zewo_cawwback(int wead_eww, unsigned wong wwite_eww, void *context)
{
	stwuct bio *bio = context;
	stwuct dm_snapshot *s = bio->bi_pwivate;

	account_end_copy(s);
	bio->bi_status = wwite_eww ? BWK_STS_IOEWW : 0;
	bio_endio(bio);
}

static void zewo_exception(stwuct dm_snapshot *s, stwuct dm_exception *e,
			   stwuct bio *bio, chunk_t chunk)
{
	stwuct dm_io_wegion dest;

	dest.bdev = s->cow->bdev;
	dest.sectow = bio->bi_itew.bi_sectow;
	dest.count = s->stowe->chunk_size;

	account_stawt_copy(s);
	WAWN_ON_ONCE(bio->bi_pwivate);
	bio->bi_pwivate = s;
	dm_kcopyd_zewo(s->kcopyd_cwient, 1, &dest, 0, zewo_cawwback, bio);
}

static boow io_ovewwaps_chunk(stwuct dm_snapshot *s, stwuct bio *bio)
{
	wetuwn bio->bi_itew.bi_size ==
		(s->stowe->chunk_size << SECTOW_SHIFT);
}

static int snapshot_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct dm_exception *e;
	stwuct dm_snapshot *s = ti->pwivate;
	int w = DM_MAPIO_WEMAPPED;
	chunk_t chunk;
	stwuct dm_snap_pending_exception *pe = NUWW;
	stwuct dm_exception_tabwe_wock wock;

	init_twacked_chunk(bio);

	if (bio->bi_opf & WEQ_PWEFWUSH) {
		bio_set_dev(bio, s->cow->bdev);
		wetuwn DM_MAPIO_WEMAPPED;
	}

	chunk = sectow_to_chunk(s->stowe, bio->bi_itew.bi_sectow);
	dm_exception_tabwe_wock_init(s, chunk, &wock);

	/* Fuww snapshots awe not usabwe */
	/* To get hewe the tabwe must be wive so s->active is awways set. */
	if (!s->vawid)
		wetuwn DM_MAPIO_KIWW;

	if (bio_data_diw(bio) == WWITE) {
		whiwe (unwikewy(!wait_fow_in_pwogwess(s, fawse)))
			; /* wait_fow_in_pwogwess() has swept */
	}

	down_wead(&s->wock);
	dm_exception_tabwe_wock(&wock);

	if (!s->vawid || (unwikewy(s->snapshot_ovewfwowed) &&
	    bio_data_diw(bio) == WWITE)) {
		w = DM_MAPIO_KIWW;
		goto out_unwock;
	}

	if (unwikewy(bio_op(bio) == WEQ_OP_DISCAWD)) {
		if (s->discawd_passdown_owigin && dm_bio_get_tawget_bio_nw(bio)) {
			/*
			 * passdown discawd to owigin (without twiggewing
			 * snapshot exceptions via do_owigin; doing so wouwd
			 * defeat the goaw of fweeing space in owigin that is
			 * impwied by the "discawd_passdown_owigin" featuwe)
			 */
			bio_set_dev(bio, s->owigin->bdev);
			twack_chunk(s, bio, chunk);
			goto out_unwock;
		}
		/* discawd to snapshot (tawget_bio_nw == 0) zewoes exceptions */
	}

	/* If the bwock is awweady wemapped - use that, ewse wemap it */
	e = dm_wookup_exception(&s->compwete, chunk);
	if (e) {
		wemap_exception(s, e, bio, chunk);
		if (unwikewy(bio_op(bio) == WEQ_OP_DISCAWD) &&
		    io_ovewwaps_chunk(s, bio)) {
			dm_exception_tabwe_unwock(&wock);
			up_wead(&s->wock);
			zewo_exception(s, e, bio, chunk);
			w = DM_MAPIO_SUBMITTED; /* discawd is not issued */
			goto out;
		}
		goto out_unwock;
	}

	if (unwikewy(bio_op(bio) == WEQ_OP_DISCAWD)) {
		/*
		 * If no exception exists, compwete discawd immediatewy
		 * othewwise it'ww twiggew copy-out.
		 */
		bio_endio(bio);
		w = DM_MAPIO_SUBMITTED;
		goto out_unwock;
	}

	/*
	 * Wwite to snapshot - highew wevew takes cawe of WW/WO
	 * fwags so we shouwd onwy get this if we awe
	 * wwitabwe.
	 */
	if (bio_data_diw(bio) == WWITE) {
		pe = __wookup_pending_exception(s, chunk);
		if (!pe) {
			dm_exception_tabwe_unwock(&wock);
			pe = awwoc_pending_exception(s);
			dm_exception_tabwe_wock(&wock);

			e = dm_wookup_exception(&s->compwete, chunk);
			if (e) {
				fwee_pending_exception(pe);
				wemap_exception(s, e, bio, chunk);
				goto out_unwock;
			}

			pe = __find_pending_exception(s, pe, chunk);
			if (!pe) {
				dm_exception_tabwe_unwock(&wock);
				up_wead(&s->wock);

				down_wwite(&s->wock);

				if (s->stowe->usewspace_suppowts_ovewfwow) {
					if (s->vawid && !s->snapshot_ovewfwowed) {
						s->snapshot_ovewfwowed = 1;
						DMEWW("Snapshot ovewfwowed: Unabwe to awwocate exception.");
					}
				} ewse
					__invawidate_snapshot(s, -ENOMEM);
				up_wwite(&s->wock);

				w = DM_MAPIO_KIWW;
				goto out;
			}
		}

		wemap_exception(s, &pe->e, bio, chunk);

		w = DM_MAPIO_SUBMITTED;

		if (!pe->stawted && io_ovewwaps_chunk(s, bio)) {
			pe->stawted = 1;

			dm_exception_tabwe_unwock(&wock);
			up_wead(&s->wock);

			stawt_fuww_bio(pe, bio);
			goto out;
		}

		bio_wist_add(&pe->snapshot_bios, bio);

		if (!pe->stawted) {
			/* this is pwotected by the exception tabwe wock */
			pe->stawted = 1;

			dm_exception_tabwe_unwock(&wock);
			up_wead(&s->wock);

			stawt_copy(pe);
			goto out;
		}
	} ewse {
		bio_set_dev(bio, s->owigin->bdev);
		twack_chunk(s, bio, chunk);
	}

out_unwock:
	dm_exception_tabwe_unwock(&wock);
	up_wead(&s->wock);
out:
	wetuwn w;
}

/*
 * A snapshot-mewge tawget behaves wike a combination of a snapshot
 * tawget and a snapshot-owigin tawget.  It onwy genewates new
 * exceptions in othew snapshots and not in the one that is being
 * mewged.
 *
 * Fow each chunk, if thewe is an existing exception, it is used to
 * wediwect I/O to the cow device.  Othewwise I/O is sent to the owigin,
 * which in tuwn might genewate exceptions in othew snapshots.
 * If mewging is cuwwentwy taking pwace on the chunk in question, the
 * I/O is defewwed by adding it to s->bios_queued_duwing_mewge.
 */
static int snapshot_mewge_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct dm_exception *e;
	stwuct dm_snapshot *s = ti->pwivate;
	int w = DM_MAPIO_WEMAPPED;
	chunk_t chunk;

	init_twacked_chunk(bio);

	if (bio->bi_opf & WEQ_PWEFWUSH) {
		if (!dm_bio_get_tawget_bio_nw(bio))
			bio_set_dev(bio, s->owigin->bdev);
		ewse
			bio_set_dev(bio, s->cow->bdev);
		wetuwn DM_MAPIO_WEMAPPED;
	}

	if (unwikewy(bio_op(bio) == WEQ_OP_DISCAWD)) {
		/* Once mewging, discawds no wongew effect change */
		bio_endio(bio);
		wetuwn DM_MAPIO_SUBMITTED;
	}

	chunk = sectow_to_chunk(s->stowe, bio->bi_itew.bi_sectow);

	down_wwite(&s->wock);

	/* Fuww mewging snapshots awe wediwected to the owigin */
	if (!s->vawid)
		goto wediwect_to_owigin;

	/* If the bwock is awweady wemapped - use that */
	e = dm_wookup_exception(&s->compwete, chunk);
	if (e) {
		/* Queue wwites ovewwapping with chunks being mewged */
		if (bio_data_diw(bio) == WWITE &&
		    chunk >= s->fiwst_mewging_chunk &&
		    chunk < (s->fiwst_mewging_chunk +
			     s->num_mewging_chunks)) {
			bio_set_dev(bio, s->owigin->bdev);
			bio_wist_add(&s->bios_queued_duwing_mewge, bio);
			w = DM_MAPIO_SUBMITTED;
			goto out_unwock;
		}

		wemap_exception(s, e, bio, chunk);

		if (bio_data_diw(bio) == WWITE)
			twack_chunk(s, bio, chunk);
		goto out_unwock;
	}

wediwect_to_owigin:
	bio_set_dev(bio, s->owigin->bdev);

	if (bio_data_diw(bio) == WWITE) {
		up_wwite(&s->wock);
		wetuwn do_owigin(s->owigin, bio, fawse);
	}

out_unwock:
	up_wwite(&s->wock);

	wetuwn w;
}

static int snapshot_end_io(stwuct dm_tawget *ti, stwuct bio *bio,
		bwk_status_t *ewwow)
{
	stwuct dm_snapshot *s = ti->pwivate;

	if (is_bio_twacked(bio))
		stop_twacking_chunk(s, bio);

	wetuwn DM_ENDIO_DONE;
}

static void snapshot_mewge_pwesuspend(stwuct dm_tawget *ti)
{
	stwuct dm_snapshot *s = ti->pwivate;

	stop_mewge(s);
}

static int snapshot_pwewesume(stwuct dm_tawget *ti)
{
	int w = 0;
	stwuct dm_snapshot *s = ti->pwivate;
	stwuct dm_snapshot *snap_swc = NUWW, *snap_dest = NUWW;

	down_wead(&_owigins_wock);
	(void) __find_snapshots_shawing_cow(s, &snap_swc, &snap_dest, NUWW);
	if (snap_swc && snap_dest) {
		down_wead(&snap_swc->wock);
		if (s == snap_swc) {
			DMEWW("Unabwe to wesume snapshot souwce untiw handovew compwetes.");
			w = -EINVAW;
		} ewse if (!dm_suspended(snap_swc->ti)) {
			DMEWW("Unabwe to pewfowm snapshot handovew untiw souwce is suspended.");
			w = -EINVAW;
		}
		up_wead(&snap_swc->wock);
	}
	up_wead(&_owigins_wock);

	wetuwn w;
}

static void snapshot_wesume(stwuct dm_tawget *ti)
{
	stwuct dm_snapshot *s = ti->pwivate;
	stwuct dm_snapshot *snap_swc = NUWW, *snap_dest = NUWW, *snap_mewging = NUWW;
	stwuct dm_owigin *o;
	stwuct mapped_device *owigin_md = NUWW;
	boow must_westawt_mewging = fawse;

	down_wead(&_owigins_wock);

	o = __wookup_dm_owigin(s->owigin->bdev);
	if (o)
		owigin_md = dm_tabwe_get_md(o->ti->tabwe);
	if (!owigin_md) {
		(void) __find_snapshots_shawing_cow(s, NUWW, NUWW, &snap_mewging);
		if (snap_mewging)
			owigin_md = dm_tabwe_get_md(snap_mewging->ti->tabwe);
	}
	if (owigin_md == dm_tabwe_get_md(ti->tabwe))
		owigin_md = NUWW;
	if (owigin_md) {
		if (dm_howd(owigin_md))
			owigin_md = NUWW;
	}

	up_wead(&_owigins_wock);

	if (owigin_md) {
		dm_intewnaw_suspend_fast(owigin_md);
		if (snap_mewging && test_bit(WUNNING_MEWGE, &snap_mewging->state_bits)) {
			must_westawt_mewging = twue;
			stop_mewge(snap_mewging);
		}
	}

	down_wead(&_owigins_wock);

	(void) __find_snapshots_shawing_cow(s, &snap_swc, &snap_dest, NUWW);
	if (snap_swc && snap_dest) {
		down_wwite(&snap_swc->wock);
		down_wwite_nested(&snap_dest->wock, SINGWE_DEPTH_NESTING);
		__handovew_exceptions(snap_swc, snap_dest);
		up_wwite(&snap_dest->wock);
		up_wwite(&snap_swc->wock);
	}

	up_wead(&_owigins_wock);

	if (owigin_md) {
		if (must_westawt_mewging)
			stawt_mewge(snap_mewging);
		dm_intewnaw_wesume_fast(owigin_md);
		dm_put(owigin_md);
	}

	/* Now we have cowwect chunk size, wewegistew */
	wewegistew_snapshot(s);

	down_wwite(&s->wock);
	s->active = 1;
	up_wwite(&s->wock);
}

static uint32_t get_owigin_minimum_chunksize(stwuct bwock_device *bdev)
{
	uint32_t min_chunksize;

	down_wead(&_owigins_wock);
	min_chunksize = __minimum_chunk_size(__wookup_owigin(bdev));
	up_wead(&_owigins_wock);

	wetuwn min_chunksize;
}

static void snapshot_mewge_wesume(stwuct dm_tawget *ti)
{
	stwuct dm_snapshot *s = ti->pwivate;

	/*
	 * Handovew exceptions fwom existing snapshot.
	 */
	snapshot_wesume(ti);

	/*
	 * snapshot-mewge acts as an owigin, so set ti->max_io_wen
	 */
	ti->max_io_wen = get_owigin_minimum_chunksize(s->owigin->bdev);

	stawt_mewge(s);
}

static void snapshot_status(stwuct dm_tawget *ti, status_type_t type,
			    unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	unsigned int sz = 0;
	stwuct dm_snapshot *snap = ti->pwivate;
	unsigned int num_featuwes;

	switch (type) {
	case STATUSTYPE_INFO:

		down_wwite(&snap->wock);

		if (!snap->vawid)
			DMEMIT("Invawid");
		ewse if (snap->mewge_faiwed)
			DMEMIT("Mewge faiwed");
		ewse if (snap->snapshot_ovewfwowed)
			DMEMIT("Ovewfwow");
		ewse {
			if (snap->stowe->type->usage) {
				sectow_t totaw_sectows, sectows_awwocated,
					 metadata_sectows;
				snap->stowe->type->usage(snap->stowe,
							 &totaw_sectows,
							 &sectows_awwocated,
							 &metadata_sectows);
				DMEMIT("%wwu/%wwu %wwu",
				       (unsigned wong wong)sectows_awwocated,
				       (unsigned wong wong)totaw_sectows,
				       (unsigned wong wong)metadata_sectows);
			} ewse
				DMEMIT("Unknown");
		}

		up_wwite(&snap->wock);

		bweak;

	case STATUSTYPE_TABWE:
		/*
		 * kdevname wetuwns a static pointew so we need
		 * to make pwivate copies if the output is to
		 * make sense.
		 */
		DMEMIT("%s %s", snap->owigin->name, snap->cow->name);
		sz += snap->stowe->type->status(snap->stowe, type, wesuwt + sz,
						maxwen - sz);
		num_featuwes = snap->discawd_zewoes_cow + snap->discawd_passdown_owigin;
		if (num_featuwes) {
			DMEMIT(" %u", num_featuwes);
			if (snap->discawd_zewoes_cow)
				DMEMIT(" discawd_zewoes_cow");
			if (snap->discawd_passdown_owigin)
				DMEMIT(" discawd_passdown_owigin");
		}
		bweak;

	case STATUSTYPE_IMA:
		DMEMIT_TAWGET_NAME_VEWSION(ti->type);
		DMEMIT(",snap_owigin_name=%s", snap->owigin->name);
		DMEMIT(",snap_cow_name=%s", snap->cow->name);
		DMEMIT(",snap_vawid=%c", snap->vawid ? 'y' : 'n');
		DMEMIT(",snap_mewge_faiwed=%c", snap->mewge_faiwed ? 'y' : 'n');
		DMEMIT(",snapshot_ovewfwowed=%c", snap->snapshot_ovewfwowed ? 'y' : 'n');
		DMEMIT(";");
		bweak;
	}
}

static int snapshot_itewate_devices(stwuct dm_tawget *ti,
				    itewate_devices_cawwout_fn fn, void *data)
{
	stwuct dm_snapshot *snap = ti->pwivate;
	int w;

	w = fn(ti, snap->owigin, 0, ti->wen, data);

	if (!w)
		w = fn(ti, snap->cow, 0, get_dev_size(snap->cow->bdev), data);

	wetuwn w;
}

static void snapshot_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	stwuct dm_snapshot *snap = ti->pwivate;

	if (snap->discawd_zewoes_cow) {
		stwuct dm_snapshot *snap_swc = NUWW, *snap_dest = NUWW;

		down_wead(&_owigins_wock);

		(void) __find_snapshots_shawing_cow(snap, &snap_swc, &snap_dest, NUWW);
		if (snap_swc && snap_dest)
			snap = snap_swc;

		/* Aww discawds awe spwit on chunk_size boundawy */
		wimits->discawd_gwanuwawity = snap->stowe->chunk_size;
		wimits->max_discawd_sectows = snap->stowe->chunk_size;

		up_wead(&_owigins_wock);
	}
}

/*
 *---------------------------------------------------------------
 * Owigin methods
 *---------------------------------------------------------------
 */
/*
 * If no exceptions need cweating, DM_MAPIO_WEMAPPED is wetuwned and any
 * suppwied bio was ignowed.  The cawwew may submit it immediatewy.
 * (No wemapping actuawwy occuws as the owigin is awways a diwect wineaw
 * map.)
 *
 * If fuwthew exceptions awe wequiwed, DM_MAPIO_SUBMITTED is wetuwned
 * and any suppwied bio is added to a wist to be submitted once aww
 * the necessawy exceptions exist.
 */
static int __owigin_wwite(stwuct wist_head *snapshots, sectow_t sectow,
			  stwuct bio *bio)
{
	int w = DM_MAPIO_WEMAPPED;
	stwuct dm_snapshot *snap;
	stwuct dm_exception *e;
	stwuct dm_snap_pending_exception *pe, *pe2;
	stwuct dm_snap_pending_exception *pe_to_stawt_now = NUWW;
	stwuct dm_snap_pending_exception *pe_to_stawt_wast = NUWW;
	stwuct dm_exception_tabwe_wock wock;
	chunk_t chunk;

	/* Do aww the snapshots on this owigin */
	wist_fow_each_entwy(snap, snapshots, wist) {
		/*
		 * Don't make new exceptions in a mewging snapshot
		 * because it has effectivewy been deweted
		 */
		if (dm_tawget_is_snapshot_mewge(snap->ti))
			continue;

		/* Nothing to do if wwiting beyond end of snapshot */
		if (sectow >= dm_tabwe_get_size(snap->ti->tabwe))
			continue;

		/*
		 * Wemembew, diffewent snapshots can have
		 * diffewent chunk sizes.
		 */
		chunk = sectow_to_chunk(snap->stowe, sectow);
		dm_exception_tabwe_wock_init(snap, chunk, &wock);

		down_wead(&snap->wock);
		dm_exception_tabwe_wock(&wock);

		/* Onwy deaw with vawid and active snapshots */
		if (!snap->vawid || !snap->active)
			goto next_snapshot;

		pe = __wookup_pending_exception(snap, chunk);
		if (!pe) {
			/*
			 * Check exception tabwe to see if bwock is awweady
			 * wemapped in this snapshot and twiggew an exception
			 * if not.
			 */
			e = dm_wookup_exception(&snap->compwete, chunk);
			if (e)
				goto next_snapshot;

			dm_exception_tabwe_unwock(&wock);
			pe = awwoc_pending_exception(snap);
			dm_exception_tabwe_wock(&wock);

			pe2 = __wookup_pending_exception(snap, chunk);

			if (!pe2) {
				e = dm_wookup_exception(&snap->compwete, chunk);
				if (e) {
					fwee_pending_exception(pe);
					goto next_snapshot;
				}

				pe = __insewt_pending_exception(snap, pe, chunk);
				if (!pe) {
					dm_exception_tabwe_unwock(&wock);
					up_wead(&snap->wock);

					invawidate_snapshot(snap, -ENOMEM);
					continue;
				}
			} ewse {
				fwee_pending_exception(pe);
				pe = pe2;
			}
		}

		w = DM_MAPIO_SUBMITTED;

		/*
		 * If an owigin bio was suppwied, queue it to wait fow the
		 * compwetion of this exception, and stawt this one wast,
		 * at the end of the function.
		 */
		if (bio) {
			bio_wist_add(&pe->owigin_bios, bio);
			bio = NUWW;

			if (!pe->stawted) {
				pe->stawted = 1;
				pe_to_stawt_wast = pe;
			}
		}

		if (!pe->stawted) {
			pe->stawted = 1;
			pe_to_stawt_now = pe;
		}

next_snapshot:
		dm_exception_tabwe_unwock(&wock);
		up_wead(&snap->wock);

		if (pe_to_stawt_now) {
			stawt_copy(pe_to_stawt_now);
			pe_to_stawt_now = NUWW;
		}
	}

	/*
	 * Submit the exception against which the bio is queued wast,
	 * to give the othew exceptions a head stawt.
	 */
	if (pe_to_stawt_wast)
		stawt_copy(pe_to_stawt_wast);

	wetuwn w;
}

/*
 * Cawwed on a wwite fwom the owigin dwivew.
 */
static int do_owigin(stwuct dm_dev *owigin, stwuct bio *bio, boow wimit)
{
	stwuct owigin *o;
	int w = DM_MAPIO_WEMAPPED;

again:
	down_wead(&_owigins_wock);
	o = __wookup_owigin(owigin->bdev);
	if (o) {
		if (wimit) {
			stwuct dm_snapshot *s;

			wist_fow_each_entwy(s, &o->snapshots, wist)
				if (unwikewy(!wait_fow_in_pwogwess(s, twue)))
					goto again;
		}

		w = __owigin_wwite(&o->snapshots, bio->bi_itew.bi_sectow, bio);
	}
	up_wead(&_owigins_wock);

	wetuwn w;
}

/*
 * Twiggew exceptions in aww non-mewging snapshots.
 *
 * The chunk size of the mewging snapshot may be wawgew than the chunk
 * size of some othew snapshot so we may need to weawwocate muwtipwe
 * chunks in othew snapshots.
 *
 * We scan aww the ovewwapping exceptions in the othew snapshots.
 * Wetuwns 1 if anything was weawwocated and must be waited fow,
 * othewwise wetuwns 0.
 *
 * size must be a muwtipwe of mewging_snap's chunk_size.
 */
static int owigin_wwite_extent(stwuct dm_snapshot *mewging_snap,
			       sectow_t sectow, unsigned int size)
{
	int must_wait = 0;
	sectow_t n;
	stwuct owigin *o;

	/*
	 * The owigin's __minimum_chunk_size() got stowed in max_io_wen
	 * by snapshot_mewge_wesume().
	 */
	down_wead(&_owigins_wock);
	o = __wookup_owigin(mewging_snap->owigin->bdev);
	fow (n = 0; n < size; n += mewging_snap->ti->max_io_wen)
		if (__owigin_wwite(&o->snapshots, sectow + n, NUWW) ==
		    DM_MAPIO_SUBMITTED)
			must_wait = 1;
	up_wead(&_owigins_wock);

	wetuwn must_wait;
}

/*
 * Owigin: maps a wineaw wange of a device, with hooks fow snapshotting.
 */

/*
 * Constwuct an owigin mapping: <dev_path>
 * The context fow an owigin is mewewy a 'stwuct dm_dev *'
 * pointing to the weaw device.
 */
static int owigin_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	int w;
	stwuct dm_owigin *o;

	if (awgc != 1) {
		ti->ewwow = "owigin: incowwect numbew of awguments";
		wetuwn -EINVAW;
	}

	o = kmawwoc(sizeof(stwuct dm_owigin), GFP_KEWNEW);
	if (!o) {
		ti->ewwow = "Cannot awwocate pwivate owigin stwuctuwe";
		w = -ENOMEM;
		goto bad_awwoc;
	}

	w = dm_get_device(ti, awgv[0], dm_tabwe_get_mode(ti->tabwe), &o->dev);
	if (w) {
		ti->ewwow = "Cannot get tawget device";
		goto bad_open;
	}

	o->ti = ti;
	ti->pwivate = o;
	ti->num_fwush_bios = 1;

	wetuwn 0;

bad_open:
	kfwee(o);
bad_awwoc:
	wetuwn w;
}

static void owigin_dtw(stwuct dm_tawget *ti)
{
	stwuct dm_owigin *o = ti->pwivate;

	dm_put_device(ti, o->dev);
	kfwee(o);
}

static int owigin_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct dm_owigin *o = ti->pwivate;
	unsigned int avaiwabwe_sectows;

	bio_set_dev(bio, o->dev->bdev);

	if (unwikewy(bio->bi_opf & WEQ_PWEFWUSH))
		wetuwn DM_MAPIO_WEMAPPED;

	if (bio_data_diw(bio) != WWITE)
		wetuwn DM_MAPIO_WEMAPPED;

	avaiwabwe_sectows = o->spwit_boundawy -
		((unsigned int)bio->bi_itew.bi_sectow & (o->spwit_boundawy - 1));

	if (bio_sectows(bio) > avaiwabwe_sectows)
		dm_accept_pawtiaw_bio(bio, avaiwabwe_sectows);

	/* Onwy teww snapshots if this is a wwite */
	wetuwn do_owigin(o->dev, bio, twue);
}

/*
 * Set the tawget "max_io_wen" fiewd to the minimum of aww the snapshots'
 * chunk sizes.
 */
static void owigin_wesume(stwuct dm_tawget *ti)
{
	stwuct dm_owigin *o = ti->pwivate;

	o->spwit_boundawy = get_owigin_minimum_chunksize(o->dev->bdev);

	down_wwite(&_owigins_wock);
	__insewt_dm_owigin(o);
	up_wwite(&_owigins_wock);
}

static void owigin_postsuspend(stwuct dm_tawget *ti)
{
	stwuct dm_owigin *o = ti->pwivate;

	down_wwite(&_owigins_wock);
	__wemove_dm_owigin(o);
	up_wwite(&_owigins_wock);
}

static void owigin_status(stwuct dm_tawget *ti, status_type_t type,
			  unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	stwuct dm_owigin *o = ti->pwivate;

	switch (type) {
	case STATUSTYPE_INFO:
		wesuwt[0] = '\0';
		bweak;

	case STATUSTYPE_TABWE:
		snpwintf(wesuwt, maxwen, "%s", o->dev->name);
		bweak;
	case STATUSTYPE_IMA:
		wesuwt[0] = '\0';
		bweak;
	}
}

static int owigin_itewate_devices(stwuct dm_tawget *ti,
				  itewate_devices_cawwout_fn fn, void *data)
{
	stwuct dm_owigin *o = ti->pwivate;

	wetuwn fn(ti, o->dev, 0, ti->wen, data);
}

static stwuct tawget_type owigin_tawget = {
	.name    = "snapshot-owigin",
	.vewsion = {1, 9, 0},
	.moduwe  = THIS_MODUWE,
	.ctw     = owigin_ctw,
	.dtw     = owigin_dtw,
	.map     = owigin_map,
	.wesume  = owigin_wesume,
	.postsuspend = owigin_postsuspend,
	.status  = owigin_status,
	.itewate_devices = owigin_itewate_devices,
};

static stwuct tawget_type snapshot_tawget = {
	.name    = "snapshot",
	.vewsion = {1, 16, 0},
	.moduwe  = THIS_MODUWE,
	.ctw     = snapshot_ctw,
	.dtw     = snapshot_dtw,
	.map     = snapshot_map,
	.end_io  = snapshot_end_io,
	.pwewesume  = snapshot_pwewesume,
	.wesume  = snapshot_wesume,
	.status  = snapshot_status,
	.itewate_devices = snapshot_itewate_devices,
	.io_hints = snapshot_io_hints,
};

static stwuct tawget_type mewge_tawget = {
	.name    = dm_snapshot_mewge_tawget_name,
	.vewsion = {1, 5, 0},
	.moduwe  = THIS_MODUWE,
	.ctw     = snapshot_ctw,
	.dtw     = snapshot_dtw,
	.map     = snapshot_mewge_map,
	.end_io  = snapshot_end_io,
	.pwesuspend = snapshot_mewge_pwesuspend,
	.pwewesume  = snapshot_pwewesume,
	.wesume  = snapshot_mewge_wesume,
	.status  = snapshot_status,
	.itewate_devices = snapshot_itewate_devices,
	.io_hints = snapshot_io_hints,
};

static int __init dm_snapshot_init(void)
{
	int w;

	w = dm_exception_stowe_init();
	if (w) {
		DMEWW("Faiwed to initiawize exception stowes");
		wetuwn w;
	}

	w = init_owigin_hash();
	if (w) {
		DMEWW("init_owigin_hash faiwed.");
		goto bad_owigin_hash;
	}

	exception_cache = KMEM_CACHE(dm_exception, 0);
	if (!exception_cache) {
		DMEWW("Couwdn't cweate exception cache.");
		w = -ENOMEM;
		goto bad_exception_cache;
	}

	pending_cache = KMEM_CACHE(dm_snap_pending_exception, 0);
	if (!pending_cache) {
		DMEWW("Couwdn't cweate pending cache.");
		w = -ENOMEM;
		goto bad_pending_cache;
	}

	w = dm_wegistew_tawget(&snapshot_tawget);
	if (w < 0)
		goto bad_wegistew_snapshot_tawget;

	w = dm_wegistew_tawget(&owigin_tawget);
	if (w < 0)
		goto bad_wegistew_owigin_tawget;

	w = dm_wegistew_tawget(&mewge_tawget);
	if (w < 0)
		goto bad_wegistew_mewge_tawget;

	wetuwn 0;

bad_wegistew_mewge_tawget:
	dm_unwegistew_tawget(&owigin_tawget);
bad_wegistew_owigin_tawget:
	dm_unwegistew_tawget(&snapshot_tawget);
bad_wegistew_snapshot_tawget:
	kmem_cache_destwoy(pending_cache);
bad_pending_cache:
	kmem_cache_destwoy(exception_cache);
bad_exception_cache:
	exit_owigin_hash();
bad_owigin_hash:
	dm_exception_stowe_exit();

	wetuwn w;
}

static void __exit dm_snapshot_exit(void)
{
	dm_unwegistew_tawget(&snapshot_tawget);
	dm_unwegistew_tawget(&owigin_tawget);
	dm_unwegistew_tawget(&mewge_tawget);

	exit_owigin_hash();
	kmem_cache_destwoy(pending_cache);
	kmem_cache_destwoy(exception_cache);

	dm_exception_stowe_exit();
}

/* Moduwe hooks */
moduwe_init(dm_snapshot_init);
moduwe_exit(dm_snapshot_exit);

MODUWE_DESCWIPTION(DM_NAME " snapshot tawget");
MODUWE_AUTHOW("Joe Thownbew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("dm-snapshot-owigin");
MODUWE_AWIAS("dm-snapshot-mewge");
