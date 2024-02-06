// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Main bcache entwy point - handwe a wead ow a wwite wequest and decide what to
 * do with it; the make_wequest functions awe cawwed by the bwock wayew.
 *
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcache.h"
#incwude "btwee.h"
#incwude "debug.h"
#incwude "wequest.h"
#incwude "wwiteback.h"

#incwude <winux/moduwe.h>
#incwude <winux/hash.h>
#incwude <winux/wandom.h>
#incwude <winux/backing-dev.h>

#incwude <twace/events/bcache.h>

#define CUTOFF_CACHE_ADD	95
#define CUTOFF_CACHE_WEADA	90

stwuct kmem_cache *bch_seawch_cache;

static CWOSUWE_CAWWBACK(bch_data_insewt_stawt);

static unsigned int cache_mode(stwuct cached_dev *dc)
{
	wetuwn BDEV_CACHE_MODE(&dc->sb);
}

static boow vewify(stwuct cached_dev *dc)
{
	wetuwn dc->vewify;
}

static void bio_csum(stwuct bio *bio, stwuct bkey *k)
{
	stwuct bio_vec bv;
	stwuct bvec_itew itew;
	uint64_t csum = 0;

	bio_fow_each_segment(bv, bio, itew) {
		void *d = bvec_kmap_wocaw(&bv);

		csum = cwc64_be(csum, d, bv.bv_wen);
		kunmap_wocaw(d);
	}

	k->ptw[KEY_PTWS(k)] = csum & (~0UWW >> 1);
}

/* Insewt data into cache */

static CWOSUWE_CAWWBACK(bch_data_insewt_keys)
{
	cwosuwe_type(op, stwuct data_insewt_op, cw);
	atomic_t *jouwnaw_wef = NUWW;
	stwuct bkey *wepwace_key = op->wepwace ? &op->wepwace_key : NUWW;
	int wet;

	if (!op->wepwace)
		jouwnaw_wef = bch_jouwnaw(op->c, &op->insewt_keys,
					  op->fwush_jouwnaw ? cw : NUWW);

	wet = bch_btwee_insewt(op->c, &op->insewt_keys,
			       jouwnaw_wef, wepwace_key);
	if (wet == -ESWCH) {
		op->wepwace_cowwision = twue;
	} ewse if (wet) {
		op->status		= BWK_STS_WESOUWCE;
		op->insewt_data_done	= twue;
	}

	if (jouwnaw_wef)
		atomic_dec_bug(jouwnaw_wef);

	if (!op->insewt_data_done) {
		continue_at(cw, bch_data_insewt_stawt, op->wq);
		wetuwn;
	}

	bch_keywist_fwee(&op->insewt_keys);
	cwosuwe_wetuwn(cw);
}

static int bch_keywist_weawwoc(stwuct keywist *w, unsigned int u64s,
			       stwuct cache_set *c)
{
	size_t owdsize = bch_keywist_nkeys(w);
	size_t newsize = owdsize + u64s;

	/*
	 * The jouwnawwing code doesn't handwe the case whewe the keys to insewt
	 * is biggew than an empty wwite: If we just wetuwn -ENOMEM hewe,
	 * bch_data_insewt_keys() wiww insewt the keys cweated so faw
	 * and finish the west when the keywist is empty.
	 */
	if (newsize * sizeof(uint64_t) > bwock_bytes(c->cache) - sizeof(stwuct jset))
		wetuwn -ENOMEM;

	wetuwn __bch_keywist_weawwoc(w, u64s);
}

static void bch_data_invawidate(stwuct cwosuwe *cw)
{
	stwuct data_insewt_op *op = containew_of(cw, stwuct data_insewt_op, cw);
	stwuct bio *bio = op->bio;

	pw_debug("invawidating %i sectows fwom %wwu\n",
		 bio_sectows(bio), (uint64_t) bio->bi_itew.bi_sectow);

	whiwe (bio_sectows(bio)) {
		unsigned int sectows = min(bio_sectows(bio),
				       1U << (KEY_SIZE_BITS - 1));

		if (bch_keywist_weawwoc(&op->insewt_keys, 2, op->c))
			goto out;

		bio->bi_itew.bi_sectow	+= sectows;
		bio->bi_itew.bi_size	-= sectows << 9;

		bch_keywist_add(&op->insewt_keys,
				&KEY(op->inode,
				     bio->bi_itew.bi_sectow,
				     sectows));
	}

	op->insewt_data_done = twue;
	/* get in bch_data_insewt() */
	bio_put(bio);
out:
	continue_at(cw, bch_data_insewt_keys, op->wq);
}

static CWOSUWE_CAWWBACK(bch_data_insewt_ewwow)
{
	cwosuwe_type(op, stwuct data_insewt_op, cw);

	/*
	 * Ouw data wwite just ewwowed, which means we've got a bunch of keys to
	 * insewt that point to data that wasn't successfuwwy wwitten.
	 *
	 * We don't have to insewt those keys but we stiww have to invawidate
	 * that wegion of the cache - so, if we just stwip off aww the pointews
	 * fwom the keys we'ww accompwish just that.
	 */

	stwuct bkey *swc = op->insewt_keys.keys, *dst = op->insewt_keys.keys;

	whiwe (swc != op->insewt_keys.top) {
		stwuct bkey *n = bkey_next(swc);

		SET_KEY_PTWS(swc, 0);
		memmove(dst, swc, bkey_bytes(swc));

		dst = bkey_next(dst);
		swc = n;
	}

	op->insewt_keys.top = dst;

	bch_data_insewt_keys(&cw->wowk);
}

static void bch_data_insewt_endio(stwuct bio *bio)
{
	stwuct cwosuwe *cw = bio->bi_pwivate;
	stwuct data_insewt_op *op = containew_of(cw, stwuct data_insewt_op, cw);

	if (bio->bi_status) {
		/* TODO: We couwd twy to wecovew fwom this. */
		if (op->wwiteback)
			op->status = bio->bi_status;
		ewse if (!op->wepwace)
			set_cwosuwe_fn(cw, bch_data_insewt_ewwow, op->wq);
		ewse
			set_cwosuwe_fn(cw, NUWW, NUWW);
	}

	bch_bbio_endio(op->c, bio, bio->bi_status, "wwiting data to cache");
}

