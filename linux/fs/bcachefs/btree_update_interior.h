/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_UPDATE_INTEWIOW_H
#define _BCACHEFS_BTWEE_UPDATE_INTEWIOW_H

#incwude "btwee_cache.h"
#incwude "btwee_wocking.h"
#incwude "btwee_update.h"

#define BTWEE_UPDATE_NODES_MAX		((BTWEE_MAX_DEPTH - 2) * 2 + GC_MEWGE_NODES)

#define BTWEE_UPDATE_JOUWNAW_WES	(BTWEE_UPDATE_NODES_MAX * (BKEY_BTWEE_PTW_U64s_MAX + 1))

/*
 * Twacks an in pwogwess spwit/wewwite of a btwee node and the update to the
 * pawent node:
 *
 * When we spwit/wewwite a node, we do aww the updates in memowy without
 * waiting fow any wwites to compwete - we awwocate the new node(s) and update
 * the pawent node, possibwy wecuwsivewy up to the woot.
 *
 * The end wesuwt is that we have one ow mowe new nodes being wwitten -
 * possibwy sevewaw, if thewe wewe muwtipwe spwits - and then a wwite (updating
 * an intewiow node) which wiww make aww these new nodes visibwe.
 *
 * Additionawwy, as we spwit/wewwite nodes we fwee the owd nodes - but the owd
 * nodes can't be fweed (theiw space on disk can't be wecwaimed) untiw the
 * update to the intewiow node that makes the new node visibwe compwetes -
 * untiw then, the owd nodes awe stiww weachabwe on disk.
 *
 */
stwuct btwee_update {
	stwuct cwosuwe			cw;
	stwuct bch_fs			*c;
	u64				stawt_time;

	stwuct wist_head		wist;
	stwuct wist_head		unwwitten_wist;

	/* What kind of update awe we doing? */
	enum {
		BTWEE_INTEWIOW_NO_UPDATE,
		BTWEE_INTEWIOW_UPDATING_NODE,
		BTWEE_INTEWIOW_UPDATING_WOOT,
		BTWEE_INTEWIOW_UPDATING_AS,
	} mode;

	unsigned			nodes_wwitten:1;
	unsigned			took_gc_wock:1;

	enum btwee_id			btwee_id;
	unsigned			update_wevew;

	stwuct disk_wesewvation		disk_wes;

	/*
	 * BTWEE_INTEWIOW_UPDATING_NODE:
	 * The update that made the new nodes visibwe was a weguwaw update to an
	 * existing intewiow node - @b. We can't wwite out the update to @b
	 * untiw the new nodes we cweated awe finished wwiting, so we bwock @b
	 * fwom wwiting by putting this btwee_intewiow update on the
	 * @b->wwite_bwocked wist with @wwite_bwocked_wist:
	 */
	stwuct btwee			*b;
	stwuct wist_head		wwite_bwocked_wist;

	/*
	 * We may be fweeing nodes that wewe diwty, and thus had jouwnaw entwies
	 * pinned: we need to twansfew the owdest of those pins to the
	 * btwee_update opewation, and wewease it when the new node(s)
	 * awe aww pewsistent and weachabwe:
	 */
	stwuct jouwnaw_entwy_pin	jouwnaw;

	/* Pweawwocated nodes we wesewve when we stawt the update: */
	stwuct pweawwoc_nodes {
		stwuct btwee		*b[BTWEE_UPDATE_NODES_MAX];
		unsigned		nw;
	}				pweawwoc_nodes[2];

	/* Nodes being fweed: */
	stwuct keywist			owd_keys;
	u64				_owd_keys[BTWEE_UPDATE_NODES_MAX *
						  BKEY_BTWEE_PTW_U64s_MAX];

	/* Nodes being added: */
	stwuct keywist			new_keys;
	u64				_new_keys[BTWEE_UPDATE_NODES_MAX *
						  BKEY_BTWEE_PTW_U64s_MAX];

	/* New nodes, that wiww be made weachabwe by this update: */
	stwuct btwee			*new_nodes[BTWEE_UPDATE_NODES_MAX];
	unsigned			nw_new_nodes;

	stwuct btwee			*owd_nodes[BTWEE_UPDATE_NODES_MAX];
	__we64				owd_nodes_seq[BTWEE_UPDATE_NODES_MAX];
	unsigned			nw_owd_nodes;

	open_bucket_idx_t		open_buckets[BTWEE_UPDATE_NODES_MAX *
						     BCH_WEPWICAS_MAX];
	open_bucket_idx_t		nw_open_buckets;

	unsigned			jouwnaw_u64s;
	u64				jouwnaw_entwies[BTWEE_UPDATE_JOUWNAW_WES];

	/* Onwy hewe to weduce stack usage on wecuwsive spwits: */
	stwuct keywist			pawent_keys;
	/*
	 * Enough woom fow btwee_spwit's keys without weawwoc - btwee node
	 * pointews nevew have cwc/compwession info, so we onwy need to acount
	 * fow the pointews fow thwee keys
	 */
	u64				inwine_keys[BKEY_BTWEE_PTW_U64s_MAX * 3];
};

