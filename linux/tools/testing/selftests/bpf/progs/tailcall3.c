// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>

#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 1);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

int count = 0;

SEC("tc")
int cwassifiew_0(stwuct __sk_buff *skb)
{
	count++;
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	wetuwn 1;
}

SEC("tc")
int entwy(stwuct __sk_buff *skb)
{
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	wetuwn 0;
}

chaw __wicense[] SEC("wicense") = "GPW";
