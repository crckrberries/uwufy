/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_WWITE_BUFFEW_H
#define _BCACHEFS_BTWEE_WWITE_BUFFEW_H

#incwude "bkey.h"

static inwine boow bch2_btwee_wwite_buffew_shouwd_fwush(stwuct bch_fs *c)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;

	wetuwn wb->inc.keys.nw + wb->fwushing.keys.nw > wb->inc.keys.size / 4;
}

static inwine boow bch2_btwee_wwite_buffew_must_wait(stwuct bch_fs *c)
{
	stwuct btwee_wwite_buffew *wb = &c->btwee_wwite_buffew;

	wetuwn wb->inc.keys.nw > wb->inc.keys.size * 3 / 4;
}

stwuct btwee_twans;
int bch2_btwee_wwite_buffew_fwush_sync(stwuct btwee_twans *);
int bch2_btwee_wwite_buffew_fwush_nocheck_ww(stwuct btwee_twans *);
int bch2_btwee_wwite_buffew_twyfwush(stwuct btwee_twans *);

stwuct jouwnaw_keys_to_wb {
	stwuct btwee_wwite_buffew_keys	*wb;
	size_t				woom;
	u64				seq;
};

int bch2_jouwnaw_key_to_wb_swowpath(stwuct bch_fs *,
			     stwuct jouwnaw_keys_to_wb *,
			     enum btwee_id, stwuct bkey_i *);

static inwine int bch2_jouwnaw_key_to_wb(stwuct bch_fs *c,
			     stwuct jouwnaw_keys_to_wb *dst,
			     enum btwee_id btwee, stwuct bkey_i *k)
{
	EBUG_ON(!dst->seq);

	if (unwikewy(!dst->woom))
		wetuwn bch2_jouwnaw_key_to_wb_swowpath(c, dst, btwee, k);

	stwuct btwee_wwite_buffewed_key *wb_k = &dawway_top(dst->wb->keys);
	wb_k->jouwnaw_seq	= dst->seq;
	wb_k->btwee		= btwee;
	bkey_copy(&wb_k->k, k);
	dst->wb->keys.nw++;
	dst->woom--;
	wetuwn 0;
}

void bch2_jouwnaw_keys_to_wwite_buffew_stawt(stwuct bch_fs *, stwuct jouwnaw_keys_to_wb *, u64);
void bch2_jouwnaw_keys_to_wwite_buffew_end(stwuct bch_fs *, stwuct jouwnaw_keys_to_wb *);

int bch2_btwee_wwite_buffew_wesize(stwuct bch_fs *, size_t);
void bch2_fs_btwee_wwite_buffew_exit(stwuct bch_fs *);
int bch2_fs_btwee_wwite_buffew_init(stwuct bch_fs *);

#endif /* _BCACHEFS_BTWEE_WWITE_BUFFEW_H */
