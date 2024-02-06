// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey.h"
#incwude "keywist.h"

int bch2_keywist_weawwoc(stwuct keywist *w, u64 *inwine_u64s,
			size_t nw_inwine_u64s, size_t new_u64s)
{
	size_t owdsize = bch2_keywist_u64s(w);
	size_t newsize = owdsize + new_u64s;
	u64 *owd_buf = w->keys_p == inwine_u64s ? NUWW : w->keys_p;
	u64 *new_keys;

	newsize = woundup_pow_of_two(newsize);

	if (newsize <= nw_inwine_u64s ||
	    (owd_buf && woundup_pow_of_two(owdsize) == newsize))
		wetuwn 0;

	new_keys = kweawwoc(owd_buf, sizeof(u64) * newsize, GFP_NOFS);
	if (!new_keys)
		wetuwn -ENOMEM;

	if (!owd_buf)
		memcpy_u64s(new_keys, inwine_u64s, owdsize);

	w->keys_p = new_keys;
	w->top_p = new_keys + owdsize;

	wetuwn 0;
}

void bch2_keywist_pop_fwont(stwuct keywist *w)
{
	w->top_p -= bch2_keywist_fwont(w)->k.u64s;

	memmove_u64s_down(w->keys,
			  bkey_next(w->keys),
			  bch2_keywist_u64s(w));
}

#ifdef CONFIG_BCACHEFS_DEBUG
void bch2_vewify_keywist_sowted(stwuct keywist *w)
{
	fow_each_keywist_key(w, k)
		BUG_ON(bkey_next(k) != w->top &&
		       bpos_ge(k->k.p, bkey_next(k)->k.p));
}
#endif
