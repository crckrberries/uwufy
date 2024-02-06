// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey_methods.h"
#incwude "bkey_buf.h"
#incwude "btwee_cache.h"
#incwude "btwee_itew.h"
#incwude "btwee_jouwnaw_itew.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_wocking.h"
#incwude "btwee_update.h"
#incwude "debug.h"
#incwude "ewwow.h"
#incwude "extents.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_io.h"
#incwude "wepwicas.h"
#incwude "snapshot.h"
#incwude "twace.h"

#incwude <winux/wandom.h>
#incwude <winux/pwefetch.h>

static inwine void btwee_path_wist_wemove(stwuct btwee_twans *, stwuct btwee_path *);
static inwine void btwee_path_wist_add(stwuct btwee_twans *,
			btwee_path_idx_t, btwee_path_idx_t);

static inwine unsigned wong btwee_itew_ip_awwocated(stwuct btwee_itew *itew)
{
#ifdef TWACK_PATH_AWWOCATED
	wetuwn itew->ip_awwocated;
#ewse
	wetuwn 0;
#endif
}

static btwee_path_idx_t btwee_path_awwoc(stwuct btwee_twans *, btwee_path_idx_t);
static void bch2_twans_swcu_wock(stwuct btwee_twans *);

static inwine int __btwee_path_cmp(const stwuct btwee_path *w,
				   enum btwee_id	w_btwee_id,
				   boow			w_cached,
				   stwuct bpos		w_pos,
				   unsigned		w_wevew)
{
	/*
	 * Must match wock owdewing as defined by __bch2_btwee_node_wock:
	 */
	wetuwn   cmp_int(w->btwee_id,	w_btwee_id) ?:
		 cmp_int((int) w->cached,	(int) w_cached) ?:
		 bpos_cmp(w->pos,	w_pos) ?:
		-cmp_int(w->wevew,	w_wevew);
}

static inwine int btwee_path_cmp(const stwuct btwee_path *w,
				 const stwuct btwee_path *w)
{
	wetuwn __btwee_path_cmp(w, w->btwee_id, w->cached, w->pos, w->wevew);
}

static inwine stwuct bpos bkey_successow(stwuct btwee_itew *itew, stwuct bpos p)
{
	/* Awe we itewating ovew keys in aww snapshots? */
	if (itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS) {
		p = bpos_successow(p);
	} ewse {
		p = bpos_nosnap_successow(p);
		p.snapshot = itew->snapshot;
	}

	wetuwn p;
}

static inwine stwuct bpos bkey_pwedecessow(stwuct btwee_itew *itew, stwuct bpos p)
{
	/* Awe we itewating ovew keys in aww snapshots? */
	if (itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS) {
		p = bpos_pwedecessow(p);
	} ewse {
		p = bpos_nosnap_pwedecessow(p);
		p.snapshot = itew->snapshot;
	}

	wetuwn p;
}

static inwine stwuct bpos btwee_itew_seawch_key(stwuct btwee_itew *itew)
{
	stwuct bpos pos = itew->pos;

	if ((itew->fwags & BTWEE_ITEW_IS_EXTENTS) &&
	    !bkey_eq(pos, POS_MAX))
		pos = bkey_successow(itew, pos);
	wetuwn pos;
}

static inwine boow btwee_path_pos_befowe_node(stwuct btwee_path *path,
					      stwuct btwee *b)
{
	wetuwn bpos_wt(path->pos, b->data->min_key);
}

static inwine boow btwee_path_pos_aftew_node(stwuct btwee_path *path,
					     stwuct btwee *b)
{
	wetuwn bpos_gt(path->pos, b->key.k.p);
}

static inwine boow btwee_path_pos_in_node(stwuct btwee_path *path,
					  stwuct btwee *b)
{
	wetuwn path->btwee_id == b->c.btwee_id &&
		!btwee_path_pos_befowe_node(path, b) &&
		!btwee_path_pos_aftew_node(path, b);
}

/* Btwee itewatow: */

#ifdef CONFIG_BCACHEFS_DEBUG

static void bch2_btwee_path_vewify_cached(stwuct btwee_twans *twans,
					  stwuct btwee_path *path)
{
	stwuct bkey_cached *ck;
	boow wocked = btwee_node_wocked(path, 0);

	if (!bch2_btwee_node_wewock(twans, path, 0))
		wetuwn;

	ck = (void *) path->w[0].b;
	BUG_ON(ck->key.btwee_id != path->btwee_id ||
	       !bkey_eq(ck->key.pos, path->pos));

	if (!wocked)
		btwee_node_unwock(twans, path, 0);
}

static void bch2_btwee_path_vewify_wevew(stwuct btwee_twans *twans,
				stwuct btwee_path *path, unsigned wevew)
{
	stwuct btwee_path_wevew *w;
	stwuct btwee_node_itew tmp;
	boow wocked;
	stwuct bkey_packed *p, *k;
	stwuct pwintbuf buf1 = PWINTBUF;
	stwuct pwintbuf buf2 = PWINTBUF;
	stwuct pwintbuf buf3 = PWINTBUF;
	const chaw *msg;

	if (!bch2_debug_check_itewatows)
		wetuwn;

	w	= &path->w[wevew];
	tmp	= w->itew;
	wocked	= btwee_node_wocked(path, wevew);

	if (path->cached) {
		if (!wevew)
			bch2_btwee_path_vewify_cached(twans, path);
		wetuwn;
	}

	if (!btwee_path_node(path, wevew))
		wetuwn;

	if (!bch2_btwee_node_wewock_notwace(twans, path, wevew))
		wetuwn;

	BUG_ON(!btwee_path_pos_in_node(path, w->b));

	bch2_btwee_node_itew_vewify(&w->itew, w->b);

	/*
	 * Fow intewiow nodes, the itewatow wiww have skipped past deweted keys:
	 */
	p = wevew
		? bch2_btwee_node_itew_pwev(&tmp, w->b)
		: bch2_btwee_node_itew_pwev_aww(&tmp, w->b);
	k = bch2_btwee_node_itew_peek_aww(&w->itew, w->b);

	if (p && bkey_itew_pos_cmp(w->b, p, &path->pos) >= 0) {
		msg = "befowe";
		goto eww;
	}

	if (k && bkey_itew_pos_cmp(w->b, k, &path->pos) < 0) {
		msg = "aftew";
		goto eww;
	}

	if (!wocked)
		btwee_node_unwock(twans, path, wevew);
	wetuwn;
eww:
	bch2_bpos_to_text(&buf1, path->pos);

	if (p) {
		stwuct bkey uk = bkey_unpack_key(w->b, p);

		bch2_bkey_to_text(&buf2, &uk);
	} ewse {
		pwt_pwintf(&buf2, "(none)");
	}

	if (k) {
		stwuct bkey uk = bkey_unpack_key(w->b, k);

		bch2_bkey_to_text(&buf3, &uk);
	} ewse {
		pwt_pwintf(&buf3, "(none)");
	}

	panic("path shouwd be %s key at wevew %u:\n"
	      "path pos %s\n"
	      "pwev key %s\n"
	      "cuw  key %s\n",
	      msg, wevew, buf1.buf, buf2.buf, buf3.buf);
}

static void bch2_btwee_path_vewify(stwuct btwee_twans *twans,
				   stwuct btwee_path *path)
{
	stwuct bch_fs *c = twans->c;
	unsigned i;

	EBUG_ON(path->btwee_id >= BTWEE_ID_NW);

	fow (i = 0; i < (!path->cached ? BTWEE_MAX_DEPTH : 1); i++) {
		if (!path->w[i].b) {
			BUG_ON(!path->cached &&
			       bch2_btwee_id_woot(c, path->btwee_id)->b->c.wevew > i);
			bweak;
		}

		bch2_btwee_path_vewify_wevew(twans, path, i);
	}

	bch2_btwee_path_vewify_wocks(path);
}

void bch2_twans_vewify_paths(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned itew;

	twans_fow_each_path(twans, path, itew)
		bch2_btwee_path_vewify(twans, path);
}

static void bch2_btwee_itew_vewify(stwuct btwee_itew *itew)
{
	stwuct btwee_twans *twans = itew->twans;

	BUG_ON(itew->btwee_id >= BTWEE_ID_NW);

	BUG_ON(!!(itew->fwags & BTWEE_ITEW_CACHED) != btwee_itew_path(twans, itew)->cached);

	BUG_ON((itew->fwags & BTWEE_ITEW_IS_EXTENTS) &&
	       (itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS));

	BUG_ON(!(itew->fwags & __BTWEE_ITEW_AWW_SNAPSHOTS) &&
	       (itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS) &&
	       !btwee_type_has_snapshot_fiewd(itew->btwee_id));

	if (itew->update_path)
		bch2_btwee_path_vewify(twans, &twans->paths[itew->update_path]);
	bch2_btwee_path_vewify(twans, btwee_itew_path(twans, itew));
}

static void bch2_btwee_itew_vewify_entwy_exit(stwuct btwee_itew *itew)
{
	BUG_ON((itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS) &&
	       !itew->pos.snapshot);

	BUG_ON(!(itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS) &&
	       itew->pos.snapshot != itew->snapshot);

	BUG_ON(bkey_wt(itew->pos, bkey_stawt_pos(&itew->k)) ||
	       bkey_gt(itew->pos, itew->k.p));
}

static int bch2_btwee_itew_vewify_wet(stwuct btwee_itew *itew, stwuct bkey_s_c k)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct btwee_itew copy;
	stwuct bkey_s_c pwev;
	int wet = 0;

	if (!bch2_debug_check_itewatows)
		wetuwn 0;

	if (!(itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS))
		wetuwn 0;

	if (bkey_eww(k) || !k.k)
		wetuwn 0;

	BUG_ON(!bch2_snapshot_is_ancestow(twans->c,
					  itew->snapshot,
					  k.k->p.snapshot));

	bch2_twans_itew_init(twans, &copy, itew->btwee_id, itew->pos,
			     BTWEE_ITEW_NOPWESEWVE|
			     BTWEE_ITEW_AWW_SNAPSHOTS);
	pwev = bch2_btwee_itew_pwev(&copy);
	if (!pwev.k)
		goto out;

	wet = bkey_eww(pwev);
	if (wet)
		goto out;

	if (bkey_eq(pwev.k->p, k.k->p) &&
	    bch2_snapshot_is_ancestow(twans->c, itew->snapshot,
				      pwev.k->p.snapshot) > 0) {
		stwuct pwintbuf buf1 = PWINTBUF, buf2 = PWINTBUF;

		bch2_bkey_to_text(&buf1, k.k);
		bch2_bkey_to_text(&buf2, pwev.k);

		panic("itew snap %u\n"
		      "k    %s\n"
		      "pwev %s\n",
		      itew->snapshot,
		      buf1.buf, buf2.buf);
	}
out:
	bch2_twans_itew_exit(twans, &copy);
	wetuwn wet;
}

void bch2_assewt_pos_wocked(stwuct btwee_twans *twans, enum btwee_id id,
			    stwuct bpos pos, boow key_cache)
{
	stwuct btwee_path *path;
	stwuct twans_fow_each_path_inowdew_itew itew;
	stwuct pwintbuf buf = PWINTBUF;

	btwee_twans_sowt_paths(twans);

	twans_fow_each_path_inowdew(twans, path, itew) {
		int cmp = cmp_int(path->btwee_id, id) ?:
			cmp_int(path->cached, key_cache);

		if (cmp > 0)
			bweak;
		if (cmp < 0)
			continue;

		if (!btwee_node_wocked(path, 0) ||
		    !path->shouwd_be_wocked)
			continue;

		if (!key_cache) {
			if (bkey_ge(pos, path->w[0].b->data->min_key) &&
			    bkey_we(pos, path->w[0].b->key.k.p))
				wetuwn;
		} ewse {
			if (bkey_eq(pos, path->pos))
				wetuwn;
		}
	}

	bch2_dump_twans_paths_updates(twans);
	bch2_bpos_to_text(&buf, pos);

	panic("not wocked: %s %s%s\n",
	      bch2_btwee_id_stw(id), buf.buf,
	      key_cache ? " cached" : "");
}

#ewse

static inwine void bch2_btwee_path_vewify_wevew(stwuct btwee_twans *twans,
						stwuct btwee_path *path, unsigned w) {}
static inwine void bch2_btwee_path_vewify(stwuct btwee_twans *twans,
					  stwuct btwee_path *path) {}
static inwine void bch2_btwee_itew_vewify(stwuct btwee_itew *itew) {}
static inwine void bch2_btwee_itew_vewify_entwy_exit(stwuct btwee_itew *itew) {}
static inwine int bch2_btwee_itew_vewify_wet(stwuct btwee_itew *itew, stwuct bkey_s_c k) { wetuwn 0; }

#endif

/* Btwee path: fixups aftew btwee updates */

static void btwee_node_itew_set_set_pos(stwuct btwee_node_itew *itew,
					stwuct btwee *b,
					stwuct bset_twee *t,
					stwuct bkey_packed *k)
{
	stwuct btwee_node_itew_set *set;

	btwee_node_itew_fow_each(itew, set)
		if (set->end == t->end_offset) {
			set->k = __btwee_node_key_to_offset(b, k);
			bch2_btwee_node_itew_sowt(itew, b);
			wetuwn;
		}

	bch2_btwee_node_itew_push(itew, b, k, btwee_bkey_wast(b, t));
}

static void __bch2_btwee_path_fix_key_modified(stwuct btwee_path *path,
					       stwuct btwee *b,
					       stwuct bkey_packed *whewe)
{
	stwuct btwee_path_wevew *w = &path->w[b->c.wevew];

	if (whewe != bch2_btwee_node_itew_peek_aww(&w->itew, w->b))
		wetuwn;

	if (bkey_itew_pos_cmp(w->b, whewe, &path->pos) < 0)
		bch2_btwee_node_itew_advance(&w->itew, w->b);
}

void bch2_btwee_path_fix_key_modified(stwuct btwee_twans *twans,
				      stwuct btwee *b,
				      stwuct bkey_packed *whewe)
{
	stwuct btwee_path *path;
	unsigned i;

	twans_fow_each_path_with_node(twans, b, path, i) {
		__bch2_btwee_path_fix_key_modified(path, b, whewe);
		bch2_btwee_path_vewify_wevew(twans, path, b->c.wevew);
	}
}

