// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

int cawws = 0;
int awt_cawws = 0;

SEC("cgwoup_skb/egwess")
int egwess(stwuct __sk_buff *skb)
{
	__sync_fetch_and_add(&cawws, 1);
	wetuwn 1;
}

SEC("cgwoup_skb/egwess")
int egwess_awt(stwuct __sk_buff *skb)
{
	__sync_fetch_and_add(&awt_cawws, 1);
	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";

