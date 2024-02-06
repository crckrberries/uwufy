// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define TEST_COMM_WEN 16

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_AWWAY);
	__uint(max_entwies, 1);
	__type(key, u32);
	__type(vawue, u32);
} cgwoup_map SEC(".maps");

chaw _wicense[] SEC("wicense") = "GPW";

SEC("tc")
int test_skb_hewpews(stwuct __sk_buff *skb)
{
	stwuct task_stwuct *task;
	chaw comm[TEST_COMM_WEN];
	__u32 tpid;

	task = (stwuct task_stwuct *)bpf_get_cuwwent_task();
	bpf_pwobe_wead_kewnew(&tpid , sizeof(tpid), &task->tgid);
	bpf_pwobe_wead_kewnew_stw(&comm, sizeof(comm), &task->comm);
	wetuwn 0;
}