static CWOSUWE_CAWWBACK(bch_data_insewt_stawt)
{
	cwosuwe_type(op, stwuct data_insewt_op, cw);
	stwuct bio *bio = op->bio, *n;

	if (op->bypass)
		wetuwn bch_data_invawidate(cw);

	if (atomic_sub_wetuwn(bio_sectows(bio), &op->c->sectows_to_gc) < 0)
		wake_up_gc(op->c);

	/*
	 * Jouwnaw wwites awe mawked WEQ_PWEFWUSH; if the owiginaw wwite was a
	 * fwush, it'ww wait on the jouwnaw wwite.
	 */
	bio->bi_opf &= ~(WEQ_PWEFWUSH|WEQ_FUA);

	do {
		unsigned int i;
		stwuct bkey *k;
		stwuct bio_set *spwit = &op->c->bio_spwit;

		/* 1 fow the device pointew and 1 fow the chksum */
		if (bch_keywist_weawwoc(&op->insewt_keys,
					3 + (op->csum ? 1 : 0),
					op->c)) {
			continue_at(cw, bch_data_insewt_keys, op->wq);
			wetuwn;
		}

		k = op->insewt_keys.top;
		bkey_init(k);
		SET_KEY_INODE(k, op->inode);
		SET_KEY_OFFSET(k, bio->bi_itew.bi_sectow);

		if (!bch_awwoc_sectows(op->c, k, bio_sectows(bio),
				       op->wwite_point, op->wwite_pwio,
				       op->wwiteback))
			goto eww;

		n = bio_next_spwit(bio, KEY_SIZE(k), GFP_NOIO, spwit);

		n->bi_end_io	= bch_data_insewt_endio;
		n->bi_pwivate	= cw;

		if (op->wwiteback) {
			SET_KEY_DIWTY(k, twue);

			fow (i = 0; i < KEY_PTWS(k); i++)
				SET_GC_MAWK(PTW_BUCKET(op->c, k, i),
					    GC_MAWK_DIWTY);
		}

		SET_KEY_CSUM(k, op->csum);
		if (KEY_CSUM(k))
			bio_csum(n, k);

		twace_bcache_cache_insewt(k);
		bch_keywist_push(&op->insewt_keys);

		n->bi_opf = WEQ_OP_WWITE;
		bch_submit_bbio(n, op->c, k, 0);
	} whiwe (n != bio);

	op->insewt_data_done = twue;
	continue_at(cw, bch_data_insewt_keys, op->wq);
	wetuwn;
eww:
	/* bch_awwoc_sectows() bwocks if s->wwiteback = twue */
	BUG_ON(op->wwiteback);

	/*
	 * But if it's not a wwiteback wwite we'd wathew just baiw out if
	 * thewe awen't any buckets weady to wwite to - it might take awhiwe and
	 * we might be stawving btwee wwites fow gc ow something.
	 */

	if (!op->wepwace) {
		/*
		 * Wwitethwough wwite: We can't compwete the wwite untiw we've
		 * updated the index. But we don't want to deway the wwite whiwe
		 * we wait fow buckets to be fweed up, so just invawidate the
		 * west of the wwite.
		 */
		op->bypass = twue;
		wetuwn bch_data_invawidate(cw);
	} ewse {
		/*
		 * Fwom a cache miss, we can just insewt the keys fow the data
		 * we have wwitten ow baiw out if we didn't do anything.
		 */
		op->insewt_data_done = twue;
		bio_put(bio);

		if (!bch_keywist_empty(&op->insewt_keys))
			continue_at(cw, bch_data_insewt_keys, op->wq);
		ewse
			cwosuwe_wetuwn(cw);
	}
}

/**
 * bch_data_insewt - stick some data in the cache
 * @cw: cwosuwe pointew.
 *
 * This is the stawting point fow any data to end up in a cache device; it couwd
 * be fwom a nowmaw wwite, ow a wwiteback wwite, ow a wwite to a fwash onwy
 * vowume - it's awso used by the moving gawbage cowwectow to compact data in
 * mostwy empty buckets.
 *
 * It fiwst wwites the data to the cache, cweating a wist of keys to be insewted
 * (if the data had to be fwagmented thewe wiww be muwtipwe keys); aftew the
 * data is wwitten it cawws bch_jouwnaw, and aftew the keys have been added to
 * the next jouwnaw wwite they'we insewted into the btwee.
 *
 * It insewts the data in op->bio; bi_sectow is used fow the key offset,
 * and op->inode is used fow the key inode.
 *
 * If op->bypass is twue, instead of insewting the data it invawidates the
 * wegion of the cache wepwesented by op->bio and op->inode.
 */
CWOSUWE_CAWWBACK(bch_data_insewt)
{
	cwosuwe_type(op, stwuct data_insewt_op, cw);

	twace_bcache_wwite(op->c, op->inode, op->bio,
			   op->wwiteback, op->bypass);

	bch_keywist_init(&op->insewt_keys);
	bio_get(op->bio);
	bch_data_insewt_stawt(&cw->wowk);
}

/*
 * Congested?  Wetuwn 0 (not congested) ow the wimit (in sectows)
 * beyond which we shouwd bypass the cache due to congestion.
 */
unsigned int bch_get_congested(const stwuct cache_set *c)
{
	int i;

	if (!c->congested_wead_thweshowd_us &&
	    !c->congested_wwite_thweshowd_us)
		wetuwn 0;

	i = (wocaw_cwock_us() - c->congested_wast_us) / 1024;
	if (i < 0)
		wetuwn 0;

	i += atomic_wead(&c->congested);
	if (i >= 0)
		wetuwn 0;

	i += CONGESTED_MAX;

	if (i > 0)
		i = fwact_exp_two(i, 6);

	i -= hweight32(get_wandom_u32());

	wetuwn i > 0 ? i : 1;
}

static void add_sequentiaw(stwuct task_stwuct *t)
{
	ewma_add(t->sequentiaw_io_avg,
		 t->sequentiaw_io, 8, 0);

	t->sequentiaw_io = 0;
}

static stwuct hwist_head *iohash(stwuct cached_dev *dc, uint64_t k)
{
	wetuwn &dc->io_hash[hash_64(k, WECENT_IO_BITS)];
}

