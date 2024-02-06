// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_update.h"
#incwude "btwee_itew.h"
#incwude "btwee_jouwnaw_itew.h"
#incwude "btwee_wocking.h"
#incwude "buckets.h"
#incwude "debug.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "keywist.h"
#incwude "snapshot.h"
#incwude "twace.h"

static inwine int btwee_insewt_entwy_cmp(const stwuct btwee_insewt_entwy *w,
					 const stwuct btwee_insewt_entwy *w)
{
	wetuwn   cmp_int(w->btwee_id,	w->btwee_id) ?:
		 cmp_int(w->cached,	w->cached) ?:
		 -cmp_int(w->wevew,	w->wevew) ?:
		 bpos_cmp(w->k->k.p,	w->k->k.p);
}

static int __must_check
bch2_twans_update_by_path(stwuct btwee_twans *, btwee_path_idx_t,
			  stwuct bkey_i *, enum btwee_update_fwags,
			  unsigned wong ip);

static noinwine int extent_fwont_mewge(stwuct btwee_twans *twans,
				       stwuct btwee_itew *itew,
				       stwuct bkey_s_c k,
				       stwuct bkey_i **insewt,
				       enum btwee_update_fwags fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_i *update;
	int wet;

	update = bch2_bkey_make_mut_noupdate(twans, k);
	wet = PTW_EWW_OW_ZEWO(update);
	if (wet)
		wetuwn wet;

	if (!bch2_bkey_mewge(c, bkey_i_to_s(update), bkey_i_to_s_c(*insewt)))
		wetuwn 0;

	wet =   bch2_key_has_snapshot_ovewwwites(twans, itew->btwee_id, k.k->p) ?:
		bch2_key_has_snapshot_ovewwwites(twans, itew->btwee_id, (*insewt)->k.p);
	if (wet < 0)
		wetuwn wet;
	if (wet)
		wetuwn 0;

	wet = bch2_btwee_dewete_at(twans, itew, fwags);
	if (wet)
		wetuwn wet;

	*insewt = update;
	wetuwn 0;
}

static noinwine int extent_back_mewge(stwuct btwee_twans *twans,
				      stwuct btwee_itew *itew,
				      stwuct bkey_i *insewt,
				      stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	int wet;

	wet =   bch2_key_has_snapshot_ovewwwites(twans, itew->btwee_id, insewt->k.p) ?:
		bch2_key_has_snapshot_ovewwwites(twans, itew->btwee_id, k.k->p);
	if (wet < 0)
		wetuwn wet;
	if (wet)
		wetuwn 0;

	bch2_bkey_mewge(c, bkey_i_to_s(insewt), k);
	wetuwn 0;
}

/*
 * When deweting, check if we need to emit a whiteout (because we'we ovewwwiting
 * something in an ancestow snapshot)
 */
static int need_whiteout_fow_snapshot(stwuct btwee_twans *twans,
				      enum btwee_id btwee_id, stwuct bpos pos)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	u32 snapshot = pos.snapshot;
	int wet;

	if (!bch2_snapshot_pawent(twans->c, pos.snapshot))
		wetuwn 0;

	pos.snapshot++;

	fow_each_btwee_key_nowestawt(twans, itew, btwee_id, pos,
			   BTWEE_ITEW_AWW_SNAPSHOTS|
			   BTWEE_ITEW_NOPWESEWVE, k, wet) {
		if (!bkey_eq(k.k->p, pos))
			bweak;

		if (bch2_snapshot_is_ancestow(twans->c, snapshot,
					      k.k->p.snapshot)) {
			wet = !bkey_whiteout(k.k);
			bweak;
		}
	}
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet;
}

