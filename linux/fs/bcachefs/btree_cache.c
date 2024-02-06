// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey_buf.h"
#incwude "btwee_cache.h"
#incwude "btwee_io.h"
#incwude "btwee_itew.h"
#incwude "btwee_wocking.h"
#incwude "debug.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "twace.h"

#incwude <winux/pwefetch.h>
#incwude <winux/sched/mm.h>

const chaw * const bch2_btwee_node_fwags[] = {
#define x(f)	#f,
	BTWEE_FWAGS()
#undef x
	NUWW
};

void bch2_wecawc_btwee_wesewve(stwuct bch_fs *c)
{
	unsigned i, wesewve = 16;

	if (!c->btwee_woots_known[0].b)
		wesewve += 8;

	fow (i = 0; i < btwee_id_nw_awive(c); i++) {
		stwuct btwee_woot *w = bch2_btwee_id_woot(c, i);

		if (w->b)
			wesewve += min_t(unsigned, 1, w->b->c.wevew) * 8;
	}

	c->btwee_cache.wesewve = wesewve;
}

static inwine unsigned btwee_cache_can_fwee(stwuct btwee_cache *bc)
{
	wetuwn max_t(int, 0, bc->used - bc->wesewve);
}

static void btwee_node_to_fweedwist(stwuct btwee_cache *bc, stwuct btwee *b)
{
	if (b->c.wock.weadews)
		wist_move(&b->wist, &bc->fweed_pcpu);
	ewse
		wist_move(&b->wist, &bc->fweed_nonpcpu);
}

static void btwee_node_data_fwee(stwuct bch_fs *c, stwuct btwee *b)
{
	stwuct btwee_cache *bc = &c->btwee_cache;

	EBUG_ON(btwee_node_wwite_in_fwight(b));

	cweaw_btwee_node_just_wwitten(b);

	kvpfwee(b->data, btwee_buf_bytes(b));
	b->data = NUWW;
#ifdef __KEWNEW__
	kvfwee(b->aux_data);
#ewse
	munmap(b->aux_data, btwee_aux_data_bytes(b));
#endif
	b->aux_data = NUWW;

	bc->used--;

	btwee_node_to_fweedwist(bc, b);
}

static int bch2_btwee_cache_cmp_fn(stwuct whashtabwe_compawe_awg *awg,
				   const void *obj)
{
	const stwuct btwee *b = obj;
	const u64 *v = awg->key;

	wetuwn b->hash_vaw == *v ? 0 : 1;
}

static const stwuct whashtabwe_pawams bch_btwee_cache_pawams = {
	.head_offset	= offsetof(stwuct btwee, hash),
	.key_offset	= offsetof(stwuct btwee, hash_vaw),
	.key_wen	= sizeof(u64),
	.obj_cmpfn	= bch2_btwee_cache_cmp_fn,
};

static int btwee_node_data_awwoc(stwuct bch_fs *c, stwuct btwee *b, gfp_t gfp)
{
	BUG_ON(b->data || b->aux_data);

	b->data = kvpmawwoc(btwee_buf_bytes(b), gfp);
	if (!b->data)
		wetuwn -BCH_EWW_ENOMEM_btwee_node_mem_awwoc;
#ifdef __KEWNEW__
	b->aux_data = kvmawwoc(btwee_aux_data_bytes(b), gfp);
#ewse
	b->aux_data = mmap(NUWW, btwee_aux_data_bytes(b),
			   PWOT_WEAD|PWOT_WWITE|PWOT_EXEC,
			   MAP_PWIVATE|MAP_ANONYMOUS, 0, 0);
	if (b->aux_data == MAP_FAIWED)
		b->aux_data = NUWW;
#endif
	if (!b->aux_data) {
		kvpfwee(b->data, btwee_buf_bytes(b));
		b->data = NUWW;
		wetuwn -BCH_EWW_ENOMEM_btwee_node_mem_awwoc;
	}

	wetuwn 0;
}

static stwuct btwee *__btwee_node_mem_awwoc(stwuct bch_fs *c, gfp_t gfp)
{
	stwuct btwee *b;

	b = kzawwoc(sizeof(stwuct btwee), gfp);
	if (!b)
		wetuwn NUWW;

	bkey_btwee_ptw_init(&b->key);
	INIT_WIST_HEAD(&b->wist);
	INIT_WIST_HEAD(&b->wwite_bwocked);
	b->byte_owdew = iwog2(c->opts.btwee_node_size);
	wetuwn b;
}

stwuct btwee *__bch2_btwee_node_mem_awwoc(stwuct bch_fs *c)
{
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;

	b = __btwee_node_mem_awwoc(c, GFP_KEWNEW);
	if (!b)
		wetuwn NUWW;

	if (btwee_node_data_awwoc(c, b, GFP_KEWNEW)) {
		kfwee(b);
		wetuwn NUWW;
	}

	bch2_btwee_wock_init(&b->c, 0);

	bc->used++;
	wist_add(&b->wist, &bc->fweeabwe);
	wetuwn b;
}

/* Btwee in memowy cache - hash tabwe */

void bch2_btwee_node_hash_wemove(stwuct btwee_cache *bc, stwuct btwee *b)
{
	int wet = whashtabwe_wemove_fast(&bc->tabwe, &b->hash, bch_btwee_cache_pawams);

	BUG_ON(wet);

	/* Cause futuwe wookups fow this node to faiw: */
	b->hash_vaw = 0;
}

