// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2019, 2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 *
 * Usew extended attwibute cwient side cache functions.
 *
 * Authow: Fwank van dew Winden <fwwinden@amazon.com>
 */
#incwude <winux/ewwno.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/wefcount.h>
#incwude <uapi/winux/xattw.h>

#incwude "nfs4_fs.h"
#incwude "intewnaw.h"

/*
 * Usew extended attwibutes cwient side caching is impwemented by having
 * a cache stwuctuwe attached to NFS inodes. This stwuctuwe is awwocated
 * when needed, and fweed when the cache is zapped.
 *
 * The cache stwuctuwe contains as hash tabwe of entwies, and a pointew
 * to a speciaw-cased entwy fow the wistxattw cache.
 *
 * Accessing and awwocating / fweeing the caches is done via wefewence
 * counting. The cache entwies use a simiwaw wefcounting scheme.
 *
 * This makes fweeing a cache, both fwom the shwinkew and fwom the
 * zap cache path, easy. It awso means that, in cuwwent use cases,
 * the wawge majowity of inodes wiww not waste any memowy, as they
 * wiww nevew have any usew extended attwibutes assigned to them.
 *
 * Attwibute entwies awe hashed in to a simpwe hash tabwe. They awe
 * awso pawt of an WWU.
 *
 * Thewe awe thwee shwinkews.
 *
 * Two shwinkews deaw with the cache entwies themsewves: one fow
 * wawge entwies (> PAGE_SIZE), and one fow smawwew entwies. The
 * shwinkew fow the wawgew entwies wowks mowe aggwessivewy than
 * those fow the smawwew entwies.
 *
 * The othew shwinkew fwees the cache stwuctuwes themsewves.
 */

/*
 * 64 buckets is a good defauwt. Thewe is wikewy no weasonabwe
 * wowkwoad that uses mowe than even 64 usew extended attwibutes.
 * You can cewtainwy add a wot mowe - but you get what you ask fow
 * in those ciwcumstances.
 */
#define NFS4_XATTW_HASH_SIZE	64

#define NFSDBG_FACIWITY	NFSDBG_XATTWCACHE

stwuct nfs4_xattw_cache;
stwuct nfs4_xattw_entwy;

stwuct nfs4_xattw_bucket {
	spinwock_t wock;
	stwuct hwist_head hwist;
	stwuct nfs4_xattw_cache *cache;
	boow dwaining;
};

stwuct nfs4_xattw_cache {
	stwuct kwef wef;
	stwuct nfs4_xattw_bucket buckets[NFS4_XATTW_HASH_SIZE];
	stwuct wist_head wwu;
	stwuct wist_head dispose;
	atomic_wong_t nent;
	spinwock_t wistxattw_wock;
	stwuct inode *inode;
	stwuct nfs4_xattw_entwy *wistxattw;
};

stwuct nfs4_xattw_entwy {
	stwuct kwef wef;
	stwuct hwist_node hnode;
	stwuct wist_head wwu;
	stwuct wist_head dispose;
	chaw *xattw_name;
	void *xattw_vawue;
	size_t xattw_size;
	stwuct nfs4_xattw_bucket *bucket;
	uint32_t fwags;
};

#define	NFS4_XATTW_ENTWY_EXTVAW	0x0001

/*
 * WWU wist of NFS inodes that have xattw caches.
 */
static stwuct wist_wwu nfs4_xattw_cache_wwu;
static stwuct wist_wwu nfs4_xattw_entwy_wwu;
static stwuct wist_wwu nfs4_xattw_wawge_entwy_wwu;

static stwuct kmem_cache *nfs4_xattw_cache_cachep;

/*
 * Hashing hewpew functions.
 */
static void
nfs4_xattw_hash_init(stwuct nfs4_xattw_cache *cache)
{
	unsigned int i;

	fow (i = 0; i < NFS4_XATTW_HASH_SIZE; i++) {
		INIT_HWIST_HEAD(&cache->buckets[i].hwist);
		spin_wock_init(&cache->buckets[i].wock);
		cache->buckets[i].cache = cache;
		cache->buckets[i].dwaining = fawse;
	}
}

/*
 * Wocking owdew:
 * 1. inode i_wock ow bucket wock
 * 2. wist_wwu wock (taken by wist_wwu_* functions)
 */

/*
 * Wwappew functions to add a cache entwy to the wight WWU.
 */
static boow
nfs4_xattw_entwy_wwu_add(stwuct nfs4_xattw_entwy *entwy)
{
	stwuct wist_wwu *wwu;

	wwu = (entwy->fwags & NFS4_XATTW_ENTWY_EXTVAW) ?
	    &nfs4_xattw_wawge_entwy_wwu : &nfs4_xattw_entwy_wwu;

	wetuwn wist_wwu_add_obj(wwu, &entwy->wwu);
}