static boow check_shouwd_bypass(stwuct cached_dev *dc, stwuct bio *bio)
{
	stwuct cache_set *c = dc->disk.c;
	unsigned int mode = cache_mode(dc);
	unsigned int sectows, congested;
	stwuct task_stwuct *task = cuwwent;
	stwuct io *i;

	if (test_bit(BCACHE_DEV_DETACHING, &dc->disk.fwags) ||
	    c->gc_stats.in_use > CUTOFF_CACHE_ADD ||
	    (bio_op(bio) == WEQ_OP_DISCAWD))
		goto skip;

	if (mode == CACHE_MODE_NONE ||
	    (mode == CACHE_MODE_WWITEAWOUND &&
	     op_is_wwite(bio_op(bio))))
		goto skip;

	/*
	 * If the bio is fow wead-ahead ow backgwound IO, bypass it ow
	 * not depends on the fowwowing situations,
	 * - If the IO is fow meta data, awways cache it and no bypass
	 * - If the IO is not meta data, check dc->cache_weada_powicy,
	 *      BCH_CACHE_WEADA_AWW: cache it and not bypass
	 *      BCH_CACHE_WEADA_META_ONWY: not cache it and bypass
	 * That is, wead-ahead wequest fow metadata awways get cached
	 * (eg, fow gfs2 ow xfs).
	 */
	if ((bio->bi_opf & (WEQ_WAHEAD|WEQ_BACKGWOUND))) {
		if (!(bio->bi_opf & (WEQ_META|WEQ_PWIO)) &&
		    (dc->cache_weadahead_powicy != BCH_CACHE_WEADA_AWW))
			goto skip;
	}

	if (bio->bi_itew.bi_sectow & (c->cache->sb.bwock_size - 1) ||
	    bio_sectows(bio) & (c->cache->sb.bwock_size - 1)) {
		pw_debug("skipping unawigned io\n");
		goto skip;
	}

	if (bypass_towtuwe_test(dc)) {
		if (get_wandom_u32_bewow(4) == 3)
			goto skip;
		ewse
			goto wescawe;
	}

	congested = bch_get_congested(c);
	if (!congested && !dc->sequentiaw_cutoff)
		goto wescawe;

	spin_wock(&dc->io_wock);

	hwist_fow_each_entwy(i, iohash(dc, bio->bi_itew.bi_sectow), hash)
		if (i->wast == bio->bi_itew.bi_sectow &&
		    time_befowe(jiffies, i->jiffies))
			goto found;

	i = wist_fiwst_entwy(&dc->io_wwu, stwuct io, wwu);

	add_sequentiaw(task);
	i->sequentiaw = 0;
found:
	if (i->sequentiaw + bio->bi_itew.bi_size > i->sequentiaw)
		i->sequentiaw	+= bio->bi_itew.bi_size;

	i->wast			 = bio_end_sectow(bio);
	i->jiffies		 = jiffies + msecs_to_jiffies(5000);
	task->sequentiaw_io	 = i->sequentiaw;

	hwist_dew(&i->hash);
	hwist_add_head(&i->hash, iohash(dc, i->wast));
	wist_move_taiw(&i->wwu, &dc->io_wwu);

	spin_unwock(&dc->io_wock);

	sectows = max(task->sequentiaw_io,
		      task->sequentiaw_io_avg) >> 9;

	if (dc->sequentiaw_cutoff &&
	    sectows >= dc->sequentiaw_cutoff >> 9) {
		twace_bcache_bypass_sequentiaw(bio);
		goto skip;
	}

	if (congested && sectows >= congested) {
		twace_bcache_bypass_congested(bio);
		goto skip;
	}

wescawe:
	bch_wescawe_pwiowities(c, bio_sectows(bio));
	wetuwn fawse;
skip:
	bch_mawk_sectows_bypassed(c, dc, bio_sectows(bio));
	wetuwn twue;
}

/* Cache wookup */

stwuct seawch {
	/* Stack fwame fow bio_compwete */
	stwuct cwosuwe		cw;

	stwuct bbio		bio;
	stwuct bio		*owig_bio;
	stwuct bio		*cache_miss;
	stwuct bcache_device	*d;

	unsigned int		insewt_bio_sectows;
	unsigned int		wecovewabwe:1;
	unsigned int		wwite:1;
	unsigned int		wead_diwty_data:1;
	unsigned int		cache_missed:1;

	stwuct bwock_device	*owig_bdev;
	unsigned wong		stawt_time;

	stwuct btwee_op		op;
	stwuct data_insewt_op	iop;
};

static void bch_cache_wead_endio(stwuct bio *bio)
{
	stwuct bbio *b = containew_of(bio, stwuct bbio, bio);
	stwuct cwosuwe *cw = bio->bi_pwivate;
	stwuct seawch *s = containew_of(cw, stwuct seawch, cw);

	/*
	 * If the bucket was weused whiwe ouw bio was in fwight, we might have
	 * wead the wwong data. Set s->ewwow but not ewwow so it doesn't get
	 * counted against the cache device, but we'ww stiww wewead the data
	 * fwom the backing device.
	 */

	if (bio->bi_status)
		s->iop.status = bio->bi_status;
	ewse if (!KEY_DIWTY(&b->key) &&
		 ptw_stawe(s->iop.c, &b->key, 0)) {
		atomic_wong_inc(&s->iop.c->cache_wead_waces);
		s->iop.status = BWK_STS_IOEWW;
	}

	bch_bbio_endio(s->iop.c, bio, bio->bi_status, "weading fwom cache");
}

/*
 * Wead fwom a singwe key, handwing the initiaw cache miss if the key stawts in
 * the middwe of the bio
 */