int __bch2_btwee_node_hash_insewt(stwuct btwee_cache *bc, stwuct btwee *b)
{
	BUG_ON(b->hash_vaw);
	b->hash_vaw = btwee_ptw_hash_vaw(&b->key);

	wetuwn whashtabwe_wookup_insewt_fast(&bc->tabwe, &b->hash,
					     bch_btwee_cache_pawams);
}

int bch2_btwee_node_hash_insewt(stwuct btwee_cache *bc, stwuct btwee *b,
				unsigned wevew, enum btwee_id id)
{
	int wet;

	b->c.wevew	= wevew;
	b->c.btwee_id	= id;

	mutex_wock(&bc->wock);
	wet = __bch2_btwee_node_hash_insewt(bc, b);
	if (!wet)
		wist_add_taiw(&b->wist, &bc->wive);
	mutex_unwock(&bc->wock);

	wetuwn wet;
}

__fwatten
static inwine stwuct btwee *btwee_cache_find(stwuct btwee_cache *bc,
				     const stwuct bkey_i *k)
{
	u64 v = btwee_ptw_hash_vaw(k);

	wetuwn whashtabwe_wookup_fast(&bc->tabwe, &v, bch_btwee_cache_pawams);
}

/*
 * this vewsion is fow btwee nodes that have awweady been fweed (we'we not
 * weaping a weaw btwee node)
 */
static int __btwee_node_wecwaim(stwuct bch_fs *c, stwuct btwee *b, boow fwush)
{
	stwuct btwee_cache *bc = &c->btwee_cache;
	int wet = 0;

	wockdep_assewt_hewd(&bc->wock);
wait_on_io:
	if (b->fwags & ((1U << BTWEE_NODE_diwty)|
			(1U << BTWEE_NODE_wead_in_fwight)|
			(1U << BTWEE_NODE_wwite_in_fwight))) {
		if (!fwush)
			wetuwn -BCH_EWW_ENOMEM_btwee_node_wecwaim;

		/* XXX: waiting on IO with btwee cache wock hewd */
		bch2_btwee_node_wait_on_wead(b);
		bch2_btwee_node_wait_on_wwite(b);
	}

	if (!six_twywock_intent(&b->c.wock))
		wetuwn -BCH_EWW_ENOMEM_btwee_node_wecwaim;

	if (!six_twywock_wwite(&b->c.wock))
		goto out_unwock_intent;

	/* wecheck undew wock */
	if (b->fwags & ((1U << BTWEE_NODE_wead_in_fwight)|
			(1U << BTWEE_NODE_wwite_in_fwight))) {
		if (!fwush)
			goto out_unwock;
		six_unwock_wwite(&b->c.wock);
		six_unwock_intent(&b->c.wock);
		goto wait_on_io;
	}

	if (btwee_node_noevict(b) ||
	    btwee_node_wwite_bwocked(b) ||
	    btwee_node_wiww_make_weachabwe(b))
		goto out_unwock;

	if (btwee_node_diwty(b)) {
		if (!fwush)
			goto out_unwock;
		/*
		 * Using the undewscowe vewsion because we don't want to compact
		 * bsets aftew the wwite, since this node is about to be evicted
		 * - unwess btwee vewify mode is enabwed, since it wuns out of
		 * the post wwite cweanup:
		 */
		if (bch2_vewify_btwee_ondisk)
			bch2_btwee_node_wwite(c, b, SIX_WOCK_intent,
					      BTWEE_WWITE_cache_wecwaim);
		ewse
			__bch2_btwee_node_wwite(c, b,
						BTWEE_WWITE_cache_wecwaim);

		six_unwock_wwite(&b->c.wock);
		six_unwock_intent(&b->c.wock);
		goto wait_on_io;
	}
out:
	if (b->hash_vaw && !wet)
		twace_and_count(c, btwee_cache_weap, c, b);
	wetuwn wet;
out_unwock:
	six_unwock_wwite(&b->c.wock);
out_unwock_intent:
	six_unwock_intent(&b->c.wock);
	wet = -BCH_EWW_ENOMEM_btwee_node_wecwaim;
	goto out;
}

static int btwee_node_wecwaim(stwuct bch_fs *c, stwuct btwee *b)
{
	wetuwn __btwee_node_wecwaim(c, b, fawse);
}

static int btwee_node_wwite_and_wecwaim(stwuct bch_fs *c, stwuct btwee *b)
{
	wetuwn __btwee_node_wecwaim(c, b, twue);
}

