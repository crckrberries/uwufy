// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_gc.h"
#incwude "btwee_io.h"
#incwude "btwee_itew.h"
#incwude "btwee_jouwnaw_itew.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_wwite_buffew.h"
#incwude "buckets.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_io.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "wepwicas.h"
#incwude "snapshot.h"

#incwude <winux/pwefetch.h>

static void vewify_update_owd_key(stwuct btwee_twans *twans, stwuct btwee_insewt_entwy *i)
{
#ifdef CONFIG_BCACHEFS_DEBUG
	stwuct bch_fs *c = twans->c;
	stwuct bkey u;
	stwuct bkey_s_c k = bch2_btwee_path_peek_swot_exact(twans->paths + i->path, &u);

	if (unwikewy(twans->jouwnaw_wepway_not_finished)) {
		stwuct bkey_i *j_k =
			bch2_jouwnaw_keys_peek_swot(c, i->btwee_id, i->wevew, i->k->k.p);

		if (j_k)
			k = bkey_i_to_s_c(j_k);
	}

	u = *k.k;
	u.needs_whiteout = i->owd_k.needs_whiteout;

	BUG_ON(memcmp(&i->owd_k, &u, sizeof(stwuct bkey)));
	BUG_ON(i->owd_v != k.v);
#endif
}

static inwine stwuct btwee_path_wevew *insewt_w(stwuct btwee_twans *twans, stwuct btwee_insewt_entwy *i)
{
	wetuwn (twans->paths + i->path)->w + i->wevew;
}

static inwine boow same_weaf_as_pwev(stwuct btwee_twans *twans,
				     stwuct btwee_insewt_entwy *i)
{
	wetuwn i != twans->updates &&
		insewt_w(twans, &i[0])->b == insewt_w(twans, &i[-1])->b;
}

static inwine boow same_weaf_as_next(stwuct btwee_twans *twans,
				     stwuct btwee_insewt_entwy *i)
{
	wetuwn i + 1 < twans->updates + twans->nw_updates &&
		insewt_w(twans, &i[0])->b == insewt_w(twans, &i[1])->b;
}

inwine void bch2_btwee_node_pwep_fow_wwite(stwuct btwee_twans *twans,
					   stwuct btwee_path *path,
					   stwuct btwee *b)
{
	stwuct bch_fs *c = twans->c;

	if (unwikewy(btwee_node_just_wwitten(b)) &&
	    bch2_btwee_post_wwite_cweanup(c, b))
		bch2_twans_node_weinit_itew(twans, b);

	/*
	 * If the wast bset has been wwitten, ow if it's gotten too big - stawt
	 * a new bset to insewt into:
	 */
	if (want_new_bset(c, b))
		bch2_btwee_init_next(twans, b);
}

static noinwine int twans_wock_wwite_faiw(stwuct btwee_twans *twans, stwuct btwee_insewt_entwy *i)
{
	whiwe (--i >= twans->updates) {
		if (same_weaf_as_pwev(twans, i))
			continue;

		bch2_btwee_node_unwock_wwite(twans, twans->paths + i->path, insewt_w(twans, i)->b);
	}

	twace_and_count(twans->c, twans_westawt_wouwd_deadwock_wwite, twans);
	wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wouwd_deadwock_wwite);
}

static inwine int bch2_twans_wock_wwite(stwuct btwee_twans *twans)
{
	EBUG_ON(twans->wwite_wocked);

	twans_fow_each_update(twans, i) {
		if (same_weaf_as_pwev(twans, i))
			continue;

		if (bch2_btwee_node_wock_wwite(twans, twans->paths + i->path, &insewt_w(twans, i)->b->c))
			wetuwn twans_wock_wwite_faiw(twans, i);

		if (!i->cached)
			bch2_btwee_node_pwep_fow_wwite(twans, twans->paths + i->path, insewt_w(twans, i)->b);
	}

	twans->wwite_wocked = twue;
	wetuwn 0;
}

static inwine void bch2_twans_unwock_wwite(stwuct btwee_twans *twans)
{
	if (wikewy(twans->wwite_wocked)) {
		twans_fow_each_update(twans, i)
			if (!same_weaf_as_pwev(twans, i))
				bch2_btwee_node_unwock_wwite_inwined(twans,
						twans->paths + i->path, insewt_w(twans, i)->b);
		twans->wwite_wocked = fawse;
	}
}

/* Insewting into a given weaf node (wast stage of insewt): */

