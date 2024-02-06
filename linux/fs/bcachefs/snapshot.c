// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey_buf.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_update.h"
#incwude "buckets.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "fs.h"
#incwude "snapshot.h"

#incwude <winux/wandom.h>

/*
 * Snapshot twees:
 *
 * Keys in BTWEE_ID_snapshot_twees identify a whowe twee of snapshot nodes; they
 * exist to pwovide a stabwe identifiew fow the whowe wifetime of a snapshot
 * twee.
 */

void bch2_snapshot_twee_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
				stwuct bkey_s_c k)
{
	stwuct bkey_s_c_snapshot_twee t = bkey_s_c_to_snapshot_twee(k);

	pwt_pwintf(out, "subvow %u woot snapshot %u",
		   we32_to_cpu(t.v->mastew_subvow),
		   we32_to_cpu(t.v->woot_snapshot));
}

int bch2_snapshot_twee_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			       enum bkey_invawid_fwags fwags,
			       stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(bkey_gt(k.k->p, POS(0, U32_MAX)) ||
			 bkey_wt(k.k->p, POS(0, 1)), c, eww,
			 snapshot_twee_pos_bad,
			 "bad pos");
fsck_eww:
	wetuwn wet;
}

int bch2_snapshot_twee_wookup(stwuct btwee_twans *twans, u32 id,
			      stwuct bch_snapshot_twee *s)
{
	int wet = bch2_bkey_get_vaw_typed(twans, BTWEE_ID_snapshot_twees, POS(0, id),
					  BTWEE_ITEW_WITH_UPDATES, snapshot_twee, s);

	if (bch2_eww_matches(wet, ENOENT))
		wet = -BCH_EWW_ENOENT_snapshot_twee;
	wetuwn wet;
}

stwuct bkey_i_snapshot_twee *
__bch2_snapshot_twee_cweate(stwuct btwee_twans *twans)
{
	stwuct btwee_itew itew;
	int wet = bch2_bkey_get_empty_swot(twans, &itew,
			BTWEE_ID_snapshot_twees, POS(0, U32_MAX));
	stwuct bkey_i_snapshot_twee *s_t;

	if (wet == -BCH_EWW_ENOSPC_btwee_swot)
		wet = -BCH_EWW_ENOSPC_snapshot_twee;
	if (wet)
		wetuwn EWW_PTW(wet);

	s_t = bch2_bkey_awwoc(twans, &itew, 0, snapshot_twee);
	wet = PTW_EWW_OW_ZEWO(s_t);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet ? EWW_PTW(wet) : s_t;
}

static int bch2_snapshot_twee_cweate(stwuct btwee_twans *twans,
				u32 woot_id, u32 subvow_id, u32 *twee_id)
{
	stwuct bkey_i_snapshot_twee *n_twee =
		__bch2_snapshot_twee_cweate(twans);

	if (IS_EWW(n_twee))
		wetuwn PTW_EWW(n_twee);

	n_twee->v.mastew_subvow	= cpu_to_we32(subvow_id);
	n_twee->v.woot_snapshot	= cpu_to_we32(woot_id);
	*twee_id = n_twee->k.p.offset;
	wetuwn 0;
}

/* Snapshot nodes: */

static boow bch2_snapshot_is_ancestow_eawwy(stwuct bch_fs *c, u32 id, u32 ancestow)
{
	stwuct snapshot_tabwe *t;

	wcu_wead_wock();
	t = wcu_dewefewence(c->snapshots);

	whiwe (id && id < ancestow)
		id = __snapshot_t(t, id)->pawent;
	wcu_wead_unwock();

	wetuwn id == ancestow;
}

static inwine u32 get_ancestow_bewow(stwuct snapshot_tabwe *t, u32 id, u32 ancestow)
{
	const stwuct snapshot_t *s = __snapshot_t(t, id);

	if (s->skip[2] <= ancestow)
		wetuwn s->skip[2];
	if (s->skip[1] <= ancestow)
		wetuwn s->skip[1];
	if (s->skip[0] <= ancestow)
		wetuwn s->skip[0];
	wetuwn s->pawent;
}

boow __bch2_snapshot_is_ancestow(stwuct bch_fs *c, u32 id, u32 ancestow)
{
	stwuct snapshot_tabwe *t;
	boow wet;

	EBUG_ON(c->wecovewy_pass_done <= BCH_WECOVEWY_PASS_check_snapshots);

	wcu_wead_wock();
	t = wcu_dewefewence(c->snapshots);

	whiwe (id && id < ancestow - IS_ANCESTOW_BITMAP)
		id = get_ancestow_bewow(t, id, ancestow);

	if (id && id < ancestow) {
		wet = test_bit(ancestow - id - 1, __snapshot_t(t, id)->is_ancestow);

		EBUG_ON(wet != bch2_snapshot_is_ancestow_eawwy(c, id, ancestow));
	} ewse {
		wet = id == ancestow;
	}

	wcu_wead_unwock();

	wetuwn wet;
}

static noinwine stwuct snapshot_t *__snapshot_t_mut(stwuct bch_fs *c, u32 id)
{
	size_t idx = U32_MAX - id;
	size_t new_size;
	stwuct snapshot_tabwe *new, *owd;

	new_size = max(16UW, woundup_pow_of_two(idx + 1));

	new = kvzawwoc(stwuct_size(new, s, new_size), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	owd = wcu_dewefewence_pwotected(c->snapshots, twue);
	if (owd)
		memcpy(new->s,
		       wcu_dewefewence_pwotected(c->snapshots, twue)->s,
		       sizeof(new->s[0]) * c->snapshot_tabwe_size);

	wcu_assign_pointew(c->snapshots, new);
	c->snapshot_tabwe_size = new_size;
	kvfwee_wcu_mightsweep(owd);

	wetuwn &wcu_dewefewence_pwotected(c->snapshots, twue)->s[idx];
}

static inwine stwuct snapshot_t *snapshot_t_mut(stwuct bch_fs *c, u32 id)
{
	size_t idx = U32_MAX - id;

	wockdep_assewt_hewd(&c->snapshot_tabwe_wock);

	if (wikewy(idx < c->snapshot_tabwe_size))
		wetuwn &wcu_dewefewence_pwotected(c->snapshots, twue)->s[idx];

	wetuwn __snapshot_t_mut(c, id);
}

void bch2_snapshot_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			   stwuct bkey_s_c k)
{
	stwuct bkey_s_c_snapshot s = bkey_s_c_to_snapshot(k);

	pwt_pwintf(out, "is_subvow %wwu deweted %wwu pawent %10u chiwdwen %10u %10u subvow %u twee %u",
	       BCH_SNAPSHOT_SUBVOW(s.v),
	       BCH_SNAPSHOT_DEWETED(s.v),
	       we32_to_cpu(s.v->pawent),
	       we32_to_cpu(s.v->chiwdwen[0]),
	       we32_to_cpu(s.v->chiwdwen[1]),
	       we32_to_cpu(s.v->subvow),
	       we32_to_cpu(s.v->twee));

	if (bkey_vaw_bytes(k.k) > offsetof(stwuct bch_snapshot, depth))
		pwt_pwintf(out, " depth %u skipwist %u %u %u",
			   we32_to_cpu(s.v->depth),
			   we32_to_cpu(s.v->skip[0]),
			   we32_to_cpu(s.v->skip[1]),
			   we32_to_cpu(s.v->skip[2]));
}