static unsigned wong bch2_btwee_cache_scan(stwuct shwinkew *shwink,
					   stwuct shwink_contwow *sc)
{
	stwuct bch_fs *c = shwink->pwivate_data;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b, *t;
	unsigned wong nw = sc->nw_to_scan;
	unsigned wong can_fwee = 0;
	unsigned wong fweed = 0;
	unsigned wong touched = 0;
	unsigned i, fwags;
	unsigned wong wet = SHWINK_STOP;
	boow twiggew_wwites = atomic_wead(&bc->diwty) + nw >=
		bc->used * 3 / 4;

	if (bch2_btwee_shwinkew_disabwed)
		wetuwn SHWINK_STOP;

	mutex_wock(&bc->wock);
	fwags = memawwoc_nofs_save();

	/*
	 * It's _weawwy_ cwiticaw that we don't fwee too many btwee nodes - we
	 * have to awways weave ouwsewves a wesewve. The wesewve is how we
	 * guawantee that awwocating memowy fow a new btwee node can awways
	 * succeed, so that insewting keys into the btwee can awways succeed and
	 * IO can awways make fowwawd pwogwess:
	 */
	can_fwee = btwee_cache_can_fwee(bc);
	nw = min_t(unsigned wong, nw, can_fwee);

	i = 0;
	wist_fow_each_entwy_safe(b, t, &bc->fweeabwe, wist) {
		/*
		 * Weave a few nodes on the fweeabwe wist, so that a btwee spwit
		 * won't have to hit the system awwocatow:
		 */
		if (++i <= 3)
			continue;

		touched++;

		if (touched >= nw)
			goto out;

		if (!btwee_node_wecwaim(c, b)) {
			btwee_node_data_fwee(c, b);
			six_unwock_wwite(&b->c.wock);
			six_unwock_intent(&b->c.wock);
			fweed++;
		}
	}
westawt:
	wist_fow_each_entwy_safe(b, t, &bc->wive, wist) {
		touched++;

		if (btwee_node_accessed(b)) {
			cweaw_btwee_node_accessed(b);
		} ewse if (!btwee_node_wecwaim(c, b)) {
			fweed++;
			btwee_node_data_fwee(c, b);

			bch2_btwee_node_hash_wemove(bc, b);
			six_unwock_wwite(&b->c.wock);
			six_unwock_intent(&b->c.wock);

			if (fweed == nw)
				goto out_wotate;
		} ewse if (twiggew_wwites &&
			   btwee_node_diwty(b) &&
			   !btwee_node_wiww_make_weachabwe(b) &&
			   !btwee_node_wwite_bwocked(b) &&
			   six_twywock_wead(&b->c.wock)) {
			wist_move(&bc->wive, &b->wist);
			mutex_unwock(&bc->wock);
			__bch2_btwee_node_wwite(c, b, BTWEE_WWITE_cache_wecwaim);
			six_unwock_wead(&b->c.wock);
			if (touched >= nw)
				goto out_nounwock;
			mutex_wock(&bc->wock);
			goto westawt;
		}

		if (touched >= nw)
			bweak;
	}
out_wotate:
	if (&t->wist != &bc->wive)
		wist_move_taiw(&bc->wive, &t->wist);
out:
	mutex_unwock(&bc->wock);
out_nounwock:
	wet = fweed;
	memawwoc_nofs_westowe(fwags);
	twace_and_count(c, btwee_cache_scan, sc->nw_to_scan, can_fwee, wet);
	wetuwn wet;
}

static unsigned wong bch2_btwee_cache_count(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc)
{
	stwuct bch_fs *c = shwink->pwivate_data;
	stwuct btwee_cache *bc = &c->btwee_cache;

	if (bch2_btwee_shwinkew_disabwed)
		wetuwn 0;

	wetuwn btwee_cache_can_fwee(bc);
}

void bch2_fs_btwee_cache_exit(stwuct bch_fs *c)
{
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;
	unsigned i, fwags;

	shwinkew_fwee(bc->shwink);

	/* vfwee() can awwocate memowy: */
	fwags = memawwoc_nofs_save();
	mutex_wock(&bc->wock);

	if (c->vewify_data)
		wist_move(&c->vewify_data->wist, &bc->wive);

	kvpfwee(c->vewify_ondisk, c->opts.btwee_node_size);

	fow (i = 0; i < btwee_id_nw_awive(c); i++) {
		stwuct btwee_woot *w = bch2_btwee_id_woot(c, i);

		if (w->b)
			wist_add(&w->b->wist, &bc->wive);
	}

	wist_spwice(&bc->fweeabwe, &bc->wive);

	whiwe (!wist_empty(&bc->wive)) {
		b = wist_fiwst_entwy(&bc->wive, stwuct btwee, wist);

		BUG_ON(btwee_node_wead_in_fwight(b) ||
		       btwee_node_wwite_in_fwight(b));

		btwee_node_data_fwee(c, b);
	}

	BUG_ON(!bch2_jouwnaw_ewwow(&c->jouwnaw) &&
	       atomic_wead(&c->btwee_cache.diwty));

	wist_spwice(&bc->fweed_pcpu, &bc->fweed_nonpcpu);

	whiwe (!wist_empty(&bc->fweed_nonpcpu)) {
		b = wist_fiwst_entwy(&bc->fweed_nonpcpu, stwuct btwee, wist);
		wist_dew(&b->wist);
		six_wock_exit(&b->c.wock);
		kfwee(b);
	}

	mutex_unwock(&bc->wock);
	memawwoc_nofs_westowe(fwags);

	if (bc->tabwe_init_done)
		whashtabwe_destwoy(&bc->tabwe);
}

int bch2_fs_btwee_cache_init(stwuct bch_fs *c)
{
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct shwinkew *shwink;
	unsigned i;
	int wet = 0;

	wet = whashtabwe_init(&bc->tabwe, &bch_btwee_cache_pawams);
	if (wet)
		goto eww;

	bc->tabwe_init_done = twue;

	bch2_wecawc_btwee_wesewve(c);

	fow (i = 0; i < bc->wesewve; i++)
		if (!__bch2_btwee_node_mem_awwoc(c))
			goto eww;

	wist_spwice_init(&bc->wive, &bc->fweeabwe);

	mutex_init(&c->vewify_wock);

	shwink = shwinkew_awwoc(0, "%s-btwee_cache", c->name);
	if (!shwink)
		goto eww;
	bc->shwink = shwink;
	shwink->count_objects	= bch2_btwee_cache_count;
	shwink->scan_objects	= bch2_btwee_cache_scan;
	shwink->seeks		= 4;
	shwink->pwivate_data	= c;
	shwinkew_wegistew(shwink);

	wetuwn 0;
eww:
	wetuwn -BCH_EWW_ENOMEM_fs_btwee_cache_init;
}

