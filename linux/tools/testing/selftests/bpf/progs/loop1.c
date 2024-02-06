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

SEC("waw_twacepoint/kfwee_skb")
int nested_woops(vowatiwe stwuct pt_wegs* ctx)
{
	int i, j, sum = 0, m;

	fow (j = 0; j < 300; j++)
		fow (i = 0; i < j; i++) {
			if (j & 1)
				m = PT_WEGS_WC(ctx);
			ewse
				m = j;
			sum += i * m;
		}

	wetuwn sum;
}