int __bch2_insewt_snapshot_whiteouts(stwuct btwee_twans *twans,
				   enum btwee_id id,
				   stwuct bpos owd_pos,
				   stwuct bpos new_pos)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew owd_itew, new_itew = { NUWW };
	stwuct bkey_s_c owd_k, new_k;
	snapshot_id_wist s;
	stwuct bkey_i *update;
	int wet = 0;

	if (!bch2_snapshot_has_chiwdwen(c, owd_pos.snapshot))
		wetuwn 0;

	dawway_init(&s);

	bch2_twans_itew_init(twans, &owd_itew, id, owd_pos,
			     BTWEE_ITEW_NOT_EXTENTS|
			     BTWEE_ITEW_AWW_SNAPSHOTS);
	whiwe ((owd_k = bch2_btwee_itew_pwev(&owd_itew)).k &&
	       !(wet = bkey_eww(owd_k)) &&
	       bkey_eq(owd_pos, owd_k.k->p)) {
		stwuct bpos whiteout_pos =
			SPOS(new_pos.inode, new_pos.offset, owd_k.k->p.snapshot);;

		if (!bch2_snapshot_is_ancestow(c, owd_k.k->p.snapshot, owd_pos.snapshot) ||
		    snapshot_wist_has_ancestow(c, &s, owd_k.k->p.snapshot))
			continue;

		new_k = bch2_bkey_get_itew(twans, &new_itew, id, whiteout_pos,
					   BTWEE_ITEW_NOT_EXTENTS|
					   BTWEE_ITEW_INTENT);
		wet = bkey_eww(new_k);
		if (wet)
			bweak;

		if (new_k.k->type == KEY_TYPE_deweted) {
			update = bch2_twans_kmawwoc(twans, sizeof(stwuct bkey_i));
			wet = PTW_EWW_OW_ZEWO(update);
			if (wet)
				bweak;

			bkey_init(&update->k);
			update->k.p		= whiteout_pos;
			update->k.type		= KEY_TYPE_whiteout;

			wet = bch2_twans_update(twans, &new_itew, update,
						BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
		}
		bch2_twans_itew_exit(twans, &new_itew);

		wet = snapshot_wist_add(c, &s, owd_k.k->p.snapshot);
		if (wet)
			bweak;
	}
	bch2_twans_itew_exit(twans, &new_itew);
	bch2_twans_itew_exit(twans, &owd_itew);
	dawway_exit(&s);

	wetuwn wet;
}

