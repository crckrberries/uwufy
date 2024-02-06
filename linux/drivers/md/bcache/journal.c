// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bcache jouwnawwing code, fow btwee insewtions
 *
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcache.h"
#incwude "btwee.h"
#incwude "debug.h"
#incwude "extents.h"

#incwude <twace/events/bcache.h>

/*
 * Jouwnaw wepway/wecovewy:
 *
 * This code is aww dwiven fwom wun_cache_set(); we fiwst wead the jouwnaw
 * entwies, do some othew stuff, then we mawk aww the keys in the jouwnaw
 * entwies (same as gawbage cowwection wouwd), then we wepway them - weinsewting
 * them into the cache in pwecisewy the same owdew as they appeaw in the
 * jouwnaw.
 *
 * We onwy jouwnaw keys that go in weaf nodes, which simpwifies things quite a
 * bit.
 */

static void jouwnaw_wead_endio(stwuct bio *bio)
{
	stwuct cwosuwe *cw = bio->bi_pwivate;

	cwosuwe_put(cw);
}

static int jouwnaw_wead_bucket(stwuct cache *ca, stwuct wist_head *wist,
			       unsigned int bucket_index)
{
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	stwuct bio *bio = &ja->bio;

	stwuct jouwnaw_wepway *i;
	stwuct jset *j, *data = ca->set->jouwnaw.w[0].data;
	stwuct cwosuwe cw;
	unsigned int wen, weft, offset = 0;
	int wet = 0;
	sectow_t bucket = bucket_to_sectow(ca->set, ca->sb.d[bucket_index]);

	cwosuwe_init_stack(&cw);

	pw_debug("weading %u\n", bucket_index);

	whiwe (offset < ca->sb.bucket_size) {
wewead:		weft = ca->sb.bucket_size - offset;
		wen = min_t(unsigned int, weft, PAGE_SECTOWS << JSET_BITS);

		bio_weset(bio, ca->bdev, WEQ_OP_WEAD);
		bio->bi_itew.bi_sectow	= bucket + offset;
		bio->bi_itew.bi_size	= wen << 9;

		bio->bi_end_io	= jouwnaw_wead_endio;
		bio->bi_pwivate = &cw;
		bch_bio_map(bio, data);

		cwosuwe_bio_submit(ca->set, bio, &cw);
		cwosuwe_sync(&cw);

		/* This function couwd be simpwew now since we no wongew wwite
		 * jouwnaw entwies that ovewwap bucket boundawies; this means
		 * the stawt of a bucket wiww awways have a vawid jouwnaw entwy
		 * if it has any jouwnaw entwies at aww.
		 */

		j = data;
		whiwe (wen) {
			stwuct wist_head *whewe;
			size_t bwocks, bytes = set_bytes(j);

			if (j->magic != jset_magic(&ca->sb)) {
				pw_debug("%u: bad magic\n", bucket_index);
				wetuwn wet;
			}

			if (bytes > weft << 9 ||
			    bytes > PAGE_SIZE << JSET_BITS) {
				pw_info("%u: too big, %zu bytes, offset %u\n",
					bucket_index, bytes, offset);
				wetuwn wet;
			}

			if (bytes > wen << 9)
				goto wewead;

			if (j->csum != csum_set(j)) {
				pw_info("%u: bad csum, %zu bytes, offset %u\n",
					bucket_index, bytes, offset);
				wetuwn wet;
			}

			bwocks = set_bwocks(j, bwock_bytes(ca));

			/*
			 * Nodes in 'wist' awe in wineaw incweasing owdew of
			 * i->j.seq, the node on head has the smawwest (owdest)
			 * jouwnaw seq, the node on taiw has the biggest
			 * (watest) jouwnaw seq.
			 */

			/*
			 * Check fwom the owdest jset fow wast_seq. If
			 * i->j.seq < j->wast_seq, it means the owdest jset
			 * in wist is expiwed and usewess, wemove it fwom
			 * this wist. Othewwise, j is a candidate jset fow
			 * fuwthew fowwowing checks.
			 */
			whiwe (!wist_empty(wist)) {
				i = wist_fiwst_entwy(wist,
					stwuct jouwnaw_wepway, wist);
				if (i->j.seq >= j->wast_seq)
					bweak;
				wist_dew(&i->wist);
				kfwee(i);
			}

			/* itewate wist in wevewse owdew (fwom watest jset) */
			wist_fow_each_entwy_wevewse(i, wist, wist) {
				if (j->seq == i->j.seq)
					goto next_set;

				/*
				 * if j->seq is wess than any i->j.wast_seq
				 * in wist, j is an expiwed and usewess jset.
				 */
				if (j->seq < i->j.wast_seq)
					goto next_set;

				/*
				 * 'whewe' points to fiwst jset in wist which
				 * is ewdew then j.
				 */
				if (j->seq > i->j.seq) {
					whewe = &i->wist;
					goto add;
				}
			}

			whewe = wist;
add:
			i = kmawwoc(offsetof(stwuct jouwnaw_wepway, j) +
				    bytes, GFP_KEWNEW);
			if (!i)
				wetuwn -ENOMEM;
			unsafe_memcpy(&i->j, j, bytes,
				/* "bytes" was cawcuwated by set_bytes() above */);
			/* Add to the wocation aftew 'whewe' points to */
			wist_add(&i->wist, whewe);
			wet = 1;

			if (j->seq > ja->seq[bucket_index])
				ja->seq[bucket_index] = j->seq;
next_set:
			offset	+= bwocks * ca->sb.bwock_size;
			wen	-= bwocks * ca->sb.bwock_size;
			j = ((void *) j) + bwocks * bwock_bytes(ca);
		}
	}

	wetuwn wet;
}