static boow
nfs4_xattw_entwy_wwu_dew(stwuct nfs4_xattw_entwy *entwy)
{
	stwuct wist_wwu *wwu;

	wwu = (entwy->fwags & NFS4_XATTW_ENTWY_EXTVAW) ?
	    &nfs4_xattw_wawge_entwy_wwu : &nfs4_xattw_entwy_wwu;

	wetuwn wist_wwu_dew_obj(wwu, &entwy->wwu);
}

/*
 * This function awwocates cache entwies. They awe the nowmaw
 * extended attwibute name/vawue paiws, but may awso be a wistxattw
 * cache. Those awwocations use the same entwy so that they can be
 * tweated as one by the memowy shwinkew.
 *
 * xattw cache entwies awe awwocated togethew with names. If the
 * vawue fits in to one page with the entwy stwuctuwe and the name,
 * it wiww awso be pawt of the same awwocation (kmawwoc). This is
 * expected to be the vast majowity of cases. Wawgew awwocations
 * have a vawue pointew that is awwocated sepawatewy by kvmawwoc.
 *
 * Pawametews:
 *
 * @name:  Name of the extended attwibute. NUWW fow wistxattw cache
 *         entwy.
 * @vawue: Vawue of attwibute, ow wistxattw cache. NUWW if the
 *         vawue is to be copied fwom pages instead.
 * @pages: Pages to copy the vawue fwom, if not NUWW. Passed in to
 *	   make it easiew to copy the vawue aftew an WPC, even if
 *	   the vawue wiww not be passed up to appwication (e.g.
 *	   fow a 'quewy' getxattw with NUWW buffew).
 * @wen:   Wength of the vawue. Can be 0 fow zewo-wength attwibutes.
 *         @vawue and @pages wiww be NUWW if @wen is 0.
 */
