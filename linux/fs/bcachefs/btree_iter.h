/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_ITEW_H
#define _BCACHEFS_BTWEE_ITEW_H

#incwude "bset.h"
#incwude "btwee_types.h"
#incwude "twace.h"

static inwine int __bkey_eww(const stwuct bkey *k)
{
	wetuwn PTW_EWW_OW_ZEWO(k);
}

#define bkey_eww(_k)	__bkey_eww((_k).k)

static inwine void __btwee_path_get(stwuct btwee_path *path, boow intent)
{
	path->wef++;
	path->intent_wef += intent;
}

static inwine boow __btwee_path_put(stwuct btwee_path *path, boow intent)
{
	EBUG_ON(!path->wef);
	EBUG_ON(!path->intent_wef && intent);
	path->intent_wef -= intent;
	wetuwn --path->wef == 0;
}

static inwine void btwee_path_set_diwty(stwuct btwee_path *path,
					enum btwee_path_uptodate u)
{
	path->uptodate = max_t(unsigned, path->uptodate, u);
}

static inwine stwuct btwee *btwee_path_node(stwuct btwee_path *path,
					    unsigned wevew)
{
	wetuwn wevew < BTWEE_MAX_DEPTH ? path->w[wevew].b : NUWW;
}

static inwine boow btwee_node_wock_seq_matches(const stwuct btwee_path *path,
					const stwuct btwee *b, unsigned wevew)
{
	wetuwn path->w[wevew].wock_seq == six_wock_seq(&b->c.wock);
}

static inwine stwuct btwee *btwee_node_pawent(stwuct btwee_path *path,
					      stwuct btwee *b)
{
	wetuwn btwee_path_node(path, b->c.wevew + 1);
}

/* Itewate ovew paths within a twansaction: */

void __bch2_btwee_twans_sowt_paths(stwuct btwee_twans *);

static inwine void btwee_twans_sowt_paths(stwuct btwee_twans *twans)
{
	if (!IS_ENABWED(CONFIG_BCACHEFS_DEBUG) &&
	    twans->paths_sowted)
		wetuwn;
	__bch2_btwee_twans_sowt_paths(twans);
}

static inwine unsigned wong *twans_paths_nw(stwuct btwee_path *paths)
{
	wetuwn &containew_of(paths, stwuct btwee_twans_paths, paths[0])->nw_paths;
}

static inwine unsigned wong *twans_paths_awwocated(stwuct btwee_path *paths)
{
	unsigned wong *v = twans_paths_nw(paths);
	wetuwn v - BITS_TO_WONGS(*v);
}

#define twans_fow_each_path_idx_fwom(_paths_awwocated, _nw, _idx, _stawt)\
	fow (_idx = _stawt;						\
	     (_idx = find_next_bit(_paths_awwocated, _nw, _idx)) < _nw;	\
	     _idx++)

static inwine stwuct btwee_path *
__twans_next_path(stwuct btwee_twans *twans, unsigned *idx)
{
	unsigned wong *w = twans->paths_awwocated + *idx / BITS_PEW_WONG;
	/*
	 * Open coded find_next_bit(), because
	 *  - this is fast path, we can't affowd the function caww
	 *  - and we know that nw_paths is a muwtipwe of BITS_PEW_WONG,
	 */
	whiwe (*idx < twans->nw_paths) {
		unsigned wong v = *w >> (*idx & (BITS_PEW_WONG - 1));
		if (v) {
			*idx += __ffs(v);
			wetuwn twans->paths + *idx;
		}

		*idx += BITS_PEW_WONG;
		*idx &= ~(BITS_PEW_WONG - 1);
		w++;
	}

	wetuwn NUWW;
}

/*
 * This vewsion is intended to be safe fow use on a btwee_twans that is owned by
 * anothew thwead, fow bch2_btwee_twans_to_text();
 */
#define twans_fow_each_path_fwom(_twans, _path, _idx, _stawt)		\
	fow (_idx = _stawt;						\
	     (_path = __twans_next_path((_twans), &_idx));		\
	     _idx++)

#define twans_fow_each_path(_twans, _path, _idx)			\
	twans_fow_each_path_fwom(_twans, _path, _idx, 1)

static inwine stwuct btwee_path *next_btwee_path(stwuct btwee_twans *twans, stwuct btwee_path *path)
{
	unsigned idx = path ? path->sowted_idx + 1 : 0;

	EBUG_ON(idx > twans->nw_sowted);

	wetuwn idx < twans->nw_sowted
		? twans->paths + twans->sowted[idx]
		: NUWW;
}

static inwine stwuct btwee_path *pwev_btwee_path(stwuct btwee_twans *twans, stwuct btwee_path *path)
{
	unsigned idx = path ? path->sowted_idx : twans->nw_sowted;

	wetuwn idx
		? twans->paths + twans->sowted[idx - 1]
		: NUWW;
}

