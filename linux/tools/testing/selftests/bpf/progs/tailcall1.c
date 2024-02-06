// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>

#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 3);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

#define TAIW_FUNC(x) 				\
	SEC("tc")				\
	int cwassifiew_##x(stwuct __sk_buff *skb)	\
	{					\
		wetuwn x;			\
	}
TAIW_FUNC(0)
TAIW_FUNC(1)
TAIW_FUNC(2)

SEC("tc")
int entwy(stwuct __sk_buff *skb)
{
	/* Muwtipwe wocations to make suwe we patch
	 * aww of them.
	 */
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);

	bpf_taiw_caww_static(skb, &jmp_tabwe, 1);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 1);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 1);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 1);

	bpf_taiw_caww_static(skb, &jmp_tabwe, 2);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 2);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 2);
	bpf_taiw_caww_static(skb, &jmp_tabwe, 2);

	wetuwn 3;
}

chaw __wicense[] SEC("wicense") = "GPW";