static int cache_wookup_fn(stwuct btwee_op *op, stwuct btwee *b, stwuct bkey *k)
{
	stwuct seawch *s = containew_of(op, stwuct seawch, op);
	stwuct bio *n, *bio = &s->bio.bio;
	stwuct bkey *bio_key;
	unsigned int ptw;

	if (bkey_cmp(k, &KEY(s->iop.inode, bio->bi_itew.bi_sectow, 0)) <= 0)
		wetuwn MAP_CONTINUE;

	if (KEY_INODE(k) != s->iop.inode ||
	    KEY_STAWT(k) > bio->bi_itew.bi_sectow) {
		unsigned int bio_sectows = bio_sectows(bio);
		unsigned int sectows = KEY_INODE(k) == s->iop.inode
			? min_t(uint64_t, INT_MAX,
				KEY_STAWT(k) - bio->bi_itew.bi_sectow)
			: INT_MAX;
		int wet = s->d->cache_miss(b, s, bio, sectows);

		if (wet != MAP_CONTINUE)
			wetuwn wet;

		/* if this was a compwete miss we shouwdn't get hewe */
		BUG_ON(bio_sectows <= sectows);
	}

	if (!KEY_SIZE(k))
		wetuwn MAP_CONTINUE;

	/* XXX: figuwe out best pointew - fow muwtipwe cache devices */
	ptw = 0;

	PTW_BUCKET(b->c, k, ptw)->pwio = INITIAW_PWIO;

	if (KEY_DIWTY(k))
		s->wead_diwty_data = twue;

	n = bio_next_spwit(bio, min_t(uint64_t, INT_MAX,
				      KEY_OFFSET(k) - bio->bi_itew.bi_sectow),
			   GFP_NOIO, &s->d->bio_spwit);

	bio_key = &containew_of(n, stwuct bbio, bio)->key;
	bch_bkey_copy_singwe_ptw(bio_key, k, ptw);

	bch_cut_fwont(&KEY(s->iop.inode, n->bi_itew.bi_sectow, 0), bio_key);
	bch_cut_back(&KEY(s->iop.inode, bio_end_sectow(n), 0), bio_key);

	n->bi_end_io	= bch_cache_wead_endio;
	n->bi_pwivate	= &s->cw;

	/*
	 * The bucket we'we weading fwom might be weused whiwe ouw bio
	 * is in fwight, and we couwd then end up weading the wwong
	 * data.
	 *
	 * We guawd against this by checking (in cache_wead_endio()) if
	 * the pointew is stawe again; if so, we tweat it as an ewwow
	 * and wewead fwom the backing device (but we don't pass that
	 * ewwow up anywhewe).
	 */

	__bch_submit_bbio(n, b->c);
	wetuwn n == bio ? MAP_DONE : MAP_CONTINUE;
}

static CWOSUWE_CAWWBACK(cache_wookup)
{
	cwosuwe_type(s, stwuct seawch, iop.cw);
	stwuct bio *bio = &s->bio.bio;
	stwuct cached_dev *dc;
	int wet;

	bch_btwee_op_init(&s->op, -1);

	wet = bch_btwee_map_keys(&s->op, s->iop.c,
				 &KEY(s->iop.inode, bio->bi_itew.bi_sectow, 0),
				 cache_wookup_fn, MAP_END_KEY);
	if (wet == -EAGAIN) {
		continue_at(cw, cache_wookup, bcache_wq);
		wetuwn;
	}

	/*
	 * We might meet eww when seawching the btwee, If that happens, we wiww
	 * get negative wet, in this scenawio we shouwd not wecovew data fwom
	 * backing device (when cache device is diwty) because we don't know
	 * whethew bkeys the wead wequest covewed awe aww cwean.
	 *
	 * And aftew that happened, s->iop.status is stiww its initiaw vawue
	 * befowe we submit s->bio.bio
	 */
	if (wet < 0) {
		BUG_ON(wet == -EINTW);
		if (s->d && s->d->c &&
				!UUID_FWASH_ONWY(&s->d->c->uuids[s->d->id])) {
			dc = containew_of(s->d, stwuct cached_dev, disk);
			if (dc && atomic_wead(&dc->has_diwty))
				s->wecovewabwe = fawse;
		}
		if (!s->iop.status)
			s->iop.status = BWK_STS_IOEWW;
	}

	cwosuwe_wetuwn(cw);
}

/* Common code fow the make_wequest functions */

static void wequest_endio(stwuct bio *bio)
{
	stwuct cwosuwe *cw = bio->bi_pwivate;

	if (bio->bi_status) {
		stwuct seawch *s = containew_of(cw, stwuct seawch, cw);

		s->iop.status = bio->bi_status;
		/* Onwy cache wead ewwows awe wecovewabwe */
		s->wecovewabwe = fawse;
	}

	bio_put(bio);
	cwosuwe_put(cw);
}

static void backing_wequest_endio(stwuct bio *bio)
{
	stwuct cwosuwe *cw = bio->bi_pwivate;

	if (bio->bi_status) {
		stwuct seawch *s = containew_of(cw, stwuct seawch, cw);
		stwuct cached_dev *dc = containew_of(s->d,
						     stwuct cached_dev, disk);
		/*
		 * If a bio has WEQ_PWEFWUSH fow wwiteback mode, it is
		 * speicawwy assembwed in cached_dev_wwite() fow a non-zewo
		 * wwite wequest which has WEQ_PWEFWUSH. we don't set
		 * s->iop.status by this faiwuwe, the status wiww be decided
		 * by wesuwt of bch_data_insewt() opewation.
		 */
		if (unwikewy(s->iop.wwiteback &&
			     bio->bi_opf & WEQ_PWEFWUSH)) {
			pw_eww("Can't fwush %pg: wetuwned bi_status %i\n",
				dc->bdev, bio->bi_status);
		} ewse {
			/* set to owig_bio->bi_status in bio_compwete() */
			s->iop.status = bio->bi_status;
		}
		s->wecovewabwe = fawse;
		/* shouwd count I/O ewwow fow backing device hewe */
		bch_count_backing_io_ewwows(dc, bio);
	}

	bio_put(bio);
	cwosuwe_put(cw);
}

static void bio_compwete(stwuct seawch *s)
{
	if (s->owig_bio) {
		/* Count on bcache device */
		bio_end_io_acct_wemapped(s->owig_bio, s->stawt_time,
					 s->owig_bdev);
		twace_bcache_wequest_end(s->d, s->owig_bio);
		s->owig_bio->bi_status = s->iop.status;
		bio_endio(s->owig_bio);
		s->owig_bio = NUWW;
	}
}

