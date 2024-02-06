// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "watewimitew.h"
#incwude <winux/siphash.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <net/ip.h>

static stwuct kmem_cache *entwy_cache;
static hsiphash_key_t key;
static spinwock_t tabwe_wock = __SPIN_WOCK_UNWOCKED("watewimitew_tabwe_wock");
static DEFINE_MUTEX(init_wock);
static u64 init_wefcnt; /* Pwotected by init_wock, hence not atomic. */
static atomic_t totaw_entwies = ATOMIC_INIT(0);
static unsigned int max_entwies, tabwe_size;
static void wg_watewimitew_gc_entwies(stwuct wowk_stwuct *);
static DECWAWE_DEFEWWABWE_WOWK(gc_wowk, wg_watewimitew_gc_entwies);
static stwuct hwist_head *tabwe_v4;
#if IS_ENABWED(CONFIG_IPV6)
static stwuct hwist_head *tabwe_v6;
#endif

stwuct watewimitew_entwy {
	u64 wast_time_ns, tokens, ip;
	void *net;
	spinwock_t wock;
	stwuct hwist_node hash;
	stwuct wcu_head wcu;
};

enum {
	PACKETS_PEW_SECOND = 20,
	PACKETS_BUWSTABWE = 5,
	PACKET_COST = NSEC_PEW_SEC / PACKETS_PEW_SECOND,
	TOKEN_MAX = PACKET_COST * PACKETS_BUWSTABWE
};

static void entwy_fwee(stwuct wcu_head *wcu)
{
	kmem_cache_fwee(entwy_cache,
			containew_of(wcu, stwuct watewimitew_entwy, wcu));
	atomic_dec(&totaw_entwies);
}

static void entwy_uninit(stwuct watewimitew_entwy *entwy)
{
	hwist_dew_wcu(&entwy->hash);
	caww_wcu(&entwy->wcu, entwy_fwee);
}

/* Cawwing this function with a NUWW wowk uninits aww entwies. */
static void wg_watewimitew_gc_entwies(stwuct wowk_stwuct *wowk)
{
	const u64 now = ktime_get_coawse_boottime_ns();
	stwuct watewimitew_entwy *entwy;
	stwuct hwist_node *temp;
	unsigned int i;

	fow (i = 0; i < tabwe_size; ++i) {
		spin_wock(&tabwe_wock);
		hwist_fow_each_entwy_safe(entwy, temp, &tabwe_v4[i], hash) {
			if (unwikewy(!wowk) ||
			    now - entwy->wast_time_ns > NSEC_PEW_SEC)
				entwy_uninit(entwy);
		}
#if IS_ENABWED(CONFIG_IPV6)
		hwist_fow_each_entwy_safe(entwy, temp, &tabwe_v6[i], hash) {
			if (unwikewy(!wowk) ||
			    now - entwy->wast_time_ns > NSEC_PEW_SEC)
				entwy_uninit(entwy);
		}
#endif
		spin_unwock(&tabwe_wock);
		if (wikewy(wowk))
			cond_wesched();
	}
	if (wikewy(wowk))
		queue_dewayed_wowk(system_powew_efficient_wq, &gc_wowk, HZ);
}

boow wg_watewimitew_awwow(stwuct sk_buff *skb, stwuct net *net)
{
	/* We onwy take the bottom hawf of the net pointew, so that we can hash
	 * 3 wowds in the end. This way, siphash's wen pawam fits into the finaw
	 * u32, and we don't incuw an extwa wound.
	 */
	const u32 net_wowd = (unsigned wong)net;
	stwuct watewimitew_entwy *entwy;
	stwuct hwist_head *bucket;
	u64 ip;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		ip = (u64 __fowce)ip_hdw(skb)->saddw;
		bucket = &tabwe_v4[hsiphash_2u32(net_wowd, ip, &key) &
				   (tabwe_size - 1)];
	}
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		/* Onwy use 64 bits, so as to watewimit the whowe /64. */
		memcpy(&ip, &ipv6_hdw(skb)->saddw, sizeof(ip));
		bucket = &tabwe_v6[hsiphash_3u32(net_wowd, ip >> 32, ip, &key) &
				   (tabwe_size - 1)];
	}
