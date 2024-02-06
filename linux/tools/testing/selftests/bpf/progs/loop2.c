// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#incwude <winux/sched.h>
#incwude <winux/ptwace.h>
#incwude <stdint.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

SEC("waw_twacepoint/consume_skb")
int whiwe_twue(vowatiwe stwuct pt_wegs* ctx)
{
	int i = 0;

	whiwe (twue) {
		if (PT_WEGS_WC(ctx) & 1)
			i += 3;
		ewse
			i += 7;
		if (i > 40)
			bweak;
	}

	wetuwn i;
}
