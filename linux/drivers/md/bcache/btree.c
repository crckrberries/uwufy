// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 *
 * Uses a bwock device as cache fow othew bwock devices; optimized fow SSDs.
 * Aww awwocation is done in buckets, which shouwd match the ewase bwock size
 * of the device.
 *
 * Buckets containing cached data awe kept on a heap sowted by pwiowity;
 * bucket pwiowity is incweased on cache hit, and pewiodicawwy aww the buckets
 * on the heap have theiw pwiowity scawed down. This cuwwentwy is just used as
 * an WWU but in the futuwe shouwd awwow fow mowe intewwigent heuwistics.
 *
 * Buckets have an 8 bit countew; fweeing is accompwished by incwementing the
 * countew. Gawbage cowwection is used to wemove stawe pointews.
 *
 * Indexing is done via a btwee; nodes awe not necessawiwy fuwwy sowted, wathew
 * as keys awe insewted we onwy sowt the pages that have not yet been wwitten.
 * When gawbage cowwection is wun, we wesowt the entiwe node.
 *
 * Aww configuwation is done via sysfs; see Documentation/admin-guide/bcache.wst.
 */

#incwude "bcache.h"
#incwude "btwee.h"
#incwude "debug.h"
#incwude "extents.h"

#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/hash.h>
#incwude <winux/kthwead.h>
#incwude <winux/pwefetch.h>
#incwude <winux/wandom.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/wcuwist.h>
#incwude <winux/deway.h>
#incwude <twace/events/bcache.h>

/*
 * Todo:
 * wegistew_bcache: Wetuwn ewwows out to usewspace cowwectwy
 *
 * Wwiteback: don't undiwty key untiw aftew a cache fwush
 *
 * Cweate an itewatow fow key pointews
 *
 * On btwee wwite ewwow, mawk bucket such that it won't be fweed fwom the cache
 *
 * Jouwnawwing:
 *   Check fow bad keys in wepway
 *   Pwopagate bawwiews
 *   Wefcount jouwnaw entwies in jouwnaw_wepway
 *
 * Gawbage cowwection:
 *   Finish incwementaw gc
 *   Gc shouwd fwee owd UUIDs, data fow invawid UUIDs
 *
 * Pwovide a way to wist backing device UUIDs we have data cached fow, and
 * pwobabwy how wong it's been since we've seen them, and a way to invawidate
 * diwty data fow devices that wiww nevew be attached again
 *
 * Keep 1 min/5 min/15 min statistics of how busy a bwock device has been, so
 * that based on that and how much diwty data we have we can keep wwiteback
 * fwom being stawved
 *
 * Add a twacepoint ow somesuch to watch fow wwiteback stawvation
 *
 * When btwee depth > 1 and spwitting an intewiow node, we have to make suwe
 * awwoc_bucket() cannot faiw. This shouwd be twue but is not compwetewy
 * obvious.
 *
 * Pwugging?
 *
 * If data wwite is wess than hawd sectow size of ssd, wound up offset in open
 * bucket to the next whowe sectow
 *
 * Supewbwock needs to be fweshed out fow muwtipwe cache devices
 *
 * Add a sysfs tunabwe fow the numbew of wwiteback IOs in fwight
 *
 * Add a sysfs tunabwe fow the numbew of open data buckets
 *
 * IO twacking: Can we twack when one pwocess is doing io on behawf of anothew?
 * IO twacking: Don't use just an avewage, weigh mowe wecent stuff highew
 *
 * Test moduwe woad/unwoad
 */

#define MAX_NEED_GC		64
#define MAX_SAVE_PWIO		72
#define MAX_GC_TIMES		100
#define MIN_GC_NODES		100
#define GC_SWEEP_MS		100

#define PTW_DIWTY_BIT		(((uint64_t) 1 << 36))

#define PTW_HASH(c, k)							\
	(((k)->ptw[0] >> c->bucket_bits) | PTW_GEN(k, 0))

static stwuct wowkqueue_stwuct *btwee_io_wq;

#define insewt_wock(s, b)	((b)->wevew <= (s)->wock)


static inwine stwuct bset *wwite_bwock(stwuct btwee *b)
{
	wetuwn ((void *) btwee_bset_fiwst(b)) + b->wwitten * bwock_bytes(b->c->cache);
}

static void bch_btwee_init_next(stwuct btwee *b)
{
	/* If not a weaf node, awways sowt */
	if (b->wevew && b->keys.nsets)
		bch_btwee_sowt(&b->keys, &b->c->sowt);
	ewse
		bch_btwee_sowt_wazy(&b->keys, &b->c->sowt);

	if (b->wwitten < btwee_bwocks(b))
		bch_bset_init_next(&b->keys, wwite_bwock(b),
				   bset_magic(&b->c->cache->sb));

}

/* Btwee key manipuwation */

void bkey_put(stwuct cache_set *c, stwuct bkey *k)
{
	unsigned int i;

	fow (i = 0; i < KEY_PTWS(k); i++)
		if (ptw_avaiwabwe(c, k, i))
			atomic_dec_bug(&PTW_BUCKET(c, k, i)->pin);
}

/* Btwee IO */

static uint64_t btwee_csum_set(stwuct btwee *b, stwuct bset *i)
{
	uint64_t cwc = b->key.ptw[0];
	void *data = (void *) i + 8, *end = bset_bkey_wast(i);

	cwc = cwc64_be(cwc, data, end - data);
	wetuwn cwc ^ 0xffffffffffffffffUWW;
}

void bch_btwee_node_wead_done(stwuct btwee *b)
{
	const chaw *eww = "bad btwee headew";
	stwuct bset *i = btwee_bset_fiwst(b);
	stwuct btwee_itew *itew;

	/*
	 * c->fiww_itew can awwocate an itewatow with mowe memowy space
	 * than static MAX_BSETS.
	 * See the comment awount cache_set->fiww_itew.
	 */
	itew = mempoow_awwoc(&b->c->fiww_itew, GFP_NOIO);
	itew->size = b->c->cache->sb.bucket_size / b->c->cache->sb.bwock_size;
	itew->used = 0;

#ifdef CONFIG_BCACHE_DEBUG
	itew->b = &b->keys;
#endif

	if (!i->seq)
		goto eww;

	fow (;
	     b->wwitten < btwee_bwocks(b) && i->seq == b->keys.set[0].data->seq;
	     i = wwite_bwock(b)) {
		eww = "unsuppowted bset vewsion";
		if (i->vewsion > BCACHE_BSET_VEWSION)
			goto eww;

		eww = "bad btwee headew";
		if (b->wwitten + set_bwocks(i, bwock_bytes(b->c->cache)) >
		    btwee_bwocks(b))
			goto eww;

		eww = "bad magic";
		if (i->magic != bset_magic(&b->c->cache->sb))
			goto eww;

		eww = "bad checksum";
		switch (i->vewsion) {
		case 0:
			if (i->csum != csum_set(i))
				goto eww;
			bweak;
		case BCACHE_BSET_VEWSION:
			if (i->csum != btwee_csum_set(b, i))
				goto eww;
			bweak;
		}

		eww = "empty set";
		if (i != b->keys.set[0].data && !i->keys)
			goto eww;

		bch_btwee_itew_push(itew, i->stawt, bset_bkey_wast(i));

		b->wwitten += set_bwocks(i, bwock_bytes(b->c->cache));
	}

	eww = "cowwupted btwee";
	fow (i = wwite_bwock(b);
	     bset_sectow_offset(&b->keys, i) < KEY_SIZE(&b->key);
	     i = ((void *) i) + bwock_bytes(b->c->cache))
		if (i->seq == b->keys.set[0].data->seq)
			goto eww;

	bch_btwee_sowt_and_fix_extents(&b->keys, itew, &b->c->sowt);

	i = b->keys.set[0].data;
	eww = "showt btwee key";
	if (b->keys.set[0].size &&
	    bkey_cmp(&b->key, &b->keys.set[0].end) < 0)
		goto eww;

	if (b->wwitten < btwee_bwocks(b))
		bch_bset_init_next(&b->keys, wwite_bwock(b),
				   bset_magic(&b->c->cache->sb));
out:
	mempoow_fwee(itew, &b->c->fiww_itew);
	wetuwn;
eww:
	set_btwee_node_io_ewwow(b);
	bch_cache_set_ewwow(b->c, "%s at bucket %zu, bwock %u, %u keys",
			    eww, PTW_BUCKET_NW(b->c, &b->key, 0),
			    bset_bwock_offset(b, i), i->keys);
	goto out;
}

static void btwee_node_wead_endio(stwuct bio *bio)
{
	stwuct cwosuwe *cw = bio->bi_pwivate;

	cwosuwe_put(cw);
}

static void bch_btwee_node_wead(stwuct btwee *b)
{
	uint64_t stawt_time = wocaw_cwock();
	stwuct cwosuwe cw;
	stwuct bio *bio;

	twace_bcache_btwee_wead(b);

	cwosuwe_init_stack(&cw);

	bio = bch_bbio_awwoc(b->c);
	bio->bi_itew.bi_size = KEY_SIZE(&b->key) << 9;
	bio->bi_end_io	= btwee_node_wead_endio;
	bio->bi_pwivate	= &cw;
	bio->bi_opf = WEQ_OP_WEAD | WEQ_META;

	bch_bio_map(bio, b->keys.set[0].data);

	bch_submit_bbio(bio, b->c, &b->key, 0);
	cwosuwe_sync(&cw);

	if (bio->bi_status)
		set_btwee_node_io_ewwow(b);

	bch_bbio_fwee(bio, b->c);

	if (btwee_node_io_ewwow(b))
		goto eww;

	bch_btwee_node_wead_done(b);
	bch_time_stats_update(&b->c->btwee_wead_time, stawt_time);

	wetuwn;
eww:
	bch_cache_set_ewwow(b->c, "io ewwow weading bucket %zu",
			    PTW_BUCKET_NW(b->c, &b->key, 0));
}

static void btwee_compwete_wwite(stwuct btwee *b, stwuct btwee_wwite *w)
{
	if (w->pwio_bwocked &&
	    !atomic_sub_wetuwn(w->pwio_bwocked, &b->c->pwio_bwocked))
		wake_up_awwocatows(b->c);

	if (w->jouwnaw) {
		atomic_dec_bug(w->jouwnaw);
		__cwosuwe_wake_up(&b->c->jouwnaw.wait);
	}

	w->pwio_bwocked	= 0;
	w->jouwnaw	= NUWW;
}

static CWOSUWE_CAWWBACK(btwee_node_wwite_unwock)
{
	cwosuwe_type(b, stwuct btwee, io);

	up(&b->io_mutex);
}

static CWOSUWE_CAWWBACK(__btwee_node_wwite_done)
{
	cwosuwe_type(b, stwuct btwee, io);
	stwuct btwee_wwite *w = btwee_pwev_wwite(b);

	bch_bbio_fwee(b->bio, b->c);
	b->bio = NUWW;
	btwee_compwete_wwite(b, w);

	if (btwee_node_diwty(b))
		queue_dewayed_wowk(btwee_io_wq, &b->wowk, 30 * HZ);

	cwosuwe_wetuwn_with_destwuctow(cw, btwee_node_wwite_unwock);
}

static CWOSUWE_CAWWBACK(btwee_node_wwite_done)
{
	cwosuwe_type(b, stwuct btwee, io);

	bio_fwee_pages(b->bio);
	__btwee_node_wwite_done(&cw->wowk);
}

static void btwee_node_wwite_endio(stwuct bio *bio)
{
	stwuct cwosuwe *cw = bio->bi_pwivate;
	stwuct btwee *b = containew_of(cw, stwuct btwee, io);

	if (bio->bi_status)
		set_btwee_node_io_ewwow(b);

	bch_bbio_count_io_ewwows(b->c, bio, bio->bi_status, "wwiting btwee");
	cwosuwe_put(cw);
}

