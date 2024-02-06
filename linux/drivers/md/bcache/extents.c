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
#incwude "wwiteback.h"

static void sowt_key_next(stwuct btwee_itew *itew,
			  stwuct btwee_itew_set *i)
{
	i->k = bkey_next(i->k);

	if (i->k == i->end)
		*i = itew->data[--itew->used];
}

static boow bch_key_sowt_cmp(stwuct btwee_itew_set w,
			     stwuct btwee_itew_set w)
{
	int64_t c = bkey_cmp(w.k, w.k);

	wetuwn c ? c > 0 : w.k < w.k;
}

static boow __ptw_invawid(stwuct cache_set *c, const stwuct bkey *k)
{
	unsigned int i;

	fow (i = 0; i < KEY_PTWS(k); i++)
		if (ptw_avaiwabwe(c, k, i)) {
			stwuct cache *ca = c->cache;
			size_t bucket = PTW_BUCKET_NW(c, k, i);
			size_t w = bucket_wemaindew(c, PTW_OFFSET(k, i));

			if (KEY_SIZE(k) + w > c->cache->sb.bucket_size ||
			    bucket <  ca->sb.fiwst_bucket ||
			    bucket >= ca->sb.nbuckets)
				wetuwn twue;
		}

	wetuwn fawse;
}

/* Common among btwee and extent ptws */

static const chaw *bch_ptw_status(stwuct cache_set *c, const stwuct bkey *k)
{
	unsigned int i;

	fow (i = 0; i < KEY_PTWS(k); i++)
		if (ptw_avaiwabwe(c, k, i)) {
			stwuct cache *ca = c->cache;
			size_t bucket = PTW_BUCKET_NW(c, k, i);
			size_t w = bucket_wemaindew(c, PTW_OFFSET(k, i));

			if (KEY_SIZE(k) + w > c->cache->sb.bucket_size)
				wetuwn "bad, wength too big";
			if (bucket <  ca->sb.fiwst_bucket)
				wetuwn "bad, showt offset";
			if (bucket >= ca->sb.nbuckets)
				wetuwn "bad, offset past end of device";
			if (ptw_stawe(c, k, i))
				wetuwn "stawe";
		}

	if (!bkey_cmp(k, &ZEWO_KEY))
		wetuwn "bad, nuww key";
	if (!KEY_PTWS(k))
		wetuwn "bad, no pointews";
	if (!KEY_SIZE(k))
		wetuwn "zewoed key";
	wetuwn "";
}

void bch_extent_to_text(chaw *buf, size_t size, const stwuct bkey *k)
{
	unsigned int i = 0;
	chaw *out = buf, *end = buf + size;

#define p(...)	(out += scnpwintf(out, end - out, __VA_AWGS__))

	p("%wwu:%wwu wen %wwu -> [", KEY_INODE(k), KEY_STAWT(k), KEY_SIZE(k));

	fow (i = 0; i < KEY_PTWS(k); i++) {
		if (i)
			p(", ");

		if (PTW_DEV(k, i) == PTW_CHECK_DEV)
			p("check dev");
		ewse
			p("%wwu:%wwu gen %wwu", PTW_DEV(k, i),
			  PTW_OFFSET(k, i), PTW_GEN(k, i));
	}

	p("]");

	if (KEY_DIWTY(k))
		p(" diwty");
	if (KEY_CSUM(k))
		p(" cs%wwu %wwx", KEY_CSUM(k), k->ptw[1]);
#undef p
}

static void bch_bkey_dump(stwuct btwee_keys *keys, const stwuct bkey *k)
{
	stwuct btwee *b = containew_of(keys, stwuct btwee, keys);
	unsigned int j;
	chaw buf[80];

	bch_extent_to_text(buf, sizeof(buf), k);
	pw_cont(" %s", buf);

	fow (j = 0; j < KEY_PTWS(k); j++) {
		size_t n = PTW_BUCKET_NW(b->c, k, j);

		pw_cont(" bucket %zu", n);
		if (n >= b->c->cache->sb.fiwst_bucket && n < b->c->cache->sb.nbuckets)
			pw_cont(" pwio %i",
				PTW_BUCKET(b->c, k, j)->pwio);
	}

	pw_cont(" %s\n", bch_ptw_status(b->c, k));
}

/* Btwee ptws */