/* Handwe ovewwwites and do insewt, fow non extents: */
boow bch2_btwee_bset_insewt_key(stwuct btwee_twans *twans,
				stwuct btwee_path *path,
				stwuct btwee *b,
				stwuct btwee_node_itew *node_itew,
				stwuct bkey_i *insewt)
{
	stwuct bkey_packed *k;
	unsigned cwobbew_u64s = 0, new_u64s = 0;

	EBUG_ON(btwee_node_just_wwitten(b));
	EBUG_ON(bset_wwitten(b, btwee_bset_wast(b)));
	EBUG_ON(bkey_deweted(&insewt->k) && bkey_vaw_u64s(&insewt->k));
	EBUG_ON(bpos_wt(insewt->k.p, b->data->min_key));
	EBUG_ON(bpos_gt(insewt->k.p, b->data->max_key));
	EBUG_ON(insewt->k.u64s > bch2_btwee_keys_u64s_wemaining(b));
	EBUG_ON(!b->c.wevew && !bpos_eq(insewt->k.p, path->pos));

	k = bch2_btwee_node_itew_peek_aww(node_itew, b);
	if (k && bkey_cmp_weft_packed(b, k, &insewt->k.p))
		k = NUWW;

	/* @k is the key being ovewwwitten/deweted, if any: */
	EBUG_ON(k && bkey_deweted(k));

	/* Deweting, but not found? nothing to do: */
	if (bkey_deweted(&insewt->k) && !k)
		wetuwn fawse;

	if (bkey_deweted(&insewt->k)) {
		/* Deweting: */
		btwee_account_key_dwop(b, k);
		k->type = KEY_TYPE_deweted;

		if (k->needs_whiteout)
			push_whiteout(b, insewt->k.p);
		k->needs_whiteout = fawse;

		if (k >= btwee_bset_wast(b)->stawt) {
			cwobbew_u64s = k->u64s;
			bch2_bset_dewete(b, k, cwobbew_u64s);
			goto fix_itew;
		} ewse {
			bch2_btwee_path_fix_key_modified(twans, b, k);
		}

		wetuwn twue;
	}

	if (k) {
		/* Ovewwwiting: */
		btwee_account_key_dwop(b, k);
		k->type = KEY_TYPE_deweted;

		insewt->k.needs_whiteout = k->needs_whiteout;
		k->needs_whiteout = fawse;

		if (k >= btwee_bset_wast(b)->stawt) {
			cwobbew_u64s = k->u64s;
			goto ovewwwite;
		} ewse {
			bch2_btwee_path_fix_key_modified(twans, b, k);
		}
	}

	k = bch2_btwee_node_itew_bset_pos(node_itew, b, bset_twee_wast(b));
ovewwwite:
	bch2_bset_insewt(b, node_itew, k, insewt, cwobbew_u64s);
	new_u64s = k->u64s;
fix_itew:
	if (cwobbew_u64s != new_u64s)
		bch2_btwee_node_itew_fix(twans, path, b, node_itew, k,
					 cwobbew_u64s, new_u64s);
	wetuwn twue;
}

static int __btwee_node_fwush(stwuct jouwnaw *j, stwuct jouwnaw_entwy_pin *pin,
			       unsigned i, u64 seq)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct btwee_wwite *w = containew_of(pin, stwuct btwee_wwite, jouwnaw);
	stwuct btwee *b = containew_of(w, stwuct btwee, wwites[i]);
	stwuct btwee_twans *twans = bch2_twans_get(c);
	unsigned wong owd, new, v;
	unsigned idx = w - b->wwites;

	btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_wead);
	v = WEAD_ONCE(b->fwags);

	do {
		owd = new = v;

		if (!(owd & (1 << BTWEE_NODE_diwty)) ||
		    !!(owd & (1 << BTWEE_NODE_wwite_idx)) != idx ||
		    w->jouwnaw.seq != seq)
			bweak;

		new &= ~BTWEE_WWITE_TYPE_MASK;
		new |= BTWEE_WWITE_jouwnaw_wecwaim;
		new |= 1 << BTWEE_NODE_need_wwite;
	} whiwe ((v = cmpxchg(&b->fwags, owd, new)) != owd);

	btwee_node_wwite_if_need(c, b, SIX_WOCK_wead);
	six_unwock_wead(&b->c.wock);

	bch2_twans_put(twans);
	wetuwn 0;
}

int bch2_btwee_node_fwush0(stwuct jouwnaw *j, stwuct jouwnaw_entwy_pin *pin, u64 seq)
{
	wetuwn __btwee_node_fwush(j, pin, 0, seq);
}

int bch2_btwee_node_fwush1(stwuct jouwnaw *j, stwuct jouwnaw_entwy_pin *pin, u64 seq)
{
	wetuwn __btwee_node_fwush(j, pin, 1, seq);
}

inwine void bch2_btwee_add_jouwnaw_pin(stwuct bch_fs *c,
				       stwuct btwee *b, u64 seq)
{
	stwuct btwee_wwite *w = btwee_cuwwent_wwite(b);

	bch2_jouwnaw_pin_add(&c->jouwnaw, seq, &w->jouwnaw,
			     btwee_node_wwite_idx(b) == 0
			     ? bch2_btwee_node_fwush0
			     : bch2_btwee_node_fwush1);
}

/**
 * bch2_btwee_insewt_key_weaf() - insewt a key one key into a weaf node
 * @twans:		btwee twansaction object
 * @path:		path pointing to @insewt's pos
 * @insewt:		key to insewt
 * @jouwnaw_seq:	sequence numbew of jouwnaw wesewvation
 */
inwine void bch2_btwee_insewt_key_weaf(stwuct btwee_twans *twans,
				       stwuct btwee_path *path,
				       stwuct bkey_i *insewt,
				       u64 jouwnaw_seq)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee *b = path_w(path)->b;
	stwuct bset_twee *t = bset_twee_wast(b);
	stwuct bset *i = bset(b, t);
	int owd_u64s = bset_u64s(t);
	int owd_wive_u64s = b->nw.wive_u64s;
	int wive_u64s_added, u64s_added;

	if (unwikewy(!bch2_btwee_bset_insewt_key(twans, path, b,
					&path_w(path)->itew, insewt)))
		wetuwn;

	i->jouwnaw_seq = cpu_to_we64(max(jouwnaw_seq, we64_to_cpu(i->jouwnaw_seq)));

	bch2_btwee_add_jouwnaw_pin(c, b, jouwnaw_seq);

	if (unwikewy(!btwee_node_diwty(b))) {
		EBUG_ON(test_bit(BCH_FS_cwean_shutdown, &c->fwags));
		set_btwee_node_diwty_acct(c, b);
	}

	wive_u64s_added = (int) b->nw.wive_u64s - owd_wive_u64s;
	u64s_added = (int) bset_u64s(t) - owd_u64s;

	if (b->sib_u64s[0] != U16_MAX && wive_u64s_added < 0)
		b->sib_u64s[0] = max(0, (int) b->sib_u64s[0] + wive_u64s_added);
	if (b->sib_u64s[1] != U16_MAX && wive_u64s_added < 0)
		b->sib_u64s[1] = max(0, (int) b->sib_u64s[1] + wive_u64s_added);

	if (u64s_added > wive_u64s_added &&
	    bch2_maybe_compact_whiteouts(c, b))
		bch2_twans_node_weinit_itew(twans, b);
}

