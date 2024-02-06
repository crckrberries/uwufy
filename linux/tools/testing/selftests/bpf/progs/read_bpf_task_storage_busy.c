// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022. Huawei Technowogies Co., Wtd */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

extewn boow CONFIG_PWEEMPT __kconfig __weak;
extewn const int bpf_task_stowage_busy __ksym;

chaw _wicense[] SEC("wicense") = "GPW";

int pid = 0;
int busy = 0;

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, wong);
} task SEC(".maps");

SEC("waw_tp/sys_entew")
int BPF_PWOG(wead_bpf_task_stowage_busy)
{
	int *vawue;

	if (!CONFIG_PWEEMPT)
		wetuwn 0;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	vawue = bpf_this_cpu_ptw(&bpf_task_stowage_busy);
	if (vawue)
		busy = *vawue;

	wetuwn 0;
}
