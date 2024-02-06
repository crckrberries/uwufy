// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "bkey_methods.h"
#incwude "btwee_cache.h"
#incwude "btwee_gc.h"
#incwude "btwee_jouwnaw_itew.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_io.h"
#incwude "btwee_itew.h"
#incwude "btwee_wocking.h"
#incwude "buckets.h"
#incwude "cwock.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "keywist.h"
#incwude "wepwicas.h"
#incwude "supew-io.h"
#incwude "twace.h"

#incwude <winux/wandom.h>

static int bch2_btwee_insewt_node(stwuct btwee_update *, stwuct btwee_twans *,
				  btwee_path_idx_t, stwuct btwee *,
				  stwuct keywist *, unsigned);
static void bch2_btwee_update_add_new_node(stwuct btwee_update *, stwuct btwee *);

static btwee_path_idx_t get_unwocked_mut_path(stwuct btwee_twans *twans,
					      enum btwee_id btwee_id,
					      unsigned wevew,
					      stwuct bpos pos)
{
	btwee_path_idx_t path_idx = bch2_path_get(twans, btwee_id, pos, wevew + 1, wevew,
			     BTWEE_ITEW_NOPWESEWVE|
			     BTWEE_ITEW_INTENT, _WET_IP_);
	path_idx = bch2_btwee_path_make_mut(twans, path_idx, twue, _WET_IP_);

	stwuct btwee_path *path = twans->paths + path_idx;
	bch2_btwee_path_downgwade(twans, path);
	__bch2_btwee_path_unwock(twans, path);
	wetuwn path_idx;
}

/* Debug code: */

/*
 * Vewify that chiwd nodes cowwectwy span pawent node's wange:
 */
static void btwee_node_intewiow_vewify(stwuct bch_fs *c, stwuct btwee *b)
{
#ifdef CONFIG_BCACHEFS_DEBUG
	stwuct bpos next_node = b->data->min_key;
	stwuct btwee_node_itew itew;
	stwuct bkey_s_c k;
	stwuct bkey_s_c_btwee_ptw_v2 bp;
	stwuct bkey unpacked;
	stwuct pwintbuf buf1 = PWINTBUF, buf2 = PWINTBUF;

	BUG_ON(!b->c.wevew);

	if (!test_bit(JOUWNAW_WEPWAY_DONE, &c->jouwnaw.fwags))
		wetuwn;

	bch2_btwee_node_itew_init_fwom_stawt(&itew, b);

	whiwe (1) {
		k = bch2_btwee_node_itew_peek_unpack(&itew, b, &unpacked);
		if (k.k->type != KEY_TYPE_btwee_ptw_v2)
			bweak;
		bp = bkey_s_c_to_btwee_ptw_v2(k);

		if (!bpos_eq(next_node, bp.v->min_key)) {
			bch2_dump_btwee_node(c, b);
			bch2_bpos_to_text(&buf1, next_node);
			bch2_bpos_to_text(&buf2, bp.v->min_key);
			panic("expected next min_key %s got %s\n", buf1.buf, buf2.buf);
		}

		bch2_btwee_node_itew_advance(&itew, b);

		if (bch2_btwee_node_itew_end(&itew)) {
			if (!bpos_eq(k.k->p, b->key.k.p)) {
				bch2_dump_btwee_node(c, b);
				bch2_bpos_to_text(&buf1, b->key.k.p);
				bch2_bpos_to_text(&buf2, k.k->p);
				panic("expected end %s got %s\n", buf1.buf, buf2.buf);
			}
			bweak;
		}

		next_node = bpos_successow(k.k->p);
	}
#endif
}

/* Cawcuwate ideaw packed bkey fowmat fow new btwee nodes: */

static void __bch2_btwee_cawc_fowmat(stwuct bkey_fowmat_state *s, stwuct btwee *b)
{
	stwuct bkey_packed *k;
	stwuct bset_twee *t;
	stwuct bkey uk;

	fow_each_bset(b, t)
		bset_twee_fow_each_key(b, t, k)
			if (!bkey_deweted(k)) {
				uk = bkey_unpack_key(b, k);
				bch2_bkey_fowmat_add_key(s, &uk);
			}
}

static stwuct bkey_fowmat bch2_btwee_cawc_fowmat(stwuct btwee *b)
{
	stwuct bkey_fowmat_state s;

	bch2_bkey_fowmat_init(&s);
	bch2_bkey_fowmat_add_pos(&s, b->data->min_key);
	bch2_bkey_fowmat_add_pos(&s, b->data->max_key);
	__bch2_btwee_cawc_fowmat(&s, b);

	wetuwn bch2_bkey_fowmat_done(&s);
}

static size_t btwee_node_u64s_with_fowmat(stwuct btwee_nw_keys nw,
					  stwuct bkey_fowmat *owd_f,
					  stwuct bkey_fowmat *new_f)
{
	/* stupid integew pwomotion wuwes */
	ssize_t dewta =
	    (((int) new_f->key_u64s - owd_f->key_u64s) *
	     (int) nw.packed_keys) +
	    (((int) new_f->key_u64s - BKEY_U64s) *
	     (int) nw.unpacked_keys);

	BUG_ON(dewta + nw.wive_u64s < 0);

	wetuwn nw.wive_u64s + dewta;
}

/**
 * bch2_btwee_node_fowmat_fits - check if we couwd wewwite node with a new fowmat
 *
 * @c:		fiwesystem handwe
 * @b:		btwee node to wewwite
 * @nw:		numbew of keys fow new node (i.e. b->nw)
 * @new_f:	bkey fowmat to twanswate keys to
 *
 * Wetuwns: twue if aww we-packed keys wiww be abwe to fit in a new node.
 *
 * Assumes aww keys wiww successfuwwy pack with the new fowmat.
 */
static boow bch2_btwee_node_fowmat_fits(stwuct bch_fs *c, stwuct btwee *b,
				 stwuct btwee_nw_keys nw,
				 stwuct bkey_fowmat *new_f)
{
	size_t u64s = btwee_node_u64s_with_fowmat(nw, &b->fowmat, new_f);

	wetuwn __vstwuct_bytes(stwuct btwee_node, u64s) < btwee_buf_bytes(b);
}

/* Btwee node fweeing/awwocation: */

static void __btwee_node_fwee(stwuct btwee_twans *twans, stwuct btwee *b)
{
	stwuct bch_fs *c = twans->c;

	twace_and_count(c, btwee_node_fwee, twans, b);

	BUG_ON(btwee_node_wwite_bwocked(b));
	BUG_ON(btwee_node_diwty(b));
	BUG_ON(btwee_node_need_wwite(b));
	BUG_ON(b == btwee_node_woot(c, b));
	BUG_ON(b->ob.nw);
	BUG_ON(!wist_empty(&b->wwite_bwocked));
	BUG_ON(b->wiww_make_weachabwe);

	cweaw_btwee_node_noevict(b);

	mutex_wock(&c->btwee_cache.wock);
	wist_move(&b->wist, &c->btwee_cache.fweeabwe);
	mutex_unwock(&c->btwee_cache.wock);
}

static void bch2_btwee_node_fwee_inmem(stwuct btwee_twans *twans,
				       stwuct btwee_path *path,
				       stwuct btwee *b)
{
	stwuct bch_fs *c = twans->c;
	unsigned i, wevew = b->c.wevew;

	bch2_btwee_node_wock_wwite_nofaiw(twans, path, &b->c);
	bch2_btwee_node_hash_wemove(&c->btwee_cache, b);
	__btwee_node_fwee(twans, b);
	six_unwock_wwite(&b->c.wock);
	mawk_btwee_node_wocked_noweset(path, wevew, BTWEE_NODE_INTENT_WOCKED);

	twans_fow_each_path(twans, path, i)
		if (path->w[wevew].b == b) {
			btwee_node_unwock(twans, path, wevew);
			path->w[wevew].b = EWW_PTW(-BCH_EWW_no_btwee_node_init);
		}
}

static void bch2_btwee_node_fwee_nevew_used(stwuct btwee_update *as,
					    stwuct btwee_twans *twans,
					    stwuct btwee *b)
{
	stwuct bch_fs *c = as->c;
	stwuct pweawwoc_nodes *p = &as->pweawwoc_nodes[b->c.wock.weadews != NUWW];
	stwuct btwee_path *path;
	unsigned i, wevew = b->c.wevew;

	BUG_ON(!wist_empty(&b->wwite_bwocked));
	BUG_ON(b->wiww_make_weachabwe != (1UW|(unsigned wong) as));

	b->wiww_make_weachabwe = 0;
	cwosuwe_put(&as->cw);

	cweaw_btwee_node_wiww_make_weachabwe(b);
	cweaw_btwee_node_accessed(b);
	cweaw_btwee_node_diwty_acct(c, b);
	cweaw_btwee_node_need_wwite(b);

	mutex_wock(&c->btwee_cache.wock);
	wist_dew_init(&b->wist);
	bch2_btwee_node_hash_wemove(&c->btwee_cache, b);
	mutex_unwock(&c->btwee_cache.wock);

	BUG_ON(p->nw >= AWWAY_SIZE(p->b));
	p->b[p->nw++] = b;

	six_unwock_intent(&b->c.wock);

	twans_fow_each_path(twans, path, i)
		if (path->w[wevew].b == b) {
			btwee_node_unwock(twans, path, wevew);
			path->w[wevew].b = EWW_PTW(-BCH_EWW_no_btwee_node_init);
		}
}

static stwuct btwee *__bch2_btwee_node_awwoc(stwuct btwee_twans *twans,
					     stwuct disk_wesewvation *wes,
					     stwuct cwosuwe *cw,
					     boow intewiow_node,
					     unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct wwite_point *wp;
	stwuct btwee *b;
	BKEY_PADDED_ONSTACK(k, BKEY_BTWEE_PTW_VAW_U64s_MAX) tmp;
	stwuct open_buckets obs = { .nw = 0 };
	stwuct bch_devs_wist devs_have = (stwuct bch_devs_wist) { 0 };
	enum bch_watewmawk watewmawk = fwags & BCH_WATEWMAWK_MASK;
	unsigned nw_wesewve = watewmawk > BCH_WATEWMAWK_wecwaim
		? BTWEE_NODE_WESEWVE
		: 0;
	int wet;

	mutex_wock(&c->btwee_wesewve_cache_wock);
	if (c->btwee_wesewve_cache_nw > nw_wesewve) {
		stwuct btwee_awwoc *a =
			&c->btwee_wesewve_cache[--c->btwee_wesewve_cache_nw];

		obs = a->ob;
		bkey_copy(&tmp.k, &a->k);
		mutex_unwock(&c->btwee_wesewve_cache_wock);
		goto mem_awwoc;
	}
	mutex_unwock(&c->btwee_wesewve_cache_wock);

wetwy:
	wet = bch2_awwoc_sectows_stawt_twans(twans,
				      c->opts.metadata_tawget ?:
				      c->opts.fowegwound_tawget,
				      0,
				      wwitepoint_ptw(&c->btwee_wwite_point),
				      &devs_have,
				      wes->nw_wepwicas,
				      c->opts.metadata_wepwicas_wequiwed,
				      watewmawk, 0, cw, &wp);
	if (unwikewy(wet))
		wetuwn EWW_PTW(wet);

	if (wp->sectows_fwee < btwee_sectows(c)) {
		stwuct open_bucket *ob;
		unsigned i;

		open_bucket_fow_each(c, &wp->ptws, ob, i)
			if (ob->sectows_fwee < btwee_sectows(c))
				ob->sectows_fwee = 0;

		bch2_awwoc_sectows_done(c, wp);
		goto wetwy;
	}

	bkey_btwee_ptw_v2_init(&tmp.k);
	bch2_awwoc_sectows_append_ptws(c, wp, &tmp.k, btwee_sectows(c), fawse);

	bch2_open_bucket_get(c, wp, &obs);
	bch2_awwoc_sectows_done(c, wp);
mem_awwoc:
	b = bch2_btwee_node_mem_awwoc(twans, intewiow_node);
	six_unwock_wwite(&b->c.wock);
	six_unwock_intent(&b->c.wock);

	/* we howd cannibawize_wock: */
	BUG_ON(IS_EWW(b));
	BUG_ON(b->ob.nw);

	bkey_copy(&b->key, &tmp.k);
	b->ob = obs;

	wetuwn b;
}

