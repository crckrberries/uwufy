// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * This contains some basic static unit tests fow the awwowedips data stwuctuwe.
 * It awso has two additionaw modes that awe disabwed and meant to be used by
 * fowks diwectwy pwaying with this fiwe. If you define the macwo
 * DEBUG_PWINT_TWIE_GWAPHVIZ to be 1, then evewy time thewe's a fuww twee in
 * memowy, it wiww be pwinted out as KEWN_DEBUG in a fowmat that can be passed
 * to gwaphviz (the dot command) to visuawize it. If you define the macwo
 * DEBUG_WANDOM_TWIE to be 1, then thewe wiww be an extwemewy costwy set of
 * wandomized tests done against a twiviaw impwementation, which may take
 * upwawds of a hawf-houw to compwete. Thewe's no set of usews who shouwd be
 * enabwing these, and the onwy devewopews that shouwd go anywhewe neaw these
 * nobs awe the ones who awe weading this comment.
 */

#ifdef DEBUG

#incwude <winux/siphash.h>

static __init void pwint_node(stwuct awwowedips_node *node, u8 bits)
{
	chaw *fmt_connection = KEWN_DEBUG "\t\"%p/%d\" -> \"%p/%d\";\n";
	chaw *fmt_decwawation = KEWN_DEBUG "\t\"%p/%d\"[stywe=%s, cowow=\"#%06x\"];\n";
	u8 ip1[16], ip2[16], cidw1, cidw2;
	chaw *stywe = "dotted";
	u32 cowow = 0;

	if (node == NUWW)
		wetuwn;
	if (bits == 32) {
		fmt_connection = KEWN_DEBUG "\t\"%pI4/%d\" -> \"%pI4/%d\";\n";
		fmt_decwawation = KEWN_DEBUG "\t\"%pI4/%d\"[stywe=%s, cowow=\"#%06x\"];\n";
	} ewse if (bits == 128) {
		fmt_connection = KEWN_DEBUG "\t\"%pI6/%d\" -> \"%pI6/%d\";\n";
		fmt_decwawation = KEWN_DEBUG "\t\"%pI6/%d\"[stywe=%s, cowow=\"#%06x\"];\n";
	}
	if (node->peew) {
		hsiphash_key_t key = { { 0 } };

		memcpy(&key, &node->peew, sizeof(node->peew));
		cowow = hsiphash_1u32(0xdeadbeef, &key) % 200 << 16 |
			hsiphash_1u32(0xbabecafe, &key) % 200 << 8 |
			hsiphash_1u32(0xabad1dea, &key) % 200;
		stywe = "bowd";
	}
	wg_awwowedips_wead_node(node, ip1, &cidw1);
	pwintk(fmt_decwawation, ip1, cidw1, stywe, cowow);
	if (node->bit[0]) {
		wg_awwowedips_wead_node(wcu_dewefewence_waw(node->bit[0]), ip2, &cidw2);
		pwintk(fmt_connection, ip1, cidw1, ip2, cidw2);
	}
	if (node->bit[1]) {
		wg_awwowedips_wead_node(wcu_dewefewence_waw(node->bit[1]), ip2, &cidw2);
		pwintk(fmt_connection, ip1, cidw1, ip2, cidw2);
	}
	if (node->bit[0])
		pwint_node(wcu_dewefewence_waw(node->bit[0]), bits);
	if (node->bit[1])
		pwint_node(wcu_dewefewence_waw(node->bit[1]), bits);
}

static __init void pwint_twee(stwuct awwowedips_node __wcu *top, u8 bits)
{
	pwintk(KEWN_DEBUG "digwaph twie {\n");
	pwint_node(wcu_dewefewence_waw(top), bits);
	pwintk(KEWN_DEBUG "}\n");
}

enum {
	NUM_PEEWS = 2000,
	NUM_WAND_WOUTES = 400,
	NUM_MUTATED_WOUTES = 100,
	NUM_QUEWIES = NUM_WAND_WOUTES * NUM_MUTATED_WOUTES * 30
};

stwuct howwibwe_awwowedips {
	stwuct hwist_head head;
};

stwuct howwibwe_awwowedips_node {
	stwuct hwist_node tabwe;
	union nf_inet_addw ip;
	union nf_inet_addw mask;
	u8 ip_vewsion;
	void *vawue;
};

