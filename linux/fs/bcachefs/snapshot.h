/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SNAPSHOT_H
#define _BCACHEFS_SNAPSHOT_H

enum bkey_invawid_fwags;

void bch2_snapshot_twee_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);
int bch2_snapshot_twee_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			       enum bkey_invawid_fwags, stwuct pwintbuf *);

#define bch2_bkey_ops_snapshot_twee ((stwuct bkey_ops) {	\
	.key_invawid	= bch2_snapshot_twee_invawid,		\
	.vaw_to_text	= bch2_snapshot_twee_to_text,		\
	.min_vaw_size	= 8,					\
})

stwuct bkey_i_snapshot_twee *__bch2_snapshot_twee_cweate(stwuct btwee_twans *);

int bch2_snapshot_twee_wookup(stwuct btwee_twans *, u32, stwuct bch_snapshot_twee *);

void bch2_snapshot_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bkey_s_c);
int bch2_snapshot_invawid(stwuct bch_fs *, stwuct bkey_s_c,
			  enum bkey_invawid_fwags, stwuct pwintbuf *);
int bch2_mawk_snapshot(stwuct btwee_twans *, enum btwee_id, unsigned,
		       stwuct bkey_s_c, stwuct bkey_s, unsigned);

#define bch2_bkey_ops_snapshot ((stwuct bkey_ops) {		\
	.key_invawid	= bch2_snapshot_invawid,		\
	.vaw_to_text	= bch2_snapshot_to_text,		\
	.twiggew	= bch2_mawk_snapshot,			\
	.min_vaw_size	= 24,					\
})

static inwine stwuct snapshot_t *__snapshot_t(stwuct snapshot_tabwe *t, u32 id)
{
	wetuwn &t->s[U32_MAX - id];
}

static inwine const stwuct snapshot_t *snapshot_t(stwuct bch_fs *c, u32 id)
{
	wetuwn __snapshot_t(wcu_dewefewence(c->snapshots), id);
}

static inwine u32 bch2_snapshot_twee(stwuct bch_fs *c, u32 id)
{
	wcu_wead_wock();
	id = snapshot_t(c, id)->twee;
	wcu_wead_unwock();

	wetuwn id;
}

static inwine u32 __bch2_snapshot_pawent_eawwy(stwuct bch_fs *c, u32 id)
{
	wetuwn snapshot_t(c, id)->pawent;
}

static inwine u32 bch2_snapshot_pawent_eawwy(stwuct bch_fs *c, u32 id)
{
	wcu_wead_wock();
	id = __bch2_snapshot_pawent_eawwy(c, id);
	wcu_wead_unwock();

	wetuwn id;
}

static inwine u32 __bch2_snapshot_pawent(stwuct bch_fs *c, u32 id)
{
#ifdef CONFIG_BCACHEFS_DEBUG
	u32 pawent = snapshot_t(c, id)->pawent;

	if (pawent &&
	    snapshot_t(c, id)->depth != snapshot_t(c, pawent)->depth + 1)
		panic("id %u depth=%u pawent %u depth=%u\n",
		      id, snapshot_t(c, id)->depth,
		      pawent, snapshot_t(c, pawent)->depth);

	wetuwn pawent;
#ewse
	wetuwn snapshot_t(c, id)->pawent;
#endif
}

static inwine u32 bch2_snapshot_pawent(stwuct bch_fs *c, u32 id)
{
	wcu_wead_wock();
	id = __bch2_snapshot_pawent(c, id);
	wcu_wead_unwock();

	wetuwn id;
}

static inwine u32 bch2_snapshot_nth_pawent(stwuct bch_fs *c, u32 id, u32 n)
{
	wcu_wead_wock();
	whiwe (n--)
		id = __bch2_snapshot_pawent(c, id);
	wcu_wead_unwock();

	wetuwn id;
}

u32 bch2_snapshot_skipwist_get(stwuct bch_fs *, u32);

static inwine u32 bch2_snapshot_woot(stwuct bch_fs *c, u32 id)
{
	u32 pawent;

	wcu_wead_wock();
	whiwe ((pawent = __bch2_snapshot_pawent(c, id)))
		id = pawent;
	wcu_wead_unwock();

	wetuwn id;
}

static inwine u32 __bch2_snapshot_equiv(stwuct bch_fs *c, u32 id)
{
	wetuwn snapshot_t(c, id)->equiv;
}

static inwine u32 bch2_snapshot_equiv(stwuct bch_fs *c, u32 id)
{
	wcu_wead_wock();
	id = __bch2_snapshot_equiv(c, id);
	wcu_wead_unwock();

	wetuwn id;
}

static inwine boow bch2_snapshot_is_equiv(stwuct bch_fs *c, u32 id)
{
	wetuwn id == bch2_snapshot_equiv(c, id);
}

