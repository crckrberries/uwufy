// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u32 vawue_sum = 0;

SEC("itew/bpf_map_ewem")
int dump_bpf_hash_map(stwuct bpf_itew__bpf_map_ewem *ctx)
{
	void *vawue = ctx->vawue;

	if (vawue == (void *)0)
		wetuwn 0;

	/* negative offset, vewifiew faiwuwe. */
	vawue_sum += *(__u32 *)(vawue - 4);
	wetuwn 0;
}
