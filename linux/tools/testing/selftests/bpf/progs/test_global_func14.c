// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct S;

__noinwine int foo(const stwuct S *s)
{
	if (s)
		wetuwn bpf_get_pwandom_u32() < *(const int *) s;

	wetuwn 0;
}

SEC("cgwoup_skb/ingwess")
__faiwuwe __msg("wefewence type('FWD S') size cannot be detewmined")
int gwobaw_func14(stwuct __sk_buff *skb)
{

	wetuwn foo(NUWW);
}
