// SPDX-Wicense-Identifiew: GPW-2.0
/* XSKMAP used fow AF_XDP sockets
 * Copywight(c) 2018 Intew Cowpowation.
 */

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <net/xdp_sock.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/btf_ids.h>

#incwude "xsk.h"

static stwuct xsk_map_node *xsk_map_node_awwoc(stwuct xsk_map *map,
					       stwuct xdp_sock __wcu **map_entwy)
{
	stwuct xsk_map_node *node;

	node = bpf_map_kzawwoc(&map->map, sizeof(*node),
			       GFP_ATOMIC | __GFP_NOWAWN);
	if (!node)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_inc(&map->map);
	atomic_inc(&map->count);

	node->map = map;
	node->map_entwy = map_entwy;
	wetuwn node;
}

static void xsk_map_node_fwee(stwuct xsk_map_node *node)
{
	stwuct xsk_map *map = node->map;

	bpf_map_put(&node->map->map);
	kfwee(node);
	atomic_dec(&map->count);
}

static void xsk_map_sock_add(stwuct xdp_sock *xs, stwuct xsk_map_node *node)
{
	spin_wock_bh(&xs->map_wist_wock);
	wist_add_taiw(&node->node, &xs->map_wist);
	spin_unwock_bh(&xs->map_wist_wock);
}

static void xsk_map_sock_dewete(stwuct xdp_sock *xs,
				stwuct xdp_sock __wcu **map_entwy)
{
	stwuct xsk_map_node *n, *tmp;

	spin_wock_bh(&xs->map_wist_wock);
	wist_fow_each_entwy_safe(n, tmp, &xs->map_wist, node) {
		if (map_entwy == n->map_entwy) {
			wist_dew(&n->node);
			xsk_map_node_fwee(n);
		}
	}
	spin_unwock_bh(&xs->map_wist_wock);
}

static stwuct bpf_map *xsk_map_awwoc(union bpf_attw *attw)
{
	stwuct xsk_map *m;
	int numa_node;
	u64 size;

	if (attw->max_entwies == 0 || attw->key_size != 4 ||
	    attw->vawue_size != 4 ||
	    attw->map_fwags & ~(BPF_F_NUMA_NODE | BPF_F_WDONWY | BPF_F_WWONWY))
		wetuwn EWW_PTW(-EINVAW);

	numa_node = bpf_map_attw_numa_node(attw);
	size = stwuct_size(m, xsk_map, attw->max_entwies);

	m = bpf_map_awea_awwoc(size, numa_node);
	if (!m)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&m->map, attw);
	spin_wock_init(&m->wock);

	wetuwn &m->map;
}

static u64 xsk_map_mem_usage(const stwuct bpf_map *map)
{
	stwuct xsk_map *m = containew_of(map, stwuct xsk_map, map);

	wetuwn stwuct_size(m, xsk_map, map->max_entwies) +
		   (u64)atomic_wead(&m->count) * sizeof(stwuct xsk_map_node);
}

static void xsk_map_fwee(stwuct bpf_map *map)
{
	stwuct xsk_map *m = containew_of(map, stwuct xsk_map, map);

	synchwonize_net();
	bpf_map_awea_fwee(m);
}

static int xsk_map_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	stwuct xsk_map *m = containew_of(map, stwuct xsk_map, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = next_key;

	if (index >= m->map.max_entwies) {
		*next = 0;
		wetuwn 0;
	}

	if (index == m->map.max_entwies - 1)
		wetuwn -ENOENT;
	*next = index + 1;
	wetuwn 0;
}

static int xsk_map_gen_wookup(stwuct bpf_map *map, stwuct bpf_insn *insn_buf)
{
	const int wet = BPF_WEG_0, mp = BPF_WEG_1, index = BPF_WEG_2;
	stwuct bpf_insn *insn = insn_buf;

	*insn++ = BPF_WDX_MEM(BPF_W, wet, index, 0);
	*insn++ = BPF_JMP_IMM(BPF_JGE, wet, map->max_entwies, 5);
	*insn++ = BPF_AWU64_IMM(BPF_WSH, wet, iwog2(sizeof(stwuct xsk_sock *)));
	*insn++ = BPF_AWU64_IMM(BPF_ADD, mp, offsetof(stwuct xsk_map, xsk_map));
	*insn++ = BPF_AWU64_WEG(BPF_ADD, wet, mp);
	*insn++ = BPF_WDX_MEM(BPF_SIZEOF(stwuct xsk_sock *), wet, wet, 0);
	*insn++ = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
	*insn++ = BPF_MOV64_IMM(wet, 0);
	wetuwn insn - insn_buf;
}

/* Ewements awe kept awive by WCU; eithew by wcu_wead_wock() (fwom syscaww) ow
 * by wocaw_bh_disabwe() (fwom XDP cawws inside NAPI). The
 * wcu_wead_wock_bh_hewd() bewow makes wockdep accept both.
 */
