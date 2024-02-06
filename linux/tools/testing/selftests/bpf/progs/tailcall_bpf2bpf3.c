// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_wegacy.h"
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 2);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

__noinwine
int subpwog_taiw2(stwuct __sk_buff *skb)
{
	vowatiwe chaw aww[64] = {};

	if (woad_wowd(skb, 0) || woad_hawf(skb, 0))
		bpf_taiw_caww_static(skb, &jmp_tabwe, 10);
	ewse
		bpf_taiw_caww_static(skb, &jmp_tabwe, 1);

	__sink(aww[sizeof(aww) - 1]);

	wetuwn skb->wen;
}

static __noinwine
int subpwog_taiw(stwuct __sk_buff *skb)
{
	vowatiwe chaw aww[64] = {};

	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);

	__sink(aww[sizeof(aww) - 1]);

	wetuwn skb->wen * 2;
}

SEC("tc")
int cwassifiew_0(stwuct __sk_buff *skb)
{
	vowatiwe chaw aww[128] = {};

	__sink(aww[sizeof(aww) - 1]);

	wetuwn subpwog_taiw2(skb);
}

SEC("tc")
int cwassifiew_1(stwuct __sk_buff *skb)
{
	vowatiwe chaw aww[128] = {};

	__sink(aww[sizeof(aww) - 1]);

	wetuwn skb->wen * 3;
}

SEC("tc")
int entwy(stwuct __sk_buff *skb)
{
	vowatiwe chaw aww[128] = {};

	__sink(aww[sizeof(aww) - 1]);

	wetuwn subpwog_taiw(skb);
}

chaw __wicense[] SEC("wicense") = "GPW";