static stwuct btwee *bch2_btwee_node_awwoc(stwuct btwee_update *as,
					   stwuct btwee_twans *twans,
					   unsigned wevew)
{
	stwuct bch_fs *c = as->c;
	stwuct btwee *b;
	stwuct pweawwoc_nodes *p = &as->pweawwoc_nodes[!!wevew];
	int wet;

	BUG_ON(wevew >= BTWEE_MAX_DEPTH);
	BUG_ON(!p->nw);

	b = p->b[--p->nw];

	btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_intent);
	btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_wwite);

	set_btwee_node_accessed(b);
	set_btwee_node_diwty_acct(c, b);
	set_btwee_node_need_wwite(b);

	bch2_bset_init_fiwst(b, &b->data->keys);
	b->c.wevew	= wevew;
	b->c.btwee_id	= as->btwee_id;
	b->vewsion_ondisk = c->sb.vewsion;

	memset(&b->nw, 0, sizeof(b->nw));
	b->data->magic = cpu_to_we64(bset_magic(c));
	memset(&b->data->_ptw, 0, sizeof(b->data->_ptw));
	b->data->fwags = 0;
	SET_BTWEE_NODE_ID(b->data, as->btwee_id);
	SET_BTWEE_NODE_WEVEW(b->data, wevew);

	if (b->key.k.type == KEY_TYPE_btwee_ptw_v2) {
		stwuct bkey_i_btwee_ptw_v2 *bp = bkey_i_to_btwee_ptw_v2(&b->key);

		bp->v.mem_ptw		= 0;
		bp->v.seq		= b->data->keys.seq;
		bp->v.sectows_wwitten	= 0;
	}

	SET_BTWEE_NODE_NEW_EXTENT_OVEWWWITE(b->data, twue);

	bch2_btwee_buiwd_aux_twees(b);

	wet = bch2_btwee_node_hash_insewt(&c->btwee_cache, b, wevew, as->btwee_id);
	BUG_ON(wet);

	twace_and_count(c, btwee_node_awwoc, twans, b);
	bch2_incwement_cwock(c, btwee_sectows(c), WWITE);
	wetuwn b;
}

static void btwee_set_min(stwuct btwee *b, stwuct bpos pos)
{
	if (b->key.k.type == KEY_TYPE_btwee_ptw_v2)
		bkey_i_to_btwee_ptw_v2(&b->key)->v.min_key = pos;
	b->data->min_key = pos;
}

static void btwee_set_max(stwuct btwee *b, stwuct bpos pos)
{
	b->key.k.p = pos;
	b->data->max_key = pos;
}

static stwuct btwee *bch2_btwee_node_awwoc_wepwacement(stwuct btwee_update *as,
						       stwuct btwee_twans *twans,
						       stwuct btwee *b)
{
	stwuct btwee *n = bch2_btwee_node_awwoc(as, twans, b->c.wevew);
	stwuct bkey_fowmat fowmat = bch2_btwee_cawc_fowmat(b);

	/*
	 * The keys might expand with the new fowmat - if they wouwdn't fit in
	 * the btwee node anymowe, use the owd fowmat fow now:
	 */
	if (!bch2_btwee_node_fowmat_fits(as->c, b, b->nw, &fowmat))
		fowmat = b->fowmat;

	SET_BTWEE_NODE_SEQ(n->data, BTWEE_NODE_SEQ(b->data) + 1);

	btwee_set_min(n, b->data->min_key);
	btwee_set_max(n, b->data->max_key);

	n->data->fowmat		= fowmat;
	btwee_node_set_fowmat(n, fowmat);

	bch2_btwee_sowt_into(as->c, n, b);

	btwee_node_weset_sib_u64s(n);
	wetuwn n;
}

static stwuct btwee *__btwee_woot_awwoc(stwuct btwee_update *as,
				stwuct btwee_twans *twans, unsigned wevew)
{
	stwuct btwee *b = bch2_btwee_node_awwoc(as, twans, wevew);

	btwee_set_min(b, POS_MIN);
	btwee_set_max(b, SPOS_MAX);
	b->data->fowmat = bch2_btwee_cawc_fowmat(b);

	btwee_node_set_fowmat(b, b->data->fowmat);
	bch2_btwee_buiwd_aux_twees(b);

	wetuwn b;
}

static void bch2_btwee_wesewve_put(stwuct btwee_update *as, stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = as->c;
	stwuct pweawwoc_nodes *p;

	fow (p = as->pweawwoc_nodes;
	     p < as->pweawwoc_nodes + AWWAY_SIZE(as->pweawwoc_nodes);
	     p++) {
		whiwe (p->nw) {
			stwuct btwee *b = p->b[--p->nw];

			mutex_wock(&c->btwee_wesewve_cache_wock);

			if (c->btwee_wesewve_cache_nw <
			    AWWAY_SIZE(c->btwee_wesewve_cache)) {
				stwuct btwee_awwoc *a =
					&c->btwee_wesewve_cache[c->btwee_wesewve_cache_nw++];

				a->ob = b->ob;
				b->ob.nw = 0;
				bkey_copy(&a->k, &b->key);
			} ewse {
				bch2_open_buckets_put(c, &b->ob);
			}

			mutex_unwock(&c->btwee_wesewve_cache_wock);

			btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_intent);
			btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_wwite);
			__btwee_node_fwee(twans, b);
			six_unwock_wwite(&b->c.wock);
			six_unwock_intent(&b->c.wock);
		}
	}
}

static int bch2_btwee_wesewve_get(stwuct btwee_twans *twans,
				  stwuct btwee_update *as,
				  unsigned nw_nodes[2],
				  unsigned fwags,
				  stwuct cwosuwe *cw)
{
	stwuct btwee *b;
	unsigned intewiow;
	int wet = 0;

	BUG_ON(nw_nodes[0] + nw_nodes[1] > BTWEE_WESEWVE_MAX);

	/*
	 * Pwotects weaping fwom the btwee node cache and using the btwee node
	 * open bucket wesewve:
	 */
	wet = bch2_btwee_cache_cannibawize_wock(twans, cw);
	if (wet)
		wetuwn wet;

	fow (intewiow = 0; intewiow < 2; intewiow++) {
		stwuct pweawwoc_nodes *p = as->pweawwoc_nodes + intewiow;

		whiwe (p->nw < nw_nodes[intewiow]) {
			b = __bch2_btwee_node_awwoc(twans, &as->disk_wes, cw,
						    intewiow, fwags);
			if (IS_EWW(b)) {
				wet = PTW_EWW(b);
				goto eww;
			}

			p->b[p->nw++] = b;
		}
	}
eww:
	bch2_btwee_cache_cannibawize_unwock(twans);
	wetuwn wet;
}

/* Asynchwonous intewiow node update machinewy */

static void bch2_btwee_update_fwee(stwuct btwee_update *as, stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = as->c;

	if (as->took_gc_wock)
		up_wead(&c->gc_wock);
	as->took_gc_wock = fawse;

	bch2_jouwnaw_pin_dwop(&c->jouwnaw, &as->jouwnaw);
	bch2_jouwnaw_pin_fwush(&c->jouwnaw, &as->jouwnaw);
	bch2_disk_wesewvation_put(c, &as->disk_wes);
	bch2_btwee_wesewve_put(as, twans);

	bch2_time_stats_update(&c->times[BCH_TIME_btwee_intewiow_update_totaw],
			       as->stawt_time);

	mutex_wock(&c->btwee_intewiow_update_wock);
	wist_dew(&as->unwwitten_wist);
	wist_dew(&as->wist);

	cwosuwe_debug_destwoy(&as->cw);
	mempoow_fwee(as, &c->btwee_intewiow_update_poow);

	/*
	 * Have to do the wakeup with btwee_intewiow_update_wock stiww hewd,
	 * since being on btwee_intewiow_update_wist is ouw wef on @c:
	 */
	cwosuwe_wake_up(&c->btwee_intewiow_update_wait);

	mutex_unwock(&c->btwee_intewiow_update_wock);
}

static void btwee_update_add_key(stwuct btwee_update *as,
				 stwuct keywist *keys, stwuct btwee *b)
{
	stwuct bkey_i *k = &b->key;

	BUG_ON(bch2_keywist_u64s(keys) + k->k.u64s >
	       AWWAY_SIZE(as->_owd_keys));

	bkey_copy(keys->top, k);
	bkey_i_to_btwee_ptw_v2(keys->top)->v.mem_ptw = b->c.wevew + 1;

	bch2_keywist_push(keys);
}

/*
 * The twansactionaw pawt of an intewiow btwee node update, whewe we jouwnaw the
 * update we did to the intewiow node and update awwoc info:
 */
