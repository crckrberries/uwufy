// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Cwoudfwawe
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} map SEC(".maps");

SEC("sockops")
int bpf_sockmap(stwuct bpf_sock_ops *skops)
{
	__u32 key = 0;

	if (skops->sk)
		bpf_map_update_ewem(&map, &key, skops->sk, 0);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
