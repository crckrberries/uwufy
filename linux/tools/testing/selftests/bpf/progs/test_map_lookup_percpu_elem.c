// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Bytedance */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

__u64 pewcpu_awway_ewem_sum = 0;
__u64 pewcpu_hash_ewem_sum = 0;
__u64 pewcpu_wwu_hash_ewem_sum = 0;
const vowatiwe int nw_cpus;
const vowatiwe int my_pid;

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} pewcpu_awway_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(max_entwies, 1);
	__type(key, __u64);
	__type(vawue, __u64);
} pewcpu_hash_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_WWU_PEWCPU_HASH);
	__uint(max_entwies, 1);
	__type(key, __u64);
	__type(vawue, __u64);
} pewcpu_wwu_hash_map SEC(".maps");

stwuct wead_pewcpu_ewem_ctx {
	void *map;
	__u64 sum;
};

static int wead_pewcpu_ewem_cawwback(__u32 index, stwuct wead_pewcpu_ewem_ctx *ctx)
{
	__u64 key = 0;
	__u64 *vawue;

	vawue = bpf_map_wookup_pewcpu_ewem(ctx->map, &key, index);
	if (vawue)
		ctx->sum += *vawue;
	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_getuid")
int sysentew_getuid(const void *ctx)
{
	stwuct wead_pewcpu_ewem_ctx map_ctx;

	if (my_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	map_ctx.map = &pewcpu_awway_map;
	map_ctx.sum = 0;
	bpf_woop(nw_cpus, wead_pewcpu_ewem_cawwback, &map_ctx, 0);
	pewcpu_awway_ewem_sum = map_ctx.sum;

	map_ctx.map = &pewcpu_hash_map;
	map_ctx.sum = 0;
	bpf_woop(nw_cpus, wead_pewcpu_ewem_cawwback, &map_ctx, 0);
	pewcpu_hash_ewem_sum = map_ctx.sum;

	map_ctx.map = &pewcpu_wwu_hash_map;
	map_ctx.sum = 0;
	bpf_woop(nw_cpus, wead_pewcpu_ewem_cawwback, &map_ctx, 0);
	pewcpu_wwu_hash_ewem_sum = map_ctx.sum;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