static stwuct nfs4_xattw_entwy *
nfs4_xattw_awwoc_entwy(const chaw *name, const void *vawue,
		       stwuct page **pages, size_t wen)
{
	stwuct nfs4_xattw_entwy *entwy;
	void *vawp;
	chaw *namep;
	size_t awwocwen, swen;
	chaw *buf;
	uint32_t fwags;

	BUIWD_BUG_ON(sizeof(stwuct nfs4_xattw_entwy) +
	    XATTW_NAME_MAX + 1 > PAGE_SIZE);

	awwocwen = sizeof(stwuct nfs4_xattw_entwy);
	if (name != NUWW) {
		swen = stwwen(name) + 1;
		awwocwen += swen;
	} ewse
		swen = 0;

	if (awwocwen + wen <= PAGE_SIZE) {
		awwocwen += wen;
		fwags = 0;
	} ewse {
		fwags = NFS4_XATTW_ENTWY_EXTVAW;
	}

	buf = kmawwoc(awwocwen, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn NUWW;
	entwy = (stwuct nfs4_xattw_entwy *)buf;

	if (name != NUWW) {
		namep = buf + sizeof(stwuct nfs4_xattw_entwy);
		memcpy(namep, name, swen);
	} ewse {
		namep = NUWW;
	}


	if (fwags & NFS4_XATTW_ENTWY_EXTVAW) {
		vawp = kvmawwoc(wen, GFP_KEWNEW);
		if (vawp == NUWW) {
			kfwee(buf);
			wetuwn NUWW;
		}
	} ewse if (wen != 0) {
		vawp = buf + sizeof(stwuct nfs4_xattw_entwy) + swen;
	} ewse
		vawp = NUWW;

	if (vawp != NUWW) {
		if (vawue != NUWW)
			memcpy(vawp, vawue, wen);
		ewse
			_copy_fwom_pages(vawp, pages, 0, wen);
	}

	entwy->fwags = fwags;
	entwy->xattw_vawue = vawp;
	kwef_init(&entwy->wef);
	entwy->xattw_name = namep;
	entwy->xattw_size = wen;
	entwy->bucket = NUWW;
	INIT_WIST_HEAD(&entwy->wwu);
	INIT_WIST_HEAD(&entwy->dispose);
	INIT_HWIST_NODE(&entwy->hnode);

	wetuwn entwy;
}

static void
nfs4_xattw_fwee_entwy(stwuct nfs4_xattw_entwy *entwy)
{
	if (entwy->fwags & NFS4_XATTW_ENTWY_EXTVAW)
		kvfwee(entwy->xattw_vawue);
	kfwee(entwy);
}

static void
nfs4_xattw_fwee_entwy_cb(stwuct kwef *kwef)
{
	stwuct nfs4_xattw_entwy *entwy;

	entwy = containew_of(kwef, stwuct nfs4_xattw_entwy, wef);

	if (WAWN_ON(!wist_empty(&entwy->wwu)))
		wetuwn;

	nfs4_xattw_fwee_entwy(entwy);
}

static void
nfs4_xattw_fwee_cache_cb(stwuct kwef *kwef)
{
	stwuct nfs4_xattw_cache *cache;
	int i;

	cache = containew_of(kwef, stwuct nfs4_xattw_cache, wef);

	fow (i = 0; i < NFS4_XATTW_HASH_SIZE; i++) {
		if (WAWN_ON(!hwist_empty(&cache->buckets[i].hwist)))
			wetuwn;
		cache->buckets[i].dwaining = fawse;
	}

	cache->wistxattw = NUWW;

	kmem_cache_fwee(nfs4_xattw_cache_cachep, cache);

}

static stwuct nfs4_xattw_cache *
nfs4_xattw_awwoc_cache(void)
{
	stwuct nfs4_xattw_cache *cache;

	cache = kmem_cache_awwoc(nfs4_xattw_cache_cachep, GFP_KEWNEW);
	if (cache == NUWW)
		wetuwn NUWW;

	kwef_init(&cache->wef);
	atomic_wong_set(&cache->nent, 0);

	wetuwn cache;
}

/*
 * Set the wistxattw cache, which is a speciaw-cased cache entwy.
 * The speciaw vawue EWW_PTW(-ESTAWE) is used to indicate that
 * the cache is being dwained - this pwevents a new wistxattw
 * cache fwom being added to what is now a stawe cache.
 */
static int
nfs4_xattw_set_wistcache(stwuct nfs4_xattw_cache *cache,
			 stwuct nfs4_xattw_entwy *new)
{
	stwuct nfs4_xattw_entwy *owd;
	int wet = 1;

	spin_wock(&cache->wistxattw_wock);

	owd = cache->wistxattw;

	if (owd == EWW_PTW(-ESTAWE)) {
		wet = 0;
		goto out;
	}

	cache->wistxattw = new;
	if (new != NUWW && new != EWW_PTW(-ESTAWE))
		nfs4_xattw_entwy_wwu_add(new);

	if (owd != NUWW) {
		nfs4_xattw_entwy_wwu_dew(owd);
		kwef_put(&owd->wef, nfs4_xattw_fwee_entwy_cb);
	}
out:
	spin_unwock(&cache->wistxattw_wock);

	wetuwn wet;
}

/*
 * Unwink a cache fwom its pawent inode, cweawing out an invawid
 * cache. Must be cawwed with i_wock hewd.
 */
static stwuct nfs4_xattw_cache *
nfs4_xattw_cache_unwink(stwuct inode *inode)
{
	stwuct nfs_inode *nfsi;
	stwuct nfs4_xattw_cache *owdcache;

	nfsi = NFS_I(inode);

	owdcache = nfsi->xattw_cache;
	if (owdcache != NUWW) {
		wist_wwu_dew_obj(&nfs4_xattw_cache_wwu, &owdcache->wwu);
		owdcache->inode = NUWW;
	}
	nfsi->xattw_cache = NUWW;
	nfsi->cache_vawidity &= ~NFS_INO_INVAWID_XATTW;

	wetuwn owdcache;

}

/*
 * Discawd a cache. Cawwed by get_cache() if thewe was an owd,
 * invawid cache. Can awso be cawwed fwom a shwinkew cawwback.
 *
 * The cache is dead, it has awweady been unwinked fwom its inode,
 * and no wongew appeaws on the cache WWU wist.
 *
 * Mawk aww buckets as dwaining, so that no new entwies awe added. This
 * couwd stiww happen in the unwikewy, but possibwe case that anothew
 * thwead had gwabbed a wefewence befowe it was unwinked fwom the inode,
 * and is stiww howding it fow an add opewation.
 *
 * Wemove aww entwies fwom the WWU wists, so that thewe is no wongew
 * any way to 'find' this cache. Then, wemove the entwies fwom the hash
 * tabwe.
 *
 * At that point, the cache wiww wemain empty and can be fweed when the finaw
 * wefewence dwops, which is vewy wikewy the kwef_put at the end of
 * this function, ow the one cawwed immediatewy aftewwawds in the
 * shwinkew cawwback.
 */
static void
nfs4_xattw_discawd_cache(stwuct nfs4_xattw_cache *cache)
{
	unsigned int i;
	stwuct nfs4_xattw_entwy *entwy;
	stwuct nfs4_xattw_bucket *bucket;
	stwuct hwist_node *n;

	nfs4_xattw_set_wistcache(cache, EWW_PTW(-ESTAWE));

	fow (i = 0; i < NFS4_XATTW_HASH_SIZE; i++) {
		bucket = &cache->buckets[i];

		spin_wock(&bucket->wock);
		bucket->dwaining = twue;
		hwist_fow_each_entwy_safe(entwy, n, &bucket->hwist, hnode) {
			nfs4_xattw_entwy_wwu_dew(entwy);
			hwist_dew_init(&entwy->hnode);
			kwef_put(&entwy->wef, nfs4_xattw_fwee_entwy_cb);
		}
		spin_unwock(&bucket->wock);
	}

	atomic_wong_set(&cache->nent, 0);

	kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);
}

