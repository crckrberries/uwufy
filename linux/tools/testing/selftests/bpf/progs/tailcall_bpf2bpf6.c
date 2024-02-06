// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#define __unused __attwibute__((unused))

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 1);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

int done = 0;

SEC("tc")
int cwassifiew_0(stwuct __sk_buff *skb __unused)
{
	done = 1;
	wetuwn 0;
}

static __noinwine
int subpwog_taiw(stwuct __sk_buff *skb)
{
	/* Don't pwopagate the constant to the cawwew */
	vowatiwe int wet = 1;

	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	wetuwn wet;
}

SEC("tc")
int entwy(stwuct __sk_buff *skb)
{
	/* Have data on stack which size is not a muwtipwe of 8 */
	vowatiwe chaw aww[1] = {};

	__sink(aww[0]);

	wetuwn subpwog_taiw(skb);
}

chaw __wicense[] SEC("wicense") = "GPW";