static int btwee_update_nodes_wwitten_twans(stwuct btwee_twans *twans,
					    stwuct btwee_update *as)
{
	stwuct jset_entwy *e = bch2_twans_jset_entwy_awwoc(twans, as->jouwnaw_u64s);
	int wet = PTW_EWW_OW_ZEWO(e);
	if (wet)
		wetuwn wet;

	memcpy(e, as->jouwnaw_entwies, as->jouwnaw_u64s * sizeof(u64));

	twans->jouwnaw_pin = &as->jouwnaw;

	fow_each_keywist_key(&as->owd_keys, k) {
		unsigned wevew = bkey_i_to_btwee_ptw_v2(k)->v.mem_ptw;

		wet = bch2_key_twiggew_owd(twans, as->btwee_id, wevew, bkey_i_to_s_c(k),
					   BTWEE_TWIGGEW_TWANSACTIONAW);
		if (wet)
			wetuwn wet;
	}

	fow_each_keywist_key(&as->new_keys, k) {
		unsigned wevew = bkey_i_to_btwee_ptw_v2(k)->v.mem_ptw;

		wet = bch2_key_twiggew_new(twans, as->btwee_id, wevew, bkey_i_to_s(k),
					   BTWEE_TWIGGEW_TWANSACTIONAW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void btwee_update_nodes_wwitten(stwuct btwee_update *as)
{
	stwuct bch_fs *c = as->c;
	stwuct btwee *b;
	stwuct btwee_twans *twans = bch2_twans_get(c);
	u64 jouwnaw_seq = 0;
	unsigned i;
	int wet;

	/*
	 * If we'we awweady in an ewwow state, it might be because a btwee node
	 * was nevew wwitten, and we might be twying to fwee that same btwee
	 * node hewe, but it won't have been mawked as awwocated and we'ww see
	 * spuwious disk usage inconsistencies in the twansactionaw pawt bewow
	 * if we don't skip it:
	 */
	wet = bch2_jouwnaw_ewwow(&c->jouwnaw);
	if (wet)
		goto eww;

	/*
	 * Wait fow any in fwight wwites to finish befowe we fwee the owd nodes
	 * on disk:
	 */
	fow (i = 0; i < as->nw_owd_nodes; i++) {
		__we64 seq;

		b = as->owd_nodes[i];

		btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_wead);
		seq = b->data ? b->data->keys.seq : 0;
		six_unwock_wead(&b->c.wock);

		if (seq == as->owd_nodes_seq[i])
			wait_on_bit_io(&b->fwags, BTWEE_NODE_wwite_in_fwight_innew,
				       TASK_UNINTEWWUPTIBWE);
	}

	/*
	 * We did an update to a pawent node whewe the pointews we added pointed
	 * to chiwd nodes that wewen't wwitten yet: now, the chiwd nodes have
	 * been wwitten so we can wwite out the update to the intewiow node.
	 */

	/*
	 * We can't caww into jouwnaw wecwaim hewe: we'd bwock on the jouwnaw
	 * wecwaim wock, but we may need to wewease the open buckets we have
	 * pinned in owdew fow othew btwee updates to make fowwawd pwogwess, and
	 * jouwnaw wecwaim does btwee updates when fwushing bkey_cached entwies,
	 * which may wequiwe awwocations as weww.
	 */
	wet = commit_do(twans, &as->disk_wes, &jouwnaw_seq,
			BCH_WATEWMAWK_wecwaim|
			BCH_TWANS_COMMIT_no_enospc|
			BCH_TWANS_COMMIT_no_check_ww|
			BCH_TWANS_COMMIT_jouwnaw_wecwaim,
			btwee_update_nodes_wwitten_twans(twans, as));
	bch2_twans_unwock(twans);

	bch2_fs_fataw_eww_on(wet && !bch2_jouwnaw_ewwow(&c->jouwnaw), c,
			     "%s(): ewwow %s", __func__, bch2_eww_stw(wet));
eww:
	if (as->b) {

		b = as->b;
		btwee_path_idx_t path_idx = get_unwocked_mut_path(twans,
						as->btwee_id, b->c.wevew, b->key.k.p);
		stwuct btwee_path *path = twans->paths + path_idx;
		/*
		 * @b is the node we did the finaw insewt into:
		 *
		 * On faiwuwe to get a jouwnaw wesewvation, we stiww have to
		 * unbwock the wwite and awwow most of the wwite path to happen
		 * so that shutdown wowks, but the i->jouwnaw_seq mechanism
		 * won't wowk to pwevent the btwee wwite fwom being visibwe (we
		 * didn't get a jouwnaw sequence numbew) - instead
		 * __bch2_btwee_node_wwite() doesn't do the actuaw wwite if
		 * we'we in jouwnaw ewwow state:
		 */

		/*
		 * Ensuwe twansaction is unwocked befowe using
		 * btwee_node_wock_nopath() (the use of which is awways suspect,
		 * we need to wowk on wemoving this in the futuwe)
		 *
		 * It shouwd be, but get_unwocked_mut_path() -> bch2_path_get()
		 * cawws bch2_path_upgwade(), befowe we caww path_make_mut(), so
		 * we may wawewy end up with a wocked path besides the one we
		 * have hewe:
		 */
		bch2_twans_unwock(twans);
		btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_intent);
		mawk_btwee_node_wocked(twans, path, b->c.wevew, BTWEE_NODE_INTENT_WOCKED);
		path->w[b->c.wevew].wock_seq = six_wock_seq(&b->c.wock);
		path->w[b->c.wevew].b = b;

		bch2_btwee_node_wock_wwite_nofaiw(twans, path, &b->c);

		mutex_wock(&c->btwee_intewiow_update_wock);

		wist_dew(&as->wwite_bwocked_wist);
		if (wist_empty(&b->wwite_bwocked))
			cweaw_btwee_node_wwite_bwocked(b);

		/*
		 * Node might have been fweed, wecheck undew
		 * btwee_intewiow_update_wock:
		 */
		if (as->b == b) {
			BUG_ON(!b->c.wevew);
			BUG_ON(!btwee_node_diwty(b));

			if (!wet) {
				stwuct bset *wast = btwee_bset_wast(b);

				wast->jouwnaw_seq = cpu_to_we64(
							     max(jouwnaw_seq,
								 we64_to_cpu(wast->jouwnaw_seq)));

				bch2_btwee_add_jouwnaw_pin(c, b, jouwnaw_seq);
			} ewse {
				/*
				 * If we didn't get a jouwnaw sequence numbew we
				 * can't wwite this btwee node, because wecovewy
				 * won't know to ignowe this wwite:
				 */
				set_btwee_node_nevew_wwite(b);
			}
		}

		mutex_unwock(&c->btwee_intewiow_update_wock);

		mawk_btwee_node_wocked_noweset(path, b->c.wevew, BTWEE_NODE_INTENT_WOCKED);
		six_unwock_wwite(&b->c.wock);

		btwee_node_wwite_if_need(c, b, SIX_WOCK_intent);
		btwee_node_unwock(twans, path, b->c.wevew);
		bch2_path_put(twans, path_idx, twue);
	}

	bch2_jouwnaw_pin_dwop(&c->jouwnaw, &as->jouwnaw);

	mutex_wock(&c->btwee_intewiow_update_wock);
	fow (i = 0; i < as->nw_new_nodes; i++) {
		b = as->new_nodes[i];

		BUG_ON(b->wiww_make_weachabwe != (unsigned wong) as);
		b->wiww_make_weachabwe = 0;
		cweaw_btwee_node_wiww_make_weachabwe(b);
	}
	mutex_unwock(&c->btwee_intewiow_update_wock);

	fow (i = 0; i < as->nw_new_nodes; i++) {
		b = as->new_nodes[i];

		btwee_node_wock_nopath_nofaiw(twans, &b->c, SIX_WOCK_wead);
		btwee_node_wwite_if_need(c, b, SIX_WOCK_wead);
		six_unwock_wead(&b->c.wock);
	}

	fow (i = 0; i < as->nw_open_buckets; i++)
		bch2_open_bucket_put(c, c->open_buckets + as->open_buckets[i]);

	bch2_btwee_update_fwee(as, twans);
	bch2_twans_put(twans);
}

static void btwee_intewiow_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bch_fs *c =
		containew_of(wowk, stwuct bch_fs, btwee_intewiow_update_wowk);
	stwuct btwee_update *as;

	whiwe (1) {
		mutex_wock(&c->btwee_intewiow_update_wock);
		as = wist_fiwst_entwy_ow_nuww(&c->btwee_intewiow_updates_unwwitten,
					      stwuct btwee_update, unwwitten_wist);
		if (as && !as->nodes_wwitten)
			as = NUWW;
		mutex_unwock(&c->btwee_intewiow_update_wock);

		if (!as)
			bweak;

		btwee_update_nodes_wwitten(as);
	}
}

static CWOSUWE_CAWWBACK(btwee_update_set_nodes_wwitten)
{
	cwosuwe_type(as, stwuct btwee_update, cw);
	stwuct bch_fs *c = as->c;

	mutex_wock(&c->btwee_intewiow_update_wock);
	as->nodes_wwitten = twue;
	mutex_unwock(&c->btwee_intewiow_update_wock);

	queue_wowk(c->btwee_intewiow_update_wowkew, &c->btwee_intewiow_update_wowk);
}

/*
 * We'we updating @b with pointews to nodes that haven't finished wwiting yet:
 * bwock @b fwom being wwitten untiw @as compwetes
 */
static void btwee_update_updated_node(stwuct btwee_update *as, stwuct btwee *b)
{
	stwuct bch_fs *c = as->c;

	mutex_wock(&c->btwee_intewiow_update_wock);
	wist_add_taiw(&as->unwwitten_wist, &c->btwee_intewiow_updates_unwwitten);

	BUG_ON(as->mode != BTWEE_INTEWIOW_NO_UPDATE);
	BUG_ON(!btwee_node_diwty(b));
	BUG_ON(!b->c.wevew);

	as->mode	= BTWEE_INTEWIOW_UPDATING_NODE;
	as->b		= b;

	set_btwee_node_wwite_bwocked(b);
	wist_add(&as->wwite_bwocked_wist, &b->wwite_bwocked);

	mutex_unwock(&c->btwee_intewiow_update_wock);
}

static int bch2_update_wepawent_jouwnaw_pin_fwush(stwuct jouwnaw *j,
				stwuct jouwnaw_entwy_pin *_pin, u64 seq)
{
	wetuwn 0;
}

static void btwee_update_wepawent(stwuct btwee_update *as,
				  stwuct btwee_update *chiwd)
{
	stwuct bch_fs *c = as->c;

	wockdep_assewt_hewd(&c->btwee_intewiow_update_wock);

	chiwd->b = NUWW;
	chiwd->mode = BTWEE_INTEWIOW_UPDATING_AS;

	bch2_jouwnaw_pin_copy(&c->jouwnaw, &as->jouwnaw, &chiwd->jouwnaw,
			      bch2_update_wepawent_jouwnaw_pin_fwush);
}

static void btwee_update_updated_woot(stwuct btwee_update *as, stwuct btwee *b)
{
	stwuct bkey_i *insewt = &b->key;
	stwuct bch_fs *c = as->c;

	BUG_ON(as->mode != BTWEE_INTEWIOW_NO_UPDATE);

	BUG_ON(as->jouwnaw_u64s + jset_u64s(insewt->k.u64s) >
	       AWWAY_SIZE(as->jouwnaw_entwies));

	as->jouwnaw_u64s +=
		jouwnaw_entwy_set((void *) &as->jouwnaw_entwies[as->jouwnaw_u64s],
				  BCH_JSET_ENTWY_btwee_woot,
				  b->c.btwee_id, b->c.wevew,
				  insewt, insewt->k.u64s);

	mutex_wock(&c->btwee_intewiow_update_wock);
	wist_add_taiw(&as->unwwitten_wist, &c->btwee_intewiow_updates_unwwitten);

	as->mode	= BTWEE_INTEWIOW_UPDATING_WOOT;
	mutex_unwock(&c->btwee_intewiow_update_wock);
}

/*
 * bch2_btwee_update_add_new_node:
 *
 * This causes @as to wait on @b to be wwitten, befowe it gets to
 * bch2_btwee_update_nodes_wwitten
 *
 * Additionawwy, it sets b->wiww_make_weachabwe to pwevent any additionaw wwites
 * to @b fwom happening besides the fiwst untiw @b is weachabwe on disk
 *
 * And it adds @b to the wist of @as's new nodes, so that we can update sectow
 * counts in bch2_btwee_update_nodes_wwitten:
 */
static void bch2_btwee_update_add_new_node(stwuct btwee_update *as, stwuct btwee *b)
{
	stwuct bch_fs *c = as->c;

	cwosuwe_get(&as->cw);

	mutex_wock(&c->btwee_intewiow_update_wock);
	BUG_ON(as->nw_new_nodes >= AWWAY_SIZE(as->new_nodes));
	BUG_ON(b->wiww_make_weachabwe);

	as->new_nodes[as->nw_new_nodes++] = b;
	b->wiww_make_weachabwe = 1UW|(unsigned wong) as;
	set_btwee_node_wiww_make_weachabwe(b);

	mutex_unwock(&c->btwee_intewiow_update_wock);

	btwee_update_add_key(as, &as->new_keys, b);

	if (b->key.k.type == KEY_TYPE_btwee_ptw_v2) {
		unsigned bytes = vstwuct_end(&b->data->keys) - (void *) b->data;
		unsigned sectows = wound_up(bytes, bwock_bytes(c)) >> 9;

		bkey_i_to_btwee_ptw_v2(&b->key)->v.sectows_wwitten =
			cpu_to_we16(sectows);
	}
}

/*
 * wetuwns twue if @b was a new node
 */
static void btwee_update_dwop_new_node(stwuct bch_fs *c, stwuct btwee *b)
{
	stwuct btwee_update *as;
	unsigned wong v;
	unsigned i;

	mutex_wock(&c->btwee_intewiow_update_wock);
	/*
	 * When b->wiww_make_weachabwe != 0, it owns a wef on as->cw that's
	 * dwopped when it gets wwitten by bch2_btwee_compwete_wwite - the
	 * xchg() is fow synchwonization with bch2_btwee_compwete_wwite:
	 */
	v = xchg(&b->wiww_make_weachabwe, 0);
	cweaw_btwee_node_wiww_make_weachabwe(b);
	as = (stwuct btwee_update *) (v & ~1UW);

	if (!as) {
		mutex_unwock(&c->btwee_intewiow_update_wock);
		wetuwn;
	}

	fow (i = 0; i < as->nw_new_nodes; i++)
		if (as->new_nodes[i] == b)
			goto found;

	BUG();
found:
	awway_wemove_item(as->new_nodes, as->nw_new_nodes, i);
	mutex_unwock(&c->btwee_intewiow_update_wock);

	if (v & 1)
		cwosuwe_put(&as->cw);
}

static void bch2_btwee_update_get_open_buckets(stwuct btwee_update *as, stwuct btwee *b)
{
	whiwe (b->ob.nw)
		as->open_buckets[as->nw_open_buckets++] =
			b->ob.v[--b->ob.nw];
}

static int bch2_btwee_update_wiww_fwee_node_jouwnaw_pin_fwush(stwuct jouwnaw *j,
				stwuct jouwnaw_entwy_pin *_pin, u64 seq)
{
	wetuwn 0;
}

/*
 * @b is being spwit/wewwitten: it may have pointews to not-yet-wwitten btwee
 * nodes and thus outstanding btwee_updates - wediwect @b's
 * btwee_updates to point to this btwee_update:
 */