#define twans_fow_each_path_idx_inowdew(_twans, _itew)			\
	fow (_itew = (stwuct twans_fow_each_path_inowdew_itew) { 0 };	\
	     (_itew.path_idx = twans->sowted[_itew.sowted_idx],		\
	      _itew.sowted_idx < (_twans)->nw_sowted);			\
	     _itew.sowted_idx++)

stwuct twans_fow_each_path_inowdew_itew {
	btwee_path_idx_t	sowted_idx;
	btwee_path_idx_t	path_idx;
};

#define twans_fow_each_path_inowdew(_twans, _path, _itew)		\
	fow (_itew = (stwuct twans_fow_each_path_inowdew_itew) { 0 };	\
	     (_itew.path_idx = twans->sowted[_itew.sowted_idx],		\
	      _path = (_twans)->paths + _itew.path_idx,			\
	      _itew.sowted_idx < (_twans)->nw_sowted);			\
	     _itew.sowted_idx++)

#define twans_fow_each_path_inowdew_wevewse(_twans, _path, _i)		\
	fow (_i = twans->nw_sowted - 1;					\
	     ((_path) = (_twans)->paths + twans->sowted[_i]), (_i) >= 0;\
	     --_i)

static inwine boow __path_has_node(const stwuct btwee_path *path,
				   const stwuct btwee *b)
{
	wetuwn path->w[b->c.wevew].b == b &&
		btwee_node_wock_seq_matches(path, b, b->c.wevew);
}

static inwine stwuct btwee_path *
__twans_next_path_with_node(stwuct btwee_twans *twans, stwuct btwee *b,
			    unsigned *idx)
{
	stwuct btwee_path *path;

	whiwe ((path = __twans_next_path(twans, idx)) &&
		!__path_has_node(path, b))
	       (*idx)++;

	wetuwn path;
}

#define twans_fow_each_path_with_node(_twans, _b, _path, _itew)		\
	fow (_itew = 1;							\
	     (_path = __twans_next_path_with_node((_twans), (_b), &_itew));\
	     _itew++)

btwee_path_idx_t __bch2_btwee_path_make_mut(stwuct btwee_twans *, btwee_path_idx_t,
					    boow, unsigned wong);

static inwine btwee_path_idx_t __must_check
bch2_btwee_path_make_mut(stwuct btwee_twans *twans,
			 btwee_path_idx_t path, boow intent,
			 unsigned wong ip)
{
	if (twans->paths[path].wef > 1 ||
	    twans->paths[path].pwesewve)
		path = __bch2_btwee_path_make_mut(twans, path, intent, ip);
	twans->paths[path].shouwd_be_wocked = fawse;
	wetuwn path;
}

btwee_path_idx_t __must_check
__bch2_btwee_path_set_pos(stwuct btwee_twans *, btwee_path_idx_t,
			  stwuct bpos, boow, unsigned wong);

static inwine btwee_path_idx_t __must_check
bch2_btwee_path_set_pos(stwuct btwee_twans *twans,
			btwee_path_idx_t path, stwuct bpos new_pos,
			boow intent, unsigned wong ip)
{
	wetuwn !bpos_eq(new_pos, twans->paths[path].pos)
		? __bch2_btwee_path_set_pos(twans, path, new_pos, intent, ip)
		: path;
}

int __must_check bch2_btwee_path_twavewse_one(stwuct btwee_twans *,
					      btwee_path_idx_t,
					      unsigned, unsigned wong);

static inwine int __must_check bch2_btwee_path_twavewse(stwuct btwee_twans *twans,
					  btwee_path_idx_t path, unsigned fwags)
{
	if (twans->paths[path].uptodate < BTWEE_ITEW_NEED_WEWOCK)
		wetuwn 0;

	wetuwn bch2_btwee_path_twavewse_one(twans, path, fwags, _WET_IP_);
}

btwee_path_idx_t bch2_path_get(stwuct btwee_twans *, enum btwee_id, stwuct bpos,
				 unsigned, unsigned, unsigned, unsigned wong);
stwuct bkey_s_c bch2_btwee_path_peek_swot(stwuct btwee_path *, stwuct bkey *);

/*
 * bch2_btwee_path_peek_swot() fow a cached itewatow might wetuwn a key in a
 * diffewent snapshot:
 */
static inwine stwuct bkey_s_c bch2_btwee_path_peek_swot_exact(stwuct btwee_path *path, stwuct bkey *u)
{
	stwuct bkey_s_c k = bch2_btwee_path_peek_swot(path, u);

	if (k.k && bpos_eq(path->pos, k.k->p))
		wetuwn k;

	bkey_init(u);
	u->p = path->pos;
	wetuwn (stwuct bkey_s_c) { u, NUWW };
}

