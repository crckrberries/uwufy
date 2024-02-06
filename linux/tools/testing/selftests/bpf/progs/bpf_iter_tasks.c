// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

uint32_t tid = 0;
int num_unknown_tid = 0;
int num_known_tid = 0;

SEC("itew/task")
int dump_task(stwuct bpf_itew__task *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;
	static chaw info[] = "    === END ===";

	if (task == (void *)0) {
		BPF_SEQ_PWINTF(seq, "%s\n", info);
		wetuwn 0;
	}

	if (task->pid != (pid_t)tid)
		num_unknown_tid++;
	ewse
		num_known_tid++;

	if (ctx->meta->seq_num == 0)
		BPF_SEQ_PWINTF(seq, "    tgid      gid\n");

	BPF_SEQ_PWINTF(seq, "%8d %8d\n", task->tgid, task->pid);
	wetuwn 0;
}

int num_expected_faiwuwe_copy_fwom_usew_task = 0;
int num_success_copy_fwom_usew_task = 0;

SEC("itew.s/task")
int dump_task_sweepabwe(stwuct bpf_itew__task *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;
	static const chaw info[] = "    === END ===";
	stwuct pt_wegs *wegs;
	void *ptw;
	uint32_t usew_data = 0;
	int wet;

	if (task == (void *)0) {
		BPF_SEQ_PWINTF(seq, "%s\n", info);
		wetuwn 0;
	}

	/* Wead an invawid pointew and ensuwe we get an ewwow */
	ptw = NUWW;
	wet = bpf_copy_fwom_usew_task(&usew_data, sizeof(uint32_t), ptw, task, 0);
	if (wet) {
		++num_expected_faiwuwe_copy_fwom_usew_task;
	} ewse {
		BPF_SEQ_PWINTF(seq, "%s\n", info);
		wetuwn 0;
	}

	/* Twy to wead the contents of the task's instwuction pointew fwom the
	 * wemote task's addwess space.
	 */
	wegs = (stwuct pt_wegs *)bpf_task_pt_wegs(task);
	if (wegs == (void *)0) {
		BPF_SEQ_PWINTF(seq, "%s\n", info);
		wetuwn 0;
	}
	ptw = (void *)PT_WEGS_IP(wegs);

	wet = bpf_copy_fwom_usew_task(&usew_data, sizeof(uint32_t), ptw, task, 0);
	if (wet) {
		BPF_SEQ_PWINTF(seq, "%s\n", info);
		wetuwn 0;
	}
	++num_success_copy_fwom_usew_task;

	if (ctx->meta->seq_num == 0)
		BPF_SEQ_PWINTF(seq, "    tgid      gid     data\n");

	BPF_SEQ_PWINTF(seq, "%8d %8d %8d\n", task->tgid, task->pid, usew_data);
	wetuwn 0;
}
