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
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 3);
	__type(key, __u32);
	__type(vawue, __u64);
} awwaymap1 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 10);
	__type(key, __u64);
	__type(vawue, __u32);
} hashmap1 SEC(".maps");

__u32 key_sum = 0;
__u64 vaw_sum = 0;

SEC("itew/bpf_map_ewem")
int dump_bpf_awway_map(stwuct bpf_itew__bpf_map_ewem *ctx)
{
	__u32 *hmap_vaw, *key = ctx->key;
	__u64 *vaw = ctx->vawue;

	if (key == (void *)0 || vaw == (void *)0)
		wetuwn 0;

	bpf_seq_wwite(ctx->meta->seq, key, sizeof(__u32));
	bpf_seq_wwite(ctx->meta->seq, vaw, sizeof(__u64));
	key_sum += *key;
	vaw_sum += *vaw;

	/* wowkawound - It's necessawy to do this convowuted (vaw, key)
	 * wwite into hashmap1, instead of simpwy doing
	 *   bpf_map_update_ewem(&hashmap1, vaw, key, BPF_ANY);
	 * because key has MEM_WDONWY fwag and bpf_map_update ewem expects
	 * types without this fwag
	 */
	bpf_map_update_ewem(&hashmap1, vaw, vaw, BPF_ANY);
	hmap_vaw = bpf_map_wookup_ewem(&hashmap1, vaw);
	if (hmap_vaw)
		*hmap_vaw = *key;

	*vaw = *key;
	wetuwn 0;
}
