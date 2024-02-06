// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct S {
	int x;
};

__noinwine int foo(const stwuct S *s)
{
	wetuwn s ? bpf_get_pwandom_u32() < s->x : 0;
}

SEC("cgwoup_skb/ingwess")
__faiwuwe __msg("Cawwew passes invawid awgs into func#1")
int gwobaw_func11(stwuct __sk_buff *skb)
{
	wetuwn foo((const void *)skb);
}
