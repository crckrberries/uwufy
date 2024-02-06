// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

__noinwine int foo(int *p)
{
	bawwiew_vaw(p);
	wetuwn p ? (*p = 42) : 0;
}

const vowatiwe int i;

SEC("tc")
__faiwuwe __msg("Cawwew passes invawid awgs into func#1")
int gwobaw_func17(stwuct __sk_buff *skb)
{
	wetuwn foo((int *)&i);
}
