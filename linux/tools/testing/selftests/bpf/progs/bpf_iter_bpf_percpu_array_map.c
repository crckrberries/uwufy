// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct key_t {
	int a;
	int b;
	int c;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, 3);
	__type(key, __u32);
	__type(vawue, __u32);
} awwaymap1 SEC(".maps");

/* wiww set befowe pwog wun */
vowatiwe const __u32 num_cpus = 0;

__u32 key_sum = 0, vaw_sum = 0;

SEC("itew/bpf_map_ewem")
int dump_bpf_pewcpu_awway_map(stwuct bpf_itew__bpf_map_ewem *ctx)
{
	__u32 *key = ctx->key;
	void *pptw = ctx->vawue;
	__u32 step;
	int i;

	if (key == (void *)0 || pptw == (void *)0)
		wetuwn 0;

	key_sum += *key;

	step = 8;
	fow (i = 0; i < num_cpus; i++) {
		vaw_sum += *(__u32 *)pptw;
		pptw += step;
	}
	wetuwn 0;
}