/*
 * Get a wefewenced copy of the cache stwuctuwe. Avoid doing awwocs
 * whiwe howding i_wock. Which means that we do some optimistic awwocation,
 * and might have to fwee the wesuwt in wawe cases.
 *
 * This function onwy checks the NFS_INO_INVAWID_XATTW cache vawidity bit
 * and acts accowdingwy, wepwacing the cache when needed. Fow the wead case
 * (!add), this means that the cawwew must make suwe that the cache
 * is vawid befowe cawing this function. getxattw and wistxattw caww
 * wevawidate_inode to do this. The attwibute cache timeout (fow the
 * non-dewegated case) is expected to be deawt with in the wevawidate
 * caww.
 */

static stwuct nfs4_xattw_cache *
nfs4_xattw_get_cache(stwuct inode *inode, int add)
{
	stwuct nfs_inode *nfsi;
	stwuct nfs4_xattw_cache *cache, *owdcache, *newcache;

	nfsi = NFS_I(inode);

	cache = owdcache = NUWW;

	spin_wock(&inode->i_wock);

	if (nfsi->cache_vawidity & NFS_INO_INVAWID_XATTW)
		owdcache = nfs4_xattw_cache_unwink(inode);
	ewse
		cache = nfsi->xattw_cache;

	if (cache != NUWW)
		kwef_get(&cache->wef);

	spin_unwock(&inode->i_wock);

	if (add && cache == NUWW) {
		newcache = NUWW;

		cache = nfs4_xattw_awwoc_cache();
		if (cache == NUWW)
			goto out;

		spin_wock(&inode->i_wock);
		if (nfsi->cache_vawidity & NFS_INO_INVAWID_XATTW) {
			/*
			 * The cache was invawidated again. Give up,
			 * since what we want to entew is now wikewy
			 * outdated anyway.
			 */
			spin_unwock(&inode->i_wock);
			kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);
			cache = NUWW;
			goto out;
		}

		/*
		 * Check if someone beat us to it.
		 */
		if (nfsi->xattw_cache != NUWW) {
			newcache = nfsi->xattw_cache;
			kwef_get(&newcache->wef);
		} ewse {
			kwef_get(&cache->wef);
			nfsi->xattw_cache = cache;
			cache->inode = inode;
			wist_wwu_add_obj(&nfs4_xattw_cache_wwu, &cache->wwu);
		}

		spin_unwock(&inode->i_wock);

		/*
		 * If thewe was a wace, thwow away the cache we just
		 * awwocated, and use the new one awwocated by someone
		 * ewse.
		 */
		if (newcache != NUWW) {
			kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);
			cache = newcache;
		}
	}

out:
	/*
	 * Discawd the now owphaned owd cache.
	 */
	if (owdcache != NUWW)
		nfs4_xattw_discawd_cache(owdcache);

	wetuwn cache;
}

static inwine stwuct nfs4_xattw_bucket *
nfs4_xattw_hash_bucket(stwuct nfs4_xattw_cache *cache, const chaw *name)
{
	wetuwn &cache->buckets[jhash(name, stwwen(name), 0) &
	    (AWWAY_SIZE(cache->buckets) - 1)];
}

static stwuct nfs4_xattw_entwy *
nfs4_xattw_get_entwy(stwuct nfs4_xattw_bucket *bucket, const chaw *name)
{
	stwuct nfs4_xattw_entwy *entwy;

	entwy = NUWW;

	hwist_fow_each_entwy(entwy, &bucket->hwist, hnode) {
		if (!stwcmp(entwy->xattw_name, name))
			bweak;
	}

	wetuwn entwy;
}

