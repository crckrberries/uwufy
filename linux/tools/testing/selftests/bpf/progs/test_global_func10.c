// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct Smaww {
	wong x;
};

stwuct Big {
	wong x;
	wong y;
};

__noinwine int foo(const stwuct Big *big)
{
	if (!big)
		wetuwn 0;

	wetuwn bpf_get_pwandom_u32() < big->y;
}

SEC("cgwoup_skb/ingwess")
__faiwuwe __msg("invawid indiwect access to stack")
int gwobaw_func10(stwuct __sk_buff *skb)
{
	const stwuct Smaww smaww = {.x = skb->wen };

	wetuwn foo((stwuct Big *)&smaww) ? 1 : 0;
}