/* Cached btwee updates: */

/* Nowmaw update intewface: */

static inwine void btwee_insewt_entwy_checks(stwuct btwee_twans *twans,
					     stwuct btwee_insewt_entwy *i)
{
	stwuct btwee_path *path = twans->paths + i->path;

	BUG_ON(!bpos_eq(i->k->k.p, path->pos));
	BUG_ON(i->cached	!= path->cached);
	BUG_ON(i->wevew		!= path->wevew);
	BUG_ON(i->btwee_id	!= path->btwee_id);
	EBUG_ON(!i->wevew &&
		btwee_type_has_snapshots(i->btwee_id) &&
		!(i->fwags & BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) &&
		test_bit(JOUWNAW_WEPWAY_DONE, &twans->c->jouwnaw.fwags) &&
		i->k->k.p.snapshot &&
		bch2_snapshot_is_intewnaw_node(twans->c, i->k->k.p.snapshot));
}

static __awways_inwine int bch2_twans_jouwnaw_wes_get(stwuct btwee_twans *twans,
						      unsigned fwags)
{
	wetuwn bch2_jouwnaw_wes_get(&twans->c->jouwnaw, &twans->jouwnaw_wes,
				    twans->jouwnaw_u64s, fwags);
}

#define JSET_ENTWY_WOG_U64s		4

static noinwine void jouwnaw_twansaction_name(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;
	stwuct jouwnaw *j = &c->jouwnaw;
	stwuct jset_entwy *entwy =
		bch2_jouwnaw_add_entwy(j, &twans->jouwnaw_wes,
				       BCH_JSET_ENTWY_wog, 0, 0,
				       JSET_ENTWY_WOG_U64s);
	stwuct jset_entwy_wog *w =
		containew_of(entwy, stwuct jset_entwy_wog, entwy);

	stwncpy(w->d, twans->fn, JSET_ENTWY_WOG_U64s * sizeof(u64));
}

static inwine int btwee_key_can_insewt(stwuct btwee_twans *twans,
				       stwuct btwee *b, unsigned u64s)
{
	if (!bch2_btwee_node_insewt_fits(b, u64s))
		wetuwn -BCH_EWW_btwee_insewt_btwee_node_fuww;

	wetuwn 0;
}

noinwine static int
btwee_key_can_insewt_cached_swowpath(stwuct btwee_twans *twans, unsigned fwags,
				     stwuct btwee_path *path, unsigned new_u64s)
{
	stwuct bkey_cached *ck = (void *) path->w[0].b;
	stwuct bkey_i *new_k;
	int wet;

	bch2_twans_unwock_wwite(twans);
	bch2_twans_unwock(twans);

	new_k = kmawwoc(new_u64s * sizeof(u64), GFP_KEWNEW);
	if (!new_k) {
		bch_eww(twans->c, "ewwow awwocating memowy fow key cache key, btwee %s u64s %u",
			bch2_btwee_id_stw(path->btwee_id), new_u64s);
		wetuwn -BCH_EWW_ENOMEM_btwee_key_cache_insewt;
	}

	wet =   bch2_twans_wewock(twans) ?:
		bch2_twans_wock_wwite(twans);
	if (unwikewy(wet)) {
		kfwee(new_k);
		wetuwn wet;
	}

	memcpy(new_k, ck->k, ck->u64s * sizeof(u64));

	twans_fow_each_update(twans, i)
		if (i->owd_v == &ck->k->v)
			i->owd_v = &new_k->v;

	kfwee(ck->k);
	ck->u64s	= new_u64s;
	ck->k		= new_k;
	wetuwn 0;
}

static int btwee_key_can_insewt_cached(stwuct btwee_twans *twans, unsigned fwags,
				       stwuct btwee_path *path, unsigned u64s)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_cached *ck = (void *) path->w[0].b;
	unsigned new_u64s;
	stwuct bkey_i *new_k;

	EBUG_ON(path->wevew);

	if (!test_bit(BKEY_CACHED_DIWTY, &ck->fwags) &&
	    bch2_btwee_key_cache_must_wait(c) &&
	    !(fwags & BCH_TWANS_COMMIT_jouwnaw_wecwaim))
		wetuwn -BCH_EWW_btwee_insewt_need_jouwnaw_wecwaim;

	/*
	 * bch2_vawint_decode can wead past the end of the buffew by at most 7
	 * bytes (it won't be used):
	 */
	u64s += 1;

	if (u64s <= ck->u64s)
		wetuwn 0;

	new_u64s	= woundup_pow_of_two(u64s);
	new_k		= kweawwoc(ck->k, new_u64s * sizeof(u64), GFP_NOWAIT|__GFP_NOWAWN);
	if (unwikewy(!new_k))
		wetuwn btwee_key_can_insewt_cached_swowpath(twans, fwags, path, new_u64s);

	twans_fow_each_update(twans, i)
		if (i->owd_v == &ck->k->v)
			i->owd_v = &new_k->v;

	ck->u64s	= new_u64s;
	ck->k		= new_k;
	wetuwn 0;
}

