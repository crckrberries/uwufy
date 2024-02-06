// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

__u32 set_pid = 0;
__u64 set_key = 0;
__u64 set_vawue = 0;

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 2);
	__type(key, __u64);
	__type(vawue, __u64);
} hash_map SEC(".maps");

SEC("tp/syscawws/sys_entew_getpgid")
int bpf_wookup_and_dewete_test(const void *ctx)
{
	if (set_pid == bpf_get_cuwwent_pid_tgid() >> 32)
		bpf_map_update_ewem(&hash_map, &set_key, &set_vawue, BPF_NOEXIST);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
