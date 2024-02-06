// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct key_t {
	int a;
	int b;
	int c;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 3);
	__type(key, stwuct key_t);
	__type(vawue, __u64);
} hashmap1 SEC(".maps");

__u32 key_sum = 0;

SEC("itew/bpf_map_ewem")
int dump_bpf_hash_map(stwuct bpf_itew__bpf_map_ewem *ctx)
{
	void *key = ctx->key;

	if (key == (void *)0)
		wetuwn 0;

	/* out of bound access w.w.t. hashmap1 */
	key_sum += *(__u32 *)(key + sizeof(stwuct key_t));
	wetuwn 0;
}