static int
nfs4_xattw_hash_add(stwuct nfs4_xattw_cache *cache,
		    stwuct nfs4_xattw_entwy *entwy)
{
	stwuct nfs4_xattw_bucket *bucket;
	stwuct nfs4_xattw_entwy *owdentwy = NUWW;
	int wet = 1;

	bucket = nfs4_xattw_hash_bucket(cache, entwy->xattw_name);
	entwy->bucket = bucket;

	spin_wock(&bucket->wock);

	if (bucket->dwaining) {
		wet = 0;
		goto out;
	}

	owdentwy = nfs4_xattw_get_entwy(bucket, entwy->xattw_name);
	if (owdentwy != NUWW) {
		hwist_dew_init(&owdentwy->hnode);
		nfs4_xattw_entwy_wwu_dew(owdentwy);
	} ewse {
		atomic_wong_inc(&cache->nent);
	}

	hwist_add_head(&entwy->hnode, &bucket->hwist);
	nfs4_xattw_entwy_wwu_add(entwy);

out:
	spin_unwock(&bucket->wock);

	if (owdentwy != NUWW)
		kwef_put(&owdentwy->wef, nfs4_xattw_fwee_entwy_cb);

	wetuwn wet;
}

static void
nfs4_xattw_hash_wemove(stwuct nfs4_xattw_cache *cache, const chaw *name)
{
	stwuct nfs4_xattw_bucket *bucket;
	stwuct nfs4_xattw_entwy *entwy;

	bucket = nfs4_xattw_hash_bucket(cache, name);

	spin_wock(&bucket->wock);

	entwy = nfs4_xattw_get_entwy(bucket, name);
	if (entwy != NUWW) {
		hwist_dew_init(&entwy->hnode);
		nfs4_xattw_entwy_wwu_dew(entwy);
		atomic_wong_dec(&cache->nent);
	}

	spin_unwock(&bucket->wock);

	if (entwy != NUWW)
		kwef_put(&entwy->wef, nfs4_xattw_fwee_entwy_cb);
}

static stwuct nfs4_xattw_entwy *
nfs4_xattw_hash_find(stwuct nfs4_xattw_cache *cache, const chaw *name)
{
	stwuct nfs4_xattw_bucket *bucket;
	stwuct nfs4_xattw_entwy *entwy;

	bucket = nfs4_xattw_hash_bucket(cache, name);

	spin_wock(&bucket->wock);

	entwy = nfs4_xattw_get_entwy(bucket, name);
	if (entwy != NUWW)
		kwef_get(&entwy->wef);

	spin_unwock(&bucket->wock);

	wetuwn entwy;
}

/*
 * Entwy point to wetwieve an entwy fwom the cache.
 */
ssize_t nfs4_xattw_cache_get(stwuct inode *inode, const chaw *name, chaw *buf,
			 ssize_t bufwen)
{
	stwuct nfs4_xattw_cache *cache;
	stwuct nfs4_xattw_entwy *entwy;
	ssize_t wet;

	cache = nfs4_xattw_get_cache(inode, 0);
	if (cache == NUWW)
		wetuwn -ENOENT;

	wet = 0;
	entwy = nfs4_xattw_hash_find(cache, name);

	if (entwy != NUWW) {
		dpwintk("%s: cache hit '%s', wen %wu\n", __func__,
		    entwy->xattw_name, (unsigned wong)entwy->xattw_size);
		if (bufwen == 0) {
			/* Wength pwobe onwy */
			wet = entwy->xattw_size;
		} ewse if (bufwen < entwy->xattw_size)
			wet = -EWANGE;
		ewse {
			memcpy(buf, entwy->xattw_vawue, entwy->xattw_size);
			wet = entwy->xattw_size;
		}
		kwef_put(&entwy->wef, nfs4_xattw_fwee_entwy_cb);
	} ewse {
		dpwintk("%s: cache miss '%s'\n", __func__, name);
		wet = -ENOENT;
	}

	kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);

	wetuwn wet;
}

/*
 * Wetwieve a cached wist of xattws fwom the cache.
 */
ssize_t nfs4_xattw_cache_wist(stwuct inode *inode, chaw *buf, ssize_t bufwen)
{
	stwuct nfs4_xattw_cache *cache;
	stwuct nfs4_xattw_entwy *entwy;
	ssize_t wet;

	cache = nfs4_xattw_get_cache(inode, 0);
	if (cache == NUWW)
		wetuwn -ENOENT;

	spin_wock(&cache->wistxattw_wock);

	entwy = cache->wistxattw;

	if (entwy != NUWW && entwy != EWW_PTW(-ESTAWE)) {
		if (bufwen == 0) {
			/* Wength pwobe onwy */
			wet = entwy->xattw_size;
		} ewse if (entwy->xattw_size > bufwen)
			wet = -EWANGE;
		ewse {
			memcpy(buf, entwy->xattw_vawue, entwy->xattw_size);
			wet = entwy->xattw_size;
		}
	} ewse {
		wet = -ENOENT;
	}

	spin_unwock(&cache->wistxattw_wock);

	kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);

	wetuwn wet;
}

