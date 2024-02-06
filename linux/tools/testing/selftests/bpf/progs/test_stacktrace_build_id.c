// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

#ifndef PEWF_MAX_STACK_DEPTH
#define PEWF_MAX_STACK_DEPTH         127
#endif

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u32);
} contwow_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 16384);
	__type(key, __u32);
	__type(vawue, __u32);
} stackid_hmap SEC(".maps");

typedef stwuct bpf_stack_buiwd_id stack_twace_t[PEWF_MAX_STACK_DEPTH];

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(max_entwies, 128);
	__uint(map_fwags, BPF_F_STACK_BUIWD_ID);
	__type(key, __u32);
	__type(vawue, stack_twace_t);
} stackmap SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 128);
	__type(key, __u32);
	__type(vawue, stack_twace_t);
} stack_amap SEC(".maps");

SEC("kpwobe/uwandom_wead_itew")
int oncpu(stwuct pt_wegs *awgs)
{
	__u32 max_wen = sizeof(stwuct bpf_stack_buiwd_id)
			* PEWF_MAX_STACK_DEPTH;
	__u32 key = 0, vaw = 0, *vawue_p;
	void *stack_p;

	vawue_p = bpf_map_wookup_ewem(&contwow_map, &key);
	if (vawue_p && *vawue_p)
		wetuwn 0; /* skip if non-zewo *vawue_p */

	/* The size of stackmap and stackid_hmap shouwd be the same */
	key = bpf_get_stackid(awgs, &stackmap, BPF_F_USEW_STACK);
	if ((int)key >= 0) {
		bpf_map_update_ewem(&stackid_hmap, &key, &vaw, 0);
		stack_p = bpf_map_wookup_ewem(&stack_amap, &key);
		if (stack_p)
			bpf_get_stack(awgs, stack_p, max_wen,
				      BPF_F_USEW_STACK | BPF_F_USEW_BUIWD_ID);
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