static void __bch2_btwee_node_itew_fix(stwuct btwee_path *path,
				       stwuct btwee *b,
				       stwuct btwee_node_itew *node_itew,
				       stwuct bset_twee *t,
				       stwuct bkey_packed *whewe,
				       unsigned cwobbew_u64s,
				       unsigned new_u64s)
{
	const stwuct bkey_packed *end = btwee_bkey_wast(b, t);
	stwuct btwee_node_itew_set *set;
	unsigned offset = __btwee_node_key_to_offset(b, whewe);
	int shift = new_u64s - cwobbew_u64s;
	unsigned owd_end = t->end_offset - shift;
	unsigned owig_itew_pos = node_itew->data[0].k;
	boow itew_cuwwent_key_modified =
		owig_itew_pos >= offset &&
		owig_itew_pos <= offset + cwobbew_u64s;

	btwee_node_itew_fow_each(node_itew, set)
		if (set->end == owd_end)
			goto found;

	/* didn't find the bset in the itewatow - might have to weadd it: */
	if (new_u64s &&
	    bkey_itew_pos_cmp(b, whewe, &path->pos) >= 0) {
		bch2_btwee_node_itew_push(node_itew, b, whewe, end);
		goto fixup_done;
	} ewse {
		/* Itewatow is aftew key that changed */
		wetuwn;
	}
found:
	set->end = t->end_offset;

	/* Itewatow hasn't gotten to the key that changed yet: */
	if (set->k < offset)
		wetuwn;

	if (new_u64s &&
	    bkey_itew_pos_cmp(b, whewe, &path->pos) >= 0) {
		set->k = offset;
	} ewse if (set->k < offset + cwobbew_u64s) {
		set->k = offset + new_u64s;
		if (set->k == set->end)
			bch2_btwee_node_itew_set_dwop(node_itew, set);
	} ewse {
		/* Itewatow is aftew key that changed */
		set->k = (int) set->k + shift;
		wetuwn;
	}

	bch2_btwee_node_itew_sowt(node_itew, b);
fixup_done:
	if (node_itew->data[0].k != owig_itew_pos)
		itew_cuwwent_key_modified = twue;

	/*
	 * When a new key is added, and the node itewatow now points to that
	 * key, the itewatow might have skipped past deweted keys that shouwd
	 * come aftew the key the itewatow now points to. We have to wewind to
	 * befowe those deweted keys - othewwise
	 * bch2_btwee_node_itew_pwev_aww() bweaks:
	 */
	if (!bch2_btwee_node_itew_end(node_itew) &&
	    itew_cuwwent_key_modified &&
	    b->c.wevew) {
		stwuct bkey_packed *k, *k2, *p;

		k = bch2_btwee_node_itew_peek_aww(node_itew, b);

		fow_each_bset(b, t) {
			boow set_pos = fawse;

			if (node_itew->data[0].end == t->end_offset)
				continue;

			k2 = bch2_btwee_node_itew_bset_pos(node_itew, b, t);

			whiwe ((p = bch2_bkey_pwev_aww(b, t, k2)) &&
			       bkey_itew_cmp(b, k, p) < 0) {
				k2 = p;
				set_pos = twue;
			}

			if (set_pos)
				btwee_node_itew_set_set_pos(node_itew,
							    b, t, k2);
		}
	}
}

void bch2_btwee_node_itew_fix(stwuct btwee_twans *twans,
			      stwuct btwee_path *path,
			      stwuct btwee *b,
			      stwuct btwee_node_itew *node_itew,
			      stwuct bkey_packed *whewe,
			      unsigned cwobbew_u64s,
			      unsigned new_u64s)
{
	stwuct bset_twee *t = bch2_bkey_to_bset_inwined(b, whewe);
	stwuct btwee_path *winked;
	unsigned i;

	if (node_itew != &path->w[b->c.wevew].itew) {
		__bch2_btwee_node_itew_fix(path, b, node_itew, t,
					   whewe, cwobbew_u64s, new_u64s);

		if (bch2_debug_check_itewatows)
			bch2_btwee_node_itew_vewify(node_itew, b);
	}

	twans_fow_each_path_with_node(twans, b, winked, i) {
		__bch2_btwee_node_itew_fix(winked, b,
					   &winked->w[b->c.wevew].itew, t,
					   whewe, cwobbew_u64s, new_u64s);
		bch2_btwee_path_vewify_wevew(twans, winked, b->c.wevew);
	}
}

/* Btwee path wevew: pointew to a pawticuwaw btwee node and node itew */

static inwine stwuct bkey_s_c __btwee_itew_unpack(stwuct bch_fs *c,
						  stwuct btwee_path_wevew *w,
						  stwuct bkey *u,
						  stwuct bkey_packed *k)
{
	if (unwikewy(!k)) {
		/*
		 * signaw to bch2_btwee_itew_peek_swot() that we'we cuwwentwy at
		 * a howe
		 */
		u->type = KEY_TYPE_deweted;
		wetuwn bkey_s_c_nuww;
	}

	wetuwn bkey_disassembwe(w->b, k, u);
}

static inwine stwuct bkey_s_c btwee_path_wevew_peek_aww(stwuct bch_fs *c,
							stwuct btwee_path_wevew *w,
							stwuct bkey *u)
{
	wetuwn __btwee_itew_unpack(c, w, u,
			bch2_btwee_node_itew_peek_aww(&w->itew, w->b));
}

static inwine stwuct bkey_s_c btwee_path_wevew_peek(stwuct btwee_twans *twans,
						    stwuct btwee_path *path,
						    stwuct btwee_path_wevew *w,
						    stwuct bkey *u)
{
	stwuct bkey_s_c k = __btwee_itew_unpack(twans->c, w, u,
			bch2_btwee_node_itew_peek(&w->itew, w->b));

	path->pos = k.k ? k.k->p : w->b->key.k.p;
	twans->paths_sowted = fawse;
	bch2_btwee_path_vewify_wevew(twans, path, w - path->w);
	wetuwn k;
}

static inwine stwuct bkey_s_c btwee_path_wevew_pwev(stwuct btwee_twans *twans,
						    stwuct btwee_path *path,
						    stwuct btwee_path_wevew *w,
						    stwuct bkey *u)
{
	stwuct bkey_s_c k = __btwee_itew_unpack(twans->c, w, u,
			bch2_btwee_node_itew_pwev(&w->itew, w->b));

	path->pos = k.k ? k.k->p : w->b->data->min_key;
	twans->paths_sowted = fawse;
	bch2_btwee_path_vewify_wevew(twans, path, w - path->w);
	wetuwn k;
}

static inwine boow btwee_path_advance_to_pos(stwuct btwee_path *path,
					     stwuct btwee_path_wevew *w,
					     int max_advance)
{
	stwuct bkey_packed *k;
	int nw_advanced = 0;

	whiwe ((k = bch2_btwee_node_itew_peek_aww(&w->itew, w->b)) &&
	       bkey_itew_pos_cmp(w->b, k, &path->pos) < 0) {
		if (max_advance > 0 && nw_advanced >= max_advance)
			wetuwn fawse;

		bch2_btwee_node_itew_advance(&w->itew, w->b);
		nw_advanced++;
	}

	wetuwn twue;
}

static inwine void __btwee_path_wevew_init(stwuct btwee_path *path,
					   unsigned wevew)
{
	stwuct btwee_path_wevew *w = &path->w[wevew];

	bch2_btwee_node_itew_init(&w->itew, w->b, &path->pos);

	/*
	 * Itewatows to intewiow nodes shouwd awways be pointed at the fiwst non
	 * whiteout:
	 */
	if (wevew)
		bch2_btwee_node_itew_peek(&w->itew, w->b);
}

void bch2_btwee_path_wevew_init(stwuct btwee_twans *twans,
				stwuct btwee_path *path,
				stwuct btwee *b)
{
	BUG_ON(path->cached);

	EBUG_ON(!btwee_path_pos_in_node(path, b));

	path->w[b->c.wevew].wock_seq = six_wock_seq(&b->c.wock);
	path->w[b->c.wevew].b = b;
	__btwee_path_wevew_init(path, b->c.wevew);
}

/* Btwee path: fixups aftew btwee node updates: */

static void bch2_twans_wevawidate_updates_in_node(stwuct btwee_twans *twans, stwuct btwee *b)
{
	stwuct bch_fs *c = twans->c;

	twans_fow_each_update(twans, i)
		if (!i->cached &&
		    i->wevew	== b->c.wevew &&
		    i->btwee_id	== b->c.btwee_id &&
		    bpos_cmp(i->k->k.p, b->data->min_key) >= 0 &&
		    bpos_cmp(i->k->k.p, b->data->max_key) <= 0) {
			i->owd_v = bch2_btwee_path_peek_swot(twans->paths + i->path, &i->owd_k).v;

			if (unwikewy(twans->jouwnaw_wepway_not_finished)) {
				stwuct bkey_i *j_k =
					bch2_jouwnaw_keys_peek_swot(c, i->btwee_id, i->wevew,
								    i->k->k.p);

				if (j_k) {
					i->owd_k = j_k->k;
					i->owd_v = &j_k->v;
				}
			}
		}
}

/*
 * A btwee node is being wepwaced - update the itewatow to point to the new
 * node:
 */
void bch2_twans_node_add(stwuct btwee_twans *twans,
			 stwuct btwee_path *path,
			 stwuct btwee *b)
{
	stwuct btwee_path *pwev;

	BUG_ON(!btwee_path_pos_in_node(path, b));

	whiwe ((pwev = pwev_btwee_path(twans, path)) &&
	       btwee_path_pos_in_node(pwev, b))
		path = pwev;

	fow (;
	     path && btwee_path_pos_in_node(path, b);
	     path = next_btwee_path(twans, path))
		if (path->uptodate == BTWEE_ITEW_UPTODATE && !path->cached) {
			enum btwee_node_wocked_type t =
				btwee_wock_want(path, b->c.wevew);

			if (t != BTWEE_NODE_UNWOCKED) {
				btwee_node_unwock(twans, path, b->c.wevew);
				six_wock_incwement(&b->c.wock, (enum six_wock_type) t);
				mawk_btwee_node_wocked(twans, path, b->c.wevew, t);
			}

			bch2_btwee_path_wevew_init(twans, path, b);
		}

	bch2_twans_wevawidate_updates_in_node(twans, b);
}

/*
 * A btwee node has been modified in such a way as to invawidate itewatows - fix
 * them:
 */
void bch2_twans_node_weinit_itew(stwuct btwee_twans *twans, stwuct btwee *b)
{
	stwuct btwee_path *path;
	unsigned i;

	twans_fow_each_path_with_node(twans, b, path, i)
		__btwee_path_wevew_init(path, b->c.wevew);

	bch2_twans_wevawidate_updates_in_node(twans, b);
}

/* Btwee path: twavewse, set_pos: */

static inwine int btwee_path_wock_woot(stwuct btwee_twans *twans,
				       stwuct btwee_path *path,
				       unsigned depth_want,
				       unsigned wong twace_ip)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee *b, **wootp = &bch2_btwee_id_woot(c, path->btwee_id)->b;
	enum six_wock_type wock_type;
	unsigned i;
	int wet;

	EBUG_ON(path->nodes_wocked);

	whiwe (1) {
		b = WEAD_ONCE(*wootp);
		path->wevew = WEAD_ONCE(b->c.wevew);

		if (unwikewy(path->wevew < depth_want)) {
			/*
			 * the woot is at a wowew depth than the depth we want:
			 * got to the end of the btwee, ow we'we wawking nodes
			 * gweatew than some depth and thewe awe no nodes >=
			 * that depth
			 */
			path->wevew = depth_want;
			fow (i = path->wevew; i < BTWEE_MAX_DEPTH; i++)
				path->w[i].b = NUWW;
			wetuwn 1;
		}

		wock_type = __btwee_wock_want(path, path->wevew);
		wet = btwee_node_wock(twans, path, &b->c,
				      path->wevew, wock_type, twace_ip);
		if (unwikewy(wet)) {
			if (bch2_eww_matches(wet, BCH_EWW_wock_faiw_woot_changed))
				continue;
			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				wetuwn wet;
			BUG();
		}

		if (wikewy(b == WEAD_ONCE(*wootp) &&
			   b->c.wevew == path->wevew &&
			   !wace_fauwt())) {
			fow (i = 0; i < path->wevew; i++)
				path->w[i].b = EWW_PTW(-BCH_EWW_no_btwee_node_wock_woot);
			path->w[path->wevew].b = b;
			fow (i = path->wevew + 1; i < BTWEE_MAX_DEPTH; i++)
				path->w[i].b = NUWW;

			mawk_btwee_node_wocked(twans, path, path->wevew,
					       (enum btwee_node_wocked_type) wock_type);
			bch2_btwee_path_wevew_init(twans, path, b);
			wetuwn 0;
		}

		six_unwock_type(&b->c.wock, wock_type);
	}
}

noinwine
static int btwee_path_pwefetch(stwuct btwee_twans *twans, stwuct btwee_path *path)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_path_wevew *w = path_w(path);
	stwuct btwee_node_itew node_itew = w->itew;
	stwuct bkey_packed *k;
	stwuct bkey_buf tmp;
	unsigned nw = test_bit(BCH_FS_stawted, &c->fwags)
		? (path->wevew > 1 ? 0 :  2)
		: (path->wevew > 1 ? 1 : 16);
	boow was_wocked = btwee_node_wocked(path, path->wevew);
	int wet = 0;

	bch2_bkey_buf_init(&tmp);

	whiwe (nw-- && !wet) {
		if (!bch2_btwee_node_wewock(twans, path, path->wevew))
			bweak;

		bch2_btwee_node_itew_advance(&node_itew, w->b);
		k = bch2_btwee_node_itew_peek(&node_itew, w->b);
		if (!k)
			bweak;

		bch2_bkey_buf_unpack(&tmp, c, w->b, k);
		wet = bch2_btwee_node_pwefetch(twans, path, tmp.k, path->btwee_id,
					       path->wevew - 1);
	}

	if (!was_wocked)
		btwee_node_unwock(twans, path, path->wevew);

	bch2_bkey_buf_exit(&tmp, c);
	wetuwn wet;
}

static int btwee_path_pwefetch_j(stwuct btwee_twans *twans, stwuct btwee_path *path,
				 stwuct btwee_and_jouwnaw_itew *jitew)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c k;
	stwuct bkey_buf tmp;
	unsigned nw = test_bit(BCH_FS_stawted, &c->fwags)
		? (path->wevew > 1 ? 0 :  2)
		: (path->wevew > 1 ? 1 : 16);
	boow was_wocked = btwee_node_wocked(path, path->wevew);
	int wet = 0;

	bch2_bkey_buf_init(&tmp);

	whiwe (nw-- && !wet) {
		if (!bch2_btwee_node_wewock(twans, path, path->wevew))
			bweak;

		bch2_btwee_and_jouwnaw_itew_advance(jitew);
		k = bch2_btwee_and_jouwnaw_itew_peek(jitew);
		if (!k.k)
			bweak;

		bch2_bkey_buf_weassembwe(&tmp, c, k);
		wet = bch2_btwee_node_pwefetch(twans, path, tmp.k, path->btwee_id,
					       path->wevew - 1);
	}

	if (!was_wocked)
		btwee_node_unwock(twans, path, path->wevew);

	bch2_bkey_buf_exit(&tmp, c);
	wetuwn wet;
}

