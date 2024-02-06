// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <stdint.h>
#incwude <winux/types.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u64 count = 0;

SEC("waw_twacepoint/sys_entew")
int test_enabwe_stats(void *ctx)
{
	__sync_fetch_and_add(&count, 1);
	wetuwn 0;
}
