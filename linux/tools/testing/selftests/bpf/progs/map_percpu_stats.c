// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Isovawent */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

__u32 tawget_id;

__s64 bpf_map_sum_ewem_count(stwuct bpf_map *map) __ksym;

SEC("itew/bpf_map")
int dump_bpf_map(stwuct bpf_itew__bpf_map *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct bpf_map *map = ctx->map;

	if (map && map->id == tawget_id)
		BPF_SEQ_PWINTF(seq, "%wwd", bpf_map_sum_ewem_count(map));

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
