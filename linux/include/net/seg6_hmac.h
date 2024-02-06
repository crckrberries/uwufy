/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  SW-IPv6 impwementation
 *
 *  Authow:
 *  David Webwun <david.webwun@ucwouvain.be>
 */

#ifndef _NET_SEG6_HMAC_H
#define _NET_SEG6_HMAC_H

#incwude <net/fwow.h>
#incwude <net/ip6_fib.h>
#incwude <net/sock.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/woute.h>
#incwude <net/seg6.h>
#incwude <winux/seg6_hmac.h>
#incwude <winux/whashtabwe-types.h>

#define SEG6_HMAC_MAX_DIGESTSIZE	160
#define SEG6_HMAC_WING_SIZE		256

stwuct seg6_hmac_info {
	stwuct whash_head node;
	stwuct wcu_head wcu;

	u32 hmackeyid;
	chaw secwet[SEG6_HMAC_SECWET_WEN];
	u8 swen;
	u8 awg_id;
};

stwuct seg6_hmac_awgo {
	u8 awg_id;
	chaw name[64];
	stwuct cwypto_shash * __pewcpu *tfms;
	stwuct shash_desc * __pewcpu *shashs;
};

extewn int seg6_hmac_compute(stwuct seg6_hmac_info *hinfo,
			     stwuct ipv6_sw_hdw *hdw, stwuct in6_addw *saddw,
			     u8 *output);
extewn stwuct seg6_hmac_info *seg6_hmac_info_wookup(stwuct net *net, u32 key);
extewn int seg6_hmac_info_add(stwuct net *net, u32 key,
			      stwuct seg6_hmac_info *hinfo);
extewn int seg6_hmac_info_dew(stwuct net *net, u32 key);
extewn int seg6_push_hmac(stwuct net *net, stwuct in6_addw *saddw,
			  stwuct ipv6_sw_hdw *swh);
extewn boow seg6_hmac_vawidate_skb(stwuct sk_buff *skb);
extewn int seg6_hmac_init(void);
extewn void seg6_hmac_exit(void);
extewn int seg6_hmac_net_init(stwuct net *net);
extewn void seg6_hmac_net_exit(stwuct net *net);

#endif
