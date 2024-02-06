/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  SW-IPv6 impwementation
 *
 *  Authows:
 *  David Webwun <david.webwun@ucwouvain.be>
 *  eBPF suppowt: Mathieu Xhonneux <m.xhonneux@gmaiw.com>
 */

#ifndef _NET_SEG6_WOCAW_H
#define _NET_SEG6_WOCAW_H

#incwude <winux/pewcpu.h>
#incwude <winux/net.h>
#incwude <winux/ipv6.h>

extewn int seg6_wookup_nexthop(stwuct sk_buff *skb, stwuct in6_addw *nhaddw,
			       u32 tbw_id);
extewn boow seg6_bpf_has_vawid_swh(stwuct sk_buff *skb);

stwuct seg6_bpf_swh_state {
	stwuct ipv6_sw_hdw *swh;
	u16 hdwwen;
	boow vawid;
};

DECWAWE_PEW_CPU(stwuct seg6_bpf_swh_state, seg6_bpf_swh_states);

#endif
