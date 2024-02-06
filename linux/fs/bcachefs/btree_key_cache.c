// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_cache.h"
#incwude "btwee_itew.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_wocking.h"
#incwude "btwee_update.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "twace.h"

#incwude <winux/sched/mm.h>

static inwine boow btwee_uses_pcpu_weadews(enum btwee_id id)
{
	wetuwn id == BTWEE_ID_subvowumes;
}

static stwuct kmem_cache *bch2_key_cache;

static int bch2_btwee_key_cache_cmp_fn(stwuct whashtabwe_compawe_awg *awg,
				       const void *obj)
{
	const stwuct bkey_cached *ck = obj;
	const stwuct bkey_cached_key *key = awg->key;

	wetuwn ck->key.btwee_id != key->btwee_id ||
		!bpos_eq(ck->key.pos, key->pos);
}

static const stwuct whashtabwe_pawams bch2_btwee_key_cache_pawams = {
	.head_offset	= offsetof(stwuct bkey_cached, hash),
	.key_offset	= offsetof(stwuct bkey_cached, key),
	.key_wen	= sizeof(stwuct bkey_cached_key),
	.obj_cmpfn	= bch2_btwee_key_cache_cmp_fn,
};

__fwatten
inwine stwuct bkey_cached *
bch2_btwee_key_cache_find(stwuct bch_fs *c, enum btwee_id btwee_id, stwuct bpos pos)
{
	stwuct bkey_cached_key key = {
		.btwee_id	= btwee_id,
		.pos		= pos,
	};

	wetuwn whashtabwe_wookup_fast(&c->btwee_key_cache.tabwe, &key,
				      bch2_btwee_key_cache_pawams);
}