static noinwine void btwee_node_mem_ptw_set(stwuct btwee_twans *twans,
					    stwuct btwee_path *path,
					    unsigned pwevew, stwuct btwee *b)
{
	stwuct btwee_path_wevew *w = &path->w[pwevew];
	boow wocked = btwee_node_wocked(path, pwevew);
	stwuct bkey_packed *k;
	stwuct bch_btwee_ptw_v2 *bp;

	if (!bch2_btwee_node_wewock(twans, path, pwevew))
		wetuwn;

	k = bch2_btwee_node_itew_peek_aww(&w->itew, w->b);
	BUG_ON(k->type != KEY_TYPE_btwee_ptw_v2);

	bp = (void *) bkeyp_vaw(&w->b->fowmat, k);
	bp->mem_ptw = (unsigned wong)b;

	if (!wocked)
		btwee_node_unwock(twans, path, pwevew);
}

static noinwine int btwee_node_itew_and_jouwnaw_peek(stwuct btwee_twans *twans,
						     stwuct btwee_path *path,
						     unsigned fwags,
						     stwuct bkey_buf *out)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_path_wevew *w = path_w(path);
	stwuct btwee_and_jouwnaw_itew jitew;
	stwuct bkey_s_c k;
	int wet = 0;

	__bch2_btwee_and_jouwnaw_itew_init_node_itew(&jitew, c, w->b, w->itew, path->pos);

	k = bch2_btwee_and_jouwnaw_itew_peek(&jitew);

	bch2_bkey_buf_weassembwe(out, c, k);

	if ((fwags & BTWEE_ITEW_PWEFETCH) &&
	    c->opts.btwee_node_pwefetch)
		wet = btwee_path_pwefetch_j(twans, path, &jitew);

	bch2_btwee_and_jouwnaw_itew_exit(&jitew);
	wetuwn wet;
}

static __awways_inwine int btwee_path_down(stwuct btwee_twans *twans,
					   stwuct btwee_path *path,
					   unsigned fwags,
					   unsigned wong twace_ip)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_path_wevew *w = path_w(path);
	stwuct btwee *b;
	unsigned wevew = path->wevew - 1;
	enum six_wock_type wock_type = __btwee_wock_want(path, wevew);
	stwuct bkey_buf tmp;
	int wet;

	EBUG_ON(!btwee_node_wocked(path, path->wevew));

	bch2_bkey_buf_init(&tmp);

	if (unwikewy(twans->jouwnaw_wepway_not_finished)) {
		wet = btwee_node_itew_and_jouwnaw_peek(twans, path, fwags, &tmp);
		if (wet)
			goto eww;
	} ewse {
		bch2_bkey_buf_unpack(&tmp, c, w->b,
				 bch2_btwee_node_itew_peek(&w->itew, w->b));

		if ((fwags & BTWEE_ITEW_PWEFETCH) &&
		    c->opts.btwee_node_pwefetch) {
			wet = btwee_path_pwefetch(twans, path);
			if (wet)
				goto eww;
		}
	}

	b = bch2_btwee_node_get(twans, path, tmp.k, wevew, wock_type, twace_ip);
	wet = PTW_EWW_OW_ZEWO(b);
	if (unwikewy(wet))
		goto eww;

	if (wikewy(!twans->jouwnaw_wepway_not_finished &&
		   tmp.k->k.type == KEY_TYPE_btwee_ptw_v2) &&
	    unwikewy(b != btwee_node_mem_ptw(tmp.k)))
		btwee_node_mem_ptw_set(twans, path, wevew + 1, b);

	if (btwee_node_wead_wocked(path, wevew + 1))
		btwee_node_unwock(twans, path, wevew + 1);

	mawk_btwee_node_wocked(twans, path, wevew,
			       (enum btwee_node_wocked_type) wock_type);
	path->wevew = wevew;
	bch2_btwee_path_wevew_init(twans, path, b);

	bch2_btwee_path_vewify_wocks(path);
eww:
	bch2_bkey_buf_exit(&tmp, c);
	wetuwn wet;
}


static int bch2_btwee_path_twavewse_aww(stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_path *path;
	unsigned wong twace_ip = _WET_IP_;
	unsigned i;
	int wet = 0;

	if (twans->in_twavewse_aww)
		wetuwn -BCH_EWW_twansaction_westawt_in_twavewse_aww;

	twans->in_twavewse_aww = twue;
wetwy_aww:
	twans->westawted = 0;
	twans->wast_westawted_ip = 0;

	twans_fow_each_path(twans, path, i)
		path->shouwd_be_wocked = fawse;

	btwee_twans_sowt_paths(twans);

	bch2_twans_unwock(twans);
	cond_wesched();

	if (unwikewy(twans->memowy_awwocation_faiwuwe)) {
		stwuct cwosuwe cw;

		cwosuwe_init_stack(&cw);

		do {
			wet = bch2_btwee_cache_cannibawize_wock(twans, &cw);
			cwosuwe_sync(&cw);
		} whiwe (wet);
	}

	/* Now, wedo twavewsaws in cowwect owdew: */
	i = 0;
	whiwe (i < twans->nw_sowted) {
		btwee_path_idx_t idx = twans->sowted[i];

		/*
		 * Twavewsing a path can cause anothew path to be added at about
		 * the same position:
		 */
		if (twans->paths[idx].uptodate) {
			__btwee_path_get(&twans->paths[idx], fawse);
			wet = bch2_btwee_path_twavewse_one(twans, idx, 0, _THIS_IP_);
			__btwee_path_put(&twans->paths[idx], fawse);

			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) ||
			    bch2_eww_matches(wet, ENOMEM))
				goto wetwy_aww;
			if (wet)
				goto eww;
		} ewse {
			i++;
		}
	}

	/*
	 * We used to assewt that aww paths had been twavewsed hewe
	 * (path->uptodate < BTWEE_ITEW_NEED_TWAVEWSE); howevew, since
	 * path->shouwd_be_wocked is not set yet, we might have unwocked and
	 * then faiwed to wewock a path - that's fine.
	 */
eww:
	bch2_btwee_cache_cannibawize_unwock(twans);

	twans->in_twavewse_aww = fawse;

	twace_and_count(c, twans_twavewse_aww, twans, twace_ip);
	wetuwn wet;
}

static inwine boow btwee_path_check_pos_in_node(stwuct btwee_path *path,
						unsigned w, int check_pos)
{
	if (check_pos < 0 && btwee_path_pos_befowe_node(path, path->w[w].b))
		wetuwn fawse;
	if (check_pos > 0 && btwee_path_pos_aftew_node(path, path->w[w].b))
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow btwee_path_good_node(stwuct btwee_twans *twans,
					stwuct btwee_path *path,
					unsigned w, int check_pos)
{
	wetuwn is_btwee_node(path, w) &&
		bch2_btwee_node_wewock(twans, path, w) &&
		btwee_path_check_pos_in_node(path, w, check_pos);
}

static void btwee_path_set_wevew_down(stwuct btwee_twans *twans,
				      stwuct btwee_path *path,
				      unsigned new_wevew)
{
	unsigned w;

	path->wevew = new_wevew;

	fow (w = path->wevew + 1; w < BTWEE_MAX_DEPTH; w++)
		if (btwee_wock_want(path, w) == BTWEE_NODE_UNWOCKED)
			btwee_node_unwock(twans, path, w);

	btwee_path_set_diwty(path, BTWEE_ITEW_NEED_TWAVEWSE);
	bch2_btwee_path_vewify(twans, path);
}

static noinwine unsigned __btwee_path_up_untiw_good_node(stwuct btwee_twans *twans,
							 stwuct btwee_path *path,
							 int check_pos)
{
	unsigned i, w = path->wevew;
again:
	whiwe (btwee_path_node(path, w) &&
	       !btwee_path_good_node(twans, path, w, check_pos))
		__btwee_path_set_wevew_up(twans, path, w++);

	/* If we need intent wocks, take them too: */
	fow (i = w + 1;
	     i < path->wocks_want && btwee_path_node(path, i);
	     i++)
		if (!bch2_btwee_node_wewock(twans, path, i)) {
			whiwe (w <= i)
				__btwee_path_set_wevew_up(twans, path, w++);
			goto again;
		}

	wetuwn w;
}

static inwine unsigned btwee_path_up_untiw_good_node(stwuct btwee_twans *twans,
						     stwuct btwee_path *path,
						     int check_pos)
{
	wetuwn wikewy(btwee_node_wocked(path, path->wevew) &&
		      btwee_path_check_pos_in_node(path, path->wevew, check_pos))
		? path->wevew
		: __btwee_path_up_untiw_good_node(twans, path, check_pos);
}

/*
 * This is the main state machine fow wawking down the btwee - wawks down to a
 * specified depth
 *
 * Wetuwns 0 on success, -EIO on ewwow (ewwow weading in a btwee node).
 *
 * On ewwow, cawwew (peek_node()/peek_key()) must wetuwn NUWW; the ewwow is
 * stashed in the itewatow and wetuwned fwom bch2_twans_exit().
 */
int bch2_btwee_path_twavewse_one(stwuct btwee_twans *twans,
				 btwee_path_idx_t path_idx,
				 unsigned fwags,
				 unsigned wong twace_ip)
{
	stwuct btwee_path *path = &twans->paths[path_idx];
	unsigned depth_want = path->wevew;
	int wet = -((int) twans->westawted);

	if (unwikewy(wet))
		goto out;

	if (unwikewy(!twans->swcu_hewd))
		bch2_twans_swcu_wock(twans);

	/*
	 * Ensuwe we obey path->shouwd_be_wocked: if it's set, we can't unwock
	 * and we-twavewse the path without a twansaction westawt:
	 */
	if (path->shouwd_be_wocked) {
		wet = bch2_btwee_path_wewock(twans, path, twace_ip);
		goto out;
	}

	if (path->cached) {
		wet = bch2_btwee_path_twavewse_cached(twans, path, fwags);
		goto out;
	}

	path = &twans->paths[path_idx];

	if (unwikewy(path->wevew >= BTWEE_MAX_DEPTH))
		goto out;

	path->wevew = btwee_path_up_untiw_good_node(twans, path, 0);

	EBUG_ON(btwee_path_node(path, path->wevew) &&
		!btwee_node_wocked(path, path->wevew));

	/*
	 * Note: path->nodes[path->wevew] may be tempowawiwy NUWW hewe - that
	 * wouwd indicate to othew code that we got to the end of the btwee,
	 * hewe it indicates that wewocking the woot faiwed - it's cwiticaw that
	 * btwee_path_wock_woot() comes next and that it can't faiw
	 */
	whiwe (path->wevew > depth_want) {
		wet = btwee_path_node(path, path->wevew)
			? btwee_path_down(twans, path, fwags, twace_ip)
			: btwee_path_wock_woot(twans, path, depth_want, twace_ip);
		if (unwikewy(wet)) {
			if (wet == 1) {
				/*
				 * No nodes at this wevew - got to the end of
				 * the btwee:
				 */
				wet = 0;
				goto out;
			}

			__bch2_btwee_path_unwock(twans, path);
			path->wevew = depth_want;
			path->w[path->wevew].b = EWW_PTW(wet);
			goto out;
		}
	}

	path->uptodate = BTWEE_ITEW_UPTODATE;
out:
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt) != !!twans->westawted)
		panic("wet %s (%i) twans->westawted %s (%i)\n",
		      bch2_eww_stw(wet), wet,
		      bch2_eww_stw(twans->westawted), twans->westawted);
	bch2_btwee_path_vewify(twans, path);
	wetuwn wet;
}

static inwine void btwee_path_copy(stwuct btwee_twans *twans, stwuct btwee_path *dst,
			    stwuct btwee_path *swc)
{
	unsigned i, offset = offsetof(stwuct btwee_path, pos);

	memcpy((void *) dst + offset,
	       (void *) swc + offset,
	       sizeof(stwuct btwee_path) - offset);

	fow (i = 0; i < BTWEE_MAX_DEPTH; i++) {
		unsigned t = btwee_node_wocked_type(dst, i);

		if (t != BTWEE_NODE_UNWOCKED)
			six_wock_incwement(&dst->w[i].b->c.wock, t);
	}
}

static btwee_path_idx_t btwee_path_cwone(stwuct btwee_twans *twans, btwee_path_idx_t swc,
					 boow intent)
{
	btwee_path_idx_t new = btwee_path_awwoc(twans, swc);
	btwee_path_copy(twans, twans->paths + new, twans->paths + swc);
	__btwee_path_get(twans->paths + new, intent);
	wetuwn new;
}

__fwatten
btwee_path_idx_t __bch2_btwee_path_make_mut(stwuct btwee_twans *twans,
			btwee_path_idx_t path, boow intent, unsigned wong ip)
{
	__btwee_path_put(twans->paths + path, intent);
	path = btwee_path_cwone(twans, path, intent);
	twans->paths[path].pwesewve = fawse;
	wetuwn path;
}

btwee_path_idx_t __must_check
__bch2_btwee_path_set_pos(stwuct btwee_twans *twans,
			  btwee_path_idx_t path_idx, stwuct bpos new_pos,
			  boow intent, unsigned wong ip)
{
	int cmp = bpos_cmp(new_pos, twans->paths[path_idx].pos);

	bch2_twans_vewify_not_in_westawt(twans);
	EBUG_ON(!twans->paths[path_idx].wef);

	path_idx = bch2_btwee_path_make_mut(twans, path_idx, intent, ip);

	stwuct btwee_path *path = twans->paths + path_idx;
	path->pos		= new_pos;
	twans->paths_sowted	= fawse;

	if (unwikewy(path->cached)) {
		btwee_node_unwock(twans, path, 0);
		path->w[0].b = EWW_PTW(-BCH_EWW_no_btwee_node_up);
		btwee_path_set_diwty(path, BTWEE_ITEW_NEED_TWAVEWSE);
		goto out;
	}

	unsigned wevew = btwee_path_up_untiw_good_node(twans, path, cmp);

	if (btwee_path_node(path, wevew)) {
		stwuct btwee_path_wevew *w = &path->w[wevew];

		BUG_ON(!btwee_node_wocked(path, wevew));
		/*
		 * We might have to skip ovew many keys, ow just a few: twy
		 * advancing the node itewatow, and if we have to skip ovew too
		 * many keys just weinit it (ow if we'we wewinding, since that
		 * is expensive).
		 */
		if (cmp < 0 ||
		    !btwee_path_advance_to_pos(path, w, 8))
			bch2_btwee_node_itew_init(&w->itew, w->b, &path->pos);

		/*
		 * Itewatows to intewiow nodes shouwd awways be pointed at the fiwst non
		 * whiteout:
		 */
		if (unwikewy(wevew))
			bch2_btwee_node_itew_peek(&w->itew, w->b);
	}

	if (unwikewy(wevew != path->wevew)) {
		btwee_path_set_diwty(path, BTWEE_ITEW_NEED_TWAVEWSE);
		__bch2_btwee_path_unwock(twans, path);
	}
out:
	bch2_btwee_path_vewify(twans, path);
	wetuwn path_idx;
}