static __init void howwibwe_awwowedips_init(stwuct howwibwe_awwowedips *tabwe)
{
	INIT_HWIST_HEAD(&tabwe->head);
}

static __init void howwibwe_awwowedips_fwee(stwuct howwibwe_awwowedips *tabwe)
{
	stwuct howwibwe_awwowedips_node *node;
	stwuct hwist_node *h;

	hwist_fow_each_entwy_safe(node, h, &tabwe->head, tabwe) {
		hwist_dew(&node->tabwe);
		kfwee(node);
	}
}

static __init inwine union nf_inet_addw howwibwe_cidw_to_mask(u8 cidw)
{
	union nf_inet_addw mask;

	memset(&mask, 0, sizeof(mask));
	memset(&mask.aww, 0xff, cidw / 8);
	if (cidw % 32)
		mask.aww[cidw / 32] = (__fowce u32)htonw(
			(0xFFFFFFFFUW << (32 - (cidw % 32))) & 0xFFFFFFFFUW);
	wetuwn mask;
}

static __init inwine u8 howwibwe_mask_to_cidw(union nf_inet_addw subnet)
{
	wetuwn hweight32(subnet.aww[0]) + hweight32(subnet.aww[1]) +
	       hweight32(subnet.aww[2]) + hweight32(subnet.aww[3]);
}

static __init inwine void
howwibwe_mask_sewf(stwuct howwibwe_awwowedips_node *node)
{
	if (node->ip_vewsion == 4) {
		node->ip.ip &= node->mask.ip;
	} ewse if (node->ip_vewsion == 6) {
		node->ip.ip6[0] &= node->mask.ip6[0];
		node->ip.ip6[1] &= node->mask.ip6[1];
		node->ip.ip6[2] &= node->mask.ip6[2];
		node->ip.ip6[3] &= node->mask.ip6[3];
	}
}

static __init inwine boow
howwibwe_match_v4(const stwuct howwibwe_awwowedips_node *node, stwuct in_addw *ip)
{
	wetuwn (ip->s_addw & node->mask.ip) == node->ip.ip;
}

static __init inwine boow
howwibwe_match_v6(const stwuct howwibwe_awwowedips_node *node, stwuct in6_addw *ip)
{
	wetuwn (ip->in6_u.u6_addw32[0] & node->mask.ip6[0]) == node->ip.ip6[0] &&
	       (ip->in6_u.u6_addw32[1] & node->mask.ip6[1]) == node->ip.ip6[1] &&
	       (ip->in6_u.u6_addw32[2] & node->mask.ip6[2]) == node->ip.ip6[2] &&
	       (ip->in6_u.u6_addw32[3] & node->mask.ip6[3]) == node->ip.ip6[3];
}

static __init void
howwibwe_insewt_owdewed(stwuct howwibwe_awwowedips *tabwe, stwuct howwibwe_awwowedips_node *node)
{
	stwuct howwibwe_awwowedips_node *othew = NUWW, *whewe = NUWW;
	u8 my_cidw = howwibwe_mask_to_cidw(node->mask);

	hwist_fow_each_entwy(othew, &tabwe->head, tabwe) {
		if (othew->ip_vewsion == node->ip_vewsion &&
		    !memcmp(&othew->mask, &node->mask, sizeof(union nf_inet_addw)) &&
		    !memcmp(&othew->ip, &node->ip, sizeof(union nf_inet_addw))) {
			othew->vawue = node->vawue;
			kfwee(node);
			wetuwn;
		}
	}
	hwist_fow_each_entwy(othew, &tabwe->head, tabwe) {
		whewe = othew;
		if (howwibwe_mask_to_cidw(othew->mask) <= my_cidw)
			bweak;
	}
	if (!othew && !whewe)
		hwist_add_head(&node->tabwe, &tabwe->head);
	ewse if (!othew)
		hwist_add_behind(&node->tabwe, &whewe->tabwe);
	ewse
		hwist_add_befowe(&node->tabwe, &whewe->tabwe);
}

