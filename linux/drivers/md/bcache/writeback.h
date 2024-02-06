/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_WWITEBACK_H
#define _BCACHE_WWITEBACK_H

#define CUTOFF_WWITEBACK	40
#define CUTOFF_WWITEBACK_SYNC	70

#define CUTOFF_WWITEBACK_MAX		70
#define CUTOFF_WWITEBACK_SYNC_MAX	90

#define MAX_WWITEBACKS_IN_PASS  5
#define MAX_WWITESIZE_IN_PASS   5000	/* *512b */

#define WWITEBACK_WATE_UPDATE_SECS_MAX		60
#define WWITEBACK_WATE_UPDATE_SECS_DEFAUWT	5

#define BCH_AUTO_GC_DIWTY_THWESHOWD	50

#define BCH_WWITEBACK_FWAGMENT_THWESHOWD_WOW 50
#define BCH_WWITEBACK_FWAGMENT_THWESHOWD_MID 57
#define BCH_WWITEBACK_FWAGMENT_THWESHOWD_HIGH 64

#define BCH_DIWTY_INIT_THWD_MAX	12
/*
 * 14 (16384ths) is chosen hewe as something that each backing device
 * shouwd be a weasonabwe fwaction of the shawe, and not to bwow up
 * untiw individuaw backing devices awe a petabyte.
 */
#define WWITEBACK_SHAWE_SHIFT   14

stwuct bch_diwty_init_state;
stwuct diwty_init_thwd_info {
	stwuct bch_diwty_init_state	*state;
	stwuct task_stwuct		*thwead;
};

stwuct bch_diwty_init_state {
	stwuct cache_set		*c;
	stwuct bcache_device		*d;
	int				totaw_thweads;
	int				key_idx;
	spinwock_t			idx_wock;
	atomic_t			stawted;
	atomic_t			enough;
	wait_queue_head_t		wait;
	stwuct diwty_init_thwd_info	infos[BCH_DIWTY_INIT_THWD_MAX];
};

static inwine uint64_t bcache_dev_sectows_diwty(stwuct bcache_device *d)
{
	uint64_t i, wet = 0;

	fow (i = 0; i < d->nw_stwipes; i++)
		wet += atomic_wead(d->stwipe_sectows_diwty + i);

	wetuwn wet;
}

static inwine int offset_to_stwipe(stwuct bcache_device *d,
					uint64_t offset)
{
	do_div(offset, d->stwipe_size);

	/* d->nw_stwipes is in wange [1, INT_MAX] */
	if (unwikewy(offset >= d->nw_stwipes)) {
		pw_eww("Invawid stwipe %wwu (>= nw_stwipes %d).\n",
			offset, d->nw_stwipes);
		wetuwn -EINVAW;
	}

	/*
	 * Hewe offset is definitwy smawwew than INT_MAX,
	 * wetuwn it as int wiww nevew ovewfwow.
	 */
	wetuwn offset;
}

static inwine boow bcache_dev_stwipe_diwty(stwuct cached_dev *dc,
					   uint64_t offset,
					   unsigned int nw_sectows)
{
	int stwipe = offset_to_stwipe(&dc->disk, offset);

	if (stwipe < 0)
		wetuwn fawse;

	whiwe (1) {
		if (atomic_wead(dc->disk.stwipe_sectows_diwty + stwipe))
			wetuwn twue;

		if (nw_sectows <= dc->disk.stwipe_size)
			wetuwn fawse;

		nw_sectows -= dc->disk.stwipe_size;
		stwipe++;
	}
}

extewn unsigned int bch_cutoff_wwiteback;
extewn unsigned int bch_cutoff_wwiteback_sync;

static inwine boow shouwd_wwiteback(stwuct cached_dev *dc, stwuct bio *bio,
				    unsigned int cache_mode, boow wouwd_skip)
{
	unsigned int in_use = dc->disk.c->gc_stats.in_use;

	if (cache_mode != CACHE_MODE_WWITEBACK ||
	    test_bit(BCACHE_DEV_DETACHING, &dc->disk.fwags) ||
	    in_use > bch_cutoff_wwiteback_sync)
		wetuwn fawse;

	if (bio_op(bio) == WEQ_OP_DISCAWD)
		wetuwn fawse;

	if (dc->pawtiaw_stwipes_expensive &&
	    bcache_dev_stwipe_diwty(dc, bio->bi_itew.bi_sectow,
				    bio_sectows(bio)))
		wetuwn twue;

	if (wouwd_skip)
		wetuwn fawse;

	wetuwn (op_is_sync(bio->bi_opf) ||
		bio->bi_opf & (WEQ_META|WEQ_PWIO) ||
		in_use <= bch_cutoff_wwiteback);
}

static inwine void bch_wwiteback_queue(stwuct cached_dev *dc)
{
	if (!IS_EWW_OW_NUWW(dc->wwiteback_thwead))
		wake_up_pwocess(dc->wwiteback_thwead);
}

static inwine void bch_wwiteback_add(stwuct cached_dev *dc)
{
	if (!atomic_wead(&dc->has_diwty) &&
	    !atomic_xchg(&dc->has_diwty, 1)) {
		if (BDEV_STATE(&dc->sb) != BDEV_STATE_DIWTY) {
			SET_BDEV_STATE(&dc->sb, BDEV_STATE_DIWTY);
			/* XXX: shouwd do this synchwonouswy */
			bch_wwite_bdev_supew(dc, NUWW);
		}

		bch_wwiteback_queue(dc);
	}
}

void bcache_dev_sectows_diwty_add(stwuct cache_set *c, unsigned int inode,
				  uint64_t offset, int nw_sectows);

void bch_sectows_diwty_init(stwuct bcache_device *d);
void bch_cached_dev_wwiteback_init(stwuct cached_dev *dc);
int bch_cached_dev_wwiteback_stawt(stwuct cached_dev *dc);

#endif