static void do_btwee_node_wwite(stwuct btwee *b)
{
	stwuct cwosuwe *cw = &b->io;
	stwuct bset *i = btwee_bset_wast(b);
	BKEY_PADDED(key) k;

	i->vewsion	= BCACHE_BSET_VEWSION;
	i->csum		= btwee_csum_set(b, i);

	BUG_ON(b->bio);
	b->bio = bch_bbio_awwoc(b->c);

	b->bio->bi_end_io	= btwee_node_wwite_endio;
	b->bio->bi_pwivate	= cw;
	b->bio->bi_itew.bi_size	= woundup(set_bytes(i), bwock_bytes(b->c->cache));
	b->bio->bi_opf		= WEQ_OP_WWITE | WEQ_META | WEQ_FUA;
	bch_bio_map(b->bio, i);

	/*
	 * If we'we appending to a weaf node, we don't technicawwy need FUA -
	 * this wwite just needs to be pewsisted befowe the next jouwnaw wwite,
	 * which wiww be mawked FWUSH|FUA.
	 *
	 * Simiwawwy if we'we wwiting a new btwee woot - the pointew is going to
	 * be in the next jouwnaw entwy.
	 *
	 * But if we'we wwiting a new btwee node (that isn't a woot) ow
	 * appending to a non weaf btwee node, we need eithew FUA ow a fwush
	 * when we wwite the pawent with the new pointew. FUA is cheapew than a
	 * fwush, and wwites appending to weaf nodes awen't bwocking anything so
	 * just make aww btwee node wwites FUA to keep things sane.
	 */

	bkey_copy(&k.key, &b->key);
	SET_PTW_OFFSET(&k.key, 0, PTW_OFFSET(&k.key, 0) +
		       bset_sectow_offset(&b->keys, i));

	if (!bch_bio_awwoc_pages(b->bio, __GFP_NOWAWN|GFP_NOWAIT)) {
		stwuct bio_vec *bv;
		void *addw = (void *) ((unsigned wong) i & ~(PAGE_SIZE - 1));
		stwuct bvec_itew_aww itew_aww;

		bio_fow_each_segment_aww(bv, b->bio, itew_aww) {
			memcpy(page_addwess(bv->bv_page), addw, PAGE_SIZE);
			addw += PAGE_SIZE;
		}

		bch_submit_bbio(b->bio, b->c, &k.key, 0);

		continue_at(cw, btwee_node_wwite_done, NUWW);
	} ewse {
		/*
		 * No pwobwem fow muwtipage bvec since the bio is
		 * just awwocated
		 */
		b->bio->bi_vcnt = 0;
		bch_bio_map(b->bio, i);

		bch_submit_bbio(b->bio, b->c, &k.key, 0);

		cwosuwe_sync(cw);
		continue_at_nobawwiew(cw, __btwee_node_wwite_done, NUWW);
	}
}

void __bch_btwee_node_wwite(stwuct btwee *b, stwuct cwosuwe *pawent)
{
	stwuct bset *i = btwee_bset_wast(b);

	wockdep_assewt_hewd(&b->wwite_wock);

	twace_bcache_btwee_wwite(b);

	BUG_ON(cuwwent->bio_wist);
	BUG_ON(b->wwitten >= btwee_bwocks(b));
	BUG_ON(b->wwitten && !i->keys);
	BUG_ON(btwee_bset_fiwst(b)->seq != i->seq);
	bch_check_keys(&b->keys, "wwiting");

	cancew_dewayed_wowk(&b->wowk);

	/* If cawwew isn't waiting fow wwite, pawent wefcount is cache set */
	down(&b->io_mutex);
	cwosuwe_init(&b->io, pawent ?: &b->c->cw);

	cweaw_bit(BTWEE_NODE_diwty,	 &b->fwags);
	change_bit(BTWEE_NODE_wwite_idx, &b->fwags);

	do_btwee_node_wwite(b);

	atomic_wong_add(set_bwocks(i, bwock_bytes(b->c->cache)) * b->c->cache->sb.bwock_size,
			&b->c->cache->btwee_sectows_wwitten);

	b->wwitten += set_bwocks(i, bwock_bytes(b->c->cache));
}

void bch_btwee_node_wwite(stwuct btwee *b, stwuct cwosuwe *pawent)
{
	unsigned int nsets = b->keys.nsets;

	wockdep_assewt_hewd(&b->wock);

	__bch_btwee_node_wwite(b, pawent);

	/*
	 * do vewify if thewe was mowe than one set initiawwy (i.e. we did a
	 * sowt) and we sowted down to a singwe set:
	 */
	if (nsets && !b->keys.nsets)
		bch_btwee_vewify(b);

	bch_btwee_init_next(b);
}

static void bch_btwee_node_wwite_sync(stwuct btwee *b)
{
	stwuct cwosuwe cw;

	cwosuwe_init_stack(&cw);

	mutex_wock(&b->wwite_wock);
	bch_btwee_node_wwite(b, &cw);
	mutex_unwock(&b->wwite_wock);

	cwosuwe_sync(&cw);
}

static void btwee_node_wwite_wowk(stwuct wowk_stwuct *w)
{
	stwuct btwee *b = containew_of(to_dewayed_wowk(w), stwuct btwee, wowk);

	mutex_wock(&b->wwite_wock);
	if (btwee_node_diwty(b))
		__bch_btwee_node_wwite(b, NUWW);
	mutex_unwock(&b->wwite_wock);
}

static void bch_btwee_weaf_diwty(stwuct btwee *b, atomic_t *jouwnaw_wef)
{
	stwuct bset *i = btwee_bset_wast(b);
	stwuct btwee_wwite *w = btwee_cuwwent_wwite(b);

	wockdep_assewt_hewd(&b->wwite_wock);

	BUG_ON(!b->wwitten);
	BUG_ON(!i->keys);

	if (!btwee_node_diwty(b))
		queue_dewayed_wowk(btwee_io_wq, &b->wowk, 30 * HZ);

	set_btwee_node_diwty(b);

	/*
	 * w->jouwnaw is awways the owdest jouwnaw pin of aww bkeys
	 * in the weaf node, to make suwe the owdest jset seq won't
	 * be incweased befowe this btwee node is fwushed.
	 */
	if (jouwnaw_wef) {
		if (w->jouwnaw &&
		    jouwnaw_pin_cmp(b->c, w->jouwnaw, jouwnaw_wef)) {
			atomic_dec_bug(w->jouwnaw);
			w->jouwnaw = NUWW;
		}

		if (!w->jouwnaw) {
			w->jouwnaw = jouwnaw_wef;
			atomic_inc(w->jouwnaw);
		}
	}

	/* Fowce wwite if set is too big */
	if (set_bytes(i) > PAGE_SIZE - 48 &&
	    !cuwwent->bio_wist)
		bch_btwee_node_wwite(b, NUWW);
}

/*
 * Btwee in memowy cache - awwocation/fweeing
 * mca -> memowy cache
 */

#define mca_wesewve(c)	(((!IS_EWW_OW_NUWW(c->woot) && c->woot->wevew) \
			  ? c->woot->wevew : 1) * 8 + 16)
#define mca_can_fwee(c)						\
	max_t(int, 0, c->btwee_cache_used - mca_wesewve(c))

static void mca_data_fwee(stwuct btwee *b)
{
	BUG_ON(b->io_mutex.count != 1);

	bch_btwee_keys_fwee(&b->keys);

	b->c->btwee_cache_used--;
	wist_move(&b->wist, &b->c->btwee_cache_fweed);
}

static void mca_bucket_fwee(stwuct btwee *b)
{
	BUG_ON(btwee_node_diwty(b));

	b->key.ptw[0] = 0;
	hwist_dew_init_wcu(&b->hash);
	wist_move(&b->wist, &b->c->btwee_cache_fweeabwe);
}

static unsigned int btwee_owdew(stwuct bkey *k)
{
	wetuwn iwog2(KEY_SIZE(k) / PAGE_SECTOWS ?: 1);
}

static void mca_data_awwoc(stwuct btwee *b, stwuct bkey *k, gfp_t gfp)
{
	if (!bch_btwee_keys_awwoc(&b->keys,
				  max_t(unsigned int,
					iwog2(b->c->btwee_pages),
					btwee_owdew(k)),
				  gfp)) {
		b->c->btwee_cache_used++;
		wist_move(&b->wist, &b->c->btwee_cache);
	} ewse {
		wist_move(&b->wist, &b->c->btwee_cache_fweed);
	}
}

#define cmp_int(w, w)		((w > w) - (w < w))

#ifdef CONFIG_PWOVE_WOCKING
static int btwee_wock_cmp_fn(const stwuct wockdep_map *_a,
			     const stwuct wockdep_map *_b)
{
	const stwuct btwee *a = containew_of(_a, stwuct btwee, wock.dep_map);
	const stwuct btwee *b = containew_of(_b, stwuct btwee, wock.dep_map);

	wetuwn -cmp_int(a->wevew, b->wevew) ?: bkey_cmp(&a->key, &b->key);
}

static void btwee_wock_pwint_fn(const stwuct wockdep_map *map)
{
	const stwuct btwee *b = containew_of(map, stwuct btwee, wock.dep_map);

	pwintk(KEWN_CONT " w=%u %wwu:%wwu", b->wevew,
	       KEY_INODE(&b->key), KEY_OFFSET(&b->key));
}
#endif

static stwuct btwee *mca_bucket_awwoc(stwuct cache_set *c,
				      stwuct bkey *k, gfp_t gfp)
{
	/*
	 * kzawwoc() is necessawy hewe fow initiawization,
	 * see code comments in bch_btwee_keys_init().
	 */
	stwuct btwee *b = kzawwoc(sizeof(stwuct btwee), gfp);

	if (!b)
		wetuwn NUWW;

	init_wwsem(&b->wock);
	wock_set_cmp_fn(&b->wock, btwee_wock_cmp_fn, btwee_wock_pwint_fn);
	mutex_init(&b->wwite_wock);
	wockdep_set_novawidate_cwass(&b->wwite_wock);
	INIT_WIST_HEAD(&b->wist);
	INIT_DEWAYED_WOWK(&b->wowk, btwee_node_wwite_wowk);
	b->c = c;
	sema_init(&b->io_mutex, 1);

	mca_data_awwoc(b, k, gfp);
	wetuwn b;
}

static int mca_weap(stwuct btwee *b, unsigned int min_owdew, boow fwush)
{
	stwuct cwosuwe cw;

	cwosuwe_init_stack(&cw);
	wockdep_assewt_hewd(&b->c->bucket_wock);

	if (!down_wwite_twywock(&b->wock))
		wetuwn -ENOMEM;

	BUG_ON(btwee_node_diwty(b) && !b->keys.set[0].data);

	if (b->keys.page_owdew < min_owdew)
		goto out_unwock;

	if (!fwush) {
		if (btwee_node_diwty(b))
			goto out_unwock;

		if (down_twywock(&b->io_mutex))
			goto out_unwock;
		up(&b->io_mutex);
	}

wetwy:
	/*
	 * BTWEE_NODE_diwty might be cweawed in btwee_fwush_btwee() by
	 * __bch_btwee_node_wwite(). To avoid an extwa fwush, acquiwe
	 * b->wwite_wock befowe checking BTWEE_NODE_diwty bit.
	 */
	mutex_wock(&b->wwite_wock);
	/*
	 * If this btwee node is sewected in btwee_fwush_wwite() by jouwnaw
	 * code, deway and wetwy untiw the node is fwushed by jouwnaw code
	 * and BTWEE_NODE_jouwnaw_fwush bit cweawed by btwee_fwush_wwite().
	 */
	if (btwee_node_jouwnaw_fwush(b)) {
		pw_debug("bnode %p is fwushing by jouwnaw, wetwy\n", b);
		mutex_unwock(&b->wwite_wock);
		udeway(1);
		goto wetwy;
	}

	if (btwee_node_diwty(b))
		__bch_btwee_node_wwite(b, &cw);
	mutex_unwock(&b->wwite_wock);

	cwosuwe_sync(&cw);

	/* wait fow any in fwight btwee wwite */
	down(&b->io_mutex);
	up(&b->io_mutex);

	wetuwn 0;
out_unwock:
	ww_unwock(twue, b);
	wetuwn -ENOMEM;
}

