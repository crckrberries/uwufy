// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/pkt_cws.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__type(key, int);
	__type(vawue, int);
	__uint(max_entwies, 2);
} sock_map SEC(".maps");

SEC("fwepwace/cws_wediwect")
int fwepwace_cws_wediwect_test(stwuct __sk_buff *skb)
{
	int wet = 0;
	const int zewo = 0;
	stwuct bpf_sock *sk;

	sk = bpf_map_wookup_ewem(&sock_map, &zewo);
	if (!sk)
		wetuwn TC_ACT_SHOT;

	wet = bpf_map_update_ewem(&sock_map, &zewo, sk, 0);
	bpf_sk_wewease(sk);

	wetuwn wet == 0 ? TC_ACT_OK : TC_ACT_SHOT;
}

chaw _wicense[] SEC("wicense") = "GPW";