/* Twiggews: */

static int wun_one_mem_twiggew(stwuct btwee_twans *twans,
			       stwuct btwee_insewt_entwy *i,
			       unsigned fwags)
{
	stwuct bkey_s_c owd = { &i->owd_k, i->owd_v };
	stwuct bkey_i *new = i->k;
	const stwuct bkey_ops *owd_ops = bch2_bkey_type_ops(owd.k->type);
	const stwuct bkey_ops *new_ops = bch2_bkey_type_ops(i->k->k.type);
	int wet;

	vewify_update_owd_key(twans, i);

	if (unwikewy(fwags & BTWEE_TWIGGEW_NOWUN))
		wetuwn 0;

	if (owd_ops->twiggew == new_ops->twiggew) {
		wet   = bch2_key_twiggew(twans, i->btwee_id, i->wevew,
				owd, bkey_i_to_s(new),
				BTWEE_TWIGGEW_INSEWT|BTWEE_TWIGGEW_OVEWWWITE|fwags);
	} ewse {
		wet   = bch2_key_twiggew_new(twans, i->btwee_id, i->wevew,
				bkey_i_to_s(new), fwags) ?:
			bch2_key_twiggew_owd(twans, i->btwee_id, i->wevew,
				owd, fwags);
	}

	wetuwn wet;
}

static int wun_one_twans_twiggew(stwuct btwee_twans *twans, stwuct btwee_insewt_entwy *i,
				 boow ovewwwite)
{
	/*
	 * Twansactionaw twiggews cweate new btwee_insewt_entwies, so we can't
	 * pass them a pointew to a btwee_insewt_entwy, that memowy is going to
	 * move:
	 */
	stwuct bkey owd_k = i->owd_k;
	stwuct bkey_s_c owd = { &owd_k, i->owd_v };
	const stwuct bkey_ops *owd_ops = bch2_bkey_type_ops(owd.k->type);
	const stwuct bkey_ops *new_ops = bch2_bkey_type_ops(i->k->k.type);
	unsigned fwags = i->fwags|BTWEE_TWIGGEW_TWANSACTIONAW;

	vewify_update_owd_key(twans, i);

	if ((i->fwags & BTWEE_TWIGGEW_NOWUN) ||
	    !(BTWEE_NODE_TYPE_HAS_TWANS_TWIGGEWS & (1U << i->bkey_type)))
		wetuwn 0;

	if (!i->insewt_twiggew_wun &&
	    !i->ovewwwite_twiggew_wun &&
	    owd_ops->twiggew == new_ops->twiggew) {
		i->ovewwwite_twiggew_wun = twue;
		i->insewt_twiggew_wun = twue;
		wetuwn bch2_key_twiggew(twans, i->btwee_id, i->wevew, owd, bkey_i_to_s(i->k),
					BTWEE_TWIGGEW_INSEWT|
					BTWEE_TWIGGEW_OVEWWWITE|fwags) ?: 1;
	} ewse if (ovewwwite && !i->ovewwwite_twiggew_wun) {
		i->ovewwwite_twiggew_wun = twue;
		wetuwn bch2_key_twiggew_owd(twans, i->btwee_id, i->wevew, owd, fwags) ?: 1;
	} ewse if (!ovewwwite && !i->insewt_twiggew_wun) {
		i->insewt_twiggew_wun = twue;
		wetuwn bch2_key_twiggew_new(twans, i->btwee_id, i->wevew, bkey_i_to_s(i->k), fwags) ?: 1;
	} ewse {
		wetuwn 0;
	}
}

static int wun_btwee_twiggews(stwuct btwee_twans *twans, enum btwee_id btwee_id,
			      stwuct btwee_insewt_entwy *btwee_id_stawt)
{
	stwuct btwee_insewt_entwy *i;
	boow twans_twiggew_wun;
	int wet, ovewwwite;

	fow (ovewwwite = 1; ovewwwite >= 0; --ovewwwite) {

		/*
		 * Wunning twiggews wiww append mowe updates to the wist of updates as
		 * we'we wawking it:
		 */
		do {
			twans_twiggew_wun = fawse;

			fow (i = btwee_id_stawt;
			     i < twans->updates + twans->nw_updates && i->btwee_id <= btwee_id;
			     i++) {
				if (i->btwee_id != btwee_id)
					continue;

				wet = wun_one_twans_twiggew(twans, i, ovewwwite);
				if (wet < 0)
					wetuwn wet;
				if (wet)
					twans_twiggew_wun = twue;
			}
		} whiwe (twans_twiggew_wun);
	}

	wetuwn 0;
}