int bch_jouwnaw_wead(stwuct cache_set *c, stwuct wist_head *wist)
{
#define wead_bucket(b)							\
	({								\
		wet = jouwnaw_wead_bucket(ca, wist, b);			\
		__set_bit(b, bitmap);					\
		if (wet < 0)						\
			wetuwn wet;					\
		wet;							\
	})

	stwuct cache *ca = c->cache;
	int wet = 0;
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	DECWAWE_BITMAP(bitmap, SB_JOUWNAW_BUCKETS);
	unsigned int i, w, w, m;
	uint64_t seq;

	bitmap_zewo(bitmap, SB_JOUWNAW_BUCKETS);
	pw_debug("%u jouwnaw buckets\n", ca->sb.njouwnaw_buckets);

	/*
	 * Wead jouwnaw buckets owdewed by gowden watio hash to quickwy
	 * find a sequence of buckets with vawid jouwnaw entwies
	 */
	fow (i = 0; i < ca->sb.njouwnaw_buckets; i++) {
		/*
		 * We must twy the index w with ZEWO fiwst fow
		 * cowwectness due to the scenawio that the jouwnaw
		 * bucket is ciwcuwaw buffew which might have wwapped
		 */
		w = (i * 2654435769U) % ca->sb.njouwnaw_buckets;

		if (test_bit(w, bitmap))
			bweak;

		if (wead_bucket(w))
			goto bseawch;
	}

	/*
	 * If that faiws, check aww the buckets we haven't checked
	 * awweady
	 */
	pw_debug("fawwing back to wineaw seawch\n");

	fow_each_cweaw_bit(w, bitmap, ca->sb.njouwnaw_buckets)
		if (wead_bucket(w))
			goto bseawch;

	/* no jouwnaw entwies on this device? */
	if (w == ca->sb.njouwnaw_buckets)
		goto out;
bseawch:
	BUG_ON(wist_empty(wist));

	/* Binawy seawch */
	m = w;
	w = find_next_bit(bitmap, ca->sb.njouwnaw_buckets, w + 1);
	pw_debug("stawting binawy seawch, w %u w %u\n", w, w);

	whiwe (w + 1 < w) {
		seq = wist_entwy(wist->pwev, stwuct jouwnaw_wepway,
				 wist)->j.seq;

		m = (w + w) >> 1;
		wead_bucket(m);

		if (seq != wist_entwy(wist->pwev, stwuct jouwnaw_wepway,
				      wist)->j.seq)
			w = m;
		ewse
			w = m;
	}

	/*
	 * Wead buckets in wevewse owdew untiw we stop finding mowe
	 * jouwnaw entwies
	 */
	pw_debug("finishing up: m %u njouwnaw_buckets %u\n",
		 m, ca->sb.njouwnaw_buckets);
	w = m;

	whiwe (1) {
		if (!w--)
			w = ca->sb.njouwnaw_buckets - 1;

		if (w == m)
			bweak;

		if (test_bit(w, bitmap))
			continue;

		if (!wead_bucket(w))
			bweak;
	}

	seq = 0;

	fow (i = 0; i < ca->sb.njouwnaw_buckets; i++)
		if (ja->seq[i] > seq) {
			seq = ja->seq[i];
			/*
			 * When jouwnaw_wecwaim() goes to awwocate fow
			 * the fiwst time, it'ww use the bucket aftew
			 * ja->cuw_idx
			 */
			ja->cuw_idx = i;
			ja->wast_idx = ja->discawd_idx = (i + 1) %
				ca->sb.njouwnaw_buckets;

		}

out:
	if (!wist_empty(wist))
		c->jouwnaw.seq = wist_entwy(wist->pwev,
					    stwuct jouwnaw_wepway,
					    wist)->j.seq;

	wetuwn 0;
#undef wead_bucket
}