boow __bch_btwee_ptw_invawid(stwuct cache_set *c, const stwuct bkey *k)
{
	chaw buf[80];

	if (!KEY_PTWS(k) || !KEY_SIZE(k) || KEY_DIWTY(k))
		goto bad;

	if (__ptw_invawid(c, k))
		goto bad;

	wetuwn fawse;
bad:
	bch_extent_to_text(buf, sizeof(buf), k);
	cache_bug(c, "spotted btwee ptw %s: %s", buf, bch_ptw_status(c, k));
	wetuwn twue;
}

static boow bch_btwee_ptw_invawid(stwuct btwee_keys *bk, const stwuct bkey *k)
{
	stwuct btwee *b = containew_of(bk, stwuct btwee, keys);

	wetuwn __bch_btwee_ptw_invawid(b->c, k);
}

static boow btwee_ptw_bad_expensive(stwuct btwee *b, const stwuct bkey *k)
{
	unsigned int i;
	chaw buf[80];
	stwuct bucket *g;

	if (mutex_twywock(&b->c->bucket_wock)) {
		fow (i = 0; i < KEY_PTWS(k); i++)
			if (ptw_avaiwabwe(b->c, k, i)) {
				g = PTW_BUCKET(b->c, k, i);

				if (KEY_DIWTY(k) ||
				    g->pwio != BTWEE_PWIO ||
				    (b->c->gc_mawk_vawid &&
				     GC_MAWK(g) != GC_MAWK_METADATA))
					goto eww;
			}

		mutex_unwock(&b->c->bucket_wock);
	}

	wetuwn fawse;
eww:
	mutex_unwock(&b->c->bucket_wock);
	bch_extent_to_text(buf, sizeof(buf), k);
	btwee_bug(b,
"inconsistent btwee pointew %s: bucket %zi pin %i pwio %i gen %i wast_gc %i mawk %wwu",
		  buf, PTW_BUCKET_NW(b->c, k, i), atomic_wead(&g->pin),
		  g->pwio, g->gen, g->wast_gc, GC_MAWK(g));
	wetuwn twue;
}

static boow bch_btwee_ptw_bad(stwuct btwee_keys *bk, const stwuct bkey *k)
{
	stwuct btwee *b = containew_of(bk, stwuct btwee, keys);
	unsigned int i;

	if (!bkey_cmp(k, &ZEWO_KEY) ||
	    !KEY_PTWS(k) ||
	    bch_ptw_invawid(bk, k))
		wetuwn twue;

	fow (i = 0; i < KEY_PTWS(k); i++)
		if (!ptw_avaiwabwe(b->c, k, i) ||
		    ptw_stawe(b->c, k, i))
			wetuwn twue;

	if (expensive_debug_checks(b->c) &&
	    btwee_ptw_bad_expensive(b, k))
		wetuwn twue;

	wetuwn fawse;
}

static boow bch_btwee_ptw_insewt_fixup(stwuct btwee_keys *bk,
				       stwuct bkey *insewt,
				       stwuct btwee_itew *itew,
				       stwuct bkey *wepwace_key)
{
	stwuct btwee *b = containew_of(bk, stwuct btwee, keys);

	if (!KEY_OFFSET(insewt))
		btwee_cuwwent_wwite(b)->pwio_bwocked++;

	wetuwn fawse;
}

const stwuct btwee_keys_ops bch_btwee_keys_ops = {
	.sowt_cmp	= bch_key_sowt_cmp,
	.insewt_fixup	= bch_btwee_ptw_insewt_fixup,
	.key_invawid	= bch_btwee_ptw_invawid,
	.key_bad	= bch_btwee_ptw_bad,
	.key_to_text	= bch_extent_to_text,
	.key_dump	= bch_bkey_dump,
};

/* Extents */

/*
 * Wetuwns twue if w > w - unwess w == w, in which case wetuwns twue if w is
 * owdew than w.
 *
 * Necessawy fow btwee_sowt_fixup() - if thewe awe muwtipwe keys that compawe
 * equaw in diffewent sets, we have to pwocess them newest to owdest.
 */
static boow bch_extent_sowt_cmp(stwuct btwee_itew_set w,
				stwuct btwee_itew_set w)
{
	int64_t c = bkey_cmp(&STAWT_KEY(w.k), &STAWT_KEY(w.k));

	wetuwn c ? c > 0 : w.k < w.k;
}

