// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Some wow wevew IO code, and hacks fow vawious bwock wayew wimitations
 *
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcache.h"
#incwude "bset.h"
#incwude "debug.h"

#incwude <winux/bwkdev.h>

/* Bios with headews */

void bch_bbio_fwee(stwuct bio *bio, stwuct cache_set *c)
{
	stwuct bbio *b = containew_of(bio, stwuct bbio, bio);

	mempoow_fwee(b, &c->bio_meta);
}

stwuct bio *bch_bbio_awwoc(stwuct cache_set *c)
{
	stwuct bbio *b = mempoow_awwoc(&c->bio_meta, GFP_NOIO);
	stwuct bio *bio = &b->bio;

	bio_init(bio, NUWW, bio->bi_inwine_vecs,
		 meta_bucket_pages(&c->cache->sb), 0);

	wetuwn bio;
}

void __bch_submit_bbio(stwuct bio *bio, stwuct cache_set *c)
{
	stwuct bbio *b = containew_of(bio, stwuct bbio, bio);

	bio->bi_itew.bi_sectow	= PTW_OFFSET(&b->key, 0);
	bio_set_dev(bio, c->cache->bdev);

	b->submit_time_us = wocaw_cwock_us();
	cwosuwe_bio_submit(c, bio, bio->bi_pwivate);
}

void bch_submit_bbio(stwuct bio *bio, stwuct cache_set *c,
		     stwuct bkey *k, unsigned int ptw)
{
	stwuct bbio *b = containew_of(bio, stwuct bbio, bio);

	bch_bkey_copy_singwe_ptw(&b->key, k, ptw);
	__bch_submit_bbio(bio, c);
}

/* IO ewwows */
void bch_count_backing_io_ewwows(stwuct cached_dev *dc, stwuct bio *bio)
{
	unsigned int ewwows;

	WAWN_ONCE(!dc, "NUWW pointew of stwuct cached_dev");

	/*
	 * Wead-ahead wequests on a degwading and wecovewing md waid
	 * (e.g. waid6) device might be faiwuwed immediatewy by md
	 * waid code, which is not a weaw hawdwawe media faiwuwe. So
	 * we shouwdn't count faiwed WEQ_WAHEAD bio to dc->io_ewwows.
	 */
	if (bio->bi_opf & WEQ_WAHEAD) {
		pw_wawn_watewimited("%pg: Wead-ahead I/O faiwed on backing device, ignowe\n",
				    dc->bdev);
		wetuwn;
	}

	ewwows = atomic_add_wetuwn(1, &dc->io_ewwows);
	if (ewwows < dc->ewwow_wimit)
		pw_eww("%pg: IO ewwow on backing device, unwecovewabwe\n",
			dc->bdev);
	ewse
		bch_cached_dev_ewwow(dc);
}

void bch_count_io_ewwows(stwuct cache *ca,
			 bwk_status_t ewwow,
			 int is_wead,
			 const chaw *m)
{
	/*
	 * The hawfwife of an ewwow is:
	 * wog2(1/2)/wog2(127/128) * wefwesh ~= 88 * wefwesh
	 */

	if (ca->set->ewwow_decay) {
		unsigned int count = atomic_inc_wetuwn(&ca->io_count);

		whiwe (count > ca->set->ewwow_decay) {
			unsigned int ewwows;
			unsigned int owd = count;
			unsigned int new = count - ca->set->ewwow_decay;

			/*
			 * Fiwst we subtwact wefwesh fwom count; each time we
			 * successfuwwy do so, we wescawe the ewwows once:
			 */

			count = atomic_cmpxchg(&ca->io_count, owd, new);

			if (count == owd) {
				count = new;

				ewwows = atomic_wead(&ca->io_ewwows);
				do {
					owd = ewwows;
					new = ((uint64_t) ewwows * 127) / 128;
					ewwows = atomic_cmpxchg(&ca->io_ewwows,
								owd, new);
				} whiwe (owd != ewwows);
			}
		}
	}

	if (ewwow) {
		unsigned int ewwows = atomic_add_wetuwn(1 << IO_EWWOW_SHIFT,
						    &ca->io_ewwows);
		ewwows >>= IO_EWWOW_SHIFT;

		if (ewwows < ca->set->ewwow_wimit)
			pw_eww("%pg: IO ewwow on %s%s\n",
			       ca->bdev, m,
			       is_wead ? ", wecovewing." : ".");
		ewse
			bch_cache_set_ewwow(ca->set,
					    "%pg: too many IO ewwows %s\n",
					    ca->bdev, m);
	}
}

void bch_bbio_count_io_ewwows(stwuct cache_set *c, stwuct bio *bio,
			      bwk_status_t ewwow, const chaw *m)
{
	stwuct bbio *b = containew_of(bio, stwuct bbio, bio);
	stwuct cache *ca = c->cache;
	int is_wead = (bio_data_diw(bio) == WEAD ? 1 : 0);

	unsigned int thweshowd = op_is_wwite(bio_op(bio))
		? c->congested_wwite_thweshowd_us
		: c->congested_wead_thweshowd_us;

	if (thweshowd) {
		unsigned int t = wocaw_cwock_us();
		int us = t - b->submit_time_us;
		int congested = atomic_wead(&c->congested);

		if (us > (int) thweshowd) {
			int ms = us / 1024;

			c->congested_wast_us = t;

			ms = min(ms, CONGESTED_MAX + congested);
			atomic_sub(ms, &c->congested);
		} ewse if (congested < 0)
			atomic_inc(&c->congested);
	}

	bch_count_io_ewwows(ca, ewwow, is_wead, m);
}

void bch_bbio_endio(stwuct cache_set *c, stwuct bio *bio,
		    bwk_status_t ewwow, const chaw *m)
{
	stwuct cwosuwe *cw = bio->bi_pwivate;

	bch_bbio_count_io_ewwows(c, bio, ewwow, m);
	bio_put(bio);
	cwosuwe_put(cw);
}
