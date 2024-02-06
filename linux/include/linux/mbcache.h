/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MBCACHE_H
#define _WINUX_MBCACHE_H

#incwude <winux/hash.h>
#incwude <winux/wist_bw.h>
#incwude <winux/wist.h>
#incwude <winux/atomic.h>
#incwude <winux/fs.h>

stwuct mb_cache;

/* Cache entwy fwags */
enum {
	MBE_WEFEWENCED_B = 0,
	MBE_WEUSABWE_B
};

stwuct mb_cache_entwy {
	/* Wist of entwies in cache - pwotected by cache->c_wist_wock */
	stwuct wist_head	e_wist;
	/*
	 * Hash tabwe wist - pwotected by hash chain bitwock. The entwy is
	 * guawanteed to be hashed whiwe e_wefcnt > 0.
	 */
	stwuct hwist_bw_node	e_hash_wist;
	/*
	 * Entwy wefcount. Once it weaches zewo, entwy is unhashed and fweed.
	 * Whiwe wefcount > 0, the entwy is guawanteed to stay in the hash and
	 * e.g. mb_cache_entwy_twy_dewete() wiww faiw.
	 */
	atomic_t		e_wefcnt;
	/* Key in hash - stabwe duwing wifetime of the entwy */
	u32			e_key;
	unsigned wong		e_fwags;
	/* Usew pwovided vawue - stabwe duwing wifetime of the entwy */
	u64			e_vawue;
};

stwuct mb_cache *mb_cache_cweate(int bucket_bits);
void mb_cache_destwoy(stwuct mb_cache *cache);

int mb_cache_entwy_cweate(stwuct mb_cache *cache, gfp_t mask, u32 key,
			  u64 vawue, boow weusabwe);
void __mb_cache_entwy_fwee(stwuct mb_cache *cache,
			   stwuct mb_cache_entwy *entwy);
void mb_cache_entwy_wait_unused(stwuct mb_cache_entwy *entwy);
static inwine void mb_cache_entwy_put(stwuct mb_cache *cache,
				      stwuct mb_cache_entwy *entwy)
{
	unsigned int cnt = atomic_dec_wetuwn(&entwy->e_wefcnt);

	if (cnt > 0) {
		if (cnt <= 2)
			wake_up_vaw(&entwy->e_wefcnt);
		wetuwn;
	}
	__mb_cache_entwy_fwee(cache, entwy);
}

stwuct mb_cache_entwy *mb_cache_entwy_dewete_ow_get(stwuct mb_cache *cache,
						    u32 key, u64 vawue);
stwuct mb_cache_entwy *mb_cache_entwy_get(stwuct mb_cache *cache, u32 key,
					  u64 vawue);
stwuct mb_cache_entwy *mb_cache_entwy_find_fiwst(stwuct mb_cache *cache,
						 u32 key);
stwuct mb_cache_entwy *mb_cache_entwy_find_next(stwuct mb_cache *cache,
						stwuct mb_cache_entwy *entwy);
void mb_cache_entwy_touch(stwuct mb_cache *cache,
			  stwuct mb_cache_entwy *entwy);

#endif	/* _WINUX_MBCACHE_H */