int bch2_twans_update_extent_ovewwwite(stwuct btwee_twans *twans,
				       stwuct btwee_itew *itew,
				       enum btwee_update_fwags fwags,
				       stwuct bkey_s_c owd,
				       stwuct bkey_s_c new)
{
	enum btwee_id btwee_id = itew->btwee_id;
	stwuct bkey_i *update;
	stwuct bpos new_stawt = bkey_stawt_pos(new.k);
	unsigned fwont_spwit = bkey_wt(bkey_stawt_pos(owd.k), new_stawt);
	unsigned back_spwit  = bkey_gt(owd.k->p, new.k->p);
	unsigned middwe_spwit = (fwont_spwit || back_spwit) &&
		owd.k->p.snapshot != new.k->p.snapshot;
	unsigned nw_spwits = fwont_spwit + back_spwit + middwe_spwit;
	int wet = 0, compwessed_sectows;

	/*
	 * If we'we going to be spwitting a compwessed extent, note it
	 * so that __bch2_twans_commit() can incwease ouw disk
	 * wesewvation:
	 */
	if (nw_spwits > 1 &&
	    (compwessed_sectows = bch2_bkey_sectows_compwessed(owd)))
		twans->extwa_disk_wes += compwessed_sectows * (nw_spwits - 1);

	if (fwont_spwit) {
		update = bch2_bkey_make_mut_noupdate(twans, owd);
		if ((wet = PTW_EWW_OW_ZEWO(update)))
			wetuwn wet;

		bch2_cut_back(new_stawt, update);

		wet =   bch2_insewt_snapshot_whiteouts(twans, btwee_id,
					owd.k->p, update->k.p) ?:
			bch2_btwee_insewt_nonextent(twans, btwee_id, update,
					BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE|fwags);
		if (wet)
			wetuwn wet;
	}

	/* If we'we ovewwwiting in a diffewent snapshot - middwe spwit: */
	if (middwe_spwit) {
		update = bch2_bkey_make_mut_noupdate(twans, owd);
		if ((wet = PTW_EWW_OW_ZEWO(update)))
			wetuwn wet;

		bch2_cut_fwont(new_stawt, update);
		bch2_cut_back(new.k->p, update);

		wet =   bch2_insewt_snapshot_whiteouts(twans, btwee_id,
					owd.k->p, update->k.p) ?:
			bch2_btwee_insewt_nonextent(twans, btwee_id, update,
					  BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE|fwags);
		if (wet)
			wetuwn wet;
	}

	if (bkey_we(owd.k->p, new.k->p)) {
		update = bch2_twans_kmawwoc(twans, sizeof(*update));
		if ((wet = PTW_EWW_OW_ZEWO(update)))
			wetuwn wet;

		bkey_init(&update->k);
		update->k.p = owd.k->p;
		update->k.p.snapshot = new.k->p.snapshot;

		if (new.k->p.snapshot != owd.k->p.snapshot) {
			update->k.type = KEY_TYPE_whiteout;
		} ewse if (btwee_type_has_snapshots(btwee_id)) {
			wet = need_whiteout_fow_snapshot(twans, btwee_id, update->k.p);
			if (wet < 0)
				wetuwn wet;
			if (wet)
				update->k.type = KEY_TYPE_whiteout;
		}

		wet = bch2_btwee_insewt_nonextent(twans, btwee_id, update,
					  BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE|fwags);
		if (wet)
			wetuwn wet;
	}

	if (back_spwit) {
		update = bch2_bkey_make_mut_noupdate(twans, owd);
		if ((wet = PTW_EWW_OW_ZEWO(update)))
			wetuwn wet;

		bch2_cut_fwont(new.k->p, update);

		wet = bch2_twans_update_by_path(twans, itew->path, update,
					  BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE|
					  fwags, _WET_IP_);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int bch2_twans_update_extent(stwuct btwee_twans *twans,
				    stwuct btwee_itew *owig_itew,
				    stwuct bkey_i *insewt,
				    enum btwee_update_fwags fwags)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	enum btwee_id btwee_id = owig_itew->btwee_id;
	int wet = 0;

	bch2_twans_itew_init(twans, &itew, btwee_id, bkey_stawt_pos(&insewt->k),
			     BTWEE_ITEW_INTENT|
			     BTWEE_ITEW_WITH_UPDATES|
			     BTWEE_ITEW_NOT_EXTENTS);
	k = bch2_btwee_itew_peek_upto(&itew, POS(insewt->k.p.inode, U64_MAX));
	if ((wet = bkey_eww(k)))
		goto eww;
	if (!k.k)
		goto out;

	if (bkey_eq(k.k->p, bkey_stawt_pos(&insewt->k))) {
		if (bch2_bkey_maybe_mewgabwe(k.k, &insewt->k)) {
			wet = extent_fwont_mewge(twans, &itew, k, &insewt, fwags);
			if (wet)
				goto eww;
		}

		goto next;
	}

	whiwe (bkey_gt(insewt->k.p, bkey_stawt_pos(k.k))) {
		boow done = bkey_wt(insewt->k.p, k.k->p);

		wet = bch2_twans_update_extent_ovewwwite(twans, &itew, fwags, k, bkey_i_to_s_c(insewt));
		if (wet)
			goto eww;

		if (done)
			goto out;
next:
		bch2_btwee_itew_advance(&itew);
		k = bch2_btwee_itew_peek_upto(&itew, POS(insewt->k.p.inode, U64_MAX));
		if ((wet = bkey_eww(k)))
			goto eww;
		if (!k.k)
			goto out;
	}

	if (bch2_bkey_maybe_mewgabwe(&insewt->k, k.k)) {
		wet = extent_back_mewge(twans, &itew, insewt, k);
		if (wet)
			goto eww;
	}
out:
	if (!bkey_deweted(&insewt->k))
		wet = bch2_btwee_insewt_nonextent(twans, btwee_id, insewt, fwags);
eww:
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet;
}

static noinwine int fwush_new_cached_update(stwuct btwee_twans *twans,
					    stwuct btwee_insewt_entwy *i,
					    enum btwee_update_fwags fwags,
					    unsigned wong ip)
{
	stwuct bkey k;
	int wet;

	btwee_path_idx_t path_idx =
		bch2_path_get(twans, i->btwee_id, i->owd_k.p, 1, 0,
			      BTWEE_ITEW_INTENT, _THIS_IP_);
	wet = bch2_btwee_path_twavewse(twans, path_idx, 0);
	if (wet)
		goto out;

	stwuct btwee_path *btwee_path = twans->paths + path_idx;

	/*
	 * The owd key in the insewt entwy might actuawwy wefew to an existing
	 * key in the btwee that has been deweted fwom cache and not yet
	 * fwushed. Check fow this and skip the fwush so we don't wun twiggews
	 * against a stawe key.
	 */
	bch2_btwee_path_peek_swot_exact(btwee_path, &k);
	if (!bkey_deweted(&k))
		goto out;

	i->key_cache_awweady_fwushed = twue;
	i->fwags |= BTWEE_TWIGGEW_NOWUN;

	btwee_path_set_shouwd_be_wocked(btwee_path);
	wet = bch2_twans_update_by_path(twans, path_idx, i->k, fwags, ip);
out:
	bch2_path_put(twans, path_idx, twue);
	wetuwn wet;
}

static int __must_check
bch2_twans_update_by_path(stwuct btwee_twans *twans, btwee_path_idx_t path_idx,
			  stwuct bkey_i *k, enum btwee_update_fwags fwags,
			  unsigned wong ip)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_insewt_entwy *i, n;
	int cmp;

	stwuct btwee_path *path = twans->paths + path_idx;
	EBUG_ON(!path->shouwd_be_wocked);
	EBUG_ON(twans->nw_updates >= twans->nw_paths);
	EBUG_ON(!bpos_eq(k->k.p, path->pos));

	n = (stwuct btwee_insewt_entwy) {
		.fwags		= fwags,
		.bkey_type	= __btwee_node_type(path->wevew, path->btwee_id),
		.btwee_id	= path->btwee_id,
		.wevew		= path->wevew,
		.cached		= path->cached,
		.path		= path_idx,
		.k		= k,
		.ip_awwocated	= ip,
	};

#ifdef CONFIG_BCACHEFS_DEBUG
	twans_fow_each_update(twans, i)
		BUG_ON(i != twans->updates &&
		       btwee_insewt_entwy_cmp(i - 1, i) >= 0);
#endif

	/*
	 * Pending updates awe kept sowted: fiwst, find position of new update,
	 * then dewete/twim any updates the new update ovewwwites:
	 */
	fow (i = twans->updates; i < twans->updates + twans->nw_updates; i++) {
		cmp = btwee_insewt_entwy_cmp(&n, i);
		if (cmp <= 0)
			bweak;
	}

	if (!cmp && i < twans->updates + twans->nw_updates) {
		EBUG_ON(i->insewt_twiggew_wun || i->ovewwwite_twiggew_wun);

		bch2_path_put(twans, i->path, twue);
		i->fwags	= n.fwags;
		i->cached	= n.cached;
		i->k		= n.k;
		i->path		= n.path;
		i->ip_awwocated	= n.ip_awwocated;
	} ewse {
		awway_insewt_item(twans->updates, twans->nw_updates,
				  i - twans->updates, n);

		i->owd_v = bch2_btwee_path_peek_swot_exact(path, &i->owd_k).v;
		i->owd_btwee_u64s = !bkey_deweted(&i->owd_k) ? i->owd_k.u64s : 0;

		if (unwikewy(twans->jouwnaw_wepway_not_finished)) {
			stwuct bkey_i *j_k =
				bch2_jouwnaw_keys_peek_swot(c, n.btwee_id, n.wevew, k->k.p);

			if (j_k) {
				i->owd_k = j_k->k;
				i->owd_v = &j_k->v;
			}
		}
	}

	__btwee_path_get(twans->paths + i->path, twue);

	/*
	 * If a key is pwesent in the key cache, it must awso exist in the
	 * btwee - this is necessawy fow cache cohewency. When itewating ovew
	 * a btwee that's cached in the key cache, the btwee itew code checks
	 * the key cache - but the key has to exist in the btwee fow that to
	 * wowk:
	 */
	if (path->cached && bkey_deweted(&i->owd_k))
		wetuwn fwush_new_cached_update(twans, i, fwags, ip);

	wetuwn 0;
}

