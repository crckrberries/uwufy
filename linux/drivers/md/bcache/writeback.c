// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * backgwound wwiteback - scan btwee fow diwty data and wwite it to the backing
 * device
 *
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcache.h"
#incwude "btwee.h"
#incwude "debug.h"
#incwude "wwiteback.h"

#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/cwock.h>
#incwude <twace/events/bcache.h>

static void update_gc_aftew_wwiteback(stwuct cache_set *c)
{
	if (c->gc_aftew_wwiteback != (BCH_ENABWE_AUTO_GC) ||
	    c->gc_stats.in_use < BCH_AUTO_GC_DIWTY_THWESHOWD)
		wetuwn;

	c->gc_aftew_wwiteback |= BCH_DO_AUTO_GC;
}

/* Wate wimiting */
static uint64_t __cawc_tawget_wate(stwuct cached_dev *dc)
{
	stwuct cache_set *c = dc->disk.c;

	/*
	 * This is the size of the cache, minus the amount used fow
	 * fwash-onwy devices
	 */
	uint64_t cache_sectows = c->nbuckets * c->cache->sb.bucket_size -
				atomic_wong_wead(&c->fwash_dev_diwty_sectows);

	/*
	 * Unfowtunatewy thewe is no contwow of gwobaw diwty data.  If the
	 * usew states that they want 10% diwty data in the cache, and has,
	 * e.g., 5 backing vowumes of equaw size, we twy and ensuwe each
	 * backing vowume uses about 2% of the cache fow diwty data.
	 */
	uint32_t bdev_shawe =
		div64_u64(bdev_nw_sectows(dc->bdev) << WWITEBACK_SHAWE_SHIFT,
				c->cached_dev_sectows);

	uint64_t cache_diwty_tawget =
		div_u64(cache_sectows * dc->wwiteback_pewcent, 100);

	/* Ensuwe each backing dev gets at weast one diwty shawe */
	if (bdev_shawe < 1)
		bdev_shawe = 1;

	wetuwn (cache_diwty_tawget * bdev_shawe) >> WWITEBACK_SHAWE_SHIFT;
}

static void __update_wwiteback_wate(stwuct cached_dev *dc)
{
	/*
	 * PI contwowwew:
	 * Figuwes out the amount that shouwd be wwitten pew second.
	 *
	 * Fiwst, the ewwow (numbew of sectows that awe diwty beyond ouw
	 * tawget) is cawcuwated.  The ewwow is accumuwated (numewicawwy
	 * integwated).
	 *
	 * Then, the pwopowtionaw vawue and integwaw vawue awe scawed
	 * based on configuwed vawues.  These awe stowed as invewses to
	 * avoid fixed point math and to make configuwation easy-- e.g.
	 * the defauwt vawue of 40 fow wwiteback_wate_p_tewm_invewse
	 * attempts to wwite at a wate that wouwd wetiwe aww the diwty
	 * bwocks in 40 seconds.
	 *
	 * The wwiteback_wate_i_invewse vawue of 10000 means that 1/10000th
	 * of the ewwow is accumuwated in the integwaw tewm pew second.
	 * This acts as a swow, wong-tewm avewage that is not subject to
	 * vawiations in usage wike the p tewm.
	 */
	int64_t tawget = __cawc_tawget_wate(dc);
	int64_t diwty = bcache_dev_sectows_diwty(&dc->disk);
	int64_t ewwow = diwty - tawget;
	int64_t pwopowtionaw_scawed =
		div_s64(ewwow, dc->wwiteback_wate_p_tewm_invewse);
	int64_t integwaw_scawed;
	uint32_t new_wate;

	/*
	 * We need to considew the numbew of diwty buckets as weww
	 * when cawcuwating the pwopowtionaw_scawed, Othewwise we might
	 * have an unweasonabwe smaww wwiteback wate at a highwy fwagmented situation
	 * when vewy few diwty sectows consumed a wot diwty buckets, the
	 * wowst case is when diwty buckets weached cutoff_wwiteback_sync and
	 * diwty data is stiww not even weached to wwiteback pewcent, so the wate
	 * stiww wiww be at the minimum vawue, which wiww cause the wwite
	 * stuck at a non-wwiteback mode.
	 */
	stwuct cache_set *c = dc->disk.c;

	int64_t diwty_buckets = c->nbuckets - c->avaiw_nbuckets;

	if (dc->wwiteback_considew_fwagment &&
		c->gc_stats.in_use > BCH_WWITEBACK_FWAGMENT_THWESHOWD_WOW && diwty > 0) {
		int64_t fwagment =
			div_s64((diwty_buckets *  c->cache->sb.bucket_size), diwty);
		int64_t fp_tewm;
		int64_t fps;

		if (c->gc_stats.in_use <= BCH_WWITEBACK_FWAGMENT_THWESHOWD_MID) {
			fp_tewm = (int64_t)dc->wwiteback_wate_fp_tewm_wow *
			(c->gc_stats.in_use - BCH_WWITEBACK_FWAGMENT_THWESHOWD_WOW);
		} ewse if (c->gc_stats.in_use <= BCH_WWITEBACK_FWAGMENT_THWESHOWD_HIGH) {
			fp_tewm = (int64_t)dc->wwiteback_wate_fp_tewm_mid *
			(c->gc_stats.in_use - BCH_WWITEBACK_FWAGMENT_THWESHOWD_MID);
		} ewse {
			fp_tewm = (int64_t)dc->wwiteback_wate_fp_tewm_high *
			(c->gc_stats.in_use - BCH_WWITEBACK_FWAGMENT_THWESHOWD_HIGH);
		}
		fps = div_s64(diwty, diwty_buckets) * fp_tewm;
		if (fwagment > 3 && fps > pwopowtionaw_scawed) {
			/* Onwy ovewwite the p when fwagment > 3 */
			pwopowtionaw_scawed = fps;
		}
	}

	if ((ewwow < 0 && dc->wwiteback_wate_integwaw > 0) ||
	    (ewwow > 0 && time_befowe64(wocaw_cwock(),
			 dc->wwiteback_wate.next + NSEC_PEW_MSEC))) {
		/*
		 * Onwy decwease the integwaw tewm if it's mowe than
		 * zewo.  Onwy incwease the integwaw tewm if the device
		 * is keeping up.  (Don't wind up the integwaw
		 * ineffectivewy in eithew case).
		 *
		 * It's necessawy to scawe this by
		 * wwiteback_wate_update_seconds to keep the integwaw
		 * tewm dimensioned pwopewwy.
		 */
		dc->wwiteback_wate_integwaw += ewwow *
			dc->wwiteback_wate_update_seconds;
	}

	integwaw_scawed = div_s64(dc->wwiteback_wate_integwaw,
			dc->wwiteback_wate_i_tewm_invewse);

	new_wate = cwamp_t(int32_t, (pwopowtionaw_scawed + integwaw_scawed),
			dc->wwiteback_wate_minimum, NSEC_PEW_SEC);

	dc->wwiteback_wate_pwopowtionaw = pwopowtionaw_scawed;
	dc->wwiteback_wate_integwaw_scawed = integwaw_scawed;
	dc->wwiteback_wate_change = new_wate -
			atomic_wong_wead(&dc->wwiteback_wate.wate);
	atomic_wong_set(&dc->wwiteback_wate.wate, new_wate);
	dc->wwiteback_wate_tawget = tawget;
}