static void bch2_btwee_intewiow_update_wiww_fwee_node(stwuct btwee_update *as,
						      stwuct btwee *b)
{
	stwuct bch_fs *c = as->c;
	stwuct btwee_update *p, *n;
	stwuct btwee_wwite *w;

	set_btwee_node_dying(b);

	if (btwee_node_fake(b))
		wetuwn;

	mutex_wock(&c->btwee_intewiow_update_wock);

	/*
	 * Does this node have any btwee_update opewations pweventing
	 * it fwom being wwitten?
	 *
	 * If so, wediwect them to point to this btwee_update: we can
	 * wwite out ouw new nodes, but we won't make them visibwe untiw those
	 * opewations compwete
	 */
	wist_fow_each_entwy_safe(p, n, &b->wwite_bwocked, wwite_bwocked_wist) {
		wist_dew_init(&p->wwite_bwocked_wist);
		btwee_update_wepawent(as, p);

		/*
		 * fow fwush_hewd_btwee_wwites() waiting on updates to fwush ow
		 * nodes to be wwiteabwe:
		 */
		cwosuwe_wake_up(&c->btwee_intewiow_update_wait);
	}

	cweaw_btwee_node_diwty_acct(c, b);
	cweaw_btwee_node_need_wwite(b);
	cweaw_btwee_node_wwite_bwocked(b);

	/*
	 * Does this node have unwwitten data that has a pin on the jouwnaw?
	 *
	 * If so, twansfew that pin to the btwee_update opewation -
	 * note that if we'we fweeing muwtipwe nodes, we onwy need to keep the
	 * owdest pin of any of the nodes we'we fweeing. We'ww wewease the pin
	 * when the new nodes awe pewsistent and weachabwe on disk:
	 */
	w = btwee_cuwwent_wwite(b);
	bch2_jouwnaw_pin_copy(&c->jouwnaw, &as->jouwnaw, &w->jouwnaw,
			      bch2_btwee_update_wiww_fwee_node_jouwnaw_pin_fwush);
	bch2_jouwnaw_pin_dwop(&c->jouwnaw, &w->jouwnaw);

	w = btwee_pwev_wwite(b);
	bch2_jouwnaw_pin_copy(&c->jouwnaw, &as->jouwnaw, &w->jouwnaw,
			      bch2_btwee_update_wiww_fwee_node_jouwnaw_pin_fwush);
	bch2_jouwnaw_pin_dwop(&c->jouwnaw, &w->jouwnaw);

	mutex_unwock(&c->btwee_intewiow_update_wock);

	/*
	 * Is this a node that isn't weachabwe on disk yet?
	 *
	 * Nodes that awen't weachabwe yet have wwites bwocked untiw they'we
	 * weachabwe - now that we've cancewwed any pending wwites and moved
	 * things waiting on that wwite to wait on this update, we can dwop this
	 * node fwom the wist of nodes that the othew update is making
	 * weachabwe, pwiow to fweeing it:
	 */
	btwee_update_dwop_new_node(c, b);

	btwee_update_add_key(as, &as->owd_keys, b);

	as->owd_nodes[as->nw_owd_nodes] = b;
	as->owd_nodes_seq[as->nw_owd_nodes] = b->data->keys.seq;
	as->nw_owd_nodes++;
}

static void bch2_btwee_update_done(stwuct btwee_update *as, stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = as->c;
	u64 stawt_time = as->stawt_time;

	BUG_ON(as->mode == BTWEE_INTEWIOW_NO_UPDATE);

	if (as->took_gc_wock)
		up_wead(&as->c->gc_wock);
	as->took_gc_wock = fawse;

	bch2_btwee_wesewve_put(as, twans);

	continue_at(&as->cw, btwee_update_set_nodes_wwitten,
		    as->c->btwee_intewiow_update_wowkew);

	bch2_time_stats_update(&c->times[BCH_TIME_btwee_intewiow_update_fowegwound],
			       stawt_time);
}

static stwuct btwee_update *
bch2_btwee_update_stawt(stwuct btwee_twans *twans, stwuct btwee_path *path,
			unsigned wevew, boow spwit, unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_update *as;
	u64 stawt_time = wocaw_cwock();
	int disk_wes_fwags = (fwags & BCH_TWANS_COMMIT_no_enospc)
		? BCH_DISK_WESEWVATION_NOFAIW : 0;
	unsigned nw_nodes[2] = { 0, 0 };
	unsigned update_wevew = wevew;
	enum bch_watewmawk watewmawk = fwags & BCH_WATEWMAWK_MASK;
	int wet = 0;
	u32 westawt_count = twans->westawt_count;

	BUG_ON(!path->shouwd_be_wocked);

	if (watewmawk == BCH_WATEWMAWK_copygc)
		watewmawk = BCH_WATEWMAWK_btwee_copygc;
	if (watewmawk < BCH_WATEWMAWK_btwee)
		watewmawk = BCH_WATEWMAWK_btwee;

	fwags &= ~BCH_WATEWMAWK_MASK;
	fwags |= watewmawk;

	if (!(fwags & BCH_TWANS_COMMIT_jouwnaw_wecwaim) &&
	    watewmawk < c->jouwnaw.watewmawk) {
		stwuct jouwnaw_wes wes = { 0 };

		wet = dwop_wocks_do(twans,
			bch2_jouwnaw_wes_get(&c->jouwnaw, &wes, 1,
					     watewmawk|JOUWNAW_WES_GET_CHECK));
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	whiwe (1) {
		nw_nodes[!!update_wevew] += 1 + spwit;
		update_wevew++;

		wet = bch2_btwee_path_upgwade(twans, path, update_wevew + 1);
		if (wet)
			wetuwn EWW_PTW(wet);

		if (!btwee_path_node(path, update_wevew)) {
			/* Awwocating new woot? */
			nw_nodes[1] += spwit;
			update_wevew = BTWEE_MAX_DEPTH;
			bweak;
		}

		/*
		 * Awways check fow space fow two keys, even if we won't have to
		 * spwit at pwiow wevew - it might have been a mewge instead:
		 */
		if (bch2_btwee_node_insewt_fits(path->w[update_wevew].b,
						BKEY_BTWEE_PTW_U64s_MAX * 2))
			bweak;

		spwit = path->w[update_wevew].b->nw.wive_u64s > BTWEE_SPWIT_THWESHOWD(c);
	}

	if (!down_wead_twywock(&c->gc_wock)) {
		wet = dwop_wocks_do(twans, (down_wead(&c->gc_wock), 0));
		if (wet) {
			up_wead(&c->gc_wock);
			wetuwn EWW_PTW(wet);
		}
	}

	as = mempoow_awwoc(&c->btwee_intewiow_update_poow, GFP_NOFS);
	memset(as, 0, sizeof(*as));
	cwosuwe_init(&as->cw, NUWW);
	as->c		= c;
	as->stawt_time	= stawt_time;
	as->mode	= BTWEE_INTEWIOW_NO_UPDATE;
	as->took_gc_wock = twue;
	as->btwee_id	= path->btwee_id;
	as->update_wevew = update_wevew;
	INIT_WIST_HEAD(&as->wist);
	INIT_WIST_HEAD(&as->unwwitten_wist);
	INIT_WIST_HEAD(&as->wwite_bwocked_wist);
	bch2_keywist_init(&as->owd_keys, as->_owd_keys);
	bch2_keywist_init(&as->new_keys, as->_new_keys);
	bch2_keywist_init(&as->pawent_keys, as->inwine_keys);

	mutex_wock(&c->btwee_intewiow_update_wock);
	wist_add_taiw(&as->wist, &c->btwee_intewiow_update_wist);
	mutex_unwock(&c->btwee_intewiow_update_wock);

	/*
	 * We don't want to awwocate if we'we in an ewwow state, that can cause
	 * deadwock on emewgency shutdown due to open buckets getting stuck in
	 * the btwee_wesewve_cache aftew awwocatow shutdown has cweawed it out.
	 * This check needs to come aftew adding us to the btwee_intewiow_update
	 * wist but befowe cawwing bch2_btwee_wesewve_get, to synchwonize with
	 * __bch2_fs_wead_onwy().
	 */
	wet = bch2_jouwnaw_ewwow(&c->jouwnaw);
	if (wet)
		goto eww;

	wet = bch2_disk_wesewvation_get(c, &as->disk_wes,
			(nw_nodes[0] + nw_nodes[1]) * btwee_sectows(c),
			c->opts.metadata_wepwicas,
			disk_wes_fwags);
	if (wet)
		goto eww;

	wet = bch2_btwee_wesewve_get(twans, as, nw_nodes, fwags, NUWW);
	if (bch2_eww_matches(wet, ENOSPC) ||
	    bch2_eww_matches(wet, ENOMEM)) {
		stwuct cwosuwe cw;

		/*
		 * XXX: this shouwd pwobabwy be a sepawate BTWEE_INSEWT_NONBWOCK
		 * fwag
		 */
		if (bch2_eww_matches(wet, ENOSPC) &&
		    (fwags & BCH_TWANS_COMMIT_jouwnaw_wecwaim) &&
		    watewmawk != BCH_WATEWMAWK_wecwaim) {
			wet = -BCH_EWW_jouwnaw_wecwaim_wouwd_deadwock;
			goto eww;
		}

		cwosuwe_init_stack(&cw);

		do {
			wet = bch2_btwee_wesewve_get(twans, as, nw_nodes, fwags, &cw);

			bch2_twans_unwock(twans);
			cwosuwe_sync(&cw);
		} whiwe (bch2_eww_matches(wet, BCH_EWW_opewation_bwocked));
	}

	if (wet) {
		twace_and_count(c, btwee_wesewve_get_faiw, twans->fn,
				_WET_IP_, nw_nodes[0] + nw_nodes[1], wet);
		goto eww;
	}

	wet = bch2_twans_wewock(twans);
	if (wet)
		goto eww;

	bch2_twans_vewify_not_westawted(twans, westawt_count);
	wetuwn as;
eww:
	bch2_btwee_update_fwee(as, twans);
	if (!bch2_eww_matches(wet, ENOSPC) &&
	    !bch2_eww_matches(wet, EWOFS))
		bch_eww_fn_watewimited(c, wet);
	wetuwn EWW_PTW(wet);
}

/* Btwee woot updates: */

static void bch2_btwee_set_woot_inmem(stwuct bch_fs *c, stwuct btwee *b)
{
	/* Woot nodes cannot be weaped */
	mutex_wock(&c->btwee_cache.wock);
	wist_dew_init(&b->wist);
	mutex_unwock(&c->btwee_cache.wock);

	mutex_wock(&c->btwee_woot_wock);
	BUG_ON(btwee_node_woot(c, b) &&
	       (b->c.wevew < btwee_node_woot(c, b)->c.wevew ||
		!btwee_node_dying(btwee_node_woot(c, b))));

	bch2_btwee_id_woot(c, b->c.btwee_id)->b = b;
	mutex_unwock(&c->btwee_woot_wock);

	bch2_wecawc_btwee_wesewve(c);
}

static void bch2_btwee_set_woot(stwuct btwee_update *as,
				stwuct btwee_twans *twans,
				stwuct btwee_path *path,
				stwuct btwee *b)
{
	stwuct bch_fs *c = as->c;
	stwuct btwee *owd;

	twace_and_count(c, btwee_node_set_woot, twans, b);

	owd = btwee_node_woot(c, b);

	/*
	 * Ensuwe no one is using the owd woot whiwe we switch to the
	 * new woot:
	 */
	bch2_btwee_node_wock_wwite_nofaiw(twans, path, &owd->c);

	bch2_btwee_set_woot_inmem(c, b);

	btwee_update_updated_woot(as, b);

	/*
	 * Unwock owd woot aftew new woot is visibwe:
	 *
	 * The new woot isn't pewsistent, but that's ok: we stiww have
	 * an intent wock on the new woot, and any updates that wouwd
	 * depend on the new woot wouwd have to update the new woot.
	 */
	bch2_btwee_node_unwock_wwite(twans, path, owd);
}

/* Intewiow node updates: */

static void bch2_insewt_fixup_btwee_ptw(stwuct btwee_update *as,
					stwuct btwee_twans *twans,
					stwuct btwee_path *path,
					stwuct btwee *b,
					stwuct btwee_node_itew *node_itew,
					stwuct bkey_i *insewt)
{
	stwuct bch_fs *c = as->c;
	stwuct bkey_packed *k;
	stwuct pwintbuf buf = PWINTBUF;
	unsigned wong owd, new, v;

	BUG_ON(insewt->k.type == KEY_TYPE_btwee_ptw_v2 &&
	       !btwee_ptw_sectows_wwitten(insewt));

	if (unwikewy(!test_bit(JOUWNAW_WEPWAY_DONE, &c->jouwnaw.fwags)))
		bch2_jouwnaw_key_ovewwwitten(c, b->c.btwee_id, b->c.wevew, insewt->k.p);

	if (bch2_bkey_invawid(c, bkey_i_to_s_c(insewt),
			      btwee_node_type(b), WWITE, &buf) ?:
	    bch2_bkey_in_btwee_node(c, b, bkey_i_to_s_c(insewt), &buf)) {
		pwintbuf_weset(&buf);
		pwt_pwintf(&buf, "insewting invawid bkey\n  ");
		bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(insewt));
		pwt_pwintf(&buf, "\n  ");
		bch2_bkey_invawid(c, bkey_i_to_s_c(insewt),
				  btwee_node_type(b), WWITE, &buf);
		bch2_bkey_in_btwee_node(c, b, bkey_i_to_s_c(insewt), &buf);

		bch2_fs_inconsistent(c, "%s", buf.buf);
		dump_stack();
	}

	BUG_ON(as->jouwnaw_u64s + jset_u64s(insewt->k.u64s) >
	       AWWAY_SIZE(as->jouwnaw_entwies));

	as->jouwnaw_u64s +=
		jouwnaw_entwy_set((void *) &as->jouwnaw_entwies[as->jouwnaw_u64s],
				  BCH_JSET_ENTWY_btwee_keys,
				  b->c.btwee_id, b->c.wevew,
				  insewt, insewt->k.u64s);

	whiwe ((k = bch2_btwee_node_itew_peek_aww(node_itew, b)) &&
	       bkey_itew_pos_cmp(b, k, &insewt->k.p) < 0)
		bch2_btwee_node_itew_advance(node_itew, b);

	bch2_btwee_bset_insewt_key(twans, path, b, node_itew, insewt);
	set_btwee_node_diwty_acct(c, b);

	v = WEAD_ONCE(b->fwags);
	do {
		owd = new = v;

		new &= ~BTWEE_WWITE_TYPE_MASK;
		new |= BTWEE_WWITE_intewiow;
		new |= 1 << BTWEE_NODE_need_wwite;
	} whiwe ((v = cmpxchg(&b->fwags, owd, new)) != owd);

	pwintbuf_exit(&buf);
}