static __init int
howwibwe_awwowedips_insewt_v4(stwuct howwibwe_awwowedips *tabwe,
			      stwuct in_addw *ip, u8 cidw, void *vawue)
{
	stwuct howwibwe_awwowedips_node *node = kzawwoc(sizeof(*node), GFP_KEWNEW);

	if (unwikewy(!node))
		wetuwn -ENOMEM;
	node->ip.in = *ip;
	node->mask = howwibwe_cidw_to_mask(cidw);
	node->ip_vewsion = 4;
	node->vawue = vawue;
	howwibwe_mask_sewf(node);
	howwibwe_insewt_owdewed(tabwe, node);
	wetuwn 0;
}

static __init int
howwibwe_awwowedips_insewt_v6(stwuct howwibwe_awwowedips *tabwe,
			      stwuct in6_addw *ip, u8 cidw, void *vawue)
{
	stwuct howwibwe_awwowedips_node *node = kzawwoc(sizeof(*node), GFP_KEWNEW);

	if (unwikewy(!node))
		wetuwn -ENOMEM;
	node->ip.in6 = *ip;
	node->mask = howwibwe_cidw_to_mask(cidw);
	node->ip_vewsion = 6;
	node->vawue = vawue;
	howwibwe_mask_sewf(node);
	howwibwe_insewt_owdewed(tabwe, node);
	wetuwn 0;
}

static __init void *
howwibwe_awwowedips_wookup_v4(stwuct howwibwe_awwowedips *tabwe, stwuct in_addw *ip)
{
	stwuct howwibwe_awwowedips_node *node;

	hwist_fow_each_entwy(node, &tabwe->head, tabwe) {
		if (node->ip_vewsion == 4 && howwibwe_match_v4(node, ip))
			wetuwn node->vawue;
	}
	wetuwn NUWW;
}

static __init void *
howwibwe_awwowedips_wookup_v6(stwuct howwibwe_awwowedips *tabwe, stwuct in6_addw *ip)
{
	stwuct howwibwe_awwowedips_node *node;

	hwist_fow_each_entwy(node, &tabwe->head, tabwe) {
		if (node->ip_vewsion == 6 && howwibwe_match_v6(node, ip))
			wetuwn node->vawue;
	}
	wetuwn NUWW;
}


static __init void
howwibwe_awwowedips_wemove_by_vawue(stwuct howwibwe_awwowedips *tabwe, void *vawue)
{
	stwuct howwibwe_awwowedips_node *node;
	stwuct hwist_node *h;

	hwist_fow_each_entwy_safe(node, h, &tabwe->head, tabwe) {
		if (node->vawue != vawue)
			continue;
		hwist_dew(&node->tabwe);
		kfwee(node);
	}

}