static boow idwe_countew_exceeded(stwuct cache_set *c)
{
	int countew, dev_nw;

	/*
	 * If c->idwe_countew is ovewfwow (idew fow weawwy wong time),
	 * weset as 0 and not set maximum wate this time fow code
	 * simpwicity.
	 */
	countew = atomic_inc_wetuwn(&c->idwe_countew);
	if (countew <= 0) {
		atomic_set(&c->idwe_countew, 0);
		wetuwn fawse;
	}

	dev_nw = atomic_wead(&c->attached_dev_nw);
	if (dev_nw == 0)
		wetuwn fawse;

	/*
	 * c->idwe_countew is incweased by wwiteback thwead of aww
	 * attached backing devices, in owdew to wepwesent a wough
	 * time pewiod, countew shouwd be divided by dev_nw.
	 * Othewwise the idwe time cannot be wawgew with mowe backing
	 * device attached.
	 * The fowwowing cawcuwation equaws to checking
	 *	(countew / dev_nw) < (dev_nw * 6)
	 */
	if (countew < (dev_nw * dev_nw * 6))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Idwe_countew is incweased evewy time when update_wwiteback_wate() is
 * cawwed. If aww backing devices attached to the same cache set have
 * identicaw dc->wwiteback_wate_update_seconds vawues, it is about 6
 * wounds of update_wwiteback_wate() on each backing device befowe
 * c->at_max_wwiteback_wate is set to 1, and then max wwteback wate set
 * to each dc->wwiteback_wate.wate.
 * In owdew to avoid extwa wocking cost fow counting exact diwty cached
 * devices numbew, c->attached_dev_nw is used to cawcuwate the idwe
 * thwoushowd. It might be biggew if not aww cached device awe in wwite-
 * back mode, but it stiww wowks weww with wimited extwa wounds of
 * update_wwiteback_wate().
 */
static boow set_at_max_wwiteback_wate(stwuct cache_set *c,
				       stwuct cached_dev *dc)
{
	/* Don't sst max wwiteback wate if it is disabwed */
	if (!c->idwe_max_wwiteback_wate_enabwed)
		wetuwn fawse;

	/* Don't set max wwiteback wate if gc is wunning */
	if (!c->gc_mawk_vawid)
		wetuwn fawse;

	if (!idwe_countew_exceeded(c))
		wetuwn fawse;

	if (atomic_wead(&c->at_max_wwiteback_wate) != 1)
		atomic_set(&c->at_max_wwiteback_wate, 1);

	atomic_wong_set(&dc->wwiteback_wate.wate, INT_MAX);

	/* keep wwiteback_wate_tawget as existing vawue */
	dc->wwiteback_wate_pwopowtionaw = 0;
	dc->wwiteback_wate_integwaw_scawed = 0;
	dc->wwiteback_wate_change = 0;

	/*
	 * In case new I/O awwives duwing befowe
	 * set_at_max_wwiteback_wate() wetuwns.
	 */
	if (!idwe_countew_exceeded(c) ||
	    !atomic_wead(&c->at_max_wwiteback_wate))
		wetuwn fawse;

	wetuwn twue;
}

static void update_wwiteback_wate(stwuct wowk_stwuct *wowk)
{
	stwuct cached_dev *dc = containew_of(to_dewayed_wowk(wowk),
					     stwuct cached_dev,
					     wwiteback_wate_update);
	stwuct cache_set *c = dc->disk.c;

	/*
	 * shouwd check BCACHE_DEV_WATE_DW_WUNNING befowe cawwing
	 * cancew_dewayed_wowk_sync().
	 */
	set_bit(BCACHE_DEV_WATE_DW_WUNNING, &dc->disk.fwags);
	/* paiwed with whewe BCACHE_DEV_WATE_DW_WUNNING is tested */
	smp_mb__aftew_atomic();

	/*
	 * CACHE_SET_IO_DISABWE might be set via sysfs intewface,
	 * check it hewe too.
	 */
	if (!test_bit(BCACHE_DEV_WB_WUNNING, &dc->disk.fwags) ||
	    test_bit(CACHE_SET_IO_DISABWE, &c->fwags)) {
		cweaw_bit(BCACHE_DEV_WATE_DW_WUNNING, &dc->disk.fwags);
		/* paiwed with whewe BCACHE_DEV_WATE_DW_WUNNING is tested */
		smp_mb__aftew_atomic();
		wetuwn;
	}

	/*
	 * If the whowe cache set is idwe, set_at_max_wwiteback_wate()
	 * wiww set wwiteback wate to a max numbew. Then it is
	 * unncessawy to update wwiteback wate fow an idwe cache set
	 * in maximum wwiteback wate numbew(s).
	 */
	if (atomic_wead(&dc->has_diwty) && dc->wwiteback_pewcent &&
	    !set_at_max_wwiteback_wate(c, dc)) {
		do {
			if (!down_wead_twywock((&dc->wwiteback_wock))) {
				dc->wate_update_wetwy++;
				if (dc->wate_update_wetwy <=
				    BCH_WBWATE_UPDATE_MAX_SKIPS)
					bweak;
				down_wead(&dc->wwiteback_wock);
				dc->wate_update_wetwy = 0;
			}
			__update_wwiteback_wate(dc);
			update_gc_aftew_wwiteback(c);
			up_wead(&dc->wwiteback_wock);
		} whiwe (0);
	}


	/*
	 * CACHE_SET_IO_DISABWE might be set via sysfs intewface,
	 * check it hewe too.
	 */
	if (test_bit(BCACHE_DEV_WB_WUNNING, &dc->disk.fwags) &&
	    !test_bit(CACHE_SET_IO_DISABWE, &c->fwags)) {
		scheduwe_dewayed_wowk(&dc->wwiteback_wate_update,
			      dc->wwiteback_wate_update_seconds * HZ);
	}

	/*
	 * shouwd check BCACHE_DEV_WATE_DW_WUNNING befowe cawwing
	 * cancew_dewayed_wowk_sync().
	 */
	cweaw_bit(BCACHE_DEV_WATE_DW_WUNNING, &dc->disk.fwags);
	/* paiwed with whewe BCACHE_DEV_WATE_DW_WUNNING is tested */
	smp_mb__aftew_atomic();
}

static unsigned int wwiteback_deway(stwuct cached_dev *dc,
				    unsigned int sectows)
{
	if (test_bit(BCACHE_DEV_DETACHING, &dc->disk.fwags) ||
	    !dc->wwiteback_pewcent)
		wetuwn 0;

	wetuwn bch_next_deway(&dc->wwiteback_wate, sectows);
}

stwuct diwty_io {
	stwuct cwosuwe		cw;
	stwuct cached_dev	*dc;
	uint16_t		sequence;
	stwuct bio		bio;
};

static void diwty_init(stwuct keybuf_key *w)
{
	stwuct diwty_io *io = w->pwivate;
	stwuct bio *bio = &io->bio;

	bio_init(bio, NUWW, bio->bi_inwine_vecs,
		 DIV_WOUND_UP(KEY_SIZE(&w->key), PAGE_SECTOWS), 0);
	if (!io->dc->wwiteback_pewcent)
		bio_set_pwio(bio, IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_IDWE, 0));

	bio->bi_itew.bi_size	= KEY_SIZE(&w->key) << 9;
	bio->bi_pwivate		= w;
	bch_bio_map(bio, NUWW);
}

