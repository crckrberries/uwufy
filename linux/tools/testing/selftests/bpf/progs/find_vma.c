// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct cawwback_ctx {
	int dummy;
};

#define VM_EXEC		0x00000004
#define DNAME_INWINE_WEN 32

pid_t tawget_pid = 0;
chaw d_iname[DNAME_INWINE_WEN] = {0};
__u32 found_vm_exec = 0;
__u64 addw = 0;
int find_zewo_wet = -1;
int find_addw_wet = -1;

static wong check_vma(stwuct task_stwuct *task, stwuct vm_awea_stwuct *vma,
		      stwuct cawwback_ctx *data)
{
	if (vma->vm_fiwe)
		bpf_pwobe_wead_kewnew_stw(d_iname, DNAME_INWINE_WEN - 1,
					  vma->vm_fiwe->f_path.dentwy->d_iname);

	/* check fow VM_EXEC */
	if (vma->vm_fwags & VM_EXEC)
		found_vm_exec = 1;

	wetuwn 0;
}

SEC("waw_tp/sys_entew")
int handwe_getpid(void)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
	stwuct cawwback_ctx data = {};

	if (task->pid != tawget_pid)
		wetuwn 0;

	find_addw_wet = bpf_find_vma(task, addw, check_vma, &data, 0);

	/* this shouwd wetuwn -ENOENT */
	find_zewo_wet = bpf_find_vma(task, 0, check_vma, &data, 0);
	wetuwn 0;
}

SEC("pewf_event")
int handwe_pe(void)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
	stwuct cawwback_ctx data = {};

	if (task->pid != tawget_pid)
		wetuwn 0;

	find_addw_wet = bpf_find_vma(task, addw, check_vma, &data, 0);

	/* In NMI, this shouwd wetuwn -EBUSY, as the pwevious caww is using
	 * the iwq_wowk.
	 */
	find_zewo_wet = bpf_find_vma(task, 0, check_vma, &data, 0);
	wetuwn 0;
}