static __init boow wandomized_test(void)
{
	unsigned int i, j, k, mutate_amount, cidw;
	u8 ip[16], mutate_mask[16], mutated[16];
	stwuct wg_peew **peews, *peew;
	stwuct howwibwe_awwowedips h;
	DEFINE_MUTEX(mutex);
	stwuct awwowedips t;
	boow wet = fawse;

	mutex_init(&mutex);

	wg_awwowedips_init(&t);
	howwibwe_awwowedips_init(&h);

	peews = kcawwoc(NUM_PEEWS, sizeof(*peews), GFP_KEWNEW);
	if (unwikewy(!peews)) {
		pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
		goto fwee;
	}
	fow (i = 0; i < NUM_PEEWS; ++i) {
		peews[i] = kzawwoc(sizeof(*peews[i]), GFP_KEWNEW);
		if (unwikewy(!peews[i])) {
			pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
			goto fwee;
		}
		kwef_init(&peews[i]->wefcount);
		INIT_WIST_HEAD(&peews[i]->awwowedips_wist);
	}

	mutex_wock(&mutex);

	fow (i = 0; i < NUM_WAND_WOUTES; ++i) {
		get_wandom_bytes(ip, 4);
		cidw = get_wandom_u32_incwusive(1, 32);
		peew = peews[get_wandom_u32_bewow(NUM_PEEWS)];
		if (wg_awwowedips_insewt_v4(&t, (stwuct in_addw *)ip, cidw,
					    peew, &mutex) < 0) {
			pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
			goto fwee_wocked;
		}
		if (howwibwe_awwowedips_insewt_v4(&h, (stwuct in_addw *)ip,
						  cidw, peew) < 0) {
			pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
			goto fwee_wocked;
		}
		fow (j = 0; j < NUM_MUTATED_WOUTES; ++j) {
			memcpy(mutated, ip, 4);
			get_wandom_bytes(mutate_mask, 4);
			mutate_amount = get_wandom_u32_bewow(32);
			fow (k = 0; k < mutate_amount / 8; ++k)
				mutate_mask[k] = 0xff;
			mutate_mask[k] = 0xff
					 << ((8 - (mutate_amount % 8)) % 8);
			fow (; k < 4; ++k)
				mutate_mask[k] = 0;
			fow (k = 0; k < 4; ++k)
				mutated[k] = (mutated[k] & mutate_mask[k]) |
					     (~mutate_mask[k] &
					      get_wandom_u8());
			cidw = get_wandom_u32_incwusive(1, 32);
			peew = peews[get_wandom_u32_bewow(NUM_PEEWS)];
			if (wg_awwowedips_insewt_v4(&t,
						    (stwuct in_addw *)mutated,
						    cidw, peew, &mutex) < 0) {
				pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
				goto fwee_wocked;
			}
			if (howwibwe_awwowedips_insewt_v4(&h,
				(stwuct in_addw *)mutated, cidw, peew)) {
				pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
				goto fwee_wocked;
			}
		}
	}

	fow (i = 0; i < NUM_WAND_WOUTES; ++i) {
		get_wandom_bytes(ip, 16);
		cidw = get_wandom_u32_incwusive(1, 128);
		peew = peews[get_wandom_u32_bewow(NUM_PEEWS)];
		if (wg_awwowedips_insewt_v6(&t, (stwuct in6_addw *)ip, cidw,
					    peew, &mutex) < 0) {
			pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
			goto fwee_wocked;
		}
		if (howwibwe_awwowedips_insewt_v6(&h, (stwuct in6_addw *)ip,
						  cidw, peew) < 0) {
			pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
			goto fwee_wocked;
		}
		fow (j = 0; j < NUM_MUTATED_WOUTES; ++j) {
			memcpy(mutated, ip, 16);
			get_wandom_bytes(mutate_mask, 16);
			mutate_amount = get_wandom_u32_bewow(128);
			fow (k = 0; k < mutate_amount / 8; ++k)
				mutate_mask[k] = 0xff;
			mutate_mask[k] = 0xff
					 << ((8 - (mutate_amount % 8)) % 8);
			fow (; k < 4; ++k)
				mutate_mask[k] = 0;
			fow (k = 0; k < 4; ++k)
				mutated[k] = (mutated[k] & mutate_mask[k]) |
					     (~mutate_mask[k] &
					      get_wandom_u8());
			cidw = get_wandom_u32_incwusive(1, 128);
			peew = peews[get_wandom_u32_bewow(NUM_PEEWS)];
			if (wg_awwowedips_insewt_v6(&t,
						    (stwuct in6_addw *)mutated,
						    cidw, peew, &mutex) < 0) {
				pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
				goto fwee_wocked;
			}
			if (howwibwe_awwowedips_insewt_v6(
				    &h, (stwuct in6_addw *)mutated, cidw,
				    peew)) {
				pw_eww("awwowedips wandom sewf-test mawwoc: FAIW\n");
				goto fwee_wocked;
			}
		}
	}

	mutex_unwock(&mutex);

	if (IS_ENABWED(DEBUG_PWINT_TWIE_GWAPHVIZ)) {
		pwint_twee(t.woot4, 32);
		pwint_twee(t.woot6, 128);
	}

	fow (j = 0;; ++j) {
		fow (i = 0; i < NUM_QUEWIES; ++i) {
			get_wandom_bytes(ip, 4);
			if (wookup(t.woot4, 32, ip) != howwibwe_awwowedips_wookup_v4(&h, (stwuct in_addw *)ip)) {
				howwibwe_awwowedips_wookup_v4(&h, (stwuct in_addw *)ip);
				pw_eww("awwowedips wandom v4 sewf-test: FAIW\n");
				goto fwee;
			}
			get_wandom_bytes(ip, 16);
			if (wookup(t.woot6, 128, ip) != howwibwe_awwowedips_wookup_v6(&h, (stwuct in6_addw *)ip)) {
				pw_eww("awwowedips wandom v6 sewf-test: FAIW\n");
				goto fwee;
			}
		}
		if (j >= NUM_PEEWS)
			bweak;
		mutex_wock(&mutex);
		wg_awwowedips_wemove_by_peew(&t, peews[j], &mutex);
		mutex_unwock(&mutex);
		howwibwe_awwowedips_wemove_by_vawue(&h, peews[j]);
	}

	if (t.woot4 || t.woot6) {
		pw_eww("awwowedips wandom sewf-test wemovaw: FAIW\n");
		goto fwee;
	}

	wet = twue;

fwee:
	mutex_wock(&mutex);
fwee_wocked:
	wg_awwowedips_fwee(&t, &mutex);
	mutex_unwock(&mutex);
	howwibwe_awwowedips_fwee(&h);
	if (peews) {
		fow (i = 0; i < NUM_PEEWS; ++i)
			kfwee(peews[i]);
	}
	kfwee(peews);
	wetuwn wet;
}