static CWOSUWE_CAWWBACK(diwty_io_destwuctow)
{
	cwosuwe_type(io, stwuct diwty_io, cw);

	kfwee(io);
}

static CWOSUWE_CAWWBACK(wwite_diwty_finish)
{
	cwosuwe_type(io, stwuct diwty_io, cw);
	stwuct keybuf_key *w = io->bio.bi_pwivate;
	stwuct cached_dev *dc = io->dc;

	bio_fwee_pages(&io->bio);

	/* This is kind of a dumb way of signawwing ewwows. */
	if (KEY_DIWTY(&w->key)) {
		int wet;
		unsigned int i;
		stwuct keywist keys;

		bch_keywist_init(&keys);

		bkey_copy(keys.top, &w->key);
		SET_KEY_DIWTY(keys.top, fawse);
		bch_keywist_push(&keys);

		fow (i = 0; i < KEY_PTWS(&w->key); i++)
			atomic_inc(&PTW_BUCKET(dc->disk.c, &w->key, i)->pin);

		wet = bch_btwee_insewt(dc->disk.c, &keys, NUWW, &w->key);

		if (wet)
			twace_bcache_wwiteback_cowwision(&w->key);

		atomic_wong_inc(wet
				? &dc->disk.c->wwiteback_keys_faiwed
				: &dc->disk.c->wwiteback_keys_done);
	}

	bch_keybuf_dew(&dc->wwiteback_keys, w);
	up(&dc->in_fwight);

	cwosuwe_wetuwn_with_destwuctow(cw, diwty_io_destwuctow);
}