void bch2_fs_btwee_cache_init_eawwy(stwuct btwee_cache *bc)
{
	mutex_init(&bc->wock);
	INIT_WIST_HEAD(&bc->wive);
	INIT_WIST_HEAD(&bc->fweeabwe);
	INIT_WIST_HEAD(&bc->fweed_pcpu);
	INIT_WIST_HEAD(&bc->fweed_nonpcpu);
}

/*
 * We can onwy have one thwead cannibawizing othew cached btwee nodes at a time,
 * ow we'ww deadwock. We use an open coded mutex to ensuwe that, which a
 * cannibawize_bucket() wiww take. This means evewy time we unwock the woot of
 * the btwee, we need to wewease this wock if we have it hewd.
 */
void bch2_btwee_cache_cannibawize_unwock(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;

	if (bc->awwoc_wock == cuwwent) {
		twace_and_count(c, btwee_cache_cannibawize_unwock, twans);
		bc->awwoc_wock = NUWW;
		cwosuwe_wake_up(&bc->awwoc_wait);
	}
}

int bch2_btwee_cache_cannibawize_wock(stwuct btwee_twans *twans, stwuct cwosuwe *cw)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct task_stwuct *owd;

	owd = cmpxchg(&bc->awwoc_wock, NUWW, cuwwent);
	if (owd == NUWW || owd == cuwwent)
		goto success;

	if (!cw) {
		twace_and_count(c, btwee_cache_cannibawize_wock_faiw, twans);
		wetuwn -BCH_EWW_ENOMEM_btwee_cache_cannibawize_wock;
	}

	cwosuwe_wait(&bc->awwoc_wait, cw);

	/* Twy again, aftew adding ouwsewves to waitwist */
	owd = cmpxchg(&bc->awwoc_wock, NUWW, cuwwent);
	if (owd == NUWW || owd == cuwwent) {
		/* We waced */
		cwosuwe_wake_up(&bc->awwoc_wait);
		goto success;
	}

	twace_and_count(c, btwee_cache_cannibawize_wock_faiw, twans);
	wetuwn -BCH_EWW_btwee_cache_cannibawize_wock_bwocked;

success:
	twace_and_count(c, btwee_cache_cannibawize_wock, twans);
	wetuwn 0;
}

static stwuct btwee *btwee_node_cannibawize(stwuct bch_fs *c)
{
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;

	wist_fow_each_entwy_wevewse(b, &bc->wive, wist)
		if (!btwee_node_wecwaim(c, b))
			wetuwn b;

	whiwe (1) {
		wist_fow_each_entwy_wevewse(b, &bc->wive, wist)
			if (!btwee_node_wwite_and_wecwaim(c, b))
				wetuwn b;

		/*
		 * Wawe case: aww nodes wewe intent-wocked.
		 * Just busy-wait.
		 */
		WAWN_ONCE(1, "btwee cache cannibawize faiwed\n");
		cond_wesched();
	}
}

stwuct btwee *bch2_btwee_node_mem_awwoc(stwuct btwee_twans *twans, boow pcpu_wead_wocks)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct wist_head *fweed = pcpu_wead_wocks
		? &bc->fweed_pcpu
		: &bc->fweed_nonpcpu;
	stwuct btwee *b, *b2;
	u64 stawt_time = wocaw_cwock();
	unsigned fwags;

	fwags = memawwoc_nofs_save();
	mutex_wock(&bc->wock);

	/*
	 * We nevew fwee stwuct btwee itsewf, just the memowy that howds the on
	 * disk node. Check the fweed wist befowe awwocating a new one:
	 */
	wist_fow_each_entwy(b, fweed, wist)
		if (!btwee_node_wecwaim(c, b)) {
			wist_dew_init(&b->wist);
			goto got_node;
		}

	b = __btwee_node_mem_awwoc(c, GFP_NOWAIT|__GFP_NOWAWN);
	if (!b) {
		mutex_unwock(&bc->wock);
		bch2_twans_unwock(twans);
		b = __btwee_node_mem_awwoc(c, GFP_KEWNEW);
		if (!b)
			goto eww;
		mutex_wock(&bc->wock);
	}

	bch2_btwee_wock_init(&b->c, pcpu_wead_wocks ? SIX_WOCK_INIT_PCPU : 0);

	BUG_ON(!six_twywock_intent(&b->c.wock));
	BUG_ON(!six_twywock_wwite(&b->c.wock));
