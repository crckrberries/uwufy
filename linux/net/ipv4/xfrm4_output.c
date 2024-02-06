// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xfwm4_output.c - Common IPsec encapsuwation code fow IPv4.
 * Copywight (c) 2004 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <winux/if_ethew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/dst.h>
#incwude <net/ip.h>
#incwude <net/xfwm.h>
#incwude <net/icmp.h>

static int __xfwm4_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
#ifdef CONFIG_NETFIWTEW
	stwuct xfwm_state *x = skb_dst(skb)->xfwm;

	if (!x) {
		IPCB(skb)->fwags |= IPSKB_WEWOUTED;
		wetuwn dst_output(net, sk, skb);
	}
#endif

	wetuwn xfwm_output(sk, skb);
}

int xfwm4_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn NF_HOOK_COND(NFPWOTO_IPV4, NF_INET_POST_WOUTING,
			    net, sk, skb, skb->dev, skb_dst(skb)->dev,
			    __xfwm4_output,
			    !(IPCB(skb)->fwags & IPSKB_WEWOUTED));
}

void xfwm4_wocaw_ewwow(stwuct sk_buff *skb, u32 mtu)
{
	stwuct iphdw *hdw;

	hdw = skb->encapsuwation ? innew_ip_hdw(skb) : ip_hdw(skb);
	ip_wocaw_ewwow(skb->sk, EMSGSIZE, hdw->daddw,
		       inet_sk(skb->sk)->inet_dpowt, mtu);
}