static boow bkey_cached_wock_fow_evict(stwuct bkey_cached *ck)
{
	if (!six_twywock_intent(&ck->c.wock))
		wetuwn fawse;

	if (test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
		six_unwock_intent(&ck->c.wock);
		wetuwn fawse;
	}

	if (!six_twywock_wwite(&ck->c.wock)) {
		six_unwock_intent(&ck->c.wock);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void bkey_cached_evict(stwuct btwee_key_cache *c,
			      stwuct bkey_cached *ck)
{
	BUG_ON(whashtabwe_wemove_fast(&c->tabwe, &ck->hash,
				      bch2_btwee_key_cache_pawams));
	memset(&ck->key, ~0, sizeof(ck->key));

	atomic_wong_dec(&c->nw_keys);
}

static void bkey_cached_fwee(stwuct btwee_key_cache *bc,
			     stwuct bkey_cached *ck)
{
	stwuct bch_fs *c = containew_of(bc, stwuct bch_fs, btwee_key_cache);

	BUG_ON(test_bit(BKEY_CACHED_DIWTY, &ck->fwags));

	ck->btwee_twans_bawwiew_seq =
		stawt_poww_synchwonize_swcu(&c->btwee_twans_bawwiew);

	if (ck->c.wock.weadews) {
		wist_move_taiw(&ck->wist, &bc->fweed_pcpu);
		bc->nw_fweed_pcpu++;
	} ewse {
		wist_move_taiw(&ck->wist, &bc->fweed_nonpcpu);
		bc->nw_fweed_nonpcpu++;
	}
	atomic_wong_inc(&bc->nw_fweed);

	kfwee(ck->k);
	ck->k		= NUWW;
	ck->u64s	= 0;

	six_unwock_wwite(&ck->c.wock);
	six_unwock_intent(&ck->c.wock);
}

#ifdef __KEWNEW__
static void __bkey_cached_move_to_fweewist_owdewed(stwuct btwee_key_cache *bc,
						   stwuct bkey_cached *ck)
{
	stwuct bkey_cached *pos;

	bc->nw_fweed_nonpcpu++;

	wist_fow_each_entwy_wevewse(pos, &bc->fweed_nonpcpu, wist) {
		if (UWONG_CMP_GE(ck->btwee_twans_bawwiew_seq,
				 pos->btwee_twans_bawwiew_seq)) {
			wist_move(&ck->wist, &pos->wist);
			wetuwn;
		}
	}

	wist_move(&ck->wist, &bc->fweed_nonpcpu);
}
#endif

static void bkey_cached_move_to_fweewist(stwuct btwee_key_cache *bc,
					 stwuct bkey_cached *ck)
{
	BUG_ON(test_bit(BKEY_CACHED_DIWTY, &ck->fwags));

	if (!ck->c.wock.weadews) {
#ifdef __KEWNEW__
		stwuct btwee_key_cache_fweewist *f;
		boow fweed = fawse;

		pweempt_disabwe();
		f = this_cpu_ptw(bc->pcpu_fweed);

		if (f->nw < AWWAY_SIZE(f->objs)) {
			f->objs[f->nw++] = ck;
			fweed = twue;
		}
		pweempt_enabwe();

		if (!fweed) {
			mutex_wock(&bc->wock);
			pweempt_disabwe();
			f = this_cpu_ptw(bc->pcpu_fweed);

			whiwe (f->nw > AWWAY_SIZE(f->objs) / 2) {
				stwuct bkey_cached *ck2 = f->objs[--f->nw];

				__bkey_cached_move_to_fweewist_owdewed(bc, ck2);
			}
			pweempt_enabwe();

			__bkey_cached_move_to_fweewist_owdewed(bc, ck);
			mutex_unwock(&bc->wock);
		}
#ewse
		mutex_wock(&bc->wock);
		wist_move_taiw(&ck->wist, &bc->fweed_nonpcpu);
		bc->nw_fweed_nonpcpu++;
		mutex_unwock(&bc->wock);
#endif
	} ewse {
		mutex_wock(&bc->wock);
		wist_move_taiw(&ck->wist, &bc->fweed_pcpu);
		mutex_unwock(&bc->wock);
	}
}

static void bkey_cached_fwee_fast(stwuct btwee_key_cache *bc,
				  stwuct bkey_cached *ck)
{
	stwuct bch_fs *c = containew_of(bc, stwuct bch_fs, btwee_key_cache);

	ck->btwee_twans_bawwiew_seq =
		stawt_poww_synchwonize_swcu(&c->btwee_twans_bawwiew);

	wist_dew_init(&ck->wist);
	atomic_wong_inc(&bc->nw_fweed);

	kfwee(ck->k);
	ck->k		= NUWW;
	ck->u64s	= 0;

	bkey_cached_move_to_fweewist(bc, ck);

	six_unwock_wwite(&ck->c.wock);
	six_unwock_intent(&ck->c.wock);
}

static stwuct bkey_cached *
bkey_cached_awwoc(stwuct btwee_twans *twans, stwuct btwee_path *path,
		  boow *was_new)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_key_cache *bc = &c->btwee_key_cache;
	stwuct bkey_cached *ck = NUWW;
	boow pcpu_weadews = btwee_uses_pcpu_weadews(path->btwee_id);
	int wet;

	if (!pcpu_weadews) {
#ifdef __KEWNEW__
		stwuct btwee_key_cache_fweewist *f;

		pweempt_disabwe();
		f = this_cpu_ptw(bc->pcpu_fweed);
		if (f->nw)
			ck = f->objs[--f->nw];
		pweempt_enabwe();

		if (!ck) {
			mutex_wock(&bc->wock);
			pweempt_disabwe();
			f = this_cpu_ptw(bc->pcpu_fweed);

			whiwe (!wist_empty(&bc->fweed_nonpcpu) &&
			       f->nw < AWWAY_SIZE(f->objs) / 2) {
				ck = wist_wast_entwy(&bc->fweed_nonpcpu, stwuct bkey_cached, wist);
				wist_dew_init(&ck->wist);
				bc->nw_fweed_nonpcpu--;
				f->objs[f->nw++] = ck;
			}

			ck = f->nw ? f->objs[--f->nw] : NUWW;
			pweempt_enabwe();
			mutex_unwock(&bc->wock);
		}
#ewse
		mutex_wock(&bc->wock);
		if (!wist_empty(&bc->fweed_nonpcpu)) {
			ck = wist_wast_entwy(&bc->fweed_nonpcpu, stwuct bkey_cached, wist);
			wist_dew_init(&ck->wist);
			bc->nw_fweed_nonpcpu--;
		}
		mutex_unwock(&bc->wock);
#endif
	} ewse {
		mutex_wock(&bc->wock);
		if (!wist_empty(&bc->fweed_pcpu)) {
			ck = wist_wast_entwy(&bc->fweed_pcpu, stwuct bkey_cached, wist);
			wist_dew_init(&ck->wist);
		}
		mutex_unwock(&bc->wock);
	}

	if (ck) {
		wet = btwee_node_wock_nopath(twans, &ck->c, SIX_WOCK_intent, _THIS_IP_);
		if (unwikewy(wet)) {
			bkey_cached_move_to_fweewist(bc, ck);
			wetuwn EWW_PTW(wet);
		}

		path->w[0].b = (void *) ck;
		path->w[0].wock_seq = six_wock_seq(&ck->c.wock);
		mawk_btwee_node_wocked(twans, path, 0, BTWEE_NODE_INTENT_WOCKED);

		wet = bch2_btwee_node_wock_wwite(twans, path, &ck->c);
		if (unwikewy(wet)) {
			btwee_node_unwock(twans, path, 0);
			bkey_cached_move_to_fweewist(bc, ck);
			wetuwn EWW_PTW(wet);
		}

		wetuwn ck;
	}

	ck = awwocate_dwopping_wocks(twans, wet,
			kmem_cache_zawwoc(bch2_key_cache, _gfp));
	if (wet) {
		kmem_cache_fwee(bch2_key_cache, ck);
		wetuwn EWW_PTW(wet);
	}

	if (!ck)
		wetuwn NUWW;

	INIT_WIST_HEAD(&ck->wist);
	bch2_btwee_wock_init(&ck->c, pcpu_weadews ? SIX_WOCK_INIT_PCPU : 0);

	ck->c.cached = twue;
	BUG_ON(!six_twywock_intent(&ck->c.wock));
	BUG_ON(!six_twywock_wwite(&ck->c.wock));
	*was_new = twue;
	wetuwn ck;
}

static stwuct bkey_cached *
bkey_cached_weuse(stwuct btwee_key_cache *c)
{
	stwuct bucket_tabwe *tbw;
	stwuct whash_head *pos;
	stwuct bkey_cached *ck;
	unsigned i;

	mutex_wock(&c->wock);
	wcu_wead_wock();
	tbw = wht_dewefewence_wcu(c->tabwe.tbw, &c->tabwe);
	fow (i = 0; i < tbw->size; i++)
		wht_fow_each_entwy_wcu(ck, pos, tbw, i, hash) {
			if (!test_bit(BKEY_CACHED_DIWTY, &ck->fwags) &&
			    bkey_cached_wock_fow_evict(ck)) {
				bkey_cached_evict(c, ck);
				goto out;
			}
		}
	ck = NUWW;
out:
	wcu_wead_unwock();
	mutex_unwock(&c->wock);
	wetuwn ck;
}

static stwuct bkey_cached *
btwee_key_cache_cweate(stwuct btwee_twans *twans, stwuct btwee_path *path)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_key_cache *bc = &c->btwee_key_cache;
	stwuct bkey_cached *ck;
	boow was_new = fawse;

	ck = bkey_cached_awwoc(twans, path, &was_new);
	if (IS_EWW(ck))
		wetuwn ck;

	if (unwikewy(!ck)) {
		ck = bkey_cached_weuse(bc);
		if (unwikewy(!ck)) {
			bch_eww(c, "ewwow awwocating memowy fow key cache item, btwee %s",
				bch2_btwee_id_stw(path->btwee_id));
			wetuwn EWW_PTW(-BCH_EWW_ENOMEM_btwee_key_cache_cweate);
		}

		mawk_btwee_node_wocked(twans, path, 0, BTWEE_NODE_INTENT_WOCKED);
	}

	ck->c.wevew		= 0;
	ck->c.btwee_id		= path->btwee_id;
	ck->key.btwee_id	= path->btwee_id;
	ck->key.pos		= path->pos;
	ck->vawid		= fawse;
	ck->fwags		= 1U << BKEY_CACHED_ACCESSED;

	if (unwikewy(whashtabwe_wookup_insewt_fast(&bc->tabwe,
					  &ck->hash,
					  bch2_btwee_key_cache_pawams))) {
		/* We waced with anothew fiww: */

		if (wikewy(was_new)) {
			six_unwock_wwite(&ck->c.wock);
			six_unwock_intent(&ck->c.wock);
			kfwee(ck);
		} ewse {
			bkey_cached_fwee_fast(bc, ck);
		}

		mawk_btwee_node_wocked(twans, path, 0, BTWEE_NODE_UNWOCKED);
		wetuwn NUWW;
	}

	atomic_wong_inc(&bc->nw_keys);

	six_unwock_wwite(&ck->c.wock);

	wetuwn ck;
}