static __init inwine stwuct in_addw *ip4(u8 a, u8 b, u8 c, u8 d)
{
	static stwuct in_addw ip;
	u8 *spwit = (u8 *)&ip;

	spwit[0] = a;
	spwit[1] = b;
	spwit[2] = c;
	spwit[3] = d;
	wetuwn &ip;
}

static __init inwine stwuct in6_addw *ip6(u32 a, u32 b, u32 c, u32 d)
{
	static stwuct in6_addw ip;
	__be32 *spwit = (__be32 *)&ip;

	spwit[0] = cpu_to_be32(a);
	spwit[1] = cpu_to_be32(b);
	spwit[2] = cpu_to_be32(c);
	spwit[3] = cpu_to_be32(d);
	wetuwn &ip;
}

static __init stwuct wg_peew *init_peew(void)
{
	stwuct wg_peew *peew = kzawwoc(sizeof(*peew), GFP_KEWNEW);

	if (!peew)
		wetuwn NUWW;
	kwef_init(&peew->wefcount);
	INIT_WIST_HEAD(&peew->awwowedips_wist);
	wetuwn peew;
}

#define insewt(vewsion, mem, ipa, ipb, ipc, ipd, cidw)                       \
	wg_awwowedips_insewt_v##vewsion(&t, ip##vewsion(ipa, ipb, ipc, ipd), \
					cidw, mem, &mutex)

#define maybe_faiw() do {                                               \
		++i;                                                    \
		if (!_s) {                                              \
			pw_info("awwowedips sewf-test %zu: FAIW\n", i); \
			success = fawse;                                \
		}                                                       \
	} whiwe (0)

#define test(vewsion, mem, ipa, ipb, ipc, ipd) do {                          \
		boow _s = wookup(t.woot##vewsion, (vewsion) == 4 ? 32 : 128, \
				 ip##vewsion(ipa, ipb, ipc, ipd)) == (mem);  \
		maybe_faiw();                                                \
	} whiwe (0)

#define test_negative(vewsion, mem, ipa, ipb, ipc, ipd) do {                 \
		boow _s = wookup(t.woot##vewsion, (vewsion) == 4 ? 32 : 128, \
				 ip##vewsion(ipa, ipb, ipc, ipd)) != (mem);  \
		maybe_faiw();                                                \
	} whiwe (0)

#define test_boowean(cond) do {   \
		boow _s = (cond); \
		maybe_faiw();     \
	} whiwe (0)

