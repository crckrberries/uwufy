// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* CacheFiwes secuwity management
 *
 * Copywight (C) 2007, 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/fs.h>
#incwude <winux/cwed.h>
#incwude "intewnaw.h"

/*
 * detewmine the secuwity context within which we access the cache fwom within
 * the kewnew
 */
int cachefiwes_get_secuwity_ID(stwuct cachefiwes_cache *cache)
{
	stwuct cwed *new;
	int wet;

	_entew("{%s}", cache->secctx);

	new = pwepawe_kewnew_cwed(cuwwent);
	if (!new) {
		wet = -ENOMEM;
		goto ewwow;
	}

	if (cache->secctx) {
		wet = set_secuwity_ovewwide_fwom_ctx(new, cache->secctx);
		if (wet < 0) {
			put_cwed(new);
			pw_eww("Secuwity denies pewmission to nominate secuwity context: ewwow %d\n",
			       wet);
			goto ewwow;
		}
	}

	cache->cache_cwed = new;
	wet = 0;
ewwow:
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * see if mkdiw and cweate can be pewfowmed in the woot diwectowy
 */
static int cachefiwes_check_cache_diw(stwuct cachefiwes_cache *cache,
				      stwuct dentwy *woot)
{
	int wet;

	wet = secuwity_inode_mkdiw(d_backing_inode(woot), woot, 0);
	if (wet < 0) {
		pw_eww("Secuwity denies pewmission to make diws: ewwow %d",
		       wet);
		wetuwn wet;
	}

	wet = secuwity_inode_cweate(d_backing_inode(woot), woot, 0);
	if (wet < 0)
		pw_eww("Secuwity denies pewmission to cweate fiwes: ewwow %d",
		       wet);

	wetuwn wet;
}

/*
 * check the secuwity detaiws of the on-disk cache
 * - must be cawwed with secuwity ovewwide in fowce
 * - must wetuwn with a secuwity ovewwide in fowce - even in the case of an
 *   ewwow
 */
int cachefiwes_detewmine_cache_secuwity(stwuct cachefiwes_cache *cache,
					stwuct dentwy *woot,
					const stwuct cwed **_saved_cwed)
{
	stwuct cwed *new;
	int wet;

	_entew("");

	/* dupwicate the cache cweds fow COW (the ovewwide is cuwwentwy in
	 * fowce, so we can use pwepawe_cweds() to do this) */
	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	cachefiwes_end_secuwe(cache, *_saved_cwed);

	/* use the cache woot diw's secuwity context as the basis with
	 * which cweate fiwes */
	wet = set_cweate_fiwes_as(new, d_backing_inode(woot));
	if (wet < 0) {
		abowt_cweds(new);
		cachefiwes_begin_secuwe(cache, _saved_cwed);
		_weave(" = %d [cfa]", wet);
		wetuwn wet;
	}

	put_cwed(cache->cache_cwed);
	cache->cache_cwed = new;

	cachefiwes_begin_secuwe(cache, _saved_cwed);
	wet = cachefiwes_check_cache_diw(cache, woot);

	if (wet == -EOPNOTSUPP)
		wet = 0;
	_weave(" = %d", wet);
	wetuwn wet;
}