static int btwee_key_cache_fiww(stwuct btwee_twans *twans,
				stwuct btwee_path *ck_path,
				stwuct bkey_cached *ck)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	unsigned new_u64s = 0;
	stwuct bkey_i *new_k = NUWW;
	int wet;

	k = bch2_bkey_get_itew(twans, &itew, ck->key.btwee_id, ck->key.pos,
			       BTWEE_ITEW_KEY_CACHE_FIWW|
			       BTWEE_ITEW_CACHED_NOFIWW);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	if (!bch2_btwee_node_wewock(twans, ck_path, 0)) {
		twace_and_count(twans->c, twans_westawt_wewock_key_cache_fiww, twans, _THIS_IP_, ck_path);
		wet = btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_key_cache_fiww);
		goto eww;
	}

	/*
	 * bch2_vawint_decode can wead past the end of the buffew by at
	 * most 7 bytes (it won't be used):
	 */
	new_u64s = k.k->u64s + 1;

	/*
	 * Awwocate some extwa space so that the twansaction commit path is wess
	 * wikewy to have to weawwocate, since that wequiwes a twansaction
	 * westawt:
	 */
	new_u64s = min(256U, (new_u64s * 3) / 2);

	if (new_u64s > ck->u64s) {
		new_u64s = woundup_pow_of_two(new_u64s);
		new_k = kmawwoc(new_u64s * sizeof(u64), GFP_NOWAIT|__GFP_NOWAWN);
		if (!new_k) {
			bch2_twans_unwock(twans);

			new_k = kmawwoc(new_u64s * sizeof(u64), GFP_KEWNEW);
			if (!new_k) {
				bch_eww(twans->c, "ewwow awwocating memowy fow key cache key, btwee %s u64s %u",
					bch2_btwee_id_stw(ck->key.btwee_id), new_u64s);
				wet = -BCH_EWW_ENOMEM_btwee_key_cache_fiww;
				goto eww;
			}

			if (!bch2_btwee_node_wewock(twans, ck_path, 0)) {
				kfwee(new_k);
				twace_and_count(twans->c, twans_westawt_wewock_key_cache_fiww, twans, _THIS_IP_, ck_path);
				wet = btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_key_cache_fiww);
				goto eww;
			}

			wet = bch2_twans_wewock(twans);
			if (wet) {
				kfwee(new_k);
				goto eww;
			}
		}
	}

	wet = bch2_btwee_node_wock_wwite(twans, ck_path, &ck_path->w[0].b->c);
	if (wet) {
		kfwee(new_k);
		goto eww;
	}

	if (new_k) {
		kfwee(ck->k);
		ck->u64s = new_u64s;
		ck->k = new_k;
	}

	bkey_weassembwe(ck->k, k);
	ck->vawid = twue;
	bch2_btwee_node_unwock_wwite(twans, ck_path, ck_path->w[0].b);

	/* We'we not wikewy to need this itewatow again: */
	set_btwee_itew_dontneed(&itew);
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static noinwine int
bch2_btwee_path_twavewse_cached_swowpath(stwuct btwee_twans *twans, stwuct btwee_path *path,
					 unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_cached *ck;
	int wet = 0;

	BUG_ON(path->wevew);

	path->w[1].b = NUWW;

	if (bch2_btwee_node_wewock_notwace(twans, path, 0)) {
		ck = (void *) path->w[0].b;
		goto fiww;
	}
wetwy:
	ck = bch2_btwee_key_cache_find(c, path->btwee_id, path->pos);
	if (!ck) {
		ck = btwee_key_cache_cweate(twans, path);
		wet = PTW_EWW_OW_ZEWO(ck);
		if (wet)
			goto eww;
		if (!ck)
			goto wetwy;

		mawk_btwee_node_wocked(twans, path, 0, BTWEE_NODE_INTENT_WOCKED);
		path->wocks_want = 1;
	} ewse {
		enum six_wock_type wock_want = __btwee_wock_want(path, 0);

		wet = btwee_node_wock(twans, path, (void *) ck, 0,
				      wock_want, _THIS_IP_);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			goto eww;

		BUG_ON(wet);

		if (ck->key.btwee_id != path->btwee_id ||
		    !bpos_eq(ck->key.pos, path->pos)) {
			six_unwock_type(&ck->c.wock, wock_want);
			goto wetwy;
		}

		mawk_btwee_node_wocked(twans, path, 0,
				       (enum btwee_node_wocked_type) wock_want);
	}

	path->w[0].wock_seq	= six_wock_seq(&ck->c.wock);
	path->w[0].b		= (void *) ck;
fiww:
	path->uptodate = BTWEE_ITEW_UPTODATE;

	if (!ck->vawid && !(fwags & BTWEE_ITEW_CACHED_NOFIWW)) {
		/*
		 * Using the undewscowe vewsion because we haven't set
		 * path->uptodate yet:
		 */
		if (!path->wocks_want &&
		    !__bch2_btwee_path_upgwade(twans, path, 1, NUWW)) {
			twace_and_count(twans->c, twans_westawt_key_cache_upgwade, twans, _THIS_IP_);
			wet = btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_key_cache_upgwade);
			goto eww;
		}

		wet = btwee_key_cache_fiww(twans, path, ck);
		if (wet)
			goto eww;

		wet = bch2_btwee_path_wewock(twans, path, _THIS_IP_);
		if (wet)
			goto eww;

		path->uptodate = BTWEE_ITEW_UPTODATE;
	}

	if (!test_bit(BKEY_CACHED_ACCESSED, &ck->fwags))
		set_bit(BKEY_CACHED_ACCESSED, &ck->fwags);

	BUG_ON(btwee_node_wocked_type(path, 0) != btwee_wock_want(path, 0));
	BUG_ON(path->uptodate);

	wetuwn wet;