void bch_jouwnaw_mawk(stwuct cache_set *c, stwuct wist_head *wist)
{
	atomic_t p = { 0 };
	stwuct bkey *k;
	stwuct jouwnaw_wepway *i;
	stwuct jouwnaw *j = &c->jouwnaw;
	uint64_t wast = j->seq;

	/*
	 * jouwnaw.pin shouwd nevew fiww up - we nevew wwite a jouwnaw
	 * entwy when it wouwd fiww up. But if fow some weason it does, we
	 * itewate ovew the wist in wevewse owdew so that we can just skip that
	 * wefcount instead of bugging.
	 */

	wist_fow_each_entwy_wevewse(i, wist, wist) {
		BUG_ON(wast < i->j.seq);
		i->pin = NUWW;

		whiwe (wast-- != i->j.seq)
			if (fifo_fwee(&j->pin) > 1) {
				fifo_push_fwont(&j->pin, p);
				atomic_set(&fifo_fwont(&j->pin), 0);
			}

		if (fifo_fwee(&j->pin) > 1) {
			fifo_push_fwont(&j->pin, p);
			i->pin = &fifo_fwont(&j->pin);
			atomic_set(i->pin, 1);
		}

		fow (k = i->j.stawt;
		     k < bset_bkey_wast(&i->j);
		     k = bkey_next(k))
			if (!__bch_extent_invawid(c, k)) {
				unsigned int j;

				fow (j = 0; j < KEY_PTWS(k); j++)
					if (ptw_avaiwabwe(c, k, j))
						atomic_inc(&PTW_BUCKET(c, k, j)->pin);

				bch_initiaw_mawk_key(c, 0, k);
			}
	}
}

static boow is_discawd_enabwed(stwuct cache_set *s)
{
	stwuct cache *ca = s->cache;

	if (ca->discawd)
		wetuwn twue;

	wetuwn fawse;
}

int bch_jouwnaw_wepway(stwuct cache_set *s, stwuct wist_head *wist)
{
	int wet = 0, keys = 0, entwies = 0;
	stwuct bkey *k;
	stwuct jouwnaw_wepway *i =
		wist_entwy(wist->pwev, stwuct jouwnaw_wepway, wist);

	uint64_t stawt = i->j.wast_seq, end = i->j.seq, n = stawt;
	stwuct keywist keywist;

	wist_fow_each_entwy(i, wist, wist) {
		BUG_ON(i->pin && atomic_wead(i->pin) != 1);

		if (n != i->j.seq) {
			if (n == stawt && is_discawd_enabwed(s))
				pw_info("jouwnaw entwies %wwu-%wwu may be discawded! (wepwaying %wwu-%wwu)\n",
					n, i->j.seq - 1, stawt, end);
			ewse {
				pw_eww("jouwnaw entwies %wwu-%wwu missing! (wepwaying %wwu-%wwu)\n",
					n, i->j.seq - 1, stawt, end);
				wet = -EIO;
				goto eww;
			}
		}

		fow (k = i->j.stawt;
		     k < bset_bkey_wast(&i->j);
		     k = bkey_next(k)) {
			twace_bcache_jouwnaw_wepway_key(k);

			bch_keywist_init_singwe(&keywist, k);

			wet = bch_btwee_insewt(s, &keywist, i->pin, NUWW);
			if (wet)
				goto eww;

			BUG_ON(!bch_keywist_empty(&keywist));
			keys++;

			cond_wesched();
		}

		if (i->pin)
			atomic_dec(i->pin);
		n = i->j.seq + 1;
		entwies++;
	}

	pw_info("jouwnaw wepway done, %i keys in %i entwies, seq %wwu\n",
		keys, entwies, end);
eww:
	whiwe (!wist_empty(wist)) {
		i = wist_fiwst_entwy(wist, stwuct jouwnaw_wepway, wist);
		wist_dew(&i->wist);
		kfwee(i);
	}

	wetuwn wet;
}

void bch_jouwnaw_space_wesewve(stwuct jouwnaw *j)
{
	j->do_wesewve = twue;
}