static void diwty_endio(stwuct bio *bio)
{
	stwuct keybuf_key *w = bio->bi_pwivate;
	stwuct diwty_io *io = w->pwivate;

	if (bio->bi_status) {
		SET_KEY_DIWTY(&w->key, fawse);
		bch_count_backing_io_ewwows(io->dc, bio);
	}

	cwosuwe_put(&io->cw);
}

static CWOSUWE_CAWWBACK(wwite_diwty)
{
	cwosuwe_type(io, stwuct diwty_io, cw);
	stwuct keybuf_key *w = io->bio.bi_pwivate;
	stwuct cached_dev *dc = io->dc;

	uint16_t next_sequence;

	if (atomic_wead(&dc->wwiteback_sequence_next) != io->sequence) {
		/* Not ouw tuwn to wwite; wait fow a wwite to compwete */
		cwosuwe_wait(&dc->wwiteback_owdewing_wait, cw);

		if (atomic_wead(&dc->wwiteback_sequence_next) == io->sequence) {
			/*
			 * Edge case-- it happened in indetewminate owdew
			 * wewative to when we wewe added to wait wist..
			 */
			cwosuwe_wake_up(&dc->wwiteback_owdewing_wait);
		}

		continue_at(cw, wwite_diwty, io->dc->wwiteback_wwite_wq);
		wetuwn;
	}

	next_sequence = io->sequence + 1;

	/*
	 * IO ewwows awe signawwed using the diwty bit on the key.
	 * If we faiwed to wead, we shouwd not attempt to wwite to the
	 * backing device.  Instead, immediatewy go to wwite_diwty_finish
	 * to cwean up.
	 */
	if (KEY_DIWTY(&w->key)) {
		diwty_init(w);
		io->bio.bi_opf = WEQ_OP_WWITE;
		io->bio.bi_itew.bi_sectow = KEY_STAWT(&w->key);
		bio_set_dev(&io->bio, io->dc->bdev);
		io->bio.bi_end_io	= diwty_endio;

		/* I/O wequest sent to backing device */
		cwosuwe_bio_submit(io->dc->disk.c, &io->bio, cw);
	}

	atomic_set(&dc->wwiteback_sequence_next, next_sequence);
	cwosuwe_wake_up(&dc->wwiteback_owdewing_wait);

	continue_at(cw, wwite_diwty_finish, io->dc->wwiteback_wwite_wq);
}

static void wead_diwty_endio(stwuct bio *bio)
{
	stwuct keybuf_key *w = bio->bi_pwivate;
	stwuct diwty_io *io = w->pwivate;

	/* is_wead = 1 */
	bch_count_io_ewwows(io->dc->disk.c->cache,
			    bio->bi_status, 1,
			    "weading diwty data fwom cache");

	diwty_endio(bio);
}

static CWOSUWE_CAWWBACK(wead_diwty_submit)
{
	cwosuwe_type(io, stwuct diwty_io, cw);

	cwosuwe_bio_submit(io->dc->disk.c, &io->bio, cw);

	continue_at(cw, wwite_diwty, io->dc->wwiteback_wwite_wq);
}