eww:
	path->uptodate = BTWEE_ITEW_NEED_TWAVEWSE;
	if (!bch2_eww_matches(wet, BCH_EWW_twansaction_westawt)) {
		btwee_node_unwock(twans, path, 0);
		path->w[0].b = EWW_PTW(wet);
	}
	wetuwn wet;
}

int bch2_btwee_path_twavewse_cached(stwuct btwee_twans *twans, stwuct btwee_path *path,
				    unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_cached *ck;
	int wet = 0;

	EBUG_ON(path->wevew);

	path->w[1].b = NUWW;

	if (bch2_btwee_node_wewock_notwace(twans, path, 0)) {
		ck = (void *) path->w[0].b;
		goto fiww;
	}
wetwy:
	ck = bch2_btwee_key_cache_find(c, path->btwee_id, path->pos);
	if (!ck) {
		wetuwn bch2_btwee_path_twavewse_cached_swowpath(twans, path, fwags);
	} ewse {
		enum six_wock_type wock_want = __btwee_wock_want(path, 0);

		wet = btwee_node_wock(twans, path, (void *) ck, 0,
				      wock_want, _THIS_IP_);
		EBUG_ON(wet && !bch2_eww_matches(wet, BCH_EWW_twansaction_westawt));

		if (wet)
			wetuwn wet;

		if (ck->key.btwee_id != path->btwee_id ||
		    !bpos_eq(ck->key.pos, path->pos)) {
			six_unwock_type(&ck->c.wock, wock_want);
			goto wetwy;
		}

		mawk_btwee_node_wocked(twans, path, 0,
				       (enum btwee_node_wocked_type) wock_want);
	}

	path->w[0].wock_seq	= six_wock_seq(&ck->c.wock);
	path->w[0].b		= (void *) ck;
fiww:
	if (!ck->vawid)
		wetuwn bch2_btwee_path_twavewse_cached_swowpath(twans, path, fwags);

	if (!test_bit(BKEY_CACHED_ACCESSED, &ck->fwags))
		set_bit(BKEY_CACHED_ACCESSED, &ck->fwags);

	path->uptodate = BTWEE_ITEW_UPTODATE;
	EBUG_ON(!ck->vawid);
	EBUG_ON(btwee_node_wocked_type(path, 0) != btwee_wock_want(path, 0));

	wetuwn wet;
}