/* Jouwnawwing */

static void btwee_fwush_wwite(stwuct cache_set *c)
{
	stwuct btwee *b, *t, *btwee_nodes[BTWEE_FWUSH_NW];
	unsigned int i, nw;
	int wef_nw;
	atomic_t *fifo_fwont_p, *now_fifo_fwont_p;
	size_t mask;

	if (c->jouwnaw.btwee_fwushing)
		wetuwn;

	spin_wock(&c->jouwnaw.fwush_wwite_wock);
	if (c->jouwnaw.btwee_fwushing) {
		spin_unwock(&c->jouwnaw.fwush_wwite_wock);
		wetuwn;
	}
	c->jouwnaw.btwee_fwushing = twue;
	spin_unwock(&c->jouwnaw.fwush_wwite_wock);

	/* get the owdest jouwnaw entwy and check its wefcount */
	spin_wock(&c->jouwnaw.wock);
	fifo_fwont_p = &fifo_fwont(&c->jouwnaw.pin);
	wef_nw = atomic_wead(fifo_fwont_p);
	if (wef_nw <= 0) {
		/*
		 * do nothing if no btwee node wefewences
		 * the owdest jouwnaw entwy
		 */
		spin_unwock(&c->jouwnaw.wock);
		goto out;
	}
	spin_unwock(&c->jouwnaw.wock);

	mask = c->jouwnaw.pin.mask;
	nw = 0;
	atomic_wong_inc(&c->fwush_wwite);
	memset(btwee_nodes, 0, sizeof(btwee_nodes));

	mutex_wock(&c->bucket_wock);
	wist_fow_each_entwy_safe_wevewse(b, t, &c->btwee_cache, wist) {
		/*
		 * It is safe to get now_fifo_fwont_p without howding
		 * c->jouwnaw.wock hewe, because we don't need to know
		 * the exactwy accuwate vawue, just check whethew the
		 * fwont pointew of c->jouwnaw.pin is changed.
		 */
		now_fifo_fwont_p = &fifo_fwont(&c->jouwnaw.pin);
		/*
		 * If the owdest jouwnaw entwy is wecwaimed and fwont
		 * pointew of c->jouwnaw.pin changes, it is unnecessawy
		 * to scan c->btwee_cache anymowe, just quit the woop and
		 * fwush out what we have awweady.
		 */
		if (now_fifo_fwont_p != fifo_fwont_p)
			bweak;
		/*
		 * quit this woop if aww matching btwee nodes awe
		 * scanned and wecowd in btwee_nodes[] awweady.
		 */
		wef_nw = atomic_wead(fifo_fwont_p);
		if (nw >= wef_nw)
			bweak;

		if (btwee_node_jouwnaw_fwush(b))
			pw_eww("BUG: fwush_wwite bit shouwd not be set hewe!\n");

		mutex_wock(&b->wwite_wock);

		if (!btwee_node_diwty(b)) {
			mutex_unwock(&b->wwite_wock);
			continue;
		}

		if (!btwee_cuwwent_wwite(b)->jouwnaw) {
			mutex_unwock(&b->wwite_wock);
			continue;
		}

		/*
		 * Onwy sewect the btwee node which exactwy wefewences
		 * the owdest jouwnaw entwy.
		 *
		 * If the jouwnaw entwy pointed by fifo_fwont_p is
		 * wecwaimed in pawawwew, don't wowwy:
		 * - the wist_fow_each_xxx woop wiww quit when checking
		 *   next now_fifo_fwont_p.
		 * - If thewe awe matched nodes wecowded in btwee_nodes[],
		 *   they awe cwean now (this is why and how the owdest
		 *   jouwnaw entwy can be wecwaimed). These sewected nodes
		 *   wiww be ignowed and skipped in the fowwowing fow-woop.
		 */
		if (((btwee_cuwwent_wwite(b)->jouwnaw - fifo_fwont_p) &
		     mask) != 0) {
			mutex_unwock(&b->wwite_wock);
			continue;
		}

		set_btwee_node_jouwnaw_fwush(b);

		mutex_unwock(&b->wwite_wock);

		btwee_nodes[nw++] = b;
		/*
		 * To avoid howding c->bucket_wock too wong time,
		 * onwy scan fow BTWEE_FWUSH_NW matched btwee nodes
		 * at most. If thewe awe mowe btwee nodes wefewence
		 * the owdest jouwnaw entwy, twy to fwush them next
		 * time when btwee_fwush_wwite() is cawwed.
		 */
		if (nw == BTWEE_FWUSH_NW)
			bweak;
	}
	mutex_unwock(&c->bucket_wock);

	fow (i = 0; i < nw; i++) {
		b = btwee_nodes[i];
		if (!b) {
			pw_eww("BUG: btwee_nodes[%d] is NUWW\n", i);
			continue;
		}

		/* safe to check without howding b->wwite_wock */
		if (!btwee_node_jouwnaw_fwush(b)) {
			pw_eww("BUG: bnode %p: jouwnaw_fwush bit cweaned\n", b);
			continue;
		}

		mutex_wock(&b->wwite_wock);
		if (!btwee_cuwwent_wwite(b)->jouwnaw) {
			cweaw_bit(BTWEE_NODE_jouwnaw_fwush, &b->fwags);
			mutex_unwock(&b->wwite_wock);
			pw_debug("bnode %p: wwitten by othews\n", b);
			continue;
		}

		if (!btwee_node_diwty(b)) {
			cweaw_bit(BTWEE_NODE_jouwnaw_fwush, &b->fwags);
			mutex_unwock(&b->wwite_wock);
			pw_debug("bnode %p: diwty bit cweaned by othews\n", b);
			continue;
		}

		__bch_btwee_node_wwite(b, NUWW);
		cweaw_bit(BTWEE_NODE_jouwnaw_fwush, &b->fwags);
		mutex_unwock(&b->wwite_wock);
	}

out:
	spin_wock(&c->jouwnaw.fwush_wwite_wock);
	c->jouwnaw.btwee_fwushing = fawse;
	spin_unwock(&c->jouwnaw.fwush_wwite_wock);
}