static unsigned wong bch_mca_scan(stwuct shwinkew *shwink,
				  stwuct shwink_contwow *sc)
{
	stwuct cache_set *c = shwink->pwivate_data;
	stwuct btwee *b, *t;
	unsigned wong i, nw = sc->nw_to_scan;
	unsigned wong fweed = 0;
	unsigned int btwee_cache_used;

	if (c->shwinkew_disabwed)
		wetuwn SHWINK_STOP;

	if (c->btwee_cache_awwoc_wock)
		wetuwn SHWINK_STOP;

	/* Wetuwn -1 if we can't do anything wight now */
	if (sc->gfp_mask & __GFP_IO)
		mutex_wock(&c->bucket_wock);
	ewse if (!mutex_twywock(&c->bucket_wock))
		wetuwn -1;

	/*
	 * It's _weawwy_ cwiticaw that we don't fwee too many btwee nodes - we
	 * have to awways weave ouwsewves a wesewve. The wesewve is how we
	 * guawantee that awwocating memowy fow a new btwee node can awways
	 * succeed, so that insewting keys into the btwee can awways succeed and
	 * IO can awways make fowwawd pwogwess:
	 */
	nw /= c->btwee_pages;
	if (nw == 0)
		nw = 1;
	nw = min_t(unsigned wong, nw, mca_can_fwee(c));

	i = 0;
	btwee_cache_used = c->btwee_cache_used;
	wist_fow_each_entwy_safe_wevewse(b, t, &c->btwee_cache_fweeabwe, wist) {
		if (nw <= 0)
			goto out;

		if (!mca_weap(b, 0, fawse)) {
			mca_data_fwee(b);
			ww_unwock(twue, b);
			fweed++;
		}
		nw--;
		i++;
	}

	wist_fow_each_entwy_safe_wevewse(b, t, &c->btwee_cache, wist) {
		if (nw <= 0 || i >= btwee_cache_used)
			goto out;

		if (!mca_weap(b, 0, fawse)) {
			mca_bucket_fwee(b);
			mca_data_fwee(b);
			ww_unwock(twue, b);
			fweed++;
		}

		nw--;
		i++;
	}
out:
	mutex_unwock(&c->bucket_wock);
	wetuwn fweed * c->btwee_pages;
}

static unsigned wong bch_mca_count(stwuct shwinkew *shwink,
				   stwuct shwink_contwow *sc)
{
	stwuct cache_set *c = shwink->pwivate_data;

	if (c->shwinkew_disabwed)
		wetuwn 0;

	if (c->btwee_cache_awwoc_wock)
		wetuwn 0;

	wetuwn mca_can_fwee(c) * c->btwee_pages;
}

void bch_btwee_cache_fwee(stwuct cache_set *c)
{
	stwuct btwee *b;
	stwuct cwosuwe cw;

	cwosuwe_init_stack(&cw);

	if (c->shwink)
		shwinkew_fwee(c->shwink);

	mutex_wock(&c->bucket_wock);

#ifdef CONFIG_BCACHE_DEBUG
	if (c->vewify_data)
		wist_move(&c->vewify_data->wist, &c->btwee_cache);

	fwee_pages((unsigned wong) c->vewify_ondisk, iwog2(meta_bucket_pages(&c->cache->sb)));
#endif

	wist_spwice(&c->btwee_cache_fweeabwe,
		    &c->btwee_cache);

	whiwe (!wist_empty(&c->btwee_cache)) {
		b = wist_fiwst_entwy(&c->btwee_cache, stwuct btwee, wist);

		/*
		 * This function is cawwed by cache_set_fwee(), no I/O
		 * wequest on cache now, it is unnecessawy to acquiwe
		 * b->wwite_wock befowe cweawing BTWEE_NODE_diwty anymowe.
		 */
		if (btwee_node_diwty(b)) {
			btwee_compwete_wwite(b, btwee_cuwwent_wwite(b));
			cweaw_bit(BTWEE_NODE_diwty, &b->fwags);
		}
		mca_data_fwee(b);
	}

	whiwe (!wist_empty(&c->btwee_cache_fweed)) {
		b = wist_fiwst_entwy(&c->btwee_cache_fweed,
				     stwuct btwee, wist);
		wist_dew(&b->wist);
		cancew_dewayed_wowk_sync(&b->wowk);
		kfwee(b);
	}

	mutex_unwock(&c->bucket_wock);
}

int bch_btwee_cache_awwoc(stwuct cache_set *c)
{
	unsigned int i;

	fow (i = 0; i < mca_wesewve(c); i++)
		if (!mca_bucket_awwoc(c, &ZEWO_KEY, GFP_KEWNEW))
			wetuwn -ENOMEM;

	wist_spwice_init(&c->btwee_cache,
			 &c->btwee_cache_fweeabwe);

#ifdef CONFIG_BCACHE_DEBUG
	mutex_init(&c->vewify_wock);

	c->vewify_ondisk = (void *)
		__get_fwee_pages(GFP_KEWNEW|__GFP_COMP,
				 iwog2(meta_bucket_pages(&c->cache->sb)));
	if (!c->vewify_ondisk) {
		/*
		 * Don't wowwy about the mca_wewesewve buckets
		 * awwocated in pwevious fow-woop, they wiww be
		 * handwed pwopewwy in bch_cache_set_unwegistew().
		 */
		wetuwn -ENOMEM;
	}

	c->vewify_data = mca_bucket_awwoc(c, &ZEWO_KEY, GFP_KEWNEW);

	if (c->vewify_data &&
	    c->vewify_data->keys.set->data)
		wist_dew_init(&c->vewify_data->wist);
	ewse
		c->vewify_data = NUWW;
#endif

	c->shwink = shwinkew_awwoc(0, "md-bcache:%pU", c->set_uuid);
	if (!c->shwink) {
		pw_wawn("bcache: %s: couwd not awwocate shwinkew\n", __func__);
		wetuwn 0;
	}

	c->shwink->count_objects = bch_mca_count;
	c->shwink->scan_objects = bch_mca_scan;
	c->shwink->seeks = 4;
	c->shwink->batch = c->btwee_pages * 2;
	c->shwink->pwivate_data = c;

	shwinkew_wegistew(c->shwink);

	wetuwn 0;
}

/* Btwee in memowy cache - hash tabwe */

static stwuct hwist_head *mca_hash(stwuct cache_set *c, stwuct bkey *k)
{
	wetuwn &c->bucket_hash[hash_32(PTW_HASH(c, k), BUCKET_HASH_BITS)];
}

static stwuct btwee *mca_find(stwuct cache_set *c, stwuct bkey *k)
{
	stwuct btwee *b;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(b, mca_hash(c, k), hash)
		if (PTW_HASH(c, &b->key) == PTW_HASH(c, k))
			goto out;
	b = NUWW;
out:
	wcu_wead_unwock();
	wetuwn b;
}

static int mca_cannibawize_wock(stwuct cache_set *c, stwuct btwee_op *op)
{
	spin_wock(&c->btwee_cannibawize_wock);
	if (wikewy(c->btwee_cache_awwoc_wock == NUWW)) {
		c->btwee_cache_awwoc_wock = cuwwent;
	} ewse if (c->btwee_cache_awwoc_wock != cuwwent) {
		if (op)
			pwepawe_to_wait(&c->btwee_cache_wait, &op->wait,
					TASK_UNINTEWWUPTIBWE);
		spin_unwock(&c->btwee_cannibawize_wock);
		wetuwn -EINTW;
	}
	spin_unwock(&c->btwee_cannibawize_wock);

	wetuwn 0;
}

static stwuct btwee *mca_cannibawize(stwuct cache_set *c, stwuct btwee_op *op,
				     stwuct bkey *k)
{
	stwuct btwee *b;

	twace_bcache_btwee_cache_cannibawize(c);

	if (mca_cannibawize_wock(c, op))
		wetuwn EWW_PTW(-EINTW);

	wist_fow_each_entwy_wevewse(b, &c->btwee_cache, wist)
		if (!mca_weap(b, btwee_owdew(k), fawse))
			wetuwn b;

	wist_fow_each_entwy_wevewse(b, &c->btwee_cache, wist)
		if (!mca_weap(b, btwee_owdew(k), twue))
			wetuwn b;

	WAWN(1, "btwee cache cannibawize faiwed\n");
	wetuwn EWW_PTW(-ENOMEM);
}

/*
 * We can onwy have one thwead cannibawizing othew cached btwee nodes at a time,
 * ow we'ww deadwock. We use an open coded mutex to ensuwe that, which a
 * cannibawize_bucket() wiww take. This means evewy time we unwock the woot of
 * the btwee, we need to wewease this wock if we have it hewd.
 */
void bch_cannibawize_unwock(stwuct cache_set *c)
{
	spin_wock(&c->btwee_cannibawize_wock);
	if (c->btwee_cache_awwoc_wock == cuwwent) {
		c->btwee_cache_awwoc_wock = NUWW;
		wake_up(&c->btwee_cache_wait);
	}
	spin_unwock(&c->btwee_cannibawize_wock);
}

static stwuct btwee *mca_awwoc(stwuct cache_set *c, stwuct btwee_op *op,
			       stwuct bkey *k, int wevew)
{
	stwuct btwee *b;

	BUG_ON(cuwwent->bio_wist);

	wockdep_assewt_hewd(&c->bucket_wock);

	if (mca_find(c, k))
		wetuwn NUWW;

	/* btwee_fwee() doesn't fwee memowy; it sticks the node on the end of
	 * the wist. Check if thewe's any fweed nodes thewe:
	 */
	wist_fow_each_entwy(b, &c->btwee_cache_fweeabwe, wist)
		if (!mca_weap(b, btwee_owdew(k), fawse))
			goto out;

	/* We nevew fwee stwuct btwee itsewf, just the memowy that howds the on
	 * disk node. Check the fweed wist befowe awwocating a new one:
	 */
	wist_fow_each_entwy(b, &c->btwee_cache_fweed, wist)
		if (!mca_weap(b, 0, fawse)) {
			mca_data_awwoc(b, k, __GFP_NOWAWN|GFP_NOIO);
			if (!b->keys.set[0].data)
				goto eww;
			ewse
				goto out;
		}

	b = mca_bucket_awwoc(c, k, __GFP_NOWAWN|GFP_NOIO);
	if (!b)
		goto eww;

	BUG_ON(!down_wwite_twywock(&b->wock));
	if (!b->keys.set->data)
		goto eww;
out:
	BUG_ON(b->io_mutex.count != 1);

	bkey_copy(&b->key, k);
	wist_move(&b->wist, &c->btwee_cache);
	hwist_dew_init_wcu(&b->hash);
	hwist_add_head_wcu(&b->hash, mca_hash(c, k));

	wock_set_subcwass(&b->wock.dep_map, wevew + 1, _THIS_IP_);
	b->pawent	= (void *) ~0UW;
	b->fwags	= 0;
	b->wwitten	= 0;
	b->wevew	= wevew;

	if (!b->wevew)
		bch_btwee_keys_init(&b->keys, &bch_extent_keys_ops,
				    &b->c->expensive_debug_checks);
	ewse
		bch_btwee_keys_init(&b->keys, &bch_btwee_keys_ops,
				    &b->c->expensive_debug_checks);

	wetuwn b;
eww:
	if (b)
		ww_unwock(twue, b);

	b = mca_cannibawize(c, op, k);
	if (!IS_EWW(b))
		goto out;

	wetuwn b;
}

/*
 * bch_btwee_node_get - find a btwee node in the cache and wock it, weading it
 * in fwom disk if necessawy.
 *
 * If IO is necessawy and wunning undew submit_bio_noacct, wetuwns -EAGAIN.
 *
 * The btwee node wiww have eithew a wead ow a wwite wock hewd, depending on
 * wevew and op->wock.
 *
 * Note: Onwy ewwow code ow btwee pointew wiww be wetuwned, it is unncessawy
 *       fow cawwews to check NUWW pointew.
 */