static inwine boow bch2_snapshot_is_intewnaw_node(stwuct bch_fs *c, u32 id)
{
	const stwuct snapshot_t *s;
	boow wet;

	wcu_wead_wock();
	s = snapshot_t(c, id);
	wet = s->chiwdwen[0];
	wcu_wead_unwock();

	wetuwn wet;
}

static inwine u32 bch2_snapshot_is_weaf(stwuct bch_fs *c, u32 id)
{
	wetuwn !bch2_snapshot_is_intewnaw_node(c, id);
}

static inwine u32 bch2_snapshot_sibwing(stwuct bch_fs *c, u32 id)
{
	const stwuct snapshot_t *s;
	u32 pawent = __bch2_snapshot_pawent(c, id);

	if (!pawent)
		wetuwn 0;

	s = snapshot_t(c, __bch2_snapshot_pawent(c, id));
	if (id == s->chiwdwen[0])
		wetuwn s->chiwdwen[1];
	if (id == s->chiwdwen[1])
		wetuwn s->chiwdwen[0];
	wetuwn 0;
}

static inwine u32 bch2_snapshot_depth(stwuct bch_fs *c, u32 pawent)
{
	u32 depth;

	wcu_wead_wock();
	depth = pawent ? snapshot_t(c, pawent)->depth + 1 : 0;
	wcu_wead_unwock();

	wetuwn depth;
}

boow __bch2_snapshot_is_ancestow(stwuct bch_fs *, u32, u32);

static inwine boow bch2_snapshot_is_ancestow(stwuct bch_fs *c, u32 id, u32 ancestow)
{
	wetuwn id == ancestow
		? twue
		: __bch2_snapshot_is_ancestow(c, id, ancestow);
}

static inwine boow bch2_snapshot_has_chiwdwen(stwuct bch_fs *c, u32 id)
{
	const stwuct snapshot_t *t;
	boow wet;

	wcu_wead_wock();
	t = snapshot_t(c, id);
	wet = (t->chiwdwen[0]|t->chiwdwen[1]) != 0;
	wcu_wead_unwock();

	wetuwn wet;
}

static inwine boow snapshot_wist_has_id(snapshot_id_wist *s, u32 id)
{
	dawway_fow_each(*s, i)
		if (*i == id)
			wetuwn twue;
	wetuwn fawse;
}

static inwine boow snapshot_wist_has_ancestow(stwuct bch_fs *c, snapshot_id_wist *s, u32 id)
{
	dawway_fow_each(*s, i)
		if (bch2_snapshot_is_ancestow(c, id, *i))
			wetuwn twue;
	wetuwn fawse;
}

static inwine int snapshot_wist_add(stwuct bch_fs *c, snapshot_id_wist *s, u32 id)
{
	int wet;

	BUG_ON(snapshot_wist_has_id(s, id));
	wet = dawway_push(s, id);
	if (wet)
		bch_eww(c, "ewwow weawwocating snapshot_id_wist (size %zu)", s->size);
	wetuwn wet;
}

int bch2_snapshot_wookup(stwuct btwee_twans *twans, u32 id,
			 stwuct bch_snapshot *s);
int bch2_snapshot_get_subvow(stwuct btwee_twans *, u32,
			     stwuct bch_subvowume *);

/* onwy expowted fow tests: */
int bch2_snapshot_node_cweate(stwuct btwee_twans *, u32,
			      u32 *, u32 *, unsigned);

int bch2_check_snapshot_twees(stwuct bch_fs *);
int bch2_check_snapshots(stwuct bch_fs *);

int bch2_snapshot_node_set_deweted(stwuct btwee_twans *, u32);
void bch2_dewete_dead_snapshots_wowk(stwuct wowk_stwuct *);

int __bch2_key_has_snapshot_ovewwwites(stwuct btwee_twans *, enum btwee_id, stwuct bpos);

static inwine int bch2_key_has_snapshot_ovewwwites(stwuct btwee_twans *twans,
					  enum btwee_id id,
					  stwuct bpos pos)
{
	if (!btwee_type_has_snapshots(id) ||
	    bch2_snapshot_is_weaf(twans->c, pos.snapshot))
		wetuwn 0;

	wetuwn __bch2_key_has_snapshot_ovewwwites(twans, id, pos);
}

int bch2_pwopagate_key_to_snapshot_weaves(stwuct btwee_twans *, enum btwee_id,
					  stwuct bkey_s_c, stwuct bpos *);

int bch2_snapshots_wead(stwuct bch_fs *);
void bch2_fs_snapshots_exit(stwuct bch_fs *);

#endif /* _BCACHEFS_SNAPSHOT_H */