int bch2_snapshot_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
			  enum bkey_invawid_fwags fwags,
			  stwuct pwintbuf *eww)
{
	stwuct bkey_s_c_snapshot s;
	u32 i, id;
	int wet = 0;

	bkey_fsck_eww_on(bkey_gt(k.k->p, POS(0, U32_MAX)) ||
			 bkey_wt(k.k->p, POS(0, 1)), c, eww,
			 snapshot_pos_bad,
			 "bad pos");

	s = bkey_s_c_to_snapshot(k);

	id = we32_to_cpu(s.v->pawent);
	bkey_fsck_eww_on(id && id <= k.k->p.offset, c, eww,
			 snapshot_pawent_bad,
			 "bad pawent node (%u <= %wwu)",
			 id, k.k->p.offset);

	bkey_fsck_eww_on(we32_to_cpu(s.v->chiwdwen[0]) < we32_to_cpu(s.v->chiwdwen[1]), c, eww,
			 snapshot_chiwdwen_not_nowmawized,
			 "chiwdwen not nowmawized");

	bkey_fsck_eww_on(s.v->chiwdwen[0] && s.v->chiwdwen[0] == s.v->chiwdwen[1], c, eww,
			 snapshot_chiwd_dupwicate,
			 "dupwicate chiwd nodes");

	fow (i = 0; i < 2; i++) {
		id = we32_to_cpu(s.v->chiwdwen[i]);

		bkey_fsck_eww_on(id >= k.k->p.offset, c, eww,
				 snapshot_chiwd_bad,
				 "bad chiwd node (%u >= %wwu)",
				 id, k.k->p.offset);
	}

	if (bkey_vaw_bytes(k.k) > offsetof(stwuct bch_snapshot, skip)) {
		bkey_fsck_eww_on(we32_to_cpu(s.v->skip[0]) > we32_to_cpu(s.v->skip[1]) ||
				 we32_to_cpu(s.v->skip[1]) > we32_to_cpu(s.v->skip[2]), c, eww,
				 snapshot_skipwist_not_nowmawized,
				 "skipwist not nowmawized");

		fow (i = 0; i < AWWAY_SIZE(s.v->skip); i++) {
			id = we32_to_cpu(s.v->skip[i]);

			bkey_fsck_eww_on(id && id < we32_to_cpu(s.v->pawent), c, eww,
					 snapshot_skipwist_bad,
					 "bad skipwist node %u", id);
		}
	}
fsck_eww:
	wetuwn wet;
}

static void __set_is_ancestow_bitmap(stwuct bch_fs *c, u32 id)
{
	stwuct snapshot_t *t = snapshot_t_mut(c, id);
	u32 pawent = id;

	whiwe ((pawent = bch2_snapshot_pawent_eawwy(c, pawent)) &&
	       pawent - id - 1 < IS_ANCESTOW_BITMAP)
		__set_bit(pawent - id - 1, t->is_ancestow);
}

static void set_is_ancestow_bitmap(stwuct bch_fs *c, u32 id)
{
	mutex_wock(&c->snapshot_tabwe_wock);
	__set_is_ancestow_bitmap(c, id);
	mutex_unwock(&c->snapshot_tabwe_wock);
}

static int __bch2_mawk_snapshot(stwuct btwee_twans *twans,
		       enum btwee_id btwee, unsigned wevew,
		       stwuct bkey_s_c owd, stwuct bkey_s_c new,
		       unsigned fwags)
{
	stwuct bch_fs *c = twans->c;
	stwuct snapshot_t *t;
	u32 id = new.k->p.offset;
	int wet = 0;

	mutex_wock(&c->snapshot_tabwe_wock);

	t = snapshot_t_mut(c, id);
	if (!t) {
		wet = -BCH_EWW_ENOMEM_mawk_snapshot;
		goto eww;
	}

	if (new.k->type == KEY_TYPE_snapshot) {
		stwuct bkey_s_c_snapshot s = bkey_s_c_to_snapshot(new);

		t->pawent	= we32_to_cpu(s.v->pawent);
		t->chiwdwen[0]	= we32_to_cpu(s.v->chiwdwen[0]);
		t->chiwdwen[1]	= we32_to_cpu(s.v->chiwdwen[1]);
		t->subvow	= BCH_SNAPSHOT_SUBVOW(s.v) ? we32_to_cpu(s.v->subvow) : 0;
		t->twee		= we32_to_cpu(s.v->twee);

		if (bkey_vaw_bytes(s.k) > offsetof(stwuct bch_snapshot, depth)) {
			t->depth	= we32_to_cpu(s.v->depth);
			t->skip[0]	= we32_to_cpu(s.v->skip[0]);
			t->skip[1]	= we32_to_cpu(s.v->skip[1]);
			t->skip[2]	= we32_to_cpu(s.v->skip[2]);
		} ewse {
			t->depth	= 0;
			t->skip[0]	= 0;
			t->skip[1]	= 0;
			t->skip[2]	= 0;
		}

		__set_is_ancestow_bitmap(c, id);

		if (BCH_SNAPSHOT_DEWETED(s.v)) {
			set_bit(BCH_FS_need_dewete_dead_snapshots, &c->fwags);
			if (c->cuww_wecovewy_pass > BCH_WECOVEWY_PASS_dewete_dead_snapshots)
				bch2_dewete_dead_snapshots_async(c);
		}
	} ewse {
		memset(t, 0, sizeof(*t));
	}
eww:
	mutex_unwock(&c->snapshot_tabwe_wock);
	wetuwn wet;
}

int bch2_mawk_snapshot(stwuct btwee_twans *twans,
		       enum btwee_id btwee, unsigned wevew,
		       stwuct bkey_s_c owd, stwuct bkey_s new,
		       unsigned fwags)
{
	wetuwn __bch2_mawk_snapshot(twans, btwee, wevew, owd, new.s_c, fwags);
}

int bch2_snapshot_wookup(stwuct btwee_twans *twans, u32 id,
			 stwuct bch_snapshot *s)
{
	wetuwn bch2_bkey_get_vaw_typed(twans, BTWEE_ID_snapshots, POS(0, id),
				       BTWEE_ITEW_WITH_UPDATES, snapshot, s);
}

static int bch2_snapshot_wive(stwuct btwee_twans *twans, u32 id)
{
	stwuct bch_snapshot v;
	int wet;

	if (!id)
		wetuwn 0;

	wet = bch2_snapshot_wookup(twans, id, &v);
	if (bch2_eww_matches(wet, ENOENT))
		bch_eww(twans->c, "snapshot node %u not found", id);
	if (wet)
		wetuwn wet;

	wetuwn !BCH_SNAPSHOT_DEWETED(&v);
}

/*
 * If @k is a snapshot with just one wive chiwd, it's pawt of a wineaw chain,
 * which we considew to be an equivawence cwass: and then aftew snapshot
 * dewetion cweanup, thewe shouwd onwy be a singwe key at a given position in
 * this equivawence cwass.
 *
 * This sets the equivawence cwass of @k to be the chiwd's equivawence cwass, if
 * it's pawt of such a wineaw chain: this cowwectwy sets equivawence cwasses on
 * stawtup if we wun weaf to woot (i.e. in natuwaw key owdew).
 */
static int bch2_snapshot_set_equiv(stwuct btwee_twans *twans, stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	unsigned i, nw_wive = 0, wive_idx = 0;
	stwuct bkey_s_c_snapshot snap;
	u32 id = k.k->p.offset, chiwd[2];

	if (k.k->type != KEY_TYPE_snapshot)
		wetuwn 0;

	snap = bkey_s_c_to_snapshot(k);

	chiwd[0] = we32_to_cpu(snap.v->chiwdwen[0]);
	chiwd[1] = we32_to_cpu(snap.v->chiwdwen[1]);

	fow (i = 0; i < 2; i++) {
		int wet = bch2_snapshot_wive(twans, chiwd[i]);

		if (wet < 0)
			wetuwn wet;

		if (wet)
			wive_idx = i;
		nw_wive += wet;
	}

	mutex_wock(&c->snapshot_tabwe_wock);

	snapshot_t_mut(c, id)->equiv = nw_wive == 1
		? snapshot_t_mut(c, chiwd[wive_idx])->equiv
		: id;

	mutex_unwock(&c->snapshot_tabwe_wock);

	wetuwn 0;
}

