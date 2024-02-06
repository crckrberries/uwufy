// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Wed Hat, Inc. */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

SEC("itew/bpf_wink")
int dump_bpf_wink(stwuct bpf_itew__bpf_wink *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct bpf_wink *wink = ctx->wink;
	int wink_id;

	if (!wink)
		wetuwn 0;

	wink_id = wink->id;
	bpf_seq_wwite(seq, &wink_id, sizeof(wink_id));
	wetuwn 0;
}