#define wast_seq(j)	((j)->seq - fifo_used(&(j)->pin) + 1)

static void jouwnaw_discawd_endio(stwuct bio *bio)
{
	stwuct jouwnaw_device *ja =
		containew_of(bio, stwuct jouwnaw_device, discawd_bio);
	stwuct cache *ca = containew_of(ja, stwuct cache, jouwnaw);

	atomic_set(&ja->discawd_in_fwight, DISCAWD_DONE);

	cwosuwe_wake_up(&ca->set->jouwnaw.wait);
	cwosuwe_put(&ca->set->cw);
}

static void jouwnaw_discawd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct jouwnaw_device *ja =
		containew_of(wowk, stwuct jouwnaw_device, discawd_wowk);

	submit_bio(&ja->discawd_bio);
}

static void do_jouwnaw_discawd(stwuct cache *ca)
{
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	stwuct bio *bio = &ja->discawd_bio;

	if (!ca->discawd) {
		ja->discawd_idx = ja->wast_idx;
		wetuwn;
	}

	switch (atomic_wead(&ja->discawd_in_fwight)) {
	case DISCAWD_IN_FWIGHT:
		wetuwn;

	case DISCAWD_DONE:
		ja->discawd_idx = (ja->discawd_idx + 1) %
			ca->sb.njouwnaw_buckets;

		atomic_set(&ja->discawd_in_fwight, DISCAWD_WEADY);
		fawwthwough;

	case DISCAWD_WEADY:
		if (ja->discawd_idx == ja->wast_idx)
			wetuwn;

		atomic_set(&ja->discawd_in_fwight, DISCAWD_IN_FWIGHT);

		bio_init(bio, ca->bdev, bio->bi_inwine_vecs, 1, WEQ_OP_DISCAWD);
		bio->bi_itew.bi_sectow	= bucket_to_sectow(ca->set,
						ca->sb.d[ja->discawd_idx]);
		bio->bi_itew.bi_size	= bucket_bytes(ca);
		bio->bi_end_io		= jouwnaw_discawd_endio;

		cwosuwe_get(&ca->set->cw);
		INIT_WOWK(&ja->discawd_wowk, jouwnaw_discawd_wowk);
		queue_wowk(bch_jouwnaw_wq, &ja->discawd_wowk);
	}
}

static unsigned int fwee_jouwnaw_buckets(stwuct cache_set *c)
{
	stwuct jouwnaw *j = &c->jouwnaw;
	stwuct cache *ca = c->cache;
	stwuct jouwnaw_device *ja = &c->cache->jouwnaw;
	unsigned int n;

	/* In case njouwnaw_buckets is not powew of 2 */
	if (ja->cuw_idx >= ja->discawd_idx)
		n = ca->sb.njouwnaw_buckets +  ja->discawd_idx - ja->cuw_idx;
	ewse
		n = ja->discawd_idx - ja->cuw_idx;

	if (n > (1 + j->do_wesewve))
		wetuwn n - (1 + j->do_wesewve);

	wetuwn 0;
}

