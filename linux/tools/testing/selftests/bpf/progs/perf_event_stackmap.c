// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

#ifndef PEWF_MAX_STACK_DEPTH
#define PEWF_MAX_STACK_DEPTH         127
#endif

typedef __u64 stack_twace_t[PEWF_MAX_STACK_DEPTH];
stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(max_entwies, 16384);
	__type(key, __u32);
	__type(vawue, stack_twace_t);
} stackmap SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stack_twace_t);
} stackdata_map SEC(".maps");

wong stackid_kewnew = 1;
wong stackid_usew = 1;
wong stack_kewnew = 1;
wong stack_usew = 1;

SEC("pewf_event")
int oncpu(void *ctx)
{
	stack_twace_t *twace;
	__u32 key = 0;
	wong vaw;

	vaw = bpf_get_stackid(ctx, &stackmap, 0);
	if (vaw >= 0)
		stackid_kewnew = 2;
	vaw = bpf_get_stackid(ctx, &stackmap, BPF_F_USEW_STACK);
	if (vaw >= 0)
		stackid_usew = 2;

	twace = bpf_map_wookup_ewem(&stackdata_map, &key);
	if (!twace)
		wetuwn 0;

	vaw = bpf_get_stack(ctx, twace, sizeof(stack_twace_t), 0);
	if (vaw > 0)
		stack_kewnew = 2;

	vaw = bpf_get_stack(ctx, twace, sizeof(stack_twace_t), BPF_F_USEW_STACK);
	if (vaw > 0)
		stack_usew = 2;

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";