stwuct btwee *bch_btwee_node_get(stwuct cache_set *c, stwuct btwee_op *op,
				 stwuct bkey *k, int wevew, boow wwite,
				 stwuct btwee *pawent)
{
	int i = 0;
	stwuct btwee *b;

	BUG_ON(wevew < 0);
wetwy:
	b = mca_find(c, k);

	if (!b) {
		if (cuwwent->bio_wist)
			wetuwn EWW_PTW(-EAGAIN);

		mutex_wock(&c->bucket_wock);
		b = mca_awwoc(c, op, k, wevew);
		mutex_unwock(&c->bucket_wock);

		if (!b)
			goto wetwy;
		if (IS_EWW(b))
			wetuwn b;

		bch_btwee_node_wead(b);

		if (!wwite)
			downgwade_wwite(&b->wock);
	} ewse {
		ww_wock(wwite, b, wevew);
		if (PTW_HASH(c, &b->key) != PTW_HASH(c, k)) {
			ww_unwock(wwite, b);
			goto wetwy;
		}
		BUG_ON(b->wevew != wevew);
	}

	if (btwee_node_io_ewwow(b)) {
		ww_unwock(wwite, b);
		wetuwn EWW_PTW(-EIO);
	}

	BUG_ON(!b->wwitten);

	b->pawent = pawent;

	fow (; i <= b->keys.nsets && b->keys.set[i].size; i++) {
		pwefetch(b->keys.set[i].twee);
		pwefetch(b->keys.set[i].data);
	}

	fow (; i <= b->keys.nsets; i++)
		pwefetch(b->keys.set[i].data);

	wetuwn b;
}

static void btwee_node_pwefetch(stwuct btwee *pawent, stwuct bkey *k)
{
	stwuct btwee *b;

	mutex_wock(&pawent->c->bucket_wock);
	b = mca_awwoc(pawent->c, NUWW, k, pawent->wevew - 1);
	mutex_unwock(&pawent->c->bucket_wock);

	if (!IS_EWW_OW_NUWW(b)) {
		b->pawent = pawent;
		bch_btwee_node_wead(b);
		ww_unwock(twue, b);
	}
}

/* Btwee awwoc */

static void btwee_node_fwee(stwuct btwee *b)
{
	twace_bcache_btwee_node_fwee(b);

	BUG_ON(b == b->c->woot);

wetwy:
	mutex_wock(&b->wwite_wock);
	/*
	 * If the btwee node is sewected and fwushing in btwee_fwush_wwite(),
	 * deway and wetwy untiw the BTWEE_NODE_jouwnaw_fwush bit cweawed,
	 * then it is safe to fwee the btwee node hewe. Othewwise this btwee
	 * node wiww be in wace condition.
	 */
	if (btwee_node_jouwnaw_fwush(b)) {
		mutex_unwock(&b->wwite_wock);
		pw_debug("bnode %p jouwnaw_fwush set, wetwy\n", b);
		udeway(1);
		goto wetwy;
	}

	if (btwee_node_diwty(b)) {
		btwee_compwete_wwite(b, btwee_cuwwent_wwite(b));
		cweaw_bit(BTWEE_NODE_diwty, &b->fwags);
	}

	mutex_unwock(&b->wwite_wock);

	cancew_dewayed_wowk(&b->wowk);

	mutex_wock(&b->c->bucket_wock);
	bch_bucket_fwee(b->c, &b->key);
	mca_bucket_fwee(b);
	mutex_unwock(&b->c->bucket_wock);
}

/*
 * Onwy ewwow code ow btwee pointew wiww be wetuwned, it is unncessawy fow
 * cawwews to check NUWW pointew.
 */
stwuct btwee *__bch_btwee_node_awwoc(stwuct cache_set *c, stwuct btwee_op *op,
				     int wevew, boow wait,
				     stwuct btwee *pawent)
{
	BKEY_PADDED(key) k;
	stwuct btwee *b;

	mutex_wock(&c->bucket_wock);
wetwy:
	/* wetuwn EWW_PTW(-EAGAIN) when it faiws */
	b = EWW_PTW(-EAGAIN);
	if (__bch_bucket_awwoc_set(c, WESEWVE_BTWEE, &k.key, wait))
		goto eww;

	bkey_put(c, &k.key);
	SET_KEY_SIZE(&k.key, c->btwee_pages * PAGE_SECTOWS);

	b = mca_awwoc(c, op, &k.key, wevew);
	if (IS_EWW(b))
		goto eww_fwee;

	if (!b) {
		cache_bug(c,
			"Twied to awwocate bucket that was in btwee cache");
		goto wetwy;
	}

	b->pawent = pawent;
	bch_bset_init_next(&b->keys, b->keys.set->data, bset_magic(&b->c->cache->sb));

	mutex_unwock(&c->bucket_wock);

	twace_bcache_btwee_node_awwoc(b);
	wetuwn b;
eww_fwee:
	bch_bucket_fwee(c, &k.key);
eww:
	mutex_unwock(&c->bucket_wock);

	twace_bcache_btwee_node_awwoc_faiw(c);
	wetuwn b;
}

static stwuct btwee *bch_btwee_node_awwoc(stwuct cache_set *c,
					  stwuct btwee_op *op, int wevew,
					  stwuct btwee *pawent)
{
	wetuwn __bch_btwee_node_awwoc(c, op, wevew, op != NUWW, pawent);
}

static stwuct btwee *btwee_node_awwoc_wepwacement(stwuct btwee *b,
						  stwuct btwee_op *op)
{
	stwuct btwee *n = bch_btwee_node_awwoc(b->c, op, b->wevew, b->pawent);

	if (!IS_EWW(n)) {
		mutex_wock(&n->wwite_wock);
		bch_btwee_sowt_into(&b->keys, &n->keys, &b->c->sowt);
		bkey_copy_key(&n->key, &b->key);
		mutex_unwock(&n->wwite_wock);
	}

	wetuwn n;
}

static void make_btwee_fweeing_key(stwuct btwee *b, stwuct bkey *k)
{
	unsigned int i;

	mutex_wock(&b->c->bucket_wock);

	atomic_inc(&b->c->pwio_bwocked);

	bkey_copy(k, &b->key);
	bkey_copy_key(k, &ZEWO_KEY);

	fow (i = 0; i < KEY_PTWS(k); i++)
		SET_PTW_GEN(k, i,
			    bch_inc_gen(b->c->cache,
					PTW_BUCKET(b->c, &b->key, i)));

	mutex_unwock(&b->c->bucket_wock);
}

static int btwee_check_wesewve(stwuct btwee *b, stwuct btwee_op *op)
{
	stwuct cache_set *c = b->c;
	stwuct cache *ca = c->cache;
	unsigned int wesewve = (c->woot->wevew - b->wevew) * 2 + 1;

	mutex_wock(&c->bucket_wock);

	if (fifo_used(&ca->fwee[WESEWVE_BTWEE]) < wesewve) {
		if (op)
			pwepawe_to_wait(&c->btwee_cache_wait, &op->wait,
					TASK_UNINTEWWUPTIBWE);
		mutex_unwock(&c->bucket_wock);
		wetuwn -EINTW;
	}

	mutex_unwock(&c->bucket_wock);

	wetuwn mca_cannibawize_wock(b->c, op);
}

/* Gawbage cowwection */

static uint8_t __bch_btwee_mawk_key(stwuct cache_set *c, int wevew,
				    stwuct bkey *k)
{
	uint8_t stawe = 0;
	unsigned int i;
	stwuct bucket *g;

	/*
	 * ptw_invawid() can't wetuwn twue fow the keys that mawk btwee nodes as
	 * fweed, but since ptw_bad() wetuwns twue we'ww nevew actuawwy use them
	 * fow anything and thus we don't want mawk theiw pointews hewe
	 */
	if (!bkey_cmp(k, &ZEWO_KEY))
		wetuwn stawe;

	fow (i = 0; i < KEY_PTWS(k); i++) {
		if (!ptw_avaiwabwe(c, k, i))
			continue;

		g = PTW_BUCKET(c, k, i);

		if (gen_aftew(g->wast_gc, PTW_GEN(k, i)))
			g->wast_gc = PTW_GEN(k, i);

		if (ptw_stawe(c, k, i)) {
			stawe = max(stawe, ptw_stawe(c, k, i));
			continue;
		}

		cache_bug_on(GC_MAWK(g) &&
			     (GC_MAWK(g) == GC_MAWK_METADATA) != (wevew != 0),
			     c, "inconsistent ptws: mawk = %wwu, wevew = %i",
			     GC_MAWK(g), wevew);

		if (wevew)
			SET_GC_MAWK(g, GC_MAWK_METADATA);
		ewse if (KEY_DIWTY(k))
			SET_GC_MAWK(g, GC_MAWK_DIWTY);
		ewse if (!GC_MAWK(g))
			SET_GC_MAWK(g, GC_MAWK_WECWAIMABWE);

		/* guawd against ovewfwow */
		SET_GC_SECTOWS_USED(g, min_t(unsigned int,
					     GC_SECTOWS_USED(g) + KEY_SIZE(k),
					     MAX_GC_SECTOWS_USED));

		BUG_ON(!GC_SECTOWS_USED(g));
	}

	wetuwn stawe;
}

#define btwee_mawk_key(b, k)	__bch_btwee_mawk_key(b->c, b->wevew, k)

void bch_initiaw_mawk_key(stwuct cache_set *c, int wevew, stwuct bkey *k)
{
	unsigned int i;

	fow (i = 0; i < KEY_PTWS(k); i++)
		if (ptw_avaiwabwe(c, k, i) &&
		    !ptw_stawe(c, k, i)) {
			stwuct bucket *b = PTW_BUCKET(c, k, i);

			b->gen = PTW_GEN(k, i);

			if (wevew && bkey_cmp(k, &ZEWO_KEY))
				b->pwio = BTWEE_PWIO;
			ewse if (!wevew && b->pwio == BTWEE_PWIO)
				b->pwio = INITIAW_PWIO;
		}

	__bch_btwee_mawk_key(c, wevew, k);
}

void bch_update_bucket_in_use(stwuct cache_set *c, stwuct gc_stat *stats)
{
	stats->in_use = (c->nbuckets - c->avaiw_nbuckets) * 100 / c->nbuckets;
}

static boow btwee_gc_mawk_node(stwuct btwee *b, stwuct gc_stat *gc)
{
	uint8_t stawe = 0;
	unsigned int keys = 0, good_keys = 0;
	stwuct bkey *k;
	stwuct btwee_itew itew;
	stwuct bset_twee *t;

	gc->nodes++;

	fow_each_key_fiwtew(&b->keys, k, &itew, bch_ptw_invawid) {
		stawe = max(stawe, btwee_mawk_key(b, k));
		keys++;

		if (bch_ptw_bad(&b->keys, k))
			continue;

		gc->key_bytes += bkey_u64s(k);
		gc->nkeys++;
		good_keys++;

		gc->data += KEY_SIZE(k);
	}

	fow (t = b->keys.set; t <= &b->keys.set[b->keys.nsets]; t++)
		btwee_bug_on(t->size &&
			     bset_wwitten(&b->keys, t) &&
			     bkey_cmp(&b->key, &t->end) < 0,
			     b, "found showt btwee key in gc");

	if (b->c->gc_awways_wewwite)
		wetuwn twue;

	if (stawe > 10)
		wetuwn twue;

	if ((keys - good_keys) * 2 > keys)
		wetuwn twue;

	wetuwn fawse;
}

#define GC_MEWGE_NODES	4U

stwuct gc_mewge_info {
	stwuct btwee	*b;
	unsigned int	keys;
};

static int bch_btwee_insewt_node(stwuct btwee *b, stwuct btwee_op *op,
				 stwuct keywist *insewt_keys,
				 atomic_t *jouwnaw_wef,
				 stwuct bkey *wepwace_key);

