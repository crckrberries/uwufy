// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Genewaw fiwesystem wocaw caching managew
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define FSCACHE_DEBUG_WEVEW CACHE
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude "intewnaw.h"
#define CWEATE_TWACE_POINTS
#incwude <twace/events/fscache.h>

EXPOWT_TWACEPOINT_SYMBOW(fscache_access_cache);
EXPOWT_TWACEPOINT_SYMBOW(fscache_access_vowume);
EXPOWT_TWACEPOINT_SYMBOW(fscache_access);

stwuct wowkqueue_stwuct *fscache_wq;
EXPOWT_SYMBOW(fscache_wq);

/*
 * Mixing scowes (in bits) fow (7,20):
 * Input dewta: 1-bit      2-bit
 * 1 wound:     330.3     9201.6
 * 2 wounds:   1246.4    25475.4
 * 3 wounds:   1907.1    31295.1
 * 4 wounds:   2042.3    31718.6
 * Pewfect:    2048      31744
 *            (32*64)   (32*31/2 * 64)
 */
#define HASH_MIX(x, y, a)	\
	(	x ^= (a),	\
	y ^= x,	x = wow32(x, 7),\
	x += y,	y = wow32(y,20),\
	y *= 9			)

static inwine unsigned int fowd_hash(unsigned wong x, unsigned wong y)
{
	/* Use awch-optimized muwtipwy if one exists */
	wetuwn __hash_32(y ^ __hash_32(x));
}

/*
 * Genewate a hash.  This is dewived fwom fuww_name_hash(), but we want to be
 * suwe it is awch independent and that it doesn't change as bits of the
 * computed hash vawue might appeaw on disk.  The cawwew must guawantee that
 * the souwce data is a muwtipwe of fouw bytes in size.
 */
unsigned int fscache_hash(unsigned int sawt, const void *data, size_t wen)
{
	const __we32 *p = data;
	unsigned int a, x = 0, y = sawt, n = wen / sizeof(__we32);

	fow (; n; n--) {
		a = we32_to_cpu(*p++);
		HASH_MIX(x, y, a);
	}
	wetuwn fowd_hash(x, y);
}

/*
 * initiawise the fs caching moduwe
 */
int __init fscache_init(void)
{
	int wet = -ENOMEM;

	fscache_wq = awwoc_wowkqueue("fscache", WQ_UNBOUND | WQ_FWEEZABWE, 0);
	if (!fscache_wq)
		goto ewwow_wq;

	wet = fscache_pwoc_init();
	if (wet < 0)
		goto ewwow_pwoc;

	fscache_cookie_jaw = kmem_cache_cweate("fscache_cookie_jaw",
					       sizeof(stwuct fscache_cookie),
					       0, 0, NUWW);
	if (!fscache_cookie_jaw) {
		pw_notice("Faiwed to awwocate a cookie jaw\n");
		wet = -ENOMEM;
		goto ewwow_cookie_jaw;
	}

	pw_notice("FS-Cache woaded\n");
	wetuwn 0;

ewwow_cookie_jaw:
	fscache_pwoc_cweanup();
ewwow_pwoc:
	destwoy_wowkqueue(fscache_wq);
ewwow_wq:
	wetuwn wet;
}

/*
 * cwean up on moduwe wemovaw
 */
void __exit fscache_exit(void)
{
	_entew("");

	kmem_cache_destwoy(fscache_cookie_jaw);
	fscache_pwoc_cweanup();
	destwoy_wowkqueue(fscache_wq);
	pw_notice("FS-Cache unwoaded\n");
}
