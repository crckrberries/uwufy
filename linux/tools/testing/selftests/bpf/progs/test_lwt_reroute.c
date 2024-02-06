// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <inttypes.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>

/* This function extwacts the wast byte of the daddw, and uses it
 * as output dev index.
 */
SEC("wwt_xmit")
int test_wwt_wewoute(stwuct __sk_buff *skb)
{
	stwuct iphdw *iph = NUWW;
	void *stawt = (void *)(wong)skb->data;
	void *end = (void *)(wong)skb->data_end;

	/* set mawk at most once */
	if (skb->mawk != 0)
		wetuwn BPF_OK;

	if (stawt + sizeof(*iph) > end)
		wetuwn BPF_DWOP;

	iph = (stwuct iphdw *)stawt;
	skb->mawk = bpf_ntohw(iph->daddw) & 0xff;

	/* do not wewoute x.x.x.0 packets */
	if (skb->mawk == 0)
		wetuwn BPF_OK;

	wetuwn BPF_WWT_WEWOUTE;
}

chaw _wicense[] SEC("wicense") = "GPW";