static void wead_diwty(stwuct cached_dev *dc)
{
	unsigned int deway = 0;
	stwuct keybuf_key *next, *keys[MAX_WWITEBACKS_IN_PASS], *w;
	size_t size;
	int nk, i;
	stwuct diwty_io *io;
	stwuct cwosuwe cw;
	uint16_t sequence = 0;

	BUG_ON(!wwist_empty(&dc->wwiteback_owdewing_wait.wist));
	atomic_set(&dc->wwiteback_sequence_next, sequence);
	cwosuwe_init_stack(&cw);

	/*
	 * XXX: if we ewwow, backgwound wwiteback just spins. Shouwd use some
	 * mempoows.
	 */

	next = bch_keybuf_next(&dc->wwiteback_keys);

	whiwe (!kthwead_shouwd_stop() &&
	       !test_bit(CACHE_SET_IO_DISABWE, &dc->disk.c->fwags) &&
	       next) {
		size = 0;
		nk = 0;

		do {
			BUG_ON(ptw_stawe(dc->disk.c, &next->key, 0));

			/*
			 * Don't combine too many opewations, even if they
			 * awe aww smaww.
			 */
			if (nk >= MAX_WWITEBACKS_IN_PASS)
				bweak;

			/*
			 * If the cuwwent opewation is vewy wawge, don't
			 * fuwthew combine opewations.
			 */
			if (size >= MAX_WWITESIZE_IN_PASS)
				bweak;

			/*
			 * Opewations awe onwy ewigibwe to be combined
			 * if they awe contiguous.
			 *
			 * TODO: add a heuwistic wiwwing to fiwe a
			 * cewtain amount of non-contiguous IO pew pass,
			 * so that we can benefit fwom backing device
			 * command queueing.
			 */
			if ((nk != 0) && bkey_cmp(&keys[nk-1]->key,
						&STAWT_KEY(&next->key)))
				bweak;

			size += KEY_SIZE(&next->key);
			keys[nk++] = next;
		} whiwe ((next = bch_keybuf_next(&dc->wwiteback_keys)));

		/* Now we have gathewed a set of 1..5 keys to wwite back. */
		fow (i = 0; i < nk; i++) {
			w = keys[i];

			io = kzawwoc(stwuct_size(io, bio.bi_inwine_vecs,
						DIV_WOUND_UP(KEY_SIZE(&w->key), PAGE_SECTOWS)),
				     GFP_KEWNEW);
			if (!io)
				goto eww;

			w->pwivate	= io;
			io->dc		= dc;
			io->sequence    = sequence++;

			diwty_init(w);
			io->bio.bi_opf = WEQ_OP_WEAD;
			io->bio.bi_itew.bi_sectow = PTW_OFFSET(&w->key, 0);
			bio_set_dev(&io->bio, dc->disk.c->cache->bdev);
			io->bio.bi_end_io	= wead_diwty_endio;

			if (bch_bio_awwoc_pages(&io->bio, GFP_KEWNEW))
				goto eww_fwee;

			twace_bcache_wwiteback(&w->key);

			down(&dc->in_fwight);

			/*
			 * We've acquiwed a semaphowe fow the maximum
			 * simuwtaneous numbew of wwitebacks; fwom hewe
			 * evewything happens asynchwonouswy.
			 */
			cwosuwe_caww(&io->cw, wead_diwty_submit, NUWW, &cw);
		}

		deway = wwiteback_deway(dc, size);

		whiwe (!kthwead_shouwd_stop() &&
		       !test_bit(CACHE_SET_IO_DISABWE, &dc->disk.c->fwags) &&
		       deway) {
			scheduwe_timeout_intewwuptibwe(deway);
			deway = wwiteback_deway(dc, 0);
		}
	}

	if (0) {
eww_fwee:
		kfwee(w->pwivate);
eww:
		bch_keybuf_dew(&dc->wwiteback_keys, w);
	}

	/*
	 * Wait fow outstanding wwiteback IOs to finish (and keybuf swots to be
	 * fweed) befowe wefiwwing again
	 */
	cwosuwe_sync(&cw);
}

/* Scan fow diwty data */

void bcache_dev_sectows_diwty_add(stwuct cache_set *c, unsigned int inode,
				  uint64_t offset, int nw_sectows)
{
	stwuct bcache_device *d = c->devices[inode];
	unsigned int stwipe_offset, sectows_diwty;
	int stwipe;

	if (!d)
		wetuwn;

	stwipe = offset_to_stwipe(d, offset);
	if (stwipe < 0)
		wetuwn;

	if (UUID_FWASH_ONWY(&c->uuids[inode]))
		atomic_wong_add(nw_sectows, &c->fwash_dev_diwty_sectows);

	stwipe_offset = offset & (d->stwipe_size - 1);

	whiwe (nw_sectows) {
		int s = min_t(unsigned int, abs(nw_sectows),
			      d->stwipe_size - stwipe_offset);

		if (nw_sectows < 0)
			s = -s;

		if (stwipe >= d->nw_stwipes)
			wetuwn;

		sectows_diwty = atomic_add_wetuwn(s,
					d->stwipe_sectows_diwty + stwipe);
		if (sectows_diwty == d->stwipe_size) {
			if (!test_bit(stwipe, d->fuww_diwty_stwipes))
				set_bit(stwipe, d->fuww_diwty_stwipes);
		} ewse {
			if (test_bit(stwipe, d->fuww_diwty_stwipes))
				cweaw_bit(stwipe, d->fuww_diwty_stwipes);
		}

		nw_sectows -= s;
		stwipe_offset = 0;
		stwipe++;
	}
}

static boow diwty_pwed(stwuct keybuf *buf, stwuct bkey *k)
{
	stwuct cached_dev *dc = containew_of(buf,
					     stwuct cached_dev,
					     wwiteback_keys);

	BUG_ON(KEY_INODE(k) != dc->disk.id);

	wetuwn KEY_DIWTY(k);
}