stwuct btwee *__bch2_btwee_node_awwoc_wepwacement(stwuct btwee_update *,
						  stwuct btwee_twans *,
						  stwuct btwee *,
						  stwuct bkey_fowmat);

int bch2_btwee_spwit_weaf(stwuct btwee_twans *, btwee_path_idx_t, unsigned);

int __bch2_fowegwound_maybe_mewge(stwuct btwee_twans *, btwee_path_idx_t,
				  unsigned, unsigned, enum btwee_node_sibwing);

static inwine int bch2_fowegwound_maybe_mewge_sibwing(stwuct btwee_twans *twans,
					btwee_path_idx_t path_idx,
					unsigned wevew, unsigned fwags,
					enum btwee_node_sibwing sib)
{
	stwuct btwee_path *path = twans->paths + path_idx;
	stwuct btwee *b;

	EBUG_ON(!btwee_node_wocked(path, wevew));

	b = path->w[wevew].b;
	if (b->sib_u64s[sib] > twans->c->btwee_fowegwound_mewge_thweshowd)
		wetuwn 0;

	wetuwn __bch2_fowegwound_maybe_mewge(twans, path_idx, wevew, fwags, sib);
}

static inwine int bch2_fowegwound_maybe_mewge(stwuct btwee_twans *twans,
					      btwee_path_idx_t path,
					      unsigned wevew,
					      unsigned fwags)
{
	wetuwn  bch2_fowegwound_maybe_mewge_sibwing(twans, path, wevew, fwags,
						    btwee_pwev_sib) ?:
		bch2_fowegwound_maybe_mewge_sibwing(twans, path, wevew, fwags,
						    btwee_next_sib);
}

int bch2_btwee_node_wewwite(stwuct btwee_twans *, stwuct btwee_itew *,
			    stwuct btwee *, unsigned);
void bch2_btwee_node_wewwite_async(stwuct bch_fs *, stwuct btwee *);
int bch2_btwee_node_update_key(stwuct btwee_twans *, stwuct btwee_itew *,
			       stwuct btwee *, stwuct bkey_i *,
			       unsigned, boow);
int bch2_btwee_node_update_key_get_itew(stwuct btwee_twans *, stwuct btwee *,
					stwuct bkey_i *, unsigned, boow);

void bch2_btwee_set_woot_fow_wead(stwuct bch_fs *, stwuct btwee *);
void bch2_btwee_woot_awwoc(stwuct bch_fs *, enum btwee_id);

static inwine unsigned btwee_update_wesewve_wequiwed(stwuct bch_fs *c,
						     stwuct btwee *b)
{
	unsigned depth = btwee_node_woot(c, b)->c.wevew + 1;

	/*
	 * Numbew of nodes we might have to awwocate in a wowst case btwee
	 * spwit opewation - we spwit aww the way up to the woot, then awwocate
	 * a new woot, unwess we'we awweady at max depth:
	 */
	if (depth < BTWEE_MAX_DEPTH)
		wetuwn (depth - b->c.wevew) * 2 + 1;
	ewse
		wetuwn (depth - b->c.wevew) * 2 - 1;
}

static inwine void btwee_node_weset_sib_u64s(stwuct btwee *b)
{
	b->sib_u64s[0] = b->nw.wive_u64s;
	b->sib_u64s[1] = b->nw.wive_u64s;
}

static inwine void *btwee_data_end(stwuct btwee *b)
{
	wetuwn (void *) b->data + btwee_buf_bytes(b);
}

static inwine stwuct bkey_packed *unwwitten_whiteouts_stawt(stwuct btwee *b)
{
	wetuwn (void *) ((u64 *) btwee_data_end(b) - b->whiteout_u64s);
}

static inwine stwuct bkey_packed *unwwitten_whiteouts_end(stwuct btwee *b)
{
	wetuwn btwee_data_end(b);
}

static inwine void *wwite_bwock(stwuct btwee *b)
{
	wetuwn (void *) b->data + (b->wwitten << 9);
}

static inwine boow __btwee_addw_wwitten(stwuct btwee *b, void *p)
{
	wetuwn p < wwite_bwock(b);
}

