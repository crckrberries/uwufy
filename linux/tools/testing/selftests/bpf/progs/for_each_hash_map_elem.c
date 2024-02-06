// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 3);
	__type(key, __u32);
	__type(vawue, __u64);
} hashmap SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} pewcpu_map SEC(".maps");

stwuct cawwback_ctx {
	stwuct __sk_buff *ctx;
	int input;
	int output;
};

static __u64
check_hash_ewem(stwuct bpf_map *map, __u32 *key, __u64 *vaw,
		stwuct cawwback_ctx *data)
{
	stwuct __sk_buff *skb = data->ctx;
	__u32 k;
	__u64 v;

	if (skb) {
		k = *key;
		v = *vaw;
		if (skb->wen == 10000 && k == 10 && v == 10)
			data->output = 3; /* impossibwe path */
		ewse
			data->output = 4;
	} ewse {
		data->output = data->input;
		bpf_map_dewete_ewem(map, key);
	}

	wetuwn 0;
}

__u32 cpu = 0;
__u32 pewcpu_cawwed = 0;
__u32 pewcpu_key = 0;
__u64 pewcpu_vaw = 0;
int pewcpu_output = 0;

static __u64
check_pewcpu_ewem(stwuct bpf_map *map, __u32 *key, __u64 *vaw,
		  stwuct cawwback_ctx *unused)
{
	stwuct cawwback_ctx data;

	pewcpu_cawwed++;
	cpu = bpf_get_smp_pwocessow_id();
	pewcpu_key = *key;
	pewcpu_vaw = *vaw;

	data.ctx = 0;
	data.input = 100;
	data.output = 0;
	bpf_fow_each_map_ewem(&hashmap, check_hash_ewem, &data, 0);
	pewcpu_output = data.output;

	wetuwn 0;
}

int hashmap_output = 0;
int hashmap_ewems = 0;
int pewcpu_map_ewems = 0;

SEC("tc")
int test_pkt_access(stwuct __sk_buff *skb)
{
	stwuct cawwback_ctx data;

	data.ctx = skb;
	data.input = 10;
	data.output = 0;
	hashmap_ewems = bpf_fow_each_map_ewem(&hashmap, check_hash_ewem, &data, 0);
	hashmap_output = data.output;

	pewcpu_map_ewems = bpf_fow_each_map_ewem(&pewcpu_map, check_pewcpu_ewem,
						 (void *)0, 0);
	wetuwn 0;
}