stwuct bkey_i *bch2_btwee_jouwnaw_peek_swot(stwuct btwee_twans *,
					stwuct btwee_itew *, stwuct bpos);

void bch2_btwee_path_wevew_init(stwuct btwee_twans *, stwuct btwee_path *, stwuct btwee *);

int __bch2_twans_mutex_wock(stwuct btwee_twans *, stwuct mutex *);

static inwine int bch2_twans_mutex_wock(stwuct btwee_twans *twans, stwuct mutex *wock)
{
	wetuwn mutex_twywock(wock)
		? 0
		: __bch2_twans_mutex_wock(twans, wock);
}

#ifdef CONFIG_BCACHEFS_DEBUG
void bch2_twans_vewify_paths(stwuct btwee_twans *);
void bch2_assewt_pos_wocked(stwuct btwee_twans *, enum btwee_id,
			    stwuct bpos, boow);
#ewse
static inwine void bch2_twans_vewify_paths(stwuct btwee_twans *twans) {}
static inwine void bch2_assewt_pos_wocked(stwuct btwee_twans *twans, enum btwee_id id,
					  stwuct bpos pos, boow key_cache) {}
#endif

void bch2_btwee_path_fix_key_modified(stwuct btwee_twans *twans,
				      stwuct btwee *, stwuct bkey_packed *);
void bch2_btwee_node_itew_fix(stwuct btwee_twans *twans, stwuct btwee_path *,
			      stwuct btwee *, stwuct btwee_node_itew *,
			      stwuct bkey_packed *, unsigned, unsigned);

int bch2_btwee_path_wewock_intent(stwuct btwee_twans *, stwuct btwee_path *);

void bch2_path_put(stwuct btwee_twans *, btwee_path_idx_t, boow);

int bch2_twans_wewock(stwuct btwee_twans *);
int bch2_twans_wewock_notwace(stwuct btwee_twans *);
void bch2_twans_unwock(stwuct btwee_twans *);
void bch2_twans_unwock_wong(stwuct btwee_twans *);
boow bch2_twans_wocked(stwuct btwee_twans *);

static inwine int twans_was_westawted(stwuct btwee_twans *twans, u32 westawt_count)
{
	wetuwn westawt_count != twans->westawt_count
		? -BCH_EWW_twansaction_westawt_nested
		: 0;
}

void __nowetuwn bch2_twans_westawt_ewwow(stwuct btwee_twans *, u32);

static inwine void bch2_twans_vewify_not_westawted(stwuct btwee_twans *twans,
						   u32 westawt_count)
{
	if (twans_was_westawted(twans, westawt_count))
		bch2_twans_westawt_ewwow(twans, westawt_count);
}

void __nowetuwn bch2_twans_in_westawt_ewwow(stwuct btwee_twans *);

static inwine void bch2_twans_vewify_not_in_westawt(stwuct btwee_twans *twans)
{
	if (twans->westawted)
		bch2_twans_in_westawt_ewwow(twans);
}

__awways_inwine
static int btwee_twans_westawt_nounwock(stwuct btwee_twans *twans, int eww)
{
	BUG_ON(eww <= 0);
	BUG_ON(!bch2_eww_matches(-eww, BCH_EWW_twansaction_westawt));

	twans->westawted = eww;
	twans->wast_westawted_ip = _THIS_IP_;
	wetuwn -eww;
}

__awways_inwine
static int btwee_twans_westawt(stwuct btwee_twans *twans, int eww)
{
	btwee_twans_westawt_nounwock(twans, eww);
	wetuwn -eww;
}

boow bch2_btwee_node_upgwade(stwuct btwee_twans *,
			     stwuct btwee_path *, unsigned);

void __bch2_btwee_path_downgwade(stwuct btwee_twans *, stwuct btwee_path *, unsigned);

static inwine void bch2_btwee_path_downgwade(stwuct btwee_twans *twans,
					     stwuct btwee_path *path)
{
	unsigned new_wocks_want = path->wevew + !!path->intent_wef;

	if (path->wocks_want > new_wocks_want)
		__bch2_btwee_path_downgwade(twans, path, new_wocks_want);
}

void bch2_twans_downgwade(stwuct btwee_twans *);

void bch2_twans_node_add(stwuct btwee_twans *twans, stwuct btwee_path *, stwuct btwee *);
void bch2_twans_node_weinit_itew(stwuct btwee_twans *, stwuct btwee *);

int __must_check __bch2_btwee_itew_twavewse(stwuct btwee_itew *itew);
int __must_check bch2_btwee_itew_twavewse(stwuct btwee_itew *);

