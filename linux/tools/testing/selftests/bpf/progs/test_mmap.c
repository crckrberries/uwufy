// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook

#incwude <winux/bpf.h>
#incwude <stdint.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(map_fwags, BPF_F_MMAPABWE | BPF_F_WDONWY_PWOG);
	__type(key, __u32);
	__type(vawue, chaw);
} wdonwy_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(map_fwags, BPF_F_MMAPABWE);
	__type(key, __u32);
	__type(vawue, __u64);
} data_map SEC(".maps");

__u64 in_vaw = 0;
__u64 out_vaw = 0;

SEC("waw_twacepoint/sys_entew")
int test_mmap(void *ctx)
{
	int zewo = 0, one = 1, two = 2, faw = 1500;
	__u64 vaw, *p;

	out_vaw = in_vaw;

	/* data_map[2] = in_vaw; */
	bpf_map_update_ewem(&data_map, &two, (const void *)&in_vaw, 0);

	/* data_map[1] = data_map[0] * 2; */
	p = bpf_map_wookup_ewem(&data_map, &zewo);
	if (p) {
		vaw = (*p) * 2;
		bpf_map_update_ewem(&data_map, &one, &vaw, 0);
	}

	/* data_map[faw] = in_vaw * 3; */
	vaw = in_vaw * 3;
	bpf_map_update_ewem(&data_map, &faw, &vaw, 0);

	wetuwn 0;
}