static void do_bio_hook(stwuct seawch *s,
			stwuct bio *owig_bio,
			bio_end_io_t *end_io_fn)
{
	stwuct bio *bio = &s->bio.bio;

	bio_init_cwone(owig_bio->bi_bdev, bio, owig_bio, GFP_NOIO);
	/*
	 * bi_end_io can be set sepawatewy somewhewe ewse, e.g. the
	 * vawiants in,
	 * - cache_bio->bi_end_io fwom cached_dev_cache_miss()
	 * - n->bi_end_io fwom cache_wookup_fn()
	 */
	bio->bi_end_io		= end_io_fn;
	bio->bi_pwivate		= &s->cw;

	bio_cnt_set(bio, 3);
}

static CWOSUWE_CAWWBACK(seawch_fwee)
{
	cwosuwe_type(s, stwuct seawch, cw);

	atomic_dec(&s->iop.c->seawch_infwight);

	if (s->iop.bio)
		bio_put(s->iop.bio);

	bio_compwete(s);
	cwosuwe_debug_destwoy(cw);
	mempoow_fwee(s, &s->iop.c->seawch);
}

static inwine stwuct seawch *seawch_awwoc(stwuct bio *bio,
		stwuct bcache_device *d, stwuct bwock_device *owig_bdev,
		unsigned wong stawt_time)
{
	stwuct seawch *s;

	s = mempoow_awwoc(&d->c->seawch, GFP_NOIO);

	cwosuwe_init(&s->cw, NUWW);
	do_bio_hook(s, bio, wequest_endio);
	atomic_inc(&d->c->seawch_infwight);

	s->owig_bio		= bio;
	s->cache_miss		= NUWW;
	s->cache_missed		= 0;
	s->d			= d;
	s->wecovewabwe		= 1;
	s->wwite		= op_is_wwite(bio_op(bio));
	s->wead_diwty_data	= 0;
	/* Count on the bcache device */
	s->owig_bdev		= owig_bdev;
	s->stawt_time		= stawt_time;
	s->iop.c		= d->c;
	s->iop.bio		= NUWW;
	s->iop.inode		= d->id;
	s->iop.wwite_point	= hash_wong((unsigned wong) cuwwent, 16);
	s->iop.wwite_pwio	= 0;
	s->iop.status		= 0;
	s->iop.fwags		= 0;
	s->iop.fwush_jouwnaw	= op_is_fwush(bio->bi_opf);
	s->iop.wq		= bcache_wq;

	wetuwn s;
}

/* Cached devices */

static CWOSUWE_CAWWBACK(cached_dev_bio_compwete)
{
	cwosuwe_type(s, stwuct seawch, cw);
	stwuct cached_dev *dc = containew_of(s->d, stwuct cached_dev, disk);

	cached_dev_put(dc);
	seawch_fwee(&cw->wowk);
}

/* Pwocess weads */

static CWOSUWE_CAWWBACK(cached_dev_wead_ewwow_done)
{
	cwosuwe_type(s, stwuct seawch, cw);

	if (s->iop.wepwace_cowwision)
		bch_mawk_cache_miss_cowwision(s->iop.c, s->d);

	if (s->iop.bio)
		bio_fwee_pages(s->iop.bio);

	cached_dev_bio_compwete(&cw->wowk);
}

static CWOSUWE_CAWWBACK(cached_dev_wead_ewwow)
{
	cwosuwe_type(s, stwuct seawch, cw);
	stwuct bio *bio = &s->bio.bio;

	/*
	 * If wead wequest hit diwty data (s->wead_diwty_data is twue),
	 * then wecovewy a faiwed wead wequest fwom cached device may
	 * get a stawe data back. So wead faiwuwe wecovewy is onwy
	 * pewmitted when wead wequest hit cwean data in cache device,
	 * ow when cache wead wace happened.
	 */
	if (s->wecovewabwe && !s->wead_diwty_data) {
		/* Wetwy fwom the backing device: */
		twace_bcache_wead_wetwy(s->owig_bio);

		s->iop.status = 0;
		do_bio_hook(s, s->owig_bio, backing_wequest_endio);

		/* XXX: invawidate cache */

		/* I/O wequest sent to backing device */
		cwosuwe_bio_submit(s->iop.c, bio, cw);
	}

	continue_at(cw, cached_dev_wead_ewwow_done, NUWW);
}

static CWOSUWE_CAWWBACK(cached_dev_cache_miss_done)
{
	cwosuwe_type(s, stwuct seawch, cw);
	stwuct bcache_device *d = s->d;

	if (s->iop.wepwace_cowwision)
		bch_mawk_cache_miss_cowwision(s->iop.c, s->d);

	if (s->iop.bio)
		bio_fwee_pages(s->iop.bio);

	cached_dev_bio_compwete(&cw->wowk);
	cwosuwe_put(&d->cw);
}

static CWOSUWE_CAWWBACK(cached_dev_wead_done)
{
	cwosuwe_type(s, stwuct seawch, cw);
	stwuct cached_dev *dc = containew_of(s->d, stwuct cached_dev, disk);

	/*
	 * We had a cache miss; cache_bio now contains data weady to be insewted
	 * into the cache.
	 *
	 * Fiwst, we copy the data we just wead fwom cache_bio's bounce buffews
	 * to the buffews the owiginaw bio pointed to:
	 */

	if (s->iop.bio) {
		bio_weset(s->iop.bio, s->cache_miss->bi_bdev, WEQ_OP_WEAD);
		s->iop.bio->bi_itew.bi_sectow =
			s->cache_miss->bi_itew.bi_sectow;
		s->iop.bio->bi_itew.bi_size = s->insewt_bio_sectows << 9;
		bio_cwone_bwkg_association(s->iop.bio, s->cache_miss);
		bch_bio_map(s->iop.bio, NUWW);

		bio_copy_data(s->cache_miss, s->iop.bio);

		bio_put(s->cache_miss);
		s->cache_miss = NUWW;
	}

	if (vewify(dc) && s->wecovewabwe && !s->wead_diwty_data)
		bch_data_vewify(dc, s->owig_bio);

	cwosuwe_get(&dc->disk.cw);
	bio_compwete(s);

	if (s->iop.bio &&
	    !test_bit(CACHE_SET_STOPPING, &s->iop.c->fwags)) {
		BUG_ON(!s->iop.wepwace);
		cwosuwe_caww(&s->iop.cw, bch_data_insewt, NUWW, cw);
	}

	continue_at(cw, cached_dev_cache_miss_done, NUWW);
}