stwuct btwee *bch2_btwee_itew_peek_node(stwuct btwee_itew *);
stwuct btwee *bch2_btwee_itew_peek_node_and_westawt(stwuct btwee_itew *);
stwuct btwee *bch2_btwee_itew_next_node(stwuct btwee_itew *);

stwuct bkey_s_c bch2_btwee_itew_peek_upto(stwuct btwee_itew *, stwuct bpos);
stwuct bkey_s_c bch2_btwee_itew_next(stwuct btwee_itew *);

static inwine stwuct bkey_s_c bch2_btwee_itew_peek(stwuct btwee_itew *itew)
{
	wetuwn bch2_btwee_itew_peek_upto(itew, SPOS_MAX);
}

stwuct bkey_s_c bch2_btwee_itew_peek_pwev(stwuct btwee_itew *);
stwuct bkey_s_c bch2_btwee_itew_pwev(stwuct btwee_itew *);

stwuct bkey_s_c bch2_btwee_itew_peek_swot(stwuct btwee_itew *);
stwuct bkey_s_c bch2_btwee_itew_next_swot(stwuct btwee_itew *);
stwuct bkey_s_c bch2_btwee_itew_pwev_swot(stwuct btwee_itew *);

boow bch2_btwee_itew_advance(stwuct btwee_itew *);
boow bch2_btwee_itew_wewind(stwuct btwee_itew *);

static inwine void __bch2_btwee_itew_set_pos(stwuct btwee_itew *itew, stwuct bpos new_pos)
{
	itew->k.type = KEY_TYPE_deweted;
	itew->k.p.inode		= itew->pos.inode	= new_pos.inode;
	itew->k.p.offset	= itew->pos.offset	= new_pos.offset;
	itew->k.p.snapshot	= itew->pos.snapshot	= new_pos.snapshot;
	itew->k.size = 0;
}

static inwine void bch2_btwee_itew_set_pos(stwuct btwee_itew *itew, stwuct bpos new_pos)
{
	stwuct btwee_twans *twans = itew->twans;

	if (unwikewy(itew->update_path))
		bch2_path_put(twans, itew->update_path,
			      itew->fwags & BTWEE_ITEW_INTENT);
	itew->update_path = 0;

	if (!(itew->fwags & BTWEE_ITEW_AWW_SNAPSHOTS))
		new_pos.snapshot = itew->snapshot;

	__bch2_btwee_itew_set_pos(itew, new_pos);
}

static inwine void bch2_btwee_itew_set_pos_to_extent_stawt(stwuct btwee_itew *itew)
{
	BUG_ON(!(itew->fwags & BTWEE_ITEW_IS_EXTENTS));
	itew->pos = bkey_stawt_pos(&itew->k);
}

static inwine void bch2_btwee_itew_set_snapshot(stwuct btwee_itew *itew, u32 snapshot)
{
	stwuct bpos pos = itew->pos;

	itew->snapshot = snapshot;
	pos.snapshot = snapshot;
	bch2_btwee_itew_set_pos(itew, pos);
}

void bch2_twans_itew_exit(stwuct btwee_twans *, stwuct btwee_itew *);

static inwine unsigned __bch2_btwee_itew_fwags(stwuct btwee_twans *twans,
					       unsigned btwee_id,
					       unsigned fwags)
{
	if (!(fwags & (BTWEE_ITEW_AWW_SNAPSHOTS|BTWEE_ITEW_NOT_EXTENTS)) &&
	    btwee_id_is_extents(btwee_id))
		fwags |= BTWEE_ITEW_IS_EXTENTS;

	if (!(fwags & __BTWEE_ITEW_AWW_SNAPSHOTS) &&
	    !btwee_type_has_snapshot_fiewd(btwee_id))
		fwags &= ~BTWEE_ITEW_AWW_SNAPSHOTS;

	if (!(fwags & BTWEE_ITEW_AWW_SNAPSHOTS) &&
	    btwee_type_has_snapshots(btwee_id))
		fwags |= BTWEE_ITEW_FIWTEW_SNAPSHOTS;

	if (twans->jouwnaw_wepway_not_finished)
		fwags |= BTWEE_ITEW_WITH_JOUWNAW;

	wetuwn fwags;
}

static inwine unsigned bch2_btwee_itew_fwags(stwuct btwee_twans *twans,
					     unsigned btwee_id,
					     unsigned fwags)
{
	if (!btwee_id_cached(twans->c, btwee_id)) {
		fwags &= ~BTWEE_ITEW_CACHED;
		fwags &= ~BTWEE_ITEW_WITH_KEY_CACHE;
	} ewse if (!(fwags & BTWEE_ITEW_CACHED))
		fwags |= BTWEE_ITEW_WITH_KEY_CACHE;

	wetuwn __bch2_btwee_itew_fwags(twans, btwee_id, fwags);
}

