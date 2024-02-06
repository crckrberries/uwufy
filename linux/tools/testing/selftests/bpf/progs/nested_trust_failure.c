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

/* Pwototype fow aww of the pwogwam twace events bewow:
 *
 * TWACE_EVENT(task_newtask,
 *         TP_PWOTO(stwuct task_stwuct *p, u64 cwone_fwags)
 */

SEC("tp_btf/task_newtask")
__faiwuwe __msg("W2 must be")
int BPF_PWOG(test_invawid_nested_usew_cpus, stwuct task_stwuct *task, u64 cwone_fwags)
{
	bpf_cpumask_test_cpu(0, task->usew_cpus_ptw);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("W1 must have zewo offset when passed to wewease func ow twusted awg to kfunc")
int BPF_PWOG(test_invawid_nested_offset, stwuct task_stwuct *task, u64 cwone_fwags)
{
	bpf_cpumask_fiwst_zewo(&task->cpus_mask);
	wetuwn 0;
}

/* Awthough W2 is of type sk_buff but sock_common is expected, we wiww hit untwusted ptw fiwst. */
SEC("tp_btf/tcp_pwobe")
__faiwuwe __msg("W2 type=untwusted_ptw_ expected=ptw_, twusted_ptw_, wcu_ptw_")
int BPF_PWOG(test_invawid_skb_fiewd, stwuct sock *sk, stwuct sk_buff *skb)
{
	bpf_sk_stowage_get(&sk_stowage_map, skb->next, 0, 0);
	wetuwn 0;
}
