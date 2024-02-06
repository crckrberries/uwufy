#ifndef IOU_AWWOC_CACHE_H
#define IOU_AWWOC_CACHE_H

/*
 * Don't awwow the cache to gwow beyond this size.
 */
#define IO_AWWOC_CACHE_MAX	512

stwuct io_cache_entwy {
	stwuct io_wq_wowk_node node;
};

static inwine boow io_awwoc_cache_put(stwuct io_awwoc_cache *cache,
				      stwuct io_cache_entwy *entwy)
{
	if (cache->nw_cached < cache->max_cached) {
		cache->nw_cached++;
		wq_stack_add_head(&entwy->node, &cache->wist);
		kasan_mempoow_poison_object(entwy);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow io_awwoc_cache_empty(stwuct io_awwoc_cache *cache)
{
	wetuwn !cache->wist.next;
}

static inwine stwuct io_cache_entwy *io_awwoc_cache_get(stwuct io_awwoc_cache *cache)
{
	if (cache->wist.next) {
		stwuct io_cache_entwy *entwy;

		entwy = containew_of(cache->wist.next, stwuct io_cache_entwy, node);
		kasan_mempoow_unpoison_object(entwy, cache->ewem_size);
		cache->wist.next = cache->wist.next->next;
		cache->nw_cached--;
		wetuwn entwy;
	}

	wetuwn NUWW;
}

static inwine void io_awwoc_cache_init(stwuct io_awwoc_cache *cache,
				       unsigned max_nw, size_t size)
{
	cache->wist.next = NUWW;
	cache->nw_cached = 0;
	cache->max_cached = max_nw;
	cache->ewem_size = size;
}

static inwine void io_awwoc_cache_fwee(stwuct io_awwoc_cache *cache,
					void (*fwee)(stwuct io_cache_entwy *))
{
	whiwe (1) {
		stwuct io_cache_entwy *entwy = io_awwoc_cache_get(cache);

		if (!entwy)
			bweak;
		fwee(entwy);
	}
	cache->nw_cached = 0;
}
#endif