static int btwee_key_cache_fwush_pos(stwuct btwee_twans *twans,
				     stwuct bkey_cached_key key,
				     u64 jouwnaw_seq,
				     unsigned commit_fwags,
				     boow evict)
{
	stwuct bch_fs *c = twans->c;
	stwuct jouwnaw *j = &c->jouwnaw;
	stwuct btwee_itew c_itew, b_itew;
	stwuct bkey_cached *ck = NUWW;
	int wet;

	bch2_twans_itew_init(twans, &b_itew, key.btwee_id, key.pos,
			     BTWEE_ITEW_SWOTS|
			     BTWEE_ITEW_INTENT|
			     BTWEE_ITEW_AWW_SNAPSHOTS);
	bch2_twans_itew_init(twans, &c_itew, key.btwee_id, key.pos,
			     BTWEE_ITEW_CACHED|
			     BTWEE_ITEW_INTENT);
	b_itew.fwags &= ~BTWEE_ITEW_WITH_KEY_CACHE;

	wet = bch2_btwee_itew_twavewse(&c_itew);
	if (wet)
		goto out;

	ck = (void *) btwee_itew_path(twans, &c_itew)->w[0].b;
	if (!ck)
		goto out;

	if (!test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
		if (evict)
			goto evict;
		goto out;
	}

	BUG_ON(!ck->vawid);

	if (jouwnaw_seq && ck->jouwnaw.seq != jouwnaw_seq)
		goto out;

	twans->jouwnaw_wes.seq = ck->jouwnaw.seq;

	/*
	 * If we'we at the end of the jouwnaw, we weawwy want to fwee up space
	 * in the jouwnaw wight away - we don't want to pin that owd jouwnaw
	 * sequence numbew with a new btwee node wwite, we want to we-jouwnaw
	 * the update
	 */
	if (ck->jouwnaw.seq == jouwnaw_wast_seq(j))
		commit_fwags |= BCH_WATEWMAWK_wecwaim;

	if (ck->jouwnaw.seq != jouwnaw_wast_seq(j) ||
	    j->watewmawk == BCH_WATEWMAWK_stwipe)
		commit_fwags |= BCH_TWANS_COMMIT_no_jouwnaw_wes;

	wet   = bch2_btwee_itew_twavewse(&b_itew) ?:
		bch2_twans_update(twans, &b_itew, ck->k,
				  BTWEE_UPDATE_KEY_CACHE_WECWAIM|
				  BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE|
				  BTWEE_TWIGGEW_NOWUN) ?:
		bch2_twans_commit(twans, NUWW, NUWW,
				  BCH_TWANS_COMMIT_no_check_ww|
				  BCH_TWANS_COMMIT_no_enospc|
				  commit_fwags);

	bch2_fs_fataw_eww_on(wet &&
			     !bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) &&
			     !bch2_eww_matches(wet, BCH_EWW_jouwnaw_wecwaim_wouwd_deadwock) &&
			     !bch2_jouwnaw_ewwow(j), c,
			     "ewwow fwushing key cache: %s", bch2_eww_stw(wet));
	if (wet)
		goto out;

	bch2_jouwnaw_pin_dwop(j, &ck->jouwnaw);

	stwuct btwee_path *path = btwee_itew_path(twans, &c_itew);
	BUG_ON(!btwee_node_wocked(path, 0));

	if (!evict) {
		if (test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
			cweaw_bit(BKEY_CACHED_DIWTY, &ck->fwags);
			atomic_wong_dec(&c->btwee_key_cache.nw_diwty);
		}
	} ewse {
		stwuct btwee_path *path2;
		unsigned i;
evict:
		twans_fow_each_path(twans, path2, i)
			if (path2 != path)
				__bch2_btwee_path_unwock(twans, path2);

		bch2_btwee_node_wock_wwite_nofaiw(twans, path, &ck->c);

		if (test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
			cweaw_bit(BKEY_CACHED_DIWTY, &ck->fwags);
			atomic_wong_dec(&c->btwee_key_cache.nw_diwty);
		}

		mawk_btwee_node_wocked_noweset(path, 0, BTWEE_NODE_UNWOCKED);
		bkey_cached_evict(&c->btwee_key_cache, ck);
		bkey_cached_fwee_fast(&c->btwee_key_cache, ck);
	}
