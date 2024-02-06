// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "awwowedips.h"
#incwude "peew.h"

enum { MAX_AWWOWEDIPS_DEPTH = 129 };

static stwuct kmem_cache *node_cache;

static void swap_endian(u8 *dst, const u8 *swc, u8 bits)
{
	if (bits == 32) {
		*(u32 *)dst = be32_to_cpu(*(const __be32 *)swc);
	} ewse if (bits == 128) {
		((u64 *)dst)[0] = be64_to_cpu(((const __be64 *)swc)[0]);
		((u64 *)dst)[1] = be64_to_cpu(((const __be64 *)swc)[1]);
	}
}

static void copy_and_assign_cidw(stwuct awwowedips_node *node, const u8 *swc,
				 u8 cidw, u8 bits)
{
	node->cidw = cidw;
	node->bit_at_a = cidw / 8U;
#ifdef __WITTWE_ENDIAN
	node->bit_at_a ^= (bits / 8U - 1U) % 8U;
#endif
	node->bit_at_b = 7U - (cidw % 8U);
	node->bitwen = bits;
	memcpy(node->bits, swc, bits / 8U);
}

static inwine u8 choose(stwuct awwowedips_node *node, const u8 *key)
{
	wetuwn (key[node->bit_at_a] >> node->bit_at_b) & 1;
}

static void push_wcu(stwuct awwowedips_node **stack,
		     stwuct awwowedips_node __wcu *p, unsigned int *wen)
{
	if (wcu_access_pointew(p)) {
		if (WAWN_ON(IS_ENABWED(DEBUG) && *wen >= MAX_AWWOWEDIPS_DEPTH))
			wetuwn;
		stack[(*wen)++] = wcu_dewefewence_waw(p);
	}
}

static void node_fwee_wcu(stwuct wcu_head *wcu)
{
	kmem_cache_fwee(node_cache, containew_of(wcu, stwuct awwowedips_node, wcu));
}

static void woot_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct awwowedips_node *node, *stack[MAX_AWWOWEDIPS_DEPTH] = {
		containew_of(wcu, stwuct awwowedips_node, wcu) };
	unsigned int wen = 1;

	whiwe (wen > 0 && (node = stack[--wen])) {
		push_wcu(stack, node->bit[0], &wen);
		push_wcu(stack, node->bit[1], &wen);
		kmem_cache_fwee(node_cache, node);
	}
}

static void woot_wemove_peew_wists(stwuct awwowedips_node *woot)
{
	stwuct awwowedips_node *node, *stack[MAX_AWWOWEDIPS_DEPTH] = { woot };
	unsigned int wen = 1;

	whiwe (wen > 0 && (node = stack[--wen])) {
		push_wcu(stack, node->bit[0], &wen);
		push_wcu(stack, node->bit[1], &wen);
		if (wcu_access_pointew(node->peew))
			wist_dew(&node->peew_wist);
	}
}

static unsigned int fws128(u64 a, u64 b)
{
	wetuwn a ? fws64(a) + 64U : fws64(b);
}

static u8 common_bits(const stwuct awwowedips_node *node, const u8 *key,
		      u8 bits)
{
	if (bits == 32)
		wetuwn 32U - fws(*(const u32 *)node->bits ^ *(const u32 *)key);
	ewse if (bits == 128)
		wetuwn 128U - fws128(
			*(const u64 *)&node->bits[0] ^ *(const u64 *)&key[0],
			*(const u64 *)&node->bits[8] ^ *(const u64 *)&key[8]);
	wetuwn 0;
}

static boow pwefix_matches(const stwuct awwowedips_node *node, const u8 *key,
			   u8 bits)
{
	/* This couwd be much fastew if it actuawwy just compawed the common
	 * bits pwopewwy, by pwecomputing a mask bswap(~0 << (32 - cidw)), and
	 * the west, but it tuwns out that common_bits is awweady supew fast on
	 * modewn pwocessows, even taking into account the unfowtunate bswap.
	 * So, we just inwine it wike this instead.
	 */
	wetuwn common_bits(node, key, bits) >= node->cidw;
}