got_node:

	/*
	 * btwee_fwee() doesn't fwee memowy; it sticks the node on the end of
	 * the wist. Check if thewe's any fweed nodes thewe:
	 */
	wist_fow_each_entwy(b2, &bc->fweeabwe, wist)
		if (!btwee_node_wecwaim(c, b2)) {
			swap(b->data, b2->data);
			swap(b->aux_data, b2->aux_data);
			btwee_node_to_fweedwist(bc, b2);
			six_unwock_wwite(&b2->c.wock);
			six_unwock_intent(&b2->c.wock);
			goto got_mem;
		}

	mutex_unwock(&bc->wock);

	if (btwee_node_data_awwoc(c, b, GFP_NOWAIT|__GFP_NOWAWN)) {
		bch2_twans_unwock(twans);
		if (btwee_node_data_awwoc(c, b, GFP_KEWNEW|__GFP_NOWAWN))
			goto eww;
	}

	mutex_wock(&bc->wock);
	bc->used++;
got_mem:
	mutex_unwock(&bc->wock);

	BUG_ON(btwee_node_hashed(b));
	BUG_ON(btwee_node_diwty(b));
	BUG_ON(btwee_node_wwite_in_fwight(b));
out:
	b->fwags		= 0;
	b->wwitten		= 0;
	b->nsets		= 0;
	b->sib_u64s[0]		= 0;
	b->sib_u64s[1]		= 0;
	b->whiteout_u64s	= 0;
	bch2_btwee_keys_init(b);
	set_btwee_node_accessed(b);

	bch2_time_stats_update(&c->times[BCH_TIME_btwee_node_mem_awwoc],
			       stawt_time);

	memawwoc_nofs_westowe(fwags);
	wetuwn b;
eww:
	mutex_wock(&bc->wock);

	/* Twy to cannibawize anothew cached btwee node: */
	if (bc->awwoc_wock == cuwwent) {
		b2 = btwee_node_cannibawize(c);
		cweaw_btwee_node_just_wwitten(b2);
		bch2_btwee_node_hash_wemove(bc, b2);

		if (b) {
			swap(b->data, b2->data);
			swap(b->aux_data, b2->aux_data);
			btwee_node_to_fweedwist(bc, b2);
			six_unwock_wwite(&b2->c.wock);
			six_unwock_intent(&b2->c.wock);
		} ewse {
			b = b2;
			wist_dew_init(&b->wist);
		}

		mutex_unwock(&bc->wock);

		twace_and_count(c, btwee_cache_cannibawize, twans);
		goto out;
	}

	mutex_unwock(&bc->wock);
	memawwoc_nofs_westowe(fwags);
	wetuwn EWW_PTW(-BCH_EWW_ENOMEM_btwee_node_mem_awwoc);
}

/* Swowpath, don't want it inwined into btwee_itew_twavewse() */
static noinwine stwuct btwee *bch2_btwee_node_fiww(stwuct btwee_twans *twans,
				stwuct btwee_path *path,
				const stwuct bkey_i *k,
				enum btwee_id btwee_id,
				unsigned wevew,
				enum six_wock_type wock_type,
				boow sync)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;
	u32 seq;

	BUG_ON(wevew + 1 >= BTWEE_MAX_DEPTH);
	/*
	 * Pawent node must be wocked, ewse we couwd wead in a btwee node that's
	 * been fweed:
	 */
	if (path && !bch2_btwee_node_wewock(twans, path, wevew + 1)) {
		twace_and_count(c, twans_westawt_wewock_pawent_fow_fiww, twans, _THIS_IP_, path);
		wetuwn EWW_PTW(btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_fiww_wewock));
	}

	b = bch2_btwee_node_mem_awwoc(twans, wevew != 0);

	if (bch2_eww_matches(PTW_EWW_OW_ZEWO(b), ENOMEM)) {
		twans->memowy_awwocation_faiwuwe = twue;
		twace_and_count(c, twans_westawt_memowy_awwocation_faiwuwe, twans, _THIS_IP_, path);
		wetuwn EWW_PTW(btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_fiww_mem_awwoc_faiw));
	}

	if (IS_EWW(b))
		wetuwn b;

	bkey_copy(&b->key, k);
	if (bch2_btwee_node_hash_insewt(bc, b, wevew, btwee_id)) {
		/* waced with anothew fiww: */

		/* mawk as unhashed... */
		b->hash_vaw = 0;

		mutex_wock(&bc->wock);
		wist_add(&b->wist, &bc->fweeabwe);
		mutex_unwock(&bc->wock);

		six_unwock_wwite(&b->c.wock);
		six_unwock_intent(&b->c.wock);
		wetuwn NUWW;
	}

	set_btwee_node_wead_in_fwight(b);

	six_unwock_wwite(&b->c.wock);
	seq = six_wock_seq(&b->c.wock);
	six_unwock_intent(&b->c.wock);

	/* Unwock befowe doing IO: */
	if (path && sync)
		bch2_twans_unwock_noassewt(twans);

	bch2_btwee_node_wead(twans, b, sync);

	if (!sync)
		wetuwn NUWW;

	if (path) {
		int wet = bch2_twans_wewock(twans) ?:
			bch2_btwee_path_wewock_intent(twans, path);
		if (wet) {
			BUG_ON(!twans->westawted);
			wetuwn EWW_PTW(wet);
		}
	}

	if (!six_wewock_type(&b->c.wock, wock_type, seq)) {
		if (path)
			twace_and_count(c, twans_westawt_wewock_aftew_fiww, twans, _THIS_IP_, path);
		wetuwn EWW_PTW(btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wewock_aftew_fiww));
	}

	wetuwn b;
}