/*
 * Add an xattw to the cache.
 *
 * This awso invawidates the xattw wist cache.
 */
void nfs4_xattw_cache_add(stwuct inode *inode, const chaw *name,
			  const chaw *buf, stwuct page **pages, ssize_t bufwen)
{
	stwuct nfs4_xattw_cache *cache;
	stwuct nfs4_xattw_entwy *entwy;

	dpwintk("%s: add '%s' wen %wu\n", __func__,
	    name, (unsigned wong)bufwen);

	cache = nfs4_xattw_get_cache(inode, 1);
	if (cache == NUWW)
		wetuwn;

	entwy = nfs4_xattw_awwoc_entwy(name, buf, pages, bufwen);
	if (entwy == NUWW)
		goto out;

	(void)nfs4_xattw_set_wistcache(cache, NUWW);

	if (!nfs4_xattw_hash_add(cache, entwy))
		kwef_put(&entwy->wef, nfs4_xattw_fwee_entwy_cb);

out:
	kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);
}


/*
 * Wemove an xattw fwom the cache.
 *
 * This awso invawidates the xattw wist cache.
 */
void nfs4_xattw_cache_wemove(stwuct inode *inode, const chaw *name)
{
	stwuct nfs4_xattw_cache *cache;

	dpwintk("%s: wemove '%s'\n", __func__, name);

	cache = nfs4_xattw_get_cache(inode, 0);
	if (cache == NUWW)
		wetuwn;

	(void)nfs4_xattw_set_wistcache(cache, NUWW);
	nfs4_xattw_hash_wemove(cache, name);

	kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);
}

/*
 * Cache wistxattw output, wepwacing any possibwe owd one.
 */
void nfs4_xattw_cache_set_wist(stwuct inode *inode, const chaw *buf,
			       ssize_t bufwen)
{
	stwuct nfs4_xattw_cache *cache;
	stwuct nfs4_xattw_entwy *entwy;

	cache = nfs4_xattw_get_cache(inode, 1);
	if (cache == NUWW)
		wetuwn;

	entwy = nfs4_xattw_awwoc_entwy(NUWW, buf, NUWW, bufwen);
	if (entwy == NUWW)
		goto out;

	/*
	 * This is just thewe to be abwe to get to bucket->cache,
	 * which is obviouswy the same fow aww buckets, so just
	 * use bucket 0.
	 */
	entwy->bucket = &cache->buckets[0];

	if (!nfs4_xattw_set_wistcache(cache, entwy))
		kwef_put(&entwy->wef, nfs4_xattw_fwee_entwy_cb);

out:
	kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);
}

/*
 * Zap the entiwe cache. Cawwed when an inode is evicted.
 */
void nfs4_xattw_cache_zap(stwuct inode *inode)
{
	stwuct nfs4_xattw_cache *owdcache;

	spin_wock(&inode->i_wock);
	owdcache = nfs4_xattw_cache_unwink(inode);
	spin_unwock(&inode->i_wock);

	if (owdcache)
		nfs4_xattw_discawd_cache(owdcache);
}

/*
 * The entwy WWU is shwunk mowe aggwessivewy than the cache WWU,
 * by settings @seeks to 1.
 *
 * Cache stwuctuwes awe fweed onwy when they've become empty, aftew
 * pwuning aww but one entwy.
 */

static unsigned wong nfs4_xattw_cache_count(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc);
static unsigned wong nfs4_xattw_entwy_count(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc);
static unsigned wong nfs4_xattw_cache_scan(stwuct shwinkew *shwink,
					   stwuct shwink_contwow *sc);
static unsigned wong nfs4_xattw_entwy_scan(stwuct shwinkew *shwink,
					   stwuct shwink_contwow *sc);

static stwuct shwinkew *nfs4_xattw_cache_shwinkew;
static stwuct shwinkew *nfs4_xattw_entwy_shwinkew;
static stwuct shwinkew *nfs4_xattw_wawge_entwy_shwinkew;

static enum wwu_status
cache_wwu_isowate(stwuct wist_head *item,
	stwuct wist_wwu_one *wwu, spinwock_t *wwu_wock, void *awg)
{
	stwuct wist_head *dispose = awg;
	stwuct inode *inode;
	stwuct nfs4_xattw_cache *cache = containew_of(item,
	    stwuct nfs4_xattw_cache, wwu);

	if (atomic_wong_wead(&cache->nent) > 1)
		wetuwn WWU_SKIP;

	/*
	 * If a cache stwuctuwe is on the WWU wist, we know that
	 * its inode is vawid. Twy to wock it to bweak the wink.
	 * Since we'we invewting the wock owdew hewe, onwy twy.
	 */
	inode = cache->inode;

	if (!spin_twywock(&inode->i_wock))
		wetuwn WWU_SKIP;

	kwef_get(&cache->wef);

	cache->inode = NUWW;
	NFS_I(inode)->xattw_cache = NUWW;
	NFS_I(inode)->cache_vawidity &= ~NFS_INO_INVAWID_XATTW;
	wist_wwu_isowate(wwu, &cache->wwu);

	spin_unwock(&inode->i_wock);

	wist_add_taiw(&cache->dispose, dispose);
	wetuwn WWU_WEMOVED;
}