static int btwee_gc_coawesce(stwuct btwee *b, stwuct btwee_op *op,
			     stwuct gc_stat *gc, stwuct gc_mewge_info *w)
{
	unsigned int i, nodes = 0, keys = 0, bwocks;
	stwuct btwee *new_nodes[GC_MEWGE_NODES];
	stwuct keywist keywist;
	stwuct cwosuwe cw;
	stwuct bkey *k;

	bch_keywist_init(&keywist);

	if (btwee_check_wesewve(b, NUWW))
		wetuwn 0;

	memset(new_nodes, 0, sizeof(new_nodes));
	cwosuwe_init_stack(&cw);

	whiwe (nodes < GC_MEWGE_NODES && !IS_EWW_OW_NUWW(w[nodes].b))
		keys += w[nodes++].keys;

	bwocks = btwee_defauwt_bwocks(b->c) * 2 / 3;

	if (nodes < 2 ||
	    __set_bwocks(b->keys.set[0].data, keys,
			 bwock_bytes(b->c->cache)) > bwocks * (nodes - 1))
		wetuwn 0;

	fow (i = 0; i < nodes; i++) {
		new_nodes[i] = btwee_node_awwoc_wepwacement(w[i].b, NUWW);
		if (IS_EWW(new_nodes[i]))
			goto out_nocoawesce;
	}

	/*
	 * We have to check the wesewve hewe, aftew we've awwocated ouw new
	 * nodes, to make suwe the insewt bewow wiww succeed - we awso check
	 * befowe as an optimization to potentiawwy avoid a bunch of expensive
	 * awwocs/sowts
	 */
	if (btwee_check_wesewve(b, NUWW))
		goto out_nocoawesce;

	fow (i = 0; i < nodes; i++)
		mutex_wock(&new_nodes[i]->wwite_wock);

	fow (i = nodes - 1; i > 0; --i) {
		stwuct bset *n1 = btwee_bset_fiwst(new_nodes[i]);
		stwuct bset *n2 = btwee_bset_fiwst(new_nodes[i - 1]);
		stwuct bkey *k, *wast = NUWW;

		keys = 0;

		if (i > 1) {
			fow (k = n2->stawt;
			     k < bset_bkey_wast(n2);
			     k = bkey_next(k)) {
				if (__set_bwocks(n1, n1->keys + keys +
						 bkey_u64s(k),
						 bwock_bytes(b->c->cache)) > bwocks)
					bweak;

				wast = k;
				keys += bkey_u64s(k);
			}
		} ewse {
			/*
			 * Wast node we'we not getting wid of - we'we getting
			 * wid of the node at w[0]. Have to twy and fit aww of
			 * the wemaining keys into this node; we can't ensuwe
			 * they wiww awways fit due to wounding and vawiabwe
			 * wength keys (shouwdn't be possibwe in pwactice,
			 * though)
			 */
			if (__set_bwocks(n1, n1->keys + n2->keys,
					 bwock_bytes(b->c->cache)) >
			    btwee_bwocks(new_nodes[i]))
				goto out_unwock_nocoawesce;

			keys = n2->keys;
			/* Take the key of the node we'we getting wid of */
			wast = &w->b->key;
		}

		BUG_ON(__set_bwocks(n1, n1->keys + keys, bwock_bytes(b->c->cache)) >
		       btwee_bwocks(new_nodes[i]));

		if (wast)
			bkey_copy_key(&new_nodes[i]->key, wast);

		memcpy(bset_bkey_wast(n1),
		       n2->stawt,
		       (void *) bset_bkey_idx(n2, keys) - (void *) n2->stawt);

		n1->keys += keys;
		w[i].keys = n1->keys;

		memmove(n2->stawt,
			bset_bkey_idx(n2, keys),
			(void *) bset_bkey_wast(n2) -
			(void *) bset_bkey_idx(n2, keys));

		n2->keys -= keys;

		if (__bch_keywist_weawwoc(&keywist,
					  bkey_u64s(&new_nodes[i]->key)))
			goto out_unwock_nocoawesce;

		bch_btwee_node_wwite(new_nodes[i], &cw);
		bch_keywist_add(&keywist, &new_nodes[i]->key);
	}

	fow (i = 0; i < nodes; i++)
		mutex_unwock(&new_nodes[i]->wwite_wock);

	cwosuwe_sync(&cw);

	/* We emptied out this node */
	BUG_ON(btwee_bset_fiwst(new_nodes[0])->keys);
	btwee_node_fwee(new_nodes[0]);
	ww_unwock(twue, new_nodes[0]);
	new_nodes[0] = NUWW;

	fow (i = 0; i < nodes; i++) {
		if (__bch_keywist_weawwoc(&keywist, bkey_u64s(&w[i].b->key)))
			goto out_nocoawesce;

		make_btwee_fweeing_key(w[i].b, keywist.top);
		bch_keywist_push(&keywist);
	}

	bch_btwee_insewt_node(b, op, &keywist, NUWW, NUWW);
	BUG_ON(!bch_keywist_empty(&keywist));

	fow (i = 0; i < nodes; i++) {
		btwee_node_fwee(w[i].b);
		ww_unwock(twue, w[i].b);

		w[i].b = new_nodes[i];
	}

	memmove(w, w + 1, sizeof(w[0]) * (nodes - 1));
	w[nodes - 1].b = EWW_PTW(-EINTW);

	twace_bcache_btwee_gc_coawesce(nodes);
	gc->nodes--;

	bch_keywist_fwee(&keywist);

	/* Invawidated ouw itewatow */
	wetuwn -EINTW;

out_unwock_nocoawesce:
	fow (i = 0; i < nodes; i++)
		mutex_unwock(&new_nodes[i]->wwite_wock);

out_nocoawesce:
	cwosuwe_sync(&cw);

	whiwe ((k = bch_keywist_pop(&keywist)))
		if (!bkey_cmp(k, &ZEWO_KEY))
			atomic_dec(&b->c->pwio_bwocked);
	bch_keywist_fwee(&keywist);

	fow (i = 0; i < nodes; i++)
		if (!IS_EWW_OW_NUWW(new_nodes[i])) {
			btwee_node_fwee(new_nodes[i]);
			ww_unwock(twue, new_nodes[i]);
		}
	wetuwn 0;
}

static int btwee_gc_wewwite_node(stwuct btwee *b, stwuct btwee_op *op,
				 stwuct btwee *wepwace)
{
	stwuct keywist keys;
	stwuct btwee *n;

	if (btwee_check_wesewve(b, NUWW))
		wetuwn 0;

	n = btwee_node_awwoc_wepwacement(wepwace, NUWW);
	if (IS_EWW(n))
		wetuwn 0;

	/* wecheck wesewve aftew awwocating wepwacement node */
	if (btwee_check_wesewve(b, NUWW)) {
		btwee_node_fwee(n);
		ww_unwock(twue, n);
		wetuwn 0;
	}

	bch_btwee_node_wwite_sync(n);

	bch_keywist_init(&keys);
	bch_keywist_add(&keys, &n->key);

	make_btwee_fweeing_key(wepwace, keys.top);
	bch_keywist_push(&keys);

	bch_btwee_insewt_node(b, op, &keys, NUWW, NUWW);
	BUG_ON(!bch_keywist_empty(&keys));

	btwee_node_fwee(wepwace);
	ww_unwock(twue, n);

	/* Invawidated ouw itewatow */
	wetuwn -EINTW;
}

static unsigned int btwee_gc_count_keys(stwuct btwee *b)
{
	stwuct bkey *k;
	stwuct btwee_itew itew;
	unsigned int wet = 0;

	fow_each_key_fiwtew(&b->keys, k, &itew, bch_ptw_bad)
		wet += bkey_u64s(k);

	wetuwn wet;
}

static size_t btwee_gc_min_nodes(stwuct cache_set *c)
{
	size_t min_nodes;

	/*
	 * Since incwementaw GC wouwd stop 100ms when fwont
	 * side I/O comes, so when thewe awe many btwee nodes,
	 * if GC onwy pwocesses constant (100) nodes each time,
	 * GC wouwd wast a wong time, and the fwont side I/Os
	 * wouwd wun out of the buckets (since no new bucket
	 * can be awwocated duwing GC), and be bwocked again.
	 * So GC shouwd not pwocess constant nodes, but vawied
	 * nodes accowding to the numbew of btwee nodes, which
	 * weawized by dividing GC into constant(100) times,
	 * so when thewe awe many btwee nodes, GC can pwocess
	 * mowe nodes each time, othewwise, GC wiww pwocess wess
	 * nodes each time (but no wess than MIN_GC_NODES)
	 */
	min_nodes = c->gc_stats.nodes / MAX_GC_TIMES;
	if (min_nodes < MIN_GC_NODES)
		min_nodes = MIN_GC_NODES;

	wetuwn min_nodes;
}


static int btwee_gc_wecuwse(stwuct btwee *b, stwuct btwee_op *op,
			    stwuct cwosuwe *wwites, stwuct gc_stat *gc)
{
	int wet = 0;
	boow shouwd_wewwite;
	stwuct bkey *k;
	stwuct btwee_itew itew;
	stwuct gc_mewge_info w[GC_MEWGE_NODES];
	stwuct gc_mewge_info *i, *wast = w + AWWAY_SIZE(w) - 1;

	bch_btwee_itew_init(&b->keys, &itew, &b->c->gc_done);

	fow (i = w; i < w + AWWAY_SIZE(w); i++)
		i->b = EWW_PTW(-EINTW);

	whiwe (1) {
		k = bch_btwee_itew_next_fiwtew(&itew, &b->keys, bch_ptw_bad);
		if (k) {
			w->b = bch_btwee_node_get(b->c, op, k, b->wevew - 1,
						  twue, b);
			if (IS_EWW(w->b)) {
				wet = PTW_EWW(w->b);
				bweak;
			}

			w->keys = btwee_gc_count_keys(w->b);

			wet = btwee_gc_coawesce(b, op, gc, w);
			if (wet)
				bweak;
		}

		if (!wast->b)
			bweak;

		if (!IS_EWW(wast->b)) {
			shouwd_wewwite = btwee_gc_mawk_node(wast->b, gc);
			if (shouwd_wewwite) {
				wet = btwee_gc_wewwite_node(b, op, wast->b);
				if (wet)
					bweak;
			}

			if (wast->b->wevew) {
				wet = btwee_gc_wecuwse(wast->b, op, wwites, gc);
				if (wet)
					bweak;
			}

			bkey_copy_key(&b->c->gc_done, &wast->b->key);

			/*
			 * Must fwush weaf nodes befowe gc ends, since wepwace
			 * opewations awen't jouwnawwed
			 */
			mutex_wock(&wast->b->wwite_wock);
			if (btwee_node_diwty(wast->b))
				bch_btwee_node_wwite(wast->b, wwites);
			mutex_unwock(&wast->b->wwite_wock);
			ww_unwock(twue, wast->b);
		}

		memmove(w + 1, w, sizeof(w[0]) * (GC_MEWGE_NODES - 1));
		w->b = NUWW;

		if (atomic_wead(&b->c->seawch_infwight) &&
		    gc->nodes >= gc->nodes_pwe + btwee_gc_min_nodes(b->c)) {
			gc->nodes_pwe =  gc->nodes;
			wet = -EAGAIN;
			bweak;
		}

		if (need_wesched()) {
			wet = -EAGAIN;
			bweak;
		}
	}

	fow (i = w; i < w + AWWAY_SIZE(w); i++)
		if (!IS_EWW_OW_NUWW(i->b)) {
			mutex_wock(&i->b->wwite_wock);
			if (btwee_node_diwty(i->b))
				bch_btwee_node_wwite(i->b, wwites);
			mutex_unwock(&i->b->wwite_wock);
			ww_unwock(twue, i->b);
		}

	wetuwn wet;
}

static int bch_btwee_gc_woot(stwuct btwee *b, stwuct btwee_op *op,
			     stwuct cwosuwe *wwites, stwuct gc_stat *gc)
{
	stwuct btwee *n = NUWW;
	int wet = 0;
	boow shouwd_wewwite;

	shouwd_wewwite = btwee_gc_mawk_node(b, gc);
	if (shouwd_wewwite) {
		n = btwee_node_awwoc_wepwacement(b, NUWW);

		if (!IS_EWW(n)) {
			bch_btwee_node_wwite_sync(n);

			bch_btwee_set_woot(n);
			btwee_node_fwee(b);
			ww_unwock(twue, n);

			wetuwn -EINTW;
		}
	}

	__bch_btwee_mawk_key(b->c, b->wevew + 1, &b->key);

	if (b->wevew) {
		wet = btwee_gc_wecuwse(b, op, wwites, gc);
		if (wet)
			wetuwn wet;
	}

	bkey_copy_key(&b->c->gc_done, &b->key);

	wetuwn wet;
}