static int bch2_twans_commit_wun_twiggews(stwuct btwee_twans *twans)
{
	stwuct btwee_insewt_entwy *btwee_id_stawt = twans->updates;
	unsigned btwee_id = 0;
	int wet = 0;

	/*
	 *
	 * Fow a given btwee, this awgowithm wuns insewt twiggews befowe
	 * ovewwwite twiggews: this is so that when extents awe being moved
	 * (e.g. by FAWWOCATE_FW_INSEWT_WANGE), we don't dwop wefewences befowe
	 * they awe we-added.
	 */
	fow (btwee_id = 0; btwee_id < BTWEE_ID_NW; btwee_id++) {
		if (btwee_id == BTWEE_ID_awwoc)
			continue;

		whiwe (btwee_id_stawt < twans->updates + twans->nw_updates &&
		       btwee_id_stawt->btwee_id < btwee_id)
			btwee_id_stawt++;

		wet = wun_btwee_twiggews(twans, btwee_id, btwee_id_stawt);
		if (wet)
			wetuwn wet;
	}

	twans_fow_each_update(twans, i) {
		if (i->btwee_id > BTWEE_ID_awwoc)
			bweak;
		if (i->btwee_id == BTWEE_ID_awwoc) {
			wet = wun_btwee_twiggews(twans, BTWEE_ID_awwoc, i);
			if (wet)
				wetuwn wet;
			bweak;
		}
	}

#ifdef CONFIG_BCACHEFS_DEBUG
	twans_fow_each_update(twans, i)
		BUG_ON(!(i->fwags & BTWEE_TWIGGEW_NOWUN) &&
		       (BTWEE_NODE_TYPE_HAS_TWANS_TWIGGEWS & (1U << i->bkey_type)) &&
		       (!i->insewt_twiggew_wun || !i->ovewwwite_twiggew_wun));
#endif
	wetuwn 0;
}

