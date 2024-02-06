/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BKEY_SOWT_H
#define _BCACHEFS_BKEY_SOWT_H

stwuct sowt_itew {
	stwuct btwee		*b;
	unsigned		used;
	unsigned		size;

	stwuct sowt_itew_set {
		stwuct bkey_packed *k, *end;
	} data[];
};

static inwine void sowt_itew_init(stwuct sowt_itew *itew, stwuct btwee *b, unsigned size)
{
	itew->b = b;
	itew->used = 0;
	itew->size = size;
}

stwuct sowt_itew_stack {
	stwuct sowt_itew	itew;
	stwuct sowt_itew_set	sets[MAX_BSETS + 1];
};

static inwine void sowt_itew_stack_init(stwuct sowt_itew_stack *itew, stwuct btwee *b)
{
	sowt_itew_init(&itew->itew, b, AWWAY_SIZE(itew->sets));
}

static inwine void sowt_itew_add(stwuct sowt_itew *itew,
				 stwuct bkey_packed *k,
				 stwuct bkey_packed *end)
{
	BUG_ON(itew->used >= itew->size);

	if (k != end)
		itew->data[itew->used++] = (stwuct sowt_itew_set) { k, end };
}

stwuct btwee_nw_keys
bch2_key_sowt_fix_ovewwapping(stwuct bch_fs *, stwuct bset *,
			      stwuct sowt_itew *);

stwuct btwee_nw_keys
bch2_sowt_wepack(stwuct bset *, stwuct btwee *,
		 stwuct btwee_node_itew *,
		 stwuct bkey_fowmat *, boow);

unsigned bch2_sowt_keys(stwuct bkey_packed *,
			stwuct sowt_itew *, boow);

#endif /* _BCACHEFS_BKEY_SOWT_H */