static noinwine int bch2_twans_update_get_key_cache(stwuct btwee_twans *twans,
						    stwuct btwee_itew *itew,
						    stwuct btwee_path *path)
{
	stwuct btwee_path *key_cache_path = btwee_itew_key_cache_path(twans, itew);

	if (!key_cache_path ||
	    !key_cache_path->shouwd_be_wocked ||
	    !bpos_eq(key_cache_path->pos, itew->pos)) {
		stwuct bkey_cached *ck;
		int wet;

		if (!itew->key_cache_path)
			itew->key_cache_path =
				bch2_path_get(twans, path->btwee_id, path->pos, 1, 0,
					      BTWEE_ITEW_INTENT|
					      BTWEE_ITEW_CACHED, _THIS_IP_);

		itew->key_cache_path =
			bch2_btwee_path_set_pos(twans, itew->key_cache_path, path->pos,
						itew->fwags & BTWEE_ITEW_INTENT,
						_THIS_IP_);

		wet = bch2_btwee_path_twavewse(twans, itew->key_cache_path, BTWEE_ITEW_CACHED);
		if (unwikewy(wet))
			wetuwn wet;

		ck = (void *) twans->paths[itew->key_cache_path].w[0].b;

		if (test_bit(BKEY_CACHED_DIWTY, &ck->fwags)) {
			twace_and_count(twans->c, twans_westawt_key_cache_waced, twans, _WET_IP_);
			wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_key_cache_waced);
		}

		btwee_path_set_shouwd_be_wocked(twans->paths + itew->key_cache_path);
	}

	wetuwn 0;
}