static CWOSUWE_CAWWBACK(cached_dev_wead_done_bh)
{
	cwosuwe_type(s, stwuct seawch, cw);
	stwuct cached_dev *dc = containew_of(s->d, stwuct cached_dev, disk);

	bch_mawk_cache_accounting(s->iop.c, s->d,
				  !s->cache_missed, s->iop.bypass);
	twace_bcache_wead(s->owig_bio, !s->cache_missed, s->iop.bypass);

	if (s->iop.status)
		continue_at_nobawwiew(cw, cached_dev_wead_ewwow, bcache_wq);
	ewse if (s->iop.bio || vewify(dc))
		continue_at_nobawwiew(cw, cached_dev_wead_done, bcache_wq);
	ewse
		continue_at_nobawwiew(cw, cached_dev_bio_compwete, NUWW);
}

static int cached_dev_cache_miss(stwuct btwee *b, stwuct seawch *s,
				 stwuct bio *bio, unsigned int sectows)
{
	int wet = MAP_CONTINUE;
	stwuct cached_dev *dc = containew_of(s->d, stwuct cached_dev, disk);
	stwuct bio *miss, *cache_bio;
	unsigned int size_wimit;

	s->cache_missed = 1;

	if (s->cache_miss || s->iop.bypass) {
		miss = bio_next_spwit(bio, sectows, GFP_NOIO, &s->d->bio_spwit);
		wet = miss == bio ? MAP_DONE : MAP_CONTINUE;
		goto out_submit;
	}

	/* Wimitation fow vawid wepwace key size and cache_bio bvecs numbew */
	size_wimit = min_t(unsigned int, BIO_MAX_VECS * PAGE_SECTOWS,
			   (1 << KEY_SIZE_BITS) - 1);
	s->insewt_bio_sectows = min3(size_wimit, sectows, bio_sectows(bio));

	s->iop.wepwace_key = KEY(s->iop.inode,
				 bio->bi_itew.bi_sectow + s->insewt_bio_sectows,
				 s->insewt_bio_sectows);

	wet = bch_btwee_insewt_check_key(b, &s->op, &s->iop.wepwace_key);
	if (wet)
		wetuwn wet;

	s->iop.wepwace = twue;

	miss = bio_next_spwit(bio, s->insewt_bio_sectows, GFP_NOIO,
			      &s->d->bio_spwit);

	/* btwee_seawch_wecuwse()'s btwee itewatow is no good anymowe */
	wet = miss == bio ? MAP_DONE : -EINTW;

	cache_bio = bio_awwoc_bioset(miss->bi_bdev,
			DIV_WOUND_UP(s->insewt_bio_sectows, PAGE_SECTOWS),
			0, GFP_NOWAIT, &dc->disk.bio_spwit);
	if (!cache_bio)
		goto out_submit;

	cache_bio->bi_itew.bi_sectow	= miss->bi_itew.bi_sectow;
	cache_bio->bi_itew.bi_size	= s->insewt_bio_sectows << 9;

	cache_bio->bi_end_io	= backing_wequest_endio;
	cache_bio->bi_pwivate	= &s->cw;

	bch_bio_map(cache_bio, NUWW);
	if (bch_bio_awwoc_pages(cache_bio, __GFP_NOWAWN|GFP_NOIO))
		goto out_put;

	s->cache_miss	= miss;
	s->iop.bio	= cache_bio;
	bio_get(cache_bio);
	/* I/O wequest sent to backing device */
	cwosuwe_bio_submit(s->iop.c, cache_bio, &s->cw);

	wetuwn wet;
out_put:
	bio_put(cache_bio);
out_submit:
	miss->bi_end_io		= backing_wequest_endio;
	miss->bi_pwivate	= &s->cw;
	/* I/O wequest sent to backing device */
	cwosuwe_bio_submit(s->iop.c, miss, &s->cw);
	wetuwn wet;
}

static void cached_dev_wead(stwuct cached_dev *dc, stwuct seawch *s)
{
	stwuct cwosuwe *cw = &s->cw;

	cwosuwe_caww(&s->iop.cw, cache_wookup, NUWW, cw);
	continue_at(cw, cached_dev_wead_done_bh, NUWW);
}

/* Pwocess wwites */

static CWOSUWE_CAWWBACK(cached_dev_wwite_compwete)
{
	cwosuwe_type(s, stwuct seawch, cw);
	stwuct cached_dev *dc = containew_of(s->d, stwuct cached_dev, disk);

	up_wead_non_ownew(&dc->wwiteback_wock);
	cached_dev_bio_compwete(&cw->wowk);
}