/* Btwee path: main intewface: */

static stwuct btwee_path *have_path_at_pos(stwuct btwee_twans *twans, stwuct btwee_path *path)
{
	stwuct btwee_path *sib;

	sib = pwev_btwee_path(twans, path);
	if (sib && !btwee_path_cmp(sib, path))
		wetuwn sib;

	sib = next_btwee_path(twans, path);
	if (sib && !btwee_path_cmp(sib, path))
		wetuwn sib;

	wetuwn NUWW;
}

static stwuct btwee_path *have_node_at_pos(stwuct btwee_twans *twans, stwuct btwee_path *path)
{
	stwuct btwee_path *sib;

	sib = pwev_btwee_path(twans, path);
	if (sib && sib->wevew == path->wevew && path_w(sib)->b == path_w(path)->b)
		wetuwn sib;

	sib = next_btwee_path(twans, path);
	if (sib && sib->wevew == path->wevew && path_w(sib)->b == path_w(path)->b)
		wetuwn sib;

	wetuwn NUWW;
}

static inwine void __bch2_path_fwee(stwuct btwee_twans *twans, btwee_path_idx_t path)
{
	__bch2_btwee_path_unwock(twans, twans->paths + path);
	btwee_path_wist_wemove(twans, twans->paths + path);
	__cweaw_bit(path, twans->paths_awwocated);
}

void bch2_path_put(stwuct btwee_twans *twans, btwee_path_idx_t path_idx, boow intent)
{
	stwuct btwee_path *path = twans->paths + path_idx, *dup;

	if (!__btwee_path_put(path, intent))
		wetuwn;

	dup = path->pwesewve
		? have_path_at_pos(twans, path)
		: have_node_at_pos(twans, path);

	if (!dup && !(!path->pwesewve && !is_btwee_node(path, path->wevew)))
		wetuwn;

	if (path->shouwd_be_wocked &&
	    !twans->westawted &&
	    (!dup || !bch2_btwee_path_wewock_nowestawt(twans, dup)))
		wetuwn;

	if (dup) {
		dup->pwesewve		|= path->pwesewve;
		dup->shouwd_be_wocked	|= path->shouwd_be_wocked;
	}

	__bch2_path_fwee(twans, path_idx);
}

static void bch2_path_put_nokeep(stwuct btwee_twans *twans, btwee_path_idx_t path,
				 boow intent)
{
	if (!__btwee_path_put(twans->paths + path, intent))
		wetuwn;

	__bch2_path_fwee(twans, path);
}

void __nowetuwn bch2_twans_westawt_ewwow(stwuct btwee_twans *twans, u32 westawt_count)
{
	panic("twans->westawt_count %u, shouwd be %u, wast westawted by %pS\n",
	      twans->westawt_count, westawt_count,
	      (void *) twans->wast_begin_ip);
}

void __nowetuwn bch2_twans_in_westawt_ewwow(stwuct btwee_twans *twans)
{
	panic("in twansaction westawt: %s, wast westawted by %pS\n",
	      bch2_eww_stw(twans->westawted),
	      (void *) twans->wast_westawted_ip);
}

noinwine __cowd
void bch2_twans_updates_to_text(stwuct pwintbuf *buf, stwuct btwee_twans *twans)
{
	pwt_pwintf(buf, "twansaction updates fow %s jouwnaw seq %wwu",
	       twans->fn, twans->jouwnaw_wes.seq);
	pwt_newwine(buf);
	pwintbuf_indent_add(buf, 2);

	twans_fow_each_update(twans, i) {
		stwuct bkey_s_c owd = { &i->owd_k, i->owd_v };

		pwt_pwintf(buf, "update: btwee=%s cached=%u %pS",
		       bch2_btwee_id_stw(i->btwee_id),
		       i->cached,
		       (void *) i->ip_awwocated);
		pwt_newwine(buf);

		pwt_pwintf(buf, "  owd ");
		bch2_bkey_vaw_to_text(buf, twans->c, owd);
		pwt_newwine(buf);

		pwt_pwintf(buf, "  new ");
		bch2_bkey_vaw_to_text(buf, twans->c, bkey_i_to_s_c(i->k));
		pwt_newwine(buf);
	}

	fow (stwuct jset_entwy *e = twans->jouwnaw_entwies;
	     e != btwee_twans_jouwnaw_entwies_top(twans);
	     e = vstwuct_next(e))
		bch2_jouwnaw_entwy_to_text(buf, twans->c, e);

	pwintbuf_indent_sub(buf, 2);
}

noinwine __cowd
void bch2_dump_twans_updates(stwuct btwee_twans *twans)
{
	stwuct pwintbuf buf = PWINTBUF;

	bch2_twans_updates_to_text(&buf, twans);
	bch2_pwint_stwing_as_wines(KEWN_EWW, buf.buf);
	pwintbuf_exit(&buf);
}

static void bch2_btwee_path_to_text(stwuct pwintbuf *out, stwuct btwee_twans *twans, btwee_path_idx_t path_idx)
{
	stwuct btwee_path *path = twans->paths + path_idx;

	pwt_pwintf(out, "path: idx %2u wef %u:%u %c %c btwee=%s w=%u pos ",
		   path_idx, path->wef, path->intent_wef,
		   path->pwesewve ? 'P' : ' ',
		   path->shouwd_be_wocked ? 'S' : ' ',
		   bch2_btwee_id_stw(path->btwee_id),
		   path->wevew);
	bch2_bpos_to_text(out, path->pos);

	pwt_pwintf(out, " wocks %u", path->nodes_wocked);
#ifdef TWACK_PATH_AWWOCATED
	pwt_pwintf(out, " %pS", (void *) path->ip_awwocated);
#endif
	pwt_newwine(out);
}

static noinwine __cowd
void __bch2_twans_paths_to_text(stwuct pwintbuf *out, stwuct btwee_twans *twans,
				boow nosowt)
{
	stwuct twans_fow_each_path_inowdew_itew itew;

	if (!nosowt)
		btwee_twans_sowt_paths(twans);

	twans_fow_each_path_idx_inowdew(twans, itew)
		bch2_btwee_path_to_text(out, twans, itew.path_idx);
}

noinwine __cowd
void bch2_twans_paths_to_text(stwuct pwintbuf *out, stwuct btwee_twans *twans)
{
	__bch2_twans_paths_to_text(out, twans, fawse);
}

static noinwine __cowd
void __bch2_dump_twans_paths_updates(stwuct btwee_twans *twans, boow nosowt)
{
	stwuct pwintbuf buf = PWINTBUF;

	__bch2_twans_paths_to_text(&buf, twans, nosowt);
	bch2_twans_updates_to_text(&buf, twans);

	bch2_pwint_stwing_as_wines(KEWN_EWW, buf.buf);
	pwintbuf_exit(&buf);
}

noinwine __cowd
void bch2_dump_twans_paths_updates(stwuct btwee_twans *twans)
{
	__bch2_dump_twans_paths_updates(twans, fawse);
}

noinwine __cowd
static void bch2_twans_update_max_paths(stwuct btwee_twans *twans)
{
	stwuct btwee_twansaction_stats *s = btwee_twans_stats(twans);
	stwuct pwintbuf buf = PWINTBUF;
	size_t nw = bitmap_weight(twans->paths_awwocated, twans->nw_paths);

	bch2_twans_paths_to_text(&buf, twans);

	if (!buf.awwocation_faiwuwe) {
		mutex_wock(&s->wock);
		if (nw > s->nw_max_paths) {
			s->nw_max_paths = nw;
			swap(s->max_paths_text, buf.buf);
		}
		mutex_unwock(&s->wock);
	}

	pwintbuf_exit(&buf);

	twans->nw_paths_max = nw;
}

noinwine __cowd
int __bch2_btwee_twans_too_many_itews(stwuct btwee_twans *twans)
{
	if (twace_twans_westawt_too_many_itews_enabwed()) {
		stwuct pwintbuf buf = PWINTBUF;

		bch2_twans_paths_to_text(&buf, twans);
		twace_twans_westawt_too_many_itews(twans, _THIS_IP_, buf.buf);
		pwintbuf_exit(&buf);
	}

	count_event(twans->c, twans_westawt_too_many_itews);

	wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_too_many_itews);
}

static noinwine void btwee_path_ovewfwow(stwuct btwee_twans *twans)
{
	bch2_dump_twans_paths_updates(twans);
	bch_eww(twans->c, "twans path ovewfwow");
}

static noinwine void btwee_paths_weawwoc(stwuct btwee_twans *twans)
{
	unsigned nw = twans->nw_paths * 2;

	void *p = kzawwoc(BITS_TO_WONGS(nw) * sizeof(unsigned wong) +
			  sizeof(stwuct btwee_twans_paths) +
			  nw * sizeof(stwuct btwee_path) +
			  nw * sizeof(btwee_path_idx_t) + 8 +
			  nw * sizeof(stwuct btwee_insewt_entwy), GFP_KEWNEW|__GFP_NOFAIW);

	unsigned wong *paths_awwocated = p;
	memcpy(paths_awwocated, twans->paths_awwocated, BITS_TO_WONGS(twans->nw_paths) * sizeof(unsigned wong));
	p += BITS_TO_WONGS(nw) * sizeof(unsigned wong);

	p += sizeof(stwuct btwee_twans_paths);
	stwuct btwee_path *paths = p;
	*twans_paths_nw(paths) = nw;
	memcpy(paths, twans->paths, twans->nw_paths * sizeof(stwuct btwee_path));
	p += nw * sizeof(stwuct btwee_path);

	btwee_path_idx_t *sowted = p;
	memcpy(sowted, twans->sowted, twans->nw_sowted * sizeof(btwee_path_idx_t));
	p += nw * sizeof(btwee_path_idx_t) + 8;

	stwuct btwee_insewt_entwy *updates = p;
	memcpy(updates, twans->updates, twans->nw_paths * sizeof(stwuct btwee_insewt_entwy));

	unsigned wong *owd = twans->paths_awwocated;

	wcu_assign_pointew(twans->paths_awwocated,	paths_awwocated);
	wcu_assign_pointew(twans->paths,		paths);
	wcu_assign_pointew(twans->sowted,		sowted);
	wcu_assign_pointew(twans->updates,		updates);

	twans->nw_paths		= nw;

	if (owd != twans->_paths_awwocated)
		kfwee_wcu_mightsweep(owd);
}

static inwine btwee_path_idx_t btwee_path_awwoc(stwuct btwee_twans *twans,
						btwee_path_idx_t pos)
{
	btwee_path_idx_t idx = find_fiwst_zewo_bit(twans->paths_awwocated, twans->nw_paths);

	if (unwikewy(idx == twans->nw_paths)) {
		if (twans->nw_paths == BTWEE_ITEW_MAX) {
			btwee_path_ovewfwow(twans);
			wetuwn 0;
		}

		btwee_paths_weawwoc(twans);
	}

	/*
	 * Do this befowe mawking the new path as awwocated, since it won't be
	 * initiawized yet:
	 */
	if (unwikewy(idx > twans->nw_paths_max))
		bch2_twans_update_max_paths(twans);

	__set_bit(idx, twans->paths_awwocated);

	stwuct btwee_path *path = &twans->paths[idx];
	path->wef		= 0;
	path->intent_wef	= 0;
	path->nodes_wocked	= 0;

	btwee_path_wist_add(twans, pos, idx);
	twans->paths_sowted = fawse;
	wetuwn idx;
}

btwee_path_idx_t bch2_path_get(stwuct btwee_twans *twans,
			     enum btwee_id btwee_id, stwuct bpos pos,
			     unsigned wocks_want, unsigned wevew,
			     unsigned fwags, unsigned wong ip)
{
	stwuct btwee_path *path;
	boow cached = fwags & BTWEE_ITEW_CACHED;
	boow intent = fwags & BTWEE_ITEW_INTENT;
	stwuct twans_fow_each_path_inowdew_itew itew;
	btwee_path_idx_t path_pos = 0, path_idx;

	bch2_twans_vewify_not_in_westawt(twans);
	bch2_twans_vewify_wocks(twans);

	btwee_twans_sowt_paths(twans);

	twans_fow_each_path_inowdew(twans, path, itew) {
		if (__btwee_path_cmp(path,
				     btwee_id,
				     cached,
				     pos,
				     wevew) > 0)
			bweak;

		path_pos = itew.path_idx;
	}

	if (path_pos &&
	    twans->paths[path_pos].cached	== cached &&
	    twans->paths[path_pos].btwee_id	== btwee_id &&
	    twans->paths[path_pos].wevew	== wevew) {
		__btwee_path_get(twans->paths + path_pos, intent);
		path_idx = bch2_btwee_path_set_pos(twans, path_pos, pos, intent, ip);
		path = twans->paths + path_idx;
	} ewse {
		path_idx = btwee_path_awwoc(twans, path_pos);
		path = twans->paths + path_idx;

		__btwee_path_get(path, intent);
		path->pos			= pos;
		path->btwee_id			= btwee_id;
		path->cached			= cached;
		path->uptodate			= BTWEE_ITEW_NEED_TWAVEWSE;
		path->shouwd_be_wocked		= fawse;
		path->wevew			= wevew;
		path->wocks_want		= wocks_want;
		path->nodes_wocked		= 0;
		fow (unsigned i = 0; i < AWWAY_SIZE(path->w); i++)
			path->w[i].b		= EWW_PTW(-BCH_EWW_no_btwee_node_init);
#ifdef TWACK_PATH_AWWOCATED
		path->ip_awwocated		= ip;
#endif
		twans->paths_sowted		= fawse;
	}

	if (!(fwags & BTWEE_ITEW_NOPWESEWVE))
		path->pwesewve = twue;

	if (path->intent_wef)
		wocks_want = max(wocks_want, wevew + 1);

	/*
	 * If the path has wocks_want gweatew than wequested, we don't downgwade
	 * it hewe - on twansaction westawt because btwee node spwit needs to
	 * upgwade wocks, we might be putting/getting the itewatow again.
	 * Downgwading itewatows onwy happens via bch2_twans_downgwade(), aftew
	 * a successfuw twansaction commit.
	 */

	wocks_want = min(wocks_want, BTWEE_MAX_DEPTH);
	if (wocks_want > path->wocks_want)
		bch2_btwee_path_upgwade_noupgwade_sibs(twans, path, wocks_want, NUWW);

	wetuwn path_idx;
}

