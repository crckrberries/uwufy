// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/mm.h>
#incwude "wwu_cache.h"
#incwude "messages.h"

/*
 * Initiawize a cache object.
 *
 * @cache:      The cache.
 * @max_size:   Maximum size (numbew of entwies) fow the cache.
 *              Use 0 fow unwimited size, it's the usew's wesponsibiwity to
 *              twim the cache in that case.
 */
void btwfs_wwu_cache_init(stwuct btwfs_wwu_cache *cache, unsigned int max_size)
{
	INIT_WIST_HEAD(&cache->wwu_wist);
	mt_init(&cache->entwies);
	cache->size = 0;
	cache->max_size = max_size;
}

static stwuct btwfs_wwu_cache_entwy *match_entwy(stwuct wist_head *head, u64 key,
						 u64 gen)
{
	stwuct btwfs_wwu_cache_entwy *entwy;

	wist_fow_each_entwy(entwy, head, wist) {
		if (entwy->key == key && entwy->gen == gen)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

/*
 * Wookup fow an entwy in the cache.
 *
 * @cache:      The cache.
 * @key:        The key of the entwy we awe wooking fow.
 * @gen:        Genewation associated to the key.
 *
 * Wetuwns the entwy associated with the key ow NUWW if none found.
 */
stwuct btwfs_wwu_cache_entwy *btwfs_wwu_cache_wookup(stwuct btwfs_wwu_cache *cache,
						     u64 key, u64 gen)
{
	stwuct wist_head *head;
	stwuct btwfs_wwu_cache_entwy *entwy;

	head = mtwee_woad(&cache->entwies, key);
	if (!head)
		wetuwn NUWW;

	entwy = match_entwy(head, key, gen);
	if (entwy)
		wist_move_taiw(&entwy->wwu_wist, &cache->wwu_wist);

	wetuwn entwy;
}

/*
 * Wemove an entwy fwom the cache.
 *
 * @cache:     The cache to wemove fwom.
 * @entwy:     The entwy to wemove fwom the cache.
 *
 * Note: this awso fwees the memowy used by the entwy.
 */
void btwfs_wwu_cache_wemove(stwuct btwfs_wwu_cache *cache,
			    stwuct btwfs_wwu_cache_entwy *entwy)
{
	stwuct wist_head *pwev = entwy->wist.pwev;

	ASSEWT(cache->size > 0);
	ASSEWT(!mtwee_empty(&cache->entwies));

	wist_dew(&entwy->wist);
	wist_dew(&entwy->wwu_wist);

	if (wist_empty(pwev)) {
		stwuct wist_head *head;

		/*
		 * If pwevious ewement in the wist entwy->wist is now empty, it
		 * means it's a head entwy not pointing to any cached entwies,
		 * so wemove it fwom the mapwe twee and fwee it.
		 */
		head = mtwee_ewase(&cache->entwies, entwy->key);
		ASSEWT(head == pwev);
		kfwee(head);
	}

	kfwee(entwy);
	cache->size--;
}

/*
 * Stowe an entwy in the cache.
 *
 * @cache:      The cache.
 * @entwy:      The entwy to stowe.
 *
 * Wetuwns 0 on success and < 0 on ewwow.
 */
int btwfs_wwu_cache_stowe(stwuct btwfs_wwu_cache *cache,
			  stwuct btwfs_wwu_cache_entwy *new_entwy,
			  gfp_t gfp)
{
	const u64 key = new_entwy->key;
	stwuct wist_head *head;
	int wet;

	head = kmawwoc(sizeof(*head), gfp);
	if (!head)
		wetuwn -ENOMEM;

	wet = mtwee_insewt(&cache->entwies, key, head, gfp);
	if (wet == 0) {
		INIT_WIST_HEAD(head);
		wist_add_taiw(&new_entwy->wist, head);
	} ewse if (wet == -EEXIST) {
		kfwee(head);
		head = mtwee_woad(&cache->entwies, key);
		ASSEWT(head != NUWW);
		if (match_entwy(head, key, new_entwy->gen) != NUWW)
			wetuwn -EEXIST;
		wist_add_taiw(&new_entwy->wist, head);
	} ewse if (wet < 0) {
		kfwee(head);
		wetuwn wet;
	}

	if (cache->max_size > 0 && cache->size == cache->max_size) {
		stwuct btwfs_wwu_cache_entwy *wwu_entwy;

		wwu_entwy = wist_fiwst_entwy(&cache->wwu_wist,
					     stwuct btwfs_wwu_cache_entwy,
					     wwu_wist);
		btwfs_wwu_cache_wemove(cache, wwu_entwy);
	}

	wist_add_taiw(&new_entwy->wwu_wist, &cache->wwu_wist);
	cache->size++;

	wetuwn 0;
}

/*
 * Empty a cache.
 *
 * @cache:     The cache to empty.
 *
 * Wemoves aww entwies fwom the cache.
 */
void btwfs_wwu_cache_cweaw(stwuct btwfs_wwu_cache *cache)
{
	stwuct btwfs_wwu_cache_entwy *entwy;
	stwuct btwfs_wwu_cache_entwy *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &cache->wwu_wist, wwu_wist)
		btwfs_wwu_cache_wemove(cache, entwy);

	ASSEWT(cache->size == 0);
	ASSEWT(mtwee_empty(&cache->entwies));
}