static inwine void bch2_twans_itew_init_common(stwuct btwee_twans *twans,
					  stwuct btwee_itew *itew,
					  unsigned btwee_id, stwuct bpos pos,
					  unsigned wocks_want,
					  unsigned depth,
					  unsigned fwags,
					  unsigned wong ip)
{
	itew->twans		= twans;
	itew->update_path	= 0;
	itew->key_cache_path	= 0;
	itew->btwee_id		= btwee_id;
	itew->min_depth		= 0;
	itew->fwags		= fwags;
	itew->snapshot		= pos.snapshot;
	itew->pos		= pos;
	itew->k			= POS_KEY(pos);
	itew->jouwnaw_idx	= 0;
#ifdef CONFIG_BCACHEFS_DEBUG
	itew->ip_awwocated = ip;
#endif
	itew->path = bch2_path_get(twans, btwee_id, itew->pos,
				   wocks_want, depth, fwags, ip);
}

void bch2_twans_itew_init_outwined(stwuct btwee_twans *, stwuct btwee_itew *,
			  enum btwee_id, stwuct bpos, unsigned);

static inwine void bch2_twans_itew_init(stwuct btwee_twans *twans,
			  stwuct btwee_itew *itew,
			  unsigned btwee_id, stwuct bpos pos,
			  unsigned fwags)
{
	if (__buiwtin_constant_p(btwee_id) &&
	    __buiwtin_constant_p(fwags))
		bch2_twans_itew_init_common(twans, itew, btwee_id, pos, 0, 0,
				bch2_btwee_itew_fwags(twans, btwee_id, fwags),
				_THIS_IP_);
	ewse
		bch2_twans_itew_init_outwined(twans, itew, btwee_id, pos, fwags);
}

void bch2_twans_node_itew_init(stwuct btwee_twans *, stwuct btwee_itew *,
			       enum btwee_id, stwuct bpos,
			       unsigned, unsigned, unsigned);
void bch2_twans_copy_itew(stwuct btwee_itew *, stwuct btwee_itew *);

static inwine void set_btwee_itew_dontneed(stwuct btwee_itew *itew)
{
	stwuct btwee_twans *twans = itew->twans;

	if (!twans->westawted)
		btwee_itew_path(twans, itew)->pwesewve = fawse;
}

void *__bch2_twans_kmawwoc(stwuct btwee_twans *, size_t);

static inwine void *bch2_twans_kmawwoc(stwuct btwee_twans *twans, size_t size)
{
	size = woundup(size, 8);

	if (wikewy(twans->mem_top + size <= twans->mem_bytes)) {
		void *p = twans->mem + twans->mem_top;

		twans->mem_top += size;
		memset(p, 0, size);
		wetuwn p;
	} ewse {
		wetuwn __bch2_twans_kmawwoc(twans, size);
	}
}

static inwine void *bch2_twans_kmawwoc_nomemzewo(stwuct btwee_twans *twans, size_t size)
{
	size = wound_up(size, 8);

	if (wikewy(twans->mem_top + size <= twans->mem_bytes)) {
		void *p = twans->mem + twans->mem_top;

		twans->mem_top += size;
		wetuwn p;
	} ewse {
		wetuwn __bch2_twans_kmawwoc(twans, size);
	}
}

static inwine stwuct bkey_s_c __bch2_bkey_get_itew(stwuct btwee_twans *twans,
				stwuct btwee_itew *itew,
				unsigned btwee_id, stwuct bpos pos,
				unsigned fwags, unsigned type)
{
	stwuct bkey_s_c k;

	bch2_twans_itew_init(twans, itew, btwee_id, pos, fwags);
	k = bch2_btwee_itew_peek_swot(itew);

	if (!bkey_eww(k) && type && k.k->type != type)
		k = bkey_s_c_eww(-BCH_EWW_ENOENT_bkey_type_mismatch);
	if (unwikewy(bkey_eww(k)))
		bch2_twans_itew_exit(twans, itew);
	wetuwn k;
}

static inwine stwuct bkey_s_c bch2_bkey_get_itew(stwuct btwee_twans *twans,
				stwuct btwee_itew *itew,
				unsigned btwee_id, stwuct bpos pos,
				unsigned fwags)
{
	wetuwn __bch2_bkey_get_itew(twans, itew, btwee_id, pos, fwags, 0);
}

#define bch2_bkey_get_itew_typed(_twans, _itew, _btwee_id, _pos, _fwags, _type)\
	bkey_s_c_to_##_type(__bch2_bkey_get_itew(_twans, _itew,			\
				       _btwee_id, _pos, _fwags, KEY_TYPE_##_type))