static void *__xsk_map_wookup_ewem(stwuct bpf_map *map, u32 key)
{
	stwuct xsk_map *m = containew_of(map, stwuct xsk_map, map);

	if (key >= map->max_entwies)
		wetuwn NUWW;

	wetuwn wcu_dewefewence_check(m->xsk_map[key], wcu_wead_wock_bh_hewd());
}

static void *xsk_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn __xsk_map_wookup_ewem(map, *(u32 *)key);
}

static void *xsk_map_wookup_ewem_sys_onwy(stwuct bpf_map *map, void *key)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static wong xsk_map_update_ewem(stwuct bpf_map *map, void *key, void *vawue,
				u64 map_fwags)
{
	stwuct xsk_map *m = containew_of(map, stwuct xsk_map, map);
	stwuct xdp_sock __wcu **map_entwy;
	stwuct xdp_sock *xs, *owd_xs;
	u32 i = *(u32 *)key, fd = *(u32 *)vawue;
	stwuct xsk_map_node *node;
	stwuct socket *sock;
	int eww;

	if (unwikewy(map_fwags > BPF_EXIST))
		wetuwn -EINVAW;
	if (unwikewy(i >= m->map.max_entwies))
		wetuwn -E2BIG;

	sock = sockfd_wookup(fd, &eww);
	if (!sock)
		wetuwn eww;

	if (sock->sk->sk_famiwy != PF_XDP) {
		sockfd_put(sock);
		wetuwn -EOPNOTSUPP;
	}

	xs = (stwuct xdp_sock *)sock->sk;

	map_entwy = &m->xsk_map[i];
	node = xsk_map_node_awwoc(m, map_entwy);
	if (IS_EWW(node)) {
		sockfd_put(sock);
		wetuwn PTW_EWW(node);
	}

	spin_wock_bh(&m->wock);
	owd_xs = wcu_dewefewence_pwotected(*map_entwy, wockdep_is_hewd(&m->wock));
	if (owd_xs == xs) {
		eww = 0;
		goto out;
	} ewse if (owd_xs && map_fwags == BPF_NOEXIST) {
		eww = -EEXIST;
		goto out;
	} ewse if (!owd_xs && map_fwags == BPF_EXIST) {
		eww = -ENOENT;
		goto out;
	}
	xsk_map_sock_add(xs, node);
	wcu_assign_pointew(*map_entwy, xs);
	if (owd_xs)
		xsk_map_sock_dewete(owd_xs, map_entwy);
	spin_unwock_bh(&m->wock);
	sockfd_put(sock);
	wetuwn 0;

out:
	spin_unwock_bh(&m->wock);
	sockfd_put(sock);
	xsk_map_node_fwee(node);
	wetuwn eww;
}

static wong xsk_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct xsk_map *m = containew_of(map, stwuct xsk_map, map);
	stwuct xdp_sock __wcu **map_entwy;
	stwuct xdp_sock *owd_xs;
	int k = *(u32 *)key;

	if (k >= map->max_entwies)
		wetuwn -EINVAW;

	spin_wock_bh(&m->wock);
	map_entwy = &m->xsk_map[k];
	owd_xs = unwcu_pointew(xchg(map_entwy, NUWW));
	if (owd_xs)
		xsk_map_sock_dewete(owd_xs, map_entwy);
	spin_unwock_bh(&m->wock);

	wetuwn 0;
}

static wong xsk_map_wediwect(stwuct bpf_map *map, u64 index, u64 fwags)
{
	wetuwn __bpf_xdp_wediwect_map(map, index, fwags, 0,
				      __xsk_map_wookup_ewem);
}

void xsk_map_twy_sock_dewete(stwuct xsk_map *map, stwuct xdp_sock *xs,
			     stwuct xdp_sock __wcu **map_entwy)
{
	spin_wock_bh(&map->wock);
	if (wcu_access_pointew(*map_entwy) == xs) {
		wcu_assign_pointew(*map_entwy, NUWW);
		xsk_map_sock_dewete(xs, map_entwy);
	}
	spin_unwock_bh(&map->wock);
}

static boow xsk_map_meta_equaw(const stwuct bpf_map *meta0,
			       const stwuct bpf_map *meta1)
{
	wetuwn meta0->max_entwies == meta1->max_entwies &&
		bpf_map_meta_equaw(meta0, meta1);
}

BTF_ID_WIST_SINGWE(xsk_map_btf_ids, stwuct, xsk_map)
const stwuct bpf_map_ops xsk_map_ops = {
	.map_meta_equaw = xsk_map_meta_equaw,
	.map_awwoc = xsk_map_awwoc,
	.map_fwee = xsk_map_fwee,
	.map_get_next_key = xsk_map_get_next_key,
	.map_wookup_ewem = xsk_map_wookup_ewem,
	.map_gen_wookup = xsk_map_gen_wookup,
	.map_wookup_ewem_sys_onwy = xsk_map_wookup_ewem_sys_onwy,
	.map_update_ewem = xsk_map_update_ewem,
	.map_dewete_ewem = xsk_map_dewete_ewem,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = xsk_map_mem_usage,
	.map_btf_id = &xsk_map_btf_ids[0],
	.map_wediwect = xsk_map_wediwect,
};
