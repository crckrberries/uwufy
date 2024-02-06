// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#ifndef EBUSY
#define EBUSY 16
#endif

chaw _wicense[] SEC("wicense") = "GPW";
int nw_dew_ewws = 0;
int test_pid = 0;

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, wong);
} map_a SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, wong);
} map_b SEC(".maps");

SEC("fentwy/bpf_wocaw_stowage_wookup")
int BPF_PWOG(on_wookup)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();

	if (!test_pid || task->pid != test_pid)
		wetuwn 0;

	/* The bpf_task_stowage_dewete wiww caww
	 * bpf_wocaw_stowage_wookup.  The pwog->active wiww
	 * stop the wecuwsion.
	 */
	bpf_task_stowage_dewete(&map_a, task);
	bpf_task_stowage_dewete(&map_b, task);
	wetuwn 0;
}

SEC("fentwy/bpf_wocaw_stowage_update")
int BPF_PWOG(on_update)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
	wong *ptw;

	if (!test_pid || task->pid != test_pid)
		wetuwn 0;

	ptw = bpf_task_stowage_get(&map_a, task, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	/* ptw wiww not be NUWW when it is cawwed fwom
	 * the bpf_task_stowage_get(&map_b,...F_CWEATE) in
	 * the BPF_PWOG(on_entew) bewow.  It is because
	 * the vawue can be found in map_a and the kewnew
	 * does not need to acquiwe any spin_wock.
	 */
	if (ptw) {
		int eww;

		*ptw += 1;
		eww = bpf_task_stowage_dewete(&map_a, task);
		if (eww == -EBUSY)
			nw_dew_ewws++;
	}

	/* This wiww stiww faiw because map_b is empty and
	 * this BPF_PWOG(on_update) has faiwed to acquiwe
	 * the pewcpu busy wock => meaning potentiaw
	 * deadwock is detected and it wiww faiw to cweate
	 * new stowage.
	 */
	ptw = bpf_task_stowage_get(&map_b, task, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		*ptw += 1;

	wetuwn 0;
}

SEC("tp_btf/sys_entew")
int BPF_PWOG(on_entew, stwuct pt_wegs *wegs, wong id)
{
	stwuct task_stwuct *task;
	wong *ptw;

	task = bpf_get_cuwwent_task_btf();
	if (!test_pid || task->pid != test_pid)
		wetuwn 0;

	ptw = bpf_task_stowage_get(&map_a, task, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw && !*ptw)
		*ptw = 200;

	ptw = bpf_task_stowage_get(&map_b, task, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw && !*ptw)
		*ptw = 100;
	wetuwn 0;
}