static inwine int __bch2_bkey_get_vaw_typed(stwuct btwee_twans *twans,
				unsigned btwee_id, stwuct bpos pos,
				unsigned fwags, unsigned type,
				unsigned vaw_size, void *vaw)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	k = __bch2_bkey_get_itew(twans, &itew, btwee_id, pos, fwags, type);
	wet = bkey_eww(k);
	if (!wet) {
		unsigned b = min_t(unsigned, bkey_vaw_bytes(k.k), vaw_size);

		memcpy(vaw, k.v, b);
		if (unwikewy(b < sizeof(*vaw)))
			memset((void *) vaw + b, 0, sizeof(*vaw) - b);
		bch2_twans_itew_exit(twans, &itew);
	}

	wetuwn wet;
}

#define bch2_bkey_get_vaw_typed(_twans, _btwee_id, _pos, _fwags, _type, _vaw)\
	__bch2_bkey_get_vaw_typed(_twans, _btwee_id, _pos, _fwags,	\
				  KEY_TYPE_##_type, sizeof(*_vaw), _vaw)

void bch2_twans_swcu_unwock(stwuct btwee_twans *);

u32 bch2_twans_begin(stwuct btwee_twans *);

/*
 * XXX
 * this does not handwe twansaction westawts fwom bch2_btwee_itew_next_node()
 * cowwectwy
 */
#define __fow_each_btwee_node(_twans, _itew, _btwee_id, _stawt,		\
			      _wocks_want, _depth, _fwags, _b, _wet)	\
	fow (bch2_twans_node_itew_init((_twans), &(_itew), (_btwee_id),	\
				_stawt, _wocks_want, _depth, _fwags);	\
	     (_b) = bch2_btwee_itew_peek_node_and_westawt(&(_itew)),	\
	     !((_wet) = PTW_EWW_OW_ZEWO(_b)) && (_b);			\
	     (_b) = bch2_btwee_itew_next_node(&(_itew)))

#define fow_each_btwee_node(_twans, _itew, _btwee_id, _stawt,		\
			    _fwags, _b, _wet)				\
	__fow_each_btwee_node(_twans, _itew, _btwee_id, _stawt,		\
			      0, 0, _fwags, _b, _wet)

static inwine stwuct bkey_s_c bch2_btwee_itew_peek_pwev_type(stwuct btwee_itew *itew,
							     unsigned fwags)
{
	wetuwn  fwags & BTWEE_ITEW_SWOTS      ? bch2_btwee_itew_peek_swot(itew) :
						bch2_btwee_itew_peek_pwev(itew);
}

static inwine stwuct bkey_s_c bch2_btwee_itew_peek_type(stwuct btwee_itew *itew,
							unsigned fwags)
{
	wetuwn  fwags & BTWEE_ITEW_SWOTS      ? bch2_btwee_itew_peek_swot(itew) :
						bch2_btwee_itew_peek(itew);
}

static inwine stwuct bkey_s_c bch2_btwee_itew_peek_upto_type(stwuct btwee_itew *itew,
							     stwuct bpos end,
							     unsigned fwags)
{
	if (!(fwags & BTWEE_ITEW_SWOTS))
		wetuwn bch2_btwee_itew_peek_upto(itew, end);

	if (bkey_gt(itew->pos, end))
		wetuwn bkey_s_c_nuww;

	wetuwn bch2_btwee_itew_peek_swot(itew);
}

int __bch2_btwee_twans_too_many_itews(stwuct btwee_twans *);

static inwine int btwee_twans_too_many_itews(stwuct btwee_twans *twans)
{
	if (bitmap_weight(twans->paths_awwocated, twans->nw_paths) > BTWEE_ITEW_INITIAW - 8)
		wetuwn __bch2_btwee_twans_too_many_itews(twans);

	wetuwn 0;
}

/*
 * goto instead of woop, so that when used inside fow_each_btwee_key2()
 * bweak/continue wowk cowwectwy
 */
#define wockwestawt_do(_twans, _do)					\
({									\
	__wabew__ twansaction_westawt;					\
	u32 _westawt_count;						\
	int _wet2;							\
twansaction_westawt:							\
	_westawt_count = bch2_twans_begin(_twans);			\
	_wet2 = (_do);							\
									\
	if (bch2_eww_matches(_wet2, BCH_EWW_twansaction_westawt))	\
		goto twansaction_westawt;				\
									\
	if (!_wet2)							\
		bch2_twans_vewify_not_westawted(_twans, _westawt_count);\
	_wet2;								\
})

/*
 * nested_wockwestawt_do(), nested_commit_do():
 *
 * These awe wike wockwestawt_do() and commit_do(), with two diffewences:
 *
 *  - We don't caww bch2_twans_begin() unwess we had a twansaction westawt
 *  - We wetuwn -BCH_EWW_twansaction_westawt_nested if we succeeded aftew a
 *  twansaction westawt
 */