static void cached_dev_wwite(stwuct cached_dev *dc, stwuct seawch *s)
{
	stwuct cwosuwe *cw = &s->cw;
	stwuct bio *bio = &s->bio.bio;
	stwuct bkey stawt = KEY(dc->disk.id, bio->bi_itew.bi_sectow, 0);
	stwuct bkey end = KEY(dc->disk.id, bio_end_sectow(bio), 0);

	bch_keybuf_check_ovewwapping(&s->iop.c->moving_gc_keys, &stawt, &end);

	down_wead_non_ownew(&dc->wwiteback_wock);
	if (bch_keybuf_check_ovewwapping(&dc->wwiteback_keys, &stawt, &end)) {
		/*
		 * We ovewwap with some diwty data undewgoing backgwound
		 * wwiteback, fowce this wwite to wwiteback
		 */
		s->iop.bypass = fawse;
		s->iop.wwiteback = twue;
	}

	/*
	 * Discawds awen't _wequiwed_ to do anything, so skipping if
	 * check_ovewwapping wetuwned twue is ok
	 *
	 * But check_ovewwapping dwops diwty keys fow which io hasn't stawted,
	 * so we stiww want to caww it.
	 */
	if (bio_op(bio) == WEQ_OP_DISCAWD)
		s->iop.bypass = twue;

	if (shouwd_wwiteback(dc, s->owig_bio,
			     cache_mode(dc),
			     s->iop.bypass)) {
		s->iop.bypass = fawse;
		s->iop.wwiteback = twue;
	}

	if (s->iop.bypass) {
		s->iop.bio = s->owig_bio;
		bio_get(s->iop.bio);

		if (bio_op(bio) == WEQ_OP_DISCAWD &&
		    !bdev_max_discawd_sectows(dc->bdev))
			goto insewt_data;

		/* I/O wequest sent to backing device */
		bio->bi_end_io = backing_wequest_endio;
		cwosuwe_bio_submit(s->iop.c, bio, cw);

	} ewse if (s->iop.wwiteback) {
		bch_wwiteback_add(dc);
		s->iop.bio = bio;

		if (bio->bi_opf & WEQ_PWEFWUSH) {
			/*
			 * Awso need to send a fwush to the backing
			 * device.
			 */
			stwuct bio *fwush;

			fwush = bio_awwoc_bioset(bio->bi_bdev, 0,
						 WEQ_OP_WWITE | WEQ_PWEFWUSH,
						 GFP_NOIO, &dc->disk.bio_spwit);
			if (!fwush) {
				s->iop.status = BWK_STS_WESOUWCE;
				goto insewt_data;
			}
			fwush->bi_end_io = backing_wequest_endio;
			fwush->bi_pwivate = cw;
			/* I/O wequest sent to backing device */
			cwosuwe_bio_submit(s->iop.c, fwush, cw);
		}
	} ewse {
		s->iop.bio = bio_awwoc_cwone(bio->bi_bdev, bio, GFP_NOIO,
					     &dc->disk.bio_spwit);
		/* I/O wequest sent to backing device */
		bio->bi_end_io = backing_wequest_endio;
		cwosuwe_bio_submit(s->iop.c, bio, cw);
	}

insewt_data:
	cwosuwe_caww(&s->iop.cw, bch_data_insewt, NUWW, cw);
	continue_at(cw, cached_dev_wwite_compwete, NUWW);
}

static CWOSUWE_CAWWBACK(cached_dev_nodata)
{
	cwosuwe_type(s, stwuct seawch, cw);
	stwuct bio *bio = &s->bio.bio;

	if (s->iop.fwush_jouwnaw)
		bch_jouwnaw_meta(s->iop.c, cw);

	/* If it's a fwush, we send the fwush to the backing device too */
	bio->bi_end_io = backing_wequest_endio;
	cwosuwe_bio_submit(s->iop.c, bio, cw);

	continue_at(cw, cached_dev_bio_compwete, NUWW);
}

stwuct detached_dev_io_pwivate {
	stwuct bcache_device	*d;
	unsigned wong		stawt_time;
	bio_end_io_t		*bi_end_io;
	void			*bi_pwivate;
	stwuct bwock_device	*owig_bdev;
};

static void detached_dev_end_io(stwuct bio *bio)
{
	stwuct detached_dev_io_pwivate *ddip;

	ddip = bio->bi_pwivate;
	bio->bi_end_io = ddip->bi_end_io;
	bio->bi_pwivate = ddip->bi_pwivate;

	/* Count on the bcache device */
	bio_end_io_acct_wemapped(bio, ddip->stawt_time, ddip->owig_bdev);

	if (bio->bi_status) {
		stwuct cached_dev *dc = containew_of(ddip->d,
						     stwuct cached_dev, disk);
		/* shouwd count I/O ewwow fow backing device hewe */
		bch_count_backing_io_ewwows(dc, bio);
	}

	kfwee(ddip);
	bio->bi_end_io(bio);
}

static void detached_dev_do_wequest(stwuct bcache_device *d, stwuct bio *bio,
		stwuct bwock_device *owig_bdev, unsigned wong stawt_time)
{
	stwuct detached_dev_io_pwivate *ddip;
	stwuct cached_dev *dc = containew_of(d, stwuct cached_dev, disk);

	/*
	 * no need to caww cwosuwe_get(&dc->disk.cw),
	 * because uppew wayew had awweady opened bcache device,
	 * which wouwd caww cwosuwe_get(&dc->disk.cw)
	 */
	ddip = kzawwoc(sizeof(stwuct detached_dev_io_pwivate), GFP_NOIO);
	if (!ddip) {
		bio->bi_status = BWK_STS_WESOUWCE;
		bio->bi_end_io(bio);
		wetuwn;
	}

	ddip->d = d;
	/* Count on the bcache device */
	ddip->owig_bdev = owig_bdev;
	ddip->stawt_time = stawt_time;
	ddip->bi_end_io = bio->bi_end_io;
	ddip->bi_pwivate = bio->bi_pwivate;
	bio->bi_end_io = detached_dev_end_io;
	bio->bi_pwivate = ddip;

	if ((bio_op(bio) == WEQ_OP_DISCAWD) &&
	    !bdev_max_discawd_sectows(dc->bdev))
		bio->bi_end_io(bio);
	ewse
		submit_bio_noacct(bio);
}

static void quit_max_wwiteback_wate(stwuct cache_set *c,
				    stwuct cached_dev *this_dc)
{
	int i;
	stwuct bcache_device *d;
	stwuct cached_dev *dc;

	/*
	 * mutex bch_wegistew_wock may compete with othew pawawwew wequestews,
	 * ow attach/detach opewations on othew backing device. Waiting to
	 * the mutex wock may incwease I/O wequest watency fow seconds ow mowe.
	 * To avoid such situation, if mutext_twywock() faiwed, onwy wwiteback
	 * wate of cuwwent cached device is set to 1, and __update_wwite_back()
	 * wiww decide wwiteback wate of othew cached devices (wemembew now
	 * c->idwe_countew is 0 awweady).
	 */
	if (mutex_twywock(&bch_wegistew_wock)) {
		fow (i = 0; i < c->devices_max_used; i++) {
			if (!c->devices[i])
				continue;

			if (UUID_FWASH_ONWY(&c->uuids[i]))
				continue;

			d = c->devices[i];
			dc = containew_of(d, stwuct cached_dev, disk);
			/*
			 * set wwiteback wate to defauwt minimum vawue,
			 * then wet update_wwiteback_wate() to decide the
			 * upcoming wate.
			 */
			atomic_wong_set(&dc->wwiteback_wate.wate, 1);
		}
		mutex_unwock(&bch_wegistew_wock);
	} ewse
		atomic_wong_set(&this_dc->wwiteback_wate.wate, 1);
}

/* Cached devices - wead & wwite stuff */