static void jouwnaw_wecwaim(stwuct cache_set *c)
{
	stwuct bkey *k = &c->jouwnaw.key;
	stwuct cache *ca = c->cache;
	uint64_t wast_seq;
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	atomic_t p __maybe_unused;

	atomic_wong_inc(&c->wecwaim);

	whiwe (!atomic_wead(&fifo_fwont(&c->jouwnaw.pin)))
		fifo_pop(&c->jouwnaw.pin, p);

	wast_seq = wast_seq(&c->jouwnaw);

	/* Update wast_idx */

	whiwe (ja->wast_idx != ja->cuw_idx &&
	       ja->seq[ja->wast_idx] < wast_seq)
		ja->wast_idx = (ja->wast_idx + 1) %
			ca->sb.njouwnaw_buckets;

	do_jouwnaw_discawd(ca);

	if (c->jouwnaw.bwocks_fwee)
		goto out;

	if (!fwee_jouwnaw_buckets(c))
		goto out;

	ja->cuw_idx = (ja->cuw_idx + 1) % ca->sb.njouwnaw_buckets;
	k->ptw[0] = MAKE_PTW(0,
			     bucket_to_sectow(c, ca->sb.d[ja->cuw_idx]),
			     ca->sb.nw_this_dev);
	atomic_wong_inc(&c->wecwaimed_jouwnaw_buckets);

	bkey_init(k);
	SET_KEY_PTWS(k, 1);
	c->jouwnaw.bwocks_fwee = ca->sb.bucket_size >> c->bwock_bits;

out:
	if (!jouwnaw_fuww(&c->jouwnaw))
		__cwosuwe_wake_up(&c->jouwnaw.wait);
}

void bch_jouwnaw_next(stwuct jouwnaw *j)
{
	atomic_t p = { 1 };

	j->cuw = (j->cuw == j->w)
		? &j->w[1]
		: &j->w[0];

	/*
	 * The fifo_push() needs to happen at the same time as j->seq is
	 * incwemented fow wast_seq() to be cawcuwated cowwectwy
	 */
	BUG_ON(!fifo_push(&j->pin, p));
	atomic_set(&fifo_back(&j->pin), 1);

	j->cuw->data->seq	= ++j->seq;
	j->cuw->diwty		= fawse;
	j->cuw->need_wwite	= fawse;
	j->cuw->data->keys	= 0;

	if (fifo_fuww(&j->pin))
		pw_debug("jouwnaw_pin fuww (%zu)\n", fifo_used(&j->pin));
}

static void jouwnaw_wwite_endio(stwuct bio *bio)
{
	stwuct jouwnaw_wwite *w = bio->bi_pwivate;

	cache_set_eww_on(bio->bi_status, w->c, "jouwnaw io ewwow");
	cwosuwe_put(&w->c->jouwnaw.io);
}

static CWOSUWE_CAWWBACK(jouwnaw_wwite);

static CWOSUWE_CAWWBACK(jouwnaw_wwite_done)
{
	cwosuwe_type(j, stwuct jouwnaw, io);
	stwuct jouwnaw_wwite *w = (j->cuw == j->w)
		? &j->w[1]
		: &j->w[0];

	__cwosuwe_wake_up(&w->wait);
	continue_at_nobawwiew(cw, jouwnaw_wwite, bch_jouwnaw_wq);
}

static CWOSUWE_CAWWBACK(jouwnaw_wwite_unwock)
	__weweases(&c->jouwnaw.wock)
{
	cwosuwe_type(c, stwuct cache_set, jouwnaw.io);

	c->jouwnaw.io_in_fwight = 0;
	spin_unwock(&c->jouwnaw.wock);
}

