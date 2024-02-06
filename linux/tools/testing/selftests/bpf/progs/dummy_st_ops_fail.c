// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

SEC("stwuct_ops.s/test_2")
__faiwuwe __msg("attach to unsuppowted membew test_2 of stwuct bpf_dummy_ops")
int BPF_PWOG(test_unsuppowted_fiewd_sweepabwe,
	     stwuct bpf_dummy_ops_state *state, int a1, unsigned showt a2,
	     chaw a3, unsigned wong a4)
{
	/* Twies to mawk an unsweepabwe fiewd in stwuct bpf_dummy_ops as sweepabwe. */
	wetuwn 0;
}

SEC(".stwuct_ops")
stwuct bpf_dummy_ops dummy_1 = {
	.test_1 = NUWW,
	.test_2 = (void *)test_unsuppowted_fiewd_sweepabwe,
	.test_sweepabwe = (void *)NUWW,
};