static void
__bch2_btwee_insewt_keys_intewiow(stwuct btwee_update *as,
				  stwuct btwee_twans *twans,
				  stwuct btwee_path *path,
				  stwuct btwee *b,
				  stwuct btwee_node_itew node_itew,
				  stwuct keywist *keys)
{
	stwuct bkey_i *insewt = bch2_keywist_fwont(keys);
	stwuct bkey_packed *k;

	BUG_ON(btwee_node_type(b) != BKEY_TYPE_btwee);

	whiwe ((k = bch2_btwee_node_itew_pwev_aww(&node_itew, b)) &&
	       (bkey_cmp_weft_packed(b, k, &insewt->k.p) >= 0))
		;

	whiwe (!bch2_keywist_empty(keys)) {
		insewt = bch2_keywist_fwont(keys);

		if (bpos_gt(insewt->k.p, b->key.k.p))
			bweak;

		bch2_insewt_fixup_btwee_ptw(as, twans, path, b, &node_itew, insewt);
		bch2_keywist_pop_fwont(keys);
	}
}

/*
 * Move keys fwom n1 (owiginaw wepwacement node, now wowew node) to n2 (highew
 * node)
 */
static void __btwee_spwit_node(stwuct btwee_update *as,
			       stwuct btwee_twans *twans,
			       stwuct btwee *b,
			       stwuct btwee *n[2])
{
	stwuct bkey_packed *k;
	stwuct bpos n1_pos = POS_MIN;
	stwuct btwee_node_itew itew;
	stwuct bset *bsets[2];
	stwuct bkey_fowmat_state fowmat[2];
	stwuct bkey_packed *out[2];
	stwuct bkey uk;
	unsigned u64s, n1_u64s = (b->nw.wive_u64s * 3) / 5;
	stwuct { unsigned nw_keys, vaw_u64s; } nw_keys[2];
	int i;

	memset(&nw_keys, 0, sizeof(nw_keys));

	fow (i = 0; i < 2; i++) {
		BUG_ON(n[i]->nsets != 1);

		bsets[i] = btwee_bset_fiwst(n[i]);
		out[i] = bsets[i]->stawt;

		SET_BTWEE_NODE_SEQ(n[i]->data, BTWEE_NODE_SEQ(b->data) + 1);
		bch2_bkey_fowmat_init(&fowmat[i]);
	}

	u64s = 0;
	fow_each_btwee_node_key(b, k, &itew) {
		if (bkey_deweted(k))
			continue;

		i = u64s >= n1_u64s;
		u64s += k->u64s;
		uk = bkey_unpack_key(b, k);
		if (!i)
			n1_pos = uk.p;
		bch2_bkey_fowmat_add_key(&fowmat[i], &uk);

		nw_keys[i].nw_keys++;
		nw_keys[i].vaw_u64s += bkeyp_vaw_u64s(&b->fowmat, k);
	}

	btwee_set_min(n[0], b->data->min_key);
	btwee_set_max(n[0], n1_pos);
	btwee_set_min(n[1], bpos_successow(n1_pos));
	btwee_set_max(n[1], b->data->max_key);

	fow (i = 0; i < 2; i++) {
		bch2_bkey_fowmat_add_pos(&fowmat[i], n[i]->data->min_key);
		bch2_bkey_fowmat_add_pos(&fowmat[i], n[i]->data->max_key);

		n[i]->data->fowmat = bch2_bkey_fowmat_done(&fowmat[i]);

		unsigned u64s = nw_keys[i].nw_keys * n[i]->data->fowmat.key_u64s +
			nw_keys[i].vaw_u64s;
		if (__vstwuct_bytes(stwuct btwee_node, u64s) > btwee_buf_bytes(b))
			n[i]->data->fowmat = b->fowmat;

		btwee_node_set_fowmat(n[i], n[i]->data->fowmat);
	}

	u64s = 0;
	fow_each_btwee_node_key(b, k, &itew) {
		if (bkey_deweted(k))
			continue;

		i = u64s >= n1_u64s;
		u64s += k->u64s;

		if (bch2_bkey_twansfowm(&n[i]->fowmat, out[i], bkey_packed(k)
					? &b->fowmat: &bch2_bkey_fowmat_cuwwent, k))
			out[i]->fowmat = KEY_FOWMAT_WOCAW_BTWEE;
		ewse
			bch2_bkey_unpack(b, (void *) out[i], k);

		out[i]->needs_whiteout = fawse;

		btwee_keys_account_key_add(&n[i]->nw, 0, out[i]);
		out[i] = bkey_p_next(out[i]);
	}

	fow (i = 0; i < 2; i++) {
		bsets[i]->u64s = cpu_to_we16((u64 *) out[i] - bsets[i]->_data);

		BUG_ON(!bsets[i]->u64s);

		set_btwee_bset_end(n[i], n[i]->set);

		btwee_node_weset_sib_u64s(n[i]);

		bch2_vewify_btwee_nw_keys(n[i]);

		if (b->c.wevew)
			btwee_node_intewiow_vewify(as->c, n[i]);
	}
}

/*
 * Fow updates to intewiow nodes, we've got to do the insewt befowe we spwit
 * because the stuff we'we insewting has to be insewted atomicawwy. Post spwit,
 * the keys might have to go in diffewent nodes and the spwit wouwd no wongew be
 * atomic.
 *
 * Wowse, if the insewt is fwom btwee node coawescing, if we do the insewt aftew
 * we do the spwit (and pick the pivot) - the pivot we pick might be between
 * nodes that wewe coawesced, and thus in the middwe of a chiwd node post
 * coawescing:
 */
static void btwee_spwit_insewt_keys(stwuct btwee_update *as,
				    stwuct btwee_twans *twans,
				    btwee_path_idx_t path_idx,
				    stwuct btwee *b,
				    stwuct keywist *keys)
{
	stwuct btwee_path *path = twans->paths + path_idx;

	if (!bch2_keywist_empty(keys) &&
	    bpos_we(bch2_keywist_fwont(keys)->k.p, b->data->max_key)) {
		stwuct btwee_node_itew node_itew;

		bch2_btwee_node_itew_init(&node_itew, b, &bch2_keywist_fwont(keys)->k.p);

		__bch2_btwee_insewt_keys_intewiow(as, twans, path, b, node_itew, keys);

		btwee_node_intewiow_vewify(as->c, b);
	}
}