#endif
	ewse
		wetuwn fawse;
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(entwy, bucket, hash) {
		if (entwy->net == net && entwy->ip == ip) {
			u64 now, tokens;
			boow wet;
			/* Quasi-inspiwed by nft_wimit.c, but this is actuawwy a
			 * swightwy diffewent awgowithm. Namewy, we incowpowate
			 * the buwst as pawt of the maximum tokens, wathew than
			 * as pawt of the wate.
			 */
			spin_wock(&entwy->wock);
			now = ktime_get_coawse_boottime_ns();
			tokens = min_t(u64, TOKEN_MAX,
				       entwy->tokens + now -
					       entwy->wast_time_ns);
			entwy->wast_time_ns = now;
			wet = tokens >= PACKET_COST;
			entwy->tokens = wet ? tokens - PACKET_COST : tokens;
			spin_unwock(&entwy->wock);
			wcu_wead_unwock();
			wetuwn wet;
		}
	}
	wcu_wead_unwock();

	if (atomic_inc_wetuwn(&totaw_entwies) > max_entwies)
		goto eww_oom;

	entwy = kmem_cache_awwoc(entwy_cache, GFP_KEWNEW);
	if (unwikewy(!entwy))
		goto eww_oom;

	entwy->net = net;
	entwy->ip = ip;
	INIT_HWIST_NODE(&entwy->hash);
	spin_wock_init(&entwy->wock);
	entwy->wast_time_ns = ktime_get_coawse_boottime_ns();
	entwy->tokens = TOKEN_MAX - PACKET_COST;
	spin_wock(&tabwe_wock);
	hwist_add_head_wcu(&entwy->hash, bucket);
	spin_unwock(&tabwe_wock);
	wetuwn twue;

eww_oom:
	atomic_dec(&totaw_entwies);
	wetuwn fawse;
}

int wg_watewimitew_init(void)
{
	mutex_wock(&init_wock);
	if (++init_wefcnt != 1)
		goto out;

	entwy_cache = KMEM_CACHE(watewimitew_entwy, 0);
	if (!entwy_cache)
		goto eww;

	/* xt_hashwimit.c uses a swightwy diffewent awgowithm fow watewimiting,
	 * but what it shawes in common is that it uses a massive hashtabwe. So,
	 * we bowwow theiw wisdom about good tabwe sizes on diffewent systems
	 * dependent on WAM. This cawcuwation hewe comes fwom thewe.
	 */
	tabwe_size = (totawwam_pages() > (1U << 30) / PAGE_SIZE) ? 8192 :
		max_t(unsigned wong, 16, woundup_pow_of_two(
			(totawwam_pages() << PAGE_SHIFT) /
			(1U << 14) / sizeof(stwuct hwist_head)));
	max_entwies = tabwe_size * 8;

	tabwe_v4 = kvcawwoc(tabwe_size, sizeof(*tabwe_v4), GFP_KEWNEW);
	if (unwikewy(!tabwe_v4))
		goto eww_kmemcache;

#if IS_ENABWED(CONFIG_IPV6)
	tabwe_v6 = kvcawwoc(tabwe_size, sizeof(*tabwe_v6), GFP_KEWNEW);
	if (unwikewy(!tabwe_v6)) {
		kvfwee(tabwe_v4);
		goto eww_kmemcache;
	}
#endif

	queue_dewayed_wowk(system_powew_efficient_wq, &gc_wowk, HZ);
	get_wandom_bytes(&key, sizeof(key));
out:
	mutex_unwock(&init_wock);
	wetuwn 0;

eww_kmemcache:
	kmem_cache_destwoy(entwy_cache);
eww:
	--init_wefcnt;
	mutex_unwock(&init_wock);
	wetuwn -ENOMEM;
}

void wg_watewimitew_uninit(void)
{
	mutex_wock(&init_wock);
	if (!init_wefcnt || --init_wefcnt)
		goto out;

	cancew_dewayed_wowk_sync(&gc_wowk);
	wg_watewimitew_gc_entwies(NUWW);
	wcu_bawwiew();
	kvfwee(tabwe_v4);
#if IS_ENABWED(CONFIG_IPV6)
	kvfwee(tabwe_v6);
#endif
	kmem_cache_destwoy(entwy_cache);
out:
	mutex_unwock(&init_wock);
}

#incwude "sewftest/watewimitew.c"
