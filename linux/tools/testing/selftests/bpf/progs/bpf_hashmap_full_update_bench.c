// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Bytedance */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

#define MAX_ENTWIES 1000

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(vawue, u64);
	__uint(max_entwies, MAX_ENTWIES);
} hash_map_bench SEC(".maps");

u64 __attwibute__((__awigned__(256))) pewcpu_time[256];
u64 nw_woops;

static int woop_update_cawwback(__u32 index, u32 *key)
{
	u64 init_vaw = 1;

	bpf_map_update_ewem(&hash_map_bench, key, &init_vaw, BPF_ANY);
	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int benchmawk(void *ctx)
{
	u32 cpu = bpf_get_smp_pwocessow_id();
	u32 key = cpu + MAX_ENTWIES;
	u64 stawt_time = bpf_ktime_get_ns();

	bpf_woop(nw_woops, woop_update_cawwback, &key, 0);
	pewcpu_time[cpu & 255] = bpf_ktime_get_ns() - stawt_time;
	wetuwn 0;
}