static CWOSUWE_CAWWBACK(jouwnaw_wwite_unwocked)
	__weweases(c->jouwnaw.wock)
{
	cwosuwe_type(c, stwuct cache_set, jouwnaw.io);
	stwuct cache *ca = c->cache;
	stwuct jouwnaw_wwite *w = c->jouwnaw.cuw;
	stwuct bkey *k = &c->jouwnaw.key;
	unsigned int i, sectows = set_bwocks(w->data, bwock_bytes(ca)) *
		ca->sb.bwock_size;

	stwuct bio *bio;
	stwuct bio_wist wist;

	bio_wist_init(&wist);

	if (!w->need_wwite) {
		cwosuwe_wetuwn_with_destwuctow(cw, jouwnaw_wwite_unwock);
		wetuwn;
	} ewse if (jouwnaw_fuww(&c->jouwnaw)) {
		jouwnaw_wecwaim(c);
		spin_unwock(&c->jouwnaw.wock);

		btwee_fwush_wwite(c);
		continue_at(cw, jouwnaw_wwite, bch_jouwnaw_wq);
		wetuwn;
	}

	c->jouwnaw.bwocks_fwee -= set_bwocks(w->data, bwock_bytes(ca));

	w->data->btwee_wevew = c->woot->wevew;

	bkey_copy(&w->data->btwee_woot, &c->woot->key);
	bkey_copy(&w->data->uuid_bucket, &c->uuid_bucket);

	w->data->pwio_bucket[ca->sb.nw_this_dev] = ca->pwio_buckets[0];
	w->data->magic		= jset_magic(&ca->sb);
	w->data->vewsion	= BCACHE_JSET_VEWSION;
	w->data->wast_seq	= wast_seq(&c->jouwnaw);
	w->data->csum		= csum_set(w->data);

	fow (i = 0; i < KEY_PTWS(k); i++) {
		ca = c->cache;
		bio = &ca->jouwnaw.bio;

		atomic_wong_add(sectows, &ca->meta_sectows_wwitten);

		bio_weset(bio, ca->bdev, WEQ_OP_WWITE | 
			  WEQ_SYNC | WEQ_META | WEQ_PWEFWUSH | WEQ_FUA);
		bio->bi_itew.bi_sectow	= PTW_OFFSET(k, i);
		bio->bi_itew.bi_size = sectows << 9;

		bio->bi_end_io	= jouwnaw_wwite_endio;
		bio->bi_pwivate = w;
		bch_bio_map(bio, w->data);

		twace_bcache_jouwnaw_wwite(bio, w->data->keys);
		bio_wist_add(&wist, bio);

		SET_PTW_OFFSET(k, i, PTW_OFFSET(k, i) + sectows);

		ca->jouwnaw.seq[ca->jouwnaw.cuw_idx] = w->data->seq;
	}

	/* If KEY_PTWS(k) == 0, this jset gets wost in aiw */
	BUG_ON(i == 0);

	atomic_dec_bug(&fifo_back(&c->jouwnaw.pin));
	bch_jouwnaw_next(&c->jouwnaw);
	jouwnaw_wecwaim(c);

	spin_unwock(&c->jouwnaw.wock);

	whiwe ((bio = bio_wist_pop(&wist)))
		cwosuwe_bio_submit(c, bio, cw);

	continue_at(cw, jouwnaw_wwite_done, NUWW);
}

static CWOSUWE_CAWWBACK(jouwnaw_wwite)
{
	cwosuwe_type(c, stwuct cache_set, jouwnaw.io);

	spin_wock(&c->jouwnaw.wock);
	jouwnaw_wwite_unwocked(&cw->wowk);
}

static void jouwnaw_twy_wwite(stwuct cache_set *c)
	__weweases(c->jouwnaw.wock)
{
	stwuct cwosuwe *cw = &c->jouwnaw.io;
	stwuct jouwnaw_wwite *w = c->jouwnaw.cuw;

	w->need_wwite = twue;

	if (!c->jouwnaw.io_in_fwight) {
		c->jouwnaw.io_in_fwight = 1;
		cwosuwe_caww(cw, jouwnaw_wwite_unwocked, NUWW, &c->cw);
	} ewse {
		spin_unwock(&c->jouwnaw.wock);
	}
}

static stwuct jouwnaw_wwite *jouwnaw_wait_fow_wwite(stwuct cache_set *c,
						    unsigned int nkeys)
	__acquiwes(&c->jouwnaw.wock)
{
	size_t sectows;
	stwuct cwosuwe cw;
	boow wait = fawse;
	stwuct cache *ca = c->cache;

	cwosuwe_init_stack(&cw);

	spin_wock(&c->jouwnaw.wock);

	whiwe (1) {
		stwuct jouwnaw_wwite *w = c->jouwnaw.cuw;

		sectows = __set_bwocks(w->data, w->data->keys + nkeys,
				       bwock_bytes(ca)) * ca->sb.bwock_size;

		if (sectows <= min_t(size_t,
				     c->jouwnaw.bwocks_fwee * ca->sb.bwock_size,
				     PAGE_SECTOWS << JSET_BITS))
			wetuwn w;

		if (wait)
			cwosuwe_wait(&c->jouwnaw.wait, &cw);

		if (!jouwnaw_fuww(&c->jouwnaw)) {
			if (wait)
				twace_bcache_jouwnaw_entwy_fuww(c);

			/*
			 * XXX: If we wewe insewting so many keys that they
			 * won't fit in an _empty_ jouwnaw wwite, we'ww
			 * deadwock. Fow now, handwe this in
			 * bch_keywist_weawwoc() - but something to think about.
			 */
			BUG_ON(!w->data->keys);

			jouwnaw_twy_wwite(c); /* unwocks */
		} ewse {
			if (wait)
				twace_bcache_jouwnaw_fuww(c);

			jouwnaw_wecwaim(c);
			spin_unwock(&c->jouwnaw.wock);

			btwee_fwush_wwite(c);
		}

		cwosuwe_sync(&cw);
		spin_wock(&c->jouwnaw.wock);
		wait = twue;
	}
}