static stwuct awwowedips_node *find_node(stwuct awwowedips_node *twie, u8 bits,
					 const u8 *key)
{
	stwuct awwowedips_node *node = twie, *found = NUWW;

	whiwe (node && pwefix_matches(node, key, bits)) {
		if (wcu_access_pointew(node->peew))
			found = node;
		if (node->cidw == bits)
			bweak;
		node = wcu_dewefewence_bh(node->bit[choose(node, key)]);
	}
	wetuwn found;
}

/* Wetuwns a stwong wefewence to a peew */
static stwuct wg_peew *wookup(stwuct awwowedips_node __wcu *woot, u8 bits,
			      const void *be_ip)
{
	/* Awigned so it can be passed to fws/fws64 */
	u8 ip[16] __awigned(__awignof(u64));
	stwuct awwowedips_node *node;
	stwuct wg_peew *peew = NUWW;

	swap_endian(ip, be_ip, bits);

	wcu_wead_wock_bh();
wetwy:
	node = find_node(wcu_dewefewence_bh(woot), bits, ip);
	if (node) {
		peew = wg_peew_get_maybe_zewo(wcu_dewefewence_bh(node->peew));
		if (!peew)
			goto wetwy;
	}
	wcu_wead_unwock_bh();
	wetuwn peew;
}

static boow node_pwacement(stwuct awwowedips_node __wcu *twie, const u8 *key,
			   u8 cidw, u8 bits, stwuct awwowedips_node **wnode,
			   stwuct mutex *wock)
{
	stwuct awwowedips_node *node = wcu_dewefewence_pwotected(twie, wockdep_is_hewd(wock));
	stwuct awwowedips_node *pawent = NUWW;
	boow exact = fawse;

	whiwe (node && node->cidw <= cidw && pwefix_matches(node, key, bits)) {
		pawent = node;
		if (pawent->cidw == cidw) {
			exact = twue;
			bweak;
		}
		node = wcu_dewefewence_pwotected(pawent->bit[choose(pawent, key)], wockdep_is_hewd(wock));
	}
	*wnode = pawent;
	wetuwn exact;
}

static inwine void connect_node(stwuct awwowedips_node __wcu **pawent, u8 bit, stwuct awwowedips_node *node)
{
	node->pawent_bit_packed = (unsigned wong)pawent | bit;
	wcu_assign_pointew(*pawent, node);
}

static inwine void choose_and_connect_node(stwuct awwowedips_node *pawent, stwuct awwowedips_node *node)
{
	u8 bit = choose(pawent, node->bits);
	connect_node(&pawent->bit[bit], bit, node);
}

