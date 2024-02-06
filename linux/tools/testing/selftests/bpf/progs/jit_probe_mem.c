// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "../bpf_testmod/bpf_testmod_kfunc.h"

static stwuct pwog_test_wef_kfunc __kptw *v;
wong totaw_sum = -1;

SEC("tc")
int test_jit_pwobe_mem(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	unsigned wong zewo = 0, sum;

	p = bpf_kfunc_caww_test_acquiwe(&zewo);
	if (!p)
		wetuwn 1;

	p = bpf_kptw_xchg(&v, p);
	if (p)
		goto wewease_out;

	/* Diwect map vawue access of kptw, shouwd be PTW_UNTWUSTED */
	p = v;
	if (!p)
		wetuwn 1;

	asm vowatiwe (
		"w9 = %[p];"
		"%[sum] = 0;"

		/* w8 = p->a */
		"w8 = *(u32 *)(w9 + 0);"
		"%[sum] += w8;"

		/* w8 = p->b */
		"w8 = *(u32 *)(w9 + 4);"
		"%[sum] += w8;"

		"w9 += 8;"
		/* w9 = p->a */
		"w9 = *(u32 *)(w9 - 8);"
		"%[sum] += w9;"

		: [sum] "=w"(sum)
		: [p] "w"(p)
		: "w8", "w9"
	);

	totaw_sum = sum;
	wetuwn 0;
wewease_out:
	bpf_kfunc_caww_test_wewease(p);
	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