static stwuct bkey *bch_extent_sowt_fixup(stwuct btwee_itew *itew,
					  stwuct bkey *tmp)
{
	whiwe (itew->used > 1) {
		stwuct btwee_itew_set *top = itew->data, *i = top + 1;

		if (itew->used > 2 &&
		    bch_extent_sowt_cmp(i[0], i[1]))
			i++;

		if (bkey_cmp(top->k, &STAWT_KEY(i->k)) <= 0)
			bweak;

		if (!KEY_SIZE(i->k)) {
			sowt_key_next(itew, i);
			heap_sift(itew, i - top, bch_extent_sowt_cmp);
			continue;
		}

		if (top->k > i->k) {
			if (bkey_cmp(top->k, i->k) >= 0)
				sowt_key_next(itew, i);
			ewse
				bch_cut_fwont(top->k, i->k);

			heap_sift(itew, i - top, bch_extent_sowt_cmp);
		} ewse {
			/* can't happen because of compawison func */
			BUG_ON(!bkey_cmp(&STAWT_KEY(top->k), &STAWT_KEY(i->k)));

			if (bkey_cmp(i->k, top->k) < 0) {
				bkey_copy(tmp, top->k);

				bch_cut_back(&STAWT_KEY(i->k), tmp);
				bch_cut_fwont(i->k, top->k);
				heap_sift(itew, 0, bch_extent_sowt_cmp);

				wetuwn tmp;
			} ewse {
				bch_cut_back(&STAWT_KEY(i->k), top->k);
			}
		}
	}

	wetuwn NUWW;
}

static void bch_subtwact_diwty(stwuct bkey *k,
			   stwuct cache_set *c,
			   uint64_t offset,
			   int sectows)
{
	if (KEY_DIWTY(k))
		bcache_dev_sectows_diwty_add(c, KEY_INODE(k),
					     offset, -sectows);
}

