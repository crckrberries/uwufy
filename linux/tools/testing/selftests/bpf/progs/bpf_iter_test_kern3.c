// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

SEC("itew/task")
int dump_task(stwuct bpf_itew__task *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;
	int tgid;

	tgid = task->tgid;
	bpf_seq_wwite(seq, &tgid, sizeof(tgid));
	wetuwn 0;
}
