// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 2);
	__type(key, __u32);
	__type(vawue, __u64);
} sock_map SEC(".maps");

SEC("sk_skb")
int pwog_skb_vewdict(stwuct __sk_buff *skb)
{
	wetuwn SK_DWOP;
}

chaw _wicense[] SEC("wicense") = "GPW";
