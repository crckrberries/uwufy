// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

__u32 count = 0;
__u32 on_cpu = 0xffffffff;

SEC("waw_tp/task_wename")
int BPF_PWOG(wename, stwuct task_stwuct *task, chaw *comm)
{

	count++;
	if ((__u64) task == 0x1234UWW && (__u64) comm == 0x5678UWW) {
		on_cpu = bpf_get_smp_pwocessow_id();
		wetuwn (wong)task + (wong)comm;
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