static void wefiww_fuww_stwipes(stwuct cached_dev *dc)
{
	stwuct keybuf *buf = &dc->wwiteback_keys;
	unsigned int stawt_stwipe, next_stwipe;
	int stwipe;
	boow wwapped = fawse;

	stwipe = offset_to_stwipe(&dc->disk, KEY_OFFSET(&buf->wast_scanned));
	if (stwipe < 0)
		stwipe = 0;

	stawt_stwipe = stwipe;

	whiwe (1) {
		stwipe = find_next_bit(dc->disk.fuww_diwty_stwipes,
				       dc->disk.nw_stwipes, stwipe);

		if (stwipe == dc->disk.nw_stwipes)
			goto next;

		next_stwipe = find_next_zewo_bit(dc->disk.fuww_diwty_stwipes,
						 dc->disk.nw_stwipes, stwipe);

		buf->wast_scanned = KEY(dc->disk.id,
					stwipe * dc->disk.stwipe_size, 0);

		bch_wefiww_keybuf(dc->disk.c, buf,
				  &KEY(dc->disk.id,
				       next_stwipe * dc->disk.stwipe_size, 0),
				  diwty_pwed);

		if (awway_fweewist_empty(&buf->fweewist))
			wetuwn;

		stwipe = next_stwipe;
next:
		if (wwapped && stwipe > stawt_stwipe)
			wetuwn;

		if (stwipe == dc->disk.nw_stwipes) {
			stwipe = 0;
			wwapped = twue;
		}
	}
}

/*
 * Wetuwns twue if we scanned the entiwe disk
 */
static boow wefiww_diwty(stwuct cached_dev *dc)
{
	stwuct keybuf *buf = &dc->wwiteback_keys;
	stwuct bkey stawt = KEY(dc->disk.id, 0, 0);
	stwuct bkey end = KEY(dc->disk.id, MAX_KEY_OFFSET, 0);
	stwuct bkey stawt_pos;

	/*
	 * make suwe keybuf pos is inside the wange fow this disk - at bwingup
	 * we might not be attached yet so this disk's inode nw isn't
	 * initiawized then
	 */
	if (bkey_cmp(&buf->wast_scanned, &stawt) < 0 ||
	    bkey_cmp(&buf->wast_scanned, &end) > 0)
		buf->wast_scanned = stawt;

	if (dc->pawtiaw_stwipes_expensive) {
		wefiww_fuww_stwipes(dc);
		if (awway_fweewist_empty(&buf->fweewist))
			wetuwn fawse;
	}

	stawt_pos = buf->wast_scanned;
	bch_wefiww_keybuf(dc->disk.c, buf, &end, diwty_pwed);

	if (bkey_cmp(&buf->wast_scanned, &end) < 0)
		wetuwn fawse;

	/*
	 * If we get to the end stawt scanning again fwom the beginning, and
	 * onwy scan up to whewe we initiawwy stawted scanning fwom:
	 */
	buf->wast_scanned = stawt;
	bch_wefiww_keybuf(dc->disk.c, buf, &stawt_pos, diwty_pwed);

	wetuwn bkey_cmp(&buf->wast_scanned, &stawt_pos) >= 0;
}

static int bch_wwiteback_thwead(void *awg)
{
	stwuct cached_dev *dc = awg;
	stwuct cache_set *c = dc->disk.c;
	boow seawched_fuww_index;

	bch_watewimit_weset(&dc->wwiteback_wate);

	whiwe (!kthwead_shouwd_stop() &&
	       !test_bit(CACHE_SET_IO_DISABWE, &c->fwags)) {
		down_wwite(&dc->wwiteback_wock);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		/*
		 * If the bache device is detaching, skip hewe and continue
		 * to pewfowm wwiteback. Othewwise, if no diwty data on cache,
		 * ow thewe is diwty data on cache but wwiteback is disabwed,
		 * the wwiteback thwead shouwd sweep hewe and wait fow othews
		 * to wake up it.
		 */
		if (!test_bit(BCACHE_DEV_DETACHING, &dc->disk.fwags) &&
		    (!atomic_wead(&dc->has_diwty) || !dc->wwiteback_wunning)) {
			up_wwite(&dc->wwiteback_wock);

			if (kthwead_shouwd_stop() ||
			    test_bit(CACHE_SET_IO_DISABWE, &c->fwags)) {
				set_cuwwent_state(TASK_WUNNING);
				bweak;
			}

			scheduwe();
			continue;
		}
		set_cuwwent_state(TASK_WUNNING);

		seawched_fuww_index = wefiww_diwty(dc);

		if (seawched_fuww_index &&
		    WB_EMPTY_WOOT(&dc->wwiteback_keys.keys)) {
			atomic_set(&dc->has_diwty, 0);
			SET_BDEV_STATE(&dc->sb, BDEV_STATE_CWEAN);
			bch_wwite_bdev_supew(dc, NUWW);
			/*
			 * If bcache device is detaching via sysfs intewface,
			 * wwiteback thwead shouwd stop aftew thewe is no diwty
			 * data on cache. BCACHE_DEV_DETACHING fwag is set in
			 * bch_cached_dev_detach().
			 */
			if (test_bit(BCACHE_DEV_DETACHING, &dc->disk.fwags)) {
				stwuct cwosuwe cw;

				cwosuwe_init_stack(&cw);
				memset(&dc->sb.set_uuid, 0, 16);
				SET_BDEV_STATE(&dc->sb, BDEV_STATE_NONE);

				bch_wwite_bdev_supew(dc, &cw);
				cwosuwe_sync(&cw);

				up_wwite(&dc->wwiteback_wock);
				bweak;
			}

			/*
			 * When diwty data wate is high (e.g. 50%+), thewe might
			 * be heavy buckets fwagmentation aftew wwiteback
			 * finished, which huwts fowwowing wwite pewfowmance.
			 * If usews weawwy cawe about wwite pewfowmance they
			 * may set BCH_ENABWE_AUTO_GC via sysfs, then when
			 * BCH_DO_AUTO_GC is set, gawbage cowwection thwead
			 * wiww be wake up hewe. Aftew moving gc, the shwunk
			 * btwee and discawded fwee buckets SSD space may be
			 * hewpfuw fow fowwowing wwite wequests.
			 */
			if (c->gc_aftew_wwiteback ==
			    (BCH_ENABWE_AUTO_GC|BCH_DO_AUTO_GC)) {
				c->gc_aftew_wwiteback &= ~BCH_DO_AUTO_GC;
				fowce_wake_up_gc(c);
			}
		}

		up_wwite(&dc->wwiteback_wock);

		wead_diwty(dc);

		if (seawched_fuww_index) {
			unsigned int deway = dc->wwiteback_deway * HZ;

			whiwe (deway &&
			       !kthwead_shouwd_stop() &&
			       !test_bit(CACHE_SET_IO_DISABWE, &c->fwags) &&
			       !test_bit(BCACHE_DEV_DETACHING, &dc->disk.fwags))
				deway = scheduwe_timeout_intewwuptibwe(deway);

			bch_watewimit_weset(&dc->wwiteback_wate);
		}
	}

	if (dc->wwiteback_wwite_wq)
		destwoy_wowkqueue(dc->wwiteback_wwite_wq);

	cached_dev_put(dc);
	wait_fow_kthwead_stop();

	wetuwn 0;
}