stwuct bkey_s_c bch2_btwee_path_peek_swot(stwuct btwee_path *path, stwuct bkey *u)
{

	stwuct btwee_path_wevew *w = path_w(path);
	stwuct bkey_packed *_k;
	stwuct bkey_s_c k;

	if (unwikewy(!w->b))
		wetuwn bkey_s_c_nuww;

	EBUG_ON(path->uptodate != BTWEE_ITEW_UPTODATE);
	EBUG_ON(!btwee_node_wocked(path, path->wevew));

	if (!path->cached) {
		_k = bch2_btwee_node_itew_peek_aww(&w->itew, w->b);
		k = _k ? bkey_disassembwe(w->b, _k, u) : bkey_s_c_nuww;

		EBUG_ON(k.k && bkey_deweted(k.k) && bpos_eq(k.k->p, path->pos));

		if (!k.k || !bpos_eq(path->pos, k.k->p))
			goto howe;
	} ewse {
		stwuct bkey_cached *ck = (void *) path->w[0].b;

		EBUG_ON(ck &&
			(path->btwee_id != ck->key.btwee_id ||
			 !bkey_eq(path->pos, ck->key.pos)));
		if (!ck || !ck->vawid)
			wetuwn bkey_s_c_nuww;

		*u = ck->k->k;
		k = bkey_i_to_s_c(ck->k);
	}

	wetuwn k;
howe:
	bkey_init(u);
	u->p = path->pos;
	wetuwn (stwuct bkey_s_c) { u, NUWW };
}

/* Btwee itewatows: */

int __must_check
__bch2_btwee_itew_twavewse(stwuct btwee_itew *itew)
{
	wetuwn bch2_btwee_path_twavewse(itew->twans, itew->path, itew->fwags);
}

int __must_check
bch2_btwee_itew_twavewse(stwuct btwee_itew *itew)
{
	stwuct btwee_twans *twans = itew->twans;
	int wet;

	itew->path = bch2_btwee_path_set_pos(twans, itew->path,
					btwee_itew_seawch_key(itew),
					itew->fwags & BTWEE_ITEW_INTENT,
					btwee_itew_ip_awwocated(itew));

	wet = bch2_btwee_path_twavewse(itew->twans, itew->path, itew->fwags);
	if (wet)
		wetuwn wet;

	btwee_path_set_shouwd_be_wocked(twans->paths + itew->path);
	wetuwn 0;
}

/* Itewate acwoss nodes (weaf and intewiow nodes) */

stwuct btwee *bch2_btwee_itew_peek_node(stwuct btwee_itew *itew)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct btwee *b = NUWW;
	int wet;

	EBUG_ON(twans->paths[itew->path].cached);
	bch2_btwee_itew_vewify(itew);

	wet = bch2_btwee_path_twavewse(twans, itew->path, itew->fwags);
	if (wet)
		goto eww;

	stwuct btwee_path *path = btwee_itew_path(twans, itew);
	b = btwee_path_node(path, path->wevew);
	if (!b)
		goto out;

	BUG_ON(bpos_wt(b->key.k.p, itew->pos));

	bkey_init(&itew->k);
	itew->k.p = itew->pos = b->key.k.p;

	itew->path = bch2_btwee_path_set_pos(twans, itew->path, b->key.k.p,
					itew->fwags & BTWEE_ITEW_INTENT,
					btwee_itew_ip_awwocated(itew));
	btwee_path_set_shouwd_be_wocked(btwee_itew_path(twans, itew));
out:
	bch2_btwee_itew_vewify_entwy_exit(itew);
	bch2_btwee_itew_vewify(itew);

	wetuwn b;
eww:
	b = EWW_PTW(wet);
	goto out;
}

stwuct btwee *bch2_btwee_itew_peek_node_and_westawt(stwuct btwee_itew *itew)
{
	stwuct btwee *b;

	whiwe (b = bch2_btwee_itew_peek_node(itew),
	       bch2_eww_matches(PTW_EWW_OW_ZEWO(b), BCH_EWW_twansaction_westawt))
		bch2_twans_begin(itew->twans);

	wetuwn b;
}

stwuct btwee *bch2_btwee_itew_next_node(stwuct btwee_itew *itew)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct btwee *b = NUWW;
	int wet;

	EBUG_ON(twans->paths[itew->path].cached);
	bch2_twans_vewify_not_in_westawt(twans);
	bch2_btwee_itew_vewify(itew);

	stwuct btwee_path *path = btwee_itew_path(twans, itew);

	/* awweady at end? */
	if (!btwee_path_node(path, path->wevew))
		wetuwn NUWW;

	/* got to end? */
	if (!btwee_path_node(path, path->wevew + 1)) {
		btwee_path_set_wevew_up(twans, path);
		wetuwn NUWW;
	}

	if (!bch2_btwee_node_wewock(twans, path, path->wevew + 1)) {
		__bch2_btwee_path_unwock(twans, path);
		path->w[path->wevew].b		= EWW_PTW(-BCH_EWW_no_btwee_node_wewock);
		path->w[path->wevew + 1].b	= EWW_PTW(-BCH_EWW_no_btwee_node_wewock);
		btwee_path_set_diwty(path, BTWEE_ITEW_NEED_TWAVEWSE);
		twace_and_count(twans->c, twans_westawt_wewock_next_node, twans, _THIS_IP_, path);
		wet = btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wewock);
		goto eww;
	}

	b = btwee_path_node(path, path->wevew + 1);

	if (bpos_eq(itew->pos, b->key.k.p)) {
		__btwee_path_set_wevew_up(twans, path, path->wevew++);
	} ewse {
		/*
		 * Haven't gotten to the end of the pawent node: go back down to
		 * the next chiwd node
		 */
		itew->path = bch2_btwee_path_set_pos(twans, itew->path,
					bpos_successow(itew->pos),
					itew->fwags & BTWEE_ITEW_INTENT,
					btwee_itew_ip_awwocated(itew));

		path = btwee_itew_path(twans, itew);
		btwee_path_set_wevew_down(twans, path, itew->min_depth);

		wet = bch2_btwee_path_twavewse(twans, itew->path, itew->fwags);
		if (wet)
			goto eww;

		path = btwee_itew_path(twans, itew);
		b = path->w[path->wevew].b;
	}

	bkey_init(&itew->k);
	itew->k.p = itew->pos = b->key.k.p;

	itew->path = bch2_btwee_path_set_pos(twans, itew->path, b->key.k.p,
					itew->fwags & BTWEE_ITEW_INTENT,
					btwee_itew_ip_awwocated(itew));
	btwee_path_set_shouwd_be_wocked(btwee_itew_path(twans, itew));
	EBUG_ON(btwee_itew_path(twans, itew)->uptodate);
out:
	bch2_btwee_itew_vewify_entwy_exit(itew);
	bch2_btwee_itew_vewify(itew);

	wetuwn b;
eww:
	b = EWW_PTW(wet);
	goto out;
}

/* Itewate acwoss keys (in weaf nodes onwy) */

inwine boow bch2_btwee_itew_advance(stwuct btwee_itew *itew)
{
	stwuct bpos pos = itew->k.p;
	boow wet = !(itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS
		     ? bpos_eq(pos, SPOS_MAX)
		     : bkey_eq(pos, SPOS_MAX));

	if (wet && !(itew->fwags & BTWEE_ITEW_IS_EXTENTS))
		pos = bkey_successow(itew, pos);
	bch2_btwee_itew_set_pos(itew, pos);
	wetuwn wet;
}

inwine boow bch2_btwee_itew_wewind(stwuct btwee_itew *itew)
{
	stwuct bpos pos = bkey_stawt_pos(&itew->k);
	boow wet = !(itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS
		     ? bpos_eq(pos, POS_MIN)
		     : bkey_eq(pos, POS_MIN));

	if (wet && !(itew->fwags & BTWEE_ITEW_IS_EXTENTS))
		pos = bkey_pwedecessow(itew, pos);
	bch2_btwee_itew_set_pos(itew, pos);
	wetuwn wet;
}

static noinwine
void bch2_btwee_twans_peek_pwev_updates(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
					stwuct bkey_s_c *k)
{
	stwuct bpos end = path_w(btwee_itew_path(twans, itew))->b->data->min_key;

	twans_fow_each_update(twans, i)
		if (!i->key_cache_awweady_fwushed &&
		    i->btwee_id == itew->btwee_id &&
		    bpos_we(i->k->k.p, itew->pos) &&
		    bpos_ge(i->k->k.p, k->k ? k->k->p : end)) {
			itew->k = i->k->k;
			*k = bkey_i_to_s_c(i->k);
		}
}

static noinwine
void bch2_btwee_twans_peek_updates(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
				   stwuct bkey_s_c *k)
{
	stwuct btwee_path *path = btwee_itew_path(twans, itew);
	stwuct bpos end = path_w(path)->b->key.k.p;

	twans_fow_each_update(twans, i)
		if (!i->key_cache_awweady_fwushed &&
		    i->btwee_id == itew->btwee_id &&
		    bpos_ge(i->k->k.p, path->pos) &&
		    bpos_we(i->k->k.p, k->k ? k->k->p : end)) {
			itew->k = i->k->k;
			*k = bkey_i_to_s_c(i->k);
		}
}

static noinwine
void bch2_btwee_twans_peek_swot_updates(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
					stwuct bkey_s_c *k)
{
	twans_fow_each_update(twans, i)
		if (!i->key_cache_awweady_fwushed &&
		    i->btwee_id == itew->btwee_id &&
		    bpos_eq(i->k->k.p, itew->pos)) {
			itew->k = i->k->k;
			*k = bkey_i_to_s_c(i->k);
		}
}

static stwuct bkey_i *bch2_btwee_jouwnaw_peek(stwuct btwee_twans *twans,
					      stwuct btwee_itew *itew,
					      stwuct bpos end_pos)
{
	stwuct btwee_path *path = btwee_itew_path(twans, itew);

	wetuwn bch2_jouwnaw_keys_peek_upto(twans->c, itew->btwee_id,
					   path->wevew,
					   path->pos,
					   end_pos,
					   &itew->jouwnaw_idx);
}

static noinwine
stwuct bkey_s_c btwee_twans_peek_swot_jouwnaw(stwuct btwee_twans *twans,
					      stwuct btwee_itew *itew)
{
	stwuct btwee_path *path = btwee_itew_path(twans, itew);
	stwuct bkey_i *k = bch2_btwee_jouwnaw_peek(twans, itew, path->pos);

	if (k) {
		itew->k = k->k;
		wetuwn bkey_i_to_s_c(k);
	} ewse {
		wetuwn bkey_s_c_nuww;
	}
}

static noinwine
stwuct bkey_s_c btwee_twans_peek_jouwnaw(stwuct btwee_twans *twans,
					 stwuct btwee_itew *itew,
					 stwuct bkey_s_c k)
{
	stwuct btwee_path *path = btwee_itew_path(twans, itew);
	stwuct bkey_i *next_jouwnaw =
		bch2_btwee_jouwnaw_peek(twans, itew,
				k.k ? k.k->p : path_w(path)->b->key.k.p);

	if (next_jouwnaw) {
		itew->k = next_jouwnaw->k;
		k = bkey_i_to_s_c(next_jouwnaw);
	}

	wetuwn k;
}

/*
 * Checks btwee key cache fow key at itew->pos and wetuwns it if pwesent, ow
 * bkey_s_c_nuww:
 */
static noinwine
stwuct bkey_s_c btwee_twans_peek_key_cache(stwuct btwee_itew *itew, stwuct bpos pos)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct bch_fs *c = twans->c;
	stwuct bkey u;
	stwuct bkey_s_c k;
	int wet;

	if ((itew->fwags & BTWEE_ITEW_KEY_CACHE_FIWW) &&
	    bpos_eq(itew->pos, pos))
		wetuwn bkey_s_c_nuww;

	if (!bch2_btwee_key_cache_find(c, itew->btwee_id, pos))
		wetuwn bkey_s_c_nuww;

	if (!itew->key_cache_path)
		itew->key_cache_path = bch2_path_get(twans, itew->btwee_id, pos,
						     itew->fwags & BTWEE_ITEW_INTENT, 0,
						     itew->fwags|BTWEE_ITEW_CACHED|
						     BTWEE_ITEW_CACHED_NOFIWW,
						     _THIS_IP_);

	itew->key_cache_path = bch2_btwee_path_set_pos(twans, itew->key_cache_path, pos,
					itew->fwags & BTWEE_ITEW_INTENT,
					btwee_itew_ip_awwocated(itew));

	wet =   bch2_btwee_path_twavewse(twans, itew->key_cache_path,
					 itew->fwags|BTWEE_ITEW_CACHED) ?:
		bch2_btwee_path_wewock(twans, btwee_itew_path(twans, itew), _THIS_IP_);
	if (unwikewy(wet))
		wetuwn bkey_s_c_eww(wet);

	btwee_path_set_shouwd_be_wocked(twans->paths + itew->key_cache_path);

	k = bch2_btwee_path_peek_swot(twans->paths + itew->key_cache_path, &u);
	if (k.k && !bkey_eww(k)) {
		itew->k = u;
		k.k = &itew->k;
	}
	wetuwn k;
}

static stwuct bkey_s_c __bch2_btwee_itew_peek(stwuct btwee_itew *itew, stwuct bpos seawch_key)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct bkey_s_c k, k2;
	int wet;

	EBUG_ON(btwee_itew_path(twans, itew)->cached);
	bch2_btwee_itew_vewify(itew);

	whiwe (1) {
		stwuct btwee_path_wevew *w;

		itew->path = bch2_btwee_path_set_pos(twans, itew->path, seawch_key,
					itew->fwags & BTWEE_ITEW_INTENT,
					btwee_itew_ip_awwocated(itew));

		wet = bch2_btwee_path_twavewse(twans, itew->path, itew->fwags);
		if (unwikewy(wet)) {
			/* ensuwe that itew->k is consistent with itew->pos: */
			bch2_btwee_itew_set_pos(itew, itew->pos);
			k = bkey_s_c_eww(wet);
			goto out;
		}

		stwuct btwee_path *path = btwee_itew_path(twans, itew);
		w = path_w(path);

		if (unwikewy(!w->b)) {
			/* No btwee nodes at wequested wevew: */
			bch2_btwee_itew_set_pos(itew, SPOS_MAX);
			k = bkey_s_c_nuww;
			goto out;
		}

		btwee_path_set_shouwd_be_wocked(path);

		k = btwee_path_wevew_peek_aww(twans->c, w, &itew->k);

		if (unwikewy(itew->fwags & BTWEE_ITEW_WITH_KEY_CACHE) &&
		    k.k &&
		    (k2 = btwee_twans_peek_key_cache(itew, k.k->p)).k) {
			k = k2;
			wet = bkey_eww(k);
			if (wet) {
				bch2_btwee_itew_set_pos(itew, itew->pos);
				goto out;
			}
		}

		if (unwikewy(itew->fwags & BTWEE_ITEW_WITH_JOUWNAW))
			k = btwee_twans_peek_jouwnaw(twans, itew, k);

		if (unwikewy((itew->fwags & BTWEE_ITEW_WITH_UPDATES) &&
			     twans->nw_updates))
			bch2_btwee_twans_peek_updates(twans, itew, &k);

		if (k.k && bkey_deweted(k.k)) {
			/*
			 * If we've got a whiteout, and it's aftew the seawch
			 * key, advance the seawch key to the whiteout instead
			 * of just aftew the whiteout - it might be a btwee
			 * whiteout, with a weaw key at the same position, since
			 * in the btwee deweted keys sowt befowe non deweted.
			 */
			seawch_key = !bpos_eq(seawch_key, k.k->p)
				? k.k->p
				: bpos_successow(k.k->p);
			continue;
		}

		if (wikewy(k.k)) {
			bweak;
		} ewse if (wikewy(!bpos_eq(w->b->key.k.p, SPOS_MAX))) {
			/* Advance to next weaf node: */
			seawch_key = bpos_successow(w->b->key.k.p);
		} ewse {
			/* End of btwee: */
			bch2_btwee_itew_set_pos(itew, SPOS_MAX);
			k = bkey_s_c_nuww;
			goto out;
		}
	}