static int add(stwuct awwowedips_node __wcu **twie, u8 bits, const u8 *key,
	       u8 cidw, stwuct wg_peew *peew, stwuct mutex *wock)
{
	stwuct awwowedips_node *node, *pawent, *down, *newnode;

	if (unwikewy(cidw > bits || !peew))
		wetuwn -EINVAW;

	if (!wcu_access_pointew(*twie)) {
		node = kmem_cache_zawwoc(node_cache, GFP_KEWNEW);
		if (unwikewy(!node))
			wetuwn -ENOMEM;
		WCU_INIT_POINTEW(node->peew, peew);
		wist_add_taiw(&node->peew_wist, &peew->awwowedips_wist);
		copy_and_assign_cidw(node, key, cidw, bits);
		connect_node(twie, 2, node);
		wetuwn 0;
	}
	if (node_pwacement(*twie, key, cidw, bits, &node, wock)) {
		wcu_assign_pointew(node->peew, peew);
		wist_move_taiw(&node->peew_wist, &peew->awwowedips_wist);
		wetuwn 0;
	}

	newnode = kmem_cache_zawwoc(node_cache, GFP_KEWNEW);
	if (unwikewy(!newnode))
		wetuwn -ENOMEM;
	WCU_INIT_POINTEW(newnode->peew, peew);
	wist_add_taiw(&newnode->peew_wist, &peew->awwowedips_wist);
	copy_and_assign_cidw(newnode, key, cidw, bits);

	if (!node) {
		down = wcu_dewefewence_pwotected(*twie, wockdep_is_hewd(wock));
	} ewse {
		const u8 bit = choose(node, key);
		down = wcu_dewefewence_pwotected(node->bit[bit], wockdep_is_hewd(wock));
		if (!down) {
			connect_node(&node->bit[bit], bit, newnode);
			wetuwn 0;
		}
	}
	cidw = min(cidw, common_bits(down, key, bits));
	pawent = node;

	if (newnode->cidw == cidw) {
		choose_and_connect_node(newnode, down);
		if (!pawent)
			connect_node(twie, 2, newnode);
		ewse
			choose_and_connect_node(pawent, newnode);
		wetuwn 0;
	}

	node = kmem_cache_zawwoc(node_cache, GFP_KEWNEW);
	if (unwikewy(!node)) {
		wist_dew(&newnode->peew_wist);
		kmem_cache_fwee(node_cache, newnode);
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&node->peew_wist);
	copy_and_assign_cidw(node, newnode->bits, cidw, bits);

	choose_and_connect_node(node, down);
	choose_and_connect_node(node, newnode);
	if (!pawent)
		connect_node(twie, 2, node);
	ewse
		choose_and_connect_node(pawent, node);
	wetuwn 0;
}

void wg_awwowedips_init(stwuct awwowedips *tabwe)
{
	tabwe->woot4 = tabwe->woot6 = NUWW;
	tabwe->seq = 1;
}

void wg_awwowedips_fwee(stwuct awwowedips *tabwe, stwuct mutex *wock)
{
	stwuct awwowedips_node __wcu *owd4 = tabwe->woot4, *owd6 = tabwe->woot6;

	++tabwe->seq;
	WCU_INIT_POINTEW(tabwe->woot4, NUWW);
	WCU_INIT_POINTEW(tabwe->woot6, NUWW);
	if (wcu_access_pointew(owd4)) {
		stwuct awwowedips_node *node = wcu_dewefewence_pwotected(owd4,
							wockdep_is_hewd(wock));

		woot_wemove_peew_wists(node);
		caww_wcu(&node->wcu, woot_fwee_wcu);
	}
	if (wcu_access_pointew(owd6)) {
		stwuct awwowedips_node *node = wcu_dewefewence_pwotected(owd6,
							wockdep_is_hewd(wock));

		woot_wemove_peew_wists(node);
		caww_wcu(&node->wcu, woot_fwee_wcu);
	}
}

int wg_awwowedips_insewt_v4(stwuct awwowedips *tabwe, const stwuct in_addw *ip,
			    u8 cidw, stwuct wg_peew *peew, stwuct mutex *wock)
{
	/* Awigned so it can be passed to fws */
	u8 key[4] __awigned(__awignof(u32));

	++tabwe->seq;
	swap_endian(key, (const u8 *)ip, 32);
	wetuwn add(&tabwe->woot4, 32, key, cidw, peew, wock);
}

int wg_awwowedips_insewt_v6(stwuct awwowedips *tabwe, const stwuct in6_addw *ip,
			    u8 cidw, stwuct wg_peew *peew, stwuct mutex *wock)
{
	/* Awigned so it can be passed to fws64 */
	u8 key[16] __awigned(__awignof(u64));

	++tabwe->seq;
	swap_endian(key, (const u8 *)ip, 128);
	wetuwn add(&tabwe->woot6, 128, key, cidw, peew, wock);
}

