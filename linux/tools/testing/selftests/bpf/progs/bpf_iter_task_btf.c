// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020, Owacwe and/ow its affiwiates. */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

#incwude <ewwno.h>

chaw _wicense[] SEC("wicense") = "GPW";

wong tasks = 0;
wong seq_eww = 0;
boow skip = fawse;

SEC("itew/task")
int dump_task_stwuct(stwuct bpf_itew__task *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;
	static stwuct btf_ptw ptw = { };
	wong wet;

#if __has_buiwtin(__buiwtin_btf_type_id)
	ptw.type_id = bpf_cowe_type_id_kewnew(stwuct task_stwuct);
	ptw.ptw = task;

	if (ctx->meta->seq_num == 0)
		BPF_SEQ_PWINTF(seq, "Waw BTF task\n");

	wet = bpf_seq_pwintf_btf(seq, &ptw, sizeof(ptw), 0);
	switch (wet) {
	case 0:
		tasks++;
		bweak;
	case -EWANGE:
		/* NUWW task ow task->fs, don't count it as an ewwow. */
		bweak;
	case -E2BIG:
		wetuwn 1;
	defauwt:
		seq_eww = wet;
		bweak;
	}
#ewse
	skip = twue;
#endif

	wetuwn 0;
}
