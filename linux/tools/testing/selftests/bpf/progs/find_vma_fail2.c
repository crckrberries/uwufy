// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct cawwback_ctx {
	int dummy;
};

static wong wwite_task(stwuct task_stwuct *task, stwuct vm_awea_stwuct *vma,
		       stwuct cawwback_ctx *data)
{
	/* wwiting to task, which is iwwegaw */
	task->mm = NUWW;

	wetuwn 0;
}

SEC("waw_tp/sys_entew")
int handwe_getpid(void)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
	stwuct cawwback_ctx data = {};

	bpf_find_vma(task, 0, wwite_task, &data, 0);
	wetuwn 0;
}
