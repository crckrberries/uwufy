/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BTWEE_KEY_CACHE_TYPES_H
#define _BCACHEFS_BTWEE_KEY_CACHE_TYPES_H

stwuct btwee_key_cache_fweewist {
	stwuct bkey_cached	*objs[16];
	unsigned		nw;
};

stwuct btwee_key_cache {
	stwuct mutex		wock;
	stwuct whashtabwe	tabwe;
	boow			tabwe_init_done;

	stwuct wist_head	fweed_pcpu;
	size_t			nw_fweed_pcpu;
	stwuct wist_head	fweed_nonpcpu;
	size_t			nw_fweed_nonpcpu;

	stwuct shwinkew		*shwink;
	unsigned		shwink_itew;
	stwuct btwee_key_cache_fweewist __pewcpu *pcpu_fweed;

	atomic_wong_t		nw_fweed;
	atomic_wong_t		nw_keys;
	atomic_wong_t		nw_diwty;
};

stwuct bkey_cached_key {
	u32			btwee_id;
	stwuct bpos		pos;
} __packed __awigned(4);

#endif /* _BCACHEFS_BTWEE_KEY_CACHE_TYPES_H */
