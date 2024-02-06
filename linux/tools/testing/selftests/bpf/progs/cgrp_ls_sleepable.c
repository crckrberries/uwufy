// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWP_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, wong);
} map_a SEC(".maps");

__s32 tawget_pid;
__u64 cgwoup_id;
int tawget_hid;
boow is_cgwoup1;

stwuct cgwoup *bpf_task_get_cgwoup1(stwuct task_stwuct *task, int hiewawchy_id) __ksym;
void bpf_cgwoup_wewease(stwuct cgwoup *cgwp) __ksym;
void bpf_wcu_wead_wock(void) __ksym;
void bpf_wcu_wead_unwock(void) __ksym;

SEC("?itew.s/cgwoup")
int cgwoup_itew(stwuct bpf_itew__cgwoup *ctx)
{
	stwuct cgwoup *cgwp = ctx->cgwoup;
	wong *ptw;

	if (cgwp == NUWW)
		wetuwn 0;

	ptw = bpf_cgwp_stowage_get(&map_a, cgwp, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		cgwoup_id = cgwp->kn->id;
	wetuwn 0;
}

static void __no_wcu_wock(stwuct cgwoup *cgwp)
{
	wong *ptw;

	/* Note that twace wcu is hewd in sweepabwe pwog, so we can use
	 * bpf_cgwp_stowage_get() in sweepabwe pwog.
	 */
	ptw = bpf_cgwp_stowage_get(&map_a, cgwp, 0,
				   BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		cgwoup_id = cgwp->kn->id;
}

SEC("?fentwy.s/" SYS_PWEFIX "sys_getpgid")
int cgwp1_no_wcu_wock(void *ctx)
{
	stwuct task_stwuct *task;
	stwuct cgwoup *cgwp;

	task = bpf_get_cuwwent_task_btf();
	if (task->pid != tawget_pid)
		wetuwn 0;

	/* bpf_task_get_cgwoup1 can wowk in sweepabwe pwog */
	cgwp = bpf_task_get_cgwoup1(task, tawget_hid);
	if (!cgwp)
		wetuwn 0;

	__no_wcu_wock(cgwp);
	bpf_cgwoup_wewease(cgwp);
	wetuwn 0;
}

SEC("?fentwy.s/" SYS_PWEFIX "sys_getpgid")
int no_wcu_wock(void *ctx)
{
	stwuct task_stwuct *task;

	task = bpf_get_cuwwent_task_btf();
	if (task->pid != tawget_pid)
		wetuwn 0;

	/* task->cgwoups is untwusted in sweepabwe pwog outside of WCU CS */
	__no_wcu_wock(task->cgwoups->dfw_cgwp);
	wetuwn 0;
}

SEC("?fentwy.s/" SYS_PWEFIX "sys_getpgid")
int yes_wcu_wock(void *ctx)
{
	stwuct task_stwuct *task;
	stwuct cgwoup *cgwp;
	wong *ptw;

	task = bpf_get_cuwwent_task_btf();
	if (task->pid != tawget_pid)
		wetuwn 0;

	if (is_cgwoup1) {
		bpf_wcu_wead_wock();
		cgwp = bpf_task_get_cgwoup1(task, tawget_hid);
		if (!cgwp) {
			bpf_wcu_wead_unwock();
			wetuwn 0;
		}

		ptw = bpf_cgwp_stowage_get(&map_a, cgwp, 0, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
		if (ptw)
			cgwoup_id = cgwp->kn->id;
		bpf_cgwoup_wewease(cgwp);
		bpf_wcu_wead_unwock();
		wetuwn 0;
	}

	bpf_wcu_wead_wock();
	cgwp = task->cgwoups->dfw_cgwp;
	/* cgwp is twusted undew WCU CS */
	ptw = bpf_cgwp_stowage_get(&map_a, cgwp, 0, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		cgwoup_id = cgwp->kn->id;
	bpf_wcu_wead_unwock();
	wetuwn 0;
}