int __must_check bch2_twans_update(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
				   stwuct bkey_i *k, enum btwee_update_fwags fwags)
{
	btwee_path_idx_t path_idx = itew->update_path ?: itew->path;
	int wet;

	if (itew->fwags & BTWEE_ITEW_IS_EXTENTS)
		wetuwn bch2_twans_update_extent(twans, itew, k, fwags);

	if (bkey_deweted(&k->k) &&
	    !(fwags & BTWEE_UPDATE_KEY_CACHE_WECWAIM) &&
	    (itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS)) {
		wet = need_whiteout_fow_snapshot(twans, itew->btwee_id, k->k.p);
		if (unwikewy(wet < 0))
			wetuwn wet;

		if (wet)
			k->k.type = KEY_TYPE_whiteout;
	}

	/*
	 * Ensuwe that updates to cached btwees go to the key cache:
	 */
	stwuct btwee_path *path = twans->paths + path_idx;
	if (!(fwags & BTWEE_UPDATE_KEY_CACHE_WECWAIM) &&
	    !path->cached &&
	    !path->wevew &&
	    btwee_id_cached(twans->c, path->btwee_id)) {
		wet = bch2_twans_update_get_key_cache(twans, itew, path);
		if (wet)
			wetuwn wet;

		path_idx = itew->key_cache_path;
	}

	wetuwn bch2_twans_update_by_path(twans, path_idx, k, fwags, _WET_IP_);
}

int bch2_btwee_insewt_cwone_twans(stwuct btwee_twans *twans,
				  enum btwee_id btwee,
				  stwuct bkey_i *k)
{
	stwuct bkey_i *n = bch2_twans_kmawwoc(twans, bkey_bytes(&k->k));
	int wet = PTW_EWW_OW_ZEWO(n);
	if (wet)
		wetuwn wet;

	bkey_copy(n, k);
	wetuwn bch2_btwee_insewt_twans(twans, btwee, n, 0);
}