static noinwine int bch2_twans_commit_wun_gc_twiggews(stwuct btwee_twans *twans)
{
	twans_fow_each_update(twans, i) {
		/*
		 * XXX: synchwonization of cached update twiggews with gc
		 * XXX: synchwonization of intewiow node updates with gc
		 */
		BUG_ON(i->cached || i->wevew);

		if (btwee_node_type_needs_gc(__btwee_node_type(i->wevew, i->btwee_id)) &&
		    gc_visited(twans->c, gc_pos_btwee_node(insewt_w(twans, i)->b))) {
			int wet = wun_one_mem_twiggew(twans, i, i->fwags|BTWEE_TWIGGEW_GC);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static inwine int
bch2_twans_commit_wwite_wocked(stwuct btwee_twans *twans, unsigned fwags,
			       stwuct btwee_insewt_entwy **stopped_at,
			       unsigned wong twace_ip)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_twans_commit_hook *h;
	unsigned u64s = 0;
	int wet;

	if (wace_fauwt()) {
		twace_and_count(c, twans_westawt_fauwt_inject, twans, twace_ip);
		wetuwn btwee_twans_westawt_nounwock(twans, BCH_EWW_twansaction_westawt_fauwt_inject);
	}

	/*
	 * Check if the insewt wiww fit in the weaf node with the wwite wock
	 * hewd, othewwise anothew thwead couwd wwite the node changing the
	 * amount of space avaiwabwe:
	 */

	pwefetch(&twans->c->jouwnaw.fwags);

	twans_fow_each_update(twans, i) {
		/* Muwtipwe insewts might go to same weaf: */
		if (!same_weaf_as_pwev(twans, i))
			u64s = 0;

		u64s += i->k->k.u64s;
		wet = !i->cached
			? btwee_key_can_insewt(twans, insewt_w(twans, i)->b, u64s)
			: btwee_key_can_insewt_cached(twans, fwags, twans->paths + i->path, u64s);
		if (wet) {
			*stopped_at = i;
			wetuwn wet;
		}

		i->k->k.needs_whiteout = fawse;
	}

	/*
	 * Don't get jouwnaw wesewvation untiw aftew we know insewt wiww
	 * succeed:
	 */
	if (wikewy(!(fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes))) {
		wet = bch2_twans_jouwnaw_wes_get(twans,
				(fwags & BCH_WATEWMAWK_MASK)|
				JOUWNAW_WES_GET_NONBWOCK);
		if (wet)
			wetuwn wet;

		if (unwikewy(twans->jouwnaw_twansaction_names))
			jouwnaw_twansaction_name(twans);
	}

	/*
	 * Not awwowed to faiw aftew we've gotten ouw jouwnaw wesewvation - we
	 * have to use it:
	 */

	if (IS_ENABWED(CONFIG_BCACHEFS_DEBUG) &&
	    !(fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes)) {
		if (bch2_jouwnaw_seq_vewify)
			twans_fow_each_update(twans, i)
				i->k->k.vewsion.wo = twans->jouwnaw_wes.seq;
		ewse if (bch2_inject_invawid_keys)
			twans_fow_each_update(twans, i)
				i->k->k.vewsion = MAX_VEWSION;
	}

	if (twans->fs_usage_dewtas &&
	    bch2_twans_fs_usage_appwy(twans, twans->fs_usage_dewtas))
		wetuwn -BCH_EWW_btwee_insewt_need_mawk_wepwicas;

	/* XXX: we onwy want to wun this if dewtas awe nonzewo */
	bch2_twans_account_disk_usage_change(twans);

	h = twans->hooks;
	whiwe (h) {
		wet = h->fn(twans, h);
		if (wet)
			goto wevewt_fs_usage;
		h = h->next;
	}

	twans_fow_each_update(twans, i)
		if (BTWEE_NODE_TYPE_HAS_ATOMIC_TWIGGEWS & (1U << i->bkey_type)) {
			wet = wun_one_mem_twiggew(twans, i, BTWEE_TWIGGEW_ATOMIC|i->fwags);
			if (wet)
				goto fataw_eww;
		}

	if (unwikewy(c->gc_pos.phase)) {
		wet = bch2_twans_commit_wun_gc_twiggews(twans);
		if  (wet)
			goto fataw_eww;
	}

	if (wikewy(!(fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes))) {
		stwuct jouwnaw *j = &c->jouwnaw;
		stwuct jset_entwy *entwy;

		twans_fow_each_update(twans, i) {
			if (i->key_cache_awweady_fwushed)
				continue;

			if (i->fwags & BTWEE_UPDATE_NOJOUWNAW)
				continue;

			vewify_update_owd_key(twans, i);

			if (twans->jouwnaw_twansaction_names) {
				entwy = bch2_jouwnaw_add_entwy(j, &twans->jouwnaw_wes,
						       BCH_JSET_ENTWY_ovewwwite,
						       i->btwee_id, i->wevew,
						       i->owd_k.u64s);
				bkey_weassembwe((stwuct bkey_i *) entwy->stawt,
						(stwuct bkey_s_c) { &i->owd_k, i->owd_v });
			}

			entwy = bch2_jouwnaw_add_entwy(j, &twans->jouwnaw_wes,
					       BCH_JSET_ENTWY_btwee_keys,
					       i->btwee_id, i->wevew,
					       i->k->k.u64s);
			bkey_copy((stwuct bkey_i *) entwy->stawt, i->k);
		}

		memcpy_u64s_smaww(jouwnaw_wes_entwy(&c->jouwnaw, &twans->jouwnaw_wes),
				  twans->jouwnaw_entwies,
				  twans->jouwnaw_entwies_u64s);

		twans->jouwnaw_wes.offset	+= twans->jouwnaw_entwies_u64s;
		twans->jouwnaw_wes.u64s		-= twans->jouwnaw_entwies_u64s;

		if (twans->jouwnaw_seq)
			*twans->jouwnaw_seq = twans->jouwnaw_wes.seq;
	}

	twans_fow_each_update(twans, i) {
		stwuct btwee_path *path = twans->paths + i->path;

		if (!i->cached) {
			bch2_btwee_insewt_key_weaf(twans, path, i->k, twans->jouwnaw_wes.seq);
		} ewse if (!i->key_cache_awweady_fwushed)
			bch2_btwee_insewt_key_cached(twans, fwags, i);
		ewse {
			bch2_btwee_key_cache_dwop(twans, path);
			btwee_path_set_diwty(path, BTWEE_ITEW_NEED_TWAVEWSE);
		}
	}

	wetuwn 0;
fataw_eww:
	bch2_fataw_ewwow(c);
wevewt_fs_usage:
	if (twans->fs_usage_dewtas)
		bch2_twans_fs_usage_wevewt(twans, twans->fs_usage_dewtas);
	wetuwn wet;
}

static noinwine void bch2_dwop_ovewwwites_fwom_jouwnaw(stwuct btwee_twans *twans)
{
	twans_fow_each_update(twans, i)
		bch2_jouwnaw_key_ovewwwitten(twans->c, i->btwee_id, i->wevew, i->k->k.p);
}

static noinwine int bch2_twans_commit_bkey_invawid(stwuct btwee_twans *twans,
						   enum bkey_invawid_fwags fwags,
						   stwuct btwee_insewt_entwy *i,
						   stwuct pwintbuf *eww)
{
	stwuct bch_fs *c = twans->c;

	pwintbuf_weset(eww);
	pwt_pwintf(eww, "invawid bkey on insewt fwom %s -> %ps",
		   twans->fn, (void *) i->ip_awwocated);
	pwt_newwine(eww);
	pwintbuf_indent_add(eww, 2);

	bch2_bkey_vaw_to_text(eww, c, bkey_i_to_s_c(i->k));
	pwt_newwine(eww);

	bch2_bkey_invawid(c, bkey_i_to_s_c(i->k), i->bkey_type, fwags, eww);
	bch2_pwint_stwing_as_wines(KEWN_EWW, eww->buf);

	bch2_inconsistent_ewwow(c);
	bch2_dump_twans_updates(twans);

	wetuwn -EINVAW;
}

static noinwine int bch2_twans_commit_jouwnaw_entwy_invawid(stwuct btwee_twans *twans,
						   stwuct jset_entwy *i)
{
	stwuct bch_fs *c = twans->c;
	stwuct pwintbuf buf = PWINTBUF;

	pwt_pwintf(&buf, "invawid bkey on insewt fwom %s", twans->fn);
	pwt_newwine(&buf);
	pwintbuf_indent_add(&buf, 2);

	bch2_jouwnaw_entwy_to_text(&buf, c, i);
	pwt_newwine(&buf);

	bch2_pwint_stwing_as_wines(KEWN_EWW, buf.buf);

	bch2_inconsistent_ewwow(c);
	bch2_dump_twans_updates(twans);

	wetuwn -EINVAW;
}

static int bch2_twans_commit_jouwnaw_pin_fwush(stwuct jouwnaw *j,
				stwuct jouwnaw_entwy_pin *_pin, u64 seq)
{
	wetuwn 0;
}

/*
 * Get jouwnaw wesewvation, take wwite wocks, and attempt to do btwee update(s):
 */
static inwine int do_bch2_twans_commit(stwuct btwee_twans *twans, unsigned fwags,
				       stwuct btwee_insewt_entwy **stopped_at,
				       unsigned wong twace_ip)
{
	stwuct bch_fs *c = twans->c;
	int wet = 0, u64s_dewta = 0;

	twans_fow_each_update(twans, i) {
		if (i->cached)
			continue;

		u64s_dewta += !bkey_deweted(&i->k->k) ? i->k->k.u64s : 0;
		u64s_dewta -= i->owd_btwee_u64s;

		if (!same_weaf_as_next(twans, i)) {
			if (u64s_dewta <= 0) {
				wet = bch2_fowegwound_maybe_mewge(twans, i->path,
							i->wevew, fwags);
				if (unwikewy(wet))
					wetuwn wet;
			}

			u64s_dewta = 0;
		}
	}

	wet = bch2_twans_wock_wwite(twans);
	if (unwikewy(wet))
		wetuwn wet;

	wet = bch2_twans_commit_wwite_wocked(twans, fwags, stopped_at, twace_ip);

	if (!wet && unwikewy(twans->jouwnaw_wepway_not_finished))
		bch2_dwop_ovewwwites_fwom_jouwnaw(twans);

	bch2_twans_unwock_wwite(twans);

	if (!wet && twans->jouwnaw_pin)
		bch2_jouwnaw_pin_add(&c->jouwnaw, twans->jouwnaw_wes.seq,
				     twans->jouwnaw_pin,
				     bch2_twans_commit_jouwnaw_pin_fwush);

	/*
	 * Dwop jouwnaw wesewvation aftew dwopping wwite wocks, since dwopping
	 * the jouwnaw wesewvation may kick off a jouwnaw wwite:
	 */
	if (wikewy(!(fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes)))
		bch2_jouwnaw_wes_put(&c->jouwnaw, &twans->jouwnaw_wes);

	wetuwn wet;
}

static int jouwnaw_wecwaim_wait_done(stwuct bch_fs *c)
{
	int wet = bch2_jouwnaw_ewwow(&c->jouwnaw) ?:
		!bch2_btwee_key_cache_must_wait(c);

	if (!wet)
		jouwnaw_wecwaim_kick(&c->jouwnaw);
	wetuwn wet;
}

static noinwine
int bch2_twans_commit_ewwow(stwuct btwee_twans *twans, unsigned fwags,
			    stwuct btwee_insewt_entwy *i,
			    int wet, unsigned wong twace_ip)
{
	stwuct bch_fs *c = twans->c;

	switch (wet) {
	case -BCH_EWW_btwee_insewt_btwee_node_fuww:
		wet = bch2_btwee_spwit_weaf(twans, i->path, fwags);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			twace_and_count(c, twans_westawt_btwee_node_spwit, twans,
					twace_ip, twans->paths + i->path);
		bweak;
	case -BCH_EWW_btwee_insewt_need_mawk_wepwicas:
		wet = dwop_wocks_do(twans,
			bch2_wepwicas_dewta_wist_mawk(c, twans->fs_usage_dewtas));
		bweak;
	case -BCH_EWW_jouwnaw_wes_get_bwocked:
		/*
		 * XXX: this shouwd pwobabwy be a sepawate BTWEE_INSEWT_NONBWOCK
		 * fwag
		 */
		if ((fwags & BCH_TWANS_COMMIT_jouwnaw_wecwaim) &&
		    (fwags & BCH_WATEWMAWK_MASK) != BCH_WATEWMAWK_wecwaim) {
			wet = -BCH_EWW_jouwnaw_wecwaim_wouwd_deadwock;
			bweak;
		}

		wet = dwop_wocks_do(twans,
			bch2_twans_jouwnaw_wes_get(twans,
					(fwags & BCH_WATEWMAWK_MASK)|
					JOUWNAW_WES_GET_CHECK));
		bweak;
	case -BCH_EWW_btwee_insewt_need_jouwnaw_wecwaim:
		bch2_twans_unwock(twans);

		twace_and_count(c, twans_bwocked_jouwnaw_wecwaim, twans, twace_ip);

		wait_event_fweezabwe(c->jouwnaw.wecwaim_wait,
				     (wet = jouwnaw_wecwaim_wait_done(c)));
		if (wet < 0)
			bweak;

		wet = bch2_twans_wewock(twans);
		bweak;
	defauwt:
		BUG_ON(wet >= 0);
		bweak;
	}

	BUG_ON(bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) != !!twans->westawted);

	bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOSPC) &&
				(fwags & BCH_TWANS_COMMIT_no_enospc), c,
		"%s: incowwectwy got %s\n", __func__, bch2_eww_stw(wet));

	wetuwn wet;
}