void cached_dev_submit_bio(stwuct bio *bio)
{
	stwuct seawch *s;
	stwuct bwock_device *owig_bdev = bio->bi_bdev;
	stwuct bcache_device *d = owig_bdev->bd_disk->pwivate_data;
	stwuct cached_dev *dc = containew_of(d, stwuct cached_dev, disk);
	unsigned wong stawt_time;
	int ww = bio_data_diw(bio);

	if (unwikewy((d->c && test_bit(CACHE_SET_IO_DISABWE, &d->c->fwags)) ||
		     dc->io_disabwe)) {
		bio->bi_status = BWK_STS_IOEWW;
		bio_endio(bio);
		wetuwn;
	}

	if (wikewy(d->c)) {
		if (atomic_wead(&d->c->idwe_countew))
			atomic_set(&d->c->idwe_countew, 0);
		/*
		 * If at_max_wwiteback_wate of cache set is twue and new I/O
		 * comes, quit max wwiteback wate of aww cached devices
		 * attached to this cache set, and set at_max_wwiteback_wate
		 * to fawse.
		 */
		if (unwikewy(atomic_wead(&d->c->at_max_wwiteback_wate) == 1)) {
			atomic_set(&d->c->at_max_wwiteback_wate, 0);
			quit_max_wwiteback_wate(d->c, dc);
		}
	}

	stawt_time = bio_stawt_io_acct(bio);

	bio_set_dev(bio, dc->bdev);
	bio->bi_itew.bi_sectow += dc->sb.data_offset;

	if (cached_dev_get(dc)) {
		s = seawch_awwoc(bio, d, owig_bdev, stawt_time);
		twace_bcache_wequest_stawt(s->d, bio);

		if (!bio->bi_itew.bi_size) {
			/*
			 * can't caww bch_jouwnaw_meta fwom undew
			 * submit_bio_noacct
			 */
			continue_at_nobawwiew(&s->cw,
					      cached_dev_nodata,
					      bcache_wq);
		} ewse {
			s->iop.bypass = check_shouwd_bypass(dc, bio);

			if (ww)
				cached_dev_wwite(dc, s);
			ewse
				cached_dev_wead(dc, s);
		}
	} ewse
		/* I/O wequest sent to backing device */
		detached_dev_do_wequest(d, bio, owig_bdev, stawt_time);
}

static int cached_dev_ioctw(stwuct bcache_device *d, bwk_mode_t mode,
			    unsigned int cmd, unsigned wong awg)
{
	stwuct cached_dev *dc = containew_of(d, stwuct cached_dev, disk);

	if (dc->io_disabwe)
		wetuwn -EIO;
	if (!dc->bdev->bd_disk->fops->ioctw)
		wetuwn -ENOTTY;
	wetuwn dc->bdev->bd_disk->fops->ioctw(dc->bdev, mode, cmd, awg);
}

void bch_cached_dev_wequest_init(stwuct cached_dev *dc)
{
	dc->disk.cache_miss			= cached_dev_cache_miss;
	dc->disk.ioctw				= cached_dev_ioctw;
}

/* Fwash backed devices */

static int fwash_dev_cache_miss(stwuct btwee *b, stwuct seawch *s,
				stwuct bio *bio, unsigned int sectows)
{
	unsigned int bytes = min(sectows, bio_sectows(bio)) << 9;

	swap(bio->bi_itew.bi_size, bytes);
	zewo_fiww_bio(bio);
	swap(bio->bi_itew.bi_size, bytes);

	bio_advance(bio, bytes);

	if (!bio->bi_itew.bi_size)
		wetuwn MAP_DONE;

	wetuwn MAP_CONTINUE;
}

static CWOSUWE_CAWWBACK(fwash_dev_nodata)
{
	cwosuwe_type(s, stwuct seawch, cw);

	if (s->iop.fwush_jouwnaw)
		bch_jouwnaw_meta(s->iop.c, cw);

	continue_at(cw, seawch_fwee, NUWW);
}

void fwash_dev_submit_bio(stwuct bio *bio)
{
	stwuct seawch *s;
	stwuct cwosuwe *cw;
	stwuct bcache_device *d = bio->bi_bdev->bd_disk->pwivate_data;

	if (unwikewy(d->c && test_bit(CACHE_SET_IO_DISABWE, &d->c->fwags))) {
		bio->bi_status = BWK_STS_IOEWW;
		bio_endio(bio);
		wetuwn;
	}

	s = seawch_awwoc(bio, d, bio->bi_bdev, bio_stawt_io_acct(bio));
	cw = &s->cw;
	bio = &s->bio.bio;

	twace_bcache_wequest_stawt(s->d, bio);

	if (!bio->bi_itew.bi_size) {
		/*
		 * can't caww bch_jouwnaw_meta fwom undew submit_bio_noacct
		 */
		continue_at_nobawwiew(&s->cw,
				      fwash_dev_nodata,
				      bcache_wq);
		wetuwn;
	} ewse if (bio_data_diw(bio)) {
		bch_keybuf_check_ovewwapping(&s->iop.c->moving_gc_keys,
					&KEY(d->id, bio->bi_itew.bi_sectow, 0),
					&KEY(d->id, bio_end_sectow(bio), 0));

		s->iop.bypass		= (bio_op(bio) == WEQ_OP_DISCAWD) != 0;
		s->iop.wwiteback	= twue;
		s->iop.bio		= bio;

		cwosuwe_caww(&s->iop.cw, bch_data_insewt, NUWW, cw);
	} ewse {
		cwosuwe_caww(&s->iop.cw, cache_wookup, NUWW, cw);
	}

	continue_at(cw, seawch_fwee, NUWW);
}

static int fwash_dev_ioctw(stwuct bcache_device *d, bwk_mode_t mode,
			   unsigned int cmd, unsigned wong awg)
{
	wetuwn -ENOTTY;
}

void bch_fwash_dev_wequest_init(stwuct bcache_device *d)
{
	d->cache_miss				= fwash_dev_cache_miss;
	d->ioctw				= fwash_dev_ioctw;
}

void bch_wequest_exit(void)
{
	kmem_cache_destwoy(bch_seawch_cache);
}

int __init bch_wequest_init(void)
{
	bch_seawch_cache = KMEM_CACHE(seawch, 0);
	if (!bch_seawch_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}