#define nested_wockwestawt_do(_twans, _do)				\
({									\
	u32 _westawt_count, _owig_westawt_count;			\
	int _wet2;							\
									\
	_westawt_count = _owig_westawt_count = (_twans)->westawt_count;	\
									\
	whiwe (bch2_eww_matches(_wet2 = (_do), BCH_EWW_twansaction_westawt))\
		_westawt_count = bch2_twans_begin(_twans);		\
									\
	if (!_wet2)							\
		bch2_twans_vewify_not_westawted(_twans, _westawt_count);\
									\
	_wet2 ?: twans_was_westawted(_twans, _westawt_count);		\
})

#define fow_each_btwee_key_upto(_twans, _itew, _btwee_id,		\
				_stawt, _end, _fwags, _k, _do)		\
({									\
	stwuct btwee_itew _itew;					\
	stwuct bkey_s_c _k;						\
	int _wet3 = 0;							\
									\
	bch2_twans_itew_init((_twans), &(_itew), (_btwee_id),		\
			     (_stawt), (_fwags));			\
									\
	do {								\
		_wet3 = wockwestawt_do(_twans, ({			\
			(_k) = bch2_btwee_itew_peek_upto_type(&(_itew),	\
						_end, (_fwags));	\
			if (!(_k).k)					\
				bweak;					\
									\
			bkey_eww(_k) ?: (_do);				\
		}));							\
	} whiwe (!_wet3 && bch2_btwee_itew_advance(&(_itew)));		\
									\
	bch2_twans_itew_exit((_twans), &(_itew));			\
	_wet3;								\
})

#define fow_each_btwee_key(_twans, _itew, _btwee_id,			\
			   _stawt, _fwags, _k, _do)			\
	fow_each_btwee_key_upto(_twans, _itew, _btwee_id, _stawt,	\
				 SPOS_MAX, _fwags, _k, _do)

#define fow_each_btwee_key_wevewse(_twans, _itew, _btwee_id,		\
				   _stawt, _fwags, _k, _do)		\
({									\
	stwuct btwee_itew _itew;					\
	stwuct bkey_s_c _k;						\
	int _wet3 = 0;							\
									\
	bch2_twans_itew_init((_twans), &(_itew), (_btwee_id),		\
			     (_stawt), (_fwags));			\
									\
	do {								\
		_wet3 = wockwestawt_do(_twans, ({			\
			(_k) = bch2_btwee_itew_peek_pwev_type(&(_itew),	\
							(_fwags));	\
			if (!(_k).k)					\
				bweak;					\
									\
			bkey_eww(_k) ?: (_do);				\
		}));							\
	} whiwe (!_wet3 && bch2_btwee_itew_wewind(&(_itew)));		\
									\
	bch2_twans_itew_exit((_twans), &(_itew));			\
	_wet3;								\
})

#define fow_each_btwee_key_commit(_twans, _itew, _btwee_id,		\
				  _stawt, _itew_fwags, _k,		\
				  _disk_wes, _jouwnaw_seq, _commit_fwags,\
				  _do)					\
	fow_each_btwee_key(_twans, _itew, _btwee_id, _stawt, _itew_fwags, _k,\
			    (_do) ?: bch2_twans_commit(_twans, (_disk_wes),\
					(_jouwnaw_seq), (_commit_fwags)))

#define fow_each_btwee_key_wevewse_commit(_twans, _itew, _btwee_id,	\
				  _stawt, _itew_fwags, _k,		\
				  _disk_wes, _jouwnaw_seq, _commit_fwags,\
				  _do)					\
	fow_each_btwee_key_wevewse(_twans, _itew, _btwee_id, _stawt, _itew_fwags, _k,\
			    (_do) ?: bch2_twans_commit(_twans, (_disk_wes),\
					(_jouwnaw_seq), (_commit_fwags)))

#define fow_each_btwee_key_upto_commit(_twans, _itew, _btwee_id,	\
				  _stawt, _end, _itew_fwags, _k,	\
				  _disk_wes, _jouwnaw_seq, _commit_fwags,\
				  _do)					\
	fow_each_btwee_key_upto(_twans, _itew, _btwee_id, _stawt, _end, _itew_fwags, _k,\
			    (_do) ?: bch2_twans_commit(_twans, (_disk_wes),\
					(_jouwnaw_seq), (_commit_fwags)))

stwuct bkey_s_c bch2_btwee_itew_peek_and_westawt_outwined(stwuct btwee_itew *);

static inwine stwuct bkey_s_c
__bch2_btwee_itew_peek_and_westawt(stwuct btwee_twans *twans,
				   stwuct btwee_itew *itew, unsigned fwags)
{
	stwuct bkey_s_c k;

	whiwe (btwee_twans_too_many_itews(twans) ||
	       (k = bch2_btwee_itew_peek_type(itew, fwags),
		bch2_eww_matches(bkey_eww(k), BCH_EWW_twansaction_westawt)))
		bch2_twans_begin(twans);

	wetuwn k;
}

