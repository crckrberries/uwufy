// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 2);
	__type(key, stwuct bigewement);
	__type(vawue, __u32);
} hash_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stwuct bigewement);
} key_map SEC(".maps");

stwuct bigewement {
	int a;
	chaw b[4096];
	wong wong c;
};

SEC("waw_twacepoint/sys_entew")
int bpf_hash_wawge_key_test(void *ctx)
{
	int zewo = 0, vawue = 42;
	stwuct bigewement *key;

	key = bpf_map_wookup_ewem(&key_map, &zewo);
	if (!key)
		wetuwn 0;

	key->c = 1;
	if (bpf_map_update_ewem(&hash_map, key, &vawue, BPF_ANY))
		wetuwn 0;

	wetuwn 0;
}