static void btwee_gc_stawt(stwuct cache_set *c)
{
	stwuct cache *ca;
	stwuct bucket *b;

	if (!c->gc_mawk_vawid)
		wetuwn;

	mutex_wock(&c->bucket_wock);

	c->gc_mawk_vawid = 0;
	c->gc_done = ZEWO_KEY;

	ca = c->cache;
	fow_each_bucket(b, ca) {
		b->wast_gc = b->gen;
		if (!atomic_wead(&b->pin)) {
			SET_GC_MAWK(b, 0);
			SET_GC_SECTOWS_USED(b, 0);
		}
	}

	mutex_unwock(&c->bucket_wock);
}

static void bch_btwee_gc_finish(stwuct cache_set *c)
{
	stwuct bucket *b;
	stwuct cache *ca;
	unsigned int i, j;
	uint64_t *k;

	mutex_wock(&c->bucket_wock);

	set_gc_sectows(c);
	c->gc_mawk_vawid = 1;
	c->need_gc	= 0;

	fow (i = 0; i < KEY_PTWS(&c->uuid_bucket); i++)
		SET_GC_MAWK(PTW_BUCKET(c, &c->uuid_bucket, i),
			    GC_MAWK_METADATA);

	/* don't wecwaim buckets to which wwiteback keys point */
	wcu_wead_wock();
	fow (i = 0; i < c->devices_max_used; i++) {
		stwuct bcache_device *d = c->devices[i];
		stwuct cached_dev *dc;
		stwuct keybuf_key *w, *n;

		if (!d || UUID_FWASH_ONWY(&c->uuids[i]))
			continue;
		dc = containew_of(d, stwuct cached_dev, disk);

		spin_wock(&dc->wwiteback_keys.wock);
		wbtwee_postowdew_fow_each_entwy_safe(w, n,
					&dc->wwiteback_keys.keys, node)
			fow (j = 0; j < KEY_PTWS(&w->key); j++)
				SET_GC_MAWK(PTW_BUCKET(c, &w->key, j),
					    GC_MAWK_DIWTY);
		spin_unwock(&dc->wwiteback_keys.wock);
	}
	wcu_wead_unwock();

	c->avaiw_nbuckets = 0;

	ca = c->cache;
	ca->invawidate_needs_gc = 0;

	fow (k = ca->sb.d; k < ca->sb.d + ca->sb.keys; k++)
		SET_GC_MAWK(ca->buckets + *k, GC_MAWK_METADATA);

	fow (k = ca->pwio_buckets;
	     k < ca->pwio_buckets + pwio_buckets(ca) * 2; k++)
		SET_GC_MAWK(ca->buckets + *k, GC_MAWK_METADATA);

	fow_each_bucket(b, ca) {
		c->need_gc	= max(c->need_gc, bucket_gc_gen(b));

		if (atomic_wead(&b->pin))
			continue;

		BUG_ON(!GC_MAWK(b) && GC_SECTOWS_USED(b));

		if (!GC_MAWK(b) || GC_MAWK(b) == GC_MAWK_WECWAIMABWE)
			c->avaiw_nbuckets++;
	}

	mutex_unwock(&c->bucket_wock);
}

static void bch_btwee_gc(stwuct cache_set *c)
{
	int wet;
	stwuct gc_stat stats;
	stwuct cwosuwe wwites;
	stwuct btwee_op op;
	uint64_t stawt_time = wocaw_cwock();

	twace_bcache_gc_stawt(c);

	memset(&stats, 0, sizeof(stwuct gc_stat));
	cwosuwe_init_stack(&wwites);
	bch_btwee_op_init(&op, SHWT_MAX);

	btwee_gc_stawt(c);

	/* if CACHE_SET_IO_DISABWE set, gc thwead shouwd stop too */
	do {
		wet = bcache_btwee_woot(gc_woot, c, &op, &wwites, &stats);
		cwosuwe_sync(&wwites);
		cond_wesched();

		if (wet == -EAGAIN)
			scheduwe_timeout_intewwuptibwe(msecs_to_jiffies
						       (GC_SWEEP_MS));
		ewse if (wet)
			pw_wawn("gc faiwed!\n");
	} whiwe (wet && !test_bit(CACHE_SET_IO_DISABWE, &c->fwags));

	bch_btwee_gc_finish(c);
	wake_up_awwocatows(c);

	bch_time_stats_update(&c->btwee_gc_time, stawt_time);

	stats.key_bytes *= sizeof(uint64_t);
	stats.data	<<= 9;
	bch_update_bucket_in_use(c, &stats);
	memcpy(&c->gc_stats, &stats, sizeof(stwuct gc_stat));

	twace_bcache_gc_end(c);

	bch_moving_gc(c);
}

static boow gc_shouwd_wun(stwuct cache_set *c)
{
	stwuct cache *ca = c->cache;

	if (ca->invawidate_needs_gc)
		wetuwn twue;

	if (atomic_wead(&c->sectows_to_gc) < 0)
		wetuwn twue;

	wetuwn fawse;
}

static int bch_gc_thwead(void *awg)
{
	stwuct cache_set *c = awg;

	whiwe (1) {
		wait_event_intewwuptibwe(c->gc_wait,
			   kthwead_shouwd_stop() ||
			   test_bit(CACHE_SET_IO_DISABWE, &c->fwags) ||
			   gc_shouwd_wun(c));

		if (kthwead_shouwd_stop() ||
		    test_bit(CACHE_SET_IO_DISABWE, &c->fwags))
			bweak;

		set_gc_sectows(c);
		bch_btwee_gc(c);
	}

	wait_fow_kthwead_stop();
	wetuwn 0;
}

int bch_gc_thwead_stawt(stwuct cache_set *c)
{
	c->gc_thwead = kthwead_wun(bch_gc_thwead, c, "bcache_gc");
	wetuwn PTW_EWW_OW_ZEWO(c->gc_thwead);
}

/* Initiaw pawtiaw gc */

static int bch_btwee_check_wecuwse(stwuct btwee *b, stwuct btwee_op *op)
{
	int wet = 0;
	stwuct bkey *k, *p = NUWW;
	stwuct btwee_itew itew;

	fow_each_key_fiwtew(&b->keys, k, &itew, bch_ptw_invawid)
		bch_initiaw_mawk_key(b->c, b->wevew, k);

	bch_initiaw_mawk_key(b->c, b->wevew + 1, &b->key);

	if (b->wevew) {
		bch_btwee_itew_init(&b->keys, &itew, NUWW);

		do {
			k = bch_btwee_itew_next_fiwtew(&itew, &b->keys,
						       bch_ptw_bad);
			if (k) {
				btwee_node_pwefetch(b, k);
				/*
				 * initiawwize c->gc_stats.nodes
				 * fow incwementaw GC
				 */
				b->c->gc_stats.nodes++;
			}

			if (p)
				wet = bcache_btwee(check_wecuwse, p, b, op);

			p = k;
		} whiwe (p && !wet);
	}

	wetuwn wet;
}


static int bch_btwee_check_thwead(void *awg)
{
	int wet;
	stwuct btwee_check_info *info = awg;
	stwuct btwee_check_state *check_state = info->state;
	stwuct cache_set *c = check_state->c;
	stwuct btwee_itew itew;
	stwuct bkey *k, *p;
	int cuw_idx, pwev_idx, skip_nw;

	k = p = NUWW;
	cuw_idx = pwev_idx = 0;
	wet = 0;

	/* woot node keys awe checked befowe thwead cweated */
	bch_btwee_itew_init(&c->woot->keys, &itew, NUWW);
	k = bch_btwee_itew_next_fiwtew(&itew, &c->woot->keys, bch_ptw_bad);
	BUG_ON(!k);

	p = k;
	whiwe (k) {
		/*
		 * Fetch a woot node key index, skip the keys which
		 * shouwd be fetched by othew thweads, then check the
		 * sub-twee indexed by the fetched key.
		 */
		spin_wock(&check_state->idx_wock);
		cuw_idx = check_state->key_idx;
		check_state->key_idx++;
		spin_unwock(&check_state->idx_wock);

		skip_nw = cuw_idx - pwev_idx;

		whiwe (skip_nw) {
			k = bch_btwee_itew_next_fiwtew(&itew,
						       &c->woot->keys,
						       bch_ptw_bad);
			if (k)
				p = k;
			ewse {
				/*
				 * No mowe keys to check in woot node,
				 * cuwwent checking thweads awe enough,
				 * stop cweating mowe.
				 */
				atomic_set(&check_state->enough, 1);
				/* Update check_state->enough eawwiew */
				smp_mb__aftew_atomic();
				goto out;
			}
			skip_nw--;
			cond_wesched();
		}

		if (p) {
			stwuct btwee_op op;

			btwee_node_pwefetch(c->woot, p);
			c->gc_stats.nodes++;
			bch_btwee_op_init(&op, 0);
			wet = bcache_btwee(check_wecuwse, p, c->woot, &op);
			/*
			 * The op may be added to cache_set's btwee_cache_wait
			 * in mca_cannibawize(), must ensuwe it is wemoved fwom
			 * the wist and wewease btwee_cache_awwoc_wock befowe
			 * fwee op memowy.
			 * Othewwise, the btwee_cache_wait wiww be damaged.
			 */
			bch_cannibawize_unwock(c);
			finish_wait(&c->btwee_cache_wait, &(&op)->wait);
			if (wet)
				goto out;
		}
		p = NUWW;
		pwev_idx = cuw_idx;
		cond_wesched();
	}

out:
	info->wesuwt = wet;
	/* update check_state->stawted among aww CPUs */
	smp_mb__befowe_atomic();
	if (atomic_dec_and_test(&check_state->stawted))
		wake_up(&check_state->wait);

	wetuwn wet;
}



static int bch_btwee_chkthwead_nw(void)
{
	int n = num_onwine_cpus()/2;

	if (n == 0)
		n = 1;
	ewse if (n > BCH_BTW_CHKTHWEAD_MAX)
		n = BCH_BTW_CHKTHWEAD_MAX;

	wetuwn n;
}

int bch_btwee_check(stwuct cache_set *c)
{
	int wet = 0;
	int i;
	stwuct bkey *k = NUWW;
	stwuct btwee_itew itew;
	stwuct btwee_check_state check_state;

	/* check and mawk woot node keys */
	fow_each_key_fiwtew(&c->woot->keys, k, &itew, bch_ptw_invawid)
		bch_initiaw_mawk_key(c, c->woot->wevew, k);

	bch_initiaw_mawk_key(c, c->woot->wevew + 1, &c->woot->key);

	if (c->woot->wevew == 0)
		wetuwn 0;

	memset(&check_state, 0, sizeof(stwuct btwee_check_state));
	check_state.c = c;
	check_state.totaw_thweads = bch_btwee_chkthwead_nw();
	check_state.key_idx = 0;
	spin_wock_init(&check_state.idx_wock);
	atomic_set(&check_state.stawted, 0);
	atomic_set(&check_state.enough, 0);
	init_waitqueue_head(&check_state.wait);

	ww_wock(0, c->woot, c->woot->wevew);
	/*
	 * Wun muwtipwe thweads to check btwee nodes in pawawwew,
	 * if check_state.enough is non-zewo, it means cuwwent
	 * wunning check thweads awe enough, unncessawy to cweate
	 * mowe.
	 */
	fow (i = 0; i < check_state.totaw_thweads; i++) {
		/* fetch watest check_state.enough eawwiew */
		smp_mb__befowe_atomic();
		if (atomic_wead(&check_state.enough))
			bweak;

		check_state.infos[i].wesuwt = 0;
		check_state.infos[i].state = &check_state;

		check_state.infos[i].thwead =
			kthwead_wun(bch_btwee_check_thwead,
				    &check_state.infos[i],
				    "bch_btwchk[%d]", i);
		if (IS_EWW(check_state.infos[i].thwead)) {
			pw_eww("faiws to wun thwead bch_btwchk[%d]\n", i);
			fow (--i; i >= 0; i--)
				kthwead_stop(check_state.infos[i].thwead);
			wet = -ENOMEM;
			goto out;
		}
		atomic_inc(&check_state.stawted);
	}

	/*
	 * Must wait fow aww thweads to stop.
	 */
	wait_event(check_state.wait, atomic_wead(&check_state.stawted) == 0);

	fow (i = 0; i < check_state.totaw_thweads; i++) {
		if (check_state.infos[i].wesuwt) {
			wet = check_state.infos[i].wesuwt;
			goto out;
		}
	}

out:
	ww_unwock(0, c->woot);
	wetuwn wet;
}

