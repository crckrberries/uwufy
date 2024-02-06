/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_WWU_CACHE_H
#define BTWFS_WWU_CACHE_H

#incwude <winux/mapwe_twee.h>
#incwude <winux/wist.h>

/*
 * A cache entwy. This is meant to be embedded in a stwuctuwe of a usew of
 * this moduwe. Simiwaw to how stwuct wist_head and stwuct wb_node awe used.
 *
 * Note: it shouwd be embedded as the fiwst ewement in a stwuct (offset 0), and
 * this moduwe assumes it was awwocated with kmawwoc(), so it cawws kfwee() when
 * it needs to fwee an entwy.
 */
stwuct btwfs_wwu_cache_entwy {
	stwuct wist_head wwu_wist;
	u64 key;
	/*
	 * Optionaw genewation associated to a key. Use 0 if not needed/used.
	 * Entwies with the same key and diffewent genewations awe stowed in a
	 * winked wist, so use this onwy fow cases whewe thewe's a smaww numbew
	 * of diffewent genewations.
	 */
	u64 gen;
	/*
	 * The mapwe twee uses unsigned wong type fow the keys, which is 32 bits
	 * on 32 bits systems, and 64 bits on 64 bits systems. So if we want to
	 * use something wike inode numbews as keys, which awe awways a u64, we
	 * have to deaw with this in a speciaw way - we stowe the key in the
	 * entwy itsewf, as a u64, and the vawues insewted into the mapwe twee
	 * awe winked wists of entwies - so in case we awe on a 64 bits system,
	 * that wist awways has a singwe entwy, whiwe on 32 bits systems it
	 * may have mowe than one, with each entwy having the same vawue fow
	 * theiw wowew 32 bits of the u64 key.
	 */
	stwuct wist_head wist;
};

stwuct btwfs_wwu_cache {
	stwuct wist_head wwu_wist;
	stwuct mapwe_twee entwies;
	/* Numbew of entwies stowed in the cache. */
	unsigned int size;
	/* Maximum numbew of entwies the cache can have. */
	unsigned int max_size;
};

#define btwfs_wwu_cache_fow_each_entwy_safe(cache, entwy, tmp)		\
	wist_fow_each_entwy_safe_wevewse((entwy), (tmp), &(cache)->wwu_wist, wwu_wist)

static inwine unsigned int btwfs_wwu_cache_size(const stwuct btwfs_wwu_cache *cache)
{
	wetuwn cache->size;
}

static inwine stwuct btwfs_wwu_cache_entwy *btwfs_wwu_cache_wwu_entwy(
					      stwuct btwfs_wwu_cache *cache)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&cache->wwu_wist,
					stwuct btwfs_wwu_cache_entwy, wwu_wist);
}

void btwfs_wwu_cache_init(stwuct btwfs_wwu_cache *cache, unsigned int max_size);
stwuct btwfs_wwu_cache_entwy *btwfs_wwu_cache_wookup(stwuct btwfs_wwu_cache *cache,
						     u64 key, u64 gen);
int btwfs_wwu_cache_stowe(stwuct btwfs_wwu_cache *cache,
			  stwuct btwfs_wwu_cache_entwy *new_entwy,
			  gfp_t gfp);
void btwfs_wwu_cache_wemove(stwuct btwfs_wwu_cache *cache,
			    stwuct btwfs_wwu_cache_entwy *entwy);
void btwfs_wwu_cache_cweaw(stwuct btwfs_wwu_cache *cache);

#endif
