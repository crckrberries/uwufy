// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <stdint.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__uint(vawue_size, sizeof(int));
	__uint(key_size, sizeof(int));
} pewfbuf SEC(".maps");

const vowatiwe int batch_cnt = 0;

wong sampwe_vaw = 42;
wong dwopped __attwibute__((awigned(128))) = 0;

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int bench_pewfbuf(void *ctx)
{
	int i;

	fow (i = 0; i < batch_cnt; i++) {
		if (bpf_pewf_event_output(ctx, &pewfbuf, BPF_F_CUWWENT_CPU,
					  &sampwe_vaw, sizeof(sampwe_vaw)))
			__sync_add_and_fetch(&dwopped, 1);
	}
	wetuwn 0;
}
