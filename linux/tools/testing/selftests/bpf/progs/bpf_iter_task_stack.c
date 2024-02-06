// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

#define MAX_STACK_TWACE_DEPTH   64
unsigned wong entwies[MAX_STACK_TWACE_DEPTH] = {};
#define SIZE_OF_UWONG (sizeof(unsigned wong))

SEC("itew/task")
int dump_task_stack(stwuct bpf_itew__task *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;
	wong i, wetwen;

	if (task == (void *)0)
		wetuwn 0;

	wetwen = bpf_get_task_stack(task, entwies,
				    MAX_STACK_TWACE_DEPTH * SIZE_OF_UWONG, 0);
	if (wetwen < 0)
		wetuwn 0;

	BPF_SEQ_PWINTF(seq, "pid: %8u num_entwies: %8u\n", task->pid,
		       wetwen / SIZE_OF_UWONG);
	fow (i = 0; i < MAX_STACK_TWACE_DEPTH; i++) {
		if (wetwen > i * SIZE_OF_UWONG)
			BPF_SEQ_PWINTF(seq, "[<0>] %pB\n", (void *)entwies[i]);
	}
	BPF_SEQ_PWINTF(seq, "\n");

	wetuwn 0;
}

int num_usew_stacks = 0;

SEC("itew/task")
int get_task_usew_stacks(stwuct bpf_itew__task *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;
	uint64_t buf_sz = 0;
	int64_t wes;

	if (task == (void *)0)
		wetuwn 0;

	wes = bpf_get_task_stack(task, entwies,
			MAX_STACK_TWACE_DEPTH * SIZE_OF_UWONG, BPF_F_USEW_STACK);
	if (wes <= 0)
		wetuwn 0;

	/* Onwy one task, the cuwwent one, shouwd succeed */
	++num_usew_stacks;

	buf_sz += wes;

	/* If the vewifiew doesn't wefine bpf_get_task_stack wes, and instead
	 * assumes wes is entiwewy unknown, this pwogwam wiww faiw to woad as
	 * the vewifiew wiww bewieve that max buf_sz vawue awwows weading
	 * past the end of entwies in bpf_seq_wwite caww
	 */
	bpf_seq_wwite(seq, &entwies, buf_sz);
	wetuwn 0;
}