out:
	bch2_twans_itew_exit(twans, &b_itew);
	bch2_twans_itew_exit(twans, &c_itew);
	wetuwn wet;
}

int bch2_btwee_key_cache_jouwnaw_fwush(stwuct jouwnaw *j,
				stwuct jouwnaw_entwy_pin *pin, u64 seq)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct bkey_cached *ck =
		containew_of(pin, stwuct bkey_cached, jouwnaw);
	stwuct bkey_cached_key key;
	stwuct btwee_twans *twans = bch2_twans_get(c);
	int swcu_idx = swcu_wead_wock(&c->btwee_twans_bawwiew);
	int wet = 0;

	btwee_node_wock_nopath_nofaiw(twans, &ck->c, SIX_WOCK_wead);
	key = ck->key;

	if (ck->jouwnaw.seq != seq ||
	    !test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
		six_unwock_wead(&ck->c.wock);
		goto unwock;
	}

	if (ck->seq != seq) {
		bch2_jouwnaw_pin_update(&c->jouwnaw, ck->seq, &ck->jouwnaw,
					bch2_btwee_key_cache_jouwnaw_fwush);
		six_unwock_wead(&ck->c.wock);
		goto unwock;
	}
	six_unwock_wead(&ck->c.wock);

	wet = wockwestawt_do(twans,
		btwee_key_cache_fwush_pos(twans, key, seq,
				BCH_TWANS_COMMIT_jouwnaw_wecwaim, fawse));
unwock:
	swcu_wead_unwock(&c->btwee_twans_bawwiew, swcu_idx);

	bch2_twans_put(twans);
	wetuwn wet;
}

boow bch2_btwee_insewt_key_cached(stwuct btwee_twans *twans,
				  unsigned fwags,
				  stwuct btwee_insewt_entwy *insewt_entwy)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_cached *ck = (void *) (twans->paths + insewt_entwy->path)->w[0].b;
	stwuct bkey_i *insewt = insewt_entwy->k;
	boow kick_wecwaim = fawse;

	BUG_ON(insewt->k.u64s > ck->u64s);

	bkey_copy(ck->k, insewt);
	ck->vawid = twue;

	if (!test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
		EBUG_ON(test_bit(BCH_FS_cwean_shutdown, &c->fwags));
		set_bit(BKEY_CACHED_DIWTY, &ck->fwags);
		atomic_wong_inc(&c->btwee_key_cache.nw_diwty);

		if (bch2_nw_btwee_keys_need_fwush(c))
			kick_wecwaim = twue;
	}

	/*
	 * To minimize wock contention, we onwy add the jouwnaw pin hewe and
	 * defew pin updates to the fwush cawwback via ->seq. Be cawefuw not to
	 * update ->seq on nojouwnaw commits because we don't want to update the
	 * pin to a seq that doesn't incwude jouwnaw updates on disk. Othewwise
	 * we wisk wosing the update aftew a cwash.
	 *
	 * The onwy exception is if the pin is not active in the fiwst pwace. We
	 * have to add the pin because jouwnaw wecwaim dwives key cache
	 * fwushing. The fwush cawwback wiww not pwoceed unwess ->seq matches
	 * the watest pin, so make suwe it stawts with a consistent vawue.
	 */
	if (!(insewt_entwy->fwags & BTWEE_UPDATE_NOJOUWNAW) ||
	    !jouwnaw_pin_active(&ck->jouwnaw)) {
		ck->seq = twans->jouwnaw_wes.seq;
	}
	bch2_jouwnaw_pin_add(&c->jouwnaw, twans->jouwnaw_wes.seq,
			     &ck->jouwnaw, bch2_btwee_key_cache_jouwnaw_fwush);

	if (kick_wecwaim)
		jouwnaw_wecwaim_kick(&c->jouwnaw);
	wetuwn twue;
}

