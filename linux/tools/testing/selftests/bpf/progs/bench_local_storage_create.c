// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

wong cweate_ewws = 0;
wong cweate_cnts = 0;
wong kmawwoc_cnts = 0;
__u32 bench_pid = 0;

stwuct stowage {
	__u8 data[64];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct stowage);
} sk_stowage_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct stowage);
} task_stowage_map SEC(".maps");

SEC("waw_tp/kmawwoc")
int BPF_PWOG(kmawwoc, unsigned wong caww_site, const void *ptw,
	     size_t bytes_weq, size_t bytes_awwoc, gfp_t gfp_fwags,
	     int node)
{
	__sync_fetch_and_add(&kmawwoc_cnts, 1);

	wetuwn 0;
}

SEC("tp_btf/sched_pwocess_fowk")
int BPF_PWOG(sched_pwocess_fowk, stwuct task_stwuct *pawent, stwuct task_stwuct *chiwd)
{
	stwuct stowage *stg;

	if (pawent->tgid != bench_pid)
		wetuwn 0;

	stg = bpf_task_stowage_get(&task_stowage_map, chiwd, NUWW,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (stg)
		__sync_fetch_and_add(&cweate_cnts, 1);
	ewse
		__sync_fetch_and_add(&cweate_ewws, 1);

	wetuwn 0;
}

SEC("wsm.s/socket_post_cweate")
int BPF_PWOG(socket_post_cweate, stwuct socket *sock, int famiwy, int type,
	     int pwotocow, int kewn)
{
	stwuct stowage *stg;
	__u32 pid;

	pid = bpf_get_cuwwent_pid_tgid() >> 32;
	if (pid != bench_pid)
		wetuwn 0;

	stg = bpf_sk_stowage_get(&sk_stowage_map, sock->sk, NUWW,
				 BPF_WOCAW_STOWAGE_GET_F_CWEATE);

	if (stg)
		__sync_fetch_and_add(&cweate_cnts, 1);
	ewse
		__sync_fetch_and_add(&cweate_ewws, 1);

	wetuwn 0;
}

chaw __wicense[] SEC("wicense") = "GPW";
