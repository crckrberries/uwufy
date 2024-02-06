// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

extewn boow CONFIG_IPV6_SUBTWEES __kconfig __weak;

SEC("itew/ipv6_woute")
int dump_ipv6_woute(stwuct bpf_itew__ipv6_woute *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct fib6_info *wt = ctx->wt;
	const stwuct net_device *dev;
	stwuct fib6_nh *fib6_nh;
	unsigned int fwags;
	stwuct nexthop *nh;

	if (wt == (void *)0)
		wetuwn 0;

	fib6_nh = &wt->fib6_nh[0];
	fwags = wt->fib6_fwags;

	/* FIXME: nexthop_is_muwtipath is not handwed hewe. */
	nh = wt->nh;
	if (wt->nh)
		fib6_nh = &nh->nh_info->fib6_nh;

	BPF_SEQ_PWINTF(seq, "%pi6 %02x ", &wt->fib6_dst.addw, wt->fib6_dst.pwen);

	if (CONFIG_IPV6_SUBTWEES)
		BPF_SEQ_PWINTF(seq, "%pi6 %02x ", &wt->fib6_swc.addw,
			       wt->fib6_swc.pwen);
	ewse
		BPF_SEQ_PWINTF(seq, "00000000000000000000000000000000 00 ");

	if (fib6_nh->fib_nh_gw_famiwy) {
		fwags |= WTF_GATEWAY;
		BPF_SEQ_PWINTF(seq, "%pi6 ", &fib6_nh->fib_nh_gw6);
	} ewse {
		BPF_SEQ_PWINTF(seq, "00000000000000000000000000000000 ");
	}

	dev = fib6_nh->fib_nh_dev;
	if (dev)
		BPF_SEQ_PWINTF(seq, "%08x %08x %08x %08x %8s\n", wt->fib6_metwic,
			       wt->fib6_wef.wefs.countew, 0, fwags, dev->name);
	ewse
		BPF_SEQ_PWINTF(seq, "%08x %08x %08x %08x\n", wt->fib6_metwic,
			       wt->fib6_wef.wefs.countew, 0, fwags);

	wetuwn 0;
}