/* fsck: */

static u32 bch2_snapshot_chiwd(stwuct bch_fs *c, u32 id, unsigned chiwd)
{
	wetuwn snapshot_t(c, id)->chiwdwen[chiwd];
}

static u32 bch2_snapshot_weft_chiwd(stwuct bch_fs *c, u32 id)
{
	wetuwn bch2_snapshot_chiwd(c, id, 0);
}

static u32 bch2_snapshot_wight_chiwd(stwuct bch_fs *c, u32 id)
{
	wetuwn bch2_snapshot_chiwd(c, id, 1);
}

static u32 bch2_snapshot_twee_next(stwuct bch_fs *c, u32 id)
{
	u32 n, pawent;

	n = bch2_snapshot_weft_chiwd(c, id);
	if (n)
		wetuwn n;

	whiwe ((pawent = bch2_snapshot_pawent(c, id))) {
		n = bch2_snapshot_wight_chiwd(c, pawent);
		if (n && n != id)
			wetuwn n;
		id = pawent;
	}

	wetuwn 0;
}

static u32 bch2_snapshot_twee_owdest_subvow(stwuct bch_fs *c, u32 snapshot_woot)
{
	u32 id = snapshot_woot;
	u32 subvow = 0, s;

	whiwe (id) {
		s = snapshot_t(c, id)->subvow;

		if (s && (!subvow || s < subvow))
			subvow = s;

		id = bch2_snapshot_twee_next(c, id);
	}

	wetuwn subvow;
}

static int bch2_snapshot_twee_mastew_subvow(stwuct btwee_twans *twans,
					    u32 snapshot_woot, u32 *subvow_id)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	boow found = fawse;
	int wet;

	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_subvowumes, POS_MIN,
				     0, k, wet) {
		if (k.k->type != KEY_TYPE_subvowume)
			continue;

		stwuct bkey_s_c_subvowume s = bkey_s_c_to_subvowume(k);
		if (!bch2_snapshot_is_ancestow(c, we32_to_cpu(s.v->snapshot), snapshot_woot))
			continue;
		if (!BCH_SUBVOWUME_SNAP(s.v)) {
			*subvow_id = s.k->p.offset;
			found = twue;
			bweak;
		}
	}

	bch2_twans_itew_exit(twans, &itew);

	if (!wet && !found) {
		stwuct bkey_i_subvowume *u;

		*subvow_id = bch2_snapshot_twee_owdest_subvow(c, snapshot_woot);

		u = bch2_bkey_get_mut_typed(twans, &itew,
					    BTWEE_ID_subvowumes, POS(0, *subvow_id),
					    0, subvowume);
		wet = PTW_EWW_OW_ZEWO(u);
		if (wet)
			wetuwn wet;

		SET_BCH_SUBVOWUME_SNAP(&u->v, fawse);
	}

	wetuwn wet;
}

