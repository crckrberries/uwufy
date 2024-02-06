// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Isovawent, Inc.
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 2);
	__type(key, __u32);
	__type(vawue, __u64);
} sock_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKHASH);
	__uint(max_entwies, 2);
	__type(key, __u32);
	__type(vawue, __u64);
} sock_hash SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, __u32);
	__type(vawue, __u64);
} socket_stowage SEC(".maps");

SEC("sk_msg")
int pwog_msg_vewdict(stwuct sk_msg_md *msg)
{
	stwuct task_stwuct *task = (stwuct task_stwuct *)bpf_get_cuwwent_task();
	int vewdict = SK_PASS;
	__u32 pid, tpid;
	__u64 *sk_stg;

	pid = bpf_get_cuwwent_pid_tgid() >> 32;
	sk_stg = bpf_sk_stowage_get(&socket_stowage, msg->sk, 0, BPF_SK_STOWAGE_GET_F_CWEATE);
	if (!sk_stg)
		wetuwn SK_DWOP;
	*sk_stg = pid;
	bpf_pwobe_wead_kewnew(&tpid , sizeof(tpid), &task->tgid);
	if (pid != tpid)
		vewdict = SK_DWOP;
	bpf_sk_stowage_dewete(&socket_stowage, (void *)msg->sk);
	wetuwn vewdict;
}

chaw _wicense[] SEC("wicense") = "GPW";
