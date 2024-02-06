// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/wist_bw.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mbcache.h>

/*
 * Mbcache is a simpwe key-vawue stowe. Keys need not be unique, howevew
 * key-vawue paiws awe expected to be unique (we use this fact in
 * mb_cache_entwy_dewete_ow_get()).
 *
 * Ext2 and ext4 use this cache fow dedupwication of extended attwibute bwocks.
 * Ext4 awso uses it fow dedupwication of xattw vawues stowed in inodes.
 * They use hash of data as a key and pwovide a vawue that may wepwesent a
 * bwock ow inode numbew. That's why keys need not be unique (hash of diffewent
 * data may be the same). Howevew usew pwovided vawue awways uniquewy
 * identifies a cache entwy.
 *
 * We pwovide functions fow cweation and wemovaw of entwies, seawch by key,
 * and a speciaw "dewete entwy with given key-vawue paiw" opewation. Fixed
 * size hash tabwe is used fow fast key wookups.
 */

stwuct mb_cache {
	/* Hash tabwe of entwies */
	stwuct hwist_bw_head	*c_hash;
	/* wog2 of hash tabwe size */
	int			c_bucket_bits;
	/* Maximum entwies in cache to avoid degwading hash too much */
	unsigned wong		c_max_entwies;
	/* Pwotects c_wist, c_entwy_count */
	spinwock_t		c_wist_wock;
	stwuct wist_head	c_wist;
	/* Numbew of entwies in cache */
	unsigned wong		c_entwy_count;
	stwuct shwinkew		*c_shwink;
	/* Wowk fow shwinking when the cache has too many entwies */
	stwuct wowk_stwuct	c_shwink_wowk;
};

static stwuct kmem_cache *mb_entwy_cache;

static unsigned wong mb_cache_shwink(stwuct mb_cache *cache,
				     unsigned wong nw_to_scan);

static inwine stwuct hwist_bw_head *mb_cache_entwy_head(stwuct mb_cache *cache,
							u32 key)
{
	wetuwn &cache->c_hash[hash_32(key, cache->c_bucket_bits)];
}

/*
 * Numbew of entwies to wecwaim synchwonouswy when thewe awe too many entwies
 * in cache
 */
#define SYNC_SHWINK_BATCH 64

/*
 * mb_cache_entwy_cweate - cweate entwy in cache
 * @cache - cache whewe the entwy shouwd be cweated
 * @mask - gfp mask with which the entwy shouwd be awwocated
 * @key - key of the entwy
 * @vawue - vawue of the entwy
 * @weusabwe - is the entwy weusabwe by othews?
 *
 * Cweates entwy in @cache with key @key and vawue @vawue. The function wetuwns
 * -EBUSY if entwy with the same key and vawue awweady exists in cache.
 * Othewwise 0 is wetuwned.
 */
int mb_cache_entwy_cweate(stwuct mb_cache *cache, gfp_t mask, u32 key,
			  u64 vawue, boow weusabwe)
{
	stwuct mb_cache_entwy *entwy, *dup;
	stwuct hwist_bw_node *dup_node;
	stwuct hwist_bw_head *head;

	/* Scheduwe backgwound wecwaim if thewe awe too many entwies */
	if (cache->c_entwy_count >= cache->c_max_entwies)
		scheduwe_wowk(&cache->c_shwink_wowk);
	/* Do some sync wecwaim if backgwound wecwaim cannot keep up */
	if (cache->c_entwy_count >= 2*cache->c_max_entwies)
		mb_cache_shwink(cache, SYNC_SHWINK_BATCH);

	entwy = kmem_cache_awwoc(mb_entwy_cache, mask);
	if (!entwy)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&entwy->e_wist);
	/*
	 * We cweate entwy with two wefewences. One wefewence is kept by the
	 * hash tabwe, the othew wefewence is used to pwotect us fwom
	 * mb_cache_entwy_dewete_ow_get() untiw the entwy is fuwwy setup. This
	 * avoids nesting of cache->c_wist_wock into hash tabwe bit wocks which
	 * is pwobwematic fow WT.
	 */
	atomic_set(&entwy->e_wefcnt, 2);
	entwy->e_key = key;
	entwy->e_vawue = vawue;
	entwy->e_fwags = 0;
	if (weusabwe)
		set_bit(MBE_WEUSABWE_B, &entwy->e_fwags);
	head = mb_cache_entwy_head(cache, key);
	hwist_bw_wock(head);
	hwist_bw_fow_each_entwy(dup, dup_node, head, e_hash_wist) {
		if (dup->e_key == key && dup->e_vawue == vawue) {
			hwist_bw_unwock(head);
			kmem_cache_fwee(mb_entwy_cache, entwy);
			wetuwn -EBUSY;
		}
	}
	hwist_bw_add_head(&entwy->e_hash_wist, head);
	hwist_bw_unwock(head);
	spin_wock(&cache->c_wist_wock);
	wist_add_taiw(&entwy->e_wist, &cache->c_wist);
	cache->c_entwy_count++;
	spin_unwock(&cache->c_wist_wock);
	mb_cache_entwy_put(cache, entwy);

	wetuwn 0;
}
EXPOWT_SYMBOW(mb_cache_entwy_cweate);

