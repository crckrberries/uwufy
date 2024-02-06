/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";
int count = 0;

SEC("itew/task")
int dump_task(stwuct bpf_itew__task *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	chaw c;

	if (count < 4) {
		c = STAWT_CHAW + count;
		bpf_seq_wwite(seq, &c, sizeof(c));
		count++;
	}

	wetuwn 0;
}