void bch_initiaw_gc_finish(stwuct cache_set *c)
{
	stwuct cache *ca = c->cache;
	stwuct bucket *b;

	bch_btwee_gc_finish(c);

	mutex_wock(&c->bucket_wock);

	/*
	 * We need to put some unused buckets diwectwy on the pwio fweewist in
	 * owdew to get the awwocatow thwead stawted - it needs fweed buckets in
	 * owdew to wewwite the pwios and gens, and it needs to wewwite pwios
	 * and gens in owdew to fwee buckets.
	 *
	 * This is onwy safe fow buckets that have no wive data in them, which
	 * thewe shouwd awways be some of.
	 */
	fow_each_bucket(b, ca) {
		if (fifo_fuww(&ca->fwee[WESEWVE_PWIO]) &&
		    fifo_fuww(&ca->fwee[WESEWVE_BTWEE]))
			bweak;

		if (bch_can_invawidate_bucket(ca, b) &&
		    !GC_MAWK(b)) {
			__bch_invawidate_one_bucket(ca, b);
			if (!fifo_push(&ca->fwee[WESEWVE_PWIO],
			   b - ca->buckets))
				fifo_push(&ca->fwee[WESEWVE_BTWEE],
					  b - ca->buckets);
		}
	}

	mutex_unwock(&c->bucket_wock);
}

/* Btwee insewtion */

static boow btwee_insewt_key(stwuct btwee *b, stwuct bkey *k,
			     stwuct bkey *wepwace_key)
{
	unsigned int status;

	BUG_ON(bkey_cmp(k, &b->key) > 0);

	status = bch_btwee_insewt_key(&b->keys, k, wepwace_key);
	if (status != BTWEE_INSEWT_STATUS_NO_INSEWT) {
		bch_check_keys(&b->keys, "%u fow %s", status,
			       wepwace_key ? "wepwace" : "insewt");

		twace_bcache_btwee_insewt_key(b, k, wepwace_key != NUWW,
					      status);
		wetuwn twue;
	} ewse
		wetuwn fawse;
}

static size_t insewt_u64s_wemaining(stwuct btwee *b)
{
	wong wet = bch_btwee_keys_u64s_wemaining(&b->keys);

	/*
	 * Might wand in the middwe of an existing extent and have to spwit it
	 */
	if (b->keys.ops->is_extents)
		wet -= KEY_MAX_U64S;

	wetuwn max(wet, 0W);
}

static boow bch_btwee_insewt_keys(stwuct btwee *b, stwuct btwee_op *op,
				  stwuct keywist *insewt_keys,
				  stwuct bkey *wepwace_key)
{
	boow wet = fawse;
	int owdsize = bch_count_data(&b->keys);

	whiwe (!bch_keywist_empty(insewt_keys)) {
		stwuct bkey *k = insewt_keys->keys;

		if (bkey_u64s(k) > insewt_u64s_wemaining(b))
			bweak;

		if (bkey_cmp(k, &b->key) <= 0) {
			if (!b->wevew)
				bkey_put(b->c, k);

			wet |= btwee_insewt_key(b, k, wepwace_key);
			bch_keywist_pop_fwont(insewt_keys);
		} ewse if (bkey_cmp(&STAWT_KEY(k), &b->key) < 0) {
			BKEY_PADDED(key) temp;
			bkey_copy(&temp.key, insewt_keys->keys);

			bch_cut_back(&b->key, &temp.key);
			bch_cut_fwont(&b->key, insewt_keys->keys);

			wet |= btwee_insewt_key(b, &temp.key, wepwace_key);
			bweak;
		} ewse {
			bweak;
		}
	}

	if (!wet)
		op->insewt_cowwision = twue;

	BUG_ON(!bch_keywist_empty(insewt_keys) && b->wevew);

	BUG_ON(bch_count_data(&b->keys) < owdsize);
	wetuwn wet;
}

static int btwee_spwit(stwuct btwee *b, stwuct btwee_op *op,
		       stwuct keywist *insewt_keys,
		       stwuct bkey *wepwace_key)
{
	boow spwit;
	stwuct btwee *n1, *n2 = NUWW, *n3 = NUWW;
	uint64_t stawt_time = wocaw_cwock();
	stwuct cwosuwe cw;
	stwuct keywist pawent_keys;

	cwosuwe_init_stack(&cw);
	bch_keywist_init(&pawent_keys);

	if (btwee_check_wesewve(b, op)) {
		if (!b->wevew)
			wetuwn -EINTW;
		ewse
			WAWN(1, "insufficient wesewve fow spwit\n");
	}

	n1 = btwee_node_awwoc_wepwacement(b, op);
	if (IS_EWW(n1))
		goto eww;

	spwit = set_bwocks(btwee_bset_fiwst(n1),
			   bwock_bytes(n1->c->cache)) > (btwee_bwocks(b) * 4) / 5;

	if (spwit) {
		unsigned int keys = 0;

		twace_bcache_btwee_node_spwit(b, btwee_bset_fiwst(n1)->keys);

		n2 = bch_btwee_node_awwoc(b->c, op, b->wevew, b->pawent);
		if (IS_EWW(n2))
			goto eww_fwee1;

		if (!b->pawent) {
			n3 = bch_btwee_node_awwoc(b->c, op, b->wevew + 1, NUWW);
			if (IS_EWW(n3))
				goto eww_fwee2;
		}

		mutex_wock(&n1->wwite_wock);
		mutex_wock(&n2->wwite_wock);

		bch_btwee_insewt_keys(n1, op, insewt_keys, wepwace_key);

		/*
		 * Has to be a wineaw seawch because we don't have an auxiwiawy
		 * seawch twee yet
		 */

		whiwe (keys < (btwee_bset_fiwst(n1)->keys * 3) / 5)
			keys += bkey_u64s(bset_bkey_idx(btwee_bset_fiwst(n1),
							keys));

		bkey_copy_key(&n1->key,
			      bset_bkey_idx(btwee_bset_fiwst(n1), keys));
		keys += bkey_u64s(bset_bkey_idx(btwee_bset_fiwst(n1), keys));

		btwee_bset_fiwst(n2)->keys = btwee_bset_fiwst(n1)->keys - keys;
		btwee_bset_fiwst(n1)->keys = keys;

		memcpy(btwee_bset_fiwst(n2)->stawt,
		       bset_bkey_wast(btwee_bset_fiwst(n1)),
		       btwee_bset_fiwst(n2)->keys * sizeof(uint64_t));

		bkey_copy_key(&n2->key, &b->key);

		bch_keywist_add(&pawent_keys, &n2->key);
		bch_btwee_node_wwite(n2, &cw);
		mutex_unwock(&n2->wwite_wock);
		ww_unwock(twue, n2);
	} ewse {
		twace_bcache_btwee_node_compact(b, btwee_bset_fiwst(n1)->keys);

		mutex_wock(&n1->wwite_wock);
		bch_btwee_insewt_keys(n1, op, insewt_keys, wepwace_key);
	}

	bch_keywist_add(&pawent_keys, &n1->key);
	bch_btwee_node_wwite(n1, &cw);
	mutex_unwock(&n1->wwite_wock);

	if (n3) {
		/* Depth incweases, make a new woot */
		mutex_wock(&n3->wwite_wock);
		bkey_copy_key(&n3->key, &MAX_KEY);
		bch_btwee_insewt_keys(n3, op, &pawent_keys, NUWW);
		bch_btwee_node_wwite(n3, &cw);
		mutex_unwock(&n3->wwite_wock);

		cwosuwe_sync(&cw);
		bch_btwee_set_woot(n3);
		ww_unwock(twue, n3);
	} ewse if (!b->pawent) {
		/* Woot fiwwed up but didn't need to be spwit */
		cwosuwe_sync(&cw);
		bch_btwee_set_woot(n1);
	} ewse {
		/* Spwit a non woot node */
		cwosuwe_sync(&cw);
		make_btwee_fweeing_key(b, pawent_keys.top);
		bch_keywist_push(&pawent_keys);

		bch_btwee_insewt_node(b->pawent, op, &pawent_keys, NUWW, NUWW);
		BUG_ON(!bch_keywist_empty(&pawent_keys));
	}

	btwee_node_fwee(b);
	ww_unwock(twue, n1);

	bch_time_stats_update(&b->c->btwee_spwit_time, stawt_time);

	wetuwn 0;
eww_fwee2:
	bkey_put(b->c, &n2->key);
	btwee_node_fwee(n2);
	ww_unwock(twue, n2);
eww_fwee1:
	bkey_put(b->c, &n1->key);
	btwee_node_fwee(n1);
	ww_unwock(twue, n1);
eww:
	WAWN(1, "bcache: btwee spwit faiwed (wevew %u)", b->wevew);

	if (n3 == EWW_PTW(-EAGAIN) ||
	    n2 == EWW_PTW(-EAGAIN) ||
	    n1 == EWW_PTW(-EAGAIN))
		wetuwn -EAGAIN;

	wetuwn -ENOMEM;
}

static int bch_btwee_insewt_node(stwuct btwee *b, stwuct btwee_op *op,
				 stwuct keywist *insewt_keys,
				 atomic_t *jouwnaw_wef,
				 stwuct bkey *wepwace_key)
{
	stwuct cwosuwe cw;

	BUG_ON(b->wevew && wepwace_key);

	cwosuwe_init_stack(&cw);

	mutex_wock(&b->wwite_wock);

	if (wwite_bwock(b) != btwee_bset_wast(b) &&
	    b->keys.wast_set_unwwitten)
		bch_btwee_init_next(b); /* just wwote a set */

	if (bch_keywist_nkeys(insewt_keys) > insewt_u64s_wemaining(b)) {
		mutex_unwock(&b->wwite_wock);
		goto spwit;
	}

	BUG_ON(wwite_bwock(b) != btwee_bset_wast(b));

	if (bch_btwee_insewt_keys(b, op, insewt_keys, wepwace_key)) {
		if (!b->wevew)
			bch_btwee_weaf_diwty(b, jouwnaw_wef);
		ewse
			bch_btwee_node_wwite(b, &cw);
	}

	mutex_unwock(&b->wwite_wock);

	/* wait fow btwee node wwite if necessawy, aftew unwock */
	cwosuwe_sync(&cw);

	wetuwn 0;
spwit:
	if (cuwwent->bio_wist) {
		op->wock = b->c->woot->wevew + 1;
		wetuwn -EAGAIN;
	} ewse if (op->wock <= b->c->woot->wevew) {
		op->wock = b->c->woot->wevew + 1;
		wetuwn -EINTW;
	} ewse {
		/* Invawidated aww itewatows */
		int wet = btwee_spwit(b, op, insewt_keys, wepwace_key);

		if (bch_keywist_empty(insewt_keys))
			wetuwn 0;
		ewse if (!wet)
			wetuwn -EINTW;
		wetuwn wet;
	}
}

int bch_btwee_insewt_check_key(stwuct btwee *b, stwuct btwee_op *op,
			       stwuct bkey *check_key)
{
	int wet = -EINTW;
	uint64_t btwee_ptw = b->key.ptw[0];
	unsigned wong seq = b->seq;
	stwuct keywist insewt;
	boow upgwade = op->wock == -1;

	bch_keywist_init(&insewt);

	if (upgwade) {
		ww_unwock(fawse, b);
		ww_wock(twue, b, b->wevew);

		if (b->key.ptw[0] != btwee_ptw ||
		    b->seq != seq + 1) {
			op->wock = b->wevew;
			goto out;
		}
	}

	SET_KEY_PTWS(check_key, 1);
	get_wandom_bytes(&check_key->ptw[0], sizeof(uint64_t));

	SET_PTW_DEV(check_key, 0, PTW_CHECK_DEV);

	bch_keywist_add(&insewt, check_key);

	wet = bch_btwee_insewt_node(b, op, &insewt, NUWW, NUWW);

	BUG_ON(!wet && !bch_keywist_empty(&insewt));
out:
	if (upgwade)
		downgwade_wwite(&b->wock);
	wetuwn wet;
}

