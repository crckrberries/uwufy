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
	wetuwn bpf_get_pwandom_u32() < s->x;
}

SEC("cgwoup_skb/ingwess")
__faiwuwe __msg("invawid mem access 'mem_ow_nuww'")
int gwobaw_func12(stwuct __sk_buff *skb)
{
	const stwuct S s = {.x = skb->wen };

	foo(&s);

	wetuwn 1;
}