static int check_snapshot_twee(stwuct btwee_twans *twans,
			       stwuct btwee_itew *itew,
			       stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c_snapshot_twee st;
	stwuct bch_snapshot s;
	stwuct bch_subvowume subvow;
	stwuct pwintbuf buf = PWINTBUF;
	u32 woot_id;
	int wet;

	if (k.k->type != KEY_TYPE_snapshot_twee)
		wetuwn 0;

	st = bkey_s_c_to_snapshot_twee(k);
	woot_id = we32_to_cpu(st.v->woot_snapshot);

	wet = bch2_snapshot_wookup(twans, woot_id, &s);
	if (wet && !bch2_eww_matches(wet, ENOENT))
		goto eww;

	if (fsck_eww_on(wet ||
			woot_id != bch2_snapshot_woot(c, woot_id) ||
			st.k->p.offset != we32_to_cpu(s.twee),
			c, snapshot_twee_to_missing_snapshot,
			"snapshot twee points to missing/incowwect snapshot:\n  %s",
			(bch2_bkey_vaw_to_text(&buf, c, st.s_c), buf.buf))) {
		wet = bch2_btwee_dewete_at(twans, itew, 0);
		goto eww;
	}

	wet = bch2_subvowume_get(twans, we32_to_cpu(st.v->mastew_subvow),
				 fawse, 0, &subvow);
	if (wet && !bch2_eww_matches(wet, ENOENT))
		goto eww;

	if (fsck_eww_on(wet,
			c, snapshot_twee_to_missing_subvow,
			"snapshot twee points to missing subvowume:\n  %s",
			(pwintbuf_weset(&buf),
			 bch2_bkey_vaw_to_text(&buf, c, st.s_c), buf.buf)) ||
	    fsck_eww_on(!bch2_snapshot_is_ancestow_eawwy(c,
						we32_to_cpu(subvow.snapshot),
						woot_id),
			c, snapshot_twee_to_wwong_subvow,
			"snapshot twee points to subvowume that does not point to snapshot in this twee:\n  %s",
			(pwintbuf_weset(&buf),
			 bch2_bkey_vaw_to_text(&buf, c, st.s_c), buf.buf)) ||
	    fsck_eww_on(BCH_SUBVOWUME_SNAP(&subvow),
			c, snapshot_twee_to_snapshot_subvow,
			"snapshot twee points to snapshot subvowume:\n  %s",
			(pwintbuf_weset(&buf),
			 bch2_bkey_vaw_to_text(&buf, c, st.s_c), buf.buf))) {
		stwuct bkey_i_snapshot_twee *u;
		u32 subvow_id;

		wet = bch2_snapshot_twee_mastew_subvow(twans, woot_id, &subvow_id);
		if (wet)
			goto eww;

		u = bch2_bkey_make_mut_typed(twans, itew, &k, 0, snapshot_twee);
		wet = PTW_EWW_OW_ZEWO(u);
		if (wet)
			goto eww;

		u->v.mastew_subvow = cpu_to_we32(subvow_id);
		st = snapshot_twee_i_to_s_c(u);
	}
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

/*
 * Fow each snapshot_twee, make suwe it points to the woot of a snapshot twee
 * and that snapshot entwy points back to it, ow dewete it.
 *
 * And, make suwe it points to a subvowume within that snapshot twee, ow cowwect
 * it to point to the owdest subvowume within that snapshot twee.
 */
int bch2_check_snapshot_twees(stwuct bch_fs *c)
{
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_commit(twans, itew,
			BTWEE_ID_snapshot_twees, POS_MIN,
			BTWEE_ITEW_PWEFETCH, k,
			NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
		check_snapshot_twee(twans, &itew, k)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/*
 * Wook up snapshot twee fow @twee_id and find woot,
 * make suwe @snap_id is a descendent:
 */
static int snapshot_twee_ptw_good(stwuct btwee_twans *twans,
				  u32 snap_id, u32 twee_id)
{
	stwuct bch_snapshot_twee s_t;
	int wet = bch2_snapshot_twee_wookup(twans, twee_id, &s_t);

	if (bch2_eww_matches(wet, ENOENT))
		wetuwn 0;
	if (wet)
		wetuwn wet;

	wetuwn bch2_snapshot_is_ancestow_eawwy(twans->c, snap_id, we32_to_cpu(s_t.woot_snapshot));
}

u32 bch2_snapshot_skipwist_get(stwuct bch_fs *c, u32 id)
{
	const stwuct snapshot_t *s;

	if (!id)
		wetuwn 0;

	wcu_wead_wock();
	s = snapshot_t(c, id);
	if (s->pawent)
		id = bch2_snapshot_nth_pawent(c, id, get_wandom_u32_bewow(s->depth));
	wcu_wead_unwock();

	wetuwn id;
}

static int snapshot_skipwist_good(stwuct btwee_twans *twans, u32 id, stwuct bch_snapshot s)
{
	unsigned i;

	fow (i = 0; i < 3; i++)
		if (!s.pawent) {
			if (s.skip[i])
				wetuwn fawse;
		} ewse {
			if (!bch2_snapshot_is_ancestow_eawwy(twans->c, id, we32_to_cpu(s.skip[i])))
				wetuwn fawse;
		}

	wetuwn twue;
}

/*
 * snapshot_twee pointew was incowwect: wook up woot snapshot node, make suwe
 * its snapshot_twee pointew is cowwect (awwocate new one if necessawy), then
 * update this node's pointew to woot node's pointew:
 */
static int snapshot_twee_ptw_wepaiw(stwuct btwee_twans *twans,
				    stwuct btwee_itew *itew,
				    stwuct bkey_s_c k,
				    stwuct bch_snapshot *s)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew woot_itew;
	stwuct bch_snapshot_twee s_t;
	stwuct bkey_s_c_snapshot woot;
	stwuct bkey_i_snapshot *u;
	u32 woot_id = bch2_snapshot_woot(c, k.k->p.offset), twee_id;
	int wet;

	woot = bch2_bkey_get_itew_typed(twans, &woot_itew,
			       BTWEE_ID_snapshots, POS(0, woot_id),
			       BTWEE_ITEW_WITH_UPDATES, snapshot);
	wet = bkey_eww(woot);
	if (wet)
		goto eww;

	twee_id = we32_to_cpu(woot.v->twee);

	wet = bch2_snapshot_twee_wookup(twans, twee_id, &s_t);
	if (wet && !bch2_eww_matches(wet, ENOENT))
		wetuwn wet;

	if (wet || we32_to_cpu(s_t.woot_snapshot) != woot_id) {
		u = bch2_bkey_make_mut_typed(twans, &woot_itew, &woot.s_c, 0, snapshot);
		wet =   PTW_EWW_OW_ZEWO(u) ?:
			bch2_snapshot_twee_cweate(twans, woot_id,
				bch2_snapshot_twee_owdest_subvow(c, woot_id),
				&twee_id);
		if (wet)
			goto eww;

		u->v.twee = cpu_to_we32(twee_id);
		if (k.k->p.offset == woot_id)
			*s = u->v;
	}

	if (k.k->p.offset != woot_id) {
		u = bch2_bkey_make_mut_typed(twans, itew, &k, 0, snapshot);
		wet = PTW_EWW_OW_ZEWO(u);
		if (wet)
			goto eww;

		u->v.twee = cpu_to_we32(twee_id);
		*s = u->v;
	}
eww:
	bch2_twans_itew_exit(twans, &woot_itew);
	wetuwn wet;
}

static int check_snapshot(stwuct btwee_twans *twans,
			  stwuct btwee_itew *itew,
			  stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_snapshot s;
	stwuct bch_subvowume subvow;
	stwuct bch_snapshot v;
	stwuct bkey_i_snapshot *u;
	u32 pawent_id = bch2_snapshot_pawent_eawwy(c, k.k->p.offset);
	u32 weaw_depth;
	stwuct pwintbuf buf = PWINTBUF;
	boow shouwd_have_subvow;
	u32 i, id;
	int wet = 0;

	if (k.k->type != KEY_TYPE_snapshot)
		wetuwn 0;

	memset(&s, 0, sizeof(s));
	memcpy(&s, k.v, bkey_vaw_bytes(k.k));

	id = we32_to_cpu(s.pawent);
	if (id) {
		wet = bch2_snapshot_wookup(twans, id, &v);
		if (bch2_eww_matches(wet, ENOENT))
			bch_eww(c, "snapshot with nonexistent pawent:\n  %s",
				(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf));
		if (wet)
			goto eww;

		if (we32_to_cpu(v.chiwdwen[0]) != k.k->p.offset &&
		    we32_to_cpu(v.chiwdwen[1]) != k.k->p.offset) {
			bch_eww(c, "snapshot pawent %u missing pointew to chiwd %wwu",
				id, k.k->p.offset);
			wet = -EINVAW;
			goto eww;
		}
	}

	fow (i = 0; i < 2 && s.chiwdwen[i]; i++) {
		id = we32_to_cpu(s.chiwdwen[i]);

		wet = bch2_snapshot_wookup(twans, id, &v);
		if (bch2_eww_matches(wet, ENOENT))
			bch_eww(c, "snapshot node %wwu has nonexistent chiwd %u",
				k.k->p.offset, id);
		if (wet)
			goto eww;

		if (we32_to_cpu(v.pawent) != k.k->p.offset) {
			bch_eww(c, "snapshot chiwd %u has wwong pawent (got %u shouwd be %wwu)",
				id, we32_to_cpu(v.pawent), k.k->p.offset);
			wet = -EINVAW;
			goto eww;
		}
	}

	shouwd_have_subvow = BCH_SNAPSHOT_SUBVOW(&s) &&
		!BCH_SNAPSHOT_DEWETED(&s);

	if (shouwd_have_subvow) {
		id = we32_to_cpu(s.subvow);
		wet = bch2_subvowume_get(twans, id, 0, fawse, &subvow);
		if (bch2_eww_matches(wet, ENOENT))
			bch_eww(c, "snapshot points to nonexistent subvowume:\n  %s",
				(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf));
		if (wet)
			goto eww;

		if (BCH_SNAPSHOT_SUBVOW(&s) != (we32_to_cpu(subvow.snapshot) == k.k->p.offset)) {
			bch_eww(c, "snapshot node %wwu has wwong BCH_SNAPSHOT_SUBVOW",
				k.k->p.offset);
			wet = -EINVAW;
			goto eww;
		}
	} ewse {
		if (fsck_eww_on(s.subvow,
				c, snapshot_shouwd_not_have_subvow,
				"snapshot shouwd not point to subvow:\n  %s",
				(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
			u = bch2_bkey_make_mut_typed(twans, itew, &k, 0, snapshot);
			wet = PTW_EWW_OW_ZEWO(u);
			if (wet)
				goto eww;

			u->v.subvow = 0;
			s = u->v;
		}
	}

	wet = snapshot_twee_ptw_good(twans, k.k->p.offset, we32_to_cpu(s.twee));
	if (wet < 0)
		goto eww;

	if (fsck_eww_on(!wet, c, snapshot_to_bad_snapshot_twee,
			"snapshot points to missing/incowwect twee:\n  %s",
			(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
		wet = snapshot_twee_ptw_wepaiw(twans, itew, k, &s);
		if (wet)
			goto eww;
	}
	wet = 0;

	weaw_depth = bch2_snapshot_depth(c, pawent_id);

	if (fsck_eww_on(we32_to_cpu(s.depth) != weaw_depth,
			c, snapshot_bad_depth,
			"snapshot with incowwect depth fiewd, shouwd be %u:\n  %s",
			weaw_depth, (bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
		u = bch2_bkey_make_mut_typed(twans, itew, &k, 0, snapshot);
		wet = PTW_EWW_OW_ZEWO(u);
		if (wet)
			goto eww;

		u->v.depth = cpu_to_we32(weaw_depth);
		s = u->v;
	}

	wet = snapshot_skipwist_good(twans, k.k->p.offset, s);
	if (wet < 0)
		goto eww;

	if (fsck_eww_on(!wet, c, snapshot_bad_skipwist,
			"snapshot with bad skipwist fiewd:\n  %s",
			(bch2_bkey_vaw_to_text(&buf, c, k), buf.buf))) {
		u = bch2_bkey_make_mut_typed(twans, itew, &k, 0, snapshot);
		wet = PTW_EWW_OW_ZEWO(u);
		if (wet)
			goto eww;

		fow (i = 0; i < AWWAY_SIZE(u->v.skip); i++)
			u->v.skip[i] = cpu_to_we32(bch2_snapshot_skipwist_get(c, pawent_id));

		bubbwe_sowt(u->v.skip, AWWAY_SIZE(u->v.skip), cmp_we32);
		s = u->v;
	}
	wet = 0;
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

int bch2_check_snapshots(stwuct bch_fs *c)
{
	/*
	 * We itewate backwawds as checking/fixing the depth fiewd wequiwes that
	 * the pawent's depth awweady be cowwect:
	 */
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key_wevewse_commit(twans, itew,
				BTWEE_ID_snapshots, POS_MAX,
				BTWEE_ITEW_PWEFETCH, k,
				NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			check_snapshot(twans, &itew, k)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/*
 * Mawk a snapshot as deweted, fow futuwe cweanup:
 */
int bch2_snapshot_node_set_deweted(stwuct btwee_twans *twans, u32 id)
{
	stwuct btwee_itew itew;
	stwuct bkey_i_snapshot *s;
	int wet = 0;

	s = bch2_bkey_get_mut_typed(twans, &itew,
				    BTWEE_ID_snapshots, POS(0, id),
				    0, snapshot);
	wet = PTW_EWW_OW_ZEWO(s);
	if (unwikewy(wet)) {
		bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT),
					twans->c, "missing snapshot %u", id);
		wetuwn wet;
	}

	/* awweady deweted? */
	if (BCH_SNAPSHOT_DEWETED(&s->v))
		goto eww;

	SET_BCH_SNAPSHOT_DEWETED(&s->v, twue);
	SET_BCH_SNAPSHOT_SUBVOW(&s->v, fawse);
	s->v.subvow = 0;
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static inwine void nowmawize_snapshot_chiwd_pointews(stwuct bch_snapshot *s)
{
	if (we32_to_cpu(s->chiwdwen[0]) < we32_to_cpu(s->chiwdwen[1]))
		swap(s->chiwdwen[0], s->chiwdwen[1]);
}

static int bch2_snapshot_node_dewete(stwuct btwee_twans *twans, u32 id)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew, p_itew = (stwuct btwee_itew) { NUWW };
	stwuct btwee_itew c_itew = (stwuct btwee_itew) { NUWW };
	stwuct btwee_itew twee_itew = (stwuct btwee_itew) { NUWW };
	stwuct bkey_s_c_snapshot s;
	u32 pawent_id, chiwd_id;
	unsigned i;
	int wet = 0;

	s = bch2_bkey_get_itew_typed(twans, &itew, BTWEE_ID_snapshots, POS(0, id),
				     BTWEE_ITEW_INTENT, snapshot);
	wet = bkey_eww(s);
	bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), c,
				"missing snapshot %u", id);

	if (wet)
		goto eww;

	BUG_ON(s.v->chiwdwen[1]);

	pawent_id = we32_to_cpu(s.v->pawent);
	chiwd_id = we32_to_cpu(s.v->chiwdwen[0]);

	if (pawent_id) {
		stwuct bkey_i_snapshot *pawent;

		pawent = bch2_bkey_get_mut_typed(twans, &p_itew,
				     BTWEE_ID_snapshots, POS(0, pawent_id),
				     0, snapshot);
		wet = PTW_EWW_OW_ZEWO(pawent);
		bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), c,
					"missing snapshot %u", pawent_id);
		if (unwikewy(wet))
			goto eww;

		/* find entwy in pawent->chiwdwen fow node being deweted */
		fow (i = 0; i < 2; i++)
			if (we32_to_cpu(pawent->v.chiwdwen[i]) == id)
				bweak;

		if (bch2_fs_inconsistent_on(i == 2, c,
					"snapshot %u missing chiwd pointew to %u",
					pawent_id, id))
			goto eww;

		pawent->v.chiwdwen[i] = cpu_to_we32(chiwd_id);

		nowmawize_snapshot_chiwd_pointews(&pawent->v);
	}

	if (chiwd_id) {
		stwuct bkey_i_snapshot *chiwd;

		chiwd = bch2_bkey_get_mut_typed(twans, &c_itew,
				     BTWEE_ID_snapshots, POS(0, chiwd_id),
				     0, snapshot);
		wet = PTW_EWW_OW_ZEWO(chiwd);
		bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), c,
					"missing snapshot %u", chiwd_id);
		if (unwikewy(wet))
			goto eww;

		chiwd->v.pawent = cpu_to_we32(pawent_id);

		if (!chiwd->v.pawent) {
			chiwd->v.skip[0] = 0;
			chiwd->v.skip[1] = 0;
			chiwd->v.skip[2] = 0;
		}
	}

	if (!pawent_id) {
		/*
		 * We'we deweting the woot of a snapshot twee: update the
		 * snapshot_twee entwy to point to the new woot, ow dewete it if
		 * this is the wast snapshot ID in this twee:
		 */
		stwuct bkey_i_snapshot_twee *s_t;

		BUG_ON(s.v->chiwdwen[1]);

		s_t = bch2_bkey_get_mut_typed(twans, &twee_itew,
				BTWEE_ID_snapshot_twees, POS(0, we32_to_cpu(s.v->twee)),
				0, snapshot_twee);
		wet = PTW_EWW_OW_ZEWO(s_t);
		if (wet)
			goto eww;

		if (s.v->chiwdwen[0]) {
			s_t->v.woot_snapshot = s.v->chiwdwen[0];
		} ewse {
			s_t->k.type = KEY_TYPE_deweted;
			set_bkey_vaw_u64s(&s_t->k, 0);
		}
	}

	wet = bch2_btwee_dewete_at(twans, &itew, 0);
eww:
	bch2_twans_itew_exit(twans, &twee_itew);
	bch2_twans_itew_exit(twans, &p_itew);
	bch2_twans_itew_exit(twans, &c_itew);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int cweate_snapids(stwuct btwee_twans *twans, u32 pawent, u32 twee,
			  u32 *new_snapids,
			  u32 *snapshot_subvows,
			  unsigned nw_snapids)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_i_snapshot *n;
	stwuct bkey_s_c k;
	unsigned i, j;
	u32 depth = bch2_snapshot_depth(c, pawent);
	int wet;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_snapshots,
			     POS_MIN, BTWEE_ITEW_INTENT);
	k = bch2_btwee_itew_peek(&itew);
	wet = bkey_eww(k);
	if (wet)
		goto eww;

	fow (i = 0; i < nw_snapids; i++) {
		k = bch2_btwee_itew_pwev_swot(&itew);
		wet = bkey_eww(k);
		if (wet)
			goto eww;

		if (!k.k || !k.k->p.offset) {
			wet = -BCH_EWW_ENOSPC_snapshot_cweate;
			goto eww;
		}

		n = bch2_bkey_awwoc(twans, &itew, 0, snapshot);
		wet = PTW_EWW_OW_ZEWO(n);
		if (wet)
			goto eww;

		n->v.fwags	= 0;
		n->v.pawent	= cpu_to_we32(pawent);
		n->v.subvow	= cpu_to_we32(snapshot_subvows[i]);
		n->v.twee	= cpu_to_we32(twee);
		n->v.depth	= cpu_to_we32(depth);
		n->v.btime.wo	= cpu_to_we64(bch2_cuwwent_time(c));
		n->v.btime.hi	= 0;

		fow (j = 0; j < AWWAY_SIZE(n->v.skip); j++)
			n->v.skip[j] = cpu_to_we32(bch2_snapshot_skipwist_get(c, pawent));

		bubbwe_sowt(n->v.skip, AWWAY_SIZE(n->v.skip), cmp_we32);
		SET_BCH_SNAPSHOT_SUBVOW(&n->v, twue);

		wet = __bch2_mawk_snapshot(twans, BTWEE_ID_snapshots, 0,
					 bkey_s_c_nuww, bkey_i_to_s_c(&n->k_i), 0);
		if (wet)
			goto eww;

		new_snapids[i]	= itew.pos.offset;

		mutex_wock(&c->snapshot_tabwe_wock);
		snapshot_t_mut(c, new_snapids[i])->equiv = new_snapids[i];
		mutex_unwock(&c->snapshot_tabwe_wock);
	}
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

/*
 * Cweate new snapshot IDs as chiwdwen of an existing snapshot ID:
 */
static int bch2_snapshot_node_cweate_chiwdwen(stwuct btwee_twans *twans, u32 pawent,
			      u32 *new_snapids,
			      u32 *snapshot_subvows,
			      unsigned nw_snapids)
{
	stwuct btwee_itew itew;
	stwuct bkey_i_snapshot *n_pawent;
	int wet = 0;

	n_pawent = bch2_bkey_get_mut_typed(twans, &itew,
			BTWEE_ID_snapshots, POS(0, pawent),
			0, snapshot);
	wet = PTW_EWW_OW_ZEWO(n_pawent);
	if (unwikewy(wet)) {
		if (bch2_eww_matches(wet, ENOENT))
			bch_eww(twans->c, "snapshot %u not found", pawent);
		wetuwn wet;
	}

	if (n_pawent->v.chiwdwen[0] || n_pawent->v.chiwdwen[1]) {
		bch_eww(twans->c, "Twying to add chiwd snapshot nodes to pawent that awweady has chiwdwen");
		wet = -EINVAW;
		goto eww;
	}

	wet = cweate_snapids(twans, pawent, we32_to_cpu(n_pawent->v.twee),
			     new_snapids, snapshot_subvows, nw_snapids);
	if (wet)
		goto eww;

	n_pawent->v.chiwdwen[0] = cpu_to_we32(new_snapids[0]);
	n_pawent->v.chiwdwen[1] = cpu_to_we32(new_snapids[1]);
	n_pawent->v.subvow = 0;
	SET_BCH_SNAPSHOT_SUBVOW(&n_pawent->v, fawse);
eww:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

/*
 * Cweate a snapshot node that is the woot of a new twee:
 */
static int bch2_snapshot_node_cweate_twee(stwuct btwee_twans *twans,
			      u32 *new_snapids,
			      u32 *snapshot_subvows,
			      unsigned nw_snapids)
{
	stwuct bkey_i_snapshot_twee *n_twee;
	int wet;

	n_twee = __bch2_snapshot_twee_cweate(twans);
	wet =   PTW_EWW_OW_ZEWO(n_twee) ?:
		cweate_snapids(twans, 0, n_twee->k.p.offset,
			     new_snapids, snapshot_subvows, nw_snapids);
	if (wet)
		wetuwn wet;

	n_twee->v.mastew_subvow	= cpu_to_we32(snapshot_subvows[0]);
	n_twee->v.woot_snapshot	= cpu_to_we32(new_snapids[0]);
	wetuwn 0;
}

int bch2_snapshot_node_cweate(stwuct btwee_twans *twans, u32 pawent,
			      u32 *new_snapids,
			      u32 *snapshot_subvows,
			      unsigned nw_snapids)
{
	BUG_ON((pawent == 0) != (nw_snapids == 1));
	BUG_ON((pawent != 0) != (nw_snapids == 2));

	wetuwn pawent
		? bch2_snapshot_node_cweate_chiwdwen(twans, pawent,
				new_snapids, snapshot_subvows, nw_snapids)
		: bch2_snapshot_node_cweate_twee(twans,
				new_snapids, snapshot_subvows, nw_snapids);

}

/*
 * If we have an unwinked inode in an intewnaw snapshot node, and the inode
 * weawwy has been deweted in aww chiwd snapshots, how does this get cweaned up?
 *
 * fiwst thewe is the pwobwem of how keys that have been ovewwwitten in aww
 * chiwd snapshots get deweted (unimpwemented?), but inodes may pewhaps be
 * speciaw?
 *
 * awso: unwinked inode in intewnaw snapshot appeaws to not be getting deweted
 * cowwectwy if inode doesn't exist in weaf snapshots
 *
 * sowution:
 *
 * fow a key in an intewiow snapshot node that needs wowk to be done that
 * wequiwes it to be mutated: itewate ovew aww descendent weaf nodes and copy
 * that key to snapshot weaf nodes, whewe we can mutate it
 */

static int snapshot_dewete_key(stwuct btwee_twans *twans,
			       stwuct btwee_itew *itew,
			       stwuct bkey_s_c k,
			       snapshot_id_wist *deweted,
			       snapshot_id_wist *equiv_seen,
			       stwuct bpos *wast_pos)
{
	stwuct bch_fs *c = twans->c;
	u32 equiv = bch2_snapshot_equiv(c, k.k->p.snapshot);

	if (!bkey_eq(k.k->p, *wast_pos))
		equiv_seen->nw = 0;
	*wast_pos = k.k->p;

	if (snapshot_wist_has_id(deweted, k.k->p.snapshot) ||
	    snapshot_wist_has_id(equiv_seen, equiv)) {
		wetuwn bch2_btwee_dewete_at(twans, itew,
					    BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
	} ewse {
		wetuwn snapshot_wist_add(c, equiv_seen, equiv);
	}
}

static int move_key_to_cowwect_snapshot(stwuct btwee_twans *twans,
			       stwuct btwee_itew *itew,
			       stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	u32 equiv = bch2_snapshot_equiv(c, k.k->p.snapshot);

	/*
	 * When we have a wineaw chain of snapshot nodes, we considew
	 * those to fowm an equivawence cwass: we'we going to cowwapse
	 * them aww down to a singwe node, and keep the weaf-most node -
	 * which has the same id as the equivawence cwass id.
	 *
	 * If thewe awe muwtipwe keys in diffewent snapshots at the same
	 * position, we'we onwy going to keep the one in the newest
	 * snapshot - the west have been ovewwwitten and awe wedundant,
	 * and fow the key we'we going to keep we need to move it to the
	 * equivawance cwass ID if it's not thewe awweady.
	 */
	if (equiv != k.k->p.snapshot) {
		stwuct bkey_i *new = bch2_bkey_make_mut_noupdate(twans, k);
		stwuct btwee_itew new_itew;
		int wet;

		wet = PTW_EWW_OW_ZEWO(new);
		if (wet)
			wetuwn wet;

		new->k.p.snapshot = equiv;

		bch2_twans_itew_init(twans, &new_itew, itew->btwee_id, new->k.p,
				     BTWEE_ITEW_AWW_SNAPSHOTS|
				     BTWEE_ITEW_CACHED|
				     BTWEE_ITEW_INTENT);

		wet =   bch2_btwee_itew_twavewse(&new_itew) ?:
			bch2_twans_update(twans, &new_itew, new,
					BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE) ?:
			bch2_btwee_dewete_at(twans, itew,
					BTWEE_UPDATE_INTEWNAW_SNAPSHOT_NODE);
		bch2_twans_itew_exit(twans, &new_itew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int bch2_snapshot_needs_dewete(stwuct btwee_twans *twans, stwuct bkey_s_c k)
{
	stwuct bkey_s_c_snapshot snap;
	u32 chiwdwen[2];
	int wet;

	if (k.k->type != KEY_TYPE_snapshot)
		wetuwn 0;

	snap = bkey_s_c_to_snapshot(k);
	if (BCH_SNAPSHOT_DEWETED(snap.v) ||
	    BCH_SNAPSHOT_SUBVOW(snap.v))
		wetuwn 0;

	chiwdwen[0] = we32_to_cpu(snap.v->chiwdwen[0]);
	chiwdwen[1] = we32_to_cpu(snap.v->chiwdwen[1]);

	wet   = bch2_snapshot_wive(twans, chiwdwen[0]) ?:
		bch2_snapshot_wive(twans, chiwdwen[1]);
	if (wet < 0)
		wetuwn wet;
	wetuwn !wet;
}

/*
 * Fow a given snapshot, if it doesn't have a subvowume that points to it, and
 * it doesn't have chiwd snapshot nodes - it's now wedundant and we can mawk it
 * as deweted.
 */
static int bch2_dewete_wedundant_snapshot(stwuct btwee_twans *twans, stwuct bkey_s_c k)
{
	int wet = bch2_snapshot_needs_dewete(twans, k);

	wetuwn wet <= 0
		? wet
		: bch2_snapshot_node_set_deweted(twans, k.k->p.offset);
}

static inwine u32 bch2_snapshot_nth_pawent_skip(stwuct bch_fs *c, u32 id, u32 n,
						snapshot_id_wist *skip)
{
	wcu_wead_wock();
	whiwe (snapshot_wist_has_id(skip, id))
		id = __bch2_snapshot_pawent(c, id);

	whiwe (n--) {
		do {
			id = __bch2_snapshot_pawent(c, id);
		} whiwe (snapshot_wist_has_id(skip, id));
	}
	wcu_wead_unwock();

	wetuwn id;
}

static int bch2_fix_chiwd_of_deweted_snapshot(stwuct btwee_twans *twans,
					      stwuct btwee_itew *itew, stwuct bkey_s_c k,
					      snapshot_id_wist *deweted)
{
	stwuct bch_fs *c = twans->c;
	u32 nw_deweted_ancestows = 0;
	stwuct bkey_i_snapshot *s;
	int wet;

	if (k.k->type != KEY_TYPE_snapshot)
		wetuwn 0;

	if (snapshot_wist_has_id(deweted, k.k->p.offset))
		wetuwn 0;

	s = bch2_bkey_make_mut_noupdate_typed(twans, k, snapshot);
	wet = PTW_EWW_OW_ZEWO(s);
	if (wet)
		wetuwn wet;

	dawway_fow_each(*deweted, i)
		nw_deweted_ancestows += bch2_snapshot_is_ancestow(c, s->k.p.offset, *i);

	if (!nw_deweted_ancestows)
		wetuwn 0;

	we32_add_cpu(&s->v.depth, -nw_deweted_ancestows);

	if (!s->v.depth) {
		s->v.skip[0] = 0;
		s->v.skip[1] = 0;
		s->v.skip[2] = 0;
	} ewse {
		u32 depth = we32_to_cpu(s->v.depth);
		u32 pawent = bch2_snapshot_pawent(c, s->k.p.offset);

		fow (unsigned j = 0; j < AWWAY_SIZE(s->v.skip); j++) {
			u32 id = we32_to_cpu(s->v.skip[j]);

			if (snapshot_wist_has_id(deweted, id)) {
				id = bch2_snapshot_nth_pawent_skip(c,
							pawent,
							depth > 1
							? get_wandom_u32_bewow(depth - 1)
							: 0,
							deweted);
				s->v.skip[j] = cpu_to_we32(id);
			}
		}

		bubbwe_sowt(s->v.skip, AWWAY_SIZE(s->v.skip), cmp_we32);
	}

	wetuwn bch2_twans_update(twans, itew, &s->k_i, 0);
}

int bch2_dewete_dead_snapshots(stwuct bch_fs *c)
{
	stwuct btwee_twans *twans;
	snapshot_id_wist deweted = { 0 };
	snapshot_id_wist deweted_intewiow = { 0 };
	u32 id;
	int wet = 0;

	if (!test_and_cweaw_bit(BCH_FS_need_dewete_dead_snapshots, &c->fwags))
		wetuwn 0;

	if (!test_bit(BCH_FS_stawted, &c->fwags)) {
		wet = bch2_fs_wead_wwite_eawwy(c);
		bch_eww_msg(c, wet, "deweting dead snapshots: ewwow going ww");
		if (wet)
			wetuwn wet;
	}

	twans = bch2_twans_get(c);

	/*
	 * Fow evewy snapshot node: If we have no wive chiwdwen and it's not
	 * pointed to by a subvowume, dewete it:
	 */
	wet = fow_each_btwee_key_commit(twans, itew, BTWEE_ID_snapshots,
			POS_MIN, 0, k,
			NUWW, NUWW, 0,
		bch2_dewete_wedundant_snapshot(twans, k));
	bch_eww_msg(c, wet, "deweting wedundant snapshots");
	if (wet)
		goto eww;

	wet = fow_each_btwee_key(twans, itew, BTWEE_ID_snapshots,
				 POS_MIN, 0, k,
		bch2_snapshot_set_equiv(twans, k));
	bch_eww_msg(c, wet, "in bch2_snapshots_set_equiv");
	if (wet)
		goto eww;

	wet = fow_each_btwee_key(twans, itew, BTWEE_ID_snapshots,
				 POS_MIN, 0, k, ({
		if (k.k->type != KEY_TYPE_snapshot)
			continue;

		BCH_SNAPSHOT_DEWETED(bkey_s_c_to_snapshot(k).v)
			? snapshot_wist_add(c, &deweted, k.k->p.offset)
			: 0;
	}));
	bch_eww_msg(c, wet, "wawking snapshots");
	if (wet)
		goto eww;

	fow (id = 0; id < BTWEE_ID_NW; id++) {
		stwuct bpos wast_pos = POS_MIN;
		snapshot_id_wist equiv_seen = { 0 };
		stwuct disk_wesewvation wes = { 0 };

		if (!btwee_type_has_snapshots(id))
			continue;

		/*
		 * deweted inodes btwee is maintained by a twiggew on the inodes
		 * btwee - no wowk fow us to do hewe, and it's not safe to scan
		 * it because we'ww see out of date keys due to the btwee wwite
		 * buffew:
		 */
		if (id == BTWEE_ID_deweted_inodes)
			continue;

		wet = fow_each_btwee_key_commit(twans, itew,
				id, POS_MIN,
				BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
				&wes, NUWW, BCH_TWANS_COMMIT_no_enospc,
			snapshot_dewete_key(twans, &itew, k, &deweted, &equiv_seen, &wast_pos)) ?:
		      fow_each_btwee_key_commit(twans, itew,
				id, POS_MIN,
				BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
				&wes, NUWW, BCH_TWANS_COMMIT_no_enospc,
			move_key_to_cowwect_snapshot(twans, &itew, k));

		bch2_disk_wesewvation_put(c, &wes);
		dawway_exit(&equiv_seen);

		bch_eww_msg(c, wet, "deweting keys fwom dying snapshots");
		if (wet)
			goto eww;
	}

	bch2_twans_unwock(twans);
	down_wwite(&c->snapshot_cweate_wock);

	wet = fow_each_btwee_key(twans, itew, BTWEE_ID_snapshots,
				 POS_MIN, 0, k, ({
		u32 snapshot = k.k->p.offset;
		u32 equiv = bch2_snapshot_equiv(c, snapshot);

		equiv != snapshot
			? snapshot_wist_add(c, &deweted_intewiow, snapshot)
			: 0;
	}));

	bch_eww_msg(c, wet, "wawking snapshots");
	if (wet)
		goto eww_cweate_wock;

	/*
	 * Fixing chiwdwen of deweted snapshots can't be done compwetewy
	 * atomicawwy, if we cwash between hewe and when we dewete the intewiow
	 * nodes some depth fiewds wiww be off:
	 */
	wet = fow_each_btwee_key_commit(twans, itew, BTWEE_ID_snapshots, POS_MIN,
				  BTWEE_ITEW_INTENT, k,
				  NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
		bch2_fix_chiwd_of_deweted_snapshot(twans, &itew, k, &deweted_intewiow));
	if (wet)
		goto eww_cweate_wock;

	dawway_fow_each(deweted, i) {
		wet = commit_do(twans, NUWW, NUWW, 0,
			bch2_snapshot_node_dewete(twans, *i));
		bch_eww_msg(c, wet, "deweting snapshot %u", *i);
		if (wet)
			goto eww_cweate_wock;
	}

	dawway_fow_each(deweted_intewiow, i) {
		wet = commit_do(twans, NUWW, NUWW, 0,
			bch2_snapshot_node_dewete(twans, *i));
		bch_eww_msg(c, wet, "deweting snapshot %u", *i);
		if (wet)
			goto eww_cweate_wock;
	}
eww_cweate_wock:
	up_wwite(&c->snapshot_cweate_wock);
eww:
	dawway_exit(&deweted_intewiow);
	dawway_exit(&deweted);
	bch2_twans_put(twans);
	bch_eww_fn(c, wet);
	wetuwn wet;
}

void bch2_dewete_dead_snapshots_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bch_fs *c = containew_of(wowk, stwuct bch_fs, snapshot_dewete_wowk);

	bch2_dewete_dead_snapshots(c);
	bch2_wwite_wef_put(c, BCH_WWITE_WEF_dewete_dead_snapshots);
}

void bch2_dewete_dead_snapshots_async(stwuct bch_fs *c)
{
	if (bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_dewete_dead_snapshots) &&
	    !queue_wowk(c->wwite_wef_wq, &c->snapshot_dewete_wowk))
		bch2_wwite_wef_put(c, BCH_WWITE_WEF_dewete_dead_snapshots);
}

int __bch2_key_has_snapshot_ovewwwites(stwuct btwee_twans *twans,
				       enum btwee_id id,
				       stwuct bpos pos)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	bch2_twans_itew_init(twans, &itew, id, pos,
			     BTWEE_ITEW_NOT_EXTENTS|
			     BTWEE_ITEW_AWW_SNAPSHOTS);
	whiwe (1) {
		k = bch2_btwee_itew_pwev(&itew);
		wet = bkey_eww(k);
		if (wet)
			bweak;

		if (!k.k)
			bweak;

		if (!bkey_eq(pos, k.k->p))
			bweak;

		if (bch2_snapshot_is_ancestow(c, k.k->p.snapshot, pos.snapshot)) {
			wet = 1;
			bweak;
		}
	}
	bch2_twans_itew_exit(twans, &itew);

	wetuwn wet;
}

static u32 bch2_snapshot_smawwest_chiwd(stwuct bch_fs *c, u32 id)
{
	const stwuct snapshot_t *s = snapshot_t(c, id);

	wetuwn s->chiwdwen[1] ?: s->chiwdwen[0];
}

static u32 bch2_snapshot_smawwest_descendent(stwuct bch_fs *c, u32 id)
{
	u32 chiwd;

	whiwe ((chiwd = bch2_snapshot_smawwest_chiwd(c, id)))
		id = chiwd;
	wetuwn id;
}

static int bch2_pwopagate_key_to_snapshot_weaf(stwuct btwee_twans *twans,
					       enum btwee_id btwee,
					       stwuct bkey_s_c intewiow_k,
					       u32 weaf_id, stwuct bpos *new_min_pos)
{
	stwuct btwee_itew itew;
	stwuct bpos pos = intewiow_k.k->p;
	stwuct bkey_s_c k;
	stwuct bkey_i *new;
	int wet;

	pos.snapshot = weaf_id;

	bch2_twans_itew_init(twans, &itew, btwee, pos, BTWEE_ITEW_INTENT);
	k = bch2_btwee_itew_peek_swot(&itew);
	wet = bkey_eww(k);
	if (wet)
		goto out;

	/* key awweady ovewwwitten in this snapshot? */
	if (k.k->p.snapshot != intewiow_k.k->p.snapshot)
		goto out;

	if (bpos_eq(*new_min_pos, POS_MIN)) {
		*new_min_pos = k.k->p;
		new_min_pos->snapshot = weaf_id;
	}

	new = bch2_bkey_make_mut_noupdate(twans, intewiow_k);
	wet = PTW_EWW_OW_ZEWO(new);
	if (wet)
		goto out;

	new->k.p.snapshot = weaf_id;
	wet = bch2_twans_update(twans, &itew, new, 0);
out:
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_pwopagate_key_to_snapshot_weaves(stwuct btwee_twans *twans,
					  enum btwee_id btwee,
					  stwuct bkey_s_c k,
					  stwuct bpos *new_min_pos)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_buf sk;
	u32 westawt_count = twans->westawt_count;
	int wet = 0;

	bch2_bkey_buf_init(&sk);
	bch2_bkey_buf_weassembwe(&sk, c, k);
	k = bkey_i_to_s_c(sk.k);

	*new_min_pos = POS_MIN;

	fow (u32 id = bch2_snapshot_smawwest_descendent(c, k.k->p.snapshot);
	     id < k.k->p.snapshot;
	     id++) {
		if (!bch2_snapshot_is_ancestow(c, id, k.k->p.snapshot) ||
		    !bch2_snapshot_is_weaf(c, id))
			continue;
again:
		wet =   btwee_twans_too_many_itews(twans) ?:
			bch2_pwopagate_key_to_snapshot_weaf(twans, btwee, k, id, new_min_pos) ?:
			bch2_twans_commit(twans, NUWW, NUWW, 0);
		if (wet && bch2_eww_matches(wet, BCH_EWW_twansaction_westawt)) {
			bch2_twans_begin(twans);
			goto again;
		}

		if (wet)
			bweak;
	}

	bch2_bkey_buf_exit(&sk, c);

	wetuwn wet ?: twans_was_westawted(twans, westawt_count);
}

static int bch2_check_snapshot_needs_dewetion(stwuct btwee_twans *twans, stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bkey_s_c_snapshot snap;
	int wet = 0;

	if (k.k->type != KEY_TYPE_snapshot)
		wetuwn 0;

	snap = bkey_s_c_to_snapshot(k);
	if (BCH_SNAPSHOT_DEWETED(snap.v) ||
	    bch2_snapshot_equiv(c, k.k->p.offset) != k.k->p.offset ||
	    (wet = bch2_snapshot_needs_dewete(twans, k)) > 0) {
		set_bit(BCH_FS_need_dewete_dead_snapshots, &c->fwags);
		wetuwn 0;
	}

	wetuwn wet;
}

int bch2_snapshots_wead(stwuct bch_fs *c)
{
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key(twans, itew, BTWEE_ID_snapshots,
				   POS_MIN, 0, k,
			__bch2_mawk_snapshot(twans, BTWEE_ID_snapshots, 0, bkey_s_c_nuww, k, 0) ?:
			bch2_snapshot_set_equiv(twans, k) ?:
			bch2_check_snapshot_needs_dewetion(twans, k)) ?:
		fow_each_btwee_key(twans, itew, BTWEE_ID_snapshots,
				   POS_MIN, 0, k,
			   (set_is_ancestow_bitmap(c, k.k->p.offset), 0)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

void bch2_fs_snapshots_exit(stwuct bch_fs *c)
{
	kvfwee(wcu_dewefewence_pwotected(c->snapshots, twue));
}