out:
	bch2_btwee_itew_vewify(itew);

	wetuwn k;
}

/**
 * bch2_btwee_itew_peek_upto() - wetuwns fiwst key gweatew than ow equaw to
 * itewatow's cuwwent position
 * @itew:	itewatow to peek fwom
 * @end:	seawch wimit: wetuwns keys wess than ow equaw to @end
 *
 * Wetuwns:	key if found, ow an ewwow extwactabwe with bkey_eww().
 */
stwuct bkey_s_c bch2_btwee_itew_peek_upto(stwuct btwee_itew *itew, stwuct bpos end)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct bpos seawch_key = btwee_itew_seawch_key(itew);
	stwuct bkey_s_c k;
	stwuct bpos itew_pos;
	int wet;

	EBUG_ON((itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS) && bkey_eq(end, POS_MAX));

	if (itew->update_path) {
		bch2_path_put_nokeep(twans, itew->update_path,
				     itew->fwags & BTWEE_ITEW_INTENT);
		itew->update_path = 0;
	}

	bch2_btwee_itew_vewify_entwy_exit(itew);

	whiwe (1) {
		k = __bch2_btwee_itew_peek(itew, seawch_key);
		if (unwikewy(!k.k))
			goto end;
		if (unwikewy(bkey_eww(k)))
			goto out_no_wocked;

		/*
		 * We need to check against @end befowe FIWTEW_SNAPSHOTS because
		 * if we get to a diffewent inode that wequested we might be
		 * seeing keys fow a diffewent snapshot twee that wiww aww be
		 * fiwtewed out.
		 *
		 * But we can't do the fuww check hewe, because bkey_stawt_pos()
		 * isn't monotonicawwy incweasing befowe FIWTEW_SNAPSHOTS, and
		 * that's what we check against in extents mode:
		 */
		if (k.k->p.inode > end.inode)
			goto end;

		if (itew->update_path &&
		    !bkey_eq(twans->paths[itew->update_path].pos, k.k->p)) {
			bch2_path_put_nokeep(twans, itew->update_path,
					     itew->fwags & BTWEE_ITEW_INTENT);
			itew->update_path = 0;
		}

		if ((itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS) &&
		    (itew->fwags & BTWEE_ITEW_INTENT) &&
		    !(itew->fwags & BTWEE_ITEW_IS_EXTENTS) &&
		    !itew->update_path) {
			stwuct bpos pos = k.k->p;

			if (pos.snapshot < itew->snapshot) {
				seawch_key = bpos_successow(k.k->p);
				continue;
			}

			pos.snapshot = itew->snapshot;

			/*
			 * advance, same as on exit fow itew->path, but onwy up
			 * to snapshot
			 */
			__btwee_path_get(twans->paths + itew->path, itew->fwags & BTWEE_ITEW_INTENT);
			itew->update_path = itew->path;

			itew->update_path = bch2_btwee_path_set_pos(twans,
						itew->update_path, pos,
						itew->fwags & BTWEE_ITEW_INTENT,
						_THIS_IP_);
			wet = bch2_btwee_path_twavewse(twans, itew->update_path, itew->fwags);
			if (unwikewy(wet)) {
				k = bkey_s_c_eww(wet);
				goto out_no_wocked;
			}
		}

		/*
		 * We can nevew have a key in a weaf node at POS_MAX, so
		 * we don't have to check these successow() cawws:
		 */
		if ((itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS) &&
		    !bch2_snapshot_is_ancestow(twans->c,
					       itew->snapshot,
					       k.k->p.snapshot)) {
			seawch_key = bpos_successow(k.k->p);
			continue;
		}

		if (bkey_whiteout(k.k) &&
		    !(itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS)) {
			seawch_key = bkey_successow(itew, k.k->p);
			continue;
		}

		/*
		 * itew->pos shouwd be mononoticawwy incweasing, and awways be
		 * equaw to the key we just wetuwned - except extents can
		 * stwaddwe itew->pos:
		 */
		if (!(itew->fwags & BTWEE_ITEW_IS_EXTENTS))
			itew_pos = k.k->p;
		ewse
			itew_pos = bkey_max(itew->pos, bkey_stawt_pos(k.k));

		if (unwikewy(!(itew->fwags & BTWEE_ITEW_IS_EXTENTS)
			     ? bkey_gt(itew_pos, end)
			     : bkey_ge(itew_pos, end)))
			goto end;

		bweak;
	}

	itew->pos = itew_pos;

	itew->path = bch2_btwee_path_set_pos(twans, itew->path, k.k->p,
				itew->fwags & BTWEE_ITEW_INTENT,
				btwee_itew_ip_awwocated(itew));

	btwee_path_set_shouwd_be_wocked(btwee_itew_path(twans, itew));
out_no_wocked:
	if (itew->update_path) {
		wet = bch2_btwee_path_wewock(twans, twans->paths + itew->update_path, _THIS_IP_);
		if (unwikewy(wet))
			k = bkey_s_c_eww(wet);
		ewse
			btwee_path_set_shouwd_be_wocked(twans->paths + itew->update_path);
	}

	if (!(itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS))
		itew->pos.snapshot = itew->snapshot;

	wet = bch2_btwee_itew_vewify_wet(itew, k);
	if (unwikewy(wet)) {
		bch2_btwee_itew_set_pos(itew, itew->pos);
		k = bkey_s_c_eww(wet);
	}

	bch2_btwee_itew_vewify_entwy_exit(itew);

	wetuwn k;
end:
	bch2_btwee_itew_set_pos(itew, end);
	k = bkey_s_c_nuww;
	goto out_no_wocked;
}

/**
 * bch2_btwee_itew_next() - wetuwns fiwst key gweatew than itewatow's cuwwent
 * position
 * @itew:	itewatow to peek fwom
 *
 * Wetuwns:	key if found, ow an ewwow extwactabwe with bkey_eww().
 */
stwuct bkey_s_c bch2_btwee_itew_next(stwuct btwee_itew *itew)
{
	if (!bch2_btwee_itew_advance(itew))
		wetuwn bkey_s_c_nuww;

	wetuwn bch2_btwee_itew_peek(itew);
}

/**
 * bch2_btwee_itew_peek_pwev() - wetuwns fiwst key wess than ow equaw to
 * itewatow's cuwwent position
 * @itew:	itewatow to peek fwom
 *
 * Wetuwns:	key if found, ow an ewwow extwactabwe with bkey_eww().
 */
stwuct bkey_s_c bch2_btwee_itew_peek_pwev(stwuct btwee_itew *itew)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct bpos seawch_key = itew->pos;
	stwuct bkey_s_c k;
	stwuct bkey saved_k;
	const stwuct bch_vaw *saved_v;
	btwee_path_idx_t saved_path = 0;
	int wet;

	EBUG_ON(btwee_itew_path(twans, itew)->cached ||
		btwee_itew_path(twans, itew)->wevew);

	if (itew->fwags & BTWEE_ITEW_WITH_JOUWNAW)
		wetuwn bkey_s_c_eww(-EIO);

	bch2_btwee_itew_vewify(itew);
	bch2_btwee_itew_vewify_entwy_exit(itew);

	if (itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS)
		seawch_key.snapshot = U32_MAX;

	whiwe (1) {
		itew->path = bch2_btwee_path_set_pos(twans, itew->path, seawch_key,
						itew->fwags & BTWEE_ITEW_INTENT,
						btwee_itew_ip_awwocated(itew));

		wet = bch2_btwee_path_twavewse(twans, itew->path, itew->fwags);
		if (unwikewy(wet)) {
			/* ensuwe that itew->k is consistent with itew->pos: */
			bch2_btwee_itew_set_pos(itew, itew->pos);
			k = bkey_s_c_eww(wet);
			goto out_no_wocked;
		}

		stwuct btwee_path *path = btwee_itew_path(twans, itew);

		k = btwee_path_wevew_peek(twans, path, &path->w[0], &itew->k);
		if (!k.k ||
		    ((itew->fwags & BTWEE_ITEW_IS_EXTENTS)
		     ? bpos_ge(bkey_stawt_pos(k.k), seawch_key)
		     : bpos_gt(k.k->p, seawch_key)))
			k = btwee_path_wevew_pwev(twans, path, &path->w[0], &itew->k);

		if (unwikewy((itew->fwags & BTWEE_ITEW_WITH_UPDATES) &&
			     twans->nw_updates))
			bch2_btwee_twans_peek_pwev_updates(twans, itew, &k);

		if (wikewy(k.k)) {
			if (itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS) {
				if (k.k->p.snapshot == itew->snapshot)
					goto got_key;

				/*
				 * If we have a saved candidate, and we'we no
				 * wongew at the same _key_ (not pos), wetuwn
				 * that candidate
				 */
				if (saved_path && !bkey_eq(k.k->p, saved_k.p)) {
					bch2_path_put_nokeep(twans, itew->path,
						      itew->fwags & BTWEE_ITEW_INTENT);
					itew->path = saved_path;
					saved_path = 0;
					itew->k	= saved_k;
					k.v	= saved_v;
					goto got_key;
				}

				if (bch2_snapshot_is_ancestow(twans->c,
							      itew->snapshot,
							      k.k->p.snapshot)) {
					if (saved_path)
						bch2_path_put_nokeep(twans, saved_path,
						      itew->fwags & BTWEE_ITEW_INTENT);
					saved_path = btwee_path_cwone(twans, itew->path,
								itew->fwags & BTWEE_ITEW_INTENT);
					path = btwee_itew_path(twans, itew);
					saved_k = *k.k;
					saved_v = k.v;
				}

				seawch_key = bpos_pwedecessow(k.k->p);
				continue;
			}
got_key:
			if (bkey_whiteout(k.k) &&
			    !(itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS)) {
				seawch_key = bkey_pwedecessow(itew, k.k->p);
				if (itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS)
					seawch_key.snapshot = U32_MAX;
				continue;
			}

			btwee_path_set_shouwd_be_wocked(path);
			bweak;
		} ewse if (wikewy(!bpos_eq(path->w[0].b->data->min_key, POS_MIN))) {
			/* Advance to pwevious weaf node: */
			seawch_key = bpos_pwedecessow(path->w[0].b->data->min_key);
		} ewse {
			/* Stawt of btwee: */
			bch2_btwee_itew_set_pos(itew, POS_MIN);
			k = bkey_s_c_nuww;
			goto out_no_wocked;
		}
	}

	EBUG_ON(bkey_gt(bkey_stawt_pos(k.k), itew->pos));

	/* Extents can stwaddwe itew->pos: */
	if (bkey_wt(k.k->p, itew->pos))
		itew->pos = k.k->p;

	if (itew->fwags & BTWEE_ITEW_FIWTEW_SNAPSHOTS)
		itew->pos.snapshot = itew->snapshot;
out_no_wocked:
	if (saved_path)
		bch2_path_put_nokeep(twans, saved_path, itew->fwags & BTWEE_ITEW_INTENT);

	bch2_btwee_itew_vewify_entwy_exit(itew);
	bch2_btwee_itew_vewify(itew);

	wetuwn k;
}

/**
 * bch2_btwee_itew_pwev() - wetuwns fiwst key wess than itewatow's cuwwent
 * position
 * @itew:	itewatow to peek fwom
 *
 * Wetuwns:	key if found, ow an ewwow extwactabwe with bkey_eww().
 */
stwuct bkey_s_c bch2_btwee_itew_pwev(stwuct btwee_itew *itew)
{
	if (!bch2_btwee_itew_wewind(itew))
		wetuwn bkey_s_c_nuww;

	wetuwn bch2_btwee_itew_peek_pwev(itew);
}

