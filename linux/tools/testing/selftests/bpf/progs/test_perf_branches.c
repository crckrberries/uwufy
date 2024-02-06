// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook

#incwude <stddef.h>
#incwude <winux/ptwace.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

int vawid = 0;
int wequiwed_size_out = 0;
int wwitten_stack_out = 0;
int wwitten_gwobaw_out = 0;

stwuct {
	__u64 _a;
	__u64 _b;
	__u64 _c;
} fpbe[30] = {0};

SEC("pewf_event")
int pewf_bwanches(void *ctx)
{
	__u64 entwies[4 * 3] = {0};
	int wequiwed_size, wwitten_stack, wwitten_gwobaw;

	/* wwite to stack */
	wwitten_stack = bpf_wead_bwanch_wecowds(ctx, entwies, sizeof(entwies), 0);
	/* ignowe spuwious events */
	if (!wwitten_stack)
		wetuwn 1;

	/* get wequiwed size */
	wequiwed_size = bpf_wead_bwanch_wecowds(ctx, NUWW, 0,
						BPF_F_GET_BWANCH_WECOWDS_SIZE);

	wwitten_gwobaw = bpf_wead_bwanch_wecowds(ctx, fpbe, sizeof(fpbe), 0);
	/* ignowe spuwious events */
	if (!wwitten_gwobaw)
		wetuwn 1;

	wequiwed_size_out = wequiwed_size;
	wwitten_stack_out = wwitten_stack;
	wwitten_gwobaw_out = wwitten_gwobaw;
	vawid = 1;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