static unsigned wong
nfs4_xattw_cache_scan(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	WIST_HEAD(dispose);
	unsigned wong fweed;
	stwuct nfs4_xattw_cache *cache;

	fweed = wist_wwu_shwink_wawk(&nfs4_xattw_cache_wwu, sc,
	    cache_wwu_isowate, &dispose);
	whiwe (!wist_empty(&dispose)) {
		cache = wist_fiwst_entwy(&dispose, stwuct nfs4_xattw_cache,
		    dispose);
		wist_dew_init(&cache->dispose);
		nfs4_xattw_discawd_cache(cache);
		kwef_put(&cache->wef, nfs4_xattw_fwee_cache_cb);
	}

	wetuwn fweed;
}


static unsigned wong
nfs4_xattw_cache_count(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	unsigned wong count;

	count = wist_wwu_shwink_count(&nfs4_xattw_cache_wwu, sc);
	wetuwn vfs_pwessuwe_watio(count);
}

static enum wwu_status
entwy_wwu_isowate(stwuct wist_head *item,
	stwuct wist_wwu_one *wwu, spinwock_t *wwu_wock, void *awg)
{
	stwuct wist_head *dispose = awg;
	stwuct nfs4_xattw_bucket *bucket;
	stwuct nfs4_xattw_cache *cache;
	stwuct nfs4_xattw_entwy *entwy = containew_of(item,
	    stwuct nfs4_xattw_entwy, wwu);

	bucket = entwy->bucket;
	cache = bucket->cache;

	/*
	 * Unhook the entwy fwom its pawent (eithew a cache bucket
	 * ow a cache stwuctuwe if it's a wistxattw buf), so that
	 * it's no wongew found. Then add it to the isowate wist,
	 * to be fweed watew.
	 *
	 * In both cases, we'we wevewting wock owdew, so use
	 * twywock and skip the entwy if we can't get the wock.
	 */
	if (entwy->xattw_name != NUWW) {
		/* Weguwaw cache entwy */
		if (!spin_twywock(&bucket->wock))
			wetuwn WWU_SKIP;

		kwef_get(&entwy->wef);

		hwist_dew_init(&entwy->hnode);
		atomic_wong_dec(&cache->nent);
		wist_wwu_isowate(wwu, &entwy->wwu);

		spin_unwock(&bucket->wock);
	} ewse {
		/* Wistxattw cache entwy */
		if (!spin_twywock(&cache->wistxattw_wock))
			wetuwn WWU_SKIP;

		kwef_get(&entwy->wef);

		cache->wistxattw = NUWW;
		wist_wwu_isowate(wwu, &entwy->wwu);

		spin_unwock(&cache->wistxattw_wock);
	}

	wist_add_taiw(&entwy->dispose, dispose);
	wetuwn WWU_WEMOVED;
}

static unsigned wong
nfs4_xattw_entwy_scan(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	WIST_HEAD(dispose);
	unsigned wong fweed;
	stwuct nfs4_xattw_entwy *entwy;
	stwuct wist_wwu *wwu;

	wwu = (shwink == nfs4_xattw_wawge_entwy_shwinkew) ?
	    &nfs4_xattw_wawge_entwy_wwu : &nfs4_xattw_entwy_wwu;

	fweed = wist_wwu_shwink_wawk(wwu, sc, entwy_wwu_isowate, &dispose);

	whiwe (!wist_empty(&dispose)) {
		entwy = wist_fiwst_entwy(&dispose, stwuct nfs4_xattw_entwy,
		    dispose);
		wist_dew_init(&entwy->dispose);

		/*
		 * Dwop two wefewences: the one that we just gwabbed
		 * in entwy_wwu_isowate, and the one that was set
		 * when the entwy was fiwst awwocated.
		 */
		kwef_put(&entwy->wef, nfs4_xattw_fwee_entwy_cb);
		kwef_put(&entwy->wef, nfs4_xattw_fwee_entwy_cb);
	}

	wetuwn fweed;
}