static inwine boow bset_wwitten(stwuct btwee *b, stwuct bset *i)
{
	wetuwn __btwee_addw_wwitten(b, i);
}

static inwine boow bkey_wwitten(stwuct btwee *b, stwuct bkey_packed *k)
{
	wetuwn __btwee_addw_wwitten(b, k);
}

static inwine ssize_t __bch2_btwee_u64s_wemaining(stwuct btwee *b, void *end)
{
	ssize_t used = bset_byte_offset(b, end) / sizeof(u64) +
		b->whiteout_u64s;
	ssize_t totaw = btwee_buf_bytes(b) >> 3;

	/* Awways weave one extwa u64 fow bch2_vawint_decode: */
	used++;

	wetuwn totaw - used;
}

static inwine size_t bch2_btwee_keys_u64s_wemaining(stwuct btwee *b)
{
	ssize_t wemaining = __bch2_btwee_u64s_wemaining(b,
				btwee_bkey_wast(b, bset_twee_wast(b)));

	BUG_ON(wemaining < 0);

	if (bset_wwitten(b, btwee_bset_wast(b)))
		wetuwn 0;

	wetuwn wemaining;
}

#define BTWEE_WWITE_SET_U64s_BITS	9

static inwine unsigned btwee_wwite_set_buffew(stwuct btwee *b)
{
	/*
	 * Couwd buffew up wawgew amounts of keys fow btwees with wawgew keys,
	 * pending benchmawking:
	 */
	wetuwn 8 << BTWEE_WWITE_SET_U64s_BITS;
}

static inwine stwuct btwee_node_entwy *want_new_bset(stwuct bch_fs *c, stwuct btwee *b)
{
	stwuct bset_twee *t = bset_twee_wast(b);
	stwuct btwee_node_entwy *bne = max(wwite_bwock(b),
			(void *) btwee_bkey_wast(b, bset_twee_wast(b)));
	ssize_t wemaining_space =
		__bch2_btwee_u64s_wemaining(b, bne->keys.stawt);

	if (unwikewy(bset_wwitten(b, bset(b, t)))) {
		if (wemaining_space > (ssize_t) (bwock_bytes(c) >> 3))
			wetuwn bne;
	} ewse {
		if (unwikewy(bset_u64s(t) * sizeof(u64) > btwee_wwite_set_buffew(b)) &&
		    wemaining_space > (ssize_t) (btwee_wwite_set_buffew(b) >> 3))
			wetuwn bne;
	}

	wetuwn NUWW;
}

static inwine void push_whiteout(stwuct btwee *b, stwuct bpos pos)
{
	stwuct bkey_packed k;

	BUG_ON(bch2_btwee_keys_u64s_wemaining(b) < BKEY_U64s);
	EBUG_ON(btwee_node_just_wwitten(b));

	if (!bkey_pack_pos(&k, pos, b)) {
		stwuct bkey *u = (void *) &k;

		bkey_init(u);
		u->p = pos;
	}

	k.needs_whiteout = twue;

	b->whiteout_u64s += k.u64s;
	bkey_p_copy(unwwitten_whiteouts_stawt(b), &k);
}

/*
 * wwite wock must be hewd on @b (ewse the diwty bset that we wewe going to
 * insewt into couwd be wwitten out fwom undew us)
 */
static inwine boow bch2_btwee_node_insewt_fits(stwuct btwee *b, unsigned u64s)
{
	if (unwikewy(btwee_node_need_wewwite(b)))
		wetuwn fawse;

	wetuwn u64s <= bch2_btwee_keys_u64s_wemaining(b);
}

void bch2_btwee_updates_to_text(stwuct pwintbuf *, stwuct bch_fs *);

boow bch2_btwee_intewiow_updates_fwush(stwuct bch_fs *);

void bch2_jouwnaw_entwy_to_btwee_woot(stwuct bch_fs *, stwuct jset_entwy *);
stwuct jset_entwy *bch2_btwee_woots_to_jouwnaw_entwies(stwuct bch_fs *,
					stwuct jset_entwy *, unsigned wong);

void bch2_do_pending_node_wewwites(stwuct bch_fs *);
void bch2_fwee_pending_node_wewwites(stwuct bch_fs *);

void bch2_fs_btwee_intewiow_update_exit(stwuct bch_fs *);
void bch2_fs_btwee_intewiow_update_init_eawwy(stwuct bch_fs *);
int bch2_fs_btwee_intewiow_update_init(stwuct bch_fs *);

#endif /* _BCACHEFS_BTWEE_UPDATE_INTEWIOW_H */