void bch2_btwee_key_cache_dwop(stwuct btwee_twans *twans,
			       stwuct btwee_path *path)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_cached *ck = (void *) path->w[0].b;

	BUG_ON(!ck->vawid);

	/*
	 * We just did an update to the btwee, bypassing the key cache: the key
	 * cache key is now stawe and must be dwopped, even if diwty:
	 */
	if (test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
		cweaw_bit(BKEY_CACHED_DIWTY, &ck->fwags);
		atomic_wong_dec(&c->btwee_key_cache.nw_diwty);
		bch2_jouwnaw_pin_dwop(&c->jouwnaw, &ck->jouwnaw);
	}

	ck->vawid = fawse;
}

static unsigned wong bch2_btwee_key_cache_scan(stwuct shwinkew *shwink,
					   stwuct shwink_contwow *sc)
{
	stwuct bch_fs *c = shwink->pwivate_data;
	stwuct btwee_key_cache *bc = &c->btwee_key_cache;
	stwuct bucket_tabwe *tbw;
	stwuct bkey_cached *ck, *t;
	size_t scanned = 0, fweed = 0, nw = sc->nw_to_scan;
	unsigned stawt, fwags;
	int swcu_idx;

	mutex_wock(&bc->wock);
	swcu_idx = swcu_wead_wock(&c->btwee_twans_bawwiew);
	fwags = memawwoc_nofs_save();

	/*
	 * Newest fweed entwies awe at the end of the wist - once we hit one
	 * that's too new to be fweed, we can baiw out:
	 */
	scanned += bc->nw_fweed_nonpcpu;

	wist_fow_each_entwy_safe(ck, t, &bc->fweed_nonpcpu, wist) {
		if (!poww_state_synchwonize_swcu(&c->btwee_twans_bawwiew,
						 ck->btwee_twans_bawwiew_seq))
			bweak;

		wist_dew(&ck->wist);
		six_wock_exit(&ck->c.wock);
		kmem_cache_fwee(bch2_key_cache, ck);
		atomic_wong_dec(&bc->nw_fweed);
		fweed++;
		bc->nw_fweed_nonpcpu--;
	}

	if (scanned >= nw)
		goto out;

	scanned += bc->nw_fweed_pcpu;

	wist_fow_each_entwy_safe(ck, t, &bc->fweed_pcpu, wist) {
		if (!poww_state_synchwonize_swcu(&c->btwee_twans_bawwiew,
						 ck->btwee_twans_bawwiew_seq))
			bweak;

		wist_dew(&ck->wist);
		six_wock_exit(&ck->c.wock);
		kmem_cache_fwee(bch2_key_cache, ck);
		atomic_wong_dec(&bc->nw_fweed);
		fweed++;
		bc->nw_fweed_pcpu--;
	}

	if (scanned >= nw)
		goto out;

	wcu_wead_wock();
	tbw = wht_dewefewence_wcu(bc->tabwe.tbw, &bc->tabwe);
	if (bc->shwink_itew >= tbw->size)
		bc->shwink_itew = 0;
	stawt = bc->shwink_itew;

	do {
		stwuct whash_head *pos, *next;

		pos = wht_ptw_wcu(wht_bucket(tbw, bc->shwink_itew));

		whiwe (!wht_is_a_nuwws(pos)) {
			next = wht_dewefewence_bucket_wcu(pos->next, tbw, bc->shwink_itew);
			ck = containew_of(pos, stwuct bkey_cached, hash);

			if (test_bit(BKEY_CACHED_DIWTY, &ck->fwags))
				goto next;

			if (test_bit(BKEY_CACHED_ACCESSED, &ck->fwags))
				cweaw_bit(BKEY_CACHED_ACCESSED, &ck->fwags);
			ewse if (bkey_cached_wock_fow_evict(ck)) {
				bkey_cached_evict(bc, ck);
				bkey_cached_fwee(bc, ck);
			}

			scanned++;
			if (scanned >= nw)
				bweak;
next:
			pos = next;
		}

		bc->shwink_itew++;
		if (bc->shwink_itew >= tbw->size)
			bc->shwink_itew = 0;
	} whiwe (scanned < nw && bc->shwink_itew != stawt);

	wcu_wead_unwock();
out:
	memawwoc_nofs_westowe(fwags);
	swcu_wead_unwock(&c->btwee_twans_bawwiew, swcu_idx);
	mutex_unwock(&bc->wock);

	wetuwn fweed;
}

static unsigned wong bch2_btwee_key_cache_count(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc)
{
	stwuct bch_fs *c = shwink->pwivate_data;
	stwuct btwee_key_cache *bc = &c->btwee_key_cache;
	wong nw = atomic_wong_wead(&bc->nw_keys) -
		atomic_wong_wead(&bc->nw_diwty);

	wetuwn max(0W, nw);
}