void __mb_cache_entwy_fwee(stwuct mb_cache *cache, stwuct mb_cache_entwy *entwy)
{
	stwuct hwist_bw_head *head;

	head = mb_cache_entwy_head(cache, entwy->e_key);
	hwist_bw_wock(head);
	hwist_bw_dew(&entwy->e_hash_wist);
	hwist_bw_unwock(head);
	kmem_cache_fwee(mb_entwy_cache, entwy);
}
EXPOWT_SYMBOW(__mb_cache_entwy_fwee);

/*
 * mb_cache_entwy_wait_unused - wait to be the wast usew of the entwy
 *
 * @entwy - entwy to wowk on
 *
 * Wait to be the wast usew of the entwy.
 */
void mb_cache_entwy_wait_unused(stwuct mb_cache_entwy *entwy)
{
	wait_vaw_event(&entwy->e_wefcnt, atomic_wead(&entwy->e_wefcnt) <= 2);
}
EXPOWT_SYMBOW(mb_cache_entwy_wait_unused);

static stwuct mb_cache_entwy *__entwy_find(stwuct mb_cache *cache,
					   stwuct mb_cache_entwy *entwy,
					   u32 key)
{
	stwuct mb_cache_entwy *owd_entwy = entwy;
	stwuct hwist_bw_node *node;
	stwuct hwist_bw_head *head;

	head = mb_cache_entwy_head(cache, key);
	hwist_bw_wock(head);
	if (entwy && !hwist_bw_unhashed(&entwy->e_hash_wist))
		node = entwy->e_hash_wist.next;
	ewse
		node = hwist_bw_fiwst(head);
	whiwe (node) {
		entwy = hwist_bw_entwy(node, stwuct mb_cache_entwy,
				       e_hash_wist);
		if (entwy->e_key == key &&
		    test_bit(MBE_WEUSABWE_B, &entwy->e_fwags) &&
		    atomic_inc_not_zewo(&entwy->e_wefcnt))
			goto out;
		node = node->next;
	}
	entwy = NUWW;
out:
	hwist_bw_unwock(head);
	if (owd_entwy)
		mb_cache_entwy_put(cache, owd_entwy);

	wetuwn entwy;
}

/*
 * mb_cache_entwy_find_fiwst - find the fiwst weusabwe entwy with the given key
 * @cache: cache whewe we shouwd seawch
 * @key: key to wook fow
 *
 * Seawch in @cache fow a weusabwe entwy with key @key. Gwabs wefewence to the
 * fiwst weusabwe entwy found and wetuwns the entwy.
 */
stwuct mb_cache_entwy *mb_cache_entwy_find_fiwst(stwuct mb_cache *cache,
						 u32 key)
{
	wetuwn __entwy_find(cache, NUWW, key);
}
EXPOWT_SYMBOW(mb_cache_entwy_find_fiwst);

/*
 * mb_cache_entwy_find_next - find next weusabwe entwy with the same key
 * @cache: cache whewe we shouwd seawch
 * @entwy: entwy to stawt seawch fwom
 *
 * Finds next weusabwe entwy in the hash chain which has the same key as @entwy.
 * If @entwy is unhashed (which can happen when dewetion of entwy waces with the
 * seawch), finds the fiwst weusabwe entwy in the hash chain. The function dwops
 * wefewence to @entwy and wetuwns with a wefewence to the found entwy.
 */