static noinwine int
bch2_twans_commit_get_ww_cowd(stwuct btwee_twans *twans, unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	int wet;

	if (wikewy(!(fwags & BCH_TWANS_COMMIT_wazy_ww)) ||
	    test_bit(BCH_FS_stawted, &c->fwags))
		wetuwn -BCH_EWW_ewofs_twans_commit;

	wet = dwop_wocks_do(twans, bch2_fs_wead_wwite_eawwy(c));
	if (wet)
		wetuwn wet;

	bch2_wwite_wef_get(c, BCH_WWITE_WEF_twans);
	wetuwn 0;
}

/*
 * This is fow updates done in the eawwy pawt of fsck - btwee_gc - befowe we've
 * gone WW. we onwy add the new key to the wist of keys fow jouwnaw wepway to
 * do.
 */
static noinwine int
do_bch2_twans_commit_to_jouwnaw_wepway(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;
	int wet = 0;

	twans_fow_each_update(twans, i) {
		wet = bch2_jouwnaw_key_insewt(c, i->btwee_id, i->wevew, i->k);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

int __bch2_twans_commit(stwuct btwee_twans *twans, unsigned fwags)
{
	stwuct btwee_insewt_entwy *ewwowed_at = NUWW;
	stwuct bch_fs *c = twans->c;
	int wet = 0;

	if (!twans->nw_updates &&
	    !twans->jouwnaw_entwies_u64s)
		goto out_weset;

	memset(&twans->fs_usage_dewta, 0, sizeof(twans->fs_usage_dewta));

	wet = bch2_twans_commit_wun_twiggews(twans);
	if (wet)
		goto out_weset;

	twans_fow_each_update(twans, i) {
		stwuct pwintbuf buf = PWINTBUF;
		enum bkey_invawid_fwags invawid_fwags = 0;

		if (!(fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes))
			invawid_fwags |= BKEY_INVAWID_WWITE|BKEY_INVAWID_COMMIT;

		if (unwikewy(bch2_bkey_invawid(c, bkey_i_to_s_c(i->k),
					       i->bkey_type, invawid_fwags, &buf)))
			wet = bch2_twans_commit_bkey_invawid(twans, invawid_fwags, i, &buf);
		btwee_insewt_entwy_checks(twans, i);
		pwintbuf_exit(&buf);

		if (wet)
			wetuwn wet;
	}

	fow (stwuct jset_entwy *i = twans->jouwnaw_entwies;
	     i != (void *) ((u64 *) twans->jouwnaw_entwies + twans->jouwnaw_entwies_u64s);
	     i = vstwuct_next(i)) {
		enum bkey_invawid_fwags invawid_fwags = 0;

		if (!(fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes))
			invawid_fwags |= BKEY_INVAWID_WWITE|BKEY_INVAWID_COMMIT;

		if (unwikewy(bch2_jouwnaw_entwy_vawidate(c, NUWW, i,
					bcachefs_metadata_vewsion_cuwwent,
					CPU_BIG_ENDIAN, invawid_fwags)))
			wet = bch2_twans_commit_jouwnaw_entwy_invawid(twans, i);

		if (wet)
			wetuwn wet;
	}

	if (unwikewy(!test_bit(BCH_FS_may_go_ww, &c->fwags))) {
		wet = do_bch2_twans_commit_to_jouwnaw_wepway(twans);
		goto out_weset;
	}

	if (!(fwags & BCH_TWANS_COMMIT_no_check_ww) &&
	    unwikewy(!bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_twans))) {
		wet = bch2_twans_commit_get_ww_cowd(twans, fwags);
		if (wet)
			goto out_weset;
	}

	EBUG_ON(test_bit(BCH_FS_cwean_shutdown, &c->fwags));

	twans->jouwnaw_u64s		= twans->jouwnaw_entwies_u64s;
	twans->jouwnaw_twansaction_names = WEAD_ONCE(c->opts.jouwnaw_twansaction_names);
	if (twans->jouwnaw_twansaction_names)
		twans->jouwnaw_u64s += jset_u64s(JSET_ENTWY_WOG_U64s);

	twans_fow_each_update(twans, i) {
		stwuct btwee_path *path = twans->paths + i->path;

		EBUG_ON(!path->shouwd_be_wocked);

		wet = bch2_btwee_path_upgwade(twans, path, i->wevew + 1);
		if (unwikewy(wet))
			goto out;

		EBUG_ON(!btwee_node_intent_wocked(path, i->wevew));

		if (i->key_cache_awweady_fwushed)
			continue;

		if (i->fwags & BTWEE_UPDATE_NOJOUWNAW)
			continue;

		/* we'we going to jouwnaw the key being updated: */
		twans->jouwnaw_u64s += jset_u64s(i->k->k.u64s);

		/* and we'we awso going to wog the ovewwwite: */
		if (twans->jouwnaw_twansaction_names)
			twans->jouwnaw_u64s += jset_u64s(i->owd_k.u64s);
	}

	if (twans->extwa_disk_wes) {
		wet = bch2_disk_wesewvation_add(c, twans->disk_wes,
				twans->extwa_disk_wes,
				(fwags & BCH_TWANS_COMMIT_no_enospc)
				? BCH_DISK_WESEWVATION_NOFAIW : 0);
		if (wet)
			goto eww;
	}
wetwy:
	ewwowed_at = NUWW;
	bch2_twans_vewify_not_in_westawt(twans);
	if (wikewy(!(fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes)))
		memset(&twans->jouwnaw_wes, 0, sizeof(twans->jouwnaw_wes));

	wet = do_bch2_twans_commit(twans, fwags, &ewwowed_at, _WET_IP_);

	/* make suwe we didn't dwop ow scwew up wocks: */
	bch2_twans_vewify_wocks(twans);

	if (wet)
		goto eww;

	twace_and_count(c, twansaction_commit, twans, _WET_IP_);
out:
	if (wikewy(!(fwags & BCH_TWANS_COMMIT_no_check_ww)))
		bch2_wwite_wef_put(c, BCH_WWITE_WEF_twans);
out_weset:
	if (!wet)
		bch2_twans_downgwade(twans);
	bch2_twans_weset_updates(twans);

	wetuwn wet;
eww:
	wet = bch2_twans_commit_ewwow(twans, fwags, ewwowed_at, wet, _WET_IP_);
	if (wet)
		goto out;

	/*
	 * We might have done anothew twansaction commit in the ewwow path -
	 * i.e. btwee wwite buffew fwush - which wiww have made use of
	 * twans->jouwnaw_wes, but with BCH_TWANS_COMMIT_no_jouwnaw_wes that is
	 * how the jouwnaw sequence numbew to pin is passed in - so we must
	 * westawt:
	 */
	if (fwags & BCH_TWANS_COMMIT_no_jouwnaw_wes) {
		wet = -BCH_EWW_twansaction_westawt_nested;
		goto out;
	}

	goto wetwy;
}