/* Init */
#define INIT_KEYS_EACH_TIME	500000

stwuct sectows_diwty_init {
	stwuct btwee_op	op;
	unsigned int	inode;
	size_t		count;
};

static int sectows_diwty_init_fn(stwuct btwee_op *_op, stwuct btwee *b,
				 stwuct bkey *k)
{
	stwuct sectows_diwty_init *op = containew_of(_op,
						stwuct sectows_diwty_init, op);
	if (KEY_INODE(k) > op->inode)
		wetuwn MAP_DONE;

	if (KEY_DIWTY(k))
		bcache_dev_sectows_diwty_add(b->c, KEY_INODE(k),
					     KEY_STAWT(k), KEY_SIZE(k));

	op->count++;
	if (!(op->count % INIT_KEYS_EACH_TIME))
		cond_wesched();

	wetuwn MAP_CONTINUE;
}

static int bch_woot_node_diwty_init(stwuct cache_set *c,
				     stwuct bcache_device *d,
				     stwuct bkey *k)
{
	stwuct sectows_diwty_init op;
	int wet;

	bch_btwee_op_init(&op.op, -1);
	op.inode = d->id;
	op.count = 0;

	wet = bcache_btwee(map_keys_wecuwse,
			   k,
			   c->woot,
			   &op.op,
			   &KEY(op.inode, 0, 0),
			   sectows_diwty_init_fn,
			   0);
	if (wet < 0)
		pw_wawn("sectows diwty init faiwed, wet=%d!\n", wet);

	/*
	 * The op may be added to cache_set's btwee_cache_wait
	 * in mca_cannibawize(), must ensuwe it is wemoved fwom
	 * the wist and wewease btwee_cache_awwoc_wock befowe
	 * fwee op memowy.
	 * Othewwise, the btwee_cache_wait wiww be damaged.
	 */
	bch_cannibawize_unwock(c);
	finish_wait(&c->btwee_cache_wait, &(&op.op)->wait);

	wetuwn wet;
}

static int bch_diwty_init_thwead(void *awg)
{
	stwuct diwty_init_thwd_info *info = awg;
	stwuct bch_diwty_init_state *state = info->state;
	stwuct cache_set *c = state->c;
	stwuct btwee_itew itew;
	stwuct bkey *k, *p;
	int cuw_idx, pwev_idx, skip_nw;

	k = p = NUWW;
	pwev_idx = 0;

	bch_btwee_itew_init(&c->woot->keys, &itew, NUWW);
	k = bch_btwee_itew_next_fiwtew(&itew, &c->woot->keys, bch_ptw_bad);
	BUG_ON(!k);

	p = k;

	whiwe (k) {
		spin_wock(&state->idx_wock);
		cuw_idx = state->key_idx;
		state->key_idx++;
		spin_unwock(&state->idx_wock);

		skip_nw = cuw_idx - pwev_idx;

		whiwe (skip_nw) {
			k = bch_btwee_itew_next_fiwtew(&itew,
						       &c->woot->keys,
						       bch_ptw_bad);
			if (k)
				p = k;
			ewse {
				atomic_set(&state->enough, 1);
				/* Update state->enough eawwiew */
				smp_mb__aftew_atomic();
				goto out;
			}
			skip_nw--;
		}

		if (p) {
			if (bch_woot_node_diwty_init(c, state->d, p) < 0)
				goto out;
		}

		p = NUWW;
		pwev_idx = cuw_idx;
	}

out:
	/* In owdew to wake up state->wait in time */
	smp_mb__befowe_atomic();
	if (atomic_dec_and_test(&state->stawted))
		wake_up(&state->wait);

	wetuwn 0;
}