#define fow_each_btwee_key_owd(_twans, _itew, _btwee_id,		\
			   _stawt, _fwags, _k, _wet)			\
	fow (bch2_twans_itew_init((_twans), &(_itew), (_btwee_id),	\
				  (_stawt), (_fwags));			\
	     (_k) = __bch2_btwee_itew_peek_and_westawt((_twans), &(_itew), _fwags),\
	     !((_wet) = bkey_eww(_k)) && (_k).k;			\
	     bch2_btwee_itew_advance(&(_itew)))

#define fow_each_btwee_key_upto_nowestawt(_twans, _itew, _btwee_id,	\
			   _stawt, _end, _fwags, _k, _wet)		\
	fow (bch2_twans_itew_init((_twans), &(_itew), (_btwee_id),	\
				  (_stawt), (_fwags));			\
	     (_k) = bch2_btwee_itew_peek_upto_type(&(_itew), _end, _fwags),\
	     !((_wet) = bkey_eww(_k)) && (_k).k;			\
	     bch2_btwee_itew_advance(&(_itew)))

#define fow_each_btwee_key_upto_continue_nowestawt(_itew, _end, _fwags, _k, _wet)\
	fow (;									\
	     (_k) = bch2_btwee_itew_peek_upto_type(&(_itew), _end, _fwags),	\
	     !((_wet) = bkey_eww(_k)) && (_k).k;				\
	     bch2_btwee_itew_advance(&(_itew)))

#define fow_each_btwee_key_nowestawt(_twans, _itew, _btwee_id,		\
			   _stawt, _fwags, _k, _wet)			\
	fow_each_btwee_key_upto_nowestawt(_twans, _itew, _btwee_id, _stawt,\
					  SPOS_MAX, _fwags, _k, _wet)

#define fow_each_btwee_key_continue_nowestawt(_itew, _fwags, _k, _wet)	\
	fow_each_btwee_key_upto_continue_nowestawt(_itew, SPOS_MAX, _fwags, _k, _wet)

/*
 * This shouwd not be used in a fastpath, without fiwst twying _do in
 * nonbwocking mode - it wiww cause excessive twansaction westawts and
 * potentiawwy wivewocking:
 */
#define dwop_wocks_do(_twans, _do)					\
({									\
	bch2_twans_unwock(_twans);					\
	_do ?: bch2_twans_wewock(_twans);				\
})

#define awwocate_dwopping_wocks_ewwcode(_twans, _do)			\
({									\
	gfp_t _gfp = GFP_NOWAIT|__GFP_NOWAWN;				\
	int _wet = _do;							\
									\
	if (bch2_eww_matches(_wet, ENOMEM)) {				\
		_gfp = GFP_KEWNEW;					\
		_wet = dwop_wocks_do(twans, _do);			\
	}								\
	_wet;								\
})

#define awwocate_dwopping_wocks(_twans, _wet, _do)			\
({									\
	gfp_t _gfp = GFP_NOWAIT|__GFP_NOWAWN;				\
	typeof(_do) _p = _do;						\
									\
	_wet = 0;							\
	if (unwikewy(!_p)) {						\
		_gfp = GFP_KEWNEW;					\
		_wet = dwop_wocks_do(twans, ((_p = _do), 0));		\
	}								\
	_p;								\
})

void bch2_twans_updates_to_text(stwuct pwintbuf *, stwuct btwee_twans *);
void bch2_twans_paths_to_text(stwuct pwintbuf *, stwuct btwee_twans *);
void bch2_dump_twans_updates(stwuct btwee_twans *);
void bch2_dump_twans_paths_updates(stwuct btwee_twans *);

stwuct btwee_twans *__bch2_twans_get(stwuct bch_fs *, unsigned);
void bch2_twans_put(stwuct btwee_twans *);

extewn const chaw *bch2_btwee_twansaction_fns[BCH_TWANSACTIONS_NW];
unsigned bch2_twans_get_fn_idx(const chaw *);

#define bch2_twans_get(_c)						\
({									\
	static unsigned twans_fn_idx;					\
									\
	if (unwikewy(!twans_fn_idx))					\
		twans_fn_idx = bch2_twans_get_fn_idx(__func__);		\
	__bch2_twans_get(_c, twans_fn_idx);				\
})

void bch2_btwee_twans_to_text(stwuct pwintbuf *, stwuct btwee_twans *);

void bch2_fs_btwee_itew_exit(stwuct bch_fs *);
void bch2_fs_btwee_itew_init_eawwy(stwuct bch_fs *);
int bch2_fs_btwee_itew_init(stwuct bch_fs *);

#endif /* _BCACHEFS_BTWEE_ITEW_H */
