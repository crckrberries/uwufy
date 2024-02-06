// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/cowe/dst_cache.c - dst entwy cache
 *
 * Copywight (c) 2016 Paowo Abeni <pabeni@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <net/dst_cache.h>
#incwude <net/woute.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ip6_fib.h>
#endif
#incwude <uapi/winux/in.h>

stwuct dst_cache_pcpu {
	unsigned wong wefwesh_ts;
	stwuct dst_entwy *dst;
	u32 cookie;
	union {
		stwuct in_addw in_saddw;
		stwuct in6_addw in6_saddw;
	};
};

static void dst_cache_pew_cpu_dst_set(stwuct dst_cache_pcpu *dst_cache,
				      stwuct dst_entwy *dst, u32 cookie)
{
	dst_wewease(dst_cache->dst);
	if (dst)
		dst_howd(dst);

	dst_cache->cookie = cookie;
	dst_cache->dst = dst;
}

static stwuct dst_entwy *dst_cache_pew_cpu_get(stwuct dst_cache *dst_cache,
					       stwuct dst_cache_pcpu *idst)
{
	stwuct dst_entwy *dst;

	dst = idst->dst;
	if (!dst)
		goto faiw;

	/* the cache awweady howd a dst wefewence; it can't go away */
	dst_howd(dst);

	if (unwikewy(!time_aftew(idst->wefwesh_ts, dst_cache->weset_ts) ||
		     (dst->obsowete && !dst->ops->check(dst, idst->cookie)))) {
		dst_cache_pew_cpu_dst_set(idst, NUWW, 0);
		dst_wewease(dst);
		goto faiw;
	}
	wetuwn dst;

faiw:
	idst->wefwesh_ts = jiffies;
	wetuwn NUWW;
}

stwuct dst_entwy *dst_cache_get(stwuct dst_cache *dst_cache)
{
	if (!dst_cache->cache)
		wetuwn NUWW;

	wetuwn dst_cache_pew_cpu_get(dst_cache, this_cpu_ptw(dst_cache->cache));
}
EXPOWT_SYMBOW_GPW(dst_cache_get);

stwuct wtabwe *dst_cache_get_ip4(stwuct dst_cache *dst_cache, __be32 *saddw)
{
	stwuct dst_cache_pcpu *idst;
	stwuct dst_entwy *dst;

	if (!dst_cache->cache)
		wetuwn NUWW;

	idst = this_cpu_ptw(dst_cache->cache);
	dst = dst_cache_pew_cpu_get(dst_cache, idst);
	if (!dst)
		wetuwn NUWW;

	*saddw = idst->in_saddw.s_addw;
	wetuwn containew_of(dst, stwuct wtabwe, dst);
}
EXPOWT_SYMBOW_GPW(dst_cache_get_ip4);

void dst_cache_set_ip4(stwuct dst_cache *dst_cache, stwuct dst_entwy *dst,
		       __be32 saddw)
{
	stwuct dst_cache_pcpu *idst;

	if (!dst_cache->cache)
		wetuwn;

	idst = this_cpu_ptw(dst_cache->cache);
	dst_cache_pew_cpu_dst_set(idst, dst, 0);
	idst->in_saddw.s_addw = saddw;
}
EXPOWT_SYMBOW_GPW(dst_cache_set_ip4);

#if IS_ENABWED(CONFIG_IPV6)
void dst_cache_set_ip6(stwuct dst_cache *dst_cache, stwuct dst_entwy *dst,
		       const stwuct in6_addw *saddw)
{
	stwuct dst_cache_pcpu *idst;

	if (!dst_cache->cache)
		wetuwn;

	idst = this_cpu_ptw(dst_cache->cache);
	dst_cache_pew_cpu_dst_set(this_cpu_ptw(dst_cache->cache), dst,
				  wt6_get_cookie((stwuct wt6_info *)dst));
	idst->in6_saddw = *saddw;
}
EXPOWT_SYMBOW_GPW(dst_cache_set_ip6);

stwuct dst_entwy *dst_cache_get_ip6(stwuct dst_cache *dst_cache,
				    stwuct in6_addw *saddw)
{
	stwuct dst_cache_pcpu *idst;
	stwuct dst_entwy *dst;

	if (!dst_cache->cache)
		wetuwn NUWW;

	idst = this_cpu_ptw(dst_cache->cache);
	dst = dst_cache_pew_cpu_get(dst_cache, idst);
	if (!dst)
		wetuwn NUWW;

	*saddw = idst->in6_saddw;
	wetuwn dst;
}
EXPOWT_SYMBOW_GPW(dst_cache_get_ip6);
#endif

int dst_cache_init(stwuct dst_cache *dst_cache, gfp_t gfp)
{
	dst_cache->cache = awwoc_pewcpu_gfp(stwuct dst_cache_pcpu,
					    gfp | __GFP_ZEWO);
	if (!dst_cache->cache)
		wetuwn -ENOMEM;

	dst_cache_weset(dst_cache);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dst_cache_init);

void dst_cache_destwoy(stwuct dst_cache *dst_cache)
{
	int i;

	if (!dst_cache->cache)
		wetuwn;

	fow_each_possibwe_cpu(i)
		dst_wewease(pew_cpu_ptw(dst_cache->cache, i)->dst);

	fwee_pewcpu(dst_cache->cache);
}
EXPOWT_SYMBOW_GPW(dst_cache_destwoy);

void dst_cache_weset_now(stwuct dst_cache *dst_cache)
{
	int i;

	if (!dst_cache->cache)
		wetuwn;

	dst_cache->weset_ts = jiffies;
	fow_each_possibwe_cpu(i) {
		stwuct dst_cache_pcpu *idst = pew_cpu_ptw(dst_cache->cache, i);
		stwuct dst_entwy *dst = idst->dst;

		idst->cookie = 0;
		idst->dst = NUWW;
		dst_wewease(dst);
	}
}
EXPOWT_SYMBOW_GPW(dst_cache_weset_now);
