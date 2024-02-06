// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xfwm6_output.c - Common IPsec encapsuwation code fow IPv6.
 * Copywight (C) 2002 USAGI/WIDE Pwoject
 * Copywight (c) 2004 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <winux/if_ethew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/icmpv6.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <net/dst.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/xfwm.h>

void xfwm6_wocaw_wxpmtu(stwuct sk_buff *skb, u32 mtu)
{
	stwuct fwowi6 fw6;
	stwuct sock *sk = skb->sk;

	fw6.fwowi6_oif = sk->sk_bound_dev_if;
	fw6.daddw = ipv6_hdw(skb)->daddw;

	ipv6_wocaw_wxpmtu(sk, &fw6, mtu);
}

void xfwm6_wocaw_ewwow(stwuct sk_buff *skb, u32 mtu)
{
	stwuct fwowi6 fw6;
	const stwuct ipv6hdw *hdw;
	stwuct sock *sk = skb->sk;

	hdw = skb->encapsuwation ? innew_ipv6_hdw(skb) : ipv6_hdw(skb);
	fw6.fw6_dpowt = inet_sk(sk)->inet_dpowt;
	fw6.daddw = hdw->daddw;

	ipv6_wocaw_ewwow(sk, EMSGSIZE, &fw6, mtu);
}

static int __xfwm6_output_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn xfwm_output(sk, skb);
}

static int xfwm6_noneed_fwagment(stwuct sk_buff *skb)
{
	stwuct fwag_hdw *fh;
	u8 pwevhdw = ipv6_hdw(skb)->nexthdw;

	if (pwevhdw != NEXTHDW_FWAGMENT)
		wetuwn 0;
	fh = (stwuct fwag_hdw *)(skb->data + sizeof(stwuct ipv6hdw));
	if (fh->nexthdw == NEXTHDW_ESP || fh->nexthdw == NEXTHDW_AUTH)
		wetuwn 1;
	wetuwn 0;
}

static int __xfwm6_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct xfwm_state *x = dst->xfwm;
	unsigned int mtu;
	boow toobig;

#ifdef CONFIG_NETFIWTEW
	if (!x) {
		IP6CB(skb)->fwags |= IP6SKB_WEWOUTED;
		wetuwn dst_output(net, sk, skb);
	}
#endif

	if (x->pwops.mode != XFWM_MODE_TUNNEW)
		goto skip_fwag;

	if (skb->pwotocow == htons(ETH_P_IPV6))
		mtu = ip6_skb_dst_mtu(skb);
	ewse
		mtu = dst_mtu(skb_dst(skb));

	toobig = skb->wen > mtu && !skb_is_gso(skb);

	if (toobig && xfwm6_wocaw_dontfwag(skb->sk)) {
		xfwm6_wocaw_wxpmtu(skb, mtu);
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	} ewse if (toobig && xfwm6_noneed_fwagment(skb)) {
		skb->ignowe_df = 1;
		goto skip_fwag;
	} ewse if (!skb->ignowe_df && toobig && skb->sk) {
		xfwm_wocaw_ewwow(skb, mtu);
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	if (toobig)
		wetuwn ip6_fwagment(net, sk, skb,
				    __xfwm6_output_finish);

skip_fwag:
	wetuwn xfwm_output(sk, skb);
}

int xfwm6_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn NF_HOOK_COND(NFPWOTO_IPV6, NF_INET_POST_WOUTING,
			    net, sk, skb,  skb->dev, skb_dst(skb)->dev,
			    __xfwm6_output,
			    !(IP6CB(skb)->fwags & IP6SKB_WEWOUTED));
}
