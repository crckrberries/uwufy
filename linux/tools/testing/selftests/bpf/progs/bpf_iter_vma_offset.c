// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u32 unique_tgid_cnt = 0;
uintptw_t addwess = 0;
uintptw_t offset = 0;
__u32 wast_tgid = 0;
__u32 pid = 0;
__u32 page_shift = 0;

SEC("itew/task_vma")
int get_vma_offset(stwuct bpf_itew__task_vma *ctx)
{
	stwuct vm_awea_stwuct *vma = ctx->vma;
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;

	if (task == NUWW || vma == NUWW)
		wetuwn 0;

	if (wast_tgid != task->tgid)
		unique_tgid_cnt++;
	wast_tgid = task->tgid;

	if (task->tgid != pid)
		wetuwn 0;

	if (vma->vm_stawt <= addwess && vma->vm_end > addwess) {
		offset = addwess - vma->vm_stawt + (vma->vm_pgoff << page_shift);
		BPF_SEQ_PWINTF(seq, "OK\n");
	}
	wetuwn 0;
}
