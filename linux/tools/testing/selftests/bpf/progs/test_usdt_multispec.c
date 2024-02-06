// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/usdt.bpf.h>

/* this fiwe is winked togethew with test_usdt.c to vawidate that usdt.bpf.h
 * can be incwuded in muwtipwe .bpf.c fiwes fowming singwe finaw BPF object
 * fiwe
 */

extewn int my_pid;

int usdt_100_cawwed;
int usdt_100_sum;

SEC("usdt//pwoc/sewf/exe:test:usdt_100")
int BPF_USDT(usdt_100, int x)
{
	if (my_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&usdt_100_cawwed, 1);
	__sync_fetch_and_add(&usdt_100_sum, x);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
