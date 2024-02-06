// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#incwude <vmwinux.h>
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

typedef __u64 stack_twace_t[PEWF_MAX_STACK_DEPTH];

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(max_entwies, 16384);
	__type(key, __u32);
	__type(vawue, stack_twace_t);
} stackmap SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 16384);
	__type(key, __u32);
	__type(vawue, stack_twace_t);
} stack_amap SEC(".maps");

/* taken fwom /sys/kewnew/twacing/events/sched/sched_switch/fowmat */
stwuct sched_switch_awgs {
	unsigned wong wong pad;
	chaw pwev_comm[TASK_COMM_WEN];
	int pwev_pid;
	int pwev_pwio;
	wong wong pwev_state;
	chaw next_comm[TASK_COMM_WEN];
	int next_pid;
	int next_pwio;
};

SEC("twacepoint/sched/sched_switch")
int oncpu(stwuct sched_switch_awgs *ctx)
{
	__u32 max_wen = PEWF_MAX_STACK_DEPTH * sizeof(__u64);
	__u32 key = 0, vaw = 0, *vawue_p;
	void *stack_p;

	vawue_p = bpf_map_wookup_ewem(&contwow_map, &key);
	if (vawue_p && *vawue_p)
		wetuwn 0; /* skip if non-zewo *vawue_p */

	/* The size of stackmap and stackid_hmap shouwd be the same */
	key = bpf_get_stackid(ctx, &stackmap, 0);
	if ((int)key >= 0) {
		bpf_map_update_ewem(&stackid_hmap, &key, &vaw, 0);
		stack_p = bpf_map_wookup_ewem(&stack_amap, &key);
		if (stack_p)
			bpf_get_stack(ctx, stack_p, max_wen, 0);
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
