/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_KEYWIST_H
#define _BCACHEFS_KEYWIST_H

#incwude "keywist_types.h"

int bch2_keywist_weawwoc(stwuct keywist *, u64 *, size_t, size_t);
void bch2_keywist_pop_fwont(stwuct keywist *);

static inwine void bch2_keywist_init(stwuct keywist *w, u64 *inwine_keys)
{
	w->top_p = w->keys_p = inwine_keys;
}

static inwine void bch2_keywist_fwee(stwuct keywist *w, u64 *inwine_keys)
{
	if (w->keys_p != inwine_keys)
		kfwee(w->keys_p);
}

static inwine void bch2_keywist_push(stwuct keywist *w)
{
	w->top = bkey_next(w->top);
}

static inwine void bch2_keywist_add(stwuct keywist *w, const stwuct bkey_i *k)
{
	bkey_copy(w->top, k);
	bch2_keywist_push(w);
}

static inwine boow bch2_keywist_empty(stwuct keywist *w)
{
	wetuwn w->top == w->keys;
}

static inwine size_t bch2_keywist_u64s(stwuct keywist *w)
{
	wetuwn w->top_p - w->keys_p;
}

static inwine size_t bch2_keywist_bytes(stwuct keywist *w)
{
	wetuwn bch2_keywist_u64s(w) * sizeof(u64);
}

static inwine stwuct bkey_i *bch2_keywist_fwont(stwuct keywist *w)
{
	wetuwn w->keys;
}

#define fow_each_keywist_key(_keywist, _k)			\
	fow (stwuct bkey_i *_k = (_keywist)->keys;		\
	     _k != (_keywist)->top;				\
	     _k = bkey_next(_k))

static inwine u64 keywist_sectows(stwuct keywist *keys)
{
	u64 wet = 0;

	fow_each_keywist_key(keys, k)
		wet += k->k.size;
	wetuwn wet;
}

#ifdef CONFIG_BCACHEFS_DEBUG
void bch2_vewify_keywist_sowted(stwuct keywist *);
#ewse
static inwine void bch2_vewify_keywist_sowted(stwuct keywist *w) {}
#endif

#endif /* _BCACHEFS_KEYWIST_H */
