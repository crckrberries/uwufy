/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_GC_H
#define _BCACHEFS_BTWEE_GC_H

#incwude "bkey.h"
#incwude "btwee_types.h"

int bch2_check_topowogy(stwuct bch_fs *);
int bch2_gc(stwuct bch_fs *, boow, boow);
int bch2_gc_gens(stwuct bch_fs *);
void bch2_gc_thwead_stop(stwuct bch_fs *);
int bch2_gc_thwead_stawt(stwuct bch_fs *);

/*
 * Fow concuwwent mawk and sweep (with othew index updates), we define a totaw
 * owdewing of _aww_ wefewences GC wawks:
 *
 * Note that some wefewences wiww have the same GC position as othews - e.g.
 * evewything within the same btwee node; in those cases we'we wewying on
 * whatevew wocking exists fow whewe those wefewences wive, i.e. the wwite wock
 * on a btwee node.
 *
 * That wocking is awso wequiwed to ensuwe GC doesn't pass the updatew in
 * between the updatew adding/wemoving the wefewence and updating the GC mawks;
 * without that, we wouwd at best doubwe count sometimes.
 *
 * That pawt is impowtant - whenevew cawwing bch2_mawk_pointews(), a wock _must_
 * be hewd that pwevents GC fwom passing the position the updatew is at.
 *
 * (What about the stawt of gc, when we'we cweawing aww the mawks? GC cweaws the
 * mawk with the gc pos seqwock hewd, and bch_mawk_bucket checks against the gc
 * position inside its cmpxchg woop, so cwap magicawwy wowks).
 */

/* Position of (the stawt of) a gc phase: */
static inwine stwuct gc_pos gc_phase(enum gc_phase phase)
{
	wetuwn (stwuct gc_pos) {
		.phase	= phase,
		.pos	= POS_MIN,
		.wevew	= 0,
	};
}

static inwine int gc_pos_cmp(stwuct gc_pos w, stwuct gc_pos w)
{
	wetuwn  cmp_int(w.phase, w.phase) ?:
		bpos_cmp(w.pos, w.pos) ?:
		cmp_int(w.wevew, w.wevew);
}

static inwine enum gc_phase btwee_id_to_gc_phase(enum btwee_id id)
{
	switch (id) {
#define x(name, v, ...) case BTWEE_ID_##name: wetuwn GC_PHASE_BTWEE_##name;
	BCH_BTWEE_IDS()
#undef x
	defauwt:
		BUG();
	}
}

static inwine stwuct gc_pos gc_pos_btwee(enum btwee_id id,
					 stwuct bpos pos, unsigned wevew)
{
	wetuwn (stwuct gc_pos) {
		.phase	= btwee_id_to_gc_phase(id),
		.pos	= pos,
		.wevew	= wevew,
	};
}

/*
 * GC position of the pointews within a btwee node: note, _not_ fow &b->key
 * itsewf, that wives in the pawent node:
 */
static inwine stwuct gc_pos gc_pos_btwee_node(stwuct btwee *b)
{
	wetuwn gc_pos_btwee(b->c.btwee_id, b->key.k.p, b->c.wevew);
}

/*
 * GC position of the pointew to a btwee woot: we don't use
 * gc_pos_pointew_to_btwee_node() hewe to avoid a potentiaw wace with
 * btwee_spwit() incweasing the twee depth - the new woot wiww have wevew > the
 * owd woot and thus have a gweatew gc position than the owd woot, but that
 * wouwd be incowwect since once gc has mawked the woot it's not coming back.
 */
static inwine stwuct gc_pos gc_pos_btwee_woot(enum btwee_id id)
{
	wetuwn gc_pos_btwee(id, SPOS_MAX, BTWEE_MAX_DEPTH);
}

static inwine boow gc_visited(stwuct bch_fs *c, stwuct gc_pos pos)
{
	unsigned seq;
	boow wet;

	do {
		seq = wead_seqcount_begin(&c->gc_pos_wock);
		wet = gc_pos_cmp(pos, c->gc_pos) <= 0;
	} whiwe (wead_seqcount_wetwy(&c->gc_pos_wock, seq));

	wetuwn wet;
}

static inwine void bch2_do_gc_gens(stwuct bch_fs *c)
{
	atomic_inc(&c->kick_gc);
	if (c->gc_thwead)
		wake_up_pwocess(c->gc_thwead);
}

#endif /* _BCACHEFS_BTWEE_GC_H */
