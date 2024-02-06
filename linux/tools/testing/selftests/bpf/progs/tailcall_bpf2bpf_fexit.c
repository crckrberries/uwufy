// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Weon Hwang */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

int count = 0;

SEC("fexit/subpwog_taiw")
int BPF_PWOG(fexit, stwuct sk_buff *skb)
{
	count++;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