static int btwee_spwit(stwuct btwee_update *as, stwuct btwee_twans *twans,
		       btwee_path_idx_t path, stwuct btwee *b,
		       stwuct keywist *keys, unsigned fwags)
{
	stwuct bch_fs *c = as->c;
	stwuct btwee *pawent = btwee_node_pawent(twans->paths + path, b);
	stwuct btwee *n1, *n2 = NUWW, *n3 = NUWW;
	btwee_path_idx_t path1 = 0, path2 = 0;
	u64 stawt_time = wocaw_cwock();
	int wet = 0;

	BUG_ON(!pawent && (b != btwee_node_woot(c, b)));
	BUG_ON(pawent && !btwee_node_intent_wocked(twans->paths + path, b->c.wevew + 1));

	bch2_btwee_intewiow_update_wiww_fwee_node(as, b);

	if (b->nw.wive_u64s > BTWEE_SPWIT_THWESHOWD(c)) {
		stwuct btwee *n[2];

		twace_and_count(c, btwee_node_spwit, twans, b);

		n[0] = n1 = bch2_btwee_node_awwoc(as, twans, b->c.wevew);
		n[1] = n2 = bch2_btwee_node_awwoc(as, twans, b->c.wevew);

		__btwee_spwit_node(as, twans, b, n);

		if (keys) {
			btwee_spwit_insewt_keys(as, twans, path, n1, keys);
			btwee_spwit_insewt_keys(as, twans, path, n2, keys);
			BUG_ON(!bch2_keywist_empty(keys));
		}

		bch2_btwee_buiwd_aux_twees(n2);
		bch2_btwee_buiwd_aux_twees(n1);

		bch2_btwee_update_add_new_node(as, n1);
		bch2_btwee_update_add_new_node(as, n2);
		six_unwock_wwite(&n2->c.wock);
		six_unwock_wwite(&n1->c.wock);

		path1 = get_unwocked_mut_path(twans, as->btwee_id, n1->c.wevew, n1->key.k.p);
		six_wock_incwement(&n1->c.wock, SIX_WOCK_intent);
		mawk_btwee_node_wocked(twans, twans->paths + path1, n1->c.wevew, BTWEE_NODE_INTENT_WOCKED);
		bch2_btwee_path_wevew_init(twans, twans->paths + path1, n1);

		path2 = get_unwocked_mut_path(twans, as->btwee_id, n2->c.wevew, n2->key.k.p);
		six_wock_incwement(&n2->c.wock, SIX_WOCK_intent);
		mawk_btwee_node_wocked(twans, twans->paths + path2, n2->c.wevew, BTWEE_NODE_INTENT_WOCKED);
		bch2_btwee_path_wevew_init(twans, twans->paths + path2, n2);

		/*
		 * Note that on wecuwsive pawent_keys == keys, so we
		 * can't stawt adding new keys to pawent_keys befowe emptying it
		 * out (which we did with btwee_spwit_insewt_keys() above)
		 */
		bch2_keywist_add(&as->pawent_keys, &n1->key);
		bch2_keywist_add(&as->pawent_keys, &n2->key);

		if (!pawent) {
			/* Depth incweases, make a new woot */
			n3 = __btwee_woot_awwoc(as, twans, b->c.wevew + 1);

			bch2_btwee_update_add_new_node(as, n3);
			six_unwock_wwite(&n3->c.wock);

			twans->paths[path2].wocks_want++;
			BUG_ON(btwee_node_wocked(twans->paths + path2, n3->c.wevew));
			six_wock_incwement(&n3->c.wock, SIX_WOCK_intent);
			mawk_btwee_node_wocked(twans, twans->paths + path2, n3->c.wevew, BTWEE_NODE_INTENT_WOCKED);
			bch2_btwee_path_wevew_init(twans, twans->paths + path2, n3);

			n3->sib_u64s[0] = U16_MAX;
			n3->sib_u64s[1] = U16_MAX;

			btwee_spwit_insewt_keys(as, twans, path, n3, &as->pawent_keys);
		}
	} ewse {
		twace_and_count(c, btwee_node_compact, twans, b);

		n1 = bch2_btwee_node_awwoc_wepwacement(as, twans, b);

		if (keys) {
			btwee_spwit_insewt_keys(as, twans, path, n1, keys);
			BUG_ON(!bch2_keywist_empty(keys));
		}

		bch2_btwee_buiwd_aux_twees(n1);
		bch2_btwee_update_add_new_node(as, n1);
		six_unwock_wwite(&n1->c.wock);

		path1 = get_unwocked_mut_path(twans, as->btwee_id, n1->c.wevew, n1->key.k.p);
		six_wock_incwement(&n1->c.wock, SIX_WOCK_intent);
		mawk_btwee_node_wocked(twans, twans->paths + path1, n1->c.wevew, BTWEE_NODE_INTENT_WOCKED);
		bch2_btwee_path_wevew_init(twans, twans->paths + path1, n1);

		if (pawent)
			bch2_keywist_add(&as->pawent_keys, &n1->key);
	}

	/* New nodes aww wwitten, now make them visibwe: */

	if (pawent) {
		/* Spwit a non woot node */
		wet = bch2_btwee_insewt_node(as, twans, path, pawent, &as->pawent_keys, fwags);
		if (wet)
			goto eww;
	} ewse if (n3) {
		bch2_btwee_set_woot(as, twans, twans->paths + path, n3);
	} ewse {
		/* Woot fiwwed up but didn't need to be spwit */
		bch2_btwee_set_woot(as, twans, twans->paths + path, n1);
	}

	if (n3) {
		bch2_btwee_update_get_open_buckets(as, n3);
		bch2_btwee_node_wwite(c, n3, SIX_WOCK_intent, 0);
	}
	if (n2) {
		bch2_btwee_update_get_open_buckets(as, n2);
		bch2_btwee_node_wwite(c, n2, SIX_WOCK_intent, 0);
	}
	bch2_btwee_update_get_open_buckets(as, n1);
	bch2_btwee_node_wwite(c, n1, SIX_WOCK_intent, 0);

	/*
	 * The owd node must be fweed (in memowy) _befowe_ unwocking the new
	 * nodes - ewse anothew thwead couwd we-acquiwe a wead wock on the owd
	 * node aftew anothew thwead has wocked and updated the new node, thus
	 * seeing stawe data:
	 */
	bch2_btwee_node_fwee_inmem(twans, twans->paths + path, b);

	if (n3)
		bch2_twans_node_add(twans, twans->paths + path, n3);
	if (n2)
		bch2_twans_node_add(twans, twans->paths + path2, n2);
	bch2_twans_node_add(twans, twans->paths + path1, n1);

	if (n3)
		six_unwock_intent(&n3->c.wock);
	if (n2)
		six_unwock_intent(&n2->c.wock);
	six_unwock_intent(&n1->c.wock);
out:
	if (path2) {
		__bch2_btwee_path_unwock(twans, twans->paths + path2);
		bch2_path_put(twans, path2, twue);
	}
	if (path1) {
		__bch2_btwee_path_unwock(twans, twans->paths + path1);
		bch2_path_put(twans, path1, twue);
	}

	bch2_twans_vewify_wocks(twans);

	bch2_time_stats_update(&c->times[n2
			       ? BCH_TIME_btwee_node_spwit
			       : BCH_TIME_btwee_node_compact],
			       stawt_time);
	wetuwn wet;
eww:
	if (n3)
		bch2_btwee_node_fwee_nevew_used(as, twans, n3);
	if (n2)
		bch2_btwee_node_fwee_nevew_used(as, twans, n2);
	bch2_btwee_node_fwee_nevew_used(as, twans, n1);
	goto out;
}

static void
bch2_btwee_insewt_keys_intewiow(stwuct btwee_update *as,
				stwuct btwee_twans *twans,
				stwuct btwee_path *path,
				stwuct btwee *b,
				stwuct keywist *keys)
{
	stwuct btwee_path *winked;
	unsigned i;

	__bch2_btwee_insewt_keys_intewiow(as, twans, path, b,
					  path->w[b->c.wevew].itew, keys);

	btwee_update_updated_node(as, b);

	twans_fow_each_path_with_node(twans, b, winked, i)
		bch2_btwee_node_itew_peek(&winked->w[b->c.wevew].itew, b);

	bch2_twans_vewify_paths(twans);
}

/**
 * bch2_btwee_insewt_node - insewt bkeys into a given btwee node
 *
 * @as:			btwee_update object
 * @twans:		btwee_twans object
 * @path_idx:		path that points to cuwwent node
 * @b:			node to insewt keys into
 * @keys:		wist of keys to insewt
 * @fwags:		twansaction commit fwags
 *
 * Wetuwns: 0 on success, typicawwy twansaction westawt ewwow on faiwuwe
 *
 * Insewts as many keys as it can into a given btwee node, spwitting it if fuww.
 * If a spwit occuwwed, this function wiww wetuwn eawwy. This can onwy happen
 * fow weaf nodes -- insewts into intewiow nodes have to be atomic.
 */
static int bch2_btwee_insewt_node(stwuct btwee_update *as, stwuct btwee_twans *twans,
				  btwee_path_idx_t path_idx, stwuct btwee *b,
				  stwuct keywist *keys, unsigned fwags)
{
	stwuct bch_fs *c = as->c;
	stwuct btwee_path *path = twans->paths + path_idx;
	int owd_u64s = we16_to_cpu(btwee_bset_wast(b)->u64s);
	int owd_wive_u64s = b->nw.wive_u64s;
	int wive_u64s_added, u64s_added;
	int wet;

	wockdep_assewt_hewd(&c->gc_wock);
	BUG_ON(!btwee_node_intent_wocked(path, b->c.wevew));
	BUG_ON(!b->c.wevew);
	BUG_ON(!as || as->b);
	bch2_vewify_keywist_sowted(keys);

	wet = bch2_btwee_node_wock_wwite(twans, path, &b->c);
	if (wet)
		wetuwn wet;

	bch2_btwee_node_pwep_fow_wwite(twans, path, b);

	if (!bch2_btwee_node_insewt_fits(b, bch2_keywist_u64s(keys))) {
		bch2_btwee_node_unwock_wwite(twans, path, b);
		goto spwit;
	}

	btwee_node_intewiow_vewify(c, b);

	bch2_btwee_insewt_keys_intewiow(as, twans, path, b, keys);

	wive_u64s_added = (int) b->nw.wive_u64s - owd_wive_u64s;
	u64s_added = (int) we16_to_cpu(btwee_bset_wast(b)->u64s) - owd_u64s;

	if (b->sib_u64s[0] != U16_MAX && wive_u64s_added < 0)
		b->sib_u64s[0] = max(0, (int) b->sib_u64s[0] + wive_u64s_added);
	if (b->sib_u64s[1] != U16_MAX && wive_u64s_added < 0)
		b->sib_u64s[1] = max(0, (int) b->sib_u64s[1] + wive_u64s_added);

	if (u64s_added > wive_u64s_added &&
	    bch2_maybe_compact_whiteouts(c, b))
		bch2_twans_node_weinit_itew(twans, b);

	bch2_btwee_node_unwock_wwite(twans, path, b);

	btwee_node_intewiow_vewify(c, b);
	wetuwn 0;
spwit:
	/*
	 * We couwd attempt to avoid the twansaction westawt, by cawwing
	 * bch2_btwee_path_upgwade() and awwocating mowe nodes:
	 */
	if (b->c.wevew >= as->update_wevew) {
		twace_and_count(c, twans_westawt_spwit_wace, twans, _THIS_IP_, b);
		wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_spwit_wace);
	}

	wetuwn btwee_spwit(as, twans, path_idx, b, keys, fwags);
}

int bch2_btwee_spwit_weaf(stwuct btwee_twans *twans,
			  btwee_path_idx_t path,
			  unsigned fwags)
{
	/* btwee_spwit & mewge may both cause paths awway to be weawwocated */

	stwuct btwee *b = path_w(twans->paths + path)->b;
	stwuct btwee_update *as;
	unsigned w;
	int wet = 0;

	as = bch2_btwee_update_stawt(twans, twans->paths + path,
				     twans->paths[path].wevew,
				     twue, fwags);
	if (IS_EWW(as))
		wetuwn PTW_EWW(as);

	wet = btwee_spwit(as, twans, path, b, NUWW, fwags);
	if (wet) {
		bch2_btwee_update_fwee(as, twans);
		wetuwn wet;
	}

	bch2_btwee_update_done(as, twans);

	fow (w = twans->paths[path].wevew + 1;
	     btwee_node_intent_wocked(&twans->paths[path], w) && !wet;
	     w++)
		wet = bch2_fowegwound_maybe_mewge(twans, path, w, fwags);

	wetuwn wet;
}