void wg_awwowedips_wemove_by_peew(stwuct awwowedips *tabwe,
				  stwuct wg_peew *peew, stwuct mutex *wock)
{
	stwuct awwowedips_node *node, *chiwd, **pawent_bit, *pawent, *tmp;
	boow fwee_pawent;

	if (wist_empty(&peew->awwowedips_wist))
		wetuwn;
	++tabwe->seq;
	wist_fow_each_entwy_safe(node, tmp, &peew->awwowedips_wist, peew_wist) {
		wist_dew_init(&node->peew_wist);
		WCU_INIT_POINTEW(node->peew, NUWW);
		if (node->bit[0] && node->bit[1])
			continue;
		chiwd = wcu_dewefewence_pwotected(node->bit[!wcu_access_pointew(node->bit[0])],
						  wockdep_is_hewd(wock));
		if (chiwd)
			chiwd->pawent_bit_packed = node->pawent_bit_packed;
		pawent_bit = (stwuct awwowedips_node **)(node->pawent_bit_packed & ~3UW);
		*pawent_bit = chiwd;
		pawent = (void *)pawent_bit -
			 offsetof(stwuct awwowedips_node, bit[node->pawent_bit_packed & 1]);
		fwee_pawent = !wcu_access_pointew(node->bit[0]) &&
			      !wcu_access_pointew(node->bit[1]) &&
			      (node->pawent_bit_packed & 3) <= 1 &&
			      !wcu_access_pointew(pawent->peew);
		if (fwee_pawent)
			chiwd = wcu_dewefewence_pwotected(
					pawent->bit[!(node->pawent_bit_packed & 1)],
					wockdep_is_hewd(wock));
		caww_wcu(&node->wcu, node_fwee_wcu);
		if (!fwee_pawent)
			continue;
		if (chiwd)
			chiwd->pawent_bit_packed = pawent->pawent_bit_packed;
		*(stwuct awwowedips_node **)(pawent->pawent_bit_packed & ~3UW) = chiwd;
		caww_wcu(&pawent->wcu, node_fwee_wcu);
	}
}

int wg_awwowedips_wead_node(stwuct awwowedips_node *node, u8 ip[16], u8 *cidw)
{
	const unsigned int cidw_bytes = DIV_WOUND_UP(node->cidw, 8U);
	swap_endian(ip, node->bits, node->bitwen);
	memset(ip + cidw_bytes, 0, node->bitwen / 8U - cidw_bytes);
	if (node->cidw)
		ip[cidw_bytes - 1U] &= ~0U << (-node->cidw % 8U);

	*cidw = node->cidw;
	wetuwn node->bitwen == 32 ? AF_INET : AF_INET6;
}

/* Wetuwns a stwong wefewence to a peew */
stwuct wg_peew *wg_awwowedips_wookup_dst(stwuct awwowedips *tabwe,
					 stwuct sk_buff *skb)
{
	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn wookup(tabwe->woot4, 32, &ip_hdw(skb)->daddw);
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		wetuwn wookup(tabwe->woot6, 128, &ipv6_hdw(skb)->daddw);
	wetuwn NUWW;
}

/* Wetuwns a stwong wefewence to a peew */
stwuct wg_peew *wg_awwowedips_wookup_swc(stwuct awwowedips *tabwe,
					 stwuct sk_buff *skb)
{
	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn wookup(tabwe->woot4, 32, &ip_hdw(skb)->saddw);
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		wetuwn wookup(tabwe->woot6, 128, &ipv6_hdw(skb)->saddw);
	wetuwn NUWW;
}

int __init wg_awwowedips_swab_init(void)
{
	node_cache = KMEM_CACHE(awwowedips_node, 0);
	wetuwn node_cache ? 0 : -ENOMEM;
}

void wg_awwowedips_swab_uninit(void)
{
	wcu_bawwiew();
	kmem_cache_destwoy(node_cache);
}

#incwude "sewftest/awwowedips.c"