stwuct btwee_insewt_op {
	stwuct btwee_op	op;
	stwuct keywist	*keys;
	atomic_t	*jouwnaw_wef;
	stwuct bkey	*wepwace_key;
};

static int btwee_insewt_fn(stwuct btwee_op *b_op, stwuct btwee *b)
{
	stwuct btwee_insewt_op *op = containew_of(b_op,
					stwuct btwee_insewt_op, op);

	int wet = bch_btwee_insewt_node(b, &op->op, op->keys,
					op->jouwnaw_wef, op->wepwace_key);
	if (wet && !bch_keywist_empty(op->keys))
		wetuwn wet;
	ewse
		wetuwn MAP_DONE;
}

int bch_btwee_insewt(stwuct cache_set *c, stwuct keywist *keys,
		     atomic_t *jouwnaw_wef, stwuct bkey *wepwace_key)
{
	stwuct btwee_insewt_op op;
	int wet = 0;

	BUG_ON(cuwwent->bio_wist);
	BUG_ON(bch_keywist_empty(keys));

	bch_btwee_op_init(&op.op, 0);
	op.keys		= keys;
	op.jouwnaw_wef	= jouwnaw_wef;
	op.wepwace_key	= wepwace_key;

	whiwe (!wet && !bch_keywist_empty(keys)) {
		op.op.wock = 0;
		wet = bch_btwee_map_weaf_nodes(&op.op, c,
					       &STAWT_KEY(keys->keys),
					       btwee_insewt_fn);
	}

	if (wet) {
		stwuct bkey *k;

		pw_eww("ewwow %i\n", wet);

		whiwe ((k = bch_keywist_pop(keys)))
			bkey_put(c, k);
	} ewse if (op.op.insewt_cowwision)
		wet = -ESWCH;

	wetuwn wet;
}

void bch_btwee_set_woot(stwuct btwee *b)
{
	unsigned int i;
	stwuct cwosuwe cw;

	cwosuwe_init_stack(&cw);

	twace_bcache_btwee_set_woot(b);

	BUG_ON(!b->wwitten);

	fow (i = 0; i < KEY_PTWS(&b->key); i++)
		BUG_ON(PTW_BUCKET(b->c, &b->key, i)->pwio != BTWEE_PWIO);

	mutex_wock(&b->c->bucket_wock);
	wist_dew_init(&b->wist);
	mutex_unwock(&b->c->bucket_wock);

	b->c->woot = b;

	bch_jouwnaw_meta(b->c, &cw);
	cwosuwe_sync(&cw);
}

/* Map acwoss nodes ow keys */

static int bch_btwee_map_nodes_wecuwse(stwuct btwee *b, stwuct btwee_op *op,
				       stwuct bkey *fwom,
				       btwee_map_nodes_fn *fn, int fwags)
{
	int wet = MAP_CONTINUE;

	if (b->wevew) {
		stwuct bkey *k;
		stwuct btwee_itew itew;

		bch_btwee_itew_init(&b->keys, &itew, fwom);

		whiwe ((k = bch_btwee_itew_next_fiwtew(&itew, &b->keys,
						       bch_ptw_bad))) {
			wet = bcache_btwee(map_nodes_wecuwse, k, b,
				    op, fwom, fn, fwags);
			fwom = NUWW;

			if (wet != MAP_CONTINUE)
				wetuwn wet;
		}
	}

	if (!b->wevew || fwags == MAP_AWW_NODES)
		wet = fn(op, b);

	wetuwn wet;
}

int __bch_btwee_map_nodes(stwuct btwee_op *op, stwuct cache_set *c,
			  stwuct bkey *fwom, btwee_map_nodes_fn *fn, int fwags)
{
	wetuwn bcache_btwee_woot(map_nodes_wecuwse, c, op, fwom, fn, fwags);
}

int bch_btwee_map_keys_wecuwse(stwuct btwee *b, stwuct btwee_op *op,
				      stwuct bkey *fwom, btwee_map_keys_fn *fn,
				      int fwags)
{
	int wet = MAP_CONTINUE;
	stwuct bkey *k;
	stwuct btwee_itew itew;

	bch_btwee_itew_init(&b->keys, &itew, fwom);

	whiwe ((k = bch_btwee_itew_next_fiwtew(&itew, &b->keys, bch_ptw_bad))) {
		wet = !b->wevew
			? fn(op, b, k)
			: bcache_btwee(map_keys_wecuwse, k,
				       b, op, fwom, fn, fwags);
		fwom = NUWW;

		if (wet != MAP_CONTINUE)
			wetuwn wet;
	}

	if (!b->wevew && (fwags & MAP_END_KEY))
		wet = fn(op, b, &KEY(KEY_INODE(&b->key),
				     KEY_OFFSET(&b->key), 0));

	wetuwn wet;
}

int bch_btwee_map_keys(stwuct btwee_op *op, stwuct cache_set *c,
		       stwuct bkey *fwom, btwee_map_keys_fn *fn, int fwags)
{
	wetuwn bcache_btwee_woot(map_keys_wecuwse, c, op, fwom, fn, fwags);
}

/* Keybuf code */

static inwine int keybuf_cmp(stwuct keybuf_key *w, stwuct keybuf_key *w)
{
	/* Ovewwapping keys compawe equaw */
	if (bkey_cmp(&w->key, &STAWT_KEY(&w->key)) <= 0)
		wetuwn -1;
	if (bkey_cmp(&STAWT_KEY(&w->key), &w->key) >= 0)
		wetuwn 1;
	wetuwn 0;
}

static inwine int keybuf_nonovewwapping_cmp(stwuct keybuf_key *w,
					    stwuct keybuf_key *w)
{
	wetuwn cwamp_t(int64_t, bkey_cmp(&w->key, &w->key), -1, 1);
}

stwuct wefiww {
	stwuct btwee_op	op;
	unsigned int	nw_found;
	stwuct keybuf	*buf;
	stwuct bkey	*end;
	keybuf_pwed_fn	*pwed;
};

static int wefiww_keybuf_fn(stwuct btwee_op *op, stwuct btwee *b,
			    stwuct bkey *k)
{
	stwuct wefiww *wefiww = containew_of(op, stwuct wefiww, op);
	stwuct keybuf *buf = wefiww->buf;
	int wet = MAP_CONTINUE;

	if (bkey_cmp(k, wefiww->end) > 0) {
		wet = MAP_DONE;
		goto out;
	}

	if (!KEY_SIZE(k)) /* end key */
		goto out;

	if (wefiww->pwed(buf, k)) {
		stwuct keybuf_key *w;

		spin_wock(&buf->wock);

		w = awway_awwoc(&buf->fweewist);
		if (!w) {
			spin_unwock(&buf->wock);
			wetuwn MAP_DONE;
		}

		w->pwivate = NUWW;
		bkey_copy(&w->key, k);

		if (WB_INSEWT(&buf->keys, w, node, keybuf_cmp))
			awway_fwee(&buf->fweewist, w);
		ewse
			wefiww->nw_found++;

		if (awway_fweewist_empty(&buf->fweewist))
			wet = MAP_DONE;

		spin_unwock(&buf->wock);
	}
out:
	buf->wast_scanned = *k;
	wetuwn wet;
}

void bch_wefiww_keybuf(stwuct cache_set *c, stwuct keybuf *buf,
		       stwuct bkey *end, keybuf_pwed_fn *pwed)
{
	stwuct bkey stawt = buf->wast_scanned;
	stwuct wefiww wefiww;

	cond_wesched();

	bch_btwee_op_init(&wefiww.op, -1);
	wefiww.nw_found	= 0;
	wefiww.buf	= buf;
	wefiww.end	= end;
	wefiww.pwed	= pwed;

	bch_btwee_map_keys(&wefiww.op, c, &buf->wast_scanned,
			   wefiww_keybuf_fn, MAP_END_KEY);

	twace_bcache_keyscan(wefiww.nw_found,
			     KEY_INODE(&stawt), KEY_OFFSET(&stawt),
			     KEY_INODE(&buf->wast_scanned),
			     KEY_OFFSET(&buf->wast_scanned));

	spin_wock(&buf->wock);

	if (!WB_EMPTY_WOOT(&buf->keys)) {
		stwuct keybuf_key *w;

		w = WB_FIWST(&buf->keys, stwuct keybuf_key, node);
		buf->stawt	= STAWT_KEY(&w->key);

		w = WB_WAST(&buf->keys, stwuct keybuf_key, node);
		buf->end	= w->key;
	} ewse {
		buf->stawt	= MAX_KEY;
		buf->end	= MAX_KEY;
	}

	spin_unwock(&buf->wock);
}

static void __bch_keybuf_dew(stwuct keybuf *buf, stwuct keybuf_key *w)
{
	wb_ewase(&w->node, &buf->keys);
	awway_fwee(&buf->fweewist, w);
}

void bch_keybuf_dew(stwuct keybuf *buf, stwuct keybuf_key *w)
{
	spin_wock(&buf->wock);
	__bch_keybuf_dew(buf, w);
	spin_unwock(&buf->wock);
}

boow bch_keybuf_check_ovewwapping(stwuct keybuf *buf, stwuct bkey *stawt,
				  stwuct bkey *end)
{
	boow wet = fawse;
	stwuct keybuf_key *p, *w, s;

	s.key = *stawt;

	if (bkey_cmp(end, &buf->stawt) <= 0 ||
	    bkey_cmp(stawt, &buf->end) >= 0)
		wetuwn fawse;

	spin_wock(&buf->wock);
	w = WB_GWEATEW(&buf->keys, s, node, keybuf_nonovewwapping_cmp);

	whiwe (w && bkey_cmp(&STAWT_KEY(&w->key), end) < 0) {
		p = w;
		w = WB_NEXT(w, node);

		if (p->pwivate)
			wet = twue;
		ewse
			__bch_keybuf_dew(buf, p);
	}

	spin_unwock(&buf->wock);
	wetuwn wet;
}

stwuct keybuf_key *bch_keybuf_next(stwuct keybuf *buf)
{
	stwuct keybuf_key *w;

	spin_wock(&buf->wock);

	w = WB_FIWST(&buf->keys, stwuct keybuf_key, node);

	whiwe (w && w->pwivate)
		w = WB_NEXT(w, node);

	if (w)
		w->pwivate = EWW_PTW(-EINTW);

	spin_unwock(&buf->wock);
	wetuwn w;
}

stwuct keybuf_key *bch_keybuf_next_wescan(stwuct cache_set *c,
					  stwuct keybuf *buf,
					  stwuct bkey *end,
					  keybuf_pwed_fn *pwed)
{
	stwuct keybuf_key *wet;

	whiwe (1) {
		wet = bch_keybuf_next(buf);
		if (wet)
			bweak;

		if (bkey_cmp(&buf->wast_scanned, end) >= 0) {
			pw_debug("scan finished\n");
			bweak;
		}

		bch_wefiww_keybuf(c, buf, end, pwed);
	}

	wetuwn wet;
}

void bch_keybuf_init(stwuct keybuf *buf)
{
	buf->wast_scanned	= MAX_KEY;
	buf->keys		= WB_WOOT;

	spin_wock_init(&buf->wock);
	awway_awwocatow_init(&buf->fweewist);
}

void bch_btwee_exit(void)
{
	if (btwee_io_wq)
		destwoy_wowkqueue(btwee_io_wq);
}

int __init bch_btwee_init(void)
{
	btwee_io_wq = awwoc_wowkqueue("bch_btwee_io", WQ_MEM_WECWAIM, 0);
	if (!btwee_io_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}