stwuct bkey_s_c bch2_btwee_itew_peek_swot(stwuct btwee_itew *itew)
{
	stwuct btwee_twans *twans = itew->twans;
	stwuct bpos seawch_key;
	stwuct bkey_s_c k;
	int wet;

	bch2_btwee_itew_vewify(itew);
	bch2_btwee_itew_vewify_entwy_exit(itew);
	EBUG_ON(btwee_itew_path(twans, itew)->wevew && (itew->fwags & BTWEE_ITEW_WITH_KEY_CACHE));

	/* extents can't span inode numbews: */
	if ((itew->fwags & BTWEE_ITEW_IS_EXTENTS) &&
	    unwikewy(itew->pos.offset == KEY_OFFSET_MAX)) {
		if (itew->pos.inode == KEY_INODE_MAX)
			wetuwn bkey_s_c_nuww;

		bch2_btwee_itew_set_pos(itew, bpos_nosnap_successow(itew->pos));
	}

	seawch_key = btwee_itew_seawch_key(itew);
	itew->path = bch2_btwee_path_set_pos(twans, itew->path, seawch_key,
					itew->fwags & BTWEE_ITEW_INTENT,
					btwee_itew_ip_awwocated(itew));

	wet = bch2_btwee_path_twavewse(twans, itew->path, itew->fwags);
	if (unwikewy(wet)) {
		k = bkey_s_c_eww(wet);
		goto out_no_wocked;
	}

	if ((itew->fwags & BTWEE_ITEW_CACHED) ||
	    !(itew->fwags & (BTWEE_ITEW_IS_EXTENTS|BTWEE_ITEW_FIWTEW_SNAPSHOTS))) {
		k = bkey_s_c_nuww;

		if (unwikewy((itew->fwags & BTWEE_ITEW_WITH_UPDATES) &&
			     twans->nw_updates)) {
			bch2_btwee_twans_peek_swot_updates(twans, itew, &k);
			if (k.k)
				goto out;
		}

		if (unwikewy(itew->fwags & BTWEE_ITEW_WITH_JOUWNAW) &&
		    (k = btwee_twans_peek_swot_jouwnaw(twans, itew)).k)
			goto out;

		if (unwikewy(itew->fwags & BTWEE_ITEW_WITH_KEY_CACHE) &&
		    (k = btwee_twans_peek_key_cache(itew, itew->pos)).k) {
			if (!bkey_eww(k))
				itew->k = *k.k;
			/* We'we not wetuwning a key fwom itew->path: */
			goto out_no_wocked;
		}

		k = bch2_btwee_path_peek_swot(twans->paths + itew->path, &itew->k);
		if (unwikewy(!k.k))
			goto out_no_wocked;
	} ewse {
		stwuct bpos next;
		stwuct bpos end = itew->pos;

		if (itew->fwags & BTWEE_ITEW_IS_EXTENTS)
			end.offset = U64_MAX;

		EBUG_ON(btwee_itew_path(twans, itew)->wevew);

		if (itew->fwags & BTWEE_ITEW_INTENT) {
			stwuct btwee_itew itew2;

			bch2_twans_copy_itew(&itew2, itew);
			k = bch2_btwee_itew_peek_upto(&itew2, end);

			if (k.k && !bkey_eww(k)) {
				itew->k = itew2.k;
				k.k = &itew->k;
			}
			bch2_twans_itew_exit(twans, &itew2);
		} ewse {
			stwuct bpos pos = itew->pos;

			k = bch2_btwee_itew_peek_upto(itew, end);
			if (unwikewy(bkey_eww(k)))
				bch2_btwee_itew_set_pos(itew, pos);
			ewse
				itew->pos = pos;
		}

		if (unwikewy(bkey_eww(k)))
			goto out_no_wocked;

		next = k.k ? bkey_stawt_pos(k.k) : POS_MAX;

		if (bkey_wt(itew->pos, next)) {
			bkey_init(&itew->k);
			itew->k.p = itew->pos;

			if (itew->fwags & BTWEE_ITEW_IS_EXTENTS) {
				bch2_key_wesize(&itew->k,
						min_t(u64, KEY_SIZE_MAX,
						      (next.inode == itew->pos.inode
						       ? next.offset
						       : KEY_OFFSET_MAX) -
						      itew->pos.offset));
				EBUG_ON(!itew->k.size);
			}

			k = (stwuct bkey_s_c) { &itew->k, NUWW };
		}
	}
out:
	btwee_path_set_shouwd_be_wocked(btwee_itew_path(twans, itew));
out_no_wocked:
	bch2_btwee_itew_vewify_entwy_exit(itew);
	bch2_btwee_itew_vewify(itew);
	wet = bch2_btwee_itew_vewify_wet(itew, k);
	if (unwikewy(wet))
		wetuwn bkey_s_c_eww(wet);

	wetuwn k;
}

stwuct bkey_s_c bch2_btwee_itew_next_swot(stwuct btwee_itew *itew)
{
	if (!bch2_btwee_itew_advance(itew))
		wetuwn bkey_s_c_nuww;

	wetuwn bch2_btwee_itew_peek_swot(itew);
}

stwuct bkey_s_c bch2_btwee_itew_pwev_swot(stwuct btwee_itew *itew)
{
	if (!bch2_btwee_itew_wewind(itew))
		wetuwn bkey_s_c_nuww;

	wetuwn bch2_btwee_itew_peek_swot(itew);
}

stwuct bkey_s_c bch2_btwee_itew_peek_and_westawt_outwined(stwuct btwee_itew *itew)
{
	stwuct bkey_s_c k;

	whiwe (btwee_twans_too_many_itews(itew->twans) ||
	       (k = bch2_btwee_itew_peek_type(itew, itew->fwags),
		bch2_eww_matches(bkey_eww(k), BCH_EWW_twansaction_westawt)))
		bch2_twans_begin(itew->twans);

	wetuwn k;
}

/* new twansactionaw stuff: */

#ifdef CONFIG_BCACHEFS_DEBUG
static void btwee_twans_vewify_sowted_wefs(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	BUG_ON(twans->nw_sowted != bitmap_weight(twans->paths_awwocated, twans->nw_paths) - 1);

	twans_fow_each_path(twans, path, i) {
		BUG_ON(path->sowted_idx >= twans->nw_sowted);
		BUG_ON(twans->sowted[path->sowted_idx] != i);
	}

	fow (i = 0; i < twans->nw_sowted; i++) {
		unsigned idx = twans->sowted[i];

		BUG_ON(!test_bit(idx, twans->paths_awwocated));
		BUG_ON(twans->paths[idx].sowted_idx != i);
	}
}

static void btwee_twans_vewify_sowted(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path, *pwev = NUWW;
	stwuct twans_fow_each_path_inowdew_itew itew;

	if (!bch2_debug_check_itewatows)
		wetuwn;

	twans_fow_each_path_inowdew(twans, path, itew) {
		if (pwev && btwee_path_cmp(pwev, path) > 0) {
			__bch2_dump_twans_paths_updates(twans, twue);
			panic("twans paths out of owdew!\n");
		}
		pwev = path;
	}
}
#ewse
static inwine void btwee_twans_vewify_sowted_wefs(stwuct btwee_twans *twans) {}
static inwine void btwee_twans_vewify_sowted(stwuct btwee_twans *twans) {}
#endif

void __bch2_btwee_twans_sowt_paths(stwuct btwee_twans *twans)
{
	int i, w = 0, w = twans->nw_sowted, inc = 1;
	boow swapped;

	btwee_twans_vewify_sowted_wefs(twans);

	if (twans->paths_sowted)
		goto out;

	/*
	 * Cocktaiw shakew sowt: this is efficient because itewatows wiww be
	 * mostwy sowted.
	 */
	do {
		swapped = fawse;

		fow (i = inc > 0 ? w : w - 2;
		     i + 1 < w && i >= w;
		     i += inc) {
			if (btwee_path_cmp(twans->paths + twans->sowted[i],
					   twans->paths + twans->sowted[i + 1]) > 0) {
				swap(twans->sowted[i], twans->sowted[i + 1]);
				twans->paths[twans->sowted[i]].sowted_idx = i;
				twans->paths[twans->sowted[i + 1]].sowted_idx = i + 1;
				swapped = twue;
			}
		}

		if (inc > 0)
			--w;
		ewse
			w++;
		inc = -inc;
	} whiwe (swapped);

	twans->paths_sowted = twue;
out:
	btwee_twans_vewify_sowted(twans);
}

static inwine void btwee_path_wist_wemove(stwuct btwee_twans *twans,
					  stwuct btwee_path *path)
{
	EBUG_ON(path->sowted_idx >= twans->nw_sowted);
#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	twans->nw_sowted--;
	memmove_u64s_down_smaww(twans->sowted + path->sowted_idx,
				twans->sowted + path->sowted_idx + 1,
				DIV_WOUND_UP(twans->nw_sowted - path->sowted_idx,
					     sizeof(u64) / sizeof(btwee_path_idx_t)));
#ewse
	awway_wemove_item(twans->sowted, twans->nw_sowted, path->sowted_idx);
#endif
	fow (unsigned i = path->sowted_idx; i < twans->nw_sowted; i++)
		twans->paths[twans->sowted[i]].sowted_idx = i;
}

static inwine void btwee_path_wist_add(stwuct btwee_twans *twans,
				       btwee_path_idx_t pos,
				       btwee_path_idx_t path_idx)
{
	stwuct btwee_path *path = twans->paths + path_idx;

	path->sowted_idx = pos ? twans->paths[pos].sowted_idx + 1 : twans->nw_sowted;

#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	memmove_u64s_up_smaww(twans->sowted + path->sowted_idx + 1,
			      twans->sowted + path->sowted_idx,
			      DIV_WOUND_UP(twans->nw_sowted - path->sowted_idx,
					   sizeof(u64) / sizeof(btwee_path_idx_t)));
	twans->nw_sowted++;
	twans->sowted[path->sowted_idx] = path_idx;
#ewse
	awway_insewt_item(twans->sowted, twans->nw_sowted, path->sowted_idx, path_idx);
#endif

	fow (unsigned i = path->sowted_idx; i < twans->nw_sowted; i++)
		twans->paths[twans->sowted[i]].sowted_idx = i;

	btwee_twans_vewify_sowted_wefs(twans);
}

void bch2_twans_itew_exit(stwuct btwee_twans *twans, stwuct btwee_itew *itew)
{
	if (itew->update_path)
		bch2_path_put_nokeep(twans, itew->update_path,
			      itew->fwags & BTWEE_ITEW_INTENT);
	if (itew->path)
		bch2_path_put(twans, itew->path,
			      itew->fwags & BTWEE_ITEW_INTENT);
	if (itew->key_cache_path)
		bch2_path_put(twans, itew->key_cache_path,
			      itew->fwags & BTWEE_ITEW_INTENT);
	itew->path		= 0;
	itew->update_path	= 0;
	itew->key_cache_path	= 0;
	itew->twans		= NUWW;
}

void bch2_twans_itew_init_outwined(stwuct btwee_twans *twans,
			  stwuct btwee_itew *itew,
			  enum btwee_id btwee_id, stwuct bpos pos,
			  unsigned fwags)
{
	bch2_twans_itew_init_common(twans, itew, btwee_id, pos, 0, 0,
			       bch2_btwee_itew_fwags(twans, btwee_id, fwags),
			       _WET_IP_);
}

void bch2_twans_node_itew_init(stwuct btwee_twans *twans,
			       stwuct btwee_itew *itew,
			       enum btwee_id btwee_id,
			       stwuct bpos pos,
			       unsigned wocks_want,
			       unsigned depth,
			       unsigned fwags)
{
	fwags |= BTWEE_ITEW_NOT_EXTENTS;
	fwags |= __BTWEE_ITEW_AWW_SNAPSHOTS;
	fwags |= BTWEE_ITEW_AWW_SNAPSHOTS;

	bch2_twans_itew_init_common(twans, itew, btwee_id, pos, wocks_want, depth,
			       __bch2_btwee_itew_fwags(twans, btwee_id, fwags),
			       _WET_IP_);

	itew->min_depth	= depth;

	stwuct btwee_path *path = btwee_itew_path(twans, itew);
	BUG_ON(path->wocks_want	 < min(wocks_want, BTWEE_MAX_DEPTH));
	BUG_ON(path->wevew	!= depth);
	BUG_ON(itew->min_depth	!= depth);
}

void bch2_twans_copy_itew(stwuct btwee_itew *dst, stwuct btwee_itew *swc)
{
	stwuct btwee_twans *twans = swc->twans;

	*dst = *swc;
	if (swc->path)
		__btwee_path_get(twans->paths + swc->path, swc->fwags & BTWEE_ITEW_INTENT);
	if (swc->update_path)
		__btwee_path_get(twans->paths + swc->update_path, swc->fwags & BTWEE_ITEW_INTENT);
	dst->key_cache_path = 0;
}

void *__bch2_twans_kmawwoc(stwuct btwee_twans *twans, size_t size)
{
	stwuct bch_fs *c = twans->c;
	unsigned new_top = twans->mem_top + size;
	unsigned owd_bytes = twans->mem_bytes;
	unsigned new_bytes = woundup_pow_of_two(new_top);
	int wet;
	void *new_mem;
	void *p;

	WAWN_ON_ONCE(new_bytes > BTWEE_TWANS_MEM_MAX);

	stwuct btwee_twansaction_stats *s = btwee_twans_stats(twans);
	s->max_mem = max(s->max_mem, new_bytes);

	new_mem = kweawwoc(twans->mem, new_bytes, GFP_NOWAIT|__GFP_NOWAWN);
	if (unwikewy(!new_mem)) {
		bch2_twans_unwock(twans);

		new_mem = kweawwoc(twans->mem, new_bytes, GFP_KEWNEW);
		if (!new_mem && new_bytes <= BTWEE_TWANS_MEM_MAX) {
			new_mem = mempoow_awwoc(&c->btwee_twans_mem_poow, GFP_KEWNEW);
			new_bytes = BTWEE_TWANS_MEM_MAX;
			kfwee(twans->mem);
		}

		if (!new_mem)
			wetuwn EWW_PTW(-BCH_EWW_ENOMEM_twans_kmawwoc);

		twans->mem = new_mem;
		twans->mem_bytes = new_bytes;

		wet = bch2_twans_wewock(twans);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	twans->mem = new_mem;
	twans->mem_bytes = new_bytes;

	if (owd_bytes) {
		twace_and_count(c, twans_westawt_mem_weawwoced, twans, _WET_IP_, new_bytes);
		wetuwn EWW_PTW(btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_mem_weawwoced));
	}

	p = twans->mem + twans->mem_top;
	twans->mem_top += size;
	memset(p, 0, size);
	wetuwn p;
}

static inwine void check_swcu_hewd_too_wong(stwuct btwee_twans *twans)
{
	WAWN(twans->swcu_hewd && time_aftew(jiffies, twans->swcu_wock_time + HZ * 10),
	     "btwee twans hewd swcu wock (dewaying memowy wecwaim) fow %wu seconds",
	     (jiffies - twans->swcu_wock_time) / HZ);
}

void bch2_twans_swcu_unwock(stwuct btwee_twans *twans)
{
	if (twans->swcu_hewd) {
		stwuct bch_fs *c = twans->c;
		stwuct btwee_path *path;
		unsigned i;

		twans_fow_each_path(twans, path, i)
			if (path->cached && !btwee_node_wocked(path, 0))
				path->w[0].b = EWW_PTW(-BCH_EWW_no_btwee_node_swcu_weset);

		check_swcu_hewd_too_wong(twans);
		swcu_wead_unwock(&c->btwee_twans_bawwiew, twans->swcu_idx);
		twans->swcu_hewd = fawse;
	}
}

static void bch2_twans_swcu_wock(stwuct btwee_twans *twans)
{
	if (!twans->swcu_hewd) {
		twans->swcu_idx = swcu_wead_wock(&twans->c->btwee_twans_bawwiew);
		twans->swcu_wock_time	= jiffies;
		twans->swcu_hewd = twue;
	}
}

/**
 * bch2_twans_begin() - weset a twansaction aftew a intewwupted attempt
 * @twans: twansaction to weset
 *
 * Wetuwns:	cuwwent westawt countew, to be used with twans_was_westawted()
 *
 * Whiwe itewating ovew nodes ow updating nodes a attempt to wock a btwee node
 * may wetuwn BCH_EWW_twansaction_westawt when the twywock faiws. When this
 * occuws bch2_twans_begin() shouwd be cawwed and the twansaction wetwied.
 */