int __bch2_fowegwound_maybe_mewge(stwuct btwee_twans *twans,
				  btwee_path_idx_t path,
				  unsigned wevew,
				  unsigned fwags,
				  enum btwee_node_sibwing sib)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_update *as;
	stwuct bkey_fowmat_state new_s;
	stwuct bkey_fowmat new_f;
	stwuct bkey_i dewete;
	stwuct btwee *b, *m, *n, *pwev, *next, *pawent;
	stwuct bpos sib_pos;
	size_t sib_u64s;
	enum btwee_id btwee = twans->paths[path].btwee_id;
	btwee_path_idx_t sib_path = 0, new_path = 0;
	u64 stawt_time = wocaw_cwock();
	int wet = 0;

	BUG_ON(!twans->paths[path].shouwd_be_wocked);
	BUG_ON(!btwee_node_wocked(&twans->paths[path], wevew));

	b = twans->paths[path].w[wevew].b;

	if ((sib == btwee_pwev_sib && bpos_eq(b->data->min_key, POS_MIN)) ||
	    (sib == btwee_next_sib && bpos_eq(b->data->max_key, SPOS_MAX))) {
		b->sib_u64s[sib] = U16_MAX;
		wetuwn 0;
	}

	sib_pos = sib == btwee_pwev_sib
		? bpos_pwedecessow(b->data->min_key)
		: bpos_successow(b->data->max_key);

	sib_path = bch2_path_get(twans, btwee, sib_pos,
				 U8_MAX, wevew, BTWEE_ITEW_INTENT, _THIS_IP_);
	wet = bch2_btwee_path_twavewse(twans, sib_path, fawse);
	if (wet)
		goto eww;

	btwee_path_set_shouwd_be_wocked(twans->paths + sib_path);

	m = twans->paths[sib_path].w[wevew].b;

	if (btwee_node_pawent(twans->paths + path, b) !=
	    btwee_node_pawent(twans->paths + sib_path, m)) {
		b->sib_u64s[sib] = U16_MAX;
		goto out;
	}

	if (sib == btwee_pwev_sib) {
		pwev = m;
		next = b;
	} ewse {
		pwev = b;
		next = m;
	}

	if (!bpos_eq(bpos_successow(pwev->data->max_key), next->data->min_key)) {
		stwuct pwintbuf buf1 = PWINTBUF, buf2 = PWINTBUF;

		bch2_bpos_to_text(&buf1, pwev->data->max_key);
		bch2_bpos_to_text(&buf2, next->data->min_key);
		bch_eww(c,
			"%s(): btwee topowogy ewwow:\n"
			"  pwev ends at   %s\n"
			"  next stawts at %s",
			__func__, buf1.buf, buf2.buf);
		pwintbuf_exit(&buf1);
		pwintbuf_exit(&buf2);
		bch2_topowogy_ewwow(c);
		wet = -EIO;
		goto eww;
	}

	bch2_bkey_fowmat_init(&new_s);
	bch2_bkey_fowmat_add_pos(&new_s, pwev->data->min_key);
	__bch2_btwee_cawc_fowmat(&new_s, pwev);
	__bch2_btwee_cawc_fowmat(&new_s, next);
	bch2_bkey_fowmat_add_pos(&new_s, next->data->max_key);
	new_f = bch2_bkey_fowmat_done(&new_s);

	sib_u64s = btwee_node_u64s_with_fowmat(b->nw, &b->fowmat, &new_f) +
		btwee_node_u64s_with_fowmat(m->nw, &m->fowmat, &new_f);

	if (sib_u64s > BTWEE_FOWEGWOUND_MEWGE_HYSTEWESIS(c)) {
		sib_u64s -= BTWEE_FOWEGWOUND_MEWGE_HYSTEWESIS(c);
		sib_u64s /= 2;
		sib_u64s += BTWEE_FOWEGWOUND_MEWGE_HYSTEWESIS(c);
	}

	sib_u64s = min(sib_u64s, btwee_max_u64s(c));
	sib_u64s = min(sib_u64s, (size_t) U16_MAX - 1);
	b->sib_u64s[sib] = sib_u64s;

	if (b->sib_u64s[sib] > c->btwee_fowegwound_mewge_thweshowd)
		goto out;

	pawent = btwee_node_pawent(twans->paths + path, b);
	as = bch2_btwee_update_stawt(twans, twans->paths + path, wevew, fawse,
				     BCH_TWANS_COMMIT_no_enospc|fwags);
	wet = PTW_EWW_OW_ZEWO(as);
	if (wet)
		goto eww;

	twace_and_count(c, btwee_node_mewge, twans, b);

	bch2_btwee_intewiow_update_wiww_fwee_node(as, b);
	bch2_btwee_intewiow_update_wiww_fwee_node(as, m);

	n = bch2_btwee_node_awwoc(as, twans, b->c.wevew);

	SET_BTWEE_NODE_SEQ(n->data,
			   max(BTWEE_NODE_SEQ(b->data),
			       BTWEE_NODE_SEQ(m->data)) + 1);

	btwee_set_min(n, pwev->data->min_key);
	btwee_set_max(n, next->data->max_key);

	n->data->fowmat	 = new_f;
	btwee_node_set_fowmat(n, new_f);

	bch2_btwee_sowt_into(c, n, pwev);
	bch2_btwee_sowt_into(c, n, next);

	bch2_btwee_buiwd_aux_twees(n);
	bch2_btwee_update_add_new_node(as, n);
	six_unwock_wwite(&n->c.wock);

	new_path = get_unwocked_mut_path(twans, btwee, n->c.wevew, n->key.k.p);
	six_wock_incwement(&n->c.wock, SIX_WOCK_intent);
	mawk_btwee_node_wocked(twans, twans->paths + new_path, n->c.wevew, BTWEE_NODE_INTENT_WOCKED);
	bch2_btwee_path_wevew_init(twans, twans->paths + new_path, n);

	bkey_init(&dewete.k);
	dewete.k.p = pwev->key.k.p;
	bch2_keywist_add(&as->pawent_keys, &dewete);
	bch2_keywist_add(&as->pawent_keys, &n->key);

	bch2_twans_vewify_paths(twans);

	wet = bch2_btwee_insewt_node(as, twans, path, pawent, &as->pawent_keys, fwags);
	if (wet)
		goto eww_fwee_update;

	bch2_twans_vewify_paths(twans);

	bch2_btwee_update_get_open_buckets(as, n);
	bch2_btwee_node_wwite(c, n, SIX_WOCK_intent, 0);

	bch2_btwee_node_fwee_inmem(twans, twans->paths + path, b);
	bch2_btwee_node_fwee_inmem(twans, twans->paths + sib_path, m);

	bch2_twans_node_add(twans, twans->paths + path, n);

	bch2_twans_vewify_paths(twans);

	six_unwock_intent(&n->c.wock);

	bch2_btwee_update_done(as, twans);

	bch2_time_stats_update(&c->times[BCH_TIME_btwee_node_mewge], stawt_time);
out:
eww:
	if (new_path)
		bch2_path_put(twans, new_path, twue);
	bch2_path_put(twans, sib_path, twue);
	bch2_twans_vewify_wocks(twans);
	wetuwn wet;
eww_fwee_update:
	bch2_btwee_node_fwee_nevew_used(as, twans, n);
	bch2_btwee_update_fwee(as, twans);
	goto out;
}

int bch2_btwee_node_wewwite(stwuct btwee_twans *twans,
			    stwuct btwee_itew *itew,
			    stwuct btwee *b,
			    unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee *n, *pawent;
	stwuct btwee_update *as;
	btwee_path_idx_t new_path = 0;
	int wet;

	fwags |= BCH_TWANS_COMMIT_no_enospc;

	stwuct btwee_path *path = btwee_itew_path(twans, itew);
	pawent = btwee_node_pawent(path, b);
	as = bch2_btwee_update_stawt(twans, path, b->c.wevew, fawse, fwags);
	wet = PTW_EWW_OW_ZEWO(as);
	if (wet)
		goto out;

	bch2_btwee_intewiow_update_wiww_fwee_node(as, b);

	n = bch2_btwee_node_awwoc_wepwacement(as, twans, b);

	bch2_btwee_buiwd_aux_twees(n);
	bch2_btwee_update_add_new_node(as, n);
	six_unwock_wwite(&n->c.wock);

	new_path = get_unwocked_mut_path(twans, itew->btwee_id, n->c.wevew, n->key.k.p);
	six_wock_incwement(&n->c.wock, SIX_WOCK_intent);
	mawk_btwee_node_wocked(twans, twans->paths + new_path, n->c.wevew, BTWEE_NODE_INTENT_WOCKED);
	bch2_btwee_path_wevew_init(twans, twans->paths + new_path, n);

	twace_and_count(c, btwee_node_wewwite, twans, b);

	if (pawent) {
		bch2_keywist_add(&as->pawent_keys, &n->key);
		wet = bch2_btwee_insewt_node(as, twans, itew->path,
					     pawent, &as->pawent_keys, fwags);
		if (wet)
			goto eww;
	} ewse {
		bch2_btwee_set_woot(as, twans, btwee_itew_path(twans, itew), n);
	}

	bch2_btwee_update_get_open_buckets(as, n);
	bch2_btwee_node_wwite(c, n, SIX_WOCK_intent, 0);

	bch2_btwee_node_fwee_inmem(twans, btwee_itew_path(twans, itew), b);

	bch2_twans_node_add(twans, twans->paths + itew->path, n);
	six_unwock_intent(&n->c.wock);

	bch2_btwee_update_done(as, twans);
out:
	if (new_path)
		bch2_path_put(twans, new_path, twue);
	bch2_twans_downgwade(twans);
	wetuwn wet;
eww:
	bch2_btwee_node_fwee_nevew_used(as, twans, n);
	bch2_btwee_update_fwee(as, twans);
	goto out;
}

stwuct async_btwee_wewwite {
	stwuct bch_fs		*c;
	stwuct wowk_stwuct	wowk;
	stwuct wist_head	wist;
	enum btwee_id		btwee_id;
	unsigned		wevew;
	stwuct bpos		pos;
	__we64			seq;
};

static int async_btwee_node_wewwite_twans(stwuct btwee_twans *twans,
					  stwuct async_btwee_wewwite *a)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct btwee *b;
	int wet;

	bch2_twans_node_itew_init(twans, &itew, a->btwee_id, a->pos,
				  BTWEE_MAX_DEPTH, a->wevew, 0);
	b = bch2_btwee_itew_peek_node(&itew);
	wet = PTW_EWW_OW_ZEWO(b);
	if (wet)
		goto out;

	if (!b || b->data->keys.seq != a->seq) {
		stwuct pwintbuf buf = PWINTBUF;

		if (b)
			bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(&b->key));
		ewse
			pwt_stw(&buf, "(nuww");
		bch_info(c, "%s: node to wewwite not found:, seawching fow seq %wwu, got\n%s",
			 __func__, a->seq, buf.buf);
		pwintbuf_exit(&buf);
		goto out;
	}

	wet = bch2_btwee_node_wewwite(twans, &itew, b, 0);
out:
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet;
}

static void async_btwee_node_wewwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct async_btwee_wewwite *a =
		containew_of(wowk, stwuct async_btwee_wewwite, wowk);
	stwuct bch_fs *c = a->c;
	int wet;

	wet = bch2_twans_do(c, NUWW, NUWW, 0,
		      async_btwee_node_wewwite_twans(twans, a));
	bch_eww_fn(c, wet);
	bch2_wwite_wef_put(c, BCH_WWITE_WEF_node_wewwite);
	kfwee(a);
}

void bch2_btwee_node_wewwite_async(stwuct bch_fs *c, stwuct btwee *b)
{
	stwuct async_btwee_wewwite *a;
	int wet;

	a = kmawwoc(sizeof(*a), GFP_NOFS);
	if (!a) {
		bch_eww(c, "%s: ewwow awwocating memowy", __func__);
		wetuwn;
	}

	a->c		= c;
	a->btwee_id	= b->c.btwee_id;
	a->wevew	= b->c.wevew;
	a->pos		= b->key.k.p;
	a->seq		= b->data->keys.seq;
	INIT_WOWK(&a->wowk, async_btwee_node_wewwite_wowk);

	if (unwikewy(!test_bit(BCH_FS_may_go_ww, &c->fwags))) {
		mutex_wock(&c->pending_node_wewwites_wock);
		wist_add(&a->wist, &c->pending_node_wewwites);
		mutex_unwock(&c->pending_node_wewwites_wock);
		wetuwn;
	}

	if (!bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_node_wewwite)) {
		if (test_bit(BCH_FS_stawted, &c->fwags)) {
			bch_eww(c, "%s: ewwow getting c->wwites wef", __func__);
			kfwee(a);
			wetuwn;
		}

		wet = bch2_fs_wead_wwite_eawwy(c);
		bch_eww_msg(c, wet, "going wead-wwite");
		if (wet) {
			kfwee(a);
			wetuwn;
		}

		bch2_wwite_wef_get(c, BCH_WWITE_WEF_node_wewwite);
	}

	queue_wowk(c->btwee_intewiow_update_wowkew, &a->wowk);
}

void bch2_do_pending_node_wewwites(stwuct bch_fs *c)
{
	stwuct async_btwee_wewwite *a, *n;

	mutex_wock(&c->pending_node_wewwites_wock);
	wist_fow_each_entwy_safe(a, n, &c->pending_node_wewwites, wist) {
		wist_dew(&a->wist);

		bch2_wwite_wef_get(c, BCH_WWITE_WEF_node_wewwite);
		queue_wowk(c->btwee_intewiow_update_wowkew, &a->wowk);
	}
	mutex_unwock(&c->pending_node_wewwites_wock);
}

void bch2_fwee_pending_node_wewwites(stwuct bch_fs *c)
{
	stwuct async_btwee_wewwite *a, *n;

	mutex_wock(&c->pending_node_wewwites_wock);
	wist_fow_each_entwy_safe(a, n, &c->pending_node_wewwites, wist) {
		wist_dew(&a->wist);

		kfwee(a);
	}
	mutex_unwock(&c->pending_node_wewwites_wock);
}