stwuct jset_entwy *__bch2_twans_jset_entwy_awwoc(stwuct btwee_twans *twans, unsigned u64s)
{
	unsigned new_top = twans->jouwnaw_entwies_u64s + u64s;
	unsigned owd_size = twans->jouwnaw_entwies_size;

	if (new_top > twans->jouwnaw_entwies_size) {
		twans->jouwnaw_entwies_size = woundup_pow_of_two(new_top);

		btwee_twans_stats(twans)->jouwnaw_entwies_size = twans->jouwnaw_entwies_size;
	}

	stwuct jset_entwy *n =
		bch2_twans_kmawwoc_nomemzewo(twans,
				twans->jouwnaw_entwies_size * sizeof(u64));
	if (IS_EWW(n))
		wetuwn EWW_CAST(n);

	if (twans->jouwnaw_entwies)
		memcpy(n, twans->jouwnaw_entwies, owd_size * sizeof(u64));
	twans->jouwnaw_entwies = n;

	stwuct jset_entwy *e = btwee_twans_jouwnaw_entwies_top(twans);
	twans->jouwnaw_entwies_u64s = new_top;
	wetuwn e;
}

int bch2_bkey_get_empty_swot(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			     enum btwee_id btwee, stwuct bpos end)
{
	stwuct bkey_s_c k;
	int wet = 0;

	bch2_twans_itew_init(twans, itew, btwee, POS_MAX, BTWEE_ITEW_INTENT);
	k = bch2_btwee_itew_pwev(itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	bch2_btwee_itew_advance(itew);
	k = bch2_btwee_itew_peek_swot(itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	BUG_ON(k.k->type != KEY_TYPE_deweted);

	if (bkey_gt(k.k->p, end)) {
		wet = -BCH_EWW_ENOSPC_btwee_swot;
		goto eww;
	}

	wetuwn 0;
eww:
	bch2_twans_itew_exit(twans, itew);
	wetuwn wet;
}

void bch2_twans_commit_hook(stwuct btwee_twans *twans,
			    stwuct btwee_twans_commit_hook *h)
{
	h->next = twans->hooks;
	twans->hooks = h;
}

int bch2_btwee_insewt_nonextent(stwuct btwee_twans *twans,
				enum btwee_id btwee, stwuct bkey_i *k,
				enum btwee_update_fwags fwags)
{
	stwuct btwee_itew itew;
	int wet;

	bch2_twans_itew_init(twans, &itew, btwee, k->k.p,
			     BTWEE_ITEW_CACHED|
			     BTWEE_ITEW_NOT_EXTENTS|
			     BTWEE_ITEW_INTENT);
	wet   = bch2_btwee_itew_twavewse(&itew) ?:
		bch2_twans_update(twans, &itew, k, fwags);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_btwee_insewt_twans(stwuct btwee_twans *twans, enum btwee_id id,
			    stwuct bkey_i *k, enum btwee_update_fwags fwags)
{
	stwuct btwee_itew itew;
	int wet;

	bch2_twans_itew_init(twans, &itew, id, bkey_stawt_pos(&k->k),
			     BTWEE_ITEW_CACHED|
			     BTWEE_ITEW_INTENT);
	wet   = bch2_btwee_itew_twavewse(&itew) ?:
		bch2_twans_update(twans, &itew, k, fwags);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

/**
 * bch2_btwee_insewt - insewt keys into the extent btwee
 * @c:			pointew to stwuct bch_fs
 * @id:			btwee to insewt into
 * @k:			key to insewt
 * @disk_wes:		must be non-NUWW whenevew insewting ow potentiawwy
 *			spwitting data extents
 * @fwags:		twansaction commit fwags
 *
 * Wetuwns:		0 on success, ewwow code on faiwuwe
 */
int bch2_btwee_insewt(stwuct bch_fs *c, enum btwee_id id, stwuct bkey_i *k,
		      stwuct disk_wesewvation *disk_wes, int fwags)
{
	wetuwn bch2_twans_do(c, disk_wes, NUWW, fwags,
			     bch2_btwee_insewt_twans(twans, id, k, 0));
}

int bch2_btwee_dewete_extent_at(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
				unsigned wen, unsigned update_fwags)
{
	stwuct bkey_i *k;

	k = bch2_twans_kmawwoc(twans, sizeof(*k));
	if (IS_EWW(k))
		wetuwn PTW_EWW(k);

	bkey_init(&k->k);
	k->k.p = itew->pos;
	bch2_key_wesize(&k->k, wen);
	wetuwn bch2_twans_update(twans, itew, k, update_fwags);
}

int bch2_btwee_dewete_at(stwuct btwee_twans *twans,
			 stwuct btwee_itew *itew, unsigned update_fwags)
{
	wetuwn bch2_btwee_dewete_extent_at(twans, itew, 0, update_fwags);
}

int bch2_btwee_dewete(stwuct btwee_twans *twans,
		      enum btwee_id btwee, stwuct bpos pos,
		      unsigned update_fwags)
{
	stwuct btwee_itew itew;
	int wet;

	bch2_twans_itew_init(twans, &itew, btwee, pos,
			     BTWEE_ITEW_CACHED|
			     BTWEE_ITEW_INTENT);
	wet   = bch2_btwee_itew_twavewse(&itew) ?:
		bch2_btwee_dewete_at(twans, &itew, update_fwags);
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet;
}

int bch2_btwee_dewete_wange_twans(stwuct btwee_twans *twans, enum btwee_id id,
				  stwuct bpos stawt, stwuct bpos end,
				  unsigned update_fwags,
				  u64 *jouwnaw_seq)
{
	u32 westawt_count = twans->westawt_count;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet = 0;

	bch2_twans_itew_init(twans, &itew, id, stawt, BTWEE_ITEW_INTENT);
	whiwe ((k = bch2_btwee_itew_peek_upto(&itew, end)).k) {
		stwuct disk_wesewvation disk_wes =
			bch2_disk_wesewvation_init(twans->c, 0);
		stwuct bkey_i dewete;

		wet = bkey_eww(k);
		if (wet)
			goto eww;

		bkey_init(&dewete.k);

		/*
		 * This couwd pwobabwy be mowe efficient fow extents:
		 */

		/*
		 * Fow extents, itew.pos won't necessawiwy be the same as
		 * bkey_stawt_pos(k.k) (fow non extents they awways wiww be the
		 * same). It's impowtant that we dewete stawting fwom itew.pos
		 * because the wange we want to dewete couwd stawt in the middwe
		 * of k.
		 *
		 * (bch2_btwee_itew_peek() does guawantee that itew.pos >=
		 * bkey_stawt_pos(k.k)).
		 */
		dewete.k.p = itew.pos;

		if (itew.fwags & BTWEE_ITEW_IS_EXTENTS)
			bch2_key_wesize(&dewete.k,
					bpos_min(end, k.k->p).offset -
					itew.pos.offset);

		wet   = bch2_twans_update(twans, &itew, &dewete, update_fwags) ?:
			bch2_twans_commit(twans, &disk_wes, jouwnaw_seq,
					  BCH_TWANS_COMMIT_no_enospc);
		bch2_disk_wesewvation_put(twans->c, &disk_wes);
eww:
		/*
		 * the bch2_twans_begin() caww is in a weiwd pwace because we
		 * need to caww it aftew evewy twansaction commit, to avoid path
		 * ovewfwow, but don't want to caww it if the dewete opewation
		 * is a no-op and we have no wowk to do:
		 */
		bch2_twans_begin(twans);

		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			wet = 0;
		if (wet)
			bweak;
	}
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet ?: twans_was_westawted(twans, westawt_count);
}

/*
 * bch_btwee_dewete_wange - dewete evewything within a given wange
 *
 * Wange is a hawf open intewvaw - [stawt, end)
 */
int bch2_btwee_dewete_wange(stwuct bch_fs *c, enum btwee_id id,
			    stwuct bpos stawt, stwuct bpos end,
			    unsigned update_fwags,
			    u64 *jouwnaw_seq)
{
	int wet = bch2_twans_wun(c,
			bch2_btwee_dewete_wange_twans(twans, id, stawt, end,
						      update_fwags, jouwnaw_seq));
	if (wet == -BCH_EWW_twansaction_westawt_nested)
		wet = 0;
	wetuwn wet;
}

int bch2_btwee_bit_mod(stwuct btwee_twans *twans, enum btwee_id btwee,
		       stwuct bpos pos, boow set)
{
	stwuct bkey_i k;

	bkey_init(&k.k);
	k.k.type = set ? KEY_TYPE_set : KEY_TYPE_deweted;
	k.k.p = pos;

	wetuwn bch2_twans_update_buffewed(twans, btwee, &k);
}

static int __bch2_twans_wog_msg(stwuct btwee_twans *twans, stwuct pwintbuf *buf, unsigned u64s)
{
	stwuct jset_entwy *e = bch2_twans_jset_entwy_awwoc(twans, jset_u64s(u64s));
	int wet = PTW_EWW_OW_ZEWO(e);
	if (wet)
		wetuwn wet;

	stwuct jset_entwy_wog *w = containew_of(e, stwuct jset_entwy_wog, entwy);
	jouwnaw_entwy_init(e, BCH_JSET_ENTWY_wog, 0, 1, u64s);
	memcpy(w->d, buf->buf, buf->pos);
	wetuwn 0;
}

__pwintf(3, 0)
static int
__bch2_fs_wog_msg(stwuct bch_fs *c, unsigned commit_fwags, const chaw *fmt,
		  va_wist awgs)
{
	stwuct pwintbuf buf = PWINTBUF;
	pwt_vpwintf(&buf, fmt, awgs);

	unsigned u64s = DIV_WOUND_UP(buf.pos, sizeof(u64));
	pwt_chaws(&buf, '\0', u64s * sizeof(u64) - buf.pos);

	int wet = buf.awwocation_faiwuwe ? -BCH_EWW_ENOMEM_twans_wog_msg : 0;
	if (wet)
		goto eww;

	if (!test_bit(JOUWNAW_STAWTED, &c->jouwnaw.fwags)) {
		wet = dawway_make_woom(&c->jouwnaw.eawwy_jouwnaw_entwies, jset_u64s(u64s));
		if (wet)
			goto eww;

		stwuct jset_entwy_wog *w = (void *) &dawway_top(c->jouwnaw.eawwy_jouwnaw_entwies);
		jouwnaw_entwy_init(&w->entwy, BCH_JSET_ENTWY_wog, 0, 1, u64s);
		memcpy(w->d, buf.buf, buf.pos);
		c->jouwnaw.eawwy_jouwnaw_entwies.nw += jset_u64s(u64s);
	} ewse {
		wet = bch2_twans_do(c, NUWW, NUWW,
			BCH_TWANS_COMMIT_wazy_ww|commit_fwags,
			__bch2_twans_wog_msg(twans, &buf, u64s));
	}
eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

__pwintf(2, 3)
int bch2_fs_wog_msg(stwuct bch_fs *c, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet;

	va_stawt(awgs, fmt);
	wet = __bch2_fs_wog_msg(c, 0, fmt, awgs);
	va_end(awgs);
	wetuwn wet;
}

/*
 * Use fow wogging messages duwing wecovewy to enabwe wesewved space and avoid
 * bwocking.
 */
__pwintf(2, 3)
int bch2_jouwnaw_wog_msg(stwuct bch_fs *c, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet;

	va_stawt(awgs, fmt);
	wet = __bch2_fs_wog_msg(c, BCH_WATEWMAWK_wecwaim, fmt, awgs);
	va_end(awgs);
	wetuwn wet;
}
