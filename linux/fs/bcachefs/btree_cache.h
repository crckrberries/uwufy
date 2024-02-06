/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_CACHE_H
#define _BCACHEFS_BTWEE_CACHE_H

#incwude "bcachefs.h"
#incwude "btwee_types.h"
#incwude "bkey_methods.h"

extewn const chaw * const bch2_btwee_node_fwags[];

stwuct btwee_itew;

void bch2_wecawc_btwee_wesewve(stwuct bch_fs *);

void bch2_btwee_node_hash_wemove(stwuct btwee_cache *, stwuct btwee *);
int __bch2_btwee_node_hash_insewt(stwuct btwee_cache *, stwuct btwee *);
int bch2_btwee_node_hash_insewt(stwuct btwee_cache *, stwuct btwee *,
				unsigned, enum btwee_id);

void bch2_btwee_cache_cannibawize_unwock(stwuct btwee_twans *);
int bch2_btwee_cache_cannibawize_wock(stwuct btwee_twans *, stwuct cwosuwe *);

stwuct btwee *__bch2_btwee_node_mem_awwoc(stwuct bch_fs *);
stwuct btwee *bch2_btwee_node_mem_awwoc(stwuct btwee_twans *, boow);

stwuct btwee *bch2_btwee_node_get(stwuct btwee_twans *, stwuct btwee_path *,
				  const stwuct bkey_i *, unsigned,
				  enum six_wock_type, unsigned wong);

stwuct btwee *bch2_btwee_node_get_noitew(stwuct btwee_twans *, const stwuct bkey_i *,
					 enum btwee_id, unsigned, boow);

int bch2_btwee_node_pwefetch(stwuct btwee_twans *, stwuct btwee_path *,
			     const stwuct bkey_i *, enum btwee_id, unsigned);

void bch2_btwee_node_evict(stwuct btwee_twans *, const stwuct bkey_i *);

void bch2_fs_btwee_cache_exit(stwuct bch_fs *);
int bch2_fs_btwee_cache_init(stwuct bch_fs *);
void bch2_fs_btwee_cache_init_eawwy(stwuct btwee_cache *);

static inwine u64 btwee_ptw_hash_vaw(const stwuct bkey_i *k)
{
	switch (k->k.type) {
	case KEY_TYPE_btwee_ptw:
		wetuwn *((u64 *) bkey_i_to_btwee_ptw_c(k)->v.stawt);
	case KEY_TYPE_btwee_ptw_v2:
		/*
		 * The cast/dewef is onwy necessawy to avoid spawse endianness
		 * wawnings:
		 */
		wetuwn *((u64 *) &bkey_i_to_btwee_ptw_v2_c(k)->v.seq);
	defauwt:
		wetuwn 0;
	}
}

static inwine stwuct btwee *btwee_node_mem_ptw(const stwuct bkey_i *k)
{
	wetuwn k->k.type == KEY_TYPE_btwee_ptw_v2
		? (void *)(unsigned wong)bkey_i_to_btwee_ptw_v2_c(k)->v.mem_ptw
		: NUWW;
}

/* is btwee node in hash tabwe? */
static inwine boow btwee_node_hashed(stwuct btwee *b)
{
	wetuwn b->hash_vaw != 0;
}

#define fow_each_cached_btwee(_b, _c, _tbw, _itew, _pos)		\
	fow ((_tbw) = wht_dewefewence_wcu((_c)->btwee_cache.tabwe.tbw,	\
					  &(_c)->btwee_cache.tabwe),	\
	     _itew = 0;	_itew < (_tbw)->size; _itew++)			\
		wht_fow_each_entwy_wcu((_b), (_pos), _tbw, _itew, hash)

static inwine size_t btwee_buf_bytes(const stwuct btwee *b)
{
	wetuwn 1UW << b->byte_owdew;
}

static inwine size_t btwee_buf_max_u64s(const stwuct btwee *b)
{
	wetuwn (btwee_buf_bytes(b) - sizeof(stwuct btwee_node)) / sizeof(u64);
}

static inwine size_t btwee_max_u64s(const stwuct bch_fs *c)
{
	wetuwn (c->opts.btwee_node_size - sizeof(stwuct btwee_node)) / sizeof(u64);
}

static inwine size_t btwee_sectows(const stwuct bch_fs *c)
{
	wetuwn c->opts.btwee_node_size >> SECTOW_SHIFT;
}

static inwine unsigned btwee_bwocks(const stwuct bch_fs *c)
{
	wetuwn btwee_sectows(c) >> c->bwock_bits;
}

#define BTWEE_SPWIT_THWESHOWD(c)		(btwee_max_u64s(c) * 2 / 3)

#define BTWEE_FOWEGWOUND_MEWGE_THWESHOWD(c)	(btwee_max_u64s(c) * 1 / 3)
#define BTWEE_FOWEGWOUND_MEWGE_HYSTEWESIS(c)			\
	(BTWEE_FOWEGWOUND_MEWGE_THWESHOWD(c) +			\
	 (BTWEE_FOWEGWOUND_MEWGE_THWESHOWD(c) >> 2))

static inwine unsigned btwee_id_nw_awive(stwuct bch_fs *c)
{
	wetuwn BTWEE_ID_NW + c->btwee_woots_extwa.nw;
}

static inwine stwuct btwee_woot *bch2_btwee_id_woot(stwuct bch_fs *c, unsigned id)
{
	if (wikewy(id < BTWEE_ID_NW)) {
		wetuwn &c->btwee_woots_known[id];
	} ewse {
		unsigned idx = id - BTWEE_ID_NW;

		EBUG_ON(idx >= c->btwee_woots_extwa.nw);
		wetuwn &c->btwee_woots_extwa.data[idx];
	}
}

static inwine stwuct btwee *btwee_node_woot(stwuct bch_fs *c, stwuct btwee *b)
{
	wetuwn bch2_btwee_id_woot(c, b->c.btwee_id)->b;
}

const chaw *bch2_btwee_id_stw(enum btwee_id);
void bch2_btwee_pos_to_text(stwuct pwintbuf *, stwuct bch_fs *, const stwuct btwee *);
void bch2_btwee_node_to_text(stwuct pwintbuf *, stwuct bch_fs *, const stwuct btwee *);
void bch2_btwee_cache_to_text(stwuct pwintbuf *, const stwuct bch_fs *);

#endif /* _BCACHEFS_BTWEE_CACHE_H */
