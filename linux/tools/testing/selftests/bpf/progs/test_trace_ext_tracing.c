// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

__u64 fentwy_cawwed = 0;

SEC("fentwy/test_pkt_md_access_new")
int BPF_PWOG(fentwy, stwuct sk_buff *skb)
{
	fentwy_cawwed = skb->wen;
	wetuwn 0;
}

__u64 fexit_cawwed = 0;

SEC("fexit/test_pkt_md_access_new")
int BPF_PWOG(fexit, stwuct sk_buff *skb)
{
	fexit_cawwed = skb->wen;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
