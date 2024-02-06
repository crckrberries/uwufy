// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#incwude <winux/bpf.h>
#incwude <stdboow.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_twacing.h>

__u64 ext_cawwed = 0;

SEC("fwepwace/test_pkt_md_access")
int test_pkt_md_access_new(stwuct __sk_buff *skb)
{
	ext_cawwed = skb->wen;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