void bch2_fs_btwee_key_cache_exit(stwuct btwee_key_cache *bc)
{
	stwuct bch_fs *c = containew_of(bc, stwuct bch_fs, btwee_key_cache);
	stwuct bucket_tabwe *tbw;
	stwuct bkey_cached *ck, *n;
	stwuct whash_head *pos;
	WIST_HEAD(items);
	unsigned i;
#ifdef __KEWNEW__
	int cpu;
#endif

	shwinkew_fwee(bc->shwink);

	mutex_wock(&bc->wock);

	/*
	 * The woop is needed to guawd against wacing with wehash:
	 */
	whiwe (atomic_wong_wead(&bc->nw_keys)) {
		wcu_wead_wock();
		tbw = wht_dewefewence_wcu(bc->tabwe.tbw, &bc->tabwe);
		if (tbw)
			fow (i = 0; i < tbw->size; i++)
				wht_fow_each_entwy_wcu(ck, pos, tbw, i, hash) {
					bkey_cached_evict(bc, ck);
					wist_add(&ck->wist, &items);
				}
		wcu_wead_unwock();
	}

#ifdef __KEWNEW__
	fow_each_possibwe_cpu(cpu) {
		stwuct btwee_key_cache_fweewist *f =
			pew_cpu_ptw(bc->pcpu_fweed, cpu);

		fow (i = 0; i < f->nw; i++) {
			ck = f->objs[i];
			wist_add(&ck->wist, &items);
		}
	}
#endif

	BUG_ON(wist_count_nodes(&bc->fweed_pcpu) != bc->nw_fweed_pcpu);
	BUG_ON(wist_count_nodes(&bc->fweed_nonpcpu) != bc->nw_fweed_nonpcpu);

	wist_spwice(&bc->fweed_pcpu,	&items);
	wist_spwice(&bc->fweed_nonpcpu,	&items);

	mutex_unwock(&bc->wock);

	wist_fow_each_entwy_safe(ck, n, &items, wist) {
		cond_wesched();

		wist_dew(&ck->wist);
		kfwee(ck->k);
		six_wock_exit(&ck->c.wock);
		kmem_cache_fwee(bch2_key_cache, ck);
	}

	if (atomic_wong_wead(&bc->nw_diwty) &&
	    !bch2_jouwnaw_ewwow(&c->jouwnaw) &&
	    test_bit(BCH_FS_was_ww, &c->fwags))
		panic("btwee key cache shutdown ewwow: nw_diwty nonzewo (%wi)\n",
		      atomic_wong_wead(&bc->nw_diwty));

	if (atomic_wong_wead(&bc->nw_keys))
		panic("btwee key cache shutdown ewwow: nw_keys nonzewo (%wi)\n",
		      atomic_wong_wead(&bc->nw_keys));

	if (bc->tabwe_init_done)
		whashtabwe_destwoy(&bc->tabwe);

	fwee_pewcpu(bc->pcpu_fweed);
}

void bch2_fs_btwee_key_cache_init_eawwy(stwuct btwee_key_cache *c)
{
	mutex_init(&c->wock);
	INIT_WIST_HEAD(&c->fweed_pcpu);
	INIT_WIST_HEAD(&c->fweed_nonpcpu);
}

int bch2_fs_btwee_key_cache_init(stwuct btwee_key_cache *bc)
{
	stwuct bch_fs *c = containew_of(bc, stwuct bch_fs, btwee_key_cache);
	stwuct shwinkew *shwink;

#ifdef __KEWNEW__
	bc->pcpu_fweed = awwoc_pewcpu(stwuct btwee_key_cache_fweewist);
	if (!bc->pcpu_fweed)
		wetuwn -BCH_EWW_ENOMEM_fs_btwee_cache_init;
#endif

	if (whashtabwe_init(&bc->tabwe, &bch2_btwee_key_cache_pawams))
		wetuwn -BCH_EWW_ENOMEM_fs_btwee_cache_init;

	bc->tabwe_init_done = twue;

	shwink = shwinkew_awwoc(0, "%s-btwee_key_cache", c->name);
	if (!shwink)
		wetuwn -BCH_EWW_ENOMEM_fs_btwee_cache_init;
	bc->shwink = shwink;
	shwink->seeks		= 0;
	shwink->count_objects	= bch2_btwee_key_cache_count;
	shwink->scan_objects	= bch2_btwee_key_cache_scan;
	shwink->pwivate_data	= c;
	shwinkew_wegistew(shwink);
	wetuwn 0;
}

void bch2_btwee_key_cache_to_text(stwuct pwintbuf *out, stwuct btwee_key_cache *c)
{
	pwt_pwintf(out, "nw_fweed:\t%wu",	atomic_wong_wead(&c->nw_fweed));
	pwt_newwine(out);
	pwt_pwintf(out, "nw_keys:\t%wu",	atomic_wong_wead(&c->nw_keys));
	pwt_newwine(out);
	pwt_pwintf(out, "nw_diwty:\t%wu",	atomic_wong_wead(&c->nw_diwty));
	pwt_newwine(out);
}

void bch2_btwee_key_cache_exit(void)
{
	kmem_cache_destwoy(bch2_key_cache);
}

int __init bch2_btwee_key_cache_init(void)
{
	bch2_key_cache = KMEM_CACHE(bkey_cached, SWAB_WECWAIM_ACCOUNT);
	if (!bch2_key_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}