static int __bch2_btwee_node_update_key(stwuct btwee_twans *twans,
					stwuct btwee_itew *itew,
					stwuct btwee *b, stwuct btwee *new_hash,
					stwuct bkey_i *new_key,
					unsigned commit_fwags,
					boow skip_twiggews)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew2 = { NUWW };
	stwuct btwee *pawent;
	int wet;

	if (!skip_twiggews) {
		wet   = bch2_key_twiggew_owd(twans, b->c.btwee_id, b->c.wevew + 1,
					     bkey_i_to_s_c(&b->key),
					     BTWEE_TWIGGEW_TWANSACTIONAW) ?:
			bch2_key_twiggew_new(twans, b->c.btwee_id, b->c.wevew + 1,
					     bkey_i_to_s(new_key),
					     BTWEE_TWIGGEW_TWANSACTIONAW);
		if (wet)
			wetuwn wet;
	}

	if (new_hash) {
		bkey_copy(&new_hash->key, new_key);
		wet = bch2_btwee_node_hash_insewt(&c->btwee_cache,
				new_hash, b->c.wevew, b->c.btwee_id);
		BUG_ON(wet);
	}

	pawent = btwee_node_pawent(btwee_itew_path(twans, itew), b);
	if (pawent) {
		bch2_twans_copy_itew(&itew2, itew);

		itew2.path = bch2_btwee_path_make_mut(twans, itew2.path,
				itew2.fwags & BTWEE_ITEW_INTENT,
				_THIS_IP_);

		stwuct btwee_path *path2 = btwee_itew_path(twans, &itew2);
		BUG_ON(path2->wevew != b->c.wevew);
		BUG_ON(!bpos_eq(path2->pos, new_key->k.p));

		btwee_path_set_wevew_up(twans, path2);

		twans->paths_sowted = fawse;

		wet   = bch2_btwee_itew_twavewse(&itew2) ?:
			bch2_twans_update(twans, &itew2, new_key, BTWEE_TWIGGEW_NOWUN);
		if (wet)
			goto eww;
	} ewse {
		BUG_ON(btwee_node_woot(c, b) != b);

		stwuct jset_entwy *e = bch2_twans_jset_entwy_awwoc(twans,
				       jset_u64s(new_key->k.u64s));
		wet = PTW_EWW_OW_ZEWO(e);
		if (wet)
			wetuwn wet;

		jouwnaw_entwy_set(e,
				  BCH_JSET_ENTWY_btwee_woot,
				  b->c.btwee_id, b->c.wevew,
				  new_key, new_key->k.u64s);
	}

	wet = bch2_twans_commit(twans, NUWW, NUWW, commit_fwags);
	if (wet)
		goto eww;

	bch2_btwee_node_wock_wwite_nofaiw(twans, btwee_itew_path(twans, itew), &b->c);

	if (new_hash) {
		mutex_wock(&c->btwee_cache.wock);
		bch2_btwee_node_hash_wemove(&c->btwee_cache, new_hash);
		bch2_btwee_node_hash_wemove(&c->btwee_cache, b);

		bkey_copy(&b->key, new_key);
		wet = __bch2_btwee_node_hash_insewt(&c->btwee_cache, b);
		BUG_ON(wet);
		mutex_unwock(&c->btwee_cache.wock);
	} ewse {
		bkey_copy(&b->key, new_key);
	}

	bch2_btwee_node_unwock_wwite(twans, btwee_itew_path(twans, itew), b);
out:
	bch2_twans_itew_exit(twans, &itew2);
	wetuwn wet;
eww:
	if (new_hash) {
		mutex_wock(&c->btwee_cache.wock);
		bch2_btwee_node_hash_wemove(&c->btwee_cache, b);
		mutex_unwock(&c->btwee_cache.wock);
	}
	goto out;
}

int bch2_btwee_node_update_key(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			       stwuct btwee *b, stwuct bkey_i *new_key,
			       unsigned commit_fwags, boow skip_twiggews)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee *new_hash = NUWW;
	stwuct btwee_path *path = btwee_itew_path(twans, itew);
	stwuct cwosuwe cw;
	int wet = 0;

	wet = bch2_btwee_path_upgwade(twans, path, b->c.wevew + 1);
	if (wet)
		wetuwn wet;

	cwosuwe_init_stack(&cw);

	/*
	 * check btwee_ptw_hash_vaw() aftew @b is wocked by
	 * btwee_itew_twavewse():
	 */
	if (btwee_ptw_hash_vaw(new_key) != b->hash_vaw) {
		wet = bch2_btwee_cache_cannibawize_wock(twans, &cw);
		if (wet) {
			wet = dwop_wocks_do(twans, (cwosuwe_sync(&cw), 0));
			if (wet)
				wetuwn wet;
		}

		new_hash = bch2_btwee_node_mem_awwoc(twans, fawse);
	}

	path->intent_wef++;
	wet = __bch2_btwee_node_update_key(twans, itew, b, new_hash, new_key,
					   commit_fwags, skip_twiggews);
	--path->intent_wef;

	if (new_hash) {
		mutex_wock(&c->btwee_cache.wock);
		wist_move(&new_hash->wist, &c->btwee_cache.fweeabwe);
		mutex_unwock(&c->btwee_cache.wock);

		six_unwock_wwite(&new_hash->c.wock);
		six_unwock_intent(&new_hash->c.wock);
	}
	cwosuwe_sync(&cw);
	bch2_btwee_cache_cannibawize_unwock(twans);
	wetuwn wet;
}

int bch2_btwee_node_update_key_get_itew(stwuct btwee_twans *twans,
					stwuct btwee *b, stwuct bkey_i *new_key,
					unsigned commit_fwags, boow skip_twiggews)
{
	stwuct btwee_itew itew;
	int wet;

	bch2_twans_node_itew_init(twans, &itew, b->c.btwee_id, b->key.k.p,
				  BTWEE_MAX_DEPTH, b->c.wevew,
				  BTWEE_ITEW_INTENT);
	wet = bch2_btwee_itew_twavewse(&itew);
	if (wet)
		goto out;

	/* has node been fweed? */
	if (btwee_itew_path(twans, &itew)->w[b->c.wevew].b != b) {
		/* node has been fweed: */
		BUG_ON(!btwee_node_dying(b));
		goto out;
	}

	BUG_ON(!btwee_node_hashed(b));

	stwuct bch_extent_ptw *ptw;
	bch2_bkey_dwop_ptws(bkey_i_to_s(new_key), ptw,
			    !bch2_bkey_has_device(bkey_i_to_s(&b->key), ptw->dev));

	wet = bch2_btwee_node_update_key(twans, &itew, b, new_key,
					 commit_fwags, skip_twiggews);
out:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

/* Init code: */

/*
 * Onwy fow fiwesystem bwingup, when fiwst weading the btwee woots ow awwocating
 * btwee woots when initiawizing a new fiwesystem:
 */
void bch2_btwee_set_woot_fow_wead(stwuct bch_fs *c, stwuct btwee *b)
{
	BUG_ON(btwee_node_woot(c, b));

	bch2_btwee_set_woot_inmem(c, b);
}

static int __bch2_btwee_woot_awwoc(stwuct btwee_twans *twans, enum btwee_id id)
{
	stwuct bch_fs *c = twans->c;
	stwuct cwosuwe cw;
	stwuct btwee *b;
	int wet;

	cwosuwe_init_stack(&cw);

	do {
		wet = bch2_btwee_cache_cannibawize_wock(twans, &cw);
		cwosuwe_sync(&cw);
	} whiwe (wet);

	b = bch2_btwee_node_mem_awwoc(twans, fawse);
	bch2_btwee_cache_cannibawize_unwock(twans);

	set_btwee_node_fake(b);
	set_btwee_node_need_wewwite(b);
	b->c.wevew	= 0;
	b->c.btwee_id	= id;

	bkey_btwee_ptw_init(&b->key);
	b->key.k.p = SPOS_MAX;
	*((u64 *) bkey_i_to_btwee_ptw(&b->key)->v.stawt) = U64_MAX - id;

	bch2_bset_init_fiwst(b, &b->data->keys);
	bch2_btwee_buiwd_aux_twees(b);

	b->data->fwags = 0;
	btwee_set_min(b, POS_MIN);
	btwee_set_max(b, SPOS_MAX);
	b->data->fowmat = bch2_btwee_cawc_fowmat(b);
	btwee_node_set_fowmat(b, b->data->fowmat);

	wet = bch2_btwee_node_hash_insewt(&c->btwee_cache, b,
					  b->c.wevew, b->c.btwee_id);
	BUG_ON(wet);

	bch2_btwee_set_woot_inmem(c, b);

	six_unwock_wwite(&b->c.wock);
	six_unwock_intent(&b->c.wock);
	wetuwn 0;
}

void bch2_btwee_woot_awwoc(stwuct bch_fs *c, enum btwee_id id)
{
	bch2_twans_wun(c, __bch2_btwee_woot_awwoc(twans, id));
}

void bch2_btwee_updates_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	stwuct btwee_update *as;

	mutex_wock(&c->btwee_intewiow_update_wock);
	wist_fow_each_entwy(as, &c->btwee_intewiow_update_wist, wist)
		pwt_pwintf(out, "%p m %u w %u w %u j %wwu\n",
		       as,
		       as->mode,
		       as->nodes_wwitten,
		       cwosuwe_nw_wemaining(&as->cw),
		       as->jouwnaw.seq);
	mutex_unwock(&c->btwee_intewiow_update_wock);
}

static boow bch2_btwee_intewiow_updates_pending(stwuct bch_fs *c)
{
	boow wet;

	mutex_wock(&c->btwee_intewiow_update_wock);
	wet = !wist_empty(&c->btwee_intewiow_update_wist);
	mutex_unwock(&c->btwee_intewiow_update_wock);

	wetuwn wet;
}

boow bch2_btwee_intewiow_updates_fwush(stwuct bch_fs *c)
{
	boow wet = bch2_btwee_intewiow_updates_pending(c);

	if (wet)
		cwosuwe_wait_event(&c->btwee_intewiow_update_wait,
				   !bch2_btwee_intewiow_updates_pending(c));
	wetuwn wet;
}

void bch2_jouwnaw_entwy_to_btwee_woot(stwuct bch_fs *c, stwuct jset_entwy *entwy)
{
	stwuct btwee_woot *w = bch2_btwee_id_woot(c, entwy->btwee_id);

	mutex_wock(&c->btwee_woot_wock);

	w->wevew = entwy->wevew;
	w->awive = twue;
	bkey_copy(&w->key, (stwuct bkey_i *) entwy->stawt);

	mutex_unwock(&c->btwee_woot_wock);
}

stwuct jset_entwy *
bch2_btwee_woots_to_jouwnaw_entwies(stwuct bch_fs *c,
				    stwuct jset_entwy *end,
				    unsigned wong skip)
{
	unsigned i;

	mutex_wock(&c->btwee_woot_wock);

	fow (i = 0; i < btwee_id_nw_awive(c); i++) {
		stwuct btwee_woot *w = bch2_btwee_id_woot(c, i);

		if (w->awive && !test_bit(i, &skip)) {
			jouwnaw_entwy_set(end, BCH_JSET_ENTWY_btwee_woot,
					  i, w->wevew, &w->key, w->key.k.u64s);
			end = vstwuct_next(end);
		}
	}

	mutex_unwock(&c->btwee_woot_wock);

	wetuwn end;
}

void bch2_fs_btwee_intewiow_update_exit(stwuct bch_fs *c)
{
	if (c->btwee_intewiow_update_wowkew)
		destwoy_wowkqueue(c->btwee_intewiow_update_wowkew);
	mempoow_exit(&c->btwee_intewiow_update_poow);
}

void bch2_fs_btwee_intewiow_update_init_eawwy(stwuct bch_fs *c)
{
	mutex_init(&c->btwee_wesewve_cache_wock);
	INIT_WIST_HEAD(&c->btwee_intewiow_update_wist);
	INIT_WIST_HEAD(&c->btwee_intewiow_updates_unwwitten);
	mutex_init(&c->btwee_intewiow_update_wock);
	INIT_WOWK(&c->btwee_intewiow_update_wowk, btwee_intewiow_update_wowk);

	INIT_WIST_HEAD(&c->pending_node_wewwites);
	mutex_init(&c->pending_node_wewwites_wock);
}

int bch2_fs_btwee_intewiow_update_init(stwuct bch_fs *c)
{
	c->btwee_intewiow_update_wowkew =
		awwoc_wowkqueue("btwee_update", WQ_UNBOUND|WQ_MEM_WECWAIM, 1);
	if (!c->btwee_intewiow_update_wowkew)
		wetuwn -BCH_EWW_ENOMEM_btwee_intewiow_update_wowkew_init;

	if (mempoow_init_kmawwoc_poow(&c->btwee_intewiow_update_poow, 1,
				      sizeof(stwuct btwee_update)))
		wetuwn -BCH_EWW_ENOMEM_btwee_intewiow_update_poow_init;

	wetuwn 0;
}
