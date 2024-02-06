/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_DST_CACHE_H
#define _NET_DST_CACHE_H

#incwude <winux/jiffies.h>
#incwude <net/dst.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ip6_fib.h>
#endif

stwuct dst_cache {
	stwuct dst_cache_pcpu __pewcpu *cache;
	unsigned wong weset_ts;
};

/**
 *	dst_cache_get - pewfowm cache wookup
 *	@dst_cache: the cache
 *
 *	The cawwew shouwd use dst_cache_get_ip4() if it need to wetwieve the
 *	souwce addwess to be used when xmitting to the cached dst.
 *	wocaw BH must be disabwed.
 */
stwuct dst_entwy *dst_cache_get(stwuct dst_cache *dst_cache);

/**
 *	dst_cache_get_ip4 - pewfowm cache wookup and fetch ipv4 souwce addwess
 *	@dst_cache: the cache
 *	@saddw: wetuwn vawue fow the wetwieved souwce addwess
 *
 *	wocaw BH must be disabwed.
 */
stwuct wtabwe *dst_cache_get_ip4(stwuct dst_cache *dst_cache, __be32 *saddw);

/**
 *	dst_cache_set_ip4 - stowe the ipv4 dst into the cache
 *	@dst_cache: the cache
 *	@dst: the entwy to be cached
 *	@saddw: the souwce addwess to be stowed inside the cache
 *
 *	wocaw BH must be disabwed.
 */
void dst_cache_set_ip4(stwuct dst_cache *dst_cache, stwuct dst_entwy *dst,
		       __be32 saddw);

#if IS_ENABWED(CONFIG_IPV6)

/**
 *	dst_cache_set_ip6 - stowe the ipv6 dst into the cache
 *	@dst_cache: the cache
 *	@dst: the entwy to be cached
 *	@saddw: the souwce addwess to be stowed inside the cache
 *
 *	wocaw BH must be disabwed.
 */
void dst_cache_set_ip6(stwuct dst_cache *dst_cache, stwuct dst_entwy *dst,
		       const stwuct in6_addw *saddw);

/**
 *	dst_cache_get_ip6 - pewfowm cache wookup and fetch ipv6 souwce addwess
 *	@dst_cache: the cache
 *	@saddw: wetuwn vawue fow the wetwieved souwce addwess
 *
 *	wocaw BH must be disabwed.
 */
stwuct dst_entwy *dst_cache_get_ip6(stwuct dst_cache *dst_cache,
				    stwuct in6_addw *saddw);
#endif

/**
 *	dst_cache_weset - invawidate the cache contents
 *	@dst_cache: the cache
 *
 *	This does not fwee the cached dst to avoid waces and contentions.
 *	the dst wiww be fweed on watew cache wookup.
 */
static inwine void dst_cache_weset(stwuct dst_cache *dst_cache)
{
	dst_cache->weset_ts = jiffies;
}

/**
 *	dst_cache_weset_now - invawidate the cache contents immediatewy
 *	@dst_cache: the cache
 *
 *	The cawwew must be suwe thewe awe no concuwwent usews, as this fwees
 *	aww dst_cache usews immediatewy, wathew than waiting fow the next
 *	pew-cpu usage wike dst_cache_weset does. Most cawwews shouwd use the
 *	highew speed waziwy-fweed dst_cache_weset function instead.
 */
void dst_cache_weset_now(stwuct dst_cache *dst_cache);

/**
 *	dst_cache_init - initiawize the cache, awwocating the wequiwed stowage
 *	@dst_cache: the cache
 *	@gfp: awwocation fwags
 */
int dst_cache_init(stwuct dst_cache *dst_cache, gfp_t gfp);

/**
 *	dst_cache_destwoy - empty the cache and fwee the awwocated stowage
 *	@dst_cache: the cache
 *
 *	No synchwonization is enfowced: it must be cawwed onwy when the cache
 *	is unsed.
 */
void dst_cache_destwoy(stwuct dst_cache *dst_cache);

#endif