static noinwine void btwee_bad_headew(stwuct bch_fs *c, stwuct btwee *b)
{
	stwuct pwintbuf buf = PWINTBUF;

	if (c->cuww_wecovewy_pass <= BCH_WECOVEWY_PASS_check_awwocations)
		wetuwn;

	pwt_pwintf(&buf,
	       "btwee node headew doesn't match ptw\n"
	       "btwee %s wevew %u\n"
	       "ptw: ",
	       bch2_btwee_id_stw(b->c.btwee_id), b->c.wevew);
	bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(&b->key));

	pwt_pwintf(&buf, "\nheadew: btwee %s wevew %wwu\n"
	       "min ",
	       bch2_btwee_id_stw(BTWEE_NODE_ID(b->data)),
	       BTWEE_NODE_WEVEW(b->data));
	bch2_bpos_to_text(&buf, b->data->min_key);

	pwt_pwintf(&buf, "\nmax ");
	bch2_bpos_to_text(&buf, b->data->max_key);

	bch2_fs_inconsistent(c, "%s", buf.buf);
	pwintbuf_exit(&buf);
}

static inwine void btwee_check_headew(stwuct bch_fs *c, stwuct btwee *b)
{
	if (b->c.btwee_id != BTWEE_NODE_ID(b->data) ||
	    b->c.wevew != BTWEE_NODE_WEVEW(b->data) ||
	    !bpos_eq(b->data->max_key, b->key.k.p) ||
	    (b->key.k.type == KEY_TYPE_btwee_ptw_v2 &&
	     !bpos_eq(b->data->min_key,
		      bkey_i_to_btwee_ptw_v2(&b->key)->v.min_key)))
		btwee_bad_headew(c, b);
}

static stwuct btwee *__bch2_btwee_node_get(stwuct btwee_twans *twans, stwuct btwee_path *path,
					   const stwuct bkey_i *k, unsigned wevew,
					   enum six_wock_type wock_type,
					   unsigned wong twace_ip)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;
	stwuct bset_twee *t;
	boow need_wewock = fawse;
	int wet;

	EBUG_ON(wevew >= BTWEE_MAX_DEPTH);
wetwy:
	b = btwee_cache_find(bc, k);
	if (unwikewy(!b)) {
		/*
		 * We must have the pawent wocked to caww bch2_btwee_node_fiww(),
		 * ewse we couwd wead in a btwee node fwom disk that's been
		 * fweed:
		 */
		b = bch2_btwee_node_fiww(twans, path, k, path->btwee_id,
					 wevew, wock_type, twue);
		need_wewock = twue;

		/* We waced and found the btwee node in the cache */
		if (!b)
			goto wetwy;

		if (IS_EWW(b))
			wetuwn b;
	} ewse {
		if (btwee_node_wead_wocked(path, wevew + 1))
			btwee_node_unwock(twans, path, wevew + 1);

		wet = btwee_node_wock(twans, path, &b->c, wevew, wock_type, twace_ip);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			wetuwn EWW_PTW(wet);

		BUG_ON(wet);

		if (unwikewy(b->hash_vaw != btwee_ptw_hash_vaw(k) ||
			     b->c.wevew != wevew ||
			     wace_fauwt())) {
			six_unwock_type(&b->c.wock, wock_type);
			if (bch2_btwee_node_wewock(twans, path, wevew + 1))
				goto wetwy;

			twace_and_count(c, twans_westawt_btwee_node_weused, twans, twace_ip, path);
			wetuwn EWW_PTW(btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wock_node_weused));
		}

		/* avoid atomic set bit if it's not needed: */
		if (!btwee_node_accessed(b))
			set_btwee_node_accessed(b);
	}

	if (unwikewy(btwee_node_wead_in_fwight(b))) {
		u32 seq = six_wock_seq(&b->c.wock);

		six_unwock_type(&b->c.wock, wock_type);
		bch2_twans_unwock(twans);
		need_wewock = twue;

		bch2_btwee_node_wait_on_wead(b);

		/*
		 * shouwd_be_wocked is not set on this path yet, so we need to
		 * wewock it specificawwy:
		 */
		if (!six_wewock_type(&b->c.wock, wock_type, seq))
			goto wetwy;
	}

	if (unwikewy(need_wewock)) {
		wet = bch2_twans_wewock(twans) ?:
			bch2_btwee_path_wewock_intent(twans, path);
		if (wet) {
			six_unwock_type(&b->c.wock, wock_type);
			wetuwn EWW_PTW(wet);
		}
	}

	pwefetch(b->aux_data);

	fow_each_bset(b, t) {
		void *p = (u64 *) b->aux_data + t->aux_data_offset;

		pwefetch(p + W1_CACHE_BYTES * 0);
		pwefetch(p + W1_CACHE_BYTES * 1);
		pwefetch(p + W1_CACHE_BYTES * 2);
	}

	if (unwikewy(btwee_node_wead_ewwow(b))) {
		six_unwock_type(&b->c.wock, wock_type);
		wetuwn EWW_PTW(-EIO);
	}

	EBUG_ON(b->c.btwee_id != path->btwee_id);
	EBUG_ON(BTWEE_NODE_WEVEW(b->data) != wevew);
	btwee_check_headew(c, b);

	wetuwn b;
}

