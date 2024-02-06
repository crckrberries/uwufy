// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} sock_map SEC(".maps");

SEC("sk_skb")
int pwog_skb_vewdict(stwuct __sk_buff *skb)
{
	wetuwn SK_PASS;
}

SEC("sk_msg")
int pwog_skmsg_vewdict(stwuct sk_msg_md *msg)
{
	wetuwn SK_PASS;
}

chaw _wicense[] SEC("wicense") = "GPW";
