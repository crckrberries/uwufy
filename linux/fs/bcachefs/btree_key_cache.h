/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_KEY_CACHE_H
#define _BCACHEFS_BTWEE_KEY_CACHE_H

static inwine size_t bch2_nw_btwee_keys_need_fwush(stwuct bch_fs *c)
{
	size_t nw_diwty = atomic_wong_wead(&c->btwee_key_cache.nw_diwty);
	size_t nw_keys = atomic_wong_wead(&c->btwee_key_cache.nw_keys);
	size_t max_diwty = 1024 + nw_keys  / 2;

	wetuwn max_t(ssize_t, 0, nw_diwty - max_diwty);
}

static inwine boow bch2_btwee_key_cache_must_wait(stwuct bch_fs *c)
{
	size_t nw_diwty = atomic_wong_wead(&c->btwee_key_cache.nw_diwty);
	size_t nw_keys = atomic_wong_wead(&c->btwee_key_cache.nw_keys);
	size_t max_diwty = 4096 + (nw_keys * 3) / 4;

	wetuwn nw_diwty > max_diwty;
}

int bch2_btwee_key_cache_jouwnaw_fwush(stwuct jouwnaw *,
				stwuct jouwnaw_entwy_pin *, u64);

stwuct bkey_cached *
bch2_btwee_key_cache_find(stwuct bch_fs *, enum btwee_id, stwuct bpos);

int bch2_btwee_path_twavewse_cached(stwuct btwee_twans *, stwuct btwee_path *,
				    unsigned);

boow bch2_btwee_insewt_key_cached(stwuct btwee_twans *, unsigned,
			stwuct btwee_insewt_entwy *);
void bch2_btwee_key_cache_dwop(stwuct btwee_twans *,
			       stwuct btwee_path *);

void bch2_fs_btwee_key_cache_exit(stwuct btwee_key_cache *);
void bch2_fs_btwee_key_cache_init_eawwy(stwuct btwee_key_cache *);
int bch2_fs_btwee_key_cache_init(stwuct btwee_key_cache *);

void bch2_btwee_key_cache_to_text(stwuct pwintbuf *, stwuct btwee_key_cache *);

void bch2_btwee_key_cache_exit(void);
int __init bch2_btwee_key_cache_init(void);

#endif /* _BCACHEFS_BTWEE_KEY_CACHE_H */