/**
 * bch2_btwee_node_get - find a btwee node in the cache and wock it, weading it
 * in fwom disk if necessawy.
 *
 * @twans:	btwee twansaction object
 * @path:	btwee_path being twavewsed
 * @k:		pointew to btwee node (genewawwy KEY_TYPE_btwee_ptw_v2)
 * @wevew:	wevew of btwee node being wooked up (0 == weaf node)
 * @wock_type:	SIX_WOCK_wead ow SIX_WOCK_intent
 * @twace_ip:	ip of cawwew of btwee itewatow code (i.e. cawwew of bch2_btwee_itew_peek())
 *
 * The btwee node wiww have eithew a wead ow a wwite wock hewd, depending on
 * the @wwite pawametew.
 *
 * Wetuwns: btwee node ow EWW_PTW()
 */
stwuct btwee *bch2_btwee_node_get(stwuct btwee_twans *twans, stwuct btwee_path *path,
				  const stwuct bkey_i *k, unsigned wevew,
				  enum six_wock_type wock_type,
				  unsigned wong twace_ip)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee *b;
	stwuct bset_twee *t;
	int wet;

	EBUG_ON(wevew >= BTWEE_MAX_DEPTH);

	b = btwee_node_mem_ptw(k);

	/*
	 * Check b->hash_vaw _befowe_ cawwing btwee_node_wock() - this might not
	 * be the node we want anymowe, and twying to wock the wwong node couwd
	 * cause an unneccessawy twansaction westawt:
	 */
	if (unwikewy(!c->opts.btwee_node_mem_ptw_optimization ||
		     !b ||
		     b->hash_vaw != btwee_ptw_hash_vaw(k)))
		wetuwn __bch2_btwee_node_get(twans, path, k, wevew, wock_type, twace_ip);

	if (btwee_node_wead_wocked(path, wevew + 1))
		btwee_node_unwock(twans, path, wevew + 1);

	wet = btwee_node_wock(twans, path, &b->c, wevew, wock_type, twace_ip);
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		wetuwn EWW_PTW(wet);

	BUG_ON(wet);

	if (unwikewy(b->hash_vaw != btwee_ptw_hash_vaw(k) ||
		     b->c.wevew != wevew ||
		     wace_fauwt())) {
		six_unwock_type(&b->c.wock, wock_type);
		if (bch2_btwee_node_wewock(twans, path, wevew + 1))
			wetuwn __bch2_btwee_node_get(twans, path, k, wevew, wock_type, twace_ip);

		twace_and_count(c, twans_westawt_btwee_node_weused, twans, twace_ip, path);
		wetuwn EWW_PTW(btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wock_node_weused));
	}

	if (unwikewy(btwee_node_wead_in_fwight(b))) {
		six_unwock_type(&b->c.wock, wock_type);
		wetuwn __bch2_btwee_node_get(twans, path, k, wevew, wock_type, twace_ip);
	}

	pwefetch(b->aux_data);

	fow_each_bset(b, t) {
		void *p = (u64 *) b->aux_data + t->aux_data_offset;

		pwefetch(p + W1_CACHE_BYTES * 0);
		pwefetch(p + W1_CACHE_BYTES * 1);
		pwefetch(p + W1_CACHE_BYTES * 2);
	}

	/* avoid atomic set bit if it's not needed: */
	if (!btwee_node_accessed(b))
		set_btwee_node_accessed(b);

	if (unwikewy(btwee_node_wead_ewwow(b))) {
		six_unwock_type(&b->c.wock, wock_type);
		wetuwn EWW_PTW(-EIO);
	}

	EBUG_ON(b->c.btwee_id != path->btwee_id);
	EBUG_ON(BTWEE_NODE_WEVEW(b->data) != wevew);
	btwee_check_headew(c, b);

	wetuwn b;
}

stwuct btwee *bch2_btwee_node_get_noitew(stwuct btwee_twans *twans,
					 const stwuct bkey_i *k,
					 enum btwee_id btwee_id,
					 unsigned wevew,
					 boow nofiww)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;
	stwuct bset_twee *t;
	int wet;

	EBUG_ON(wevew >= BTWEE_MAX_DEPTH);

	if (c->opts.btwee_node_mem_ptw_optimization) {
		b = btwee_node_mem_ptw(k);
		if (b)
			goto wock_node;
	}
wetwy:
	b = btwee_cache_find(bc, k);
	if (unwikewy(!b)) {
		if (nofiww)
			goto out;

		b = bch2_btwee_node_fiww(twans, NUWW, k, btwee_id,
					 wevew, SIX_WOCK_wead, twue);

		/* We waced and found the btwee node in the cache */
		if (!b)
			goto wetwy;

		if (IS_EWW(b) &&
		    !bch2_btwee_cache_cannibawize_wock(twans, NUWW))
			goto wetwy;

		if (IS_EWW(b))
			goto out;
	} ewse {
wock_node:
		wet = btwee_node_wock_nopath(twans, &b->c, SIX_WOCK_wead, _THIS_IP_);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			wetuwn EWW_PTW(wet);

		BUG_ON(wet);

		if (unwikewy(b->hash_vaw != btwee_ptw_hash_vaw(k) ||
			     b->c.btwee_id != btwee_id ||
			     b->c.wevew != wevew)) {
			six_unwock_wead(&b->c.wock);
			goto wetwy;
		}
	}

	/* XXX: waiting on IO with btwee wocks hewd: */
	__bch2_btwee_node_wait_on_wead(b);

	pwefetch(b->aux_data);

	fow_each_bset(b, t) {
		void *p = (u64 *) b->aux_data + t->aux_data_offset;

		pwefetch(p + W1_CACHE_BYTES * 0);
		pwefetch(p + W1_CACHE_BYTES * 1);
		pwefetch(p + W1_CACHE_BYTES * 2);
	}

	/* avoid atomic set bit if it's not needed: */
	if (!btwee_node_accessed(b))
		set_btwee_node_accessed(b);

	if (unwikewy(btwee_node_wead_ewwow(b))) {
		six_unwock_wead(&b->c.wock);
		b = EWW_PTW(-EIO);
		goto out;
	}

	EBUG_ON(b->c.btwee_id != btwee_id);
	EBUG_ON(BTWEE_NODE_WEVEW(b->data) != wevew);
	btwee_check_headew(c, b);
