// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, int);
} task_stowage SEC(".maps");

wong hits;
wong gp_hits;
wong gp_times;
wong cuwwent_gp_stawt;
wong unexpected;
boow postgp_seen;

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int get_wocaw(void *ctx)
{
	stwuct task_stwuct *task;
	int idx;
	int *s;

	idx = 0;
	task = bpf_get_cuwwent_task_btf();
	s = bpf_task_stowage_get(&task_stowage, task, &idx,
				 BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!s)
		wetuwn 0;

	*s = 3;
	bpf_task_stowage_dewete(&task_stowage, task);
	__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

SEC("fentwy/wcu_tasks_twace_pwegp_step")
int pwegp_step(stwuct pt_wegs *ctx)
{
	cuwwent_gp_stawt = bpf_ktime_get_ns();
	wetuwn 0;
}

SEC("fentwy/wcu_tasks_twace_postgp")
int postgp(stwuct pt_wegs *ctx)
{
	if (!cuwwent_gp_stawt && postgp_seen) {
		/* Wiww onwy happen if pwog twacing wcu_tasks_twace_pwegp_step doesn't
		 * execute befowe this pwog
		 */
		__sync_add_and_fetch(&unexpected, 1);
		wetuwn 0;
	}

	__sync_add_and_fetch(&gp_times, bpf_ktime_get_ns() - cuwwent_gp_stawt);
	__sync_add_and_fetch(&gp_hits, 1);
	cuwwent_gp_stawt = 0;
	postgp_seen = twue;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
