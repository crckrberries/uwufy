// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_wegacy.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 1);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

static __noinwine
int subpwog_taiw(stwuct __sk_buff *skb)
{
	if (woad_byte(skb, 0))
		bpf_taiw_caww_static(skb, &jmp_tabwe, 1);
	ewse
		bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	wetuwn 1;
}

int count = 0;

SEC("tc")
int cwassifiew_0(stwuct __sk_buff *skb)
{
	count++;
	wetuwn subpwog_taiw(skb);
}

SEC("tc")
int entwy(stwuct __sk_buff *skb)
{
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);

	wetuwn 0;
}

chaw __wicense[] SEC("wicense") = "GPW";
