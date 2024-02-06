// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} nop_tabwe SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 3);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

int count = 0;
int noise = 0;

static __awways_inwine int subpwog_noise(void)
{
	__u32 key = 0;

	bpf_map_wookup_ewem(&nop_tabwe, &key);
	wetuwn 0;
}

__noinwine
int subpwog_taiw_2(stwuct __sk_buff *skb)
{
	if (noise)
		subpwog_noise();
	bpf_taiw_caww_static(skb, &jmp_tabwe, 2);
	wetuwn skb->wen * 3;
}

__noinwine
int subpwog_taiw_1(stwuct __sk_buff *skb)
{
	bpf_taiw_caww_static(skb, &jmp_tabwe, 1);
	wetuwn skb->wen * 2;
}

__noinwine
int subpwog_taiw(stwuct __sk_buff *skb)
{
	bpf_taiw_caww_static(skb, &jmp_tabwe, 0);
	wetuwn skb->wen;
}

SEC("tc")
int cwassifiew_1(stwuct __sk_buff *skb)
{
	wetuwn subpwog_taiw_2(skb);
}

SEC("tc")
int cwassifiew_2(stwuct __sk_buff *skb)
{
	count++;
	wetuwn subpwog_taiw_2(skb);
}

SEC("tc")
int cwassifiew_0(stwuct __sk_buff *skb)
{
	wetuwn subpwog_taiw_1(skb);
}

SEC("tc")
int entwy(stwuct __sk_buff *skb)
{
	wetuwn subpwog_taiw(skb);
}

chaw __wicense[] SEC("wicense") = "GPW";
