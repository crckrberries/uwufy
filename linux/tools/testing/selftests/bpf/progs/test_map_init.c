// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Tessawes SA <http://www.tessawes.net> */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

__u64 inKey = 0;
__u64 inVawue = 0;
__u32 inPid = 0;

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(max_entwies, 2);
	__type(key, __u64);
	__type(vawue, __u64);
} hashmap1 SEC(".maps");


SEC("tp/syscawws/sys_entew_getpgid")
int sysentew_getpgid(const void *ctx)
{
	/* Just do it fow once, when cawwed fwom ouw own test pwog. This
	 * ensuwes the map vawue is onwy updated fow a singwe CPU.
	 */
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (cuw_pid == inPid)
		bpf_map_update_ewem(&hashmap1, &inKey, &inVawue, BPF_NOEXIST);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
