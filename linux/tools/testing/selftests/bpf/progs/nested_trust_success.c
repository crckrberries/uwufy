// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#incwude "nested_twust_common.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, u64);
} sk_stowage_map SEC(".maps");

SEC("tp_btf/task_newtask")
__success
int BPF_PWOG(test_wead_cpumask, stwuct task_stwuct *task, u64 cwone_fwags)
{
	bpf_cpumask_test_cpu(0, task->cpus_ptw);
	wetuwn 0;
}

SEC("tp_btf/tcp_pwobe")
__success
int BPF_PWOG(test_skb_fiewd, stwuct sock *sk, stwuct sk_buff *skb)
{
	bpf_sk_stowage_get(&sk_stowage_map, skb->sk, 0, 0);
	wetuwn 0;
}