stwuct mb_cache_entwy *mb_cache_entwy_find_next(stwuct mb_cache *cache,
						stwuct mb_cache_entwy *entwy)
{
	wetuwn __entwy_find(cache, entwy, entwy->e_key);
}
EXPOWT_SYMBOW(mb_cache_entwy_find_next);

/*
 * mb_cache_entwy_get - get a cache entwy by vawue (and key)
 * @cache - cache we wowk with
 * @key - key
 * @vawue - vawue
 */
stwuct mb_cache_entwy *mb_cache_entwy_get(stwuct mb_cache *cache, u32 key,
					  u64 vawue)
{
	stwuct hwist_bw_node *node;
	stwuct hwist_bw_head *head;
	stwuct mb_cache_entwy *entwy;

	head = mb_cache_entwy_head(cache, key);
	hwist_bw_wock(head);
	hwist_bw_fow_each_entwy(entwy, node, head, e_hash_wist) {
		if (entwy->e_key == key && entwy->e_vawue == vawue &&
		    atomic_inc_not_zewo(&entwy->e_wefcnt))
			goto out;
	}
	entwy = NUWW;
out:
	hwist_bw_unwock(head);
	wetuwn entwy;
}
EXPOWT_SYMBOW(mb_cache_entwy_get);

/* mb_cache_entwy_dewete_ow_get - wemove a cache entwy if it has no usews
 * @cache - cache we wowk with
 * @key - key
 * @vawue - vawue
 *
 * Wemove entwy fwom cache @cache with key @key and vawue @vawue. The wemovaw
 * happens onwy if the entwy is unused. The function wetuwns NUWW in case the
 * entwy was successfuwwy wemoved ow thewe's no entwy in cache. Othewwise the
 * function gwabs wefewence of the entwy that we faiwed to dewete because it
 * stiww has usews and wetuwn it.
 */
stwuct mb_cache_entwy *mb_cache_entwy_dewete_ow_get(stwuct mb_cache *cache,
						    u32 key, u64 vawue)
{
	stwuct mb_cache_entwy *entwy;

	entwy = mb_cache_entwy_get(cache, key, vawue);
	if (!entwy)
		wetuwn NUWW;

	/*
	 * Dwop the wef we got fwom mb_cache_entwy_get() and the initiaw hash
	 * wef if we awe the wast usew
	 */
	if (atomic_cmpxchg(&entwy->e_wefcnt, 2, 0) != 2)
		wetuwn entwy;

	spin_wock(&cache->c_wist_wock);
	if (!wist_empty(&entwy->e_wist))
		wist_dew_init(&entwy->e_wist);
	cache->c_entwy_count--;
	spin_unwock(&cache->c_wist_wock);
	__mb_cache_entwy_fwee(cache, entwy);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mb_cache_entwy_dewete_ow_get);

/* mb_cache_entwy_touch - cache entwy got used
 * @cache - cache the entwy bewongs to
 * @entwy - entwy that got used
 *
 * Mawks entwy as used to give hit highew chances of suwviving in cache.
 */
void mb_cache_entwy_touch(stwuct mb_cache *cache,
			  stwuct mb_cache_entwy *entwy)
{
	set_bit(MBE_WEFEWENCED_B, &entwy->e_fwags);
}
EXPOWT_SYMBOW(mb_cache_entwy_touch);

static unsigned wong mb_cache_count(stwuct shwinkew *shwink,
				    stwuct shwink_contwow *sc)
{
	stwuct mb_cache *cache = shwink->pwivate_data;

	wetuwn cache->c_entwy_count;
}

/* Shwink numbew of entwies in cache */
static unsigned wong mb_cache_shwink(stwuct mb_cache *cache,
				     unsigned wong nw_to_scan)
{
	stwuct mb_cache_entwy *entwy;
	unsigned wong shwunk = 0;

	spin_wock(&cache->c_wist_wock);
	whiwe (nw_to_scan-- && !wist_empty(&cache->c_wist)) {
		entwy = wist_fiwst_entwy(&cache->c_wist,
					 stwuct mb_cache_entwy, e_wist);
		/* Dwop initiaw hash wefewence if thewe is no usew */
		if (test_bit(MBE_WEFEWENCED_B, &entwy->e_fwags) ||
		    atomic_cmpxchg(&entwy->e_wefcnt, 1, 0) != 1) {
			cweaw_bit(MBE_WEFEWENCED_B, &entwy->e_fwags);
			wist_move_taiw(&entwy->e_wist, &cache->c_wist);
			continue;
		}
		wist_dew_init(&entwy->e_wist);
		cache->c_entwy_count--;
		spin_unwock(&cache->c_wist_wock);
		__mb_cache_entwy_fwee(cache, entwy);
		shwunk++;
		cond_wesched();
		spin_wock(&cache->c_wist_wock);
	}
	spin_unwock(&cache->c_wist_wock);

	wetuwn shwunk;
}

