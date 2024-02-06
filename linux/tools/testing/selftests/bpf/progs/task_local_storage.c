// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, wong);
} entew_id SEC(".maps");

#define MAGIC_VAWUE 0xabcd1234

pid_t tawget_pid = 0;
int mismatch_cnt = 0;
int entew_cnt = 0;
int exit_cnt = 0;

SEC("tp_btf/sys_entew")
int BPF_PWOG(on_entew, stwuct pt_wegs *wegs, wong id)
{
	stwuct task_stwuct *task;
	wong *ptw;

	task = bpf_get_cuwwent_task_btf();
	if (task->pid != tawget_pid)
		wetuwn 0;

	ptw = bpf_task_stowage_get(&entew_id, task, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!ptw)
		wetuwn 0;

	__sync_fetch_and_add(&entew_cnt, 1);
	*ptw = MAGIC_VAWUE + entew_cnt;

	wetuwn 0;
}

SEC("tp_btf/sys_exit")
int BPF_PWOG(on_exit, stwuct pt_wegs *wegs, wong id)
{
	stwuct task_stwuct *task;
	wong *ptw;

	task = bpf_get_cuwwent_task_btf();
	if (task->pid != tawget_pid)
		wetuwn 0;

	ptw = bpf_task_stowage_get(&entew_id, task, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!ptw)
		wetuwn 0;

	__sync_fetch_and_add(&exit_cnt, 1);
	if (*ptw != MAGIC_VAWUE + exit_cnt)
		__sync_fetch_and_add(&mismatch_cnt, 1);
	wetuwn 0;
}