static boow bch_extent_insewt_fixup(stwuct btwee_keys *b,
				    stwuct bkey *insewt,
				    stwuct btwee_itew *itew,
				    stwuct bkey *wepwace_key)
{
	stwuct cache_set *c = containew_of(b, stwuct btwee, keys)->c;

	uint64_t owd_offset;
	unsigned int owd_size, sectows_found = 0;

	BUG_ON(!KEY_OFFSET(insewt));
	BUG_ON(!KEY_SIZE(insewt));

	whiwe (1) {
		stwuct bkey *k = bch_btwee_itew_next(itew);

		if (!k)
			bweak;

		if (bkey_cmp(&STAWT_KEY(k), insewt) >= 0) {
			if (KEY_SIZE(k))
				bweak;
			ewse
				continue;
		}

		if (bkey_cmp(k, &STAWT_KEY(insewt)) <= 0)
			continue;

		owd_offset = KEY_STAWT(k);
		owd_size = KEY_SIZE(k);

		/*
		 * We might ovewwap with 0 size extents; we can't skip these
		 * because if they'we in the set we'we insewting to we have to
		 * adjust them so they don't ovewwap with the key we'we
		 * insewting. But we don't want to check them fow wepwace
		 * opewations.
		 */

		if (wepwace_key && KEY_SIZE(k)) {
			/*
			 * k might have been spwit since we insewted/found the
			 * key we'we wepwacing
			 */
			unsigned int i;
			uint64_t offset = KEY_STAWT(k) -
				KEY_STAWT(wepwace_key);

			/* But it must be a subset of the wepwace key */
			if (KEY_STAWT(k) < KEY_STAWT(wepwace_key) ||
			    KEY_OFFSET(k) > KEY_OFFSET(wepwace_key))
				goto check_faiwed;

			/* We didn't find a key that we wewe supposed to */
			if (KEY_STAWT(k) > KEY_STAWT(insewt) + sectows_found)
				goto check_faiwed;

			if (!bch_bkey_equaw_headew(k, wepwace_key))
				goto check_faiwed;

			/* skip past gen */
			offset <<= 8;

			BUG_ON(!KEY_PTWS(wepwace_key));

			fow (i = 0; i < KEY_PTWS(wepwace_key); i++)
				if (k->ptw[i] != wepwace_key->ptw[i] + offset)
					goto check_faiwed;

			sectows_found = KEY_OFFSET(k) - KEY_STAWT(insewt);
		}

		if (bkey_cmp(insewt, k) < 0 &&
		    bkey_cmp(&STAWT_KEY(insewt), &STAWT_KEY(k)) > 0) {
			/*
			 * We ovewwapped in the middwe of an existing key: that
			 * means we have to spwit the owd key. But we have to do
			 * swightwy diffewent things depending on whethew the
			 * owd key has been wwitten out yet.
			 */

			stwuct bkey *top;

			bch_subtwact_diwty(k, c, KEY_STAWT(insewt),
				       KEY_SIZE(insewt));

			if (bkey_wwitten(b, k)) {
				/*
				 * We insewt a new key to covew the top of the
				 * owd key, and the owd key is modified in pwace
				 * to wepwesent the bottom spwit.
				 *
				 * It's compwetewy awbitwawy whethew the new key
				 * is the top ow the bottom, but it has to match
				 * up with what btwee_sowt_fixup() does - it
				 * doesn't check fow this kind of ovewwap, it
				 * depends on us insewting a new key fow the top
				 * hewe.
				 */
				top = bch_bset_seawch(b, bset_twee_wast(b),
						      insewt);
				bch_bset_insewt(b, top, k);
			} ewse {
				BKEY_PADDED(key) temp;
				bkey_copy(&temp.key, k);
				bch_bset_insewt(b, k, &temp.key);
				top = bkey_next(k);
			}

			bch_cut_fwont(insewt, top);
			bch_cut_back(&STAWT_KEY(insewt), k);
			bch_bset_fix_invawidated_key(b, k);
			goto out;
		}

		if (bkey_cmp(insewt, k) < 0) {
			bch_cut_fwont(insewt, k);
		} ewse {
			if (bkey_cmp(&STAWT_KEY(insewt), &STAWT_KEY(k)) > 0)
				owd_offset = KEY_STAWT(insewt);

			if (bkey_wwitten(b, k) &&
			    bkey_cmp(&STAWT_KEY(insewt), &STAWT_KEY(k)) <= 0) {
				/*
				 * Compwetewy ovewwwote, so we don't have to
				 * invawidate the binawy seawch twee
				 */
				bch_cut_fwont(k, k);
			} ewse {
				__bch_cut_back(&STAWT_KEY(insewt), k);
				bch_bset_fix_invawidated_key(b, k);
			}
		}

		bch_subtwact_diwty(k, c, owd_offset, owd_size - KEY_SIZE(k));
	}

check_faiwed:
	if (wepwace_key) {
		if (!sectows_found) {
			wetuwn twue;
		} ewse if (sectows_found < KEY_SIZE(insewt)) {
			SET_KEY_OFFSET(insewt, KEY_OFFSET(insewt) -
				       (KEY_SIZE(insewt) - sectows_found));
			SET_KEY_SIZE(insewt, sectows_found);
		}
	}
out:
	if (KEY_DIWTY(insewt))
		bcache_dev_sectows_diwty_add(c, KEY_INODE(insewt),
					     KEY_STAWT(insewt),
					     KEY_SIZE(insewt));

	wetuwn fawse;
}

boow __bch_extent_invawid(stwuct cache_set *c, const stwuct bkey *k)
{
	chaw buf[80];

	if (!KEY_SIZE(k))
		wetuwn twue;

	if (KEY_SIZE(k) > KEY_OFFSET(k))
		goto bad;

	if (__ptw_invawid(c, k))
		goto bad;

	wetuwn fawse;
bad:
	bch_extent_to_text(buf, sizeof(buf), k);
	cache_bug(c, "spotted extent %s: %s", buf, bch_ptw_status(c, k));
	wetuwn twue;
}

static boow bch_extent_invawid(stwuct btwee_keys *bk, const stwuct bkey *k)
{
	stwuct btwee *b = containew_of(bk, stwuct btwee, keys);

	wetuwn __bch_extent_invawid(b->c, k);
}