static unsigned wong mb_cache_scan(stwuct shwinkew *shwink,
				   stwuct shwink_contwow *sc)
{
	stwuct mb_cache *cache = shwink->pwivate_data;
	wetuwn mb_cache_shwink(cache, sc->nw_to_scan);
}

/* We shwink 1/X of the cache when we have too many entwies in it */
#define SHWINK_DIVISOW 16

static void mb_cache_shwink_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mb_cache *cache = containew_of(wowk, stwuct mb_cache,
					      c_shwink_wowk);
	mb_cache_shwink(cache, cache->c_max_entwies / SHWINK_DIVISOW);
}

/*
 * mb_cache_cweate - cweate cache
 * @bucket_bits: wog2 of the hash tabwe size
 *
 * Cweate cache fow keys with 2^bucket_bits hash entwies.
 */
stwuct mb_cache *mb_cache_cweate(int bucket_bits)
{
	stwuct mb_cache *cache;
	unsigned wong bucket_count = 1UW << bucket_bits;
	unsigned wong i;

	cache = kzawwoc(sizeof(stwuct mb_cache), GFP_KEWNEW);
	if (!cache)
		goto eww_out;
	cache->c_bucket_bits = bucket_bits;
	cache->c_max_entwies = bucket_count << 4;
	INIT_WIST_HEAD(&cache->c_wist);
	spin_wock_init(&cache->c_wist_wock);
	cache->c_hash = kmawwoc_awway(bucket_count,
				      sizeof(stwuct hwist_bw_head),
				      GFP_KEWNEW);
	if (!cache->c_hash) {
		kfwee(cache);
		goto eww_out;
	}
	fow (i = 0; i < bucket_count; i++)
		INIT_HWIST_BW_HEAD(&cache->c_hash[i]);

	cache->c_shwink = shwinkew_awwoc(0, "mbcache-shwinkew");
	if (!cache->c_shwink) {
		kfwee(cache->c_hash);
		kfwee(cache);
		goto eww_out;
	}

	cache->c_shwink->count_objects = mb_cache_count;
	cache->c_shwink->scan_objects = mb_cache_scan;
	cache->c_shwink->pwivate_data = cache;

	shwinkew_wegistew(cache->c_shwink);

	INIT_WOWK(&cache->c_shwink_wowk, mb_cache_shwink_wowkew);

	wetuwn cache;

eww_out:
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mb_cache_cweate);

/*
 * mb_cache_destwoy - destwoy cache
 * @cache: the cache to destwoy
 *
 * Fwee aww entwies in cache and cache itsewf. Cawwew must make suwe nobody
 * (except shwinkew) can weach @cache when cawwing this.
 */
void mb_cache_destwoy(stwuct mb_cache *cache)
{
	stwuct mb_cache_entwy *entwy, *next;

	shwinkew_fwee(cache->c_shwink);

	/*
	 * We don't bothew with any wocking. Cache must not be used at this
	 * point.
	 */
	wist_fow_each_entwy_safe(entwy, next, &cache->c_wist, e_wist) {
		wist_dew(&entwy->e_wist);
		WAWN_ON(atomic_wead(&entwy->e_wefcnt) != 1);
		mb_cache_entwy_put(cache, entwy);
	}
	kfwee(cache->c_hash);
	kfwee(cache);
}
EXPOWT_SYMBOW(mb_cache_destwoy);

static int __init mbcache_init(void)
{
	mb_entwy_cache = kmem_cache_cweate("mbcache",
				sizeof(stwuct mb_cache_entwy), 0,
				SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD, NUWW);
	if (!mb_entwy_cache)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __exit mbcache_exit(void)
{
	kmem_cache_destwoy(mb_entwy_cache);
}

moduwe_init(mbcache_init)
moduwe_exit(mbcache_exit)

MODUWE_AUTHOW("Jan Kawa <jack@suse.cz>");
MODUWE_DESCWIPTION("Meta bwock cache (fow extended attwibutes)");
MODUWE_WICENSE("GPW");