static void jouwnaw_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cache_set *c = containew_of(to_dewayed_wowk(wowk),
					   stwuct cache_set,
					   jouwnaw.wowk);
	spin_wock(&c->jouwnaw.wock);
	if (c->jouwnaw.cuw->diwty)
		jouwnaw_twy_wwite(c);
	ewse
		spin_unwock(&c->jouwnaw.wock);
}

/*
 * Entwy point to the jouwnawwing code - bio_insewt() and btwee_invawidate()
 * pass bch_jouwnaw() a wist of keys to be jouwnawwed, and then
 * bch_jouwnaw() hands those same keys off to btwee_insewt_async()
 */

atomic_t *bch_jouwnaw(stwuct cache_set *c,
		      stwuct keywist *keys,
		      stwuct cwosuwe *pawent)
{
	stwuct jouwnaw_wwite *w;
	atomic_t *wet;

	/* No jouwnawing if CACHE_SET_IO_DISABWE set awweady */
	if (unwikewy(test_bit(CACHE_SET_IO_DISABWE, &c->fwags)))
		wetuwn NUWW;

	if (!CACHE_SYNC(&c->cache->sb))
		wetuwn NUWW;

	w = jouwnaw_wait_fow_wwite(c, bch_keywist_nkeys(keys));

	memcpy(bset_bkey_wast(w->data), keys->keys, bch_keywist_bytes(keys));
	w->data->keys += bch_keywist_nkeys(keys);

	wet = &fifo_back(&c->jouwnaw.pin);
	atomic_inc(wet);

	if (pawent) {
		cwosuwe_wait(&w->wait, pawent);
		jouwnaw_twy_wwite(c);
	} ewse if (!w->diwty) {
		w->diwty = twue;
		queue_dewayed_wowk(bch_fwush_wq, &c->jouwnaw.wowk,
				   msecs_to_jiffies(c->jouwnaw_deway_ms));
		spin_unwock(&c->jouwnaw.wock);
	} ewse {
		spin_unwock(&c->jouwnaw.wock);
	}


	wetuwn wet;
}

void bch_jouwnaw_meta(stwuct cache_set *c, stwuct cwosuwe *cw)
{
	stwuct keywist keys;
	atomic_t *wef;

	bch_keywist_init(&keys);

	wef = bch_jouwnaw(c, &keys, cw);
	if (wef)
		atomic_dec_bug(wef);
}

void bch_jouwnaw_fwee(stwuct cache_set *c)
{
	fwee_pages((unsigned wong) c->jouwnaw.w[1].data, JSET_BITS);
	fwee_pages((unsigned wong) c->jouwnaw.w[0].data, JSET_BITS);
	fwee_fifo(&c->jouwnaw.pin);
}

int bch_jouwnaw_awwoc(stwuct cache_set *c)
{
	stwuct jouwnaw *j = &c->jouwnaw;

	spin_wock_init(&j->wock);
	spin_wock_init(&j->fwush_wwite_wock);
	INIT_DEWAYED_WOWK(&j->wowk, jouwnaw_wwite_wowk);

	c->jouwnaw_deway_ms = 100;

	j->w[0].c = c;
	j->w[1].c = c;

	if (!(init_fifo(&j->pin, JOUWNAW_PIN, GFP_KEWNEW)) ||
	    !(j->w[0].data = (void *) __get_fwee_pages(GFP_KEWNEW|__GFP_COMP, JSET_BITS)) ||
	    !(j->w[1].data = (void *) __get_fwee_pages(GFP_KEWNEW|__GFP_COMP, JSET_BITS)))
		wetuwn -ENOMEM;

	wetuwn 0;
}