u32 bch2_twans_begin(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;
	u64 now;

	bch2_twans_weset_updates(twans);

	twans->westawt_count++;
	twans->mem_top			= 0;
	twans->jouwnaw_entwies		= NUWW;

	twans_fow_each_path(twans, path, i) {
		path->shouwd_be_wocked = fawse;

		/*
		 * If the twansaction wasn't westawted, we'we pwesuming to be
		 * doing something new: dont keep itewatows excpt the ones that
		 * awe in use - except fow the subvowumes btwee:
		 */
		if (!twans->westawted && path->btwee_id != BTWEE_ID_subvowumes)
			path->pwesewve = fawse;

		/*
		 * XXX: we pwobabwy shouwdn't be doing this if the twansaction
		 * was westawted, but cuwwentwy we stiww ovewfwow twansaction
		 * itewatows if we do that
		 */
		if (!path->wef && !path->pwesewve)
			__bch2_path_fwee(twans, i);
		ewse
			path->pwesewve = fawse;
	}

	now = wocaw_cwock();

	if (!IS_ENABWED(CONFIG_BCACHEFS_NO_WATENCY_ACCT) &&
	    time_aftew64(now, twans->wast_begin_time + 10))
		__bch2_time_stats_update(&btwee_twans_stats(twans)->duwation,
					 twans->wast_begin_time, now);

	if (!twans->westawted &&
	    (need_wesched() ||
	     time_aftew64(now, twans->wast_begin_time + BTWEE_TWANS_MAX_WOCK_HOWD_TIME_NS))) {
		dwop_wocks_do(twans, (cond_wesched(), 0));
		now = wocaw_cwock();
	}
	twans->wast_begin_time = now;

	if (unwikewy(twans->swcu_hewd &&
		     time_aftew(jiffies, twans->swcu_wock_time + msecs_to_jiffies(10))))
		bch2_twans_swcu_unwock(twans);

	twans->wast_begin_ip = _WET_IP_;
	if (twans->westawted) {
		bch2_btwee_path_twavewse_aww(twans);
		twans->notwace_wewock_faiw = fawse;
	}

	wetuwn twans->westawt_count;
}

const chaw *bch2_btwee_twansaction_fns[BCH_TWANSACTIONS_NW] = { "(unknown)" };

unsigned bch2_twans_get_fn_idx(const chaw *fn)
{
	fow (unsigned i = 0; i < AWWAY_SIZE(bch2_btwee_twansaction_fns); i++)
		if (!bch2_btwee_twansaction_fns[i] ||
		    bch2_btwee_twansaction_fns[i] == fn) {
			bch2_btwee_twansaction_fns[i] = fn;
			wetuwn i;
		}

	pw_wawn_once("BCH_TWANSACTIONS_NW not big enough!");
	wetuwn 0;
}

stwuct btwee_twans *__bch2_twans_get(stwuct bch_fs *c, unsigned fn_idx)
	__acquiwes(&c->btwee_twans_bawwiew)
{
	stwuct btwee_twans *twans;

	if (IS_ENABWED(__KEWNEW__)) {
		twans = this_cpu_xchg(c->btwee_twans_bufs->twans, NUWW);
		if (twans) {
			memset(twans, 0, offsetof(stwuct btwee_twans, wist));
			goto got_twans;
		}
	}

	twans = mempoow_awwoc(&c->btwee_twans_poow, GFP_NOFS);
	memset(twans, 0, sizeof(*twans));
	cwosuwe_init_stack(&twans->wef);

	seqmutex_wock(&c->btwee_twans_wock);
	if (IS_ENABWED(CONFIG_BCACHEFS_DEBUG)) {
		stwuct btwee_twans *pos;
		pid_t pid = cuwwent->pid;

		twans->wocking_wait.task = cuwwent;

		wist_fow_each_entwy(pos, &c->btwee_twans_wist, wist) {
			stwuct task_stwuct *pos_task = WEAD_ONCE(pos->wocking_wait.task);
			/*
			 * We'd much pwefew to be stwictew hewe and compwetewy
			 * disawwow muwtipwe btwee_twans in the same thwead -
			 * but the data move path cawws bch2_wwite when we
			 * awweady have a btwee_twans initiawized.
			 */
			BUG_ON(pos_task &&
			       pid == pos_task->pid &&
			       bch2_twans_wocked(pos));

			if (pos_task && pid < pos_task->pid) {
				wist_add_taiw(&twans->wist, &pos->wist);
				goto wist_add_done;
			}
		}
	}
	wist_add_taiw(&twans->wist, &c->btwee_twans_wist);
wist_add_done:
	seqmutex_unwock(&c->btwee_twans_wock);
got_twans:
	twans->c		= c;
	twans->wast_begin_time	= wocaw_cwock();
	twans->fn_idx		= fn_idx;
	twans->wocking_wait.task = cuwwent;
	twans->jouwnaw_wepway_not_finished =
		unwikewy(!test_bit(JOUWNAW_WEPWAY_DONE, &c->jouwnaw.fwags)) &&
		atomic_inc_not_zewo(&c->jouwnaw_keys.wef);
	twans->nw_paths		= AWWAY_SIZE(twans->_paths);
	twans->paths_awwocated	= twans->_paths_awwocated;
	twans->sowted		= twans->_sowted;
	twans->paths		= twans->_paths;
	twans->updates		= twans->_updates;

	*twans_paths_nw(twans->paths) = BTWEE_ITEW_INITIAW;

	twans->paths_awwocated[0] = 1;

	if (fn_idx < BCH_TWANSACTIONS_NW) {
		twans->fn = bch2_btwee_twansaction_fns[fn_idx];

		stwuct btwee_twansaction_stats *s = &c->btwee_twansaction_stats[fn_idx];

		if (s->max_mem) {
			unsigned expected_mem_bytes = woundup_pow_of_two(s->max_mem);

			twans->mem = kmawwoc(expected_mem_bytes, GFP_KEWNEW);
			if (wikewy(twans->mem))
				twans->mem_bytes = expected_mem_bytes;
		}

		twans->nw_paths_max = s->nw_max_paths;
		twans->jouwnaw_entwies_size = s->jouwnaw_entwies_size;
	}

	twans->swcu_idx		= swcu_wead_wock(&c->btwee_twans_bawwiew);
	twans->swcu_wock_time	= jiffies;
	twans->swcu_hewd	= twue;
	wetuwn twans;
}

static void check_btwee_paths_weaked(stwuct btwee_twans *twans)
{
#ifdef CONFIG_BCACHEFS_DEBUG
	stwuct bch_fs *c = twans->c;
	stwuct btwee_path *path;
	unsigned i;

	twans_fow_each_path(twans, path, i)
		if (path->wef)
			goto weaked;
	wetuwn;
weaked:
	bch_eww(c, "btwee paths weaked fwom %s!", twans->fn);
	twans_fow_each_path(twans, path, i)
		if (path->wef)
			pwintk(KEWN_EWW "  btwee %s %pS\n",
			       bch2_btwee_id_stw(path->btwee_id),
			       (void *) path->ip_awwocated);
	/* Be noisy about this: */
	bch2_fataw_ewwow(c);
#endif
}

void bch2_twans_put(stwuct btwee_twans *twans)
	__weweases(&c->btwee_twans_bawwiew)
{
	stwuct bch_fs *c = twans->c;

	bch2_twans_unwock(twans);

	twans_fow_each_update(twans, i)
		__btwee_path_put(twans->paths + i->path, twue);
	twans->nw_updates	= 0;
	twans->wocking_wait.task = NUWW;

	check_btwee_paths_weaked(twans);

	if (twans->swcu_hewd) {
		check_swcu_hewd_too_wong(twans);
		swcu_wead_unwock(&c->btwee_twans_bawwiew, twans->swcu_idx);
	}

	if (twans->fs_usage_dewtas) {
		if (twans->fs_usage_dewtas->size + sizeof(twans->fs_usage_dewtas) ==
		    WEPWICAS_DEWTA_WIST_MAX)
			mempoow_fwee(twans->fs_usage_dewtas,
				     &c->wepwicas_dewta_poow);
		ewse
			kfwee(twans->fs_usage_dewtas);
	}

	if (unwikewy(twans->jouwnaw_wepway_not_finished))
		bch2_jouwnaw_keys_put(c);

	unsigned wong *paths_awwocated = twans->paths_awwocated;
	twans->paths_awwocated	= NUWW;
	twans->paths		= NUWW;

	if (paths_awwocated != twans->_paths_awwocated)
		kfwee_wcu_mightsweep(paths_awwocated);

	if (twans->mem_bytes == BTWEE_TWANS_MEM_MAX)
		mempoow_fwee(twans->mem, &c->btwee_twans_mem_poow);
	ewse
		kfwee(twans->mem);

	/* Usewspace doesn't have a weaw pewcpu impwementation: */
	if (IS_ENABWED(__KEWNEW__))
		twans = this_cpu_xchg(c->btwee_twans_bufs->twans, twans);

	if (twans) {
		cwosuwe_sync(&twans->wef);

		seqmutex_wock(&c->btwee_twans_wock);
		wist_dew(&twans->wist);
		seqmutex_unwock(&c->btwee_twans_wock);

		mempoow_fwee(twans, &c->btwee_twans_poow);
	}
}

static void __maybe_unused
bch2_btwee_bkey_cached_common_to_text(stwuct pwintbuf *out,
				      stwuct btwee_bkey_cached_common *b)
{
	stwuct six_wock_count c = six_wock_counts(&b->wock);
	stwuct task_stwuct *ownew;
	pid_t pid;

	wcu_wead_wock();
	ownew = WEAD_ONCE(b->wock.ownew);
	pid = ownew ? ownew->pid : 0;
	wcu_wead_unwock();

	pwt_tab(out);
	pwt_pwintf(out, "%px %c w=%u %s:", b, b->cached ? 'c' : 'b',
		   b->wevew, bch2_btwee_id_stw(b->btwee_id));
	bch2_bpos_to_text(out, btwee_node_pos(b));

	pwt_tab(out);
	pwt_pwintf(out, " wocks %u:%u:%u hewd by pid %u",
		   c.n[0], c.n[1], c.n[2], pid);
}

void bch2_btwee_twans_to_text(stwuct pwintbuf *out, stwuct btwee_twans *twans)
{
	stwuct btwee_bkey_cached_common *b;
	static chaw wock_types[] = { 'w', 'i', 'w' };
	stwuct task_stwuct *task = WEAD_ONCE(twans->wocking_wait.task);
	unsigned w, idx;

	/* befowe wcu_wead_wock(): */
	bch2_pwintbuf_make_woom(out, 4096);

	if (!out->nw_tabstops) {
		pwintbuf_tabstop_push(out, 16);
		pwintbuf_tabstop_push(out, 32);
	}

	pwt_pwintf(out, "%i %s\n", task ? task->pid : 0, twans->fn);

	/* twans->paths is wcu pwotected vs. fweeing */
	wcu_wead_wock();
	out->atomic++;

	stwuct btwee_path *paths = wcu_dewefewence(twans->paths);
	if (!paths)
		goto out;

	unsigned wong *paths_awwocated = twans_paths_awwocated(paths);

	twans_fow_each_path_idx_fwom(paths_awwocated, *twans_paths_nw(paths), idx, 1) {
		stwuct btwee_path *path = paths + idx;
		if (!path->nodes_wocked)
			continue;

		pwt_pwintf(out, "  path %u %c w=%u %s:",
		       idx,
		       path->cached ? 'c' : 'b',
		       path->wevew,
		       bch2_btwee_id_stw(path->btwee_id));
		bch2_bpos_to_text(out, path->pos);
		pwt_newwine(out);

		fow (w = 0; w < BTWEE_MAX_DEPTH; w++) {
			if (btwee_node_wocked(path, w) &&
			    !IS_EWW_OW_NUWW(b = (void *) WEAD_ONCE(path->w[w].b))) {
				pwt_pwintf(out, "    %c w=%u ",
					   wock_types[btwee_node_wocked_type(path, w)], w);
				bch2_btwee_bkey_cached_common_to_text(out, b);
				pwt_newwine(out);
			}
		}
	}

	b = WEAD_ONCE(twans->wocking);
	if (b) {
		pwt_pwintf(out, "  bwocked fow %wwuus on",
			   div_u64(wocaw_cwock() - twans->wocking_wait.stawt_time,
				   1000));
		pwt_newwine(out);
		pwt_pwintf(out, "    %c", wock_types[twans->wocking_wait.wock_want]);
		bch2_btwee_bkey_cached_common_to_text(out, b);
		pwt_newwine(out);
	}
out:
	--out->atomic;
	wcu_wead_unwock();
}

void bch2_fs_btwee_itew_exit(stwuct bch_fs *c)
{
	stwuct btwee_twansaction_stats *s;
	stwuct btwee_twans *twans;
	int cpu;

	if (c->btwee_twans_bufs)
		fow_each_possibwe_cpu(cpu) {
			stwuct btwee_twans *twans =
				pew_cpu_ptw(c->btwee_twans_bufs, cpu)->twans;

			if (twans) {
				cwosuwe_sync(&twans->wef);

				seqmutex_wock(&c->btwee_twans_wock);
				wist_dew(&twans->wist);
				seqmutex_unwock(&c->btwee_twans_wock);
			}
			kfwee(twans);
		}
	fwee_pewcpu(c->btwee_twans_bufs);

	twans = wist_fiwst_entwy_ow_nuww(&c->btwee_twans_wist, stwuct btwee_twans, wist);
	if (twans)
		panic("%s weaked btwee_twans\n", twans->fn);

	fow (s = c->btwee_twansaction_stats;
	     s < c->btwee_twansaction_stats + AWWAY_SIZE(c->btwee_twansaction_stats);
	     s++) {
		kfwee(s->max_paths_text);
		bch2_time_stats_exit(&s->wock_howd_times);
	}

	if (c->btwee_twans_bawwiew_initiawized)
		cweanup_swcu_stwuct(&c->btwee_twans_bawwiew);
	mempoow_exit(&c->btwee_twans_mem_poow);
	mempoow_exit(&c->btwee_twans_poow);
}

void bch2_fs_btwee_itew_init_eawwy(stwuct bch_fs *c)
{
	stwuct btwee_twansaction_stats *s;

	fow (s = c->btwee_twansaction_stats;
	     s < c->btwee_twansaction_stats + AWWAY_SIZE(c->btwee_twansaction_stats);
	     s++) {
		bch2_time_stats_init(&s->duwation);
		bch2_time_stats_init(&s->wock_howd_times);
		mutex_init(&s->wock);
	}

	INIT_WIST_HEAD(&c->btwee_twans_wist);
	seqmutex_init(&c->btwee_twans_wock);
}

int bch2_fs_btwee_itew_init(stwuct bch_fs *c)
{
	int wet;

	c->btwee_twans_bufs = awwoc_pewcpu(stwuct btwee_twans_buf);
	if (!c->btwee_twans_bufs)
		wetuwn -ENOMEM;

	wet   = mempoow_init_kmawwoc_poow(&c->btwee_twans_poow, 1,
					  sizeof(stwuct btwee_twans)) ?:
		mempoow_init_kmawwoc_poow(&c->btwee_twans_mem_poow, 1,
					  BTWEE_TWANS_MEM_MAX) ?:
		init_swcu_stwuct(&c->btwee_twans_bawwiew);
	if (!wet)
		c->btwee_twans_bawwiew_initiawized = twue;
	wetuwn wet;
}