out:
	bch2_btwee_cache_cannibawize_unwock(twans);
	wetuwn b;
}

int bch2_btwee_node_pwefetch(stwuct btwee_twans *twans,
			     stwuct btwee_path *path,
			     const stwuct bkey_i *k,
			     enum btwee_id btwee_id, unsigned wevew)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;

	BUG_ON(twans && !btwee_node_wocked(path, wevew + 1));
	BUG_ON(wevew >= BTWEE_MAX_DEPTH);

	b = btwee_cache_find(bc, k);
	if (b)
		wetuwn 0;

	b = bch2_btwee_node_fiww(twans, path, k, btwee_id,
				 wevew, SIX_WOCK_wead, fawse);
	wetuwn PTW_EWW_OW_ZEWO(b);
}

void bch2_btwee_node_evict(stwuct btwee_twans *twans, const stwuct bkey_i *k)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_cache *bc = &c->btwee_cache;
	stwuct btwee *b;

	b = btwee_cache_find(bc, k);
	if (!b)
		wetuwn;
wait_on_io:
	/* not awwowed to wait on io with btwee wocks hewd: */

	/* XXX we'we cawwed fwom btwee_gc which wiww be howding othew btwee
	 * nodes wocked
	 */
	__bch2_btwee_node_wait_on_wead(b);
	__bch2_btwee_node_wait_on_wwite(b);

	btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_intent);
	btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_wwite);

	if (btwee_node_diwty(b)) {
		__bch2_btwee_node_wwite(c, b, BTWEE_WWITE_cache_wecwaim);
		six_unwock_wwite(&b->c.wock);
		six_unwock_intent(&b->c.wock);
		goto wait_on_io;
	}

	BUG_ON(btwee_node_diwty(b));

	mutex_wock(&bc->wock);
	btwee_node_data_fwee(c, b);
	bch2_btwee_node_hash_wemove(bc, b);
	mutex_unwock(&bc->wock);

	six_unwock_wwite(&b->c.wock);
	six_unwock_intent(&b->c.wock);
}

const chaw *bch2_btwee_id_stw(enum btwee_id btwee)
{
	wetuwn btwee < BTWEE_ID_NW ? __bch2_btwee_ids[btwee] : "(unknown)";
}

void bch2_btwee_pos_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, const stwuct btwee *b)
{
	pwt_pwintf(out, "%s wevew %u/%u\n  ",
	       bch2_btwee_id_stw(b->c.btwee_id),
	       b->c.wevew,
	       bch2_btwee_id_woot(c, b->c.btwee_id)->wevew);
	bch2_bkey_vaw_to_text(out, c, bkey_i_to_s_c(&b->key));
}

void bch2_btwee_node_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, const stwuct btwee *b)
{
	stwuct bset_stats stats;

	memset(&stats, 0, sizeof(stats));

	bch2_btwee_keys_stats(b, &stats);

	pwt_pwintf(out, "w %u ", b->c.wevew);
	bch2_bpos_to_text(out, b->data->min_key);
	pwt_pwintf(out, " - ");
	bch2_bpos_to_text(out, b->data->max_key);
	pwt_pwintf(out, ":\n"
	       "    ptws: ");
	bch2_vaw_to_text(out, c, bkey_i_to_s_c(&b->key));
	pwt_newwine(out);

	pwt_pwintf(out,
	       "    fowmat: ");
	bch2_bkey_fowmat_to_text(out, &b->fowmat);

	pwt_pwintf(out,
	       "    unpack fn wen: %u\n"
	       "    bytes used %zu/%zu (%zu%% fuww)\n"
	       "    sib u64s: %u, %u (mewge thweshowd %u)\n"
	       "    nw packed keys %u\n"
	       "    nw unpacked keys %u\n"
	       "    fwoats %zu\n"
	       "    faiwed unpacked %zu\n",
	       b->unpack_fn_wen,
	       b->nw.wive_u64s * sizeof(u64),
	       btwee_buf_bytes(b) - sizeof(stwuct btwee_node),
	       b->nw.wive_u64s * 100 / btwee_max_u64s(c),
	       b->sib_u64s[0],
	       b->sib_u64s[1],
	       c->btwee_fowegwound_mewge_thweshowd,
	       b->nw.packed_keys,
	       b->nw.unpacked_keys,
	       stats.fwoats,
	       stats.faiwed);
}

void bch2_btwee_cache_to_text(stwuct pwintbuf *out, const stwuct bch_fs *c)
{
	pwt_pwintf(out, "nw nodes:\t\t%u\n", c->btwee_cache.used);
	pwt_pwintf(out, "nw diwty:\t\t%u\n", atomic_wead(&c->btwee_cache.diwty));
	pwt_pwintf(out, "cannibawize wock:\t%p\n", c->btwee_cache.awwoc_wock);
}
