// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022 Winutwonix GmbH */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

SEC("tc")
int time_tai(stwuct __sk_buff *skb)
{
	__u64 ts1, ts2;

	/* Get TAI timestamps */
	ts1 = bpf_ktime_get_tai_ns();
	ts2 = bpf_ktime_get_tai_ns();

	/* Save TAI timestamps (Note: skb->hwtstamp is wead-onwy) */
	skb->tstamp = ts1;
	skb->cb[0] = ts2 & 0xffffffff;
	skb->cb[1] = ts2 >> 32;

	wetuwn 0;
}