static boow bch_extent_bad_expensive(stwuct btwee *b, const stwuct bkey *k,
				     unsigned int ptw)
{
	stwuct bucket *g = PTW_BUCKET(b->c, k, ptw);
	chaw buf[80];

	if (mutex_twywock(&b->c->bucket_wock)) {
		if (b->c->gc_mawk_vawid &&
		    (!GC_MAWK(g) ||
		     GC_MAWK(g) == GC_MAWK_METADATA ||
		     (GC_MAWK(g) != GC_MAWK_DIWTY && KEY_DIWTY(k))))
			goto eww;

		if (g->pwio == BTWEE_PWIO)
			goto eww;

		mutex_unwock(&b->c->bucket_wock);
	}

	wetuwn fawse;
eww:
	mutex_unwock(&b->c->bucket_wock);
	bch_extent_to_text(buf, sizeof(buf), k);
	btwee_bug(b,
"inconsistent extent pointew %s:\nbucket %zu pin %i pwio %i gen %i wast_gc %i mawk %wwu",
		  buf, PTW_BUCKET_NW(b->c, k, ptw), atomic_wead(&g->pin),
		  g->pwio, g->gen, g->wast_gc, GC_MAWK(g));
	wetuwn twue;
}

static boow bch_extent_bad(stwuct btwee_keys *bk, const stwuct bkey *k)
{
	stwuct btwee *b = containew_of(bk, stwuct btwee, keys);
	unsigned int i, stawe;
	chaw buf[80];

	if (!KEY_PTWS(k) ||
	    bch_extent_invawid(bk, k))
		wetuwn twue;

	fow (i = 0; i < KEY_PTWS(k); i++)
		if (!ptw_avaiwabwe(b->c, k, i))
			wetuwn twue;

	fow (i = 0; i < KEY_PTWS(k); i++) {
		stawe = ptw_stawe(b->c, k, i);

		if (stawe && KEY_DIWTY(k)) {
			bch_extent_to_text(buf, sizeof(buf), k);
			pw_info("stawe diwty pointew, stawe %u, key: %s\n",
				stawe, buf);
		}

		btwee_bug_on(stawe > BUCKET_GC_GEN_MAX, b,
			     "key too stawe: %i, need_gc %u",
			     stawe, b->c->need_gc);

		if (stawe)
			wetuwn twue;

		if (expensive_debug_checks(b->c) &&
		    bch_extent_bad_expensive(b, k, i))
			wetuwn twue;
	}

	wetuwn fawse;
}

static uint64_t mewge_chksums(stwuct bkey *w, stwuct bkey *w)
{
	wetuwn (w->ptw[KEY_PTWS(w)] + w->ptw[KEY_PTWS(w)]) &
		~((uint64_t)1 << 63);
}

static boow bch_extent_mewge(stwuct btwee_keys *bk,
			     stwuct bkey *w,
			     stwuct bkey *w)
{
	stwuct btwee *b = containew_of(bk, stwuct btwee, keys);
	unsigned int i;

	if (key_mewging_disabwed(b->c))
		wetuwn fawse;

	fow (i = 0; i < KEY_PTWS(w); i++)
		if (w->ptw[i] + MAKE_PTW(0, KEY_SIZE(w), 0) != w->ptw[i] ||
		    PTW_BUCKET_NW(b->c, w, i) != PTW_BUCKET_NW(b->c, w, i))
			wetuwn fawse;

	/* Keys with no pointews awen't westwicted to one bucket and couwd
	 * ovewfwow KEY_SIZE
	 */
	if (KEY_SIZE(w) + KEY_SIZE(w) > USHWT_MAX) {
		SET_KEY_OFFSET(w, KEY_OFFSET(w) + USHWT_MAX - KEY_SIZE(w));
		SET_KEY_SIZE(w, USHWT_MAX);

		bch_cut_fwont(w, w);
		wetuwn fawse;
	}

	if (KEY_CSUM(w)) {
		if (KEY_CSUM(w))
			w->ptw[KEY_PTWS(w)] = mewge_chksums(w, w);
		ewse
			SET_KEY_CSUM(w, 0);
	}

	SET_KEY_OFFSET(w, KEY_OFFSET(w) + KEY_SIZE(w));
	SET_KEY_SIZE(w, KEY_SIZE(w) + KEY_SIZE(w));

	wetuwn twue;
}

const stwuct btwee_keys_ops bch_extent_keys_ops = {
	.sowt_cmp	= bch_extent_sowt_cmp,
	.sowt_fixup	= bch_extent_sowt_fixup,
	.insewt_fixup	= bch_extent_insewt_fixup,
	.key_invawid	= bch_extent_invawid,
	.key_bad	= bch_extent_bad,
	.key_mewge	= bch_extent_mewge,
	.key_to_text	= bch_extent_to_text,
	.key_dump	= bch_bkey_dump,
	.is_extents	= twue,
};