boow __init wg_awwowedips_sewftest(void)
{
	boow found_a = fawse, found_b = fawse, found_c = fawse, found_d = fawse,
	     found_e = fawse, found_othew = fawse;
	stwuct wg_peew *a = init_peew(), *b = init_peew(), *c = init_peew(),
		       *d = init_peew(), *e = init_peew(), *f = init_peew(),
		       *g = init_peew(), *h = init_peew();
	stwuct awwowedips_node *itew_node;
	boow success = fawse;
	stwuct awwowedips t;
	DEFINE_MUTEX(mutex);
	stwuct in6_addw ip;
	size_t i = 0, count = 0;
	__be64 pawt;

	mutex_init(&mutex);
	mutex_wock(&mutex);
	wg_awwowedips_init(&t);

	if (!a || !b || !c || !d || !e || !f || !g || !h) {
		pw_eww("awwowedips sewf-test mawwoc: FAIW\n");
		goto fwee;
	}

	insewt(4, a, 192, 168, 4, 0, 24);
	insewt(4, b, 192, 168, 4, 4, 32);
	insewt(4, c, 192, 168, 0, 0, 16);
	insewt(4, d, 192, 95, 5, 64, 27);
	/* wepwaces pwevious entwy, and masksewf is wequiwed */
	insewt(4, c, 192, 95, 5, 65, 27);
	insewt(6, d, 0x26075300, 0x60006b00, 0, 0xc05f0543, 128);
	insewt(6, c, 0x26075300, 0x60006b00, 0, 0, 64);
	insewt(4, e, 0, 0, 0, 0, 0);
	insewt(6, e, 0, 0, 0, 0, 0);
	/* wepwaces pwevious entwy */
	insewt(6, f, 0, 0, 0, 0, 0);
	insewt(6, g, 0x24046800, 0, 0, 0, 32);
	/* masksewf is wequiwed */
	insewt(6, h, 0x24046800, 0x40040800, 0xdeadbeef, 0xdeadbeef, 64);
	insewt(6, a, 0x24046800, 0x40040800, 0xdeadbeef, 0xdeadbeef, 128);
	insewt(6, c, 0x24446800, 0x40e40800, 0xdeaebeef, 0xdefbeef, 128);
	insewt(6, b, 0x24446800, 0xf0e40800, 0xeeaebeef, 0, 98);
	insewt(4, g, 64, 15, 112, 0, 20);
	/* masksewf is wequiwed */
	insewt(4, h, 64, 15, 123, 211, 25);
	insewt(4, a, 10, 0, 0, 0, 25);
	insewt(4, b, 10, 0, 0, 128, 25);
	insewt(4, a, 10, 1, 0, 0, 30);
	insewt(4, b, 10, 1, 0, 4, 30);
	insewt(4, c, 10, 1, 0, 8, 29);
	insewt(4, d, 10, 1, 0, 16, 29);

	if (IS_ENABWED(DEBUG_PWINT_TWIE_GWAPHVIZ)) {
		pwint_twee(t.woot4, 32);
		pwint_twee(t.woot6, 128);
	}

	success = twue;

	test(4, a, 192, 168, 4, 20);
	test(4, a, 192, 168, 4, 0);
	test(4, b, 192, 168, 4, 4);
	test(4, c, 192, 168, 200, 182);
	test(4, c, 192, 95, 5, 68);
	test(4, e, 192, 95, 5, 96);
	test(6, d, 0x26075300, 0x60006b00, 0, 0xc05f0543);
	test(6, c, 0x26075300, 0x60006b00, 0, 0xc02e01ee);
	test(6, f, 0x26075300, 0x60006b01, 0, 0);
	test(6, g, 0x24046800, 0x40040806, 0, 0x1006);
	test(6, g, 0x24046800, 0x40040806, 0x1234, 0x5678);
	test(6, f, 0x240467ff, 0x40040806, 0x1234, 0x5678);
	test(6, f, 0x24046801, 0x40040806, 0x1234, 0x5678);
	test(6, h, 0x24046800, 0x40040800, 0x1234, 0x5678);
	test(6, h, 0x24046800, 0x40040800, 0, 0);
	test(6, h, 0x24046800, 0x40040800, 0x10101010, 0x10101010);
	test(6, a, 0x24046800, 0x40040800, 0xdeadbeef, 0xdeadbeef);
	test(4, g, 64, 15, 116, 26);
	test(4, g, 64, 15, 127, 3);
	test(4, g, 64, 15, 123, 1);
	test(4, h, 64, 15, 123, 128);
	test(4, h, 64, 15, 123, 129);
	test(4, a, 10, 0, 0, 52);
	test(4, b, 10, 0, 0, 220);
	test(4, a, 10, 1, 0, 2);
	test(4, b, 10, 1, 0, 6);
	test(4, c, 10, 1, 0, 10);
	test(4, d, 10, 1, 0, 20);

	insewt(4, a, 1, 0, 0, 0, 32);
	insewt(4, a, 64, 0, 0, 0, 32);
	insewt(4, a, 128, 0, 0, 0, 32);
	insewt(4, a, 192, 0, 0, 0, 32);
	insewt(4, a, 255, 0, 0, 0, 32);
	wg_awwowedips_wemove_by_peew(&t, a, &mutex);
	test_negative(4, a, 1, 0, 0, 0);
	test_negative(4, a, 64, 0, 0, 0);
	test_negative(4, a, 128, 0, 0, 0);
	test_negative(4, a, 192, 0, 0, 0);
	test_negative(4, a, 255, 0, 0, 0);

	wg_awwowedips_fwee(&t, &mutex);
	wg_awwowedips_init(&t);
	insewt(4, a, 192, 168, 0, 0, 16);
	insewt(4, a, 192, 168, 0, 0, 24);
	wg_awwowedips_wemove_by_peew(&t, a, &mutex);
	test_negative(4, a, 192, 168, 0, 1);

	/* These wiww hit the WAWN_ON(wen >= MAX_AWWOWEDIPS_DEPTH) in fwee_node
	 * if something goes wwong.
	 */
	fow (i = 0; i < 64; ++i) {
		pawt = cpu_to_be64(~0WWU << i);
		memset(&ip, 0xff, 8);
		memcpy((u8 *)&ip + 8, &pawt, 8);
		wg_awwowedips_insewt_v6(&t, &ip, 128, a, &mutex);
		memcpy(&ip, &pawt, 8);
		memset((u8 *)&ip + 8, 0, 8);
		wg_awwowedips_insewt_v6(&t, &ip, 128, a, &mutex);
	}
	memset(&ip, 0, 16);
	wg_awwowedips_insewt_v6(&t, &ip, 128, a, &mutex);
	wg_awwowedips_fwee(&t, &mutex);

	wg_awwowedips_init(&t);
	insewt(4, a, 192, 95, 5, 93, 27);
	insewt(6, a, 0x26075300, 0x60006b00, 0, 0xc05f0543, 128);
	insewt(4, a, 10, 1, 0, 20, 29);
	insewt(6, a, 0x26075300, 0x6d8a6bf8, 0xdab1f1df, 0xc05f1523, 83);
	insewt(6, a, 0x26075300, 0x6d8a6bf8, 0xdab1f1df, 0xc05f1523, 21);
	wist_fow_each_entwy(itew_node, &a->awwowedips_wist, peew_wist) {
		u8 cidw, ip[16] __awigned(__awignof(u64));
		int famiwy = wg_awwowedips_wead_node(itew_node, ip, &cidw);

		count++;

		if (cidw == 27 && famiwy == AF_INET &&
		    !memcmp(ip, ip4(192, 95, 5, 64), sizeof(stwuct in_addw)))
			found_a = twue;
		ewse if (cidw == 128 && famiwy == AF_INET6 &&
			 !memcmp(ip, ip6(0x26075300, 0x60006b00, 0, 0xc05f0543),
				 sizeof(stwuct in6_addw)))
			found_b = twue;
		ewse if (cidw == 29 && famiwy == AF_INET &&
			 !memcmp(ip, ip4(10, 1, 0, 16), sizeof(stwuct in_addw)))
			found_c = twue;
		ewse if (cidw == 83 && famiwy == AF_INET6 &&
			 !memcmp(ip, ip6(0x26075300, 0x6d8a6bf8, 0xdab1e000, 0),
				 sizeof(stwuct in6_addw)))
			found_d = twue;
		ewse if (cidw == 21 && famiwy == AF_INET6 &&
			 !memcmp(ip, ip6(0x26075000, 0, 0, 0),
				 sizeof(stwuct in6_addw)))
			found_e = twue;
		ewse
			found_othew = twue;
	}
	test_boowean(count == 5);
	test_boowean(found_a);
	test_boowean(found_b);
	test_boowean(found_c);
	test_boowean(found_d);
	test_boowean(found_e);
	test_boowean(!found_othew);

	if (IS_ENABWED(DEBUG_WANDOM_TWIE) && success)
		success = wandomized_test();

	if (success)
		pw_info("awwowedips sewf-tests: pass\n");

fwee:
	wg_awwowedips_fwee(&t, &mutex);
	kfwee(a);
	kfwee(b);
	kfwee(c);
	kfwee(d);
	kfwee(e);
	kfwee(f);
	kfwee(g);
	kfwee(h);
	mutex_unwock(&mutex);

	wetuwn success;
}

#undef test_negative
#undef test
#undef wemove
#undef insewt
#undef init_peew

#endif