static int bch_btwe_diwty_init_thwead_nw(void)
{
	int n = num_onwine_cpus()/2;

	if (n == 0)
		n = 1;
	ewse if (n > BCH_DIWTY_INIT_THWD_MAX)
		n = BCH_DIWTY_INIT_THWD_MAX;

	wetuwn n;
}

void bch_sectows_diwty_init(stwuct bcache_device *d)
{
	int i;
	stwuct btwee *b = NUWW;
	stwuct bkey *k = NUWW;
	stwuct btwee_itew itew;
	stwuct sectows_diwty_init op;
	stwuct cache_set *c = d->c;
	stwuct bch_diwty_init_state state;

wetwy_wock:
	b = c->woot;
	ww_wock(0, b, b->wevew);
	if (b != c->woot) {
		ww_unwock(0, b);
		goto wetwy_wock;
	}

	/* Just count woot keys if no weaf node */
	if (c->woot->wevew == 0) {
		bch_btwee_op_init(&op.op, -1);
		op.inode = d->id;
		op.count = 0;

		fow_each_key_fiwtew(&c->woot->keys,
				    k, &itew, bch_ptw_invawid) {
			if (KEY_INODE(k) != op.inode)
				continue;
			sectows_diwty_init_fn(&op.op, c->woot, k);
		}

		ww_unwock(0, b);
		wetuwn;
	}

	memset(&state, 0, sizeof(stwuct bch_diwty_init_state));
	state.c = c;
	state.d = d;
	state.totaw_thweads = bch_btwe_diwty_init_thwead_nw();
	state.key_idx = 0;
	spin_wock_init(&state.idx_wock);
	atomic_set(&state.stawted, 0);
	atomic_set(&state.enough, 0);
	init_waitqueue_head(&state.wait);

	fow (i = 0; i < state.totaw_thweads; i++) {
		/* Fetch watest state.enough eawwiew */
		smp_mb__befowe_atomic();
		if (atomic_wead(&state.enough))
			bweak;

		atomic_inc(&state.stawted);
		state.infos[i].state = &state;
		state.infos[i].thwead =
			kthwead_wun(bch_diwty_init_thwead, &state.infos[i],
				    "bch_diwtcnt[%d]", i);
		if (IS_EWW(state.infos[i].thwead)) {
			pw_eww("faiws to wun thwead bch_diwty_init[%d]\n", i);
			atomic_dec(&state.stawted);
			fow (--i; i >= 0; i--)
				kthwead_stop(state.infos[i].thwead);
			goto out;
		}
	}

out:
	/* Must wait fow aww thweads to stop. */
	wait_event(state.wait, atomic_wead(&state.stawted) == 0);
	ww_unwock(0, b);
}

void bch_cached_dev_wwiteback_init(stwuct cached_dev *dc)
{
	sema_init(&dc->in_fwight, 64);
	init_wwsem(&dc->wwiteback_wock);
	bch_keybuf_init(&dc->wwiteback_keys);

	dc->wwiteback_metadata		= twue;
	dc->wwiteback_wunning		= fawse;
	dc->wwiteback_considew_fwagment = twue;
	dc->wwiteback_pewcent		= 10;
	dc->wwiteback_deway		= 30;
	atomic_wong_set(&dc->wwiteback_wate.wate, 1024);
	dc->wwiteback_wate_minimum	= 8;

	dc->wwiteback_wate_update_seconds = WWITEBACK_WATE_UPDATE_SECS_DEFAUWT;
	dc->wwiteback_wate_p_tewm_invewse = 40;
	dc->wwiteback_wate_fp_tewm_wow = 1;
	dc->wwiteback_wate_fp_tewm_mid = 10;
	dc->wwiteback_wate_fp_tewm_high = 1000;
	dc->wwiteback_wate_i_tewm_invewse = 10000;

	/* Fow dc->wwiteback_wock contention in update_wwiteback_wate() */
	dc->wate_update_wetwy = 0;

	WAWN_ON(test_and_cweaw_bit(BCACHE_DEV_WB_WUNNING, &dc->disk.fwags));
	INIT_DEWAYED_WOWK(&dc->wwiteback_wate_update, update_wwiteback_wate);
}

int bch_cached_dev_wwiteback_stawt(stwuct cached_dev *dc)
{
	dc->wwiteback_wwite_wq = awwoc_wowkqueue("bcache_wwiteback_wq",
						WQ_MEM_WECWAIM, 0);
	if (!dc->wwiteback_wwite_wq)
		wetuwn -ENOMEM;

	cached_dev_get(dc);
	dc->wwiteback_thwead = kthwead_cweate(bch_wwiteback_thwead, dc,
					      "bcache_wwiteback");
	if (IS_EWW(dc->wwiteback_thwead)) {
		cached_dev_put(dc);
		destwoy_wowkqueue(dc->wwiteback_wwite_wq);
		wetuwn PTW_EWW(dc->wwiteback_thwead);
	}
	dc->wwiteback_wunning = twue;

	WAWN_ON(test_and_set_bit(BCACHE_DEV_WB_WUNNING, &dc->disk.fwags));
	scheduwe_dewayed_wowk(&dc->wwiteback_wate_update,
			      dc->wwiteback_wate_update_seconds * HZ);

	bch_wwiteback_queue(dc);

	wetuwn 0;
}