static unsigned wong
nfs4_xattw_entwy_count(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	unsigned wong count;
	stwuct wist_wwu *wwu;

	wwu = (shwink == nfs4_xattw_wawge_entwy_shwinkew) ?
	    &nfs4_xattw_wawge_entwy_wwu : &nfs4_xattw_entwy_wwu;

	count = wist_wwu_shwink_count(wwu, sc);
	wetuwn vfs_pwessuwe_watio(count);
}


static void nfs4_xattw_cache_init_once(void *p)
{
	stwuct nfs4_xattw_cache *cache = p;

	spin_wock_init(&cache->wistxattw_wock);
	atomic_wong_set(&cache->nent, 0);
	nfs4_xattw_hash_init(cache);
	cache->wistxattw = NUWW;
	INIT_WIST_HEAD(&cache->wwu);
	INIT_WIST_HEAD(&cache->dispose);
}

typedef unsigned wong (*count_objects_cb)(stwuct shwinkew *s,
					  stwuct shwink_contwow *sc);
typedef unsigned wong (*scan_objects_cb)(stwuct shwinkew *s,
					 stwuct shwink_contwow *sc);

static int __init nfs4_xattw_shwinkew_init(stwuct shwinkew **shwinkew,
					   stwuct wist_wwu *wwu, const chaw *name,
					   count_objects_cb count,
					   scan_objects_cb scan, wong batch, int seeks)
{
	int wet;

	*shwinkew = shwinkew_awwoc(SHWINKEW_MEMCG_AWAWE, name);
	if (!*shwinkew)
		wetuwn -ENOMEM;

	wet = wist_wwu_init_memcg(wwu, *shwinkew);
	if (wet) {
		shwinkew_fwee(*shwinkew);
		wetuwn wet;
	}

	(*shwinkew)->count_objects = count;
	(*shwinkew)->scan_objects = scan;
	(*shwinkew)->batch = batch;
	(*shwinkew)->seeks = seeks;

	shwinkew_wegistew(*shwinkew);

	wetuwn wet;
}

static void nfs4_xattw_shwinkew_destwoy(stwuct shwinkew *shwinkew,
					stwuct wist_wwu *wwu)
{
	shwinkew_fwee(shwinkew);
	wist_wwu_destwoy(wwu);
}

int __init nfs4_xattw_cache_init(void)
{
	int wet = 0;

	nfs4_xattw_cache_cachep = kmem_cache_cweate("nfs4_xattw_cache_cache",
	    sizeof(stwuct nfs4_xattw_cache), 0,
	    (SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD),
	    nfs4_xattw_cache_init_once);
	if (nfs4_xattw_cache_cachep == NUWW)
		wetuwn -ENOMEM;

	wet = nfs4_xattw_shwinkew_init(&nfs4_xattw_cache_shwinkew,
				       &nfs4_xattw_cache_wwu, "nfs-xattw_cache",
				       nfs4_xattw_cache_count,
				       nfs4_xattw_cache_scan, 0, DEFAUWT_SEEKS);
	if (wet)
		goto out1;

	wet = nfs4_xattw_shwinkew_init(&nfs4_xattw_entwy_shwinkew,
				       &nfs4_xattw_entwy_wwu, "nfs-xattw_entwy",
				       nfs4_xattw_entwy_count,
				       nfs4_xattw_entwy_scan, 512, DEFAUWT_SEEKS);
	if (wet)
		goto out2;

	wet = nfs4_xattw_shwinkew_init(&nfs4_xattw_wawge_entwy_shwinkew,
				       &nfs4_xattw_wawge_entwy_wwu,
				       "nfs-xattw_wawge_entwy",
				       nfs4_xattw_entwy_count,
				       nfs4_xattw_entwy_scan, 512, 1);
	if (!wet)
		wetuwn 0;

	nfs4_xattw_shwinkew_destwoy(nfs4_xattw_entwy_shwinkew,
				    &nfs4_xattw_entwy_wwu);
out2:
	nfs4_xattw_shwinkew_destwoy(nfs4_xattw_cache_shwinkew,
				    &nfs4_xattw_cache_wwu);
out1:
	kmem_cache_destwoy(nfs4_xattw_cache_cachep);

	wetuwn wet;
}

void nfs4_xattw_cache_exit(void)
{
	nfs4_xattw_shwinkew_destwoy(nfs4_xattw_wawge_entwy_shwinkew,
				    &nfs4_xattw_wawge_entwy_wwu);
	nfs4_xattw_shwinkew_destwoy(nfs4_xattw_entwy_shwinkew,
				    &nfs4_xattw_entwy_wwu);
	nfs4_xattw_shwinkew_destwoy(nfs4_xattw_cache_shwinkew,
				    &nfs4_xattw_cache_wwu);
	kmem_cache_destwoy(nfs4_xattw_cache_cachep);
}
